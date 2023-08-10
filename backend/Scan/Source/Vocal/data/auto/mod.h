
/* ************************************************************************* */
/*
 *	mod.h
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
 *	This file contains automatically generated data for mod.
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

#ifndef _DATA_MOD_H
#define _DATA_MOD_H
#include "data/sections.h"

/* ************************************************************************* */

typedef struct {
	const_d    fract                       _correlator_fit_threshold;
	const_d    fract                       _delta_energy_threshold;
	const_d    fract                       _threshold_fsk;
	const_d    fract                       _threshold_v22;
	const_d    sint15                      _hit_counter_init;
	const_d    sint15                      _reversal_timeout_init;
	const_d    fract                       _ec_fast_slew;
	const_d    fract                       _ec_medium_slew;
	const_d    fract                       _ec_slow_slew;
} mod_const_t;

/* ************************************************************************* */

DEF_DATA(mod_const_t, mod_const)
#define MOD_CONST_DATA mod_const_t mod_const
#define MOD_CONST USE_DATA(mod_const)
#define mod_const_used

/* ************************************************************************* */

#define correlator_fit_threshold         MOD_CONST._correlator_fit_threshold
#define delta_energy_threshold           MOD_CONST._delta_energy_threshold
#define threshold_fsk                    MOD_CONST._threshold_fsk
#define threshold_v22                    MOD_CONST._threshold_v22
#define hit_counter_init                 MOD_CONST._hit_counter_init
#define reversal_timeout_init            MOD_CONST._reversal_timeout_init
#define ec_fast_slew                     MOD_CONST._ec_fast_slew
#define ec_medium_slew                   MOD_CONST._ec_medium_slew
#define ec_slow_slew                     MOD_CONST._ec_slow_slew

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

