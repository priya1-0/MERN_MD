
/* ************************************************************************* */
/*
 *	route.h
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

#ifndef _NET_ROUTE_H
#define _NET_ROUTE_H

/* Include file for routing function, structures and parameters
 */

#define HASHMOD 16
#define HASHMASK 15

#if HASHMOD & HASHMASK
#define RT_HASH(x) (x % HASHMOD)
#else
#define RT_HASH(x) (x & HASHMASK)
#endif

/* IP/IPX routing table entrys */
struct route {
	struct route *prev;	/* Linked list pointers */
	struct route *next;
	struct route *same;
	struct sockaddr target;	/* Target IP/IPX address */
	uint32 netmask;		/* Network/subnetwork mask associated with route */
	struct sockaddr gateway;/* IP/IPX address of local gateway for this target */
	sint15 tos;		/* Type of service/packet priority */
	uint16 hopcount;	/* Hop count metric */
	uint16 delay;		/* Delay to destination network metric */
	sint15 metric;		/* The actual dynamic routing metric */
	struct iface *iface;	/* Device interface structure */
	uint16 flags;
#define	RTPRIVATE	0x1	/* Should the world be told of this route ? */
#define	RTTRIG		0x2	/* Trigger is pending for this route */
#define RT8023		0x4     /* Set if route uses 802.3 ethernet encapsulation */
#define RT8022		0x8	/* Set if route uses 802.2 ethernet encapsulation */
	struct timer timer;	/* Time until aging of this entry */
	uint32 uses;		/* Usage count */

	uint8 ipRouteProto;	/* Method route learned */
#define RTP_OTHER	1L
#define RTP_LCL		2L
#define RTP_NETMGMT	3L
#define RTP_ICMP	4L
#define RTP_RIP		8L
};

extern struct sockaddr Default_addr[AF_IFCMAX];		/* Default addresses for system */
extern struct route *Routes[AF_IFCMAX][HASHMOD];	/* Routing table */
extern struct route Route_default[AF_IFCMAX];		/* Default route entries */

#define	NULLROUTE	((struct route *) 0)

/* Cache for the last-used routing entry, speeds up the common case where
 * we handle a burst of packets to the same destination
 */
struct rt_cache {
	struct sockaddr target;
	struct route *route;
};

extern struct rt_cache Route_cache[AF_IFCMAX]; 		/* The routes last taken */

/* Default hops to delay conversion table as used by gated */
#define DELAY_INFINITY 30000

extern const sint15 Hop_to_delay[];

#endif /* _NET_ROUTE_H */
