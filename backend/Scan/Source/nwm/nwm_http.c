/************************************************************************

 MODULE: Network module HTTP code.

 OWNER:

 $Revision$

 $Date$

 $RCSfile$

 DESCRIPTION: This module contains the http related network code.

************************************************************************/
/**************************************************************************
                       - Include Files -
***************************************************************************/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>   //For sprintf (string manipulation)
#include "nwm_net.h"
#include "nwm_http.h"

#include "com_eepromapp.h"
#include "global.h"
#include "bsm_global.h"
#include "cx077.h" //Modem header file
#include "uim_ui.h"

#include "fsm_pbfr.h"
#include "fsm_file.h"
#include "fsm_encrypt.h"

#include "aim_kappa.h"
#include "nwm_httpdigest.h"
#include "zlm_decompress.h"

/***************************************************************************
                                        - Private Function	-
****************************************************************************/
UINT16 nwm_Process_HTTP_UNAUTHORIZED(http_request_data *http_rec);
bool nwm_Process_HTTP_Authenticate_Get(UINT16 *status, http_request_data *http_request, char *idstr);
char *nwm_HTTP_find_header(char *header, char *buffer, char *end_buffer, INT16 case_sensitivity);
void nwm_HTTP_Initialization(const int numberForms, const char *httpDefaulpage);

/*******************************************************************************
                      - Global Variables -
*******************************************************************************/
char                      dateTime[HTTP_DATETIME_LEN +1]; //+1 for null, holds a date/time string from server
UINT32                    dateTimeTicks; //systems tick that cooresponds to the date/time string
form_struct               formArr[NWC_MAX_NUM_FORMS]; //array of forms
char                      formNameArr[NWC_MAX_NUM_FORMS][NWC_MAX_FORM_NAME_SIZE]; //array to hold form name strings
char                      formFileNameArr[NWC_MAX_NUM_FORMS][NWC_MAX_FORM_NAME_SIZE]; //array to hold form file name strings
http_request_data         http_request;
char                      http_str[MDM_STRING_128];   //temp for string data and dialing string
static http_digest_struct digest = { 0 };

char sendHeader[   NWC_HTML_SEND_HEADER_SIZE];   //raw header buffer
char serverName[NWM_HTTP_SERVER_NAME_MAX_SIZE];
char filename[NWM_HTTP_FILE_NAME_MAX_SIZE];
char user_name[NWM_HTTP_USER_NAME_MAX_SIZE];
char user_password[NWM_HTTP_USER_PASSWORD_MAX_SIZE];

#pragma DATA_SECTION (returnbuffer,   ".nwm_file00");
char returnbuffer  [ NWC_HTML_RECEIVE_BUFFER_PART_SIZE]; //raw response buffer
#pragma DATA_SECTION (returnbuffer01, ".nwm_file01");
char returnbuffer01[ NWC_HTML_RECEIVE_BUFFER_PART_SIZE]; //raw response buffer
#pragma DATA_SECTION (returnbuffer02, ".nwm_file02");
char returnbuffer02[ NWC_HTML_RECEIVE_BUFFER_PART_SIZE]; //raw response buffer
#pragma DATA_SECTION (returnbuffer03, ".nwm_file03");
char returnbuffer03[ NWC_HTML_RECEIVE_BUFFER_PART_SIZE]; //raw response buffer
#pragma DATA_SECTION (returnbuffer04, ".nwm_file04");
char returnbuffer04[ NWC_HTML_RECEIVE_BUFFER_PART_SIZE]; //raw response buffer
#pragma DATA_SECTION (returnbuffer05, ".nwm_file05");
char returnbuffer05[ NWC_HTML_RECEIVE_BUFFER_PART_SIZE]; //raw response buffer
#pragma DATA_SECTION (returnbuffer06, ".nwm_file06");
char returnbuffer06[ NWC_HTML_RECEIVE_BUFFER_PART_SIZE]; //raw response buffer
#pragma DATA_SECTION (returnbuffer07, ".nwm_file07");
char returnbuffer07[ NWC_HTML_RECEIVE_BUFFER_PART_SIZE]; //raw response buffer
#pragma DATA_SECTION (returnbuffer08, ".nwm_file08");
char returnbuffer08[ NWC_HTML_RECEIVE_BUFFER_PART_SIZE]; //raw response buffer
#pragma DATA_SECTION (returnbuffer09, ".nwm_file09");
char returnbuffer09[ NWC_HTML_RECEIVE_BUFFER_PART_SIZE]; //raw response buffer
#pragma DATA_SECTION (returnbuffer10, ".nwm_file10");
char returnbuffer10[ NWC_HTML_RECEIVE_BUFFER_PART_SIZE]; //raw response buffer
#pragma DATA_SECTION (returnbuffer11, ".nwm_file11");
char returnbuffer11[ NWC_HTML_RECEIVE_BUFFER_PART_SIZE]; //raw response buffer
#pragma DATA_SECTION (returnbuffer12, ".nwm_file12");
char returnbuffer12[ NWC_HTML_RECEIVE_BUFFER_PART_SIZE]; //raw response buffer
#pragma DATA_SECTION (returnbuffer13, ".nwm_file13");
char returnbuffer13[ NWC_HTML_RECEIVE_BUFFER_PART_SIZE]; //raw response buffer
#pragma DATA_SECTION (returnbuffer14, ".nwm_file14");
char returnbuffer14[ NWC_HTML_RECEIVE_BUFFER_PART_SIZE]; //raw response buffer
#pragma DATA_SECTION (returnbuffer15, ".nwm_file15");
char returnbuffer15[ NWC_HTML_RECEIVE_BUFFER_PART_SIZE]; //raw response buffer

// This is a list of all the flash tags and addresses that are updateable
// through the FDN.
flash_tag tag[] =
{
    {coc_DIALPREFIX_ADDR,      coc_DIALPREFIX_SIZE,      "DialPrefix:"  },   //00
    {coc_HTTPHomePage_ADDR,    coc_HTTPHomePage_SIZE,    "HomePage:"    },   //01
    {coc_ISPHostName_ADDR,     coc_ISPHostName_SIZE,     "ISPHostName:" },   //02
    {coc_HTTPServerName_ADDR,  coc_HTTPServerName_SIZE,  "Server:"      },   //03
    {coc_ISPPhone1_ADDR,       coc_ISPPhone1_SIZE,       "Phone1:"      },   //04
    {coc_ISPPhone2_ADDR,       coc_ISPPhone2_SIZE,       "Phone2:"      },   //05
    {coc_ISPPhone3_ADDR,       coc_ISPPhone3_SIZE,       "Phone3:"      },   //06
    {coc_ISPPhone4_ADDR,       coc_ISPPhone4_SIZE,       "Phone4:"      },   //07
    {coc_MDMCountryCode_ADDR,  coc_MDMCountryCode_SIZE,  "Country:"     },   //08
    {coc_ISPAuthMethod_ADDR,   coc_ISPAuthMethod_SIZE,   "ISPAuth:"     },   //09
    {coc_StaticDNS_ADDR,       coc_StaticDNS_SIZE,       "DNS:"         }    //10
};
#define NWC_EE_NUM_CONST 11
// size of all the flash parameters added together
#define FDN_PARAMETER_SIZE  coc_DIALPREFIX_SIZE +       \
                            coc_HTTPHomePage_SIZE +     \
                            coc_ISPHostName_SIZE +      \
                            coc_HTTPServerName_SIZE +   \
                            coc_ISPPhone1_SIZE +        \
                            coc_ISPPhone2_SIZE +        \
                            coc_ISPPhone3_SIZE +        \
                            coc_ISPPhone4_SIZE +        \
                            coc_MDMCountryCode_SIZE +   \
                            coc_ISPAuthMethod_SIZE +    \
                            coc_StaticDNS_SIZE
// storage for backup and restore of FW update flash parameters
char fdn_parameters[FDN_PARAMETER_SIZE];

// Private function prototypes
void backup_fdn_parameters(void);
void restore_fdn_parameters(void);


