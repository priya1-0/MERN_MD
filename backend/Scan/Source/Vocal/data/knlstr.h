
/* ************************************************************************* */
/*
 *	knlstr.h
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
 *	Module:		DATA
 *
 *	This file contains struct definitions for knl files..
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 19:33:26  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _DATA_KNLSTR_H
#define _DATA_KNLSTR_H

/* ************************************************************************* */

typedef void (*event_service_t) (void);
typedef uint16 state_owner_t;

typedef void (*thread_routine_t) (void);
typedef uint16 ident_t;

typedef uint16 pid__t;
typedef struct task_s {
	event_t	event;
	pid__t	pid;
	event_t (*runf) (void);
	void (*exitf) (void);
} task_t;

typedef const struct state_action_s {
	event_t event;
	const struct state_action_s *next_state;
	event_service_t event_service;
} state_action_t, *state_t;

typedef struct {
	state_t current_state;
	state_t initial_state;
	state_owner_t state_owner;
} state_list_t;

typedef struct {
	uint16 value;
	event_t event;
} timer_list_t;

typedef struct {
	void (*_dispatch) (event_t, uint16);
	bool _dsp_uses_background;
	event_t _bg_event_queue [NUMBER_OF_BG_EVENTS];
	uint16 _bg_svalue_queue [NUMBER_OF_BG_EVENTS];
	int _bg_event_insert;
	int _bg_event_remove;
	state_list_t _bg_state_list [NUMBER_OF_BG_STATES];
	int _number_bg_states;
	int _current_bg_state;
	bool _within_state_update;
	bool _current_bg_state_active;
	task_t _bg_task_table [NUMBER_OF_BG_TASKS];
	int _current_bg_task;
	int _number_bg_tasks;
	bool _within_task_update;
	bool _current_bg_task_active;
	timer_list_t _bg_timer_list [NUMBER_OF_BG_TIMERS];
	int _number_bg_timers;
	uint16 _time_until_next_timer_update;
	event_t _bg_task_event;
} kernel_local_t;

/* ************************************************************************* */
#endif /* _DATA_KNLSTR_H */
