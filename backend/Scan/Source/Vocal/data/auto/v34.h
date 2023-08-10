
/* ************************************************************************* */
/*
 *	v34.h
 *
 *	(C) 1994 - 2008 VOCAL Technologies, Ltd.
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
 *	This file contains automatically generated data for v34.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.2.4.2  2009/04/28 19:12:25  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _DATA_V34_H
#define _DATA_V34_H
#include "data/sections.h"

/* ************************************************************************* */

typedef struct {
	var_d      fract CIRCULAR              _rx_lpf_buffer [C7K2_FSK_RX_LPF_SIZE * 2];
	var_d      fract                       _convert_adjust_output_gain;
	var_d      fract                       _convert_adjust_output_log;
	var_d      fract                       _convert_agc_1_input_log;
	var_d      fract                       _convert_agc_1_output_log;
	var_d      fract                       _convert_agc_2_input_log;
	var_d      fract                       _convert_agc_2_output_log;
	var_d      fract                       _convert_energy_log;
	var_d      fract                       _convert_gain_input_log;
	var_d      fract                       _convert_target_log;
	var_d      fract                       _energy_echo_log;
	var_d      fract                       _energy_receive_log;
	var_d      fract                       _energy_total_log;
	var_d      fract40                     _energy_echo40;
	var_d      fract40                     _energy_input40;
	var_d      fract40                     _energy_receive40;
	var_d      fract40                     _energy_total40;
	var_d      sint15                      _convert_adjust_output_exponent;
	var_d      uint16 *                    _v34h_rx_buffer_load_pointer;
	var_d      uint16 *                    _v34h_rx_buffer_stream_pointer;
	var_d      uint16 *                    _v34h_rx_control_this_pointer;
	var_d      uint16 *                    _v34h_rx_m_ijk_ring_index_pointer;
	var_d      uint16 CIRCULAR             _temp_dm_buffer [32];
	var_d      sint15                      _v34_bulk_extra_buffer_real [BULK_EXTRA_BUFFER_SIZE];
	var_d      sint15                      _v34_bulk_extra_buffer_imag [BULK_EXTRA_BUFFER_SIZE];
	var_d      uint32                      _v34h_rx_g2_table [36];
	var_d      uint32                      _v34h_tx_g2_table [36];
	var_d      uint32                      _v34h_rx_g4_table [70];
	var_d      uint32                      _v34h_tx_g4_table [70];
	var_d      uint32                      _v34h_tx_g8_table [276];
	var_d      uint32                      _v34h_rx_g8_table [276];
	var_d      uint32                      _v34h_rx_z8_table [276];
	var_d      uint32                      _v34h_tx_z8_table [276];
	var_d      sint15                      _v34n_tx_qn_coef_real [V34_NO_QN_COEFS];
	var_d      sint15                      _v34n_tx_qn_coef_imag [V34_NO_QN_COEFS];
	var_d      fract                       _v34_slew_cos_BE;
	var_d      fract                       _v34_slew_sin_BE;
	var_d      fract                       _v34_slew_pos_BE;
	var_d      fract                       _v34_slew_neg_BE;
	var_d      fract                       _v34_slew_cos_BE2;
	var_d      fract                       _v34_slew_sin_BE2;
	var_d      fract                       _v34_slew_BE2;
	var_d      sint15                      _v34n_parm_sample_ec_update_increment;
	var_d      sint15                      _v34_tx_local_data_enable;
	var_d      ufract                      _v34_tx_local_gain_adjust;
	var_d      uint16                      _v34_tx_local_use_nonlinear;
	var_d      sint15                      _v34_tx_remote_data_enable;
	var_d      ufract                      _v34_tx_remote_gain_adjust;
	var_d      uint16                      _v34_tx_remote_use_nonlinear;
	var_d      uint16                      _v34s_special_local_train_offset;
	var_d      uint16                      _v34s_special_local_train_length;
	var_d      sint15                      _v34s_special_local_train_shift_slew;
	var_d      bool                        _v34s_special_local_train_enable;
	var_d      bool                        _v34s_special_local_train_option;
	var_d      bool                        _v34s_special_local_decor_option;
	var_d      bool                        _v34s_reneg_initiator;
	var_d      bool                        _v34_frame_rx_E_found;
	var_d      bool                        _v34_frame_rx_MP_found;
	var_d      bool                        _v34_rx_B1_enable_flag;
	var_d      fract*                      _v34_tx_decor_poffset;
	var_d      fract*                      _v34_tx_decor_coefs;
	var_d      fract                       _v34_tx_decor_output;
	var_d      fract                       _convert_log__gain;
	var_d      fract                       _demod_half_imag;
	var_d      fract                       _demod_half_real;
	var_d      fract                       _equalized_yn_imag;
	var_d      fract                       _equalized_yn_real;
	var_d      fract                       _equalizer_output_imag;
	var_d      fract                       _equalizer_output_real;
	var_d      fract                       _FALL_adjusted_mse_count;
	var_d      fract                       _FALL_adjusted_mse_delta;
	var_d      fract                       _FALL_adjusted_mse_value;
	var_d      fract                       _FALL_fallback_value;
	var_d      fract                       _FALL_fallforward_value;
	var_d      fract                       _FALL_mse_value;
	var_d      fract                       _local_ec_slewx;
	var_d      fract                       _max_energy;
	var_d      fract                       _min_energy;
	var_d      fract                       _phase_roll_hilbert_buffer [PHASE_ROLL_HILBERT_BUFFER_SIZE];
	var_d      fract                       _previous_sign;
	var_d      fract                       _retrain_imag;
	var_d      fract                       _retrain_real;
	var_d      fract                       _sdt_DC_angle_store_imag;
	var_d      fract                       _sdt_DC_angle_store_real;
	var_d      fract                       _v34n_rx_preeq_gain;
	var_d      fract                       _v34n_rx_preeq_Whi;
	var_d      fract                       _v34n_rx_preeq_Wlo;
	var_d      fract                       _v34n_rx_preeq_Wme;
	var_d      fract                       _v34n_rx_receive_agc2_level;
	var_d      fract                       _v34n_rx_receive_gain;
	var_d      fract                       _v34n_rx_mse_bias;
	var_d      fract                       _V34N_TRN2_DATA_MAXRATE_TABLE [V34N_MAX_MAXRATE];
	var_d      fract                       _v34s_prev_phase_roll_second;
	var_d      fract                       _v34s_prev_prev_phase_roll_second;
	var_d      fract                       _v34_BE_Gn;
	var_d      fract                       _v34_BE_Gp;
	var_d      fract                       _v34_BE_jam_baud_agc;
	var_d      fract                       _v34_BE_log_Gn;
	var_d      fract                       _v34_BE_log_Gn_prev;
	var_d      fract                       _v34_BE_log_Gp;
	var_d      fract                       _v34_BE_log_Gp_prev;
	var_d      fract                       _v34_BE_log_jam_baud_agc;
	var_d      fract                       _v34_BE_modify_Gn_gain;
	var_d      fract                       _v34_BE_modify_Gp_gain;
	var_d      fract                       _v34_BE_neg_log_magnitude;
	var_d      fract                       _v34_BE_pos_log_magnitude;
	var_d      fract                       _v34_CONV_agc_value;
	var_d      fract                       _v34_CONV_MSE_value;
	var_d      fract                       _v34_equalized_imag;
	var_d      fract                       _v34_equalized_real;
	var_d      fract                       _V34_INTERPOLATOR_COEFS [xC8K0_V34_XX_INTERPOLATOR_COEFS_SIZE];
	var_d      fract                       _v34_MSE_N_value;
	var_d      fract                       _v34_MSE_S_value;
	var_d      fract                       _v34_MSE_value;
	var_d      fract                       _v34_MSE_value_count;
	var_d      fract                       _v34_MSE_value_energy;
	var_d      fract                       _V34_PRE_HI_EQUALIZER_COEFS [5];
	var_d      fract                       _V34_PRE_LO_EQUALIZER_COEFS [5];
	var_d      fract                       _V34_PRE_ME_EQUALIZER_COEFS [5];
	var_d      fract                       _v34_renego_prev_imag;
	var_d      fract                       _v34_renego_prev_real;
	var_d      fract                       _v34_resync_data_buffer_imag [2*(V34_RESYNC_Nx2_plus_1)];
	var_d      fract                       _v34_resync_data_buffer_real [2*(V34_RESYNC_Nx2_plus_1)];
	var_d      fract                       _v34_resync_mean_buffer_imag [1*(V34_RESYNC_Nx2_plus_1)];
	var_d      fract                       _v34_resync_mean_buffer_real [1*(V34_RESYNC_Nx2_plus_1)];
	var_d      fract                       _v34_resync_perfect_imag;
	var_d      fract                       _v34_resync_perfect_real;
	var_d      fract                       _v34_resync_variance_buffer_imag [1*(V34_RESYNC_Nx2_plus_1)];
	var_d      fract                       _v34_resync_variance_buffer_real [1*(V34_RESYNC_Nx2_plus_1)];
	var_d      fract                       _V34_RX_LPF_COEFS [(xC8K0_V34_XX_HALF_RX_LPF_SIZE)*2];
	var_d      fract                       _v34_rx_zn_hat_imag;
	var_d      fract                       _v34_rx_zn_hat_real;
	var_d      fract                       _v34_rx_zn_tilde_imag;
	var_d      fract                       _v34_rx_zn_tilde_real;
	var_d      fract                       _V34_SLEW_COS_RETRAIN;
	var_d      fract                       _V34_SLEW_RETRAIN;
	var_d      fract                       _V34_SLEW_SIN_RETRAIN;
	var_d      fract                       _v34_temp_pre_emph_coefs_1 [33];
	var_d      fract                       _v34_temp_pre_emph_coefs_6 [33];
	var_d      fract                       _v34_TRN1_agc_value;
	var_d      fract                       _v34_TRN1_MSE_value;
	var_d      fract                       _v34_TRN2_agc_value;
	var_d      fract                       _v34_TRN2_MSE_rate_value;
	var_d      fract                       _v34_TRN2_MSE_value;
	var_d      fract                       _V34_TX_PRE_EMPH_COEFS [xC8K0_V34_XX_TX_BPF_SIZE];
	var_d      fract                       _v34_tx_zn_local_imag;
	var_d      fract                       _v34_tx_zn_local_real;
	var_d      fract                       _v34_tx_zn_remote_imag;
	var_d      fract                       _v34_tx_zn_remote_real;
	var_d      fract32                     _equalizer_coef_imag32 [xV34_XX_EQUALIZER_TAPS];
	var_d      fract32                     _equalizer_coef_real32 [xV34_XX_EQUALIZER_TAPS];
	var_d      fract32                     _phase_roll__second_order_term_32;
	var_d      fract32                     _phroll_remote_energy32;
	var_d      fract32                     _v34_BE_neg_power_32;
	var_d      fract32                     _v34_BE_pos_power_32;
	var_d      fract32                     _v34_resync_mcomp_buffer_imag32 [1*(V34_RESYNC_Nx2_plus_1)];
	var_d      fract32                     _v34_resync_mcomp_buffer_real32 [1*(V34_RESYNC_Nx2_plus_1)];
	var_d      fract32                     _v34_resync_vcomp_buffer_imag32 [1*(V34_RESYNC_Nx2_plus_1)];
	var_d      fract32                     _v34_resync_vcomp_buffer_real32 [1*(V34_RESYNC_Nx2_plus_1)];
	var_d      mse_struct                  _v34_MSE_stack;
	var_d      mse_struct                  _v34_MSE_S_stack;
	var_d      mse_struct                  _v34_TRN2_MSE_stack [V34_TRN2_MSE_STACK_SIZE];
	var_d      sint15                      _v34_rx_interpolator_size;
	var_d      sint15                      _v34_tx_interpolator_size;
	var_d      sint15                      _constellation_imag;
	var_d      sint15                      _constellation_real;
	var_d      sint15                      _convert_log__exponent;
	var_d      sint15                      _degree_limit;
	var_d      sint15                      _detect_count;
	var_d      sint15                      _detect_limit;
	var_d      sint15                      _floor_detect__shift;
	var_d      sint15                      _local_ec_shift_slew;
	var_d      sint15                      _lookback_update_base;
	var_d      sint15                      _ph4n_rx_trained_qn_coef_imag [V34_NO_QN_COEFS];
	var_d      sint15                      _ph4n_rx_trained_qn_coef_real [V34_NO_QN_COEFS];
	var_d      sint15                      _ph4n_tx_receive_qn_coef_imag [V34_NO_QN_COEFS];
	var_d      sint15                      _ph4n_tx_receive_qn_coef_real [V34_NO_QN_COEFS];
	var_d      phase_t                     _phase_adjust;
	var_d      sint15                      _remote_ec_shift_slew;
	var_d      sint15                      _retrain_count;
	var_d      sint15                      _retrain_limit;
	var_d      sint15                      _saved_rx_mapper_loop_counter;
	var_d      sint15                      _temporary_buffer [8];
	var_d      sint15                      _V34H_RX_BASE_GROUP_SIZE_1;
	var_d      sint15                      _v34h_rx_I1ij_m;
	var_d      sint15                      _v34h_rx_J_super_frame_size_x2;
	var_d      sint15                      _v34h_rx_Q_n;
	var_d      sint15                      _v34h_rx_V0_m;
	var_d      sint15                      _v34h_rx_V0_m_error_count;
	var_d      sint15                      _v34h_rx_w_1_quantize;
	var_d      sint15                      _v34h_rx_Z_m;
	var_d      sint15                      _v34h_rx_Z_m_previous;
	var_d      sint15                      _v34h_tx_control_hi_frame [16];
	var_d      sint15                      _v34h_tx_control_lo_frame [16];
	var_d      sint15                      _v34h_tx_I1ij_m;
	var_d      sint15                      _v34h_tx_J_super_frame_size_x2;
	var_d      sint15                      _v34h_tx_mapping_frame_count;
	var_d      sint15                      _v34h_tx_m_count_4D;
	var_d      sint15                      _v34h_tx_V0_m;
	var_d      sint15                      _v34h_tx_w_1_quantize;
	var_d      sint15                      _v34h_tx_Z_m;
	var_d      sint15                      _v34n_measured_roundtrip_delay;
	var_d      sint15                      _v34n_rx_preeq_exponent;
	var_d      sint15                      _v34s_gear_counter;
	var_d      sint15                      _v34s_log_energy_previous;
	var_d      sint15                      _v34s_number_final_MPA_to_send;
	var_d      sint15                      _v34s_post_MPA_bit_counter;
	var_d      sint15                      _v34s_run_holdoff_count;
	var_d      sint15                      _v34s_run_V0_m_error_count;
	var_d      sint15                      _v34s_run_v0_m_holdoff_count;
	var_d      sint15                      _v34_BE_modify_Gn_exp;
	var_d      sint15                      _v34_BE_modify_Gp_exp;
	var_d      sint15                      _v34_bulk_extra_input_offset;
	var_d      sint15                      _v34_bulk_extra_local_offset;
	var_d      sint15                      _v34_resync_baud_correction;
	var_d      sint15                      _v34_resync_count;
	var_d      sint15                      _v34_resync_data_offset;
	var_d      sint15                      _v34_resync_min_index;
	var_d      phase_t                     _v34_resync_phase_correction;
	var_d      sint15                      _V34_RXI_COUNT;
	var_d      phase_t                     _V34_RXI_PLL_COUNT;
	var_d      phase_t                     _V34_RXI_PLL_COUNT_x2;
	var_d      phase_t                     _V34_RXI_PLL_HALF_ADJUST;
	var_d      sint15                      _V34_RXI_TAPS;
	var_d      sint15                      _v34_rx_4D_indicator;
	var_d      sint15                      _v34_rx_cn_imag;
	var_d      sint15                      _v34_rx_cn_real;
	var_d      sint15                      _v34_rx_pn_hat_imag;
	var_d      sint15                      _v34_rx_pn_hat_real;
	var_d      sint15                      _v34_rx_pn_imag;
	var_d      sint15                      _v34_rx_pn_real;
	var_d      sint15                      _v34_rx_pn_tilde_imag;
	var_d      sint15                      _v34_rx_pn_tilde_real;
	var_d      sint15                      _v34_rx_predicted_V0_m_Jx2_counter;
	var_d      sint15                      _v34_rx_predicted_V0_m_Px2_counter;
	var_d      sint15                      _v34_rx_predicted_V0_m_value;
	var_d      sint15                      _v34_rx_qn_hat_pointer;
	var_d      sint15                      _v34_rx_qn_pointer;
	var_d      sint15                      _v34_rx_qn_tilde_pointer;
	var_d      sint15                      _v34_rx_trellis_lookback_array [V34_LOOKBACK_DEPTH * (16 * 5)];
	var_d      sint15                      _v34_rx_un_imag;
	var_d      sint15                      _v34_rx_un_real;
	var_d      sint15                      _v34_rx_W0_2m;
	var_d      sint15                      _v34_rx_xn_hat_imag;
	var_d      sint15                      _v34_rx_xn_hat_real;
	var_d      sint15                      _v34_rx_xn_imag;
	var_d      sint15                      _v34_rx_xn_real;
	var_d      sint15                      _v34_rx_xn_tilde_imag;
	var_d      sint15                      _v34_rx_xn_tilde_real;
	var_d      sint15                      _v34_rx_Y0_m;
	var_d      sint15                      _v34_rx_yn_hat_imag;
	var_d      sint15                      _v34_rx_yn_hat_real;
	var_d      sint15                      _v34_rx_yn_imag;
	var_d      sint15                      _v34_rx_yn_real;
	var_d      sint15                      _v34_rx_yn_tilde_imag;
	var_d      sint15                      _v34_rx_yn_tilde_real;
	var_d      sint15                      _v34_scheduled_retrain_in_seconds;
	var_d      phase_t                     _v34_temp_hi_carrier;
	var_d      phase_t                     _v34_temp_lo_carrier;
	var_d      sint15                      _V34_TXI_COUNT;
	var_d      phase_t                     _V34_TXI_PLL_COUNT;
	var_d      sint15                      _V34_TXI_TAPS;
	var_d      sint15                      _v34_tx_4D_indicator;
	var_d      sint15                      _v34_tx_cn_imag;
	var_d      sint15                      _v34_tx_cn_real;
	var_d      sint15                      _v34_tx_local_pattern_offset;
	var_d      sint15                      _v34_tx_pn_imag;
	var_d      sint15                      _v34_tx_pn_real;
	var_d      sint15                      _v34_tx_pn_remote_imag;
	var_d      sint15                      _v34_tx_pn_remote_real;
	var_d      sint15                      _v34_tx_qn_pointer;
	var_d      sint15                      _v34_tx_qn_remote_offset;
	var_d      sint15                      _v34_tx_remote_pattern_offset;
	var_d      sint15                      _v34_tx_s_n;
	var_d      sint15                      _v34_tx_un_imag;
	var_d      sint15                      _v34_tx_un_real;
	var_d      sint15                      _v34_tx_W0_2m;
	var_d      sint15                      _v34_tx_xn_imag;
	var_d      sint15                      _v34_tx_xn_local_imag;
	var_d      sint15                      _v34_tx_xn_local_real;
	var_d      sint15                      _v34_tx_xn_real;
	var_d      sint15                      _v34_tx_xn_remote_imag;
	var_d      sint15                      _v34_tx_xn_remote_real;
	var_d      sint15                      _v34_tx_Y0_m;
	var_d      sint15                      _v34_tx_yn_imag;
	var_d      sint15                      _v34_tx_yn_real;
	var_d      sint15                      _v34_tx_yn_remote_imag;
	var_d      sint15                      _v34_tx_yn_remote_real;
	var_d      sint15                      _v34_yn_equalized_imag;
	var_d      sint15                      _v34_yn_equalized_real;
	var_d      sint15                      _v34_yn_error_imag;
	var_d      sint15                      _v34_yn_error_real;
	var_d      sint15                      _v34_yn_perfect_imag;
	var_d      sint15                      _v34_yn_perfect_real;
	var_d      sint15 CIRCULAR             _v34_rx_qn_buffer_imag [2*V34_NO_QN_COEFS];
	var_d      sint15 CIRCULAR             _v34_rx_qn_buffer_real [2*V34_NO_QN_COEFS];
	var_d      sint15 CIRCULAR             _v34_rx_qn_hat_buffer_imag [2*V34_NO_QN_COEFS];
	var_d      sint15 CIRCULAR             _v34_rx_qn_hat_buffer_real [2*V34_NO_QN_COEFS];
	var_d      sint15 CIRCULAR             _v34_rx_qn_tilde_buffer_imag [2*V34_NO_QN_COEFS];
	var_d      sint15 CIRCULAR             _v34_rx_qn_tilde_buffer_real [2*V34_NO_QN_COEFS];
	var_d      sint15 CIRCULAR             _v34_tx_qn_buffer_imag [2*V34_NO_QN_COEFS];
	var_d      sint15 CIRCULAR             _v34_tx_qn_buffer_real [2*V34_NO_QN_COEFS];
	var_d      sint15 CIRCULAR             _v34_tx_qn_remote_buffer_imag [2*V34_NO_QN_COEFS];
	var_d      sint15 CIRCULAR             _v34_tx_qn_remote_buffer_real [2*V34_NO_QN_COEFS];
	var_d      sint15*                     _plookback;
	var_d      sint15*                     _v34h_tx_control_pointer;
	var_d      thread_routine_t            _v34_forced_train_routine;
	var_d      thread_routine_t            _v34_resync_train_routine;
	var_d      ufract                      _v34n_rx_gain_adjust;
	var_d      ufract                      _V34N_RX_GAIN_ADJUST_TABLE [V34N_MAX_MAXRATE*2*2];
	var_d      ufract                      _v34n_rx_inverse_gain_adjust;
	var_d      ufract                      _v34n_rx_receive_level;
	var_d      ufract                      _v34n_tx_gain_adjust;
	var_d      ufract                      _V34N_TX_GAIN_ADJUST_TABLE [V34N_MAX_MAXRATE*2*2];
	var_d      ufract                      _v34_resync_min_value;
	var_d      ufract                      _v34_resync_nxt_value;
	var_d      ufract                      _v34_resync_total_buffer [1*(V34_RESYNC_Nx2_plus_1)];
	var_d      ufract                      _V34_RXI_ADJUST;
	var_d      ufract                      _v34_temp_pre_emph_adjust_table [11];
	var_d      ufract                      _V34_TXI_ADJUST;
	var_d      ufract                      _v34_tx_preemph_gain_adjust;
	var_d      ufract                      _V34_T_OVER_8K0_RATIO;
	var_d      uint16                      _FALL_catastrophic_flag;
	var_d      uint16                      _FALL_fallback_flag;
	var_d      uint16                      _FALL_fallforward_flag;
	var_d      uint16                      _FALL_fallforward_possible_flag;
	var_d      uint16                      _ph4n_rx_acknowledge;
	var_d      uint16                      _ph4n_rx_answer_to_call_maxrate;
	var_d      uint16                      _ph4n_rx_auxiliary_option;
	var_d      uint16                      _ph4n_rx_call_to_answer_maxrate;
	var_d      uint16                      _ph4n_rx_MP_type;
	var_d      uint16                      _ph4n_rx_trained_maxrate;
	var_d      uint16                      _ph4n_rx_trained_nonlinear;
	var_d      uint16                      _ph4n_rx_trained_shaping;
	var_d      uint16                      _ph4n_rx_train_precoding;
	var_d      uint16                      _ph4n_tx_acknowledge;
	var_d      uint16                      _ph4n_tx_answer_to_call_maxrate;
	var_d      uint16                      _ph4n_tx_auxiliary_option;
	var_d      uint16                      _ph4n_tx_call_to_answer_maxrate;
	var_d      uint16                      _ph4n_tx_ITU_bit_reserved;
	var_d      uint16                      _ph4n_tx_ITU_reserved;
	var_d      uint16                      _ph4n_tx_MP_type;
	var_d      uint16                      _ph4n_tx_receive_nonlinear;
	var_d      uint16                      _ph4n_tx_receive_shaping;
	var_d      uint16                      _rx_call_to_answer_new_maxrate;
	var_d      uint16                      _save_rx_answer_to_call_maxrate;
	var_d      uint16                      _save_rx_call_to_answer_maxrate;
	var_d      uint16                      _scramb_lsb;
	var_d      uint16                      _scramb_msb;
	var_d      uint16                      _v34h_aux_tx_flag;
	var_d      uint16                      _v34h_baud_tx_flag_previous;
	var_d      uint16                      _v34h_rx_AMP_value;
	var_d      uint16                      _v34h_rx_aux_adjust_flag;
	var_d      uint16                      _v34h_rx_aux_restore_flag;
	var_d      uint16                      _v34h_rx_buffer1 [8];
	var_d      uint16                      _v34h_rx_buffer2 [8];
	var_d      uint16                      _v34h_rx_b_bits_per_mapping_frame;
	var_d      uint16                      _v34h_rx_control_hi_frame [8];
	var_d      uint16                      _v34h_rx_control_lo_frame [8];
	var_d      uint16                      _v34h_rx_half_data_frame_counter;
	var_d      uint16                      _v34h_rx_K_number_shell_bits;
	var_d      uint16                      _v34h_rx_L_over_4_1_size;
	var_d      uint16                      _v34h_rx_m_count_4D;
	var_d      uint16                      _v34h_rx_m_ijk_ring_index_buffer [8];
	var_d      uint16                      _v34h_rx_M_number_rings;
	var_d      uint16                      _v34h_rx_P_data_frame_size;
	var_d      uint16                      _v34h_rx_Qn_1st_2D;
	var_d      uint16                      _v34h_rx_q_bits_per_2D_subgroup;
	var_d      uint16                      _v34h_rx_residue;
	var_d      uint16                      _v34h_rx_residue_length;
	var_d      uint16                      _v34h_rx_r_bits;
	var_d      uint16                      _v34h_rx_state;
	var_d      uint16                      _v34h_rx_SWP_value;
	var_d      uint16                      _v34h_rx_V0_m_register;
	var_d      uint16                      _v34h_rx_write_enable;
	var_d      uint16                      _v34h_tx_AMP_value;
	var_d      uint16                      _v34h_tx_buffer [16];
	var_d      uint16                      _v34h_tx_b_bits_per_mapping_frame;
	var_d      uint16                      _v34h_tx_half_data_frame_counter;
	var_d      uint16                      _v34h_tx_K_number_shell_bits;
	var_d      uint16                      _v34h_tx_L_over_4_1_size;
	var_d      uint16                      _v34h_tx_m_ijk_ring_index_buffer [8];
	var_d      uint16                      _v34h_tx_M_number_rings;
	var_d      uint16                      _v34h_tx_N_bits_per_data_frame;
	var_d      uint16                      _v34h_tx_process_enable;
	var_d      uint16                      _v34h_tx_P_data_frame_size;
	var_d      uint16                      _v34h_tx_q_bits_per_2D_subgroup;
	var_d      uint16                      _v34h_tx_Q_n;
	var_d      uint16                      _v34h_tx_residue_hi;
	var_d      uint16                      _v34h_tx_residue_length;
	var_d      uint16                      _v34h_tx_residue_lo;
	var_d      uint16                      _v34h_tx_r_bits;
	var_d      uint16                      _v34h_tx_state;
	var_d      uint16                      _v34h_tx_SWP_value;
	var_d      uint16                      _v34s_capture_buffer [5*3];
	var_d      uint16                      _v34s_gear_change_period;
	var_d      uint16                      _v34s_last_frame_was_an_MPA;
	var_d      uint16                      _v34s_retrain_from_data_flag;
	var_d      uint16                      _v34s_rev_count;
	var_d      uint16                      _v34_frame_rx_E_found_previous;
	var_d      uint16                      _v34_frame_rx_MP_found_previous;
	var_d      uint16                      _v34_frame_rx_sync_register;
	var_d      uint16                      _v34_frame_tx_bits_per_baud;
	var_d      uint16                      _v34_initialize_data_illegal_setting;
	var_d      uint16                      _v34_local_fetching_flag;
	var_d      uint16                      _V34_MD_LENGTH_INCREMENT;
	var_d      uint16                      _v34_pp_ftr_offset;
	var_d      uint16                      _v34_resync_state;
	var_d      phase_t                     _V34_RX_CARRIER_FREQUENCY;
	var_d      uint16                      _v34_rx_valid_qn_coefs_flag;
	var_d      uint16                      _v34_symbol_diff_decode_data;
	var_d      uint16                      _v34_symbol_diff_encode_data;
	var_d      phase_t                     _V34_TX_CARRIER_FREQUENCY;
	var_d      uint16*                     _pnew_scores;
	var_d      uint16*                     _pold_scores;
	var_d      uint16*                     _v34h_rx_control_next_pointer;
	var_d      uint16*                     _v34h_rx_e0_last_pointer;
	var_d      uint16*                     _v34h_tx_buffer_current;
	var_d      uint16*                     _v34h_tx_last_e0_pointer;
	var_d      uint16*                     _v34h_tx_m_ijk_ring_index_pointer;
	var_d      uint16*                     _v34h_tx_pointer;
	var_d      uint16*                     _v34n_rx_MP0_body [18];
	var_d      uint16*                     _v34n_rx_MP1_body [30];
	var_d      uint16*                     _v34n_tx_MP0_body [18];
	var_d      uint16*                     _v34n_tx_MP1_body [30];
} v34_vars_t;