/********************************************************************************
FUNCTION: nwm_HTTP_Send_Data

DESCRIPTION: This function handles the HTTP sequence for authenticating
             and sending the data file.

ARGS:
    <none>
RETURNS:
    UINT16 status.
*********************************************************************************/
UINT16 nwm_HTTP_Send_Data(void)
{
    UINT16 status;
    UINT16 attempts;     //temp to hold file transfer attempts

    // Initialize http. Target page has been determined in function
    // nwm_GetModemNetwork_Params() and stored in nwv_HttpISP_Param.http_FileName
    nwm_HTTP_Initialization(NWC_NUM_SEND_FORMS, nwv_HttpISP_Param.http_FileName);

    if(nwm_Process_HTTP_Authenticate_Get(&status, &http_request, ""))
    {
        // set tick time for date/time string
        dateTimeTicks = NU_Retrieve_Clock();
        nwm_Extract_DateTime(http_request.returnbuf, dateTime);

        #ifdef NWM_API_UNIT_TEST
        {
                        #warn "WARNING: Network API call test enabled"
            char   dateTimestr[HTTP_DATETIME_LEN+1];             // for date/time string
            UINT32 ticks;                                // for system tick time
            nwm_RetrieveHTTPDateTime(dateTimestr, &ticks);
        }
                #endif

        // Log the connect time provided by the server for reference.
        strcpy(http_str, "HTTP: Server time: ");
        strcat(http_str, dateTime);
        bsm_EHLog((char*)http_str,0);

        // Move on to the POST - Check for NU_SUCCESS and HTTP 200 OK.
        bsm_EHLog("HTTP: DIGEST Authentication successful.",status);
        // Set HTTP non-defaults.
        http_request.method_type      = HTTP_METHOD_POST;
        http_request.send_header[0]   = 0;
        http_request.send_header_size = strlen(http_request.send_header);
        http_request.numforms         = NWC_NUM_SEND_FORMS;
        http_request.return_type      = HTTP_FORM_VALUE_TYPE_16;

        // setup form_data
        strcpy( formArr[0].name,      NWC_DEFAULT_FORMNAME);
        formArr[0].file_name  = NULL;  //file_name is optional
        formArr[0].input_type = HTTP_INPUT_TYPE_FILE;

        // Extract the POST parameters from the html.
        nwm_Extract_HTTP_Target(&formArr[0]);

        // Increment the file transfer attempts.
        bsm_EEReadBuf((UINT8*)http_str, coc_FileTransferAttempts_SIZE, coc_FileTransferAttempts_ADDR);      // Read it.
        //place value into variable so it can be incremented
        attempts  = (http_str[0] & 0xFF) << 8;
        attempts |= (http_str[1] & 0xFF) << 0;
        if( attempts == 0xFFFF)   // If it is the unprogrammed Flash value,
        {
            attempts = 0;         // reset it to zero.
        }
        attempts++;               // Increment it.
        //unpack variable into buffer to write back to flash
        http_str[0] = (attempts & 0xFF00) >> 8;
        http_str[1] = (attempts & 0x00FF) >> 0;
        bsm_EEWriteBuf((UINT8*)http_str, coc_FileTransferAttempts_SIZE, coc_FileTransferAttempts_ADDR);     // Write it.

        // Update the data file with the asset information and encrypt.
        #ifndef LARGE_POST_TEST
        fsm_UpdateAssetDataAndCloseFile();
            #else
                #warn "WARNING: Large Post Test -- Incorrect patient data file to be uploaded"
        fsm_PackedBfrSetIndex(FSV_FILE,0);
        {
            UINT32 count;
            for (count = 0; count < 0x40000; count++)
            {
                fsm_PackedBfrWrite(FSV_FILE, ((char)count & 0xFF) + ((count / 256) & 0xFF) );
            }
        }
        bsm_SDPrint("CRC computation and data encryption ");
        fsm_FileCRC16();            // Add 2 bytes of CRC
        fsm_EncryptFile();              // Adds 6 bytes of padding
        bsm_SDPrint(" completed.");
        #endif


        // Update the data file pointer and length for the POST.
        formArr[0].value      = fsm_PackedBfrStartAddress(FSV_FILE);
        formArr[0].length     = fsm_PackedBfrGetIndex(FSV_FILE);
        formArr[0].value_type = HTTP_FORM_VALUE_TYPE_8_PACKED_HIGH;

#ifdef NETWORK_DEBUG
        http_request.timeout  = NWC_MAX_NETWORK_TIMEOUT1;
#else
        if(formArr[0].length>=NWC_LARGE_DATA_POST_BYTES)
        {
            http_request.timeout = NWC_MAX_NETWORK_TIMEOUT1;
        }

#endif
        // Log the number of bytes posted.
        strcpy(http_str, "HTTP: Posting ");
        ltoa( formArr[0].length, &http_str[strlen(http_str)]);
        strcat(http_str, " bytes.");
        bsm_EHLog(http_str, status);

        // Process the POST.
        status = http_Process_Request(&http_request);

        // If successful, check the HTML for a yea/nea.
        if(status == HTTP_STATUS_OK)
        {
            // Check the HTML for status of the file that was sent.
            if(strstr(http_request.return_body, NWC_HTML_DATA_ACCEPTED))
            {
                // Change the return status.
                status = NWC_OK;

                // Log the successful POST.
                bsm_EHLog("HTTP: Data POST successful.",status);

            }
            else if(strstr(http_request.return_body, NWC_HTML_DATA_REJECTED))
            {
                // Change the return status.
                status = NWC_ERR_HTTP_POST_FAILURE;

                // Log the POST failure.
                bsm_EHLog("HTTP: Data POST failure - CRC/Encryption.",status);
            }
            else  // Should not reach this error.
            {
                // Change the return status.
                status = NWC_ERR_HTTP_POST_FAILURE;

                // Log the POST failure.
                bsm_EHLog("HTTP: Data POST failure - HTML message.",status);
            }
        }
        else
        {
            // Log the POST failure.
            bsm_EHLog("HTTP: Data POST failure.",status);

            // Change the return status.
            status = NWC_ERR_HTTP_POST_FAILURE;
        }
    }
    else
    { //GET failed

        // Set the correct status. */
        status = NWC_ERR_HTTP_GET_FAILURE;
    } //End of if(nwm_Process_HTTP_Authenticate_Get(&status, &http_request, ""))

    // Hang up only if we did not upload. If the upload is successful, we want to update the software.
    if(status != NWC_OK)
    {
        // Ensure modem is on hook
        mdm_Send_Control_String(MDM_HANGUP_STR, http_str, sizeof(http_str));
    }

    return status;
}


