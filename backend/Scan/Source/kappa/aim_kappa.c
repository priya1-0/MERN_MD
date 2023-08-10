 /*
***********************************************************************
 2490 In-home Remote Monitor
 Copyright (c) Medtronic, Inc. 2001

 MODULE: Application Interrogation Module for the Kappa Family.

 OWNER: Medtronic

 $Revision$

 $Date$

 $RCSfile$

 FUNCTIONS:
bool aim_CheckForDevice (void);
bool aim_KappaAutoIdA(unsigned long *p_deviceId, unsigned long *p_submodelId);
bool aim_KappaIsKnownDevice (int theDeviceId);
int aim_Interrogate(void);
bool aim_KappaResumeTelemetryA(void);
void aim_KappaRead(ait_KappaDeviceMemoryRange *kappa_Table);
bool aim_KappaIsDual(void);
void aim_KappaSetEGMModeGain(char telemType);
char aim_KappaGetPermPacingMode(void);
void aim_KappaRTT(void);
void aim_KappaSetMarkerArrayType(bool *modeFound, **p_markerArray);
bool aim_KappaCollectWaveFormDataA(char magnetModeStatus,
                                   char collectionSeconds,
                                   char telemType,
                                   unsigned long egmTicks);
void aim_KappaSetMagnetMode(char magnetModeStatus);
char aim_KappaGetTempPacingMode(void);
char aim_KappaGetModeGainByte(void);
bool aim_KappaGetSerialNumber(char *p_serialNumber);
void aim_KappaSetSerialNumberLocation(ait_KappaDeviceMemoryRange *p_kappa);
void aim_KappaAssembleSerialString(char *completeSNString);
void aim_KappaSixDigitSerialNumber(char* serialUplink, char *sixDigitSN);
bool aim_KappaValidateSerialNumber(void);
USHORT aim_KappaAddParity(char *dlBuffer, char *dlBufferWithParity, USHORT size);
bool aim_KappaCheckUplinkParity(char *aiv_kappaUplink, unsigned long size);
void aim_KappaSendTelemetryA(char *p_dlBufferWithParity, USHORT downlinkSize,
                       ......char *p_uplink,   USHORT uplinkSize, bool aiv_processACK);
void aim_KappaRTTSendTelemetry(char *p_markerArray, USHORT markerArraySize,
                               char *p_dlBufferWithParity, USHORT totalSize);
void aim_KappaEstablishSolidTelemetryLink(USHORT duration);
bool aim_KappaCheckRTTDataValidStatusBit(void);
void aim_UpdateDateTime(void);
void aim_KappaFindStartTime(char *str, unsigned long totalElapsedSeconds, char *startTime);
bool aim_KappaCheckERIStatus(void);
bool aim_MonitorIsA2020C(void);
bool aim_skipInterrogationCheckFWUpdates(void);
void aim_SaveSessionParameters(void);
 ENDPURPOSE

***********************************************************************
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "itoa.h"

#include "bsm_global.h"
#include "bsm_power.h"
#include "bsm_led.h"
#include "com_main.h"
#include "com_eepromapp.h"
#include "uim_ui.h"
#include "aim_kappa.h"
#include "fsm_kappa.h"
#include "fsm_file.h"
#include "tam_htel.h"
#include "nwm_net.h"
#include "ctype.h"

#include "aim_kdr700.h"
#include "aim_kdr900.h"
#include "aim_enpulse.h"
#include "aim_phoenix.h"

#include "aim_NVStorage.h"

// The instrument model (string) is defined here.
// The model id string is set for a "project" or firmware image.
// It contains the "fsc" pre-fix because it is used by the fsm code
// when generating the file.
const char fsc_InstrumentModelIDString[]  = "2490H";
char       *fsc_p_InstrumentModelIDString = (char *)fsc_InstrumentModelIDString;

//SERIAL NUMBER - prefix, 9999999, possible location code, and terminator
#define AIC_KAPPA_SIZE_OF_COMPLETE_SERIAL_NUMBER (3 + 6 + 1 + 1)
#define AIC_KAPPA_SIZE_OF_NODEVICE_MODEL_ID      5

#define POWER_BUTTON_HOLD_PERIOD 1000     // 1000 ticks = 10,000 msec = 10 sec.

// Wait 1 second, from end of downlink to start of uplink.
// 10 msec. per tick.
#define TAM_SEND_TIMEOUT 100


// See nEw3 Product Specification, Medtronic doc A17513,
// Table A-1.85
// Adapta FW revs are 1.3 and 2.0.
// nEw3 will be set to 4.1.

#define FIRMWARE_REV_OFFSET (7)
#define ADAPTA_FW_REV_13    (0x23)
#define ADAPTA_FW_REV_20    (0x40)
#define nEw3_FW_REV_41      (0x81)

#define nEw3_PREFIX_CHAR 'N'

#define MAX_SERIAL_NUMBER (999999L)

#define AIC_RADIOPAQUE_LENGTH   3       // Size of "PWY" of "PWY123456Q"
#define AIC_SIX_DIGIT_SN_LENGTH 6       // Size of "123456" of "PWY123456Q"

#define AIC_DDIR_MODE 0xB7        // DDIR mode

bool        skipInterrogationCheckFWUpdates = false;
static bool autoIdSuccessful;

//CLOCK TICKS
unsigned long aiv_ticksAtStartOfMemoryDump;
unsigned long aiv_ticksAtStartOfWaveform;
unsigned long aiv_ticksAtStartOfInterrogation;

//RETRIEVES NETWORK DATE TIME
extern void nwm_RetrieveHTTPDateTime(char *, unsigned long *);

//ID
char   *aiv_workingKappaDeviceIDString;
char   aiv_workingKappaSubModelId;
char   aiv_workingKappaDevice;
USHORT aiv_workingKappaDeviceTableIndex       = 0; //index to indicate if Kappa 700 or 900
USHORT aiv_specificKappaDeviceTableIndex      = 0;

//SERIAL NUMBER - can hold up to "PQS123456"
char        aiv_workingDeviceKappaFirmwareRev = 0;
char        aiv_workingKappaSerial[AIC_KAPPA_SIZE_OF_COMPLETE_SERIAL_NUMBER]; // serial number w/o prefix
bool        aiv_workingKappaSerialNumberValid = false;          // valid serial number?
static char aiv_completeSNString[AIC_KAPPA_SIZE_OF_COMPLETE_SERIAL_NUMBER]; // serial number with prefix

// The serial number bytes may have flex bits in the upper nibble.
// Use this mask to remove them for serial number usage
#define SERIAL_NUMBER_FLEX_MASK (0x0FFFFFL)

//MARKER
USHORT aiv_markerArraySize;

//DATA VALID STATUS BIT, Initialized to false, if RTT successful it is set to true
bool aiv_DataValidStatusBit = false;

char          aiv_ulKappa[AIC_KAPPA_MAX_UPLINK_SIZE];

// Large enough for single Chamber colllect 30 sec wavefore bytes, also used to dual chamber
// collect 7 sec waveform
unsigned char aiv_KappaWaveformData[AIC_KAPPA_EXPECTED_SINGLE_NUMBER_OF_EGM_BYTES];
// Global variables to save duration/time of interrogation.
unsigned long aiv_currentInterrogationDurationTime=0;

ait_KappaDeviceTableEntry aiv_2490H_KappaDeviceTableA[] =
{ /*Model ID, device-preinterrogate, device-interrogate, autoIdEnable */
    {AIC_DEVICE_MODEL_KAPPA700, aim_KDR700PreInterrogate,  aim_KDR700Interrogate,  false},
    {AIC_DEVICE_MODEL_KAPPA900, aim_KDR900PreInterrogate,  aim_KDR900Interrogate,  false},
    {AIC_DEVICE_MODEL_ENPULSE,  aim_EnpulsePreInterrogate, aim_EnpulseInterrogate, false},
    {AIC_DEVICE_MODEL_E3,       aim_EnpulsePreInterrogate, aim_EnpulseInterrogate, false},
    {AIC_NULL_DEVICE_ID, NULL, NULL, false},
};

ait_KappaDeviceTableEntry aiv_2020C_KappaDeviceTableA[] =
{ /*Model ID, device-preinterrogate, device-interrogate, autoIdEnable */
    {AIC_DEVICE_MODEL_KAPPA700, aim_KDR700PreInterrogate,  aim_KDR700Interrogate,  false},
    {AIC_DEVICE_MODEL_KAPPA900, aim_KDR900PreInterrogate,  aim_KDR900Interrogate,  false},
    {AIC_DEVICE_MODEL_ENPULSE,  aim_EnpulsePreInterrogate, aim_EnpulseInterrogate, false},
    {AIC_DEVICE_MODEL_E3,       aim_EnpulsePreInterrogate, aim_EnpulseInterrogate, false},
    {AIC_DEVICE_MODEL_PHOENIX,  aim_PhoenixPreInterrogate, aim_PhoenixInterrogate, true},
    {AIC_DEVICE_MODEL_PHOENIX_VITATRON,  aim_PhoenixPreInterrogate, aim_PhoenixInterrogate, true},
    {AIC_NULL_DEVICE_ID, NULL, NULL, false},
};

ait_KappaDeviceTableEntry *aiv_KappaDeviceTableA = aiv_2490H_KappaDeviceTableA;

//KAPPA NO DEVICE TABLE
ait_KappaSpecificDeviceTableEntry aiv_KappaNoDeviceTable[] =
{
    {"XXXX", "X", "XXXXXXXXX", 0x00, 0x00, AIC_NULL_DEVICE_ID}
};

//KAPPA DEVICE TABLE
ait_KappaSpecificDeviceTableEntry aiv_KappaSpecificDeviceTableA[] =
{
    /*Device String, Single/Dual, Serial Num. w/ null 6-digits,  batt. connector ID, submodel, Model ID, */
    {"KDR730", "D", "PHA000000", 0x00, 0x00, AIC_DEVICE_MODEL_KAPPA700},
    {"KDR731", "D", "PHB000000", 0x01, 0x00, AIC_DEVICE_MODEL_KAPPA700},
    {"KDR733", "D", "PHD000000", 0x02, 0x00, AIC_DEVICE_MODEL_KAPPA700},
    {"KDR736", "D", "PHC000000", 0x03, 0x00, AIC_DEVICE_MODEL_KAPPA700},
    {"KDR700", "D", "PGT000000", 0x00, 0x01, AIC_DEVICE_MODEL_KAPPA700},
    {"KDR701", "D", "PGU000000", 0x01, 0x01, AIC_DEVICE_MODEL_KAPPA700},
    {"KDR703", "D", "PGY000000", 0x02, 0x01, AIC_DEVICE_MODEL_KAPPA700},
    {"KDR706", "D", "PGW000000", 0x03, 0x01, AIC_DEVICE_MODEL_KAPPA700},
    {"KDR720", "D", "PGP000000", 0x00, 0x05, AIC_DEVICE_MODEL_KAPPA700},
    {"KDR721", "D", "PGR000000", 0x01, 0x05, AIC_DEVICE_MODEL_KAPPA700},
    {"KD700",  "D", "PHJ000000", 0x00, 0x02, AIC_DEVICE_MODEL_KAPPA700},
    {"KD701",  "D", "PHK000000", 0x01, 0x02, AIC_DEVICE_MODEL_KAPPA700},
    {"KD703",  "D", "PHM000000", 0x02, 0x02, AIC_DEVICE_MODEL_KAPPA700},
    {"KD706",  "D", "PHL000000", 0x03, 0x02, AIC_DEVICE_MODEL_KAPPA700},
    {"KVDD700","D", "PHN000000", 0x00, 0x04, AIC_DEVICE_MODEL_KAPPA700},
    {"KVDD701","D", "PHP000000", 0x01, 0x04, AIC_DEVICE_MODEL_KAPPA700},
    {"KSR700", "S", "PHR000000", 0x00, 0x06, AIC_DEVICE_MODEL_KAPPA700},
    {"KSR701", "S", "PHT000000", 0x01, 0x06, AIC_DEVICE_MODEL_KAPPA700},
    {"KSR703", "S", "PHW000000", 0x02, 0x06, AIC_DEVICE_MODEL_KAPPA700},
    {"KSR706", "S", "PHU000000", 0x03, 0x06, AIC_DEVICE_MODEL_KAPPA700},
    {"KDR600", "D", "PHE000000", 0x00, 0x09, AIC_DEVICE_MODEL_KAPPA700},
    {"KDR601", "D", "PHF000000", 0x01, 0x09, AIC_DEVICE_MODEL_KAPPA700},
    {"KDR603", "D", "PHH000000", 0x02, 0x09, AIC_DEVICE_MODEL_KAPPA700},
    {"KDR606", "D", "PHG000000", 0x03, 0x09, AIC_DEVICE_MODEL_KAPPA700},
    {"KDR651", "D", "PLJ000000", 0x01, 0x08, AIC_DEVICE_MODEL_KAPPA700},
    {"KDR653", "D", "PLK000000", 0x02, 0x08, AIC_DEVICE_MODEL_KAPPA700},
    {"KDR656", "D", "PLL000000", 0x03, 0x08, AIC_DEVICE_MODEL_KAPPA700},
    {"KDR931", "D", "PKT000000", 0x01, 0x00, AIC_DEVICE_MODEL_KAPPA900},
    {"KDR933", "D", "PKU000000", 0x02, 0x00, AIC_DEVICE_MODEL_KAPPA900},
    {"KDR901", "D", "PKM000000", 0x01, 0x01, AIC_DEVICE_MODEL_KAPPA900},
    {"KDR903", "D", "PKN000000", 0x02, 0x01, AIC_DEVICE_MODEL_KAPPA900},
    {"KDR906", "D", "PKP000000", 0x03, 0x01, AIC_DEVICE_MODEL_KAPPA900},
    {"KDR921", "D", "PKR000000", 0x01, 0x05, AIC_DEVICE_MODEL_KAPPA900},
    {"KD901",  "D", "PLB000000", 0x01, 0x02, AIC_DEVICE_MODEL_KAPPA900},
    {"KD903",  "D", "PLC000000", 0x02, 0x02, AIC_DEVICE_MODEL_KAPPA900},
    {"KD906",  "D", "PLD000000", 0x03, 0x02, AIC_DEVICE_MODEL_KAPPA900},
    {"KVDD901","D", "PLE000000", 0x01, 0x04, AIC_DEVICE_MODEL_KAPPA900},
    {"KSR901", "S", "PLF000000", 0x01, 0x06, AIC_DEVICE_MODEL_KAPPA900},
    {"KSR903", "S", "PLG000000", 0x02, 0x06, AIC_DEVICE_MODEL_KAPPA900},
    {"KSR906", "S", "PLH000000", 0x03, 0x06, AIC_DEVICE_MODEL_KAPPA900},
    {"KDR801", "D", "PKW000000", 0x01, 0x09, AIC_DEVICE_MODEL_KAPPA900},
    {"KDR803", "D", "PKY000000", 0x02, 0x09, AIC_DEVICE_MODEL_KAPPA900},
    {"KDR806", "D", "PLA000000", 0x03, 0x09, AIC_DEVICE_MODEL_KAPPA900},

    //
    // Enpulse - see Product Spec tables, "Table 141: Access Code and
    // Hybrid Links, by IPG Model" and "Table 5: Physical Device Size And
    // Radiopaque Code"
    //
    // MODEL    D/S   RADIOPAQUE  BATT  SUBF  FAMILY ID
    //

    {"E2VDD01","D", "PMV000000", 0x01, 0x04, AIC_DEVICE_MODEL_ENPULSE},
    {"E2SR01", "S", "PMW000000", 0x01, 0x06, AIC_DEVICE_MODEL_ENPULSE},
    {"E2SR03", "S", "PMY000000", 0x02, 0x06, AIC_DEVICE_MODEL_ENPULSE},
    {"E2SR06", "S", "PNA000000", 0x03, 0x06, AIC_DEVICE_MODEL_ENPULSE},
    {"E1DR21", "D", "PPT000000", 0x01, 0x0D, AIC_DEVICE_MODEL_ENPULSE},
    {"E1DR01", "D", "PRA000000", 0x01, 0x09, AIC_DEVICE_MODEL_ENPULSE},
    {"E1DR03", "D", "PRB000000", 0x02, 0x09, AIC_DEVICE_MODEL_ENPULSE},
    {"E1DR06", "D", "PRE000000", 0x03, 0x09, AIC_DEVICE_MODEL_ENPULSE},

    {"E2DR21", "D", "PMU000000", 0x01, 0x05, AIC_DEVICE_MODEL_ENPULSE},  // (ACM)
    {"E2DR01", "D", "PNB000000", 0x01, 0x01, AIC_DEVICE_MODEL_ENPULSE},  // (ACM)
    {"E2DR03", "D", "PNC000000", 0x02, 0x01, AIC_DEVICE_MODEL_ENPULSE},  // (ACM)
    {"E2DR06", "D", "PNH000000", 0x03, 0x01, AIC_DEVICE_MODEL_ENPULSE},  // (ACM)
    {"E2DR31", "D", "PNL000000", 0x01, 0x00, AIC_DEVICE_MODEL_ENPULSE},  // (ACM)
    {"E2DR33", "D", "PNM000000", 0x02, 0x00, AIC_DEVICE_MODEL_ENPULSE},  // (ACM)
    {"E2D01",  "D", "PNF000000", 0x01, 0x02, AIC_DEVICE_MODEL_ENPULSE},  // (ACM)
    {"E2D03",  "D", "PNG000000", 0x02, 0x02, AIC_DEVICE_MODEL_ENPULSE},  // (ACM)

    // Adapta, Sensia. Also starting point for nEw3

    {"ADDRL1",  "D", "PWE000000", 0x01, 0x00, AIC_DEVICE_MODEL_E3},
    {"ADDR01",  "D", "PWB000000", 0x01, 0x01, AIC_DEVICE_MODEL_E3},
    {"ADDR03",  "D", "PWD000000", 0x02, 0x01, AIC_DEVICE_MODEL_E3},
    {"ADDR06",  "D", "PWC000000", 0x03, 0x01, AIC_DEVICE_MODEL_E3},
    {"ADDRS1",  "D", "PWA000000", 0x01, 0x05, AIC_DEVICE_MODEL_E3},
    {"ADD01",   "D", "PWF000000", 0x01, 0x02, AIC_DEVICE_MODEL_E3},
    {"ADVDD01", "D", "PWG000000", 0x01, 0x04, AIC_DEVICE_MODEL_E3},
    {"VEDR01",  "D", "PWH000000", 0x01, 0x0D, AIC_DEVICE_MODEL_E3},
    {"SEDR01",  "D", "PWL000000", 0x01, 0x09, AIC_DEVICE_MODEL_E3},
    {"SEDRL1",  "D", "PWJ000000", 0x01, 0x08, AIC_DEVICE_MODEL_E3},
    {"SED01",   "D", "PWK000000", 0x01, 0x0A, AIC_DEVICE_MODEL_E3},
    {"ADSR01",  "S", "PWM000000", 0x01, 0x06, AIC_DEVICE_MODEL_E3},
    {"ADSR03",  "S", "PWP000000", 0x02, 0x06, AIC_DEVICE_MODEL_E3},
    {"ADSR06",  "S", "PWN000000", 0x03, 0x06, AIC_DEVICE_MODEL_E3},
    {"SESR01",  "S", "PWR000000", 0x01, 0x0E, AIC_DEVICE_MODEL_E3},
    {"SES01",   "S", "PWS000000", 0x01, 0x0C, AIC_DEVICE_MODEL_E3},

    // Phoenix, Medtronic - [Attesta, Sphera]

    {"ATDRL1",  "D", "FNE000000", 0x01, 0x00, AIC_DEVICE_MODEL_PHOENIX},
    {"ATDR01",  "D", "FNB000000", 0x01, 0x01, AIC_DEVICE_MODEL_PHOENIX},
    {"ATDRS1",  "D", "FNA000000", 0x01, 0x05, AIC_DEVICE_MODEL_PHOENIX},
    {"SPDR01",  "D", "FNC000000", 0x01, 0x09, AIC_DEVICE_MODEL_PHOENIX},
    {"SPDRL1",  "D", "FND000000", 0x01, 0x08, AIC_DEVICE_MODEL_PHOENIX},
    {"ATSR01",  "S", "FNF000000", 0x01, 0x06, AIC_DEVICE_MODEL_PHOENIX},
    {"SPSR01",  "S", "FNG000000", 0x01, 0x0E, AIC_DEVICE_MODEL_PHOENIX},


    // Phoenix, Vitatron - [Q80A2, Q70A2, G70A2, Q50A2, Q20A2, G20A2]

    {"Q80A2", "D", "510000000", 0x01, 0x00, AIC_DEVICE_MODEL_PHOENIX_VITATRON},
    {"Q70A2", "D", "520000000", 0x01, 0x01, AIC_DEVICE_MODEL_PHOENIX_VITATRON},
    {"G70A2", "D", "550000000", 0x01, 0x09, AIC_DEVICE_MODEL_PHOENIX_VITATRON},    
    {"Q50A2", "D", "530000000", 0x01, 0x02, AIC_DEVICE_MODEL_PHOENIX_VITATRON},
    {"Q20A2", "S", "540000000", 0x01, 0x06, AIC_DEVICE_MODEL_PHOENIX_VITATRON},
    {"G20A2", "S", "560000000", 0x01, 0x0E, AIC_DEVICE_MODEL_PHOENIX_VITATRON},
        
    {"End of Table", "End of Table", AIC_NULL_DEVICE_ID, AIC_NULL_DEVICE_ID, AIC_NULL_DEVICE_ID}
};

