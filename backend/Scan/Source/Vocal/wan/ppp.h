
/* ************************************************************************* */
/*
 *	ppp.h
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
 *	This file contains the PPP delcarations.
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

#ifndef _WAN_PPP_H
#define _WAN_PPP_H

struct ppp_hdr {
	uint8 addr;
#define HDLC_ALL_ADDR		0xff	/* HDLC all-station */
	uint8 control;
#define HDLC_UI			0x03	/* HDLC Unnumbered Information */
	uint16 protocol;
#define PPP_IP_PROTOCOL		0x0021	/* Internet Protocol */
#define PPP_OSINL_PROTOCOL	0x0023	/* OSI Network Layer */
#define PPP_XNS_PROTOCOL 	0x0025	/* Xerox NS IDP */
#define PPP_DN4_PROTOCOL 	0x0027	/* DECnet Phase IV */
#define PPP_AT_PROTOCOL 	0x0029	/* Appletalk */
#define PPP_IPX_PROTOCOL	0x002b	/* Novell IPX */
#define PPP_VJCH_PROTOCOL	0x002d	/* Van Jacobson Compressed TCP/IP */
#define PPP_VJUCH_PROTOCOL	0x002f	/* Van Jacobson Uncompressed TCP/IP */
#define PPP_BPDU_PROTOCOL 	0x0031	/* Bridging PDU */
#define PPP_ST2_PROTOCOL 	0x0033	/* Stream Protocol (ST-II) */
#define PPP_BV_PROTOCOL 	0x0035	/* Banyan Vines */

#define PPP_8021D_PROTOCOL 	0x0201	/* 802.1d Hello Packets */
#define PPP_LUXCOM_PROTOCOL 	0x0231	/* Luxcom */
#define PPP_SIGMA_PROTOCOL 	0x0233	/* Sigma Network Systems */

#define PPP_IPCP_PROTOCOL	0x8021	/* Internet Protocol Control Protocol */
#define PPP_OSINLCP_PROTOCOL 	0x8023	/* OSI Network Layer Control Protocol */
#define PPP_XNSCP_PROTOCOL 	0x8025	/* Xerox NS IDP Control Protocol */
#define PPP_DN4CP_PROTOCOL 	0x8027	/* DECnet Phase IV Control Protocol */
#define PPP_ATCP_PROTOCOL 	0x8029	/* Appletalk Control Protocol */
#define PPP_IPXCP_PROTOCOL	0x802b	/* Novell IPX Control Protocol */
#define PPP_BNCP_PROTOCOL 	0x8031	/* Bridging NCP */
#define PPP_ST2CP_PROTOCOL 	0x8033	/* Stream Protocol Control Protocol */
#define PPP_BVCP_PROTOCOL 	0x8035	/* Banyan Vines Control Protocol */

#define PPP_LCP_PROTOCOL	0xc021	/* Link Control Protocol */
#define PPP_PAP_PROTOCOL	0xc023	/* Password Authentication Protocol */
#define PPP_CHAP_PROTOCOL	0xc223	/* Challenge Handshake A P */
#define PPP_LQR_PROTOCOL	0xc025	/* Link Quality Report */
};

#define PPP_HDR_LEN		4	/* Max bytes for PPP/HDLC envelope header */
#define PPP_PADDING		8	/* Max bytes for PPP/HDLC padding */
#define PPPOE_HDR_LEN	8	/* Size of PPPoE header */

/* HDLC envelope constants */
#define HDLC_ENVLEN		8	/* Max bytes for HDLC envelope (outgoing) */

#define HDLC_FLAG		0x7e	/* HDLC async start/stop flag */
#define HDLC_ESC_ASYNC	0x7d	/* HDLC transparency escape flag for async */
#define HDLC_ESC_COMPL	0x20	/* HDLC transparency bit complement mask */

#define HDLC_FCS_START	0xffff	/* Starting bit string for FCS calculation */
#define HDLC_FCS_FINAL	0xf0b8	/* FCS when summed over frame and sender FCS */

#endif /* _WAN_PPP_H */
