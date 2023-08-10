/************************************************************************
*
* MODULE: nwm_net.c
*
* OWNER:
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* FUNCTIONS:
* --Public--
*
* --Private--

*
* DESCRIPTION: This module contains the network related code.
*
*************************************************************************/
#include <stdlib.h>
#include <stdio.h>   //For sprintf (string manipulation)
#include <string.h>
#include "nwm_net.h"
#include "nwm_http.h"
#include "global.h"
#include "bsm_global.h"
#include "printf2490.h"

#include "cx077.h"   //Modem header file
#include "uim_ui.h"
#include "aim_kappa.h"
#include "vocal\include\silabs.h"


// Global Variables
nwst_HttpISP_Param nwv_HttpISP_Param;

//Local Defines
#define PHONE1                  "P1" // Value in flash indicating successful upload using phone1
#define PHONE2                  "P2" // Value in flash indicating successful upload using phone2
#define PREFIX_N_INDEX_0        "N"  // Value in flash indicating last working prefix used was 'N' position
#define PREFIX_7_INDEX_1        "7"  // Value in flash indicating last working prefix used was '7' position
#define PREFIX_8_INDEX_2        "8"  // Value in flash indicating last working prefix used was '8' position
#define PREFIX_9_INDEX_3        "9"  // Value in flash indicating last working prefix used was '9' position
#define MAX_RESPONSE_LENGTH     256
#define INVALID_PREFIX_INDEX    0xFF
#define MAX_PREFIX_INDEX        3
#define MAX_PREFIX_BUF_SIZE     2
#define NWC_MAX_INCOMP_EQUIP    (2)  // max incompatiable equipment number for each prefix (2490H) regardless of signal or dual carriers

// Cap the max modem speed to 31.2k or 19.2 bps
#define MDM_CONNECT_SPEED_LIMITS_1    "AT+ms=11,0,2400,31200\r"
#define MDM_CONNECT_SPEED_LIMITS_2    "AT+ms=11,1,4800,19200\r"


// Local Variables
char nwv_call_failure_reason_code;                        // Call failure reason code from the modem.
char net_str[MDM_STRING_64];                              // temp for string data and dialing string
char mdmResponse[MDM_STRING_64];                          // response string for modem responses
BYTE phone_number[ISP_PHONE1_MAX_SIZE];                   // Current phone number
BYTE lastWorkPhoneFlag[ISP_LASTWORKPHONEFLAG_MAX_SIZE];   // last known working phone flag

UINT16 prefix_incomp_dial_counts[MAX_PREFIX_INDEX+1];
UINT16 dial_prefix_index=INVALID_PREFIX_INDEX;            // the Prefix to be used
UINT16 incomp_equip_2490H;     // flag=1, indicating the dial faulure is due to incompatible equipment for 2490H
                               // it's updated for 2490H and 2020C, but is read and used only by 2490H.
UINT16 last_used_prefix_sw_index; 
BYTE   lastUsedPrefix[NWM_LASTUSEDPREFIX_MAX_SIZE];
BYTE   lastWorkPrefix[ISP_LASTWORKPREFIX_MAX_SIZE];
UINT16 lastWorkPrefixIndex;

// Local Declaration Prototypes
void nwm_FlushAndClearEventLogBlock(void);
void nwm_ConfigureModem(UINT16 current_dial_attempt);
void nwm_ResetModem(void);
uint16 codec_process_control_word(uint16 control);
void nwm_Get_CurrentPhoneNumber(UINT16 dial_attempts);
void nwm_SaveLastWorkPhone(void);
bool nwm_isDualCarrier(void);
void nwm_FindDialPrefixIndex(void);
UINT16 nwm_GetLastWorkPrefixIndex(void);
UINT16 nwm_GetLastUsedPrefixIndex(void);
void nwm_SaveLastUsedPrefixAndWorkPrefix(UINT16 dial_status);
void nwm_SaveLastWorkPrefix(UINT16 prefixIndex);