/*
In order to enable handshaking during page interrogation, a final 
TurnOffReceiver() function call was needed to terminate device communication. 
This function interface is not exposed for general application usage and is 
encapsulated in tam_RecieveCommon.c. Rather than expose the interface to the 
entire application by adding the prototype into its header file, the function 
prototype was defined here so that usage of the function would continue to be 
limited.
See TFS/2490H-MR2/212 for a full description of the hand shaking addition.

TurnOffReceiver() also needed to be called during the Push to Update feature 
because it was not working without it.
*/
void TurnOffReceiver(void);


/*
***********************************************************************

 FUNCTION:   aim_CheckForDevice

 DESCRIPTION:
This function initializes the global variables and sub-system.
This function then checks for a device under the head. Repeatedly auto-id
and updating ui.
If a valid and supported device is found then the device specific
pre-Interrogate function is called.

Finally, the device id, submodel id, and index into the device table are saved in
global variables and will be used when later doing the full Interrogate.

If no valid and supported device is found this function will
shut the system down, unless the power button has been held pressed for
some time, in which case, a flag is set so as to skip interrogation and
proceed to check firmware updates in the main loop.

This function is the starting point for application telemetry
with device. aim_KappaInterrogate() is the finishing point for
application telemetry with device.  For this reason,
uim_InterrogationStarted() is called at the start of this
function and uim_InterrogationComplete() is called at the end
of aim_KappaInterrogate().

 NOTE: No phone tones are initiated in this function or at this
       point in (run) time because this code runs before the phone
       is initialized and available.

 FUNCTION CONSTANTS:

    AIC_NULL_DEVICE_ID
       Initialization value for device id.

 FUNCTION RETURN:
   0/1 = fail/success = false/true

 FUNCTION PARAMETERS:

***********************************************************************
*/

bool aim_CheckForDevice (void)
{
    unsigned long deviceId;
    unsigned long submodelId;
    unsigned long telemetryWarningTimer;
    unsigned long powerButtonHoldTimer;

    // initialize telemetry
#ifndef DSP_2490_SIMULATION
    tam_Initialize_TelemetryA(tac_L88TelemProtocol);
#endif

    if (aim_MonitorIsA2020C())
    {
        bsm_EHLog("2020C: Looking for device...", 0);
        aiv_KappaDeviceTableA = aiv_2020C_KappaDeviceTableA;
    }
    else
    {
        bsm_EHLog("2490H: Looking for device...", 0);
        aiv_KappaDeviceTableA = aiv_2490H_KappaDeviceTableA;
    }

    aiv_ticksAtStartOfInterrogation   = NU_Retrieve_Clock();

    // Initialize device id variables.
    aiv_workingKappaDeviceIDString    = AIC_NULL_DEVICE_ID;

    aiv_workingKappaSerialNumberValid = false;

    // Initialize the UI to indicate that interrogation/autoID has started.
    // (For a 2020C monitor, certain UI functions depend upon autoIDSuccessful
    // flag. So, initialize this first.)
    autoIdSuccessful = false;
    uim_InterrogationStarted();

    // initialize the warning timer
    telemetryWarningTimer = NU_Retrieve_Clock() + AIC_TELEMETRY_WARNING_PERIOD;

    // Initialize the power button hold timer.
    powerButtonHoldTimer  = NU_Retrieve_Clock() + POWER_BUTTON_HOLD_PERIOD;

    // Perform the Auto-ID, if no device found after a period of time
    // shut the system down.
    // while there is no device under the head
    deviceId   = AIC_NULL_DEVICE_ID;
    submodelId = AIC_NULL_DEVICE_ID;

    while (aim_KappaAutoIdA(&deviceId, &submodelId) != true)
    {
        // If the power button is being held, hold off the telemetry warning
        // until the power button is no longer held.
        if (bsm_isPowerStateGoodHold())
        {
            if (powerButtonHoldTimer < NU_Retrieve_Clock())
            {
                // Turn off the receiver since it was left on
                // by the auto ID
                TurnOffReceiver();
                // Device was not found and
                // power button held pressed for some time.
                bsm_EHLog("Device not found & power button held pressed...", 0);
                bsm_EHLog("Skip interrogation & look for FW updates...", 0);
                skipInterrogationCheckFWUpdates = true;
                deviceId                        = AIC_NULL_DEVICE_ID;

                // Since device interrogation is being skipped, we need to provide
                // empty values for certain asset file information
                // ---------------------------------------------------------------
                // Save pointer to model string.
                aiv_workingKappaDeviceIDString = aiv_KappaNoDeviceTable[0].deviceString;

                //Get basic format of serial number
                sprintf(aiv_completeSNString, "%s", aiv_KappaNoDeviceTable[0].serialNumber);

                strcpy(fsv_AssetSectionHeader.version, "2.0");
                // ---------------------------------------------------------------

                uim_InterrogationSkipped();
                return true;
            }
        }
        else
        {
            uim_TelemetryWarning(on);
        }

        // if we cannot establish communication with original device
        //  within the defined period of time we shut down
        if (telemetryWarningTimer < NU_Retrieve_Clock())
        {
            bsm_EHLock("Device not found.");
        }

        deviceId = AIC_NULL_DEVICE_ID;
    }

    uim_TelemetryWarning(OFF);

    if (deviceId != AIC_NULL_DEVICE_ID)
    {
        // valid device found....
        autoIdSuccessful = true;

        // For the 2020C, sound the complete tone and turn on the first
        // interrogation LED.
        if (aim_MonitorIsA2020C())
        {
            // Turn on the first progress LED to indicate successful autoId.
            bsm_LDChange(bsc_LEDPROGRESS1, bsc_LEDON);

            NU_Sleep(100);     // Wait for 1 sec
            // Sound interrogation complete tone to indicate successful
            // autoId.
            uim_CompleteTone();

            // Initialize the UI to indicate that interrogation has started.
            uim_InterrogationStarted();
        }

        bsm_EHLog("Device auto-id successful", 0);

    }

    // execute the pre-interrogate function.
    // aiv_workingDeviceIdTableIndex was previously set.
    aiv_workingKappaDevice     = deviceId;
    aiv_workingKappaSubModelId = submodelId;

    aiv_KappaDeviceTableA[aiv_workingKappaDeviceTableIndex].preInterrogate();

    return(true);
}

/*
***********************************************************************

 FUNCTION:   aim_KappaAutoIdA

 DESCRIPTION:
This Telemetry A function returns the id of the device under the head.
Local uplink and downlink buffers are used to keep this simple. The
aim_KappaSendTelemetryA() is not used because we are not ready to call
aim_KappaResumeTelemetryA() yet if there is a loss of telemetry.

 FUNCTION CONSTANTS:

   AIC_A_AUTOID_MESSAGE
      Message used to auto id a Telemetry A device under the head.

   AIC_KAPPA_A_AUTOID_EXPECTED_UPLINK
      Expected size of the auto id uplink.

   AIC_KAPPA_A_AUTOID_DOWNLINK_SIZE
      Expected size of the auto id downlink.

 FUNCTION RETURN:
   0/1 = fail/success = false/true

 FUNCTION PARAMETERS:
   p_deviceId
      Set to the model id of the device under the head.
   p_submodelId
      Set to the submodel id of the device under the head.

***********************************************************************
*/
const char AIC_KAPPA_A_AUTOID_MESSAGE[] =
{
    0xc1, 0x00, 0x00, 0xc1, 0x00, 0x00, 0x00
};

#define AIC_KAPPA_A_AUTOID_DOWNLINK_SIZE   7
#define AIC_KAPPA_A_AUTOID_EXPECTED_UPLINK 4

bool aim_KappaAutoIdA(unsigned long *p_deviceId, unsigned long *p_submodelId)
{
    tat_status status;
    char       autoIdDownlink[AIC_KAPPA_A_AUTOID_DOWNLINK_SIZE];
    char       autoIdUplink[AIC_KAPPA_A_AUTOID_EXPECTED_UPLINK];
    bool       returnCode = false; // initialize to not successful

    *p_deviceId   = 0;
    *p_submodelId = 0;

    memcpy(autoIdDownlink, AIC_KAPPA_A_AUTOID_MESSAGE, AIC_KAPPA_A_AUTOID_DOWNLINK_SIZE);

#ifdef DSP_2490_SIMULATION
    status          = tac_successful;
    autoIdUplink[0] = AIC_DEVICE_MODEL_KAPPA700;
    autoIdUplink[1] = 0x82;
    autoIdUplink[2] = 0x01;
    autoIdUplink[3] =  autoIdUplink[0] ^ autoIdUplink[1] ^ autoIdUplink[2];
#else

    status          = tam_Send_Telemetry(autoIdDownlink, AIC_KAPPA_A_AUTOID_DOWNLINK_SIZE,
                                         autoIdUplink, AIC_KAPPA_A_AUTOID_EXPECTED_UPLINK,
                                         TAM_SEND_TIMEOUT);
#endif

    if (status != tac_successful)
        returnCode = false;
    else if ((autoIdUplink[0] ^ autoIdUplink[1] ^
              autoIdUplink[2] ^ autoIdUplink[3]) != 0)
        returnCode = false;
    else if (autoIdUplink[1] != 0x82)
        returnCode = false;
    else
    {
        *p_deviceId   = autoIdUplink[0];            // model id
        *p_submodelId = (autoIdUplink[2] & 0x0F);   // submodel id
        // verify the device is supported.
        returnCode    = aim_KappaIsKnownDevice(autoIdUplink[0]);

        if (returnCode == true) {
            // A supported device is under the head but is it
            //  only enable via the FDN Phone4 parameter.
            // Check for auto id enable support via the FDN 
            //  Phone4 parameter.
            returnCode = aim_CheckDeviceModelEnable(*p_deviceId);
        }
    }

    return (returnCode);
}

/*
***********************************************************************

 FUNCTION:   aim_KappaIsKnownDevice

 DESCRIPTION:
This function determines if the passed device is in the list of a devices
that we are capable of interrogating.

 FUNCTION CONSTANTS:

   AIC_NULL_DEVICE_ID
      Null initialization value for device id.

 FUNCTION RETURN:
   Can we interrogate = false/true = can't do/can do

 FUNCTION PARAMETERS:
   theDevice
      The id of the device to check for interrogation possibilities.

***********************************************************************
*/
bool aim_KappaIsKnownDevice (int theDeviceId)
{
    bool deviceFound = false;
    aiv_workingKappaDeviceTableIndex = 0;

    // Can't process a null device id.
    if (theDeviceId == AIC_NULL_DEVICE_ID)
        return(deviceFound);

    // Check the device table.
    // A device id of AIC_NULL_DEVICE_ID signals the end of the table.
    while (AIC_NULL_DEVICE_ID != aiv_KappaDeviceTableA[aiv_workingKappaDeviceTableIndex].deviceId)
    {
        if ( theDeviceId == aiv_KappaDeviceTableA[aiv_workingKappaDeviceTableIndex].deviceId)
        {
            deviceFound = true;
            break;
        }
        aiv_workingKappaDeviceTableIndex++;
    }

    return (deviceFound);
}

