/* Copyright (c) 2001 by Medtronic Inc.  All Rights Reserved */
/********************************************************************
DOCUMENT

$Revision$

$Date$

$RCSfile$

MODULE:
  tbm_handler.c  area = telemetry B

FUNCTIONS:
  tbm_initSession
  tbm_reInitTelemB
  tbm_telemBAutoID
  tbm_telemBClose
  tbm_telemBData
  tbm_telemBInitialize
  tbm_telemBUplinks

DESCRIPTION:
  This file contains functions which are available to the 2490B Application
  modules to perform Telemetry B functions.

ENDDOCUMENT
********************************************************************/
#include "..\types.h"
#include <string.h>

#define DEFINED_HERE
#include "tbm_handler.h"
#undef DEFINED_HERE

#include "tbm_fsm.h"
#include "tbm_events.h"
#include "tbm_channel.h"
#include "tbm_queue.h"
#include "tbm_timer.h"
#include "tbm_main.h"
#include "tbm_trx.h"
#include "tbm_rcv.h"
#include "../bsm/bsm_Event.h"

/*
*******************************************************************
*****     LOCAL FUNCTION PROTOTYPES
*******************************************************************
*/
void tbm_initSession(void);
void tbm_reInitTelemB(void);

/********************************************************************

FUNCTION:
  tbm_initSession

DESCRIPTION:
  This is a local function which initializes the structure tbv_session
  which contains information and pointers for general use during any
  telemetry processing.

INPUT:
  none

OUTPUT:
  none

********************************************************************/
void tbm_initSession(void)
{
    tbv_session.sessionStatus              = tbc_successful;

/* Initialize the constant portions of the Telemetry B Open Session downlink Frame. */
    tbv_session.openSessFrame.length       = 16;
    tbv_session.openSessFrame.finalFrame   = (USHORT) TRUE;
    tbv_session.openSessFrame.syncType     = tbc_sc_extended;
    tbv_session.openSessFrame.frameType    = tbt_dlUFrameOpen;
    tbv_session.openSessFrame.dlHeader     = 0x00;
    tbv_session.openSessFrame.infoField[0] = TBC_PROTOCOL_SOM_U;    /* Start of Message */
    tbv_session.openSessFrame.infoField[1] = TBC_PROTOCOL_SOM_L;    /* Start of Message */
    tbv_session.openSessFrame.infoField[2] = 0xCB;  /* Protocol Command /Record Size */
    tbv_session.openSessFrame.infoField[3] = TBC_PROTOCOL_CC_OPEN;  /* Protocol Command Code */
    tbv_session.openSessFrame.infoField[4] = TBC_OPEN_DATA_RATE_087;    /* Protocol ID (uplink rate set to 87.5 kbps) */

/*  Initialize the constant portions of the basic Telemetry B Device ID downlink Frame. */
    tbv_session.deviceIDFrame.length       = 8;
    tbv_session.deviceIDFrame.finalFrame   = (USHORT) TRUE;
    tbv_session.deviceIDFrame.syncType     = tbc_sc_extended;
    tbv_session.deviceIDFrame.uplinkRate   = tbc_dr_21;
    tbv_session.deviceIDFrame.frameType    = tbt_dlUFrame;
    tbv_session.deviceIDFrame.dlHeader     = 0;

#ifdef DEBUG_BAD_MSG
        #warn "Transmit Bad Message Simulated."
    tbv_session.deviceIDFrame.infoField[0] = ~TBC_PROTOCOL_SOM_U;
#else
    tbv_session.deviceIDFrame.infoField[0] = TBC_PROTOCOL_SOM_U;    /* Start of Message */
#endif

    tbv_session.deviceIDFrame.infoField[1] = TBC_PROTOCOL_SOM_L;    /* Start of Message */
    tbv_session.deviceIDFrame.infoField[2] = 0xC3;  /* Protocol Command/Record Size */
    tbv_session.deviceIDFrame.infoField[3] = TBC_PROTOCOL_CC_DEV_ID;    /* Protocol Command Code */
    tbv_session.deviceIDFrame.infoField[4] = 0x00;  /* Protocol ID (number devices in DL */

/* Initialize the session variables. */
    tbv_session.DeviceIDRespPtr            = NULL;
    tbv_session.TargetDeviceIDPtr          = NULL;
    tbv_session.ProgrammerID               = 0x0000;
    tbv_session.ConfigBPtr                 = NULL;
    tbv_session.bufferUsedLengthPtr        = NULL;
    tbv_session.RespPtr                    = NULL;
    tbv_session.MaxBufferSize              = 0;
    tbv_session.UplinkSampleTime           = 0;
    tbv_session.AppDataReqPtr              = NULL;
    tbv_session.AppDataReqLen              = 0;
    tbv_session.FirstULRespTime            = 0;

}

