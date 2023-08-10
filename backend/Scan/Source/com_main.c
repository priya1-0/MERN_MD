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
#include "aim_kappa.h"
#include "bsm_global.h"
#include "nwm_net.h"
#include "uim_ui.h"

#ifdef DSP_2490_SIMULATION
#include "device_sim.h"
#endif

#ifdef ITEM_TEST_TELEMA
  #include "tam_ItemMap.h"
#endif
#ifdef ITEM_TEST_TELEMB
extern void dbg_itemTestApp(char testType);
#endif

#include "tbm_handler.h"

#ifdef HALT_TESTING
#include "bsm_HaltTesting.h"
#endif

#ifdef MAX_SESSION_TIME_TEST
#include "bsm_TestMaxSessionTime.h"
#endif

#ifdef SKIP_INTERROGATION
#warn "WARNING: Skip Interrogation"
#include "fsm_pbfr.h"
#endif //End of SKIP_INTERROGATION

#ifdef EMC_TESTING
#include "tam_global.h"
#endif

#ifdef TEST_HA1
#include "nwm_httpdigest.h"
#endif

#ifdef TEST_NET_HTTP
#include "nwm_http.h"
#include "nwm_net.h"
#endif

#ifdef VOCAL_TESTING
#include "bsm_serialport.h"
#include <stdio.h>
#endif


#include <csl_icache.h>
////////////
#include <csl_wdtim.h>
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

#ifdef DEVELOPMENT_NV_DEFAULTS

#include "2490G_Defaults.h"

#endif

////////////////////////////////////////////////////////////////////////////////
//
//  com_MainTask
//
////////////////////////////////////////////////////////////////////////////////
void com_MainTask()
{
    bst_POSTERR postError;

#ifdef VOCAL_TESTING
    int  counter =0;
    char output[100];
#endif

    // Set the watchdog counter
    WDTCNT1  = 0;
    WDTCNT2  = 0;
    WDTCNT3  = 0;
    WDTCNT4  = 0;

    // Set the watchdog period to 1 second
    WDTPRD1  = ((CPU_FREQ/FAST_PERIPH_CLK_DIV) & 0x0000FFFF) >> 0;
    WDTPRD2  = ((CPU_FREQ/FAST_PERIPH_CLK_DIV) & 0xFFFF0000) >> 16;
    WDTPRD3  = 0;
    WDTPRD4  = 0;

    WDTCTL1  = 0x0080;
    WDTGCTL1 = 0x000B;
    WDTWCTL1 = 0x4000;

    CHIP_FSET(TSSR, IWCON, 1);
        
    if( !bsm_EEInit() )
    {
        uim_ErrorTone();
        // Shut down without flushing to FLASH which
        // should leave the FLASH corrupt on reboot
        bsm_PMShutDownFlashCorrupt(false);
    }

#ifdef __2490TELEMA__
    // Make sure Telemetry B is off when doing Telemetry A.
    tbm_telemBDeactivate();
#endif

#ifdef DEVELOPMENT_NV_DEFAULTS
        #warn "WARNING: Setting NV Defaults for Development."
    setNVDefaultsForDevelopment();
#endif

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

    bsm_SDPrint("POST Passed.");

#ifdef ITEM_TEST_TELEMA
        #warn "WARNING: Item Mapping Test."
    tam_itemMap();
#endif
#ifdef ITEM_TEST_TELEMB
        #warn "WARNING: Item Mapping Test."
    dbg_itemTestApp('U');
#endif

    // Enable the start button shutdown feature
    bsm_PMEnableButton();

    // Turn on the green LED above the start button.
    uim_DisplayReady();

#ifdef MAX_SESSION_TIME_TEST
        #warn "Max Session Time Test."
    bsm_TestMaxSessionTime();
#endif

#ifdef HALT_TESTING
        #warn "HALT Testing Build."
    bsm_HaltTesting();
#endif

#ifdef DSP_2490_SIMULATION
#ifndef __BRADY
        #warn "WARNING: DSP Simulation."
    // for setting up the reading of the *.dm file
    DeviceSimInit();
#endif
#endif

#ifdef MODEM_CONSTANT_TRANSMIT
        #warn "Modem Echo Out Build."
    bsm_modemConstantTransmit();
#endif

#ifdef TEST_HA1
        #warn "Digest Unit Tests ."
    UTest1_calcHA();
    UTest2_calcHA();
#endif

#ifdef TEST_NET_HTTP
        #warn "HTTP and NET initialization Unit Test"
    nwm_GetModemNetwork_Params();
    UTest1_HTTP_Initialization();
#endif



#ifdef EMC_TESTING
        #warn "WARNING: EMC Testing Code"
    while(1)
    {
        tam_Cancel_Repeat_Downlink();
#endif

#ifdef VOCAL_TESTING
        #warn "WARNING: VOCAL Testing Code"
    while(1)
    {
        counter = counter+1;
        sprintf(output, "VOCAL TEST manual TX counter: %d", counter);
        bsm_SDPrint(output);
#endif
#ifdef SKIP_INTERROGATION
#warn "WARNING: Skip Interrogation"
#else
    // AutoId Device and send resume command immediately.
    // (If device is not found but the power button was held throughout,
    // then, 'skipInterrogationCheckFWUpdates' flag is set.)
    aim_CheckForDevice();

    if (!(aim_skipInterrogationCheckFWUpdates()))
    {
        // Interrogate the device
        if (!aim_Interrogate())
        {
            bsm_EHLock("Device Interrogation failed");
        }
    }

#ifdef EMC_TESTING
}
#endif

    // This is required for all device/telemetries.
    // Tachy-Telemetry A, Brady-Telemetry A, and Tachy-Telemetry-B
    tbm_telemBDeactivate();

#endif //End of SKIP_INTERROGATION

#ifdef SKIP_INTERROGATION
#warn "WARNING: Skip Interrogation"
    fsm_PackedBfrInit(FSV_FILE);

#endif //End of SKIP_INTERROGATION

    nwm_Send_Data();

#ifdef VOCAL_TESTING
}
#endif

    bsm_PMShutDown();
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