/*
***********************************************************************

 FUNCTION: aim_CheckDeviceModelEnable

 DESCRIPTION:

        Determines if the particular device model has been enabled via the
        Phone4 parameter.  This routine relies on a particular format for
        the model ids listed in the Phone4 parameter.
        1. The very first character must be a '#'
        2. The entire string must be terminated with a ';'
        3. A ',' must separate the individual model id information 
        4. Hexidecimal entries should be upper case
        5. NULL termination is not required. 

        Example format: #0019,0017,002A;

        This function expects the aiv_workingKappaDeviceTableIndex to
        be accuratley set prior to calling this function. The index is
        used to determine FDN Phone4 parameter should additionally be 
        check for device support.

        For extensibility, submodel information checking may be easily
        added provided it directly follows the corresponding model id.
        

 FUNCTION PARAMETERS:

        unsigned long deviceId - a valid device ID determined via AutoID.

 FUNCTION RETURN:

   boolean true if device is enabled. If the device
   has not been enabled, false is returned.

***********************************************************************
*/
bool aim_CheckDeviceModelEnable(unsigned long deviceId)
{
    char        DeviceEnableList[coc_ISPPhone4_SIZE];
    char        model_id_str[4];
    char        HexToAscii[] = "0123456789ABCDEF";
    int         loop_cnt;
    bool        ret_val = false;
    bool        model_found = false;

    // Check if autoIdEnable is active for the device under the head.
    if ( false == aiv_KappaDeviceTableA[aiv_workingKappaDeviceTableIndex].autoIdEnable )
    {
        return true;
    }


    // Read in the device enable data from the Phone4 parameter
    bsm_EEReadBuf((UINT8*)DeviceEnableList, coc_ISPPhone4_SIZE, coc_ISPPhone4_ADDR);

    // Check the first character for validity
    if (DeviceEnableList[0] == '#')
    {
        // Initial character found, replace with a comma to optimize the loop below
        DeviceEnableList[0] = ',';

        // Convert the deviceId passed in, into a 4 byte character string
        // for comparison
        model_id_str[0] = HexToAscii[(deviceId & 0x0000F000) >> 12];
        model_id_str[1] = HexToAscii[(deviceId & 0x00000F00) >>  8];
        model_id_str[2] = HexToAscii[(deviceId & 0x000000F0) >>  4];
        model_id_str[3] = HexToAscii[(deviceId & 0x0000000F)      ];

        // The initial character has been located
        // now parse the data for the model id and terminating character
        for(loop_cnt = 0; loop_cnt < coc_ISPPhone4_SIZE; loop_cnt++)
        {
            // Look for the start of the next entry
            if(DeviceEnableList[loop_cnt] == ',')
            {
                // If we haven't already found a matching id,
                // Read 4 bytes of model data and compare to the interrogated Device Id
                if(model_found == false &&
                   DeviceEnableList[loop_cnt+1] == model_id_str[0] &&
                   DeviceEnableList[loop_cnt+2] == model_id_str[1] &&
                   DeviceEnableList[loop_cnt+3] == model_id_str[2] &&
                   DeviceEnableList[loop_cnt+4] == model_id_str[3])
                {
                   // model id located
                   model_found = true;
                   // extensibility - Extra code could be added here to support submodel id
                }
            }
            else if(DeviceEnableList[loop_cnt] == ';')
            {
                // This is the terminating character, if a model id match was found,
                // set the return value to true
                if (model_found == true)
                {
                    ret_val = true;
                }
                break; // Exit - terminating character found
            }
        }
    }
    // return the status of the string search
    return(ret_val);
}

/*
***********************************************************************

 FUNCTION:   aim_Interrogate

 DESCRIPTION:
This function is called to interrogate the data of the device currently under
the head. Before making this function-call a call must have been made to
aim_CheckForDevice(). The function aim_CheckForDevice(), detected the device,
validated the device, and stored the device id, submodelid, and serial number in global
variables which are then used here.

The findings of the previously called aim_CheckForDevice() function
are used to branch to the device specific initialization and interrogation
routines.

For Telemetry A, aim_KappaResumeTelemetryA() is called to validate serial
number.

FUNCTION CONSTANTS:

   AIC_NULL_DEVICE_ID
       Initialization value for device id.

   AIC_MAGNET_MODE_OFF
      Decode value of 0x03, passed to turn magnet mode off.

   AIC_MAGNET_MODE_ON
      Decode value of 0x04, passed to turn magnet mode on.

FUNCTION RETURN:
   success = 0

***********************************************************************
*/
int aim_Interrogate(void)
{
    char timeOfSave[15] = {"XXXXXXXXXXXXXX"};

    // This function should not be called if the device id
    // is not valid.  aim_KappaCheckForDevice() should have been called
    // previous to this and set the device id.
    if (aiv_workingKappaDevice == AIC_NULL_DEVICE_ID)
        return(false);
    // Verify same device is present and resume detect.
    aim_KappaResumeTelemetryA();

    //aim_KappaAssembleSerialString does the following:
    //1. get complete serial number string for writing it to file and
    //2. set aiv_specificKappaDeviceTableIndex to correspond to specific Kappa Device
    //3. get aiv_workingKappaDeviceIDString for writing it to file
    aim_KappaAssembleSerialString(aiv_completeSNString);

    // Open the file-structure here.
    fsm_OpenFile(aiv_workingKappaDeviceIDString, aiv_completeSNString, timeOfSave, AIC_NUMBER_OF_SECTIONS);

    aiv_ticksAtStartOfWaveform = NU_Retrieve_Clock();

    fsm_OpenKappaWaveformFileSection( aiv_workingKappaDeviceIDString, aiv_completeSNString,
                                      aim_KappaGetModeGainByte());


    // Wavefrom collection
    aim_KappaCollectWaveform();


    fsm_CloseKappaWaveformFileSection();

    //Waveform complete, set 3rd light=blinking
    uim_IlluminateLED(AIC_LED3);

    // Perform the RTT interrogation after the waveform collection
    aim_KappaRTT();

    //Sets EGM mode and gain back to default AEGM
    aim_KappaSetEGMModeGain(AIC_ATRIAL_EGM_MODE);

    // Restore magnet mode to off
    aim_KappaSetMagnetMode(AIC_MAGNET_MODE_OFF);

    aiv_ticksAtStartOfMemoryDump = NU_Retrieve_Clock();
    // The device id and device id table index were previously set
    // by aim_KappaCheckForDevice(), call the device-specific interrogate.
    aiv_KappaDeviceTableA[aiv_workingKappaDeviceTableIndex].interrogate();

    // Turn of the receiver otherwise monitor and 
    //  device will continue hand shaking
    TurnOffReceiver();

    //set all five LEDs to "On"
    uim_IlluminateLED(AIC_LED6);

    uim_InterrogationComplete();

    // After the Interrogate start the UI for modem.
    // Turn on the 1st phone LED.
    uim_ModemStart(ON);

    aim_KappaSaveInterrogationDurationTime();
    return(true);
}

/*
***********************************************************************

 FUNCTION:   aim_KappaResumeTelemetryA

 DESCRIPTION:
This Telemetry A function resumes telemetry by searching for the current
device using the aim_SerialNumber function. It's assumed that before this
function is called, the device id has been interrogated, validated, and
locked in. If this is the first time this function is called then the serial
number is unknown and must be interrogated. If the specific device is not
found (specific device is not under the head) a warning is issued.
If the specific device is not found in a period of time we shutdown.
This function does not return unless the device responds with the specific
serial number.

 FUNCTION CONSTANTS:

   AIC_TELEMETRY_RETRY
      The amount of time we wait between attempts to re-establish
      communication.

   AIC_TELEMETRY_WARNING_PERIOD
      The amount of time that we allow the retries to go on before
      we shut down.

 FUNCTION RETURN:
      true - specific device is found.

***********************************************************************
*/
bool aim_KappaResumeTelemetryA(void)
{
    unsigned long telemetryWarningTimer;
    bool          deviceFound;

    // initialize the warning timer
    telemetryWarningTimer = NU_Retrieve_Clock() + AIC_TELEMETRY_WARNING_PERIOD;

    // while there is no device or current device's serial number is incorrect
    deviceFound           = false;
    while (!deviceFound)
    {
        // to resume telemetry a successful valid serial number must be
        // obtained and a successful resume detect must be done.
        // A special case - the first time this is called the serial
        // number is not known and must be interrogated and locked in.

        // If needed query the serial number for the first time.
        if (aiv_workingKappaSerialNumberValid == false)
        {
            if (aim_KappaGetSerialNumber(aiv_workingKappaSerial, &aiv_workingDeviceKappaFirmwareRev) == true)
            {
                aiv_workingKappaSerialNumberValid = true;
                deviceFound = true;
            }
        }
        else if (aim_KappaValidateSerialNumber() == true)
            deviceFound = true;
        // If there was a problem then update the clock and UI
        if (!deviceFound)
        {
            bsm_SDPrint("Resume TelemA. ");
            uim_TelemetryWarning(on);

            // if we cannot establish communication with original device
            //  within the defined period of time we shut down
            // a deviceFound=false will never be returned.
            if (telemetryWarningTimer < NU_Retrieve_Clock())
            {
                bsm_EHLock("Telem. A device not found.");
            }

        }
    }
    uim_TelemetryWarning(OFF);

    return(deviceFound);
}

/*
***********************************************************************

 FUNCTION:   aim_KappaRead

 DESCRIPTION:
This Telemetry A function steps sequentially through a specific Kappa Device Memory
Range table, each time sending a downlink request and receiving uplinked memory pages
until all memory defined in table is uplinked. Each uplink buffer is written
to file. The design allows aim_KappaRead to remain intact should the
pages per uplink specification change (AIC_KAPPA_PAGES_PER_UPLINK).
Downlinks are assembled in the following order:
1. family id
2. process uplink command code (bits 4-7) and  sub-family id (bits 0-3)
3. control
4. segment number
5. control (bits 6,7) and number of pages to uplink (bits 0-5)
6. starting page of particular uplink

Parity is inserted after every three bytes and downlink is performed by
aim_KappaSendTelemetryA().  When 1/3 of device memory has been uplinked LED 4 is
set to blinking, when device memory is 2/3 complete LED 5 is set to blinking.
When device memory is completely uplinked the 5th LED is illuminated to indicate
end of interrogation.

 FUNCTION CONSTANTS:

   AIC_KAPPA_PAGES_PER_UPLINK
     The maximum number of pages that can be uplinked per request.

   AIC_KAPPA_MAX_UPLINK_SIZE
     The maximum number of bytes that can be uplinked.

   AIC_KAPPA_UPLINK_PAGE_SIZE
     Size of an uplinked page including parity byte.

   AIC_DO_NOT_PROCESSACK
     Not expecting an uplink that returns an ACK.


 FUNCTION PARAMETERS:
    kappa_Table
      The device specific memory range table.
***********************************************************************
*/
void aim_KappaRead(ait_KappaDeviceMemoryRange *kappa_Table)
{
    int    tIndex           = 0;
    USHORT size             = 0;
    USHORT totalSize        = 0;

    USHORT pagesUplinked    = 0;
    USHORT pagesCompleted   = 0;
    USHORT pagesToUplink    = 0;
    USHORT tableMemorySize  = 0;
    USHORT downlinkComplete = 0;
    char   outputString[35] = {0};
    char   aNumber[3]       = {0};
    USHORT pages;

    char dataValidByte;
    bool ledFourBlinking = false;
    bool ledFiveBlinking = false;
    char dlBuffer[AIC_KAPPA_MAX_DL_PRE_PARITY_SIZE];
    char dlBufferWithParity[AIC_KAPPA_MAX_DOWNLINK_SIZE];

    //step through entire table and add up the bytes, used later for turning on LED's
    while(kappa_Table[tIndex].numPages != 0)
    {
        tableMemorySize += kappa_Table[tIndex].size;
        tIndex++;
    }

    tIndex = 0;
    while(kappa_Table[tIndex].size != 0)   //go through entire table
    {
        size           = 0;
        pagesCompleted = 0;
        pagesUplinked  = 0;

        //Do until all pages in row "tIndex" are downlinked
        while(pagesUplinked < kappa_Table[tIndex].numPages)
        {
            // downlink model id, submodel id, control byte and segment number
            dlBuffer[size++] = aiv_workingKappaDevice;         //family id code
            dlBuffer[size++] = (aiv_workingKappaSubModelId << 4); //submodel and comm. code
            if(kappa_Table[tIndex].segment != 0)
            {
                dlBuffer[size++] = 0x80;                     //control byte
                dlBuffer[size++] = kappa_Table[tIndex].segment; //seg. select
            }

            //determine the number of pages to uplink and the first page of uplink
            if( kappa_Table[tIndex].numPages < (AIC_KAPPA_PAGES_PER_UPLINK + pagesUplinked) )
            {
                pagesToUplink  = (kappa_Table[tIndex].numPages - pagesUplinked);
                pagesUplinked  = kappa_Table[tIndex].numPages;
                pagesCompleted = kappa_Table[tIndex].numPages - pagesToUplink;
            }
            else
            {
                pagesToUplink  =  AIC_KAPPA_PAGES_PER_UPLINK;
                pagesCompleted = pagesUplinked;
                pagesUplinked  = pagesCompleted + AIC_KAPPA_PAGES_PER_UPLINK;
            }

            //downlink number of pages to uplink and the first page of uplink
            dlBuffer[size++]  = (0x00 | (pagesToUplink - 1));   //control byte
            dlBuffer[size++]  = (kappa_Table[tIndex].firstPage + pagesCompleted);

            totalSize         = aim_KappaAddParity(dlBuffer, dlBufferWithParity, size);

            //compute bytes downlinked thus far
            downlinkComplete += (pagesToUplink * AIC_KAPPA_UPLINK_PAGE_SIZE);

            //Assemble string for bsm_SDPrint call
            strcpy(outputString, "Interrogating Seg ");
            aim_itoa(kappa_Table[tIndex].segment, aNumber, 10);
            strcat(outputString, aNumber);
            strcat(outputString, ", Pages ");
            aim_itoa((kappa_Table[tIndex].firstPage + pagesCompleted), aNumber, 10);
            strcat(outputString, aNumber);
            strcat(outputString, "-");
            aim_itoa( ((pagesToUplink - 1) + pagesCompleted), aNumber, 10);
            strcat(outputString, aNumber);
            bsm_SDPrint(outputString);

            aim_KappaSendTelemetryA(dlBufferWithParity, totalSize, aiv_ulKappa,
                                    (pagesToUplink * AIC_KAPPA_UPLINK_PAGE_SIZE + AIC_KAPPA_HEADER),
                                    AIC_DO_NOT_PROCESSACK);

            //LED's
            if ( (downlinkComplete > (tableMemorySize/3) ) && !ledFourBlinking )
            {
                //if 1/3 done with table set 4th LED to blinking
                uim_IlluminateLED(AIC_LED4);
                ledFourBlinking = true;
            }
            else if ( (downlinkComplete > ( tableMemorySize - tableMemorySize/3)) && !ledFiveBlinking )
            {
                //else if 2/3 done with table set 5th LED to blinking
                uim_IlluminateLED(AIC_LED5);
                ledFiveBlinking = true;
            }

            //DATA VALID STATUS BIT
            //IF RTT FAILED THEN THE DATA VALID STATUS BIT MUST BE SET TO
            //FALSE BEFORE IT IS WRITTEN TO FILE
            if ( (aiv_DataValidStatusBit == false) && //INDICATES RTT FAILED
                 (kappa_Table[tIndex].segment == AIC_DATA_VALID_SEGMENT) &&
                 ((kappa_Table[tIndex].firstPage + pagesCompleted) <= AIC_DATA_VALID_PAGE) &&
                 ((kappa_Table[tIndex].firstPage + pagesUplinked) >=  AIC_DATA_VALID_PAGE) )
            {
                pages         = ((kappa_Table[tIndex].firstPage + pagesUplinked) - AIC_DATA_VALID_PAGE);
                dataValidByte = aiv_ulKappa[
                    AIC_KAPPA_HEADER + (pages * AIC_KAPPA_UPLINK_PAGE_SIZE) + AIC_DATA_VALID_OFFSET];
                aiv_ulKappa[AIC_KAPPA_HEADER + (pages * AIC_KAPPA_UPLINK_PAGE_SIZE) + AIC_DATA_VALID_OFFSET]
                              = (dataValidByte & AIC_DATA_VALID_MASK);
            }

            fsm_WriteMemoryDumpFileSection( &aiv_ulKappa[2],
                                            pagesToUplink,
                                            kappa_Table[tIndex].segment,
                                            (kappa_Table[tIndex].firstPage + pagesCompleted),
                                            kappa_Table[tIndex].offset );

            size = 0; // reset size for next pages
        }
        tIndex++; //step to next line of table
    }
}

/************************************************************************

 FUNCTION:   aim_KappaIsDual

 DESCRIPTION:
   This function returns number of chamber of the device.


 FUNCTION RETURN:
   Bool: true if it id dual chamber. Otherwise is false

***********************************************************************
*/
bool aim_KappaIsDual(void)
{
    if(aiv_KappaSpecificDeviceTableA[aiv_specificKappaDeviceTableIndex].chambered == "D")
    {
        return true;
    }
    else
    {
        return false;
    }
}


