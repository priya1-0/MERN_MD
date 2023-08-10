
/* ************************************************************************* */
/*
 *	route.c
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
 *	This file contains the routing and table functions.
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

#include "system/system.h"
#include "lansend/global.h"

#include "net/local.h"

#include "dev/dev.h"
#include "sys/sys.h"

#include "ip/ip.h"

#include "trace/trace.h"

#include "lansend/lansend.h"

/* Default addresses for system */
struct sockaddr Default_addr[AF_IFCMAX] = {
	{AF_INET},		/* Start with default IP address of 0.0.0.0 */
};

/* All known routes */
struct route *Routes[AF_IFCMAX][HASHMOD];	/* Routing table */
struct route Route_default[AF_IFCMAX] = {	/* Default route entries */
	{
		NULLROUTE, NULLROUTE, NULLROUTE,	/* Default IP route */
		{AF_NONE}, 0, {AF_NONE},
		0, IPRIP_INFINITY, 0, 0,	/* Init hop count metric to infinity */
		NULLIF, 0, {0}, 0, RTP_OTHER
	},
};
struct rt_cache Route_cache[AF_IFCMAX] = {	/* The routes last taken */
	{
		{AF_NONE}, NULLROUTE
	},
};

/* Default hops to delay conversion table as used by gated */
extern const sint15 Hop_to_delay[] = {
	  0,			/* 0 */
	  100,			/* 1 */
	  148,			/* 2 */
	  219,			/* 3 */
	  325,			/* 4 */
	  481,			/* 5 */
	  713,			/* 6 */
	  1057,			/* 7 */
	  1567,			/* 8 */
	  2322,			/* 9 */
	  3440,			/* 10 */
	  5097,			/* 11 */
	  7552,			/* 12 */
	  11190,		/* 13 */
	  16579,		/* 14 */
	  24564,		/* 15 */
	  DELAY_INFINITY,	/* 16 */
	  DELAY_INFINITY,	/* 17 */
	  DELAY_INFINITY,	/* 18 */
};

ENTRY void
route_init (void)
{
	int i, j;

	/* Default addresses for system */
	Default_addr[AF_INET].sa_family = AF_INET;
	Default_addr[AF_INET].sin_address = 0L;

	for (i = 0; i < AF_IFCMAX; i++) {
		for (j = 0; j < HASHMOD; j++) {
			Routes[i][j] = NULLROUTE;
		}
		Route_cache[i].target.sa_family = AF_NONE;
		Route_cache[i].route = NULLROUTE;

		Route_default[i].prev = NULLROUTE;	/* Linked list pointers */
		Route_default[i].next = NULLROUTE;
		Route_default[i].same = NULLROUTE;
		Route_default[i].target.sa_family = AF_NONE;	/* Target IP/IPX address */
		Route_default[i].netmask = 0;		/* Network/subnetwork mask associated with route */
		Route_default[i].gateway.sa_family = AF_NONE;/* IP/IPX address of local gateway for this target */
		Route_default[i].tos = 0;		/* Type of service/packet priority */
		Route_default[i].hopcount = IPRIP_INFINITY;	/* Hop count metric */
		Route_default[i].delay = 0;		/* Delay to destination network metric */
		Route_default[i].metric = 0;		/* The actual dynamic routing metric */
		Route_default[i].iface = NULLIF;	/* Device interface structure */
		Route_default[i].flags = 0;
		Route_default[i].timer.next = 0;	/* Time until aging of this entry */
		Route_default[i].uses = 0;		/* Usage count */
		Route_default[i].ipRouteProto = RTP_OTHER;	/* Method route learned */
	}

}

/* Add an entry to the routing table.
 *
 * TARGET is the target address.
 * NETMASK is the targets netmask.
 * GATEWAY is an optional gateway to be reached via IFACE.
 * IFP is the interface to which a packet is to be routed.
 * HOPCOUNT is the number of networks between here and the target.
 * DELAY is the amount of time it take to get from here to the target.
 * tos
 * METRIC is the metric for this route entry.
 * TTL is the Time To Live of this route entry in seconds.
 * PRIVATE, if not 0 inhibits the advertising of this entry.
 *
 * Returns a pointer to the route on success, NULLROUTE on failure */
