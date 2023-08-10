
/* ************************************************************************* */
/*
 *	ip.c
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
 *	This file contains the upper half of IP, consisting of send / receive
 *	primitives, including fragment reassembly, for higher level protocols.
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

struct mib_entry Ip_mib[21] = {
	{"",					{0}},
	{"ipForwarding",		{1}},
	{"ipDefaultTTL",		{MAXTTL}},
	{"ipInReceives",		{0}},
	{"ipInHdrErrors",		{0}},
	{"ipInAddrErrors",		{0}},
	{"ipForwDatagrams",		{0}},
	{"ipInUnknownProtos",	{0}},
	{"ipInDiscards",		{0}},
	{"ipInDelivers",		{0}},
	{"ipOutRequests",		{0}},
	{"ipOutDiscards",		{0}},
	{"ipOutNoRoutes",		{0}},
	{"ipReasmTimeout",		{TLB}},
	{"ipReasmReqds",		{0}},
	{"ipReasmOKs",			{0}},
	{"ipReasmFails",		{0}},
	{"ipFragOKs",			{0}},
	{"ipFragFails",			{0}},
	{"ipFragCreates",		{0}},
	{"ipRoutingDiscards",	{0}},
};

struct reasm *Reasmq = NULLREASM;
struct raw_ip *Raw_ip = NULLRIP;

static uint16 ip_id = 1;

ENTRY void
ip_init (void)
{
	Ip_mib[0].value.integer = 0;
	Ip_mib[1].value.integer = 1;
	Ip_mib[2].value.integer = MAXTTL;
	Ip_mib[3].value.integer = 0;
	Ip_mib[4].value.integer = 0;
	Ip_mib[5].value.integer = 0;
	Ip_mib[6].value.integer = 0;
	Ip_mib[7].value.integer = 0;
	Ip_mib[8].value.integer = 0;
	Ip_mib[9].value.integer = 0;
	Ip_mib[10].value.integer = 0;
	Ip_mib[11].value.integer = 0;
	Ip_mib[12].value.integer = 0;
	Ip_mib[13].value.integer = TLB;
	Ip_mib[14].value.integer = 0;
	Ip_mib[15].value.integer = 0;
	Ip_mib[16].value.integer = 0;
	Ip_mib[17].value.integer = 0;
	Ip_mib[18].value.integer = 0;
	Ip_mib[19].value.integer = 0;
	Ip_mib[20].value.integer = 0;

	Reasmq = NULLREASM;
	Raw_ip = NULLRIP;

	ip_id = 1;
}

/* ************************************************************************* */
/*
 *	Entry Routine: ip_module_reset
 *
 *	This routine sets the variables of the ip module to safe values.
 *
 *	Parameters:
 *		none
 *
 *	Returns:
 *		none
 */

ENTRY void
ip_module_reset (void)
{

	domain_init ();

	icmp_init ();
	icmpcmd_init ();
	ipcmd_init ();

	ip_init ();

	tcpsock_init ();
	tcpsubr_init ();
	tcpuser_init ();

	udp_init ();
	udpsock_init ();
}

/* ************************************************************************* */
/*
 *	Entry Routine: ip_startup
 *
 *	This starts up the ip module.
 *
 *	Parameters:
 *		none
 *
 *	Returns:
 *		none
 */
ENTRY void
ip_startup (void)
{

}

#define	INSERT	0
#define	APPEND	1
#define	PREPEND	2

/* Send an IP datagram. Modeled after the example interface on p 32 of
 * RFC 791
 */
ENTRY int
ip_send (struct sockaddr *source, struct sockaddr *dest, char protocol, char tos, char ttl, struct mbuf *bp, uint16 length, uint16 id, uint16 df)
{
	struct mbuf *tbp;
	struct iface *ifp = NULLIF;
	struct ip ip;			/* IP header */
	static uint16 id_cntr = 0;	/* Datagram serial number */
	int ret;

	ipOutRequests++;

	if (source->sin_address == IPADDR_ANY)
		source = locaddr (dest);
	if (length == 0 && bp != NULLBUF)
		length = len_p (bp);
	if (id == 0)
		id = id_cntr++;
	if (ttl == 0) {
		ttl = ipDefaultTTL;
	}

	/* Fill in IP header */
	ip.version = IPVERSION;
	ip.tos = tos;
	ip.length = IPHDRLEN + length;

	/* Generate a unique packet ID in case the packet ID is specified as zero */
	if (!id) {
		id = ip_id++;
		if (!ip_id) {
			ip_id++;
		}
	}
	ip.id = id;

	ip.offset = 0;
	ip.flags.mf = 0;
	ip.flags.df = df;
	ip.flags.congest = 0;
	ip.ttl = ttl;
	ip.protocol = protocol;
	ip.source = *source;
	ip.dest = *dest;
	ip.optlen = 0;
	/* DLW Convert header to network form. */
	if ((tbp = htonip (&ip, bp, IP_CS_NEW)) == NULLBUF) {
		free_p (bp);
		return -1;
	}
	if (ismyaddr (&ip.dest)) {
		/* Pretend it has been sent by the loopback interface before
		 * it appears in the receive queue
		 */
		ifp = Loopback;
		Loopback->ipsndcnt++;
		Loopback->rawsndcnt++;
		Loopback->lastsent = secclock ();
	}
	tbp->b_type = PT_IP;
	ret = net_route (ifp, tbp);
	return ret;
}

