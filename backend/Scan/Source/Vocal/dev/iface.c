
/* ************************************************************************* */
/*
 *	iface.c
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
 *  Interface support routines.
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

#include "net/net.h"
#include "sys/sys.h"
#include "dev/dev.h"

#include "ip/ip.h"

#include "dev/local.h"

#include "term/term.h"

#include "trace/trace.h"
#include "wan/wan.h"

/* ************************************************************************* */

extern struct mbuf *Hopper;

/* Interface list header */
struct iface *Ifaces = NULLIF;

/* Interface sequence number */
uint16 ifNumber = 0;

/* Loopback pseudo-interface.
 * This isn't a real interface, it just bounces the packet back. */
struct iface *Loopback = NULLIF;

ENTRY void
iface_init (void)
{
	Ifaces = NULLIF;
	ifNumber = 0;
	Loopback = NULLIF;

}

/* ************************************************************************* */
/*
 *  Process: if_tx
 *
 * 	General purpose interface transmit task, one for each device that can
 *  send datagrams. It waits on the interface's output queue (outq),
 *  extracts datagrams placed there in priority order by if_send (),
 *  and sends them to the device's send routine.
 *
 *  Parameters:
 *    "dev" is the device index (not used)
 *    "p1" is a void interface pointer
 *    "p2" is an unused pointer
 *
 *  Started By: setencap
 *
 *  Terminated By: alert -1 or ifp->txproc == NULLPROC
 *
 */
ENTRY void
if_tx (int dev, void *p1, void *p2)
{
	struct iface *ifp = (struct iface *) p1;
	struct mbuf *bp;

	do {
		/* Wait for a packet on the queue */
		while (ifp->outq == NULLBUF && ifp->txproc != NULLPROC) {
			if (pwait (&ifp->outq) != 0) {
				/* Killed by signal. */
				ifp->txproc = NULLPROC;
			}
		}

		/* Process was killed, so skip the rest */
		if (ifp->txproc == NULLPROC)
			continue;

		/* Not killed, process the input packet */
		bp = dequeue (&ifp->outq);
		ifp->outdepth++;

		if ((*ifp->iosend) (ifp, bp) == -1) {
			ifp->txproc = NULLPROC;
		}
		else {
			/* Let other tasks run, just in case send didn't block */
			pwait (NULL);
		}
	} while (ifp->txproc != NULLPROC);
}

/* ************************************************************************* */
/*
 *  Function: iface_garbage
 *
 *  Perform garbage colection on the hopper when memory is low.
 *
 *  Parameters:
 *    "red" is nonzero when significant memory shortage exists.
 *
 *  Returns: (none)
 *
 */
ENTRY void
iface_garbage (int red)
{
	struct mbuf *bp;
	int count;

	for (count = (red ? 2 : 1); count > 0; count--) {
		bp = NULLBUF;
		network_nested_interrupt_disable ();
		if (Hopper != NULLBUF) {
			bp = dequeue (&Hopper);
		}
		network_nested_interrupt_restore ();
		if (bp != NULLBUF)
			free_p (bp);
	}
}

/* ************************************************************************* */
/*
 *  Function: if_send
 *
 *  Put a packet on the interface output queue.
 *
 *  Parameters:
 *    "ifp" is a pointer to the interface structure for the device
 *    "bp" is a pointer to a packet structure
 *
 *  Command Line: x x x
 *
 *  Returns: (none)
 *  Returns: 0 for success always
 *  Returns: 0 for success
 *           else error
 *
 */
