
/* ************************************************************************* */
/*
 *	parmd.h
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
 *	Module:		OMC
 *
 *	This file contains the parameter and status definitions for the omc
 *	processes.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 20:41:08  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _OMC_PARMD_H
#define _OMC_PARMD_H

/* ************************************************************************* */

#include "include/config.h"

/* ************************************************************************* */

typedef struct {
	uint8	_parm__dial_string [DIAL_STRING_SIZE];
	bool	_parm__dial_originate_en;
	bool	_parm__dial_tone_dialing_en;
	bool	_parm__dial_busy_tone_detect_en;
	bool	_parm__dial_dial_tone_det_en;
	uint16	_parm__dial_pause_wait_duration;
	uint16	_parm__dial_blind_dial_wait_duration;
	uint16 	_parm__dial_dial_tone_abort_duration;
	uint16	_parm__dial_dial_tone_wait_duration;
	uint16	_parm__dial_silence_wait_duration;
	uint16	_parm__dial_bong_wait_duration;
	uint16	_parm__dial_flash_make_duration;
	uint16	_parm__dial_flash_break_duration;
	uint16	_parm__dial_billing_delay_duration;
	uint16	_parm__dial_hook_off_min_duration;
	uint16	_parm__dial_hook_on_min_duration;
	bool	_parm__dial_null_bypasses_dialtone_detect_en;
	bool	_parm__dial_null_bypasses_blind_delay_en;
	bool	_parm__dial_bypass_post_dial_wait;
	bool	_parm__dial_dial_tone_det_rqd;
	bool	_stat__dial_string_reverse_originate_request;
	bool	_stat__dial_string_toggle_v25_calling_tone_request;
	uint16	_parm__dial_itel_cp_predial_mask;
	uint16	_parm__dial_itel_cp_secondary_dial_mask;
	uint16	_parm__dial_itel_cp_post_dial_mask;
	uint16	_parm__dial_itel_dial_option_mask;
	uint16	_parm__dial_answer_wait_duration;
	uint16	_parm__dial_post_dt_pause_duration;

	uint16	_parm__dp_allowed_mask;
	uint16	_parm__dp_preferred_mask;
	uint16	_parm__dp_autoselect_mask;
	uint16	_parm__dp_compression_mask;
	uint16	_parm__dp_cellular_mode;
	uint16	_parm__dp_cmn_async_format;
	uint16	_parm__dp_cmn_inactivity_disconnect_mode;
	uint16	_parm__dp_cmn_inactivity_duration;
	uint16	_parm__dp_cmn_break_mode;
	uint16	_parm__dp_cmn_break_duration;
	uint16	_parm__dp_cmn_tx_lsd_duration;
	uint16	_parm__dp_cmn_rx_lsd_duration;
	bool	_parm__dp_cmn_binary_en;
	bool	_parm__dp_cmn_hdlc_en;
	uint16	_parm__dp_cmn_hdlc_threshold;
	bool	_parm__dp_cmn_data_mon_en;
	uint16	_parm__dp_cmn_rate_index;
	uint16	_parm__dp_direct_sbd_mode;
	uint16	_parm__dp_direct_sbd_threshold;
	uint16	_parm__dp_buffered_flow_control_mode;
	uint16	_parm__dp_buffered_xoff_char;
	uint16	_parm__dp_buffered_xon_char;
	uint16	_parm__dp_lapm_tx_max_data_size;
	uint16	_parm__dp_lapm_rx_max_data_size;
	uint16	_parm__dp_lapm_tx_window_size;
	uint16	_parm__dp_lapm_rx_window_size;
	uint16	_parm__dp_lapm_test_control;
	uint16	_parm__dp_lapm_selective_reject_control;
	uint16	_parm__dp_lapm_fcs32_control;
	uint16	_parm__dp_lapm_startup_inactivity_duration;
	uint16	_parm__dp_lapm_retry_cnt;
	uint16	_parm__dp_lapm_mnp_mode;
	uint16	_parm__dp_lapm_xid_id [3];
	uint16	_parm__dp_v42bis_p1;
	uint16	_parm__dp_v42bis_p2;
	uint16	_parm__dp_mnp_protocol_level;
	uint16	_parm__dp_mnp_serial_number [6];
	uint16	_parm__dp_mnp_service_class;
	uint16	_parm__dp_mnp_max_data_size;
	bool	_parm__dp_mnp_block_mode_en;
	bool	_parm__dp_mnp_stream_size_256_en;
	bool	_parm__dp_mnp_header_optimize_en;
	bool	_parm__dp_mnp_selective_retransmit_en;
	uint16	_parm__dp_mnp_data_compression_select;
	uint16  _parm__dp_mnp_startup_inactivity_duration;
	uint16	_parm__dp_mnp_retry_cnt;

	uint16	_parm__dp_detect_odp_duration;
	uint16	_parm__dp_detect_adp_duration;
	uint16	_parm__dp_detect_odp_detect_threshold;
	uint16	_parm__dp_detect_adp_detect_threshold;
	uint16	_parm__dp_detect_flag_threshold;
	uint16	_parm__dp_autorel_type;
	uint16	_parm__dp_autorel_duration;
	uint16	_parm__dp_autorel_char;
	uint16	_parm__dp_disconnect_mgmnt_mode;
	uint16	_parm__dp_disconnect_mgmnt_duration;
	uint16	_parm__dp_start_delay;
	uint16	_parm__dp_selection_mask;
	uint16	_parm__dp_v120_detect_control;
	uint16  _stat__dp_v42bis_p0;
	uint16  _stat__dp_v42bis_p1;
	uint16  _stat__dp_v42bis_p2;
	uint16  _stat__dp_lapm_tx_window_size;
	uint16  _stat__dp_lapm_rx_window_size;
	uint16  _stat__dp_lapm_tx_max_data_size;
	uint16  _stat__dp_lapm_rx_max_data_size;
	uint16  _stat__dp_lapm_test_control;
	uint16  _stat__dp_lapm_selective_reject_control;
	uint16  _stat__dp_lapm_fcs32_control;
	uint16  _stat__dp_mnp_local_credit_amount;
	uint16  _stat__dp_mnp_max_data_size;
	uint16  _stat__dp_mnp_protocol_level;
	uint16  _stat__dp_mnp_service_class;
	uint16  _stat__dp_mnp_remote_credit_amount;
	uint16  _stat__dp_mnp_selective_retransmit_en;
	uint16  _stat__dp_mnp_data_compression_used;
	uint16  _stat__dp_mnp_stream_size_256_en;
	uint16  _stat__dp_mnp_header_optimize_en;
	uint16	_stat__dp_protocol;
	uint16	_stat__dp_compression;
	uint16	_stat__dp_disconnect_reason;
	uint16	_stat__dp_disconnect_subreason;
	uint16	_stat__dp_inactivity_tmr;
	uint16	_stat__dp_cellular_mode;

	bool	_parm__omc_dm_originate_en;
	bool	_parm__omc_dm_dial_originate_override_en;
	bool	_parm__omc_dm_dial_toggle_v25_calling_tone_override_en;
	uint16	_parm__omc_dm_options_mask;
	uint16	_parm__omc_v8_en_mask;
	uint16	_parm__omc_local_is_cellular;
	bool	_parm__omc_dm_billing_delay_en;
	uint16	_parm__omc_dmdp_max_startup_duration;
	uint16	_parm__omc_fp_max_startup_duration;
	uint16	_parm__omc_telephony_active_mask;
	uint16  _parm__omc_idle_off_hook;
	uint16	_stat__omc_originate;
	uint16	_stat__omc_carrier_family;
	uint16	_stat__omc_tx_data_rate;
	uint16	_stat__omc_rx_data_rate;
	uint16	_stat__omc_disconnect_reason;
	uint16	_stat__omc_state;
	uint16	_stat__omc_remote_is_cellular;

	uint16 _parm__dp_df_lapm_retx_metric_hit_value;
	uint16 _parm__dp_df_lapm_retx_metric_limit;
	uint16 _parm__dp_df_lapm_retx_adjust_cnt_max;
	uint16 _parm__dp_df_lapm_retx_speed_group_decrement;
	bool   _parm__dp_df_lapm_retx_adjust_via_retrain;
	uint16 _parm__dp_df_mnp_retx_metric_hit_value;
	uint16 _parm__dp_df_mnp_retx_metric_limit;
	uint16 _parm__dp_df_mnp_retx_adjust_cnt_max;
	uint16 _parm__dp_df_mnp_retx_speed_group_decrement;
	bool   _parm__dp_df_mnp_retx_adjust_via_retrain;
	uint16 _stat__dp_df_retx_metric;
	uint16 _stat__dp_df_retx_adjust_cnt;
	uint16 _stat__omc_v34_tx_rate_en_mask;

	uint32 _stat__omc_time;
	uint32 _stat__omc_idle_time_start;
	uint32 _stat__omc_call_time_start;
	uint16 _parm__omc_st_period_definition;
	uint32 _stat__omc_dp_time_start;
	uint32 _stat__omc_initial_tx_data_rate;
	uint32 _stat__omc_initial_rx_data_rate;
	uint32 _stat__omc_current_tx_data_rate;
	uint32 _stat__omc_current_rx_data_rate;
	uint32 _stat__omc_highest_tx_data_rate;
	uint32 _stat__omc_highest_rx_data_rate;
	uint16 _stat__dmmon_retrain_local_cnt;
	uint16 _stat__dmmon_retrain_auto_cnt;
	uint16 _stat__dmmon_retrain_remote_cnt;
	uint16 _stat__dmmon_renegotiate_local_cnt;
	uint16 _stat__dmmon_renegotiate_auto_cnt;
	uint16 _stat__dmmon_renegotiate_remote_cnt;
	uint32 _stat__dp_rx_hdlc_error_frame_cnt;
	uint32 _stat__dp_rx_hdlc_frame_cnt;
	uint32 _stat__dp_tx_hdlc_frame_cnt;
	uint32 _stat__dp_tx_df_cnt;
	uint32 _stat__dp_tx_df_retx_cnt;
	uint32 _stat__dp_rx_df_cnt;
	uint32 _stat__dp_rx_df_dup_cnt;
	uint32 _stat__dp_rx_df_missing_cnt;
	uint32 _stat__dp_rx_df_retx_cnt;
	uint32 _stat__dp_rx_overflow_cnt;
	uint32 _stat__dp_call_tx_compdata_mtr;
	uint32 _stat__dp_call_rx_compdata_mtr;
	uint32 _stat__dp_call_tx_data_mtr;
	uint32 _stat__dp_call_rx_data_mtr;
	uint32 _stat__dp_call_tx_comp_rate;
	uint32 _stat__dp_call_rx_comp_rate;
	uint32 _stat__dp_call_tx_cps;
	uint32 _stat__dp_call_rx_cps;
	uint32 _stat__dp_st_tx_compdata_mtr;
	uint32 _stat__dp_st_rx_compdata_mtr;
	uint32 _stat__dp_st_tx_data_mtr;
	uint32 _stat__dp_st_rx_data_mtr;
	uint32 _stat__dp_st_tx_comp_rate;
	uint32 _stat__dp_st_rx_comp_rate;
	uint32 _stat__dp_st_tx_cps;
	uint32 _stat__dp_st_rx_cps;

	bool	_parm__dial_rring_monitor_en;
	uint16	_parm__dial_rring_cease_duration;
	uint16	_parm__dial_rring_absent_duration;
	bool	_parm__dial_restricted_dial_pending;
} omc_parm_t;