/*******************************************************************************************
FUNCTION: nwm_Send_Data

DESCRIPTION: This function is called by the 2490 Application to send the
             interrogation information to the network.

             This function is responsible for the overall control of dialing,
             logging in, and sending the file and asset data, retrieving any
             updates and initiating updates as necessary. If a failure occurs
             at any point, an error message will be written to the error log.
             There are a total of 12 dial attempts with a 10-minute pause
             between every 3 attempts. There is also a maximum number of 
             incompatible equipment attempts allowed during the dial sequence.
             For 2020C, if the max incompatible equipment limit is reached, then the 
             function returns FALSE indicating a failure has occurred. For 2490H,
             dial prefix and dial prefix overide requirements will be followed (SCR 217276).
             If the data is successfully sent to the network the function returns TRUE.

UPDATES VIA SCR 119034: The 2490H network retry algorithm is currently executed only in
                        the event of a failure in the device data file upload. The
                        firmware/ programmable parameter update is being attempted only
                        once.

                        Thus, if a sufficiently large number of remote monitors make
                        simultaneous requests for firmware/ parameter updates from the
                        CareLink server, several of these requests shall fail. A 2490H
                        remote monitor averages about four transmissions per year, so a
                        2490H that encounters a failed firmware update might have to wait
                        for several months before the next attempt occurs. In order to
                        prevent a 2490H remote monitor from being denied important
                        firmware/ programmable parameter updates in this manner, a firmware
                        update retry algorithm has to be implemented, as per the newly
                        added requirements in the "FLBL8: Firmware Update" section of the
                        2490H SRS Revision C.

                        According to the above firmware update requirements, the 2490H
                        remote monitor shall make a maximum of 12 dial-up attempts when
                        failures occur in either the uploading of the device 
                        interrogation package or in the downloading of new 
                        firmware/programmable parameters.

                        Several outcomes are possible from the firmware/ programmable
                        parameter update operation. These have grouped below based on the
                        desired action to be taken by the 2490H.

                        STOP FURTHER RETRIES (DIAL ATTEMPTS) IN CASE OF THE FOLLOWING:
                        1.) Firmware/ programmable parameter update was successful
                        2.) No firmware/ programmable parameter updates available from the
                            CareLink server
                        3.) Downloaded firmware is the same as installed firmware
                        4.) Firmware update operation in flash failed due to one or more of
                            the ensuing reasons.
                                a. insufficient battery voltage
                                b. unknown flash type
                                c. unable to clear the current CRC
                                d. software block verification failed
                                e. downloaded code was too large

                        CONTINUE WITH THE FIRMWARE RETRY SEQUENCE IN CASE OF THE FOLLOWING:
                        1.) Failure to get update page (Initial HTTP "Get" failed)
                        2.) Asset POST Failure after a successful login
                        3.) CRC mismatch in the response from server
                        4.) CRC mismatch in the downloaded firmware

                        In addition, during the firmware update process, if the 2490 is not
                        able to detect a telephone line even after trying for two minutes,
                        the 2490 shall turn off both AUDIO_ALERT_TONE and
                        LED_TELEPHONE_ERROR, and proceed to UI_UPLOAD_COMPLETE. Refer to
                        the updated requirement called UI_TELEPHONE_ERROR in the 2490 SRS
                        for the 2490G2 Plus Maintenance Release.


ARGS:
        <none>

RETURNS:
    BOOL: TRUE if success,
          FALSE if failure.
*******************************************************************************************/
BOOL nwm_Send_Data (void)
{
    UINT16 status, i;
    UINT16 dial_attempts;        // Number of dial attempts
    UINT16 incomp_equip_2020C;   // Number of Dial attempts resulting in 'incompatible equipment' for 2020C
    UINT16 max_incomp_equip;     // Maximum number of incompatible equipment retries, used for 2020C
    UINT16 attempts;             // Holds number of dialing attempts when updating in NVStorage
    bool   isDualCarrier;        // Dual carrier available flag
    char   VTOutput[80];
    bst_DialSwitchState dial_prefix_sw;  //prefix switch setting

    bool firmwareUpdateOnly = false;     // Is the current dial-up attempt for firmware update only?


    // Initialize phone number and last work phone flag
    memset(phone_number, 0, sizeof(phone_number));
    memset(lastWorkPhoneFlag, 0, sizeof(lastWorkPhoneFlag));

    //Read modem and network parameters from flash. If they are not provided, use defaults.
    nwm_GetModemNetwork_Params();

   // Initialize Prefix vaiables and Get last used and work prefix indexes 
    for (i=0; i<= MAX_PREFIX_INDEX; i++)
    {
        prefix_incomp_dial_counts[i] = 0;
    }
    incomp_equip_2490H = 0xFF;    // flag, Initialize to unknown before dial starts
    incomp_equip_2020C = 0;       // Initialize incomp_equip attempts
    // Get last used  prefix index (index of string value read from flash above)
    last_used_prefix_sw_index = nwm_GetLastUsedPrefixIndex();
    // Get last working prefix index (index of string value read from flash above)
    lastWorkPrefixIndex = nwm_GetLastWorkPrefixIndex();
 
    // Check phone parameters to determine if dual or single carrier     
    isDualCarrier = nwm_isDualCarrier();
    
    // Set max number incompatible equipment occurrences based on dual or single carrier.
    // This will be only used for 2020A/2020B Monitors
    if (isDualCarrier)
    {
        // Dual carrier, allow up to 4 incompatible equipment occurrences (2 per carrier)
        max_incomp_equip = NWC_MAX_INCOMP_EQUIP_DUAL;
    }
    else
    {
        // Single carrier, allow up to 2 incompatible equipment occurrences
        max_incomp_equip = NWC_MAX_INCOMP_EQUIP_SINGLE;
    }

    // Turn on the 1st phone LED.
    uim_ModemStart(ON);

    // Connect with PMN, try NWC_DIAL_ATTEMPTS for 2490H and 2020C
    // and 'max_incomp_equip' attempts for 2020C
    for (dial_attempts=0; 
         ((dial_attempts < NWC_DIAL_ATTEMPTS) && (incomp_equip_2020C < max_incomp_equip));
         dial_attempts++)
    {

        // Check to see if we should delay.
        if (dial_attempts > 0)
        {
            if (dial_attempts % 3 == 0)
            {
                bsm_SDPrint("Entering wait period.");

#ifdef VOCAL_TESTING
                #warn "VOCAL testing enabled"
                GLB_LTMR_WAIT(NWM_MINUTE_DELAY(3));
#else
                GLB_LTMR_WAIT(NWM_MINUTE_DELAY(10));
#endif
            }
            else
            {
                // Wait for 40 seconds before the next attempt
                // to reduce the chances of GSM lock up.
                // (See SCR # 201072 for details).
                GLB_LTMR_WAIT(40000);
            }
        }

        // initialize modem
        status = bsm_setModemState(ON);

        // Proceed only if modem initialization was successful
        if(status == MDM_ERRORCODE__NO_ERROR)
        {
            // Turn on the 1st phone LED.
            uim_ModemStart(ON);

            // Send the dial attempt number to the debug port.
            net_str[0] = NULL;
            strcat(net_str, "Dial attempt ");
            ltoa( dial_attempts+1, &net_str[strlen(net_str)]);
            bsm_SDPrint(net_str);

            strcpy(VTOutput,"Country code: ");
            strcat(VTOutput, nwv_HttpISP_Param.mdm_CountryCode);
            bsm_SDPrint(VTOutput);

            // Set Country code, etc.
            nwm_ConfigureModem(dial_attempts);

            // Check for the phone line.
            status = nwm_IsPhoneLineConnected();

            // Increment the connection attempt counter.
            bsm_EEReadBuf((UINT8*)net_str, coc_NetworkConnectionAttempts_SIZE, coc_NetworkConnectionAttempts_ADDR);  // Read it.
            // Place value into variable so it can be incremented
            attempts  = (net_str[0] & 0xFF) << 8;
            attempts |= (net_str[1] & 0xFF) << 0;
            if( attempts == 0xFFFF)       // If it is the unprogrammed Flash value,
            {
                attempts = 0;             // reset it to zero.
            }
            attempts++;                   // Increment it.

            // Unpack variable into buffer to write back to flash
            net_str[0] = (attempts & 0xFF00) >> 8;
            net_str[1] = (attempts & 0x00FF) >> 0;
            bsm_EEWriteBuf((UINT8*)net_str, coc_NetworkConnectionAttempts_SIZE,
                                            coc_NetworkConnectionAttempts_ADDR); // Write it.
            // Note: This parameter is never cleared in the Flash.

            switch(status)
            {
            case true:  //Phone line check passed
                // Connect to ISP
                status = nwm_Dial_Sequence(dial_attempts);
                break;

            case false: //Phone line check failed
            default:
                // Log the problem.
                bsm_EHLog("Phone line problem.",status);

                // The patient has 2 minutes to get off the phone.
                status = nwm_Line_Problem_Action(dial_attempts);

                // If the dialtone is back, dial.
                if(status == NWC_OK)
                {
                    // Connect to ISP
                    status = nwm_Dial_Sequence(dial_attempts);
                }
                else // Exit the dial attempts loop.
                {
                    // Set leave condition to exit loop
                    dial_attempts = NWC_DIAL_ATTEMPTS+1;
                }
                break;

            } // End of switch.

            // Check for incompatible equipment (treat a "no response" and "no answer" as incompatible equipment)
            if ( (status == NWC_ERR_INCOMP_EQUIP)
                  || (status == NWC_ERR_NO_RESPONSE)
                  || (status == NWC_ERR_NO_ANSWER) )
            {
                incomp_equip_2490H = 1;
                if (aim_MonitorIsA2020C() )
                {
                   incomp_equip_2020C++;
                }
            }
            else
            {
                incomp_equip_2490H = 0;
            }
            // Save the last used prefix and work prefix  
            // before the post data starts
            nwm_SaveLastUsedPrefixAndWorkPrefix(status); 


            // If login was successful, log ip address, change LEDs, and send data.
            if(status == NWC_OK)
            {
                // Save current phone to NVstorage as last known working phone
                // number when dial out is successful (rather than after upload
                // is successful)
                nwm_SaveLastWorkPhone();
                     
                // log the IP address
                nwm_ExtractIPAddress();

                // Turn off the 1st phone LED.
                uim_ModemStart(OFF);

                // Make the phone line LEDs blink in succession.
                uim_StrobePhoneLeds(ON);

                // Check if the device file has been uploaded already.
                // If so, only firmware update retry has to be performed
                if ( false == firmwareUpdateOnly &&
                     (aim_skipInterrogationCheckFWUpdates() == false))
                {
                    // Send the file using HTTP.
                    status = nwm_HTTP_Send_Data();
                    if (status == NWC_OK)
                    {
                        // Package was uploaded successfully.
                        // Save the asset log entries that were written after
                        // the asset file was readied for upload, then erase the
                        // asset/event log block and finally re-write the saved
                        // asset log entries to the asset/event log block.
                        nwm_FlushAndClearEventLogBlock();
#ifdef SKIP_INTERROGATION
                        #warn "WARNING: Skip Interrogation"
#else
                        // Update the session parameters.
                        aim_SaveSessionParameters();
#endif //End of SKIP_INTERROGATION
                    }
                }
                else
                {
                    status = NWC_OK;
                } // if ( false == firmwareUpdate
            } // if( status == NWC_OK
            else if(dial_prefix_index == INVALID_PREFIX_INDEX)
            {
                //to terminate the dial
                dial_attempts = NWC_DIAL_ATTEMPTS+1;
            }
        } // End -- if(status == MDM_ERRORCODE__NO_ERROR)
        else
        {  // Modem failed init, log error, set status
            bsm_EHLog("Modem failed initialization.", status);
            status = NWC_ERR_FAILURE;

            //Shutoff modem
            bsm_setModemState(OFF);
        } // End -- if(status == MDM_ERRORCODE__NO_ERROR)

        if ( status == NWC_OK )
        {
            // Connection and upload of data successful, do software update

            // Clear last interrogation duration
            net_str[0] = 0xFFFF;     //blank out variable
            net_str[1] = 0xFFFF;     //blank out variable
            bsm_EEWriteBuf((UINT8*)net_str, coc_LastInterrogateDuration_SIZE,
                                            coc_LastInterrogateDuration_ADDR);

            status = nwm_HTTP_FirmwareUpdate();
            // In case there was an error during the actual update to flash,
            // stop attempting further dial ups
            if ( NWC_ERR_SWUPDATE_FAILURE == status )
            {
                status = NWC_OK;
            }

            // If the first attempt to perform a firmware update failed, log the status in the relevant flag
            if ( ( false == firmwareUpdateOnly ) && ( NWC_OK != status ) &&
                 (aim_skipInterrogationCheckFWUpdates() == false))
            {
                firmwareUpdateOnly = true;
            }
            else if ( NWC_OK == status )
            {
                // Break out of the dial attempts loop if the firmware update was successful.
                break;
            }     //  if ( ( false == firmwareUpdateOnly )

        } //  if ( status == NWC_OK )   // Connection an

        // Turn off blinking LEDs.
        uim_StrobePhoneLeds(OFF);

        // Turn on the 1st phone LED.
        uim_ModemStart(ON);

        // shut off modem before returning
        bsm_setModemState(OFF);

    } // End of dial attempts loop.

    // Check if the maximum dial attempts were exhausted during the device data file upload
    if ( ( false == firmwareUpdateOnly )
         && ( status != NWC_OK )
         && ( ( dial_attempts >= NWC_DIAL_ATTEMPTS )
              || ( incomp_equip_2020C >= max_incomp_equip ) ) )
    {

        // Maximum dial/upload attempts has occured

        // Log the complete failure to upload.
        bsm_EHLog("Maximum dial/upload attempts.",0);

        // Signal the error and shut down.
        // Only if there wasn't a line problem
        if( status != NWC_ERR_LINE_PROBLEM)
        {
            uim_UploadFailure();
        }

        //Shut off modem and wait before returning
        bsm_setModemState(OFF);

        //Only wait if there wasn't a line problem
        if( status != NWC_ERR_LINE_PROBLEM)
        {
            GLB_LTMR_WAIT(NWM_MINUTE_DELAY(2));             //Wait 120 seconds
        }
    }
    else
    {
        // In case there was a phone line error during the firmware update,
        // turn off the modem error LED
        uim_ModemWarning(OFF);

        // This end case includes only a successful device data upload
        // This end case includes both failed and successful firmware updates

        uim_ModemTransferComplete();

        // shut off modem and wait before returning
        bsm_setModemState(OFF);

#ifdef VOCAL_TESTING
        GLB_LTMR_WAIT( 30000 );
#else
        GLB_LTMR_WAIT( NWM_MINUTE_DELAY(2) ); //wait 120 seconds
#endif
    }

    // No phone line, phone in use, modem not responding, or
    // after sending software update status. Convert to BOOL
    status = (status == NWC_OK) ? TRUE : FALSE;

    return status;

} // nwm_Send_Data()


