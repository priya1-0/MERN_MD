
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
 *	Module:		MNP
 *
 *	This file contains the private parameter declarations/definitions
 *	for the MNP module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 20:29:43  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _MNP_LOCALD_H
#define _MNP_LOCALD_H

#include "mnp/config.h"
#include "mnp/frames.h"

/* ************************************************************************* */

typedef struct {

/* ************************************************************************* */

	/*
	 * negotiated mnp options
	 *
	 */

	uint8	_nego_data_compression;	/* 0, 3 */
	uint16	_nego_compression_type;
	bool	_nego_header_optimize_en;
	bool	_nego_stream_size_256_en;
	uint8	_nego_service_class;		/* MNP_CLASS__xxx */
	uint8	_nego_service_level;		/* MNP_LEVEL__xxx */
	uint16	_nego_max_data_size;		/* 64 - 260 */

/* ************************************************************************* */
	/*
	 * arrays of the transmit and receive frames
	 *
	 */

	mnp_lt_frame_t       _tx_frame_buffers [MNP__NUMBER_OF_BUFFERS];
	mnp_receive_frame_t  _rx_frame_buffers [MNP__NUMBER_OF_BUFFERS];

/* ************************************************************************* */
	/*
	 * static buffers that contain a particular transmit frame
	 *
	 */

	mnp_lr_frame_t  _tx_lr_frame;
	mnp_ld_frame_t  _tx_ld_frame;
	mnp_ln_frame_t  _tx_ln_frame;
	mnp_lna_frame_t _tx_lna_frame;
	mnp_la_frame_t  _tx_la_frame;

/* ************************************************************************* */
	/*
	 * receive buffer management variables
	 *
	 */

	mnp_receive_frame_t *_rx_empty_queue [MNP__NUMBER_OF_BUFFERS+1];
	mnp_receive_frame_t *_rx_process_queue [MNP__NUMBER_OF_BUFFERS+1];
	mnp_receive_frame_t *_rx_receive_queue [MNP__NUMBER_OF_BUFFERS+1];

	uint8	_rx_empty_queue_in;
	uint8	_rx_empty_queue_out;
	uint8	_rx_process_queue_in;
	uint8	_rx_process_queue_out;
	uint8	_rx_receive_queue_in;
	uint8	_rx_receive_queue_out;

/* ************************************************************************* */
	/*
	 * transmit buffer management variables
	 *
	 */

	bool	_tx_busy_flag;
	uint8	_tx_input_index;
	uint8	_tx_oldest_index;
	uint8	_tx_send_index;
	uint8	_tx_scanned_index;

/* ************************************************************************* */
	/*
	 * holding buffer management variables
	 *
 	 */

	uint8   _tx_holding_queue_in;
	uint8   _tx_holding_queue_out;

/* ************************************************************************* */
	/*
	 * transmit buffer size management variables
	 *
	 */

	uint8	_tx_pdu_dec_amount; 			/* 0 - 64 */
	uint8	_tx_pdu_inc_amount;			/* 0 - 32 */
	uint16	_session_max_data_size;		/* 0 - 256 */
	uint16	_restricted_max_data_size;	/*  */
	uint16	_current_max_data_size;		/*  */
	uint8	_tx_good_frames_count;		/* 0 - 0xFF */

/* ************************************************************************* */
	/*
	 * results of parsing received frames
	 *
	 */

	uint16	_rx_lr_parm_flags;
	uint16	_rx_lr_service_level;
	uint16	_rx_lr_serial_number [6];
	uint16	_rx_lr_service_class;
	uint16	_rx_lr_credit_amount;
	uint16	_rx_lr_max_data_size_tmp [2];
	uint16	_rx_lr_max_data_size;
	uint16	_rx_lr_optimization;
	uint16	_rx_lr_data_compression;
	uint16  _rx_lr_none;

	uint16	_rx_ld_parm_flags;
	uint16	_rx_ld_disconnect_reason;			/* DP_REASON__xxx */
	uint16	_rx_ld_user_disconnect_reason;	/* DP_REASON__xxx */

	uint16	_rx_ln_parm_flags;
	uint16	_rx_ln_sequence_number;		/* 0 - 255 */
	uint16	_rx_ln_break_type;

	uint16	_rx_lna_parm_flags;
	uint16	_rx_lna_sequence_number;		/* 0 - 255 */

	uint16	_rx_lt_parm_flags;
	uint16	_rx_lt_sequence_number;		/* 0 - 255 */

	uint16	_rx_la_parm_flags;
	uint16	_rx_la_sequence_number;		/* 0 - 255 */
	uint16	_rx_la_credit_amount;

/* ************************************************************************* */
	/*
	 * mnp system wide working frame pointers
	 *
	 */

	mnp_receive_frame_t *_rx_empty_framep;
	mnp_receive_frame_t *_rx_working_framep;
	mnp_receive_frame_t *_rx_buffer_framep;
	mnp_receive_frame_t *_rx_current_framep;

	mnp_transmit_frame_t *_tx_active_framep;
	mnp_transmit_frame_t *_tx_working_framep;
	mnp_transmit_frame_t *_tx_current_framep;
	mnp_transmit_frame_t *_tx_holding_framep[MNP__NUMBER_OF_HOLD_BUFFERS];

/* ************************************************************************* */
	/*
	 * variables used to building and emptying lt frames
	 *
	 */

	bool	_empty_lt_in_progress;

	pack8	*_rx_empty_datap;
	uint16  _rx_empty_byte_count;
	uint8	_rx_empty_byte_limit_count;

	pack8	*_tx_build_datap;
	uint16  _tx_build_byte_count;
	uint16  _tx_build_byte_remaining_count;

/* ************************************************************************* */
	/*
	 * miscellaneous program flags
	 *
	 */

	uint8	_status;						/* DP_STATUS__xxx */
	uint8	_state;						/* MNP_STATE__xxx */

	uint8	_user_disconnect_reason;		/* DP_REASON__xxx */
	uint8	_rcvd_disconnect_reason;		/* DP_REASON__xxx */
	uint8	_rcvd_user_disconnect_reason; 	/* DP_REASON__xxx */

	bool	_idle_flag;					/* true if mnp_idle honored */
    bool    _suspend_timers;            /* will suspend and idle mnp */
	bool	_suspend_flag;					/* true if mnp_suspend honored */
	bool	_disconnect_flag;				/* true if we have disconnected */

	uint8	_frame_retry_count;			/* generic frame retry count */
										/* MNP_RETRY__xxx */
	uint8	_ln_retry_count;				/* specific ln retry count */

/* ************************************************************************* */
	/*
	 * timer variables
	 *
	 */

	uint8	_timer_div;
	uint8	_timer_tick;
	uint8	_timer_tick2;
	uint8   _timer_tick10;
	uint8	_ln_transmit_timer;
	uint8	_missing_response_timer;
	uint8	_transmit_delay_timer;
	uint8	_la_transmit_timer;
	uint16	_timer_inactivity;
	uint16  _timer_startup_inactivity;

	/* ************************************************************************* */
	/*
	 * variables for keeping track of the various types of breaks
	 *
	 */

	bool	_sequenced_dte_break_pending;		/* sequenced dte break in progress */
	uint16	_sequenced_dte_char_count;		/* how many dte chars to go */

	bool	_sequenced_line_break_pending;		/* sequenced line break in progress */
	uint16	_sequenced_line_char_count;		/* how many line chars to go */

	bool	_send_dte_break_request;			/* do a dte_to_break () */
	bool	_send_line_break_request;			/* do a line_to_break () */

	bool	_dte_break_pending;				/* error correction dte break is pending */

	bool	_clear_transmit_buffers_req;		/* clear mnp transmit buffers */
	bool	_clear_receive_buffers_req;		/* clear mnp receive buffers */

/* ************************************************************************* */
	/*
	 * variables for keeping track of where we are and what we are doing
	 *
	 */

/* ************************************************************************* */
	/*
	 * lt generation variables
	 *
	 */

	/* number of buffers reported in the remote modem */

	uint8	_max_remote_credit_amount;

	/* we recieved a la. we may be able to free some */
	/* our pending pending tx buffers                */

	bool	_la_frame_was_received_flag;

	/* the la receiver discovered duplicate la frames */
	/* indicating the remote link has out of sequence */
	/* frames and we should start resending them      */

	bool	_found_a_duplicate_la_frame;

	/* this flags indicates a mnp frame has been sent.      */
	/* if this is a resend then decrement the retry counter */

	bool	_lt_frame_was_sent;

	/* the last sent lt sequence number */

	uint8	_send_lt_sequence_number;		/* 0 - 255 */

	/* the last contents of the received la frame */
	/* for an aid in detecting duplicate la's     */

	uint8	_last_rx_la_credit_amount;
	uint8	_last_rx_la_sequence_number;	/* 0 - 255 */

/* ************************************************************************* */
	/*
	 * la generation variables
	 *
	 */

	/* the amount of receive space we have now and had */
	/* the last time we reported our buffer space      */

	uint8	_our_local_credit_amount;
	uint8	_last_reported_local_credit_amount;
	uint8	_current_remote_credit_amount;

	/* last lt that was acknowledged by a la */

	uint8	_last_sent_la_sequence_number;	/* 0 - 255 */

	/* we have an explicit command to create a la frame */

	bool	_la_send_request_pending;

	/* the receiver found something very wrong and wants */
	/* duplicate la's to be generated                    */

	bool	_out_of_sequence_lt_frame_found;

	/* if we were reported that we had no space an the     */
	/* last la frame then this variable enables a test     */
	/* for expidited la generation when space becomes free */

	bool	_force_la_if_more_local_space;

	/* this is the last sequence number that was correctly */
	/* processed from the line data                        */

	uint8	_last_correct_lt_sequence_number;	/* 0 - 255 */

/* ************************************************************************* */
	/*
	 * ln generation variables
	 *
	 */

	/* flag and sequence number of ln frame to send          */
	/* flag to indicate that we expect a lna for the ln sent */

	bool	_ln_send_request_pending;
	uint8	_send_ln_sequence_number;	/* 0 - 255 */
	bool	_lna_expected_for_sent_ln;

/* ************************************************************************* */
	/*
	 * lna generation variables
	 *
	 */

	/* the last ln to detect duplicate ln (corrupted lna's)        */
	/* the flag to indicate we have received a ln an lna is needed */

	uint8	_last_rx_ln_sequence_number;	/* 0 - 255 */
	bool	_lna_send_request_pending;

/* ************************************************************************* */
	/*
	 * other miscellaneous variables
	 *
	 */

	/* last proper lt sequenced from process queue */

	uint8	_empty_data_sequence_number;	/* 0 - 255 */
	bool	_preconnect_frame_pending;			/* NOT USED */

/* ************************************************************************* */

/* ************************************************************************* */
	/*
	 * info variables
	 *
	 */

	uint8	_line_type;			/* LINE_TYPE__xxx */
	uint8	_compression_used;	/* COMPRESSION__xxx */
	uint8	_error_count;
	uint16	_current_block_size;
	uint8	_stop_mode;			/* STOP_MODE_xxx */

/**** Pre Lapm ***/

	uint16	_num_of_flags_rx;

/**** AutoReliable inactivity time for mnp_plus startups. ***/
	uint8	_ar_inactivity_timer;

	bool	_received_first_mnp_lr;

	bool	_suspend_trying_to_connect;

	uint16	_remote_max_data_size_seen;

} mnp_local_t;

