
/* ************************************************************************* */
/*
 *	stdio.c
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
 *	This file contains the standard I / O routines with socket support.
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

#define S_IREAD		O_RDONLY
#define S_IWRITE	O_WRONLY

/* ************************************************************************* */

#define _CREAT(a,b)	_creat((a),(b))
#define _OPEN(a,b)	_open((a),(b))
#define _CLOSE(a)	_close((a))
#define _READ(a,b,c)	_read((a),(b),(c))
#define _WRITE(a,b,c)	_write((a),(b),(c))
#define _LSEEK(a,b,c)	_lseek((a),(b),(c))
#define _DUP(a) 	dup((a))

/* ************************************************************************* */

extern char *Tmpfile;

FILE *_LFiles = NULLFILE;

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

ENTRY void
stdio_init (void)
{
	_LFiles = NULLFILE;
}

/* ************************************************************************* */

/* Open a file and associate it with a (possibly specified) stream */
ENTRY FILE *
freopen (const char *filename, char *mode, FILE *fp)
{
	int modef;
	int textmode = 0;
	int create = 0;
	int append = 0;
	int fd;
	struct stat statbuf;

	if (strchr (mode, 'r') != NULLCHAR) {
		modef = O_RDONLY;
	} else if (strchr (mode, 'w') != NULLCHAR) {
		create = 1;
		modef = O_WRONLY;
	} else if (strchr (mode, 'a') != NULLCHAR) {
		modef = O_WRONLY;
		append = 1;
		if (stat (filename, &statbuf) == -1 && errno == ENOENT) {
			create = 1;	/* Doesn't exist, so create */
		}
	} else {
		return NULLFILE;	/* No recognizable mode! */
	}

	if (strchr (mode, '+') != NULLCHAR)
		modef = O_RDWR; /* Update implies R/W */

	if (strchr (mode, 't') != NULLCHAR)
		textmode = 1;

	if (create) {
		fd = _CREAT (filename, S_IREAD | S_IWRITE);
	} else {
		fd = _OPEN (filename, modef);
	}
	if (fd == -1) {
		return NULLFILE;
	}

	if (fp != NULLFILE) {
		_fclose (fp);
	} else {
		if ((fp = _fcreat ()) == NULLFILE) {
			_CLOSE (fd);
			if (create) {
				unlink (filename);
			}
			return NULLFILE;
		}
	}
	fp->fd = fd;
	fp->offset = 0;
	fp->type = _FL_FILE;
	fp->bufmode = _IOFBF;
	fp->ptr = strdup (filename);
	if (textmode)
		fp->flags |= _FL_ASCII;
	if (append)
		fp->flags |= _FL_APPEND;
	fp->bufsize = BUFSIZ;
	seteol (fp, Eol);
	return fp;
}

/* ************************************************************************* */

/* Associate a file or socket descripter (small integer) with a stream */
ENTRY FILE *
fdopen (int handle, const char *mode)
{
	FILE *fp;
	int textmode = 0;
	int append = 0;

	if (handle == -1)
		return NULLFILE;

	if (strchr (mode, 'a') != NULLCHAR)
		append = 1;

	if (strchr (mode, 't') != NULLCHAR)
		textmode = 1;

	if ((fp = _fcreat ()) == NULLFILE)
		return NULLFILE;

	fp->fd = handle;
	fp->bufmode = _IOFBF;
	if (handle >= Nfiles)
		fp->type = _FL_SOCK;
	else
		fp->type = _FL_FILE;
	if (textmode)
		fp->flags |= _FL_ASCII;
	if (append)
		fp->flags |= _FL_APPEND;

	fp->bufsize = BUFSIZ;
	/* set default eol sequence, can be overridden by user */
	switch (fp->type) {
	case _FL_SOCK:
		seteol(fp,eolseq(handle));	/* Socket eol seq */
		break;
	case _FL_FILE:
		seteol(fp,Eol); /* System end-of-line sequence */
		break;
	}
	fp->refcnt = 1;

	return fp;
}

/* ************************************************************************* */

/* Create a stream in pipe mode (whatever is written can be
 * read back) . These always work in binary mode.
 */
