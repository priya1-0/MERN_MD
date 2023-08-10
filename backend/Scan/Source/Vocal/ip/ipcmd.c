
/* ************************************************************************* */
/*
 *	ipcmd.c
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
 *	This file contains the IP related commands.
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

#include "utils/utils.h"

static uint32 Ip_pool_new = 0L;
uint32 Ip_pool_min = 0L;
uint32 Ip_pool_max = 0L;
int Ip_secure = FALSE;

ENTRY void
ipcmd_init (void)
{
	Ip_pool_new = 0L;
	Ip_pool_min = 0L;
	Ip_pool_max = 0L;
	Ip_secure = FALSE;
}

LOCAL int
doipaddr (int argc, char *argv[], void *p)
{
	register struct iface *ifp;

	if (argc >= 2) {
		/* Lookup the interface name if it exists */
		if ((ifp = if_lookup (argv[1])) != NULLIF) {
			return chg_bit16 (&(ifp->flags), IFF_GLOBAL, "Allow Global", --argc, &argv[1]);
		}
	}
	return chg_addr (&Default_addr[AF_INET], AF_INET, "IP address", argc, argv);
}

LOCAL int
doipfilter (int argc, char *argv[], void *p)
{
	return chg_bool (&Ip_secure, "IP secure packet filtering", argc, argv);
}

/* Set a pool of addresses for dynamic assignment */
LOCAL int
doippool (int argc, char *argv[], void *p)
{
	struct sockaddr sock;
	uint16 pool_cnt;

	if (argc < 2) {
		if (Ip_pool_min == 0L) {
			printf("None\n");
		} else {
			printf("%s thru ", inet_ntoa(Ip_pool_min));
			printf("%s\n", inet_ntoa(Ip_pool_max));
		}
		return 0;
	}

	if (atos_err (argv[1], AF_INET, &sock))
		return 1;

	/* May specify a consecutive range of addresses; otherwise assume 1 */
	if (argc < 3)
		pool_cnt = 1;
	else {
		if (atoi16u_err (argv[2], &pool_cnt))
			return 1;
	}

	Ip_pool_new =
	Ip_pool_min = sock.sin_address;
	Ip_pool_max = Ip_pool_min + pool_cnt -1;
	return 0;
}

/* Assign an unused address from the pool */
ENTRY uint32
ip_pool (struct iface *ifp)
{
	int i = 1 + (int) (Ip_pool_max - Ip_pool_min);
	uint32 addr = 0L;
	register struct iface *sifp;

	do {
		if ((addr = Ip_pool_new++) >= Ip_pool_max)
			Ip_pool_new = Ip_pool_min;

		/* Check if address is already in use */
		for (sifp = Ifaces; sifp != NULLIF; sifp = sifp->next) {
			if (sifp->peeraddr[AF_INET].sin_address == addr) {
				addr = 0L;
				break;
			}
		}
	} while (i-->0  &&  addr == 0L);

	if (addr != 0L) {
		ifp->peeraddr[AF_INET].sin_address = addr;
		ifp->flags |= IFF_POOL;
		ifp->flags &= ~IFF_PEER;
	}
	return addr;
}

LOCAL int
doipmib (int argc, char *argv[], void *p)
{
	print_mib (Ip_mib, NUMIPMIB);
	return 0;
}

LOCAL int
doipshow (int argc, char *argv[], void *p)
{
	register struct reasm *rp;
	register struct frag *fp;

	printf ("Reassembly Fragments\n");

	if (Reasmq != NULLREASM)
		printf ("Source          Destination     ID    Proto Timer      Length  Offset  Last\n");

	for (rp = Reasmq; rp != NULLREASM; rp = rp->next) {
		printf ("%15s ",snhtoa (&rp->source));
		printf ("%15s %-5u %5u %10lu %6u",
			snhtoa (&rp->dest), rp->id, uchar (rp->protocol),
			(long) read_timer (&rp->timer), rp->length);
		if ((fp = rp->fraglist) != NULLFRAG) {
			printf ("  %6u  %6u\n", fp->offset, fp->last);
			for (fp = fp->next; fp != NULLFRAG; fp = fp->next) {
				printf ("\t\t\t\t\t\t\t\t%6u  %6u\n",
					fp->offset, fp->last);
                        }
		}
		else
			printf ("\n");
	}
	return 0;
}

