
/* ************************************************************************* */
/*
 *	local.h
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
 *	This file contains the private declarations for the TRACE module.
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

#ifndef _TRACE_LOCAL_H
#define _TRACE_LOCAL_H

#include "trace/locald.h"
#include "trace/trace.h"

/* ************************************************************************* */

typedef struct symtab_s {
	struct symtab_s *next;
	uint16 seg;
	uint16 offs;
	char *name;
} symtab_t;

/* ************************************************************************* */
/* States: */

/* trace.c */

/* ************************************************************************* */

/* Variables: */

/* States: */

/* trace.c */

/*- MKHEADER Begin -*/

/* Local Routines: */

/* trace.c */

#ifdef trace_trace_c
static void ctohex (char *buf, uint16 c);
static void fmtline (FILE *fp, uint16 addr, char *buf, uint16 len);
static void hex_dump (FILE *fp, struct mbuf **bpp);
static void ascii_dump (FILE *fp, struct mbuf **bpp);
static void show_trace (struct iface *ifp);
#endif /* trace_trace_c */

/*- MKHEADER End -*/


/* ************************************************************************* */

#endif /* _TRACE_LOCAL_H */
