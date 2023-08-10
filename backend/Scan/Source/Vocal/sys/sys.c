
/* ************************************************************************* */
/*
 *	sys.c
 *
 *	(C) 2004 - 2006 VOCAL Technologies, Ltd.
 *
 *	ALL RIGHTS RESERVED.  PROPRIETARY AND CONFIDENTIAL.
 *
 *	VOCAL Technologies, Ltd.
 *	90A John Muir Drive.
 *	Buffalo, NY  14228
 *
 *	Product:	LANsEND
 *
 *	Module:		sys
 *
 *  module configuration routines.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 20:46:45  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#include "system/system.h"

#include "lansend/global.h"
#include "sys/sys.h"

/* ************************************************************************* */
/*
 *	Entry Routine: sys_module_reset
 *
 *	This routine sets the variables of the sys module to safe values.
 *
 *	Parameters:
 *		none
 *
 *	Returns:
 *		none
 */

ENTRY void
sys_module_reset (void)
{
	alloc_init ();
	filesys_init ();
	kernel_init ();
	mbuf_init ();
	session_init ();
	stdio_init ();
	ti_sys_init ();
	timer_init ();
	keyboard_init ();
	serial_init ();
}

/* ************************************************************************* */
/*
 *	Entry Routine: sys_startup
 *
 *	This starts up the sys module.
 *
 *	Parameters:
 *		none
 *
 *	Returns:
 *		none
 */
ENTRY void
sys_startup (void)
{
}
