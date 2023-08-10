
/* ************************************************************************* */
/*
 *	udp.c
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
 *	This file contains the UDP functions.
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

struct mib_entry Udp_mib[] = {
	{"",				{0}},
	{"udpInDatagrams",	{0}},
	{"udpNoPorts",		{0}},
	{"udpInErrors",		{0}},
	{"udpOutDatagrams",	{0}},
};

/* UDP control structures list */
struct udp_cb *Udps = NULLUDP;

ENTRY void
udp_init (void)
{
	Udps = NULLUDP;

	Udp_mib[0].value.integer = 0;
	udpInDatagrams = 0;
	udpNoPorts = 0;
	udpInErrors = 0;
	udpOutDatagrams = 0;
}

/* Process an incoming UDP response */
ENTRY void
udp_icmp (sint31 icsource, sint31 source, sint31 dest, char type, char code, struct mbuf **bpp)
{
	struct udp seg;
	struct sockaddr lsocket;
	register struct udp_cb *up;

	/* Extract the socket info from the returned UDP header fragment
	 * Note that since this is a datagram we sent, the source fields
	 * refer to the local side.
	 */
	ntohudp (&seg, bpp);
	lsocket.sin_port = seg.source;
	lsocket.sin_address = source;

	if ((up = lookup_udp (&lsocket)) == NULLUDP) {
		/* Unknown packet */
		return;
	}

}

/* Create a UDP control block for lsocket, so that we can queue
 * incoming datagrams.
 */
ENTRY struct udp_cb *
open_udp (struct sockaddr *lsocket, void (*r_upcall) (void))
{
	register struct udp_cb *up;

	if ((up = lookup_udp (lsocket)) != NULLUDP) {
		/* Already exists */
		Net_error = CON_EXISTS;
		return NULLUDP;
	}
	up = (struct udp_cb *) callocw (1, sizeof (struct udp_cb));
	up->socket = *lsocket;
	up->r_upcall = (void (*) (struct iface *, struct udp_cb *, int))r_upcall;

	up->next = Udps;
	Udps = up;
	return up;
}

