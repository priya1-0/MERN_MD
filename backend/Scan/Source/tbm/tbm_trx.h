/*
 * Telemetry B Trx
 */
#ifdef DEFINED_HERE
        #define SCOPE
#else
        #define SCOPE extern
#endif

#include "tbt_channel.h"

// The ordering of the enumeration values is significant!!
// TX_DONE must be less than TX_INIT in value.
typedef enum
{
    TX_DONE=0,
    TX_INIT,
    TX_SYNC,
    TX_DATA,
    TX_IDLE
} TX_STATE_t;

// Info field + 2 flag + 2 crc + 2 prg ID + header
#define TBC_MAX_DL_FRAME (TBC_MAX_DL_IFIELD_SIZE + 7)

//
//  Global Variables
//

SCOPE TX_STATE_t tbm_xmtState;

/* Global pointer that always points to the head of the current transmit buffer */
SCOPE tbt_dlFrameType * tbv_p_headTxBuffer;

/* Global pointer that points to the next downlink, in most cases */
/* it is set up during the uplink process functions, sometimes it */
/* is set up asynchronously in the channel/link interface functions */
SCOPE tbt_dlFrameType * tbv_p_nextDownlink;

/* A global pointer that when it is !NULL it will send the downlink */
/* frame in the tbv_ackNakHandshakeQ following a uplink waveform */
SCOPE tbt_dlFrameType * tbv_p_ackNakdl;

/* Global pointer used to track/transmit each byte of the current downlink */
SCOPE unsigned char * tbv_p_currentTxBuffer;

SCOPE tbt_dlFrameQ    tbv_dlFrameQ;
SCOPE tbt_dlFrameType *pTxPacket;
SCOPE tbt_dlFrameType tbv_txFrame;
SCOPE UINT16          txFrame[TBC_MAX_DL_FRAME];
SCOPE INT16           tbv_syncBits;
SCOPE UINT16          tbv_txWackBitCount;
SCOPE UINT16          tbv_txWackBitSize;

SCOPE UINT16 tbv_txArray[16][TBC_MAX_DL_FRAME];
SCOPE UINT16 tbv_txFrameNum;

SCOPE tbt_dlFrameType tbv_ackNakHandshakeQ;
SCOPE UINT8           tbv_wack;
//
// Global Functions
//
SCOPE void tbm_startPacketTrx(void);
SCOPE void tbm_trxInit(void);
SCOPE void tbm_txFrame(void);
SCOPE UINT16 tbm_frameCRC (UINT8 *, UINT16);
SCOPE void tbm_disableTrx(void);
SCOPE void tbm_processTransmitComplete(tbt_dlFrameType *);
SCOPE void tbm_enableTrxInt(void);
SCOPE void tbm_disableTrxInt(void);


#undef SCOPE
