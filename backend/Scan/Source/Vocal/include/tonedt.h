
/* ************************************************************************* */
/*
 *	tonedt.h
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
 *	Module:		LIBAUTO
 *
 *	This file contains the tone detect symbol definitions.
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

#ifndef _INCLUDE_TONEDT_H
#define _INCLUDE_TONEDT_H

/* ************************************************************************* */
/*
 *	Define tone detector constants
 *
 */
#define NUMBER_MAX_TONE_DETECTORS					16		/* Maximum of 16 */
#define NUMBER_S1_DETECTORS							5		/* Maximum of 5 */
#define NUMBER_DT_DETECTORS							6		/* Maximum of 6 */

#define NUMBER_ORIG_DETECTORS						8		/* Maximum of NUMBER_MAX_TONE_DETECTORS */
#define NUMBER_ANSW_DETECTORS						7		/* Maximum of NUMBER_MAX_TONE_DETECTORS */
#define NUMBER_V8BIS_DETECTORS						7		/* Maximum of NUMBER_MAX_TONE_DETECTORS */
#define NUMBER_CP_DETECTORS							10		/* Maximum of NUMBER_MAX_TONE_DETECTORS */
#define NUMBER_AD_DETECTORS							7		/* Maximum of NUMBER_MAX_TONE_DETECTORS */
#define NUMBER_GENERAL_DETECTORS					7		/* Maximum of NUMBER_MAX_TONE_DETECTORS */

#define SLEW_RATE_DT_DETECTORS						0x0200	/* Special slew rate for DT detectors */
#define SLEW_RATE_S1_DETECTORS						0x0355	/* Special slew rate for S1 detectors */
#define SLEW_RATE_DETECTORS							0x0355	/* Standard slew rate */

/* ************************************************************************* */

/* TONE_DETECTOR_DATA */
/* single precision: */
#define TONE_DETECTOR_LENGTH						NUMBER_MAX_TONE_DETECTORS

#define	S1_DETECTOR_LENGTH							(1+15*NUMBER_S1_DETECTORS)

#define TONE_DETECTOR_DECIMATE						20

/* ************************************************************************* */
/*
 *	Define automode timer constants
 *
 */
#define NUMBER_AUTOMODE_TIMERS						0x0007	/* Maximum of 8 */

/* ************************************************************************* */
/*
 *	Define tone detect masks
 *
 */
#define TONEDT__ANSWER_2100							0x0010	/* Special tone used by call progress */
#define TONEDT__V32_3000							0x0040	/* Special tone used by call progress */

/* ************************************************************************* */
/*
 *	Bit masks in the tone_detector_flags produced by the originate
 *	tone detector
 */
#define TONEDT_ORIG__V23_1300						0x0001				/* V.23 */
#define TONEDT_ORIG__V21_1650						0x0002				/* V.21 */
#define TONEDT_ORIG__V22_USB1						0x0004				/* V.22 - 2250Hz */
#define TONEDT_ORIG__B103_B212_2225					0x0008				/* Bell 103/212 */
#define TONEDT_ORIG__ANSWER_2100					TONEDT__ANSWER_2100	/* Answer tone */
#define TONEDT_ORIG__V32_600						0x0020				/* V.32 - not used */
#define TONEDT_ORIG__V32_AC							TONEDT__V32_3000	/* V.32 - 3000Hz - Special for call progress */
#define TONEDT_ORIG__B202_1200						0x0080
/*
 *	Bit masks in the tone_detector_flags produced by the answer
 *	tone detector
 */
#define TONEDT_ANS__V23_390							0x0001	/* V.23 */
#define TONEDT_ANS__V21_980							0x0002	/* V.21 */

#define TONEDT_ANS__B103_1270						0x0008	/* Bell 103  */

#define TONEDT_ANS__V32_AA							0x0020	/* V.32 - 1800Hz */
#define TONEDT_ANS__V32_3000						TONEDT__V32_3000	/* Special for call progress - not used for timer */
/*define TONEDT_ANS__B202_387	0x0080  Bell 202 - not used for timer */

#define TONEDT_ANS__CALLING_1300					0x0400	/* Data calling tone */
#define TONEDT_ANS__CNG_1100						0x0800	/* FAX calling tone (CNG) */

/* ************************************************************************* */
/*
 *	Bit masks in the tone_detector_flags produced by the respond tone detector
 *
 */
/*define TONEDT_V8BIS__ANSWER_2100	TONEDT__ANSWER_2100  Answer tone - not used */

