
/* ************************************************************************* */
/*
 *	kernel.c
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
 *	This file contains the non pre - empting synchronization kernel functions.
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
#include "pump/pump.h"

#include "lansend/daemon.h"

#include "include/test.h"

/* ************************************************************************* */

int Stkchk = 0;

struct proc emptyproc = {0};

struct proc *Curproc = &emptyproc;	/* Currently running process */
struct proc *Rdytab = NULLPROC;		/* Processes ready to run (not including curproc) */
struct proc *Waittab[PHASH];		/* Waiting process list */	/* Initialized at run-time in network_init */
struct proc *Susptab = NULLPROC;	/* Suspended processes */
static struct mbuf *Killq = NULLBUF;
struct ksig Ksig;					/* Initialized at run-time in network_init */
void *lastevent;

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

ENTRY void
kernel_init (void)
{
	int i;

	Stkchk = 0;

	Curproc = &emptyproc;	/* Currently running process */
	Rdytab = NULLPROC;		/* Processes ready to run (not including curproc) */
	Susptab = NULLPROC;	/* Suspended processes */
	Killq = NULLBUF;
	lastevent = NULL;

	for (i = 0; i < PHASH; i++) {
		Waittab[i] = NULLPROC;
	}
	memset ((void *) &Ksig, (sizeof (struct ksig)), 0);
}

/* ************************************************************************* */

/* Create a process descriptor for the main function. Must be actually
 * called from the main function, and must be called before any other
 * tasking functions are called !
 *
 * Note that standard I / O is NOT set up here.
 */
ENTRY struct proc *
mainproc (char *name)
{
	register struct proc *pp;

	/* Create process descriptor */
	pp = (struct proc *) callocw (1, sizeof (struct proc));

	/* Create name */
	pp->name = strdup (name);

	pp->stack = NULL;
	pp->stksize = 0;
	pp->sysstack = NULL;
	pp->sysstksize = 0;

	/* no previous sockets */
	pp->input = NULLFILE;
	pp->output = NULLFILE;

	/* Make current */
	pp->state = READY;
	Curproc = pp;
	return pp;
}

/* ************************************************************************* */

/* Create a new, ready process and return pointer to descriptor.
 * The general registers are not initialized, but optional args are pushed
 * on the stack so they can be seen by a C function.
 */
ENTRY struct proc *
newproc (char *name, unsigned int stksize, void (*pc) (int, void*, void*), int iarg, void *parg1, void *parg2, int freeargs)
{
	register struct proc *pp;
	struct session *sp;
	int i;
	stksize += 0;

	if (Stkchk)
		chkstk ();

	/* Create process descriptor */
	pp = (struct proc *) callocw (1, sizeof (struct proc));

	/* Create name */
	pp->name = strdup (name);

	/* Allocate stack */
	pp->stksize = stksize;
	if ((pp->stack = (uint16 *) malloc (sizeof(uint16) * stksize)) == NULL) {
		free (pp->name);
		free ((char *) pp);
		return NULLPROC;
	}
	/* Initialize stack for high-water check */
	for (i = 0;i < stksize;i++)
		pp->stack[i] = STACKPAT;

	/* Allocate system stack */
	pp->sysstksize = stksize / 2;
	if ((pp->sysstack = (uint16 *) malloc (sizeof (uint16) *pp->sysstksize)) == NULL) {
		free (pp->name);
		free (pp->stack);
		free ((char *) pp);
		return NULLPROC;
	}
	/* Initialize stack for high-water check */
	for (i = 0;i < pp->sysstksize;i++)
		pp->sysstack[i] = STACKPAT;

	/* Do machine-dependent initialization of stack */
	psetup (pp, iarg, parg1, parg2, (void (*) ()) pc);

	if (freeargs)
		pp->flags |= P_FREEARGS;
	pp->iarg = iarg;
	pp->parg1 = parg1;
	pp->parg2 = parg2;

	/* Inherit creator's session, input and output sockets */
	pp->session = (struct session *) Curproc->session;
	sp = pp->session;
	sp->processes++;

	pp->input = fdup (stdin);
	pp->output = fdup (stdout);

	/* Add to ready process table */
	pp->state = READY;
	addproc (pp);
	return pp;
}

/* ************************************************************************* */

/* Free resources allocated to specified process. If a process wants to kill
 * itself, the reaper is called to do the dirty work. This avoids some
 * messy situations that would otherwise occur, like freeing your own stack.
 */
