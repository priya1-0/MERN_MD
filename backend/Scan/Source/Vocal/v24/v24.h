
/* ************************************************************************* */
/*
 *	v24.h
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
 *	This file contains the public declarations for the V24 module.
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

#ifndef _V24_V24_H
#define _V24_V24_H

/* ************************************************************************* */

#include "v24/v24d.h"

/* ************************************************************************* */

#define V24_DCD_MODE__ALWAYS_ON			0
#define V24_DCD_MODE__PUMP				1
#define V24_DCD_MODE__PULSE				2
#define V24_DCD_MODE__ILLEGAL			0xffff

#define V24_DSR_MODE__ALWAYS_ON			0
#define V24_DSR_MODE__PUMP				1
#define V24_DSR_MODE__ILLEGAL			0xffff

#define V24_CTS_MODE__ALWAYS_ON			1
#define V24_CTS_MODE__PUMP				0
#define V24_CTS_MODE__RTS_DELAY			2
#define V24_CTS_MODE__ILLEGAL			0xffff

#define V24_DTR_MODE__IGNORE			0
#define V24_DTR_MODE__ESCAPE_REQUEST	1
#define V24_DTR_MODE__HANGUP_REQUEST	2
#define V24_DTR_MODE__RESET_REQUEST		3
#define V24_DTR_MODE__ILLEGAL			0xffff

/* ************************************************************************* */

#define V24_DU__NO_DATA_AVAILABLE		0x8000
#define V24_DU__BREAK					0x8000
#define V24_DU__BREAK_START				0x4000
#define V24_DU__BREAK_END				0x2000
#define V24_DU__FRAME_ERROR				0x0800
#define V24_DU__PARITY_ERROR			0x0400
#define V24_DU__WITHIN_SEQUENCE			0x0200

/* DTE towards DCE */
#define V24_DU__EDGE__105_OFF			0x0042
#define V24_DU__EDGE__105_ON			0x0043
#define V24_DU__EDGE__108_OFF			0x0044
#define V24_DU__EDGE__108_ON			0x0045
#define V24_DU__EDGE__133_OFF			0x0046
#define V24_DU__EDGE__133_ON			0x0047

/* DCE towards DTE */
#define V24_DU__EDGE__106_OFF			0x0062
#define V24_DU__EDGE__106_ON			0x0063
#define V24_DU__EDGE__107_OFF			0x0064
#define V24_DU__EDGE__107_ON			0x0065
#define V24_DU__EDGE__109_OFF			0x0066
#define V24_DU__EDGE__109_ON			0x0067
#define V24_DU__EDGE__110_OFF			0x0068
#define V24_DU__EDGE__110_ON			0x0069
#define V24_DU__EDGE__125_OFF			0x006A
#define V24_DU__EDGE__125_ON			0x006B
#define V24_DU__EDGE__132_OFF			0x006C
#define V24_DU__EDGE__132_ON			0x006D
#define V24_DU__EDGE__142_OFF			0x006E
#define V24_DU__EDGE__142_ON			0x006F

/* Common names */
#define V24_DU__EDGE__RTS_OFF			V24_DU__EDGE__105_OFF
#define V24_DU__EDGE__RTS_ON			V24_DU__EDGE__105_ON
#define V24_DU__EDGE__DTR_OFF			V24_DU__EDGE__108_OFF
#define V24_DU__EDGE__DTR_ON			V24_DU__EDGE__108_ON
#define V24_DU__EDGE__CTS_OFF			V24_DU__EDGE__106_OFF
#define V24_DU__EDGE__CTS_ON			V24_DU__EDGE__106_ON
#define V24_DU__EDGE__DCD_OFF			V24_DU__EDGE__109_OFF
#define V24_DU__EDGE__DCD_ON			V24_DU__EDGE__109_ON
#define V24_DU__EDGE__DSR_OFF			V24_DU__EDGE__107_OFF
#define V24_DU__EDGE__DSR_ON			V24_DU__EDGE__107_ON
#define V24_DU__EDGE__RI_OFF			V24_DU__EDGE__125_OFF
#define V24_DU__EDGE__RI_ON				V24_DU__EDGE__125_ON

/* ************************************************************************* */

/*- MKHEADER Begin -*/

/* Global States: */

/* v24.c */
extern state_action_t v24_idle [];

/* Global Routines: */

/* v24.c */
void v24_module_reset (void);
void v24_mode_change (void);
void v24_sm_start (void);
void sr_csc_reset (void);
void sr_csc_start (void);
void sr_dteif_dtr_on (void);
void sr_dteif_dtr_off (void);
void v24_cmdset_cts_on_handoff (void);
void v24_cmdset_cts_off_handoff (void);

/*- MKHEADER End -*/


/* ************************************************************************* */

#endif /* _V24_V24_H */
