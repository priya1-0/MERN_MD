
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
 *	Module:		BUFFERED
 *
 *	This file contains the private parameter declarations/definitions
 *	for the BUFFERED module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 18:27:31  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _BUFFERED_LOCALD_H
#define _BUFFERED_LOCALD_H

/* ************************************************************************* */

#include "buffered/config.h"

/* ************************************************************************* */

typedef struct {
	/* Buffer Related Parameters */
	uint16	_rx_buffer [BUFFERED_RX_BUFFER_SIZE];
	uint16	_tx_buffer [BUFFERED_TX_BUFFER_SIZE];
	uint16	*_rx_inp;
	uint16	*_rx_outp;
	uint16	_rx_cnt;
	uint16	*_tx_inp;
	uint16	*_tx_outp;
	uint16	_tx_cnt;

	/* Pseudo parameters */
	uint16	_break_mode;
	uint16	_flow_control_mode;
	uint16	_xon_xoff_mask;
	uint16	_xon_char;
	uint16	_xoff_char;
	uint16	_prev_flow_control_mode;

	/* Miscellaneous control variables */
	uint8	_status;					/* DP_STATUS__xxx					*/
	uint8	_state;						/* BUFFERED_STATE__xxx				*/
	bool	_idle_flag;					/* TRUE if within idle				*/
	bool	_suspend_flag;				/* TRUE if within suspend			*/
	bool	_disconnect_flag;			/* TRUE if disconnect commanded		*/

	/* Timer variables */
	uint16	_timer_100ms_tick;			/* BG uses this as 100 ms tick cnt	*/
	uint16	_timer_100ms_div;			/* Used to divide 100 ms to get 1 s	*/

	/* Variables related to breaks */
	bool	_within_rx_break;
	bool	_tx_break_expedited;

	/* Variables related to LSD */
	uint16	_tx_lsd_tmr;
	bool	_tx_start_lsd;
	bool	_tx_within_lsd;

	/* Variables related to xon/xoff */
	bool	_tx_xoff_request_pending;
	bool	_tx_xon_request_pending;
	bool	_tx_xoff_was_sent;
	bool	_rx_xoff_was_rcvd;

	/* Info variables */
	uint8	_stop_mode;

} buffered_local_t;

/* ************************************************************************* */

#define BUFFERED_LOCAL_DATA buffered_local_t buffered_local
DEF_DATA(buffered_local_t, buffered_local)
#define BUFFERED_LOCAL USE_DATA(buffered_local)

/* ************************************************************************* */

#define buffered_rx_buffer						(BUFFERED_LOCAL._rx_buffer)
#define buffered_tx_buffer						(BUFFERED_LOCAL._tx_buffer)

#define buffered_rx_inp							(BUFFERED_LOCAL._rx_inp)
#define buffered_rx_outp						(BUFFERED_LOCAL._rx_outp)
#define buffered_rx_cnt							(BUFFERED_LOCAL._rx_cnt)
#define buffered_tx_inp							(BUFFERED_LOCAL._tx_inp)
#define buffered_tx_outp						(BUFFERED_LOCAL._tx_outp)
#define buffered_tx_cnt							(BUFFERED_LOCAL._tx_cnt)
#define buffered_break_mode						(BUFFERED_LOCAL._break_mode)
#define buffered_flow_control_mode				(BUFFERED_LOCAL._flow_control_mode)
#define buffered_xon_xoff_mask					(BUFFERED_LOCAL._xon_xoff_mask)
#define buffered_xon_char						(BUFFERED_LOCAL._xon_char)
#define buffered_xoff_char						(BUFFERED_LOCAL._xoff_char)
#define buffered_prev_flow_control_mode			(BUFFERED_LOCAL._prev_flow_control_mode)
#define buffered_status							(BUFFERED_LOCAL._status)
#define buffered_state							(BUFFERED_LOCAL._state)
#define buffered_idle_flag						(BUFFERED_LOCAL._idle_flag)
#define buffered_suspend_flag					(BUFFERED_LOCAL._suspend_flag)
#define buffered_disconnect_flag				(BUFFERED_LOCAL._disconnect_flag)
#define buffered_timer_100ms_tick				(BUFFERED_LOCAL._timer_100ms_tick)
#define buffered_timer_100ms_div				(BUFFERED_LOCAL._timer_100ms_div)
#define buffered_within_rx_break				(BUFFERED_LOCAL._within_rx_break)
#define buffered_tx_break_expedited				(BUFFERED_LOCAL._tx_break_expedited)
#define buffered_tx_lsd_tmr						(BUFFERED_LOCAL._tx_lsd_tmr)
#define buffered_tx_start_lsd					(BUFFERED_LOCAL._tx_start_lsd)
#define buffered_tx_within_lsd					(BUFFERED_LOCAL._tx_within_lsd)
#define buffered_tx_xoff_request_pending		(BUFFERED_LOCAL._tx_xoff_request_pending)
#define buffered_tx_xon_request_pending			(BUFFERED_LOCAL._tx_xon_request_pending)
#define buffered_tx_xoff_was_sent				(BUFFERED_LOCAL._tx_xoff_was_sent)
#define buffered_rx_xoff_was_rcvd				(BUFFERED_LOCAL._rx_xoff_was_rcvd)
#define buffered_stop_mode						(BUFFERED_LOCAL._stop_mode)

/* ************************************************************************* */

#endif /* _BUFFERED_LOCALD_H */
