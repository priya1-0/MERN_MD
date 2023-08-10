
/* ************************************************************************* */
/*
 *	ph2.h
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
 *	This file contains automatically generated data for ph2.
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

#ifndef _DATA_PH2_H
#define _DATA_PH2_H
#include "data/sections.h"

/* ************************************************************************* */

typedef struct {
	var_d      bool                        _ph2_AB_detected;
	var_d      bool                        _ph2_AB_detect_enable;
	var_d      bool                        _ph2_INFOMARKS_detected;
	var_d      bool                        _ph2_INFOMARKS_detect_enable;
	var_d      bool                        _ph2_INFO_detected;
	var_d      bool                        _ph2_INFO_detect_enable;
	var_d      bool                        _ph2_retrain_flag;
	var_d      fract                       _helper_imag;
	var_d      fract                       _helper_real;
	var_d      fract                       _ph2n_probing_adj_Whi;
	var_d      fract                       _ph2n_probing_adj_Wlo;
	var_d      fract                       _ph2n_probing_adj_Wme;
	var_d      fract                       _ph2n_probing_Gr_gain;
	var_d      fract                       _ph2n_probing_L1_log_N_buffer [PH2P_NO_TONES];
	var_d      fract                       _ph2n_probing_L1_log_P_buffer [PH2P_NO_TONES];
	var_d      fract                       _ph2n_probing_receive_agc2_level;
	var_d      fract                       _ph2n_probing_receive_gain;
	var_d      fract                       _ph2n_probing_receive_level;
	var_d      fract                       _ph2n_probing_receive_preeq_level;
	var_d      fract                       _ph2n_probing_Whi;
	var_d      fract                       _ph2n_probing_Wlo;
	var_d      fract                       _ph2n_probing_Wme;
	var_d      fract                       _ph2p_anal_adj_log_Whi;
	var_d      fract                       _ph2p_anal_adj_log_Wlo;
	var_d      fract                       _ph2p_anal_adj_log_Wme;
	var_d      fract                       _ph2p_anal_gain_average;
	var_d      fract                       _ph2p_anal_L2_variance;
	var_d      fract                       _ph2p_anal_log_adjust;
	var_d      fract                       _ph2p_anal_log_BxR_buffer [PH2P_NO_PREEQ_BINS];
	var_d      fract                       _ph2p_anal_log_B_buffer [PH2P_NO_PREEQ_BINS];
	var_d      fract                       _ph2p_anal_log_Eb;
	var_d      fract                       _ph2p_anal_log_Ep;
	var_d      fract                       _ph2p_anal_log_E_buffer [PH2P_NO_TONES];
	var_d      fract                       _ph2p_anal_log_Gr;
	var_d      fract                       _ph2p_anal_log_Gr_exponent;
	var_d      fract                       _ph2p_anal_log_Gr_remainder;
	var_d      fract                       _ph2p_anal_log_Gt;
	var_d      fract                       _ph2p_anal_log_N_buffer [PH2P_NO_TONES];
	var_d      fract                       _ph2p_anal_log_P_buffer [PH2P_NO_TONES];
	var_d      fract                       _ph2p_anal_log_P_buffer_adj [PH2P_NO_TONES];
	var_d      fract                       _ph2p_anal_log_R_buffer [PH2P_NO_PREEQ_BINS];
	var_d      fract                       _ph2p_anal_log_S_buffer [PH2P_NO_TONES];
	var_d      fract                       _ph2p_anal_log_Whi;
	var_d      fract                       _ph2p_anal_log_Wlo;
	var_d      fract                       _ph2p_anal_log_Wme;
	var_d      fract                       _ph2p_anal_log_Z_buffer [PH2P_NO_TONES];
	var_d      fract                       _ph2p_anal_variance_00_table [PH2P_NO_PREEMPHASIS];
	var_d      fract                       _ph2p_anal_variance_01_table [PH2P_NO_PREEMPHASIS];
	var_d      fract                       _ph2p_anal_variance_02_table [PH2P_NO_PREEMPHASIS];
	var_d      fract                       _ph2p_anal_variance_03_table [PH2P_NO_PREEMPHASIS];
	var_d      fract                       _ph2p_anal_variance_04_table [PH2P_NO_PREEMPHASIS];
	var_d      fract                       _ph2p_anal_variance_05_table [PH2P_NO_PREEMPHASIS];
	var_d      fract                       _ph2p_anal_variance_10_table [PH2P_NO_PREEMPHASIS];
	var_d      fract                       _ph2p_anal_variance_11_table [PH2P_NO_PREEMPHASIS];
	var_d      fract                       _ph2p_anal_variance_12_table [PH2P_NO_PREEMPHASIS];
	var_d      fract                       _ph2p_anal_variance_13_table [PH2P_NO_PREEMPHASIS];
	var_d      fract                       _ph2p_anal_variance_14_table [PH2P_NO_PREEMPHASIS];
	var_d      fract                       _ph2p_anal_variance_15_table [PH2P_NO_PREEMPHASIS];
	var_d      fract                       _ph2p_L2_log_power_display_buffer [PH2P_NO_BINS_x2];
	var_d      fract                       _ph2p_powr_powr_cx_buffer [PH2P_BLOCKSIZE];
	var_d      fract                       _ph2p_powr_temp_x_buffer [2*PH2P_BLOCKSIZE];
	var_d      fract                       _ph2_ac_sample_buffer [2*(PH2_AUTOCORREL_BUFFER_LENGTH)];
	var_d      fract                       _ph2_dummy_loopback_imag;
	var_d      fract                       _ph2_dummy_loopback_real;
	var_d      fract                       _ph2_dummy_loopback_sample;
	var_d      fract                       _ph2_rx_checker_bpf_buffer [2*(63+1-1)];
	var_d      fract                       _ph2_rx_checker_energy;
	var_d      fract                       _ph2_rx_passband_buffer [2*(PH2_RX_DATA_SIZE+16)];
	var_d      fract                       _ph2_rx_special_bpf_buffer [2*(63+1-1)];
	var_d      fract                       _ph2_tx_dcd_threshold;
	var_d      fract                       _ph2_tx_passband_buffer [2*(PH2_TX_DATA_SIZE+16)];
	var_d      fract                       _saved_precalculated_correct;
	var_d      fract                       _THD_measurement_actual;
	var_d      fract                       _THD_measurement_compare;
	var_d      fract                       _THD_measurement_noise;
	var_d      fract                       _THD_measurement_relative;
	var_d      fract                       _THD_measurement_variance;
	var_d      fract                       _THD_sum_L1_magnitude;
	var_d      fract                       _THD_sum_L2_magnitude;
	var_d      fract                       _THD_sum_L2_N_norm;
	var_d      fract                       _THD_sum_L2_S_norm;
	var_d      fract                       _THD_sum_L2_S_over_N;
	var_d      fract                       _THD_sum_L2_S_power;
	var_d      fract                       _v34n_rx_optional_gain;
	var_d      fract                       _v34n_rx_required_gain;
	var_d      fract                       _v34n_tx_optional_gain;
	var_d      fract                       _v34n_tx_required_gain;
	var_d      fract *                     _ph2p_anal_log_E_plus_start;
	var_d      fract *                     _ph2p_anal_log_N_plus_start;
	var_d      fract *                     _ph2p_anal_log_P_plus_start;
	var_d      fract *                     _ph2p_anal_log_S_plus_start;
	var_d      fract *                     _ph2p_anal_log_Z_plus_start;
	var_d      fract *                     _ph2p_anal_maxrate_lookup_pointer;
	var_d      const fract *               _ph2p_anal_preemph1_pointer;
	var_d      const fract *               _ph2p_anal_preemph6_pointer;
	var_d      fract *                     _ph2p_anal_variance_CS_pointer;
	var_d      fract *                     _ph2p_anal_variance_CS_table;
	var_d      fract *                     _ph2_rx_checker_bpf_coef_pointer;
	var_d      fract *                     _ph2_tx_passband_coef_pointer;
	var_d      fract *                     _saved_Lx_log_N_pointer;
	var_d      fract *                     _saved_Lx_log_power_pointer;
	var_d      fract *                     _saved_Lx_log_P_pointer;
	var_d      fract CIRCULAR              _ph2_rx_rate_conv_9K6_8K0_buffer [2*(PH2_RX_RATE_CONV_DATA_BUFFER)];
	var_d      fract CIRCULAR              _ph2_tx_interpolator_buffer_imag [2*(PH2_TX_INTERPOLATOR_SIZE)];
	var_d      fract CIRCULAR              _ph2_tx_interpolator_buffer_real [2*(PH2_TX_INTERPOLATOR_SIZE)];
	var_d      fract CIRCULAR              _ph2_tx_rate_conv_9K6_8K0_buffer [2*(PH2_TX_RATE_CONV_DATA_BUFFER)];
	var_d      fract*                      _ph2p_bg_sample_in_pointer;
	var_d      fract*                      _ph2_rx_passband_coef_pointer;
	var_d      fract*                      _ph2_rx_special_bpf_coef_pointer;
	var_d      fract32                     _ph2p_fefo_ar_ai_stage1_buffer32 [2*(PH2P_FEFO_BIN_COUNT)];
	var_d      fract32                     _ph2p_fefo_ar_ai_stage2_buffer32 [2*(PH2P_FEFO_BIN_COUNT)];
	var_d      fract32                     _ph2p_fefo_delta_buffer32 [PH2P_NO_BINS];
	var_d      fract32                     _ph2p_fefo_delta_buffer_hertz32 [PH2P_NO_BINS];
	var_d      fract32                     _ph2p_fefo_dw_k_buffer32 [PH2P_FEFO_BIN_COUNT];
	var_d      fract32                     _ph2p_fefo_dw_k_buffer_scaled32 [PH2P_FEFO_BIN_COUNT];
	var_d      fract32                     _ph2p_fefo_test_b32;
	var_d      fract32                     _ph2p_fefo_test_b_prime32;
	var_d      fract32                     _ph2p_fefo_test_delta32;
	var_d      fract32                     _ph2p_fefo_test_m_prime32;
	var_d      fract32                     _ph2p_powr_dmod_rx_buffer32 [PH2P_BLOCKSIZE + PH2P_WINDOW_LENGTH_NOISE];
	var_d      fract32                     _ph2p_powr_L1_spectrum_power_buffer32 [PH2P_NO_BINS_x2];
	var_d      fract32                     _ph2p_powr_L2_spectrum_power_buffer32 [PH2P_NO_BINS_x2];
	var_d      fract32                     _ph2p_powr_N_buffer32 [PH2P_NO_TONES];
	var_d      fract32                     _ph2p_powr_P_buffer32 [PH2P_NO_TONES];
	var_d      fract32                     _ph2_ac_lpf_data_buffer32 [PH2_LPF_DATA_BUFFER_LENGTH];
	var_d      fract32                     _ph2_rx_signal_detect_filter32;
	var_d      fract32*                    _saved_Lx_spectrum_power_pointer32;
	var_d      fract40                     _ph2_rx_checker_sum40;
	var_d      powr_phase_offset_t         _ph2p_fefo_powr_phase_offset_buffer [PH2P_NO_BINS];
	var_d      powr_variable_setup_table_t _ph2p_powr_variable_setup_table [PH2P_NO_BINS_x2];
	var_d      sint15                      _ph2n_probing_frequency_buffer [PH2P_NO_TONES];
	var_d      sint15                      _ph2n_probing_Gr_exponent;
	var_d      sint15                      _ph2n_probing_L1_SE_power_adjust;
	var_d      sint15                      _ph2n_rx_frequency_offset;
	var_d      sint15                      _ph2n_rx_transmit_attenuation;
	var_d      sint15                      _ph2n_tx_transmit_attenuation;
	var_d      sint15                      _ph2p_anal_count_length;
	var_d      sint15                      _ph2p_anal_preemph_index;
	var_d      sint15                      _ph2p_anal_start_bin;
	var_d      sint15                      _ph2p_bg_dlyd64_out_offset;
	var_d      sint15                      _ph2p_bg_sample_offset;
	var_d      sint15                      _ph2p_bg_sample_out_offset;
	var_d      sint15                      _ph2p_fefo_bin_step;
	var_d      sint15                      _ph2p_fefo_gain_adjust_shift;
	var_d      sint15                      _ph2p_fefo_holdoff_time;
	var_d      sint15                      _ph2p_fefo_powr_SE_gain_adjust;
	var_d      sint15                      _ph2p_fefo_SB_gain_adjust;
	var_d      sint15                      _ph2p_fefo_start_bin_phase_index;
	var_d      phase_t                     _ph2p_fefo_ws_k_buffer [PH2P_FEFO_BIN_COUNT];
	var_d      sint15                      _ph2p_fefo_y_coord_scale_N;
	var_d      sint15                      _ph2p_powr_dmod_rx_offset32;
	var_d      sint15                      _PH2P_POWR_LX_FINAL_TUNE;
	var_d      sint15                      _PH2P_POWR_LX_PROCESS_LENGTH;
	var_d      sint15                      _ph2p_powr_rx_clear_length;
	var_d      sint15                      _ph2p_powr_saved_holdoff_I7_offset;
	var_d      sint15                      _ph2p_powr_SB_power_adjust;
	var_d      sint15                      _ph2s_INFO0_ack_counter;
	var_d      sint15                      _ph2s_orig_INFO1_counter;
	var_d      sint15                      _ph2_AB_zero_count;
	var_d      sint15                      _ph2_ac_sample_offset;
	var_d      sint15                      _ph2_guard_counter;
	var_d      sint15                      _ph2_guard_tone_enable;
	var_d      phase_t                     _ph2_guard_tone_increment;
	var_d      phase_t                     _ph2_guard_tone_phase;
	var_d      sint15                      _ph2_INFO_detect_state;
	var_d      sint15                      _ph2_rxtx_rate_conv_modulo_counter;
	var_d      sint15                      _ph2_rx_baud_counter;
	var_d      sint15                      _ph2_rx_checker_bpf_offset;
	var_d      sint15                      _ph2_rx_checker_count;
	var_d      sint15                      _ph2_rx_dcd_level;
	var_d      sint15                      _ph2_rx_passband_offset;
	var_d      sint15                      _ph2_rx_rate_conv_9K6_8K0_pointer;
	var_d      sint15                      _ph2_rx_special_bpf_offset;
	var_d      sint15                      _ph2_tx_baud_counter;
	var_d      sint15                      _ph2_tx_interpolator_offset;
	var_d      sint15                      _ph2_tx_Lx_offset;
	var_d      sint15                      _ph2_tx_passband_offset;
	var_d      sint15                      _ph2_tx_rate_conv_9K6_8K0_pointer;
	var_d      sint15                      _v34p_bg_block_count;
	var_d      sint15                      _v34p_bg_sample_count;
	var_d      sint15                      _v34_frame_rx_save_bit_count;
	var_d      sint15 *                    _saved_Lx_SE_power_adjust_pointer;
	var_d      const sint15 *              _v34_frame_rx_save_bit_parse_pointer_bits;
	var_d      ufract                      _ph2p_anal_flatvar;
	var_d      ufract                      _ph2_guard_tone_amplitude;
	var_d      ufract                      _ph2_guard_tone_gain;
	var_d      ufract                      _ph2_scale_value;
	var_d      ufract                      _ph2_tx_Lx_gain;
	var_d      uint16                      _ph2n_probing_train_16pt;
	var_d      uint16                      _ph2n_rx_acknowledge;
	var_d      uint16                      _ph2n_rx_carrier [V34N_MAX_SYMBOL+1];
	var_d      uint16                      _ph2n_rx_optional_attenuation;
	var_d      uint16                      _ph2n_rx_preemph [V34N_MAX_SYMBOL+1];
	var_d      uint16                      _ph2n_rx_required_attenuation;
	var_d      uint16                      _ph2n_tx_acknowledge;
	var_d      uint16                      _ph2n_tx_carrier [V34N_MAX_SYMBOL+1];
	var_d      uint16                      _ph2n_tx_frequency_offset;
	var_d      uint16                      _ph2n_tx_maxrate [V34N_MAX_SYMBOL+1];
	var_d      uint16                      _ph2n_tx_optional_attenuation;
	var_d      uint16                      _ph2n_tx_preemph [V34N_MAX_SYMBOL+1];
	var_d      uint16                      _ph2n_tx_required_attenuation;
	var_d      uint16                      _ph2p_anal_maxrate;
	var_d      uint16                      _ph2p_anal_maxrates_00_table [PH2P_NO_PREEMPHASIS];
	var_d      uint16                      _ph2p_anal_maxrates_01_table [PH2P_NO_PREEMPHASIS];
	var_d      uint16                      _ph2p_anal_maxrates_02_table [PH2P_NO_PREEMPHASIS];
	var_d      uint16                      _ph2p_anal_maxrates_03_table [PH2P_NO_PREEMPHASIS];
	var_d      uint16                      _ph2p_anal_maxrates_04_table [PH2P_NO_PREEMPHASIS];
	var_d      uint16                      _ph2p_anal_maxrates_05_table [PH2P_NO_PREEMPHASIS];
	var_d      uint16                      _ph2p_anal_maxrates_10_table [PH2P_NO_PREEMPHASIS];
	var_d      uint16                      _ph2p_anal_maxrates_11_table [PH2P_NO_PREEMPHASIS];
	var_d      uint16                      _ph2p_anal_maxrates_12_table [PH2P_NO_PREEMPHASIS];
	var_d      uint16                      _ph2p_anal_maxrates_13_table [PH2P_NO_PREEMPHASIS];
	var_d      uint16                      _ph2p_anal_maxrates_14_table [PH2P_NO_PREEMPHASIS];
	var_d      uint16                      _ph2p_anal_maxrates_15_table [PH2P_NO_PREEMPHASIS];
	var_d      uint16                      _ph2p_anal_maxrate_results [PH2P_NO_SYMBOL_RATES*PH2P_NO_CARRIERS];
	var_d      uint16                      _ph2p_anal_preemph_results_buffer [PH2P_NO_SYMBOL_RATES*PH2P_NO_CARRIERS];
	var_d      uint16                      _ph2p_fefo_holdoff_flag;
	var_d      uint16                      _ph2p_powr_L1_delay_delay_start;
	var_d      uint16                      _ph2p_powr_L1_to_L2_delay_offset;
	var_d      uint16                      _ph2_AB_edge_correl_last;
	var_d      uint16                      _ph2_AB_qualify_length;
	var_d      uint16                      _ph2_ac_sample_bit_pattern [10];
	var_d      uint16                      _ph2_data_timeout_enable;
	var_d      uint16                      _ph2_data_timeout_start;
	var_d      uint16                      _ph2_INFOMARKS_one_count;
	var_d      uint16                      _ph2_INFOMARKS_qualify_length;
	var_d      uint16                      _ph2_INFO_correl_last;
	var_d      uint16                      _ph2_rx_baud_current;
	var_d      uint16                      _ph2_rx_checker_length;
	var_d      uint16                      _ph2_rx_data_size;
	var_d      uint16                      _ph2_rx_data_size_1;
	var_d      uint16                      _ph2_rx_dcd_integration_time;
	var_d      uint16                      _ph2_rx_signal_detect;
	var_d      uint16                      _ph2_tx_baud_current;
	var_d      uint16                      _ph2_tx_data_size;
	var_d      uint16                      _ph2_tx_data_size_1;
	var_d      uint16                      _v34p_bg_block_finished_flags [PH2P_SAMPLE_MAX_PH2B_BLOCKS];
	var_d      uint16 *                    _ph2p_anal_maxrates_CS_pointer;
	var_d      uint16 *                    _ph2p_anal_maxrates_CS_table;
	var_d      uint16 *                    _ph2p_anal_maxrate_results_pointer;
	var_d      uint16 *                    _ph2p_anal_preemph_results_pointer;
	var_d      uint16 **                   _v34_frame_rx_save_bit_parse_pointer;
	var_d      uint16*                     _v34n_rx_INFO0_body [14];
	var_d      uint16*                     _v34n_rx_INFO1a_body [9];
	var_d      uint16*                     _v34n_rx_INFO1c_body [22];
	var_d      uint16*                     _v34n_tx_INFO0_body [14];
	var_d      uint16*                     _v34n_tx_INFO1a_body [9];
	var_d      uint16*                     _v34n_tx_INFO1c_body [22];
	var_d      sint15                      _ph2n_rx_maxrate [V34N_MAX_SYMBOL+1];
	var_d      fract40                     _ph2_ac_output40;
	var_d      fract40                     _ph2p_powr_variable_buffer40 [2*PH2P_NO_BINS_x2];
	var_d      fract40                     _ph2p_powr_spectrum_power_buffer40 [PH2P_NO_BINS_x2];
	var_d      fract40                     _ph2p_powr_reconstruction_buffer40 [2*PH2P_NO_BINS];
	var_d      fract40                     _ph2p_fefo_spectrum_buffer40 [2*PH2P_FEFO_BIN_COUNT];
} ph2_vars_t;

