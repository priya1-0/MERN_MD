
/* ************************************************************************* */
/*
 *	sys.h
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
 *	This file contains global declarations for the SYS module.
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

#ifndef _SYS_SYS_H
#define _SYS_SYS_H

struct sockaddr;

#include "sys/sysd.h"

#include "sys/cmdparse.h"
#include "sys/display.h"
#include "sys/files.h"
#include "sys/filesys.h"
#include "sys/mbuf.h"
#include "sys/timer.h"
#include "sys/stdio.h"

#include "sys/session.h"

#include "sys/proc.h"

#include <stdlib.h>
#include <ctype.h>

/* ************************************************************************* */

/* ************************************************************************* */

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

#define sprintf SYS_sprintf
int sscanf (char*, char *fmt, ...);
void tmpnam (char * tmpname);

/* This section contains missing declarations */

/* Convert a pointer to a long integer */
#define ptol(p)	((sint31)(p))
/* convert a long integer to a pointer */
#define ltop(l)	((void*)(l))

/* ************************************************************************* */

extern char * sys_errlist[];
int access (char*, int);

#define HUGE
#define FAR

/* ************************************************************************* */

struct ffblk {
	int ff_attrib;
	int ff_fsize;
	int ff_ftime;
	int ff_fdate;
	char ff_name[12];
};
#define FA_HIDDEN	0x0002
#define FA_SYSTEM	0x0004
#define FA_DIREC	0x0008

struct dirsort {
	struct dirsort *next;
	struct ffblk de;
};

/* ************************************************************************* */

void (*getirq (uint16 irq)) (void);

/* ************************************************************************* */

/*- MKHEADER Begin -*/

/* Global Routines: */

/* alloc.c */
void alloc_init (void);
void * mallocw (size_t nb);
void * callocw (size_t nelem, size_t size);
int availmem (void);
int domem (int argc, char *argv[], void *p);
void gcollect (int i, void *v1, void *v2);

/* cmdparse.c */
void cmdnotfound (void);
void cmdhelp (const struct cmds tab[], int level);
int cmderror (const struct cmds *cmdp, int argc, char *argv[]);
int cmdparse (const struct cmds cmds[], register char *line, void *p);
int cmdprefix (char *argv[]);
int subcmd (const struct cmds tab[], int argc, char *argv[], void *p);
int ifacecmd (int check, const struct cmds tab[], int argc, char *argv[], void *p);
int chg_bool (int *var, char *label, int argc, char *argv[]);
int chg_bit16 (uint16 *bits, uint16 mask, char *label, int argc, char *argv[]);
int chg_int32s (sint31 *var, char *label, int argc, char *argv[]);
int chg_int16u (uint16 *var, char *label, int argc, char *argv[]);
int chg_int16s (sint15 *var, char *label, int argc, char *argv[]);
int chg_int16u_max (uint16 *var, char *label, int argc, char *argv[], uint16 max);
int chg_int8u (uint8 *var, char *label, int argc, char *argv[]);
int chg_addr (struct sockaddr *addr, uint16 family, char *label, int argc, char *argv[]);
int chg_mask (uint32 *mask, char *label, int argc, char *argv[]);
int chg_timer (struct timer *t, char *label, int argc, char *argv[]);

/* filesys.c */
void filesys_init (void);
void packed_data_read (void *dst, uint32 src, sint31 len);
void packed_data_write (uint32 dst, void *src, sint31 len);
void read_from_file_space (struct file_entry *fds, void *dst, sint31 len);
void write_to_file_space (struct file_entry *fds, void *src, sint31 len);
int _creat (const char *file, int mode);
int _open (const char *file, int mode);
int dup (int fd);
int _close (int fd);
int _read (int fd, void *buf, unsigned cnt);
int _write (int fd, const void *buf, unsigned cnt);
sint31 _lseek (int fd, sint31 offset, int whence);
char * fversion (int fd);
int sversion (int fd, const char *version);
int remove (const char *file);
int unlink (const char *file);
int rename (const char *oldfile, const char *newfile);
int fstat (int fd, struct stat *statbuf);
int stat (const char *file, struct stat *statbuf);
sint15 showdirentry (int fd, int full, FILE *fp);
uint16 get_flbkqlen(void);
void fbuf_init (void);
void fqstat (void);
struct fblk * alloc_fblk (void);
void free_fblk (struct fblk *blk);

/* getopt.c */
int getopt (int argc, char **argv, char *opts);

/* kernel.c */
void kernel_init (void);
struct proc * mainproc (char *name);
struct proc * newproc (char *name, unsigned int stksize, void (*pc) (int, void*, void*), int iarg, void *parg1, void *parg2, int freeargs);
void killproc (struct proc *pp);
void killself (void);
void killall (void);
void killer (int i, void *v1, void *v2);
void suspend (struct proc *pp);
void resume (struct proc *pp);
void setpriority (struct proc *pp, sint15 priority);
void alert (struct proc *pp, int val);
void alert_event (void *event, int n, int val);
int pwait (void *event);
void psignal (void *event, int n);
void chname (struct proc *pp, char *newname);

/* ksubr.c */
void kinit (void);
int ps (int argc, char *argv[], void *p);
int stkutil (register uint16 * sp, unsigned int size);
void chkstk (void);
void psetup (struct proc *pp, int iarg, void *parg1, void *parg2, void (*pc) (void));
void procstartup (void);
unsigned phash (void *event);
int atoproc_err (char *cp, struct proc **pp);
int doconsole (int argc, char *argv[], void *p);
int doprocess (int argc, char *argv[], void *p);

