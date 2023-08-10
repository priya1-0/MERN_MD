/************************************************************************
*
* MODULE: tam_TelemetryA.c
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the functions to interface to all
*              Telemetry A functionality.
*
*************************************************************************/

/////////////
// Includes
/////////////
#include "global.h"

#include <csl.h>
#include <csl_mcbsp.h>
#include <csl_dma.h>
#include <csl_irq.h>
#include <csl_gpio.h>

#include "tam_RepeatTask.h"

#include "tam_global.h"

#define DEFINED_HERE
#include "tam_TelemetryA.h"
#undef DEFINED_HERE

#include "tam_TransmitCommon.h"
#include "tam_ReceiveCommon.h"
#include "tam_RepeatTask.h"
#include "bsm_Event.h"

////////////
// Defines
////////////

///////////
// Macros
///////////

//////////////////////
// global data
//////////////////////


/******************************************************************

FUNCTION: tam_Initialize_TelemetryA

DESCRIPTION: This function initializes the Telemetry A resources.

ARGS:
        tat_telemetryProtocolType v_protocolType: The type of
                telemetry we are going to use.

RETURNS:
    <none>

******************************************************************/
tat_status tam_Initialize_TelemetryA(tat_telemetryProtocolType Type)
{
    static BOOL OneTime = FALSE;

    // Configure the Antenna to receive
    InitializeTransmitEnable();
    SetAntennaToReceive_M();

    if( !OneTime )
    {
        OneTime          = TRUE;

        // Open the McBSP0 for Telemetry A Receive functionality.
        hMcbsp_TelemA    = MCBSP_open(MCBSP_PORT0, MCBSP_OPEN_RESET);
        // Open DMA channel for Tx DMA
        hDma_Tx          = DMA_open(DMA_CHA0,DMA_OPEN_RESET);
        // Open DMA channels for Rx DMA
        hDma_Rx          = DMA_open(DMA_CHA1,DMA_OPEN_RESET);
        // Open DMA channel for Tx Handshake DMA
        hDma_TxHandshake = DMA_open(DMA_CHA2,DMA_OPEN_RESET);
    }

    switch(Type)
    {
    case tac_L88TelemProtocol:
        Tw                  = TwL88;
        T0                  = T0L88;
        T1                  = T1L88;
        Tb                  = TbL88;
        Trb                 = TrbL88;
        Te                  = TeL88;
        Threply             = ThreplyL88;
        FrameTime           = FrameTimeL88;

        SamplesPerFrame     = (MESSAGE_LENGTH_L88*RX_FREQUENCY/DEVICE_FREQ/RX_MCBSP_BITS_PER_SAMPLE);
        NumPulsesPerFrame   = NUM_PULSES_PER_FRAME_L88;

        TelemetryType       = tac_L88TelemProtocol;

        ProcessReceivedData = ProcessReceivedDataL88;
        break;

    case tac_GemTelemProtocol:
        Tw                  = TwICD;
        T0                  = T0ICD;
        T1                  = T1ICD;
        Tb                  = TbICD;
        Trb                 = TrbICD;
        Te                  = TeICD;
        Threply             = ThreplyICD;
        FrameTime           = FrameTimeICD;

        SamplesPerFrame     = (MESSAGE_LENGTH_ICD*RX_FREQUENCY/DEVICE_FREQ/RX_MCBSP_BITS_PER_SAMPLE);
        NumPulsesPerFrame   = NUM_PULSES_PER_FRAME_ICD;

        TelemetryType       = tac_GemTelemProtocol;

        ProcessReceivedData = ProcessReceivedDataIcd;
        break;

    default:
        break;
    }

    return tac_successful;
}



/************************************************************************

FUNCTION:     tam_Send_Telemetry
DESCRIPTION:

This function will accept a downlink message intended for a device, and
transmit the complete message.  Than it will wait for the response.
 Note: Prior to this function performing its specified task, it
       checks that the repeat downlink command is not active.  If
       the repeat downlink is active, this function returns with
       a failure and does not attempt to execute its specified task.

ARGS:
        BYTE* p_downlinkMsg: Pointer to a message to downlink
        USHORT v_downlinkSize: Number of bytes in the downlink message
        BYTE *p_uplinkMsg: Pointer to a buffer to store the uplink message
        USHORT v_uplinkSize: Number of bytes to uplink
        BYTE v_tmTimeoutDuration: Number of 10 milliseconds to wait for uplink

RETURNS:
        tat_status: tac_successful if everything happened

*************************************************************************/
tat_status tam_Send_Telemetry(  BYTE   *p_downlinkMsg,
                                USHORT v_downlinkSize,
                                BYTE   *p_uplinkMsg,
                                USHORT v_uplinkSize,
                                BYTE   v_tmTimeoutDuration)
{
    // if the repeat task is running, return
    if (IsRepeatDownlinkActive())
    {
        return tac_repeatDownlinkActive;
    }

    // Initialize the AGC
    InitializeAgc();
    AgcPulseSelect = HIGH_GAIN;

    // if there are bytes to send, send them
    if( v_downlinkSize )
    {
        TransmitDownlinkBuffer(p_downlinkMsg, v_downlinkSize);
    }
    else
    {
        bsm_EHLock("Tried to transmit 0 bytes");
    }

    // if there are bytes to receive, receive them
    if( v_uplinkSize )
    {
        return ReceiveMemoryUplink(v_uplinkSize, v_tmTimeoutDuration, p_uplinkMsg);
    }
    else
    {
        bsm_EHLock("Tried to receive 0 bytes");
    }

    return tac_successful;
}