/* ************************************************************************* */

#define MNP_LOCAL_DATA mnp_local_t mnp_local
DEF_DATA(mnp_local_t, mnp_local)
#define MNP_LOCAL USE_DATA(mnp_local)

/* ************************************************************************* */

/*
 * module data definitions
 *
 */

#define mnp_nego_data_compression			(MNP_LOCAL._nego_data_compression)
#define mnp_nego_compression_type			(MNP_LOCAL._nego_compression_type)
#define mnp_nego_header_optimize_en			(MNP_LOCAL._nego_header_optimize_en)
#define mnp_nego_stream_size_256_en			(MNP_LOCAL._nego_stream_size_256_en)
#define mnp_nego_service_class				(MNP_LOCAL._nego_service_class)
#define mnp_nego_service_level				(MNP_LOCAL._nego_service_level)
#define mnp_nego_max_data_size				(MNP_LOCAL._nego_max_data_size)

#define mnp_tx_frame_buffers				(MNP_LOCAL._tx_frame_buffers)
#define mnp_rx_frame_buffers				(MNP_LOCAL._rx_frame_buffers)

#define mnp_tx_lr_frame						(MNP_LOCAL._tx_lr_frame)
#define mnp_tx_ld_frame						(MNP_LOCAL._tx_ld_frame)
#define mnp_tx_ln_frame						(MNP_LOCAL._tx_ln_frame)
#define mnp_tx_lna_frame					(MNP_LOCAL._tx_lna_frame)
#define mnp_tx_la_frame						(MNP_LOCAL._tx_la_frame)

