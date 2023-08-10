/************************************************************************
*
* MODULE: bsm_Power.h
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
*              Power Button and Shutdown.
*
*************************************************************************/

#ifndef BSM_POWER_H
#define BSM_POWER_H

/////////////
// Includes
/////////////

#include <csl.h>
#include <csl_gpio.h>

#include "../global.h"

///////////////
// Prototypes
///////////////
void bsm_PowerInit(void);
BOOL bsm_IsBatteryGood(void);
BOOL bsm_isPowerStateGoodHold(void);
void bsm_EnableDummyLoad(void);
void bsm_DisableDummyLoad(void);
void bsm_PMDisableButton(void);
void bsm_PMEnableButton(void);
void bsm_PMShutDown(void);
void bsm_PMShutDownFlashCorrupt(bool flush);
void bsm_PMPowerButtonShutdownSWI(void);
void bsm_PMDisableSWI(void);
void bsm_PMEnableSWI(void);

#endif