/*******************************************************************************************
FUNCTION: nwm_Line_Problem_Action

DESCRIPTION: This function is called when there is no dialtone or the
             phone line is in use when attempting to upload the data.
             It tries to detect a dialtone, if it cannot find one in 2 minutes (2490H) or
             15 minutes (2020C), status is failed.

ARGS:
    UINT16 current_dial_attempt

RETURNS:
    UINT16: Dial tone present:                NWC_OK
            Phone line error:                 NWC_ERR_LINE_PROBLEM
*******************************************************************************************/
UINT16 nwm_Line_Problem_Action(UINT16 current_dial_attempt)
{
    GLB_LTMR_OBJ start_time;
    GLB_LTMR_OBJ phoneline_check_timeout;
    UINT16       status;

    // Compute when we should quit checking.
    status = false;
    GLB_GET_LTMR(start_time);

    // Setup phoneline check timeout value based on device type
    if (aim_MonitorIsA2020C())
    {
        // Monitor is a 2020C
        // Setup phone line check timeout value to 15 min (+/- 5 secs)
        phoneline_check_timeout = NWM_MINUTE_DELAY(15) - 5000;

        // No dial tone - Blink LED and enable Alert Tone for up to 15 minutes
        uim_ModemWarning_AlertTone_15Minutes();
    }
    else
    {
        // Device is a 2490H - setup phone line check timeout value to 2 minutes (+/- 5 secs)
        phoneline_check_timeout = NWM_MINUTE_DELAY(2) - 5000;

        // No dial tone - Blink LED and enable Alert Tone for up to 2 minutes
        uim_ModemWarning(ON);   // Default Alert Tone is configured for 2 minute duration
    }

    //check for phone line
    while( GLB_HAS_LTMR_EXPIRED(start_time, phoneline_check_timeout) != TRUE) // +/- 5seconds
    {
        bsm_SDPrint("Line Problem Action");
        // Reset the modem.
        nwm_ResetModem();
        // Modem reset may have changed some programmed settings
        // to their default values. Therefore, reconfigure modem.
        nwm_ConfigureModem(current_dial_attempt);

        // Check the phone line.
        status = nwm_IsPhoneLineConnected();

        if(status == true)
        {
            // Turn off the tone and the Phone LED
            uim_ModemWarning(OFF);
            bsm_SDPrint("Dialtone Found");
            status = NWC_OK;
            // break out of the while loop.
            break;
        }
        else {
            status = NWC_ERR_LINE_PROBLEM;
        }
    }

    if(status != NWC_OK)
    {
        // Phoneline check timeout period has been exceeded - Log error
        if (aim_MonitorIsA2020C())
        {
            // Monitor is a 2020C
            // 15 minutes have elapsed without dialtone
            bsm_EHLog("Modem Failure: Line problem exists after 15 minutes.", status);
        }
        else
        {
            // Device is a 2490H - 2 minutes have elapsed without dialtone
            bsm_EHLog("Modem Failure: Line problem exists after 2 minutes.", status);
        }
    }
    return status;
}


/*******************************************************************************************
FUNCTION: nwm_Dial_Sequence

DESCRIPTION: This function performs the dialing actions. It uses prefix and
             determines tone/pulse settings. If dialing was successful, it
             checks the connect speed. It PAP/CHAP login and then initiates
             PPP authentication and connection.
             It returns connection status including incompatible equipment
             detection, connect success, and connect fail.
             In doing this behavior, this function calls nwm_Dial_and_Connect().
ARGS:
        int:  dial_attempts: number of dial attempt

RETURNS:
    UINT16: Dial Success:                     NWC_OK
            Dial Failure:                     NWC_ERR_FAILURE
            Incompatiable equipment detected: NWC_ERR_INCOMP_EQUIP
            Invalid (to slow) connect speed:  NWC_ERR_CONNECT_SPEED
*******************************************************************************************/
UINT16 nwm_Dial_Sequence(int dial_attempts)
{
    UINT16 status;
    char   isp_username[ISP_USER_NAME_MAX_SIZE + ISP_HOST_NAME_MAX_SIZE + 1];
    char   VTOutput[80];

    // Update log
    bsm_EHLog("Phone line ok.",0);

    // Get current phone number
    nwm_Get_CurrentPhoneNumber(dial_attempts);

    // Find Dial Prefix Index
    nwm_FindDialPrefixIndex();
               
    if (dial_prefix_index > MAX_PREFIX_INDEX)
    {                    
         // Invalid prefix index indicates max incompatible equipment attempts reached
         status = NWC_ERR_FAILURE;
    }
    else
    {
        // Dial and connect to an ISP (authentication and PPP done later)
        status = nwm_Dial_and_Connect(phone_number);
    }

    if(status == NWC_OK || status == NWC_CONNECT)
    {

        if (strstr((char*)nwv_HttpISP_Param.ISP_AuthMethod, bsc_PAP)||
            strstr((char*)nwv_HttpISP_Param.ISP_AuthMethod, bsc_CHAP))
        {
            //username string to be in the form 'securip.<hostname>.<username>'
            bsm_EHLog("NWM: PAP/CHAP Login",0);

            sprintf(VTOutput,"NWM: ISP Auth. Method: %s.",
                    nwv_HttpISP_Param.ISP_AuthMethod);
            bsm_SDPrint(VTOutput);

            sprintf(VTOutput, "NWM: ISP Host Name: %s.",
                    nwv_HttpISP_Param.ISP_HostName);
            bsm_SDPrint(VTOutput);

            // PAP/CHAP login user name is isp_userName@isp_HostName
            strcpy(isp_username, nwv_HttpISP_Param.IP_UserName);
            strcat(isp_username, "@");
            strcat(isp_username, nwv_HttpISP_Param.ISP_HostName);


            //Do the network init with PAP/CHAP enabled
            status = network_Init(TRUE, isp_username, nwv_HttpISP_Param.IP_Password);

            strcpy(mdmResponse, "Network Init Response: ");
            ltoa( status, &mdmResponse[strlen(mdmResponse)]);
            bsm_EHLog(mdmResponse, status);

            // Return Type Conversion
            status = (status == MDM_ERRORCODE__NO_ERROR) ? NWC_OK : NWC_ERR_FAILURE;

        } // End -- if -> (ISPAuthMeth is bsc_PAP -or- bsc_CHAP)
        else
        {
            bsm_EHLog("NWM: Invalid ISP auth method",0);
        }         // End else

        //Check if static DNS is required
        if ((nwv_HttpISP_Param.nwm_StaticDNS[0] & 0xFF) != 0xFF)        // if the value is programmed, then use it
        {
            strcpy(net_str, NWM_STATIC_DNS_COMMAND);
            strcat(net_str, nwv_HttpISP_Param.nwm_StaticDNS);
            strcat(net_str, MDM_CR_STR);
            network_Send_Cmd(net_str);
        }

        //Set TCP/IP paramemters
        //Note: These were experimentally chosen. The segment size was chosen
        //      as a large value to lower overhead and transmissions during large
        //      file transfers. The Windows should (read as *must* or *shall*) be
        //      a multiple of the segment size. This was experimentally chosen
        //      to reduce download times of large files.
        strcpy(net_str, NET_CMD_CHANGE_MSS);
        network_Send_Cmd(net_str);           //Maximum Segment Size
        strcpy(net_str, NET_CMD_CHANGE_WINDOW_SIZE);
        network_Send_Cmd(net_str);        //Windows size -> should be a multiple of the MSS
    }

    return status;

} // nwm_Dial_Sequence()


