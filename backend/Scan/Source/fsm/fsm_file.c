/*
************************************************************************
 2490 In-home Remote Monitor
 Copyright (c) Medtronic, Inc. 2001

 MODULE: Application File System Module routines.

 OWNER: Medtronic

 $Revision$

 $Date$

 $RCSfile$

 FUNCTIONS:
      --Public--
void fsm_InitFile(void)
fst_File* fsm_GetFile(void)
void fsm_NumberByte (unsigned char aByte)
void fsm_NumberInteger (unsigned int anInteger)
void fsm_NumberLong (unsigned long aLong)
void fsm_HexByte (unsigned char aByte)
void fsm_DataByte (char aByte)
void fsm_DataInteger (int anInteger)
void fsm_DataLong(unsigned int aULong)
void fsm_Data (char *p_src, int aLength)
void fsm_String (char *aString)
void fsm_StringWithoutNullTermination (char *aString)
void fsm_OpenFile ( char *deviceModelId, char *deviceSN, char *timeOfSave,
                    unsigned int numSections)
bool fsm_ReplaceFileInterrogationTimeStamp(char *pszTimeStamp)
void fsm_UpdateAssetDataAndCloseFile (void)
void fsm_AssetData ( void)
void fsm_FileSectionHeader ( fst_FileSectionHeader *fh)
void fsm_FileSectionHeaderUpdate (fst_FileSectionHeader *fh)
void fsm_FileCheckSum(void)
void fsm_FileCRC16 (void)

                --Private--

 DESCRIPTION:
This module contains the routines used to manage the RAM file which contains
the following sections:
     - Header
     - Asset Data


This module will manage all of the file pointers, checksum and encryption of the
RAM file.

File Header Content
-------------------
<file type>	Null terminate file type
<file version>	Null terminate file version
<model id>	Null Terminated "2490A"
<serial number>	Null Terminatedstring representing the serial number of the 2490 sending the data
<ICD model>	Null terminated ICD device model ID example "7273"
<ICD serial number>	Null Terminate string representing the serial number of the ICD
<2490 last session device time stamp>	Null terminated string representing the date/time the data  was interrogated
YYYY = year = 0000 - 9999
mm = month = 01 - 12
DD = day = 01 - 31
HH = hours = 00 - 23
MM = minutes = 00 - 59
SS = seconds = 00 - 59
<number of sections>	Binary word representing number of data sections to follow.
<data section>	See data section format.
<crc16 checksum> checksum of entire file before it is has been emcrypted. High byte/low byte

Data Section Header Content
---------------------------
<section type>	Null terminated representing section type (1=asset, 2= save-to-disk, 3=EPR, 4=waveforms
<version>	Null Terminated version of this section "1"
<length>	32bit Binary word representing length
<data content>	See Asset Content, Save-To-Disk Content and Presenting Waveform Content.

Asset Management Data Content
-----------------------------
<model id>                  Null Terminated "2490A"
<2490 firmware revision>    Null terminated string = "1.0"
<serial number>	            Null terminated bytes representing the serial number
                            of the 2490 sending the data
<prefix>	            Null terminated string representing the four possible
                            prefixes " 789"
<country code>              String 2 or 3 bytes in length representing country
                            of deployment. See SRS for country codes.
<ISP phone numbers>	    4 Null Terminated string representing the four
                            possible ISP phone numbers
<ISP auth method>           'PAP' CHAP' or 'SCRIPTED'
<DNS server>                The DNS server.
<total ON time>	            Two binary words representing the total Powered On
                            time in minutes. (never cleared)
< file transfer attempts>        Binary word representing number of file transfer attempts, cleared after data is sent.
< file transfer successes>       Binary word representing number successful file transfers, cleared after data is sent
<network connection attempts>    Binary word representing number network connect attempts, cleared after data is sent.
<network connection successes>   Binary word representing number successful network connections, cleared after data is sent
<interrogation duration>         Binary word representing in seconds the  interrogation duration, cleared after data is sent.
<number log entries>             Binary word representing total number of log entries.
<error / network connection log> Null terminated log strings

=======


 GLOBAL MODULE DATA:
 fsv_connectTimeIndex - Marks where connect time will be placed in the file

 STATIC MODULE DATA:

 ENDPURPOSE

************************************************************************
*/
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "types.h"
#include "target.h"
#include "global.h"
#include "bsm_global.h"
#include "fsm_file.h"
#include "fsm_encrypt.h"
#include "com_eepromapp.h"
#include "com_main.h"
#include "aim_NVStorage.h"
#include "bsm_AppCrc.h"

