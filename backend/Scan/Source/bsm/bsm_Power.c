
/************************************************************************
*
* MODULE: bsm_Power.c
*
* OWNER:
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the functions to control the power
*              button and the power supplies.
*
*************************************************************************/

/////////////
// Includes
/////////////
#include <csl.h>
#include <csl_gpio.h>
#include <csl_hpi.h>
#include "2490Gcfg.h" //For SWI information


#include "global.h"
#include "bsm_led.h"
#include "bsm_power.h"
#include "bsm_NVStorage.h"
#include "uim_ui.h"
#include "bsm_SerialPort.h"
#include "bsm_Tone.h"
#include "tbm_Handler.h"
#include "bsm_Event.h"

////////////
// Defines
////////////

#define HOLD    1
#define RELEASE 0

#define HOLD_TIME_MS         500
#define GLITCH_TIME_MS       100
#define PERIODIC_TIME_MS     10
#define SHUTDOWN_ACCELERATOR 4

#define InitializePowerSwitch() HPI_FSET(HGPIODIR, HD0, 0); \
    HPI_FSET(HGPIOEN, EN0, 1)
#define GetPowerSwitch()        HPI_FGET(HGPIODAT, HD0)

#define TurnOffPowerSupplies()  GPIO_FSET(IODATA, IO7D, 1);
#define TurnOnPowerSupplies()   GPIO_FSET(IODATA, IO7D, 0);
#define InitializePowerSupply() TurnOnPowerSupplies(); \
    GPIO_FSET(IODIR, IO7DIR, GPIO_OUTPUT);

#define InitializeBatteryGood() GPIO_FSET(IODIR, IO6DIR, GPIO_INPUT);
#define IsBatteryGood()         GPIO_FGET(IODATA, IO6D);

#define DisableDummyLoad()    GPIO_FSET(IODATA, IO2D, 0)
#define EnableDummyLoad()     GPIO_FSET(IODATA, IO2D, 1)
#define InitializeDummyLoad() DisableDummyLoad(); \
    GPIO_FSET(IODIR, IO2DIR, GPIO_OUTPUT);

#define _TIMER_WDTWCTL1_ADDR (0x4014u)
#define _TIMER_WDTWCTL1      PREG16(_TIMER_WDTWCTL1_ADDR)
#define WDTWCTL1             _TIMER_WDTWCTL1

#define _TIMER_WDTWCTL2_ADDR (0x4015u)
#define _TIMER_WDTWCTL2      PREG16(_TIMER_WDTWCTL2_ADDR)
#define WDTWCTL2             _TIMER_WDTWCTL2

#define WDTWCTL1_WEN 0x40

#define KICK_WATCHDOG_1()  WDTWCTL2  = 0xA5C6
#define KICK_WATCHDOG_2()  WDTWCTL2  = 0xDA7E
#define DISABLE_WATCHDOG() WDTWCTL1 &= ~WDTWCTL1_WEN

//////////
// Types
//////////
typedef enum bst_PowerStateTag
{
    bsc_POWER_UP_HOLD,
    bsc_POWER_UP_RELEASE,
    bsc_LED_BLINK,
    bsc_POWER_UP_GOOD_HOLD,
    bsc_RELEASE,
    bsc_HOLD
} bst_PowerState;

////////////
// Globals
////////////
static bst_PowerState PowerState;
static Bool           Disable;
static int            Debounce = HOLD_TIME_MS;
static BOOL           shutdownInprogress; //Flag that denotes if a shutdown is in progress.
static SWI_Attrs      swiAttrs;

///////////////
// Prototypes
///////////////
void bsm_UpdatePower(void);



/******************************************************************

FUNCTION: bsm_PowerInit

DESCRIPTION:  This function initializes the hardware

ARGS:
        <none>

RETURNS:
    <none>

******************************************************************/
void bsm_PowerInit(void)
{
    InitializePowerSupply();
    InitializePowerSwitch();
    InitializeBatteryGood();
    InitializeDummyLoad();

    // A change in the requirements says we do not debounce the power button on
    // power up.  Moved the LED Blink call to after the function test flag is
    // checked.
    PowerState         = bsc_POWER_UP_GOOD_HOLD;
    Disable            = FALSE;
    shutdownInprogress = FALSE;
}

/******************************************************************

FUNCTION: bsm_IsBatteryGood

DESCRIPTION:  This function returns the value of the battery good
                          signal

ARGS:
        <none>

RETURNS:
    TRUE  if the battery is good
    FALSE otherwise

******************************************************************/
BOOL bsm_IsBatteryGood(void)
{
    return IsBatteryGood();
}

