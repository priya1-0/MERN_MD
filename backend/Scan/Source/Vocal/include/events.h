
/* ************************************************************************* */
/*
 *	events.h
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
 *	Define event types and specific codes.
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

#ifndef _INCLUDE_EVENTS_H
#define _INCLUDE_EVENTS_H

/* ************************************************************************* */
/*
 *	Define event/status types and mask
 *
 *	Bits 14 and 13 of the event/status type are used in the following combinations
 *
 *	14	13	Produced by				Used by					Notes
 *	0	0	Pump/Controller/Host	Pump					Only these events are routed from controller to pump
 *	0	1	Pump					Pump/Controller/Host
 *	1	0	Pump/Controller			Controller/Host			Status codes with associated data
 *	1	1	Controller/Host			Controller/Host
 *
 */
#define EVENT__MASK								0x07ff	/* Event numbers unique by this mask only! */

#define ET__INHIBIT								0x0800	/* Inhibitable events */
#define ET__API									0x1000	/* Minimal event reports */
#define ET__REPORT								0x2000	/* Normal event reports */
#define ET__COMMAND								0x4000	/* Set for controller only events */
#define ET__PERIODIC							0x8000	/* Periodic event reports */

#define ET__FOREGROUND							0x4000	/* Cleared for foreground events */
#define ET__BACKGROUND							0x6000	/* Set for background events */

#define ET__NNS									0x8000	/* No new state coding indication */

/* ************************************************************************* */
/*
 *	Define recommended event blocks
 *
 */
#define EVENT_BLOCK__PUMP_1						0x0000
#define EVENT_BLOCK__PUMP_2						0x0100
#define EVENT_BLOCK__TIMERS						0x0200
#define EVENT_BLOCK__INTERNAL					0x0158	/* Was 0x0300 */

#define EVENT_BLOCK__BACKGROUND					0x0400
#define EVENT_BLOCK__SPARE						0x0500

#define EVENT_BLOCK__ISDN						0x0600
#define EVENT_BLOCK__CUSTOMER					0x0700

/* ************************************************************************* */
/*
 *	Define system events
 *
 */
#define EVENT__NULL								0x000
#define EVENT__FG_ENABLE						0x001
/*#define EVENT__TIMER_TICK						0x002 + ET__PERIODIC*/
#define EVENT__TIMER_TICK						0x002 + ET__REPORT
#define EVENT__MAILBOX_PROCESSOR_START			0x003 + ET__REPORT + ET__API

#define EVENT__PROCESSOR_POWERDOWN				0x004 + ET__INHIBIT
#define EVENT__PROCESSOR_RESTART				0x005 + ET__REPORT + ET__API
#define EVENT__PROCESSOR_WATCHDOG				0x006
#define EVENT__PROCESSOR_PROG_FLAG				0x007

#define EVENT__ENABLE_DSP						EVENT__FG_ENABLE
#define EVENT__BG_TIMER_TICK					EVENT__TIMER_TICK

/* ************************************************************************* */
/*
 *	Define line interface events
 *
 */
#define EVENT__SAMPLE_RATE_CONVERT				0x008
#define EVENT__SAMPLE_RATE_NORMAL				0x009
#define EVENT__RUN_U_LAW						0x00a
#define EVENT__RUN_A_LAW						0x00b
#define EVENT__RUN_LINEAR						0x00c
#define EVENT__RUN_TIMESLOT						0x00d
#define EVENT__BIT_REVERSE						0x00e
#define EVENT__BIT_NORMAL						0x00f

/* ************************************************************************* */
/*
 *	Define major pump events
 *
 */
#define EVENT__TRAIN_GO							0x010
#define EVENT__AUTOMODE_GO						0x011
#define EVENT__PRE_TRAIN_GO						0x012
#define EVENT__MODULATION_DETECT				0x013 + ET__REPORT
#define EVENT__MODULATION_NUDGE					0x014 + ET__REPORT
#define EVENT__STATISTICS_REPORT				0x015
#define EVENT__SAMPLE_BUFFER_OVERFLOW			0x016 + ET__REPORT + ET__API
#define EVENT__INTERRUPT_LOST					0x017 + ET__REPORT + ET__API

#define EVENT__CONNECTION_ON					0x018 + ET__REPORT + ET__API
#define EVENT__CONNECTION_OFF					0x019 + ET__REPORT + ET__API
#define EVENT__TONE_CHANGE						0x01a + ET__REPORT
#define EVENT__RLSD_ON							0x01b
#define EVENT__RLSD_OFF							0x01c
#define EVENT__DELTA_RLSD_ON					0x01d
#define EVENT__TONE_ON							0x01e + ET__REPORT
#define EVENT__TONE_OFF							0x01f + ET__REPORT

/* ************************************************************************* */
/*
 *	Define V.24 events
 *
 */
#define EVENT__V24_OFF							0x020 + ET__REPORT + ET__API

#define EVENT__CTS_ON							0x021 + ET__REPORT + ET__API
#define EVENT__CTS_OFF							0x022 + ET__REPORT + ET__API
#define EVENT__DCD_ON							0x023 + ET__REPORT + ET__API
#define EVENT__DCD_OFF							0x024 + ET__REPORT + ET__API
#define EVENT__DSR_ON							0x025 + ET__REPORT + ET__API
#define EVENT__DSR_OFF							0x026 + ET__REPORT + ET__API

#define EVENT__RTS_ON							0x027
#define EVENT__RTS_OFF							0x028
#define EVENT__DTR_ON							0x029
#define EVENT__DTR_OFF							0x02a

#define EVENT__PUMP_CTS_ON						EVENT__CTS_ON
#define EVENT__PUMP_DCD_ON						EVENT__DCD_ON
#define EVENT__PUMP_CTS_OFF						EVENT__CTS_OFF
#define EVENT__PUMP_DCD_OFF						EVENT__DCD_OFF

/* ************************************************************************* */
/*
 *	Define sample recording events
 *
 */
#define EVENT__RECORD_SAMPLE_START				0x02d
#define EVENT__RECORD_SAMPLE_STOP				0x02e
#define EVENT__RECORD_SAMPLE_OVERRUN			0x02f + ET__REPORT

/* ************************************************************************* */
/*
 *	Overlay events
 *
 */
#define EVENT__MODULE_TIMEOUT					0x030 + ET__REPORT + ET__API
#define EVENT__MODULE_UNLOAD					0x031 + ET__REPORT
#define EVENT__MODULE_DOWN						0x032 + ET__REPORT
#define EVENT__MODULE_LOAD						0x033 + ET__REPORT
#define EVENT__MODULE_UP						0x034 + ET__REPORT + ET__API
#define EVENT__MODULE_DONE						0x035 + ET__REPORT

/* ************************************************************************* */
/*
 *	Define modulation control events
 *
 */
#define EVENT__MODULATION_STOP					0x040
#define EVENT__CONNECT_ANSWER					0x041
#define EVENT__CONNECT_ORIGINATE				0x042
#define EVENT__TEST_ANSWER						0x043
#define EVENT__TEST_ORIGINATE					0x044
#define EVENT__FAX_MODE_GO						0x045
/* #define EVENT__FXPMP_CMD_ANSWER_START		0x046	*/
/* #define EVENT__FXPMP_CMD_ORIGINATE_START		0x047	*/
#define EVENT__INITIATE_CLEARDOWN				0x046
#define EVENT__CLEARDOWN_ACK					0x047 + ET__REPORT
#define EVENT__INITIATE_MOH						0x04a + ET__REPORT + ET__API
#define EVENT__TERMINATE_MOH					0x04b + ET__REPORT + ET__API

#define EVENT__FX_START_FR						0x04c + ET__REPORT
#define EVENT__FX_START_FT						0x04d + ET__REPORT
#define EVENT__FX_PREFAX_GO						0x04e + ET__REPORT
#define EVENT__FX_PREFAX_STOP					0x04f + ET__REPORT

#define EVENT__MODE_STOP						EVENT__MODULATION_STOP
#define EVENT__GO_ORIG_AUTOMODE					EVENT__CONNECT_ORIGINATE
#define EVENT__GO_ANSW_AUTOMODE					EVENT__CONNECT_ANSWER
#define EVENT__GO_ANSW_FIXED					EVENT__TEST_ANSWER
#define EVENT__GO_ORIG_FIXED					EVENT__TEST_ORIGINATE

/* ************************************************************************* */
/*
 *	Define telephony control events
 *
 */
#define EVENT__TELEPHONY_GO						0x050

#define EVENT__DETECT_RINGING					0x051
#define EVENT__DETECT_PRECISE_TONES				0x052
#define EVENT__DETECT_CALL_PROGRESS				0x053
/*efine EVENT__DETECT_DISCONNECT_TONE			0x310 */
#define EVENT__DETECT_STOP						0x054

#define EVENT__RING_ENERGY_OFF					0x048 + ET__REPORT
#define EVENT__RING_ENERGY_ON					0x049 + ET__REPORT

#define EVENT__DETECT_DTMF						0x055
#define EVENT__DETECT_DTMF_STOP					0x056
#define EVENT__DTMF_DETECTED					0x057 + ET__REPORT + ET__API

#define EVENT__OFF_HOOK							0x058
#define EVENT__ON_HOOK							0x059

#define EVENT__DTMF_DIAL						0x05a
#define EVENT__PULSE_DIAL						0x05b
#define EVENT__DIAL_DONE						0x05c + ET__REPORT + ET__API
#define EVENT__DTMF_CONTINUOUS					0x05d
#define EVENT__DTMF_STOP						0x05e

#define EVENT__TONE_GENERATOR					0x05f
#define EVENT__TONE_PATTERN						0x060
#define EVENT__TONE_STOP						EVENT__DTMF_STOP

#define EVENT__BONG_GENERATOR					0x02b
#define EVENT__PCM_PLAYBACK_START				0x0c7
#define EVENT__PCM_PLAYBACK_DONE  				0x0c8 + ET__REPORT + ET__API

#define EVENT__RINGING_DETECTED					0x061 + ET__REPORT + ET__API
#define EVENT__CALL_PROGRESS_TONE_CHANGE		0x062 + ET__REPORT

#define EVENT__DIALTONE_FOUND					0x063 + ET__REPORT + ET__API
#define EVENT__DIALTONE_LOST					0x064 + ET__REPORT + ET__API
#define EVENT__SILENCE_FOUND					0x065 + ET__REPORT + ET__API
#define EVENT__SILENCE_LOST						0x066 + ET__REPORT + ET__API
#define EVENT__BUSY_FOUND						0x067 + ET__REPORT + ET__API
#define EVENT__BUSY_LOST						0x068 + ET__REPORT + ET__API
#define EVENT__RRING_FOUND						0x069 + ET__REPORT + ET__API
#define EVENT__BONG_FOUND						0x06a + ET__REPORT + ET__API
#define EVENT__ANS_FOUND						0x06b + ET__REPORT + ET__API
#define EVENT__CED_FOUND						EVENT__ANS_FOUND
#define EVENT__CNG_FOUND						0x06c + ET__REPORT + ET__API
/*efine EVENT__DISCONNECT_TONE_FOUND			0x312 + ET__REPORT + ET__API */

#define EVENT__TELEPHONY_READY					0x06d + ET__REPORT + ET__API
#define EVENT__AM_CNG_DETECT					0x06e + ET__REPORT + ET__API

#define EVENT__CALL_PROGRESS_START				0x06f
/*efine EVENT__DISCONNECT_TONE_START			0x311 */

#define EVENT__PRODUCE_DTMF_TONE				EVENT__DTMF_DIAL
#define EVENT__DTMF_CONT						EVENT__DTMF_CONTINUOUS

#define EVENT__DETECT_MF_R2_FORWARD				0x036
#define EVENT__DETECT_MF_R2_BACKWARD			0x037
#define EVENT__DETECT_MF_STOP					0x038
#define EVENT__MF_DETECTED						0x039 + ET__REPORT + ET__API
#define EVENT__MF_DETECT_END					EVENT__DEVELOPER_GROUP + 0x00be
#define EVENT__DETECT_MF_R1						0x03b

#define EVENT__DETECT_MF_FORWARD				EVENT__DETECT_MF_R2_FORWARD
#define EVENT__DETECT_MF_BACKWARD				EVENT__DETECT_MF_R2_BACKWARD
#define EVENT__DETECT_MF_BELLCORE				EVENT__DETECT_MF_R1

#define EVENT__MF_TIMED							0x03a
#define EVENT__MF_CONTINUOUS					0x03d
#define EVENT__MF_STOP							0x03e

#define EVENT__NOISE_GENERATOR					0x03f
#define EVENT__NOISE_STOP						0x0cb

#define EVENT__CALLER_ID1_RCV					0x03c
#define EVENT__CALLER_ID_RECEIVED				0x03d + ET__REPORT + ET__API
#define EVENT__CALLER_ID1_GEN					0x04a
#define EVENT__CALLER_ID2_GEN					0x04b
#define EVENT__CALLER_ID_SHUTDOWN				0x02c + ET__REPORT

/* ************************************************************************* */
/*
 *	Define speech record/playback events
 *
 */
#define EVENT__SPEECH_ENCODE_START				0x070
#define EVENT__SPEECH_DECODE_START				0x071
#define EVENT__SPEECH_ENCODE_STOP				0x072
#define EVENT__SPEECH_DECODE_STOP				0x073

#define EVENT__SPEECH_GO						0x074
#define EVENT__SPEECH_READY						0x075 + ET__REPORT + ET__API

#define EVENT__SPEECH_MISSING_FRAME				0x076 + ET__REPORT + ET__API
#define EVENT__SPEECH_DECODER_RESET				0x077 + ET__REPORT + ET__API
#define EVENT__SPEECH_DECODER_TRANSITION		0x07b + ET__REPORT + ET__API
#define EVENT__SPEECH_DECODER_UNDERFLOW			0x07c + ET__REPORT + ET__API
#define EVENT__SPEECH_ENCODER_OVERRUN			0x07d + ET__REPORT + ET__API
#define EVENT__SPEECH_DECODER_UNDERRUN			EVENT__SPEECH_DECODER_UNDERFLOW

#define EVENT__SPEECH_GAIN_CHANGE				0x089

#define EVENT__SPEECH_TRANSCODE_START			0x08a
#define EVENT__SPEECH_TRANSCODE_STOP			0x08b

#define EVENT__SPEECH_ENC_PACKET_READY			0x08a + ET__REPORT + ET__API
#define EVENT__SPEECH_DEC_PACKET_READY			0x08b + ET__REPORT + ET__API

#define EVENT__SPEECH_SILENCE_DETECTED			0x08c + ET__REPORT + ET__API
#define EVENT__SPEECH_SPEECH_DETECTED			0x08d + ET__REPORT + ET__API

/* ************************************************************************* */
/*
 *	Define speakerphone control events
 *
 */
#define EVENT__SPEAKERPHONE_FDX					0x078
#define EVENT__SPEAKERPHONE_HDX					0x079
#define EVENT__SPEAKERPHONE_STOP				0x07a

#define EVENT__SPEAKER_MONITOR_ON				0x07e
#define EVENT__SPEAKER_MONITOR_OFF				0x07f

#define EVENT__G165_LEC_START					0x08e
#define EVENT__G165_LEC_STOP					0x08f

/* ************************************************************************* */
/*
 *	Define SART events
 *
 */
