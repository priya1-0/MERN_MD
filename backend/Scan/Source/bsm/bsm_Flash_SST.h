/************************************************************************
*
* MODULE: bsm_Flash_SST.h
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
* bsm_SST_Erase_CHIP()
* bsm_SST_Erase_BLCK()
* bsm_SST_Erase_SECT()
* bsm_SST_Read()
* bsm_SST_Write()
* bsm_SST_ID()
*
* --Private--
* gen_common()
* erase_common()
*
* DESCRIPTION: SST Flash driver header file
*
*************************************************************************/
#ifndef __SST_FLASH_H
#define __SST_FLASH_H
#include "global.h"

// FOLLOWING TIMES IN 1ms
#define SST_ERASE_CHIP_TSCE (100) //Tsce 100ms
#define SST_ERASE_BLCK_TBE  (25)  //Tbe  25ms
#define SST_ERASE_SECT_TSE  (25)  //Tse  25ms

// FOLLOWING TIMES IN 1ns
#define SST_WRITE_TBP     (20000)    //Tbp  20us
#define SST_ID_ENTRY_TIDA (150)   //Tida 150ns

// FLASH COMMANDS
// Common to all commands
#define SST_CMD_DATA_1 (0xAAAA)
#define SST_CMD_ADDR_1 (0x5555)
#define SST_CMD_DATA_2 (0x5555)
#define SST_CMD_ADDR_2 (0x2AAA)

// Write specific
#define SST_CMD_WRITE_DATA (0x00A0)
#define SST_CMD_WRITE_ADDR (0x5555)

// Erase common
#define SST_CMD_ERASE_DATA_1 (0x8080)
#define SST_CMD_ERASE_ADDR_1 (0x5555)
#define SST_CMD_ERASE_DATA_2 (0xAAAA)
#define SST_CMD_ERASE_ADDR_2 (0x5555)
#define SST_CMD_ERASE_DATA_3 (0x5555)
#define SST_CMD_ERASE_ADDR_3 (0x2AAA)

// Erase specific
#define SST_CMD_ERASE_CHIP_DATA (0x1010)
#define SST_CMD_ERASE_CHIP_ADDR (0x5555)

#define SST_CMD_ERASE_BLCK_DATA (0x5050)
// SST_CMD_ERASE_BLCK_ADDR is desired block

#define SST_CMD_ERASE_SECT_DATA (0x3030)
// SST_CMD_ERASE_SECT_ADDR is desired sector

// Identification specific
#define SST_CMD_ID_ENTRY_DATA (0x9090)
#define SST_CMD_ID_ENTRY_ADDR (0x5555)
#define SST_CMD_ID_EXIT_DATA  (0xF0F0)

// Identification information
#define SST_Manufact_ID_LOC (0x0000)
#define SST_Manufact_ID     (0x00BF)
#define SST_Device_ID_LOC   (0x0001)
#define SST_39VF200A        (0x2789) //SST39LF/VF200A 2789H
#define SST_39VF400A        (0x2780) //SST39LF/VF400A 2780H
#define SST_39VF800A        (0x2781) //SST39LF/VF800A 2781H
#define SST_39VF160A        (0x2782) //SST39LF/VF160A 2782H
#define SST_39VF320A        (0x2783) //SST39LF/VF320A 2783H
#define SST_39VF1601        (0x234b) //SST39LF/VF1601 234bH
#define SST_39VF3201        (0x235b) //SST39LF/VF3201 235bH
#define SST_39VF6401        (0x236b) //SST39LF/VF6401 236bH

// Status bits
#define SST_POLLING (0x8080)    //DQ7
#define SST_TOGGLE  (0x0040)    //DQ6

//when erased the word's value by default is:
#define bsm_SST_BLANK_FLASH (0xFFFF)


//Block Layout - 1MB
//#define SST_BLCK_NUMBLOCKS  (15)   //Really 16 but we're breaking the uppermost block into sectors
//#define SST_SECT_NUMBLOCKS  (16)   //


//Block Layout - 2MB
#define SST_BLCK_NUMBLOCKS (31)    //Really 32 but we're breaking the uppermost block into sectors
#define SST_SECT_NUMBLOCKS (16)    //

//General block information
#define SST_BLCK_NUMWORDS   (32768) // 32k words per block
#define SST_SECT_NUMWORDS   (2048) // 2k words per block
#define SST_TOTAL_NUMBLOCKS (SST_BLCK_NUMBLOCKS + SST_SECT_NUMBLOCKS)


// I/O configuration
// Macros


//FUNCTION DECLARATIONS
BOOL bsm_SST_Erase_CHIP(void);
BOOL bsm_SST_Erase_BLCK(UINT32 Offset);
BOOL bsm_SST_Erase_SECT(UINT32 Offset);
BOOL bsm_SST_Write(     UINT32 Offset, UINT16* Buffer);
void bsm_SST_Read(      UINT32 Offset, UINT16* Buffer);
BOOL bsm_SST_ID(void);
inline void gen_common(void);
inline void erase_common(void);

#endif
