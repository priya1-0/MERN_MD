/*
************************************************************************
 2490 In-home Remote Monitor
 Copyright (c) Medtronic, Inc. 2002

 MODULE: Application File System Module Routines.

 OWNER: Medtronic

 $Revision$

 $Date$

 $RCSfile$

 FUNCTIONS:
      --Public--
void fsm_OpenMemoryDumpFileSection(unsigned char familyID, unsigned char modelID)
void fsm_CloseMemoryDumpFileSection(void)
void fsm_WriteMemoryDumpFileSection(char *paBuffer,
                                    unsigned short usPagesToUplink,
                                    char bSegment,
                                    char bPage,
                                    char bOffset)
bool fsm_ReplaceMemoryDumpFileTimeStamp(char *pszTimeStamp)

void fsm_OpenKappaWaveformFileSection(char *pszDeviceModelID,
                                      char *pszDeviceSerialNumber,
                                      char bEGMCollectionType)
void fsm_CloseKappaWaveformFileSection(void)
void fsm_WriteKappaWaveformFileSection(char bEGMAttribute,
                                       unsigned int unDataLength,
                                       unsigned int unBufferLength,
                                       unsigned int unBufferStartIndex,
                                       char *paBuffer)
bool fsm_ReplaceKappaWaveformFileTimeStamp(char *pszTimeStamp)

                --Private--

 DESCRIPTION:
This module contains the routines used to manage the following sections of the RAM file
for Kappa Devices:
     - Memory Dump (Brady Format [Equivalent to Tachy Save To Disk])
     - Presenting Waveform Data

Data Section Header Content
---------------------------
<section type>	Null Terminated String ("1"=asset, "2"= save-to-disk, "3"=EPR, "4"=waveforms
<version>	Null Terminated version of this section "2.0"
<length>	32bit Binary word representing length
<data content>	See Asset Content, Save-To-Disk Content and Presenting Waveform Content.


Device Save To Disk (Memory Dump)
---------------------------------
For each supported device interrogated, the Remote Monitor shall
create the data section specified in each device's specific
Software Requirements Specification.


Presenting Waveforms/Marker Data Content
----------------------------------------
<2490 model id>	                      Null Terminated String ("2490H")
<2490 firmware revision>              Null Terminated String ("2.0")
<2490 serial number>                  NUll Terminated String (Serial Number of 2490)
<model>	                              Null Terminated String (Device Model ID, ex. "KDR700")
<serial number>	                      NUll Terminated String (Serial Number of Device)
<device time of waveform collection>  Null Terminated String (Date/Time Waveform Collection Intiated
                                      YYYY = year = 0000 - 9999
                                      mm = month = 01 - 12
                                      DD = day = 01 - 31
                                      HH = hours = 00 - 23
                                      MM = minutes = 00 - 59
                                      SS = seconds = 00 - 59
<number of egm strips>                Binary Byte (0x03)
<egm collection type>                 Binary Byte (Mode/Gain Byte, See Product Specification for Details)
<egm attribute>                       Null Terminated String ("MAGNET" or "NON-MAGNET", Describes Collection Mode)
<number of bytes>                     Length of Data [to Follow]
<data samples>                        Data
<egm attribute>                       Null Terminated String ("MAGNET" or "NON-MAGNET", Describes Collection Mode)
<number of bytes>                     Length of Data [to Follow]
<data samples>                        Data


 GLOBAL MODULE DATA:

 STATIC MODULE DATA:

 ENDPURPOSE

************************************************************************
*/
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "fsm_file.h"
#include "fsm_kappa.h"
#include "com_eepromapp.h"
#include "aim_kappa.h"

#ifdef DSP_2490

#include "fsm_pbfr.h"

#endif


// Defined as an extern here because it is decided at compile time
// by the specific project/application file as to the contents.
extern char* fsc_p_InstrumentModelIDString;

