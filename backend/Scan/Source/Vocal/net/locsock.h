
/* ************************************************************************* */
/*
 *	locsock.h
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
 *	This file contains the global declarations for the NET module.
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

#ifndef	_NET_LOCSOCK_H
#define	_NET_LOCSOCK_H

struct loc {
	struct usock *peer;
	struct mbuf *q;
	int hiwat;		/* Flow control point */
	int flags;
#define	LOC_SHUTDOWN	1
};

#define	NULLLOC	(struct loc *)0
#define	LOCDFLOW	5	/* dgram socket flow-control point, packets */
#define	LOCSFLOW	2048	/* stream socket flow control point, bytes */

#endif /* _NET_LOCSOCK_H */
