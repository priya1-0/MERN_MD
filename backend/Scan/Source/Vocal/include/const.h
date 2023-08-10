
#define USE_REDUCED_NOMINAL_V34_POWER_LEVEL_FOR_IMPROVED_PERFORMANCE
#define USE_NEW_SIZE_COMPUTATIONS
#undef  USE_NEW_SIZE_COMPUTATIONS

/* ************************************************************************* */
/*
 *	const.h
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
 *	This file contains miscellaneous constants.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 19:50:34  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _INCLUDE_CONST_H
#define _INCLUDE_CONST_H

/* ************************************************************************* */
/* miscellaneous hook control defines */
/* ************************************************************************* */

#define DAA_ON_HOOK					0x0002
#define DAA_OFF_HOOK				0x0001
#define DAA_TRANSITION_ON_HOOK		0x0020
#define DAA_TRANSITION_OFF_HOOK		0x0010

/* ************************************************************************* */
/* these defines set up the delay values through the sample buffer and codec */
/* ************************************************************************* */

/* Put any additional hardware delay that might be present in the system */
/* here.  This should be in number of samples, at the CODEC rate. For most */
/* systems, this value should be at or near zero. */

#define SAMPLE_CODEC_DELAY              0

/* ********************************** */
/* handle 16 khz rate doubleing first */

#define RATE_CNV_CENTER_16K0			0
#define SAMPLE_BUFFER_DELAY_TEMP        (SAMPLE_BUFFER_SINGLE_CHANNEL_SIZE+SAMPLE_CODEC_DELAY)

/* ********************************** */
/* 7.2 khz rate convert */

#define RATE_CNV_TX_SIZE                0x000B
#define RATE_CNV_RX_SIZE                0x000D
#define RATE_CNV_CENTER_8P0_7P2			0x000C
#define RATE_CNV_CENTER_7P2				(RATE_CNV_CENTER_16K0 + RATE_CNV_CENTER_8P0_7P2)

/* ********************************** */
/* 9.6 khz rate convert */

#define RATE_CNV_CENTER_8P0_9P6			FIXME
#define RATE_CNV_CENTER_9P6				(RATE_CNV_CENTER_16K0 + RATE_CNV_CENTER_8P0_9P6)

/* ********************************** */
/* now handle constants for 8 khz operation */

#define SAMPLE_BUFFER_DELAY_7P2         (SAMPLE_BUFFER_DELAY_TEMP*72/80)
#define SAMPLE_BUFFER_DELAY_8P0         SAMPLE_BUFFER_DELAY_TEMP
#define TIMER_TICK_RATE					80	/* 10 ms at 8 khz */

/* ********************************** */
/* miscellaneous sample buffer size derived constants */

/* the g168 echo canceller runs outside the 7p2 rate interpolator, but */
/* inside the 16k0 rate interpolator.  It is a special case. */
#define SAMPLE_BUFFER_DELAY_G168		SAMPLE_BUFFER_DELAY_TEMP

/* ************************************************************************* */
/* miscellaneous */
/* ************************************************************************* */

/* ************************************************************************* */

#undef DO_V34_INCREASE_TRANSMIT_HEADROOM
#define DO_V34_INCREASE_TRANSMIT_HEADROOM

#undef DO_V34_INCREASE_RECEIVE_HEADROOM
#define DO_V34_INCREASE_RECEIVE_HEADROOM

/* ************************************************************************* */

/* ************************************************************************* */
/* Transmit signal level constants */
/* ************************************************************************* */

#define SERVER_TRANSMIT_LEVEL__V34				UFRACT (16483)	/* -14.0 dBm */
#define SERVER_TRANSMIT_DBM__V34						-14		/* -14.0 dBm */

#ifdef USE_REDUCED_NOMINAL_V34_POWER_LEVEL_FOR_IMPROVED_PERFORMANCE
#define NOMINAL_TRANSMIT_LEVEL__V34				UFRACT (16483)	/* -14.0 dBm */
#define NOMINAL_TRANSMIT_DBM__V34						-14		/* -14.0 dBm */
#else /* USE_REDUCED_NOMINAL_V34_POWER_LEVEL_FOR_IMPROVED_PERFORMANCE */
#define NOMINAL_TRANSMIT_LEVEL__V34				UFRACT (20752)	/* -12.0 dBm */
#define NOMINAL_TRANSMIT_DBM__V34						-12		/* -12.0 dBm */
#endif /* USE_REDUCED_NOMINAL_V34_POWER_LEVEL_FOR_IMPROVED_PERFORMANCE */

#define SERVER_TRANSMIT_LEVEL__OTHER			UFRACT (20579)	/* -14.0 dBm */
#define SERVER_TRANSMIT_DBM__OTHER						-14		/* -14.0 dBm */
#define NOMINAL_TRANSMIT_LEVEL__OTHER			UFRACT (32768)	/* -10.0 dBm */
#define NOMINAL_TRANSMIT_DBM__OTHER						-10		/* -10.0 dBm */

#define  NOMINAL_TRANSMIT_LEVEL__V32			UFRACT (33899)	/* -10.0 dBm */
#define _NOMINAL_TRANSMIT_LEVEL__V32			33899			/* no UFRACT, for use in assembler */

#define NOMINAL_TRANSMIT_LEVEL__V22_ORIG		UFRACT (35216)	/* -10.0 dBm */
#define NOMINAL_TRANSMIT_LEVEL__V22_ANS			UFRACT (36947)	/* -10.0 dBm */

