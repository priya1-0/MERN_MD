
/* ************************************************************************* */
/*
 *	tcphdr.c
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
 *	This file contains the TCP header conversion functions.
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

/* Convert TCP header in host format into mbuf ready for transmission,
 * link in data (if any) . If ph != NULL, compute checksum, otherwise
 * take checksum from tcph->checksum
 */
ENTRY struct mbuf *
htontcp (register struct tcp *tcph, struct mbuf *bp, struct pseudo_header *ph)
{
	uint16 hdrlen;
	register char *cp;

	hdrlen = TCPLEN;
	if (tcph->optlen > 0 && tcph->optlen <= TCP_MAXOPT) {
		hdrlen += tcph->optlen;
	} else if (tcph->mss != 0) {
		hdrlen += MSS_LENGTH;
	}
	pushdown (&bp, hdrlen);
	cp = bp->data;
	cp = put16 (cp, tcph->source);
	cp = put16 (cp, tcph->dest);
	cp = put32 (cp, tcph->seq);
	cp = put32 (cp, tcph->ack);
	*cp++ = hdrlen << 2;	/* Offset field */
	*cp = 0;
	if (tcph->flags.cwr)
		*cp |= TCP_FLAG__CWR;
	if (tcph->flags.ece)
		*cp |= TCP_FLAG__ECE;
	if (tcph->flags.urg)
		*cp |= TCP_FLAG__URG;
	if (tcph->flags.ack)
		*cp |= TCP_FLAG__ACK;
	if (tcph->flags.psh)
		*cp |= TCP_FLAG__PSH;
	if (tcph->flags.rst)
		*cp |= TCP_FLAG__RST;
	if (tcph->flags.syn)
		*cp |= TCP_FLAG__SYN;
	if (tcph->flags.fin)
		*cp |= TCP_FLAG__FIN;
	cp++;
	cp = put16 (cp, tcph->wnd);
	if (ph == NULLHEADER) {
		/* Use user-supplied checksum */
		cp = put16 (cp, tcph->checksum);
	} else {
		/* Zero out checksum field for later recalculation */
		*cp++= 0;
		*cp++= 0;
	}
	cp = put16 (cp, tcph->up);

	/* Write options, if any */
	if (hdrlen > TCPLEN) {
		if (tcph->optlen > 0) {
			memcpy (cp, tcph->options, tcph->optlen);
		} else if (tcph->mss != 0) {
			*cp++= MSS_KIND;
			*cp++= MSS_LENGTH;
			cp = put16 (cp, tcph->mss);
		}
	}
	/* Recompute checksum, if requested */
	if (ph != NULLHEADER)
		put16 (&bp->data[16], cksum (ph, bp, ph->length));
	return bp;
}
/* Pull TCP header off mbuf */
ENTRY int
ntohtcp (register struct tcp *tcph, struct mbuf **bpp)
{
	int hdrlen, i;
	int kind, kindlen;
	register int flags;
	char hdrbuf[TCPLEN], *cp;

	i = pullup (bpp, hdrbuf, TCPLEN);
	/* Note that the results will be garbage if the header is too short.
	 * We don't check for this because returned ICMP messages will be
	 * truncated, and we at least want to get the port numbers.
	 */
	tcph->source = get16 (&hdrbuf[0]);
	tcph->dest = get16 (&hdrbuf[2]);
	tcph->seq = get32 (&hdrbuf[4]);
	tcph->ack = get32 (&hdrbuf[8]);
	flags = hdrbuf[13];
	tcph->flags.cwr = flags & TCP_FLAG__CWR;
	tcph->flags.ece = flags & TCP_FLAG__ECE;
	tcph->flags.urg = flags & TCP_FLAG__URG;
	tcph->flags.ack = flags & TCP_FLAG__ACK;
	tcph->flags.psh = flags & TCP_FLAG__PSH;
	tcph->flags.rst = flags & TCP_FLAG__RST;
	tcph->flags.syn = flags & TCP_FLAG__SYN;
	tcph->flags.fin = flags & TCP_FLAG__FIN;
	tcph->wnd = get16 (&hdrbuf[14]);
	tcph->checksum = get16 (&hdrbuf[16]);
	tcph->up = get16 (&hdrbuf[18]);
	tcph->mss = 0;

	/* Check for option field.
	 */
	hdrlen = (hdrbuf[12] & 0xf0) >> 2;
	if (i < TCPLEN || hdrlen < TCPLEN) {
		tcph->optlen = 0;
		return -1;	/* Header smaller than legal minimum */
	}

	if ((tcph->optlen = hdrlen - TCPLEN) == 0)
		return hdrlen;	/* No options, all done */

	if (pullup (bpp, tcph->options, tcph->optlen) < tcph->optlen) {
		/* Remainder too short for options length specified */
		return -1;
	}

	/* Process options */
	for (cp = tcph->options, i = tcph->optlen; i > 0;) {
		kind = *cp++;
		/* Process single-byte options */
		switch (kind) {
		case EOL_KIND:
			i--;
			cp++;
			return hdrlen;	/* End of options list */
		case NOOP_KIND:
			i--;
			cp++;
			continue;	/* Go look for next option */
		}
		/* All other options have a length field */
		kindlen = uchar (*cp++);

		/* Process valid multi-byte options */
		switch (kind) {
		case MSS_KIND:
			if (kindlen == MSS_LENGTH) {
				tcph->mss = get16 (cp);
			}
			break;
		}
		kindlen = max(2,kindlen); /* Enforce legal minimum */
		i -= kindlen;
		cp += kindlen - 2;
	}
	return hdrlen;
}
