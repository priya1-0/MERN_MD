
/* ************************************************************************* */
/*
 *	devcmd.c
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
 *	Module:		DEV
 *
 *  Various device configuration routines.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 19:38:37  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#include "system/system.h"
#include "lansend/global.h"

#include <ctype.h>

#include "net/net.h"
#include "sys/sys.h"
#include "dev/dev.h"

#include "ip/ip.h"

#include "dev/mdmcmd.h"
#include "dev/devmdm.h"

#include "dev/local.h"

#include "lansend/lansend.h"

#include "term/term.h"
#include "trace/trace.h"

/* ************************************************************************* */

/* ************************************************************************* */
/*
 *  Function: do_if_ipaddr
 *
 *  Set or display the IP address for the device or circuit.
 *
 *  Parameters:
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is a void pointer to the interface
 *
 *  Command Line: device|circuit <device|circuit> ip addr [addr] <netmask>
 *
 *  Returns: 0 for success
 *           else error
 *
 */
LOCAL int
do_if_ipaddr (int argc, char *argv[], void *p)
{
	struct iface *ifp = (struct iface *) p;
	struct sockaddr *sp = &ifp->address[AF_INET];
	struct sockaddr sock;
	uint32 netmask;

	sock = *sp;
	if (chg_addr (&sock, AF_INET, "IP address", argc, argv))
		return 1;

	netmask = ifp->netmask[AF_INET];
	if (argc > 2) {
		if (chg_mask (&netmask, "IP network mask", (argc - 1), &argv[1]))
			return 1;
	}

	/* Remove and add route for IP interface address */
	if (argc > 1) {
		if_setaddr (ifp, &sock, netmask, TRUE);
	}
	return 0;
}

/* ************************************************************************* */
/*
 *  Function: do_if_ippeer
 *
 *  Set or display the IP peer address for the device or circuit.
 *
 *  Parameters:
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is a void pointer to the interface
 *
 *  Command Line: device|circuit <device|circuit> ip peer [addr]
 *
 *  Returns: 0 for success
 *           else error
 *
 */
LOCAL int
do_if_ippeer (int argc, char *argv[], void *p)
{
	struct iface *ifp = (struct iface *) p;

	return chg_addr (&ifp->peeraddr[AF_INET], AF_INET, "IP peer address", argc, argv);
}

/* ************************************************************************* */
/*
 *  Function: do_if_ipbroad
 *
 *  Set or display the IP broadcast address for the device or circuit.
 *
 *  Parameters:
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is a void pointer to the interface
 *
 *  Command Line: device|circuit <device|circuit> ip broad [addr]
 *
 *  Returns: 0 for success
 *           else error
 *
 */
LOCAL int
do_if_ipbroad (int argc, char *argv[], void *p)
{
	struct iface *ifp = (struct iface *) p;
	struct route *rp;
	struct sockaddr *sp = &ifp->broadcast[AF_INET];
	struct sockaddr sock;

	sock = *sp;
	if (chg_addr (&sock, AF_INET, "IP broadcast address", argc, argv))
		return 1;

	/* Remove and add route for IP broadcast address */
	if (argc > 1) {
		if (sp->sa_family == AF_INET) {
			rp = rt_exact (sp, 0xffffffffL, ifp);
			if (rp != NULLROUTE)
				rt_drop (sp, 0xffffffffL, ifp);
		}
		*sp = sock;
		rt_add (sp, 0xffffffffL, NULL, ifp, 1, 0, 0, 0L, 1);

	}
	return 0;
}

/* ************************************************************************* */
/*
 *  Function: do_if_ipnetmask
 *
 *  Set or display the IP (sub) network mask address for the device or circuit.
 *
 *  Parameters:
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is a void pointer to the interface
 *
 *  Command Line: device|circuit <device|circuit> ip netmask [mask]
 *
 *  Returns: 0 for success
 *           else error
 *
 */
LOCAL int
do_if_ipnetmsk (int argc, char *argv[], void *p)
{
	struct iface *ifp = (struct iface *) p;
	struct sockaddr sock;
	uint32 netmask;

	netmask = ifp->netmask[AF_INET];
	if (chg_mask (&netmask, "IP network mask", argc, argv))
		return 1;

	/* Remove and add route for the IP interface address */
	if (argc > 1) {
		sock = ifp->address[AF_INET];
		if_setaddr (ifp, &sock, netmask, TRUE);
	}
	return 0;
}

