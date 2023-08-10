
/* ************************************************************************* */
/*
 *	ttydrvr.c
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
 *  Terminal mode line editing input routine.
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

#define	OFF	0
#define	ON	1

#define	LINESIZE	256

/* ************************************************************************* */

/* Keyboard input buffer */
#define KBSIZE  256
static struct {
	char buf[KBSIZE];
	char *wp;
	char *rp;
	volatile int cnt;
} Keyboard;			/* Initialized at run-time in ioinit below */

extern char Session_escape;

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

ENTRY void
keyboard_init (void)
{
	/* Initialize keyboard queue */
	Keyboard.rp = Keyboard.wp = Keyboard.buf;
	/* Initialize keyboard queue */
	Keyboard.rp = Keyboard.wp = Keyboard.buf;
}

/* ************************************************************************* */
/*
 *	Routines used in PC and x86 versions
 *
 *	(Actually, all versions should be able to use these same functions
 *
 */

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

/* Keyboard input process */
ENTRY void
keyboard (int i, void *v1, void *v2)
{
	struct session *current;
	struct user_s *master;
	int c;
	char *cp;

	/* Keyboard process loop */
	forever {
		c = kbread ();

		current = Active_session;
		master = Users[current->user];

		if ((c == Session_escape) && (Session_escape != 0) && (current != master->list[0])) {
			/* Save current tty mode and set cooked */
			master->recent = current;
			current = master->list[0];
			master->active = current;
			Active_session = current;
			alert (master->display, 1);
		} else

		/* Ordinary ASCII character, hand to tty editor */
		if ((cp = ttydrvr (current, (char) c)) != NULLCHAR) {
			if (*cp == 0) {
				fputc (0, current->input);
			} else {
				fputs (cp, current->input);
			}
			fflush (current->input);
			free (cp);
		}

	}
}

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */
/*
 *  Function: ttydrvr
 *
 *  Accept characters from the incoming tty buffer and process them
 *  (if in cooked mode) or just pass them directly (if in raw mode) .
 *
 *  Echoing (if enabled) is direct to the raw terminal.  This requires
 *  recording (if enabled) of locally typed info to be done by the session
 *  itself so that edited output instead of raw input is recorded.
 *
 *  Parameters:
 *    "sp" is a pointer to the session structure
 *    "c" is the character to be processed
 *
 *  Returns: 0 for success always
 *  Returns: pointer to completed line
 *           or NULLCHAR pointer if no line completed
 *
 */
ENTRY char *
ttydrvr (struct session *sp, char c)
{
	char *cp, *rp;

	switch (sp->ttystate.edit) {
	case OFF:
		cp = (char *) mallocw (2);
		rp = cp;

		*cp++= c;
		*cp = '\0';
		if (sp->ttystate.echo)
			fputc (c, Curproc->output);
		return rp;
	case ON:
		if (sp->ttystate.line == NULLCHAR) {
			sp->ttystate.line = (char *) calloc (1, LINESIZE);
			sp->ttystate.lp = sp->ttystate.line;
			if (sp->ttystate.line == NULL) {
				return NULLCHAR;
			}
		}

		cp = sp->ttystate.lp;
		rp = sp->ttystate.line;
		/* Perform cooked-mode line editing */
		switch (uchar (c)) {
		case ASCII__ESC:		/* ESC terminates the line as well */
			*cp++= c;
			c = '\n';			/* Fall into CR code */
		case '\r':				/* CR and LF both terminate the line */
		case '\n':
			if (sp->ttystate.crnl)
				*cp++= '\n';
			else
				*cp++= c;
			*cp++= '\0';
			if (sp->ttystate.echo)
				putc ('\n', Curproc->output);

			sp->ttystate.line = NULLCHAR;
			return rp;
		case ASCII__DEL:
		case '\b':				/* Character delete */
			if (sp->ttystate.lp != rp) {
				sp->ttystate.lp--;
				if (sp->ttystate.echo)
					fputs ("\b \b", Curproc->output);
			}
			break;
		case CTLR:				/* print line buffer */
			if (sp->ttystate.echo) {
				fprintf (Curproc->output, "^R\n");
				fwrite (rp, 1, (size_t) (cp - rp), Curproc->output);
			}
			break;
		case CTLU:				/* Line kill */
			while (sp->ttystate.lp != rp) {
				sp->ttystate.lp--;
				if (sp->ttystate.echo) {
					fputs ("\b \b", Curproc->output);
				}
			}
			break;
		default:				/* Ordinary character */
			*cp++= c;

			/* ^Z apparently hangs the terminal emulators under
			 * DoubleDos and Desqview. I REALLY HATE having to patch
			 * around other people's bugs like this ! ! !
			 */
			if (sp->ttystate.echo &&

				c != CTLZ &&

				cp - rp < LINESIZE -1) {
				putc (c, Curproc->output);

			}
			else if (cp - rp >= LINESIZE -1) {
				putc ('\007', Curproc->output);		/* Beep */
				cp--;
			}
			sp->ttystate.lp = cp;
			break;
		}
		break;
	}
	return NULLCHAR;
}
