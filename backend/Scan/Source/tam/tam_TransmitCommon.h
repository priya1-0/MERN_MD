/************************************************************************
*
* MODULE: tam_TransmitCommon.h
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the functions common to Telemetry A to
*              transmit data.
*
*************************************************************************/
#ifndef TAM_TRANSMITCOMMON_H
#define TAM_TRANSMITCOMMON_H


#include "global.h"

/* Function prototypes. */
void TransmitDownlinkBuffer(BYTE* Buffer, UINT16 Length);
void TransmitHandshake(void);
void tam_EndOfHandshakePulseIrq(void);
void DisableMcbsp(void);
void EnableMcbsp(void);
void ConfigureMcbsp(void);
void TransmitShortMessage(BYTE* Buffer, UINT16 Length);

#endif
