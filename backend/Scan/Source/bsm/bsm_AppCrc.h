/************************************************************************
*
* MODULE: bsm_AppCrc.h
*
* OWNER:
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the functions to check the program
*
*************************************************************************/
#ifndef _BSM_APPCRC_H
#define _BSM_APPCRC_H

/////////////
// Includes
/////////////
#include "../global.h"

////////////
// Defines
////////////
#define FLASH_BEGIN_WORDS 0x200000
#define FLASH_SIZE_WORDS  0x100000
#define FLASH_END_WORDS   (FLASH_BEGIN_WORDS+FLASH_SIZE_WORDS)

#define CRC_LOCATION (FLASH_END_WORDS - 0x2000 - 2)

//////////
// Types
//////////


////////////
// Globals
////////////


///////////////
// Prototypes
///////////////


BOOL bsm_CheckProgram(void);
UINT16 aim_CRC(BYTE* DataPtr, UINT32 Length);
UINT16 aim_CRCPerByte(UINT16 InitialCRC, BYTE Data);
UINT16 CalculateProgramCrc(BYTE* DataPtr, UINT32 Length);
UINT32 CalculateCcitt32(UINT16* WordAddress, UINT32 ByteOffset, UINT32 NumOfBytes);

UINT32 bsm_AppCRCValue(void);

#endif