#define mnp_rx_empty_queue					(MNP_LOCAL._rx_empty_queue)
#define mnp_rx_process_queue				(MNP_LOCAL._rx_process_queue)
#define mnp_rx_receive_queue				(MNP_LOCAL._rx_receive_queue)

#define mnp_rx_empty_queue_in				(MNP_LOCAL._rx_empty_queue_in)
#define mnp_rx_empty_queue_out				(MNP_LOCAL._rx_empty_queue_out)
#define mnp_rx_process_queue_in				(MNP_LOCAL._rx_process_queue_in)
#define mnp_rx_process_queue_out			(MNP_LOCAL._rx_process_queue_out)
#define mnp_rx_receive_queue_in				(MNP_LOCAL._rx_receive_queue_in)
#define mnp_rx_receive_queue_out			(MNP_LOCAL._rx_receive_queue_out)

#define mnp_tx_busy_flag					(MNP_LOCAL._tx_busy_flag)
#define mnp_tx_input_index					(MNP_LOCAL._tx_input_index)
#define mnp_tx_oldest_index					(MNP_LOCAL._tx_oldest_index)
#define mnp_tx_send_index					(MNP_LOCAL._tx_send_index)
#define mnp_tx_scanned_index				(MNP_LOCAL._tx_scanned_index)

