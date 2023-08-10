/************************************************************************
*
* MODULE: tam_RttTest.c
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the functions for RTT Test.
*
*************************************************************************/

#include "global.h"
#include "tam_global.h"
#include "tam_TelemetryA.h"
#include "tam_RepeatTask.h"
#include "tam_TransmitCommon.h"
#include "uim_ui.h"
#include <csl_gpio.h>

// 2000 milliseconds
#define RTT_MARKER_TIMEOUT 2000

// wait for 250 msec.
#define RTT_ACK_TIMEOUT 25

// uplink command byte corresponding to an ACK
#define RTT_ACK_RESPONSE 0x81

// bit 7 set high indicates successful handshake - handshake status byte
#define tac_SUCCESSFUL_HANDSHAKE 0x80

// bit 6 set high indicates temporary operations in effect
#define tac_TEMPORARY_OPERATIONS 0x40

/************************************************************************

FUNCTION:     tam_RTT_Test
DESCRIPTION: This functions performs a RTT Test on the implant.

ARGS:
        BYTE *p_markers: Pointer to a list of markers.
        USHORT v_numberOfMarkers: The number of markers in the list
        BYTE *p_downlinkMsg: Message to downlink after a marker is found
        USHORT v_downlinkSize: The number of bytes in the downlink message.
        USHORT v_timeoutDuration: The number of 10's of milliseconds to wait.

RETURNS:
        tat_status: tac_successful if everything happened

*************************************************************************/
tat_status tam_RTT_Test(BYTE *p_markers, USHORT v_numberOfMarkers,
                        BYTE *p_downlinkMsg, USHORT v_downlinkSize,
                        USHORT v_timeoutDuration)
{
    switch( TelemetryType )
    {
    case tac_L88TelemProtocol:
        return tam_RTT_TestL88(p_markers, v_numberOfMarkers,
                               p_downlinkMsg, v_downlinkSize,
                               v_timeoutDuration);

    case tac_GemTelemProtocol:
        return tam_RTT_TestIcd(p_markers, v_numberOfMarkers,
                               p_downlinkMsg, v_downlinkSize,
                               v_timeoutDuration);

    default:
        return tac_badTelemetryType;
    }
}

 /* 
* Per the Adapta PRS (A06725), which is consistent with Kappas, Enpulse: 
* 
* "The values in the following tables represent the value of the lower 6 bits 
* of the 8-bit marker code. Bits 7 and/or 6 ("VREV" and "AREV", respectively) 
* may also be set, and should be disregarded for purposes of decoding 
* Pacing Event Markers." 
* 
* The following mask will zero bits 2^7 and 2^6. 
* 
*/ 
#define tac_MARKER_BITS_ONLY 0x3F

