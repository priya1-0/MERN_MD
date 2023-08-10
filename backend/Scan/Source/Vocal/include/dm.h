
/* ************************************************************************* */
/*
 *	dm.h
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
 *	This header file contains data modulation related symbol definitions.
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

#ifndef _INCLUDE_DM_H
#define _INCLUDE_DM_H

/* ************************************************************************* */
/*
 *	The value of symbol DM_CARRIER_STATUS__MASK will not change.
 *	The value of symbol DM_CARRIER_STATUS__BIT__ASYNC will not change.
 *	The value of symbol DM_CARRIER_STATUS__BIT__FAX will not change.
 */

#define DM_CARRIER_STATUS__MASK							0xff00
#define DM_CARRIER_STATUS__BIT__ASYNC					0x1000
#define DM_CARRIER_STATUS__BIT__FAX						0x2000
#define DM_CARRIER_STATUS__BIT__BELL					0x4000
#define DM_CARRIER_STATUS__BIT__BINARY					0x4000
#define DM_CARRIER_STATUS__BIT__DIGITAL					0x8000

#define DM_CARRIER_STATUS__BF__MASK						0x0f00
#define DM_CARRIER_STATUS__BF__V21						0x0100
#define DM_CARRIER_STATUS__BF__V22						0x0200
/*efine DM_CARRIER_STATUS__BF__V22B						0x0300 */
#define DM_CARRIER_STATUS__BF__V23						0x0400
#define DM_CARRIER_STATUS__BF__V26T						0x0600
#define DM_CARRIER_STATUS__BF__V27T						0x0700
#define DM_CARRIER_STATUS__BF__V29						0x0800
#define DM_CARRIER_STATUS__BF__V32						0x0900
#define DM_CARRIER_STATUS__BF__V32B						0x0a00
#define DM_CARRIER_STATUS__BF__V34						0x0b00
#define DM_CARRIER_STATUS__BF__V17						0x0c00

#define DM_CARRIER_STATUS__BF__K56						0x0500
#define DM_CARRIER_STATUS__BF__V90						0x0d00
#define DM_CARRIER_STATUS__BF__V92						0x0300

#define DM_CARRIER_STATUS__BF__V110						0x0e00
#define DM_CARRIER_STATUS__BF__ISDN						0x0f00

/* ************************************************************************* */

#define DM_V32_RATE__BIT__BASE							0x0111
#define DM_V32_RATE__BIT__TCM							0x0880
#define DM_V32_RATE__BIT__4800							0x0400
#define DM_V32_RATE__BIT__7200							0x0040
#define DM_V32_RATE__BIT__9600							0x0200
#define DM_V32_RATE__BIT__12000							0x0020
#define DM_V32_RATE__BIT__14400							0x0008
#define DM_V32_RATE__BIT__16800							0x0004
#define DM_V32_RATE__BIT__19200							0x0002

#define DM_V32_RATE__4800								DM_V32_RATE__BIT__BASE | DM_V32_RATE__BIT__4800
#define DM_V32_RATE__7200_TCM							DM_V32_RATE__BIT__BASE | DM_V32_RATE__BIT__TCM | DM_V32_RATE__BIT__7200
#define DM_V32_RATE__9600								DM_V32_RATE__BIT__BASE | DM_V32_RATE__BIT__9600
#define DM_V32_RATE__9600_TCM							DM_V32_RATE__BIT__BASE | DM_V32_RATE__BIT__TCM | DM_V32_RATE__BIT__9600
#define DM_V32_RATE__12000_TCM							DM_V32_RATE__BIT__BASE | DM_V32_RATE__BIT__TCM | DM_V32_RATE__BIT__12000
#define DM_V32_RATE__14400_TCM							DM_V32_RATE__BIT__BASE | DM_V32_RATE__BIT__TCM | DM_V32_RATE__BIT__14400
#define DM_V32_RATE__16800_TCM							DM_V32_RATE__BIT__BASE | DM_V32_RATE__BIT__TCM | DM_V32_RATE__BIT__16800
#define DM_V32_RATE__19200_TCM							DM_V32_RATE__BIT__BASE | DM_V32_RATE__BIT__TCM | DM_V32_RATE__BIT__19200

