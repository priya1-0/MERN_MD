/* Copyright (c) 2001 by Medtronic Inc.  All Rights Reserved */
/********************************************************************
DOCUMENT

$Revision$

$Date$

$RCSfile$

NAME:    tbm_channel.h

PURPOSE: Various subroutines for general use by Channel and Handler.

ENDDOCUMENT
********************************************************************/
#ifndef tbm_channel
#define tbm_channel

#include "tbm_fsm.h"

#ifdef DEFINED_HERE
        #define SCOPE
#else
        #define SCOPE extern
#endif

typedef struct {
    BOOL tbm_chanCov_activate;
    BOOL tbm_chanCov_autoIDDone;
    BOOL tbm_chanCov_autoIDFail;
    BOOL tbm_chanCov_captureDataDone;
    BOOL tbm_chanCov_checkAutoIDDone;
    BOOL tbm_chanCov_closeDone;
    BOOL tbm_chanCov_closeSession;
    BOOL tbm_chanCov_concludeAutoID;
    BOOL tbm_chanCov_continueAutoID;
    BOOL tbm_chanCov_createDLframes;
    BOOL tbm_chanCov_deviceIDTx;
    BOOL tbm_chanCov_doAutoID;
    BOOL tbm_chanCov_doReturn;
    BOOL tbm_chanCov_EGMtimerExp;
    BOOL tbm_chanCov_FreeFrame;
    BOOL tbm_chanCov_initLinkMode1;
    BOOL tbm_chanCov_listenForDeviceIDResp;
    BOOL tbm_chanCov_listenForOpenResp;
    BOOL tbm_chanCov_lossOfTelemetry;
    BOOL tbm_chanCov_noResp;
    BOOL tbm_chanCov_noTx;
    BOOL tbm_chanCov_openFail;
    BOOL tbm_chanCov_openSession;
    BOOL tbm_chanCov_processDeviceIDResp;
    BOOL tbm_chanCov_processMissedWF;
    BOOL tbm_chanCov_processOpenResp;
    BOOL tbm_chanCov_processULnonWFFrame;
    BOOL tbm_chanCov_processULWaveform;
    BOOL tbm_chanCov_processWFOpenResp;
    BOOL tbm_chanCov_startAppDataTimer;
    BOOL tbm_chanCov_stopLinkMode1;
    BOOL tbm_chanCov_stopSession;
    BOOL tbm_chanCov_tlmAbuse;
    BOOL tbm_chanCov_txTimeoutMode1;
    BOOL tbm_chanCov_txTimeoutMode2;
    BOOL tbm_chanCov_unexpTelemEvent;
} tbm_chanCoverage_t;

/* The maximum number of times that the Channel layer will try to send an
asynchronous downlink frame to the Link layer before failing. */
#define TBC_MAX_CHAN_TX_RETRIES 1
#define TBC_240_MS_TIMER        12 /* 12 * 20 ms = 240 ms */
#define TBC_500_MS_TIMER        26 /* 25 * 20 ms = 500 ms */

// Global Variables
SCOPE tbm_Chan           tbv_Channel;
SCOPE BOOL               shortTimeoutTimerInitialized;
SCOPE USHORT             tbv_respCurrentLength;
SCOPE UINT16             tbv_unexpEventCounter;
SCOPE tbm_chanCoverage_t tbv_chanCoverage;


SCOPE void tbm_noResp(void);
SCOPE void tbm_noTx(void);
SCOPE void tbm_EGMtimerExp(void);

#undef SCOPE

#endif /* tbm_channel_h */
