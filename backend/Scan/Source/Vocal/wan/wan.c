
/* ************************************************************************* */
/*
 *	wan.c
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
 *	Module:		wan
 *
 *  module configuration routines.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 20:56:09  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#include "system/system.h"

#include "lansend/global.h"
#include "net/net.h"
#include "sys/sys.h"
#include "dev/dev.h"
#include "ip/ip.h"
#include "wan/wan.h"

/* ************************************************************************* */
/*
 *	Entry Routine: wan_module_reset
 *
 *	This routine sets the variables of the wan module to safe values.
 *
 *	Parameters:
 *		none
 *
 *	Returns:
 *		none
 */

ENTRY void
wan_module_reset (void)
{
	pppfsm_init();
	pppipcp_init();
	ppplcp_init();

}

/* ************************************************************************* */
/*
 *	Entry Routine: wan_startup
 *
 *	This starts up the wan module.
 *
 *	Parameters:
 *		none
 *
 *	Returns:
 *		none
 */
ENTRY void
wan_startup (void)
{

}
