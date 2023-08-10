
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
 *	Module:		DTEIF
 *
 *	This file contains the private parameter declarations/definitions
 *	for the DTEIF module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 19:48:36  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _DTEIF_LOCALD_H
#define _DTEIF_LOCALD_H

#include "dteif/config.h"

/* ************************************************************************* */

typedef struct {
	uint16	_hw_base;
	bool	_int_active;
	uint16	_lsr_status;
	uint16	_mcr_control;
	uint16	_msr_status;
	uint16	_rate_index;
	uint16	_port_number;
	uint16	_int_number;
	uint16	_int_mask;
	bool	_uart_overrun_flag;

	bool   _ignore_break_null;
	uint16 _echo_buffer [DTEIF_ECHO_BUFFER_SIZE];
	uint16 *_echo_inp;
	uint16 *_echo_outp;
	bool	_16550_fifo_avail;

} dteif_local_t;

/* ************************************************************************* */

DEF_DATA(dteif_local_t, dteif_local)
#define DTEIF_LOCAL_DATA dteif_local_t dteif_local
#define DTEIF_LOCAL USE_DATA(dteif_local)

/* ************************************************************************* */

#define	dteif_hw_base						(DTEIF_LOCAL._hw_base)
#define	dteif_int_active					(DTEIF_LOCAL._int_active)
#define	dteif_lsr_status					(DTEIF_LOCAL._lsr_status)
#define	dteif_mcr_control					(DTEIF_LOCAL._mcr_control)
#define	dteif_msr_status					(DTEIF_LOCAL._msr_status)
#define	dteif_rate_index					(DTEIF_LOCAL._rate_index)
#define	dteif_port_number					(DTEIF_LOCAL._port_number)
#define	dteif_int_number					(DTEIF_LOCAL._int_number)
#define	dteif_int_mask						(DTEIF_LOCAL._int_mask)
#define	dteif_uart_overrun_flag				(DTEIF_LOCAL._uart_overrun_flag)
#define	dteif_ignore_break_null				(DTEIF_LOCAL._ignore_break_null)
#define	dteif_echo_buffer					(DTEIF_LOCAL._echo_buffer)
#define	dteif_echo_inp						(DTEIF_LOCAL._echo_inp)
#define	dteif_echo_outp						(DTEIF_LOCAL._echo_outp)
#define	dteif_16550_fifo_avail				(DTEIF_LOCAL._16550_fifo_avail)

/* ************************************************************************* */

#endif /* _DTEIF_LOCALD_H */