/* Send a UDP datagram */
ENTRY int
send_udp (struct sockaddr *lsocket, struct sockaddr *fsocket, char tos, char ttl, struct mbuf *bp, uint16 length, uint16 id, char df)
{
	struct pseudo_header ph;
	struct udp udp;
	struct sockaddr *laddr;

	if (length != 0 && bp != NULLBUF)
		trim_mbuf (&bp, length);
	else
		length = len_p (bp);

	length += UDPHDR;

	laddr = lsocket;
	if (laddr->sin_address == IPADDR_ANY)
		laddr = locaddr (fsocket);

	udp.source = lsocket->sin_port;
	udp.dest = fsocket->sin_port;
	udp.length = length;

	/* Create IP pseudo-header, compute checksum and send it */
	ph.length = length;
	ph.source = laddr->sin_address;
	ph.dest = fsocket->sin_address;
	ph.protocol = UDP_PTCL;

	bp = htonudp (&udp, bp, &ph);
	udpOutDatagrams++;
	ip_send (laddr, fsocket, UDP_PTCL, tos, ttl, bp, length, id, df);
	return (int) (length - UDPHDR);
}
/* Accept a waiting datagram, if available. Returns length of datagram */
ENTRY int
recv_udp (register struct udp_cb *up, struct sockaddr *fsocket, struct mbuf **bp)
{
	struct sockaddr sp;
	struct mbuf *buf;
	uint16 length;

	if (up == NULLUDP) {
		Net_error = NO_CONN;
		return -1;
	}
	if (up->rcvcnt == 0) {
		Net_error = WOULDBLK;
		return -1;
	}
	buf = dequeue (&up->rcvq);
	up->rcvcnt--;

	/* Strip socket header */
	pullup (&buf, (char *) &sp, SOCKSIZE);

	/* Fill in the user's foreign socket structure, if given */
	if (fsocket != NULLSA) {
		*fsocket = sp;
	}
	/* Hand data to user */
	length = len_p (buf);
	if (bp != NULLBUFP)
		*bp = buf;
	else
		free_p (buf);
	return (int) length;
}
/* Delete a UDP control block */
ENTRY int
del_udp (struct udp_cb *conn)
{
	register struct udp_cb *up;
	struct udp_cb *udplast = NULLUDP;

	for (up = Udps;up != NULLUDP;udplast = up, up = up->next) {
		if (up == conn)
			break;
	}
	if (up == NULLUDP) {
		/* Either conn was NULL or not found on list */
		Net_error = INVALID;
		return -1;
	}

	/* Get rid of all pending packets */
	free_q (&up->rcvq);

	/* Remove from list */
	if (udplast != NULLUDP)
		udplast->next = up->next;
	else
		Udps = up->next;	/* was first on list */

	free ((char *) up);
	return 0;
}
/* Process an incoming UDP datagram */
ENTRY void
udp_input (struct iface *iface, struct ip *ip, struct mbuf *bp, int rxbroadcast)
{
	struct pseudo_header ph;
	struct udp udp;
	struct udp_cb *up;
	struct sockaddr lsocket, fsocket;
	uint16 length;

	if (bp == NULLBUF)
		return;

	/* Create pseudo-header and verify checksum */
	ph.source = ip->source.sin_address;
	ph.dest = ip->dest.sin_address;
	ph.protocol = ip->protocol;
	length = ip->length - IPHDRLEN - ip->optlen;
	ph.length = length;

	/* Peek at header checksum before we extract the header. This
	 * allows us to bypass cksum () if the checksum field was not
	 * set by the sender.
	 */
	udp.checksum = udpcksum (bp);
	if (udp.checksum != 0 && cksum (&ph, bp, length) != 0) {
		/* Checksum non-zero, and wrong */
		udpInErrors++;
		free_p (bp);
		return;
	}
	/* Extract UDP header in host order */
	if (ntohudp (&udp, &bp) != 0) {
		/* Truncated header */
		udpInErrors++;
		free_p (bp);
		return;
	}
	/* If this was a broadcast packet, pretend it was sent to us */
	if (rxbroadcast) {
		lsocket = iface->address[AF_INET];
	} else
		lsocket = ip->dest;

	lsocket.sin_port = udp.dest;
	/* See if there's somebody around to read it */
	if ((up = lookup_udp (&lsocket)) == NULLUDP) {
		/* Nope, return an ICMP message */
		if (!rxbroadcast) {
			bp = htonudp (&udp, bp, &ph);
			icmp_output (ip, bp, ICMP_DEST_UNREACH, ICMP_PORT_UNREACH, NULL);
		}
		udpNoPorts++;
		free_p (bp);
		return;
	}
	/* Create space for the foreign socket info */
	pushdown (&bp, sizeof (fsocket));
	fsocket = ip->source;
	fsocket.sin_port = udp.source;
	memcpy (bp->data, (char *) &fsocket, sizeof (fsocket));

	/* Queue it */
	enqueue (&up->rcvq, bp);
	up->rcvcnt++;
	udpInDatagrams++;
	if (up->r_upcall)
		(*up->r_upcall) (iface, up, up->rcvcnt);
}
/* Look up UDP socket.
 * Return control block pointer or NULLUDP if nonexistant
 * As side effect, move control block to top of list to speed future
 * searches.
 */
LOCAL struct udp_cb *
lookup_udp (struct sockaddr *socket)
{
	register struct udp_cb *up;
	struct udp_cb *uplast = NULLUDP;

	for (up = Udps;up != NULLUDP;uplast = up, up = up->next) {
		if ((up->socket.sin_port == socket->sin_port) &&
		    ((up->socket.sin_address == IPADDR_ANY) ||
		    (inet_hostsame (socket, &up->socket)))) {
			if (uplast != NULLUDP) {
				/* Move to top of list */
				uplast->next = up->next;
				up->next = Udps;
				Udps = up;
			}
			return up;
		}
	}
	return NULLUDP;
}

/* Attempt to reclaim unused space in UDP receive queues */
ENTRY void
udp_garbage (int red)
{
	register struct udp_cb *udp;

	for (udp = Udps;udp != NULLUDP; udp = udp->next) {
		mbuf_crunch (&udp->rcvq);
	}
}
