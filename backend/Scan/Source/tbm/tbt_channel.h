/* Copyright (c) 2001 by Medtronic Inc.  All Rights Reserved */
/********************************************************************
DOCUMENT

$Revision$
$Date$
$RCSfile$

NAME:
  tbt_channel.h

PURPOSE:
  This include file contains the type definitions used
  for the interface between Telemetry Channel and the Telemetry
  Link layer.

ENDDOCUMENT
********************************************************************/

#ifndef tbt_channel_h
#define tbt_channel_h

#include "global.h"
#include "tbt_queue.h"

/* Telemetry B frame constants. */
#define TBC_PROTOCOL_SOM_U        0xe0
#define TBC_PROTOCOL_SOM_L        0x02
#define TBC_PROTOCOL_REJECT       0xe0
#define TBC_PROTOCOL_DEV_ID_RR    0xc0
#define TBC_PROTOCOL_OPEN_SESS_RR 0xc1
#define TBC_PROTOCOL_CLOSE_SESS   0xc2
#define TBC_PROTOCOL_CC_DEV_ID    0x00
#define TBC_PROTOCOL_CC_OPEN      0x01
#define TBC_PROTOCOL_CC_CLOSE     0x02

#define TBC_PROTOCOL_OVERHEAD 0x03      /* 3 Bytes, DLH, and PrgmID */

#define TBC_APP_UL_OVERHEAD        0x02 /* 2 Bytes, DLH and cmdCode */
#define TBC_APP_TAG_FIELD_BYTE     0x07
#define TBC_APP_REQUESTED_RR       0x40 /* + tag */
#define TBC_APP_REQUESTED_REJECT   0x48 /* + tag */
#define TBC_APP_REQUESTED_UPLINK   0x60 /* + tag */
#define TBC_APP_UNREQUESTED_UPLINK 0x20
#define TBC_PROTOCOL_DL_ID_BYTE    4
#define TBC_PROTOCOL_DL_CC_BYTE    2
#define TBC_START_OF_MSG_BYTE_SIZE 2
/*  The maximum I field size permitted by Telemetry B Protocol is 256 bytes.  However,
the 2490 Telemetry B instrument has selected 32 as it's maximum I field size.  This
selection was based on the Marquis implementation which has a maximum i-field size of 25.
The largest message size permitted by Telemetry B Protocol is 310 bytes; therefore a maximum
of 13 Telemetry B frames would be required to downlink a message of that size. */
#define TBC_MAX_DL_IFIELD_SIZE    32 /* Either Protocol or App Data Downlink i-field size. */
#define TBC_DL_FRAME_Q_SIZE       16
#define TBC_MAX_MSG_REQ_BYTE_SIZE 310

#define TBC_MAX_UPLINK_BYTE_SIZE 256
#define TBC_UL_FRAME_Q_SIZE      8

#define TBC_DEVICE_ID_BYTE_SIZE       6
#define TBC_MAX_NUMBER_OF_DEVICES     16 /*Maximum number of devices auto id can find. */
#define TBC_MAX_TARGETS_PER_DEVICE_ID 4     /*Maximum number of devices allowed in the
                                               Device ID Request. */
#define TBC_DEVICE_ID_RESP_WINDOW     600 /* The time interval that the instrument will continue
                                           to listen for Device ID Responses after issuing the
                                           Device ID Request. */

typedef enum tbt_syncCharType
{
    tbc_sc_normal        = 0,   /* nomal sync char */
    tbc_sc_extended      = 1,   /* extended sync char */
    tbc_end_syncCharType = 0x4000
}
tbt_syncCharType;

typedef USHORT tbt_dataRateRangeType;

typedef enum tbt_dataRateType
{
    tbc_dr_21        = 0x0002,  /* 21.875 */
    tbc_dr_87        = 0x0008,  /* 87.5   */
    end_dataRateType = 0x4000
}
tbt_dataRateType;

/* Telemetry B Open Data Rate Definitions. */
#define TBC_OPEN_DATA_RATE_021 0x01
#define TBC_OPEN_DATA_RATE_087 0x03

