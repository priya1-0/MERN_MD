
/* ************************************************************************* */
/*
 *	stdio.h
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

#ifndef _SYS_STDIO_H
#define _SYS_STDIO_H

struct stat {
    sint15 st_dev;
    sint15 st_ino;
    sint15 st_mode;
    sint15 st_nlink;
    int   st_uid;
    int   st_gid;
    sint15 st_rdev;
    sint31  st_size;
    sint31  st_atime;
    sint31  st_mtime;
    sint31  st_ctime;
};

#define	EOL_LEN	3

struct _file{
	unsigned cookie;		/* Detect bogus file pointers */
#define	_COOKIE	0xdead
	int refcnt;
	struct _file *prev;
	struct _file *next;

	/* These two entries used only when type == _FL_FILE */
	int fd;			/* File descriptor or socket index */
	sint31 offset;		/* Seek offset */

	int type;
#define	_FL_SOCK	1	/* Associated with network socket */
#define	_FL_FILE	2	/* Associated with file */
#define	_FL_DISPLAY	3	/* Associated with display driver */
#define	_FL_PIPE	4	/* Pipe mode */

	int bufmode;		/* Output buffering mode */
#define	_IOFBF	1		/* Full buffering */
#define	_IOLBF	2		/* Line buffering */
#define	_IONBF	3		/* No buffering */

	int flags;
#define	_FL_ERR		0x1	/* Error on stream */
#define	_FL_EOF		0x2	/* EOF seen */
#define	_FL_ASCII	0x4	/* Ascii (newline translate) mode */
#define	_FL_APPEND	0x8	/* Always seek to end before writing */
#define	_FL_TMP		0x10	/* Delete on close */
#define _FL_NOFILL	0x20	/* Read only first mbuf on fread */
	struct mbuf *obuf;	/* Output buffer */
	struct mbuf *ibuf;	/* Input buffer */
	char eol[EOL_LEN];	/* Text mode end-of-line sequence, if any */
	int bufsize;		/* Size of buffer to use */
	void *ptr;		/* File name or display pointer */
};

typedef struct _file FILE;

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned int size_t;
#endif /* _SIZE_T */

#ifndef NULL
#define	NULL	(void *)0
#endif /* NULL */

#define	BUFSIZ			1500
#define	PRINTF_BUFSIZ	2000
#define	EOF				(-1)
#define	L_tmpnam		13

#define	SEEK_SET		0
#define	SEEK_CUR		1
#define	SEEK_END		2

#define	stdout	Curproc->output
#define	stdin	Curproc->input
#define	stderr	Curproc->output

#define	STREAM_BINARY	0
#define	STREAM_ASCII	1
#define STREAM_NOFILL	2
#define STREAM_FILL		3

/* Macros */
#define	feof(fp)	((fp)->flags & _FL_EOF)
#define ferror(fp)	((fp)->flags & _FL_ERR)
#define	fileno(fp)	((fp) != NULLFILE ? (fp)->fd : -1)
#define fopen(s,m)	(freopen((s),(m),NULLFILE))
#define	putc(c,fp)	(fputc((c),(fp)))
#define	getc(fp)	(fgetc((fp)))
#define	getchar()	(getc(stdin))
#define	clearerr(fp)	((fp)->flags &= ~(_FL_EOF|_FL_ERR))
#define rewind(fp)	((void)fseek((fp),0L,SEEK_SET),clearerr((fp)))
#define	putchar(c)	(putc((c),stdout))

#endif /* _SYS_STDIO_H */