/*
***********************************************************************

 FUNCTION:   aim_KappaSetEGMModeGain

 DESCRIPTION:
This function sets telemetry type to passed type and also set EGM gain based
on the passed in telemetry type if the device is a dual
chambered device by issuing the special command Accept Telemetry Type.


 FUNCTION CONSTANTS:

   AIC_ATRIAL_EGM_MODE
     Pacing mode encode value of 0x00
   AIC_VENTRI_EGM_MODE
     Pacing mode encode vakue of 0x01
   AIC_SUMMED_EGM_MODE
     Pacing mode encode value of 0x03

   AIC_AEGM_GAIN
     Pacing mode encode value of 0x60 (7.5 mV).
   AIC_VEGM_GAIN
     Pacing mode encode value of 0x20 (15 mV)
   AIC_SEGM_GAIN
     Pacing mode encode vakue of 0x60 (7.5 mV)

   AIC_KAPPA_UPLINK_PAGE_SIZE
     Size of an uplinked page including parity byte.

   AIC_PROCESSACK
     Expecting an uplink that returns an ACK.

 FUNCTION PARAMETERS:
   telemType
     Analog telemetry type set EGM type to the passed in telemetry type


***********************************************************************
*/

void aim_KappaSetEGMModeGain(char telemType)
{
    char   dlBuffer[AIC_KAPPA_MAX_DL_PRE_PARITY_SIZE];
    char   dlBufferWithParity[AIC_KAPPA_MAX_DOWNLINK_SIZE];
    USHORT totalSize     = 0;
    USHORT size          = 0;


    //if the device is dual chambered and the device is not at ERI
    //program the Analog Telemetry Type to passed in EGM type and
    //the corresponding gain and downlink accept telemetry type special command
    //(used to force the analog telemetry type and gain commands to occur immediately)
    if(aim_KappaIsDual() && !(aim_KappaCheckERIStatus()) )
    {
        // header
        dlBuffer[size++] = aiv_workingKappaDevice;         //family id code
        dlBuffer[size++] = (aiv_workingKappaSubModelId << 4); //submodel and command code

        // Set Analog Telemetry Type to passed in type and corresponding egm gain
        dlBuffer[size++] = (0xC0 | 0x11);           //format: <bit 7>, more records follow (1=more records)
                                                    //        <bit 6 - 5>, type of operation (10=store mask command)
                                                    //        <bit 4 - 0>, page offset where Analog Telemetry Type is located
        dlBuffer[size++] = 0x06;                    //page - page in memory where Analog Telemetry Type is located

        // Set EGM gain base on the telemetry type and analog tememetry type
        // in memory value - value to be programmed
        if (telemType == AIC_ATRIAL_EGM_MODE)
        {
            dlBuffer[size++] = (AIC_AEGM_GAIN | telemType);
        }
        else if (telemType == AIC_VENTRI_EGM_MODE)
        {
            dlBuffer[size++] = (AIC_VEGM_GAIN | telemType);
        }
        else if (telemType == AIC_SUMMED_EGM_MODE)
        {
             dlBuffer[size++] = (AIC_SEGM_GAIN | telemType);
        }


        dlBuffer[size++] = 0xE3;                    //mask - mask to use (egm telemetry type (0x83) and Gain (0x60)
                                                    // Change segment and downlink Accept Telemetry Type special command
        dlBuffer[size++] = 0x80;                    //format: <bit 7>, more records follow (1=more records)
                                                    //        <bit 6 - 5>, type of operation (00=segment select command)
                                                    //        <bit 4 - 0>, reserved
        dlBuffer[size++] = 0xff;                    //segment number, 255
        dlBuffer[size++] = (0x20 | 0x01);           //format: <bit 7>, more records follow (0=no more records)
                                                    //        <bit 6 - 5>, type of operation (01=special command)
                                                    //        <bit 4 - 0>, page offset where Accept Telemetry Type is located
                                                    //        con. byte and IPG mem offset)
        dlBuffer[size++] = 0x00;                    //page - page in memory where Analog Telemetry Type is located
        dlBuffer[size++] = 0x00;                    //memory value - value to be programmed


        totalSize = aim_KappaAddParity(dlBuffer, dlBufferWithParity, size);

        aim_KappaSendTelemetryA(dlBufferWithParity, totalSize,
                                aiv_ulKappa, AIC_ACK_UPLINK_SIZE, AIC_PROCESSACK);
    }
    else
    {
        bsm_EHLog("Single Chamber or Dual Chamber and device is in ERI. No telemetry type and gain are programmed.", 0);
    }
}

/************************************************************************

 FUNCTION:   aim_KappaGetPermPacingMode

 DESCRIPTION:
This function returns the permanent pacing mode byte of the
device.

 FUNCTION CONSTANTS:
   AIC_KAPPA_UPLINK_PAGE_SIZE
     Size of an uplinked page including parity byte.
   AIC_DO_NOT_PROCESSACK
     Not expecting an uplink that returns an ACK.

 FUNCTION RETURN:
   Byte containing permanent pacing mode.

***********************************************************************
*/
char aim_KappaGetPermPacingMode(void)
{
    char   dlBuffer[AIC_KAPPA_MAX_DL_PRE_PARITY_SIZE];
    char   dlBufferWithParity[AIC_KAPPA_MAX_DOWNLINK_SIZE];
    char   permPacingMode;
    USHORT totalSize = 0;
    USHORT size      = 0;

    //get permanent pacing mode
    dlBuffer[size++] = aiv_workingKappaDevice;            //family id code
    dlBuffer[size++] = (aiv_workingKappaSubModelId << 4); //submodel and command code
    dlBuffer[size++] = 0x00;                              //control byte
    dlBuffer[size++] = 0x02;                              //page to uplink

    totalSize        = aim_KappaAddParity(dlBuffer, dlBufferWithParity, size);

    aim_KappaSendTelemetryA(dlBufferWithParity, totalSize,
                            aiv_ulKappa, AIC_ONE_PAGE_UPLINK_SIZE, AIC_DO_NOT_PROCESSACK); // timeout

    permPacingMode = aiv_ulKappa[AIC_KAPPA_HEADER + 0x1C]; //header + offset

    return(permPacingMode);
}


/************************************************************************

 FUNCTION:   aim_KappaGetTempPacingMode

 DESCRIPTION:
 This function returns the Temp pacing mode byte of the
 device.

 FUNCTION CONSTANTS:
   AIC_KAPPA_UPLINK_PAGE_SIZE
     Size of an uplinked page including parity byte.
   AIC_DO_NOT_PROCESSACK
     Not expecting an uplink that returns an ACK.

 FUNCTION RETURN:
   Byte containing permanent pacing mode.

***********************************************************************
*/
char aim_KappaGetTempPacingMode(void)
{
    char   dlBuffer[AIC_KAPPA_MAX_DL_PRE_PARITY_SIZE];
    char   dlBufferWithParity[AIC_KAPPA_MAX_DOWNLINK_SIZE];
    char   tempPacingMode;
    USHORT totalSize = 0;
    USHORT size      = 0;


    //get permanent pacing mode
    dlBuffer[size++] = aiv_workingKappaDevice;            //family id code
    dlBuffer[size++] = (aiv_workingKappaSubModelId << 4); //submodel and command code
    dlBuffer[size++] = 0x00;                              //control byte
    dlBuffer[size++] = 0x02;                              //page to uplink

    totalSize = aim_KappaAddParity(dlBuffer, dlBufferWithParity, size);

    aim_KappaSendTelemetryA(dlBufferWithParity, totalSize,
                            aiv_ulKappa, AIC_ONE_PAGE_UPLINK_SIZE, AIC_DO_NOT_PROCESSACK); // timeout

    tempPacingMode = aiv_ulKappa[AIC_KAPPA_HEADER + 0x02]; //header + offset

    return(tempPacingMode);
}

/************************************************************************

 FUNCTION:   aim_KappaSetMarkerArrayType

 DESCRIPTION:
This function is used by aim_KappaRTT() to determine and return the
appropriate array of markers to be sent for performing RTT.
The Carelink Monitor must synchronize the RTT special command to occur immediately
after a Ventricular event (paced, sense, or triggered) in DXX or VXX mode and
immediately after an Atrial event (pace, sense, or triggered) in AXX mode.
The function first gets the permanent pacing mode from the IPG and determines whether
the IPG is in a single chamber pacing mode, a dual ventricular pacing mode,
or a dual atrial pacing mode. Each pacing mode within the IPG has a cooresponding
set of hexidecimal values that represent possible markers (such as VP, AS, etc)
that can occur while in that mode.  So once we determine the permanent pacing
mode of the IPG we send the matching set of hex-represented markers to
tam_RTT_Send_Telemetry in KappaRTT().  In the tam code the Monitor waits until it
sees one of these markers and when it does the RTT Special Command is initiated.

 FUNCTION CONSTANTS:

   AIC_AXX_MODE_ARRAY
     Array of Atrial modes.

   AIC_A_MARKER_ARRAY
     Array of Atrial markers.

   AIC_V_MARKER_ARRAY
     Array of Ventricular markers.

   AIC_SINGLE_CHAMBER_MARKER_ARRAY
     Array of Single chamber A. and V. markers.

 FUNCTION RETURN:
   Array of either: dual chamber atrial markers, dual chamber ventricular
   markers, or single chamber a. and v. markers.

************************************************************************/
#define AIC_AXX_MARKER_ARRAY_SIZE                    10
#define AIC_VXX_MARKER_ARRAY_SIZE                    11
#define AIC_SINGLE_CHAMBER_AXX_VXX_MARKER_ARRAY_SIZE 5

//DUAL CHAMBER ATRIAL_MARKERS
static char AIC_A_MARKER[AIC_AXX_MARKER_ARRAY_SIZE] = {
    0x02, 0x08, 0x0A, 0x10, 0x18,
    0x22, 0x28, 0x30, 0x32, 0x3A
};
//DUAL CHAMBER VENTRICULAR_MARKERS
char AIC_V_MARKER[AIC_VXX_MARKER_ARRAY_SIZE] = {
    0x03, 0x1B, 0x01, 0x11,
    0x21, 0x29, 0x31, 0x3B, 0x0B, 0x2b, 0x23
};
//SINGLE CHAMBER A. AND V. MARKERS
char AIC_SINGLE_CHAMBER_MARKER[AIC_SINGLE_CHAMBER_AXX_VXX_MARKER_ARRAY_SIZE] =
{0x03, 0x23, 0x01, 0x31, 0x3B };

//DUAL CHAMBER ATRIAL MODES
char AIC_AXX_MODE[] = {
    0x02, /* AOO */ 0x12, /* AAI */ 0x1A, /* AAT */ 0x82,    /* AOOR */
    0x92, /* AAIR */ 0x32, /* ADI */ 0xB2   /* ADIR */
};

void aim_KappaSetMarkerArrayType(bool *modeFound, char **p_markerArray)
{
    USHORT n;
    bool   found = false;
    char   permPacingMode;

   
    permPacingMode = aim_KappaGetPermPacingMode();

    if( (permPacingMode == 0x10) || /*OAO*/
        (permPacingMode == 0x20) || /*OVO*/
        (permPacingMode == 0x30) ) /*ODO*/
    {
        *modeFound = false; //invalid mode, do not perform RTT
    }
    else
    {
        *modeFound = true;
        //if dual chamber device
        if(aiv_KappaSpecificDeviceTableA[aiv_specificKappaDeviceTableIndex].chambered == "D")
        {
            for(n=0; n < (sizeof(AIC_AXX_MODE)); n++)
            { //check to see if the dual chamber device is in atrial pacing mode
                if(permPacingMode == AIC_AXX_MODE[n])
                {
                    aiv_markerArraySize = AIC_AXX_MARKER_ARRAY_SIZE;
                    *p_markerArray      = AIC_A_MARKER;
                    found               = true;
                    break;
                }
            }
            //if not atrial pacing, then the device is either pacing in both chambers or
            //in just the ventricle, in both cases, we send the same array of markers
            if(!found)
            {
                aiv_markerArraySize = AIC_VXX_MARKER_ARRAY_SIZE;
                *p_markerArray      = AIC_V_MARKER;
            }
        }
        //else the device is a single chamber device, send corresponding marker array
        else
        {
            aiv_markerArraySize = AIC_SINGLE_CHAMBER_AXX_VXX_MARKER_ARRAY_SIZE;
            *p_markerArray      = AIC_SINGLE_CHAMBER_MARKER;
        }
    }

}