ENTRY FILE *
pipeopen (void)
{
	FILE *fp;

	if ((fp = _fcreat ()) == NULLFILE)
		return NULLFILE;

	fp->fd = -1;
	fp->type = _FL_PIPE;
	fp->bufmode = _IOFBF;
	fp->bufsize = BUFSIZ;

	strcpy(fp->eol,"\r\n");
	return fp;
}

/* ************************************************************************* */

/* Create a new display screen and associate it with a stream. */
ENTRY FILE *
displayopen (const char *mode, int noscrol)
{
	FILE *fp;
	int textmode = 0;

	if (strchr (mode, 't') != NULLCHAR)
		textmode = 1;

	if ((fp = _fcreat ()) == NULLFILE)
		return NULLFILE;

	fp->fd = -1;
	fp->type = _FL_DISPLAY;
	fp->bufmode = _IOFBF;
	if (textmode)
		fp->flags |= _FL_ASCII;

	fp->ptr = newserial (NROWS, NCOLS, noscrol);
	fp->bufsize = BUFSIZ;
	strcpy(fp->eol,"\r\n");
	return fp;
}

/* ************************************************************************* */

/* Read string from stdin into buf until newline, which is not retained */
ENTRY char *
gets (char *s)
{
	int c;
	char *cp;

	cp = s;
	for (;;) {
		if ((c = getc (stdin)) == EOF)
			return NULLCHAR;

		if (uchar (c) == '\n')
			break;

		if (s != NULLCHAR)
			*cp++= c;
	}
	if (s != NULLCHAR)
		*cp = '\0';
	return s;
}

/* ************************************************************************* */

/* Read a line from a stream into a buffer, retaining newline */
ENTRY char *
fgets (char *buf, int len, FILE *fp)
{
	int c;
	char *cp;

	cp = buf;
	while (len-- > 1) {	/* Allow room for the terminal null */
		if ((c = getc (fp)) == EOF) {
			return NULLCHAR;
		}
		if (c == '\r')
			c = '\n';
		if (buf != NULLCHAR)
			*cp++= c;
		if (uchar (c) == '\n')
			break;
	}
	if (buf != NULLCHAR)
		*cp = '\0';
	return buf;
}

/* ************************************************************************* */

/* Do printf on a stream */
ENTRY int
fprintf (FILE *fp, const char *fmt, ...)
{
	va_list args;
	int len;

	va_start (args, fmt);
	len = vfprintf (fp, fmt, args);
	va_end (args);
	return len;
}

/* ************************************************************************* */

/* Printf on standard output stream */
ENTRY int
printf (const char *fmt, ...)
{
	va_list args;
	int len;

	va_start (args, fmt);
	len = vfprintf (stdout, fmt, args);
	va_end (args);
	return len;
}

/* ************************************************************************* */

/* The guts of printf, uses variable arg version of sprintf */
ENTRY int
vprintf (const char *fmt, va_list args)
{
	return vfprintf (stdout, fmt, args);
}

/* ************************************************************************* */

/* The guts of printf, uses variable arg version of sprintf */
ENTRY int
vfprintf (FILE *fp, const char *fmt, va_list args)
{
	int len, cnt, withargs;
	char *buf;

	if (fp == NULLFILE || fp->cookie != _COOKIE)
		return -1;
	if (strchr (fmt, '%') == NULLCHAR) {
		/* Common case optimization: no args, so we don't
		 * need vsprintf ()
		 */
		withargs = 0;
		buf = (char *)fmt;
	} else {
		/* Use a default value that is hopefully longer than the
		 * biggest output string we'll ever print (!)
		 */
		withargs = 1;
		buf = (char *) mallocw (PRINTF_BUFSIZ);
		generic_vsnprintf (buf, BUFSIZ, fmt, args);
	}
	len = strlen (buf);
	cnt = fwrite (buf, 1, len, fp);
	if (cnt != len)
		cnt = -1;
	if (withargs)
		free (buf);
	return cnt;
}

/* ************************************************************************* */