/* ************************************************************************* */
/*
 *  Function: type_ip
 *
 *  Return string corresponding to the IP type for the device.
 *
 *  Parameters:
 *    "ip_type" is the type to be decoded
 *
 *  Returns: Pointer to type as a string
 *
 */
LOCAL char *
type_ip (int ip_type)
{
	char *cp;

	switch (ip_type) {
	case PT_IP:
		cp = "II";
		break;
	case PT_IP_8022:
		cp = "802.2";
		break;
	case PT_IP_SNAP:
		cp = "SNAP";
		break;
	case 0:
		cp = "Any";
		break;
	default:
		cp = "Error";
	}
	return cp;
}

/* ************************************************************************* */
/*
 *  Function: do_if_iptype
 *
 *  Set or display the IP encapsulation type for the device.
 *
 *  Parameters:
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is a void pointer to the interface
 *
 *  Command Line: device|circuit <device|circuit> ip type [II|802.2|snap|any]
 *
 *  Returns: 0 for success
 *           else error
 *
 */
LOCAL int
do_if_iptype (int argc, char *argv[], void *p)
{
	struct iface *ifp = (struct iface *) p;

	if ((ifp->iftype == NULLIFT) || (ifp->iftype->ifType != IFT_ETHERNET)) {
		printf ("Device not an ethernet type: %s\n", ifp->name);
		return 1;
	}

	if (argc < 2) {
		printf ("IP type: %s\n", type_ip (ifp->ip_type));
	}
	else {
		if (stricmp (argv[1], "II") == 0)
			ifp->ip_type = PT_IP;
		else if (stricmp (argv[1], "802.2") == 0)
			ifp->ip_type = PT_IP_8022;
		else if (stricmp (argv[1], "SNAP") == 0)
			ifp->ip_type = PT_IP_SNAP;
		else if (stricmp (argv[1], "any") == 0)
			ifp->ip_type = 0;
		else {
			printf ("Invalid ethernet type: %s\n", argv[1]);
			return 1;
		}
	}
	return 0;
}

/* ************************************************************************* */
/*
 *  Command Table: device|circuit <device|circuit> ip ...
 *
 */
static const struct cmds Devipcmds[] = {
	{"address",		do_if_ipaddr,		0,	0,	"[addr]"},
	{"broadcast",	do_if_ipbroad,		0,	0,	"[addr]"},
	{"type",		do_if_iptype,		0,	0,	"[II|802.2|snap|any]"},
	{"netmask",		do_if_ipnetmsk,		0,	0,	"[mask]"},
	{"peer",		do_if_ippeer,		0,	0,	"[addr]"},
	{NULLCHAR},
};

/* ************************************************************************* */
/*
 *  Function: do_if_ip
 *
 *  Perform IP specific configuration for the device or circuit.
 *
 *  Parameters:
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is a void pointer to the interface
 *
 *  Command Line: device|circuit <device|circuit> ip ...
 *
 *  Returns: 0 for success
 *           else error
 *
 */
LOCAL int
do_if_ip (int argc, char *argv[], void *p)
{
	return subcmd (Devipcmds, argc, argv, p);
}

/* ************************************************************************* */
/*
 *  Function: do_if_detach
 *
 *  Detach the device or circuit.
 *
 *  Parameters:
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is a void pointer to the interface
 *
 *  Command Line: device|circuit <device|circuit> detach
 *
 *  Returns: 0 for success
 *           else error
 *
 */
LOCAL int
do_if_detach (int argc, char *argv[], void *p)
{
	register struct iface *ifp = (struct iface *) p;

	if (if_detach (ifp) == -1) {
		printf ("Can't detach loopback/tunnel interfaces\n");
	}
	return 0;
}

/* ************************************************************************* */
/*
 *  Function: do_if_encap
 *
 *  Set or display the encapsulation for the device or circuit.
 *
 *  Parameters:
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is a void pointer to the interface
 *
 *  Command Line: device|circuit <device|circuit> encap [protocol]
 *
 *  Returns: 0 for success
 *           else error
 *
 */