/* ************************************************************************* */

DEF_DATA(v34_vars_t, v34_vars)
#define V34_VARS_DATA v34_vars_t v34_vars
#define V34_VARS USE_DATA(v34_vars)
#define v34_vars_used

/* ************************************************************************* */

#define rx_lpf_buffer                    V34_VARS._rx_lpf_buffer
#define convert_adjust_output_gain       V34_VARS._convert_adjust_output_gain
#define convert_adjust_output_log        V34_VARS._convert_adjust_output_log
#define convert_agc_1_input_log          V34_VARS._convert_agc_1_input_log
#define convert_agc_1_output_log         V34_VARS._convert_agc_1_output_log
#define convert_agc_2_input_log          V34_VARS._convert_agc_2_input_log
#define convert_agc_2_output_log         V34_VARS._convert_agc_2_output_log
#define convert_energy_log               V34_VARS._convert_energy_log
#define convert_gain_input_log           V34_VARS._convert_gain_input_log
#define convert_target_log               V34_VARS._convert_target_log
#define energy_echo_log                  V34_VARS._energy_echo_log
#define energy_receive_log               V34_VARS._energy_receive_log
#define energy_total_log                 V34_VARS._energy_total_log
#define energy_echo40                    V34_VARS._energy_echo40
#define energy_input40                   V34_VARS._energy_input40
#define energy_receive40                 V34_VARS._energy_receive40
#define energy_total40                   V34_VARS._energy_total40
#define convert_adjust_output_exponent   V34_VARS._convert_adjust_output_exponent
#define v34h_rx_buffer_load_pointer      V34_VARS._v34h_rx_buffer_load_pointer
#define v34h_rx_buffer_stream_pointer    V34_VARS._v34h_rx_buffer_stream_pointer
#define v34h_rx_control_this_pointer     V34_VARS._v34h_rx_control_this_pointer
#define v34h_rx_m_ijk_ring_index_pointer V34_VARS._v34h_rx_m_ijk_ring_index_pointer
#define temp_dm_buffer                   V34_VARS._temp_dm_buffer
#define v34_bulk_extra_buffer_real       V34_VARS._v34_bulk_extra_buffer_real
#define v34_bulk_extra_buffer_imag       V34_VARS._v34_bulk_extra_buffer_imag
#define v34h_rx_g2_table                 V34_VARS._v34h_rx_g2_table
#define v34h_tx_g2_table                 V34_VARS._v34h_tx_g2_table
#define v34h_rx_g4_table                 V34_VARS._v34h_rx_g4_table
#define v34h_tx_g4_table                 V34_VARS._v34h_tx_g4_table
#define v34h_tx_g8_table                 V34_VARS._v34h_tx_g8_table
#define v34h_rx_g8_table                 V34_VARS._v34h_rx_g8_table
#define v34h_rx_z8_table                 V34_VARS._v34h_rx_z8_table
#define v34h_tx_z8_table                 V34_VARS._v34h_tx_z8_table
#define v34n_tx_qn_coef_real             V34_VARS._v34n_tx_qn_coef_real
#define v34n_tx_qn_coef_imag             V34_VARS._v34n_tx_qn_coef_imag
#define v34_slew_cos_BE                  V34_VARS._v34_slew_cos_BE
#define v34_slew_sin_BE                  V34_VARS._v34_slew_sin_BE
#define v34_slew_pos_BE                  V34_VARS._v34_slew_pos_BE
#define v34_slew_neg_BE                  V34_VARS._v34_slew_neg_BE
#define v34_slew_cos_BE2                 V34_VARS._v34_slew_cos_BE2
#define v34_slew_sin_BE2                 V34_VARS._v34_slew_sin_BE2
#define v34_slew_BE2                     V34_VARS._v34_slew_BE2
#define v34n_parm_sample_ec_update_increment V34_VARS._v34n_parm_sample_ec_update_increment
#define v34_tx_local_data_enable         V34_VARS._v34_tx_local_data_enable
#define v34_tx_local_gain_adjust         V34_VARS._v34_tx_local_gain_adjust
#define v34_tx_local_use_nonlinear       V34_VARS._v34_tx_local_use_nonlinear
#define v34_tx_remote_data_enable        V34_VARS._v34_tx_remote_data_enable
#define v34_tx_remote_gain_adjust        V34_VARS._v34_tx_remote_gain_adjust
#define v34_tx_remote_use_nonlinear      V34_VARS._v34_tx_remote_use_nonlinear
#define v34s_special_local_train_offset  V34_VARS._v34s_special_local_train_offset
#define v34s_special_local_train_length  V34_VARS._v34s_special_local_train_length
#define v34s_special_local_train_shift_slew V34_VARS._v34s_special_local_train_shift_slew
#define v34s_special_local_train_enable  V34_VARS._v34s_special_local_train_enable
#define v34s_special_local_train_option  V34_VARS._v34s_special_local_train_option
#define v34s_special_local_decor_option  V34_VARS._v34s_special_local_decor_option
#define v34s_reneg_initiator             V34_VARS._v34s_reneg_initiator
#define v34_frame_rx_E_found             V34_VARS._v34_frame_rx_E_found
#define v34_frame_rx_MP_found            V34_VARS._v34_frame_rx_MP_found
#define v34_rx_B1_enable_flag            V34_VARS._v34_rx_B1_enable_flag
#define v34_tx_decor_poffset             V34_VARS._v34_tx_decor_poffset
#define v34_tx_decor_coefs               V34_VARS._v34_tx_decor_coefs
#define v34_tx_decor_output              V34_VARS._v34_tx_decor_output
#define convert_log__gain                V34_VARS._convert_log__gain
#define demod_half_imag                  V34_VARS._demod_half_imag
#define demod_half_real                  V34_VARS._demod_half_real
#define equalized_yn_imag                V34_VARS._equalized_yn_imag
#define equalized_yn_real                V34_VARS._equalized_yn_real
#define equalizer_output_imag            V34_VARS._equalizer_output_imag
#define equalizer_output_real            V34_VARS._equalizer_output_real
#define FALL_adjusted_mse_count          V34_VARS._FALL_adjusted_mse_count
#define FALL_adjusted_mse_delta          V34_VARS._FALL_adjusted_mse_delta
#define FALL_adjusted_mse_value          V34_VARS._FALL_adjusted_mse_value
#define FALL_fallback_value              V34_VARS._FALL_fallback_value
#define FALL_fallforward_value           V34_VARS._FALL_fallforward_value
#define FALL_mse_value                   V34_VARS._FALL_mse_value
#define local_ec_slewx                   V34_VARS._local_ec_slewx
#define max_energy                       V34_VARS._max_energy
#define min_energy                       V34_VARS._min_energy
#define phase_roll_hilbert_buffer        V34_VARS._phase_roll_hilbert_buffer
#define previous_sign                    V34_VARS._previous_sign
#define retrain_imag                     V34_VARS._retrain_imag
#define retrain_real                     V34_VARS._retrain_real
#define sdt_DC_angle_store_imag          V34_VARS._sdt_DC_angle_store_imag
#define sdt_DC_angle_store_real          V34_VARS._sdt_DC_angle_store_real
#define v34n_rx_preeq_gain               V34_VARS._v34n_rx_preeq_gain
#define v34n_rx_preeq_Whi                V34_VARS._v34n_rx_preeq_Whi
#define v34n_rx_preeq_Wlo                V34_VARS._v34n_rx_preeq_Wlo
#define v34n_rx_preeq_Wme                V34_VARS._v34n_rx_preeq_Wme
#define v34n_rx_receive_agc2_level       V34_VARS._v34n_rx_receive_agc2_level
#define v34n_rx_receive_gain             V34_VARS._v34n_rx_receive_gain
#define v34n_rx_mse_bias                 V34_VARS._v34n_rx_mse_bias
#define V34N_TRN2_DATA_MAXRATE_TABLE     V34_VARS._V34N_TRN2_DATA_MAXRATE_TABLE
#define v34s_prev_phase_roll_second      V34_VARS._v34s_prev_phase_roll_second
#define v34s_prev_prev_phase_roll_second V34_VARS._v34s_prev_prev_phase_roll_second
#define v34_BE_Gn                        V34_VARS._v34_BE_Gn
#define v34_BE_Gp                        V34_VARS._v34_BE_Gp
#define v34_BE_jam_baud_agc              V34_VARS._v34_BE_jam_baud_agc
#define v34_BE_log_Gn                    V34_VARS._v34_BE_log_Gn
#define v34_BE_log_Gn_prev               V34_VARS._v34_BE_log_Gn_prev
#define v34_BE_log_Gp                    V34_VARS._v34_BE_log_Gp
#define v34_BE_log_Gp_prev               V34_VARS._v34_BE_log_Gp_prev
#define v34_BE_log_jam_baud_agc          V34_VARS._v34_BE_log_jam_baud_agc
#define v34_BE_modify_Gn_gain            V34_VARS._v34_BE_modify_Gn_gain
#define v34_BE_modify_Gp_gain            V34_VARS._v34_BE_modify_Gp_gain
#define v34_BE_neg_log_magnitude         V34_VARS._v34_BE_neg_log_magnitude
#define v34_BE_pos_log_magnitude         V34_VARS._v34_BE_pos_log_magnitude
#define v34_CONV_agc_value               V34_VARS._v34_CONV_agc_value
#define v34_CONV_MSE_value               V34_VARS._v34_CONV_MSE_value
#define v34_equalized_imag               V34_VARS._v34_equalized_imag
#define v34_equalized_real               V34_VARS._v34_equalized_real
#define V34_INTERPOLATOR_COEFS           V34_VARS._V34_INTERPOLATOR_COEFS
#define v34_MSE_N_value                  V34_VARS._v34_MSE_N_value
#define v34_MSE_S_value                  V34_VARS._v34_MSE_S_value
#define v34_MSE_value                    V34_VARS._v34_MSE_value
#define v34_MSE_value_count              V34_VARS._v34_MSE_value_count
#define v34_MSE_value_energy             V34_VARS._v34_MSE_value_energy
#define V34_PRE_HI_EQUALIZER_COEFS       V34_VARS._V34_PRE_HI_EQUALIZER_COEFS
#define V34_PRE_LO_EQUALIZER_COEFS       V34_VARS._V34_PRE_LO_EQUALIZER_COEFS
#define V34_PRE_ME_EQUALIZER_COEFS       V34_VARS._V34_PRE_ME_EQUALIZER_COEFS
#define v34_renego_prev_imag             V34_VARS._v34_renego_prev_imag
#define v34_renego_prev_real             V34_VARS._v34_renego_prev_real
#define v34_resync_data_buffer_imag      V34_VARS._v34_resync_data_buffer_imag
#define v34_resync_data_buffer_real      V34_VARS._v34_resync_data_buffer_real
#define v34_resync_mean_buffer_imag      V34_VARS._v34_resync_mean_buffer_imag
#define v34_resync_mean_buffer_real      V34_VARS._v34_resync_mean_buffer_real
#define v34_resync_perfect_imag          V34_VARS._v34_resync_perfect_imag
#define v34_resync_perfect_real          V34_VARS._v34_resync_perfect_real
#define v34_resync_variance_buffer_imag  V34_VARS._v34_resync_variance_buffer_imag
#define v34_resync_variance_buffer_real  V34_VARS._v34_resync_variance_buffer_real
#define V34_RX_LPF_COEFS                 V34_VARS._V34_RX_LPF_COEFS
#define v34_rx_zn_hat_imag               V34_VARS._v34_rx_zn_hat_imag
#define v34_rx_zn_hat_real               V34_VARS._v34_rx_zn_hat_real
#define v34_rx_zn_tilde_imag             V34_VARS._v34_rx_zn_tilde_imag
#define v34_rx_zn_tilde_real             V34_VARS._v34_rx_zn_tilde_real
#define V34_SLEW_COS_RETRAIN             V34_VARS._V34_SLEW_COS_RETRAIN
#define V34_SLEW_RETRAIN                 V34_VARS._V34_SLEW_RETRAIN
#define V34_SLEW_SIN_RETRAIN             V34_VARS._V34_SLEW_SIN_RETRAIN
#define v34_temp_pre_emph_coefs_1        V34_VARS._v34_temp_pre_emph_coefs_1
#define v34_temp_pre_emph_coefs_6        V34_VARS._v34_temp_pre_emph_coefs_6
#define v34_TRN1_agc_value               V34_VARS._v34_TRN1_agc_value
#define v34_TRN1_MSE_value               V34_VARS._v34_TRN1_MSE_value
#define v34_TRN2_agc_value               V34_VARS._v34_TRN2_agc_value
#define v34_TRN2_MSE_rate_value          V34_VARS._v34_TRN2_MSE_rate_value
#define v34_TRN2_MSE_value               V34_VARS._v34_TRN2_MSE_value
#define V34_TX_PRE_EMPH_COEFS            V34_VARS._V34_TX_PRE_EMPH_COEFS
#define v34_tx_zn_local_imag             V34_VARS._v34_tx_zn_local_imag
#define v34_tx_zn_local_real             V34_VARS._v34_tx_zn_local_real
#define v34_tx_zn_remote_imag            V34_VARS._v34_tx_zn_remote_imag
#define v34_tx_zn_remote_real            V34_VARS._v34_tx_zn_remote_real
#define equalizer_coef_imag32            V34_VARS._equalizer_coef_imag32
#define equalizer_coef_real32            V34_VARS._equalizer_coef_real32
#define phase_roll__second_order_term_32 V34_VARS._phase_roll__second_order_term_32
#define phroll_remote_energy32           V34_VARS._phroll_remote_energy32
#define v34_BE_neg_power_32              V34_VARS._v34_BE_neg_power_32
#define v34_BE_pos_power_32              V34_VARS._v34_BE_pos_power_32
#define v34_resync_mcomp_buffer_imag32   V34_VARS._v34_resync_mcomp_buffer_imag32
#define v34_resync_mcomp_buffer_real32   V34_VARS._v34_resync_mcomp_buffer_real32
#define v34_resync_vcomp_buffer_imag32   V34_VARS._v34_resync_vcomp_buffer_imag32
#define v34_resync_vcomp_buffer_real32   V34_VARS._v34_resync_vcomp_buffer_real32
#define v34_MSE_stack                    V34_VARS._v34_MSE_stack
#define v34_MSE_S_stack                  V34_VARS._v34_MSE_S_stack
#define v34_TRN2_MSE_stack               V34_VARS._v34_TRN2_MSE_stack
#define v34_rx_interpolator_size         V34_VARS._v34_rx_interpolator_size
#define v34_tx_interpolator_size         V34_VARS._v34_tx_interpolator_size
#define constellation_imag               V34_VARS._constellation_imag
#define constellation_real               V34_VARS._constellation_real
#define convert_log__exponent            V34_VARS._convert_log__exponent
#define degree_limit                     V34_VARS._degree_limit
#define detect_count                     V34_VARS._detect_count
#define detect_limit                     V34_VARS._detect_limit
#define floor_detect__shift              V34_VARS._floor_detect__shift
#define local_ec_shift_slew              V34_VARS._local_ec_shift_slew
#define lookback_update_base             V34_VARS._lookback_update_base
#define ph4n_rx_trained_qn_coef_imag     V34_VARS._ph4n_rx_trained_qn_coef_imag
#define ph4n_rx_trained_qn_coef_real     V34_VARS._ph4n_rx_trained_qn_coef_real
#define ph4n_tx_receive_qn_coef_imag     V34_VARS._ph4n_tx_receive_qn_coef_imag
#define ph4n_tx_receive_qn_coef_real     V34_VARS._ph4n_tx_receive_qn_coef_real
#define phase_adjust                     V34_VARS._phase_adjust
#define remote_ec_shift_slew             V34_VARS._remote_ec_shift_slew
#define retrain_count                    V34_VARS._retrain_count
#define retrain_limit                    V34_VARS._retrain_limit
#define saved_rx_mapper_loop_counter     V34_VARS._saved_rx_mapper_loop_counter
#define temporary_buffer                 V34_VARS._temporary_buffer
#define V34H_RX_BASE_GROUP_SIZE_1        V34_VARS._V34H_RX_BASE_GROUP_SIZE_1
#define v34h_rx_I1ij_m                   V34_VARS._v34h_rx_I1ij_m
#define v34h_rx_J_super_frame_size_x2    V34_VARS._v34h_rx_J_super_frame_size_x2
#define v34h_rx_Q_n                      V34_VARS._v34h_rx_Q_n
#define v34h_rx_V0_m                     V34_VARS._v34h_rx_V0_m
#define v34h_rx_V0_m_error_count         V34_VARS._v34h_rx_V0_m_error_count
#define v34h_rx_w_1_quantize             V34_VARS._v34h_rx_w_1_quantize
#define v34h_rx_Z_m                      V34_VARS._v34h_rx_Z_m
#define v34h_rx_Z_m_previous             V34_VARS._v34h_rx_Z_m_previous
#define v34h_tx_control_hi_frame         V34_VARS._v34h_tx_control_hi_frame
#define v34h_tx_control_lo_frame         V34_VARS._v34h_tx_control_lo_frame
#define v34h_tx_I1ij_m                   V34_VARS._v34h_tx_I1ij_m
#define v34h_tx_J_super_frame_size_x2    V34_VARS._v34h_tx_J_super_frame_size_x2
#define v34h_tx_mapping_frame_count      V34_VARS._v34h_tx_mapping_frame_count
#define v34h_tx_m_count_4D               V34_VARS._v34h_tx_m_count_4D
#define v34h_tx_V0_m                     V34_VARS._v34h_tx_V0_m
#define v34h_tx_w_1_quantize             V34_VARS._v34h_tx_w_1_quantize
#define v34h_tx_Z_m                      V34_VARS._v34h_tx_Z_m
#define v34n_measured_roundtrip_delay    V34_VARS._v34n_measured_roundtrip_delay
#define v34n_rx_preeq_exponent           V34_VARS._v34n_rx_preeq_exponent
#define v34s_gear_counter                V34_VARS._v34s_gear_counter
#define v34s_log_energy_previous         V34_VARS._v34s_log_energy_previous
#define v34s_number_final_MPA_to_send    V34_VARS._v34s_number_final_MPA_to_send
#define v34s_post_MPA_bit_counter        V34_VARS._v34s_post_MPA_bit_counter
#define v34s_run_holdoff_count           V34_VARS._v34s_run_holdoff_count
#define v34s_run_V0_m_error_count        V34_VARS._v34s_run_V0_m_error_count
#define v34s_run_v0_m_holdoff_count      V34_VARS._v34s_run_v0_m_holdoff_count
#define v34_BE_modify_Gn_exp             V34_VARS._v34_BE_modify_Gn_exp
#define v34_BE_modify_Gp_exp             V34_VARS._v34_BE_modify_Gp_exp
#define v34_bulk_extra_input_offset      V34_VARS._v34_bulk_extra_input_offset
#define v34_bulk_extra_local_offset      V34_VARS._v34_bulk_extra_local_offset
#define v34_resync_baud_correction       V34_VARS._v34_resync_baud_correction
#define v34_resync_count                 V34_VARS._v34_resync_count
#define v34_resync_data_offset           V34_VARS._v34_resync_data_offset
#define v34_resync_min_index             V34_VARS._v34_resync_min_index
#define v34_resync_phase_correction      V34_VARS._v34_resync_phase_correction
#define V34_RXI_COUNT                    V34_VARS._V34_RXI_COUNT
#define V34_RXI_PLL_COUNT                V34_VARS._V34_RXI_PLL_COUNT
#define V34_RXI_PLL_COUNT_x2             V34_VARS._V34_RXI_PLL_COUNT_x2
#define V34_RXI_PLL_HALF_ADJUST          V34_VARS._V34_RXI_PLL_HALF_ADJUST
#define V34_RXI_TAPS                     V34_VARS._V34_RXI_TAPS
#define v34_rx_4D_indicator              V34_VARS._v34_rx_4D_indicator
#define v34_rx_cn_imag                   V34_VARS._v34_rx_cn_imag
#define v34_rx_cn_real                   V34_VARS._v34_rx_cn_real
#define v34_rx_pn_hat_imag               V34_VARS._v34_rx_pn_hat_imag
#define v34_rx_pn_hat_real               V34_VARS._v34_rx_pn_hat_real
#define v34_rx_pn_imag                   V34_VARS._v34_rx_pn_imag
#define v34_rx_pn_real                   V34_VARS._v34_rx_pn_real
#define v34_rx_pn_tilde_imag             V34_VARS._v34_rx_pn_tilde_imag
#define v34_rx_pn_tilde_real             V34_VARS._v34_rx_pn_tilde_real
#define v34_rx_predicted_V0_m_Jx2_counter V34_VARS._v34_rx_predicted_V0_m_Jx2_counter
#define v34_rx_predicted_V0_m_Px2_counter V34_VARS._v34_rx_predicted_V0_m_Px2_counter
#define v34_rx_predicted_V0_m_value      V34_VARS._v34_rx_predicted_V0_m_value
#define v34_rx_qn_hat_pointer            V34_VARS._v34_rx_qn_hat_pointer
#define v34_rx_qn_pointer                V34_VARS._v34_rx_qn_pointer
#define v34_rx_qn_tilde_pointer          V34_VARS._v34_rx_qn_tilde_pointer
#define v34_rx_trellis_lookback_array    V34_VARS._v34_rx_trellis_lookback_array
#define v34_rx_un_imag                   V34_VARS._v34_rx_un_imag
#define v34_rx_un_real                   V34_VARS._v34_rx_un_real
#define v34_rx_W0_2m                     V34_VARS._v34_rx_W0_2m
#define v34_rx_xn_hat_imag               V34_VARS._v34_rx_xn_hat_imag
#define v34_rx_xn_hat_real               V34_VARS._v34_rx_xn_hat_real
#define v34_rx_xn_imag                   V34_VARS._v34_rx_xn_imag
#define v34_rx_xn_real                   V34_VARS._v34_rx_xn_real
#define v34_rx_xn_tilde_imag             V34_VARS._v34_rx_xn_tilde_imag
#define v34_rx_xn_tilde_real             V34_VARS._v34_rx_xn_tilde_real
#define v34_rx_Y0_m                      V34_VARS._v34_rx_Y0_m
#define v34_rx_yn_hat_imag               V34_VARS._v34_rx_yn_hat_imag
#define v34_rx_yn_hat_real               V34_VARS._v34_rx_yn_hat_real
#define v34_rx_yn_imag                   V34_VARS._v34_rx_yn_imag
#define v34_rx_yn_real                   V34_VARS._v34_rx_yn_real
#define v34_rx_yn_tilde_imag             V34_VARS._v34_rx_yn_tilde_imag
#define v34_rx_yn_tilde_real             V34_VARS._v34_rx_yn_tilde_real
#define v34_scheduled_retrain_in_seconds V34_VARS._v34_scheduled_retrain_in_seconds
#define v34_temp_hi_carrier              V34_VARS._v34_temp_hi_carrier
#define v34_temp_lo_carrier              V34_VARS._v34_temp_lo_carrier
#define V34_TXI_COUNT                    V34_VARS._V34_TXI_COUNT
#define V34_TXI_PLL_COUNT                V34_VARS._V34_TXI_PLL_COUNT
#define V34_TXI_TAPS                     V34_VARS._V34_TXI_TAPS
#define v34_tx_4D_indicator              V34_VARS._v34_tx_4D_indicator
#define v34_tx_cn_imag                   V34_VARS._v34_tx_cn_imag
#define v34_tx_cn_real                   V34_VARS._v34_tx_cn_real
#define v34_tx_local_pattern_offset      V34_VARS._v34_tx_local_pattern_offset
#define v34_tx_pn_imag                   V34_VARS._v34_tx_pn_imag
#define v34_tx_pn_real                   V34_VARS._v34_tx_pn_real
#define v34_tx_pn_remote_imag            V34_VARS._v34_tx_pn_remote_imag
#define v34_tx_pn_remote_real            V34_VARS._v34_tx_pn_remote_real
#define v34_tx_qn_pointer                V34_VARS._v34_tx_qn_pointer
#define v34_tx_qn_remote_offset          V34_VARS._v34_tx_qn_remote_offset
#define v34_tx_remote_pattern_offset     V34_VARS._v34_tx_remote_pattern_offset
#define v34_tx_s_n                       V34_VARS._v34_tx_s_n
#define v34_tx_un_imag                   V34_VARS._v34_tx_un_imag
#define v34_tx_un_real                   V34_VARS._v34_tx_un_real
#define v34_tx_W0_2m                     V34_VARS._v34_tx_W0_2m
#define v34_tx_xn_imag                   V34_VARS._v34_tx_xn_imag
#define v34_tx_xn_local_imag             V34_VARS._v34_tx_xn_local_imag
#define v34_tx_xn_local_real             V34_VARS._v34_tx_xn_local_real
#define v34_tx_xn_real                   V34_VARS._v34_tx_xn_real
#define v34_tx_xn_remote_imag            V34_VARS._v34_tx_xn_remote_imag
#define v34_tx_xn_remote_real            V34_VARS._v34_tx_xn_remote_real
#define v34_tx_Y0_m                      V34_VARS._v34_tx_Y0_m
#define v34_tx_yn_imag                   V34_VARS._v34_tx_yn_imag
#define v34_tx_yn_real                   V34_VARS._v34_tx_yn_real
#define v34_tx_yn_remote_imag            V34_VARS._v34_tx_yn_remote_imag
#define v34_tx_yn_remote_real            V34_VARS._v34_tx_yn_remote_real
#define v34_yn_equalized_imag            V34_VARS._v34_yn_equalized_imag
#define v34_yn_equalized_real            V34_VARS._v34_yn_equalized_real
#define v34_yn_error_imag                V34_VARS._v34_yn_error_imag
#define v34_yn_error_real                V34_VARS._v34_yn_error_real
#define v34_yn_perfect_imag              V34_VARS._v34_yn_perfect_imag
#define v34_yn_perfect_real              V34_VARS._v34_yn_perfect_real
#define v34_rx_qn_buffer_imag            V34_VARS._v34_rx_qn_buffer_imag
#define v34_rx_qn_buffer_real            V34_VARS._v34_rx_qn_buffer_real
#define v34_rx_qn_hat_buffer_imag        V34_VARS._v34_rx_qn_hat_buffer_imag
#define v34_rx_qn_hat_buffer_real        V34_VARS._v34_rx_qn_hat_buffer_real
#define v34_rx_qn_tilde_buffer_imag      V34_VARS._v34_rx_qn_tilde_buffer_imag
#define v34_rx_qn_tilde_buffer_real      V34_VARS._v34_rx_qn_tilde_buffer_real
#define v34_tx_qn_buffer_imag            V34_VARS._v34_tx_qn_buffer_imag
#define v34_tx_qn_buffer_real            V34_VARS._v34_tx_qn_buffer_real
#define v34_tx_qn_remote_buffer_imag     V34_VARS._v34_tx_qn_remote_buffer_imag
#define v34_tx_qn_remote_buffer_real     V34_VARS._v34_tx_qn_remote_buffer_real
#define plookback                        V34_VARS._plookback
#define v34h_tx_control_pointer          V34_VARS._v34h_tx_control_pointer
#define v34_forced_train_routine         V34_VARS._v34_forced_train_routine
#define v34_resync_train_routine         V34_VARS._v34_resync_train_routine
#define v34n_rx_gain_adjust              V34_VARS._v34n_rx_gain_adjust
#define V34N_RX_GAIN_ADJUST_TABLE        V34_VARS._V34N_RX_GAIN_ADJUST_TABLE
#define v34n_rx_inverse_gain_adjust      V34_VARS._v34n_rx_inverse_gain_adjust
#define v34n_rx_receive_level            V34_VARS._v34n_rx_receive_level
#define v34n_tx_gain_adjust              V34_VARS._v34n_tx_gain_adjust
#define V34N_TX_GAIN_ADJUST_TABLE        V34_VARS._V34N_TX_GAIN_ADJUST_TABLE
#define v34_resync_min_value             V34_VARS._v34_resync_min_value
#define v34_resync_nxt_value             V34_VARS._v34_resync_nxt_value
#define v34_resync_total_buffer          V34_VARS._v34_resync_total_buffer
#define V34_RXI_ADJUST                   V34_VARS._V34_RXI_ADJUST
#define v34_temp_pre_emph_adjust_table   V34_VARS._v34_temp_pre_emph_adjust_table
#define V34_TXI_ADJUST                   V34_VARS._V34_TXI_ADJUST
#define v34_tx_preemph_gain_adjust       V34_VARS._v34_tx_preemph_gain_adjust
#define V34_T_OVER_8K0_RATIO             V34_VARS._V34_T_OVER_8K0_RATIO
#define FALL_catastrophic_flag           V34_VARS._FALL_catastrophic_flag
#define FALL_fallback_flag               V34_VARS._FALL_fallback_flag
#define FALL_fallforward_flag            V34_VARS._FALL_fallforward_flag
#define FALL_fallforward_possible_flag   V34_VARS._FALL_fallforward_possible_flag
#define ph4n_rx_acknowledge              V34_VARS._ph4n_rx_acknowledge
#define ph4n_rx_answer_to_call_maxrate   V34_VARS._ph4n_rx_answer_to_call_maxrate
#define ph4n_rx_auxiliary_option         V34_VARS._ph4n_rx_auxiliary_option
#define ph4n_rx_call_to_answer_maxrate   V34_VARS._ph4n_rx_call_to_answer_maxrate
#define ph4n_rx_MP_type                  V34_VARS._ph4n_rx_MP_type
#define ph4n_rx_trained_maxrate          V34_VARS._ph4n_rx_trained_maxrate
#define ph4n_rx_trained_nonlinear        V34_VARS._ph4n_rx_trained_nonlinear
#define ph4n_rx_trained_shaping          V34_VARS._ph4n_rx_trained_shaping
#define ph4n_rx_train_precoding          V34_VARS._ph4n_rx_train_precoding
#define ph4n_tx_acknowledge              V34_VARS._ph4n_tx_acknowledge
#define ph4n_tx_answer_to_call_maxrate   V34_VARS._ph4n_tx_answer_to_call_maxrate
#define ph4n_tx_auxiliary_option         V34_VARS._ph4n_tx_auxiliary_option
#define ph4n_tx_call_to_answer_maxrate   V34_VARS._ph4n_tx_call_to_answer_maxrate
#define ph4n_tx_ITU_bit_reserved         V34_VARS._ph4n_tx_ITU_bit_reserved
#define ph4n_tx_ITU_reserved             V34_VARS._ph4n_tx_ITU_reserved
#define ph4n_tx_MP_type                  V34_VARS._ph4n_tx_MP_type
#define ph4n_tx_receive_nonlinear        V34_VARS._ph4n_tx_receive_nonlinear
#define ph4n_tx_receive_shaping          V34_VARS._ph4n_tx_receive_shaping
#define rx_call_to_answer_new_maxrate    V34_VARS._rx_call_to_answer_new_maxrate
#define save_rx_answer_to_call_maxrate   V34_VARS._save_rx_answer_to_call_maxrate
#define save_rx_call_to_answer_maxrate   V34_VARS._save_rx_call_to_answer_maxrate
#define scramb_lsb                       V34_VARS._scramb_lsb
#define scramb_msb                       V34_VARS._scramb_msb
#define v34h_aux_tx_flag                 V34_VARS._v34h_aux_tx_flag
#define v34h_baud_tx_flag_previous       V34_VARS._v34h_baud_tx_flag_previous
#define v34h_rx_AMP_value                V34_VARS._v34h_rx_AMP_value
#define v34h_rx_aux_adjust_flag          V34_VARS._v34h_rx_aux_adjust_flag
#define v34h_rx_aux_restore_flag         V34_VARS._v34h_rx_aux_restore_flag
#define v34h_rx_buffer1                  V34_VARS._v34h_rx_buffer1
#define v34h_rx_buffer2                  V34_VARS._v34h_rx_buffer2
#define v34h_rx_b_bits_per_mapping_frame V34_VARS._v34h_rx_b_bits_per_mapping_frame
#define v34h_rx_control_hi_frame         V34_VARS._v34h_rx_control_hi_frame
#define v34h_rx_control_lo_frame         V34_VARS._v34h_rx_control_lo_frame
#define v34h_rx_half_data_frame_counter  V34_VARS._v34h_rx_half_data_frame_counter
#define v34h_rx_K_number_shell_bits      V34_VARS._v34h_rx_K_number_shell_bits
#define v34h_rx_L_over_4_1_size          V34_VARS._v34h_rx_L_over_4_1_size
#define v34h_rx_m_count_4D               V34_VARS._v34h_rx_m_count_4D
#define v34h_rx_m_ijk_ring_index_buffer  V34_VARS._v34h_rx_m_ijk_ring_index_buffer
#define v34h_rx_M_number_rings           V34_VARS._v34h_rx_M_number_rings
#define v34h_rx_P_data_frame_size        V34_VARS._v34h_rx_P_data_frame_size
#define v34h_rx_Qn_1st_2D                V34_VARS._v34h_rx_Qn_1st_2D
#define v34h_rx_q_bits_per_2D_subgroup   V34_VARS._v34h_rx_q_bits_per_2D_subgroup
#define v34h_rx_residue                  V34_VARS._v34h_rx_residue
#define v34h_rx_residue_length           V34_VARS._v34h_rx_residue_length
#define v34h_rx_r_bits                   V34_VARS._v34h_rx_r_bits
#define v34h_rx_state                    V34_VARS._v34h_rx_state
#define v34h_rx_SWP_value                V34_VARS._v34h_rx_SWP_value
#define v34h_rx_V0_m_register            V34_VARS._v34h_rx_V0_m_register
#define v34h_rx_write_enable             V34_VARS._v34h_rx_write_enable
#define v34h_tx_AMP_value                V34_VARS._v34h_tx_AMP_value
#define v34h_tx_buffer                   V34_VARS._v34h_tx_buffer
#define v34h_tx_b_bits_per_mapping_frame V34_VARS._v34h_tx_b_bits_per_mapping_frame
#define v34h_tx_half_data_frame_counter  V34_VARS._v34h_tx_half_data_frame_counter
#define v34h_tx_K_number_shell_bits      V34_VARS._v34h_tx_K_number_shell_bits
#define v34h_tx_L_over_4_1_size          V34_VARS._v34h_tx_L_over_4_1_size
#define v34h_tx_m_ijk_ring_index_buffer  V34_VARS._v34h_tx_m_ijk_ring_index_buffer
#define v34h_tx_M_number_rings           V34_VARS._v34h_tx_M_number_rings
#define v34h_tx_N_bits_per_data_frame    V34_VARS._v34h_tx_N_bits_per_data_frame
#define v34h_tx_process_enable           V34_VARS._v34h_tx_process_enable
#define v34h_tx_P_data_frame_size        V34_VARS._v34h_tx_P_data_frame_size
#define v34h_tx_q_bits_per_2D_subgroup   V34_VARS._v34h_tx_q_bits_per_2D_subgroup
#define v34h_tx_Q_n                      V34_VARS._v34h_tx_Q_n
#define v34h_tx_residue_hi               V34_VARS._v34h_tx_residue_hi
#define v34h_tx_residue_length           V34_VARS._v34h_tx_residue_length
#define v34h_tx_residue_lo               V34_VARS._v34h_tx_residue_lo
#define v34h_tx_r_bits                   V34_VARS._v34h_tx_r_bits
#define v34h_tx_state                    V34_VARS._v34h_tx_state
#define v34h_tx_SWP_value                V34_VARS._v34h_tx_SWP_value
#define v34s_capture_buffer              V34_VARS._v34s_capture_buffer
#define v34s_gear_change_period          V34_VARS._v34s_gear_change_period
#define v34s_last_frame_was_an_MPA       V34_VARS._v34s_last_frame_was_an_MPA
#define v34s_retrain_from_data_flag      V34_VARS._v34s_retrain_from_data_flag
#define v34s_rev_count                   V34_VARS._v34s_rev_count
#define v34_frame_rx_E_found_previous    V34_VARS._v34_frame_rx_E_found_previous
#define v34_frame_rx_MP_found_previous   V34_VARS._v34_frame_rx_MP_found_previous
#define v34_frame_rx_sync_register       V34_VARS._v34_frame_rx_sync_register
#define v34_frame_tx_bits_per_baud       V34_VARS._v34_frame_tx_bits_per_baud
#define v34_initialize_data_illegal_setting V34_VARS._v34_initialize_data_illegal_setting
#define v34_local_fetching_flag          V34_VARS._v34_local_fetching_flag
#define V34_MD_LENGTH_INCREMENT          V34_VARS._V34_MD_LENGTH_INCREMENT
#define v34_pp_ftr_offset                V34_VARS._v34_pp_ftr_offset
#define v34_resync_state                 V34_VARS._v34_resync_state
#define V34_RX_CARRIER_FREQUENCY         V34_VARS._V34_RX_CARRIER_FREQUENCY
#define v34_rx_valid_qn_coefs_flag       V34_VARS._v34_rx_valid_qn_coefs_flag
#define v34_symbol_diff_decode_data      V34_VARS._v34_symbol_diff_decode_data
#define v34_symbol_diff_encode_data      V34_VARS._v34_symbol_diff_encode_data
#define V34_TX_CARRIER_FREQUENCY         V34_VARS._V34_TX_CARRIER_FREQUENCY
#define pnew_scores                      V34_VARS._pnew_scores
#define pold_scores                      V34_VARS._pold_scores
#define v34h_rx_control_next_pointer     V34_VARS._v34h_rx_control_next_pointer
#define v34h_rx_e0_last_pointer          V34_VARS._v34h_rx_e0_last_pointer
#define v34h_tx_buffer_current           V34_VARS._v34h_tx_buffer_current
#define v34h_tx_last_e0_pointer          V34_VARS._v34h_tx_last_e0_pointer
#define v34h_tx_m_ijk_ring_index_pointer V34_VARS._v34h_tx_m_ijk_ring_index_pointer
#define v34h_tx_pointer                  V34_VARS._v34h_tx_pointer
#define v34n_rx_MP0_body                 V34_VARS._v34n_rx_MP0_body
#define v34n_rx_MP1_body                 V34_VARS._v34n_rx_MP1_body
#define v34n_tx_MP0_body                 V34_VARS._v34n_tx_MP0_body
#define v34n_tx_MP1_body                 V34_VARS._v34n_tx_MP1_body

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

