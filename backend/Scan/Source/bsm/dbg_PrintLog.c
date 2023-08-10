/************************************************************************
*
* MODULE: dbg_PrintLog.c
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the function for printing the log.
*
*************************************************************************/

/////////////
// Includes
/////////////
#include "bsm_serialport.h"
#include "bsm_Event.h"
#include <stdlib.h>

/******************************************************************

FUNCTION: PrintLog

DESCRIPTION: This function prints all the log messages that are in
             the flash.

ARGS:
        <none>

RETURNS:
    <none>

******************************************************************/
void PrintLog(void)
{
    char          Message[bsc_EHMAXLOGENTRY];
    int           Code;
    unsigned long Time;

    bsm_EHResetLogReadPointer();

    // loop while we still have messages
    while (bsm_EHReadNextEntry(Message, &Code, &Time))
    {
        bsm_SDPrint(Message);
    }

}
