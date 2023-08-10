
/* ************************************************************************* */
/*
 *	enet.h
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
 *  Define the generic ethernet constants and structures.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 19:38:37  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _DEV_ENET_H
#define _DEV_ENET_H

#define	EADDR_LEN	6

/* Host byte order format of an ethernet header */
struct ether {
	char dest[EADDR_LEN];
	char source[EADDR_LEN];
	uint16 type;
};

#define	ETHERLEN	14

/* Ethernet broadcast address */
extern char Ether_bdcst[];

/* Ethernet type fields */
#define	ETHER_TYPE_IP				0x0800		/* Type field for IP */
#define	ETHER_TYPE_ARP				0x0806		/* Type field for ARP */
#define	ETHER_TYPE_REVARP			0x8035		/* Type field for reverse ARP */
#define ETHER_TYPE_IPX				0x8137		/* Type field for ECONFIGED IPX */
#define MAX_8023_LENGTH				0x05EE		/* Largest size 802.3 packet used in Ethernet type field */

#define ETHER_TYPE_PPPOE_DISCOVERY	0x8863		/* Type field for PPPoE discovery phase */
#define ETHER_TYPE_PPPOE_SESSION	0x8864		/* Type field for PPPoE session phase */

#define	RUNT			60			/* smallest legal size packet, no fcs */
#define	GIANT			1514		/* largest legal size packet, no fcs */

#define	MAXTRIES		16			/* Maximum number of transmission attempts */

#endif /* _DEV_ENET_H */
