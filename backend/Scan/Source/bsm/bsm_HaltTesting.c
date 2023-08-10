/************************************************************************
*
* MODULE: bsm_HaltTesting.c
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This is the Highly Accelerated Life Testing (HALT) function.
*
*************************************************************************/

/////////////
// Includes
/////////////

#include "global.h"
#include "bsm_global.h"
#include "nwm_net.h"
#include "uim_ui.h"
#include "tbm_main.h"
#include "tbm_handler.h"
#include "tbm_rcv.h"
#include "tam_global.h"

#ifdef __2490TELEMA__
#include "aim_kappa.h"
#endif

#include <string.h>

extern int ltoa(long, char*);

/******************************************************************

FUNCTION: bsm_HaltTesting

DESCRIPTION: This function exercises all of the functionality of the
             unit.

ARGS:
        <none>

RETURNS:
    <none>

******************************************************************/
void bsm_HaltTesting(void)
{
    bst_POSTERR   postError;
    char          mdmResponse[64];
    bst_Led       Led;
    UINT32        LoopCounter = 0;
    UINT32        Time;
    unsigned long deviceId;
    unsigned long submodelId;

    tbt_autoIDRespType DeviceResponse;
    tbt_reqStatus      Status;
    unsigned short     tbv_ProgrammerID;
    UINT16             ConnectStatus;

    bsm_SDPrint("Starting HALT Testing");
    while(1)
    {
        LoopCounter++;

        ltoa(LoopCounter, mdmResponse);
        bsm_SDWrite("HALT Loop Number: ", 18);
        bsm_SDPrint(mdmResponse);

        GLB_GET_LTMR(Time);
        ltoa(Time/LTMR_TICKS_PER_SECOND, mdmResponse);
        bsm_SDWrite("Elapsed Time (seconds): ", 24);
        bsm_SDPrint(mdmResponse);

        postError = bsm_CheckHardware();
        if( postError == bsc_POST_OK )
        {
            bsm_SDPrint("Flash, SDRAM, and DAA OK");
            uim_DisplayReady();
        }
        else if( postError == bsc_POST_MDM_FAILED )
        {
            bsm_SDPrint("ERROR: Modem Failed!");
        }
        else if( postError == bsc_POST_ROM_FAILED )
        {
            bsm_SDPrint("ERROR: ROM Failed!");
        }
        else if( postError == bsc_POST_VOLTS_FAILED )
        {
            bsm_SDPrint("ERROR: Volts Failed!");
        }
        else if( postError == bsc_POST_RAM_FAILED )
        {
            bsm_SDPrint("ERROR: RAM Failed!");
        }
        else
        {
            bsm_SDPrint("ERROR: Something Failed!");
        }
#ifdef __2490TELEMA__
        // AutoId Device and send resume command immediately.
        tam_Initialize_TelemetryA(tac_L88TelemProtocol);

        if( aim_KappaAutoIdA(&deviceId, &submodelId) )
        {
            bsm_SDPrint("Found a device");
            uim_ModemStart(TRUE);
        }
        else
        {
            bsm_SDPrint("ERROR: Did not find a device");
        }
#endif
#ifdef __2490TELEMB__

        tbm_telemBInitialize();

        Status = tbm_telemBAutoID(&DeviceResponse, tbv_ProgrammerID);

        if( DeviceResponse.numberFound == 1)
        {
            bsm_SDPrint("Found a device");
        }
        else
        {
            bsm_SDPrint("ERROR: Did not find a device");
        }

        tbm_telemBDeactivate();

#endif

        bsm_setModemState(ON);
        // Connect to the computer modem
        ConnectStatus = nwm_Dial_and_Connect((BYTE*)"123-4567");
        if( ConnectStatus == NWC_CONNECT || ConnectStatus == NWC_OK )
        {
            int ModemSpeed;
            int Characters;

            bsm_SDPrint("Connected");

            // wait 10 seconds
            GLB_LTMR_WAIT(60000UL);

            bsm_SDPrint("Are we still connected?");

            ModemSpeed = mdm_Get_Connect_Speed();

            if( ModemSpeed != 0 )
            {
                bsm_SDPrint("Modem stayed connected");
            }
            else
            {
                bsm_SDPrint("ERROR: Modem not connected");
            }
            // hang up the modem
            mdm_Send_Control_String(MDM_HANGUP_STR, mdmResponse, sizeof(mdmResponse) );
        }
        else
        {
            bsm_SDPrint("ERROR: Did not connect to remote computer");
        }

        bsm_setModemState(OFF);

        for( Led = (bst_Led)0; Led < bsc_MAXLEDS; Led++ )
        {
            bsm_LDChange(Led, bsc_LEDFASTFLASH);
        }

        // turn on the high tone
        bsm_TNSound(100, 0, 10, bsc_TONEHIGH, bsc_ONBEEP);

        // wait 3 seconds to look at the LEDs and listen to the tone
        GLB_LTMR_WAIT(3000);

        for( Led = (bst_Led)0; Led < bsc_MAXLEDS; Led++ )
        {
            bsm_LDChange(Led, bsc_LEDOFF);
        }

        // turn off the tone.
        bsm_TNStop();
    }
}