#define DM_V32_BIS_ALL_DATA_RATE__7200					DM_V32_RATE__4800 | DM_V32_RATE__7200_TCM
#define DM_V32_BIS_ALL_DATA_RATE__9600					DM_V32_RATE__4800 | DM_V32_RATE__7200_TCM | DM_V32_RATE__9600_TCM
#define DM_V32_BIS_ALL_DATA_RATE__12000					DM_V32_RATE__4800 | DM_V32_RATE__7200_TCM | DM_V32_RATE__9600_TCM | DM_V32_RATE__12000_TCM
#define DM_V32_BIS_ALL_DATA_RATE__14400					DM_V32_RATE__4800 | DM_V32_RATE__7200_TCM | DM_V32_RATE__9600_TCM | DM_V32_RATE__12000_TCM | DM_V32_RATE__14400_TCM
#define DM_V32_BIS_ALL_DATA_RATE__16800					DM_V32_RATE__4800 | DM_V32_RATE__7200_TCM | DM_V32_RATE__9600_TCM | DM_V32_RATE__12000_TCM | DM_V32_RATE__14400_TCM | DM_V32_RATE__16800_TCM
#define DM_V32_BIS_ALL_DATA_RATE__19200					DM_V32_RATE__4800 | DM_V32_RATE__7200_TCM | DM_V32_RATE__9600_TCM | DM_V32_RATE__12000_TCM | DM_V32_RATE__14400_TCM | DM_V32_RATE__16800_TCM | DM_V32_RATE__19200_TCM

#define DM_V32_ALL_DATA_RATE__9600						DM_V32_RATE__4800 | DM_V32_RATE__9600

/* ************************************************************************* */

#define DM_V22_RATE__BIT__600							0x0004
#define DM_V22_RATE__BIT__1200							0x0008
#define DM_V22BIS_RATE__BIT__2400						0x0020

/* ************************************************************************* */

#define DM_OPTION__BIT__CALLING_TONE_EN					0x0001
#define DM_OPTION__BIT__ANSWER_TONE_EN					0x0002
#define DM_OPTION__BIT__ANSWER_REVERSE_DIS				CONFIG__ANSWER_REVERSE_DISABLE
#define DM_OPTION__BIT__GUARD_TONE_EN					0x0004
#define DM_OPTION__BIT__SWITCHED_CARRIER_EN				0x0008
#define DM_OPTION__BIT__FAX_ADAPTIVE_ANSWER_EN			0x0010
#define DM_OPTION__BIT__POINT_OF_SALE_EN				0x0020
#define DM_OPTION__BIT__FSK_SHORT_TRAIN					0x0040
#define DM_OPTION__BIT__FAX_FAA_EN						0x0200

/* ************************************************************************* */

#define DM_LINE_QUAL_MON__OFF							0x0000
#define DM_LINE_QUAL_MON__RETRAIN						0x0001
#define DM_LINE_QUAL_MON__FALLBACK						0x0002
#define DM_LINE_QUAL_MON__FALLFORWARD					0x0004
#define DM_LINE_QUAL_MON__RENEGOTIATE_LIMIT				0x0008
#define DM_LINE_QUAL_MON__TX_RATE_CONTROL				0x0100
#define DM_LINE_QUAL_MON__POST_RENEG_ASSURANCE			0x0200

/* ************************************************************************* */

#define DM_CLOCK__INTERNAL								0x0000
#define DM_CLOCK__EXTERNAL								0x0001
#define DM_CLOCK__SLAVE									0x0002

/* ************************************************************************* */