#ifdef __2490_HF_TELEMB__
#include "aim_epr.h"
extern ait_EPRData aiv_EPRData;        // For the EPR serial number
#endif

#include "fsm_pbfr.h"

fst_FileHeader       v_fileHeader;
fst_AssetDataSection v_assetData;

#define c_DSTypeNull       "0"
#define c_DSTypeAsset      "1"
#define c_DSTypeSaveToDisk "2"
#define c_DSTypeEPR        "3"
#define c_DSTypeWaveform   "4"

fst_FileSectionHeader fsv_SaveToDiskSectionHeader = {
    c_DSTypeSaveToDisk,     // char	;
    "1.0",     // char	version;
    0,         // long  length;
    0,         // long  startIndex;
};

fst_FileSectionHeader fsv_AssetSectionHeader = {
    c_DSTypeAsset,     // char	type;
    "1.0",     // char	version;
    0,         // long  length;
    0,         // long  startIndex;
};

fst_FileSectionHeader fsv_EPRSectionHeader = {
    c_DSTypeEPR,     // char	type;
    "1.0",     // char	version;
    0,         // long  length;
    0,         // long  startIndex;
};
fst_FileSectionHeader fsv_WaveformSectionHeader = {
    c_DSTypeWaveform,     // char	type;
    "1.0",     // char	version;
    0,         // long  length;
    0,         // long  startIndex;
};


// This index and valid-flag are used to save the location of the
// Asset Data Section.  This allows the second call to fsm_CloseFile()
// to resave the Asset Data Section information in the same location.
long assetDataSectionIndex               = 0;
bool assetDataSectionIndexValid          = false;

//Reset the Index
long fsv_FileInterrogationTimeStampIndex = -1;

// Defined as an extern here because it is decided at compile time
// by the specific project/application file as to the contents.
extern char* fsc_p_InstrumentModelIDString;

extern void aim_UpdateDateTime(void);

/*
***********************************************************************

 FUNCTION:   fsm_InitFile

 DESCRIPTION:
Initialize to an empty file. the application is responsible for
initializing it's waveform section header.

***********************************************************************
*/
void fsm_InitFile(void)
{
    // Allocate memory for the data file.
    fsm_PackedBfrInit(FSV_FILE);

    // Clear the file indexes and flags.
    assetDataSectionIndex               = 0;
    assetDataSectionIndexValid          = false;

    fsv_FileInterrogationTimeStampIndex = -1;

    //Initialize data
    memset((char *)&v_fileHeader,0,sizeof(fst_FileHeader));
    strcpy(v_fileHeader.fileType,"Text");
    strcpy(v_fileHeader.fileVersion,"1.0");
    strcpy(v_fileHeader.monitorModelId, fsc_p_InstrumentModelIDString);
    v_fileHeader.numSections = 3;

    memset((char *)&v_assetData,0,sizeof(fst_AssetDataSection));
    strcpy((char*)v_assetData.monitorModelId, fsc_p_InstrumentModelIDString);
}

/*
***********************************************************************

 FUNCTION:   fsm_GetFile

 DESCRIPTION:
Returns a pointer to the save to disk file.

 FUNCTION RETURN:
    Pointer to the save to disk file.


***********************************************************************
*/
#ifndef DSP_2490
fst_File* fsm_GetFile(void)
{
    return(&fsv_file);
}
#endif

/*
***********************************************************************

 FUNCTION:   fsm_NumberByte

 DESCRIPTION:
Outputs the ASCII, base 10 representation of a 1 byte value terminated with
a new line ("\n" = 0x0a).

Example:
value = 0x80; output = "128<nl>" = 31 32 38 0a

 FUNCTION PARAMETERS:
   aByte
      Value to be output.

***********************************************************************
*/
void fsm_NumberByte (unsigned char aByte)
{
#ifndef DSP_2490
    ADD_TO_FILE_INDEX(sprintf((char*)&fsv_file.file[fsv_file.index], "%u\n", aByte));
#else
    char buffer[20];
    (void)sprintf((char*)buffer, "%u\n", aByte);
    fsm_StringWithoutNullTermination(buffer);
#endif
}

/*
***********************************************************************

 FUNCTION:   fsm_NumberInteger

 DESCRIPTION:
Outputs the ASCII, base 10 representation of an integer terminated with a
new line ("\n" = 0x0a).

Example:
value = 0x80; output = "128<nl>" = 31 32 38 0a


 FUNCTION PARAMETERS:
   anInteger
      Value to be output.

***********************************************************************
*/
void fsm_NumberInteger (unsigned int anInteger)
{
#ifndef DSP_2490
    ADD_TO_FILE_INDEX(sprintf((char*)&fsv_file.file[fsv_file.index], "%u\n", anInteger));
#else
    char buffer[20];
    (void)sprintf(buffer, "%u\n", anInteger);
    fsm_StringWithoutNullTermination(buffer);
#endif
}

