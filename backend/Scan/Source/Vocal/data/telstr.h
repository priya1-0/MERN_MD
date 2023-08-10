
/* ************************************************************************* */
/*
 *	telstr.h
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
 *	This file contains struct definitions for tel files.
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

#ifndef _DATA_TELSTR_H
#define _DATA_TELSTR_H

/* ************************************************************************* */

/* ************************************************************************* */

typedef struct {
	uint16 status_bit;
	uint16 detect_mask;
	const uint16 *entry_table;
	uint16 count_limit;
} cp_t;

typedef struct {
	uint16 active_change;
	sint15 active_timer;
	uint16 active_count;
} cpd_t;

typedef struct {
	phase_t initial_phase;
	phase_t current_phase;
	ufract tone_level;
} tone_generator_buffer_t;

typedef struct {
	fract dtmf_coef;	/* 2.14 */
	uint16 dtmf_number_of_iterations;
	fract dtmf_scale;
} dtmf_goertzel_coef_t;

typedef struct  {
	phase_t demod_frequency;
	phase_t phase_limit;
	fract threshold;
	sint15 off_to_on;
	sint15 on_keep;
	sint15 on_to_off;
	uint16 mask;
} tone_detector_coef_t;

typedef struct  {
	phase_t demod_phase;
	fract32 first_real32;
	fract32 second_real32;
	fract32 first_imag32;
	fract32 second_imag32;
	phase_t previous_phase;
	fract32 ref32;
	uint16 detect_value;
	sint15 off_counter;
	sint15 on_counter;
} tone_detector_vars_t;

/* ************************************************************************* */

#endif /* _DATA_TELSTR_H */