/* ************************************************************************* */

DEF_DATA(ph2_vars_t, ph2_vars)
#define PH2_VARS_DATA ph2_vars_t ph2_vars
#define PH2_VARS USE_DATA(ph2_vars)
#define ph2_vars_used

/* ************************************************************************* */

#define ph2_AB_detected                  PH2_VARS._ph2_AB_detected
#define ph2_AB_detect_enable             PH2_VARS._ph2_AB_detect_enable
#define ph2_INFOMARKS_detected           PH2_VARS._ph2_INFOMARKS_detected
#define ph2_INFOMARKS_detect_enable      PH2_VARS._ph2_INFOMARKS_detect_enable
#define ph2_INFO_detected                PH2_VARS._ph2_INFO_detected
#define ph2_INFO_detect_enable           PH2_VARS._ph2_INFO_detect_enable
#define ph2_retrain_flag                 PH2_VARS._ph2_retrain_flag
#define helper_imag                      PH2_VARS._helper_imag
#define helper_real                      PH2_VARS._helper_real
#define ph2n_probing_adj_Whi             PH2_VARS._ph2n_probing_adj_Whi
#define ph2n_probing_adj_Wlo             PH2_VARS._ph2n_probing_adj_Wlo
#define ph2n_probing_adj_Wme             PH2_VARS._ph2n_probing_adj_Wme
#define ph2n_probing_Gr_gain             PH2_VARS._ph2n_probing_Gr_gain
#define ph2n_probing_L1_log_N_buffer     PH2_VARS._ph2n_probing_L1_log_N_buffer
#define ph2n_probing_L1_log_P_buffer     PH2_VARS._ph2n_probing_L1_log_P_buffer
#define ph2n_probing_receive_agc2_level  PH2_VARS._ph2n_probing_receive_agc2_level
#define ph2n_probing_receive_gain        PH2_VARS._ph2n_probing_receive_gain
#define ph2n_probing_receive_level       PH2_VARS._ph2n_probing_receive_level
#define ph2n_probing_receive_preeq_level PH2_VARS._ph2n_probing_receive_preeq_level
#define ph2n_probing_Whi                 PH2_VARS._ph2n_probing_Whi
#define ph2n_probing_Wlo                 PH2_VARS._ph2n_probing_Wlo
#define ph2n_probing_Wme                 PH2_VARS._ph2n_probing_Wme
#define ph2p_anal_adj_log_Whi            PH2_VARS._ph2p_anal_adj_log_Whi
#define ph2p_anal_adj_log_Wlo            PH2_VARS._ph2p_anal_adj_log_Wlo
#define ph2p_anal_adj_log_Wme            PH2_VARS._ph2p_anal_adj_log_Wme
#define ph2p_anal_gain_average           PH2_VARS._ph2p_anal_gain_average
#define ph2p_anal_L2_variance            PH2_VARS._ph2p_anal_L2_variance
#define ph2p_anal_log_adjust             PH2_VARS._ph2p_anal_log_adjust
#define ph2p_anal_log_BxR_buffer         PH2_VARS._ph2p_anal_log_BxR_buffer
#define ph2p_anal_log_B_buffer           PH2_VARS._ph2p_anal_log_B_buffer
#define ph2p_anal_log_Eb                 PH2_VARS._ph2p_anal_log_Eb
#define ph2p_anal_log_Ep                 PH2_VARS._ph2p_anal_log_Ep
#define ph2p_anal_log_E_buffer           PH2_VARS._ph2p_anal_log_E_buffer
#define ph2p_anal_log_Gr                 PH2_VARS._ph2p_anal_log_Gr
#define ph2p_anal_log_Gr_exponent        PH2_VARS._ph2p_anal_log_Gr_exponent
#define ph2p_anal_log_Gr_remainder       PH2_VARS._ph2p_anal_log_Gr_remainder
#define ph2p_anal_log_Gt                 PH2_VARS._ph2p_anal_log_Gt
#define ph2p_anal_log_N_buffer           PH2_VARS._ph2p_anal_log_N_buffer
#define ph2p_anal_log_P_buffer           PH2_VARS._ph2p_anal_log_P_buffer
#define ph2p_anal_log_P_buffer_adj       PH2_VARS._ph2p_anal_log_P_buffer_adj
#define ph2p_anal_log_R_buffer           PH2_VARS._ph2p_anal_log_R_buffer
#define ph2p_anal_log_S_buffer           PH2_VARS._ph2p_anal_log_S_buffer
#define ph2p_anal_log_Whi                PH2_VARS._ph2p_anal_log_Whi
#define ph2p_anal_log_Wlo                PH2_VARS._ph2p_anal_log_Wlo
#define ph2p_anal_log_Wme                PH2_VARS._ph2p_anal_log_Wme
#define ph2p_anal_log_Z_buffer           PH2_VARS._ph2p_anal_log_Z_buffer
#define ph2p_anal_variance_00_table      PH2_VARS._ph2p_anal_variance_00_table
#define ph2p_anal_variance_01_table      PH2_VARS._ph2p_anal_variance_01_table
#define ph2p_anal_variance_02_table      PH2_VARS._ph2p_anal_variance_02_table
#define ph2p_anal_variance_03_table      PH2_VARS._ph2p_anal_variance_03_table
#define ph2p_anal_variance_04_table      PH2_VARS._ph2p_anal_variance_04_table
#define ph2p_anal_variance_05_table      PH2_VARS._ph2p_anal_variance_05_table
#define ph2p_anal_variance_10_table      PH2_VARS._ph2p_anal_variance_10_table
#define ph2p_anal_variance_11_table      PH2_VARS._ph2p_anal_variance_11_table
#define ph2p_anal_variance_12_table      PH2_VARS._ph2p_anal_variance_12_table
#define ph2p_anal_variance_13_table      PH2_VARS._ph2p_anal_variance_13_table
#define ph2p_anal_variance_14_table      PH2_VARS._ph2p_anal_variance_14_table
#define ph2p_anal_variance_15_table      PH2_VARS._ph2p_anal_variance_15_table
#define ph2p_L2_log_power_display_buffer PH2_VARS._ph2p_L2_log_power_display_buffer
#define ph2p_powr_powr_cx_buffer         PH2_VARS._ph2p_powr_powr_cx_buffer
#define ph2p_powr_temp_x_buffer          PH2_VARS._ph2p_powr_temp_x_buffer
#define ph2_ac_sample_buffer             PH2_VARS._ph2_ac_sample_buffer
#define ph2_dummy_loopback_imag          PH2_VARS._ph2_dummy_loopback_imag
#define ph2_dummy_loopback_real          PH2_VARS._ph2_dummy_loopback_real
#define ph2_dummy_loopback_sample        PH2_VARS._ph2_dummy_loopback_sample
#define ph2_rx_checker_bpf_buffer        PH2_VARS._ph2_rx_checker_bpf_buffer
#define ph2_rx_checker_energy            PH2_VARS._ph2_rx_checker_energy
#define ph2_rx_passband_buffer           PH2_VARS._ph2_rx_passband_buffer
#define ph2_rx_special_bpf_buffer        PH2_VARS._ph2_rx_special_bpf_buffer
#define ph2_tx_dcd_threshold             PH2_VARS._ph2_tx_dcd_threshold
#define ph2_tx_passband_buffer           PH2_VARS._ph2_tx_passband_buffer
#define saved_precalculated_correct      PH2_VARS._saved_precalculated_correct
#define THD_measurement_actual           PH2_VARS._THD_measurement_actual
#define THD_measurement_compare          PH2_VARS._THD_measurement_compare
#define THD_measurement_noise            PH2_VARS._THD_measurement_noise
#define THD_measurement_relative         PH2_VARS._THD_measurement_relative
#define THD_measurement_variance         PH2_VARS._THD_measurement_variance
#define THD_sum_L1_magnitude             PH2_VARS._THD_sum_L1_magnitude
#define THD_sum_L2_magnitude             PH2_VARS._THD_sum_L2_magnitude
#define THD_sum_L2_N_norm                PH2_VARS._THD_sum_L2_N_norm
#define THD_sum_L2_S_norm                PH2_VARS._THD_sum_L2_S_norm
#define THD_sum_L2_S_over_N              PH2_VARS._THD_sum_L2_S_over_N
#define THD_sum_L2_S_power               PH2_VARS._THD_sum_L2_S_power
#define v34n_rx_optional_gain            PH2_VARS._v34n_rx_optional_gain
#define v34n_rx_required_gain            PH2_VARS._v34n_rx_required_gain
#define v34n_tx_optional_gain            PH2_VARS._v34n_tx_optional_gain
#define v34n_tx_required_gain            PH2_VARS._v34n_tx_required_gain
#define ph2p_anal_log_E_plus_start       PH2_VARS._ph2p_anal_log_E_plus_start
#define ph2p_anal_log_N_plus_start       PH2_VARS._ph2p_anal_log_N_plus_start
#define ph2p_anal_log_P_plus_start       PH2_VARS._ph2p_anal_log_P_plus_start
#define ph2p_anal_log_S_plus_start       PH2_VARS._ph2p_anal_log_S_plus_start
#define ph2p_anal_log_Z_plus_start       PH2_VARS._ph2p_anal_log_Z_plus_start
#define ph2p_anal_maxrate_lookup_pointer PH2_VARS._ph2p_anal_maxrate_lookup_pointer
#define ph2p_anal_preemph1_pointer       PH2_VARS._ph2p_anal_preemph1_pointer
#define ph2p_anal_preemph6_pointer       PH2_VARS._ph2p_anal_preemph6_pointer
#define ph2p_anal_variance_CS_pointer    PH2_VARS._ph2p_anal_variance_CS_pointer
#define ph2p_anal_variance_CS_table      PH2_VARS._ph2p_anal_variance_CS_table
#define ph2_rx_checker_bpf_coef_pointer  PH2_VARS._ph2_rx_checker_bpf_coef_pointer
#define ph2_tx_passband_coef_pointer     PH2_VARS._ph2_tx_passband_coef_pointer
#define saved_Lx_log_N_pointer           PH2_VARS._saved_Lx_log_N_pointer
#define saved_Lx_log_power_pointer       PH2_VARS._saved_Lx_log_power_pointer
#define saved_Lx_log_P_pointer           PH2_VARS._saved_Lx_log_P_pointer
#define ph2_rx_rate_conv_9K6_8K0_buffer  PH2_VARS._ph2_rx_rate_conv_9K6_8K0_buffer
#define ph2_tx_interpolator_buffer_imag  PH2_VARS._ph2_tx_interpolator_buffer_imag
#define ph2_tx_interpolator_buffer_real  PH2_VARS._ph2_tx_interpolator_buffer_real
#define ph2_tx_rate_conv_9K6_8K0_buffer  PH2_VARS._ph2_tx_rate_conv_9K6_8K0_buffer
#define ph2p_bg_sample_in_pointer        PH2_VARS._ph2p_bg_sample_in_pointer
#define ph2_rx_passband_coef_pointer     PH2_VARS._ph2_rx_passband_coef_pointer
#define ph2_rx_special_bpf_coef_pointer  PH2_VARS._ph2_rx_special_bpf_coef_pointer
#define ph2p_fefo_ar_ai_stage1_buffer32  PH2_VARS._ph2p_fefo_ar_ai_stage1_buffer32
#define ph2p_fefo_ar_ai_stage2_buffer32  PH2_VARS._ph2p_fefo_ar_ai_stage2_buffer32
#define ph2p_fefo_delta_buffer32         PH2_VARS._ph2p_fefo_delta_buffer32
#define ph2p_fefo_delta_buffer_hertz32   PH2_VARS._ph2p_fefo_delta_buffer_hertz32
#define ph2p_fefo_dw_k_buffer32          PH2_VARS._ph2p_fefo_dw_k_buffer32
#define ph2p_fefo_dw_k_buffer_scaled32   PH2_VARS._ph2p_fefo_dw_k_buffer_scaled32
#define ph2p_fefo_test_b32               PH2_VARS._ph2p_fefo_test_b32
#define ph2p_fefo_test_b_prime32         PH2_VARS._ph2p_fefo_test_b_prime32
#define ph2p_fefo_test_delta32           PH2_VARS._ph2p_fefo_test_delta32
#define ph2p_fefo_test_m_prime32         PH2_VARS._ph2p_fefo_test_m_prime32
#define ph2p_powr_dmod_rx_buffer32       PH2_VARS._ph2p_powr_dmod_rx_buffer32
#define ph2p_powr_L1_spectrum_power_buffer32 PH2_VARS._ph2p_powr_L1_spectrum_power_buffer32
#define ph2p_powr_L2_spectrum_power_buffer32 PH2_VARS._ph2p_powr_L2_spectrum_power_buffer32
#define ph2p_powr_N_buffer32             PH2_VARS._ph2p_powr_N_buffer32
#define ph2p_powr_P_buffer32             PH2_VARS._ph2p_powr_P_buffer32
#define ph2_ac_lpf_data_buffer32         PH2_VARS._ph2_ac_lpf_data_buffer32
#define ph2_rx_signal_detect_filter32    PH2_VARS._ph2_rx_signal_detect_filter32
#define saved_Lx_spectrum_power_pointer32 PH2_VARS._saved_Lx_spectrum_power_pointer32
#define ph2_rx_checker_sum40             PH2_VARS._ph2_rx_checker_sum40
#define ph2p_fefo_powr_phase_offset_buffer PH2_VARS._ph2p_fefo_powr_phase_offset_buffer
#define ph2p_powr_variable_setup_table   PH2_VARS._ph2p_powr_variable_setup_table
#define ph2n_probing_frequency_buffer    PH2_VARS._ph2n_probing_frequency_buffer
#define ph2n_probing_Gr_exponent         PH2_VARS._ph2n_probing_Gr_exponent
#define ph2n_probing_L1_SE_power_adjust  PH2_VARS._ph2n_probing_L1_SE_power_adjust
#define ph2n_rx_frequency_offset         PH2_VARS._ph2n_rx_frequency_offset
#define ph2n_rx_transmit_attenuation     PH2_VARS._ph2n_rx_transmit_attenuation
#define ph2n_tx_transmit_attenuation     PH2_VARS._ph2n_tx_transmit_attenuation
#define ph2p_anal_count_length           PH2_VARS._ph2p_anal_count_length
#define ph2p_anal_preemph_index          PH2_VARS._ph2p_anal_preemph_index
#define ph2p_anal_start_bin              PH2_VARS._ph2p_anal_start_bin
#define ph2p_bg_dlyd64_out_offset        PH2_VARS._ph2p_bg_dlyd64_out_offset
#define ph2p_bg_sample_offset            PH2_VARS._ph2p_bg_sample_offset
#define ph2p_bg_sample_out_offset        PH2_VARS._ph2p_bg_sample_out_offset
#define ph2p_fefo_bin_step               PH2_VARS._ph2p_fefo_bin_step
#define ph2p_fefo_gain_adjust_shift      PH2_VARS._ph2p_fefo_gain_adjust_shift
#define ph2p_fefo_holdoff_time           PH2_VARS._ph2p_fefo_holdoff_time
#define ph2p_fefo_powr_SE_gain_adjust    PH2_VARS._ph2p_fefo_powr_SE_gain_adjust
#define ph2p_fefo_SB_gain_adjust         PH2_VARS._ph2p_fefo_SB_gain_adjust
#define ph2p_fefo_start_bin_phase_index  PH2_VARS._ph2p_fefo_start_bin_phase_index
#define ph2p_fefo_ws_k_buffer            PH2_VARS._ph2p_fefo_ws_k_buffer
#define ph2p_fefo_y_coord_scale_N        PH2_VARS._ph2p_fefo_y_coord_scale_N
#define ph2p_powr_dmod_rx_offset32       PH2_VARS._ph2p_powr_dmod_rx_offset32
#define PH2P_POWR_LX_FINAL_TUNE          PH2_VARS._PH2P_POWR_LX_FINAL_TUNE
#define PH2P_POWR_LX_PROCESS_LENGTH      PH2_VARS._PH2P_POWR_LX_PROCESS_LENGTH
#define ph2p_powr_rx_clear_length        PH2_VARS._ph2p_powr_rx_clear_length
#define ph2p_powr_saved_holdoff_I7_offset PH2_VARS._ph2p_powr_saved_holdoff_I7_offset
#define ph2p_powr_SB_power_adjust        PH2_VARS._ph2p_powr_SB_power_adjust
#define ph2s_INFO0_ack_counter           PH2_VARS._ph2s_INFO0_ack_counter
#define ph2s_orig_INFO1_counter          PH2_VARS._ph2s_orig_INFO1_counter
#define ph2_AB_zero_count                PH2_VARS._ph2_AB_zero_count
#define ph2_ac_sample_offset             PH2_VARS._ph2_ac_sample_offset
#define ph2_guard_counter                PH2_VARS._ph2_guard_counter
#define ph2_guard_tone_enable            PH2_VARS._ph2_guard_tone_enable
#define ph2_guard_tone_increment         PH2_VARS._ph2_guard_tone_increment
#define ph2_guard_tone_phase             PH2_VARS._ph2_guard_tone_phase
#define ph2_INFO_detect_state            PH2_VARS._ph2_INFO_detect_state
#define ph2_rxtx_rate_conv_modulo_counter PH2_VARS._ph2_rxtx_rate_conv_modulo_counter
#define ph2_rx_baud_counter              PH2_VARS._ph2_rx_baud_counter
#define ph2_rx_checker_bpf_offset        PH2_VARS._ph2_rx_checker_bpf_offset
#define ph2_rx_checker_count             PH2_VARS._ph2_rx_checker_count
#define ph2_rx_dcd_level                 PH2_VARS._ph2_rx_dcd_level
#define ph2_rx_passband_offset           PH2_VARS._ph2_rx_passband_offset
#define ph2_rx_rate_conv_9K6_8K0_pointer PH2_VARS._ph2_rx_rate_conv_9K6_8K0_pointer
#define ph2_rx_special_bpf_offset        PH2_VARS._ph2_rx_special_bpf_offset
#define ph2_tx_baud_counter              PH2_VARS._ph2_tx_baud_counter
#define ph2_tx_interpolator_offset       PH2_VARS._ph2_tx_interpolator_offset
#define ph2_tx_Lx_offset                 PH2_VARS._ph2_tx_Lx_offset
#define ph2_tx_passband_offset           PH2_VARS._ph2_tx_passband_offset
#define ph2_tx_rate_conv_9K6_8K0_pointer PH2_VARS._ph2_tx_rate_conv_9K6_8K0_pointer
#define v34p_bg_block_count              PH2_VARS._v34p_bg_block_count
#define v34p_bg_sample_count             PH2_VARS._v34p_bg_sample_count
#define v34_frame_rx_save_bit_count      PH2_VARS._v34_frame_rx_save_bit_count
#define saved_Lx_SE_power_adjust_pointer PH2_VARS._saved_Lx_SE_power_adjust_pointer
#define v34_frame_rx_save_bit_parse_pointer_bits PH2_VARS._v34_frame_rx_save_bit_parse_pointer_bits
#define ph2p_anal_flatvar                PH2_VARS._ph2p_anal_flatvar
#define ph2_guard_tone_amplitude         PH2_VARS._ph2_guard_tone_amplitude
#define ph2_guard_tone_gain              PH2_VARS._ph2_guard_tone_gain
#define ph2_scale_value                  PH2_VARS._ph2_scale_value
#define ph2_tx_Lx_gain                   PH2_VARS._ph2_tx_Lx_gain
#define ph2n_probing_train_16pt          PH2_VARS._ph2n_probing_train_16pt
#define ph2n_rx_acknowledge              PH2_VARS._ph2n_rx_acknowledge
#define ph2n_rx_carrier                  PH2_VARS._ph2n_rx_carrier
#define ph2n_rx_optional_attenuation     PH2_VARS._ph2n_rx_optional_attenuation
#define ph2n_rx_preemph                  PH2_VARS._ph2n_rx_preemph
#define ph2n_rx_required_attenuation     PH2_VARS._ph2n_rx_required_attenuation
#define ph2n_tx_acknowledge              PH2_VARS._ph2n_tx_acknowledge
#define ph2n_tx_carrier                  PH2_VARS._ph2n_tx_carrier
#define ph2n_tx_frequency_offset         PH2_VARS._ph2n_tx_frequency_offset
#define ph2n_tx_maxrate                  PH2_VARS._ph2n_tx_maxrate
#define ph2n_tx_optional_attenuation     PH2_VARS._ph2n_tx_optional_attenuation
#define ph2n_tx_preemph                  PH2_VARS._ph2n_tx_preemph
#define ph2n_tx_required_attenuation     PH2_VARS._ph2n_tx_required_attenuation
#define ph2p_anal_maxrate                PH2_VARS._ph2p_anal_maxrate
#define ph2p_anal_maxrates_00_table      PH2_VARS._ph2p_anal_maxrates_00_table
#define ph2p_anal_maxrates_01_table      PH2_VARS._ph2p_anal_maxrates_01_table
#define ph2p_anal_maxrates_02_table      PH2_VARS._ph2p_anal_maxrates_02_table
#define ph2p_anal_maxrates_03_table      PH2_VARS._ph2p_anal_maxrates_03_table
#define ph2p_anal_maxrates_04_table      PH2_VARS._ph2p_anal_maxrates_04_table
#define ph2p_anal_maxrates_05_table      PH2_VARS._ph2p_anal_maxrates_05_table
#define ph2p_anal_maxrates_10_table      PH2_VARS._ph2p_anal_maxrates_10_table
#define ph2p_anal_maxrates_11_table      PH2_VARS._ph2p_anal_maxrates_11_table
#define ph2p_anal_maxrates_12_table      PH2_VARS._ph2p_anal_maxrates_12_table
#define ph2p_anal_maxrates_13_table      PH2_VARS._ph2p_anal_maxrates_13_table
#define ph2p_anal_maxrates_14_table      PH2_VARS._ph2p_anal_maxrates_14_table
#define ph2p_anal_maxrates_15_table      PH2_VARS._ph2p_anal_maxrates_15_table
#define ph2p_anal_maxrate_results        PH2_VARS._ph2p_anal_maxrate_results
#define ph2p_anal_preemph_results_buffer PH2_VARS._ph2p_anal_preemph_results_buffer
#define ph2p_fefo_holdoff_flag           PH2_VARS._ph2p_fefo_holdoff_flag
#define ph2p_powr_L1_delay_delay_start   PH2_VARS._ph2p_powr_L1_delay_delay_start
#define ph2p_powr_L1_to_L2_delay_offset  PH2_VARS._ph2p_powr_L1_to_L2_delay_offset
#define ph2_AB_edge_correl_last          PH2_VARS._ph2_AB_edge_correl_last
#define ph2_AB_qualify_length            PH2_VARS._ph2_AB_qualify_length
#define ph2_ac_sample_bit_pattern        PH2_VARS._ph2_ac_sample_bit_pattern
#define ph2_data_timeout_enable          PH2_VARS._ph2_data_timeout_enable
#define ph2_data_timeout_start           PH2_VARS._ph2_data_timeout_start
#define ph2_INFOMARKS_one_count          PH2_VARS._ph2_INFOMARKS_one_count
#define ph2_INFOMARKS_qualify_length     PH2_VARS._ph2_INFOMARKS_qualify_length
#define ph2_INFO_correl_last             PH2_VARS._ph2_INFO_correl_last
#define ph2_rx_baud_current              PH2_VARS._ph2_rx_baud_current
#define ph2_rx_checker_length            PH2_VARS._ph2_rx_checker_length
#define ph2_rx_data_size                 PH2_VARS._ph2_rx_data_size
#define ph2_rx_data_size_1               PH2_VARS._ph2_rx_data_size_1
#define ph2_rx_dcd_integration_time      PH2_VARS._ph2_rx_dcd_integration_time
#define ph2_rx_signal_detect             PH2_VARS._ph2_rx_signal_detect
#define ph2_tx_baud_current              PH2_VARS._ph2_tx_baud_current
#define ph2_tx_data_size                 PH2_VARS._ph2_tx_data_size
#define ph2_tx_data_size_1               PH2_VARS._ph2_tx_data_size_1
#define v34p_bg_block_finished_flags     PH2_VARS._v34p_bg_block_finished_flags
#define ph2p_anal_maxrates_CS_pointer    PH2_VARS._ph2p_anal_maxrates_CS_pointer
#define ph2p_anal_maxrates_CS_table      PH2_VARS._ph2p_anal_maxrates_CS_table
#define ph2p_anal_maxrate_results_pointer PH2_VARS._ph2p_anal_maxrate_results_pointer
#define ph2p_anal_preemph_results_pointer PH2_VARS._ph2p_anal_preemph_results_pointer
#define v34_frame_rx_save_bit_parse_pointer PH2_VARS._v34_frame_rx_save_bit_parse_pointer
#define v34n_rx_INFO0_body               PH2_VARS._v34n_rx_INFO0_body
#define v34n_rx_INFO1a_body              PH2_VARS._v34n_rx_INFO1a_body
#define v34n_rx_INFO1c_body              PH2_VARS._v34n_rx_INFO1c_body
#define v34n_tx_INFO0_body               PH2_VARS._v34n_tx_INFO0_body
#define v34n_tx_INFO1a_body              PH2_VARS._v34n_tx_INFO1a_body
#define v34n_tx_INFO1c_body              PH2_VARS._v34n_tx_INFO1c_body
#define ph2n_rx_maxrate                  PH2_VARS._ph2n_rx_maxrate
#define ph2_ac_output40                  PH2_VARS._ph2_ac_output40
#define ph2p_powr_variable_buffer40      PH2_VARS._ph2p_powr_variable_buffer40
#define ph2p_powr_spectrum_power_buffer40 PH2_VARS._ph2p_powr_spectrum_power_buffer40
#define ph2p_powr_reconstruction_buffer40 PH2_VARS._ph2p_powr_reconstruction_buffer40
#define ph2p_fefo_spectrum_buffer40      PH2_VARS._ph2p_fefo_spectrum_buffer40

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