#define NOMINAL_TRANSMIT_LEVEL__V17				UFRACT (33833)	/* -10.0 dBm */
#define NOMINAL_TRANSMIT_LEVEL__V29				UFRACT (36123)	/* -10.0 dBm */
#define NOMINAL_TRANSMIT_LEVEL__V27_4800		UFRACT (35510)	/* -10.0 dBm */
#define NOMINAL_TRANSMIT_LEVEL__V27_2400		UFRACT (34771)	/* -10.0 dBm */

#define NOMINAL_TRANSMIT_LEVEL__FSK				UFRACT (32768)	/* -10.0 dBm */
#define NOMINAL_TRANSMIT_LEVEL__V21_ORIG		FRACT (10840)	/* -10.0 dBm */
#define NOMINAL_TRANSMIT_LEVEL__V21_ANS			FRACT (9975)	/* -10.0 dBm */
#define NOMINAL_TRANSMIT_LEVEL__V23_ORIG		FRACT (10008)	/* -10.0 dBm */
#define NOMINAL_TRANSMIT_LEVEL__V23_ANS			FRACT (8899)	/* -10.0 dBm */
#define NOMINAL_TRANSMIT_LEVEL__B103_ORIG		FRACT (10716)	/* -10.0 dBm */
#define NOMINAL_TRANSMIT_LEVEL__B103_ANS		FRACT (11100)	/* -10.0 dBm */
#define NOMINAL_TRANSMIT_LEVEL__B202_ORIG		FRACT (9600)	/* -10.0 dBm */
#define NOMINAL_TRANSMIT_LEVEL__B202_ANS		FRACT (9168)	/* -10.0 dBm */

/* Direct tone generator */
#define NOMINAL_TONE_LEVEL__DTMF_LOW			UFRACT (7632)	/* -9.5 dBm */
#define NOMINAL_TONE_LEVEL__DTMF_HIGH			UFRACT (9608)	/* -7.5 dBm */
#define NOMINAL_TONE_LEVEL__MF					UFRACT (10176)	/* -7.0 dBm */
#define NOMINAL_TONE_LEVEL__0dBm				UFRACT (22784)	/*  0.0 dBm */

#define NOMINAL_TONE_LEVEL__V25_ANSWER			UFRACT (5540)	/* -14.5 dBm */
#define NOMINAL_TONE_LEVEL__V25_CALLING			UFRACT (5217)	/* -14.5 dBm */
#define NOMINAL_TONE_LEVEL__FAX_CALLING			UFRACT (5481)	/* -14.5 dBm */
#define _NOMINAL_TONE_LEVEL__FAX_CALLING		5481			/* -14.5 dBm */

#define NOMINAL_TONE_LEVEL__V8_ANSWER			 FRACT (5241)	/* -10.9 dBm including 4 dB difference in nominal transmit level */

#define NOMINAL_TONE_LEVEL__V8_CNG				UFRACT (6904)	/* -14.5 dBm */
#define NOMINAL_TONE_LEVEL__V8BIS				UFRACT (8758)	/* -10.0 dBm */
/*#define INITIAL_TONE_LEVEL__V8BIS				UFRACT (1237)*/	/* -27.0 dBm */
#define INITIAL_TONE_LEVEL__V8BIS				UFRACT (1961)	/* -23.0 dBm */

/* ************************************************************************* */

#define FAX_CARRIER_DROPOUT_TIME					 6500		/* 6.5 seconds */

#define MAP_ZERO_INDEX                             0xFC00

#define LINE_TX_BUFFER_SIZE                        0x0064
#define LINE_RX_BUFFER_SIZE                        0x0064

#define  PI_OVER_128                               FRACT (0x0324)
#define _PI_OVER_128                               0x0324

/* ************************************************************************* */
/* fsk modulation constants */
/* ************************************************************************* */

#define FSK_OVERSAMPLE_RATE                     18

#define C7K2_FSK_TX_INTERPOLATOR_SIZE              0x0000 + (0x0005 * 0x0002)	/* only 2*2 needed */
#define C7K2_FSK_RX_INTERPOLATOR_SIZE              0x0000 + (0x0008 * 0x0002)	/* only 11  needed */

#define C7K2_FSK_REDUCE_LPF_SIZE                   0x0014
#define C7K2_FSK_RX_LPF_SIZE                       0x0034

#define C7K2_FSK_TONE_ON_TIME                      0x0E10	/* 0.5s*7200 CNG tone */
#define C7K2_FSK_TONE_OFF_TIME                     0x5460	/* 3.0s*7200 CNG tone */

#define C7K2_FSK_TX_BPF_SIZE                       0x001E
#define C7K2_TX_BPF_SIZE                           0x001E
#define C7K2_HALF_RX_LPF_SIZE                      0x001A

/* ************************************************************************* */
/* synchronous modulation constants */
/* ************************************************************************* */

#define C7K2_TX_INTERPOLATOR_SIZE                  5
#define C7K2_RX_INTERPOLATOR_SIZE                  8
#define MAX_C7K2_INTERPOLATOR_SIZE                 8

#define C7P2_BAUD_TIMING_PHASE                     0x0038

#define EQUALIZER_RANDOM_AMPLITUDE                 FRACT (0x0003)
#define EQUALIZER_SHIFT                            0x0003

