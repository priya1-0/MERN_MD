/************************************************************************
*
* MODULE: tam_ContinuousEgm.c
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the functions to capture a contunuous
*              EGM waveform.
*
*************************************************************************/

#include "tam_global.h"
#include "tam_TelemetryA.h"
#include "tam_RepeatTask.h"
#include "bsm_Event.h"
#include "aim_kappa.h"
#include "bsm_serialport.h"
#include <stdio.h>
#include <csl_gpio.h>

////////////
// defines
////////////

// number of IPG uplink frames per second
#define tac_IPG_FRAMES_PER_SECOND (DEVICE_FREQ/MESSAGE_LENGTH_L88)

// number of IPG Frames per System Clock (1ms)
#define tac_NUM_IPG_FRAMES_PER_SYSTEM_CLOCK (tac_IPG_FRAMES_PER_SECOND/GLB_LOW_RES_ROLLOVER*1000)

// bit 7 set high indicates successful handshake - handshake status byte
#define tac_SUCCESSFUL_HANDSHAKE 0x80

// ICD (GEMS) frames per second
#define tac_ICD_FRAMES_PER_SECOND (DEVICE_FREQ/MESSAGE_LENGTH_ICD)

// Some overhead to account for any delay in capturing the waveform
#define tac_EGM_RECORD_TIME_OVERHEAD_MS 300

// number of invalid frames threshold
#define tac_INVALID_FRAME_THRESHOLD 10


////////////
// Globals
////////////
// flag for continuous 7 (Dual) or 10 (Single) seconds EGM collection
static BOOL tav_continuousCollectionCompleted;

// flag for collecting 30 seconds of EGM data
static BOOL tav_allCollectionCompleted;

// system time when telemetry was lost while collecting EGM data (in ms)
static ULONG tav_systemTimeTelemetryIsLost;


/************************************************************************

FUNCTION:     tam_Continuous_Egm
DESCRIPTION:  This function selects the type of telemetry EGM to receive.

ARGS:
        BYTE* p_uplinkMsg: Pointer to a buffer to store the uplink message
        BYTE v_recordTime: Number of seconds to record
        USHORT *p_uplinkSize: Pointer to a variable to record the number of
                              bytes in p_uplinkMsg
        USHORT *p_startEgmsampleCount: Last sample stored in p_uplinkMsg
        bool v_bypass10SecondCheck: By-pass 10 second of continuous data
                                    collection during tam_Continuous_EgmL88.

RETURNS:
        tat_status: tac_successful if everything happened

*************************************************************************/
tat_status tam_Continuous_Egm(BYTE   *p_uplinkMsg,
                              BYTE   v_recordTime,
                              USHORT *p_uplinkSize,
                              USHORT *p_startEgmsampleCount,
                              bool   v_bypass10SecondCheck)
{
    switch( TelemetryType )
    {
    case tac_L88TelemProtocol:
        return tam_Continuous_EgmL88(p_uplinkMsg,
                                     v_recordTime,
                                     p_uplinkSize,
                                     p_startEgmsampleCount,
                                     v_bypass10SecondCheck);

    case tac_GemTelemProtocol:
        return tam_Continuous_EgmIcd(p_uplinkMsg,
                                     v_recordTime,
                                     p_uplinkSize,
                                     p_startEgmsampleCount);

    default:
        return tac_badTelemetryType;
    }
}


