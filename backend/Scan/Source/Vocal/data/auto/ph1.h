
/* ************************************************************************* */
/*
 *	ph1.h
 *
 *	(C) 1994 - 2007 VOCAL Technologies, Ltd.
 *
 *	ALL RIGHTS RESERVED.  PROPRIETARY AND CONFIDENTIAL.
 *
 *	VOCAL Technologies, Ltd.
 *	90A John Muir Drive.
 *	Buffalo, NY  14228
 *
 *	Product:	MODEM 101
 *
 *	Module:		DATA
 *
 *	This file contains automatically generated data for ph1.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 19:12:25  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _DATA_PH1_H
#define _DATA_PH1_H
#include "data/sections.h"

/* ************************************************************************* */

typedef struct {
	const_d    phase_t                     _ANSam_trace_offset;
} ph1_const_t;

/* ************************************************************************* */

DEF_DATA(ph1_const_t, ph1_const)
#define PH1_CONST_DATA ph1_const_t ph1_const
#define PH1_CONST USE_DATA(ph1_const)
#define ph1_const_used

/* ************************************************************************* */

#define ANSam_trace_offset               PH1_CONST._ANSam_trace_offset

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

typedef struct {
	var_d      fract                       _ANSam_current_sample;
	var_d      fract                       _ANSam_magnitude;
	var_d      fract                       _ANSam_magnitude_lpf;
	var_d      fract                       _ANSam_midpoint_value;
	var_d      fract                       _ANSam_trace_count_2100_imag;
	var_d      fract                       _ANSam_trace_count_2100_real;
	var_d      fract                       _ANSam_trace_imag;
	var_d      fract                       _ANSam_trace_magphase_imag;
	var_d      fract                       _ANSam_trace_magphase_lpf_imag;
	var_d      fract                       _ANSam_trace_magphase_lpf_real;
	var_d      fract                       _ANSam_trace_magphase_max_imag;
	var_d      fract                       _ANSam_trace_magphase_max_real;
	var_d      fract                       _ANSam_trace_magphase_mid_imag;
	var_d      fract                       _ANSam_trace_magphase_mid_real;
	var_d      fract                       _ANSam_trace_magphase_min_imag;
	var_d      fract                       _ANSam_trace_magphase_min_real;
	var_d      fract                       _ANSam_trace_magphase_real;
	var_d      fract                       _ANSam_trace_max_imag;
	var_d      fract                       _ANSam_trace_max_real;
	var_d      fract                       _ANSam_trace_mid_imag;
	var_d      fract                       _ANSam_trace_mid_real;
	var_d      fract                       _ANSam_trace_min_imag;
	var_d      fract                       _ANSam_trace_min_real;
	var_d      fract                       _ANSam_trace_real;
	var_d      fract32                     _ANSam_magnitude_lpf32;
	var_d      fract32                     _ANSam_magnitude_max32;
	var_d      fract32                     _ANSam_magnitude_min32;
	var_d      fract40                     _ANSam_power40;
	var_d      sint15                      _ANSam_count_2100;
	var_d      sint15                      _ANSam_cycle_count;
	var_d      phase_t                     _ANSam_delta_phase;
	var_d      sint15                      _ANSam_max_tracking_count;
	var_d      phase_t                     _ANSam_measured_delta_phase;
	var_d      sint15                      _ANSam_min_tracking_count;
	var_d      phase_t                     _ANSam_phase;
	var_d      sint15                      _ANSam_sample_count;
	var_d      sint15                      _ANSam_trace_count_2100_value;
	var_d      sint15                      _ANSam_trace_index;
	var_d      phase_t                     _ANSam_trace_phase;
	var_d      sint15                      _answ_v8_CJ_count;
	var_d      sint15                      _answ_v8_JM_count;
	var_d      sint15                      _answ_v8_JM_sent;
	var_d      sint15                      _orig_v8_CI_count;
	var_d      sint15                      _orig_v8_CJ_count;
	var_d      sint15                      _orig_v8_CM_count;
	var_d      uint16                      _ANSam_detect_15Hz;
	var_d      uint16                      _ANSam_detect_2100;
	var_d      uint16                      _answ_v8_found_CI;
	var_d      uint16                      _answ_v8_found_CJ;
	var_d      uint16                      _answ_v8_found_CM;
	var_d      uint16                      _orig_v8_CI_sent;
	var_d      uint16                      _orig_v8_CJ_sent;
	var_d      uint16                      _orig_v8_CM_sent;
	var_d      uint16                      _orig_v8_found_ANS;
	var_d      uint16                      _orig_v8_found_ANSam;
	var_d      uint16                      _orig_v8_found_JM;
	var_d      uint16                      _send__v8__call_function;
	var_d      uint16                      _send__v8__gstn_access;
	var_d      uint16                      _send__v8__modulation_modes [3];
	var_d      uint16                      _send__v8__protocols;
} ph1_vars_t;