/************************************************************************

 FUNCTION:   aim_KappaRTT

 DESCRIPTION:
This function assembles downlink for performing RTT Measurement Sequence.
It begins by downlinking a request for permanent amplitude, permanent pulse width,
and permanent pace polarity parameter values. For each of these 3 uplinked
parameters it checks to determine if it is in the appriopriate range. If so,
the corresponding temporary  parameter in the IPG is set to the value of the
permanent parameter. If not, the temporary parameter in the IPG is set to a
value that is acceptable for performing RTT (per product specification,
commented in function below).
The Carelink Monitor must synchronize the RTT special command to occur immediately
after a Ventricular event in DXX or VXX mode and immediately after an Atrial event
in AXX mode. To accomplish this, aim_KappaSetMarkerArrayType() uses the
current mode of the device to return the appropriate array of markers to
be sent to the TAM code via aim_KappaRTTSendTelemetry(). The TAM code waits
for an event to occur, sets the temporary values, and implements the request
for Measured Data special command.

 FUNCTION CONSTANTS:

   AIC_KAPPA_UPLINK_PAGE_SIZE
     Size of an uplinked page including parity byte.

   AIC_DO_NOT_PROCESSACK
     Not expecting an uplink that returns an ACK.

   AIC_KAPPA_HEADER
     First 2 bytes of kappa uplink, consists of Family ID and command code.

   AIC_AV_BIPOLAR_MANUAL
     Encode value for both atrial and ventricular bipolar manual. Equals 0x00.

   AIC_A_UNIPOLAR_MANUAL
     Encode value for atrial unipolar manual. Equals 0x01.

   AIC_V_UNIPOLAR_MANUAL
     Encode value for ventricular unipolar manual. Equals 0x10.

   AIC_AMPLITUDE_FIVE_VOLTS
     Encode value for amplitude of five volts. Equals 0x19.

************************************************************************/
void aim_KappaRTT(void)
{
    char AAmplitude;
    char VAmplitude;
    char APulseWidth;
    char VPulseWidth;
    char APacePolarity;
    char VPacePolarity;
    char AVPacePolarity;
    bool modeFound    = false;
    bool eriStatus    = true;
    bool aConfigure   = false;
    bool vConfigure   = false;
    bool invalidValue = false;

    char   *p_markerArray;
    char   dlBuffer[AIC_KAPPA_MAX_DL_PRE_PARITY_SIZE];
    char   dlBufferWithParity[AIC_KAPPA_MAX_DOWNLINK_SIZE];
    USHORT totalSize = 0;
    USHORT size      = 0;

    //get permanent amplitude, pulsewidth, and pace polarity
    dlBuffer[size++] = aiv_workingKappaDevice;           //family id code
    dlBuffer[size++] = (aiv_workingKappaSubModelId << 4); //submodel and command code
    dlBuffer[size++] = 0x00;                             //control byte
    dlBuffer[size++] = 0x02;                             //first page to uplink

    totalSize        = aim_KappaAddParity(dlBuffer, dlBufferWithParity, size);

    aim_KappaSendTelemetryA(dlBufferWithParity, totalSize,
                            aiv_ulKappa, AIC_ONE_PAGE_UPLINK_SIZE, AIC_DO_NOT_PROCESSACK);

    //store current/permanent values from device
    AAmplitude    = (aiv_ulKappa[AIC_KAPPA_HEADER + 0x17] & 0xff); //[offset] & mask
    VAmplitude    = (aiv_ulKappa[AIC_KAPPA_HEADER + 0x18] & 0xff); //[offset] & mask
    APulseWidth   = (aiv_ulKappa[AIC_KAPPA_HEADER + 0x1E] & 0xf0); //[offset] & mask
    VPulseWidth   = (aiv_ulKappa[AIC_KAPPA_HEADER + 0x1F] & 0xf0); //[offset] & mask
    APacePolarity = (aiv_ulKappa[AIC_KAPPA_HEADER + 0x19] & 0x03); //[offset] & mask
    VPacePolarity =(aiv_ulKappa[AIC_KAPPA_HEADER + 0x19] & 0x30); //[offset] & mask

    //Check for invalid parameter values
    // if( (AAmplitude || VAmplitude) < 0x00 ) - we don't need this case because
    //the variables are unsigned short and can not be set less then zero
    if( (AAmplitude > 0x1C) || (VAmplitude > 0x1C)  )
    {
        invalidValue = true;
    }

    //if( (APulseWidth || VPulseWidth) < 0x00)  - we don't need this case because
    //the variables are unsigned short and can not be set less then zero
    if( (APulseWidth > 0xF0) || (VPulseWidth > 0xF0) )
    {
        invalidValue = true;
    }
    if( (APacePolarity != 0x00) &&
        (APacePolarity != 0x01) &&
        (APacePolarity != 0x02) )
    {
        invalidValue = true;
    }
    if( (VPacePolarity != 0x00) &&
        (VPacePolarity != 0x10) &&
        (VPacePolarity != 0x20) )
    {
        invalidValue = true;
    }

    if(invalidValue == true)
    { //invalid value, do not perform RTT
        aiv_DataValidStatusBit = false;
    }

    else
    {
        //determine A. and V. amplitude encode value
        //if perm amplitude is less then 5.0 volts then set temp equal to 5.0 volts
        if (AAmplitude < AIC_AMPLITUDE_FIVE_VOLTS)
            AAmplitude = AIC_AMPLITUDE_FIVE_VOLTS;
        if (VAmplitude < AIC_AMPLITUDE_FIVE_VOLTS)
            VAmplitude = AIC_AMPLITUDE_FIVE_VOLTS;

        //determine A. and V. pulse width encode value
        //if perm pulse width is less then 1.0 ms set temp equal to 1.0 ms
        if(APulseWidth <= 0xD0)
            APulseWidth = 0x0D;
        else
            APulseWidth = (APulseWidth >> 4);

        if(VPulseWidth <= 0xD0)
            VPulseWidth = 0x0D;
        else
            VPulseWidth = (VPulseWidth >> 4);

        // determine A. and V. pace polarity Encode value
        // set temp pace polarity to Bipolar Manual (if permanent value is either Bipolar Manual
        // or Autopace) or Unipolar Manual (if permanent value is Unipolar Manual)
        if( (VPacePolarity == AIC_V_UNIPOLAR_MANUAL) &&
            (APacePolarity == AIC_A_UNIPOLAR_MANUAL) )

            AVPacePolarity = (AIC_V_UNIPOLAR_MANUAL  | AIC_A_UNIPOLAR_MANUAL);

        else if( ((APacePolarity == AIC_AV_BIPOLAR_MANUAL) ||
                  (APacePolarity == AIC_A_AUTOPACE)) &&
                 ((VPacePolarity == AIC_AV_BIPOLAR_MANUAL) ||
                  (VPacePolarity == AIC_V_AUTOPACE)) )

            AVPacePolarity = AIC_AV_BIPOLAR_MANUAL;

        else if( (APacePolarity == AIC_AV_BIPOLAR_MANUAL) ||
                 (APacePolarity == AIC_A_AUTOPACE) )

            AVPacePolarity = AIC_V_UNIPOLAR_MANUAL;

        else if( (VPacePolarity == AIC_AV_BIPOLAR_MANUAL) ||
                 (VPacePolarity == AIC_V_AUTOPACE) )

            AVPacePolarity = AIC_A_UNIPOLAR_MANUAL;
        else
            bsm_EHLock("In aim_KappaRTT: Error setting Polarity for RTT.");

        //header
        size             = 0;
        dlBuffer[size++] = aiv_workingKappaDevice;          // family id code
        dlBuffer[size++] = (aiv_workingKappaSubModelId << 4); //submodel
        // set temporary amplitude values
        dlBuffer[size++] = (0xE0 | 0x0E); //(store mask | IPG mem offset)
        dlBuffer[size++] = 0x02;       // page
        dlBuffer[size++] = 0x02;       // number of contigous bytes
        dlBuffer[size++] = AAmplitude; // value
        dlBuffer[size++] = VAmplitude; // value

        //set temporary polarity values
        dlBuffer[size++] = (0xC0 | 0x10); //(store mask | IPG mem offset)
        dlBuffer[size++] = 0x02;        // page
        dlBuffer[size++] = AVPacePolarity; // value
        dlBuffer[size++] = 0x33;        //mask

        //set temporary A. Pulse Width
        dlBuffer[size++] = (0xC0 | 0x04); //(store mask | IPG mem offset)
        dlBuffer[size++] = 0x02;        // page
        dlBuffer[size++] = APulseWidth; // value, 1.0 ms
        dlBuffer[size++] = 0x0f;        // mask value

        //set temporary V. Pulse Width
        dlBuffer[size++] = (0xC0 | 0x05); //(store mask | IPG mem offset)
        dlBuffer[size++] = 0x02;        // page
        dlBuffer[size++] = VPulseWidth; // value, 1.0 ms
        dlBuffer[size++] = 0x0f;        // mask value

        //downlink Request Measured Data special command
        dlBuffer[size++] = 0x80;        //control byte, more recs. to follow
        dlBuffer[size++] = 0xff;        //segment select
        dlBuffer[size++] = (0x20 | 0x09); //con. byte and IPG mem offset)
        dlBuffer[size++] = 0x00;        //num of pages
        dlBuffer[size++] = 0x00;        //mem value

        totalSize        = aim_KappaAddParity(dlBuffer, dlBufferWithParity, size);

        aim_KappaSetMarkerArrayType(&modeFound, &p_markerArray);

        if(modeFound == true)
        {
            aim_KappaRTTSendTelemetry(p_markerArray, aiv_markerArraySize,
                                      dlBufferWithParity, totalSize);
        }
        else
        { //Mode is OVO, OAO, or ODO so we do not run RTT
            aiv_DataValidStatusBit = false;
        }
    }
}
/***********************************************************************

 FUNCTION:      aim_KappaCollectWaveformDataA

 DESCRIPTION:
Collect Telemetry A waveform data and save in the file. If a telemetry
failure occurs attempt to re-establish with aim_KappaResumeTelemetryA()
- this will shut the system down if telemetry can not be restored in
a specific amount of time.  After resuming telemetry set magnet mode again.

 FUNCTION CONSTANTS:

   AIC_A_KAPPA_EGM_BYTES_PER_SECOND
     Number of EGM bytes/sec.

   AIC_KAPPA_SINGLE_EGM_SECONDS/AIC_KAPPA_DUAL_EGM_SECONDS
     Number of seconds to collect waveform.

 FUNCTION PARAMETERS:
   magnetModeStatus
     Determines status of magnet mode, either "On" or "Off".
   collectionSeconds
     Number of seconds to collect waveform
   setTelemType
     Determines the need to set telemetry type.
   telemType
     Telemetry Type, AEGM, VEGM and SEGM.
   *currEgmSeconds
     pointer to current EGM colleced time in seconds
   prevEgmSeconds
     Previous EGM collected time in seconds
   *egmCollected
     pointer to a flag that indicates EGM collected or failed

************************************************************************/
bool aim_KappaCollectWaveFormDataA(char magnetModeStatus,
                                   char collectionSeconds,
                                   char telemType,
                                   unsigned long egmTicks,
                                   bool *deviceIsDDIR )
{
    bool          warningOccurred         = false;
    tat_status    status;
    USHORT        receivedUplinkSize      = 0;
    USHORT        startEGMCollectionIndex = 0;
    unsigned long egmTimeInMagnetMode     = 0;
    USHORT        expectedNumberEGMBytes  = 0;
    bool          egmCollected            = true;


    // Magnet mode waveform collection should not be more than 72 seconds for the whole waveform collection
    if(magnetModeStatus == AIC_MAGNET_MODE_ON)
    {
        egmTimeInMagnetMode = (NU_Retrieve_Clock() - egmTicks)/100;

        if(egmTimeInMagnetMode >= 72 )
        {
             bsm_EHLog("Magnet mode waveform collection timedout.", 0);
             egmCollected = false;
             return egmCollected;
        }
    }

    aim_KappaSetEGMModeGain(telemType);

    if ( magnetModeStatus == AIC_MAGNET_MODE_OFF)
    {
        if ( *deviceIsDDIR == true )
        {
            // Set pacing mode to DDIR if it has already in DDIR to prevent modeswitch in non-magnet mode
            bsm_EHLog("Non-magnet mode and device is in DDIR mode. Set temp pacing to DDIR.",0);
            aim_KappaSetPacingMode(AIC_DDIR_MODE);
        }
    }
    else
    {
         // Set magnet mode on
        aim_KappaSetMagnetMode(magnetModeStatus);
    }

    // Initialize waveform buffer
    memset(aiv_KappaWaveformData, 0, sizeof(aiv_KappaWaveformData));


    // The tam function will not exceed expectedNumberEGMBytes which
    // is calculated based on bytes/sample and samples/second.
    do {
           if(magnetModeStatus == AIC_MAGNET_MODE_OFF)
               bsm_SDPrint("Non-magnet mode waveform collection started.");
           else
               bsm_SDPrint("Magnet mode waveform collection started.");

#ifdef DSP_2490_SIMULATION
           warningOccurred = false;
        break;
#else

           status  = tam_Continuous_Egm((char *)aiv_KappaWaveformData, collectionSeconds,
                                         &receivedUplinkSize, &startEGMCollectionIndex, false);

           expectedNumberEGMBytes = (collectionSeconds * AIC_A_KAPPA_EGM_BYTES_PER_SECOND);

           if ( (status != tac_successful) ||
                (receivedUplinkSize < expectedNumberEGMBytes ) )
           {

               uim_TelemetryWarning(on);
               warningOccurred = true;
               aim_KappaResumeTelemetryA();

               egmTimeInMagnetMode = (NU_Retrieve_Clock() - egmTicks)/100;

               if((magnetModeStatus == AIC_MAGNET_MODE_ON) &&
                   (egmTimeInMagnetMode >= 72 ))
               {    // We do not want to be in magnet mode for more then 72 seconds for the whole waveform collection
                    // quit trying to get magnet-egm and continue
                    bsm_EHLog("Magnet mode timed out.", 0);
                    egmCollected = false;

                    break;
               }

               aim_KappaSetEGMModeGain(telemType);

               if( magnetModeStatus == AIC_MAGNET_MODE_OFF)
               {
                  if( *deviceIsDDIR == true )
                  {
                      // Set pacing mode to DDIR if it has already in DDIR to prevent modeswitch in non-magnet mode
                      bsm_EHLog("Non-magnet mode and device is in DDIR mode. Set temp pacing to DDIR.",0);
                      aim_KappaSetPacingMode(AIC_DDIR_MODE);
                  }
               }
               else
               {
                   // Set magnet mode on
                   aim_KappaSetMagnetMode(magnetModeStatus);
               }

        } else
            break;
#endif
    } while (1);

    if (warningOccurred)
        uim_TelemetryWarning(OFF);


    if(egmCollected)
    {
        receivedUplinkSize = expectedNumberEGMBytes;

        fsm_WriteKappaWaveformFileSection(magnetModeStatus,
                                          receivedUplinkSize,
                                          expectedNumberEGMBytes, //The size dependes on single or dual chamber device
                                          //this index is in frames, mult by 2 to get actual start index
                                          (startEGMCollectionIndex *2),
                                          telemType,
                                          aiv_KappaWaveformData,
                                          aim_KappaGetModeGainByte());
    }

    return egmCollected;
}


/***********************************************************************

 FUNCTION:      aim_KappaCollectWaveform

 DESCRIPTION:
Collect Telemetry A waveform data and save in the file. For single chamber device
it will collect 30 sec in non-magnet mode and 3 sec in magnet mode. For dual
chamber device, it will collect each of telemetry type AEGM, VEGM, and SEGM for
7 sec in non magnet mode and each of telemetry type for 7 sec in magnet mode.

 FUNCTION CONSTANTS:

   AIC_KAPPA_NUMBER_OF_EGM_BYTES
     Number of EGM bytes. Calculated based on bytes/sample and samples/second.

   AIC_KAPPA_SINGLE_EGM_SECONDS/AIC_KAPPA_DUAL_EGM_SECONDS
     Number of seconds to collect waveform.

 FUNCTION PARAMETERS:
   magnetModeStatus
     Determines status of magnet mode, either "On" or "Off".

************************************************************************/
void aim_KappaCollectWaveform(void)
{
    unsigned long egmTicks = 0;
    bool egmCollected = true;
    bool deviceIsDDIR = false;

    if(aim_KappaIsDual())
    {
       bsm_EHLog("Dual Chamber, Non-Magnet Mode",0);

       // Special flag to set temp pacing mode for device a with perm mode DDDR in AT/AF
       if (aim_KappaGetTempPacingMode() == AIC_DDIR_MODE)
       {
           bsm_EHLog("Device is in DDIR perm mode and patient is in AT/AF", 0);
           deviceIsDDIR = true;
       }

       bsm_EHLog("AEGM", 0);
       egmCollected = aim_KappaCollectWaveFormDataA(AIC_MAGNET_MODE_OFF,
                                     AIC_KAPPA_DUAL_EGM_SECONDS,
                                     AIC_ATRIAL_EGM_MODE,
                                     egmTicks,
                                     &deviceIsDDIR);

       bsm_EHLog("VEGM", 0);
       egmCollected = aim_KappaCollectWaveFormDataA(AIC_MAGNET_MODE_OFF,
                                      AIC_KAPPA_DUAL_EGM_SECONDS,
                                      AIC_VENTRI_EGM_MODE,
                                      egmTicks,
                                      &deviceIsDDIR);

       bsm_EHLog("SEGM", 0);
       egmCollected = aim_KappaCollectWaveFormDataA(AIC_MAGNET_MODE_OFF,
                                      AIC_KAPPA_DUAL_EGM_SECONDS,
                                      AIC_SUMMED_EGM_MODE,
                                      egmTicks,
                                      &deviceIsDDIR);

       uim_IlluminateLED(AIC_LED2); //Non magnet waveform complete, set 2nd light=blinking

       bsm_EHLog("Dual Chamber, Magnet Mode", 0);

       // Get a starting tick time of magnet mode collection to track total magnet mode collection time
       egmTicks = NU_Retrieve_Clock();
       bsm_EHLog("AEGM", 0);
       egmCollected = aim_KappaCollectWaveFormDataA(AIC_MAGNET_MODE_ON,
                                                    AIC_KAPPA_DUAL_EGM_SECONDS,
                                                    AIC_ATRIAL_EGM_MODE,
                                                    egmTicks,
                                                    &deviceIsDDIR);

       // if AEGM collection was successful then try VEGM
       if (egmCollected)
       {
           bsm_EHLog("VEGM", 0);
           egmCollected = aim_KappaCollectWaveFormDataA(AIC_MAGNET_MODE_ON,
                                                        AIC_KAPPA_DUAL_EGM_SECONDS,
                                                        AIC_VENTRI_EGM_MODE,
                                                        egmTicks,
                                                       &deviceIsDDIR);
           // if VEGM collection was successful then try SEGM
           if (egmCollected)
           {
               bsm_EHLog("SEGM", 0);
               egmCollected = aim_KappaCollectWaveFormDataA(AIC_MAGNET_MODE_ON,
                                                            AIC_KAPPA_DUAL_EGM_SECONDS,
                                                            AIC_SUMMED_EGM_MODE,
                                                            egmTicks,
                                                            &deviceIsDDIR);
               // if SEGM collection was successful
               if (!egmCollected)
               {
                   bsm_EHLog("Unable to collect SEGM.", 0);
               }
           }
           else
           {
               bsm_EHLog("Unable to collect VEGM. Collection of SEGM will NOT be attempted.", 0);
           }

       }
       else
       {
           bsm_EHLog("Unable to collect AEGM. Collection of VEGM and SEGM will NOT be attempted.", 0);
       }

    }
    else // Single chamber magnet mode egm
    {
       bsm_EHLog("Single Chamber, Non-Magnet Mode",0);
       egmCollected = aim_KappaCollectWaveFormDataA(AIC_MAGNET_MODE_OFF,
                                                    AIC_KAPPA_SINGLE_EGM_SECONDS,
                                                    AIC_DONT_CARE_MODE,
                                                    egmTicks,
                                                    &deviceIsDDIR);
       //Non magnet waveform complete, set 2nd light=blinking
       uim_IlluminateLED(AIC_LED2);

       bsm_EHLog("Single Chamber, Magnet Mode",0);

       // Get a starting tick time of magnet mode collection to track total magnet mode collection time
       egmTicks = NU_Retrieve_Clock();
       egmCollected = aim_KappaCollectWaveFormDataA(AIC_MAGNET_MODE_ON,
                                                    AIC_KAPPA_SINGLE_EGM_SECONDS,
                                                    AIC_DONT_CARE_MODE,
                                                    egmTicks,
                                                    &deviceIsDDIR);
       if (!egmCollected)
       {
           bsm_EHLog("Unable to collect magnet mode waveform.", 0);
       }
    }

 }



