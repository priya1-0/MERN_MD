
/* ************************************************************************* */
/*
 *	socket.c
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
 *	This file contains the application programming interface functions.  These
 *	are based loosely on the Berkely UNIX socket model.
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

extern const char *Socktypes[] = {
	"Not Used",
	"TCP",
	"UDP",
	"AX25 I",
	"AX25 UI",
	"Raw IP",
	"NETROM3",
	"NETROM",
	"Loc St",
	"Loc Dg",
	"SPX",
	"PEP",
};

extern const char *Sock_errlist[] = {
	"operation would block",
	"not connected",
	"socket type not supported",
	"address family not supported",
	"is connected",
	"operation not supported",
	"alarm",
	"abort",
	"interrupt",
	"connection refused",
	"message size",
	"address in use"
};

const char Badsocket[] = "Bad socket";
struct usock **Usock = ((struct usock**)0);		/* Socket entry array */

ENTRY void
socket_init (void)
{
	Usock = ((struct usock**)0);		/* Socket entry array */
}

/* Initialize user socket array */
ENTRY void
sockinit (void)
{
	if (Usock != (struct usock **) NULL)
		return;	/* Already initialized */
	Usock = (struct usock **) callocw (Nsock, sizeof (struct usock *));
}

/* Create a user socket, return socket index
 * The mapping to actual protocols is as follows:
 *
 *
 * ADDRESS FAMILY	Stream		Datagram	Raw		Seq. Packet
 *
 * AF_INET		TCP		UDP		IP
 * AF_AX25		I - frames	UI - frames
 * AF_NETROM						NET / ROM L3	NET / ROM L4
 * AF_LOCAL		stream loopback	packet loopback
 * AF_NOVELL				PEP				SPX
 */
ENTRY int
socket (int af, int type, int protocol)
{
	register struct usock *up;
	const struct socklink *sp;
	int s;

	for (s = 0;s < Nsock;s++)
		if (Usock[s] == NULLUSOCK)
			break;
	if (s == Nsock) {
		errno = EMFILE;
		return -1;
	}
	Usock[s] = up = (struct usock *) calloc (1, sizeof (struct usock));
	if (up == NULL) {
		errno = ENOMEM;
		return -1;
	}

	s += Nfiles;
	up->index = s;
	up->refcnt = 1;
	errno = 0;
	up->rdysock = -1;
	up->owner = Curproc;
	switch (af) {
	case AF_LOCAL:
		switch (type) {
		case SOCK_STREAM:
			up->type = TYPE_LOCAL_STREAM;
			break;
		case SOCK_DGRAM:
			up->type = TYPE_LOCAL_DGRAM;
			break;
		default:
			errno = ESOCKTNOSUPPORT;
			break;
		}
		break;
	case AF_INET:
		switch (type) {
		case SOCK_STREAM:
			up->type = TYPE_TCP;
			break;
		case SOCK_DGRAM:
			up->type = TYPE_UDP;
			break;
		case SOCK_RAW:
			up->type = TYPE_RAW;
			break;
		default:
			errno = ESOCKTNOSUPPORT;
			break;
		}
		break;
	default:
		errno = EAFNOSUPPORT;
		break;
	}
	/* Look for entry in protocol table */
	for (sp = Socklink;sp->type != -1;sp++) {
		if (up->type == sp->type)
			break;
	}
	up->sp = (struct socklink *) sp;
	if (sp->type == -1 || sp->socket == NULLFP
	  || (*sp->socket) (up, protocol) == -1) {
		errno = ESOCKTNOSUPPORT;
		return -1;
	}
	return s;
}

/* Attach a local address/port to a socket. If not issued before a connect
 * or listen, will be issued automatically
 */
