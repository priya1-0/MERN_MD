/*
***********************************************************************
 2490 In-home Remote Monitor
 Copyright (c) Medtronic, Inc. 2003

 MODULE: Interface for EEPROM storage.

 OWNER: Medtronic

 $Revision$

 $Date$

 $RCSfile$


 DESCRIPTION:

 These functions allow for easier accessing of the bsm_EERead and
 bsm_EEWrite functions for 16 and 32 bit values.



 ENDPURPOSE

***********************************************************************
*/


#include "types.h"
#include "aim_NVStorage.h"
#include "bsm_NVStorage.h"




UINT32 aim_EEReadUINT32(unsigned int Addr)
{
    unsigned char temp[4];

    // Read 4 "bytes"

    (void)bsm_EEReadBuf(temp, 4, Addr);

    // Convert from "bytes" to complete unsigned 32 bit long

    return ( ((UINT32)(temp[0] & 0x00FF) << 24) |
             ((UINT32)(temp[1] & 0x00FF) << 16) |
             ((UINT32)(temp[2] & 0x00FF) <<  8) |
             ((UINT32)(temp[3] & 0x00FF) <<  0));
}






UINT16 aim_EEReadUINT16(unsigned int Addr)
{
    unsigned char temp[2];

    // Read 2 "bytes"
    (void)bsm_EEReadBuf(temp, 2, Addr);

    // Convert from "bytes" to complete unsigned 16 bit long
    return ( ((UINT16)(temp[0] & 0x00FF) <<  8) |
             ((UINT16)(temp[1] & 0x00FF) <<  0));
}






void  aim_EEWriteUINT32(UINT32 ulongValue, unsigned int Addr)
{
    unsigned char temp[4];

    temp[0] = (ulongValue >> 24) & 0x00FF;
    temp[1] = (ulongValue >> 16) & 0x00FF;
    temp[2] = (ulongValue >>  8) & 0x00FF;
    temp[3] = (ulongValue >>  0) & 0x00FF;

    (void)bsm_EEWriteBuf((BYTE*)temp, 4, Addr); // Write it.
}




void  aim_EEWriteUINT16(UINT16 uintValue, unsigned int Addr)
{
    unsigned char temp[2];

    temp[0] = (uintValue >>  8) & 0x00FF;
    temp[1] = (uintValue >>  0) & 0x00FF;

    (void)bsm_EEWriteBuf((BYTE*)temp, 2, Addr); // Write it.
}




