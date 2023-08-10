
/* ************************************************************************* */
/*
 *	tcp.h
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

#ifndef _IP_TCP_H
#define _IP_TCP_H

/* TCP implementation. Follows RFC 793 as closely as possible */

/* ************************************************************************* */

#define TCP_FLAG__FIN	0x0001		/* No more data from sender */
#define TCP_FLAG__SYN	0x0002		/* Synchronize sequence numbers */
#define TCP_FLAG__RST	0x0004		/* Reset the connection */
#define TCP_FLAG__PSH	0x0008		/* Push function */
#define TCP_FLAG__ACK	0x0010		/* Acknowledgment field significant */
#define TCP_FLAG__URG	0x0020		/* Urgent Pointer field significant */

/* Congestion control from RFC 3168 */
#define TCP_FLAG__ECE	0x0040		/* ECN-Echo (Explicit congestion notification echo) */
#define TCP_FLAG__CWR	0x0080		/* Congestion window reduced */

/* ************************************************************************* */

#define	DEF_MSS	512	/* Default maximum segment size */
#define	DEF_WND	2048	/* Default receiver window */
#define	RTTCACHE 16	/* # of TCP round-trip-time cache entries */
#define	DEF_RTT	5000	/* Initial guess at round trip time (5 sec) */
#define	MSL2	30	/* Guess at two maximum-segment lifetimes */
#define	MIN_RTO	500L	/* Minimum timeout, milliseconds */
#define	TCP_HDR_PAD	70	/* mbuf size to preallocate for headers */

#define	geniss()	((sint31)msclock() << 12) /* Increment clock at 4 MB/sec */

/* Number of consecutive duplicate acks to trigger fast recovery */
#define	TCPDUPACKS	3

/* Round trip timing parameters */
#define	AGAIN	8	/* Average RTT gain = 1/8 */
#define	LAGAIN	3	/* Log2(AGAIN) */
#define	DGAIN	4	/* Mean deviation gain = 1/4 */
#define	LDGAIN	2	/* log2(DGAIN) */

/* TCP segment header -- internal representation
 * Note that this structure is NOT the actual header as it appears on the
 * network (in particular, the offset field is missing) .
 * All that knowledge is in the functions ntohtcp () and htontcp () in tcpsubr.c
 */
#define TCPLEN		20	/* Minimum Header length, bytes */
#define	TCP_MAXOPT	40	/* Largest option field, bytes */
struct tcp {
	uint16 source;	/* Source port */
	uint16 dest;	/* Destination port */
	sint31 seq;	/* Sequence number */
	sint31 ack;	/* Acknowledgment number */
	uint16 wnd;			/* Receiver flow control window */
	uint16 checksum;			/* Checksum */
	uint16 up;			/* Urgent pointer */
	uint16 mss;			/* Optional max seg size */
	struct {
		char cwr;
		char ece;
		char urg;
		char ack;
		char psh;
		char rst;
		char syn;
		char fin;
	} flags;
	char optlen;			/* Length of options field, bytes */
	char options[TCP_MAXOPT];	/* Options field */
};
/* TCP options */
#define	EOL_KIND	0
#define	NOOP_KIND	1
#define	MSS_KIND	2
#define	MSS_LENGTH	4

/* Resequencing queue entry */
struct reseq {
	struct reseq *next;	/* Linked-list pointer */
	struct tcp seg;		/* TCP header */
	struct mbuf *bp;	/* data */
	uint16 length;		/* data length */
	char tos;		/* Type of service */
};
#define	NULLRESEQ	(struct reseq *)0

/* TCP connection control block */
struct tcb {
	struct tcb *next;	/* Linked list pointer */

	struct connection conn;

	char state;	/* Connection state */

/* These numbers match those defined in the MIB for TCP connection state */
#define	TCP_CLOSED		1
#define	TCP_LISTEN		2
#define	TCP_SYN_SENT		3
#define	TCP_SYN_RECEIVED	4
#define	TCP_ESTABLISHED		5
#define	TCP_FINWAIT1		6
#define	TCP_FINWAIT2		7
#define	TCP_CLOSE_WAIT		8
#define	TCP_LAST_ACK		9
#define	TCP_CLOSING		10
#define	TCP_TIME_WAIT		11

	char reason;		/* Reason for closing */
#define	NORMAL		0	/* Normal close */
#define	RESET		1	/* Reset by other end */
#define	TIMEOUT		2	/* Excessive retransmissions */
#define	NETWORK		3	/* Network problem (ICMP message) */

/* If reason == NETWORK, the ICMP type and code values are stored here */
	char type;
	char code;

	/* Send sequence variables */
	struct {
		sint31 una;	/* First unacknowledged sequence number */
		sint31 nxt;	/* Next sequence num to be sent for the first time */
		sint31 ptr;	/* Working transmission pointer */
		sint31 wl1;	/* Sequence number used for last window update */
		sint31 wl2;	/* Ack number used for last window update */
		uint16 wnd;	/* Other end's offered receive window */
		uint16 up;	/* Send urgent pointer */
	} snd;
	sint31 iss;		/* Initial send sequence number */
	sint31 resent;		/* Count of bytes retransmitted */
	uint16 cwind;		/* Congestion window */
	uint16 ssthresh;		/* Slow-start threshold */
	int dupacks;		/* Count of duplicate (do-nothing) ACKs */

