/************************************************************************
*
* MODULE: bsm_NVStorage.c
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
* bsm_EEWriteBuf()
* bsm_EEReadBuf()
* bsm_EEFlush()
*
* --Private--
* bsm_EEInit()
* bsm_EEnumByteTOnumWord()
* bsm_Reset_Flash_Mirror()
*
* DESCRIPTION: Non-Volatile storage, this gives a means read/write
*              and clear non-volatile memory.
*************************************************************************/
#define DEFINED_HERE
#include "bsm_NVStorage.h"
#undef DEFINED_HERE

//#include "..\aim\fsm_file.h"
#include "bsm_Event.h"
#include "bsm_Flash.h"
#include "bsm_Flash_Intel.h"
#include "bsm_Flash_SST.h"
#include "bsm_AppCrc.h"
#include "bsm_SerialPort.h"
#include "csl_std.h" //for interrupt disable/enable



/************************************************************/
/* Global Variables                                         */
/************************************************************/
UINT32 OnTimeAtPowerUp;

/************************************************************/
/* Function Defintions                                      */
/************************************************************/

/*******************************************************************************************

FUNCTION:bsm_EEWriteBuf

DESCRIPTION:Writes Length bytes from "buffer" into non-volatile
             memory starting at offset Addr.

ARGS:
        unsigned char* buffer: Specifies where to pull the information passed in
    unsigned int   Length: Specifies number of bytes to be written
    unsigned int   Addr:   Specifies starting address of Flash to write to

RETURNS:
     BOOL: TRUE if address and length are OK and data is written,
           FALSE otherwise (and no data is written).
*******************************************************************************************/
BOOL bsm_EEWriteBuf(unsigned char* buffer, unsigned int Length, unsigned int Addr)
{
    int i; //loop var

    //Check length and address for validity
    if(Addr   >= bsc_NVStorage_SIZE*2     || //Address is out of range of Flash, *2 for word to byte
       Length >  bsc_NVStorage_SIZE*2+1 - Addr) { //Length extends beyond Flash Space, *2 for word to byte
        return FALSE;
    }

    //Check for application scratch pad rollover
    if(
#if coc_AppScratchPad_ADDR != 0
        Addr >=  coc_AppScratchPad_ADDR                          && //these are in bytes already
#endif
        Addr <   coc_AppScratchPad_ADDR + coc_AppScratchPad_SIZE && //these are in bytes already
        Length > coc_AppScratchPad_ADDR - Addr + coc_AppScratchPad_SIZE) {
        return FALSE; //Address is within Application scratch pad but length rolls
        //out of scratch pad area
    }

    //Do Write from flashMirror
    DISABLE_INTERRUPTS;
    for( i = 0; i < Length; i++ ) {
        *(&bsv_FLRAM[Addr++]) = buffer[i] & 0x00FF; //Issue actual write (bytes)
    }
    ENABLE_INTERRUPTS;

    return TRUE; //All writes succeeded
}

/*******************************************************************************************
FUNCTION:bsm_EEReadBuf

DESCRIPTION:Reads Length bytes from non-volatile memory starting at offset
            Addr, placing the data into "buffer".

ARGS:
        unsigned char* buffer: Specifies where to put the information read
    unsigned int   Length: Specifies number of bytes to be read
    unsigned int   Addr:   Specifies starting address of Flash to read from

RETURNS:
     BOOL: TRUE if address and length are OK and data is read,
           FALSE otherwise (and no data is read).
*******************************************************************************************/
BOOL bsm_EEReadBuf(unsigned char* buffer, unsigned int Length, unsigned int Addr)
{
    int i; //loop var

    /*Check length and address for validity*/
    if( Addr   >= bsc_NVStorage_SIZE*2     || //Address is out of range of Flash, *2 for word to byte
        Length >  bsc_NVStorage_SIZE*2+1 - Addr) { //Length extends beyond Flash Space, *2 for word to byte
        return FALSE;
    }


    //Check for application scratch pad rollover
    if(
#if coc_AppScratchPad_ADDR != 0
        Addr >=coc_AppScratchPad_ADDR                          && //these are in bytes already
#endif
        Addr < coc_AppScratchPad_ADDR + coc_AppScratchPad_SIZE && //these are in bytes already
        Length > coc_AppScratchPad_ADDR - Addr + coc_AppScratchPad_SIZE) {
        return FALSE; //Address is within Application scratch pad but length rolls
        //out of scratch pad area
    }

    //Do read from flashMirror
    for( i = 0; i < Length; i++ ) {
        buffer[i] = bsv_FLRAM[Addr++]; //Issue actual read
    }
    return TRUE;
}


