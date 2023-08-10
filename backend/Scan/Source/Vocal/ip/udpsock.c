
/* ************************************************************************* */
/*
 *	udpsock.c
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

#include "system/system.h"
#include "lansend/global.h"

#include "net/net.h"
#include "sys/sys.h"
#include "dev/dev.h"

#include "ip/ip.h"

#include "ip/local.h"

/* ************************************************************************* */

ENTRY int so_udp (struct usock *up, int protocol)
{
	return 0;
}

ENTRY int
so_udp_bind (struct usock *up)
{
	int s;

	s = up->index;
	if ((up->cb.udp = open_udp ((struct sockaddr *) up->name, (void (*) (void))s_urcall)) == NULLUDP)
		return -1;
	up->cb.udp->user = s;
	return 0;
}

ENTRY int
so_udp_conn (struct usock *up)
{
	if (up->name == NULLCHAR) {
		autobind (up);
	}
	return 0;
}

ENTRY int
so_udp_recv (struct usock *up, struct mbuf **bpp, int len, char *from, int *fromlen)
{
	int cnt;
	struct udp_cb *udp;
	struct sockaddr fsocket, *remote;

	while ((udp = up->cb.udp) != NULLUDP
	&& (cnt = recv_udp (udp, &fsocket, bpp)) == -1) {
		if (up->noblock) {
			errno = EWOULDBLOCK;
			return -1;
		} else if ((errno = pwait (up)) != 0) {
			return -1;
		}
	}
	if (udp == NULLUDP) {
		/* Connection went away */
		errno = ENOTCONN;
		return -1;
	}
	if (from != NULLCHAR && fromlen != (int *) NULL && *fromlen >= SOCKSIZE) {
		remote = (struct sockaddr *) from;
		*remote = fsocket;
		*fromlen = SOCKSIZE;
	}
	return cnt;
}

ENTRY int
so_udp_send (struct usock *up, struct mbuf *bp, char *to)
{
	struct sockaddr *local, *remote;

	if (up->name == NULLCHAR)
		autobind (up);
	local = (struct sockaddr *) up->name;
	if (to != NULLCHAR) {
		remote = (struct sockaddr *) to;
	} else if (up->peername != NULLCHAR) {
		remote = (struct sockaddr *) up->peername;
	} else {
		free_p (bp);
		errno = ENOTCONN;
		return -1;
	}
	return send_udp (local, remote, up->tos, 0, bp, 0, 0, 0);
}

ENTRY int
so_udp_qlen (struct usock *up, int rtx)
{
	int len;

	switch (rtx) {
	case 0:
		len = up->cb.udp->rcvcnt;
		break;
	case 1:
		len = 0;
		break;
	}
	return len;
}

ENTRY int
so_udp_close (struct usock *up)
{
	if (up->cb.udp != NULLUDP) {
		del_udp (up->cb.udp);
	}
	return 0;
}

ENTRY int
so_udp_shut (struct usock *up, int how)
{
	int s;

	s = up->index;
	close_s (s);
	return 0;
}

LOCAL void
s_urcall (struct iface *iface, struct udp_cb *udp, int cnt)
{
	psignal (itop (udp->user), 1);
	pwait (NULL);
}

ENTRY int
so_udp_stat (struct usock *up)
{
	ucb_detail (up->cb.udp);
	return 0;
}

/* ************************************************************************* */

/* Issue an automatic bind of a local address */
LOCAL void
autobind (struct usock *up)
{
	struct sockaddr local;
	int s;

	s = up->index;
	local.sa_family = AF_INET;
	local.sin_address = IPADDR_ANY;

	/* Assign the next UDP port number */

	local.sin_port = udp_get_next_port ();
	bind (s, (char *) &local, SOCKSIZE);
}

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

static uint16 next_udp_port = IPPORT_REGISTERED + 1;

/* ************************************************************************* */

ENTRY void
udpsock_init (void)
{
	next_udp_port = (generic_rand16 () >> 3) + IPPORT_REGISTERED + 1;
}

/* ************************************************************************* */
/*
 *	Entry Routine:	udp_get_next_port
 *
 *	This routine gets the next (in sequential order) available UDP port
 *	number which is outside the possible reserved ranges and is not in
 *	use locally or mapped via a NAT translation.
 *
 *	Parameters:
 *
 *	Returns:
 *		next available port number
 */
ENTRY uint16
udp_get_next_port (void)
{
	/* Assign the next UDP port number */

	for (;;) {
		/* Increment the port number */
		next_udp_port++;
		if (!next_udp_port) {
			next_udp_port = IPPORT_REGISTERED + 1;
		}

		/* Make sure at least some useable range is always available */
		if (next_udp_port <= (IPPORT_DYNAMIC - 1024)) {

		}

		/* Check for avaibility of port */
		if (udp_port_avail (next_udp_port, 0)) {
			break;
		}

		/* We should never run out of port numbers, so keep trying */
	}

	return next_udp_port;
}

/* ************************************************************************* */
/*
 *	Entry Routine:	udp_port_avail
 *
 *	This routine checks if the candidate UDP port number is not in use locally
 *	or mapped via a NAT translation.
 *
 *	Parameters:
 *
 *	Returns:
 *		TRUE if the port is available (currently not in use)
 *		FALSE otherwise
 */
ENTRY bool
udp_port_avail (uint16 port, bool local)
{
	register struct udp_cb *up;

	/* Check for avaibility of the candidate port */
	for (up = Udps; up != NULLUDP; up = up->next) {
		if (port == up->socket.sin_port) {
			return 0;	/* Port is in use and hence not available */
		}
	}

	return 1;			/* Port is available */
}