#define C7K2_RX_EQUALIZER_SIZE                     0x0020	/* max v.22 and v.32 sizes */
#define C7K2_RX_SEQUENCE_DETECTOR_SIZE             0x0018	/* fixed, product of 8 and 3 */
#define C7K2_RX_LPF_SIZE                           0x0002 * C7K2_HALF_RX_LPF_SIZE
#define C7K2_V22_EQUALIZER_CENTER_TAP              0x0008
#define C7K2_V22_EQUALIZER_SIZE                    0x0010
#define C7K2_V32_EQUALIZER_SIZE                    0x0020
#define V32_CENTER_TAP_DELAY                       0x001C	/* 12+V32_EQUALIZER_LENGTH/2 */

#define COS1200                                    FRACT (0xC1B1)	/* (1-.0264587402344) * cos (1200/3600*360) */
#define SIN1200                                    FRACT (0x6BEB)	/* (1-.0264587402344) * sin (1200/3600*360) */
#define SLEW1200                                   FRACT (0x0363)	/* .0264587402344 */

#define COS2400                                    FRACT (0xC35B)	/* (1-.0524597167969) * cos (2400/3600*360) */
#define SIN2400                                    FRACT (0x96F6)	/* (1-.0524597167969) * sin (2400/3600*360) */
#define SLEW2400                                   FRACT (0x06B7)	/* .0524597167969 */

#define EC_UPDATE_RATE                             0x000C
#define EC_UPDATE_INCREMENT                        0x0004

/* ************************************************************************* */
/* V32 constants */
/* ************************************************************************* */

#define V32_REMOTE_TAPS                            0x00A8
#define V32_LOCAL_TAPS                             0x0084

#define V32_TOTAL_TAPS                             (V32_REMOTE_TAPS + V32_LOCAL_TAPS)

/* this delay was intended to encompass the v32 output and rate interp */
/* filters.  We really should not delay to the center of the filter, */
/* because it has a response that starts with tap 0. */
#define V32_OUTPUT_FILTER_DELAY                    0
#define V32_LOCAL_DELAY                            (SAMPLE_BUFFER_DELAY_7P2)
#define V32_LOCAL_ECHO_POSITION                    (V32_LOCAL_DELAY+V32_OUTPUT_FILTER_DELAY)

#define V32_ECHO_BUFFER_SIZE                       ((EC_UPDATE_RATE - 1) + V32_REMOTE_TAPS + (EC_UPDATE_RATE - 1) + V32_LOCAL_TAPS + V32_LOCAL_ECHO_POSITION)

/* place the remote echo response in the middle of the remote canceller */
#define V32_REMOTE_ECHO_POSITION                   (V32_REMOTE_TAPS / 2)

/* these timing constants are used to hold off bulk delay for a minimum amount of time */
/* we divide by 3 because v32 symbol rate is 2400, and 7200/2400 = 3 */
#define V32_LOCAL_ECHO_BAUDS                       (V32_TOTAL_TAPS / 3)
#define V32_REMOTE_ECHO_BAUDS                      (V32_REMOTE_TAPS / 3)

#define V32_BULK_HOLDOFF_TIME                      0x0012

/* partitioned v32 ec stuff.  Unused, kept for reference only */

/* ************************************************************************* */

#define LOOKBACK_DEPTH                             0x0010
#define LOOKBACK_BUFFER_SIZE                       (LOOKBACK_DEPTH * 0x0012)

#define HILBERT_TAP_2_8                            FRACT (0x1B2A)
#define HILBERT_TAP_4_6                            FRACT (0x517D)
#define PHASE_ROLL_AGC_DECAY                       FRACT (0x0100)

/*
 *	Other various equates.
 */
#define V22_PROPAGATION_DELAY                      0x02D0 + 0x012C

#define AC_SEQ_DETECT_DELAY                        0x000A
#define AA_SEQ_DETECT_DELAY                        0x0008

#define ORIG_TURNAROUND_DELAY                      (0x0011 + AC_SEQ_DETECT_DELAY + 0x0014)
#define ANS_TURNAROUND_DELAY                       (0x0011 + AA_SEQ_DETECT_DELAY + 0x0014)
/*
 *	Echo canceller sample based equates.
 *	Echo canceller baud based equates.
 */

#define DO_BULK_1500                               /* Selects 1.5 sec or .8 sec */

#ifdef DO_BULK_1500
#define MAX_BULK_DELAY                             0x0E02
#define BULK_DELAY_BUFFER_SIZEOF                   0x0F00
#else /* DO_BULK_1500 */
#define MAX_BULK_DELAY                             0x077F
#define BULK_DELAY_BUFFER_SIZEOF                   0x0800
#endif /* DO_BULK_1500 */

#define SART_TX_BUFFER_SIZE                        0x0064
#define SART_RX_BUFFER_SIZE                        0x0064

#define BULK_EXTRA_BUFFER_SIZE                     16

#define	P18_2100_NOTCH_SIZE							20

/* ************************************************************************* */
/* various v34 delay settings */
/* ************************************************************************* */

#define xV34_XX_LOCAL_DELAY                        (SAMPLE_BUFFER_DELAY_8P0)
#define xV34_XX_OUTPUT_FILTER_PRE_RESPONSE         17	 /* C8K0_C34_TX_BPF_SIZE/2 */

/****************************************/
/* line delays due to filter responses  */
/****************************************/

#define xV34_XX_OUTPUT_LINE_PRE_RESPONSE	(31)	 /* codec and rate changes */

/* ************************************************************************* */
/* v34 echo canceller, output filter, and equalizer defines */
/* ************************************************************************* */

/* tap counts for local and remote cancellers */
#define xV34_XX_REMOTE_TAPS                        180
#define xV34_XX_LOCAL_TAPS                         140
#define xV34_XX_TOTAL_TAPS                         (xV34_XX_REMOTE_TAPS) + (xV34_XX_LOCAL_TAPS)

