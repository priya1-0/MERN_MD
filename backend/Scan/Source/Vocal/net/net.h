
/* ************************************************************************* */
/*
 *	net.h
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
 *	Module:		NET
 *
 *	This file contains the global declarations for the NET module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 20:31:57  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _NET_NET_H
#define _NET_NET_H

#include "system/system.h"

#include "net/netd.h"

#include "snmp/mib.h"

#include "net/af.h"
#include "net/locsock.h"
#include "net/sockaddr.h"
#include "net/route.h"
#include "net/netuser.h"
#include "net/socket.h"

/* ************************************************************************* */
/*
 *	Router/NAT/Firewall Operating Modes
 *
 */
#define LANSEND_SHARED_IP_SUPPORT	0

#define LANSEND_PASSTHROUGH_SUPPORT	0

#define LANSEND_ROUTER_SUPPORT	0

#define LANSEND_NAT_SUPPORT	0

#define LANSEND_NAT_FIREWALL_SUPPORT	0

#define NUM_ROUTER_MODES		(1 + LANSEND_SHARED_IP_SUPPORT + LANSEND_PASSTHROUGH_SUPPORT  + LANSEND_ROUTER_SUPPORT + LANSEND_NAT_SUPPORT + LANSEND_NAT_FIREWALL_SUPPORT)

#define ROUTER_MODE__OFF					0x0000
#define ROUTER_MODE__SHARED_IP				LANSEND_SHARED_IP_SUPPORT
#define ROUTER_MODE__PASSTHROUGH			LANSEND_SHARED_IP_SUPPORT + LANSEND_PASSTHROUGH_SUPPORT
#define ROUTER_MODE__ROUTER					LANSEND_SHARED_IP_SUPPORT + LANSEND_PASSTHROUGH_SUPPORT + LANSEND_ROUTER_SUPPORT
#define ROUTER_MODE__NAT					LANSEND_SHARED_IP_SUPPORT + LANSEND_PASSTHROUGH_SUPPORT + LANSEND_ROUTER_SUPPORT + LANSEND_NAT_SUPPORT
#define ROUTER_MODE__NAT_FIREWALL			LANSEND_SHARED_IP_SUPPORT + LANSEND_PASSTHROUGH_SUPPORT + LANSEND_ROUTER_SUPPORT + LANSEND_NAT_SUPPORT + LANSEND_NAT_FIREWALL_SUPPORT
/* ************************************************************************* */

/*- MKHEADER Begin -*/

/* Global Routines: */

/* af.c */
uint32 af_netmask (struct sockaddr *sa);
uint32 af_net (struct sockaddr *sa);
uint32 af_subnetmask (struct sockaddr *sa);
uint16 af_hash (struct sockaddr *sa);
int af_netmatch (struct sockaddr *sa1, struct sockaddr *sa2);
int af_netsame (struct sockaddr *sa1, struct sockaddr *sa2);
int af_hostmatch (struct sockaddr *sa1, struct sockaddr *sa2);
int af_hostsame (struct sockaddr *sa1, struct sockaddr *sa2);
int af_portmatch (struct sockaddr *sa1, struct sockaddr *sa2);
int af_portsame (struct sockaddr *sa1, struct sockaddr *sa2);
int af_connectionmatch (struct sockaddr *sa1, struct sockaddr *sa2);
int af_connectionsame (struct sockaddr *sa1, struct sockaddr *sa2);
int af_broadcast (struct sockaddr *sa, uint32 netmask);
void af_default (int family, struct sockaddr *sa);

/* locsock.c */
int so_los (struct usock *up, int protocol);
int so_lod (struct usock *up, int protocol);
int so_lo_recv (struct usock *up, struct mbuf **bpp, int len, char *from, int *fromlen);
int so_los_send (struct usock *up, struct mbuf *bp, char *to);
int so_lod_send (struct usock *up, struct mbuf *bp, char *to);
int so_lod_qlen (struct usock *up, int rtx);
int so_los_qlen (struct usock *up, int rtx);
int so_loc_shut (struct usock *up, int how);
int so_loc_close (struct usock *up);
int so_loc_stat (struct usock *up);

