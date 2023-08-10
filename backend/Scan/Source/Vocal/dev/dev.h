
/* ************************************************************************* */
/*
 *	dev.h
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
 *	Module:		DEV
 *
 *	This file contains the include list.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 19:38:37  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _DEV_DEV_H
#define _DEV_DEV_H

#include "dev/devd.h"

#include "dev/iface.h"

#include "dev/devparam.h"

/* ************************************************************************* */

/*- MKHEADER Begin -*/

/* Global Routines: */

/* dev.c */
void dev_module_reset (void);
void dev_startup (void);
sint31 pkt_ioctl (struct iface *ifp, int cmd, int set, sint31 val);
uint32 buff_to_dword_le (char *buffer);

/* devcmd.c */
int do_device (int argc, char *argv[], void *p);

/* devmdm.c */
void mdm_init (void);
uint16 cnt_mdm (struct iface *ifp);
int mdm_attach (int argc, char *argv[], void *name);

/* devparam.c */
int devparam (char *s);
char * parmname (int n);

/* mdmcmd.c */
int do_mdm (int argc, char *argv[], void *p);

/*- MKHEADER End -*/


/* ************************************************************************* */

#endif /* _DEV_DEV_H */