#define EVENT__TX_DATA_START					0x080
#define EVENT__RX_DATA_START					0x081
#define EVENT__TX_DATA_STOP						0x082
#define EVENT__RX_DATA_STOP						0x083

#define EVENT__TX_UNDERFLOW						0x084 + ET__REPORT + ET__INHIBIT
#define EVENT__RX_OVERFLOW						0x085 + ET__REPORT

#define EVENT__SART_NO_MORE_DATA				0x086 + ET__REPORT
#define EVENT__SART_RX_PROGRAM_DONE				0x087 + ET__REPORT
#define EVENT__SART_TX_PROGRAM_DONE				0x088 + ET__REPORT

/* ************************************************************************* */
/*
 *	Define digital loopback control events
 *
 */
#define EVENT__LOCAL_RDLB_REQUEST				0x090 + ET__REPORT
#define EVENT__REMOTE_RDLB_REQUEST				0x091 + ET__REPORT
#define EVENT__MANUAL_RDLB_REQUEST				0x092 + ET__REPORT
#define EVENT__STOP_RDLB_REQUEST				0x093 + ET__REPORT + ET__API
#define EVENT__V54_PREPARATORY_DETECT			0x094 + ET__REPORT
#define EVENT__V54_ACKNOWLEDGE_DETECT			0x095 + ET__REPORT
#define EVENT__V54_TERMINATION_DETECT			0x096 + ET__REPORT
#define EVENT__V54_1S_DETECT					0x097 + ET__REPORT
#define EVENT__V24_LOOP2_ON						0x098 + ET__REPORT
#define EVENT__V24_LOOP2_OFF					0x099 + ET__REPORT
#define EVENT__PUMP_CLOCKS_TO_RDLB_SETTING		0x09a + ET__REPORT
#define EVENT__PUMP_CLOCKS_TO_NORMAL_SETTING	0x09b + ET__REPORT
/*
 *	V.22/V.22bis loopback specific events
 *
 */
#define EVENT__PUMP_UNSCRAMBLER_REQUEST			0x09c + ET__REPORT
#define EVENT__PUMP_SCRAMBLER_REQUEST			0x09d + ET__REPORT
#define EVENT__PUMP_MUTE_REQUEST				0x09e + ET__REPORT
#define EVENT__PUMP_UNMUTE_REQUEST				0x09f + ET__REPORT
#define TIMER__RLSD								1
#define TIMER__RLSD1							1
#define TIMER__RLSD2							1

#define EVENT__LOCAL_LOOPBACK					0x09f
#define EVENT__LOOP2_CHANGE						0x09f + ET__REPORT

/* Temporal */
#define EVENT__LOOPBACK_TRANSMIT_INSTALL		0x0ae
#define EVENT__LOOPBACK_RECEIVE_INSTALL			0x0af
/* -------- */

/* ************************************************************************* */
/*
 *	Define facsimile control events
 *
 */
#define EVENT__FXPMP_CMD_ANSWER_START			0x0a0
#define EVENT__FXPMP_CMD_CNG_OFF				0x0a1
#define EVENT__FXPMP_CMD_CONTINUE				0x0a2
#define EVENT__FXPMP_CMD_DISCONNECT				0x0a3
#define EVENT__FXPMP_CMD_ESCAPE					0x0a4
#define EVENT__FXPMP_CMD_FRH					0x0a5
#define EVENT__FXPMP_CMD_FRM					0x0a6
#define EVENT__FXPMP_CMD_FTH					0x0a7
#define EVENT__FXPMP_CMD_FTM					0x0a8
#define EVENT__FXPMP_CMD_HALT					0x0a9
#define EVENT__FXPMP_CMD_ORIGINATE_START		0x0aa
#define EVENT__FXPMP_CMD_SIL_DET_OFF			0x0ab
#define EVENT__FXPMP_CMD_SIL_DET_ON				0x0ac
#define EVENT__FXPMP_CMD_FRV21					0x0ad
/*
 *	Define facsimile response events
 *
 */
#define EVENT__FXPMP_LINE_RX_BIN				0x0b0 + ET__REPORT + ET__API
#define EVENT__FXPMP_LINE_RX_HDLC				0x0b1 + ET__REPORT + ET__API
#define EVENT__FXPMP_LINE_TX_BIN				0x0b2 + ET__REPORT + ET__API
#define EVENT__FXPMP_LINE_TX_HDLC				0x0b3 + ET__REPORT + ET__API
#define EVENT__FXPMP_RSP_CED_DETECT				0x0b4 + ET__REPORT + ET__API
#define EVENT__FXPMP_RSP_CONNECT				0x0b5 + ET__REPORT + ET__API
#define EVENT__FXPMP_RSP_DCS_DETECT				0x0b6 + ET__REPORT + ET__API
#define EVENT__FXPMP_RSP_DISC					0x0b7 + ET__REPORT + ET__API
#define EVENT__FXPMP_RSP_ERROR					0x0b8 + ET__REPORT + ET__API
#define EVENT__FXPMP_RSP_FCERROR				0x0b9 + ET__REPORT + ET__API
#define EVENT__FXPMP_RSP_FLAGS_DETECT			0x0ba + ET__REPORT + ET__API
#define EVENT__FXPMP_RSP_OK						0x0bb + ET__REPORT + ET__API
#define EVENT__FXPMP_RSP_READY					0x0bc + ET__REPORT + ET__API
#define EVENT__FXPMP_RSP_RX_FRAME				0x0bd + ET__REPORT + ET__API
#define EVENT__FXPMP_RSP_SILENCE_DETECT			0x0be + ET__REPORT + ET__API
#define EVENT__FXPMP_RSP_UNKNOWN				0x0bf + ET__REPORT + ET__API
/*
 *	Define internal facsimile control events
 *
 */
#define EVENT__FX_SILENCE_RETEST				0x0e0 + ET__REPORT
#define EVENT__FX_SILENCE_ADJUST				0x0e1 + ET__REPORT
#define EVENT__FX_REINSTALL_THREADS				0x0e2 + ET__REPORT
#define EVENT__FX_SILENCE_ON					0x0e3 + ET__REPORT
#define EVENT__FX_SILENCE_OFF					0x0e4 + ET__REPORT
#define EVENT__FX_V21_CARRIER_DETECT			0x0e5 + ET__REPORT
#define EVENT__FX_V21_FLAG_DETECT				0x0e6 + ET__REPORT
#define EVENT__FX_TX_SEND_STOP					0x0e7 + ET__REPORT
#define EVENT__FX_TX_STOPPED					0x0e8 + ET__REPORT
#define EVENT__FX_TX_TRAINED					0x0e9 + ET__REPORT
#define EVENT__FX_MODULATION_DONE				0x0ea + ET__REPORT
#define EVENT__FX_V21_ENERGY_DETECT				0x0eb + ET__REPORT
#define EVENT__FX_HS_CARRIER_DETECT				0x0ec + ET__REPORT
#define EVENT__FX_CARRIER_LOSS					0x0ed + ET__REPORT
#define EVENT__FX_MODULATION_GO					0x0ee + ET__REPORT
#define EVENT__FX_MODULATION_STOP				0x0ef + ET__REPORT
#define EVENT__FX_OVERLAY						0x0af + ET__REPORT

/* ************************************************************************* */
/*
 *	Define modulation events
 *
 */
#define EVENT__SCRAMBLER_MATCH					0x0c0
#define EVENT__SEQUENCE_REVERSAL				0x0c1 + ET__INHIBIT + ET__REPORT
#define EVENT__SEQUENCE_DETECT					0x0c2 + ET__INHIBIT + ET__REPORT
#define EVENT__SEQUENCE_LOST					0x0c3 + ET__INHIBIT + ET__REPORT
#define EVENT__REVERSAL_ABORT					0x0c4 + ET__INHIBIT + ET__REPORT
#define EVENT__ENERGY_OFF						0x0c5 + ET__INHIBIT + ET__REPORT
#define EVENT__TRAIN_RESTART					0x0c6

#define EVENT__RATE_DETECT						0x0c9 + ET__REPORT
#define EVENT__E_DETECT							0x0ca + ET__REPORT
/* 0x0cb used above */
#define EVENT__REMOTE_RETRAIN					0x0cc + ET__INHIBIT + ET__REPORT + ET__API
#define EVENT__REMOTE_RENEGOTIATE				0x0cd + ET__INHIBIT + ET__REPORT + ET__API
#define EVENT__LOCAL_RENEGOTIATE				0x0ce + ET__API
#define EVENT__LOCAL_RETRAIN					0x0cf + ET__API
#define EVENT__AUTO_RETRAIN						0x0d0 + ET__INHIBIT + ET__REPORT + ET__API
#define EVENT__AUTO_RENEGOTIATE					0x0d1 + ET__INHIBIT + ET__REPORT + ET__API
#define EVENT__REFLECTED_DATA					0x0d3 + ET__INHIBIT + ET__REPORT
#define EVENT__GSTN_CLEARDOWN					0x0d4 + ET__REPORT + ET__API
#define EVENT__TRAIN_TIMEOUT					0x0d5 + ET__REPORT
#define EVENT__CATASTROPHIC_MSE_DETECTED		0x0d6 + ET__INHIBIT + ET__REPORT
#define EVENT__CATASTROPHIC_MSE_DELAY			0x0d7 + ET__INHIBIT + ET__REPORT
#define EVENT__SIGNAL_GOOD						0x0d8 + ET__INHIBIT
#define EVENT__SIGNAL_BAD						0x0d9 + ET__INHIBIT

#define EVENT__MONITOR_INPUT_RAW_STATUS			0x0da
#define EVENT__MONITOR_SHORT_GAIN_INHIBIT		0x0db
#define EVENT__MONITOR_SHORT_GAIN_RESYNC		0x0dc
#define EVENT__MONITOR_LONG_GAIN_INHIBIT		0x0dd
#define EVENT__MONITOR_LONG_GAIN_RESYNC			0x0de

#define EVENT__MONITOR_PHASE_ERROR				0x0df
#define EVENT__MONITOR_PHASE_RESYNC				0x0ae

/* ************************************************************************* */
/*
 *	Define V.22bis/V.22 specific events - move these to 0x0f0 to 0x0ff range
 *
 */
#define EVENT__SCRAMBLED_BINARY_0				0x0e0
#define EVENT__SCRAMBLED_BINARY_0_LOSS			0x0e1
#define EVENT__SCRAMBLED_BINARY_1				0x0e2
#define EVENT__SCRAMBLED_BINARY_1_LOSS			0x0e3
#define EVENT__SCRAMBLED_BINARY_1_32			0x0e4
#define EVENT__UNSCRAMBLED_BINARY_0				0x0e5
#define EVENT__UNSCRAMBLED_BINARY_0_LOSS		0x0e6
#define EVENT__UNSCRAMBLED_BINARY_1				0x0e7
#define EVENT__UNSCRAMBLED_BINARY_1_LOSS		0x0e8
#define EVENT__SCRAMBLED_ALTERNATIONS			0x0e9
#define EVENT__SCRAMBLED_ALT_LOSS				0x0ea
#define EVENT__SCRAMBLED_ALT_32					0x0eb
#define EVENT__S1_DETECT						0x0ec + ET__REPORT
#define EVENT__S1_LOSS							0x0ed
#define EVENT__POSSIBLE_USB_LOSS				0x0ee
#define EVENT__ALT_UNSCRAMBLED_BINARY_1			0x0ef
#define EVENT__ALT_S1_DETECT					0x0f0 + ET__REPORT
#define EVENT__ALT_S1_LOSS						0x0f1 + ET__REPORT
#define EVENT__ALT_POSSIBLE_USB_LOSS			0x0f2 + ET__REPORT
#define EVENT__V22_LOCAL_RETRAIN				0x0f3 + ET__REPORT + ET__API
/* 0x0f4 to 0x0f7 available */
/* 0x0fa to 0x0fb available */

#define EVENT__AUTOMODE_STOP					0x0fc + ET__REPORT
#define EVENT__V25ANS_START						0x0fd + ET__REPORT
#define EVENT__V32AA_DETECT_START				0x0fe + ET__REPORT
#define EVENT__V8JM_START						0x0ff + ET__REPORT

/* ************************************************************************* */
/*
 *	Define Caller ID specific events
 *
 */
#define EVENT__CH_SEIZE_DETECTED				0x0f8 + ET__REPORT + ET__API
#define EVENT__MARKS_DETECTED					0x0f9 + ET__REPORT + ET__API

/* ************************************************************************* */
/*
 *	Define V.34 specific events
 *
 */
#define EVENT__ENABLE_V34_INV_PARSER			0x100 + ET__REPORT

#define EVENT__FRAME_SENT						0x101
#define EVENT__E_RECEIVED						0x102 + ET__REPORT

#define EVENT__MP_RECEIVED						0x103 + ET__REPORT
#define EVENT__MPA_RECEIVED						0x104 + ET__REPORT
#define EVENT__MP_RECEIVED_CRC_ERROR			0x105 + ET__REPORT

#define EVENT__INFO_RECEIVED_CRC_OK				0x106 + ET__REPORT
#define EVENT__INFO_RECEIVED_CRC_ERROR			0x107 + ET__REPORT

#define EVENT__J4_DETECT						0x108 + ET__REPORT
#define EVENT__J16_DETECT						0x109 + ET__REPORT
#define EVENT__JE_DETECT						0x10a + ET__REPORT

#define EVENT__EQUALIZER_START					0x10b + ET__REPORT
#define EVENT__EQUALIZER_PP_START				0x10c + ET__REPORT
#define EVENT__EQUALIZER_TRN_START				0x10e + ET__REPORT
#define EVENT__EQUALIZER_HOLD					0x10f + ET__REPORT
#define EVENT__EQUALIZER_FREEZE					0x110 + ET__REPORT
#define EVENT__EQUALIZER_B1_START				0x111 + ET__REPORT

#define EVENT__BULK_HOLDOFF_DONE				0x112 + ET__REPORT
#define EVENT__EC_CONVERGED						0x113 + ET__REPORT
#define EVENT__EC_START							0x114 + ET__REPORT

#define EVENT__EC_HOLDOFF_START					0x115 + ET__REPORT
#define EVENT__EC_HOLDOFF_DONE					0x116 + ET__REPORT

#define EVENT__RX_PREDICTION_DONE				0x117 + ET__REPORT

#define EVENT__INFO_FOUND						0x118 + ET__REPORT
#define EVENT__AB_DETECT						0x119 + ET__REPORT
#define EVENT__AB_REVERSAL						0x11a + ET__REPORT
#define EVENT__AB_LOSS							0x11b + ET__REPORT
#define EVENT__INFOMARKS_DETECT					0x11c + ET__REPORT
#define EVENT__INFOMARKS_LOSS					0x11d + ET__REPORT

#define EVENT__RENEGOTIATE_SYMBOLS				0x11e + ET__REPORT
#define EVENT__RESYNC_PROCESS_FAIL				0x11f + ET__REPORT
#define EVENT__RESYNC_PROCESS_PASS				0x120 + ET__REPORT

#define EVENT__PROBING_BG_PROCESS_START			0x121 + ET__REPORT
#define EVENT__PROBING_BG_PREMATURE_END			0x122 + ET__REPORT
#define EVENT__PROBING_BG_NORMAL_END			0x123 + ET__REPORT
#define EVENT__PROCESS_PROBING_TIMEOUT			0x124 + ET__REPORT

