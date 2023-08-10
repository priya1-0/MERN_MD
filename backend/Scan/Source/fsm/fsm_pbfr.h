/*
************************************************************************
 2490 In-home Remote Monitor
 Copyright (c) Medtronic, Inc. 2004

 MODULE: Packed-byte Simulated File System.

 OWNER: Medtronic

 $Revision$

 $Date$

 $RCSfile$

 DESCRIPTION:

        This module contains the interfaces for byte buffers in the 2490G.
        The Texas Instruments' DSP's minimum addressable data unit ("MADU")
        is 16 bits.  This module supports buffers of MADUs in which 2
        8-bit bytes are packed in each 16-bit unit.


 ENDPURPOSE

************************************************************************
*/


#ifndef fsm_pbfr_h
#define fsm_pbfr_h


#include "types.h"

/*
************************************************************************

        Definitions

************************************************************************
*/


// Define the buffer index type. This valus is always the next
// writing position.

typedef long fst_PackedBfrIndex;

// Define the buffer index count
typedef long fst_PackedBfrCount;


// There is currently only one buffer defined to replace the fsm
// "file" component in the 2490G. However, additional packed buffers
// can be used.	The enumerated value is used in calls to differentiate
// which buffer you are accessing.

typedef enum {

    FSV_FILE = 0,

    NUMBER_OF_PACKED_BUFFER_IDS

} fst_PackedBfrIdEnum;


/*
************************************************************************

        Functions

************************************************************************
*/


/*
***********************************************************************

 FUNCTION:   fsm_PackedBfrInit

 DESCRIPTION:

        This function initializes a particular packed buffer.  The buffer's
        read/write index is set to 0.

 FUNCTION PARAMETERS:

        fst_PackedBfrIdEnum bfrId - Buffer to initialize.

 FUNCTION RETURN:

   None.

***********************************************************************
*/

void fsm_PackedBfrInit(fst_PackedBfrIdEnum bfrId);



/*
***********************************************************************

 FUNCTION: fsm_PackedBfrsInitAll

 DESCRIPTION:

        Initializes all buffers in system.

 FUNCTION PARAMETERS:

        int clear - if non-zero, files are written with a debug pattern
                                during initialization.

 FUNCTION RETURN:

   None.

***********************************************************************
*/

void fsm_PackedBfrsInitAll(int clear);


/*
***********************************************************************

 FUNCTION: fsm_PackedBfrWrite

 DESCRIPTION:

        Write a single byte to the buffer.

 FUNCTION PARAMETERS:

        fst_PackedBfrIdEnum id - which buffer.
        char byte - the data.

 FUNCTION RETURN:

   None.

***********************************************************************
*/

void fsm_PackedBfrWrite(fst_PackedBfrIdEnum id, char byte);


/*
***********************************************************************

 FUNCTION: fsm_PackedBfrWriteAt

 DESCRIPTION:

        Write a single byte to the buffer at a specific byte location. The
        buffer's byte index is at the new location + 1 upon exit.

 FUNCTION PARAMETERS:

        fst_PackedBfrIdEnum id - which buffer.
        fst_PackedBfrIndex index - where to put the byte.
        char byte - the data.

 FUNCTION RETURN:

   None.

***********************************************************************
*/

void fsm_PackedBfrWriteAt(fst_PackedBfrIdEnum id,
                          fst_PackedBfrIndex  index,
                          char                byte);



/*
***********************************************************************

 FUNCTION: fsm_PackedBfrWriteMultiple

 DESCRIPTION:

        Write a sequence of bytes to the buffer.

 FUNCTION PARAMETERS:

        fst_PackedBfrIdEnum id - which buffer.
        char *chArray - pointer to 16-bit chars in which the byte data
                                        is in the lower 8 bits.
        fst_PackedBfrCount count - number of bytes to write.

 FUNCTION RETURN:

   None.

***********************************************************************
*/

void fsm_PackedBfrWriteMultiple(fst_PackedBfrIdEnum id,
                                char                *chArray,
                                fst_PackedBfrCount  count);


/*
***********************************************************************

 FUNCTION: fsm_PackedBfrWriteMultipleAt

 DESCRIPTION:

        Write a sequence of bytes to the buffer at a specific byte location.
        The buffer's byte index is at the new location + count upon exit.

 FUNCTION PARAMETERS:

        fst_PackedBfrIdEnum id - which buffer.
        fst_PackedBfrIndex index - where to start putting the bytes.
        char *chArray - pointer to 16-bit chars in which the byte data
                                        is in the lower 8 bits.
        fst_PackedBfrCount count - number of bytes to write.

 FUNCTION RETURN:

   None.

***********************************************************************
*/


