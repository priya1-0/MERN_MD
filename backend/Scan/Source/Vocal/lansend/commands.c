
/* ************************************************************************* */
/*
 *	commands.c
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
 *	This file contains the functions.
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

#include <ctype.h>

#include "net/net.h"
#include "sys/sys.h"
#include "dev/dev.h"

#include "ip/ip.h"

#include "lansend/local.h"

#include "trace/trace.h"
#include "term/term.h"
#include "utils/utils.h"
#include "wan/wan.h"

#include "pump/pump.h"
#include "include/test.h"

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

/* ************************************************************************* */

LOCAL int
dodate (int argc, char *argv[], void *p)
{
	time_t timer;
	struct tm *tmp;
	sint15 year, month, day;

	time (&timer);
	tmp = localtime (&timer);

	/* Display current date and time */
	if (argc == 1) {
		day = tmp->tm_mday;
		month = tmp->tm_mon + 1;
		year = tmp->tm_year + 1900;

		printf ("Date: %d/%02d/%02d - %s", year, month, day, asctime (tmp));
		return 0;
	}
	/* Set the current date */
	else {
		if (!parse_date (tmp, argv[1])) {
			timer = mktime (tmp);
			if (timer != (time_t)-1) {
				stime (&timer);
				return 0;
			}
		}
		printf ("Invalid date entry: %s\n", argv[1]);
	}
	return 1;
}

/* ************************************************************************* */

LOCAL int
dotime (int argc, char *argv[], void *p)
{
	time_t timer;
	struct tm *tmp;
	sint15 hours, mins, secs;

	time (&timer);
	tmp = localtime (&timer);

	/* Display current date and time */
	if (argc == 1) {
		hours = tmp->tm_hour;
		mins = tmp->tm_min;
		secs = tmp->tm_sec;
		printf ("Time: %02d:%02d:%02d - %s", hours, mins, secs, asctime (tmp));
		return 0;
	}
	/* Set the current time */
	else {
		if (!parse_time (tmp, argv[1])) {
			timer = mktime (tmp);
			if (timer != (time_t)-1) {
				stime (&timer);
				return 0;
			}
		}
		printf ("Invalid time entry: %s\n", argv[1]);
	}
	return 1;
}

/* ************************************************************************* */

LOCAL int
docmdfile (int argc, char *argv[], void *p)
{
	return cmdfile (argv[1]);
}

/* ************************************************************************* */

ENTRY int
cmdfile (char *file)
{
	char *intmp;
	FILE *fp;
	char cmdbuf[256];

	/* Read command file */
	if ((fp = fopen (file, READ_TEXT)) == NULLFILE) {
		int save_errno = errno;
		printf ("Can't read config file %s", file);
		errno = save_errno;
		perror ("");
	}
	else {
		while (fgets (cmdbuf, sizeof (cmdbuf), fp) != NULLCHAR) {
			intmp = strdup (cmdbuf);
			if (cmdparse (Cmds, cmdbuf, NULL) != 0) {
				printf ("input line: %s", intmp);
			}
			free (intmp);
			pwait (NULL);
		}
		fclose (fp);
	}
	return 0;
}

/* ************************************************************************* */

ENTRY int
domore (int argc, char *argv[], void *p)
{
	FILE *fp;
	int c;
	int rows = MOREROWS;

	if ((fp = fopen (argv[1], READ_TEXT)) == NULLFILE) {
		printf ("Can't open %s", argv[1]);
		perror ("");
	} else {
		while ((c = getc (fp)) != EOF) {
			putc (c, stdout);
			if (c == '\n') {
				rows--;
				if (rows == 0) {
					if ((rows = morewait (NULLCHAR)) < 1) {
						break;
					}
				}
			}
		}
		fclose (fp);
		putc ('\n', stdout);
		putc ('\r', stdout);
	}
	return 0;
}

/* ************************************************************************* */

