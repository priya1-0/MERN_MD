
/* ************************************************************************* */
/*
 *	iproute.c
 *
 *	(C) 1994 - 2006 VOCAL Technologies, Ltd.
 *
 *	ALL RIGHTS RESERVED.  PROPRIETARY AND CONFIDENTIAL.
 *
 *	VOCAL Technologies, Ltd.
 *	90A John Muir Drive.
 *	Buffalo, NY  14228
 *
 *	Product:	LANsEND
 *
 *	Module:		IP
 *
 *	This file contains the lower half of IP consistin of gateway routines.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 19:52:55  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#include "system/system.h"
#include "lansend/global.h"

#include "net/net.h"
#include "sys/sys.h"
#include "dev/dev.h"

#include "ip/ip.h"

#include "ip/local.h"

#include "utils/utils.h"
#include "trace/trace.h"

/* Add an IP datagram to an interface output queue, sorting first by
 * the precedence field in the IP header, and secondarily by an
 * "interactive" flag set by peeking at the transport layer to see
 * if the packet belongs to what appears to be an interactive session.
 * A layer violation, yes, but a useful one...
 *
 * IFACE is the queue that the packet is going out on.
 * GATEWAY is the address to send the packet to.
 * IP is the ip header for the packet.
 * BP is the data section of the packet.
 * CKGOOD is the checksum for this packet.  If it's 0 then compute it.
 *
 * Return 0 if all went ok, else -1 */
LOCAL int
q_pkt (struct iface *iface, struct sockaddr *gateway, struct ip *ip, struct mbuf *bp, int ckgood)
{
	struct mbuf *tbp;
	struct udp udp;
	int ret;

	/* Put the ip header in front of the packet */
	if ((tbp = htonip (ip, bp, ckgood)) == NULLBUF) {
		free_p (bp);
		return -1;
	}
	iface->ipsndcnt++;

	/* Create priority field consisting of tos (Type Of Service) with 2
	 * unused low order bits stripped, one of which we'll use as an
	 * "interactive" flag and the other as a "non-maintanence" flag */
	tbp->priority = (ip->tos & 0xfc);

	/* If Queue empty, no priority decisions to be made.
	 * This is the usual case for fast networks like Ethernet,
	 * so we can avoid some time - consuming stuff.
	 */
	if (iface->outq != NULLBUF) {
		struct mbuf *dbp;
		struct tcp tcp;
		int i;

		/* See if this packet references a "priority" TCP port number */
		if (ip->protocol == TCP_PTCL && ip->offset == 0) {
			/* Extract a copy of the TCP header so it can be screwed with */
			if (dup_p (&dbp, tbp, IPHDRLEN + ip->optlen,
				 TCPLEN + TCP_MAXOPT) >= TCPLEN) {
				/* Turn it back to host format */
				ntohtcp (&tcp, &dbp);
				/* Is it interactive? */
				for (i = 0; Tcp_interact[i] != -1;i++) {
					if (tcp.source == Tcp_interact[i] ||
					   tcp.dest == Tcp_interact[i]) {
						/* Up it's priority */
						tbp->priority |= 2;
						break;
					}
				}
			}
			free_p (dbp);
		}
	}

	/* Use the specified format for the interface */
	tbp->b_type = iface->ip_type;

	if (tbp->b_type == 0)
		tbp->b_type = PT_IP;

	/* Determine if traffic is of a maintanence type */
	tbp->priority |= 1;
	if (ip->protocol == UDP_PTCL) {
		struct mbuf *dbp;

		/* Extract a copy of the UDP header so it can be screwed with */
		if (dup_p (&dbp, tbp, IPHDRLEN + ip->optlen, UDPHDR) >= UDPHDR) {
			/* Turn it back to host format */
			ntohudp (&udp, &dbp);
			/* Check for RIP packets */
			if ((udp.source == IPPORT_RIP) || (udp.dest == IPPORT_RIP))
				/* Lower it's priority */
				tbp->priority &= ~1;
		}
		free_p (dbp);
	}

	ret = (*iface->iftype->outgoing) (iface, tbp, gateway);
	return ret;
}

