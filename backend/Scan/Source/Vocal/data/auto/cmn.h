
/* ************************************************************************* */
/*
 *	cmn.h
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
 *	This file contains automatically generated data for cmn.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.3  2010/02/16 21:58:36  zhangn1
 *	Revision History:	SCR #186247. Incorporate South Africa Tx Tone
 *	Revision History:	
 *	Revision History:	Revision 1.1.6.2  2009/04/28 19:12:25  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _DATA_CMN_H
#define _DATA_CMN_H
#include "data/sections.h"

/* ************************************************************************* */

typedef struct {
	const_d    fract                       _BAUD_AGC_REFERENCE;
	const_d    fract                       _BAUD_PLL_CLOCK_SCALE;
	const_d    fract                       _BAUD_PLL_FREQ_ERROR_RATIO;
	const_d    fract                       _DCD_HYSTERESIS;
	const_d    fract                       _DELTA_HYSTERESIS;
	const_d    fract                       _DELTA_REF_LEVEL;
	const_d    fract                       _DELTA_SLEW_RATE;
	const_d    sint15                      _DELTA_INTEGRATION_TIME;
	const_d    fract                       _ANSAM_LOWER_THRESHOLD;
	const_d    fract                       _ANSAM_LPF_SLEW_1ST;
	const_d    fract                       _ANSAM_LPF_SLEW_2ND;
	const_d    fract                       _ANSAM_MAGNITUDE_LIMIT;
	const_d    fract                       _ANSAM_UPPER_THRESHOLD;
	const_d    sint15                      _ANSAM_2100_MAX;
	const_d    sint15                      _ANSAM_2100_MAX_x2;
	const_d    sint15                      _ANSAM_CYCLE_COUNT_MAX;
	const_d    phase_t                     _ANSAM_DELTA_PHASE_LIMIT;
	const_d    sint15                      _ANSAM_MAX_SAMPLES_PLUS_1;
	const_d    sint15                      _ANSAM_MIN_SAMPLES;
	const_d    sint15                      _ANSAM_TRACKING_LIMIT;
	const_d    sint15                      _PH2S_INFO0_ACK_LIMIT;
	const_d    uint16                      _ANSW_V8_CJ_COUNT_MIN;
	const_d    uint16                      _ANSW_V8_JM_COUNT_NOM;
	const_d    uint16                      _baud_tx_break_duration;
	const_d    fract                       _CORRELATOR_FIT_THRESHOLD;
	const_d    fract                       _DELTA_ENERGY_THRESHOLD;
	const_d    sint15                      _HIT_COUNTER_INIT;
	const_d    sint15                      _REVERSAL_TIMEOUT_INIT;
} cmn_const_t;

/* ************************************************************************* */

DEF_DATA(cmn_const_t, cmn_const)
#define CMN_CONST_DATA cmn_const_t cmn_const
#define CMN_CONST USE_DATA(cmn_const)
#define cmn_const_used

/* ************************************************************************* */

#define BAUD_AGC_REFERENCE               CMN_CONST._BAUD_AGC_REFERENCE
#define BAUD_PLL_CLOCK_SCALE             CMN_CONST._BAUD_PLL_CLOCK_SCALE
#define BAUD_PLL_FREQ_ERROR_RATIO        CMN_CONST._BAUD_PLL_FREQ_ERROR_RATIO
#define DCD_HYSTERESIS                   CMN_CONST._DCD_HYSTERESIS
#define DELTA_HYSTERESIS                 CMN_CONST._DELTA_HYSTERESIS
#define DELTA_REF_LEVEL                  CMN_CONST._DELTA_REF_LEVEL
#define DELTA_SLEW_RATE                  CMN_CONST._DELTA_SLEW_RATE
#define DELTA_INTEGRATION_TIME           CMN_CONST._DELTA_INTEGRATION_TIME
#define ANSAM_LOWER_THRESHOLD            CMN_CONST._ANSAM_LOWER_THRESHOLD
#define ANSAM_LPF_SLEW_1ST               CMN_CONST._ANSAM_LPF_SLEW_1ST
#define ANSAM_LPF_SLEW_2ND               CMN_CONST._ANSAM_LPF_SLEW_2ND
#define ANSAM_MAGNITUDE_LIMIT            CMN_CONST._ANSAM_MAGNITUDE_LIMIT
#define ANSAM_UPPER_THRESHOLD            CMN_CONST._ANSAM_UPPER_THRESHOLD
#define ANSAM_2100_MAX                   CMN_CONST._ANSAM_2100_MAX
#define ANSAM_2100_MAX_x2                CMN_CONST._ANSAM_2100_MAX_x2
#define ANSAM_CYCLE_COUNT_MAX            CMN_CONST._ANSAM_CYCLE_COUNT_MAX
#define ANSAM_DELTA_PHASE_LIMIT          CMN_CONST._ANSAM_DELTA_PHASE_LIMIT
#define ANSAM_MAX_SAMPLES_PLUS_1         CMN_CONST._ANSAM_MAX_SAMPLES_PLUS_1
#define ANSAM_MIN_SAMPLES                CMN_CONST._ANSAM_MIN_SAMPLES
#define ANSAM_TRACKING_LIMIT             CMN_CONST._ANSAM_TRACKING_LIMIT
#define PH2S_INFO0_ACK_LIMIT             CMN_CONST._PH2S_INFO0_ACK_LIMIT
#define ANSW_V8_CJ_COUNT_MIN             CMN_CONST._ANSW_V8_CJ_COUNT_MIN
#define ANSW_V8_JM_COUNT_NOM             CMN_CONST._ANSW_V8_JM_COUNT_NOM
#define baud_tx_break_duration           CMN_CONST._baud_tx_break_duration
#define CORRELATOR_FIT_THRESHOLD         CMN_CONST._CORRELATOR_FIT_THRESHOLD
#define DELTA_ENERGY_THRESHOLD           CMN_CONST._DELTA_ENERGY_THRESHOLD
#define HIT_COUNTER_INIT                 CMN_CONST._HIT_COUNTER_INIT
#define REVERSAL_TIMEOUT_INIT            CMN_CONST._REVERSAL_TIMEOUT_INIT

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

