
/* ************************************************************************* */
/*
 *	ppppap.h
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
 *	This file contains the PPP PAP declarations.
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

#ifndef _WAN_PPPAP_H
#define _WAN_PPPAP_H

/* PAP control block */
struct pap_s {
	char *username;
	char *password;
	char *message;			/* message from last response */
	struct proc *pp;		/* request process */
};

#define PAP_REQ_TRY	5		/* REQ attempts */
#define PAP_FAIL_MAX	3		/* # attempts from remote */
#define PAP_TIMEOUT	20		/* Seconds to wait for ACK/NAK */

#endif /* _WAN_PPPAP_H */
