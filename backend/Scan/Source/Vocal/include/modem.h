
/* ************************************************************************* */
/*
 *	modem.h
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
 *	This header file contains modem related symbol definitions.
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

#ifndef _INCLUDE_MODEM_H
#define _INCLUDE_MODEM_H

/* ************************************************************************* */

/* The values of symbols BR__75 to BR__33600 and BR__MASK will not change. */

#define BR__MASK	0x00ff

#define BR__75		0x0000
#define BR__300		0x0001
#define BR__600		0x0002
#define BR__1200	0x0003

#define BR__2400	0x0004			/* Matches V.32/V.34 data rate codes */
#define BR__4800	0x0005
#define BR__7200	0x0006
#define BR__9600	0x0007
#define BR__12000	0x0008
#define BR__14400	0x0009
#define BR__16800	0x000a
#define BR__19200	0x000b
#define BR__21600	0x000c
#define BR__24000	0x000d
#define BR__26400	0x000e
#define BR__28800	0x000f
#define BR__31200	0x0010
#define BR__33600	0x0011

#define BR__V92_24000	0x0012		/* Matches V.92 data rate codes */
#define BR__V92_25333	0x0013
#define BR__V92_26667	0x0014

#define BR__V90_28000	0x0015		/* Matches V.90/V.92 data rate codes */
#define BR__V90_29333	0x0016
#define BR__V90_30667	0x0017
#define BR__V90_32000	0x0018
#define BR__V90_33333	0x0019
#define BR__V90_34667	0x001a
#define BR__V90_36000	0x001b
#define BR__V90_37333	0x001c
#define BR__V90_38667	0x001d
#define BR__V90_40000	0x001e
#define BR__V90_41333	0x001f
#define BR__V90_42667	0x0020
#define BR__V90_44000	0x0021
#define BR__V90_45333	0x0022
#define BR__V90_46667	0x0023
#define BR__V90_48000	0x0024
#define BR__V90_49333	0x0025
#define BR__V90_50667	0x0026
#define BR__V90_52000	0x0027
#define BR__V90_53333	0x0028
#define BR__V90_54667	0x0029
#define BR__V90_56000	0x002a

#define BR__V90_57333	0x002b		/* V.90 all digital mode extension */
#define BR__V90_58667	0x002c
#define BR__V90_60000	0x002d
#define BR__V90_61333	0x002e
#define BR__V90_62667	0x002f
#define BR__V90_64000	0x0030

#define BR__K56_32000	0x0031		/* K56Flex data rate codes */
#define BR__K56_34000	0x0032
#define BR__K56_36000	0x0033
#define BR__K56_38000	0x0034
#define BR__K56_40000	0x0035
#define BR__K56_42000	0x0036
#define BR__K56_44000	0x0037
#define BR__K56_46000	0x0038
#define BR__K56_48000	0x0039
#define BR__K56_50000	0x003a
#define BR__K56_52000	0x003b
#define BR__K56_54000	0x003c
#define BR__K56_56000	0x003d
#define BR__K56_58000	0x003e
#define BR__K56_60000	0x003f

#define BR__57600	0x0041
#define BR__115200	0x0042
#define BR__230400	0x0043
#define BR__50		0x0044
#define BR__110		0x0045
#define BR__134		0x0046
#define BR__150		0x0047
#define BR__1800	0x0048
#define BR__2000	0x0049
#define BR__3600	0x004a
#define BR__11520	0x004b
#define BR__23040	0x004c
#define BR__36000	0x004d
#define BR__38400	0x004e

#define BR__43200	0x007e
#define BR__48000	0x007f
#define BR__56000	0x0080
#define BR__64000	0x0081
#define BR__128000	0x0082
#define BR__8000	0x0083
#define BR__16000	0x0084
#define BR__32000	0x0085

#define BR__DEFAULT	0x00ff

/* ************************************************************************* */

#define OMC_REASON__NULL								0x0000

#define OMC_REASON__OMC_NORMAL_LOCAL					0x0001
#define OMC_REASON__OMC_NORMAL_REMOTE					0x0002
#define OMC_REASON__OMC_INACTIVITY						0x0003
#define OMC_REASON__OMC_CIRCUIT_LOSS					0x0004
#define OMC_REASON__OMC_HALTED							0x0005
#define OMC_REASON__OMC_DM_TIMEOUT						0x0006
#define OMC_REASON__OMC_DP_TIMEOUT						0x0007
#define OMC_REASON__OMC_IMPROPER_CONTROL				0x0008
#define OMC_REASON__OMC_FAX_DETECTED					0x0009
#define OMC_REASON__OMC_DM_CLEARDOWN					0x000A
#define OMC_REASON__OMC_CALL_FUNCTION_UNSUPPORTED		0x000B
#define OMC_REASON__OMC_T30_SESSION						0x000C
#define OMC_REASON__OMC_FX1_SESSION						0x000D