/*
***********************************************************************

 FUNCTION:   fsm_NumberLong

 DESCRIPTION:
Outputs the ASCII, base 10 representation of a long terminated with a
new line ("\n" = 0x0a).

Example:
value = 0x80; output = "128<nl>" = 31 32 38 0a

 FUNCTION PARAMETERS:
   aLong
      Value to be output.

***********************************************************************
*/
void fsm_NumberLong (unsigned long aLong)
{
#ifndef DSP_2490
    ADD_TO_FILE_INDEX(sprintf((char*)&fsv_file.file[fsv_file.index], "%lu\n", aLong));
#else
    char buffer[20];
    (void)sprintf(buffer, "%lu\n", aLong);
    fsm_StringWithoutNullTermination(buffer);
#endif
}

/*
***********************************************************************

 FUNCTION:   fsm_HexByte

 DESCRIPTION:
Outputs the ASCII, base 16 representation of a 1 byte value prepended by
"0x" and terminated with a new line ("\n" = 0x0a).

Example:
value = 0x80; output = "0x80" = 30 78 38 30

 FUNCTION PARAMETERS:
   aByte
      Value to be output.

***********************************************************************
*/
void fsm_HexByte (unsigned char aByte)
{
 #ifndef DSP_2490
    // Verify the file size will not be exceeded.
    if ((fsv_file.index + 4) >= FSC_MAX_FILE_SIZE)      // 4 Is the Set Length of Output
        bsm_EHLock("FSM - Exceeded file size.");

    // Write to the File, and Increment the Index
    ADD_TO_FILE_INDEX(sprintf((char*)&fsv_file.file[fsv_file.index], "0x%02x", aByte));
#else
    char buffer[10];
    (void)sprintf(buffer, "0x%02x", aByte);
    fsm_StringWithoutNullTermination(buffer);
#endif
}

/*
***********************************************************************

 FUNCTION:   fsm_DataByte

 DESCRIPTION:
Outputs a binary byte (char).

 FUNCTION PARAMETERS:
   aByte
      Value to be output.

***********************************************************************
*/
void fsm_DataByte (char aByte)
{
#ifndef DSP_2490
    fsv_file.file[fsv_file.index] = aByte;
    INCR_FILE_INDEX();
#else
    fsm_PackedBfrWrite(FSV_FILE,aByte);
#endif
}

/*
***********************************************************************

 FUNCTION:   fsm_DataInteger

 DESCRIPTION:
Outputs a binary integer.

 FUNCTION PARAMETERS:
   anInteger
      Value to be output.

***********************************************************************
*/
void fsm_DataInteger (int anInteger)
{
#ifndef DSP_2490
    fsv_file.file[fsv_file.index] = (anInteger&0xff00)>>8;  // high byte
    INCR_FILE_INDEX();
    fsv_file.file[fsv_file.index] = anInteger&0x00ff;     // low byte
    INCR_FILE_INDEX();
#else
    fsm_PackedBfrWrite(FSV_FILE, (char)((anInteger & 0xff00)>>8));
    fsm_PackedBfrWrite(FSV_FILE, (char) (anInteger & 0x00ff)    );
#endif
}
/*
***********************************************************************

 FUNCTION:   fsm_DataLong

 DESCRIPTION:
Outputs a binary unsigned long.

 FUNCTION PARAMETERS:
   anInteger
      Value to be output.

***********************************************************************
*/
void fsm_DataLong (unsigned long aULong)
{
#ifndef DSP_2490
    fsv_file.file[fsv_file.index] = (aULong & 0xff000000)>>24;  // high byte
    INCR_FILE_INDEX();
    fsv_file.file[fsv_file.index] = (aULong & 0x00ff0000)>>16;     // low byte
    INCR_FILE_INDEX();
    fsv_file.file[fsv_file.index] = (aULong & 0xff00)>>8;  // high byte
    INCR_FILE_INDEX();
    fsv_file.file[fsv_file.index] = aULong&0x00ff;     // low byte
    INCR_FILE_INDEX();
#else
    fsm_PackedBfrWrite(FSV_FILE,(char)((aULong & 0xff000000)>>24));     // high byte high word
    fsm_PackedBfrWrite(FSV_FILE,(char)((aULong & 0x00ff0000)>>16));             // low byte
    fsm_PackedBfrWrite(FSV_FILE,(char)((aULong & 0xff00    )>>8 ));     // high byte, low word
    fsm_PackedBfrWrite(FSV_FILE,(char)( aULong & 0x00ff         ));             // low byte
#endif
}


