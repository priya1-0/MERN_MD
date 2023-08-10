
/* ************************************************************************* */
/*
 *	socket.h
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

#ifndef	_NET_SOCKET_H
#define	_NET_SOCKET_H

/* This file is to be included automatically by a protocol specific
 * file such as ip.h or ipx.h, or it may be referenced manually if the
 * protocol specific control blocks do not need to be accessed.
 */

#define	SOCK_STREAM	0
#define	SOCK_DGRAM	1
#define	SOCK_RAW	2
#define SOCK_SEQPACKET	3

#define	EWOULDBLOCK	36
#define	ENOTCONN	37
#define	ESOCKTNOSUPPORT	38
#define	EAFNOSUPPORT	39
#define	EISCONN		40
#define	EOPNOTSUPP	41
#define	EALARM		42
#define	EABORT		43
#undef	EINTR
#define	EINTR		44
#define	ECONNREFUSED	45

#define EMSGSIZE	46
#define	EADDRINUSE	47
#define	EMAX		47
#define	ETIMEOUT	12345

extern const char *Sock_errlist[];

#define	SOCKBASE	128	/* Start of socket indexes */

union cb {

	struct tcb *tcb;		/* TCP socket */

	struct udp_cb *udp;		/* UDP socket */

	struct raw_ip *rip;		/* Raw IP socket */

	struct loc *local;		/* Local sockets */

	char *p;				/* General pointer when no specific type defined */
};

/* User sockets */
struct usock {
	unsigned index;
	struct proc *owner;
	int refcnt;
	char noblock;
	char type;
#define	TYPE_NOTUSED		0
#define	TYPE_TCP		1
#define	TYPE_UDP		2
#define	TYPE_AX25I		3
#define	TYPE_AX25UI		4
#define TYPE_RAW		5
#define TYPE_NETROML3		6
#define TYPE_NETROML4		7
#define	TYPE_LOCAL_STREAM	8
#define	TYPE_LOCAL_DGRAM	9
#define TYPE_SPX		10		/* Novell Services */
#define TYPE_PEP		11		/* Novell Services */
	struct socklink *sp;
	int rdysock;
	union cb cb;
	char *name;
	int namelen;
	char *peername;
	int peernamelen;
	char errcodes[4];	/* Protocol-specific error codes */
	char tos;		/* Internet type-of-service */
	int flag;		/* Mode flags, defined in socket.h */
};
#define	NULLUSOCK	((struct usock *)0)

struct socklink {
	int type;		/* Socket type */
	int (*socket) (struct usock *, int);
	int (*bind) (struct usock *);
	int (*listen) (struct usock *, int);
	int (*connect) (struct usock *);
	int accept;
	int (*recv) (struct usock *, struct mbuf **, int len, char *, int *);
	int (*send) (struct usock *, struct mbuf *, char *to);
	int (*qlen) (struct usock *, int);
	int (*kick) (struct usock *);
	int (*shut) (struct usock *, int);
	int (*close) (struct usock *);
	int (*check) (char *, int);
	char **error;
	char *(*state) (struct usock *);
	int (*status) (struct usock *);
	char *eol;
};

extern const struct socklink Socklink[];

extern const char Badsocket[];
extern const char *Socktypes[];
extern struct usock **Usock;
extern uint16 Lport;

#endif /* _NET_SOCKET_H */
