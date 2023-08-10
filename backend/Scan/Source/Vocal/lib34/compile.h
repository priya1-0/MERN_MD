
/* ************************************************************************* */
/*
 *	compile.h
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
 *	Module:		LIB34
 *
 *	This file contains automatically generated data for knl constant.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 19:58:32  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _LIB34_COMPILE_H
#define _LIB34_COMPILE_H

#define	V34_TRN2_MSE_STACK_SIZE				10		/* data/other sta34/v34trn2 */
#define	V34_MSE_STRUCT_SIZE					4		/* data/other sta34/v34trn2 */

#define	PH2_AUTOCORREL_BUFFER_LENGTH		32		/* data/ph2v libph2/ph2dem! */
#define	PH2_LPF_DATA_BUFFER_LENGTH			6		/* data/ph2v libph2/ph2dem! */

#define V34_LEN_600T_ROUNDTRIP_ADJUST		24		/*  40 ms */
#define V34_LEN_8K0_ROUNDTRIP_ADJUST		40*8	/* 320 samples */

#define V34_MINIMUM_16PT_TRAIN_SPEED		3		/* lib34n/v34ph3 */
#define	V34_CORRECT_4_DBM_IN_6_10			FRACT (1361)	/* sta34/v34trn2 */

/* ************************************************************************* */

#define	V34_SYMBOL_VARIABLE_CONSTANT_LENGTH	22										/* data/ph3c lib34l/v34l! */
#define	V34_SYMBOL_FIXED_CONSTANT_LENGTH	27										/* data/ph3c lib34l/v34l! */
#define	V34_SYMBOL_CONSTANT_LENGTH			49		/* sum of above */					/* data/ph3c lib34l/v34l! */

#define	V34_SYMBOL_VARIABLE_DATA_LENGTH		15										/* data/ph3c lib34l/v34l! */
#define	V34_TX_CARRIER_DATA_LENGTH			 2										/* data/ph3c lib34l/v34l! */
#define	V34_RX_CARRIER_DATA_LENGTH			 4										/* data/ph3c lib34l/v34l! */
#define	V34_SYMBOL_DATA_LENGTH				21		/* sum of above */					/* data/ph3c lib34l/v34l! */

/* ************************************************************************* */

#define PH1_OLD_DETECT_METHOD_OPTION				/* libfsk/ansdet! libfsk/ansdet */
#undef  PH1S_TEST_CAPTURE_ANSAM_OPTION				/* stafsk/helper, stafsk/v8org */

#define	PH2_THRESHOLD_FIXED_OPTION					/* libph2/ph2dem libph2/ph2dem! data/ph2v */
#undef	PH2_TEST_PHASE_REVERSAL_OPTION				/* libph2/ph2dem libph2/ph2dem! */

#define PH2P_NEW_PROBING_PREEMPHASIS_METHOD_OPTION	/* data/ph2v, lib34c/ph2powr */
#define	PH2P_GAIN_ADJUST_OPTION						/* lib34c/ph2fefo lib34c/ph2powr */
#define	PH2P_RX_PRECISION_OPTION					/* lib34c/ph2fefo lib34c/ph2powr libph2/constph2 */

#define PH2S_USE_BG_POST_PROCESSING_OPTION			/* staph2/ph2org */
#define	PH2S_SHOW_STATE_CHANGES_OPTION				/* staph2/ph2org */
#undef	PH2S_CHANGES_V24_SIGNALS_OPTION				/* staph2/ph2org */
#undef	PH2S_PROBING_START_DELAY_OPTION				/* staph2/ph2org */
#define PH2S_TEST_RETRAIN_OPTION					/* data/ph2c lib34n/v34ph2 */
#define PH2P_SUM_ENERGY_MEASUREMENTS_OPTION			/* data/ph2v, lib34c/ph2powr */
#define PH2N_INFO_HANDSHAKE_FLAG_OPTION				/* lib34n/ph2info */

#define V34_USE_SAMPLE_ECHO_UPDATE_OPTION			/* lib34l/echoup! lib34l/echoup lib34l/ecloop */
#undef	V34_USE_BLOCKSIZE_2_UPDATE_OPTION			/* lib34l/echoup */
#define V34_USE_SAMPLE_PHASE_ROLL_CORRECTION_OPTION	/* lib34l/phroll! */
#define V34_CONDITIONAL_PHASE_ROLL_OPTION			/* lib34l/phroll! */
#define V34_INHIBIT_HALF_SECOND_OPTION				/* lib34l/phroll! */
#undef	V34_RENEG_DEBUG_CODE_OPTION					/* lib34l/v34ren */
#undef	V34_TRN2_USES_DEBUG_MSE_OPTION				/* data/other */
#define	V34_TEST_MSE_EVENTS							/* sta34/v34trn2 */

