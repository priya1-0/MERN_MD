
/* ************************************************************************* */
/*
 *	wan.h
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
 *	Module:		WAN
 *
 *	This file contains the functions.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 20:56:09  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _WAN_WAN_H
#define _WAN_WAN_H

#include "wan/ppp.h"
#include "wan/pppchap.h"
#include "wan/pppfsm.h"
#include "wan/pppipcp.h"
#include "wan/ppplcp.h"
#include "wan/ppppap.h"

#include "wan/slhc.h"

/* ************************************************************************* */

/*- MKHEADER Begin -*/

/* Global Routines: */

/* ppp.c */
int ppp_send (struct iface *ifp, struct mbuf *bp, void *unused);
void ppp_out (int dev, void *p1, void *p2);
void ppp_asy_in (int dev, void *p1, void *p2);
void ppp_proc (struct iface *ifp, struct mbuf *bp);
void ppp_packet_proc (struct iface *ifp, struct mbuf *bp, uint16 size, uint16 protocol);
void ppp_iostatus (struct iface *ifp, int command, sint31 value);
int ppp_discard (struct iface *ifp, struct mbuf *bp);
int ppp_echo (struct iface *ifp, struct mbuf *bp);
void ppp_attach (struct iface *ifp);
void ppp_detach (struct iface *ifp);
void ppp_timeout (struct iface *ifp);
int ppp_start (struct iface *ifp);
void ppp_suspend (struct iface *ifp);

/* pppchap.c */
int doppp_chap(int argc, char *argv[], void *p);
int dochap_host (int argc, char *argv[], void *p);
int dochap_message (int argc, char *argv[], void *p);
int dochap_user (int argc, char *argv[], void *p);
void chap_proc (struct fsm_s *fsm_p, struct mbuf *bp);
void chap_down (struct fsm_s *fsm_p);
void chap_attach (struct ppp_s *ppp_p);
void chap_init (struct ppp_s *ppp_p);
int chap_local (struct ppp_s *ppp_p);
int chap_remote (struct ppp_s *ppp_p);

/* pppcmd.c */
int doppp_commands (int argc, char *argv[], void *p);
int doppp_close (int argc, char *argv[], void *p);
int doppp_open (int argc, char *argv[], void *p);
int doppp_quick (int argc, char *argv[], void *p);
void ppp_show (struct iface *ifp);
void genstat (struct ppp_s *ppp_p);
int doppp_timeout (int argc, char *argv[], void *p);
int doppp_try (int argc, char *argv[], void *p);

/* pppfsm.c */
void pppfsm_init(void);
int ntohcnf (struct config_hdr *cnf, struct mbuf **bpp);
void htonopt_copy (struct mbuf **bpp, struct option_hdr *opt, struct mbuf **copy_bpp);
int ntohopt (struct option_hdr *opt, struct mbuf **bpp);
void fsm_log (struct fsm_s *fsm_p, char *comment);
void fsm_timer (struct fsm_s *fsm_p);
int fsm_send (struct fsm_s *fsm_p, uint8 code, uint8 identifier, struct mbuf *bp);
void fsm_proc (struct fsm_s *fsm_p, struct mbuf *bp);
void fsm_up (struct fsm_s *fsm_p);
void fsm_down (struct fsm_s *fsm_p);
void fsm_open (struct fsm_s *fsm_p);
void fsm_close (struct fsm_s *fsm_p);
void fsm_attach (struct fsm_s *fsm_p);
void fsm_init (struct fsm_s *fsm_p);
void fsm_free (struct fsm_s *fsm_p);

/* pppipcp.c */
void pppipcp_init(void);
int doppp_ipcp (int argc, char *argv[], void *p);
void ipcp_attach (struct ppp_s *ppp_p);
void ipcp_init (struct ppp_s *ppp_p);

/* ppplcp.c */
void ppplcp_init(void);
int doppp_lcp (int argc, char *argv[], void *p);
void ppp_ready (struct ppp_s *ppp_p);
void lcp_starting (struct fsm_s *fsm_p);
void lcp_attach (struct ppp_s *ppp_p);
void lcp_init (struct ppp_s *ppp_p);

/* ppppap.c */
int doppp_pap (int argc, char *argv[], void *p);
int dopap_message (int argc, char *argv[], void *p);
int dopap_user (int argc, char *argv[], void *p);
void pap_proc (struct fsm_s *fsm_p, struct mbuf *bp);
void pap_down (struct fsm_s *fsm_p);
void pap_attach (struct ppp_s *ppp_p);
void pap_init (struct ppp_s *ppp_p);
int pap_local (struct ppp_s *ppp_p);
int pap_remote (struct ppp_s *ppp_p);

/* slhc.c */
struct slcompress * slhc_init (int rslots, int tslots);
void slhc_free (struct slcompress *comp);
int slhc_compress (struct slcompress *comp, struct mbuf **bpp, int compress_cid);
int slhc_uncompress (struct slcompress *comp, struct mbuf **bpp);
int slhc_remember (struct slcompress *comp, struct mbuf **bpp);
int slhc_toss (struct slcompress *comp);
void slhc_i_status (struct slcompress *comp);
void slhc_o_status (struct slcompress *comp);

/* wan.c */
void wan_module_reset (void);
void wan_startup (void);

/*- MKHEADER End -*/


/* ************************************************************************* */

#endif /* _WAN_WAN_H */