/********************************************************************************
      Function:   nwm_Dial_and_Connect

   Description:  Using stored phone number, prefix setting, and doing tone/pulse
                 detection; this function dials the modem and attempts
                 connection to stored ISP.
                 It succeeds if connection is established and that connection is
                 at least equal to or greater than 9600 Baud.
ARGS:
        BYTE* phoneNumber: Phone number to dial, null terminated.

RETURNS:
    UINT16: Dial Success:                     NWC_CONNECT
            Dial Failure:                     NWC_ERR_FAILURE
                Incompatiable equipment detected: NWC_ERR_INCOMP_EQUIP
            Invalid (to slow) connect speed:  NWC_ERR_CONNECT_SPEED
*********************************************************************************/
UINT16 nwm_Dial_and_Connect(BYTE* phoneNumber)
{
    UINT16              status;
    bst_ToneSwitchState dial_type;                 //current dial_type
    UINT16              index;                     //loop variable
    UINT32              connectSpeed;              //Connect speed
    BYTE                dialString[MDM_STRING_64]; //to store the full dial number

    //Null out the string
    for(index = 0; index < sizeof(dialString); index++)
    {
        dialString[index] = 0;
    }

    // Get the dial prefix.
    net_str[MDM_DIAL_PREFIX_MAX_SIZE-1] = 0;

    strcpy((char*)net_str, nwv_HttpISP_Param.mdm_DialPrefix);

    // Change any 'N' or 'n' to a null.
    for(index = 0; index < coc_DIALPREFIX_SIZE; index++)
    {
        if(net_str[index] == 'N' || net_str[index] == 'n')
            net_str[index] = 0x0;
    }

    // Add comma to string to provide additional 2 sec delay after going off-hook
    dialString[0]  = ',';       // 2 sec delay

    // Force invalid prefix index value to 0 (None prefix setting)
    if (dial_prefix_index > 3)
        dial_prefix_index = 0;

    // Save indexed prefix value {None, 7, 8, 9} into dialString[1]
    dialString[1] = net_str[dial_prefix_index];

    // Add comma to string to provide 2 sec delay after prefix (assuming there is one)
    // if no prefix, this comma will not be used due to dialString[1]=NULL
    dialString[2] = ',';        // 2 sec delay

    // Null terminate to make a string.
    dialString[3] = 0;

    // Concatenate the dial prefix with the phone number.
    strcat((char*)dialString, (char*)phoneNumber);

    // Log the phone number string.
    net_str[0] = NULL;
    strcat(net_str, "Phone number: ");
    strcat(net_str, (char*)dialString);
    bsm_EHLog((char*)net_str,0);

    dial_type = bsm_INReadTonePulse();

    // Determined the correct dial type, now dial and connect
    // Enable modem audio
    mdm_Send_Control_String(MDM_SPEAKER_ON_STR, mdmResponse, sizeof(mdmResponse));

    // Set modem audio level
    mdm_Send_Control_String(MDM_SPEAKER_VOLUME, mdmResponse, sizeof(mdmResponse));

    // Build full dial string (the number is in dialString)
    switch(dial_type) {
    case bsc_TONE:
        // copy the dial type string
        strcpy((char*)net_str, MDM_TONE_DIAL_PREFIX);
        break;
    case bsc_PULSE:
    // break intentionally left off, pulse by default
    default:
        // copy the dial type string
        strcpy((char*)net_str, MDM_PULSE_DIAL_PREFIX);
        break;
    }

    // add the full number into the dial command
    strcat((char*)net_str, (char*)dialString);

    // add the carriage return
    strcat((char*)net_str, MDM_CR_STR);
    bsm_EHLog((char*)net_str,0);

    // Dial the entire number
    mdm_Send_Control_String((char*)net_str, mdmResponse, sizeof(mdmResponse));
    status = nwm_Get_Modem_Response (mdmResponse);

    if( status != NWC_OK && status != NWC_CONNECT )
    {
        nwm_Process_Modem_Error (status);
    }
    else
    {
        // Checking for successful connection and minimum connect speed
        connectSpeed = mdm_Get_Connect_Speed();
        if(connectSpeed >= (UINT32)NWC_MIN_CONNECT_SPEED)
        {
            //sprintf((char*)str,"Connected at %ld.", connectSpeed);
            net_str[0] = NULL;
            strcat(net_str, "Connected at ");
            ltoa( connectSpeed, &net_str[strlen(net_str)]);
            status     = NWC_CONNECT;
        }
        else
        {
            //sprintf((char*)str,"Connection too slow: %ld.", connectSpeed);
            net_str[0] = NULL;
            strcat(net_str, "Connection too slow: ");
            ltoa( connectSpeed, &net_str[strlen(net_str)]);
            status     = NWC_ERR_CONNECT_SPEED;
        }

        bsm_EHLog((char*)net_str, status);
    }

    return status;
}


/*******************************************************************************************

FUNCTION: nwm_ConfigureModem

DESCRIPTION:
    This functions configures the modem, based on the country code settings. This function
    needs to be called after a modem reset in order to bring the modem back to the
    configuration programmed into the 2490.

ARGS:
    UINT16 current_dial_attempt

RETURNS:
    <none>

*******************************************************************************************/
void nwm_ConfigureModem(UINT16 current_dial_attempt)
{
    // Initialize the command string to set the country code
    strcpy(net_str, MDM_COUNTRY_SELECT);
    strcat(net_str, nwv_HttpISP_Param.mdm_CountryCode);
    strcat(net_str, MDM_CR_STR);

    // Initialize the modem country code.
    mdm_Send_Control_String(net_str, mdmResponse, sizeof(mdmResponse));

    // Changing the country code resets DTMF signal strength.
    // Set DTMF signal strength again.
    mdm_setModemDTMFStrength();

    // Enable error correction.
    strcpy(net_str, MDM_ENABLE_ERROR_CORRECTION);
    mdm_Send_Control_String(net_str, mdmResponse, sizeof(mdmResponse));

    // Set the guard time before and after the escape sequence (+++) to 1 second
    mdm_Send_Control_String(MDM_1_SEC_GUARD_TIME_STR, mdmResponse,
                            sizeof(mdmResponse));

    // Set connection speed limits due to eDevice/GSM can't handle the data 
    //  transmit speed > 31.2K bps
    if (current_dial_attempt == 0)
    {
        // restrict the maximum modem speed to 31200 for initial dial attempt
        mdm_Send_Control_String(MDM_CONNECT_SPEED_LIMITS_1, mdmResponse, sizeof(mdmResponse));
    }
    else
    {
        // restrict the maximum modem speed to 19200 on the 2nd and beyond dial attempt
        mdm_Send_Control_String(MDM_CONNECT_SPEED_LIMITS_2, mdmResponse, sizeof(mdmResponse));
    }

}

/*******************************************************************************************

FUNCTION: nwm_ResetModem

DESCRIPTION:
    This functions terminates an existing dial-up connection, hangs up the phone
    and resets the modem.

ARGS:
    <none>

RETURNS:
    <none>

*******************************************************************************************/
void nwm_ResetModem(void)
{

    // Reset the modem and go on-hook.
    GLB_LTMR_WAIT(1000);        // 1 second delay guard band before "+++" escape command
    mdm_Send_Control_String(MDM_PLUSPLUSPLUS_STR, mdmResponse, sizeof(mdmResponse));
    GLB_LTMR_WAIT(1000);        // 1 second delay guard band after "+++" escape command
    mdm_Send_Control_String(MDM_RESET_STR, mdmResponse, sizeof(mdmResponse));

}

/*******************************************************************************************
FUNCTION: nwm_IsPhoneLineConnected

DESCRIPTION: Checks phone line.

ARGS:
        <none>

RETURNS:
    TRUE if phone line attached
    FALSE if failure.

*******************************************************************************************/
bool nwm_IsPhoneLineConnected(void)
{
    UINT16 val;

    // Read "Line Voltage Status" register.
    // (Bit 15 - 1 indicates a read and 0 indicates a write
    //  Bits 14:8 - indicates the register in decimal
    //  Bits 7:0 - used for data writes)

    // LVS value of 0 implies line is not connected.
    // Reference: Serial Interface Direct Access Arrangement (DAA) Si3056
    // data sheets.

    val = codec_process_control_word ((DAA_LoopVoltage << 8) | 0x8000);
    return (val != 0x00);
}


/********************************************************************************

      Function:   nwm_Get_Modem_Response

   Description:   This function returns a status based on the given modem
                  respnse string.
ARGS:
        char *: reponse - string return from modem

RETURNS:
    UINT16: Command accepted:                 NWC_OK
            Connection occured:               NWC_CONNECT
            No dial tone:                     NWC_ERR_NO_DIALTONE
            Line connected but in use:        NWC_ERR_LINE_IN_USE
            Dialed number is busy:            NWC_ERR_BUSY
            No Response                       NWC_ERR_NO_RESPONSE
            Incompatiable equipment detected: NWC_ERR_INCOMP_EQUIP
            An unknown error occurred:        NWC_ERR_UNKNOWN
*********************************************************************************/
UINT16 nwm_Get_Modem_Response (char* response)
{
    UINT16      status;
    static char tempbuf[100];

    if(response[0] == 0)                          // Check for no string.
        status = NWC_ERR_NO_RESPONSE;
    else if(strstr(response, NWC_STR_OK))         // Check for OK string.
        status = NWC_OK;
    else if(strstr(response, NWC_STR_CONNECT))    // Check for connection string
        status = NWC_CONNECT;
    else if(strstr(response, NWC_STR_BUSY))       // Check for busy string.
        status = NWC_ERR_BUSY;
    else if(strstr(response, NWC_STR_NO_DIALTONE)) // Check for no dial tone string.
        status = NWC_ERR_NO_DIALTONE;
    else if(strstr(response, NWC_STR_NO_ANSWER))  // Check for no answer string.
        status = NWC_ERR_NO_ANSWER;
    else if(strstr(response, NWC_STR_NO_CONNECT)) // Check for incompatible equipment
    {
        status = NWC_ERR_INCOMP_EQUIP;
        sprintf(tempbuf,"stat__omc_disconnect_reason is 0x%04x", get_disconnect_reason());
        bsm_EHLog(tempbuf,0);
    }
    else if(strstr(response, NWC_STR_LINE_IN_USE)) // Check for line is use string.
        status = NWC_ERR_LINE_IN_USE;
    else
        status = NWC_ERR_UNKNOWN;

    return status;
}



