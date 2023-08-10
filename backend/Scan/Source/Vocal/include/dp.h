
/* ************************************************************************* */
/*
 *	dp.h
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
 *	This header file contains data protocol related symbol definitions.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 19:50:34  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _INCLUDE_DP_H
#define _INCLUDE_DP_H

/* ************************************************************************* */

#define DP_PROTOCOL__BIT__NONE							0x0000
#define DP_PROTOCOL__BIT__LAPM							0x0001
#define DP_PROTOCOL__BIT__MNP							0x0002
#define DP_PROTOCOL__BIT__BUFFERED						0x0004
#define DP_PROTOCOL__BIT__DIRECT						0x0008
#define DP_PROTOCOL__BIT__CELLULAR						0x0010
#define DP_PROTOCOL__BIT__HIGH_SPEED_RELIABLE			0x0100
#define DP_PROTOCOL__BIT__V120							0x0200

/* ************************************************************************* */

#define DP_COMPRESSION__NONE							0x0000
#define DP_COMPRESSION__V42BIS							0x0001
#define DP_COMPRESSION__MNP5							0x0002

/* ************************************************************************* */

#define DP_AUTOSELECT__BIT__NONE						0x0000
#define DP_AUTOSELECT__BIT__V42_DETECT					0x0001
#define DP_AUTOSELECT__BIT__MNP_AUTORELIABLE			0x0002

/* ************************************************************************* */

#define DP_COMP_MODE_TX__BF__MASK						0x000f
#define DP_COMP_MODE_TX__BF__OFF						0x0000
#define DP_COMP_MODE_TX__BF__ACK_ONLY					0x0001
#define DP_COMP_MODE_TX__BF__REQUESTED					0x0002
#define DP_COMP_MODE_TX__BF__REQUIRED					0x0003
#define DP_COMP_MODE_RX__BF__MASK						0x00f0
#define DP_COMP_MODE_RX__BF__OFF						0x0000
#define DP_COMP_MODE_RX__BF__ACK_ONLY					0x0010
#define DP_COMP_MODE_RX__BF__REQUESTED					0x0020
#define DP_COMP_MODE_RX__BF__REQUIRED					0x0030
#define DP_COMP_TYPE__BIT__V42BIS						0x0100
#define DP_COMP_TYPE__BIT__MNP5							0x0200

/* The value of symbols DP_COMPRESSION__xxx will not change. */
#define DP_COMPRESSION__BIT__NULL						0x0000
#define DP_COMPRESSION__BIT__TX							0x0001
#define DP_COMPRESSION__BIT__RX							0x0002

/* ************************************************************************* */

#define DP_MNP_BTLZ__BIT__XID_PROPOSE_EN				0x0001
#define DP_MNP_BTLZ__BIT__XID_NEGO_EN					0x0002
#define DP_MNP_BTLZ__BIT__LR_PROPOSE_EN					0x0004
#define DP_MNP_BTLZ__BIT__LR_NEGO_EN					0x0008
#define DP_LAPM_MNP__BIT__XID_PROPOSE_EN				0x0010
#define DP_LAPM_MNP__BIT__XID_NEGO_EN					0x0020
#define DP_LAPM_MNP__BIT__BTLZ_RQD						0x0100
#define DP_LAPM_MNP__BIT__MNP10_RQD						0x0200
#define DP_LAPM_MNP__BIT__MNP10EC_RQD					0x0400

/* ************************************************************************* */

#define DP_CELLULAR_EN__BF__MASK						0x0003
#define DP_CELLULAR_EN__BF__OFF							0x0000
#define DP_CELLULAR_EN__BF__ACK_ONLY					0x0001
#define DP_CELLULAR_EN__BF__REQUESTED					0x0002
#define DP_CELLULAR_EN__BF__REQUIRED					0x0003
#define DP_CELLULAR__BIT__MNP10							0x0010
#define DP_CELLULAR__BIT__ETC							0x0020

/* ************************************************************************* */

#define DP_CELLULAR__NONE								0x0000
#define DP_CELLULAR__MNP5								0x0001
#define DP_CELLULAR__ETC								0x0002

/* ************************************************************************* */

#define DP_MNP10__BIT__XID_PROPOSE_EN					0x0001
#define DP_MNP10__BIT__XID_NEGO_EN						0x0002
#define DP_MNP10__BIT__LR_PROPOSE_EN					0x0004
#define DP_MNP10__BIT__LR_NEGO_EN						0x0008
#define DP_MNP10__BIT__ENHANCED_CELLULAR_EN				0x0010

/* ************************************************************************* */

#define DP_MNP10_TX_ADJUST__BF__MASK					0x0003
#define DP_MNP10_TX_ADJUST__BF__OFF						0x0000
#define DP_MNP10_TX_ADJUST__BF__CONDITIONAL				0x0001
#define DP_MNP10_TX_ADJUST__BF__UNCONDITIONAL			0x0002

