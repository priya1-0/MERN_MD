
/* ************************************************************************* */
/*
 *	mnpld.h
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
 *	the LINE-MNP module.
 *
 *	1. Definitions of variables that are only used within this module.
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

#ifndef _LINE_MNPLD_H
#define _LINE_MNPLD_H

#include "mnp/frames.h"

/* ************************************************************************* */

typedef struct {
	uint8	_rx_state;					/* MNP_ASYNC_RX_xxx */
	uint8	_tx_state;					/* MNP_ASYNC_TX_xxx */
	umod8	_rx_crc16_hi;					/* high uint8 mnp calculated crc */
	umod8	_rx_crc16_lo;					/* low uint8  mnp calculated crc */
	umod8	_tx_crc16_hi;
	umod8	_tx_crc16_lo;

/* ************************************************************************* */

	bool	_first_data_of_frame;

	uint16	_tx_byte_count;
	pack8	*_tx_bufferp;
	mnp_transmit_frame_t *_tx_mnp_framep;

	bool	_rx_frame_error;
	uint16	_rx_byte_count;
	pack8	*_rx_bufferp;
	mnp_receive_frame_t *_rx_mnp_framep;

	uint8	_tx_char;						/* MNP_ASYNC_xxx */
	uint8	_rx_char;						/* MNP_ASYNC_xxx */
	uint16	_rx_data_unit;
	uint16	_tx_data_unit;
	bool	_sync_en;

	bool	_tx_active;

	mnp_receive_frame_t  *(*_rx_fp)(void);
	mnp_transmit_frame_t  *(*_tx_fp)(void);

} line_local_mnp_t;

/* ************************************************************************* */

#define LINE_LOCAL_MNP_DATA line_local_mnp_t line_local_mnp
DEF_DATA(line_local_mnp_t, line_local_mnp)
#define LINE_LOCAL_MNP USE_DATA(line_local_mnp)

/* ************************************************************************* */

#define mnp_async_rx_state					(LINE_LOCAL_MNP._rx_state)
#define mnp_async_tx_state					(LINE_LOCAL_MNP._tx_state)
#define mnp_async_rx_crc16_hi				(LINE_LOCAL_MNP._rx_crc16_hi)
#define mnp_async_rx_crc16_lo				(LINE_LOCAL_MNP._rx_crc16_lo)
#define mnp_async_tx_crc16_hi				(LINE_LOCAL_MNP._tx_crc16_hi)
#define mnp_async_tx_crc16_lo				(LINE_LOCAL_MNP._tx_crc16_lo)

#define mnp_first_data_of_frame				(LINE_LOCAL_MNP._first_data_of_frame)

#define mnp_tx_byte_count					(LINE_LOCAL_MNP._tx_byte_count)
#define mnp_tx_bufferp						(LINE_LOCAL_MNP._tx_bufferp)
#define mnp_tx_mnp_framep					(LINE_LOCAL_MNP._tx_mnp_framep)

#define mnp_rx_frame_error					(LINE_LOCAL_MNP._rx_frame_error)
#define mnp_rx_byte_count					(LINE_LOCAL_MNP._rx_byte_count)
#define mnp_rx_bufferp						(LINE_LOCAL_MNP._rx_bufferp)
#define mnp_rx_mnp_framep					(LINE_LOCAL_MNP._rx_mnp_framep)

#define mnp_tx_char							(LINE_LOCAL_MNP._tx_char)
#define mnp_rx_char							(LINE_LOCAL_MNP._rx_char)
#define mnp_rx_data_unit					(LINE_LOCAL_MNP._rx_data_unit)
#define mnp_tx_data_unit					(LINE_LOCAL_MNP._tx_data_unit)
#define mnp_sync_en							(LINE_LOCAL_MNP._sync_en)

#define mnp_tx_active						(LINE_LOCAL_MNP._tx_active)

#define mnp_rx_fp							(LINE_LOCAL_MNP._rx_fp)
#define mnp_tx_fp							(LINE_LOCAL_MNP._tx_fp)

/* ************************************************************************* */

#endif /* _LINE_MNPLD_H */
