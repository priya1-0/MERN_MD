
/* ************************************************************************* */
/*
 *	session.c
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
 *	This file contains the user control functions.
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

#include "lansend/lansend.h"
#include "utils/utils.h"

/* ************************************************************************* */

extern const struct cmds Cmds[];

static char Badsess[] = "Invalid session\n";

/* ************************************************************************* */

char *Sestypes[] = {
	"",
	"Telnet",
	"FTP",
	"AX25",
	"Finger",
	"Ping",
	"NET/ROM",
	"Command",
	"More",
	"Hopcheck",
	"Tip",
	"PPP PAP",
	"Dial",
	"Query",
	"Cache",
	"Trace",
	"Remote"
};

struct user_s **Users = (struct user_s **)NULL;			/* User entry array */

struct session *Active_session = (struct session *) NULL;

char Session_escape = 0x1d;				/* Default escape character is ^] */

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

ENTRY void
session_init (void)
{
	Users = (struct user_s **)NULL;			/* User entry array */
	Active_session = (struct session *) NULL;

	Session_escape = 0x1d;
}

/* ************************************************************************* */

/* Initialize user session array */
ENTRY void
sessinit (void)
{
	int i;
	if (Users != (struct user_s **) NULL)
		return;	/* Already initialized */
	Users = (struct user_s **) callocw (Nusers, sizeof (struct user_s *));
	for (i = 0; i < Nusers; i++) {
		Users[i] = NULLUSER;
	}
}

/* ************************************************************************* */

/* Convert a character string containing a decimal session index number
 * into a pointer. If the arg is NULLCHAR, use the current default session.
 * If the index is out of range or unused, return NULLSESSION.
 */
ENTRY struct session *
sessptr (char *cp)
{
	register struct session *sp = Active_session;
	struct user_s *master = Users[sp->user];
	uint16 i;

	if (cp == NULLCHAR)
		return master->recent;

	i = (uint16) atoi (cp);
	if (i >= Nsessions)
		return NULLSESSION;
	else
		return master->list[i];
}

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* "session" subcommands */
static const struct cmds Sessioncmds[] = {
	{"close",		doclose,			0,	0,	"[number]"},
	{"escape",		doescape,			0,	0,	"[char]"},
	{"go",			dogo,				0,	0,	"[number]"},
	{"kick",		dokick,				0,	0,	"[number]"},
	{"show",		dosessionshow,		0,	0,	""},
	{"reset",		doreset,			0,	0,	"[number]"},
	{NULLCHAR},
};

/* ************************************************************************* */

/* Select and display sessions */
ENTRY int
dosession (int argc, char *argv[], void *p)
{

	return subcmd (Sessioncmds, argc, argv, p);
}

ENTRY int
dosessionshow (int argc, char *argv[], void *p)
{
	struct session *sp = Active_session;
	struct user_s *master = Users[sp->user];
	struct sockaddr fsocket;
	int i, k, n, r, s, t;
	char *cp;

	printf(" #  S#  Type     Rcv-Q Snd-Q State        User Ed Ec Remote socket\n");
	for (n = 0; n < Nsessions; n++) {
		sp = master->list[n];

		if (sp == NULLSESSION)
			continue;

		r = 0;
		t = 0;
		cp = NULLCHAR;

		if ((sp->network != NULLFILE)
		   && ((s = fileno (sp->network)) != -1)
		) {
			i = SOCKSIZE;
			k = getpeername (s, (char *) &fsocket, &i);
			r += socklen (s, 0);
			t += socklen (s, 1);
			cp = sockstate (s);
		}
		printf("%c%-3u%-4d%-8s%6d%6d %-13s %4d %d %d ",
			(master->recent == sp) ? '*':' ',
			sp->session_num,
			s,
			Sestypes[sp->type],
			r,
			t,
			(cp != NULLCHAR) ? cp : "",
			sp->user,
			sp->ttystate.edit,
			sp->ttystate.echo
		);

		if (sp->name != NULLCHAR)
			printf(" %s",sp->name);
		if (sp->network != NULLFILE && k == 0)
			printf(" (%s)",snhptoa(&fsocket));
		printf("\n");

		if (sp->record != NULLFILE)
			printf("    Record: %s\n",fpname(sp->record));
		if (sp->upload != NULLFILE)
			printf("    Upload: %s\n",fpname(sp->upload));
	}
	return 0;
}

/* ************************************************************************* */

