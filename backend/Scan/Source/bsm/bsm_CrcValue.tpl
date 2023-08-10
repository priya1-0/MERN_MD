/************************************************************************
*
* MODULE: bsm_CrcValue.c
*
* OWNER: 
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the CRC value of the program.  The .tpl 
*              file is used by WinCRC to create a CRC value of the program.
*              The .tpl file is then copied to a .c file with the CRC value 
*              filled in.
*
*************************************************************************/

/////////////
// Includes
/////////////
#include "global.h"

////////////
// Globals
////////////
#ifndef SKIP_CRC
#pragma DATA_SECTION(StoredCrcL, ".crc");
#pragma DATA_SECTION(StoredCrcH, ".crc");

UINT16 StoredCrcH;
UINT16 StoredCrcL;

#endif
