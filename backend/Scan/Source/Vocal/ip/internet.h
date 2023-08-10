
/* ************************************************************************* */
/*
 *	internet.h
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

#ifndef _IP_INTERNET_H
#define _IP_INTERNET_H

/* Global structures and constants pertaining to the interface between IP and
 * 	higher level protocols
 */

/* IP protocol field values */
#define	ICMP_PTCL	1	/* Internet Control Message Protocol */
#define	TCP_PTCL	6	/* Transmission Control Protocol */
#define	UDP_PTCL	17	/* User Datagram Protocol */
#define	IP_PTCL		4	/* IP inside IP */
#define IPV6_PTCL	41	/* IP Verson 6 Protocol */

#define GRE_PTCL	47	/* General Encapsulation Protocol */
#define ESP_PTCL	50	/* Encapsulated Security Protocol */
#define AH_PTCL		51	/* Authentication Header Protocol */
#define ICP_PTCL	108	/* IP Payload Compression Protocol */

#define IGMP_PTCL	2	/* Internet Group Management */
#define IGRP_PTCL	88	/* IGRP */
#define OSPF_PTCL	89	/* OSPF */

#define	MAXTTL		255	/* Maximum possible IP time-to-live value */

/* DoD-style precedences */
#define	IP_PRECEDENCE	0xe0	/* Mask for precedence field */
#define	ROUTINE		0x00
#define	IP_PRIORITY	0x20
#define	IMMEDIATE	0x40
#define	FLASH		0x60
#define	FLASH_OVER	0x80
#define	CRITIC		0xa0
#define	INET_CTL	0xc0
#define	NET_CTL		0xe0

/* Amateur-style precedences */
#define	AM_ROUTINE	0x00
#define	AM_WELFARE	0x20
#define	AM_PRIORITY	0x40
#define	AM_EMERGENCY	0x60

/* Class-of-service bits */
#define	IP_COS		0x1c	/* Mask for class-of-service bits */
#define	LOW_DELAY	0x10
#define	THROUGHPUT	0x08
#define	RELIABILITY	0x04

/* IP TOS fields */
#define	PREC(x)		(((x)>>5) & 0x7)
#define	TOS_DELAY	0x10
#define	THRUPUT		0x8
#define	RELIABLITY	0x4

#define IPPORT_RESERVED		1024
#define IPPORT_USERRESERVED	5000

#define IPPORT_WELL_KNOWN	1023	/* 0 to 1023 are Well Known Ports */
#define IPPORT_REGISTERED	49151	/* 1024 to 49151 are Registered Ports */
#define IPPORT_DYNAMIC		65535	/* 49152 to 65535 are Dynamic or Private Ports */

/* TCP port numbers */
#define	IPPORT_ECHO			7		/* Echo data port */
#define	IPPORT_DISCARD		9		/* Discard data port */
#define	IPPORT_FTPD			20		/* FTP Data port */
#define	IPPORT_FTP			21		/* FTP Control port */
#define IPPORT_TELNET		23		/* Telnet port */
#define IPPORT_SMTP			25		/* Mail port */
#define	IPPORT_MTP			57		/* Secondary telnet protocol */
#define	IPPORT_TFTP			69		/* TFTP server port */
#define	IPPORT_FINGER		79		/* Finger port */
#define	IPPORT_WEBSERVER	80		/* Web Server port */
#define	IPPORT_TTYLINK		87		/* Chat port */
#define IPPORT_POP			109		/* pop2 port */
#define	IPPORT_NNTP			119		/* Netnews port */
#define	IPPORT_LOGIN		513		/* BSD rlogin port */
#define IPPORT_PPTP			1723	/* PPTP port */

/* UDP port numbers */
#define	IPPORT_DOMAIN		53
#define	IPPORT_BOOTPS		67
#define	IPPORT_BOOTPC		68
#define IPPORT_SNMP			161
#define IPPORT_ISAKMP		500		/* IKE/IPSec key negotiation port */
#define IPPORT_SYSLOG		514
#define	IPPORT_RIP			520
#define IPPORT_L2TP			1701	/* L2TP port */
#define IPPORT_STUN			3478	/* STUN server port */
#define IPPORT_IPSEC		4500	/* IPSec port */

#endif /* _IP_INTERNET_H */