/* Reassemble incoming IP fragments and dispatch completed datagrams
 * to the proper transport module
 */
ENTRY void
ip_recv (struct iface *iface, struct ip *ip, struct mbuf *bp, int rxbroadcast)
{
	/* Function to call with completed datagram */
	register struct raw_ip *rp;
	struct mbuf *bp1, *tbp;
	int rxcnt = 0;
	register const struct iplink *ipp;

	/* If we have a complete packet, call the next layer
	 * to handle the result. Note that fraghandle passes back
	 * a length field that does NOT include the IP header
	 */
	if ((bp = fraghandle (ip, bp)) == NULLBUF) {
		return;		/* Not done yet */
	}

	ipInDelivers++;

	for (rp = Raw_ip;rp != NULLRIP;rp = rp->next) {
		if (rp->protocol != ip->protocol)
			continue;
		rxcnt++;
		/* Duplicate the data portion, and put the header back on */
		dup_p (&bp1, bp, 0, len_p (bp));
		if (bp1 != NULLBUF && (tbp = htonip (ip, bp1, IP_CS_OLD)) != NULLBUF) {
			enqueue (&rp->rcvq, tbp);
			if (rp->r_upcall != NULLVFP)
				(*rp->r_upcall) (rp);
		} else {
			free_p (bp1);
		}
	}
	/* Look it up in the transport protocol table */
	for (ipp = Iplink;ipp->funct != NULL;ipp++) {
		if (ipp->proto == ip->protocol)
			break;
	}
	if (ipp->funct != NULL) {
		/* Found, call transport protocol */
		(*ipp->funct) (iface, ip, bp, rxbroadcast);
	} else {
		/* Not found */
		if (rxcnt == 0) {
			/* Send an ICMP Protocol Unknown response... */
			ipInUnknownProtos++;
			/* ...unless it's a broadcast */
			if (!rxbroadcast) {
				icmp_output (ip, bp, ICMP_DEST_UNREACH, ICMP_PROT_UNREACH, NULLICMP);
			}
		}
		free_p (bp);
	}
}

/* Process IP datagram fragments
 * If datagram is complete, return it with ip->length containing the data
 * length (MINUS header); otherwise return NULLBUF
 */
