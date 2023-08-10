
/* ************************************************************************* */
/*
 *	mdm.h
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
 *	Module:		MDM
 *
 *	This file contains the public declarations for the MDM module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 20:23:04  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _MDM_MDM_H
#define _MDM_MDM_H

/* ************************************************************************* */

#include "mdm/mdmd.h"

/* ************************************************************************* */

/*	The below numbers set the rate at which the background is called
	as a ratio to the timer interrupt.  Neither TICK_THROTTLE_RATIO_BOTTOM
	nor TICK_THROTTLE_RATIO_TOP can ever be zero!								 */

#define TICK_THROTTLE_RATIO_TOP		1
#define TICK_THROTTLE_RATIO_BOTTOM	1

/* ************************************************************************* */

/*- MKHEADER Begin -*/

/* Global Routines: */

/* main.c */
int vocal_main (void);
int vocal_application_startup (void);
int vocal_application_bg (void);
int vocal_application_shutdown (void);
int application_startup (void);
int application_bg (void);
void application_shutdown (void);
void main_timer (void);
bool system_configure_init (void);
bool system_configure_start (void);
void clear_structures (void);

/* mdm.c */
void mdm_bg (void);
void mdm_hardware_bg (void);
void mdm_system_exit (int errorcode);
void mdm_system_bg (void);

/*- MKHEADER End -*/


/* ************************************************************************* */

#endif /* _MDM_MDM_H */