typedef struct {
	stat_d     fract                       _stat__snr_mse_measure;
} v34_stats_t;

/* ************************************************************************* */

DEF_DATA(v34_stats_t, v34_stats)
#define V34_STATS_DATA v34_stats_t v34_stats
#define V34_STATS USE_DATA(v34_stats)
#define v34_stats_used

/* ************************************************************************* */

#define stat__snr_mse_measure            V34_STATS._stat__snr_mse_measure

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

typedef struct {
	debug_d    bool                        _v34n_parm_error_recovery_enable;
	debug_d    bool                        _v34n_parm_preemptive_phase_roll_slow;
	debug_d    bool                        _v34n_parm_remote_clear_disable;
	debug_d    bool                        _v34s_apply_agc_1;
	debug_d    bool                        _v34s_conditional_ecc;
	debug_d    bool                        _v34s_reneg_allow_recv_MP_within_ignore;
	debug_d    bool                        _v34s_reneg_allow_send_MP_within_ignore;
	debug_d    bool                        _v34s_reneg_ignore_send_MP_recv_MP;
	debug_d    bool                        _v34s_reneg_init_SN_to_S_to_retrain;
	debug_d    bool                        _v34s_reneg_init_S_to_SN_to_retrain;
	debug_d    bool                        _v34s_reneg_resp_S_to_SN_to_retrain;
	debug_d    bool                        _v34s_reneg_test_init_ignore_S;
	debug_d    bool                        _v34s_reneg_test_init_ignore_SN;
	debug_d    bool                        _v34s_reneg_test_init_variable_S_length;
	debug_d    bool                        _v34s_reneg_test_produce_noise;
	debug_d    bool                        _v34s_reneg_test_resp_ignore_S;
	debug_d    bool                        _v34s_reneg_test_resp_ignore_SN;
	debug_d    bool                        _v34s_reneg_test_resp_variable_S_length;
	debug_d    bool                        _v34s_retrigger_renegotiation;
	debug_d    bool                        _v34s_retrigger_retrain;
	debug_d    bool                        _v34s_special_startup;
	debug_d    fract                       _ec_very_slow_slew;
	debug_d    fract                       _threshold_s1;
	debug_d    fract                       _threshold_s2;
	debug_d    fract                       _V34_BE_INITIAL_Gn;
	debug_d    fract                       _V34_BE_INITIAL_Gp;
	debug_d    fract                       _v34_equalizer_slew_B1_medium;
	debug_d    fract                       _v34_equalizer_slew_B1_slow;
	debug_d    fract                       _v34_equalizer_slew_data_slow;
	debug_d    fract                       _v34_equalizer_slew_fast;
	debug_d    fract                       _v34_equalizer_slew_medium;
	debug_d    fract                       _v34_equalizer_slew_slow;
	debug_d    sint15                      _ec_fast_shift_slew_local;
	debug_d    sint15                      _ec_fast_shift_slew_remote;
	debug_d    sint15                      _ec_medium_shift_slew_local;
	debug_d    sint15                      _ec_medium_shift_slew_remote;
	debug_d    sint15                      _ec_slow_shift_slew_local;
	debug_d    sint15                      _ec_slow_shift_slew_remote;
	debug_d    sint15                      _ec_very_slow_shift_slew_local;
	debug_d    sint15                      _ec_very_slow_shift_slew_remote;
	debug_d    sint15                      _ec_xtrain_shift_slew_local;
	debug_d    sint15                      _ec_xtrain_shift_slew_remote;
	debug_d    sint15                      _ec_ytrain_shift_slew_local;
	debug_d    sint15                      _ec_ytrain_shift_slew_remote;
	debug_d    sint15                      _ec_ztrain_shift_slew_local;
	debug_d    sint15                      _ec_ztrain_shift_slew_remote;
	debug_d    sint15                      _V34S_AGC_1_SETTLE_TIME;
	debug_d    sint15                      _v34s_capture_counter;
	debug_d    sint15                      _V34S_LEN_8K0_1RT_MAX_1ST_TRAIN;
	debug_d    sint15                      _V34S_LEN_8K0_1RT_MIN_1ST_TRAIN;
	debug_d    sint15                      _V34S_LEN_8K0_MIN_LOCAL_TRAIN;
	debug_d    sint15                      _V34S_LEN_8K0_SPECIAL_LOCAL_TRAIN;
	debug_d    sint15                      _V34S_LEN_8K0_REMOTE_GUARD;
	debug_d    sint15                      _v34_equalizer_slew_data_offset;
	debug_d    sint15                      _v34_helper_state_index;
	debug_d    sint15                      _v34_TRN2_MSE_report_rate;
	debug_d    uint16                      _v34n_sm_INFO1c_end_delay;
	debug_d    ufract                      _v34s_reneg_test_noise_level;
	debug_d    uint16                      _V34S_ANSW_8K0_1RT_Jsrt_to_S_SNdet;
	debug_d    uint16                      _V34S_ANSW_8K0_1RT_S_SN_to_JEdet;
	debug_d    uint16                      _V34S_ANSW_8K0_2RT_Jend_to_Jdet;
	debug_d    uint16                      _V34S_ANSW_8K0_3RT_SNend_to_Edet;
	debug_d    uint16                      _v34s_conditional_frequency_offset;
	debug_d    uint16                      _V34S_INIT_8K0_2RT_S_SN_to_Edet;
	debug_d    uint16                      _V34S_LEN_8K0_PRE_GEAR_CHANGE;
	debug_d    uint16                      _V34S_ORIG_8K0_1RT_Jsrt_to_S_SNdet;
	debug_d    uint16                      _V34S_ORIG_8K0_2RT_INFO1cend_to_Jsrt;
	debug_d    uint16                      _V34S_ORIG_8K0_2RT_JEend_to_Edet;
	debug_d    uint16                      _v34s_reneg_special_flag;
	debug_d    uint16                      _V34S_RESP_8K0_3RT_S_SN_to_Edet;
	debug_d    uint16                      _v34s_short_renegotiations;
} v34_debug_t;