ENTRY struct route *
rt_add (struct sockaddr *target, uint32 netmask, struct sockaddr *gateway, struct iface *ifp, uint16 hopcount, uint16 delay, sint15 tos, sint31 ttl, char private_add)
{
	struct route *rp, **hp, *rpn;
	uint16 family = target->sa_family;
	uint32 mask;

	if (ifp == NULLIF)
		return NULLROUTE;

	if ((target->sa_family == AF_INET) && (netmask == 0xffffffffL) && ismyaddr (target))
		return NULLROUTE;	/* Don't accept routes to ourselves */

	if (family >= AF_IFCMAX)
		return NULLROUTE;

	Route_cache[family].route = NULLROUTE;	/* Flush cache */

	/* Find the route if it already exists */
	if (netmask == 0L) {
		/* Zero mask refers to the default route */
		rp = &Route_default[family];
		memset ((char *) rp, 0, sizeof (struct route));
	} else {
		if ((rp = rt_exact (target, netmask, NULLIF)) == NULLROUTE) {
			/* The target is not already in the table, so create a new
			 * entry and put it in */
			if ((rp = (struct route *) calloc (1, sizeof (struct route))) == NULLROUTE)
				return NULLROUTE;

			/* Compute mask with ones in all least significant
			 * bits that are zero plus one more bit */
			mask = 1L;
			if (netmask != 0xffffffffL) {
				mask = netmask ^ (netmask -1);
			}
			/* Find spot to insert route entry according to netmask */
			hp = &Routes[family][rt_hash (target) ];
			if (((rpn = *hp) == NULLROUTE) || ((rpn->netmask & mask) == 0)) {
				/* Insert at head of table */
				rp->prev = NULLROUTE;
				rp->next = *hp;
				if (rp->next != NULLROUTE)
					rp->next->prev = rp;
				*hp = rp;
			}
			else {
				/* Search for correct spot to insert */
				while (rpn->next != NULLROUTE) {
					if ((rpn->next->netmask & mask) == 0)
						break;
					rpn = rpn->next;
				}
				/* Insert before route found in table which is
				 * really after current route pointer */
				rp->prev = rpn;
				rp->next = rpn->next;
				rpn->next = rp;
				if (rp->next != NULLROUTE)
					rp->next->prev = rp;
			}
		}
		else {
			for (; rp != NULLROUTE; rp = rp->same) {
				rpn = rp;
				if (rp->iface == ifp)
					break;
			}
			if (rp == NULLROUTE) {
				/* If the target route is already in the table but under
				 * a different iface, create a second path to the target.
				 */
				rp = (struct route *) callocw (1, sizeof (struct route));
				/* Insert at end of same list for the route entry */
				rpn->same = rp;
				rp->prev = rpn;
			}
		}
	}

	/* Fill in / replace old data in this route */
	rp->target = *target;
	rp->netmask = netmask;
	if (gateway != NULLSA) {
		rp->gateway = *gateway;
	}
	else {
		rp->gateway.sa_family = AF_NONE;
	}
	rp->tos = tos;
	hopcount = min (hopcount, 16);	/* Should this be symbolic and per family?? */
	rp->hopcount = hopcount;
	if (delay == 0)
		rp->delay = Hop_to_delay[hopcount];
	else
		rp->delay = delay;
	rp->iface = ifp;
	rp->flags = private_add ? RTPRIVATE : 0;	/* Should anyone be told of this route? */
	switch (family) {
	case AF_INET:
		rp->timer.func = iprt_timeout;  /* Set the timer field */
		break;
	}
	rp->timer.arg = (void *) rp;
	set_timer (&rp->timer, ttl * 1000L);
	stop_timer (&rp->timer);
	start_timer(&rp->timer); /* Start the timer if appropriate */
	rp->ipRouteProto = RTP_LCL;

	rt_update ();
	return rp;
}

