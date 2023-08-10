
/* ************************************************************************* */
/*
 *	constph2.h
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
 *	Module:		LIBPH2
 *
 *	This file contains phase2 defines.
 *
 *	THIS FILE IS THE SAME AS:
 *		lib/ptloop.inc
 *		lib/ptloop!.dsp
 *		lib/ptloop.dsp
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 19:59:18  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _LIBPH2_CONSTPH2_H
#define _LIBPH2_CONSTPH2_H

#include "lib34n/const34n.h"
#include "include/ph2.h"
#include "lib34/compile.h"

	/* ***************************************************************** */
	/*
	 *	Constants used within the phase 2 tx/rx foreground processing.
	 */

#define PH2_RXTX_COEF_SIZE					41
#define PH2_TX_DATA_SIZE					PH2_RXTX_COEF_SIZE - 1
#define PH2_RX_DATA_SIZE					PH2_RXTX_COEF_SIZE - 1

#define	PH2_TX_L1_GAIN						UFRACT(0x44C0)
#define	PH2_TX_L2_GAIN						UFRACT(0x2260)
#define PH2_TX_INTERPOLATOR_SIZE			2

#define	PH2_RX_CHECKER_COUNT				96		 /* 9K6 */
#define	PH2_RX_CHECKER_LENGTH				10		 /* 100ms * 9.6 / PH2_RX_CHECKER_COUNT */
#define	PH2_RX_CHECKER_THRESHOLD			FRACT (0xd654)	 /* (-45dBm-6.184+10log(PH2_RX_CHECKER_COUNT)) * 1024/(10log(2)) */

#define	PH2P_SAMPLE_MAX_PH2B_BLOCKS			50		 /* including the 0th block */
				/* data/ph2b libph2/ph2inf! libph2/ph2inf staph2/probtest */

	/* ***************************************************************** */
	/*
	 *	lib34n/ph2probr
	 *
	 *	Constants used by negotiation results processing.
	 */

#define	PH2P_NO_CARRIERS	    			2
#define	PH2P_NO_SYMBOL_RATES				6
#define	PH2P_NO_PREEMPHASIS					11
#define	PH2P_NO_TONES						25
#define	PH2P_NO_DATA_RATES					V34N_MAX_MAXRATE
#define	PH2P_NO_PREEQ_BINS					9

	/* ***************************************************************** */
	/*
	 *	lib34c/ph2fefo, lib34c/ph2powr
	 *
	 *	Constants used within the probing background processing.
	 *	These constants are also used within the fe-fo and power measurements.
	 */

#define	PH2P_PRE_FEFO_PROCESS_LENGTH		768		/* used */
#define	PH2P_FEFO_PROCESS_LENGTH			1536	/* routine by 128 blocks */
#define	PH2P_L1_PROCESS_LENGTH				1536	/* 160ms * 9.6, 12*128 */
/* define	PH2P_L2_PROCESS_LENGTH			3072 */	/* 320ms * 9.6, 24*128 */
#define	PH2P_L2_PROCESS_LENGTH				2816	/* 320ms * 9.6, 22*128 */

#define	PH2P_PRE_FEFO_OFFSET				0		/* not used, same as below */
#define	PH2P_FEFO_OFFSET					0
#define	PH2P_L1_OFFSET						0
#define	PH2P_L2_OFFSET						PH2P_L1_OFFSET + PH2P_L1_PROCESS_LENGTH

	/* ***************************************************************** */
	/*
	 *	lib34c/bg_ph2
	 *
	 *	Constants used within the probing background control processing.
	 */

#define	PH2B_INITIALIZE_START_BY_128		0		/*  */

#define	PH2B_FEFO_START_BY_128				0		/*  */
#define	PH2B_PRE_FEFO_START_BY_128			6		/* PH2P_PRE_FEFO_PROCESS_LENGTH/128 */
#define	PH2B_FEFO_COUNT_OF_128				12		/* PH2P_FEFO_PROCESS_LENGTH/128 */

