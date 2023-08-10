/************************************************************************
*
* MODULE: bsm_serialport.h
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the function declarations for the
*              serial port.
*
*************************************************************************/
#ifndef BSM_SERIALPORT_H
#define BSM_SERIALPORT_H

#include "../global.h"

///////////////
// prototypes
///////////////
void bsm_SDInit(void);
void bsm_SDPrint(char* p);
void bsm_SDWrite_Unlimited(char* p, UINT32 LengthP);
void bsm_SDWrite(char* p, UINT16 LengthP);
int bsm_SDRead(void);
int bsm_SDReadBytes(BYTE* Buffer, UINT16 Length);
void bsm_SDReadLine(char* Buffer, int Size);
BOOL bsm_SDTxCheckMutex(void);

#endif
