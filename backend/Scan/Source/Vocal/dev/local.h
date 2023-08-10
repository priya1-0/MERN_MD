
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
 *	Module:		DEV
 *
 *	This file contains the functions.
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

#ifndef _DEV_LOCAL_H
#define _DEV_LOCAL_H

#include "dev/locald.h"
#include "dev/dev.h"

/* ************************************************************************* */

/*- MKHEADER Begin -*/

/* Local Routines: */

/* devcmd.c */

#ifdef dev_devcmd_c
static int do_if_ipaddr (int argc, char *argv[], void *p);
static int do_if_ippeer (int argc, char *argv[], void *p);
static int do_if_ipbroad (int argc, char *argv[], void *p);
static int do_if_ipnetmsk (int argc, char *argv[], void *p);
static char * type_ip (int ip_type);
static int do_if_iptype (int argc, char *argv[], void *p);
static int do_if_ip (int argc, char *argv[], void *p);
static int do_if_detach (int argc, char *argv[], void *p);
static int do_if_encap (int argc, char *argv[], void *p);
static int do_if_mtu (int argc, char *argv[], void *p);
static int do_if_mib (int argc, char *argv[], void *p);
static void piface (struct iface *ifp, int mode);
static int do_if_show (int argc, char *argv[], void *p);
static int do_if_start (int argc, char *argv[], void *p);
static int do_if_stop (int argc, char *argv[], void *p);
static int do_dev_attach (int argc, char *argv[], void *p);
static int do_dev_inbuf (int argc, char *argv[], void *p);
static int do_dev_outbuf (int argc, char *argv[], void *p);
static int do_dev_linkadr (int argc, char *argv[], void *p);
static int do_ioctl (int argc, char *argv[], void *p);
#endif /* dev_devcmd_c */

/* devmdm.c */

#ifdef dev_devmdm_c
static sint31 mdm_ioctl (struct iface *ifp, int cmd, int set, sint31 val);
static void mdm_msint (struct mdm *mdmp);
static int mdm_send (struct iface *ifp, struct mbuf *bp);
static int get_mdm (struct iface *ifp);
static int unget_mdm (struct iface *ifp, uint8 c);
static int mdm_waitrlsd (struct iface *ifp, int want);
static void mdm_monitor (int dev, void *p1, void *p2);
static void mdm_timeout (void *p);
static int mdm_stop (struct iface *ifp);
#endif /* dev_devmdm_c */

/* mdmcmd.c */

#ifdef dev_mdmcmd_c
static void pmdm (struct mdm *mdmp);
static int do_show (int argc, char *argv[], void *p);
static int do_idle (int argc, char *argv[], void *p);
static int do_ioctl (int argc, char *argv[], void *p);
static int do_hangup (int argc, char *argv[], void *p);
#endif /* dev_mdmcmd_c */

/*- MKHEADER End -*/


/* ************************************************************************* */

#endif /* _DEV_LOCAL_H */
