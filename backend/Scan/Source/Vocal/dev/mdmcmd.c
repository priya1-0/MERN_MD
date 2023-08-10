#undef use_mdm_trace_proc

/* ************************************************************************* */
/*
 *	mdmcmd.c
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
 *	Module:		DEV
 *
 *  Command processing routines to control the master / mdm ports.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 19:38:37  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#include "system/system.h"
#include "lansend/global.h"

#include <ctype.h>

#include "net/net.h"
#include "sys/sys.h"
#include "dev/dev.h"
#include "dev/devmdm.h"
#include "dev/mdmcmd.h"

#include "ip/ip.h"

#include "dev/local.h"

#include "term/term.h"

#include "trace/trace.h"

#include "dteif/dteif.h"

/* ************************************************************************* */
/*
 *  Function: pmdm
 *
 *  Print information for an mdm interface.
 *
 *  Parameters:
 *    "mdmp" is the mdm pointer
 *
 *  Returns: (none)
 *
 */
LOCAL void
pmdm (struct mdm *mdmp)
{
	/* Map rs232 states to strings for printing. */
	static char *rs232[8] = {"None", "1", "On", "Off", "4", "5", "Up", "Down"};

	printf ("%s:\n", mdmp->iface->name);

	printf (" MS: DTR %s %ld, RTS %s %ld, DSR %s %ld, CTS %s %ld, DCD %s %ld\n",
		rs232[(int) mdmp->dtrState], mdmp->dtrChanges,
		rs232[(int) mdmp->rtsState], mdmp->rtsChanges,
		rs232[(int) mdmp->dsrState], mdmp->dsrChanges,
		rs232[(int) mdmp->ctsState], mdmp->ctsChanges,
		rs232[(int) mdmp->dcdState], mdmp->dcdChanges);

	printf (" RX: %10ld char\n", mdmp->rxchar);

	printf (" TX: %10ld char, THRE TO%s\n",
		mdmp->txchar, mdmp->txbp ? " [BUSY]" : "");

#ifdef use_mdm_trace_proc
	printf("Modem event/status tracing %s\n",((mdmp->trace_proc != NULLPROC)?"enabled":"disabled"));
#endif /* use_mdm_trace_proc */
}

/* ************************************************************************* */
/*
 *  Function: do_show
 *
 *  Display the mdm data for the interface.
 *
 *  Parameters:
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is a void pointer to the interface
 *
 *  Command Line: mdm <dev> show
 *
 *  Returns: 0 for success always
 *
 */
LOCAL int
do_show (int argc, char *argv[], void *p)
{
	struct iface *ifp = (struct iface *) p;

	if (ifp == NULLIF) {
		for (ifp = Ifaces; ifp != NULLIF; ifp = ifp->next) {
			if (ifp->d_type == IFD_MDM &&
				ifp->ddv != NULL) {
				pmdm ((struct mdm *) ifp->ddv);
			}
		}
	}
	else {
		pmdm ((struct mdm *) ifp->ddv);
	}
	return 0;
}

/* ************************************************************************* */
/*
 *  Function: do_idle
 *
 *  Set or display the idle time for an mdm interface.  The
 *  connection is broken after the idle time elapses.
 *
 *  Parameters:
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is a void pointer to the interface
 *
 *  Command Line: mdm <dev> idle [secs]
 *
 *  Returns: 0 for success
 *           else error
 *
 */
LOCAL int
do_idle (int argc, char *argv[], void *p)
{
	struct iface *ifp = (struct iface *) p;
	struct mdm *mdmp = (struct mdm *) ifp->ddv;

	if (chg_timer (&mdmp->idle, "Idle timer duration", argc, argv))
		return 1;
	if (argc > 1) {
		start_timer (&mdmp->idle);
		ifp->LastChange = secclock ();
	}
	else {
		printf ("Time left: %ld\n", (sint31) (read_timer (&mdmp->idle) / 1000L));
	}

	return 0;
}

/* ************************************************************************* */
/*
 *  Function: do_ioctl
 *
 *  Perform ioctl operation on the mdm port.
 *
 *  Parameters:
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is a void pointer to the interface
 *
 *  Command Line: mdm <dev> ioctl <param> [value]
 *
 *  Returns: 0 for success
 *           else error
 *
 */
LOCAL int
do_ioctl (int argc, char *argv[], void *p)
{
	struct iface *ifp = (struct iface *) p;
	int param;

	/* Map the param string to a number. */
	if ((param = devparam (argv[1])) == -1) {
		printf ("Unknown paramameter: %s\n", argv[1]);
		return 1;
	}

	if (ifp->ioctl != NULL) {
		if (argc > 2) {
			sint31 x;

			if (atoi32s_err (argv[2], &x))
				return 1;
			(*ifp->ioctl) (ifp, param, TRUE, x);
		}
		else
			printf ("%s %s is set to: %2lx\n", ifp->name, argv[1],
				(*ifp->ioctl) (ifp, param, FALSE, 0));
	}

	return 0;
}