/* ************************************************************************* */

DEF_DATA(omc_parm_t, omc_parm)
#define OMC_PARM_DATA omc_parm_t omc_parm
#define OMC_PARM USE_DATA(omc_parm)

/* ************************************************************************* */

#define parm__dial_string							(OMC_PARM._parm__dial_string)
#define parm__dial_originate_en						(OMC_PARM._parm__dial_originate_en)
#define parm__dial_tone_dialing_en					(OMC_PARM._parm__dial_tone_dialing_en)
#define parm__dial_busy_tone_detect_en				(OMC_PARM._parm__dial_busy_tone_detect_en)
#define parm__dial_dial_tone_det_en					(OMC_PARM._parm__dial_dial_tone_det_en)
#define parm__dial_pause_wait_duration				(OMC_PARM._parm__dial_pause_wait_duration)
#define parm__dial_blind_dial_wait_duration			(OMC_PARM._parm__dial_blind_dial_wait_duration)
#define parm__dial_dial_tone_abort_duration			(OMC_PARM._parm__dial_dial_tone_abort_duration)
#define parm__dial_dial_tone_wait_duration			(OMC_PARM._parm__dial_dial_tone_wait_duration)
#define parm__dial_silence_wait_duration			(OMC_PARM._parm__dial_silence_wait_duration)
#define parm__dial_bong_wait_duration				(OMC_PARM._parm__dial_bong_wait_duration)
#define parm__dial_flash_make_duration				(OMC_PARM._parm__dial_flash_make_duration)
#define parm__dial_flash_break_duration				(OMC_PARM._parm__dial_flash_break_duration)
#define parm__dial_billing_delay_duration			(OMC_PARM._parm__dial_billing_delay_duration)
#define parm__dial_hook_off_min_duration			(OMC_PARM._parm__dial_hook_off_min_duration)
#define parm__dial_hook_on_min_duration				(OMC_PARM._parm__dial_hook_on_min_duration)
#define parm__dial_null_bypasses_dialtone_detect_en	(OMC_PARM._parm__dial_null_bypasses_dialtone_detect_en)
#define parm__dial_null_bypasses_blind_delay_en		(OMC_PARM._parm__dial_null_bypasses_blind_delay_en)
#define parm__dial_bypass_post_dial_wait			(OMC_PARM._parm__dial_bypass_post_dial_wait)
#define parm__dial_dial_tone_det_rqd				(OMC_PARM._parm__dial_dial_tone_det_rqd)
#define stat__dial_string_reverse_originate_request	(OMC_PARM._stat__dial_string_reverse_originate_request)
#define stat__dial_string_toggle_v25_calling_tone_request (OMC_PARM._stat__dial_string_toggle_v25_calling_tone_request)
#define parm__dial_itel_cp_predial_mask				(OMC_PARM._parm__dial_itel_cp_predial_mask)
#define parm__dial_itel_cp_secondary_dial_mask		(OMC_PARM._parm__dial_itel_cp_secondary_dial_mask)
#define parm__dial_itel_cp_post_dial_mask			(OMC_PARM._parm__dial_itel_cp_post_dial_mask)
#define parm__dial_itel_dial_option_mask			(OMC_PARM._parm__dial_itel_dial_option_mask)

