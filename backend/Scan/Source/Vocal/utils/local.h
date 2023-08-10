
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
 *	Module:		UTILS
 *
 *	This file contains the private declarations for the UTILS module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 20:53:02  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _UTILS_LOCAL_H
#define _UTILS_LOCAL_H

#include "utils/locald.h"
#include "utils/utils.h"

/* ************************************************************************* */
/*- MKHEADER Begin -*/

/* Local Routines: */

/* httpcli.c */

#ifdef utils_httpcli_c
static int http_status (int status);
static void get_proc (int iarg, void *p1, void *p2);
static int getfile_proc (int iarg, void *p1, void *p2);
static int doget (int argc, char *argv[], void *p);
static int dogetfile (int argc, char *argv[], void *p);
#endif /* utils_httpcli_c */

/* ping.c */

#ifdef utils_ping_c
static void pinghdr (struct session *sp, struct ping *ping);
static void pingtx (int s, void *ping1, void *p);
#endif /* utils_ping_c */

/*- MKHEADER End -*/


/* ************************************************************************* */
#endif /* _UTILS_LOCAL_H */
