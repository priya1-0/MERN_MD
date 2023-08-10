
/* ************************************************************************* */
/*
 *	modstr.h
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
 *	This file contains struct definitions for mod files.
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

#ifndef _DATA_MODSTR_H
#define _DATA_MODSTR_H

/* ************************************************************************* */

/* ************************************************************************* */

typedef struct {
	sint15 speed;			/* Modulation speed. It can be negative */
	uint16 hdlc_delay;		/* HDLC delay. */
	uint16 binary_delay;	/* BINARY delay. */
	state_t state;			/* Modulation start state. */
	uint16 fxpmp_code;		/* Fax pump code. */
} code_table_t;

typedef struct {
	sint15 offset;
	fract gain;
} fsk_interpolator_buffer_t;

typedef struct {
	sint15 width;
	fract  normal;
	fract  feedback;
} agc_2_slews_t;

typedef struct {
	fract sum;
	sint15 count;
	sint15 limit;
	fract save [3];
} energy_buffer_t;

typedef struct {
	fract32 error_sum32;
	fract32 post_ec_power_sum32;
	fract32 pre_ec_power_sum32;
	sint15 block_size_counter;
	sint15 block_size_value;
} statistics_buffer_t;

typedef struct {
	ufract		prescale;
	fract40		power_sum40;
	sint15		count_limit;
	sint15		count;
	fract		log2_power;
	fract		log2_count;
	fract		log2_difference;
	fract		db_difference;
	fract		db_power;
} powr_measurement_t;

/* ************************************************************************* */

#endif /* _DATA_MODSTR_H */