/*******************************************************************************************
FUNCTION:bsm_EEFlush

DESCRIPTION:Flush the RAM copy out to non-volatile memory.

Note:  - Do not disable interrupts before calling this function, this function requires
         interrupts (the timer for timing flash writes).
       - No calls that modify flash contents should be called while this function is running


ARGS:
        <none>

RETURNS:
    <none>
*******************************************************************************************/
BOOL bsm_EEFlush(void)
{
    BYTE   temp[2]; //Byte array to write to FlashMirror
    UINT16 crc;    //holds crc
    UINT16 i;      //loop variable
    BOOL   status;

    //Prep the Event Handler for flush (saves pointer to RAM copy for flush to flash)
    bsm_EHFlushPrep();

    //obtain the crc
    crc = aim_CRC(bsv_FLRAM, (UINT32)coc_CRC_ADDR); //CRC_ADDR is in bytes, convert to words
    //Note: CRC_ADDR must be word aligned for crc to succeed

    //Fill temp byte array and Write CRC to FlashMirror
    temp[0] = (BYTE)( (crc & 0xFF00) >> 8 ); //Low Byte
    temp[1] = (BYTE)( (crc & 0x00FF)      ); //High byte
    bsm_EEWriteBuf((UINT8*)temp, coc_CRC_SIZE, coc_CRC_ADDR);

    /*Flush Primary NVStorage Space*/
    for(i=0; i<bsc_NVSTORAGE_MAX_FLUSH; i++) {
        //Erase flash blocks, write NVStorage to Flash, and , and validite
        //check the NVStorage block from Flash
        status = bsm_EEFlushAndCheck((UINT32)bsc_NV_PRIMARY_BLOCK_ADDR);

        //Check if erasures, writes, and validity check succeeded
        if(status == TRUE) {
            //If erasures, writes, and validity check succeeded, break out of loop
            break;
        }
    } //For

    /*Check if Flush of Primary NVStorage Space failed*/
    if(status == FALSE) {
        //Primary block didn't get flushed properly, log event
        bsm_EHLog("Primary NVStorage failed to flush", bsc_EHPRIMARYFAILED_CODE);
        //Prep the Event Handler for flush (saves pointer to RAM copy for flush to flash)
        bsm_EHFlushPrep();

        //obtain the crc
        crc = aim_CRC(bsv_FLRAM, (UINT32)coc_CRC_ADDR); //CRC_ADDR is in bytes, convert to words
        //Note: CRC_ADDR must be word aligned for crc to succeed

        //Fill temp byte array and Write CRC to FlashMirror
        temp[0] = (BYTE)( (crc & 0xFF00) >> 8 ); //Low Byte
        temp[1] = (BYTE)( (crc & 0x00FF)      ); //High byte
        bsm_EEWriteBuf((UINT8*)temp, coc_CRC_SIZE, coc_CRC_ADDR);
    }

    /*Flush Backup NVStorage Space*/
    for(i=0; i<bsc_NVSTORAGE_MAX_FLUSH; i++) {
        //Erase flash blocks, write NVStorage to Flash, and , and validity
        //check the NVStorage block from Flash
        status = bsm_EEFlushAndCheck((UINT32)bsc_NV_BACKUP_BLOCK_ADDR);

        //Check if erasures, writes, and validity check succeeded
        if(status == TRUE) {
            //If erasures, writes, and validity check succeeded, break out of loop
            break;
        }
    } //For

    //Return status of if flush operation was successful
    return status;
}

