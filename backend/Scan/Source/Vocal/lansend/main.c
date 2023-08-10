
/* ************************************************************************* */
/*
 *	main.c
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
 *	Module:		MAIN
 *
 *	This file contains the main functions.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 19:56:06  zhangn1
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

#include "lansend/lansend.h"
#include "lansend/local.h"

#include "trace/trace.h"
#include "utils/utils.h"
#include "sys/sys.h"
#include "wan/wan.h"
#include "term/term.h"

#include "dteif/dteif.h"
#include "v24/v24.h"

#include <tsk.h>

/* ************************************************************************* */

extern const char Nospace[] = "No space!!\n";	/* Generic malloc fail message */
char *Hostname = NULLCHAR;

struct proc *Cmdpp = NULLPROC;
int main_exit = FALSE;							/* from main program (flag) */

char Prompt[] = "-> ";
static FILE *Logfp = NULLFILE;

static time_t StartTime = 0;                /* time that NOS was started */
static int Verbose = 0;

static const char far ifDescr_Loopback[] = "LANsEND Loopback Virtual Device";

/* ************************************************************************* */

/* Embedded cold start command file string
 */
static const char far Coldstart[] = {
#include "customer/cx077net.h"
				};

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

ENTRY void
network_reset (void)
{
	dev_module_reset ();

	ip_module_reset ();

	utils_module_reset ();

	lansend_module_reset ();

	net_module_reset ();

	sys_module_reset ();

	wan_module_reset ();

	lansend_module_reset ();
}

/* ************************************************************************* */

ENTRY void
network_kernel_install (void)
{
	StartTime = time (&StartTime);

	kinit ();

	sockinit ();

	sessinit ();

}

/* ************************************************************************* */

ENTRY void
lansend_startup (void)
{

	struct session *sp;
	const struct daemon *tp;
	static FILE *fp = NULLFILE;

	Cmdpp = mainproc ("net main");

	sp = newsession ("net main", COMMAND, TRUE);
	Users[sp->user]->display = Cmdpp;

	printf ("\n\nLANsEND Run-Time Version %s\n%s\n", VOCAL_REVISION, COPYRIGHT_STRING);
	fflush (stdout);

	/* default interfaces */
	Loopback = if_attach ("loopback", 0);
	Loopback->iftype = &Iftypes[0];
	Loopback->ifDescr = ifDescr_Loopback;
	Loopback->address[AF_INET].sa_family = AF_INET;
	Loopback->address[AF_INET].sin_address = IPADDR_LOOPBACK;
	Loopback->netmask[AF_INET] = 0xff000000L;
	Loopback->Speed = 10000000L;
	Loopback->indepth = 0;
	Loopback->outdepth = 0;
	rt_add (&Loopback->address[AF_INET], 0xff000000L, NULL, Loopback,
	    0, 0, 0, 0L, 1);

	/* Start background Daemons */
	for (tp = Daemons;; tp++) {
		if (tp->name == NULLCHAR)
			break;
		newproc (tp->name, tp->stksize, tp->fp, 0, NULLCHAR, NULL, 0);
	}

	/* Write commands to startup file if it does not exist */
	if ((fp = fopen (Startup, READ_TEXT)) == NULLFILE) {
		if ((fp = fopen (Startup, WRITE_TEXT)) != NULLFILE) {
			fwrite ((void *) Coldstart, 1, strlen (Coldstart), fp);
		}
	}
	fclose (fp);

}

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */
/*
 *	Entry Routine:	command_process
 *
 *	Network kernel process with handles user commands
 *
 *	Parameters:
 *		none
 *
 *	Returns:
 *		none
 */
ENTRY void
command_process (int i, void *p1, void *p2)
{
	char cmdbuf[256];

	for (;;) {
		printf (Prompt);
		fflush (stdout);
		if (fgets (cmdbuf, sizeof (cmdbuf), stdin) != NULLCHAR) {

			cmdparse (Cmds, cmdbuf, NULL);
		}
	}
}

/* ************************************************************************* */
/*
 *	Entry Routine:	net_bg
 *
 *	Network kernel main polling loop
 *
 *	Parameters:
 *		none
 *
 *	Returns:
 *		none
 */
extern uint16 periodic_command_flag;

ENTRY void
net_bg (void)
{
	static int debug_count = 30000;

	static int startup_delay = 10000;

	/* Execute commands from startup file */
	if (startup_delay == 0) {
		cmdfile (Startup);
		fflush (stdout);

	}

	if (startup_delay >= 0) {
		startup_delay--;
	}

	if (periodic_command_flag) {
		if (--debug_count == 0) {
			debug_count = 30000;
			ps (0, NULL, NULL);
		}
	}

	pwait (NULL);

}

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

ENTRY int
dolog (int argc, char *argv[], void *p)
{
	static char *logname;

	if (argc < 2) {
		if (Logfp)
			printf ("Logging to %s\n", logname);
		else
			printf ("Logging off\n");
		return 0;
	}
	if (Logfp) {
		net_log (-1, "NOS log closed");
		fclose (Logfp);
		Logfp = NULLFILE;
		free (logname);
		logname = NULLCHAR;
	}
	if (strcmp (argv[1], "stop") != 0) {
		logname = strdup (argv[1]);
		Logfp = fopen (logname, APPEND_TEXT);
		net_log (-1, "NOS was started at %s", ctime (&StartTime));
	}
	return 0;
}

/* ************************************************************************* */
/*
 * Log messages of the form
 * Tue Jan 31 00:00:00 1987 44.64.0.7:1003 open FTP
 */