ENTRY void
killproc (struct proc *pp)
{
	struct session *sp;
	char **argv;

	if (pp == NULLPROC)
		return;

	if ((pp->stack == NULL) && (pp->stksize == 0)) {
		/* don't kill the process created by mainproc, it will be cleaned up by dspbios */
	}
	else
	{
		/* Don't check the stack here! Will cause infinite recursion if
		 * called from a stack error
		 */
		if (pp == Curproc)
			killself();	/* Doesn't return */
	}

	/* kill session */
	if ((sp = (struct session *) pp->session) != NULLSESSION
	  && sp->proc0 == pp) {
		freesession (sp);
	}

	/* Close any open sockets */
	fclose (pp->input);
	fclose (pp->output);

	/* freesock(pp); is this really needed anymore? */

	/* Stop alarm clock in case it's running */
	stop_timer (&pp->alarm);

	/* Alert everyone waiting for this proc to die */
	psignal (pp, 0);

	/* Remove from appropriate table */
	delproc (pp);

	/* Free allocated memory resources */
	if (pp->flags & P_FREEARGS) {
		argv = (char **) pp->parg1;
		while (pp->iarg-- != 0)
			free (*argv++);
		free (pp->parg1);
	}

	free (pp->name);
	free (pp->stack);
	free (pp->sysstack);
	free ((char *) pp);
}

/* ************************************************************************* */

/* Terminate current process by sending a request to the killer process.
 * Automatically called when a process function returns. Does not return.
 */
ENTRY void
killself (void)
{
	register struct mbuf *bp;

	bp = ambufw (sizeof (Curproc));
	bp->cnt = sizeof (Curproc);
	memcpy (bp->data, (char *) &Curproc, sizeof (Curproc));
	enqueue (&Killq, bp);

	/* "Wait for me; I will be merciful and quick." */
	for (;;)
		pwait (NULL);
}

/* ************************************************************************* */

/* Terminate all processes */
ENTRY void
killall (void)
{
	int i;

	while (Rdytab != NULLPROC)
		killproc (Rdytab);

	for (i = 0; i < PHASH; i++)
		while (Waittab[i] != NULLPROC)
			killproc (Waittab[i]);

	while (Susptab != NULLPROC)
		killproc (Susptab);

	killproc (Curproc);
}

/* ************************************************************************* */

/* Process used by processes that want to kill themselves */
ENTRY void
killer (int i, void *v1, void *v2)
{
	struct proc *pp;
	struct mbuf *bp;

	for (;;) {
		while (Killq == NULLBUF)
			pwait (&Killq);
		bp = dequeue (&Killq);
		pullup (&bp, (char *) &pp, sizeof (pp));
		free_p (bp);
		if (pp != Curproc)	/* We're immortal */
			killproc (pp);
	}
}

/* ************************************************************************* */

/* Inhibit a process from running */
ENTRY void
suspend (struct proc *pp)
{
	if (pp == NULLPROC)
		return;
	if (pp == Curproc) {
		pp->state |= SUSPEND;
		pwait (NULL);
	} else {
		delproc(pp);	/* Running process isn't on any list */
		pp->state |= SUSPEND;
		addproc (pp);
	}
}

/* ************************************************************************* */

/* Restart suspended process */
ENTRY void
resume (struct proc *pp)
{
	if (pp == NULLPROC)
		return;
	delproc(pp);	/* Can't be Curproc! */
	pp->state &= ~SUSPEND;
	addproc (pp);
}

/* ************************************************************************* */

/* Set process priority */
ENTRY void
setpriority (struct proc *pp, sint15 priority)
{
	if (pp == NULLPROC)
		return;
	if (pp == Curproc) {
		pp->priority = priority;
	}
	else {
		delproc (pp);	/* Running process isn't on any list */
		pp->priority = priority;
		addproc (pp);
	}
}

/* ************************************************************************* */

/* Wakeup waiting process, regardless of event it's waiting for. The process
 * will see a return value of "val" from its pwait() call. Must not be
 * called from an interrupt handler.
 */
ENTRY void
alert (struct proc *pp, int val)
{
	if (pp == NULLPROC)
		return;

	if (pp != Curproc)
		delproc (pp);
	pp->state &= ~WAITING;
	pp->retval = val;
	pp->event = NULL;
	if (pp != Curproc)
		addproc (pp);
}

/* ************************************************************************* */

/* Wakeup process waiting on specified event. The process
 * will see a return value of "val" from its pwait() call. Must not be
 * called from an interrupt handler.
 */
ENTRY void
alert_event (void *event, int n, int val)
{

	psig (event, n, val);
}

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

/* Post a wait on a specified event and give up the CPU until it happens. The
 * null event is special: it means "I don't want to block on an event, but let
 * somebody else run for a while". It can also mean that the present process
 * is terminating; in this case the wait never returns.
 *
 * Pwait () returns 0 if the event was signaled; otherwise it returns the
 * arg in an alert () call. Pwait must not be called from interrupt level.
 *
 * Before waiting and after giving up the CPU, pwait () processes the signal
 * queue containing events signaled when interrupts were off. This means
 * the process queues are no longer modified by interrupt handlers,
 * so it is no longer necessary to run with interrupts disabled here. This
 * greatly improves interrupt latencies.
 */

