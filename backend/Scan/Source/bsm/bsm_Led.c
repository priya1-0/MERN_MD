/************************************************************************
*
* MODULE: bsm_Led.c
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
*              LEDs.
*
*************************************************************************/

/////////////
// Includes
/////////////

#include <csl.h>
#include <csl_gpio.h>
#include <csl_hpi.h>

// Remove these defines if they ever get added into the CSL
#define _HPI_HGPIODAT2_ADDR (0xA00Eu)
#define _HPI_HGPIODAT2      PREG16(_HPI_HGPIODAT2_ADDR)
#define HGPIODAT2           _HPI_HGPIODAT2

#define _HPI_HGPIODIR2_ADDR (0xA00Cu)
#define _HPI_HGPIODIR2      PREG16(_HPI_HGPIODIR2_ADDR)
#define HGPIODIR2           _HPI_HGPIODIR2

#include "bsm_led.h"

////////////
// Defines
////////////

#define LED_UPDATE_PERIOD_MS 100                    // This is defined in the CDB file
#define FAST_BLINK_PERIOD_MS 1200                       // on for 600 ms, off for 600 ms
#define SLOW_BLINK_PERIOD_MS 3000                       // on for 1500 ms, off for 1500 ms

#define LedClock      GPIO_PIN5                             // bit mask for the I/O pin
#define LedData       GPIO_PIN3                             // bit mask for the I/O pin
#define LedClockAddr  _GPIO_IODATA                      // register of I/O pins
#define LedDataAddr   _GPIO_IODATA                              // register of I/O pins
#define LedDir        _GPIO_IODIR                                       // register for the direction
#define LedMode       0x20                                              // mode pin of the LED driver
#define LedModeAddr   HGPIODAT2
#define LedModeDir    HGPIODIR2
#define LedOutputDis  0x01                                      // output enable pin
#define LedOutputAddr HGPIODAT2
#define LedOutputDir  HGPIODIR2

// macros to clear and set the LED Data pin
#define SetLedData()   LedDataAddr   = LedDataAddr | (LedData)
#define ClearLedData() LedDataAddr   = LedDataAddr & ~(LedData)

// macros to clear and set the LED Clock pin
#define SetLedClock()   LedClockAddr = LedClockAddr | (LedClock)
#define ClearLedClock() LedClockAddr = LedClockAddr & ~(LedClock)

// the rising and falling edges of the clock must be at least 6.4ns apart
// RJD: this may need some nops to reduce EMI noise
#define PulseClock() LedClockAddr               = LedClockAddr | (LedClock); \
    LedClockAddr                                = LedClockAddr & ~(LedClock)

#define EnableLedOutputEnable()  LedOutputAddr &= ~(LedOutputDis)
#define DisableLedOutputEnable() LedOutputAddr |= LedOutputDis

#define SetLedHold()  LedModeAddr              &= ~LedMode
#define SetLedShift() LedModeAddr              |= LedMode

//////////
// Types
//////////

typedef struct bst_LedStructTag
{
    UINT16 OnTime;
    UINT16 OffTime;
    UINT16 ReloadOnTime;
    UINT16 ReloadOffTime;
    bst_LedState State;
}bst_LedStruct;

////////////
// Globals
////////////

// state of all the LEDs
static bst_LedStruct LedArray[bsc_MAXLEDS] = { 0 };

// This variable is set to TRUE when it has changed
static BOOL StateChanged = FALSE;

///////////////
// Prototypes
///////////////
static void bsm_SetLed(bst_Led Led, bst_LedState OnOff);
static void bsm_BlinkLed(bst_Led Led, UINT16 BlinkPeriod);
void bsm_ModemProgression(void);
void bsm_UpdateLeds(void);
static void TwiddleHardware(void);





/******************************************************************

FUNCTION: bsm_LedInit

DESCRIPTION:  This function turns all the LEDs off.

ARGS:
        <none>

RETURNS:
    <none>

******************************************************************/
void bsm_LedInit(void)
{
    int i;

    // Clear the Led Array
    for (i = 0; i < bsc_MAXLEDS; i++)
    {
        LedArray[i].OnTime        = 0;
        LedArray[i].OffTime       = 0;
        LedArray[i].ReloadOnTime  = 0;
        LedArray[i].ReloadOffTime = 0;
        LedArray[i].State         = bsc_LEDOFF;
    }

    // Set clock and data low
    ClearLedData();
    ClearLedClock();

    // enable the outputs
    EnableLedOutputEnable();

    // set the lines as outputs
    LedDir |= (LedClock | LedData);

    HPI_FSET(HGPIOEN, EN2, 1);                                          // Enable the Mode and
    HPI_FSET(HGPIOEN, EN4, 1);                                          // Output Enable as I/O

    EnableLedOutputEnable();
    SetLedHold();

    LedOutputDir |= LedOutputDis;               // Set HAS and HBIL as outputs
    LedModeDir   |= LedMode;

    // clear the LEDs
    TwiddleHardware();
}