#define mnp_tx_holding_queue_in				(MNP_LOCAL._tx_holding_queue_in)
#define mnp_tx_holding_queue_out            (MNP_LOCAL._tx_holding_queue_out)

#define mnp_tx_pdu_dec_amount				(MNP_LOCAL._tx_pdu_dec_amount)
#define mnp_tx_pdu_inc_amount				(MNP_LOCAL._tx_pdu_inc_amount)
#define mnp_session_max_data_size			(MNP_LOCAL._session_max_data_size)
#define mnp_restricted_max_data_size		(MNP_LOCAL._restricted_max_data_size)
#define mnp_current_max_data_size			(MNP_LOCAL._current_max_data_size)
#define mnp_tx_good_frames_count			(MNP_LOCAL._tx_good_frames_count)

#define mnp_rx_lr_parm_flags				(MNP_LOCAL._rx_lr_parm_flags)
#define mnp_rx_lr_service_level				(MNP_LOCAL._rx_lr_service_level)
#define mnp_rx_lr_serial_number				(MNP_LOCAL._rx_lr_serial_number)
#define mnp_rx_lr_service_class				(MNP_LOCAL._rx_lr_service_class)
#define mnp_rx_lr_credit_amount				(MNP_LOCAL._rx_lr_credit_amount)
#define mnp_rx_lr_max_data_size_tmp			(MNP_LOCAL._rx_lr_max_data_size_tmp)
#define mnp_rx_lr_max_data_size				(MNP_LOCAL._rx_lr_max_data_size)
#define mnp_rx_lr_optimization				(MNP_LOCAL._rx_lr_optimization)
#define mnp_rx_lr_data_compression			(MNP_LOCAL._rx_lr_data_compression)
#define mnp_rx_lr_none						(MNP_LOCAL._rx_lr_none)

#define mnp_rx_ld_parm_flags				(MNP_LOCAL._rx_ld_parm_flags)
#define mnp_rx_ld_disconnect_reason			(MNP_LOCAL._rx_ld_disconnect_reason)
#define mnp_rx_ld_user_disconnect_reason	(MNP_LOCAL._rx_ld_user_disconnect_reason)