/* tap and echo offsets for cancellers */
#define xV34_XX_ECHO_BUFFER_SIZE                   (2*((EC_UPDATE_RATE-1)+xV34_XX_REMOTE_TAPS+(EC_UPDATE_RATE-1)+xV34_XX_LOCAL_TAPS+xV34_XX_LOCAL_DELAY))
#define xV34_XX_REMOTE_ECHO_POSITION               60
#define xV34_XX_LOCAL_ECHO_POSITION                (xV34_XX_OUTPUT_FILTER_PRE_RESPONSE + xV34_XX_OUTPUT_LINE_PRE_RESPONSE)

/* these defines are for setup of the improved echo canceller option */
#define V34S_SPECIAL_CT_POSITION                 235     /* empirical, xV34_XX_REMOTE_TAPS+55 */
#define V34S_SPECIAL_CT_PRELENGTH                8
#define V34S_SPECIAL_CT_PSTLENGTH                24
#define V34S_SPECIAL_TRAIN_LENGTH                V34S_SPECIAL_CT_PRELENGTH+V34S_SPECIAL_CT_PSTLENGTH
#define V34S_SPECIAL_TRAIN_OFFSET                V34S_SPECIAL_CT_POSITION -V34S_SPECIAL_CT_PSTLENGTH-xV34_XX_REMOTE_TAPS
#define V34S_SPECIAL_TRAIN_SLEW                  -1         /* 0 -2 -3 */

#define xC8K0_V34_XX_HALF_RX_LPF_SIZE              34
#define xC8K0_V34_XX_HALF_TX_BPF_SIZE              17			/* fixed */

#define xC8K0_V34_XX_TX_BPF_SIZE                   33
#define xC8K0_V34_XX_TX_BPF_CENTER_TAP             17

#define xV34_XX_EQUALIZER_SIZE                     196	/* EQUALIZER_TAPS*2+4 */
#define xV34_XX_EQUALIZER_TAPS                     96	/* EQUALIZER_LENGTH * 2 */
#define xV34_XX_EQUALIZER_HALF_TAPS                48	/* EQUALIZER_HALF_LENGTH*2 */
#define xV34_XX_EQUALIZER_LENGTH                   48	/* EQUALIZER_HALF_LENGTH*2 */
#define xV34_XX_EQUALIZER_HALF_LENGTH              24	/* fse */
#define xV34_XX_CENTER_TAP_DELAY                   34	/* 12+EQUALIZER_TAPS/2-2 */

/* ************************************************************************* */
/* ph2 symbol adjust constants */
/* ************************************************************************* */

#define PH2_LEN_SYMBOL_ADJUST                      19

#define PH2_LEN_SAMPLE_ADJUST                      13

#ifdef USE_NEW_SIZE_COMPUTATIONS

#undef  PH2_LEN_SYMBOL_ADJUST
#undef  PH2_LEN_SAMPLE_ADJUST

#define V34_LEN_SAMPLES_8K0						(xV34_XX_LOCAL_DELAY + xV34_XX_LOCAL_ECHO_POSITION)
#define V34_LEN_SAMPLES_9K6						((V34_LEN_SAMPLES_8K0 * 9.6)/8)
#define PH2_LEN_BASE_OFFSET						150.2
#define PH2_LEN_SAMPLES_9K6						(PH2_LEN_BASE_OFFSET + V34_LEN_SAMPLES_9K6)

#define PH2_LEN_SYMBOL_ADJUST					((int) ((PH2_LEN_SAMPLES_9K6 + 15) /16))
#define PH2_LEN_SAMPLE_ADJUST					((int) (PH2_LEN_SYMBOL_ADJUST * 16 - PH2_LEN_SAMPLES_9K6 + 0.5))

#endif /* USE_NEW_SIZE_COMPUTATIONS */

/* ************************************************************************* */
/* v34 interpolator defines */
/* ************************************************************************* */

#define DO_LARGE_INTERPOLATORS

#ifdef DO_LARGE_INTERPOLATORS
/* tx interpolators */
#define xC8K0_V34_24_TX_INTERPOLATOR_SIZE          0x0020	/* xV34_24_TXI_TAPS*2 */
#define xC8K0_V34_27_TX_INTERPOLATOR_SIZE          0x0020	/* xV34_27_TXI_TAPS*2 */
#define xC8K0_V34_28_TX_INTERPOLATOR_SIZE          0x0020	/* xV34_28_TXI_TAPS*2 */
#define xC8K0_V34_30_TX_INTERPOLATOR_SIZE          0x0020	/* xV34_30_TXI_TAPS*2 */
#define xC8K0_V34_32_TX_INTERPOLATOR_SIZE          0x0020	/* xV34_32_TXI_TAPS*2 */
#define xC8K0_V34_34_TX_INTERPOLATOR_SIZE          0x0020	/* xV34_34_TXI_TAPS*2 */
#define xC8K0_V34_XX_TX_INTERPOLATOR_SIZE          0x0020	/* max of above */

#define xV34_24_TXI_TAPS                           16
#define xV34_27_TXI_TAPS                           16
#define xV34_28_TXI_TAPS                           16
#define xV34_30_TXI_TAPS                           16
#define xV34_32_TXI_TAPS                           16
#define xV34_34_TXI_TAPS                           16
#define xV34_XX_TXI_TAPS                           16

