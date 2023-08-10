
/* ************************************************************************* */
/*
 *	pump.h
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
 *	Pump global rate selection locations, mask bits, and status conditions.
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

#ifndef _INCLUDE_PUMP_H
#define _INCLUDE_PUMP_H

/* ************************************************************************* */

#include "include/dm.h"

/* ************************************************************************* */
/*
 *	Define permitted pump modulation bit masks
 *
 */
#define PERMIT__NONE		0x0000

#define PERMIT__AUTOMODE	0x8000		/* Enable automode operation */
#define PERMIT__V8			0x4000		/* Enable V.8 operation */
#define PERMIT__V8_BIS		0x2000		/* Enable V.8bis operation */

#define PERMIT__V92			0x1000		/* V.92 PCM upstream */
#define PERMIT__V90			0x0800		/* V.90 up to 56K */
#define PERMIT__V34			0x0400		/* V.34 28,800 et al. */
#define PERMIT__V32			0x0200		/* V.32terbo 19,200 and 16,800 */
										/* V.32bis 14,400, 12,000, 9600, 7200 */
										/* V.32 9600 and 4800 non-trellis */
#define PERMIT__V23			0x0100		/* V.23 1200 or Bell 202*/
#define PERMIT__V23_HALF	0x0080		/* V.23 600  */
#define PERMIT__V23_REV		0x0040		/* V.23 75 */			/* Not used */
#define PERMIT__V22_BIS		0x0020		/* V.22bis 2400 */
#define PERMIT__V22_FALL	0x0010		/* V.22bis 1200 */		/* Not used */
#define PERMIT__V22			0x0008		/* V.22 1200 or Bell 212*/
#define PERMIT__V22_HALF	0x0004		/* V.22 600 */
#define PERMIT__V21			0x0002		/* V.21 300 or Bell 103 */
#define PERMIT__BELL		0x0001		/* Enable Bell mode */
/*
 *	Define permitted pump modulation masks
 *
 */
#define PERMIT_MASK__V34	(PERMIT__V34)
#define PERMIT_MASK__V32	(PERMIT__V32)
#define PERMIT_MASK__V23	(PERMIT__V23 | PERMIT__V23_HALF | PERMIT__V23_REV)
#define PERMIT_MASK__V22	(PERMIT__V22_BIS | PERMIT__V22_FALL | PERMIT__V22 | PERMIT__V22_HALF)
#define PERMIT_MASK__V21	(PERMIT__V21)

#define PERMIT__V8_OR_AUTOMODE	(PERMIT__AUTOMODE | PERMIT__V8)
/*
 *	Define permitted digital mode bit masks
 *
 */
#define PERMIT__HDSPATCH				0x2000		/* Enable H.DISPATCH operation */
#define PERMIT__GSMV110_TRANSPARENT		0x0010		/* Transparent (Async) GSM V.110 Rate Adaptation */
#define PERMIT__GSMV110_NONTRANSPARENT	0x0008		/* Non-Trasparent GSM V.110 Rate Adaptation */
#define PERMIT__ISDN_B1_56				0x0004		/* Enable 56 Kbps B1 direct data mode */
#define PERMIT__ISDN_B1_64				0x0002		/* Enable 64 Kbps B1 direct data mode */
#define PERMIT__V110					0x0001		/* V.110 Rate Adaptation */

#define PERMIT__GSMV110		(PERMIT__GSMV110_TRANSPARENT | PERMIT__GSMV110_NONTRANSPARENT)
#define PERMIT__ISDN_B1		(PERMIT__ISDN_B1_64 | PERMIT__ISDN_B1_56)
/*
 *	Define selected half-duplex modulation bit masks
 *
 */
#define SELECT__TX_ENABLE		0x8000
#define SELECT__RX_ENABLE		0x4000
#define SELECT__FAST_TRAIN		0x2000
#define SELECT__ECHO_PROTECT	0x1000

#define SELECT__BRIDGE_ENABLE	0x0800		/* Used with non-V.34 */

#define SELECT__V34_FULL		0x0800		/* V.34 full duplex */
#define SELECT__V34_HALF		0x0400		/* V.34 half duplex */
#define SELECT__V17_144			0x0200		/* 14,400 */
#define SELECT__V17_120			0x0100		/* 12,000 */
#define SELECT__V17_96			0x0080		/* 9600 */
#define SELECT__V17_72			0x0040		/* 7200 */
#define SELECT__V29_96			0x0020		/* 9600 */
#define SELECT__V29_72			0x0010		/* 7200 */
#define SELECT__V29_48			0x0008		/* 4800 */
#define SELECT__V27_48			0x0004		/* 4800 */
#define SELECT__V27_24			0x0002		/* 2400 */
#define SELECT__V21				0x0001		/* 300 */
/*
 *	Define selected half-duplex modulation masks
 *
 */
