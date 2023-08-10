
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
 *  Module:		DP
 *
 *	This file contains the private parameter declarations/definitions
 *	for the DP module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 18:25:53  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _DP_LOCALD_H
#define _DP_LOCALD_H

#include "dp/dpd.h"
#include "dp/config.h"

/* ************************************************************************* */

typedef struct {
	dpf_t			   	*_fp;
	uint16				_installed_mode;
	uint16				_module_to_install;
	dp_start_state_e	_start_state;
	uint8				_prev_status_code;
	uint8				_status;
	uint16				_start_code;
	uint16				_module_to_start;
	uint8				_no_further_action;
	bool				_line_ready_pending;
	bool				_install_pending;
	bool				_start_continue_pending;
	bool				_install_module_pending;
	bool				_restart_pending;
	bool				_stat_started_pending;
	bool				_within_flag;
} dp_local_t;

/* ************************************************************************* */

DEF_DATA (dp_local_t, dp_local)
#define DP_LOCAL_DATA dp_local_t dp_local
#define DP_LOCAL USE_DATA(dp_local)

/* ************************************************************************* */

#define dp_module_to_install				(DP_LOCAL._module_to_install)
#define dp_start_state						(DP_LOCAL._start_state)
#define dp_prev_status_code					(DP_LOCAL._prev_status_code)
#define dp_status							(DP_LOCAL._status)
#define dp_fp								(DP_LOCAL._fp)
#define dp_installed_mode					(DP_LOCAL._installed_mode)
#define dp_start_code						(DP_LOCAL._start_code)
#define dp_module_to_start					(DP_LOCAL._module_to_start)
#define dp_no_further_action				(DP_LOCAL._no_further_action)
#define dp_line_ready_pending				(DP_LOCAL._line_ready_pending)
#define dp_install_pending			        (DP_LOCAL._install_pending)
#define dp_start_continue_pending		    (DP_LOCAL._start_continue_pending)
#define dp_install_module_pending			(DP_LOCAL._install_module_pending)
#define dp_restart_pending					(DP_LOCAL._restart_pending)
#define dp_stat_started_pending				(DP_LOCAL._stat_started_pending)
#define dp_within_flag						(DP_LOCAL._within_flag)

/* ************************************************************************* */

#endif /* _DP_LOCALD_H */
