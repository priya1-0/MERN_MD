
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
 *	Product:	LANsEND
 *
 *	Module:		TERM
 *
 *	This file contains the private declarations for the TERM module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 20:49:20  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _TERM_LOCAL_H
#define _TERM_LOCAL_H

#include "term/locald.h"
#include "term/term.h"

/* ************************************************************************* */
/*- MKHEADER Begin -*/

/* Local Routines: */

/* term.c */

#ifdef term_term_c
static void hangup_proc (int unused1, void *p1, void *unused2);
#endif /* term_term_c */

/*- MKHEADER End -*/


/* ************************************************************************* */

#endif /* _TERM_LOCAL_H */
