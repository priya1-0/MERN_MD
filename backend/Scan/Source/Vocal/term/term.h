
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
 *	This file contains the public declarations for the TERM module.
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

#ifndef _TERM_TERM_H
#define _TERM_TERM_H

#include "term/termd.h"
#include "dev/iface.h"
#include "net/socket.h"
#include "ip/ip.h"
#include "ip/tcp.h"
#include "utils/telnet.h"
#include "term/chat.h"
#include "term/decide.h"
#include "term/modcap.h"
#include "term/modem.h"
#include "term/netcom.h"
#include "term/shell.h"

/* ************************************************************************* */
/*- MKHEADER Begin -*/

/* Global Routines: */

/* term.c */
void term_module_reset (void);
void term_startup (void);
void hangup_wait (struct iface *ifp);
void hangup (void *p);

/*- MKHEADER End -*/


/* ************************************************************************* */

#endif /* _TERM_TERM_H */
