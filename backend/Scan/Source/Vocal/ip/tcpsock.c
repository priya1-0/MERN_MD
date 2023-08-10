
/* ************************************************************************* */
/*
 *	tcpsock.c
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

static uint16 next_tcp_port = IPPORT_REGISTERED + 1;	/* Use the first dynamic port */

/* ************************************************************************* */

ENTRY void
tcpsock_init (void)
{
	Lport = 1024;
	next_tcp_port = (generic_rand16 () >> 3) + IPPORT_REGISTERED + 1;
}

/* ************************************************************************* */

ENTRY int
so_tcp (struct usock *up, int protocol)
{
	up->type = TYPE_TCP;
	return 0;
}

ENTRY int
so_tcp_listen (struct usock *up, int backlog)
{
	int s;
	struct sockaddr *local;

	s = up->index;
	if (up->name == NULLCHAR)
		autobind (up);

	local = (struct sockaddr *) up->name;
	up->cb.tcb = open_tcp (local, NULLSA,
	 backlog ? TCP_SERVER:TCP_PASSIVE, 0,
	(void (*) (void))s_trcall, (void (*) (void))s_ttcall, (void (*) (void))s_tscall, up->tos, s);
	return 0;
}

ENTRY int
so_tcp_conn (struct usock *up)
{
	int s;
	struct tcb *tcb;
	struct sockaddr *local, *remote;

	if (up->name == NULLCHAR) {
		autobind (up);
	}
	if (checkipaddr (up->peername, up->namelen) == -1) {
		errno = EAFNOSUPPORT;
		return -1;
	}
	s = up->index;
	/* Construct the TCP-style ports from the sockaddr structs */
	local = (struct sockaddr *) up->name;
	remote = (struct sockaddr *) up->peername;

	if (local->sin_address == IPADDR_ANY)
		/* Choose a local address */
		local->sin_address = (locaddr (remote))->sin_address;

	/* Open the TCB in active mode */
	up->cb.tcb = open_tcp (local, remote, TCP_ACTIVE, 0,
	 (void (*) (void))s_trcall, (void (*) (void))s_ttcall, (void (*) (void))s_tscall, up->tos, s);

	/* Wait for the connection to complete */
	while ((tcb = up->cb.tcb) != NULLTCB && tcb->state != TCP_ESTABLISHED) {
		if (up->noblock) {
			errno = EWOULDBLOCK;
			return -1;
		} else if ((errno = pwait (up)) != 0) {
			return -1;
		}
	}
	if (tcb == NULLTCB) {
		/* Probably got refused */
		free (up->peername);
		up->peername = NULLCHAR;
		errno = ECONNREFUSED;
		return -1;
	}
	return 0;
}

ENTRY int
so_tcp_recv (struct usock *up, struct mbuf **bpp, int len, char *from, int *fromlen)
{
	int cnt;
	struct tcb *tcb;

	while ((tcb = up->cb.tcb) != NULLTCB && tcb->r_upcall != trdiscard
	 && (cnt = recv_tcp (tcb, bpp, (uint16) len)) == -1) {
		if (up->noblock) {
			errno = EWOULDBLOCK;
			return -1;
		} else if ((errno = pwait (up)) != 0) {
			return -1;
		}
	}
	if (tcb == NULLTCB) {
		/* Connection went away */
		errno = ENOTCONN;
		return -1;
	} else if (tcb->r_upcall == trdiscard) {
		/* Receive shutdown has been done */
		errno = ENOTCONN;	/* CHANGE */
		return -1;
	}
	return cnt;
}

ENTRY int
so_tcp_send (struct usock *up, struct mbuf *bp, char *to)
{
	struct tcb *tcb;
	int cnt;

	if ((tcb = up->cb.tcb) == NULLTCB) {
		free_p (bp);
		errno = ENOTCONN;
		return -1;
	}
	cnt = send_tcp (tcb, bp);

	while ((tcb = up->cb.tcb) != NULLTCB &&
	 tcb->sndcnt > tcb->window) {
		/* Send queue is full */
		if (up->noblock) {
			errno = EWOULDBLOCK;
			return -1;
		} else if ((errno = pwait (up)) != 0) {
			return -1;
		}
	}
	if (tcb == NULLTCB) {
		errno = ENOTCONN;
		return -1;
	}
	return cnt;
}

ENTRY int
so_tcp_qlen (struct usock *up, int rtx)
{
	int len;

	switch (rtx) {
	case 0:
		len = up->cb.tcb->rcvcnt;
		break;
	case 1:
		len = up->cb.tcb->sndcnt;
		break;
	}
	return len;
}

ENTRY int
so_tcp_kick (struct usock *up)
{
	kick_tcp (up->cb.tcb);
	return 0;
}

ENTRY int
so_tcp_shut (struct usock *up, int how)
{
	switch (how) {
	case 0:	/* No more receives -- replace upcall */
		up->cb.tcb->r_upcall = trdiscard;
		break;
	case 1:	/* Send EOF */
		close_tcp (up->cb.tcb);
		break;
	case 2:	/* Blow away TCB */
		reset_tcp (up->cb.tcb);
		up->cb.tcb = NULLTCB;
		break;
	}
	return 0;
}

ENTRY int
so_tcp_close (struct usock *up)
{
	if (up->cb.tcb != NULLTCB) {	/* In case it's been reset */
		up->cb.tcb->r_upcall = trdiscard;
		/* Tell the TCP_CLOSED upcall there's no more socket */
		up->cb.tcb->user = -1;
		close_tcp (up->cb.tcb);
	}
	return 0;
}