/* put a char to a stream */
ENTRY int
fputc (int c, FILE *fp)
{
	int nbytes;
	struct mbuf *bp;
	int eol;

	if (c == '\n' && (fp->flags & _FL_ASCII)) {
		nbytes = strlen (fp->eol);
		eol = 1;
	} else {
		nbytes = 1;
		eol = 0;
	}
	bp = fp->obuf;
	if (bp != NULLBUF && bp->size - bp->cnt < nbytes && fflush (fp) == EOF)
		return EOF;
	if (fp->obuf == NULLBUF)
		fp->obuf = ambufw (max (nbytes, fp->bufsize));

	bp = fp->obuf;
	if (eol)
		memcpy (&bp->data[bp->cnt], fp->eol, nbytes);
	else {
		bp->data[bp->cnt] = c;
	}
	bp->cnt += nbytes;

	if (bp->cnt == bp->size || (fp->bufmode == _IONBF)
	 || ((fp->bufmode == _IOLBF) && eol)) {
		if (fflush (fp) == EOF)
			return EOF;
	}
	return c;
}

/* ************************************************************************* */

/* put a string to a stream */
ENTRY int
fputs (char *buf, FILE *fp)
{
	int cnt, len;

	len = strlen (buf);
	cnt = fwrite (buf, 1, len, fp);
	if (cnt != len)
		return EOF;
	return uchar (buf[len -1]);
}

/* ************************************************************************* */

/* Put a string to standard output */
ENTRY int
puts (char *s)
{
	if (fputs (s, stdout) == EOF)
		return EOF;
	putchar ('\n');
	return 1;
}

/* ************************************************************************* */

/* Peek at a character from the stream if available */

#define	favail(fp)	(((fp) != NULLFILE) && ((fp)->ibuf != NULLBUF) && ((fp)->ibuf->cnt != 0))

ENTRY int
fpeek (FILE *fp)
{
	int c;

	if (favail(fp)) {
		c = _fgetc (fp);
		if (c != EOF) {
			ungetc (c, fp);
		}
		return c;
	}
	return EOF;			/* Return EOF to indicate nothing available, but it may not be a true EOF condition */
}

/* ************************************************************************* */

/* Read a character from the stream */
ENTRY int
fgetc (FILE *fp)
{
	int c;

	if (fp == NULLFILE || fp->cookie != _COOKIE)
		return EOF;
	c = _fgetc (fp);
	if (c == EOF || !(fp->flags & _FL_ASCII) || c != fp->eol[0])
		return c;
	/* First char of newline sequence encountered */
	if (fp->eol[1] == '\0')
		return '\n';    /* Translate 1-char eol sequence */
	/* Try to read next input character */
	if ((c = _fgetc (fp)) == EOF)
		return fp->eol[0];	/* Got a better idea? */
	if (c == fp->eol[1]) {
		/* Translate two-character eol sequence into newline */
		return '\n';
	} else {
		/* CR-NUL sequence on Internet -> bare CR (kludge?) */
		if (c != '\0')
			ungetc (c, fp);
		/* Otherwise return first char unchanged */
		return fp->eol[0];
	}
}

/* ************************************************************************* */

/* Read a character from a stream without newline processing */
ENTRY int
_fgetc (FILE *fp)
{
	struct mbuf *bp;

	if (fp == NULLFILE || fp->cookie != _COOKIE)
		return EOF;
	fflush (fp);
	if ((bp = fp->ibuf) == NULLBUF || bp->cnt == 0)
		if (_fillbuf (fp, 1) == NULLBUF)
			return EOF;
	return PULLCHAR (&fp->ibuf);
}

/* ************************************************************************* */