/* ************************************************************************* */

#define DP_MNP10_LINK_NEGO_SPEED__HIGHEST				0x0001
#define DP_MNP10_LINK_NEGO_SPEED__V22					0x0002
#define DP_MNP10_LINK_NEGO_SPEED__4800					0x0003

/* ************************************************************************* */

#define DP_MNP10_STATUS__BIT__MNP10_ACTIVE				0x0001
#define DP_MNP10_STATUS__BIT__ENHANCED_CELLULAR_ACTIVE	0x0002
#define DP_MNP10_STATUS__BIT__REMOTE_TX_ADJUST_ACTIVE	0x0004
#define DP_MNP10_STATUS__BIT__LOCAL_TX_ADJUST_ACTIVE	0x0008

/* ************************************************************************* */

#define DP_INACTIVITY__BIT__TX							0x0001
#define DP_INACTIVITY__BIT__RX							0x0002
#define DP_INACTIVITY__BIT__RX_EC						0x0004

/* ************************************************************************* */

#define DP_BREAK__IGNORE								0x0000
#define DP_BREAK__DESTRUCTIVE							0x0001
#define DP_BREAK__EXPEDITED								0x0002
#define DP_BREAK__SEQUENCED								0x0003

/* ************************************************************************* */

#define DP_DIRECT_SBD__BIT__EN							0x0001
#define DP_DIRECT_SBD__BF__MASK							0x0002
#define DP_DIRECT_SBD__BF__1_OF_8						0x0000
#define DP_DIRECT_SBD__BF__1_OF_4						0x0002

/* ************************************************************************* */

#define DP_BUFFERED_FC__BIT__NONE						0x0000
#define DP_BUFFERED_FC__BIT__ENABLE						0x0001
#define DP_BUFFERED_FC__BIT__PASS_THROUGH				0x0002
#define DP_BUFFERED_FC__BIT__FORCE_SEVEN_BIT_COMPARES	0x0004

/* ************************************************************************* */

/* The value of symbol DP_LAPM_SREJ__OFF will not change. */
/* The value of symbol DP_LAPM_SREJ__ON will not change. */
#define DP_LAPM_SREJ__OFF								0x0000
#define DP_LAPM_SREJ__REQUESTED							0x0001
#define DP_LAPM_SREJ__REQUIRED							0x0002
#define DP_LAPM_SREJ__ON								0x0001

/* ************************************************************************* */

/* The value of symbol DP_LAPM_TEST__OFF will not change. */
/* The value of symbol DP_LAPM_TEST__EN will not change. */
#define DP_LAPM_TEST__OFF								0x0000
#define DP_LAPM_TEST__EN								0x0001

/* ************************************************************************* */

/* The value of symbol DP_LAPM_FCS__16_BIT will not change. */
/* The value of symbol DP_LAPM_FCS__32_BIT will not change. */
#define DP_LAPM_FCS__16_BIT								0x0000
#define DP_LAPM_FCS__32_BIT_REQUESTED					0x0001
#define DP_LAPM_FCS__32_BIT_REQUIRED					0x0002
#define DP_LAPM_FCS__32_BIT								0x0001

/* ************************************************************************* */

#define DP_MNP_LEVEL__MINIMAL_SERVICE					0x0001
#define DP_MNP_LEVEL__STANDARD_SERVICE					0x0002

/* ************************************************************************* */

#define DP_MNP_CLASS__1_CREDIT							0x0001
#define DP_MNP_CLASS__FULL_ASYNC						0x0002
#define DP_MNP_CLASS__FULL_SYNC							0x0003

/* ************************************************************************* */

#define DP_MNP_MAX_SIZE__64								64
#define DP_MNP_MAX_SIZE__128							128
#define DP_MNP_MAX_SIZE__192							192
#define DP_MNP_MAX_SIZE__256							256

/* ************************************************************************* */

#define DP_MNP_COMPRESSION__MNP5_ONLY					0x0000
#define DP_MNP_COMPRESSION__MNP5_BTLZ_ACK_ONLY			0x0001
#define DP_MNP_COMPRESSION__BTLZ_REQUESTED				0x0002
#define DP_MNP_COMPRESSION__BTLZ_REQUIRED				0x0003

/* ************************************************************************* */

#define DP_AUTOREL__BIT__TIMER_EN						0x0001
#define DP_AUTOREL__BIT__200_CHAR_BUFFER_EN				0x0002
#define DP_AUTOREL__BIT__CHARACTER_EN					0x0004
#define DP_AUTOREL__BIT__7_BIT_COMPARES					0x0008

/* ************************************************************************* */