	/* Receive sequence variables */
	struct {
		sint31 nxt;	/* Incoming sequence number expected next */
		uint16 wnd;	/* Our offered receive window */
		uint16 up;	/* Receive urgent pointer */
	} rcv;
	sint31 irs;		/* Initial receive sequence number */
	sint31 rerecv;		/* Count of duplicate bytes received */
	uint16 mss;		/* Maximum segment size */

	uint16 window;		/* Receiver window and send queue limit */
	uint16 limit;		/* Send queue limit */

	void (*r_upcall) (struct tcb *tcb, int cnt);
		/* Call when "significant" amount of data arrives */
	void (*t_upcall) (struct tcb *tcb, int cnt);
		/* Call when ok to send more data */
	void (*s_upcall) (struct tcb *tcb, int old, int new_state);
		/* Call when connection state changes */
	struct {		/* Control flags */
		char force;	/* We owe the other end an ACK or window update */
		char clone;	/* Server-type TCB, cloned on incoming SYN */
		char retran;	/* A retransmission has occurred */
		char active;	/* TCB created with an active open */
		char synack;	/* Our SYN has been acked */
		char rtt_run;	/* We're timing a segment */
		char congest;	/* Copy of last IP congest bit received */
	} flags;
	char tos;		/* Type of service (for IP) */
	int backoff;		/* Backoff interval */

	struct mbuf *rcvq;	/* Receive queue */
	struct mbuf *sndq;	/* Send queue */
	uint16 rcvcnt;		/* Count of items on rcvq */
	uint16 sndcnt;		/* Number of unacknowledged sequence numbers on
				 * sndq. NB: includes SYN and FIN, which don't
				 * actually appear on sndq !
				 */

	struct reseq *reseq;	/* Out-of-order segment queue */
	struct timer timer;	/* Retransmission timer */
	sint31 rtt_time;		/* Stored clock values for RTT */
	sint31 rttseq;		/* Sequence number being timed */
	sint31 srtt;		/* Smoothed round trip time, milliseconds */
	sint31 mdev;		/* Mean deviation, milliseconds */
	sint31 lastactive;	/* Clock time when xmtr last active */

	int user;		/* User parameter (e.g., for mapping to an
				 * application control block
				 */
};
#define	NULLTCB	(struct tcb *)0
/* TCP round-trip time cache */
struct tcp_rtt {
	struct sockaddr addr;	/* Destination IP address */
	sint31 srtt;		/* Most recent SRTT */
	sint31 mdev;		/* Most recent mean deviation */
};
#define	NULLRTT	(struct tcp_rtt *)0
extern struct tcp_rtt Tcp_rtt[];

/* TCP statistics counters */
struct tcp_stat {
	uint16 runt;		/* Smaller than minimum size */
	uint16 checksum;		/* TCP header checksum errors */
	uint16 conout;		/* Outgoing connection attempts */
	uint16 conin;		/* Incoming connection attempts */
	uint16 resets;		/* Resets generated */
	uint16 bdcsts;		/* Bogus broadcast packets */
};

/* SNMP MIB variables, used for statistics and control. See RFC 1066 */
extern struct mib_entry Tcp_mib[];
#define	tcpRtoAlgorithm	Tcp_mib[1].value.integer
#define	tcpRtoMin	Tcp_mib[2].value.integer
#define	tcpRtoMax	Tcp_mib[3].value.integer
#define	tcpMaxConn	Tcp_mib[4].value.integer
#define	tcpActiveOpens	Tcp_mib[5].value.integer
#define tcpPassiveOpens	Tcp_mib[6].value.integer
#define	tcpAttemptFails	Tcp_mib[7].value.integer
#define	tcpEstabResets	Tcp_mib[8].value.integer
#define	tcpCurrEstab	Tcp_mib[9].value.integer
#define	tcpInSegs	Tcp_mib[10].value.integer
#define	tcpOutSegs	Tcp_mib[11].value.integer
#define	tcpRetransSegs	Tcp_mib[12].value.integer
#define	tcpInErrs	Tcp_mib[14].value.integer
#define	tcpOutRsts	Tcp_mib[15].value.integer
#define	NUMTCPMIB	15

extern struct tcb *Tcbs;
extern char *Tcpstates[];
extern char *Tcpreasons[];

/* Codes for the open_tcp call */
#define	TCP_PASSIVE	0
#define	TCP_ACTIVE	1
#define	TCP_SERVER	2	/* Passive, clone on opening */

/* In tcpcmd.c: */
extern sint31 Tcp_irtt;
extern uint16 Tcp_mss;
extern int Tcp_syndata;
extern int Tcp_trace;
extern uint16 Tcp_window;

#endif /* _IP_TCP_H */
