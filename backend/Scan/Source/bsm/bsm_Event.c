/************************************************************************
*
* MODULE: bsm_Event.c
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
* bsm_EHAssetLogToBuffer
* bsm_EHBufferToAssetLog
* bsm_EHLogFull()
* bsm_EHResetLogReadPointer()
* bsm_EHReadNextEntry()
* bsm_EHLock()
*
* --Private--
* bsm_EHClearLog()
* bsm_EHInit()
* bsm_EHFlushPrep()
* bsm_EHLogEndOffset()
* bsm_EHSaveCurrLogWrite()
*
* DESCRIPTION: This module implements the event handling and logging
*              functions (For Event Log).
*
*************************************************************************/

#include <string.h>  //For string manipulation
#include <stdlib.h>
#include <stdio.h>   //For sprinf (string manipulation)
#include "bsm_Event.h"
#include "bsm_Flash.h"
#include "bsm_Flash_Intel.h"
#include "bsm_Flash_SST.h"
#include "bsm_SerialPort.h"
#include "bsm_NVStorage.h"
#include "bsm_Power.h"
#include "global.h"

#include "com_eepromapp.h"

//***********************************************************
// Defines
//************************************************************
#define ASSET_LOG_BUFFER_SIZE (4096) // About 3000 bytes are needed.

/************************************************************/
/* Global Variables                                         */
/************************************************************/
static UINT32 CurrLogWrite; //Holds the offset to first free/unused byte in log space.
static UINT32 CurrLogRead; //Holds the offset to the next byte to read in log space.
//Notes for both of above variables
//Note: This variable is stored/saved in Flash when
//non-volatile storage is Flushed to Flash and releoaded
//when the RAM byte array copy is Initiated on startup.
static char   sTemp[(UINT16)bsc_EHMAXLOGENTRY + (UINT16)1]; // To build message, linenum and filename
static char   assetLogBuffer[ASSET_LOG_BUFFER_SIZE+1]; // 1 extra for null char.
static UINT32 saveCurrLogWrite; //Copy CurrLogWrite when asset file is uploaded

/************************************************************/
/* Function Definitions										*/
/************************************************************/

/*******************************************************************************
FUNCTION: bsm_EHAssetLogToBuffer

DESCRIPTION:
      Copy the asset log entries between saveCurrLogWrite and CurrLogWrite
      to the assetLogBuffer.
      If there is not enough room in the assetLogBuffer, copy a maximum of
      ASSET_LOG_BUFFER_SIZE bytes and add NULL at the end.

ARGS:
      none.

RETURNS:
      Number of bytes of asset log that were copied.
      If all bytes could not be copied because buffer was small, then the
      return value includes the NULL. Log data would be lost if bsm_Flash_Read_With_Unpacked()
      failed to get data from asset log and put it into the assetLogBuffer. No retry exists.
*******************************************************************************/
UINT32 bsm_EHAssetLogToBuffer(void)
{
    bool   bufferEnd;
    bool   ret;
    BYTE   byteTemp[2];
    UINT32 i;

    if (CurrLogWrite == saveCurrLogWrite)
    {
        // Nothing to save.
        return 0;
    }

    // Copy from the asset log to the buffer.
    // Copy only what can be fit in the buffer.
    memset(assetLogBuffer, 0, sizeof(assetLogBuffer));
    i           = 0;
    bufferEnd   = false;
    ret         = true;
    byteTemp[0] = 0;
    byteTemp[1] = 0;
    while ((saveCurrLogWrite < CurrLogWrite) &&
           (bufferEnd == false) &&
           (ret == true))
    {
        //(2* since argument is supposed to be byte address and we have word
        // address)
        ret = bsm_Flash_Read_With_Unpacked(2*bsc_EVENTLOG_BLOCK_ADDR+2*(saveCurrLogWrite++), byteTemp, (UINT32)2);
        if (ret == true)
        {
            assetLogBuffer[i++] = byteTemp[0];
            if (i == ASSET_LOG_BUFFER_SIZE)
            {
                assetLogBuffer[i++]=0x00; // Add null, include it in return cnt
                bufferEnd          = true;
            }
            else
            {
                assetLogBuffer[i++] = byteTemp[1];
                if (i == ASSET_LOG_BUFFER_SIZE)
                {
                    assetLogBuffer[i++]=0x00; //Add null,include it in return cnt
                    bufferEnd          = true;
                }
            }
        }
    }
    return i;
}