#define SELECT_MASK__V34_FULL	(SELECT__V34_FULL)
#define SELECT_MASK__V34_HALF	(SELECT__V34_HALF)
#define SELECT_MASK__V17		(SELECT__V17_144 | SELECT__V17_120 | SELECT__V17_96 | SELECT__V17_72)
#define SELECT_MASK__V29		(SELECT__V29_96 | SELECT__V29_72 | SELECT__V29_48)
#define SELECT_MASK__V27		(SELECT__V27_48 | SELECT__V27_24)
#define SELECT_MASK__V21		(SELECT__V21)
/*
 *	Define option configuration masks
 *
 */
#define CONFIG__V25_CALLING					0x0001	/* Enable V.25 calling tone */
#define CONFIG__V25_ANSWER					0x0002	/* Enable V.25 answer tone */

#define CONFIG__GUARD_550					0x0004	/* Enable V.22/V.22bis guard tone */
/* #define CONFIG__GUARD_1800				0x0008 */	/* Enable V.22/V.22bis guard tone */
#define CONFIG__SWITCHED_CARRIER_ENABLE		0x0008	/* Enable V.23 Half-duplex switched carrier */

/* #define CONFIG__V8_MODE					0x0010 */	/* Modulation V.8 auto mode */
#define CONFIG__EARLY_HANDSHAKE_ENABLE		0x0010	/* Enable V.23 early transmit */

/* #define CONFIG__RDL_ACK					0x0020 */	/* Enable acknowledge of remote RDL */
#define CONFIG__POINT_OF_SALE_ENABLE		0x0020	/* V.22 Point of Sale Enable */

#define CONFIG__V8_CI_ENABLE				0x0040	/* V.8 CI enable control */
#define CONFIG__V8_EXTERNAL					0x0080	/* V.8 external negotiations */
#define CONFIG__V8_START_DISABLE			0x0100	/* V.8 completion start inhibit */
#define CONFIG__V8_CNG_ENABLE				0x0400	/* V.8 CNG generation control */
#define CONFIG__V8_V21_FLAG_DETECT_ENABLE	0x0800	/* V.8 V.21 flag detect control */

#define CONFIG__FAX_FAA						0x0200	/* FAX Adaptive answer enable */

#define CONFIG__AUTOMODE_REVERSE_ENABLE		0x1000	/* Automode begins with V.21, then V.22 */
#define CONFIG__ANSWER_REVERSE_DISABLE		0x2000	/* Answer tone reversal disable */
#define CONFIG__V8_SHORT_ENABLE				0x4000	/* Enable V.92 short V.8 operation */

/*
 *	Bit definitions
 *
 */
#define CONFIG__V8_CI_DISABLE__BIT			6	/* V.8 CI disable control */
#define CONFIG__V8_EXTERNAL__BIT			7	/* V.8 external negotiations */
#define CONFIG__V8_START_DISABLE__BIT		8	/* V.8 completion start inhibit */

#define CONFIG__FAX_FAA__BIT				9	/* FAX Adaptive answer enable */

/* ************************************************************************* */
/*
 *	Define pump status masks
 *
 */
#define PUMP__NEGOTIATION			0x0001
#define PUMP__CONNECTION			0x0002
#define PUMP__RETRAIN				0x0004

#define PUMP__LOCAL_RETRAIN			0x0010
#define PUMP__REMOTE_RETRAIN		0x0020
#define PUMP__AUTO_RETRAIN			0x0040

#define PUMP__LOCAL_RENEGOTIATION	0x0100
#define PUMP__REMOTE_RENEGOTIATION	0x0200
#define PUMP__AUTO_RENEGOTIATION	0x0400

#define PUMP__TIMEOUT				0x1000
#define PUMP__RETRY					0x2000
#define PUMP__CLEARDOWN				0x4000

/*
 *	Define RDLB status masks
 *
 */

#define RDLB__

/* ************************************************************************* */
/*
 *	The following speed bases and masks are used to set the
 *	default modulation bases.
 *
 */

#define SPEED__ISDN__BASE						(DM_CARRIER_STATUS__BF__ISDN + DM_CARRIER_STATUS__BIT__DIGITAL)
#define SPEED__V110__BASE						(DM_CARRIER_STATUS__BF__V110 + DM_CARRIER_STATUS__BIT__DIGITAL)
#define SPEED__GSMV110_NONTRANSPARENT__BASE		(DM_CARRIER_STATUS__BF__V110 + DM_CARRIER_STATUS__BIT__DIGITAL + DM_CARRIER_STATUS__BIT__GSM)
#define SPEED__GSMV110_TRANSPARENT__BASE		(DM_CARRIER_STATUS__BF__V110 + DM_CARRIER_STATUS__BIT__DIGITAL + DM_CARRIER_STATUS__BIT__GSM + DM_CARRIER_STATUS__BIT__ASYNC)

#define SPEED__V90__BASE						(DM_CARRIER_STATUS__BF__V90)
#define SPEED__V92__BASE						(DM_CARRIER_STATUS__BF__V92)
#define SPEED__K56__BASE						(DM_CARRIER_STATUS__BF__K56)

