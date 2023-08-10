
/* ************************************************************************* */
/*
 *	logging.h
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
 *	Module:		DEBUG
 *
 *	DSP debug Logging mechanism defines
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 19:35:04  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _DEBUG_LOGGING_H
#define _DEBUG_LOGGING_H

#define	MODEM_TYPE			v34n_rxtx_call_direction
#define	ORIG_MODEM			1
#define	ANSW_MODEM			0

/* ************************************************************************* */
/*
 *	Debug macros for use in C Language Code
 */

#define debug_log0(val)		report_status (STATUS__LOG_0, val)
#define debug_log1(val)		report_status (STATUS__LOG_1, val)
#define debug_log2(val)		report_status (STATUS__LOG_2, val)
#define debug_log3(val)		report_status (STATUS__LOG_3, val)
#define debug_log4(val)		report_status (STATUS__LOG_4, val)
#define debug_log5(val)		report_status (STATUS__LOG_5, val)
#define debug_log6(val)		report_status (STATUS__LOG_6, val)
#define debug_log7(val)		report_status (STATUS__LOG_7, val)
#define debug_log8(val)		report_status (STATUS__LOG_8, val)
#define debug_log9(val)		report_status (STATUS__LOG_9, val)
#define debug_logA(val)		report_status (STATUS__LOG_A, val)
#define debug_logB(val)		report_status (STATUS__LOG_B, val)
#define debug_logC(val)		report_status (STATUS__LOG_C, val)
#define debug_logD(val)		report_status (STATUS__LOG_D, val)
#define debug_logE(val)		report_status (STATUS__LOG_E, val)
#define debug_logF(val)		report_status (STATUS__LOG_F, val)

/* ************************************************************************* */

/*- MKHEADER Begin -*/

/*- MKHEADER End -*/


/* ************************************************************************* */

#endif /* _DEBUG_LOGGING_H */
