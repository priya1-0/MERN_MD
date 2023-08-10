
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
 *	Module:		IP
 *
 *	This file contains the private declarations for the IP module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 19:52:55  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _IP_LOCAL_H
#define _IP_LOCAL_H

#include "ip/locald.h"
#include "ip/ip.h"

/* ************************************************************************* */

/*- MKHEADER Begin -*/

/* Local Routines: */

/* domain.c */

#ifdef ip_domain_c
static int docache (int argc, char *argv[], void *p);
static int dosuffix (int argc, char *argv[], void *p);
static int docacheclean (int argc, char *argv[], void *p);
static int docachelist (int argc, char *argv[], void *p);
static int docachesize (int argc, char *argv[], void *p);
static int docachewait (int argc, char *argv[], void *p);
static void dlist_add (register struct dserver *dp);
static void dlist_drop (register struct dserver *dp);
static int dodnsadd (int argc, char *argv[], void *p);
static int dodnsdrop (int argc, char *argv[], void *p);
static int dodnslist (int argc, char *argv[], void *p);
static int dodnsquery (int argc, char *argv[], void *p);
static int dodnsretry (int argc, char *argv[], void *p);
static int dodnstrace (int argc, char *argv[], void *p);
static char * dtype (int value);
static int check_ttl (register struct rr *rrlp);
static int compare_rr (register struct rr *search_rrp, register struct rr *target_rrp);
static int compare_rr_list (register struct rr *rrlp, register struct rr *target_rrp);
static struct rr * copy_rr (register struct rr *rrp);
static struct rr * copy_rr_list (register struct rr *rrlp);
static struct rr * make_rr (int source, char *dname, uint16 dclass, uint16 dtype, sint31 ttl, uint16 rdl, void *data);
static void dcache_add (register struct rr *rrlp);
static void dcache_drop (register struct rr *rrp);
static struct rr * dcache_search (struct rr *rrlp);
static void dcache_update (register struct rr *rrlp);
static struct rr * get_rr (FILE *fp, struct rr *lastrrp);
static void put_rr (FILE *fp, struct rr *rrp);
static struct rr * dfile_search (struct rr *rrlp);
static void dfile_update (int s, void *unused, void *p);
static void dumpdomain (struct dhdr *dhp, sint31 rtt);
static int dns_makequery (uint16 op, struct rr *srrp, char *buffer, uint16 buflen);
static void dns_query (struct rr *rrlp);
static int isaddr (register char *s);
static char * checksuffix (char *dname);
static struct rr * resolver (register struct rr *rrlp);
#endif /* ip_domain_c */

/* domhdr.c */

#ifdef ip_domhdr_c
static char * getq (struct rr **rrpp, char *msg, char *cp);
static char * ntohrr (struct rr **rrpp, char *msg, char *cp);
static int dn_expand (char *msg, char *eom, char *compressed, char *full, int fullen);
#endif /* ip_domhdr_c */

/* icmpcmd.c */

#ifdef ip_icmpcmd_c
static int doicmpmib (int argc, char *argv[], void *p);
static int doicmptrace (int argc, char *argv[], void *p);
static int doicmpecho (int argc, char *argv[], void *p);
#endif /* ip_icmpcmd_c */

/* ip.c */

#ifdef ip_ip_c
static struct mbuf * fraghandle (struct ip *ip, struct mbuf *bp);
static struct reasm * lookup_reasm (struct ip *ip);
static struct reasm * creat_reasm (register struct ip *ip);
static void free_reasm (struct reasm *r);
static void ip_timeout (void *arg);
static struct frag * newfrag (uint16 offset, uint16 last, struct mbuf *bp);
static void freefrag (struct frag *fp);
static void rdrop (struct iface *ifp);
#endif /* ip_ip_c */

/* ipcmd.c */

