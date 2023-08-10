
/* ************************************************************************* */
/*
 *	itel.c
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
 *	This file contains international telephony related routines.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.4  2010/02/16 22:12:20  zhangn1
 *	Revision History:	SCR #186247. Incorporate South Africa Tx Tone
 *	Revision History:	
 *	Revision History:	Revision 1.1.6.3  2010/02/16 17:46:58  zhangn1
 *	Revision History:	SCR #185921. Fix Malta dial tone and South Korea Reg 59 issues.
 *	Revision History:	
 *	Revision History:	Revision 1.1.6.2  2009/04/28 19:06:28  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#include "system/system.h"

#include "csc/local.h"
#include "csc/structs.h"
#include "bind/bind.h"
#include "omc/parmd.h"
#include "csp/csp.h"
#include "omc/omc.h"
#include "include/silabs.h"
#include "csc/silabd.h"
#include "pump/pump.h"
#include "general/general.h"

#define NOMINAL_TONE_DBM__DTMF_LOW						 (-9)	/* -9.0 dBm */
#define NOMINAL_TONE_DBM__DTMF_HIGH						 (-7)	/* -7.0 dBm */
/* ************************************************************************* */

/*
************************************************************************* */
/*
 *    Local Routine: convert_dB_to_linear
 *
 *  Converts an input linear DB value(level_dB) to a fixed point representation
 *  based on the nominal values of linear and fixed point mode.
 *
 *
 *    Parameters:
 *        level_dB ,nominal_linear, nominal_dB
 *
 *    Returns:
 *        (fract) linear_value
 */
ENTRY fract 
convert_dB_to_linear (sint15 level_dB, ufract nominal_linear, sint15 nominal_dB)
{
	fract32 level32;
	fract adjust;
	uint32 temp32;
	int count;

	// construct the nominal level in 2.30 format
	//printf("convert_db %3d %04hx %3d\n", level_dB, nominal_linear, nominal_dB);
	temp32 = UINTTRUNC(nominal_linear);
	temp32 = temp32 << 15;
	level32 = LFRACTL(temp32);

	adjust = FRACT (18383);		// +1 dB gain multiplier, 2.14 format
	count = -nominal_dB + level_dB;
	if (level_dB < nominal_dB) {
		count = -level_dB + nominal_dB;
		adjust = FRACT (14602);	// -1 dB gain multiplier, 2.14 format
	}
	//printf("  adjust %04hx ct %3d\n", adjust, count);

	while (count--) {
		level32 = LMMSSLS(level32, adjust);
		level32 = LSHIFTL(level32, 1);	// adjusted gain, 2.14 format
		if (level32 >= LFRACT(0x4000)) {
			// Maximum gain
			//printf("  final 7fff\n");
			return S1;
		}
		//printf("  ct %3d %04hx\n", count, FORMATL(level32));
	}

	level32 = LSHIFTL(level32, 1);	// adjusted gain, 1.15 format
	//printf("  final %04hx\n", FORMATL(level32));
	return FORMATL(level32);
}

/* ************************************************************************* */
/*
 *	Entry Routine: itel_set
 *
 *	This routine is used to select international telephony country code.
 *
 *	Parameters:
 *		"code" is the country code, one of ICC__xxx.
 *
 *	Returns:
 *		TRUE if error occurred.
 */

