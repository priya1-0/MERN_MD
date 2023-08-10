/************************************************************************
*
* MODULE: com_eepromapp.h
*
* OWNER:
*
* DESCRIPTION: The application level FLASH data map is
* defined here. The FLASH is managed by functions in
* AssetManagement, ConfigurationData, EventLog and
* AppScratchPad modules
*
* FLASH Memory Addresses relative to block type address
* Non-Volatile Storage
* Address Range(BYTES)		Usage
* 0000-1DFF					Application ScratchPad
* 1E00-1FFD					Asset Management, Configuration Data, BSM Management
* 1FFE-1FFF					Non-Volatile Storage CRC
*
*
* GLOBAL DEFINES:
*
* ENDPURPOSE
*
*************************************************************************/
#ifndef __FLASH_MAP_H
#define __FLASH_MAP_H

/**********************************************************************/
/* FLASH addresses and lengths                                        */
/**********************************************************************/

//address of flash within system
//1mb - also must change block counts in specific flash to match this
//#define bsc_EELastAddr		   (0x7FFFF)//The last address in flash in WORDS,
//denotes size of flash, not full

//2mb  - also must change block counts in specific flash to match this
#define bsc_EELastAddr (0xFFFFF)            //The last address in flash in WORDS,
//denotes size of flash, not full
//address of flash within system
//ADDRESSes in WORDS
#define bsc_FLASHBASEADDR (0x200000)         //Base Address of Flash in main memory map, word address
//Non-volatile Storage Block Locations
#define bsc_NV_PRIMARY_BLOCK_ADDR (bsc_EELastAddr - bsc_NVStorage_SIZE + 1) //Address of Primary Non-volatile storage block, Relative to flash
#define bsc_NV_BACKUP_BLOCK_ADDR  (bsc_EELastAddr - 2*bsc_NVStorage_SIZE + 1) //Address of backupNon-volatile storage block, Relative to flash
#define bsc_NVStorage_SIZE        (0x1000)  //  8kB =  4kW Block size, Total size of Non-Volatile Storage (in Words)
#define bsc_SST_NVSECT_COUNT      (2)       //Number of SST sectors that comprise the NVStorage block
#define bsc_INTEL_NVSECT_COUNT    (1)       //Number of INTEL sectors that comprise the NVStorage block
//Event Log Block Location          F8000
#define bsc_EVENTLOG_BLOCK_ADDR (bsc_EELastAddr - 2*bsc_NVStorage_SIZE - bsc_EVENTLOG_SIZE + 1)   //Event Log block, Relative to flash
#define bsc_EVENTLOG_SIZE       (0x6000)   // 48kB = 24kW Block size, Total size of Event Log (in Words)
#define bsc_SST_ELSECT_COUNT    (12)        //Number of SST sectors that comprise the EventLog block
#define bsc_INTEL_ELSECT_COUNT  (6)         //Number of INTEL sectors that comprise the EventLog block
//Code Block Location
#define bsc_CODE_BLOCK_ADDR       (0x00000) //Code block, Relative to flash
#define bsc_CODE_BLOCK_LENGTH     (bsc_EVENTLOG_BLOCK_ADDR) //Code block length in words
#define bsc_SST_CODE_BLCK_COUNT   (31)      //Number of SST blocks that comprise the Code block
#define bsc_INTEL_CODE_BLCK_COUNT (31)      //Number of INTEL blocks that comprise the Code block


//Flash TypeDef
typedef enum
{
    bsc_INTEL=0,
    bsc_SST,
    bsc_Unknown
}  bsc_Flash_Type;


//ISP Auth Medthod TypeDef
#define bsc_PAP      "PAP"
#define bsc_CHAP     "CHAP"
#define bsc_SCRIPTED "SCRIPTED"

/**********************************************************************/
/* FLASH sizes in BYTES: All must be even (so that they are aligned)  */
/**********************************************************************/

//Application ScratchPad
#define coc_AppScratchPad_SIZE (0x1800)             // 6kB space for Application Scratch Pad

//Asset Management Data
#define coc_SWVer_SIZE                     (4)    // Software Version
#define coc_EEPROM_SN_SIZE                 (16)   // serial number of the 2490 Remote Monitor
#define coc_DIALPREFIX_SIZE                (6)    // prefix list, must be as large as string size with null-terminating character do to parameter updating
#define coc_LastInterrogateDuration_SIZE   (2)    // duration of  last interrogation in seconds
#define coc_FileTransferAttempts_SIZE      (2)    // file transfer attempts
#define coc_NetworkConnectionAttempts_SIZE (2)    // number of network connection attempts
#define coc_HWMetric_SIZE                  (4)    // Cumulative on-time