/********************************************************************************

      Function:   nwm_Process_Modem_Error_Full

   Description:   This function processes a modem error by adding an appropriate
                  event log message
ARGS:
        UINT16: status - The status returned from 'nwm_Get_Modem_Response'

RETURNS:
    <none>
*********************************************************************************/
void nwm_Process_Modem_Error_Full (int Code, int LineNum, char * FileName)
{
    switch(Code) {
    case NWC_OK:
        // No error, no need to create a log entry
        break;
    case NWC_CONNECT:
        // No error, we connected
        bsm_EHLogFull("Connection Established",Code, LineNum, FileName);
        break;
    case NWC_ERR_NO_DIALTONE:
        // dial type detection failed due to Line problem
        bsm_EHLogFull("Modem problem: no dialtone before use.",Code, LineNum, FileName);
        break;
    case NWC_ERR_LINE_IN_USE:
        // dial type detection failed due to dialtone problem
        bsm_EHLogFull("Modem problem: line problem, line is in use.",Code, LineNum, FileName);
        break;
    case NWC_ERR_BUSY:
        // dial type detection failed due to dialtone problem
        bsm_EHLogFull("Modem problem: line problem, dialed line is busy.",Code, LineNum, FileName);
        break;
    case NWC_ERR_INCOMP_EQUIP:
        // dial type detection failed due to detection of incompatible equipment
        bsm_EHLogFull("Modem problem: Incompatible Equipment.",Code, LineNum, FileName);
        break;
    case NWC_ERR_NO_ANSWER:
        // dial type detection failed due to no answer from dialed line
        bsm_EHLogFull("Modem problem: Incompatible Equipment - dialed line did not answer.",Code, LineNum, FileName);
        break;
    case NWC_ERR_NO_RESPONSE:
        // dial type detection failed due to no response from modem
        bsm_EHLogFull("Modem problem: Incompatible Equipment - no response from modem.",Code, LineNum, FileName);
        break;
    case NWC_ERR_UNKNOWN:
    // Break intentionally left off;
    default:
        // dial type detection failed due to an unknown error
        bsm_EHLogFull("Modem problem: Unknown error.",Code, LineNum, FileName);
        break;
    }
}


/*******************************************************************************************
FUNCTION: nwm_ExtractIPAddress

DESCRIPTION: This function extracts the IPAddress from the network layer and creates a
             log entry. The string that is sought after is of the form:
             "IP address: 144.15.80.244\r\n"

ARGS:
        <none>

RETURNS:
    <none>
*******************************************************************************************/
#define DATA_BUF_SIZE       32
#define IPADDRESS_TIMEOUT   500
#define NET_VALID_DATA_MASK 0x8000
void nwm_ExtractIPAddress(void)
{
    char         data[DATA_BUF_SIZE];
    UINT16       index;
    GLB_LTMR_OBJ startTime;

    //mark down starting time
    GLB_GET_LTMR(startTime);

    //empty buffer
    while(!GLB_HAS_LTMR_EXPIRED(startTime, (UINT32)IPADDRESS_TIMEOUT))
    {

        if( (serial_console_tx()) == NET_VALID_DATA_MASK)
        {         //end of data found
            break;
        }
    }

    //Issue IP-Address Command
    strcpy( data, NET_CMD_GET_IP_ADDRESS);
    network_Send_Cmd(data);

    //Find IP-Address string
    index = 0;
    while(!GLB_HAS_LTMR_EXPIRED(startTime, (UINT32)IPADDRESS_TIMEOUT))
    {
        data[index] = serial_console_tx();
        if( data[index] != NET_VALID_DATA_MASK)
        { //valid data byte found
            if(data[0] == 'I')
            { //started on valid string
                if(data[index] == '\r')
                { //end of IP-Address string found
                    break;
                }
                index++;

                if (index == DATA_BUF_SIZE - 1)
                {
                  // Last byte filled in, room left only for
                  // null at the end.
                    bsm_SDPrint("nwm_ExtractIPAddress(): Rcvd 31 bytes");
                    break;
                }
            }
        }
    }
    data[index] = 0;     //null terminate (incase of timeout)
    bsm_EHLog(data,0);
}

/******************************************************************

FUNCTION: nwm_LogModemInitError

DESCRIPTION:  This function logs full text errors of the modem init

ARGS:
        UINT16 status: There status code returned by the modem Init function.

RETURNS:
    <none>

******************************************************************/
void nwm_LogModemInitError(UINT16 status)
{
    switch(status) {
    case MDM_ERRORCODE__GENERAL:
        bsm_EHLog("MDM: init error - MDM_ERRORCODE__GENERAL", status);
        break;
    case MDM_ERRORCODE__SYSTEM_INITIALIZATION:
        bsm_EHLog("MDM: init error - MDM_ERRORCODE__SYSTEM_INITIALIZATION", status);
        break;
    case MDM_ERRORCODE__HARDWARE_RESET_FAILURE:
        bsm_EHLog("MDM: init error - MDM_ERRORCODE__HARDWARE_RESET_FAILURE", status);
        break;
    case MDM_ERRORCODE__HARDWARE_TIMEOUT:
        bsm_EHLog("MDM: init error - MDM_ERRORCODE__HARDWARE_TIMEOUT", status);
        break;
    case MDM_ERRORCODE__DSP_TIMER_FAILURE:
        bsm_EHLog("MDM: init error - MDM_ERRORCODE__DSP_TIMER_FAILURE", status);
        break;
    case MDM_ERRORCODE__DSPDRV_SETUP:
        bsm_EHLog("MDM: init error - MDM_ERRORCODE__DSPDRV_SETUP", status);
        break;
    case MDM_ERRORCODE__DSPDRV_STARTUP:
        bsm_EHLog("MDM: init error - MDM_ERRORCODE__DSPDRV_STARTUP", status);
        break;
    case MDM_ERRORCODE__DTEIF_SETUP:
        bsm_EHLog("MDM: init error - MDM_ERRORCODE__DTEIF_SETUP", status);
        break;
    case MDM_ERRORCODE__DTEIF_STARTUP:
        bsm_EHLog("MDM: init error - MDM_ERRORCODE__DTEIF_STARTUP", status);
        break;
    case MDM_ERRORCODE__DIAGNOSTIC_STARTUP:
        bsm_EHLog("MDM: init error - MDM_ERRORCODE__DIAGNOSTIC_STARTUP", status);
        break;
    case MDM_ERRORCODE__SYSTEM_CONFIGURATION:
        bsm_EHLog("MDM: init error - MDM_ERRORCODE__SYSTEM_CONFIGURATION", status);
        break;
    case MDM_ERRORCODE__CTRL_BREAK_SEEN:
        bsm_EHLog("MDM: init error - MDM_ERRORCODE__CTRL_BREAK_SEEN", status);
        break;
    case MDM_ERRORCODE__SHUTDOWN:
        bsm_EHLog("MDM: init error - MDM_ERRORCODE__SHUTDOWN", status);
        break;
    default:
        bsm_EHLog("MDM: init error - MDM_ERRORCODE__UNDEFINED", status);
        break;
    }

} // nwm_LogModemInitError()