typedef struct {
	var_d      fract                       _train_on_data_slew;
	var_d      sint15                      _fsk_shift_gain;
	var_d      sint15                      _guard_tone_enable;
	var_d      phase_t                     _guard_tone_increment;
	var_d      phase_t                     _guard_tone_phase;
	var_d      fract                       _guard_tone_amplitude;
	var_d      fract                       _guard_tone_gain;
	var_d      fract                       _agc_2_feedback_slew;
	var_d      fract                       _btrec_baud_agc_slew;
	var_d      fract                       _btrec_baud_first_slew;
	var_d      fract                       _btrec_baud_second_slew;
	var_d      fract32                     _btrec_rx_phase_second32;
	var_d      fract                       _dcd_rcv_level;
	var_d      fract                       _dcd_threshold;
	var_d      fract                       _delta_threshold;
	var_d      fract                       _equalizer_slew;
	var_d      fract                       _error_imag;
	var_d      fract                       _error_real;
	var_d      fract                       _fsk_ANSam_deviation;
	var_d      fract                       _fsk_gain_adjust;
	var_d      fract                       _fsk_local_interpolator_buffer_gain [C7K2_FSK_TX_INTERPOLATOR_SIZE * 2];
	var_d      fract32                     _fsk_previous_dif32;
	var_d      sint15                      _fsk_previous_exp;
	var_d      fract                       _jitter_frequency;
	var_d      fract                       _jitter_1st_order_slew;
	var_d      fract                       _jitter_2nd_order_slew;
	var_d      fract                       _jitter_jitter_imag;
	var_d      fract                       _jitter_jitter_limit;
	var_d      fract                       _jitter_jitter_real;
	var_d      fract                       _jitter_max_freq;
	var_d      fract                       _jitter_min_freq;
	var_d      fract                       _jitter_Q_factor;
	var_d      fract                       _mean_square_error;
	var_d      fract                       _out_vxxmod_remote;
	var_d      fract                       _phase_loop_imag;
	var_d      fract                       _phase_loop_real;
	var_d      fract                       _pre_equalized_energy_level;
	var_d      fract                       _pre_equalizer_coefs [5];
	var_d      fract                       _temp_c7k2_interpolator_coefs [MAX_C7K2_INTERPOLATOR_SIZE];
	var_d      sint15                      _ec_update_rate_divider;
	var_d      fract                       _local_ec_slew;
	var_d      fract                       _remote_ec_slew;
	var_d      fract                       _ptloop_1st_order_slew;
	var_d      fract                       _ptloop_2nd_order_slew;
	var_d      fract32                     _ptloop_2nd_order_term32;
	var_d      sint15                      _ptloop_monitor_count;
	var_d      fract                       _ptloop_anti_oscillation_slew;
	var_d      fract32                     _ptloop_angle32;
	var_d      fract                       _ptloop_angle_change_limit;
	var_d      sint15                      _rate_seq_counter;
	var_d      uint16                      _received_e_seq;
	var_d      uint16                      _sequence_reg;
	var_d      fract                       _sequence_detect_level;
	var_d      fract40                     _det_energy40;
	var_d      sint15                      _det_exponent;
	var_d      fract                       _tmp_baud_sum_imag;
	var_d      fract                       _tmp_baud_sum_real;
	var_d      uint16                      _sdt_poffset;
	var_d      fract                       _sdt_correlator_fit_threshold;
	var_d      fract                       _sdt_dcd_threshold;
	var_d      fract                       _sdt_delta_energy_threshold;
	var_d      sint15                      _sdt_hit_counter;
	var_d      sint15                      _sdt_reversal_timeout;
	var_d      sint15                      _sdt_reversal_timeout_init;
	var_d      uint16                      _sdt_bit_delay_buffer [4];
	var_d      fract                       _sdt_off_threshold;
	var_d      fract                       _sdt_peak_hold;
	var_d      fract                       _sdt_angle_store_imag [4];
	var_d      fract                       _sdt_angle_store_real [4];
	var_d      fract CIRCULAR              _sdt_data_buffer_imag [2*32];
	var_d      fract CIRCULAR              _sdt_data_buffer_real [2*32];
	var_d      fract                       _tmp_baud_UVW_real [4];
	var_d      fract                       _tmp_baud_UVW_imag [4];
	var_d      fract                       _retrain_threshold;
	var_d      fract                       _train_on_data_coordinate;
	var_d      fract                       _train_on_data_switch;
	var_d      ufract                      _tx_bpf_gain_adjust;
	var_d      fract CIRCULAR              _extra_rate_reduction_buffer_imag [2 * C7K2_FSK_REDUCE_LPF_SIZE];
	var_d      fract CIRCULAR              _extra_rate_reduction_buffer_real [2 * C7K2_FSK_REDUCE_LPF_SIZE];
	var_d      fract CIRCULAR              _rate_reduction_buffer_imag [2 * C7K2_FSK_REDUCE_LPF_SIZE];
	var_d      fract CIRCULAR              _rate_reduction_buffer_real [2 * C7K2_FSK_REDUCE_LPF_SIZE];
	var_d      const fract*                _fsk_tx_passband_coef_pointer;
	var_d      const fract*                _tx_bpf_coef_pointer;
	var_d      fract32                     _btrec_baud_filter_gain32;
	var_d      fract32                     _conv_energy32;
	var_d      phase_t                     _add_deletes_per_baud;
	var_d      ufract                      _agc_2_gain;
	var_d      sint15                      _agc_2_exponent;
	var_d      sint15                      _agc_2_lpf_width;
	var_d      sint15                      _bulk_delay_input_poffset;
	var_d      sint15                      _bulk_delay_local_poffset;
	var_d      sint15                      _bulk_delay_remote_poffset;
	var_d      sint15                      _dcd_integration_time;
	var_d      sint15                      _dcd_level;
	var_d      sint15                      _delta_level;
	var_d      sint15                      _descrambler_mask_table [6];
	var_d      sint15                      _equalizer_coef_count;
	var_d      sint15                      _fsk_ANSam_enable;
	var_d      phase_t                     _fsk_ANSam_increment;
	var_d      phase_t                     _fsk_ANSam_phase;
	var_d      phase_t                     _fsk_clock_capture_width;
	var_d      phase_t                     _fsk_local_interpolator_buffer_offset [C7K2_FSK_TX_INTERPOLATOR_SIZE * 2];
	var_d      sint15                      _fsk_local_interpolator_poffset;
	var_d      sint15                      _fsk_processing_mode;
	var_d      sint15                      _missed_sample_counter;
	var_d      phase_t                     _modulator_offset;
	var_d      sint15                      _rate_reduction_ratio;
	var_d      phase_t                     _rx_clock_phase_slave;
	var_d      sint15                      _rx_interpolator_pointer_adjust;
	var_d      phase_t                     _tx_clock_phase_slave;
	var_d      statistics_buffer_t         _statistics_buffer;
	var_d      uint16                      _clock_mode;
	var_d      uint16                      _descrambler_output;
	var_d      uint16                      _differential_data;
	var_d      uint16                      _ec_error_poffset;
	var_d      uint16                      _equalizer_poffset;
	var_d      uint16                      _extra_rate_reduction_counter;
	var_d      uint16                      _extra_rate_reduction_poffset;
	var_d      uint16                      _prev_diffdec_input;
	var_d      uint16                      _rate_reduction_poffset;
	var_d      uint16                      _rx_overspeed_offset;
	var_d      uint16                      _scrambler_mask_table [5];
	var_d      uint16                      _trellis_data;
	var_d      uint16                      _tx_match_sequence;
	var_d      uint32                      _fsk_bitstream;
	var_d      fract                       _edge_m1200_real;
	var_d      fract                       _edge_m1200_imag;
	var_d      fract                       _edge_p1200_real;
	var_d      fract                       _edge_p1200_imag;
	var_d      fract                       _btrec_p2400_real;
	var_d      fract                       _btrec_p2400_imag;
	var_d      fract CIRCULAR              _ec_error_buffer [2*(EC_UPDATE_RATE)];
	var_d      fract CIRCULAR              _rx_interpolator_buffer_imag [2*((xC8K0_V34_XX_RX_INTERPOLATOR_SIZE)/2)];
	var_d      fract CIRCULAR              _rx_interpolator_buffer_real [2*((xC8K0_V34_XX_RX_INTERPOLATOR_SIZE)/2)];
	var_d      fract CIRCULAR              _rx_lpf_buffer_imag [2*((xC8K0_V34_XX_HALF_RX_LPF_SIZE)*2)];
	var_d      fract CIRCULAR              _equalizer_buffer_real [2*((xV34_XX_EQUALIZER_SIZE)/2)];
	var_d      fract CIRCULAR              _equalizer_buffer_imag [2*((xV34_XX_EQUALIZER_SIZE)/2)];
	var_d      fract                       _equalizer_coef_imag [C7K2_RX_EQUALIZER_SIZE];
	var_d      fract                       _equalizer_coef_real [C7K2_RX_EQUALIZER_SIZE];
	var_d      fract                       _demod_imag;
	var_d      fract                       _demod_real;
	var_d      fract CIRCULAR              _remote_interpolator_buffer_imag [2 * MAX_VXX_TX_INTERPOLATOR_SIZE];
	var_d      fract CIRCULAR              _remote_interpolator_buffer_real [2 * MAX_VXX_TX_INTERPOLATOR_SIZE];
	var_d      fract CIRCULAR              _local_interpolator_buffer_imag [2 * MAX_VXX_TX_INTERPOLATOR_SIZE];
	var_d      fract CIRCULAR              _local_interpolator_buffer_real [2 * MAX_VXX_TX_INTERPOLATOR_SIZE];
	var_d      fract32                     _btrec_rx_phase_first_low;
	var_d      fract32                     _agc_2_lpf32;
	var_d      ufract                      _agc_2_normal_slew;
	var_d      fract32                     _tmp_half_energy32;
	var_d      fract32                     _tmp_full_energy32;
	var_d      uint16                      _ph2n_measured_roundtrip_delay;
	var_d      uint16                      _ph2n_sm_INFO1c_end_delay;
	var_d      fract                       _ph2n_probing_transmit_gain;
	var_d      fract                       _ph2n_rx_preeq_gain;
	var_d      fract                       _ph2n_rx_preeq_Whi;
	var_d      fract                       _ph2n_rx_preeq_Wlo;
	var_d      fract                       _ph2n_rx_preeq_Wme;
	var_d      fract                       _ph2n_rx_receive_agc2_level;
	var_d      fract                       _ph2n_rx_receive_gain;
	var_d      fract                       _ph2n_rx_receive_level;
	var_d      fract                       _ph2n_rx_mse_bias;
	var_d      sint15                      _ph2n_rx_preeq_exponent;
	var_d      sint15                      _v34n_established_ph4_count;
	var_d      sint15                      _v34n_rx_frequency_offset;
	var_d      sint15                      _v34n_tx_frequency_offset;
	var_d      sint15                      _v34_frame_rx_bit_count;
	var_d      sint15                      _v34_frame_rx_word_count;
	var_d      sint15                      _v34_frame_tx_bit_count;
	var_d      sint15                      _v34_frame_tx_word_count;
	var_d      const sint15 *              _v34_frame_rx_bit_parse_pointer_bits;
	var_d      ufract                      _v34n_rx_transmit_gain;
	var_d      uint16                      _current_crc;
	var_d      uint16                      _n16_bits;
	var_d      uint16                      _ph2n_probing_maxrate [2*(V34N_MAX_SYMBOL + 1)];
	var_d      uint16                      _ph2n_probing_preemph [2*(V34N_MAX_SYMBOL + 1)];
	var_d      uint16                      _ph2n_rx_train_16pt;
	var_d      uint16                      _ph2n_rx_use_shaping;
	var_d      uint16                      _v34n_data_rate_MAXIMUM [V34N_MAX_SYMBOL+1];
	var_d      uint16                      _v34n_parm_16point_option;
	var_d      uint16                      _v34n_parm_asymmetric_option;
	var_d      uint16                      _v34n_parm_attenuation_option;
	var_d      uint16                      _v34n_parm_auxiliary_option;
	var_d      uint16                      _v34n_parm_clock_option;
	var_d      uint16                      _v34n_parm_CME_option;
	var_d      uint16                      _v34n_parm_data_rate_option;
	var_d      uint16                      _v34n_parm_difference_option;
	var_d      uint16                      _v34n_parm_hi_carrier_option;
	var_d      uint16                      _v34n_parm_hi_data_rate_option;
	var_d      uint16                      _v34n_parm_lo_carrier_option;
	var_d      uint16                      _v34n_parm_nonlinear_option;
	var_d      uint16                      _v34n_parm_precoder_option;
	var_d      uint16                      _v34n_parm_ptt_attenuation_option;
	var_d      uint16                      _v34n_parm_ptt_hi_carrier_option;
	var_d      uint16                      _v34n_parm_ptt_lo_carrier_option;
	var_d      uint16                      _v34n_parm_ptt_symbol_option;
	var_d      uint16                      _v34n_parm_shaping_option;
	var_d      uint16                      _v34n_parm_symbol_option;
	var_d      uint16                      _v34n_parm_trellis_option;
	var_d      uint16                      _v34n_rxtx_cleardown_active;
	var_d      uint16                      _v34n_rxtx_hi_data_rate_option;
	var_d      uint16                      _v34n_rx_carrier_frequency;
	var_d      uint16                      _v34n_rx_clock_mode;
	var_d      uint16                      _v34n_rx_MD_length;
	var_d      uint16                      _v34n_rx_preemph_value;
	var_d      uint16                      _v34n_rx_probing_maxrate;
	var_d      uint16                      _v34n_rx_symbol_rate;
	var_d      uint16                      _v34n_tx_carrier_frequency;
	var_d      uint16                      _v34n_tx_clock_mode;
	var_d      uint16                      _v34n_tx_data_rate_option;
	var_d      uint16                      _v34n_tx_MD_length;
	var_d      uint16                      _v34n_tx_preemph_value;
	var_d      uint16                      _v34n_tx_probing_maxrate;
	var_d      uint16                      _v34n_tx_symbol_rate;
	var_d      uint16                      _v34_frame_tx_bit_buffer [12]; /* 172+16    = 16*11.75 */
	var_d      uint16 *                    _v34_frame_tx_bit_pointer;
	var_d      uint16                      _v34_frame_rx_bit_buffer [11];
	var_d      uint16                      _v34_frame_rx_bit_offset;
	var_d      uint16 **                   _v34_frame_rx_bit_parse_pointer;
	var_d      uint16                      _v34_frame_rx_calculated_crc;
} mod_vars_t;