#define DP_DISC_MGMNT_TX__BF__MASK						0x0003
#define DP_DISC_MGMNT_TX__BF__ABANDON					0x0000
#define DP_DISC_MGMNT_TX__BF__FOREVER					0x0001
#define DP_DISC_MGMNT_TX__BF__TIMED						0x0002
#define DP_DISC_MGMNT_RX__BF__MASK						0x000c
#define DP_DISC_MGMNT_RX__BF__ABANDON					0x0000
#define DP_DISC_MGMNT_RX__BF__FOREVER					0x0004
#define DP_DISC_MGMNT_RX__BF__TIMED						0x0008

/* ************************************************************************* */

#define DP_LAPM_DEFAULT_TX_WINDOW_SIZE					LAPM_NUMBER_TX_BUFFERS
#define DP_LAPM_DEFAULT_RX_WINDOW_SIZE					LAPM_NUMBER_RX_BUFFERS
#define DP_LAPM_DEFAULT_N401							CMD_I_INFO_MAX

/* ************************************************************************* */

/* The value of symbol DP_SYNC_CODE__INACTIVE will not change. */
#define DP_SYNC_CODE__INACTIVE							0x0000
#define DP_SYNC_CODE__NORMAL_STARTUP					0x0001
#define DP_SYNC_CODE__NON_LAPM_SYNC_DETECT				0x0002

/* ************************************************************************* */

#define DP_STATUS__HALTED					0  /* status while halted */
#define DP_STATUS__CONNECTING				1  /* status while connecting */
#define DP_STATUS__IDLE						2  /* status while idle */
#define DP_STATUS__SUSPEND					3  /* status while suspeded */
#define DP_STATUS__MNP						4  /* status while in MNP */
#define DP_STATUS__DISCONNECTING			5  /* status while disconnecting */
#define DP_STATUS__BUFFERED					6  /* status while in buffered */
#define DP_STATUS__LAPM						7  /* status while in LAPM */
#define DP_STATUS__DIRECT					8  /* status while in direct */
#define DP_STATUS__RUNNING					9  /* status while in any DP */
#define DP_STATUS__STARTUP					10 /* prev_status init to this */
#define DP_STATUS__NEGO_FAILURE				11 /* mnp, lapm, buffered */
#define DP_STATUS__LOAD_COMPRESSION			12 /* used to load in the compression overlays */
#define DP_STATUS__DET_AUTOREL_NEXT_STATE	13 /* detect or autoreliable next state */
#define DP_STATUS__STARTUP_FAILURE			14 /* startup failure will shutdown the dp state machine */
#define DP_STATUS__DETECT					15 /* idle state of detect until a real protocol is started */
#define DP_STATUS__V120						16 /* status while in V.120 */
#define DP_STATUS__INTERNAL_ERROR			99 /* error in state machine */

/* ************************************************************************* */
/* BTLZ dictionary size and string length */

#define DP_BTLZ_P1__MIN				512		/* minimum of BTLZ_P1 */

#define DP_BTLZ_P1__MAX				1024	/* maximim of BTLZ_P1 */

#define DP_BTLZ_P2__MIN				6		/* minimum of BTLZ_P2 */

#define DP_BTLZ_P2__MAX				250		/* maximum of BTLZ_P2 */

/* ************************************************************************* */

#define V120_MODE_FRAMING__BF__MASK			0x03
#define V120_MODE_FRAMING__BF__NONE			0x00
#define V120_MODE_FRAMING__BF__SYNC			0x01
#define V120_MODE_FRAMING__BF__ASYNC		0x02
#define V120_MODE__BIT__ECM_ON				0x04

/* ************************************************************************* */

#define	LAPF_AUTOSTART__BIT__SABME_CMD_EN			0x0001
#define LAPF_AUTOSTART__BIT__SABME_RSP_EN			0x0002
#define LAPF_AUTOSTART__BIT__SABME_TIMEOUT_EN		0x0004
#define LAPF_AUTOSTART__BIT__UNACK_MODE_PERMITTED	0x0008
#define LAPF_AUTOSTART__BIT__EC_MODE_PERMITTED		0x0010
#define LAPF_AUTOSTART__BIT__HALT_UPON_DM			0x0020

/* ************************************************************************* */

#define DP_DIG_DET__BIT__ENABLE							0x0001
#define DP_DIG_DET__BIT__V120_TRANS_EN					0x0002

#define DP_DIG_DET_PROT__NONE							0
#define DP_DIG_DET_PROT__TIMEOUT						1
#define DP_DIG_DET_PROT__OTHER							2
#define DP_DIG_DET_PROT__V120							3
#define DP_DIG_DET_PROT__SYNC_PPP						4
#define DP_DIG_DET_PROT__LAPB							5

/* ************************************************************************* */

/* ************************************************************************* */

#endif /* _INCLUDE_DP_H */
