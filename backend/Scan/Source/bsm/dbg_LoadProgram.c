/************************************************************************
*
* MODULE: dbg_LoadProgram.c
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the functions to load a temporary program.
*
*************************************************************************/

/////////////
// Includes
/////////////
#include <csl.h>

#include "global.h"
#include "bsm_serialport.h"
#include "bsm_AppCrc.h"
#include "dbg_ReceiveXModem.h"
#include "dbg_Flash.h"
#include <csl_wdtim.h>

////////////
// Externs
////////////

// This is the beginning of the 2MB buffer for the NWM.
extern char returnbuffer;

typedef void (*APP_PTR)(void);

/******************************************************************

FUNCTION: LoadProgram

DESCRIPTION: This function loads a temporary program into memory
             and runs it.  The parameters are an 8 hex digit CRC
             and an 8 hex digit start address.

ARGS:
        char* Parameters: A pointer to a character buffer that has the
                          parameters.

RETURNS:
    <none>

******************************************************************/
void LoadProgram(char* Parameters)
{
    UINT32  Crc1;
    UINT32  Crc2;
    UINT32  Crc3;
    UINT32  Crc4;
    UINT32  AppCrc;
    UINT32  Addr1;
    UINT32  Addr2;
    UINT32  Addr3;
    UINT32  Addr4;
    UINT32  CalculatedCrc;
    char    * returnBuffer    = &returnbuffer;
    UINT32  ApplicationLength = 0;
    APP_PTR ApplicationAddr;

    // read in the CRC
    // skip the spaces
    while(*Parameters == ' ')
    {
        Parameters++;
    }

    Crc4        = PackByte(Parameters);
    Parameters += 2;
    Crc3        = PackByte(Parameters);
    Parameters += 2;
    Crc2        = PackByte(Parameters);
    Parameters += 2;
    Crc1        = PackByte(Parameters);
    Parameters += 2;

    AppCrc      = (Crc4 << 24) |
                  (Crc3 << 16) |
                  (Crc2 <<  8) |
                  (Crc1 <<  0);

    // read in the start address
    // skip the spaces
    while(*Parameters == ' ')
    {
        Parameters++;
    }

    Addr4           = PackByte(Parameters);
    Parameters     += 2;
    Addr3           = PackByte(Parameters);
    Parameters     += 2;
    Addr2           = PackByte(Parameters);
    Parameters     += 2;
    Addr1           = PackByte(Parameters);
    Parameters     += 2;

    ApplicationAddr = (APP_PTR)((Addr4 << 24) |
                                (Addr3 << 16) |
                                (Addr2 <<  8) |
                                (Addr1 <<  0));

    ApplicationLength = GetXModemFile(returnBuffer);

    // verify the CRC
    CalculatedCrc     = CalculateCcitt32((UINT16*)returnBuffer, 0, ApplicationLength*2);

    if( CalculatedCrc != AppCrc )
    {
        bsm_SDPrint("CRCs did not match.  The program was not executed.");
        return;
    }

    // if this will over write this function, don't do it
    if( ApplicationLength > (UINT32)LoadProgram )
    {
        bsm_SDPrint("Image will over write this function.  Cannot continue.");
        return;
    }

    // turn off interrupt while we are copying data
    DISABLE_INTERRUPTS;

    // disable the watchdog
    CHIP_FSET(TSSR, NMISEL, 0);
    CHIP_FSET(TSSR, IWCON, 0);

    {
        register UINT32  Source      = (UINT32)&returnbuffer;
        register UINT32  Destination = (UINT32)0x80;        // this is the normal spot for the vector table
        register UINT32  AppLength   = ApplicationLength;
        register APP_PTR AppAddr     = ApplicationAddr;

        while(AppLength)
        {
            *(UINT16*)Destination = *(UINT16*)Source;
            Destination++;
            Source++;
            AppLength--;
        }

        AppAddr();
    }
}
