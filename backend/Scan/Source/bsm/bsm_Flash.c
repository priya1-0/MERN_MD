/************************************************************************
*
* MODULE: bsm_Flash.c
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
* bsm_Flash_Write_With_Unaligned_Packed()
* bsm_Flash_Erase_BLCK()
* bsm_Flash_Erase_SECT()
* bsm_Flash_Init()
* bsc_Flash_Type bsm_Flash_Get_Type()
*
* --Private--
*
* DESCRIPTION: This is the "Flash wrapper." It is used to talk directly
*              to flash. It is responsible for providing a general
*              interface not specific to SST or Intel Flash types. This
*              interface is intended to be used by asset management,
*              configuration data, error log, and software update modules.
*              These modules need to understand the memory map of both
*              types of flash to understand what a block erase will do.
*              Before using the functionality of this module, an
*              initialization must be performed to determine which type
*              of Flash is connected to device.
*
*************************************************************************/
#include "global.h"

#include "bsm_Flash.h"
#include "bsm_Flash_SST.h"
#include "bsm_Flash_Intel.h"
#include "bsm_General.h"
#include "bsm_Power.h"


//PRIVATE MODULE DATA
static bsc_Flash_Type bsv_Flash_Type;
static BOOL           flashInprogress; //If true, flash is in use.

/******************************************************************

FUNCTION: bsm_Flash_With_Read_Packed

DESCRIPTION:  This function reads a number of WORDs from Flash. The
              WORDs are returned in packed form. This function is
              used by software update.

ARGS:
        UINT32  Offset: Offset into the Flash to read
        UINT16* Buffer: the memory buffer to place the BYTEs
        UINT32  Length: length of the transfer in WORDs

RETURNS:
    BOOL: TRUE - Read succeeded (Flash had been identified correctly, in bounds)
          FALSE- Read failed (Flash had NOT been identified correctly, or out of bounds)

******************************************************************/
BOOL bsm_Flash_Read_With_Packed(UINT32 Offset, UINT16* Buffer, UINT32 Length)
{
    UINT16 index; //Word index

    //Will operation stay within flash boundary?
    if( Offset > (UINT32)bsc_EELastAddr   || //check if starting offset is valid
        Length > bsc_EELastAddr+1 - Offset) { //check if length is too long
        return FALSE;
    }

    for(index = 0; index < Length; index++) {
        switch(bsv_Flash_Type) { //Check the Flash type
        case bsc_SST: //It's SST, issue a SST Read
            bsm_SST_Read(Offset + index, &Buffer[index]);
            break;
        case bsc_INTEL: //It's Intel, issue a Intel Read
            bsm_Intel_Read(Offset + index, &Buffer[index]);
            break;
        default:
            return FALSE; //unknown type
        }
    }
    return TRUE; //read successfull
}

/******************************************************************

FUNCTION: bsm_Flash_Read_With_Unpacked

DESCRIPTION: This function reads a number of unpacked BYTEs from
             Flash. The BYTEs are returned in unpacked form, namely
             one byte per word. This function is used by
             non-volatile storage.
NOTE: The length is in BYTES and NOT WORDS.
NOTE: The ADDR is BYTE addressable NOT WORD addressable

ARGS:
        UINT32  Offset: Offset into the Flash to read
        BYTE*   Buffer: the memory buffer to place the BYTEs
        UINT32  Length: length of the transfer in WORDs

RETURNS:
    BOOL: TRUE - Read succeeded (Flash had been identified correctly, in bounds)
          FALSE- Read failed (Flash had NOT been identified correctly, or out of bounds)

******************************************************************/
BOOL bsm_Flash_Read_With_Unpacked(UINT32 Offset, BYTE* Buffer, UINT32 Length)
{
    UINT32 wordOffset;
    BOOL   highLow;   //bool for HIGH or LOW byte
    UINT16 indexB=0;  //Byte index
    UINT16 indexW=0;  //Word index
    UINT16 temp;      //Temp storage for word read from Flash

    //Find the address offset in Words
    wordOffset = Offset >> 1; //Passed offset is in Bytes

    //Will operation stay within flash boundary?
    if( wordOffset > (UINT32)bsc_EELastAddr || //check if starting offset is valid
        bsm_EEnumByteTOnumWord(Length) > bsc_EELastAddr+1 - wordOffset) { //check if length is too long
        return FALSE;
    }


    //Init which byte we start at;
    if(Offset%2 == 0) {
        highLow = LOW;
    }else{
        highLow = HIGH;
    }

    while(indexB < Length) {
        //Read a word in from Flash
        switch(bsv_Flash_Type) { //Check the Flash type
        case bsc_SST: //It's SST, issue a SST Read
            bsm_SST_Read(wordOffset + indexW++, &temp); //copy Word from Flash to temporary
            break;
        case bsc_INTEL: //It's Intel, issue a Intel Read
            bsm_Intel_Read(wordOffset + indexW++, &temp); //copy Word from Flash to temporary
            break;
        default:
            return FALSE; //unknown type either flash not init or failed init.
        }
        if(highLow == LOW) { //if we're after the high byte
            //Copy LOW byte from temp to next element in Byte Array
            Buffer[indexB++] = (temp & 0xFF00) >> 8;
            highLow          = HIGH; //Set to HIGH Byte
        }
        if(indexB < Length) {
            //highLow must be HIGH to be here and there is another Byte to read.
            //Copy HIGH byte from temp to next element in Byte Array
            Buffer[indexB++] = (temp & 0x00FF);
            highLow          = LOW; //Set to LOW byte
        }
    }
    return TRUE; //read successfull
}