/********************************************************************************

FUNCTION: nwm_HTTP_FirmwareUpdate

DESCRIPTION: This function handles the HTTP sequence for receiving
             new information such as phone numbers, a password or
             new program code.

DATA FORMAT: The format of the data returned by the server is as follows:

<Byte 1> Number of Sections

<Byte 2> Section Type
<Byte 3> Length of Section 1
<Byte 4> Length of Section 1
<Byte 5> Length of Section 1
<Byte 6> Length of Section 1
<Byte 7 ... A> Section 1 Data

<Byte A+1> Section Type
<Byte A+2> Length of Section 2
<Byte A+3> Length of Section 2
<Byte A+4> Length of Section 2
<Byte A+5> Length of Section 2
<Byte A+6 ... B> Section 2 Data

The last word is the CRC 16 of the file.

Secton Type is defined as:
0x01 - main code.
0x03 - Flash (ASCII)

The Flash is sent as a tag followed by a string terminated by a crlf.  The tags can be found
within the nwm_Update_Flash() function.
example: "Server:www.medtronic.com<cr><lf>"


ARGS:
    <none>
RETURNS:
    UINT16 status. NWC_ERR_SWUPDATE_FAILURE - an update began to be committed and failed
                   NWC_ERR_FAILURE - a failure but update did not start (flash remains intact)
                   NWC_OK - any other conditions are considered NWC_OK (no-update or update success).
*********************************************************************************/
UINT16 nwm_HTTP_FirmwareUpdate(void)
{
    UINT16 status;
    UINT32 size;   //size of file
    UINT16 server_crc;
    UINT16 crc;
    UINT16 num_sections;
    UINT16 section_type;
    UINT16 index;
    UINT32 su_SWVer;
    UINT32 currSWVer;
    UINT32 calcSWVer;
    UINT32 offset;
    UINT32 main_offset;
    UINT32 flash_offset;
    UINT32 len_main;
    UINT32 len_flash;
    UINT32 i;
    UINT16 * data_ptr;

    bool fwImageIsCompressed = false;
    bool haveMainCode        = false;

    // Initialize
    data_ptr = 0;

    nwm_HTTP_Initialization(NWC_NUM_SWUPDATE_FORMS, NWC_HTTP_DEF_FWUPDATE_PAGE);

    // Process the first GET.
    if(nwm_Process_HTTP_Authenticate_Get(&status, &http_request, "/FWUpdate"))
    {
        char dateTimeYMDStr[15] = {"XXXXXXXXXXXXXX"};
        char * p_YMDStr         = dateTimeYMDStr;

        if (strlen(aim_KappaGetInterrogationTimeDateString()) == 14)
        {
            p_YMDStr = aim_KappaGetInterrogationTimeDateString();
        }

        // Move on to the POST - Check for NU_SUCCESS and HTTP 200 OK.
        bsm_EHLog("HTTP/FWUpdate: DIGEST Authentication successful.",status);

        // Set HTTP non-defaults.
        http_request.method_type      = HTTP_METHOD_POST;
        http_request.send_header[0]   = 0;
        http_request.send_header_size = strlen(http_request.send_header);
        http_request.numforms         = NWC_NUM_SWUPDATE_FORMS;
        http_request.return_type      = HTTP_FORM_VALUE_TYPE_8_PACKED_HIGH;          //request that the response body be packedhigh

        // setup form_data
        strcpy( formArr[0].name, NWC_DEFAULT_FORMNAME);
        formArr[0].file_name  = NULL;  //file_name is optional
        formArr[0].input_type = HTTP_INPUT_TYPE_FILE;

        // Extract the POST parameters from the html.
        nwm_Extract_HTTP_Target(&formArr[0]);

        // Initialize the file and add the header information.
        fsm_OpenFile(aim_KappaGetWorkingDeviceIDString(),
                     aim_KappaGetCompleteSNString(),
                     p_YMDStr,
                     1);

        // Add the asset data.
        fsm_AssetData();

        bsm_SDPrint("CRC computation and data encryption ");
        // Calculate and append the CRC16.
        fsm_FileCRC16();

        // Encrypt the file.
        fsm_EncryptFile();

        bsm_SDPrint(" completed.");

        // Update the data file pointer and length for the POST.
        formArr[0].value      = (char*)fsm_PackedBfrStartAddress(FSV_FILE);
        formArr[0].length     = fsm_PackedBfrGetIndex(FSV_FILE);
        formArr[0].value_type = HTTP_FORM_VALUE_TYPE_8_PACKED_HIGH;

        // Log the number of bytes posted.
        strcpy(http_str, "HTTP/FWUpdate: Posting ");
        ltoa( formArr[0].length, &http_str[strlen(http_str)]);
        strcat(http_str, " bytes.");
        bsm_EHLog(http_str,status);

        // Process the POST.
        status = http_Process_Request(&http_request);

        // If successful, check the HTML for a yea/nea.
        if(status == HTTP_STATUS_OK)
        {
            status = NWC_OK;

            // Check the HTML for status of the file that was sent.
            if(bsm_packedStringSearch(http_request.return_body, NWC_HTML_DATA_REJECTED))
            {
                // Change the return status.
                status = NWC_ERR_FAILURE;

                // Log the POST failure.
                bsm_EHLog("HTTP/FWUpdate: Asset POST failure.", status);
            }
            else if(bsm_packedStringSearch(http_request.return_body, NWC_HTML_DATA_NONE))
            {
                // Change the return status.
                status = NWC_OK;

                // Log
                bsm_EHLog("HTTP/FWUpdate: No update.", status);
            }
            else  // The asset data posted successfully.
            {
                // Log the POST status.
                bsm_EHLog("HTTP/FWUpdate: Decrypting response.", status);

                // Setup base pointer and initial offset
                data_ptr     = (UINT16*)http_request.return_body;
                offset       = 0;
                main_offset  = 0;
                flash_offset = 0;

                // Decrypt the file.
                http_request.return_body_size = fsm_BlowfishForPackedData(
                    (UINT8*)data_ptr,                          // Starting memory address
                    http_request.return_body_size,             // Number of bytes
                    FALSE);                                    // Decrypt

                // Reduce the length by the crc length
                size = http_request.return_body_size - 2;

                // Extract the server-generated CRC.
                server_crc  = bsm_getByteFromPackedArray(data_ptr, size    ) << 8;
                server_crc += bsm_getByteFromPackedArray(data_ptr, size + 1);

                // Calculate the CRC16.
                crc = 0x0000; //setup initial crc seed
                for(i=0; i<size; i++) //calculate crc
                {
                    crc = aim_CRCPerByte(crc,  bsm_getByteFromPackedArray(data_ptr, i));
                }

                // Compare and check the CRC.
                if( server_crc == crc )
                {
                    // Log.
                    bsm_EHLog("HTTP/FWUpdate: Download complete-CRC match.", 0);

                    // Extract the number of sections.
                    num_sections = bsm_getByteFromPackedArray(data_ptr, offset);
                    offset++;

                    // Set the appropriate pointers.
                    for(index = 0; index < num_sections; index++)
                    {
                        section_type = bsm_getByteFromPackedArray(data_ptr, offset);
                        offset++; //incr ptr

                        switch(section_type)
                        {
                        case NWC_SU_MAIN_SECT:
                            // Compute the length.
                            len_main  = (UINT32)(bsm_getByteFromPackedArray(data_ptr, offset)) << 24;
                            offset++;    //incr ptr

                            len_main += (UINT32)(bsm_getByteFromPackedArray(data_ptr, offset)) << 16;
                            offset++;    //incr ptr

                            len_main += (UINT32)(bsm_getByteFromPackedArray(data_ptr, offset)) << 8;
                            offset++;    //incr ptr

                            len_main += (UINT32)(bsm_getByteFromPackedArray(data_ptr, offset));
                            offset++;    //incr ptr

                            // Determine if FW image is compressed.

                            fwImageIsCompressed = zlm_IsCompressed(data_ptr, offset,len_main);

                            // Save the offset to main.
                            main_offset = offset;

                            // Move past the data.
                            offset += len_main;

                            // Extract the new SWVer from the end of the main section.
                            su_SWVer  = (UINT32)(bsm_getByteFromPackedArray(data_ptr, offset-4)) << 24;
                            su_SWVer += (UINT32)(bsm_getByteFromPackedArray(data_ptr, offset-3)) << 16;
                            su_SWVer += (UINT32)(bsm_getByteFromPackedArray(data_ptr, offset-2)) << 8;
                            su_SWVer += (UINT32)(bsm_getByteFromPackedArray(data_ptr, offset-1));

                            // Debug string.
                            bsm_EHLog("HTTP/FWUpdate: Main code received.", 0);
                            break;

                        case NWC_SU_Flash_SECT:
                            // Compute the length.
                            len_flash  = (UINT32)(bsm_getByteFromPackedArray(data_ptr, offset)) << 24;
                            offset++;    //incr ptr

                            len_flash += (UINT32)(bsm_getByteFromPackedArray(data_ptr, offset)) << 16;
                            offset++;    //incr ptr

                            len_flash += (UINT32)(bsm_getByteFromPackedArray(data_ptr, offset)) << 8;
                            offset++;    //incr ptr

                            len_flash += (UINT32)(bsm_getByteFromPackedArray(data_ptr, offset));
                            offset++;    //incr ptr

                            // Save the offset to flash.
                            flash_offset = offset;

                            // Move past the data.
                            offset += len_flash;

                            // Debug string.
                            bsm_EHLog("HTTP/FWUpdate: Flash data received.", 0);
                            break;

                        default: break;
                        } // End of the switch statement.
                    } // End of the for loop.

                    // Update the Flash.
                    if(flash_offset != 0)
                    {
                        // save the previous set of parameters before they are
                        // over-written in case we need to roll back
                        backup_fdn_parameters();
                        // Send a debug string.
                        bsm_EHLog("HTTP/FWUpdate: Updating Flash Parameters Begin.", 0);

                        status = nwm_Update_Flash(data_ptr, flash_offset, len_flash);
                        status = (status ? NWC_OK : NWC_ERR_SWUPDATE_FAILURE);

                        if (status == NWC_OK)
                        {
                            // Flash parameters have been written but have not been
                            // persisted with bsm_EEFlush(). If power is lost during
                            // main code update the parameters will revert.
                            bsm_EHLog("HTTP/FWUpdate: Updating Flash Parameters Complete.", 0);
                        }
                    }

                    // Update the main code
                    currSWVer  = 0; //initialize to zero
                    bsm_EEReadBuf((UINT8*)http_str, coc_SWVer_SIZE, coc_SWVer_ADDR);
                    currSWVer  =  (((UINT32)http_str[0]) & 0xFF) << 24;
                    currSWVer +=  (((UINT32)http_str[1]) & 0xFF) << 16;
                    currSWVer +=  (((UINT32)http_str[2]) & 0xFF) <<  8;
                    currSWVer +=  (((UINT32)http_str[3]) & 0xFF) <<  0;

                    // Decompress if there's a main image and it's compressed

                    if ((main_offset != 0) && (fwImageIsCompressed))
                    {
                        // If a compressed image was sent down,
                        // decompress the code and adjust pointers

                        // We also overwrite the whole download buffer
                        len_main = zlm_UnpackFirmwareImage(data_ptr, main_offset, len_main);

                        if (len_main == 0)
                        {
                            bsm_EHLog("Error in processing compressed image.", 0);
                            status = NWC_ERR_FAILURE;
                        }
                        else
                        {
                            data_ptr     = (UINT16*)returnbuffer;  // One word, 2 bytes
                            offset       = len_main;
                            main_offset  = 0;
                            haveMainCode = true;
                        }

                        // Extract the new SWVer from the end of the main section.
                        su_SWVer  = (UINT32)(bsm_getByteFromPackedArray(data_ptr, offset-4)) << 24;
                        su_SWVer += (UINT32)(bsm_getByteFromPackedArray(data_ptr, offset-3)) << 16;
                        su_SWVer += (UINT32)(bsm_getByteFromPackedArray(data_ptr, offset-2)) << 8;
                        su_SWVer += (UINT32)(bsm_getByteFromPackedArray(data_ptr, offset-1));
                    }

                    #ifdef UPDATE_IF_SAME
                        #warn "Main code updates if new version is the same as current version"
                    currSWVer = su_SWVer - 1;     //Make sure these are no equal so an update
                                                  //that is downloaded but not needed is still
                                                  //written, in production the actual update would
                                                  //not be done if the versions(CRCs) matched
                    #endif
                    // Check if there was a FW flash parameter or decompression error
                    if(status == NWC_OK)
                    {
                        if( ((main_offset != 0) || (haveMainCode)) && (su_SWVer !=  currSWVer))
                        {
                            // Note: CRC check on downloaded file has already passed, check the actual
                            //       calculated CRC against the CRC reported by the server
                            calcSWVer = CalculateCcitt32(data_ptr, main_offset, (len_main - 4));    //minus 4 so calculated crc does not include stored crc in image

                            if(calcSWVer == su_SWVer)
                            {   //The calculated CRC matched the CRC provided by the server
                                // Send a debug string.
                                bsm_EHLog("HTTP/FWUpdate: Calculated CRC of main code matched server provided CRC", 0);
                                // Update the FLASH.
                                // Note: CRC check on downloaded file has already passed
                                // Update the software update codes and SWVer in Flash.
                                http_str[0] = (su_SWVer & 0xFF000000UL) >> 24;
                                http_str[1] = (su_SWVer & 0x00FF0000UL) >> 16;
                                http_str[2] = (su_SWVer & 0x0000FF00UL) >>  8;
                                http_str[3] = (su_SWVer & 0x000000FFUL) >>  0;
                                bsm_EEWriteBuf((UINT8*)http_str, coc_SWVer_SIZE, coc_SWVer_ADDR);

                                // Send a debug string.
                                bsm_EHLog("HTTP/FWUpdate: Updating Main Code Begin.", 0);

                                status = bsm_SUDoUpdate(data_ptr, main_offset, len_main);

                                // Return Type Conversion
                                status = (status == TRUE) ? NWC_OK : NWC_ERR_SWUPDATE_FAILURE;

                                if (status == NWC_OK)
                                {
                                    // Log success
                                    bsm_EHLog("HTTP/FWUpdate: Updating Main Code Complete.", 0);
                                }
                                else
                                {
                                    // Log failure
                                    bsm_EHLog("HTTP/FWUpdate: Updating Main Code Failure.", 0);
                                }
                            }
                            else
                            {    // calculated CRC did not match server provided CRC
                                status = NWC_ERR_FAILURE;
                                bsm_EHLog("HTTP/FWUpdate: Calculated CRC did not match server provided CRC, not updating.", status);
                            }
                        }
                        else     // There is no main code or duplicate main code.
                        {
                            // Check the main code version against current version.
                            if(su_SWVer == currSWVer)
                            {
                                bsm_EHLog("HTTP/FWUpdate: Main code the same, not updating.", status);
                            }
                        }
                    }
                    // Check if flash parameters were recieved
                    if (flash_offset != 0)
                    {
                        // Check if FW flash parameters or main code failed
                        if (status != NWC_OK)
                        {
                            bsm_EHLog("HTTP/FWUpdate: Restore flash parameters.", 0);
                            restore_fdn_parameters();
                        }

                        // Persist the flash parameters regardless.
                        // The preceding logic will have left the programmable flash
                        // parameters in the correct state.
                        bsm_EEFlush();
                        bsm_EHLog("Flash parameters have been persisted.", 0);
                    }
                } //crc check on file
                else // The CRCs did not match.
                {
                    // Log.
                    bsm_EHLog("HTTP/FWUpdate: Download complete-CRC mismatch.", 0);

                    // Set the status
                    status = NWC_ERR_FAILURE;
                }

                // Send the status of the Flash update.
                if( (status != NWC_ERR_SWUPDATE_FAILURE) && (status != NWC_ERR_FAILURE) )
                {
                    nwm_Send_FU_Status(TRUE);
                }
                else
                {
                    nwm_Send_FU_Status(FALSE);
                }
            } //update
        } //POST
        else
        { // Unable to POST the asset data.
            bsm_EHLog("HTTP/FWUpdate: Failure POSTing asset data.", status);

            // Set the correct status. */
            status = NWC_ERR_FAILURE;
        }
    } //GET
    else
    { // Unable to GET the software update page.
        bsm_EHLog("HTTP/FWUpdate: Failure getting update page.", status);

        // Set the correct status.
        status = NWC_ERR_FAILURE;
    }

    return status;
}


