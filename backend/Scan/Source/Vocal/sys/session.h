
/* ************************************************************************* */
/*
 *	session.h
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
 *	Module:		SYS
 *
 *	This file contains the functions.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 20:46:45  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _SYS_SESSION_H
#define _SYS_SESSION_H

#define	MOREROWS	24	/* rows on screen before --more-- */

/* ************************************************************************* */

struct ttystate {
	char *line;		/* Line buffer */
	char *lp;		/* Pointer into same */
	int echo;		/* Keyboard local echoing? */
	int edit;		/* Local editing? */
	int crnl;		/* Translate cr to lf? */
	int rows;		/* Number of rows on display */
};

/* ************************************************************************* */

/* Session control structure; only one entry is used at a time */
struct session {
	int type;
#define	FREE	0
#define	TELNET	1
#define	FTP		2
#define	AX25TNC	3
#define	FINGER	4
#define	PING	5
#define NRSESSION 6
#define	COMMAND	7
#define	VIEW	8
#define	HOP		9
#define	TIP		10
#define	PPPPASS	11
#define DIAL	12
#define DQUERY	13
#define DCLIST	14
#define	ITRACE	15
#define REMCMD	16

	uint16 user;		/* user number */
	uint16 session_num; 	/* session number for this user */
	int processes;		/* # processes using this session */

	char *name;			/* Name of remote host */
	void *cb;			/* control block */

	struct ttystate ttystate;

	struct proc *proc0;	/* Primary session process (e.g., tn recv) */
	struct proc *proc1;	/* Secondary session process (e.g., tn xmit) */
	struct proc *proc2;	/* Tertiary session process (e.g., upload) */

	FILE *network;		/* Primary network socket (control for FTP) */
	FILE *record;		/* Receive record file */
	FILE *upload;		/* Send file */

	FILE *input;		/* Input stream */
	FILE *output;		/* Output stream */
	int (*ctlproc) (int);	/* Function to hand keyboard ctls */
};
#define	NULLSESSION	(struct session *)0

/* ************************************************************************* */

struct user_s {
	int user;
	struct session **list;
	struct session *active;
	struct session *recent;
	struct proc *display;
};
#define NULLUSER	(struct user_s *)0

/* ************************************************************************* */

extern uint16 Nsessions;		/* Maximum number of sessions */
extern uint16 Nusers;			/* Maximum number of logins */

extern struct session *Active_session;

/* In session.c: */
extern char *Sestypes[];		/* session type names */
extern struct user_s **Users;		/* User entry array */

#define	ALERT_EOF	1

/* ************************************************************************* */

/* ************************************************************************* */

#endif /* _SYS_SESSION_H */