/*
***********************************************************************

 FUNCTION:   fsm_Data

 DESCRIPTION:
Outputs a length of data bytes.

Note:
This function does not use memcpy() for these reasons:
1.) Some copies are done from one area in fsv_file.file to
    an other area in fsv_file.file.  memcpy()'s results are
    undefined for objects that have areas that overlap.
2.) memcpy() takes an int-param for size.
    To ensure that the length of 65,535 is not exceeded an
    unsigned long is used.

 FUNCTION PARAMETERS:
   p_src
      Pointer to the data.

   length
      Length of the data pointed to by p_src.

***********************************************************************
*/
void fsm_Data (char *p_src, unsigned long length)
{
    unsigned long i;
#ifndef DSP_2490
    char *tempPointer;

    // Verify the file size will not be exceeded.
    if ((fsv_file.index + length) >= (FSC_MAX_FILE_SIZE - c_DATA_FILE_OFFSET))
        bsm_EHLock("FSM - Exceeded file size.");

    // Now that we've verified there's enough room copy the data.
    tempPointer = p_src;
    for (i = 0; i < length; i++)
    {
        fsv_file.file[fsv_file.index++] = *tempPointer;
        tempPointer++;
    }
#else
    fsm_PackedBfrWriteMultiple(FSV_FILE, p_src, length);
#endif

}

/*
***********************************************************************

 FUNCTION:   fsm_String

 DESCRIPTION:
Outputs a NULL terminated string.

 FUNCTION PARAMETERS:
   aString
      Value to be output.


***********************************************************************
*/
void fsm_String (char *aString)
{
#ifndef DSP_2490
    ADD_TO_FILE_INDEX(sprintf((char*)&fsv_file.file[fsv_file.index], "%s", aString));

    // The null terminator is not included in the returned count.
    INCR_FILE_INDEX();
#else
    fsm_PackedBfrWriteMultiple(FSV_FILE, aString, strlen(aString)+1);
#endif

}

/*
***********************************************************************

 FUNCTION:   fsm_StringWithoutNullTermination

 DESCRIPTION:
Outputs a NON-NULL terminated string.

 FUNCTION PARAMETERS:
   aString
      Value to be output.


***********************************************************************
*/
void fsm_StringWithoutNullTermination (char *aString)
{
#ifndef DSP_2490
    ADD_TO_FILE_INDEX(sprintf((char*)&fsv_file.file[fsv_file.index], "%s", aString));
#else
    fsm_PackedBfrWriteMultiple(FSV_FILE, aString, strlen(aString));
#endif
}

/*
***********************************************************************

 FUNCTION:	fsm_EEReadString

 DESCRIPTION:
 reads the string from EEProm and
 validates the that string passed is alpha numeric and null terminated.

 FUNCTION PARAMETERS:

***********************************************************************
*/
void fsm_EEReadString (char *string, unsigned int size, unsigned int address) {
    int i;

    bsm_EEReadBuf((unsigned char*)string,size, address);
    // validate string check for alpha number and null terminated
    for (i=0; i < size; i++) {
        if (!isalnum(string[i]))
            break;
    }
    if (string[i] != 0)
        string[i] = 0;

}




/*
***********************************************************************

 FUNCTION:	fsm_OpenFile

 DESCRIPTION:
Output the <file header> component of the general file structure posted to the
server.
File Header Content
-------------------
<file type>	Null terminate file type
<file version>	Null terminate file version
<model id>	Null Terminated "2490A"
<serial number>	NUll Terminate string representing the serial number of the 2490 sending the data
<ICD model>	Null terminated ICD device model ID example "7273"
<ICD serial number>	Null Terminated string representing the serial number of the ICD
<network time of connection>	Null terminated string representing the date/time
                the data  was interrogated.  Format = YYYYmmDDHHMMSS.
                YYYY = year = 0000 - 9999
                mm = month = 01 - 12
                DD = day = 01 - 31
                HH = hours = 00 - 23
                MM = minutes = 00 - 59
                SS = seconds = 00 - 59
<number of sections>	Binary word representing number of data sections to follow.
<data section>	See data section format.
<crc16>	16 bit CRC of entire file upload after it has been decrypted. High byte/low byte

 FUNCTION PARAMETERS:
        fh
                Value to output.

***********************************************************************
*/
void fsm_OpenFile ( char *deviceModelId, char *deviceSN, char *timeOfSave,
                    unsigned int numSections)
{
#ifndef DSP_2490
    fst_File *pFile;
#endif

    // Initialize File system
    fsm_InitFile();

    fsm_String(v_fileHeader.fileType);
    fsm_String(v_fileHeader.fileVersion);
    fsm_String(v_fileHeader.monitorModelId);
    fsm_EEReadString(v_fileHeader.monitorSerialNumber,coc_EEPROM_SN_SIZE, coc_EEPROM_SN_ADDR);
    fsm_String(v_fileHeader.monitorSerialNumber);
    fsm_String((char*)deviceModelId);
    fsm_String((char*)deviceSN);

    //Save the Index to the File Header Interrogation Timestamp
#ifndef DSP_2490
    pFile                               = fsm_GetFile();
    fsv_FileInterrogationTimeStampIndex = pFile->index;
#else
    fsv_FileInterrogationTimeStampIndex = fsm_PackedBfrGetIndex(FSV_FILE);
#endif

    fsm_String((char*)timeOfSave);
    fsm_DataInteger(numSections);

}