LOCAL int
do_if_encap (int argc, char *argv[], void *p)
{
	struct iface *ifp = (struct iface *) p;

	if (argc < 2) {
		printf ("Encapsulation protocol: %s\n", ifp->iftype->name);
	}
	else {
		{
			printf ("Encapsulation protocol can not be changed for device\n");
			return 1;
		}
	}
	return 0;
}

/* ************************************************************************* */
/*
 *  Function: do_if_mtu
 *
 *  Set or display the maximum transmission unit for the device or circuit.
 *
 *  Parameters:
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is a void pointer to the interface
 *
 *  Command Line: device|circuit <device|circuit> mtu [bytes]
 *
 *  Returns: 0 for success
 *           else error
 *
 */
LOCAL int
do_if_mtu (int argc, char *argv[], void *p)
{
	struct iface *ifp = (struct iface *) p;

	return chg_int16u (&ifp->mtu, "Device MTU", argc, argv);
}

/* ************************************************************************* */
/*
 *  Function: do_if_mib
 *
 *  Display the MIB variables for the device or circuit.
 *
 *  Parameters:
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is a void pointer to the interface
 *
 *  Command Line: device|circuit <device|circuit> mib
 *
 *  Returns: 0 for success always
 *
 */
LOCAL int
do_if_mib (int argc, char *argv[], void *p)
{
	register struct iface *ifp = (struct iface *) p;
	register const struct iftype *ift = ifp->iftype;
	char *cp;

	/* Display the MIB values */
	printf ("%s\t\t%14s\n", "Device:\t", ifp->name);
	printf ("( 1) ifIndex\t\t%14u\n", ifp->ifIndex);
	printf ("( 2) ifDescr\t\t%14s\n", ifp->ifDescr);
	printf ("( 3) ifType\t\t%11s(%u)\t( 4) ifMtu\t\t%14u\n", ift->name, ift->ifType, ifp->mtu);

	if (ift->hwalen)
		cp = ift->format (ifp->hwaddr);
	else if ((cp = ifp->hwaddr) == NULLCHAR)
		cp = "None.";
	printf ("( 5) ifSpeed\t\t%14lu\t( 6) ifPhysAddress %19s\n", (long) ifp->Speed, cp);

	if (ifp->flags & IFF_TESTING)
		cp = "Testing";
	else if (ifp->flags & IFF_START)
		cp = "Up";
	else
		cp = "Down";
	printf ("( 7) ifAdminStatus\t%14s\t", cp);

	if (ifp->flags & IFF_TESTING)
		cp = "Testing";
	else if (ifp->flags & IFF_UP)
		cp = "Up";
	else
		cp = "Down";
	printf ("( 8) ifOperStatus\t%14s\n", cp);
	printf ("( 9) ifLastChange\t%14s\t(10) ifInOctets\t\t%14lu\n", tformat (ifp->LastChange), (long) ifp->ifInOctets);
	printf ("(11) ifInUcastPkts\t%14lu\t(12) ifInNUcastPkts\t%14lu\n", (long) ifp->ifInUcastPkts, (long) (ifp->ifInMcastPkts + ifp->ifInBcastPkts));
	printf ("(13) ifInDiscards\t%14lu\t(14) ifInErrors\t\t%14lu\n", (long) ifp->ifInDiscards, (long) ifp->ifInErrors);
	printf ("(15) ifInUnknownProtos\t%14lu\t(16) ifOutOctets\t%14lu\n", /* (long) ifp->ifInUnknownProtos */ (long) 0L, (long) ifp->ifOutOctets);
	printf ("(17) ifOutUcastPkts\t%14lu\t(18) ifOutNUcastPkts\t%14lu\n", (long) ifp->ifOutUcastPkts, (long) (ifp->ifOutMcastPkts + ifp->ifOutBcastPkts));
	printf ("(19) ifOutDiscards\t%14lu\t(20) ifOutErrors\t%14lu\n", (long) ifp->ifOutDiscards, (long) ifp->ifOutErrors);
	printf ("(21) ifOutQlen\t\t%14u\n", len_q (ifp->outq));

	if (ifp->address[AF_INET].sa_family == AF_INET) {
		printf ("\n( 1) ifAdEntAddr\t%14s\t( 2) ifAdEntIfIndex\t%14u\n", snhtoa (&ifp->address[AF_INET]), ifp->ifIndex);
		printf ("( 3) ifAdEntNetMask    %15s\t( 4) ifEntBcastAddr    %15s\n", inet_ntoa (ifp->netmask[AF_INET]), snhtoa (&ifp->broadcast[AF_INET]));
		printf ("( 5) ifAdEntReasmMaxSize%14u\n", MAX_UINT16);
	}
	return 0;
}

