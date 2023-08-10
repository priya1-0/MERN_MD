
/* ************************************************************************* */
/*
 *	net.c
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
 *	Module:		net
 *
 *  module configuration routines.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 20:31:57  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#include "system/system.h"

#include "lansend/global.h"
#include "net/net.h"

/* ************************************************************************* */
/*
 *	Entry Routine: net_module_reset
 *
 *	This routine sets the variables of the net module to safe values.
 *
 *	Parameters:
 *		none
 *
 *	Returns:
 *		none
 */

ENTRY void
net_module_reset (void)
{
	netuser_init ();
	route_init ();
	socket_init ();
}

/* ************************************************************************* */
/*
 *	Entry Routine: net_startup
 *
 *	This starts up the net module.
 *
 *	Parameters:
 *		none
 *
 *	Returns:
 *		none
 */
ENTRY void
net_startup (void)
{

}