LOCAL int
doiprtimer (int argc, char *argv[], void *p)
{
	return chg_int32s (&ipReasmTimeout,"IP reasm timeout (seconds)",argc,argv);
}

LOCAL int
doipttl (int argc, char *argv[], void *p)
{
	return chg_int32s (&ipDefaultTTL,"IP Time-to-live (hops)",argc,argv);
}

/* "ip options" subcommands */
static const struct cmds Optscmds[] = {
	{"rtimer",		doiprtimer,			0,	0,	"[secs]"},
	{"ttl",			doipttl,			0,	0,	"[hops]"},
	{NULLCHAR},
};

LOCAL int
doipoptions (int argc, char *argv[], void *p)
{
	return subcmd (Optscmds, argc, argv, p);
}

/* Dump a routing table entry */
LOCAL void
iproute_detail (register struct route *rp)
{
	char *cp;

	if (rp->target.sin_address != 0L) {
		cp = snhtoa (&rp->target);
	} else {
		cp = "default";
	}

	printf ("%-15s 0x%08lx %-14s ",cp, (long) rp->netmask, rp->iface->name);
	printf ("%-15s %4u %5u ", snhtoa (&rp->gateway), rp->hopcount, rp->delay);

	printf ("%6d %c %5lu ", rp->metric, ((rp->flags & RTPRIVATE) ? 'P':'.'), (long) (read_timer (&rp->timer) / 1000L));

	printf ("%5lu\n", (long) rp->uses);
}

LOCAL int
doiprouteshow (int argc, char *argv[], void *p)
{
	register int i;
	register struct route *rp, *rps;

	printf ("Network/Host    Mask       Device         Gateway         Hops Delay Metric P Timer   Use\n");

	for (i = 0; i < HASHMOD; i++) {
		for (rp = Routes[AF_INET][i]; rp != NULLROUTE; rp = rp->next) {
			for (rps = rp; rps != NULLROUTE; rps = rps->same) {
				iproute_detail (rps);
			}
		}
	}

	if (Route_default[AF_INET].iface != NULLIF) {
		iproute_detail (&Route_default[AF_INET]);
	}
	return 0;
}

/* Add an entry to the routing table
 * E.g., "add 1.2.3.4 ax0 5.6.7.8 3"
 */
LOCAL int
doipadd (int argc, char *argv[], void *p)
{
	struct iface *ifp;
	struct sockaddr dest;
	struct sockaddr gateway;
	char *bitp;
	uint16 hopcount = 0;
	uint16 delay = 0;
	sint15 tos = 0;
	uint32 netmask = 0L;
	char ipadd_private = 0;

	gateway.sa_family = AF_NONE;
	if (argv[0][0] == 'p')
		ipadd_private = 1;
	if (stricmp(argv[1],"default") == 0) {
		dest.sa_family = AF_INET;
		dest.sin_address = 0L;
		ipadd_private = 1;
	} else {
		/* If IP address is followed by an optional slash and
		 * a length field, (e.g., 128.96 / 16) get it;
		 * otherwise assume a full 32 - bit address
		 */
		if ((bitp = strchr (argv[1], '/')) != NULLCHAR) {
			/* Terminate address token for resolve() call */
			*bitp++= '\0';
			if (atom_err (bitp, &netmask))
				return 1;
		}
		else {
			netmask = 0xffffffffL;
		}

		if (atos_err (argv[1], AF_INET, &dest))
			return 1;
	}

	if (atoiface_err (argv[2], &ifp))
		return 1;

	if (argc > 3) {
		if (atos_err (argv[3], AF_INET, &gateway))
			return 1;
	}

	if (argc > 4) {
		if (atoi16u_err (argv[4], &hopcount))
			return 1;
	}
	else
		hopcount = 1;

	if (argc > 5) {
		if (atoi16u_err (argv[5], &delay))
			return 1;
	}

	if (rt_add (&dest, netmask, &gateway, ifp, hopcount, delay, tos, 0, ipadd_private) == NULLROUTE)
		printf("Route add failed\n");

	return 0;
}

