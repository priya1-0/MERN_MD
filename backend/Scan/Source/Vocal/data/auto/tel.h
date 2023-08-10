
/* ************************************************************************* */
/*
 *	tel.h
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
 *	This file contains automatically generated data for tel.
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

#ifndef _DATA_TEL_H
#define _DATA_TEL_H
#include "data/sections.h"

/* ************************************************************************* */

typedef struct {
	var_d      uint16                      _rd_decimate;
	var_d      bool                        _rd_prev_was_off;
	var_d      uint16                      _rd_period_cnt;
	var_d      uint16                      _rd_criteria_duration;
	var_d      uint16                      _rd_metric;
	var_d      uint16                      _rd_cadence_history_1;
	var_d      uint16                      _rd_cadence_history_2;
	var_d      uint16                      _rd_period_beyond_range;
	var_d      fract                       _cp_biquad_data_buffer [26];
	var_d      uint16                      _telephony_temp;
} tel_vars_t;

/* ************************************************************************* */

DEF_DATA(tel_vars_t, tel_vars)
#define TEL_VARS_DATA tel_vars_t tel_vars
#define TEL_VARS USE_DATA(tel_vars)
#define tel_vars_used

/* ************************************************************************* */

#define rd_decimate                      TEL_VARS._rd_decimate
#define rd_prev_was_off                  TEL_VARS._rd_prev_was_off
#define rd_period_cnt                    TEL_VARS._rd_period_cnt
#define rd_criteria_duration             TEL_VARS._rd_criteria_duration
#define rd_metric                        TEL_VARS._rd_metric
#define rd_cadence_history_1             TEL_VARS._rd_cadence_history_1
#define rd_cadence_history_2             TEL_VARS._rd_cadence_history_2
#define rd_period_beyond_range           TEL_VARS._rd_period_beyond_range
#define cp_biquad_data_buffer            TEL_VARS._cp_biquad_data_buffer
#define telephony_temp                   TEL_VARS._telephony_temp

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

typedef struct {
	parm_d     uint16                      _parm__pulse_make_time;
	parm_d     uint16                      _parm__pulse_break_time;
	parm_d     uint16                      _parm__pulse_delay_time;
} tel_parms_t;

/* ************************************************************************* */

DEF_DATA(tel_parms_t, tel_parms)
#define TEL_PARMS_DATA tel_parms_t tel_parms
#define TEL_PARMS USE_DATA(tel_parms)
#define tel_parms_used

/* ************************************************************************* */

#define parm__pulse_make_time            TEL_PARMS._parm__pulse_make_time
#define parm__pulse_break_time           TEL_PARMS._parm__pulse_break_time
#define parm__pulse_delay_time           TEL_PARMS._parm__pulse_delay_time

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

typedef struct {
	stat_d     bool                        _stat__cp_rd_ring_energy_active;
	stat_d     bool                        _stat__cp_rd_within_detect;
	stat_d     uint16                      _stat__cp_rd_energy_on_time;
	stat_d     uint16                      _stat__call_progress_cadence_detect_mask;
	stat_d     uint16                      _stat__call_progress_tone_detect_mask;
} tel_stats_t;

/* ************************************************************************* */

DEF_DATA(tel_stats_t, tel_stats)
#define TEL_STATS_DATA tel_stats_t tel_stats
#define TEL_STATS USE_DATA(tel_stats)
#define tel_stats_used

/* ************************************************************************* */

#define stat__cp_rd_ring_energy_active   TEL_STATS._stat__cp_rd_ring_energy_active
#define stat__cp_rd_within_detect        TEL_STATS._stat__cp_rd_within_detect
#define stat__cp_rd_energy_on_time       TEL_STATS._stat__cp_rd_energy_on_time
#define stat__call_progress_cadence_detect_mask TEL_STATS._stat__call_progress_cadence_detect_mask
#define stat__call_progress_tone_detect_mask TEL_STATS._stat__call_progress_tone_detect_mask

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