/********************************************************************

FUNCTION:
  tbm_reInitTelemB

DESCRIPTION:
  This is a local function which re-initializes the Telemetry system.

INPUT:
  none

OUTPUT:
  none


********************************************************************/
void tbm_reInitTelemB(void)
{
    /*
       Initialize the Event Manager.
     */
    tbm_initializeEvents();
    /*
       Clean out the uplink and downlink queues.
     */
    tbm_dequeueAllEntries((tbt_queuePointer *) &tbv_ulFrameQ);
    tbm_dequeueAllEntries((tbt_queuePointer *) &tbv_dlFrameQ);
    /*
       Restart all the static timers.
     */
    tbm_reloadAllTimers();
}

/********************************************************************

FUNCTION: tbm_telemBAutoID

DESCRIPTION:
  This function is called by the 2490B Application to perform Auto ID of
  all Telemetry B type devices in range of the RF Head.

INPUT:
  tbv_deviceIDRespPtr : a pointer to a response buffer.
  tbv_ProgrammerID : the 2490B Programmer ID.

OUTPUT:
  "return value" : status which indicate the success or failure of this function.
  *tbv_DeviceIDRespPtr : The device ID's are returned in the response buffer. The
  format of the buffer is defined by the type: tbt_autoIDRespType

********************************************************************/
tbt_reqStatus tbm_telemBAutoID(tbt_autoIDRespType * tbv_DeviceIDRespPtr,
                               UINT16             tbv_ProgrammerID)
{
    // Ensure that the handshake timer is disabled.
    tbm_hsDisable();

    /*
       Initialize all of the session variables.
     */
    tbm_initSession();

    /*
       re-Initialize the Telemetry sub-systems..
     */
    tbm_reInitTelemB();

    tbv_session.DeviceIDRespPtr              = tbv_DeviceIDRespPtr;
    tbv_session.DeviceIDRespPtr->numberFound = 0;
    /*
       Initialize the variable portions of the basic Telemetry B Device ID downlink Frame.
     */
    tbv_session.deviceIDFrame.pgmrId[0]      = (tbv_ProgrammerID >> 8) & 0xff;
    tbv_session.deviceIDFrame.pgmrId[1]      = tbv_ProgrammerID & 0xff;

    /*
       Initialize response time.
     */
    tbv_session.FirstULRespTime              = TBC_DEVICE_ID_RESP_WINDOW;

    /*
       Post a state-machine event to the event processor.
     */
    tbm_postEvent(&tbm_Chan_AutoIDRequest);

    /*
       Start the event processor.  All telemetry actions are continued
       by use of the event processor.
     */
    tbm_eventProcessor();

    // Disable the handshake timer.
    tbm_hsDisable();

    /*
       Return to the calling function, and return the status of this
       function.
     */
    return (tbv_session.sessionStatus);
}

/********************************************************************

FUNCTION:  tbm_telemBClose

DESCRIPTION:
  This function will terminate a active session with the device.

INPUTS:
none

OUTPUTS:
  "return value" : status which indicate the success or failure of this function.

********************************************************************/
tbt_reqStatus tbm_telemBClose(void)
{

    // Disable the handshake timer.
    tbm_hsDisable();

    /*
       re-Initialize the Telemetry sub-systems..
     */
    tbm_reInitTelemB();

    /*
       Post a state-machine event to the event processor.
     */
    tbm_postEvent(&tbm_Chan_CloseRequest);

    /*
       Start the event processor.  All telemetry actions are continued
       by use of the event processor.
     */
    tbm_eventProcessor();

    // Disable the handshake timer.
    tbm_hsDisable();

    /*
       Return to the calling function, and return the status of this
       function.
     */
    return (tbv_session.sessionStatus);
}

