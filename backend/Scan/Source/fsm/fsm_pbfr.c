/*
***********************************************************************
 2490 In-home Remote Monitor
 Copyright (c) Medtronic, Inc. 2003

 MODULE: Packed-byte Simulated File System.

 OWNER: Medtronic

 $Revision$

 $Date$

 $RCSfile$


 DESCRIPTION:

 The TI DSP does not support the fsm_file() code as written for the H8
 processor and ATI Nucleus OS. The main differences are:

 1) The TI DSP and compiler doesn't support 8-bit chars. It uses 16-bit
    chars.
 2) The TI compiler doesn't support an object greater than 64K words
    (16-bit words) in size.

 We create several large 16-bit word buffers, and pack two 8-bit into
 each word. Each buffer is a "power of 2
 " size to permit quick division
 and multiplication by shifting.




 NOTE:  This code has not been optimized for speed, since the amount of
        data maintained by this module is still relatively small.

        To improve performance, the following suggestions are offered:

         - inlining of the low level functions
         - use memcpy for the word-aligned sections of memory transfers
           in a block





 ENDPURPOSE

***********************************************************************
*/

#include "fsm_pbfr.h"
#include "types.h"
#include "bsm_global.h"
#include <string.h>


/*
************************************************************************

        Definitions

************************************************************************
*/


// Each buffer is 32Kwords - there were some compiler errata regarding
// 64K indices.

#define PB_BUFFER_SIZE_IN_WORDS ((long)32*(long)1024)

#define INVALID_PACKED_BFR_INDEX ((fst_PackedBfrIndex)-1)


//****************************************************************************
// This is where we map the large word buffers to externally defined SECTIONs
//****************************************************************************

// Define the "fsv.file" SECTION blocks.

#pragma DATA_SECTION(fb0,"RamDiskBlock0");
UINT16 fb0[PB_BUFFER_SIZE_IN_WORDS]; // 32K words, 64 K bytes

#pragma DATA_SECTION(fb1,"RamDiskBlock1");
UINT16 fb1[PB_BUFFER_SIZE_IN_WORDS];

#pragma DATA_SECTION(fb2,"RamDiskBlock2");
UINT16 fb2[PB_BUFFER_SIZE_IN_WORDS]; // 32K words, 64 K bytes

#pragma DATA_SECTION(fb3,"RamDiskBlock3");
UINT16 fb3[PB_BUFFER_SIZE_IN_WORDS];

#pragma DATA_SECTION(fb4,"RamDiskBlock4");
UINT16 fb4[PB_BUFFER_SIZE_IN_WORDS];

#pragma DATA_SECTION(fb5,"RamDiskBlock5");
UINT16 fb5[PB_BUFFER_SIZE_IN_WORDS];

UINT16 *fsv_FileBlocks[] = {fb0, fb1, fb2, fb3, fb4, fb5 };


#define NUMBER_OF_FSV_FILE_PB_BLOCKS (sizeof(fsv_FileBlocks)/sizeof(UINT16*))


// This structure is used to collect the information related to
// each buffer entity.

typedef struct {

    int numberOf32KWBlocks;
    UINT16 **pbfrList;
    long maxSizeInBytes;
    long volatile byteIndex;

} PBFR_DEF;


// This is an array of PBFR_DEFs, indexable by a fst_PackedBfrIdEnum

static PBFR_DEF pBfrDefs[NUMBER_OF_PACKED_BUFFER_IDS] = {

    // For the "fsv.file" system in the H8 code
    {
        NUMBER_OF_FSV_FILE_PB_BLOCKS,

        fsv_FileBlocks,

        PB_BUFFER_SIZE_IN_WORDS * (long)NUMBER_OF_FSV_FILE_PB_BLOCKS * 2,

        INVALID_PACKED_BFR_INDEX
    }

};




/*
************************************************************************

        Local Functions

************************************************************************
*/


/*
***********************************************************************

 FUNCTION:  _pb_setIndex

 DESCRIPTION:

        Low level index setting - assumes buffer ID and byte location is
        valid.

 FUNCTION PARAMETERS:

        fst_PackedBfrIdEnum bfrId - which buffer
        fst_PackedBfrIndex newIndex - byte index.

 FUNCTION RETURN:

   None.

***********************************************************************
*/

//

static void _pb_setIndex(fst_PackedBfrIdEnum bfrId, fst_PackedBfrIndex newIndex)
{
    pBfrDefs[bfrId].byteIndex = newIndex;
}


/*
***********************************************************************

 FUNCTION:  _pb_read

 DESCRIPTION:

        Low level read function - assumes buffer ID and byte location are
        valid.

 FUNCTION PARAMETERS:

        fst_PackedBfrIdEnum bfrId - ID of the packed buffer

 FUNCTION RETURN:

   .

***********************************************************************
*/

