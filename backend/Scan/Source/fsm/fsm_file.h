/*
************************************************************************
 2490 In-home Remote Monitor
 Copyright (c) Medtronic, Inc. 2001

 MODULE: Application File Module  routines.

 OWNER: Medtronic

 $Revision$

 $Date$

 $RCSfile$

 DESCRIPTION:
Function prototype for file saving including "Save to Disk" routines.
This module defines the typedef structures which hold the data used for "Save to
Disk". These typedef structure hold the binary values of the actual data written to
the file. For example, the physicalAddress field of the ait_address typedef structure
will have the binary value of the address where as the "Save to Disk" file
will be written with the ASCII representation of this value. So if
physicalAddress = 0x80 the file will be written with "0x31 0x32 0x38 0x0a" or
"128<LF>" where 0x0a is a line feed. There are routines defined elsewhere
which take these structures as input parameters and output the data it as
defined in the SRS defined "Save to Disk" format.

Generally a "Save to Disk" file consists of the data from a number of data groups.
Some data groups (<parameter data>, <patient data>, <clock data>, etc)
are contiguous blocks of data that are read in their entirety during each
interrogation. Other data groups (<patient alert log data >, <vt/vf log data>,
<episode data>, etc.) are called device logs which are large circular buffers
of data which overwrite themselves.

 GLOBAL MODULE DATA:

 STATIC MODULE DATA:

 ENDPURPOSE

************************************************************************
*/

#ifndef fsm_file_h
#define fsm_file_h

#include "types.h"
#include "com_eepromapp.h"


typedef struct
{
    long index;
    char *file;
}  fst_File;

#define FSC_MONITOR_MODEL_ID_SIZE 8

// The file header is described in the 2490A srs.
typedef struct
{
    char fileType[5];
    char fileVersion[8];
    char monitorModelId[FSC_MONITOR_MODEL_ID_SIZE + 1];
    char monitorSerialNumber[coc_EEPROM_SN_SIZE + 1];
    char deviceModelId[8];
    char deviceSerialNumber[coc_LastSerial_SIZE+1];
    char timeOfSave[30];
    int numSections;
} fst_FileHeader;

// The file section header is defined in the 2490A srs.
typedef struct
{
    char type[5];
    char version[8];
    long length;
    long lengthIndex;
    long startIndex;
} fst_FileSectionHeader;

// This length is defined here because the fw revision is
// used in several areas (fsm_WriteWaveform....) so if the length
// is changed the affected areas will be udpated.
#define FSC_ASSET_DATA_FW_REVISION_LENGTH    9
#define FSC_ASSET_DATA_MONITOR_SERIAL_NUMBER 16

// The Asset Data Section is defined in the 2490A srs.
typedef struct
{
    char monitorModelId[FSC_MONITOR_MODEL_ID_SIZE + 1];
    char firmwareRevision[FSC_ASSET_DATA_FW_REVISION_LENGTH];
    char monitorSerialNumber[FSC_ASSET_DATA_MONITOR_SERIAL_NUMBER];
    char dialPrefix[coc_DIALPREFIX_SIZE + 1];
    char countryCode[coc_MDMCountryCode_SIZE + 1];
    char phoneNumberOne  [coc_ISPPhone1_SIZE + 1];
    char phoneNumberTwo  [coc_ISPPhone2_SIZE + 1];
    char phoneNumberThree[coc_ISPPhone3_SIZE + 1];
    char phoneNumberFour [coc_ISPPhone4_SIZE + 1];
    char ISPAuthMethod[coc_ISPAuthMethod_SIZE + 1];
    char DNSServer[coc_StaticDNS_SIZE + 1];
    unsigned long totalOnTime;
    unsigned int fileTransferAttempts;
    unsigned int connectionAttempts;
    int interrogationDuration;
    int numberLogEntries;
    // Determine how to write log entries
} fst_AssetDataSection;

extern fst_FileSectionHeader fsv_AssetSectionHeader;
extern fst_FileSectionHeader fsv_SaveToDiskSectionHeader;
extern fst_FileSectionHeader fsv_WaveformSectionHeader;
extern fst_FileSectionHeader fsv_EPRSectionHeader;
extern fst_FileHeader        fsv_fileHeader;

void fsm_InitFile(void);
fst_File* fsm_GetFile(void);
void fsm_NumberByte (unsigned char aByte);
void fsm_NumberInteger (unsigned int anInteger);
void fsm_NumberLong (unsigned long aLong);
void fsm_HexByte (unsigned char aByte);
void fsm_DataByte (char aByte);
void fsm_DataInteger (int anInteger);
void fsm_Data (char *p_src, unsigned long length);
void fsm_String (char *aString);
void fsm_StringWithoutNullTermination (char *aString);
void fsm_EEReadString (char *string, unsigned int size, unsigned int address);
void fsm_OpenFile (char *deviceModelId,  char *deviceSN, char *timeOfSave, unsigned int numSections);
bool fsm_ReplaceFileInterrogationTimeStamp(char *pszTimeStamp);
void fsm_DeleteFile(void);
void fsm_UpdateAssetDataAndCloseFile (void);
void fsm_SetAssetInterrogationTime (void);
void fsm_FileCRC16(void);
void fsm_UpdateFileIndex(long updateValue);
void fsm_AssetData ( void);
void fsm_FileSectionHeaderUpdate( fst_FileSectionHeader *fh);
void fsm_FileSectionHeader (fst_FileSectionHeader *fh);
void fsm_FileCheckSum(long startIndex);
void fsm_SetInstrumentModelID(char *modelIDString);
char *fsm_GetInstrumentModelID(void);

// These are macro/functions used to verify we do not exceed the allowable file size.
#define INCR_FILE_INDEX()    fsm_UpdateFileIndex(1)
#define ADD_TO_FILE_INDEX(a) fsm_UpdateFileIndex(a)


// Include this file to pull in CRC prototypes
#include "bsm_AppCrc.h"

#endif
