/************************************************************************
*
* MODULE: bsm_Tone.c
*
* OWNER:
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file defines all the functions to control the
*              Audio Tones.
*
*************************************************************************/

/////////////
// Includes
/////////////
#include <csl.h>

#ifdef  _INLINE
#undef  _INLINE
#endif
#define _INLINE

#include <csl_gpt.h>

#include <csl_chip.h>

#include "global.h"
#include "bsm_tone.h"

////////////
// Defines
////////////
#define PERIODIC_TIME_MS 10

//////////
// Types
//////////
typedef enum bst_ToneStateTag
{
    bsc_TONE_ON,
    bsc_TONE_OFF,
    bsc_DEAD_TIME
} bst_ToneState;

typedef struct bst_ToneStructTag
{
    INT16 OnTime;
    INT16 OffTime;
    UINT16 NumberOfTones;
    UINT16 ReloadNumberOfTones;
    INT16 ReloadOnTime;
    INT16 ReloadOffTime;
    INT16 DeadTime;
    INT16 ReloadDeadTime;
    INT32 Duration;
    bst_ToneState State;
} bst_ToneStruct;

////////////
// Globals
////////////
static bst_ToneStruct Tone;
static GPT_Handle     hGpt;

///////////////
// Prototypes
///////////////
static void TwiddleHardware(void);



/******************************************************************

FUNCTION: bsm_ToneInit

DESCRIPTION:  This function initializes the tone generator

ARGS:
        <none>

RETURNS:
    <none>

******************************************************************/
void bsm_ToneInit(void)
{
    hGpt                     = GPT_open(GPT_DEV1, GPT_OPEN_RESET);

    Tone.OnTime              = 0;
    Tone.OffTime             = 0;
    Tone.NumberOfTones       = 0;
    Tone.ReloadNumberOfTones = 0;
    Tone.ReloadOnTime        = 0;
    Tone.ReloadOffTime       = 0;
    Tone.DeadTime            = 0;
    Tone.ReloadDeadTime      = 0;
    Tone.Duration            = 0;
    Tone.State               = bsc_TONE_OFF;
}


/******************************************************************

FUNCTION: bsm_TNSound

DESCRIPTION:  This function set the Tone to play a series of beeps.

ARGS:
        UINT16 OnTime: The number of 10ms ticks the tone plays
        UINT16 OffTime: The number of 10ms ticks the tone is off
        INT32 Duration: The total length of time the tones should play
        bst_ToneType ToneType: The type of the tone.
        bst_BeepRate Rate: Fast (200ms on, 1000ms off),
                           Slow (500ms on, 500ms off), or
                           On (always on)

RETURNS:
    <none>

******************************************************************/
void bsm_TNSound( UINT16       OnTime,
                  UINT16       OffTime,
                  INT32        Duration,
                  bst_ToneType ToneType,
                  bst_BeepRate Rate)
{
    ioport UINT16 *GPTCNT1_0 = (UINT16*)0x2408;
    ioport UINT16 *GPTCNT2_0 = (UINT16*)0x2409;
    ioport UINT16 *GPTCNT3_0 = (UINT16*)0x240A;
    ioport UINT16 *GPTCNT4_0 = (UINT16*)0x240B;

    UINT32 rollover          = ((CPU_FREQ/FAST_PERIPH_CLK_DIV)/ToneType)/2;

    DISABLE_INTERRUPTS;

    // Stop the timer
    GPT_RSET(GPTCTL11, 0);

    // reset the count to 0
    *GPTCNT1_0 = 0;
    *GPTCNT2_0 = 0;
    *GPTCNT3_0 = 0;
    *GPTCNT4_0 = 0;

    // Initialize the timer to rollover at twice the frequency
    GPT_init64(
        hGpt,                                                   // Device Handle; see GPT_open
        0x0000,                                                 // Global timer control(not used)
        0x008c,                                                 // timer1 control value
        rollover>>16,                                   // MSB of timer period value
        rollover&0xffff                             // LSB of timer period value
        );

    // In the TSSR, set the Timer 1 output to be used.
    CHIP_FSET(TSSR, TIM1MODE, 1);

    switch(Rate)
    {
    default:
    case bsc_FASTBEEP:
        Tone.OnTime              = 200;
        Tone.OffTime             = 1000;
        Tone.ReloadOnTime        = 200;
        Tone.ReloadOffTime       = 1000;
        Tone.NumberOfTones       = (OnTime+119)/120;
        Tone.ReloadNumberOfTones = (OnTime+119)/120;
        break;

    case bsc_SLOWBEEP:
        Tone.OnTime              = 250;
        Tone.OffTime             = 250;
        Tone.ReloadOnTime        = 250;
        Tone.ReloadOffTime       = 250;
        Tone.NumberOfTones       = (OnTime+49)/50;
        Tone.ReloadNumberOfTones = (OnTime+49)/50;
        break;

    case bsc_ONBEEP:
        Tone.OnTime              = OnTime*10;
        Tone.OffTime             = 0;
        Tone.ReloadOnTime        = OnTime*10;
        Tone.ReloadOffTime       = 0;
        Tone.NumberOfTones       = 1;
        Tone.ReloadNumberOfTones = 1;
        break;
    }

    Tone.DeadTime       = OffTime*10;
    Tone.ReloadDeadTime = OffTime*10;
    Tone.Duration       = Duration*10L;
    Tone.State          = bsc_TONE_ON;

    // start the timer
    GPT_start(hGpt);

    ENABLE_INTERRUPTS;
}

