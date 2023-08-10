/* Copyright (c) 2001 by Medtronic Inc.  All Rights Reserved */
/********************************************************************

NAME:     link.h

PURPOSE:  This header file contains many of the defines, types, and
sturctures used by the Link Layer.

*************************************************************************/
#ifndef link_h
#define link_h
#include "tbt_channel.h"
#include "..\types.h"

/* Some DEBUG defines, should be commented out for */
/* release code
#define DEBUG_VARS_ON
#define DEBUG_STATE
#define DEBUG_ON
#define DEBUG_SIZE 300
#define LED_DEBUG */

/* WACK packet define */
#define TBC_no_wack 0xffff

/* Downlink Flag Byte Define */
#define TBC_flag 0x7e

/* Downlink Frame Header Defines */

#define TBC_dlHeaderUFrameMode1 0x58
#define TBC_dlHeaderUFrameMode0 0x48
#define TBC_dlAck               0x90
#define TBC_dlNak               0xD0
#define TBC_dlHandshake         0x59

#define TBC_seqMask 0x07

/* Uplink Frame header Defines */
/* with Numbered portion masked */

#define TBC_ulWf    0xff
#define TBC_ulufmd0 0x80
#define TBC_ulufmd1 0xA0
#define TBC_ulufmd2 0xC0
#define TBC_ulufmd3 0xE0

#define TBC_ulNak 0xB8
#define TBC_ulAck 0xB0

#define TBC_ulwfmd0 0x08
#define TBC_ulwfmd1 0x28
#define TBC_ulwfmd2 0x48
#define TBC_ulwfmd3 0x68

#define TBC_ulwfmd1p 0x38
#define TBC_ulwfmd3p 0x78

#define TBC_uldfmd1  0x20
#define TBC_uldfmd1f 0x30

/* This defines the type of frame being received (uplinked) */

typedef enum tbt_ulFrameHeader
{
    tbt_ulInvalid = 0,
    tbt_ulData    = 1,
    tbt_ulDataf   = 2,
    tbt_ulDatasb  = 3,
    tbt_ulUFrame  = 4,
    tbt_ulAck     = 5,
    tbt_ulAcksb   = 6,
    tbt_ulNak     = 7,
    tbt_ulNaksb   = 8,
    tbt_ulWf      = 9,
    tbt_ulWfp     = 10,
    tbt_ulWfmmID  = 11
}
tbt_ulFrameHeader;

/* Two types of sync, normal or extended */

typedef enum tbt_syncType
{
    tbt_normal   = 0,
    tbt_extended = 1
}
tbt_syncType;

/* A structure to follow status of a downlink frame */

typedef struct tbt_txFrameType
{
    tbt_syncType sync;
    tbt_dlFrameHeader frameType;
    BYTE header;
    tbt_txFrameStatus status;
    BYTE attemptCount;
}
tbt_txFrameType;

/* The ACK, NAK, Handshake - queue */
typedef struct tbt_dlAckNakHandshakeQ
{
    BYTE length;
    BYTE header;
    USHORT programmerID;

}
tbt_dlAckNakHandshakeQ;

/* A structure to track some current uplink information */

typedef struct tbt_rxFrameType
{
    BYTE headerType;
    BYTE header;
    void (*processFunction)(void);
}
tbt_rxFrameType;

/* The following variables are DEBUG variables */
/* The tracking of these variables are set by enabling */
/* the define "DEBUG_VARS_ON */

