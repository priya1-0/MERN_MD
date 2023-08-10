
/* ************************************************************************* */
/*
 *	buffered.h
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
 *	Module:		BUFFERED
 *
 *	This file contains the public declarations for the BUFFERED module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 18:27:31  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _BUFFERED_BUFFER_H
#define _BUFFERED_BUFFER_H

/* ************************************************************************* */

#include "dp/dp.h"

/* ************************************************************************* */

/*- MKHEADER Begin -*/

/* Global Routines: */

/* bg.c */
void dp_reset_inactivity_timer (void);

/* buffer.c */
void buffered_rx_clear (void);
bool buffered_rx_get_du (uint16 *dup);
bool buffered_rx_put_du (uint16 du);

/* routines.c */
dpf_t * buffered_entry (void);

/*- MKHEADER End -*/


/* ************************************************************************* */

#endif /* _BUFFERED_BUFFERED_H */
