/************************************************************************
*
* MODULE: tam_ItemMap.c
*
* OWNER:
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the functions to do an Item Map.
*
* The Hardware Connections:
* -------------------------
* 1.) Remove R232 from 2490G.
* 2.) Mapper CH1-out connects through 3.3K resistor to GPIO-4(U2-pin #2).
* 3.) Mapper CH1-in connects through 1K resistor to LED_ANTENNA_N(U16-pin6).
* 4.) Power: TP17(+) and TP18(-).
* Currently XF is not used.
*
*************************************************************************/

/////////////
// Includes
/////////////
#include "global.h"
#include "tam_TelemetryA.h"
#include "tam_RepeatTask.h"
#include "bsm_global.h"
#include "tam_ItemMap.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

////////////
// Defines
////////////

#define tac_MAP_UPLINK_SIZE 132         // Header 2 bytes, Data bytes (128
                                        // bytes) and trailer 2 bytes (CRC)
#define tac_IPG_MAP_UPLINK_SIZE 35      // Header 2 bytes (Family Id and
                                        // Command Code), Data bytes (32 bytes
                                        // for 1 memory page) Parity byte
                                        // (1 bytes)
#define tac_MAP_TIMEOUT 100             // item map timeout


///////////
// Macros
///////////
#define InitializeMapperInput() _GPIO_IODIR &= ~GPIO_PIN4
#define ReadMapperInput()       ((_GPIO_IODATA & GPIO_PIN4) ? HIGH : LOW)

#define InitializeMapperOutput() // No Initialization needed
#define SetMapperOutput()        GLB_SET_XF
#define ClearMapperOutput()      GLB_CLR_XF

////////////
// Globals
////////////
bool tav_testDeviceFound = false;
BYTE v_downlinkMessage[7];

// canned downlink messages to a GEM that requests 128
// bytes starting at address 0x1000
// Last two bytes are crc and are overwritten by code.
BYTE v_7227TestMessage[] = {0x4B, 0x00, 0x7F, 0x10, 0x00, 0x00, 0x00};
BYTE v_7229TestMessage[] = {0x65, 0x00, 0x7F, 0x10, 0x00, 0x00, 0x00};
BYTE v_7231TestMessage[] = {0xC6, 0x00, 0x7F, 0x10, 0x00, 0x00, 0x00};
BYTE v_7271TestMessage[] = {0x4F, 0x00, 0x7F, 0x10, 0x00, 0x00, 0x00};
BYTE v_7275TestMessage[] = {0xCC, 0x00, 0x7F, 0x10, 0x00, 0x00, 0x00};
BYTE v_7273TestMessage[] = {0xC3, 0x00, 0x7F, 0x10, 0x00, 0x78, 0x09};

///////////////
// Prototypes
///////////////
tat_status tam_Perform_Universal_Map(void);
tat_status tam_Perform_IPG_Universal_Map(void);


