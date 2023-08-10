/************************************************************************
*
* MODULE: dbg_Modem.h
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the functions debug the modem.
*
*************************************************************************/
#ifndef DBG_MODEM_H
#define DBG_MODEM_H

/////////////
// Prototypes
/////////////
void SendAtCommand(char* Command);
void TerminalDataExchange(void);
void IgnoreCarrierLoss(void);
void Read_sRegisters(void);
void Write_sRegisters(char* CommandLineParameters);

#endif
