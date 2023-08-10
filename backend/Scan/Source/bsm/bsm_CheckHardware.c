/************************************************************************
*
* MODULE: bsm_CheckHardware.c
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the functions to check the hardware
*
*************************************************************************/

/////////////
// includes
/////////////

#include "global.h"
#include "bsm_CheckHardware.h"
#include "dbg_TestInternalRam.h"
#include "dbg_TestExternalRam.h"
#include "dbg_BurnIn.h"
#include "bsm_DebugPort.h"
#include "bsm_Power.h"
#include "bsm_AppCrc.h"
#include "bsm_General.h"
#include "cx077.h"
#include "com_eepromapp.h"
#include "bsm_SwitchInput.h"
#include "bsm_NVStorage.h"
#include "uim_ui.h"
#include "bsm_serialport.h"
#include "bsm_Event.h"

////////////
// globals
////////////


/******************************************************************

FUNCTION: bsm_CheckHardware

DESCRIPTION: This function checks all the hardware in the unit.  It
             also checks for a host computer attached to the serial
             port.

ARGS:
        <none>

RETURNS:
        Returns any failures with the hardware

******************************************************************/
bst_POSTERR bsm_CheckHardware(void)
{
    int mdm_status;

    bst_POSTERR status = bsc_POST_OK;

    // Check for Burn-In Test pin high
    if( bsm_INReadBurnInPin() )
    {
        BurnInTest();
    }

    //set the UI to POST In Progress
    uim_POSTInProgress();

    // Check for a host computer connected to the serial port
    bsm_CheckDebugPort();

    // start up the modem
    mdm_status = bsm_setModemState(ON);
    bsm_setModemState(OFF);

    // Check the Modem
    if(mdm_status != MDM_ERRORCODE__NO_ERROR)
    {
        bsm_EHLog("Modem failure in POST.", mdm_status);
        status = bsc_POST_MDM_FAILED;
    }

    if( status == bsc_POST_OK )
    {
        // Check the Flash
        if( !bsm_CheckProgram() )
        {
            bsm_EHLog("ROM (Flash) Test Failed in POST.",0);
            status = bsc_POST_ROM_FAILED;
        }
    }

    if( status == bsc_POST_OK )
    {
        // test the internal and external RAM
        if( !TestSdram() ||
            !TestInternalRam() )
        {
            bsm_EHLog("RAM Test Failed in POST.",0);
            status = bsc_POST_RAM_FAILED;
        }
    }

    if( status == bsc_POST_OK )
    {
        // Turn on the dummy load to let the battery sink some current.
        bsm_EnableDummyLoad();

        // Wait 1 second for the battery to lose some electrons.
        GLB_LTMR_WAIT(1000);

        // check the battery
        if( !bsm_IsBatteryGood() )
        {
            bsm_EHLog("Voltage test failed in POST.",0);
            status = bsc_POST_VOLTS_FAILED;
        }

        bsm_DisableDummyLoad();
    }

    return status;
}