/* ************************************************************************* */

DEF_DATA(mod_vars_t, mod_vars)
#define MOD_VARS_DATA mod_vars_t mod_vars
#define MOD_VARS USE_DATA(mod_vars)
#define mod_vars_used

/* ************************************************************************* */

#define train_on_data_slew               MOD_VARS._train_on_data_slew
#define fsk_shift_gain                   MOD_VARS._fsk_shift_gain
#define guard_tone_enable                MOD_VARS._guard_tone_enable
#define guard_tone_increment             MOD_VARS._guard_tone_increment
#define guard_tone_phase                 MOD_VARS._guard_tone_phase
#define guard_tone_amplitude             MOD_VARS._guard_tone_amplitude
#define guard_tone_gain                  MOD_VARS._guard_tone_gain
#define agc_2_feedback_slew              MOD_VARS._agc_2_feedback_slew
#define btrec_baud_agc_slew              MOD_VARS._btrec_baud_agc_slew
#define btrec_baud_first_slew            MOD_VARS._btrec_baud_first_slew
#define btrec_baud_second_slew           MOD_VARS._btrec_baud_second_slew
#define btrec_rx_phase_second32          MOD_VARS._btrec_rx_phase_second32
#define dcd_rcv_level                    MOD_VARS._dcd_rcv_level
#define dcd_threshold                    MOD_VARS._dcd_threshold
#define delta_threshold                  MOD_VARS._delta_threshold
#define equalizer_slew                   MOD_VARS._equalizer_slew
#define error_imag                       MOD_VARS._error_imag
#define error_real                       MOD_VARS._error_real
#define fsk_ANSam_deviation              MOD_VARS._fsk_ANSam_deviation
#define fsk_gain_adjust                  MOD_VARS._fsk_gain_adjust
#define fsk_local_interpolator_buffer_gain MOD_VARS._fsk_local_interpolator_buffer_gain
#define fsk_previous_dif32               MOD_VARS._fsk_previous_dif32
#define fsk_previous_exp                 MOD_VARS._fsk_previous_exp
#define jitter_frequency                 MOD_VARS._jitter_frequency
#define jitter_1st_order_slew            MOD_VARS._jitter_1st_order_slew
#define jitter_2nd_order_slew            MOD_VARS._jitter_2nd_order_slew
#define jitter_jitter_imag               MOD_VARS._jitter_jitter_imag
#define jitter_jitter_limit              MOD_VARS._jitter_jitter_limit
#define jitter_jitter_real               MOD_VARS._jitter_jitter_real
#define jitter_max_freq                  MOD_VARS._jitter_max_freq
#define jitter_min_freq                  MOD_VARS._jitter_min_freq
#define jitter_Q_factor                  MOD_VARS._jitter_Q_factor
#define mean_square_error                MOD_VARS._mean_square_error
#define out_vxxmod_remote                MOD_VARS._out_vxxmod_remote
#define phase_loop_imag                  MOD_VARS._phase_loop_imag
#define phase_loop_real                  MOD_VARS._phase_loop_real
#define pre_equalized_energy_level       MOD_VARS._pre_equalized_energy_level
#define pre_equalizer_coefs              MOD_VARS._pre_equalizer_coefs
#define temp_c7k2_interpolator_coefs     MOD_VARS._temp_c7k2_interpolator_coefs
#define ec_update_rate_divider           MOD_VARS._ec_update_rate_divider
#define local_ec_slew                    MOD_VARS._local_ec_slew
#define remote_ec_slew                   MOD_VARS._remote_ec_slew
#define ptloop_1st_order_slew            MOD_VARS._ptloop_1st_order_slew
#define ptloop_2nd_order_slew            MOD_VARS._ptloop_2nd_order_slew
#define ptloop_2nd_order_term32          MOD_VARS._ptloop_2nd_order_term32
#define ptloop_monitor_count             MOD_VARS._ptloop_monitor_count
#define ptloop_anti_oscillation_slew     MOD_VARS._ptloop_anti_oscillation_slew
#define ptloop_angle32                   MOD_VARS._ptloop_angle32
#define ptloop_angle_change_limit        MOD_VARS._ptloop_angle_change_limit
#define rate_seq_counter                 MOD_VARS._rate_seq_counter
#define received_e_seq                   MOD_VARS._received_e_seq
#define sequence_reg                     MOD_VARS._sequence_reg
#define sequence_detect_level            MOD_VARS._sequence_detect_level
#define det_energy40                     MOD_VARS._det_energy40
#define det_exponent                     MOD_VARS._det_exponent
#define tmp_baud_sum_imag                MOD_VARS._tmp_baud_sum_imag
#define tmp_baud_sum_real                MOD_VARS._tmp_baud_sum_real
#define sdt_poffset                      MOD_VARS._sdt_poffset
#define sdt_correlator_fit_threshold     MOD_VARS._sdt_correlator_fit_threshold
#define sdt_dcd_threshold                MOD_VARS._sdt_dcd_threshold
#define sdt_delta_energy_threshold       MOD_VARS._sdt_delta_energy_threshold
#define sdt_hit_counter                  MOD_VARS._sdt_hit_counter
#define sdt_reversal_timeout             MOD_VARS._sdt_reversal_timeout
#define sdt_reversal_timeout_init        MOD_VARS._sdt_reversal_timeout_init
#define sdt_bit_delay_buffer             MOD_VARS._sdt_bit_delay_buffer
#define sdt_off_threshold                MOD_VARS._sdt_off_threshold
#define sdt_peak_hold                    MOD_VARS._sdt_peak_hold
#define sdt_angle_store_imag             MOD_VARS._sdt_angle_store_imag
#define sdt_angle_store_real             MOD_VARS._sdt_angle_store_real
#define sdt_data_buffer_imag             MOD_VARS._sdt_data_buffer_imag
#define sdt_data_buffer_real             MOD_VARS._sdt_data_buffer_real
#define tmp_baud_UVW_real                MOD_VARS._tmp_baud_UVW_real
#define tmp_baud_UVW_imag                MOD_VARS._tmp_baud_UVW_imag
#define retrain_threshold                MOD_VARS._retrain_threshold
#define train_on_data_coordinate         MOD_VARS._train_on_data_coordinate
#define train_on_data_switch             MOD_VARS._train_on_data_switch
#define tx_bpf_gain_adjust               MOD_VARS._tx_bpf_gain_adjust
#define extra_rate_reduction_buffer_imag MOD_VARS._extra_rate_reduction_buffer_imag
#define extra_rate_reduction_buffer_real MOD_VARS._extra_rate_reduction_buffer_real
#define rate_reduction_buffer_imag       MOD_VARS._rate_reduction_buffer_imag
#define rate_reduction_buffer_real       MOD_VARS._rate_reduction_buffer_real
#define fsk_tx_passband_coef_pointer     MOD_VARS._fsk_tx_passband_coef_pointer
#define tx_bpf_coef_pointer              MOD_VARS._tx_bpf_coef_pointer
#define btrec_baud_filter_gain32         MOD_VARS._btrec_baud_filter_gain32
#define conv_energy32                    MOD_VARS._conv_energy32
#define add_deletes_per_baud             MOD_VARS._add_deletes_per_baud
#define agc_2_gain                       MOD_VARS._agc_2_gain
#define agc_2_exponent                   MOD_VARS._agc_2_exponent
#define agc_2_lpf_width                  MOD_VARS._agc_2_lpf_width
#define bulk_delay_input_poffset         MOD_VARS._bulk_delay_input_poffset
#define bulk_delay_local_poffset         MOD_VARS._bulk_delay_local_poffset
#define bulk_delay_remote_poffset        MOD_VARS._bulk_delay_remote_poffset
#define dcd_integration_time             MOD_VARS._dcd_integration_time
#define dcd_level                        MOD_VARS._dcd_level
#define delta_level                      MOD_VARS._delta_level
#define descrambler_mask_table           MOD_VARS._descrambler_mask_table
#define equalizer_coef_count             MOD_VARS._equalizer_coef_count
#define fsk_ANSam_enable                 MOD_VARS._fsk_ANSam_enable
#define fsk_ANSam_increment              MOD_VARS._fsk_ANSam_increment
#define fsk_ANSam_phase                  MOD_VARS._fsk_ANSam_phase
#define fsk_clock_capture_width          MOD_VARS._fsk_clock_capture_width
#define fsk_local_interpolator_buffer_offset MOD_VARS._fsk_local_interpolator_buffer_offset
#define fsk_local_interpolator_poffset   MOD_VARS._fsk_local_interpolator_poffset
#define fsk_processing_mode              MOD_VARS._fsk_processing_mode
#define missed_sample_counter            MOD_VARS._missed_sample_counter
#define modulator_offset                 MOD_VARS._modulator_offset
#define rate_reduction_ratio             MOD_VARS._rate_reduction_ratio
#define rx_clock_phase_slave             MOD_VARS._rx_clock_phase_slave
#define rx_interpolator_pointer_adjust   MOD_VARS._rx_interpolator_pointer_adjust
#define tx_clock_phase_slave             MOD_VARS._tx_clock_phase_slave
#define statistics_buffer                MOD_VARS._statistics_buffer
#define clock_mode                       MOD_VARS._clock_mode
#define descrambler_output               MOD_VARS._descrambler_output
#define differential_data                MOD_VARS._differential_data
#define ec_error_poffset                 MOD_VARS._ec_error_poffset
#define equalizer_poffset                MOD_VARS._equalizer_poffset
#define extra_rate_reduction_counter     MOD_VARS._extra_rate_reduction_counter
#define extra_rate_reduction_poffset     MOD_VARS._extra_rate_reduction_poffset
#define prev_diffdec_input               MOD_VARS._prev_diffdec_input
#define rate_reduction_poffset           MOD_VARS._rate_reduction_poffset
#define rx_overspeed_offset              MOD_VARS._rx_overspeed_offset
#define scrambler_mask_table             MOD_VARS._scrambler_mask_table
#define trellis_data                     MOD_VARS._trellis_data
#define tx_match_sequence                MOD_VARS._tx_match_sequence
#define fsk_bitstream                    MOD_VARS._fsk_bitstream
#define edge_m1200_real                  MOD_VARS._edge_m1200_real
#define edge_m1200_imag                  MOD_VARS._edge_m1200_imag
#define edge_p1200_real                  MOD_VARS._edge_p1200_real
#define edge_p1200_imag                  MOD_VARS._edge_p1200_imag
#define btrec_p2400_real                 MOD_VARS._btrec_p2400_real
#define btrec_p2400_imag                 MOD_VARS._btrec_p2400_imag
#define ec_error_buffer                  MOD_VARS._ec_error_buffer
#define rx_interpolator_buffer_imag      MOD_VARS._rx_interpolator_buffer_imag
#define rx_interpolator_buffer_real      MOD_VARS._rx_interpolator_buffer_real
#define rx_lpf_buffer_imag               MOD_VARS._rx_lpf_buffer_imag
#define equalizer_buffer_real            MOD_VARS._equalizer_buffer_real
#define equalizer_buffer_imag            MOD_VARS._equalizer_buffer_imag
#define equalizer_coef_imag              MOD_VARS._equalizer_coef_imag
#define equalizer_coef_real              MOD_VARS._equalizer_coef_real
#define demod_imag                       MOD_VARS._demod_imag
#define demod_real                       MOD_VARS._demod_real
#define remote_interpolator_buffer_imag  MOD_VARS._remote_interpolator_buffer_imag
#define remote_interpolator_buffer_real  MOD_VARS._remote_interpolator_buffer_real
#define local_interpolator_buffer_imag   MOD_VARS._local_interpolator_buffer_imag
#define local_interpolator_buffer_real   MOD_VARS._local_interpolator_buffer_real
#define btrec_rx_phase_first_low         MOD_VARS._btrec_rx_phase_first_low
#define agc_2_lpf32                      MOD_VARS._agc_2_lpf32
#define agc_2_normal_slew                MOD_VARS._agc_2_normal_slew
#define tmp_half_energy32                MOD_VARS._tmp_half_energy32
#define tmp_full_energy32                MOD_VARS._tmp_full_energy32
#define ph2n_measured_roundtrip_delay    MOD_VARS._ph2n_measured_roundtrip_delay
#define ph2n_sm_INFO1c_end_delay         MOD_VARS._ph2n_sm_INFO1c_end_delay
#define ph2n_probing_transmit_gain       MOD_VARS._ph2n_probing_transmit_gain
#define ph2n_rx_preeq_gain               MOD_VARS._ph2n_rx_preeq_gain
#define ph2n_rx_preeq_Whi                MOD_VARS._ph2n_rx_preeq_Whi
#define ph2n_rx_preeq_Wlo                MOD_VARS._ph2n_rx_preeq_Wlo
#define ph2n_rx_preeq_Wme                MOD_VARS._ph2n_rx_preeq_Wme
#define ph2n_rx_receive_agc2_level       MOD_VARS._ph2n_rx_receive_agc2_level
#define ph2n_rx_receive_gain             MOD_VARS._ph2n_rx_receive_gain
#define ph2n_rx_receive_level            MOD_VARS._ph2n_rx_receive_level
#define ph2n_rx_mse_bias                 MOD_VARS._ph2n_rx_mse_bias
#define ph2n_rx_preeq_exponent           MOD_VARS._ph2n_rx_preeq_exponent
#define v34n_established_ph4_count       MOD_VARS._v34n_established_ph4_count
#define v34n_rx_frequency_offset         MOD_VARS._v34n_rx_frequency_offset
#define v34n_tx_frequency_offset         MOD_VARS._v34n_tx_frequency_offset
#define v34_frame_rx_bit_count           MOD_VARS._v34_frame_rx_bit_count
#define v34_frame_rx_word_count          MOD_VARS._v34_frame_rx_word_count
#define v34_frame_tx_bit_count           MOD_VARS._v34_frame_tx_bit_count
#define v34_frame_tx_word_count          MOD_VARS._v34_frame_tx_word_count
#define v34_frame_rx_bit_parse_pointer_bits MOD_VARS._v34_frame_rx_bit_parse_pointer_bits
#define v34n_rx_transmit_gain            MOD_VARS._v34n_rx_transmit_gain
#define current_crc                      MOD_VARS._current_crc
#define n16_bits                         MOD_VARS._n16_bits
#define ph2n_probing_maxrate             MOD_VARS._ph2n_probing_maxrate
#define ph2n_probing_preemph             MOD_VARS._ph2n_probing_preemph
#define ph2n_rx_train_16pt               MOD_VARS._ph2n_rx_train_16pt
#define ph2n_rx_use_shaping              MOD_VARS._ph2n_rx_use_shaping
#define v34n_data_rate_MAXIMUM           MOD_VARS._v34n_data_rate_MAXIMUM
#define v34n_parm_16point_option         MOD_VARS._v34n_parm_16point_option
#define v34n_parm_asymmetric_option      MOD_VARS._v34n_parm_asymmetric_option
#define v34n_parm_attenuation_option     MOD_VARS._v34n_parm_attenuation_option
#define v34n_parm_auxiliary_option       MOD_VARS._v34n_parm_auxiliary_option
#define v34n_parm_clock_option           MOD_VARS._v34n_parm_clock_option
#define v34n_parm_CME_option             MOD_VARS._v34n_parm_CME_option
#define v34n_parm_data_rate_option       MOD_VARS._v34n_parm_data_rate_option
#define v34n_parm_difference_option      MOD_VARS._v34n_parm_difference_option
#define v34n_parm_hi_carrier_option      MOD_VARS._v34n_parm_hi_carrier_option
#define v34n_parm_hi_data_rate_option    MOD_VARS._v34n_parm_hi_data_rate_option
#define v34n_parm_lo_carrier_option      MOD_VARS._v34n_parm_lo_carrier_option
#define v34n_parm_nonlinear_option       MOD_VARS._v34n_parm_nonlinear_option
#define v34n_parm_precoder_option        MOD_VARS._v34n_parm_precoder_option
#define v34n_parm_ptt_attenuation_option MOD_VARS._v34n_parm_ptt_attenuation_option
#define v34n_parm_ptt_hi_carrier_option  MOD_VARS._v34n_parm_ptt_hi_carrier_option
#define v34n_parm_ptt_lo_carrier_option  MOD_VARS._v34n_parm_ptt_lo_carrier_option
#define v34n_parm_ptt_symbol_option      MOD_VARS._v34n_parm_ptt_symbol_option
#define v34n_parm_shaping_option         MOD_VARS._v34n_parm_shaping_option
#define v34n_parm_symbol_option          MOD_VARS._v34n_parm_symbol_option
#define v34n_parm_trellis_option         MOD_VARS._v34n_parm_trellis_option
#define v34n_rxtx_cleardown_active       MOD_VARS._v34n_rxtx_cleardown_active
#define v34n_rxtx_hi_data_rate_option    MOD_VARS._v34n_rxtx_hi_data_rate_option
#define v34n_rx_carrier_frequency        MOD_VARS._v34n_rx_carrier_frequency
#define v34n_rx_clock_mode               MOD_VARS._v34n_rx_clock_mode
#define v34n_rx_MD_length                MOD_VARS._v34n_rx_MD_length
#define v34n_rx_preemph_value            MOD_VARS._v34n_rx_preemph_value
#define v34n_rx_probing_maxrate          MOD_VARS._v34n_rx_probing_maxrate
#define v34n_rx_symbol_rate              MOD_VARS._v34n_rx_symbol_rate
#define v34n_tx_carrier_frequency        MOD_VARS._v34n_tx_carrier_frequency
#define v34n_tx_clock_mode               MOD_VARS._v34n_tx_clock_mode
#define v34n_tx_data_rate_option         MOD_VARS._v34n_tx_data_rate_option
#define v34n_tx_MD_length                MOD_VARS._v34n_tx_MD_length
#define v34n_tx_preemph_value            MOD_VARS._v34n_tx_preemph_value
#define v34n_tx_probing_maxrate          MOD_VARS._v34n_tx_probing_maxrate
#define v34n_tx_symbol_rate              MOD_VARS._v34n_tx_symbol_rate
#define v34_frame_tx_bit_buffer          MOD_VARS._v34_frame_tx_bit_buffer
#define v34_frame_tx_bit_pointer         MOD_VARS._v34_frame_tx_bit_pointer
#define v34_frame_rx_bit_buffer          MOD_VARS._v34_frame_rx_bit_buffer
#define v34_frame_rx_bit_offset          MOD_VARS._v34_frame_rx_bit_offset
#define v34_frame_rx_bit_parse_pointer   MOD_VARS._v34_frame_rx_bit_parse_pointer
#define v34_frame_rx_calculated_crc      MOD_VARS._v34_frame_rx_calculated_crc

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

