
/* ************************************************************************* */
/*
 *	iface.h
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
 *  Define interface data structures.
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

#ifndef _DEV_IFACE_H
#define _DEV_IFACE_H

#include "net/net.h"

#include "term/chat.h"

#include "sys/mbuf.h"

struct iface;

/* Packet driver interface classes */
enum classes {
	CL_NONE = 0,
	CL_ETHERNET,
	CL_PRONET_10,
	CL_IEEE8025,
	CL_OMNINET,
	CL_APPLETALK,
	CL_SLIP,
	CL_STARLAN,
	CL_ARCNET,
	CL_AX25,
	CL_KISS,
	CL_IEEE8023,
	CL_FDDI,
	CL_INTERNET_X25,
	CL_LANSTAR,
	CL_SLFP,
	CL_NETROM,
	CL_PPP,
	CL_QTSO,
	CL_NCLASS
};

/* Packet types -- used to define actual contents of mbuf:
 * < 18   used by packet drivers
 * > 32     used by PPP  (See ppp.h PPP_IP_PROTOCOL and beyond)
 * > 1500   used by ethernet
 */
enum ptypes {
	PT_STREAM = CL_NCLASS,
	PT_IP,
	PT_IPX,
	PT_IPXHC,
	PT_IP_8022,
	PT_IP_SNAP,
	PT_IP_PPPOE,
	PT_IPX_8023,
	PT_IPX_8022,
	PT_IPX_SNAP,
	PT_NTYPE
};

/* Interface encapsulation mode table entry.  An array of these structures
 * are initialized in config.c with all of the information necessary to
 * attach a device. */
struct iftype {
	uint16 ifType;				/* Type of interface */
/* ifTypes as per SNMP in RFC1573 */
#define IFT_OTHER		1		/* None of the following */
#define IFT_ETHERNET	6		/* Any speed Ethernet */
#define IFT_PPP			23		/* PPP */
#define IFT_LOOP		24		/* Software loopback */
#define IFT_SLIP		28		/* Generic SLIP */
#define IFT_RS232		33		/* Serial */
#define IFT_MODEM		48		/* Generic Modem */

#define IFT_PPPOE		1006	/* PPP over Ethernet - non-standard code assignment */
#define IFT_PKTRADIO	1007	/* Packet radio - non-standard code assignment */

	char *name;					/* Name of encapsulation technique */

	/* Set up an interface to be of the type described in this structure.
	 * IFP is the interface to set.
	 * This is called via the attach command or ppp and slip commands. */
	void (*attach) (struct iface *ifp);

	/* Remove the encapsalation from this interface.
	 * IFP is the interface to unset.
	 * Called when detaching an interface.  */
	void (*detach) (struct iface *ifp);

	/* Start the encapsalation for this interface.
	 * IFP is the interface to start.
	 * Called when starting down an interface via SETENCAP. */
	int (*start) (struct iface *ifp);

	/* Suspend the encapsalation from this interface.
	 * IFP is the interface to suspend.
	 * Called when shutting down an interface.  If changing an
	 * interface's encapsalation SETENCAP will suspend the old type
	 * for you. */
	void (*suspend) (struct iface *ifp);

	/* Level 1 "datagram level" output packet handler.
	 * This deals with outgoing packets, usually adding the level
	 * 0 header and calling IFSEND.
	 * IFP is the actual interface that this packet is going out of.
	 * BP is a datagram (medium independent) packet.
	 * PVP is the packets destination.  (Next hop) */
	int (*outgoing) (struct iface *ifp, struct mbuf *bp, void *pvp);

	/* Level 0 "link level" input packet handler.
	 * This deals with all the incoming packets from this interface.
	 * IFP is the interface that this packet came in on.
	 * BP is a level 0 packet. */
	void (*incoming) (struct iface *ifp, struct mbuf *bp);

	/* Provide I/O status encapsalation for this interface.
	 * IFP is the interface to receiving the I / O status.
	 * COMMAND is the
	 * VALUE is the
	 * Called when the status changes for an interface.  */
	void (*iostatus) (struct iface *ifp, int command, sint31 value);

	/* Perform timeout processing for this interface.
	 * IFP is the interface to receiving the timeout.
	 * Called when the timout occurs for an interface.  */
	void (*timeout) (struct iface *ifp);

	/* Display the state/statistics of this interfaces encapsalation.
	 * IFP is the interface to show. */
	void (*show) (struct iface *);

	int (*discard) (struct iface *, struct mbuf *);
	int (*echo) (struct iface *, struct mbuf *);

