/************************************************************************
*
* MODULE: dbg_Flash.c
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the functions for debugging the flash.
*
*************************************************************************/

/////////////
// Includes
/////////////
#include <stdlib.h>
#include <ctype.h>

#include "global.h"
#include "bsm_serialport.h"
#include "bsm_NVStorage.h"
#include "dbg_Flash.h"

////////////
// Defines
////////////
#define MAX_WRITE_DATA_LENGTH 64

/////////////////////
// Local Prototypes
/////////////////////
BOOL IsHexData(char *HexData);

/******************************************************************

FUNCTION: WriteFlash

DESCRIPTION: This function writes data to the Flash.

ARGS:
        char* CommandLineParameters: pointer to a character array that
            contains the parameters.

RETURNS:
    <none>

******************************************************************/
void WriteFlash(char* CommandLineParameters)
{
    UINT32 Location;
    UINT32 Length;
    BYTE   Data[MAX_WRITE_DATA_LENGTH];
    UINT16 DataIndex = 0;

    // parse out the location
    Location = atoi(CommandLineParameters);

    // move the pointer to the length
    while( *CommandLineParameters != ' ' &&
           *CommandLineParameters != NULL )
    {
        CommandLineParameters++;
    }
    // skip past the ' ' after the location
    CommandLineParameters++;

    // parse out the length
    Length = atoi(CommandLineParameters);

    // move the pointer to the data
    while( *CommandLineParameters != ' ' &&
           *CommandLineParameters != NULL )
    {
        CommandLineParameters++;
    }
    // skip past the ' ' after the length
    CommandLineParameters++;

    // parse out the data
    while( *CommandLineParameters != NULL &&
           DataIndex < Length )
    {
        // Using quotes.
        if(*CommandLineParameters == '"')
        {
            CommandLineParameters++;
            while(*CommandLineParameters != '"' && DataIndex < Length)
            {
                Data[DataIndex++]=*CommandLineParameters++;
            }

            if((*CommandLineParameters != '"') || (DataIndex != Length))
            {
                bsm_SDPrint("Bad Length for the given data");
                return;
            }
        }
        // Not using quotes.
        else
        {
            // Check for '0x'
            if((*(CommandLineParameters+1)=='x') || (*(CommandLineParameters+1)=='X'))
            {
                // Move past the 0x
                CommandLineParameters += 2;
            }

            // More data?
            while((*CommandLineParameters != 0x0) && (DataIndex < Length))
            {
                // Check data
                if(IsHexData(CommandLineParameters))
                {
                    // Add data
                    Data[DataIndex++]      = PackByte(CommandLineParameters);

                    // Bump the pointer
                    CommandLineParameters += 2;
                }
                else
                {
                    // Invalid data
                    bsm_SDPrint("Bad Data format");
                    return;
                }
            }

            // Check the length
            if((DataIndex != Length) || (*CommandLineParameters))
            {
                bsm_SDPrint("Bad Length for the given data");
                return;
            }
        }
    }

    bsm_EEWriteBuf(Data, Length, Location);
}

