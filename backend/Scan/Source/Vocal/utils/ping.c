
/* ************************************************************************* */
/*
 *	ping.c
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
 *	Module:		UTILS
 *
 *	This file contains the PING functions.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 20:53:02  zhangn1
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

#include "utils/local.h"

/* Send ICMP Echo Request packets */
ENTRY int
doping (int argc, char *argv[], void *p)
{
	struct proc *pinger = NULLPROC;	/* Transmit process */
	struct ping ping;
	struct sockaddr from;
	struct icmp icmp;
	struct mbuf *bp;
	sint31 timestamp, rtt, abserr;
	int s, fromlen;
	struct session *sp;

	memset ((char *) &ping, 0, sizeof (ping));

	/* Allocate a session descriptor */
	if ((sp = ping.sp = newsession (argv[1], PING, TRUE)) == NULLSESSION) {
		return 1;
	}
	if ((s = socket (AF_INET, SOCK_RAW, ICMP_PTCL)) == -1) {
		printf("Can't create socket\n");
		keywait (NULLCHAR, 1);
		freesession (sp);
		return 1;
	}
	sp->network = fdopen(s,"r+t");	/* Set up for session close */

	printf("Resolving %s... ",sp->name);
	if ((ping.target = inet_addr (sp->name)) == 0) {
		printf("Host %s unknown\n",sp->name);
		keywait (NULLCHAR, 1);
		close (s);

		freesession (sp);
		return 1;
	}

	if (argc > 2) {
		if (atoi16u_err (argv[2], &ping.len)) {
			close (s);
			return 1;
		}
	}

	if (argc > 3) {
		if (atoi32s_err (argv[3], &ping.interval)) {
			close (s);
			return 1;
		}
	}

	/* Optionally ping a range of IP addresses */
	if (argc > 4)
		ping.incflag = TRUE;

	if (ping.interval != 0) {
		pinger = newproc("pingtx",500,pingtx,s,&ping,NULL,0);
	} else {
		/* One shot ping; let echo_proc hook handle response.
		 * A negative ID will not be confused with a legal socket
		 * number, which is used to identify repeated pings
		 */
		pingem (s, ping.target, 0, (sp->user | 0x8000U), ping.len);
		pause (100);
		close (s);
		freesession (sp);
		return 0;
	}

	/* Now collect the replies */
	pinghdr (sp, &ping);

	for (;;) {
		fromlen = sizeof (from);
		if (recv_mbuf (s, &bp, 0, 0, (char *) &from, &fromlen) == -1) {
			break;
		}
		ntohicmp (&icmp, &bp);
		if ((icmp.type != ICMP_ECHO_REPLY) || (icmp.args.echo.id != s)) {
			/* Ignore other people's responses */
			free_p (bp);
			continue;
		}
		/* Get timestamp */
		timestamp = get32 (bp->data);

		free_p (bp);

		ping.responses++;

		/* Compute round trip time, update smoothed estimates */
		rtt = msclock () - timestamp;
		abserr = (rtt > ping.srtt) ? (rtt - ping.srtt) : (ping.srtt - rtt);

		if (ping.responses == 1) {
			/* First response, base entire SRTT on it */
			ping.srtt = rtt;
			ping.mdev = 0;
		} else {
			ping.srtt = (7*ping.srtt + rtt + 4) >> 3;
			ping.mdev = (3*ping.mdev + abserr + 2) >> 2;
		}
		if ((ping.responses % 20) == 0)
			pinghdr (sp, &ping);

		if (ping.incflag) {
			struct rr *save_rrlp, *rrlp;

			printf("%-15s",inet_ntoa(from.sin_address));

			for (rrlp = save_rrlp = inverse_a (from.sin_address);
			    rrlp != NULLRR;
			    rrlp = rrlp->next) {
				if (rrlp->rdlength > 0) {
					switch (rrlp->type) {
					case TYPE_PTR:
						printf(" %s", rrlp->rdata.name);
						break;
					case TYPE_A:
						printf(" %s", rrlp->name);
						break;
					default:
						continue /*for*/;
					}
					break /*for*/;
				}
			}
			free_rr (save_rrlp);

			printf(" (%lu ms)\n", (long) rtt);
		} else {

			printf("%5lu%5lu%10lu%15lu%15lu%15lu\n",
				(long) ping.sent,
				(long) ping.responses,
				(long) ((ping.responses*100 + ping.sent / 2) / ping.sent),
				(long) rtt,
				(long) ping.srtt,
				(long) ping.mdev);
		}
	}
	if (pinger != NULLPROC)
		killproc (pinger);
	freesession (sp);
	return 0;
}
LOCAL void
pinghdr (struct session *sp, struct ping *ping)
{
	printf("Pinging %s (%s); data %d interval %lu ms:\n",
		sp->name,
		inet_ntoa (ping->target),
		ping->len,
		(long) ping->interval);
	if (!ping->incflag) {
		printf(" sent  rcvd    %       rtt        avg              rtt              mdev\n");
	}
}

