
/* ************************************************************************* */
/*
 *	ip.h
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
 *	This file contains the functions.
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

#ifndef _IP_IP_H
#define _IP_IP_H

#include "ip/ipd.h"

#include "ip/internet.h"

#include "ip/arp.h"
#include "ip/domain.h"
#include "ip/icmp.h"
#include "ip/iprip.h"
#include "ip/tcp.h"
#include "ip/udp.h"

/* ************************************************************************* */

#define IP_FLAG__MF		0x2000		/* More fragments */
#define IP_FLAG__DF		0x4000		/* Don't Fragment */
#define IP_FLAG__CE		0x8000		/* Congestion experienced */

/* Congestion control from RFC 3168 - ECN is found in TOS byte */
#define IP_ECN__NOT		0x0000		/* Not ECN-Capable Transport (ECT) */
#define IP_ECN__ECT1	0x0001		/* ECT codepoint 1 */
#define IP_ECN__ECT0	0x0002		/* ECT codepoint 0 */
#define IP_ECN__CE		0x0003		/* Congestion experienced */

/* ************************************************************************* */

#define TLB		30	/* Default reassembly timeout, sec */
#define	IPVERSION	4
#define IP_CS_OLD	1	/* use saved checksum */
#define IP_CS_NEW	0	/* calculate checksum */

/* SNMP MIB variables, used for statistics and control. See RFC 1066 */
extern struct mib_entry Ip_mib[];
#define	ipForwarding		Ip_mib[1].value.integer
#define	ipDefaultTTL		Ip_mib[2].value.integer
#define	ipInReceives		Ip_mib[3].value.integer
#define	ipInHdrErrors		Ip_mib[4].value.integer
#define	ipInAddrErrors		Ip_mib[5].value.integer
#define	ipForwDatagrams		Ip_mib[6].value.integer
#define	ipInUnknownProtos	Ip_mib[7].value.integer
#define	ipInDiscards		Ip_mib[8].value.integer
#define	ipInDelivers		Ip_mib[9].value.integer
#define	ipOutRequests		Ip_mib[10].value.integer
#define	ipOutDiscards		Ip_mib[11].value.integer
#define	ipOutNoRoutes		Ip_mib[12].value.integer
#define	ipReasmTimeout		Ip_mib[13].value.integer
#define	ipReasmReqds		Ip_mib[14].value.integer
#define	ipReasmOKs		Ip_mib[15].value.integer
#define	ipReasmFails		Ip_mib[16].value.integer
#define	ipFragOKs		Ip_mib[17].value.integer
#define	ipFragFails		Ip_mib[18].value.integer
#define	ipFragCreates		Ip_mib[19].value.integer
#define ipRoutingDiscards	Ip_mib[20].value.integer
#define	NUMIPMIB	20

/* IP header, INTERNAL representation */
#define IPHDRLEN	20	/* Length of standard IP header */
#define IP_MAXOPT	40	/* Largest option field, bytes */
struct ip {
	struct sockaddr source;	/* Source address */
	struct sockaddr dest;	/* Destination address */
	uint16 length;		/* Total length */
	uint16 id;		/* Identification */
	uint16 offset;		/* Fragment offset in bytes */
	uint16 checksum;	/* Header checksum */

	struct {
		uint8 congest;	/* Congestion experienced bit (exp) */
		uint8 df;	/* Don't fragment flag */
		uint8 mf;	/* More Fragments flag */
	} flags;

	uint8 version;		/* IP version number */
	uint8 tos;		/* Type of service */
	uint8 ttl;		/* Time to live */
	uint8 protocol;		/* Protocol */
	uint8 optlen;		/* Length of options field, bytes */
	uint8 options[IP_MAXOPT];/* Options field */
};
#define	NULLIP	(struct ip *)0

/* Fields in option type byte */
#define	OPT_COPIED	0x80	/* Copied-on-fragmentation flag */
#define	OPT_CLASS	0x60	/* Option class */
#define	OPT_NUMBER	0x1f	/* Option number */

/* IP option numbers */
#define	IP_EOL		0	/* End of options list */
#define	IP_NOOP		1	/* No Operation */
#define	IP_SECURITY	2	/* Security parameters */
#define	IP_LSROUTE	3	/* Loose Source Routing */
#define	IP_TIMESTAMP	4	/* Internet Timestamp */
#define	IP_RROUTE	7	/* Record Route */
#define	IP_STREAMID	8	/* Stream ID */
#define	IP_SSROUTE	9	/* Strict Source Routing */

/* Timestamp option flags */
#define	TS_ONLY		0	/* Time stamps only */
#define	TS_ADDRESS	1	/* Addresses + Time stamps */
#define	TS_PRESPEC	3	/* Prespecified addresses only */