/* ************************************************************************* */

DEF_DATA(v34_debug_t, v34_debug)
#define V34_DEBUG_DATA v34_debug_t v34_debug
#define V34_DEBUG USE_DATA(v34_debug)
#define v34_debug_used

/* ************************************************************************* */

#define v34n_parm_error_recovery_enable  V34_DEBUG._v34n_parm_error_recovery_enable
#define v34n_parm_preemptive_phase_roll_slow V34_DEBUG._v34n_parm_preemptive_phase_roll_slow
#define v34n_parm_remote_clear_disable   V34_DEBUG._v34n_parm_remote_clear_disable
#define v34s_apply_agc_1                 V34_DEBUG._v34s_apply_agc_1
#define v34s_conditional_ecc             V34_DEBUG._v34s_conditional_ecc
#define v34s_reneg_allow_recv_MP_within_ignore V34_DEBUG._v34s_reneg_allow_recv_MP_within_ignore
#define v34s_reneg_allow_send_MP_within_ignore V34_DEBUG._v34s_reneg_allow_send_MP_within_ignore
#define v34s_reneg_ignore_send_MP_recv_MP V34_DEBUG._v34s_reneg_ignore_send_MP_recv_MP
#define v34s_reneg_init_SN_to_S_to_retrain V34_DEBUG._v34s_reneg_init_SN_to_S_to_retrain
#define v34s_reneg_init_S_to_SN_to_retrain V34_DEBUG._v34s_reneg_init_S_to_SN_to_retrain
#define v34s_reneg_resp_S_to_SN_to_retrain V34_DEBUG._v34s_reneg_resp_S_to_SN_to_retrain
#define v34s_reneg_test_init_ignore_S    V34_DEBUG._v34s_reneg_test_init_ignore_S
#define v34s_reneg_test_init_ignore_SN   V34_DEBUG._v34s_reneg_test_init_ignore_SN
#define v34s_reneg_test_init_variable_S_length V34_DEBUG._v34s_reneg_test_init_variable_S_length
#define v34s_reneg_test_produce_noise    V34_DEBUG._v34s_reneg_test_produce_noise
#define v34s_reneg_test_resp_ignore_S    V34_DEBUG._v34s_reneg_test_resp_ignore_S
#define v34s_reneg_test_resp_ignore_SN   V34_DEBUG._v34s_reneg_test_resp_ignore_SN
#define v34s_reneg_test_resp_variable_S_length V34_DEBUG._v34s_reneg_test_resp_variable_S_length
#define v34s_retrigger_renegotiation     V34_DEBUG._v34s_retrigger_renegotiation
#define v34s_retrigger_retrain           V34_DEBUG._v34s_retrigger_retrain
#define v34s_special_startup             V34_DEBUG._v34s_special_startup
#define ec_very_slow_slew                V34_DEBUG._ec_very_slow_slew
#define threshold_s1                     V34_DEBUG._threshold_s1
#define threshold_s2                     V34_DEBUG._threshold_s2
#define V34_BE_INITIAL_Gn                V34_DEBUG._V34_BE_INITIAL_Gn
#define V34_BE_INITIAL_Gp                V34_DEBUG._V34_BE_INITIAL_Gp
#define v34_equalizer_slew_B1_medium     V34_DEBUG._v34_equalizer_slew_B1_medium
#define v34_equalizer_slew_B1_slow       V34_DEBUG._v34_equalizer_slew_B1_slow
#define v34_equalizer_slew_data_slow     V34_DEBUG._v34_equalizer_slew_data_slow
#define v34_equalizer_slew_fast          V34_DEBUG._v34_equalizer_slew_fast
#define v34_equalizer_slew_medium        V34_DEBUG._v34_equalizer_slew_medium
#define v34_equalizer_slew_slow          V34_DEBUG._v34_equalizer_slew_slow
#define ec_fast_shift_slew_local         V34_DEBUG._ec_fast_shift_slew_local
#define ec_fast_shift_slew_remote        V34_DEBUG._ec_fast_shift_slew_remote
#define ec_medium_shift_slew_local       V34_DEBUG._ec_medium_shift_slew_local
#define ec_medium_shift_slew_remote      V34_DEBUG._ec_medium_shift_slew_remote
#define ec_slow_shift_slew_local         V34_DEBUG._ec_slow_shift_slew_local
#define ec_slow_shift_slew_remote        V34_DEBUG._ec_slow_shift_slew_remote
#define ec_very_slow_shift_slew_local    V34_DEBUG._ec_very_slow_shift_slew_local
#define ec_very_slow_shift_slew_remote   V34_DEBUG._ec_very_slow_shift_slew_remote
#define ec_xtrain_shift_slew_local       V34_DEBUG._ec_xtrain_shift_slew_local
#define ec_xtrain_shift_slew_remote      V34_DEBUG._ec_xtrain_shift_slew_remote
#define ec_ytrain_shift_slew_local       V34_DEBUG._ec_ytrain_shift_slew_local
#define ec_ytrain_shift_slew_remote      V34_DEBUG._ec_ytrain_shift_slew_remote
#define ec_ztrain_shift_slew_local       V34_DEBUG._ec_ztrain_shift_slew_local
#define ec_ztrain_shift_slew_remote      V34_DEBUG._ec_ztrain_shift_slew_remote
#define V34S_AGC_1_SETTLE_TIME           V34_DEBUG._V34S_AGC_1_SETTLE_TIME
#define v34s_capture_counter             V34_DEBUG._v34s_capture_counter
#define V34S_LEN_8K0_1RT_MAX_1ST_TRAIN   V34_DEBUG._V34S_LEN_8K0_1RT_MAX_1ST_TRAIN
#define V34S_LEN_8K0_1RT_MIN_1ST_TRAIN   V34_DEBUG._V34S_LEN_8K0_1RT_MIN_1ST_TRAIN
#define V34S_LEN_8K0_MIN_LOCAL_TRAIN     V34_DEBUG._V34S_LEN_8K0_MIN_LOCAL_TRAIN
#define V34S_LEN_8K0_SPECIAL_LOCAL_TRAIN V34_DEBUG._V34S_LEN_8K0_SPECIAL_LOCAL_TRAIN
#define V34S_LEN_8K0_REMOTE_GUARD        V34_DEBUG._V34S_LEN_8K0_REMOTE_GUARD
#define v34_equalizer_slew_data_offset   V34_DEBUG._v34_equalizer_slew_data_offset
#define v34_helper_state_index           V34_DEBUG._v34_helper_state_index
#define v34_TRN2_MSE_report_rate         V34_DEBUG._v34_TRN2_MSE_report_rate
#define v34n_sm_INFO1c_end_delay         V34_DEBUG._v34n_sm_INFO1c_end_delay
#define v34s_reneg_test_noise_level      V34_DEBUG._v34s_reneg_test_noise_level
#define V34S_ANSW_8K0_1RT_Jsrt_to_S_SNdet V34_DEBUG._V34S_ANSW_8K0_1RT_Jsrt_to_S_SNdet
#define V34S_ANSW_8K0_1RT_S_SN_to_JEdet  V34_DEBUG._V34S_ANSW_8K0_1RT_S_SN_to_JEdet
#define V34S_ANSW_8K0_2RT_Jend_to_Jdet   V34_DEBUG._V34S_ANSW_8K0_2RT_Jend_to_Jdet
#define V34S_ANSW_8K0_3RT_SNend_to_Edet  V34_DEBUG._V34S_ANSW_8K0_3RT_SNend_to_Edet
#define v34s_conditional_frequency_offset V34_DEBUG._v34s_conditional_frequency_offset
#define V34S_INIT_8K0_2RT_S_SN_to_Edet   V34_DEBUG._V34S_INIT_8K0_2RT_S_SN_to_Edet
#define V34S_LEN_8K0_PRE_GEAR_CHANGE     V34_DEBUG._V34S_LEN_8K0_PRE_GEAR_CHANGE
#define V34S_ORIG_8K0_1RT_Jsrt_to_S_SNdet V34_DEBUG._V34S_ORIG_8K0_1RT_Jsrt_to_S_SNdet
#define V34S_ORIG_8K0_2RT_INFO1cend_to_Jsrt V34_DEBUG._V34S_ORIG_8K0_2RT_INFO1cend_to_Jsrt
#define V34S_ORIG_8K0_2RT_JEend_to_Edet  V34_DEBUG._V34S_ORIG_8K0_2RT_JEend_to_Edet
#define v34s_reneg_special_flag          V34_DEBUG._v34s_reneg_special_flag
#define V34S_RESP_8K0_3RT_S_SN_to_Edet   V34_DEBUG._V34S_RESP_8K0_3RT_S_SN_to_Edet
#define v34s_short_renegotiations        V34_DEBUG._v34s_short_renegotiations

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

