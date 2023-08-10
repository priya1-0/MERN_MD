/************************************************************************
*
* MODULE: bsm_Flash.h
*
* OWNER:
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* FUNCTIONS:
* --Public--
* bsm_Flash_Read_With_Packed()
* bsm_Flash_Read_With_Unpacked()
* bsm_Flash_Write_With_Packed()
* bsm_Flash_Write_With_Unpacked()
* bsm_Flash_Erase_BLCK()
* bsm_Flash_Erase_SECT()
* bsm_Flash_Init()
* bsc_Flash_Type bsm_Flash_Get_Type()
*
* --Private--
*
* DESCRIPTION: Flash Wrapper Header File
*
*************************************************************************/
#ifndef __FLASH_H
#define __FLASH_H

#include "global.h"
#include "com_eepromapp.h" //for bsc_Flash_Type


#define bsm_EEnumByteTOnumWord(x) ((x)/2 + (x)%2) //Convert from byte to word rounded up.

//FUNCTION DECLARATIONS
BOOL bsm_Flash_Read_With_Packed(   UINT32 Offset, UINT16* Buffer, UINT32 Length);
BOOL bsm_Flash_Read_With_Unpacked( UINT32 Offset, BYTE*   Buffer, UINT32 Length);
BOOL bsm_Flash_Write_With_Packed(  UINT32 Offset, UINT16* Buffer, UINT32 Length);
BOOL bsm_Flash_Write_With_Unpacked(UINT32 Offset, BYTE*   Buffer, UINT32 Length);
BOOL bsm_Flash_Write_With_Unaligned_Packed(UINT32 destOffset, UINT16* basePtr, UINT32 byteOffset, UINT32 Length);
BOOL bsm_Flash_Erase_BLCK(    UINT32 Offset);
BOOL bsm_Flash_Erase_SECT(    UINT32 Offset);
BOOL bsm_Flash_Init(void);
bsc_Flash_Type bsm_Flash_Get_Type(void);
inline void bsm_Flash_Set_Inprogress(BOOL newState);
inline BOOL bsm_Flash_Get_Inprogress();

void bsm_Flash_Test(void);


#endif

