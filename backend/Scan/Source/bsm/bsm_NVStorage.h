/************************************************************************
*
* MODULE: bsm_NVStorage.h
*
* OWNER:
*
* $Revision: 1.0
*
* $Date$
*
* $RCSfile$
*
* FUNCTIONS:
* --Public--
* bsm_EEWriteBuf()
* bsm_EEReadBuf()
* bsm_EEFlush()
*
* --Private--
* bsm_EEInit()
* bsm_EEnumByteTOnumWord()

* DESCRIPTION: Non-Volatile Storage Module header file
*
*************************************************************************/
#ifndef __NVSTORAGE_H
#define __NVSTORAGE_H

#include "../global.h"
#include "../com_eepromapp.h"

#ifdef DEFINED_HERE
        #define SCOPE
#else
        #define SCOPE extern
#endif


SCOPE BYTE bsv_FLRAM[2*(UINT32)bsc_NVStorage_SIZE]; // byte array for mirrored copy of flash,
// bsc_NVStorage_SIZE is in words, mult by 2 to convert to bytes


#define bsc_NVSTORAGE_MAX_FLUSH (2) //Maximum number of flush attemps per NVStorage block

SCOPE BOOL bsm_EEWriteBuf(unsigned char* buffer, unsigned int Length, unsigned int Addr);
SCOPE BOOL bsm_EEReadBuf(unsigned char* buffer, unsigned int Length, unsigned int Addr);
SCOPE BOOL bsm_EEFlush(void);
SCOPE BOOL bsm_EEInit(void);
SCOPE BOOL bsm_EEFlushAndCheck(UINT32 offset);
SCOPE BOOL bsm_EECheckForBlank(void);
SCOPE void bsm_Reset_Flash_Mirror(void);
SCOPE UINT32 bsm_ReadTotalOnTimeMinutes(void);
SCOPE void bsm_WriteTotalOnTimeMinutes(void);

#undef SCOPE

#endif
