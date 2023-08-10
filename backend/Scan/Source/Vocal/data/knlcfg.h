
/* ************************************************************************* */
/*
 *	knlcfg.h
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
 *	Module:		KERNEL
 *
 *	This file defines array sizes for variables related to the
 *	KERNEL module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 19:33:26  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _DATA_KNLCFG_H
#define _DATA_KNLCFG_H

/* ************************************************************************* */

#define NUMBER_OF_FGBG_STATES			16
#define NUMBER_OF_FGBG_TIMERS			16

/* ************************************************************************* */

#define NUMBER_OF_FG_EVENTS				256

#define NUMBER_OF_FG_STATES				NUMBER_OF_FGBG_STATES
#define NUMBER_OF_FG_TIMERS				NUMBER_OF_FGBG_TIMERS

#define NUMBER_OF_FG_BLOCKS				0x0009

#define NUMBER_OF_TOTAL_THREAD_COMP		0x0040

/* ************************************************************************* */

#define NUMBER_OF_BG_EVENTS				256
#define NUMBER_OF_BG_TASKS				16

#define NUMBER_OF_BG_EVENTS_TICKS		(NUMBER_OF_BG_EVENTS / 4)

#define NUMBER_OF_BG_STATES				NUMBER_OF_FGBG_STATES
#define NUMBER_OF_BG_TIMERS				NUMBER_OF_FGBG_TIMERS

#define STATUS_BUFFER_SIZEOF			256

/* ************************************************************************* */

/* ************************************************************************* */

#endif /* _DATA_KNLCFG_H */
