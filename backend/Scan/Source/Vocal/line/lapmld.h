
/* ************************************************************************* */
/*
 *	lapmld.h
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
 *	This file contains the intra-module definitions for the LINE module.
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

#ifndef _LINE_LAPMLD_H
#define _LINE_LAPMLD_H

#include "lapm/frames.h"

/* ************************************************************************* */

typedef struct {

	bool	_first_data_of_frame;

	uint16	_tx_byte_count;
	pack8	*_tx_bufferp;
	lapm_tx_frame_t *_tx_lapm_framep;

	bool	_rx_frame_error;
	uint16	_rx_byte_count;
	pack8	*_rx_bufferp;
	lapm_rx_frame_t *_rx_lapm_framep;

	uint8	_rx_char;
	bool	_tx_active;

} line_local_lapm_t;

/* ************************************************************************* */

#define LINE_LOCAL_LAPM_DATA line_local_lapm_t line_local_lapm
DEF_DATA(line_local_lapm_t, line_local_lapm)
#define LINE_LOCAL_LAPM USE_DATA(line_local_lapm)

/* ************************************************************************* */

#define lapm_first_data_of_frame			(LINE_LOCAL_LAPM._first_data_of_frame)

#define lapm_tx_byte_count					(LINE_LOCAL_LAPM._tx_byte_count)
#define lapm_tx_bufferp						(LINE_LOCAL_LAPM._tx_bufferp)
#define lapm_tx_lapm_framep					(LINE_LOCAL_LAPM._tx_lapm_framep)

#define lapm_rx_frame_error					(LINE_LOCAL_LAPM._rx_frame_error)
#define lapm_rx_byte_count					(LINE_LOCAL_LAPM._rx_byte_count)
#define lapm_rx_bufferp						(LINE_LOCAL_LAPM._rx_bufferp)
#define lapm_rx_lapm_framep					(LINE_LOCAL_LAPM._rx_lapm_framep)

#define lapm_rx_char						(LINE_LOCAL_LAPM._rx_char)
#define lapm_tx_active						(LINE_LOCAL_LAPM._tx_active)

/* ************************************************************************* */

#endif /* _LINE_LAPMLD_H */