LOCAL struct mbuf *
fraghandle (struct ip *ip, struct mbuf *bp)
{
	register struct reasm *rp; /* Pointer to reassembly descriptor */
	struct frag *lastfrag, *nextfrag, *tfp;
	struct mbuf *tbp;
	uint16 i;
	uint16 last;		/* Index of first byte beyond fragment */

	last = ip->offset + ip->length - (IPHDRLEN + ip->optlen);

	rp = lookup_reasm (ip);
	if (ip->offset == 0 && ! ip->flags.mf) {
		/* Complete datagram received. Discard any earlier fragments */
		if (rp != NULLREASM) {
			free_reasm (rp);
			ipReasmOKs++;
		}
		return bp;
	}
	ipReasmReqds++;
	if (rp == NULLREASM) {
		/* First fragment; create new reassembly descriptor */
		if ((rp = creat_reasm (ip)) == NULLREASM) {
			/* No space for descriptor, drop fragment */
			ipReasmFails++;
			free_p (bp);
			return NULLBUF;
		}
	}
	/* Keep restarting timer as long as we keep getting fragments */
	stop_timer (&rp->timer);
	start_timer (&rp->timer);

	/* If this is the last fragment, we now know how long the
	 * entire datagram is; record it
	 */
	if (!ip->flags.mf)
		rp->length = last;

	/* Set nextfrag to the first fragment which begins after us,
	 * and lastfrag to the last fragment which begins before us
	 */
	lastfrag = NULLFRAG;
	for (nextfrag = rp->fraglist;nextfrag != NULLFRAG;nextfrag = nextfrag->next) {
		if (nextfrag->offset > ip->offset)
			break;
		lastfrag = nextfrag;
	}
	/* Check for overlap with preceeding fragment */
	if (lastfrag != NULLFRAG  && ip->offset < lastfrag->last) {
		/* Strip overlap from new fragment */
		i = lastfrag->last - ip->offset;
		pullup (&bp, NULLCHAR, i);
		if (bp == NULLBUF)
			return NULLBUF;	/* Nothing left */
		ip->offset += i;
	}
	/* Look for overlap with succeeding segments */
	for (; nextfrag != NULLFRAG; nextfrag = tfp) {
		tfp = nextfrag->next;	/* save in case we delete fp */

		if (nextfrag->offset >= last)
			break;	/* Past our end */
		/* Trim the front of this entry; if nothing is
		 * left, remove it.
		 */
		i = last - nextfrag->offset;
		pullup (&nextfrag->buf, NULLCHAR, i);
		if (nextfrag->buf == NULLBUF) {
			/* superseded; delete from list */
			if (nextfrag->prev != NULLFRAG)
				nextfrag->prev->next = nextfrag->next;
			else
				rp->fraglist = nextfrag->next;
			if (tfp->next != NULLFRAG)
				nextfrag->next->prev = nextfrag->prev;
			freefrag (nextfrag);
		} else
			nextfrag->offset = last;
	}
	/* Lastfrag now points, as before, to the fragment before us;
	 * nextfrag points at the next fragment. Check to see if we can
	 * join to either or both fragments.
	 */
	i = INSERT;
	if (lastfrag != NULLFRAG && lastfrag->last == ip->offset)
		i |= APPEND;
	if (nextfrag != NULLFRAG && nextfrag->offset == last)
		i |= PREPEND;
	switch (i) {
	case INSERT:	/* Insert new desc between lastfrag and nextfrag */
		tfp = newfrag (ip->offset, last, bp);
		tfp->prev = lastfrag;
		tfp->next = nextfrag;
		if (lastfrag != NULLFRAG)
			lastfrag->next = tfp;	/* Middle of list */
		else
			rp->fraglist = tfp;	/* First on list */
		if (nextfrag != NULLFRAG)
			nextfrag->prev = tfp;
		break;
	case APPEND:	/* Append to lastfrag */
		append (&lastfrag->buf, bp);
		lastfrag->last = last;	/* Extend forward */
		break;
	case PREPEND:	/* Prepend to nextfrag */
		tbp = nextfrag->buf;
		nextfrag->buf = bp;
		append (&nextfrag->buf, tbp);
		nextfrag->offset = ip->offset;	/* Extend backward */
		break;
	case (APPEND | PREPEND) :
		/* Consolidate by appending this fragment and nextfrag
		 * to lastfrag and removing the nextfrag descriptor
		 */
		append (&lastfrag->buf, bp);
		append (&lastfrag->buf, nextfrag->buf);
		nextfrag->buf = NULLBUF;
		lastfrag->last = nextfrag->last;

		/* Finally unlink and delete the now unneeded nextfrag */
		lastfrag->next = nextfrag->next;
		if (nextfrag->next != NULLFRAG)
			nextfrag->next->prev = lastfrag;
		freefrag (nextfrag);
		break;
	}
	if (rp->fraglist->offset == 0 && rp->fraglist->next == NULLFRAG
		&& rp->length != 0) {
		/* We've gotten a complete datagram, so extract it from the
		 * reassembly buffer and pass it on.
		 */
		bp = rp->fraglist->buf;
		rp->fraglist->buf = NULLBUF;
		/* Tell IP the entire length */
		ip->length = rp->length + (IPHDRLEN + ip->optlen);
		free_reasm (rp);
		ipReasmOKs++;
		return bp;
	} else {
		return NULLBUF;
	}
}
/* Arrange for receipt of raw IP datagrams */
ENTRY struct raw_ip *
raw_ip (int protocol, void (*r_upcall) (void))
{
	register struct raw_ip *rp;

	rp = (struct raw_ip *) callocw (1, sizeof (struct raw_ip));
	rp->protocol = protocol;
	rp->r_upcall = (void (*) (struct raw_ip *))r_upcall;
	rp->next = Raw_ip;
	Raw_ip = rp;
	return rp;
}
/* Free a raw IP descriptor */
ENTRY void
del_ip (struct raw_ip *rpp)
{
	struct raw_ip *rplast = NULLRIP;
	register struct raw_ip *rp;

	/* Do sanity check on arg */
	for (rp = Raw_ip;rp != NULLRIP;rplast = rp, rp = rp->next)
		if (rp == rpp)
			break;
	if (rp == NULLRIP)
		return;	/* Doesn't exist */

	/* Unlink */
	if (rplast != NULLRIP)
		rplast->next = rp->next;
	else
		Raw_ip = rp->next;
	/* Free resources */
	free_q (&rp->rcvq);
	free ((char *) rp);
}

