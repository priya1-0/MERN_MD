
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
 *	Module:		LAPM
 *
 *	This file contains the private parameter declarations/definitions
 *	for the LAPM module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 19:57:11  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _LAPM_LOCALD_H
#define _LAPM_LOCALD_H

/* ************************************************************************* */

#include "lapm/config.h"
#include "lapm/types.h"

/* ************************************************************************* */

typedef struct {

/* ************************************************************************* */
	/*
	 * physical allocation of transmit and receive frame space
	 *
	 */

	lapm_tx_frame_t			_tx_buffer [LAPM_NUMBER_TX_BUFFERS];
	lapm_rx_frame_t			_rx_buffer [LAPM_NUMBER_RX_BUFFERS];
	lapm_ctl_frame_t		_control_buffer [LAPM_NUMBER_CTL_BUFFERS];
	lapm_break_frame_t		_break_segment;
	lapm_xid_frame_t		_xid_segment;
	lapm_test_frame_t		_test_segment;

	/*
	 * transmit and receive lower level pointers
	 *
	 */

	lapm_tx_frame_t *_tx_holding_framep;
	lapm_tx_frame_t *_tx_current_framep;
	lapm_tx_frame_t *_tx_sent_framep;
	lapm_tx_frame_t *_tx_sent2_framep;
	lapm_tx_frame_t *_tx_sent3_framep;

	lapm_rx_frame_t *_receive_active_frame;

/* ************************************************************************* */
	/*
	 * working event variables
	 *
	 */

	lapm_event_t _event_buffer [LAPM_NUMBER_OF_EVENTS];

	lapm_event_t *_eventp;
	lapm_rx_frame_t *_event_rx_framep;

	void (*_func)(void);
	lapm_event_t _local_event;
	lapm_state_t _state;

/* ************************************************************************* */
	/*
	 * linked list maintenance allocation
	 *
	 */

	lapm_list_t _control_list;
	lapm_list_t _tx_list;
	lapm_list_t _tx_ack_list;
	lapm_list_t _event_list;
	lapm_list_t _rx_list;
	lapm_list_t _rx_hold_list;
	lapm_list_t _rx_temp_list;

/* ************************************************************************* */
	/*
	 * buffer based queues and pointers
	 *
	 */

	uint8	_rx_queue_in;
	uint8	_rx_queue_out;
	lapm_rx_frame_t  *_rx_queue [LAPM_NUMBER_RX_BUFFERS+1];

	uint8	_empty_queue_in;
	uint8	_empty_queue_out;
	lapm_rx_frame_t  *_empty_queue [LAPM_NUMBER_RX_BUFFERS+1];

	uint8	_tx_queue_in;
	uint8	_tx_queue_out;
	uint8	_tx_ack_queue_in;
	uint8	_tx_ack_queue_out;
	lapm_tx_frame_t *_tx_queue [LAPM_NUMBER_TX_BUFFERS+1];

	uint8	_srej_queue_in;
	uint8	_srej_queue_out;
	lapm_tx_frame_t *_srej_queue [LAPM_NUMBER_TX_BUFFERS+1];

/* ************************************************************************* */
	/*
	 * variables containing negotiable parameters
	 *
	 */

	lapm_negotiation_parameters_t _negotiated_parms;
	lapm_negotiation_parameters_t _required_parms;

/* ************************************************************************* */
	/*
	 * v.42 general purpose working variables
	 *
	 */

	uint16	_k;							/* current value of lapm_k */
	uint8	_local_va;					/* local va */
	uint8	_local_break_vr;			/* local break vr */
	uint8	_local_vr;					/* local vr */
	uint8	_local_break_vs;			/* local break vs */
	uint8	_local_vs;					/* local vs */
	uint8	_remote_nr;					/* remote nr */
	uint8	_remote_ns;					/* remote ns */
	uint8	_remote_break_vr;			/* remote break vr */

	bool	_local_busy;				/* local busy */
	bool	_remote_busy;				/* remote busy */

	uint8	_local_addr;				/* local address */
	uint8	_remote_addr;				/* remote address */

	uint16	_n400_limit;				/* reload value for n400 */
	uint16	_t401_limit;				/* reload value for n401 */
	uint16	_t403_limit;				/* reload value for n403 */
	uint16	_100ms_limit;				/* reload value for misc init timer */
	uint16	_inactivity_limit;			/* reload value for inactivity timer */

	uint8	_timer_tick;				/* 100ms timer */
	uint8	_timer_1s;					/* 1s timer */
	uint8   _timer_1_3s;				/* 1/3s timer */

	uint16	_n400;						/* current n400 count */
	uint16	_timer_array [LAPM_NUMBER_OF_TIMERS];

/* ************************************************************************* */
	/*
	 * frame reject information fields
	 *
	 */

	frmr_t	_FRMR_values;				/* reject frame information */

/* ************************************************************************* */
	/*
	 * lapm test values
	 *
	 */

	uint8	*_test_datap;				/* test pointer */
	uint16	_test_results;				/* test results */

/* ************************************************************************* */
	/*
	 * local "routine" working variables
	 *
	 */

	lapm_tx_frame_t *_tx_ctl_framep;	/* lapmctl.c */
	lapm_ctl_frame_t  *_ctl_framep;		/* lapmctl.c */

	lapm_rx_frame_t *_rx_continue_framep;	/* lapmrx.c */
	lapm_rx_frame_t *_rx_bg_framep;		/* lapmbg.c */
	lapm_rx_frame_t *_rx_fg_framep;		/* lapmfg.c */

	uint8	_fg_cmd;					/* lapmfg.c */
	uint8	_fg_size;					/* lapmfg.c */

/* ************************************************************************* */
	/*
	 * local data transmit and receive working variables
	 *
	 */

	bool	_tx_buffer_pending;			/* tx char in buffer */
	bool	_rx_buffer_pending;			/* rx frame is being delivered */

	uint8	_rx_empty_count;			/* number of bytes pending in rx frame */
	uint8	_rx_next_frame_number;		/* the next frame to deliver */

/* ************************************************************************* */
	/*
	 * local xid building and parsing working variables
	 *
	 */

	bool	_xid_include_btlz;			/* flag used when building xid */
	uint8	_xid_btlz_length;			/* length used when building xid */
	uint16	_xid_length;				/* total length of building xid */
	uint8	_xid_build_bfr [4];		 	/* building xid storage */
	uint8	_xid_parse_bfr [4];		 	/* parsing xid storage */
	pack8	*_tx_xid_resyncp;			/* resynce for extended xid */

/* ************************************************************************* */
	/*
	 * break variables
	 *
	 */

	bool	_tx_break_pending;			/* transmit dte break is pending */
	bool	_tx_break_sequenced;		/* break frame is pending */
	bool	_dte_break_pending;			/* lapm receive break pending */

	uint16	_dte_chars_before_break;	/* number dte chars till tx frame break */
	uint8	_break_length;				/* working tx break length */
	uint8	_break_length_default;  	/* parameter default break length */
	uint8	_break_type;				/* working tx break type */
	uint8	_rx_break_type;				/* working rx break type */
	uint8	_rx_break_length;			/* working rx break length */

/* ************************************************************************* */
	/*
	 * general lapm variables
	 *
	 */

	bool	_poll_active;				/* lapm is being polled */
	umod8	_sequence_number;			/* 0 - 255: next lapm sequence number */

	bool	_disconnect_active;			/* lapm is disconnecting */
	bool	_idle_flag;					/* lapm is idle */
	bool    _suspend_timers;			/* suspend timers when going into suspend and idle */
	bool	_suspend_flag;				/* lapm is suspended */
	bool	_reconfigure_active;

	bool	_rx_I_frame_discarded;		/* lapm I frame has been discarded */
	bool	_reject_active;				/* lapm reject frame pending */
	bool	_test_active;				/* lapm test frame pending */
	bool	_xid_active;				/* lapm xid frame pending */
	bool	_rx_xid_sync;				/* lapm xid rx active */
	uint8	_status;					/* lapm running status */
	uint16	_tx_test_frame;				/* lapm test frame count */

/* ************************************************************************* */
	/*
	 * receive frame statistics variables
	 *
	 */

	sint31	_rx_bad_frame_count;
	sint31	_rx_frame_count;
	sint31	_rx_long_frame_count;
	sint31	_rx_short_frame_count;

/* ************************************************************************* */
	/*
	 * info variables
	 *
	 */

	uint8	_line_type;					/* LINE_TYPE__xxx */
	uint8	_compression_used;			/* COMPRESSION__xxx */
	uint8	_error_count;
	uint16	_current_block_size;
	uint8	_stop_mode;					/* STOP_MODE__xxx */

	bool	_suspend_trying_to_connect;

	bool	_ua_just_sent;

	bool	_first_xid;
} lapm_local_t;

