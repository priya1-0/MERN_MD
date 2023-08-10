
/* ************************************************************************* */
/*
 *	timer.c
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
 *	This file contains the general purpose software timer functions.
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

#include "system/system.h"

#include "lansend/global.h"

#include "net/net.h"
#include "sys/sys.h"
#include "dev/dev.h"

#include "ip/ip.h"

#include "sys/local.h"
#include "include/test.h"

#include "lansend/lansend.h"

#include "sys/sys.h"

/* ************************************************************************* */

sint31 Clock_ticks = 0;
static uint32 clock_ms = 0;
static uint32 clock_sec = 0;
static uint16 clock_sec_fract = 0;
int Tick = 0;

int Tick_10msec = 0;

time_t Time_sec = (time_t) 0L;

/* ************************************************************************* */

/* Head of running timer chain.
 * The list of running timers is sorted in increasing order of expiration;
 * i.e., the first timer to expire is always at the head of the list.
 */
static struct timer *Timers = NULLTIMER;

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

ENTRY void
timer_init (void)
{
	Clock_ticks = 0;
	Tick = 0;
	clock_ms = 0L;
	clock_sec = 0L;
	clock_sec_fract = 0;
	Time_sec = (time_t) 0L;
	Timers = NULLTIMER;
}

/* ************************************************************************* */

#ifdef DO_OS_LINUX_UNUSED
#include <pthread.h>

ENTRY void *
ata_timer_start_pthread (void *p)
{
	print_info (("Starting ATA Timer\n"));
	timerproc (0, NULL, NULL);

	print_info (("Ending ATA Timer\n"));
	pthread_exit (NULL);

	/* Should never reach this point */
	return NULL;
}
#endif /* DO_OS_LINUX_UNUSED */

/* ************************************************************************* */

