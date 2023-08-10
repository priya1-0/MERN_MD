/*
************************************************************************
 2490 In-home Remote Monitor
 Copyright (c) Medtronic, Inc. 2001

 MODULE: Application Interrogation Module for the Kappa Family.

 OWNER: Medtronic

 $Revision$

 $Date$

 $RCSfile$

 DESCRIPTION:
This module contains the interfaces for high level code for interrogating a device. The
main objective of a Remote Monitor interrogation is to create a "Save to
Disk" file very similar to that created by a programmer. For more
information about the content and format of this file see the "Save to Disk"
section of the device specific SRS.

 GLOBAL MODULE DATA:

 STATIC MODULE DATA:

 ENDPURPOSE

************************************************************************
*/

#ifndef aim_kappa_h
#define aim_kappa_h

#include "types.h"

#define AIC_NULL_DEVICE_ID 0x00

//UPLINK/DOWNLINK
#define AIC_KAPPA_HEADER                 2
#define AIC_KAPPA_MAX_DOWNLINK_SIZE      46
#define AIC_KAPPA_MAX_DL_PRE_PARITY_SIZE 34
#define AIC_KAPPA_UPLINK_PAGE_SIZE       33
#define AIC_KAPPA_PAGES_PER_UPLINK       8
#define AIC_KAPPA_MAX_UPLINK_SIZE        (AIC_KAPPA_PAGES_PER_UPLINK * AIC_KAPPA_UPLINK_PAGE_SIZE + AIC_KAPPA_HEADER)
#define AIC_ACK_UPLINK_SIZE              3
#define AIC_ONE_PAGE_UPLINK_SIZE         35
#define AIC_COMPLETE_SN_MAX_SIZE         14
#define AIC_NUMBER_OF_SECTIONS           3

//DATA VALID STATUS BIT
#define AIC_DATA_VALID_SEGMENT 0x01
#define AIC_DATA_VALID_PAGE    0x0C
#define AIC_DATA_VALID_OFFSET  0x02
#define AIC_DATA_VALID_MASK    0xEF

//MODE encode/decode values
#define AIC_ATRIAL_EGM_MODE 0x00
#define AIC_VENTRI_EGM_MODE 0x01
#define AIC_SUMMED_EGM_MODE 0x03
#define AIC_MAGNET_MODE_ON  0x04
#define AIC_MAGNET_MODE_OFF 0x03
#define AIC_DONT_CARE_MODE  0x99 // EGM mode don't care used for single chamber magnet mode and non-magnet mode
#define AIC_AEGM_GAIN       0x60
#define AIC_VEGM_GAIN       0x20
#define AIC_SEGM_GAIN       0x60

//ACK
#define AIC_PROCESSACK        true
#define AIC_DO_NOT_PROCESSACK false
#define AIC_ACK               0x81

//RTT encode/decode values for parameters
#define AIC_AV_BIPOLAR_MANUAL    0x00
#define AIC_A_UNIPOLAR_MANUAL    0x01
#define AIC_V_UNIPOLAR_MANUAL    0x10
#define AIC_A_AUTOPACE           0x02
#define AIC_V_AUTOPACE           0x20
#define AIC_AMPLITUDE_FIVE_VOLTS 0x19

#define AIC_RTT_TIMEOUT                600 //6 seconds for handshake only. Used to be 8 seconds.
#define AIC_KAPPA_RRT_PAGES_PER_UPLINK 1
#define AIC_RTT_DOWNLINK_SIZE          32

// EGM WAVEFORM COLLECTION
/*780=(390Hz*2(type,value)), 30=seconds*/
#define AIC_A_KAPPA_EGM_BYTES_PER_SECOND       780
#define AIC_KAPPA_SINGLE_EGM_SECONDS                  30
#define AIC_KAPPA_DUAL_EGM_SECONDS           7 //Period of collection for AtrialEGM, Ventricular EGM and summed EGM individually
// Number of bytes need to be collected waveform for single chamber device
#define AIC_KAPPA_EXPECTED_SINGLE_NUMBER_OF_EGM_BYTES (AIC_A_KAPPA_EGM_BYTES_PER_SECOND * AIC_KAPPA_SINGLE_EGM_SECONDS)


// Forece the system to have two seconds of waveform collection before attempting
// another RTT test
#define AIC_ESTABLISH_SOLID_LINK_TIME 2

#define AIC_LED1 0
#define AIC_LED2 1
#define AIC_LED3 2
#define AIC_LED4 3
#define AIC_LED5 4
#define AIC_LED6 5

//SERIAL NUMBER
#define AIC_KAPPA_SIZE_OF_SERIAL_NUMBER 6

