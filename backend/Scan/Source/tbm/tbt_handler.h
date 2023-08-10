/* Copyright (c) 2001 by Medtronic Inc.  All Rights Reserved */
/********************************************************************
DOCUMENT

$Revision$

$Date$

$RCSfile$

NAME:    tbt_handler.h  types for telemetry B

PURPOSE: Controls the format of data passed between IRM Application
         functions and the Telemetry B functions.

ENDDOCUMENT
*************************************************************************/

#ifndef tbt_handler_h
#define tbt_handler_h

#include "..\types.h"
#include "tbt_channel.h"

typedef enum tbt_reqStatus
{
    tbc_successful      = 0,
    tbc_not_successful  = 1,    /* reserved for the types of failures which
                                   can be recovered if the request is retried. */
    tbc_telemetry_abuse = 2,    /* reserved for requests which mis use the
                                   telemetry module interfaces. */
    tbc_fail            = 3,    /* reserved for the types of failures that
                                   require a power cycle. */
    tbc_end_reqStatus   = 0x7000 /* Force to 16 bits. */
}
tbt_reqStatus;

/* Device ID entry */
typedef struct tbt_devIdEntry
{
    BYTE modelIDHigh;
    BYTE modelIDLow;
    BYTE subModelID;
    BYTE serialNumberHigh;
    BYTE serialNumberMed;
    BYTE serialNumberLow;
}
tbt_devIdEntry;

/**********************************************
 *   Response Buffer Formats
 **********************************************/
/* Buffer header for uplink data. This is the format for each individual telemetry
frame added to the response buffer.  Note the header will be followed by the data
from the actual uplink frame.*/
#define TBC_UPLINK_RESP_ENTRY_HEADER_SIZE 3

/* Buffer header for Downlink Application Data Feature. Note the header will
be followed by the data from the actual uplink frame, the length of which
may vary.  This is the format for the entire response buffer starting from
the beginning.  */
#define TBC_APPDATA_RESP_BUFFER_HEADER_SIZE 4

/*   Buffer format for Auto ID Response.  This is the format for the entire
     response buffer starting from the beginning.      */
typedef struct tbt_autoIDRespType
{
    USHORT numberFound;
    tbt_devIdEntry response[TBC_MAX_NUMBER_OF_DEVICES]; /* max 16 entries */
}
tbt_autoIDRespType;

/************************************************************
Values for the Config B Table.
*************************************************************
*/
typedef UINT16 tbt_procCfgOptionsType;

/* bit definition of  tbt_procCfgOptionsType */
/* bit 0 -- 0 = Do not WAK Waveform,
         -- 1 = WAK Waveform */
#define TBC_NO_WAK_WAVEFORM_FRAMES 0x0000
#define TBC_WAK_WAVEFORM_FRAMES    0x0001
/* bit 1 -- 0 = Normal Gain Mode,
         -- 1 = Reduced Gain Mode */
#define TBC_NORMAL_GAIN_MODE  0x0000
#define TBC_REDUCED_GAIN_MODE 0x0002
/* bit 4 -- 0 = Downlink ACK/NAK after Waveform,
         -- 1 = Downlink ACK/NAK immediately */
#define TBC_NO_IMMEDIATE_ACK_NAK 0x0000
#define TBC_IMMEDIATE_ACK_NAK    0x0010
/* bit 5 -- 0 = Normal operation.
         -- 1 = If device uplinks address 3 in header indicating
                rexmitted WF we will withhold all pending downlinks.
*/
#define TBC_NO_DL_ON_WF_REXMIT 0x0020
#define TBC_DL_ON_WF_REXMIT    0x0000

/************************************************************
The Config B Table format.
*************************************************************
*/
typedef struct tbt_configBTableType
{
    USHORT tableLabel;          /* not used in 2490 */
    UINT32 tableDate;    /* MMDDYYYY, not used in 2490 */
    tbt_dataRateRangeType dataRateSupported;
    tbt_dataRateType defaultDataRate;
    USHORT modelID;
    UINT16 subModelID;
    tbt_procCfgOptionsType protocolConfigOptions;
    USHORT maxRetriesAsynchMessages;
    USHORT maxRetriesSyncMessages;
    USHORT minHandshakeInterval;    /* ms */
    USHORT instShortTimeout;    /* ms */
    USHORT maxDlIFieldSize2187; /* bytes */
    USHORT maxUlIFieldSize2187; /* bytes */
    USHORT maxAvgWFInterval2187;    /* ms */
    USHORT maxDlIFieldSize8750; /* bytes */
    USHORT maxUlIFieldSize8750; /* bytes */
    USHORT maxAvgWFInterval8750;    /* ms */
    USHORT maxDlIFieldSize175;  /* bytes */
    USHORT maxUlIFieldSize175;  /* bytes */
    USHORT maxAvgWFInterval175; /* ms */
    USHORT maxDownlinkMsgSize;  /* bytes */
    USHORT maxUplinkMsgSize;    /* bytes */
    USHORT telemBReqRespTimeout;    /* ms */
    /*
       time to receive uplink Frame, protocol or first mem uplink
     */
    USHORT memUplinkRespTimeout;    /* ms */
    /*
       time to receive consecutive mem uplink frame
     */
    USHORT numDataFrameBeforeAckNak;
    USHORT uiOptions;           /* not used in 2490 */
    USHORT emergencyManagement; /* not used in 2490 */
    USHORT reserved;
    USHORT numDataZeroInSyncChar;
    USHORT deviceIdQuietTime;   /* ms */
    USHORT deviceIdRespTime;    /* ms */
    USHORT deviceQuietTimeAfterOpenSession; /* sec */
    USHORT deviceShortTimeout;  /* ms */
    USHORT deviceSessionTimeout;    /* ms */
    USHORT defaultTXPower;      /* not used in 2490 */
    USHORT diagnosticMode;      /* not used in 2490 */
    USHORT tableChecksum;       /* not used in 2490 */
}
tbt_configBTableType;

