/************************************************************************
*
* MODULE: 2490G_Defaults.c
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This is a development-only function to set the NV storage
* to safe testing values.
*
*************************************************************************/

/////////////
// Includes
/////////////


#include "bsm_Event.h"
#include "bsm_NVStorage.h"
#include "com_eepromapp.h"
#include "nwm_http.h"

#include <string.h>


////////////
// Globals
////////////

#define Cred 1

#if Cred == 1
//Credentials 1
        #define SN            "IJR000090P"
        #define SWVer         "1234"
        #define EncryptionKey "s9bPR0l"
//	#define ISP_UIC      "qnet-dnvyz-30450"
//	#define ISP_PASSWORD "04aqfw2kq9620xuo"
        #define ISP_UIC            "qnet-ppytl-47034"
        #define ISP_PASSWORD       "cxjytij2kwn86dgp"
        #define HTTP_USER_NAME     "qapp-6745-uswxfw"
        #define HTTP_USER_PASSWORD "Pg4uD7XXvrB6UlFb"
#elif Cred == 2
//Credentials 2
        #define SN            "IJR000091P"
        #define SWVer         "1234"
        #define EncryptionKey "hsGpX6u"
//	#define ISP_UIC      "qnet-legvw-60984"
//	#define ISP_PASSWORD "c6t95fpyku8kh557"
        #define HTTP_USER_NAME     "qapp-1702-bcgfci"
        #define HTTP_USER_PASSWORD "AnMo7lvK2m0Azs7v"
        #define ISP_UIC            "qnet-ppytl-47034"
        #define ISP_PASSWORD       "cxjytij2kwn86dgp"
#elif Cred == 3
//Credentials 3
        #define SN                 "IJR000092P"
        #define EncryptionKey      "mAcMHma"
        #define ISP_UIC            "qnet-gjghd-39107"
        #define ISP_PASSWORD       "oat7td0k5cbcy7df"
        #define HTTP_USER_NAME     "qapp-2969-fjyxzl"
        #define HTTP_USER_PASSWORD "1PPZ8fw2lSmv9Uzk"
#elif Cred == 4
//Credentials 4
        #define SN                 "IJR000093P"
        #define EncryptionKey      "GK8mdqE"
        #define ISP_UIC            "qnet-eavzy-48197"
        #define ISP_PASSWORD       "vi5bbhmgqi85y1ki"
        #define HTTP_USER_NAME     "qapp-1015-wlrczi"
        #define HTTP_USER_PASSWORD "3yEfB8gitg1MwhWY"
#elif Cred == 5
//Credentials 5
        #define SN                 "IJR000094P"
        #define EncryptionKey      "GuFM2OO"
        #define ISP_UIC            "qnet-fdplr-87128"
        #define ISP_PASSWORD       "3in86cb3u8xq7u9b"
        #define HTTP_USER_NAME     "qapp-7712-inppmm"
        #define HTTP_USER_PASSWORD "lidrItu3S7e1GSsV"
#elif Cred == 6
//Credentials 6
        #define SN                 "IJR000020P"
        #define EncryptionKey      "KwgtxKB"
        #define ISP_UIC            "qnet-dhtst-24108"
        #define ISP_PASSWORD       "l4arsh0ku6g6sp07"
        #define HTTP_USER_NAME     "qapp-3345-ffevfh"
        #define HTTP_USER_PASSWORD "O4x5AVxZiJsLfTmf"
#elif Cred == 7
//Credentials 7
        #define SN                 "IJR000021P"
        #define EncryptionKey      "WBNmYPO"
        #define ISP_UIC            "qnet-mmyvx-92381"
        #define ISP_PASSWORD       "m3g3h9wpzl8iicgu"
        #define HTTP_USER_NAME     "qapp-7633-rzcdze"
        #define HTTP_USER_PASSWORD "XBY1x3PrYOaS4ral"
#elif Cred == 8
//Credentials 8
        #define SN                 "IJR000022P"
        #define EncryptionKey      "6a75fKb"
        #define ISP_UIC            "qnet-xsswd-14287"
        #define ISP_PASSWORD       "8ol9xkyz1nozngu8"
        #define HTTP_USER_NAME     "qapp-3882-wghsix"
        #define HTTP_USER_PASSWORD "3MQ0EXkgQ3hjqfTh"