#define parm__dp_allowed_mask						(OMC_PARM._parm__dp_allowed_mask)
#define parm__dp_preferred_mask						(OMC_PARM._parm__dp_preferred_mask)
#define parm__dp_autoselect_mask					(OMC_PARM._parm__dp_autoselect_mask)
#define parm__dp_compression_mask					(OMC_PARM._parm__dp_compression_mask)
#define parm__dp_cellular_mode						(OMC_PARM._parm__dp_cellular_mode)
#define parm__dp_cmn_async_format					(OMC_PARM._parm__dp_cmn_async_format)
#define parm__dp_cmn_inactivity_disconnect_mode		(OMC_PARM._parm__dp_cmn_inactivity_disconnect_mode)
#define parm__dp_cmn_inactivity_duration			(OMC_PARM._parm__dp_cmn_inactivity_duration)
#define parm__dp_cmn_break_mode						(OMC_PARM._parm__dp_cmn_break_mode)
#define parm__dp_cmn_break_duration					(OMC_PARM._parm__dp_cmn_break_duration)
#define parm__dp_cmn_tx_lsd_duration				(OMC_PARM._parm__dp_cmn_tx_lsd_duration)
#define parm__dp_cmn_rx_lsd_duration				(OMC_PARM._parm__dp_cmn_rx_lsd_duration)
#define parm__dp_cmn_binary_en						(OMC_PARM._parm__dp_cmn_binary_en)
#define parm__dp_cmn_hdlc_en						(OMC_PARM._parm__dp_cmn_hdlc_en)
#define parm__dp_cmn_hdlc_threshold					(OMC_PARM._parm__dp_cmn_hdlc_threshold)
#define parm__dp_cmn_data_mon_en					(OMC_PARM._parm__dp_cmn_data_mon_en)
#define parm__dp_cmn_rate_index						(OMC_PARM._parm__dp_cmn_rate_index)
#define parm__dp_direct_sbd_mode					(OMC_PARM._parm__dp_direct_sbd_mode)
#define parm__dp_direct_sbd_threshold				(OMC_PARM._parm__dp_direct_sbd_threshold)
#define parm__dp_buffered_flow_control_mode			(OMC_PARM._parm__dp_buffered_flow_control_mode)
#define parm__dp_buffered_xoff_char					(OMC_PARM._parm__dp_buffered_xoff_char)
#define parm__dp_buffered_xon_char					(OMC_PARM._parm__dp_buffered_xon_char)
#define parm__dp_lapm_tx_max_data_size				(OMC_PARM._parm__dp_lapm_tx_max_data_size)
#define parm__dp_lapm_rx_max_data_size				(OMC_PARM._parm__dp_lapm_rx_max_data_size)
#define parm__dp_lapm_tx_window_size				(OMC_PARM._parm__dp_lapm_tx_window_size)
#define parm__dp_lapm_rx_window_size				(OMC_PARM._parm__dp_lapm_rx_window_size)
#define parm__dp_lapm_test_control					(OMC_PARM._parm__dp_lapm_test_control)
#define parm__dp_lapm_selective_reject_control		(OMC_PARM._parm__dp_lapm_selective_reject_control)
#define parm__dp_lapm_fcs32_control					(OMC_PARM._parm__dp_lapm_fcs32_control)
#define parm__dp_lapm_startup_inactivity_duration	(OMC_PARM._parm__dp_lapm_startup_inactivity_duration)
#define parm__dp_lapm_retry_cnt						(OMC_PARM._parm__dp_lapm_retry_cnt)
#define parm__dp_lapm_mnp_mode						(OMC_PARM._parm__dp_lapm_mnp_mode)
#define parm__dp_lapm_xid_id						(OMC_PARM._parm__dp_lapm_xid_id)
#define parm__dp_v42bis_p1							(OMC_PARM._parm__dp_v42bis_p1)
#define parm__dp_v42bis_p2							(OMC_PARM._parm__dp_v42bis_p2)
#define parm__dp_mnp_protocol_level					(OMC_PARM._parm__dp_mnp_protocol_level)
#define parm__dp_mnp_serial_number					(OMC_PARM._parm__dp_mnp_serial_number)
#define parm__dp_mnp_service_class					(OMC_PARM._parm__dp_mnp_service_class)
#define parm__dp_mnp_max_data_size					(OMC_PARM._parm__dp_mnp_max_data_size)
#define parm__dp_mnp_block_mode_en					(OMC_PARM._parm__dp_mnp_block_mode_en)
#define parm__dp_mnp_stream_size_256_en				(OMC_PARM._parm__dp_mnp_stream_size_256_en)
#define parm__dp_mnp_header_optimize_en				(OMC_PARM._parm__dp_mnp_header_optimize_en)
#define parm__dp_mnp_selective_retransmit_en		(OMC_PARM._parm__dp_mnp_selective_retransmit_en)
#define parm__dp_mnp_data_compression_select		(OMC_PARM._parm__dp_mnp_data_compression_select)
#define parm__dp_mnp_startup_inactivity_duration	(OMC_PARM._parm__dp_mnp_startup_inactivity_duration)
#define parm__dp_mnp_retry_cnt						(OMC_PARM._parm__dp_mnp_retry_cnt)
#define parm__dp_detect_odp_duration				(OMC_PARM._parm__dp_detect_odp_duration)
#define parm__dp_detect_adp_duration				(OMC_PARM._parm__dp_detect_adp_duration)
#define parm__dp_detect_odp_detect_threshold		(OMC_PARM._parm__dp_detect_odp_detect_threshold)
#define parm__dp_detect_adp_detect_threshold		(OMC_PARM._parm__dp_detect_adp_detect_threshold)
#define parm__dp_detect_flag_threshold				(OMC_PARM._parm__dp_detect_flag_threshold)
#define parm__dp_autorel_type						(OMC_PARM._parm__dp_autorel_type)
#define parm__dp_autorel_duration					(OMC_PARM._parm__dp_autorel_duration)
#define parm__dp_autorel_char						(OMC_PARM._parm__dp_autorel_char)
#define parm__dp_disconnect_mgmnt_mode				(OMC_PARM._parm__dp_disconnect_mgmnt_mode)
#define parm__dp_disconnect_mgmnt_duration			(OMC_PARM._parm__dp_disconnect_mgmnt_duration)
#define parm__dp_start_delay						(OMC_PARM._parm__dp_start_delay)
#define parm__dp_selection_mask						(OMC_PARM._parm__dp_selection_mask)
#define parm__dp_v120_detect_control				(OMC_PARM._parm__dp_v120_detect_control)
#define stat__dp_v42bis_p0							(OMC_PARM._stat__dp_v42bis_p0)
#define stat__dp_v42bis_p1							(OMC_PARM._stat__dp_v42bis_p1)
#define stat__dp_v42bis_p2							(OMC_PARM._stat__dp_v42bis_p2)
#define stat__dp_lapm_tx_window_size				(OMC_PARM._stat__dp_lapm_tx_window_size)
#define stat__dp_lapm_rx_window_size				(OMC_PARM._stat__dp_lapm_rx_window_size)
#define stat__dp_lapm_tx_max_data_size				(OMC_PARM._stat__dp_lapm_tx_max_data_size)
#define stat__dp_lapm_rx_max_data_size				(OMC_PARM._stat__dp_lapm_rx_max_data_size)
#define stat__dp_lapm_test_control					(OMC_PARM._stat__dp_lapm_test_control)
#define stat__dp_lapm_selective_reject_control		(OMC_PARM._stat__dp_lapm_selective_reject_control)
#define stat__dp_lapm_fcs32_control					(OMC_PARM._stat__dp_lapm_fcs32_control)
#define stat__dp_mnp_local_credit_amount			(OMC_PARM._stat__dp_mnp_local_credit_amount)
#define stat__dp_mnp_max_data_size					(OMC_PARM._stat__dp_mnp_max_data_size)
#define stat__dp_mnp_protocol_level					(OMC_PARM._stat__dp_mnp_protocol_level)
#define stat__dp_mnp_service_class					(OMC_PARM._stat__dp_mnp_service_class)
#define stat__dp_mnp_remote_credit_amount			(OMC_PARM._stat__dp_mnp_remote_credit_amount)
#define stat__dp_mnp_selective_retransmit_en		(OMC_PARM._stat__dp_mnp_selective_retransmit_en)
#define stat__dp_mnp_data_compression_used			(OMC_PARM._stat__dp_mnp_data_compression_used)
#define stat__dp_mnp_stream_size_256_en				(OMC_PARM._stat__dp_mnp_stream_size_256_en)
#define stat__dp_mnp_header_optimize_en				(OMC_PARM._stat__dp_mnp_header_optimize_en)
#define stat__dp_protocol							(OMC_PARM._stat__dp_protocol)
#define stat__dp_compression						(OMC_PARM._stat__dp_compression)
#define stat__dp_disconnect_reason					(OMC_PARM._stat__dp_disconnect_reason)
#define stat__dp_disconnect_subreason				(OMC_PARM._stat__dp_disconnect_subreason)
#define stat__dp_inactivity_tmr						(OMC_PARM._stat__dp_inactivity_tmr)
#define stat__dp_cellular_mode						(OMC_PARM._stat__dp_cellular_mode)