/********************************************************************************
FUNCTION: nwm_Send_FU_Status

DESCRIPTION: This function sends the status of the firmware update to the
             server.  It is called after either the main code updates or the
             Flash updates, which ever is last. It sends the 2490 serial
             number, the current firmware version, and success or failure.
             It only attempts to post this information once.

ARGS:
    BOOL fustatus: true  - Firmware image / parameter update successful.
                   false - Firmware image / parameter update unsuccessful.
RETURNS:
    <none>
*********************************************************************************/
void nwm_Send_FU_Status(BOOL fustatus)
{
    UINT16 status;
    char   form_value[3][20];

    nwm_HTTP_Initialization(NWC_NUM_SWSTATUS_FORMS, NWC_HTTP_DEF_STAT_PAGE);

    // Process the first GET.
    if(nwm_Process_HTTP_Authenticate_Get(&status, &http_request, "/Stat"))
    {
        // Append the default status page.
        strcpy(http_request.filename, NWC_HTTP_DEF_STAT_TAR);

        // Setup the POST parameters.
        http_request.method_type              = HTTP_METHOD_POST;
        strcpy(http_request.send_header, NWC_HTTP_CONTENT_TYPE );
        strcat(http_request.send_header, "application/x-www-form-urlencoded\r\n");
        http_request.send_header_size         = strlen(http_request.send_header);
        http_request.numforms                 = NWC_NUM_SWSTATUS_FORMS;
        http_request.disposition_boundary_tag = NULL; //no disposition is required, url-encoded

        // Add the field names.
        strcpy(formArr[0].name, NWC_HTTP_DEF_STAT_SN);
        strcpy(formArr[1].name, NWC_HTTP_DEF_STAT_VER);
        strcpy(formArr[2].name, NWC_HTTP_DEF_STAT_SUC);
        formArr[0].name_length = strlen(formArr[0].name);
        formArr[1].name_length = strlen(formArr[1].name);
        formArr[2].name_length = strlen(formArr[2].name);
        formArr[0].file_name   = NULL;
        formArr[1].file_name   = NULL;
        formArr[2].file_name   = NULL;

        // Add the field types.
        formArr[0].input_type  = HTTP_INPUT_TYPE_TEXTBOX;
        formArr[1].input_type  = HTTP_INPUT_TYPE_TEXTBOX;
        formArr[2].input_type  = HTTP_INPUT_TYPE_TEXTBOX;
        formArr[0].value_type  = HTTP_FORM_VALUE_TYPE_16;
        formArr[1].value_type  = HTTP_FORM_VALUE_TYPE_16;
        formArr[2].value_type  = HTTP_FORM_VALUE_TYPE_16;

        // Determine the 2490 serial number.
        bsm_EEReadBuf((UINT8*)form_value[0], coc_EEPROM_SN_SIZE, coc_EEPROM_SN_ADDR);
        formArr[0].value = (char*)form_value[0];

        // Determine the version number.
        bsm_EEReadBuf((UINT8*)http_str, coc_SWVer_SIZE, coc_SWVer_ADDR);
        sprintf(form_value[1], "%02X%02X%02X%02X", http_str[0], http_str[1], http_str[2], http_str[3]);
        formArr[1].value = (char*)form_value[1];

        // Set the status.
        if(fustatus)
        {
            strcpy(form_value[2], NWC_HTTP_SUCCESS);
        }
        else
        {
            strcpy(form_value[2], NWC_HTTP_FAILURE);
        }
        formArr[2].value  = (char*)form_value[2];

        // Update the lengths.
        formArr[0].length = strlen(form_value[0]);
        formArr[1].length = strlen(form_value[1]);
        formArr[2].length = strlen(form_value[2]);

        // Update the http structure pointers.
        formArr[0].value  = (char*)&form_value[0];
        formArr[1].value  = (char*)&form_value[1];
        formArr[2].value  = (char*)&form_value[2];

        // Log the update status.
        strcpy(http_str, "HTTP/State: ");
        strcat(http_str, formArr[2].value);
        bsm_EHLog(http_str,0);

        // Process the request.
        http_request.return_header_size = 0;
        http_request.return_body_size   = 0;
        http_request.returnbuf_size     = 0;
        GLB_LTMR_WAIT(1000);
        status                          = http_Process_Request(&http_request);

        // Log the status of the request.
        strcpy(http_str, "HTTP/Stat: Server response: ");
        ltoa( status, &http_str[strlen(http_str)]);
        bsm_EHLog(http_str,status);
    }
    else
    {
        strcpy(http_str, "HTTP/Stat: Failed GET of http://");
        strcat(http_str, serverName);
        strcat(http_str, filename);
        bsm_EHLog(http_str, status);
    }
}