/* net.c */
void net_module_reset (void);
void net_startup (void);

/* netuser.c */
void netuser_init (void);
sint31 atonl (register char *s);
char * inet_ntoa (sint31 a);
char * ethertoa (char *addr);
char * sntoa (struct sockaddr *a);
char * snhtoa (struct sockaddr *a);
char * snhptoa (struct sockaddr *a);
char * snhpctoa (struct sockaddr *a);
int atos_err (char *cp, uint16 family, struct sockaddr *dest);
int atosr_err (char *cp, uint16 family, struct sockaddr *dest, struct route **rpp);
int atosb_err (char *cp, uint16 family, struct sockaddr *dest);
int atosbr_err (char *cp, uint16 family, struct sockaddr *dest, struct route **rpp);
int atom_err (char *cp, uint32 *netmask);
int atoether_err (char *cp, char address[]);
int atoiface_err (char *cp, struct iface **ifpp);
int atoi16s_err (char *cp, sint15 *np);
int atoi16u_err (char *cp, uint16 *np);
int atoi16uh_err (char *cp, uint16 *np);
int atoi32s_err (char *cp, sint31 *np);
int atoi32u_err (char *cp, uint32 *np);
int atoi32uh_err (char *cp, uint32 *np);
void print_mib (struct mib_entry mib[], int entries);

/* route.c */
void route_init (void);
struct route * rt_add (struct sockaddr *target, uint32 netmask, struct sockaddr *gateway, struct iface *ifp, uint16 hopcount, uint16 delay, sint15 tos, sint31 ttl, char private_add);
int rt_drop (struct sockaddr *target, uint32 netmask, struct iface *ifp);
uint16 rt_mtu (struct sockaddr *addr);
struct sockaddr * locaddr (struct sockaddr *addr);
void rt_update (void);
struct route * rt_lookup (struct sockaddr *target);
struct route * rt_assign (struct iface **ifpp, struct sockaddr *target);
struct route * rt_exact (struct sockaddr *target, uint32 netmask, struct iface *ifp);
void rt_merge (uint16 sa_family, int trace);
int rt_netmatch (struct sockaddr *sa1, struct sockaddr *sa2, uint32 netmask);
int rt_netsame (struct sockaddr *sa1, struct sockaddr *sa2, uint32 netmask);
uint16 rt_hash (struct sockaddr *sa);

/* sockcmd.c */
int dosock (int argc, char *argv[], void *p);

/* socket.c */
void socket_init (void);
void sockinit (void);
int socket (int af, int type, int protocol);
int bind (int s, char *name, int namelen);
int listen (int s, int backlog);
int connect (int s, char *peername, int peernamelen);
int accept (int s, char *peername, int *peernamelen);
int recv_mbuf (int s, struct mbuf **bpp, int len, int flags, char *from, int *fromlen);
int send_mbuf (int s, struct mbuf *bp, int flags, char *to, int tolen);
int getsockname (int s, char *name, int *namelen);
int getpeername (int s, char *peername, int *peernamelen);
int socklen (int s, int rtx);
int sockkick (int s);
struct proc * sockowner (int s, struct proc *newowner);
int shutdown (int s, int how);
int close_s (int s);
int usesock (int s);
void freesock (struct proc *pp);
int settos (int s, char tos);
int socketpair (int af, int type, int protocol, int sv[]);
char * eolseq (int s);

/* sockuser.c */
int recv (int s, char *buf, int len, int flags);
int recvfrom (int s, char *buf, int len, int flags, char *from, int *fromlen);
int send (int s, char *buf, int len, int flags);
int sendto (int s, char *buf, int len, int flags, char *to, int tolen);

/* sockutil.c */
char * sockerr (int s);
char * sockstate (int s);
struct usock * itop (register int s);
void st_garbage (int red);

/*- MKHEADER End -*/


/* ************************************************************************* */

#endif /* _NET_NET_H */