/* mbuf.c */
void mbuf_init (void);
void refiq (void);
void iqstat (void);
struct mbuf * alloc_ibuf (uint16 size, sint15 adjust);
struct mbuf * alloc_mbuf (uint16 size);
struct mbuf * ambufw (uint16 size);
struct mbuf * free_mbuf (register struct mbuf *bp);
struct mbuf * free_p (register struct mbuf *bp);
void free_q (struct mbuf **q);
uint16 len_p (register struct mbuf *bp);
uint16 len_q (register struct mbuf *bp);
void trim_mbuf (struct mbuf **bpp, uint16 length);
uint16 dup_p (struct mbuf **hp, struct mbuf *bp, uint16 offset, uint16 cnt);
struct mbuf * copy_p (struct mbuf *bp, uint16 cnt);
uint16 pullup (struct mbuf **bph, char *buf, uint16 cnt);
uint16 pullup_packed (struct mbuf **bph, uint16 *buf, uint16 cnt);
void pushdown (struct mbuf **bph, uint16 size);
uint8 * tackdown (struct mbuf **bph, uint16 size);
void append (struct mbuf **bph, struct mbuf *bp);
void enqueue (struct mbuf **q, struct mbuf *bp);
struct mbuf * dequeue (register struct mbuf **q);
struct mbuf * qdata (char *data, uint16 cnt);
uint16 dqdata (struct mbuf *bp, char *buf, uint16 cnt);
uint32 pull32 (struct mbuf **bpp);
sint31 pull16 (struct mbuf **bpp);
sint15 pullchar (struct mbuf **bpp);
int write_p (FILE *fp, struct mbuf *bp);
void mbuf_crunch (struct mbuf **bpp);

/* misc.c */
char * smsg (char *msgs[], uint16 nmsgs, uint16 n);
void rip (register char *s);
int memcnt (char *buf, char c, int size);
char * strdup (const char *s);
int log2 (uint16 x);

/* pathname.c */
char * pathname (char *cd, char *path);

/* serial.c */
void serial_init (void);
struct display * newserial (int rows, int cols, int noscrol);
void closeserial (struct display *dp);
void serialwrite (struct display *dp, char *buf, int cnt);

/* session.c */
void session_init (void);
void sessinit (void);
struct session * sessptr (char *cp);
int dosession (int argc, char *argv[], void *p);
int dosessionshow (int argc, char *argv[], void *p);
int dogo (int argc, char *argv[], void *p);
int doclose (int argc, char *argv[], void *p);
int doreset (int argc, char *argv[], void *p);
int dokick (int argc, char *argv[], void *p);
struct session * newsession (char *name, int type, int makecur);
void freesession (struct session *sp);
int keywait (char *prompt, int flush);
int morewait (char *prompt);
void sesflush (void);

/* stdio.c */
void stdio_init (void);
FILE * freopen (const char *filename, char *mode, FILE *fp);
FILE * fdopen (int handle, const char *mode);
FILE * pipeopen (void);
FILE * displayopen (const char *mode, int noscrol);
char * gets (char *s);
char * fgets (char *buf, int len, FILE *fp);
int fprintf (FILE *fp, const char *fmt, ...);
int printf (const char *fmt, ...);
int vprintf (const char *fmt, va_list args);
int vfprintf (FILE *fp, const char *fmt, va_list args);
int fputc (int c, FILE *fp);
int fputs (char *buf, FILE *fp);
int puts (char *s);
int fpeek (FILE *fp);
int fgetc (FILE *fp);
int _fgetc (FILE *fp);
int fflush (FILE *fp);
int seteol (FILE *fp, char *seq);
int fmode (FILE *fp, int mode);
int fclose (FILE *fp);
int fseek (FILE *fp, sint31 offset, int whence);
sint31 ftell (FILE *fp);
int ungetc (int c, FILE *fp);
size_t fwrite (void *ptr, size_t size, size_t n, FILE *fp);
size_t fread (void *ptr, size_t size, size_t n, FILE *fp);
void perror (char *s);
int setvbuf (FILE *fp, char *buf, int type, int size);
void setbuf (FILE *fp, char *buf);
FILE * tmpfile (void);
int read (int fd, void *buf, unsigned cnt);
int write (int fd, CONST void *buf, unsigned cnt);
int lseek (int fd, sint31 offset, int whence);
int open (const char *filename, int mode);
int create (const char *filename, int mode);
int close (int fd);
void fcloseall (void);
void flushall (void);
FILE * fdup (FILE *fp);
char * fpname (FILE *fp);
int dofiles (int argc, char *argv[], void *p);

/* string.c */
int stricmp (const char *string1, const char *string2);
int strnicmp (const char *string1, const char *string2, size_t n);

/* sys.c */
void sys_module_reset (void);
void sys_startup (void);

/* ti.c */
void ti_sys_init (void);
char * itoa (sint7 balance, char tmp[11], int len);
int random (int i);
int tisetjmp (sint31 *env);
int tilongjmp (sint31 *env, int returnvalue);
uint8 large_buf_strcat (sint31 dest, const char *src, uint32 size);
uint32 large_buf_strlen (sint31 cs);
uint8 large_buf_strcpy (sint31 dest, const char *src, uint32 size);

/* timer.c */
void timer_init (void);
void timerproc (int i, void *v1, void *v2);
void start_timer (struct timer *t);
void stop_timer (struct timer *timer);
sint31 read_timer (struct timer *t);
void set_timer (struct timer *t, sint31 interval);
int pause (sint31 ms);
void alarm (sint31 ms);
void ctick (void);
void pctick (void);
sint31 msclock (void);
sint31 secclock (void);
time_t time (time_t *timer);
int stime (time_t *timer);

/* ttydrvr.c */
void keyboard_init (void);
void keyboard (int i, void *v1, void *v2);
char * ttydrvr (struct session *sp, char c);

/*- MKHEADER End -*/


/* ************************************************************************* */

#endif /* _SYS_SYS_H */
