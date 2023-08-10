
/* ************************************************************************* */
/*
 *	dp.h
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
 *	Module:		DP
 *
 *	This file contains the public declarations for the DP module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 18:25:54  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _DP_DP_H
#define _DP_DP_H

/* ************************************************************************* */

#include "dp/dpd.h"
#include "dp/config.h"

/* ************************************************************************* */
#define STOP_MODE__RESET								0x0000
#define STOP_MODE__BUFFERED								0x0001
#define STOP_MODE__MNP									0x0002
#define STOP_MODE__LAPM									0x0003

/* ************************************************************************* */
/*
 *	MNP indications as to current SART installed.
 *
 */

#define DP_LINE_TYPE__ASYNC								0x0000
#define DP_LINE_TYPE__SYNC								0x0001

/* ************************************************************************* */

#define DP_TIMER_DIV									1  /* 100ms */

/* ************************************************************************* */
/*
 *	These inter-protocol result codes indicate the reason for a particular
 *	protocol's startup failing.  Depending upon this value, a different
 *	protocol may then be attempted.
 *
 */

#define DP_RESULT__NONE									0x0000
#define DP_RESULT__FLAGS								0x0001
#define DP_RESULT__FAILURE								0x0002
#define DP_RESULT__PLR									0x0003
#define DP_RESULT__ADP_ODP								0x0004

/* ************************************************************************* */
/*
 *  HDLC flags for detecting LAPM start
 *
 */

#define DP_HDLC_FLAG__SH_0								0x007E
#define DP_HDLC_FLAG__SH_1								0x003F
#define DP_HDLC_FLAG__SH_2								0x00BF

/* ************************************************************************* */
/*
 * current_mode
 *
 */

#define DP_WITHIN__NO_MODE								0x0000		/* DP while running no mode			*/
#define DP_WITHIN__MNP_VER_1_MODE						0x0001		/* DP while running MNP				*/
#define DP_WITHIN__BUFFERED_MODE						0x0002		/* DP while running SPEED BUFFERING	*/
#define DP_WITHIN__LAPM_MODE							0x0003		/* DP while running LAPM			*/
#define DP_WITHIN__DIRECT_MODE							0x0004		/* DP while running DIRECT			*/
#define DP_WITHIN__AR_DET_MODE							0x0005      /* DP while running detect and/or autoreliable */
#define DP_WITHIN__MNP_VER_2_MODE						0x0006		/* MNP while looking for flags for purpose of entering LAPM */
#define DP_WITHIN__MNP_VER_3_MODE						0x0007      /* MNP for which initial LR packet portion is from bfrd rx buffer */
#define DP_WITHIN__V120_MODE							0x0008

/* ************************************************************************* */
/*
 *   Failure types from dp_process_failure_types ()..
 *
 */

#define DP_FAILURE__NONE								0x0000
#define DP_FAILURE__NO_FURTHER_ACTION					0x0001

/* ************************************************************************* */

/*- MKHEADER Begin -*/

/* Global Routines: */

/* dp.c */
void dp_task_start (void);
void dp_sm_startup (void);
void dp_timer_service (void);
void dp_retrain_sm_start (void);

/* linkage.c */
uint16 dp_process_failure_type (void);
void dp_tx_put_break (uint16 duration);

/*- MKHEADER End -*/


/* ************************************************************************* */

#endif /* _DP_DP_H */