/* Flush output on a stream. All actual output is done here. */
ENTRY int
fflush (FILE *fp)
{
	struct mbuf *bp;

	if (fp == NULLFILE) {
		flushall ();
		return 0;
	}

	if (fp->cookie != _COOKIE)
		return 0;

	if (fp->obuf == NULLBUF)
		return 0;	/* Nothing to do */

	bp = fp->obuf;
	fp->obuf = NULLBUF;
	switch (fp->type) {
	case _FL_PIPE:
		append (&fp->ibuf, bp);
		psignal (&fp->ibuf, 1);
		while (len_p (fp->ibuf) >= BUFSIZ)
			pwait(&fp->obuf);	/* Hold at hiwat mark */
		return 0;
	case _FL_SOCK:
		return send_mbuf (fp->fd, bp, 0, NULLCHAR, 0);
	case _FL_FILE:
		do {
			int cnt;
			if (fp->flags & _FL_APPEND)
				_LSEEK (fp->fd, 0L, SEEK_END);
			else
				_LSEEK (fp->fd, fp->offset, SEEK_SET);
			cnt = _WRITE (fp->fd, bp->data, bp->cnt);
			if (cnt > 0)
				fp->offset += cnt;
			if (cnt != bp->cnt) {
				fp->flags |= _FL_ERR;
				free_p (bp);
				return EOF;
			}
			bp = free_mbuf (bp);
		} while (bp != NULLBUF);
		return 0;
	case _FL_DISPLAY:
		do {

			serialwrite ((struct display *) fp->ptr, bp->data, bp->cnt);

			bp = free_mbuf (bp);

		} while (bp != NULLBUF);
		return 0;
	}
	return 0;	/* Can't happen */
}

/* ************************************************************************* */

/* Set the end-of-line sequence on a stream */
ENTRY int
seteol (FILE *fp, char *seq)
{
	if (fp == NULLFILE || fp->cookie != _COOKIE)
		return -1;
	if (seq != NULLCHAR)
		strncpy (fp->eol, seq, sizeof (fp->eol));
	else
		*fp->eol = '\0';
	return 0;
}

/* ************************************************************************* */

/* Enable/disable eol translation, return previous state */
ENTRY int
fmode (FILE *fp, int mode)
{
	int prev;

	if (fp == NULLFILE || fp->cookie != _COOKIE)
		return -1;
	fflush (fp);
	prev = (fp->flags & _FL_ASCII) ? STREAM_ASCII : STREAM_BINARY;
	switch (mode) {
	case STREAM_ASCII:	/* Turn on ascii translation */
		fp->flags |= _FL_ASCII;
		break;
	case STREAM_BINARY:	/* Turn it off */
		fp->flags &= ~_FL_ASCII;
		break;
	case STREAM_NOFILL:	/* turn off buffer filling on fread */
		fp->flags |= _FL_NOFILL;
		break;
	case STREAM_FILL:	/* turn on buffer filling on fread */
		fp->flags &= ~_FL_NOFILL;
		break;
	default:
		break;
	}
	return prev;
}

/* ************************************************************************* */

ENTRY int
fclose (FILE *fp)
{
	if (fp == NULLFILE || fp->cookie != _COOKIE) {
		return -1;
	}
	if (--fp->refcnt != 0) {
		return 0;	/* Others are still using it */
	}
	_fclose (fp);
	if (fp->prev != NULLFILE)
		fp->prev->next = fp->next;
	else
		_LFiles = fp->next;

	if (fp->next != NULLFILE)
		fp->next->prev = fp->prev;
	free (fp);
	return 0;
}

/* ************************************************************************* */

ENTRY int
fseek (FILE *fp, sint31 offset, int whence)
{

	if (fp == NULLFILE || fp->cookie != _COOKIE || fp->type != _FL_FILE) {
		errno = EINVAL;
		return -1;
	}
	fflush(fp);	/* Flush output buffer */
	/* On relative seeks, adjust for data in input buffer */
	switch (whence) {
	case SEEK_SET:
		fp->offset = offset;	/* Absolute seek */
		break;
	case SEEK_CUR:
		/* Relative seek, adjusting for buffered data */
		fp->offset += offset - len_p (fp->ibuf);
		break;
	case SEEK_END:
		break;
	}
	/* Toss input buffer */
	free_p (fp->ibuf);
	fp->ibuf = NULLBUF;
	fp->flags &= ~_FL_EOF;
	return 0;
}

/* ************************************************************************* */

ENTRY sint31
ftell (FILE *fp)
{
	if (fp == NULLFILE || fp->cookie != _COOKIE || fp->type != _FL_FILE)
		return -1;
	fflush (fp);
	return fp->offset /* - len_p(fp->ibuf) */;
}

