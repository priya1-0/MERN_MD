
/* ************************************************************************* */
/*
 *	time.h
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
 *	Module:		CSC
 *
 *	This file contains definitions for the duration of various timers.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 19:06:28  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _CSC_TIME_H
#define _CSC_TIME_H

/* ************************************************************************* */

#define TIME__CSC_CMD_ENTRY_ABANDON			3000
#define TIME__TIES_OK_RELEASE				10
#define TIME__OMC_DIAL_ACK_TIMEOUT			30
#define TIME__OMC_CONNECT_ACK_TIMEOUT		30
#define TIME__OMC_DISCONNECT_ACK_TIMEOUT	40
#define TIME__OMC_ON_HOOK_TIMEOUT			100
#define TIME__FLOW_CONTROL_PULSE_LOW		50
#define TIME__RING_CNT_CLEAR				800
#define TIME__OMC_HALT_ACK_TIMEOUT			200
#define TIME__OMC_FX1_ESCAPE_TIMEOUT		100
#define TIME__OMC_FX2_ESCAPE_TIMEOUT		100

#define TIME__FX2_DC2_WAIT_DURATION			3000
#define TIME__FX2_DTE_TX_STOP_DURATION		3000

#define TIME__RDLB_REMOTE_ACK				1000

/* ************************************************************************* */

#endif /* _CSC_TIME_H */