/* This defines the type of frame being transmitted */

typedef enum tbt_dlFrameHeader
{
    tbt_dlInvalid     = 0,
    tbt_dlData        = 1,
    tbt_dlUFrame      = 2,
    tbt_dlUFrameOpen  = 3,
    tbt_dlAck         = 4,
    tbt_dlNak         = 5,
    tbt_dlHandshake   = 6,
    tbt_dlWak         = 7,
    tbt_dlUFrameClose = 8,
    tbt_dlEnd         = 0x7fff
}
tbt_dlFrameHeader;

/* The current status of a downlink frame */

typedef enum tbt_txFrameStatus
{
    tbt_txNoStatus          = 0,
    tbt_txInQueue           = 1,
    tbt_txInProgress        = 2,
    tbt_txInProgressNoRetry = 3,
    tbt_txComplete          = 4,
    tbt_txAcked             = 5,
    tbt_txEnd               = 0x7fff
}
tbt_txFrameStatus;

typedef struct tbt_dlFrameType
{
    USHORT length;              /* len of dl Hdr, pgmrId, I Field  */
    USHORT finalFrame;          /* TRUE for final frame,up/down link */
    tbt_syncCharType syncType;  /* sync char used for protocol downlink */
    tbt_dataRateType uplinkRate;
    tbt_dlFrameHeader frameType;
    tbt_txFrameStatus status;
    USHORT attemptCount;
    BYTE reserved1;
    BYTE dlHeader;
    BYTE pgmrId[2];
    /*
       information field starts here
     */
    BYTE infoField[TBC_MAX_DL_IFIELD_SIZE];
    BYTE CRC[2];
}
tbt_dlFrameType;

typedef struct tbt_ulWaveFormType
{
    USHORT length;              /* len of dl Hdr, pgmrId, I Field  */
    USHORT finalFrame;          /* TRUE for final frame,up/down link */
    BYTE reservedByte1;
    BYTE dlHeader;
    BYTE pgmrId[2];
    BYTE infoField[TBC_MAX_UPLINK_BYTE_SIZE];   /* information field starts here */
    BYTE CRC[2];
}
tbt_ulWaveFormType;

typedef struct tbt_ulNonWaveFormType
{
    USHORT length;              /* len of dl Hdr, cmdCode, I Field        */
    USHORT finalFrame;          /* TRUE for final frame,up/down link */
    BYTE reservedByte1;
    BYTE dlHeader;
    BYTE cmdCode;
    BYTE infoField[TBC_MAX_UPLINK_BYTE_SIZE];   /* information field starts here */
    BYTE CRC[2];
}
tbt_ulNonWaveFormType;

/**********************************************
 *   Telemetry Request (downlink) Types
 **********************************************/
#define    TBC_IDALL   0x0401
#define    TBD_OPEN    0x0404
#define    TBC_CLOSE   0x0405
#define    TBC_APPDATA 0x0408

/****************************************************************
DATATYPE:
  tbt_dlFrameQ

DESCRIPTION/USE:
  This queue is used to store downlink frames until they
  can be transmitted by the Telemetry Link layer.

VALUES:
  A queue data structure consists of a queue header
  followed by space for the queue entries.

****************************************************************/

typedef struct tbt_dlFrameQ
{
    tbt_queueHeader header;
    void *dlFrames[TBC_DL_FRAME_Q_SIZE];
}
tbt_dlFrameQ;

/****************************************************************
DATATYPE:
  tbt_ulFrameQ

DESCRIPTION/USE:
  This queue is used to store uplink frames until they
  can be processed by the Telemetry Channel layer.

VALUES:
  A queue data structure consists of a queue header
  followed by space for the queue entries.

****************************************************************/

typedef struct tbt_ulFrameQ
{
    tbt_queueHeader header;
    void *ulFrames[TBC_UL_FRAME_Q_SIZE];
}
tbt_ulFrameQ;

#endif /* end  tbt_channel_h */