/******************************************************************

FUNCTION: bsm_Flash_Erase_BLCK

DESCRIPTION:  This function erases the selected block of Flash.
              WARNING: Due to differences in block layout between
              flash types, this function should be used with caution.

ARGS:
        UINT32 Offset: the offset of the block of Flash to erase
RETURNS:
    BOOL: TRUE - Erase succeeded (Flash had been identified correctly)
          FALSE- Erase failed (Flash had NOT been identified correctly)

******************************************************************/
BOOL bsm_Flash_Erase_BLCK(UINT32 Offset){
    BOOL ret;

    //check the Flash In Progess Flag
    if(!bsm_Flash_Get_Inprogress())
    {
        //set the inprogress flag
        bsm_Flash_Set_Inprogress(TRUE);

        switch(bsv_Flash_Type) {
        case bsc_SST:
            ret = bsm_SST_Erase_BLCK(Offset);
            break;
        case bsc_INTEL:
            ret = bsm_Intel_Erase_BLCK(Offset);
            break;
        case bsc_Unknown:
        //if we get here we had failed to identify flash -- fail...
        //Break intentionally left off
        default:
            ret = FALSE;
            break;
        }

        //clear the inprogress flag
        bsm_Flash_Set_Inprogress(FALSE);
    }
    else
    {
        ret = FALSE;
    }

    return ret;
}


/******************************************************************

FUNCTION: bsm_Flash_Erase_SECT

DESCRIPTION:  This function erases the selected sector of Flash.
              WARNING: Due to differences in block layout between
              flash types, this function should be used with caution.
              Note: Intel Flash does not support Sector erasures.

ARGS:
        UINT32 Offset: the offset of the sector of Flash to erase
RETURNS:
    BOOL: TRUE - Erase succeeded (Flash had been identified correctly)
          FALSE- Erase failed (Flash had NOT been identified correctly)

******************************************************************/
BOOL bsm_Flash_Erase_SECT(UINT32 Offset){
    BOOL ret;

    //check the Flash In Progess Flag
    if(!bsm_Flash_Get_Inprogress())
    {
        //set the inprogress flag
        bsm_Flash_Set_Inprogress(TRUE);

        switch(bsv_Flash_Type) {
        case bsc_SST:
            ret = bsm_SST_Erase_SECT(Offset);
            break;
        case bsc_INTEL:    //Intel doesn't support Sectors, fail
        //Break intentionally left off
        case bsc_Unknown:
        //Break intentionally left off
        default:
            ret = FALSE;
            break;
        }

        //clear the inprogress flag
        bsm_Flash_Set_Inprogress(FALSE);
    }
    else
    {
        ret = FALSE;
    }

    return ret;
}



