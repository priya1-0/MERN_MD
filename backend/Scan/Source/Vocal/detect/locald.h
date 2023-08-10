
/* ************************************************************************* */
/*
 *	locald.h
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
 *	Module:		DETECT
 *
 *	This file contains the private parameter declarations/definitions
 *	for the DETECT module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 18:29:10  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _DETECT_LOCALD_H
#define _DETECT_LOCALD_H

/* ************************************************************************* */

typedef struct {
	uint8	_status;
	uint8	_state;
	uint8	_disconnect_reason;
	bool	_disconnect_request;

	uint16	_rx_data_unit;
	uint16	_tx_data_unit;
	uint8	_rx_data;

/* ************************************************************************* */
/*
 *  timer variables
 *
 */

	uint8	_timer_div;
	uint8	_timer_tick;
	uint8	_timer_tick2;

	uint8	_odp_attempt_timer;
	uint8	_adp_attempt_timer;
	uint8	_ar_attempt_timer;

	uint8	_odp_attempt_timer_exp;
	uint8	_adp_attempt_timer_exp;
	uint8	_ar_attempt_timer_exp;

/* ************************************************************************* */
/*
 *  originate only
 *
 */

	uint8	_odp_character_to_send;
	uint8	_adp_character_to_send;

/* ************************************************************************* */
/*
 *  number of odps or adps to receive before actual detection of such.
 *
 */

	uint8	_num_valid_adp_rx;
	uint8	_num_valid_odp_rx;

	uint8	_num_of_flags_rx;

	uint8	_num_of_char_rx;
	uint8	_num_of_ar_char_rx;

/* ************************************************************************* */
/*
 *  receive state machine variables
 *
 */

	uint8	_pre_lapm_state;
	uint8	_pre_mnp_state;

	uint8	_det_adp_state;
	uint16  _det_adp_lapm;
	uint16  _det_adp_mnp;
	uint16  _det_adp_buffered;

	uint8   _det_odp_state;
	uint16  _det_odp;

	uint8   _detected_odp;

	uint8   _exit_cnt;

	uint8   _result_code;

/* ************************************************************************* */
/*
 *    Autoreliable variables
 *
 */

	uint16	_ar_ch_cntr;
	uint16  _ar_ch_detect_cnt;

	uint8	_ar_timer_en;
	uint8	_ar_200_ch_en;
	uint8   _ar_char_en;

	uint8   _test_result_code;

	bool	_use_line_interrupts;

	bool	_detect_timer_en;
	bool	_flag_detect_en;
	bool    _det_adp_en;
	bool    _det_odp_en;
	bool	_trans_adp_en;
	bool	_trans_odp_en;
	bool	_pre_mnp_en;

	bool    _pre_mnp_detecting;

} detect_local_t;

/* ************************************************************************* */

#define DETECT_LOCAL_DATA detect_local_t detect_local
DEF_DATA(detect_local_t, detect_local)
#define DETECT_LOCAL USE_DATA(detect_local)

/* ************************************************************************* */

#define dp_detect_status					(DETECT_LOCAL._status)
#define detect_state						(DETECT_LOCAL._state)
#define detect_disconnect_reason			(DETECT_LOCAL._disconnect_reason)
#define detect_disconnect_request			(DETECT_LOCAL._disconnect_request)
#define detect_rx_data_unit					(DETECT_LOCAL._rx_data_unit)
#define detect_tx_data_unit					(DETECT_LOCAL._tx_data_unit)
#define detect_rx_data						(DETECT_LOCAL._rx_data)

/* *** Timer Variables *** */

#define detect_timer_div					(DETECT_LOCAL._timer_div)
#define detect_timer_tick					(DETECT_LOCAL._timer_tick)
#define detect_timer_tick2					(DETECT_LOCAL._timer_tick2)

#define detect_odp_attempt_timer			(DETECT_LOCAL._odp_attempt_timer)
#define detect_adp_attempt_timer			(DETECT_LOCAL._adp_attempt_timer)
#define detect_ar_attempt_timer				(DETECT_LOCAL._ar_attempt_timer)

#define detect_odp_attempt_timer_exp		(DETECT_LOCAL._odp_attempt_timer_exp)
#define detect_adp_attempt_timer_exp		(DETECT_LOCAL._adp_attempt_timer_exp)
#define detect_ar_attempt_timer_exp			(DETECT_LOCAL._ar_attempt_timer_exp)

#define detect_odp_character_to_send        (DETECT_LOCAL._odp_character_to_send)
#define detect_adp_character_to_send        (DETECT_LOCAL._adp_character_to_send)

#define detect_num_valid_adp_rx				(DETECT_LOCAL._num_valid_adp_rx)
#define detect_num_valid_odp_rx				(DETECT_LOCAL._num_valid_odp_rx)

#define detect_num_of_flags_rx				(DETECT_LOCAL._num_of_flags_rx)
#define detect_num_of_char_rx				(DETECT_LOCAL._num_of_char_rx)
#define detect_num_of_ar_char_rx			(DETECT_LOCAL._num_of_ar_char_rx)

#define detect_pre_lapm_state				(DETECT_LOCAL._pre_lapm_state)
#define detect_pre_mnp_state				(DETECT_LOCAL._pre_mnp_state)

#define detect_ar_ch_cntr					(DETECT_LOCAL._ar_ch_cntr)
#define detect_ar_ch_detect_cnt				(DETECT_LOCAL._ar_ch_detect_cnt)

#define detect_det_adp_state				(DETECT_LOCAL._det_adp_state)
#define detect_det_adp_lapm					(DETECT_LOCAL._det_adp_lapm)
#define detect_det_adp_mnp					(DETECT_LOCAL._det_adp_mnp)
#define detect_det_adp_buffered				(DETECT_LOCAL._det_adp_buffered)

#define detect_det_odp_state				(DETECT_LOCAL._det_odp_state)
#define detect_det_odp						(DETECT_LOCAL._det_odp)

#define detect_detected_odp					(DETECT_LOCAL._detected_odp)
#define detect_exit_cnt						(DETECT_LOCAL._exit_cnt)

#define detect_ar_timer_en					(DETECT_LOCAL._ar_timer_en)
#define detect_ar_200_ch_en					(DETECT_LOCAL._ar_200_ch_en)
#define detect_ar_char_en					(DETECT_LOCAL._ar_char_en)

#define detect_result_code					(DETECT_LOCAL._result_code)

#define detect_test_result_code				(DETECT_LOCAL._test_result_code)

#define detect_use_line_interrupts			(DETECT_LOCAL._use_line_interrupts)

#define detect_detect_timer_en				(DETECT_LOCAL._detect_timer_en)
#define detect_flag_detect_en				(DETECT_LOCAL._flag_detect_en)
#define detect_det_adp_en					(DETECT_LOCAL._det_adp_en)
#define detect_det_odp_en					(DETECT_LOCAL._det_odp_en)
#define detect_trans_adp_en					(DETECT_LOCAL._trans_adp_en)
#define detect_trans_odp_en					(DETECT_LOCAL._trans_odp_en)
#define detect_pre_mnp_en					(DETECT_LOCAL._pre_mnp_en)

#define detect_pre_mnp_detecting			(DETECT_LOCAL._pre_mnp_detecting)

/* ************************************************************************* */

#endif /* _DETECT_LOCALD_H */
