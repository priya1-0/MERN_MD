/************************************************************************
*
* MODULE: bsm_Flash_Intel.h
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
* bsm_Intel_Read()
* bsm_Intel_Erase_BLCK()
* bsm_Intel_Write()
* bsm_Intel_ID()
* bsm_Intel_Poll_For_Status()
* bsm_Intel_UnlockBlock()
*
* --Private--
*
* DESCRIPTION: Intel Flash driver header file
*
*************************************************************************/
#ifndef __INTEL_FLASH_H
#define __INTEL_FLASH_H

#include "global.h"

// FOLLOWING TIMES IN 1ms
#define INTEL_ERASE_BLCK_TIME (5000)     // T = 5sec
#define INTEL_ERASE_SECT_TIME (4000)     // T = 4sec

// FOLLOWING TIMES IN 1ns
#define INTEL_WRITE_TIME (201000)           // T = 201us


// FLASH COMMANDS
#define INTEL_CMD_READ_ARRAY (0xFF)     //Must be issued after any other command cycle before
                                        //array can be read.
#define INTEL_CMD_READ_IDENTIFIER (0x90) //Puts the device into the read-identifier mode so that
                                         //reading the device will output the manufacturer/device
                                         //codes or block-lock status.
#define INTEL_CMD_READ_STATUS  (0x70)   //Allows the status register to be read.
#define INTEL_CMD_CLEAR_STATUS (0x50)   //Clears status register bits 3-5.
#define INTEL_CMD_WRITE        (0x40)   //Write data and address are given in the following cycle
                                        //to complete the WRITE.
#define INTEL_CMD_ERASE_1 (0x20)        //The first command given in the two-cycle ERASE sequence.
#define INTEL_CMD_ERASE_2 (0xD0)        //The second command given in the two-cycle ERASE sequence.

#define INTEL_CMD_UNLOCK_1 (0x60)       //The first command given in the two-cycle UNLOCK sequence
#define INTEL_CMD_UNLOCK_2 (0xD0)       //The second command given in the two-cycle UNLOCK sequence.


// STATUS BITS
#define SR7 (0x80) // Write Machine STATUS 1 = Ready;                   0 = Busy
#define SR6 (0x40) // ERASE SUSPEND STATUS 1 = ERASE suspended;         0 = ERASE in progress/completed
#define SR5 (0x20) // ERASE STATUS         1 = BLOCK ERASE;             0 = Successful BLOCK ERASE
#define SR4 (0x10) // WRITE STATUS         1 = WORD/BYTE WRITE error;   0 = Successful WORD/BYTE WRITE
#define SR3 (0x08) // VPP STATUS           1 = No VPP voltage detected; 0 = VPP present
#define SR2 (0x04) // WRITE SUSPEND STATUS 1 = WRITE suspended;         0 = WRITE in progress/completed
#define SR1 (0x02) // BLOCK LOCK STATUS    1 = Block is locked;         0 = Block not locked

#define UNLOCK_LOCATION       (0x0002)
#define UNLOCK_STATUS_MASK    (0x0001)
#define UNLOCK_STATUS_DESIRED (0x0000)

// Identification information
#define INTEL_Manufact_ID_LOC (0x0000)
#define INTEL_Manufact_ID     (0x0089)

#define INTEL_DEVICE_ID_LOC      (0x0001)
#define INTEL_DEVICE_8Mb_TOP     (0x88C0)
#define INTEL_DEVICE_8Mb_BOTTOM  (0x88C1)
#define INTEL_DEVICE_16Mb_TOP    (0x88C2)
#define INTEL_DEVICE_16Mb_BOTTOM (0x88C3)
#define INTEL_DEVICE_32Mb_TOP    (0x88C4)
#define INTEL_DEVICE_32Mb_BOTTOM (0x88C5)
#define INTEL_DEVICE_64Mb_TOP    (0x88CC)
#define INTEL_DEVICE_64Mb_BOTTOM (0x88CD)

//when erased the word's value by default is:
#define bsm_INTEL_BLANK_FLASH (0xFFFF)

//Block Layout 2MB
#define INTEL_BLCK_NUMBLOCKS (31)
#define INTEL_SECT_NUMBLOCKS (8)


//Block Layout 1MB
//#define INTEL_BLCK_NUMBLOCKS  (15)
//#define INTEL_SECT_NUMBLOCKS  (8)

//General block information
#define INTEL_BLCK_NUMWORDS   (32768) /* words per block */
#define INTEL_SECT_NUMWORDS   (4096) /* words per block */
#define INTEL_TOTAL_NUMBLOCKS (INTEL_BLCK_NUMBLOCKS +INTEL_SECT_NUMBLOCKS)


// I/O configuration
// Macros
//TYPE DECLARATIONS
typedef enum
{
    bsc_INTEL_WRITE=0,
    bsc_INTEL_ERASE,
    bsc_INTEL_READ
}  bsc_INTEL_CMD_Type;

//FUNCTION DECLARATIONS
void   bsm_Intel_Read(      UINT32 Offset, UINT16* Buffer);
BOOL   bsm_Intel_Erase_BLCK(UINT32 Offset);
BOOL   bsm_Intel_Write(     UINT32 Offset, UINT16* Buffer);
BOOL   bsm_Intel_ID(void);
BOOL   bsm_Intel_Poll_For_Status(TICK_TIME Time, bsc_INTEL_CMD_Type cmdType);
BOOL   bsm_Intel_UnlockBlock(UINT32 Offset);
UINT32 bsm_Intel_Get_Block_Address(UINT32 Offset);


#endif