/***************************************************************************
FUNCTION: nwm_GetModemNetwork_Params

DESCRIPTION: This function read all modem and network related EEPROM parameters
from flash. If the EEPROM parameters are not available, use defaults. The function
also pre-processes some of the parameters.

ARGS:
        <none>

RETURNS:
    <none>

****************************************************************************/
void nwm_GetModemNetwork_Params(void)
{
    char filename[NWM_HTTP_FILE_NAME_MAX_SIZE];

    // clear and initialize nwv_htppISP_Param values
    memset((char *)&nwv_HttpISP_Param, '\0', sizeof(nwst_HttpISP_Param));

    // Read http server from Flash. if it not provided, use the default.
    bsm_EEReadBuf((UINT8*)nwv_HttpISP_Param.http_ServerName, coc_HTTPServerName_SIZE, coc_HTTPServerName_ADDR);

    nwv_HttpISP_Param.http_ServerName[NWM_HTTP_SERVER_NAME_MAX_SIZE-1] = 0; // ensure result is null terminated

    if ( (nwv_HttpISP_Param.http_ServerName[0] & 0xFF) == 0x00ff)           // If it is the unprogrammed,
    {
        strcpy((char*)nwv_HttpISP_Param.http_ServerName, NWC_HTTP_DEF_SERVER); // Set to default.
    }

    // Read http user name from flash
    bsm_EEReadBuf((UINT8*)nwv_HttpISP_Param.http_UserName, coc_HTTPLoginID_SIZE, coc_HTTPLoginID_ADDR);

    nwv_HttpISP_Param.http_UserName[NWM_HTTP_USER_NAME_MAX_SIZE-1] = 0; // ensure result is null terminated

    // Read http password from the flash
    bsm_EEReadBuf((UINT8*)nwv_HttpISP_Param.http_UserPassword, coc_HTTPPassword_SIZE, coc_HTTPPassword_ADDR);

    nwv_HttpISP_Param.http_UserPassword[NWM_HTTP_USER_PASSWORD_MAX_SIZE-1] = 0; // ensure result is null terminated

    // Read the target page from the Flash. If it's not provided, use the default page.
    bsm_EEReadBuf((UINT8*)nwv_HttpISP_Param.http_FileName, coc_HTTPHomePage_SIZE, coc_HTTPHomePage_ADDR);

    if(nwv_HttpISP_Param.http_FileName[0] != 0xff)
    {
        nwv_HttpISP_Param.http_FileName[NWM_HTTP_FILE_NAME_MAX_SIZE-1] = 0; //ensure string is null-terminated

        //Ensure that the target page is prefixed with '/'
        if(nwv_HttpISP_Param.http_FileName[0] != '/')
        {
            strcpy(filename, "/");    //start string with '/' and null terminate
        }
        else
        {
            filename[0] = 0;    //null terminate string
        }

        strcat(filename, nwv_HttpISP_Param.http_FileName); //copy stored homepage parameter
        strcpy((char*)nwv_HttpISP_Param.http_FileName, filename);

    }
    else
    {
        strcpy((char*)nwv_HttpISP_Param.http_FileName, NWC_HTTP_DEF_DATA_PAGE);
    }

    // Read country code from flash. If it's not provided, use default.
    bsm_EEReadBuf((UINT8*)nwv_HttpISP_Param.mdm_CountryCode, coc_MDMCountryCode_SIZE, coc_MDMCountryCode_ADDR);

    nwv_HttpISP_Param.mdm_CountryCode[MDM_COUNTRY_CODE_MAX_SIZE-1] = 0;     // ensure result is null terminated

    if ( (nwv_HttpISP_Param.mdm_CountryCode[0] & 0xFF) == 0x00ff)           // If it is the unprogrammed
    {
        strcpy((char*)nwv_HttpISP_Param.mdm_CountryCode, NWC_DEFAULT_COUNTRY_CODE); // Set to default.
    }

    // Read the ISP Auth Method from flash. If it's not provided, use default.
    bsm_EEReadBuf((UINT8*)nwv_HttpISP_Param.ISP_AuthMethod, coc_ISPAuthMethod_SIZE, coc_ISPAuthMethod_ADDR);

    nwv_HttpISP_Param.ISP_AuthMethod[ISP_AUTH_METHOD_MAX_SIZE-1]= 0; //ensure result is null-terminated

    if ( (nwv_HttpISP_Param.ISP_AuthMethod[0] & 0xFF) == 0xFF)
    {
        strcpy((char*)nwv_HttpISP_Param.ISP_AuthMethod, NWC_DEF_ISPAUTH_TYPE);
    }

    // Read Verizon phone number from flash. If it's not provided, use default.
    bsm_EEReadBuf((UINT8*)nwv_HttpISP_Param.ISP_Phone1, coc_ISPPhone1_SIZE, coc_ISPPhone1_ADDR);

    nwv_HttpISP_Param.ISP_Phone1[ISP_PHONE1_MAX_SIZE-1]= 0; //ensure result is null-terminated

    if ( (nwv_HttpISP_Param.ISP_Phone1[0] & 0xFF) == 0xFF)
    {
        strcpy((char*)nwv_HttpISP_Param.ISP_Phone1, NWC_DEF_VERIZON_PHONE);
    }

    // Read AT&T phone number from flash. If it's not provided, use default.
    bsm_EEReadBuf((UINT8*)nwv_HttpISP_Param.ISP_Phone2, coc_ISPPhone2_SIZE, coc_ISPPhone2_ADDR);

    nwv_HttpISP_Param.ISP_Phone2[ISP_PHONE2_MAX_SIZE-1]= 0; //ensure result is null-terminated

    if ( (nwv_HttpISP_Param.ISP_Phone2[0] & 0xFF) == 0xFF)
    {
        strcpy((char*)nwv_HttpISP_Param.ISP_Phone2, NWC_DEF_ATT_PHONE);
    }

    // Read last working phone flag from flash.
    bsm_EEReadBuf((UINT8*)nwv_HttpISP_Param.ISP_LastWorkPhoneFlag, coc_ISPLastWorkPhoneFlag_SIZE, coc_ISPLastWorkPhoneFlag_ADDR);

    nwv_HttpISP_Param.ISP_LastWorkPhoneFlag[ISP_LASTWORKPHONEFLAG_MAX_SIZE-1]= 0; //ensure result is null-terminated

    //Initialize the last working phone to phone1 if this is very first call.
    if ( (nwv_HttpISP_Param.ISP_LastWorkPhoneFlag[0] & 0xFF) == 0xFF)
    {
        strcpy((char*)nwv_HttpISP_Param.ISP_LastWorkPhoneFlag, PHONE1);
    }

    // Read last working prefix from flash (NOTE: string value is pointer to prefix SW position)
    // Valid values: 'N', '7', '8', '9'  (all other values are considered invalid)
    bsm_EEReadBuf((UINT8*)nwv_HttpISP_Param.ISP_LastWorkPrefix, coc_ISPLastWorkPrefix_SIZE, coc_ISPLastWorkPrefix_ADDR);

    nwv_HttpISP_Param.ISP_LastWorkPrefix[ISP_LASTWORKPREFIX_MAX_SIZE-1]= 0; //ensure result is null-terminated

    // Read ISP hostname from flash. If it's not provided, use default.
    bsm_EEReadBuf((UINT8*)nwv_HttpISP_Param.ISP_HostName, coc_ISPHostName_SIZE, coc_ISPHostName_ADDR);

    nwv_HttpISP_Param.ISP_HostName[ISP_HOST_NAME_MAX_SIZE-1] = 0;     //ensure result is null-terminated

    if ( (nwv_HttpISP_Param.ISP_HostName[0] & 0xFF) == 0xFF)
    {
        strcpy((char*)nwv_HttpISP_Param.ISP_HostName, NWC_DEF_HOSTNAME);
    }

    // Read ISP user name from flash
    bsm_EEReadBuf((UINT8*)nwv_HttpISP_Param.IP_UserName, coc_IPLoginID_SIZE, coc_IPLoginID_ADDR);

    nwv_HttpISP_Param.IP_UserName[ISP_USER_NAME_MAX_SIZE-1] = 0;     //ensure result is null-terminated

    // Read ISP password from flash
    bsm_EEReadBuf((UINT8*)nwv_HttpISP_Param.IP_Password, coc_IPPassword_SIZE, coc_IPPassword_ADDR);

    nwv_HttpISP_Param.IP_Password[ISP_PASSWORD_MAX_SIZE-1] = 0;     //ensure result is null-terminated

    // Read DNS from flash
    bsm_EEReadBuf((UINT8*)nwv_HttpISP_Param.nwm_StaticDNS, coc_StaticDNS_SIZE, coc_StaticDNS_ADDR);

    nwv_HttpISP_Param.nwm_StaticDNS[NWM_STATIC_DNS_MAX_SIZE-1] = 0;     //ensure result is null-terminated

    // Read the dial prefix from the Flash. If it's not provided, use default.
    bsm_EEReadBuf((UINT8*)nwv_HttpISP_Param.mdm_DialPrefix, coc_DIALPREFIX_SIZE, coc_DIALPREFIX_ADDR);

    nwv_HttpISP_Param.mdm_DialPrefix[MDM_DIAL_PREFIX_MAX_SIZE-1] = 0; //ensure result is null-terminated

    if ( (nwv_HttpISP_Param.mdm_DialPrefix[0] & 0xFF) == 0x00ff)
    {
        strcpy((char*)nwv_HttpISP_Param.mdm_DialPrefix, NWC_DEF_PHONE_PREFIX );
    }

}

/*
 *****************************************************************************
 * FUNCTION: nwm_FlushAndClearEventLogBlock
 *
 * DESCRIPTION:
 *     This function is called after a successful asset file upload.
 *     It does the following:
 *     - Save the asset log entries written after the asset file upload.
 *     - Clear the event log block.
 *     - Copy the saved asset log entries.
 *
 * INPUTS:
 *     None.
 *
 * RETURNS:
 *     None
 *
 * NOTE:
 ********************************************************************************/