static _pb_read(fst_PackedBfrIdEnum bfrId)
{
    char byteRead = fsm_PackedBfrUnpackChar((unsigned char *) *(pBfrDefs[bfrId].pbfrList), (unsigned long) pBfrDefs[bfrId].byteIndex);

    pBfrDefs[bfrId].byteIndex++; // Increment byte position
    return(byteRead);
}



/*
***********************************************************************

 FUNCTION: _pb_write

 DESCRIPTION:

        Low level write function - assumes buffer ID and byte location are
        valid.

 FUNCTION PARAMETERS:

        fst_PackedBfrIdEnum bfrId - ID of the packed buffer
        char aByte - data to write.

 FUNCTION RETURN:

   None.

***********************************************************************
*/


static _pb_write(fst_PackedBfrIdEnum bfrId, char aByte)
{
    fsm_PackedBfrPackChar((unsigned char) aByte, (unsigned char *) *(pBfrDefs[bfrId].pbfrList), (unsigned long) pBfrDefs[bfrId].byteIndex);
    pBfrDefs[bfrId].byteIndex++; // Increment byte position
}


/*
***********************************************************************

 FUNCTION:  _pb_verifyParams

 DESCRIPTION:

        Parameter verification of index ranges, buffer ids, sizes/limits.
    If parameters are invalid, the system shuts down via bsm_EHLock().

 FUNCTION PARAMETERS:

    fst_PackedBfrIdEnum bfrId - which buffer (not block)
    fst_PackedBfrIndex index  - a new index for a WriteAt or ReadAt.
                    Set to -1 to use current byteIndex
    fst_PackedBfrCount count  - the count for WriteMultiple/ReadMultiple.
                    Always > 0


 FUNCTION RETURN:

   None.

***********************************************************************
*/

static void _pb_verifyParams(fst_PackedBfrIdEnum bfrId, fst_PackedBfrIndex index,
                             fst_PackedBfrCount count)
{
    fst_PackedBfrIndex expectedStart;
    PBFR_DEF           * thisBuffer;

    // Check the ID passed in

    if ((bfrId < 0 ) || (bfrId >= NUMBER_OF_PACKED_BUFFER_IDS))
        bsm_EHLock("_pb_verifyParams: bad buffer id.");

    thisBuffer =  &pBfrDefs[bfrId];     // Get pointer to buffer info

    // Check start index

    expectedStart = (index == -1) ? thisBuffer->byteIndex : index;

    if (expectedStart >= thisBuffer->maxSizeInBytes)
        bsm_EHLock("_pb_verifyParams: starting index past end.");

    // Check start + count
    if ((expectedStart + count) > thisBuffer->maxSizeInBytes)
        bsm_EHLock("_pb_verifyParams: data access will exceed buffer size.");

    // Check count >= 0

    if (count < 0)
        bsm_EHLock("_pb_verifyParams: count < 0.");

    if (expectedStart < 0)
        bsm_EHLock("_pb_verifyParams: byte index < 0");
}



/*
***********************************************************************

 FUNCTION: fsm_PackedBfrInit

 DESCRIPTION:

        See fsm_pbfr.h.

***********************************************************************
*/

void fsm_PackedBfrInit(fst_PackedBfrIdEnum bfrId)
{

    unsigned long start, end;
    int           x;

    // Check the ID passed in.
    if ((bfrId < 0 ) || (bfrId >= NUMBER_OF_PACKED_BUFFER_IDS))
        bsm_EHLock("fsm_PackedBfrInit - bad buffer id"); // no return

    // check if the packed buffer blocks are contiguous in memory

    for (x = 0; x < pBfrDefs[bfrId].numberOf32KWBlocks-2; x++)
    {
        start = (unsigned long)pBfrDefs[bfrId].pbfrList[x];
        end   = (unsigned long)pBfrDefs[bfrId].pbfrList[x+1];

        if ((start + (unsigned long)PB_BUFFER_SIZE_IN_WORDS) != end)
            bsm_EHLock("fsm_PackedBfrInit - non-contiguous packed buffer blocks");             // no return
    }

    // Set byte offset to 0
    pBfrDefs[bfrId].byteIndex = 0;

}



/*
***********************************************************************

 FUNCTION: fsm_PackedBfrsInitAll

 DESCRIPTION:

        See fsm_pbfr.h.

***********************************************************************
*/

