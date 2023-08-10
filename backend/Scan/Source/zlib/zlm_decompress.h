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

#include "types.h"

bool zlm_IsCompressed(UINT16* flagBase, unsigned long flagOffset, unsigned long size);

unsigned long zlm_UnpackFirmwareImage(
    UINT16 *packedData, unsigned long byteOffset, unsigned long byteLen);

void UTest_ZlmDecompressed(void);