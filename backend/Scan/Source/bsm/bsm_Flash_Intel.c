/************************************************************************
*
* MODULE: bsm_Flash_Intel.c
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
* DESCRIPTION:This is the Flash driver specific to a Intel flash device.
*             It handles direct interface to and from the Intel device.
*             Its functionality should only be called by the Flash
*             wrapper functions not specifc to Intel.
*
*************************************************************************/
#include "bsm_Flash_Intel.h"
#include "com_eepromapp.h"

/******************************************************************

FUNCTION: bsm_Intel_Read

DESCRIPTION:  This function Reads a WORD from the Flash.

ARGS:
        UINT32  Offset: Offset into the Flash to read
        UINT16* Buffer: the memory WORD to place the read WORD

RETURNS:
    <none>

******************************************************************/
void bsm_Intel_Read(UINT32 Offset, UINT16* Buffer)
{
    *Buffer = *(volatile UINT16*)((UINT32)bsc_FLASHBASEADDR + Offset);
}

/******************************************************************

FUNCTION: bsm_Intel_Erase_BLCK

DESCRIPTION:  This function erases selected block of Flash. Block
              is selected by the address sent as Offset argument,
              the block that this address is in will be erased.

ARGS:
        UINT32 Offset: Offset into the Flash to erase, Defines Block
RETURNS:
    BOOL: TRUE if Erase succeeded,
          FALSE if failure was detected.

******************************************************************/
BOOL bsm_Intel_Erase_BLCK(UINT32 Offset){

    *(volatile UINT16*)((UINT32)bsc_FLASHBASEADDR + Offset) = INTEL_CMD_ERASE_1; //Do first erase command
    *(volatile UINT16*)((UINT32)bsc_FLASHBASEADDR + Offset) = INTEL_CMD_ERASE_2; //Do Second erase command, offset is within block to erase

    //Poll the status register
    return bsm_Intel_Poll_For_Status(INTEL_ERASE_BLCK_TIME, bsc_INTEL_ERASE);
}

/******************************************************************

FUNCTION: bsm_Intel_Write
DESCRIPTION:  This function writes a WORD to Flash. The Flash must
              be erased before trying to write WORDs. This operation
              relies on polling to determine when the operation
              completes, as such there is an intrinsic need to '
              timeout' so as not to deadlock.

ARGS:
        UINT32  Offset: Offset into the Flash to write
        UINT16* Buffer: the WORD to write

RETURNS:
    BOOL: TRUE if Write succeeded,
          FALSE if failure was detected.

******************************************************************/
BOOL bsm_Intel_Write(UINT32 Offset, UINT16* Buffer){

    *(volatile UINT16*)((UINT32)bsc_FLASHBASEADDR + Offset) = INTEL_CMD_WRITE; //Issue first write command
    *(volatile UINT16*)((UINT32)bsc_FLASHBASEADDR + Offset) = *Buffer; //Issue actual write

    //Poll the status register
    return bsm_Intel_Poll_For_Status(INTEL_WRITE_TIME, bsc_INTEL_WRITE);
}


/******************************************************************

FUNCTION: bsm_Intel_ID

DESCRIPTION:  This function communicates with flash device to ID
              device. It checks to see if the connected Flash
              Device is Intel.

ARGS:
        <none>

RETURNS:
    BOOL: TRUE  - Intel flash was found
          FALSE - Intel flash NOT found

******************************************************************/
BOOL bsm_Intel_ID(void){
    UINT16 manufactID;
    UINT16 deviceCode;
    BOOL   status;

    status                                             = FALSE;

    /*Check manufacturer's ID */
    *(volatile UINT16*)((UINT32)bsc_FLASHBASEADDR + 0) = INTEL_CMD_READ_IDENTIFIER; //Start reading ID of device

    /* Wait for the mode to enter*/
    GLB_HTMR_WAIT(INTEL_WRITE_TIME);

    manufactID = *(volatile UINT16*)((UINT32)bsc_FLASHBASEADDR + (UINT32)INTEL_Manufact_ID_LOC); //Read Manufacturer ID
    deviceCode = *(volatile UINT16*)((UINT32)bsc_FLASHBASEADDR + (UINT32)INTEL_DEVICE_ID_LOC);    //Read device ID

    /*Determine if device type is Intel*/
    if(manufactID == INTEL_Manufact_ID ) {
        if(deviceCode == INTEL_DEVICE_8Mb_TOP  ||
           deviceCode == INTEL_DEVICE_16Mb_TOP ||
           deviceCode == INTEL_DEVICE_32Mb_TOP ||
           deviceCode == INTEL_DEVICE_64Mb_TOP )
        {
            status = TRUE;
        }
    }

    // the Flash should be in Read mode by default
    *(volatile UINT16*)((UINT32)bsc_FLASHBASEADDR) = INTEL_CMD_READ_ARRAY; //Issue the read array command for subsequent reads.

    return status;
}


