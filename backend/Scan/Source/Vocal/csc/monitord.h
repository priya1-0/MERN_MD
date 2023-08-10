
/* ************************************************************************* */
/*
 *	monitord.h
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
 *	Module:		MONITOR
 *
 *	This file contains the public parameter declarations/definitions for
 *	the MONITOR module.
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

#ifndef _MONITOR_MONITORD_H
#define _MONITOR_MONITORD_H

/* ************************************************************************* */

typedef struct {
	bool	_mon__rsp_done;

	bool	_bog__cp_dial_only;
	bool	_bog__csc_hangup_request;
	bool	_bog__dte_fax_rx_done;

	bool	_fog__inactivity_dtimer_expired;		/* Set by bg 10ms timer */
	bool	_mon__ring_cnt_cleared_timer_expired;
	bool	_fog__dteif_tx_start;

	bool	_mon__csc_access_continue;
	bool	_mon__csc_timer_expd;
	bool	_mon__omc_irsp_csi;
	bool	_mon__omc_irsp_dcs;
	bool	_mon__omc_irsp_dis;
	bool	_mon__omc_irsp_dtc;
	bool	_mon__omc_irsp_fcon;
	bool	_mon__omc_irsp_stop;
	bool	_mon__omc_irsp_tsi;
	bool	_mon__t30_irsp_cfr;
	bool	_mon__t30_irsp_cig;
	bool	_mon__t30_irsp_connect;
	bool	_mon__t30_irsp_csi;
	bool	_mon__t30_irsp_dcs;
	bool	_mon__t30_irsp_dis;
	bool	_mon__t30_irsp_dtc;
	bool	_mon__t30_irsp_fcon;
	bool	_mon__t30_irsp_fet;
	bool	_mon__t30_irsp_fpoll;
	bool	_mon__t30_irsp_fpts;
	bool	_mon__t30_irsp_stop;
	bool	_mon__t30_irsp_tsi;
	bool	_mon__t30_irsp_voice;

	bool	_mon__omc_irsp_cfr;
	bool	_mon__omc_irsp_cig;
	bool	_mon__omc_irsp_connect;
	bool	_mon__omc_irsp_fet;
	bool	_mon__omc_irsp_fpoll;
	bool	_mon__omc_irsp_fpts;
	bool	_mon__omc_irsp_rx_page;
	bool	_mon__omc_irsp_voice;

	uint8	_status;

	uint16	_frame_report_state;
	uint16	_frame_report_value;
} monitor_monitor_t;

/* ************************************************************************* */

DEF_DATA(monitor_monitor_t, monitor_monitor)
#define MONITOR_MONITOR_DATA monitor_monitor_t monitor_monitor
#define MONITOR_MONITOR USE_DATA(monitor_monitor)

/* ************************************************************************* */

#define	mon__rsp_done						(MONITOR_MONITOR._mon__rsp_done)

#define	bog__cp_dial_only					(MONITOR_MONITOR._bog__cp_dial_only)
#define	bog__csc_hangup_request				(MONITOR_MONITOR._bog__csc_hangup_request)
#define	bog__dte_fax_rx_done				(MONITOR_MONITOR._bog__dte_fax_rx_done)

#define	fog__inactivity_dtimer_expired		(MONITOR_MONITOR._fog__inactivity_dtimer_expired)
#define	mon__ring_cnt_cleared_timer_expired	(MONITOR_MONITOR._mon__ring_cnt_cleared_timer_expired)
#define	fog__dteif_tx_start					(MONITOR_MONITOR._fog__dteif_tx_start)

#define mon__csc_access_continue			(MONITOR_MONITOR._mon__csc_access_continue)
#define mon__csc_timer_expd					(MONITOR_MONITOR._mon__csc_timer_expd)
#define mon__omc_irsp_csi					(MONITOR_MONITOR._mon__omc_irsp_csi)
#define mon__omc_irsp_dcs					(MONITOR_MONITOR._mon__omc_irsp_dcs)
#define mon__omc_irsp_dis					(MONITOR_MONITOR._mon__omc_irsp_dis)
#define mon__omc_irsp_dtc					(MONITOR_MONITOR._mon__omc_irsp_dtc)
#define mon__omc_irsp_fcon					(MONITOR_MONITOR._mon__omc_irsp_fcon)
#define mon__omc_irsp_stop					(MONITOR_MONITOR._mon__omc_irsp_stop)
#define mon__omc_irsp_tsi					(MONITOR_MONITOR._mon__omc_irsp_tsi)
#define mon__t30_irsp_cfr					(MONITOR_MONITOR._mon__t30_irsp_cfr)
#define mon__t30_irsp_cig					(MONITOR_MONITOR._mon__t30_irsp_cig)
#define mon__t30_irsp_connect				(MONITOR_MONITOR._mon__t30_irsp_connect)
#define mon__t30_irsp_csi					(MONITOR_MONITOR._mon__t30_irsp_csi)
#define mon__t30_irsp_dcs					(MONITOR_MONITOR._mon__t30_irsp_dcs)
#define mon__t30_irsp_dis					(MONITOR_MONITOR._mon__t30_irsp_dis)
#define mon__t30_irsp_dtc					(MONITOR_MONITOR._mon__t30_irsp_dtc)
#define mon__t30_irsp_fcon					(MONITOR_MONITOR._mon__t30_irsp_fcon)
#define mon__t30_irsp_fet					(MONITOR_MONITOR._mon__t30_irsp_fet)
#define mon__t30_irsp_fpoll					(MONITOR_MONITOR._mon__t30_irsp_fpoll)
#define mon__t30_irsp_fpts					(MONITOR_MONITOR._mon__t30_irsp_fpts)
#define mon__t30_irsp_stop					(MONITOR_MONITOR._mon__t30_irsp_stop)
#define mon__t30_irsp_tsi					(MONITOR_MONITOR._mon__t30_irsp_tsi)
#define mon__t30_irsp_voice					(MONITOR_MONITOR._mon__t30_irsp_voice)

#define mon__omc_irsp_cfr					(MONITOR_MONITOR._mon__omc_irsp_cfr)
#define mon__omc_irsp_cig					(MONITOR_MONITOR._mon__omc_irsp_cig)
#define mon__omc_irsp_connect				(MONITOR_MONITOR._mon__omc_irsp_connect)
#define mon__omc_irsp_fet					(MONITOR_MONITOR._mon__omc_irsp_fet)
#define mon__omc_irsp_fpoll					(MONITOR_MONITOR._mon__omc_irsp_fpoll)
#define mon__omc_irsp_fpts					(MONITOR_MONITOR._mon__omc_irsp_fpts)
#define mon__omc_irsp_rx_page				(MONITOR_MONITOR._mon__omc_irsp_rx_page)
#define mon__omc_irsp_voice					(MONITOR_MONITOR._mon__omc_irsp_voice)

#define dp_monitor_status					(MONITOR_MONITOR._status)

#define csc_frame_report_state				(MONITOR_MONITOR._frame_report_state)
#define csc_frame_report_value				(MONITOR_MONITOR._frame_report_value)

/* ************************************************************************* */

#endif /* _MONITOR_MONITORD_H */
