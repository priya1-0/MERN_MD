
/* ************************************************************************* */
/*
 *	cscd.h
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
 *	This file contains the public parameter declarations/definitions for
 *	the CSC module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 19:06:28  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _CSC_CSCD_H
#define _CSC_CSCD_H

#include "csc/config.h"

/* ************************************************************************* */

typedef struct {

	uint16	_mode;

	uint16	_fc_state;
	uint16	_fc_xoff_state;
	uint16	_fc_cts_state;
	bool	_fc_cts;

	bool	_inactivity_ignores_rx;
	uint16	_inactivity_dtimer_reload;

	volatile uint16	_inactivity_dtimer;
	volatile uint16 _decisec_timer;

	bool	_dcd;

	uint16	_opcode;
	bool	_char_abort_inhibit;

	bool	_fx_within_fax;
	bool	_fx_fx1_select;
	bool	_fx_fx2_0_select;
	bool	_fx_changed;
	uint16	_fx2_start_opcode;
	bool	_fx2_within_voice;
	bool	_fx2_within_fdt;
	bool	_fx2_within_tx;

	bool	_fx2_halt_upon_char_seen;
	bool	_fx2_hangup_code_override;
	uint16	_fx2_hangup_code;
	uint16	_fx2_report;
	uint16	_fx2_return_state;
	bool	_fx2_halt_sent;

	bool	_within_data;
	bool	_ties_mode;
	uint16 _ring_to_answer_min_duration;
	uint16 _ring_to_answer_max_duration;
	uint16 _ring_cnt_max;
} csc_csc_t;

/* ************************************************************************* */

DEF_DATA(csc_csc_t, csc_csc)
#define CSC_CSC_DATA csc_csc_t csc_csc
#define CSC_CSC USE_DATA(csc_csc)

/* ************************************************************************* */

#define csc_mode							(CSC_CSC._mode)

#define csc_dial_string						(CSC_CSC._dial_string)
#define csc_fc_state						(CSC_CSC._fc_state)
#define csc_fc_xoff_state					(CSC_CSC._fc_xoff_state)
#define csc_fc_cts_state					(CSC_CSC._fc_cts_state)
#define csc_fc_cts							(CSC_CSC._fc_cts)
#define csc_inactivity_ignores_rx			(CSC_CSC._inactivity_ignores_rx)
#define csc_inactivity_dtimer_reload		(CSC_CSC._inactivity_dtimer_reload)
#define csc_decisec_timer					(CSC_CSC._decisec_timer)
#define csc_inactivity_dtimer				(CSC_CSC._inactivity_dtimer)

#define mdm_dcd								(CSC_CSC._dcd)

#define csc_opcode							(CSC_CSC._opcode)
#define csc_char_abort_inhibit				(CSC_CSC._char_abort_inhibit)

#define csc_fx_within_fax					(CSC_CSC._fx_within_fax)
#define csc_fx_fx1_select					(CSC_CSC._fx_fx1_select)
#define csc_fx_fx2_0_select 				(CSC_CSC._fx_fx2_0_select)
#define csc_fx_changed						(CSC_CSC._fx_changed)
#define csc_fx2_start_opcode				(CSC_CSC._fx2_start_opcode)
#define csc_fx2_within_voice	 			(CSC_CSC._fx2_within_voice)
#define csc_fx2_within_fdt					(CSC_CSC._fx2_within_fdt)
#define csc_fx2_within_tx					(CSC_CSC._fx2_within_tx)
#define csc_fx2_halt_upon_char_seen			(CSC_CSC._fx2_halt_upon_char_seen)
#define csc_fx2_hangup_code_override		(CSC_CSC._fx2_hangup_code_override)
#define csc_fx2_hangup_code					(CSC_CSC._fx2_hangup_code)
#define csc_fx2_report						(CSC_CSC._fx2_report)
#define csc_fx2_return_state				(CSC_CSC._fx2_return_state)
#define csc_fx2_halt_sent					(CSC_CSC._fx2_halt_sent)

#define csc_within_data						(CSC_CSC._within_data)

#define csc_ties_mode						(CSC_CSC._ties_mode)
#define parm__csc_ring_to_answer_min_duration	(CSC_CSC._ring_to_answer_min_duration)
#define parm__csc_ring_to_answer_max_duration	(CSC_CSC._ring_to_answer_max_duration)
#define parm__csc_ring_cnt_max					(CSC_CSC._ring_cnt_max)

/* ************************************************************************* */

#endif /* _CSC_CSCD_H */