ENTRY bool
itel_set (uint16 code)
{
	uint16 i;
	uint16 return_flag = TRUE;

	for (i = 0; i < ITEL_COUNTRY_ENTRY_MAX; i++) {
		if (code == itel_table [i]._itel_country_code) {
			fg_print_debug_off(("itel_set %d\n",code));
			parm__itel_country_code = code;
			parm__itel_cp_predial_mask = itel_table [i]._itel_cp_predial_mask;
			parm__itel_cp_secondary_dial_mask = itel_table [i]._itel_cp_secondary_dial_mask;
			parm__itel_cp_post_dial_mask = itel_table [i]._itel_cp_post_dial_mask;
			parm__itel_pulse_make_time = itel_table [i]._itel_pulse_make_time;
			parm__itel_pulse_break_time = itel_table [i]._itel_pulse_break_time;
			parm__itel_pulse_post_digit_time = itel_table [i]._itel_pulse_post_digit_time;
			parm__itel_dtmf_tone_on_time = itel_table [i]._itel_dtmf_tone_on_time;
			parm__itel_dtmf_tone_off_time = itel_table [i]._itel_dtmf_tone_off_time;
			parm__itel_dtmf_high_tone_level = itel_table [i]._itel_dtmf_high_tone_level;
			parm__itel_dtmf_low_tone_level = itel_table [i]._itel_dtmf_low_tone_level;
			parm__itel_max_transmit_level = itel_table [i]._itel_max_transmit_level;
			parm__itel_min_receive_threshold = itel_table [i]._itel_min_receive_threshold;
			parm__itel_carrier_loss_disconnect_duration = itel_table [i]._itel_carrier_loss_disconnect_duration;
			parm__itel_dial_option_mask = itel_table [i]._itel_dial_option_mask;
			parm__itel_dial_tone_criteria_duration = itel_table [i]._itel_dial_tone_criteria_duration;
			parm__itel_dial_tone_wait_duration = itel_table [i]._itel_dial_tone_wait_duration;
			parm__itel_post_dial_tone_pause_duration = itel_table [i]._itel_post_dial_tone_pause_duration;
			parm__itel_blind_dial_wait_min = itel_table [i]._itel_blind_dial_wait_min;
			parm__itel_blind_dial_wait_max = itel_table [i]._itel_blind_dial_wait_max;
			parm__itel_dial_answer_wait_duration = itel_table [i]._itel_dial_answer_wait_duration;
			parm__itel_ring_to_answer_min_duration = itel_table [i]._itel_ring_to_answer_min_duration;
			parm__itel_ring_to_answer_max_duration = itel_table [i]._itel_ring_to_answer_max_duration;
			parm__itel_ring_cnt_min = itel_table [i]._itel_ring_cnt_min;
			parm__itel_ring_cnt_max = itel_table [i]._itel_ring_cnt_max;
			parm__itel_max_delayed_dial_attempts = itel_table [i]._itel_max_delayed_dial_attempts;
			parm__itel_delayed_dial_12_interval = itel_table [i]._itel_delayed_dial_12_interval;
			parm__itel_delayed_dial_subsequent_interval = itel_table [i]._itel_delayed_dial_subsequent_interval;
			parm__itel_delayed_reset_duration = itel_table [i]._itel_delayed_reset_duration;
			parm__itel_codec_impedance = itel_table [i]._itel_codec_impedance;
			return_flag = FALSE;
			break;
		}
	}
	if (return_flag) {
		return TRUE;
	} else {
		return_flag = TRUE;
	}

	for (i = 0; i < DAA_ITEL_COUNTRY_ENTRY_MAX; i++) {
		if (code == daa_itel_table [i]._daa_itel_country_code) {
			parm__daa_itel_country_code = code;
			debug_log1(parm__daa_itel_country_code);
			parm__daa_itel_daa_reg16 = daa_itel_table [i]._daa_reg16;
			debug_log1(parm__daa_itel_daa_reg16);
			parm__daa_itel_daa_reg26 = daa_itel_table [i]._daa_reg26;
			debug_log1(parm__daa_itel_daa_reg26);
			parm__daa_itel_daa_reg30 = daa_itel_table [i]._daa_reg30;
			debug_log1(parm__daa_itel_daa_reg30);
			parm__daa_itel_daa_reg31 = daa_itel_table [i]._daa_reg31;
			debug_log1(parm__daa_itel_daa_reg31);
			return_flag = FALSE;
			break;
		}
	}

	return return_flag;

}

/* ************************************************************************* */
/*
 *	Module Routine: itel_bind
 *
 *	This routine is used to bind the itel configuration with various omc
 *	and pump layer parameters.
 *
 *	Parameters:
 *		none
 *
 *	Returns:
 *		none
 */