ENTRY int
bind (int s, char *name, int namelen)
{
	register struct usock *up;
	struct socklink *sp;

	if ((up = itop (s)) == NULLUSOCK) {
		errno = EBADF;
		return -1;
	}
	if (name == NULLCHAR) {
		errno = EFAULT;
		return -1;
	}
	if (up->name != NULLCHAR) {
		/* Bind has already been issued */
		errno = EINVAL;
		return -1;
	}
	sp = up->sp;
	if (sp->check != NULLFP && (*sp->check) (name, namelen) == -1) {
		/* Incorrect length or family for chosen protocol */
		errno = EAFNOSUPPORT;
		return -1;
	}
	/* Stash name in an allocated block */
	up->namelen = namelen;
	up->name = (char *) mallocw (namelen);
	memcpy (up->name, name, namelen);

	/* a bind routine is optional - don't fail if it isn't present */
	if (sp->bind != NULLFP && (*sp->bind) (up) == -1) {
		errno = EOPNOTSUPP;
		return -1;
	}
	return 0;
}
/* Post a listen on a socket */
ENTRY int
listen (int s, int backlog)
{
	register struct usock *up;
	struct socklink *sp;

	if ((up = itop (s)) == NULLUSOCK) {
		errno = EBADF;
		return -1;
	}
	if (up->cb.p != NULLCHAR) {
		errno = EISCONN;
		return -1;
	}
	sp = up->sp;
	/* Fail if listen routine isn't present */
	if (sp->listen == NULLFP || (*sp->listen) (up, backlog) == -1) {
		errno = EOPNOTSUPP;
		return -1;
	}
	return 0;
}
/* Initiate active open. For datagram sockets, merely bind the remote address. */
ENTRY int
connect (int s, char *peername, int peernamelen)
{
	register struct usock *up;
	struct socklink *sp;

	if ((up = itop (s)) == NULLUSOCK) {
		errno = EBADF;
		return -1;
	}
	if (peername == NULLCHAR) {
		/* Connect must specify a remote address */
		errno = EFAULT;
		return -1;
	}
	sp = up->sp;
	/* Check name format, if checking routine is available */
	if (sp->check != NULLFP && (*sp->check) (peername, peernamelen) == -1) {
		errno = EAFNOSUPPORT;
		return -1;
	}
	if (up->peername != NULLCHAR)
		free (up->peername);
	up->peername = (char *) mallocw (peernamelen);
	memcpy (up->peername, peername, peernamelen);
	up->peernamelen = peernamelen;

	/* a connect routine is optional - don't fail if it isn't present */
	if (sp->connect != NULLFP && (*sp->connect) (up) == -1) {
		return -1;
	}
	return 0;
}
/* Wait for a connection. Valid only for connection-oriented sockets. */
ENTRY int
accept (int s, char *peername, int *peernamelen)
{
	int i;
	register struct usock *up;
	struct socklink *sp;

	if ((up = itop (s)) == NULLUSOCK) {
		errno = EBADF;
		return -1;
	}
	if (up->cb.p == NULLCHAR) {
		errno = EOPNOTSUPP;
		return -1;
	}
	sp = up->sp;
	/* Fail if accept flag isn't set */
	if (sp->accept == FALSE) {
		errno = EOPNOTSUPP;
		return -1;
	}
	/* Wait for the state-change upcall routine to signal us */
	while ((up->cb.p != NULLCHAR) && (up->rdysock == -1)) {
		if (up->noblock) {
			errno = EWOULDBLOCK;
			return -1;
		} else if ((errno = pwait (up)) != 0) {
			return -1;
		}
	}
	if (up->cb.p == NULLCHAR) {
		/* Blown away */
		errno = EBADF;
		return -1;
	}
	i = up->rdysock;
	up->rdysock = -1;

	up = itop (i);
	if (peername != NULLCHAR && peernamelen != NULL) {
		*peernamelen = min (up->peernamelen, *peernamelen);
		memcpy (peername, up->peername, *peernamelen);
	}
	return i;
}
/* Low-level receive routine. Passes mbuf back to user; more efficient than
 * higher - level functions recv () and recvfrom \ \(). Datagram sockets ignore
 * the len parameter.
 */