/*
***********************************************************************

 FUNCTION:	fsm_ReplaceFileInterrogationTimeStamp

 DESCRIPTION:
        Replace the timestamp in the File Header.

 FUNCTION PARAMETERS:

  pszTimeStamp
      The Timestamp Used to Replace the File Header Timestamp.

***********************************************************************
*/
bool fsm_ReplaceFileInterrogationTimeStamp(char *pszTimeStamp)
{
    unsigned long ulTempIndex;
    bool          retval = false;
#ifndef DSP_2490
    fst_File *pFile      = fsm_GetFile();
#endif

    //If There Is A Valid Index and a Valid Timestamp String ("YYYYMMDDHHMMSS", Length of 14)
    if ( (fsv_FileInterrogationTimeStampIndex >= 0) &&
         (strlen(pszTimeStamp) == 14) )
    {
#ifndef DSP_2490
        //Save Out the File Index, and Replace with Timestamp Index
        ulTempIndex  = pFile->index;
        pFile->index = fsv_FileInterrogationTimeStampIndex;

        //Overwrite the Timestamp...
        fsm_String(pszTimeStamp);

        //Reset the File Index
        pFile->index = ulTempIndex;
#else
        //Save current the File Index, and Replace with Timestamp Index
        ulTempIndex  = fsm_PackedBfrGetIndex(FSV_FILE);
        fsm_PackedBfrSetIndex(FSV_FILE,fsv_FileInterrogationTimeStampIndex);
        fsm_String(pszTimeStamp);       //Overwrite the Timestamp...
        fsm_PackedBfrSetIndex(FSV_FILE,ulTempIndex);    //Reset the File Index
#endif

        //Set the Successful Return Code
        retval = true;
    }
    return retval;
}

/*
***********************************************************************

 FUNCTION:	fsm_UpdateAssetDataAndCloseFile

 DESCRIPTION:

If this is the first call then
  save where the asset data section info is written to the file,
  retrieve the asset data,
  calculate the CRC of the file and write it to the file,
  finally encrypt the file
Else, it's the second (or more) call then
  decrypt the file,
  reset the file pointer to the original asset data section,
  update the asset data,
  calculate the CRC of the file and write it to the file,
  finally encrypt the file

 FUNCTION PARAMETERS:

***********************************************************************
*/
void fsm_UpdateAssetDataAndCloseFile (void )
{
#ifndef DSP_2490
    if (!assetDataSectionIndexValid)
    {
        //aim_Update_DateTime() should only be called here. The date and times
        //saved during the device interr. need only to be written to the file once.
        //So if we disconnect and redial we do not want to re-determine
        //these date/time values.
        aim_UpdateDateTime();
        assetDataSectionIndex      = fsv_file.index;
        assetDataSectionIndexValid = true;
    }
    else
    {
        // decrypt the file.
        fsm_Decrypt(fsv_file.file, fsv_file.index);

        // reset the file index.
        fsv_file.index = assetDataSectionIndex;
    }

    // Output the Asset Data.
    fsm_AssetData();

    // Calculate the CRC16 of the file and encrypt.
    fsm_FileCRC16();

    fsm_Encrypt(fsv_file.file, fsv_file.index);

#else
    if (!assetDataSectionIndexValid)
    {
        //aim_Update_DateTime() should only be called here. The date and times
        //saved during the device interr. need only to be written to the file once.
        //So if we disconnect and redial we do not want to re-determine
        //these date/time values.
        aim_UpdateDateTime();
        assetDataSectionIndex      = fsm_PackedBfrGetIndex(FSV_FILE);
        assetDataSectionIndexValid = true;
    }
    else
    {
        // decrypt the file.
        fsm_DecryptFile();

        // reset the file index.
        fsm_PackedBfrSetIndex(FSV_FILE,assetDataSectionIndex);
    }

    // Output the Asset Data.
    fsm_AssetData();

    bsm_SDPrint("CRC computation ");

    // Calculate/append the CRC16 of the file and encrypt.
    fsm_FileCRC16();

    // For simulation, don't encrypt then have to and decrypt
#ifndef DSP_2490_SIMULATION
    bsm_SDPrint("and file encryption ");
    fsm_EncryptFile();
    bsm_SDPrint("completed.");
#endif

#endif
}