#elif Cred == 9
//Credentials 9
        #define SN                 "IJR000023P"
        #define EncryptionKey      "HHcY8Ij"
        #define ISP_UIC            "qnet-gtwjp-54372"
        #define ISP_PASSWORD       "f1xf6yr6k67nwnsu"
        #define HTTP_USER_NAME     "qapp-5145-gfdyhp"
        #define HTTP_USER_PASSWORD "E9NaeTmENGMVCkoB"
#elif Cred == 10
//Credentials 10
        #define SN                 "IJR000024P"
        #define EncryptionKey      "sFGz4B7"
        #define ISP_UIC            "qnet-vhtms-29943"
        #define ISP_PASSWORD       "e92qjqxb92jb7pi7"
        #define HTTP_USER_NAME     "qapp-2738-ihwtdp"
        #define HTTP_USER_PASSWORD "UZT4WhCGRKbP1Gff"
#elif Cred == 11
//Credentials 11
        #define SN                 "IJR000025P"
        #define EncryptionKey      "dcrzvEp"
        #define ISP_UIC            "qnet-sbkmb-72864"
        #define ISP_PASSWORD       "1fxpn8vrt0tcdfuw"
        #define HTTP_USER_NAME     "qapp-6221-qesygd"
        #define HTTP_USER_PASSWORD "Nmig0woySe8sraiM"
#elif Cred == 12
//Credentials 12
        #define SN                 "IJR000026P"
        #define EncryptionKey      "ojLHdo0"
        #define ISP_UIC            "qnet-bvury-82990"
        #define ISP_PASSWORD       "am7dn1fj1p7gxme2"
        #define HTTP_USER_NAME     "qapp-9554-llicpd"
        #define HTTP_USER_PASSWORD "cLo1lYV6eprzNoUW"
#elif Cred == 13
//Credentials 13
        #define SN                 "IJR000027P"
        #define EncryptionKey      "59HB94o"
        #define ISP_UIC            "qnet-umyfv-21153"
        #define ISP_PASSWORD       "zrbsgpv1p92mvna1"
        #define HTTP_USER_NAME     "qapp-7528-gzsvfc"
        #define HTTP_USER_PASSWORD "49p7p8knaIz7E2n2"
#elif Cred == 14
//Credentials 14
        #define SN                 "IJR000028P"
        #define EncryptionKey      "lA24MHa"
        #define ISP_UIC            "qnet-foxtf-31641"
        #define ISP_PASSWORD       "p2zog03svbw236ul"
        #define HTTP_USER_NAME     "qapp-2536-wcdezr"
        #define HTTP_USER_PASSWORD "8Jn6HEjSIJjWHuFN"
#elif Cred ==15
//Credentials 2490J 15
        #define SN                 "IJT000004P"
        #define EncryptionKey      "Z0SBX4A"
        #define ISP_UIC            "qnet-ppytl-47034@idctest.medtronic.com"
        #define ISP_PASSWORD       "cxjytij2kwn86dgp"
        #define HTTP_USER_NAME     "qapp-2776-mtnnub"
        #define HTTP_USER_PASSWORD "dZohMwRj40xfpFfP"
#else
//Credentials 16
        #define SN                 "IJR000029P"
        #define EncryptionKey      "BtLFlGJ"
        #define ISP_UIC            "qnet-mxqke-61984"
        #define ISP_PASSWORD       "0plthbhlizaf2f04"
        #define HTTP_USER_NAME     "qapp-7674-nathlj"
        #define HTTP_USER_PASSWORD "3daxBbJcYvDhSIh0"
#endif

#define SWVer "1234"

//#define NWC_DEF_HOSTNAME           "MDTRMQ" // Non-production
//#define NWC_DEF_PHONE              "18005721959"
#define NWC_DEF_HOSTNAME     "idctest.medtronic.com"       // IDC-production
#define NWC_DEF_PHONE        "18884137028"       //New MCI
#define NWC_DEF_PHONE_PREFIX "\x00\x37\x38\x39"

