
/* ************************************************************************* */
/*
 *	v34vastr.h
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
 *	This file contains struct definitions cmn files.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 19:33:25  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _DATA_V34VASTR_H
#define _DATA_V34VASTR_H

/* ************************************************************************* */

typedef struct {
	fract32	delta32;
	fract32 phase32;
	sint15	k;
} powr_phase_offset_t;

typedef struct {
	sint15	bin;
	fract40	*DFT_ptr40;
	fract40 *spectr_ptr40;
} powr_variable_setup_table_t;

/* ************************************************************************* */

#endif /* _DATA_V34VASTR_H */
