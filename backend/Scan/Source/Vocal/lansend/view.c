
/* ************************************************************************* */
/*
 *	view.c
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

#include "net/net.h"
#include "sys/sys.h"
#include "dev/dev.h"

#include "ip/ip.h"

#include "lansend/local.h"

/* ************************************************************************* */

ENTRY int
doview (int argc, char *argv[], void *p)
{
	FILE *fp;

	if ((fp = fopen (argv[1], READ_TEXT)) == NULLFILE) {
		printf("Can't read %s\n",argv[1]);
		return 1;
	}
	newproc("view",512,view,0,(void *)fp,NULL,0);
	return 0;
}

/* ************************************************************************* */

/* Random-access file display program. Used both to read local
 * files with the "view" command, and by the FTP client to view
 * directory listings, temporary copies of read files, etc.
 *
 */
ENTRY void
view (int s, void *p1, void *p2)
{
	struct session *sp;
	FILE *fp;
	char *name;
	int c;
	sint31 offset = 0;
	int row, col;
	int cols = 80;
	int rows = 25;
	sint31 polldelay = 0;

	fp = (FILE *) p1;
	if (p2 != NULL)
		name = (char *) p2;
	else
		name = fpname (fp);

	if ((sp = newsession (name, VIEW, TRUE)) == NULLSESSION)
		return;

	if (p2 != NULL)
		free (name);

	if (s != 0)
		polldelay = s;
	sp->ctlproc = ctlproc;
	/* Put tty into raw mode so single-char responses will work */
	sp->ttystate.echo = sp->ttystate.edit = 0;
	for (;;) {
		fseek (fp, offset, SEEK_SET);
		putchar(ASCII__FF);	/* Clear screen */
		/* Display a screen's worth of data, keeping track of
		 * cursor location so we know when the screen is full
		 */
		col = row = 0;
		while ((c = getc (fp)), c != EOF) {
			switch (c) {
			case '\n':
				row++;
				col = 0;
				break;
			case '\t':
				if (col < cols - 8)
					col = (col + 8) & ~7;
				break;
			default:
				col++;
				break;
			}
			if (col >= cols) {
				/* Virtual newline caused by wraparound */
				col = 0;
				row++;
			}
			if (row >= rows)
				break;	/* Screen now full */
			putchar (c);
		}
		fflush (stdout);
		/* If we hit the end of the file and the file may be
		 * growing, then set an alarm to time out the getchar ()
		 */
		do {
			if (feof (fp) && polldelay != 0) {
				alarm (polldelay);
			}
			c = getchar();	/* Wait for user keystroke */
			alarm(0L);	/* Cancel alarm */
			if (c != -1 || errno != EALARM)
				break;	/* User hit key */
			/* Alarm timeout; see if more data arrived by
			 * clearing the EOF flag, trying to read
			 * another byte, and then testing EOF again
			 */
			clearerr (fp);
			(void) getc (fp);
			c = ' ';	/* Simulate a no-op keypress */
		} while (feof (fp));
		switch (c) {
		case 'h':	/* Home */
		case 'H':
		case '<':	/* For emacs users */
			offset = 0;
			break;
		case 'e':	/* End */
		case '>':	/* For emacs users */
			fseek (fp, 0L, SEEK_END);
			offset = lineseek (fp, ftell (fp), - rows, cols);
			break;
		case CTLD:	/* Down one half screen (for VI users) */
			if (!feof (fp))
				offset = lineseek (fp, offset, rows / 2, cols);
			break;
		case CTLU:	/* Up one half screen (for VI users) */
			offset = lineseek (fp, offset, - rows / 2, cols);
			break;
		case 'd':	/* down line */
		case CTLN:	/* For emacs users */
		case 'j':	/* For vi users */
			if (!feof (fp))
				offset = lineseek (fp, offset, 1, cols);
			break;
		case 'D':	/* Down page */
		case CTLV:	/* For emacs users */
			if (!feof (fp))
				offset = lineseek (fp, offset, rows, cols);
			break;
		case 'u':	/* up line */
		case CTLP:	/* for emacs users */
		case 'k':	/* for vi users */
			offset = lineseek (fp, offset, -1, cols);
			break;
		case 'U':	/* Up page */
		case 'v':	/* for emacs users */
			offset = lineseek (fp, offset, - rows, cols);
			break;
		case CTLC:
		case 'q':
		case 'Q':
		case ASCII__ESC:
			goto done;
		default:
			break;	/* Redisplay screen */
		}
	}
done:	fclose (fp);
	freesession (sp);
}