/* ************************************************************************* */

DEF_DATA(ph1_vars_t, ph1_vars)
#define PH1_VARS_DATA ph1_vars_t ph1_vars
#define PH1_VARS USE_DATA(ph1_vars)
#define ph1_vars_used

/* ************************************************************************* */

#define ANSam_current_sample             PH1_VARS._ANSam_current_sample
#define ANSam_magnitude                  PH1_VARS._ANSam_magnitude
#define ANSam_magnitude_lpf              PH1_VARS._ANSam_magnitude_lpf
#define ANSam_midpoint_value             PH1_VARS._ANSam_midpoint_value
#define ANSam_trace_count_2100_imag      PH1_VARS._ANSam_trace_count_2100_imag
#define ANSam_trace_count_2100_real      PH1_VARS._ANSam_trace_count_2100_real
#define ANSam_trace_imag                 PH1_VARS._ANSam_trace_imag
#define ANSam_trace_magphase_imag        PH1_VARS._ANSam_trace_magphase_imag
#define ANSam_trace_magphase_lpf_imag    PH1_VARS._ANSam_trace_magphase_lpf_imag
#define ANSam_trace_magphase_lpf_real    PH1_VARS._ANSam_trace_magphase_lpf_real
#define ANSam_trace_magphase_max_imag    PH1_VARS._ANSam_trace_magphase_max_imag
#define ANSam_trace_magphase_max_real    PH1_VARS._ANSam_trace_magphase_max_real
#define ANSam_trace_magphase_mid_imag    PH1_VARS._ANSam_trace_magphase_mid_imag
#define ANSam_trace_magphase_mid_real    PH1_VARS._ANSam_trace_magphase_mid_real
#define ANSam_trace_magphase_min_imag    PH1_VARS._ANSam_trace_magphase_min_imag
#define ANSam_trace_magphase_min_real    PH1_VARS._ANSam_trace_magphase_min_real
#define ANSam_trace_magphase_real        PH1_VARS._ANSam_trace_magphase_real
#define ANSam_trace_max_imag             PH1_VARS._ANSam_trace_max_imag
#define ANSam_trace_max_real             PH1_VARS._ANSam_trace_max_real
#define ANSam_trace_mid_imag             PH1_VARS._ANSam_trace_mid_imag
#define ANSam_trace_mid_real             PH1_VARS._ANSam_trace_mid_real
#define ANSam_trace_min_imag             PH1_VARS._ANSam_trace_min_imag
#define ANSam_trace_min_real             PH1_VARS._ANSam_trace_min_real
#define ANSam_trace_real                 PH1_VARS._ANSam_trace_real
#define ANSam_magnitude_lpf32            PH1_VARS._ANSam_magnitude_lpf32
#define ANSam_magnitude_max32            PH1_VARS._ANSam_magnitude_max32
#define ANSam_magnitude_min32            PH1_VARS._ANSam_magnitude_min32
#define ANSam_power40                    PH1_VARS._ANSam_power40
#define ANSam_count_2100                 PH1_VARS._ANSam_count_2100
#define ANSam_cycle_count                PH1_VARS._ANSam_cycle_count
#define ANSam_delta_phase                PH1_VARS._ANSam_delta_phase
#define ANSam_max_tracking_count         PH1_VARS._ANSam_max_tracking_count
#define ANSam_measured_delta_phase       PH1_VARS._ANSam_measured_delta_phase
#define ANSam_min_tracking_count         PH1_VARS._ANSam_min_tracking_count
#define ANSam_phase                      PH1_VARS._ANSam_phase
#define ANSam_sample_count               PH1_VARS._ANSam_sample_count
#define ANSam_trace_count_2100_value     PH1_VARS._ANSam_trace_count_2100_value
#define ANSam_trace_index                PH1_VARS._ANSam_trace_index
#define ANSam_trace_phase                PH1_VARS._ANSam_trace_phase
#define answ_v8_CJ_count                 PH1_VARS._answ_v8_CJ_count
#define answ_v8_JM_count                 PH1_VARS._answ_v8_JM_count
#define answ_v8_JM_sent                  PH1_VARS._answ_v8_JM_sent
#define orig_v8_CI_count                 PH1_VARS._orig_v8_CI_count
#define orig_v8_CJ_count                 PH1_VARS._orig_v8_CJ_count
#define orig_v8_CM_count                 PH1_VARS._orig_v8_CM_count
#define ANSam_detect_15Hz                PH1_VARS._ANSam_detect_15Hz
#define ANSam_detect_2100                PH1_VARS._ANSam_detect_2100
#define answ_v8_found_CI                 PH1_VARS._answ_v8_found_CI
#define answ_v8_found_CJ                 PH1_VARS._answ_v8_found_CJ
#define answ_v8_found_CM                 PH1_VARS._answ_v8_found_CM
#define orig_v8_CI_sent                  PH1_VARS._orig_v8_CI_sent
#define orig_v8_CJ_sent                  PH1_VARS._orig_v8_CJ_sent
#define orig_v8_CM_sent                  PH1_VARS._orig_v8_CM_sent
#define orig_v8_found_ANS                PH1_VARS._orig_v8_found_ANS
#define orig_v8_found_ANSam              PH1_VARS._orig_v8_found_ANSam
#define orig_v8_found_JM                 PH1_VARS._orig_v8_found_JM
#define send__v8__call_function          PH1_VARS._send__v8__call_function
#define send__v8__gstn_access            PH1_VARS._send__v8__gstn_access
#define send__v8__modulation_modes       PH1_VARS._send__v8__modulation_modes
#define send__v8__protocols              PH1_VARS._send__v8__protocols

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

