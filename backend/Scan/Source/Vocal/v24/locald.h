
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
 *	Module:		V24
 *
 *	This file contains the private parameter declarations/definitions
 *	for the V24 module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 20:53:24  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _V24_LOCALD_H
#define _V24_LOCALD_H

/* ************************************************************************* */

typedef struct {

	uint16	_dcd_mode;
	uint16	_dsr_mode;
	uint16	_cts_mode;
	uint16	_dtr_mode;
	uint16	_ri_duration;
	uint16	_dtr_low_debounce_duration;
	uint16	_dtr_high_debounce_duration;
	uint16	_rts_low_debounce_duration;
	uint16	_rts_high_debounce_duration;
	uint16	_dcd_disconnect_pulse_duration;

	uint16	_within_dtr_debounce;
	uint16	_within_rts_debounce;

} v24_local_t;

/* ************************************************************************* */

DEF_DATA(v24_local_t, v24_local)
#define V24_LOCAL_DATA v24_local_t v24_local
#define V24_LOCAL USE_DATA(v24_local)

/* ************************************************************************* */

#define v24_dcd_mode						(V24_LOCAL._dcd_mode)
#define v24_dsr_mode						(V24_LOCAL._dsr_mode)
#define v24_cts_mode						(V24_LOCAL._cts_mode)
#define v24_dtr_mode						(V24_LOCAL._dtr_mode)

#define v24_ri_duration						(V24_LOCAL._ri_duration)
#define v24_dtr_low_debounce_duration		(V24_LOCAL._dtr_low_debounce_duration)
#define v24_dtr_high_debounce_duration		(V24_LOCAL._dtr_high_debounce_duration)
#define v24_rts_low_debounce_duration		(V24_LOCAL._rts_low_debounce_duration)
#define v24_rts_high_debounce_duration		(V24_LOCAL._rts_high_debounce_duration)
#define v24_dcd_disconnect_pulse_duration	(V24_LOCAL._dcd_disconnect_pulse_duration)

#define v24_within_dtr_debounce				(V24_LOCAL._within_dtr_debounce)
#define v24_within_rts_debounce				(V24_LOCAL._within_rts_debounce)

/* ************************************************************************* */

#endif /* _V24_LOCALD_H */