ENTRY int
dobytes (int argc, char *argv[], void *p)
{
	FILE *fp;
	int c;

	if ((fp = fopen (argv[1], READ_BINARY)) == NULLFILE) {
		printf ("Can't open %s", argv[1]);
		perror ("");
	} else {
		while ((c = getc (fp)) != EOF) {
			printf ("%x\n", c);
		}
		fclose (fp);
	}
	return 0;
}

/* ************************************************************************* */

ENTRY int
dowords (int argc, char *argv[], void *p)
{
	FILE *fp;
	int c;

	if ((fp = fopen (argv[1], READ_BINARY)) == NULLFILE) {
		printf ("Can't open %s", argv[1]);
		perror ("");
	} else {
		uint16 data;
		while ((c = getc (fp)) != EOF) {
			data = ((uint16) c) << 8;
			c = getc (fp);
			data = data | ((uint16) c & 0xff);
			printf ("%04x\n", data);
		}
		fclose (fp);
	}
	return 0;
}

/* ************************************************************************* */

ENTRY int
dohex (int argc, char *argv[], void *p)
{
	FILE *fp;
	int c;
	int rows = MOREROWS;
	uint32 offset = 0;
	char buffer[17];
	int len = 0;

	if ((fp = fopen (argv[1], READ_BINARY)) == NULLFILE) {
		printf ("Can't open %s", argv[1]);
		perror ("");
	} else {
		while ((c = getc (fp)) != EOF) {
			if ((offset & 0xf) == 0) {
				buffer[len] = 0;
				printf (" %s\n", buffer);
				len = 0;

				rows--;
				if (rows == 0) {
					if (argc > 2) {
						rows = MOREROWS;
						pause (200L);
					} else {
						if ((rows = morewait (NULLCHAR)) < 1) {
							break;
						}
					}
				}

				printf ("0x%06lx: ", offset);
			}
			printf ("%02x ", c);
			c &= 0x7f;
			if (c < 0x20) c = '.';
			if (c == 0x7f) c = '.';
			buffer[len++] = c;
			offset++;
		}
		buffer[len] = 0;
		printf (" %s\n", buffer);

		fclose (fp);
	}
	return 0;
}

/* ************************************************************************* */

/* ************************************************************************* */

LOCAL int
docreate (int argc, char *argv[], void *p)
{
	FILE *fp;
	int c;
	int cnt = 0;

	if ((fp = fopen (argv[1], WRITE_TEXT)) == NULLFILE) {
		printf ("Can't create %s", argv[1]);
		perror ("");
	} else {
		while ((c = getc (stdin)) != EOF) {
			if (c == '+') {
				cnt++;
				if (cnt == 3) {
					break;
				}
			} else {
				cnt = 0;
			}
			putc (c, fp);
			if (c == '\r') {
				putc ('\n', fp);
			}
		}
		fclose (fp);
		putc ('\n', stdout);
		putc ('\r', stdout);
	}
	return 0;
}

/* ************************************************************************* */

LOCAL int
doappend (int argc, char *argv[], void *p)
{
	FILE *fp;
	int c;
	int cnt = 0;

	if ((fp = fopen (argv[1], APPEND_TEXT)) == NULLFILE) {
		printf ("Can't create %s", argv[1]);
		perror ("");
	} else {
		while ((c = getc (stdin)) != EOF) {
			if (c == '+') {
				cnt++;
				if (cnt == 3) {
					break;
				}
			} else {
				cnt = 0;
			}
			putc (c, fp);
			if (c == '\r') {
				putc ('\n', fp);
			}
		}
		fclose (fp);
		putc ('\n', stdout);
		putc ('\r', stdout);
	}
	return 0;
}

/* ************************************************************************* */

LOCAL int
dofill (int argc, char *argv[], void *p)
{
	FILE *fp;
	int c;
	sint31 repeat, i;
	int cnt = 0;

	if (atoi32s_err (argv[2], &repeat)) {
		return 1;
	}
	if ((fp = fopen (argv[1], WRITE_TEXT)) == NULLFILE) {
		printf ("Can't create %s", argv[1]);
		perror ("");
	} else {
		while ((c = getc (stdin)) != EOF) {
			if (c == '+') {
				cnt++;
				if (cnt == 3) {
					break;
				}
			} else {
				cnt = 0;
			}
			if (c == '\r') {
				putc ('\r', fp);
				putc ('\n', fp);
			} else {
				i = repeat;
				while (i--) {
					putc (c, fp);
				}
			}
		}
		fclose (fp);
		putc ('\n', stdout);
		putc ('\r', stdout);
	}
	return 0;
}

