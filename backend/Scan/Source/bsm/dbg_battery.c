/************************************************************************
*
* MODULE: dbg_battery.c
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the functions for debugging the battery
*              threshold.
*
*************************************************************************/

/////////////
// Includes
/////////////
#include "bsm_serialport.h"
#include "bsm_power.h"

/******************************************************************

FUNCTION: ReadBatteryThreshold

DESCRIPTION: This function reads the battery threshold pin and
                         writes the value to the ResultsBuffer

ARGS:
        <none>

RETURNS:
        <none>

******************************************************************/
void ReadBatteryThreshold(void)
{
    if( bsm_IsBatteryGood() )
    {
        bsm_SDPrint("Battery Good");
    }
    else
    {
        bsm_SDPrint("Battery Bad");
    }
}