#define EVENT__INFO0_CLOCK_MAX					0x125 + ET__REPORT
#define EVENT__INFO1_ATTENUATION				0x126 + ET__REPORT
#define EVENT__INFO1_PREEMPH_MAX				0x127 + ET__REPORT
#define EVENT__INFO1_MAXRATE_MIN				0x128 + ET__REPORT
#define EVENT__INFO1_MAXRATE_MAX				0x129 + ET__REPORT
#define EVENT__INFO1_SYMBOL_ERROR				0x130 + ET__REPORT
#define EVENT__INFO1_CARRIER_ERROR				0x131 + ET__REPORT
#define EVENT__INFO1_SYMBOL_MAX					0x132 + ET__REPORT
#define EVENT__INFO1_PREEMP_MAX					0x133 + ET__REPORT
#define EVENT__INFO1_FORCE_SYMBOL				0x134 + ET__REPORT
#define EVENT__MP_TRELLIS_MAX					0x135 + ET__REPORT
#define EVENT__MP_MAXRATE_MIN					0x136 + ET__REPORT
#define EVENT__MP_MAXRATE_MAX					0x137 + ET__REPORT
#define EVENT__INCOMPATIBLE_SETTING				0x138 + ET__REPORT
#define EVENT__PARAM_B_OUT_OF_RANGE				0x139 + ET__REPORT

/* ************************************************************************* */
/*
 *	Define V.8 specific events
 *
 */
#define EVENT__V8_TX_FRAME_SENT					0x140 + ET__REPORT
#define EVENT__V8_CJ_SENT						0x141 + ET__REPORT
#define EVENT__V8_RX_FRAME_VERIFIED				0x142 + ET__REPORT
#define EVENT__V8_CJ_RECEIVED					0x143 + ET__REPORT
#define EVENT__V8_DONE_CM_FOUND					0x144 + ET__REPORT
#define EVENT__V8_DONE_ANSAM_FOUND				0x145 + ET__REPORT
#define EVENT__V8_DONE_SUCCESS					0x146 + ET__REPORT
#define EVENT__V8_DONE_FAIL						0x147 + ET__REPORT

#define EVENT__ANSAM_2100_FOUND					0x148 + ET__REPORT
#define EVENT__ANSAM_2100_LOSS					0x149 + ET__REPORT
#define EVENT__ANSAM_15HZ_FOUND					0x14a + ET__REPORT

#define EVENT__V8_DONE_SHORT					0x14b + ET__REPORT
#define EVENT__V8_PCM_MODE_SWITCH				0x14c + ET__REPORT
#define EVENT__V8_RX_FRAME_START				0x14e + ET__REPORT
#define EVENT__V8_CMD_CONTINUE					0x14f

#define EVENT__V8_QC1a_RECEIVED					EVENT__MPA_RECEIVED
#define EVENT__V8_QC2a_RECEIVED					EVENT__MPA_RECEIVED
#define EVENT__V8_QC1d_RECEIVED					EVENT__MP_RECEIVED
#define EVENT__V8_QC2d_RECEIVED					EVENT__MP_RECEIVED

#define EVENT__V8_QCA1a_RECEIVED				EVENT__INFO_RECEIVED_CRC_OK
#define EVENT__V8_QCA2a_RECEIVED				EVENT__INFO_RECEIVED_CRC_OK
#define EVENT__V8_QCA1d_RECEIVED				EVENT__E_RECEIVED
#define EVENT__V8_QCA2d_RECEIVED				EVENT__E_RECEIVED

#define EVENT__V8_QC_SENT						EVENT__V8_TX_FRAME_SENT
#define EVENT__V8_QTS_DETECT					EVENT__SEQUENCE_DETECT
#define EVENT__V8_QTS_REVERSAL					EVENT__SEQUENCE_REVERSAL
#define EVENT__V8_TONEq_DETECT					EVENT__FX_V21_CARRIER_DETECT

/* ************************************************************************* */
/*
 *	Define V.110 specific events
 *
 */
#define EVENT__SYNC_DETECTED					0x150 + ET__REPORT
#define EVENT__SYNC_LOST						0x151 + ET__REPORT
#define EVENT__SYNC_TIMEOUT						0x152 + ET__REPORT
#define EVENT__DISCONNECT						0x153 + ET__REPORT
#define EVENT__RATE_DETECTED					0x154 + ET__REPORT
#define EVENT__SYNC_STARTED						0x155 + ET__REPORT
#define EVENT__AUTO_DETECT_STARTED				0x156 + ET__REPORT

#define EVENT__SYNC_ERROR						0x157 + ET__REPORT

/* ************************************************************************* */
/*
 *	Define internal pump events
 *
 */
#define EVENT_GROUP__TX_INTERNAL				EVENT_BLOCK__INTERNAL		/* 4 */
#define EVENT_GROUP__RX_INTERNAL				EVENT_BLOCK__INTERNAL + 4	/* 4 */

#define LOCAL__START_NWAY_RECEIVE				EVENT_GROUP__TX_INTERNAL + 1
#define LOCAL__CLEARDOWN_FOUND					EVENT_GROUP__TX_INTERNAL + 0
#define LOCAL__TX_TRAIN_GO						EVENT_GROUP__TX_INTERNAL + 0
#define LOCAL__RESYNC_FRCB1_START				EVENT_GROUP__TX_INTERNAL + 1

#define LOCAL__RX_TRAIN_RESET					EVENT_GROUP__RX_INTERNAL + 0
#define LOCAL__RX_TRAIN_START					EVENT_GROUP__RX_INTERNAL + 1
#define LOCAL__RX_TRAIN_STOP					EVENT_GROUP__RX_INTERNAL + 2
#define LOCAL__RX_TRAIN_PRESTART				EVENT_GROUP__RX_INTERNAL + 3

/* ************************************************************************* */
/*
 *	Define V.8bis specific events
 *
 */
#define EVENT__V8BIS_DURING_CALL_MODE			0x160
#define EVENT__V8BIS_TIMEOUT					0x161 + ET__REPORT
#define EVENT__V8BIS_REINSTALL_THREADS			0x162 + ET__REPORT

#define EVENT__V8BIS_MR_INITIATE				0x163
#define EVENT__V8BIS_CR_INITIATE				0x164
#define EVENT__V8BIS_ES_INITIATE				0x165
#define EVENT__V8BIS_ES_INITIATE_DELAY			0x166
#define EVENT__V8BIS_MSG_INITIATE				0x167

#define EVENT__V8BIS_MR_RESPOND					0x168
#define EVENT__V8BIS_CR_RESPOND					0x169
#define EVENT__V8BIS_ES_RESPOND					0x16a
#define EVENT__V8BIS_MSG_RESPOND				0x16b

#define EVENT__V8BIS_MR_DETECTED				0x16c + ET__REPORT
#define EVENT__V8BIS_CR_DETECTED				0x16d + ET__REPORT
#define EVENT__V8BIS_ES_DETECTED				0x16e + ET__REPORT
#define EVENT__V8BIS_MSG_DETECTED				0x16f + ET__REPORT

#define EVENT__V8BIS_SEGMENT_1_DETECTED			0x170 + ET__REPORT
#define EVENT__V8BIS_SEGMENT_1_TIMEOUT			0x171 + ET__REPORT
#define EVENT__V8BIS_TONE_SEGMENT_2_DONE		0x172 + ET__REPORT

#define EVENT__V8BIS_TX_START					0x173 + ET__REPORT
#define EVENT__V8BIS_TX_STOP					0x174
#define EVENT__V8BIS_RX_START					0x175 + ET__REPORT
#define EVENT__V8BIS_RX_STOP					0x176 + ET__REPORT
#define EVENT__V8BIS_FLAGS_DETECT				0x177 + ET__REPORT

#define EVENT__V8BIS_TX_PACKET_DONE				0x178 + ET__REPORT
#define EVENT__V8BIS_RX_PACKET_DONE				0x179 + ET__REPORT

#define EVENT__V8BIS_TERMINATE					0x17a

/* ************************************************************************* */
/*
 *	Define V.34 half-duplex specific events
 *
 */
#define EVENT__CC_START							0x180 + ET__REPORT
#define EVENT__CC_RESTART						0x181 + ET__REPORT
#define EVENT__CC_STOP							0x182 + ET__REPORT
#define EVENT__CC_RESTART_PP					0x183 + ET__REPORT
#define EVENT__CC_RESTART_S						0x184 + ET__REPORT
#define EVENT__CC_RESTART_AC					0x185 + ET__REPORT
#define EVENT__CC_DETECT_ONES					0x186 + ET__REPORT
#define EVENT__CC_DETECT_NOT_FLAGS				0x186 + ET__REPORT

#define EVENT__V34FHD_IRSP_CC_RESYNC			0x187 + ET__REPORT + ET__API

#define EVENT__CC_TONE_DETECT					0x188 + ET__REPORT
#define EVENT__CC_AC_DETECT						0x189 + ET__REPORT
#define EVENT__CC_S_DETECT						0x18a + ET__REPORT
#define EVENT__CC_PP_DETECT						0x18b + ET__REPORT
#define EVENT__CC_S_RECEIVED					0x18c + ET__REPORT
#define EVENT__CC_PP_RECEIVED					0x18d + ET__REPORT

#define EVENT__V34FHD_IRSP_DC_NOSIG				0x18e + ET__REPORT + ET__API
#define EVENT__V34FHD_IRSP_RATE_CHANGE			0x18f + ET__REPORT + ET__API

#define EVENT__V34FHD_RSP_DC_START				0x190 + ET__REPORT
#define EVENT__V34FHD_RSP_CC_START				0x191 + ET__REPORT
#define EVENT__V34FHD_RSP_DC_END				0x192 + ET__REPORT
#define EVENT__V34FHD_RSP_CC_END				0x193 + ET__REPORT
#define EVENT__V34FHD_RSP_DC_RETRAIN			0x194 + ET__REPORT
#define EVENT__V34FHD_RSP_CC_RETRAIN			0x195 + ET__REPORT

#define EVENT__V34FHD_IRSP_ONES_DETECT			0x196 + ET__REPORT + ET__API
#define EVENT__V34FHD_IRSP_SILENCE_DETECT		0x197 + ET__REPORT + ET__API

#define EVENT__V34FHD_CMD_DC_START				0x198
#define EVENT__V34FHD_CMD_CC_START				0x199
#define EVENT__V34FHD_RSP_DC_CONNECT			0x19a + ET__REPORT + ET__API
#define EVENT__V34FHD_RSP_CC_CONNECT			0x19b + ET__REPORT + ET__API
#define EVENT__V34FHD_RSP_DC_DISCONNECT			0x19c + ET__REPORT + ET__API
#define EVENT__V34FHD_RSP_CC_DISCONNECT			0x19d + ET__REPORT + ET__API
#define EVENT__V34FHD_CMD_MPH_READY				0x19e + ET__REPORT + ET__API
#define EVENT__V34FHD_RSP_MPH_READY				0x19f + ET__REPORT + ET__API

/* ************************************************************************* */
/*
 *	Define V.13 specific events
 *
 */
#define EVENT__V13_CIRCUIT_105_OFF				0x1a0 + ET__REPORT + ET__API
#define EVENT__V13_CIRCUIT_105_ON				0x1a1 + ET__REPORT + ET__API
#define EVENT__V13_CIRCUIT_109_OFF				0x1a2 + ET__REPORT + ET__API
#define EVENT__V13_CIRCUIT_109_ON				0x1a3 + ET__REPORT + ET__API
#define EVENT__V13_POLY_IDLE_DETECT				0x1a4 + ET__REPORT
#define EVENT__V13_POLY_ON_DETECT				0x1a5 + ET__REPORT
#define EVENT__V13_POLY_IDLE_LOST				0x1a6 + ET__REPORT
/* 0x1a7 available */

/* ************************************************************************* */
/*
 *	Define RBS signaling events
 *
 */
#define EVENT__RBS_RX_A0B0						0x1a8 + ET__REPORT
#define EVENT__RBS_RX_A0B1						0x1a9 + ET__REPORT
#define EVENT__RBS_RX_A1B0						0x1aa + ET__REPORT
#define EVENT__RBS_RX_A1B1						0x1ab + ET__REPORT

/* ************************************************************************* */
/*
 *	Define debug events
 *
 */
#define EVENT__REPORT_FGTHREADS					0x1ac
/* 0x1ad available */

#define EVENT__SERIAL_READ_DATA					0x1ae + ET__REPORT
#define EVENT__SERIAL_READ_DONE					0x1af + ET__REPORT

/* ************************************************************************* */
/*
 *	Define additional telephony events
 *
 */
#define EVENT__DTMF_EARLY_DETECT				0x1b0 + ET__REPORT + ET__API
#define EVENT__DTMF_EARLY_DETECT_END			0x1b1 + ET__REPORT + ET__API
#define EVENT__DTMF_MIN_TIMER					0x1b2 + ET__REPORT + ET__API
#define EVENT__DTMF_DETECT_END					0x1b3 + ET__REPORT + ET__API

#define EVENT__VDET_PROCESSING					0x1b4
#define EVENT__AD_SIT_MIN_TIMER					0x1b5 + ET__REPORT + ET__API
#define EVENT__AD_SIT_MAX_TIMER					0x1b6 + ET__REPORT + ET__API
#define EVENT__AD_START							0x1b7
#define EVENT__AD_STOP							0x1b8
#define EVENT__FAXDET_START						0x1b9
#define EVENT__FAXDET_STOP						0x1ba

#define EVENT__FAXDET_MEASUREMENT				0x1bb
#define EVENT__FAXDET_DETECT					0x1bc + ET__REPORT
#define EVENT__AD_DETECT						0x1bd + ET__REPORT

#define EVENT__CID2_TIMEOUT						0x1be + ET__REPORT

/* ************************************************************************* */
/*
 *	Define K56Flex events
 *
 */
#define EVENT__K56_V8BIS_ACK					0x1c0 + ET__REPORT
#define EVENT__K56_V8BIS_NAK					0x1c1 + ET__REPORT
#define EVENT__K56_V8BIS_K56_MS					0x1c2 + ET__REPORT
#define EVENT__K56_V8BIS_MS						0x1c3 + ET__REPORT

#define EVENT__SLOT_COUNTER_CLEAR				0x1c4 + ET__REPORT
#define EVENT__SLOT_COUNTER_ALIGN				0x1c5 + ET__REPORT
#define EVENT__JA_RECEIVED						0x1c6 + ET__REPORT
#define EVENT__J8_DETECT						0x1c7 + ET__REPORT
#define EVENT__SLOT_COUNTER_ERROR				0x1c8 + ET__REPORT

#define EVENT__K56_TRN2A_TIMEOUT				0x1cc + ET__REPORT
#define EVENT__K56_TRN2B_START					0x1cd + ET__REPORT
#define EVENT__K56_FRAME_SENT_JA				0x1ce + ET__REPORT
#define EVENT__K56_FRAME_SENT_MP				0x1cf + ET__REPORT

