/************************************************************************
*
* MODULE: dbg_led.c
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the functions for debugging the LEDs.
*
*************************************************************************/

/////////////
// Includes
/////////////
#include "bsm_led.h"
#include "bsm_serialport.h"
#include <stdlib.h>

/******************************************************************

FUNCTION: SetLed

DESCRIPTION: This function sets the LED to a value.

ARGS:
        UINT8 Led: The led to control.
        UINT8 OffOn: The state to change the LED to.

RETURNS:
    <none>

******************************************************************/
void SetLed(char* CommandLineParameters)
{
    bst_Led      Led;
    bst_LedState OffOn;

    bsm_SDPrint("Changing LED");

    // look for the LED number at the first location in the parameter list.
    if( CommandLineParameters[0] < '0' || CommandLineParameters[0] > '9' )
    {
        bsm_SDPrint("Usage: LE Led OnOff");
        bsm_SDPrint("Led : 0 to 15");
        bsm_SDPrint("On = 1, Off = 0");
    }

    Led = (bst_Led) atoi(CommandLineParameters);

    // look for the off/on state after the LED number.  the 2 is because there
    // is at least 1 digit for the LED and 1 space.
    OffOn = (bst_LedState) atoi(CommandLineParameters + (int)Led/10 + 2);

    // if the LED number makes sense...
    if( Led < bsc_MAXLEDS )
    {
        // if the OffOn variable makes sense...
        if( OffOn == bsc_LEDOFF ||
            OffOn == bsc_LEDON  ||
            OffOn == bsc_LEDFASTFLASH)
        {
            bsm_LDChange( (bst_Led)Led, (bst_LedState)OffOn);
            bsm_SDPrint("LED Set");
        }
        // otherwise, the OffOn variable is not a valid value
        else
        {
            bsm_SDPrint("LED State Unknown");
        }
    }
    // otherwise the Led number is not a valid value
    else
    {
        bsm_SDPrint("LED Number Unknown");
    }
}

