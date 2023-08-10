
/* ************************************************************************* */
/*
 *  local.h
 *
 *	(C) 1994 - 2006 VOCAL Technologies, Ltd.
 *
 *  ALL RIGHTS RESERVED.  PROPRIETARY AND CONFIDENTIAL.
 *
 *  VOCAL Technologies, Ltd.
 *  90A John Muir Drive.
 *  Buffalo, NY  14228
 *
 *  Product:    MODEM 101
 *
 *  Module:     CUSTOMER
 *
 *  This file contains the private declarations for the CUSTOMER module.
 *
 *  Revision Number:    $Revision$
 *  Revision Status:    $State$
 *  Last Modified:      $Date$
 *  Identification:     $Id$
 *
 *  Revision History:   $Log$
 *  Revision History:   Revision 1.2.6.2  2009/04/28 19:09:22  zhangn1
 *  Revision History:   SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *  Revision History:
 *
 */
/* ************************************************************************* */

#ifndef _CUSTOMER_LOCAL_H
#define _CUSTOMER_LOCAL_H

/* ************************************************************************* */

#include "customer/customer.h"

/* ************************************************************************* */
/* fully local symbols for only this directory */

#define HTTP_DATA_8BIT   (8)
#define HTTP_DATA_16BIT  (16)

#define NET_PPP_AUTH_NONE	0
#define NET_PPP_AUTH_PAP	1
#define NET_PPP_AUTH_CHAP	2

/* ************************************************************************* */

/*- MKHEADER Begin -*/

/* Module Routines: */

/* cx077a.c */
void network_send_cmd (int iarge, void * cmdstr, void * p2);
void network_send_cmd_proc (int iarge, void * cmdstr, void * p2);
int network_Get_PPP_Auth_Type (void);

/* Local Routines: */

/* netdump.c */

#ifdef customer_netdump_c
static void print_buffered_string (bool now, char *str);
static uint16 decodeint (struct mbuf **bpp);
static void ctohex (char *buf, uint16 c);
static void fmtline (FILE *fp, uint16 addr, char *buf, uint16 len);
static void hex_dump (FILE *fp, struct mbuf **bpp);
static void ascii_dump (FILE *fp, struct mbuf **bpp);
static void show_trace (struct iface *ifp);
#endif /* customer_netdump_c */

/*- MKHEADER End -*/


/* ************************************************************************* */

#endif /* _CUSTOMER_LOCAL_H */