void fsm_PackedBfrsInitAll(int clear)
{
    int  bufferId;
    int  block;
    char clearWord = 0x9999; // helps in debugging

    // Set all the byte offsets to 0
    for (bufferId = 0; bufferId < (int)NUMBER_OF_PACKED_BUFFER_IDS; bufferId++)
    {
        fsm_PackedBfrInit((fst_PackedBfrIdEnum)bufferId);

        // Possibly init all blocks;

        if (0 != clear)
        {
            for (block = 0; block < pBfrDefs[bufferId].numberOf32KWBlocks; block++)
            {
                memset(pBfrDefs[bufferId].pbfrList[block], clearWord, PB_BUFFER_SIZE_IN_WORDS);
            }
        }

    }
}



/*
***********************************************************************

 FUNCTION: fsm_PackedBfrRead

 DESCRIPTION:

        See fsm_pbfr.h.

***********************************************************************
*/

char fsm_PackedBfrRead(fst_PackedBfrIdEnum bfrId)
{
    _pb_verifyParams(bfrId, -1, 1);             // Validate the parameters

    return(_pb_read( bfrId) );
}



/*
***********************************************************************

 FUNCTION: fsm_PackedBfrReadAt

 DESCRIPTION:

        See fsm_pbfr.h.

***********************************************************************
*/

char fsm_PackedBfrReadAt(fst_PackedBfrIdEnum bfrId, fst_PackedBfrIndex newIndex)
{
    if (newIndex < 0)
    {
        bsm_EHLock("fsm_PackedBfrReadAt: Negative value for index");
    }

    _pb_verifyParams(bfrId, newIndex, 1);

    _pb_setIndex(bfrId,newIndex);

    return(_pb_read(bfrId));
}


/*
***********************************************************************

 FUNCTION: fsm_PackedBfrReadMultiple

 DESCRIPTION:

        See fsm_pbfr.h.

***********************************************************************
*/

void fsm_PackedBfrReadMultiple(fst_PackedBfrIdEnum bfrId, char* chArray, fst_PackedBfrCount count)
{
    _pb_verifyParams(bfrId, -1, count);

    while(count--)
        *chArray++ = _pb_read(bfrId);
}


/*
***********************************************************************

 FUNCTION: fsm_PackedBfrReadMultipleAt

 DESCRIPTION:

        See fsm_pbfr.h.

***********************************************************************
*/

void fsm_PackedBfrReadMultipleAt(fst_PackedBfrIdEnum bfrId, fst_PackedBfrIndex index,
                                 char* chArray, fst_PackedBfrCount count)
{

    if (index < 0)
    {
        bsm_EHLock("fsm_PackedBfrReadMultipleAt: Negative value for index");
    }

    _pb_verifyParams(bfrId, index, count);
    _pb_setIndex(bfrId,index);

    while(count--)
    {
        *chArray++ = _pb_read(bfrId);
    }
}


/*
***********************************************************************

 FUNCTION: fsm_PackedBfrWrite

 DESCRIPTION:

        See fsm_pbfr.h.

***********************************************************************
*/

void fsm_PackedBfrWrite(fst_PackedBfrIdEnum bfrId, char byte)
{
    _pb_verifyParams(bfrId, -1, 1);             // Validate the parameters
    _pb_write(bfrId, byte);
}


/*
***********************************************************************

 FUNCTION: fsm_PackedBfrWriteAt

 DESCRIPTION:

        See fsm_pbfr.h.

***********************************************************************
*/

void fsm_PackedBfrWriteAt(fst_PackedBfrIdEnum bfrId, fst_PackedBfrIndex index, char byte)
{

    if (index < 0)
    {
        bsm_EHLock("fsm_PackedBfrWriteAt: Negative value for index");
    }

    _pb_verifyParams(bfrId, index, 1);

    _pb_setIndex(bfrId,index);

    _pb_write(bfrId, byte);
}


/*
***********************************************************************

 FUNCTION: fsm_PackedBfrWriteMultiple

 DESCRIPTION:

        See fsm_pbfr.h.

***********************************************************************
*/
void fsm_PackedBfrWriteMultiple(fst_PackedBfrIdEnum bfrId, char* chArray, fst_PackedBfrCount count)
{
    _pb_verifyParams(bfrId, -1, count);

    while(count--)
    {
        _pb_write(bfrId, *chArray++);
    }
}



/*
***********************************************************************

 FUNCTION: fsm_PackedBfrWriteMultipleAt

 DESCRIPTION:

        See fsm_pbfr.h.

***********************************************************************
*/

void fsm_PackedBfrWriteMultipleAt(fst_PackedBfrIdEnum bfrId, fst_PackedBfrIndex index,
                                  char* chArray, fst_PackedBfrCount count)
{

    if (index < 0)
    {
        bsm_EHLock("fsm_PackedBfrWriteMultipleAt: Negative value for index");
    }

    _pb_verifyParams(bfrId, index, count);

    _pb_setIndex(bfrId,index);

    while(count--)
    {
        _pb_write(bfrId, *chArray++);
    }

}