/*******************************************************************************************
FUNCTION:bsm_EEInit

DESCRIPTION:Loads FLASH into RAM. This is intended to be called during
            system bringup/initialization.

ARGS:
        <none>

RETURNS:
    BOOL
*******************************************************************************************/
BOOL bsm_EEInit(void)
{
    UINT16 calcedCRC;
    BYTE   storedCRC[coc_CRC_SIZE];
    BOOL   status = TRUE;
    UINT32 offset;
    UINT16 block;
    UINT16 temp[coc_HWMetric_SIZE];

    /*Initialize the Flash Device*/
    if( bsm_Flash_Init() != TRUE) { //Init the Flash device
        return FALSE; //Flash failed to initialize,
    }

    /*If type is Intel, we must unlock the NVStorage and Event Log blocks*/
    if(bsm_Flash_Get_Type() == bsc_INTEL) {
        //Type is Intel, Unlock NVStorage and event log blocks(sectors)
        offset = bsc_EVENTLOG_BLOCK_ADDR; //initial address
        for ( block=0; block < INTEL_SECT_NUMBLOCKS; block++ ) {
            if(bsm_Intel_UnlockBlock(offset) == FALSE) {
                return FALSE;
            }
            offset += INTEL_SECT_NUMWORDS;
        }
    }


    /*Issue read from Flash to flashMirror*/
    bsm_Flash_Read_With_Unpacked(bsc_NV_PRIMARY_BLOCK_ADDR*2, bsv_FLRAM, (UINT32)bsc_NVStorage_SIZE*2);
    /* clear out the upper 8-bit of the byte array (byte array really a word array)*/
    for(offset=0; offset<(UINT32)bsc_NVStorage_SIZE*2; offset++)    //*2 for word to byte conversion
    {
        bsv_FLRAM[offset] &= 0x00FF;
    }

    /*Calculate CRC*/
    calcedCRC = aim_CRC(bsv_FLRAM, (UINT32)coc_CRC_ADDR); //CRC_ADDR is in bytes, convert to words
    //Note: CRC_ADDR must be word aligned for crc to succeed


    /*Read CRC from FlashMirror*/
    bsm_EEReadBuf((UINT8*)storedCRC, coc_CRC_SIZE, coc_CRC_ADDR);

    /*Check if CRCs match*/
    if((storedCRC[0] & 0x00FF) != ((calcedCRC >> 8) & 0x00FF )||
       (storedCRC[1] & 0x00FF) != ( calcedCRC       & 0x00FF )) {
        //CRCs did not match, try backup NVStorage block
        bsm_SDPrint("Primary NVStorage Init failed CRC");

        /*Issue read from Flash to flashMirror*/
        bsm_Flash_Read_With_Unpacked(bsc_NV_BACKUP_BLOCK_ADDR*2, bsv_FLRAM, (UINT32)bsc_NVStorage_SIZE*2);

        /*Calculate CRC*/
        calcedCRC = aim_CRC(bsv_FLRAM, (UINT32)coc_CRC_ADDR); //CRC_ADDR is in bytes, convert to words
        //Note: CRC_ADDR must be word aligned for crc to succeed

        /*Read CRC from FlashMirror*/
        bsm_EEReadBuf((UINT8*)storedCRC, coc_CRC_SIZE, coc_CRC_ADDR);
        if((storedCRC[0] & 0x00FF) != ((calcedCRC >> 8) & 0x00FF) ||
           (storedCRC[1] & 0x00FF) != (calcedCRC       & 0x00FF)) {
            /*Init the Event Handler (sets pointers)*/
            /*Then we can log messages */
            bsm_EHInit();

            /* At this point both block have failed crc, check if block is all FF's*/
            status = bsm_EECheckForBlank();
            if(status == TRUE) {
                /*Log crc failure of Primary CRC block.*/
                bsm_EHLog("Primary and Backup NVStorage Block CRC failed - test passed but unit is unprogrammed", bsc_EHPRIMARYANDBACKUPFAILED_CODE);
            }
            else
            {
                /* NVStorage in flash has lost integrity, data read is not valid*/
                bsm_EHLog("Primary and Backup NVStorage Block CRC failed - data integrity is lost", bsc_EHPRIMARYANDBACKUPFAILED_CODE);
            }
            
            // set the returned status to FALSE to indicate a failure.
            status = FALSE;
        }else{
            /* CRC match, proceed*/
            status = TRUE;
            /*Init the Event Handler (sets pointers)*/
            bsm_EHInit();
            /*Log crc failure of Primary CRC block.*/
            bsm_EHLog("Primary NVStorage Block CRC failed, Backup block OK", bsc_EHPRIMARYFAILEDBACKUPOK_CODE);
        }
    }else{
        /* CRC match, proceed*/
        status = TRUE;
        /*Init the Event Handler (sets pointers)*/
        bsm_EHInit();
    }

    bsm_EEReadBuf((BYTE*)temp, coc_HWMetric_SIZE, coc_HWMetric_ADDR);  // Read it.
    OnTimeAtPowerUp = ((UINT32)(temp[0] & 0x00FF) << 24) |
                      ((UINT32)(temp[1] & 0x00FF) << 16) |
                      ((UINT32)(temp[2] & 0x00FF) <<  8) |
                      ((UINT32)(temp[3] & 0x00FF) <<  0);

    if(OnTimeAtPowerUp == 0xFFFFFFFF)           // If it is the unprogrammed,
    {
        OnTimeAtPowerUp = 0;                // reset it to zero.
    }

    return status;
}