long fsv_WaveformSectionTimeStampIndex      = -1;
long fsv_WaveformSectionNumberOfStripsIndex = -1;
long fsv_MemoryDumpSectionTimeStampIndex    = -1;

/*
***********************************************************************

 FUNCTION:	fsm_OpenMemoryDumpFileSection

 DESCRIPTION:
Output the file section header for the Memory Dump section.
Output the <memory dump header> component of the Memory Dump file.

 FUNCTION PARAMETERS:
   familyID
      Family ID for Device Being Interrogated
   modelID
      Model ID for Device Being Interrogated

***********************************************************************
*/
void fsm_OpenMemoryDumpFileSection ( unsigned char familyID, unsigned char modelID )
{
    char     pszRMSerialNumber[coc_EEPROM_SN_SIZE + 1];
    char     pszChecksum[9];
    fst_File *pFile;

    // Write Section Header save index for later updates
    fsm_FileSectionHeader (&fsv_SaveToDiskSectionHeader);

    // Write Header
    fsm_StringWithoutNullTermination("\"VERSION\",\"9953ABv4.0.1\"\n");
    fsm_StringWithoutNullTermination("// Family Id ");
    fsm_HexByte(familyID);
    fsm_StringWithoutNullTermination("  Model Id ");
    fsm_HexByte(modelID);
    fsm_StringWithoutNullTermination("\n");

    fsm_StringWithoutNullTermination("// Instrument Model ID 2490H  Instrument Firmware Revision ");
    sprintf(pszChecksum, "%08lX", bsm_AppCRCValue());
    fsm_StringWithoutNullTermination(pszChecksum);
    fsm_StringWithoutNullTermination("\n");

    fsm_StringWithoutNullTermination("// Instrument Serial Number ");
    fsm_EEReadString(pszRMSerialNumber, coc_EEPROM_SN_SIZE, coc_EEPROM_SN_ADDR);
    pszRMSerialNumber[coc_EEPROM_SN_SIZE] = 0x00;
    fsm_StringWithoutNullTermination(pszRMSerialNumber);
    fsm_StringWithoutNullTermination("  Timestamp ");

    //Retrieve the Timestamp Index
#ifndef DSP_2490
    pFile                               = fsm_GetFile();
    fsv_MemoryDumpSectionTimeStampIndex = pFile->index;
#else
    fsv_MemoryDumpSectionTimeStampIndex = fsm_PackedBfrGetIndex(FSV_FILE);
#endif

    //Continue Writing the Header
    fsm_StringWithoutNullTermination("XXXXXXXXXXXXXX");
    fsm_StringWithoutNullTermination("\n");
}

/*
***********************************************************************

 FUNCTION:	fsm_CloseMemoryDumpFileSection

 DESCRIPTION:
Close the memory dump file section.

 FUNCTION PARAMETERS:


***********************************************************************
*/
void fsm_CloseMemoryDumpFileSection (void)
{
    // Update the Final Length of the File Section
    fsm_FileSectionHeaderUpdate (&fsv_SaveToDiskSectionHeader);
}


