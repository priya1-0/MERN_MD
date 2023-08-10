
/* ************************************************************************* */
/*
 *	bufferld.h
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
 *	Module:		LINE
 *
 *	This file contains the private parameter definitions for
 *	the LINE-BUFFERED module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 20:00:57  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _LINE_BUFFERLD_H
#define _LINE_BUFFERLD_H

/* ************************************************************************* */

typedef struct {
	uint16	_unused;
} line_local_buffered_t;

/* ************************************************************************* */

#define LINE_LOCAL_BUFFERED_DATA line_local_buffered_t line_local_buffered
DEF_DATA(line_local_buffered_t, line_local_buffered)
#define LINE_LOCAL_BUFFERED USE_DATA(line_local_buffered)

/* ************************************************************************* */

#define buffered_unused					(LINE_LOCAL_BUFFERED._unused)

/* ************************************************************************* */

#endif /* _LINE_BUFFERLD_H */
