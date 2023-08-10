/************************************************************************
*
* MODULE: bsm_SUSoftwareUpdate.c
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
* bsm_SUDoUpdate()
*
* --Private--
* min()
*
* DESCRIPTION: Handles writing a software update to the flash. It keeps
*              track of what blocks to erase and write for the software update.
*
*************************************************************************/
#include "bsm_SUSoftwareUpdate.h"
#include "bsm_Event.h"
#include "bsm_Flash.h"
#include "bsm_Flash_Intel.h"
#include "bsm_Flash_SST.h"
#include "bsm_power.h"
#include "bsm_General.h"
#include "..\com_eepromapp.h"

//Not needed, using an intrinsic function '_min'
#define min(x,y) (((x) < (y)) ? (x) : (y))

/************************************************************/
/* Global Variables                                         */
/************************************************************/
#ifndef SKIP_CRC
extern UINT16 StoredCrcL;
extern UINT16 StoredCrcH;
#endif

/************************************************************/
/* Function Defintions                                      */
/************************************************************/

/*******************************************************************************************
FUNCTION:bsm_SUDoUpdate

DESCRIPTION:This function is passed software update data that has been validated as
            uncorrupted data. It then writes the software update to flash and then reads it
            back to confirm that the data was written correctly. Note that this expects
            a packed buffer (2 bytes packed per word)

ARGS:
    UINT16* data: base pointer to buffer containing update data
    UINT32 offset: byte offset into the data pointer for the buffer
    UINT32 length: length of update buffer in BYTES

RETURNS:
    BOOL: TRUE if success,
          FALSE if failure.
*******************************************************************************************/
BOOL bsm_SUDoUpdate(UINT16* basePtr, UINT32 byteOffset, UINT32 byteLength)
{
    UINT16 i;   //1st(outer)  loop var
    UINT16 j;  //2nd(middle) loop var
    UINT32 k; //3rd(inner)  loop var
    UINT16 srcTemp;
    UINT16 destTemp;

    UINT32 wordOffset;
    UINT16 numBlocksMAX;
    UINT16 numBlocks;
    UINT32 numBytesPerBlock;
    UINT32 numBytes;
    UINT32 longTemp;

    BOOL status;

    /*Determine the number of blocks and number of words per block for the flash type*/
    wordOffset = 0;
    switch(bsm_Flash_Get_Type()) {
    case bsc_SST:
        numBlocksMAX     = bsc_SST_CODE_BLCK_COUNT;
        numBytesPerBlock = 2 * SST_BLCK_NUMWORDS;
        break;
    case bsc_INTEL:
        numBlocksMAX     = bsc_INTEL_CODE_BLCK_COUNT;
        numBytesPerBlock = 2 * INTEL_BLCK_NUMWORDS;

        /* If flashType is Intel, Unlock all Code blocks*/
        for ( i=0; i<INTEL_BLCK_NUMBLOCKS; i++ ) {
            if(bsm_Intel_UnlockBlock(wordOffset) == FALSE) {
                return FALSE;
            }
            wordOffset += INTEL_BLCK_NUMWORDS;
        }
        break;
    case bsc_Unknown:
    //break intentionally left off
    default:
        bsm_EHLog("SUDoUpdate failed: unknown flash type", bsc_EHSUFAILEDUNKNOWFLASHTYPE_CODE);
        return false;
    }

    /*Determine the actual number of blocks to write based on code size*/
    numBlocks = ( byteLength / numBytesPerBlock); // byte to word conversion
    if( (byteLength % numBytesPerBlock) > 0) {
        numBlocks++;
    }
    if(numBlocks > numBlocksMAX) {
        bsm_EHLog("SUDoUpdate failed: Code passed to SUDoUpdate was too large", bsc_EHSUFAILEDCODETOOLARGE_CODE );
        return false;
    }

    /* Check the battery */
    if( !bsm_IsBatteryGood() )
    {
        bsm_EHLog("SUDoUpdate failed: Insufficient battery power", bsc_EHSUFAILEDBATTERYLOW_CODE );
        return false;
    }

    /* Disable power button before writing to flash */
    bsm_PMDisableButton();

        #ifndef SKIP_CRC
    /* Clear the CRC that is stored in the flash */
    srcTemp   = 0;
    longTemp  = ((UINT32)&StoredCrcH);             //get address of 1st part of CRC
    longTemp -= bsc_FLASHBASEADDR;                 //calculate offset into flash for this CRC
    bsm_Flash_Write_With_Packed( longTemp, &srcTemp, sizeof(StoredCrcH));

    srcTemp   = 0;
    longTemp  = ((UINT32)&StoredCrcL);             //get address of 1st part of CRC
    longTemp -= bsc_FLASHBASEADDR;                 //calculate offset into flash for this CRC
    bsm_Flash_Write_With_Packed( longTemp, &srcTemp, sizeof(StoredCrcL));

    /* Check that CRC was cleared */
    if(StoredCrcL != 0x0000 || StoredCrcH != 0x0000)
    {
        bsm_EHLog("SUDoUpdate failed: Failed to clear CRC", bsc_EHSUFAILEDBATTERYLOW_CODE );
        return false;
    }
        #else
                #warn "CRC clearing during software update is disabled."
        #endif


    /*Write data to the flash and verify*/
    wordOffset = bsc_CODE_BLOCK_ADDR; //Initial offset
    status     = TRUE;
    for(i = 0; i < numBlocks; i++) { //go through each block
        /*Check if previous blocks failed*/
        if(status == FALSE) {
            //previous block failed maximum times, do not continue more blocks
            break;
        }

        /*Previous blocks succeeded, try to write and verify this block*/
        for(j = 0; j<bsc_CODE_MAX_FLUSH; j++) {

            /*erase  current Block*/
            status   = bsm_Flash_Erase_BLCK(wordOffset); //Erase current block

            /*Determine the number of bytes to be written to current Block*/
            numBytes = min( byteLength, numBytesPerBlock );
            //Note: min is an intrinsic function

            /*write  current Block*/
            if(status == TRUE) {
                status = bsm_Flash_Write_With_Unaligned_Packed(wordOffset, basePtr, byteOffset, numBytes);
            }

            /*verify current Block*/
            if(status == TRUE) {
                for(k=0; k < numBytes; k+=2) {
                    status  = bsm_Flash_Read_With_Packed(wordOffset + k/2, &destTemp, 1); //read one word from flash

                    /* Get desired word */
                    srcTemp = bsm_getByteFromPackedArray(basePtr, byteOffset + k) << 8;

                    // if this is the last word of an odd number of bytes...
                    if(k == (numBytes-1) && numBytes%2 == 1)
                    {
                        srcTemp |= 0x00FF;
                    }
                    else
                    {
                        srcTemp = srcTemp | bsm_getByteFromPackedArray(basePtr, byteOffset + k+1) & 0x00FF;
                    }

                    if(status == FALSE || srcTemp != destTemp)
                    {
                        bsm_EHLog("SWDoUpdate block verification failed", bsc_EHSUFAILEDVERIFICATION_CODE);
                        status = FALSE;
                        break;
                    }
                    //Word was verified, move onto next word.
                } //for(k)
            }

            /*if block verified, goto next block else retry*/
            if(status == TRUE) {
                wordOffset += numBytesPerBlock/2;   //set offset to next block
                byteOffset += numBytesPerBlock; //set offset to next block
                byteLength -= numBytes; // adjust the number of bytes left
                break; //finished with this block, go on to next.
            }
        } //for(j)
    } //for(i)

    /* Enable power button after writing to flash */
    bsm_PMEnableButton();

    return status;
}