ENTRY int
pwait (void *event)
{
	register struct proc *oldproc;
	int tmp;
	int i_depth;

#ifdef REMOVE_THIS_CODE
	if (network_nested_interrupt_read_depth ()) {

		fg_print_std(("pwait used by interrupt code %d %d\n", network_nested_interrupt_read_depth(), interrupt_running_fg));
		fg_print_routine(("interrupts disabled from pwait() %04hx '%s'\n", network_nested_interrupt_read_depth(), Curproc->name));

		while (network_nested_interrupt_read_depth()) {
			network_nested_interrupt_restore ();
		}

	}
#endif /* REMOVE_THIS_CODE */

	Ksig.pwaits++;
#ifdef REPLACE_THIS_CODE
	if (network_nested_interrupt_read_depth ()) {
#else /* REPLACE_THIS_CODE */
#define intcontext() 0
	if (intcontext ()) {
#endif /* REPLACE_THIS_CODE */
		/* Pwait must not be called from interrupt context */
		Ksig.pwaitints++;
		return 0;
	}
	/* Enable interrupts, after saving the current state.
	 * This minimizes interrupt latency since we may have a lot
	 * of work to do. This seems safe, since care has been taken
	 * here to ensure that signals from interrupt level are not lost, e.g.,
	 * if we're waiting on an event, we post it before we scan the
	 * signal queue.
	 */
	i_depth = network_nested_interrupt_read_depth ();

	network_nested_interrupt_forced_enable ();
	if (Stkchk)
		chkstk ();

	if (event != NULL) {
		/* Post a wait for the specified event */
		Curproc->event = event;
		Curproc->state = WAITING;
		addproc(Curproc);	/* Put us on the wait list */
	}
	/* If the signal queue contains a signal for the event that we're
	 * waiting for, this will wake us back up
	 */
	procsigs ();
	if (event == NULL) {
		/* We remain runnable */
		if (Rdytab == NULLPROC) {
			/* Nothing else is ready, so just return */
			Ksig.pwaitnops++;

			network_nested_interrupt_force_depth (i_depth);
			return 0;
		}
		addproc(Curproc); /* Put us on the end of the ready list */
	}

	/* Look for a ready process and run it. If there are none,
	 * loop or halt until an interrupt makes something ready.
	 */
	while (Rdytab == NULLPROC) {
		/* Give system back to upper-level multitasker, if any.
		 * Note that this function enables interrupts internally
		 * to prevent deadlock, but it restores our state
		 * before returning.
		 */
sys_putc ('%');

		/* Process signals that occurred during the giveup() */
		procsigs ();
	}
	/* Remove first entry from ready list */
	oldproc = Curproc;
	Curproc = Rdytab;
	delproc (Curproc);

	/* Now do the context switch.
	 * This technique was inspired by Rob, PE1CHL, and is a bit tricky.
	 *
	 * First save the current process's state. Then if
	 * this is still the old process, load the new environment. Since the
	 * new task will "think" it's returning from the setjmp() with a return
	 * value of 1, the comparison with 0 will bypass the longjmp (), which
	 * would otherwise cause an infinite loop.
	 */

	/* Save interrupt depth */
	oldproc->i_depth = i_depth;

	if (setjmp (oldproc->env) == 0) {

		/* We're still running in the old task; load new task context.
		 * The interrupt state is restored here in case longjmp
		 * doesn't do it (e.g., systems other than Turbo - C) .
		 */
		longjmp (Curproc->env, 1);
	}
	/* At this point, we're running in the newly dispatched task */

	tmp = Curproc->retval;
	Curproc->retval = 0;

	/* Also restore the true interrupt state here, in case the longjmp
	 * DOES restore the interrupt state saved at the time of the setjmp \().
	 * This is the case with Turbo - C's setjmp / longjmp.
	 */
	network_nested_interrupt_force_depth (Curproc->i_depth);
	/* If an exception signal was sent and we're prepared, take it */
	if ((Curproc->flags & P_SSET) && tmp == Curproc->signo) {
		longjmp (Curproc->sig, 1);
	}

	/* Otherwise return normally to the new task */
	return tmp;
}

/* ************************************************************************* */

ENTRY void
psignal (void *event, int n)
{
	if (!network_nested_interrupt_read_depth ()) {
		/* Interrupts are on, just call psig directly after
		 * processing the previously queued signals
		 */
		procsigs ();
		psig (event, n, 0);
		return;
	}

	/* Interrupts are off, so quickly queue event */
	Ksig.psigsqueued++;

	/* Ignore duplicate signals to protect against a mad device driver
	 * overflowing the signal queue
	 */
	if (event == lastevent && Ksig.nentries != 0) {
		Ksig.dupsigs++;
		return;
	}
	if (Ksig.nentries == SIGQSIZE) {
		/* It's hard to handle this gracefully */
		Ksig.lostsigs++;
		return;
	}
	lastevent = Ksig.wp->event = event;
	Ksig.wp->n = n;
	if (++Ksig.wp >= &Ksig.entry[SIGQSIZE])
		Ksig.wp = Ksig.entry;
	Ksig.nentries++;
}

/* ************************************************************************* */

LOCAL int
procsigs (void)
{
	int cnt = 0;
	int tmp;

	for (;;) {
		/* Atomic read and decrement of entry count */
		network_nested_interrupt_disable ();
		tmp = Ksig.nentries;
		if (tmp != 0)
			Ksig.nentries--;
		network_nested_interrupt_restore ();
		if (tmp == 0)
			break;
		psig (Ksig.rp->event, Ksig.rp->n, 0);
		if (++Ksig.rp >= &Ksig.entry[SIGQSIZE])
			Ksig.rp = Ksig.entry;
		cnt++;
	}
	if (cnt > Ksig.maxentries)
		Ksig.maxentries = cnt;	/* Record high water mark */
	return cnt;
}

/* ************************************************************************* */

/* Make ready the first 'n' processes waiting for a given event. The ready
 * processes will see a return value of 0 from pwait \().  Note that they don't
 * actually get control until we explicitly give up the CPU ourselves through
 * a pwait \(). psig is now called from pwait, which is never called at
 * interrupt time, so it is no longer necessary to protect the proc queues
 * against interrupts. This also helps interrupt latencies considerably.
 */
LOCAL void
psig (void *event, int n, int val)
{
	register struct proc *pp;
	struct proc *pnext;
	unsigned int hashval;
	int cnt = 0;

	Ksig.psigs++;
	if (Stkchk)
		chkstk ();

	if (event == NULL) {
		Ksig.psignops++;
		return;		/* Null events are invalid */
	}
	/* n == 0 means "signal everybody waiting for this event" */
	if (n == 0)
		n = MAX_SINT15;

	hashval = phash (event);
	for (pp = Waittab[hashval];n != 0 && pp != NULLPROC;pp = pnext) {
		pnext = pp->next;
		if (pp->event == event) {

			delproc (pp);
			pp->state &= ~WAITING;
			pp->retval = val;
			pp->event = NULL;
			addproc (pp);
			n--;
			cnt++;
		}
	}
	for (pp = Susptab;n != 0 && pp != NULLPROC;pp = pnext) {
		pnext = pp->next;
		if (pp->event == event) {

			delproc (pp);
			pp->state &= ~WAITING;
			pp->event = 0;
			pp->retval = val;
			addproc (pp);
			n--;
			cnt++;
		}
	}
	if (cnt == 0)
		Ksig.psignops++;
	else
		Ksig.psigwakes += cnt;
}

/* ************************************************************************* */

/* Rename a process */
ENTRY void
chname (struct proc *pp, char *newname)
{
	free (pp->name);
	pp->name = strdup (newname);

}

/* ************************************************************************* */

/* Remove a process entry from the appropriate table */
LOCAL void
delproc (struct proc *entry)
{
	if (entry == NULLPROC)
		return;

	if (entry->next != NULLPROC)
		entry->next->prev = entry->prev;
	if (entry->prev != NULLPROC) {
		entry->prev->next = entry->next;
	} else {
		switch (entry->state) {
		case READY:
			Rdytab = entry->next;
			break;
		case WAITING:
			Waittab[phash (entry->event) ] = entry->next;
			break;
		case SUSPEND:
		case SUSPEND | WAITING:
			Susptab = entry->next;
			break;
		}
	}
}

/* ************************************************************************* */

/* Append proc entry to end of appropriate list */
LOCAL void
addproc (struct proc *entry)
{
	register struct proc *pp;
	struct proc **head;

	if (entry == NULLPROC)
		return;

	entry->next = NULLPROC;
	switch (entry->state) {
	case READY:

		head = &Rdytab;
		break;

	case WAITING:
		head = &Waittab[phash (entry->event) ];
		break;
	case SUSPEND:
	case SUSPEND | WAITING:
		head = &Susptab;
		break;
	}
	if (*head == NULLPROC) {
		/* Empty list, stick at beginning */
		entry->prev = NULLPROC;
		*head = entry;
	} else {
		/* Find last entry on list */
		for (pp = *head;pp->next != NULLPROC;pp = pp->next)
		;
		pp->next = entry;
		entry->prev = pp;
	}
}
