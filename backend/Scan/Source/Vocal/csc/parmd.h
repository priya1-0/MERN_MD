
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
 *	Module:		CSC
 *
 *	This file contains the public parameters definitions for
 *	the parameters configuring the CSC module.
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

#ifndef _CSC_PARMD_H
#define _CSC_PARMD_H

/* ************************************************************************* */

/* ************************************* */
/*
 *		Prefixes:
 *			ci_	command interface
 *			cs_	csc state machine
 *			sq_	signal
 *			if_	dte interface
 *
 */
/* ************************************* */

typedef struct {
	bool	_parm_csc_allow_early_cmds;
	bool	_parm_csc_delayed_s3_echo_en;
	bool	_parm_csc_reset_delay_en;
	bool	_parm_csc_command_echo_en;
	bool	_parm_csc_quiet_results_en;
	bool	_parm_csc_verbose_results_en;
	char	_parm_csc_command_termination_character;
	char	_parm_csc_response_format_character;
	char	_parm_csc_command_edit_character;
	char	_parm_csc_escape_character;
	char	_parm_csc_remote_escape_character;
	bool	_parm_csc_cmd_escape_en;
	uint8	_parm_csc_escape_prompt_release_duration;
	bool	_parm_csc_break_is_online_escape_en;
	uint8	_parm_csc_response_reject_control;
	uint8	_parm_csc_report_select_control;
	uint8	_parm_csc_report_select_override;
	bool	_parm_csc_modulation_report_en;
	bool	_parm_csc_local_rate_report_en;
	bool	_parm_csc_data_protocol_report_en;
	bool	_parm_csc_data_compression_report_en;
	uint16	_parm_csc_store_telephone_number;
	uint16	_parm_csc_default_restore_profile;
	uint16	_parm_csc_remote_password;
	uint16	_parm_csc_callback_password;
	uint16	_parm_csc_break_control;
	bool	_parm_csc_originate;

	uint8	_parm_if_assumed_dte_rate;
	uint8	_parm_if_assumed_dte_parity;
	uint8	_parm_if_fix_dte_character_rate;
	uint8	_parm_if_fix_dte_character_format;
	uint8	_parm_if_fix_dte_character_parity;

	uint8	_parm_csc_autoanswer_ring_cnt;
	uint8	_parm_csc_sleep_inactivity_duration;
	uint8	_parm_csc_disconnect_inactivity_duration;
	uint16	_parm_csc_inactivity_ignores_direct_rx;

	bool	_parm_lb_lalb_en;
	uint16	_parm_lb_rdlb_requested;
	bool	_parm_lb_rdlb_self_test_en;
	bool	_parm_lb_lalb_self_test_en;
	bool	_parm_lb_rdlb_remote_en;
	uint16	_parm_lb_test_timer;

	uint8	_parm_drv_speaker_control;
	uint8	_parm_drv_speaker_volume;
	bool	_parm_drv_leased_line_en;
	uint16	_parm_drv_telephone_jack_select;

	char	_parm_sg_xon_character;
	char	_parm_sg_xoff_character;
	uint8	_parm_sg_flow_control_dce_by_dte_en;
	uint8	_parm_sg_flow_control_dte_by_dce_en;
	bool	_parm_sg_xon_after_connect_en;
	bool	_parm_sg_dm_xon_after_connect_en;
	bool	_parm_sg_fx1_xon_after_connect_en;
	bool	_parm_sg_xon_on_no_activity_en;
	bool	_parm_sg_cts_on_no_activity_en;
	bool	_parm_sg_xoff_on_critical_en;
	bool	_parm_sg_cts_on_critical_en;
	uint8	_parm_sg_fc_no_activity_duration;
	bool	_parm_sg_dce_by_dte_fc_eats_xon_xoff_en;
	bool	_parm_sg_dce_by_dte_fc_uses_xon_xoff_en;
	bool	_parm_sg_dce_by_dte_fc_uses_cts_en;
	bool	_parm_sg_dte_by_dce_fc_uses_xon_xoff_en;
	bool	_parm_sg_dte_by_dce_fc_uses_cts_en;

	bool	_parm_dte_rx_bor_en;
	bool	_parm_dte_tx_bor_en;
	bool	_parm_dte_rx_ascii_rep_en;

	/* Status */
	uint16	_stat_lb_rdlb_within;
	uint16	_stat_if_dte_speed;
	bool	_stat_csc_autoanswer;
	uint16	_stat_csc_tx_data_rate;
	uint16	_stat_csc_rx_data_rate;
	uint16	_stat_csc_rx_level;
	uint16	_stat_csc_carrier_family;
	uint16	_stat_csc_originate;
	uint16	_stat_csc_protocol;
	uint16	_stat_csc_compression;

	uint16	_parm_csc_bor_diag_en;
	uint16	_parm_csc_report_fx2_idr_en;
	uint16	_parm_csc_report_fx2_nsr_en;
	uint16	_parm_csc_report_fx2_rpr_en;
	uint16	_parm_csc_report_fx2_tpr_en;
	uint16	_parm_csc_adaptive_answer_en;
	uint16	_parm_csc_fx2_fc_code;

	uint16	_stat_csc_hangup_code;
	uint16	_stat_csc_hangup_code_en;

	bool	_parm_csc_bypass_reset_delay;
	bool	_parm_csc_bypass_post_cmd_delay;
	bool	_parm_csc_allow_early_commands;
	uint16	_parm_csc_reset_delay_duration;

	uint16	_parm_dte_char_detect_duration;
	bool	_parm_dte_char_detect_en;
	uint16	_stat_dte_char_seen;

	bool	_parm_csc_fx1_faa_en;

	uint16	_parm_csc_telephony_active_mask;
	uint8	_parm_csc_itel_country_code;
	uint8	_parm_itel_country_code;
	uint16	_parm_itel_cp_predial_mask;
	uint16	_parm_itel_cp_secondary_dial_mask;
	uint16	_parm_itel_cp_post_dial_mask;
	uint8	_parm_itel_pulse_make_time;
	uint8	_parm_itel_pulse_break_time;
	uint16	_parm_itel_pulse_post_digit_time;
	uint8	_parm_itel_dtmf_tone_on_time;
	uint8	_parm_itel_dtmf_tone_off_time;
	uint8	_parm_itel_dtmf_high_tone_level;
	uint8	_parm_itel_dtmf_low_tone_level;
	uint8	_parm_itel_max_transmit_level;
	uint8	_parm_itel_min_receive_threshold;
	uint8	_parm_itel_carrier_loss_disconnect_duration;
	uint16	_parm_itel_dial_option_mask;
	uint8	_parm_itel_dial_tone_criteria_duration;
	uint8	_parm_itel_dial_tone_wait_duration;
	uint8	_parm_itel_post_dial_tone_pause_duration;
	uint8	_parm_itel_blind_dial_wait_min;
	uint16	_parm_itel_blind_dial_wait_max;
	uint8	_parm_itel_dial_answer_wait_duration;
	uint8	_parm_itel_ring_to_answer_min_duration;
	uint8	_parm_itel_ring_to_answer_max_duration;
	uint8	_parm_itel_ring_cnt_min;
	uint8	_parm_itel_ring_cnt_max;
	uint8	_parm_itel_max_delayed_dial_attempts;
	uint8	_parm_itel_delayed_dial_12_interval;
	uint8	_parm_itel_delayed_dial_subsequent_interval;
	uint16	_parm_itel_delayed_reset_duration;
	uint8	_parm_itel_codec_impedance;
    uint16  _parm__daa_itel_country_code;
    uint16  _parm__daa_itel_daa_reg16;
    uint16  _parm__daa_itel_daa_reg26;
    uint16  _parm__daa_itel_daa_reg30;
    uint16  _parm__daa_itel_daa_reg31;
	uint16	_parm_csc_spk_monitor_control;
	uint16	_parm_csc_spk_monitor_volume;
	bool	_parm_csc_online_retrain_request;
	uint16	_stat_csc_dial_fail_reason;
	uint16	_stat_csc_omc_disconnect_reason;
} csc_parm_t;

