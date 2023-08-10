
/* ************************************************************************* */
/*
 *	udp.h
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

#ifndef _IP_UDP_H
#define _IP_UDP_H

/* SNMP MIB variables, used for statistics and control. See RFC 1066 */
extern struct mib_entry Udp_mib[];
#define	udpInDatagrams	Udp_mib[1].value.integer
#define	udpNoPorts	Udp_mib[2].value.integer
#define	udpInErrors	Udp_mib[3].value.integer
#define	udpOutDatagrams	Udp_mib[4].value.integer
#define	NUMUDPMIB	4

/* User Datagram Protocol definitions */

/* Structure of a UDP protocol header */
struct udp {
	uint16 source;	/* Source port */
	uint16 dest;	/* Destination port */
	uint16 length;	/* Length of header and data */
	uint16 checksum;	/* Checksum over pseudo-header, header and data */
};
#define	UDPHDR	8	/* Length of UDP header */

/* User Datagram Protocol control block
 * Each entry on the receive queue consists of the
 * remote socket structure, followed by any data
 */
struct udp_cb {
	struct udp_cb *next;
	struct sockaddr socket;	/* Local port accepting datagrams */
	void (*r_upcall) (struct iface *iface, struct udp_cb *, int);
				/* Function to call when one arrives */
	struct mbuf *rcvq;	/* Queue of pending datagrams */
	int rcvcnt;		/* Count of pending datagrams */
	int user;		/* User link */
};
extern struct udp_cb *Udps;	/* Hash table for UDP structures */
#define	NULLUDP	(struct udp_cb *)0

#endif /* _IP_UDP_H */