/*
***********************************************************************

 FUNCTION: fsm_PackedBfrGetIndex

 DESCRIPTION:

        See fsm_pbfr.h.

***********************************************************************
*/


fst_PackedBfrIndex fsm_PackedBfrGetIndex(fst_PackedBfrIdEnum bfrId)
{
    // Check the ID passed in.
    if ((bfrId < 0 ) || (bfrId >= NUMBER_OF_PACKED_BUFFER_IDS))
        bsm_EHLock("fsm_PackedBfrGetIndex - bad buffer id"); // no return

    return(pBfrDefs[bfrId].byteIndex);
}



/*
***********************************************************************

 FUNCTION: fsm_PackedBfrSetIndex

 DESCRIPTION:

        See fsm_pbfr.h.

***********************************************************************
*/

void fsm_PackedBfrSetIndex(fst_PackedBfrIdEnum bfrId, fst_PackedBfrIndex newIndex)
{
    if (newIndex < 0)
    {
        bsm_EHLock("fsm_PackedBfrSetIndex: Negative value for index");
    }
    _pb_verifyParams(bfrId, newIndex, 1);
    _pb_setIndex(bfrId, newIndex);

}



/*
***********************************************************************

 FUNCTION: fsm_PackedBfrTransferData

 DESCRIPTION:

        See fsm_pbfr.h.

***********************************************************************
*/

void fsm_PackedBfrTransferData(fst_PackedBfrIdEnum bfrId, fst_PackedBfrIndex destinationIndex,
                               fst_PackedBfrIndex sourceIndex, fst_PackedBfrCount sizeL)
{

    char aByte;

    PBFR_DEF* bufferInfo;

    if ((destinationIndex < 0) || (sourceIndex < 0))
    {
        bsm_EHLock("fsm_PackedBfrTransferData: Negative value for index");
    }

    if (destinationIndex == sourceIndex) // Dest == source - we're done
        return;

    // Verify the parameters

    _pb_verifyParams(bfrId, destinationIndex, sizeL);
    _pb_verifyParams(bfrId, sourceIndex, sizeL);

    // Just use existing functions to transfer. If not fast enough, then optimize
    // The ranges may overlap - the original 2490 code didn't worry about this.

    while (sizeL--)
    {
        _pb_setIndex(bfrId,sourceIndex++);
        aByte = _pb_read(bfrId);

        _pb_setIndex(bfrId,destinationIndex++);
        _pb_write(bfrId,aByte);
    }
}


/*
***********************************************************************

 FUNCTION: fsm_PackedBfrStartAddress

 DESCRIPTION:

        See fsm_pbfr.h.

***********************************************************************
*/

char * fsm_PackedBfrStartAddress( fst_PackedBfrIdEnum bfrId )
{
    // Check the ID passed in

    if ((bfrId < 0 ) || (bfrId >= NUMBER_OF_PACKED_BUFFER_IDS))
        bsm_EHLock("fsm_PackedBfrStartAddress: bad buffer id.");

    return((char*) pBfrDefs[bfrId].pbfrList[0]);
}




/*
***********************************************************************

 FUNCTION: fsm_PackedBfrStartAddress

 DESCRIPTION:

        See fsm_pbfr.h.

***********************************************************************
*/

unsigned long fsm_PackedBfrByteLength( fst_PackedBfrIdEnum bfrId )
{
    // Check the ID passed in

    if ((bfrId < 0 ) || (bfrId >= NUMBER_OF_PACKED_BUFFER_IDS))
        bsm_EHLock("fsm_PackedBfrByteLength: bad buffer id.");

    return((unsigned long) pBfrDefs[bfrId].maxSizeInBytes);
}





bool fsm_PackedBfrTransfer(

    char *SourceBase,       unsigned long sourceByteOffset,

    char *DestBase, unsigned long destinationByteOffset,

    unsigned long byteCount)

{
    //Non-optimized packed buffer transfers
    while (byteCount)
    {
        fsm_PackedBfrPackChar(
            fsm_PackedBfrUnpackChar(SourceBase, sourceByteOffset++),
            DestBase,
            destinationByteOffset++);

        byteCount--;
    }

    return(true);     // No parameter checking was done
}





#ifdef UNIT_TEST_FSM_PBFR

void UTestFsmPbfr(void)
{
    static char b[1024];
    char        bufNum = '0';
    int         x;

    fsm_PackedBfrInit(FSV_FILE);

    while(bufNum < '8')
    {
        memset(b, bufNum, sizeof(b));
        for (x = 0; x < 64; x++)
            fsm_PackedBfrWriteMultiple(FSV_FILE, b, sizeof(b));
        bufNum++;
    }

    bsm_EHLog("End of fill", 0);

    // Try one more to get error
    fsm_PackedBfrWrite(FSV_FILE, 0x88);

}

#endif