/********************************************************************************
FUNCTION: nwm_Extract_DateTime

DESCRIPTION: This function extracts the http server Date/Time string

ARGS:
    char* httpBuffer: response that has the date/time string
    char* dateTime:   string to place extracted date time into

RETURNS:
    <none>
*********************************************************************************/
void nwm_Extract_DateTime(char* httpBuffer, char* dateTime)
{
    char* pDate;

    // Check for Date string.
    pDate = strstr(httpBuffer, NWC_HTTP_DATE);
    if(pDate != 0)
    {
        pDate += sizeof(NWC_HTTP_DATE) -1; //Move pointer to start of dateTime string,
                                           //-1 because sizeof includes null terminating
                                           //character when used with a string
        strncpy(dateTime, pDate, HTTP_DATETIME_LEN);
        dateTime[HTTP_DATETIME_LEN] = 0; //null terminate string
    }
    else
    {
        // DateTime string not found, null the result
        dateTime[0] = 0;
    }
}


/********************************************************************************
FUNCTION: nwm_RetrieveHTTPDateTime

DESCRIPTION: This function copies the HTTP date/time string and the
             corresponding ticks.

PREREQUISITES: Two local variables need to be declared as illustrated below
               followed by the function call. The ticks and the string will
               be copied into the locally declared variables.

               char   string[HTTP_DATETIME_LEN+1]; //+1 for NULL
               UINT32 ticks;
               nwm_RetrieveHTTPdateTime(string, &ticks);

ARGS:
    char*   dateTimestr: function returns a date/time string to this argument
    UINT32* ticks: corresponding system tick time to the sate/time string

RETURNS:
    <none>
*********************************************************************************/
void nwm_RetrieveHTTPDateTime(char *dateTimestr, unsigned long *ticks)
{
    dateTime[HTTP_DATETIME_LEN] = 0; //null terminate string
    strcpy(dateTimestr, dateTime);
    *ticks                      = dateTimeTicks;
}


/********************************************************************************
FUNCTION: nwm_Extract_HTTP_Target

DESCRIPTION: This function extracts the POST target from the HTML we
             receive after we GET the root page at the server. It fills out the
             target form information for the next http_request.

ARGS:
    struct form_struct* form: pointer to form to placed extract post target info
                              into

EXAMPLE:
        --<source page that was downloaded>--
        <HTML>
                <BODY>
                    <FORM   ACTION="2490DataCollection.asp"
                                METHOD="POST"
                                ENCTYPE="multipart/form-data">

                      <INPUT TYPE="File" NAME="File">
                      <INPUT TYPE="Submit" VALUE="Submit">
                    </FORM>

                </BODY>
        </HTML>

        --<information that is extracted from source>--
        http_request.filename = "2490DataCollection.asp";
        form.name = "File"

RETURNS:
    <none>
*********************************************************************************/
void nwm_Extract_HTTP_Target(form_struct* form)
{
    char *pStart;
    char *pEnd;
    int  offset;

    // Find the 'ACTION' string in the html .
    pStart = strstr( http_request.return_body, NWC_HTML_ACTION);

    // Find target in html
    if(pStart != 0) //if action tag was found
    {
        // Move past the ACTION string.
        pStart += strlen(NWC_HTML_ACTION);

        // Increment past the first double quote.
        pStart++;

        // Find the 2nd double quote.
        pEnd = strstr(pStart, NWC_HTTP_QUOTE);

        if(pEnd != 0)
        {
            offset = pEnd - pStart;

            // Find base path in http_request
            pEnd   = strrchr(http_request.filename, NWC_HTTP_DIRECTORY_SLASH);
            if(pEnd == 0)
            {   // Vaild path doesn't exist in request, create root path as minimum
                http_request.filename[0] = NWC_HTTP_DIRECTORY_SLASH;
                http_request.filename[1] = 0;
                pEnd                     = &http_request.filename[1];
            }
            else
            {   // point to character after directory slash, null terminate string
                pEnd++;
                *pEnd = 0;
            }

            // Cat the target.
            strncat(pEnd, pStart, offset);

            // Null terminate the string.
            pEnd += offset;
            *pEnd = 0;
        }
    }

    // Find the 'INPUT' string in the html.
    pStart = strstr(http_request.return_body, NWC_HTML_INPUT);

    if(pStart != 0)
    {
        // Find the next instance of NAME.
        pStart  = strstr(pStart,NWC_HTML_NAME);

        // Move past the NAME string.
        pStart += strlen(NWC_HTML_NAME);

        // Increment past the first double quote.
        pStart++;

        // Find the 2nd double quote.
        pEnd = strstr(pStart, NWC_HTTP_QUOTE);
        if(pEnd != 0)
        {
            offset = pEnd - pStart;

            // Copy the filename.
            strncpy(form->name, pStart, offset);
            form->name[offset] = 0;
            //strcat(form->name, NWC_HTTP_HEADER_LINE_END);
            form->name_length  = strlen(form->name);
        }
    }
}