typedef struct {
	persist_d  uint16                      _ph2n_tx_2743_option;
	persist_d  uint16                      _ph2n_tx_2800_option;
	persist_d  uint16                      _ph2n_tx_3429_option;
	persist_d  uint16                      _ph2n_tx_lo_3000_option;
	persist_d  uint16                      _ph2n_tx_hi_3000_option;
	persist_d  uint16                      _ph2n_tx_lo_3200_option;
	persist_d  uint16                      _ph2n_tx_hi_3200_option;
	persist_d  uint16                      _ph2n_tx_tx_3429_option;
	persist_d  uint16                      _v34n_tx_attenuation_option;
	persist_d  uint16                      _v34n_tx_difference_option;
	persist_d  uint16                      _v34n_tx_CME_option;
	persist_d  uint16                      _v34n_tx_hi_data_rate_option;
	persist_d  uint16                      _v34n_tx_symbol_option;
	persist_d  uint16                      _v34n_tx_lo_carrier_option;
	persist_d  uint16                      _v34n_tx_hi_carrier_option;
	persist_d  uint16                      _ph2n_rx_2743_option;
	persist_d  uint16                      _ph2n_rx_2800_option;
	persist_d  uint16                      _ph2n_rx_3429_option;
	persist_d  uint16                      _ph2n_rx_lo_3000_option;
	persist_d  uint16                      _ph2n_rx_hi_3000_option;
	persist_d  uint16                      _ph2n_rx_lo_3200_option;
	persist_d  uint16                      _ph2n_rx_hi_3200_option;
	persist_d  uint16                      _ph2n_rx_tx_3429_option;
	persist_d  uint16                      _ph2n_rx_receive_attenuation;
	persist_d  uint16                      _ph2n_rx_receive_difference;
	persist_d  uint16                      _ph2n_rx_receive_CME;
	persist_d  uint16                      _ph2n_rx_receive_hi_data_rate;
	persist_d  uint16                      _ph2n_rx_receive_clock;
	persist_d  uint16                      _v34n_rx_symbol_option;
	persist_d  uint16                      _v34n_rx_lo_carrier_option;
	persist_d  uint16                      _v34n_rx_hi_carrier_option;
	persist_d  uint16                      _v34n_rx_attenuation_option;
	persist_d  uint16                      _v34n_rx_difference_option;
	persist_d  uint16                      _v34n_rx_CME_option;
	persist_d  uint16                      _v34n_rx_hi_data_rate_option;
	persist_d  uint16                      _v34n_rxtx_difference_option;
	persist_d  sint15                      _ph2n_probing_frequency_offset;
	persist_d  uint16                      _ph2n_probing_use_shaping;
	persist_d  fract                       _ph2n_probing_L2_log_P_buffer [PH2P_NO_TONES];
	persist_d  fract                       _ph2n_probing_L2_log_N_buffer [PH2P_NO_TONES];
	persist_d  sint15                      _ph2n_probing_L2_SE_power_adjust;
} ph2_persist_t;