/* Put a packet on output queue */
ENTRY int
if_send (struct iface *ifp, struct mbuf *bp, void *unused)
{
	struct mbuf *tbp, *tlast;

	if (ifp == NULLIF) {
		free_p (bp);
		return -1;
	}

	/* Check the number of packets already on the queue.
	 */
	if (ifp->outdepth < 1) {
		ifp->ifOutDiscards++;
		free_p (bp);
		return -1;
	}
	ifp->outdepth--;

	/* Search the queue looking for the first packet with precedence
	 * lower than our packet
	 */
	tlast = NULLBUF;
	for (tbp = ifp->outq; tbp != NULLBUF; tlast = tbp, tbp = tbp->qnext) {
		if (bp->priority > tbp->priority) {
			break;				/* Add it just before tbp */
		}
	}
	bp->qnext = tbp;
	if (tlast == NULLBUF) {
		/* First on queue */
		ifp->outq = bp;
	}
	else {
		tlast->qnext = bp;
	}

	psignal (&ifp->outq, 1);

	/* Bump the last active timer for non-maintanence packets */
	if (bp->priority & 1)
		ifp->lastactive = secclock ();
	return 0;
}

/* ************************************************************************* */
/*
 *  Process: x
 *
 *  description
 *
 *  Parameters:
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is an unused pointer
 *
 *  Started By: x
 *
 *  Terminated By: (never)
 *
 */
/* Process packets in the Hopper.  These are packets that were grabbed off
 * the raw interface and stuck on a central queue.  This code is the
 * multiplexer.
 * None of these variables are used. */
ENTRY void
network (int i, void *v1, void *v2)
{
	struct mbuf *bp;
	const struct iftype *ift;
	struct iface *ifp;

loop:
	refiq ();					/* Replenish interrupt buffer pool */

	/* Just wait in this loop until a packet arrives in the Hopper. */
	for (;;) {
		network_nested_interrupt_disable ();
		bp = Hopper;
		if (bp != NULLBUF) {
			bp = dequeue (&Hopper);
			network_nested_interrupt_restore ();
			break;
		}
		network_nested_interrupt_restore ();
		pwait (&Hopper);
	}

	/* Process the input packet */
	pullup (&bp, (char *) &ifp, sizeof (ifp));
	if (ifp != NULLIF) {
		/* Real interface, update the stats. */
		ifp->indepth++;
		ifp->rawrecvcnt++;
		ifp->lastrecv = secclock ();
		ift = ifp->iftype;
	}
	else {
		/* Loop back packet. */
		ift = &Iftypes[0];
	}
	dump (ifp, IF_TRACE_IN, bp);

	/* Give the packet to the type specific recieve function. */
	if (ift->incoming != NULLVFP) {
		(*ift->incoming) (ifp, bp);
	}
	else {
		free_p (bp);			/* Nowhere to send it */
	}
	/* Let everything else run - this keeps the system from wedging
	 * when we're hit by a big burst of packets
	 */
	pwait (NULL);
	goto loop;					/* Nasty, Nasty goto :-P */
}

/* ************************************************************************* */
/*
 *  Function: x
 *
 *  description
 *
 *  Parameters:
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is an unused pointer
 *
 *  Command Line: x x x
 *
 *  Returns: (none)
 *  Returns: 0 for success always
 *  Returns: 0 for success
 *           else error
 *
 */
/* Put an interface-mbuf into the Hopper for network_task to deal with.
 *
 * IFP is the interface that is going to deal with the data in the mbuf.
 * BP is the mbuf to be delt with.
 *
 * Returns 0 if OK. */
ENTRY int
net_route (struct iface *ifp, struct mbuf *bp)
{

	/* Check the number of packets already on the queue
	 * from this interface.
	 */
	if ((ifp != NULLIF) && (ifp != Loopback) && (ifp->indepth < 1)) {
		ifp->ifInDiscards++;
		free_p (bp);
		return -1;
	}
	if (ifp != NULLIF) {
		ifp->indepth--;
	}

	/* Prepend the interface pointer to the beginning of the packet. */
	pushdown (&bp, sizeof (ifp));
	memcpy (&bp->data[0], (char *) &ifp, sizeof (ifp));
	/* Stick it on the queue. */
	enqueue (&Hopper, bp);
	return 0;
}

