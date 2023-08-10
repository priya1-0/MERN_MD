/*
***********************************************************************
 2490 In-home Remote Monitor
 Copyright (c) Medtronic, Inc. 2001

 MODULE: User Interface Module

 OWNER: Medtronic

 $Revision$

 $Date$

 $RCSfile$

 FUNCTIONS:
      --Public--
long uim_AddToEstimatedSize (long size)
void uim_InterrogationStarted(void)
void uim_InterrogationProgress(long size)
void uim_InterrogationComplete(void)
void uim_InterrogationSkipped(void)
void uim_AlertTone(void)
void uim_ErrorTone(void)
void uim_CompleteTone(void)
void uim_TelemetryWarning(bool onOff)
void uim_ModemWarning(bool state)
void uim_ModemWarning_AlertTone_15Minutes(void)
void uim_ModemError(void)
void uim_ModemStart(bool state)
void uim_DisplayReady(void)
void uim_POSTInProgress(void)
void uim_BatteryWarning(void)
void uim_ModemTransferComplete(void)
void uim_StrobePhoneLeds(bool state)
void uim_EPRWarning(void)


 DESCRIPTION:
    This module contains the code which is used to control the UI of the Remote
    Monitor.


 GLOBAL MODULE DATA:

 STATIC MODULE DATA:

 ENDPURPOSE

***********************************************************************
*/
#include "aim_kappa.h"
#include "uim_ui.h"
#include "bsm_global.h"
#include "bsm_power.h"
#include "com_main.h"
#include "nwm_net.h"
#include "types.h" // ON/OFF defined here.

// the size of the estimated interrogate
long uiv_estimatedSize;
// the actual amount of interrogated data
long uiv_actualSize;

// current flashing telemetry progress led
unsigned int v_flashingTelemetryLed;

/*
***********************************************************************

 FUNCTION:   uim_AddToEstimatedSize

 DESCRIPTION:
Add the passed value to the total data to be interrogated. This number will
be used to update the progress meter.

 FUNCTION CONSTANTS:

 FUNCTION PARAMETERS:
   size
      The number of units to add to the estimated interrogation data
      size.

***********************************************************************
*/

long uim_AddToEstimatedSize (long size)
{
    uiv_estimatedSize += size;
    return(uiv_estimatedSize);
}

/*
***********************************************************************

 FUNCTION:   uim_InterrogationStarted

 DESCRIPTION:
This function initializes the data which controls the progress meter and also
starts the first progress meter LED flashing. Finally, makes a call to initialize
the 6 second countdown and emit tone over phone line.

 FUNCTION CONSTANTS:
   None

 FUNCTION PARAMETERS:
   None


***********************************************************************
*/

void uim_InterrogationStarted(void)
{
    uiv_estimatedSize = 0;
    uiv_actualSize    = 0;

    // start flashing first progress meter LED and
    //  turn all the rest off
    uim_InterrogationProgress(0);
}

/*
***********************************************************************

 FUNCTION:   uim_InterrogationProgress

 DESCRIPTION:
This function updates the progress meter as data is being read. The parameter
passed into this function is the amount of data just read. This value is
compared to the total amount to read and the LED's are updated accordingly.
A call is made to emit a tone over the phone line if needed.

If the estimated size is 0, then only light the 1 LED. Otherwise figure
the percentage.  The first LED indicates initial telemetry is being done
(such as collect waveform data).  The remaining 4 LED's are used to
indicate progress in interrogating the estimated data.

 FUNCTION CONSTANTS:
    AIC_PROGRESS_LEDS
      Array of the progress meter LED's.

   AIC_NUMBER_OF_PROGRESS_LEDS
      Number of elements in the array.

 FUNCTION PARAMETERS:
   None


***********************************************************************
*/
const int AIC_PROGRESS_LEDS[] =
{
    bsc_LEDPROGRESS1,
    bsc_LEDPROGRESS2,
    bsc_LEDPROGRESS3,
    bsc_LEDPROGRESS4,
    bsc_LEDPROGRESS5
};
#define AIC_NUMBER_OF_PROGRESS_LEDS sizeof(AIC_PROGRESS_LEDS)/sizeof(int)

