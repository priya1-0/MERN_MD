
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
 *	Module:		MNP5
 *
 *	This file contains the private parameter declarations/definitions
 *	for the MNP5 module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 20:31:23  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _MNP5_LOCALD_H
#define _MNP5_LOCALD_H

/* ************************************************************************* */
/*
 * adaptive frequency structures
 *
 */

typedef struct {
	uint8	freq;
	uint8	indx;
} freq_table_t;

typedef struct {
	uint8	header;
	uint8	body;
} token_table_t;

/* ************************************************************************* */

typedef struct {

	freq_table_t _tx_freq_table [256];		/* transmit table */
	freq_table_t _rx_freq_table [256];		/* receive table */
	octet	_char_table [256];				/* character table */

/* ************************************************************************* */
	/*
	 * encoder variables
	 *
	 */

	sint31	_tx_chars_in;
	sint31	_tx_bytes_out;

	uint8	_tx_body;
	uint8	_tx_body_length;
	uint8	_mnp5_tx_header;
	uint8	_tx_input_bit_count;
	uint8	_tx_output_byte;
	octet	_tx_repeat_char;
	uint8	_tx_repeat_char_count;
	uint8	_tx_repeat_guard_count;

/* ************************************************************************* */
	/*
	 * decoder variables
	 *
	 */

	sint31	_rx_bytes_in;
	sint31	_rx_chars_out;

	uint8	_rx_body;
	uint8	_rx_body_length;
	uint8	_rx_body_ones_count;
	uint8	_rx_build_bit_count;
	uint8	_rx_input_val;
	uint8	_rx_header;
	bool	_rx_header_needed;
	uint8	_rx_input_body;
	uint8	_rx_input_header;
	uint8	_rx_input_bit_count;
	octet	_rx_repeat_char;
	uint8	_rx_repeat_char_count;
	uint8	_rx_repeat_guard_count;

} mnp5_local_t;

/* ************************************************************************* */

#define MNP5_LOCAL_DATA mnp5_local_t mnp5_local
DEF_DATA(mnp5_local_t, mnp5_local)
#define MNP5_LOCAL USE_DATA(mnp5_local)

/* ************************************************************************* */

#define tx_freq_table						(MNP5_LOCAL._tx_freq_table)
#define rx_freq_table						(MNP5_LOCAL._rx_freq_table)
#define char_table							(MNP5_LOCAL._char_table)

#define mnp5_tx_chars_in					(MNP5_LOCAL._tx_chars_in)
#define mnp5_tx_bytes_out					(MNP5_LOCAL._tx_bytes_out)
#define tx_body								(MNP5_LOCAL._tx_body)
#define tx_body_length						(MNP5_LOCAL._tx_body_length)
#define mnp5_tx_header							(MNP5_LOCAL._mnp5_tx_header)
#define tx_input_bit_count					(MNP5_LOCAL._tx_input_bit_count)
#define tx_output_byte						(MNP5_LOCAL._tx_output_byte)
#define tx_repeat_char						(MNP5_LOCAL._tx_repeat_char)
#define tx_repeat_char_count				(MNP5_LOCAL._tx_repeat_char_count)
#define tx_repeat_guard_count				(MNP5_LOCAL._tx_repeat_guard_count)

#define mnp5_rx_bytes_in					(MNP5_LOCAL._rx_bytes_in)
#define mnp5_rx_chars_out					(MNP5_LOCAL._rx_chars_out)
#define rx_body								(MNP5_LOCAL._rx_body)
#define rx_body_length						(MNP5_LOCAL._rx_body_length)
#define rx_body_ones_count					(MNP5_LOCAL._rx_body_ones_count)
#define rx_build_bit_count					(MNP5_LOCAL._rx_build_bit_count)
#define rx_input_val						(MNP5_LOCAL._rx_input_val)
#define rx_header							(MNP5_LOCAL._rx_header)
#define rx_header_needed					(MNP5_LOCAL._rx_header_needed)
#define rx_input_body						(MNP5_LOCAL._rx_input_body)
#define rx_input_header						(MNP5_LOCAL._rx_input_header)
#define rx_input_bit_count					(MNP5_LOCAL._rx_input_bit_count)
#define rx_repeat_char						(MNP5_LOCAL._rx_repeat_char)
#define rx_repeat_char_count				(MNP5_LOCAL._rx_repeat_char_count)
#define rx_repeat_guard_count				(MNP5_LOCAL._rx_repeat_guard_count)

/* ************************************************************************* */

#endif /* _MNP5_LOCALD_H */