/************************************************************************

FUNCTION:     tam_Continuous_EgmL88
DESCRIPTION:  This function collects frames of data for a certain amount
              of time.  If this function is called with a non-zero
              startEgmsampleCount, then invalid frames are inserted in the
              buffer to the current time of the call.

ARGS:
        BYTE* p_uplinkMsg: Pointer to a buffer to store the uplink message
        BYTE v_recordTime: Number of seconds to record
        USHORT *p_uplinkSize: Pointer to a variable to record the number of
                              bytes in p_uplinkMsg
        USHORT *p_startEgmsampleCount: Last sample stored in p_uplinkMsg
        bool v_bypass10SecondCheck: By-pass 10 second of continuous data
                                    collection during tam_Continuous_EgmL88.

RETURNS:
        tat_status: tac_successful if everything happened

*************************************************************************/
tat_status tam_Continuous_EgmL88(BYTE   *p_uplinkMsg,
                                 BYTE   v_recordTime,
                                 USHORT *p_uplinkSize,
                                 USHORT *p_startEgmsampleCount,
                                 bool   v_bypass10SecondCheck)
{
    tat_status    v_telemetryStatus = tac_unknownError;
    USHORT        v_egmFrameCounter;         // number of memory frames received
    tat_frameType v_dataIdentifier;          // data identifier associated with
                                             // current uplink frame
    BYTE v_data;                             // data associated with the current
                                             // uplink frame
    BYTE v_previousMarkerFrameData;          // marker data from previous frame

    BOOL v_firstFrame         = true;        // used to keep track of first
                                             // recieved frame
    BOOL v_markerFrameCheck   = false;       // flag to indicate when to perform
                                             // marker double frame check
    BOOL v_markerOnFirstFrame = false;       // flag to indicate marker received
                                             // on first frame
    ULONG v_timePast          = 0;           // amount of time past to re-
                                             // establish telemetry
    USHORT v_count;                          // loop counter
    ULONG  v_countLong;                      // loop counter
    USHORT v_continuousSecondCounter = 0;    // egm continuous collection counter
    USHORT expectedUplinkFrames;

    ULONG StartTime;
    USHORT v_continuousCollectTime = 0;
    USHORT v_collectBoundary = 0;
    static char buffer[100];
    USHORT v_invalidCount = 0;

    // if the repeat task is active, then just return
    if( IsRepeatDownlinkActive() )
    {
        return tac_repeatDownlinkActive;
    }

    expectedUplinkFrames = v_recordTime * tac_IPG_FRAMES_PER_SECOND;

    //Set waveform collection time for single chamber device waveform collection or establish solid link
    if ((v_recordTime == AIC_KAPPA_SINGLE_EGM_SECONDS))
    {
       v_continuousCollectTime = 10; // 10 sec continuous EGM for single chamber
       v_collectBoundary = 3100; // 31 sec
    }
    else if (v_recordTime == AIC_KAPPA_DUAL_EGM_SECONDS) // Set waveform collection time for dual chamber device waveform collection
    {
       v_continuousCollectTime = 7; // 7 sec continuous EGM for dual chamber of each telem type
       v_collectBoundary = 800; // 8 sec
    }
    else if (v_recordTime == AIC_ESTABLISH_SOLID_LINK_TIME)
    {
       v_continuousCollectTime = 2; // 2 sec continuous EGM for establish solid telemetry during RTT
       v_collectBoundary = 300; // 3 sec
    }
    else
    {
       bsm_EHLock("Wrong max collection time passed in");
    }


    // determine if we are starting a collection from scratch or
    // continuing a previous collection
    if (*p_startEgmsampleCount == 0)
    {
        // reset variables for initial collection
        v_egmFrameCounter                 = 0;
        tav_continuousCollectionCompleted = false;
        tav_allCollectionCompleted        = false;
    }
    else
    {
        GLB_LTMR_OBJ CurrentTime;

        // set egm frame counter to previous setting
        v_egmFrameCounter = *p_startEgmsampleCount;

        // determine how much time has past since last EGM sample
        // when telemetry was lost
        GLB_GET_LTMR(CurrentTime);
        v_timePast = CurrentTime - tav_systemTimeTelemetryIsLost;

        // if enough time has past that we would wrap the entire buffer
        // (and therefore lose any data collected, only take the remainder
        // of the timePast divided by the length of the buffer
        if (v_timePast * tac_IPG_FRAMES_PER_SECOND / 1000 >
            expectedUplinkFrames)
        {
            v_timePast = expectedUplinkFrames %
                         (v_timePast * tac_IPG_FRAMES_PER_SECOND / 1000);
        }

        // fill in data buffer with invalid IDs for lost time
        for (v_countLong = 0;
             v_countLong < v_timePast * tac_IPG_FRAMES_PER_SECOND / 1000;
             v_countLong++)
        {
            p_uplinkMsg[v_egmFrameCounter * 2]     = tac_invalidIdentifierFrame;
            p_uplinkMsg[v_egmFrameCounter * 2 + 1] = 0;
            v_egmFrameCounter++;

            // determine if we wrapped the max (7/30) second
            // collection buffer
            if (v_egmFrameCounter >= expectedUplinkFrames)
            {
                v_egmFrameCounter          = 0;
                tav_allCollectionCompleted = true;

                // determine if we already have collected
                // 7 (Dual) or 10 (single) seconds of continuous data.  If so,
                // do not over write it.
                if (tav_continuousCollectionCompleted)
                {
                    break;  // exit out of inner for loop
                }
            }
        }
    }

    StartTime = NU_Retrieve_Clock();

    // begin capturing
    TurnOnReceiver();

    // set up 7 (dual)/10 (single) second counter based on egm frames collected,
    // to determine when we have collected 7(Dual)/10 (single) seconds of continuous EGM
    if (!tav_continuousCollectionCompleted)
        v_continuousSecondCounter = 0;

    // collect memory frames, continue to collect until we have both
    // 7 out of 30 seconds of contnuous data for single chamber device or
    // 7 out of 7 seconds of continuous data fro dual chamber device.
    while ((!tav_continuousCollectionCompleted ||
            !tav_allCollectionCompleted) &&
           NU_Retrieve_Clock() - StartTime < v_collectBoundary )
    {

        // retrieve next frame from device
        if( RxDataValid )
        {
            DISABLE_INTERRUPTS;
            v_data            = RxData;
            v_dataIdentifier  = RxDataType;
            RxDataValid       = FALSE;
            ENABLE_INTERRUPTS;

            v_telemetryStatus = tac_successful;

            // perform marker frame check only if previous frame was a marker
            if (v_markerFrameCheck)
            {
                // second frame is a marker
                if (v_dataIdentifier == tac_markerFrame)
                {
                    // compare previous marker frame data with current
                    // marker frame data
                    if (v_previousMarkerFrameData != v_data)
                    {
                        v_telemetryStatus = tac_markerDoubleFrameFailure;
                        bsm_SDPrint("Double frame failure");
                        break;
                    }

                }
                else                 // second frame is NOT a marker
                {
                    // Determine if marker was received on first frame
                    // This could mean that we received the second of
                    // the two markers.  In other words, we just miss
                    // sampling the first marker, because we started
                    // collecting EGM data too late.
                    if (!v_markerOnFirstFrame)
                    {
                        // failure, we did not see back to back markers
                        // on the uplink
                        v_telemetryStatus = tac_markerDoubleFrameFailure;
                        bsm_SDPrint("Double frame failure. Start collect EGM too late");
                        break;
                    }
                    else
                    {
                        // No failure, we began sampling with a marker.
                        // There maybe the chance that we missed the first
                        // marker, because we started sampling late.
                        v_markerOnFirstFrame = false;

                        v_markerFrameCheck   = false;
                    }
                }
            }

            // Process frame -
            // received Handshake Frame
            if (v_dataIdentifier == tac_handshakeRequestFrame)
            {
                // no data with handshake request

                // handshake is sent in the interrupt
            }
            // received Handshake Confirmation Frame
            else if (v_dataIdentifier == tac_handshakeConfirmFrame)
            {
                // if this is not the first frame
                if( !v_firstFrame )
                {
                    // check for handshake status from device
                    if (!(v_data & tac_SUCCESSFUL_HANDSHAKE))
                    {
                        v_telemetryStatus = tac_unsuccessfulHandshake;
                        bsm_SDPrint("Missing handshake request");
                        break;
                    }
                }
            }
            // check if a marker frame is received
            else if (v_dataIdentifier == tac_markerFrame)
            {
                // determine if this is the first or second marker
                // in the uplink marker error detection
                if (!v_markerFrameCheck)
                {
                    // first, perform error check on next frame
                    v_previousMarkerFrameData = v_data;
                    v_markerFrameCheck        = true;
                }
                else
                {
                    // second, reset flag to prevent performing marker
                    // frame checking on next frame
                    v_markerFrameCheck = false;
                }

                // determine if marker frame was first frame received
                // when we started sampling
                if (v_firstFrame)
                {
                    v_markerOnFirstFrame = true;
                }
            }

            if (v_dataIdentifier == tac_telemetrySegmentTimeError)
            {
                // segment time errors occur after not seeing
                // an edge for NUM_FRAMES_IN_SEGMENT_TIME_ERROR frames
                for (v_count = 0; v_count < NUM_FRAMES_IN_SEGMENT_TIME_ERROR; v_count++)
                {
                    p_uplinkMsg[v_egmFrameCounter * 2]     = tac_invalidIdentifierFrame;
                    p_uplinkMsg[v_egmFrameCounter * 2 + 1] = 0;
                    v_egmFrameCounter++;

                    // determine if we wrapped the max (7 or 30) second
                    // collection buffer
                    if (v_egmFrameCounter >= expectedUplinkFrames)
                    {
                        // inidicate wrapping occurred and reset counter
                        v_egmFrameCounter          = 0;
                        tav_allCollectionCompleted = true;

                    }
                }

                v_telemetryStatus = tac_telemetrySegmentTimeError;
                bsm_SDPrint("Segment time error");
                // break out of the while loop.
                break;
            }

            // clear first frame flag.  Note: this condition will only
            // be true on the first loop of the while loop.
            if (v_firstFrame)
            {
                v_firstFrame = false;
            }

            if( v_telemetryStatus == tac_successful )
            {

                // Lower level data receiving ProcessReceivedDataL88() sends 0xFF due to
                // the pulse offset are out of defined range. Application layer makes it retry
                // collection if received more than 10 invalid frames
                // This filter only apply to dual chamber device
                if ( aim_KappaIsDual() && ( v_dataIdentifier == tac_invalidIdentifierFrame ) )
                {
                    v_invalidCount++;
                    if (v_invalidCount >= tac_INVALID_FRAME_THRESHOLD)
                    {
                        v_telemetryStatus = tac_unknownError;
                        bsm_SDPrint("Exceeded invalid frame threshold.");
                        break;

                    }
                }

                p_uplinkMsg[v_egmFrameCounter * 2]     = (BYTE)v_dataIdentifier;
                p_uplinkMsg[v_egmFrameCounter * 2 + 1] = (BYTE) v_data;
                v_egmFrameCounter++;
                v_continuousSecondCounter++;                     // increment 7/10 second continous counter

                // determine if we wrapped the max (7 or 30) second
                // collection buffer
                if (v_egmFrameCounter >= expectedUplinkFrames)
                {
                    // inidicate wrapping occurred and reset counter
                    v_egmFrameCounter          = 0;
                    tav_allCollectionCompleted = true;
                }
            }
            else
            {
                p_uplinkMsg[v_egmFrameCounter * 2]     = tac_invalidIdentifierFrame;
                p_uplinkMsg[v_egmFrameCounter * 2 + 1] = 0;
                v_egmFrameCounter++;

                // determine if we wrapped the max (7 or 30) second
                // collection buffer
                if (v_egmFrameCounter >= expectedUplinkFrames)
                {
                    // inidicate wrapping occurred and reset counter
                    v_egmFrameCounter          = 0;
                    tav_allCollectionCompleted = true;

                }

                bsm_SDPrint("Received invalid frame");

                // break out of the while loop
                break;
            }

            // check to see if we have collected continuous 7 (Dual) or 10 (Single) second of continous
            // EGM data
            if (!tav_continuousCollectionCompleted)
            {
                // determine continuous (7 or 10) second collection or by-pass (7 or 10) second collection
                if ((v_continuousSecondCounter >= v_continuousCollectTime * tac_IPG_FRAMES_PER_SECOND) ||
                    v_bypass10SecondCheck)
                {
                    tav_continuousCollectionCompleted = true;
                }
            }
        }
        else         // no frames available, yet
        {
        }
    }


    // stop capturing
    TurnOffReceiver();

    // determine if we wrapped the buffer to calculate the uplink size
    if (tav_allCollectionCompleted)
    {
        *p_uplinkSize = expectedUplinkFrames * 2;
    }
    else
    {
        *p_uplinkSize = v_egmFrameCounter * 2;
    }

    // determine if we were successful in collecting 30 second of data
    // and 10 second of continuous data for single chamber or 7 second of data
    // and 7 second of continuouos data of for dual chamber.
    if (tav_continuousCollectionCompleted && tav_allCollectionCompleted)
    {
        v_telemetryStatus = tac_successful;
    }
    else if( NU_Retrieve_Clock() - StartTime >= v_collectBoundary )
    {
        v_telemetryStatus = tac_telemetryTimeout;
    }
    else
    {
        GLB_LTMR_OBJ CurrentTime;

        GLB_GET_LTMR(CurrentTime);

        // sample clock to determine how much time past trying to
        // re-establish telemetry connection
        tav_systemTimeTelemetryIsLost = CurrentTime;
    }

    // indicates the next slot in the buffer where an EGM sample
    // will be stored.  Note: when telemetry status is successful
    // this value will indicate the circular buffers starting
    // index.
    *p_startEgmsampleCount = v_egmFrameCounter;

    return (v_telemetryStatus);
}