	/* Write packet tracing information out for this level 1 packet.
	 * OUT is the file to send the data out of.
	 * PACKET is the packet that the data is to be sent out of.
	 * CHECK is unused, so I don't know what it's for. */
	void (*trace) (struct iface *ifp, FILE * out, struct mbuf ** packet, int check);

	/* Test to see if a high level address is specificaly for here.
	 * Multicasts are examples of addresses that would fail this test.
	 * I've only seen this used in trace functions.
	 * IFACE is the interface that's dealing with this packet.
	 * PACKET is the level 1 packet to check.
	 * Return 0 for fail ! 0 for passed. */
	int (*addrtest) (struct iface * iface, struct mbuf * packet);

	/* Function that formats a link addresses (ADDR) into an ascii
	 * string. */
	char *(*format) (char *addr);

	/* Parse an ascii string (IN) into a binary link address (OUT).
	 * The reverse of format.  Return 0 if the string parsed, else ! 0. */
	int (*scan) (char *in, char *out);

	int arptype;				/* Type of ARP used by hardware */

	int hwalen;					/* Length of hardware address, if any */

	char *broadcast;			/* Broadcast hardware address, if any */
};

#define	NULLIFT	(struct iftype *) 0

extern const struct iftype Iftypes[];	/* All the known types of interfaces. */

/* Interface control structure.  This actually describes each individual
 * interface that gets attached. */
struct iface {
	struct iface *next;			/* Linked list pointer */
	uint16 ifIndex;				/* Unique value for each interface */
	const char *ifDescr;		/* Description of interface hardware */
	char *name;					/* Ascii string with user assigned interface name. */

	struct sockaddr address[AF_IFCMAX];		/* Address */
	struct sockaddr broadcast[AF_IFCMAX];	/* Broadcast address */
	uint32 netmask[AF_IFCMAX];	/* Network mask */
	struct sockaddr peeraddr[AF_IFCMAX];	/* Peer address, if assigned */

	uint16 mru;					/* Maximum receive unit size */
	uint16 mtu;					/* Maximum transmission unit size */
#define MXU_DEFAULT	1500		/* default for both MRU and MTU */
#define MXU_MINIMUM	 576		/* minimum for both MRU and MTU */
#define MTU_SLIP	1006		/* SLIP default for MTU */

	uint16 flags;				/* Configuration flags */
#define IFF_DYNAMIC	0x0001		/* address dynamically assigned */
#define IFF_PEER	0x0002		/* peer address assigned by command */
#define IFF_POOL	0x0004		/* peer address assigned from pool */

#define IFF_GLOBAL	0x0010		/* Global address assigned from device */

#define IFF_TESTING	0x0200		/* Interface is being tested */
#define IFF_UP		0x0400		/* Interface is ready for traffic */
#define IFF_START	0x0800		/* Interface started and available */

	uint16 trace;				/* Trace flags */
#define IF_TRACE_OUT	0x0001	/* Output packets */
#define IF_TRACE_IN	0x0010		/* Packets to me except broadcast */
#define IF_TRACE_ASCII	0x0100	/* Dump packets in ascii */
#define IF_TRACE_HEX	0x0200	/* Dump packets in hex/ascii */
#define IF_TRACE_NOBC	0x1000	/* Suppress broadcasts */
#define IF_TRACE_RAW	0x2000	/* Raw dump, if supported */
	FILE *trfp;					/* Stream to trace to */

	/* Data for connecting to an outside system. */
	struct chat *out_chat;		/* Chat script used to log in once it's dialed out. */
	char *out_name;				/* The name the outgoing connection logs in as. */
	char *out_password;			/* The password it uses. */

	struct proc *rxproc;		/* Receiver process, if any.  This gets
								 ** called every now and then to grab packets
								 ** from this interface and start them routing.
								 ** This is for interfaces that don't generate
								 ** a per packet interupt.  (Serial lines come
								 * * to mind.) */
	struct proc *txproc;		/* Send process.  This dequeues packets from
								 ** outq and sends them out the wire through
								 * * this interface. */
	struct proc *supv;			/* Supervisory process, if any.  It hangs
								 ** around drinking coffee and taking credit
								 * * for the work of other processes. */
	struct mbuf *outq;			/* Packet transmission queue. */
	sint15 outdepth;				/* # allowed packets on output queue */
#define QOUT_DEFAULT	5
	sint15 indepth;				/* # allowed packets on network queue */
#define QIN_DEFAULT	3
	sint15 balance;				/* # balance level for sharing outgoing load */
#define QBAL_DEFAULT	0

	uint16 ip_type;				/* IP ethernet encapsulation type */

	struct timer timer;			/* Timer for testing procedure */

