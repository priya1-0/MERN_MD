
/* ************************************************************************* */
/*
 *	sockutil.c
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
 *	This file contains the lower level socket functions.
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

/* Return ASCII string giving reason for connection closing */
ENTRY char *
sockerr (int s)
{
	register struct usock *up;
	struct socklink *sp;

	if ((up = itop (s)) == NULLUSOCK) {
		errno = EBADF;
		return (char *) Badsocket;
	}
	sp = up->sp;
	if (sp->error != NULL) {
		return sp->error[(int) up->errcodes[0]];
	} else {
		errno = EOPNOTSUPP;	/* not yet, anyway */
		return NULLCHAR;
	}
}
/* Get state of protocol. Valid only for connection-oriented sockets. */
ENTRY char *
sockstate (int s)
{
	register struct usock *up;
	struct socklink *sp;

	if ((up = itop (s)) == NULLUSOCK) {
		errno = EBADF;
		return NULLCHAR;
	}
	if (up->cb.p == NULLCHAR) {
		errno = ENOTCONN;
		return NULLCHAR;
	}
	sp = up->sp;
	if (sp->state != NULL)
		return (*sp->state) (up);

	/* Datagram sockets don't have state */
	errno = EOPNOTSUPP;
	return NULLCHAR;
}
/* Convert a socket index to an internal user socket structure pointer */
ENTRY struct usock *
itop (register int s)
{
	s -= Nfiles;
	if (s < 0 || s >= Nsock)
		return NULLUSOCK;

	return Usock[s];
}

ENTRY void
st_garbage (int red)
{
	int i;
	struct usock *up;

	for (i = Nfiles;i < Nfiles + Nsock;i++) {
		up = Usock[i];
		if (up != NULLUSOCK && up->type == TYPE_LOCAL_STREAM)
			mbuf_crunch (&up->cb.local->q);
	}
}