/* ************************************************************************* */
/*
 *  Function: do_hangup
 *
 *  Hangup an mdm port.
 *
 *  Parameters:
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is a void pointer to the interface
 *
 *  Command Line: mdm <dev> hangup
 *
 *  Returns: 0 for success
 *           else error
 *
 */
LOCAL int
do_hangup (int argc, char *argv[], void *p)
{
	struct iface *ifp = (struct iface *) p;

	hangup_wait (ifp);

	return 0;
}

#ifdef use_mdm_trace_proc
/* ************************************************************************* */
/*
 *  Process: nb_trace
 *
 *  Process to trace modem event / status buffer
 *
 *  Parameters:
 *    "unused1" is an unused int
 *    "p1" is unused
 *    "p2" is unused
 *
 *  Started By: do_send
 *
 *  Terminated By: killproc.
 *
 */
LOCAL void
nb_trace (int unused1, void *p1, void *p2)
{
	uint16 status_cnt;
	static uint16 fg__remove = 0;

	for (;;) {

		if (fg_status_insert >= fg_status_remove) {
			status_cnt = fg_status_insert - fg_status_remove;
		}
		else {
			status_cnt = STATUS_BUFFER_SIZEOF -
						 (fg_status_remove - fg_status_insert);
		}

		if (status_cnt != 0) {

			while (status_cnt) {

				if ((fg_status_event_queue[fg_status_remove] == 0x2002)
					 || ((fg_status_event_queue[fg_status_remove] & 0x4760) == 0x4760)
					 || ((fg_status_event_queue[fg_status_remove] & 0x0200) == 0x0200)
					 || (fg_status_event_queue[fg_status_remove] == 0)
				) {
				}
				else {
					printf("<%04x:%04x>",fg_status_event_queue [fg_status_remove],
										   fg_status_svalue_queue[fg_status_remove]);
				}

				if (fg_status_remove == (STATUS_BUFFER_SIZEOF -1)) {
					fg_status_remove = 0;
				}
				else {
					fg_status_remove++;
				}

				status_cnt--;
			}
		}
		fflush (stdout);
		pwait (NULL);
	}
}

/* ************************************************************************* */
/*
 *  Function: do_trace
 *
 *  Enable / disable modem event tracing
 *
 *  Parameters:
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is a void pointer to the interface
 *
 *  Command Line: mdm <dev> trace [on/off]
 *
 *  Returns: 0 for success
 *           else error
 *
 */
LOCAL int
do_trace (int argc, char *argv[], void *p)
{
	struct iface *ifp = (struct iface *) p;
	struct mdm *mdmp = ifp->ddv;
	int enabled;

	if (argc > 1) {
		if (stricmp(argv[1],"on") == 0) {
			enabled = 1;
		}
		else if (stricmp(argv[1],"off") == 0) {
			enabled = 0;
		}
		else {
			printf("Invalid parameter\n");
			return -1;
		}

		/* Set the value */
		if ((mdmp->trace_proc == NULLPROC) && enabled) {
			/* start the tracing process */
			mdmp->trace_proc = newproc (if_name (ifp, " trace"), 320, nb_trace, 0, 0, NULL, 0);
		}
		if ((mdmp->trace_proc != NULLPROC) && ! enabled) {
			killproc (mdmp->trace_proc);
			mdmp->trace_proc = NULLPROC;
		}
	}

	printf("Modem event/status tracing %s\n",((mdmp->trace_proc != NULLPROC)?"enabled":"disabled"));

	return 0;
}
#endif /* use_mdm_trace_proc */

/* ************************************************************************* */
/*
 *  Command Table: mdm <dev> ...
 *
 */
static const struct cmds mdm_cmds[] = {
	{"hangup",		do_hangup,			0,	0,	""},
	{"idle",		do_idle,			0,	0,	"[secs]"},
	{"ioctl",		do_ioctl,			0,	2,	"<param> [value]"},
	/* "show" comes first so "s" does a show */
	{"show",		do_show,			0,	0,	""},
#ifdef use_mdm_trace_proc
	{"trace",		do_trace,			0, 0,	"[on/off]"},
#endif /* use_mdm_trace_proc */
	{NULLCHAR}
};

/* ************************************************************************* */
/*
 *  Function: do_mdm
 *
 *  Process commands to control an mdm port.
 *
 *  Parameters:
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is a void pointer to the interface
 *
 *  Command Line: mdm <dev> ...
 *
 *  Returns: 0 for success
 *           else error
 *
 */
ENTRY int
do_mdm (int argc, char *argv[], void *p)
{
	return ifacecmd ((IFACECMD_EXIST | IFACECMD_SHOW | IFACECMD_MDM),
					 mdm_cmds, argc, argv, p);
}