/********************************************************************************
FUNCTION: nwm_Update_Flash

DESCRIPTION: This function will update the Flash based on information sent from
             the server.

FORMAT:  The software searches through the file looking for the tags that are
         listed below.  It then steps through the file recording the value.  It
         stops when it encounters a carriage return (0x0d). Non-ASCII characters
         can be used including nulls.  To 'erase' a value in the Flash, a 0xff
         can be used as the value such as "Phone1:\xff\x0d".  A special case
         exists for the phone dial prefix.  An 'N' or 'n' can be used in place
         of the null: "N789" will translate into a null, 7, 8, 9 for the switch
         positions.

ARGS:
    char* data: base pointer to buffer containg update data
    UINT32 offset: byte offset into the buffer for the buffer
    UINT32 length: length of update buffer

RETURNS:
    BOOL status: TRUE if successful, false otherwise
*********************************************************************************/
BOOL nwm_Update_Flash(UINT16 *basePtr, UINT32 offset, UINT32 length)
{
    UINT16 strlength;
    UINT16 ii;
    UINT32 jj;
    char   * temp;
    BOOL   status=FALSE;
    char   tmpStr[200];

    // Check the data for each of the strings.
    for(ii=0; ii < NWC_EE_NUM_CONST; ii++)
    {
        // Traverse the entire buffer.
        for( jj = 0; jj < length; jj++)
        {
            bsm_unpackByteArray(http_str, basePtr, offset+jj, strlen(tag[ii].name));
            if( memcmp(tag[ii].name, http_str, strlen(tag[ii].name)) == 0) // A tag was found.
            {
                // Move past the tag.
                jj  += strlen(tag[ii].name);

                // Extract the parameter.
                temp = extract_parameter(basePtr, offset + jj);

                // Determine the length.
                strlength = strlen(temp);

                // Write the response to the Flash and track the status.
                // We add 1 to the string length so the terminating null is included.
                status = bsm_EEWriteBuf((UINT8*)temp, strlength + 1, tag[ii].address);

                // Log the received parameter tag and its value.
                sprintf(tmpStr, "Rcvd-%s%s", tag[ii].name, temp);
                bsm_EHLog(tmpStr, 0);

                // Break out of the inner loop.
                break;
            }
        }
    }
    return status;
}

/********************************************************************************
FUNCTION: extract_parameter

DESCRIPTION: This function extracts a parameter from after an Flash tag.
             Used in software update

ARGS:
    char*  data: pointer to buffer containing update tag
    UINT32 offset: byte offset into the buffer containing update tag

RETURNS:
    char*: pointer to extracted parameter
*********************************************************************************/
char* extract_parameter(UINT16 *base_ptr, UINT32 offset)
{
    int    index = 0;
    UINT16 data;

    do
    {
        data              = bsm_getByteFromPackedArray(base_ptr, offset++);
        http_str[index++] = data;
    }
    while(data != 0x0D); // Tags are terminated by a <CR>

    // Null terminate the string.
    http_str[index-1] = 0x00;

    return http_str;
}




/********************************************************************************
FUNCTION: nwm_HTTP_Setup

DESCRIPTION: This function esets up defaults for the http_request

ARGS:
    int numForms: The number for forms to have pointers to (This does not set the
                  numForms field.) This default return data type is unpacked.

RETURNS:
    <none>
*********************************************************************************/
void nwm_HTTP_Setup(int numForms)
{
    int i;

    http_request.method_type  = HTTP_METHOD_GET;
    http_request.http_version = HTTP_V1_0;
    http_request.servername   = serverName;
    http_request.filename     = filename;
    http_request.portnumber   = NWC_HTML_PORTNUM;
    for(i=0; i < numForms; i++)
    {    //fill form array
        http_request.forms[i]            = &formArr[i];        //fill array of pointers to the forms
        http_request.forms[i]->name      = formNameArr[i]; //associate form name pointer with form name string array
        http_request.forms[i]->file_name = formFileNameArr[i];         //associate form file_name pointer with form file_name string array
    }
    http_request.numforms                 = (0);              //no forms by default
    http_request.disposition_boundary_tag = "----------10000000";      // NULL if boundary disposition is not used,
                                                                       //   of NULL the input type of file is not valid and is ignored
    http_request.send_header              = sendHeader;
    strcpy(http_request.send_header, NWC_HTTP_DEFAULT_SEND_HEADER_1);
    http_request.send_header_size         = strlen(http_request.send_header);
    http_request.user_name                = user_name;
    http_request.user_password            = user_password;
    http_request.returnbuf                = returnbuffer;
    http_request.returnbuf_max_size       = NWC_HTML_RECEIVE_BUFFER_SIZE * (2L); //multipy to convert to number of bytes
    http_request.return_type              = HTTP_FORM_VALUE_TYPE_16;
    http_request.returnbuf_size           = 0;
    http_request.return_header_size       = 0;
    http_request.return_body_size         = 0;
    http_request.timeout                  = NWC_MAX_NETWORK_TIMEOUT;
}



