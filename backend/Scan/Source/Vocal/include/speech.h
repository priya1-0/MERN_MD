
/* ************************************************************************* */
/*
 *	speech.h
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
 *	Speech coder selection masks.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 19:50:33  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _INCLUDE_SPEECH_H
#define _INCLUDE_SPEECH_H

/* ************************************************************************* */
/*
 *	Type of coder in bits 11-8, rate/coder dependent options in bits 5-0,
 *	system options in bits 15-12
 */
#define SPEECH__BF__MASK					0x0F00
#define SPEECH_OPTIONS__BF__MASK			0x003F

#define SPEECH__BIT__SILENCE				0x1000
#define SPEECH__BIT__NON_VOICE				0x2000
#define SPEECH__BIT__DTMF					0x4000
#define SPEECH__BIT__CONCEALMENT_DISABLE	0x8000

#define SPEECH__LINEAR				0x0000
#define SPEECH__LINEAR_8			0x0008
#define SPEECH__LINEAR_9			0x0009
#define SPEECH__LINEAR_10			0x000a
#define SPEECH__LINEAR_11			0x000b
#define SPEECH__LINEAR_12			0x000c
#define SPEECH__LINEAR_13			0x000d
#define SPEECH__LINEAR_14			0x000e
#define SPEECH__LINEAR_15			0x000f
#define SPEECH__LINEAR_16			0x0010

#define SPEECH__G711				0x0100
#define SPEECH__G711_U_LAW			0x0100
#define SPEECH__G711_A_LAW			0x0101

#define SPEECH__G721				0x0604		/* G.721 is G.726 32000 */

#define SPEECH__G722				0x0200

#define SPEECH__G722_1				0x0210
#define SPEECH__G722_1_24K			0x0210		/* G.722.1 specified 24K rate code in low bits */
#define SPEECH__G722_1_32K			0x0211		/* G.722.1 specified 32K rate code in low bits */

#define SPEECH__G722P2				0x0220
#define SPEECH__G722P2_6K60			0x0220
#define SPEECH__G722P2_8K85			0x0221
#define SPEECH__G722P2_12K65		0x0222
#define SPEECH__G722P2_14K25		0x0223
#define SPEECH__G722P2_15K85		0x0224
#define SPEECH__G722P2_18K25		0x0225
#define SPEECH__G722P2_19K85		0x0226
#define SPEECH__G722P2_23K05		0x0227
#define SPEECH__G722P2_23K85		0x0228

#define SPEECH__G723				0x0300
#define SPEECH__G723_6K4			0x0300		/* G.723 specified 6.4K rate code in low bits */
#define SPEECH__G723_5K3			0x0301		/* G.723 specified 5.3K rate code in low bits */
#define SPEECH__BIT__G723_RATE		0x0001		/* G.723 0 - 6.4K, 1 - 5.3K */
#define SPEECH__BIT__G723_REDUCED_PROCESSING 0x0002 /* G.723 0 - normal, 1 - reduced processing */

#define SPEECH__G726				0x0600
#define SPEECH__G726_16000			0x0602		/* G.726 16000 uses 2 bits per sample */
#define SPEECH__G726_24000			0x0603		/* G.726 24000 uses 3 bits per sample */
#define SPEECH__G726_32000			0x0604		/* G.726 32000 uses 4 bits per sample */
#define SPEECH__G726_40000			0x0605		/* G.726 48000 uses 5 bits per sample */

#define SPEECH__G728				0x0800

#define SPEECH__G729				0x0900
#define SPEECH__G729_A				0x0901
#define SPEECH__G729_B				0x0902
#define SPEECH__G729_AB				0x0903
#define SPEECH__BIT__G729_A			0x0001
#define SPEECH__BIT__G729_B			0x0002

#define SPEECH__G729_E				0x0902
#define SPEECH__G729_E_8K			0x0902		/* G.729e specified 8K rate code */
#define SPEECH__G729_E_11K8			0x0903		/* G.729e specified 11K8 rate code */
#define SPEECH__G729_D				0x0904
#define SPEECH__G729_D_8K			0x0904		/* G.729d specified 8K rate code */
#define SPEECH__G729_D_6K4			0x0905		/* G.729d specified 6K4 rate code */

#define SPEECH__GSM_EFR				0x0a00
#define SPEECH__GSM_FR				0x0a01
#define SPEECH__GSM_HFR				0x0a02

#define SPEECH__GSM_AMR				0x0b00

#define SPEECH__GSM_AMR_4K75		0x0b00
#define SPEECH__GSM_AMR_5K15		0x0b01
#define SPEECH__GSM_AMR_5K9 		0x0b02
#define SPEECH__GSM_AMR_6K7 		0x0b03
#define SPEECH__GSM_AMR_7K4 		0x0b04
#define SPEECH__GSM_AMR_7K95		0x0b05
#define SPEECH__GSM_AMR_10K2		0x0b06
#define SPEECH__GSM_AMR_12K2		0x0b07

#define SPEECH__MELP				0x0c00

#define SPEECH__ILBC				0x0d00
#define SPEECH__ILBC_13K33			0x0d00
#define SPEECH__ILBC_15K2			0x0d01

#define SPEECH__FAX_T38				0x0e00

#define SPEECH__SPEEX				0x0f00

/* ************************************************************************* */

