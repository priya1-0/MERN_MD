/************************************************************************
*
* MODULE: bsm_CheckHardware.h
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION:
*
* ENDPURPOSE
*************************************************************************/

#ifndef __bsm_CHECKHARDWARE_H
#define __bsm_CHECKHARDWARE_H

/////////////
// Includes
/////////////
#include "../global.h"

////////////
// Defines
////////////

//////////
// Types
//////////

// Testing Driver Data Type Definitions
typedef enum {
    bsc_POST_OK,
    bsc_POST_ROM_FAILED,
    bsc_POST_VOLTS_FAILED,
    bsc_POST_EEPROM_FAILED,
    bsc_POST_RAM_FAILED,
    bsc_POST_MDM_FAILED
} bst_POSTERR;

///////////////
// Prototypes
///////////////

bst_POSTERR bsm_CheckHardware(void);

#endif //__bsm_CHECKHARDWARE_H

