
/* ************************************************************************* */
/*
 *	v24d.h
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
 *	This file contains the public parameter declarations/definitions for
 *	the V24 module.
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

#ifndef _V24_V24D_H
#define _V24_V24D_H

/* ************************************************************************* */

typedef struct {
	uint16	_parm_dcd_mode;
	uint16	_parm_dsr_mode;
	uint16	_parm_cts_mode;
	uint16	_parm_dtr_mode;

	uint16	_parm_ri_duration;
	uint16	_parm_dtr_low_debounce_duration;
	uint16	_parm_dtr_high_debounce_duration;
	uint16	_parm_rts_low_debounce_duration;
	uint16	_parm_rts_high_debounce_duration;
	uint16	_parm_dcd_disconnect_pulse_duration;

	bool	_stat_dcd;
	bool	_stat_dsr;
	bool	_stat_cts;
	bool	_stat_ri;

	bool	_stat_rts;
	bool	_stat_dtr;

	bool	_stat_within_connect;
	bool	_stat_rts_dteif;
	bool	_stat_dtr_dteif;
	bool	_stat_dcd_pump;
	bool	_stat_dsr_pump;
	bool	_stat_cts_pump;

} v24_v24_t;

/* ************************************************************************* */

DEF_DATA(v24_v24_t, v24_v24)
#define V24_V24_DATA v24_v24_t v24_v24
#define V24_V24 USE_DATA(v24_v24)

/* ************************************************************************* */

#define	parm__v24_dcd_mode						(V24_V24._parm_dcd_mode)
#define	parm__v24_dsr_mode						(V24_V24._parm_dsr_mode)
#define	parm__v24_cts_mode						(V24_V24._parm_cts_mode)
#define	parm__v24_dtr_mode						(V24_V24._parm_dtr_mode)

#define	parm__v24_ri_duration					(V24_V24._parm_ri_duration)
#define	parm__v24_dtr_low_debounce_duration		(V24_V24._parm_dtr_low_debounce_duration)
#define	parm__v24_dtr_high_debounce_duration	(V24_V24._parm_dtr_high_debounce_duration)
#define	parm__v24_rts_low_debounce_duration		(V24_V24._parm_rts_low_debounce_duration)
#define	parm__v24_rts_high_debounce_duration	(V24_V24._parm_rts_high_debounce_duration)
#define	parm__v24_dcd_disconnect_pulse_duration	(V24_V24._parm_dcd_disconnect_pulse_duration)

#define	stat__v24_dcd							(V24_V24._stat_dcd)
#define	stat__v24_dsr							(V24_V24._stat_dsr)
#define	stat__v24_cts							(V24_V24._stat_cts)
#define	stat__v24_ri							(V24_V24._stat_ri)

#define	stat__v24_rts							(V24_V24._stat_rts)
#define	stat__v24_dtr							(V24_V24._stat_dtr)

#define	stat__v24_within_connect				(V24_V24._stat_within_connect)
#define	stat__v24_rts_dteif						(V24_V24._stat_rts_dteif)
#define	stat__v24_dtr_dteif						(V24_V24._stat_dtr_dteif)
#define	stat__v24_dcd_pump						(V24_V24._stat_dcd_pump)
#define	stat__v24_dsr_pump						(V24_V24._stat_dsr_pump)
#define	stat__v24_cts_pump						(V24_V24._stat_cts_pump)

/* ************************************************************************* */

#endif /* _V24_V24D_H */