#define EVENT__K56_ILLEGAL_SYMBOL				0x1d0 + ET__REPORT
#define EVENT__K56_ILLEGAL_CARRIER				0x1d1 + ET__REPORT
#define EVENT__K56_TXLR_MAXRATE_LIMITED			0x1d2 + ET__REPORT
#define EVENT__K56_TXRL_MAXRATE_LIMITED			0x1d3 + ET__REPORT
#define EVENT__K56_TXxx_MINRATE_LIMITED			0x1d4 + ET__REPORT
#define EVENT__K56_RXLR_MAXRATE_MAX				0x1d5 + ET__REPORT
#define EVENT__K56_RXLR_MAXRATE_MIN				0x1d6 + ET__REPORT
#define EVENT__K56_RXRL_MAXRATE_MAX				0x1d7 + ET__REPORT
#define EVENT__K56_RXRL_MAXRATE_MIN				0x1d8 + ET__REPORT
#define EVENT__K56_RBS_MAX_LIMIT				0x1d9 + ET__REPORT
#define EVENT__K56_ASYMMETRIC_LAWS				0x1da + ET__REPORT
#define EVENT__K56_LOCAL_FALLBACK				0x1db + ET__REPORT
#define EVENT__K56_REMOTE_FALLBACK				0x1dc + ET__REPORT

#define EVENT__K56_RXxx_MINRATE_LIMITED			0x1dd + ET__REPORT

/* ************************************************************************* */
/*
 *	Define V.90 events
 *
 */
#define EVENT__INFO_V90_FALLBACK				0x1e0 + ET__REPORT
#define EVENT__FRAME_OVERRUN					0x1e1 + ET__REPORT

#define EVENT__DIL_N_MIN						0x1e2 + ET__REPORT
#define EVENT__DIL_N_MAX						0x1e3 + ET__REPORT
#define EVENT__DIL_LSP_MIN						0x1e4 + ET__REPORT
#define EVENT__DIL_LSP_MAX						0x1e5 + ET__REPORT
#define EVENT__DIL_LTP_MIN						0x1e6 + ET__REPORT
#define EVENT__DIL_LTP_MAX						0x1e7 + ET__REPORT

#define EVENT__CP_CONSTEL_MAX					0x1e8 + ET__REPORT

#define EVENT__DIL_PASS							0x1e9 + ET__REPORT
#define EVENT__DIL_PROCESS_START				0x1ea + ET__REPORT
#define EVENT__DIL_PROCESS_PREMATURE_END		0x1eb + ET__REPORT
#define EVENT__DIL_PROCESS_NORMAL_END			0x1ec + ET__REPORT

#define EVENT__ENCODER_K_MISMATCH				0x1ed + ET__REPORT
#define EVENT__ENCODER_S_MAX					0x1ee + ET__REPORT

#define EVENT__SHAPER_COEF_OVERFLOW				0x1ef + ET__REPORT
#define EVENT__SHAPER_OVERFLOW					0x1f0 + ET__REPORT
#define EVENT__ROCKWELL_BUG						0x1f1 + ET__REPORT
#define EVENT__SILENCE_SEGMENT					0x1f2 + ET__REPORT
#define EVENT__USR_QUIRK						0x1f3 + ET__REPORT

#define EVENT__V90_LOCAL_FALLBACK				0x1f4 + ET__REPORT
#define EVENT__CP_TYPE_MISMATCH					0x1f5 + ET__REPORT

/* ************************************************************************* */
/*
 *	Define V.92 events
 *
 */
#define EVENT__MH_RECEIVED_CRC_OK				EVENT__MP_RECEIVED + ET__API
#define EVENT__MH_ENTERED						0x1f7 + ET__REPORT + ET__API
#define EVENT__MH_REQUESTED						0x1f8 + ET__REPORT + ET__API
#define EVENT__MH_DENIED						0x1f9 + ET__REPORT + ET__API
#define EVENT__MH_ACKNOWLEDGED					0x1fa + ET__REPORT + ET__API
#define EVENT__MH_RECONNECT_REQUEST				0x1fb + ET__REPORT + ET__API
#define EVENT__MH_CLEARDOWN_REQUEST				0x1fc + ET__REPORT + ET__API
#define EVENT__MH_CLEARDOWN_ACKNOWLEDGE			0x1fd + ET__REPORT + ET__API
#define EVENT__MH_TIMEOUT						0x1fe + ET__REPORT + ET__API

#define EVENT__MH_POST_ENERGY					EVENT__RLSD_ON
#define EVENT__MH_POST_SILENCE					EVENT__RLSD_OFF

#define EVENT__JP_RECEIVED						EVENT__J4_DETECT
#define EVENT__JD_RECEIVED						EVENT__INFO_RECEIVED_CRC_OK
#define EVENT__JX_RECEIVED_CRC_ERROR			EVENT__INFO_RECEIVED_CRC_ERROR

#define EVENT__CPd_RECEIVED						EVENT__MP_RECEIVED
#define EVENT__CPdA_RECEIVED					EVENT__MPA_RECEIVED
#define EVENT__CPd_RECEIVED_CRC_ERROR			EVENT__MP_RECEIVED_CRC_ERROR

#define EVENT__CPu_RECEIVED						EVENT__MP_RECEIVED
#define EVENT__CPuA_RECEIVED					EVENT__MPA_RECEIVED
#define EVENT__CPu_RECEIVED_CRC_ERROR			EVENT__MP_RECEIVED_CRC_ERROR

#define EVENT__CPus_RECEIVED					EVENT__CC_PP_DETECT
#define EVENT__CPusA_RECEIVED					EVENT__CC_PP_RECEIVED
#define EVENT__CPus_RECEIVED_CRC_ERROR			EVENT__CP_TYPE_MISMATCH

#define EVENT__SUVd_RECEIVED					EVENT__CC_S_DETECT
#define EVENT__SUVdA_RECEIVED					EVENT__CC_S_RECEIVED
#define EVENT__SUVd_RECEIVED_CRC_ERROR			EVENT__INFO_RECEIVED_CRC_ERROR

#define EVENT__SUVu_RECEIVED					EVENT__CC_S_DETECT
#define EVENT__SUVuA_RECEIVED					EVENT__CC_S_RECEIVED
#define EVENT__SUVu_RECEIVED_CRC_ERROR			EVENT__INFO_RECEIVED_CRC_ERROR

#define EVENT__EXu_SENT							EVENT__CC_RESTART_S
#define EVENT__EXu_RECEIVED						EVENT__E_RECEIVED

#define EVENT__CPu_SENT							EVENT__K56_FRAME_SENT_MP
#define EVENT__CPd_SENT							EVENT__K56_FRAME_SENT_MP
#define EVENT__SUVd_SENT						EVENT__K56_FRAME_SENT_JA
#define EVENT__SUVu_SENT						EVENT__K56_FRAME_SENT_JA
/*#define EVENT__SUVd_SENT						EVENT__FRAME_SENT */
/*#define EVENT__SUVu_SENT						EVENT__FRAME_SENT */

#define EVENT__PRELENGTH_MAX					EVENT__DIL_LSP_MAX
#define EVENT__PRETOTAL_MAX						EVENT__DIL_LTP_MAX
#define EVENT__MODULUS_M_MIN					EVENT__DIL_LTP_MIN
#define EVENT__ENCODER_K_MIN					EVENT__DIL_N_MIN
#define EVENT__ENCODER_K_MAX					EVENT__DIL_N_MAX
#define EVENT__ENCODER_POINT_NOT_FOUND			EVENT__K56_ILLEGAL_SYMBOL

#define EVENT__CONSTEL_BG_PROCESS_START			EVENT__DIL_PROCESS_START
#define EVENT__CONSTEL_BG_NORMAL_END			EVENT__DIL_PROCESS_NORMAL_END
#define EVENT__CONSTEL_BG_PREMATURE_END			EVENT__DIL_PROCESS_PREMATURE_END

/* ************************************************************************* */
/*
 *	Define V21/V34F control channel fax probe events.
 */

#define	EVENT__SCC_DATA_RATE_1200				EVENT__J4_DETECT
#define	EVENT__SCC_DATA_RATE_2400				EVENT__J16_DETECT
#define	EVENT__SCC_TRAIN_RESTART				EVENT__TRAIN_RESTART
#define	EVENT__SCC_EQUALIZER_START				EVENT__EQUALIZER_START
#define	EVENT__SCC_EQUALIZER_HOLD				EVENT__EQUALIZER_HOLD
#define	EVENT__SCC_TONE_DETECT					EVENT__CC_TONE_DETECT
#define	EVENT__SCC_AC_DETECT					EVENT__CC_AC_DETECT
#define	EVENT__SCC_S_DETECT						EVENT__CC_S_DETECT
#define	EVENT__SCC_PP_DETECT					EVENT__CC_PP_DETECT
#define	EVENT__SCC_S_RECEIVED					EVENT__CC_S_RECEIVED
#define	EVENT__SCC_PP_RECEIVED					EVENT__CC_PP_RECEIVED
#define	EVENT__SCC_DETECT_ONES					EVENT__CC_DETECT_ONES
#define	EVENT__SCC_DETECT_NOT_FLAGS				EVENT__CC_DETECT_NOT_FLAGS
#define	EVENT__SCC_MPh_RECEIVED					EVENT__MP_RECEIVED
#define	EVENT__SCC_E_RECEIVED					EVENT__E_RECEIVED

#define	EVENT__RCC_DATA_RATE_1200				0x1c9 + ET__REPORT
#define	EVENT__RCC_DATA_RATE_2400				0x1ca + ET__REPORT
#define	EVENT__RCC_TRAIN_RESTART				0x1cb + ET__REPORT
#define	EVENT__RCC_EQUALIZER_START				0x1de + ET__REPORT
#define	EVENT__RCC_EQUALIZER_HOLD				0x1df + ET__REPORT
#define	EVENT__RCC_TONE_DETECT					0x1f6 + ET__REPORT
#define	EVENT__RCC_AC_DETECT					0x1f7 + ET__REPORT
#define	EVENT__RCC_S_DETECT						0x1f8 + ET__REPORT
#define	EVENT__RCC_PP_DETECT					0x1f9 + ET__REPORT
#define	EVENT__RCC_S_RECEIVED					0x1fa + ET__REPORT
#define	EVENT__RCC_PP_RECEIVED					0x1fb + ET__REPORT
#define	EVENT__RCC_DETECT_ONES					0x1fc + ET__REPORT
#define	EVENT__RCC_DETECT_NOT_FLAGS				0x1fd + ET__REPORT
#define	EVENT__RCC_MPh_RECEIVED					0x1fe + ET__REPORT
#define	EVENT__RCC_E_RECEIVED					0x1ff + ET__REPORT

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */
/*
 *	Define internal timer events
 *
 */
#define EVENT_TIMERS__TX_TIMERS					EVENT_BLOCK__TIMERS			/* 16 */
#define EVENT_TIMERS__RX_TIMERS					EVENT_BLOCK__TIMERS + 16	/* 32 */
#define EVENT_TIMERS__EQ_TIMERS					EVENT_BLOCK__TIMERS + 32	/* 16 */
#define EVENT_TIMERS__SART_TIMERS				EVENT_BLOCK__TIMERS + 48	/* 8 */
#define EVENT_TIMERS__EC_TIMERS					EVENT_BLOCK__TIMERS + 56	/* 20 */
#define EVENT_TIMERS__RUN_TIMERS				EVENT_BLOCK__TIMERS + 76	/* 8 */
#define EVENT_TIMERS__MAIN_TIMERS				EVENT_BLOCK__TIMERS + 84	/* 4 */

#define EVENT_TIMERS__CALL_PROGRESS				EVENT_BLOCK__TIMERS + 88	/* 8 */
#define EVENT_TIMERS__V25_TIMERS				EVENT_BLOCK__TIMERS + 96	/* 4 */
#define EVENT_TIMERS__CALL_TIMERS				EVENT_BLOCK__TIMERS + 100	/* 11 */ /* was 2 */

#define EVENT_TIMERS__FX_TIMERS					EVENT_BLOCK__TIMERS + 118	/* 4 */ /* was + 104 */ /* actually used 6 */

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */
/*
 *	Define IPBX/DEV events
 *
 */

/* DEV message handling (ISR to FG) */
#define	EVENT__DEV_TX_FRAME_DONE				0x280 + ET__REPORT
#define EVENT__DEV_RX_FRAME_DONE				0x281 + ET__REPORT
#define EVENT__DEV_RX_FRAME_OVERRUN				0x282 + ET__REPORT
#define EVENT__DEV_TX_MESSAGE_DONE				0x283 + ET__REPORT

/* DEV indication signals (ISR to FG) */
#define EVENT__DEV_IND_KEY_PRESSED				0x284 + ET__REPORT
#define EVENT__DEV_IND_KEY_RELEASED				0x285 + ET__REPORT
#define EVENT__DEV_IND_HEADSET_ON				0x286 + ET__REPORT
#define EVENT__DEV_IND_HEADSET_OFF				0x287 + ET__REPORT

#define EVENT__DEV_IND_OFF_HOOK					0x288 + ET__REPORT
#define EVENT__DEV_IND_ON_HOOK					0x289 + ET__REPORT
#define EVENT__DEV_IND_LINE_DISCONNECT			0x28a + ET__REPORT
#define EVENT__DEV_IND_LINE_RECONNECT			0x28b + ET__REPORT
#define EVENT__DEV_IND_POLARITY_REVERSE			0x28c + ET__REPORT

#define EVENT__DEV_IND_LINE_IN_USE				0x28d + ET__REPORT
#define EVENT__DEV_IND_LINE_NOT_IN_USE			0x28e + ET__REPORT
#define EVENT__DEV_IND_PARALLEL_OFF_HOOK		0x28f + ET__REPORT

/* These events must be the same as the ordinary ring detector */
#define EVENT__DEV_IND_RINGING_OFF				EVENT__RING_ENERGY_OFF
#define EVENT__DEV_IND_RINGING_ON				EVENT__RING_ENERGY_ON

/* DEV commands (BG to FG) */
#define EVENT__DEV_CMD_HW_RESET					0x290
#define EVENT__DEV_CMD_SW_RESET					0x291

#define EVENT__DEV_CMD_START_RINGING			0x292
#define EVENT__DEV_CMD_STOP_RINGING				0x293
#define EVENT__DEV_CMD_DIAL_DONE				0x294
#define EVENT__DEV_CMD_STANDBY					0x295
#define EVENT__DEV_CMD_REVERSE					0x296
#define EVENT__DEV_CMD_GLARE					0x297
#define EVENT__DEV_CMD_DISCONNECT				0x298
#define EVENT__DEV_CMD_CONNECTED				0x299
#define EVENT__DEV_CMD_BUSY						0x29a

#define EVENT__DEV_IND_ERROR					0x29b + ET__REPORT
/* 0x29c used below */

#define EVENT__DEV_CMD_OFF_HOOK					EVENT__OFF_HOOK
#define EVENT__DEV_CMD_ON_HOOK					EVENT__ON_HOOK

/* --- */
#define EVENT__DEV_CMD_START_TEST				0x29d
#define EVENT__DEV_CMD_STOP_TEST				0x29e
#define EVENT__DEV_WRITE_READ_TEST				0x29f

/* DEV responses (FG to BG) */
#define EVENT__DEV_RSP_OFF_HOOK					0x2a0 + ET__REPORT
#define EVENT__DEV_RSP_ON_HOOK					0x2a1 + ET__REPORT
#define EVENT__DEV_RSP_RING_ANSWER				0x2a2 + ET__REPORT
#define EVENT__DEV_RSP_HOOKFLASH				0x2a3 + ET__REPORT

#define EVENT__DEV_RSP_KEY_ENCODED				0x2a4 + ET__REPORT
#define EVENT__DEV_RSP_KEY_REPEATED				0x2a5 + ET__REPORT
#define EVENT__DEV_RSP_KEY_ALTERNATE			0x2a6 + ET__REPORT
#define EVENT__DEV_RSP_KEY_CLEARED				0x2a7 + ET__REPORT