void fsm_PackedBfrWriteMultipleAt(fst_PackedBfrIdEnum id,
                                  fst_PackedBfrIndex  index,
                                  char                *chArray,
                                  fst_PackedBfrCount  count);

/*
***********************************************************************

 FUNCTION: fsm_PackedBfrRead

 FUNCTION: fsm_PackedBfrWrite

 DESCRIPTION:

        Inverse operation of fsm_PackedBfrWrite - reads a single byte from the
        buffer.

 FUNCTION PARAMETERS:

        fst_PackedBfrIdEnum id - which buffer.


 FUNCTION RETURN:

        char - the data.

***********************************************************************
*/

char fsm_PackedBfrRead(fst_PackedBfrIdEnum id);



/*
***********************************************************************

 FUNCTION: fsm_PackedBfrReadAt

 DESCRIPTION:

        Reads a single byte from the buffer at a specific byte location.
        The buffer's byte index is at the new location + 1 upon exit.

 FUNCTION PARAMETERS:

        fst_PackedBfrIdEnum id - which buffer.
        fst_PackedBfrIndex index - where to get the byte.

 FUNCTION RETURN:

        char - the data.

***********************************************************************
*/
char fsm_PackedBfrReadAt(fst_PackedBfrIdEnum id, fst_PackedBfrIndex index);


/*
***********************************************************************

 FUNCTION: fsm_PackedBfrReadMultiple

 DESCRIPTION:

        Read a sequence of bytes from the buffer.

 FUNCTION PARAMETERS:

        fst_PackedBfrIdEnum id - which buffer.
        char *chArray - pointer to 16-bit char array from the data read.
        fst_PackedBfrCount count - number of bytes to read.

 FUNCTION RETURN:

   None.

***********************************************************************
*/

void fsm_PackedBfrReadMultiple(fst_PackedBfrIdEnum id,
                               char                *chArray,
                               fst_PackedBfrCount  count );


/*
***********************************************************************

 FUNCTION: fsm_PackedBfrReadMultipleAt

 DESCRIPTION:

        Read a sequence of bytes to the buffer at a specific byte location.
        The buffer's byte index is at the new location + count upon exit.

 FUNCTION PARAMETERS:

        fst_PackedBfrIdEnum id - which buffer.
        fst_PackedBfrIndex index - where to start getting the bytes.
        char *chArray - pointer to 16-bit char array from the data read.
        fst_PackedBfrCount count - number of bytes to read.

 FUNCTION RETURN:

   None.

***********************************************************************
*/

void fsm_PackedBfrReadMultipleAt(fst_PackedBfrIdEnum id,
                                 fst_PackedBfrIndex  index,
                                 char                *chArray,
                                 fst_PackedBfrCount  count);



/*
***********************************************************************

 FUNCTION: fsm_PackedBfrSetIndex

 DESCRIPTION:

        Sets the internal byte index for the buffer to the passed value.

 FUNCTION PARAMETERS:

        fst_PackedBfrIdEnum id - which buffer.
        fst_PackedBfrIndex newIndex - new byte index value.

 FUNCTION RETURN:

   None.

***********************************************************************
*/

void fsm_PackedBfrSetIndex(fst_PackedBfrIdEnum id, fst_PackedBfrIndex newIndex);

/*
***********************************************************************

 FUNCTION: fsm_PackedBfrGetIndex

 DESCRIPTION:

        Gets the internal byte index for the buffer to the passed value.

 FUNCTION PARAMETERS:

        fst_PackedBfrIdEnum id - which buffer.

 FUNCTION RETURN:

   Current byte index value.

***********************************************************************
*/

fst_PackedBfrIndex fsm_PackedBfrGetIndex(fst_PackedBfrIdEnum id);


/*
***********************************************************************

 FUNCTION: fsm_PackedBfrTransferData

 DESCRIPTION:

        The original 2490D code used memcpy() for move data withing the
        RAM disk buffer. This function simulates the same action.


 FUNCTION PARAMETERS:

        fst_PackedBfrIdEnum id - which buffer.
        fst_PackedBfrIndex destinationIndex - where to move the source data to.
        fst_PackedBfrIndex sourceIndex - where to get the data to transfer.
        fst_PackedBfrCount sizeL - number of bytes to move.


 FUNCTION RETURN:

   None.

***********************************************************************
*/