/* Remove an entry from the routing table.
 *
 * TARGET is the address to be removed.
 * BITS is the number of significant bits in the addresss.
 *
 * Returns 0 on success, -1 if entry was not in table */
ENTRY int
rt_drop (struct sockaddr *target, uint32 netmask, struct iface *ifp)
{
	register struct route *rp;
	struct route *rps, *rpd;
	uint16 family = target->sa_family;

	if (family >= AF_IFCMAX)
		return -1;

	Route_cache[family].route = NULLROUTE;	/* Flush the cache */

	if (netmask == 0L) {
		/* Nail the default entry */
		stop_timer (&Route_default[family].timer);
		Route_default[family].iface = NULLIF;
		return 0;
	}
	/* Search appropriate chain for existing entry */
	for (rp = Routes[family][rt_hash (target) ];
	    rp != NULLROUTE; rp = rp->next) {
		if (netmask != rp->netmask)
			continue;
		if (rt_netsame (&rp->target, target, rp->netmask))
			break;
	}
	if (rp == NULLROUTE)
		return -1;	/* Not in table */
	/* Determine which of the same group to drop (or all) */
	for (rps = rp; rps->same != NULLROUTE;) {
		if ((ifp == NULLIF) || (rps->same->iface == ifp)) {
			/* Drop the specific route entry */
			rpd = rps->same;
			stop_timer (&rpd->timer);
			rps->same = rpd->same;
			if (rps->same != NULLROUTE)
				rps->same->prev = rps;
			free ((char *) rpd);
		}
		else
			rps = rps->same;
	}
	/* Process dropping head of same group */
	if ((ifp == NULLIF) || (rp->iface == ifp)) {
		stop_timer (&rp->timer);
		if (rp->same != NULLROUTE) {
			rp->same->next = rp->next;
			rp->same->prev = rp->prev;
			if (rp->next != NULLROUTE)
				rp->next->prev = rp->same;
			if (rp->prev != NULLROUTE)
				rp->prev->next = rp->same;
			else
				/* First route */
				Routes[family][rt_hash (target) ] = rp->same;
		}
		else {
			if (rp->next != NULLROUTE)
				rp->next->prev = rp->prev;
			if (rp->prev != NULLROUTE)
				rp->prev->next = rp->next;
			else
				/* First route */
				Routes[family][rt_hash (target) ] = rp->next;
		}
		free ((char *) rp);
	}
	return 0;
}

/* Given an address, return the MTU (Maximum Transmit Unit) of the local
 * interface used to reach that destination. This is used by TCP to avoid
 * local fragmentation.
 *
 * ADDR is the address.
 *
 * Return the MTU or 0 if not found */
ENTRY uint16
rt_mtu (struct sockaddr *addr)
{
	register struct route *rp;
	struct iface *iface;

	rp = rt_lookup (addr);
	if (rp == NULLROUTE || rp->iface == NULLIF)
		return 0;

	iface = rp->iface;
		return iface->mtu;
}

/* Given a destination address, return the address of the local
 * interface that will be used to reach it.
 *
 * ADDR is the address.
 *
 * Return the address of the interface, if there is no route to the
 * destination, pick the first non - loopback address */
ENTRY struct sockaddr *
locaddr (struct sockaddr *addr)
{
	register struct route *rp;
	struct iface *ifp;

	if (ismyaddr (addr))
		return addr;	/* Loopback case */

	rp = rt_lookup(addr);	/* This may need to find/use the address of the active route to the destination */
	if (rp != NULLROUTE) {
		ifp = rp->iface;
		if (ifp == Loopback)
			ifp = NULLIF;	/* No dice */

	}
	else {
		/* No route currently exists, so just pick the first real
		 * interface and use its address */
		for (ifp = Ifaces;ifp != NULLIF;ifp = ifp->next) {
			if ((ifp != Loopback)
			)
				break;
		}
	}

	if ((ifp == NULLIF) || (ifp->address[addr->sa_family].sa_family == AF_NONE)) {
		if (addr->sa_family == AF_INET)
			return &Default_addr[AF_INET];
		if (addr->sa_family == AF_NOVELL)
			return &Default_addr[AF_NOVELL];
	}
	return (&(ifp->address[addr->sa_family]));
}