#define EVENT__DEV_RSP_LINE_IN_USE				0x2a8 + ET__REPORT
#define EVENT__DEV_RSP_LINE_NOT_IN_USE			0x2a9 + ET__REPORT
#define EVENT__DEV_RSP_PARALLEL_OFF_HOOK		0x2aa + ET__REPORT
#define EVENT__DEV_RSP_RINGING_DETECTED			0x2ab + ET__REPORT
#define EVENT__DEV_RSP_RINGING_ENDED			0x2ac + ET__REPORT
#define EVENT__DEV_RSP_LINE_DISCONNECT			0x2ad + ET__REPORT
#define EVENT__DEV_RSP_POLARITY_REVERSE			0x2ae + ET__REPORT

#define EVENT__DEV_RSP_CONFIGURATION_COMPLETE	0x2af + ET__REPORT

/* DEV internal timers (FG to FG) */
#define EVENT__DEV_RESET_DELAY					0x2b0
#define EVENT__DEV_CALIBRATE_DELAY				0x2b1

#define EVENT__DEV_RING_ON_DELAY				0x2b2
#define EVENT__DEV_RING_OFF_DELAY				0x2b3
#define EVENT__DEV_TRANSITION_DELAY				0x2b4

#define	EVENT__DEV_HOOKFLASH_MINIMUM			0x2b5
#define EVENT__DEV_HOOKFLASH_MAXIMUM			0x2b6
#define EVENT__DEV_HOOKFLASH_HANGUP				0x2b7

#define EVENT__DEV_CLAMP_TIMER					0x29c

#define EVENT__DEV_KEY_TIMER					0x2b8
#define EVENT__DEV_RING_MINIMUM					0x2b9 + ET__REPORT

/* DEV commands (BG/FG to FG) */
#define EVENT__DEV_CMD_PSTN_RELAY_ON			0x2ba
#define EVENT__DEV_CMD_PSTN_RELAY_OFF			0x2bb

#define EVENT__DEV_CMD_SPEAKER_ON				0x2bc
#define EVENT__DEV_CMD_SPEAKER_OFF				0x2bd
#define EVENT__DEV_KEY_SPEAKER					0x2be + ET__REPORT
#define EVENT__DEV_KEY_MUTE						0x2bf + ET__REPORT

/* ************************************************************************* */
/*
 *	Define IPBX/VOIP events
 *
 */
/* IPBX/VOIP commands (VOIP to BG) */
#define EVENT__IPBX_CMD_INCOMING_CALL			0x2c0 + ET__BACKGROUND
#define EVENT__IPBX_CMD_INCOMING_CANCEL			0x2c1 + ET__BACKGROUND
#define EVENT__IPBX_CMD_RINGBACK				0x2c2 + ET__BACKGROUND
#define EVENT__IPBX_CMD_BUSY					0x2c3 + ET__BACKGROUND
#define EVENT__IPBX_CMD_UNAVAILABLE				0x2c4 + ET__BACKGROUND
#define EVENT__IPBX_CMD_SIT						0x2c5 + ET__BACKGROUND
#define EVENT__IPBX_CMD_PRECONNECTED			0x2fe + ET__BACKGROUND
#define EVENT__IPBX_CMD_CONNECTED				0x2c6 + ET__BACKGROUND
#define EVENT__IPBX_CMD_DISCONNECT				0x2c7 + ET__BACKGROUND
#define EVENT__IPBX_CMD_CONFERENCE				0x2c8 + ET__BACKGROUND
#define EVENT__IPBX_CMD_HOLD_DISCONNECT			0x2c9 + ET__BACKGROUND
#define EVENT__IPBX_CMD_HOLD_RERING				0x2ca + ET__BACKGROUND
#define EVENT__IPBX_CMD_MEDIA_CHANGE			0x2cb + ET__BACKGROUND

/* IPBX/PSTN commands (PSTN to BG) */
#define EVENT__IPBX_CMD_OFF_HOOK				0x2cc + ET__BACKGROUND
#define EVENT__IPBX_CMD_ON_HOOK					0x2cd + ET__BACKGROUND
#define EVENT__IPBX_CMD_ORIGINATE				0x2ce + ET__BACKGROUND
#define EVENT__IPBX_CMD_ORIGINATE_CANCEL		0x2cf + ET__BACKGROUND

/* FXS/FXO responses (BG to VOIP) */
#define EVENT__IPBX_RSP_ORIGINATE				0x2d0 + ET__BACKGROUND
#define EVENT__IPBX_RSP_RINGING_CANCELLED		0x2d1 + ET__BACKGROUND
#define EVENT__IPBX_RSP_INCOMING_ANSWERED		0x2d2 + ET__BACKGROUND
#define EVENT__IPBX_RSP_VOIP_CALL_START			0x2d3 + ET__BACKGROUND
#define EVENT__IPBX_RSP_PSTN_CALL_START			0x2d4 + ET__BACKGROUND
#define EVENT__IPBX_RSP_STATION_CALL_START		0x2d5 + ET__BACKGROUND
#define EVENT__IPBX_RSP_DISCONNECT				0x2d6 + ET__BACKGROUND
#define EVENT__IPBX_RING_NO_ANSWER_TIMER		0x2d7 + ET__BACKGROUND

/* IPBX internal (BG to BG) */
#define EVENT__IPBX_STARTUP						0x2d8 + ET__BACKGROUND
#define EVENT__IPBX_NEXT_STARTUP				0x2d9 + ET__BACKGROUND
#define EVENT__IPBX_FIRST_PARM_SET				0x2da + ET__BACKGROUND
#define EVENT__IPBX_NEXT_PARM_SET				0x2db + ET__BACKGROUND

#define EVENT__IPBX_INPUT_COMPLETE				0x2dc + ET__BACKGROUND
#define EVENT__IPBX_INPUT_ERROR					0x2dd + ET__BACKGROUND
#define EVENT__IPBX_NUMBER_ERROR				0x2de + ET__BACKGROUND
/* 0x2df used below */

#define EVENT__IPBX_CID_RECEIVED				0x2e0 + ET__BACKGROUND
#define EVENT__IPBX_CID_WAIT_TIMER				0x2e1 + ET__BACKGROUND
#define EVENT__IPBX_CID_CLEAR_TIMER				0x2e2 + ET__BACKGROUND

/* IPBX timers (BG to BG) */
#define EVENT__IPBX_DIALING_TIMEOUT				0x2e3 + ET__BACKGROUND
#define EVENT__IPBX_DIALTONE_PAUSE				0x2e4 + ET__BACKGROUND
#define EVENT__IPBX_INITIAL_DIAL_TIMEOUT		0x2e5 + ET__BACKGROUND
#define EVENT__IPBX_INTERDIGIT_TIMER			0x2e6 + ET__BACKGROUND

#define EVENT__IPBX_TIMEOUT_WARNING				0x2e7 + ET__BACKGROUND
#define EVENT__IPBX_TIMEOUT_BUSY				0x2e8 + ET__BACKGROUND
#define EVENT__IPBX_TIMEOUT_REORDER				0x2e9 + ET__BACKGROUND
#define EVENT__IPBX_TIMEOUT_PAUSE				0x2ea + ET__BACKGROUND
#define EVENT__IPBX_WARM_LINE_TIMER				0x2eb + ET__BACKGROUND
#define EVENT__IPBX_CALL_HOLD_TIMER				0x2ec + ET__BACKGROUND
#define EVENT__IPBX_HOLD_DROP_TIMER				0x2ed + ET__BACKGROUND

/* IPBX internal (BG to BG) */
#define EVENT__IPBX_INPUT_TONE_START			0x2ee + ET__BACKGROUND
#define EVENT__IPBX_INPUT_TONE_STOP				0x2ef + ET__BACKGROUND

/* ************************************************************************* */
/*
 *	Define LED events
 *
 */
#define EVENT__IPBX_RED_LED_CMD_START			0x2f0
#define EVENT__IPBX_GREEN_LED_CMD_START			0x2f1
#define EVENT__IPBX_RED_LED_SEGMENT_TIMER		0x2f2
#define EVENT__IPBX_GREEN_LED_SEGMENT_TIMER		0x2f3

#define EVENT__IPBX_LED_PERIODIC_TIMER			0x2f4
#define EVENT__IPBX_LED_CMD_START				0x2f5
#define EVENT__IPBX_LED_SEGMENT_TIMER			0x2f6
#define EVENT__IPBX_LED_RSP_STARTED				0x2f7 + ET__REPORT

/* ************************************************************************* */
/*
 *	Define other IPBX events
 *
 */
#define EVENT__IPBX_RTP_STARTUP					0x2f8
#define EVENT__IPBX_RTP_SHUTDOWN				0x2f9
#define EVENT__IPBX_RTP_RESTART					0x2fa
#define EVENT__IPBX_RTP_DTMF_PLAYOUT			0x2fb
#define EVENT__IPBX_RTP_TRANSFER				0x2df

#define EVENT__IPBX_RTP_STATISTICS_REPORT		0x2fc
#define EVENT__IPBX_RTP_STATISTICS_READ			0x2fd + ET__REPORT
/* 0x2fe used above */
#define EVENT__IPBX_PERIODIC_TIMER				0x2ff + ET__BACKGROUND

/* ************************************************************************* */
/*
 *	Define DPBX/VPPN events
 *
 */
#define EVENT__VPPN_CMD_DEV_COMMAND_SEND		0x300
#define EVENT__VPPN_CMD_DEV_FINALIZE			0x301
#define EVENT__VPPN_CMD_DEV_REGISTER			0x302
#define EVENT__VPPN_CMD_DEV_ACTIVATE			0x303
#define EVENT__VPPN_CMD_DEV_DEACTIVATE			0x304
#define EVENT__VPPN_CMD_DEV_UNREGISTER			0x305

#define EVENT__VPPN_CMD_DEV_UPDATE_FIRMWARE		0x306
#define EVENT__VPPN_CMD_DEV_READ_FIRMWARE		0x307

#define EVENT__VPPN_RSP_DEV_COMMAND_SENT		0x308 + ET__REPORT
#define EVENT__VPPN_RSP_DEV_UPDATE_COMPLETE		0x309 + ET__REPORT
#define EVENT__VPPN_RSP_DEV_READ_COMPLETE		0x30a + ET__REPORT

#define EVENT__VPPN_STATISTICS_TIMER			0x30b

#define EVENT__VPPN_REQ_DEV_FINALIZE			0x30c + ET__REPORT
#define EVENT__VPPN_REQ_DEV_REGISTER			0x30d + ET__REPORT

#define EVENT__VPPN_IND_DEV_SPOTTED				0x30e + ET__REPORT
#define EVENT__VPPN_IND_DEV_VANISHED			0x30f + ET__REPORT

/* ************************************************************************* */
/*
 *	Define Telephony events
 *
 */
#define EVENT__DETECT_DISCONNECT_TONE			0x310
#define EVENT__DISCONNECT_TONE_START			0x311
#define EVENT__DISCONNECT_TONE_FOUND			0x312 + ET__REPORT + ET__API

#define EVENT__PRIORITY_PATTERN_START			0x313
#define EVENT__PRIORITY_TONE_STOP				0x314

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */
/*
 *	Define bonding events
 *
 */

/* ************************************************************************* */
/*
 *
 *	Channel control events
 */

#define EVENT__DT_MF_SYNCH_PR					0x010 + EVENT_BLOCK__ISDN
#define EVENT__DT_MF_SYNCH_SR					0x011 + EVENT_BLOCK__ISDN
#define EVENT__DT_MF_UNSYNCH_PR					0x012 + EVENT_BLOCK__ISDN
#define EVENT__DT_MF_UNSYNCH_SR					0x013 + EVENT_BLOCK__ISDN
#define EVENT__DT_FBW_SYNCH						0x014 + EVENT_BLOCK__ISDN
#define EVENT__DT_RI_GAIN						0x015 + EVENT_BLOCK__ISDN
#define EVENT__DT_RI_LOST						0x016 + EVENT_BLOCK__ISDN
#define EVENT__DT_ALLIGN_GAIN_PR				0x017 + EVENT_BLOCK__ISDN
#define EVENT__DT_ALLIGN_LOST_PR				0x018 + EVENT_BLOCK__ISDN
#define EVENT__DT_ALLIGN_GAIN_SR				0x019 + EVENT_BLOCK__ISDN
#define EVENT__DT_ALLIGN_LOST_SR				0x020 + EVENT_BLOCK__ISDN
/*
 *	Bonding multiframe control
 *
 */
#define EVENT__BMC_CC_LSYNCH_IND				0x020 + EVENT_BLOCK__ISDN
#define EVENT__BMC_CC_RSYNCH_IND				0x021 + EVENT_BLOCK__ISDN
#define EVENT__BMC_CC_RSYNCH_FAIL_IND			0x022 + EVENT_BLOCK__ISDN
#define EVENT__BMC_CC_FAIL_IND_PR				0x023 + EVENT_BLOCK__ISDN
#define EVENT__BMC_CC_FAIL_IND_SR				0x024 + EVENT_BLOCK__ISDN
#define EVENT__BMC_CC_LLOS_IND					0x025 + EVENT_BLOCK__ISDN
#define EVENT__BMC_CC_RLOS_IND					0x026 + EVENT_BLOCK__ISDN
/*
 *	Negotiation control
 *
 */
#define EVENT__BMC_CC_ADD_REQ_PR				0x026 + EVENT_BLOCK__ISDN
#define EVENT__BMC_CC_DEL_REQ_PR				0x027 + EVENT_BLOCK__ISDN
#define EVENT__BMC_CC_ADD_REQ_SR				0x028 + EVENT_BLOCK__ISDN
#define EVENT__BMC_CC_DEL_REQ_SR				0x029 + EVENT_BLOCK__ISDN
/*
 *	Information channel message detection
 *
 */
#define EVENT__BDT_CID							0x030 + EVENT_BLOCK__ISDN
#define EVENT__BDT_INIT_REQ						0x031 + EVENT_BLOCK__ISDN
#define EVENT__BDT_INIT_ACK						0x032 + EVENT_BLOCK__ISDN
#define EVENT__BDT_DN_REQ						0x033 + EVENT_BLOCK__ISDN
#define EVENT__BDT_DN_RESP						0x034 + EVENT_BLOCK__ISDN
#define EVENT__BDT_ADD_CH						0x035 + EVENT_BLOCK__ISDN
#define EVENT__BDT_ADD_CH_ACK					0x036 + EVENT_BLOCK__ISDN
#define EVENT__BDT_ADD_CH_REJ					0x037 + EVENT_BLOCK__ISDN
#define EVENT__BDT_DEL_CH						0x038 + EVENT_BLOCK__ISDN
#define EVENT__BDT_DEL_CH_ACK					0x039 + EVENT_BLOCK__ISDN
#define EVENT__BDT_DEL_CH_REJ					0x03a + EVENT_BLOCK__ISDN
#define EVENT__BDT_DISC_REQ						0x03b + EVENT_BLOCK__ISDN
#define EVENT__BDT_DISC_ACK						0x03c + EVENT_BLOCK__ISDN
/*
 *	Events from higher layer
 *
 */