/*
***********************************************************************

 FUNCTION:   fsm_WriteMemoryDumpFileSection

 DESCRIPTION:
   Outputs an internal header followed by a set of hexadecimal data bytes.

 FUNCTION PARAMETERS:
   paBuffer
      Pointer to the data
   usPagesToUplink
      Number of Page Retrieved
   bSegment
      Segment Number
   bPage
      Beginning Page Number
   bOffset
      Beginning Offset Into the First Page

***********************************************************************
*/
void fsm_WriteMemoryDumpFileSection (char           *paBuffer,
                                     unsigned short usPagesToUplink,
                                     char           bSegment,
                                     char           bPage,
                                     char           bOffset)
{
    unsigned char  dataCounter;
    unsigned short pageCounter;
    unsigned char  offset;
    char           *tempPointer;
    char           tempHeader[33];    // 32 Is the Maximum Header Length ( + NULL = 33 Bytes )

    // Set the Temporary Pointer to the Start of Data
    tempPointer = paBuffer;

    // For Each Page, Write Out a Header Followed By the Associated Data
    for (pageCounter = (unsigned short)bPage; pageCounter < ((unsigned short)bPage + usPagesToUplink); pageCounter++)
    {
        if (pageCounter == (unsigned short)bPage)
        {
            //Set the Initial Offset
            offset = bOffset;
        }
        else
        {
            //Rest the Offset to Zero (To Get the Entire Page)
            offset = 0;
        }

        // Write the Page Header
        sprintf(tempHeader, "segment %d  page %d  offset %d\n", bSegment, pageCounter, offset);
        fsm_StringWithoutNullTermination(tempHeader);

        // Write the Data
        for (dataCounter = offset; dataCounter < (unsigned char)(KAPPA_MEMORY_PAGE_SIZE); dataCounter++)
        {
            fsm_HexByte((unsigned char)*tempPointer);
            fsm_StringWithoutNullTermination("\n");
            tempPointer++;
        }

        // Skip Over the Parity Byte
        tempPointer++;

        //Add a New Line Character To Finish the Page Block
        fsm_StringWithoutNullTermination("\n");
    }
}


/*
***********************************************************************

 FUNCTION:	fsm_ReplaceMemoryDumpFileTimeStamp

 DESCRIPTION:
        Replace the timestamp in the Memory Dump Section Internal Header.

 FUNCTION PARAMETERS:

  pszTimeStamp
      The Timestamp Used to Replace the Current Memory Dump Timestamp.

***********************************************************************
*/
bool fsm_ReplaceMemoryDumpFileTimeStamp(char *pszTimeStamp)
{
    unsigned long ulTempIndex;
    bool          retval = false;

#ifndef DSP_2490
    fst_File *pFile      = fsm_GetFile();
#endif

    //If There Is A Valid Index and a Valid Timestamp String ("YYYYMMDDHHMMSS", Length of 14)
    if ( (fsv_MemoryDumpSectionTimeStampIndex >= 0) &&
         (strlen(pszTimeStamp) == 14) )
    {
        //Save Out the File Index, and Replace with Timestamp Index

#ifndef DSP_2490
        ulTempIndex  = pFile->index;
        pFile->index = fsv_MemoryDumpSectionTimeStampIndex;
#else
        ulTempIndex  = fsm_PackedBfrGetIndex(FSV_FILE);
        fsm_PackedBfrSetIndex(FSV_FILE,fsv_MemoryDumpSectionTimeStampIndex);
#endif

        //Overwrite the Timestamp...
        fsm_StringWithoutNullTermination(pszTimeStamp);

        //Manually Overwrite the NULL to Add the Line Feed Character

#ifndef DSP_2490
        pFile->file[pFile->index] = '\n';
#else
        fsm_PackedBfrWrite(FSV_FILE,'\n');
#endif

        //Reset the File Index

#ifndef DSP_2490
        pFile->index = ulTempIndex;
#else
        fsm_PackedBfrSetIndex(FSV_FILE,ulTempIndex);
#endif

        //Set the Successful Return Code
        retval = true;
    }
    return retval;
}