typedef struct {
	var_d      fract32                     _echo_canceller_error_sum;
	var_d      int                         _echo_canceller_display_counter;
	var_d      int                         _echo_canceller_display_decimate;
	var_d      int                         _echo_canceller_debug_display_offset;
	var_d      sint15                      _sys_number_missed_samples_max;
	var_d      uint16                      _baud_rx_data_unit;
	var_d      event_t                     _fg_event_queue [NUMBER_OF_FG_EVENTS];
	var_d      state_list_t                _fg_state_list [NUMBER_OF_FG_STATES];
	var_d      timer_list_t                _fg_timer_list [NUMBER_OF_FG_TIMERS];
	var_d      state_list_t                _bg_state_list [NUMBER_OF_BG_STATES];
	var_d      int                         _number_bg_states;
	var_d      int                         _current_bg_state;
	var_d      bool                        _current_bg_state_active;
	var_d      event_t                     _bgkernel_current_event;
	var_d      uint16                      _bgkernel_current_svalue;
	var_d      bool                        _within_bg_state_update;
	var_d      timer_list_t                _bg_timer_list [NUMBER_OF_BG_TIMERS];
	var_d      int                         _number_bg_timers;
	var_d      uint16                      _bg_kernel_anomaly;
	var_d      uint16                      _fg_kernel_anomaly;
	var_d      task_t                      _bg_task_table [NUMBER_OF_BG_TASKS];
	var_d      bool                        _within_task_update;
	var_d      bool                        _current_bg_task_active;
	var_d      int                         _number_bg_tasks;
	var_d      event_t                     _bg_task_event;
	var_d      int                         _current_bg_task;
	var_d      ident_t                     _fg_thread_idents [NUMBER_OF_TOTAL_THREAD_COMP];
	var_d      powr_measurement_t          _rx_measurment_buffer_1;
	var_d      powr_measurement_t          _tx_measurment_buffer_1;
	var_d      fract                       _tone_detector_data [TONE_DETECTOR_DECIMATE];
	var_d      fract                       _PH2P_ANAL_16PT_NOISE_LIMIT;
	var_d      fract                       _PH2P_ANAL_CENTER_ENERGY_WEIGHT;
	var_d      fract                       _PH2P_ANAL_DEMOD_ENERGY_LOSS;
	var_d      fract                       _PH2P_ANAL_MSE_CORRECT;
	var_d      fract                       _PH2P_ANAL_NOISE_THRESHOLD;
	var_d      fract                       _PH2P_ANAL_PREEQ_ENERGY_LOSS;
	var_d      fract                       _PH2P_ANAL_TEST_REQUIRED_GAIN;
	var_d      fract                       _PH2P_ANAL_THD_THRESHOLD;
	var_d      fract                       _PH2P_ANAL_TRANSMIT_GAIN;
	var_d      fract                       _PH2_RX_DCD_HYSTERESIS;
	var_d      fract *                     _ph2_log_power_input_pointer;
	var_d      sint15                      _clock_cycles_per_baud;
	var_d      sint15                      _PH2P_ANAL_TEST_CARRIER_FREQUENCY;
	var_d      sint15                      _PH2P_ANAL_TEST_PREEMPH_VALUE;
	var_d      sint15                      _PH2P_ANAL_TEST_SYMBOL_RATE;
	var_d      sint15                      _PH2P_BG_CALCULATE_NORM_POWER;
	var_d      sint15                      _PH2P_FEFO_DW_K_GAIN_MARGIN;
	var_d      sint15                      _PH2P_FEFO_GAIN_MARGIN;
	var_d      sint15                      _PH2P_POWR_GAIN_MARGIN;
	var_d      sint15                      _PH2P_POWR_L1_FINAL_TUNE;
	var_d      sint15                      _PH2P_POWR_L2_FINAL_TUNE;
	var_d      sint15                      _PH2P_POWR_LX_FINAL_ROUNDING;
	var_d      sint15                      _PH2P_POWR_LX_INITIAL_ROUNDING;
	var_d      sint15                      _PH2P_POWR_LX_INITIAL_TUNE;
	var_d      sint15                      _PH2P_POWR_NOISE_ADJ_EXPONENT;
	var_d      sint15                      _PH2P_POWR_RX_CLEAR_INIT;
	var_d      uint16                      _PH2P_ANAL_TEST_ENABLE;
	var_d      uint16                      _PH2P_ANAL_USE_SHAPING;
	var_d      uint16                      _PH2P_BG_SAMPLE_OFFSET_LENGTH;
	var_d      uint16                      _PH2S_LEN_T_DATA_TIMEOUT;
	var_d      uint16                      _PH2_RX_OFFSET_LENGTH;
	var_d      uint16                      _PH2_RX_PROBING_OFFSET_LENGTH;
	var_d      uint16                      _PH2_TX_OFFSET_LENGTH;
	var_d      uint16                      _sys_number_missed_8K0_samples;
	var_d      thread_routine_t            _mg_run_entry_pointer;
	var_d      uint16                      _v34n_rxtx_call_direction;
	var_d      sint15                      _tone_generator_silence;
	var_d      sint15                      _tone_generator_previous;
} cmn_vars_t;

/* ************************************************************************* */

DEF_DATA(cmn_vars_t, cmn_vars)
#define CMN_VARS_DATA cmn_vars_t cmn_vars
#define CMN_VARS USE_DATA(cmn_vars)
#define cmn_vars_used

/* ************************************************************************* */

#define echo_canceller_error_sum         CMN_VARS._echo_canceller_error_sum
#define echo_canceller_display_counter   CMN_VARS._echo_canceller_display_counter
#define echo_canceller_display_decimate  CMN_VARS._echo_canceller_display_decimate
#define echo_canceller_debug_display_offset CMN_VARS._echo_canceller_debug_display_offset
#define sys_number_missed_samples_max    CMN_VARS._sys_number_missed_samples_max
#define baud_rx_data_unit                CMN_VARS._baud_rx_data_unit
#define fg_event_queue                   CMN_VARS._fg_event_queue
#define fg_state_list                    CMN_VARS._fg_state_list
#define fg_timer_list                    CMN_VARS._fg_timer_list
#define bg_state_list                    CMN_VARS._bg_state_list
#define number_bg_states                 CMN_VARS._number_bg_states
#define current_bg_state                 CMN_VARS._current_bg_state
#define current_bg_state_active          CMN_VARS._current_bg_state_active
#define bgkernel_current_event           CMN_VARS._bgkernel_current_event
#define bgkernel_current_svalue          CMN_VARS._bgkernel_current_svalue
#define within_bg_state_update           CMN_VARS._within_bg_state_update
#define bg_timer_list                    CMN_VARS._bg_timer_list
#define number_bg_timers                 CMN_VARS._number_bg_timers
#define bg_kernel_anomaly                CMN_VARS._bg_kernel_anomaly
#define fg_kernel_anomaly                CMN_VARS._fg_kernel_anomaly
#define bg_task_table                    CMN_VARS._bg_task_table
#define within_task_update               CMN_VARS._within_task_update
#define current_bg_task_active           CMN_VARS._current_bg_task_active
#define number_bg_tasks                  CMN_VARS._number_bg_tasks
#define bg_task_event                    CMN_VARS._bg_task_event
#define current_bg_task                  CMN_VARS._current_bg_task
#define fg_thread_idents                 CMN_VARS._fg_thread_idents
#define rx_measurment_buffer_1           CMN_VARS._rx_measurment_buffer_1
#define tx_measurment_buffer_1           CMN_VARS._tx_measurment_buffer_1
#define tone_detector_data               CMN_VARS._tone_detector_data
#define PH2P_ANAL_16PT_NOISE_LIMIT       CMN_VARS._PH2P_ANAL_16PT_NOISE_LIMIT
#define PH2P_ANAL_CENTER_ENERGY_WEIGHT   CMN_VARS._PH2P_ANAL_CENTER_ENERGY_WEIGHT
#define PH2P_ANAL_DEMOD_ENERGY_LOSS      CMN_VARS._PH2P_ANAL_DEMOD_ENERGY_LOSS
#define PH2P_ANAL_MSE_CORRECT            CMN_VARS._PH2P_ANAL_MSE_CORRECT
#define PH2P_ANAL_NOISE_THRESHOLD        CMN_VARS._PH2P_ANAL_NOISE_THRESHOLD
#define PH2P_ANAL_PREEQ_ENERGY_LOSS      CMN_VARS._PH2P_ANAL_PREEQ_ENERGY_LOSS
#define PH2P_ANAL_TEST_REQUIRED_GAIN     CMN_VARS._PH2P_ANAL_TEST_REQUIRED_GAIN
#define PH2P_ANAL_THD_THRESHOLD          CMN_VARS._PH2P_ANAL_THD_THRESHOLD
#define PH2P_ANAL_TRANSMIT_GAIN          CMN_VARS._PH2P_ANAL_TRANSMIT_GAIN
#define PH2_RX_DCD_HYSTERESIS            CMN_VARS._PH2_RX_DCD_HYSTERESIS
#define ph2_log_power_input_pointer      CMN_VARS._ph2_log_power_input_pointer
#define clock_cycles_per_baud            CMN_VARS._clock_cycles_per_baud
#define PH2P_ANAL_TEST_CARRIER_FREQUENCY CMN_VARS._PH2P_ANAL_TEST_CARRIER_FREQUENCY
#define PH2P_ANAL_TEST_PREEMPH_VALUE     CMN_VARS._PH2P_ANAL_TEST_PREEMPH_VALUE
#define PH2P_ANAL_TEST_SYMBOL_RATE       CMN_VARS._PH2P_ANAL_TEST_SYMBOL_RATE
#define PH2P_BG_CALCULATE_NORM_POWER     CMN_VARS._PH2P_BG_CALCULATE_NORM_POWER
#define PH2P_FEFO_DW_K_GAIN_MARGIN       CMN_VARS._PH2P_FEFO_DW_K_GAIN_MARGIN
#define PH2P_FEFO_GAIN_MARGIN            CMN_VARS._PH2P_FEFO_GAIN_MARGIN
#define PH2P_POWR_GAIN_MARGIN            CMN_VARS._PH2P_POWR_GAIN_MARGIN
#define PH2P_POWR_L1_FINAL_TUNE          CMN_VARS._PH2P_POWR_L1_FINAL_TUNE
#define PH2P_POWR_L2_FINAL_TUNE          CMN_VARS._PH2P_POWR_L2_FINAL_TUNE
#define PH2P_POWR_LX_FINAL_ROUNDING      CMN_VARS._PH2P_POWR_LX_FINAL_ROUNDING
#define PH2P_POWR_LX_INITIAL_ROUNDING    CMN_VARS._PH2P_POWR_LX_INITIAL_ROUNDING
#define PH2P_POWR_LX_INITIAL_TUNE        CMN_VARS._PH2P_POWR_LX_INITIAL_TUNE
#define PH2P_POWR_NOISE_ADJ_EXPONENT     CMN_VARS._PH2P_POWR_NOISE_ADJ_EXPONENT
#define PH2P_POWR_RX_CLEAR_INIT          CMN_VARS._PH2P_POWR_RX_CLEAR_INIT
#define PH2P_ANAL_TEST_ENABLE            CMN_VARS._PH2P_ANAL_TEST_ENABLE
#define PH2P_ANAL_USE_SHAPING            CMN_VARS._PH2P_ANAL_USE_SHAPING
#define PH2P_BG_SAMPLE_OFFSET_LENGTH     CMN_VARS._PH2P_BG_SAMPLE_OFFSET_LENGTH
#define PH2S_LEN_T_DATA_TIMEOUT          CMN_VARS._PH2S_LEN_T_DATA_TIMEOUT
#define PH2_RX_OFFSET_LENGTH             CMN_VARS._PH2_RX_OFFSET_LENGTH
#define PH2_RX_PROBING_OFFSET_LENGTH     CMN_VARS._PH2_RX_PROBING_OFFSET_LENGTH
#define PH2_TX_OFFSET_LENGTH             CMN_VARS._PH2_TX_OFFSET_LENGTH
#define sys_number_missed_8K0_samples    CMN_VARS._sys_number_missed_8K0_samples
#define mg_run_entry_pointer             CMN_VARS._mg_run_entry_pointer
#define v34n_rxtx_call_direction         CMN_VARS._v34n_rxtx_call_direction
#define tone_generator_silence           CMN_VARS._tone_generator_silence
#define tone_generator_previous          CMN_VARS._tone_generator_previous

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