//family device IDs
#define AIC_DEVICE_MODEL_KAPPA700 0x00000003L /*Telemetry A */
#define AIC_DEVICE_MODEL_KAPPA900 0x00000011L /*Telemetry A */
#define AIC_DEVICE_MODEL_ENPULSE  0x00000012L
#define AIC_DEVICE_MODEL_E3       0x00000013L
#define AIC_DEVICE_MODEL_PHOENIX  0x00000018L
#define AIC_DEVICE_MODEL_PHOENIX_VITATRON  0x00000019L

//subfamily IDs
#define AIC_KDR700_SUBFAMILY_ID 0x00000001L
#define AIC_KDR720_SUBFAMILY_ID 0x00000101L

#define AIC_ID_2020C "LPI"

extern void aim_KDR700PreInterrogate(void);
extern void aim_KDR700Interrogate(void);
extern void aim_KDR900PreInterrogate(void);
extern void aim_KDR900Interrogate(void);

typedef struct
{
    char *deviceString;
    char *chambered;
    char *serialNumber;
    char bConnectorId;
    char subModel;
    unsigned long deviceId;
} ait_KappaSpecificDeviceTableEntry;

typedef struct
{
    unsigned long deviceId;
    void (*preInterrogate)(void);
    void (*interrogate)(void);
    bool autoIdEnable;
} ait_KappaDeviceTableEntry;

typedef  struct
{
    int segment;
    int firstPage;
    int numPages;
    int offset;
    unsigned int size;
    char *data;
} ait_KappaDeviceMemoryRange;

//KAPPA NO DEVICE TABLE
extern ait_KappaSpecificDeviceTableEntry aiv_KappaNoDeviceTable[];

//KAPPA DEVICE TABLE
extern ait_KappaSpecificDeviceTableEntry aiv_KappaSpecificDeviceTableA[];

bool aim_CheckForDevice (void);
bool aim_KappaAutoIdA(unsigned long *p_deviceId, unsigned long *p_submodelId);
bool aim_KappaIsKnownDevice (int theDeviceId);
bool aim_CheckDeviceModelEnable(unsigned long deviceId);
int aim_Interrogate(void);
bool aim_KappaResumeTelemetryA(void);
void aim_KappaRead(ait_KappaDeviceMemoryRange *kappa_Table);
bool aim_KappaIsDual(void);
void aim_KappaSetEGMModeGain(char telemType);
char aim_KappaGetPermPacingMode(void);
void aim_KappaRTT(void);
void aim_KappaEstablishSolidTelemetryLink(USHORT duration);
void aim_KappaSetMarkerArrayType(bool *modeFound, char **p_markerArray);
void aim_KappaCollectWaveform(void);
bool aim_KappaCollectWaveFormDataA(char magnetModeStatus,
                                   char collectionSeconds,
                                   char telemType,
                                   unsigned long egmTicks,
                                   bool *deviceIsDDIR );
void aim_KappaSetMagnetMode(char magnetModeStatus);
char aim_KappaGetModeGainByte(void);
bool aim_MonitorIsA2020C(void);
bool aim_skipInterrogationCheckFWUpdates(void);
bool aim_autoIdSuccessful(void);
void aim_SaveSessionParameters(void);
void aim_KappaSetPacingMode(char pacingMode);

//serial number
bool aim_KappaGetSerialNumber(char *p_serialNumber, char* p_fwRev);
void aim_KappaSetSerialNumberLocation(ait_KappaDeviceMemoryRange *p_kappa);
void aim_KappaAssembleSerialString(char *completeSNString);
void aim_KappaSixDigitSerialNumber(char* serialUplink, char *sixDigitSN);
bool aim_KappaValidateSerialNumber(void);

//kappa serial number, device id, and interrogation timedate strings
char * aim_KappaGetCompleteSNString();
char * aim_KappaGetWorkingDeviceIDString();
char * aim_KappaGetInterrogationTimeDateString();

//parity
USHORT aim_KappaAddParity(char *dlBuffer, char *dlBufferWithParity, USHORT size);

bool aim_KappaCheckUplinkParity(char *aiv_kappaUplink, unsigned long size);

void aim_KappaSendTelemetryA(char *p_dlBufferWithParity, USHORT downlinkSize,
                             char *p_uplink,   USHORT uplinkSize, bool aiv_processACK);

void aim_KappaRTTSendTelemetry(char *p_markerArray, USHORT markerArraySize,
                               char *p_dlBufferWithParity, USHORT totalSize);

bool aim_KappaCheckRTTDataValidStatusBit(void);
void aim_UpdateDateTime(void);
void aim_KappaFindStartTime(char *str, unsigned long totalElapsedSeconds, char *startTime);
bool aim_KappaCheckERIStatus(void);

void aim_KappaSaveInterrogationDurationTime(void);

#endif

