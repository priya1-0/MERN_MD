
/* ************************************************************************* */
/*
 *	monitor.h
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
 *	Module:		MONITOR
 *
 *	This file contains the public declarations for the MONITOR module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 19:06:28  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _MONITOR_MONITOR_H
#define _MONITOR_MONITOR_H

#include "csc/monitord.h"

/* ************************************************************************* */

/*- MKHEADER Begin -*/

/* Global Routines: */

/* monitor.c */
void monitor_module_reset (void);
void monitor_start (void);

/*- MKHEADER End -*/


/* ************************************************************************* */

#endif /* _CSC_MONITOR_H */
