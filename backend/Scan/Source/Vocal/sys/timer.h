
/* ************************************************************************* */
/*
 *	timer.h
 *
 *	(C) 1994 - 2006 VOCAL Technologies, Ltd.
 *
 *	ALL RIGHTS RESERVED.  PROPRIETARY AND CONFIDENTIAL.
 *
 *	VOCAL Technologies, Ltd.
 *	90A John Muir Drive.
 *	Buffalo, NY  14228
 *
 *	Product:	LANsEND
 *
 *	Module:		SYS
 *
 *	This file contains the functions.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 20:46:45  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _SYS_TIMER_H
#define _SYS_TIMER_H

/* ************************************************************************* */
/*
 *	Define standard time data types
 *
 */

#ifndef  _TIME_T
#define  _TIME_T
typedef uint32 time_t;

struct tm {
	int tm_sec;		/* Seconds after the minute   - [0,59]  */
	int tm_min;		/* Minutes after the hour     - [0,59]  */
	int tm_hour;	/* Hours after the midnight   - [0,23]  */
	int tm_mday;	/* Day of the month           - [1,31]  */
	int tm_mon;		/* Months since January       - [0,11]  */
	int tm_year;	/* Years since 1900                     */
	int tm_wday;	/* Days since Sunday          - [0,6]   */
	int tm_yday;	/* Days since Jan 1st         - [0,365] */
	int tm_isdst;	/* Daylight Savings Time flag           */
};
#endif /* _TIME_T */

/* ************************************************************************* */

/* Software timers
 * There is one of these structures for each simulated timer.
 * Whenever the timer is running, it is on a linked list
 * pointed to by "Timers". The list is sorted in ascending order of
 * expiration, with the first timer to expire at the head. This
 * allows the timer process to avoid having to scan the entire list
 * on every clock tick; once it finds an unexpired timer, it can
 * stop searching.
 *
 * Stopping a timer or letting it expire causes it to be removed
 * from the list. Starting a timer puts it on the list at the right
 * place.
 */
struct timer {
	struct timer *next;	/* Linked-list pointer */
	sint31 duration;		/* Duration of timer, in ticks */
	sint31 expiration;	/* Clock time at expiration */
	void (*func) (void *);	/* Function to call at expiration */
	void *arg;		/* Arg to pass function */
	char state;		/* Timer state */
#define	TIMER_STOP	0
#define	TIMER_RUN	1
#define	TIMER_EXPIRE	2
};
#define	NULLTIMER	(struct timer *)0
#define	MAX_TIME	(sint31)4294967295	/* Max long integer */

/* ************************************************************************* */

#ifndef MSPTICK
#define	MSPTICK		100		/* Milliseconds per tick */
#endif /* MSPTICK */

/* ************************************************************************* */

/* Useful user macros that hide the timer structure internals */

#ifdef USE_MSEC_TIMERS
#define	dur_timer(t)	((t)->duration)
#else /* USE_MSEC_TIMERS */
#define	dur_timer(t)	((t)->duration*MSPTICK)
#endif /* USE_MSEC_TIMERS */

#define	run_timer(t)	((t)->state == TIMER_RUN)

/* ************************************************************************* */

extern void (*Cfunc[])();	/* List of clock tick functions */

/* ************************************************************************* */

/* ************************************************************************* */

#endif /* _SYS_TIMER_H */
