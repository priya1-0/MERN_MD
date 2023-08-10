/************************************************************************
*
* MODULE: bsm_Event.h
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
* bsm_EHAssetLogToBuffer
* bsm_EHBufferToAssetLog
* bsm_EHLogFull()
* bsm_EHResetLogReadPointer()
* bsm_EHReadNextEntry()
* bsm_EHLock()
*
* --Private--
* bsm_EHClearLog()
* bsm_EHInit()
* bsm_EHFlushPrep()
* bsm_EHLogEndOffset()
* bsm_EHSaveCurrLogWrite()
*
* DESCRIPTION: Event Handler header file
*
*************************************************************************/
#ifndef __EVENT_H
#define __EVENT_H

#include "../global.h"

// DEFINES
#define bsm_EHLog(Message, Code) (bsm_EHLogFull(Message, ((UINT16)Code), __LINE__, __FILE__))
#define bsc_EHMAXMESSAGELEN (200)      //Maximum message size for a log entry
#define bsc_EHMAXLOGENTRY   (250)      //Maximum size in bytes of a log entry
#define bsc_EVENTCODE_SIZE  (0x02)             //Number of bytes for the event code

/* Error Codes*/
#define bsc_EHLOCKLOGCODE                  (0x7D02) //TBD 32002 in previous code, //Code logged when we have an EHLock call.
#define bsc_EHPRIMARYFAILED_CODE           (0xFFFF) //Code logged when Primary flash block has failed crc
#define bsc_EHPRIMARYANDBACKUPFAILED_CODE  (0xFFFE) //Code logged when Primary and Backup flash block have failed crc
#define bsc_EHPRIMARYFAILEDBACKUPOK_CODE   (0xFFFD) //Code logged when Primary flash block has failed but Backup block is OK
#define bsc_EHSUFAILEDUNKNOWFLASHTYPE_CODE (0xFFFC) //Code logged when Software Update failes due to unknow flash type
#define bsc_EHSUFAILEDCODETOOLARGE_CODE    (0xFFFB) //Code logged when Software Update failes due passed code being to large
#define bsc_EHSUFAILEDVERIFICATION_CODE    (0xFFFA) //Code logged when Software Update failes due verification failure
#define bsc_EHSUFAILEDBATTERYLOW_CODE      (0xFFF9) //Code logged when Software Update failes due verification failure



//TYPE DECLARATIONS

//FUNCTION DECLARATIONS
UINT32 bsm_EHAssetLogToBuffer(void);
void bsm_EHBufferToAssetLog(UINT32 numOfBytes);
bool bsm_EHLogFull(char * Message, int Code, int LineNum, char * FileName);
void bsm_EHResetLogReadPointer(void);
bool bsm_EHReadNextEntry(char * pMessage, int * pCode, unsigned long * pTime);
void bsm_EHLock(char *errBuf);
void bsm_EHClearLog(void);
void bsm_EHInit(void);
void bsm_EHFlushPrep(void);
void bsm_EHSaveCurrLogWrite(void);

#endif