/********************************************************************************
FUNCTION: print_http_request

DESCRIPTION: This prints out the entire http_request structure

ARGS:
    none

RETURNS:
    <none>
*********************************************************************************/
void print_http_request()
{
    int i;

    strcpy(http_str, "\r\n*** http_request METHOD TYPE: ");
    ltoa( http_request.method_type, &http_str[strlen(http_str)]);
    strcat(http_str, " ***");
    bsm_SDPrint(http_str);

    strcpy(http_str, "\r\n*** http_request HTTP VERSION: ");
    ltoa( http_request.http_version, &http_str[strlen(http_str)]);
    strcat(http_str, " ***");
    bsm_SDPrint(http_str);

    strcpy(http_str, "\r\n*** http_request SERVER NAME: ");
    strcat(http_str, http_request.servername);
    strcat(http_str, " ***");
    bsm_SDPrint(http_str);

    strcpy(http_str, "\r\n*** http_request FILE NAME: ");
    strcat(http_str, http_request.filename);
    strcat(http_str, " ***");
    bsm_SDPrint(http_str);

    strcpy(http_str, "\r\n*** http_request PORT NUMBER: ");
    ltoa( http_request.portnumber, &http_str[strlen(http_str)]);
    strcat(http_str, " ***");
    bsm_SDPrint(http_str);

    strcpy(http_str, "\r\n*** http_request NUMBER OF FORMS: ");
    ltoa( http_request.numforms, &http_str[strlen(http_str)]);
    strcat(http_str, " ***");
    bsm_SDPrint(http_str);

    for(i=0; i<http_request.numforms; i++)
    {           // form name
        strcpy(http_str, "\r\n*** form[");
        ltoa( i, &http_str[strlen(http_str)]);
        strcat(http_str, "] NAME: ");
        strncpy(&http_str[strlen(http_str)], http_request.forms[i]->name, http_request.forms[i]->name_length + 1);
        strcat(http_str, " ***");
        bsm_SDPrint(http_str);

        //form input type
        strcpy(http_str, "\r\n*** form[");
        ltoa( i, &http_str[strlen(http_str)]);
        strcat(http_str, "] INPUT TYPE: ");
        ltoa( http_request.forms[i]->input_type, &http_str[strlen(http_str)]);
        strcat(http_str, " ***");
        bsm_SDPrint(http_str);

        //value type
        strcpy(http_str, "\r\n*** form[");
        ltoa( i, &http_str[strlen(http_str)]);
        strcat(http_str, "] VALUE TYPE: ");
        ltoa( http_request.forms[i]->value_type, &http_str[strlen(http_str)]);
        strcat(http_str, " ***");
        bsm_SDPrint(http_str);

        //value type
        strcpy(http_str, "\r\n*** form[");
        ltoa( i, &http_str[strlen(http_str)]);
        strcat(http_str, "] LENGTH: ");
        ltoa( http_request.forms[i]->length, &http_str[strlen(http_str)]);
        strcat(http_str, " ***");
        bsm_SDPrint(http_str);

        //form value
        strcpy(http_str, "\r\n*** form[");
        ltoa( i, &http_str[strlen(http_str)]);
        strcat(http_str, "] VALUE: ");
        bsm_SDPrint(http_str);
        if(http_request.forms[i]->value == NULL)
        {
            bsm_SDPrint("-NULL Pointer-");
        }
        else if(http_request.forms[i]->length <= 0)
        {
            strcpy(http_str, " - form value length: ");
            ltoa( http_request.forms[i]->length, &http_str[strlen(http_str)]);
            strcat(http_str, " -");
            bsm_SDPrint(http_str);
        }
        else
        {
            bsm_SDWrite_Unlimited(http_request.forms[i]->value, http_request.forms[i]->length );
        }

        //form file name
        strcpy(http_str, "\r\n*** form[");
        ltoa( i, &http_str[strlen(http_str)]);
        strcat(http_str, "} FILENAME: ");
        if(http_request.forms[i]->file_name== NULL)
        {
            bsm_SDPrint("-NULL Pointer-");
        }
        else
        {
            strcpy(&http_str[strlen(http_str)], http_request.forms[i]->file_name);
        }
        strcat(http_str, " ***");
        bsm_SDPrint(http_str);
    }

    bsm_SDPrint("\r\n***  http_request SEND HEADER: ***");
    if(http_request.send_header == NULL)
    {
        bsm_SDPrint("-NULL Pointer-");
    }
    else if(http_request.send_header_size <= 0)
    {
        strcpy(http_str, " - send header size: ");
        ltoa( http_request.send_header_size, &http_str[strlen(http_str)]);
        strcat(http_str, " -");
        bsm_SDPrint(http_str);
    }
    else
    {
        bsm_SDWrite_Unlimited(http_request.send_header, http_request.send_header_size );
    }

    strcpy(http_str, "\r\n*** http_request USER NAME: ");
    if(http_request.user_name != NULL)
    {
        strcat(http_str, http_request.user_name);
    }
    else
    {
        strcat(http_str,"-NULL Pointer-");
    }
    strcat(http_str, " ***");
    bsm_SDPrint(http_str);

    strcpy(http_str, "\r\n*** http_request USER PASSWORD: ");
    if(http_request.user_password != NULL)
    {
        strcat(http_str, http_request.user_password);
    }
    else
    {
        strcat(http_str,"-NULL Pointer-");
    }
    strcat(http_str, " ***");
    bsm_SDPrint(http_str);

    bsm_SDPrint("\r\n***  http_request RETURN HEADER: ***");
    if(http_request.return_header == NULL)
    {
        bsm_SDPrint("-NULL Pointer-");
    }
    else if(http_request.return_header_size <= 0)
    {
        strcpy(http_str, " - return header size: ");
        ltoa( http_request.return_header_size, &http_str[strlen(http_str)]);
        strcat(http_str, " -");
        bsm_SDPrint(http_str);
    }
    else
    {
        bsm_SDWrite_Unlimited(http_request.return_header, http_request.return_header_size);
    }


    bsm_SDPrint("\r\n***  http_request RETURN BODY: ***");
    if(http_request.return_body == NULL)
    {
        bsm_SDPrint("-NULL Pointer-");
    }
    else if(http_request.return_body_size <= 0)
    {
        strcpy(http_str, " - return body size: ");
        ltoa( http_request.return_body_size, &http_str[strlen(http_str)]);
        strcat(http_str, " -");
        bsm_SDPrint(http_str);
    }
    else
    {
        bsm_SDWrite_Unlimited(http_request.return_body, http_request.return_body_size);
    }

    bsm_SDPrint("\r\n***  http_request RETURN BUFFER: ***");
    if(http_request.returnbuf == NULL)
    {
        bsm_SDPrint("-NULL Pointer-");
    }
    else if(http_request.returnbuf_size <= 0)
    {
        strcpy(http_str, " - return buffer size: ");
        ltoa( http_request.returnbuf_size, &http_str[strlen(http_str)]);
        strcat(http_str, " -");
        bsm_SDPrint(http_str);
    }
    else
    {
        bsm_SDWrite_Unlimited(http_request.returnbuf, http_request.returnbuf_size);
    }
}




/********************************************************************************

         Function:   nwm_Process_HTTP_Authenticate_Get

      Description:   This is a high level function that calls
                     nwm_Process_HTTP_Request for the GET method only.  If the
                     client has not be authenticated with the server this
                     function will execute a digest challenge and expect the
                     server to return HTTP_UNAUTHORIZED.  The client will then
                     execute a digest authentication with the server.

          Returns:   true  - successful digest authentication
                     false - failed digest authentiation

*********************************************************************************/
bool nwm_Process_HTTP_Authenticate_Get(UINT16 *status, http_request_data *http_request, char *idstr)
{
    int  ret_val = true;
    char str[128];
    char Buffer[100];

    /* Set the method. */
    http_request->method_type = HTTP_METHOD_GET;

    /* Process challenge/authentication GET. */

    *status = http_Process_Request(http_request);
    GLB_LTMR_WAIT(5000);

    sprintf(Buffer, "HTTP status %d 1st Request", *status);
    bsm_SDPrint(Buffer);

    if ((*status!= HTTP_STATUS_OK) && (*status == HTTP_STATUS_UNAUTH))
    {

        /* Log */
        sprintf(str, "HTTP%s: Challenge GET success of %s%s.", idstr, http_request->servername, http_request->filename);
        bsm_EHLog(str, *status);

        //Handles HTTP Unauthorized return message
        *status=nwm_Process_HTTP_UNAUTHORIZED(http_request);


        /* Process the authentication GET */
        *status = http_Process_Request(http_request);
        GLB_LTMR_WAIT(5000);

        sprintf(Buffer, "HTTP status %d 2nd Request", *status);
        bsm_SDPrint(Buffer);

        /* HTTP_Process_HTTP_UNAUTHORIZED() sets the isAuthenticated flag */
        if ((*status == HTTP_STATUS_OK))
        {

            /* Log */
            sprintf(str, "HTTP%s: Authentication GET success of %s%s.", idstr, http_request->servername, http_request->filename);
            bsm_EHLog(str, *status);

        }
        else
        {
            /* Log the problem. */
            if(*status == HTTP_STATUS_UNAUTH)
            {
                sprintf(str, "HTTP%s: Authentication GET failure of %s%s, HTTP Status %d.", idstr, http_request->servername, http_request->filename, *status );
                bsm_EHLog(str, *status);

                //Handles HTTP Unauthorized return message.
                *status=nwm_Process_HTTP_UNAUTHORIZED(http_request);


            }
            else
            {
                sprintf(str, "HTTP%s: Authentication GET failure.", idstr);
                bsm_EHLog(str, *status);

            }

            ret_val = false;
        }
    }
    else if ((*status == HTTP_STATUS_OK))
    {
        /* Log */
        sprintf(str, "HTTP%s: Authentication GET success of %s%s.", idstr, http_request->servername, http_request->filename);
        bsm_EHLog(str, *status);
    }
    else
    {
        /* Log the problem. */
        sprintf(str, "HTTP%s: Initial GET failed - not an authentication problem.", idstr);
        bsm_EHLog(str, *status);

        ret_val = false;
    }

    return ret_val;
}



/********************************************************************************
FUNCTION: nwm_Process_HTTP_UNAUTHORIZED

DESCRIPTION:
                Handles the HTTP Unauthorized return Message.  The routine
        parses the Header and looks for the authenticate Header.  It
            then searches for the Digest realm message.  If it is not the
            Digest Realm then it is an unsupported  method. If it is Digest
                auth then the dialog Box for the username and password will flash
            up.  After the User name and Password have been inputed, they
            will be encoded per RFC 2617.  Then the routine will exit.

ARGS:
    none

RETURNS:
    <none>
*********************************************************************************/