#define EVENT__BONDING_INIT_REQ					0x040 + EVENT_BLOCK__ISDN
#define EVENT__DQ_CONN_REQ						0x041 + EVENT_BLOCK__ISDN
#define EVENT__DQ_DISC_REQ						0x042 + EVENT_BLOCK__ISDN
#define EVENT__DQ_DEL_CH_REQ					0x043 + EVENT_BLOCK__ISDN
#define EVENT__DQ_ADD_CH_REQ					0x044 + EVENT_BLOCK__ISDN
#define EVENT__DQ_ABORT_REQ						0x045 + EVENT_BLOCK__ISDN
/*
 *	Events to higher layer
 *
 */
#define EVENT__DQ_INIT_IND						0x050 + EVENT_BLOCK__ISDN
#define EVENT__DQ_ADD_CH_IND					0x051 + EVENT_BLOCK__ISDN
#define EVENT__DQ_ADD_CH_CONF					0x052 + EVENT_BLOCK__ISDN
#define EVENT__DQ_ADD_CH_FAIL_IND				0x053 + EVENT_BLOCK__ISDN
#define EVENT__DQ_DEL_CH_IND					0x054 + EVENT_BLOCK__ISDN
#define EVENT__DQ_DEL_CH_CONF					0x055 + EVENT_BLOCK__ISDN
#define EVENT__DQ_DEL_CH_FAIL_IND				0x056 + EVENT_BLOCK__ISDN
#define EVENT__DQ_DISC_IND						0x057 + EVENT_BLOCK__ISDN
#define EVENT__DQ_CID_FAIL_IND					0x058 + EVENT_BLOCK__ISDN
/*
 *	Timer events for multiframe protocol
 *
 */
#define EVENT__T_FA_EXP							0x060 + EVENT_BLOCK__ISDN
/*
 *	Timer events for answering endpoint
 *
 */
#define EVENT__TANULL_EXP						0x070 + EVENT_BLOCK__ISDN
#define EVENT__TAINIT_EXP						0x071 + EVENT_BLOCK__ISDN
#define EVENT__TAADD01_EXP						0x072 + EVENT_BLOCK__ISDN
#define EVENT__TAADD_EXP						0x073 + EVENT_BLOCK__ISDN
#define EVENT__TADEL_EXP						0x074 + EVENT_BLOCK__ISDN
#define EVENT__TAADD02_EXP						0x076 + EVENT_BLOCK__ISDN
#define EVENT__TADISC_EXP						0x077 + EVENT_BLOCK__ISDN
/*
 *	Timer events for calling endpoint
 *
 */
#define EVENT__TCINIT_EXP						0x081 + EVENT_BLOCK__ISDN
#define EVENT__TCADD01_EXP						0x082 + EVENT_BLOCK__ISDN
#define EVENT__TCADD_EXP						0x083 + EVENT_BLOCK__ISDN
#define EVENT__TCDEL_EXP						0x084 + EVENT_BLOCK__ISDN
#define EVENT__TCID_EXP							0x085 + EVENT_BLOCK__ISDN
#define EVENT__TCADD02_EXP						0x086 + EVENT_BLOCK__ISDN
#define EVENT__TCDISC_EXP						0x087 + EVENT_BLOCK__ISDN

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */
/*
 *	Define background events
 *
 */

/* ************************************************************************* */
/*
 *	Protocol Timers - These timer ticks occur at a high rate.  Any diagnostic
 *	mechanisms may want to ignore their display.  Rather than examining for a
 *	large set of timer event numbers, many of these timers can share the same
 *	event number since they typically cannot be active at the same time.
 *
 */
/*#define EVENT__PROTOCOL_TICK_TIMER			0x521 + ET__PERIODIC + ET__BACKGROUND*/
#define EVENT__PROTOCOL_TICK_TIMER				0x521 + ET__BACKGROUND
#define EVENT__FX1_TICK_TIMER					EVENT__PROTOCOL_TICK_TIMER
#define EVENT__T30_TICK_TIMER					EVENT__PROTOCOL_TICK_TIMER
#define EVENT__DP_TIMER							EVENT__PROTOCOL_TICK_TIMER

/* ************************************************************************* */
/*
 *	OMC events
 *
 */
#define EVENT__DMDP_TIMER						0x400 + ET__BACKGROUND
#define EVENT__OMC_DIAL_RRING_TIMER				0x401 + ET__BACKGROUND
#define EVENT__OMC_UNUSED_2						0x402 + ET__BACKGROUND
#define EVENT__OMC_OFF_HOOK_MIN_TIMER			0x403 + ET__BACKGROUND
#define EVENT__OMC_ACCESS_DONE					0x404 + ET__BACKGROUND
#define EVENT__OMC_OVERLAY						0x405 + ET__BACKGROUND
#define EVENT__OMC_OVERLAY_CONTINUE				0x406 + ET__BACKGROUND
#define EVENT__OMC_TIMER						0x407 + ET__BACKGROUND
#define EVENT__OMC_ADP_SENT						0x408 + ET__BACKGROUND
#define EVENT__OMC_INSTALL						0x409 + ET__BACKGROUND
#define EVENT__OMC_CMD_CONNECT					0x40a + ET__BACKGROUND
#define EVENT__OMC_CMD_DIAL						0x40b + ET__BACKGROUND
#define EVENT__OMC_CMD_DISCONNECT				0x40c + ET__BACKGROUND
#define EVENT__OMC_CMD_ESCAPE					0x40d + ET__BACKGROUND
#define EVENT__OMC_CMD_HALT						0x40e + ET__BACKGROUND
#define EVENT__OMC_CMD_HOOK_OFF					0x40f + ET__BACKGROUND
#define EVENT__OMC_CMD_IDLE						0x410 + ET__BACKGROUND
#define EVENT__OMC_CMD_HOOK_ON					0x411 + ET__BACKGROUND
#define EVENT__OMC_CMD_RETRAIN					0x412 + ET__BACKGROUND
#define EVENT__OMC_CMD_REMOVE					0x413 + ET__BACKGROUND
#define EVENT__OMC_CMD_T30_ORIGINATE			0x414 + ET__BACKGROUND
#define EVENT__OMC_CMD_T30_ANSWER				0x415 + ET__BACKGROUND
#define EVENT__OMC_CMD_UNIDLE					0x416 + ET__BACKGROUND
#define EVENT__OMC_RSP_CMD_ACK					0x417 + ET__BACKGROUND + ET__API
#define EVENT__OMC_RSP_CONNECT					0x418 + ET__BACKGROUND + ET__API
#define EVENT__OMC_RSP_DISC						0x419 + ET__BACKGROUND + ET__API
#define EVENT__OMC_RSP_ERROR					0x41a + ET__BACKGROUND + ET__API
#define EVENT__OMC_RSP_FCERROR					0x41b + ET__BACKGROUND + ET__API
#define EVENT__OMC_RSP_HALT_ACK					0x41c + ET__BACKGROUND + ET__API
#define EVENT__OMC_RSP_NO_CARRIER				0x41d + ET__BACKGROUND + ET__API
#define EVENT__OMC_RSP_OK						0x41e + ET__BACKGROUND + ET__API
#define EVENT__OMC_RSP_ON_HOOK					0x41f + ET__BACKGROUND + ET__API
#define EVENT__OMC_RSP_RING						0x420 + ET__BACKGROUND + ET__API
#define EVENT__OMC_RSP_RX_FRAME					0x421 + ET__BACKGROUND + ET__API
#define EVENT__OMC_DIAL_RSP_RRING_LOST			0x422 + ET__BACKGROUND + ET__API
#define EVENT__OMC_DIAL_RSP_BUSY				0x423 + ET__BACKGROUND + ET__API
#define EVENT__OMC_DIAL_RSP_DELAYED				0x424 + ET__BACKGROUND + ET__API
#define EVENT__OMC_DIAL_RSP_NO_ANSWER			0x425 + ET__BACKGROUND + ET__API
#define EVENT__OMC_DIAL_RSP_NO_DIALTONE			0x426 + ET__BACKGROUND + ET__API
#define EVENT__OMC_DIAL_RSP_SUCCESS				0x427 + ET__BACKGROUND + ET__API
#define EVENT__OMC_DIAL_IRSP_BONG				0x428 + ET__BACKGROUND + ET__API
#define EVENT__OMC_IRSP_CARRIER					0x429 + ET__BACKGROUND + ET__API
#define EVENT__OMC_IRSP_PROTOCOL				0x42a + ET__BACKGROUND + ET__API
#define EVENT__OMC_IRSP_COMPRESSION				0x42b + ET__BACKGROUND + ET__API
#define EVENT__OMC_RSP_OFF_HOOK					0x42c + ET__BACKGROUND + ET__API
#define EVENT__HOOK_CMD_OFF						0x42d + ET__BACKGROUND
#define EVENT__HOOK_RSP_OFF						0x42e + ET__BACKGROUND + ET__API
#define EVENT__HOOK_CMD_ON						0x42f + ET__BACKGROUND
#define EVENT__HOOK_RSP_ON						0x430 + ET__BACKGROUND + ET__API
#define EVENT__OMC_CMD_CONTINUE					0x431 + ET__BACKGROUND
#define EVENT__OMC_RSP_FAX						0x432 + ET__BACKGROUND + ET__API
#define EVENT__OMC_IRSP_DATA					0x433 + ET__BACKGROUND + ET__API
#define EVENT__OMC_DP_FALLBACK_TIMER			0x435 + ET__BACKGROUND
#define EVENT__OMC_IRSP_DETECT_ODP				0x436 + ET__BACKGROUND
#define EVENT__OMC_IRSP_DETECT_MNP				0x437 + ET__BACKGROUND
#define EVENT__OMC_IRSP_DETECT_FLAGS			0x438 + ET__BACKGROUND
#define EVENT__OMC_IRSP_DETECT_ADP_LAPM			0x439 + ET__BACKGROUND
#define EVENT__OMC_IRSP_DETECT_ADP_MNP			0x43a + ET__BACKGROUND
#define EVENT__OMC_IRSP_DETECT_ADP_BUFFERED		0x43b + ET__BACKGROUND
#define EVENT__OMC_IRSP_DETECT_AR_200			0x43c + ET__BACKGROUND
#define EVENT__OMC_IRSP_DETECT_AR_CHAR			0x43d + ET__BACKGROUND
#define EVENT__OMC_IRSP_DETECT_TIMEOUT			0x43e + ET__BACKGROUND
#define EVENT__OMC_HOOK_TIMER					0x43f + ET__BACKGROUND
#define EVENT__CIRCUIT_DISCONNECT				0x440 + ET__BACKGROUND
#define EVENT__OMC_CMD_FX1_ANSWER				0x441 + ET__BACKGROUND
#define EVENT__OMC_CMD_FX1_ORIGINATE			0x442 + ET__BACKGROUND
#define EVENT__DIAL_READY						0x443 + ET__BACKGROUND
#define EVENT__OMC_READY						0x444 + ET__BACKGROUND + ET__API
#define EVENT__OMC_RSP_CONTINUE					0x445 + ET__BACKGROUND + ET__API
#define EVENT__OMC_REQUIREMENT_FAIL				0x446 + ET__BACKGROUND
#define EVENT__OMC_TEL_ACTIVE_CHANGE			0x447 + ET__BACKGROUND
#define EVENT__OMC_TONE_DETECT_SYNC				0x448 + ET__BACKGROUND
#define EVENT__OMC_ON_HOOK_IDLE					0x449 + ET__BACKGROUND
#define EVENT__OMC_MONITOR_TICK					0x44a + ET__BACKGROUND
#define EVENT__OMC_MONITOR_ST_UPDATE			0x44b + ET__BACKGROUND
#define EVENT__OMC_MONITOR_CONNECT_SYNC			0x44c + ET__BACKGROUND
#define EVENT__OMC_CMD_RENEGOTIATE				0x44d + ET__BACKGROUND
#define EVENT__OMC_IRSP_DETECT_SYNC				0x44e + ET__BACKGROUND + ET__API
#define EVENT__OMC_MONITOR_PRA_TIMER			0x44f + ET__BACKGROUND
#define EVENT__OMC_SHUTDOWN						0x450 + ET__BACKGROUND
#define EVENT__OMC_MONITOR_CMD_STOP				0x451 + ET__BACKGROUND
#define EVENT__OMC_MONITOR_RSP_IDLE				0x452 + ET__BACKGROUND
#define EVENT__OMC_DMDISCMON_TIMER				0x453 + ET__BACKGROUND
#define EVENT__POST_DIALTONE_PAUSE_TIMER		0x454 + ET__BACKGROUND

/* ************************************************************************* */
/*
 *	SCC events
 *
 */
#define EVENT__SCC_CMD_ANSWER_START				0x480 + ET__BACKGROUND
#define EVENT__SCC_CMD_CALLER_START				0x481 + ET__BACKGROUND
#define EVENT__SCC_CMD_DISCONNECT				0x482 + ET__BACKGROUND
#define EVENT__SCC_CMD_GENERATE_START			0x483 + ET__BACKGROUND
#define EVENT__SCC_CMD_GENERATE_STOP			0x484 + ET__BACKGROUND
#define EVENT__SCC_CMD_DETECTOR_CHANGE			0x485 + ET__BACKGROUND
#define EVENT__SCC_CMD_VOLUME_CHANGE			0x486 + ET__BACKGROUND
#define EVENT__SCC_CMD_OPERATION_CHANGE			0x487 + ET__BACKGROUND
#define EVENT__SCC_CMD_G711_TRANSITION			0x488 + ET__BACKGROUND

#define EVENT__SCC_RSP_READY					0x490 + ET__BACKGROUND
#define EVENT__SCC_RSP_DISCONNECT				0x491 + ET__BACKGROUND
#define EVENT__SCC_RSP_GENERATE_DONE			0x492 + ET__BACKGROUND
#define EVENT__SCC_RSP_OPERATION_ACK			0x493 + ET__BACKGROUND
#define EVENT__SCC_RSP_OPERATION_NAK			0x494 + ET__BACKGROUND

#define EVENT__SCC_TIMER						0x49F + ET__BACKGROUND

/* ************************************************************************* */
/*
 *	TSSC events
 *
 */
#define EVENT__TSSC_CMD_CANCEL					0x4A0 + ET__BACKGROUND
#define EVENT__TSSC_CMD_DISCONNECT				0x4A1 + ET__BACKGROUND
#define EVENT__TSSC_CMD_HALT					0x4A2 + ET__BACKGROUND
#define EVENT__TSSC_CMD_INBND_MONITOR			0x4A3 + ET__BACKGROUND
#define EVENT__TSSC_CMD_INBND_START				0x4A4 + ET__BACKGROUND
#define EVENT__TSSC_CMD_OUTBND_START			0x4A5 + ET__BACKGROUND
#define EVENT__TSSC_CMD_TAKEOVER				0x4A6 + ET__BACKGROUND

#define EVENT__TSSC_ICMD_CP_CHANGE				0x4A7 + ET__BACKGROUND
#define EVENT__TSSC_ICMD_INBND_PROC_ACCEPT		0x4A8 + ET__BACKGROUND
#define EVENT__TSSC_ICMD_INBND_PROC_FAIL		0x4A9 + ET__BACKGROUND

#define EVENT__TSSC_IRSP_CIRCUIT_LOSS			0x4AA + ET__BACKGROUND + ET__API
#define EVENT__TSSC_IRSP_CP_CHANGE				0x4AB + ET__BACKGROUND + ET__API
#define EVENT__TSSC_IRSP_INBND_PROC_READY		0x4AC + ET__BACKGROUND + ET__API
#define EVENT__TSSC_IRSP_OUTBND_START_SUCC		0x4AD + ET__BACKGROUND + ET__API

