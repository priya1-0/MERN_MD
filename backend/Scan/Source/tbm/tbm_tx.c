/********************************************************************
DOCUMENT

$Revision$

$Date$

$RCSfile$

NAME:  tbm_tx.c

PURPOSE  Module contains functions dealing with 2490B transmit.

USAGE:  none

ENDDOCUMENT
********************************************************************/
#include <stdlib.h>

#include "tbt_channel.h"
#include "link.h"
#include "tbm_fsm.h"
#include "tbm_events.h"
#include "tbm_queue.h"
#include "tbm_trx.h"
#include "tbm_channel.h"
#include "tbm_main.h"
#include "tbm_rcv.h"
#include "tbm_timer.h"
#include <string.h>

void tbm_txWack(void);

/********************************************************************

FUNCTION: tbm_txFrame

DESCRIPTION:  This function will start transmission of a Telemetry
              frame.  tbv_p_nextDownlink needs to point to a valid
              'B' frame type (tbt_dlFrameType *).
              It can also transmit a WACK frame if tbv_p_nextDownlink
              points to the &tbv_wack.

ARGS:
    <none>

RETURNS:
    <none>

NOTES:
    Global pointer tbv_p_nextDownlink is pointer to downlink frame

********************************************************************/
void tbm_txFrame( void )
{
    UINT16 crc,len;

#ifdef DEBUG_VARS_ON
    debugVars.inListenMode = FALSE;
#endif
    //
    // Transmit frame is a WACK.
    //
    /**/
    if (tbv_p_nextDownlink == (tbt_dlFrameType *)&tbv_wack)
    {
#ifdef DEBUG_VARS_ON
        debugVars.startedTransmitting = 2;
#endif

#ifdef DEBUG_STATE
        ++stateIndex;
        stateIndex       &= STATE_MASK;
        state[stateIndex] = tbt_wackSent;
#endif

        tbm_txWack();
    }
    //
    // Transmit frame is a regular downlink.
    //
    else {

#ifdef DEBUG_STATE
        ++stateIndex;
        stateIndex       &= STATE_MASK;
        state[stateIndex] = tbt_downlinkSent;
#endif

#ifdef DEBUG_VARS_ON
        debugVars.startedTransmitting = 1;
#endif

        tbv_txInProgress              = TRUE;

        // Initialize transmitter control variables
        tbv_p_headTxBuffer            = tbv_p_nextDownlink;
        tbv_p_currentTxBuffer         = (UINT8 *)&txFrame;
        // Tx length needs to include start flag, end flag, and CRC (4 bytes more).
        tbv_txSize                    = (UINT16)tbv_p_headTxBuffer->length + 4;
        tbv_txByteCount               = 0;

        // Don't use the WACK bit counter.
        tbv_txWackBitCount            = 0;
        tbv_txWackBitSize             = TBC_no_wack;

        // Set the number of sync bits to be transmitted.
        tbv_syncBits                  = (tbv_p_nextDownlink->syncType == tbc_sc_extended) ?
                                        3192 : 5;

        len                           =0;
        txFrame[len++]                = 0x7e;
        memcpy(&txFrame[len], &tbv_p_headTxBuffer->dlHeader, tbv_p_headTxBuffer->length);
        len                          += tbv_p_headTxBuffer->length;

        // Calculate the CRC of the frame and store it at the CRC position of the frame.
        crc                           = tbm_frameCRC(&(tbv_p_headTxBuffer->dlHeader), tbv_p_headTxBuffer->length);
        txFrame[len++]                = crc & 0xff;
        txFrame[len++]                = (crc >> 8) & 0xff;

        txFrame[len]                  = 0x7e;

#ifdef DEBUG_ON
        ++debugHeadersIndex;
        debugHeaders[debugHeadersIndex % DEBUG_SIZE]       = 0x01;
        ++debugHeadersIndex;
        debugHeaders[debugHeadersIndex % DEBUG_SIZE]       = tbv_p_headTxBuffer->dlHeader;
        debugHeaders[(debugHeadersIndex % DEBUG_SIZE) + 1] = 0xffff;
#endif
        // Set desired rate, the following uplink rate may change
        desiredUplinkRate                                  = tbv_p_nextDownlink->uplinkRate;
    }

    tbv_txFrameNum &= 15;
    memset (&tbv_txArray[tbv_txFrameNum], 0, TBC_MAX_DL_FRAME);
    memcpy (&tbv_txArray[tbv_txFrameNum], tbv_p_currentTxBuffer, tbv_txSize);
    ++tbv_txFrameNum;


    // Physical Layer function to initiate the downlink.
    tbm_startPacketTrx();

    tbv_p_nextDownlink = NULL;

    return;
} /* tbm_txFrame */


