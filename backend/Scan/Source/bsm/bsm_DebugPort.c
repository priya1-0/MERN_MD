/************************************************************************
*
* MODULE: bsm_DebugPort.c
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the functions for all the debug
*              functionality.
*
*************************************************************************/

/////////////
// Includes
/////////////

#include "global.h"
#include "bsm_SerialPort.h"
#include "dbg_Password.h"
#include "bsm_DebugOperations.h"

#include <string.h>

////////////
// Defines
////////////
#define DEBUG_PORT_TIMEOUT 500
#define MAX_COMMAND_SIZE   64

////////////
// Globals
////////////

////////////////////////////////
// Private Function Prototypes
////////////////////////////////



/******************************************************************

FUNCTION: bsm_CheckDebugPort

DESCRIPTION: This function reads the command and parameters and
             stores them in a buffer.  ReadCommand returns when it
             finds a carriage return or line feed.

ARGS:
        <none>

RETURNS:
        <none>

******************************************************************/
void bsm_CheckDebugPort(void)
{
    GLB_LTMR_OBJ StartTime;
    UINT16       RxByte;
    char         Buffer[MAX_COMMAND_SIZE];

    bsm_SDPrint(":\n");
    GLB_GET_LTMR(StartTime);

    // look for a a host computer
    while( !GLB_HAS_LTMR_EXPIRED(StartTime, DEBUG_PORT_TIMEOUT) )
    {
        RxByte = bsm_SDRead();
        if( RxByte == '\r' || RxByte == '\n' )
        {
            break;
        }
    }

    // if there isn't a host computer continue with boot up
    if( GLB_HAS_LTMR_EXPIRED(StartTime, DEBUG_PORT_TIMEOUT) )
    {
        return;
    }

    // if the password is entered correctly...
    if( CheckPassword() )
    {
        do
        {
            bsm_SDPrint("Type HP, for a list of commands.");
            bsm_SDWrite(">", 1);

            // clear any previous command
            memset(Buffer, 0x00, MAX_COMMAND_SIZE);

            // read a command from the host computer
            bsm_SDReadLine(Buffer, MAX_COMMAND_SIZE);
            bsm_SDPrint("");
            bsm_SDPrint("");

            // execute the commands until it returns FALSE
        } while( ExecuteCommand(Buffer) );
    }
}
