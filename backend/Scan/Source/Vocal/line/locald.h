
/* ************************************************************************* */
/*
 *	locald.h
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
 *	This file contains the private parameter declarations/definitions
 *	for the LINE module.
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

#ifndef _LINE_LOCALD_H
#define _LINE_LOCALD_H

/* ************************************************************************* */

typedef struct {
	void	(*_rx_intp) (uint16);
	uint16	(*_tx_intp) (void);
	uint16	_sart_rx_parm;
	uint16	_sart_tx_parm;
	uint16	_prev_sart_rx_parm;
	uint16	_prev_sart_tx_parm;
	uint16	_tx_next_expected;
	uint16	_rx_next_expected;
} line_local_t;

/* ************************************************************************* */

DEF_DATA(line_local_t, line_local)
#define LINE_LOCAL_DATA line_local_t line_local
#define LINE_LOCAL USE_DATA(line_local)

/* ************************************************************************* */

#define line_rx_intp						(LINE_LOCAL._rx_intp)
#define line_tx_intp						(LINE_LOCAL._tx_intp)
#define line_sart_rx_parm					(LINE_LOCAL._sart_rx_parm)
#define line_sart_tx_parm					(LINE_LOCAL._sart_tx_parm)
#define line_prev_sart_rx_parm				(LINE_LOCAL._prev_sart_rx_parm)
#define line_prev_sart_tx_parm				(LINE_LOCAL._prev_sart_tx_parm)
#define line_tx_next_expected				(LINE_LOCAL._tx_next_expected)
#define line_rx_next_expected				(LINE_LOCAL._rx_next_expected)

/* ************************************************************************* */

#endif /* LINE_LOCALD_H */