/* ************************************************************************* */
/*
 *  Function: x
 *
 *  description
 *
 *  Parameters:
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is an unused pointer
 *
 *  Command Line: x x x
 *
 *  Returns: (none)
 *  Returns: 0 for success always
 *  Returns: 0 for success
 *           else error
 *
 */
/* Raw network input routine for packets without link-level header.
 * These are for packets off the network or from the internal interfaces.
 *
 * IFACE is the interface that this packet come in on.
 * BP is the ip packet */
ENTRY void
net_proc (struct iface *ifp, struct mbuf *bp)
{

	switch (bp->b_type) {
	case PT_IP:
	case PT_IP_8022:
	case PT_IP_SNAP:
		ip_route (ifp, bp, 0);
		break;
	default:
		net_log (-1, "Dropping packet type %d", bp->b_type);
		free_p (bp);
		break;
	}
}

/* ************************************************************************* */
/*
 *  Function: x
 *
 *  description
 *
 *  Parameters:
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is an unused pointer
 *
 *  Command Line: x x x
 *
 *  Returns: (none)
 *  Returns: 0 for success always
 *  Returns: 0 for success
 *           else error
 *
 */
/* Function to set encapsulation mode.
 *
 * IFP is the interface to be changed.
 * MODE is the ascii name of the encapsulaton mode.
 *
 * Return 0 if everything went ok, else -1.
 */
ENTRY int
setencap (struct iface *ifp, char *mode)
{
	const struct iftype *ift;
	char *ifn;

	alert (ifp->rxproc, -1);
	alert (ifp->txproc, -1);
	pwait (NULL);

	/* Call encapsulation suspend routine, if any */
	if ((ifp->iftype != NULLIFT) && (ifp->iftype->suspend != NULLVFP)) {
		(*ifp->iftype->suspend) (ifp);
	}

	ifp->iftype = NULLIFT;

	/* Scan the known names of encapsulation modes. */
	for (ift = &Iftypes[0]; ift->name != NULLCHAR; ift++)
		if (strnicmp (ift->name, mode, strlen (mode)) == 0)
			break;
	if (ift->name == NULLCHAR) {
		return -1;
	}
	/* Found it */
	ifp->iftype = ift;

	if (ifp->mru < ifp->mtu) {
		ifp->mru = ifp->mtu;
	}

	/* Start encapsulation processes only for devices not for circuits */
		{

		{
			free (ifp->hwaddr);
			if (ift->hwalen > 0)
				ifp->hwaddr = (char *) mallocw (ift->hwalen);
			else
				ifp->hwaddr = NULLCHAR;
		}

		ifp->txproc = newproc (ifn = if_name (ifp, " out"), 320, if_tx, ifp->dev, ifp, NULL, 0);
		free (ifn);

		ifp->lastactive = secclock ();	/* Bump time so it will not idle immediately */

		/* Start the encapsulation assuming attach routine will be called
		 * by start routine if and only if it is necessary. */
		if (ift->start != NULLFP) {
			return (*ift->start) (ifp);
		}
	}
	return 0;
}

/* ************************************************************************* */
/*
 *  Function: x
 *
 *  description
 *
 *  Parameters:
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is an unused pointer
 *
 *  Command Line: x x x
 *
 *  Returns: (none)
 *  Returns: 0 for success always
 *  Returns: 0 for success
 *           else error
 *
 */
/* Detach (and free) a specified interface.
 * IFP is the interface to be detached.
 *   If an error occurs, the structure is left unchanged.
 * Return 0 for detached, -1 for error. */