/* ************************************************************************* */

LOCAL int
dodir (int argc, char *argv[], void *p)
{
	int i;
	printf ("Name             Size     Pointer\n");
	for (i = 0; i < DEFNFILES; i++) {
		if (Fds[i].use) {
			printf ("%16s %8ld 0x%08lx (%d)\n", Fds[i].name, (long) Fds[i].size, (long) Fds[i].data, i);
		}
	}

	fqstat ();
	return 0;
}

/* ************************************************************************* */

LOCAL int
dodelete (int argc, char *argv[], void *p)
{
	int i;

	for (i = 1;i < argc; i++) {
		if (unlink (argv[i]) == -1) {
			printf ("Can't delete %s: %d\n", argv[i], errno);
		}
	}
	return 0;
}

/* ************************************************************************* */

LOCAL int
dorename (int argc, char *argv[], void *p)
{
	if (rename (argv[1], argv[2]) == -1)
		printf ("Can't rename: %d\n", errno);
	return 0;
}

/* ************************************************************************* */

LOCAL int
doquit (int argc, char *argv[], void *p)
{
	struct session *sp = (struct session *) Curproc->session;

	printf ("End of Telnet session\n");
	fclose (sp->network);
	sp->network = NULLFILE;
	return 0;
}

/* ************************************************************************* */

/* ************************************************************************* */

LOCAL int
donull (int argc, char *argv[], void *p)
{
	return 0;
}

/* ************************************************************************* */

LOCAL int
dohostname (int argc, char *argv[], void *p)
{
	if (argc < 2) {
		printf ("%s\n", Hostname);
	} else {
		struct iface *ifp;
		char *name;
		int namelength;

		name = argv[1];
		if ((ifp = if_lookup (argv[1])) != NULLIF) {
			if ((name = resolve_a (ifp->address[AF_INET].sin_address, FALSE)) == NULLCHAR) {
				printf ("Interface address not resolved\n");
				return 1;
			}
		}

		if (Hostname != NULLCHAR)
			free (Hostname);
		Hostname = strdup (name);
		printf ("Hostname set to '%s'.\n", Hostname);

		/* remove trailing dot */
		if ((namelength = strlen (Hostname)) > 0
		&& Hostname[namelength -1] == '.') {
			Hostname[namelength -1] = '\0';
		}
	}
	return 0;
}

/* ************************************************************************* */

LOCAL int
dohelp (int argc, char *argv[], void *p)
{
	int level = 0;

	if (argv[0][1] == '?')
		level = 1;

	cmdhelp (Cmds, level);
	return 0;
}

/* ************************************************************************* */

LOCAL int
dorsthelp (int argc, char *argv[], void *p)
{
	cmdhelp (Restcmds, 0);
	return 0;
}

/* ************************************************************************* */

/* ************************************************************************* */

/* ************************************************************************* */

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

/* ************************************************************************* */

/* ************************************************************************* */

/* ************************************************************************* */

/* ************************************************************************* */

uint16 periodic_command_flag = 0;

ENTRY int
doperiodic (int argc, char *argv[], void *p)
{
	periodic_command_flag = 1;
	return 0;
}

/* ************************************************************************* */

ENTRY int
donoperiodic (int argc, char *argv[], void *p)
{
	periodic_command_flag = 0;
	return 0;
}

/* ************************************************************************* */

LOCAL int
doevent (int argc, char *argv[], void *p)
{
	uint16 event;
	uint16 channel = 0;

	if (atoi16uh_err (argv[1], &event)) {
		return 1;
	}

	if (argc > 2) {
		if (atoi16uh_err (argv[2], &channel))
			return 1;
	}

	printf ("Posting event 0x%04x on channel %d\n", event, channel);

	set_event (event);
	return 0;
}