/*
***********************************************************************

 FUNCTION:	fsm_AssetData

 DESCRIPTION:
Output the <asset data> component of the general file structure posted to the
server.
Asset Data  Content
-------------------
<model id>                  Null Terminated "2490A"
<2490 firmware revision>    The main code Checksum
<serial number>	            Null terminated "8" bytes representing the serial number
                            of the 2490 sending the data
<prefix>	            Null terminated string representing the four possible
                            prefixes " 789"
<country code>		        Null terminated 2 to 3 bytes for modem/DAA country-specific setup
<ISP phone numbers>	    4 Null Terminated strings representing the four
                            possible ISP phone numbers
<ISP auth method>           'PAP' CHAP' or 'SCRIPTED'
<DNS server>                The DNS server.
<total ON time>	            Two binary words representing the total Powered On
                            time in minutes. (never cleared)
< file transfer attempts>        Binary word representing number of file transfer attempts, cleared after data is sent.
< file transfer successes>       Binary word representing number successful file transfers, cleared after data is sent
<network connection attempts>    Binary word representing number network connect attempts, cleared after data is sent.
<network connection successes>   Binary word representing number successful network connections, cleared after data is sent
<interrogation duration>         Binary word representing in seconds the  interrogation duration, cleared after data is sent.
<checksum>                       binary long word
<number log entries>             Binary word representing total number of log entries.
<error / network connection log> Null terminated log strings

 FUNCTION PARAMETERS:

***********************************************************************
*/

