/************************************************************************
*
* MODULE: dbg_ReceiveXModem.c
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the functions to receive a file over
*              X-Modem.
*
*************************************************************************/

/////////////
// Includes
/////////////
#include <csl.h>

#include "global.h"
#include "bsm_serialport.h"

////////////
// Defines
////////////
#define END_OF_TRANSFER_TIME 2000

/******************************************************************

FUNCTION: GetXModemFile

DESCRIPTION: This function gets a file from the debug port using
             the X-Modem protocol

ARGS:
        char* returnBuffer: the buffer to put the data

RETURNS:
    Returns the number of WORDS received.

******************************************************************/
char XBuffer[128];
UINT32 GetXModemFile(char* returnBuffer)
{
    GLB_LTMR_OBJ StartTxTimer;
    GLB_LTMR_OBJ EndOfTransferTimer;
    int          Retries     = 0;
    UINT16       Checksum;
    BOOL         NotStarted  = TRUE;
    INT16        Data;
    UINT32       BufferIndex = 0;

    UINT32 Address           = (UINT32)returnBuffer;

    enum X_MODEM_STATE
    {
        HEADER,
        BLOCK,
        N_BLOCK,
        DATA1,
        DATA2,
        CHECKSUM
    };
    enum X_MODEM_STATE State = HEADER;


    // prompt the user to send the file
    bsm_SDPrint("Send the file by X MODEM to burn into flash.");

    // Send a NAK every 3 seconds until the transfer starts.  Exit after 10 tries.

    while(Retries < 10 && NotStarted == TRUE)
    {
        Retries++;

        // Send a NAK
        bsm_SDWrite("\x15", 1);

        // Wait 3 seconds
        GLB_GET_LTMR(StartTxTimer);

        while(!GLB_HAS_LTMR_EXPIRED(StartTxTimer, 3000))
        {
            if( (Data = bsm_SDRead()) != -1 )
            {
                NotStarted = FALSE;
                break;
            }
        }
    }

    if( NotStarted == FALSE )
    {
        GLB_GET_LTMR(EndOfTransferTimer);
        while( !GLB_HAS_LTMR_EXPIRED( EndOfTransferTimer, END_OF_TRANSFER_TIME) )
        {
            UINT16 Count;
            switch(State)
            {
            case HEADER:
                if( Data == '\x01' )
                {
                    State = BLOCK;
                }
                else if( Data == '\x04' )
                {
                    // Send an ACK
                    bsm_SDWrite("\x06", 1);

                    return BufferIndex;
                }
                break;

            case BLOCK:
                State = N_BLOCK;
                break;

            case N_BLOCK:
                State    = DATA1;
                Count    = 0;
                Checksum = 0;
                break;

            case DATA1:
                (*(UINT16*)Address) = Data;
                Checksum           += Data;
                Count++;
                State               = DATA2;
                break;

            case DATA2:
                *((UINT16*)Address) = (*((UINT16*)Address)<<8) | Data;

                Address++;
                BufferIndex++;
                Checksum += Data;
                Count++;

                if( Count == 128 )
                {
                    State = CHECKSUM;
                }
                else
                {
                    State = DATA1;
                }
                break;

            case CHECKSUM:
                if( (Checksum&0xFF) == (Data&0xFF) )
                {
                    State = HEADER;

                    // Send an ACK
                    bsm_SDWrite("\x06", 1);

                }
                else
                {
                    // move back a block
                    BufferIndex = BufferIndex - 128/2;
                    Address     = Address - 128/2;

                    State       = HEADER;

                    // Send a NAK
                    bsm_SDWrite("\x15", 1);
                }
            }

            while( !GLB_HAS_LTMR_EXPIRED( EndOfTransferTimer, END_OF_TRANSFER_TIME) )
            {
                if( (Data = bsm_SDRead()) >= 0 )
                {
                    GLB_GET_LTMR(EndOfTransferTimer);
                    break;
                }
            }

        }
    }

    return BufferIndex;
}

