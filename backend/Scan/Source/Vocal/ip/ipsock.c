
/* ************************************************************************* */
/*
 *	ipsock.c
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

uint16 Lport = 1024;
char Inet_eol[] = "\r\n";

/* ************************************************************************* */

/* DLW Create user socket UP for protocal PROTOCAL.
 * The packet upcall is set to rip_recv. */
ENTRY int
so_ip_sock (struct usock *up, int protocol)
{
	int s;

	s = up->index;
	up->cb.rip = raw_ip (protocol, (void (*) (void))rip_recv);
	up->cb.rip->user = s;
	return 0;
}

/* DLW Bind the user socket. */
ENTRY int
so_ip_conn (struct usock *up)
{
	if (up->name == NULLCHAR)
		autobind (up);
	return 0;
}

/* DLW Read a packet from ip socket UP.  Put the data in BPP.
 * FROM, if non NULL, is filled in with the source address.
 * FROMLEN is the size of FROM, and is set to the size of the source address
 *   after it's been read in.
 * Return the number of bytes recieved (I think its minus the header),
 * or -1 if an error occurs. */
ENTRY int
so_ip_recv (struct usock *up, struct mbuf **bpp, int len, char *from, int *fromlen)
{
	struct raw_ip *rip;
	struct sockaddr *remote;
	struct ip ip;
	int cnt;

	/* DLW Wait for a packet to come in, or the connection to die.
	 * If this is a "no block" socket, return.  I think the reason this is
	 * in a loop is that PWAIT can be woken up for various reasons, and
	 * this wants to keep ckecking until a packet arrives. */
	while ((rip = up->cb.rip) != NULLRIP && rip->rcvq == NULLBUF) {
		if (up->noblock) {
			errno = EWOULDBLOCK;
			return -1;
		} else if ((errno = pwait (up)) != 0) {
			return -1;
		}
	}
	if (rip == NULLRIP) {
		/* Connection went away */
		errno = ENOTCONN;
		return -1;
	}
	/* DLW Grab the packet. */
	*bpp = dequeue (&rip->rcvq);
	/* DLW Convert the header to the machine format. */
	ntohip (&ip, bpp);

	cnt = len_p (*bpp);
	/* DLW If FROM is non null, and is big enough, then fill in the
	 * FROM structure. */
	if (from != NULLCHAR && fromlen != (int *) NULL && *fromlen >= SOCKSIZE) {
		remote = (struct sockaddr *) from;
		*remote = ip.source;
		remote->sin_port = 0;
		*fromlen = SOCKSIZE;
	}
	return cnt;
}

/* DLW Send the packet PB out socket UP to destination TO.
 * The packet gets freed.
 * Return 0 for no error, or -1. */
ENTRY int
so_ip_send (struct usock *up, struct mbuf *bp, char *to)
{
	struct sockaddr *local, *remote;

	/* DLW If not already bound, autobind socket. */
	if (up->name == NULLCHAR)
		autobind (up);
	local = (struct sockaddr *) up->name;
	/* DLW If TO is defined, this is where the packet goes,
	 * else send it to the already defined peer, else it has nowhere
	 * to go. */
	if (to != NULLCHAR) {
		remote = (struct sockaddr *) to;
	} else if (up->peername != NULLCHAR) {
		remote = (struct sockaddr *) up->peername;
	} else {
		free_p (bp);
		errno = ENOTCONN;
		return -1;
	}
	/* DLW Send the packet. */
	ip_send (local, remote, (char) up->cb.rip->protocol, 0, 0, bp, 0, 0, 0);
	return 0;
}

/* DLW Return the number of packets in UP queue.
 * If RTX is 0, return the number of packets in the recieve queue.  If it's
 *   1 return the number of packets in the transmit que.  (Always zero.) */
ENTRY int
so_ip_qlen (struct usock *up, int rtx)
{
	int len;

	switch (rtx) {
	case 0:
		len = len_q (up->cb.rip->rcvq);
		break;
	case 1:
		len = 0;
		break;
	}
	return len;
}

/* DLW Shut down the socket. */
ENTRY int
so_ip_close (struct usock *up)
{
	del_ip (up->cb.rip);
	return 0;
}

/* DLW Check that NAME is a valid AF_INET socket, and that NAMELEN is of the
 * correct size.  Return 0 for success, -1 for error. */
ENTRY int
checkipaddr (char *name, int namelen)
{
	struct sockaddr *sock;

	sock = (struct sockaddr *) name;
	if (sock->sa_family != AF_INET || namelen != SOCKSIZE)
		return -1;
	return 0;
}

/* Raw IP receive upcall routine */
/* DLW Tell the socket user that a packet has arrived. */
LOCAL void
rip_recv (struct raw_ip *rp)
{
	psignal (itop (rp->user), 1);
	pwait (NULL);
}

/* Issue an automatic bind of a local address */
/* DLW Bind socket UP to a port. */
LOCAL void
autobind (struct usock *up)
{
	struct sockaddr local;
	int s;

	s = up->index;
	local.sa_family = AF_INET;
	local.sin_address = IPADDR_ANY;
	local.sin_port = Lport++;
	bind (s, (char *) &local, SOCKSIZE);
}
