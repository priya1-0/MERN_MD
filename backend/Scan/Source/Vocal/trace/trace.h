
/* ************************************************************************* */
/*
 *	trace.h
 *
 *	(C) 1994 - 2006 VOCAL Technologies, Ltd.
 *
 *	ALL RIGHTS RESERVED.  PROPRIETARY AND CONFIDENTIAL.
 *
 *	VOCAL Technologies, Ltd.
 *	90A John Muir Drive.
 *	Buffalo, NY  14228
 *
 *	Product:	LANSEND
 *
 *	Module:		TRACE
 *
 *	This file contains the public declarations for the TRACE module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 20:50:30  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _TRACE_TRACE_H
#define _TRACE_TRACE_H

/* ************************************************************************* */

#include "trace/traced.h"

/* ************************************************************************* */
/* States: */

/* trace.c */

/* ************************************************************************* */

/* Variables: */

/* States: */

/* trace.c */

/*- MKHEADER Begin -*/

/* Global Routines: */

/* trace.c */
void dump (struct iface *ifp, int direction, struct mbuf *bp);
void raw_dump (struct iface *ifp, int direction, struct mbuf *bp);
int dotrace (int argc, char *argv[], void *p);
void shuttrace (void);
void trace_log (struct iface *ifp, char *fmt, ...);
int tprintf (struct iface *ifp, char *fmt, ...);

/*- MKHEADER End -*/


/* ************************************************************************* */

#endif /* _TRACE_TRACE_H */