void fsm_AssetData ( void)
{
    long          logEntryFileIndex = 0;
    static char   logMessage[bsc_EHMAXLOGENTRY + 1];
    int           errorCode;
    unsigned long errorTime;
#ifdef DSP_2490
    fst_PackedBfrIndex endOfFile;
#endif

    // Write Section Header save index for later updates
    fsm_FileSectionHeader (&fsv_AssetSectionHeader);

    // Write Body of asset data
    fsm_String((char*)v_assetData.monitorModelId);
    sprintf((char*)v_assetData.firmwareRevision,"%08lX",bsm_AppCRCValue());
    fsm_String((char*)v_assetData.firmwareRevision);
    fsm_EEReadString((char*)v_assetData.monitorSerialNumber,coc_EEPROM_SN_SIZE, coc_EEPROM_SN_ADDR);
    fsm_String((char*)v_assetData.monitorSerialNumber);
    bsm_EEReadBuf((unsigned char*)v_assetData.dialPrefix,coc_DIALPREFIX_SIZE, coc_DIALPREFIX_ADDR);
    // pad with null
    v_assetData.dialPrefix[coc_DIALPREFIX_SIZE] = 0;
    fsm_Data(v_assetData.dialPrefix, coc_DIALPREFIX_SIZE+1);

    // Country code - new for 2490G/J/H
    bsm_EEReadBuf((unsigned char*)v_assetData.countryCode,
                  coc_MDMCountryCode_SIZE, coc_MDMCountryCode_ADDR);
    fsm_String((char*)v_assetData.countryCode);


    bsm_EEReadBuf((unsigned char*)v_assetData.phoneNumberOne,coc_ISPPhone1_SIZE, coc_ISPPhone1_ADDR);
    fsm_String((char*)v_assetData.phoneNumberOne);
    bsm_EEReadBuf((unsigned char*)v_assetData.phoneNumberTwo,coc_ISPPhone2_SIZE, coc_ISPPhone2_ADDR);
    fsm_String((char*)v_assetData.phoneNumberTwo);
    bsm_EEReadBuf((unsigned char*)v_assetData.phoneNumberThree,coc_ISPPhone3_SIZE, coc_ISPPhone3_ADDR);
    fsm_String((char*)v_assetData.phoneNumberThree);
    bsm_EEReadBuf((unsigned char*)v_assetData.phoneNumberFour,coc_ISPPhone4_SIZE, coc_ISPPhone4_ADDR);
    fsm_String((char*)v_assetData.phoneNumberFour);

    // ISP Authentication Method and DNS Server new for 2490G/J/H
    bsm_EEReadBuf((unsigned char*)v_assetData.ISPAuthMethod,coc_ISPAuthMethod_SIZE, coc_ISPAuthMethod_ADDR);
    fsm_String((char*)v_assetData.ISPAuthMethod);
    bsm_EEReadBuf((unsigned char*)v_assetData.DNSServer, coc_StaticDNS_SIZE, coc_StaticDNS_ADDR);
    fsm_String((char*)v_assetData.DNSServer);

    v_assetData.totalOnTime          = bsm_ReadTotalOnTimeMinutes();
    fsm_DataLong(v_assetData.totalOnTime);

    v_assetData.fileTransferAttempts = (int)
                                       aim_EEReadUINT16(coc_FileTransferAttempts_ADDR);

    fsm_DataInteger(v_assetData.fileTransferAttempts);

    v_assetData.connectionAttempts = (int)
                                     aim_EEReadUINT16(coc_NetworkConnectionAttempts_ADDR);

    fsm_DataInteger(v_assetData.connectionAttempts);

    v_assetData.interrogationDuration = (int)
                                        aim_EEReadUINT16(coc_LastInterrogateDuration_ADDR);

    fsm_DataInteger(v_assetData.interrogationDuration);

    // Read Log Data
    v_assetData.numberLogEntries = 0;
#ifndef DSP_2490
    logEntryFileIndex            = fsv_file.index;
#else
    logEntryFileIndex            = fsm_PackedBfrGetIndex(FSV_FILE);
#endif
    fsm_DataInteger(v_assetData.numberLogEntries);

    // Reset read ptr to read log from the begining.
    bsm_EHResetLogReadPointer();
    // Save a copy of the write ptr for later use.
    bsm_EHSaveCurrLogWrite();
    // Loop while log entries exist.
    while (bsm_EHReadNextEntry(logMessage, &errorCode, &errorTime)) {
        fsm_StringWithoutNullTermination(logMessage);
        fsm_DataByte(0x0d);     /* Carriage return */
        fsm_DataByte(0x0a);     /* Line feed */
        v_assetData.numberLogEntries++;
    }
    // Update number of log entries in file
#ifndef DSP_2490
    fsv_file.file[logEntryFileIndex]   = (v_assetData.numberLogEntries & 0xff00)>>8;    // high byte
    fsv_file.file[logEntryFileIndex+1] = v_assetData.numberLogEntries & 0x00ff;         // low byte
#else
    endOfFile                          = fsm_PackedBfrGetIndex(FSV_FILE); // Save current EOF

    fsm_PackedBfrWriteAt(FSV_FILE, logEntryFileIndex,(v_assetData.numberLogEntries & 0xff00)>>8);
    fsm_PackedBfrWriteAt(FSV_FILE, logEntryFileIndex+1,v_assetData.numberLogEntries & 0x00ff);

    fsm_PackedBfrSetIndex(FSV_FILE, endOfFile);    // Restore EOF
#endif

    fsm_FileSectionHeaderUpdate(&fsv_AssetSectionHeader);

}

/*
***********************************************************************

 FUNCTION:	fsm_FileSectionHeader

 DESCRIPTION:
Output the <data section header> component of the general file structure posted to the
server.

 FUNCTION PARAMETERS:
        fh
                Value to output.
        index to length for updating

***********************************************************************
*/
void fsm_FileSectionHeader (fst_FileSectionHeader *fh)
{
    fsm_String(fh->type);
    fsm_String(fh->version);

    // Save for updates later
#ifndef DSP_2490
    fh->lengthIndex = fsv_file.index;
    fsm_Data((char*)&fh->length, sizeof(fh->length));
    // Track starting Index to calculate length later in Update call
    fh->startIndex  = fsv_file.index;
#else
    fh->lengthIndex = fsm_PackedBfrGetIndex(FSV_FILE);
    fsm_DataLong(fh->length);

    // Track starting Index to calculate length later in Update call
    fh->startIndex = fsm_PackedBfrGetIndex(FSV_FILE);
#endif
}
/*
***********************************************************************

 FUNCTION:	fsm_FileSectionHeaderUpdate

 DESCRIPTION:
Updates the length of the section header, must be done
after section is written completely
FUNCTION PARAMETERS:
        fh

***********************************************************************
*/
void fsm_FileSectionHeaderUpdate (fst_FileSectionHeader *fh)
{

    // calculate length based on current index and saved index

#ifndef DSP_2490
    fh->length                       = fsv_file.index - fh->startIndex;

    fsv_file.file[fh->lengthIndex]   = (fh->length & 0xff000000)>>24;       // high byte
    fsv_file.file[fh->lengthIndex+1] = (fh->length & 0x00ff0000)>>16;      // low byte
    fsv_file.file[fh->lengthIndex+2] = (fh->length & 0xff00)>>8;   // high byte
    fsv_file.file[fh->lengthIndex+3] =  fh->length & 0x00ff;      // low byte
#else
    // Save current position
    long currIndex = fsm_PackedBfrGetIndex(FSV_FILE);

    fh->length = currIndex - fh->startIndex;

    fsm_PackedBfrSetIndex(FSV_FILE,fh->lengthIndex);
    fsm_DataLong(fh->length);

    // Restore current position
    fsm_PackedBfrSetIndex(FSV_FILE,currIndex);

#endif

}