/******************************************************************

FUNCTION: bsm_LDChange

DESCRIPTION:  This function sets an LED to be On, Off, Fast Blink,
              Slow Blink, or Strobe.

ARGS:
        bst_Led Led: LED to be changed.
        bst_LedState: On, Off, fast flash, slow flash, or strobe

RETURNS:
    <none>

******************************************************************/
void bsm_LDChange(bst_Led Led, bst_LedState OnOff)
{
    // do an action based on the new state
    switch (OnOff)
    {
    case bsc_LEDOFF:
    case bsc_LEDON:
        bsm_SetLed(Led, OnOff);
        break;

    case bsc_LEDFASTFLASH:
        bsm_BlinkLed(Led, FAST_BLINK_PERIOD_MS / LED_UPDATE_PERIOD_MS);
        break;

    case bsc_LEDSLOWFLASH:
        bsm_BlinkLed(Led, SLOW_BLINK_PERIOD_MS / LED_UPDATE_PERIOD_MS);
        break;

    case bsc_LEDSTROBE:
        bsm_ModemProgression();
        break;

    default:
        break;
    }

    #ifdef LOW_BATT_GPIO_TOGGLE
                #warn "Low Battery State causes XF pin to switch state."
    if(Led == bsc_LEDLOWBATT)
    {            //Check if chnage is for the LowBattery LED
        if(OnOff == bsc_LEDOFF)
        {                //if the change is to shut if off, turn on XF pin
            GLB_SET_XF;
        }
        else
        {                //if the change is not to shut if off, shut off XF pin
            GLB_CLR_XF;
        }
    }
        #endif
}

/******************************************************************

FUNCTION: bsm_SetLed

DESCRIPTION:  This function sets an LED to be On or Off.

ARGS:
        bst_Led Led: LED to be changed.
        bst_LedState: On or Off

RETURNS:
    <none>

******************************************************************/
void bsm_SetLed(bst_Led Led, bst_LedState OnOff)
{
    // disable interrupt around
    DISABLE_INTERRUPTS;

    StateChanged          = TRUE;

    // set the on and off time to 0 to keep the LED in the same state
    LedArray[Led].OnTime  = 0;
    LedArray[Led].OffTime = 0;

    // turn the LED on or off
    LedArray[Led].State   = OnOff;

    ENABLE_INTERRUPTS;
}

/******************************************************************

FUNCTION: bsm_BlinkLed

DESCRIPTION:  This function sets an LED to blink.

ARGS:
        bst_Led Led: LED to set to blinking.
        UINT16 BlinkPeriod: Number of milliseconds in a period

RETURNS:
    <none>

******************************************************************/
void bsm_BlinkLed(bst_Led Led, UINT16 BlinkPeriod)
{
    DISABLE_INTERRUPTS;

    StateChanged                = TRUE;

    LedArray[Led].State         = bsc_LEDON;

    LedArray[Led].OnTime        = BlinkPeriod/2;
    LedArray[Led].OffTime       = BlinkPeriod/2;
    LedArray[Led].ReloadOnTime  = BlinkPeriod/2;
    LedArray[Led].ReloadOffTime = BlinkPeriod/2;

    ENABLE_INTERRUPTS;
}


