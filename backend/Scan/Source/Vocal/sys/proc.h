
/* ************************************************************************* */
/*
 *	proc.h
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

#ifndef _SYS_PROC_H
#define _SYS_PROC_H

typedef long tijmpbuf[8];
#define jmp_buf tijmpbuf
#undef setjmp
#define setjmp(x) tisetjmp(x)
#undef longjmp
#define longjmp(x,y) tilongjmp(x,y)

#define	SIGQSIZE	200	/* Entries in psignal queue */

/* Kernel process control block */
#define	PHASH	16		/* Number of wait table hash chains */
struct proc {
	struct proc *prev;	/* Process table pointers */
	struct proc *next;

	int flags;
#define	P_SSET		2	/* Process has set sig */
#define	P_FREEARGS	4	/* Free args on termination */
	uint16 i_depth;		/* Process interrupt nested depth */

	jmp_buf env;		/* Process state */
	jmp_buf sig;		/* State for alert signal */
	int signo;		/* Arg to alert to cause signal */
	uint16 state;
#define	READY	0
#define	WAITING	1
#define	SUSPEND	2
	sint15 priority;	/* Process priority */
	void *event;		/* Wait event */
	uint16 *stack;		/* Process stack */
	unsigned stksize;	/* Size of same */
	uint16 *sysstack;		/* Process system stack */
	unsigned sysstksize;	/* Size of same */
	char *name;		/* Arbitrary user-assigned name */
	int retval;		/* Return value from next pwait() */
	struct timer alarm;	/* Alarm clock timer */
	void *session;		/* the session for standard IO */
	FILE *input;		/* standard input socket */
	FILE *output;		/* standard output socket */
	int iarg;		/* Copy of iarg */
	void *parg1;		/* Copy of parg1 */
	void *parg2;		/* Copy of parg2 */
	char *prefix;		/* Nested command prefix */
	void (*entry) (int,void*,void*);    /* Process entry point */
};
#define NULLPROC (struct proc *)0

extern struct proc *Waittab[];	/* Head of wait list */
extern struct proc *Rdytab;	/* Head of ready list */
extern struct proc *Curproc;	/* Currently running process */
extern struct proc *Susptab;	/* Suspended processes */
extern uint16 Proctrace;	/* Process trace flag */
extern int Stkchk;		/* Stack checking flag */

struct sigentry {
	void *event;
	int n;
};
struct ksig {
	struct sigentry entry[SIGQSIZE];
	struct sigentry *wp;
	struct sigentry *rp;
	volatile int nentries;	/* modified both by interrupts and main */
	int maxentries;
	sint31 dupsigs;
	int lostsigs;
	sint31 psigs;		/* Count of psignal calls */
	sint31 psigwakes;	/* Processes woken */
	sint31 psignops;		/* Psignal calls that didn't wake anything */
	sint31 psigsqueued;	/* Psignal calls queued with ints off */
	sint31 pwaits;		/* Count of pwait calls */
	sint31 pwaitnops;	/* pwait calls that didn't block */
	sint31 pwaitints;	/* Pwait calls from interrupt context (error) */
};
extern struct ksig Ksig;

/* Prepare for an exception signal and return 0. If after this macro
 * is executed any other process executes alert (pp, val), this will
 * invoke the exception and cause this macro to return a second time,
 * but with the return value 1. This cannot be a function since the stack
 * frame current at the time setjmp is called must still be current
 * at the time the signal is taken. Note use of comma operators to return
 * the value of setjmp as the overall macro expression value.
 */
#define	SETSIG(val)	(Curproc->flags |= P_SSET,\
	Curproc->signo = (val), setjmp (Curproc->sig))

/* Stack background fill value for high water mark checking */
#define	STACKPAT	0x1221

/* Value stashed in location 0 to detect null pointer dereferences */
#define	NULLPAT		0xdead

#endif /* _SYS_PROC_H */
