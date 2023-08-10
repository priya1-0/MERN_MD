
/* ************************************************************************* */
/*
 *	structs.h
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
 *	This file contains structure definitions for the CSC module.
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

#ifndef _CSC_STRUCTS_H
#define _CSC_STRUCTS_H

/* ************************************************************************* */

typedef struct {
	uint8	_itel_country_code;
	uint16	_itel_cp_predial_mask;
	uint16	_itel_cp_secondary_dial_mask;
	uint16	_itel_cp_post_dial_mask;
	uint8	_itel_pulse_make_time;
	uint8	_itel_pulse_break_time;
	uint16	_itel_pulse_post_digit_time;
	uint8	_itel_dtmf_tone_on_time;
	uint8	_itel_dtmf_tone_off_time;
	uint8	_itel_dtmf_high_tone_level;
	uint8	_itel_dtmf_low_tone_level;
	uint8	_itel_max_transmit_level;
	uint8	_itel_min_receive_threshold;
	uint8	_itel_carrier_loss_disconnect_duration;
	uint16	_itel_dial_option_mask;
	uint8	_itel_dial_tone_criteria_duration;
	uint8	_itel_dial_tone_wait_duration;
	uint8	_itel_post_dial_tone_pause_duration;
	uint8	_itel_blind_dial_wait_min;
	uint16	_itel_blind_dial_wait_max;
	uint8	_itel_dial_answer_wait_duration;
	uint8	_itel_ring_to_answer_min_duration;
	uint8	_itel_ring_to_answer_max_duration;
	uint8	_itel_ring_cnt_min;
	uint8	_itel_ring_cnt_max;
	uint8	_itel_max_delayed_dial_attempts;
	uint8	_itel_delayed_dial_12_interval;
	uint8	_itel_delayed_dial_subsequent_interval;
	uint16	_itel_delayed_reset_duration;
	uint8	_itel_codec_impedance;
} itel_entry_t;

extern itel_entry_t itel_table [];

typedef struct {
	uint8	_daa_itel_country_code;
	uint8	_daa_reg16;
	uint8	_daa_reg31;
	uint8	_daa_reg26;
	uint8	_daa_reg30;
} daa_itel_entry_t;
extern daa_itel_entry_t daa_itel_table [];

#endif /* _CSC_STRUCTS_H */