/* The value of symbols DM_CARRIER__xxx will not change. */
#define DM_CARRIER__MASK__CARRIER						0x00fe
#define DM_CARRIER__BIT__V21							0x0002
#define DM_CARRIER__BIT__V23							0x0004
#define DM_CARRIER__BIT__V26							0x0008
#define DM_CARRIER__BIT__V22							0x0010
#define DM_CARRIER__BIT__V32							0x0020
#define DM_CARRIER__BIT__V34							0x0040
#define DM_CARRIER__BIT__K56							0x0080
#define DM_CARRIER__BIT__V90							0x0100
#define DM_CARRIER__BIT__AUTOMODE						0x8000
#define DM_CARRIER__BIT__V8								0x4000
#define DM_CARRIER__BIT__BELL							0x0001
#define DM_CARRIER__BIT__V110							0x1000

/* ************************************************************************* */

#define DM_V26BIS__BIT__1200							0x0001
#define DM_V26BIS__BIT__2400							0x0002
#define DM_V26TER__BIT__1200							0x0004
#define DM_V26TER__BIT__2400							0x0008

/* ************************************************************************* */

#define DM_SYMBOL_RATE__ASYNC							0x0001
#define DM_SYMBOL_RATE__600								0x0002
#define DM_SYMBOL_RATE__1200							0x0003
#define DM_SYMBOL_RATE__2400							0x0004
#define DM_SYMBOL_RATE__2743							0x0005
#define DM_SYMBOL_RATE__2800							0x0006
#define DM_SYMBOL_RATE__3000							0x0007
#define DM_SYMBOL_RATE__3200							0x0008
#define DM_SYMBOL_RATE__3429							0x0009

/* ************************************************************************** */

#define DM_V34_DATA_RATE__BIT__2400						0x0001
#define DM_V34_DATA_RATE__BIT__4800						0x0002
#define DM_V34_DATA_RATE__BIT__7200						0x0004
#define DM_V34_DATA_RATE__BIT__9600						0x0008
#define DM_V34_DATA_RATE__BIT__12000					0x0010
#define DM_V34_DATA_RATE__BIT__14400					0x0020
#define DM_V34_DATA_RATE__BIT__16800					0x0040
#define DM_V34_DATA_RATE__BIT__19200					0x0080
#define DM_V34_DATA_RATE__BIT__21600					0x0100
#define DM_V34_DATA_RATE__BIT__24000					0x0200
#define DM_V34_DATA_RATE__BIT__26400					0x0400
#define DM_V34_DATA_RATE__BIT__28800					0x0800
#define DM_V34_DATA_RATE__BIT__31200					0x1000
#define DM_V34_DATA_RATE__BIT__33600					0x2000

#define DM_V34_ALL_DATA_RATE__4800						0x0003
#define DM_V34_ALL_DATA_RATE__7200						0x0007
#define DM_V34_ALL_DATA_RATE__9600						0x000f
#define DM_V34_ALL_DATA_RATE__12000						0x001f
#define DM_V34_ALL_DATA_RATE__14400						0x003f
#define DM_V34_ALL_DATA_RATE__16800						0x007f
#define DM_V34_ALL_DATA_RATE__19200						0x00ff
#define DM_V34_ALL_DATA_RATE__21600						0x01ff
#define DM_V34_ALL_DATA_RATE__24000						0x03ff
#define DM_V34_ALL_DATA_RATE__26400						0x07ff
#define DM_V34_ALL_DATA_RATE__28800						0x0fff
#define DM_V34_ALL_DATA_RATE__31200						0x1fff
#define DM_V34_ALL_DATA_RATE__33600						0x3fff

/* ************************************************************************* */

