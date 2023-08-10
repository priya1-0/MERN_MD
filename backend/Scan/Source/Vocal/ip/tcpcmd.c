
/* ************************************************************************* */
/*
 *	tcpcmd.c
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
 *	This file contains the TCP control and status functions.
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

extern int Tcp_trace;
extern sint31 Tcp_irtt;
extern uint16 Tcp_mss;
extern uint16 Tcp_window;
extern int Tcp_syndata;

/* Convert a string to a TCB address and verify it.
 */
LOCAL int
atotcb_err (char *cp, struct tcb **tcbpp)
{
	uint32 num;

	if (atoi32uh_err (cp, &num))
		return 1;
	*tcbpp = (struct tcb *) ltop (num);
	if (!tcbval (*tcbpp)) {
		printf ("Not a valid TCB address: %s\n", cp);
		return 1;
	}
	return 0;
}

LOCAL int
dotcptrace (int argc, char *argv[], void *p)
{
	return chg_bool (&Tcp_trace, "TCP state tracing", argc, argv);
}

/* Eliminate a TCP connection */
LOCAL int
dotcpreset (int argc, char *argv[], void *p)
{
	struct tcb *tcb;

	if (atotcb_err (argv[1], &tcb))
		return 1;
	reset_tcp (tcb);
	return 0;
}

/* Set initial round trip time for new connections */
LOCAL int
dotcpirtt (int argc, char *argv[], void *p)
{
	struct tcp_rtt *tp;
	int heading = 1;

	if (chg_int32s (&Tcp_irtt,"TCP default irtt (milliseconds)",argc,argv))
		return 1;

	if (argc < 2) {
		for (tp = &Tcp_rtt[0];tp < &Tcp_rtt[RTTCACHE];tp++) {
			if (tp->addr.sin_address != 0) {
				if (heading) {
					printf ("\nAddress                srtt        mdev\n");
					heading = 0;
				}
				printf("%15s %-10lu %-10lu\n",
					snhtoa (&tp->addr), tp->srtt, tp->mdev);
			}
		}
	}
	return 0;
}

/* Set smoothed round trip time for specified TCB */
LOCAL int
dorcprtt (int argc, char *argv[], void *p)
{
	struct tcb *tcb;

	if (atotcb_err (argv[1], &tcb))
		return 1;
	return (atoi32s_err (argv[2], &tcb->srtt));
}

/* Force a retransmission */
LOCAL int
dotcpkick (int argc, char *argv[], void *p)
{
	struct tcb *tcb;

	if (atotcb_err (argv[1], &tcb))
		return 1;
	if (kick_tcp (tcb) == -1) {
		return 1;
	}
	return 0;
}

/* Set default maximum segment size */
LOCAL int
dotcpmss (int argc, char *argv[], void *p)
{
	return chg_int16u (&Tcp_mss,"TCP MSS (maximum segment size)",argc,argv);
}

/* Set default window size */
LOCAL int
dotcpwind (int argc, char *argv[], void *p)
{
	return chg_int16u (&Tcp_window,"TCP window",argc,argv);
}

LOCAL int
dotcpsyndata (int argc, char *argv[], void *p)
{
	return chg_bool (&Tcp_syndata, "TCP syn+data piggybacking", argc, argv);
}

/* Display MIB parameters */
LOCAL int
dotcpmib (int argc, char *argv[], void *p)
{
	struct tcb *tcb;

	print_mib (Tcp_mib, NUMTCPMIB);

	if (argc > 1) {
		if (atotcb_err (argv[1], &tcb))
			return 1;
		printf ("\nTCB:\t\t\t%14lx\n", ptol (tcb));
		printf ("( 1) tcpConnState\t%11s(%u)\t( 2) tcpConnLocalAddress %13s\n", Tcpstates[(int)tcb->state], tcb->state, snhtoa (&tcb->conn.local));
		printf ("( 3) tcpConnLocalPort\t%14u\t( 4) tcpConnRemAddress\t %13s\n", tcb->conn.local.sin_port, snhtoa (&tcb->conn.remote));
		printf ("( 5) tcpConnRemPort\t%14u\n", tcb->conn.remote.sin_port);
	}
	return 0;
}

/* Dump TCP stats and summary of all TCBs
 *     &TCB Rcv - Q Snd - Q  Local socket           Remote socket          State
 *     1234     0     0  xxx.xxx.xxx.xxx:xxxxx  xxx.xxx.xxx.xxx:xxxxx  Established
 */
LOCAL int
tcb_summary (void)
{
	register struct tcb *tcb;

	printf("TCB      Rcv-Q Snd-Q  Local socket           Remote socket          State\n");
	for (tcb = Tcbs;tcb != NULLTCB;tcb = tcb->next) {
		printf("%8lx%6u%6u  %-23s",ptol(tcb),tcb->rcvcnt,tcb->sndcnt,
			snhptoa (&tcb->conn.local));
		printf("%-23s%-s%s\n",snhptoa (&tcb->conn.remote),
			Tcpstates[(int) tcb->state],
			(((tcb->state == TCP_LISTEN) && (tcb->flags.clone)) ? " (S)" : ""));
	}
	return 0;
}

