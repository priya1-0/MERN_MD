
/* ************************************************************************* */
/*
 *	term.h
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
 *	Module:		TERM
 *
 *	Define and structures used in the dialer in decider.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 20:49:20  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _TERM_DECIDE_H
#define _TERM_DECIDE_H

#include "sys/timer.h"
/* Queue containing unmatched characters from decider. */
#define DECIDE_NO_MATCH_LEN 128

struct decide {
	enum {
		DECIDE_IDLE,					/* Waiting for a connection. */
		DECIDE_CONNECTING,				/* Dialing out a connection. */
		DECIDE_CHALLENGE,				/* Challenging a dial in connection. */
		DECIDE_MAX
	} state;
	/* Sub state of the above states. */
	enum {
		DSUB_WAITING,					/* Waiting for something to happen. */

		DSUB_DIALING,					/* Dialing out. */
		DSUB_RESPONDING,				/* Responding to a distant challenge. */
		DSUB_CONNECTED,					/* Successfully dialed out. */

		DSUB_INIT,						/* Initializing dial in. */
		DSUB_ENTRY,						/* Entering a dial in challenge. */
		DSUB_LOGIN,						/* Waiting for login string. */
		DSUB_PASSWORD,					/* Waiting for password string. */
		DSUB_ACCEPTING,					/* User made it in. */

		DSUB_MAX
	} sub_state;

	uint32 wait;
#define DEFAULT_DIAL_WAIT (60u * 1000u)
	struct timer wait_timer;
#define DEFAULT_DIAL_RETRY 5
	uint16 retry;
	uint16 test;
#define DEFAULT_DIAL_TEST (4 * 60 * 60)
	uint16 retest;
#define DEFAULT_DIAL_RETEST (30 * 60)
	uint8 no_match[DECIDE_NO_MATCH_LEN];
	uint8 *no_matchp;

	int chal_fails;						/* How many times a login challenged my try. */
#define CHAL_MAX_TRYS 3
	struct timer chal_time;				/* Login challenge time out. */

	uint32 originates;					/* Number of dial outs originated by dialer */
	uint32 answers;						/* Number of dial ins answered by dialer */
};
#define NULLDECIDE ((struct decide *) 0)

/* Assorted modem challenge macros. */
#define CHAL_TIMER_INTERVAL (30000L)	/* How long to wait for an entry. */
#define MNL "\r\n"						/* Modem New Line: Full line feed for
										 * end of modem string. */
#define CHALLENGE_TITLE "LANsEND"		/* Title */
#define CHALLENGE_LOGIN_PROMPT "Login: "
#define CHALLENGE_PASSWORD_PROMPT "Password: "

#endif /* _TERM_DECIDE_H */