/* ************************************************************************* */

#define LAPM_LOCAL_DATA lapm_local_t lapm_local
DEF_DATA(lapm_local_t, lapm_local)
#define LAPM_LOCAL USE_DATA(lapm_local)

/* ************************************************************************* */

#define lapm_tx_buffer						(LAPM_LOCAL._tx_buffer)
#define lapm_rx_buffer						(LAPM_LOCAL._rx_buffer)
#define lapm_control_buffer					(LAPM_LOCAL._control_buffer)
#define lapm_break_segment					(LAPM_LOCAL._break_segment)
#define lapm_xid_segment					(LAPM_LOCAL._xid_segment)
#define lapm_test_segment					(LAPM_LOCAL._test_segment)

#define lapm_tx_holding_framep				(LAPM_LOCAL._tx_holding_framep)
#define lapm_tx_current_framep				(LAPM_LOCAL._tx_current_framep)
#define lapm_tx_sent_framep					(LAPM_LOCAL._tx_sent_framep)
#define lapm_tx_sent2_framep				(LAPM_LOCAL._tx_sent2_framep)
#define lapm_tx_sent3_framep				(LAPM_LOCAL._tx_sent3_framep)

#define receive_active_frame				(LAPM_LOCAL._receive_active_frame)

#define lapm_event_buffer					(LAPM_LOCAL._event_buffer)

