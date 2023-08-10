
/* ************************************************************************* */
/*
 *	iphdr.c
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
 *	This file contains the IP header conversion functions.
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

/* Convert IP header in host format to network mbuf
 * If cflag != 0, take checksum from structure,
 * otherwise compute it automatically.
 */
ENTRY struct mbuf *
htonip (register struct ip *ip, struct mbuf *bp, int cflag)
{
	uint16 hdr_len;
	register char *cp;
	uint16 fl_offs;

	hdr_len = IPHDRLEN + ip->optlen;
	if (hdr_len > IPHDRLEN + IP_MAXOPT)
		hdr_len = IPHDRLEN + IP_MAXOPT;

	pushdown (&bp, hdr_len);
	cp = bp->data;

	*cp++= (ip->version << 4) | (hdr_len >> 2);
	*cp++= ip->tos;
	cp = put16 (cp, ip->length);
	cp = put16 (cp, ip->id);
	fl_offs = ip->offset >> 3;
	if (ip->flags.congest)
		fl_offs |= IP_FLAG__CE;
	if (ip->flags.df)
		fl_offs |= IP_FLAG__DF;
	if (ip->flags.mf)
		fl_offs |= IP_FLAG__MF;

	cp = put16 (cp, fl_offs);
	*cp++= ip->ttl;
	*cp++= ip->protocol;
	if (cflag) {
		/* Use checksum from host structure */
		cp = put16 (cp, ip->checksum);
	} else {
		/* Clear checksum for later recalculation */
		*cp++= 0;
		*cp++= 0;
	}
	cp = put32 (cp, ip->source.sin_address);
	cp = put32 (cp, ip->dest.sin_address);
	if (ip->optlen != 0)
		memcpy (cp, ip->options, min (ip->optlen, IP_MAXOPT));

	/* If requested, recompute checksum and insert into header */
	if (!cflag)
		put16 (&bp->data[10], cksum (NULLHEADER, bp, hdr_len));

	return bp;
}

/* Extract an IP header from mbuf */
ENTRY int
ntohip (register struct ip *ip, struct mbuf **bpp)
{
	int ihl;
	uint16 fl_offs;
	char ipbuf[IPHDRLEN];

	if (pullup (bpp, ipbuf, IPHDRLEN) != IPHDRLEN)
		return -1;

	ip->version = (ipbuf[0] >> 4) & 0xf;
	ip->tos = uchar(ipbuf[1]);
	ip->length = get16 (&ipbuf[2]);
	ip->id = get16 (&ipbuf[4]);
	fl_offs = get16 (&ipbuf[6]);
	ip->offset = (fl_offs & 0x1fff) << 3;
	ip->flags.mf = (fl_offs & IP_FLAG__MF) ? 1 : 0;
	ip->flags.df = (fl_offs & IP_FLAG__DF) ? 1 : 0;
	ip->flags.congest = (fl_offs & IP_FLAG__CE) ? 1 : 0;
	ip->ttl = uchar(ipbuf[8]);
	ip->protocol = uchar(ipbuf[9]);
	ip->checksum = get16 (&ipbuf[10]);
	ip->source.sa_family = AF_INET;
	ip->source.sin_address = get32 (&ipbuf[12]);
	ip->dest.sa_family = AF_INET;
	ip->dest.sin_address = get32 (&ipbuf[16]);

	ihl = (ipbuf[0] & 0xf) << 2;
	if (ihl < IPHDRLEN) {
		/* Bogus packet; header is too short */
		ip->optlen = 0;
		return -1;
	}
	if ((ip->optlen = ihl - IPHDRLEN) != 0) {
		if (pullup (bpp, (char *) ip->options, ip->optlen) < ip->optlen)
			return -1;
	}
	return ihl;
}
/* Perform end-around-carry adjustment */
ENTRY uint16
eac (register sint31 sum)
{
	register uint16 csum;

	while ((csum = sum >> 16) != 0)
		sum = csum + (sum & 0xffffL);
	return (uint16) (sum & 0xffffl);	/* Chops to 16 bits */
}

/* Checksum a mbuf chain, with optional pseudo-header */
ENTRY uint16
cksum (struct pseudo_header *ph, struct mbuf *m, uint16 len)
{
	register uint16 cnt, total;
	register sint31 sum, csum;
	register char *up;
	int swap = 0;

	sum = 0l;

	/* Sum pseudo-header, if present */
	if (ph != NULLHEADER) {
		sum = hiword (ph->source);
		sum += loword (ph->source);
		sum += hiword (ph->dest);
		sum += loword (ph->dest);
		sum += uchar (ph->protocol);
		sum += ph->length;
	}
	/* Now do each mbuf on the chain */
	for (total = 0; m != NULLBUF && total < len; m = m->next) {
		cnt = min (m->cnt, len - total);
		up = (char *) m->data;
		csum = 0;

		while (cnt) {
			if (swap)
				csum += uchar (*up++);
			else
				csum += (uint16) (uchar (*up++) << 8);
			cnt--;
			swap = ! swap;
		}
		sum += csum;
		total += m->cnt;
	}
	/* Do final end-around carry, complement and return */
	return (uint16) (~eac (sum) & 0xffff);
}