/******************************************************************

FUNCTION: bsm_Intel_Poll_For_Status

DESCRIPTION:  This function polls the Intel Flash for status. It
              takes an arguement for the timeout delay, pass the
              appropriate time (Max write time, max rease time etc)
              for the command that status is waiting on. Also required
              the command type, Write or Erase.


ARGS:
        UINT16  Time:               Timeout(unit dependent on bsc_INTEL_CMD_Type.)
        bsc_INTEL_CMD_Type cmdType: The type of command that was issued.
                                                                INTEL_WRITE_TIME :: time in ns
                                                                INTEL_ERASE_TIME :: time is ms


RETURNS:
    BOOL: TRUE if no errors or timeout occured,
          FALSE otherwise

******************************************************************/
BOOL bsm_Intel_Poll_For_Status(TICK_TIME timeout, bsc_INTEL_CMD_Type cmdType){
    UINT16       Status;
    GLB_LTMR_OBJ baseL;
    GLB_HTMR_OBJ baseH;


    //Pole for initial status with a timeout, time out is specific to command (passed in),
    //units of timeout (ns vs. ms) specific to command type.
    switch( cmdType) {
    case bsc_INTEL_ERASE:
        //Timeout time given in ms
        GLB_GET_LTMR(baseL);     //get base time
        /* Get into read status mode*/
        *(volatile UINT16*)((UINT32)bsc_FLASHBASEADDR) = INTEL_CMD_READ_STATUS; //Initiate read status register
        do {
            Status = *(volatile UINT16*)((UINT32)bsc_FLASHBASEADDR);
        } while( (Status & SR7) != SR7 && GLB_HAS_LTMR_EXPIRED(baseL, timeout) == FALSE);

        break;
    case bsc_INTEL_WRITE:
        //Timeout time given in ns
        GLB_GET_HTMR(baseH); //get base time
        /* Get into read status mode*/
        *(volatile UINT16*)((UINT32)bsc_FLASHBASEADDR) = INTEL_CMD_READ_STATUS; //Initiate read status register
        do {
            Status = *(UINT16*)((UINT32)bsc_FLASHBASEADDR);
        } while( (Status & SR7) != SR7 && GLB_HAS_HTMR_EXPIRED(baseH, timeout) == FALSE);

        break;
    default:
        return FALSE;
    }


    if( (Status & SR3) != 0) {
        // Vpp Error
        *(volatile UINT16*)((UINT32)bsc_FLASHBASEADDR) = INTEL_CMD_CLEAR_STATUS; //Clear status because Flash can't clear this bit itself
        return FALSE;
    }


    switch( cmdType) {
    case bsc_INTEL_ERASE:
        if( (Status & SR4) != 0 && (Status & SR5) != 0) {
            //SR[4,5]=(1,1)
            //Command Sequence Error
            *(volatile UINT16*)((UINT32)bsc_FLASHBASEADDR) = INTEL_CMD_CLEAR_STATUS; //Clear status because Flash can't clear this bit itself
            return FALSE;
        }
        if( (Status & SR5) != 0) {
            //Block Erase Error
            *(volatile UINT16*)((UINT32)bsc_FLASHBASEADDR) = INTEL_CMD_CLEAR_STATUS; //Clear status because Flash can't clear this bit itself
            return FALSE;
        }
        break;
    case bsc_INTEL_WRITE:
        if( (Status & SR4) != 0) {
            // Program(Write) Error
            *(volatile UINT16*)((UINT32)bsc_FLASHBASEADDR) = INTEL_CMD_CLEAR_STATUS; //Clear status because Flash can't clear this bit itself
            return FALSE;
        }
        break;
    }

    if( (Status & SR1) != 0) {
        //Block Locked Error
        *(volatile UINT16*)((UINT32)bsc_FLASHBASEADDR) = INTEL_CMD_CLEAR_STATUS; //Clear status because Flash can't clear this bit itself
        return FALSE;
    }

    // the Flash should be in Read mode by default
    *(volatile UINT16*)((UINT32)bsc_FLASHBASEADDR + 0) = INTEL_CMD_READ_ARRAY; //Issue the read array command for subsequent reads.

    return TRUE; //No Error detected


}