#define lapm_eventp							(LAPM_LOCAL._eventp)
#define lapm_event_rx_framep				(LAPM_LOCAL._event_rx_framep)

#define lapm_func							(LAPM_LOCAL._func)
#define lapm_local_event					(LAPM_LOCAL._local_event)
#define lapm_state							(LAPM_LOCAL._state)

#define lapm_control_list					(LAPM_LOCAL._control_list)
#define lapm_tx_list						(LAPM_LOCAL._tx_list)
#define lapm_tx_ack_list					(LAPM_LOCAL._tx_ack_list)
#define lapm_event_list						(LAPM_LOCAL._event_list)
#define lapm_rx_list						(LAPM_LOCAL._rx_list)
#define lapm_rx_hold_list					(LAPM_LOCAL._rx_hold_list)
#define lapm_rx_temp_list					(LAPM_LOCAL._rx_temp_list)

#define lapm_rx_queue_in					(LAPM_LOCAL._rx_queue_in)
#define lapm_rx_queue_out					(LAPM_LOCAL._rx_queue_out)
#define lapm_rx_queue						(LAPM_LOCAL._rx_queue)

#define lapm_empty_queue_in					(LAPM_LOCAL._empty_queue_in)
#define lapm_empty_queue_out				(LAPM_LOCAL._empty_queue_out)
#define lapm_empty_queue					(LAPM_LOCAL._empty_queue)

#define lapm_tx_queue_in					(LAPM_LOCAL._tx_queue_in)
#define lapm_tx_queue_out					(LAPM_LOCAL._tx_queue_out)
#define lapm_tx_ack_queue_in				(LAPM_LOCAL._tx_ack_queue_in)
#define lapm_tx_ack_queue_out				(LAPM_LOCAL._tx_ack_queue_out)
#define lapm_tx_queue						(LAPM_LOCAL._tx_queue)

#define lapm_srej_queue_in					(LAPM_LOCAL._srej_queue_in)
#define lapm_srej_queue_out					(LAPM_LOCAL._srej_queue_out)
#define lapm_srej_queue						(LAPM_LOCAL._srej_queue)

#define lapm_negotiated_parms				(LAPM_LOCAL._negotiated_parms)
#define lapm_required_parms					(LAPM_LOCAL._required_parms)

#define lapm_k								(LAPM_LOCAL._k)
#define lapm_local_va						(LAPM_LOCAL._local_va)
#define lapm_local_break_vr					(LAPM_LOCAL._local_break_vr)
#define lapm_local_vr						(LAPM_LOCAL._local_vr)
#define lapm_local_break_vs					(LAPM_LOCAL._local_break_vs)
#define lapm_local_vs						(LAPM_LOCAL._local_vs)
#define lapm_remote_nr						(LAPM_LOCAL._remote_nr)
#define lapm_remote_ns						(LAPM_LOCAL._remote_ns)
#define lapm_remote_break_vr				(LAPM_LOCAL._remote_break_vr)

#define lapm_local_busy						(LAPM_LOCAL._local_busy)
#define lapm_remote_busy					(LAPM_LOCAL._remote_busy)

#define lapm_local_addr						(LAPM_LOCAL._local_addr)
#define lapm_remote_addr					(LAPM_LOCAL._remote_addr)

#define lapm_n400_limit						(LAPM_LOCAL._n400_limit)
#define lapm_t401_limit						(LAPM_LOCAL._t401_limit)
#define lapm_t403_limit						(LAPM_LOCAL._t403_limit)
#define lapm_100ms_limit					(LAPM_LOCAL._100ms_limit)
#define lapm_inactivity_limit				(LAPM_LOCAL._inactivity_limit)

#define lapm_timer_tick						(LAPM_LOCAL._timer_tick)
#define lapm_timer_1s						(LAPM_LOCAL._timer_1s)
#define lapm_timer_1_3s						(LAPM_LOCAL._timer_1_3s)

#define lapm_n400							(LAPM_LOCAL._n400)
#define lapm_timer_array					(LAPM_LOCAL._timer_array)

