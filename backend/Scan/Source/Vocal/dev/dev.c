
/* ************************************************************************* */
/*
 *	dev.c
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
 *	Module:		dev
 *
 *  module configuration routines.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 19:38:37  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#include "system/system.h"

#include "lansend/global.h"
#include "dev/dev.h"

/* ************************************************************************* */
/*
 *	Entry Routine: dev_module_reset
 *
 *	This routine sets the variables of the dev module to safe values.
 *
 *	Parameters:
 *		none
 *
 *	Returns:
 *		none
 */

ENTRY void
dev_module_reset (void)
{
	mdm_init ();
	iface_init ();

}

/* ************************************************************************* */
/*
 *	Entry Routine: dev_startup
 *
 *	This starts up the dev module.
 *
 *	Parameters:
 *		none
 *
 *	Returns:
 *		none
 */
ENTRY void
dev_startup (void)
{

}

/* utility routines */

/* ************************************************************************* */
/*
 *  Function: pkt_ioctl
 *
 *  Perform control operation on the ethernet device.
 *
 *  Parameters:
 *    "ifp" is a pointer to the interface structure for the device
 *    "cmd" is the ioctl command number
 *    "set" is a boolean for performing set operation
 *    "val" is the value to be used for a set operation
 *
 *  Returns: value of current setting
 *
 */
ENTRY sint31
pkt_ioctl (struct iface *ifp, int cmd, int set, sint31 val)
{

	switch (cmd) {
	case PARAM_SPEED:
		/* report the device speed */
		return 100000000L;		/* 100 Mbps */

	case PARAM_BLIND:			/* Can't see what we are doing, so pretend we're up */
		cmd = PARAM_UP;
		val = 0L;

	case PARAM_DOWN:			/* Set the connection DOWN. */
	case PARAM_UP:				/* Set the connection UP. */
	case PARAM_IDLE:
	case PARAM_READY:
		if (ifp->iftype != NULLIFT && ifp->iftype->iostatus != NULLVFP) {
			(*ifp->iftype->iostatus) (ifp, cmd, val);
		}
		return 0;

	case PARAM_DTR:
	case PARAM_RTS:
	case PARAM_DCD:
	case PARAM_XOFF:
		return 0;				/* Not supported */
	}

	return -1;
}

ENTRY uint32
buff_to_dword_le (char *buffer)
{
	uint32 value;

	value  = (((uint32)*buffer++) & 0xFFUL);
	value |= (((uint32)*buffer++) & 0xFFUL) << 8;
	value |= (((uint32)*buffer++) & 0xFFUL) <<16;
	value |= (((uint32)*buffer++) & 0xFFUL) <<24;
	return value;
}