/******************************************************************

FUNCTION: bsm_Flash_Write_With_Packed

DESCRIPTION:  This function writes a number of WORDSs to Flash. The
              Flash must be erased before trying to write WORDSs.
              The BYTEs should be passed in packed form(as WORDs).
NOTE: The length is in WORDs.

ARGS:
        UINT32  Offset: Offset into the Flash to write
        UINT16* Buffer: the memory buffer of the BYTEs to write from
        UINT32 Length:  the number of WORDSs to write

RETURNS:
    BOOL: TRUE - Read succeeded (Flash had been identified correctly, in bounds)
          FALSE- Read failed (Flash had NOT been identified correctly, or out of bounds)

******************************************************************/
BOOL bsm_Flash_Write_With_Packed(UINT32 Offset, UINT16* Buffer, UINT32 Length){
    UINT16 index; //Word index
    BOOL   ret;

    //Will operation stay within flash boundary?
    if( Offset > (UINT32)bsc_EELastAddr   || //check if starting offset is valid
        Length > bsc_EELastAddr+1 - Offset) { //check if length is too long
        return FALSE;
    }

    //check the Flash In Progess Flag
    if(!bsm_Flash_Get_Inprogress())
    {
        //set the inprogress flag
        bsm_Flash_Set_Inprogress(TRUE);

        for(index = 0; index < Length; index++) {
            switch(bsv_Flash_Type) {   //Check the Flash type
            case bsc_SST:    //It's SST, issue a SST Read
                ret = bsm_SST_Write(Offset + index, &Buffer[index]);
                break;
            case bsc_INTEL:    //It's Intel, issue a Intel Read
                ret = bsm_Intel_Write(Offset + index, &Buffer[index]);
                break;
            default:
                ret = FALSE;    //unknown type
                break;
            }
        }

        //clear the inprogress flag
        bsm_Flash_Set_Inprogress(FALSE);
    }
    else
    {
        ret = FALSE;
    }
    return ret;
}


/******************************************************************

FUNCTION: bsm_Flash_Write_With_Unpacked

DESCRIPTION:  This function writes a number of unpacked BYTEs to
              Flash. The Flash must be erased before trying to write
              BYTEs. The BYTEs should be passed in unpacked form,
              namely one byte per word. This function is used by
              non-volatile storage.
NOTE: The length is in WORDS an NOT BYTES.
NOTE: The ADDR is in WORD addressable NOT BYTE addressable.
NOTE: Although it writes a number of bytes, all writes are performed
      as word operations so all writes are word aligned.

ARGS:
        UINT32  Offset: Offset into the Flash to write
        BYTE*   Buffer: the memory buffer to read the BYTEs from
        UINT32  Length: The number of WORDs to write

RETURNS:
    BOOL: TRUE - Read succeeded (Flash had been identified correctly, in bounds)
          FALSE- Read failed (Flash had NOT been identified correctly, or out of bounds)

******************************************************************/
BOOL bsm_Flash_Write_With_Unpacked(UINT32 Offset, BYTE* Buffer, UINT32 Length)
{
    UINT16 indexB=0; //Byte index
    UINT16 indexW;   //Word index
    UINT16 temp;     //Temp storage for word to write to Flash
    BOOL   ret;


    //Will operation stay within flash boundary?
    if( Offset > (UINT32)bsc_EELastAddr   || //check if starting offset is valid
        Length > bsc_EELastAddr+1 - Offset) { //check if length is too long
        return FALSE;
    }

    //check the Flash In Progess Flag
    if(!bsm_Flash_Get_Inprogress())
    {
        //set the inprogress flag
        bsm_Flash_Set_Inprogress(TRUE);

        for(indexW = 0; indexW < Length; indexW++) {
            //Copy Low byte from temp to next element in Byte Array
            temp  = (((UINT16)Buffer[indexB++]) <<8) & 0xFF00;
            //Copy High byte from temp to next element in Byte Array
            temp +=  ((UINT16)Buffer[indexB++])      & 0x00FF;

            switch(bsv_Flash_Type) {   //Check the Flash type
            case bsc_SST:    //It's SST, issue a SST Read
                ret = bsm_SST_Write(Offset + indexW, &temp);
                break;
            case bsc_INTEL:    //It's Intel, issue a Intel Read
                ret = bsm_Intel_Write(Offset + indexW, &temp);
                break;
            default:
                ret = FALSE;    //unknown type
                break;
            }
        }

        //clear the inprogress flag
        bsm_Flash_Set_Inprogress(FALSE);
    }
    else
    {
        ret = FALSE;
    }
    return ret;
}


