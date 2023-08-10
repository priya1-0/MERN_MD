
/* ************************************************************************* */
/*
 *	csc.h
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
 *	This file contains the public declarations for the CSC module.
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

#ifndef _CSC_CSC_H
#define _CSC_CSC_H

#include "csc/macro.h"
#include "csc/cscd.h"
#include "csc/parmd.h"

/* ************************************************************************* */

#define CSC_ICNCT_CODE__CARRIER						0
#define CSC_ICNCT_CODE__PROTOCOL					1
#define CSC_ICNCT_CODE__COMPRESSION					2

/* WARNING - The below defines must match their corresponding result code! */
#define CSC_RC__CARRIER_300							40
#define CSC_RC__CARRIER_1200_75						44
#define CSC_RC__CARRIER_75_1200						45
#define CSC_RC__CARRIER_1200						46
#define CSC_RC__CARRIER_2400						47
#define CSC_RC__CARRIER_4800						48
#define CSC_RC__CARRIER_7200						49
#define CSC_RC__CARRIER_9600						50
#define CSC_RC__CARRIER_12000						51
#define CSC_RC__CARRIER_14400						52
#define CSC_RC__CARRIER_16800						53
#define CSC_RC__CARRIER_19200						54
#define CSC_RC__CARRIER_21600						55
#define CSC_RC__CARRIER_24000						56
#define CSC_RC__CARRIER_26400						57
#define CSC_RC__CARRIER_28800						58

/* WARNING - The below defines must match their corresponding result code! */
#define CSC_RC__COMPRESSION_MNP5					66
#define CSC_RC__COMPRESSION_V42BIS					67
#define CSC_RC__COMPRESSION_NONE					69

/* WARNING - The below defines must match their corresponding result code! */
#define CSC_RC__PROTOCOL_NONE						76
#define CSC_RC__PROTOCOL_LAPM						77
#define CSC_RC__PROTOCOL_MNP						80
#define CSC_RC__PROTOCOL_CELLULAR					81
#define CSC_RC__PROTOCOL_DIRECT		0	/* Notice this is never a result */

/* WARNING - The below defines must match their corresponding result code! */
#define CSC_RC__CONNECT_300							1
#define CSC_RC__CONNECT_600							9
#define CSC_RC__CONNECT_1200_75						23
#define CSC_RC__CONNECT_75_1200						22
#define CSC_RC__CONNECT_1200						5
#define CSC_RC__CONNECT_2400						10
#define CSC_RC__CONNECT_4800						11
#define CSC_RC__CONNECT_7200						13
#define CSC_RC__CONNECT_9600						12
#define CSC_RC__CONNECT_12000						14
#define CSC_RC__CONNECT_14400						15
#define CSC_RC__CONNECT_16800						59
#define CSC_RC__CONNECT_19200						16
#define CSC_RC__CONNECT_21600						61
#define CSC_RC__CONNECT_24000						62
#define CSC_RC__CONNECT_26400						63
#define CSC_RC__CONNECT_28800						64
#define CSC_RC__CONNECT_38400						17
#define CSC_RC__CONNECT_57600						18
#define CSC_RC__CONNECT_115200						19

/* WARNING - The below defines must match command set status defintions! */
#define CSC_RC__DISC_REASON_NORMAL					0
#define CSC_RC__DISC_REASON_CARRIER_LOSS			4
#define CSC_RC__DISC_REASON_V42_NEGO_FAIL			5
#define CSC_RC__DISC_REASON_NO_COMMON_PROTOCOL		9
#define CSC_RC__DISC_REASON_REMOTE_INITIATED		12
#define CSC_RC__DISC_REASON_NO_RESPONSE				13
#define CSC_RC__DISC_REASON_PROTOCOL_VIOLATION		14

#define CSC_FC_STATE__COMMAND						0
#define CSC_FC_STATE__GO							1
#define CSC_FC_STATE__STOP							2

#define CSC_FC_XOFF_STATE__GO						0
#define CSC_FC_XOFF_STATE__WAIT_STOP				1
#define CSC_FC_XOFF_STATE__STOP						2
#define CSC_FC_XOFF_STATE__CRITICAL					3
#define CSC_FC_XOFF_STATE__WAIT_GO					4

#define CSC_FC_CTS_STATE__GO						0
#define CSC_FC_CTS_STATE__WAIT_GO					1
#define CSC_FC_CTS_STATE__STOP						2