ENTRY void
echo_proc (sint31 source, sint31 dest, icmp_t *icmp, struct mbuf *bp)
{
	sint31 timestamp, rtt;
	struct user_s *up;
	int index;

	if (Icmp_echo && ((icmp->args.echo.id & 0x8000U) == 0x8000U)
	 && ((index = (icmp->args.echo.id & 0x7fff)) < Nusers)
	 && ((up = Users[index]) != NULL)) {

		/* Compute round trip time */
		timestamp = get32 (bp->data);
		rtt = msclock () - timestamp;
		fprintf(up->display->output, "%s (%lu ms)\n", (long) inet_ntoa (source), rtt);
	}

	free_p (bp);
}

/* Ping transmit process. Runs until killed */
LOCAL void
pingtx (int s, void *ping1, void *p)
{
	struct ping *ping;
	int c;

	ping = (struct ping *) ping1;
	ping->sent = 0;

	if (ping->incflag) {
		for (;;) {
			pingem (s, ping->target++, 0,
				(uint16) s, ping->len);
			ping->sent++;
			pause (ping->interval);
		}
	} else {
		for (;;) {
			pingem (s, ping->target, (uint16) ping->sent++,
				(uint16) s, ping->len);
			pause (ping->interval);
			if ((c = fpeek(stdin)) != EOF) {
				c = getc(stdin);		/* Read the character */
				if ((c == EOF) || (c == ASCII__ESC)) {
					close (s);
					for (;;) {
						pwait (NULL);	/* Stay here until the kill */
					}
				}
			}
		}
	}
}

/* Send ICMP Echo Request packet */
ENTRY int
pingem (int s, uint32 target, uint16 seq, uint16 id, uint16 len)
{
	struct mbuf *data;
	struct mbuf *bp;
	struct icmp icmp;
	struct sockaddr to;
	uint32 clock;

#define CLOCK_SIZEOF	4

	clock = msclock ();
	data = ambufw ((uint16) (len + CLOCK_SIZEOF));
	data->cnt = len + CLOCK_SIZEOF;

	/* Set optional data field, if any, to all 55's */
	if (len != 0) {
		memset (data->data + CLOCK_SIZEOF, 0x55, len);
	}

	/* Insert timestamp and build ICMP header */
	put32 (data->data, clock);

	icmpOutEchos++;
	icmpOutMsgs++;
	icmp.type = ICMP_ECHO;
	icmp.code = 0;
	icmp.args.echo.seq = seq;
	icmp.args.echo.id = id;
	if ((bp = htonicmp (&icmp, data)) == NULLBUF) {
		free_p (data);
		return 0;
	}
	to.sa_family = AF_INET;
	to.sin_address = target;
	send_mbuf (s, bp, 0, (char *) &to, sizeof (to));
	return 0;
}