#define lapm_FRMR_values					(LAPM_LOCAL._FRMR_values)

#define lapm_test_datap						(LAPM_LOCAL._test_datap)
#define lapm_test_results					(LAPM_LOCAL._test_results)

#define lapm_tx_ctl_framep					(LAPM_LOCAL._tx_ctl_framep)
#define lapm_ctl_framep						(LAPM_LOCAL._ctl_framep)

#define lapm_rx_continue_framep				(LAPM_LOCAL._rx_continue_framep)
#define lapm_rx_bg_framep					(LAPM_LOCAL._rx_bg_framep)
#define lapm_rx_fg_framep					(LAPM_LOCAL._rx_fg_framep)

#define lapm_fg_cmd							(LAPM_LOCAL._fg_cmd)
#define lapm_fg_size						(LAPM_LOCAL._fg_size)

#define lapm_tx_buffer_pending				(LAPM_LOCAL._tx_buffer_pending)
#define lapm_rx_buffer_pending				(LAPM_LOCAL._rx_buffer_pending)

#define lapm_rx_empty_count					(LAPM_LOCAL._rx_empty_count)
#define lapm_rx_next_frame_number			(LAPM_LOCAL._rx_next_frame_number)

#define lapm_xid_include_btlz				(LAPM_LOCAL._xid_include_btlz)
#define lapm_xid_btlz_length				(LAPM_LOCAL._xid_btlz_length)
#define lapm_xid_length						(LAPM_LOCAL._xid_length)
#define lapm_xid_build_bfr					(LAPM_LOCAL._xid_build_bfr)
#define lapm_xid_parse_bfr					(LAPM_LOCAL._xid_parse_bfr)
#define lapm_tx_xid_resyncp					(LAPM_LOCAL._tx_xid_resyncp)

#define lapm_tx_break_pending				(LAPM_LOCAL._tx_break_pending)
#define lapm_tx_break_sequenced				(LAPM_LOCAL._tx_break_sequenced)
#define lapm_dte_break_pending				(LAPM_LOCAL._dte_break_pending)

#define lapm_dte_chars_before_break			(LAPM_LOCAL._dte_chars_before_break)
#define lapm_break_length					(LAPM_LOCAL._break_length)
#define lapm_break_length_default			(LAPM_LOCAL._break_length_default)
#define lapm_break_type						(LAPM_LOCAL._break_type)
#define lapm_rx_break_type					(LAPM_LOCAL._rx_break_type)
#define lapm_rx_break_length				(LAPM_LOCAL._rx_break_length)

#define lapm_poll_active					(LAPM_LOCAL._poll_active)
#define lapm_sequence_number				(LAPM_LOCAL._sequence_number)

#define lapm_disconnect_active				(LAPM_LOCAL._disconnect_active)
#define lapm_idle_flag						(LAPM_LOCAL._idle_flag)
#define lapm_suspend_timers					(LAPM_LOCAL._suspend_timers)
#define lapm_suspend_flag					(LAPM_LOCAL._suspend_flag)
#define lapm_reconfigure_active				(LAPM_LOCAL._reconfigure_active)

#define lapm_rx_I_frame_discarded			(LAPM_LOCAL._rx_I_frame_discarded)
#define lapm_reject_active					(LAPM_LOCAL._reject_active)
#define lapm_test_active					(LAPM_LOCAL._test_active)
#define lapm_xid_active						(LAPM_LOCAL._xid_active)
#define lapm_rx_xid_sync					(LAPM_LOCAL._rx_xid_sync)
#define lapm_status							(LAPM_LOCAL._status)
#define lapm_tx_test_frame					(LAPM_LOCAL._tx_test_frame)

#define lapm_rx_bad_frame_count				(LAPM_LOCAL._rx_bad_frame_count)
#define lapm_rx_frame_count					(LAPM_LOCAL._rx_frame_count)
#define lapm_rx_long_frame_count			(LAPM_LOCAL._rx_long_frame_count)
#define lapm_rx_short_frame_count			(LAPM_LOCAL._rx_short_frame_count)

#define lapm_line_type						(LAPM_LOCAL._line_type)
#define lapm_compression_used				(LAPM_LOCAL._compression_used)
#define lapm_error_count					(LAPM_LOCAL._error_count)
#define lapm_current_block_size				(LAPM_LOCAL._current_block_size)
#define lapm_stop_mode						(LAPM_LOCAL._stop_mode)

#define lapm_suspend_trying_to_connect		(LAPM_LOCAL._suspend_trying_to_connect)
#define lapm_ua_just_sent					(LAPM_LOCAL._ua_just_sent)
#define lapm_first_xid						(LAPM_LOCAL._first_xid)

/* ************************************************************************* */

#endif /* _LAPM_LOCALD_H */
