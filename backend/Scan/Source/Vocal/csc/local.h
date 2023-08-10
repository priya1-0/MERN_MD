
/* ************************************************************************* */
/*
 *	local.h
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
 *	This file contains the private declarations for the CSC module.
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

#ifndef _CSC_LOCAL_H
#define _CSC_LOCAL_H

#include "csc/locald.h"
#include "csc/csc.h"
#include "csc/response.h"
#include "csc/dte.h"
#include "csc/state.h"
#include "csc/time.h"
#include "csc/monitor.h"
#include "csc/macro.h"

/* ************************************************************************* */

#define	TIES_STATE__LOOK_FOR_1ST		0
#define	TIES_STATE__LOOK_FOR_2ND		1
#define	TIES_STATE__LOOK_FOR_3RD		2
#define	TIES_STATE__LOOK_FOR_A			3
#define	TIES_STATE__LOOK_FOR_T			4
#define	TIES_STATE__LOOK_FOR_NONDIGIT	5
#define	TIES_STATE__LOOK_FOR_DIGIT1		6
#define	TIES_STATE__LOOK_FOR_DIGIT2		7
#define	TIES_STATE__LOOK_FOR_DIGIT3		8
#define	TIES_STATE__SAW_AMPERSAND		9
#define	TIES_STATE__SAW_ASTERISK		10

#define CSC_REPORT_CODE__CIG	0
#define CSC_REPORT_CODE__CSI	1
#define CSC_REPORT_CODE__TSI	2
#define CSC_REPORT_CODE__DIS	3
#define CSC_REPORT_CODE__DCS	4
#define CSC_REPORT_CODE__DTC	5
#define CSC_REPORT_CODE__FET	6
#define CSC_REPORT_CODE__FPTS	7

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/*- MKHEADER Begin -*/

/* Module Routines: */

/* command.c */
void e_reset_delay (void);
void e_idle__b (void);
void e_idle__c (void);
void e_idle__d (void);
void e_idle__common (void);
void e_cmd_entry__b (void);
void e_cmd_continue (void);
void e_cmd_result__e (void);
void e_cmd_result__e_ok (void);
void e_cmd_result__ok (void);
void e_cmd_result__error (void);
void e_cmd_result__k_no_carrier (void);
void e_cmd_result__k_fcerror (void);
void e_cmd_result__k_ok (void);
void e_cmd_result__i_error (void);
void e_cmd_result__i_ok (void);
void e_cmd_result__j_rx_frame (void);
void e_cmd_result__j_nc (void);
void sfl_csc_reset_request (void);
void sfl_csc_hangup_request (void);
void sfl_omc_rsp_on_hook (void);
void sfl_omc_rsp_ok (void);
void sfl_dteif_at_prefix_seen (void);
void sfl_dteif_repeat_prev_cmd (void);
void sfl_csc_s3_received (void);
void sfl_dte_char_seen (void);
void sfl_omc_irsp_carrier (void);
void sfl_omc_irsp_compression (void);
void sfl_omc_irsp_protocol (void);
void sfl_omc_rsp_connect (void);
void sfl_omc_rsp_error (void);
void sfl_omc_rsp_rx_frame (void);
void sfl_omc_rsp_no_carrier (void);
void csc_accept_advanced_commands (void);
void sr_cmd_process__x (void);
void sr_cmd_process__y (void);
void sr_cmd_process__z (void);
void csc_fclass_change (void);

/* dial.c */
void e_dial_ack__a (void);
void e_dial_ack (void);

/* dmdp.c */
void e_dmdp_access__a (void);
void e_dmdp_access__b (void);

/* fc.c */
void csc_fc_check (uint16 rsp_code);
void csc_fc_go (void);
void csc_fc_stop (void);
void csc_fc_critical_stop (void);
void csc_fc_cts_off (void);

/* hook.c */
void e_on_hook (void);
void e_off_hook (void);

/* itel.c */
void itel_csc_bind (void);

/* shutdown.c */
void e_disconnect_ack__a (void);
void e_disconnect_ack__b (void);
void e_disconnect_ack__c (void);
void e_disconnect_ack__f_nc (void);
void e_disconnect_ack__h_nc (void);
void e_disconnect_ack__i_nc (void);
void e_disconnect_ack__ok (void);
void e_disconnect_ack__null (void);
void e_disconnect_ack__no_carrier (void);
void e_disconnecting__a (void);
void e_on_hook_rsp__a (void);
void e_on_hook_rsp__b (void);
void e_on_hook_rsp__f_nc (void);
void e_on_hook_rsp__i_error (void);
void e_on_hook_rsp__k_nc (void);
void e_on_hook_rsp__no_carrier (void);
void e_on_hook_rsp__error (void);
void e_halting__a (void);
void e_halting__d (void);
void e_halting__f_no_carrier (void);
void e_halting__h_null (void);
void e_halting__i_null (void);
void e_halting__j_ok (void);
void e_halting__j_error (void);
void e_halting__error (void);
void e_halting__null (void);
void e_halting__ok (void);
void e_halting__no_carrier (void);
void e_halting__common (void);

