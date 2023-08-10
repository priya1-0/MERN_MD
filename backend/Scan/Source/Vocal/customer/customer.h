
/* ************************************************************************* */
/*
 *  customer.h
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
 *  This file contains the public declarations for the CUSTOMER module.
 *
 *  Revision Number:    $Revision$
 *  Revision Status:    $State$
 *  Last Modified:      $Date$
 *  Identification:     $Id$
 *
 *  Revision History:   $Log$
 *  Revision History:   Revision 1.1.24.1  2009/04/28 19:09:22  zhangn1
 *  Revision History:   SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *  Revision History:
 *
 */
/* ************************************************************************* */

#ifndef _CUSTOMER_CUSTOMER_H
#define _CUSTOMER_CUSTOMER_H

/* ************************************************************************* */

/* ************************************************************************* */

/*- MKHEADER Begin -*/

/* Global Routines: */

/* cx077a.c */
int mdm_Send_Control_String (char* command, char* respbuf, int buflen);
int mdm_Init (void);
void mdm_Shut_Off (void);
void mdm_Purge_Input_Buffer (void);
int mdm_Send_String (int length, char* buffer);
int network_Send_Cmd (char * cmdstr);
void network_init_proc (int do_auth, void * username, void * password);
int network_Init (int do_auth, char* username, char* password);
void http_process (int iarg, void * p1, void * p2);
void speaker_monitor_on (void);
void speaker_monitor_off (void);
void mdm_Store_Data (void);
void set_num_fg_states (int desired);
int read_num_fg_states (void);
void mdm_setModemDTMFStrength (void);
void mdm_setModemCadenceDialDetect (void);
void mdm_setNetworkDebugEnable (int mode);

/* netdump.c */
void ip_dump (struct iface *ifp, FILE *fp, struct mbuf **bpp, int check);
void icmp_dump (struct iface *ifp, FILE *fp, struct mbuf **bpp, sint31 source, sint31 dest, int check);
void tcp_dump (FILE *fp, struct mbuf **bpp, sint31 source, sint31 dest, int check);
void udp_dump (FILE *fp, struct mbuf **bpp, sint31 source, sint31 dest, int check);
void ppp_fsm_dump (FILE *fp, struct mbuf **bpp, int unused);
void ppp_dump (struct iface *ifp, FILE *fp, struct mbuf **bpp, int unused);
void vjcomp_dump (FILE *fp, struct mbuf **bpp, int unused);
void sl_dump (struct iface *ifp, FILE *fp, struct mbuf **bpp, int unused);
void dump (struct iface *ifp, int direction, struct mbuf *bp);
void raw_dump (struct iface *ifp, int direction, struct mbuf *bp);
int dotrace (int argc, char *argv[], void *p);
void shuttrace (void);
void trace_log (struct iface *ifp, char *fmt, ...);
int tprintf (struct iface *ifp, char *fmt, ...);

/*- MKHEADER End -*/


/* ************************************************************************* */

#endif /* _CUSTOMER_CUSTOMER_H */