typedef struct {
	parm_d     uint16                      _parm__dm_carrier_detect_duration;
	parm_d     uint16                      _parm__dm_carrier_loss_disconnect_duration;
	parm_d     uint16                      _parm__dm_line_quality_monitor_mode;
	parm_d     uint16                      _parm__dm_options_mask;
	parm_d     uint16                      _parm__dm_v32_rate_en_mask;
	parm_d     uint16                      _parm__pump_data_modes;
	parm_d     uint16                      _parm__sart_rx_mode;
	parm_d     uint16                      _parm__sart_tx_mode;
	parm_d     ufract                      _parm__tone_transmit_level;
	parm_d     uint16                      _parm__call_progress_cadence_detect_mask;
	parm_d     uint16                      _parm__cp_rd_above_range_metric;
	parm_d     uint16                      _parm__cp_rd_below_range_metric;
	parm_d     uint16                      _parm__cp_rd_cycle_period_max;
	parm_d     uint16                      _parm__cp_rd_cycle_period_min;
	parm_d     uint16                      _parm__cp_rd_decimate_cnt;
	parm_d     uint16                      _parm__cp_rd_energy_off_duration;
	parm_d     uint16                      _parm__cp_rd_inc_detect_duration;
	parm_d     uint16                      _parm__cp_rd_min_detect_duration;
	parm_d     uint16                      _parm__cp_rd_qualify_metric;
	parm_d     ufract                      _parm__dtmf_high_tone_level;
	parm_d     ufract                      _parm__dtmf_low_tone_level;
	parm_d     uint16                      _parm__tel_digit;
	parm_d     uint16                      _parm__spk_monitor_tx_gain;
	parm_d     uint16                      _parm__spk_monitor_rx_gain;
	parm_d     fract                       _parm__dm_v34_mse_cmn_bias;
	parm_d     fract                       _parm__dm_v34_mse_data_bias;
	parm_d     fract                       _parm__dm_v34_mse_fallback;
	parm_d     fract                       _parm__dm_v34_mse_fallforward;
	parm_d     fract                       _parm__dm_v34_mse_trn_bias;
	parm_d     ufract                      _parm__pump_v34_transmit_level;
	parm_d     uint16                      _parm__dm_v34_carrier_mask;
	parm_d     uint16                      _parm__dm_v34_data_rate_mask;
	parm_d     uint16                      _parm__dm_v34_options_mask;
	parm_d     uint16                      _parm__dm_v34_ptt_carrier_mask;
	parm_d     uint16                      _parm__dm_v34_ptt_restriction_mask;
	parm_d     uint16                      _parm__dm_v34_symbol_difference_max;
	parm_d     uint16                      _parm__dm_v34_trellis_num;
	parm_d     uint16                      _parm__tel_answer_tone_length;
	parm_d     uint16                      _parm__v8__call_function;
	parm_d     uint16                      _parm__v8__gstn_access;
	parm_d     uint16                      _parm__v8__modulation_modes [3];
	parm_d     uint16                      _parm__v8__protocols;
} cmn_parms_t;

/* ************************************************************************* */

DEF_DATA(cmn_parms_t, cmn_parms)
#define CMN_PARMS_DATA cmn_parms_t cmn_parms
#define CMN_PARMS USE_DATA(cmn_parms)
#define cmn_parms_used

/* ************************************************************************* */

