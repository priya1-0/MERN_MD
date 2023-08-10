/************************************************************************
*
* MODULE: dbg_menu.c
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the functions to print the menu.
*
*************************************************************************/

/////////////
// includes
/////////////

#include "global.h"
#include "bsm_serialport.h"

#include "com_eepromapp.h"
#include <stdio.h>

#ifdef __DEV_VT__
/******************************************************************

FUNCTION: PrintMenu

DESCRIPTION: This function prints the debug menu to the serial port

ARGS:
        <none>

RETURNS:
    <none>

******************************************************************/
void PrintMenu(void)
{
    bsm_SDPrint("< Main Menu >");
    bsm_SDPrint("SI-System ID");
    bsm_SDPrint("TW-Test Watchdog");
    bsm_SDPrint("BT-Read Battery Threshold");
    bsm_SDPrint("LE-Set Led");
    bsm_SDPrint("RT-Read Pulse Tone Switch");
    bsm_SDPrint("RP-Read Prefix Switch");
    bsm_SDPrint("AS-Set Audio Speaker");
    bsm_SDPrint("CR-Continuous RF");
#ifdef __2490TELEMB__
    bsm_SDPrint("TB-Receive Telemetry B");
    bsm_SDPrint("TH-Telemetry B H-Field Test App");
    bsm_SDPrint("TT-Telemetry B Item Mapping, Triggered");
    bsm_SDPrint("TS-Telemetry B Item Mapping, Single Cycle");
    bsm_SDPrint("TC-Telemetry B 100 Count L/H Data Rate Test");
#endif
    bsm_SDPrint("BC-Start Counting Telemetry A Pulses");
    bsm_SDPrint("EC-Stop Counting Telemetry A Pulses");
    bsm_SDPrint("BJ-Start Telemetry A Jitter");
    bsm_SDPrint("EJ-Stop Telemetry A Jitter");
    bsm_SDPrint("SM-SDRAM Memory Test");
    bsm_SDPrint("IM-Internal Memory Test");
    bsm_SDPrint("CF-Calculate CRC");
    bsm_SDPrint("BI-Burn In Test");
    bsm_SDPrint("WF-Write Flash");
    bsm_SDPrint("RF-Read Flash");
    bsm_SDPrint("RL-Read Log");
    bsm_SDPrint("CL-Clear Log");
    bsm_SDPrint("CC-Commit Flash Changes");
    bsm_SDPrint("SU-Software Update");
    bsm_SDPrint("LP-Load Temporary Program");
    bsm_SDPrint("OM-Open Modem");
    bsm_SDPrint("MD-Send Command To Modem");
    bsm_SDPrint("MT-Modem Terminal Data Exchange");
    bsm_SDPrint("MI-Modem, Ignore carrier loss & retraining");
    bsm_SDPrint("MC-Modem, Force Dialtone Cadence Detection Enable");
    bsm_SDPrint("MS-Modem, Set DTMF Signal Strength");
    bsm_SDPrint("CM-Close Modem");
    bsm_SDPrint("EA-Print EEPROM Addresses");
    bsm_SDPrint("ST-Send Telemetry A Messages");
    bsm_SDPrint("SR-Read S-Registers from SiLab Chip");     // Support country code testing
    bsm_SDPrint("SW-Write S-Registers from SiLab Chip");     // Support country code testing
    bsm_SDPrint("XX-Exit");
}
#endif // __DEV_VT__