#define SPEECH_DEVICE__LINE			0x0000
#define SPEECH_DEVICE__SPEAKERPHONE	0x0001
#define SPEECH_DEVICE__HANDSET		0x0002
#define SPEECH_DEVICE__HEADSET		0x0003

/* ************************************************************************* */

#define ASM__BIT__OOB_TONE			0x8000
#define ASM__BIT__SILENCE			0x4000
#define ASM__BIT__NOISE				0x2000
#define ASM__BIT__BAD_FRAME			0x1000
#define ASM__BIT__AUDIO_RESET		0x0800
#define ASM__BIT__AUDIO_PAUSE		0x0400
#define ASM__BIT__TRANSITION_U_LAW	0x0200
#define ASM__BIT__TRANSITION_A_LAW	0x0100

#define ASM_CONTROL_ARG__BF__MASK	0x000F

/* ************************************************************************* */

#define AD_CODE__NULL				0x0000
#define AD_CODE__HALTED				0x0001
#define AD_CODE__VOICE				0x0002
#define AD_CODE__SIT				0x0004
#define AD_CODE__CNG				0x0005
#define AD_CODE__CT					0x0006
#define AD_CODE__BUSY				0x0007
#define AD_CODE__RRING				0x0008
#define AD_CODE__DIALTONE			0x0009
#define AD_CODE__SIT1				0x0010
#define AD_CODE__SIT2				0x0011
#define AD_CODE__SIT3				0x0012

/* ************************************************************************* */

#define	FAXDET__BIT__ABS				0x0020
#define	FAXDET__BIT__OLD_ABSOLUTE		0x0010
#define	FAXDET__BIT__NEW_ABSOLUTE		0x0008
#define	FAXDET__BIT__DIFF				0x0004
#define	FAXDET__BIT__V21				0x0002
#define	FAXDET__BIT__CED				0x0001
#define	FAXDET__BIT__ANSAM_PHASE_REV	0x0040

/* ************************************************************************* */

#define RTP_TONE__BIT__DTMF			0x0001
#define RTP_TONE__BIT__ANS			0x0002

/* ************************************************************************* */
/* These are control bits for reporting various Events/Status during speech
   operations. */

#define SPEECH_REPORT__BIT__ENC_PACKET_READY	0x0001
#define SPEECH_REPORT__BIT__DEC_PACKET_READY	0x0002
#define SPEECH_REPORT__BIT__ENC_OVERRUN			0x0004

/* ************************************************************************* */
/* Encoder Transitioning Control */

#define SPEECH_ENC_TRANS__BIT__SYNC_NOW			0x0001
#define SPEECH_ENC_TRANS__BIT__FOLLOW_DEC		0x0002
#define SPEECH_ENC_TRANS__BIT__VAD_EN			0x0004
#define SPEECH_ENC_TRANS__BIT__FAXDET_EN		0x0008
#define SPEECH_ENC_TRANS_DEST__BF__MASK			0x0070
#define SPEECH_ENC_TRANS_DEST__BF__ULAW			0x0000
#define SPEECH_ENC_TRANS_DEST__BF__ALAW			0x0010
#define SPEECH_ENC_TRANS_DEST__BF__LINEAR		0x0020
#define SPEECH_ENC_TRANS_DEST__BF__T38			0x0030

/* ************************************************************************* */
/* These are byte values, similar to the RTP packet payload types. */
/* Where possible, these match RFC 3551 Section 6, but they are really */
/* internal values that will be mapped into true rtp payload types in */
/* htonrtp/ntohrtp.  The reason they match RFC 3551 is we also use them */
/* as the default codec numbers in our rtpmapped SDP offers. */

#define PKT_TYPE__INVALID		127		/* unmapped or bad received packets */
#define PKT_TYPE__PCM_ULAW		0
#define PKT_TYPE__PCM_ALAW		8
#define PKT_TYPE__CNG			13		/* G.711 II */

#define PKT_TYPE__G726_16		102
#define PKT_TYPE__G726_24		103
#define PKT_TYPE__G726_32		2
#define PKT_TYPE__G726_40		105

#define PKT_TYPE__G722_1		9
#define PKT_TYPE__G722			91		/* Number can be anything */
#define PKT_TYPE__G722P2		99		/* Number can be anything */
#define PKT_TYPE__G723			4
#define PKT_TYPE__G728			15
#define PKT_TYPE__G729			18		/* No distinction with G.729A needed externally or for parsing frames */
#define PKT_TYPE__G729A			18
#define PKT_TYPE__G729B			109
#define PKT_TYPE__G729AB		109

#define PKT_TYPE__GSM_FR		3
#define PKT_TYPE__GSM_EFR		107
#define PKT_TYPE__GSM_AMR		98		/* Number can be anything */

#define PKT_TYPE__T38			108

#define PKT_TYPE__NSE			100
#define PKT_TYPE__DTMF			101

/* Packet types 110-119 are suggested as reserved for video - see include/video.h */

#define PKT_TYPE__SPEEX			97		/* Number can be anything */
#define PKT_TYPE__LINEAR		120		/* Number can be anything */
#define PKT_TYPE__MELP			122		/* Number can be anything */
#define PKT_TYPE__ILBC			124		/* Number can be anything */

#define PKT_TYPE__MISSING_INDICATION		255

#define CNG_PKT_SIZE__G729A		2
#define CNG_PKT_SIZE__G723		2

/* ************************************************************************* */

#endif /* _INCLUDE_SPEECH_H */