void nwm_FlushAndClearEventLogBlock(void)
{
    UINT32 numOfBytes;

    // If asset log entries were written after the asset file upload, save them.
    numOfBytes = bsm_EHAssetLogToBuffer();

    // Clear the event log block.
    bsm_EHClearLog();

    // Copy the saved asset log entries.
    bsm_EHBufferToAssetLog(numOfBytes);

    if (numOfBytes != 0)
    {
        bsm_SDPrint("Asset log data restored");
    }
    return;

} //end of nwm_FlushAndClearEventLogBlock

/***************************************************************************
FUNCTION: nwm_Get_CurrentPhoneNumber

DESCRIPTION: This function gets current phone number. Using the last known
working phone number for the 1st dial attempt. Switch to the other carrier
if the previous dial attempt fails for any reason.

ARGS:
        int: dial_attempts - number of dial attempts

RETURNS:
    <none>

****************************************************************************/
void nwm_Get_CurrentPhoneNumber(UINT16 dial_attempts)
{

    // The first dial attempt always use last known working phone
    if (dial_attempts == 0)
    {
        strcpy((char*)lastWorkPhoneFlag, nwv_HttpISP_Param.ISP_LastWorkPhoneFlag);

        if( strcmp((char*)lastWorkPhoneFlag, PHONE1) == 0 )
        {
            strcpy((char*)phone_number, nwv_HttpISP_Param.ISP_Phone1);
        }
        else if ( strcmp((char*)lastWorkPhoneFlag, PHONE2) == 0 )
        {
            strcpy((char*)phone_number, nwv_HttpISP_Param.ISP_Phone2);
        }
        else
        {
            //This should not happen unless the EEPROM get corrupted
            //Monitor uses phone1 to dial
            strcpy((char*)phone_number, nwv_HttpISP_Param.ISP_Phone1);
            strcpy((char*)lastWorkPhoneFlag, PHONE1);
            bsm_EHLog("Invalid last working phone flag.",0);

        }
    }
    else //Subsequence dial attempt switch to other carrier
    {
        if( strcmp((char*)phone_number, nwv_HttpISP_Param.ISP_Phone1 ) == 0 )
        {
            strcpy((char*)phone_number, nwv_HttpISP_Param.ISP_Phone2);
            strcpy((char*)lastWorkPhoneFlag, PHONE2);
        }
        else
        {
            strcpy((char*)phone_number, nwv_HttpISP_Param.ISP_Phone1);
            strcpy((char*)lastWorkPhoneFlag, PHONE1);
        }
    }
}

/***************************************************************************
FUNCTION: nwm_isDualCarrier

DESCRIPTION: This function checks the dual carrier availability by comparing
phone1 and phone2 numbers.

ARGS:

RETURNS:
    True if two phone numbers are different
        False if two phone numbers are same


****************************************************************************/

