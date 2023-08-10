
/* ************************************************************************* */
/*
 *	dtmf.h
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
 *	Module:		LIBTEL
 *
 *	DTMF digit detection symbols.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 19:50:34  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _INCLUDE_DTMF_H
#define _INCLUDE_DTMF_H

#define DTMF__DIGIT_0			0
#define DTMF__DIGIT_1			1
#define DTMF__DIGIT_2			2
#define DTMF__DIGIT_3			3
#define DTMF__DIGIT_4			4
#define DTMF__DIGIT_5			5
#define DTMF__DIGIT_6			6
#define DTMF__DIGIT_7			7
#define DTMF__DIGIT_8			8
#define DTMF__DIGIT_9			9
#define DTMF__DIGIT_A			10
#define DTMF__DIGIT_B			11
#define DTMF__DIGIT_C			12
#define DTMF__DIGIT_D			13
#define DTMF__DIGIT_STAR		14
#define DTMF__DIGIT_POUND		15

#define DTMF__FAIL_MINSIG		0x0100
#define DTMF__FAIL_RELPEAK		0x0200
#define DTMF__FAIL_TWIST		0x0400
#define DTMF__FAIL_2NDHARM		0x0800
#define DTMF__FAIL_NEWDIGIT		0x1000

#define DTMF__DIGIT_CODE		0x4000
#define DTMF__DIGIT_VALID		0x8000

/* these are used only for dtmf digit conversion routines */
#define DTMF__LOWERCASE			0
#define DTMF__UPPERCASE			1

/* ************************************************************************* */
#endif /* _INCLUDE_DTMF_H */