/* ************************************************************************* */

DEF_DATA(ph2_persist_t, ph2_persist)
#define PH2_PERSIST_DATA ph2_persist_t ph2_persist
#define PH2_PERSIST USE_DATA(ph2_persist)
#define ph2_persist_used

/* ************************************************************************* */

#define ph2n_tx_2743_option              PH2_PERSIST._ph2n_tx_2743_option
#define ph2n_tx_2800_option              PH2_PERSIST._ph2n_tx_2800_option
#define ph2n_tx_3429_option              PH2_PERSIST._ph2n_tx_3429_option
#define ph2n_tx_lo_3000_option           PH2_PERSIST._ph2n_tx_lo_3000_option
#define ph2n_tx_hi_3000_option           PH2_PERSIST._ph2n_tx_hi_3000_option
#define ph2n_tx_lo_3200_option           PH2_PERSIST._ph2n_tx_lo_3200_option
#define ph2n_tx_hi_3200_option           PH2_PERSIST._ph2n_tx_hi_3200_option
#define ph2n_tx_tx_3429_option           PH2_PERSIST._ph2n_tx_tx_3429_option
#define v34n_tx_attenuation_option       PH2_PERSIST._v34n_tx_attenuation_option
#define v34n_tx_difference_option        PH2_PERSIST._v34n_tx_difference_option
#define v34n_tx_CME_option               PH2_PERSIST._v34n_tx_CME_option
#define v34n_tx_hi_data_rate_option      PH2_PERSIST._v34n_tx_hi_data_rate_option
#define v34n_tx_symbol_option            PH2_PERSIST._v34n_tx_symbol_option
#define v34n_tx_lo_carrier_option        PH2_PERSIST._v34n_tx_lo_carrier_option
#define v34n_tx_hi_carrier_option        PH2_PERSIST._v34n_tx_hi_carrier_option
#define ph2n_rx_2743_option              PH2_PERSIST._ph2n_rx_2743_option
#define ph2n_rx_2800_option              PH2_PERSIST._ph2n_rx_2800_option
#define ph2n_rx_3429_option              PH2_PERSIST._ph2n_rx_3429_option
#define ph2n_rx_lo_3000_option           PH2_PERSIST._ph2n_rx_lo_3000_option
#define ph2n_rx_hi_3000_option           PH2_PERSIST._ph2n_rx_hi_3000_option
#define ph2n_rx_lo_3200_option           PH2_PERSIST._ph2n_rx_lo_3200_option
#define ph2n_rx_hi_3200_option           PH2_PERSIST._ph2n_rx_hi_3200_option
#define ph2n_rx_tx_3429_option           PH2_PERSIST._ph2n_rx_tx_3429_option
#define ph2n_rx_receive_attenuation      PH2_PERSIST._ph2n_rx_receive_attenuation
#define ph2n_rx_receive_difference       PH2_PERSIST._ph2n_rx_receive_difference
#define ph2n_rx_receive_CME              PH2_PERSIST._ph2n_rx_receive_CME
#define ph2n_rx_receive_hi_data_rate     PH2_PERSIST._ph2n_rx_receive_hi_data_rate
#define ph2n_rx_receive_clock            PH2_PERSIST._ph2n_rx_receive_clock
#define v34n_rx_symbol_option            PH2_PERSIST._v34n_rx_symbol_option
#define v34n_rx_lo_carrier_option        PH2_PERSIST._v34n_rx_lo_carrier_option
#define v34n_rx_hi_carrier_option        PH2_PERSIST._v34n_rx_hi_carrier_option
#define v34n_rx_attenuation_option       PH2_PERSIST._v34n_rx_attenuation_option
#define v34n_rx_difference_option        PH2_PERSIST._v34n_rx_difference_option
#define v34n_rx_CME_option               PH2_PERSIST._v34n_rx_CME_option
#define v34n_rx_hi_data_rate_option      PH2_PERSIST._v34n_rx_hi_data_rate_option
#define v34n_rxtx_difference_option      PH2_PERSIST._v34n_rxtx_difference_option
#define ph2n_probing_frequency_offset    PH2_PERSIST._ph2n_probing_frequency_offset
#define ph2n_probing_use_shaping         PH2_PERSIST._ph2n_probing_use_shaping
#define ph2n_probing_L2_log_P_buffer     PH2_PERSIST._ph2n_probing_L2_log_P_buffer
#define ph2n_probing_L2_log_N_buffer     PH2_PERSIST._ph2n_probing_L2_log_N_buffer
#define ph2n_probing_L2_SE_power_adjust  PH2_PERSIST._ph2n_probing_L2_SE_power_adjust

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