ENTRY int
if_detach (struct iface *ifp)
{
	struct iface *iftmp;
	int i, j;

	/* Cant detach the encapsalation or loopback interfaces. */

	if (ifp == Loopback) {
		return -1;
	}

	/* Drop all routes that point to this interface */
	{
		struct route *rp, *rptmp;

		for (j = 0; j < AF_IFCMAX; j++) {
			/* Process the default route */
			if (Route_default[j].iface == ifp)
				rt_drop (&Route_default[j].target, 0L, ifp);
			/* Process all other routes */
			for (i = 0; i < HASHMOD; i++) {
				for (rp = Routes[j][i]; rp != NULLROUTE; rp = rptmp) {
					/* Save next pointer in case we delete this entry */
					rptmp = rp->next;
					if (rp->iface == ifp)
						rt_drop (&rp->target, rp->netmask, rp->iface);
				}
			}
		}
	}

	/* Stop timer process if running */
	stop_timer (&ifp->timer);

	/* Remove from interface list */
	if (ifp == Ifaces) {
		Ifaces = ifp->next;
	}
	else {
		/* Search for entry just before this one
		 *(necessary because list is only singly - linked.)
		 */
		for (iftmp = Ifaces; iftmp != NULLIF; iftmp = iftmp->next)
			if (iftmp->next == ifp)
				break;
		if ((iftmp != NULLIF) && (iftmp->next == ifp))
			iftmp->next = ifp->next;
	}

	/* stop using ibufs allocated to interface. */
	Nibufs_iface -= ifp->indepth + ifp->outdepth;

	/* orderly shutdown of receive task. */
	alert (ifp->rxproc, -1);

	/* Free the connection fields. */
	free (ifp->out_name);
	free (ifp->out_password);

	/* Call all encapsulation detach routines if necessary */
	if (ifp->pppedv != NULL)
		ppp_detach (ifp);

	pwait (NULL);				/* give processes chance to shutdown */
	killproc (ifp->rxproc);
	killproc (ifp->txproc);
	killproc (ifp->supv);

	/* Call device shutdown routine, if any */
	if (ifp->iostop != NULLFP) {
		(*ifp->iostop) (ifp);
	}

	/* Free allocated memory associated with this interface */
	if (ifp->name != NULLCHAR)
		free (ifp->name);
	if (ifp->hwaddr != NULLCHAR)
		free (ifp->hwaddr);
	if (ifp->outq != NULLBUF)
		free_q (&(ifp->outq));

	/* Finally free the structure itself */
	free ((char *) ifp);
	return 0;
}

/* ************************************************************************* */
/*
 *  Function: x
 *
 *  description
 *
 *  Parameters:
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is an unused pointer
 *
 *  Command Line: x x x
 *
 *  Returns: (none)
 *  Returns: 0 for success always
 *  Returns: 0 for success
 *           else error
 *
 */
/* Attach a specified interface
 * creates the structures (avoids the old static declaration problems
 * when changing the structure) .
 *
 * NAME is the ascii name.
 *
 * Return a pointer to the interface,
 * or NULLIF if it can't be done, or is a duplicate.
 */
ENTRY struct iface *
if_attach (char *name, uint16 type)
{
	register struct iface *ifp;
	struct iface *iftmp;
	int isave;

	/* Check for insertion point in list */
	iftmp = NULLIF;
	ifp = Ifaces;
	for (; ifp != NULLIF; ifp = ifp->next) {
		if ((isave = stricmp (ifp->name, name)) == 0) {
			return NULLIF;		/* duplicate name */
		}
		else if (isave > 0) {
			break;
		}
		iftmp = ifp;
	}

	/* Create interface structure and fill in defaults */
	ifp = (struct iface *) callocw (1, sizeof (struct iface));
	if (ifp == NULL)
		return NULLIF;

	ifp->ifIndex =++ ifNumber;
	ifp->name = strdup (name);

	ifp->address[AF_INET].sa_family = AF_NONE;
	ifp->address[AF_NOVELL].sa_family = AF_NONE;

	ifp->broadcast[AF_INET].sa_family = AF_NONE;
	ifp->broadcast[AF_NOVELL].sa_family = AF_NONE;

	ifp->peeraddr[AF_INET].sa_family = AF_NONE;
	ifp->peeraddr[AF_NOVELL].sa_family = AF_NONE;

	ifp->netmask[AF_INET] = 0xffffff00L;
	ifp->netmask[AF_NOVELL] = 0xffffffffL;

	ifp->mru = MXU_DEFAULT;
	ifp->mtu = MAX_UINT16;

	ifp->flags = type | IFF_UP | IFF_START;

	{
		ifp->indepth = QIN_DEFAULT;
		ifp->outdepth = QOUT_DEFAULT;
		Nibufs_iface += ifp->indepth + ifp->outdepth;
	}
	ifp->LastChange = ifp->lastrecv = ifp->lastsent = ifp->lastactive = secclock ();

	/* Link in the interface */
	if (iftmp == NULLIF) {
		ifp->next = Ifaces;
		Ifaces = ifp;
	}
	else {
		ifp->next = iftmp->next;
		iftmp->next = ifp;
	}
	return ifp;
}