#define	PH2B_L1_START_BY_128				0		/*  */
#define	PH2B_L1_COUNT_OF_128				12		/* PH2P_L1_PROCESS_LENGTH/128 */

#define	PH2B_L2_START_BY_128				12		/* fixed from above, 0+12 */
/* define	PH2B_L2_COUNT_OF_128			24 */	/* PH2P_L2_PROCESS_LENGTH/128 */
#define	PH2B_L2_COUNT_OF_128				22		/* PH2P_L2_PROCESS_LENGTH/128 */

/* define	PH2B_POST_L2_START_BY_128		36 */	/* fixed from above, 12+24 */
#define	PH2B_POST_L2_START_BY_128			34		/* fixed from above, 12+22 */

	/* ***************************************************************** */
	/*
	 *	lib34c/ph2fefo, lib34c/ph2powr, others
	 *
	 *	Constants used by power processing and other routines.
	 */

#define	PH2P_NO_BINS						32		/* both fe-fo and power */
#define	PH2P_NO_BINS_x2						64		/* powr, probr, org, probtest */
#define	PH2P_WINDOW_LENGTH					64		/* both fe-fo and power */
#define	PH2P_WINDOW_LENGTH_NOISE			128		/* power only */
#define PH2P_BLOCKSIZE						128		/* power only */

	/* ***************************************************************** */
	/*
	 *	lib34c/ph2powr
	 *
	 *	Constants used by power processing.
	 */

#define	PH2P_POWR_DECIMATE					16
#define	PH2P_POWR_BLOCKSIZE_OVER_DECIMATE	8
#define	PH2P_POWR_LOG2_DECIMATE				4	/* for decimate by 16 */
#define	PH2P_POWR_POWER_LPF_SLEW			-9
#define	PH2P_POWR_ADJUSTED_POWER_LPF_SLEW	(PH2P_POWR_POWER_LPF_SLEW + PH2P_POWR_LOG2_DECIMATE)
#define PH2P_POWR_LEADING_ZERO_LENGTH		128

#define	PH2P_POWR_RESULT_PRECISION			3

	#define	PH2P_POWR_RX_PRECISION			2

	/* ***************************************************************** */
	/*
	 *	lib34c/ph2fefo
	 *
	 *	Constants used by fe-fo calculations.
	 */

#define	PH2P_FEFO_LOWEST_BIN_INDEX			5
#define	PH2P_FEFO_BIN_STEP_MIN				2
#define	PH2P_FEFO_BIN_COUNT					8
#define	PH2P_FEFO_PHASE_STEP				2		/* 128/WINDOW_LENGTH */
#define	PH2P_FEFO_START_BIN_PHASE_INIT		(128 - PH2P_FEFO_PHASE_STEP * PH2P_FEFO_LOWEST_BIN_INDEX)

#define PH2P_FEFO_MEASUREMENT_HOLDOFF		128
#define PH2P_FEFO_MAX_OFFSET_DW_K			FRACT (1092)	/* 65536*10Hz/9600*PH2P_FEFO_OUTER_DECIMATE_RATIO*PH2P_FEFO_INNER_DECIMATE_RATIO */
#define PH2P_FEFO_MAX_OFFSET_DW_K_ADJ		FRACT (1092*8)	/* 8 = 2^PH2P_FEFO_FREQUENCY_RATIO */

#define	PH2P_FEFO_BLOCKSIZE_OVER_DECIMATE	8		/* 128/inner/outer */
#define PH2P_FEFO_OUTER_DECIMATE_RATIO		4
#define PH2P_FEFO_INNER_DECIMATE_RATIO		4

#define PH2P_FEFO_FREQUENCY_RATIO			3		/* 8.0 */
#define PH2P_FEFO_OUTER_LPF_SLEW 			-7		/* .01 ~ 1/128 = 2^-7 */
#define PH2P_FEFO_INNER_LPF_SLEW 			-7		/* .01 ~ 1/128 = 2^-7 */
/* define PH2P_FEFO_MAX_FREQUENCY_OFFSET	20.0 */	/* ??? not implemente */

