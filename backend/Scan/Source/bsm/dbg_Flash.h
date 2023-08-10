/************************************************************************
*
* MODULE: dbg_Flash.h
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the function to debug the flash.
*
*************************************************************************/
#ifndef DBG_FLASH_H
#define DBG_FLASH_H

/////////////
// Prototypes
/////////////
void WriteFlash(char* CommandLineParameters);
void ReadFlash(char* CommandLineParameters);
void CommitChanges(void);
UINT16 PackByte(char *HexData);

#endif