/*
***********************************************************************

 FUNCTION:	fsm_OpenKappaWaveformFileSection

 DESCRIPTION:
Output the <waveform header> component of the disk file.

 FUNCTION PARAMETERS:
    pszDeviceModelId
      Device Model ID
    pszDeviceSerialNumber
      Device Serial Number
    bEGMCollectionType
      Mode/Gain Byte

***********************************************************************
*/
void fsm_OpenKappaWaveformFileSection(char *pszDeviceModelID,
                                      char *pszDeviceSerialNumber,
                                      char bEGMCollectionType)
{
    char pszRMSerialNumber[coc_EEPROM_SN_SIZE + 1];
    char pszChecksum[9];

#ifndef DSP_2490
    fst_File *pFile;
#endif

    // Write Section Header save index for later updates
    fsm_FileSectionHeader (&fsv_WaveformSectionHeader);

    // Write Header
    fsm_String(fsc_p_InstrumentModelIDString);
    sprintf(pszChecksum, "%08lX", bsm_AppCRCValue());
    fsm_String(pszChecksum);
    fsm_EEReadString(pszRMSerialNumber, coc_EEPROM_SN_SIZE, coc_EEPROM_SN_ADDR);
    pszRMSerialNumber[coc_EEPROM_SN_SIZE] = 0x00;
    fsm_String(pszRMSerialNumber);
    fsm_String(pszDeviceModelID);
    fsm_String(pszDeviceSerialNumber);

    //Retrieve the Timestamp Index

#ifndef DSP_2490
    pFile                             = fsm_GetFile();
    fsv_WaveformSectionTimeStampIndex = pFile->index;
#else
    fsv_WaveformSectionTimeStampIndex = fsm_PackedBfrGetIndex(FSV_FILE);
#endif

    //Continue Writing the Header
    fsm_String("XXXXXXXXXXXXXX");

    //Retrieve the Number Of Strips Index

#ifndef DSP_2490
    fsv_WaveformSectionNumberOfStripsIndex = pFile->index;
#else
    fsv_WaveformSectionNumberOfStripsIndex = fsm_PackedBfrGetIndex(FSV_FILE);
#endif

    fsm_DataByte(0x00);


     // Set analog telemetry type for single chamber device only
    if(!aim_KappaIsDual())
    {
        fsm_DataByte(bEGMCollectionType);
    }

}

/*
***********************************************************************

 FUNCTION:	fsm_CloseKappaWaveformFileSection

 DESCRIPTION:
        Close the waveform Section of the File.

 FUNCTION PARAMETERS:

***********************************************************************
*/
void fsm_CloseKappaWaveformFileSection(void)
{
    // Update the Final Length of the File Section
    fsm_FileSectionHeaderUpdate (&fsv_WaveformSectionHeader);
}