/************************************************************************

 FUNCTION:   aim_KappaSetMagnetMode

 DESCRIPTION:
This function controls the state of Magnet Mode.  When receiving input of
AIC_MAGNET_MODE_ON it calls specical command to Restore Magnet. When
having input of AIC_MAGNET_MODE_OFF it Returns to Permanent.

 FUNCTION CONSTANTS:
   AIC_KAPPA_UPLINK_PAGE_SIZE
     Size of an uplinked page including parity byte.
   AIC_PROCESSACK
     Expecting an uplink that returns an ACK.

 FUNCTION PARAMETERS:
   magnetModeStatus
     Passed in Special command downlink to device. Sets magnet mode to
     either "Restore Magnet" (ON) OR "Return to Permanent" (OFF).

************************************************************************/
void aim_KappaSetMagnetMode(char magnetModeStatus)
{
    char   dlBuffer[AIC_KAPPA_MAX_DL_PRE_PARITY_SIZE];
    char   dlBufferWithParity[AIC_KAPPA_MAX_DOWNLINK_SIZE];
    USHORT size      = 0;
    USHORT totalSize = 0;

    //header
    dlBuffer[size++] = aiv_workingKappaDevice;            // family id code
    dlBuffer[size++] = (aiv_workingKappaSubModelId << 4); //submodel and com. code

    //Special Command - sets mag mode to magnetModeStatus ("On" or "Off")
    dlBuffer[size++] = 0x80;            // control byte, more recs. to follow
    dlBuffer[size++] = 0xff;            //segment select
    dlBuffer[size++] = (0x20 | magnetModeStatus);   //con. byte and IPG mem offset)
    dlBuffer[size++] = 0x00;            //num of pages
    dlBuffer[size++] = 0x00;            //mem value

    totalSize        = aim_KappaAddParity(dlBuffer, dlBufferWithParity, size);

    aim_KappaSendTelemetryA(dlBufferWithParity, totalSize,
                            aiv_ulKappa, AIC_ACK_UPLINK_SIZE, AIC_PROCESSACK);

}

/************************************************************************

 FUNCTION:   aim_KappaSetPacingMode(char pacingMode)

 DESCRIPTION:
 This function controls the temp pacing mode.

 FUNCTION CONSTANTS:
   AIC_KAPPA_UPLINK_PAGE_SIZE
     Size of an uplinked page including parity byte.
   AIC_PROCESSACK
     Expecting an uplink that returns an ACK.

 FUNCTION PARAMETERS:
   pacingMode
     Passed in Special command downlink to device. Sets temp pacing mode to
     passed in value.

************************************************************************/
void aim_KappaSetPacingMode(char pacingMode)
{
    char   dlBuffer[AIC_KAPPA_MAX_DL_PRE_PARITY_SIZE];
    char   dlBufferWithParity[AIC_KAPPA_MAX_DOWNLINK_SIZE];
    USHORT size      = 0;
    USHORT totalSize = 0;

    //header
    dlBuffer[size++] = aiv_workingKappaDevice;          // family id code
    dlBuffer[size++] = (aiv_workingKappaSubModelId << 4); //submodel and com. code

    //set pacing mode values
    dlBuffer[size++] = (0x40 | 0x02); //(store mask | IPG mem offset)
    dlBuffer[size++] = 0x02;        // page
    dlBuffer[size++] = pacingMode; // value
    dlBuffer[size++] = 0xFF;        //mask

    totalSize        = aim_KappaAddParity(dlBuffer, dlBufferWithParity, size);

    aim_KappaSendTelemetryA(dlBufferWithParity, totalSize,
                            aiv_ulKappa, AIC_ACK_UPLINK_SIZE, AIC_PROCESSACK);

}

/************************************************************************

 FUNCTION:   aim_KappaGetModeGainByte

 DESCRIPTION:
This function returns the Mode/Gain byte of the
device.  This byte is passed to FSM code for the waveform header.

 FUNCTION CONSTANTS:
   AIC_KAPPA_UPLINK_PAGE_SIZE
     Size of an uplinked page including parity byte.
   AIC_DO_NOT_PROCESSACK
     Not expecting an uplink that returns an ACK.

 FUNCTION RETURN:
   Byte containing Mode/Gain.

***********************************************************************
*/
char aim_KappaGetModeGainByte(void)
{
    char   dlBuffer[AIC_KAPPA_MAX_DL_PRE_PARITY_SIZE];
    char   dlBufferWithParity[AIC_KAPPA_MAX_DOWNLINK_SIZE];
    USHORT totalSize = 0;
    USHORT size      = 0;

    //get Mode/Gain byte
    dlBuffer[size++] = aiv_workingKappaDevice;           //family id code
    dlBuffer[size++] = (aiv_workingKappaSubModelId << 4); //submodel and command code
    dlBuffer[size++] = 0x00;                        //control byte
    dlBuffer[size++] = 0x06;                        //first page to uplink

    totalSize        = aim_KappaAddParity(dlBuffer, dlBufferWithParity, size);

    aim_KappaSendTelemetryA(dlBufferWithParity, totalSize,
                            aiv_ulKappa, AIC_ONE_PAGE_UPLINK_SIZE, AIC_DO_NOT_PROCESSACK);

    //return Mode/Gain byte
    return( (aiv_ulKappa[AIC_KAPPA_HEADER + 0x11])  ); //[offset]
}

/************************************************************************

 FUNCTION:   aim_KappaGetCompleteSNString

 DESCRIPTION:
This function returns a pointer to the complete serial number (in hex-ascii
format)including radiopaque, and necessary leading zeros.

 FUNCTION CONSTANTS:

 FUNCTION PARAMETERS:

 FUNCTION RETURN
     char * to complete serial number string

************************************************************************/
char * aim_KappaGetCompleteSNString()
{
    return aiv_completeSNString;
}

/************************************************************************

 FUNCTION:   aim_KappaGetWorkingDeviceIDString

 DESCRIPTION:
 This function returns a pointer to the complete device id (in hex-ascii
 format).

 FUNCTION CONSTANTS:

 FUNCTION PARAMETERS:

 FUNCTION RETURN
     char * to device id string

************************************************************************/
char * aim_KappaGetWorkingDeviceIDString()
{
    return aiv_workingKappaDeviceIDString;
}

/************************************************************************

 FUNCTION:   aim_KappaGetInterrogationTimeDateString

 DESCRIPTION:
This function returns a pointer to the interrogation time date string.
The interrogation time date string is set by function aim_UpdateDateTime().

 FUNCTION CONSTANTS:

 FUNCTION PARAMETERS:

 FUNCTION RETURN
     char * to time date string

************************************************************************/
char * aim_KappaGetInterrogationTimeDateString()
{
    static char startTimeInterrogation[15] = {"XXXXXXXXXXXXXX"};

    return startTimeInterrogation;
}

/************************************************************************

 FUNCTION:   aim_KappaGetSerialNumber

 DESCRIPTION:
This function downlinks an 8 byte (6 byte message + 2 parity bytes) request
for the page containing the 6-digit portion of serial number.
The function aim_KappaAssembleSerialNumber() receives this serial number
as input and returns the complete serial number (in hex-ascii format)
including radiopaque, and necessary leading zeros.  The complete serail number is copied to memory.

 FUNCTION CONSTANTS:

   AIC_SERIAL_DOWNLINK_SIZE
      Size of serial number request downlink.

   AIC_SERIAL_EXPECTED_UPLINK
      Expected size of serial number uplink.

   AIC_KAPPA_UPLINK_PAGE_SIZE
     Size of an uplinked page including parity byte.

   AIC_KAPPA_HEADER
     First 2 bytes of kappa uplink, consists of Family ID and command code.

 FUNCTION PARAMETERS:
   p_serialNumber
      Serial number pointer.

 FUNCTION RETURN
   pass or fail - true/false
************************************************************************/
#define AIC_SERIAL_DL_SIZE_PARITY 6
#define AIC_SERIAL_DL_SIZE        4

bool aim_KappaGetSerialNumber(char *p_serialNumber, char* p_fwRev)
{
    tat_status status;
    char       dlSerialBuffer[AIC_SERIAL_DL_SIZE];
    char       dlSerialBufferWithParity[AIC_SERIAL_DL_SIZE_PARITY];
    char       serialUplink[AIC_ONE_PAGE_UPLINK_SIZE];
    char       sixDigitSN[10];

    USHORT tIndex     = 0;
    bool   returnCode = false;
    USHORT size       = 0;

    //header
    dlSerialBuffer[size++] = aiv_workingKappaDevice;        // family id code
    dlSerialBuffer[size++] = (aiv_workingKappaSubModelId << 4);  //submodel and com. code
    //serial number
    dlSerialBuffer[size++] = 0x00; //control byte
    dlSerialBuffer[size++] = 0x06; //1st page to uplink

    // Get whole page
    aim_KappaAddParity(dlSerialBuffer, dlSerialBufferWithParity, AIC_SERIAL_DL_SIZE);

#ifdef DSP_2490_SIMULATION
    serialUplink[0]  = 3;
    serialUplink[1]  = 131;
    serialUplink[2]  = 8;
    serialUplink[3]  = 2;
    serialUplink[4]  = 1;
    serialUplink[5]  = 0;
    serialUplink[6]  = 210;
    serialUplink[7]  = 186;
    serialUplink[8]  = 1;
    serialUplink[9]  = 99;
    serialUplink[10] = 6;
    serialUplink[11] = 64;
    serialUplink[12] = 4;
    serialUplink[13] = 13;
    serialUplink[14] = 5;
    serialUplink[15] = 31;
    serialUplink[16] = 18;
    serialUplink[17] = 64;
    serialUplink[18] = 17;
    serialUplink[19] = 96;
    serialUplink[20] = 0;
    serialUplink[21] = 0;
    serialUplink[22] = 0;
    serialUplink[23] = 1;
    serialUplink[24] = 254;
    serialUplink[25] = 0;
    serialUplink[26] = 0;
    serialUplink[27] = 0;
    serialUplink[28] = 0;
    serialUplink[29] = 0;
    serialUplink[30] = 191;
    serialUplink[31] = 125;
    serialUplink[32] = 18;
    serialUplink[33] = 14;
    serialUplink[34] = 214;

    //memcpy((char *) serialUplink[2],"012345",6);
    status           = tac_successful;
    //if (0=1)
#else

    status = tam_Send_Telemetry(dlSerialBufferWithParity, AIC_SERIAL_DL_SIZE_PARITY,
                                serialUplink, AIC_ONE_PAGE_UPLINK_SIZE,
                                TAM_SEND_TIMEOUT);
#endif

    if ( (status != tac_successful) || (!aim_KappaCheckUplinkParity(serialUplink, AIC_ONE_PAGE_UPLINK_SIZE)) )
        returnCode = false;

    else
    {
        returnCode = true;
        aim_KappaSixDigitSerialNumber(&serialUplink[2], sixDigitSN);
        // save the uplinked serial number where the caller wants
        memcpy(p_serialNumber, &sixDigitSN, AIC_KAPPA_SIZE_OF_SERIAL_NUMBER);
        // Store the FW revision
        *p_fwRev = serialUplink[2 + FIRMWARE_REV_OFFSET];
    }
    return(returnCode);
}

/************************************************************************

 FUNCTION:   aim_KappaAssembleSerialString

 DESCRIPTION:
This function receives as input the 6-digit portion of the serial number.
The function finds the exact device in the device table using the device ID,
the submodel ID, and the Battery Connector ID.  The function then sets the
aiv_workingKappaDeviceIDString and converts the 6-digit serial number to
hex-ascii form.  The serial number string in aiv_KappaDeviceTableA
is also converted to hex-ascii format before inserting the 6-digit serial number
into the serial string.  This complete serial number is then returned.

 FUNCTION PARAMETER:

   serialUplink
     6-digit serial number.

 FUNCTION RETURN:

   aiv_serialBuffer
     Complete serial number in hex-ascii format with radiopaque.

***********************************************************************/


void aim_KappaAssembleSerialString(char* completeSNString)
{
    char   dlBuffer[AIC_KAPPA_MAX_DL_PRE_PARITY_SIZE];
    char   dlBufferWithParity[AIC_KAPPA_MAX_DOWNLINK_SIZE];
    char   workingbConnectorId;
    bool   deviceFound = false;
    USHORT totalSize   = 0;
    USHORT size        = 0;

    //header
    dlBuffer[size++] = aiv_workingKappaDevice;        // family id code
    dlBuffer[size++] = (aiv_workingKappaSubModelId << 4);  //submodel and com. code

    //get battery connector id
    dlBuffer[size++] = 0x80;
    dlBuffer[size++] = 0x01; //seg. select
    dlBuffer[size++] = 0x00; //control byte
    dlBuffer[size++] = 0x0B; //page

    totalSize        = aim_KappaAddParity(dlBuffer, dlBufferWithParity, size);

    aim_KappaSendTelemetryA(dlBufferWithParity, totalSize,
                            aiv_ulKappa, AIC_ONE_PAGE_UPLINK_SIZE, AIC_DO_NOT_PROCESSACK);

    workingbConnectorId = aiv_ulKappa[AIC_KAPPA_HEADER + 0x07]; //0x07=offset

    //find index of device in table (Must match: Model ID, Sub-Model ID, and Battery Connector ID
#ifdef DSP_2490_SIMULATION
    while ( strcmp(aiv_KappaSpecificDeviceTableA[aiv_specificKappaDeviceTableIndex].deviceString, "End of Table") != 0 )
    {
        if ( (aiv_KappaSpecificDeviceTableA[aiv_specificKappaDeviceTableIndex].deviceId == aiv_workingKappaDevice) &&
             (aiv_KappaSpecificDeviceTableA[aiv_specificKappaDeviceTableIndex].subModel == aiv_workingKappaSubModelId))
        {
            deviceFound = true;
            break;
        }
        aiv_specificKappaDeviceTableIndex++;
    }
#else
    while ( strcmp(aiv_KappaSpecificDeviceTableA[aiv_specificKappaDeviceTableIndex].deviceString, "End of Table") != 0 )
    {
        if ( (aiv_KappaSpecificDeviceTableA[aiv_specificKappaDeviceTableIndex].deviceId == aiv_workingKappaDevice) &&
             (aiv_KappaSpecificDeviceTableA[aiv_specificKappaDeviceTableIndex].subModel == aiv_workingKappaSubModelId) &&
             (aiv_KappaSpecificDeviceTableA[aiv_specificKappaDeviceTableIndex].bConnectorId == workingbConnectorId) )
        {
            deviceFound = true;
            break;
        }
        aiv_specificKappaDeviceTableIndex++;
    }
#endif

    if(!deviceFound)
        bsm_EHLock("In aim_KappaGetSerialNumber: Device not found.");

    // Save pointer to model string.
    aiv_workingKappaDeviceIDString = aiv_KappaSpecificDeviceTableA[aiv_specificKappaDeviceTableIndex].deviceString;


    //Get basic format of serial number - "PQW000000"
    sprintf(completeSNString, "%s", aiv_KappaSpecificDeviceTableA[aiv_specificKappaDeviceTableIndex].serialNumber);

    // Add serial number digit chars - "PQW123456"
    memcpy (&completeSNString[AIC_RADIOPAQUE_LENGTH],aiv_workingKappaSerial,AIC_SIX_DIGIT_SN_LENGTH);

    // Perform modification of serial number prefix for nEw3 devices. Same base serial
    // number as Adapta, but if firmware = rev 4.1, change 1st prefix byte to "N". So
    // a PQW123456 becomes NQW123456.

    if (aiv_KappaSpecificDeviceTableA[aiv_specificKappaDeviceTableIndex].deviceId
        == AIC_DEVICE_MODEL_E3)
    {
        switch (aiv_workingDeviceKappaFirmwareRev)
        {
        // See nEw3 Product Specification, Medtronic doc A17513,
        // Table A-1.85

        case ADAPTA_FW_REV_13:
        case ADAPTA_FW_REV_20:

            // No modifications of strings obtained from the table

            break;

        case nEw3_FW_REV_41:

            // Change 1st char of prefix

            completeSNString[0] = nEw3_PREFIX_CHAR;
            break;

        default:
            bsm_EHLock("Unsupported Adapta/nEw3 firmware revision.");
            break;
        }

    }
}


/************************************************************************

 FUNCTION:   aim_KappaSixDigitSerialNumber

 DESCRIPTION:
This function converts the 3-byte serial binary serial number in
the uplink of page 6 to a six ASCII numeric string.

 FUNCTION PARAMETER:

   serialUplink
     pointer to device memory containing the serial number digit portion.

 FUNCTION RETURN:

   None (writes string to caller's passed pointer)

***********************************************************************/
void aim_KappaSixDigitSerialNumber(char* serialUplink, char *sixDigitSN)
{
    unsigned long serialHiMidLow = 0L;

    //move serial number low byte into unsigned long - to hold 16 bits
    serialHiMidLow = serialUplink[6]; //low byte

    //leftShift low byte 16, OR middle byte and high byte to fit entire serial number

    serialHiMidLow  = (serialHiMidLow << 8);
    serialHiMidLow  = (serialUplink[5] | serialHiMidLow);

    serialHiMidLow  = (serialHiMidLow << 8);
    serialHiMidLow  = (serialHiMidLow | serialUplink[4]);

    serialHiMidLow &= (SERIAL_NUMBER_FLEX_MASK);

    if (serialHiMidLow > MAX_SERIAL_NUMBER)
    {
        bsm_EHLock("Serial number > 999,999");
    }

    //convert serial number to ASCII decimal digits
    sprintf(sixDigitSN, "%06lu", serialHiMidLow);

}