#define OMC_REASON__DM_NORMAL_LOCAL						0x0041
#define OMC_REASON__DM_NORMAL_REMOTE					0x0042
#define OMC_REASON__DM_HALTED							0x0043
#define OMC_REASON__DM_CARRIER_LOSS						0x0044
#define OMC_REASON__DM_NEGOTIATION_REQUIREMENT_FAIL		0x0045
#define OMC_REASON__DM_GENERAL_REQUIREMENT_FAIL			0x0046
#define OMC_REASON__DM_PROTOCOL_FAIL					0x0047
#define OMC_REASON__DM_GENERAL							0x0048

#define OMC_REASON__DP_NORMAL_LOCAL						0x0081
#define OMC_REASON__DP_NORMAL_REMOTE					0x0082
#define OMC_REASON__DP_HALTED							0x0083
#define OMC_REASON__DP_NEGOTIATION_REQUIREMENT_FAIL		0x0084
#define OMC_REASON__DP_GENERAL_REQUIREMENT_FAIL			0x0085
#define OMC_REASON__DP_PROTOCOL_FAIL					0x0086
#define OMC_REASON__DP_COMPRESSION_PROTOCOL_FAIL		0x0087
#define OMC_REASON__DP_GENERAL							0x0088
#define OMC_REASON__DP_NO_RESPONSE						0x0089
#define OMC_REASON__DP_STARTUP_FAIL						0x008A
#define OMC_REASON__DP_TIMEOUT							0x008B

#define OMC_REASON__DIAL_NO_DIALTONE					0x00c0
#define OMC_REASON__DIAL_BUSY							0x00c1
#define OMC_REASON__DIAL_NO_ANSWER						0x00c2
#define OMC_REASON__DIAL_DELAYED						0x00c3
#define OMC_REASON__DIAL_RRING_NO_ANSWER				0x00c4
#define OMC_REASON__DIAL_RRING_CEASED					0x00c5
#define OMC_REASON__DIAL_NO_LOOP_CURRENT				0x00c6
#define OMC_REASON__DIAL_BLACKLISTED					0x00c7
#define OMC_REASON__DIAL_NO_CARRIER						0x00c8

#define OMC_REASON__LOCKUP_STATUS_PTR_INTEGRITY			0x8000
#define OMC_REASON__LOCKUP_STATUS_PTR_DESYNC			0x8001
#define OMC_REASON__LOCKUP_DSPIF_ANOMALY				0x8002
#define OMC_REASON__LOCKUP_TEL_STARTUP_TIMEOUT			0x8003
#define OMC_REASON__LOCKUP_V42_ENC						0x8004
#define OMC_REASON__LOCKUP_V42_DEC						0x8005

/* Notice that the below symbols are redefined as above symbols */

#define OMC_REASON__DP_INACTIVITY						OMC_REASON__OMC_INACTIVITY

/* ************************************************************************* */

#define OMC_STATE__RESET								0x0000
#define OMC_STATE__IDLE									0x0001
#define OMC_STATE__OFF_HOOK								0x0002
#define OMC_STATE__DIALING								0x0003
#define OMC_STATE__POST_DIAL							0x0004
#define OMC_STATE__FAX_DETECTED							0x0005
#define OMC_STATE__DM_CONNECTING						0x0006
#define OMC_STATE__DP_CONNECTING						0x0007
#define OMC_STATE__DATA_CONNECT							0x0008
#define OMC_STATE__DP_DISCONNECTING						0x0009
#define OMC_STATE__DM_DISCONNECTING						0x000a
#define OMC_STATE__PRE_ON_HOOK							0x000b
#define OMC_STATE__FX1									0x000c
#define OMC_STATE__T30									0x000d
#define OMC_STATE__T30_VOICE							0x000e
#define OMC_STATE__DP_IDLE								0x000f
#define OMC_STATE__RETRAIN								0x0010
#define OMC_STATE__RENEGOTIATE							0x0011
#define OMC_STATE__TEST									0x0012
#define OMC_STATE__LOOPBACK								0x0013

/* ************************************************************************* */

