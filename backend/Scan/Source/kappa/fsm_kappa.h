/*
************************************************************************
 2490 In-Home Remote Monitor
 Copyright (c) Medtronic, Inc. 2002

 MODULE: Application File Module Routines

 OWNER: Medtronic

 $Revision$

 $Date$

 $RCSfile$

 DESCRIPTION:
Function prototypes and constants for file saving including "Save to Disk" routines.
This module defines the typedef structures which hold the data used for "Save to
Disk". These typedef structure hold the binary values of the actual data written to
the file.

 GLOBAL MODULE DATA:

 STATIC MODULE DATA:

 ENDPURPOSE

************************************************************************
*/

#ifndef fsm_kappa_h
#define fsm_kappa_h

#include "types.h"
#include "fsm_file.h"
#include "aim_kappa.h"

// The Memory Dump format is defined in the device
// programmer application SRS.
typedef struct
{
    char bFamilyID;
    char bModelID;
} fst_MemoryDumpFileHeader;

// The waveform file format is defined in the 2490D SRS.
// The actual waveform data follows this header in the file.
typedef struct
{
    char pszIntrumentModelId[9];
    char pszInstrumentRevision[8];
    char pszInstrumentSerialNumber[16];
    char pszDeviceModelId[8];
    char pszDeviceSerialNumber[12];
    char pszTimeOfWaveformCollection[30];
    char bNumberOfEGMStrips;
    char bEGMCollectionType;
    //Note: For Each Collected Strip, two other values are written
    //indicating: the EGM Attribute, and Number Of Bytes for the
    //given strip data.
} fst_WaveformFileHeader;

void fsm_OpenMemoryDumpFileSection(unsigned char familyID, unsigned char modelID);
void fsm_CloseMemoryDumpFileSection(void);
void fsm_WriteMemoryDumpFileSection(char           *pabBuffer,
                                    unsigned short usPagesToUplink,
                                    char           bSegment,
                                    char           bPage,
                                    char           bOffset);
bool fsm_ReplaceMemoryDumpFileTimeStamp(char *pszTimeStamp);

#define KAPPA_MEMORY_PAGE_SIZE 32

void fsm_OpenKappaWaveformFileSection(char *pszDeviceModelID,
                                      char *pszDeviceSerialNumber,
                                      char bEGMCollectionType);
void fsm_CloseKappaWaveformFileSection(void);

#define KAPPA_WAVEFORM_MAGNET_MODE    0x04
#define KAPPA_WAVEFORM_NONMAGNET_MODE 0x03

void fsm_WriteKappaWaveformFileSection(char         bEGMAttribute,
                                       unsigned int unDataLength,
                                       unsigned int unBufferLength,
                                       unsigned int unBufferStartIndex,
                                       char         telemType,
                                       char         *paBuffer,
                                       char         bEGMCollectionType);
bool fsm_ReplaceKappaWaveformFileTimeStamp(char *pszTimeStamp);

#endif