LOCAL struct reasm *
lookup_reasm (struct ip *ip)
{
	register struct reasm *rp;
	struct reasm *rplast = NULLREASM;

	for (rp = Reasmq;rp != NULLREASM;rplast = rp, rp = rp->next) {
		if (ip->id == rp->id && inet_hostsame (& (ip->source), & (rp->source))
		 && inet_hostsame (& (ip->dest), & (rp->dest)) && ip->protocol == rp->protocol) {
			if (rplast != NULLREASM) {
				/* Move to top of list for speed */
				rplast->next = rp->next;
				rp->next = Reasmq;
				Reasmq = rp;
			}
			return rp;
		}

	}
	return NULLREASM;
}
/* Create a reassembly descriptor,
 * put at head of reassembly list
 */
LOCAL struct reasm *
creat_reasm (register struct ip *ip)
{
	register struct reasm *rp;

	if ((rp = (struct reasm *) calloc (1, sizeof (struct reasm))) == NULLREASM)
		return rp;	/* No space for descriptor */
	rp->source = ip->source;
	rp->dest = ip->dest;
	rp->id = ip->id;
	rp->protocol = ip->protocol;
	set_timer (&rp->timer, ipReasmTimeout * 1000L);
	rp->timer.func = ip_timeout;
	rp->timer.arg = rp;

	rp->next = Reasmq;
	Reasmq = rp;
	return rp;
}

/* Free all resources associated with a reassembly descriptor */
LOCAL void
free_reasm (struct reasm *r)
{
	register struct reasm *rp;
	struct reasm *rplast = NULLREASM;
	register struct frag *fp;

	for (rp = Reasmq;rp != NULLREASM;rplast = rp, rp = rp->next)
		if (r == rp)
			break;
	if (rp == NULLREASM)
		return;	/* Not on list */

	stop_timer (&rp->timer);
	/* Remove from list of reassembly descriptors */
	if (rplast != NULLREASM)
		rplast->next = rp->next;
	else
		Reasmq = rp->next;

	/* Free any fragments on list, starting at beginning */
	while ((fp = rp->fraglist) != NULLFRAG) {
		rp->fraglist = fp->next;
		free_p (fp->buf);
		free ((char *) fp);
	}
	free ((char *) rp);
}

/* Handle reassembly timeouts by deleting all reassembly resources */
LOCAL void
ip_timeout (void *arg)
{
	register struct reasm *rp;

	rp = (struct reasm *) arg;
	free_reasm (rp);
	ipReasmFails++;
}
/* Create a fragment */
LOCAL struct frag *
newfrag (uint16 offset, uint16 last, struct mbuf *bp)
{
	struct frag *fp;

	if ((fp = (struct frag *) calloc (1, sizeof (struct frag))) == NULLFRAG) {
		/* Drop fragment */
		free_p (bp);
		return NULLFRAG;
	}
	fp->buf = bp;
	fp->offset = offset;
	fp->last = last;
	return fp;
}
/* Delete a fragment, return next one on queue */
LOCAL void
freefrag (struct frag *fp)
{
	free_p (fp->buf);
	free ((char *) fp);
}

/* In red alert mode, blow away the whole reassembly queue. Otherwise crunch
 * each fragment on each reassembly descriptor
 */
ENTRY void
ip_garbage (int red)
{
	struct reasm *rp, *rp1;
	struct frag *fp;
	struct raw_ip *rwp;
	struct iface *ifp;

	/* Run through the reassembly queue */
	for (rp = Reasmq;rp != NULLREASM;rp = rp1) {
		rp1 = rp->next;
		if (red) {
			free_reasm (rp);
		} else {
			for (fp = rp->fraglist;fp != NULLFRAG;fp = fp->next) {
				mbuf_crunch (&fp->buf);
			}
		}
	}
	/* Run through the raw IP queue */
	for (rwp = Raw_ip;rwp != NULLRIP;rwp = rwp->next)
		mbuf_crunch (&rwp->rcvq);
	/* In red mode, drop one packet on each interface output queue */
	if (!red)
		return;
	for (ifp = Ifaces;ifp != NULLIF;ifp = ifp->next) {
		rdrop (ifp);
	}
}
/* Execute random drop algorithm on an interface's output queue */
LOCAL void
rdrop (struct iface *ifp)
{
	struct mbuf *bp, *bplast;
	int i;

	i = len_q (ifp->outq);
	if (i == 0)
		return;	/* Queue is empty */

	i = generic_rand32() % i;	/* Select condemned party */
	/* Search for i-th message on queue */
	bplast = NULLBUF;
	for (bp = ifp->outq;bp != NULLBUF && i > 0;i--, bplast = bp, bp = bp->qnext)
;
	/* Now remove and free it */
	if (bplast != NULLBUF)
		bplast->qnext = bp->qnext;
	else
		ifp->outq = bp->qnext;	/* First on list */
	free_p (bp);
}