/******************************************************************

FUNCTION: bsm_ModemProgression

DESCRIPTION:  This function sets the modem LEDS to blink from left
              to right.

ARGS:
        <none>

RETURNS:
    <none>

******************************************************************/
void bsm_ModemProgression(void)
{
    DISABLE_INTERRUPTS;

    StateChanged                         = TRUE;

    // set the first LED to turn on.
    LedArray[bsc_LEDDATA1].OnTime        =
        FAST_BLINK_PERIOD_MS / LED_UPDATE_PERIOD_MS / 2;
    LedArray[bsc_LEDDATA1].ReloadOnTime  =
        FAST_BLINK_PERIOD_MS / LED_UPDATE_PERIOD_MS / 2;
    LedArray[bsc_LEDDATA1].ReloadOffTime =
        FAST_BLINK_PERIOD_MS / LED_UPDATE_PERIOD_MS;
    LedArray[bsc_LEDDATA1].State         = bsc_LEDON;

    // set the second LED to turn off while the first LED is on.
    LedArray[bsc_LEDDATA2].OffTime       =
        FAST_BLINK_PERIOD_MS / LED_UPDATE_PERIOD_MS / 2;
    LedArray[bsc_LEDDATA2].ReloadOnTime  =
        FAST_BLINK_PERIOD_MS / LED_UPDATE_PERIOD_MS / 2;
    LedArray[bsc_LEDDATA2].ReloadOffTime =
        FAST_BLINK_PERIOD_MS / LED_UPDATE_PERIOD_MS;
    LedArray[bsc_LEDDATA2].State         = bsc_LEDOFF;

    // set the third LED to turn off while the first and second LED are on.
    LedArray[bsc_LEDDATA3].OffTime       =
        FAST_BLINK_PERIOD_MS / LED_UPDATE_PERIOD_MS;
    LedArray[bsc_LEDDATA3].ReloadOnTime  =
        FAST_BLINK_PERIOD_MS / LED_UPDATE_PERIOD_MS / 2;
    LedArray[bsc_LEDDATA3].ReloadOffTime =
        FAST_BLINK_PERIOD_MS / LED_UPDATE_PERIOD_MS;
    LedArray[bsc_LEDDATA3].State         = bsc_LEDOFF;

    ENABLE_INTERRUPTS;
}

/******************************************************************

FUNCTION: bsm_UpdateLeds

DESCRIPTION:  This function is called every 100ms.  When the On or
              Off Time is decremented to 0, the LED state is
              switched and the opposite time is reloaded.  A Time
                          of 0 causes the LED to stay in its current state.

ARGS:
        <none>

RETURNS:
    <none>

******************************************************************/
void bsm_UpdateLeds(void)
{
    UINT16 i;

    // loop through all the LEDs
    for (i = 0; i < bsc_MAXLEDS; i++)
    {
        switch (LedArray[i].State)
        {
        case bsc_LEDON:
            // if we are controlling the LED
            if (LedArray[i].OnTime > 0)
            {
                LedArray[i].OnTime--;
                // if the counter just turned to 0
                if (LedArray[i].OnTime == 0)
                {
                    // reload the value and change the state
                    LedArray[i].OffTime = LedArray[i].ReloadOffTime;
                    LedArray[i].State   = bsc_LEDOFF;
                    StateChanged        = TRUE;
                }
            }
            break;

        case bsc_LEDOFF:
            // if we are controlling the LED
            if (LedArray[i].OffTime > 0)
            {
                LedArray[i].OffTime--;
                // if the counter just turned to 0
                if (LedArray[i].OffTime == 0)
                {
                    // reload the counter and change the state.
                    LedArray[i].OnTime = LedArray[i].ReloadOnTime;
                    LedArray[i].State  = bsc_LEDON;
                    StateChanged       = TRUE;
                }
            }
            break;

        default:
            break;
        }
    }

    if (StateChanged)
    {
        StateChanged = FALSE;
        TwiddleHardware();
    }
}

/******************************************************************

FUNCTION: TwiddleHardware

DESCRIPTION:  This function twiddles the hardware I/O to set the
                          LEDs.

ARGS:
        <none>

RETURNS:
    <none>

******************************************************************/
void TwiddleHardware()
{
    INT16 i;

    // disable the LEDs while they are being changed
    DisableLedOutputEnable();

    // Set the mode of the shift registers to allow shifting
    SetLedShift();

    // loop through all the LEDs backwards
    for (i = bsc_MAXLEDS - 1; i >= 0; i--)
    {
        // set the data line for the LED
        if (LedArray[i].State == bsc_LEDOFF)
        {
            SetLedData();
        }
        else
        {
            ClearLedData();
        }

        // clock in the data
        PulseClock();
    }

    // Set the mode of the shift register to hold the LEDs constant
    SetLedHold();

    // turn the LEDs back on
    EnableLedOutputEnable();

    // set the line low until next time
    ClearLedData();
}