/* ************************************************************************* */

ENTRY int
ungetc (int c, FILE *fp)
{
	if (fp == NULLFILE || fp->cookie != _COOKIE)
		return -1;

	if (c == '\n' && (fp->flags & _FL_ASCII)) {
		int len = strlen (fp->eol);
		pushdown (&fp->ibuf, len);
		memcpy (fp->ibuf->data, fp->eol, len);
	} else {
		pushdown (&fp->ibuf, 1);
		*fp->ibuf->data = c;
	}
	return c;
}

/* ************************************************************************* */

ENTRY size_t
fwrite (void *ptr, size_t size, size_t n, FILE *fp)
{
	struct mbuf *bp;
	char *icp, *ocp;
	size_t bytes;
	size_t cnt;
	size_t asize;
	int room;
	int newlines = 0;
	int eollen = 1;
	int doflush = 0;

	if (fp == NULLFILE || fp->cookie != _COOKIE || size == 0)
		return 0;
	icp = (char *) ptr;
	bytes = size*n;

	/* Optimization for large binary file writes */
	if (fp->type == _FL_FILE && !(fp->flags & _FL_ASCII) && bytes >= fp->bufsize) {
		fflush (fp);
		if (fp->flags & _FL_APPEND)
			_LSEEK (fp->fd, 0L, SEEK_END);
		else
			_LSEEK (fp->fd, fp->offset, SEEK_SET);
		cnt = _WRITE (fp->fd, icp, bytes);
		if (cnt > 0)
			fp->offset += cnt;

		if (cnt != bytes)
			return cnt / size;
		return n;
	}

	if (fp->flags & _FL_ASCII) {
		/* Count the newlines in the input buffer */
		newlines = memcnt ((char *) ptr, '\n', bytes);
		if (newlines != 0) {
			eollen = strlen (fp->eol);
			if (fp->flags & _IOLBF)
				doflush = 1;
		}
	}
	while (bytes != 0) {
		bp = fp->obuf;
		if (bp != NULLBUF && (bp->cnt + eollen) > bp->size) {
			/* Current obuf is full; flush it */
			if (fflush (fp) == EOF)
				return (bytes - n*size) / size;
		}
		if ((bp = fp->obuf) == NULLBUF) {
			/* Allocate a new output buffer. The size is the
			 * larger of the buffer size or the amount of data
			 * we have to write (including any expanded newlines)
			 */
			asize = bytes + (eollen -1) *newlines;
			asize = max (fp->bufsize, asize);
			bp = fp->obuf = ambufw (asize);
		}
		if ((fp->flags & _FL_ASCII) && newlines != 0) {
			/* Copy text to buffer, expanding newlines */
			ocp = bp->data + bp->cnt;
			room = bp->size - bp->cnt;
			for (;room >= eollen && bytes != 0;icp++, bytes--) {
				if (*icp == '\n') {
					memcpy (ocp, fp->eol, eollen);
					ocp += eollen;
					room -= eollen;
					newlines--;
				} else {
					*ocp++= *icp;
					room--;
				}
			}
			bp->cnt = ocp - bp->data;
		} else {
			/* Simply copy binary data to buffer */
			cnt = min (bp->size - bp->cnt, bytes);
			memcpy (bp->data + bp->cnt, icp, cnt);
			bp->cnt += cnt;
			icp += cnt;
			bytes -= cnt;
		}
	}
	/* The final flush. Flush if the stream is unbuffered,
	 * the output buffer is full, or the stream is line buffered
	 * and we've written at least one newline (not necessarily the
	 * last character)
	 */
	if (fp->bufmode == _IONBF || bp->cnt == bp->size || doflush) {
		if (fflush (fp) == EOF) {

			return (bytes - n*size) / size;
		}
	}
	return n;
}

/* ************************************************************************* */