void uim_InterrogationProgress(long size)
{
    long percent;
    int  index;
    int  i;
    // initialize to something other than 0 so that the LEDs
    //  are driven the first time through the routine
    static int lastIndex = AIC_NUMBER_OF_PROGRESS_LEDS;

    // Calculate the percentage complete
    // don't divide by 0
    if (uiv_estimatedSize == 0)
    {
        percent = 1;

        // this is the index of the flashing LED
        index   = 0;
    }
    else
    {
        // update the actual amount of data interrogated
        uiv_actualSize += size;
        percent         = (uiv_actualSize *100)/ uiv_estimatedSize;

        // this is the index of the flashing LED
        index           = 1 + (int) (percent * (AIC_NUMBER_OF_PROGRESS_LEDS - 1))/100;
    }

    // If this is a 2020C monitor and autoId has been successful, then, if index
    // is 0 that means, autoID LED needs to be blinking.
    // In this case, instead blink the next LED, because the autoID LED is supposed to be
    // on during interrogation in a 2020C monitor once the autoID has been successful.
    if ((aim_MonitorIsA2020C() == true) &&
        (aim_autoIdSuccessful() == true) &&
        (index == 0))
    {
        index++;
    }

    // no sense driving the LEDs if the currently flashing LED hasn't changed
    if ((index != lastIndex) && (index < AIC_NUMBER_OF_PROGRESS_LEDS))
    {
        lastIndex = index;

        // all LEDs before the flashing LED should be turned on
        for(i=0; i<AIC_NUMBER_OF_PROGRESS_LEDS; ++i)
        {
            if (i<index)
            { // LED's that are on
                bsm_LDChange((bst_Led)AIC_PROGRESS_LEDS[i], bsc_LEDON);
            }
            else if (i==index)
            { // the one LED that is flashing
              // stop the current flashing LED if were are paused.
                bsm_LDChange((bst_Led)AIC_PROGRESS_LEDS[index], bsc_LEDFASTFLASH);
                v_flashingTelemetryLed = index;
            }
            else // i > index
            { // LED's that are off
                bsm_LDChange((bst_Led)AIC_PROGRESS_LEDS[i], bsc_LEDOFF);
            }

        }
    }

}
/*
***********************************************************************

 FUNCTION:   uim_IlluminateLED

 DESCRIPTION:
This function receives as input an LED index (1-5) and illuminates
lights 1 to index of the LED.

***********************************************************************
*/
void uim_IlluminateLED(USHORT index)
{
    int i;
    // all LEDs before the flashing LED should be turned on
    for(i=0; i<AIC_NUMBER_OF_PROGRESS_LEDS; ++i)
    {
        if (i<index)
        {    // LED's that are on
            bsm_LDChange((bst_Led)AIC_PROGRESS_LEDS[i], bsc_LEDON);
        }
        else if (i==index)
        {    // the one LED that is flashing
             // stop the current flashing LED if we are paused.
            bsm_LDChange((bst_Led)AIC_PROGRESS_LEDS[index], bsc_LEDFASTFLASH);
            v_flashingTelemetryLed = index;
        }
        else  // i > index
        {    // LED's that are off
            bsm_LDChange((bst_Led)AIC_PROGRESS_LEDS[i], bsc_LEDOFF);
        }

    }
}
/*
***********************************************************************

 FUNCTION:   uim_InterrogationComplete

 DESCRIPTION:
This function is called when the interrogation is finished. The
progress LEDs are all turned on (none of them are flashing) and the
interrogation completion tone is sounded. It waits 6 seconds and then
turns off all of the progress LEDs.

***********************************************************************
*/

void uim_InterrogationComplete(void)
{
    int i;
    // sound the interrogation complete tone
    uim_CompleteTone();

    // turn the interrogation progress LEDs on
    for(i=0; i<AIC_NUMBER_OF_PROGRESS_LEDS; ++i)
    {
        // LED's that are off
        bsm_LDChange((bst_Led)AIC_PROGRESS_LEDS[i], bsc_LEDON);
    }

    NU_Sleep(600);

    // turn the interrogation progress LEDs on
    for(i=0; i<AIC_NUMBER_OF_PROGRESS_LEDS; ++i)
    {
        // LED's that are off
        bsm_LDChange((bst_Led)AIC_PROGRESS_LEDS[i], bsc_LEDOFF);
    }

}

/*
***************************************************************************
*
* FUNCTION:   uim_InterrogationSkipped
*
* DESCRIPTION:
*    This function is called when the device
*    is not found and the power button is held pressed for some time.
*    Turn off the progress LEDs.
*
****************************************************************************
*/
void uim_InterrogationSkipped(void)
{
    int i;

    // Turn off the the progress LEDs that are flashing or are on.
    for(i=0; i<AIC_NUMBER_OF_PROGRESS_LEDS; ++i)
    {
        bsm_LDChange((bst_Led)AIC_PROGRESS_LEDS[i], bsc_LEDOFF);
    }
}