/*
***********************************************************************

 FUNCTION:	fsm_WriteKappaWaveformFileSection

 DESCRIPTION:
Output Waveform Data to the Disk File.

 FUNCTION PARAMETERS:
        bEGMAttribute
            Attribute Describing Collection Mode
        unDataLength
            Legnth of Data to Write
        unBufferLength
            Length of Circular Buffer
        unBufferStartIndex
            Starting Index in a Circular Buffer
        paBuffer
            Pointer to Circular Buffer Containing Data
        bEGMCollectionType
            Mode/Gain Byte

***********************************************************************
*/
void fsm_WriteKappaWaveformFileSection(char         bEGMAttribute,
                                       unsigned int unDataLength,
                                       unsigned int unBufferLength,
                                       unsigned int unBufferStartIndex,
                                       char         telemType,
                                       char         *paBuffer,
                                       char bEGMCollectionType)
{
    unsigned int       unCurrentLength;
    fst_PackedBfrIndex tempPBfrIndex;

#ifndef DSP_2490
    unsigned long ulTempIndex;
    fst_File      *pFile;
#else
    char aByte;
#endif
    // Set analog telemetry type for Dual Chamber device only
    if(aim_KappaIsDual())
    {
        fsm_DataByte(bEGMCollectionType);
    }

    //If There Is A Valid Number Of Strips Index
    if ( fsv_WaveformSectionNumberOfStripsIndex >= 0 )
    {
        //Save Out the File Index, and Replace with Timestamp Index

#ifndef DSP_2490
        pFile        = fsm_GetFile();
        ulTempIndex  = pFile->index;
        pFile->index = fsv_WaveformSectionNumberOfStripsIndex;

        //Increment the Number Of Strips...
        ((char)(pFile->file[pFile->index]))++;

        //Reset the File Index
        pFile->index  = ulTempIndex;

#else
        tempPBfrIndex = fsm_PackedBfrGetIndex(FSV_FILE);
        aByte         = fsm_PackedBfrReadAt(FSV_FILE,fsv_WaveformSectionNumberOfStripsIndex);
        aByte++;
        fsm_PackedBfrWriteAt(FSV_FILE,fsv_WaveformSectionNumberOfStripsIndex, aByte);
        fsm_PackedBfrSetIndex(FSV_FILE, tempPBfrIndex);

#endif

        // Write Internal Header Information (EGM attribute)
        if( bEGMAttribute == KAPPA_WAVEFORM_MAGNET_MODE )
        {
            if(aim_KappaIsDual())
            {
                if (telemType == AIC_ATRIAL_EGM_MODE)
                {
                    fsm_String("MAGNET-AEGM");
                }
                else if (telemType == AIC_VENTRI_EGM_MODE)
                {
                    fsm_String("MAGNET-VEGM");
                }
                else if (telemType == AIC_SUMMED_EGM_MODE)
                {
                   fsm_String("MAGNET-SEGM");
                }
             }
             else
             {
                 fsm_String("MAGNET");
             }
        }
        else if( bEGMAttribute == KAPPA_WAVEFORM_NONMAGNET_MODE )
        {
            if(aim_KappaIsDual())
            {
                if (telemType == AIC_ATRIAL_EGM_MODE)
                {
                    fsm_String("NON-MAGNET-AEGM");
                }
                else if (telemType == AIC_VENTRI_EGM_MODE)
                {
                    fsm_String("NON-MAGNET-VEGM");
                }
                else if (telemType == AIC_SUMMED_EGM_MODE)
                {
                   fsm_String("NON-MAGNET-SEGM");
                }
            }
            else
            {
               fsm_String("NON-MAGNET");
            }
        }
        //Number of bytes
        fsm_DataInteger(unDataLength);

        // Write Data Fromk Circular Buffer
        if( unBufferStartIndex + unDataLength <= unBufferLength )
        {
            fsm_Data(&paBuffer[unBufferStartIndex], unDataLength);
        }
        else
        {
            unCurrentLength = unBufferLength - unBufferStartIndex;
            fsm_Data(&paBuffer[unBufferStartIndex], unCurrentLength);
            unCurrentLength = unDataLength - unCurrentLength;
            fsm_Data(paBuffer, unCurrentLength);
        }
    }
}

/*
***********************************************************************

 FUNCTION:	fsm_ReplaceKappaWaveformFileTimeStamp

 DESCRIPTION:
        Replace the timestamp in the Waveform Section Internal Header.

 FUNCTION PARAMETERS:

  pszTimeStamp
      The Timestamp Used to Replace the Current waveform Timestamp.

***********************************************************************
*/
bool fsm_ReplaceKappaWaveformFileTimeStamp(char *pszTimeStamp)
{
    unsigned long ulTempIndex;
    bool          retval = false;

#ifndef DSP_2490
    fst_File *pFile      = fsm_GetFile();
#endif

    //If There Is A Valid Index and a Valid Timestamp String ("YYYYMMDDHHMMSS", Length of 14)
    if ( (fsv_WaveformSectionTimeStampIndex >= 0) &&
         (strlen(pszTimeStamp) == 14) )
    {
        //Save Out the File Index, and Replace with Timestamp Index

#ifndef DSP_2490
        pFile->index = fsv_WaveformSectionTimeStampIndex;
        ulTempIndex  = pFile->index;
#else
        ulTempIndex  = fsm_PackedBfrGetIndex(FSV_FILE);
        fsm_PackedBfrSetIndex(FSV_FILE, fsv_WaveformSectionTimeStampIndex);
#endif
        //Overwrite the Timestamp...
        fsm_String(pszTimeStamp);

        //Reset the File Index
#ifndef DSP_2490
        pFile->index = ulTempIndex;
#else
        fsm_PackedBfrSetIndex(FSV_FILE,ulTempIndex);
#endif

        //Set the Successful Return Code
        retval = true;
    }
    return retval;
}