LOCAL struct mbuf *
_fillbuf (FILE *fp, int cnt)
{
	struct mbuf *bp;

	if (fp->ibuf != NULLBUF)
		return fp->ibuf;	/* Stuff already in the input buffer */

	switch (fp->type) {
	case _FL_PIPE:
		while (fp->ibuf == NULLBUF)
			if ((errno = pwait(&fp->ibuf)) != 0)	/* Wait for something */
				return NULLBUF;
		psignal(&fp->obuf,1);	/* Reawaken writer, if any */
		return fp->ibuf;
	case _FL_SOCK:
		/* Always grab everything available from a socket */
		if (recv_mbuf (fp->fd, &fp->ibuf, 0, 0, NULLCHAR, 0) <= 0
		 && errno != EALARM) {
			fp->flags |= _FL_EOF;
		}
		return fp->ibuf;
	case _FL_FILE:
		/* Read from file */
		cnt = max (fp->bufsize, cnt);
		bp = ambufw (cnt);
		_LSEEK (fp->fd, fp->offset, SEEK_SET);
		cnt = _READ (fp->fd, bp->data, cnt);
		if (cnt < 0)
			fp->flags |= _FL_ERR;
		if (cnt == 0)
			fp->flags |= _FL_EOF;
		if (cnt <= 0) {
			free_p(bp);	/* Nothing successfully read */
			return NULLBUF;
		}
		fp->offset += cnt;	/* Update pointer */
		/* Buffer successfully read, store it */
		bp->cnt = cnt;
		fp->ibuf = bp;
		return bp;
	case _FL_DISPLAY:	/* Displays are write-only */
		return NULLBUF;
	}
	return NULLBUF; /* Can't happen */
}

/* ************************************************************************* */

ENTRY size_t
fread (void *ptr, size_t size, size_t n, FILE *fp)
{
	struct mbuf *bp;
	size_t bytes;
	size_t cnt;
	int c;
	size_t tot = 0;
	char *ocp;
	char *cp;

	if (fp == NULLFILE || fp->cookie != _COOKIE || size == 0)
		return 0;
	fflush (fp);
	bytes = n*size;

	ocp = (char *) ptr;
	while (bytes != 0) {
		/* Optimization for large binary file reads */
		if (fp->ibuf == NULLBUF
		 && fp->type == _FL_FILE && !(fp->flags & _FL_ASCII)
		 && bytes >= BUFSIZ) {
			_LSEEK (fp->fd, fp->offset, SEEK_SET);
			tot = _READ (fp->fd, ocp, bytes);
			if (tot > 0)
				fp->offset += tot;
			if (tot != bytes)
				return tot / size;
			return n;
		}
		/* Replenish input buffer if necessary */
		if (fp->ibuf == NULLBUF && _fillbuf (fp, bytes) == NULLBUF) {
			/* Must have hit eof or had error */
			return tot / size;
		}
		/* In this pass, read the lesser of the buffer size,
		 * the requested amount, or the amount up to the next
		 * eol sequence (if ascii mode)
		 */
		bp = fp->ibuf;
		cnt = min (bp->cnt, bytes);
		if ((fp->flags & _FL_ASCII)
		 && (cp = (char *) memchr (bp->data, fp->eol[0], cnt)) != NULLCHAR)
			cnt = min (cnt, (size_t) (cp - bp->data));
		if (cnt != 0) {
			cnt = pullup (&fp->ibuf, ocp, cnt);
			ocp += cnt;
			tot += cnt;
			bytes -= cnt;
		} else {
			/* Hit a eol sequence, use fgetc to translate */
			if ((c = fgetc (fp)) == EOF)
				return tot / size;

			*ocp++= c;
			tot++;
			bytes--;
		}
		if (fp->flags & _FL_NOFILL)
			return tot / size;
	}
	return n;
}

/* ************************************************************************* */

ENTRY void
perror (char *s)
{
	char * buf;
	if (errno < 36) {
		switch (errno) {
		case 0      :  buf = "No error";                  break;
		case EDOM   :  buf = "Domain error";              break;
		case ERANGE :  buf = "Range error";               break;
		case ENOENT :  buf = "No such file or directory"; break;
		case EFPOS  :  buf = "File positioning error";    break;
		case EILSEQ :
		default     :  buf = "Unknown error";             break;
		}
		fprintf(stderr,"%s: %s\n",s,buf);
	}
	else if (errno <= EMAX)
		fprintf(stderr,"%s: %s\n",s,Sock_errlist[errno-36]);
	else
		fprintf(stderr,"%s: errno %d\n",s,errno);
}