/* rx interpolators */
#define xC8K0_V34_24_RX_INTERPOLATOR_SIZE          56		/* xV34_24_RXI_TAPS*2+2 */
#define xC8K0_V34_27_RX_INTERPOLATOR_SIZE          48		/* xV34_27_RXI_TAPS*2+2 */
#define xC8K0_V34_28_RX_INTERPOLATOR_SIZE          48		/* xV34_28_RXI_TAPS*2+2 */
#define xC8K0_V34_30_RX_INTERPOLATOR_SIZE          44		/* xV34_30_RXI_TAPS*2+2 */
#define xC8K0_V34_32_RX_INTERPOLATOR_SIZE          42		/* xV34_32_RXI_TAPS*2+2 */
#define xC8K0_V34_34_RX_INTERPOLATOR_SIZE          40		/* xV34_34_RXI_TAPS*2+2 */
#define xC8K0_V34_XX_RX_INTERPOLATOR_SIZE          56		/* max of above */
#define xC8K0_V34_XX_HALF_RX_INTERPOLATOR_SIZE     (xC8K0_V34_XX_RX_INTERPOLATOR_SIZE / 2)

#define xV34_24_RXI_TAPS                           27
#define xV34_27_RXI_TAPS                           23
#define xV34_28_RXI_TAPS                           23
#define xV34_30_RXI_TAPS                           21
#define xV34_32_RXI_TAPS                           20
#define xV34_34_RXI_TAPS                           19
#define xV34_XX_RXI_TAPS                           27

/* interpolator coefficient generators */
#define xC8K0_V34_24_INTERPOLATOR_COEFS_SIZE       325
#define xC8K0_V34_27_INTERPOLATOR_COEFS_SIZE       561
#define xC8K0_V34_28_INTERPOLATOR_COEFS_SIZE       323
#define xC8K0_V34_30_INTERPOLATOR_COEFS_SIZE       385
#define xC8K0_V34_32_INTERPOLATOR_COEFS_SIZE       401
#define xC8K0_V34_34_INTERPOLATOR_COEFS_SIZE       457
#define xC8K0_V34_XX_INTERPOLATOR_COEFS_SIZE       561

#define xC8K0_V34_24_HALF_INTERPOLATOR_COEFS_SIZE  163
#define xC8K0_V34_27_HALF_INTERPOLATOR_COEFS_SIZE  281
#define xC8K0_V34_28_HALF_INTERPOLATOR_COEFS_SIZE  162
#define xC8K0_V34_30_HALF_INTERPOLATOR_COEFS_SIZE  193
#define xC8K0_V34_32_HALF_INTERPOLATOR_COEFS_SIZE  201
#define xC8K0_V34_34_HALF_INTERPOLATOR_COEFS_SIZE  229

#else /* DO_LARGE_INTERPOLATORS */
#error Only large interpolators can currently be used
#define xC8K0_V34_24_TX_INTERPOLATOR_SIZE          0x001A	/* xV34_24_TXI_TAPS*2 */
#define xC8K0_V34_27_TX_INTERPOLATOR_SIZE          0x001A	/* xV34_27_TXI_TAPS*2 */
#define xC8K0_V34_28_TX_INTERPOLATOR_SIZE          0x001A	/* xV34_28_TXI_TAPS*2 */
#define xC8K0_V34_30_TX_INTERPOLATOR_SIZE          0x001A	/* xV34_30_TXI_TAPS*2 */
#define xC8K0_V34_32_TX_INTERPOLATOR_SIZE          0x001A	/* xV34_32_TXI_TAPS*2 */
#define xC8K0_V34_34_TX_INTERPOLATOR_SIZE          0x001A	/* xV34_34_TXI_TAPS*2 */
#define xC8K0_V34_XX_TX_INTERPOLATOR_SIZE          0x001A	/* max of above */
#endif /* DO_LARGE_INTERPOLATORS */

/* tx interpolator */
#define xV34_24_TXI_PLL_COUNT                      PLL_COUNT_2400_BAUD_8000_SAMPLE
#define xV34_27_TXI_PLL_COUNT                      PLL_COUNT_2743_BAUD_8000_SAMPLE
#define xV34_28_TXI_PLL_COUNT                      PLL_COUNT_2800_BAUD_8000_SAMPLE
#define xV34_30_TXI_PLL_COUNT                      PLL_COUNT_3000_BAUD_8000_SAMPLE
#define xV34_32_TXI_PLL_COUNT                      PLL_COUNT_3200_BAUD_8000_SAMPLE
#define xV34_34_TXI_PLL_COUNT                      PLL_COUNT_3429_BAUD_8000_SAMPLE

#define xV34_24_TXI_ADJUST                         UFRACT (16644)
#define xV34_27_TXI_ADJUST                         UFRACT (29127)
#define xV34_28_TXI_ADJUST                         UFRACT (16644)
#define xV34_30_TXI_ADJUST                         UFRACT (19973)
#define xV34_32_TXI_ADJUST                         UFRACT (20805)
#define xV34_34_TXI_ADJUST                         UFRACT (23302)

#define xV34_24_TXI_COUNT                          20
#define xV34_27_TXI_COUNT                          35
#define xV34_28_TXI_COUNT                          20
#define xV34_30_TXI_COUNT                          24
#define xV34_32_TXI_COUNT                          25
#define xV34_34_TXI_COUNT                          28

#define xV34_XX_TXI_SHIFT                          -9