typedef struct {
	debug_d    fract                       _cp_hysteresis;
	debug_d    fract                       _cp_relative_energy;
	debug_d    fract                       _cp_threshold;
	debug_d    sint15                      _cp_average_counter;
	debug_d    sint15                      _cp_change_counter;
	debug_d    sint15                      _cp_detected;
	debug_d    sint15                      _cp_keep_counter;
	debug_d    sint15                      _cp_output;
	debug_d    sint15                      _cp_state;
	debug_d    sint15                      _cp_decimate;
	debug_d    sint15                      _false_hit_miss_limit;
	debug_d    sint15                      _false_miss_hit_limit;
	debug_d    sint15                      _silence_average_counter;
	debug_d    sint15                      _silence_change_counter;
	debug_d    sint15                      _silence_keep_counter;
	debug_d    sint15                      _silence_output;
	debug_d    sint15                      _silence_state;
	debug_d    sint15                      _tone_detect_delay;
	debug_d    sint15                      _valid_hit_limit;
	debug_d    sint15                      _valid_miss_limit;
	debug_d    cpd_t                       _cp_data [CP_TABLE_ENTRY_NUM];
	debug_d    sint15                      _cp_valid;
	debug_d    sint15                      _silence_valid;
	debug_d    tone_detector_vars_t        _tone_detector_variables [NUMBER_MAX_TONE_DETECTORS+1];
	debug_d    uint16                      _cp_active_change;
	debug_d    uint16                      _cp_previous;
	debug_d    uint16                      _cp_status_bit;
	debug_d    int                         _tone_detector_num_tones;
	debug_d    fract                       _tone_detector_slew_rate;
	debug_d    const tone_detector_coef_t* _tone_detector_constants;
} tel_debug_t;

/* ************************************************************************* */

DEF_DATA(tel_debug_t, tel_debug)
#define TEL_DEBUG_DATA tel_debug_t tel_debug
#define TEL_DEBUG USE_DATA(tel_debug)
#define tel_debug_used

/* ************************************************************************* */

#define cp_hysteresis                    TEL_DEBUG._cp_hysteresis
#define cp_relative_energy               TEL_DEBUG._cp_relative_energy
#define cp_threshold                     TEL_DEBUG._cp_threshold
#define cp_average_counter               TEL_DEBUG._cp_average_counter
#define cp_change_counter                TEL_DEBUG._cp_change_counter
#define cp_detected                      TEL_DEBUG._cp_detected
#define cp_keep_counter                  TEL_DEBUG._cp_keep_counter
#define cp_output                        TEL_DEBUG._cp_output
#define cp_state                         TEL_DEBUG._cp_state
#define cp_decimate                      TEL_DEBUG._cp_decimate
#define false_hit_miss_limit             TEL_DEBUG._false_hit_miss_limit
#define false_miss_hit_limit             TEL_DEBUG._false_miss_hit_limit
#define silence_average_counter          TEL_DEBUG._silence_average_counter
#define silence_change_counter           TEL_DEBUG._silence_change_counter
#define silence_keep_counter             TEL_DEBUG._silence_keep_counter
#define silence_output                   TEL_DEBUG._silence_output
#define silence_state                    TEL_DEBUG._silence_state
#define tone_detect_delay                TEL_DEBUG._tone_detect_delay
#define valid_hit_limit                  TEL_DEBUG._valid_hit_limit
#define valid_miss_limit                 TEL_DEBUG._valid_miss_limit
#define cp_data                          TEL_DEBUG._cp_data
#define cp_valid                         TEL_DEBUG._cp_valid
#define silence_valid                    TEL_DEBUG._silence_valid
#define tone_detector_variables          TEL_DEBUG._tone_detector_variables
#define cp_active_change                 TEL_DEBUG._cp_active_change
#define cp_previous                      TEL_DEBUG._cp_previous
#define cp_status_bit                    TEL_DEBUG._cp_status_bit
#define tone_detector_num_tones          TEL_DEBUG._tone_detector_num_tones
#define tone_detector_slew_rate          TEL_DEBUG._tone_detector_slew_rate
#define tone_detector_constants          TEL_DEBUG._tone_detector_constants

/* ************************************************************************* */

#endif /* _DATA_TEL_H */
