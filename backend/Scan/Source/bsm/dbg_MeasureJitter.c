/************************************************************************
*
* MODULE: dbg_MeasureJitter.c
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the functions for measuring the jitter
*              of Telemetry A Pulses.
*
*************************************************************************/

/////////////
// Includes
/////////////
#include <stdlib.h>
#include <string.h>
#include "bsm_serialport.h"
#include "tam_TelemetryA.h"

#include "2490Gcfg.h"
////////////
// Globals
////////////

// variable to skip the jitter measurement of the first pulse
static UINT16 MeasureJitterState = 0;

// the maximum jitter
static UINT16 Jitter;

/////////////////////
// Local Prototypes
/////////////////////
void MeasureJitter(UINT16);
static void VoidFunc(UINT16);


/******************************************************************

FUNCTION: StartMeasuringJitter

DESCRIPTION: This function starts the jitter measure.

ARGS:
        <none>

RETURNS:
    <none>

******************************************************************/
void StartMeasuringJitter(void)
{
    bsm_SDPrint("Measuring Jitter");

    tam_Initialize_TelemetryA(tac_L88TelemProtocol);

    // Set the antenna to receive
    SetAntennaToReceive_M();

    // Reset this variable to skip the first pulse
    MeasureJitterState  = 0;

    // Reset the max jitter
    Jitter              = 0;

    // Point the receive interrupt to the measure jitter function
    ProcessReceivedData = MeasureJitter;

    TurnOnReceiver();
}

/******************************************************************

FUNCTION: StopMeasuringJitter

DESCRIPTION: This function stops the jitter measure.

ARGS:
        <none>

RETURNS:
    <none>

******************************************************************/
void StopMeasuringJitter(void)
{
    char   str[30] = "Max Jitter: ";
    UINT16 Length;

    bsm_SDPrint("Stopped Measuring Jitter");

    TurnOffReceiver();

    // point the receive interrupt to a dummy function
    ProcessReceivedData                  = VoidFunc;

    // print the max jitter
    Length                               = ltoa(Jitter, str + strlen("Max Jitter: "));
    str[strlen("Max Jitter: ") + Length] = 0;
    strcat(str+strlen(str), "us");
    bsm_SDPrint(str);
}

/******************************************************************

FUNCTION: MeasureJitter

DESCRIPTION: This function measures the jitter between edges.

ARGS:
        UINT16 CurrPulse: The time count of the next rising edge

RETURNS:
    <none>

******************************************************************/
void MeasureJitter(UINT16 CurrPulse)
{
    const INT16 NOMINAL_PERIOD_US = 200;

    static UINT16 StartEdge;

    INT16 Period;

    // if this is the first time, just mark the start time
    if( MeasureJitterState < 2 )
    {
        MeasureJitterState++;

        // clear the maximum jitter
        Jitter = 0;
    }
    else
    {
        // calculate the period
        Period = ((CurrPulse - StartEdge)*RX_MCBSP_BITS_PER_SAMPLE)/(RX_FREQUENCY/1000000);

        // if this period is bigger than the previous Max Jitter...
        if( abs( Period - NOMINAL_PERIOD_US ) > Jitter )
        {
            // save the new Maximum Jitter
            Jitter = abs( Period - NOMINAL_PERIOD_US );
        }
    }

    // the next pulse length is based off of this one.
    StartEdge = CurrPulse;
}

/******************************************************************

FUNCTION: VoidFunc

DESCRIPTION: This function does nothing.  It is used after we stop
                         counting pulses or measuring the jitter.

ARGS:
        UINT16 CurrPulse: Unused parameter

RETURNS:
    <none>

******************************************************************/
void VoidFunc(UINT16 CurrPulse)
{
}
