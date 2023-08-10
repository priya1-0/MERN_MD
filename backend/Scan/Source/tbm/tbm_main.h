/*
 * Telemetry B Main
 *
 */
#ifdef DEFINED_HERE
        #define SCOPE
#else
        #define SCOPE extern
#endif

#include "link.h"
#include "tbt_channel.h"
#include "tbt_handler.h"

//
// Global Definitions

//
// Global Variables
//
#ifdef DEFINED_HERE
#pragma DATA_SECTION(tbv_active, ".tbmExtData")
#endif
SCOPE BOOL tbv_active
#ifdef DEFINED_HERE
    = FALSE
#endif
;
SCOPE UINT8                 tbv_rxInProgress;
SCOPE UINT16                tbv_rxByteCount;
SCOPE UINT8                 tbv_txInProgress;
SCOPE UINT8                 * tbv_tailRxBuffer;
SCOPE UINT8                 * tbv_headRxBuffer;
SCOPE UINT16                tbv_txByteCount;
SCOPE UINT16                tbv_txSize;
SCOPE tbt_ulNonWaveFormType receiveArray[TBC_UL_FRAME_Q_SIZE];
SCOPE tbt_ulFrameQ          tbv_ulFrameQ;
SCOPE UINT16                receiveRow,receiveOffset;
SCOPE UINT8                 tbv_bOutOfFrame;

#ifdef DEBUG_STATE
SCOPE tbt_stateType state[STATE_ARRAY_SIZE+1];
SCOPE unsigned char stateIndex;
#endif

#ifdef DEBUG_HEADERS_ON
#define DEBUG_HEADERS_SIZE 256
#define DEBUG_HEADERS_MASK 0xff
#define RCV_HEADER         0x1000
#define TRX_HEADER         0x2000
#define TRX_WACK           0x2fff
SCOPE UINT16 debugHeaders[DEBUG_HEADERS_SIZE+1];
SCOPE UINT16 debugHeadersIndex;
#endif


//
// Global Functions
//

SCOPE void tbm_disablePhysLayer(BOOL);
SCOPE void tbm_init(void);
SCOPE void tbm_enableInterrupts(void);
SCOPE void tbm_disableInterrupts(void);
SCOPE void tbm_PRDIntEnable(void );
SCOPE void tbm_PRDIntDisable(void );
#undef SCOPE
