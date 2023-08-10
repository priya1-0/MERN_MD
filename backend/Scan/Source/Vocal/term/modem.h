
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
 *	Defines and data structure for the shared modem.
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

#ifndef _TERM_MODEM_H
#define _TERM_MODEM_H

struct modem {
	sint15 local_window;				/* How many bytes made available to
										 * the client, since the last
										 * packet. */
	sint15 remote_window;				/* How many more bytes the server can
										 * send to the net. */

	struct mbuf *norm_pkt;				/* Holding point for consolidating
										 * normal packets. */

	uint16 echo_send;					/* HACK: Echo value to send back. */

	int flow_type;						/* What kind of flow control is being
										 * done. */

	uint8 stop_type;					/* Who/what flow control is currently
										 * asserted for the other side. */
	/* These are bit fields. */
#define MODEM_NO_STOP		0x00
#define MODEM_USER_SOFT		0x01
#define MODEM_USER_HARD		0x02
#define MODEM_INTERNAL_SOFT	0x04
#define MODEM_INTERNAL_HARD	0x08

	uint8 txoff;						/* Char to send out modem to stop tx. */
	uint8 txon;							/* Char to send out modem to start tx. */
	uint8 rxoff;						/* Char to receive from modem to stop
										 * our tx. */
	uint8 rxon;							/* Char to recieve from other side to
										 * start our tx. */

	uint8 hw_mode;						/* Mode this hardware is in. */

	uint8 send_status;					/* If !0 send status info. */

	/* The current state of this connection. */
	enum {
		Listening,						/* Waiting for allocation it. */
		Connected,						/* Talking to a redirector. */
		SessionEnded					/* Breaking off the session. */
	} status;

	int connection;						/* The redirector connection socket. */
	int listen;							/* The redirector listener socket. */
	struct proc *net_proc;				/* The recieve process socket. */
	struct proc *modem_proc;			/* The transmit process socket. */
	struct proc *lis_proc;				/* The listening process. */

	uint16 trace;						/* Trace level of this modem. */
};
#define NULLMODEM ((struct modem *) 0)

/* This character delimits the end of a modem command. */
#define MODEM_NEWLINE_CHAR '\r'
#define MODEM_NEWLINE_STRING "\r"

#define MODEM_DEFAULT_INIT "AT&FS58=2S25=1&D2S0=1" CHAT_NEWLINE_STRING CHAT_DELAY_STRING "AT"
#define MODEM_DEFAULT_DIAL "ATD" CHAT_CANCEL_STRING
#define MODEM_DEFAULT_CON NULL

#endif /* _TERM_MODEM_H */