/* Dump a TCP control block in detail */
ENTRY void
tcb_detail (struct tcb *tcb)
{
	sint31 sent, recvd;

	if (tcb == NULLTCB)
		return;
	/* Compute total data sent and received; take out SYN and FIN */
	sent = tcb->snd.una - tcb->iss;	/* Acknowledged data only */
	recvd = tcb->rcv.nxt - tcb->irs;
	switch (tcb->state) {
	case TCP_LISTEN:
	case TCP_SYN_SENT:	/* Nothing received or acked yet */
		sent = recvd = 0;
		break;
	case TCP_SYN_RECEIVED:
		recvd--;	/* Got SYN, no data acked yet */
		sent = 0;
		break;
	case TCP_ESTABLISHED:	/* Got and sent SYN */
	case TCP_FINWAIT1:	/* FIN not acked yet */
		sent--;
		recvd--;
		break;
	case TCP_FINWAIT2:	/* Our SYN and FIN both acked */
		sent -= 2;
		recvd--;
		break;
	case TCP_CLOSE_WAIT:	/* Got SYN and FIN, our FIN not yet acked */
	case TCP_CLOSING:
	case TCP_LAST_ACK:
		sent--;
		recvd -= 2;
		break;
	case TCP_TIME_WAIT:	/* Sent and received SYN/FIN, all acked */
		sent -= 2;
		recvd -= 2;
		break;
	}
	printf("Local:  %45s   State: %-s%s\n", snhptoa (&tcb->conn.local), Tcpstates[(int)tcb->state], (((tcb->state == TCP_LISTEN) && (tcb->flags.clone)) ? " (S)" : ""));
	printf("Remote: %45s\n", snhptoa (&tcb->conn.remote));
	printf("\n      Init Seq    Unack     Next Resent CWind Thrsh  Wind  MSS Queue      Total\n");
	printf("Send:%9lx%9lx%9lx%7lu%6u%6u%6u%5u%6u%11lu\n",
		(long) tcb->iss, (long) tcb->snd.una, (long) tcb->snd.nxt, (long) tcb->resent, tcb->cwind,
		tcb->ssthresh, tcb->snd.wnd, tcb->mss, tcb->sndcnt, (long) sent);

	printf("Recv:%9lx         %9lx%7lu            %6u     %6u%11lu\n",
		(unsigned long) tcb->irs, (unsigned long) tcb->rcv.nxt, (long) tcb->rerecv, tcb->rcv.wnd,
		(long) tcb->rcvcnt, recvd);

	if (tcb->reseq != (struct reseq *) NULL) {
		register struct reseq *rp;

		printf("\nReassembly Queue Seq  Bytes\n");
		for (rp = tcb->reseq;rp != (struct reseq *) NULL; rp = rp->next) {
			printf("%20lx  %5u\n", (long) rp->seg.seq, rp->length);
		}
	}
	printf ("\n");
	if (tcb->backoff > 0)
		printf("Backoff %u ",tcb->backoff);
	if (tcb->flags.retran)
		printf("Retrying ");
	switch (tcb->timer.state) {
	case TIMER_STOP:
		printf("Timer stopped ");
		break;
	case TIMER_RUN:
		printf("Timer running (%ld/%ld ms) ",
		 (long) read_timer (&tcb->timer),
		 (long) dur_timer (&tcb->timer));
		break;
	case TIMER_EXPIRE:
		printf("Timer expired ");
	}
	printf("SRTT %ld ms Mean dev %ld ms\n",(long) tcb->srtt, (long) tcb->mdev);
}

/* Display status of TCBs */
dotcpshow (int argc, char *argv[], void *p)
{
	struct tcb *tcb;

	if (argc < 2) {
		tcb_summary ();
	} else {
		if (atotcb_err (argv[1], &tcb))
			return 1;
		tcb_detail (tcb);
	}
	return 0;
}

/* TCP subcommand table */
static const struct cmds Tcpcmds[] = {
	{"irtt",		dotcpirtt,			0,	0,	"[msecs]"},
	{"kick",		dotcpkick,			0,	2,	"<tcb>"},
	{"mib",			dotcpmib,			0,	0,	"[tcb]"},
	{"mss",			dotcpmss,			0,	0,	"[bytes]"},
	{"reset",		dotcpreset,			0,	2,	"<tcb>"},
	{"show",		dotcpshow,			0,	0,	"[tcb]"},
	{"trace",		dotcptrace,			0,	0,	"[on|off]"},
	{"window",		dotcpwind,			0,	0,	"[bytes]"},
	{NULLCHAR},
};

ENTRY int
dotcp (int argc, char *argv[], void *p)
{
	return subcmd (Tcpcmds, argc, argv, p);
}
