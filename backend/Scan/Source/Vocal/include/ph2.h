
/* ************************************************************************* */
/*
 *	ph2.h
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
 *	Module:		INCLUDE
 *
 *	Define ph2 related symbols.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 19:50:33  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _INCLUDE_PH2_H
#define _INCLUDE_PH2_H

/* ************************************************************************* */

#define PH2_TX_RATE_CONV_DATA_BUFFER	24
#define PH2_RX_RATE_CONV_DATA_BUFFER	20
#define PH2_RATE_CONV_COEFS				122
#define SIXTEEN_ZEROES FRACT (0), FRACT (0), FRACT (0), FRACT (0), \
					   FRACT (0), FRACT (0), FRACT (0), FRACT (0), \
					   FRACT (0), FRACT (0), FRACT (0), FRACT (0), \
					   FRACT (0), FRACT (0), FRACT (0), FRACT (0)

#define	V34_TRN2_MSE_STACK_SIZE				10		/* data/other sta34/v34trn2 */
#define	V34_MSE_STRUCT_SIZE					4		/* data/other sta34/v34trn2 */

#define	PH2_AUTOCORREL_BUFFER_LENGTH		32		/* data/ph2v libph2/ph2dem! */
#define	PH2_LPF_DATA_BUFFER_LENGTH			6		/* data/ph2v libph2/ph2dem! */

#define _DM_								0x4000	/* data/ph3c lib34l/v34l! */
#define _PM_								0x0000	/* data/ph3c lib34l/v34l! */

#define V34_LEN_600T_ROUNDTRIP_ADJUST		24			/*  40 ms */

#define V34_MINIMUM_16PT_TRAIN_SPEED		3		/* lib34n/v34ph3 */

/* ************************************************************************* */

#define	V34_SYMBOL_VARIABLE_CONSTANT_LENGTH	22										/* data/ph3c lib34l/v34l! */
#define	V34_SYMBOL_FIXED_CONSTANT_LENGTH	27										/* data/ph3c lib34l/v34l! */
#define	V34_SYMBOL_CONSTANT_LENGTH			49		/* sum of above */					/* data/ph3c lib34l/v34l! */

#define	V34_SYMBOL_VARIABLE_DATA_LENGTH		15										/* data/ph3c lib34l/v34l! */
#define	V34_TX_CARRIER_DATA_LENGTH			 2										/* data/ph3c lib34l/v34l! */
#define	V34_RX_CARRIER_DATA_LENGTH			 4										/* data/ph3c lib34l/v34l! */
#define	V34_SYMBOL_DATA_LENGTH				21		/* sum of above */					/* data/ph3c lib34l/v34l! */

#define V34_PH2_COMMON_NAME_SIZE			30

/* ************************************************************************* */

#define	PH2P_RX_PRECISION_OPTION

#define	PH1_OLD_DETECT_METHOD_OPTION
#undef	PH1S_TEST_CAPTURE_ANSAM_OPTION

#define	PH2_THRESHOLD_FIXED_OPTION
#undef 	PH2_TEST_PHASE_REVERSAL_OPTION
#undef 	PH2_SMALL_CALL_K_DETECTOR_OPTION

/* ************************************************************************* */

#endif /* _INCLUDE_PH2_H */