/* Reassembly descriptor */
struct reasm {
	struct reasm *next;	/* Linked list pointer */
	struct timer timer;	/* Reassembly timeout timer */
	struct frag *fraglist;	/* Head of data fragment chain */
	uint16 length;		/* Entire datagram length, if known */
	struct sockaddr source;		/* src/dest/id/protocol uniquely describe a datagram */
	struct sockaddr dest;
	uint16 id;
	uint8 protocol;
};
#define	NULLREASM	(struct reasm *)0

/* Fragment descriptor in a reassembly list */
struct frag {
	struct frag *prev;	/* Previous fragment on list */
	struct frag *next;	/* Next fragment */
	struct mbuf *buf;	/* Actual fragment data */
	uint16 offset;		/* Starting offset of fragment */
	uint16 last;		/* Ending offset of fragment */
};
#define	NULLFRAG	(struct frag *)0

extern struct reasm *Reasmq;	/* The list of reassembly descriptors */

/* Pseudo-header for TCP and UDP checksumming */
struct pseudo_header {
	sint31 source;		/* IP source */
	sint31 dest;		/* IP destination */
	char protocol;		/* Protocol */
	uint16 length;		/* Data field length */
};
#define	NULLHEADER	(struct pseudo_header *)0

/* Structure for handling raw IP user sockets */
struct raw_ip {
	struct raw_ip *next;	/* Linked list pointer */

	struct mbuf *rcvq;	/* receive queue */
	void (*r_upcall) (struct raw_ip *);
	int protocol;		/* Protocol */
	int user;		/* User linkage */
};
#define	NULLRIP	((struct raw_ip *)0)
extern struct raw_ip *Raw_ip;

/* Transport protocol link table */
struct iplink {
	char proto;
	void (*funct) (struct iface *, struct ip *, struct mbuf *, int);
};
extern const struct iplink Iplink[];

/* List of TCP port numbers to be given priority queuing */
extern const int Tcp_interact[];

/* Local IP wildcard address */
#define	IPADDR_ANY			0x0L
#define	IPADDR_LOOPBACK		0x7f000001L

/* In ipcmd.c: */
extern int Ip_secure;
extern uint32 Ip_pool_min;
extern uint32 Ip_pool_max;

/* ************************************************************************* */

/*- MKHEADER Begin -*/

/* Global Routines: */

/* domain.c */
void domain_init (void);
int dodomain (int argc, char *argv[], void *p);
int add_nameserver (sint31 address);
int drop_nameserver (sint31 address);
sint31 get_nameserver (int entry);
void free_rr (register struct rr *rrlp);
struct rr * inverse_a (sint31 ip_address);
struct rr * resolve_rr (char *dname, uint16 dtype);
char * resolve_a (sint31 ip_address, int shorten);
sint31 resolve (char *name);
sint31 resolve_mx (char *name);
struct rr * resolve_mailb (char *name);

/* domhdr.c */
int ntohdomain (register struct dhdr *dhdr, struct mbuf **bpp);

/* icmp.c */
void icmp_init (void);
void icmp_input (struct iface *iface, struct ip *ip, struct mbuf *bp, int rxbroadcast);
int icmp_output (struct ip *ip, struct mbuf *data, char type, char code, union icmp_args *args);

/* icmpcmd.c */
void icmpcmd_init (void);
int doicmp (int argc, char *argv[], void *p);

/* icmphdr.c */
struct mbuf * htonicmp (struct icmp *icmp, struct mbuf *bp);
int ntohicmp (struct icmp *icmp, struct mbuf **bpp);

/* ip.c */
void ip_init (void);
void ip_module_reset (void);
void ip_startup (void);
int ip_send (struct sockaddr *source, struct sockaddr *dest, char protocol, char tos, char ttl, struct mbuf *bp, uint16 length, uint16 id, uint16 df);
void ip_recv (struct iface *iface, struct ip *ip, struct mbuf *bp, int rxbroadcast);
struct raw_ip * raw_ip (int protocol, void (*r_upcall) (void));
void del_ip (struct raw_ip *rpp);
void ip_garbage (int red);

/* ipcmd.c */
void ipcmd_init (void);
uint32 ip_pool (struct iface *ifp);
int doip (int argc, char *argv[], void *p);

/* iphdr.c */
struct mbuf * htonip (register struct ip *ip, struct mbuf *bp, int cflag);
int ntohip (register struct ip *ip, struct mbuf **bpp);
uint16 eac (register sint31 sum);
uint16 cksum (struct pseudo_header *ph, struct mbuf *m, uint16 len);

/* iproute.c */
int ip_route (struct iface *i_iface, struct mbuf *bp, int rxbroadcast);

/* ipsock.c */
int so_ip_sock (struct usock *up, int protocol);
int so_ip_conn (struct usock *up);
int so_ip_recv (struct usock *up, struct mbuf **bpp, int len, char *from, int *fromlen);
int so_ip_send (struct usock *up, struct mbuf *bp, char *to);
int so_ip_qlen (struct usock *up, int rtx);
int so_ip_close (struct usock *up);
int checkipaddr (char *name, int namelen);