#define DM_V34_OPTION__BIT__CME_EN						0x0001
#define DM_V34_OPTION__BIT__16POINT_EN					0x0002
#define DM_V34_OPTION__BIT__ASYMMETRIC_EN				0x0004
#define DM_V34_OPTION__BIT__AUXILIARY_EN				0x0008
#define DM_V34_OPTION__BIT__NONLINEAR_EN				0x0010
#define DM_V34_OPTION__BIT__PRECODER_EN					0x0020
#define DM_V34_OPTION__BIT__SHAPING_EN					0x0040
#define DM_V34_OPTION__BIT__ATTENUATION_EN				0x0080
#define DM_V34_OPTION__BIT__ANNEX12_EN					0x0100
#define DM_V34_OPTION__BIT__16POINT_CC_EN				0x0200
#define DM_V34_OPTION__BIT__ASYMMETRIC_CC_EN			0x0400
#define DM_V34_OPTION__BIT__SHORT_TRAIN_EN				0x0800

/* ************************************************************************* */

#define DM_V34_SYMBOL_RATE__BIT__LO_2400				0x0001
#define DM_V34_SYMBOL_RATE__BIT__LO_2743				0x0002
#define DM_V34_SYMBOL_RATE__BIT__LO_2800				0x0004
#define DM_V34_SYMBOL_RATE__BIT__LO_3000				0x0008
#define DM_V34_SYMBOL_RATE__BIT__LO_3200				0x0010
#define DM_V34_SYMBOL_RATE__BIT__LO_3429				0x0020
#define DM_V34_SYMBOL_RATE__BIT__HI_2400				0x0100
#define DM_V34_SYMBOL_RATE__BIT__HI_2743				0x0200
#define DM_V34_SYMBOL_RATE__BIT__HI_2800				0x0400
#define DM_V34_SYMBOL_RATE__BIT__HI_3000				0x0800
#define DM_V34_SYMBOL_RATE__BIT__HI_3200				0x1000
#define DM_V34_SYMBOL_RATE__BIT__HI_3429				0x2000

/* ************************************************************************* */

#define DM_V34_TRELLIS_CODING__16_STATE					0x0000
#define DM_V34_TRELLIS_CODING__32_STATE					0x0001
#define DM_V34_TRELLIS_CODING__64_STATE					0x0002

/* ************************************************************************* */

#define DM_V34_PTT_RESTRICTION__BIT__ATTENUATION		0x0001

/* ************************************************************************* */

#define DM_K56FLEX_DATA_RATE__BIT__32000				0x0001
#define DM_K56FLEX_DATA_RATE__BIT__34000				0x0002
#define DM_K56FLEX_DATA_RATE__BIT__36000				0x0004
#define DM_K56FLEX_DATA_RATE__BIT__38000				0x0008
#define DM_K56FLEX_DATA_RATE__BIT__40000				0x0010
#define DM_K56FLEX_DATA_RATE__BIT__42000				0x0020
#define DM_K56FLEX_DATA_RATE__BIT__44000				0x0040
#define DM_K56FLEX_DATA_RATE__BIT__46000				0x0080
#define DM_K56FLEX_DATA_RATE__BIT__48000				0x0100
#define DM_K56FLEX_DATA_RATE__BIT__50000				0x0200
#define DM_K56FLEX_DATA_RATE__BIT__52000				0x0400
#define DM_K56FLEX_DATA_RATE__BIT__54000				0x0800
#define DM_K56FLEX_DATA_RATE__BIT__56000				0x1000

#define DM_K56FLEX_ALL_DATA_RATE__32000					0x0003
#define DM_K56FLEX_ALL_DATA_RATE__34000					0x0007
#define DM_K56FLEX_ALL_DATA_RATE__36000					0x000f
#define DM_K56FLEX_ALL_DATA_RATE__38000					0x001f
#define DM_K56FLEX_ALL_DATA_RATE__40000					0x003f
#define DM_K56FLEX_ALL_DATA_RATE__42000					0x007f
#define DM_K56FLEX_ALL_DATA_RATE__44000					0x00ff
#define DM_K56FLEX_ALL_DATA_RATE__46000					0x01ff
#define DM_K56FLEX_ALL_DATA_RATE__48000					0x03ff
#define DM_K56FLEX_ALL_DATA_RATE__50000					0x07ff
#define DM_K56FLEX_ALL_DATA_RATE__52000					0x0fff
#define DM_K56FLEX_ALL_DATA_RATE__54000					0x1fff
#define DM_K56FLEX_ALL_DATA_RATE__56000					0x3fff