/* ************************************************************************* */

DEF_DATA(csc_parm_t, csc_parm)
#define CSC_PARM_DATA csc_parm_t csc_parm
#define CSC_PARM USE_DATA(csc_parm)

/* ************************************************************************* */

#define parm__csc_allow_early_cmds					(CSC_PARM._parm_csc_allow_early_cmds)
#define parm__csc_reset_delay_en					(CSC_PARM._parm_csc_reset_delay_en)
#define parm__csc_delayed_s3_echo_en				(CSC_PARM._parm_csc_delayed_s3_echo_en)
#define parm__csc_command_echo_en					(CSC_PARM._parm_csc_command_echo_en)
#define parm__csc_quiet_results_en					(CSC_PARM._parm_csc_quiet_results_en)
#define parm__csc_verbose_results_en				(CSC_PARM._parm_csc_verbose_results_en)
#define parm__csc_command_termination_character		(CSC_PARM._parm_csc_command_termination_character)
#define parm__csc_response_format_character			(CSC_PARM._parm_csc_response_format_character)
#define parm__csc_command_edit_character			(CSC_PARM._parm_csc_command_edit_character)
#define parm__csc_escape_character					(CSC_PARM._parm_csc_escape_character)
#define parm__csc_cmd_escape_en						(CSC_PARM._parm_csc_cmd_escape_en)
#define parm__csc_remote_escape_character			(CSC_PARM._parm_csc_remote_escape_character)
#define parm__csc_escape_prompt_release_duration	(CSC_PARM._parm_csc_escape_prompt_release_duration)
#define parm__csc_break_is_online_escape_en			(CSC_PARM._parm_csc_break_is_online_escape_en)
#define parm__csc_response_reject_control			(CSC_PARM._parm_csc_response_reject_control)
#define parm__csc_report_select_control				(CSC_PARM._parm_csc_report_select_control)
#define parm__csc_report_select_override			(CSC_PARM._parm_csc_report_select_override)
#define parm__csc_modulation_report_en				(CSC_PARM._parm_csc_modulation_report_en)
#define parm__csc_local_rate_report_en				(CSC_PARM._parm_csc_local_rate_report_en)
#define parm__csc_data_protocol_report_en			(CSC_PARM._parm_csc_data_protocol_report_en)
#define parm__csc_data_compression_report_en		(CSC_PARM._parm_csc_data_compression_report_en)
#define parm__csc_store_telephone_number			(CSC_PARM._parm_csc_store_telephone_number)
#define parm__csc_default_restore_profile			(CSC_PARM._parm_csc_default_restore_profile)
#define parm__csc_remote_password					(CSC_PARM._parm_csc_remote_password)
#define parm__csc_callback_password					(CSC_PARM._parm_csc_callback_password)
#define parm__csc_break_control						(CSC_PARM._parm_csc_break_control)
#define parm__csc_originate							(CSC_PARM._parm_csc_originate)
#define parm__if_assumed_dte_rate					(CSC_PARM._parm_if_assumed_dte_rate)
#define parm__if_assumed_dte_parity					(CSC_PARM._parm_if_assumed_dte_parity)
#define parm__if_fix_dte_character_rate				(CSC_PARM._parm_if_fix_dte_character_rate)
#define parm__if_fix_dte_character_format			(CSC_PARM._parm_if_fix_dte_character_format)
#define parm__if_fix_dte_character_parity			(CSC_PARM._parm_if_fix_dte_character_parity)
#define parm__csc_autoanswer_ring_cnt				(CSC_PARM._parm_csc_autoanswer_ring_cnt)
#define parm__csc_sleep_inactivity_duration			(CSC_PARM._parm_csc_sleep_inactivity_duration)
#define parm__csc_disconnect_inactivity_duration	(CSC_PARM._parm_csc_disconnect_inactivity_duration)
#define parm__csc_inactivity_ignores_direct_rx		(CSC_PARM._parm_csc_inactivity_ignores_direct_rx)
#define parm__lb_lalb_en							(CSC_PARM._parm_lb_lalb_en)
#define parm__lb_rdlb_requested						(CSC_PARM._parm_lb_rdlb_requested)
#define parm__lb_rdlb_self_test_en					(CSC_PARM._parm_lb_rdlb_self_test_en)
#define parm__lb_lalb_self_test_en					(CSC_PARM._parm_lb_lalb_self_test_en)
#define parm__lb_rdlb_remote_en						(CSC_PARM._parm_lb_rdlb_remote_en)
#define parm__lb_test_timer							(CSC_PARM._parm_lb_test_timer)
#define parm__drv_speaker_control					(CSC_PARM._parm_drv_speaker_control)
#define parm__drv_speaker_volume					(CSC_PARM._parm_drv_speaker_volume)
#define parm__drv_leased_line_en					(CSC_PARM._parm_drv_leased_line_en)
#define parm__drv_telephone_jack_select				(CSC_PARM._parm_drv_telephone_jack_select)

