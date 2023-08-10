
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
 *	Defines and structures for implementing chat scripts.
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

#ifndef _TERM_CHAT_H
#define _TERM_CHAT_H

/* Chat structure.
 *
 * A little note on terminology.  In my source, when I say 'chat' I mean a
 * chat structure.  When I say chat scrip, I mean the actual scrip
 * structure.  From the user standpoint, they're all chat scripts. */
struct chat {
	struct chat *next;
	char *name;							/* Title of script. */
	char **script;						/* The actual script in ARGV format.
										 * NULL entry ends this. */
};
#define NULLCHAT ((struct chat *) 0)

/* Chat script meta chars. */
#define CHAT_ESCAPE	'\\'				/* The escape char. */
#define CHAT_ESCAPE_STRING "\\"			/* Same thing as string. */
#define CHAT_LOG	'L'					/* Login name. */
#define CHAT_LOG_STRING	CHAT_ESCAPE_STRING "L" /* Login name as string. */
#define CHAT_PASS	'P'					/* Password. */
#define CHAT_PASS_STRING CHAT_ESCAPE_STRING "P" /* Password as string. */
#define CHAT_CANCEL	'c'					/* Cancel the output newline. */
#define CHAT_CANCEL_STRING CHAT_ESCAPE_STRING "c" /* Cancel as string. */
#define CHAT_BREAK	'K'					/* Send a break. */
#define CHAT_DELAY	'd'					/* Delay 2 seconds. */
#define CHAT_DELAY_STRING CHAT_ESCAPE_STRING "d" /* Delay as a string. */
#define CHAT_PAUSE	'p'					/* Pause 1/3 seconds. */
#define CHAT_NEWLINE_CHAR 'r'			/* A newline for our modem. */
#define CHAT_NEWLINE_STRING CHAT_ESCAPE_STRING "r" /* A newline for our modem. */
/* See also 'chat_trans_string' in chat.c (Currently "bNnrst-") */

/* Does the string end with a newline cancel. */
#define CHAT_CANCELED(x) ((x) != NULL && (strlen(x) >= 2) && \
			  (x)[strlen (x) - 2] == CHAT_ESCAPE &&\
			  (x)[strlen (x) -1] == CHAT_CANCEL)

#endif /* _TERM_CHAT_H */