/******************************************************************

FUNCTION: tam_itemMap

DESCRIPTION:  This function will perform a complete Telemetry A item
              map with an ICD (any GEM) or IPG (Kappa VDD 700).  The
              host system must be the 2490G board with the follow
              connected to the ITEM Mapping System:
  - ITEM Map Input: GPIO4
  - ITEM Map Output: XF

                          Once, this item map is initiated the only way to stop
                          or get out of item mapping is to shut the system down.

                          Note: Telemetry protocol (GEM or KAPPA) will be based
                          on the dial switch setting (GEM = None and
                          KAPPA = 7,8 or 9).
ARGS:
        <none>

RETURNS:
        <none>

******************************************************************/
void tam_itemMap(void)
{
    USHORT     counter = 0;          // counter used to control LEDs
    char       stdoutBuffer[50];     // send information to debug port
    tat_status v_status;             // status of telemtry

    InitializeMapperInput();
    InitializeMapperOutput();

    SetMapperOutput();

    // send information to debug port
    bsm_SDPrint("Universal Mapping Software - Initiating ITEM MAPPING");

    if (bsm_INReadDial() == bsc_DIAL1)
    {
        tam_Initialize_TelemetryA(tac_GemTelemProtocol);
    }
    else
    {
        tam_Initialize_TelemetryA(tac_L88TelemProtocol);
    }

    // continueously running mapping test, until power down
    while (1)
    {
        // send test number to debug port
        stdoutBuffer[0] = 0;
        strcat(stdoutBuffer, "Test Number: ");
        ltoa(counter + 1, &stdoutBuffer[strlen(stdoutBuffer)]);

        bsm_SDPrint(stdoutBuffer);

        // use LEDs to indicate test is running, turn on
        // next led is progress meter
        if ((counter % 5) == 0)
            bsm_LDChange(bsc_LEDPROGRESS1, bsc_LEDON);
        else if ((counter % 5) == 1)
            bsm_LDChange(bsc_LEDPROGRESS2, bsc_LEDON);
        else if ((counter % 5) == 2)
            bsm_LDChange(bsc_LEDPROGRESS3, bsc_LEDON);
        else if ((counter % 5) == 3)
            bsm_LDChange(bsc_LEDPROGRESS4, bsc_LEDON);
        else if ((counter % 5) == 4)
            bsm_LDChange(bsc_LEDPROGRESS5, bsc_LEDON);

        // If dial properties set to PULSE then free-run
        // the program to see that it is running.
        // Otherwise, use the Item Mapper.
        if (bsm_INReadTonePulse() == bsc_PULSE)
        {
            NU_Sleep(100);
        }
        else
        {
            // wait, until input trigger goes low from item mapper
            while(ReadMapperInput() == HIGH)
            {
                NU_Sleep(10);  // sleep for 100 msec.
            }
        }

        // check to see if input signal from mapper is still low
        if ((ReadMapperInput() == LOW) || (bsm_INReadTonePulse() == bsc_PULSE))
        {
            ClearMapperOutput();

            // pull output signal low in preparation for next mapping
            // request
            bsm_LDChange(bsc_LEDBADANTENNA, bsc_LEDON);

            // Determine which mapping to perform based on dial switch
            // if switch is set to NONE, perform ICD map
            // if switch is set to 7,8 or 9 perform IPG map
            if (bsm_INReadDial() == bsc_DIAL1)
                v_status = tam_Perform_Universal_Map();
            else
                v_status = tam_Perform_IPG_Universal_Map();


            if (v_status == tac_successful)
            {
                // pull output signal high to indicate successful to
                // ITEM Mapping System
                bsm_LDChange(bsc_LEDBADANTENNA, bsc_LEDOFF);
                bsm_SDPrint("Mapping: Successful");

            }
            else
            {
                // failure output information to debug port
                stdoutBuffer[0] = 0;
                strcat(stdoutBuffer, "Mapping: Failure: ");
                ltoa(v_status, &stdoutBuffer[strlen(stdoutBuffer)]);
                strcat(stdoutBuffer, " - attempt retry");

                bsm_SDPrint(stdoutBuffer);

                // attempt one retry
                if (bsm_INReadDial() == bsc_DIAL1)
                    v_status = tam_Perform_Universal_Map();
                else
                    v_status = tam_Perform_IPG_Universal_Map();

                if (v_status == tac_successful)
                {
                    // pull output signal high to indicate successful to
                    // ITEM Mapping System
                    bsm_LDChange(bsc_LEDBADANTENNA, bsc_LEDOFF);
                    bsm_SDPrint("Mapping: Successful");
                }
                else
                {
                    // pull output signal low to indicate failure to
                    // ITEM Mapping System
                    bsm_LDChange(bsc_LEDBADANTENNA, bsc_LEDON);

                    stdoutBuffer[0] = 0;
                    strcat(stdoutBuffer, "Mapping: Failure: ");
                    ltoa(v_status, &stdoutBuffer[strlen(stdoutBuffer)]);

                    bsm_SDPrint(stdoutBuffer);
                }
            }

            SetMapperOutput();

            // If dial properties set to PULSE then free-run
            // the program to see that it is running.
            // Otherwise, use the Item Mapper.
            if (bsm_INReadTonePulse() == bsc_PULSE)
            {
                NU_Sleep(100);
            }
            else
            {
                // wait, until input signal goes high before continuing with
                // next map
                while(ReadMapperInput() == LOW)
                {
                    NU_Sleep(10);
                }
            }
        }

        // use LEDs to indicate test is running, turn off
        // current led in progress meter
        if ((counter % 5) == 0)
            bsm_LDChange(bsc_LEDPROGRESS1, bsc_LEDOFF);
        else if ((counter % 5) == 1)
            bsm_LDChange(bsc_LEDPROGRESS2, bsc_LEDOFF);
        else if ((counter % 5) == 2)
            bsm_LDChange(bsc_LEDPROGRESS3, bsc_LEDOFF);
        else if ((counter % 5) == 3)
            bsm_LDChange(bsc_LEDPROGRESS4, bsc_LEDOFF);
        else if ((counter % 5) == 4)
            bsm_LDChange(bsc_LEDPROGRESS5, bsc_LEDOFF);

        // increase counter used to control which led is on
        counter++;
        if (counter > 65000)
            counter = 0;

    }
}