#define parm__sg_xon_character						(CSC_PARM._parm_sg_xon_character)
#define parm__sg_xoff_character						(CSC_PARM._parm_sg_xoff_character)
#define parm__sg_flow_control_dce_by_dte_en			(CSC_PARM._parm_sg_flow_control_dce_by_dte_en)
#define parm__sg_flow_control_dte_by_dce_en			(CSC_PARM._parm_sg_flow_control_dte_by_dce_en)
#define parm__sg_cts_control						(CSC_PARM._parm_sg_cts_control)
#define parm__sg_dsr_control						(CSC_PARM._parm_sg_dsr_control)
#define parm__sg_dcd_control						(CSC_PARM._parm_sg_dcd_control)
#define parm__sg_dtr_mode							(CSC_PARM._parm_sg_dtr_mode)
#define parm__sg_dtr_debounce_duration				(CSC_PARM._parm_sg_dtr_debounce_duration)
#define parm__sg_xon_after_connect_en				(CSC_PARM._parm_sg_xon_after_connect_en)
#define parm__sg_dm_xon_after_connect_en			(CSC_PARM._parm_sg_dm_xon_after_connect_en)
#define parm__sg_fx1_xon_after_connect_en			(CSC_PARM._parm_sg_fx1_xon_after_connect_en)
#define parm__sg_xon_on_no_activity_en				(CSC_PARM._parm_sg_xon_on_no_activity_en)
#define parm__sg_cts_on_no_activity_en				(CSC_PARM._parm_sg_cts_on_no_activity_en)
#define parm__sg_xoff_on_critical_en				(CSC_PARM._parm_sg_xoff_on_critical_en)
#define parm__sg_cts_on_critical_en					(CSC_PARM._parm_sg_cts_on_critical_en)
#define parm__sg_fc_no_activity_duration			(CSC_PARM._parm_sg_fc_no_activity_duration)
#define parm__sg_dce_by_dte_fc_eats_xon_xoff_en		(CSC_PARM._parm_sg_dce_by_dte_fc_eats_xon_xoff_en)
#define parm__sg_dce_by_dte_fc_uses_xon_xoff_en		(CSC_PARM._parm_sg_dce_by_dte_fc_uses_xon_xoff_en)
#define parm__sg_dce_by_dte_fc_uses_cts_en			(CSC_PARM._parm_sg_dce_by_dte_fc_uses_cts_en)
#define parm__sg_dte_by_dce_fc_uses_xon_xoff_en		(CSC_PARM._parm_sg_dte_by_dce_fc_uses_xon_xoff_en)
#define parm__sg_dte_by_dce_fc_uses_cts_en			(CSC_PARM._parm_sg_dte_by_dce_fc_uses_cts_en)

