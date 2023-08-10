/************************************************************************
*
* MODULE: tam_global.h
*
* OWNER:
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This header file should be the only header file from the
*              tam directory that is included in the application
*
*************************************************************************/
#ifndef TAM_GLOBAL_H
#define TAM_GLOBAL_H

#include "global.h"

// This enumeration specifies all the potential status the tam module
//   will provide the application.
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
    tac_telemetryError                       = 0xE0,
    tac_telemetryConfigurationError          = 0xE1,
    tac_telemetryTimeout                     = 0xE2,
    tac_telemetryCRCError                    = 0xE3,
    tac_telemetryInvalidStateError           = 0xE4,
    tac_telemetrySegmentTimeError            = 0xE5,
    tac_telemetryTooShortFrameError          = 0xE6,
    tac_telemetryInvalidLowerNibbleError     = 0xE7,
    tac_telemetryInvalidUpperNibbleError     = 0xE8,
    tac_telemetryInvalidIdError              = 0xE9,
    tac_telemetryMemoryFrameInterruptedError = 0xEa,
    tac_noSyncPulseReceived                  = 0xEb,
    tac_telemetryInvalidParityCheckError     = 0xEc,
    tac_markerDoubleFrameFailure             = 0xEd,
    tac_telemetryParityError                 = 0xEe

} tat_status;

typedef enum
{
    tac_GemTelemProtocol,
    tac_L88TelemProtocol,
    tac_unknownTelemProtocol
}tat_telemetryProtocolType;

typedef enum {
    // GEM                                   IPG
    tac_memoryFrame            = 0,     // message frame
    tac_handshakeRequestFrame  = 1,     // handshake request frame
    tac_markerFrame            = 2,     // marker frame
    tac_markerSupplementFrame  = 3,     // not used
    tac_idleFrame              = 5,     // idle frame
    tac_primaryEgmFrame        = 7,     // atrial egm frame
    tac_secondaryEgmFrame      = 8,     // ventricle egm frame
    tac_handshakeConfirmFrame  = 0xa,   // handshake confirm frame

    // IPG specific
    tac_aux1EgmFrame           = 0x10,
    tac_aux2EgmFrame           = 0x11,

    tac_invalidIdentifierFrame = 0xff
}   tat_frameType;


/* Function Prototypes */
tat_status tam_Initialize_TelemetryA(tat_telemetryProtocolType v_protocolType);
tat_status tam_Send_Telemetry(  BYTE   *p_downlinkMsg,
                                USHORT v_downlinkSize,
                                BYTE   *p_uplinkMsg,
                                USHORT v_uplinkSize,
                                BYTE   v_tmTimeoutDuration);

tat_status tam_Continuous_Egm(BYTE   *p_uplinkMsg,
                              BYTE   v_recordTime,
                              USHORT *p_uplinkSize,
                              USHORT *p_startEgmsampleCount,
                              bool   v_bypass10SecondCheck);

tat_status tam_Continuous_EgmL88(BYTE   *p_uplinkMsg,
                                 BYTE   v_recordTime,
                                 USHORT *p_uplinkSize,
                                 USHORT *p_startEgmsampleCount,
                                 bool   v_bypass10SecondCheck);
tat_status tam_Continuous_EgmIcd(BYTE   *p_uplinkMsg,
                                 BYTE   v_recordTime,
                                 USHORT *p_uplinkSize,
                                 USHORT *p_startEgmsampleCount);


tat_status tam_Repeat_Downlink( BYTE   *p_downlinkMsg,
                                USHORT v_downlinkSize,
                                BYTE   v_repeatInterval);


tat_status tam_Cancel_Repeat_Downlink(void);



tat_status tam_RTT_Test(        BYTE   *p_markers,
                                USHORT v_numberOfMarkers,
                                BYTE   *p_downlinkMsg,
                                USHORT v_downlinkSize,
                                USHORT v_timeoutDuration);
tat_status tam_RTT_TestL88(     BYTE   *p_markers,
                                USHORT v_numberOfMarkers,
                                BYTE   *p_downlinkMsg,
                                USHORT v_downlinkSize,
                                USHORT v_timeoutDuration);
tat_status tam_RTT_TestIcd(     BYTE   *p_markers,
                                USHORT v_numberOfMarkers,
                                BYTE   *p_downlinkMsg,
                                USHORT v_downlinkSize,
                                USHORT v_timeoutDuration);

#endif