	/* Device dependent */
	void *ddv;					/* Device dependent values, if any */
	uint16 dev;					/* Subdevice number */
	uint16 d_type;				/* Device type */
#define IFD_NONE	0
#define IFD_PACKET	1
#define IFD_ASYNC	2
#define IFD_SYNC	3

#define IFD_3C501	4			/* The following are not used */
#define IFD_DRSI	5
#define IFD_EAGLE	6
#define IFD_HAPN	7
#define IFD_HS		8
#define IFD_PC100	9
#define IFD_PI		10
#define IFD_SCC 	11
#define IFD_MDM		12			/* This one is used */

	char *hwaddr;				/* Device hardware address, if any */

	/* send mbufs to device */
	int (*iosend) (struct iface *, struct mbuf *);
	/* fetch input chars from device */
	int (*ioget) (struct iface *);
	/* Put character back on the input queue. */
	int (*iounget) (struct iface *, uint8);
	/* To device -- control */
	 sint31 (*ioctl) (struct iface *, int cmd, int set, sint31 val);
	/* Upcall from device -- when status changes */
	/* Call before detaching */
	int (*iostop) (struct iface *);
	/* Display status */
	void (*ioshow) (struct iface *);

	/* Encapsulation dependent */
	const struct iftype *iftype;	/* Pointer to appropriate iftype entry */
	void *edv;					/* Pointer to general protocol extension block, if any */
	void *pppedv;				/* Pointer to ppp protocol extension block, if any */
	void *slipedv;				/* Pointer to slip protocol extension block, if any */
	void *modemedv;				/* Pointer to modem protocol extension block, if any */
	void *decideedv;			/* Pointer to decide protocol extension block, if any */
	void *shelledv;				/* Pointer to shell protocol extension block, if any */

	/* Counters */
	uint16 attempts;			/* # of connection attempts since last success */
	uint32 ipsndcnt;			/* IP datagrams sent */
	uint32 iprecvcnt;			/* IP datagrams received */
	uint32 ipxsndcnt;			/* IPX datagrams sent */
	uint32 ipxrecvcnt;			/* IPX datagrams received */

	uint32 lastsent;			/* Clock time of last send */
	uint32 lastrecv;			/* Clock time of last receive */
	uint32 lastactive;			/* Clock time of last active (non-maintance) send */

	uint32 rawrecvcnt;			/* Raw packets received */
	uint32 ifInOctets;			/* # octets received */
	uint32 ifInUcastPkts;		/* # unicast packets */
	uint32 ifInMcastPkts;		/* # multicast packets */
	uint32 ifInBcastPkts;		/* # broadcast packets */
	uint32 ifInDiscards;		/* # discards without error */
	uint32 ifInErrors;			/* # error packets */

	uint32 rawsndcnt;			/* Raw packets sent */
	uint32 ifOutOctets;			/* # octets sent */
	uint32 ifOutUcastPkts;		/* # unicast packets */
	uint32 ifOutMcastPkts;		/* # multicast packets */
	uint32 ifOutBcastPkts;		/* # broadcast packets */
	uint32 ifOutDiscards;		/* # discards without error */
	uint32 ifOutErrors;			/* # errors on send */

	uint32 Speed;				/* current bandwidth, bits per second */

	uint32 LastChange;			/* time of last device change */
};

#define	NULLIF	(struct iface *) 0

extern uint16 ifNumber;			/* Interface sequence number */

extern struct iface *Ifaces;	/* Head of interface list. */
extern struct iface *Loopback;	/* Optional loopback interface */
extern struct iface *IP_tunnel;	/* IP-in-IP pseudo interface */

/* ************************************************************************* */

/*- MKHEADER Begin -*/

/* Global Routines: */

/* iface.c */
void iface_init (void);
void if_tx (int dev, void *p1, void *p2);
void iface_garbage (int red);
int if_send (struct iface *ifp, struct mbuf *bp, void *unused);
void network (int i, void *v1, void *v2);
int net_route (struct iface *ifp, struct mbuf *bp);
void net_proc (struct iface *ifp, struct mbuf *bp);
int setencap (struct iface *ifp, char *mode);
int if_detach (struct iface *ifp);
struct iface * if_attach (char *name, uint16 type);
struct iface * if_lookup (char *name);
int if_setaddr (struct iface *ifp, struct sockaddr *address, uint32 netmask, bool broadcast);
int ismyaddr (struct sockaddr *addr);
int ismynet (struct sockaddr *addr);
char * if_name (struct iface *ifp, char *comment);
int bitbucket (struct iface *ifp, struct mbuf *bp, void *unused);

/*- MKHEADER End -*/


/* ************************************************************************* */

#endif /* _DEV_IFACE_H */