#define parm__dm_carrier_detect_duration CMN_PARMS._parm__dm_carrier_detect_duration
#define parm__dm_carrier_loss_disconnect_duration CMN_PARMS._parm__dm_carrier_loss_disconnect_duration
#define parm__dm_line_quality_monitor_mode CMN_PARMS._parm__dm_line_quality_monitor_mode
#define parm__dm_options_mask            CMN_PARMS._parm__dm_options_mask
#define parm__dm_v32_rate_en_mask        CMN_PARMS._parm__dm_v32_rate_en_mask
#define parm__pump_data_modes            CMN_PARMS._parm__pump_data_modes
#define parm__sart_rx_mode               CMN_PARMS._parm__sart_rx_mode
#define parm__sart_tx_mode               CMN_PARMS._parm__sart_tx_mode
#define parm__tone_transmit_level        CMN_PARMS._parm__tone_transmit_level
#define parm__call_progress_cadence_detect_mask CMN_PARMS._parm__call_progress_cadence_detect_mask
#define parm__cp_rd_above_range_metric   CMN_PARMS._parm__cp_rd_above_range_metric
#define parm__cp_rd_below_range_metric   CMN_PARMS._parm__cp_rd_below_range_metric
#define parm__cp_rd_cycle_period_max     CMN_PARMS._parm__cp_rd_cycle_period_max
#define parm__cp_rd_cycle_period_min     CMN_PARMS._parm__cp_rd_cycle_period_min
#define parm__cp_rd_decimate_cnt         CMN_PARMS._parm__cp_rd_decimate_cnt
#define parm__cp_rd_energy_off_duration  CMN_PARMS._parm__cp_rd_energy_off_duration
#define parm__cp_rd_inc_detect_duration  CMN_PARMS._parm__cp_rd_inc_detect_duration
#define parm__cp_rd_min_detect_duration  CMN_PARMS._parm__cp_rd_min_detect_duration
#define parm__cp_rd_qualify_metric       CMN_PARMS._parm__cp_rd_qualify_metric
#define parm__dtmf_high_tone_level       CMN_PARMS._parm__dtmf_high_tone_level
#define parm__dtmf_low_tone_level        CMN_PARMS._parm__dtmf_low_tone_level
#define parm__tel_digit                  CMN_PARMS._parm__tel_digit
#define parm__spk_monitor_tx_gain        CMN_PARMS._parm__spk_monitor_tx_gain
#define parm__spk_monitor_rx_gain        CMN_PARMS._parm__spk_monitor_rx_gain
#define parm__dm_v34_mse_cmn_bias        CMN_PARMS._parm__dm_v34_mse_cmn_bias
#define parm__dm_v34_mse_data_bias       CMN_PARMS._parm__dm_v34_mse_data_bias
#define parm__dm_v34_mse_fallback        CMN_PARMS._parm__dm_v34_mse_fallback
#define parm__dm_v34_mse_fallforward     CMN_PARMS._parm__dm_v34_mse_fallforward
#define parm__dm_v34_mse_trn_bias        CMN_PARMS._parm__dm_v34_mse_trn_bias
#define parm__pump_v34_transmit_level    CMN_PARMS._parm__pump_v34_transmit_level
#define parm__dm_v34_carrier_mask        CMN_PARMS._parm__dm_v34_carrier_mask
#define parm__dm_v34_data_rate_mask      CMN_PARMS._parm__dm_v34_data_rate_mask
#define parm__dm_v34_options_mask        CMN_PARMS._parm__dm_v34_options_mask
#define parm__dm_v34_ptt_carrier_mask    CMN_PARMS._parm__dm_v34_ptt_carrier_mask
#define parm__dm_v34_ptt_restriction_mask CMN_PARMS._parm__dm_v34_ptt_restriction_mask
#define parm__dm_v34_symbol_difference_max CMN_PARMS._parm__dm_v34_symbol_difference_max
#define parm__dm_v34_trellis_num         CMN_PARMS._parm__dm_v34_trellis_num
#define parm__tel_answer_tone_length     CMN_PARMS._parm__tel_answer_tone_length
#define parm__v8__call_function          CMN_PARMS._parm__v8__call_function
#define parm__v8__gstn_access            CMN_PARMS._parm__v8__gstn_access
#define parm__v8__modulation_modes       CMN_PARMS._parm__v8__modulation_modes
#define parm__v8__protocols              CMN_PARMS._parm__v8__protocols

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

typedef struct {
	stat_d     uint16                      _stat__dm_carrier_code;
	stat_d     uint16                      _stat__dm_rx_bits_per_symbol;
	stat_d     uint16                      _stat__dm_state;
	stat_d     uint16                      _stat__dm_tx_bits_per_symbol;
	stat_d     uint16                      _stat__dm_tx_data_rate;
	stat_d     uint16                      _stat__sart_rx_mode;
	stat_d     uint16                      _stat__sart_tx_mode;
	stat_d     sint15                      _stat__rx_level_dbm;
	stat_d     sint15                      _stat__tx_level_dbm;
	stat_d     uint16                      _stat__tone_detect_mask;
} cmn_stats_t;

/* ************************************************************************* */

DEF_DATA(cmn_stats_t, cmn_stats)
#define CMN_STATS_DATA cmn_stats_t cmn_stats
#define CMN_STATS USE_DATA(cmn_stats)
#define cmn_stats_used

/* ************************************************************************* */

#define stat__dm_carrier_code            CMN_STATS._stat__dm_carrier_code
#define stat__dm_rx_bits_per_symbol      CMN_STATS._stat__dm_rx_bits_per_symbol
#define stat__dm_state                   CMN_STATS._stat__dm_state
#define stat__dm_tx_bits_per_symbol      CMN_STATS._stat__dm_tx_bits_per_symbol
#define stat__dm_tx_data_rate            CMN_STATS._stat__dm_tx_data_rate
#define stat__sart_rx_mode               CMN_STATS._stat__sart_rx_mode
#define stat__sart_tx_mode               CMN_STATS._stat__sart_tx_mode
#define stat__rx_level_dbm               CMN_STATS._stat__rx_level_dbm
#define stat__tx_level_dbm               CMN_STATS._stat__tx_level_dbm
#define stat__tone_detect_mask           CMN_STATS._stat__tone_detect_mask

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

