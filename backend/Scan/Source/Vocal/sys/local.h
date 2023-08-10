
/* ************************************************************************* */
/*
 *	local.h
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
 *	This file contains the private declarations for the SYS module.
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

#ifndef _SYS_LOCAL_H
#define _SYS_LOCAL_H

#include "sys/locald.h"
#include "sys/sys.h"

/* ************************************************************************* */

extern uint16 Refcnt[DEFNFILES];

/* ************************************************************************* */

/*- MKHEADER Begin -*/

/* Local Routines: */

/* alloc.c */

#ifdef sys_alloc_c
static int dopeek (int argc, char *argv[], void *p);
static int dopoke (int argc, char *argv[], void *p);
static int dostat (int argc, char *argv[], void *envp);
static int dofreelist (int argc, char *argv[], void *envp);
static int dosizes (int argc, char *argv[], void *p);
static int donibufs (int argc, char *argv[], void *p);
static int doibufsize (int argc, char *argv[], void *p);
static int dothresh (int argc, char *argv[], void *p);
#endif /* sys_alloc_c */

/* cmdparse.c */

#ifdef sys_cmdparse_c
static char * stringparse (char *line);
#endif /* sys_cmdparse_c */

/* filesys.c */

#ifdef sys_filesys_c
static void filefree (uint32 ptr);
#endif /* sys_filesys_c */

/* kernel.c */

#ifdef sys_kernel_c
static int procsigs (void);
static void psig (void *event, int n, int val);
static void delproc (struct proc *entry);
static void addproc (struct proc *entry);
#endif /* sys_kernel_c */

/* ksubr.c */

#ifdef sys_ksubr_c
static void pproc (struct proc *pp);
static void conproc (struct proc *pp, int mode);
static int doalert (int argc, char *argv[], void *p);
static int dokill (int argc, char *argv[], void *p);
static int dopriority (int argc, char *argv[], void *p);
static int doresume (int argc, char *argv[], void *p);
static int dosignal (int argc, char *argv[], void *p);
static int dosuspend (int argc, char *argv[], void *p);
#endif /* sys_ksubr_c */

/* pathname.c */

#ifdef sys_pathname_c
static void crunch (char *buf, register char *path);
#endif /* sys_pathname_c */

/* session.c */

#ifdef sys_session_c
static int doescape (int argc, char *argv[], void *p);
static void killsessions (void);
#endif /* sys_session_c */

/* stdio.c */

#ifdef sys_stdio_c
static struct mbuf * _fillbuf (FILE *fp, int cnt);
static void _fclose (FILE *fp);
static FILE * _fcreat (void);
#endif /* sys_stdio_c */

/* timer.c */

#ifdef sys_timer_c
static void t_alarm (void *x);
#endif /* sys_timer_c */

/*- MKHEADER End -*/


/* ************************************************************************* */

#endif /* _SYS_LOCAL_H */
