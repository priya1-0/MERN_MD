
/* ************************************************************************* */
/*
 *	config.c
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
 *	Module:		MAIN
 *
 *	This file contains the functions.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 19:56:06  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

/* A collection of stuff heavily dependent on the configuration info
 * in config.h. The idea is that configuration - dependent tables should
 * be located here to avoid having to pepper lots of .c files with #ifdefs,
 * requiring them to include config.h and be recompiled each time config.h
 * is modified.
 */
#include "system/system.h"
#include "lansend/global.h"

#include "net/net.h"
#include "sys/sys.h"
#include "dev/dev.h"

#include "ip/ip.h"

#include "lansend/local.h"

#include "term/term.h"
#include "trace/trace.h"
#include "utils/utils.h"
#include "wan/wan.h"

#include "include/test.h"

#include "include/hardware.h"

#include "customer/customer.h"

/* ************************************************************************* */

/* ************************************************************************* */

struct mbuf *Hopper = NULLBUF;	/* Queue of incoming packets */
uint16 Nsessions = NSESSIONS;
uint16 Nsock = DEFNSOCK;		/* Number of socket entries */
uint16 Nusers = NUSERS;

/* Free memory threshold, below which things start to happen to conserve
 * memory, like garbage collection, source quenching and refusing connects
 */
uint16 Memthresh = MTHRESH;
uint16 Nibufs_host = NHOST_IBUFS;
uint16 Ibufsize = IBUFSIZE;	/* Size of each interrupt buffer */
uint16 Nfiles = DEFNFILES;

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

ENTRY void
config_init (void)
{
	Hopper = NULLBUF;	/* Queue of incoming packets */
	Nsessions = NSESSIONS;
	Nsock = DEFNSOCK;		/* Number of socket entries */
	Nusers = NUSERS;
	Memthresh = MTHRESH;
	Ibufsize = IBUFSIZE;	/* Size of each interrupt buffer */
	Nfiles = DEFNFILES;
}

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

/* List of supported hardware devices */
extern const struct cmds Attab[] = {

	/* Dedicated synchronous interface */
	{"mdm",			mdm_attach,			0,	0,	"[modem|ppp|slip]"},

	NULLCHAR,
};

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

#define NULLSTATE ((char *(*)(struct usock *))0)

/* Socket-protocol interface table */
extern const struct socklink Socklink[] = {
	/* type,
	 * socket,		bind,			listen,			connect,
	 * accept,		recv,			send,			qlen,
	 * kick,		shut,			close,			check,
	 * error,		state,			status,			eol_seq
	 */
	TYPE_TCP,
	so_tcp,			NULLFP,			so_tcp_listen,	so_tcp_conn,
	TRUE,			so_tcp_recv,	so_tcp_send,	so_tcp_qlen,
	so_tcp_kick,	so_tcp_shut,	so_tcp_close,	checkipaddr,
	Tcpreasons,		tcpstate,		so_tcp_stat,	Inet_eol,

	TYPE_UDP,
	so_udp,			so_udp_bind,	NULLFP,			so_udp_conn,
	FALSE,			so_udp_recv,	so_udp_send,	so_udp_qlen,
	NULLFP,			NULLFP,			so_udp_close,	checkipaddr,
	NULL,			NULLSTATE,		so_udp_stat,	Inet_eol,

	TYPE_RAW,
	so_ip_sock,		NULLFP,			NULLFP,			so_ip_conn,
	FALSE,			so_ip_recv,		so_ip_send,		so_ip_qlen,
	NULLFP,			NULLFP,			so_ip_close,	checkipaddr,
	NULL,			NULLSTATE,		NULLFP,			Inet_eol,

	-1
};

/* ************************************************************************* */

/* TCP port numbers to be considered "interactive" by the IP routing
 * code and given priority in queueing
 */
extern const int Tcp_interact[] = {
	IPPORT_FTP,		/* FTP control (not data!) */
	IPPORT_TELNET,		/* Telnet */
	IPPORT_LOGIN,		/* BSD rlogin */
	IPPORT_MTP,		/* Secondary telnet */
	-1
};

/* ************************************************************************* */

/* Transport protocols atop IP */
extern const struct iplink Iplink[] = {
	TCP_PTCL,		tcp_input,

	UDP_PTCL,		udp_input,

	ICMP_PTCL,		icmp_input,

	0,				0
};

