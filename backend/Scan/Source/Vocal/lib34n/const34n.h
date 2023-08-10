
/* ************************************************************************* */
/*
 *	const34n.h
 *
 *	(C) 1995 - 2006 VOCAL Technologies, Ltd.
 *
 *	ALL RIGHTS RESERVED.  PROPRIETARY AND CONFIDENTIAL.
 *
 *	VOCAL Technologies, Ltd.
 *	90A John Muir Drive.
 *	Buffalo, NY  14228
 *
 *	Product:	MODEM 101
 *
 *	Module:		LIB34N
 *
 *	This file provides the V.34 negotiation constants.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 19:59:05  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _LIB34N_CONST34N_H
#define _LIB34N_CONST34N_H

	/*
	 *	V.34 maximum parameter settings
	 */

#define		V34N_MAX_SYMBOL						5		/* value */
#define		V34N_MAX_MAXRATE					14		/* value 33.6 */
#define		V34N_MAX_PREEMPH					10		/* value */
#define		V34N_MAX_TRELLIS					2		/* value */
#define		V34N_MAX_CLOCK						2		/* value */

#define		V34N_MAX_TRN_LENGTH					127		/* 127*35ms */

	/*
	 *	Software constrained V.34 parameter masks and limits
	 */

#define		V34N_SUPPORTED_SYMBOL				0x003f	/* mask */

#define		V34N_SUPPORTED_LO_CARRIER			0x003f	/* mask */
#define		V34N_SUPPORTED_HI_CARRIER			0x003f	/* mask */

#define		V34N_SUPPORTED_RATES				0x3fff	/* mask, 33.6 */

#define		V34N_SUPPORTED_HI_RATES				0x0001	/* mask, allow 31.2 33.6 */
#define		V34N_SUPPORTED_REDUCTION			0x0001	/* mask */
#define		V34N_SUPPORTED_CME					0x0000	/* mask */
#define		V34N_SUPPORTED_NONLINEAR			0x0001	/* mask */
#define		V34N_SUPPORTED_PRECODING			0x0001	/* mask */
#define		V34N_SUPPORTED_SHAPING				0x0001	/* mask */
#define		V34N_SUPPORTED_16POINT				0x0001	/* mask */
#define		V34N_SUPPORTED_ASYMMETRIC			0x0001	/* mask */
#define		V34N_SUPPORTED_AUXILIARY			0x0001	/* mask */
#define		V34N_SUPPORTED_DIFFERENCE			0		/* value */
#define		V34N_SUPPORTED_TRELLIS				0		/* value */
#define		V34N_SUPPORTED_CLOCK				2		/* value */

#define		V34N_SUPPORTED_16POINT_CC			1		/* mask */
#define		V34N_SUPPORTED_ASYMMETRIC_CC		1		/* mask */

	/*
	 *	V.34 phase 2 probing results
	 */

#define		PH2N_REPORT_FREQUENCY_OFFSET		1		/* boolean */

	/*
	 *	V.34 phase 2 software options
	 */

#define		PH2N_FORCE_PROBING_MINIMUM_RATE		1		/* boolean */
#define		PH2N_FORCE_INFO1C_SUPPORTED_SYMBOLS	1		/* boolean */
#define		PH2N_FORCE_INFO1A_SUPPORTED_SYMBOLS	0		/* boolean */
#define		PH4N_FORCE_ONLY_DATA_RATE_OPTIONS	0		/* boolean */

	/*
	 *	V.34 phase 3 software options
	 */

#define		PH3N_USE_MD_TRAINING				0		/* boolean */
#define		PH3N_USE_FREQUENCY_OFFSET			1		/* boolean */

	/*
	 *	V.34 phase 4 software options
	 */

#define		PH4N_MUST_HONOR_TX_TX_DATA_RATE		0		/* boolean */
#define		PH4N_MUST_HONOR_TX_RX_DATA_RATE		0		/* boolean */
#define		PH4N_MUST_HONOR_RX_TX_DATA_RATE		0		/* boolean */
#define		PH4N_MUST_HONOR_RX_RX_DATA_RATE		0		/* boolean */

	/*
	 *"	V.34 half duplex fax relay negotiation constants.
	 */

#define		V34FHD_MPH_MP0_MASK					0x1f
#define		V34FHD_MPH_MP1_MASK					0x07
#define		V34FHD_MPH_MP0_SIZE					9		/* ceil ((88-3-16) /  8)     octets */
#define		V34FHD_MPH_MP1_SIZE					22		/* ceil ((188-1-16) /  8)     octets */
#define		V34FHD_MPH_MAX_SIZE					22		/* ceil ((188-1-16) /  8)     octets */
#define		V34FHD_MPH_MP0_COUNT				3		/* ceil ((88-3-16) / 16) - 2  words */
#define		V34FHD_MPH_MP1_COUNT				9		/* ceil ((188-1-16) / 16) - 2  words */

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

#define		PARM_SYMBOL_RATE_2400				0x0001	/* 0 */
#define		PARM_SYMBOL_RATE_2743				0x0002	/* 1 */
#define		PARM_SYMBOL_RATE_2800				0x0004	/* 2 */
#define		PARM_SYMBOL_RATE_3000				0x0008	/* 3 */
#define		PARM_SYMBOL_RATE_3200				0x0010	/* 4 */
#define		PARM_SYMBOL_RATE_3429				0x0020	/* 5 */

#define		s2400								0x0
#define		s2743								0x1
#define		s2800								0x2
#define		s3000								0x3
#define		s3200								0x4
#define		s3429								0x5

#define		PARM_DATA_RATE_NONE					0x0000	/* 0 */
#define		PARM_DATA_RATE_2400					0x0001	/* 1 */
#define		PARM_DATA_RATE_4800					0x0002	/* 2 */
#define		PARM_DATA_RATE_7200					0x0004	/* 3 */
#define		PARM_DATA_RATE_9600					0x0008	/* 4 */
#define		PARM_DATA_RATE_12000				0x0010	/* 5 */
#define		PARM_DATA_RATE_14400				0x0020	/* 6 */
#define		PARM_DATA_RATE_16800				0x0040	/* 7 */
#define		PARM_DATA_RATE_19200				0x0080	/* 8 */
#define		PARM_DATA_RATE_21600				0x0100	/* 9 */
#define		PARM_DATA_RATE_24000				0x0200	/* a */
#define		PARM_DATA_RATE_26400				0x0400	/* b */
#define		PARM_DATA_RATE_28800				0x0800	/* c */
#define		PARM_DATA_RATE_31200				0x1000	/* d */
#define		PARM_DATA_RATE_33600				0x2000	/* e */
#define		PARM_DATA_RATE_ITU2					0x4000	/* f */

#define		dNONE								0x0
#define		d2400								0x1
#define		d4800								0x2
#define		d7200								0x3
#define		d9600								0x4
#define		d12000								0x5
#define		d14400								0x6
#define		d16800								0x7
#define		d19200								0x8
#define		d21600								0x9
#define		d24000								0xa
#define		d26400								0xb
#define		d28800								0xc
#define		d31200								0xd
#define		d33600								0xe
#define		dITU2								0xf

#endif /* _LIB34N_CONST34N_H */
