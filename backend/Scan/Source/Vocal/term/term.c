
/* ************************************************************************* */
/*
 *	term.c
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
 *	Module:		term
 *
 *  module configuration routines.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 20:49:20  zhangn1
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

#include "term/local.h"

#include "lansend/lansend.h"

/* ************************************************************************* */
/*
 *	Entry Routine: term_module_reset
 *
 *	This routine sets the variables of the term module to safe values.
 *
 *	Parameters:
 *		none
 *
 *	Returns:
 *		none
 */

ENTRY void
term_module_reset (void)
{
}

/* ************************************************************************* */
/*
 *	Entry Routine: term_startup
 *
 *	This starts up the term module.
 *
 *	Parameters:
 *		none
 *
 *	Returns:
 *		none
 */
ENTRY void
term_startup (void)
{
}

/***************************************************************************
 *
 * Function: hangup_wait
 *
 * Pull down DTR, wait 1 / 2 second, and reset DTR and RTS.
 *
 * Parameters:
 *   ifp is the interface to hang up.
 *
 * Returns: None.
 *
 ***************************************************************************/

ENTRY void
hangup_wait (struct iface *ifp)
{
	if (ifp != NULLIF && ifp->ioctl != NULL) {
		ifp->ioctl (ifp, PARAM_DTR, TRUE, 0L);
		pause (500L);
		ifp->ioctl (ifp, PARAM_DTR, TRUE, 1L);
		ifp->ioctl (ifp, PARAM_RTS, TRUE, 1L);
		pause (500L);
	}
}

/***************************************************************************
 *
 * Function: hangup_proc
 *
 * Hang up from outside the timer.  localdrop does a pwait which drives
 * timer processes nuts.
 *
 * Parameters:
 *   p1 is the interface to hangup.
 *
 * Returns: None.
 *
 ***************************************************************************/

LOCAL void
hangup_proc (int unused1, void *p1, void *unused2)
{
	hangup_wait ((struct iface *) p1);
}

/***************************************************************************
 *
 * Function: hangup
 *
 * Start a process to hangup a connection.
 *
 * Parameters:
 *   p is the interface to hang up.
 *
 * Returns: None.
 *
 ***************************************************************************/

ENTRY void
hangup (void *p)
{
	newproc("Hang up", 320, hangup_proc, 0, p, NULL, 0);
}
