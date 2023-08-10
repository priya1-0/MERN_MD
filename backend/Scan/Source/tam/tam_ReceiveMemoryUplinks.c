/************************************************************************
*
* MODULE: tam_ReceiveMemoryUplinks.c
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the functions receive memory frames
*              from the implant.
*
*************************************************************************/

#include "tam_global.h"
#include "tam_TelemetryA.h"

/******************************************************************

FUNCTION: ReceiveMemoryUplink

DESCRIPTION:  This function is called to receive memory bytes from
              the implant.

ARGS:
        UINT16 CurrPulse: The next pulse that has come in.

RETURNS:
        <none>

******************************************************************/
tat_status ReceiveMemoryUplink(USHORT expectedUplinkBytes,
                               BYTE   timeoutLimit,
                               BYTE   *uplinkBuffer)
{
    switch( TelemetryType )
    {
    case tac_L88TelemProtocol:
        return ReceiveMemoryUplinkL88(expectedUplinkBytes,
                                      timeoutLimit,
                                      uplinkBuffer);

    case tac_GemTelemProtocol:
        return ReceiveMemoryUplinkIcd(expectedUplinkBytes,
                                      timeoutLimit,
                                      uplinkBuffer);

    default:
        return tac_badTelemetryType;
    }
}

/******************************************************************

FUNCTION: ReceiveMemoryUplinkL88

DESCRIPTION:  This function is called to receive memory bytes from
              the implant.

ARGS:
        UINT16 CurrPulse: The next pulse that has come in.

RETURNS:
        <none>

******************************************************************/
tat_status ReceiveMemoryUplinkL88(USHORT expectedUplinkBytes,
                                  BYTE   timeoutLimit,
                                  BYTE   *uplinkBuffer)
{
    tat_status v_telemetryStatus             = tac_telemetryError;
    USHORT     v_memoryFrameCounter          = 0; // number of memory frames received
    USHORT     v_memoryFrameInterruptCounter = 0;  // used to keep track of
    // how many times a memory
    // frame get interrupted
    tat_frameType v_dataIdentifier           = tac_invalidIdentifierFrame;
    // data identifier associated with
    // current uplink frame
    BOOL v_memoryFrameFound                  = FALSE; // flag indicating occurrence of
    // memory frame
    BYTE v_data;                             // data associated with the current
    // uplink frame
    GLB_LTMR_OBJ StartTime;

    TurnOnReceiver();

    // set timeout timer
    GLB_GET_LTMR(StartTime);

    // collect memory frames
    while (v_memoryFrameCounter < expectedUplinkBytes)
    {
        if( GLB_HAS_LTMR_EXPIRED(StartTime, timeoutLimit*10) )
        {
            break;
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

            // Only perform frame processing and data storage once memory frame
            // is found
            if (v_memoryFrameFound)
            {
                // Determine if the memory frame is successful
                if (v_telemetryStatus == tac_successful &&
                    v_dataIdentifier == tac_memoryFrame)
                {
                    // store data
                    uplinkBuffer[v_memoryFrameCounter] = v_data;

                    // increment frame counter
                    v_memoryFrameCounter++;
                }
                else
                {                       // Note: handshake request, marker and handshake
                                        // confirmation frame are allowed to interrupt
                                        // memory uplinks
                    if ((v_telemetryStatus == tac_successful) &&
                        (v_dataIdentifier == tac_handshakeRequestFrame ||
                         v_dataIdentifier == tac_markerFrame ||
                         v_dataIdentifier == tac_handshakeConfirmFrame))
                    {
                        v_memoryFrameInterruptCounter++;
                    }
                    else
                    {
                        /* memory frame not successful or non-memory frame
                        interrupted memory uplink, break out of while loop */
                        if (v_telemetryStatus == tac_successful)
                        {
                            v_telemetryStatus = tac_telemetryMemoryFrameInterruptedError;
                        }

                        break;                         // break out of the while loop
                    }
                }
            }
            else
            {
                // check to see if a memory frame have been received
                if (v_telemetryStatus == tac_successful &&
                    v_dataIdentifier == tac_memoryFrame)
                {
                    v_memoryFrameFound                 = TRUE;

                    // store data
                    uplinkBuffer[v_memoryFrameCounter] = v_data;

                    // increment frame counter
                    v_memoryFrameCounter++;
                }
            }
        }
        else
        {
            v_telemetryStatus = tac_telemetryError;
        }
    }

    // check for a timeout
    if( GLB_HAS_LTMR_EXPIRED(StartTime, timeoutLimit*10) )
    {
        v_telemetryStatus = tac_telemetryTimeout;
    }
    return (v_telemetryStatus);
}

/******************************************************************

FUNCTION: ReceiveMemoryUplinkIcd

DESCRIPTION:  This function is called to receive memory bytes from
              the implant.

ARGS:
        UINT16 CurrPulse: The next pulse that has come in.

RETURNS:
        <none>

******************************************************************/
tat_status ReceiveMemoryUplinkIcd(USHORT expectedUplinkBytes,
                                  BYTE   timeoutLimit,
                                  BYTE   *uplinkBuffer)
{
    tat_status    v_telemetryStatus    = tac_successful;
    USHORT        v_memoryFrameCounter = 0;  // number of memory frames received
    tat_frameType v_dataIdentifier     = tac_invalidIdentifierFrame;
    // data identifier associated with
    // current uplink frame
    BOOL v_memoryFrameFound            = FALSE; // flag indicating occurrence of
                                                // memory frame
    BYTE v_data;                             // data associated with the current
                                             // uplink frame
    GLB_LTMR_OBJ StartTime;

    TurnOnReceiver();

    /* set timeout timer */
    GLB_GET_LTMR(StartTime);

    /* collect memory frames */
    while (v_memoryFrameCounter < expectedUplinkBytes)
    {
        if( GLB_HAS_LTMR_EXPIRED(StartTime, timeoutLimit*10) )
        {
            break;
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

            // Only perform frame processing and data storage once memory frame
            // is found
            if (v_memoryFrameFound)
            {
                // Determine if the memory frame is successful
                if (v_telemetryStatus == tac_successful &&
                    v_dataIdentifier == tac_memoryFrame)
                {
                    /* store data */
                    uplinkBuffer[v_memoryFrameCounter] = v_data;

                    /* increment frame counter */
                    v_memoryFrameCounter++;
                }
                else
                {
                    /* memory frame not successful or non-memory frame interrupted
                    memory uplink, break out of while loop */
                    v_telemetryStatus = tac_telemetryMemoryFrameInterruptedError;

                    break;                     // break out of the while loop
                }
            }
            else
            {
                // check to see if a memory frame have been received
                if (v_telemetryStatus == tac_successful &&
                    v_dataIdentifier == tac_memoryFrame)
                {
                    v_memoryFrameFound                 = TRUE;

                    /* store data */
                    uplinkBuffer[v_memoryFrameCounter] = v_data;

                    /* increment frame counter */
                    v_memoryFrameCounter++;
                }
            }
        }
        else
        {
        }
    }

    // we are done getting the memory bytes, so stop receiving
    TurnOffReceiver();

    if( GLB_HAS_LTMR_EXPIRED(StartTime, timeoutLimit*10) )
    {
        v_telemetryStatus = tac_telemetryTimeout;
    }

    return (v_telemetryStatus);
}
