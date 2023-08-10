
/* ************************************************************************* */
/*
 *	locald.h
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
 *	This file contains the private parameter declarations/definitions
 *	for the CSC module.
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

#ifndef _CSC_LOCALD_H
#define _CSC_LOCALD_H

#include "csc/config.h"

/* ************************************************************************* */

typedef struct {
	uint16	_echo_buffer [CSC_ECHO_BUFFER_SIZE];
	uint16	*_echo_inp;
	uint16	*_echo_outp;
	uint16	_echo_overflow;
	uint16	_process_code;
	bool	_delayed_s3_echo_pending;
	bool	_delayed_s3_echo_start;
	bool	_rsp_diag_continue;
	uint16	_dmdp_disc_state;
	bool	_fx1_rx_dle_etx_request;
	uint16	_csc_return_state;
	bool	_within_dle;
	uint16	_100ms_div;
	uint16	_1s_div;
	uint32	_1s_cnt;
	bool	_advanced_command_started;
	bool	_action_exit_pending;
	bool _online_ties_idle;
	uint8	_ring_to_answer_state;
} csc_local_t;

/* ************************************************************************* */

DEF_DATA(csc_local_t, csc_local)
#define CSC_LOCAL_DATA csc_local_t csc_local
#define CSC_LOCAL USE_DATA(csc_local)

/* ************************************************************************* */

#define	csc_echo_buffer						(CSC_LOCAL._echo_buffer)
#define	csc_echo_inp						(CSC_LOCAL._echo_inp)
#define	csc_echo_outp						(CSC_LOCAL._echo_outp)
#define	csc_echo_overflow					(CSC_LOCAL._echo_overflow)
#define	csc_process_code					(CSC_LOCAL._process_code)
#define	csc_delayed_s3_echo_pending			(CSC_LOCAL._delayed_s3_echo_pending)
#define	csc_delayed_s3_echo_start			(CSC_LOCAL._delayed_s3_echo_start)
#define rsp_diag_continue					(CSC_LOCAL._rsp_diag_continue)
#define csc_dmdp_disc_state					(CSC_LOCAL._dmdp_disc_state)
#define csc_return_state					(CSC_LOCAL._csc_return_state)
#define dte_fx1_rx_dle_etx_request			(CSC_LOCAL._fx1_rx_dle_etx_request)
#define dte_within_dle						(CSC_LOCAL._within_dle)
#define csc_100ms_div						(CSC_LOCAL._100ms_div)
#define csc_1s_div							(CSC_LOCAL._1s_div)
#define csc_1s_cnt							(CSC_LOCAL._1s_cnt)
#define csc_advanced_command_started		(CSC_LOCAL._advanced_command_started)

#define csc_action_exit_pending				(CSC_LOCAL._action_exit_pending)
#define	csc_online_ties_idle				(CSC_LOCAL._online_ties_idle)
#define csc_ring_to_answer_state				(CSC_LOCAL._ring_to_answer_state)

/* ************************************************************************* */

#endif /* _CSC_LOCALD_H */
