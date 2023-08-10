/************************************************************************
*
* MODULE: bsm_AppCrc.c
*
* OWNER:
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the functions to check the Flash and
*              to check the program that is running in RAM.
*
*************************************************************************/

/////////////
// Includes
/////////////
#include "global.h"
#include "bsm_AppCrc.h"
#include "com_eepromapp.h"
#include "bsm_NVStorage.h"
#include <stdio.h>
#include "bsm_global.h"

////////////
// Defines
////////////
#define CRC_INIT 0x0000

//////////
// Types
//////////

////////////
// Globals
////////////

#ifndef SKIP_CRC
extern UINT16 StoredCrcL;
extern UINT16 StoredCrcH;
#endif

static const unsigned short AIC_CRCTable[256] =
{       0x0000, 0xc0c1, 0xc181, 0x0140, 0xc301, 0x03c0, 0x0280, 0xc241,
        0xc601, 0x06c0, 0x0780, 0xc741, 0x0500, 0xc5c1, 0xc481, 0x0440,
        0xcc01, 0x0cc0, 0x0d80, 0xcd41, 0x0f00, 0xcfc1, 0xce81, 0x0e40,
        0x0a00, 0xcac1, 0xcb81, 0x0b40, 0xc901, 0x09c0, 0x0880, 0xc841,
        0xd801, 0x18c0, 0x1980, 0xd941, 0x1b00, 0xdbc1, 0xda81, 0x1a40,
        0x1e00, 0xdec1, 0xdf81, 0x1f40, 0xdd01, 0x1dc0, 0x1c80, 0xdc41,
        0x1400, 0xd4c1, 0xd581, 0x1540, 0xd701, 0x17c0, 0x1680, 0xd641,
        0xd201, 0x12c0, 0x1380, 0xd341, 0x1100, 0xd1c1, 0xd081, 0x1040,
        0xf001, 0x30c0, 0x3180, 0xf141, 0x3300, 0xf3c1, 0xf281, 0x3240,
        0x3600, 0xf6c1, 0xf781, 0x3740, 0xf501, 0x35c0, 0x3480, 0xf441,
        0x3c00, 0xfcc1, 0xfd81, 0x3d40, 0xff01, 0x3fc0, 0x3e80, 0xfe41,
        0xfa01, 0x3ac0, 0x3b80, 0xfb41, 0x3900, 0xf9c1, 0xf881, 0x3840,
        0x2800, 0xe8c1, 0xe981, 0x2940, 0xeb01, 0x2bc0, 0x2a80, 0xea41,
        0xee01, 0x2ec0, 0x2f80, 0xef41, 0x2d00, 0xedc1, 0xec81, 0x2c40,
        0xe401, 0x24c0, 0x2580, 0xe541, 0x2700, 0xe7c1, 0xe681, 0x2640,
        0x2200, 0xe2c1, 0xe381, 0x2340, 0xe101, 0x21c0, 0x2080, 0xe041,
        0xa001, 0x60c0, 0x6180, 0xa141, 0x6300, 0xa3c1, 0xa281, 0x6240,
        0x6600, 0xa6c1, 0xa781, 0x6740, 0xa501, 0x65c0, 0x6480, 0xa441,
        0x6c00, 0xacc1, 0xad81, 0x6d40, 0xaf01, 0x6fc0, 0x6e80, 0xae41,
        0xaa01, 0x6ac0, 0x6b80, 0xab41, 0x6900, 0xa9c1, 0xa881, 0x6840,
        0x7800, 0xb8c1, 0xb981, 0x7940, 0xbb01, 0x7bc0, 0x7a80, 0xba41,
        0xbe01, 0x7ec0, 0x7f80, 0xbf41, 0x7d00, 0xbdc1, 0xbc81, 0x7c40,
        0xb401, 0x74c0, 0x7580, 0xb541, 0x7700, 0xb7c1, 0xb681, 0x7640,
        0x7200, 0xb2c1, 0xb381, 0x7340, 0xb101, 0x71c0, 0x7080, 0xb041,
        0x5000, 0x90c1, 0x9181, 0x5140, 0x9301, 0x53c0, 0x5280, 0x9241,
        0x9601, 0x56c0, 0x5780, 0x9741, 0x5500, 0x95c1, 0x9481, 0x5440,
        0x9c01, 0x5cc0, 0x5d80, 0x9d41, 0x5f00, 0x9fc1, 0x9e81, 0x5e40,
        0x5a00, 0x9ac1, 0x9b81, 0x5b40, 0x9901, 0x59c0, 0x5880, 0x9841,
        0x8801, 0x48c0, 0x4980, 0x8941, 0x4b00, 0x8bc1, 0x8a81, 0x4a40,
        0x4e00, 0x8ec1, 0x8f81, 0x4f40, 0x8d01, 0x4dc0, 0x4c80, 0x8c41,
        0x4400, 0x84c1, 0x8581, 0x4540, 0x8701, 0x47c0, 0x4680, 0x8641,
        0x8201, 0x42c0, 0x4380, 0x8341, 0x4100, 0x81c1, 0x8081, 0x4040 };

