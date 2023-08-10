/************************************************************************
*
* MODULE: dbg_speaker.c
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the functions for debugging the audio
*              speaker.
*
*************************************************************************/

/////////////
// Includes
/////////////
#include "bsm_serialport.h"
#include "bsm_Tone.h"

/******************************************************************

FUNCTION: SetAudioSpeaker

DESCRIPTION: This function turns on or off the audio speaker.

ARGS:
        <none>

RETURNS:
    <none>

******************************************************************/
void SetAudioSpeaker(char* CommandLineParameters)
{
    bsm_SDPrint("Setting Audio Speaker");

    // if the parameter is a '0', turn off the audio
    if( CommandLineParameters[0] == '0' )
    {
        bsm_TNStop();
        bsm_SDPrint("Audio Off");
    }
    // if the parameter is a '1', play 900Hz
    else if( CommandLineParameters[0] == '1' )
    {
        // Turn on the Audio to the low frequency
        bsm_TNSound(0, 0, 100, bsc_TONEMID, bsc_ONBEEP);
        bsm_SDPrint("Audio Low");
    }
    // if the parameter is a '2', play 2400Hz
    else if( CommandLineParameters[0] == '2' )
    {
        // Turn on the Audio to the high frequency
        bsm_TNSound(0, 0, 100, bsc_TONEHIGH, bsc_ONBEEP);
        bsm_SDPrint("Audio High");
    }
    // otherwise, print an error message
    else
    {
        bsm_SDPrint("Unknown Audio");
    }
}