typedef struct {
	stat_d     uint16                      _stat__rx_v34_symbol_rate;
	stat_d     uint16                      _stat__tx_v34_symbol_rate;
} ph2_stats_t;

/* ************************************************************************* */

DEF_DATA(ph2_stats_t, ph2_stats)
#define PH2_STATS_DATA ph2_stats_t ph2_stats
#define PH2_STATS USE_DATA(ph2_stats)
#define ph2_stats_used

/* ************************************************************************* */

#define stat__rx_v34_symbol_rate         PH2_STATS._stat__rx_v34_symbol_rate
#define stat__tx_v34_symbol_rate         PH2_STATS._stat__tx_v34_symbol_rate

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

typedef struct {
	debug_d    fract                       _ph2_power_trace_previous_Y;
	debug_d    fract                       _ph2_power_trace_Yoffset;
	debug_d    fract                       _ph2_tx_eye_imag_previous;
	debug_d    fract                       _ph2_tx_eye_real_previous;
	debug_d    sint15                      _ph2p_powr_power_block_count;
	debug_d    uint16                      _overlay_ph2_overrides_probing_results;
	debug_d    uint16                      _overlay_ph2_to_ph2;
	debug_d    uint16                      _overlay_ph2_to_v34;
	debug_d    uint16                      _overlay_ph2_uses_ph1_results;
	debug_d    uint16                      _ph2n_parm_optional_tx_attenuation_enable;
	debug_d    uint16                      _PH2S_LEN_T_TURNAROUND_DELAY;
	debug_d    uint16                      _ph2_power_trace_bin_count;
	debug_d    uint16                      _ph2_power_trace_which_count;
	debug_d    uint16                      _ph2_rx_baud_shift_register;
	debug_d    uint16                      _ph2_rx_btrec_clock_state;
	debug_d    uint16                      _ph2_tx_baud_shift_register;
	debug_d    uint16                      _v34b_bg_ph2_state;
} ph2_debug_t;