/* Adjust the metrics for all routes
 */
ENTRY void
rt_update (void)
{
	int i, j;
	struct route *rp, *rps;
	int hop_infinity;

	/* Search all routes and determine the metric based on current assignments of virtual to physical interfaces */
	hop_infinity = IPRIP_INFINITY;
	for (i = 0; i < AF_IFCMAX; i++) {
		for (j = 0; j < HASHMOD; j++) {
			for (rp = Routes[i][j]; rp != NULLROUTE; rp = rp->next) {
				for (rps = rp; rps != NULLROUTE; rps = rps->same) {
					if (rps->hopcount == hop_infinity) {
						rps->metric = DELAY_INFINITY;
					}
					else if (!(rps->iface->flags & IFF_START)) {
						rps->metric = DELAY_INFINITY;
					}
					else if (!(rps->iface->flags & IFF_UP)) {
						rps->metric = DELAY_INFINITY;
					}
					else {
						rps->metric = rps->delay;
					}
				}
			}
		}
		rps = &Route_default[i];
		if (rps->hopcount == hop_infinity) {
			rps->metric = DELAY_INFINITY;
		}
		else if (!(rps->iface->flags & IFF_START)) {
			rps->metric = DELAY_INFINITY;
		}
		else if (!(rps->iface->flags & IFF_UP)) {
			rps->metric = DELAY_INFINITY;
		}
		else {
			rps->metric = rps->delay;
		}
		Route_cache[i].route = NULLROUTE;	/* Flush the cache */
	}
}

/* Look up target in hash table, matching the entry having the fewest number
 * of masked trailing bits.
 *
 * TARGET is the target to be looked up.
 *
 * Return the route, or the default route if not found.  If the default route
 * not set, return NULLROUTE */
ENTRY struct route *
rt_lookup (struct sockaddr *target)
{
	register struct route *rp;
	uint16 family = target->sa_family;

	if (family >= AF_IFCMAX) {
		return NULLROUTE;
	}

	/* Examine cache first */
	if (rt_netsame (target, &Route_cache[family].target, 0xffffffffL) && (Route_cache[family].route != NULLROUTE)) {
		return Route_cache[family].route;
	}

	for (rp = Routes[family][rt_hash (target) ];
	    rp != NULLROUTE;rp = rp->next) {
		if (rt_netsame (&rp->target, target, rp->netmask)) {
			/* Search equivalent entries for lowest delay */
			struct route *rps = rp->same;
			while (rps != NULLROUTE) {
				if (rps->metric < rp->metric)
					rp = rps;
				rps = rps->same;
			}
			/* Stash in cache and return */
			Route_cache[family].target = *target;
			Route_cache[family].route = rp;
			return rp;
		}
	}

	/* Didn't find the route in the table, how about the default route */
	if (Route_default[family].iface != NULLIF) {
		Route_cache[family].target = *target;
		Route_cache[family].route = &Route_default[family];
		return &Route_default[family];
	} else {
		return NULLROUTE;
	}
}

/* Look up target in hash table, matching the entry having the fewest number
 * of masked trailing bits.
 *
 * TARGET is the target to be looked up.
 *
 * Return the route, or the default route if not found.  If the default route
 * not set, return NULLROUTE */
ENTRY struct route *
rt_assign (struct iface **ifpp, struct sockaddr *target)
{
	register struct route *rp;
	struct iface *ifp;

	if ((rp = rt_lookup (target)) != NULLROUTE) {
		if (rp->metric == DELAY_INFINITY)
			return NULLROUTE;
		ifp = rp->iface;
		*ifpp = ifp;
	}
	return rp;
}
/* Search routing table for entry with a specific mask.
 *
 * TARGET is he address prefix to search for.
 * NETMASK is the mask for the prefix.
 *
 * Return the route, or NULLROUTE if not found */