/********************************************************************

FUNCTION:
  tbm_telemBData

DESCRIPTION:
  This function is called by the 2490 Application to request that a Telemetry B
  session be established with a specific device and to send that device
  an Application Downlink request.  This function must also store all of the
  responses to the Application Downlink request and provide these at the
  specific memory location defined by the calling function.

INPUT DATA:

  tbv_appDataReqInfoPtr :  a pointer to a set of required parameters.
  The details of the contents is defined by the type: tbt_appDataReqEntry.

OUTPUT RESULTS:
  "return value" : status which indicate the success or failure of this function.

  *tbv_appDataReqInfoPtr : The response information is stored in one or more of the
  parameters. The details of the contents is defined by the type: tbt_appDataReqEntry.

********************************************************************/
tbt_reqStatus tbm_telemBData(tbt_appDataReqEntry * v_appDataReqInfoPtr)
{
    // Ensure that the handshake timer is disabled before getting in session.
    tbm_hsDisable();

    /*
       re-Initialize the Telemetry sub-systems.
     */
    tbm_reInitTelemB();

    /*
       Initialize all of the session variables.
     */
    tbm_initSession();
    /*
       Check the size of the requested message.
     */
    if (v_appDataReqInfoPtr->appDataReqLen <= TBC_MAX_MSG_REQ_BYTE_SIZE)
    {
        tbv_session.TargetDeviceIDPtr    = v_appDataReqInfoPtr->targetIDPtr;
        tbv_session.ProgrammerID         = v_appDataReqInfoPtr->progID;
        tbv_session.ConfigBPtr           = v_appDataReqInfoPtr->configBPtr;
        tbv_session.bufferUsedLengthPtr  =
            v_appDataReqInfoPtr->bufferUsedLengthPtr;
        /*
           Initialize the length of the used response buffer.
         */
        *tbv_session.bufferUsedLengthPtr = 0;
        tbv_session.RespPtr              = v_appDataReqInfoPtr->respBufferPtr;

        /*
           Initialize the command code field in the response buffer.
         */
        *(tbv_session.RespPtr)           = 0x00;
        *(tbv_session.RespPtr + 1)       = 0x00;

        tbv_session.MaxBufferSize        = v_appDataReqInfoPtr->respBufferSize;
        tbv_session.AppDataReqPtr        = v_appDataReqInfoPtr->appDataReqPtr;
        tbv_session.AppDataReqLen        = v_appDataReqInfoPtr->appDataReqLen;
        tbv_session.FirstULRespTime      = v_appDataReqInfoPtr->firstULRespTime;

        /*
           Post a state-machine event to the event processor.
         */
        tbm_postEvent(&tbm_Chan_AppDataRequest);

        /*
           Start the event processor.  All telemetry actions are continued
           by use of the event processor.
         */
        tbm_eventProcessor();

        /*
           Return to the calling function, and return the status of this
           App Data function.
         */
    }                           /* end of dataCount size okay */
    else                        /* dataCount too large */
    {
        tbv_session.sessionStatus = tbc_telemetry_abuse;
    }

    // Disable the handshake timer.
    tbm_hsDisable();

    return (tbv_session.sessionStatus);
}