/* Route an IP datagram. This is the "hopper" through which all IP datagrams,
 * coming or going, must pass.
 *
 * I_IFACE is the interface that the packet came in on.
 * BP is the level one packet. (With it's link level headers stripped.)
 * RXBROADCAST is set to indicate that the packet came in on a subnet
 *   broadcast. The router will kick the packet upstairs regardless of the
 *   IP destination address.
 *
 * Return 0 if all went ok, else -1 */
ENTRY int
ip_route (struct iface *i_iface, struct mbuf *bp, int rxbroadcast)
{
	struct ip ip;			/* IP header being processed */
	uint16 ip_len;			/* IP header length */
	uint16 length;			/* Length of data portion */
	struct sockaddr gateway;	/* Gateway IP address */
	register struct route *rp;	/* Route table entry */
	struct iface *iface;		/* Output interface, possibly forwarded */
	uint16 offset;			/* Offset into current fragment */
	uint16 mf_flag;			/* Original datagram MF flag */
	int strict = 0;			/* Strict source routing flag */
	uint16 opt_len;		/* Length of current option */
	char *opt;		/* -> beginning of current option */
	int i;
	int ckgood = IP_CS_OLD; /* Has good checksum without modification */
	int pointer;		/* Relative pointer index for sroute/rroute */
	int ret;
	struct route *trp;

	if (i_iface != NULLIF) {
		ipInReceives++; /* Not locally generated */
		i_iface->iprecvcnt++;
		/* Remember type of encapsulation on ethernet */
		if (i_iface->ip_type == 0)
			i_iface->ip_type = bp->b_type;
		bp->b_type = PT_IP;
	}
	if (len_p (bp) < IPHDRLEN) {
		/* The packet is shorter than a legal IP header */
		ipInHdrErrors++;
		free_p (bp);
		return -1;
	}
	/* Sneak a peek at the IP header's IHL field to find its length */
	ip_len = (bp->data[0] & 0xf) << 2;
	if (ip_len < IPHDRLEN) {
		/* The IP header length field is too small */
		ipInHdrErrors++;
		free_p (bp);
		return -1;
	}
	if (cksum (NULLHEADER, bp, ip_len) != 0) {
		/* Bad IP header checksum; discard */
		ipInHdrErrors++;
		free_p (bp);
		return -1;
	}
	/* Extract IP header */
	ntohip (&ip, &bp);

	if (ip.version != IPVERSION) {
		/* We can't handle this version of IP */
		ipInHdrErrors++;
		free_p (bp);
		return -1;
	}

	/* Process packet filtering security if required */
	if (Ip_secure && (i_iface != NULLIF) && (i_iface != Loopback) && ! rxbroadcast) {
		if (rt_lookup (&ip.source) == NULLROUTE) {
			free_p (bp);
			ipInDiscards++;
			return -1;
		}
	}

	/* Trim data segment if necessary */
	length = ip.length - ip_len;	/* Length of data portion */
	trim_mbuf (&bp, length);

	/* If we're running low on memory, return a source quench */
	if (!rxbroadcast && availmem () != 0) {
		icmp_output (&ip, bp, ICMP_QUENCH, 0, NULLICMP);
	}

	/* Process options, if any. Also compute length of secondary IP
	 * header in case fragmentation is needed later */
	strict = 0;
	for (i = 0; i < ip.optlen; i += opt_len) {

		/* First check for the two special 1-byte options */
		switch (ip.options[i] & OPT_NUMBER) {
		case IP_EOL:
			goto no_opt;	/* End of options list, we're done */
		case IP_NOOP:
			opt_len = 1;
			continue;	/* No operation, skip to next option */
		}
		/* Not a 1-byte option, so ensure that there's at least
		 * two bytes of option left, that the option length is
		 * at least two, and that there's enough space left for
		 * the specified option length */
		if (ip.optlen - i < 2 ||
		   ((opt_len = uchar (ip.options[i + 1])) < 2) ||
		   ip.optlen - i < opt_len) {
			/* Truncated option, send ICMP and drop packet */
			if (!rxbroadcast) {
				union icmp_args icmp_args;

				icmp_args.pointer = IPHDRLEN + i;
				icmp_output (&ip, bp, ICMP_PARAM_PROB, 0, &icmp_args);
			}
			free_p (bp);
			return -1;
		}
		opt = (char *) &ip.options[i];

		switch (opt[0] & OPT_NUMBER) {
		case IP_SSROUTE:	/* Strict source route & record route */
			strict = 1;	/* note fall-thru */
		case IP_LSROUTE:	/* Loose source route & record route */
			/* Source routes are ignored unless we're in the
			 * destination field */
			if (opt_len < 3) {
				/* Option is too short to be a legal sroute.
				 * Send an ICMP message and drop it */
				if (!rxbroadcast) {
					union icmp_args icmp_args;

					icmp_args.pointer = IPHDRLEN + i;
					icmp_output (&ip, bp, ICMP_PARAM_PROB, 0, &icmp_args);
				}
				free_p (bp);
				return -1;
			}
			if (!ismyaddr (&ip.dest))
				break;	/* Skip to next option */
			pointer = uchar (opt[2]);
			if (pointer + 4 > opt_len)
				break;	/* Route exhausted; it's for us */

			/* Put address for next hop into destination field,
			 * put our address into the route field, and bump
			 * the pointer. We've already ensured enough space */
			ip.dest.sin_address = get32 (&opt[pointer]);
			put32 (&opt[pointer], (locaddr (&ip.dest))->sin_address);
			opt[2] += 4;
			ckgood = IP_CS_NEW;
			break;
		case IP_RROUTE:	/* Record route */
			if (opt_len < 3) {
				/* Option is too short to be a legal rroute.
				 * Send an ICMP message and drop it */
				if (!rxbroadcast) {
					union icmp_args icmp_args;

					icmp_args.pointer = IPHDRLEN + i;
					icmp_output (&ip, bp, ICMP_PARAM_PROB, 0, &icmp_args);
				}
				free_p (bp);
				return -1;
			}
			pointer = uchar (opt[2]);
			if (pointer + 4 > opt_len) {
				/* Route area exhausted; send an ICMP msg */
				if (!rxbroadcast) {
					union icmp_args icmp_args;

					icmp_args.pointer = IPHDRLEN + i;
					icmp_output (&ip, bp, ICMP_PARAM_PROB, 0, &icmp_args);
				}
				/* Also drop if odd-sized */
				if (pointer != opt_len) {
					free_p (bp);
					return -1;
				}
			} else {

				/* Add our address to the route.
				 * We've already ensured there's enough space */
				put32 (&opt[pointer], (locaddr (&ip.dest))->sin_address);
				opt[2] += 4;
				ckgood = IP_CS_NEW;
			}
			break;
		}
	} /* Processing options */
no_opt:

	/* See if it's a broadcast or addressed to us, and kick it upstairs.
	 * Also look for the special network directed broadcast of 255.255.255.255
	 * and for the interface's broadcast address.  Finally check for BOOTP replies.
	 */

	if (ismyaddr (&ip.dest) || rxbroadcast ||
	  ((i_iface != NULLIF) && (i_iface != Loopback) && ((ip.dest.sin_address == 0xffffffffL) || (inet_hostmatch (&ip.dest, &i_iface->broadcast[AF_INET]))))
	) {
		/* Send it up as a high level packet for us */
		ip_recv (i_iface, &ip, bp, rxbroadcast);
		return 0;
	}
	/* At this point, the packet is not destined to us (even as a broadcast).
	 * If it originated elsewhere, count it as a forwarded datagram.  It could
	 * also be a packet being bounced around interfaces internally */
	if (i_iface != NULLIF) {
		ipForwDatagrams++;
	}
	/* Adjust the IP header checksum to allow for the modified TTL */
	ip.checksum += 0x100;
	if ((ip.checksum & 0xff00) == 0)
		ip.checksum++;	/* end-around carry */

	/* Decrement TTL and discard if zero. We don't have to check
	 * rxbroadcast here because it's already been checked */
	if (--ip.ttl == 0) {
		/* Send ICMP "Time Exceeded" message */
		icmp_output (&ip, bp, ICMP_TIME_EXCEED, 0, NULLICMP);
		ipInHdrErrors++;
		free_p (bp);
		return -1;
	}
	/* Look up target address in routing table */

	if ((rp = rt_assign (&iface, &ip.dest)) == NULLROUTE) {
		/* No route exists, return unreachable message (we already
		 * know this can't be a broadcast) */

		icmp_output (&ip, bp, ICMP_DEST_UNREACH, ICMP_HOST_UNREACH, NULLICMP);
		free_p (bp);
		ipOutNoRoutes++;
		return -1;
	}

	/* Process broadcast to all interfaces */

	/* For general broadcasting, select the best route/interface to use */
	if (ip.dest.sin_address == 0xffffffffL) {
		trp = rp;

		/* Start from the first route to the "same" broadcast address */
		while (trp->prev && trp->prev->same) {
			trp = trp->prev;
		}

		/* Now search for the interface matching the packet's source address */
		while (!inet_hostmatch (&ip.source, &trp->iface->address[AF_INET])) {
			trp = trp->same;
			if (!trp) {
				break;
			}
		}

		/* If a matching interface address is found, use the associated route */
		if (trp) {
			rp = trp;
			iface = trp->iface;
		}
	}

	/* Found an output route, count it as used */
	rp->uses++;

	/* Identify broadcast to interface rather than send to a gateway */
	if ((ip.dest.sin_address == 0xffffffffL) || inet_hostmatch (&ip.dest, &iface->broadcast[AF_INET])) {
		gateway = ip.dest;
	} else

	/* Find gateway; null gateway in routing table means "send direct" */
	if (rp->gateway.sa_family == AF_NONE)
		gateway = ip.dest;
	else
		gateway = rp->gateway;

	if (strict && inet_hostsame (&gateway, &ip.dest)) {
		/* Strict source routing requires a direct entry
		 * Again, we know this isn't a broadcast */
		icmp_output (&ip, bp, ICMP_DEST_UNREACH, ICMP_ROUTE_FAIL, NULLICMP);
		free_p (bp);
		ipOutNoRoutes++;
		return -1;
	}
	if (ip.length <= iface->mtu) {
		/* Datagram smaller than interface MTU; put header
		 * back on and send normally */
		ret = q_pkt (iface, &gateway, &ip, bp, ckgood);
		return ret;
	}
	/* Fragmentation needed */
	if (ip.flags.df) {
		/* Don't Fragment set; return ICMP message and drop */
		union icmp_args icmp_args;

		icmp_args.mtu = iface->mtu;
		icmp_output (&ip, bp, ICMP_DEST_UNREACH, ICMP_FRAG_NEEDED, &icmp_args);
		free_p (bp);
		ipFragFails++;
		return -1;
	}
	/* Create fragments */
	offset = ip.offset;
	mf_flag = ip.flags.mf;		/* Save original MF flag */
	while (length != 0) {		/* As long as there's data left */
		uint16 fragsize;		/* Size of this fragment's data */
		struct mbuf *f_data;	/* Data portion of fragment */

		/* After the first fragment, should remove those
		 * options that aren't supposed to be copied on fragmentation */
		ip.offset = offset;
		if (length + ip_len <= iface->mtu) {
			/* Last fragment; send all that remains */
			fragsize = length;
			ip.flags.mf = mf_flag;	/* Pass original MF flag */
		} else {
			/* More to come, so send multiple of 8 bytes */
			fragsize = (iface->mtu - ip_len) & 0xfff8;
			ip.flags.mf = 1;
		}
		ip.length = fragsize + ip_len;

		/* Duplicate the fragment */
		dup_p (&f_data, bp, offset, fragsize);
		if (f_data == NULLBUF) {
			free_p (bp);
			ipFragFails++;
			return -1;
		}
		if (q_pkt (iface, &gateway, &ip, f_data, IP_CS_NEW) == -1) {
			/* If q_pkt fails on any fragment, free the original packet and return */
			ipFragFails++;
			free_p (bp);
			return -1;
		}
		ipFragCreates++;
		offset += fragsize;
		length -= fragsize;
    }
    ipFragOKs++;
    free_p (bp);
	return 0;
}
