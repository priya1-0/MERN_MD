
/* ************************************************************************* */
/*
 *	devparm.h
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
 *	Module:		DEV
 *
 *	This file contains the device parameter symbol declarations.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 19:38:37  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _DEV_DEVPARM_H
#define _DEV_DEVPARM_H

/* device parameter control */
#define	PARAM_DATA		 0		/* Find how much data is waiting to be read */
#define	PARAM_TXDELAY	 1
#define	PARAM_PERSIST	 2
#define	PARAM_SLOTTIME	 3
#define	PARAM_TXTAIL	 4
#define	PARAM_FULLDUP	 5
#define	PARAM_HW		 6
#define	PARAM_MUTE		 7
#define	PARAM_DTR		 8		/* Get/set Data Terminal Ready */
#define	PARAM_RTS		 9		/* Get/set Request To Send */
#define	PARAM_SPEED		10		/* Set both Tx and Rx speed */
#define	PARAM_ENDDELAY	11
#define	PARAM_GROUP		12
#define PARAM_IDLE		13
#define	PARAM_MIN		14
#define	PARAM_MAXKEY	15
#define	PARAM_WAIT		16

/* redirector functions */
#define PARAM_BREAK 	17		/* Get/set break signal */
#define PARAM_RXSIZE	18		/* Get/set the size of the interupt ring buffer */

#define PARAM_RSPEED	19		/* Set the Rx speed */
#define PARAM_RCHARLEN	20		/* Set the Rx character length */
#define PARAM_RSTOPBITS	21		/* Set the number of Rx stop bits */
#define PARAM_RPARITY	22		/* Set the Rx parity */
#define PARAM_N_PARITY	0
#define PARAM_O_PARITY	1
#define PARAM_E_PARITY	2
#define PARAM_M_PARITY	3
#define PARAM_S_PARITY	4
#define PARAM_TSPEED	23		/* Set the Tx speed */
#define PARAM_TCHARLEN	24		/* Set the Tx character length */
#define PARAM_TSTOPBITS	25		/* Set the number of Tx stop bits */
#define PARAM_TPARITY	26		/* Set the Tx parity */

#define PARAM_XOFF		27		/* Get/set a software block on transmission */

/* isolate encap from driver */
#define PARAM_TRIG		28
#define PARAM_DCD		29

#define PARAM_STATUS	30		/* Return best approximation of a the 8250
								 * status registers.  32 bit value is of the
								 * format "00 00 MSR LSR".  The upper word
								 * isn't used yet. */
#define PARAM_SAVE		31		/* Write the current configuration off
								 * somewhere.  It's only one deep. */
#define PARAM_RESTORE	32		/* Restore the configuration to match the
								 * last saved */

#define PARAM_MODE		33
#define PARAM_MODE_ASYNC	0
#define PARAM_MODE_HDLC		1
#define PARAM_MODE_SYNC		2
#define PARAM_MODE_MDM		3

#define PARAM_CLOCK		34
#define PARAM_CLOCK_INT		0
#define PARAM_CLOCK_EXT		1
#define PARAM_CLOCK_SLAVE	2

#define PARAM_DOWN		0x81
#define PARAM_UP		0x82
#define PARAM_BLIND		0x83	/* Should be vertigo, can't tell down/up? */
#define PARAM_READY		0x84
#define	PARAM_RETURN	0xff

#endif /* _DEV_DEVPARM_H */