/************************************************************************

FUNCTION:     tam_Continuous_EgmIcd
DESCRIPTION:  This function collects frames of data that describe the
              EGM from the implant.  Up to 10 seconds of data can be
              collected.

ARGS:
        BYTE* p_uplinkMsg: Pointer to a buffer to store the uplink message
        BYTE v_recordTime: Number of seconds to record
        USHORT *p_uplinkSize: Pointer to a variable to record the number of
                              bytes in p_uplinkMsg
        USHORT *p_startEgmsampleCount: Last sample stored in p_uplinkMsg

RETURNS:
        tat_status: tac_successful if everything happened

*************************************************************************/
tat_status tam_Continuous_EgmIcd(BYTE   *p_uplinkMsg,
                                 BYTE   v_recordTime,
                                 USHORT *p_uplinkSize,
                                 USHORT *p_startEgmsampleCount)
{
    tat_status    v_telemetryStatus = tac_successful;
    USHORT        v_egmFrameCounter = 0;     // number of memory frames received
    tat_frameType v_dataIdentifier;          // data identifier associated with
                                             // current uplink frame
    BYTE v_data;                             // data associated with the current
                                             // uplink frame

    USHORT v_timeoutLimit;                   // Amount of time to record prior
                                             // to timing out
    GLB_LTMR_OBJ StartTime;
    USHORT       expectedUplinkFrames;

    // return an error code if the repeat downlink is active
    if (IsRepeatDownlinkActive())
    {
        return tac_repeatDownlinkActive;
    }

    if( v_recordTime > 10 )
    {
        return tac_exceedMaximumEgmRecordTime;
    }

    // calculate the number of frames
    expectedUplinkFrames = v_recordTime * tac_ICD_FRAMES_PER_SECOND;

    // Calculate timeout, timeoutLimit is in millisecond ticks
    v_timeoutLimit       = (v_recordTime)*1000+tac_EGM_RECORD_TIME_OVERHEAD_MS;

    TurnOnReceiver();

    GLB_GET_LTMR(StartTime);

    // while we haven't timed out and we haven't received enough frames...
    while ( !GLB_HAS_LTMR_EXPIRED(StartTime, v_timeoutLimit) &&
            v_egmFrameCounter < expectedUplinkFrames)
    {
        // retrieve next frame from device
        if( RxDataValid )
        {
            DISABLE_INTERRUPTS;
            v_data                                 = RxData;
            v_dataIdentifier                       = RxDataType;
            RxDataValid                            = FALSE;
            ENABLE_INTERRUPTS;

            v_telemetryStatus                      = tac_successful;

            p_uplinkMsg[v_egmFrameCounter * 2]     = (BYTE)v_dataIdentifier;
            p_uplinkMsg[v_egmFrameCounter * 2 + 1] = v_data;
            v_egmFrameCounter++;

            // if we lose communication
            if( v_dataIdentifier == tac_telemetrySegmentTimeError )
            {
                // set the error code and break out of the loop
                v_telemetryStatus = tac_telemetrySegmentTimeError;
                break;
            }

            // if we lose communication
            if( v_dataIdentifier == tac_invalidIdentifierFrame )
            {
                // set the error code and break out of the loop
                v_telemetryStatus = tac_telemetryInvalidStateError;
                break;
            }
        }
    }

    // stop capturing
    TurnOffReceiver();

    // either we are done, timed out, or failed.  figure out which
    // so that we can return an appropriate status.
    if(GLB_HAS_LTMR_EXPIRED(StartTime, v_timeoutLimit))
    {
        v_telemetryStatus = tac_telemetryTimeout;
    }

    // there are 2 words (type and data) for each frame
    *p_uplinkSize = v_egmFrameCounter * 2;

    return (v_telemetryStatus);
}
