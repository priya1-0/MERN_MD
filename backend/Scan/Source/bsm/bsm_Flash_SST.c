/************************************************************************
*
* MODULE: bsm_Flash_SST.c
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
* DESCRIPTION: This is the Flash driver specific to a SST flash device.
*              It handles direct interface to and from the SST device.
*              Its functionality should only be called by the Flash
*              wrapper functions not specifc to SST.
*
*************************************************************************/
#include "bsm_Flash_SST.h"
#include "com_eepromapp.h"


/******************************************************************

FUNCTION: bsm_SST_Read

DESCRIPTION:  This function Reads a WORD from the Flash.

ARGS:
        UINT32  Offset: Offset into the Flash to read
        UINT16* Buffer: the memory buffer to place the BYTEs

RETURNS:
    <none>

******************************************************************/
void bsm_SST_Read(UINT32 Offset, UINT16* Buffer)
{
    *Buffer= *(volatile UINT16*)((UINT32)bsc_FLASHBASEADDR + (UINT32)Offset);
}

/******************************************************************

FUNCTION: bsm_SST_Erase_CHIP

DESCRIPTION:  This function erases the entire Flash.

ARGS:
    <none>
RETURNS:
    BOOL: TRUE if Erase succeeded,
          FALSE if failure was detected.

******************************************************************/
BOOL bsm_SST_Erase_CHIP(void){
#ifndef TEST_NO_COMMANDS
    gen_common();   //Issue common commands
    erase_common(); //issue common erase commands
    *(volatile UINT16*)((UINT32)bsc_FLASHBASEADDR + (UINT32)SST_CMD_ERASE_CHIP_ADDR) = SST_CMD_ERASE_CHIP_DATA;

    //wait Tsce 100ms
    GLB_LTMR_WAIT(SST_ERASE_CHIP_TSCE);
#else
        #warn "No flash commands being issued to SST Flash (Simulation mode)"
#endif
    return TRUE; //assume it works, no polling/status is given

}



/******************************************************************

FUNCTION: bsm_SST_Erase_BLCK

DESCRIPTION:  This function erases selected block of Flash. Block
              is selected by the address sent as Offset argument,
              the block that this address is in will be erased.

ARGS:
        UINT32 Offset: Offset into the Flash to erase, Defines block
RETURNS:
    BOOL: TRUE if Erase succeeded,
          FALSE if failure was detected.

******************************************************************/
BOOL bsm_SST_Erase_BLCK(UINT32 Offset){
#ifndef TEST_NO_COMMANDS
    gen_common();   //Issue common commands
    erase_common(); //issue common erase commands
    *(volatile UINT16*)((UINT32)bsc_FLASHBASEADDR + (UINT32)Offset) = SST_CMD_ERASE_BLCK_DATA;

    //wait Tbe 25ms
    GLB_LTMR_WAIT(SST_ERASE_BLCK_TBE);
#else
        #warn "No flash commands being issued to SST Flash (Simulation mode)"
#endif
    return TRUE; //assume it works, no polling/status is given
}



/******************************************************************

FUNCTION: bsm_SST_Erase_SECT

DESCRIPTION:  This function erases selected sector of Flash. Sector
              is selected by the address sent as Offset argument,
              the sector that this address is in will be erased.

ARGS:
        UINT32 Offset: Offset into the Flash to erase, Defines Sector.
RETURNS:
    BOOL: TRUE if Erase succeeded,
          FALSE if failure was detected.

******************************************************************/
BOOL bsm_SST_Erase_SECT(UINT32 Offset){
#ifndef TEST_NO_COMMANDS
    gen_common();   //Issue common commands
    erase_common(); //issue common erase commands
    *(volatile UINT16*)((UINT32)bsc_FLASHBASEADDR + (UINT32)Offset) = SST_CMD_ERASE_SECT_DATA;
    //wait Tse 25ms
    GLB_LTMR_WAIT(SST_ERASE_SECT_TSE);
#else
        #warn "No flash commands being issued to SST Flash (Simulation mode)"
#endif
    return TRUE; //assume it works, no polling/status is given
}



