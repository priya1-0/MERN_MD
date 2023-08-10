/************************************************************************
*
* MODULE: dbg_CalculateCrc.c
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the functions to calculate the CRC for
*              the application.
*
*************************************************************************/

/////////////
// Includes
/////////////
#include "global.h"
#include "bsm_serialport.h"
#include "bsm_AppCrc.h"
#include "com_eepromapp.h"

/******************************************************************

FUNCTION: CalculateApplicationCrc

DESCRIPTION: This function calculates the CRC of the application
             in flash

ARGS:
        <none>

RETURNS:
    <none>

******************************************************************/
void CalculateApplicationCrc(void)
{
    char   Buffer[9];
    char   HexToAscii[] = "0123456789ABCDEF";
    UINT32 Crc;

    bsm_SDPrint("Calculating CRC");
    Crc       = CalculateCcitt32((UINT16*)bsc_FLASHBASEADDR+bsc_CODE_BLOCK_ADDR, 0, (bsc_CODE_BLOCK_LENGTH - 2)*2);

    Buffer[0] = HexToAscii[(Crc & 0xF0000000) >> 28];
    Buffer[1] = HexToAscii[(Crc & 0x0F000000) >> 24];
    Buffer[2] = HexToAscii[(Crc & 0x00F00000) >> 20];
    Buffer[3] = HexToAscii[(Crc & 0x000F0000) >> 16];
    Buffer[4] = HexToAscii[(Crc & 0x0000F000) >> 12];
    Buffer[5] = HexToAscii[(Crc & 0x00000F00) >>  8];
    Buffer[6] = HexToAscii[(Crc & 0x000000F0) >>  4];
    Buffer[7] = HexToAscii[(Crc & 0x0000000F) >>  0];
    Buffer[8] = 0;
    bsm_SDPrint("CRC:");
    bsm_SDPrint(Buffer);
}
