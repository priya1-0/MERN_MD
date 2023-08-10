/************************************************************************
*
* MODULE: nwm_http.h
*
* OWNER:
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION:  This file contains the public prototype definitions for the
*               network HTTP code.
*
*************************************************************************/
#ifndef nwm_HTTP_H
#define nwm_HTTP_H

#include "global.h"
#include "cx077.h" //Modem header file
#include "httpcli.h" //HTTP client header file

#define NWC_NUM_SEND_FORMS                (1)
#define NWC_NUM_SWUPDATE_FORMS            (1)
#define NWC_NUM_SWSTATUS_FORMS            (3)
#define NWC_HTML_DIGEST_HEADER_SIZE       (512)
#define NWC_HTML_SEND_HEADER_SIZE         (512)
#define NWC_HTML_RECEIVE_BUFFER_PART_SIZE (0x0010000L) //64KW boundary buffers that make whole buffer
#define NWC_HTML_RECEIVE_BUFFER_SIZE      (0x00100000L) //1MW = 2MB
#define NWC_HTML_PORTNUM                  (80)
#define NWC_MAX_NUM_FORMS                 (3)
#define NWC_MAX_FORM_NAME_SIZE            (20)
#define NWC_MAX_NETWORK_TIMEOUT           (60000UL) //Time in milleseconds
#define NWC_MAX_NETWORK_TIMEOUT1          (600000UL) //Time in milleseconds for large data post
#define NWC_LARGE_DATA_POST_BYTES         (500000UL)
#define NWC_HTML_ACTION                   "ACTION="
#define NWC_HTML_ENCTYPE                  "ENCTYPE="
#define NWC_HTML_METHOD                   "METHOD="
#define NWC_HTML_INPUT                    "INPUT"
#define NWC_HTML_NAME                     "NAME="
#define NWC_DEFAULT_FILENAME              "data.bin"
#define NWC_DEFAULT_FORMNAME              "File"
#define NWC_HTML_DATA_ACCEPTED            "Data Accepted"
#define NWC_HTML_DATA_REJECTED            "Data NOT Accepted"
#define NWC_HTML_DATA_NONE                "No Update"
//Default server name length should be less than NWM_HTTP_SERVER_NAME_MAX_SIZE
#ifdef _DEBUG
        #warn "Non-production HTTP server name is in use"
        #define NWC_HTTP_DEF_SERVER "172.19.51.56"    // IDC test server, not production
#else
        #define NWC_HTTP_DEF_SERVER "usprod.carelinkmonitor.net"    // IDC production
#endif
//Default HTTP page name length should be less than NWM_HTTP_FILE_NAME_MAX_SIZE
#define NWC_HTTP_DEF_DATA_PAGE     "/2490.html"
#define NWC_HTTP_DEF_FWUPDATE_PAGE "/2490FwUpdate.html"
#define NWC_HTTP_DEF_STAT_PAGE     "/2490status.html"
#define NWC_HTTP_DEF_STAT_TAR      "/2490status.asp"
#define NWC_HTTP_DEF_STAT_SN       "SerialNumber"
#define NWC_HTTP_DEF_STAT_VER      "FirmwareVersion"
#define NWC_HTTP_DEF_STAT_SUC      "Succeeded"
#define NWC_HTTP_SUCCESS           "success"
#define NWC_HTTP_FAILURE           "failure"
#define NWC_HTML_BUFFER_LEN        513
#define NWC_SU_NULL4               "\xff\xff\xff\xff"

/* HTTP Packet Header 'tags'*/
#define NWC_HTTP_DEFAULT_SEND_HEADER_1   ""
#define NWC_HTTP_CONTENT_LENGTH          "Content-Length: "
#define NWC_HTTP_CONTENT_ENC             "Content-Encoding: "
#define NWC_HTTP_CONTENT_TYPE            "Content-Type: "
#define NWC_HTTP_LAST_MODIFIED           "Last-Modified: "
#define NWC_HTTP_ETAG                    "ETag: "
#define NWC_HTTP_EXPIRES                 "Expires: "
#define NWC_HTTP_LOCATION                "Location: "
#define NWC_HTTP_RESPONSE_HEADER         "HTTP/1.0"
#define NWC_HTTP_RESPONSE_HEADERA        "HTTP/1.1"
#define NWC_HTTP_BASIC                   "Basic realm="
#define NWC_HTTP_AUTHENTICATE            "WWW-Authenticate: "
#define NWC_HTTP_AUTHORIZATION           "Authorization: "
#define NWC_HTTP_IF_MODIFIED_SINCE       "If-Modified-Since: "
#define NWC_HTTP_DATE                    "Date: "
#define NWC_HTTP_QUOTE                   "\""
#define NWC_HTTP_COOKIE                  "Set-Cookie: "
#define NWC_HTTP_DIRECTORY_SLASH         '/'
#define NWC_HTTP_HEADER_LINE_END         "\r\n"
#define NWC_HTTP_DIGEST                  "Digest"
#define NWC_HTTP_DEFAULT_DIGEST_HEADER_1 ""


/* Software update section types. */
#define NWC_SU_MAIN_SECT  0x01
#define NWC_SU_TELEM_SECT 0x02
#define NWC_SU_Flash_SECT 0x03

/* used in HTTP_find_header call for either case sensitive or case insensitive comparison */
#define HTTP_HDR_CASE_SENSITIVE_CMP   1
#define HTTP_HDR_CASE_INSENSITIVE_CMP 0


/* Update tag for flash*/
typedef struct ee_struct
{
    UINT16 address;              //address in flash to update
    UINT16 length;               //length of flash consumed by parameter
    char name[14];               //expected string from FDN in order to update parameter
} flash_tag;

typedef struct stat_struct_a
{
    char sn_name[16];
    char sn_value[16];
    char ver_name[16];
    char ver_value[16];
    char suc_name[16];
    char suc_value[16];
} stat_struct;



/* Function prototypes. */
/* Public Functions*/
UINT16 nwm_HTTP_Send_Data(void);
void   nwm_RetrieveHTTPDateTime(char* datetimestr, UINT32* ticks);

/* Unit Test function */
void UTest1_HTTP_Initialization(void);

/* Private Functions*/
UINT16 nwm_HTTP_FirmwareUpdate(void);
void   nwm_Send_FU_Status(bool fustatus);
void   nwm_Extract_DateTime(char* httpBuffer, char* dateTime);
void   nwm_RetrieveHTTPDateTime(char *dateTimestr, unsigned long *ticks);
void   nwm_Extract_HTTP_Target(form_struct* form);
BOOL   nwm_Update_Flash(UINT16 *basePtr, UINT32 offset, UINT32 length);
char*  extract_parameter(UINT16 *base_ptr, UINT32 offset);
void   nwm_HTTP_Setup(int numForms);
void   print_http_request();

#endif

