/************************************************************************
*
* MODULE: bsm_SwitchInput.c
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the functions interprete the input
*              switches.
*
*************************************************************************/

/////////////
// Includes
/////////////
#include "global.h"
#include "bsm_SwitchInput.h"
#include <csl_hpi.h>

///////////
// Global
///////////
UINT16* _HPI_GPIODAT = (UINT16*)0xA00A;

#define PrefixRegister _HPI_GPIODAT
#define ToneRegister   _HPI_GPIODAT

#define PREFIX_2_BIT 0x80
#define PREFIX_3_BIT 0x40
#define PREFIX_4_BIT 0x20

#define BURN_IN_BIT 0x02

#define TONE_BIT 0x10



/******************************************************************

FUNCTION: bsm_INInit

DESCRIPTION: This function initializes the hardware for the inputs.

ARGS:
        <none>

RETURNS:
        <none>

******************************************************************/
void bsm_INInit(void)
{
    // Enable the pins for I/O
    HPI_FSET(HGPIOEN, EN7, 1);

    // Set the pins as inputs
    HPI_FSET(HGPIODIR, HD7, 0);
    HPI_FSET(HGPIODIR, HD6, 0);
    HPI_FSET(HGPIODIR, HD5, 0);
    HPI_FSET(HGPIODIR, HD4, 0);
    HPI_FSET(HGPIODIR, HD1, 0);
}

/******************************************************************

FUNCTION: bsm_INReadDial

DESCRIPTION: This function reads the prefix input.

ARGS:
        <none>

RETURNS:
        Returns the position of the prefix switch

******************************************************************/
bst_DialSwitchState bsm_INReadDial(void)
{
    UINT16 Value = HPI_RGET(HGPIODAT);

    if( (Value & PREFIX_4_BIT) == 0 )
    {
        return bsc_DIAL4;
    }
    if( (Value & PREFIX_3_BIT) == 0 )
    {
        return bsc_DIAL3;
    }
    if( (Value & PREFIX_2_BIT) == 0 )
    {
        return bsc_DIAL2;
    }

    return bsc_DIAL1;
}


/******************************************************************

FUNCTION: bsm_INReadTonePulse

DESCRIPTION: This function reads the tone type input.

ARGS:
        <none>

RETURNS:
        Returns the position of the tone switch

******************************************************************/
bst_ToneSwitchState bsm_INReadTonePulse(void)
{
    UINT16 Value;

    Value = HPI_RGET(HGPIODAT);

    if( (Value & TONE_BIT) == 0 )
    {
        return bsc_PULSE;
    }
    else
    {
        return bsc_TONE;
    }
}

/******************************************************************

FUNCTION: bsm_INReadBurnInPin

DESCRIPTION: This function reads the Burn-In Test pin.

ARGS:
        <none>

RETURNS:
        TRUE - BurnInPin is high
        FALSE - BurnInPin is low

******************************************************************/
BOOL bsm_INReadBurnInPin(void)
{
    UINT16 Value;

    Value = HPI_RGET(HGPIODAT);

    if( (Value & BURN_IN_BIT) == 0 )
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}