/************************************************************************
*
* FUNCTION:     tam_Perform_Universal_Map
*
* DESCRIPTION:
*
* This function will send a canned downlink message intended for an
* ICD (GEM II DR).  Than it will wait for the response.
*
* Note: Prior to this function performing its specified task, it
*       checks that the repeat downlink command is not active.  If
*       the repeat downlink is active, this function returns with
*       a failure and does not attempt to execute its specified task.
*
* FUNCTION CONSTANTS:
*
*   None
*
* FUNCTION DATA:
*
*   Name:    Return value
*   Use:     Indication of the success or failure of sending a
*            downlink and receiving a uplink to/from the device.
*
ENDPURPOSE
*************************************************************************/
tat_status tam_Perform_Universal_Map(void)
{
    tat_status v_status =  tac_unknownError;
    char       stdoutBuffer[50];    // used to send information to debug port
    USHORT     v_uplinkedCRC;       // CRC sent from the device in the uplink
    USHORT     v_calculatedCRC;     // CRC calculated from data in the uplink
    USHORT     v_downlinkLength;

    static bool tav_testDeviceFound = false;

    BYTE v_autoIdMessage[]          = {0x00, 0x00, 0x00, 0x00};
    BYTE v_uplinkMessage[tac_MAP_UPLINK_SIZE];

    /* Check for repeat downlink active mode */
    if (!IsRepeatDownlinkActive())
    {
        // Start the GEM auto-id code here.
        //      If testDeviceFound==false then
        //        auto-id
        //        if auto-id == true then
        //            noDeviceFound=false
        //            copy device specific downlink into v_downlinkMessage
        //            calculate crc
        //        else
        //            auto id failed
        //            do nothing
        //        end if
        //      end if
        //
        //     (a second check is done to catch auto-id failure)
        //
        //     If testDeviceFound == false then
        //       return error
        //
        //  This will then return if autoid fails or skip/continue if device found.
        if (tav_testDeviceFound == false)
        {
            // Signal Auto-Id is being done.
            bsm_SDPrint("Auto-ID of GEM being done.");

            // send auto id message to the GEM
            v_status = tam_Send_Telemetry(  v_autoIdMessage,
                                            sizeof(v_autoIdMessage),
                                            v_uplinkMessage,
                                            5,
                                            tac_MAP_TIMEOUT);

            // received data
            if (v_status == tac_successful)
            {
                // No need to calculate the CRC on auto-id since
                // crc will be calculated on downlink/uplinks which follow.

                // Now determine the model id and set up the
                // specific device downlink/uplink to be used
                // from this point on.

                // byte[0] = the model id.
                switch (v_uplinkMessage[0])
                {
                case 0x4B: // 7227
                    bsm_SDPrint("Found model 7227.");
                    tav_testDeviceFound                   = true;
                    // Copy in the specific downlink to use.
                    memcpy(v_downlinkMessage, v_7227TestMessage, sizeof(v_7227TestMessage));
                    v_downlinkLength                      = sizeof(v_downlinkMessage);
                    v_calculatedCRC                       = aim_CRC(v_downlinkMessage,v_downlinkLength-2);
                    v_downlinkMessage[v_downlinkLength-2] = (BYTE)(v_calculatedCRC & 0x00FF);      // low
                    v_downlinkMessage[v_downlinkLength-1] = (BYTE)((v_calculatedCRC & 0xFF00)>> 8);       // high
                    break;

                case 0x65: // 7229
                    bsm_SDPrint("Found model 7229.");
                    tav_testDeviceFound                   = true;
                    memcpy(v_downlinkMessage, v_7229TestMessage, sizeof(v_7229TestMessage));
                    v_downlinkLength                      = sizeof(v_downlinkMessage);
                    v_calculatedCRC                       = aim_CRC(v_downlinkMessage,v_downlinkLength-2);
                    v_downlinkMessage[v_downlinkLength-2] = (BYTE)(v_calculatedCRC & 0x00FF);      // low
                    v_downlinkMessage[v_downlinkLength-1] = (BYTE)((v_calculatedCRC & 0xFF00)>> 8);       // high
                    break;

                case 0xC6: // 7231
                    bsm_SDPrint("Found model 7231.");
                    tav_testDeviceFound                   = true;
                    memcpy(v_downlinkMessage, v_7231TestMessage, sizeof(v_7231TestMessage));
                    v_downlinkLength                      = sizeof(v_downlinkMessage);
                    v_calculatedCRC                       = aim_CRC(v_downlinkMessage,v_downlinkLength-2);
                    v_downlinkMessage[v_downlinkLength-2] = (BYTE)(v_calculatedCRC & 0x00FF);      // low
                    v_downlinkMessage[v_downlinkLength-1] = (BYTE)((v_calculatedCRC & 0xFF00)>> 8);       // high
                    break;

                case 0x4F: // 7271
                    bsm_SDPrint("Found model 7271.");
                    tav_testDeviceFound                   = true;
                    memcpy(v_downlinkMessage, v_7271TestMessage, sizeof(v_7271TestMessage));
                    v_downlinkLength                      = sizeof(v_downlinkMessage);
                    v_calculatedCRC                       = aim_CRC(v_downlinkMessage,v_downlinkLength-2);
                    v_downlinkMessage[v_downlinkLength-2] = (BYTE)(v_calculatedCRC & 0x00FF);      // low
                    v_downlinkMessage[v_downlinkLength-1] = (BYTE)((v_calculatedCRC & 0xFF00)>> 8);       // high
                    break;

                case 0xCC: // 7275
                    bsm_SDPrint("Found model 7275.");
                    tav_testDeviceFound                   = true;
                    memcpy(v_downlinkMessage, v_7275TestMessage, sizeof(v_7275TestMessage));
                    v_downlinkLength                      = sizeof(v_downlinkMessage);
                    v_calculatedCRC                       = aim_CRC(v_downlinkMessage,v_downlinkLength-2);
                    v_downlinkMessage[v_downlinkLength-2] = (BYTE)(v_calculatedCRC & 0x00FF);      // low
                    v_downlinkMessage[v_downlinkLength-1] = (BYTE)((v_calculatedCRC & 0xFF00)>> 8);       // high
                    break;

                case 0xC3: // 7273
                    bsm_SDPrint("Found model 7273.");
                    tav_testDeviceFound                   = true;
                    memcpy(v_downlinkMessage, v_7273TestMessage, sizeof(v_7273TestMessage));
                    v_downlinkLength                      = sizeof(v_downlinkMessage);
                    v_calculatedCRC                       = aim_CRC(v_downlinkMessage,v_downlinkLength-2);
                    v_downlinkMessage[v_downlinkLength-2] = (BYTE)(v_calculatedCRC & 0x00FF);      // low
                    v_downlinkMessage[v_downlinkLength-1] = (BYTE)((v_calculatedCRC & 0xFF00)>> 8);       // high
                    break;

                default:
                    bsm_SDPrint("Can not decode model.");
                    break;
                }
            }
            else
            {
                bsm_SDPrint("Auto-ID failed - dlnk cmd fail.");
                return(tac_downlinkCommandFailed);
            }
        }
        // check if the auto-id worked
        if (tav_testDeviceFound == false)
            return(tac_unknownError);

        // Stop auto id code here.

        // send message to the GEM
        v_status = tam_Send_Telemetry(  v_downlinkMessage,
                                        sizeof(v_downlinkMessage),
                                        v_uplinkMessage,
                                        tac_MAP_UPLINK_SIZE,
                                        tac_MAP_TIMEOUT);
        // received data
        if (v_status == tac_successful)
        {
            // Calculate CRC on uplink
            v_calculatedCRC = aim_CRC (v_uplinkMessage, tac_MAP_UPLINK_SIZE - 2);
            // perform crc check on uplink
            if (((BYTE)(v_calculatedCRC & 0x00FF) !=
                 v_uplinkMessage[tac_MAP_UPLINK_SIZE - 2]) ||
                (((BYTE)((v_calculatedCRC & 0xFF00) >> 8)) !=
                 v_uplinkMessage[tac_MAP_UPLINK_SIZE - 1]))
            {
                v_status = tac_telemetryCRCError;
                bsm_SDPrint("tac_telemetryCRCError");

            }

            // send crc information to debug port
            v_uplinkedCRC =
                ((USHORT)v_uplinkMessage[tac_MAP_UPLINK_SIZE - 1] << 8) +
                (USHORT)v_uplinkMessage[tac_MAP_UPLINK_SIZE - 2];
            sprintf(stdoutBuffer, "CRC: %x", v_uplinkedCRC);
            bsm_SDPrint(stdoutBuffer);
            sprintf(stdoutBuffer, "Calculated CRC: %x", v_calculatedCRC);
            bsm_SDPrint(stdoutBuffer);
        }
    }
    else
    {
        v_status = tac_repeatDownlinkActive;
    }
    return (v_status);

}