//Configuration Data
#define coc_StaticDNS_SIZE     (20)               // static DNS of form (123.321.231.312)
#define coc_ISPAuthMethod_SIZE (10)               // Authentication method used for ISP (PAP, CHAP, SCRIPTED)
#define coc_IPLoginID_SIZE     (48)               // IPLogin ID
#define coc_IPPassword_SIZE    (48)               // IPLogin Password
#define coc_EncryptionKey_SIZE (32)               // Encryption Key Max 256 bit key
#define coc_HTTPLoginID_SIZE   (20)               // Server Login ID
#define coc_HTTPPassword_SIZE  (20)               // Server Login Password
#define coc_ISPPhone1_SIZE     (32)               // ISP Phone Number 1 UUNET
#define coc_ISPPhone2_SIZE     (32)               // ISP Phone Number 2 AT&T
#define coc_ISPPhone3_SIZE     (32)               // ISP Phone Number 3
#define coc_ISPPhone4_SIZE     (32)               // ISP Phone Number 4
#define coc_ISPHostName_SIZE   (32)               // ISP Host Name (has default value if blank,
                                                  //  used for redirection in testing)
#define coc_HTTPServerName_SIZE (64)              // Server Name (has default value if blank,
                                                  //  used for redirection in testing)
#define coc_HTTPHomePage_SIZE (32)                // HTTP Home Page Name (has default value if blank,
                                                  //  used for redirection in testing)
#define coc_MDMCountryCode_SIZE (4)               // Modem Country code stored as an ASCII integer
//BSM Management Data
#define coc_CurrLogRead_SIZE  (2)                 // CurrLogRead  value -- points to byte to read in log space
#define coc_CurrLogWrite_SIZE (2)                 // CurrLogWrite value -- points to next unused byte in log space

//CRC Data, NOTE: CRC Should be the LAST element in this space!
#define coc_CRC_SIZE (2)                          // CRC Space

// Application Session Data

#define coc_LastSessionParameters_SIZE (200)       // session management data - set to max. of marquis.
#define coc_LastDevice_SIZE            (4)        // device id - set to max. of marquis
#define coc_LastSerial_SIZE            (20)       // serial number size - set to max. of marquis

#define coc_FunctionalTestDoneFlag_SIZE (2)       // (Reserved) Flag to indicate whether all functional tests passed
#define coc_BurnInTestStaus_SIZE        (2)       // Flag to indicate whether this board has passed the burn in test or failed.

#define coc_LastSessionParametersCrc_SIZE (2)     // size of session management data CRC
#define coc_ISPLastWorkPhoneFlag_SIZE     (2)     // Flag to indicate the ISP last working Phone
#define coc_ISPLastWorkPrefix_SIZE        (2)     // ISP Last Working Prefix
#define coc_LastUsedPrefix_SIZE           (2)     // Last Used Prefix 


