/************************************************************************
*
* MODULE: dbg_CountPulses.c
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the functions for counting Telemetry A
*              pulses.
*
*************************************************************************/

/////////////
// Includes
/////////////
#include <stdlib.h>
#include <string.h>
#include "bsm_serialport.h"
#include "tam_TelemetryA.h"

////////////
// Globals
////////////

// number of pulses we captured
static UINT16 Pulses;

/////////////////////
// Local Prototypes
/////////////////////
void PulseCounter(UINT16);
static void VoidFunc(UINT16);

/******************************************************************

FUNCTION: StartCountingPulses

DESCRIPTION: This function starts the pulse counting ISR.

ARGS:
        <none>

RETURNS:
    <none>

******************************************************************/
void StartCountingPulses(void)
{
    bsm_SDPrint("Counting Pulses");

    tam_Initialize_TelemetryA(tac_L88TelemProtocol);

    // Set the antenna to receive
    SetAntennaToReceive_M();

    // set the receive interrupt to call this function when it gets a pulse
    ProcessReceivedData = PulseCounter;

    // reset the the number of pulses
    Pulses              = 0;

    TurnOnReceiver();
}

/******************************************************************

FUNCTION: StopCountingPulses

DESCRIPTION: This function stops the pulse counting ISR

ARGS:
        <none>

RETURNS:
    <none>

******************************************************************/
void StopCountingPulses(void)
{
    char str[30] = "Number Of Pulses: ";

    bsm_SDPrint("Stopped Counting Pulses");

    TurnOffReceiver();

    // point the receive interrupt to a dummy function
    ProcessReceivedData = VoidFunc;

    // Print the number of pulses
    ltoa(Pulses, str + strlen("Number Of Pulses: "));
    str[strlen("Number Of Pulses: ") + Pulses/10 + 1] = 0;
    bsm_SDPrint(str);
}

/******************************************************************

FUNCTION: PulseCounter

DESCRIPTION: This function counts the number of pulses.

ARGS:
        UINT16 CurrPulse: Unused parameter

RETURNS:
    <none>

******************************************************************/
void PulseCounter(UINT16 CurrPulse)
{
    // Each time this function is called, we got another pulse
    Pulses++;
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

