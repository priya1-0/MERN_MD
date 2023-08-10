
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
 *	Product:	MODEM 101
 *
 *	Module:		SUPPORT
 *
 *	This file contains the private declarations for the SUPPORT module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 20:44:27  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _SUPPORT_LOCAL_H
#define _SUPPORT_LOCAL_H

/* ************************************************************************* */

#include "support/locald.h"

/* ************************************************************************* */

#define NEW_TOLOWER(c)	((c) | 0x20)
#define NEW_ISUPPER(c)	((c >= 0x41) && (c <= 0x5a))

#define NEW_TOUPPER(c)	((c) & 0xdf)
#define NEW_ISLOWER(c)	((c >= 0x61) && (c <= 0x7a))

/* ************************************************************************* */

/*- MKHEADER Begin -*/

/* Local Routines: */

/* print.c */

#ifdef support_print_c
static void vprint_routine (const char *fmt, va_list argp);
static char print_parse_type (const char **cpp);
static void print_output_char (char c);
#endif /* support_print_c */

/*- MKHEADER End -*/


/* ************************************************************************* */

#endif /* _SUPPORT_LOCAL_H */