/* Drop an entry from the routing table
 * E.g., "drop 128.96/16
 */
LOCAL int
doipdrop (int argc, char *argv[], void *p)
{
	char *bitp;
	uint32 netmask = 0L;
	struct sockaddr addr;
	struct iface *ifp = NULLIF;

	if (stricmp(argv[1],"default") == 0) {
		addr.sa_family = AF_INET;
		addr.sin_address = 0L;
	} else {
		/* If IP address is followed by an optional slash and length field,
		 *(e.g., 128.96 / 16) get it; otherwise assume a full 32 - bit address
		 */
		if ((bitp = strchr (argv[1], '/')) != NULLCHAR) {
			/* Terminate address token for resolve() call */
			*bitp++= '\0';
			if (atom_err (bitp, &netmask))
				return 1;
		}
		else {
			netmask = 0xffffffffL;
		}
		if (atos_err (argv[1], AF_INET, &addr))
			return 1;
	}
	if (argc > 2) {
		if (atoiface_err (argv[2], &ifp))
			return 1;
	}
	return rt_drop (&addr, netmask, ifp);
}

/* Force a timeout on all temporary routes */
LOCAL int
doipflush (int argc, char *argv[], void *p)
{
	register struct route *rp, *rps;
	struct route *rptmp, *rpstmp;
	int i;

	if (Route_default[AF_INET].timer.state == TIMER_RUN) {
		rt_drop(&Route_default[AF_INET].target,0L, Route_default[AF_INET].iface);	/* Drop default route */
	}
	for (i = 0;i < HASHMOD;i++) {
		for (rp = Routes[AF_INET][i];rp != NULLROUTE;rp = rptmp) {
			rptmp = rp->next;
			for (rps = rp; rps != NULLROUTE; rps = rpstmp) {
				rpstmp = rp->same;
				if (rps->timer.state == TIMER_RUN) {
					rt_drop (&rps->target, rps->netmask, rps->iface);
				}
			}
		}
	}
	return 0;
}

LOCAL int
doiplook (int argc, char *argv[], void *p)
{
	struct route *rp;
	struct sockaddr addr;

	if (atosr_err (argv[1], AF_INET, &addr, &rp))
		return 1;

	iproute_detail (rp);
	return 0;
}

/* "ip route" subcommands */
static const struct cmds Iprtcmds[] = {
	{"add",			doipadd,			0,	3,	"<addr[/mask]|default> <iface> [gateway [hopcount [delay]]]"},
	{"drop",		doipdrop,			0,	2,	"<addr[/mask]|default> [iface]"},
	{"flush",		doipflush,			0,	0,	""},
	/* This command assumed to begin with 'p' */
	{"private",		doipadd,			0,	3,	"<addr[/mask]|default> <iface> [gateway [hopcount [delay]]]"},
	{"query",		doiplook,			0,	2,	"<addr>"},
	{"show",		doiprouteshow,		0,	0,	""},
	{NULLCHAR},
};

/* Display and/or manipulate routing table */
LOCAL int
doiproute (int argc, char *argv[], void *p)
{
	return subcmd (Iprtcmds, argc, argv, p);
}

/* "ip" subcommands */
static const struct cmds Ipcmds[] = {
	{"address",		doipaddr,			0,	0, 	"[addr|iface [on|off]]"},

	{"domain",		dodomain,			0,	0, 	NULLCHAR},

	{"filter",		doipfilter,			0,	0,	"[on|off]"},
	{"icmp",		doicmp,				0,	0,	NULLCHAR},
	{"mib",			doipmib,			0,	0,	""},
	{"options",		doipoptions,		0,	0,	NULLCHAR},
	{"pool",		doippool,			0,	0,	"[addr [count]]"},
	{"route",		doiproute,			0,	0,	NULLCHAR},
	{"show",		doipshow,			0,	0,	""},
	{"tcp",			dotcp,				0,	0,	NULLCHAR},
	{"udp",			doudp,				0,	0,	NULLCHAR},
	{NULLCHAR},
};

ENTRY int
doip (int argc, char *argv[], void *p)
{
	return subcmd (Ipcmds, argc, argv, p);
}
