
/* ************************************************************************* */
/*
 *	tcpuser.c
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
 *	This file contains the user calls to TCP.
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

uint16 Tcp_window = DEF_WND;

ENTRY void
tcpuser_init (void)
{
	Tcp_window = DEF_WND;
}

ENTRY struct tcb *
open_tcp (struct sockaddr *local, struct sockaddr *remote, int mode, uint16 window, void (*r_upcall) (void), void (*t_upcall) (void), void (*s_upcall) (void), int tos, int user)
{
	struct connection conn;
	register struct tcb *tcb;

	if (local == NULLSA) {
		Net_error = INVALID;
		return NULLTCB;
	}
	conn.local = *local;
	if (remote != NULLSA) {
		conn.remote = *remote;
	} else {
		conn.remote.sa_family = AF_INET;
		conn.remote.sin_address = 0L;
		conn.remote.sin_port = 0;
	}
	if ((tcb = lookup_tcb (&conn)) == NULLTCB) {
		if ((tcb = create_tcb (&conn)) == NULLTCB) {
			Net_error = NO_MEM;
			return NULLTCB;
		}
	} else if (tcb->state != TCP_LISTEN) {
		Net_error = CON_EXISTS;
		return NULLTCB;
	}
	tcb->user = user;
	if (window != 0)
		tcb->window = tcb->rcv.wnd = window;
	else
		tcb->window = tcb->rcv.wnd = Tcp_window;
	tcb->snd.wnd = 1;	/* Allow space for sending a SYN */
	tcb->r_upcall = (void (*) (struct tcb *, int))r_upcall;
	tcb->t_upcall = (void (*) (struct tcb *, int))t_upcall;
	tcb->s_upcall = (void (*) (struct tcb *, int, int))s_upcall;
	tcb->tos = tos;
	switch (mode) {
	case TCP_SERVER:
		tcb->flags.clone = 1;
	case TCP_PASSIVE:	/* Note fall-thru */
		tcp_setstate (tcb, TCP_LISTEN);
		break;
	case TCP_ACTIVE:
		/* Send SYN, go into TCP_SYN_SENT state */
		tcb->flags.active = 1;
		send_syn (tcb);
		tcp_setstate (tcb, TCP_SYN_SENT);
		tcp_output (tcb);
		break;
	}
	return tcb;
}
/* User send routine */
ENTRY int
send_tcp (register struct tcb *tcb, struct mbuf *bp)
{
	uint16 cnt;

	if (tcb == NULLTCB || bp == NULLBUF) {
		free_p (bp);
		Net_error = INVALID;
		return -1;
	}
	cnt = len_p (bp);
	switch (tcb->state) {
	case TCP_CLOSED:
		free_p (bp);
		Net_error = NO_CONN;
		return -1;
	case TCP_LISTEN:
		if (tcb->conn.remote.sin_address == 0L && tcb->conn.remote.sin_port == 0) {
			/* Save data for later */
			append (&tcb->sndq, bp);
			tcb->sndcnt += cnt;
			break;
		}
		/* Change state from passive to active */
		tcb->flags.active = 1;
		send_syn (tcb);
		tcp_setstate(tcb,TCP_SYN_SENT);	/* Note fall-thru */
	case TCP_SYN_SENT:
	case TCP_SYN_RECEIVED:
	case TCP_ESTABLISHED:
	case TCP_CLOSE_WAIT:
		append (&tcb->sndq, bp);
		tcb->sndcnt += cnt;
		tcp_output (tcb);
		break;
	case TCP_FINWAIT1:
	case TCP_FINWAIT2:
	case TCP_CLOSING:
	case TCP_LAST_ACK:
	case TCP_TIME_WAIT:
		free_p (bp);
		Net_error = CON_CLOS;
		return -1;
	}
	return (int) cnt;
}
/* User receive routine */
ENTRY int
recv_tcp (register struct tcb *tcb, struct mbuf **bpp, uint16 cnt)
{

	if (tcb == NULLTCB || bpp == (struct mbuf **) NULL) {
		Net_error = INVALID;
		return -1;
	}
	if (tcb->rcvcnt == 0) {
		/* If there's nothing on the queue, our action depends on what state
		 * we're in (i.e., whether or not we're expecting any more data) .
		 * If no more data is expected, then simply return 0; this is
		 * interpreted as "end of file". Otherwise return -1.
		 */
		switch (tcb->state) {
		case TCP_LISTEN:
		case TCP_SYN_SENT:
		case TCP_SYN_RECEIVED:
		case TCP_ESTABLISHED:
		case TCP_FINWAIT1:
		case TCP_FINWAIT2:
			Net_error = WOULDBLK;
			return -1;
		case TCP_CLOSED:
		case TCP_CLOSE_WAIT:
		case TCP_CLOSING:
		case TCP_LAST_ACK:
		case TCP_TIME_WAIT:
			*bpp = NULLBUF;
			return 0;
		}
	}
	/* cnt == 0 means "I want it all" */
	if (cnt == 0)
		cnt = tcb->rcvcnt;
	/* See if the user can take all of it */
	if (tcb->rcvcnt <= cnt) {
		cnt = tcb->rcvcnt;
		*bpp = tcb->rcvq;
		tcb->rcvq = NULLBUF;
	} else {
		cnt = min (cnt, MXU_DEFAULT);
		*bpp = ambufw (cnt);
		pullup (&tcb->rcvq, (*bpp)->data, cnt);
		(*bpp)->cnt = cnt;
	}
	tcb->rcvcnt -= cnt;
	tcb->rcv.wnd += cnt;
	/* Do a window update if it was closed */
	if (cnt == tcb->rcv.wnd) {
		tcb->flags.force = 1;
		tcp_output (tcb);
	}
	return (int) cnt;
}
/* This really means "I have no more data to send". It only closes the
 * connection in one direction, and we can continue to receive data
 * indefinitely.
 */