/* ************************************************************************* */
/*
 *  Function: x
 *
 *  description
 *
 *  Parameters:
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is an unused pointer
 *
 *  Command Line: x x x
 *
 *  Returns: (none)
 *  Returns: 0 for success always
 *  Returns: 0 for success
 *           else error
 *
 */
/* Given the ascii name of an interface, find the interface.
 *
 * NAME is the ascii name.
 *
 * Return a pointer to the interface, or NULLIF if it doesn't exist.*/
ENTRY struct iface *
if_lookup (char *name)
{
	register struct iface *ifp;

	for (ifp = Ifaces; ifp != NULLIF; ifp = ifp->next)
		if (stricmp (ifp->name, name) == 0)
			break;
	return ifp;
}

/* ************************************************************************* */
/*
 *  Function: x
 *
 *  description
 *
 *  Parameters:
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is an unused pointer
 *
 *  Command Line: x x x
 *
 *  Returns: (none)
 *  Returns: 0 for success always
 *  Returns: 0 for success
 *           else error
 *
 */
/* Set the address/netmask for a device along with adjusting routes to the device
 *
 *
 */
ENTRY int
if_setaddr (struct iface *ifp, struct sockaddr *address, uint32 netmask, bool broadcast)
{
	struct route *rp;
	struct sockaddr sock;

	sock = ifp->address[AF_INET];

	/* Drop the existing route to the device */
	if (sock.sa_family == AF_INET) {
		sock.sin_address &= ifp->netmask[AF_INET];

		rp = rt_exact (&sock, ifp->netmask[AF_INET], ifp);
		if (rp != NULLROUTE) {
			rt_drop (&rp->target, ifp->netmask[AF_INET], ifp);
		}
	}

	/* Drop and re-establish a new broadcast address as well */
	if (broadcast) {
		if (ifp->broadcast[AF_INET].sa_family == AF_INET) {
			rt_drop (&ifp->broadcast[AF_INET], 0xffffffffL, ifp);
		}
	}

	/* Deduce a suitable netmask if specified as zero */
	if (netmask == 0L) {
		struct sockaddr temp;

		temp = *address;
		temp.sin_address &= 0xff000000L;	/* Start mask as if Class A */
		netmask = af_subnetmask (&temp);
	}

	/* Set the new address and netmask */
	ifp->address[AF_INET] = *address;
	ifp->netmask[AF_INET] = netmask;

	/* Set the default address if device is used for the global address */
	if (ifp->flags & IFF_GLOBAL) {
		Default_addr[AF_INET] = *address;
	}

	/* Also set the default address if it is not set yet */
	if ((Default_addr[AF_INET].sa_family != AF_INET) || (Default_addr[AF_INET].sin_address == 0L)) {
		Default_addr[AF_INET] = *address;
	}

	/* Add route to the device, no gateway, 0 metric-hop, 0 time to live, private */
	rt_add (&ifp->address[AF_INET], ifp->netmask[AF_INET], NULL, ifp, 1, 0, 0, 0L, 1);

	/* Re-establish a new broadcast address and route */
	if (broadcast) {
		ifp->broadcast[AF_INET].sa_family = AF_INET;
		ifp->broadcast[AF_INET].sin_address = address->sin_address | ~netmask;
		rt_add (&ifp->broadcast[AF_INET], 0xffffffffL, NULL, ifp, 1, 0, 0, 0L, 1);
	}

	return 0;
}

