
/* ************************************************************************* */
/*
 *	bind.h
 *
 *	(C) 1994 - 2006 VOCAL Technologies, Ltd.
 *
 *	ALL RIGHTS RESERVED.  PROPRIETARY AND CONFIDENTIAL.
 *
 *	VOCAL Technologies, Ltd.
 *	90A John Muir Drive.
 *	Buffalo, NY  14228
 *
 *	Product:	MODEM 101
 *
 *	Module:		BIND
 *
 *	This file contains the public declarations for the BIND module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 18:28:36  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _BIND_BIND_H
#define _BIND_BIND_H

/* ************************************************************************* */

#define DIALTONE_DETECT__BLIND_DIAL			0
#define DIALTONE_DETECT__DIALTONE			1

#define BREAK_CONTROL__IGN					0
#define BREAK_CONTROL__DEST					1
#define BREAK_CONTROL__EXP					2
#define BREAK_CONTROL__SEQ					3

#define BUSY_DETECT_RSP__NO_CARRIER			0
#define BUSY_DETECT_RSP__BUSY				1

/* ************************************************************************* */
/*- MKHEADER Begin -*/

/* Global Routines: */

/* bindstd.c */
void dial_nonbindable (void);
void dial_bind (void);
void dm_nonbindable (void);
void dm_bind (void);
void dp_nonbindable (void);
void dp_bind (void);
void csc_nonbindable (void);
void csc_bind (void);
void sreg_s91_bind (uint16 s91_value);

/*- MKHEADER End -*/


/* ************************************************************************* */

#endif /* _BIND_BIND_H */
