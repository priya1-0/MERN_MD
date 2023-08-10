
/* ************************************************************************* */
/*
 *	udphdr.c
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
 *	This file contains the UDP header conversion functions.
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

/* Convert UDP header in internal format to an mbuf in external format */
ENTRY struct mbuf *
htonudp (struct udp *udp, struct mbuf *bp, struct pseudo_header *ph)
{
	register char *cp;
	uint16 checksum;

	/* Allocate UDP protocol header and fill it in */
	pushdown (&bp, UDPHDR);
	cp = bp->data;
	cp = put16(cp,udp->source);	/* Source port */
	cp = put16(cp,udp->dest);	/* Destination port */
	cp = put16(cp,udp->length);	/* Length */
	*cp++ = 0;			/* Clear checksum */
	*cp--= 0;

	/* All zeros and all ones is equivalent in one's complement arithmetic;
	 * the spec requires us to change zeros into ones to distinguish an
 	 * all - zero checksum from no checksum at all
	 */
	if ((checksum = cksum (ph, bp, ph->length)) == 0)
		checksum = 0xffff;
	put16 (cp, checksum);

	return bp;
}
/* Convert UDP header in mbuf to internal structure */
ENTRY int
ntohudp (struct udp *udp, struct mbuf **bpp)
{
	char udpbuf[UDPHDR];

	if (pullup (bpp, udpbuf, UDPHDR) != UDPHDR)
		return -1;
	udp->source = get16 (&udpbuf[0]);
	udp->dest = get16 (&udpbuf[2]);
	udp->length = get16 (&udpbuf[4]);
	udp->checksum = get16 (&udpbuf[6]);
	return 0;
}
/* Extract UDP checksum value from a network-format header without
 * disturbing the header
 */
ENTRY uint16
udpcksum (struct mbuf *bp)
{
	struct mbuf *dup;
	if (dup_p (&dup, bp, 6, 2) != 2)
		return 0;
	return pull16 (&dup);
}
