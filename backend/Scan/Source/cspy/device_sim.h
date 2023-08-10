
#ifndef u32
typedef unsigned long u32;
#endif

void DeviceSimRescan(void);

void DeviceSimNormalScan(void);

void DeviceSimInit(void);

void DeviceSimAutoId(u32 *id);

void DeviceSimTimeOfSave(u32 *id);

void DeviceSimTimeOfLastSession(u32 *id);

int DeviceSimMemory(char *dataDestination, u32 length, u32 bank, u32 address, u32 mask);


#ifndef TAM_GLOBAL_H
// 
typedef enum  {
    tac_unknownError,           
    tac_downlinkCommandFailed,
    tac_failedToCreateTimer,
    tac_failedToDisableTimer,
    tac_failedToDeleteTimer,
    tac_exceedMaximumEgmRecordTime,
    tac_repeatDownlinkActive, 
    tac_repeatDownlinkNotActive,
    tac_activeOrIdleSegmentZero,
    tac_badTelemetryType,
    tac_unsuccessfulHandshake,
    tac_nonAckResponse,
    tac_temporaryOperationCompleted,
    
    // generic
    tac_successful,

// Information used in communicating telemetry error status to the host
//   Note: These match equivalent enumerations in pdm_com.h
   tac_telemetryError = 0xE0,
   tac_telemetryConfigurationError = 0xE1,
   tac_telemetryTimeout = 0xE2,
   tac_telemetryCRCError = 0xE3,
   tac_telemetryInvalidStateError = 0xE4,
   tac_telemetrySegmentTimeError = 0xE5,
   tac_telemetryTooShortFrameError = 0xE6,
   tac_telemetryInvalidLowerNibbleError = 0xE7,
   tac_telemetryInvalidUpperNibbleError = 0xE8,   
   tac_telemetryInvalidIdError = 0xE9,
   tac_telemetryMemoryFrameInterruptedError = 0xEa,
    tac_noSyncPulseReceived = 0xEb,
    tac_telemetryInvalidParityCheckError = 0xEc,
    tac_markerDoubleFrameFailure = 0xEd,
    tac_telemetryParityError = 0xEe
    
} tat_status;

#endif

tat_status aim_SimulatedSendTelemetryA_DSP(char *p_downlink, int downlinkSize,
                        char *p_uplink,   int uplinkSize,
                        bool updateProgress);

void aim_SimulatedSendTelemetryB_DSP(char *p_downlink, int downlinkSize,
                        char *p_uplink,   int uplinkSize,
                        bool updateProgress);
	                        
void DeviceSimWaveform(char *dataDestination, u32 length);

void DeviceSimError(char *message);

void DeviceSimComplete(char *message);

void DeviceSimLogInit(void);

void DeviceSimLog(char *str);

void nwm_RetrieveHTTPDateTime(char *datetimestr, unsigned long *ticks);

void nwm_RetrieveHTTPDateTime(char *datetimestr, unsigned long *ticks);

BOOL nwm_Send_Data(void);
