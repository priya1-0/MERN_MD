/************************************************************************
*
* MODULE: bsm_General.h
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
* bsm_GeneratePointer()
*
* DESCRIPTION: This file contains general board support functionality
*
*************************************************************************/
#ifndef __BSM_GENERAL_H_
#define __BSM_GENERAL_H_

#define BSM_UNPACK_STRSTR_SIZE (512)

char* bsm_GeneratePointer(char* base, INT32 offset);
BYTE bsm_getByteFromPackedArray(UINT16* basePtr, UINT32 offset);
void bsm_unpackByteArray(char* dest, UINT16* basePtr, UINT32 offset, UINT32 length);
char* bsm_packedStringSearch(char* string1, char* string2);
UINT16 bsm_setModemState(UINT32 newState);
void bsm_CopyCode(UINT32 Source, UINT32 Destination, UINT16 Size);
void bsm_VocalNetworkDebugPRD(void);
void bsm_setNetworkDebugPrint(BOOL desiredState);
void bsm_modemConstantTransmit(void);

#endif


