/************************************************************************
*
* MODULE: bsm_General.c
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
* bsm_GeneratePointer()
*
* DESCRIPTION: This file contains general board support functionality
*
*************************************************************************/

#include <string.h>
#include <stdio.h>
#include "global.h"
#include "bsm_General.h"
#include "bsm_DAA.h"
#include "bsm_serialport.h"
#include "bsm_SwitchInput.h"
#include "bsm_Led.h"
#include "cx077.h"


UINT16 bsv_unpackBuffer[BSM_UNPACK_STRSTR_SIZE];
BOOL   bsv_doPrintNetworkDebug = FALSE;
char   bsv_genTempBuffer[100];

/******************************************************************

FUNCTION: bsm_GeneratePointer

DESCRIPTION:  This function does full address pointer manipulation.
                        See page 6-101 in the 55xx CPU guide (SPRU371e).  There is a note explaining
                        that the 55xx CPU address data with the pointers using 64k modulo
                        addressing.  The C compiler will also use such pointer addressing.
                        According to ANSI C standard for C, the max array size turns out to be a
                        16-bit number, and should really be limited to 32kW.  So the C compiler will
                        not address an array that spans a 64kW boundary, unless you add some extra
                        code to handle the transitions across the 64kW Main Data Pages (MDP's).

                        Without additional code to handle the transitions across the MDP's, an array
                        greater than 64kW or an array crossing a 64kW boundary cannot be accessed
                        across its entire range using the C compiler.  Since the pointers are modulo
                        64kW, they will wrap around at the end of the MDP they start on.

                        To get around this, you need to create some routines for incrementing or
                        decrementing a pointer into the array.  If you only did random accesses to
                        the array, you would be OK.  But when you do increments or decrements, you
                        need to use these extra functions to make sure the pointer updates are done
                        with 23-bits instead of just 16-bits.

ARGS:
        char* base: base pointer address to start from
        UINT32 offset: offset from base pointer to generate

RETURNS:
    char*: generated pointer that is offset from base.

******************************************************************/
char* bsm_GeneratePointer(char* base, INT32 offset)
{
    UINT32 temp;

    temp  = (UINT32)base;
    temp += offset;
    return (char*)temp;
}


/******************************************************************

FUNCTION: bsm_getByteFromPackedArray

DESCRIPTION:  This function retrieves a byte from a packed array,
              it grabs a byte based on the byte offset into the array

ARGS:
        char* basePtr: base of the packed array
        UINT32 offset: byte offset from base pointer of byte t get

RETURNS:
    BYTE: retrieved byte

******************************************************************/
BYTE bsm_getByteFromPackedArray(UINT16* basePtr, UINT32 offset)
{
    UINT16 temp;

    // grab the word that the desired byte is in
    temp = *bsm_GeneratePointer((char*)basePtr, offset/2);

    //determine which byte of the word to grab
    if(offset%2 == 1)
    {    //grab the low byte
        return (temp & 0x00FF);
    }
    else
    {    //grab high byte
        return (temp & 0xFF00) >> 8;
    }
}

/******************************************************************

FUNCTION: bsm_unpackByteArray

DESCRIPTION:  This function unpacks a byte array into the requested
              buffeer

ARGS:
        char* dest: The destination for the unpacked data
        char* basePtr: base of the packed array
        UINT32 offset: byte offset from base pointer to start unpacking at
        UINT32 length:number of bytes to unpack

RETURNS:
    <none>

******************************************************************/
void bsm_unpackByteArray(char* dest, UINT16* basePtr, UINT32 offset, UINT32 length)
{
    UINT32 index;

    for(index = 0; index < length; index++)
    {
        *bsm_GeneratePointer(dest, index) = bsm_getByteFromPackedArray(basePtr, offset++);
    }
}


/******************************************************************

FUNCTION: bsm_packedStringSearch

DESCRIPTION:  This function unpacks a byte array and calls strstr.

ARGS:
        char* string1: Source string that is packed, this gets unpacked
                       and is used as the first arguement to a strstr call
        char* string2: String to searchm, this is an unpacked string, this
                       gets used as the second arguement to a strstr call

NOTE: The size of the search is limited to BSM_UNPACK_STRSTR_SIZE characters.
RETURNS:
    char*: return from the strstr call

******************************************************************/
char* bsm_packedStringSearch(char* string1, char* string2)
{
    int i;
    if(string1 != NULL)
    {
        i = 0;
        //unpack the string until null is encountered
        while(i < BSM_UNPACK_STRSTR_SIZE)
        {
            bsv_unpackBuffer[i] = bsm_getByteFromPackedArray((UINT16*)string1, i);
            i++;

            if(bsv_unpackBuffer[i-1] == NULL)
            {
                break;
            }
        }
        //null terminate incase end of unpack buffer is reached before null-character
        bsv_unpackBuffer[i-1] = NULL;
    }

    return strstr((char*)bsv_unpackBuffer, string2);
}