///////////////
// Prototypes
///////////////

/******************************************************************

FUNCTION: bsm_CheckProgram

DESCRIPTION:  This function verifies the flash is correct.  It also
              verifies the program was copied into RAM correctly.

ARGS:
        <none>

RETURNS:
    TRUE if the program is correct.
    FALSE if the program is not correct.

******************************************************************/
BOOL bsm_CheckProgram(void)
{
    // Calculated CRC of the flash
    UINT32 Crc;

    // Pointer to the beginning of flash
    UINT16* FlashPtr = (UINT16*)bsc_FLASHBASEADDR+bsc_CODE_BLOCK_ADDR;

    UINT32 Size      = bsc_CODE_BLOCK_LENGTH - 2;

    BYTE CrcBuffer[coc_SWVer_SIZE];

    BYTE outputLine[80];

    // First we need to CRC the Flash and compare the calculated CRC with the
    // CRC stored in Flash
    Crc = CalculateCcitt32(FlashPtr, 0, Size*2);

    (void)sprintf(outputLine,"*** %08lx ***",Crc);
    bsm_SDPrint(outputLine);

#ifndef SKIP_CRC
    // The CRC is stored at the end of flash
    if( Crc != bsm_AppCRCValue() )
    {
        return FALSE;
    }

    // write the CRC to the non-volatile storage
    CrcBuffer[0] = (StoredCrcH >> 8) & 0xFF;
    CrcBuffer[1] = (StoredCrcH >> 0) & 0xFF;
    CrcBuffer[2] = (StoredCrcL >> 8) & 0xFF;
    CrcBuffer[3] = (StoredCrcL >> 0) & 0xFF;

    bsm_EEWriteBuf(CrcBuffer, coc_SWVer_SIZE, coc_SWVer_ADDR);
#else
        #warn "WARNING: Skipped CRC Check."
#endif

    // all the locations match
    return TRUE;
}


/******************************************************************

FUNCTION: aim_CRC

DESCRIPTION:  Calculates the CRC of the lower 8-bits of a 16-bit
              word.

ARGS:
        BYTE* DataPtr: A pointer the the first word to CRC
        UINT16 Length: The number of words to CRC.

RETURNS:
    The calculated CRC of the word

******************************************************************/
UINT16 aim_CRC(BYTE *p_data, UINT32 length)
{
    // index through the data
    UINT32 i;

    // calculated CRC
    UINT16 crc;

    // index into the CRC table
    UINT16 crcIndex;

    // Current data byte
    UINT16 Data;

    // Address of the data to CRC
    UINT32 Address;

    Address = (UINT32)p_data;

    for (i=0, crc=CRC_INIT; i<length; i++)
    {
        // grab the lower byte
        Data     = (*((UINT16*)Address)) & 0xFF;

        // Calculate the intermediate byte value
        crcIndex = (unsigned short)crc ^ Data;

        // Shift the crc_index right eight times with the high order
        //  bits being filled with zeros.
        crc = (crc & 0xFF00) >> 8;
        crc = AIC_CRCTable[(crcIndex & 0xFF)] ^ crc;

        // go to the next address
        Address++;
    }

    return(crc);
}