#define parm__omc_dm_originate_en					(OMC_PARM._parm__omc_dm_originate_en)
#define parm__omc_dm_dial_originate_override_en		(OMC_PARM._parm__omc_dm_dial_originate_override_en)
#define parm__omc_dm_dial_toggle_v25_calling_tone_override_en	(OMC_PARM._parm__omc_dm_dial_toggle_v25_calling_tone_override_en)
#define parm__omc_dm_options_mask					(OMC_PARM._parm__omc_dm_options_mask)
#define parm__omc_v8_en_mask						(OMC_PARM._parm__omc_v8_en_mask)
#define parm__omc_local_is_cellular					(OMC_PARM._parm__omc_local_is_cellular)
#define parm__omc_dm_billing_delay_en				(OMC_PARM._parm__omc_dm_billing_delay_en)
#define parm__omc_dmdp_max_startup_duration			(OMC_PARM._parm__omc_dmdp_max_startup_duration)
#define parm__omc_fp_max_startup_duration			(OMC_PARM._parm__omc_fp_max_startup_duration)
#define parm__omc_idle_off_hook						(OMC_PARM._parm__omc_idle_off_hook)
#define parm__omc_telephony_active_mask				(OMC_PARM._parm__omc_telephony_active_mask)
#define stat__omc_originate							(OMC_PARM._stat__omc_originate)
#define stat__omc_carrier_family					(OMC_PARM._stat__omc_carrier_family)
#define stat__omc_tx_data_rate						(OMC_PARM._stat__omc_tx_data_rate)
#define stat__omc_rx_data_rate						(OMC_PARM._stat__omc_rx_data_rate)
#define stat__omc_disconnect_reason					(OMC_PARM._stat__omc_disconnect_reason)
#define stat__omc_state								(OMC_PARM._stat__omc_state)
#define stat__omc_remote_is_cellular				(OMC_PARM._stat__omc_remote_is_cellular)

