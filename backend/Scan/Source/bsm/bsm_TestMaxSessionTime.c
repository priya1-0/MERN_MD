/************************************************************************
*
* MODULE: bsm_TestMaxSessionTime.c
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION:
*
*************************************************************************/

/////////////
// Includes
/////////////

#include "global.h"
#include "bsm_global.h"
#include "tam_global.h"
#include "cx077.h"
#include "nwm_net.h"
#include "2490G_Defaults.h"
#include "uim_ui.h"

#include <stdio.h>
#include <string.h>

char mdmCommandTest[MDM_STRING_64]; //temp string for modem Commands and general string usage
char mdmResponseTest[MDM_STRING_64]; //temp string for modem responses

extern UINT16 nwm_Dial_Sequence(int dial_attempt);

#define INTERROGATE_TIME 3                      //Interrogation time in minutes
#define UPLINK_TIME      90                             //Uplink time in seconds.

/******************************************************************

FUNCTION: bsm_TestMaxSessionTime

DESCRIPTION: This function simulates the maximum session time for
             a device.

ARGS:
        <none>

RETURNS:
    <none>

******************************************************************/
void bsm_TestMaxSessionTime(void)
{
    UINT16              status;
    UINT32              speed; //Holds connect speed
    UINT16              DialStatus;
    GLB_LTMR_OBJ        startTime;
    bst_ToneSwitchState TPSwitch;

    UINT16 i;
    BYTE   downlinkMessage[] = {0,0,0,0};
    BYTE   uplinkMessage[5];
    UINT16 dial_attempts     = 1;

    bsm_SDPrint("*** Starting CLM Session Simulation for Telemetry A ***");
    tam_Initialize_TelemetryA(tac_GemTelemProtocol);

    uim_InterrogationStarted();

    // Five is the total interrogation size for the
    // uim_InterrogationProgress function progress.
    uim_AddToEstimatedSize(5);

    //Start Telemetry A Session for 3 min
    bsm_SDPrint("\r*** Starting Telemetry A session ***");
    for( i = 0; i < INTERROGATE_TIME*2; i++ )
    {
        UINT16       index=0;
        GLB_LTMR_OBJ Time;

        switch(i) {
        case 0:
            break;
        case 1:
            uim_InterrogationProgress(1);
            break;
        case 2:
            uim_InterrogationProgress(1);
            break;
        case 3:
            uim_InterrogationProgress(1);
            break;
        case 4:
            uim_InterrogationProgress(1);
            break;
        default:
            break;
        }

        GLB_GET_LTMR(Time);
        while( !GLB_HAS_LTMR_EXPIRED(Time, 30000) )
        {
            char spinner[4] = {'|','/','-','\\'};
            //send backspace
            index++;
            index %= 4;
            bsm_SDWrite("\b", 1);
            bsm_SDWrite(&spinner[index], 1);
            tam_Send_Telemetry(downlinkMessage, sizeof(downlinkMessage), uplinkMessage, sizeof(uplinkMessage), 200);
        }
    }
    uim_InterrogationComplete();

    //Start Telemetry A Repeat Downlink
    bsm_SDPrint("\r***Starting Telemetry A repeat***");
    tam_Repeat_Downlink(downlinkMessage, sizeof(downlinkMessage), 2);

    //Start Modem and dial
    // Turn on Progression of Modem LEDs
    uim_ModemStart(ON);

    // set the credentials
    setNVDefaultsForDevelopment();

    status = bsm_setModemState(ON);
    // Handle modem init error if in error
    if(status != MDM_ERRORCODE__NO_ERROR)
    {
        bsm_SDPrint("Modem init failed before running modem, stopping modem testing");
        sprintf(mdmCommandTest, "error: %d", status);
        bsm_SDPrint(mdmCommandTest);
    }
    else
    {
        DialStatus = nwm_Dial_Sequence(dial_attempts);

        if( DialStatus != NWC_OK && DialStatus != NWC_CONNECT )
        {
            uim_AlertTone();
            bsm_PMShutDown();
        }

        // Check connect speed
        speed = mdm_Get_Connect_Speed();
        sprintf(mdmResponseTest, "***Connected at: %lu***", speed);
        bsm_SDPrint(mdmResponseTest);

        uim_StrobePhoneLeds(ON);

        // Purge input buffer
        mdm_Purge_Input_Buffer();

        // Init the terminal mode
        mdm_Init_Term_Mode();

        // Send a string over the modem
        sprintf(mdmCommandTest, "***Hello World, I am the 2490G CLM!  :)***\r");
        status = mdm_Send_String(strlen(mdmCommandTest), mdmCommandTest);
        sprintf(mdmCommandTest, "***Sent %d characters through modem***", status);
        bsm_SDPrint(mdmCommandTest);

        //Terminal Emulation
        GLB_GET_LTMR(startTime);
        while(GLB_HAS_LTMR_EXPIRED(startTime, UPLINK_TIME*(UINT32)LTMR_TICKS_PER_SECOND) == FALSE)
        {

            // forward received characters from the modem to serial port
            status = mdm_Get_Char(sizeof(mdmCommandTest), mdmCommandTest);
            if(status > 0)
            {
                //null terminate the string
                mdmCommandTest[status] = 0;

                //Forward out serial port
                bsm_SDWrite(mdmCommandTest, status);
                mdm_Send_String(status, mdmCommandTest);
            }

            //forward character line from modem through modem
            status = bsm_SDReadBytes((BYTE*)mdmCommandTest, sizeof(mdmResponseTest));
            if(status > 0)
            {
                bsm_SDWrite(mdmCommandTest, status);
                mdm_Send_String(status, mdmCommandTest);
            }
        }
        //hangup Modem
        strcpy(mdmCommandTest, MDM_HANGUP_STR);
        bsm_SDPrint(mdmCommandTest);
        mdm_Send_Control_String(mdmCommandTest, mdmResponseTest, sizeof(mdmResponseTest));
        bsm_SDPrint(mdmResponseTest);

        uim_StrobePhoneLeds(OFF);
    }

    bsm_setModemState(OFF);
    uim_ModemTransferComplete();
    //Shutdown the system
    bsm_PMShutDown();
}

