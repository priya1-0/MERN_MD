/*
************************************************************************
 2490 In-home Remote Monitor
 Copyright (c) Medtronic, Inc. 2001

 MODULE: User Interface Module

 OWNER: Medtronic

 $Revision$

 $Date$

 $RCSfile$

 DESCRIPTION:

 GLOBAL MODULE DATA:

 STATIC MODULE DATA:

 ENDPURPOSE

************************************************************************
*/

#ifndef uim_ui_h
#define uim_ui_h

#include "types.h"


// Define the following to turn off tones.
// #define NO_TONES

long uim_AddToEstimatedSize (long size);
void uim_InterrogationStarted(void);
void uim_InterrogationProgress(long size);
void uim_IlluminateLED(USHORT index);
void uim_InterrogationComplete(void);
void uim_InterrogationSkipped(void);
void uim_AlertTone(void);
void uim_ErrorTone(void);
void uim_CompleteTone(void);
void uim_TelemetryWarning(bool onOff);
void uim_ModemWarning(bool state);
void uim_ModemWarning_AlertTone_15Minutes(void);
void uim_UploadFailure(void);
void uim_ModemStart(bool state);
void uim_DisplayReady(void);
void uim_POSTInProgress(void);
void uim_BatteryWarning(void);
void uim_ModemTransferComplete(void);
void uim_StrobePhoneLeds(bool state);
void uim_EPRWarning(bool onOff);
void uim_SWUpdateComplete(void);
void uim_SWUpdateFail(void);

#endif
