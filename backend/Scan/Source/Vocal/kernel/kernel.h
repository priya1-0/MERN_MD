
/* ************************************************************************* */
/*
 *	kernel.h
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
 *	Module:		KERNEL
 *
 *	This file contains the public declarations for the KERNEL module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 19:54:25  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _KERNEL_KERNEL_H
#define _KERNEL_KERNEL_H

/* ************************************************************************* */

#include "data/knlcfg.h"
#include "data/knlstr.h"

/* ************************************************************************* */

#define TIMER__RESTART_UPDATE						0x7ffe
#define TIMER__EXPIRATION_UPDATE					0x7fff

#define FGBGKERNEL_ANOMALY_BIT__TIMER_OVERFLOW		0x0001

#define FGKERNEL_ANOMALY_BIT__TIMER_OVERFLOW		FGBGKERNEL_ANOMALY_BIT__TIMER_OVERFLOW
#define FGKERNEL_ANOMALY_BIT__EVENT_OVERFLOW		0x0002
#define FGKERNEL_ANOMALY_BIT__REMOTE_EVENT_OVERFLOW	0x0004

#define FG_CURRENT_STATE							(fg_state_list [current_fg_state].current_state)
#define FG_CURRENT_OWNER							(fg_state_list [current_fg_state].state_owner)

#define BGKERNEL_ANOMALY_BIT__TIMER_OVERFLOW		FGBGKERNEL_ANOMALY_BIT__TIMER_OVERFLOW
#define BGKERNEL_ANOMALY_BIT__EVENT_OVERFLOW		0x0002
#define BGKERNEL_ANOMALY_BIT__REMOTE_EVENT_OVERFLOW	0x0004

#define BG_CURRENT_STATE							(bg_state_list [current_bg_state].current_state)
#define BG_CURRENT_OWNER							(bg_state_list [current_bg_state].state_owner)

#define set_event_by_channel(event,channel)			set_event (event)

/* ************************************************************************* */
/*
 *	Define the state machine allocation macros
 */

#define GLOBAL

#define STATE_BEGIN(name)\
\063pragma DATA_SECTION(name,".sect_state");\015\
						   state_action_t name [] = {

#define LOCAL_STATE_BEGIN(name)\
\063pragma DATA_SECTION(name,".sect_state");\015\
						   LOCAL state_action_t name [] = {

/* Optimize order for packing 16 and 32 bit elements */
#define S(e,es,ns) { e, ns, es },

/* ************************************************************************* */

#ifndef STATE_BEGIN
#define STATE_BEGIN(name) state_action_t name [] = {
#endif /* STATE_BEGIN */

#ifndef LOCAL_STATE_BEGIN
#define LOCAL_STATE_BEGIN(name) LOCAL state_action_t name [] = {
#endif /* LOCAL_STATE_BEGIN */

#ifndef STATE_END
#define STATE_END { EVENT__NULL, NULL, NULL } }
#endif /* STATE_END */

#ifndef S
#define S(e,es,ns) { e, es, ns },
#endif /* S */

#ifndef NNS
#define NNS NULL
#endif /* NNS */

#define return_error return

#ifdef set_event
#endif /* set_event */

#ifdef report_status
#endif /* report_status */

/* ************************************************************************* */

/* ************************************************************************* */

/*- MKHEADER Begin -*/

/* Global Routines: */

/* bginit.c */
void bg_kernel_module_reset (void);
void bg_kernel_install (void);

/* bgstates.c */
void bg_stop_current_state (void);
void bg_replace_current_state (state_t next_state);
void bg_start_state (state_t initial_state, state_owner_t state_owner);
void bg_stop_states_by_owner (state_owner_t state_owner);
void bg_stop_state (state_t initial_state, state_owner_t state_owner);

/* bgtasks.c */
void bg_set_current_task_runf (event_t (*runf) (void));
void bg_set_current_task_exitf (void (*exitf) (void));
void bg_start_task (pid__t pid, event_t (*runf) (void));
void bg_remove_task (pid__t pid);
void bg_suspend_task (pid__t pid, event_t event);
void bg_resume_task (pid__t pid);
void bg_kernel_update (void);

/* bgtimers.c */
uint16 bg_read_timer (event_t timer_event_number);
void bg_stop_timer (event_t timer_event_number);
void bg_clear_timer_block (event_t start_timer_event_number, event_t stop_timer_event_number);
void bg_start_timer (event_t timer_event_number, uint16 timer_value);
void bg_timer_update (void);

/* event.c */
void set_event (event_t event);
void set_event_status (event_t event, uint16 value);
void fg_clear_event (event_t event);
void fg_event_update (void);
void bg_clear_event (event_t event);

/* fginit.c */
void fg_kernel_install (void);
void do_nothing (void);

/* fgstates.c */
void fg_stop_current_state (void);
void fg_replace_current_state (state_t next_state);
void fg_start_modulation_state (state_t initial_state);
void fg_start_permanent_state (state_t initial_state, state_owner_t state_owner);
void fg_start_state (state_t initial_state, state_owner_t state_owner);
void fg_stop_states_by_owner (state_owner_t state_owner);
void fg_stop_state (state_t initial_state, state_owner_t state_owner);
void fg_clear_all_states (void);

/* fgthread.c */
void fg_clear_modulation_rx_threads (void);
void fg_clear_modulation_tx_threads (void);
void fg_clear_modulation_threads (void);
void fg_clear_telephony_threads (void);
void fg_clear_data_rx_threads (void);
void fg_clear_data_tx_threads (void);

/* fgthrpkd.c */
void init_thread_components (void);
void insert_thread_component (thread_routine_t routine, ident_t ident);
void remove_thread_component (ident_t ident);
void fg_clear_thread_by_owner (ident_t ident);
void fg_clear_thread (ident_t ident);
void fg_clear_all_threads (void);

/* fgtimers.c */
uint16 fg_read_timer (event_t timer_event_number);
void fg_stop_timer (event_t timer_event_number);
void fg_clear_timer_block (event_t start_timer_event_number, event_t stop_timer_event_number);
void fg_start_ms_timer (event_t timer_event_number, uint16 timer_value);
void fg_start_bit_timer (event_t timer_event_number, uint16 timer_value);
void fg_start_baud_timer (event_t timer_event_number, uint16 timer_value);
void fg_timer_update (void);
void fg_clear_all_timers (void);

/* init.c */
void kernel_module_reset (void);

/* status.c */
void report_status (event_t status, uint16 value);

/*- MKHEADER End -*/


/* ************************************************************************* */

#endif /* _KERNEL_KERNEL_H */