#define parm__dp_df_lapm_retx_metric_hit_value		(OMC_PARM._parm__dp_df_lapm_retx_metric_hit_value)
#define parm__dp_df_lapm_retx_metric_limit			(OMC_PARM._parm__dp_df_lapm_retx_metric_limit)
#define parm__dp_df_lapm_retx_adjust_cnt_max		(OMC_PARM._parm__dp_df_lapm_retx_adjust_cnt_max)
#define parm__dp_df_lapm_retx_speed_group_decrement	(OMC_PARM._parm__dp_df_lapm_retx_speed_group_decrement)
#define parm__dp_df_lapm_retx_adjust_via_retrain	(OMC_PARM._parm__dp_df_lapm_retx_adjust_via_retrain)
#define parm__dp_df_mnp_retx_metric_hit_value		(OMC_PARM._parm__dp_df_mnp_retx_metric_hit_value)
#define parm__dp_df_mnp_retx_metric_limit			(OMC_PARM._parm__dp_df_mnp_retx_metric_limit)
#define parm__dp_df_mnp_retx_adjust_cnt_max			(OMC_PARM._parm__dp_df_mnp_retx_adjust_cnt_max)
#define parm__dp_df_mnp_retx_speed_group_decrement	(OMC_PARM._parm__dp_df_mnp_retx_speed_group_decrement)
#define parm__dp_df_mnp_retx_adjust_via_retrain		(OMC_PARM._parm__dp_df_mnp_retx_adjust_via_retrain)
#define stat__dp_df_retx_metric						(OMC_PARM._stat__dp_df_retx_metric)
#define stat__dp_df_retx_adjust_cnt					(OMC_PARM._stat__dp_df_retx_adjust_cnt)
#define stat__omc_v34_tx_rate_en_mask				(OMC_PARM._stat__omc_v34_tx_rate_en_mask)

