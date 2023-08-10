
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
 *	Module:		BTLZ
 *
 *	This file contains the private parameter declarations/definitions
 *	for the BTLZ module.
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

#ifndef _BTLZ_LOCALD_H
#define _BTLZ_LOCALD_H

/* ************************************************************************* */

#include "include/dp.h"

/* ************************************************************************* */
/*
 * string dictionary (and string buffer)
 *
 */

typedef struct {

	uint8	_symbol [2*DP_BTLZ_P1__MAX];	/* raw data characters  */
	uint16	_right [2*DP_BTLZ_P1__MAX];		/* "right" (next) index */
	uint16	_deplist [2*DP_BTLZ_P1__MAX];	/* dependent list index */
	uint16  _parent [2*DP_BTLZ_P1__MAX];	/* parent_index */
	uint8	_buff [DP_BTLZ_P2__MAX+1];		/* decoder string-reversal buffer */

/* ************************************************************************* */
/*
 * common encoding variable
 *
 */

	uint8	_btlz_n_1;		/* calculate from v42_bis_n_2 (in less 8) */
	uint16	_btlz_n_2;		/* this is btlz p1                        */
	uint8	_btlz_n_7;		/* this is btlz p2                        */

	uint16	_SS_s_ptr;		/* not used */
	uint16	_SS_i_ptr;		/* not used */

/* ************************************************************************* */
	/*
	 * encoder variables
	 *
	 */

	uint8	_tx_stleng;					/* current string length */
	uint8	_tx_esc_char;				/* escape character */

	uint16	_tx_c_1;					/* next empty entry */
	uint8	_tx_c_2;					/* current codeword size (in less 8) */
	uint16	_tx_c_3;					/* threshold for codeword size change */
	uint16	_tx_prev_c_1;				/* previous value of e.c_1 */

	uint16	_tx_s_ptr;					/* search pointer */
	uint16	_tx_c_ptr;					/* current pointer */

	uint16	_tx_input_byte;				/* character passed to encoder */
	uint8	_tx_ob;						/* output holding uint8 */
	uint8	_tx_ob_bitcnt;				/* number of bits in ob */
	uint16	_tx_cw;						/* codeword to send */

	uint16	_tx_tcount;					/* anti-expansion . character count */
	uint16	_tx_comp_bits;				/* anti-expansion . compressed bit count */
	uint16	_tx_axf_delay;				/* anti-expansion . delay setting */

	bool	_tx_decoder;				/* not used	- always FALSE */
	bool	_tx_splitdict;				/* not used	- always FALSE */
	bool	_tx_transparent;			/* if encode is in transparent mode */

	bool	_tx_dictfull;				/* indicates dictionary full */
	bool	_tx_inhibit;				/* indicates inhibiting dictionary updates */

	bool	_tx_flushed;				/* indicates output stream has been flushed */

/* ************************************************************************* */
	/*
	 * decoder variables
	 *
	 */

	uint8	_rx_stleng;					/* current string string */
	uint8	_rx_esc_char;				/* escape character */

	uint16	_rx_c_1;					/* next empty entry */
	uint8	_rx_c_2;					/* current codeword size (in less 8) */
	uint16	_rx_c_3;					/* not used	- threshold for codeword size change */
	uint16	_rx_prev_c_1;				/* previous value of d.c_1 */

	uint16	_rx_s_ptr;					/* search pointer */
	uint16	_rx_c_ptr;					/* current pointer */
	uint16	_rx_l_ptr;					/* previous pointer */

	uint16	_rx_input_byte;				/* (MUST BE WORD) token passed to decoder */
	uint16	_rx_ib;						/* (MUST BE WORD) input holding uint8 */
	uint8	_rx_ib_bitcnt;				/* number of bits in ib */
	uint16	_rx_cw;						/* accumulated codeword */

	bool	_rx_decoder;				/* not used - always TRUE */
	bool	_rx_splitdict;				/* flag for simultaneous encode and decode */
	bool	_rx_transparent;			/* if decoder is in transparent mode */

	bool	_rx_dictfull;				/* indicates dictionary full */
	bool	_rx_inhibit;				/* indicates inhibiting dictionary updates */

	bool	_rx_bf_inh;					/* indicates buffer inhibits */
	bool	_rx_bf_full;				/* indicates buffer full */
	bool	_rx_mode_sw;				/* indicates the mode should switch */
	bool	_rx_escmode;				/* indicates previous escape character */

} btlz_local_t;

/* ************************************************************************* */