/******************************************************************

FUNCTION: PrintEepromAddr

DESCRIPTION: This function prints the addresses of the fields
             located in the EEPROM.

ARGS:
        <none>

RETURNS:
    <none>

******************************************************************/
void PrintEepromAddr(void)
{
    char Buffer[80];

    sprintf(Buffer, "coc_AppScratchPad_ADDR = %d", coc_AppScratchPad_ADDR);
    bsm_SDPrint(Buffer);
    sprintf(Buffer, "coc_SWVer_ADDR = %d", coc_SWVer_ADDR);
    bsm_SDPrint(Buffer);
    sprintf(Buffer, "coc_EEPROM_SN_ADDR = %d", coc_EEPROM_SN_ADDR);
    bsm_SDPrint(Buffer);
    sprintf(Buffer, "coc_DIALPREFIX_ADDR = %d", coc_DIALPREFIX_ADDR);
    bsm_SDPrint(Buffer);
    sprintf(Buffer, "coc_LastInterrogateDuration_ADDR = %d", coc_LastInterrogateDuration_ADDR);
    bsm_SDPrint(Buffer);
    sprintf(Buffer, "coc_FileTransferAttempts_ADDR = %d", coc_FileTransferAttempts_ADDR);
    bsm_SDPrint(Buffer);
    sprintf(Buffer, "coc_NetworkConnectionAttempts_ADDR = %d", coc_NetworkConnectionAttempts_ADDR);
    bsm_SDPrint(Buffer);
    sprintf(Buffer, "coc_HWMetric_ADDR = %d", coc_HWMetric_ADDR);
    bsm_SDPrint(Buffer);
    sprintf(Buffer, "coc_StaticDNS_ADDR = %d", coc_StaticDNS_ADDR);
    bsm_SDPrint(Buffer);
    sprintf(Buffer, "coc_ISPAuthMethod_ADDR = %d", coc_ISPAuthMethod_ADDR);
    bsm_SDPrint(Buffer);
    sprintf(Buffer, "coc_IPLoginID_ADDR = %d", coc_IPLoginID_ADDR);
    bsm_SDPrint(Buffer);
    sprintf(Buffer, "coc_IPPassword_ADDR = %d", coc_IPPassword_ADDR);
    bsm_SDPrint(Buffer);
    sprintf(Buffer, "coc_EncryptionKey_ADDR = %d", coc_EncryptionKey_ADDR);
    bsm_SDPrint(Buffer);
    sprintf(Buffer, "coc_HTTPLoginID_ADDR = %d", coc_HTTPLoginID_ADDR);
    bsm_SDPrint(Buffer);
    sprintf(Buffer, "coc_HTTPPassword_ADDR = %d", coc_HTTPPassword_ADDR);
    bsm_SDPrint(Buffer);
    sprintf(Buffer, "coc_ISPPhone1_ADDR = %d", coc_ISPPhone1_ADDR);
    bsm_SDPrint(Buffer);
    sprintf(Buffer, "coc_ISPPhone2_ADDR = %d", coc_ISPPhone2_ADDR);
    bsm_SDPrint(Buffer);
    sprintf(Buffer, "coc_ISPPhone3_ADDR = %d", coc_ISPPhone3_ADDR);
    bsm_SDPrint(Buffer);
    sprintf(Buffer, "coc_ISPPhone4_ADDR = %d", coc_ISPPhone4_ADDR);
    bsm_SDPrint(Buffer);
    sprintf(Buffer, "coc_ISPHostName_ADDR = %d", coc_ISPHostName_ADDR);
    bsm_SDPrint(Buffer);
    sprintf(Buffer, "coc_HTTPServerName_ADDR = %d", coc_HTTPServerName_ADDR);
    bsm_SDPrint(Buffer);
    sprintf(Buffer, "coc_HTTPHomePage_ADDR = %d", coc_HTTPHomePage_ADDR);
    bsm_SDPrint(Buffer);
    sprintf(Buffer, "coc_MDMCountryCode_ADDR = %d", coc_MDMCountryCode_ADDR);
    bsm_SDPrint(Buffer);
    sprintf(Buffer, "coc_CurrLogRead_ADDR = %d", coc_CurrLogRead_ADDR);
    bsm_SDPrint(Buffer);
    sprintf(Buffer, "coc_CurrLogWrite_ADDR = %d", coc_CurrLogWrite_ADDR);
    bsm_SDPrint(Buffer);
    sprintf(Buffer, "coc_FunctionalTestDoneFlag_ADDR = %d", coc_FunctionalTestDoneFlag_ADDR);
    bsm_SDPrint(Buffer);
    sprintf(Buffer, "coc_BurnInTestStaus_ADDR = %d", coc_BurnInTestStaus_ADDR);
    bsm_SDPrint(Buffer);
    sprintf(Buffer, "coc_LastSessionParameters_ADDR = %d", coc_LastSessionParameters_ADDR);
    bsm_SDPrint(Buffer);
    sprintf(Buffer, "coc_LastDevice_ADDR = %d", coc_LastDevice_ADDR);
    bsm_SDPrint(Buffer);
    sprintf(Buffer, "coc_LastSerial_ADDR = %d", coc_LastSerial_ADDR);
    bsm_SDPrint(Buffer);
    sprintf(Buffer, "coc_LastSessionParametersCrc_ADDR = %d", coc_LastSessionParametersCrc_ADDR);
    bsm_SDPrint(Buffer);
    sprintf(Buffer, "coc_ISPLastWorkPhoneFlag_ADDR = %d", coc_ISPLastWorkPhoneFlag_ADDR);
    bsm_SDPrint(Buffer);
    sprintf(Buffer, "coc_ISPLastWorkPrefix_ADDR = %d", coc_ISPLastWorkPrefix_ADDR); 
    bsm_SDPrint(Buffer); 
    sprintf(Buffer, "coc_LastUsedPrefix_ADDR = %d", coc_LastUsedPrefix_ADDR); 
    bsm_SDPrint(Buffer);
    sprintf(Buffer, "coc_CRC_ADDR = %d", coc_CRC_ADDR);
    bsm_SDPrint(Buffer);
}