/* ************************************************************************* */

#define DM_V90_DATA_RATE__BIT__28000					0x00000001
#define DM_V90_DATA_RATE__BIT__29333					0x00000002
#define DM_V90_DATA_RATE__BIT__30666					0x00000004
#define DM_V90_DATA_RATE__BIT__32000					0x00000008
#define DM_V90_DATA_RATE__BIT__33333					0x00000010
#define DM_V90_DATA_RATE__BIT__34666					0x00000020
#define DM_V90_DATA_RATE__BIT__36000					0x00000040
#define DM_V90_DATA_RATE__BIT__37333					0x00000080
#define DM_V90_DATA_RATE__BIT__38666					0x00000100
#define DM_V90_DATA_RATE__BIT__40000					0x00000200
#define DM_V90_DATA_RATE__BIT__41333					0x00000400
#define DM_V90_DATA_RATE__BIT__42666					0x00000800
#define DM_V90_DATA_RATE__BIT__44000					0x00001000
#define DM_V90_DATA_RATE__BIT__45333					0x00002000
#define DM_V90_DATA_RATE__BIT__46666					0x00004000
#define DM_V90_DATA_RATE__BIT__48000					0x00008000
#define DM_V90_DATA_RATE__BIT__49333					0x00010000
#define DM_V90_DATA_RATE__BIT__50666					0x00020000
#define DM_V90_DATA_RATE__BIT__52000					0x00040000
#define DM_V90_DATA_RATE__BIT__53333					0x00080000
#define DM_V90_DATA_RATE__BIT__54666					0x00100000
#define DM_V90_DATA_RATE__BIT__56000					0x00200000

#define DM_V90_ALL_DATA_RATE__28000						0x00000001
#define DM_V90_ALL_DATA_RATE__29333						0x00000003
#define DM_V90_ALL_DATA_RATE__30666						0x00000007
#define DM_V90_ALL_DATA_RATE__32000						0x0000000f
#define DM_V90_ALL_DATA_RATE__33333						0x0000001f
#define DM_V90_ALL_DATA_RATE__34666						0x0000003f
#define DM_V90_ALL_DATA_RATE__36000						0x0000007f
#define DM_V90_ALL_DATA_RATE__37333						0x000000ff
#define DM_V90_ALL_DATA_RATE__38666						0x000001ff
#define DM_V90_ALL_DATA_RATE__40000						0x000002ff
#define DM_V90_ALL_DATA_RATE__41333						0x000007ff
#define DM_V90_ALL_DATA_RATE__42666						0x00000fff
#define DM_V90_ALL_DATA_RATE__44000						0x00001fff
#define DM_V90_ALL_DATA_RATE__45333						0x00003fff
#define DM_V90_ALL_DATA_RATE__46666						0x00007fff
#define DM_V90_ALL_DATA_RATE__48000						0x0000ffff
#define DM_V90_ALL_DATA_RATE__49333						0x0001ffff
#define DM_V90_ALL_DATA_RATE__50666						0x0003ffff
#define DM_V90_ALL_DATA_RATE__52000						0x0007ffff
#define DM_V90_ALL_DATA_RATE__53333						0x000fffff
#define DM_V90_ALL_DATA_RATE__54666						0x001fffff
#define DM_V90_ALL_DATA_RATE__56000						0x003fffff

/* ************************************************************************* */

#define DM_V90_OPTION__BIT__3429_EN						0x0001
#define DM_V90_OPTION__BIT__16POINT_TRAIN_EN			0x0002
#define DM_V90_OPTION__BIT__16POINT_RENEG_EN			0x0004

