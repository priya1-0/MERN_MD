
/* ************************************************************************* */
/*
 *	locsock.c
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
 *	Module:		NET
 *
 *	This file contains the functions.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 20:31:57  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#include "system/system.h"
#include "lansend/global.h"

#include "net/local.h"

#include "dev/dev.h"
#include "sys/sys.h"

#include "ip/ip.h"

#include "net/local.h"

ENTRY int
so_los (struct usock *up, int protocol)
{
	up->cb.local = (struct loc *) callocw (1, sizeof (struct loc));
	up->cb.local->peer = up;	/* connect to self */
	up->type = TYPE_LOCAL_STREAM;
	up->cb.local->hiwat = LOCSFLOW;
	return 0;
}
ENTRY int
so_lod (struct usock *up, int protocol)
{
	up->cb.local = (struct loc *) callocw (1, sizeof (struct loc));
	up->cb.local->peer = up;	/* connect to self */
	up->type = TYPE_LOCAL_DGRAM;
	up->cb.local->hiwat = LOCDFLOW;
	return 0;
}
ENTRY int
so_lo_recv (struct usock *up, struct mbuf **bpp, int len, char *from, int *fromlen)
{
	int s;

	while (up->cb.local != NULLLOC && up->cb.local->q == NULLBUF
	  && up->cb.local->peer != NULLUSOCK) {
		if (up->noblock) {
			errno = EWOULDBLOCK;
			return -1;
		} else if ((errno = pwait (up)) != 0) {
			return -1;
		}
	}
	if (up->cb.local == NULLLOC) {
		/* Socket went away */
		errno = EBADF;
		return -1;
	}
	if (up->cb.local->q == NULLBUF &&
	   up->cb.local->peer == NULLUSOCK) {
		errno = ENOTCONN;
		return -1;
	}
	/* For datagram sockets, this will return the
	 * first packet on the queue. For stream sockets,
	 * this will return everything.
	 */
	*bpp = dequeue (&up->cb.local->q);
	if (up->cb.local->q == NULLBUF && (up->cb.local->flags & LOC_SHUTDOWN)) {
		s = up->index;
		close_s (s);
	}
	psignal (up, 0);
	return len_p (*bpp);
}
ENTRY int
so_los_send (struct usock *up, struct mbuf *bp, char *to)
{
	if (up->cb.local->peer == NULLUSOCK) {
		free_p (bp);
		errno = ENOTCONN;
		return -1;
	}
	append (&up->cb.local->peer->cb.local->q, bp);
	psignal (up->cb.local->peer, 0);
	/* If high water mark has been reached, block */
	while (up->cb.local->peer != NULLUSOCK &&
	      len_p (up->cb.local->peer->cb.local->q) >=
	      up->cb.local->peer->cb.local->hiwat) {
		if (up->noblock) {
			errno = EWOULDBLOCK;
			return -1;
		} else if ((errno = pwait (up->cb.local->peer)) != 0) {
			return -1;
		}
	}
	if (up->cb.local->peer == NULLUSOCK) {
		errno = ENOTCONN;
		return -1;
	}
	return 0;
}
ENTRY int
so_lod_send (struct usock *up, struct mbuf *bp, char *to)
{
	if (up->cb.local->peer == NULLUSOCK) {
		free_p (bp);
		errno = ENOTCONN;
		return -1;
	}
	enqueue (&up->cb.local->peer->cb.local->q, bp);
	psignal (up->cb.local->peer, 0);
	/* If high water mark has been reached, block */
	while (up->cb.local->peer != NULLUSOCK &&
	      len_q (up->cb.local->peer->cb.local->q) >=
	      up->cb.local->peer->cb.local->hiwat) {
		if (up->noblock) {
			errno = EWOULDBLOCK;
			return -1;
		} else if ((errno = pwait (up->cb.local->peer)) != 0) {
			return -1;
		}
	}
	if (up->cb.local->peer == NULLUSOCK) {
		errno = ENOTCONN;
		return -1;
	}
	return 0;
}
ENTRY int
so_lod_qlen (struct usock *up, int rtx)
{
	int len;

	switch (rtx) {
	case 0:
		len = len_q (up->cb.local->q);
		break;
	case 1:
		if (up->cb.local->peer != NULLUSOCK)
			len = len_q (up->cb.local->peer->cb.local->q);
		break;
	}
	return len;
}
ENTRY int
so_los_qlen (struct usock *up, int rtx)
{
	int len;

	switch (rtx) {
	case 0:
		len = len_p (up->cb.local->q);
		break;
	case 1:
		if (up->cb.local->peer != NULLUSOCK)
			len = len_p (up->cb.local->peer->cb.local->q);
		break;
	}
	return len;
}
ENTRY int
so_loc_shut (struct usock *up, int how)
{
	int s;

	s = up->index;

	if (up->cb.local->q == NULLBUF)
		close_s (s);
	else
		up->cb.local->flags = LOC_SHUTDOWN;
	return 0;
}
ENTRY int
so_loc_close (struct usock *up)
{
	if (up->cb.local->peer != NULLUSOCK) {
		up->cb.local->peer->cb.local->peer = NULLUSOCK;
		psignal (up->cb.local->peer, 0);
	}
	free_q (&up->cb.local->q);
	free (up->cb.local);
	return 0;
}
ENTRY int
so_loc_stat (struct usock *up)
{
	int s;

	s = up->index;

	printf("Inqlen: %d packets\n",socklen(s,0));
	printf("Outqlen: %d packets\n",socklen(s,1));
	return 0;
}