#undef	V34H_LOG_RECEIVED_XN_SIGNALS_OPTION			/* lib34h/v34dic lib34h/v34dec */
#undef	V34H_LOOPBACK_CHECK_ENABLED_OPTION			/* lib34h/v34dic */
#undef	V34H_RS_ENABLED_OPTION						/* lib34h/v34dec */

#undef	V34S_COMPILE_PREEMPH_RIPPLE_OPTION			/* sta34/helper */
#undef	V34S_COMPILE_LOGGER_ENABLED_OPTION			/* sta34/helper */
#define V34S_CONDITIONAL_ECC_OPTION					/* data/v34s sta34/v34org */
#undef	V34S_CHANGES_SOME_V24_SIGNALS_OPTION		/* sta34/v34org */

#define	V34_APPLY_ADJUSTED_PREEQ_WEIGHTS_OPTION		/*  */
#define	V34_USE_S2_FOR_S_DETECT_OPTION				/*  */
#define	V34_APPLY_POST_PREEQ_GAIN_OPTION			/*  */
#define	V34_USE_16PT_TRAIN_FROM_PH2_OPTION			/* lib34n/v34ph3 */
#define	V34_USE_SHAPING_FROM_PH2_OPTION			    /* lib34n/v34ph3 */
#undef	V34_PH2_SHAPING_INHIBITS_NONLINEAR_OPTION	/* lib34n/v34ph3 */

#undef  V34_USE_16PT_MSE_STATISTICS                 /* sta34/v34trn2 */

#undef	V34_USE_UNCORRECTED_MSE_OPTION				/* sta34/v34trn2 */
#define	K56_USE_UNCORRECTED_MSE_OPTION				/* lib56c/k56trn2 */
#define	V90_USE_UNCORRECTED_MSE_OPTION				/* lib90c/v90trn2 */
#undef	V92_USE_UNCORRECTED_MSE_OPTION				/* lib92c/v92trn2 */
#undef	V34S_USE_UNCORRECTED_MSE_OPTION				/* sta34/v34trn2 */
#undef	PH2P_V34_USE_UNCORRECTED_MSE_OPTION			/* libph2p/ph2rate */

#define V34S_CONTROL_BE_SLEWS_OPTION				/* sta34/v34org sta34/v34eqc */

#undef	V34_ENERGY_MONITOR_OPTION					/* sta34/v34mon lib34l/preeq lib34/vxxout */

#undef	PH2P_LX_LOG_POWER_DISPLAY_IN_COMMON			/* data/ph2s data/ph2b */

/* ************************************************************************* */

#ifndef	V34_USE_SAMPLE_PHASE_ROLL_CORRECTION_OPTION
#error V34_USE_SAMPLE_PHASE_ROLL_CORRECTION_OPTION ported
#endif /* V34_USE_SAMPLE_PHASE_ROLL_CORRECTION_OPTION */

/* ************************************************************************* */

#define	V34_BETTER_FINAL_EQUALIZER_SLEW_OPTION

/* ************************************************************************* */
/*
 *	V.34 half duplex options
 */

#define	OVERLAY_PH2F_TO_PH3F_OPTION
#undef	V34F_TRAIN_PRECODER_AFTER_PH3F_OPTION
#define	V34F_FORCE_1200_CONTROL_CHANNEL

/* ************************************************************************* */

#define	REMOVE_HELPER_TO_MAKE_SPACE_PH1
#define	REMOVE_HELPER_TO_MAKE_SPACE_PH3
#define	REMOVE_HELPER_TO_MAKE_SPACE_V17

#undef	REMOVE_TRACE_TO_MAKE_SPACE_PH2

#define	REMOVE_TEST_CODE_TO_MAKE_SPACE_PH1
#define	REMOVE_TEST_CODE_TO_MAKE_SPACE_PH2
#define	REMOVE_TEST_CODE_TO_MAKE_SPACE_V34

#define	MAKE_SPACE_BY_REMOVING_DUMMY_PH1
#define	MAKE_SPACE_BY_REMOVING_DUMMY_PH2
#define	MAKE_SPACE_BY_REMOVING_DUMMY_PH3

/* ************************************************************************* */

#undef	ENABLE_TX_IMPAIRMENTS

/* ************************************************************************* */

#undef	PCM_TEST_ENERGY_MONITOR_OPTION
#undef	PCM_TEST_FORCE_x_LAW

#endif /* _LIB34_COMPILE_H */