/******************************************************************

FUNCTION: bsm_setModemState

DESCRIPTION:  This function turns ON/OFF the modem. It returns the init
              status. A return value from a call where the desired
              strate is OFF is invalid.

ARGS:
        UINT32 newState: BOOLEAN (ON/OFF) of desired state for the modem.

RETURNS:
    UINT16: This is the modem init status, it is only valid when the desired
             state is ON.

******************************************************************/
#define MODEM_SHUTOFF_DELAY_IN_MS (200)
UINT16 bsm_setModemState(UINT32 newState)
{
    static UINT32 state = OFF;
    UINT16        status;

    status = MDM_ERRORCODE__NO_ERROR;     //set the default return code

    switch(newState)
    {
    case ON:
        bsm_DAA_Reset();
        if(state == OFF)
        {
            status = mdm_Init();
            //set the DTMF strength by default, any country code change
            //will need to set it again.
            mdm_setModemDTMFStrength();
        }
        state = ON;         //denote the new state
        break;
    case OFF:
        if(state == ON)
        {
            mdm_Shut_Off();
            GLB_LTMR_WAIT(MODEM_SHUTOFF_DELAY_IN_MS);
        }
        state = OFF;         //denote the new state
        break;
    default:    //if an undefined parameter is passed, shut off the modem
        mdm_Shut_Off();
        GLB_LTMR_WAIT(MODEM_SHUTOFF_DELAY_IN_MS);
    }

    return status;
}




/******************************************************************

FUNCTION: bsm_CopyCode

DESCRIPTION:  This function copied code from the load address to the
              run address

ARGS:
        UINT32 LoadStart; load address(source)
        UINT32 RunStart: run address (destination)
        UINT16 Size: length of transfer

RETURNS:
    <none>

******************************************************************/
void bsm_CopyCode(UINT32 LoadStart, UINT32 RunStart, UINT16 Size)
{
    UINT16 i;
    UINT16 * Source;
    UINT16 * Destination;

    for( i = 0; i < Size; i++)
    {
        Source       = (UINT16*)LoadStart;
        Destination  = (UINT16*)RunStart;

        *Destination = *Source;
        LoadStart++;
        RunStart++;
    }
}



/******************************************************************

FUNCTION: bsm_VocalNetworkDebugPRD

DESCRIPTION:  This grabs serialized data from the Vocal network layer
              and echos it out the serial port <if enabled>. It also
              allows use of vocal LANsEND command line through the
              serial port <if enabled>.

NOTES: If the is intended to be used (for debug), a PRD must be
       created that calls this function. A period of 20ms is suggested
       define __NET_PRINTDEBUG__ to enable the printing of the network
            debug port. This must be enabled to see results from the
            command line interface
       define __NET_CMDLINE__ to enable interaction with the network
            command line interface via the serial port.

ARGS:
        <none>

RETURNS:
    <none>

******************************************************************/
void bsm_VocalNetworkDebugPRD(void)
{
        #ifdef __NET_PRINTDEBUG__
                #warn "Network debug printing is enabled"

    INT16        data;
    UINT16       i;
    GLB_HTMR_OBJ startTime;

    GLB_GET_HTMR(startTime);
    //By default service and empty the buffer.
    //check transmit buffer mutex
    if(bsm_SDTxCheckMutex() == FALSE)
    {
        // continue printing from buffer while valid data is present and
        // before a ms timeout occurs
        i = 0;

        while( ((data = serial_console_tx()) & 0x8000) != 0x8000 )
        {
            bsv_genTempBuffer[i] = data & 0x00FF;
            i++;
            if( GLB_HAS_HTMR_EXPIRED(startTime, (UINT32)1000000) == TRUE || i >= sizeof(bsv_genTempBuffer) )
            {
                break;                        //out of while loop
            }
        }
        //check if output should occur
        if(bsv_doPrintNetworkDebug == TRUE)
        {
            bsm_SDWrite_Unlimited(bsv_genTempBuffer, i);
        }
    }

    //send commands to Vocal's layers
                #ifdef __NET_CMDLINE__
                        #warn "Network debug command line interface is enabled"
    data = bsm_SDRead();
    // Provide characters to Vocal's command line interface
    while( data > 0 )
    {
        serial_console_rx(data);
        data = bsm_SDRead();
        if( GLB_HAS_HTMR_EXPIRED(startTime, (UINT32)1000000) == TRUE )
        {
            break;                            //out of while loop
        }
    }
                #endif
        #endif
}