#define parm__dte_rx_bor_en							(CSC_PARM._parm_dte_rx_bor_en)
#define parm__dte_tx_bor_en							(CSC_PARM._parm_dte_tx_bor_en)
#define parm__dte_rx_ascii_rep_en					(CSC_PARM._parm_dte_rx_ascii_rep_en)

#define stat__lb_rdlb_within						(CSC_PARM._stat_lb_rdlb_within)
#define stat__if_dte_speed							(CSC_PARM._stat_if_dte_speed)
#define stat__csc_autoanswer						(CSC_PARM._stat_csc_autoanswer)
#define stat__csc_tx_data_rate						(CSC_PARM._stat_csc_tx_data_rate)
#define stat__csc_rx_data_rate						(CSC_PARM._stat_csc_rx_data_rate)
#define stat__csc_rx_level							(CSC_PARM._stat_csc_rx_level)
#define stat__csc_carrier_family					(CSC_PARM._stat_csc_carrier_family)
#define stat__csc_originate							(CSC_PARM._stat_csc_originate)
#define stat__csc_protocol							(CSC_PARM._stat_csc_protocol)
#define stat__csc_compression						(CSC_PARM._stat_csc_compression)

#define parm__csc_bor_diag_en						(CSC_PARM._parm_csc_bor_diag_en)
#define parm__csc_report_fx2_idr_en					(CSC_PARM._parm_csc_report_fx2_idr_en)
#define parm__csc_report_fx2_nsr_en					(CSC_PARM._parm_csc_report_fx2_nsr_en)
#define parm__csc_report_fx2_rpr_en					(CSC_PARM._parm_csc_report_fx2_rpr_en)
#define parm__csc_report_fx2_tpr_en					(CSC_PARM._parm_csc_report_fx2_tpr_en)
#define parm__csc_adaptive_answer_en				(CSC_PARM._parm_csc_adaptive_answer_en)
#define parm__csc_fx2_fc_code						(CSC_PARM._parm_csc_fx2_fc_code)