#define EVENT__TSSC_RSP_IDLE					0x4AE + ET__BACKGROUND + ET__API
#define EVENT__TSSC_RSP_INBND_DETECT			0x4AF + ET__BACKGROUND + ET__API
#define EVENT__TSSC_RSP_ON_LINE					0x4B0 + ET__BACKGROUND + ET__API
#define EVENT__TSSC_RSP_STOP					0x4B1 + ET__BACKGROUND + ET__API

#define EVENT__ETSSC_CTL_CALL_ACCEPTED			0x4B2 + ET__BACKGROUND
#define EVENT__ETSSC_CTL_CIRCUIT_LOSS			0x4B3 + ET__BACKGROUND
#define EVENT__ETSSC_CTL_CP_CHANGE				0x4B4 + ET__BACKGROUND
#define EVENT__ETSSC_CTL_INBND_DETECT			0x4B5 + ET__BACKGROUND

#define EVENT__ETSSC_IND_DISCONNECT				0x4B6 + ET__BACKGROUND
#define EVENT__ETSSC_IND_HALT					0x4B7 + ET__BACKGROUND
#define EVENT__ETSSC_IND_INBND_MONITOR			0x4B8 + ET__BACKGROUND
#define EVENT__ETSSC_IND_INBND_PROCEEDING		0x4B9 + ET__BACKGROUND
#define EVENT__ETSSC_IND_ON_LINE				0x4BA + ET__BACKGROUND
#define EVENT__ETSSC_IND_PROCEED_CP_CHANGE		0x4BB + ET__BACKGROUND
#define EVENT__ETSSC_IND_PROC_FAIL				0x4BC + ET__BACKGROUND

#define EVENT__TSSC_ADDRESS_TIMEOUT				0x4BD + ET__BACKGROUND
#define EVENT__TSSC_DIGIT_TIMEOUT				0x4BE + ET__BACKGROUND
#define EVENT__TSSC_TIMER						0x4BF + ET__BACKGROUND

/* ************************************************************************* */
/*
 *	Application Specific Background Events
 *
 */
#define EVENT__RSPMON_GOOD0						0x4c0 + ET__BACKGROUND
#define EVENT__RSPMON_GOOD1						0x4c1 + ET__BACKGROUND
#define EVENT__RSPMON_GOOD2						0x4c2 + ET__BACKGROUND
#define EVENT__RSPMON_GOOD3						0x4c3 + ET__BACKGROUND
#define EVENT__RSPMON_GOOD4						0x4c4 + ET__BACKGROUND
#define EVENT__RSPMON_GOOD5						0x4c5 + ET__BACKGROUND
#define EVENT__RSPMON_GOOD6						0x4c6 + ET__BACKGROUND
#define EVENT__RSPMON_GOOD7						0x4c7 + ET__BACKGROUND
#define EVENT__RSPMON_BAD0						0x4c8 + ET__BACKGROUND
#define EVENT__RSPMON_BAD1						0x4c9 + ET__BACKGROUND
#define EVENT__RSPMON_BAD2						0x4ca + ET__BACKGROUND
#define EVENT__RSPMON_BAD3						0x4cb + ET__BACKGROUND
#define EVENT__RSPMON_BAD4						0x4cc + ET__BACKGROUND
#define EVENT__RSPMON_BAD5						0x4cd + ET__BACKGROUND
#define EVENT__RSPMON_BAD6						0x4ce + ET__BACKGROUND
#define EVENT__RSPMON_BAD7						0x4cf + ET__BACKGROUND

#define EVENT__APP_CMD_0						0x4e0 + ET__BACKGROUND
#define EVENT__APP_CMD_1						0x4e1 + ET__BACKGROUND
#define EVENT__APP_CMD_2						0x4e2 + ET__BACKGROUND
#define EVENT__APP_CMD_3						0x4e3 + ET__BACKGROUND
#define EVENT__APP_CMD_4						0x4e4 + ET__BACKGROUND
#define EVENT__APP_CMD_5						0x4e5 + ET__BACKGROUND
#define EVENT__APP_CMD_6						0x4e6 + ET__BACKGROUND
#define EVENT__APP_CMD_7						0x4e7 + ET__BACKGROUND
#define EVENT__APP_CMD_8						0x4e8 + ET__BACKGROUND
#define EVENT__APP_CMD_9						0x4e9 + ET__BACKGROUND
#define EVENT__APP_CMD_A						0x4ea + ET__BACKGROUND
#define EVENT__APP_CMD_B						0x4eb + ET__BACKGROUND
#define EVENT__APP_CMD_C						0x4ec + ET__BACKGROUND
#define EVENT__APP_CMD_D						0x4ed + ET__BACKGROUND
#define EVENT__APP_CMD_E						0x4ee + ET__BACKGROUND
#define EVENT__APP_CMD_F						0x4ef + ET__BACKGROUND
#define EVENT__APP_RSP_0						0x4f0 + ET__BACKGROUND
#define EVENT__APP_RSP_1						0x4f1 + ET__BACKGROUND
#define EVENT__APP_RSP_2						0x4f2 + ET__BACKGROUND
#define EVENT__APP_RSP_3						0x4f3 + ET__BACKGROUND
#define EVENT__APP_RSP_4						0x4f4 + ET__BACKGROUND
#define EVENT__APP_RSP_5						0x4f5 + ET__BACKGROUND
#define EVENT__APP_RSP_6						0x4f6 + ET__BACKGROUND
#define EVENT__APP_RSP_7						0x4f7 + ET__BACKGROUND
#define EVENT__APP_RSP_8						0x4f8 + ET__BACKGROUND
#define EVENT__APP_RSP_9						0x4f9 + ET__BACKGROUND
#define EVENT__APP_RSP_A						0x4fa + ET__BACKGROUND
#define EVENT__APP_RSP_B						0x4fb + ET__BACKGROUND
#define EVENT__APP_RSP_C						0x4fc + ET__BACKGROUND
#define EVENT__APP_RSP_D						0x4fd + ET__BACKGROUND
#define EVENT__APP_RSP_E						0x4fe + ET__BACKGROUND
#define EVENT__APP_RSP_F						0x4ff + ET__BACKGROUND

/* ************************************************************************* */
/*
 *	Dial events
 *
 */
#define EVENT__DIAL_TIMER						0x500 + ET__BACKGROUND
#define EVENT__DIAL_BLIND_DIAL_TIMER			0x501 + ET__BACKGROUND
#define EVENT__DIAL_BILLING_DELAY_TIMER			0x502 + ET__BACKGROUND
#define EVENT__DIAL_HOOK_TIMER					0x503 + ET__BACKGROUND
#define EVENT__DIAL_SILENCE_TIMER				0x504 + ET__BACKGROUND

/* ************************************************************************* */
/*
 *	Data protocol events
 *
 */
#define EVENT__DP_SHUTDOWN						0x520 + ET__BACKGROUND
/* 0x6521 is used as EVENT__PROTOCOL_TICK_TIMER above */
#define EVENT__DP_CMD_UNIDLE					0x522 + ET__BACKGROUND
#define EVENT__DP_CMD_DISC						0x523 + ET__BACKGROUND
#define EVENT__DP_CMD_HALT						0x524 + ET__BACKGROUND
#define EVENT__DP_CMD_IDLE						0x525 + ET__BACKGROUND
#define EVENT__V42_CONNECTING					0x526 + ET__BACKGROUND
#define EVENT__V42_DISCONNECTING				0x527 + ET__BACKGROUND
#define EVENT__V42_HALTED						0x528 + ET__BACKGROUND
#define EVENT__V42_IDLEING						0x529 + ET__BACKGROUND
#define EVENT__V42_RUNNING						0x52a + ET__BACKGROUND
#define EVENT__DP_ACCESS_DONE					0x52b + ET__BACKGROUND
#define EVENT__DP_STAT_HALTED					0x52c + ET__BACKGROUND
#define EVENT__DP_STAT_CONNECTING				0x52d + ET__BACKGROUND
#define EVENT__DP_STAT_IDLEING					0x52e + ET__BACKGROUND
#define EVENT__DP_STAT_RUNNING					0x52f + ET__BACKGROUND
#define EVENT__DP_STAT_DISC						0x530 + ET__BACKGROUND
#define EVENT__DP_RSP_HALT						0x531 + ET__BACKGROUND
#define EVENT__DP_LINE_READY					0x532 + ET__BACKGROUND
#define EVENT__DP_INSTALL						0x533 + ET__BACKGROUND
#define EVENT__DP_CMD_UNSUSPEND					0x534 + ET__BACKGROUND
#define EVENT__DP_CMD_SUSPEND					0x535 + ET__BACKGROUND
#define EVENT__DP_STAT_STARTED					0x536 + ET__BACKGROUND
#define EVENT__DP_START_CONTINUE				0x537 + ET__BACKGROUND
#define EVENT__DP_INSTALL_MODULE				0x538 + ET__BACKGROUND
#define EVENT__DP_RESTART						0x539 + ET__BACKGROUND
#define EVENT__DP_RSP_CONNECT					0x53a + ET__BACKGROUND
#define EVENT__DP_RSP_IDLE						0x53b + ET__BACKGROUND
#define EVENT__DP_RSP_UNIDLE					0x53c + ET__BACKGROUND
#define EVENT__DP_RSP_SUSPEND					0x53d + ET__BACKGROUND
#define EVENT__DP_RSP_UNSUSPEND					0x53e + ET__BACKGROUND
#define EVENT__DP_TEST_RETRAIN					0x53f + ET__BACKGROUND
#define EVENT__DP_CMD_CONTINUE					0x540 + ET__BACKGROUND

/* ************************************************************************* */
/*
 * Events for OMC
 *
 */
#define EVENT__DM_CONNECT_LOSS					EVENT__GSTN_CLEARDOWN
#define EVENT__HW_CONNECT_LOSS					EVENT__GSTN_CLEARDOWN
#define EVENT__DM_CONNECT						EVENT__CONNECTION_ON
#define EVENT__OMC_INSTALL_CONTINUE				EVENT__OMC_OVERLAY_CONTINUE

/* ************************************************************************* */
/*
 *	T30 and T4 events
 *
 */
#define EVENT__T30_CMD_FDR						0x560 + ET__BACKGROUND
#define EVENT__T30_CMD_FDT						0x561 + ET__BACKGROUND
#define EVENT__T30_CMD_FET						0x562 + ET__BACKGROUND
#define EVENT__T30_IRSP_DIS						0x563 + ET__BACKGROUND + ET__API
#define EVENT__T30_IRSP_DCS						0x564 + ET__BACKGROUND + ET__API
#define EVENT__T30_IRSP_DTC						0x565 + ET__BACKGROUND + ET__API
#define EVENT__T30_IRSP_CSI						0x566 + ET__BACKGROUND + ET__API
#define EVENT__T30_IRSP_TSI						0x567 + ET__BACKGROUND + ET__API
#define EVENT__T30_IRSP_CIG						0x568 + ET__BACKGROUND + ET__API
#define EVENT__T30_IRSP_NSF						0x569 + ET__BACKGROUND + ET__API
#define EVENT__T30_IRSP_NSS						0x56a + ET__BACKGROUND + ET__API
#define EVENT__T30_IRSP_NSC						0x56b + ET__BACKGROUND + ET__API
#define EVENT__T30_IRSP_FPOLL					0x56c + ET__BACKGROUND + ET__API
#define EVENT__T30_IRSP_FCON					0x56d + ET__BACKGROUND + ET__API
#define EVENT__T30_IRSP_FPTS					0x56e + ET__BACKGROUND + ET__API
#define EVENT__T30_IRSP_FET						0x56f + ET__BACKGROUND + ET__API
#define EVENT__T30_IRSP_VOICE					0x570 + ET__BACKGROUND + ET__API
#define EVENT__T30_IRSP_CFR						0x571 + ET__BACKGROUND + ET__API
#define EVENT__T30_IRSP_PHASE_C_TIMEOUT			0x572 + ET__BACKGROUND + ET__API	/* Will be removed in future */
#define EVENT__T30_RSP_STOP						0x573 + ET__BACKGROUND + ET__API
#define EVENT__T30_KICK_START					0x574 + ET__BACKGROUND
#define EVENT__T30_ACCESS_DONE					0x575 + ET__BACKGROUND
#define EVENT__T30_TIMER						0x576 + ET__BACKGROUND
#define EVENT__T30_INACTIVITY_TIMEOUT			0x577 + ET__BACKGROUND
#define EVENT__T30_TMR_PHASE_C					0x577 + ET__BACKGROUND	/* Will be removed in future */
#define EVENT__T30_TMR_3S						0x578 + ET__BACKGROUND
#define EVENT__T30_TMR_T1						0x579 + ET__BACKGROUND
#define EVENT__T30_TMR_T2						0x57a + ET__BACKGROUND
#define EVENT__T30_TMR_T4						0x57b + ET__BACKGROUND
#define EVENT__T30_TMR_T5						0x57c + ET__BACKGROUND
#define EVENT__T30CR_IRSP_FCON					0x57d + ET__BACKGROUND
#define EVENT__T30CR_RSP_HS_DETECT				0x57e + ET__BACKGROUND
#define EVENT__T30CR_RSP_DISC					0x57f + ET__BACKGROUND
#define EVENT__T30CR_RSP_RX_FRAME				0x580 + ET__BACKGROUND
#define EVENT__T30CR_RSP_TMR_T2					0x581 + ET__BACKGROUND
#define EVENT__T30LINE_RSP_RX_FRAME				0x582 + ET__BACKGROUND
#define EVENT__T30LINE_RSP_OVERFLOW				0x583 + ET__BACKGROUND
#define EVENT__T30LINE_RSP_DIAG					0x584 + ET__BACKGROUND
#define EVENT__T30LINE_RSP_DISC					0x585 + ET__BACKGROUND
#define EVENT__T30LINE_RSP_RTC_DETECT			0x586 + ET__BACKGROUND
#define EVENT__T30LINE_RSP_RCP_DETECT			0x587 + ET__BACKGROUND
#define EVENT__T4_RSP_STOP						0x589 + ET__BACKGROUND
#define EVENT__ECM_RCP_DETECT					0x58a + ET__BACKGROUND
#define EVENT__ECM_RX_RDY						0x58b + ET__BACKGROUND
#define EVENT__ECM_SIM_TICK_TIMER				0x58c + ET__BACKGROUND
#define EVENT__T4_RSP_FORMAT_MISMATCH			0x58d + ET__BACKGROUND
#define EVENT__T30CR_CMD_ABORT					0x58e + ET__BACKGROUND
#define EVENT__T30CR_RSP_ABORT_ACK				0x58f + ET__BACKGROUND
#define EVENT__T30_POST_PPM_TIMER				0x590 + ET__BACKGROUND
#define EVENT__T30_HALT_TIMER					0x591 + ET__BACKGROUND
#define EVENT__T30_INACTIVITY					0x592 + ET__BACKGROUND
#define EVENT__T30_HS_TIMEOUT					0x593 + ET__BACKGROUND
#define EVENT__T4_IN_NMD						0x594 + ET__BACKGROUND
#define EVENT__T4_OUT_NMD						0x595 + ET__BACKGROUND

/* ************************************************************************* */
/*
 *	T38 events
 *
 */