/* ************************************************************************* */
/*
 *  Function: piface
 *
 *  Display the information for a device or circuit.
 *
 *  Parameters:
 *    "ifp" is a pointer to the interface
 *    "mode" is non-zero for a short display
 *
 *  Returns: (none)
 *
 */
LOCAL void
piface (struct iface *ifp, int mode)
{
	char *cp1, *cp2, *cp3;

	if (ifp->flags & IFF_TESTING) {
		cp1 = "Testing";
	}
	if (!(ifp->flags & IFF_START)) {
		cp1 = "Stopped";
	}
	else if (ifp->flags & IFF_UP) {
		cp1 = "Up";
	}
	else {
		cp1 = "Down";
	}
	printf ("%-15s %-9s %-7s %5u %5u %10lu %10lu  %10s\n", ifp->name,
		((ifp->iftype == NULLIFT) ? "None set." : ifp->iftype->name),
		cp1, ifp->mtu, ifp->mru, ifp->rawsndcnt, ifp->rawrecvcnt,
		tformat (secclock () - ifp->lastactive));

	if (mode)
		return;

	/* Translate encapsulation type for IP and IPX on ethernet */
	cp1 = cp2 = cp3 = "";
	if ((ifp->iftype != NULLIFT) && (ifp->iftype->ifType == IFT_ETHERNET)) {
		cp1 = "Type";
		cp2 = type_ip (ifp->ip_type);
	}

	printf ("\nProtocol %5s  Pkts Out   Pkts In Address          Broadcast           Netmask\n", cp1);
	printf ("IP       %5s%10lu%10lu %-15s",
		cp2, ifp->ipsndcnt, ifp->iprecvcnt, snhtoa (&(ifp->address[AF_INET])));
	printf ("  %-15s  0x%08lx\n", snhtoa (&(ifp->broadcast[AF_INET])), ifp->netmask[AF_INET]);
	printf ("IPX      %5s%10lu%10lu %-33s 0x%08lx\n",
		cp3, ifp->ipxsndcnt, ifp->ipxrecvcnt, snhtoa (&(ifp->address[AF_NOVELL])),
		ifp->netmask[AF_NOVELL]);

	{
		cp1 = "Link Address";
		cp2 = cp3 = "";
		if ((ifp->iftype->format != NULL) && (ifp->hwaddr != NULLCHAR)) {
			cp2 = (*ifp->iftype->format) (ifp->hwaddr);
		}
		printf ("\n%-17s Out Queue  Out Buf  In Buf  %7s   Last Send  Last Receive\n", cp1, cp3);
		printf ("%-17s %9d  %7d  %6d  %7s  %10s    ",
			cp2, len_q (ifp->outq), ifp->outdepth, ifp->indepth,
			"",
			tformat (secclock () - ifp->lastsent));
		printf ("%10s\n", tformat (secclock () - ifp->lastrecv));
	}
}

/* ************************************************************************* */
/*
 *  Function: do_if_show
 *
 *  Display information for the device or circuit.
 *
 *  Parameters:
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is a void pointer to the interface which is null for showing all
 *
 *  Command Line: device|circuit <device|circuit> show
 *  Command Line: device|circuit show
 *
 *  Returns: 0 for success (always)
 *
 */