ENTRY int
close_tcp (register struct tcb *tcb)
{

	if (tcb == NULLTCB) {
		Net_error = INVALID;
		return -1;
	}
	switch (tcb->state) {
	case TCP_CLOSED:
		return 0;	/* Unlikely */
	case TCP_LISTEN:
	case TCP_SYN_SENT:
		close_self (tcb, NORMAL);
		return 0;
	case TCP_SYN_RECEIVED:
	case TCP_ESTABLISHED:
		tcb->sndcnt++;
		tcb->snd.nxt++;
		tcp_setstate (tcb, TCP_FINWAIT1);
		tcp_output (tcb);
		return 0;
	case TCP_CLOSE_WAIT:
		tcb->sndcnt++;
		tcb->snd.nxt++;
		tcp_setstate (tcb, TCP_LAST_ACK);
		tcp_output (tcb);
		return 0;
	case TCP_FINWAIT1:
	case TCP_FINWAIT2:
	case TCP_CLOSING:
	case TCP_LAST_ACK:
	case TCP_TIME_WAIT:
		Net_error = CON_CLOS;
		return -1;
	}
	return -1;	/* "Can't happen" */
}
/* Delete TCB, free resources. The user is not notified, even if the TCB is
 * not in the TCP_CLOSED state. This function should normally be called by the
 * user only in response to a state change upcall to TCP_CLOSED state.
 */
ENTRY int
del_tcp (struct tcb *conn)
{
	register struct tcb *tcb;
	struct tcb *tcblast = NULLTCB;
	struct reseq *rp, *rp1;

	/* Remove from list */
	for (tcb = Tcbs;tcb != NULLTCB;tcblast = tcb, tcb = tcb->next)
		if (tcb == conn)
			break;
	if (tcb == NULLTCB) {
		Net_error = INVALID;
		return -1;	/* conn was NULL, or not on list */
	}
	if (tcblast != NULLTCB)
		tcblast->next = tcb->next;
	else
		Tcbs = tcb->next;	/* was first on list */

	stop_timer (&tcb->timer);
	for (rp = tcb->reseq;rp != NULLRESEQ;rp = rp1) {
		rp1 = rp->next;
		free_p (rp->bp);
		free ((char *) rp);
	}
	tcb->reseq = NULLRESEQ;
	free_p (tcb->rcvq);
	free_p (tcb->sndq);
	free ((char *) tcb);
	return 0;
}
/* Return 1 if arg is a valid TCB, 0 otherwise */
ENTRY int
tcbval (struct tcb *tcb)
{
	register struct tcb *tcb1;

	if (tcb == NULLTCB)
		return 0;	/* Null pointer can't be valid */
	for (tcb1 = Tcbs;tcb1 != NULLTCB;tcb1 = tcb1->next) {
		if (tcb1 == tcb)
			return 1;
	}
	return 0;
}
/* Kick a particular TCP connection */
ENTRY int
kick_tcp (register struct tcb *tcb)
{
	if (!tcbval (tcb))
		return -1;
	tcb->flags.force = 1;	/* Send ACK even if no data */
	tcp_timeout (tcb);
	return 0;
}
/* Kick all TCP connections to specified address; return number kicked */
ENTRY int
kick (sint31 addr)
{
	register struct tcb *tcb;
	int cnt = 0;

	for (tcb = Tcbs;tcb != NULLTCB;tcb = tcb->next) {
		if (tcb->conn.remote.sin_address == addr) {
			kick_tcp (tcb);
			cnt++;
		}
	}
	return cnt;
}
/* Clear all TCP connections */
ENTRY void
reset_tcp_all (void)
{
	register struct tcb *tcb;

	for (tcb = Tcbs;tcb != NULLTCB;tcb = tcb->next)
		reset_tcp (tcb);

	pwait(NULL);	/* Let the RSTs go forth */
}
ENTRY void
reset_tcp (register struct tcb *tcb)
{
	struct tcp fakeseg;
	struct ip fakeip;

	if (tcb == NULLTCB)
		return;
	if (tcb->state != TCP_LISTEN) {
		/* Compose a fake segment with just enough info to generate the
		 * correct RST reply
		 */
		memset ((char *) &fakeseg, 0, sizeof (fakeseg));
		memset ((char *) &fakeip, 0, sizeof (fakeip));
		fakeseg.dest = tcb->conn.local.sin_port;
		fakeseg.source = tcb->conn.remote.sin_port;
		fakeseg.flags.ack = 1;
		/* Here we try to pick a sequence number with the greatest likelihood
		 * of being in his receive window.
		 */
		fakeseg.ack = tcb->snd.nxt + tcb->snd.wnd -1;
		fakeip.dest = tcb->conn.local;
		fakeip.source = tcb->conn.remote;
		fakeip.tos = tcb->tos;
		reset (&fakeip, &fakeseg);
	}
	close_self (tcb, RESET);
}
#ifdef	notused
/* Return character string corresponding to a TCP well-known port, or
 * the decimal number if unknown.
 */
ENTRY char *
tcp_port (uint16 n)
{
	static char buf[32];

	switch (n) {
	case IPPORT_ECHO:
		return "echo";
	case IPPORT_DISCARD:
		return "discard";
	case IPPORT_FTPD:
		return "ftp_data";
	case IPPORT_FTP:
		return "ftp";
	case IPPORT_TELNET:
		return "telnet";
	case IPPORT_SMTP:
		return "smtp";
	case IPPORT_POP:
		return "pop";
	default:
		sprintf(buf,"%u",n);
		return buf;
	}
}
#endif /* notused */
