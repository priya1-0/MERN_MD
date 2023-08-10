/************************************************************************
*
* MODULE: dbg_BurnIn.c
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the function for the Burn In.
*
*************************************************************************/

/////////////
// Includes
/////////////
#include "global.h"
#include "bsm_serialport.h"
#include "tam_TelemetryA.h"
#include "bsm_Led.h"
#include "dbg_TestExternalRam.h"
#include "dbg_TestInternalRam.h"
#include "bsm_AppCrc.h"
#include "bsm_Event.h"
#include "bsm_tone.h"
#include "bsm_general.h"
#include "cx077.h"
#include "tbm_handler.h"
#include "bsm_nvstorage.h"

#include <string.h>

#include <csl_gpio.h>

////////////
// Defines
////////////
#define BURN_IN_TEST_NOT_RUN 0xFFFF
#define BURN_IN_TEST_FAILED  0x0000
#define BURN_IN_TEST_PASSED  0xABCD

/******************************************************************

FUNCTION: BurnInTest

DESCRIPTION: This function tests the Internal RAM, External RAM,
             exercises the LEDs, Tone, and Transmit functionality

ARGS:
        <none>

RETURNS:
    <none>

******************************************************************/
#define RX_BUFFER_SIZE 5
BYTE Buffer[RX_BUFFER_SIZE];
void BurnInTest(void)
{
    bst_Led Led     = (bst_Led)0;

    BYTE Message5[] = {0xc1, 0x00, 0x00, 0xc1, 0x00, 0x00, 0x00};     // From item mapper

    tat_status         Status;
    tbt_autoIDRespType tbv_DeviceIDResp;
    UINT16             tbv_ProgrammerID;

    BOOL FirstTime = TRUE;
    BYTE BurnInStatus[2];


#ifdef __2490TELEMA__
    tam_Initialize_TelemetryA(tac_L88TelemProtocol);
#endif

    bsm_EEReadBuf(BurnInStatus, 2, coc_BurnInTestStaus_ADDR);

    if( (BurnInStatus[0] | (BurnInStatus[1]<<8)) != BURN_IN_TEST_FAILED )
    {
        while(1)
        {
            bsm_TNSound(100, 0, 100, bsc_TONEHIGH, bsc_ONBEEP);

            if(TestInternalRam() == FALSE)
            {
                bsm_EHLog("Burnin: Internal RAM failed (DSP).", FALSE);            // Log the failure.
                break;
            }

            if(TestSdram() == FALSE)
            {
                bsm_EHLog("Burnin: SDRAM failed (SDRAM).", FALSE);            // Log the failure.
                break;
            }

            bsm_TNStop();
        #ifdef __2490TELEMA__
            tam_Send_Telemetry(Message5, sizeof(Message5), (BYTE*)Buffer, RX_BUFFER_SIZE, 100);
        #endif
        #ifdef __2490TELEMB__
            tbm_telemBInitialize();
            tbm_telemBAutoID(&tbv_DeviceIDResp, tbv_ProgrammerID);
            tbm_telemBClose();
            tbm_telemBDeactivate();
        #endif
            if(bsm_CheckProgram() == FALSE )
            {
                bsm_EHLog("Burnin: Flash Image failed (Flash).", FALSE);            // Log the failure.
                break;
            }

            if( bsm_setModemState(ON) != MDM_ERRORCODE__NO_ERROR )
            {
                bsm_EHLog("Burnin: Modem Initialization failed (DAA).", FALSE);            // Log the failure.
                break;
            }
            bsm_setModemState(OFF);

            // Only cycle through the populated LEDs
            bsm_LDChange(Led, bsc_LEDOFF);
            Led++;
            if( Led > bsc_LED_CHECKMARK )
            {
                Led = (bst_Led)0;
            }
            bsm_LDChange(Led, bsc_LEDFASTFLASH);

            if( FirstTime )
            {
                FirstTime       = FALSE;

                BurnInStatus[0] = (BURN_IN_TEST_PASSED >> 0) & 0xFF;
                BurnInStatus[1] = (BURN_IN_TEST_PASSED >> 8) & 0xFF;

                bsm_EEWriteBuf(BurnInStatus, 2, coc_BurnInTestStaus_ADDR);
                bsm_EEFlush();
            }
        }
    }

    BurnInStatus[0] = (BURN_IN_TEST_FAILED >> 0) & 0xFF;
    BurnInStatus[1] = (BURN_IN_TEST_FAILED >> 8) & 0xFF;

    bsm_EEWriteBuf(BurnInStatus, 2, coc_BurnInTestStaus_ADDR);
    bsm_EEFlush();

    // On an error, turn all the LEDs off, and turn on the LED Extra2 because it has a testpoint.
    for( Led = (bst_Led)0; Led < bsc_MAXLEDS; Led++ )
    {
        bsm_LDChange(Led, bsc_LEDOFF);
    }

    bsm_LDChange(bsc_EXTRA2, bsc_LEDON);

    while(1) ;
}