/* ************************************************************************* */

#define CSC_BREAK__IGNORE							0x0000
#define CSC_BREAK__DESTRUCTIVE						0x0001
#define CSC_BREAK__EXPEDITED						0x0002
#define CSC_BREAK__SEQUENCED						0x0003

/* ************************************************************************* */

#define FLOW_CONTROL__NONE							0
#define FLOW_CONTROL__XON							1
#define FLOW_CONTROL__RTS							2
#define FLOW_CONTROL__TRANSPARENT					3
#define FLOW_CONTROL__BOTH							4
#define FLOW_CONTROL__BOTH_AND_TRANSPARENT			5

/* ************************************************************************* */

#define CSC_SPK_MON_VOL__BF__MASK					0x0003
#define CSC_SPK_MON_VOL__BF__LOWEST					0x0000
#define CSC_SPK_MON_VOL__BF__LOW					0x0001
#define CSC_SPK_MON_VOL__BF__MED					0x0002
#define CSC_SPK_MON_VOL__BF__HIGH					0x0003
#define CSC_SPK_MON_CTL__BF__MASK					0x000c
#define CSC_SPK_MON_CTL__BF__OFF					0x0000
#define CSC_SPK_MON_CTL__BF__CONNECT				0x0004
#define CSC_SPK_MON_CTL__BF__ALWAYS					0x0008

/* ************************************************************************* */

#define CSC_MODE__ON_HOOK							0
#define CSC_MODE__OFF_HOOK							1
#define CSC_MODE__DATA								2
#define CSC_MODE__FX1								3
#define CSC_MODE__FX2								4
#define CSC_MODE__INDETERMINATE						5

/* ************************************************************************* */

#define CSC_TMON__CMD								0
#define CSC_TMON__ONLINE_CMD						1
#define CSC_TMON__DATA								2

/* ************************************************************************* */

/*- MKHEADER Begin -*/

/* Global States: */

/* command.c */
extern state_action_t csc_reset_delay [];
extern state_action_t csc_idle [];
extern state_action_t csc_cmd_entry [];
extern state_action_t csc_post_cmd_delay [];
extern state_action_t csc_cmd_access [];
extern state_action_t csc_cmd_continue [];
extern state_action_t csc_cmd_rsp [];
extern state_action_t csc_cmd_result [];
extern state_action_t csc_unsolicited_rsp [];

/* dial.c */
extern state_action_t csc_dial_ack [];
extern state_action_t csc_dialing [];
extern state_action_t csc_dial_abort [];
extern state_action_t csc_dial_fail_access [];

/* dmdp.c */
extern state_action_t csc_dmdp_access [];
extern state_action_t csc_dmdp_ack [];
extern state_action_t csc_dmdp_connecting [];
extern state_action_t csc_dmdp_irsp_access [];
extern state_action_t csc_dmdp_irsp [];
extern state_action_t csc_dmdp_connect_rsp [];
extern state_action_t csc_dmdp_online [];
extern state_action_t csc_ties_ok_rsp [];
extern state_action_t csc_ties_idle [];
extern state_action_t csc_ties_connect_rsp [];

/* hook.c */
extern state_action_t csc_on_hook [];
extern state_action_t csc_off_hook [];

/* shutdown.c */
extern state_action_t csc_disconnect_ack [];
extern state_action_t csc_disconnecting [];
extern state_action_t csc_on_hook_rsp [];
extern state_action_t csc_halting [];
extern state_action_t csc_halt_rsp [];
extern state_action_t csc_reset_cmd_delay [];
extern state_action_t csc_wait_for_reset [];

/* Global Routines: */

/* csc.c */
void csc_state_print (uint16 num);
void csc_pass_thru_state_print (uint16 num);
void csc_module_reset (void);
void csc_start (void);
void csc_10ms_timer (void);
void csc_poll (void);
void csc_mode_transition (uint16 new_mode);
uint16 str_to_bit_rate (char *str);
void csc_echo_put_du (uint16 du);
uint16 csc_echo_get_du (void);
void csc_echo_clear (void);
void csc_speaker_monitor_control (void);

/* fc.c */
void csc_fc_cts_on (void);
void csc_fc_set_parms (void);

/* itel.c */
bool itel_set (uint16 code);
void itel_bind (void);

/* misc.c */
void csc_sm_start (void);

/*- MKHEADER End -*/


/* ************************************************************************* */

#endif /* _CSC_CSC_H */