/* ************************************************************************* */

ENTRY int
doboot (int argc, char *argv[], void *p)
{

	sys_nested_interrupt_disable ();

	if (argc >= 2) {
#Acode
		.ref	_c_int00
		b		_c_int00
#Ccode
	} else {
#Acode
		.noremark 5015
		b		0xff8000
#Ccode
	}

	return 0;
}

/* ************************************************************************* */

/* No-op command */
ENTRY int
donothing (int argc, char *argv[], void *p)
{
	return 0;
}

/* ************************************************************************* */

/* version command */
LOCAL int
doversion (int argc, char *argv[], void *p)
{
	printf ("LANsEND version %s\n", VOCAL_REVISION);
	return 0;
}

/* ************************************************************************* */

#include "v24/v24.h"
#include "csc/csc.h"
#include "dteif/dteif.h"
#include "sys/sys.h"
int csc_flag = -1;
struct proc *csc_proc = NULLPROC;
struct proc *csc_txproc = NULLPROC;

ENTRY void
lansend_return(void)
{
	csc_flag = -1;
}

LOCAL int
docsc (int argc, char *argv[], void *p)
{
	uint16 channel = 0;
	char name[10];
	int c, inmode, outmode, editmode, echomode;
	struct session * current_session;
	if (argc > 1) {
		if (atoi16u_err (argv[1], &channel)) {
			return -1;
		}
	}

	sprintf (name, "CSC_RX%d\n", channel);
	csc_proc = newproc(name,1024,csc_rx_proc,0,NULL,NULL,0);
	csc_txproc = Curproc;

	/* raw */
	current_session = Curproc->session;

	editmode = current_session->ttystate.edit;
	current_session->ttystate.edit = 0;

	echomode = current_session->ttystate.echo;
	current_session->ttystate.echo = 0;

	outmode = fmode (stdout, STREAM_BINARY);
	inmode = fmode (stdin, STREAM_BINARY);

	forever {
		if ((c = _fgetc(stdin)) != EOF){
			dteif_rx (c & 0xff);
		}
		if (csc_flag == -1) {
			break;
		}
	}

	/* cook */
	csc_proc = NULLPROC;
	csc_txproc = NULLPROC;
	current_session->ttystate.edit = editmode;
	current_session->ttystate.echo = echomode;
	fmode (stdout, outmode);
	fmode (stdin, inmode);

	return 0;
}

#define UART_TX_BUF_SIZE	8192
#define UART_RX_BUF_SIZE	128
extern uint8 far uart_tx_buf[UART_TX_BUF_SIZE];
extern int uart_tx_char_count;

LOCAL void
csc_rx_proc (int argc, void *argv, void *p)
{
	uint16 du;
	char   c;
	forever {
		pwait (NULL);
		if (csc_flag == -1) {
			break;
		}
		if (uart_tx_char_count >= (sizeof (uart_tx_buf) >> 1)) {
			continue;
		}

		du = dteif_tx ();
		if (!(du & V24_DU__NO_DATA_AVAILABLE)) {
			c = du & 0xff;
{
#define UART_TX_BUF_SIZE	8192
extern uint8 far uart_tx_buf[UART_TX_BUF_SIZE];

extern int uart_tx_char_count;
extern int uart_tx_read_index;
extern int uart_tx_write_index;
extern int console_tx_active;
			sys_nested_interrupt_disable ();

			uart_tx_buf[uart_tx_write_index++] = c;
			if (uart_tx_write_index == UART_TX_BUF_SIZE) {
				uart_tx_write_index = 0;
			}
			uart_tx_char_count++;

			if (console_tx_active == FALSE) {
				/* transmitter needs a kick-start */
				dteif_tx_start_disabled ();
			}
			sys_nested_interrupt_restore ();
}
		}
	}
}