/********************************************************************

FUNCTION: tbm_txWack

DESCRIPTION:  Start Downlink transmit of a Wack

ARGS:
    <none>

RETURNS:
    <none>

********************************************************************/
void tbm_txWack( void )
{
    tbv_txInProgress      = TRUE;

    // Initialize transmitter control variables
    tbv_p_currentTxBuffer = &tbv_wack;
    tbv_txSize            = 1;
    tbv_txByteCount       = 0;

    // WACK bit count (after sync bits).
    tbv_txWackBitCount    = 0;
    tbv_txWackBitSize     = 2;

    // WACK pattern is 0,0,0,0,0,0,1,0 which is the same
    // as 6 sync bits and then 1, 0.
    tbv_syncBits = 6;
    tbv_wack     = 0x01;
}

/********************************************************************

FUNCTION: tbm_processTransmitComplete

DESCRIPTION:  Process a transmitted frame.  This function may dequeue
              a frame following transmit.  It may post an event to
              the channel layer informing it of a completed xmit.
              There is also some addt'l resetting of variables
              following specific downlinks.
ARGS:
    tbv_p_headTxBuffer

RETURNS:
    <none>

NOTES:
    Global pointer tbv_p_headTxBuffer is passed in as pointer to frame

********************************************************************/
void tbm_processTransmitComplete(tbt_dlFrameType * tbv_p_headTxBuffer)
{

#ifdef DEBUG_HEADERS_ON
    debugHeaders[debugHeadersIndex++] = (tbv_p_headTxBuffer->dlHeader | TRX_HEADER);
    debugHeadersIndex                &= DEBUG_HEADERS_MASK;
#endif

    switch (tbv_p_headTxBuffer->frameType)
    {
    case tbt_dlUFrame:
#ifdef DEBUG_STATE
        ++stateIndex;
        stateIndex       &= STATE_MASK;
        state[stateIndex] = tbt_downlinkUFrameComplete;
#endif
        if ((tbv_p_headTxBuffer->status == tbt_txInProgressNoRetry)&&(tbv_moreEventsFlag))
        {
            tbm_postEvent(&tbm_Chan_DeviceIDTxDone);
        }
        break;

    case tbt_dlUFrameOpen:
#ifdef DEBUG_STATE
        ++stateIndex;
        stateIndex                      &= STATE_MASK;
        state[stateIndex]                = tbt_downlinkOpenComplete;
#endif
        /* An open was just sent, need to reinit some seq. number variables */
        tbv_downlinkSequenceNumber       = 0;
        tbv_expectedUplinkSequenceNumber = 0;
        tbv_numberOfUnAckedFrames        = 0;
        /* Clear out pending ack Nak following "new" open */
        tbv_p_ackNakdl                   = NULL;
        timeToHandshake                  = FALSE;
        handshakeTickCounter20mS         = 0;


        if ((tbv_p_headTxBuffer->status == tbt_txInProgressNoRetry)&&(tbv_moreEventsFlag))
        {
            tbm_postEvent(&tbm_Chan_OpenTxDone);
        }
        break;

    case tbt_dlUFrameClose:

        if ((tbv_p_headTxBuffer->status == tbt_txInProgressNoRetry)&&(tbv_moreEventsFlag))
        {
            tbm_postEvent(&tbm_Chan_CloseTxDone);
            tbm_dequeueDownlink();

            /* This is done synchronously so it needs to be dequeued */
        }

        break;

    case tbt_dlAck:
    case tbt_dlNak:

#ifdef DEBUG_STATE
        ++stateIndex;
        stateIndex       &= STATE_MASK;
        state[stateIndex] = tbt_downlinkACKNAKSent;
#endif


        tbv_ackNakHandshakeQ.status    = tbt_txNoStatus;
        tbv_ackNakHandshakeQ.frameType = tbt_dlInvalid;

        timeToHandshake                = FALSE;
        handshakeTickCounter20mS       = 0;

        tbv_numberOfUnAckedFrames      = 0;
        tbv_p_ackNakdl                 = NULL;

        break;

    case tbt_dlHandshake:

#ifdef DEBUG_STATE
        ++stateIndex;
        stateIndex                   &= STATE_MASK;
        state[stateIndex]             = tbt_downlinkHSComplete;
#endif
#ifdef DEBUG_VARS_ON
        debugVars.startedTransmitting = 3;
        ++debugVars.handshakesCompleted;
#endif

        break;


    case tbt_dlData:

#ifdef DEBUG_STATE
        ++stateIndex;
        stateIndex              &= STATE_MASK;
        state[stateIndex]        = tbt_downlinkDataSent;
#endif
        timeToHandshake          = FALSE;
        handshakeTickCounter20mS = 0;

        break;


    case tbt_dlInvalid:
    default:
#ifdef DEBUG_STATE
        ++stateIndex;
        stateIndex       &= STATE_MASK;
        state[stateIndex] = tbt_downlinkSentInvalid;
#endif
        break;

    }

    return;
}

