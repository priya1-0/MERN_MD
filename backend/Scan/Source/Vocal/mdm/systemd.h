
/* ************************************************************************* */
/*
 *	systemd.h
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
 *	This file contains the parameter definitions for the system control.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 20:23:04  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _MDM_SYSTEMD_H
#define _MDM_SYSTEMD_H

#include "mdm/config.h"
#include "mdm/mdm.h"
#include "mdm/rev.h"

/* ************************************************************************* */

/*  These are the only variables for which there is a single copy of
 *  variables, regardless as to if multi-devices is used.
 */

/* system_* variables */

#ifdef WE_ARE_DEFINING_VARIABLES
/*	As per contractural obligations, VOCAL's copyright notice string MUST
 *	always be a part of the binary.  Any modifications to the software must
 *	not cause it to be absent.
 */
EXTERN char system_revision_string [] = "TI 55X";

#else /* WE_ARE_DEFINING_VARIABLES */
EXTERN char system_revision_string [];
#endif /* WE_ARE_DEFINING_VARIABLES */

#ifdef DO_WIN95_VXD
/*EXTERN DWORD win32_processed_time; */
/*EXTERN DWORD hTimerTick; */
#endif /* DO_WIN95_VXD */

/* arg_* variables */
EXTERN uint16 arg_debug_flag;

/* ************************************************************************* */

#endif /* _MDM_SYSTEMD_H */
