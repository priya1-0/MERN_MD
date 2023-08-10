
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
 *	Module:		OMC
 *
 *	This file contains the private parameter declarations/definitions
 *	for the OMC module.
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

#ifndef _OMC_LOCALD_H
#define _OMC_LOCALD_H

#include "omc/config.h"

/* ************************************************************************* */

typedef struct {
	bool	_dial_tone_dialing_en;
	uint8	*_dial_stringp;
	bool	_dial_on_hook_timer_expd;
	bool	_dial_blind_dial_timer_expd;
	bool	_dial_billing_delay_timer_expd;
	uint16	_pump_options_mask;
	bool	_delayed_on_hook;

	uint16 _om_st_tick_cnt;
	uint16 _om_prev_st_period_duration;
	uint16 _om_ret_ren;
	bool   _om_within_suspend;
	bool   _om_dm_monitor_en;
	bool   _om_dp_monitor_en;
	uint32 _om_stref_tx_compdata_mtr;
	uint32 _om_stref_rx_compdata_mtr;
	uint32 _om_stref_tx_data_mtr;
	uint32 _om_stref_rx_data_mtr;
	bool   _post_dt_pause_state;
} omc_local_t;

/* ************************************************************************* */

DEF_DATA(omc_local_t, omc_local)
#define OMC_LOCAL_DATA omc_local_t omc_local
#define OMC_LOCAL USE_DATA(omc_local)

/* ************************************************************************* */

#define dial_tone_dialing_en				(OMC_LOCAL._dial_tone_dialing_en)
#define dial_stringp						(OMC_LOCAL._dial_stringp)
#define	dial_on_hook_timer_expd				(OMC_LOCAL._dial_on_hook_timer_expd)
#define	dial_blind_dial_timer_expd			(OMC_LOCAL._dial_blind_dial_timer_expd)
#define	dial_billing_delay_timer_expd		(OMC_LOCAL._dial_billing_delay_timer_expd)
#define omc_pump_options_mask				(OMC_LOCAL._pump_options_mask)
#define	omc_delayed_on_hook					(OMC_LOCAL._delayed_on_hook)

#define omc_om_st_tick_cnt					(OMC_LOCAL._om_st_tick_cnt)
#define omc_om_prev_st_period_duration		(OMC_LOCAL._om_prev_st_period_duration)
#define omc_om_ret_ren						(OMC_LOCAL._om_ret_ren)
#define omc_om_within_suspend				(OMC_LOCAL._om_within_suspend)
#define omc_om_dm_monitor_en				(OMC_LOCAL._om_dm_monitor_en)
#define omc_om_dp_monitor_en				(OMC_LOCAL._om_dp_monitor_en)
#define omc_om_stref_tx_compdata_mtr		(OMC_LOCAL._om_stref_tx_compdata_mtr)
#define omc_om_stref_rx_compdata_mtr		(OMC_LOCAL._om_stref_rx_compdata_mtr)
#define omc_om_stref_tx_data_mtr			(OMC_LOCAL._om_stref_tx_data_mtr)
#define omc_om_stref_rx_data_mtr			(OMC_LOCAL._om_stref_rx_data_mtr)
#define dial_post_dt_pause_state			(OMC_LOCAL._post_dt_pause_state)
/* ************************************************************************* */

#endif /* _OMC_LOCALD_H */