ENTRY struct route *
rt_exact (struct sockaddr *target, uint32 netmask, struct iface *ifp)
{
	register struct route *rp, *rps;
	uint16 family = target->sa_family;

	if (family >= AF_IFCMAX)
		return NULLROUTE;

	/* If netmask == 0 then return the default route if it exists */
	if (netmask == 0L) {
		if (Route_default[family].iface != NULLIF)
			return &Route_default[family];
		else
			return NULLROUTE;
	}

	/* Scan list for routes */
	for (rp = Routes[family][rt_hash (target) ];
	    rp != NULLROUTE; rp = rp->next) {
		if (netmask != rp->netmask)
			continue;
		if (rt_netsame (&rp->target, target, rp->netmask)) {
			if (ifp == NULLIF)
				return rp;
			/* Scan for same routes */
			for (rps = rp; rps != NULLROUTE; rps = rps->same) {
				if (rps->iface == ifp)
					return rps;
			}
		}
	}
	return NULLROUTE;
}

/* Scan the routing table. For each entry, see if there's a less-specific
 * one that points to the same interface and gateway. If so, delete
 * the more specific entry, since it is redundant.
 *
 * TRACE is the level of tracing wanted in this function */
ENTRY void
rt_merge (uint16 sa_family, int trace)
{
	int i;
	uint32 netmask;
	struct route *rp, *rpnext, *rp1;

	if (sa_family >= AF_IFCMAX)
		return;
	/* For each hash bucket */
	for (i = 0;i < HASHMOD;i++) {
		/* For each entry in the bucket */
		for (rp = Routes[sa_family][i];rp != NULLROUTE;rp = rpnext) {
			rpnext = rp->next;
			/* Search all the less specific addresses */
			for (netmask = rp->netmask; netmask != 0L; netmask <<= 1) {
				if ((rp1 = rt_exact (& (rp->target), netmask, rp->iface)) != NULLROUTE &&
				    /* rp1->iface == rp->iface && */
				    af_hostsame (&(rp1->gateway), &(rp->gateway))) {
					if (trace > 1)
						printf("merge %s 0x%8lx\n", snhtoa(&rp->target),
						       rp->netmask);
					rt_drop (&(rp->target), rp->netmask, rp->iface);
					break;
				}
			}
		} /* For entry */
	} /* For bucket */
}

/* Compare if network/subnetwork/host addresses are equal according to address family
 */
ENTRY int
rt_netmatch (struct sockaddr *sa1, struct sockaddr *sa2, uint32 netmask)
{
	switch (sa1->sa_family) {
	case AF_INET:
		return ((sa2->sa_family == AF_INET) &&
		    ((sa1->sin_address & netmask) == (sa2->sin_address & netmask)));
	case AF_NOVELL:
		return ((sa2->sa_family == AF_NOVELL) &&
		    ((sa1->sns_network & netmask) == (sa2->sns_network & netmask)));
	default:
		return 0;
	}
}

/* Compare if network/subnetwork/host addresses are equal according to address family
 */
ENTRY int
rt_netsame (struct sockaddr *sa1, struct sockaddr *sa2, uint32 netmask)
{
	switch (sa1->sa_family) {
	case AF_INET:
		return ((sa1->sin_address & netmask) == (sa2->sin_address & netmask));
	case AF_NOVELL:
		return ((sa1->sns_network & netmask) == (sa2->sns_network & netmask));
	default:
		return 0;
	}
}

/* Return hashed route table index according to address family
 */
ENTRY uint16
rt_hash (struct sockaddr *sa)
{
	uint16 hash;

	hash = af_hash (sa);

#if HASHMOD & HASHMASK
	return (hash % HASHMOD);
#else /* HASHMOD & HASHMASK */
	return (hash & HASHMASK);
#endif /* HASHMOD & HASHMASK */
}