/* Process that handles clock ticks */
ENTRY void
timerproc (int i, void *v1, void *v2)
{
	register struct timer *t;
	register struct timer *expired;

	for (;;) {
		void (**vf) (void);
		int tmp;

		/* Atomic read and decrement of Tick */
		for (;;) {
			network_nested_interrupt_disable ();
			tmp = Tick;
			if (tmp != 0) {
				Tick--;
				network_nested_interrupt_restore ();
				break;
			}
			network_nested_interrupt_restore ();
			pwait (&Tick);
		}

		if (network_nested_interrupt_read_depth ()) {
			network_nested_interrupt_forced_enable ();
			print_error (("timerproc() - ints were off!\n"));
		}

		/* Call the functions listed in config.c */
		for (vf = Cfunc;*vf != NULL;vf++)
			(*vf) ();

		pwait(NULL);	/* Let them all do their writes */

		if (Timers == NULLTIMER)
			continue;	/* No active timers, all done */

		/* Initialize null expired timer list */
		expired = NULLTIMER;

		/* Move expired timers to expired list. Note use of
		 * subtraction and comparison to zero rather than the
		 * more obvious simple comparison; this avoids
		 * problems when the clock count wraps around.
		 */
#ifdef USE_MSEC_TIMERS
		while (Timers != NULLTIMER && (clock_ms - Timers->expiration) >= 0) {
#else /* USE_MSEC_TIMERS */
		while (Timers != NULLTIMER && (Clock_ticks - Timers->expiration) >= 0) {
#endif /* USE_MSEC_TIMERS */
			if (Timers->next == Timers) {
				print_error (("timerproc() - Timer loop at %lx\n", (sint31) Timers));
			}
			/* Save Timers since stop_timer will change it */
			t = Timers;
			stop_timer (t);
			t->state = TIMER_EXPIRE;
			/* Add to expired timer list */
			t->next = expired;
			expired = t;
		}
		/* Now go through the list of expired timers, removing each
		 * one and kicking the notify function, if there is one
		 */
		while ((t = expired) != NULLTIMER) {
			expired = t->next;
			if (t->func) {
				(*t->func) (t->arg);
			}
		}
		pwait(NULL);	/* Let them run before handling more ticks */
	}
}

/* ************************************************************************* */

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

/* Start a timer */
ENTRY void
start_timer (struct timer *t)
{
	register struct timer *tnext;
	struct timer *tprev = NULLTIMER;

	if (t == NULLTIMER)
		return;
	if (t->state == TIMER_RUN)
		stop_timer (t);
	if (t->duration == 0)
		return;		/* A duration value of 0 disables the timer */

#ifdef USE_MSEC_TIMERS
	t->expiration = clock_ms + t->duration;
#else /* USE_MSEC_TIMERS */
	t->expiration = Clock_ticks + t->duration;
#endif /* USE_MSEC_TIMERS */
	t->state = TIMER_RUN;

	/* Find right place on list for this guy. Once again, note use
	 * of subtraction and comparison with zero rather than direct
	 * comparison of expiration times.
	 */
	for (tnext = Timers;tnext != NULLTIMER;tprev = tnext, tnext = tnext->next) {
		if ((tnext->expiration - t->expiration) >= 0)
			break;
	}
	/* At this point, tprev points to the entry that should go right
	 * before us, and tnext points to the entry just after us. Either or
	 * both may be null.
	 */
	if (tprev == NULLTIMER)
		Timers = t;		/* Put at beginning */
	else
		tprev->next = t;

	t->next = tnext;
}

/* ************************************************************************* */

/* Stop a timer */
ENTRY void
stop_timer (struct timer *timer)
{
	register struct timer *t;
	struct timer *tlast = NULLTIMER;

	if (timer == NULLTIMER || timer->state != TIMER_RUN)
		return;

	/* Verify that timer is really on list */
	for (t = Timers;t != NULLTIMER;tlast = t, t = t->next)
		if (t == timer)
			break;

	if (t == NULLTIMER)
		return;		/* Should probably panic here */

	/* Delete from active timer list */
	if (tlast != NULLTIMER)
		tlast->next = t->next;
	else
		Timers = t->next;	/* Was first on list */

	t->state = TIMER_STOP;
}

/* ************************************************************************* */

/* Return milliseconds remaining on this timer */
ENTRY sint31
read_timer (struct timer *t)
{
	sint31 remaining;

	if (t == NULLTIMER || t->state != TIMER_RUN)
		return 0;
#ifdef USE_MSEC_TIMERS
	remaining = t->expiration - clock_ms;
#else /* USE_MSEC_TIMERS */
	remaining = t->expiration - Clock_ticks;
#endif /* USE_MSEC_TIMERS */
	if (remaining <= 0)
		return 0;	/* Already expired */
	else
#ifdef USE_MSEC_TIMERS
		return remaining;
#else /* USE_MSEC_TIMERS */
		return remaining * MSPTICK;
#endif /* USE_MSEC_TIMERS */
}

/* ************************************************************************* */

ENTRY void
set_timer (struct timer *t, sint31 interval)
{
	if (t == NULLTIMER)
		return;
	/* Round the interval up to the next full tick, and then
	 * add another tick to guarantee that the timeout will not
	 * occur before the interval is up. This is necessary because
	 * we're asynchronous with the system clock.
	 */
	if (interval != 0) {
#ifdef USE_MSEC_TIMERS
		t->duration = interval + MSPTICK;
#else /* USE_MSEC_TIMERS */
		t->duration = (interval + MSPTICK - 1) / MSPTICK;
#endif /* USE_MSEC_TIMERS */
	} else {
		t->duration = 0;
	}
}

/* ************************************************************************* */

/* Delay process for specified number of milliseconds.
 * Normally returns 0; returns -1 if aborted by alarm.
 */
ENTRY int
pause (sint31 ms)
{
	int val;

	if (Curproc == NULLPROC || ms == 0)
		return 0;
	alarm (ms);
	/* The actual event doesn't matter, since we'll be alerted */
	while (Curproc->alarm.state == TIMER_RUN) {
		if ((val = pwait (Curproc)) != 0)
			break;
	}
	alarm(0L); /* Make sure it's stopped, in case we were killed */
	return (val == EALARM) ? 0 : -1;
}

/* ************************************************************************* */

LOCAL void
t_alarm (void *x)
{
	alert ((struct proc *) x, EALARM);
}

/* ************************************************************************* */

/* Send signal to current process after specified number of milliseconds */
ENTRY void
alarm (sint31 ms)
{
	if (Curproc != NULLPROC) {
		set_timer (&Curproc->alarm, ms);
		Curproc->alarm.func = t_alarm;
		Curproc->alarm.arg = (char *) Curproc;
		start_timer (&Curproc->alarm);
	}
}

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

/*
 *	Called from the MDM BG process for each timer tick received from FG
 */

ENTRY void
ctick (void)
{
	if (++Tick_10msec >= 10) {		/* 10 cticks (@10 ms) occur per LANsEND Tick (@100 ms) */
		Tick_10msec = 0;
		Tick++;
		psignal (&Tick, 1);
	}
}

/* ************************************************************************* */

/* Called from the timer process on every tick. NOTE! This function
 * can NOT be called at interrupt time because it calls the BIOS
 */
ENTRY void
pctick (void)
{
	Clock_ticks++;			/* Clock_ticks is always incremented by one */

	clock_ms += MSPTICK;
	clock_sec_fract += MSPTICK;
	if (clock_sec_fract >= 1000) {
		clock_sec_fract -= 1000;
		clock_sec++;
		Time_sec++;			/* Used for time since Jan 1, 1970 */
	}
}

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

/* Return time since startup in milliseconds. If the system has an
 * 8254 clock chip (standard on ATs and up) then resolution is improved
 * below 55 ms (the clock tick interval) by reading back the instantaneous
 * value of the counter and combining it with the global clock tick counter.
 * Otherwise 55 ms resolution is provided.
 *
 * Reading the 8254 is a bit tricky since a tick could occur asynchronously
 * between the two reads. The tick counter is examined before and after the
 * hardware counter is read. If the tick counter changes, try again.
 * Note: the hardware counter counts down from 65536.
 */
ENTRY sint31
msclock (void)
{

	return clock_ms + Tick_10msec * 10;		/* Adjust the clock by the subticks */
}

/* ************************************************************************* */

/* Return clock in seconds */
ENTRY sint31
secclock (void)
{
	return clock_sec;
}

/* ************************************************************************* */

#ifdef DO_COMPILER_TI
#pragma FUNC_IS_SYSTEM (time)
#endif /* DO_COMPILER_TI */

/* Return time of day in seconds since Jan. 1, 1970 */
/* Add 2,208,988,800 seconds to convert to seconds since Jan. 1, 1900 */
ENTRY time_t
time (time_t *timer)
{
	if (timer != NULL)
		*timer = Time_sec;
	return Time_sec;
}

/* ************************************************************************* */

/* Set the time of day in seconds since Jan. 1, 1970 */
ENTRY int
stime (time_t *timer)
{
	Time_sec = *timer;

	return 0;
}

/* ************************************************************************* */