/******************************************************************

FUNCTION: bsm_Flash_Write_With_Unaligned_Packed

DESCRIPTION:  This function writes a number of BYTEs to Flash. The
              Flash must be erased before trying to write BYTEs.
              The BYTEs should be passed in packed form(as WORDs).
              This function is used by software update.
NOTE: The length is in BYTEs.

ARGS:
        UINT32  destOffset: the offset in the Flash to write
        UINT16* basePtr:    the word address of the buffer with the BYTEs to write
        UINT32  byteOffset: the byte offset into the byte array of the first byte to write
        UINT32  Length:     the number of BYTEs to write

RETURNS:
    BOOL: TRUE - Read succeeded (Flash had been identified correctly)
          FALSE- Read failed (Flash had NOT been identified correctly)

******************************************************************/
BOOL bsm_Flash_Write_With_Unaligned_Packed(UINT32 destOffset, UINT16* basePtr, UINT32 byteOffset, UINT32 length)
{
    UINT16 tempWord;
    UINT32 index;
    BOOL   ret;

    //Will operation stay within flash boundary?
    if( destOffset > (UINT32)bsc_EELastAddr || //check if starting offset is valid
        (length/2 + length%2) > bsc_EELastAddr+1 - destOffset) { //check if length is too long
        return FALSE;
    }

    //check the Flash In Progess Flag
    if(!bsm_Flash_Get_Inprogress())
    {
        //set the inprogress flag
        bsm_Flash_Set_Inprogress(TRUE);

        for(index = 0; index < length; index+=2) {   //for the number of packed words
            //build the packed word
            tempWord = bsm_getByteFromPackedArray(basePtr, byteOffset+index) << 8;

            // if this is the last byte and it only fills 1/2 the word...
            if(index == (length-1) && length%2 == 1)
            {
                tempWord |= 0x00FF;
            }
            else
            {
                tempWord |= bsm_getByteFromPackedArray(basePtr, byteOffset+index+1) & 0x00FF;
            }

            switch(bsv_Flash_Type) {   //Check the Flash type
            case bsc_SST:    //It's SST, issue a SST Read
                ret = bsm_SST_Write(destOffset + index/2, &tempWord);
                break;
            case bsc_INTEL:    //It's Intel, issue a Intel Read
                ret = bsm_Intel_Write(destOffset + index/2, &tempWord);
                break;
            default:
                return FALSE;    //unknown type
            }
        }

        //clear the inprogress flag
        bsm_Flash_Set_Inprogress(FALSE);
    }
    else
    {
        ret = FALSE;
    }
    return ret;
}


/******************************************************************

FUNCTION: bsm_Flash_Init

DESCRIPTION:  This function communicates with flash device to
              determine which type of flash is connected to the
              device. This initialization must be done before other
              operations to flash are performed.

ARGS:
        <none>

RETURNS:
    BOOL: TRUE  - Flash was found
          FALSE - Flash NOT found

******************************************************************/
BOOL bsm_Flash_Init(void){
    BOOL status;
    bsv_Flash_Type  = bsc_Unknown;

    //Initialize the flash in progwess flag
    flashInprogress = FALSE;

    //Check if we're connect to SST
    if(bsm_SST_ID() == TRUE) {
        bsv_Flash_Type = bsc_SST;
        status         = TRUE;
    }
    //Not SST so check for Intel
    else if(bsm_Intel_ID() == TRUE) {
        bsv_Flash_Type = bsc_INTEL;
        status         = TRUE;
    }
    //Not Intel so fail
    else{
        bsv_Flash_Type = bsc_Unknown;
        status         = FALSE;
    }

    return status;
}


/******************************************************************

FUNCTION: bsm_Flash_Get_Type

DESCRIPTION:  This function returns the Flash Type of device

ARGS:
        <none>

RETURNS:
    bsc_Flash_Type

******************************************************************/
bsc_Flash_Type bsm_Flash_Get_Type(void){
    return bsv_Flash_Type;
}


/******************************************************************

FUNCTION: bsm_Flash_Set_Inprogress

DESCRIPTION:  This function sets the flash inprogress conditions

ARGS:
        BOOL newState - new state for inprogress, TRUE is inprogress,
                                                  FALSE is available

RETURNS:
    <none>
******************************************************************/
inline void bsm_Flash_Set_Inprogress(BOOL newState){
    if(newState == TRUE)
    {
        bsm_PMDisableSWI();
    }
    else
    {
        bsm_PMEnableSWI();
    }
    flashInprogress = newState;
}

/******************************************************************

FUNCTION: bsm_Flash_Get_Inprogress

DESCRIPTION:  This function gets the flash inprogress status

ARGS:
    <none>

RETURNS:
    BOOL: TRUE is inprogress,
              FALSE is available
******************************************************************/
inline BOOL bsm_Flash_Get_Inprogress(){
    return flashInprogress;
}