#define mnp_rx_ln_parm_flags				(MNP_LOCAL._rx_ln_parm_flags)
#define mnp_rx_ln_sequence_number			(MNP_LOCAL._rx_ln_sequence_number)
#define mnp_rx_ln_break_type				(MNP_LOCAL._rx_ln_break_type)

#define mnp_rx_lna_parm_flags				(MNP_LOCAL._rx_lna_parm_flags)
#define mnp_rx_lna_sequence_number			(MNP_LOCAL._rx_lna_sequence_number)

#define mnp_rx_lt_parm_flags				(MNP_LOCAL._rx_lt_parm_flags)
#define mnp_rx_lt_sequence_number			(MNP_LOCAL._rx_lt_sequence_number)

#define mnp_rx_la_parm_flags				(MNP_LOCAL._rx_la_parm_flags)
#define mnp_rx_la_sequence_number			(MNP_LOCAL._rx_la_sequence_number)
#define mnp_rx_la_credit_amount				(MNP_LOCAL._rx_la_credit_amount)

#define mnp_rx_empty_framep					(MNP_LOCAL._rx_empty_framep)
#define mnp_rx_working_framep				(MNP_LOCAL._rx_working_framep)
#define mnp_rx_buffer_framep				(MNP_LOCAL._rx_buffer_framep)
#define mnp_rx_current_framep				(MNP_LOCAL._rx_current_framep)

#define mnp_tx_active_framep				(MNP_LOCAL._tx_active_framep)
#define mnp_tx_working_framep				(MNP_LOCAL._tx_working_framep)
#define mnp_tx_current_framep				(MNP_LOCAL._tx_current_framep)
#define mnp_tx_holding_framep				(MNP_LOCAL._tx_holding_framep)

#define mnp_empty_lt_in_progress			(MNP_LOCAL._empty_lt_in_progress)

#define mnp_rx_empty_datap					(MNP_LOCAL._rx_empty_datap)
#define mnp_rx_empty_byte_count				(MNP_LOCAL._rx_empty_byte_count)
#define mnp_rx_empty_byte_limit_count		(MNP_LOCAL._rx_empty_byte_limit_count)

#define mnp_tx_build_datap					(MNP_LOCAL._tx_build_datap)
#define mnp_tx_build_byte_count				(MNP_LOCAL._tx_build_byte_count)
#define mnp_tx_build_byte_remaining_count	(MNP_LOCAL._tx_build_byte_remaining_count)

#define mnp_status							(MNP_LOCAL._status)
#define mnp_state							(MNP_LOCAL._state)

#define mnp_user_disconnect_reason			(MNP_LOCAL._user_disconnect_reason)
#define mnp_rcvd_disconnect_reason			(MNP_LOCAL._rcvd_disconnect_reason)
#define mnp_rcvd_user_disconnect_reason		(MNP_LOCAL._rcvd_user_disconnect_reason)

#define mnp_idle_flag						(MNP_LOCAL._idle_flag)
#define mnp_suspend_timers					(MNP_LOCAL._suspend_timers)
#define mnp_suspend_flag					(MNP_LOCAL._suspend_flag)
#define mnp_disconnect_flag					(MNP_LOCAL._disconnect_flag)

#define mnp_frame_retry_count				(MNP_LOCAL._frame_retry_count)
#define mnp_ln_retry_count					(MNP_LOCAL._ln_retry_count)

#define mnp_timer_div						(MNP_LOCAL._timer_div)
#define mnp_timer_tick						(MNP_LOCAL._timer_tick)
#define mnp_timer_tick2						(MNP_LOCAL._timer_tick2)
#define mnp_timer_tick10					(MNP_LOCAL._timer_tick10)
#define mnp_ln_transmit_timer				(MNP_LOCAL._ln_transmit_timer)
#define mnp_missing_response_timer			(MNP_LOCAL._missing_response_timer)
#define mnp_transmit_delay_timer			(MNP_LOCAL._transmit_delay_timer)
#define mnp_la_transmit_timer				(MNP_LOCAL._la_transmit_timer)
#define mnp_timer_inactivity				(MNP_LOCAL._timer_inactivity)
#define mnp_timer_startup_inactivity		(MNP_LOCAL._timer_startup_inactivity)