/* ************************************************************************* */

ENTRY int
setvbuf (FILE *fp, char *buf, int type, int size)
{
	if (fp == NULLFILE || fp->cookie != _COOKIE)
		return -1;
	if (size == 0)
		type = _IONBF;
	switch (type) {
	case _IOFBF:
		fp->bufsize = size;
		break;
	case _IOLBF:
		fp->bufsize = size;
		break;
	case _IONBF:
		fp->bufsize = 1;
		break;
	default:
		return -1;	/* Invalid */
	}
	fp->bufmode = type;
	fflush (fp);
	return 0;
}

/* ************************************************************************* */

ENTRY void
setbuf (FILE *fp, char *buf)
{
	if (buf == NULLCHAR)
		setvbuf (fp, NULLCHAR, _IONBF, 0);
	else
		setvbuf (fp, buf, _IOFBF, BUFSIZ);
}

/* ************************************************************************* */

ENTRY FILE *
tmpfile (void)
{
	FILE *fp;

	fp = fopen (Tmpfile, "w+b");
	if (fp != NULLFILE)
		fp->flags |= _FL_TMP;
	return fp;
}

/* ************************************************************************* */

/* Do everything to close a stream except freeing the descriptor
 * The reference count is left unchanged, and the descriptor is still
 * on the list
 */
LOCAL void
_fclose (FILE *fp)
{
	if (fp == NULLFILE || fp->cookie != _COOKIE)
		return;
	fflush (fp);
	switch (fp->type) {
	case _FL_SOCK:
		close_s (fp->fd);
		break;
	case _FL_FILE:
		_CLOSE (fp->fd);
		fp->offset = 0;
		break;
	case _FL_DISPLAY:
		closeserial ((struct display *) fp->ptr);
		fp->ptr = NULL;
		break;
	}
	free_p(fp->obuf);	/* Should be NULLBUF anyway */
	fp->obuf = NULLBUF;
	free_p (fp->ibuf);
	fp->ibuf = NULLBUF;
	if ((fp->flags & _FL_TMP) && Refcnt[fp->fd] == 0)
		unlink ((const char *) fp->ptr);
	free (fp->ptr);
	fp->ptr = NULLCHAR;
	fp->flags = 0;
	fp->fd = -1;
}

/* ************************************************************************* */

/* allocate a new file pointer structure, init a few fields and put on list */
LOCAL FILE *
_fcreat (void)
{
	FILE *fp;

	if ((fp = (FILE *) calloc (1, sizeof (FILE))) == NULLFILE)
		return NULLFILE;

	fp->cookie = _COOKIE;
	fp->refcnt = 1;
	fp->next = _LFiles;
	_LFiles = fp;
	if (fp->next != NULLFILE)
		fp->next->prev = fp;
	return fp;
}

/* ************************************************************************* */

ENTRY int
read (int fd, void *buf, unsigned cnt)
{
	if (fd < 0 || fd >= Nfiles + Nsock) {
		errno = EINVAL;
		return -1;
	} else if (fd < Nfiles)
		return _READ (fd, buf, cnt);
	else
		return recv (fd, (char *)buf, cnt, 0);
}

/* ************************************************************************* */

ENTRY int
write (int fd, CONST void *buf, unsigned cnt)
{
	if (fd < 0 || fd >= Nfiles + Nsock) {
		errno = EINVAL;
		return -1;
	} else if (fd < Nfiles)
		return _WRITE (fd, buf, cnt);
	else
		return send (fd, (char *) buf, cnt, 0);
}

/* ************************************************************************* */

ENTRY int
lseek (int fd, sint31 offset, int whence)
{
	return _LSEEK (fd, offset, whence);
}

/* ************************************************************************* */

ENTRY int
open (const char *filename, int mode)
{
	return _OPEN (filename, mode);
}

/* ************************************************************************* */