/******************************************************************

FUNCTION: aim_CRCPerByte

DESCRIPTION:  Calculates new CRC value given a new data byte and an
                          initial CRC.

ARGS:
        UINT16 InitialCRC: An initial CRC value.
        BYTE Data: A char to add to the Initial CRC


RETURNS:
    The new calculated CRC.

******************************************************************/
UINT16 aim_CRCPerByte(UINT16 CurrentCRC, BYTE Data)
{
    // index into the CRC table
    UINT16 crcIndex;

    // Current data byte
    // Calculate the intermediate byte value
    // Make sure it's 8 bits in the data
    crcIndex = CurrentCRC ^ (UINT16)(Data & 0x00FF);

    // Shift the crc_index right eight times with the high order
    //  bits being filled with zeros.
    CurrentCRC = (CurrentCRC & 0xFF00) >> 8;
    CurrentCRC = AIC_CRCTable[(crcIndex & 0xFF)] ^ CurrentCRC;

    return(CurrentCRC);
}


/******************************************************************

FUNCTION: CalculateProgramCrc

DESCRIPTION:  Calculates the CRC of of a 16-bit word.

ARGS:
        BYTE* DataPtr: A pointer the the first word to CRC
        UINT16 Length: The number of words to CRC.

RETURNS:
    The calculated CRC of the word

******************************************************************/
UINT16 CalculateProgramCrc(BYTE *p_data, UINT32 length)
{
    // index through the data
    UINT32 i;

    // calculated CRC
    UINT16 crc;

    // index into the CRC table
    UINT16 crcIndex;

    // Current data byte
    UINT16 Data;

    // Address of the data to CRC
    UINT32 Address;

    Address = (UINT32)p_data;

    for (i=0, crc=CRC_INIT; i<length; i++)
    {
        // grab the upper byte
        Data     = (*((UINT16*)Address))>>8;

        // Calculate the intermediate byte value
        crcIndex = (unsigned short)crc ^ Data;

        // Shift the crc_index right eight times with the high order
        //  bits being filled with zeros.
        crc      = (crc & 0xFF00) >> 8;
        crc      = AIC_CRCTable[(crcIndex & 0xFF)] ^ crc;

        // grab the lower byte
        Data     = (*((UINT16*)Address)) & 0xFF;

        // Calculate the intermediate byte value
        crcIndex = (unsigned short)crc ^ Data;

        // Shift the crc_index right eight times with the high order
        //  bits being filled with zeros.
        crc = (crc & 0xFF00) >> 8;
        crc = AIC_CRCTable[(crcIndex & 0xFF)] ^ crc;

        // go to the next address
        Address++;
    }

    return(crc);
}

