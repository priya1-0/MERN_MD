
/* ************************************************************************* */
/*
 *	config.h
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
 *	This file defines array sizes for variables related to the
 *	BUFFERED module.
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

#ifndef _BUFFERED_CONFIG_H
#define _BUFFERED_CONFIG_H

/* ************************************************************************* */

#define BUFFERED_RX_BUFFER_SIZE		2048
#define BUFFERED_TX_BUFFER_SIZE		512

#define BUFFERED_RX_XON_THRESHOLD		(BUFFERED_RX_BUFFER_SIZE/4)
#define BUFFERED_RX_XOFF_THRESHOLD		(BUFFERED_RX_BUFFER_SIZE/2)

/* ************************************************************************* */

#endif /* _BUFFERED_CONFIG_H */