/* TCP receive upcall routine */
LOCAL void
s_trcall (struct tcb *tcb, int cnt)
{
	/* Wake up anybody waiting for data, and let them run */
	psignal (itop (tcb->user), 1);
	pwait (NULL);
}

/* TCP transmit upcall routine */
LOCAL void
s_ttcall (struct tcb *tcb, int cnt)
{
	/* Wake up anybody waiting to send data, and let them run */
	psignal (itop (tcb->user), 1);
	pwait (NULL);
}

/* TCP state change upcall routine */
LOCAL void
s_tscall (struct tcb *tcb, int old, int new_state)
{
	int s, ns;
	struct usock *up, *nup, *oup;
	struct sockaddr *sp;

	s = tcb->user;
	oup = up = itop (s);

	switch (new_state) {
	case TCP_CLOSED:
		/* Clean up. If the user has already closed the socket,
		 * then up will be null (s was set to -1 by the close routine) .
		 * If not, then this is an abnormal close (e.g., a reset)
		 * and clearing out the pointer in the socket structure will
		 * prevent any further operations on what will be a freed
		 * control block. Also wake up anybody waiting on events
		 * related to this tcb so they will notice it disappearing.
		 */
		if (up != NULLUSOCK) {
			up->cb.tcb = NULLTCB;
			up->errcodes[0] = tcb->reason;
			up->errcodes[1] = tcb->type;
			up->errcodes[2] = tcb->code;
		}
		del_tcp (tcb);
		break;
	case TCP_SYN_RECEIVED:
		/* Handle an incoming connection. If this is a server TCB,
		 * then we're being handed a "clone" TCB and we need to
		 * create a new socket structure for it. In either case,
		 * find out who we're talking to and wake up the guy waiting
		 * for the connection.
		 */
		if (tcb->flags.clone) {
			/* Clone the socket */
			ns = socket (AF_INET, SOCK_STREAM, 0);
			nup = itop (ns);
			ASSIGN (*nup, *up);
			tcb->user = ns;
			nup->cb.tcb = tcb;
			/* Allocate new memory for the name areas */
			nup->name = (char *) mallocw (SOCKSIZE);
			nup->peername = (char *) mallocw (SOCKSIZE);
			nup->index = ns;
			/* Store the new socket # in the old one */
			up->rdysock = ns;
			up = nup;
			s = ns;
		} else {
			/* Allocate space for the peer's name */
			up->peername = (char *) mallocw (SOCKSIZE);
			/* Store the old socket # in the old socket */
			up->rdysock = s;
		}
		/* Load the addresses. Memory for the name has already
		 * been allocated, either above or in the original bind.
		 */
		sp = (struct sockaddr *) up->name;
		*sp = up->cb.tcb->conn.local;
		up->namelen = SOCKSIZE;

		sp = (struct sockaddr *) up->peername;
		*sp = up->cb.tcb->conn.remote;
		up->peernamelen = SOCKSIZE;

		/* Wake up the guy accepting it, and let him run */
		psignal (oup, 1);
		pwait (NULL);
		break;
	default:	/* Ignore all other state transitions */
		break;
	}
	psignal(up,0);	/* In case anybody's waiting */
}
/* Discard data received on a TCP connection. Used after a receive shutdown or
 * close_s until the TCB disappears.
 */
LOCAL void
trdiscard (struct tcb *tcb, int cnt)
{
	struct mbuf *bp;

	recv_tcp (tcb, &bp, (uint16) cnt);
	free_p (bp);
}

ENTRY char *
tcpstate (struct usock *up)
{
	if (up->cb.tcb == NULLTCB)
		return NULLCHAR;
	return Tcpstates[(int) up->cb.tcb->state];
}

ENTRY int
so_tcp_stat (struct usock *up)
{
	tcb_detail (up->cb.tcb);
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

	/* Assign the next TCP port number */
	local.sin_port = tcp_get_next_port ();
	bind (s, (char *) &local, SOCKSIZE);
}

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */
/*
 *	Entry Routine:	tcp_get_next_port
 *
 *	This routine gets the next (in sequential order) available TCP port
 *	number which is outside the possible reserved ranges and is not in
 *	use locally or mapped via a NAT translation.
 *
 *	Parameters:
 *
 *	Returns:
 *		next available port number
 */
ENTRY uint16
tcp_get_next_port (void)
{
	/* Assign the next TCP port number */

	for (;;) {
		/* Increment the port number */
		next_tcp_port++;
		if (!next_tcp_port) {
			next_tcp_port = IPPORT_REGISTERED + 1;
		}

		/* Check for avaibility of port */
		if (tcp_port_avail (next_tcp_port, 0)) {
			break;
		}

		/* We should never run out of port numbers, so keep trying */
	}

	return next_tcp_port;
}

/* ************************************************************************* */
/*
 *	Entry Routine:	tcp_port_avail
 *
 *	This routine checks if the candidate TCP port number is not in use locally
 *	or mapped via a NAT translation.
 *
 *	Parameters:
 *
 *	Returns:
 *		TRUE if the port is available (currently not in use)
 *		FALSE otherwise
 */
ENTRY bool
tcp_port_avail (uint16 port, bool local)
{
	register struct tcb *tcb;

	/* Check for avaibility of port */
	for (tcb = Tcbs; tcb != NULLTCB; tcb = tcb->next) {
		if (port == tcb->conn.local.sin_port) {
			return 0;	/* Port is in use and hence not available */
		}
	}

	return 1;			/* Port is available */
}