/******************************************************************

FUNCTION: bsm_setNetworkDebugPrint

DESCRIPTION:  This sets the variable that determines if the
              debug printing prints out to the serial port or not.
NOTE:         This only makes sense when __NET_PRINTDEBUG__ is
              defined otherwise with has no effect.

ARGS:
        BOOL desiredState: TRUE to enable the printing of the debug
                           buffer, FALSE otherwise.
RETURNS:
    <none>

******************************************************************/
void bsm_setNetworkDebugPrint(BOOL desiredState)
{
    bsv_doPrintNetworkDebug = desiredState;
}

/******************************************************************

FUNCTION: bsm_modemConstantTransmit

DESCRIPTION:  This function does not return. It starts the modem,
              it dials the phone number '102'. It's intended to be
              used with a phone line simulator. It connects to
              another modem and continously echos out a message
              with a counter at the end.

ARGS:
        <none>
RETURNS:
    <none>

******************************************************************/
void bsm_modemConstantTransmit(void)
{
    UINT16              status;
    UINT16              Index  = 0;
    bst_ToneSwitchState TPSwitch;
    UINT16              strobe = FALSE;

    bsm_LDChange(bsc_LEDNODIALTONE, bsc_LEDOFF);
    bsm_LDChange(bsc_LEDDATA1,bsc_LEDOFF);
    bsm_LDChange(bsc_LEDDATA2,bsc_LEDOFF);
    bsm_LDChange(bsc_LEDDATA3,bsc_LEDOFF);
    bsm_SDPrint("***< Starting Constant Transmit Test >***");

    //begin the modem testing
    status = bsm_setModemState(ON);
    if(status != MDM_ERRORCODE__NO_ERROR)
    {           // Modem returned init error
        bsm_SDPrint("Modem init failed during testing phase, stopping modem testing:");
        sprintf(bsv_genTempBuffer, "error: %d", status);
        bsm_SDPrint(bsv_genTempBuffer);
        bsm_LDChange(bsc_LEDNODIALTONE, bsc_LEDFASTFLASH);
    }
    else
    {
        //read tone/Pulse switch and add number
        TPSwitch = bsm_INReadTonePulse();
        switch(TPSwitch) {
        case bsc_TONE:
            strcpy(bsv_genTempBuffer, "ATDT");
            break;
        case bsc_PULSE:
        default:
            strcpy(bsv_genTempBuffer, "ATDP");
            break;
        }
        strcat(bsv_genTempBuffer, "102\r");
        mdm_Send_Control_String(bsv_genTempBuffer, bsv_genTempBuffer, sizeof(bsv_genTempBuffer));
        bsm_SDPrint(bsv_genTempBuffer);

        bsm_SDPrint("***< Dialing... >***");
        bsm_SDPrint(bsv_genTempBuffer);

        sprintf(bsv_genTempBuffer, "***< Hello World, I am the 2490G CLM! >***\r");
        status = mdm_Send_String(strlen(bsv_genTempBuffer), bsv_genTempBuffer);

        while(1)
        {               //Send out a message
            if(strobe == FALSE)
            {
                bsm_LDChange(bsc_LEDDATA1,bsc_LEDSTROBE);
                strobe = TRUE;
            }

            sprintf(bsv_genTempBuffer, "The quick red fox jumps over the lazy brown dog. :%d\r\n", Index++);
            status = mdm_Send_String(strlen(bsv_genTempBuffer), bsv_genTempBuffer);
            if( status != strlen(bsv_genTempBuffer))
            {
                bsm_LDChange(bsc_LEDNODIALTONE, bsc_LEDFASTFLASH);
                bsm_LDChange(bsc_LEDDATA1,bsc_LEDOFF);
                bsm_LDChange(bsc_LEDDATA2,bsc_LEDOFF);
                bsm_LDChange(bsc_LEDDATA3,bsc_LEDOFF);
                while(1) ;                //error condition, wait where
            }
            GLB_LTMR_WAIT(1000UL);      //wait a sec
        }
    }


}