/*
***********************************************************************

 FUNCTION:   uim_AlertTone

 DESCRIPTION:
Sound a recurring alert tone. This function sets up the control parameters to
sound a series of tones for 5 seconds followed by a delay of approximately 30
seconds.

 FUNCTION CONSTANTS:
   None

 FUNCTION PARAMETERS:
   None

The ON and OFF time is taken from original 2490 code in bsm_bsmglobal.h.
So the 2490G's AIC_ALERT_ONTIME is equivalent to the original 2490's
bsc_FASTBEEPON. And the 2490G's AIC_ALERT_OFFTIME is equivalent to the
original 2490's bsc_FASTBEEPOFF. The original AIC_ALERT_DURATION has
been dropped and is controlled by the caller(caller delays and shuts down
etc.).

***********************************************************************
*/

// Note: 100 ticks = 1 second.
#define AIC_ALERT_ONTIME   500
#define AIC_ALERT_OFFTIME  2200
#define AIC_ALERT_DURATION 12000
void uim_AlertTone(void)
{

#ifdef NO_TONES
    return;
#endif

    bsm_TNSound(AIC_ALERT_ONTIME,
                AIC_ALERT_OFFTIME,
                AIC_ALERT_DURATION,
                bsc_TONEHIGH,
                bsc_FASTBEEP);
}

/*
***********************************************************************

 FUNCTION:   uim_ErrorTone

 DESCRIPTION:
1 beep 1 second in duration.

 FUNCTION CONSTANTS:
   None

 FUNCTION PARAMETERS:
   None

The ON and OFF time is taken from original 2490 code in bsm_bsmglobal.h.
So the 2490G's AIC_ERROR_ONTIME is equivalent to the original 2490's
bsc_FASTBEEPON. And the 2490G's AIC_ERROR_OFFTIME is equivalent to the
original 2490's bsc_FASTBEEPOFF. The original AIC_ERROR_DURATION has
been dropped and is controlled by the caller(caller delays and shuts down
etc.).

***********************************************************************
*/
#define AIC_ERROR_ONTIME   100
#define AIC_ERROR_OFFTIME  0
#define AIC_ERROR_DURATION AIC_ERROR_ONTIME

void uim_ErrorTone(void)
{

#ifdef NO_TONES
    return;
#endif

    bsm_TNSound(AIC_ERROR_ONTIME,
                AIC_ERROR_OFFTIME,
                AIC_ERROR_DURATION,
                bsc_TONEHIGH,
                bsc_ONBEEP);
    NU_Sleep(120);
}


/*
***********************************************************************

 FUNCTION:   uim_CompleteTone

 DESCRIPTION:
2 short beeps.

 FUNCTION CONSTANTS:
   None

 FUNCTION PARAMETERS:
   None


***********************************************************************
*/

#define AIC_COMPLETE_ONTIME   100
#define AIC_COMPLETE_OFFTIME  0
#define AIC_COMPLETE_DURATION (AIC_COMPLETE_ONTIME+AIC_COMPLETE_OFFTIME)
void uim_CompleteTone(void)
{
#ifdef NO_TONES
    return;
#endif

    bsm_TNSound(AIC_COMPLETE_ONTIME,
                AIC_COMPLETE_OFFTIME,
                AIC_COMPLETE_DURATION,
                bsc_TONEHIGH,
                bsc_SLOWBEEP);
}


/*
***********************************************************************

 FUNCTION:   uim_TelemetryWarning

 DESCRIPTION:
Start the telemetry LED flashing and sound the alert tone and remember
what state the warning is in. Don't turn it on if it is already on because
that resets the tone timers.

***********************************************************************
*/