/********************************************************************

FUNCTION:
  tbm_telemBInitialize

DESCRIPTION:
  This function initializes the Telemetry system.

  This function should be called by the A2490B pplication once per powerup session.
  Since the Event Manager is not running at this point, this function will
  directly utilize the Channel State Machine via function calls.

  CONSTRAINTS:  This function must be the first Telemetry function called. And it
  must be called only once per power on.

INPUT:
  none

OUTPUT:
  "return value" : status which indicate the success or failure of this function.


********************************************************************/
#pragma CODE_SECTION(tbm_telemBInitialize, ".tbmExtCode")
tbt_reqStatus tbm_telemBInitialize(void)
{
    /* Initialize the physical layer. This function include the copying of
    ** telemetry B physical layer code from SDRAM to internal DARAM. */
    tbm_init();

    /*
       Initialize the Channel state-machine.
     */
    tbm_Chan_initialize(&tbv_Channel);

    /*
       Initialize Telemetry by a direct call to the Channel State Machine.  This
       call is equivalent to sending the ActivateTelemB event to the State Machine.
       Note that on Power up the State Machine was initialized to the Idle state.
     */
    tbm_Chan_ActivateTelemB(&tbv_Channel);

    /*
       Return to the calling function, and return the status of this
       function.
     */
    return (tbv_session.sessionStatus);
}
/********************************************************************

FUNCTION:
  tbm_telemBDeactivate

DESCRIPTION:
  This function deactivates the Telemetry B system.

  This function must be called by the application when Telemetry
  B activities have been completed. Failure to call this function
  can have adverse affects on other modules that utilize the
  shared DARAM space that the tbm module utilizes.

INPUT:
  none

OUTPUT:
  none

********************************************************************/
#pragma CODE_SECTION(tbm_telemBDeactivate, ".tbmExtCode")
void tbm_telemBDeactivate(void)
{
    if (tbv_active) {
        // Disable the physical layer (if not disabled already).
        tbm_disablePhysLayer(TRUE);

        // This deactivates the tbm_PRD function calls,
        // among other things.
        tbv_active = FALSE;

        // Release the DMA channel that tbm receive used.
        DMA_stop(tbv_hDma);
        DMA_close(tbv_hDma);
    }
}

/********************************************************************

FUNCTION:
  tbm_telemBUplinks

DESCRIPTION:
  This function is called by the 2490B Application to request that a Telemetry B
  session be established or maintained with a specific device.  Once a session has
  been established, this function will store all of the valid waveform and supplemental
  marker uplink frames at the specific memory location.

INPUT:
  v_uplinksReqInfoPtr :  a pointer to a set of required parameters.
  The details of the contents is defined by the type: tbt_uplinksReqEntry.

OUTPUT:
  "return value" : status which indicate the success or failure of this function.

  *v_uplinksReqInfoPtr : The response information is stored in one or more of the
  parameters. The details of the contents is defined by the type: tbt_uplinksReqEntry.

********************************************************************/
tbt_reqStatus tbm_telemBUplinks(tbt_uplinksReqEntry * v_uplinksReqInfoPtr)
{
    // Ensure that the handshake timer is disabled before getting in session.
    tbm_hsDisable();

    /*
       re-Initialize the Telemetry sub-systems..
     */
    tbm_reInitTelemB();
    /*
       Initialize all of the session variables.
     */
    tbm_initSession();
    tbv_session.TargetDeviceIDPtr    = v_uplinksReqInfoPtr->targetIDPtr;
    tbv_session.ProgrammerID         = v_uplinksReqInfoPtr->progID;
    tbv_session.ConfigBPtr           = v_uplinksReqInfoPtr->configBPtr;
    tbv_session.bufferUsedLengthPtr  = v_uplinksReqInfoPtr->bufferUsedLengthPtr;
    /*
       Initialize the length of the used response buffer.
     */
    *tbv_session.bufferUsedLengthPtr = 0;

    tbv_session.RespPtr              = v_uplinksReqInfoPtr->respBufferPtr;
    tbv_session.MaxBufferSize        = v_uplinksReqInfoPtr->respBufferSize;
    tbv_session.UplinkSampleTime     = v_uplinksReqInfoPtr->uplinkListenTime;

    /*
       Post a state-machine event to the event processor.
     */
    tbm_postEvent(&tbm_Chan_UplinksRequest);

    /*
       Start the event processor.  All telemetry actions are continued
       by use of the event processor.
     */
    tbm_eventProcessor();

    // Disable the handshake timer.
    tbm_hsDisable();

    /*
       Return to the calling function, and return the status of this
       App Data function.
     */
    return (tbv_session.sessionStatus);
}

