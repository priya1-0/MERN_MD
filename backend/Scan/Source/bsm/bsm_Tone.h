/************************************************************************
*
* MODULE: bsm_Tone.h
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
*              Audio Tone
*
*************************************************************************/
#ifndef BSM_TONE_H
#define BSM_TONE_H

/////////////
// Includes
/////////////
#include <csl.h>
#include <csl_gpt.h>

#include "../global.h"

//////////
// Types
//////////

typedef enum bst_ToneTypeTag
{
    bsc_TONEHIGH = 2400,
    bsc_TONEMID  = 900,
    bsc_TONELOW  = 261     // Middle C
} bst_ToneType;

typedef enum {
    bsc_FASTBEEP,
    bsc_SLOWBEEP,
    bsc_ONBEEP
} bst_BeepRate;

/////////////
// Prototypes
/////////////

// Public Functions
void bsm_ToneInit(void);
void bsm_TNSound( UINT16       OnTime,
                  UINT16       OffTime,
                  INT32        Duration,
                  bst_ToneType ToneType,
                  bst_BeepRate Rate);
void bsm_TNStop(void);
void bsm_UpdateTone(void);


#endif