#define mnp_sequenced_dte_break_pending		(MNP_LOCAL._sequenced_dte_break_pending)
#define mnp_sequenced_dte_char_count		(MNP_LOCAL._sequenced_dte_char_count)

#define mnp_sequenced_line_break_pending	(MNP_LOCAL._sequenced_line_break_pending)
#define mnp_sequenced_line_char_count		(MNP_LOCAL._sequenced_line_char_count)

#define mnp_send_dte_break_request			(MNP_LOCAL._send_dte_break_request)
#define mnp_send_line_break_request			(MNP_LOCAL._send_line_break_request)

#define mnp_dte_break_pending				(MNP_LOCAL._dte_break_pending)

#define mnp_clear_transmit_buffers_req		(MNP_LOCAL._clear_transmit_buffers_req)
#define mnp_clear_receive_buffers_req		(MNP_LOCAL._clear_receive_buffers_req)

#define mnp_max_remote_credit_amount		(MNP_LOCAL._max_remote_credit_amount)
#define mnp_la_frame_was_received_flag		(MNP_LOCAL._la_frame_was_received_flag)
#define mnp_found_a_duplicate_la_frame		(MNP_LOCAL._found_a_duplicate_la_frame)
#define mnp_lt_frame_was_sent				(MNP_LOCAL._lt_frame_was_sent)
#define mnp_send_lt_sequence_number			(MNP_LOCAL._send_lt_sequence_number)
#define mnp_last_rx_la_credit_amount		(MNP_LOCAL._last_rx_la_credit_amount)
#define mnp_last_rx_la_sequence_number		(MNP_LOCAL._last_rx_la_sequence_number)
#define mnp_our_local_credit_amount			(MNP_LOCAL._our_local_credit_amount)
#define mnp_last_reported_local_credit_amount (MNP_LOCAL._last_reported_local_credit_amount)
#define mnp_current_remote_credit_amount	(MNP_LOCAL._current_remote_credit_amount)
#define mnp_last_sent_la_sequence_number	(MNP_LOCAL._last_sent_la_sequence_number)
#define mnp_la_send_request_pending			(MNP_LOCAL._la_send_request_pending)
#define mnp_out_of_sequence_lt_frame_found	(MNP_LOCAL._out_of_sequence_lt_frame_found)
#define mnp_force_la_if_more_local_space	(MNP_LOCAL._force_la_if_more_local_space)
#define mnp_last_correct_lt_sequence_number	(MNP_LOCAL._last_correct_lt_sequence_number)
#define mnp_ln_send_request_pending			(MNP_LOCAL._ln_send_request_pending)
#define mnp_send_ln_sequence_number			(MNP_LOCAL._send_ln_sequence_number)
#define mnp_lna_expected_for_sent_ln		(MNP_LOCAL._lna_expected_for_sent_ln)
#define mnp_last_rx_ln_sequence_number		(MNP_LOCAL._last_rx_ln_sequence_number)
#define mnp_lna_send_request_pending		(MNP_LOCAL._lna_send_request_pending)
#define mnp_empty_data_sequence_number		(MNP_LOCAL._empty_data_sequence_number)
#define mnp_preconnect_frame_pending		(MNP_LOCAL._preconnect_frame_pending)
#define mnp_line_type						 (MNP_LOCAL._line_type)
#define mnp_compression_used				(MNP_LOCAL._compression_used)
#define mnp_error_count						(MNP_LOCAL._error_count)
#define mnp_current_block_size				(MNP_LOCAL._current_block_size)
#define mnp_stop_mode						(MNP_LOCAL._stop_mode)
#define mnp_num_of_flags_rx					(MNP_LOCAL._num_of_flags_rx)
#define mnp_ar_inactivity_timer				(MNP_LOCAL._ar_inactivity_timer)
#define mnp_received_first_mnp_lr			(MNP_LOCAL._received_first_mnp_lr)
#define mnp_suspend_trying_to_connect       (MNP_LOCAL._suspend_trying_to_connect)
#define mnp_remote_max_data_size_seen       (MNP_LOCAL._remote_max_data_size_seen)

/* ************************************************************************* */

#endif /* _MNP_LOCALD_H */