/************************************************************************
*
* FUNCTION:     tam_Perform_IPG_Universal_Map
*
* DESCRIPTION:
*
* This function will send a canned downlink message intended for an
* IPG (Kappa 700).  Then it will wait for the response.
*
* Note: Prior to this function performing its specified task, it
*       checks that the repeat downlink command is not active.  If
*       the repeat downlink is active, this function returns with
*       a failure and does not attempt to execute its specified task.
*
* FUNCTION CONSTANTS:
*
*   None
*
* FUNCTION DATA:
*
*   Name:    Return value
*   Use:     Indication of the success or failure of sending a
*            downlink and receiving a uplink to/from the device.
*
ENDPURPOSE
*************************************************************************/

#include "aim_kappa.h"

#define AIC_KAPPA_A_AUTOID_EXPECTED_UPLINK 4


tat_status tam_Perform_IPG_Universal_Map(void)
{
    tat_status v_status =  tac_unknownError;
    USHORT     v_index;
    char       stdoutBuffer[50];          // used to sent data to the debug port
    BYTE       v_uplinkParity;            // calculated parity of uplink
    BYTE       v_modelId;
    BYTE       v_submodelId;
    USHORT     v_tableIndex;
    bool       v_deviceFound;

    // This is a bad Patient Activator command to get device to NAK.
    BYTE v_autoIDMessage[] = {0xc1, 0x00, 0x00, 0xc1, 0x00, 0x00, 0x00};

    // max uplink message
    // Header 2 bytes (Family Id and Command Code)
    // Data bytes (32 bytes for 1 memory page)
    // Parity byte (1 bytes)
    BYTE v_uplinkMessage[tac_IPG_MAP_UPLINK_SIZE];

    /* Check for repeat downlink active mode */
    if (!IsRepeatDownlinkActive())
    {
        // Start the Kappa auto-id code here.
        //      If testDeviceFound==false then
        //        auto-id
        //        if auto-id == true then
        //            noDeviceFound=false
        //            copy device specific downlink into v_downlinkMessage
        //            calculate crc
        //        else
        //            auto id failed
        //            do nothing
        //        end if
        //      end if
        //
        //     (a second check is done to catch auto-id failure)
        //
        //     If testDeviceFound == false then
        //       return error
        //
        //  This will then return if autoid fails or skip/continue if device found.
        if (tav_testDeviceFound == false)
        {
            // Signal Auto-Id is being done.
            bsm_SDPrint("Auto-ID of Kappa being done.");

            v_status = tam_Send_Telemetry(  v_autoIDMessage,
                                            sizeof(v_autoIDMessage),
                                            v_uplinkMessage,
                                            AIC_KAPPA_A_AUTOID_EXPECTED_UPLINK,
                                            tac_MAP_TIMEOUT);

            // received data
            if ((v_status == tac_successful) &&
                ((v_uplinkMessage[0] ^ v_uplinkMessage[1] ^
                  v_uplinkMessage[2] ^ v_uplinkMessage[3]) == 0) &&
                (v_uplinkMessage[1] == 0x82))
            {
                // Now determine the model id and set up the
                // specific device downlink/uplink to be used
                // from this point on.
                v_modelId    = v_uplinkMessage[0];                // model id
                v_submodelId = (v_uplinkMessage[2] & 0x0F);                 // submodel id

                // Check the device table.
                // A device id of AIC_NULL_DEVICE_ID signals the end of the table.
                v_tableIndex = 0;
                v_deviceFound= false;

                while (AIC_NULL_DEVICE_ID != aiv_KappaSpecificDeviceTableA[v_tableIndex].deviceId)
                {
                    if ((v_modelId == aiv_KappaSpecificDeviceTableA[v_tableIndex].deviceId) &&
                        (v_submodelId == aiv_KappaSpecificDeviceTableA[v_tableIndex].subModel))
                    {
                        v_deviceFound = true;
                        // Create downlink here.
                        // canned downlink message to a Kappa that requests 32
                        // bytes (1 memory page)

                        // For example, a K700 VDD would be...
                        // 0x03 - Family Id
                        // 0x40 Command Code (Submode Id 4 & Process Data uplink)
                        // 0x00 Control Byte (Memory Read)
                        // 0x43 Parity Byte
                        // 0x01 Memory Page Number
                        // 0x01 Parity Byte
                        v_downlinkMessage[0] = aiv_KappaSpecificDeviceTableA[v_tableIndex].deviceId;
                        v_downlinkMessage[1] = aiv_KappaSpecificDeviceTableA[v_tableIndex].subModel << 4;
                        v_downlinkMessage[2] = 0x00;
                        v_downlinkMessage[3] = v_downlinkMessage[0] ^
                                               v_downlinkMessage[1] ^
                                               v_downlinkMessage[2];
                        v_downlinkMessage[4] = 0x01;
                        v_downlinkMessage[5] = 0x01;                         // just repeat the 1 byte for parity.

                        tav_testDeviceFound  = true;
                        break;
                    }

                    v_tableIndex++;
                }

                // If the device could not be found in the table then return error.
                if (v_deviceFound == false)
                {
                    bsm_SDPrint("Auto-ID failed - kappa device not supported.");
                    return(v_status);
                }
            }
            else
            {
                bsm_SDPrint("Auto-ID failed");
                return(v_status);
            }
        }
        // check if the auto-id worked
        if (tav_testDeviceFound == false)
        {
            return(v_status);
        }

        // Stop Auto ID code here.

        // send message
        v_status = tam_Send_Telemetry(  v_downlinkMessage,
                                        6,
                                        v_uplinkMessage,
                                        tac_IPG_MAP_UPLINK_SIZE,
                                        tac_MAP_TIMEOUT);

        // received data
        if (v_status == tac_successful)
        {
            // Calculate parity on uplink
            v_uplinkParity = v_uplinkMessage[0];
            for (v_index = 1; v_index < tac_IPG_MAP_UPLINK_SIZE - 1; v_index++)
            {
                v_uplinkParity = v_uplinkParity ^ v_uplinkMessage[v_index];
            }

            // check uplink parity
            if (v_uplinkParity != v_uplinkMessage[tac_IPG_MAP_UPLINK_SIZE - 1])
            {
                v_status = tac_telemetryParityError;
                bsm_SDPrint("tac_telemetryParityError");
            }

            // send parity information out to debug port
            stdoutBuffer[0] = 0;
            strcat(stdoutBuffer, "Uplink Parity: ");
            ltoa(v_uplinkMessage[tac_IPG_MAP_UPLINK_SIZE - 1], &stdoutBuffer[strlen(stdoutBuffer)]);
            bsm_SDPrint(stdoutBuffer);

            stdoutBuffer[0] = 0;
            strcat(stdoutBuffer, "Calculated Uplink Parity: ");
            ltoa(v_uplinkParity, &stdoutBuffer[strlen(stdoutBuffer)]);
            bsm_SDPrint(stdoutBuffer);
        }
        else
        {
            v_status = tac_downlinkCommandFailed;
        }
    }
    else
    {
        v_status = tac_repeatDownlinkActive;
    }
    return (v_status);
}
