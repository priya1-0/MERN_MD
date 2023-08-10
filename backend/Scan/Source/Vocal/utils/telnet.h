
/* ************************************************************************* */
/*
 *	telnet.h
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
 *	Module:		UTILS
 *
 *	This file contains the telnet declarations.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 20:53:02  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _UTILS_TELNET_H
#define _UTILS_TELNET_H

#define	LINESIZE	256		/* Length of local editing buffer */
#define LOGOUT_CHAR	4

/* Telnet command characters */
#define	IAC		255		/* Interpret as command */
#define	WILL		251
#define	WONT		252
#define	DO		253
#define	DONT		254

/* Telnet options */
#define	TN_TRANSMIT_BINARY	0
#define	TN_ECHO			1
#define	TN_SUPPRESS_GA		3
#define	TN_STATUS		5
#define	TN_TIMING_MARK		6
#define	NOPTIONS		6

/* Telnet protocol control block */
struct telnet {
	char local[NOPTIONS];		/* Local option settings */
	char remote[NOPTIONS];		/* Remote option settings */
	struct session *session;	/* Pointer to session structure */
	char eolmode;			/* Control translation of enter key */
};
#define	NULLTN	((struct telnet *) 0)

extern int Refuse_echo;
extern int Tn_cr_mode;
extern int Stelnet;

#endif /* _UTILS_TELNET_H */