ENTRY int
recv_mbuf (int s, struct mbuf **bpp, int len, int flags, char *from, int *fromlen)
{
	register struct usock *up;
	struct socklink *sp;
	int ret;

	if ((up = itop (s)) == NULLUSOCK) {
		errno = EBADF;
		return -1;
	}
	sp = up->sp;
	/* Fail if recv routine isn't present */
	if (sp->recv == NULLFP) {
		errno = EOPNOTSUPP;
		return -1;
	}
	ret = (*sp->recv) (up, bpp, len, from, fromlen);
	return ret;
}
/* Low level send routine; user supplies mbuf for transmission. More
 * efficient than send () or sendto (), the higher level interfaces.
 * The "to" and "tolen" parameters are ignored on connection-oriented
 * sockets.
 *
 * In case of error, bp is freed so the caller doesn't have to worry about it.
 */
ENTRY int
send_mbuf (int s, struct mbuf *bp, int flags, char *to, int tolen)
{
	register struct usock *up;
	int cnt;
	struct socklink *sp;

	if ((up = itop (s)) == NULLUSOCK) {
		free_p (bp);
		errno = EBADF;
		return -1;
	}
	sp = up->sp;
	/* Fail if send routine isn't present (shouldn't happen) */
	if (sp->send == NULLFP) {
		free_p (bp);
		return -1;
	}
	/* If remote address is supplied, check it */
	if (to != NULLCHAR && (sp->check != NULLFP)
	 && (*sp->check) (to, tolen) == -1) {
		free_p (bp);
		errno = EAFNOSUPPORT;
		return -1;
	}
	/* The proto send routine is expected to free the buffer
	 * we pass it even if the send fails
	 */
	errno = EOPNOTSUPP;
	cnt = (*sp->send) (up, bp, to);
	return cnt;
}
/* Return local name passed in an earlier bind() call */
ENTRY int
getsockname (int s, char *name, int *namelen)
{
	register struct usock *up;

	if ((up = itop (s)) == NULLUSOCK) {
		errno = EBADF;
		return -1;
	}
	if (name == NULLCHAR || namelen == (int *) NULL) {
		errno = EFAULT;
		return -1;
	}
	if (up->name == NULLCHAR) {
		/* Not bound yet */
		*namelen = 0;
		return 0;
	}
	if (up->name != NULLCHAR) {
		*namelen = min (*namelen, up->namelen);
		memcpy (name, up->name, *namelen);
	}
	return 0;
}
/* Get remote name, returning result of earlier connect() call. */
ENTRY int
getpeername (int s, char *peername, int *peernamelen)
{
	register struct usock *up;

	if ((up = itop (s)) == NULLUSOCK) {
		errno = EBADF;
		return -1;
	}
	if (up->peername == NULLCHAR) {
		errno = ENOTCONN;
		return -1;
	}
	if (peername == NULLCHAR || peernamelen == (int *) NULL) {
		errno = EFAULT;
		return -1;
	}
	*peernamelen = min (*peernamelen, up->peernamelen);
	memcpy (peername, up->peername, *peernamelen);
	return 0;
}
/* Return length of protocol queue, either send or receive. */
ENTRY int
socklen (int s, int rtx)
{
	register struct usock *up;
	struct socklink *sp;
	int len = -1;

	if ((up = itop (s)) == NULLUSOCK) {
		errno = EBADF;
		return -1;
	}
	if (up->cb.p == NULLCHAR) {
		errno = ENOTCONN;
		return -1;
	}
	if (rtx < 0 || rtx > 1) {
		errno = EINVAL;
		return -1;
	}
	sp = up->sp;
	/* Fail if qlen routine isn't present */
	if (sp->qlen == NULLFP || (len = (*sp->qlen) (up, rtx)) == -1) {
		errno = EOPNOTSUPP;
		return -1;
	}
	return len;
}
/* Force retransmission. Valid only for connection-oriented sockets. */
ENTRY int
sockkick (int s)
{
	register struct usock *up;
	struct socklink *sp;

	if ((up = itop (s)) == NULLUSOCK) {
		errno = EBADF;
		return -1;
	}
	sp = up->sp;
	/* Fail if kick routine isn't present */
	if (sp->kick == NULLFP) {
		errno = EOPNOTSUPP;
		return -1;
	}
	if ((*sp->kick) (up) == -1) {
		return -1;
	}
	return 0;
}

