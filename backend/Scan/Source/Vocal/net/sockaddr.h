
/* ************************************************************************* */
/*
 *	sockaddr.h
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

#ifndef _NET_SOCKADDR_H
#define _NET_SOCKADDR_H

/* Address families in use */
#define	AF_INET		0		/* Internet */
#define AF_NOVELL	1		/* Novell Services */
#define	AF_LOCAL	2
#define AF_NONE		3		/* Not any family */
#define NAF			4		/* Next highest family number */
#define AF_IFCMAX	2		/* Interface multiprotocol address array length */

/* IANA Address families */
#define IANA_AF_RES		0	/* Reserved */
#define IANA_AF_IPV4	1	/* IP Version 4 */
#define IANA_AF_IPV6	2	/* IP Version 6 */
#define IANA_AF_IPX		11	/* Novell IPX */

/* ************************************************************************* */

/* Universal socket address structure */
struct in_addr {
	uint32 s_addr;
};

struct ns_addr {
	uint32 s_network;	/* Network and host must be in packet order */
	char s_host[6];
};

struct sockaddr {
	uint16 sa_family;
	union {
		/* Socket address, DARPA Internet style */
		struct {
			uint16 s_port;
			struct in_addr s_addr;
		} sin;
		/* Socket address, Novell Services style */
		struct {
			struct ns_addr s_addr;
			uint16 s_port;
			uint16 s_cid;
		} sns;
		char data[14];
	} sau;
};
#define NULLSA	((struct sockaddr *) 0)

/* ************************************************************************* */

#define sin_address sau.sin.s_addr.s_addr
#define sin_port sau.sin.s_port

#define sns_network sau.sns.s_addr.s_network
#define sns_host sau.sns.s_addr.s_host
#define sns_addr sau.sns.s_addr
#define sns_port sau.sns.s_port
#define sns_cid sau.sns.s_cid

#define	SOCKSIZE	(sizeof(struct sockaddr))

/* ************************************************************************* */

/* Connection structure (two sockets) */
struct connection {
	struct sockaddr local;
	struct sockaddr remote;
};

/* ************************************************************************* */

/* For compatibility with Berkeley */

#define sockaddr_in	sockaddr
#define sin_family	sa_family
#define sin_addr	sau.sin.s_addr

#define INADDR_ANY 0

#define inet_addr(a) resolve(a)

/* ************************************************************************* */

#endif /* _NET_SOCKADDR_H */