#define stat__csc_hangup_code						(CSC_PARM._stat_csc_hangup_code)
#define stat__csc_hangup_code_en					(CSC_PARM._stat_csc_hangup_code_en)

#define parm__csc_bypass_reset_delay				(CSC_PARM._parm_csc_bypass_reset_delay)
#define parm__csc_bypass_post_cmd_delay				(CSC_PARM._parm_csc_bypass_post_cmd_delay)
#define parm__csc_reset_delay_duration				(CSC_PARM._parm_csc_reset_delay_duration)

#define parm__dte_char_detect_duration				(CSC_PARM._parm_dte_char_detect_duration)
#define parm__dte_char_detect_en					(CSC_PARM._parm_dte_char_detect_en)
#define stat__dte_char_seen							(CSC_PARM._stat_dte_char_seen)

#define parm__csc_fx1_faa_en						(CSC_PARM._parm_csc_fx1_faa_en)

#define parm__csc_telephony_active_mask				(CSC_PARM._parm_csc_telephony_active_mask)
#define parm__csc_itel_country_code					(CSC_PARM._parm_csc_itel_country_code)
#define parm__itel_country_code						(CSC_PARM._parm_itel_country_code)
#define parm__itel_cp_predial_mask					(CSC_PARM._parm_itel_cp_predial_mask)
#define parm__itel_cp_secondary_dial_mask			(CSC_PARM._parm_itel_cp_secondary_dial_mask)
#define parm__itel_cp_post_dial_mask				(CSC_PARM._parm_itel_cp_post_dial_mask)
#define parm__itel_pulse_make_time					(CSC_PARM._parm_itel_pulse_make_time)
#define parm__itel_pulse_break_time					(CSC_PARM._parm_itel_pulse_break_time)
#define parm__itel_pulse_post_digit_time			(CSC_PARM._parm_itel_pulse_post_digit_time)
#define parm__itel_dtmf_tone_on_time				(CSC_PARM._parm_itel_dtmf_tone_on_time)
#define parm__itel_dtmf_tone_off_time				(CSC_PARM._parm_itel_dtmf_tone_off_time)
#define parm__itel_dtmf_high_tone_level				(CSC_PARM._parm_itel_dtmf_high_tone_level)
#define parm__itel_dtmf_low_tone_level				(CSC_PARM._parm_itel_dtmf_low_tone_level)
#define parm__itel_max_transmit_level				(CSC_PARM._parm_itel_max_transmit_level)
#define parm__itel_min_receive_threshold			(CSC_PARM._parm_itel_min_receive_threshold)
#define parm__itel_carrier_loss_disconnect_duration	(CSC_PARM._parm_itel_carrier_loss_disconnect_duration)
#define parm__itel_dial_option_mask					(CSC_PARM._parm_itel_dial_option_mask)
#define parm__itel_dial_tone_criteria_duration		(CSC_PARM._parm_itel_dial_tone_criteria_duration)
#define parm__itel_dial_tone_wait_duration			(CSC_PARM._parm_itel_dial_tone_wait_duration)
#define parm__itel_post_dial_tone_pause_duration	(CSC_PARM._parm_itel_post_dial_tone_pause_duration)
#define parm__itel_blind_dial_wait_min				(CSC_PARM._parm_itel_blind_dial_wait_min)
#define parm__itel_blind_dial_wait_max				(CSC_PARM._parm_itel_blind_dial_wait_max)
#define parm__itel_dial_answer_wait_duration		(CSC_PARM._parm_itel_dial_answer_wait_duration)
#define parm__itel_ring_to_answer_min_duration		(CSC_PARM._parm_itel_ring_to_answer_min_duration)
#define parm__itel_ring_to_answer_max_duration		(CSC_PARM._parm_itel_ring_to_answer_max_duration)
#define parm__itel_ring_cnt_min						(CSC_PARM._parm_itel_ring_cnt_min)
#define parm__itel_ring_cnt_max						(CSC_PARM._parm_itel_ring_cnt_max)
#define parm__itel_max_delayed_dial_attempts		(CSC_PARM._parm_itel_max_delayed_dial_attempts)
#define parm__itel_delayed_dial_12_interval			(CSC_PARM._parm_itel_delayed_dial_12_interval)
#define parm__itel_delayed_dial_subsequent_interval	(CSC_PARM._parm_itel_delayed_dial_subsequent_interval)
#define parm__itel_delayed_reset_duration			(CSC_PARM._parm_itel_delayed_reset_duration)
#define parm__itel_codec_impedance					(CSC_PARM._parm_itel_codec_impedance)
#define parm__daa_itel_country_code					(CSC_PARM._parm__daa_itel_country_code)
#define parm__daa_itel_daa_reg16					(CSC_PARM._parm__daa_itel_daa_reg16)
#define parm__daa_itel_daa_reg26					(CSC_PARM._parm__daa_itel_daa_reg26)
#define parm__daa_itel_daa_reg30					(CSC_PARM._parm__daa_itel_daa_reg30)
#define parm__daa_itel_daa_reg31					(CSC_PARM._parm__daa_itel_daa_reg31)
#define parm__csc_spk_monitor_control				(CSC_PARM._parm_csc_spk_monitor_control)
#define parm__csc_spk_monitor_volume				(CSC_PARM._parm_csc_spk_monitor_volume)
#define parm__csc_online_retrain_request			(CSC_PARM._parm_csc_online_retrain_request)
#define stat__csc_dial_fail_reason					(CSC_PARM._stat_csc_dial_fail_reason)
#define stat__csc_omc_disconnect_reason				(CSC_PARM._stat_csc_omc_disconnect_reason)

/* ************************************************************************* */

#endif /* _CSC_PARMD_H */