ENTRY int
create (const char *filename, int mode)
{
	return _CREAT (filename, mode);
}

/* ************************************************************************* */

ENTRY int
close (int fd)
{
	if (fd < 0 || fd >= Nfiles + Nsock) {
		errno = EINVAL;
		return -1;
	} else if (fd < Nfiles)
		return _CLOSE (fd);
	else
		return close_s (fd);
}

/* ************************************************************************* */

ENTRY void
fcloseall (void)
{
	FILE *fp, *fpnext;

	flushall ();
	for (fp = _LFiles;fp != NULLFILE;fp = fpnext) {
		fpnext = fp->next;
		if (fp->fd > 2)
			fclose (fp);
	}
}

/* ************************************************************************* */

ENTRY void
flushall (void)
{
	FILE *fp;

	for (fp = _LFiles;fp != NULLFILE;fp = fp->next) {
		fflush (fp);
	}
}

/* ************************************************************************* */

ENTRY FILE *
fdup (FILE *fp)
{
	FILE *nfp;

	if (fp == NULLFILE || fp->cookie != _COOKIE)
		return NULLFILE;	/* Invalid arg */
	switch (fp->type) {
	case _FL_FILE:
		/* Allocate new file pointer structure so each can
		 * have its own read / write pointer and buffering
		 */
		if ((nfp = _fcreat ()) == NULLFILE)
			return NULLFILE;
		nfp->fd = _DUP (fp->fd);
		nfp->offset = fp->offset;
		nfp->type = fp->type;
		nfp->bufmode = fp->bufmode;
		nfp->flags = fp->flags;
		strcpy (nfp->eol, fp->eol);
		nfp->bufsize = fp->bufsize;
		nfp->ptr = strdup ((const char *) fp->ptr);
		fp = nfp;
		break;
	case _FL_SOCK:	/* These just share the same file pointer */
	case _FL_DISPLAY:
	case _FL_PIPE:
		fp->refcnt++;
		break;
	}
	return fp;
}

/* ************************************************************************* */

ENTRY char *
fpname (FILE *fp)
{
	if (fp == NULLFILE || fp->cookie != _COOKIE)
		return NULLCHAR;
	if (fp->type == _FL_FILE)
		return (char *) fp->ptr;
	return NULLCHAR;
}

/* ************************************************************************* */

/* ************************************************************************* */

ENTRY int
dofiles (int argc, char *argv[], void *p)
{
	FILE *fp;
	int i;
	int flags;

	printf("fp       fd  ref  eol   type mod buf  flags\n");
	for (fp = _LFiles;fp != NULLFILE;fp = fp->next) {
		printf("%8lx ",(uint32)fp);
		if (fp->fd != -1)
			printf("%-3d",fp->fd);
		else
			printf("   ");
		printf(" %-3d ",fp->refcnt);
		for (i = 0;i < EOL_LEN -1;i++) {
			if (fp->eol[i] != '\0')
				printf(" %02x",fp->eol[i]);
			else
				printf("   ");
		}
		flags = fp->flags;
		switch (fp->type) {
		case _FL_SOCK:
			printf(" sock");
			break;
		case _FL_FILE:
			printf(" file");
			break;
		case _FL_DISPLAY:
			printf(" disp");
			break;
		case _FL_PIPE:
			printf(" pipe");
			break;
		}
		printf("%4s",(flags & _FL_ASCII) ? " txt" : " bin");
		switch (fp->bufmode) {
		case _IONBF:
			printf(" none");
			break;
		case _IOLBF:
			printf(" line");
			break;
		case _IOFBF:
			printf(" full");
			break;
		}
		if (flags & _FL_EOF)
			printf(" EOF");
		if (flags & _FL_ERR)
			printf(" ERR");
		if (flags & _FL_APPEND)
			printf(" APND");
		if (flags & _FL_TMP)
			printf(" TMP");
		if (flags & _FL_NOFILL)
			printf(" NOFILL");
		if (fp->type == _FL_FILE && fp->ptr != NULLCHAR)
			printf(" (%s seek=%lu)",(char *)fp->ptr,ftell(fp));
		putchar ('\n');
	}
	return 0;
}