#define SPEED__V34__BASE						(DM_CARRIER_STATUS__BF__V34)
#define SPEED__V32B__BASE						(DM_CARRIER_STATUS__BF__V32B)
#define SPEED__V32__BASE						(DM_CARRIER_STATUS__BF__V32)
#define SPEED__V26__BASE						(DM_CARRIER_STATUS__BF__V26B)
#define SPEED__V22__BASE						(DM_CARRIER_STATUS__BF__V22)

#define SPEED__V21SYNC__BASE					(DM_CARRIER_STATUS__BF__V21 + DM_CARRIER_STATUS__BIT__FAX)
#define SPEED__V21__BASE						(DM_CARRIER_STATUS__BF__V21 + DM_CARRIER_STATUS__BIT__ASYNC)
#define SPEED__B103__BASE						(DM_CARRIER_STATUS__BF__V21 + DM_CARRIER_STATUS__BIT__ASYNC + DM_CARRIER_STATUS__BIT__BELL)
#define SPEED__V23__BASE						(DM_CARRIER_STATUS__BF__V23 + DM_CARRIER_STATUS__BIT__ASYNC)
#define SPEED__B202__BASE						(DM_CARRIER_STATUS__BF__V23 + DM_CARRIER_STATUS__BIT__ASYNC + DM_CARRIER_STATUS__BIT__BELL)

#define SPEED__V17__BASE						(DM_CARRIER_STATUS__BF__V17  + DM_CARRIER_STATUS__BIT__FAX)
#define SPEED__V29__BASE						(DM_CARRIER_STATUS__BF__V29  + DM_CARRIER_STATUS__BIT__FAX)
#define SPEED__V27__BASE						(DM_CARRIER_STATUS__BF__V27T + DM_CARRIER_STATUS__BIT__FAX)

/* ************************************************************************* */

#define SPEED__V32__NONE						(SPEED__V32__BASE  + BR__2400)
#define SPEED__V32__4800						(SPEED__V32__BASE  + BR__4800)
#define SPEED__V32__7200						(SPEED__V32B__BASE + BR__7200)
#define SPEED__V32__9600U						(SPEED__V32__BASE  + BR__9600)
#define SPEED__V32__9600						(SPEED__V32B__BASE + BR__9600)
#define SPEED__V32__12000						(SPEED__V32B__BASE + BR__12000)
#define SPEED__V32__14400						(SPEED__V32B__BASE + BR__14400)

#define SPEED__V22__600							(SPEED__V22__BASE + BR__600)
#define SPEED__V22__1200						(SPEED__V22__BASE + BR__1200)
#define SPEED__V22__2400						(SPEED__V22__BASE + BR__2400)

#define SPEED__V17__7200						(SPEED__V17__BASE + BR__7200)
#define SPEED__V17__9600						(SPEED__V17__BASE + BR__9600)
#define SPEED__V17__12000						(SPEED__V17__BASE + BR__12000)
#define SPEED__V17__14400						(SPEED__V17__BASE + BR__14400)

#define SPEED__V29__4800						(SPEED__V29__BASE + BR__4800)
#define SPEED__V29__7200						(SPEED__V29__BASE + BR__7200)
#define SPEED__V29__9600						(SPEED__V29__BASE + BR__9600)

#define SPEED__V27__2400						(SPEED__V27__BASE + BR__2400)
#define SPEED__V27__4800						(SPEED__V27__BASE + BR__4800)

#define SPEED__V21SYNC__300						(SPEED__V21SYNC__BASE + BR__300)

#define SPEED__V21__300							(SPEED__V21__BASE + BR__300)
#define SPEED__B103__300						(SPEED__B103__BASE + BR__300)

#define SPEED__V23__0675						(SPEED__V23__BASE + BR__75)
#define SPEED__V23__1275						(SPEED__V23__BASE + BR__75)
#define SPEED__V23__7506						(SPEED__V23__BASE + BR__600)
#define SPEED__V23__7512						(SPEED__V23__BASE + BR__1200)

#define SPEED__B202__1275						(SPEED__B202__BASE + BR__75)
#define SPEED__B202__7512						(SPEED__B202__BASE + BR__1200)

#define SPEED__V23__CID							SPEED__V23__7512
#define SPEED__B202__CID						SPEED__B202__7512

#define SPEED__ISDN__56000						(SPEED__ISDN__BASE + BR__56000)
#define SPEED__ISDN__64000						(SPEED__ISDN__BASE + BR__64000)
#define SPEED__ISDN__128000						(SPEED__ISDN__BASE + BR__128000)

#define SPEED__ISDN__64000_BINARY				(SPEED__ISDN__BASE + BR__64000 + DM_CARRIER_STATUS__BIT__BINARY)

/* ************************************************************************* */

#define	V32_JUMP_TABLE_INDEX_14400		6
#define V32_JUMP_TABLE_INDEX_12000		5
#define V32_JUMP_TABLE_INDEX_9600		4
#define V32_JUMP_TABLE_INDEX_9600U		3
#define V32_JUMP_TABLE_INDEX_7200		2
#define V32_JUMP_TABLE_INDEX_4800		1
#define V32_JUMP_TABLE_INDEX_2400		0

/* ************************************************************************* */

#endif /* _INCLUDE_PUMP_H */