#define MDM_ERRORCODE__NO_ERROR							0
#define MDM_ERRORCODE__GENERAL							1
#define MDM_ERRORCODE__SYSTEM_INITIALIZATION			2
#define MDM_ERRORCODE__HARDWARE_RESET_FAILURE			3
#define MDM_ERRORCODE__HARDWARE_TIMEOUT					4
#define MDM_ERRORCODE__DSP_TIMER_FAILURE				5
#define MDM_ERRORCODE__DSPDRV_SETUP						6
#define MDM_ERRORCODE__DSPDRV_STARTUP					7
#define MDM_ERRORCODE__DTEIF_SETUP						8
#define MDM_ERRORCODE__DTEIF_STARTUP					9
#define MDM_ERRORCODE__DIAGNOSTIC_STARTUP				10

#define MDM_ERRORCODE__RESERVED__20						20
#define MDM_ERRORCODE__RESERVED__21						21

#define MDM_ERRORCODE__RESERVED__22						22

#define MDM_ERRORCODE__RESERVED__35						35
#define MDM_ERRORCODE__RESERVED__36						36

#define MDM_ERRORCODE__RESERVED__23						23

#define MDM_ERRORCODE__INSUFFICIENT_MEMORY				30
#define MDM_ERRORCODE__DEVICE_NOT_OPEN					31
#define MDM_ERRORCODE__DEVICE_NUMBER_OUT_OF_RANGE		32
#define MDM_ERRORCODE__SYSTEM_CONFIGURATION				33
#define MDM_ERRORCODE__CTRL_BREAK_SEEN					34
#define MDM_ERRORCODE__DINT_INPUT_FILE_ERROR			35
#define MDM_ERRORCODE__DINT_WRITE_FILE_ERROR			36

#define MDM_ERRORCODE__SHUTDOWN							50

#define MDM_ERRORCODE__NETWORK_NOT_STARTED				100
#define MDM_ERRORCODE__NETWORK_TASK_CREATE_FAILED		101
#define MDM_ERRORCODE__NETWORK_INIT_FAILED				102

/* ************************************************************************* */

#define TELEPHONY_FEATURE__BIT__RING_DETECT					0x0001
#define TELEPHONY_FEATURE__BIT__CALLER_ID					0x0002
#define TELEPHONY_FEATURE__BIT__V8BIS						0x0004
#define TELEPHONY_FEATURE__BIT__MODULATION_TEST				0x0008
#define TELEPHONY_FEATURE__BIT__TONE_DETECTORS				0x0010
#define TELEPHONY_FEATURE__BIT__SPEAKERPHONE				0x0020
#define TELEPHONY_FEATURE__BIT__OMC_OFF_HOOK_IDLE_PASS_THRU	0x0040
#define TELEPHONY_FEATURE__BIT__OMC_ON_HOOK_IDLE_PASS_THRU	0x0080

#define NTELEPHONY_FEATURE__BIT__OMC_OFF_HOOK_IDLE_PASS_THRU	0xffbf
#define NTELEPHONY_FEATURE__BIT__OMC_ON_HOOK_IDLE_PASS_THRU		0xff7f

/* ************************************************************************* */
#define PUMP_TRANSMIT_LEVEL_DEFAULT						0x4000

/* ************************************************************************* */

#define ITEL_DEFAULT_COUNTRY_CODE						ICC__UNITED_STATES;

/* ************************************************************************* */

/* Below symbols are always guaranteed to be in ascending numeric order */
#define SPK_MON__NEVER									0
#define SPK_MON__CONNECT								10
#define SPK_MON__TRAIN									20
#define SPK_MON__DATA_FAX								30
#define SPK_MON__OFF_HOOK								40
#define SPK_MON__ALWAYS									50

/* ************************************************************************* */

#define TONE_GEN_SAMPLE_RATE							8000

/* ************************************************************************* */

/* Both versions of below values should be identical, except for the quotes */
#define TONE_GEN_MIN_FREQ								200
#define S_TONE_GEN_MIN_FREQ								"200"
#define TONE_GEN_MAX_FREQ								3300
#define S_TONE_GEN_MAX_FREQ								"3300"
#define TONE_GEN_MAX_DUR								1000
#define S_TONE_GEN_MAX_DUR								"1000"

#define TONE_GEN_SAMPLE_RATE							8000

/* ************************************************************************* */

#define DIAL_FAX_MODE__BIT__CED_DETECT					0x0001
#define DIAL_FAX_MODE__BIT__V21_DETECT					0x0002
#define DIAL_FAX_MODE__BIT__CNG_GEN						0x0008

/* ************************************************************************* */

#endif /* _INCLUDE_MODEM_H */