/* tcpcmd.c */
void tcb_detail (struct tcb *tcb);
int dotcp (int argc, char *argv[], void *p);

/* tcphdr.c */
struct mbuf * htontcp (register struct tcp *tcph, struct mbuf *bp, struct pseudo_header *ph);
int ntohtcp (register struct tcp *tcph, struct mbuf **bpp);

/* tcpin.c */
void tcp_input (struct iface *iface, struct ip *ip, struct mbuf *bp, int rxbroadcast);
void tcp_icmp (sint31 icsource, sint31 source, sint31 dest, char type, char code, struct mbuf **bpp);
void reset (struct ip *ip, register struct tcp *seg);
void send_syn (register struct tcb *tcb);

/* tcpout.c */
void tcp_output (register struct tcb *tcb);

/* tcpsock.c */
void tcpsock_init (void);
int so_tcp (struct usock *up, int protocol);
int so_tcp_listen (struct usock *up, int backlog);
int so_tcp_conn (struct usock *up);
int so_tcp_recv (struct usock *up, struct mbuf **bpp, int len, char *from, int *fromlen);
int so_tcp_send (struct usock *up, struct mbuf *bp, char *to);
int so_tcp_qlen (struct usock *up, int rtx);
int so_tcp_kick (struct usock *up);
int so_tcp_shut (struct usock *up, int how);
int so_tcp_close (struct usock *up);
char * tcpstate (struct usock *up);
int so_tcp_stat (struct usock *up);
uint16 tcp_get_next_port (void);
bool tcp_port_avail (uint16 port, bool local);

/* tcpsubr.c */
void tcpsubr_init (void);
struct tcb * lookup_tcb (register struct connection *conn);
struct tcb * create_tcb (struct connection *conn);
void close_self (register struct tcb *tcb, int reason);
int seq_within (sint31 x, sint31 low, sint31 high);
int seq_lt (sint31 x, sint31 y);
int seq_gt (sint31 x, sint31 y);
int seq_ge (sint31 x, sint31 y);
void tcp_setstate (register struct tcb *tcb, register int newstate);
void rtt_add (struct sockaddr *addr, sint31 rtt);
struct tcp_rtt * rtt_get (struct sockaddr *addr);
void tcp_garbage (int red);

/* tcptimer.c */
void tcp_timeout (void *p);
sint31 backoff (int n);

/* tcpuser.c */
void tcpuser_init (void);
struct tcb * open_tcp (struct sockaddr *local, struct sockaddr *remote, int mode, uint16 window, void (*r_upcall) (void), void (*t_upcall) (void), void (*s_upcall) (void), int tos, int user);
int send_tcp (register struct tcb *tcb, struct mbuf *bp);
int recv_tcp (register struct tcb *tcb, struct mbuf **bpp, uint16 cnt);
int close_tcp (register struct tcb *tcb);
int del_tcp (struct tcb *conn);
int tcbval (struct tcb *tcb);
int kick_tcp (register struct tcb *tcb);
int kick (sint31 addr);
void reset_tcp_all (void);
void reset_tcp (register struct tcb *tcb);

/* udp.c */
void udp_init (void);
void udp_icmp (sint31 icsource, sint31 source, sint31 dest, char type, char code, struct mbuf **bpp);
struct udp_cb * open_udp (struct sockaddr *lsocket, void (*r_upcall) (void));
int send_udp (struct sockaddr *lsocket, struct sockaddr *fsocket, char tos, char ttl, struct mbuf *bp, uint16 length, uint16 id, char df);
int recv_udp (register struct udp_cb *up, struct sockaddr *fsocket, struct mbuf **bp);
int del_udp (struct udp_cb *conn);
void udp_input (struct iface *iface, struct ip *ip, struct mbuf *bp, int rxbroadcast);
void udp_garbage (int red);

/* udpcmd.c */
int ucbval (struct udp_cb *ucb);
int ucb_detail (struct udp_cb *ucb);
int doudp (int argc, char *argv[], void *p);

/* udphdr.c */
struct mbuf * htonudp (struct udp *udp, struct mbuf *bp, struct pseudo_header *ph);
int ntohudp (struct udp *udp, struct mbuf **bpp);
uint16 udpcksum (struct mbuf *bp);

/* udpsock.c */
int so_udp (struct usock *up, int protocol);
int so_udp_bind (struct usock *up);
int so_udp_conn (struct usock *up);
int so_udp_recv (struct usock *up, struct mbuf **bpp, int len, char *from, int *fromlen);
int so_udp_send (struct usock *up, struct mbuf *bp, char *to);
int so_udp_qlen (struct usock *up, int rtx);
int so_udp_close (struct usock *up);
int so_udp_shut (struct usock *up, int how);
int so_udp_stat (struct usock *up);
void udpsock_init (void);
uint16 udp_get_next_port (void);
bool udp_port_avail (uint16 port, bool local);

/*- MKHEADER End -*/


/* ************************************************************************* */

#endif /* _IP_IP_H */
