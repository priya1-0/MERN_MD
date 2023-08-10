/************************************************************************
*
* MODULE: bsm_Led.h
*
* OWNER:
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This header file declares all the functions to control the
*              LEDs
*
*************************************************************************/
#ifndef BSM_LED_H
#define BSM_LED_H

/////////////
// Includes
/////////////

#include "../global.h"

//////////
// Types
//////////

// LED Enumeration
typedef enum bst_LedTag
{
    bsc_LEDREADY,
    bsc_LEDLOWBATT,
    bsc_LEDBADANTENNA,
    bsc_LEDPROGRESS1,
    bsc_LEDPROGRESS2,
    bsc_LEDPROGRESS3,
    bsc_LEDPROGRESS4,
    bsc_LEDPROGRESS5,
    bsc_LEDNODIALTONE,
    bsc_LEDDATA1,
    bsc_LEDDATA2,
    bsc_LEDDATA3,
    bsc_LED_CHECKMARK,
    bsc_EXTRA1,
    bsc_EXTRA2,
    bsc_EXTRA3,
    bsc_MAXLEDS
} bst_Led;

typedef enum bst_LedStateTag
{
    bsc_LEDOFF,
    bsc_LEDON,
    bsc_LEDFASTFLASH,
    bsc_LEDSLOWFLASH,
    bsc_LEDSTROBE
} bst_LedState;

/////////////
// Prototypes
/////////////

void bsm_LedInit(void);
void bsm_LDChange( bst_Led Led, bst_LedState OnOff);


#endif