#define DM_V92_OPTION__BIT__MOH_QC_FORCE				0x0010	/* 1 = Attempt QC after MOH    */
#define DM_V92_OPTION__BIT__PCM_UPSTREAM_EN				0x0020	/* 1 = Enable PCM upstream     */
#define DM_V92_OPTION__BIT__SH1_ON_RESET_EN				0x0040	/* 1 = Enable short ph1 1st	time */
#define DM_V92_OPTION__BIT__SH2_ON_RESET_EN				0x0040	/* 1 = Enable short ph1 1st	time */
#define DM_V92_OPTION__BIT__8POINT_TRAIN_EN				0x0100	/* 1 = Enable 8-point in ph4   */
#define DM_V92_OPTION__BIT__8POINT_RENEG_EN				0x0200	/* 1 = Enable 8-point in reneg */
#define DM_V92_OPTION__BIT__SHORT_PHASE_2_EN			0x0400	/* 1 = Enable short phase 2    */
#define DM_V92_OPTION__BIT__MODEM_ON_HOLD_EN			0x0800	/* 1 = Enable Modem on hold    */
#define DM_V92_OPTION__BIT__MOH_ACKNOWLEDGE_EN			0x1000	/* 1 = Grant a MOH request     */
#define DM_V92_OPTION__BIT__MOH_DENY_ACTION				0x2000	/* 1 = Reconnect if MOH denied */
#define DM_V92_OPTION__BIT__MOH_DENY_STATUS				0x4000	/* 1 = Deny all MOH requests   */
#define DM_V92_OPTION__BIT__USR_DETECT					0x8000	/* 1 = Allow USR client detect */

#define DM_V92_STATUS__BIT__SH2_REMOTE					0x0001	/* remote requested short ph2      */
#define DM_V92_STATUS__BIT__V92_REMOTE					0x0002	/* remote V92 capability           */
#define DM_V92_STATUS__BIT__SH2_NEGOTD					0x0004	/* modems negotiated short ph2     */
#define DM_V92_STATUS__BIT__V92_NEGOTD					0x0008	/* modems both have V92 capability */
#define DM_V92_STATUS__BIT__SH1_REMOTE					0x0010	/* remote requested  short ph1     */
#define DM_V92_STATUS__BIT__SH1_NEGOTD					0x0020 	/* modems negotiated short ph1     */
#define DM_V92_STATUS__BIT__PCM_REMOTE					0x0040	/* remote requested  pcm upstream  */
#define DM_V92_STATUS__BIT__PCM_NEGOTD					0x0080 	/* modems negotiated pcm upstream  */

/* ************************************************************************* */

#define DM_V90_SHAPING_LOOKAHEAD__1						0x0001
#define DM_V90_SHAPING_LOOKAHEAD__2						0x0002
#define DM_V90_SHAPING_LOOKAHEAD__3						0x0003

/* ************************************************************************* */

#define FXPMP__CNG_GEN_ENABLE							0x0001
#define FXPMP__CNG_DET_ENABLE							0x0002

#define FXPMP__CED_GEN_ENABLE							0x0004
#define FXPMP__CED_DET_ENABLE							0x0008

/* ************************************************************************* */

#define RDLB__BIT__OVERALL_EN							0x0001
#define RDLB__BIT__AUTO_ACK_EN							0x0002

#define RDLB_STATE__RESET								0x0000
#define RDLB_STATE__INACTIVE							0x0001
#define RDLB_STATE__IDLE								0x0002
#define RDLB_STATE__MANUAL_LOOP2						0x0003
#define RDLB_STATE__AUTO_LOOP2							0x0004
#define RDLB_STATE__PRE_REMOTE_LOOP2					0x0005
#define RDLB_STATE__REMOTE_LOOP2						0x0006
#define RDLB_STATE__POST_REMOTE_LOOP2					0x0007

/* ************************************************************************* */

#define V13_STAT__CIRCUIT_105							0x0001
#define V13_STAT__CIRCUIT_109							0x0002

/* ************************************************************************* */

#endif /* _INCLUDE_DM_H */
