/************************************************************************
*
* MODULE: bsm_SwitchInput.h
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the functions to read the input
*              switches
*
*************************************************************************/
#ifndef BSM_SWITCHINPUT_H
#define BSM_SWITCHINPUT_H

/////////////
// Includes
/////////////
#include "../global.h"

//////////
// Types
//////////
typedef enum {
    bsc_DIAL1,
    bsc_DIAL2,
    bsc_DIAL3,
    bsc_DIAL4
} bst_DialSwitchState;

typedef enum {
    bsc_TONE,
    bsc_PULSE
} bst_ToneSwitchState;

/////////////
// Prototypes
/////////////
void bsm_INInit(void);
bst_DialSwitchState bsm_INReadDial(void);
bst_ToneSwitchState bsm_INReadTonePulse(void);
BOOL bsm_INReadBurnInPin(void);

#endif