/* FLASH Memory Map data addresses*/
typedef enum {
//Application ScratchPad
/* 2KB of Application Scratch pad                   */ coc_AppScratchPad_ADDR             = (0x0000),

//Asset Management Data
/* Software version of the 2490 Remote Monitor      */ coc_SWVer_ADDR                     = coc_AppScratchPad_ADDR + coc_AppScratchPad_SIZE,
/* serial number of the 2490 Remote Monitor         */ coc_EEPROM_SN_ADDR                 = coc_SWVer_ADDR + coc_SWVer_SIZE,
/* prefix list                                      */ coc_DIALPREFIX_ADDR                = coc_EEPROM_SN_ADDR  + coc_EEPROM_SN_SIZE,
/* duration of  last interrogation in seconds       */ coc_LastInterrogateDuration_ADDR   = coc_DIALPREFIX_ADDR + coc_DIALPREFIX_SIZE,
/* file transfer attempts                           */ coc_FileTransferAttempts_ADDR      = coc_LastInterrogateDuration_ADDR + coc_LastInterrogateDuration_SIZE,
/* number of network connection attempts            */ coc_NetworkConnectionAttempts_ADDR = coc_FileTransferAttempts_ADDR + coc_FileTransferAttempts_SIZE,
/* Hardware Metric - Cumulative on-time             */ coc_HWMetric_ADDR                  = coc_NetworkConnectionAttempts_ADDR + coc_NetworkConnectionAttempts_SIZE,

//Configuration Data
/* static DNS                                       */ coc_StaticDNS_ADDR                 = coc_HWMetric_ADDR + coc_HWMetric_SIZE,
/* ISP Authentication Method                        */ coc_ISPAuthMethod_ADDR             = coc_StaticDNS_ADDR + coc_StaticDNS_SIZE,
/* ISP Login ID                                     */ coc_IPLoginID_ADDR                 = coc_ISPAuthMethod_ADDR + coc_ISPAuthMethod_SIZE,
/* ISP Login Password                               */ coc_IPPassword_ADDR                = coc_IPLoginID_ADDR + coc_IPLoginID_SIZE,
/* Encryption Key Max 256 bit key                   */ coc_EncryptionKey_ADDR             = coc_IPPassword_ADDR + coc_IPPassword_SIZE,

/* HTTP Server Login ID                             */ coc_HTTPLoginID_ADDR               = coc_EncryptionKey_ADDR + coc_EncryptionKey_SIZE,
/* HTTP Server Login Password                       */ coc_HTTPPassword_ADDR              = coc_HTTPLoginID_ADDR + coc_HTTPLoginID_SIZE,
/* ISP Phone Number 1                               */ coc_ISPPhone1_ADDR                 = coc_HTTPPassword_ADDR + coc_HTTPPassword_SIZE,
/* ISP Phone Number 2                               */ coc_ISPPhone2_ADDR                 = coc_ISPPhone1_ADDR + coc_ISPPhone1_SIZE,
/* ISP Phone Number 3                               */ coc_ISPPhone3_ADDR                 = coc_ISPPhone2_ADDR + coc_ISPPhone2_SIZE,
/* ISP Phone Number 4                               */ coc_ISPPhone4_ADDR                 = coc_ISPPhone3_ADDR + coc_ISPPhone3_SIZE,
/* ISP Host Name (has default value if blank,       */ coc_ISPHostName_ADDR               = coc_ISPPhone4_ADDR + coc_ISPPhone4_SIZE,
/*  used for redirection in testing)                */
/* Server Name (has default value if blank,         */ coc_HTTPServerName_ADDR            = coc_ISPHostName_ADDR + coc_ISPHostName_SIZE,
/*  used for redirection in testing)                */
/* HTTP Home Page Name (has default value if blank, */ coc_HTTPHomePage_ADDR              = coc_HTTPServerName_ADDR + coc_HTTPServerName_SIZE,
/*  used for redirection in testing)                */
/* Modem Country code stored as an integer          */ coc_MDMCountryCode_ADDR            = coc_HTTPHomePage_ADDR + coc_HTTPHomePage_SIZE,

//BSM Management Data
/* CurrLogRead value -- points to next byte to read */ coc_CurrLogRead_ADDR               = coc_MDMCountryCode_ADDR + coc_MDMCountryCode_SIZE,
/* CurrLogWrite value -- points to next unused byte */ coc_CurrLogWrite_ADDR              = coc_CurrLogRead_ADDR + coc_CurrLogRead_SIZE,

/* Funtional Test Done Flag - (Reserved) FUNCTION_TEST_FLAG_VALUE is defined in bsm_CheckHardware.c.  This value means the unit is ready for the field.
                            - all other values indicate a non-field unit */
    coc_FunctionalTestDoneFlag_ADDR                                                       = coc_CurrLogWrite_ADDR + coc_CurrLogWrite_SIZE,
    coc_BurnInTestStaus_ADDR                                                              = coc_FunctionalTestDoneFlag_ADDR + coc_FunctionalTestDoneFlag_SIZE,

/* session management data                          */ coc_LastSessionParameters_ADDR     = coc_BurnInTestStaus_ADDR + coc_BurnInTestStaus_SIZE,
/* device id                                        */ coc_LastDevice_ADDR                = coc_LastSessionParameters_ADDR + coc_LastSessionParameters_SIZE,
/* serial number of device                          */ coc_LastSerial_ADDR                = coc_LastDevice_ADDR + coc_LastDevice_SIZE,
/* session management data CRC                      */ coc_LastSessionParametersCrc_ADDR  = coc_LastSerial_ADDR + coc_LastSerial_SIZE,
/* last working phone                               */ coc_ISPLastWorkPhoneFlag_ADDR      = coc_LastSessionParametersCrc_ADDR + coc_LastSessionParametersCrc_SIZE,
/* ISP Last Working Prefix                          */ coc_ISPLastWorkPrefix_ADDR         = coc_ISPLastWorkPhoneFlag_ADDR + coc_ISPLastWorkPhoneFlag_SIZE,
/* Last Used Prefix                                 */ coc_LastUsedPrefix_ADDR            = coc_ISPLastWorkPrefix_ADDR + coc_ISPLastWorkPrefix_SIZE,

//CRC Data, NOTE: CRC Should be the LAST element in this space!
/* CRC For the NVStorage Block                      */ coc_CRC_ADDR                       = bsc_NVStorage_SIZE * 2 - coc_CRC_SIZE  //(0x1FFE)//Note: This is in Bytes. Since this is the last
} coc_EEPROMApplicationAddress;

#endif