/*****************************************************************************
FUNCTION: bsm_EHBufferToAssetLog

DESCRIPTION:
      Copies the asset log entries from assetLogBuffer to the asset log.

ARGS:
      numOfBytes = Number of Bytes to be copied.

RETURNS:
      none

NOTE:
      CurrLogWrite is updated.
******************************************************************************/
void bsm_EHBufferToAssetLog(UINT32 numOfBytes)
{
    bool   ret;
    UINT32 i;

    if (numOfBytes > 0)
    {
        i  = bsm_EEnumByteTOnumWord(numOfBytes);
        ret=bsm_Flash_Write_With_Unpacked(bsc_EVENTLOG_BLOCK_ADDR+CurrLogWrite,
                                          (BYTE*)assetLogBuffer,
                                          i);
        if (ret == true)
        {
            CurrLogWrite += i;   // Increment by the number of words we wrote.
        }
    }
}

/************************************************************************

FUNCTION: bsm_EHLogFull

DESCRIPTION:Takes an Event message and the Event code and stores them
                        in the next spot in the Flash log file. In the case where
                        the log becames full this function will toss out new entry.
                        The total-on-time counter is also stored with each log
            entry. Note that the maximum length for a string to be
            passed into EHLog() is bsc_EHMAXLOGENTRY chars.

ARGS:
    char* Message: Points to an Event message.
    int Code: Contains an Event code.
    int LineNum: Names the line of the Event.
        char* FileName:	Name of file with Event.
RETURNS:
    BOOL: TRUE if the log was written with the passed data,
          FALSE if the log is full.

*************************************************************************/
bool bsm_EHLogFull(char * Message, int Code, int LineNum, char * FileName)
{
    UINT32 i;
    UINT32 longTemp;      //Temp for ticktime
    UINT16 intTemp;       //Temp to build then transfer words to Flash
    BOOL   status;

    /*Make sure message isn't too long*/
    if(strlen(Message) >= bsc_EHMAXMESSAGELEN) { // If the string is too long
        Message[bsc_EHMAXMESSAGELEN] = 0;               // Terminate it to make it fit
    }

    /*Generate log string*/
    longTemp = NU_Retrieve_Clock();
/*    sprintf(sTemp, "%s line %d code %d tick %ld: %s",
        FileName, LineNum,
        Code, longTemp,
        Message);
    TRS 1-14-2004 -- Sprintf cannot be called from the HWI context due to its use of a
                     lock mechanism (see rts.src and CCS help for sprintf and choose LCK_pend)
                     I have since switched to strcat's and itoa's to accomplish a sprintf call.
*/

    strcpy(sTemp, FileName);
    strcat(sTemp, " line ");
    ltoa( LineNum, &sTemp[strlen(sTemp)]);     // add the LineNum to the end of the sTemp
    strcat(sTemp, " code ");
    ltoa( Code, &sTemp[strlen(sTemp)]);
    strcat(sTemp, " tick ");
    ltoa( longTemp, &sTemp[strlen(sTemp)]);
    strcat(sTemp, ": ");
    i = strlen(sTemp);
    if( i + strlen(Message) > bsc_EHMAXLOGENTRY)
    {
        Message[bsc_EHMAXLOGENTRY - i] = 0;
    }
    strcat(sTemp, Message);


    /*Determine if new log entry is too long to put into log space */
    if(( CurrLogWrite*2 + strlen(sTemp) + (UINT16)NU_GCTR_SIZE + (UINT16)bsc_EVENTCODE_SIZE) >= (UINT16)bsc_EVENTLOG_SIZE*2) {
        bsm_SDPrint("Log full - attempt to write failed.");
        status = FALSE;
    }
    else {
        /* Put down the current tick time (4 bytes) */
        longTemp = NU_Retrieve_Clock();
        intTemp  = (longTemp & 0xffff0000)>>16;
        bsm_Flash_Write_With_Packed(bsc_EVENTLOG_BLOCK_ADDR + CurrLogWrite++, &intTemp, (UINT32)1);

        intTemp  = (longTemp & 0x0000ffff);
        bsm_Flash_Write_With_Packed(bsc_EVENTLOG_BLOCK_ADDR + CurrLogWrite++, &intTemp, (UINT32)1);

        /* Put down the Event code (2 bytes) */
        bsm_Flash_Write_With_Packed(bsc_EVENTLOG_BLOCK_ADDR + CurrLogWrite++, (UINT16*)(&Code), (UINT32)1);

        /* Put down the message (up to bsc_EHMAXLOGENTRY bytes, null terminated) */
        i=0;
        while((sTemp[i] != 0x0) && (i < bsc_EHMAXLOGENTRY - 1)) {
            i++; //Getting the length of the string
        }
        sTemp[i++]    = 0x00; // Be sure to null terminate the string.
        i             = bsm_EEnumByteTOnumWord(i);
        bsm_Flash_Write_With_Unpacked(bsc_EVENTLOG_BLOCK_ADDR + CurrLogWrite, (BYTE*)sTemp, i );
        CurrLogWrite += i; //Incr by the number of words we wrote
        status        = TRUE;
    }
    /* Send the log entry to the debug port so everyone can see it */
    bsm_SDPrint(sTemp);

    return status;
}