/********************************************************************

FUNCTION: calcCRC

DESCRIPTION:  Calculates the 16 bit CCITT CRC of a byte of data.

ARGS:
    unsigned short cur_crc - the input crc value.
    unsigned char data - the input data
RETURNS:
    unsigned short - the output crc value.

********************************************************************/
static UINT16 calcCRC (UINT16 cur_crc, UINT8 data)
{
    static const UINT16 crctbl[]={
        0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7,
        0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef,
        0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7, 0x62d6,
        0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c, 0xf3ff, 0xe3de,
        0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485,
        0xa56a, 0xb54b, 0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d,
        0x3653, 0x2672, 0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4,
        0xb75b, 0xa77a, 0x9719, 0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc,
        0x48c4, 0x58e5, 0x6886, 0x78a7, 0x0840, 0x1861, 0x2802, 0x3823,
        0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948, 0x9969, 0xa90a, 0xb92b,
        0x5af5, 0x4ad4, 0x7ab7, 0x6a96, 0x1a71, 0x0a50, 0x3a33, 0x2a12,
        0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b, 0xab1a,
        0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41,
        0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49,
        0x7e97, 0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70,
        0xff9f, 0xefbe, 0xdfdd, 0xcffc, 0xbf1b, 0xaf3a, 0x9f59, 0x8f78,
        0x9188, 0x81a9, 0xb1ca, 0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f,
        0x1080, 0x00a1, 0x30c2, 0x20e3, 0x5004, 0x4025, 0x7046, 0x6067,
        0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d, 0xd31c, 0xe37f, 0xf35e,
        0x02b1, 0x1290, 0x22f3, 0x32d2, 0x4235, 0x5214, 0x6277, 0x7256,
        0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c, 0xc50d,
        0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
        0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e, 0xc71d, 0xd73c,
        0x26d3, 0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634,
        0xd94c, 0xc96d, 0xf90e, 0xe92f, 0x99c8, 0x89e9, 0xb98a, 0xa9ab,
        0x5844, 0x4865, 0x7806, 0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3,
        0xcb7d, 0xdb5c, 0xeb3f, 0xfb1e, 0x8bf9, 0x9bd8, 0xabbb, 0xbb9a,
        0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1, 0x1ad0, 0x2ab3, 0x3a92,
        0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b, 0x9de8, 0x8dc9,
        0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0, 0x0cc1,
        0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8,
        0x6e17, 0x7e36, 0x4e55, 0x5e74, 0x2e93, 0x3eb2, 0x0ed1, 0x1ef0
    };

    data   ^= (UINT8)(cur_crc>>8);
    cur_crc = (0xff00 & (cur_crc<<8)) ^ crctbl[data & 0xff];
    return (cur_crc);
}

