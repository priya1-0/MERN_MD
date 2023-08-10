
/* ************************************************************************* */
/*
 *	ksubr.c
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
 *	This file contains the machine or compiler - dependent portions of kernel.
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

/* ************************************************************************* */

/* ************************************************************************* */

/* ************************************************************************* */

/* Template for contents of jmp_buf for TI 55x */
struct env {
	uint32	lcrpc;
	uint32	xar5;
	uint32	xar6;
	uint32	xar7;
	uint32	ac1;
	uint32	sp;
	uint32	ssp;
	uint16	dr2;
	uint16	dr3;
};

/* ************************************************************************* */

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

ENTRY void
kinit (void)
{
	int i;

	for (i = 0; i < PHASH; i++)
		Waittab[i] = NULLPROC;

	/* Remember location 0 pattern to detect null pointer derefs */

	/* Initialize signal queue */
	Ksig.wp = Ksig.rp = Ksig.entry;
	Ksig.nentries = 0;
	Ksig.maxentries = 0;
	Ksig.dupsigs = 0;
	Ksig.lostsigs = 0;
	Ksig.psigs = 0;		/* Count of psignal calls */
	Ksig.psigwakes = 0;	/* Processes woken */
	Ksig.psignops = 0;		/* Psignal calls that didn't wake anything */
	Ksig.psigsqueued = 0;	/* Psignal calls queued with ints off */
	Ksig.pwaits = 0;		/* Count of pwait calls */
	Ksig.pwaitnops = 0;	/* pwait calls that didn't block */
	Ksig.pwaitints = 0;	/* Pwait calls from interrupt context (error) */
}

/* ************************************************************************* */

/* Print process table info
 * Since things can change while ps is running, the ready proceses are
 * displayed last. This is because an interrupt can make a process ready,
 * but a ready process won't spontaneously become unready. Therefore a
 * process that changes during ps may show up twice, but this is better
 * than not having it showing up at all.
 */
ENTRY int
ps (int argc, char *argv[], void *p)
{
	register struct proc *pp;
	int i;

	printf("psigs %lu queued %lu hiwat %u woken %lu nops %lu dups %u\n",Ksig.psigs,
	 Ksig.psigsqueued, Ksig.maxentries, Ksig.psigwakes, Ksig.psignops, (unsigned int) Ksig.dupsigs);
	Ksig.maxentries = 0;
	printf("pwaits %lu nops %lu from int %lu\n",
	 Ksig.pwaits, Ksig.pwaitnops, Ksig.pwaitints);

	printf("PID    SP     stksize maxstk SSP    stksize maxstk pri event  fl  in  out ");

	printf("name\n");

	for (pp = Susptab;pp != NULLPROC;pp = pp->next)
		pproc (pp);

	for (i = 0;i < PHASH;i++)
		for (pp = Waittab[i];pp != NULLPROC;pp = pp->next)
			pproc (pp);

	for (pp = Rdytab;pp != NULLPROC;pp = pp->next)
		pproc (pp);

	if (Curproc != NULLPROC)
		pproc (Curproc);

	return 0;
}

/* ************************************************************************* */

LOCAL void
pproc (struct proc *pp)
{
	register struct env *ep = (struct env*) &pp->env;
	char insock[5], outsock[5];

	if (fileno (pp->input) != -1)
		sprintf(insock,"%3d",fileno(pp->input));
	else if (pp->input == NULLFILE)
		sprintf(insock,"Off");	/* Off */
	else
		sprintf(insock,"   ");	/* Pipe */

	if (fileno (pp->output) != -1)
		sprintf(outsock,"%3d",fileno(pp->output));
	else if (pp->output == NULLFILE)
		sprintf(outsock,"Off");	/* Off */
	else
		sprintf(outsock,"   ");	/* Pipe */

	printf("%-7lx",(uint32)pp);
	printf("%-7lx",(uint32)ep->sp);
	printf("%-8u",pp->stksize);
	printf("%-7u",stkutil(pp->stack,pp->stksize));
	printf("%-7lx",(uint32)ep->ssp);
	printf("%-8u",pp->sysstksize);
	printf("%-7u",stkutil(pp->sysstack,pp->sysstksize));
	printf("%-4d",pp->priority);
	printf("%-7lx",(uint32)(pp->event));
	printf("%c%c%c",
					   (pp->i_depth) ? 'I':' ',
					   (pp->state & WAITING) ? 'W':' ',
					   (pp->state & SUSPEND) ? 'S':' ');
	printf(" %s %s %s\n",insock,outsock,pp->name);
}

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

ENTRY int
stkutil (register uint16 * sp, unsigned int size)
{
	uint16 *start = sp;
	int total_size = size;
	for (;*sp == STACKPAT && sp < (start + total_size);sp++, size--);
	return size;
}

/* ************************************************************************* */

/* ************************************************************************* */

/* Verify that stack pointer for current process is within legal limits;
 * also check that no one has dereferenced a null pointer
 */
ENTRY void
chkstk (void)
{
}