/* rx interpolator */
#define xV34_24_RXI_PLL_COUNT                      PLL_COUNT_2400_BAUD_8000_SAMPLE
#define xV34_27_RXI_PLL_COUNT                      PLL_COUNT_2743_BAUD_8000_SAMPLE
#define xV34_28_RXI_PLL_COUNT                      PLL_COUNT_2800_BAUD_8000_SAMPLE
#define xV34_30_RXI_PLL_COUNT                      PLL_COUNT_3000_BAUD_8000_SAMPLE
#define xV34_32_RXI_PLL_COUNT                      PLL_COUNT_3200_BAUD_8000_SAMPLE
#define xV34_34_RXI_PLL_COUNT                      PLL_COUNT_3429_BAUD_8000_SAMPLE

#define xV34_24_RXI_ADJUST                         UFRACT (16644)
#define xV34_27_RXI_ADJUST                         UFRACT (29127)
#define xV34_28_RXI_ADJUST                         UFRACT (16644)
#define xV34_30_RXI_ADJUST                         UFRACT (19973)
#define xV34_32_RXI_ADJUST                         UFRACT (20805)
#define xV34_34_RXI_ADJUST                         UFRACT (23302)

#define xV34_24_RXI_COUNT                          12
#define xV34_27_RXI_COUNT                          24
#define xV34_28_RXI_COUNT                          14
#define xV34_30_RXI_COUNT                          18
#define xV34_32_RXI_COUNT                          20
#define xV34_34_RXI_COUNT                          24

#define xV34_XX_RXI_SHIFT                          -9

/* ************************************************************************* */
/* various symbol rate dependent defines */
/* ************************************************************************* */

#define xV34_24_HI_CARRIER                         14746
#define xV34_27_HI_CARRIER                         14980
#define xV34_28_HI_CARRIER                         15292
#define xV34_30_HI_CARRIER                         16384
#define xV34_32_HI_CARRIER                         15729
#define xV34_34_HI_CARRIER                         16050

#define xV34_24_LO_CARRIER                         13107
#define xV34_27_LO_CARRIER                         13482
#define xV34_28_LO_CARRIER                         13763
#define xV34_30_LO_CARRIER                         14746
#define xV34_32_LO_CARRIER                         14980
#define xV34_34_LO_CARRIER                         16050

#define xV34_24_MD_LENGTH_INCREMENT                84		/* multiples of 35ms in bauds */
#define xV34_27_MD_LENGTH_INCREMENT                96		/* multiples of 35ms in bauds */
#define xV34_28_MD_LENGTH_INCREMENT                98		/* multiples of 35ms in bauds */
#define xV34_30_MD_LENGTH_INCREMENT                105		/* multiples of 35ms in bauds */
#define xV34_32_MD_LENGTH_INCREMENT                112		/* multiples of 35ms in bauds */
#define xV34_34_MD_LENGTH_INCREMENT                120		/* multiples of 35ms in bauds */

#define xV34_24_T_OVER_8K0_RATIO                   UFRACT (9830)	/* 3/10 */
#define xV34_27_T_OVER_8K0_RATIO                   UFRACT (11235)	/* 12/35 */
#define xV34_28_T_OVER_8K0_RATIO                   UFRACT (11467)	/* 7/20 */
#define xV34_30_T_OVER_8K0_RATIO                   UFRACT (12288)	/* 3/8 */
#define xV34_32_T_OVER_8K0_RATIO                   UFRACT (13107)	/* 2/5 */
#define xV34_34_T_OVER_8K0_RATIO                   UFRACT (14043)	/* 3/7 */