bool nwm_isDualCarrier(void)
{
    if (strcmp(nwv_HttpISP_Param.ISP_Phone1, nwv_HttpISP_Param.ISP_Phone2) == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

/***************************************************************************
FUNCTION: nwm_SaveLastWorkPhone

DESCRIPTION: This function saves current phone number into NVStorage as last
known working phone number.

ARGS:
        <none>

RETURNS:
    <none>

****************************************************************************/
void nwm_SaveLastWorkPhone(void)
{
    //Save current phone to last known working phone in NVstorage
    bsm_EEWriteBuf((char*)lastWorkPhoneFlag, coc_ISPLastWorkPhoneFlag_SIZE, coc_ISPLastWorkPhoneFlag_ADDR);
    bsm_EEFlush();
}

/***************************************************************************
FUNCTION: nwm_FindDialPrefixIndex

DESCRIPTION: This function find the Prefix Index used for next dial attempt
based on the last used prefix index, the current position of prefix SW
index, the last work prefix index, etc.
The found prefix index is put in the global variable dial_prefix_index.
 [0]:<None>, [1]: '7', [2]: '8', [3]: '9',
               [INVALID_PREFIX_INDEX] - max incompatible equipment reached
                                        (no more dial attempts allowed)


The selection list is as:
  - if last work prefix is valid
Step 1. Current SW - if current SW position is changed from last dialing and IE<2
Step 2. last work prefix, if IE<2
Step 3. None prefix, if IE<2
Step 4. Current SW - if current SW position isn't changed from last dialing and IE<2

  - if last work prefix is invalid
Step 1. Current SW - if IE<2
Step 2. None prefix, if IE<2
Step 3. Current SW - if current SW position isn't changed from last dialing and IE<2


Index    SW Location
  0        <None>
  1         '7'
  2         '8'
  3         '9'

ARGS:  <none>

RETURNS:
    <none>
****************************************************************************/
void nwm_FindDialPrefixIndex(void)
{
    UINT16                current_prefix_sw_index;
    bst_DialSwitchState   dial_prefix_sw;

    // Read the currentSW position & determine its index.
    dial_prefix_sw = bsm_INReadDial();
    switch(dial_prefix_sw)
    {
        case bsc_DIAL4:
            current_prefix_sw_index = 3;  // SW = '9' position
            break;
        case bsc_DIAL3:
            current_prefix_sw_index = 2;  // SW = '8' position
            break;
        case bsc_DIAL2:
            current_prefix_sw_index = 1;  // SW = '7' position
            break;
        case bsc_DIAL1:                   // SW = 'None' position
        default:
            current_prefix_sw_index = 0;
            break;
    }
    // Determine if monitor is 2020C
    if ( aim_MonitorIsA2020C() )
    {
        // 2020C Monitor, use dial prefix switch setting for all dial attempts
        dial_prefix_index = current_prefix_sw_index;
        return;
    } // end - if (2020C Monitor)
    // In case of incompatible equipment error, increment the count.
    if (incomp_equip_2490H == 1)
    {
        prefix_incomp_dial_counts[dial_prefix_index]++;
    }

    // If lastWorkPrefixIndex is invalid, try using currentSW or nonePrefix index.
    if (lastWorkPrefixIndex > MAX_PREFIX_INDEX)
    {
        printf2490("lastWorkPrefixIndex is invalid");

        // Try using currentSW index
        if(prefix_incomp_dial_counts[current_prefix_sw_index] < NWC_MAX_INCOMP_EQUIP)
        {
            last_used_prefix_sw_index = current_prefix_sw_index;
            dial_prefix_index = current_prefix_sw_index;
            printf2490("Use currentSW, dial_prefix_index=0x%x", dial_prefix_index);
            return;
        }
        // Try using nonePrefix index
        else if(prefix_incomp_dial_counts[0] <NWC_MAX_INCOMP_EQUIP)
        {
             dial_prefix_index = 0;
             printf2490("Use nonePrefix, dial_prefix_index=0x%x", dial_prefix_index);
             return;
        }

        // Sorry, exhausted all options.
        dial_prefix_index = INVALID_PREFIX_INDEX;
        printf2490("Stop dialing, dial_prefix_index=0x%x", dial_prefix_index);
        return;
    }

    // lastWorkPrefixIndex is valid.
    // If currentSW has changed, try new currentSW/lastWorkPrefix/nonePrefix ind
    if (last_used_prefix_sw_index != current_prefix_sw_index)
    {
        printf2490("currentSW has changed");

        // Try using currentSW index
      if(prefix_incomp_dial_counts[current_prefix_sw_index] < NWC_MAX_INCOMP_EQUIP)
      {
            last_used_prefix_sw_index = current_prefix_sw_index;
            dial_prefix_index = current_prefix_sw_index;
            printf2490("Use new currentSW, dial_prefix_index=0x%x", dial_prefix_index);
            return;
      }
        // Try using lastWorkPrefix index
        else if (prefix_incomp_dial_counts[lastWorkPrefixIndex] <NWC_MAX_INCOMP_EQUIP)
        {
            dial_prefix_index = lastWorkPrefixIndex;
            printf2490("Use lastWorkPrefix, dial_prefix_index=0x%x", dial_prefix_index);
            return;
        }
        // Try using nonePrefix index
        else if(prefix_incomp_dial_counts[0] <NWC_MAX_INCOMP_EQUIP)
        {
            dial_prefix_index = 0;
            printf2490("Use nonePrefix, dial_prefix_index=0x%x", dial_prefix_index);
            return;
        }
        // Sorry, exhausted all options.
        dial_prefix_index = INVALID_PREFIX_INDEX;
        printf2490("Stop dialing, dial_prefix_index=0x%x", dial_prefix_index);
        return;
    }

    // If no incompatible equipment error, use same prefix as before.
    if (incomp_equip_2490H == 0)
    {
        printf2490("No incompEquipErr, use same dial_prefix_index=0x%x",
                    dial_prefix_index);
        return;
    }
    // If only one incompatible equipment error, use same prefix as before.
    if ((incomp_equip_2490H == 1) && (prefix_incomp_dial_counts[dial_prefix_index] < NWC_MAX_INCOMP_EQUIP))
    {
        printf2490("Only 1 incompEquipErr, use same dial_prefix_index=0x%x",
                    dial_prefix_index);
        return;
    }

    // Try using lastWorkPrefix index
    if (prefix_incomp_dial_counts[lastWorkPrefixIndex] <NWC_MAX_INCOMP_EQUIP)
    {
        dial_prefix_index = lastWorkPrefixIndex;
        printf2490("Use lastWorkPrefix, dial_prefix_index=0x%x", dial_prefix_index);
        return;
    }

    // Try using nonePrefix index
    if(prefix_incomp_dial_counts[0] <NWC_MAX_INCOMP_EQUIP)
    {
        dial_prefix_index = 0;
        printf2490("Use nonePrefix, dial_prefix_index=0x%x", dial_prefix_index);
        return;
    }

    // Try using currentSW
    if(prefix_incomp_dial_counts[current_prefix_sw_index] <NWC_MAX_INCOMP_EQUIP)
    {
        last_used_prefix_sw_index = current_prefix_sw_index;
        dial_prefix_index = current_prefix_sw_index;
        printf2490("Use currentSW, dial_prefix_index=0x%x", dial_prefix_index);
        return;
    }

    // Sorry, exhausted all options.
    dial_prefix_index = INVALID_PREFIX_INDEX;
    printf2490("Stop dialing, dial_prefix_index=0x%x", dial_prefix_index);
    return;
}

/***************************************************************************
FUNCTION: nwm_GetLastWorkPrefixIndex

DESCRIPTION: This function gets last working prefix read from NV storage
             and converts null terminated string into an index value
             based on the table below:

 Value from NVStorage    Prefix
 (Null terminated)       Index
      'N'                  0
      '7'                  1
      '8'                  2
      '9'                  3
   All others            0xFF

ARGS:
    <none>

RETURNS:
    UINT16 : prefixIndex - index value converted from string saved in NVRAM
              'N' -> 0, '7' -> 1, '8' -> 2, '9' - > 3,
              All others -> INVALID_PREFIX_INDEX (0xFF)

****************************************************************************/
UINT16 nwm_GetLastWorkPrefixIndex(void)
{
    UINT16 prefixIndex;

    // Read last working prefix from flash (NOTE: string value is pointer to prefix SW position)
    // Valid values: 'N', '7', '8', '9'  (all other values are considered invalid)
    bsm_EEReadBuf((UINT8*)lastWorkPrefix, coc_ISPLastWorkPrefix_SIZE, coc_ISPLastWorkPrefix_ADDR);

    lastWorkPrefix[ISP_LASTWORKPREFIX_MAX_SIZE-1]= 0; //ensure result is null-terminated

    // Convert Last Working Prefix from NVRAM to a prefix index value
    if (strcmp(lastWorkPrefix, PREFIX_N_INDEX_0) == 0)
    {
        prefixIndex = 0;
    }
    else if (strcmp(lastWorkPrefix, PREFIX_7_INDEX_1) == 0)
    {
        prefixIndex = 1;
    }
    else if (strcmp(lastWorkPrefix, PREFIX_8_INDEX_2) == 0)
    {
        prefixIndex = 2;
    }
    else if (strcmp(lastWorkPrefix, PREFIX_9_INDEX_3) == 0)
    {
        prefixIndex = 3;
    }
    else
    {
        prefixIndex = INVALID_PREFIX_INDEX;
    }

    return prefixIndex;

}
/***************************************************************************
FUNCTION: nwm_GetLastUsedPrefixIndex

DESCRIPTION: This function gets last used prefix read from NV storage
             and converts null terminated string into an index value
             based on the table below:

 Value from NVStorage    Prefix
 (Null terminated)       Index
      'N'                  0
      '7'                  1
      '8'                  2
      '9'                  3
   All others            0xFF

ARGS:
    <none>

RETURNS:
    UINT16 : prefixIndex - index value converted from string saved in NVRAM
              'N' -> 0, '7' -> 1, '8' -> 2, '9' - > 3,
              All others -> INVALID_PREFIX_INDEX (0xFF)

****************************************************************************/
UINT16 nwm_GetLastUsedPrefixIndex(void)
{
    UINT16 prefixIndex;
    //Read  last used prefix from flash (NOTE: string value is pointer to prefix SW position)
    bsm_EEReadBuf((UINT8*)lastUsedPrefix, coc_LastUsedPrefix_SIZE, coc_LastUsedPrefix_ADDR);
    lastUsedPrefix[NWM_LASTUSEDPREFIX_MAX_SIZE-1]= 0; //ensure result is null-terminated

    // Convert Last Used Prefix from NVRAM to a prefix index value
    if (strcmp(lastUsedPrefix, PREFIX_N_INDEX_0) == 0)
    {
        prefixIndex = 0;
    }
    else if (strcmp(lastUsedPrefix, PREFIX_7_INDEX_1) == 0)
    {
        prefixIndex = 1;
    }
    else if (strcmp(lastUsedPrefix, PREFIX_8_INDEX_2) == 0)
    {
        prefixIndex = 2;
    }
    else if (strcmp(lastUsedPrefix, PREFIX_9_INDEX_3) == 0)
    {
        prefixIndex = 3;
    }
    else
    {
        prefixIndex = INVALID_PREFIX_INDEX;
    }

    return prefixIndex;

}


/***************************************************************************
FUNCTION: nwm_SaveLastUsedPrefixAndWorkPrefix

DESCRIPTION: This function converts and saves the last used prefix SW Index
value into NVRAM as a null terminated string based on the table below.
And save the call nwm_SaveLastWorkPrefix when dial status is OK.

 Prefix    ---- Last Working Prefix String ----
 Index     lastUsedPrefix[0]   lastUsedPrefix[1]
   0             'N'               <NULL>
   1             '7'               <NULL>
   2             '8'               <NULL>
   3             '9'               <NULL>
  >3             0xFF              <NULL>

ARGS:
    UINT16 : dial_status - the last dial status


RETURNS:
    <none>

****************************************************************************/
void nwm_SaveLastUsedPrefixAndWorkPrefix(UINT16 dial_status)
{

    // Convert prefix index value to specific null terminated string
    switch (last_used_prefix_sw_index)
    {
        case 0:  // Index=0 -> 'N'
            strcpy((char*)lastUsedPrefix, PREFIX_N_INDEX_0);
            break;
        case 1:  // Index=1 -> '7'
            strcpy((char*)lastUsedPrefix, PREFIX_7_INDEX_1);
            break;
        case 2:  // Index=0 -> '8'
            strcpy((char*)lastUsedPrefix, PREFIX_8_INDEX_2);
            break;
        case 3:  // Index=0 -> '9'
            strcpy((char*)lastUsedPrefix, PREFIX_9_INDEX_3);
            break;
        default: // Index>3 -> 0xFF
            lastUsedPrefix[0] = INVALID_PREFIX_INDEX;
            lastUsedPrefix[1] = 0;
            break;
    }

    // Save converted prefix into NVRAM (last used prefix)
    bsm_EEWriteBuf((char*)lastUsedPrefix, coc_LastUsedPrefix_SIZE, coc_LastUsedPrefix_ADDR);
    if(dial_status == NWC_OK)
    {
        //save dial_prefix_index as the lastworkprefix when dial is OK
        nwm_SaveLastWorkPrefix(dial_prefix_index);
    }
    bsm_EEFlush();
}//end of nwm_SaveLastUsedPrefixAndWorkPrefix
/***************************************************************************
FUNCTION: nwm_SaveLastWorkPrefix

DESCRIPTION: This function converts and saves a specified prefixIndex
value into NVRAM as a null terminated string based on the table below:

 Prefix    ---- Last Working Prefix String ----
 Index     lastWorkPrefix[0]   lastWorkPrefix[1]
   0             'N'               <NULL>
   1             '7'               <NULL>
   2             '8'               <NULL>
   3             '9'               <NULL>
  >3             0xFF              <NULL>

ARGS:
    UINT16 : prefixIndex - index value to convert into string then
                           save into NVRAM for last working prefix

RETURNS:
    <none>

****************************************************************************/
void nwm_SaveLastWorkPrefix(UINT16 prefixIndex)
{

    // Convert prefix index value to specific null terminated string
    switch (prefixIndex)
    {
        case 0:  // Index=0 -> 'N'
            strcpy((char*)lastWorkPrefix, PREFIX_N_INDEX_0);
            break;
        case 1:  // Index=1 -> '7'
            strcpy((char*)lastWorkPrefix, PREFIX_7_INDEX_1);
            break;
        case 2:  // Index=0 -> '8'
            strcpy((char*)lastWorkPrefix, PREFIX_8_INDEX_2);
            break;
        case 3:  // Index=0 -> '9'
            strcpy((char*)lastWorkPrefix, PREFIX_9_INDEX_3);
            break;
        default: // Index>3 -> 0xFF
            lastWorkPrefix[0] = INVALID_PREFIX_INDEX;
            lastWorkPrefix[1] = 0;
            break;
    }

    // Save converted prefix index into NVRAM (last working prefix)
    bsm_EEWriteBuf((char*)lastWorkPrefix, coc_ISPLastWorkPrefix_SIZE, coc_ISPLastWorkPrefix_ADDR);

} //end of nwm_SaveLastWorkPrefix