/*
***********************************************************************

 FUNCTION:   fsm_FileCheckSum

 DESCRIPTION:
 This function generates the <check sum byte 1> and <check sum byte 2>.
 The format of both these data objects is a binary byte.

 <check sum byte 1> - the exclusive-or of all bytes stored in the file
                      not including <check sum byte 1>

 <check sum byte 2> - the exclusive-or of <check sum byte 1> with 0xFF

 This function generates the 2 byte check sum.

 FUNCTION PARAMETERS:

***********************************************************************
*/
void fsm_FileCheckSum (long startIndex)
{
    long          i;
    long          endIndex;
    unsigned char checksumByte1;

#ifndef DSP_2490
    // Calculate the <check sum byte 1>
    endIndex      = fsv_file.index;
    checksumByte1 = fsv_file.file[startIndex];
    for (i = (startIndex + 1); i < endIndex; i++)
    {
        checksumByte1 ^= fsv_file.file[i];
    }
    fsv_file.file[fsv_file.index] = checksumByte1;
    INCR_FILE_INDEX();

    // Calculate the <check sum byte 2>
    fsv_file.file[fsv_file.index] = checksumByte1 ^ 0xFF;
    INCR_FILE_INDEX();
#else
    endIndex                      = fsm_PackedBfrGetIndex(FSV_FILE);
    fsm_PackedBfrSetIndex(FSV_FILE,startIndex);

    for(checksumByte1 = 0, i = startIndex; i < endIndex; i++)
    {
        checksumByte1 ^= fsm_PackedBfrRead(FSV_FILE);
    }
    fsm_PackedBfrWrite(FSV_FILE,checksumByte1);
    fsm_PackedBfrWrite(FSV_FILE,checksumByte1 ^ 0xFF);
#endif

}

/*
***********************************************************************

 FUNCTION:   fsm_FileCRC16

 DESCRIPTION:
This function generates the 2 byte CRC-16.

 FUNCTION PARAMETERS:

***********************************************************************
*/
void fsm_FileCRC16 (void)
{
    unsigned int crc16;


    // Calculate the CRC16
#ifndef DSP_2490
    crc16 = aim_CRC(fsv_file.file, fsv_file.index);
#else
    long x;
    long currIndex = fsm_PackedBfrGetIndex(FSV_FILE); // Save current index
    crc16 = 0;

    fsm_PackedBfrSetIndex(FSV_FILE,0);
    for (x = 0; x < currIndex; x++)
        crc16 = aim_CRCPerByte (crc16, fsm_PackedBfrRead(FSV_FILE));

    fsm_PackedBfrSetIndex(FSV_FILE,currIndex); // Set index back to original position
#endif

    fsm_DataInteger (crc16);

}


/*
**********************************************************************

 FUNCTION:	fsm_UpdateFileIndex

 DESCRIPTION:
Updates the file index.  Checks if file size has been exceeded and
logs and halts if necessary.

FUNCTION PARAMETERS:
        updateValue
            The number of bytes to add to the current file index value.
            This value could be negative to remove "padding".
***********************************************************************
*/

void fsm_UpdateFileIndex(long updateValue)
{
#ifndef DSP_2490
    if (((fsv_file.index + updateValue) >= FSC_MAX_FILE_SIZE) ||
        ((fsv_file.index + updateValue) < 0))
        bsm_EHLock("FSM - Exceeded file size.");
    else
        fsv_file.index += updateValue;
#else
    fsm_PackedBfrSetIndex(FSV_FILE, fsm_PackedBfrGetIndex(FSV_FILE) + updateValue);
#endif
}