#define EVENT__T38_CED_DETECT					0x5a0 + ET__BACKGROUND
#define EVENT__T38_RSP_STOP						0x5a1 + ET__BACKGROUND
#define EVENT__T38_TIMER						0x5a2 + ET__BACKGROUND
#define EVENT__T38MON_FRAME_READY				0x5a3 + ET__BACKGROUND
#define EVENT__T38LINE_RSP_RX_FRAME				0x5a4 + ET__BACKGROUND
#define EVENT__T38LINE_RTC_RCP_SEEN				0x5a5 + ET__BACKGROUND
#define EVENT__T38LINE_NMD_SEEN					0x5a6 + ET__BACKGROUND
#define EVENT__T38_AFAIL_TIMER					0x5a7 + ET__BACKGROUND
#define EVENT__T38_NFAIL_TIMER					0x5a8 + ET__BACKGROUND
#define EVENT__T38MON_SIG_END					0x5a9 + ET__BACKGROUND
#define EVENT__T38_TX_UNDERFLOW					0x5aa + ET__BACKGROUND
#define EVENT__T38_RX_OVERFLOW					0x5ab + ET__BACKGROUND
#define EVENT__T38_DCS_SEEN						0x5ac + ET__BACKGROUND
#define EVENT__T38_SYSMON_TIMER					0x5ad + ET__BACKGROUND
#define EVENT__T38_CMD_HALT						0x5ae + ET__BACKGROUND
#define EVENT__T38_CMD_DISC						0x5af + ET__BACKGROUND
#define EVENT__T38_SHUTDOWN						0x5b0 + ET__BACKGROUND
#define EVENT__T38_CFR_SEEN						0x5b1 + ET__BACKGROUND
#define EVENT__T38_DATA_SEEN					0x5b2 + ET__BACKGROUND
#define EVENT__T38_SPF_TIMER					0x5b3 + ET__BACKGROUND

/* ************************************************************************* */
/*
 *	CSC events
 *
 */
#define EVENT__CSC_ACCESS_DONE					0x600 + ET__BACKGROUND
#define EVENT__CSC_TIMER						0x601 + ET__BACKGROUND
#define EVENT__CSC_S3_RECEIVED					0x602 + ET__BACKGROUND
#define EVENT__CSC_ESCAPE_REQUEST				0x603 + ET__BACKGROUND
#define EVENT__FC_PULSE_TIMER					0x604 + ET__BACKGROUND
#define EVENT__RSP_DONE							0x605 + ET__BACKGROUND
#define EVENT__CSC_RI_TIMER						0x606 + ET__BACKGROUND
#define EVENT__CSC_CONNECT						0x607 + ET__BACKGROUND
#define EVENT__CSC_DISCONNECT					0x608 + ET__BACKGROUND
#define EVENT__CSC_RING							0x609 + ET__BACKGROUND
#define EVENT__CSC_RESET						0x60a + ET__BACKGROUND
#define EVENT__CSC_START						0x60b + ET__BACKGROUND
#define EVENT__CSC_RESET_REQUEST				0x60c + ET__BACKGROUND
#define EVENT__CSC_RSP_DONE						0x60d + ET__BACKGROUND
#define EVENT__CSC_HANGUP_REQUEST				0x60e + ET__BACKGROUND
#define EVENT__CSC_ACCESS_CONTINUE				0x60f + ET__BACKGROUND
#define EVENT__CSC_AUTOANSWER_REQ				0x610 + ET__BACKGROUND
#define EVENT__CSC_CMD_ENTRY_TIMER				0x611 + ET__BACKGROUND
#define EVENT__TIES_FAILURE						0x612 + ET__BACKGROUND
#define EVENT__TIES_PROMPT						0x613 + ET__BACKGROUND
#define EVENT__TIES_SUCCESS						0x614 + ET__BACKGROUND
#define EVENT__V24_DTR_DEBOUNCE_TIMER			0x615 + ET__BACKGROUND
#define EVENT__V24_DTR_TIMER					0x616 + ET__BACKGROUND
#define EVENT__V24_RTS_TIMER					0x617 + ET__BACKGROUND
#define EVENT__V24_DCD_TIMER					0x618 + ET__BACKGROUND
#define EVENT__CSC_VOICE_REQUEST				0x619 + ET__BACKGROUND
#define EVENT__RING_CNT_CLEARED_TIMER			0x61a + ET__BACKGROUND
#define EVENT__CSC_CID_PROC_DONE				0x61b + ET__BACKGROUND
#define EVENT__CSC_TONE_REPORT_TIMER			0x61c + ET__BACKGROUND
#define EVENT__CSC_MONITOR_SERVICE				0x61d + ET__BACKGROUND
#define EVENT__CSC_RECENT_WAKEUP_TIMER			0x61e + ET__BACKGROUND
#define EVENT__CSC_PD_REQUEST					0x61f + ET__BACKGROUND
#define EVENT__CSC_PD_WAKEUP					0x620 + ET__BACKGROUND
#define EVENT__CSC_VOICE_MONITOR_TIMER			0x621 + ET__BACKGROUND
#define EVENT__CSC_VOICE_TONE_TIMER				0x622 + ET__BACKGROUND
#define EVENT__CSC_VOICE_TIMER					0x623 + ET__BACKGROUND
#define EVENT__CSC_VOICE_INBAND_CMD				0x624 + ET__BACKGROUND
#define EVENT__CSC_VOICE_SILENCE_TIMER			0x625 + ET__BACKGROUND
#define EVENT__RING_TO_ANSWER_DURATION			0x627 + ET__BACKGROUND

/* ************************************************************************* */
/*
 *	FX1 events
 *
 */
#define EVENT__FX1_CMD_FRH						0x632 + ET__BACKGROUND
#define EVENT__FX1_CMD_FTH						0x633 + ET__BACKGROUND
#define EVENT__FX1_CMD_FRM						0x634 + ET__BACKGROUND
#define EVENT__FX1_CMD_FTM						0x635 + ET__BACKGROUND
#define EVENT__FX1_CMD_FRS						0x636 + ET__BACKGROUND
#define EVENT__FX1_CMD_FTS						0x637 + ET__BACKGROUND
#define EVENT__FX1_CMD_START					0x638 + ET__BACKGROUND
#define EVENT__FX1_RSP_CONNECT					0x639 + ET__BACKGROUND
#define EVENT__FX1_RSP_OK						0x63a + ET__BACKGROUND
#define EVENT__FX1_RSP_ERROR					0x63b + ET__BACKGROUND
#define EVENT__FX1_RSP_FCERROR					0x63c + ET__BACKGROUND
#define EVENT__FX1_RSP_NO_CARRIER				0x63d + ET__BACKGROUND
#define EVENT__FX1_RSP_DONE						0x63e + ET__BACKGROUND
#define EVENT__FX1_RSP_TX_SPECIAL				0x63f + ET__BACKGROUND
#define EVENT__FX1_ACCESS_DONE					0x641 + ET__BACKGROUND
#define EVENT__FXLINE_NONFINAL_SENT				0x642 + ET__BACKGROUND
#define EVENT__FXLINE_NO_MORE_DATA				0x643 + ET__BACKGROUND
#define EVENT__FXLINE_RX_FRAME					0x644 + ET__BACKGROUND
#define EVENT__FX1_DISC_TIMER					0x645 + ET__BACKGROUND

/* ************************************************************************* */
/*
 *	FX2 events
 *
 */
#define EVENT__FX2_DTE_ABORT_TIMER				0x653 + ET__BACKGROUND

/* ************************************************************************* */
/*
 *	DTEIF
 *
 */
#define EVENT__DTEIF_DTR_ON						0x660 + ET__BACKGROUND
#define EVENT__DTEIF_DTR_OFF					0x661 + ET__BACKGROUND
#define EVENT__DTEIF_RTS_ON						0x662 + ET__BACKGROUND
#define EVENT__DTEIF_RTS_OFF					0x663 + ET__BACKGROUND
#define EVENT__DTEIF_AT_PREFIX_SEEN				0x664 + ET__BACKGROUND
#define EVENT__DTEIF_REPEAT_PREV_CMD			0x665 + ET__BACKGROUND
#define EVENT__SERIAL_CTS_FALL					0x666 + ET__BACKGROUND
#define EVENT__SERIAL_CTS_RISE					0x667 + ET__BACKGROUND
#define EVENT__SERIAL_DCD_FALL					0x668 + ET__BACKGROUND
#define EVENT__SERIAL_DCD_RISE					0x669 + ET__BACKGROUND

/* ************************************************************************* */
/*
 *	DTE events
 *
 */
#define EVENT__DTE_TX_BREAK						0x66e + ET__BACKGROUND
#define EVENT__DTE_RX_BREAK						0x66f + ET__BACKGROUND
#define EVENT__DTE_FX1_DONE						0x670 + ET__BACKGROUND
#define EVENT__DTE_FX2_DONE						0x671 + ET__BACKGROUND
#define EVENT__DTE_FDR_DC2_SEEN					0x672 + ET__BACKGROUND
#define EVENT__DTE_FDR_CAN_SEEN					0x673 + ET__BACKGROUND
#define EVENT__DTE_FDR_CHAR_SEEN				0x674 + ET__BACKGROUND
#define EVENT__DTE_POST_CMD_ECHO_TIMER			0x675 + ET__BACKGROUND
#define EVENT__DTE_ONLINE_ESCAPE_TIMER			0x676 + ET__BACKGROUND
#define EVENT__DTE_ONLINE_ESCAPE_SUCCESS		0x678 + ET__BACKGROUND
#define EVENT__DTE_ONLINE_ESCAPE_FAIL			0x679 + ET__BACKGROUND
#define EVENT__DTE_NOCHAR_INTERVAL_TIMER		0x67a + ET__BACKGROUND
#define EVENT__DTE_CHAR_SEEN					0x67b + ET__BACKGROUND
#define EVENT__DTE_ONLINE_ESCAPE_START			0x67c + ET__BACKGROUND
#define EVENT__DTE_VOICE_STOP					0x67d + ET__BACKGROUND
#define EVENT__DTE_TX_EMPTY						0x67e + ET__BACKGROUND
#define EVENT__DTE_RX_OVERFLOW					0x67f + ET__BACKGROUND

/* ************************************************************************* */
/*
 *	Serial Interface events
 *
 */
#define EVENT__SERIAL_DSR_ON					0x680 + ET__BACKGROUND
#define EVENT__SERIAL_DSR_OFF					0x681 + ET__BACKGROUND
#define EVENT__SERIAL_DTR_ON					0x682 + ET__BACKGROUND
#define EVENT__SERIAL_DTR_OFF					0x683 + ET__BACKGROUND
#define EVENT__SERIAL_DCD_ON					0x684 + ET__BACKGROUND
#define EVENT__SERIAL_DCD_OFF					0x685 + ET__BACKGROUND
#define EVENT__SERIAL_CTS_ON					0x686 + ET__BACKGROUND
#define EVENT__SERIAL_CTS_OFF					0x687 + ET__BACKGROUND
#define EVENT__SERIAL_RTS_ON					0x688 + ET__BACKGROUND
#define EVENT__SERIAL_RTS_OFF					0x689 + ET__BACKGROUND
#define EVENT__SERIAL_105_ON					0x68a + ET__BACKGROUND
#define EVENT__SERIAL_105_OFF					0x68b + ET__BACKGROUND
#define EVENT__SERIAL_RI_ON						0x68c + ET__BACKGROUND
#define EVENT__SERIAL_RI_OFF					0x68d + ET__BACKGROUND
#define EVENT__SERIAL_HOOK_ON					0x68e + ET__BACKGROUND
#define EVENT__SERIAL_HOOK_OFF					0x68f + ET__BACKGROUND
#define EVENT__BUFFER1_TX_EMPTY					0x690 + ET__BACKGROUND
#define EVENT__BUFFER1_RX_EMPTY					0x691 + ET__BACKGROUND

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */
/*
 *	Fax app (fxapp) control
 *
 */
#define EVENT__FXAPP_ENABLE						0x6a0 + ET__BACKGROUND
#define EVENT__FXAPP_DISABLE					0x6a1 + ET__BACKGROUND
#define EVENT__FXAPP_RECV						0x6a2 + ET__BACKGROUND
#define EVENT__FXAPP_SEND						0x6a3 + ET__BACKGROUND
#define EVENT__FXAPP_SEND_TEST					0x6a4 + ET__BACKGROUND
#define EVENT__FXAPP_ON_HOOK					0x6a5 + ET__BACKGROUND
#define EVENT__FXAPP_OFF_HOOK					0x6a6 + ET__BACKGROUND
#define EVENT__FXAPP_V34RECV					0x6a7 + ET__BACKGROUND

/* ************************************************************************* */
/*
 *	Voice record/playback (dtam) control
 *
 */
#define EVENT__DTAM_ENABLE						0x6b0 + ET__BACKGROUND
#define EVENT__DTAM_DISABLE						0x6b1 + ET__BACKGROUND
#define EVENT__DTAM_PLAYBACK_END				0x6b2 + ET__BACKGROUND
#define EVENT__DTAM_RECORD_END					0x6b3 + ET__BACKGROUND

/* ************************************************************************* */
/*
 *	Define VoIP events
 *
 */
#define EVENT__SIP_TIMER						0x6e0 + ET__BACKGROUND
#define EVENT__MGCP_TIMER						0x6e1 + ET__BACKGROUND
#define EVENT__MGCP_CA_STARTUP					0x6e2 + ET__BACKGROUND
#define EVENT__MGCP_CA_ENDPOINT_FOUND			0x6e3 + ET__BACKGROUND
#define EVENT__MGCP_CA_MODIFY_CONNECTION		0x6e4 + ET__BACKGROUND
#define EVENT__MGCP_CA_MODIFY_SHUTDOWN			0x6e5 + ET__BACKGROUND
#define EVENT__MGCP_CA_RECVD_CW_MDCX_RSP		0x6e6 + ET__BACKGROUND
#define EVENT__MGCP_CA_MODIFY_HF_CALL_WAITING	0x6e7 + ET__BACKGROUND
#define EVENT__MGCP_CA_MODIFY_ON_HOLD			0x6e8 + ET__BACKGROUND
#define EVENT__MGCP_CA_SEND_DIALTONE			0x6e9 + ET__BACKGROUND
#define EVENT__MGCP_CA_SEND_CALL_WAITING		0x6ea + ET__BACKGROUND
#define EVENT__MGCP_CA_MODIFY_CONNECTION_HOLD   0x6eb + ET__BACKGROUND

#define EVENT__MGCP_RSP_HOOKFLASH				0x6f0 + ET__BACKGROUND
#define EVENT__MGCP_CMD_DLCX					0x6f1 + ET__BACKGROUND

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */
/*
 *	Developer temporary events
 *
 */
#define EVENT__DEVELOPER_GROUP					0x700 + ET__REPORT
#define EVENT__TEST_R1							0x701 + ET__REPORT
#define EVENT__TEST_R2							0x702 + ET__REPORT
#define EVENT__TEST_R3							0x703 + ET__REPORT

/* ************************************************************************* */
/*
 *	Customer events
 *
 */
#define EVENT__CUSTOMER_GROUP					0x7c0 + ET__REPORT

#define EVENT__FAXMON_CMD_GO					0x7c1 + ET__REPORT
#define EVENT__FAXMON_RSP_FF					0x7c2 + ET__REPORT

/* ************************************************************************* */

#endif /* _INCLUDE_EVENTS_H */