/* ************************************************************************* */

/* Transport protocols atop ICMP */
extern const struct icmplink Icmplink[] = {
	TCP_PTCL,		tcp_icmp,
	UDP_PTCL,		udp_icmp,

	0,				0
};

/* ************************************************************************* */

/* ************************************************************************* */

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

/* Get rid of trace references in Iftypes[] if TRACE is turned off */

#define	ether_dump	NULLVFP

#ifndef DO_LANSEND_DUMP_SLIP
#define	sl_dump		NULLVFP
#endif /* DO_LANSEND_DUMP_SLIP */

/* ************************************************************************* */

/* Table of interface types. Contains most device- and encapsulation-
 * dependent info
 */
#define ETHER_FORUS ether_forus

extern const struct iftype Iftypes[] = {
	/* ifType,			name,
	 * attach,			detach,			start,			suspend,
	 * outgoing,		incoming,		iostatus,		timeout,
	 * show,			discard,		echo,			trace,
	 * addrtest,		format,			scan,			arptype,
	 * hwalen,			broadcast */

	 /* Note, ifType is the SNMP type for the encapsulation */

	 /* This entry must be first, since Loopback refers to it */
	  { IFT_OTHER,		"None.",
		NULL,			NULL,			NULL,			NULL,
		bitbucket,		net_proc,		NULL,			NULL,
		NULL,			NULL,			NULL,			ip_dump,
		NULL,			NULL,			NULL,			0,
		0,				NULL },

	/* Incomplete Raw serial line interface.*/
	  { IFT_OTHER,		"RAW SERIAL",
		NULL,			NULL,			NULL,			NULL,
		NULL,			NULL,			NULL,			NULL,
		NULL,			NULL,			NULL,			NULL,
		NULL,			NULL,			NULL,			0,
		0,				NULL },

	  { IFT_PPP,		"PPP",
		ppp_attach,		ppp_detach,		ppp_start,		ppp_suspend,
		ppp_send,		ppp_proc,		ppp_iostatus,	ppp_timeout,
		ppp_show,		ppp_discard,	ppp_echo,		ppp_dump,
		NULL,			NULL,			NULL,			0,
		0,				NULL },

	  { (uint16) -1,	NULLCHAR,
		NULLVFP,		NULLVFP,		NULLFP,			NULLVFP,
		NULLFP,			NULLVFP,		NULLVFP,		NULLVFP,
		NULLVFP,		NULLFP,			NULLFP,			NULLVFP,
		NULLFP,			NULL,			NULLFP,			0,
		0,				NULL }
};

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

/* Asynchronous interface mode table - names must match exactly (except case) to above tables
 */
extern const char *Asymode[] = {

	"PPP",

	"DIALER",
	NULLCHAR
};

/* ************************************************************************* */

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

/* Daemons to be run at startup time
 */
extern const struct daemon Daemons[] = {
	"command",	1024,		command_process,
	"killer",	512,		killer,
	"timer",	1024,		timerproc,
	"network",	1536,		network,
	"keyboard",	250,		keyboard,
	NULLCHAR,	0,			NULLVFP
};

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

/* Functions to be called on each clock tick
 */
extern void (*Cfunc[]) () = {
	pctick,			/* Call routine to keep time */

	refiq,			/* Replenish interrupt pool */

	sesflush,		/* Flush current session output */

	NULL,
};

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

/* Entry points for garbage collection
 */
extern void (*Gcollect[]) (int) = {
	tcp_garbage,
	iface_garbage,
	ip_garbage,
	udp_garbage,
	st_garbage,

	NULL
};

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

/* Functions to be called at shutdown */
extern void (*Shutdown[]) () = {
	NULLVFP,
};

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

/* Stub for routing timeout when RIP is not configured -- just remove entry */
ENTRY void
iprt_timeout (void *s)
{
	struct route *stale = (struct route *) s;

	rt_drop (&stale->target, stale->netmask, stale->iface);
}

/* ************************************************************************* */

/* Stubs for Van Jacobsen header compression */

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

/* ************************************************************************* */

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

/* ************************************************************************* */

/* ************************************************************************* */

/* ************************************************************************* */

/* ************************************************************************* */