void uim_TelemetryWarning(bool onOff)
{
    static bool state = off;

    if (state != onOff)
    {
        if (onOff == true)
        {
            if (bsm_isPowerStateGoodHold())
            {
                // If power button is being held, we don't want to trigger the telemetry warning
                // just return to avoid updating the 'state' variable.  This routine is called
                // from several points in the Telemtry A logic.
                return;
            }
            // stop the flashing progress LED
            if (AIC_NUMBER_OF_PROGRESS_LEDS > v_flashingTelemetryLed)
            {
                // Turn off the LED that was flashing so far.
                // (However, if this is a 2020C monitor that has its autoID LED
                // flashing because autoID is still in progress (and telemetry
                // warning has occured), then do not turn off the flashing autoID
                // LED. For a 2020C, autoID LED needs to stay flashing even during
                // telemetry error.)
                if((aim_MonitorIsA2020C() == false) ||
                   (aim_autoIdSuccessful() == true) ||
                   (v_flashingTelemetryLed != 0))
                {
                    bsm_LDChange((bst_Led)AIC_PROGRESS_LEDS[v_flashingTelemetryLed], bsc_LEDOFF);
                }
            }
            bsm_LDChange(bsc_LEDBADANTENNA, bsc_LEDFASTFLASH);
            // initialize tone timers to sound the warning tone
            uim_AlertTone();
        }
        else
        {
            // turn on progress leds
            // turn the telemetry warning LED off
            // turn the tone timers off
            if (AIC_NUMBER_OF_PROGRESS_LEDS > v_flashingTelemetryLed)
            {
                bsm_LDChange((bst_Led)AIC_PROGRESS_LEDS[v_flashingTelemetryLed], bsc_LEDFASTFLASH);
            }
            bsm_LDChange(bsc_LEDBADANTENNA, bsc_LEDOFF);
            bsm_TNStop();

        }
        state = onOff;
    }
}


/************************************************************************

 FUNCTION:   uim_ModemWarning

 DESCRIPTION:  Controls the modem LED flashing and alert tone.

************************************************************************/
void uim_ModemWarning(bool state)
{
    switch (state)
    {
    case ON:   uim_StrobePhoneLeds(OFF);
        bsm_LDChange(bsc_LEDDATA1, bsc_LEDON);
        bsm_LDChange(bsc_LEDNODIALTONE, bsc_LEDFASTFLASH);
        uim_AlertTone();
        break;
    case OFF:
    default:   bsm_LDChange(bsc_LEDNODIALTONE, bsc_LEDOFF);
        bsm_TNStop();
        break;
    }
}

/************************************************************************

 FUNCTION:   uim_ModemWarning_AlertTone_15Minutes

 DESCRIPTION:  Controls the Modem LED flashing and Alert Tone
               configured for 15 minute duration
               (15 minute Alert Tone required for 2020C Monitor)

************************************************************************/
void uim_ModemWarning_AlertTone_15Minutes(void)
{
    uim_StrobePhoneLeds(OFF);
    bsm_LDChange(bsc_LEDDATA1, bsc_LEDON);
    bsm_LDChange(bsc_LEDNODIALTONE, bsc_LEDFASTFLASH);

#ifdef NO_TONES
    return;
#endif
    // Setup Alert Tone to output 5 beeps in 5 secs occuring
    // approximately every 28 secs for a total duration of 15 minutes
    bsm_TNSound(500,                    // Alert On time (5 secs)
                2200,                   // Alert Off time (22 secs)
                90000,                  // Alert Duration (900 secs = 15 minutes)
                bsc_TONEHIGH,   // High frequency tone
                bsc_FASTBEEP);  // Beep length (200 msecs ON/1000 msecs OFF)
}

/************************************************************************

 FUNCTION:   uim_ModemStart

 DESCRIPTION:  Controls the flashing of the first modem LED.

************************************************************************/
void uim_ModemStart(bool state)
{
    switch (state)
    {
    case ON:   bsm_LDChange(bsc_LEDDATA1, bsc_LEDON);
        break;
    case OFF:
    default:   bsm_LDChange(bsc_LEDDATA1, bsc_LEDOFF);
        break;
    }
}
/************************************************************************

 FUNCTION:   uim_UploadFailure

 DESCRIPTION:  Controls the modem LED flashing and alert tone.

************************************************************************/
void uim_UploadFailure(void)
{
    uim_StrobePhoneLeds(false);
    bsm_LDChange(bsc_LEDNODIALTONE, bsc_LEDFASTFLASH);
    uim_AlertTone();
}
/************************************************************************

 FUNCTION:   uim_StrobePhoneLeds

 DESCRIPTION: Controls the strobing of the 3 phone line LEDs.

************************************************************************/
void uim_StrobePhoneLeds(bool state)
{

    if (true == state)
        bsm_LDChange(bsc_LEDDATA1,bsc_LEDSTROBE);
    else
    {
        bsm_LDChange(bsc_LEDDATA1,bsc_LEDOFF);
        bsm_LDChange(bsc_LEDDATA2,bsc_LEDOFF);
        bsm_LDChange(bsc_LEDDATA3,bsc_LEDOFF);
    }

}

