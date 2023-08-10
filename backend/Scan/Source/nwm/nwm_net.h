/************************************************************************
*
* MODULE: nwm_net.h
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
* DESCRIPTION:  This file contains all the header information for the
                Vocal network code.  This includes constant string
                definitions for the modem, modem and network status codes
                to supplement the Vocal status codes, an enumeration for
                ISP response strings and the public function prototypes.
*************************************************************************/
#ifndef __nwm_NETWORK_H
#define __nwm_NETWORK_H

#include "../global.h"
#include "../com_eepromapp.h"
#include "bsm_SwitchInput.h"
#include "cx077.h"

//Macro to create event logs with proper line number and file names
#define nwm_Process_Modem_Error(Code) (nwm_Process_Modem_Error_Full( ((UINT16)Code), __LINE__, __FILE__))

#define NUM_LOGIN_STR 10

//modem response strings
#define NWC_STR_OK           "OK"
#define NWC_STR_CONNECT      "CONNECT"
#define NWC_STR_BUSY         "BUSY"
#define NWC_STR_NO_DIALTONE  "NO DIALTONE"
#define NWC_STR_NO_ANSWER    "NO ANSWER"
#define NWC_STR_NO_CONNECT   "NO CARRIER"
#define NWC_STR_LINE_IN_USE  "LINE IN USE"
#define NWC_DEF_ISPAUTH_TYPE bsc_CHAP          //The length should be less than ISP_AUTH_METHOD_MAX_SIZE.
//The ISP host name length should be less than ISP_HOST_NAME_MAX_SIZE
#ifdef _DEBUG
        #warn "Non-production ISP host name is in use"
        #define NWC_DEF_HOSTNAME "idctest.medtronic.com"    //This is a test router
#else
        #define NWC_DEF_HOSTNAME "idc.medtronic.com"    //This is production router
#endif

#define NWC_DEF_VERIZON_PHONE "18884137028"       //Default Verizon phone number. The length should be less than ISP_PHONE1_MAX_SIZE.
#define NWC_DEF_ATT_PHONE     "18884137028"      //Default AT&T phone number. Set to Verizon number before AT&T is availble
//The length should be less than ISP_PHONE1_MAX_SIZE.
#define NWC_DEF_PHONE_PREFIX                 "N789" //Dial prefix. The length should be less than MDM_DIAL_PREFIX_MAX_SIZE.
#define NWC_DEFAULT_COUNTRY_CODE             "22" //This is ASCII The length should be less than MDM_COUNTRY_CODE_MAX_SIZE.
#define NWC_DIAL_ATTEMPTS                    (12)
#define NWC_MAX_INCOMP_EQUIP_SINGLE          (2) //Max incompatible equipment dial retry allowed for single carrier
#define NWC_MAX_INCOMP_EQUIP_SINGLE_OVERRIDE (4)  //Max incompatible equipment dial retry allowed for single carrier if Prefix override
#define NWC_MAX_INCOMP_EQUIP_DUAL            (4) //Max incompatible equipment dial retry allowed for dual carrier
#define NWC_MIN_CONNECT_SPEED                (9600)
#define NWM_MINUTE_DELAY(x) ((x)*60L*(LTMR_TICKS_PER_SECOND))
#define NWM_UUNET_EXPECTED_STRINGS (12)
#define NWM_GET_LOGIN_TIMEOUT      (4)  //the number of seconds to wait for a login string
#define NWM_MDM_SHUTDOWN_WAIT      (2)  //the number of seconds to wait for modem to shutdown
#define NWM_STATIC_DNS_COMMAND     "ip domain add "