typedef struct {
	parm_d     uint16                      _parm__dm_clock_control;
} mod_parms_t;

/* ************************************************************************* */

DEF_DATA(mod_parms_t, mod_parms)
#define MOD_PARMS_DATA mod_parms_t mod_parms
#define MOD_PARMS USE_DATA(mod_parms)
#define mod_parms_used

/* ************************************************************************* */

#define parm__dm_clock_control           MOD_PARMS._parm__dm_clock_control

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

typedef struct {
	stat_d     uint16                      _stat__round_trip_delay;
} mod_stats_t;

/* ************************************************************************* */

DEF_DATA(mod_stats_t, mod_stats)
#define MOD_STATS_DATA mod_stats_t mod_stats
#define MOD_STATS USE_DATA(mod_stats)
#define mod_stats_used

/* ************************************************************************* */

#define stat__round_trip_delay           MOD_STATS._stat__round_trip_delay

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

typedef struct {
	local_d    bool                        _sdt_found_detect_flag;
	local_d    bool                        _sdt_initial_detect_flag;
	local_d    uint16                      _and_mask;
	local_d    uint16                      _or_mask;
	local_d    uint16                      _received_rate_seq;
	local_d    uint16                      _v24_cts;
	local_d    uint16                      _v24_dcd;
	local_d    uint16                      _v24_dsr;
	local_d    uint16                      _v24_rxd;
	local_d    uint16                      _v24_txd;
	local_d    uint16                      _bulk_delay_buffer [BULK_DELAY_BUFFER_SIZEOF];
} mod_local_t;