/************************************************************************
*
* FUNCTION:	bsm_EHResetLogReadPointer
*
* DESCRIPTION:	Resets the read-out pointer to the oldest log in the
*				log file.
*
*************************************************************************/
void bsm_EHResetLogReadPointer(void)
{
    CurrLogRead = 0;
    return;
}

/************************************************************************

FUNCTION:	bsm_EHReadNextEntry

DESCRIPTION:Reads out the next entry from the log file.	It will take the log
                        message string and store it in Message, the original code and
                        store it in Code and the time that the log was store in Time.
                        Then, it advances the read-out pointer to the next log entry.
                        When all log entries have been read, it will return FALSE if
                        another attempt is made to read a log entry.

FUNCTION CONSTANTS:

ARGS:
    char* pMessage: points to an Event message. IMPORTANT! This
                    parameter must point to a buffer at least
                    (bsc_EHMAXLOGENTRY + 1) bytes long or an
                                overflow could occur.

    int* pCode: points to an Event code.
    unsigned long* pTime: points to a time indicating a log entry.

RETURNS:
    BOOL: TRUE if returning a log entry, or
          FALSE if there are no more log entries.
*************************************************************************/
bool bsm_EHReadNextEntry(char * pMessage, int * pCode, unsigned long * pTime) {
    bool   ret = false;
    BYTE   byteTemp[2];
    UINT16 intTemp;
    int    i; // loop var

    /* Are we at the end of the log space? */
    if ( CurrLogRead >= CurrLogWrite ) {
        ret = false;
    }

    /* Continue if the readout pointer is less than the boot pointer */
    else {
        /* Get tick time (4 bytes) */
        bsm_Flash_Read_With_Packed(bsc_EVENTLOG_BLOCK_ADDR + (CurrLogRead++), &intTemp, (UINT32)1);
        *pTime  = ((UINT32)(intTemp))<<16;

        bsm_Flash_Read_With_Packed(bsc_EVENTLOG_BLOCK_ADDR + (CurrLogRead++), &intTemp, (UINT32)1);
        *pTime += ((UINT32)(intTemp));

        /* Get the Event code (2 bytes) */
        bsm_Flash_Read_With_Packed(bsc_EVENTLOG_BLOCK_ADDR + (CurrLogRead++), (UINT16*)pCode, (UINT32)1);

        /* Cycle through each Word, copying it into the output buffer */
        i=0;
        do {
            bsm_Flash_Read_With_Unpacked( 2*bsc_EVENTLOG_BLOCK_ADDR + 2*(CurrLogRead++), byteTemp, (UINT32)2); //2* since arguement is supposed to be byte address and we have word address
            pMessage[i++] = byteTemp[0]; //write 1st byte back
            pMessage[i++] = byteTemp[1]; //write second byte back
        } while( byteTemp[0] != 0x00  && //1st byte isn't null
                 byteTemp[1] != 0x00  && //2nd byte isn't null
                 i < bsc_EHMAXLOGENTRY&& //message isn't too long
                 CurrLogRead <= bsc_EVENTLOG_SIZE); //end of log space doesn't occur
        ret = true;
        /* Ensure log is null-terminated */
        if(i >= bsc_EHMAXLOGENTRY || CurrLogRead > bsc_EVENTLOG_SIZE)
        {
            pMessage[i] = 0;
        }
    }

    return(ret);
}