/************************************************************************

 FUNCTION:   aim_KappaValidateSerialNumber

 DESCRIPTION:
This function validates serial number of the device under the head is the
same as the working device. The working device is the device we have been
working with since interrogation began.

 FUNCTION CONSTANTS:

   AIC_TELEMETRY_RETRY
      The amount of time we wait between attempts to re-establish
      communication.

   AIC_TELEMETRY_WARNING_PERIOD
      The amount of time that we allow the retries to go on before
      we shut down.

************************************************************************/
bool aim_KappaValidateSerialNumber(void)
{
    char serialNumber[AIC_KAPPA_SIZE_OF_COMPLETE_SERIAL_NUMBER];
    bool returnCode = false;
    char fwRev      = 0;

    memset(serialNumber,0,sizeof(serialNumber));

    if (aim_KappaGetSerialNumber(serialNumber, &fwRev))
    {
        if ((memcmp(      serialNumber,
                          aiv_workingKappaSerial,
                          AIC_SIX_DIGIT_SN_LENGTH) == 0)
            &&
            (fwRev == aiv_workingDeviceKappaFirmwareRev))
        {
            returnCode = true;
        }
    }

    return(returnCode);
}


/************************************************************************

 FUNCTION:   aim_KappaAddParity

 DESCRIPTION:
This function is responsible for adding parity to downlinks. It adds
parity byte after every third byte from input buffer.  If remainder of
buffer size is two bytes, final parity is calculated by XOR of them.
If one byte remains, final parity byte equals that of remaining byte.
The aiv_dlKappa[] is altered to reflect added parity and the downlink
size is returned.

 FUNCTION CONSTANTS:

 FUNCTION PARAMETERS:

   buffer
      Pointer to array of bytes.

   size
      Size of buffer.

 FUNCTION RETURN:
   Size of buffer with parity added.

************************************************************************/
USHORT aim_KappaAddParity(char *dlBuffer, char *dlBufferWithParity, USHORT size)
{
    USHORT count     = 0;
    USHORT bIndex    = 0;
    USHORT tSize     = 0;
    USHORT dlSize    = 0;
    USHORT modResult = (size % 3);

    while ( count < (size/3) )
    {
        dlBufferWithParity[dlSize++] = dlBuffer[bIndex++];
        dlBufferWithParity[dlSize++] = dlBuffer[bIndex++];
        dlBufferWithParity[dlSize++] = dlBuffer[bIndex++];
        dlBufferWithParity[dlSize++] = (dlBuffer[bIndex - 1] ^ dlBuffer[bIndex - 2] ^ dlBuffer[bIndex - 3]);
        count++;
    }
    if (modResult == 1)
    {
        dlBufferWithParity[dlSize++] = dlBuffer[bIndex++];
        dlBufferWithParity[dlSize++] = dlBuffer[bIndex - 1];
    }

    if (modResult == 2)
    {
        dlBufferWithParity[dlSize++] = dlBuffer[bIndex++];
        dlBufferWithParity[dlSize++] = dlBuffer[bIndex++];
        dlBufferWithParity[dlSize++] = (dlBuffer[bIndex - 1] ^ dlBuffer[bIndex - 2]);
    }

    if(dlSize > AIC_KAPPA_MAX_DOWNLINK_SIZE)
        bsm_EHLock("In aim_KappaAddParity: AIC_KAPPA_MAX_DOWNLINK_SIZE exceeded.");

    return(dlSize);
}

/************************************************************************

 FUNCTION:   aim_KappaCheckUplinkParity

 DESCRIPTION:
This function checks the parity of the uplinked array.  Uplink consists of
an AIC_KAPPA_HEADER plus any number of memory pages that are
"AIC_KAPPA_UPLINK_PAGE_SIZE" bytes long (includes parity). If a parity
error is found for any of the pages the function returns false,
otherwise returns true.

 FUNCTION CONSTANTS:
   aiv_

 FUNCTION PARAMETERS:

************************************************************************/
bool aim_KappaCheckUplinkParity(char *kappaUplink, unsigned long size)
{
    bool   returnCode = false;
    char   parityByte = 0x00;
    USHORT byteIndex  = 0;
    int    n;
    int    firstByte  = -1; //-1 so that the 2-byte header can be processed
                            //the 1st time through

    //check parity for each page
    while (byteIndex < size)
    {
        for(n = firstByte; n < AIC_KAPPA_UPLINK_PAGE_SIZE; n++)
            parityByte = (parityByte ^ kappaUplink[byteIndex++]);

        if(parityByte != kappaUplink[byteIndex++])
            return(false);

        else
        {
            parityByte = 0x00;     //reset parityByte for next page
            firstByte  = 1;        //for every page after 1st page we start at 1.
            returnCode = true;
        }
    }

    return(returnCode);
}
/************************************************************************

 FUNCTION:   aim_KappaSendTelemetryA

 DESCRIPTION:
This Telemetry A function is a wrapper of the TAM_SendTelem() function. We
did this because we wanted to keep the user interface requirements which are
handled by this function within the AIM module instead of at the lower level
TAM module. If there are any errors returned by the Telemetry Module or the
parity of the uplink is not valid or if an ACK is expected but not returned
this function tries to validate that the device under the head is the same
device that was identified at the start of interrogation. This function does
not return unless the communication was successful.

 FUNCTION CONSTANTS:
   AIC_ACK
     ACK decode value = 0x81.
 FUNCTION PARAMETERS:

   p_dlBufferWithParity
      Pointer to the downlink message.

   downlinkSize
      Size of the downlink message. Includes the header and parity.

   p_uplink
      Pointer to the uplink.

   uplinkSize
      Expected size of the uplink message.  Includes the header and parity.

************************************************************************/
void aim_KappaSendTelemetryA(char *p_dlBufferWithParity, USHORT downlinkSize,
                             char *p_uplink, USHORT uplinkSize, bool ack_status)
{
    tat_status status;
    // Verify the downlink length is valid.
    // If downlink length exceeded then log and halt.
    if(downlinkSize > AIC_KAPPA_MAX_DOWNLINK_SIZE)
    {
        bsm_EHLock("dlk size > dlk max");
    }

    do   {

#ifdef DSP_2490_SIMULATION
        status = tac_successful;
#else
        status = tam_Send_Telemetry(p_dlBufferWithParity, downlinkSize,
                                    p_uplink,   uplinkSize,
                                    TAM_SEND_TIMEOUT);        // timeout
#endif

        if (status == tac_successful)
        {

#ifndef DSP_2490_SIMULATION
            // The actual size of uplink compared to expected is done by
            // tam_Send_Telemetry().
            if( (ack_status == false) && (aim_KappaCheckUplinkParity( p_uplink, (long)uplinkSize)) )
                break;
            //else if an ACK is expected check for ACK
            else if ( (ack_status == true) && (p_uplink[1] == AIC_ACK) )
                break;
#else
            break;
#endif
        }

        // (status != tac_successful) or the parity did not check so
        //  display a telemetry warning and validated the device is the
        //  original device
        uim_TelemetryWarning(on);

        // after we validate that the device has not changed we
        //  can try to downlink again
        aim_KappaResumeTelemetryA();

    } while (1);

}

/************************************************************************

 FUNCTION:   aim_KappaRTTSendTelemetry

 DESCRIPTION:
This Telemetry A function is a wrapper of the tam_RTT_Send_Telemetry() function. We
did this because we wanted to keep the user interface requirements which are
handled by this function within the AIM module instead of at the lower level
TAM module. If there are any errors returned by the Telemetry Module or the
parity of the uplink is not valid this function tries to validate that the
device under the head is the same device that was identified at the start
of interrogation. This function does not return unless the communication
was successful.

 FUNCTION CONSTANTS:

   AIC_RTT_DOWNLINK_SIZE
      Max downlink size for RTT test.

   AIC_RTT_TIMEOUT
      Max time allowed to run a single RTT test.

   ESTABLISH_WF_COLLECTION_TIME
      Number of seconds to collect waveform.

 FUNCTION PARAMETERS:
   p_markerArray
      Pointer to the downlink message marker array.

   markerArraySize
     Size of the downlink array.

   p_dlBufferWithParity
      Pointer to the downlink message.

   downlinkSize
      Size of the downlink message. Includes the header and parity.

   p_uplink
      Pointer to the uplink.

   uplinkSize
      Expected size of the uplink message.  Includes the header and parity.


************************************************************************/
void aim_KappaRTTSendTelemetry(char *p_markerArray, USHORT markerArraySize,
                               char *p_dlBufferWithParity, USHORT p_totalSize)
{
    int  attempts = 0;
    bool status   = false;

    // Verify the downlink length is valid.
    // If downlink length exceeded then log and halt.
    if(p_totalSize > AIC_RTT_DOWNLINK_SIZE)
    {
        bsm_EHLock("In KappaRTTSendTelemetry: Actual downlink size != Expected downlink size");
    }

    /*Attempt RTT. RTT is successful when status returned from tam_RTT_Test
        is equal to tac_temporaryOperationCompleted AND RTT Data Valid Status Bit equals true.
        RTT should be attempted for a maximum of 3 times and then we continue with the
        device interrogation. If RTT is unsuccesful aiv_DataValidStatusBit remains false (it is
        globally initialized to false) and aim_KappaRead() will ensure that the Data Valid Status
        Bit is set to false before writing it to the memory dump file.
    */
    aiv_DataValidStatusBit = false;
    while(attempts++ < 3)
    {
        bsm_SDPrint("RTT started.");
        status = tam_RTT_Test(p_markerArray, markerArraySize,
                              p_dlBufferWithParity, p_totalSize,
                              AIC_RTT_TIMEOUT);

        bsm_SDPrint("RTT returned.");

        if( status == tac_temporaryOperationCompleted)
        {
            if( aim_KappaCheckRTTDataValidStatusBit() )
            {
                aiv_DataValidStatusBit = true;
                bsm_SDPrint("RTT completed successfully.");
                break;
            }
            else
            {
                aiv_DataValidStatusBit = false;
                bsm_SDPrint("DeviceStatusBit check failed.");
            }
        }

        bsm_SDPrint("RTT failed.");

        // RTT test failed, recover telemetry before attempting another RTT
        if( attempts != 3 )
        {
            uim_TelemetryWarning(on);

            // Obtain a solid telemetry link prior to attempting a RTT test
            // Note: This function only returns, when a solid telemetry link
            // is established.
            aim_KappaEstablishSolidTelemetryLink(AIC_ESTABLISH_SOLID_LINK_TIME);

            uim_TelemetryWarning(off);

        }

    } //end while

    if(!aiv_DataValidStatusBit)
        bsm_EHLock("RTT failed 3 times.");
}

/***********************************************************************

 FUNCTION:      aim_KappaEstablishSolidTelemetryLink

 DESCRIPTION:
Maintain an uninterrupted handshaking between the device and the monitor
for a specified duration of time.  This function is only used to determine
a if strong telemetry link exists, it does not do anything with the
collected data. If there are any errors returned by the Telemetry Module
this function tries to validate that the device under the head is the
same device that was identified at the start of interrogation.
This function does not return unless the handshaking is successful for
the specified duration.
Note: This function does not take the place of "aim_KappaCollectWaveFormDataA".


 FUNCTION CONSTANTS:

 FUNCTION PARAMETERS:
   duration
     Period of time to maintain uninterrupted handshaking between device
     and monitor

************************************************************************/
void aim_KappaEstablishSolidTelemetryLink(USHORT duration)
{
    tat_status status;
    USHORT     receivedUplinkSize      = 0;
    USHORT     startEGMCollectionIndex = 0;

    // continue do-loop until handshaking is successfully performed for
    // the specified duration
    do {

        bsm_SDPrint("Attempt to establish solid telemetry link.");

        // validate that the correct device is under telemetry head.  Note:
        // This function only returns, when the correct device is found.
        aim_KappaResumeTelemetryA();
        bsm_SDPrint("Found Device");

        // Establish a solid telemetry link by collecting waveform data.
        // Beside collecting waveform data, this function keeps track of
        // successful handshaking between the device and the monitor.  If
        // successful handshaking does not occur for the 'duration' parameter
        // specified below, the status will return with tac_unsuccessfulHandshake
        startEGMCollectionIndex = 0;

        status = tam_Continuous_Egm((char *)aiv_KappaWaveformData, duration,
                                    &receivedUplinkSize, &startEGMCollectionIndex, true);

        if (status == tac_successful)
        {
            bsm_SDPrint("Established waveform collection.");
            break;
        }

    } while (1);
}

/*
***********************************************************************
 FUNCTION:
   aim_KappaCheckRTTDataValidStatusBit()

 DESCRIPTION:
  This function gets the byte containing the Data Valid Status Bit.
  If the Data Valid Status bit is true the function returns true,
  otherwise it returns false.

 FUNCTION CONSTANTS:
   AIC_KAPPA_UPLINK_PAGE_SIZE
     Size of an uplinked page including parity byte.
   AIC_DO_NOT_PROCESSACK
     Not expecting an uplink that returns an ACK.

 FUNCTION RETURN:
   True or false.
***********************************************************************
*/
bool aim_KappaCheckRTTDataValidStatusBit(void)
{
    char   statusBit;
    bool   returnCode = false;
    char   dlBuffer[AIC_KAPPA_MAX_DL_PRE_PARITY_SIZE];
    char   dlBufferWithParity[AIC_KAPPA_MAX_DOWNLINK_SIZE];
    USHORT totalSize  = 0;
    USHORT size       = 0;

    //get RTT Data Valid Status bit
    dlBuffer[size++] = aiv_workingKappaDevice;           //family id code
    dlBuffer[size++] = (aiv_workingKappaSubModelId << 4); //submodel and command code

    dlBuffer[size++] = 0x80;                        //control byte
    dlBuffer[size++] = 0x01;                        //segment select
    dlBuffer[size++] = 0x00;                        //control byte
    dlBuffer[size++] = 0x0C;                        //first page to uplink

    totalSize        = aim_KappaAddParity(dlBuffer, dlBufferWithParity, size);

    aim_KappaSendTelemetryA(dlBufferWithParity, totalSize,
                            aiv_ulKappa, AIC_ONE_PAGE_UPLINK_SIZE, AIC_DO_NOT_PROCESSACK);

    //3 byte is status
    statusBit = ( (aiv_ulKappa[AIC_KAPPA_HEADER + 0x02]) & 0x10 ); //[offset] & mask

    if(statusBit == 0x10) //if statusBit = mask value, Data Valid = true
        returnCode = true;
    else
        returnCode = false;

    return(returnCode);
}

/*
***********************************************************************

  FUNCTION:   aim_SaveSessionParameters

  DESCRIPTION:
 This function does nothing for Kappa.

  FUNCTION CONSTANTS:

  FUNCTION RETURN:

***********************************************************************
*/
void aim_SaveSessionParameters(void)
{
}
/*
***********************************************************************

  FUNCTION:   aim_KappaFindStartTime

  DESCRIPTION:
  This function takes the total ticks, the network time stamp, and the empty string
  startTime as input and returns the startTime to be placed in the Memory Dump File.
  Overview of operations below: units of - year, month, day, hour, minutes, and seconds are
  extracted from the input string and converted to type integer.  Clock ticks are converted
  to seconds to determine the raw amount of seconds to subtract from the network time
  string received as input.  Each time unit is adjusted accordingly (see code comments
  below for details) and converted back to a string to form the final timestamp string.
  NOTE: This function was designed to support network uploads that occur under 24 hours since
  the time of interrogation.  If the fundamental use or function of the Carelink Monitor is altered
  such that interrogation data is uplinked 24 or more hours after the start of an interrogation
  this function will not perform properly.

  FUNCTION CONSTANTS:

  FUNCTION RETURN:

  INPUTS:
    char *str
         String always of the form: "Sun, 06 Nov 2002 15:49:37 GMT"

    unsigned long ticks
         Clock ticks to be converted to seconds - 100 clock ticks per second.

    char *startTime
         String to be populated with interrogation start time string.
***********************************************************************
*/
char* postThirtyDayMonths[] = {"May", "Jul", "Oct", "Dec" };

char* postThirtyOneDayMonths[] = {"Jan", "Feb", "Apr",
                                  "Jun", "Aug", "Sep", "Nov", "End" };