/* Modem strings. */
#define MDM_BUFFER_LENGTH           (20)  //length of modem response buffers
#define MDM_TONE_DIAL_PREFIX        "ATX3DT"  //Use the X3 dialing mode, instead of the default X4 mode. Dial tone
#define MDM_PULSE_DIAL_PREFIX       "ATX3DP"  //detection is disabled and busy tone detection is enabled in X3.
#define MDM_RESET_STR               "ATZ\r"  // Resets modem to default state
#define MDM_PLUSPLUSPLUS_STR        "+++"       // Escape sequence to switch modem from data mode to command mode
#define MDM_LIU_STR                 "AT-STE=1\r"
#define MDM_NC_QUERY_STR            "ATS86?\r"
#define MDM_NULL_DIAL_STR           "ATDTW;\r"
#define MDM_HANGUP_STR              "+++ATH0\r"
#define MDM_SPEAKER_ON_STR          "ATM1\r"
#define MDM_SPEAKER_VOLUME          "ATL3\r"
#define MDM_CONNECT_RESTRICT        "AT+ms=11,1,24000,24000\r" //TBD - remove any uses of this in production code
#define MDM_COUNTRY_SELECT          "AT*NC"
#define MDM_SPEAKER_OFF_STR         "ATM0\r"
#define MDM_AT_STR                  "AT\r"
#define MDM_GO_OFFHOOK_STR          "ATH1\r"
#define MDM_GO_ONHOOK_STR           "ATH0\r"     // On hook command, phone is hung up
#define MDM_1_SEC_GUARD_TIME_STR    "ATS12=50\r"        // Set guard time before and after the "+++" escape sequence
#define MDM_ENABLE_ERROR_CORRECTION "AT\\n4\r"
#define MDM_NEGOTIATE_CR_STR        ";\r"
#define MDM_CR_STR                  "\r"
#define MDM_STRING_8                (8)
#define MDM_STRING_16               (16)
#define MDM_STRING_32               (32)
#define MDM_STRING_64               (64)
#define MDM_STRING_128              (128)
#define MDM_STRING_256              (256)

#define NWC_NUM_DIALTYPE (2)

/* Networm Command Line Commands */
// Note: the '/' brings up to the 'root' command level
#define NET_CMD_CHANGE_MSS         "/ ip tcp mss 1400\r" //to change the MaxSegmentSize
#define NET_CMD_CHANGE_WINDOW_SIZE "/ ip tcp window 5600\r" //to change the Window size
#define NET_CMD_GET_IP_ADDRESS     "/ ip address\r" // Command to retrieve the IP-Address

// GLOBAL CONSTANTS
// Constants are one byte greater than the size allocated in EEPROM
// The extra byte is reserved for null termination, since it cannot
// be assumed that EEPROM values read from the monitor always null-terminated.

#define NWM_HTTP_SERVER_NAME_MAX_SIZE   ( coc_HTTPServerName_SIZE + 1 )
#define NWM_HTTP_FILE_NAME_MAX_SIZE     ( coc_HTTPHomePage_SIZE + 1 )
#define NWM_HTTP_USER_NAME_MAX_SIZE     ( coc_HTTPLoginID_SIZE + 1 )
#define NWM_HTTP_USER_PASSWORD_MAX_SIZE ( coc_HTTPPassword_SIZE + 1 )
#define MDM_COUNTRY_CODE_MAX_SIZE       ( coc_MDMCountryCode_SIZE + 1 )
#define ISP_AUTH_METHOD_MAX_SIZE        ( coc_ISPAuthMethod_SIZE + 1 )
#define ISP_PHONE1_MAX_SIZE             ( coc_ISPPhone1_SIZE + 1 )
#define ISP_PHONE2_MAX_SIZE             ( coc_ISPPhone2_SIZE + 1 )
#define ISP_PHONE3_MAX_SIZE             ( coc_ISPPhone3_SIZE + 1 )
#define ISP_PHONE4_MAX_SIZE             ( coc_ISPPhone4_SIZE + 1 )
#define ISP_HOST_NAME_MAX_SIZE          ( coc_ISPHostName_SIZE + 1 )
#define ISP_USER_NAME_MAX_SIZE          ( coc_IPLoginID_SIZE + 1 )
#define ISP_PASSWORD_MAX_SIZE           ( coc_IPPassword_SIZE + 1 )
#define NWM_STATIC_DNS_MAX_SIZE         ( coc_StaticDNS_SIZE + 1 )
#define MDM_DIAL_PREFIX_MAX_SIZE        ( coc_DIALPREFIX_SIZE + 1 )
#define ISP_LASTWORKPHONEFLAG_MAX_SIZE  ( coc_ISPLastWorkPhoneFlag_SIZE + 1 )
#define ISP_LASTWORKPREFIX_MAX_SIZE     ( coc_ISPLastWorkPrefix_SIZE + 1 )
#define NWM_LASTUSEDPREFIX_MAX_SIZE     ( coc_LastUsedPrefix_SIZE + 1 )