void fsm_PackedBfrTransferData(fst_PackedBfrIdEnum id,
                               fst_PackedBfrIndex  destinationIndex,
                               fst_PackedBfrIndex  sourceIndex,
                               fst_PackedBfrCount  sizeL);



/*
***********************************************************************

 FUNCTION: fsm_PackedBfrStartAddress

 DESCRIPTION:

        Other software may require the starting address of the blocks that
        make up a given buffer for bulk transfers, etc. The buffers must be
        contiguous in memory in this case.

 FUNCTION PARAMETERS:

        fst_PackedBfrIdEnum bfrId - which buffer.

 FUNCTION RETURN:

   char * - start address of the buffer.

***********************************************************************
*/

char * fsm_PackedBfrStartAddress( fst_PackedBfrIdEnum bfrId );



/*
***********************************************************************

 FUNCTION: fsm_PackedBfrByteLength

 DESCRIPTION:

        Returns the number of bytes that can be stored in the
        defined by the passed buffer ID.

 FUNCTION PARAMETERS:

        fst_PackedBfrIdEnum bfrId - which buffer.

 FUNCTION RETURN:

   Size, in bytes.

***********************************************************************
*/

unsigned long fsm_PackedBfrByteLength( fst_PackedBfrIdEnum bfrId );



/*---------------------------------------------------------------------------*/
/*

Lastly, they were converted to inline functions in order to enforce
passed parameters types.


---------------------------------------------------------------------------*/


/*
***********************************************************************

 FUNCTION: fsm_PackedBfrPackChar

 DESCRIPTION:

        This inline function was derived from TI 55xx compiler macro PACKCHAR
        in TI's rts.src as TRGCIO.H. PACKCHAR was changed since
        the original macro changed the second byte to zero when the first byte
        was written. This version now doesn't alter surrounding bytes when
        one is packed.	It is inlined to avoid calling overhead.

 FUNCTION PARAMETERS:

        unsigned char aByte	 - the 8-bit value to pack.
        unsigned char * arrayStart	- base pointer to 16-bit DSP chars
        unsigned long byteIndex - the byte offset to put the byte into.

 FUNCTION RETURN:

   None.

***********************************************************************
*/


inline void fsm_PackedBfrPackChar(unsigned char aByte, unsigned char * arrayStart, unsigned long byteIndex)
{

    ( (byteIndex % 2) == 0 ) ?
    ( *( (unsigned char *)( (unsigned long)arrayStart + (unsigned long)byteIndex / 2 ) ) =
          ( *( (unsigned char *)( (unsigned long)arrayStart + (unsigned long)byteIndex / 2 ) ) & 0x00ff) | ( (unsigned char)aByte << 8 ) ) :
    ( *( (unsigned char *)( (unsigned long)arrayStart + (unsigned long)byteIndex / 2 ) ) =
          ( *( (unsigned char *)( (unsigned long)arrayStart + (unsigned long)byteIndex / 2 ) ) & 0xff00) | ( (unsigned char)aByte & 0xff ) );

}




/*
***********************************************************************

 FUNCTION: fsm_PackedBfrUnpackChar

 DESCRIPTION:

        This inline function was derived from TI 55xx compiler macro
        UNPACKCHAR in TI's rts.src as TRGCIO.H. It is inlined to avoid
        calling overhead.

 FUNCTION PARAMETERS:

        unsigned char * arrayStart	- base pointer to 16-bit DSP chars
        unsigned long byteIndex - the byte offset to get a byte from.

 FUNCTION RETURN:

   A byte in the lower 8 bits of a 16-bit char.

***********************************************************************
*/


inline unsigned char fsm_PackedBfrUnpackChar(unsigned char * arrayStart, unsigned long byteIndex)
{
    return( (unsigned char) ( ( (*(unsigned char *) ( (unsigned long)arrayStart + (unsigned long)byteIndex / 2 ) ) >> ( ( ( (unsigned long)byteIndex + 1) % 2) * 8) ) & 0xFF ) );
}




bool fsm_PackedBfrTransfer(

    char *SourceBase,       unsigned long sourceByteOffset,

    char *DestinationBase, unsigned long destinationByteOffset,

    unsigned long byteCount);

#endif