typedef struct
{
    unsigned handshakesStarted;
    unsigned handshakesCompleted;
    unsigned wacksStarted;
    unsigned wacksCompleted;
    unsigned maxAttempts;
    unsigned openingFlags;
    unsigned openingFlagErrors;
    unsigned openingFlag;
    unsigned EOFsFound;
    unsigned EOFsExecuted;
    unsigned EOFErrors;
    unsigned noSync;
    unsigned crcErrors;
    unsigned aborts;
    unsigned underruns;
    unsigned overruns;
    unsigned others;
    unsigned restarts;
    unsigned goodFrames;
    unsigned trxFrames;
    unsigned uFrames;
    unsigned wfFrames;
    unsigned dataFrames;
    unsigned dataFramesBadSequence;
    unsigned invalidFrames;
    unsigned uplinksUnknown;
    unsigned mismatchPgmrID;
    unsigned missingWFs;
    unsigned consecutiveWFs;
    unsigned duplicateWFs;
    unsigned mode3Waveforms;
    unsigned char startedTransmitting;
    unsigned char state;
    unsigned char inListenMode;
    unsigned char listenMode87;
    unsigned char listenMode21;
    unsigned lostSync;

} typeDebugArray;

/* The following enums tbt_stateType are DEBUG variables */
/* The tracking of these "states" are set by enabling */
/* the define "DEBUG_STATE */
/* These enums show the state of the Link Layer while it's */
/* going through many of the functions of the Link Layer */
/* STATE_ARRAY_SIZE is where the state types are stored */

#define STATE_ARRAY_SIZE 256
#define STATE_MASK       0xff

typedef enum tbt_stateType
{
    tbt_zero     = 0,
    tbt_wackSent = 30,
    tbt_downlinkSent,
    tbt_downlinkSentInvalid,
    tbt_wackComplete,
    tbt_downlinkHSComplete,
    tbt_downlinkACKNAKSent,
    tbt_downlinkDataSent,
    tbt_downlinkUFrameComplete,
    tbt_downlinkOpenComplete,
    tbt_listenForUplink,
    tbt_listenEntered21,
    tbt_listenEntered87,
    tbt_uplinkStarted,
    tbt_uplinkStartedUnknown,
    tbt_uplinkComplete,
    tbt_handshakeAcknowledged,
    tbt_handshakeAcknowledgedByAck,
    tbt_handshakeSentWaitingAck,
    tbt_dataFrameSentWaitingAck,
    tbt_handshakeSentRetry,
    tbt_uplinkStartedDFsg,
    tbt_uplinkStartedDFsgf,
    tbt_uplinkStartedDFsb,
    tbt_uplinkStartedWF,
    tbt_uplinkStartedUF,
    tbt_uplinkStartedWFp,
    tbt_uplinkStartedNak,
    tbt_uplinkStartedNaksg,
    tbt_uplinkStartedNaksb,
    tbt_uplinkStartedAck,
    tbt_uplinkCompleteWF,
    tbt_uplinkCompleteWFmmID,
    tbt_uplinkCompleteDFsb,
    tbt_uplinkCompleteDFsgNofinal,
    tbt_uplinkCompleteDFsgFinalBit,
    tbt_uplinkCompleteInvalid,
    tbt_uplinkCompleteWFp,
    tbt_uplinkCompleteWFpNothingAcked,
    tbt_uplinkCompleteUFrame,
    tbt_uplinkCompleteWFpDFAcknowledged,
    tbt_uplinkCompleteAckDFAcknowledged,
    tbt_uplinkCompleteNakDFAcknowledged,
    tbt_uplinkCompleteGoodCRC,
    tbt_uplinkCompleteBadCRC,
    tbt_uplinkCompleteACK,
    tbt_uplinkCompleteACKsb,
    tbt_uplinkCompleteNAK,
    tbt_uplinkCompleteNAKsb,
    tbt_uplinkError,
    tbt_receiveISR,
    tbt_transmitISR,
    tbt_badISR,
    tbt_null,
    tbt_shortTimeout,
    tbt_hitMaxRetriesData,
    tbt_hitMaxRetriesDataByNak,
    tbt_hitMaxRetriesHS,
    tbt_HStimerExpire,
    tbt_timerExpire,
    tbt_ChannelWFQueued,
    tbt_ChannelWFProcessed,
    // I added these (JAB)
    tbt_telemBDataStarted,
    tbt_telemBDataCompleted,
    // End added.
    tbt_last = 0x7000
}
tbt_stateType;

#endif
