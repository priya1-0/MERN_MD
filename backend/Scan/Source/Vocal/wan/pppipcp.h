
/* ************************************************************************* */
/*
 *	pppipcp.h
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
 *	Module:		WAN
 *
 *	This file contains the PPP IPCP delcarations.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 20:56:09  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _WAN_PPPIPCP_H
#define _WAN_PPPIPCP_H

#define IPCP_REQ_TRY	20		/* REQ attempts */
#define IPCP_NAK_TRY	10		/* NAK attempts */
#define IPCP_TERM_TRY	10		/* tries on TERM REQ */
#define IPCP_TIMEOUT	3		/* Seconds to wait for response */

/* IPCP option types */
#define IPCP_2ADDRESSES		 1
#define IPCP_COMPRESS		 2
#define IPCP_1ADDRESS		 3
#define IPCP_OPTION_LIMIT	 3	/* highest # we can handle */

#define IPCP_N_2ADDRESSES	(1 << IPCP_2ADDRESSES)
#define IPCP_N_COMPRESS		(1 << IPCP_COMPRESS)
#define IPCP_N_1ADDRESS		(1 << IPCP_1ADDRESS)

/* Extended IPCP option types */
#define IPCP_EXTENDED_OPTIONS	128
#define IPCP_PRIMARY_DNS		129
#define IPCP_PRIMARY_NBNS		130
#define IPCP_SECONDARY_DNS		131
#define IPCP_SECONDARY_NBNS		132
#define IPCP_EXTENDED_LIMIT		132	/* highest # we can handle */

#define IPCP_N_PRIMARY_DNS		(1 << (IPCP_PRIMARY_DNS - IPCP_EXTENDED_OPTIONS + 8))
#define IPCP_N_PRIMARY_NBNS		(1 << (IPCP_PRIMARY_NBNS - IPCP_EXTENDED_OPTIONS + 8))
#define IPCP_N_SECONDARY_DNS	(1 << (IPCP_SECONDARY_DNS - IPCP_EXTENDED_OPTIONS + 8))
#define IPCP_N_SECONDARY_NBNS	(1 << (IPCP_SECONDARY_DNS - IPCP_EXTENDED_OPTIONS + 8))

/* Table for IPCP configuration requests */
struct ipcp_value_s {
	uint32 address;			/* address for this side */
	uint32 other;			/* address for peer side */

	uint16 compression;		/* Compression protocol */
	uint16 slots;			/* Slots (0-n)*/
	uint8 slot_compress;	/* Slots may be compressed (flag)*/

	uint32 primary_dns_address;		/* Primary DNS address */
	uint32 secondary_dns_address;	/* Secondary DNS address */

};

#define IPCP_SLOT_DEFAULT	16	/* Default # of slots */
#define IPCP_SLOT_HI		64	/* Maximum # of slots */
#define IPCP_SLOT_LO 		 1	/* Minimum # of slots */
#define IPCP_SLOT_COMPRESS	0x01	/* May compress slot id */

/* Idiosyncrases:
 *	local.want.other	stores copy of assigned address.
 *	local.work.other	used by the 2addresses negotiation only.
 *
 *	remote.want.other	stores copy of assigned address.
 *	remote.work.other	used by the 2addresses negotiation only.
 */

/* IPCP control block */
struct ipcp_pdv_s {
	struct slcompress *slhcp;	/* pointer to compression block */
	uint32	save_local_address;
	uint32	save_remote_address;
	uint32	save_global_address;
};

#endif /* _WAN_PPPIPCP_H */