typedef struct {
	stat_d     uint16                      _stat__v8_disconnect_reason;
	stat_d     uint16                      _stat__v8__call_function;
	stat_d     uint16                      _stat__v8__gstn_access;
	stat_d     uint16                      _stat__v8__modulation_modes [3];
	stat_d     uint16                      _stat__v8__protocols;
} ph1_stats_t;

/* ************************************************************************* */

DEF_DATA(ph1_stats_t, ph1_stats)
#define PH1_STATS_DATA ph1_stats_t ph1_stats
#define PH1_STATS USE_DATA(ph1_stats)
#define ph1_stats_used

/* ************************************************************************* */

#define stat__v8_disconnect_reason       PH1_STATS._stat__v8_disconnect_reason
#define stat__v8__call_function          PH1_STATS._stat__v8__call_function
#define stat__v8__gstn_access            PH1_STATS._stat__v8__gstn_access
#define stat__v8__modulation_modes       PH1_STATS._stat__v8__modulation_modes
#define stat__v8__protocols              PH1_STATS._stat__v8__protocols

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

typedef struct {
	debug_d    bool                        _orig_v8_allow_ANSam;
	debug_d    bool                        _orig_v8_allow_very_short_ANSam;
	debug_d    sint31                      _v8_tx_count;
	debug_d    uint16                      _answ_v8_allow_CM_detection;
	debug_d    uint16                      _answ_v8_use_15Hz;
	debug_d    uint16                      _answ_v8_use_invert;
	debug_d    uint16                      _v8_rx_sync_code;
	debug_d    uint16                      _v8_tx_state;
	debug_d    uint16                      _v8_tx_sync_code;
	debug_d    uint16                      _v8_rx_state;
} ph1_debug_t;

/* ************************************************************************* */

DEF_DATA(ph1_debug_t, ph1_debug)
#define PH1_DEBUG_DATA ph1_debug_t ph1_debug
#define PH1_DEBUG USE_DATA(ph1_debug)
#define ph1_debug_used

/* ************************************************************************* */

#define orig_v8_allow_ANSam              PH1_DEBUG._orig_v8_allow_ANSam
#define orig_v8_allow_very_short_ANSam   PH1_DEBUG._orig_v8_allow_very_short_ANSam
#define v8_tx_count                      PH1_DEBUG._v8_tx_count
#define answ_v8_allow_CM_detection       PH1_DEBUG._answ_v8_allow_CM_detection
#define answ_v8_use_15Hz                 PH1_DEBUG._answ_v8_use_15Hz
#define answ_v8_use_invert               PH1_DEBUG._answ_v8_use_invert
#define v8_rx_sync_code                  PH1_DEBUG._v8_rx_sync_code
#define v8_tx_state                      PH1_DEBUG._v8_tx_state
#define v8_tx_sync_code                  PH1_DEBUG._v8_tx_sync_code
#define v8_rx_state                      PH1_DEBUG._v8_rx_state

/* ************************************************************************* */

#endif /* _DATA_PH1_H */
