
/* ************************************************************************* */
/*
 *	state.h
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
 *	This file contains definitions for the states.
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

#ifndef _CSC_STATE_H
#define _CSC_STATE_H

#include "csc/stated.h"

/* ************************************************************************* */

extern state_action_t csc_monitor [];

extern state_action_t csc_cmd_access [];
extern state_action_t csc_cmd_continue [];
extern state_action_t csc_cmd_entry [];
extern state_action_t csc_cmd_result [];
extern state_action_t csc_cmd_rsp [];
extern state_action_t csc_dialing [];
extern state_action_t csc_dial_abort [];
extern state_action_t csc_dial_fail_access [];
extern state_action_t csc_dial_ack [];
extern state_action_t csc_disconnecting [];
extern state_action_t csc_disconnect_ack [];
extern state_action_t csc_dmdp_access [];
extern state_action_t csc_dmdp_ack [];
extern state_action_t csc_dmdp_connecting [];
extern state_action_t csc_dmdp_connect_rsp [];
extern state_action_t csc_dmdp_irsp [];
extern state_action_t csc_dmdp_irsp_access [];
extern state_action_t csc_dmdp_online [];
extern state_action_t csc_fx1_cmd [];
extern state_action_t csc_fx1_cmd_ack [];
extern state_action_t csc_fx1_connect_rsp [];
extern state_action_t csc_fx1_rx [];
extern state_action_t csc_fx1_rx_halt [];
extern state_action_t csc_fx1_rx_done [];
extern state_action_t csc_fx1_rx_abort [];
extern state_action_t csc_fx1_tx [];
extern state_action_t csc_halting [];
extern state_action_t csc_halt_rsp [];
extern state_action_t csc_idle [];
extern state_action_t csc_nvm_access [];
extern state_action_t csc_off_hook [];
extern state_action_t csc_on_hook [];
extern state_action_t csc_on_hook_rsp [];
extern state_action_t csc_post_cmd_delay [];
extern state_action_t csc_reset_cmd_delay [];
extern state_action_t csc_reset_delay [];
extern state_action_t csc_t30_halting [];
extern state_action_t csc_ties_connect_rsp [];
extern state_action_t csc_ties_idle [];
extern state_action_t csc_ties_ok_rsp [];
extern state_action_t csc_unsolicited_rsp [];
extern state_action_t csc_wait_for_reset [];
extern state_action_t csc_fax_detect_irsp [];
extern state_action_t fx2_cmd [];
extern state_action_t fx2_cmd_ack [];
extern state_action_t fx2_connect_rsp [];
extern state_action_t fx2_frame_report [];
extern state_action_t fx2_disconnecting [];
extern state_action_t fx2_hangup_access [];
extern state_action_t fx2_hangup_ok_rsp [];
extern state_action_t fx2_hangup_rsp [];
extern state_action_t fx2_irsp [];
extern state_action_t fx2_irsp_access [];
extern state_action_t fx2_rx [];
extern state_action_t fx2_rx_abort [];
extern state_action_t fx2_rx_stopped [];
extern state_action_t fx2_rx_wait_dc2 [];
extern state_action_t fx2_shutdown_wait [];
extern state_action_t fx2_tx [];
extern state_action_t fx2_tx_abort [];
extern state_action_t fx2_tx_stopped [];

/* ************************************************************************* */

#endif /* _CSC_STATE_H */