/************************************************************************
*
* FUNCTION:	bsm_EHClearLog
*
* DESCRIPTION:	Clears the entire Event log
*
*************************************************************************/
void bsm_EHClearLog(void) {
    int    i; //loop var
    UINT32 offset;

    /*Set all pointers back to the beginning of LOG space*/
    CurrLogWrite = 0;
    CurrLogRead  = 0;

    /*Erase Log Space*/
    offset       = bsc_EVENTLOG_BLOCK_ADDR; //Set offset to start of Event Log
    switch(bsm_Flash_Get_Type()) {
    case bsc_SST:
        for(i = 0; i < (UINT32)bsc_SST_ELSECT_COUNT; i++) {
            bsm_Flash_Erase_SECT(offset); //Erase a SST Sector
            offset += SST_SECT_NUMWORDS; //Prepare next offset
        }
        break;
    case bsc_INTEL:
        for(i = 0; i < (UINT32)bsc_INTEL_ELSECT_COUNT; i++) {
            bsm_Flash_Erase_BLCK(offset); //Erase a INTEL Sector(For intel its actually a block but a smaller block size)
            offset += INTEL_SECT_NUMWORDS; //Prepare next offset
        }
        break;
    }
}


/************************************************************************

FUNCTION: bsm_EHLock

DESCRIPTION:Log the passed message string to the event log, write the
            same passed message string out the serial port, then execute
            the function to shut System Power Down. This call is to be
            used in case of a castastrophic failure.
ARGS:
    char* pEventMessage: points to an Event message.

Returns:
      <none> (and the hardware will be powered off).
*************************************************************************/

void bsm_EHLock(char *pEventMessage) {

    /* Log that we got to this call, and */
    /* send the message to the serial port */

    bsm_EHLog(pEventMessage, bsc_EHLOCKLOGCODE);

    /* Now shut down the system */
    bsm_PMShutDown();
}

/************************************************************************

FUNCTION: bsm_EHInit

DESCRIPTION:Initializes the log pointers by reading their values from the
            mirror of flash in RAM into variables.
            Note: This should only be called by the non-volatile storage
            init function right after that function has loaded the FLASH
            mirror into RAM.
ARGS:
      <none>
Returns:
      <none>
*************************************************************************/
void bsm_EHInit(void) {
    BYTE   temp[2]; //Byte array to receive data from flash and write to FlashMirror
    UINT16 backup;  //temp used to hold backup of write pointer while verifying its value
    UINT16 i;     //loop var
    BOOL   nullLogFound; //notes if we have found a log entry of all FFs


    /* Determine the CurrLogWrite pointer */
    //The value stored in the write pointer is not needed. To ensure
    //a valid write pointer on power-up the unit will determine a write
    //pointer value by attempting to 'read' the logs until it encounters
    //an empty log (or end of log space).
    CurrLogWrite = 0;

    /*walk through event log using the write pointer as a read pointer to *
    **find its correct value within the log space                         */

    /*while there is still room for a log to be written*/
    while( CurrLogWrite < ((UINT16)bsc_EVENTLOG_SIZE - bsm_EEnumByteTOnumWord((UINT16)NU_GCTR_SIZE) -
                           bsm_EEnumByteTOnumWord((UINT16)bsc_EVENTCODE_SIZE)) ) {
        /*Make a backup of the log write pointer*/
        backup = CurrLogWrite;

        /*Enough room exists in log space for a log entry, check if there is a
        **valid entry after this point. A valid entry is one that is not all FF's*/
        for(i=0; i<bsc_EHMAXLOGENTRY; i++) {

            /*Read the next two bytes from the log*/
            bsm_Flash_Read_With_Unpacked( 2*bsc_EVENTLOG_BLOCK_ADDR + 2*(CurrLogWrite++), temp, (UINT32)2); //2* since arguement is supposed to be byte address and we have word address

            /*check for a non-FF char*/
            if(temp[0] != 0xFF ||
               temp[1] != 0xFF) {
                /*A non-FF char was found, leave for-loop*/
                nullLogFound = FALSE;
                break;
            }

            /*All FF's encountered so far, check if currLogWrite is in bounds*/
            if(CurrLogWrite > bsc_EVENTLOG_SIZE ||
               i >= bsc_EHMAXLOGENTRY - 1) {
                nullLogFound = TRUE;
                break;
            }
        } //for

        /*check if a non-FF char was found*/
        if(nullLogFound == TRUE) {
            /*We have read a full log message length of 0xFF's, reset write ptr
            **back to saved value, the write pointer is now at a valid spot*/
            CurrLogWrite = backup;
            break; //out of while loop, we have found the valid pointer value
        }
        else{
            /*A non-FF char was found, continue reading entry until a null term,
            ** max message length, or end of log space occurs*/

            /*Make sure we are in the log message space */
            /*Note: i is the loop variable telling how far into the message
            **      space of the log entry we are in.                       */
            if( CurrLogWrite < backup + bsm_EEnumByteTOnumWord((UINT16)NU_GCTR_SIZE) +
                bsm_EEnumByteTOnumWord((UINT16)bsc_EVENTCODE_SIZE) ) {
                /*Incr currLogWrite to start of message space in log entry*/
                i            = 0;
                CurrLogWrite = backup + bsm_EEnumByteTOnumWord((UINT16)NU_GCTR_SIZE) +
                               bsm_EEnumByteTOnumWord((UINT16)bsc_EVENTCODE_SIZE);
            }
            else{
                /*we're already in message space, set i accordingly*/
                i = CurrLogWrite - backup - bsm_EEnumByteTOnumWord((UINT16)NU_GCTR_SIZE) -
                    bsm_EEnumByteTOnumWord((UINT16)bsc_EVENTCODE_SIZE);
            }

            /* Cycle through each Word in the log until end of this log occurs*/
            do {
                bsm_Flash_Read_With_Unpacked( 2*bsc_EVENTLOG_BLOCK_ADDR + 2*(CurrLogWrite++), temp, (UINT32)2); //2* since arguement is supposed to be byte address and we have word address
                i += 2;                 //increment byte count of message section.
            } while( temp[0] != 0x00      && //1st byte isn't null
                     temp[1] != 0x00      && //2nd byte isn't null
                     i < bsc_EHMAXLOGENTRY&& //message isn't too long
                     CurrLogWrite < bsc_EVENTLOG_SIZE); //end of log space doesn't occur

            if( i >= bsc_EHMAXLOGENTRY)
            {
                CurrLogWrite--;
                temp[0] = 0x00; // set to null
                temp[1] = 0x00; // set to null
                bsm_Flash_Write_With_Unpacked( bsc_EVENTLOG_BLOCK_ADDR + CurrLogWrite++, temp, (UINT32)1);
            }
        }
    } //while

    /*Read from CurrLogRead FlashMirror */
    bsm_EEReadBuf((UINT8*)temp, coc_CurrLogRead_SIZE, coc_CurrLogRead_ADDR );
    CurrLogRead  =  ((UINT16)temp[0] << 8);              //Low Byte
    CurrLogRead += ((UINT16)temp[1]     ) & 0x00FF;      //High Byte

    /*write pointer was valid, check read pointer*/
    if(CurrLogRead >= bsc_EVENTLOG_SIZE || CurrLogRead > CurrLogWrite) {
        bsm_EHResetLogReadPointer();     /* Value of read pointer is invalid, *
                                         ** reset it to beginning of log      */
    }

}