/******************************************************************

FUNCTION: ReadFlash

DESCRIPTION: This function reads data from the Flash.

ARGS:
        char* CommandLineParameters: pointer to a character array that
            contains the parameters.

RETURNS:
    <none>

******************************************************************/
void ReadFlash(char* CommandLineParameters)
{
    UINT32 Location;
    UINT32 Length;
    BYTE   Data[8];
    UINT16 i;
    UINT16 j;

    // parse out the location
    Location = atoi(CommandLineParameters);

    // move the pointer to the length
    while( *CommandLineParameters != ' ' &&
           *CommandLineParameters != NULL )
    {
        CommandLineParameters++;
    }
    // skip past the ' ' after the location
    CommandLineParameters++;

    // parse out the length
    Length = atoi(CommandLineParameters);

    bsm_SDPrint("Address  | Hex                     | ASCII");
    bsm_SDPrint("---------|-------------------------|---------");

    // loop for each line of 8 data bytes
    for( i = 0; i < (Length+7)/8; i++ )
    {
        const char BinToHex[] = "0123456789ABCDEF";
        char       Buffer[10];

        // read the flash
        bsm_EEReadBuf(Data, 8, Location+i*8);


        // print the address
        Buffer[0] = BinToHex[((Location+i*8)>>28) & 0xF];
        Buffer[1] = BinToHex[((Location+i*8)>>24) & 0xF];
        Buffer[2] = BinToHex[((Location+i*8)>>20) & 0xF];
        Buffer[3] = BinToHex[((Location+i*8)>>16) & 0xF];
        Buffer[4] = BinToHex[((Location+i*8)>>12) & 0xF];
        Buffer[5] = BinToHex[((Location+i*8)>> 8) & 0xF];
        Buffer[6] = BinToHex[((Location+i*8)>> 4) & 0xF];
        Buffer[7] = BinToHex[((Location+i*8)>> 0) & 0xF];

        bsm_SDWrite(Buffer, 8);
        bsm_SDWrite(" | ", 3);

        // print the hex value
        for( j = 0; j < 8; j++ )
        {
            if( (i*8 + j) < Length )
            {
                // convert it from binary to hex
                Buffer[0] = BinToHex[(Data[j] >> 4) & 0xF];
                Buffer[1] = BinToHex[Data[j] & 0xF];
                Buffer[2] = 0;

                // print the byte
                bsm_SDWrite(Buffer, 2);
                bsm_SDWrite(" ", 1);
            }
            else
            {
                bsm_SDWrite("   ", 3);
            }
        }

        bsm_SDWrite("| ", 2);

        // print the printable ascii values
        for( j = 0; j < 8; j++ )
        {
            if( (i*8 + j) < Length )
            {
                if( isprint(Data[j]) )
                {
                    bsm_SDWrite((char*)&Data[j], 1);
                }
                else
                {
                    bsm_SDWrite(".", 1);
                }
            }
            else
            {
                bsm_SDWrite(" ", 1);
            }
        }
        bsm_SDPrint("");
    }
}

/******************************************************************

FUNCTION: IsHexData

DESCRIPTION: This function reads the next 2 bytes of the buffer and
             returns a boolean of whether they form a valid byte of
             hex data

ARGS:
        char* HexData: pointer to a character array that contains hex
                       data

RETURNS:
    TRUE: if the next 2 bytes form a valid hex byte
    FALSE: if otherwise

******************************************************************/
BOOL IsHexData(char *HexData)
{
    BOOL status = false;

    if((((*HexData >= '0') && (*HexData <= '9')) ||
        ((*HexData >= 'a') && (*HexData <= 'f')) ||
        ((*HexData >= 'A') && (*HexData <= 'F')))
       &&
       (((*(HexData+1) >= '0') && (*(HexData+1) <= '9')) ||
        ((*(HexData+1) >= 'a') && (*(HexData+1) <= 'f')) ||
        ((*(HexData+1) >= 'A') && (*(HexData+1) <= 'F'))))
        status = true;

    return status;
}

/******************************************************************

FUNCTION: PackByte

DESCRIPTION: This function is used to pack two characters into a
                     single character yielding an equivalent hex value. For
                     example, if the two character string "AB" are passed
                     into this function, the function will return an
                     unsigned character that is equivalent to the hex
                     value 0xAB. NOTE, the characters passed must be valid
                     hexadecimal characters (0-9, a-f, A-F).

ARGS:
        char* HexData: pointer to a character array that contains hex
                       data

RETURNS:
    Returns a UINT16 with the lower 8 bits filled with the hex
    value.

******************************************************************/
UINT16 PackByte(char *ptr)
{
    unsigned char total;

    // First we convert the character to its
    // corresponding Hex value:
    if (isdigit(*ptr))
    {       // Handles chars 0 - 9.
        total = *ptr - 48;
    }
    else if (isupper(*ptr))
    {           // Handles chars A - F
        total = *ptr - 55;
    }
    else     //if (islower(*ptr))
    {           // Assume char a - f
        total = *ptr - 87;
    }

    total <<= 4;
    ptr++;

    if (isdigit(*ptr))
    {           // Handles chars 0 - 9
        total |= *ptr - 48;
    }
    else if (isupper(*ptr))
    {           // Handles chars A - F
        total |= *ptr - 55;
    }
    else     //if (islower(*ptr))
    {           // Assume char a - f
        total |= *ptr - 87;
    }

    return total;
}

/******************************************************************

FUNCTION: CommitChanges

DESCRIPTION: This function writes the flash buffer out to flash.

ARGS:
        <none>

RETURNS:
    <none>

******************************************************************/
void CommitChanges(void)
{
    bsm_SDPrint("Committing changes.");
    bsm_EEFlush();
}