/*Status Codes*/
enum {
    NWC_OK,
    NWC_CONNECT,
    NWC_ERR_INCOMP_EQUIP,
    NWC_ERR_FAILURE,
    NWC_ERR_INVALID_MODE,
    NWC_ERR_NO_DIALTONE,
    NWC_ERR_NO_ANSWER,
    NWC_ERR_LINE_IN_USE,
    NWC_ERR_BUSY,
    NWC_ERR_LINE_PROBLEM,
    NWC_ERR_INVALID_LINK,
    NWC_ERR_INVALID_PW,
    NWC_ERR_INVALID_UIC,
    NWC_ERR_INVALID_LOGIN,
    NWC_ERR_CONNECT_SPEED,
    NWC_ERR_HTTP_POST_FAILURE,
    NWC_ERR_HTTP_AUTH_FAILURE,
    NWC_ERR_HTTP_GET_FAILURE,
    NWC_ERR_NO_RESPONSE,
    NWC_ERR_SWUPDATE_FAILURE,
    NWC_ERR_UNKNOWN
};


// Global Variables
// Structure contains all modem and network parameters
typedef struct
{
    BYTE http_ServerName[   NWM_HTTP_SERVER_NAME_MAX_SIZE];
    BYTE http_FileName[     NWM_HTTP_FILE_NAME_MAX_SIZE];
    BYTE http_UserName[    NWM_HTTP_USER_NAME_MAX_SIZE];
    BYTE http_UserPassword[     NWM_HTTP_USER_PASSWORD_MAX_SIZE];
    BYTE mdm_CountryCode[       MDM_COUNTRY_CODE_MAX_SIZE];
    BYTE ISP_AuthMethod[ISP_AUTH_METHOD_MAX_SIZE];
    BYTE ISP_Phone1[    ISP_PHONE1_MAX_SIZE];
    BYTE ISP_Phone2[    ISP_PHONE2_MAX_SIZE];
    BYTE ISP_Phone3[    ISP_PHONE3_MAX_SIZE];
    BYTE ISP_Phone4[    ISP_PHONE4_MAX_SIZE];
    BYTE ISP_LastWorkPhoneFlag[ ISP_LASTWORKPHONEFLAG_MAX_SIZE];
    BYTE ISP_LastWorkPrefix[ ISP_LASTWORKPREFIX_MAX_SIZE];
    BYTE ISP_HostName[  ISP_HOST_NAME_MAX_SIZE];
    BYTE IP_UserName[   ISP_USER_NAME_MAX_SIZE];
    BYTE IP_Password[ ISP_PASSWORD_MAX_SIZE];
    BYTE nwm_StaticDNS[ NWM_STATIC_DNS_MAX_SIZE];
    BYTE mdm_DialPrefix[ MDM_DIAL_PREFIX_MAX_SIZE];

} nwst_HttpISP_Param;

extern nwst_HttpISP_Param nwv_HttpISP_Param;


/*      Declaration prototypes         */
BOOL   nwm_Send_Data (void);
UINT16 nwm_Line_Problem_Action(UINT16 current_dial_attempt);
UINT16 nwm_Dial_Sequence(int dial_attempts);
UINT16 nwm_Dial_and_Connect(BYTE* phoneNumber);
UINT16 nwm_Get_Modem_Response (char* response);
void  nwm_Process_Modem_Error_Full (int Code, int LineNum, char * FileName);
void  nwm_LogModemInitError(UINT16 status);
void nwm_ExtractIPAddress(void);
void nwm_GetModemNetwork_Params(void);
bool nwm_IsPhoneLineConnected(void);


#endif