ENTRY void
net_log (int s, char *fmt, ...)
{
	va_list ap;
	char *cp;
	time_t t;
	int i;
	struct sockaddr fsocket;
	int fd;

	if (Logfp == NULLFILE)
		return;

	time (&t);
	cp = ctime (&t);
	rip (cp);
	i = SOCKSIZE;
	fprintf (Logfp, "%s", cp);
	if (getpeername (s, (char *) &fsocket, &i) != -1)
		fprintf (Logfp, " %s", snhptoa (&fsocket));

	fprintf (Logfp, " - ");
	va_start (ap, fmt);
	vfprintf (Logfp, fmt, ap);
	va_end (ap);
	fprintf (Logfp, "\n");
	fflush (Logfp);

	/* MS-DOS doesn't really flush files until they're closed */
	fd = fileno (Logfp);
	if ((fd = dup (fd)) != -1)
		close (fd);
}

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

/* ************************************************************************* */

ENTRY int
snmp_trap (sint31 trap_type, sint31 trap_specific)
{
	return 0;
}

/* ************************************************************************* */

ENTRY void
lansend_module_reset (void)
{
	Hostname = NULLCHAR;
	Cmdpp = NULLPROC;
	main_exit = FALSE;                  /* from main program (flag) */
	Logfp = NULLFILE;
	Verbose = 0;
	account_init ();
	config_init ();
}

/* ************************************************************************* */

ENTRY void
network_cmd_line (int argc, char *argv[])
{
}

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

int network_task_state = 0;
TSK_Handle hNetworkTask = NULL;
typedef struct {
	int stksize;
	void (*pc) (int, void*, void*);
	int iarg;
	void *p1;
	void *p2;
	int freeargs;
} net_proc_start_t;
net_proc_start_t net_proc_start;
volatile int net_in_kernel = 0;

/* ************************************************************************* */
/*
 *	Entry Routine:	dspbios_network_task
 *
 *	DSP\BIOS task which encapsulates the network kernel, necessary because
 *  the network kernel creates processes which have their own stacks, which
 *  will confuse DSP\BIOS' central interrupt dispatcher if the network kernel
 *	is not a DSP\BIOS task.
 *
 *	Parameters:
 *		none
 *
 *	Returns:
 *		none
 */
void nested_interrupt_force_depth (uint16 depth);

ENTRY void
dspbios_network_task (void)
{
	for (;;) {
		switch (network_task_state) {
		case 0:
			/* network_init() must be called from within the DSP\BIOS task
			 * so that the main process inherents the context of the task.
			 */
			network_reset ();
			network_kernel_install ();
			lansend_startup ();
			net_proc_start.pc = NULL;
			network_nested_interrupt_force_depth (Curproc->i_depth);

			network_task_state = 1;
			break;

		case 1:
			/* Start a user process if needed */
			if (net_proc_start.pc != NULL) {
				newproc("userproc",
						net_proc_start.stksize,
						net_proc_start.pc,
						net_proc_start.iarg,
						net_proc_start.p1,
						net_proc_start.p2,
						net_proc_start.freeargs);
				net_proc_start.pc = NULL;
			}

			/* allow all processes to run */
			pwait (NULL);
			break;
		}
		TSK_sleep (10);
	}
}

/* ************************************************************************* */
/*
 *	Entry Routine:	dspbios_network_shutdown
 *
 *	Stop all network kernel processes, and stop the DSP\BIOS task
 *
 *	Parameters:
 *		none
 *
 *	Returns:
 *		none
 */
ENTRY void
dspbios_network_shutdown (void)
{
	if (network_task_state != 0)
	{

		TSK_delete (hNetworkTask);

		network_task_state = 0;
		hNetworkTask = NULL;
	}
}

/* ************************************************************************* */
/*
 *	Entry Routine:	dspbios_network_start
 *
 *	Start the network kernel task, the task will take care of calling
 *	network_init ()
 *
 *	Parameters:
 *		none
 *
 *	Returns:
 *		none
 */
TSK_Attrs dspb_attr;

ENTRY int
dspbios_network_start (void)
{
/*
	typdef	struct TSK_Attrs {
		Int priority;
		Ptr stack;
		Uns stacksize;
		Uns sysstacksize;
		Uns stackseg;
		Ptr environ;
		String name;
		Bool exitflag;
	} dspb_attr;
*/
	dspb_attr.priority = TSK_MINPRI;
	dspb_attr.stack = NULL;
	dspb_attr.stacksize = 0x401;
	dspb_attr.sysstacksize = 0x401;
	dspb_attr.name = "NETWORK_TASK";
	dspb_attr.stackseg = NULL;
	dspb_attr.environ = NULL;
	dspb_attr.exitflag = TRUE;

	network_task_state = 0;
	hNetworkTask = TSK_create ((Fxn) dspbios_network_task, &dspb_attr);
	if (hNetworkTask == NULL) {
		return MDM_ERRORCODE__NETWORK_TASK_CREATE_FAILED;
	}
	return MDM_ERRORCODE__NO_ERROR;
}

/* ************************************************************************* */

ENTRY int
dspbios_network_start_process (int stksize, void (*pc) (int, void*, void*), int iarg, void *p1, void *p2, int freeargs)
{
	if (net_proc_start.pc == NULL) {
		net_proc_start.stksize = stksize;
		net_proc_start.iarg = iarg;
		net_proc_start.p1 = p1;
		net_proc_start.p2 = p2;
		net_proc_start.freeargs = freeargs;
		net_proc_start.pc = pc;
		return 1;
	}
	return 0;
}

/* ************************************************************************* */

ENTRY int
dspbios_network_kernel_running (void)
{
	if ((hNetworkTask != NULL) && (network_task_state != 0)) {
		return TRUE;
	}

	return FALSE;
}
