/************************************************************************
*
* MODULE: dbg_password.c
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the functions for the password.
*
*************************************************************************/

/////////////
// includes
/////////////

#include "global.h"
#include "bsm_SerialPort.h"
#include <string.h>

////////////
// defines
////////////
#define MAX_PASSWORD_SIZE 32
#define MAX_ATTEMPTS      3

////////////
// globals
////////////

static const char Password[] = "M3dtr()n|c";

/******************************************************************

FUNCTION: CheckPassword

DESCRIPTION: This function checks the password.

ARGS:
        <none>

RETURNS:
    TRUE if the password is entered correctly.
    FALSE if the password is wrong.

******************************************************************/
BOOL CheckPassword(void)
{
    UINT16 Attempts = 0;
    char   Buffer[MAX_PASSWORD_SIZE];

    while( Attempts < MAX_ATTEMPTS )
    {
        Attempts++;

        // prompt the user for the password
        bsm_SDPrint("Password: ");

        // read the password
        bsm_SDReadLine(Buffer, MAX_PASSWORD_SIZE);

        // if the password is correct, then return true
        if( strncmp(Buffer, Password, sizeof(Password)) == 0)
        {
            return TRUE;
        }
    }

    // if we tried enough times, then bail.
    return FALSE;
}


