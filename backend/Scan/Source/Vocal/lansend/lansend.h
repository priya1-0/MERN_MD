
/* ************************************************************************* */
/*
 *	lansend.h
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
 *	This file contains the global declarations for the LANSEND module.
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

#ifndef _LANSEND_LANSEND_H
#define _LANSEND_LANSEND_H

#include "lansend/lansendd.h"

#include "lansend/account.h"
#include "lansend/commands.h"
#include "lansend/daemon.h"
#include "lansend/main.h"
#include "lansend/view.h"

/* ************************************************************************* */

/*- MKHEADER Begin -*/

/* Global Routines: */

/* account.c */
void account_init (void);
struct account * account_find (char *name, char *password);
int doaccsave (int argc, char *argv[], void *p);
int doaccount (int argc, char *argv[], void *p);

/* commands.c */
int cmdfile (char *file);
int domore (int argc, char *argv[], void *p);
int dobytes (int argc, char *argv[], void *p);
int dowords (int argc, char *argv[], void *p);
int dohex (int argc, char *argv[], void *p);
int doperiodic (int argc, char *argv[], void *p);
int donoperiodic (int argc, char *argv[], void *p);
int doboot (int argc, char *argv[], void *p);
int donothing (int argc, char *argv[], void *p);
void lansend_return(void);

/* config.c */
void config_init (void);
void iprt_timeout (void *s);

/* debug.c */
int dodebugoutputall (int argc, char *argv[], void *p);
int dodebugoutputata (int argc, char *argv[], void *p);
int dodebugoutputsip (int argc, char *argv[], void *p);
int dodebugoutputmgcp (int argc, char *argv[], void *p);
int dodebugoutputnet (int argc, char *argv[], void *p);
int dodebugoutputomc (int argc, char *argv[], void *p);
int dodebugoutputpmp (int argc, char *argv[], void *p);
int dodebugoutput (int argc, char *argv[], void *p);
int dolevels (int argc, char *argv[], void *p);
int dodebug (int argc, char *argv[], void *p);

/* main.c */
void network_reset (void);
void network_kernel_install (void);
void lansend_startup (void);
void command_process (int i, void *p1, void *p2);
void net_bg (void);
int dolog (int argc, char *argv[], void *p);
void net_log (int s, char *fmt, ...);
int snmp_trap (sint31 trap_type, sint31 trap_specific);
void lansend_module_reset (void);
void network_cmd_line (int argc, char *argv[]);
void dspbios_network_task (void);
void dspbios_network_shutdown (void);
int dspbios_network_start (void);
int dspbios_network_start_process (int stksize, void (*pc) (int, void*, void*), int iarg, void *p1, void *p2, int freeargs);
int dspbios_network_kernel_running (void);

/* test.c */
int dotest (int argc, char *argv[], void *p);

/* view.c */
int doview (int argc, char *argv[], void *p);
void view (int s, void *p1, void *p2);

/*- MKHEADER End -*/


/* ************************************************************************* */

#endif /* _LANSEND_LANSEND_H */