/* Local States: */

/* monitor.c */

#ifdef csc_monitor_c
extern state_action_t csc_monitor [];
#endif /* csc_monitor_c */

/* Local Routines: */

/* command.c */

#ifdef csc_command_c
static void e_idle__a (void);
static void e_cmd_entry__a (void);
static void e_post_cmd_delay (void);
static void e_cmd_access__a (void);
static void e_cmd_access__b (void);
static void e_cmd_rsp__a (void);
static void e_cmd_rsp__b (void);
static void l_cmd_rsp (void);
static void e_cmd_result__null (void);
static void e_cmd_result__k_common (void);
static void e_cmd_result__k_disc (void);
static void l_cmd_result (void);
static void deferred_processing (void);
static void e_unsolicited_rsp__error (void);
static void e_unsolicited_rsp__ring_a (void);
static void e_unsolicited_rsp__ring_b (void);
static void itel_ring_duration_passed (void);
static void e_unsolicited_rsp__ring_common (void);
static void l_unsolicited_rsp (void);
static void sfl_omc_rsp_ring (void);
static void sfl_csc_autoanswer_req (void);
static void sfl_dte_nochar_interval_timer (void);
static void sr_cmd_process__a (void);
static void sr_cmd_process__b (void);
static void sr_cmd_process__c (void);
static void sr_cmd_process__e (void);
static void sr_cmd_process__common (void);
#endif /* csc_command_c */

/* csc.c */

#ifdef csc_csc_c
static void csc_warm_reset (void);
#endif /* csc_csc_c */

/* dial.c */

#ifdef csc_dial_c
static void e_dialing (void);
static void l_csc_dialing (void);
static void e_dial_abort__busy (void);
static void e_dial_abort__delayed (void);
static void e_dial_abort__no_answer (void);
static void e_dial_abort__no_dialtone (void);
static void e_dial_fail_access (void);
#endif /* csc_dial_c */

/* dmdp.c */

#ifdef csc_dmdp_c
static void e_dmdp_access__c (void);
static void e_dmdp_ack (void);
static void e_dmdp_connecting__a (void);
static void e_dmdp_connecting__b (void);
static void e_dmdp_irsp_access__carrier (void);
static void e_dmdp_irsp_access__protocol (void);
static void e_dmdp_irsp_access__compression (void);
static void e_dmdp_irsp_access__b (void);
static void e_dmdp_irsp (void);
static void e_dmdp_irsp__data (void);
static void e_dmdp_connect_rsp (void);
static void e_dmdp_online__a (void);
static void e_dmdp_online__b (void);
static void online_escape_timer_start (void);
static void online_escape_timer_stop (void);
static void e_ties_ok_rsp (void);
static void e_ties_idle (void);
static void e_ties_connect_rsp (void);
#endif /* csc_dmdp_c */

/* dte.c */

#ifdef csc_dte_c
static void dte_adjust_pointers_for_ties_cmd (void);
static void dte_ties_abandon (uint16 du);
#endif /* csc_dte_c */

/* monitor.c */

#ifdef csc_monitor_c
static void set_fc_pulse_expired (void);
static void set_ring_cnt_cleared_expired (void);
static void sr_frame_report (void);
static void sr_frame_detail_report (void);
#endif /* csc_monitor_c */

/* response.c */

#ifdef csc_response_c
static void rspgen_connect (void);
static void rspgen_ok (void);
static void rspgen_error (void);
static void rspgen_ring (void);
static void rspgen_no_carrier (void);
static void rspgen_data (void);
static void rspgen_fax (void);
static void rspgen_fcerror (void);
static void rspgen_dial_fail (void);
static void rspgen_initial_data_connect (void);
static void rspgen_online_data_connect (void);
static void rspgen_ties_fail_connect (void);
static void append_protocol (void);
static void append_compression (void);
static void append_modulation (void);
static void append_voice (void);
static void append_dte_speed (void);
static void append_carrier (uint16 type);
static void rspgen_intermediate_carrier (void);
static void rspgen_intermediate_protocol (void);
static void rspgen_intermediate_network (void);
static void rspgen_intermediate_compression (void);
static void rspgen_generic_connect (void);
#endif /* csc_response_c */

/* shutdown.c */

#ifdef csc_shutdown_c
static void e_disconnect_ack__error (void);
static void e_disconnect_ack__common (void);
static void e_disconnecting (void);
static void e_on_hook_rsp__ok (void);
static void e_on_hook_rsp__null (void);
static void e_on_hook_rsp__common (void);
static void e_halt_rsp__a (void);
static void e_halt_rsp__b (void);
static void e_halt_rsp__c (void);
static void e_reset_cmd_delay__a (void);
static void e_reset_cmd_delay__b (void);
static void e_wait_for_reset__a (void);
static void e_wait_for_reset__b (void);
#endif /* csc_shutdown_c */

/*- MKHEADER End -*/


/* ************************************************************************* */

#endif /* _CSC_LOCAL_H */