/* ************************************************************************* */

/* Given a starting offset into an open file stream, scan forwards
 * or backwards the specified number of lines and return a pointer to the
 * new offset.
 */
LOCAL sint31
lineseek (FILE *fp, sint31 start, int nlines, int width)
{
	sint31 offset;
	sint31 *pointers;
	int col = 0;
	int c;
	int newlines = 0;

	if (nlines == 0)
		return start;	/* Nothing to do */

	if (nlines > 0) {		/* Look forward requested # of lines */
		fseek (fp, start, SEEK_SET);
		col = 0;
		while ((c = getc (fp)), c != EOF) {
			switch (c) {
			case '\n':
				newlines++;
				col = 0;
				break;
			case '\t':
				if (col < width - 8)
					col = (col + 8) & ~7;
				break;
			default:
				col++;
				break;
			}
			if (col >= width) {
				/* Virtual newline caused by wraparound */
				col = 0;
				newlines++;
			}
			if (newlines >= nlines)
				break;	/* Found requested count */
		}
		return ftell(fp);	/* Could be EOF */
	}
	/* Backwards scan (the hardest)
	 * Start back up at most (width + 2) chars / line from the start.
	 * This handles full lines followed by expanded newline
	 * sequences
	 */
	nlines = - nlines;
	offset = (width + 2) *(nlines + 1);
	if (offset > start)
		offset = 0;	/* Go to the start of the file */
	else
		offset = start - offset;
	fseek (fp, offset, SEEK_SET);

	/* Keep a circular list of the last 'nlines' worth of offsets to
	 * each line, starting with the first
	 */
	pointers = calloc (sizeof (sint31), nlines);
	pointers[newlines++ % nlines] = offset;

	/* Now count newlines up but not including the original
	 * starting point
	 */
	col = 0;
	for (;;) {
		c = getc (fp);
		switch (c) {
		case EOF:
			goto done;
		case '\n':
			col = 0;
			offset = ftell (fp);
			if (offset >= start)
				goto done;
			pointers[newlines++ % nlines] = offset;
			break;
		case '\t':
			if (col < width - 8)
				col = (col + 8) & ~7;
			break;
		default:
			col++;
			break;
		}
		if (col >= width) {
			/* Virtual newline caused by wraparound */
			col = 0;
			offset = ftell (fp);
			if (offset >= start)
				goto done;
			pointers[newlines++ % nlines] = offset;
		}
	}
	done:;
	if (newlines >= nlines) {
		/* Select offset pointer nlines back */
		offset = pointers[newlines % nlines];
	} else {
		/* The specified number of newlines wasn't seen, so
		 * go to the start of the file
		 */
		offset = 0;
	}
	free (pointers);
	return offset;
}

/* ************************************************************************* */

/* Handle special keystrokes */
LOCAL int
ctlproc (int c)
{
	struct session *current = Active_session;
	FILE *in = current->input;

	switch (c) {
	case 256 + 71:	/* HOME */
		putc ('h', in);
		break;
	case 256 + 72:	/* Cursor up */
		putc ('u', in);
		break;
	case 256 + 73:	/* Page up */
		putc ('U', in);
		break;
	case 256 + 79:	/* End */
		putc ('e', in);
		break;
	case 256 + 80:	/* Cursor down */
		putc ('d', in);
		break;
	case 256 + 81:	/* Page down */
		putc ('D', in);
		break;
	}
	fflush (in);
	return 0;
}
