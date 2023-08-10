
/* ************************************************************************* */
/*
 *	test.h
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
 *	Define compile test options.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.2.6.2  2009/04/28 19:50:33  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _INCLUDE_TEST_H
#define _INCLUDE_TEST_H

#undef  TEST_REPORT_MP_FRAME_WORDS		/* V.34/V.90/K56Flex receive MP word reporting status */
#undef  TEST_REPORT_TX_FRAME_WORDS		/* V.34/V.90/K56Flex transmit MP word reporting status */
#undef  TEST_PH2_PROBING_DATA			/* Use ph2 L1/L2 data from file */
#undef  TEST_PH2_CALIBRATION_OPTION		/* Measure symbol & sample adjusts K, k */
#undef  TEST_V34_REPORT_DATA			/* V.34 information and MSE reporting status */
#undef  TEST_V34_PARSER_DEBUG			/* V.34 encoder/decoder debug information */
#undef	TEST_SIMULATE_RBS				/* V.90/K56Flex RBS simulation */
#undef	TEST_SIMULATE_PAD				/* V.90/K56Flex Digital PAD simulation */
#undef  TEST_TRANSMIT_IMPAIRMENTS		/* Change tx carrier/gain */
#undef  TEST_LSD_IMPULSE_NOISE			/* Add periodic impulse noise at input filter */
#undef  TEST_LSD_PHASE_HIT				/* Add periodic carrier phase hits at LSD demodulators */
#undef  TEST_LSD_FRAME_SLIP				/* Add periodic frame slips at fgmain */
#undef  TEST_LSD_PHASE_JITTER			/* Add carrier phase jitter at LSD demodulators */

#undef  TEST_12K0_RATE_CONVERT			/* 12k0 rate convert test code in fgmain */
#undef  TEST_FGMAIN_ECHO_GENERATION		/* Create test echo in fg_process */
#undef  TEST_FGMAIN_C_LOGGING			/* Record samples in fg_process */

#undef  TEST_REPORT_TONES				/* Reports tone detector mask changes */
#undef  TEST_REPORT_FGTHREADS			/* Reports the current thread table */

#undef  TEST_MIPS_MONITOR
#undef  DISABLE_FG_THREAD_EXECUTE_INLINE/* REQUIRED for mips monitor thread profiling */
#undef  TEST_DISPLAY_MIPS				/* dependent on test_mips_monitor */
#undef  TEST_CHANNEL_LIMIT

#undef  TEST_CALL_STATE_MONITOR			/* display ata/ipbx/rtp call states periodically */

#undef  TEST_CALL_RECORD				/* record pcm samples of a call	*/

#undef  TEST_VERBOSE_MDM_REASON
#undef  TEST_MATH_ON_STARTUP
#undef  TEST_FXAPP_FCLASS_1
#undef  TEST_DIGITAL_MILLIWATT

#undef  TEST_RING_DETECTION
#undef  TEST_RTP_REPORT
#undef  TEST_MSE_MEASURE
#undef  TEST_EYE_PATTERN_RECORD

#undef  TEST_SPEECH_DIRECT_LOOPBACK		/* loopback if using DO_SPEECH_DIRECT_INTERFACE */
#undef  TEST_SPEECH_ASM_LOOPBACK		/* note that if you turn on either of these, you probably also */
#undef  TEST_RTMSC_ALT_AUDIO_LOOPBACK	/* want to turn on DO_SPEECH_LARGE_ASM_BUFFERS in options.h */

#undef  MIP_SPEECH_ENCODE_MEASURE
#undef  MIP_SPEECH_DECODE_MEASURE

#undef  TEST_MINIMAL_JITTER_BUFFER

#undef  TEST_CNG_ROUTINES
#undef  TEST_ECHO_ROUTINES
#undef  TEST_EXPONENT_ROUTINES
#undef  TEST_BIQUAD_ROUTINES
#undef  TEST_LONGMULT_ROUTINES
#undef  TEST_TONEDT_SAMPLE_MODE

#undef  DO_THREAD_INTERRUPT_PROFILING	/* thread profiling from interrupt handler */
#undef  ENABLE_FAXHELP_RX_ROUTINES		/* fax display debug routines */
#undef  RECORD_SAMPLES_TO_CREATE_B1_FORCE_TRAIN	/* V17 fax force train data collection */
#undef  TEST_DUMP_BIND_INFO

#undef  TEST_TRACE_ALLOCS				/* Trace mbuf/ibuf allocations */

#undef  TEST_TAC12_ECC

#undef  DO_TEST_RSA						/* Assumes that DO_CRYPTO_RSA_ENCRYPT AND DO_CRYPTO_RSA_DECRYPT are also defined */
#undef  DO_TEST_RSA_GENERATE_KEY			/* Assumes that DO_TEST_RSA is defined */

#undef  TEST_RTP_STANDALONE				/* RTP code testing and developing */
#undef  TEST_RTP_MIRROR_LOOPBACK		/* RTP loopback, transmits only rtp packets received */
#undef  TEST_RTP_TX_TO_RX_QUEUE_LOOPBACK	/* RTP loopback from tx queue to rx queue; no tx packets generated */

#undef  DEBUG_SAVE_BITSTREAM			/* Preserve frame transmit or receive data bit buffer */

#undef  TEST_LCD_USING_WEB_PAGE			/* Test LCD UI simulated as a web page */

#undef  DO_TEST_REED_SOLOMON			/*  */

#undef STANDALONE_TEST_CODE				/* Special test code builds */

/* ************************************************************************* */

#endif /* _INCLUDE_TEST_H */