/* ************************************************************************* */
	/*
	 *	AGC_1_TARGET:			.165359456942 =~ 20*log(.165359456942)	-15.631419253
	 *	AGC_2_TARGET:			.165359456942 =~ 20*log(.165359456942)	-15.631419253
	 *	EQUALIZER_ENERGY_TARGET	.3125/2		  =~ 10*log(.3125/2)	     -8.06179973984
	 *
	 X	AGC_1_TARGET:			.082679728471 =~ 20*log(.082679728471)	-21.6520191662
	 X
	 -	AGC_1_TARGET:			.116926793337 =~ 20*log(.116926793337)	-18.6417192096
	 -	AGC_2_TARGET:			.116926793337 =~ 20*log(.116926793337)	-18.6417192096
	 -	EQUALIZER_ENERGY_TARGET	.3125/8		  =~ 10*log(.3125/8)	    -14.0823996531
	 *
	 *	calculation of value AGC2 uses to achieve target
	 *
	 *	exponent = int (log2 (AGC_2_TARGET ^2))
	 *			 = int (log2 (.165359456942^2))
	 *			 = int (log2 (.0273437500001))
	 *			 = int (-5.19264507794)
	 *			 = -5
	 *
	 -	exponent = int(log(.116926793337^2)/log(2))
	 -			 = -6
	 *
	 *
	 *	mantissa = AGC_2_TARGET^2 / 2^exponent
	 *		     = .165359456942^2 / 2^-5
	 *			 = .875000000005
	 *
	 -	mantissa = .116926793337^2 / 2^-6
	 -			 = .875000000004
	 *
	 *	value	 = - ((exponent * 2^10) + ((mantissa-.5) * 32768 * 2^-4))
	 *			 = - ((-5       * 2^10) + ((.875    -.5) * 32768 * 2^-4))
	 *			 = 4352
	 *			 = 0x1100
	 *
	 -	value	 = - ((-6       * 2^10) + ((.875    -.5) * 32768 * 2^-4))
	 -			 = 5376
	 -			 = 0x1500
	 *
	 *	linear			   1  * .165359456942 * 32768 =	5418.49868508
	 *	linear-3dB	sqrt(1/2) * .165359456942 * 32768 =	3831.45716407
	 *	-3dB		sqrt(1/2)                 * 32768 =	23170.4750059
	 *
	 -	linear			   1  * .116926793337 * 32768 =	3831.45716407
	 -	linear-3dB	sqrt(1/2) * .116926793337 * 32768 =	2709.24934254
	 -	-3dB		sqrt(1/2)                 * 32768 =	23170.4750059
	 *
	 *	log2 AGC 2 target = log2 (AGC_2_TARGET ^2) * 1024
	 *					  = log2 (.165359456942^2) * 1024
	 *					  = log2 (.0273437500001)  * 1024
	 *					  = -5317.26855981
	 *					  = -5317
	 *
	 -	log2 AGC 2 target = log(.116926793337^2)/log(2) * 1024
	 -					  = -6341.26855981
	 *
	 *	log2 AGC 1 target = log2 AGC 2 target (for now)
	 *
	 *
	 *	converion from equalizer input to equalizer output
	 *
	 *	equalizer gain	 = sqrt (equalizer energy        / AGC2 energy)
	 *					 = sqrt (EQUALIZER_ENERGY_TARGET / AGC_2_TARGET ^2)
	 *					 = sqrt(.3125/2                 / .165359456942^2)
	 *					 = sqrt (.3125/2                 / .165359456942^2)
	 *					 = 2.39045721866
	 *
	 *	equalizer gain/2 = 2.39045721866/2
	 *					 = 2.39045721867/2
	 *					 = 1.19522860934
	 *
	 *					 = 1.19522860934 * 32768
	 *					 = 39165.2510709
	 *					 = 39165*sqrt(2)
	 *
	 -	equalizer gain/2 = sqrt(.3125/8                 / .116926793337^2)/2
	 -					 = .845154254726 * 32768
	 -					 = 27694.0146189
	 *
	 *	The AB detector operate post AGC2 and is referenced to the
	 *	AGC_2 target energy:
	 *
	 *	MIN energy = X dB less than AGC_2_TARGET^2
	 *
	 *		with X = 4.5 dB
	 *
	 *			   = 10^(-4.5/10) * .165359456942^2 * 32768
	 *			   = 317.912796755
	 *			   = 318
	 *
	 -			   = 10^(-4.5/10) * .116926793337^2 * 32768
	 -			   = 158.956398377
	 *
	 *	The S detector operate post equalizer and is referenced to the
	 *	EQUALIZER target energy:
	 *
	 *	MIN S energy = 0.5 * EQUALIZER_ENERGY_TARGET * 32768
	 *				 = 0.5 * .3125/2                 * 32768
	 *				 = 2560
	 *
	 *	MAX S energy = 1.5 * EQUALIZER_ENERGY_TARGET * 32768
	 *				 = 1.5 * .3125/2                 * 32768
	 *				 = 7680
	 *
	 -	MIN S energy = 0.5 * .3125/8                 * 32768
	 -				 = 640
	 -
	 -	MAX S energy = 1.5 * .3125/8                 * 32768
	 -				 = 1920
	 *
	 *	The 16 point decision's midpoint is referenced to the
	 *	16 point gain and the receiver gain shift.  The midpoint
	 *	is determined by:
	 *
	 *	MIDPOINT = 2 (9.7) * 16 point gain * 2^V34_RX_INVG_SHIFT
	 *			 = 2 * 128 * 0x4000        * 2^6
	 *			 = 2 * 128 * .5            * 2^6
	 *			 = 8192
	 *
	 -	MIDPOINT = 2 * 128 * .5            * 2^5
	 -			 = 4096
	 *
	 *	The null real value when the trellis decoder cannot make decisions
	 *	is the magnitude of the EQUALIZER target energy
	 *
	 *	NULL_VALUE = sqrt (EQUALIZER_ENERGY_TARGET) * 32768
	 *			   = sqrt (.3125/2) * 32768
	 *			   = 12952.6892961
	 *			   = 12953
	 *
	 -	NULL_VALUE = sqrt (.3125/8) * 32768
	 -			   = 6476.34464802
	 *
	 *	inexplicably, this value is calculated as:
	 *
	 *			   = EQUALIZER_ENERGY_TARGET * 32768
	 *			   = .3125/2                 * 32768
	 *			   = 5120
	 *
	 *	The energy correction from S/N at the trellis decoder to S/N at the
	 *	gain table's target energy which is the .3125/2.  In the correction
	 *	for the MSE values, the following calculation is used:
	 *
	 *	log gain table energy target = log2 (.3125/2) *1024
	 *								 = -2742
	 *
	 -	log gain table energy target = log(.3125/8)/log(2) *1024
	 -								 = -4790.34563084
	 -								 = -2742-2048
	 -
	 *	This value does not change for different energy equalizer energy.
	 */

/* ************************************************************************* */
/* miscellaneous defines */
/* ************************************************************************* */

#define MAX_VXX_TX_INTERPOLATOR_SIZE               xC8K0_V34_XX_TX_INTERPOLATOR_SIZE

/* ************************************************************************* */
/* miscellaneous mostly v34 defines */
/* ************************************************************************* */

#define PHASE_ROLL_HILBERT_BUFFER_SIZE             12
#define RX_LPF_BUFFER_SIZE                         C7K2_HALF_RX_LPF_SIZE*4

#define V34_FS_TIME                                400
#define V34_FL_TIME                                4800

#define MAP_ZERO_INDEX                             0xFC00

/* ************************************************************************* */

#define V34_THRESHOLD_S1                           FRACT (60095)	/* -55 dBm */
#define V34_THRESHOLD_S2_LO                        FRACT (63063)	/* -20 dBm */
#define V34_THRESHOLD_S2_HI                        FRACT (63503)	/* -15 dBm */
#define V34_THRESHOLD_SF                           FRACT (63063)	/* -20 dBm */

