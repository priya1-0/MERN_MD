
/* ************************************************************************* */
/*
 *	dpd.h
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
 *	Module:		DP
 *
 *	This file contains the public parameter declarations/definitions for
 *	the DP module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 18:25:54  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _DP_DPD_H
#define _DP_DPD_H

/* ************************************************************************* */

typedef struct {
	bool	_timer_service_en;
	uint16	_suspended;
	uint16	_idled;
	uint16	_det_autorel_result_code;
	uint16	_nego_failure_result_code;
	uint16	_adp_result_code;

	bool	_tx_char_seen;
	bool	_rx_char_seen;
	bool	_buffered_rx_buffer_active;
	bool	_within_detect;

} dp_global_t;

/* ************************************************************************* */

DEF_DATA (dp_global_t, dp_global)
#define DP_GLOBAL_DATA dp_global_t dp_global
#define DP_GLOBAL USE_DATA(dp_global)

/* ************************************************************************* */

#define dp_timer_service_en					(DP_GLOBAL._timer_service_en)
#define dp_suspended						(DP_GLOBAL._suspended)
#define dp_idled							(DP_GLOBAL._idled)
#define dp_det_autorel_result_code			(DP_GLOBAL._det_autorel_result_code)
#define dp_nego_failure_result_code			(DP_GLOBAL._nego_failure_result_code)
#define dp_adp_result_code					(DP_GLOBAL._adp_result_code)
#define dp_tx_char_seen						(DP_GLOBAL._tx_char_seen)
#define dp_rx_char_seen						(DP_GLOBAL._rx_char_seen)
#define dp_buffered_rx_buffer_active		(DP_GLOBAL._buffered_rx_buffer_active)
#define dp_within_detect					(DP_GLOBAL._within_detect)

/* ************************************************************************* */

#endif /* _DP_DPD_H */