#ifdef EPR
/************************************************************************

 FUNCTION:   uim_EPRWarning

 DESCRIPTION: Signifies that the EPR is not in the socket.

************************************************************************/
void uim_EPRWarning(bool onOff)
{

    static bool eprWarningState = off;

    if (eprWarningState != onOff)
    {
        if (onOff == true)
        {
            // stop the flashing progress LED
            bsm_LDChange(AIC_PROGRESS_LEDS[v_flashingTelemetryLed], bsc_LEDOFF);
            // turn BAD EPR LED on
            bsm_LDChange(bsc_LEDBADEPR, bsc_LEDFASTFLASH);
            // initialize tone timers to sound the warning tone
            uim_AlertTone();
        }
        else
        {
            // turn on progress leds
            // turn the BAD EPR LED off
            // turn the tone timers off
            bsm_LDChange(AIC_PROGRESS_LEDS[v_flashingTelemetryLed], bsc_LEDFASTFLASH);
            bsm_LDChange(bsc_LEDBADEPR, bsc_LEDOFF);
            bsm_TNStop();

        }
        eprWarningState = onOff;
    }
}

#endif

/*
***********************************************************************

 FUNCTION:   uim_ModemTransferComplete

 DESCRIPTION:
This function is called when the  transfer of the file via modem is
finished. The phone progress LEDs are all turned OFF, the
upload-complete LED is turned ON, and complete tone is sounded.

***********************************************************************
*/

void uim_ModemTransferComplete(void)
{
    // sound the interrogation complete tone
    uim_CompleteTone();

    bsm_LDChange(bsc_LEDDATA1, bsc_LEDOFF);
    bsm_LDChange(bsc_LEDDATA2, bsc_LEDOFF);
    bsm_LDChange(bsc_LEDDATA3, bsc_LEDOFF);

    bsm_LDChange(bsc_LED_CHECKMARK, bsc_LEDON);

}

/************************************************************************

 FUNCTION:   uim_POSTInProgress
 DESCRIPTION:
Turn on the Ready LED.

***********************************************************************
*/

void uim_POSTInProgress(void)
{
    bsm_LDChange(bsc_LEDREADY, bsc_LEDFASTFLASH);

}

/*
***********************************************************************

 FUNCTION:   uim_DisplayReady
 DESCRIPTION:
Turn on the Ready LED.

***********************************************************************
*/

void uim_DisplayReady(void)
{
    bsm_LDChange(bsc_LEDREADY, bsc_LEDON);

}

/*
***********************************************************************

 FUNCTION:   uim_BatteryWarning

 DESCRIPTION:
Start the battery LED ON and sound the alert tone.

***********************************************************************
*/

void uim_BatteryWarning(void)
{
    bsm_LDChange(bsc_LEDREADY, bsc_LEDOFF);
    bsm_LDChange(bsc_LEDLOWBATT, bsc_LEDFASTFLASH);
    uim_AlertTone();
}

/*
***********************************************************************

 FUNCTION: uim_SWUpdateComplete

 DESCRIPTION:

Sounds the "complete" tone, turns off all modem LEDs,
and turns on the "Complete" LED.

***********************************************************************
*/
void uim_SWUpdateComplete(void)
{

    // sound the interrogation complete tone
    uim_CompleteTone();

    bsm_LDChange(bsc_LEDDATA1, bsc_LEDOFF);
    bsm_LDChange(bsc_LEDDATA2, bsc_LEDOFF);
    bsm_LDChange(bsc_LEDDATA3, bsc_LEDOFF);

    bsm_LDChange(bsc_LED_CHECKMARK, bsc_LEDON);

}

/*
***********************************************************************

 FUNCTION: uim_SWUpdateFail

 DESCRIPTION:

Sounds the "complete" tone, turns off all modem LEDs,
and turns on the "Complete" LED.

***********************************************************************
*/
void uim_SWUpdateFail(void)
{
    // sound the interrogation complete tone
    uim_CompleteTone();

    bsm_LDChange(bsc_LEDDATA1, bsc_LEDOFF);
    bsm_LDChange(bsc_LEDDATA2, bsc_LEDOFF);
    bsm_LDChange(bsc_LEDDATA3, bsc_LEDOFF);

    bsm_LDChange(bsc_LED_CHECKMARK, bsc_LEDON);
}