/******************************************************************

FUNCTION: bsm_Intel_UnlockBlock

DESCRIPTION: This function unlocks the specified block on the flash
             device

ARGS:
        UINT32 Offset: Offset into the Flash to erase, Defines Block
RETURNS:
        BOOL: TRUE if success,
              FALSE otherwise
Assumptions:
    The block indicated was previously locked.

******************************************************************/
BOOL bsm_Intel_UnlockBlock(UINT32 Offset)
{
    GLB_HTMR_OBJ base;
    BOOL         status;
    UINT32       blockStart;
    UINT16       temp;

    blockStart = bsm_Intel_Get_Block_Address(Offset);

    GLB_GET_HTMR(base);     //get base time
    do {
        *(volatile UINT16*)((UINT32)bsc_FLASHBASEADDR + Offset) = INTEL_CMD_UNLOCK_1; //1st unlock command
        *(volatile UINT16*)((UINT32)bsc_FLASHBASEADDR + Offset) = INTEL_CMD_UNLOCK_2; //2nd unlock command


        /*check the protection status of the block */
        temp = *(volatile UINT16*)(blockStart + (UINT32)UNLOCK_LOCATION);
        temp = temp & UNLOCK_STATUS_MASK;
        if(temp == UNLOCK_STATUS_DESIRED)
            status = TRUE;
        else
            status = FALSE;
    }
    while((GLB_HAS_HTMR_EXPIRED(base, (UINT32)INTEL_WRITE_TIME) != TRUE) && status != TRUE);

    // the Flash should be in Read mode by default
    *(volatile UINT16*)((UINT32)bsc_FLASHBASEADDR) = INTEL_CMD_READ_ARRAY; //Issue the read array command for subsequent reads.

    return status;
}

/****************************************************************************
FUNCTION: bsm_Intel_Get_Block_Address(Offset)

DESCRIPTION: This procedure determines the starting block address of the block
             containing the passed offset

ARGS:
    UINT32 Offset: Offset into the Flash to erase, Defines Block

RETURNS:
        UINT32: Starting address of block
 ***************************************************************************/
UINT32 bsm_Intel_Get_Block_Address(UINT32 Offset){
    UINT32 temp;

    // get the block number if the block is fullsize block
    temp = Offset / INTEL_BLCK_NUMWORDS;
    if(temp >= INTEL_BLCK_NUMBLOCKS )
    {
        //. Address not within full-size block addresses
        temp = Offset - (INTEL_BLCK_NUMWORDS * INTEL_BLCK_NUMBLOCKS);
        temp = temp / INTEL_SECT_NUMWORDS;
        if(temp >= INTEL_SECT_NUMBLOCKS )
        {
            //Address out of range, return what waqs passed in
            temp = Offset;
        }
        else
        {
            // Address is within small-size block addresses
            //Determine starting address
            temp  = temp * INTEL_SECT_NUMWORDS;

            //add back in offset to the small-blocks
            temp += INTEL_BLCK_NUMWORDS * INTEL_BLCK_NUMBLOCKS;

        }
    }
    else
    {
        // Address is within full-size block addresses
        // Determine starting address
        temp = temp * INTEL_BLCK_NUMWORDS;
    }

    return temp;
}


