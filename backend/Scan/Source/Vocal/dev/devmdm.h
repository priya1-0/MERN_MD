
/* ************************************************************************* */
/*
 *	devmdm.h
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
 *  Device driver for VOCAL master/mdm code.
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

#ifndef _DEV_DEVMDM_H
#define _DEV_DEVMDM_H

/* mdm controller control block */
struct mdm {
	struct iface *iface;

	struct mbuf *txbp;			/* Current packet being sent */

	struct proc *devmonitor;

	char dtrState;
	char rtsState;
	char dsrState;
	char ctsState;
	char dcdState;

	struct timer idle;			/* Idle timeout timer */

	sint31 xoffChanges;
	sint31 ctsChanges;
	sint31 dcdChanges;
	sint31 dtrChanges;
	sint31 rtsChanges;
	sint31 dsrChanges;
	sint31 hwtimeouts;			/* hw fifo character timeout int's */

	sint31 rxchar;				/* Received characters */
	sint31 txchar;				/* Transmitted characters */
	struct proc * trace_proc;	/* pointer to process handling modem event/status tracing */
};

#define NULLMDM (struct mdm *) 0

extern struct mdm *Mdm[];

#define MDM_TIMEOUT 360		/* Default timeout */

/* These values map to the rs232 array in n8250.c, also up/down <-> on/off
 * are order dependent.  See rs232CHANGED for more information. */
#define rs232NONE	    0		/* Don't care. */
#define rs232ON         2		/* Start state is UP. */
#define rs232OFF        3		/* Start state is DOWN. */
#define rs232UP         6		/* Changed to ON. */
#define rs232DOWN       7		/* Changed to OFF. */
/* This is a bit mask to map ON to UP and OFF to DOWN, so you don't have to
 * care whether this is the initial state or not. */
#define rs232CHANGED    4

#endif /* _DEV_DEVMDM_H */