/* ************************************************************************* */

DEF_DATA(ph2_debug_t, ph2_debug)
#define PH2_DEBUG_DATA ph2_debug_t ph2_debug
#define PH2_DEBUG USE_DATA(ph2_debug)
#define ph2_debug_used

/* ************************************************************************* */

#define ph2_power_trace_previous_Y       PH2_DEBUG._ph2_power_trace_previous_Y
#define ph2_power_trace_Yoffset          PH2_DEBUG._ph2_power_trace_Yoffset
#define ph2_tx_eye_imag_previous         PH2_DEBUG._ph2_tx_eye_imag_previous
#define ph2_tx_eye_real_previous         PH2_DEBUG._ph2_tx_eye_real_previous
#define ph2p_powr_power_block_count      PH2_DEBUG._ph2p_powr_power_block_count
#define overlay_ph2_overrides_probing_results PH2_DEBUG._overlay_ph2_overrides_probing_results
#define overlay_ph2_to_ph2               PH2_DEBUG._overlay_ph2_to_ph2
#define overlay_ph2_to_v34               PH2_DEBUG._overlay_ph2_to_v34
#define overlay_ph2_uses_ph1_results     PH2_DEBUG._overlay_ph2_uses_ph1_results
#define ph2n_parm_optional_tx_attenuation_enable PH2_DEBUG._ph2n_parm_optional_tx_attenuation_enable
#define PH2S_LEN_T_TURNAROUND_DELAY      PH2_DEBUG._PH2S_LEN_T_TURNAROUND_DELAY
#define ph2_power_trace_bin_count        PH2_DEBUG._ph2_power_trace_bin_count
#define ph2_power_trace_which_count      PH2_DEBUG._ph2_power_trace_which_count
#define ph2_rx_baud_shift_register       PH2_DEBUG._ph2_rx_baud_shift_register
#define ph2_rx_btrec_clock_state         PH2_DEBUG._ph2_rx_btrec_clock_state
#define ph2_tx_baud_shift_register       PH2_DEBUG._ph2_tx_baud_shift_register
#define v34b_bg_ph2_state                PH2_DEBUG._v34b_bg_ph2_state

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

typedef struct {
	local_d    fract                       _ph2p_bg_sample_buffer [PH2P_BG_SAMPLE_SIZE];
} ph2_local_t;

/* ************************************************************************* */

DEF_DATA(ph2_local_t, ph2_local)
#define PH2_LOCAL_DATA ph2_local_t ph2_local
#define PH2_LOCAL USE_DATA(ph2_local)
#define ph2_local_used

/* ************************************************************************* */

#define ph2p_bg_sample_buffer            PH2_LOCAL._ph2p_bg_sample_buffer

/* ************************************************************************* */

#endif /* _DATA_PH2_H */