/******************************************************************

FUNCTION: bsm_SST_Write

DESCRIPTION:  This function writes a WORD to Flash. The
              Flash must be erased before trying to write a WORD.
              This operation relies on polling to determine when
              the operation completes, as such there is an intrinsic
              need to 'timeout' so as not to deadlock.
NOTE: Although it writes a number of bytes, all writes are
      performed as word operations so all writes should be word
      aligned.

ARGS:
        UINT32  Offset: Offset into the Flash to write
        UINT16* Buffer: the WORD to write

RETURNS:
    BOOL: TRUE if Write succeeded,
          FALSE if failure was detected.

******************************************************************/
BOOL bsm_SST_Write(UINT32 Offset, UINT16* Buffer){
    UINT16       status;
    BOOL         didTimeout;
    GLB_HTMR_OBJ base;

    gen_common(); //Issue common commands
    *(volatile UINT16*)( (UINT32)bsc_FLASHBASEADDR + (UINT32)SST_CMD_WRITE_ADDR) = SST_CMD_WRITE_DATA; //Issue write command
    *(volatile UINT16*)( (UINT32)bsc_FLASHBASEADDR + (UINT32)Offset )            = *Buffer; //Issue actual write

    GLB_GET_HTMR(base);         //get the base time for this write

    // wait for the write to complete
    didTimeout = FALSE;
    do {
        status     = *(volatile UINT16*)( (UINT32)bsc_FLASHBASEADDR + (UINT32)Offset );
        didTimeout = GLB_HAS_HTMR_EXPIRED(base, ((UINT32)SST_WRITE_TBP));
    } while( ((status & SST_POLLING) != (*Buffer & SST_POLLING)) &&
             (!didTimeout));

    return TRUE; //write succeeded
}



/******************************************************************

FUNCTION: bsm_SST_ID

DESCRIPTION:  This function communicates with flash device to ID
              device. It checks to see if the connected Flash Device
              is SST.

ARGS:
        <none>

RETURNS:
    BOOL: TRUE  - SST flash was found
          FALSE - SST flash NOT found

******************************************************************/
BOOL bsm_SST_ID(void){
    volatile UINT16 ID;
    BOOL            Status;

    Status                                                                         = FALSE;
    gen_common(); //issue general common commands
    *(volatile UINT16*)((UINT32)bsc_FLASHBASEADDR + (UINT32)SST_CMD_ID_ENTRY_ADDR) = (UINT16)SST_CMD_ID_ENTRY_DATA;

    //wait Tida = 150ns.
    GLB_HTMR_WAIT((UINT32)SST_ID_ENTRY_TIDA);
    ID = *(volatile UINT16*)((UINT32)bsc_FLASHBASEADDR + (UINT32)SST_Manufact_ID_LOC); /* The immediate write after entering
                                                                                ID mode doesn not consistently return
                                                                                the ID data, second read does.*/
    ID = *(volatile UINT16*)((UINT32)bsc_FLASHBASEADDR + (UINT32)SST_Manufact_ID_LOC);

    //SST_Manufact_ID     (0x00BF)
    if( ID == (UINT16)SST_Manufact_ID) {

        ID = *(volatile UINT16*)((UINT32)bsc_FLASHBASEADDR + (UINT32)SST_Device_ID_LOC);

        // SST_39VF160A        (0x2782)
        // SST_39VF320A        (0x2783)
        // SST_39VF1601        (0x234b)
        // SST_39VF3201        (0x235b)
        // SST_39VF6401        (0x236b)
        if((ID == (UINT16)SST_39VF160A) ||
           (ID == (UINT16)SST_39VF320A) ||
           (ID == (UINT16)SST_39VF1601) ||
           (ID == (UINT16)SST_39VF3201) ||
           (ID == (UINT16)SST_39VF6401) ) {
            Status = TRUE;
        }
    }

    //Return to normal operation
    gen_common();
    *(volatile UINT16*)((UINT32)bsc_FLASHBASEADDR + (UINT32)SST_CMD_ID_ENTRY_ADDR) = SST_CMD_ID_EXIT_DATA;

    //wait Tida = 150ns.
    GLB_HTMR_WAIT(SST_ID_ENTRY_TIDA);

    return Status;
}



/******************************************************************

FUNCTION: gen_common

DESCRIPTION:  This issues the two common commands to do any command
              to a SST Flash.

ARGS:
RETURNS:
    <none>

******************************************************************/
inline void gen_common(void)
{
    *(volatile UINT16*)((UINT32)bsc_FLASHBASEADDR + (UINT32)SST_CMD_ADDR_1) = SST_CMD_DATA_1; //Issue first  command (general)
    *(volatile UINT16*)((UINT32)bsc_FLASHBASEADDR + (UINT32)SST_CMD_ADDR_2) = SST_CMD_DATA_2; //Issue second command (general)
}



/******************************************************************

FUNCTION: erase_common

DESCRIPTION:  This issues the three common commands to do a erase
              command to a SST Flash.

ARGS:
RETURNS:
    <none>

******************************************************************/
inline void erase_common(void)
{
    *(volatile UINT16*)((UINT32)bsc_FLASHBASEADDR + (UINT32)SST_CMD_ERASE_ADDR_1) = SST_CMD_ERASE_DATA_1; //Issue first  common (erase)
    *(volatile UINT16*)((UINT32)bsc_FLASHBASEADDR + (UINT32)SST_CMD_ERASE_ADDR_2) = SST_CMD_ERASE_DATA_2; //Issue second common (erase)
    *(volatile UINT16*)((UINT32)bsc_FLASHBASEADDR + (UINT32)SST_CMD_ERASE_ADDR_3) = SST_CMD_ERASE_DATA_3; //Issue third  common (erase)
}
