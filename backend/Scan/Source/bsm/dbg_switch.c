/************************************************************************
*
* MODULE: dbg_switch.c
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the functions for debugging the dial
*              and prefix switches.
*
*************************************************************************/

/////////////
// Includes
/////////////
#include "bsm_serialport.h"
#include "bsm_SwitchInput.h"

/******************************************************************

FUNCTION: ReadPulseToneSwitch

DESCRIPTION: This function reads the Pulse Tone switch.

ARGS:
        <none>

RETURNS:
    <none>

******************************************************************/
void ReadPulseToneSwitch(void)
{
    bst_ToneSwitchState Switch;

    bsm_SDPrint("Reading Pulse/Tone Switch");

    // Read the switch
    Switch = bsm_INReadTonePulse();

    // Based on the switch position, print a statement
    if( Switch == bsc_TONE )
    {
        bsm_SDPrint("Tone");
    }
    else
    {
        bsm_SDPrint("Pulse");
    }
}

/******************************************************************

FUNCTION: ReadPrefixSwitch

DESCRIPTION: This function reads the Prefix switch.

ARGS:
        <none>

RETURNS:
    <none>

******************************************************************/
void ReadPrefixSwitch(void)
{
    bst_DialSwitchState Switch;

    bsm_SDPrint("Reading Prefix Switch");

    // read the switch
    Switch = bsm_INReadDial();

    // based on the switch position, print a statement
    if( Switch == bsc_DIAL1 )
    {
        bsm_SDPrint("Prefix 1");
    }
    else if( Switch == bsc_DIAL2 )
    {
        bsm_SDPrint("Prefix 2");
    }
    else if( Switch == bsc_DIAL3 )
    {
        bsm_SDPrint("Prefix 3");
    }
    else
    {
        bsm_SDPrint("Prefix 4");
    }
}