ENTRY void
itel_bind (void)
{
	uint16 temp_uint16;
        fract ftemp;

	fg_print_debug_off(("itel_bind %d\n",parm__itel_country_code));
	access_csc_omc_dm_wr_direct (parm__dial_itel_cp_predial_mask,
		parm__itel_cp_predial_mask);

	access_csc_omc_dm_wr_direct (parm__dial_itel_cp_secondary_dial_mask,
		parm__itel_cp_secondary_dial_mask);

	access_csc_omc_dm_wr_direct (parm__dial_itel_cp_post_dial_mask,
		parm__itel_cp_post_dial_mask);

	access_csc_pump_dm_wr_direct (parm__pulse_make_time,
		parm__itel_pulse_make_time);

	access_csc_pump_dm_wr_direct (parm__pulse_break_time,
		parm__itel_pulse_break_time);

	access_csc_pump_dm_wr_direct (parm__pulse_delay_time,
		parm__itel_pulse_post_digit_time);

	access_csc_pump_dm_wr_direct (parm__dtmf_tone_on_time,
		parm__itel_dtmf_tone_on_time);

	access_csc_pump_dm_wr_direct (parm__dtmf_tone_off_time,
		parm__itel_dtmf_tone_off_time);

	/* Convert the nominal settings as provided in include/const.h to the desired country specific setting */
	ftemp = convert_dB_to_linear (-parm__itel_dtmf_high_tone_level, NOMINAL_TONE_LEVEL__DTMF_HIGH, NOMINAL_TONE_DBM__DTMF_HIGH);
	access_csc_pump_dm_wr_direct (parm__dtmf_high_tone_level, ftemp);
	ftemp = convert_dB_to_linear (-parm__itel_dtmf_low_tone_level, NOMINAL_TONE_LEVEL__DTMF_LOW, NOMINAL_TONE_DBM__DTMF_LOW);
	access_csc_pump_dm_wr_direct (parm__dtmf_low_tone_level, ftemp);


	access_csc_pump_dm_wr_direct (parm__dm_carrier_loss_disconnect_duration,
		parm__itel_carrier_loss_disconnect_duration);

	access_csc_omc_dm_wr_direct (parm__dial_itel_dial_option_mask,
		parm__itel_dial_option_mask);

	temp_uint16 = csstd__sreg_s06 * 100;
	if (temp_uint16 < 400) {
		temp_uint16 = 400;
	}
	access_csc_omc_dm_wr_direct (parm__dial_dial_tone_wait_duration, temp_uint16);

	temp_uint16 = parm__itel_dial_tone_wait_duration;
	if (temp_uint16 < 150) {
		temp_uint16 = 150;
	}
	temp_uint16 *= 10;
	access_csc_omc_dm_wr_direct (parm__dial_dial_tone_abort_duration, temp_uint16);

	temp_uint16 = parm__itel_post_dial_tone_pause_duration;
	temp_uint16 *= 10;
	access_csc_omc_dm_wr_direct (parm__dial_post_dt_pause_duration, temp_uint16);

	if (parm__itel_blind_dial_wait_min == 0) {
		access_csc_omc_dm_wr_direct (parm__dial_dial_tone_det_en, TRUE);
		/* parm__dial_blind_dial_wait_duration is don't care in this case. */
		temp_uint16 = parm__itel_blind_dial_wait_min;
		access_csc_omc_dm_wr_direct (parm__dial_blind_dial_wait_duration, temp_uint16);
	}
	else {
		/*	dial_bind () has already configured parm__dial_dial_tone_det_en
			according to the value of the Xn command. */
		temp_uint16 = csstd__sreg_s06 * 10;
		if (temp_uint16 < parm__itel_blind_dial_wait_min) {
			temp_uint16 = parm__itel_blind_dial_wait_min;
		}
		if (temp_uint16 > parm__itel_blind_dial_wait_max) {
			temp_uint16 = parm__itel_blind_dial_wait_max;
		}
		temp_uint16 *= 10;
		access_csc_omc_dm_wr_direct (parm__dial_blind_dial_wait_duration, temp_uint16);
	}

	access_csc_omc_dm_wr_direct (parm__dial_answer_wait_duration, parm__itel_dial_answer_wait_duration);

	parm__csc_ring_to_answer_min_duration = parm__itel_ring_to_answer_min_duration;
	parm__csc_ring_to_answer_max_duration = parm__itel_ring_to_answer_max_duration;
	if (parm__itel_ring_cnt_min > csstd__sreg_s00) {
		if (csstd__sreg_s00 != 0) {
			parm__csc_autoanswer_ring_cnt = parm__itel_ring_cnt_min;
		}
	}
	parm__csc_ring_cnt_max = parm__itel_ring_cnt_max;

/*
 * DAA_DAAControl4 => reg31
 * DAA_DCtermCtl   => reg26
 * DAA_INcontrol1  => reg16
 * DAA_ACterm      => reg30
 */
{
/*
Register 25. Resistor Calibration
Bit		D7		D6		D5		D4		D3		D2		D1		D0
Name   ACT2    OHS      ACT    IIRE     -       -       RZ      RT
*/
#define DAA_ITEL_MASK_REG25   0x20

/*
Register 59. Spark Quenching Control
Bit		D7		D6		D5		D4		D3		D2		D1		D0
Name   ACT2    OHS      ACT    IIRE     -       -       RZ      RT
*/
#define DAA_SprkQunch  59
#define DAA_ITEL_MASK_REG59   0x50

#define AUS__OHS	1
#define AUS__OHS2	1
#define AUS__SQ0	1
#define AUS__SQ1	1
#define AUS__RCALD2	1

	if (parm__itel_country_code == ICC__AUSTRALIA) {
		parm__daa_itel_daa_reg16 |= (AUS__OHS  << 6);
		parm__daa_itel_daa_reg31 |= (AUS__OHS2 << 3);

		/* Register 25. Resistor Calibration */
		temp_uint16 = codec_process_control_word (0x8000 | (DAA_ResistorCal << 8));
		temp_uint16 &= ~DAA_ITEL_MASK_REG25;
		temp_uint16 |= (AUS__RCALD2 << 5);
		codec_process_control_word ((DAA_ResistorCal << 8) | temp_uint16);

		/* Register 59. Spark Quenching Control	*/
		temp_uint16 = codec_process_control_word (0x8000 | (DAA_SprkQunch << 8));
		temp_uint16 &= ~DAA_ITEL_MASK_REG59;
		temp_uint16 |= ((AUS__SQ0  << 4) | (AUS__SQ1  << 6));
		codec_process_control_word ((DAA_SprkQunch << 8) | temp_uint16);

	}

	/* Korean ringer impedance synthesis requires the TB3 and RZ bits */
	/* RZ is already set via the table in register 16 */
#define KOR__TB3	1
	
	if (parm__itel_country_code == ICC__KOREA) {
		/* Register 59. Spark Quenching Control	*/
		temp_uint16 = codec_process_control_word (0x8000 | (DAA_SprkQunch << 8));
		temp_uint16 |= (KOR__TB3 << 7);
		codec_process_control_word ((DAA_SprkQunch << 8) | temp_uint16);
	}
}

/*
 * DAA_DAAControl4 => reg31
 * DAA_DCtermCtl   => reg26
 * DAA_INcontrol1  => reg16
 * DAA_ACterm      => reg30
 */
/* Register 16. International Control 1	*/
	temp_uint16 = codec_process_control_word (0x8000 | (DAA_INcontrol1 << 8));
	temp_uint16 &= ~DAA_ITEL_MASK_REG16;
	temp_uint16 |= parm__daa_itel_daa_reg16;
	codec_process_control_word ((DAA_INcontrol1 << 8) | temp_uint16);
/* Register 31. DAA Control 4 */
	temp_uint16 = codec_process_control_word (0x8000 | (DAA_DAAControl4 << 8));
	temp_uint16 &= ~DAA_ITEL_MASK_REG31;
	temp_uint16 |= parm__daa_itel_daa_reg31;
	codec_process_control_word ((DAA_DAAControl4 << 8) | temp_uint16);

/* Register 26. DC Termination Control */
	temp_uint16 = codec_process_control_word (0x8000 | (DAA_DCtermCtl << 8));
	temp_uint16 &= ~DAA_ITEL_MASK_REG26;
	temp_uint16 |= parm__daa_itel_daa_reg26;
	codec_process_control_word ((DAA_DCtermCtl << 8) | temp_uint16);

/* Register 30. AC Termination Control */
	temp_uint16 = codec_process_control_word (0x8000 | (DAA_ACterm << 8));
	temp_uint16 &= ~DAA_ITEL_MASK_REG30;
	temp_uint16 |= parm__daa_itel_daa_reg30;
	codec_process_control_word ((DAA_ACterm << 8) | temp_uint16);

}

/* ************************************************************************* */
/*
 *	Module Routine: itel_csc_bind
 *
 *	This routine is used to bind the itel configuration with various csc
 *	layer parameters.
 *
 *	Parameters:
 *		none
 *
 *	Returns:
 *		none
 */

MODULE void
itel_csc_bind (void)
{
}

/* ************************************************************************* */