/* define PH2P_FEFO_OUTER_RATIO				(OUTER_DECIMATE_RATIO) */					/* 4 */
/* define PH2P_FEFO_INNER_RATIO				(INNER_DECIMATE_RATIO * PH2P_FEFO_OUTER_RATIO) */	/* 4 * 4 */
/* define PH2P_FEFO_FINAL_RATIO				(PH2P_FEFO_FREQUENCY_RATIO  * PH2P_FEFO_INNER_RATIO) */	/* 8.0 * 4 * 4 */
#define PH2P_FEFO_LOG_OUTER_RATIO			2	/* log2 (outer decimate) */
#define PH2P_FEFO_LOG_INNER_RATIO			4	/* log2 (inner*outer decimate) */

#define PH2P_FEFO_ADJ_OUTER_SLEW			(PH2P_FEFO_OUTER_LPF_SLEW + PH2P_FEFO_LOG_OUTER_RATIO)		/* ~log2(.01 * 4) */
#define PH2P_FEFO_ADJ_INNER_SLEW			(PH2P_FEFO_INNER_LPF_SLEW + PH2P_FEFO_LOG_INNER_RATIO)		/* ~log2(.01 * 4 * 4 */

#define PH2P_FEFO_DOWNSHIFT					-6	/* log2(1/nx) */
#define	PH2P_FEFO_DOWNSHIFT_HI				(16 + PH2P_FEFO_DOWNSHIFT)
#define PH2P_FEFO_ADJ_OUTER_SLEW_HI			(16 + PH2P_FEFO_ADJ_OUTER_SLEW)

	/* ***************************************************************** */
	/*
	 *	lib34c/ph2fefo
	 *
	 *	Constants used by fe-fo linear regression calculations.
	 *
	 *	Linear regression constants:
	 *
	 *	M_ADJUST        4        E 0.465373
	 *  B_ADJUST        0      1/E 2.148809
	 *
	 *  M  0.052631 *       16 = 0.842105 => 27594.10    27594  M*2^M_ADJUST
	 *  B -0.63157  *        1 = -0.63157 => -20695.5   -20696  B*2^B_ADJUST
	 *
	 *
	 *	ph2p_fefo_scaled_x_i_table:
	 *
	 *	const 0 -0.36842  * 2.148809 = -0.79166  => -25941.3   -25941  const 0/E
	 *	const 1 -0.26315  * 2.148809 = -0.56547  => -18529.5   -18530  const 1/E
	 *	const 2 -0.15789  * 2.148809 = -0.33928  => -11117.7   -11118  const 2/E
	 *	const 3 -0.05263  * 2.148809 = -0.11309  => -3705.90    -3706  const 3/E
	 *	const 4  0.052631 * 2.148809 =  0.113095 => 3705.904     3706  const 4/E
	 *	const 5  0.157894 * 2.148809 =  0.339285 => 11117.71    11118  const 5/E
	 *	const 6  0.263157 * 2.148809 =  0.565476 => 18529.52    18530  const 6/E
	 *	const 7  0.368421 * 2.148809 =  0.791666 => 25941.33    25941  const 7/E
	 *
	 */

#define	PH2P_FEFO_DOWNSHIFT_LIN_REG			-3
#define	PH2P_FEFO_DOWNSHIFT_LIN_REG_HI		(16 + PH2P_FEFO_DOWNSHIFT_LIN_REG)

#define	PH2P_FEFO_X_COORD_SCALE_M_ADJ		 4
#define	PH2P_FEFO_X_COORD_SCALE_M_ADJ_x_M	 FRACT (27594)	/* M * 2^M_ADJUST */
#define	PH2P_FEFO_X_COORD_OFFSET_B_ADJ		 0
#define	PH2P_FEFO_X_COORD_OFFSET_B_ADJ_x_B	 FRACT (-20696)	/* B * 2^B_ADJUST */

#define PH2P_BG_SAMPLE_SIZE					 1536+128+1536+128

/* ************************************************************************* */
#endif /* _LIBPH2_CONSTPH2_H */