LOCAL int
docscdial (int argc, char *argv[], void *p)
{
	uint16 channel = 0;
	uint16 temp_dp_autoselect_mask = DP_AUTOSELECT__BIT__NONE;
	uint16 temp_dp_compression_mask = (DP_COMP_MODE_TX__BF__OFF | DP_COMP_MODE_RX__BF__OFF);

	if (argc > 2) {
		if (atoi16u_err (argv[2], &channel)) {
			return -1;
		}
	}

	temp_dp_autoselect_mask = DP_AUTOSELECT__BIT__V42_DETECT;
	temp_dp_autoselect_mask |= DP_AUTOSELECT__BIT__MNP_AUTORELIABLE;

	temp_dp_compression_mask = (DP_COMP_MODE_TX__BF__REQUESTED | DP_COMP_MODE_RX__BF__REQUESTED);
	temp_dp_compression_mask = (temp_dp_compression_mask | DP_COMP_TYPE__BIT__V42BIS | DP_COMP_TYPE__BIT__MNP5);
	access_csc_pump_dm_wr_direct (parm__omc_dm_originate_en, TRUE);
	access_csc_pump_dm_wr_direct (parm__dial_originate_en, TRUE);
	access_csc_pump_dm_wr_array (parm__dial_string, argv[1], ((strlen(argv[1]) + 2) / sizeof(uint16)));
	access_csc_pump_dm_wr_direct (parm__dp_compression_mask, temp_dp_compression_mask);
	access_csc_pump_dm_wr_direct (parm__dp_autoselect_mask, temp_dp_autoselect_mask);

	printf("dialing %s on channel %d \n", argv[1], channel);

	pause(3000L);
	printf("setting omc_dial \n");
	set_event (EVENT__OMC_CMD_DIAL);
	pause(5000L);
	printf("setting modulation stop \n");
	set_event (EVENT__MODULATION_STOP);
	pause(500L);
	printf("setting cmd_connect \n");
	set_event (EVENT__OMC_CMD_CONNECT);

	return 0;
}

LOCAL int
docscanswer (int argc, char *argv[], void *p)
{

	uint16 channel = 0;
	uint16 temp_dp_autoselect_mask = DP_AUTOSELECT__BIT__NONE;
	uint16 temp_dp_compression_mask = (DP_COMP_MODE_TX__BF__OFF | DP_COMP_MODE_RX__BF__OFF);

	if (argc > 1) {
		if (atoi16u_err (argv[1], &channel)) {
			return -1;
		}
	}

	access_csc_pump_dm_wr_direct (parm__omc_dm_originate_en, FALSE);

	temp_dp_autoselect_mask = DP_AUTOSELECT__BIT__V42_DETECT;
	temp_dp_autoselect_mask |= DP_AUTOSELECT__BIT__MNP_AUTORELIABLE;

	temp_dp_compression_mask = (DP_COMP_MODE_TX__BF__REQUESTED | DP_COMP_MODE_RX__BF__REQUESTED);
	temp_dp_compression_mask = (temp_dp_compression_mask | DP_COMP_TYPE__BIT__V42BIS | DP_COMP_TYPE__BIT__MNP5);

	access_csc_pump_dm_wr_direct (parm__dp_compression_mask, temp_dp_compression_mask);
	access_csc_pump_dm_wr_direct (parm__dp_autoselect_mask, temp_dp_autoselect_mask);

	set_event (EVENT__OMC_CMD_HOOK_OFF);
	pause (50L);
	set_event (EVENT__OMC_CMD_CONNECT);
	return 0;

}

LOCAL int
docschangup (int argc, char *argv[], void *p)
{
	uint16 channel = 0;

	if (argc > 1) {
		if (atoi16u_err (argv[1], &channel)) {
			return -1;
		}
	}
	set_event (EVENT__OMC_CMD_DISCONNECT);
	pause (500L);
	set_event (EVENT__OMC_CMD_HOOK_ON);

	return 0;
}

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