/* ************************************************************************* */

DEF_DATA(mod_local_t, mod_local)
#define MOD_LOCAL_DATA mod_local_t mod_local
#define MOD_LOCAL USE_DATA(mod_local)
#define mod_local_used

/* ************************************************************************* */

#define sdt_found_detect_flag            MOD_LOCAL._sdt_found_detect_flag
#define sdt_initial_detect_flag          MOD_LOCAL._sdt_initial_detect_flag
#define and_mask                         MOD_LOCAL._and_mask
#define or_mask                          MOD_LOCAL._or_mask
#define received_rate_seq                MOD_LOCAL._received_rate_seq
#define v24_cts                          MOD_LOCAL._v24_cts
#define v24_dcd                          MOD_LOCAL._v24_dcd
#define v24_dsr                          MOD_LOCAL._v24_dsr
#define v24_rxd                          MOD_LOCAL._v24_rxd
#define v24_txd                          MOD_LOCAL._v24_txd
#define bulk_delay_buffer                MOD_LOCAL._bulk_delay_buffer

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

typedef struct {
	fast_d     fract                       _AGC_2_REFERENCE_LEVEL;
	fast_d     fract                       _agc_2_signal_imag;
	fast_d     fract                       _agc_2_signal_real;
	fast_d     fract                       _out_vxxmod_local;
	fast_d     fract                       _remote_ec_sum;
	fast_d     fract                       _total_ec_sum;
	fast_d     phase_t                     _demodulator_decrement;
	fast_d     phase_t                     _demodulator_phase;
	fast_d     sint15                      _echo_canceller_poffset;
	fast_d     sint15                      _local_interpolator_poffset;
	fast_d     phase_t                     _modulator_increment;
	fast_d     phase_t                     _modulator_phase;
	fast_d     sint15                      _rate_reduction_counter;
	fast_d     sint15                      _remote_interpolator_poffset;
	fast_d     phase_t                     _tx_clock_phase_local;
	fast_d     phase_t                     _tx_clock_phase_remote;
	fast_d     sint15                      _tx_passband_poffset;
	fast_d     uint16                      _rx_interpolator_poffset;
	fast_d     uint16                      _rx_lpf_poffset;
	fast_d     const fract *               _rx_lpf_coefs;
	fast_d     fract CIRCULAR              _echo_canceller_buffer [2*((xV34_XX_ECHO_BUFFER_SIZE)/2)];
	fast_d     fract32                     _echo_canceller_coefs32 [xV34_XX_TOTAL_TAPS];
	fast_d     fract CIRCULAR              _rx_lpf_buffer_real [2*((xC8K0_V34_XX_HALF_RX_LPF_SIZE)*2)];
	fast_d     ufract                      _v34n_tx_transmit_gain;
	fast_d     fract CIRCULAR              _tx_passband_buffer [2*(xC8K0_V34_XX_TX_BPF_SIZE-1)];
} mod_fast_t;