#ifdef ip_ipcmd_c
static int doipaddr (int argc, char *argv[], void *p);
static int doipfilter (int argc, char *argv[], void *p);
static int doippool (int argc, char *argv[], void *p);
static int doipmib (int argc, char *argv[], void *p);
static int doipshow (int argc, char *argv[], void *p);
static int doiprtimer (int argc, char *argv[], void *p);
static int doipttl (int argc, char *argv[], void *p);
static int doipoptions (int argc, char *argv[], void *p);
static void iproute_detail (register struct route *rp);
static int doiprouteshow (int argc, char *argv[], void *p);
static int doipadd (int argc, char *argv[], void *p);
static int doipdrop (int argc, char *argv[], void *p);
static int doipflush (int argc, char *argv[], void *p);
static int doiplook (int argc, char *argv[], void *p);
static int doiproute (int argc, char *argv[], void *p);
#endif /* ip_ipcmd_c */

/* iproute.c */

#ifdef ip_iproute_c
static int q_pkt (struct iface *iface, struct sockaddr *gateway, struct ip *ip, struct mbuf *bp, int ckgood);
#endif /* ip_iproute_c */

/* ipsock.c */

#ifdef ip_ipsock_c
static void rip_recv (struct raw_ip *rp);
static void autobind (struct usock *up);
#endif /* ip_ipsock_c */

/* tcpcmd.c */

#ifdef ip_tcpcmd_c
static int atotcb_err (char *cp, struct tcb **tcbpp);
static int dotcptrace (int argc, char *argv[], void *p);
static int dotcpreset (int argc, char *argv[], void *p);
static int dotcpirtt (int argc, char *argv[], void *p);
static int dorcprtt (int argc, char *argv[], void *p);
static int dotcpkick (int argc, char *argv[], void *p);
static int dotcpmss (int argc, char *argv[], void *p);
static int dotcpwind (int argc, char *argv[], void *p);
static int dotcpsyndata (int argc, char *argv[], void *p);
static int dotcpmib (int argc, char *argv[], void *p);
static int tcb_summary (void);
#endif /* ip_tcpcmd_c */

/* tcpin.c */

#ifdef ip_tcpin_c
static void update (register struct tcb *tcb, register struct tcp *seg, uint16 length);
static int in_window (struct tcb *tcb, sint31 seq);
static void proc_syn (register struct tcb *tcb, char tos, struct tcp *seg);
static void add_reseq (struct tcb *tcb, char tos, struct tcp *seg, struct mbuf *bp, uint16 length);
static void get_reseq (register struct tcb *tcb, char *tos, struct tcp *seg, struct mbuf **bp, uint16 *length);
static int trim (register struct tcb *tcb, register struct tcp *seg, struct mbuf **bpp, uint16 *length);
#endif /* ip_tcpin_c */

/* tcpsock.c */

#ifdef ip_tcpsock_c
static void s_trcall (struct tcb *tcb, int cnt);
static void s_ttcall (struct tcb *tcb, int cnt);
static void s_tscall (struct tcb *tcb, int old, int new_state);
static void trdiscard (struct tcb *tcb, int cnt);
static void autobind (struct usock *up);
#endif /* ip_tcpsock_c */

/* udp.c */

#ifdef ip_udp_c
static struct udp_cb * lookup_udp (struct sockaddr *socket);
#endif /* ip_udp_c */

/* udpcmd.c */

#ifdef ip_udpcmd_c
static int atoucb_err (char *cp, struct udp_cb **ucbpp);
static int doudpmib (int argc, char *argv[], void *p);
static int ucb_summary (void);
static int doudpshow (int argc, char *argv[], void *p);
#endif /* ip_udpcmd_c */

/* udpsock.c */

#ifdef ip_udpsock_c
static void s_urcall (struct iface *iface, struct udp_cb *udp, int cnt);
static void autobind (struct usock *up);
#endif /* ip_udpsock_c */

/*- MKHEADER End -*/


/* ************************************************************************* */
#endif /* _IP_LOCAL_H */
