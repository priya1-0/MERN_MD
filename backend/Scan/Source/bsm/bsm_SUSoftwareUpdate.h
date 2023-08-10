/************************************************************************
*
* MODULE: bsm_SUSoftwareUpdate.h
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
* bsm_SUDoUpdate()
*
* --Private--
*
* DESCRIPTION: Software Update header file
*
*************************************************************************/
#ifndef __bsm_SUSOFTWAREUPDATE_H
#define __bsm_SUSOFTWAREUPDATE_H
#include "../global.h"

#define bsc_CODE_MAX_FLUSH (2) //Maximum number of flush attemps per Code block

BOOL bsm_SUDoUpdate(UINT16* basePtr, UINT32 byteOffset, UINT32 length);

#endif