/************************************************************************

FUNCTION:     tam_RTT_TestL88
DESCRIPTION: This functions performs a RTT Test on the implant.

ARGS:
        BYTE *p_markers: Pointer to a list of markers.
        USHORT v_numberOfMarkers: The number of markers in the list
        BYTE *p_downlinkMsg: Message to downlink after a marker is found
        USHORT v_downlinkSize: The number of bytes in the downlink message.
        USHORT v_timeoutDuration: The number of 10's of milliseconds to wait.

RETURNS:
        tat_status: tac_successful if everything happened

*************************************************************************/
tat_status tam_RTT_TestL88(BYTE *p_markers, USHORT v_numberOfMarkers,
                           BYTE *p_downlinkMsg, USHORT v_downlinkSize,
                           USHORT v_timeoutDuration)
{
    // This enumeration is for the different data identifiers
    // being received from the device via uplink frames.
    typedef enum {
        tac_findMarkerState,
        tac_AckState,
        tac_HandshakeState,
        tac_stopRTTState
    }   tat_rttStateType;

    tat_status       v_telemetryStatus = tac_telemetryError;
    tat_rttStateType v_RTTState        = tac_findMarkerState; // current state
                                                              // machine state
    BOOL v_startCaptureEngine          = true; // flag used to communicate
                                               // when to re-initialize
                                               // capture engine
    BOOL          v_timeout            = false; // flag used for timeout
    tat_frameType v_dataIdentifier;     // data identifier associated with
                                        // current uplink frame
    BYTE          v_data;               // data associated with frame
    BYTE          v_uplinkBuffer[4];    // buffer to store current
    tat_frameType v_previousFrame       = tac_invalidIdentifierFrame; // flag
    // containing the previous frame
    // the RTT software has processed
    USHORT temporaryOperationInprogress = 0;
    BOOL   v_configureOnce              = false;
    USHORT v_index;                     // index variable and counter

    GLB_LTMR_OBJ StartTime;
    GLB_LTMR_OBJ v_handshakeConfirmTime;

    // if the repeat downlink is active, return an error code
    if( IsRepeatDownlinkActive() )
    {
        return tac_repeatDownlinkActive;
    }

    // Clear the uplink buffer
    for (v_index = 0; v_index < 4; v_index++)
    {
        v_uplinkBuffer[v_index] = 0;
    }

    // set timer for marker search, this will occur during
    // the state - tac_findMarkerState

    GLB_GET_LTMR(StartTime);

    // The below code is set-up like a state machine.  The while loop keeps
    // the state machine running, until the last state is reach.  Than,
    // a "break" is performed to leave the while loop.
    while (!v_timeout)
    {
        // determine if we need to restart capture engine
        if (v_startCaptureEngine)
        {
            // begin capturing
            TurnOnReceiver();

            v_startCaptureEngine = false;  // do not restart capture engine
        }


        // switch to proper state in the RTT state machine
        switch(v_RTTState)
        {
        case tac_findMarkerState:
            // retrieve next frame from device
            if( RxDataValid )
            {
                DISABLE_INTERRUPTS;
                v_data            = RxData;
                v_dataIdentifier  = RxDataType;
                RxDataValid       = FALSE;
                ENABLE_INTERRUPTS;

                v_telemetryStatus = tac_successful;

                // determine if current frame is a marker
                if (v_dataIdentifier == tac_markerFrame)
                {
                    v_data &= tac_MARKER_BITS_ONLY;

                    // Is this an RTT activation marker
                    for (v_index = 0; v_index < v_numberOfMarkers; v_index++)
                    {
                        // marker matches marker in array provided by application
                        if (v_data ==  p_markers[v_index])
                        {
                            // stop capturing
                            TurnOffReceiver();

                            // send message to initiate RTT measurements
                            TransmitDownlinkBuffer(p_downlinkMsg, v_downlinkSize);
                            //bsm_SDPrint("Marker done!");
                            v_RTTState = tac_AckState;
                            break;                             // break out of for loop
                        }
                    }

                }
            }
            else
            {
            }

            // check for timeout
            if( GLB_HAS_LTMR_EXPIRED(StartTime, RTT_MARKER_TIMEOUT) )
            {
                // did not find marker before timeout
                v_timeout         = true;
                v_telemetryStatus = tac_telemetryTimeout;
                //bsm_SDPrint("Marker timeout");
            }

            break;

        case tac_AckState:

            // search for an ACK transmitted by the device
            v_telemetryStatus =     ReceiveMemoryUplink(sizeof(v_uplinkBuffer),RTT_ACK_TIMEOUT, v_uplinkBuffer);
            //bsm_SDPrint("Get Ack frames!");
            if(v_telemetryStatus == tac_successful)
            {
                // check response for an ACK
                if (v_uplinkBuffer[1] == RTT_ACK_RESPONSE)
                {
                    // set-up for next state
                    v_startCaptureEngine = true;              // prepare for more uplinks
                    v_RTTState           = tac_HandshakeState;
                    v_previousFrame      = tac_invalidIdentifierFrame;
                }
                else
                {
                    // failure occurred
                    v_telemetryStatus = tac_nonAckResponse;
                    v_RTTState        = tac_stopRTTState;
                    //bsm_SDPrint("Ack:no response");
                }
            }
            else
            {
                // failure occurred
                v_RTTState = tac_stopRTTState;
                //bsm_SDPrint("Ack:unsuccessful telemetry");
            }

            break;

        case tac_HandshakeState:

            // configure start timer and handshake confirmation timer
            // to allow a specified amount of time to run RTT test
            if (!v_configureOnce)
            {
                GLB_GET_LTMR(StartTime);
                GLB_GET_LTMR(v_handshakeConfirmTime);
                v_configureOnce = true;
            }

            // retrieve next frame from device
            if( RxDataValid )
            {
                DISABLE_INTERRUPTS;
                v_data            = RxData;
                v_dataIdentifier  = RxDataType;
                RxDataValid       = FALSE;
                ENABLE_INTERRUPTS;

                v_telemetryStatus = tac_successful;

                // process data based on previous frame processes
                if (v_previousFrame != tac_handshakeRequestFrame)
                {
                    // handshake request frame
                    if (v_dataIdentifier == tac_handshakeRequestFrame)
                    {
                        // set flag to indicate we have received a handshake
                        // request
                        v_previousFrame = tac_handshakeRequestFrame;
                        //bsm_SDPrint("HS Request Frame");
                    }
                    // other type of frame.  continue to search for handshake
                    // request
                }
                else
                {
                    // handshake confirmation frame
                    if (v_dataIdentifier == tac_handshakeConfirmFrame)
                    {
                        //bsm_SDPrint("HS Confirm Frame");
                        // check for handshake status from device
                        if (!(v_data & tac_SUCCESSFUL_HANDSHAKE))
                        {
                            v_telemetryStatus = tac_unsuccessfulHandshake;
                            //bsm_SDPrint("HS Unsuccessful Confirm Frame");
                        }
                        else
                        {
                            // determine if temporary operations are completed
                            if (v_data & tac_TEMPORARY_OPERATIONS)
                            {
                                // temporary operation is still in progress
                                temporaryOperationInprogress++;
                            }
                            else
                            {
                                // temporary operations complete successfully
                                v_telemetryStatus = tac_temporaryOperationCompleted;
                                v_RTTState        = tac_stopRTTState;
                                //bsm_SDPrint("RTT operation done");
                            }
                        }
                    }
                    else
                    {
                        // failure occurred
                        v_telemetryStatus = tac_unsuccessfulHandshake;
                        //Keep this debug line!
                        //bsm_SDPrint("Lost HS Confirm Frame!");
                    }
                }

                // remember the last frame type
                v_previousFrame = v_dataIdentifier;

                // save time when handshake confirmation frame is received
                if (v_dataIdentifier == tac_handshakeConfirmFrame) {
                    GLB_GET_LTMR(v_handshakeConfirmTime);
                }
            }
            else
            {
                v_telemetryStatus = tac_telemetryError;
            }

            // check for timeout, due to RTT Test lasting longer than requested duration
            if( GLB_HAS_LTMR_EXPIRED(StartTime, (ULONG)(v_timeoutDuration*10)) )
            {
                v_timeout         = true;
                v_telemetryStatus = tac_telemetryTimeout;
                //bsm_SDPrint("6 seconds HS timeout");
            }

            // check for early termination, due to no handshake confirmation
            // frame for more than 1 second
            if (GLB_HAS_LTMR_EXPIRED(v_handshakeConfirmTime, (ULONG)(LTMR_TICKS_PER_SECOND))) {
                uim_TelemetryWarning(on);
                v_timeout         = true;
                v_telemetryStatus = tac_telemetryTimeout;
                //bsm_SDPrint("1 seconds No Confirm Frame timeout!");

            }
            break;

        default:
            v_telemetryStatus = tac_telemetryInvalidStateError;
            v_RTTState        = tac_stopRTTState;
            //bsm_SDPrint("RTT default:telemetry Invalid State");
            break;
        }

        // check to see if state machine has reached its last state
        if (v_RTTState == tac_stopRTTState)
        {
            break;             // exit while loop
        }
    } // end of while loop

    // stop uplink capture
    TurnOffReceiver();

    return (v_telemetryStatus);
}

/************************************************************************

FUNCTION:     tam_RTT_TestIcd
DESCRIPTION: This functions performs a RTT Test on the implant.

ARGS:
        BYTE *p_markers: Pointer to a list of markers.
        USHORT v_numberOfMarkers: The number of markers in the list
        BYTE *p_downlinkMsg: Message to downlink after a marker is found
        USHORT v_downlinkSize: The number of bytes in the downlink message.
        USHORT v_timeoutDuration: The number of 10's of milliseconds to wait.

RETURNS:
        tat_status: tac_successful if everything happened

*************************************************************************/
tat_status tam_RTT_TestIcd(BYTE *p_markers, USHORT v_numberOfMarkers,
                           BYTE *p_downlinkMsg, USHORT v_downlinkSize,
                           USHORT v_timeoutDuration)
{
    return tac_badTelemetryType;
}