/*******************************************************************************************
FUNCTION:bsm_EEFlushAndCheck

DESCRIPTION:NVStorage block is flushed to the offset of Flash that is passed. Approriate
                Blocks are erased and written. Flash is read to check the validity of written
                data.

ARGS:
        UINT32 offset: Offset of Flash to begining of block(s) for NStorage to be written in
                       Flash. This value shall be in words.
                       Intended to be passed: <bsc_NV_PRIMARY_BLOCK_ADDR> -or-
                                              <bsc_NV_BACKUP_BLOCK_ADDR>

RETURNS:
    BOOL: TRUE - Flush succeeded,
          FALSE- Flush failed
*******************************************************************************************/
BOOL bsm_EEFlushAndCheck(UINT32 offset){
    UINT32 currOffset;
    int    i; //loop var
    BOOL   status;
    BYTE   temp[2]; //Byte array to write to FlashMirror

    currOffset = offset; //set current offset to original passed offset
    switch(bsm_Flash_Get_Type()) {
    case bsc_SST:
        //Erase the blocks
        for(i = 0; i < (UINT32)bsc_SST_NVSECT_COUNT; i++) {
            status      = bsm_Flash_Erase_SECT(currOffset); //Erase a SST Sector
            currOffset += SST_SECT_NUMWORDS; //Prepare next offset
        }
        break;
    case bsc_INTEL:
        //Erase the blocks
        for(i = 0; i < (UINT32)bsc_INTEL_NVSECT_COUNT; i++) {
            status      = bsm_Flash_Erase_BLCK(currOffset); //Erase a INTEL Sector(For intel its actually a block but a smaller block size)
            currOffset += INTEL_SECT_NUMWORDS; //Prepare next offset
        }
        break;
    }

    currOffset = offset; //set current offset back to original passed offset
    //check if erasure succeeded
    if(status == TRUE) {
        //erase success, Write data out to flash
        status = bsm_Flash_Write_With_Unpacked(offset, bsv_FLRAM, (UINT32)bsc_NVStorage_SIZE);
    }

    //check if write succeeded
    if(status == TRUE) {
        //Write success, Read data out to flash
        currOffset = (UINT32)offset << 1; //mult by 2 to convert to bytes
        for(i=0; i < bsc_NVStorage_SIZE*2; i++) { //*2 conversion from words to bytes
            bsm_Flash_Read_With_Unpacked(currOffset + i, &temp[0], (UINT32)1);
            if(temp[0] != (bsv_FLRAM[i] & 0x00FF))
            {
                status = FALSE;
                break;
            }
            status = TRUE;
        }
    }

    return status;
}


