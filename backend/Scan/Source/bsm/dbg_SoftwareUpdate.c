/************************************************************************
*
* MODULE: dbg_SoftwareUpdate.c
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the functions to update the software.
*
*************************************************************************/

/////////////
// Includes
/////////////
#include <csl.h>

#include "global.h"
#include "bsm_serialport.h"
#include "bsm_AppCrc.h"
#include "bsm_SUSoftwareUpdate.h"
#include "dbg_Flash.h"
#include "dbg_ReceiveXModem.h"
#include "fsm_pbfr.h"
#include "zlm_decompress.h"

////////////
// Externs
////////////

// This is the beginning of the 2MB buffer for the NWM.
extern char returnbuffer;

/******************************************************************

FUNCTION: SoftwareUpdate

DESCRIPTION: This function burns a full application program into
             flash.  The parameters has the CRC of the application.

ARGS:
        char* Parameters: A pointer to a character buffer that has the
                          CRC of the application

RETURNS:
    <none>

******************************************************************/
void SoftwareUpdate(char* Parameters)
{
    UINT32 Crc1;
    UINT32 Crc2;
    UINT32 Crc3;
    UINT32 Crc4;
    UINT32 AppCrc;
    UINT32 CalculatedCrc;
    char   * returnBuffer    = &returnbuffer;
    UINT32 ApplicationLength = 0;
    UINT32 numBytesL;

    ApplicationLength = GetXModemFile(returnBuffer);

    // verify the CRC

    if( ApplicationLength < 4 )
    {
        bsm_SDPrint("Not enough data");
        return;
    }

    if (zlm_IsCompressed((UINT16*)&returnbuffer, 0L, ApplicationLength*2))
    {
        bsm_SDPrint("Compressed image found - decompressing.");

        numBytesL = zlm_UnpackFirmwareImage((UINT16*)&returnbuffer, 0, ApplicationLength*2);

        if (0 == numBytesL)
        {
            bsm_SDPrint("Decompression failed.");
            return;
        }

        ApplicationLength = numBytesL / 2;         // Set word length
        bsm_SDPrint("Decompression was successful.");
    }

    bsm_SDPrint("Calculating CRC...");
    CalculatedCrc = CalculateCcitt32((UINT16*)returnBuffer, 0, ApplicationLength*2 - 4);

    AppCrc        = (UINT32)(*(UINT16*)((UINT32)returnBuffer+ApplicationLength-1)) |
                    ((UINT32)(*(UINT16*)((UINT32)returnBuffer+ApplicationLength-2))<< 16);

    if( CalculatedCrc != AppCrc )
    {
        bsm_SDPrint("CRCs did not match.  Flash has not been updated.");
        return;
    }

    bsm_SDPrint("CRCs matched.  Burning image into Flash.");
    // burn the new application into flash
    if( bsm_SUDoUpdate((UINT16*)returnBuffer, 0, ApplicationLength*2) )
    {
        bsm_SDPrint("Application updated SUCCESSFUL.");
    }
    else
    {
        bsm_SDPrint("FAILURE in update.  Flash may be corrupt.  Try again.");
    }
}