typedef struct {
	debug_d    uint16                      _baud_rx_fsk_oversample;
	debug_d    uint16                      _baud_rx_substate;
	debug_d    uint16                      _baud_rx_no_carrier_flag;
	debug_d    uint16                      _baud_rx_state;
	debug_d    uint16                      _baud_rx_data_dlvd;
	debug_d    uint16                      _baud_tx_state;
	debug_d    uint16                      _baud_rx_bit_cnt;
	debug_d    uint16                      _baud_tx_bit_cnt;
	debug_d    uint16                      _baud_hdlc_frame_start_indicator;
	debug_d    uint16                      _hdlc_lead_flag_cnt;
	debug_d    uint16                      _baud_tx_corrupt_packet_cnt;
	debug_d    uint16                      _baud_tx_unshifted;
	debug_d    uint16                      _baud_rx_crc_lo;
	debug_d    uint16                      _baud_tx_crc_lo;
	debug_d    bool                        _baud_rx_parity_even_space;
	debug_d    bool                        _baud_rx_parity_stick;
	debug_d    bool                        _baud_rx_parity_used;
	debug_d    bool                        _baud_tx_parity_even_space;
	debug_d    bool                        _baud_tx_parity_stick;
	debug_d    bool                        _baud_tx_parity_used;
	debug_d    sint15                      _baud_tx_delete_bit_count;
	debug_d    sint15                      _overlay_8K0_timeout;
	debug_d    uint16                      _ANSW_LEN_MS_ANSam_CI_SEARCH;
	debug_d    uint16                      _ANSW_LEN_MS_CJ_TIMEOUT;
	debug_d    uint16                      _ANSW_LEN_MS_MINIMUM_ANSam;
	debug_d    uint16                      _ANSW_LEN_MS_NOMINAL_JM;
	debug_d    uint16                      _ANSW_LEN_MS_NOMINAL_REVERSAL;
	debug_d    uint16                      _ANSW_LEN_MS_PREWAIT_DELAY;
	debug_d    uint16                      _ANSW_LEN_MS_RLSD_TURNON_DELAY;
	debug_d    uint16                      _ANSW_LEN_MS_SILENCE_DETECT;
	debug_d    uint16                      _baud_rx_data_size_code;
	debug_d    uint16                      _baud_tx_data_size_code;
	debug_d    uint16                      _baud_tx_delete_fourth;
	debug_d    uint16                      _baud_tx_two_stop_bits;
	debug_d    uint16                      _baud_tx_within_tmd_break;
	debug_d    uint16                      _ORIG_LEN_MS_INITIAL;
	debug_d    uint16                      _ORIG_LEN_MS_MAXIMUM_ANS;
	debug_d    uint16                      _ORIG_LEN_MS_RLSD_TURNON_DELAY;
	debug_d    uint16                      _ORIG_LEN_MS_SART_TO_SAMPLE_DWELL;
	debug_d    uint16                      _ORIG_LEN_MS_SILENCE_DETECT;
	debug_d    uint16                      _ORIG_LEN_MS_Te;
	debug_d    uint16                      _ORIG_V8_CI_COUNT_MIN;
	debug_d    uint16                      _ORIG_V8_CJ_COUNT_MIN;
	debug_d    uint16                      _ORIG_V8_CM_COUNT_NOM;
	debug_d    uint16                      _overlay_minor_index;
	debug_d    volatile uint16             _v34b_mg_run_active_flag;
	debug_d    fract                       _CONVERT_AGC_1_ENERGY_TARGET_LOG;
	debug_d    fract                       _CONVERT_AGC_1_GAIN_MAX_LOG;
	debug_d    fract                       _CONVERT_AGC_1_GAIN_MIN_LOG;
	debug_d    fract                       _CONVERT_AGC_2_ENERGY_TARGET_LOG;
	debug_d    fract                       _V34S_FULL_PHROLL_THRESHOLD;
	debug_d    fract                       _V34S_PARTIAL_PHROLL_THRESHOLD;
	debug_d    fract                       _V34_AB_SIGNAL_MIN_ENERGY;
	debug_d    fract                       _V34_AB_SIGNAL_SLEW_RATE;
	debug_d    fract                       _V34_BE2_SLEW_FAST;
	debug_d    fract                       _V34_BE2_SLEW_MEDIUM;
	debug_d    fract                       _V34_BE2_SLEW_SLOW;
	debug_d    fract                       _V34_BE_LOG_MAXIMUM_GAIN;
	debug_d    fract                       _V34_BE_LOG_MINIMUM_GAIN;
	debug_d    fract                       _V34_S_SIGNAL_MAX_ENERGY;
	debug_d    fract                       _V34_S_SIGNAL_MIN_ENERGY;
	debug_d    sint15                      _V34S_ENERGY_INPUT_SLEW;
	debug_d    sint15                      _V34S_FULL_CONVERGENCE_THRESHOLD;
	debug_d    sint15                      _V34S_GEAR_CONVERGENCE_THRESHOLD;
	debug_d    sint15                      _V34S_PARTIAL_CONVERGENCE_THRESHOLD;
	debug_d    sint15                      _V34S_RUN_HOLDOFF_TIME;
	debug_d    sint15                      _V34_AB_SIGNAL_C8K0_LIMIT;
	debug_d    phase_t                     _V34_A_OVER_CK80;
	debug_d    sint15                      _V34_BE_POWER_SLEW;
	debug_d    phase_t                     _V34_B_OVER_CK80;
	debug_d    sint15                      _V34_EQUALIZER_SCALE;
	debug_d    sint15                      _V34_RESYNC_FILL_LENGTH;
	debug_d    sint15                      _V34_RESYNC_LOG2_MEASURE_ADJUST;
	debug_d    sint15                      _V34_RESYNC_MEASURE_LENGTH;
	debug_d    sint15                      _V34_RESYNC_PERCENT_THRESHOLD;
	debug_d    sint15                      _V34_S_SIGNAL_2T_LIMIT;
	debug_d    sint15                      _V34_S_SIGNAL_DEGREE_WIDTH;
	debug_d    sint15                      _V34_TRN2_MSE_REPORT_RATE;
	debug_d    sint15                      _V34_TRN2_MSE_STACK_COUNT;
	debug_d    ufract                      _V34_BE_SLEW_FAST;
	debug_d    ufract                      _V34_BE_SLEW_MEDIUM;
	debug_d    ufract                      _V34_BE_SLEW_SLOW;
	debug_d    uint16                      _V34S_FINAL_MPA_SEND_COUNT;
	debug_d    uint16                      _V34S_LEN_8K0_1ST_GEAR_CHANGE;
	debug_d    uint16                      _V34S_LEN_8K0_1ST_PHASE_CHANGE;
	debug_d    uint16                      _V34S_LEN_8K0_2ND_FAST_TRAIN;
	debug_d    uint16                      _V34S_LEN_8K0_2ND_PHASE_CHANGE;
	debug_d    uint16                      _V34S_LEN_8K0_MAX_1ST_GEAR;
	debug_d    uint16                      _V34S_LEN_8K0_PHROLL_PASS;
	debug_d    uint16                      _V34S_LEN_8K0_PRE_PHASE_CHANGE;
	debug_d    uint16                      _V34S_LEN_T_2ND_CHECK_WAIT;
	debug_d    uint16                      _V34S_RENEG_INIT_T_1RT_SN_TO_S_TIMEOUT;
	debug_d    uint16                      _V34S_RENEG_INIT_T_S_TO_SN_TIMEOUT;
	debug_d    uint16                      _V34S_RENEG_RESP_T_S_TO_SN_TIMEOUT;
	debug_d    uint16                      _V34S_RENEG_TEST_T_S_LENGTH;
	debug_d    uint16                      _V34S_REVERSALS_FOUND_THRESHOLD;
	debug_d    uint16                      _V34S_RUN_8K0_ONE_SECOND_TIME;
	debug_d    uint16                      _V34S_RUN_8K0_STATISTICS_TIME;
	debug_d    uint16                      _V34S_RUN_V0_M_ERROR_LIMIT;
	debug_d    uint16                      _V34S_RUN_V0_M_HOLDOFF_TIME;
} cmn_debug_t;

/* ************************************************************************* */

DEF_DATA(cmn_debug_t, cmn_debug)
#define CMN_DEBUG_DATA cmn_debug_t cmn_debug
#define CMN_DEBUG USE_DATA(cmn_debug)
#define cmn_debug_used

/* ************************************************************************* */

