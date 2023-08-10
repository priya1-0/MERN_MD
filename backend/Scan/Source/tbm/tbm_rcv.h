/*
 * Telemetry B Receive
 *
 */
#ifdef DEFINED_HERE
        #define SCOPE
#else
        #define SCOPE extern
#endif

#include "link.h"
#include "tbt_channel.h"
#include <csl.h>
#include <csl_dma.h>

//
// Global Definitions
typedef enum
{
    RCV_FIND_SYNC=0,
    RCV_FIRST_SYNCED,
    RCV_SECOND_SYNCED,
    RCV_SYNCED,
    RCV_RESET,
    RCV_FINISH,
    RCV_DONE,
    RCV_IDLE
} RCV_PROC_STATE_t;


//
// Global Variables
//
SCOPE RCV_PROC_STATE_t tbm_rcvState;
SCOPE typeDebugArray   debugVars;
SCOPE tbt_rxFrameType  rxFrameInfo;
SCOPE UINT8            tbv_downlinkSequenceNumber;
SCOPE UINT8            tbv_expectedUplinkSequenceNumber;
SCOPE UINT8            tbv_numberOfUnAckedFrames;
SCOPE BOOL             tbv_immediateACK;
SCOPE UINT16           programmerID;
SCOPE BOOL             tbv_linkMaintainSession;
SCOPE BOOL             tbv_startWFsequenceChecking;
SCOPE UINT16           tbv_waveformsMissed;
SCOPE UINT8            priorWFSequenceNumber;
SCOPE UINT8            currentWFSequenceNumber;
SCOPE tbt_dataRateType currentUplinkRate;
SCOPE tbt_dataRateType desiredUplinkRate;
SCOPE BOOL             tbm_mode1HoldInhibit;
SCOPE DMA_Handle       tbv_hDma;        // Handle for the DMA channel.

//
// Global Functions
//
SCOPE void tbm_startPacketRcv(void);
SCOPE void tbm_initRcv(void);
SCOPE void tbm_disableRcv(BOOL);
SCOPE void tbm_dequeueDownlink(void);
SCOPE void tbm_shortTimeout(void);
SCOPE void tbm_uplinkStarted(unsigned char);
SCOPE void tbm_uplinkComplete(unsigned char);
SCOPE void tbm_disableRcvInt (void);
SCOPE void tbm_enableRcvInt (void);

#undef SCOPE
