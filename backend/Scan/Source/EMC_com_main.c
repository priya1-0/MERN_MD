/************************************************************************
*
* MODULE: com_main.c
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This is main application which is responsible for controlling
* the flow of the 2490 Processsing.
*
*************************************************************************/

/////////////
// Includes
/////////////

#include "global.h"
#include "bsm_global.h"
#include "nwm_net.h"
#include "uim_ui.h"

#ifdef DSP_2490_SIMULATION
  #include "device_sim.h"
  #include "fsm_encrypt.h"
  #include "fsm_file.h"
  #include "fsm_pbfr.h"
#endif

#ifdef ITEM_TEST
  #include "tam_ItemMap.h"
#endif

#include "bsm_DebugPort.h"

#include "cx077.h" //Modem header file

#include "tbm_handler.h"

#include "tbm_main.h"


#include <csl_icache.h>
#include <string.h>



////////////
// Defines
////////////

// Watchdog timer
#define ENABLE_WATCHDOG()
#define DISABLE_WATCHDOG()

////////////
// Globals
////////////


////////////
// Externs
////////////

// These two external functions are supplied by the specific
// application being built.
extern bool aim_CheckForDevice(void);
extern int aim_Interrogate(void);

////////////////////////////////////////////////////////////////////////////////
//
//  com_MainTask
//
////////////////////////////////////////////////////////////////////////////////
void com_MainTask()
{
    bst_POSTERR postError;
    int         x;

    char mdmResponse[256];

    bool firstTime = true;

    // Enable the watchdog timer
    ENABLE_WATCHDOG();

    bsm_EEInit();

    while (1)
    {
        //shut off modem
        bsm_setModemState(OFF);

        // Run POST if coming through the first time, or if the
        // DIAL prefix switch is closest to the front.

        if ((bsm_INReadDial() == bsc_DIAL1) || (firstTime))
        {
            uim_POSTInProgress();

            // check all the hardware
            postError = bsm_CheckHardware();

            // if the battery voltage failed...
            if (postError == bsc_POST_VOLTS_FAILED)
            {
                bsm_PMEnableButton();
                uim_BatteryWarning();
                GLB_LTMR_WAIT(120000);
                bsm_PMShutDown();
            }


            // if there were any other errors, just fail and shutdown
            if (postError != bsc_POST_OK)
            {
                uim_ErrorTone();
                bsm_EHLock("POST Failed.");
            }

            firstTime = false;

        }


        uim_DisplayReady();

        // Enable the start button shutdown feature
        bsm_PMEnableButton();

        // Interrogation
        uim_InterrogationStarted();
        uim_AddToEstimatedSize(10000);

        // Interrogate

        for (x = 0; x <= 4000; x+=200)
        {
            uim_InterrogationProgress(x);

            if (x == 600)
            {
                // Oops - lost telemetry
                uim_TelemetryWarning(ON);
                NU_Sleep(400);

                // Whew! We have telemetry
                uim_TelemetryWarning(OFF);
            }

            NU_Sleep(300);
        }

        // Sound the "Complete" tone.
        uim_InterrogationComplete();

        uim_ModemStart(ON);
        NU_Sleep(200);

        uim_ModemWarning(ON);
        NU_Sleep(400);

        uim_ModemWarning(OFF);

        uim_StrobePhoneLeds(ON);

        if (bsm_INReadTonePulse() == bsc_TONE)
        {

            // This is required for all device/telemetries.
            // Tachy-Telemetry A, Brady-Telemetry A, and Tachy-Telemetry-B
            tbm_telemBDeactivate();

            //initialize Modem
            (void)bsm_setModemState(ON);

            // Speaker on till connect
            mdm_Send_Control_String("ATM1\r", mdmResponse, sizeof(mdmResponse));
            bsm_SDPrint(mdmResponse);

            // Loud
            mdm_Send_Control_String("ATL3\r", mdmResponse, sizeof(mdmResponse));
            bsm_SDPrint(mdmResponse);

            // Dial something
            mdm_Send_Control_String("ATDT*******\r", mdmResponse, sizeof(mdmResponse));
            bsm_SDPrint(mdmResponse);

            NU_Sleep(400);

            // Go to command mode, go on-hook
            mdm_Send_Control_String("+++ATH0\r", mdmResponse, sizeof(mdmResponse));
        }

        else
        {
            NU_Sleep(2000);
        }


        uim_ModemTransferComplete();

        NU_Sleep(12000);

        bsm_LDChange(bsc_LED_CHECKMARK, bsc_LEDOFF);


    }
}

////////////////////////////////////////////////////////////////////////////////
//
//  main
//
////////////////////////////////////////////////////////////////////////////////
void main()
{
    ioport int *CLKOUTSR;

    // The following 2 assembly lines correct a "bug" in DSP/BIOS.
    // The value of GBL_initdone is hard coded in a code section.  This
    // is burned into the Flash.  Once all the initialization is done,
    // this variable is set to 1.  But when we check the Flash against the
    // RAM, this becomes an error because it looks like a byte of execution code
    // changed.  We reset the variable back to a 0.
    asm ("	.ref GBL_initdone");
    asm ("	*(#GBL_initdone) = #0");

    ICACHE_enable();

    // Turn off the CLKOUT output
    CLKOUTSR  = (ioport int*)0x8400;
    *CLKOUTSR = *CLKOUTSR | 1;

    //Allow modem to make backup of initiailized section of DARAM
    mdm_Store_Data();

    bsm_initDAA();       //init of DAA
    bsm_LedInit();
    bsm_PowerInit();
    bsm_ToneInit();
    bsm_SDInit();
    bsm_INInit();
}