/******************************************************************

FUNCTION: bsm_isPowerStateGoodHold

DESCRIPTION:
   Return true if status of the power state is bsc_POWER_UP_GOOD_HOLD

ARGS:
   <none>

RETURNS:
   True if status of the power button is bsc_POWER_UP_GOOD_HOLD
   False otherwise.
******************************************************************/
BOOL bsm_isPowerStateGoodHold(void)
{
    if (PowerState == bsc_POWER_UP_GOOD_HOLD)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/******************************************************************

FUNCTION: bsm_EnableDummyLoad

DESCRIPTION:  This function turns on the dummy load for the
              battery calculations.

ARGS:
        <none>

RETURNS:
    <none>

******************************************************************/
void bsm_EnableDummyLoad(void)
{
    EnableDummyLoad();
}

/******************************************************************

FUNCTION: bsm_DisableDummyLoad

DESCRIPTION:  This function turns off the dummy load for the
              battery.

ARGS:
        <none>

RETURNS:
    <none>

******************************************************************/
void bsm_DisableDummyLoad(void)
{
    DisableDummyLoad();
}

/******************************************************************

FUNCTION: bsm_PMDisableButton

DESCRIPTION:  This function disables the power switch from turning
              the unit off.

ARGS:
        <none>

RETURNS:
    <none>

******************************************************************/
void bsm_PMDisableButton(void)
{
    DISABLE_INTERRUPTS
        Disable = TRUE;
    ENABLE_INTERRUPTS
}

/******************************************************************

FUNCTION: bsm_EnablePowerButton

DESCRIPTION:  This function enables the power switch to turn off
              the power supplies.

ARGS:
        <none>

RETURNS:
    <none>

******************************************************************/
void bsm_PMEnableButton(void)
{
    DISABLE_INTERRUPTS
        Disable = FALSE;
    ENABLE_INTERRUPTS
}

/******************************************************************

FUNCTION: bsm_UpdatePower

DESCRIPTION:  This function updates the state of the power switch
              every PERIODIC_TIME_MS.

ARGS:
        <none>

RETURNS:
    <none>

******************************************************************/
void bsm_UpdatePower()
{
    // The watchdogs are kicked here so that if this function doesn't get called,
    // the DSP is reset because of the watchdog.  If this function can be reached,
    // then the user can turn off the unit.
    KICK_WATCHDOG_1();

    //check if shutdown is already in progress
    if(!shutdownInprogress)
    {
        switch( PowerState )
        {
        // We have just powered on and are waiting for the user to hold the
        // button long enough so the unit stays on.
        case bsc_POWER_UP_HOLD:
            if( GetPowerSwitch() == RELEASE )
            {
                Debounce   = HOLD_TIME_MS;
                PowerState = bsc_POWER_UP_RELEASE;
            }
            else
            {
                Debounce = Debounce - PERIODIC_TIME_MS;
                if( Debounce <= 0 )
                {
                    PowerState = bsc_LED_BLINK;
                    Debounce   = GLITCH_TIME_MS;
                }
            }
            break;

        // In this case, the unit just powered up and the user released the button.
        // If the button is not held down, the unit turns off.
        case bsc_POWER_UP_RELEASE:
            if( GetPowerSwitch() == HOLD )
            {
                PowerState = bsc_POWER_UP_HOLD;
                Debounce   = HOLD_TIME_MS;
            }
            else
            {
                Debounce = Debounce - PERIODIC_TIME_MS;
                if( Debounce <= 0 )
                {
                    //set the inprogress flag
                    shutdownInprogress = TRUE;

                    // Disable Telemetry B (if its currently enabled).
                    tbm_telemBDeactivate();

                    //decrement the Powerdown SWI mailbox
                    bsm_PMEnableSWI();
                }
            }
            break;

        // This is an intermediary state to turn on the LEDs to Blink
        case bsc_LED_BLINK:
            // Flash the power LED
            uim_POSTInProgress();
            PowerState = bsc_POWER_UP_GOOD_HOLD;

        // Fall through to the Good Hold State to start the debounce

        // The unit has powered up and the button was held long enough.  Now
        // we are waiting for the user to release the button.
        case bsc_POWER_UP_GOOD_HOLD:
            if( GetPowerSwitch() == HOLD )
            {
                Debounce = GLITCH_TIME_MS;
            }
            else
            {
                Debounce = Debounce - PERIODIC_TIME_MS;

                if( Debounce <= 0 )
                {
                    PowerState = bsc_RELEASE;
                }
            }
            break;

        // The unit is running and the button is release.
        case bsc_RELEASE:
            if( GetPowerSwitch() == HOLD )
            {
                PowerState = bsc_HOLD;
                Debounce   = HOLD_TIME_MS;
            }
            break;

        // The unit is running and the button is held down.  If the button is
        // held down long enough, the unit will turn off.
        case bsc_HOLD:
            if( GetPowerSwitch() == RELEASE )
            {
                PowerState = bsc_RELEASE;
            }
            else
            {
                // Shutdown needs to commence quicker than the normal debounce
                Debounce = Debounce - (PERIODIC_TIME_MS * SHUTDOWN_ACCELERATOR);
                if( Debounce <= 0 && Disable == FALSE )
                {
                    //set the inprogress flag
                    shutdownInprogress = TRUE;

                    // Disable Telemetry B (if its currently enabled).
                    tbm_telemBDeactivate();

                    //decrement the Powerdown SWI mailbox
                    bsm_PMEnableSWI();
                }
            }
            break;

        default:
            break;
        }
    }

    // This is the second watchdog kick.  See the comment above about the watchdogs
    KICK_WATCHDOG_2();
}

/******************************************************************

FUNCTION: bsm_PMShutDown

DESCRIPTION:  This function calls calls another ensuring the FLASH
              is flushed while gracefully shutting down the unit.

ARGS:
                <none>

RETURNS:
    <none>

******************************************************************/
void bsm_PMShutDown(void)
{
    bsm_PMShutDownFlashCorrupt(true);
}

/******************************************************************

FUNCTION: bsm_PMShutDownFlashCorrupt

DESCRIPTION:  This function shuts down the unit gracefully.

ARGS:
        flushFlag - This flag gates the call to bsm_EEFlush().
            So far, the one and only reason NOT to call this function is
            when the FLASH has been found corrupt. The FLASH is corrupt
            when the calculated CRC does not match the stored CRC value.
            On this platform 2 areas of FLASH are used, primary and
            secondary, to double the chances of keeping the FLASH
            integrity in tact. When both the primary and secondary data
            integrity checks fail, then FLASH should be left corrupt so
            that a reboot finds the corruption again and does not
            interrogate. If upon reboot data integrity is magically
            restored then the application should be allowed to start.

RETURNS:
    <none>

******************************************************************/
void bsm_PMShutDownFlashCorrupt(bool flush)
{
    //set the inprogress flag
    shutdownInprogress = TRUE;

    // Disable Telemetry B (if its currently enabled).
    tbm_telemBDeactivate();

    // Shut off all LEDs to give impression that unit is shut down,
    // even while we are flushing.
    // Re-initializing the LEDs turns off all of the LEDs.  This is
    // the only visible function to turn off the LEDs because we
    // are running at the same level as the periodic function that
    // updates the LEDs.
    bsm_LedInit();

    // Turn off the tones
    bsm_TNStop();

    // Make sure the modem is off.  If the modem is active, it messes up the Flash Flush
    IRQ_disable(IRQ_EVT_XINT1);
    IRQ_disable(IRQ_EVT_RINT1);

    bsm_WriteTotalOnTimeMinutes();

    // Flush the log from RAM to EEPROM
    if (flush)
    {
        bsm_EEFlush();
    }

#ifdef SKIP_SHUTDOWN
        #warn "Shutdown disabled!"
    bsm_SDPrint("Shutdown disabled!");
#else
    // Turn off interrupts so that we can complete everything
    DISABLE_INTERRUPTS;

    // If the button is pushed down, let's just wait until it's up to continue
    while( GetPowerSwitch() == HOLD )
    {
        KICK_WATCHDOG_1();
        KICK_WATCHDOG_2();
    }

    // Now take down the system
    TurnOffPowerSupplies();
#endif
    // We don't want to return
    while(1) ;
}

/******************************************************************

FUNCTION: bsm_PMPowerButtonShutdownSWI

DESCRIPTION:  This is the function that the Power Button Shutdown
              SWI calls when the SWI is posted.

ARGS:
        <none>

RETURNS:
    <none>
******************************************************************/
void bsm_PMPowerButtonShutdownSWI(void)
{
    UINT16 mbox;
    //increment the Powerdown SWI mailbox so that the mailbox does
    //not reach zero (so it is not inadvertently reposted).
    bsm_PMDisableSWI();

    //Shutdown the system.
    bsm_EHLock("Shutdown via power switch.");
}

/******************************************************************

FUNCTION: bsm_PMDisableSWI

DESCRIPTION:  This is the function disables the Power Button SWI by
              incrementing it's mailbox value.

ARGS:
        <none>

RETURNS:
    <none>
******************************************************************/
void bsm_PMDisableSWI(void)
{
    SWI_getattrs(&SWI_PowerButtonShutdown, &swiAttrs);
    swiAttrs.mailbox++;
    SWI_setattrs(&SWI_PowerButtonShutdown, &swiAttrs);
    //note: SWI_inc() will not work because after incrementing
    //      the mailbox it unconditionally posts the SWI.
}

/******************************************************************

FUNCTION: bsm_PMEnableSWI

DESCRIPTION:  This is the function enables the Power Button SWI by
              decrementing it's mailbox value. The SWI is poseted
              if the mailbox is decremented to zero.

ARGS:
        <none>

RETURNS:
    <none>
******************************************************************/
void bsm_PMEnableSWI(void)
{
    SWI_dec(&SWI_PowerButtonShutdown);
}


