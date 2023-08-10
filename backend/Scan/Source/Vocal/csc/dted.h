
/* ************************************************************************* */
/*
 *	dted.h
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
 *	the dte related resources of the CSC module.
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

#ifndef _CSC_DTED_H
#define _CSC_DTED_H

#include "csc/config.h"

/* ************************************************************************* */

typedef struct {
	uint16	_tx_buffer [DTE_TX_BUFFER_SIZE];
	uint16	_rx_buffer [DTE_RX_BUFFER_SIZE];
	char	_csc_cmdbuf [DTE_TX_CMD_SIZE];
	char	*_csc_cmdbufp;
	char	*_cmdparsep;

	char	*_parm_csp_cmdp;
	char	*_stat_csp_cmdp;
	char	*_parm_csp_endp;
	uint16	_stat_csp_code;
	uint16	_stat_csp_action;
	uint16	_parm_csp_valid_check_only_en;

	uint16	*_tx_inp;
	uint16	*_tx_outp;
	uint16	*_tx_cmdp;
	uint16	*_tx_holdp;
	uint16	*_tx_cmdmaxp;
	uint16	_tx_cnt;
	uint16	_tx_cnt_hold;
	bool	_tx_overflow;
	uint16	*_rx_inp;
	uint16	*_rx_outp;
	uint16	_rx_cnt;
	bool	_rx_overflow;
	bool	_cmd_within;
	bool	_cmd_rcvd;
	bool	_rx_expedited_break_pending;
	uint8	_rx_expedited_break_duration;
	uint16	_ties_state;
	bool	_ties_within;
	bool	_ties_upper_a;

	bool	_frame_ok;

	uint8	_dte_rx_ascii_rep_state;
	uint8	_dte_rx_prev_value;

	bool	_post_cmd_echo_within;

	uint16	_char_detect_timer;

	bool	_tx_off;
	uint32	_tx_mtr;
	uint32	_rx_mtr;
} csc_dte_t;

/* ************************************************************************* */

DEF_DATA(csc_dte_t, csc_dte)
#define CSC_DTE_DATA csc_dte_t csc_dte
#define CSC_DTE USE_DATA(csc_dte)

/* ************************************************************************* */

#define dte_tx_buffer						(CSC_DTE._tx_buffer)
#define dte_rx_buffer						(CSC_DTE._rx_buffer)

#define csc_cmdbuf							(CSC_DTE._csc_cmdbuf)
#define csc_cmdbufp							(CSC_DTE._csc_cmdbufp)
#define cmdparsep							(CSC_DTE._cmdparsep)

#define parm__csp_cmdp 						(CSC_DTE._parm_csp_cmdp)
#define stat__csp_cmdp 						(CSC_DTE._stat_csp_cmdp)
#define parm__csp_endp 						(CSC_DTE._parm_csp_endp)

#define stat__csp_code 						(CSC_DTE._stat_csp_code)
#define stat__csp_action  					(CSC_DTE._stat_csp_action)
#define parm__csp_valid_check_only_en		(CSC_DTE._parm_csp_valid_check_only_en)

#define dte_tx_inp							(CSC_DTE._tx_inp)
#define dte_tx_outp							(CSC_DTE._tx_outp)
#define dte_tx_cmdp							(CSC_DTE._tx_cmdp)
#define dte_tx_holdp						(CSC_DTE._tx_holdp)
#define dte_tx_cmdmaxp						(CSC_DTE._tx_cmdmaxp)
#define dte_tx_cnt							(CSC_DTE._tx_cnt)
#define dte_tx_cnt_hold						(CSC_DTE._tx_cnt_hold)
#define dte_tx_overflow						(CSC_DTE._tx_overflow)

#define dte_rx_inp							(CSC_DTE._rx_inp)
#define dte_rx_outp							(CSC_DTE._rx_outp)
#define dte_rx_cnt							(CSC_DTE._rx_cnt)
#define dte_rx_overflow						(CSC_DTE._rx_overflow)

#define dte_cmd_within						(CSC_DTE._cmd_within)
#define dte_cmd_rcvd						(CSC_DTE._cmd_rcvd)
#define dte_rx_expedited_break_pending		(CSC_DTE._rx_expedited_break_pending)
#define dte_rx_expedited_break_duration		(CSC_DTE._rx_expedited_break_duration)
#define dte_ties_state						(CSC_DTE._ties_state)
#define dte_ties_within						(CSC_DTE._ties_within)
#define dte_ties_upper_a					(CSC_DTE._ties_upper_a)

#define dte_fax_within						(CSC_DTE._fax_within)
#define dte_fax_2							(CSC_DTE._fax_2)
#define dte_fax_tx							(CSC_DTE._fax_tx)
#define dte_fax_bor							(CSC_DTE._fax_bor)
#define dte_fax_2_0							(CSC_DTE._fax_2_0)
#define dte_fax_frm							(CSC_DTE._fax_frm)
#define dte_fax_term_dle_sent				(CSC_DTE._fax_term_dle_sent)
#define dte_fax_frame_end_seen				(CSC_DTE._fax_frame_end_seen)
#define dte_frame_ok						(CSC_DTE._frame_ok)
#define dte_fax_rx_frame_avail				(CSC_DTE._fax_rx_frame_avail)

#define dte_fax_rx_within_dle_data			(CSC_DTE._dte_fax_rx_within_dle_data)
#define dte_fax_rx_within_dle_etx			(CSC_DTE._dte_fax_rx_within_dle_etx)
#define dte_fax_tx_within_dle_data			(CSC_DTE._dte_fax_tx_within_dle_data)
#define dte_fax_tx_within_dle_etx			(CSC_DTE._dte_fax_tx_within_dle_etx)

#define dte_fdt_send_can					(CSC_DTE._fdt_send_can)
#define dte_fdt_within_dle					(CSC_DTE._fdt_within_dle)
#define dte_fdr_send_dle_etx				(CSC_DTE._fdr_send_dle_etx)
#define dte_fdr_dc2_search_en				(CSC_DTE._fdr_dc2_search_en)
#define dte_fdr_can_search_en				(CSC_DTE._fdr_can_search_en)
#define dte_fdr_char_search_en				(CSC_DTE._fdr_char_search_en)
#define dte_fdr_within_dle_etx				(CSC_DTE._fdr_within_dle_etx)
#define dte_fdr_within_dle_dc2				(CSC_DTE._fdr_within_dle_dc2)
#define dte_fdr_within_dle_overrun			(CSC_DTE._fdr_within_dle_overrun)
#define dte_fdr_within_dle_fullness			(CSC_DTE._fdr_within_dle_fullness)
#define dte_fdr_within_dle_data				(CSC_DTE._fdr_within_dle_data)
#define dte_fdr_within_dle_double_data		(CSC_DTE._fdr_within_dle_double_data)
#define dte_fdr_fullness_req_seen			(CSC_DTE._fdr_fullness_req_seen)
#define dte_fdr_dle_dc2_sent				(CSC_DTE._fdr_dle_dc2_sent)

#define dte_rx_ascii_rep_state				(CSC_DTE._dte_rx_ascii_rep_state)
#define dte_rx_prev_value					(CSC_DTE._dte_rx_prev_value)

#define dte_post_cmd_echo_within			(CSC_DTE._post_cmd_echo_within)

#define dte_char_detect_timer				(CSC_DTE._char_detect_timer)

#define dte_tx_off							(CSC_DTE._tx_off)
#define dte_tx_mtr							(CSC_DTE._tx_mtr)
#define dte_rx_mtr							(CSC_DTE._rx_mtr)

/* ************************************************************************* */

#endif /* _CSC_DTED_H */