/********************************************************************

FUNCTION: tbm_frameCRC

DESCRIPTION:  Calculates the CCITT CRC of a telemetry B frame. The input
        data is bit reversed before calculating. The calculated CRC is bit
        reversed and complimented.

ARGS:
    unsigned char *dptr - pointer to the data to calculate the CRC on.
    unsigned short len - number of bytes to calculate CRC on.

RETURNS:
    unsigned short - the calculated CRC.

********************************************************************/
UINT16 tbm_frameCRC (UINT8 *dptr, UINT16 len)
{
    static const UINT8 rcharTable[256] = {
        0x00, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0, 0x10, 0x90, 0x50, 0xd0,
        0x30, 0xb0, 0x70, 0xf0, 0x08, 0x88, 0x48, 0xc8, 0x28, 0xa8, 0x68, 0xe8,
        0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8, 0x78, 0xf8, 0x04, 0x84, 0x44, 0xc4,
        0x24, 0xa4, 0x64, 0xe4, 0x14, 0x94, 0x54, 0xd4, 0x34, 0xb4, 0x74, 0xf4,
        0x0c, 0x8c, 0x4c, 0xcc, 0x2c, 0xac, 0x6c, 0xec, 0x1c, 0x9c, 0x5c, 0xdc,
        0x3c, 0xbc, 0x7c, 0xfc, 0x02, 0x82, 0x42, 0xc2, 0x22, 0xa2, 0x62, 0xe2,
        0x12, 0x92, 0x52, 0xd2, 0x32, 0xb2, 0x72, 0xf2, 0x0a, 0x8a, 0x4a, 0xca,
        0x2a, 0xaa, 0x6a, 0xea, 0x1a, 0x9a, 0x5a, 0xda, 0x3a, 0xba, 0x7a, 0xfa,
        0x06, 0x86, 0x46, 0xc6, 0x26, 0xa6, 0x66, 0xe6, 0x16, 0x96, 0x56, 0xd6,
        0x36, 0xb6, 0x76, 0xf6, 0x0e, 0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e, 0xee,
        0x1e, 0x9e, 0x5e, 0xde, 0x3e, 0xbe, 0x7e, 0xfe, 0x01, 0x81, 0x41, 0xc1,
        0x21, 0xa1, 0x61, 0xe1, 0x11, 0x91, 0x51, 0xd1, 0x31, 0xb1, 0x71, 0xf1,
        0x09, 0x89, 0x49, 0xc9, 0x29, 0xa9, 0x69, 0xe9, 0x19, 0x99, 0x59, 0xd9,
        0x39, 0xb9, 0x79, 0xf9, 0x05, 0x85, 0x45, 0xc5, 0x25, 0xa5, 0x65, 0xe5,
        0x15, 0x95, 0x55, 0xd5, 0x35, 0xb5, 0x75, 0xf5, 0x0d, 0x8d, 0x4d, 0xcd,
        0x2d, 0xad, 0x6d, 0xed, 0x1d, 0x9d, 0x5d, 0xdd, 0x3d, 0xbd, 0x7d, 0xfd,
        0x03, 0x83, 0x43, 0xc3, 0x23, 0xa3, 0x63, 0xe3, 0x13, 0x93, 0x53, 0xd3,
        0x33, 0xb3, 0x73, 0xf3, 0x0b, 0x8b, 0x4b, 0xcb, 0x2b, 0xab, 0x6b, 0xeb,
        0x1b, 0x9b, 0x5b, 0xdb, 0x3b, 0xbb, 0x7b, 0xfb, 0x07, 0x87, 0x47, 0xc7,
        0x27, 0xa7, 0x67, 0xe7, 0x17, 0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77, 0xf7,
        0x0f, 0x8f, 0x4f, 0xcf, 0x2f, 0xaf, 0x6f, 0xef, 0x1f, 0x9f, 0x5f, 0xdf,
        0x3f, 0xbf, 0x7f, 0xff
    };

    UINT16 crc = 0xffff;
    int    x;
    for (x=0; x<len; ++x, ++dptr) {
        // Calculate the CRC using bit reversed input data.
        crc = calcCRC(crc, rcharTable[*dptr & 0xff]);
    }
    // Compliment the result.
    crc ^= 0xffff;
    // Bit reverse the result.
    crc  = (rcharTable[crc & 0xff] << 8) | rcharTable[(crc>>8) & 0xff];
    return (crc);
}

