
/* ************************************************************************* */
/*
 *	pppchap.h
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
 *	This file contains the PPP CHAP declarations.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.2  2010/02/17 00:14:31  heiand1
 *	Revision History:	SCR 186226. Chap Login and Network initialization Timing.
 *	Revision History:	
 *	Revision History:	Revision 1.1.24.1  2009/04/28 20:56:09  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _WAN_PPPCHAP_H
#define _WAN_PPPCHAP_H

#define CHAP_CHALLENGE	1
#define CHAP_RESPONSE	2
#define CHAP_SUCCESS 	3
#define CHAP_FAILURE 	4

#define CHAP_MD5	5
#define CHAP_MD5_SIZE	16

#define CHAP_SHOW_MESSAGE	0x01

/* CHAP control block */
struct chap_s {
	char *hostname; 		/* for challenging */
	char *username; 		/* for responding */
	char *secret;			/* for responding */
	char *message;			/* message from peer */

	struct mbuf *out_bp;		/* challenge sent */
	struct proc *cpp;		/* challenge process */

	uint8 in_id;			/* identifier received */
	struct mbuf *in_bp;		/* challenge received */
	struct proc *rpp;		/* response process */
};

#define CHAP_RESP_TRY	60		/* # response attempts */
#define CHAP_FAIL_MAX	36		/* # attempts from remote */

#define CHAP_TIMEOUT	60		/* Seconds to wait for ACK/NAK */

#endif /* _WAN_PPPCHAP_H */