/******************************************************************

FUNCTION: bsm_TNStop

DESCRIPTION:  This function turns the Tone off.
ARGS:
        <none>

RETURNS:
    <none>

******************************************************************/
void bsm_TNStop(void)
{
    DISABLE_INTERRUPTS;

    Tone.Duration = 0;
    Tone.State    = bsc_TONE_OFF;

    GPT_stop(hGpt);

    ENABLE_INTERRUPTS;
}

/******************************************************************

FUNCTION: bsm_UpdateTone

DESCRIPTION:  This function is called every 10ms.  When the On or
              Off Time is decremented to 0, the Tone state is
              changed and the time is reloaded.  A Time
                          of 0 causes the Tone to stay in its current state.

ARGS:
        <none>

RETURNS:
    <none>

******************************************************************/
void bsm_UpdateTone(void)
{
    if( Tone.Duration > 0 )
    {
        Tone.Duration -= PERIODIC_TIME_MS;

        switch( Tone.State )
        {
        case bsc_TONE_ON:
            // if we are controlling the Tone
            if( Tone.OnTime > 0 )
            {
                Tone.OnTime -= PERIODIC_TIME_MS;
                // if the counter just turned to 0
                if( Tone.OnTime <= 0 )
                {
                    // reload the value and change the state
                    Tone.OffTime = Tone.ReloadOffTime;
                    Tone.State   = bsc_TONE_OFF;
                }
            }
            break;

        case bsc_TONE_OFF:
            Tone.OffTime -= PERIODIC_TIME_MS;
            // if the counter just turned to 0
            if( Tone.OffTime <= 0 )
            {
                Tone.NumberOfTones--;
                if( Tone.NumberOfTones != 0 )
                {
                    Tone.State  = bsc_TONE_ON;
                    Tone.OnTime = Tone.ReloadOnTime;
                }
                else
                {
                    Tone.State    = bsc_DEAD_TIME;
                    Tone.DeadTime = Tone.ReloadDeadTime;
                }
            }
            break;

        case bsc_DEAD_TIME:
            Tone.DeadTime-=PERIODIC_TIME_MS;

            if( Tone.DeadTime <= 0 )
            {
                Tone.State         = bsc_TONE_ON;
                Tone.OnTime        = Tone.ReloadOnTime;
                Tone.NumberOfTones = Tone.ReloadNumberOfTones;
            }
            break;

        default:
            break;
        }
    }

    TwiddleHardware();
}


/******************************************************************

FUNCTION: TwiddleHardware

DESCRIPTION:  This function modifies the hardware to output the
              frequency.

ARGS:
        <none>

RETURNS:
    <none>

******************************************************************/
void TwiddleHardware()
{
    switch( Tone.State )
    {
    case bsc_TONE_ON:
        // Turn the timer on.
        GPT_start(hGpt);
        break;

    case bsc_TONE_OFF:
    case bsc_DEAD_TIME:
        // Stop the Timer and set the output low
        GPT_stop(hGpt);
        break;

    default:
        break;
    }
}
