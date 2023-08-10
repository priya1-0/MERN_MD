
/* ************************************************************************* */
/*
 *	udpcmd.c
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
 *	This file contains the UDP related user commands.
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

/* Return 1 if arg is a valid UCB, 0 otherwise */
ENTRY int
ucbval (struct udp_cb *ucb)
{
	register struct udp_cb *ucb1;

	if (ucb == NULLUDP)
		return 0;	/* Null pointer can't be valid */
	for (ucb1 = Udps; ucb1 != NULLUDP; ucb1 = ucb1->next) {
		if (ucb1 == ucb)
			return 1;
	}
	return 0;
}
/* Convert a string to a UCB address and verify it.
 */
LOCAL int
atoucb_err (char *cp, struct udp_cb **ucbpp)
{
	uint32 num;

	if (atoi32uh_err (cp, &num))
		return 1;
	*ucbpp = (struct udp_cb *) ltop (num);
	if (!ucbval (*ucbpp)) {
		printf ("Not a valid UCB address: %s\n", cp);
		return 1;
	}
	return 0;
}

/* Display MIB variables */
LOCAL int
doudpmib (int argc, char *argv[], void *p)
{
	struct udp_cb *ucb;

	print_mib (Udp_mib, NUMUDPMIB);

	if (argc > 1) {
		if (atoucb_err (argv[1], &ucb))
			return 1;
		printf ("\nUCB:\t\t\t%14lx\n", ptol (ucb));
		printf ("( 1) udpLocalAddress\t%14s\t( 2) udpLocalPort\t%14u\n", snhtoa (&ucb->socket), ucb->socket.sin_port);
	}
	return 0;
}

LOCAL int
ucb_summary (void)
{
	register struct udp_cb *ucb;

	printf ("UCB      Rcv-Q  Local socket\n");
	for (ucb = Udps; ucb != NULLUDP; ucb = ucb->next) {
		printf ("%8lx%6u  %s\n", ptol(ucb), ucb->rcvcnt, snhptoa(&ucb->socket));
	}
	return 0;
}

ENTRY int
ucb_detail (struct udp_cb *ucb)
{
	printf ("Local: %21s Rcv-Q %6u", snhptoa (&ucb->socket), ucb->rcvcnt);
	return 0;
}

/* Dump UDP statistics and control blocks */
LOCAL int
doudpshow (int argc, char *argv[], void *p)
{
	ucb_summary ();
	return 0;
}

static const struct cmds Udpcmds[] = {
	{"mib",			doudpmib,			0,	0,	"<ucb>"},
	{"show",		doudpshow,			0,	0,	""},
	{NULLCHAR},
};

ENTRY int
doudp (int argc, char *argv[], void *p)
{
	return subcmd (Udpcmds, argc, argv, p);
}