typedef struct {
	local_d    uint16                      _v34n_rxtx_asymmetric_rates;
	local_d    uint16                      _v34n_rxtx_auxiliary_option;
	local_d    uint16                      _v34n_rxtx_data_rate_option;
	local_d    uint16                      _v34n_rx_asymmetric_option;
	local_d    uint16                      _v34n_rx_auxiliary_channel;
	local_d    uint16                      _v34n_rx_data_rate;
	local_d    uint16                      _v34n_rx_data_rate_option;
	local_d    uint16                      _v34n_rx_local_to_remote_maxrate;
	local_d    uint16                      _v34n_rx_remote_to_local_maxrate;
	local_d    uint16                      _v34n_rx_train_16pt;
	local_d    uint16                      _v34n_rx_trellis_setting;
	local_d    uint16                      _v34n_rx_use_nonlinear;
	local_d    uint16                      _v34n_rx_use_shaping;
	local_d    uint16                      _v34n_tx_asymmetric_option;
	local_d    uint16                      _v34n_tx_auxiliary_channel;
	local_d    uint16                      _v34n_tx_data_rate;
	local_d    uint16                      _v34n_tx_local_to_remote_maxrate;
	local_d    uint16                      _v34n_tx_remote_to_local_maxrate;
	local_d    uint16                      _v34n_tx_train_16pt;
	local_d    uint16                      _v34n_tx_use_nonlinear;
	local_d    uint16                      _v34n_tx_use_shaping;
} v34_local_t;

