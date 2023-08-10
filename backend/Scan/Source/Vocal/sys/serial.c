
/* ************************************************************************* */
/*
 *	serial.c
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
 *	Module:		SYS
 *
 *	This file contains the serial console functions.
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

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

ENTRY void
serial_init (void)
{
}

/* ************************************************************************* */

/* Create a new virtual display.
 * The "noscrol" flag, if set, causes lines to "wrap around" from the bottom
 * to the top of the screen instead of scrolling the entire screen upwards
 * with each new line. This can be handy for packet trace screens.
 */
ENTRY struct display *
newserial (int rows, int cols, int noscrol)
{
	struct display *dp;

	dp = (struct display *) calloc (1, sizeof (struct display));
	if (dp == NULL) {
		return NULLDISP;
	}
	dp->cookie = D_COOKIE;
	return dp;
}

/* ************************************************************************* */

/* Close a display - simply get rid of the memory */
ENTRY void
closeserial (struct display *dp)
{
	if (dp != NULLDISP && dp->cookie == D_COOKIE)
		free (dp);
}

/* ************************************************************************* */

/* Write data to the virtual display. Does NOT affect the real screen -
 * dupdate (dp) must be called to copy the virtual screen to the real
 * screen.
 */
ENTRY void
serialwrite (struct display *dp, char *buf, int cnt)
{
	if (dp == NULLDISP || dp->cookie != D_COOKIE)
		return;

	sys_putb(buf, cnt);
}

/* ************************************************************************* */
