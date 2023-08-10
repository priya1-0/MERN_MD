
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
 *	Module:		LANSEND
 *
 *	This file contains the private declarations for the LANSEND module.
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

#ifndef _LANSEND_LOCAL_H
#define _LANSEND_LOCAL_H

#include "lansend/locald.h"
#include "lansend/lansend.h"

/* ************************************************************************* */

/*- MKHEADER Begin -*/

/* Local Routines: */

/* account.c */

#ifdef lansend_account_c
static int doaccadd (int argc, char *argv[], void *p);
static int doaccdrop (int argc, char *argv[], void *p);
static int doaccshow (int argc, char *argv[], void *p);
static int doacctest (int argc, char *argv[], void *p);
static int doaccread (int argc, char *argv[], void *p);
#endif /* lansend_account_c */

/* commands.c */

#ifdef lansend_commands_c
static int dodate (int argc, char *argv[], void *p);
static int dotime (int argc, char *argv[], void *p);
static int docmdfile (int argc, char *argv[], void *p);
static int docreate (int argc, char *argv[], void *p);
static int doappend (int argc, char *argv[], void *p);
static int dofill (int argc, char *argv[], void *p);
static int dodir (int argc, char *argv[], void *p);
static int dodelete (int argc, char *argv[], void *p);
static int dorename (int argc, char *argv[], void *p);
static int doquit (int argc, char *argv[], void *p);
static int donull (int argc, char *argv[], void *p);
static int dohostname (int argc, char *argv[], void *p);
static int dohelp (int argc, char *argv[], void *p);
static int dorsthelp (int argc, char *argv[], void *p);
static int doevent (int argc, char *argv[], void *p);
static int doversion (int argc, char *argv[], void *p);
static int docsc (int argc, char *argv[], void *p);
static void csc_rx_proc (int argc, void *argv, void *p);
static int docscdial (int argc, char *argv[], void *p);
static int docscanswer (int argc, char *argv[], void *p);
static int docschangup (int argc, char *argv[], void *p);
#endif /* lansend_commands_c */

/* debug.c */

#ifdef lansend_debug_c
static void display_debug_out_masks(void);
static int debug_out_process_mask (char *cp, uint16 *np);
#endif /* lansend_debug_c */

/* view.c */

#ifdef lansend_view_c
static sint31 lineseek (FILE *fp, sint31 start, int nlines, int width);
static int ctlproc (int c);
#endif /* lansend_view_c */

/*- MKHEADER End -*/


/* ************************************************************************* */

#endif /* _LANSEND_LOCAL_H */