#define baud_rx_fsk_oversample           CMN_DEBUG._baud_rx_fsk_oversample
#define baud_rx_substate                 CMN_DEBUG._baud_rx_substate
#define baud_rx_no_carrier_flag          CMN_DEBUG._baud_rx_no_carrier_flag
#define baud_rx_state                    CMN_DEBUG._baud_rx_state
#define baud_rx_data_dlvd                CMN_DEBUG._baud_rx_data_dlvd
#define baud_tx_state                    CMN_DEBUG._baud_tx_state
#define baud_rx_bit_cnt                  CMN_DEBUG._baud_rx_bit_cnt
#define baud_tx_bit_cnt                  CMN_DEBUG._baud_tx_bit_cnt
#define baud_hdlc_frame_start_indicator  CMN_DEBUG._baud_hdlc_frame_start_indicator
#define hdlc_lead_flag_cnt               CMN_DEBUG._hdlc_lead_flag_cnt
#define baud_tx_corrupt_packet_cnt       CMN_DEBUG._baud_tx_corrupt_packet_cnt
#define baud_tx_unshifted                CMN_DEBUG._baud_tx_unshifted
#define baud_rx_crc_lo                   CMN_DEBUG._baud_rx_crc_lo
#define baud_tx_crc_lo                   CMN_DEBUG._baud_tx_crc_lo
#define baud_rx_parity_even_space        CMN_DEBUG._baud_rx_parity_even_space
#define baud_rx_parity_stick             CMN_DEBUG._baud_rx_parity_stick
#define baud_rx_parity_used              CMN_DEBUG._baud_rx_parity_used
#define baud_tx_parity_even_space        CMN_DEBUG._baud_tx_parity_even_space
#define baud_tx_parity_stick             CMN_DEBUG._baud_tx_parity_stick
#define baud_tx_parity_used              CMN_DEBUG._baud_tx_parity_used
#define baud_tx_delete_bit_count         CMN_DEBUG._baud_tx_delete_bit_count
#define overlay_8K0_timeout              CMN_DEBUG._overlay_8K0_timeout
#define ANSW_LEN_MS_ANSam_CI_SEARCH      CMN_DEBUG._ANSW_LEN_MS_ANSam_CI_SEARCH
#define ANSW_LEN_MS_CJ_TIMEOUT           CMN_DEBUG._ANSW_LEN_MS_CJ_TIMEOUT
#define ANSW_LEN_MS_MINIMUM_ANSam        CMN_DEBUG._ANSW_LEN_MS_MINIMUM_ANSam
#define ANSW_LEN_MS_NOMINAL_JM           CMN_DEBUG._ANSW_LEN_MS_NOMINAL_JM
#define ANSW_LEN_MS_NOMINAL_REVERSAL     CMN_DEBUG._ANSW_LEN_MS_NOMINAL_REVERSAL
#define ANSW_LEN_MS_PREWAIT_DELAY        CMN_DEBUG._ANSW_LEN_MS_PREWAIT_DELAY
#define ANSW_LEN_MS_RLSD_TURNON_DELAY    CMN_DEBUG._ANSW_LEN_MS_RLSD_TURNON_DELAY
#define ANSW_LEN_MS_SILENCE_DETECT       CMN_DEBUG._ANSW_LEN_MS_SILENCE_DETECT
#define baud_rx_data_size_code           CMN_DEBUG._baud_rx_data_size_code
#define baud_tx_data_size_code           CMN_DEBUG._baud_tx_data_size_code
#define baud_tx_delete_fourth            CMN_DEBUG._baud_tx_delete_fourth
#define baud_tx_two_stop_bits            CMN_DEBUG._baud_tx_two_stop_bits
#define baud_tx_within_tmd_break         CMN_DEBUG._baud_tx_within_tmd_break
#define ORIG_LEN_MS_INITIAL              CMN_DEBUG._ORIG_LEN_MS_INITIAL
#define ORIG_LEN_MS_MAXIMUM_ANS          CMN_DEBUG._ORIG_LEN_MS_MAXIMUM_ANS
#define ORIG_LEN_MS_RLSD_TURNON_DELAY    CMN_DEBUG._ORIG_LEN_MS_RLSD_TURNON_DELAY
#define ORIG_LEN_MS_SART_TO_SAMPLE_DWELL CMN_DEBUG._ORIG_LEN_MS_SART_TO_SAMPLE_DWELL
#define ORIG_LEN_MS_SILENCE_DETECT       CMN_DEBUG._ORIG_LEN_MS_SILENCE_DETECT
#define ORIG_LEN_MS_Te                   CMN_DEBUG._ORIG_LEN_MS_Te
#define ORIG_V8_CI_COUNT_MIN             CMN_DEBUG._ORIG_V8_CI_COUNT_MIN
#define ORIG_V8_CJ_COUNT_MIN             CMN_DEBUG._ORIG_V8_CJ_COUNT_MIN
#define ORIG_V8_CM_COUNT_NOM             CMN_DEBUG._ORIG_V8_CM_COUNT_NOM
#define overlay_minor_index              CMN_DEBUG._overlay_minor_index
#define v34b_mg_run_active_flag          CMN_DEBUG._v34b_mg_run_active_flag
#define CONVERT_AGC_1_ENERGY_TARGET_LOG  CMN_DEBUG._CONVERT_AGC_1_ENERGY_TARGET_LOG
#define CONVERT_AGC_1_GAIN_MAX_LOG       CMN_DEBUG._CONVERT_AGC_1_GAIN_MAX_LOG
#define CONVERT_AGC_1_GAIN_MIN_LOG       CMN_DEBUG._CONVERT_AGC_1_GAIN_MIN_LOG
#define CONVERT_AGC_2_ENERGY_TARGET_LOG  CMN_DEBUG._CONVERT_AGC_2_ENERGY_TARGET_LOG
#define V34S_FULL_PHROLL_THRESHOLD       CMN_DEBUG._V34S_FULL_PHROLL_THRESHOLD
#define V34S_PARTIAL_PHROLL_THRESHOLD    CMN_DEBUG._V34S_PARTIAL_PHROLL_THRESHOLD
#define V34_AB_SIGNAL_MIN_ENERGY         CMN_DEBUG._V34_AB_SIGNAL_MIN_ENERGY
#define V34_AB_SIGNAL_SLEW_RATE          CMN_DEBUG._V34_AB_SIGNAL_SLEW_RATE
#define V34_BE2_SLEW_FAST                CMN_DEBUG._V34_BE2_SLEW_FAST
#define V34_BE2_SLEW_MEDIUM              CMN_DEBUG._V34_BE2_SLEW_MEDIUM
#define V34_BE2_SLEW_SLOW                CMN_DEBUG._V34_BE2_SLEW_SLOW
#define V34_BE_LOG_MAXIMUM_GAIN          CMN_DEBUG._V34_BE_LOG_MAXIMUM_GAIN
#define V34_BE_LOG_MINIMUM_GAIN          CMN_DEBUG._V34_BE_LOG_MINIMUM_GAIN
#define V34_S_SIGNAL_MAX_ENERGY          CMN_DEBUG._V34_S_SIGNAL_MAX_ENERGY
#define V34_S_SIGNAL_MIN_ENERGY          CMN_DEBUG._V34_S_SIGNAL_MIN_ENERGY
#define V34S_ENERGY_INPUT_SLEW           CMN_DEBUG._V34S_ENERGY_INPUT_SLEW
#define V34S_FULL_CONVERGENCE_THRESHOLD  CMN_DEBUG._V34S_FULL_CONVERGENCE_THRESHOLD
#define V34S_GEAR_CONVERGENCE_THRESHOLD  CMN_DEBUG._V34S_GEAR_CONVERGENCE_THRESHOLD
#define V34S_PARTIAL_CONVERGENCE_THRESHOLD CMN_DEBUG._V34S_PARTIAL_CONVERGENCE_THRESHOLD
#define V34S_RUN_HOLDOFF_TIME            CMN_DEBUG._V34S_RUN_HOLDOFF_TIME
#define V34_AB_SIGNAL_C8K0_LIMIT         CMN_DEBUG._V34_AB_SIGNAL_C8K0_LIMIT
#define V34_A_OVER_CK80                  CMN_DEBUG._V34_A_OVER_CK80
#define V34_BE_POWER_SLEW                CMN_DEBUG._V34_BE_POWER_SLEW
#define V34_B_OVER_CK80                  CMN_DEBUG._V34_B_OVER_CK80
#define V34_EQUALIZER_SCALE              CMN_DEBUG._V34_EQUALIZER_SCALE
#define V34_RESYNC_FILL_LENGTH           CMN_DEBUG._V34_RESYNC_FILL_LENGTH
#define V34_RESYNC_LOG2_MEASURE_ADJUST   CMN_DEBUG._V34_RESYNC_LOG2_MEASURE_ADJUST
#define V34_RESYNC_MEASURE_LENGTH        CMN_DEBUG._V34_RESYNC_MEASURE_LENGTH
#define V34_RESYNC_PERCENT_THRESHOLD     CMN_DEBUG._V34_RESYNC_PERCENT_THRESHOLD
#define V34_S_SIGNAL_2T_LIMIT            CMN_DEBUG._V34_S_SIGNAL_2T_LIMIT
#define V34_S_SIGNAL_DEGREE_WIDTH        CMN_DEBUG._V34_S_SIGNAL_DEGREE_WIDTH
#define V34_TRN2_MSE_REPORT_RATE         CMN_DEBUG._V34_TRN2_MSE_REPORT_RATE
#define V34_TRN2_MSE_STACK_COUNT         CMN_DEBUG._V34_TRN2_MSE_STACK_COUNT
#define V34_BE_SLEW_FAST                 CMN_DEBUG._V34_BE_SLEW_FAST
#define V34_BE_SLEW_MEDIUM               CMN_DEBUG._V34_BE_SLEW_MEDIUM
#define V34_BE_SLEW_SLOW                 CMN_DEBUG._V34_BE_SLEW_SLOW
#define V34S_FINAL_MPA_SEND_COUNT        CMN_DEBUG._V34S_FINAL_MPA_SEND_COUNT
#define V34S_LEN_8K0_1ST_GEAR_CHANGE     CMN_DEBUG._V34S_LEN_8K0_1ST_GEAR_CHANGE
#define V34S_LEN_8K0_1ST_PHASE_CHANGE    CMN_DEBUG._V34S_LEN_8K0_1ST_PHASE_CHANGE
#define V34S_LEN_8K0_2ND_FAST_TRAIN      CMN_DEBUG._V34S_LEN_8K0_2ND_FAST_TRAIN
#define V34S_LEN_8K0_2ND_PHASE_CHANGE    CMN_DEBUG._V34S_LEN_8K0_2ND_PHASE_CHANGE
#define V34S_LEN_8K0_MAX_1ST_GEAR        CMN_DEBUG._V34S_LEN_8K0_MAX_1ST_GEAR
#define V34S_LEN_8K0_PHROLL_PASS         CMN_DEBUG._V34S_LEN_8K0_PHROLL_PASS
#define V34S_LEN_8K0_PRE_PHASE_CHANGE    CMN_DEBUG._V34S_LEN_8K0_PRE_PHASE_CHANGE
#define V34S_LEN_T_2ND_CHECK_WAIT        CMN_DEBUG._V34S_LEN_T_2ND_CHECK_WAIT
#define V34S_RENEG_INIT_T_1RT_SN_TO_S_TIMEOUT CMN_DEBUG._V34S_RENEG_INIT_T_1RT_SN_TO_S_TIMEOUT
#define V34S_RENEG_INIT_T_S_TO_SN_TIMEOUT CMN_DEBUG._V34S_RENEG_INIT_T_S_TO_SN_TIMEOUT
#define V34S_RENEG_RESP_T_S_TO_SN_TIMEOUT CMN_DEBUG._V34S_RENEG_RESP_T_S_TO_SN_TIMEOUT
#define V34S_RENEG_TEST_T_S_LENGTH       CMN_DEBUG._V34S_RENEG_TEST_T_S_LENGTH
#define V34S_REVERSALS_FOUND_THRESHOLD   CMN_DEBUG._V34S_REVERSALS_FOUND_THRESHOLD
#define V34S_RUN_8K0_ONE_SECOND_TIME     CMN_DEBUG._V34S_RUN_8K0_ONE_SECOND_TIME
#define V34S_RUN_8K0_STATISTICS_TIME     CMN_DEBUG._V34S_RUN_8K0_STATISTICS_TIME
#define V34S_RUN_V0_M_ERROR_LIMIT        CMN_DEBUG._V34S_RUN_V0_M_ERROR_LIMIT
#define V34S_RUN_V0_M_HOLDOFF_TIME       CMN_DEBUG._V34S_RUN_V0_M_HOLDOFF_TIME

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

