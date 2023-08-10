
/* ************************************************************************* */
/*
 *	tcpsubr.c
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
 *	This file contains the low level TCP routines including: a) control block management
 *  b) sequence number logical operations, c) state transitions, d) RTT cacheing and
 *	e) garbage collection functions.
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

/* TCP connection states */
char *Tcpstates[] = {
	"",
	"Closed",
	"Listen",
	"SYN sent",
	"SYN received",
	"Established",
	"FIN wait 1",
	"FIN wait 2",
	"Close wait",
	"Last ACK",
	"Closing",
	"Time wait"
};

/* TCP closing reasons */
char *Tcpreasons[] = {
	"Normal",
	"Reset/Refused",
	"Timeout",	/* Not actually used */
	"ICMP"		/* Not actually used */
};
struct tcb *Tcbs = NULLTCB;	/* Head of control block list */
uint16 Tcp_mss = DEF_MSS;	/* Maximum segment size to be sent with SYN */
sint31 Tcp_irtt = DEF_RTT;	/* Initial guess at round trip time */
int Tcp_trace = 0;			/* State change tracing flag */
int Tcp_syndata = FALSE;
struct tcp_rtt Tcp_rtt[RTTCACHE];	/* Initialized at run-time in network_init */

struct mib_entry Tcp_mib[] = {
	{NULLCHAR,			{0}},
	{"tcpRtoAlgorithm",	{4}},	/* Van Jacobsen's algorithm */
	{"tcpRtoMin",		{0}},	/* No lower bound */
	{"tcpRtoMax",		{MAX_SINT31}},	/* No upper bound */
	{"tcpMaxConn",		{-1L}},	/* No limit */
	{"tcpActiveOpens",	{0}},
	{"tcpPassiveOpens",	{0}},
	{"tcpAttemptFails",	{0}},
	{"tcpEstabResets",	{0}},
	{"tcpCurrEstab",	{0}},
	{"tcpInSegs",		{0}},
	{"tcpOutSegs",		{0}},
	{"tcpRetransSegs",	{0}},
	{NULLCHAR,			{0}},	/* Connection state goes here */
	{"tcpInErrs",		{0}},
	{"tcpOutRsts",		{0}},
};

ENTRY void
tcpsubr_init (void)
{
	int i;

	Tcbs = NULLTCB;	/* Head of control block list */
	Tcp_mss = DEF_MSS;	/* Maximum segment size to be sent with SYN */
	Tcp_irtt = DEF_RTT;	/* Initial guess at round trip time */
	Tcp_trace = 0;			/* State change tracing flag */
	Tcp_syndata = FALSE;
	for (i = 0; i < RTTCACHE; i++) {
		Tcp_rtt[i].addr.sa_family = 0L;
		Tcp_rtt[i].addr.sin_address = 0L;
		Tcp_rtt[i].srtt = 0;
		Tcp_rtt[i].mdev = 0;
	}

	Tcp_mib[0].value.integer = 0;
	tcpRtoAlgorithm = 4;
	tcpRtoMin = 0;
	tcpRtoMax = MAX_SINT31;
	tcpMaxConn = -1L;
	tcpActiveOpens = 0;
	tcpPassiveOpens = 0;
	tcpAttemptFails = 0;
	tcpEstabResets = 0;
	tcpCurrEstab = 0;
	tcpInSegs = 0;
	tcpOutSegs = 0;
	tcpRetransSegs = 0;
	Tcp_mib[13].value.integer = 0;
	tcpInErrs = 0;
	tcpOutRsts = 0;
}

/* Look up TCP connection
 * Return TCB pointer or NULLTCB if nonexistant.
 * Also move the entry to the top of the list to speed future searches.
 */
ENTRY struct tcb *
lookup_tcb (register struct connection *conn)
{
	register struct tcb *tcb;
	struct tcb *tcblast = NULLTCB;

	for (tcb = Tcbs;tcb != NULLTCB;tcblast = tcb, tcb = tcb->next) {
		/* Yet another structure compatibility hack */
		if (af_connectionsame (&conn->remote, &tcb->conn.remote)
		 && af_connectionsame (&conn->local, &tcb->conn.local)) {
			if (tcblast != NULLTCB) {
				/* Move to top of list */
				tcblast->next = tcb->next;
				tcb->next = Tcbs;
				Tcbs = tcb;
			}
			return tcb;
		}

	}
	return NULLTCB;
}

/* Create a TCB, return pointer. Return pointer if TCB already exists. */
ENTRY struct tcb *
create_tcb (struct connection *conn)
{
	register struct tcb *tcb;
	struct tcp_rtt *tp;

	if ((tcb = lookup_tcb (conn)) != NULLTCB)
		return tcb;
	tcb = (struct tcb *) callocw (1, sizeof (struct tcb));
	ASSIGN (tcb->conn, *conn);

	tcb->state = TCP_CLOSED;
	tcb->cwind = tcb->mss = Tcp_mss;
	tcb->ssthresh = 65535;
	if ((tp = rtt_get (&(tcb->conn.remote))) != NULLRTT) {
		tcb->srtt = tp->srtt;
		tcb->mdev = tp->mdev;
	} else {
		tcb->srtt = Tcp_irtt;	/* mdev = 0 */
	}
	/* Initialize timer intervals */
	set_timer (&tcb->timer, tcb->srtt);
	tcb->timer.func = tcp_timeout;
	tcb->timer.arg = tcb;

	tcb->next = Tcbs;
	Tcbs = tcb;
	return tcb;
}