/* Resume current session, and wait for it */
ENTRY int
dogo (int argc, char *argv[], void *p)
{
	register struct session *current = Active_session;
	register struct user_s *master = Users[current->user];
	struct session *sp = Users[current->user]->recent;

	if (argc > 1)
		sp = sessptr (argv[1]);

	if (sp == NULLSESSION)
		sp = master->recent;

	if (sp == NULLSESSION)
		return 0;

	if (master->active->session_num != 0)
		master->recent = master->active;
	master->active = sp;
	Active_session = sp;
	alert (master->display, EABORT);
	return 0;
}

/* ************************************************************************* */

ENTRY int
doclose (int argc, char *argv[], void *p)
{
	register struct session *current = Active_session;
	struct session *sp = Users[current->user]->recent;

	if (argc > 1)
		sp = sessptr (argv[1]);

	if (sp == NULLSESSION) {
		printf (Badsess);
		return -1;
	}
	shutdown (fileno (sp->network), 1);
	return 0;
}

/* ************************************************************************* */

ENTRY int
doreset (int argc, char *argv[], void *p)
{
	register struct session *current = Active_session;
	struct session *sp = Users[current->user]->recent;

	if (argc > 1)
		sp = sessptr (argv[1]);

	if (sp == NULLSESSION) {
		printf (Badsess);
		return -1;
	}
	/* Unwedge anyone waiting for a domain resolution, etc */
	alert (sp->proc0, EABORT);
	shutdown (fileno (sp->network), 2);
	return 0;
}

/* ************************************************************************* */

ENTRY int
dokick (int argc, char *argv[], void *p)
{
	register struct session *current = Active_session;
	struct session *sp = Users[current->user]->recent;

	if (argc > 1)
		sp = sessptr (argv[1]);

	if (sp == NULLSESSION) {
		printf (Badsess);
		return -1;
	}
	sockkick (fileno (sp->network));
	return 0;
}

/* ************************************************************************* */

extern char Session_escape;

LOCAL int
doescape (int argc, char *argv[], void *p)
{
	if (argc < 2)
		printf ("0x%x\n", Session_escape);
	else
		Session_escape = *argv[1];
	return 0;
}

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

ENTRY struct session *
newsession (char *name, int type, int makecur)
{
	register struct session *sp;
	register struct user_s *master;
	int i;

	if ((sp = (struct session *) calloc (1, sizeof (struct session))) == NULLSESSION) {
		printf("No space for session\n");
		return NULLSESSION;
	}

	if (type == COMMAND || type == REMCMD) {
		for (i = 0; i < Nusers; i++) {
			if (Users[i] == NULLUSER)
				break;
		}

		if (i == Nusers) {
			printf("Too many users\n");
			free (sp);
			return NULLSESSION;
		}

		master = Users[i] = (struct user_s *) callocw (1, sizeof (struct user_s));
		master->list = (struct session **)  callocw (Nsessions, sizeof (struct session *));
		master->user = i;
		master->recent = master->active = sp;

		i = 0;	/* command session */
	} else {
		register struct session *current = Active_session;
		master = Users[current->user];

		for (i = 0; i < Nsessions; i++) {
			if (master->list[i] == NULLSESSION)
				break;
		}

		if (i == Nsessions) {
			free (sp);
			printf("Too many sessions\n");
			return NULLSESSION;
		}

		/* check for temporary use of master record */
		if (master->list[0]->record != NULLFILE) {
			sp->record = master->list[0]->record;
			master->list[0]->record = NULLFILE;
		}
	}
	master->list[i] = sp;
	sp->user = master->user;
	sp->session_num = i;
	sp->type = type;

	if (name != NULLCHAR)
		sp->name = strdup (name);

	sp->proc0 = Curproc;
	sp->processes = 1;

	/* Create standard input and output sockets. Output is
	 * in text mode by default
	 */
	fclose (stdin);
	stdin =  sp->input = pipeopen ();
	setvbuf (stdin, NULLCHAR, _IONBF, 0);

	fclose (stdout);

	if (sp->user == 0) {
		stdout = sp->output = displayopen("wt",0);
	} else {
		stdout = sp->output = pipeopen ();
		fmode (stdout, STREAM_NOFILL);
	}

	Curproc->session = sp;

	/* on by default */
	sp->ttystate.crnl = sp->ttystate.edit = sp->ttystate.echo = TRUE;
	sp->ttystate.rows = MOREROWS;

	/* change from old session to new session */
	if (makecur) {
		master->recent = master->active;
		master->active = sp;
		Active_session = sp;
		alert (master->display, 1);
	}
	return sp;
}