typedef struct {
	local_d    uint16                      _fg_svalue_queue [NUMBER_OF_FG_EVENTS];
	local_d    fract                       _ph2p_L1_log_power_display_buffer [PH2P_NO_BINS_x2];
	local_d    tone_generator_buffer_t     _tone_generator_buffer [TONE_GENERATOR_COUNT];
} cmn_local_t;

/* ************************************************************************* */

DEF_DATA(cmn_local_t, cmn_local)
#define CMN_LOCAL_DATA cmn_local_t cmn_local
#define CMN_LOCAL USE_DATA(cmn_local)
#define cmn_local_used

/* ************************************************************************* */

#define fg_svalue_queue                  CMN_LOCAL._fg_svalue_queue
#define ph2p_L1_log_power_display_buffer CMN_LOCAL._ph2p_L1_log_power_display_buffer
#define tone_generator_buffer            CMN_LOCAL._tone_generator_buffer

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

typedef struct {
	fast_d     fract                      _parm__hw_tx_gain_correction;
	fast_d     ufract                      _parm__hw_rx_gain_correction;
	fast_d     sint15                      _dc_offset;
	fast_d     sint31                      _dc_offset_accumulator;
	fast_d     int                         _dc_offset_counter;
	fast_d     int                         _dc_offset_display_counter;
	fast_d     int                         _periodic_timer;
	fast_d     fract                       _input_sample;
	fast_d     sint15                      _sample_conversion_control;
	fast_d     uint16                      _conv_bpf_clip;
	fast_d     ufract                      _parm__pump_transmit_level;
	fast_d     fract                       _equalized_imag;
	fast_d     fract                       _equalized_real;
	fast_d     fract                       _perfect_imag;
	fast_d     fract                       _perfect_real;
	fast_d     fract                       _rx_sample;
	fast_d     fract                       _random_real_value;
	fast_d     fract                       _random_imag_value;
	fast_d     fract                       _precision_cos_value;
	fast_d     fract                       _precision_sin_value;
	fast_d     uint16                      _sart_rx_data_unit_1;
	fast_d     uint16                      _sart_rx_data_unit_2;
	fast_d     uint16                      _rate_conv_modulo_counter;
	fast_d     fract CIRCULAR              _rx_rate_conv_data_buffer [2 * RATE_CNV_RX_SIZE];
	fast_d     uint16                      _sart_tx_data_unit;
	fast_d     fract CIRCULAR              _tx_rate_conv_data_buffer [2 * RATE_CNV_TX_SIZE];
	fast_d     int                         _baud_xx_data;
	fast_d     sint15                      _output_sample;
	fast_d     bool                        _baud_tx_flag;
	fast_d     phase_t                     _rx_clock_phase;
	fast_d     phase_t                     _tx_clock_phase;
	fast_d     tv_union_t                  _thread_variable;
	fast_d     phase_t                     _rx_clock_cycles_per_sample;
	fast_d     int                         _baud_rx_data;
	fast_d     int                         _baud_tx_data;
	fast_d     phase_t                     _tx_clock_cycles_per_sample;
	fast_d     bool                        _baud_rx_flag;
	fast_d     uint16                      _baud_tx_data_unit;
	fast_d     uint16                      _parm__report_event_mask;
	fast_d     uint16                      _parm__report_status_mask;
	fast_d     int                         _fg_event_remove;
	fast_d     int                         _fg_event_insert;
	fast_d     int                         _fg_status_insert;
	fast_d     int                         _fg_status_remove;
	fast_d     event_t                     _fgkernel_current_event;
	fast_d     uint16                      _fgkernel_current_svalue;
	fast_d     int                         _number_fg_states;
	fast_d     int                         _number_permanent_fg_states;
	fast_d     int                         _current_fg_state;
	fast_d     bool                        _current_fg_state_active;
	fast_d     bool                        _within_fg_state_update;
	fast_d     uint16                      _fg_time_until_next_timer_update;
	fast_d     int                         _number_fg_timers;
	fast_d     int                         _bg_event_remove;
	fast_d     uint16                      _bg_time_until_next_timer_update;
	fast_d     thread_routine_t            _fg_thread_table [NUMBER_OF_TOTAL_THREAD_COMP];
	fast_d     int                         _fg_thread_offsets [NUMBER_OF_FG_BLOCKS+1];
	fast_d     int                         _fg_thread_max_usage;
	fast_d     uint16                      _rx_rate_conv_offset;
	fast_d     uint16                      _tx_rate_conv_offset;
	fast_d     int                         _tone_detector_offset;
	fast_d     bool                        _baud_rx_16_bit_mode;
	fast_d     bool                        _baud_tx_16_bit_mode;
	fast_d     int                         _aux_rx_baud;
	fast_d     int                         _aux_rx_data;
	fast_d     int                         _aux_tx_baud;
	fast_d     int                         _aux_tx_data;
	fast_d     int                         _baud_cntr;
	fast_d     int                         _baud_tx_cntr;
	fast_d     int                         _baud_rx_cntr;
} cmn_fast_t;

