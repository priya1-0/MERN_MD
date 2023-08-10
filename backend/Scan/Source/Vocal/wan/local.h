
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

#ifndef _WAN_LOCAL_H
#define _WAN_LOCAL_H

#include "wan/locald.h"
#include "wan/wan.h"

/* ************************************************************************* */

#define PPP_LOG(x, y) ppp_log (x, y)
#define PPP_ERROR(x, y, z) ppp_error (x, y, z)
#define PPP_SKIPPED(x, y, z) ppp_skipped (x, y, z)

/* ************************************************************************* */

/*- MKHEADER Begin -*/

/* Module Routines: */

/* ppp.c */
void ppp_log (struct ppp_s *ppp_p, char *comment);
void ppp_error (struct ppp_s *ppp_p, struct mbuf *bp, char *comment);
void ppp_skipped (struct ppp_s *ppp_p, struct mbuf *bp, char *comment);

/* Local Routines: */

/* pppchap.c */

#ifdef wan_pppchap_c
static int chap_lookup (char *username, char **result);
static int chap_verify (struct chap_s *chap_p, struct config_hdr *hdr, struct mbuf **bpp, char **username);
static struct mbuf * chap_makeresponse (struct fsm_s *fsm_p);
static int chap_sendresponse (struct fsm_s *fsm_p);
static void chap_shutdown (struct fsm_s *fsm_p);
static void chap_opening (struct fsm_s *fsm_p, int flag);
static int chap_response (struct fsm_s *fsm_p, struct config_hdr *hdr, struct mbuf *bp);
static int chap_check (struct fsm_s *fsm_p, struct config_hdr *hdr, struct mbuf *bp);
static void chap_challenger (int unused, void *v1, void *v2);
static void chap_free (struct fsm_s *fsm_p);
#endif /* wan_pppchap_c */

/* pppcmd.c */

#ifdef wan_pppcmd_c
static int doppp_show (int argc, char *argv[], void *p);
static int spot (struct fsm_side_s *side_p, negotiate_t mask);
static void lcpstat (struct fsm_s *fsm_p);
static void papstat (struct fsm_s *fsm_p);
static void chapstat (struct fsm_s *fsm_p);
static void ipcpstat (struct fsm_s *fsm_p);
static int dotry_nak (int argc, char *argv[], void *p);
static int dotry_req (int argc, char *argv[], void *p);
static int dotry_terminate (int argc, char *argv[], void *p);
#endif /* wan_pppcmd_c */

/* pppfsm.c */

#ifdef wan_pppfsm_c
static struct mbuf * htoncnf (struct config_hdr *cnf, struct mbuf *bp);
static void fsm_makeoptions(struct fsm_s *fsm_p, void *vp, struct mbuf **bpp, negotiate_t negotiating);
static struct mbuf * fsm_makereq (struct fsm_s *fsm_p);
static int fsm_configreq (struct fsm_s *fsm_p);
static int fsm_termreq (struct fsm_s *fsm_p);
static int fsm_termack (struct fsm_s *fsm_p, uint8 identifier);
static void fsm_irc (struct fsm_s *fsm_p);
static void fsm_zrc (struct fsm_s *fsm_p);
static void fsm_opening (struct fsm_s *fsm_p);
static int fsm_request (struct fsm_s *fsm_p, struct config_hdr *config, struct mbuf *bp);
static int fsm_ack (struct fsm_s *fsm_p, struct config_hdr *config, struct mbuf *bp);
static int fsm_nak (struct fsm_s *fsm_p, struct config_hdr *config, struct mbuf *bp);
static int fsm_reject (struct fsm_s *fsm_p, struct config_hdr *config, struct mbuf *bp);
static void fsm_timeout (void *vp);
#endif /* wan_pppfsm_c */

/* pppipcp.c */

#ifdef wan_pppipcp_c
static int doipcp_local (int argc, char *argv[], void *p);
static int doipcp_remote (int argc, char *argv[], void *p);
static int doipcp_address (int argc, char *argv[], void *p);
static int l_ipcp_compress (int argc, char *argv[], void *p);
static int doipcp_compress (int argc, char *argv[], void *p);
static int dodns_address (int argc, char *argv[], void *p);
static int doipcp_default (int argc, char *argv[], void *p);
static void ipcp_option(struct fsm_s *fsm_p, void *vp, struct mbuf **bpp, uint8 o_type);
static int ipcp_check (struct fsm_s *fsm_p, struct option_hdr *ohp, struct mbuf **bpp, int request);
static int ipcp_reject (struct fsm_s *fsm_p, struct option_hdr *ohp);
static uint32 ipcp_lookuppeer (char *peerid);
static void ipcp_starting (struct fsm_s *fsm_p);
static void ipcp_opening (struct fsm_s *fsm_p);
static void ipcp_closing (struct fsm_s *fsm_p);
static void ipcp_stopping (struct fsm_s *fsm_p);
static void ipcp_free (struct fsm_s *fsm_p);
#endif /* wan_pppipcp_c */

/* ppplcp.c */

#ifdef wan_ppplcp_c
static int dolcp_local (int argc, char *argv[], void *p);
static int dolcp_remote (int argc, char *argv[], void *p);
static int dolcp_accm (int argc, char *argv[], void *p);
static int dolcp_acfc (int argc, char *argv[], void *p);
static int l_lcp_auth (int argc, char *argv[], void *p);
static int dolcp_auth (int argc, char *argv[], void *p);
static int dolcp_magic (int argc, char *argv[], void *p);
static int l_lcp_mru (int argc, char *argv[], void *p);
static int dolcp_mru (int argc, char *argv[], void *p);
static int dolcp_pfc (int argc, char *argv[], void *p);
static int dolcp_default (int argc, char *argv[], void *p);
static void lcp_option (struct fsm_s *fsm_p, void *vp, struct mbuf **bpp, uint8 o_type);
static int lcp_check (struct fsm_s *fsm_p, struct option_hdr *ohp, struct mbuf **bpp, int request);
static int lcp_reject (struct fsm_s *fsm_p, struct option_hdr *ohp);
static void lcp_opening (struct fsm_s *fsm_p);
static void lcp_closing (struct fsm_s *fsm_p);
static void lcp_stopping (struct fsm_s *fsm_p);
static void lcp_free (struct fsm_s *fsm_p);
#endif /* wan_ppplcp_c */

/* ppppap.c */

#ifdef wan_ppppap_c
static void pap_pwdlookup (struct pap_s *pap_p);
static int pap_verify (char *username, char *password);
static struct mbuf * pap_makerequest (struct fsm_s *fsm_p);
static int pap_sendrequest (struct fsm_s *fsm_p);
static void pap_shutdown (struct fsm_s *fsm_p);
static void pap_opening (struct fsm_s *fsm_p, int flag);
static int pap_request (struct fsm_s *fsm_p, struct config_hdr *hdr, struct mbuf *data);
static int pap_check (struct fsm_s *fsm_p, struct config_hdr *hdr, struct mbuf *data);
static void pap_timeout (void *vp);
static void pap_free (struct fsm_s *fsm_p);
#endif /* wan_ppppap_c */

/* slhc.c */

#ifdef wan_slhc_c
static char * encode (char *cp, uint16 n);
static sint31 decode (struct mbuf **bpp);
#endif /* wan_slhc_c */

/*- MKHEADER End -*/


/* ************************************************************************* */

#endif /* _WAN_LOCAL_H */