UINT16 nwm_Process_HTTP_UNAUTHORIZED(http_request_data *http_rec)
{

    char  *temp_buffer     =0;    /*  Use for temporary pointer to buffer */
    char  *end_buffer_value=0;    /*  End Value address of the buffer */
    char  *next_buffer     =0;
    INT16 offset           =0;
    char  *buffer;
    INT16 ret_val          = HTTP_STATUS_OK;

    buffer           = http_rec->return_header;

    /*  Now we should check for the WWW-Authenticate tag from the server's response */
    temp_buffer      = buffer;
    end_buffer_value = &temp_buffer[strlen(buffer)];

    /*  Increment past the first CRLF command */
    temp_buffer++;
    next_buffer = temp_buffer;

    /*  Find the Authenticate Header */
    temp_buffer =nwm_HTTP_find_header(NWC_HTTP_AUTHENTICATE,next_buffer,end_buffer_value, HTTP_HDR_CASE_INSENSITIVE_CMP);
    if (temp_buffer)
    {
        /*  Move Pass the WWW-Authenticate: Entity Header field */
        temp_buffer += strlen(NWC_HTTP_AUTHENTICATE);
        next_buffer  = temp_buffer;

        /* Check for Digest Entity Header field    */
        temp_buffer  =nwm_HTTP_find_header(NWC_HTTP_DIGEST, next_buffer, end_buffer_value, HTTP_HDR_CASE_INSENSITIVE_CMP);
        if(temp_buffer)
        {
            /* Move pass the Digest " */
            temp_buffer+=strlen(NWC_HTTP_DIGEST)+1;


            //  Parse and save challenge parameters from server
            if (HTTP_DigestChallenge(temp_buffer, http_rec) != 0)
            {
                bsm_EHLog("Fail to parse and save challenge parameters from server",0);
                ret_val = HTTP_ERROR_UNAUTHORIZED;
            }

        }
        else  /* Digest not found */
        {
            /* error */
            bsm_EHLog("Fail to find digest header.",0);
            ret_val = HTTP_ERROR_UNAUTHORIZED;
        }
    }
    else  /* WWW-Authenticate not found */
    {
        /* error Should not get here */
        bsm_EHLog("Fail to find Auth header.",0);
        ret_val = HTTP_ERROR_UNAUTHORIZED;
    }

    return(ret_val);
}



/*************************************************************************
*
* FUNCTION
*
*     HTTP_find_header
*
* DESCRIPTION
*
*     Routine to find a certain sub string within in a string.  If
*     successful the pointer to the point in the string is passed back.
*     If in failure then a Null pointer is returned.
*
* INPUTS
*
*       header              - pointer to HTTP header string
*       buffer              - pointer to the first byte in the buffer
*       end_buffer          - pointer to the last byter in the buffer
*       case_sensitivity    - case sensitivity flag
*
* OUTPUTS
*
*     Returns:
*           The pointer to the point in the string if successful.
*           NULL - otherwise
*
*************************************************************************/
char *nwm_HTTP_find_header(char *header, char *buffer, char *end_buffer, INT16 case_sensitivity)
{

    INT16 length;
    INT16 cmp_ret;
    char  *ret_val = NULL;

    length = strlen(header);


    while( *buffer && (buffer < end_buffer)  )
    {

        if(case_sensitivity == HTTP_HDR_CASE_SENSITIVE_CMP)
        {
            /* case sensitive comparison */
            cmp_ret = strncmp(header,buffer,length);
        }
        else
        {
            /* case insensitive comparison */
            cmp_ret = Str_NI_Cmp(header,buffer,length);
        }


        if( cmp_ret == 0)
        {
            /* header found */
            ret_val = buffer;
            break;
        }
        buffer++;
    }

    return(ret_val);
}



/*************************************************************************
*
* FUNCTION
*
*     nwm_HTTP_Initialization(const int numberForms, const char *httpPage)
*
* DESCRIPTION
*
*     Routine to initialize http for all HTTP request functions.
*
* INPUTS
*
*       numberForms         - const int numForms: The number for forms to have pointers to.
*       httpPage		    - const char * http page name
*
* OUTPUTS
*
* Returns: None
*
*
*************************************************************************/
void nwm_HTTP_Initialization(const int numberForms, const char *httpPage)
{
    // Initialize
    memset(sendHeader, 0, sizeof(sendHeader));
    memset(user_name, 0,  sizeof(user_name));
    memset(user_password, 0, sizeof(user_password));

    // Setup http_request defaults
    nwm_HTTP_Setup(numberForms);


    /* Set up pointer to digest authentication data */
    http_request.digest                        = &digest;
    http_request.digest->isReadyToAuthenticate = FALSE;

    // Set the method.
    http_request.method_type                   = HTTP_METHOD_GET;


    // Get the server name
    strcpy(serverName, nwv_HttpISP_Param.http_ServerName);

    // Set the target page
    strcpy(filename, httpPage);

    // Log
    strcpy(http_str, "HTTP: Sending initial GET of http://");
    strcat(http_str, serverName);
    strcat(http_str, filename);
    bsm_EHLog(http_str, 0);


    // Get the user_name and password.
    strcpy(http_request.user_name, nwv_HttpISP_Param.http_UserName);

    strcpy(http_request.user_password, nwv_HttpISP_Param.http_UserPassword);

}

/*************************************************************************
*
* FUNCTION
*
*     backup_fdn_parameters(void)
*
* DESCRIPTION
*
*     This function saves a copy of the 11 programmable flash
*     parameters to a global buffer.
*
* INPUTS
*
*     None
*
* OUTPUTS
*
*     The fdn_parameters[] array is loaded with the current values
*     in the FW update flash parameters.
*
*************************************************************************/
void backup_fdn_parameters(void)
{
    UINT16 p_idx=0;     // fdn parameter string index
    UINT16 t_idx=0;     // tag index

    bsm_SDPrint("Backup programmable flash parameters.");
    for (t_idx=0; t_idx<NWC_EE_NUM_CONST; ++t_idx)
    {
        bsm_EEReadBuf(&fdn_parameters[p_idx], tag[t_idx].length, tag[t_idx].address);
        p_idx += tag[t_idx].length;
    }
}

/*************************************************************************
*
* FUNCTION
*
*     restore_fdn_parameters(void)
*
* DESCRIPTION
*
*     This function restores the 11 programmable flash parameters to
*     the values previously backed up using the backup_fdn_parameters()
*     function.
*
* INPUTS
*
*     None
*
* OUTPUTS
*
*     The FW update flash parameters are loaded with the backup
*     values in the fdn_parameters[] array.
*
*************************************************************************/
void restore_fdn_parameters(void)
{
    UINT16 p_idx=0;     // fdn parameter string index
    UINT16 t_idx=0;     // tag index

    bsm_SDPrint("Restore programmable flash parameters.");
    for (t_idx=0; t_idx<NWC_EE_NUM_CONST; ++t_idx)
    {
        bsm_EEWriteBuf(&fdn_parameters[p_idx], tag[t_idx].length, tag[t_idx].address);
        p_idx += tag[t_idx].length;
    }
}

#ifdef TEST_NET_HTTP
//***********************************************
//	Unit Test 1
//***********************************************
void UTest1_HTTP_Initialization(void)
{
    // Test for nwm_Send_Data() http initialization
    nwm_HTTP_Initialization(NWC_NUM_SEND_FORMS, nwv_HttpISP_Param.http_FileName);

    //Test for nwm_HTTP_SW_Update() http initialization
    nwm_HTTP_Initialization(NWC_NUM_SWUPDATE_FORMS, NWC_HTTP_DEF_FWUPDATE_PAGE);

    //Test for nwm_Send_SU_Status() http initialization
    nwm_HTTP_Initialization(NWC_NUM_SWSTATUS_FORMS, NWC_HTTP_DEF_STAT_PAGE);

    bsm_SDPrint("Done with http initialization unit test");
}
#endif