static const unsigned long CcittCrcTable[256] =
{
    0x00000000L, 0x77073096L, 0xEE0E612CL, 0x990951BAL,
    0x076DC419L, 0x706AF48FL, 0xE963A535L, 0x9E6495A3L,
    0x0EDB8832L, 0x79DCB8A4L, 0xE0D5E91EL, 0x97D2D988L,
    0x09B64C2BL, 0x7EB17CBDL, 0xE7B82D07L, 0x90BF1D91L,
    0x1DB71064L, 0x6AB020F2L, 0xF3B97148L, 0x84BE41DEL,
    0x1ADAD47DL, 0x6DDDE4EBL, 0xF4D4B551L, 0x83D385C7L,
    0x136C9856L, 0x646BA8C0L, 0xFD62F97AL, 0x8A65C9ECL,
    0x14015C4FL, 0x63066CD9L, 0xFA0F3D63L, 0x8D080DF5L,
    0x3B6E20C8L, 0x4C69105EL, 0xD56041E4L, 0xA2677172L,
    0x3C03E4D1L, 0x4B04D447L, 0xD20D85FDL, 0xA50AB56BL,
    0x35B5A8FAL, 0x42B2986CL, 0xDBBBC9D6L, 0xACBCF940L,
    0x32D86CE3L, 0x45DF5C75L, 0xDCD60DCFL, 0xABD13D59L,
    0x26D930ACL, 0x51DE003AL, 0xC8D75180L, 0xBFD06116L,
    0x21B4F4B5L, 0x56B3C423L, 0xCFBA9599L, 0xB8BDA50FL,
    0x2802B89EL, 0x5F058808L, 0xC60CD9B2L, 0xB10BE924L,
    0x2F6F7C87L, 0x58684C11L, 0xC1611DABL, 0xB6662D3DL,
    0x76DC4190L, 0x01DB7106L, 0x98D220BCL, 0xEFD5102AL,
    0x71B18589L, 0x06B6B51FL, 0x9FBFE4A5L, 0xE8B8D433L,
    0x7807C9A2L, 0x0F00F934L, 0x9609A88EL, 0xE10E9818L,
    0x7F6A0DBBL, 0x086D3D2DL, 0x91646C97L, 0xE6635C01L,
    0x6B6B51F4L, 0x1C6C6162L, 0x856530D8L, 0xF262004EL,
    0x6C0695EDL, 0x1B01A57BL, 0x8208F4C1L, 0xF50FC457L,
    0x65B0D9C6L, 0x12B7E950L, 0x8BBEB8EAL, 0xFCB9887CL,
    0x62DD1DDFL, 0x15DA2D49L, 0x8CD37CF3L, 0xFBD44C65L,
    0x4DB26158L, 0x3AB551CEL, 0xA3BC0074L, 0xD4BB30E2L,
    0x4ADFA541L, 0x3DD895D7L, 0xA4D1C46DL, 0xD3D6F4FBL,
    0x4369E96AL, 0x346ED9FCL, 0xAD678846L, 0xDA60B8D0L,
    0x44042D73L, 0x33031DE5L, 0xAA0A4C5FL, 0xDD0D7CC9L,
    0x5005713CL, 0x270241AAL, 0xBE0B1010L, 0xC90C2086L,
    0x5768B525L, 0x206F85B3L, 0xB966D409L, 0xCE61E49FL,
    0x5EDEF90EL, 0x29D9C998L, 0xB0D09822L, 0xC7D7A8B4L,
    0x59B33D17L, 0x2EB40D81L, 0xB7BD5C3BL, 0xC0BA6CADL,
    0xEDB88320L, 0x9ABFB3B6L, 0x03B6E20CL, 0x74B1D29AL,
    0xEAD54739L, 0x9DD277AFL, 0x04DB2615L, 0x73DC1683L,
    0xE3630B12L, 0x94643B84L, 0x0D6D6A3EL, 0x7A6A5AA8L,
    0xE40ECF0BL, 0x9309FF9DL, 0x0A00AE27L, 0x7D079EB1L,
    0xF00F9344L, 0x8708A3D2L, 0x1E01F268L, 0x6906C2FEL,
    0xF762575DL, 0x806567CBL, 0x196C3671L, 0x6E6B06E7L,
    0xFED41B76L, 0x89D32BE0L, 0x10DA7A5AL, 0x67DD4ACCL,
    0xF9B9DF6FL, 0x8EBEEFF9L, 0x17B7BE43L, 0x60B08ED5L,
    0xD6D6A3E8L, 0xA1D1937EL, 0x38D8C2C4L, 0x4FDFF252L,
    0xD1BB67F1L, 0xA6BC5767L, 0x3FB506DDL, 0x48B2364BL,
    0xD80D2BDAL, 0xAF0A1B4CL, 0x36034AF6L, 0x41047A60L,
    0xDF60EFC3L, 0xA867DF55L, 0x316E8EEFL, 0x4669BE79L,
    0xCB61B38CL, 0xBC66831AL, 0x256FD2A0L, 0x5268E236L,
    0xCC0C7795L, 0xBB0B4703L, 0x220216B9L, 0x5505262FL,
    0xC5BA3BBEL, 0xB2BD0B28L, 0x2BB45A92L, 0x5CB36A04L,
    0xC2D7FFA7L, 0xB5D0CF31L, 0x2CD99E8BL, 0x5BDEAE1DL,
    0x9B64C2B0L, 0xEC63F226L, 0x756AA39CL, 0x026D930AL,
    0x9C0906A9L, 0xEB0E363FL, 0x72076785L, 0x05005713L,
    0x95BF4A82L, 0xE2B87A14L, 0x7BB12BAEL, 0x0CB61B38L,
    0x92D28E9BL, 0xE5D5BE0DL, 0x7CDCEFB7L, 0x0BDBDF21L,
    0x86D3D2D4L, 0xF1D4E242L, 0x68DDB3F8L, 0x1FDA836EL,
    0x81BE16CDL, 0xF6B9265BL, 0x6FB077E1L, 0x18B74777L,
    0x88085AE6L, 0xFF0F6A70L, 0x66063BCAL, 0x11010B5CL,
    0x8F659EFFL, 0xF862AE69L, 0x616BFFD3L, 0x166CCF45L,
    0xA00AE278L, 0xD70DD2EEL, 0x4E048354L, 0x3903B3C2L,
    0xA7672661L, 0xD06016F7L, 0x4969474DL, 0x3E6E77DBL,
    0xAED16A4AL, 0xD9D65ADCL, 0x40DF0B66L, 0x37D83BF0L,
    0xA9BCAE53L, 0xDEBB9EC5L, 0x47B2CF7FL, 0x30B5FFE9L,
    0xBDBDF21CL, 0xCABAC28AL, 0x53B39330L, 0x24B4A3A6L,
    0xBAD03605L, 0xCDD70693L, 0x54DE5729L, 0x23D967BFL,
    0xB3667A2EL, 0xC4614AB8L, 0x5D681B02L, 0x2A6F2B94L,
    0xB40BBE37L, 0xC30C8EA1L, 0x5A05DF1BL, 0x2D02EF8DL
};