/* Close our TCB */
ENTRY void
close_self (register struct tcb *tcb, int reason)
{
	struct reseq *rp1;
	register struct reseq *rp;

	if (tcb == NULLTCB)
		return;

	stop_timer (&tcb->timer);
	tcb->reason = reason;

	/* Flush reassembly queue; nothing more can arrive */
	for (rp = tcb->reseq;rp != NULLRESEQ;rp = rp1) {
		rp1 = rp->next;
		free_p (rp->bp);
		free ((char *) rp);
	}
	tcb->reseq = NULLRESEQ;
	tcp_setstate (tcb, TCP_CLOSED);
}

/* Sequence number comparisons
 * Return true if x is between low and high inclusive,
 * false otherwise
 */
ENTRY int
seq_within (sint31 x, sint31 low, sint31 high)
{
	if (low <= high) {
		if (low <= x && x <= high)
			return 1;
	} else {
		if (low >= x && x >= high)
			return 1;
	}
	return 0;
}

ENTRY int
seq_lt (sint31 x, sint31 y)
{
	return (sint31) (x - y) < 0;
}

ENTRY int
seq_gt (sint31 x, sint31 y)
{
	return (sint31) (x - y) > 0;
}

ENTRY int
seq_ge (sint31 x, sint31 y)
{
	return (sint31) (x - y) >= 0;
}

ENTRY void
tcp_setstate (register struct tcb *tcb, register int newstate)
{
	register char oldstate;

	oldstate = tcb->state;
	tcb->state = newstate;
	if (Tcp_trace)
		printf("TCB %lx %s -> %s\n",(long) ptol(tcb),
		 Tcpstates[(int) oldstate], Tcpstates[newstate]);

	if ((oldstate == TCP_SYN_SENT) && (newstate != TCP_ESTABLISHED)) {
		tcb_detail (tcb);
	}

	/* Update MIB variables */
	switch (oldstate) {
	case TCP_CLOSED:
		if (newstate == TCP_SYN_SENT)
			tcpActiveOpens++;
		break;
	case TCP_LISTEN:
		if (newstate == TCP_SYN_RECEIVED)
			tcpPassiveOpens++;
		break;
	case TCP_SYN_SENT:
		if (newstate == TCP_CLOSED)
			tcpAttemptFails++;
		break;
	case TCP_SYN_RECEIVED:
		switch (newstate) {
		case TCP_CLOSED:
		case TCP_LISTEN:
			tcpAttemptFails++;
			break;
		}
		break;
	case TCP_ESTABLISHED:
	case TCP_CLOSE_WAIT:
		switch (newstate) {
		case TCP_CLOSED:
		case TCP_LISTEN:
			tcpEstabResets++;
			break;
		}
		tcpCurrEstab--;
		break;
	}
	if (newstate == TCP_ESTABLISHED || newstate == TCP_CLOSE_WAIT)
		tcpCurrEstab++;

	if (tcb->s_upcall)
		(*tcb->s_upcall) (tcb, oldstate, newstate);

	switch (newstate) {
	case TCP_SYN_RECEIVED:	/***/
	case TCP_ESTABLISHED:
		/* Notify the user that he can begin sending data */
		if (tcb->t_upcall)
			(*tcb->t_upcall) (tcb, tcb->window - tcb->sndcnt);
		break;
	}
}
/* Round trip timing cache routines.
 * These functions implement a very simple system for keeping track of
 * network performance for future use in new connections.
 * The emphasis here is on speed of update (rather than optimum cache hit
 * ratio) since rtt_add is called every time a TCP connection updates
 * its round trip estimate.
 */
ENTRY void
rtt_add (struct sockaddr *addr, sint31 rtt)
{
	register struct tcp_rtt *tp;
	sint31 abserr;

	tp = &Tcp_rtt[(uint16) addr->sin_address % RTTCACHE];
	if (!(inet_hostsame (&tp->addr, addr))) {
		/* New entry */
		tp->addr = *addr;
		tp->srtt = rtt;
		tp->mdev = 0;
	} else {
		/* Run our own SRTT and MDEV integrators, with rounding */
		abserr = (rtt > tp->srtt) ? rtt - tp->srtt : tp->srtt - rtt;
		tp->srtt = ((AGAIN -1) *tp->srtt + rtt + (AGAIN / 2)) >> LAGAIN;
		tp->mdev = ((DGAIN -1) *tp->mdev + abserr + (DGAIN / 2)) >> LDGAIN;
	}
}

ENTRY struct tcp_rtt *
rtt_get (struct sockaddr *addr)
{
	register struct tcp_rtt *tp;

	tp = &Tcp_rtt[(uint16) addr->sin_address % RTTCACHE];
	if (!(inet_hostsame (&tp->addr, addr)))
		return NULLRTT;
	return tp;
}

/* TCP garbage collection - called by storage allocator when free space
 * runs low. The send and receive queues are crunched. If the situation
 * is red, the resequencing queue is discarded; otherwise it is
 * also crunched.
 */
ENTRY void
tcp_garbage (int red)
{
	register struct tcb *tcb;
	struct reseq *rp, *rp1;

	for (tcb = Tcbs;tcb != NULLTCB;tcb = tcb->next) {
		mbuf_crunch (&tcb->rcvq);
		mbuf_crunch (&tcb->sndq);
		for (rp = tcb->reseq;rp != NULLRESEQ;rp = rp1) {
			rp1 = rp->next;
			if (red) {
				free_p (rp->bp);
				free ((char *) rp);
			} else {
				mbuf_crunch (&rp->bp);
			}
		}
		if (red)
			tcb->reseq = NULLRESEQ;
	}
}
