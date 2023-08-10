/************************************************************************
*
* MODULE: dbg_SendTelemAMessage.c
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the function to test talking to a
*              TelemA device.
*
*************************************************************************/

/////////////
// Includes
/////////////
#include "global.h"
#include "tam_TelemetryA.h"
#include "tam_ItemMap.h"
#include "bsm_SerialPort.h"
#include <stdlib.h>
#include <string.h>

////////////
// Globals
////////////
#define tac_MAP_UPLINK_SIZE 132         // Header 2 bytes, Data bytes (128
                                        // bytes) and trailer 2 bytes (CRC)

#ifdef __DEV_VT__
/******************************************************************

FUNCTION: SendTelemetryAMessage

DESCRIPTION: This function sends the Item Mapper messages without
             triggering to the device.

ARGS:
        char* CommandLine: Format "[G|K] [NumberOfMessages]"

RETURNS:
    <none>

******************************************************************/
void SendTelemetryAMessage(char* CommandLine)
{
    // format "ST [G|K] [NumberOfMessages]"

    tat_telemetryProtocolType TelemetryType;
    UINT16                    NumberOfMessages;
    UINT16                    i;
    tat_status                v_status;
    UINT16                    Pass = 0;
    UINT16                    Fail = 0;
    char                      Buffer[10];

    if( CommandLine[0] == 'G' )
    {
        TelemetryType = tac_GemTelemProtocol;
    }
    else if( CommandLine[0] == 'K' )
    {
        TelemetryType = tac_L88TelemProtocol;
    }
    else
    {
        bsm_SDPrint("Unrecognized Telemetry Type.  Defaulting to GEM.");
        TelemetryType = tac_GemTelemProtocol;
    }

    tam_Initialize_TelemetryA(TelemetryType);

    NumberOfMessages = atoi( &(CommandLine[2]) );

    for( i = 0; i < NumberOfMessages; i++ )
    {
        if( TelemetryType == tac_GemTelemProtocol )
        {
            v_status = tam_Perform_Universal_Map();
        }
        else
        {
            v_status = tam_Perform_IPG_Universal_Map();
        }

        if( v_status == tac_successful )
        {
            Pass++;
        }
        else
        {
            char Buffer[64];
            Fail++;

            Buffer[0] = 0;

            switch( v_status )
            {
            case tac_downlinkCommandFailed: strcat(Buffer, "Downlink Failed"); break;
            case tac_repeatDownlinkActive: strcat(Buffer, "Repeat Downlink Active"); break;
            case tac_badTelemetryType: strcat(Buffer, "Bad Telemetry Type"); break;
            case tac_unsuccessfulHandshake: strcat(Buffer, "Unsuccessful handshake"); break;
            case tac_nonAckResponse: strcat(Buffer, "Non-ACK response"); break;
            case tac_temporaryOperationCompleted: strcat(Buffer, "Temp Operation Complete"); break;
            case tac_telemetryError: strcat(Buffer, "Telemetry Error"); break;
            case tac_telemetryTimeout: strcat(Buffer, "Telemetry Timeout"); break;
            case tac_telemetryCRCError: strcat(Buffer, "CRC Error"); break;
            case tac_telemetrySegmentTimeError: strcat(Buffer, "Time Segment Error"); break;
            case tac_telemetryMemoryFrameInterruptedError: strcat(Buffer, "Memory Frame interrupt"); break;
            case tac_telemetryInvalidParityCheckError: strcat(Buffer, "Parity Error"); break;
            case tac_markerDoubleFrameFailure: strcat(Buffer, "Double Marker Error"); break;
            case tac_telemetryParityError: strcat(Buffer, "Parity Error"); break;

            default:
            case tac_unknownError: strcat(Buffer, "Unknown Error"); break;
            }
            bsm_SDPrint("##################");
            bsm_SDPrint(Buffer);
            bsm_SDPrint("##################");
        }
    }

    ltoa(Pass, Buffer);
    bsm_SDPrint("Number of Messages that Passed:");
    bsm_SDPrint(Buffer);

    bsm_SDPrint("");

    ltoa(Fail, Buffer);
    bsm_SDPrint("Number of Messages that Failed:");
    bsm_SDPrint(Buffer);

}
#endif // __DEV_VT__