/************************************************************************

FUNCTION: bsm_EHFlushPrep

DESCRIPTION:Write log pointers to the FlashMirror in preperation for a
            Flush to Flash.
            Note: This should only be called by the non-volatile storage
            Flush function prior to flushing the FlashMirror in RAM to
            Flash.
ARGS:
      <none>
Returns:
      <none>
*************************************************************************/
void bsm_EHFlushPrep(void) {
    BYTE temp[2]; //Byte array to write to FlashMirror

    /*Fill temp byte array and Write CurrLogWrite to FlashMirror*/
    temp[0] = (BYTE)( (CurrLogWrite & 0xFF00) >> 8 ); //Low Byte
    temp[1] = (BYTE)( (CurrLogWrite & 0x00FF)      ); //High byte
    bsm_EEWriteBuf((UINT8*)temp, coc_CurrLogWrite_SIZE, coc_CurrLogWrite_ADDR );

    /*Fill temp byte array and Write CurrLogRead to FlashMirror*/
    temp[0] = (BYTE)( (CurrLogRead & 0xFF00) >> 8 ); //Low Byte
    temp[1] = (BYTE)( (CurrLogRead & 0x00FF)      ); //High byte
    bsm_EEWriteBuf((UINT8*)temp, coc_CurrLogRead_SIZE, coc_CurrLogRead_ADDR );
}

/*****************************************************************************
FUNCTION:
      bsm_EHSaveCurrLogWrite

DESCRIPTION:
      Copies "CurrLogWrite" to "saveCurrLogWrite".

ARGS:
      none.

Returns:
      none.
******************************************************************************/
void bsm_EHSaveCurrLogWrite(void)
{
    saveCurrLogWrite = CurrLogWrite;
}