/* ************************************************************************* */
/*
 *  Function: x
 *
 *  description
 *
 *  Parameters:
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is an unused pointer
 *
 *  Command Line: x x x
 *
 *  Returns: (none)
 *  Returns: 0 for success always
 *  Returns: 0 for success
 *           else error
 *
 */
/* Return iface pointer if ADDR belongs to one of our interfaces,
 * NULLIF otherwise.
 * This is used to tell if an incoming packet is for us, or if it
 * has to be routed. */
ENTRY int
ismyaddr (struct sockaddr *addr)
{
	register struct iface *ifp;

	switch (addr->sa_family) {
	case AF_INET:
		/* IP */
		for (ifp = Ifaces; ifp != NULLIF; ifp = ifp->next) {
			if (inet_hostmatch (addr, &(ifp->address[AF_INET])))
				break;
		}
		return ((ifp != NULLIF) || inet_hostsame (addr, &Default_addr[AF_INET]));
	default:;
	}
	return 0;
}

/* ************************************************************************* */
/*
 *  Function: x
 *
 *  description
 *
 *  Parameters:
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is an unused pointer
 *
 *  Command Line: x x x
 *
 *  Returns: (none)
 *  Returns: 0 for success always
 *  Returns: 0 for success
 *           else error
 *
 */
/* Return iface pointer if the net portion of ADDR belongs to one of our
 * interfaces,
 * NULLIF otherwise.
 *
 * This is used to tell if ripx entries, which are network only,
 *   match one of our interfaces which is directly attached to us. */
ENTRY int
ismynet (struct sockaddr *addr)
{
	register struct iface *ifp;

	switch (addr->sa_family) {
	case AF_INET:
		/* IP */
		for (ifp = Ifaces; ifp != NULLIF; ifp = ifp->next) {
			if (inet_hostmatch (addr, &(ifp->address[AF_INET])))
				break;
		}
		return ((ifp != NULLIF) || inet_hostsame (addr, &Default_addr[AF_INET]));
	default:;
	}
	return 0;
}

/* ************************************************************************* */
/*
 *  Function: x
 *
 *  description
 *
 *  Parameters:
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is an unused pointer
 *
 *  Command Line: x x x
 *
 *  Returns: (none)
 *  Returns: 0 for success always
 *  Returns: 0 for success
 *           else error
 *
 */
/* Concatenate the name of an interface with a arbitrary string and return
 * it as a new string.  One use for this would be error / diagnostic messages
 * for a perticular interface.
 *
 * IFP is the interface to get the name from.
 * COMMENT is the string to be appended to the name.
 *
 * return The name + comment as a new string.  This routine could block. */
ENTRY char *
if_name (struct iface *ifp, char *comment)
{
	char *result;

	result = (char *) mallocw (strlen (ifp->name) + strlen (comment) + 1);
	strcpy (result, ifp->name);
	strcat (result, comment);
	return result;
}

/* ************************************************************************* */
/*
 *  Function: x
 *
 *  description
 *
 *  Parameters:
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is an unused pointer
 *
 *  Command Line: x x x
 *
 *  Returns: (none)
 *  Returns: 0 for success always
 *  Returns: 0 for success
 *           else error
 *
 */
/* Raw output routine that tosses all packets. Used by dialer, tip, etc.
 *
 * IFP isn't used.
 * BP is the packet to be ignored.  It get's freed by this routine.
 *
 * Return 0. */
ENTRY int
bitbucket (struct iface *ifp, struct mbuf *bp, void *unused)
{
	ifp->ifOutDiscards++;
	free_p (bp);
	return 0;
}