/* ************************************************************************* */

DEF_DATA(mod_fast_t, mod_fast)
#define MOD_FAST_DATA mod_fast_t mod_fast
#define MOD_FAST USE_DATA(mod_fast)
#define mod_fast_used

/* ************************************************************************* */

#define AGC_2_REFERENCE_LEVEL            MOD_FAST._AGC_2_REFERENCE_LEVEL
#define agc_2_signal_imag                MOD_FAST._agc_2_signal_imag
#define agc_2_signal_real                MOD_FAST._agc_2_signal_real
#define out_vxxmod_local                 MOD_FAST._out_vxxmod_local
#define remote_ec_sum                    MOD_FAST._remote_ec_sum
#define total_ec_sum                     MOD_FAST._total_ec_sum
#define demodulator_decrement            MOD_FAST._demodulator_decrement
#define demodulator_phase                MOD_FAST._demodulator_phase
#define echo_canceller_poffset           MOD_FAST._echo_canceller_poffset
#define local_interpolator_poffset       MOD_FAST._local_interpolator_poffset
#define modulator_increment              MOD_FAST._modulator_increment
#define modulator_phase                  MOD_FAST._modulator_phase
#define rate_reduction_counter           MOD_FAST._rate_reduction_counter
#define remote_interpolator_poffset      MOD_FAST._remote_interpolator_poffset
#define tx_clock_phase_local             MOD_FAST._tx_clock_phase_local
#define tx_clock_phase_remote            MOD_FAST._tx_clock_phase_remote
#define tx_passband_poffset              MOD_FAST._tx_passband_poffset
#define rx_interpolator_poffset          MOD_FAST._rx_interpolator_poffset
#define rx_lpf_poffset                   MOD_FAST._rx_lpf_poffset
#define rx_lpf_coefs                     MOD_FAST._rx_lpf_coefs
#define echo_canceller_buffer            MOD_FAST._echo_canceller_buffer
#define echo_canceller_coefs32           MOD_FAST._echo_canceller_coefs32
#define rx_lpf_buffer_real               MOD_FAST._rx_lpf_buffer_real
#define v34n_tx_transmit_gain            MOD_FAST._v34n_tx_transmit_gain
#define tx_passband_buffer               MOD_FAST._tx_passband_buffer

/* ************************************************************************* */

#endif /* _DATA_MOD_H */