#ifdef	DO_V34_INCREASE_RECEIVE_HEADROOM

#define MSE_TABLE_ENTRY_ADJUST                     FRACT (-2048)
#define LOG_GAIN_TABLE_ENERGY_TARGET               FRACT (-4790)

#define PHASE_ERROR_SCALE                          4	/* shift */
#define EC_OUTPUT_SCALE                            1	/* x2 	0  x0 */
#define EC_SLEW_SCALE                              1	/* x2 	2  x4 */
#define EQ_SLEW_SCALE                              1	/* x2 */
#define PC_SLEW_SCALE                              2	/* x4 */
#define FB_SLEW_SCALE                              2	/* x4 */

#else /* DO_V34_INCREASE_RECEIVE_HEADROOM */
#error NOT AVAILABLE
#endif /* DO_V34_INCREASE_RECEIVE_HEADROOM */

/* ************************************************************************* */

#define V34_TX_GAIN_4PT                            UFRACT (36636)	/* 1.1180419*32768	36635.9969792 */
#define V34_TX_GAIN_16PT                           UFRACT (16384)	/* 0.5000000*32768	16384 */
#define V34_TX_GAIN_PP                             UFRACT (512)	/* 1.00/64 * 32768	512 */
#define V34_TX_GAIN_P                              UFRACT (512)	/* 1.00/64 * 32768	512 */

#ifdef	DO_V34_INCREASE_TRANSMIT_HEADROOM
#define V34_TX_GAIN_SHIFT                          5		/* x << V34_TX_GAIN_SHIFT */
#define V34_TX_DOUBLE_OUTPUT                       1
#else /* DO_V34_INCREASE_TRANSMIT_HEADROOM */
#error NOT AVAILABLE
#endif /* DO_V34_INCREASE_TRANSMIT_HEADROOM */

#define V34_RX_GAIN_4PT                            UFRACT (36636)	/* 1.1180419*32768	36635.9969792 */
#define V34_RX_GAIN_16PT                           UFRACT (16384)	/* 0.5000000*32768	16384 */
#define V34_RX_GAIN_PP                             UFRACT (512)	/* 1.00/64 * 32768	512 */

#define V34_RX_DISP_LIMIT                          LFRACT (0x01E0)	/* 0x7800 >> V34_RX_DISP_SHIFT */
#define V34_RX_DISP_SHIFT                          6		/* x << V34_RX_DISP_SHIFT */

#ifdef	DO_V34_INCREASE_RECEIVE_HEADROOM

#define V34_RX_INVG_SHIFT                          5		/* x << V34_RX_INVG_SHIFT */
#define V34_RX_GAIN_SHIFT                          1		/* x >> V34_RX_GAIN_SHIFT */

#else /* DO_V34_INCREASE_RECEIVE_HEADROOM */
#error NOT AVAILABLE
#endif /* DO_V34_INCREASE_RECEIVE_HEADROOM */

/* ************************************************************************* */

#ifdef	DO_V34_INCREASE_RECEIVE_HEADROOM
#define V34_SYMBOL_MIDPOINT                        FRACT (4096)
#define V34_NULL_SYMBOL_VALUE                      FRACT (6476)
#define LINEAR_S_MIN_ENERGY                        FRACT (640)
#define LINEAR_S_MAX_ENERGY                        FRACT (1920)
#define LINEAR_AB_MIN_ENERGY                       FRACT (159)
#define SPECIAL_AGC_2_TARGET                       FRACT (0x1500)
#define LOG_AGC_2_ENERGY_TARGET                    FRACT (-6341)
#define LOG_AGC_1_ENERGY_TARGET                    FRACT (-6341)
#define RATIO_EQUALIZER_OVER_AGC_2_DIVIDE2         UFRACT (27694)
#define V34_LINEAR_AGC_2_TARGET                    FRACT (3831)
#define V34_LINEAR_AGC_2_TARGET_MINUS_3DB          FRACT (2709)
#define V34_LINEAR_MINUS_3DB                       FRACT (23170)
#define V34_LINEAR_MINUS_NEAR_3DB                  FRACT (23170)
#else /* DO_V34_INCREASE_RECEIVE_HEADROOM */
#error NOT AVAILABLE
#endif /* DO_V34_INCREASE_RECEIVE_HEADROOM */

/* ************************************************************************* */

#ifdef	DO_V34_INCREASE_TRANSMIT_HEADROOM

#define V34_NL_C0                                  UFRACT (30314)	/*	32768		  *	.925124816895 * 1	30314.49      */
#define V34_NL_C1                                  UFRACT (40419)	/*	10922.666667  *	.925124816895 * 4	40419.3200013 */
#define V34_NL_C2                                  UFRACT (16168)	/*	 1092.2666667 * .925124816895 * 16	16167.7280005 */

#else /* DO_V34_INCREASE_TRANSMIT_HEADROOM */
#error NOT AVAILABLE
#endif /* DO_V34_INCREASE_TRANSMIT_HEADROOM */

#define V34_PP_TABLE_SIZE                          (48*2)

#define V34_MAP_ZERO_INDEX                         0xFFFF	/* y(n) = 0,0 */
#define V34_LOOKBACK_DEPTH                         21

#define V34_BIT_INVERSION_PATTERN                  0x77fa
#define V34_NO_QN_COEFS                            3

#define V34_DECOR_TAPS                             15

/* ************************************************************************* */
#endif /* _INCLUDE_CONST_H */
