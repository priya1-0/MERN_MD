
/* ************************************************************************* */
/*
 *	iprip.h
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

#ifndef _IP_IPRIP_H
#define _IP_IPRIP_H

/* Routing Information Protocol (RIP)
 *
 *	This code is derived from the 4.2 BSD version which was
 * used as a spec since no formal specification is known to exist.
 * See RFC 1009, Gateway Requirements, for more details. AGB 4 - 29 - 88
 *
 * The draft RIP RFC was used to develop most of this code. The above
 * referred to the basics of the rip_recv () function of RIP.C. The RIP
 * RFC has now been issued as RFC1058. AGB 7 - 23 - 88
 *
 * Substantially rewritten and integrated into NOS 9 / 1989 by KA9Q
 */
#define	IPRIP_INFINITY	16	/* Route unreachable. */
#define	IPRIP_TTL	240	/* Default time-to-live for an entry */
#define	IPRIP_VERSION	1	/* Current version of IP rip. */
#define	IPRIP_IPFAM	2	/* Family is IP */

/* RIP Packet Types */
#define IPRIPCMD_REQUEST	1	/* want info */
#define IPRIPCMD_RESPONSE	2	/* responding to request */
#define	IPRIPCMD_MAX		3

#define IPHOPCNT_INFINITY	16
#define MAXIPRIPROUTES		25	/* maximum # routes per RIP pkt */

/* This is a destination specific rip structure.  If one of these exist for
 * and address (DEST), then every cycle rip packets will be sent to that
 * address. */
struct iprip_list {
	struct iprip_list *prev;
	struct iprip_list *next;	/* doubly linked list */

	/* Address to scream at periodically:
	 * This address must have a direct network interface route and an
	 * ARP entry for the appropriate hardware broadcast address, if approp.
	 */
	struct sockaddr dest;

	/* Basic rate of RIP clocks on this net interface */
	sint31 interval;

	struct timer rip_time;	/* time to output next on this net. iface */

	/* The interface to transmit on and receive from */
	struct iface *iface;

	/* Described below with the mask defs */
	char	flags;
#define	IPRIP_SPLIT 0x1	/* Do split horizon processing */
#define	IPRIP_US	0x2	/* Include ourselves in the list */
};
#define	NULLIPRIPL (struct iprip_list *)0

/* Host format of a single entry in a IP RIP response packet */
struct iprip_route {
	uint16 addr_fam;
	uint32 target;
	sint31 hopcount;
};
#define	IPRIPROUTE	20	/* Size of each routing entry */
#define	IPRIPHEADER	4	/* Size of rip header before routes */
#define	MAXIPRIPPACKET	IPRIPHEADER + (MAXIPRIPROUTES*IPRIPROUTE)

/* RIP statistics counters */
struct iprip_stat {
	sint31 output;		/* Packets sent */
	sint31 rcvd;		/* Packets received */
	sint31 request;		/* Number of request packets received */
	sint31 response;		/* Number of responses received */
	sint31 unknown;		/* Number of unknown command pkts received */
	sint31 version;		/* Number of version errors */
	sint31 addr_family;	/* Number of address family errors */
	sint31 refusals;		/* Number of packets dropped from a host
					on the refuse list */
};

/* Targets to be accepted. */
struct iprip_accept {
	struct iprip_accept *prev;
	struct iprip_accept *next;
	struct sockaddr target;
};
#define	NULLIPRIPACCEPT	(struct iprip_accept *)0

/* RIP Definition */
extern uint16 Iprip_trace;		/* What level of tracing to do. */
extern int Iprip_merge;			/* If true, merge specific routes with
					 * general routes that do the same thing. */
extern struct iprip_stat Iprip_stat;	/* RIP mib */
extern struct iprip_list *Iprip_list; /* A list of address to send rip packets to. */
extern struct iprip_accept *Iprip_accept; /* A list of gateways to be accepted. */
extern struct udp_cb *Rip_cb; /* The port that rip packets are listened for. */

#endif /* _IP_IPRIP_H */