LOCAL int
do_if_show (int argc, char *argv[], void *p)
{
	register struct iface *ifp = (struct iface *) p;
	printf ("%-15s Protocol  Status    MTU   MRU   Pkts Out    Pkts In        Idle\n", "Device");

	if (ifp == NULLIF) {
		/* Display all the interfaces */
		for (ifp = Ifaces; ifp != NULLIF; ifp = ifp->next) {
			piface (ifp, 1);
		}
		return 0;
	}
	/* Just the name, show the full interface information */
	piface (ifp, 0);

	if (argc > 1) {
		printf ("\nFlags %x Trace %x\n", ifp->flags, ifp->trace);
	}

	if (ifp->ioshow != NULLVFP) {
		(*ifp->ioshow) (ifp);
	}
	/* Call active encapsulation show routine, if any */
	if ((ifp->iftype != NULLIFT) && (ifp->iftype->show != NULLVFP)) {
		(*ifp->iftype->show) (ifp);
	}
	return 0;
}

/* ************************************************************************* */
/*
 *  Function: do_if_start
 *
 *  Start the device or circuit.
 *
 *  Parameters:
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is a void pointer to the interface
 *
 *  Command Line: device|circuit <device|circuit> start
 *
 *  Returns: 0 for success (always)
 *
 */
LOCAL int
do_if_start (int argc, char *argv[], void *p)
{
	register struct iface *ifp = (struct iface *) p;

	ifp->flags |= IFF_START | IFF_UP;
	ifp->LastChange = secclock ();
	rt_update ();
	return 0;
}

/* ************************************************************************* */
/*
 *  Function: do_if_stop
 *
 *  Stop the device or circuit.
 *
 *  Parameters:
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is a void pointer to the interface
 *
 *  Command Line: device|circuit <device|circuit> stop
 *
 *  Returns: 0 for success (always)
 *
 */
LOCAL int
do_if_stop (int argc, char *argv[], void *p)
{
	register struct iface *ifp = (struct iface *) p;

	ifp->flags &= ~(IFF_START | IFF_UP | IFF_TESTING);
	ifp->LastChange = secclock ();
	rt_update ();
	return 0;
}

/* ************************************************************************* */
/*
 *  Function: do_dev_attach
 *
 *  Attach a device.
 *
 *  Parameters:
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is a void pointer to the interface or null if does not exist
 *
 *  Command Line: device <device> attach ...
 *
 *  Returns: 0 for success
 *           else error
 *
 */
LOCAL int
do_dev_attach (int argc, char *argv[], void *p)
{
	extern const struct cmds Attab[];
	register struct iface *ifp = (struct iface *) p;

	if (ifp != NULLIF) {
		printf ("Device already exists: %s\n", ifp->name);
		return 1;
	}
	/* Set pointer to interface name and process command */
	if (subcmd (Attab, argc, argv, argv[ -1]))
		return 1;

	return 0;
}

/* ************************************************************************* */
/*
 *  Function: do_dev_inbuf
 *
 *  Set or display the input queue depth for the device.
 *
 *  Parameters:
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is a void pointer to the interface
 *
 *  Command Line: device|circuit <device|circuit> inbuf [+/- change]
 *
 *  Returns: 0 for success
 *           else error
 *
 */
LOCAL int
do_dev_inbuf (int argc, char *argv[], void *p)
{
	struct iface *ifp = (struct iface *) p;
	sint15 depth, change;

	if (argc < 2) {
		printf ("Input buffers: %d\n", ifp->indepth);
	}
	else {
		if (atoi16s_err (argv[1], &change))
			return 1;

		depth = ifp->indepth + change;
		if (depth < 0)
			depth = 0;
		if (depth > 50)
			depth = 50;
		change = depth - ifp->indepth;

		ifp->indepth = depth;
		Nibufs_iface += change;
	}
	return 0;
}

/* ************************************************************************* */
/*
 *  Function: do_dev_outbuf
 *
 *  Set or display the output queue depth for the device.
 *
 *  Parameters:
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is a void pointer to the interface
 *
 *  Command Line: device|circuit <device|circuit> outbuf [+/- change]
 *
 *  Returns: 0 for success
 *           else error
 *
 */
LOCAL int
do_dev_outbuf (int argc, char *argv[], void *p)
{
	struct iface *ifp = (struct iface *) p;
	sint15 depth, change;

	if (argc < 2) {
		printf ("Output buffers: %d\n", ifp->outdepth);
	}
	else {
		if (atoi16s_err (argv[1], &change))
			return 1;

		depth = ifp->outdepth + change;
		if (depth < 0)
			depth = 0;
		if (depth > 50)
			depth = 50;
		change = depth - ifp->outdepth;

		ifp->outdepth = depth;
		Nibufs_iface += change;
	}
	return 0;
}