char* months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec", "End" };

void aim_KappaFindStartTime(char *str, unsigned long totalElapsedSeconds, char *startTime)
{
    unsigned long elapsedSeconds;
    unsigned long elapsedHours;
    unsigned long elapsedMinutes;
    unsigned long networkSeconds;
    unsigned long networkMinAndSec;
    unsigned long elapsedMinAndSec;

    USHORT monthIndex;
    int    sixtySeconds           = 60;
    int    sixtyMinutes           = 60;
    int    twentyFourHours        = 24;
    int    n                      = 0;
    bool   dayFound               = false;

    //variables for each time-unit string from network
    char secondsStr[3]            = {0};
    char minutesStr[3]            = {0};
    char hoursStr[3]              = {0};
    char daysStr[3]               = {0};
    char monthsStr[4]             = {0};

    char yearFirstTwoDigitsStr[3] = {0};
    char yearLastTwoDigitsStr[3]  = {0};

    //variables for integer type of each time unit
    unsigned long secondInt;
    unsigned long minuteInt;
    unsigned long yearLastTwoDigitsInt;
    unsigned long yearInt;
    unsigned long hourInt;
    unsigned long dayInt;

    //variables for final start time strings
    char finalyearsStr[5]       = {0};
    char finalmonthsStr[4]      = {0};
    char finaldaysStr[3]        = {0};
    char finalhoursStr[3]       = {0};
    char finalsecondsStr[3]     = {0};
    char finalminutesStr[3]     = {0};
    char errorStringSeconds[11] = {0};
    char errorString[150];

    //get each time unit and convert to type Int.
    strncpy(secondsStr, (str + 23), 2);
    secondInt = atoi(secondsStr);

    strncpy(minutesStr, (str + 20), 2);
    minuteInt = atoi(minutesStr);

    strncpy(hoursStr, (str + 17), 2);
    hourInt   = atoi(hoursStr);

    strncpy(yearFirstTwoDigitsStr, (str + 12), 2);
    strncpy(yearLastTwoDigitsStr, (str + 14), 2);
    yearLastTwoDigitsInt = atoi(yearLastTwoDigitsStr);
    yearInt              = ( (atoi(yearFirstTwoDigitsStr) * 100) + yearLastTwoDigitsInt);

    strncpy(daysStr, (str + 5), 2);
    dayInt               = atoi(daysStr);

    strncpy(monthsStr, (str + 8), 3);

    //set network month index
    n = 0;
    while (n < 12)
    {
        if( (strcmp(monthsStr, months[n]) == 0) )
        {
            monthIndex = n;
            break;
        }
        n++;
    }

    networkSeconds   = (hourInt*3600 + minuteInt*sixtySeconds + secondInt);
    networkMinAndSec = (minuteInt*sixtySeconds + secondInt);

    //This function was designed to support network uplinks that occur under 24 hours since the time of interrogation.
    //If the fundamental use or function of the Carelink Monitor is altered such that interrogation
    //data is uplinked 24 or more hours after the start of an interrogation this function will not perform properly.
    if( totalElapsedSeconds > 86399) //86399 = the time: 23:59:59 converted to raw seconds
    {

        strcpy(errorString, " Time Error. Elapsed Seconds: ");
        aim_itoa(totalElapsedSeconds, errorStringSeconds, 10);
        strcat(errorString, errorStringSeconds);
        strcat(errorString, " Network date/time string: ");
        strcat(errorString, str);
        bsm_EHLock(errorString );
    }

    elapsedHours   = (totalElapsedSeconds / 3600); //determine hours elapsed since interro. start

    n              = 0;
    elapsedSeconds = totalElapsedSeconds;
    while(elapsedHours  > n) //substract seconds for every hour elapsed since interro. start
    {
        elapsedSeconds = (elapsedSeconds -(3600));
        n++;
    }

    elapsedMinutes = (elapsedSeconds / 60); //determine minutes elapsed since interro. start

    n              = 0;
    while(elapsedMinutes > n) //substract seconds for every minute elapsed since interro. start
    {
        elapsedSeconds = (elapsedSeconds - 60);
        n++;
    }

    elapsedMinAndSec = (elapsedMinutes*sixtySeconds + elapsedSeconds);

    if(elapsedMinAndSec > networkMinAndSec)
    {
        if(hourInt == 0)
        {
            hourInt = 23;
        }
        else
            hourInt--;
    }

    //Determine seconds and minutes
    if(secondInt < elapsedSeconds)
    {
        aim_itoa( (sixtySeconds - (elapsedSeconds - secondInt)), finalsecondsStr, 10);
        if(minuteInt == 0)
        {
            minuteInt = 59;
        }
        else
            minuteInt--;
    }
    else
    {
        aim_itoa( (secondInt - elapsedSeconds), finalsecondsStr, 10);
    }

    if(minuteInt < elapsedMinutes)
    {
        aim_itoa( (sixtyMinutes - (elapsedMinutes - minuteInt)), finalminutesStr, 10);
    }
    else
    {
        aim_itoa( (minuteInt - elapsedMinutes), finalminutesStr, 10);
    }
    //IF the (networkSeconds -  totalElapsedSeconds) > 0 the interrogation start and finish
    //occurred on the same day. Therefore, the year, day, and month will remain unchanged
    //and the hour is found by subtracting the elapsed hours.  All these units are converted
    //from integer to strings for concatenation below.
    if( networkSeconds >= totalElapsedSeconds )
    {
        aim_itoa(yearInt, finalyearsStr, 10);
        aim_itoa(dayInt, finaldaysStr, 10);
        aim_itoa((monthIndex + 1), finalmonthsStr, 10);
        aim_itoa((hourInt - elapsedHours), finalhoursStr, 10);
    }

    //ELSE the interrogation start and finish occurred on different days.
    //1.Determine the hour of the interro. start timestamp
    //2.Determine the date of the interro. start timestamp. If the network day IS NOT the
    // 1ST of the month then the month and year will not change.
    //3. If network day IS the 1ST we must change the interro. start timestamp month and date.
    //4. Change the month of the interro. start timestamp to the previous month.
    //5. Determine if the network month is preceded by a month with 31 days. If so set interro. start
    // day to 31.
    //6. Determine if the network month is preceded by a month with 30 days. If so set interro. start
    // day to 30.
    //7. If network month is March, determine if it is a leap year and set interro. start day to either
    // 28 or 29.
    //LEAP YEAR RULES: If the year is exactly divisible by 4 it is a leap year BUT if the year is the
    //last of a century (such as 1800, 1900, 2000) then it is ONLY a leap year IF it is divisble by 400.
    // 8. If the network date is January 1ST then the interro. start date year must change to the
    // previous year.
    else
    {
        // *1*
        if(elapsedHours > hourInt)
        {
            aim_itoa( (twentyFourHours - (elapsedHours - hourInt)), finalhoursStr, 10);
        }
        else
        {
            aim_itoa( (hourInt - elapsedHours), finalhoursStr, 10);
        }
        // *2*
        if(dayInt != 1)
        {
            aim_itoa((dayInt - 1), finaldaysStr, 10);
            aim_itoa((monthIndex + 1), finalmonthsStr, 10);
            aim_itoa(yearInt, finalyearsStr, 10);
        }
        // *3*
        else
        {
            // *4*
            if(monthIndex == 0) //if the network month is January, set interro. start timestamp to Dec.
                aim_itoa(12, finalmonthsStr, 10);
            else //else take number of previous month (which is monthIndex here)
                aim_itoa((monthIndex), finalmonthsStr, 10);

            // *5*
            n = 0;
            while( (postThirtyOneDayMonths[n] != "End") && (dayFound == false) )
            {
                if( strcmp(monthsStr, postThirtyOneDayMonths[n++]) == 0 )
                {
                    aim_itoa(31, finaldaysStr, 10);
                    dayFound = true;
                    break;
                }
            }
            // *6*
            n = 0;
            if(!dayFound )
            {
                while( (postThirtyDayMonths[n] != "End") && (dayFound == false) )
                {
                    if( strcmp(monthsStr, postThirtyDayMonths[n++]) == 0 )
                    {
                        aim_itoa(30, finaldaysStr, 10);
                        dayFound = true;
                        break;
                    }
                }
            }
            // *7*
            if(!dayFound)
            {
                if( strcmp(monthsStr, "Mar") == 0 )
                {
                    if( ( (yearInt % 4) == 0) && (yearLastTwoDigitsStr != "00") )
                    {
                        aim_itoa(29, finaldaysStr, 10);
                        dayFound = true;
                    }
                    else if( (yearLastTwoDigitsStr == "00") && (yearInt % 400 == 0) )
                    {
                        aim_itoa(29, finaldaysStr, 10);
                        dayFound = true;
                    }
                    else
                    {
                        aim_itoa(28, finaldaysStr, 10);
                        dayFound = true;
                    }
                }
            }
            // *8*
            if( strcmp(monthsStr, "Jan") == 0 )
            {
                aim_itoa( (yearInt - 1), finalyearsStr, 10);
            }
            else
            {
                aim_itoa(yearInt, finalyearsStr, 10);
            }
        }
    }

    //Assemble timestamp.
    //If month, day, hour, minute or second is a single digit add leading zero.
    strncpy(startTime, finalyearsStr, 4);

    if(strlen(finalmonthsStr) < 2 )
    {
        strncpy(startTime + 4, "0", 1);
        strncpy(startTime + 5, finalmonthsStr, 1);
    }
    else
        strncpy(startTime + 4, finalmonthsStr, 2 );

    if(strlen(finaldaysStr) < 2 )
    {
        strncpy(startTime + 6, "0", 1);
        strncpy(startTime + 7, finaldaysStr, 1);
    }
    else
        strncpy(startTime + 6, finaldaysStr, 2 );

    if(strlen(finalhoursStr) < 2 )
    {
        strncpy(startTime + 8, "0", 1);
        strncpy(startTime + 9, finalhoursStr, 1);
    }
    else
        strncpy(startTime + 8, finalhoursStr, 2 );

    if(strlen(finalminutesStr) < 2 )
    {
        strncpy(startTime + 10, "0", 1);
        strncpy(startTime + 11, finalminutesStr, 1);
    }
    else
        strncpy(startTime + 10, finalminutesStr, 2 );

    if(strlen(finalsecondsStr) < 2 )
    {
        strncpy(startTime + 12, "0", 1);
        strncpy(startTime + 13, finalsecondsStr, 1);
    }
    else
        strncpy(startTime + 12, finalsecondsStr, 2 );

}
/*
***********************************************************************

  FUNCTION:   aim_UpdateDateTime

  DESCRIPTION:
 This function is called in fsm_file.c by fsm_UpdateAssetDataAndCloseFile. Before we
 send the file to the network we need to get the network time and use it to
 create timestamps for: (1) the start time of the interrogation, (2)the start time of
 the device memory dump, and (3) start time of the waveform interrogation.  We have stored
 clock ticks since these start times in: aiv_totalInterrogationTicks, aiv_ticksAtStartOfMemoryDump,
 and aiv_totalWaveformTicks (there are 100 ticks in a second). The function aim_KappaFindStartTime()
 takes the total ticks, the network time stamp, and the empty startTime as input and
 returns the startTime to be placed in the Memory Dump File.

  FUNCTION CONSTANTS:

  FUNCTION RETURN:

***********************************************************************
*/
#define AIC_TICKS_PER_SECOND 100
void aim_UpdateDateTime(void)
{
    char          str[32];
    unsigned long ticks;
    char          startTimeMemoryDump[15]    =    {"XXXXXXXXXXXXXX"};
    char          startTimeWaveform[15]      =      {"XXXXXXXXXXXXXX"};
    char          startTimeInterrogation[15] = {"XXXXXXXXXXXXXX"};

    nwm_RetrieveHTTPDateTime(str, &ticks);

    aim_KappaFindStartTime(str, ( (ticks - aiv_ticksAtStartOfMemoryDump) / AIC_TICKS_PER_SECOND ), startTimeMemoryDump);
    fsm_ReplaceMemoryDumpFileTimeStamp(startTimeMemoryDump);

    aim_KappaFindStartTime(str, ( (ticks - aiv_ticksAtStartOfWaveform) / AIC_TICKS_PER_SECOND ), startTimeWaveform);
    fsm_ReplaceKappaWaveformFileTimeStamp(startTimeWaveform);

    aim_KappaFindStartTime(str, ( (ticks - aiv_ticksAtStartOfInterrogation) / AIC_TICKS_PER_SECOND ), startTimeInterrogation);
    fsm_ReplaceFileInterrogationTimeStamp(startTimeInterrogation);
    memcpy(aim_KappaGetInterrogationTimeDateString(), startTimeInterrogation, 15);
}
/*
***********************************************************************
 FUNCTION:
   aim_KappaCheckERIStatus

 DESCRIPTION:
  This function gets the byte containing the ERI Status Bit.
  If the ERI Status bit has a status of true the function returns true,
  otherwise it returns false.

 FUNCTION CONSTANTS:
   AIC_KAPPA_UPLINK_PAGE_SIZE
     Size of an uplinked page including parity byte.
   AIC_DO_NOT_PROCESSACK
     Not expecting an uplink that returns an ACK.

 FUNCTION RETURN:
   True or false.
***********************************************************************
*/
bool aim_KappaCheckERIStatus(void)
{
    char   eriStatusBit;
    bool   returnCode = false;
    char   dlBuffer[AIC_KAPPA_MAX_DL_PRE_PARITY_SIZE];
    char   dlBufferWithParity[AIC_KAPPA_MAX_DOWNLINK_SIZE];
    USHORT totalSize  = 0;
    USHORT size       = 0;

    //get ERI Status bit
    dlBuffer[size++] = aiv_workingKappaDevice;           //family id code
    dlBuffer[size++] = (aiv_workingKappaSubModelId << 4); //submodel and command code
    dlBuffer[size++] = 0x00;                        //control byte and number of pages
    dlBuffer[size++] = 0x06;                        //first page to uplink

    totalSize        = aim_KappaAddParity(dlBuffer, dlBufferWithParity, size);

    aim_KappaSendTelemetryA(dlBufferWithParity, totalSize,
                            aiv_ulKappa, AIC_ONE_PAGE_UPLINK_SIZE, AIC_DO_NOT_PROCESSACK);

    //4th byte is status
    eriStatusBit = ( (aiv_ulKappa[AIC_KAPPA_HEADER + 0x03]) & 0x02 ); //[offset] & mask

    if(eriStatusBit == 0x02) //if eriStatusBit = mask value, ERI = true
    {
        bsm_SDPrint("Device at ERI.");
        returnCode = true;
    }
    else
        returnCode = false;

    return(returnCode);
}

/*
**********************************************************************

 FUNCTION:      aim_SaveInterrogationDurationTime

 DESCRIPTION:
Compare the current system clock to the saved value to calculate
the duration of the interrogation.

FUNCTION PARAMETERS:

***********************************************************************
*/
void aim_KappaSaveInterrogationDurationTime(void)
{
    int TimeInSeconds;

    aiv_currentInterrogationDurationTime = NU_Retrieve_Clock() - aiv_ticksAtStartOfInterrogation;
    TimeInSeconds                        = aiv_currentInterrogationDurationTime/100;
    aim_EEWriteUINT16( (UINT16) TimeInSeconds, coc_LastInterrogateDuration_ADDR);
}

/*
***********************************************************************

 FUNCTION:   aim_MonitorIsA2020C

 DESCRIPTION:

   Determines if monitor is a 2020C.

 FUNCTION PARAMETERS:
   None.

 FUNCTION RETURN:
   True if a 2020C, false otherwise (a 2490H)

***********************************************************************
*/

bool aim_MonitorIsA2020C(void)
{
    unsigned char snBuffer[coc_EEPROM_SN_SIZE];
    bool          retVal = false;

    // Read monitor serial number
    bsm_EEReadBuf(snBuffer, coc_EEPROM_SN_SIZE, coc_EEPROM_SN_ADDR );

    if (0 == strncmp((unsigned char*)AIC_ID_2020C, snBuffer, 3) )
    {
        retVal = true;
    }
    return(retVal);
}

/*
***********************************************************************

  FUNCTION:   aim_skipInterrogationCheckFWUpdates

  DESCRIPTION: Returns the boolean status of the press and hold manual fw
               update feature.

***********************************************************************
*/

bool aim_skipInterrogationCheckFWUpdates(void)
{
    return skipInterrogationCheckFWUpdates;
}


/*
***********************************************************************

  FUNCTION:   aim_autoIdSuccessful

  DESCRIPTION: Returns the boolean status of the auto id success.

***********************************************************************
*/

bool aim_autoIdSuccessful(void)
{
    return autoIdSuccessful;
}