/* ************************************************************************* */

DEF_DATA(v34_local_t, v34_local)
#define V34_LOCAL_DATA v34_local_t v34_local
#define V34_LOCAL USE_DATA(v34_local)
#define v34_local_used

/* ************************************************************************* */

#define v34n_rxtx_asymmetric_rates       V34_LOCAL._v34n_rxtx_asymmetric_rates
#define v34n_rxtx_auxiliary_option       V34_LOCAL._v34n_rxtx_auxiliary_option
#define v34n_rxtx_data_rate_option       V34_LOCAL._v34n_rxtx_data_rate_option
#define v34n_rx_asymmetric_option        V34_LOCAL._v34n_rx_asymmetric_option
#define v34n_rx_auxiliary_channel        V34_LOCAL._v34n_rx_auxiliary_channel
#define v34n_rx_data_rate                V34_LOCAL._v34n_rx_data_rate
#define v34n_rx_data_rate_option         V34_LOCAL._v34n_rx_data_rate_option
#define v34n_rx_local_to_remote_maxrate  V34_LOCAL._v34n_rx_local_to_remote_maxrate
#define v34n_rx_remote_to_local_maxrate  V34_LOCAL._v34n_rx_remote_to_local_maxrate
#define v34n_rx_train_16pt               V34_LOCAL._v34n_rx_train_16pt
#define v34n_rx_trellis_setting          V34_LOCAL._v34n_rx_trellis_setting
#define v34n_rx_use_nonlinear            V34_LOCAL._v34n_rx_use_nonlinear
#define v34n_rx_use_shaping              V34_LOCAL._v34n_rx_use_shaping
#define v34n_tx_asymmetric_option        V34_LOCAL._v34n_tx_asymmetric_option
#define v34n_tx_auxiliary_channel        V34_LOCAL._v34n_tx_auxiliary_channel
#define v34n_tx_data_rate                V34_LOCAL._v34n_tx_data_rate
#define v34n_tx_local_to_remote_maxrate  V34_LOCAL._v34n_tx_local_to_remote_maxrate
#define v34n_tx_remote_to_local_maxrate  V34_LOCAL._v34n_tx_remote_to_local_maxrate
#define v34n_tx_train_16pt               V34_LOCAL._v34n_tx_train_16pt
#define v34n_tx_use_nonlinear            V34_LOCAL._v34n_tx_use_nonlinear
#define v34n_tx_use_shaping              V34_LOCAL._v34n_tx_use_shaping

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

