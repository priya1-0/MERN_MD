
/* ************************************************************************* */
/*
 *	shell.h
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
 *	Defines and structures for a dial in command line interpreter.
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

#ifndef _TERM_SHELL_H
#define _TERM_SHELL_H

struct shell {
	int restricted;						/* Restricted or regular shell. */
	struct proc *input;					/* The input gathering process. */
	struct proc *output;				/* The data sending process. */
	struct mbuf *bp;					/* The input cache. */
};
#define NULLSHELL ((struct shell *) 0)

/* Software flow control characters. */
#define SHELL_XON	ASCII__XON
#define SHELL_XOFF	ASCII__XOFF

#endif /* _TERM_SHELL_H */
