
/* ************************************************************************* */
/*
 *	tcptimer.c
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
 *	This file contains the TCP timeout functions.
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

/* Timer timeout */
ENTRY void
tcp_timeout (void *p)
{
	register struct tcb *tcb;

	tcb = (struct tcb *) p;
	if (tcb == NULLTCB)
		return;

	/* Make sure the timer has stopped (we might have been kicked) */
	stop_timer (&tcb->timer);

	switch (tcb->state) {
	case TCP_TIME_WAIT:	/* 2MSL timer has expired */
		close_self (tcb, NORMAL);
		break;
	case TCP_FINWAIT1:
		if (tcb->backoff >= 4) {
			close_self (tcb, NORMAL);
			break;
		}
		/* Fall through retransmission code */
	default:		/* Retransmission timer has expired */
		tcb->flags.retran = 1;	/* Indicate > 1  transmission */
		tcb->backoff++;
		tcb->snd.ptr = tcb->snd.una;
		/* Reduce slowstart threshold to half current window */
		tcb->ssthresh = tcb->cwind / 2;
		tcb->ssthresh = max (tcb->ssthresh, tcb->mss);
		/* Shrink congestion window to 1 packet */
		tcb->cwind = tcb->mss;
		tcp_output (tcb);
	}
}
/* Backoff function - the subject of much research */
ENTRY sint31
backoff (int n)
{
	if (n > 31)
		n = 31;	/* Prevent truncation to zero */

	return 1L << n;	/* Binary exponential back off */
}