typedef struct {
	fast_d     fract*                      _tx_passband_coef_pointer;
	fast_d     sint15                      _v34n_tx_trellis_setting;
	fast_d     sint15                      _v34_rx_trellis_best_score;
	fast_d     sint15                      _v34_rx_trellis_lookback_poffset;
	fast_d     sint15                      _v34_rx_trellis_yn_hat_poffset;
	fast_d     sint15                      _v34_rx_trellis_yn_poffset;
	fast_d     sint15                      _v34_tx_trellis_state;
	fast_d     uint16                      _ph4n_rx_trained_trellis;
	fast_d     uint16                      _ph4n_tx_receive_trellis;
	fast_d     uint16                      _v34_rx_trellis_new_scores [16];
} v34_fast_t;

/* ************************************************************************* */

DEF_DATA(v34_fast_t, v34_fast)
#define V34_FAST_DATA v34_fast_t v34_fast
#define V34_FAST USE_DATA(v34_fast)
#define v34_fast_used

/* ************************************************************************* */

#define tx_passband_coef_pointer         V34_FAST._tx_passband_coef_pointer
#define v34n_tx_trellis_setting          V34_FAST._v34n_tx_trellis_setting
#define v34_rx_trellis_best_score        V34_FAST._v34_rx_trellis_best_score
#define v34_rx_trellis_lookback_poffset  V34_FAST._v34_rx_trellis_lookback_poffset
#define v34_rx_trellis_yn_hat_poffset    V34_FAST._v34_rx_trellis_yn_hat_poffset
#define v34_rx_trellis_yn_poffset        V34_FAST._v34_rx_trellis_yn_poffset
#define v34_tx_trellis_state             V34_FAST._v34_tx_trellis_state
#define ph4n_rx_trained_trellis          V34_FAST._ph4n_rx_trained_trellis
#define ph4n_tx_receive_trellis          V34_FAST._ph4n_tx_receive_trellis
#define v34_rx_trellis_new_scores        V34_FAST._v34_rx_trellis_new_scores

/* ************************************************************************* */

#endif /* _DATA_V34_H */