#define stat__omc_time								(OMC_PARM._stat__omc_time)
#define stat__omc_idle_time_start					(OMC_PARM._stat__omc_idle_time_start)
#define stat__omc_call_time_start					(OMC_PARM._stat__omc_call_time_start)
#define parm__omc_st_period_definition				(OMC_PARM._parm__omc_st_period_definition)
#define stat__omc_dp_time_start						(OMC_PARM._stat__omc_dp_time_start)
#define stat__omc_initial_tx_data_rate				(OMC_PARM._stat__omc_initial_tx_data_rate)
#define stat__omc_initial_rx_data_rate				(OMC_PARM._stat__omc_initial_rx_data_rate)
#define stat__omc_current_tx_data_rate				(OMC_PARM._stat__omc_current_tx_data_rate)
#define stat__omc_current_rx_data_rate				(OMC_PARM._stat__omc_current_rx_data_rate)
#define stat__omc_highest_tx_data_rate				(OMC_PARM._stat__omc_highest_tx_data_rate)
#define stat__omc_highest_rx_data_rate				(OMC_PARM._stat__omc_highest_rx_data_rate)
#define stat__dmmon_retrain_local_cnt				(OMC_PARM._stat__dmmon_retrain_local_cnt)
#define stat__dmmon_retrain_auto_cnt				(OMC_PARM._stat__dmmon_retrain_auto_cnt)
#define stat__dmmon_retrain_remote_cnt				(OMC_PARM._stat__dmmon_retrain_remote_cnt)
#define stat__dmmon_renegotiate_local_cnt			(OMC_PARM._stat__dmmon_renegotiate_local_cnt)
#define stat__dmmon_renegotiate_auto_cnt			(OMC_PARM._stat__dmmon_renegotiate_auto_cnt)
#define stat__dmmon_renegotiate_remote_cnt			(OMC_PARM._stat__dmmon_renegotiate_remote_cnt)
#define stat__dp_rx_hdlc_error_frame_cnt			(OMC_PARM._stat__dp_rx_hdlc_error_frame_cnt)
#define stat__dp_rx_hdlc_frame_cnt					(OMC_PARM._stat__dp_rx_hdlc_frame_cnt)
#define stat__dp_tx_hdlc_frame_cnt					(OMC_PARM._stat__dp_tx_hdlc_frame_cnt)
#define stat__dp_tx_df_cnt							(OMC_PARM._stat__dp_tx_df_cnt)
#define stat__dp_tx_df_retx_cnt						(OMC_PARM._stat__dp_tx_df_retx_cnt)
#define stat__dp_rx_df_cnt							(OMC_PARM._stat__dp_rx_df_cnt)
#define stat__dp_rx_df_dup_cnt						(OMC_PARM._stat__dp_rx_df_dup_cnt)
#define stat__dp_rx_df_missing_cnt					(OMC_PARM._stat__dp_rx_df_missing_cnt)
#define stat__dp_rx_df_retx_cnt						(OMC_PARM._stat__dp_rx_df_retx_cnt)
#define stat__dp_rx_overflow_cnt					(OMC_PARM._stat__dp_rx_overflow_cnt)
#define stat__dp_call_tx_compdata_mtr				(OMC_PARM._stat__dp_call_tx_compdata_mtr)
#define stat__dp_call_rx_compdata_mtr				(OMC_PARM._stat__dp_call_rx_compdata_mtr)
#define stat__dp_call_tx_data_mtr					(OMC_PARM._stat__dp_call_tx_data_mtr)
#define stat__dp_call_rx_data_mtr					(OMC_PARM._stat__dp_call_rx_data_mtr)
#define stat__dp_call_tx_comp_rate					(OMC_PARM._stat__dp_call_tx_comp_rate)
#define stat__dp_call_rx_comp_rate					(OMC_PARM._stat__dp_call_rx_comp_rate)
#define stat__dp_call_tx_cps						(OMC_PARM._stat__dp_call_tx_cps)
#define stat__dp_call_rx_cps						(OMC_PARM._stat__dp_call_rx_cps)
#define stat__dp_st_tx_compdata_mtr					(OMC_PARM._stat__dp_st_tx_compdata_mtr)
#define stat__dp_st_rx_compdata_mtr					(OMC_PARM._stat__dp_st_rx_compdata_mtr)
#define stat__dp_st_tx_data_mtr						(OMC_PARM._stat__dp_st_tx_data_mtr)
#define stat__dp_st_rx_data_mtr						(OMC_PARM._stat__dp_st_rx_data_mtr)
#define stat__dp_st_tx_comp_rate					(OMC_PARM._stat__dp_st_tx_comp_rate)
#define stat__dp_st_rx_comp_rate					(OMC_PARM._stat__dp_st_rx_comp_rate)
#define stat__dp_st_tx_cps							(OMC_PARM._stat__dp_st_tx_cps)
#define stat__dp_st_rx_cps							(OMC_PARM._stat__dp_st_rx_cps)

#define parm__dial_answer_wait_duration		(OMC_PARM._parm__dial_answer_wait_duration)
#define parm__dial_post_dt_pause_duration	(OMC_PARM._parm__dial_post_dt_pause_duration)
#define parm__dial_rring_monitor_en			(OMC_PARM._parm__dial_rring_monitor_en)
#define parm__dial_rring_cease_duration		(OMC_PARM._parm__dial_rring_cease_duration)
#define parm__dial_rring_absent_duration	(OMC_PARM._parm__dial_rring_absent_duration)
#define parm__dial_restricted_dial_pending	(OMC_PARM._parm__dial_restricted_dial_pending)

/* ************************************************************************* */

#endif /* _OMC_PARMD_H */
