
/* ************************************************************************* */
/*
 *	icmphdr.c
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
 *	This file contains the functions.
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

/* Generate ICMP header in network byte order, link data, compute checksum */
ENTRY struct mbuf *
htonicmp (struct icmp *icmp, struct mbuf *bp)
{
	register char *cp;
	uint16 checksum;

	pushdown (&bp, ICMPLEN);
	cp = bp->data;

	*cp++= uchar(icmp->type);
	*cp++= uchar(icmp->code);
	cp = put16(cp,0);		/* Clear checksum */
	switch (icmp->type) {
	case ICMP_DEST_UNREACH:
		if (icmp->code == ICMP_FRAG_NEEDED) {
			/* Deering/Mogul max MTU indication */
			cp = put16 (cp, 0);
			cp = put16 (cp, icmp->args.mtu);
		} else
			cp = put32 (cp, 0L);
		break;
	case ICMP_PARAM_PROB:
		*cp++= icmp->args.pointer;
		*cp++= 0;
		cp = put16 (cp, 0);
		break;
	case ICMP_REDIRECT:
		cp = put32 (cp, icmp->args.address);
		break;
	case ICMP_ECHO:
	case ICMP_ECHO_REPLY:
	case ICMP_TIMESTAMP:
	case ICMP_TIME_REPLY:
	case ICMP_INFO_RQST:
	case ICMP_INFO_REPLY:
		cp = put16 (cp, icmp->args.echo.id);
		cp = put16 (cp, icmp->args.echo.seq);
		break;
	default:
		cp = put32 (cp, 0L);
		break;
	}
	/* Compute checksum, and stash result */
	checksum = cksum (NULLHEADER, bp, len_p (bp));
	cp = &bp->data[2];
	cp = put16 (cp, checksum);

	return bp;
}
/* Pull off ICMP header */
ENTRY int
ntohicmp (struct icmp *icmp, struct mbuf **bpp)
{
	char icmpbuf[8];

	if (icmp == (struct icmp *) NULL)
		return -1;
	if (pullup (bpp, icmpbuf, 8) != 8)
		return -1;
	icmp->type = uchar(icmpbuf[0]);
	icmp->code = uchar(icmpbuf[1]);
	switch (icmp->type) {
	case ICMP_DEST_UNREACH:
		/* Retrieve Deering/Mogul MTU value */
		if (icmp->code == ICMP_FRAG_NEEDED)
			icmp->args.mtu = get16 (&icmpbuf[6]);
		break;
	case ICMP_PARAM_PROB:
		icmp->args.pointer = uchar(icmpbuf[4]);
		break;
	case ICMP_REDIRECT:
		icmp->args.address = get32 (&icmpbuf[4]);
		break;
	case ICMP_ECHO:
	case ICMP_ECHO_REPLY:
	case ICMP_TIMESTAMP:
	case ICMP_TIME_REPLY:
	case ICMP_INFO_RQST:
	case ICMP_INFO_REPLY:
		icmp->args.echo.id = get16 (&icmpbuf[4]);
		icmp->args.echo.seq = get16 (&icmpbuf[6]);
		break;
	}
	return 0;
}
