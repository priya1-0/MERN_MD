/************************************************************************
*
* MODULE: tam_RepeatTask.c
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the functions to continuously send a
*              downlink message to the device.
*
*************************************************************************/

/////////////
// includes
/////////////
#include "global.h"
#include "2490Gcfg.h"

#include <csl.h>
#include <csl_gpio.h>

#include "tam_global.h"
#include "tam_transmitcommon.h"
#include "tam_TelemetryA.h"

////////////
// defines
////////////
#define MAX_TRANSMIT_LENGTH 10

////////////
// globals
////////////
USHORT RepeatDownlinkSize  = 0;
BYTE   RepeatDownlinkSleep = 0;
BYTE   RepeatDownlinkCount;
BYTE   RepeatDownlinkBuffer[MAX_TRANSMIT_LENGTH];

/******************************************************************

FUNCTION: IsRepeatDownlinkActive

DESCRIPTION: This function checks to see if the repeat downlink is
             active.

ARGS:
        <none>

RETURNS:
    TRUE if the downlink is active,
    FALSE is the downlink is not active.

******************************************************************/
BOOL IsRepeatDownlinkActive(void)
{
    return (RepeatDownlinkSleep > 0);
}

/************************************************************************

FUNCTION:     tam_Repeat_Downlink
DESCRIPTION: This functions sets a task to downlink a message every couple
                         seconds to keep the implant active.

ARGS:
        BYTE *p_downlinkMsg: Message to downlink
        USHORT v_downlinkSize: Number of bytes to downlink
        BYTE v_repeatInterval: Number of seconds between downlink

RETURNS:
        tat_status: tac_successful if everything happened

*************************************************************************/
tat_status tam_Repeat_Downlink(BYTE   * p_downlinkMsg,
                               USHORT v_downlinkSize,
                               BYTE   v_repeatInterval)
{
    switch( TelemetryType )
    {
    case tac_L88TelemProtocol:
        return tac_badTelemetryType;

    case tac_GemTelemProtocol:
        if( v_downlinkSize <= MAX_TRANSMIT_LENGTH )
        {
            DISABLE_INTERRUPTS;

            memcpy(RepeatDownlinkBuffer, p_downlinkMsg, v_downlinkSize);
            RepeatDownlinkSize  = v_downlinkSize;
            RepeatDownlinkSleep = v_repeatInterval;

            RepeatDownlinkCount = 0;

            ENABLE_INTERRUPTS;

            return tac_successful;
        }
        else
        {
            return tac_unknownError;
        }

    default:
        return tac_badTelemetryType;
    }
}

/************************************************************************

FUNCTION:     tam_Cancel_Repeat_Downlink
DESCRIPTION: This functions stops the task from sending the message

ARGS:
        <none>

RETURNS:
        tat_status: tac_successful if everything happened

*************************************************************************/
tat_status tam_Cancel_Repeat_Downlink(void)
{
    switch( TelemetryType )
    {
    case tac_L88TelemProtocol:
        return tac_badTelemetryType;

    case tac_GemTelemProtocol:
        DISABLE_INTERRUPTS;
        RepeatDownlinkSleep = 0;
        ENABLE_INTERRUPTS;

        return tac_successful;

    default:
        return tac_badTelemetryType;
    }
}

/******************************************************************

FUNCTION: RepeatSwiFunction

DESCRIPTION: This function is called once per second from the DSP/BIOS
             periodic function manager.  If the repeat transmit is
             active, then the function waits RepeatDownlinkSleep
             seconds and then schedules a message to be sent.

ARGS:
        <none>

RETURNS:
    <none>

******************************************************************/
void RepeatSwiFunction(void)
{
    if( RepeatDownlinkSleep > 0 )
    {
        RepeatDownlinkCount++;

        if (RepeatDownlinkCount >= RepeatDownlinkSleep)
        {
            RepeatDownlinkCount = 0;
            SWI_post(&SWI_RepeatTransmit);
        }
    }
}

/******************************************************************

FUNCTION: tam_Repeat_Transmit

DESCRIPTION: This function downlinks the data to the device

ARGS:
        <none>

RETURNS:
    <none>

******************************************************************/
void tam_Repeat_Transmit(void)
{
    TransmitShortMessage(RepeatDownlinkBuffer, RepeatDownlinkSize);
}