/* ************************************************************************* */

/* Machine-dependent initialization of a task */
ENTRY void
psetup (struct proc *pp, int iarg, void *parg1, void *parg2, void (*pc) (void))
{

	unsigned int *stktop, *sysstktop;
	struct env *ep;
	volatile uint32 ltemp;

	pp->entry = (void (*) ()) pc;

	stktop = (unsigned int *) (pp->stack + pp->stksize);
	sysstktop = (unsigned int *) (pp->sysstack + pp->sysstksize);

	/* ensure that stack pointer starts long-word aligned */
	*(uint32*)&stktop = (uint32)stktop & 0xfffffffe;				/* Even always */
	*(uint32*) &sysstktop = (uint32) sysstktop & 0xfffffffe;

	/* Now push the entry address of killself(), simulating the call to
	 * the user function.
	 */
	ltemp = (uint32) killself;
	/*
	 *	The stack of the TI55x must be ODD upon entry to a function.  (EVEN
	 *	before the call, ODD once inside the function.)  This is the
	 *	assumed alignment which allow double word load / store for auto
	 *	variables and passed arguments to functions.  The function will move
	 *	the stack an ODD number of locations and then perform a function call
	 *	which further moves the stack one more time so that upon entry the
	 *	ODD alignment is maintained.
	 *
	 *	Also, the AADD instruction creates the SAME amount of local / auto
	 *	variable space on BOTH stacks (SP and SSP) .  However, if more than
	 *	128 local variables are needed (approximately), the instruction used is
	 *	ADD # - 258, mmap (SP) which ONLY adds to the SP (not the SSP) .
	 *
	 *	Hence, use care when sizing stacks.
	 */
	stktop--;					/* Must decrement to ensure ODD alignment */	/* Odd */
	sysstktop--;
	*stktop-- = 0x5555;			/* Push pairs of stack top markers */			/* Even */
	*stktop--= 0x5555;
	*sysstktop-- = 0x5a5a;		/* Different marker for the SSP stack */		/* Odd */
	*sysstktop--= 0x5a5a;
	*stktop-- = ltemp & 0xffff;													/* Even */
	*sysstktop--= (ltemp >> 16) & 0xffff;

	/*
	 *	An empty location is at the top of the new stacks.  In the longjmp
	 *	routine, the return address is "popped" off the new stack and the
	 *	new process address is pushed on in its place.  This keeps the stack
	 *	EVEN.  Whe longjmp returns, the stack is now ODD and we are executing
	 *	the first instruction of the new process with an ODD stack.
	 *
	 */

	/* Set up task environment. Note that for Turbo-C, the setjmp
	 * sets the interrupt enable flag in the environment so that
	 * interrupts will be enabled when the task runs for the first time.
	 * Note that this requires newproc () to be called with interrupts
	 * enabled !
	 */
	setjmp (pp->env);
	ep = (struct env *) &pp->env;
	ep->sp = (uint32) stktop;
	ep->ssp = (uint32) sysstktop;
	ep->ac1 = (uint32)procstartup;										/* Once popped, pushed, and returned to, the stack will be Odd */

	/* Task initially runs with interrupts on */
	pp->i_depth = 0;
}

/* ************************************************************************* */

ENTRY void
procstartup (void)
{
	/* call the process entry point, with the proper arguments */
	Curproc->entry (Curproc->iarg, Curproc->parg1, Curproc->parg2);
	/* in case of return, terminate the process */
	killself ();
}

/* ************************************************************************* */

ENTRY unsigned
phash (void *event)
{
	register unsigned int x;

	/* Fold the two halves of the pointer */
	x = (((sint31) event >> 16) ^ (sint31) event) & 0xffff;

	/* If PHASH is a power of two, this will simply mask off the
	 * higher order bits
	 */
	return x % PHASH;
}

/* ************************************************************************* */

/* Parse process name string to process structure pointer */
ENTRY int
atoproc_err (char *cp, struct proc **pp)
{
	int i;
	struct proc *ptr;
	char *ncp;

	ptr = (struct proc *) strtoul (cp, &ncp, 16);
	if (*ncp != '\0') {
		ptr = 0;
	}

	/* Search the process tables for the named process */
	for (*pp = Susptab;*pp != NULLPROC;*pp = (*pp)->next) {
		if ((*pp == ptr) || (strcmp ((*pp)->name, cp) == 0)) {
			return 0;
		}
	}

	for (i = 0;i < PHASH;i++) {
		for (*pp = Waittab[i];*pp != NULLPROC;*pp = (*pp)->next) {
			if ((*pp == ptr) || (strcmp ((*pp)->name, cp) == 0)) {
				return 0;
			}
		}
	}

	for (*pp = Rdytab;*pp != NULLPROC;*pp = (*pp)->next) {
		if ((*pp == ptr) || (strcmp ((*pp)->name, cp) == 0)) {
			return 0;
		}
	}

	printf ("Invalid process name:%s\n", cp);
	return 1;
}

/* ************************************************************************* */

