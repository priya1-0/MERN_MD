
/* ************************************************************************* */
/*
 *	stated.h
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
 *	the state related resources of the CSC module.
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

#ifndef _CSC_STATED_H
#define _CSC_STATED_H

#include "csc/config.h"

/* ************************************************************************* */

typedef struct {
	uint16	_rsp_code;

	bool	_dte_char_seen;
	bool	_csc_reset_request;
	bool	_csc_hangup_request;
	bool	_omc_rsp_on_hook;
	bool	_omc_rsp_ring;
	bool	_csc_autoanswer_req;
	bool	_dteif_at_prefix_seen;
	bool	_dteif_repeat_prev_cmd;
	bool	_csc_s3_received;
	bool	_t30_rsp_stop;

	bool	_omc_irsp_carrier;
	bool	_omc_irsp_compression;
	bool	_omc_irsp_protocol;
	bool	_omc_rsp_connect;

	bool	_return_to_cmd_entry;
	uint16	_delayed_rsp_code;

	bool	_ready_for_reset;

	bool	_online_escape_timer_expd;

	bool	_dte_nochar_interval_timer;

	bool	_omc_rsp_ok;
	bool	_omc_rsp_no_carrier;
	bool	_omc_rsp_rx_frame;

	bool	_omc_rsp_error;
	bool	_dte_fx1_done;
	bool	_dte_fx2_done;
	bool	_dte_fx2_expd;
	bool	_dte_fdr_can_seen;
	bool	_dte_fdr_dc2_seen;
	bool	_t30_irsp_dis;
	bool	_t30_irsp_cig;
	bool	_t30_irsp_dtc;
	bool	_t30_irsp_csi;
	bool	_t30_irsp_tsi;
	bool	_t30_irsp_dcs;
	bool	_t30_irsp_fpts;
	bool	_t30_irsp_fet;
	bool	_t30_irsp_fpoll;
	bool	_t30_irsp_fcon;
	bool	_t30_irsp_voice;
	bool	_t30_irsp_cfr;
	bool	_t30_irsp_phase_c_timeout;
} csc_state_t;

/* ************************************************************************* */

DEF_DATA(csc_state_t, csc_state)
#define CSC_STATE_DATA csc_state_t csc_state
#define CSC_STATE USE_DATA(csc_state)

/* ************************************************************************* */

#define csc_rsp_code						(CSC_STATE._rsp_code)

#define mon_dte_char_seen					(CSC_STATE._dte_char_seen)
#define mon_csc_reset_request				(CSC_STATE._csc_reset_request)
#define mon_csc_hangup_request				(CSC_STATE._csc_hangup_request)
#define mon_omc_rsp_on_hook					(CSC_STATE._omc_rsp_on_hook)
#define mon_omc_rsp_ring					(CSC_STATE._omc_rsp_ring)
#define mon_csc_autoanswer_req				(CSC_STATE._csc_autoanswer_req)
#define mon_dteif_at_prefix_seen			(CSC_STATE._dteif_at_prefix_seen)
#define mon_dteif_repeat_prev_cmd			(CSC_STATE._dteif_repeat_prev_cmd)
#define mon_csc_s3_received					(CSC_STATE._csc_s3_received)
#define mon_t30_rsp_stop					(CSC_STATE._t30_rsp_stop)

#define mon_omc_irsp_carrier				(CSC_STATE._omc_irsp_carrier)
#define mon_omc_irsp_compression			(CSC_STATE._omc_irsp_compression)
#define mon_omc_irsp_protocol				(CSC_STATE._omc_irsp_protocol)
#define mon_omc_rsp_connect					(CSC_STATE._omc_rsp_connect)

#define csc_return_to_cmd_entry				(CSC_STATE._return_to_cmd_entry)
#define csc_delayed_rsp_code				(CSC_STATE._delayed_rsp_code)

#define csc_ready_for_reset					(CSC_STATE._ready_for_reset)

#define csc_online_escape_timer_expd		(CSC_STATE._online_escape_timer_expd)

#define	mon_dte_nochar_interval_timer		(CSC_STATE._dte_nochar_interval_timer)

#define	mon_omc_rsp_ok						(CSC_STATE._omc_rsp_ok)
#define	mon_omc_rsp_no_carrier				(CSC_STATE._omc_rsp_no_carrier)
#define	mon_omc_rsp_rx_frame				(CSC_STATE._omc_rsp_rx_frame)

#define	mon_omc_rsp_error					(CSC_STATE._omc_rsp_error)
#define	mon_dte_fx1_done					(CSC_STATE._dte_fx1_done)
#define	mon_dte_fx2_done					(CSC_STATE._dte_fx2_done)
#define	mon_dte_fx2_expd					(CSC_STATE._dte_fx2_expd)
#define	mon_dte_fdr_can_seen				(CSC_STATE._dte_fdr_can_seen)
#define	mon_dte_fdr_dc2_seen				(CSC_STATE._dte_fdr_dc2_seen)

#define mon_t30_irsp_dis					(CSC_STATE._t30_irsp_dis)
#define mon_t30_irsp_cig					(CSC_STATE._t30_irsp_cig)
#define mon_t30_irsp_dtc					(CSC_STATE._t30_irsp_dtc)
#define mon_t30_irsp_csi					(CSC_STATE._t30_irsp_csi)
#define mon_t30_irsp_tsi					(CSC_STATE._t30_irsp_tsi)
#define mon_t30_irsp_dcs					(CSC_STATE._t30_irsp_dcs)
#define mon_t30_irsp_fpts					(CSC_STATE._t30_irsp_fpts)
#define mon_t30_irsp_fet					(CSC_STATE._t30_irsp_fet)
#define mon_t30_irsp_fpoll					(CSC_STATE._t30_irsp_fpoll)
#define mon_t30_irsp_fcon					(CSC_STATE._t30_irsp_fcon)
#define mon_t30_irsp_voice					(CSC_STATE._t30_irsp_voice)
#define mon_t30_irsp_cfr					(CSC_STATE._t30_irsp_cfr)
#define mon_t30_irsp_phase_c_timeout		(CSC_STATE._t30_irsp_phase_c_timeout)

/* ************************************************************************* */

#endif /* _CSC_STATED_H */