/* ************************************************************************* */

DEF_DATA(cmn_fast_t, cmn_fast)
#define CMN_FAST_DATA cmn_fast_t cmn_fast
#define CMN_FAST USE_DATA(cmn_fast)
#define cmn_fast_used

/* ************************************************************************* */

#define parm__hw_tx_gain_correction      CMN_FAST._parm__hw_tx_gain_correction
#define parm__hw_rx_gain_correction      CMN_FAST._parm__hw_rx_gain_correction
#define dc_offset                        CMN_FAST._dc_offset
#define dc_offset_accumulator            CMN_FAST._dc_offset_accumulator
#define dc_offset_counter                CMN_FAST._dc_offset_counter
#define dc_offset_display_counter        CMN_FAST._dc_offset_display_counter
#define periodic_timer                   CMN_FAST._periodic_timer
#define input_sample                     CMN_FAST._input_sample
#define sample_conversion_control        CMN_FAST._sample_conversion_control
#define conv_bpf_clip                    CMN_FAST._conv_bpf_clip
#define parm__pump_transmit_level        CMN_FAST._parm__pump_transmit_level
#define equalized_imag                   CMN_FAST._equalized_imag
#define equalized_real                   CMN_FAST._equalized_real
#define perfect_imag                     CMN_FAST._perfect_imag
#define perfect_real                     CMN_FAST._perfect_real
#define rx_sample                        CMN_FAST._rx_sample
#define random_real_value                CMN_FAST._random_real_value
#define random_imag_value                CMN_FAST._random_imag_value
#define precision_cos_value              CMN_FAST._precision_cos_value
#define precision_sin_value              CMN_FAST._precision_sin_value
#define sart_rx_data_unit_1              CMN_FAST._sart_rx_data_unit_1
#define sart_rx_data_unit_2              CMN_FAST._sart_rx_data_unit_2
#define rate_conv_modulo_counter         CMN_FAST._rate_conv_modulo_counter
#define rx_rate_conv_data_buffer         CMN_FAST._rx_rate_conv_data_buffer
#define sart_tx_data_unit                CMN_FAST._sart_tx_data_unit
#define tx_rate_conv_data_buffer         CMN_FAST._tx_rate_conv_data_buffer
#define baud_xx_data                     CMN_FAST._baud_xx_data
#define output_sample                    CMN_FAST._output_sample
#define baud_tx_flag                     CMN_FAST._baud_tx_flag
#define rx_clock_phase                   CMN_FAST._rx_clock_phase
#define tx_clock_phase                   CMN_FAST._tx_clock_phase
#define thread_variable                  CMN_FAST._thread_variable
#define rx_clock_cycles_per_sample       CMN_FAST._rx_clock_cycles_per_sample
#define baud_rx_data                     CMN_FAST._baud_rx_data
#define baud_tx_data                     CMN_FAST._baud_tx_data
#define tx_clock_cycles_per_sample       CMN_FAST._tx_clock_cycles_per_sample
#define baud_rx_flag                     CMN_FAST._baud_rx_flag
#define baud_tx_data_unit                CMN_FAST._baud_tx_data_unit
#define parm__report_event_mask          CMN_FAST._parm__report_event_mask
#define parm__report_status_mask         CMN_FAST._parm__report_status_mask
#define fg_event_remove                  CMN_FAST._fg_event_remove
#define fg_event_insert                  CMN_FAST._fg_event_insert
#define fg_status_insert                 CMN_FAST._fg_status_insert
#define fg_status_remove                 CMN_FAST._fg_status_remove
#define fgkernel_current_event           CMN_FAST._fgkernel_current_event
#define fgkernel_current_svalue          CMN_FAST._fgkernel_current_svalue
#define number_fg_states                 CMN_FAST._number_fg_states
#define number_permanent_fg_states       CMN_FAST._number_permanent_fg_states
#define current_fg_state                 CMN_FAST._current_fg_state
#define current_fg_state_active          CMN_FAST._current_fg_state_active
#define within_fg_state_update           CMN_FAST._within_fg_state_update
#define fg_time_until_next_timer_update  CMN_FAST._fg_time_until_next_timer_update
#define number_fg_timers                 CMN_FAST._number_fg_timers
#define bg_event_remove                  CMN_FAST._bg_event_remove
#define bg_time_until_next_timer_update  CMN_FAST._bg_time_until_next_timer_update
#define fg_thread_table                  CMN_FAST._fg_thread_table
#define fg_thread_offsets                CMN_FAST._fg_thread_offsets
#define fg_thread_max_usage              CMN_FAST._fg_thread_max_usage
#define rx_rate_conv_offset              CMN_FAST._rx_rate_conv_offset
#define tx_rate_conv_offset              CMN_FAST._tx_rate_conv_offset
#define tone_detector_offset             CMN_FAST._tone_detector_offset
#define baud_rx_16_bit_mode              CMN_FAST._baud_rx_16_bit_mode
#define baud_tx_16_bit_mode              CMN_FAST._baud_tx_16_bit_mode
#define aux_rx_baud                      CMN_FAST._aux_rx_baud
#define aux_rx_data                      CMN_FAST._aux_rx_data
#define aux_tx_baud                      CMN_FAST._aux_tx_baud
#define aux_tx_data                      CMN_FAST._aux_tx_data
#define baud_cntr                        CMN_FAST._baud_cntr
#define baud_tx_cntr                     CMN_FAST._baud_tx_cntr
#define baud_rx_cntr                     CMN_FAST._baud_rx_cntr

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

typedef struct {
	shared_d   uint16                      _parm__dtmf_tone_off_time;
	shared_d   uint16                      _parm__dtmf_tone_on_time;
} cmn_shared_t;

/* ************************************************************************* */

DEF_DATA(cmn_shared_t, cmn_shared)
#define CMN_SHARED_DATA cmn_shared_t cmn_shared
#define CMN_SHARED USE_DATA(cmn_shared)
#define cmn_shared_used

/* ************************************************************************* */

#define parm__dtmf_tone_off_time         CMN_SHARED._parm__dtmf_tone_off_time
#define parm__dtmf_tone_on_time          CMN_SHARED._parm__dtmf_tone_on_time

/* ************************************************************************* */

#endif /* _DATA_CMN_H */