#define BTLZ_LOCAL_DATA btlz_local_t btlz_local
DEF_DATA(btlz_local_t, btlz_local)
#define BTLZ_LOCAL USE_DATA(btlz_local)

/* ************************************************************************* */

#define btlz_symbol							(BTLZ_LOCAL._symbol)
#define btlz_right							(BTLZ_LOCAL._right)
#define btlz_deplist						(BTLZ_LOCAL._deplist)
#define btlz_parent							(BTLZ_LOCAL._parent)
#define btlz_buff							(BTLZ_LOCAL._buff)

#define btlz_n_1							(BTLZ_LOCAL._btlz_n_1)
#define btlz_n_2							(BTLZ_LOCAL._btlz_n_2)
#define btlz_n_7							(BTLZ_LOCAL._btlz_n_7)

#define SS_s_ptr							(BTLZ_LOCAL._SS_s_ptr)
#define SS_i_ptr							(BTLZ_LOCAL._SS_i_ptr)

#define tx_stleng							(BTLZ_LOCAL._tx_stleng)
#define tx_esc_char							(BTLZ_LOCAL._tx_esc_char)
#define tx_c_1								(BTLZ_LOCAL._tx_c_1)
#define tx_c_2								(BTLZ_LOCAL._tx_c_2)
#define tx_c_3								(BTLZ_LOCAL._tx_c_3)
#define tx_prev_c_1							(BTLZ_LOCAL._tx_prev_c_1)
#define tx_s_ptr							(BTLZ_LOCAL._tx_s_ptr)
#define tx_c_ptr							(BTLZ_LOCAL._tx_c_ptr)
#define tx_input_byte						(BTLZ_LOCAL._tx_input_byte)
#define tx_ob								(BTLZ_LOCAL._tx_ob)
#define tx_ob_bitcnt						(BTLZ_LOCAL._tx_ob_bitcnt)
#define tx_cw								(BTLZ_LOCAL._tx_cw)
#define tx_tcount							(BTLZ_LOCAL._tx_tcount)
#define tx_comp_bits						(BTLZ_LOCAL._tx_comp_bits)
#define tx_axf_delay						(BTLZ_LOCAL._tx_axf_delay)
#define tx_decoder							(BTLZ_LOCAL._tx_decoder)
#define tx_splitdict						(BTLZ_LOCAL._tx_splitdict)
#define tx_transparent						(BTLZ_LOCAL._tx_transparent)
#define tx_dictfull							(BTLZ_LOCAL._tx_dictfull)
#define tx_inhibit							(BTLZ_LOCAL._tx_inhibit)
#define tx_flushed							(BTLZ_LOCAL._tx_flushed)

#define rx_stleng							(BTLZ_LOCAL._rx_stleng)
#define rx_esc_char							(BTLZ_LOCAL._rx_esc_char)
#define rx_c_1								(BTLZ_LOCAL._rx_c_1)
#define rx_c_2								(BTLZ_LOCAL._rx_c_2)
#define rx_c_3								(BTLZ_LOCAL._rx_c_3)
#define rx_prev_c_1							(BTLZ_LOCAL._rx_prev_c_1)
#define rx_s_ptr							(BTLZ_LOCAL._rx_s_ptr)
#define rx_c_ptr							(BTLZ_LOCAL._rx_c_ptr)
#define rx_l_ptr							(BTLZ_LOCAL._rx_l_ptr)
#define rx_input_byte						(BTLZ_LOCAL._rx_input_byte)
#define rx_ib								(BTLZ_LOCAL._rx_ib)
#define rx_ib_bitcnt						(BTLZ_LOCAL._rx_ib_bitcnt)
#define rx_cw								(BTLZ_LOCAL._rx_cw)
#define rx_decoder							(BTLZ_LOCAL._rx_decoder)
#define rx_splitdict						(BTLZ_LOCAL._rx_splitdict)
#define rx_transparent						(BTLZ_LOCAL._rx_transparent)
#define rx_dictfull							(BTLZ_LOCAL._rx_dictfull)
#define rx_inhibit							(BTLZ_LOCAL._rx_inhibit)
#define rx_bf_inh							(BTLZ_LOCAL._rx_bf_inh)
#define rx_bf_full							(BTLZ_LOCAL._rx_bf_full)
#define rx_mode_sw							(BTLZ_LOCAL._rx_mode_sw)
#define rx_escmode							(BTLZ_LOCAL._rx_escmode)

/* ************************************************************************* */

#endif /* BTLZ_LOCALD_H */