/* Change owner of socket, return previous owner */
ENTRY struct proc *
sockowner (int s, struct proc *newowner)
{
	register struct usock *up;
	struct proc *pp;

	if ((up = itop (s)) == NULLUSOCK) {
		errno = EBADF;
		return NULLPROC;
	}
	pp = up->owner;
	if (newowner != NULLPROC)
		up->owner = newowner;
	return pp;
}

/* Close down a socket three ways. Type 0 means "no more receives"; this
 * replaces the incoming data upcall with a routine that discards further
 * data. Type 1 means "no more sends", and obviously corresponds to sending
 * a TCP FIN. Type 2 means "no more receives or sends". This I interpret
 * as "abort the connection".
 */
ENTRY int
shutdown (int s, int how)
{
	register struct usock *up;
	struct socklink *sp;

	if ((up = itop (s)) == NULLUSOCK) {
		errno = EBADF;
		return -1;
	}
	if (up->cb.p == NULLCHAR) {
		errno = ENOTCONN;
		return -1;
	}
	sp = up->sp;
	/* Just close the socket if special shutdown routine not present */
	if (sp->shut == NULLFP) {
		close_s (s);
	} else if ((*sp->shut) (up, how) == -1) {
		return -1;
	}
	alert_event (up, 0, EBADF);
	return 0;
}
/* Close a socket, freeing it for reuse. Try to do a graceful close on a
 * TCP socket, if possible
 */
ENTRY int
close_s (int s)
{
	register struct usock *up;
	struct socklink *sp;

	if ((up = itop (s)) == NULLUSOCK) {
		errno = EBADF;
		return -1;
	}
	if (--up->refcnt > 0) {
		return 0;	/* Others are still using it */
	}
	/* Call proto-specific close routine if there is one */
	if ((sp = up->sp) != NULL && sp->close != NULLFP)
		(*sp->close) (up);

	free (up->name);
	free (up->peername);

	alert_event (up, 0, EBADF);	/* Wake up anybody doing an accept() or recv() */
	Usock[up->index - Nfiles] = NULLUSOCK;
	free (up);
	return 0;
}
/* Increment reference count for specified socket */
ENTRY int
usesock (int s)
{
	struct usock *up;

	if ((up = itop (s)) == NULLUSOCK) {
		errno = EBADF;
		return -1;
	}
	up->refcnt++;
	return 0;
}
/* Blow away all sockets belonging to a certain process. Used by killproc(). */
ENTRY void
freesock (struct proc *pp)
{
	register struct usock *up;
	register int i;

	for (i = Nfiles;i < Nsock + Nfiles;i++) {
		up = itop (i);
		if (up != NULLUSOCK && up->type != TYPE_NOTUSED && up->owner == pp)
			shutdown (i, 2);
	}
}

/* Set Internet type-of-service to be used */
ENTRY int
settos (int s, char tos)
{
	struct usock *up;

	if ((up = itop (s)) == NULLUSOCK) {
		errno = EBADF;
		return -1;
	}
	up->tos = tos;
	return 0;
}

/* Return a pair of mutually connected sockets in sv[0] and sv[1] */
ENTRY int
socketpair (int af, int type, int protocol, int sv[])
{
	struct usock *up0, *up1;
	if (sv == NULL) {
		errno = EFAULT;
		return -1;
	}
	if (af != AF_LOCAL) {
		errno = EAFNOSUPPORT;
		return -1;
	}
	if (type != SOCK_STREAM && type != SOCK_DGRAM) {
		errno = ESOCKTNOSUPPORT;
		return -1;
	}
	if ((sv[0] = socket (af, type, protocol)) == -1)
		return -1;
	if ((sv[1] = socket (af, type, protocol)) == -1) {
		close_s (sv[0]);
		return -1;
	}
	up0 = itop (sv[0]);
	up1 = itop (sv[1]);
	up0->cb.local->peer = up1;
	up1->cb.local->peer = up0;
	return sv[1];
}
/* Return end-of-line convention for socket */
ENTRY char *
eolseq (int s)
{
	struct usock *up;

	if ((up = itop (s)) == NULLUSOCK) {
		errno = EBADF;
		return NULLCHAR;
	}
	return up->sp->eol;
}