/* ************************************************************************* */
/*
 *  Function: do_dev_linkaddr
 *
 *  Set or display the hardware line address for the device.  This does
 *  not actually change the address in the hardware.
 *
 *  Parameters:
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is a void pointer to the interface
 *
 *  Command Line: device|circuit <device|circuit> linkaddr [link addr]
 *
 *  Returns: 0 for success
 *           else error
 *
 */
LOCAL int
do_dev_linkadr (int argc, char *argv[], void *p)
{
	struct iface *ifp = (struct iface *) p;

	if (argc < 2) {
		printf ("Hardware link address: %s\n", (((ifp->iftype->format != NULL) && (ifp->hwaddr != NULLCHAR)) ? ((*ifp->iftype->format) (ifp->hwaddr)) : "None."));
	}
	else {
		if ((ifp->iftype == NULLIFT) || (ifp->iftype->scan == NULL) ||
			(ifp->iftype->ifType == IFT_ETHERNET)) {
			printf ("Can't set link address for device\n");
			return 1;
		}
		free (ifp->hwaddr);
		ifp->hwaddr = (char *) mallocw (ifp->iftype->hwalen);
		return (*ifp->iftype->scan) (argv[1], ifp->hwaddr);
	}
	return 0;
}

/* ************************************************************************* */
/*
 *  Function: do_ioctl
 *
 *  Perform ioctl operation on the device.
 *
 *  Parameters:
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is a void pointer to the interface
 *
 *  Command Line: dev <dev> ioctl <param> [value]
 *
 *  Returns: 0 for success
 *           else error
 *
 */
LOCAL int
do_ioctl (int argc, char *argv[], void *p)
{
	struct iface *ifp = (struct iface *) p;
	int param;

	/* Map the param string to a number. */
	if ((param = devparam (argv[1])) == -1) {
		printf ("Unknown paramameter: %s\n", argv[1]);
		return 1;
	}

	if (ifp->ioctl != NULL) {
		if (argc > 2) {
			sint31 x;

			if (atoi32s_err (argv[2], &x))
				return 1;
			(*ifp->ioctl) (ifp, param, TRUE, x);
		}
		else
			printf ("%s %s is set to: %2lx\n", ifp->name, argv[1],
				(long) (*ifp->ioctl) (ifp, param, FALSE, 0));
	}

	return 0;
}

/* ************************************************************************* */
/*
 *  Command Table: device <device> ...
 *
 */
static const struct cmds Devcmds[] = {
	{"attach",		do_dev_attach,		0,	0,	NULLCHAR},
	{"detach",		do_if_detach,		0,	0,	""},
	{"encap",		do_if_encap,		0,	0,	"[protocol]"},
	{"inbuf",		do_dev_inbuf,		0,	0,	"[+/- change]"},
	{"ioctl",		do_ioctl,			0,	2,	"<param> [value]"},
	{"ip",			do_if_ip,			0,	0,	NULLCHAR},
	{"linkaddress",	do_dev_linkadr,		0,	0,	"[link addr]"},
	{"mib",			do_if_mib,			0,	0,	""},
	{"mtu",			do_if_mtu,			0,	0,	"[bytes]"},
	{"outbuf",		do_dev_outbuf,		0,	0,	"[+/- change]"},
	{"show",		do_if_show,			0,	0,	""},
	{"start",		do_if_start,		0,	0,	""},
	{"stop",		do_if_stop,			0,	0,	""},
	{NULLCHAR},
};

/* ************************************************************************* */
/*
 *  Function: do_device
 *
 *  Perform configuration of a device.
 *
 *  Parameters:
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is an unused pointer
 *
 *  Command Line: device ...
 *
 *  Returns: 0 for success
 *           else error
 *
 */
ENTRY int
do_device (int argc, char *argv[], void *p)
{

	if (ifacecmd ((IFACECMD_EXIST | IFACECMD_SHOW | IFACECMD_ATTACH | IFACECMD_DEVICE), Devcmds, argc, argv, p))
		return 1;

	return 0;
}