/************************************************************
Telemetry B Channel Layer Items.
*************************************************************
*/

typedef struct tbt_sessionType
{
/* Telemetry Parameters */
    tbt_reqStatus sessionStatus;
    tbt_dlFrameType openSessFrame;
    tbt_dlFrameType deviceIDFrame;
/* Auto ID Request Parameters. */
    tbt_autoIDRespType *DeviceIDRespPtr;
/* Common Data Request Parameters. */
    tbt_devIdEntry *TargetDeviceIDPtr;
    USHORT ProgrammerID;
    tbt_configBTableType *ConfigBPtr;
    USHORT *bufferUsedLengthPtr;
    BYTE *RespPtr;              /* either Uplink or AppData */
    UINT16 MaxBufferSize;          /* either Uplink or AppData */
/* Uplink Data Request Parameters. */
    UINT16 UplinkSampleTime;
/* Application Data Request Parameters. */
    BYTE *AppDataReqPtr;
    UINT16 AppDataReqLen;
    UINT16 FirstULRespTime;
}
tbt_sessionType;

/*
**************************************************************************
The type tbt_uplinksReqEntry contains the following parameters.
    targetIDPtr - a pointer to the device ID of the device with which to
       open a telemetry B session.
    progID - the programmer ID which is used in communicating with
      a telemetry B device.
    configBPtr - a pointer to the configuration B table which defines device
      specific telemetry B parameters about the target device.
    bufferUsedLengthPtr - a point to the location at which to store the actual
       length used of the response buffer.
    respBufferPtr - a pointer to a location at which to store the device uplinks
      captured within the time defined by tbv_UplinkSampleTime and
      not exceeding the available buffer size defined by respBufferSize. The
      length of buffer actually filled by this request is reported in the
      'bufferUsedLengthPtr' response.  The contents of this buffer are structured
      as follows:
          header 1
          frame 1 information field
          header 2
          frame 2 information field
          ...
          header N
          frame N information field
       The format of each header is as follows:
          word 0:  length of this frame's information field
          byte 2:  0x00
          byte 3:  Frame Type Specifier (Note: the actual Data Link Header of this frame
                   is used here as defined in the Telemetry B Protocol Specifiation #217420.)
          byte 4...byte M:  this frame's information field
      (Note: Telemtry B Information Fields are defined in the Telemetry B Protocol
      Specifiation #217420.)
    respBufferSize - value which defines the size of the buffer available
      at respBufferPtr
    uplinkListenTime - value in seconds which defines the amount of time during
      which to capture EGM data.
***************************************************************************
*/

typedef struct tbt_uplinksReqEntry
{
    tbt_devIdEntry *targetIDPtr;
    USHORT progID;
    tbt_configBTableType *configBPtr;
    USHORT *bufferUsedLengthPtr;
    BYTE *respBufferPtr;
    UINT16 respBufferSize;
    UINT16 uplinkListenTime;
}
tbt_uplinksReqEntry;

/*
**************************************************************************
The type tbt_appDataReqEntry contains the following parameters.
    targetIDPtr - a pointer to the device ID of the device with which to
       pen a telemetry B session.
    progID - the programmer ID which is used in communicating with
      a telemetry B device.
    configBPtr - a pointer to the configuration B table which defines device
       specific telemetry B parameters about the target device.
    bufferUsedLengthPtr - a point to the location at which to store the actual
       length used of the response buffer.
    respBufferPtr - a pointer to the location at which to store the Application
       Data response from the device.  The maximum size of this buffer is defined
       by tbv_AppDataMaxBufferSize.  The length of buffer actually filled by this
       request is reported in the 'bufferUsedLengthPtr' response.  The contents of
       this buffer are structured as follows:
          byte 0:  0x00
          byte 1:  uplink command code
          byte 2...byte N: contain the Information Fields of the Telemetry B Uplink
                  Frames recieved from the device in  response to the AppData request.
                  The Information Fields are appended to the response buffer in the
                  order in which they are received. (Telemtry B Information Fields are
                  defined in the Telemetry B Protocol Specifiation #217420.)
    respBufferSize - value which defines the size of the buffer available
      at tbv_AppDataRespPtr
    appDataReqPtr - a pointer to the Telemetry B frame which will be downlinked to
       the device.  The size of the frame is defined by tbv_AppDataReqLen.
    appDataReqLen -  value which defines the size of the frame at tbv_AppDataReqPtr
    firstULRespTime - the time within which to expect the first frame of the uplink
      response.  (Interframe delay time is given in the config B table.)
***************************************************************************
*/
typedef struct tbt_appDataReqEntry
{
    tbt_devIdEntry *targetIDPtr;
    USHORT progID;
    tbt_configBTableType *configBPtr;
    USHORT *bufferUsedLengthPtr;
    BYTE *respBufferPtr;
    UINT16 respBufferSize;
    BYTE *appDataReqPtr;
    UINT16 appDataReqLen;
    UINT16 firstULRespTime;
}
tbt_appDataReqEntry;

#endif /*  tbt_handler_h  */