/******************************************************************

FUNCTION: CalculateCcitt32

DESCRIPTION:  Calculates the 32-bit CCITT CRC on a block of words.
              The initial value is 0xFFFFFFFF.  The bits are
              reflected in and out.  The final CRC is XOR'd with
              0xFFFFFFFF before it is returned.

ARGS:
        BYTE* DataPtr: A pointer the the first word to CRC
        UINT16 Length: The number of words to CRC.

RETURNS:
    The calculated CRC of the word

******************************************************************/
UINT32 CalculateCcitt32(UINT16* WordAddress, UINT32 ByteOffset, UINT32 NumOfBytes)
{
    UINT32 crc        = 0xFFFFFFFF;
    UINT16 Data;
    UINT32 Address    = ((UINT32)WordAddress) + ByteOffset/2;  // point to the word
    UINT16 ByteSelect = ByteOffset % 2;     // select the high or low byte of the word

    // loop for all the bytes
    while (NumOfBytes)
    {
        // select the correct byte
        switch( ByteSelect )
        {
        // high byte
        case 0:
            // grab the data
            Data       = (*((UINT16*)Address))>>8;
            // the next byte is the low byte
            ByteSelect = 1;
            break;

        // low byte
        case 1:
            // grab the data
            Data       = (*((UINT16*)Address)) & 0xFF;
            // the next byte is the upper byte of the next word
            ByteSelect = 0;
            Address++;
            break;
        }

        crc = CcittCrcTable[(crc ^ Data) & 0xFFL] ^ (crc >> 8);

        NumOfBytes--;
    }

    return crc ^ 0xFFFFFFFF;
}


/******************************************************************

FUNCTION: bsm_AppCRCValue

DESCRIPTION:  Returns the 32-bit unsigned CRC from the end of
                          the application's Flash memory image.

ARGS:
        None.

RETURNS:
    The 32-bit unsigned CRC stored in Flash memory (not calculated)

******************************************************************/

UINT32 bsm_AppCRCValue()
{
    // The CRC is stored at the end of flash
    return ( ((UINT32)StoredCrcH<<16) | ((UINT32)StoredCrcL) );
}