#define TONEDT_V8BIS__INIT_MRd						0x0080	/* 650 Hz */
#define TONEDT_V8BIS__INIT_CRd						0x0100	/* 1900 Hz */
#define TONEDT_V8BIS__INIT_ESi						0x0200	/* 980 Hz */
#define TONEDT_V8BIS__INIT_MRe						0x0400	/* 650 Hz */
#define TONEDT_V8BIS__INIT_CRe						0x0800	/* 400 Hz */

#define TONEDT_V8BIS__INIT_1375						0x1000	/* Segment 1 */
#define TONEDT_V8BIS__INIT_2002						0x2000	/* Segment 1 */

#define TONEDT_V8BIS__INIT_SEG_1					0 + (TONEDT_V8BIS__INIT_1375 | TONEDT_V8BIS__INIT_2002)
/*
 *	Bit masks in the tone_detector_flags produced by the initiate tone detector
 *
 */
#define TONEDT_V8BIS__RSPD_MRd						0x0080	/* 1150 Hz */
#define TONEDT_V8BIS__RSPD_CRd						0x0100	/* 1900 Hz */
#define TONEDT_V8BIS__RSPD_ESr						0x0200	/* 1650 Hz */

#define TONEDT_V8BIS__CALLING_1300					0x0400	/* Data calling tone */
#define TONEDT_V8BIS__CNG_1100						0x0800	/* FAX calling tone (CNG) */

#define TONEDT_V8BIS__RSPD_1529						0x1000	/* Segment 1 */
#define TONEDT_V8BIS__RSPD_2225						0x2000	/* Segment 1 */

#define TONEDT_V8BIS__RSPD_SEG_1					0x0000 + (TONEDT_V8BIS__RSPD_1529 | TONEDT_V8BIS__RSPD_2225)

/* ************************************************************************* */
/*
 *	Bit masks in the tone_detector_flags produced by the call progress
 *	tone detector (includes silence and call progress energy)
 *
 */
#define TONEDT_CP__V8BIS_1375						0x1000	/* V.8bis segment 1 */
#define TONEDT_CP__V8BIS_2002						0x2000	/* V.8bis segment 1 */

#define TONEDT_CP__SILENCE							0x4000	/* Defined as bit numbers below */
#define TONEDT_CP__CALL_PROGRESS					0x8000	/* Defined as bit numbers below */

#define TONEDT_CP__SILENCE__BN						0x000E
#define TONEDT_CP__CALL_PROGRESS__BN				0x000F
/*
 *	Bit masks in the tone_detector_flags produced by the answer detect/call
 *	progress tone detector (includes silence and call progress energy)
 *
 */
#define TONEDT_AD__SIT1								0x0080	/* 900/950 Hz */
#define TONEDT_AD__SIT2								0x0100	/* 1400 Hz */
#define TONEDT_AD__SIT3								0x0200	/* 1800 Hz */

#define TONEDT_AD__CALLING_1300						0x0400	/* Data calling tone */
#define TONEDT_AD__CNG_1100							0x0800	/* FAX calling tone (CNG) */

/* ************************************************************************* */
/*
 *	Bit masks in the tone_detector_flags produced by the disconnect tone detector
 *
 */
#define TONEDT_DT__TONE_1							0x0001	/* Tone 1 as specified by parameters */
#define TONEDT_DT__TONE_2							0x0002	/* Tone 2 as specified by parameters */
#define TONEDT_DT__TONE_3							0x0004	/* Tone 3 as specified by parameters */
#define TONEDT_DT__TONE_4							0x0008	/* Tone 4 as specified by parameters */
#define TONEDT_DT__TONE_5							0x0010	/* Tone 5 as specified by parameters */
#define TONEDT_DT__TONE_6							0x0020	/* Tone 6 as specified by parameters */

#define TONEDT_DT__TONE_PAIR_1						0x0100	/* Tone pair 1 */
#define TONEDT_DT__TONE_PAIR_2						0x0200	/* Tone pair 2 */
#define TONEDT_DT__TONE_PAIR_3						0x0400	/* Tone pair 3 */

#define TONEDT_DT__SILENCE							0x4000	/* Defined as bit numbers below */
#define TONEDT_DT__CALL_PROGRESS					0x8000	/* Defined as bit numbers below */

#define TONEDT_DT__SILENCE__BN						0x000E
#define TONEDT_DT__CALL_PROGRESS__BN				0x000F

/* ************************************************************************* */

#endif /* _INCLUDE_TONEDT_H */
