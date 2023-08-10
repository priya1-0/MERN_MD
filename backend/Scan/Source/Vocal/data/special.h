
/* ************************************************************************* */
/*
 *	special.h
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
 *	Module:		DATA
 *
 *	This file contains the special data declarations.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 19:33:26  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _DATA_SPECIAL_H
#define _DATA_SPECIAL_H

/* ************************************************************************* */

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

#ifdef WE_ARE_DEFINING_VARIABLES
#pragma DATA_SECTION (union_v34_rx_trellis_s_2m_0_table,".trellis_2Darray0");
#endif /* WE_ARE_DEFINING_VARIABLES */
EXTERN sint15 union_v34_rx_trellis_s_2m_0_table [4 * 3];
#define v34_rx_trellis_s_2m_0_table union_v34_rx_trellis_s_2m_0_table
#define _v34_rx_trellis_s_2m_0_table _union_v34_rx_trellis_s_2m_0_table
asm ("	.asg _union_v34_rx_trellis_s_2m_0_table, union_v34_rx_trellis_s_2m_0_table");

#ifdef WE_ARE_DEFINING_VARIABLES
#pragma DATA_SECTION (union_v34_rx_trellis_s_2m_1_table,".trellis_2Darray1");
#endif /* WE_ARE_DEFINING_VARIABLES */
EXTERN sint15 union_v34_rx_trellis_s_2m_1_table [4 * 3];
#define v34_rx_trellis_s_2m_1_table union_v34_rx_trellis_s_2m_1_table
#define _v34_rx_trellis_s_2m_1_table _union_v34_rx_trellis_s_2m_1_table
asm ("	.asg _union_v34_rx_trellis_s_2m_1_table, union_v34_rx_trellis_s_2m_1_table");

#ifdef WE_ARE_DEFINING_VARIABLES
#pragma DATA_SECTION (union_v34_rx_trellis_old_scores,".trellis_old_scores");
#endif /* WE_ARE_DEFINING_VARIABLES */
EXTERN uint16 union_v34_rx_trellis_old_scores [16];
#define v34_rx_trellis_old_scores union_v34_rx_trellis_old_scores
#define _v34_rx_trellis_old_scores _union_v34_rx_trellis_old_scores
asm ("	.asg _union_v34_rx_trellis_old_scores, union_v34_rx_trellis_old_scores");

#ifdef WE_ARE_DEFINING_VARIABLES
#pragma DATA_SECTION (union_v34_rx_trellis_distance_4D,".trellis_4Darray");
#endif /* WE_ARE_DEFINING_VARIABLES */
EXTERN sint15 union_v34_rx_trellis_distance_4D [40];
#define v34_rx_trellis_distance_4D union_v34_rx_trellis_distance_4D
#define _v34_rx_trellis_distance_4D _union_v34_rx_trellis_distance_4D
asm ("	.asg _union_v34_rx_trellis_distance_4D, union_v34_rx_trellis_distance_4D");

asm ("	.ref _union_v34_rx_trellis_s_2m_0_table");
asm ("	.ref _union_v34_rx_trellis_s_2m_1_table");
asm ("	.ref _union_v34_rx_trellis_old_scores");
asm ("	.ref _union_v34_rx_trellis_distance_4D");

#ifdef WE_ARE_DEFINING_VARIABLES
#pragma DATA_SECTION (circ_v34_tx_decor_buffer, ".circ_v34_tx_decor_buffer")
#endif /* WE_ARE_DEFINING_VARIABLES */
EXTERN fract CIRCULAR circ_v34_tx_decor_buffer [2*V34_DECOR_TAPS];
#define  v34_tx_decor_buffer  circ_v34_tx_decor_buffer
#define _v34_tx_decor_buffer _circ_v34_tx_decor_buffer
asm ("	.asg _circ_v34_tx_decor_buffer, circ_v34_tx_decor_buffer");
asm ("	.ref _circ_v34_tx_decor_buffer");

/* ************************************************************************* */
/*
 *	Special data for ATA's built for TI 55x
 *
 */

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */
#endif /* _DATA_SPECIAL_H */