/*******************************************************************************************
FUNCTION: bsm_EECheckForBlank

DESCRIPTION: Check the flashMirror to see if it is blank, i.e. all bytes are bsm_BLANK_FLASH

ARGS:
        <none>

RETURNS:
    BOOL: TRUE - flashmirror is blank (all bytes are bsm_BLANK_FLASH
          FALSE- flashMirror is not blank
*******************************************************************************************/
BOOL bsm_EECheckForBlank(void){
    int    i;  //loop var
    UINT16 blank;
    BOOL   status;

    /* Determin the flash's blank state*/
    switch(bsm_Flash_Get_Type()) {
    case bsc_SST:
        blank = bsm_SST_BLANK_FLASH;
        break;
    case bsc_INTEL:
        blank = bsm_INTEL_BLANK_FLASH;
        break;
    }

    /* Since we're comparing bytes*/
    blank &= 0x00FF;

    status = TRUE;
    for(i=0; i < bsc_NVStorage_SIZE*2; i++) { //*2 conversion from words to bytes
        if( blank != (bsv_FLRAM[i] & 0x00FF)) {
            status = FALSE;
            break;
        }
    }
    return status;
}


/******************************************************************

FUNCTION: bsm_Reset_Flash_Mirror

DESCRIPTION:  This function clears the flash mirror of flash.

ARGS:
        <none>

RETURNS:
    <none>
******************************************************************/
void bsm_Reset_Flash_Mirror(void){
    UINT32 i; //loop var

    for(i = 0; i< bsc_NVStorage_SIZE*2; i++) {
        *(UINT16*)((UINT32)&bsv_FLRAM+i) = 0x00FF;
    }
}

/******************************************************************

FUNCTION: bsm_ReadTotalOnTimeMinutes

DESCRIPTION:  This function calculates the total minutes the unit
              has been on in its lifetime.

ARGS:
        <none>

RETURNS:
    UINT32: Total On-Time minutes
******************************************************************/
UINT32 bsm_ReadTotalOnTimeMinutes(void)
{
    UINT32 TotalOnTime;

    TotalOnTime =  OnTimeAtPowerUp + (NU_Retrieve_Clock() / (60*TICKS_PER_SECOND)); // Increment the number of on minutes.

    return TotalOnTime;
}

/******************************************************************

FUNCTION: bsm_WriteTotalOnTimeMinutes

DESCRIPTION:  This function writes the life-time minutes to the
              non-volatile storage.

ARGS:
        <none>

RETURNS:
    <none>
******************************************************************/
void bsm_WriteTotalOnTimeMinutes(void)
{
    UINT16 temp[coc_HWMetric_SIZE];
    UINT32 TotalOnTime;

    TotalOnTime = bsm_ReadTotalOnTimeMinutes();

    temp[0]     = (TotalOnTime >> 24) & 0x00FF;
    temp[1]     = (TotalOnTime >> 16) & 0x00FF;
    temp[2]     = (TotalOnTime >>  8) & 0x00FF;
    temp[3]     = (TotalOnTime >>  0) & 0x00FF;

    bsm_EEWriteBuf((BYTE*)temp, coc_HWMetric_SIZE, coc_HWMetric_ADDR); // Write it.
}
