
/* ************************************************************************* */
/*
 *	arp.h
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

#ifndef _IP_ARP_H
#define _IP_ARP_H

/* Lifetime of a valid ARP entry */
#define	ARPLIFETIME	900	/* 15 minutes */
/* Lifetime of a pending ARP entry */
#define	ARPPENDTIME	5	/* 15 seconds */

/* ARP definitions (see RFC 826) */

#define	ARPLEN		16	/* Size of ARP hdr, minus hardware addresses */

/* Address size definitions */
#define	IPALEN		4	/* Length in bytes of an IP address */
#define MAXHWALEN	16	/* Maximum length of a hardware address */

/* ARP opcodes */
#define	ARP_REQUEST	1
#define	ARP_REPLY	2
#define	REVARP_REQUEST	3
#define	REVARP_REPLY	4

/* Hardware types */
#define	ARP_NETROM	0	/* Fake for NET/ROM (never actually sent) */
#define	ARP_ETHER	1	/* Assigned to 10 megabit Ethernet */
#define	ARP_EETHER	2	/* Assigned to experimental Ethernet */
#define	ARP_AX25	3	/* Assigned to AX.25 Level 2 */
#define	ARP_PRONET	4	/* Assigned to PROnet token ring */
#define	ARP_CHAOS	5	/* Assigned to Chaosnet */
#define	ARP_IEEE802	6	/* Who uses this? */
#define	ARP_ARCNET	7
#define	ARP_APPLETALK	8
#define	NHWTYPES 9

/* Format of an ARP request or reply packet. From p. 3 */
struct arp {
	uint16 hardware;			/* Hardware type */
	uint16 protocol;			/* Protocol type */
	char hwalen;			/* Hardware address length, bytes */
	char pralen;			/* Length of protocol address */
	uint16 opcode;			/* ARP opcode (request/reply) */
	char shwaddr[MAXHWALEN];	/* Sender hardware address field */
	sint31 sprotaddr;		/* Sender Protocol address field */
	char thwaddr[MAXHWALEN];	/* Target hardware address field */
	sint31 tprotaddr;		/* Target protocol address field */
};

/* Format of ARP table */
struct arp_tab {
	struct arp_tab *next;	/* Doubly-linked list pointers */
	struct arp_tab *prev;
	struct timer timer;	/* Time until aging this entry */
	struct mbuf *pending;	/* Queue of datagrams awaiting resolution */
	struct sockaddr target;	/* Target address */
	struct iface *iface;	/* Interface corresponding to request */
	char state;		/* (In)complete */
#define	ARP_PENDING	0
#define	ARP_VALID	1
	char pub;		/* Respond to requests for this entry? */
	char *hw_addr;		/* Hardware address */

	char ipNetToMediaType;	/* Method ARP entry was made */
#define ANM_OTHER	1
#define ANM_INVALID	2
#define ANM_DYNAMIC	3
#define ANM_STATIC	4
};
#define	NULLARP	(struct arp_tab *)0
extern struct arp_tab *Arp_tab[];

struct arp_stat {
	uint32 recv;		/* Total number of ARP packets received */
	uint32 badtype;	/* Incoming requests for unsupported hardware */
	uint32 badlen;	/* Incoming length field(s) didn't match types */
	uint32 badaddr;	/* Bogus incoming addresses */
	uint32 inreq;		/* Incoming requests for us */
	uint32 replies;	/* Replies sent */
	uint32 outarp;	/* Outgoing arp requests sent */
	uint32 rarpout;	/* Outgoing rarp requests sent */
	uint32 rarpreq;	/* Incomming rarp requests processed */
	uint32 rarprep;	/* Incoming rarp replies for us */
};
extern struct arp_stat Arp_stat;

extern struct iface *Rarpifp;

#endif /* _IP_ARP_H */
