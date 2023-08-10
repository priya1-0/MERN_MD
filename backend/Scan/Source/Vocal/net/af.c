
/* ************************************************************************* */
/*
 *	af.c
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
 *	This file contains the address family functions.
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

#include "net/local.h"

/* Determine the default network mask for an address based on address family
 */
ENTRY uint32
af_netmask (struct sockaddr *sa)
{
	uint32 addr;

	switch (sa->sa_family) {
	case AF_INET:
		addr = sa->sin_address;
		if ((addr & 0x80000000L) == 0L) {
			return 0xff000000L;	/* Class A */
		}
		if ((addr & 0xc0000000L) == 0x80000000L) {
			return 0xffff0000L;	/* Class B */
		}
		if ((addr & 0xe0000000L) == 0xc0000000L) {
			return 0xffffff00L;	/* Class C */
		}
		/* Note fall through for class D and E addresses */
	default:;
	}
	return 0xffffffffL;
}

/* Return the network portion of the address according to address family
 *(This code computes the network mask to save another function call)
 */
ENTRY uint32
af_net (struct sockaddr *sa)
{
	uint32 mask = 0xffffffffL;
	uint32 addr;

	switch (sa->sa_family) {
	case AF_INET:
		addr = sa->sin_address;
		if ((addr & 0x80000000L) == 0L) {
			mask = 0xff000000L;	/* Class A */
			break;
		}
		if ((addr & 0xc0000000L) == 0x80000000L) {
			mask = 0xffff0000L;	/* Class B */
			break;
		}
		if ((addr & 0xe0000000L) == 0xc0000000L) {
			mask = 0xffffff00L;	/* Class C */
		}
		break;
	default:
		addr = 0L;
	}
	return (addr & mask);
}

/* Guess the subnetwork mask for an address based on address family
 */
ENTRY uint32
af_subnetmask (struct sockaddr *sa)
{
	uint32 addr, netmask;

	switch (sa->sa_family) {
	case AF_INET:
		addr = sa->sin_address;
		switch (hibyte (hiword (addr)) >> 6) {
		case 3:	/* Class C address */
			/* Is it a host address ? i.e. are there any 1's in the
			 * host part ? */
			if (addr & 0xffL)
				netmask = 0xffffffffL;
			else
				netmask = 0xffffff00L;
			break;
		case 2:  /* Class B address */
			if (addr & 0xffL)
				netmask = 0xffffffffL;
			else if (addr & 0xff00L)
				netmask = 0xffffff00L;
			else
				netmask = 0xffff0000L;
			break;
		case 0:	  /* Class A address */
		case 1:
			if (addr == 0L)
				netmask = 0L;		/* Default address has a zero mask */
			else if (addr & 0xffL)
				netmask = 0xffffffffL;
			else if (addr & 0xff00L)
				netmask = 0xffffff00L;
			else if (addr & 0xff0000L)
				netmask = 0xffff0000L;
			else
				netmask = 0xff000000L;
		}
		break;
	default:
		netmask = 0L;
	}
	return netmask;
}

/* Return hashed network address according to address family
 */
ENTRY uint16
af_hash (struct sockaddr *sa)
{
	uint32 hash;

	hash = af_net (sa);
	if (hash != 0L) {
		while ((hash & 0xffL) == 0L) {
			hash >>= 8;
		}
	}
	return (uint16) hash;
}

/* Compare if network addresses are equal according to address family
 */
ENTRY int
af_netmatch (struct sockaddr *sa1, struct sockaddr *sa2)
{
	return ((sa1->sa_family == sa2->sa_family) &&
	    (af_net (sa1) == af_net (sa2)));
}

/* Compare if network addresses are equal according to address family
 *(This assumes both addresses are of the same family - likely assumption)
 */
ENTRY int
af_netsame (struct sockaddr *sa1, struct sockaddr *sa2)
{
	return (af_net (sa1) == af_net (sa2));
}

/* Compare if host addresses are equal according to address family
 */
ENTRY int
af_hostmatch (struct sockaddr *sa1, struct sockaddr *sa2)
{
	switch (sa1->sa_family) {
	case AF_INET:
		return ((sa2->sa_family == AF_INET) &&
		    (sa1->sin_address == sa2->sin_address));
	case AF_NOVELL:
		return ((sa2->sa_family == AF_NOVELL) &&
		    (sa1->sns_network == sa2->sns_network) &&
		    ! memcmp (sa1->sns_host, sa2->sns_host, 6));
	default:
		return 0;
	}
}

/* Compare if host addresses are equal according to address family
 *(This assumes both addresses are of the same family - likely assumption)
 */
ENTRY int
af_hostsame (struct sockaddr *sa1, struct sockaddr *sa2)
{
	switch (sa1->sa_family) {
	case AF_INET:
		return (sa1->sin_address == sa2->sin_address);
	default:
		return 0;
	}
}

/* Compare if port addresses are equal according to address family
 */
ENTRY int
af_portmatch (struct sockaddr *sa1, struct sockaddr *sa2)
{
	switch (sa1->sa_family) {
	case AF_INET:
		return ((sa2->sa_family == AF_INET) &&
		    (sa1->sin_address == sa2->sin_address) &&
		    (sa1->sin_port == sa2->sin_port));
	default:
		return 0;
	}
}

/* Compare if port addresses are equal according to address family
 *(This assumes both addresses are of the same family - likely assumption)
 */
ENTRY int
af_portsame (struct sockaddr *sa1, struct sockaddr *sa2)
{
	switch (sa1->sa_family) {
	case AF_INET:
		return ((sa1->sin_address == sa2->sin_address) &&
		    (sa1->sin_port == sa2->sin_port));
	default:
		return 0;
	}
}

/* Compare if connection/port addresses are equal according to address family
 */
ENTRY int
af_connectionmatch (struct sockaddr *sa1, struct sockaddr *sa2)
{
	switch (sa1->sa_family) {
	case AF_INET:
		return ((sa2->sa_family == AF_INET) &&
		    (sa1->sin_address == sa2->sin_address) &&
		    (sa1->sin_port == sa2->sin_port));
	default:
		return 0;
	}
}

/* Compare if connection/port addresses are equal according to address family
 *(This assumes both addresses are of the same family - likely assumption)
 */
ENTRY int
af_connectionsame (struct sockaddr *sa1, struct sockaddr *sa2)
{
	switch (sa1->sa_family) {
	case AF_INET:
		return ((sa1->sin_address == sa2->sin_address) &&
		    (sa1->sin_port == sa2->sin_port));
	default:
		return 0;
	}
}

/* Check for broadcast address according to address family
 */
ENTRY int
af_broadcast (struct sockaddr *sa, uint32 netmask)
{
	switch (sa->sa_family) {
	case AF_INET:
		if (netmask == 0xffffffffL)
			return 0;
		return ((sa->sin_address | netmask) == 0xffffffffL);
	default:
		return 0;
	}
}

/* Initialize default values according to address family
 */
ENTRY void
af_default (int family, struct sockaddr *sa)
{
	switch (family) {
	case AF_INET:
		sa->sin_address = 0L;
		sa->sin_port = 0;
		break;
	default:
		sa->sa_family = AF_NONE;
		return;
	}
	sa->sa_family = family;
}