/* ************************************************************************* */

ENTRY void
freesession (struct session *sp)
{
	struct user_s *master;

	if (sp == NULLSESSION)
		return;

	if (sp->session_num == 0)
		killsessions ();

	pwait(NULL);	/* Wait for any pending output to go */

	sp->proc0->session = NULL;
	if (sp->proc1 != NULLPROC) {
		killproc (sp->proc1);
		sp->proc1 = NULLPROC;
	}
	if (sp->proc2 != NULLPROC) {
		killproc (sp->proc2);
		sp->proc2 = NULLPROC;
	}

	free (sp->ttystate.line);
	sp->ttystate.line = NULLCHAR;

	if (sp->network != NULLFILE) {
		fclose (sp->network);
		sp->network = NULLFILE;
	}
	if (sp->record != NULLFILE) {
		fclose (sp->record);
		sp->record = NULLFILE;
	}
	if (sp->upload != NULLFILE) {
		fclose (sp->upload);
		sp->upload = NULLFILE;
	}
	free (sp->name);
	sp->name = NULLCHAR;
	sp->type = FREE;

	if (sp->input != NULLFILE) {
		fclose (sp->input);
		sp->input = NULLFILE;
	}
	if (sp->output != NULLFILE) {
		fclose (sp->output);
		sp->output = NULLFILE;
	}

	master = Users[sp->user];

	if (sp->session_num == 0) {
		Users[sp->user] = NULLUSER;
		free (master->list);
		free (master);
	} else {
		master->list[sp->session_num] = NULLSESSION;
	}

	if (master->recent == sp) {
		master->recent = master->list[0];
	}
	if (master->active == sp) {
		master->active = master->list[0];
		Active_session = master->list[0];
		alert (master->display, 1);
	}

	free (sp);
}

/* ************************************************************************* */

LOCAL void
killsessions (void)
{
	register struct session *current = Active_session;
	struct user_s *master = Users[current->user];
	struct session **list = master->list;
	struct session *sp;
	char found;
	int i;

	for (;;)
	{
		found = FALSE;

		for (i = 1; i < Nsessions; i++)
		{
			if ((sp = list[i]) != NULLSESSION)
			{
				if (sp == Active_session) {
					Active_session = list[0];
					alert (master->display, 1);
				}

				found = TRUE;
				alert (sp->proc0, EABORT);
				shutdown (fileno (sp->network), 2);
			}
		}

		if (found)
			pwait (NULL);
		else
			break;
	}
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

/* Print prompt and read one character */
ENTRY int
keywait (char *prompt, int flush)
{
	int c;
	int i;
	int len;

	if (prompt == NULLCHAR)
		prompt = "Hit enter to continue";
	len = strlen (prompt);

	printf (prompt);
	fflush (stdout);
	c = _fgetc (stdin);

	/* Get rid of the prompt */
	for (i = len;i != 0;i--)
		putchar ('\b');
	for (i = len;i != 0;i--)
		putchar (' ');
	for (i = len;i != 0;i--)
		putchar ('\b');

	fflush (stdout);
	return (int) c;
}

/* ************************************************************************* */

/* Print prompt, read one character, determine nuber of lines to display */
ENTRY int
morewait (char *prompt)
{
	struct session *sp = Active_session;
	int echo, edit;
	int d, rows;

	if (prompt == NULLCHAR)
		prompt = "--More--";

	/* Put tty into raw mode so single-char responses will work */
	echo = sp->ttystate.echo;
	edit = sp->ttystate.edit;
	sp->ttystate.echo = sp->ttystate.edit = 0;

	d = keywait (prompt, 0);

	/* Default to display a full screen */
	rows = sp->ttystate.rows;

	/* Various characters to end the display */
	if (d == -1) rows = -1;
	if (d == 'q') rows = -1;
	if (d == 'Q') rows = -1;
	if (d == ASCII__ESC) rows = -1;

	/* Advance only a single rows */
	if (d == '\n') rows = 1;
	if (d == '\r') rows = 1;

	/* Restore the tty mode */
	sp->ttystate.echo = echo;
	sp->ttystate.edit = edit;

	return rows;
}

/* ************************************************************************* */

/* Flush the current session's standard output. Called on every clock tick */
ENTRY void
sesflush (void)
{
	register struct session *current = Active_session;
	struct session *sp = Users[current->user]->active;

	if (sp != NULLSESSION)
		fflush (sp->output);

}