/* Main command lookup and branch tables */
const struct cmds far Cmds[] = {

	{"@",			docmdfile,			0,	2,	"<file>"},

	{"account",		doaccount,			0,	0,	NULLCHAR},

	{"append",		doappend,			0,	2,	"<filename>"},

	{"at&f",		docsc,			 0,	0,	"[channel]"},
	{"csc",			docsc,			 0,	0,	"[channel]"},
	{"atd",		docscdial,			 1024,	0,	""},
	{"ata",		docscanswer,			 1024,	0,	""},
	{"ath",		docschangup,		 1024,	0,	"[channel]"},

/* This one is out of alpabetical order to allow abbreviation to "c" */

	{"console",		doconsole,			0,	2,	"<on|off> [process]"},

	{"create",		docreate,			0,	2,	"<filename>"},

/* This one is out of alpabetical order to allow abbreviation to "d" */

	{"date",		dodate,				0,	0,	"[yy-mm-dd]"},

	{"debug",		dodebug,			0,	0,	NULLCHAR},

	{"delete",		dodelete,			0,	2,	"<file>"},

	{"device",		do_device,			0,	0,	NULLCHAR},

	{"dir",			dodir,				0,	0,	""},

#ifdef DO_LANSEND_TERM_SHELL
	{"dshell",		dodshell,			0,	0,	NULLCHAR},
#endif /* DO_LANSEND_TERM_SHELL */

#ifdef DO_LANSEND_DEV_3COM_ETHERNET
	{"etherstat",	doetherstat,		0,	0,	""},
#endif /* DO_LANSEND_DEV_3COM_ETHERNET */

	{"event",		doevent,			0,	2,	"<event>"},

	{"files",		dofiles,			0,	0,	""},

	{"fill",		dofill,				0,	3,	"<filename> <count>"},

	{"help",		dohelp,				0,	0,	""},

	{"bytes",		dobytes,			0,	2,	"<file>"},
	{"words",		dowords,			0,	2,	"<file>"},
	{"hex",			dohex,				0,	2,	"<file>"},

	{"hostname",	dohostname,			0,	0,	"[name]"},

	{"http",		dohttp,				0,	0,	NULLCHAR},

	{"ip",			doip,				0,	0,	NULLCHAR},

	{"log",			dolog,				0,	0,	"[stop|filename]"},

	{"mdm",			do_mdm,				0,	0,	NULLCHAR},

#ifndef	DO_LANSEND_OS_UNIX
	{"memory",		domem,				0,	0,	NULLCHAR},
#endif /* DO_LANSEND_OS_UNIX */

	{"more",		domore,				0,	2,	"<file>"},

	{"ping",		doping,			 1024,	2,	"<hostid> [length [interval [incflag]]]"},

	{"ppp",			doppp_commands,		0,	0,	NULLCHAR},

	{"Process",		doprocess,			0,	0,	NULLCHAR},
	{"ps",			ps,					0,	0,	""},

	{"rename",		dorename,			0,	3,	"<oldfile> <newfile>"},

	{"session",		dosession,			0,	0,	"[session]"},

#ifdef DO_LANSEND_SMTP_CLIENT
	{"smtp",		dosmtp,				0,	0,	NULLCHAR},
#endif /* DO_LANSEND_SMTP_CLIENT */

	{"socket",		dosock,				0,	0,	"[socket]"},

	{"test",		dotest,				0,	0,	NULLCHAR},

	{"time",		dotime,				0,	0,	"[hh:mm[:ss]]"},

	{"trace",		dotrace,			0,	0,	"[iface [off|btio [tracefile]]]"},

	{"type",		domore,				0,	2,	"<filename>"},

	{"version",		doversion,			0,	0,	""},

	{"periodic",	doperiodic,			0,	0,	""},
	{"noperiodic",	donoperiodic,		0,	0,	""},

	{NULLCHAR}
};

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

/* Restricted command lookup and branch tables */
const struct cmds Restcmds[] = {

	{"help",		dorsthelp,			0,	0,	""},

	{"ps",			ps,					0,	0,	""},

	{"socket",		dosock,				0,	0,	""},

	{NULLCHAR}
};

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */
