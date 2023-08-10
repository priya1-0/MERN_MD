
/* ************************************************************************* */
/*
 *	account.h
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
 *	Module:		LANSEND
 *
 *	Defines account structures and functions.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 19:56:06  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _LANSEND_ACCOUNT_H
#define _LANSEND_ACCOUNT_H

struct account {
	struct account *next;
	char *name;
	char *password;
	char *protocol;
	char *address;
	char *message;
};

#define NULLACCOUNT (struct account *)0

extern struct account *Accounts;	/* List of all accounts */

#endif /* _LANSEND_ACCOUNT_H */