/* Direct I/O of a particular process either to or away from a file/socket.
 */
LOCAL void
conproc (struct proc *pp, int mode)
{
	/* Inhibit changes to keyboard and display processes */
	if (strcmp (pp->name, "keyboard")) {

		/* Allow forcing stdin/stdout of a process */
		if (mode == 2) {
			if (pp->input != NULLFILE) {
				fclose (pp->input);
				pp->input = NULLFILE;
			}

			if (pp->output != NULLFILE) {
				fclose (pp->output);
				pp->output = NULLFILE;
			}
		}

		/* Direct I/O to current process's socket */
		if (mode) {
			if (pp->input == NULLFILE) {
				pp->input = fdup (stdin);
			}
			if (pp->output == NULLFILE) {
				pp->output = fdup (stdout);
			}
		}
		/* Direct I/O away from current process's socket */
		else {
			if (pp->input == stdin) {
				fclose (stdin);
				pp->input = NULLFILE;
			}
			if (pp->output == stdout) {
				fclose (stdout);
				pp->output = NULLFILE;
			}
		}
	}
}

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

/* Change process's stdin and stdout to current process's stdin and stdout
 * if currently off, or turn process's stdin and stdout off.
 */
ENTRY int
doconsole (int argc, char *argv[], void *p)
{
	int mode = 0;
	int i;
	struct proc *pp;

	/* Allow forcing stdin/stdout of a process */
	if ((argc > 1) & (stricmp (argv[1], "force") == 0)) {
		mode = 2;
	} else if (((argc > 0) && chg_bool (&mode, "", argc, argv)) != 0)
		return 1;

	if (argc > 2) {
		if (atoproc_err (argv[2], &pp))
			return 1;
		conproc (pp, mode);
	}
	else {
		/* Direct I/O either to or away from current process's socket */
		for (pp = Susptab;pp != NULLPROC;pp = pp->next)
			conproc (pp, mode);

		for (i = 0;i < PHASH;i++)
			for (pp = Waittab[i];pp != NULLPROC;pp = pp->next)
				conproc (pp, mode);

		for (pp = Rdytab;pp != NULLPROC;pp = pp->next)
			conproc (pp, mode);
	}

	return 0;
}

/* ************************************************************************* */

/* Alert a process */
LOCAL int
doalert (int argc, char *argv[], void *p)
{
	struct proc *pp;
	sint15 value;

	if (atoproc_err (argv[1], &pp))
		return 1;
	if (atoi16s_err (argv[2], &value))
		return 1;

	alert (pp, value);
	return 0;
}

/* ************************************************************************* */

/* Kill a process */
LOCAL int
dokill (int argc, char *argv[], void *p)
{
	struct proc *pp;

	if (atoproc_err (argv[1], &pp))
		return 1;

	killproc (pp);
	return 0;
}

/* ************************************************************************* */

/* Set priority of a process */
LOCAL int
dopriority (int argc, char *argv[], void *p)
{
	struct proc *pp;
	sint15 priority;

	if (atoproc_err (argv[1], &pp))
		return 1;
	if (atoi16s_err (argv[2], &priority))
		return 1;

	setpriority (pp, priority);
	return 0;
}

/* ************************************************************************* */

/* Resume a process */
LOCAL int
doresume (int argc, char *argv[], void *p)
{
	struct proc *pp;

	if (atoproc_err (argv[1], &pp))
		return 1;

	resume (pp);
	return 0;
}

/* ************************************************************************* */

/* Signal an event */
LOCAL int
dosignal (int argc, char *argv[], void *p)
{
	uint32 event;
	sint15 value = 0;

	if (atoi32uh_err (argv[1], &event))
		return 1;

	if (argc > 2)
		if (atoi16s_err (argv[2], &value))
			return 1;

	alert_event ((void *) (event), 0, value);
	return 0;
}

/* ************************************************************************* */

/* Suspend a process */
LOCAL int
dosuspend (int argc, char *argv[], void *p)
{
	struct proc *pp;

	if (atoproc_err (argv[1], &pp))
		return 1;

	suspend (pp);
	return 0;
}

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

/* "process" subcommands */
static const struct cmds Proccmds[] = {
	{"alert",		doalert,			0,	3,	"<name> <value>"},
	{"console",		doconsole,			0,	2,	"<on|off|force> [name]"},
	{"kill",		dokill,				0,	2,	"<name>"},
	{"priority",	dopriority,			0,	3,	"<name> <priority>"},
	{"ps",			ps,					0,	0,	""},
	{"resume",		doresume,			0,	2,	"<name>"},
	{"show",		ps,					0,	0,	""},
	{"signal",		dosignal,			0,	2,	"<event> [value]"},
	{"suspend",		dosuspend,			0,	2,	"<name>"},
	{NULLCHAR},
};

/* ************************************************************************* */

/* Display and/or processes */
ENTRY int
doprocess (int argc, char *argv[], void *p)
{
	return subcmd (Proccmds, argc, argv, p);
}