//#define AUTH_TYPE bsc_SCRIPTED
#define AUTH_TYPE bsc_CHAP

//#define NWC_HTTP_DEF_SERVER    "172.24.36.37"   // DEV, not production
//#define NWC_HTTP_DEF_SERVER    "172.24.37.100"  // DEV, not production
//#define NWC_HTTP_DEF_SERVER    "172.24.36.36"   // DEV2, not production


#define PARAM_PAIR(x) ((int)(x ## _ADDR)),((int)(x ## _SIZE))

#define D_BINARY 1
#define D_TEXT   0

struct NVDefaults {
    int textOrBinary;
    int address;
    int size;
    char* data;
};

struct NVDefaults DefaultTable[] = {
    { D_TEXT, PARAM_PAIR(coc_SWVer), SWVer },
    { D_TEXT, PARAM_PAIR(coc_EEPROM_SN), SN },
    { D_BINARY, PARAM_PAIR(coc_DIALPREFIX), NWC_DEF_PHONE_PREFIX },
    { D_TEXT, PARAM_PAIR(coc_ISPAuthMethod), AUTH_TYPE },
    { D_TEXT, PARAM_PAIR(coc_IPLoginID), ISP_UIC },
    { D_TEXT, PARAM_PAIR(coc_IPPassword), ISP_PASSWORD },
    { D_TEXT, PARAM_PAIR(coc_EncryptionKey), EncryptionKey },
    { D_TEXT, PARAM_PAIR(coc_HTTPLoginID), HTTP_USER_NAME },
    { D_TEXT, PARAM_PAIR(coc_HTTPPassword), HTTP_USER_PASSWORD },
    { D_TEXT, PARAM_PAIR(coc_ISPPhone1), NWC_DEF_PHONE },
    { D_TEXT, PARAM_PAIR(coc_ISPPhone2), NWC_DEF_PHONE },
    { D_TEXT, PARAM_PAIR(coc_ISPPhone3), NWC_DEF_PHONE },
    { D_TEXT, PARAM_PAIR(coc_ISPPhone4), NWC_DEF_PHONE },
    { D_TEXT, PARAM_PAIR(coc_ISPHostName), NWC_DEF_HOSTNAME },
    { D_TEXT, PARAM_PAIR(coc_HTTPServerName), NWC_HTTP_DEF_SERVER },
    { D_TEXT, PARAM_PAIR(coc_HTTPHomePage), NWC_HTTP_DEF_DATA_PAGE  },
// This gets the package to the server area where package can be retrieved.
//{ D_TEXT	, PARAM_PAIR(coc_HTTPHomePage)	, "/2490_local.html"  },
};

#define NUMBER_OF_DEFAULTS (sizeof(DefaultTable)/sizeof(struct NVDefaults))

void setNVDefaultsForDevelopment(void)
{
    int  x;
    bool status;
    char largeBuffer[100];
    int  compareResult;

    status = FALSE;



    for (x = 0; x < NUMBER_OF_DEFAULTS; x++)
    {
        largeBuffer[DefaultTable[x].size] = 0;         // Set terminator

        // Read current value
        bsm_EEReadBuf(largeBuffer, DefaultTable[x].size, DefaultTable[x].address);

        // Do a text/zero-terminated compare or a binary

        compareResult = (DefaultTable[x].textOrBinary == D_TEXT) ?
                        strcmp(largeBuffer, DefaultTable[x].data ) :
                        memcmp(largeBuffer, DefaultTable[x].data, DefaultTable[x].size );

        // If not the default we want, set it

        if(compareResult)
        {
            (DefaultTable[x].textOrBinary == D_TEXT) ?
            strcpy(largeBuffer, DefaultTable[x].data) :
            memcpy(largeBuffer, DefaultTable[x].data, DefaultTable[x].size);
            bsm_EEWriteBuf(largeBuffer, DefaultTable[x].size,DefaultTable[x].address);
            status = TRUE;
        }
    }

    bsm_EHClearLog();

    //Flush any changes to flash
    if(status == TRUE)
    {
        bsm_EEFlush();
    }
}


