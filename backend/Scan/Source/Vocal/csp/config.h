
/* ************************************************************************* */
/*
 *	config.h
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
 *	Module:		CSP
 *
 *	This file defines array sizes for variables related to the
 *	CSP module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 18:24:09  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _CSP_CONFIG_H
#define _CSP_CONFIG_H

/* ************************************************************************* */

#define CSP_CALL_LEVEL_MAX	8

#define NUMBER_OF_DIGITS_IN_CSP_DIAL_STRING	45		/* The size of the &Z command */

#define CSPC__NO_CS_IDX 0xFFFF
#define MAX_CSP_STRING_PARM_SIZE 40

enum {
	CSP_FCLASS,

	CSP_DEFAULT_PROFILE,
	CSC_RING_CNTR,
	CSC_DISCONNECT_REASON,

	CSP_MS_MOD,
	CSP_MS_AM,

	CSP_SLASH_V,

	CSP_SREG_S00,
	CSP_SREG_S01,
	CSP_SREG_S02,
	CSP_SREG_S03,
	CSP_SREG_S04,
	CSP_SREG_S05,
	CSP_SREG_S06,
	CSP_SREG_S07,
	CSP_SREG_S08,
	CSP_SREG_S09,
	CSP_SREG_S10,
	CSP_SREG_S11,
	CSP_SREG_S12,
	CSP_SREG_S14,
	CSP_SREG_S16,
	CSP_SREG_S18,
	CSP_SREG_S19,
	CSP_SREG_S20,
	CSP_SREG_S21,
	CSP_SREG_S22,
	CSP_SREG_S23,
	CSP_SREG_S24,
	CSP_SREG_S25,
	CSP_SREG_S26,
	CSP_SREG_S27,
	CSP_SREG_S28,
	CSP_SREG_S29,
	CSP_SREG_S30,
	CSP_SREG_S31,
	CSP_SREG_S32,
	CSP_SREG_S33,
	CSP_SREG_S36,
	CSP_SREG_S37,
	CSP_SREG_S38,
	CSP_SREG_S39,
	CSP_SREG_S40,
	CSP_SREG_S41,
	CSP_SREG_S46,
	CSP_SREG_S48,
	CSP_SREG_S80,
	CSP_SREG_S82,
	CSP_SREG_S86,
	CSP_SREG_S91,
	CSP_SREG_S92,
	CSP_SREG_S95,
	CSP_SREG_S99,
	CSP_SREG_S201,
	CSP_SREG_S202,
/* CSP_SREG_NUMBER, */

	CSP_NUMBER_OF_UINT8_COMMANDS
};

enum {
	CSP_UINT32_DUMMY,

	CSP_ASTR_S91,
	CSP_ASTR_VLS,
	CSP_MS_MIN,
	CSP_MS_MAX,

	CSP_NUMBER_OF_UINT32_COMMANDS
};

enum {
	CSP_BOOL_DUMMY,

	CSP_FUNC_Z,

	CSP_NUMBER_OF_BOOL_COMMANDS
};
#endif /* _CSP_CONFIG_H */
