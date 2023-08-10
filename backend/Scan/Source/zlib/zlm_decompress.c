/*
***********************************************************************
 2490 In-home Remote Monitor
 Copyright (c) Medtronic, Inc. 2003

 MODULE: Zlib interface for 2490G.

 OWNER: Medtronic

 $Revision$

 $Date$

 $RCSfile$


 DESCRIPTION:

 This is the interface between 2490G application code and the
 Zlib compression code.




 ENDPURPOSE

***********************************************************************
*/


#include "zlm_decompress.h"

#include "nwm_http.h"
#include "fsm_pbfr.h"
#include "bsm_Event.h"
#include "bsm_serialport.h"
#include <stdio.h>
#include "puff.h"

// Exact file size of uncompressed image on disk in
// bytes - this is for 2490G/H/J

#define UNCOMPRESSED_2490G_FW_IMAGE_SIZE ((unsigned long)2031616L)

extern char returnbuffer[];

/*
***********************************************************************

 FUNCTION:

 DESCRIPTION:

    Check size of downloaded main code. .

 FUNCTION PARAMETERS:

    imageSize - size of downloaded main code

 FUNCTION RETURN:

    Returns true if (reduced) size AND flag chars indicate the main code is
    compressed.

   Returns false othewise.

***********************************************************************
*/

bool zlm_IsCompressed(UINT16* flagBase, unsigned long flagOffset, unsigned long size)
{

    char id1 = fsm_PackedBfrUnpackChar((unsigned char*)flagBase, flagOffset++);
    char id2 = fsm_PackedBfrUnpackChar((unsigned char*)flagBase, flagOffset++);

    if ((ZLIB_FLAG_CHAR1 == id1) && (ZLIB_FLAG_CHAR2 == id2) &&
        (size != UNCOMPRESSED_2490G_FW_IMAGE_SIZE))
    {
        return (true);
    }

    return (false);
}


/*
***********************************************************************

 FUNCTION: zlm_UnpackFirmwareImage

 DESCRIPTION:

    Decompresses a GZ file into the NWM buffer.

    NOTE: Wipes out the packed buffer (fsm_pbfr.c) and NWM buffer
    (returnbuffer)

 FUNCTION PARAMETERS:

    "packedData" and "offset" are the base address and byte offset
    of the start of the GZ file in memory.

    "byteLen" is the (byte) size of the GZ file.

 FUNCTION RETURN:

    Returns number of decompressed bytes, or 0 if there was a problem.

***********************************************************************/


unsigned long zlm_UnpackFirmwareImage(UINT16 *packedData, unsigned long byteOffset, unsigned long byteLen)
{
    int           result;
    unsigned long destLen, scratchLen;
    unsigned long ticks;
    static char   statMsg[120];


    // Check that the scratchpad buffer is big enough for
    // the compressed image.

    scratchLen = fsm_PackedBfrByteLength(FSV_FILE);

    snprintf(statMsg, sizeof(statMsg),
             "Scratch buffer size is %ld bytes, compressed image size is %ld bytes",
             scratchLen, byteLen);

    bsm_SDPrint(statMsg);

    if (byteLen > scratchLen)
    {
        bsm_EHLog("Compressed FW image too large for scratchpad buffer.",0);

        return(0);         //  <-- exit early with "error" return value.
    }

    // Move compressed data to scratchpad buffer

    if (!fsm_PackedBfrTransfer(
            (char*)packedData, byteOffset,                                      // Source
            fsm_PackedBfrStartAddress(FSV_FILE), 0L,            // Destination
            byteLen))                                                                           // Length
    {
        bsm_EHLog("Error transferring FW image to scratchpad.",0);
        return(0);         //  <-- exit early with "error" return value.
    }

    // Inflate the compressed data back to the destination buffer

    destLen    = (NWC_HTML_RECEIVE_BUFFER_PART_SIZE * 16) * 2;  // Max destination
    scratchLen = byteLen;


    bsm_SDPrint("Inflating compressed FW image.");
    ticks  = NU_Retrieve_Clock();

    result = puff(returnbuffer, &destLen,  fsm_PackedBfrStartAddress(FSV_FILE), &scratchLen );


    snprintf(statMsg, sizeof(statMsg),
             "Decompress OK: compressed=%ld bytes, final=%ld bytes, ticks=%ld",
             byteLen, destLen, NU_Retrieve_Clock() - ticks);

    if (result != 0)
    {
        bsm_EHLog("Error during decompression.", result);
        return (0L);
    }

    bsm_EHLog(statMsg,0);

    return (destLen);

}



#ifdef UNITTEST_ZLMDECOMPRESS

/*

        The file abcdefg.txt consisted of "ABCDEFG\r\n".

 \abcdefg.txt.gz:

  Addr     0 1  2 3  4 5  6 7  8 9  A B  C D  E F 0 2 4 6 8 A C E
--------  ---- ---- ---- ---- ---- ---- ---- ---- ----------------
00000000  1f8b 0808 33c8 f443 0003 5c61 6263 6465 ....3HtC..\abcde
00000010  6667 2e74 7874 0073 7472 7671 7573 e7e5 fg.txt.strvqusge
00000020  0200 2a3d b0ab 0900 0000                ..*=0+....
*/

char packedCompressed[] = {
    0x1f8b, 0x0808, 0x33c8, 0xf443, 0x0003, 0x5c61, 0x6263, 0x6465,
    0x6667, 0x2e74, 0x7874, 0x0073, 0x7472, 0x7671, 0x7573, 0xe7e5,
    0x0200, 0x2a3d, 0xb0ab, 0x0900, 0x0000};

extern char returnbuffer[];

void UTest_ZlmDecompressed(void)
{
    unsigned long byteLen;

    memcpy(returnbuffer, packedCompressed, sizeof(packedCompressed));

#if 0
    byteLen = zlm_UnpackFirmwareImage(
        returnbuffer, 0L,
        sizeof(packedCompressed)*2);
#endif
    bsm_SDPrint("Completed unit test");

}

#endif
