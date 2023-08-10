
/* ************************************************************************* */
/*
 *	btlzd.h
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
 *	Module:		BTLZ
 *
 *	This file contains the public parameter declarations/definitions for
 *	the BTLZ module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 18:28:01  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _BTLZ_BTLZD_H
#define _BTLZ_BTLZD_H

#include "btlz/config.h"

/* ************************************************************************* */
/*
 * common (passed) variables
 *
 */

typedef struct {
	uint8	_p0;
	uint16	_p1;
	uint8	_p2;

	bool	_tx_flush;
	expand8 *_tx_datap;
	uint8	_tx_index;

	uint8	_rx_index;
	uint8	_rx_error;
} btlz_btlz_t;

/* ************************************************************************* */

DEF_DATA (btlz_btlz_t, btlz_btlz)
#define BTLZ_BTLZ_DATA btlz_btlz_t btlz_btlz
#define BTLZ_BTLZ USE_DATA(btlz_btlz)

/* ************************************************************************* */

#define shared_btlz_p0						(BTLZ_BTLZ._p0)
#define shared_btlz_p1						(BTLZ_BTLZ._p1)
#define shared_btlz_p2						(BTLZ_BTLZ._p2)

#define shared_btlz_tx_flush				(BTLZ_BTLZ._tx_flush)
#define shared_btlz_tx_datap				(BTLZ_BTLZ._tx_datap)
#define shared_btlz_tx_index				(BTLZ_BTLZ._tx_index)
#define shared_btlz_rx_index				(BTLZ_BTLZ._rx_index)
#define shared_btlz_rx_error				(BTLZ_BTLZ._rx_error)

/* ************************************************************************* */

#endif /* _BTLZ_BTLZD_H */
