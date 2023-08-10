/********************************************************************
DOCUMENT

$Revision$

$Date$

$RCSfile$

NAME:  tbm_rx.c

PURPOSE  Module contains functions dealing with 2490B receive.

USAGE:  none

ENDDOCUMENT
********************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "tbm_fsm.h"
#include "tbm_events.h"
#include "tbt_channel.h"
#include "tbt_handler.h"
#include "link.h"
#include "tbm_queue.h"
#include "tbm_timer.h"
#include "tbm_rcv.h"
#include "tbm_channel.h"
#include "tbm_main.h"
#include "tbm_trx.h"

/* local function prototypes */

void tbm_processUlWf(void);
void tbm_processUlWfp(void);
void tbm_processUlUf(void);
void tbm_processUlDfsg(void);
void tbm_processUlDfsb(void);
void tbm_processUlDfsgf(void);
void tbm_processUlAcksg(void);
void tbm_processUlAcksb(void);
void tbm_processUlNaksg(void);
void tbm_processUlNaksb(void);

/********************************************************************

FUNCTION: tbm_uplinkStarted()

DESCRIPTION:
    This function is called from within the context of the uplink
    ISR.  From this it will determine the process function and set
    up a global variable used to track the type of the current frame.

ARGS:
    Uplink Header - eg. Waveforms, Uframes, DataFrames

RETURNS:
    <none>

NOTES:
    <none>

REQUIREMENTS:
    <none>

********************************************************************/
void tbm_uplinkStarted(unsigned char uplinkHeader)
{
    unsigned char   header;
    tbt_dlFrameType * currentDownlink = NULL;

    /* Store away the uplink Header */
    rxFrameInfo.header = uplinkHeader;
    /* Mask header sequence and determine frame type */
    header             = uplinkHeader & 0xF8;

    switch (header)
    {
    case TBC_ulufmd1:
        asm ("	nop");
        asm ("	nop");  // These are included to give a spot to trigger on
        asm ("	nop");  // a mode 1 unnumbered frame uplink.
    case TBC_ulufmd0:
    case TBC_ulufmd2:
    case TBC_ulufmd3:
        // U Code must be 0 or 1 in an unnumbered frame.
        if ((uplinkHeader & 0xf) == 0 || (uplinkHeader & 0xf) == 1) {

            rxFrameInfo.processFunction = tbm_processUlUf;
            rxFrameInfo.headerType      = tbt_ulUFrame;
#ifdef DEBUG_STATE
            ++stateIndex;
            stateIndex                 &= STATE_MASK;
            state[stateIndex]           = tbt_uplinkStartedUF;
#endif
        }
        else {
            rxFrameInfo.processFunction = NULL;
            rxFrameInfo.headerType      = tbt_ulInvalid;
            ++debugVars.uplinksUnknown;
        }
        break;

    case TBC_ulwfmd0:
    case TBC_ulwfmd1:
    case TBC_ulwfmd2:
    case TBC_ulwfmd3:

        rxFrameInfo.processFunction = tbm_processUlWf;
        rxFrameInfo.headerType      = tbt_ulWf;
#ifdef DEBUG_STATE
        ++stateIndex;
        stateIndex                 &= STATE_MASK;
        state[stateIndex]           = tbt_uplinkStartedWF;
#endif

        break;

    case TBC_ulwfmd1p:
    case TBC_ulwfmd3p:

        rxFrameInfo.processFunction = tbm_processUlWfp;
        rxFrameInfo.headerType      = tbt_ulWfp;
#ifdef DEBUG_STATE
        ++stateIndex;
        stateIndex                 &= STATE_MASK;
        state[stateIndex]           = tbt_uplinkStartedWFp;
#endif

        break;

    case TBC_uldfmd1:

        if ((rxFrameInfo.header & TBC_seqMask) == (tbv_expectedUplinkSequenceNumber))
        {
#ifdef DEBUG_STATE
            ++stateIndex;
            stateIndex                 &= STATE_MASK;
            state[stateIndex]           = tbt_uplinkStartedDFsg;
#endif
            rxFrameInfo.processFunction = tbm_processUlDfsg;
            /* try the final bit here, normally it is tbt_ulData */
            rxFrameInfo.headerType      = tbt_ulData;
        }
        else
        {
#ifdef DEBUG_STATE
            ++stateIndex;
            stateIndex                 &= STATE_MASK;
            state[stateIndex]           = tbt_uplinkStartedDFsb;
#endif
            rxFrameInfo.processFunction = tbm_processUlDfsb;
            rxFrameInfo.headerType      = tbt_ulDatasb;
        }

        break;

    case TBC_uldfmd1f:

        if ((rxFrameInfo.header & TBC_seqMask) == (tbv_expectedUplinkSequenceNumber))
        {
#ifdef DEBUG_STATE
            ++stateIndex;
            stateIndex                 &= STATE_MASK;
            state[stateIndex]           = tbt_uplinkStartedDFsgf;
#endif
            rxFrameInfo.processFunction = tbm_processUlDfsgf;
            rxFrameInfo.headerType      = tbt_ulDataf;
        }
        else
        {
#ifdef DEBUG_STATE
            ++stateIndex;
            stateIndex                 &= STATE_MASK;
            state[stateIndex]           = tbt_uplinkStartedDFsb;
#endif
            rxFrameInfo.processFunction = tbm_processUlDfsb;
            rxFrameInfo.headerType      = tbt_ulDatasb;
        }

        break;

    case TBC_ulAck:
#ifdef DEBUG_STATE
        ++stateIndex;
        stateIndex       &= STATE_MASK;
        state[stateIndex] = tbt_uplinkStartedAck;
#endif

        currentDownlink   = (tbt_dlFrameType *)tbm_getQueueEntry(&tbv_dlFrameQ);

        /* An ACK uplink only makes sense if there is a downlink in progress */
        if ( (currentDownlink->status == tbt_txInProgress) && (currentDownlink != NULL) )
        {
            /* Uplink sequence number is 1 greater than the downlink sequence number, this shows an */
            /* acknowledgement of the current xmit frame.  Need to "dequeue" current frame and xmit */
            /* the "next" frame, if any */

            if ( (((rxFrameInfo.header & TBC_seqMask) - 1) & TBC_seqMask) == (tbv_downlinkSequenceNumber) )
            {
                rxFrameInfo.processFunction = tbm_processUlAcksg;
                rxFrameInfo.headerType      = tbt_ulAck;

            }
            else
            {
                rxFrameInfo.processFunction = tbm_processUlAcksb;
                rxFrameInfo.headerType      = tbt_ulAcksb;
            }

        }

        break;


    case TBC_ulNak:
#ifdef DEBUG_STATE
        ++stateIndex;
        stateIndex       &= STATE_MASK;
        state[stateIndex] = tbt_uplinkStartedNak;
#endif
        currentDownlink   = (tbt_dlFrameType *)tbm_getQueueEntry(&tbv_dlFrameQ);
        if (currentDownlink != NULL)
        {
            if (currentDownlink->status == tbt_txInProgress)
            {

                if ( ((rxFrameInfo.header & TBC_seqMask) == (tbv_downlinkSequenceNumber))||
                     ((((rxFrameInfo.header & TBC_seqMask) - 1) & TBC_seqMask) == (tbv_downlinkSequenceNumber)) )
                {
#ifdef DEBUG_STATE
                    ++stateIndex;
                    stateIndex                 &= STATE_MASK;
                    state[stateIndex]           = tbt_uplinkStartedNaksg;
#endif
                    rxFrameInfo.processFunction = tbm_processUlNaksg;
                    rxFrameInfo.headerType      = tbt_ulNak;

                }
                else
                {
#ifdef DEBUG_STATE
                    ++stateIndex;
                    stateIndex                 &= STATE_MASK;
                    state[stateIndex]           = tbt_uplinkStartedNaksb;
#endif
                    rxFrameInfo.processFunction = tbm_processUlNaksb;
                    rxFrameInfo.headerType      = tbt_ulNaksb;
                }

            }
        }

        break;


    default:
#ifdef DEBUG_STATE
        ++stateIndex;
        stateIndex                 &= STATE_MASK;
        state[stateIndex]           = tbt_uplinkStartedUnknown;
#endif

        rxFrameInfo.processFunction = NULL;
        rxFrameInfo.headerType      = tbt_ulInvalid;

        ++debugVars.uplinksUnknown;
        break;

    }

    return;
} /* tbm_uplinkStarted() */

/********************************************************************

FUNCTION: tbm_uplinkComplete()

DESCRIPTION:
    This function is called from within the context of the Receive
    ISR when the uplink completes.  Its major processing is to
    validate reception of downlink frames, post events and queue
    frames to the channel layer.
    It is only called if the uplink has a valid CRC.
ARGS:
    Row - the row of the current uplink frame

RETURNS:
    <none>

NOTES:
    <none>

REQUIREMENTS:
    <none>

********************************************************************/
void tbm_uplinkComplete(unsigned char rowOffset)
{
    rowOffset = rowOffset;

#ifdef DEBUG_ON
    ++debugHeadersIndex;
    debugHeaders[debugHeadersIndex % DEBUG_SIZE]       = 0x02;
    ++debugHeadersIndex;
    debugHeaders[debugHeadersIndex % DEBUG_SIZE]       = rxFrameInfo.header;

    /* to search for ending information */
    debugHeaders[(debugHeadersIndex % DEBUG_SIZE) + 1] = 0xffff;

#endif
    /* The "headerType" was set up in uplinkStarted */

    switch( rxFrameInfo.headerType )
    {
    case tbt_ulUFrame:
#ifdef DEBUG_STATE
        ++stateIndex;
        stateIndex       &= STATE_MASK;
        state[stateIndex] = tbt_uplinkCompleteUFrame;
#endif
        /* Inform Channel Layer of UFrame */
        /* queue the frame to the Channel Layer */

        if (tbv_moreEventsFlag)
        {
            tbm_enqueueEntry((tbt_queuePointer *)  &tbv_ulFrameQ, &receiveArray[rowOffset]);
            tbm_postEvent(&tbm_Chan_UnNumFrameUL);
        }

#ifdef DEBUG_VARS_ON
        ++debugVars.uFrames;
        ++debugVars.goodFrames;
#endif

        break;

    case tbt_ulWf:
#ifdef DEBUG_STATE
        ++stateIndex;
        stateIndex       &= STATE_MASK;
        state[stateIndex] = tbt_uplinkCompleteWF;
#endif

        /* This "if" section is for EGM capture.  If an uplink waveform is */
        /* missed an event will be posted to inform channel layer.  It is */
        /* up to the application to retry EGM capture upon a failure */

        if ((tbv_startWFsequenceChecking)&&(tbv_linkMaintainSession))
        {
            currentWFSequenceNumber = rxFrameInfo.header & 0x07;
            /* If current WF seq is one greater than last it's all good */
            if (((currentWFSequenceNumber - 1) & 7) == (priorWFSequenceNumber & 7))
            {
#ifdef DEBUG_VARS_ON
                ++debugVars.consecutiveWFs;
                if (rxFrameInfo.header & 0x60)
                    ++debugVars.mode3Waveforms;
#endif
            }
            else
            { /* We've had a resent waveform, this is still OK */
                if (currentWFSequenceNumber == priorWFSequenceNumber)
                {
#ifdef DEBUG_VARS_ON
                    ++debugVars.duplicateWFs;
#endif
                }
                else
                {
                    /* if any waveforms are missed signal a failure of EGM capture */
                    if (tbv_moreEventsFlag)
                    {
                        tbm_postEvent( &tbm_Chan_MissedWF);
                    }
                    ++tbv_waveformsMissed;
#ifdef DEBUG_VARS_ON
                    ++debugVars.missingWFs;
#endif
                }
            }
            priorWFSequenceNumber = currentWFSequenceNumber;
        }
        else
        {
            /* We're not in EGM capture, these should be initialized for when */
            /* we do enter EGM capture */
#ifdef DEBUG_VARS_ON
            debugVars.mode3Waveforms = 0;
            debugVars.missingWFs     = 0;
#endif
            tbv_waveformsMissed      = 0;
            currentWFSequenceNumber  = rxFrameInfo.header & 0x07;
            priorWFSequenceNumber    = currentWFSequenceNumber;
        }

        /* End Section for EGM capture */


#ifdef DEBUG_VARS_ON
        ++debugVars.wfFrames;
        ++debugVars.goodFrames;
#endif

        /* check if there is a frame data "in progress" and max retries */
        if ((tbv_p_headTxBuffer->status == tbt_txInProgress)&&
            (tbv_p_headTxBuffer->frameType == tbt_dlData)&&
            (tbv_p_headTxBuffer->attemptCount == 6))
        {
#ifdef DEBUG_STATE
            ++stateIndex;
            stateIndex       &= STATE_MASK;
            state[stateIndex] = tbt_hitMaxRetriesData;
#endif
            /* hit max number of retries post a transmit timeout */
            if (tbv_moreEventsFlag)
            {
                tbm_postEvent(&tbm_Chan_TxTimeout);
            }
        }
        else /* check if there is a handshake in progress */
        if ((tbv_ackNakHandshakeQ.status == tbt_txInProgress)&&
            (tbv_ackNakHandshakeQ.frameType == tbt_dlHandshake)&&
            (tbv_ackNakHandshakeQ.attemptCount == 6))
        {
#ifdef DEBUG_STATE
            ++stateIndex;
            stateIndex       &= STATE_MASK;
            state[stateIndex] = tbt_hitMaxRetriesHS;
#endif
            /* hit max number of retries post a transmit timeout */
            if (tbv_moreEventsFlag)
            {
                tbm_postEvent(&tbm_Chan_TxTimeout);
            }
            /* handshake was acknowledged, so clean queue */
            tbv_ackNakHandshakeQ.frameType    = tbt_dlInvalid;
            tbv_ackNakHandshakeQ.status       = tbt_txNoStatus;
            tbv_ackNakHandshakeQ.attemptCount = 0;
        }

        if (tbv_moreEventsFlag)
        {

            /* queue the frame to the Channel Layer */
            tbm_enqueueEntry((tbt_queuePointer *)  &tbv_ulFrameQ, &receiveArray[rowOffset]);
            tbm_postEvent(&tbm_Chan_WaveformUL);

#ifdef DEBUG_STATE
            ++stateIndex;
            stateIndex       &= STATE_MASK;
            state[stateIndex] = tbt_ChannelWFQueued;
#endif
        }

        break;

    case tbt_ulWfp:
#ifdef DEBUG_STATE
        ++stateIndex;
        stateIndex       &= STATE_MASK;
        state[stateIndex] = tbt_uplinkCompleteWFp;
#endif

        /* This "if" section is for EGM capture.  If an uplink waveform is */
        /* missed an event will be posted to inform channel layer.  It is */
        /* up to the application to retry EGM capture upon a failure */

        if ((tbv_startWFsequenceChecking)&&(tbv_linkMaintainSession))
        {
            currentWFSequenceNumber = rxFrameInfo.header & 0x07;
            /* If current WF seq is one greater than last it's all good */
            if (((currentWFSequenceNumber - 1) & 7) == (priorWFSequenceNumber & 7))
            {
#ifdef DEBUG_VARS_ON
                ++debugVars.consecutiveWFs;
                if (rxFrameInfo.header & 0x60)
                    ++debugVars.mode3Waveforms;
#endif
            }
            else
            { /* We've had a resent waveform, this is still OK */
                if (currentWFSequenceNumber == priorWFSequenceNumber)
                {
#ifdef DEBUG_VARS_ON
                    ++debugVars.duplicateWFs;
#endif
                }
                else
                {
                    /* if any waveforms are missed signal a failure of EGM capture */
                    if (tbv_moreEventsFlag)
                    {
                        tbm_postEvent( &tbm_Chan_MissedWF);
                    }
                    ++tbv_waveformsMissed;
#ifdef DEBUG_VARS_ON
                    ++debugVars.missingWFs;
#endif
                }
            }
            priorWFSequenceNumber = currentWFSequenceNumber;
        }
        else
        {
            /* We're not in EGM capture, these should be initialized for when */
            /* we do enter EGM capture */
#ifdef DEBUG_VARS_ON
            debugVars.mode3Waveforms = 0;
            debugVars.missingWFs     = 0;
#endif
            tbv_waveformsMissed      = 0;
            currentWFSequenceNumber  = rxFrameInfo.header & 0x07;
            priorWFSequenceNumber    = currentWFSequenceNumber;
        }

        /* End Section for EGM capture */

#ifdef DEBUG_VARS_ON
        ++debugVars.wfFrames;
        ++debugVars.goodFrames;
#endif

        /* check if there is a frame data "in progress" */
        if ((tbv_p_headTxBuffer->status == tbt_txInProgress)&&
            (tbv_p_headTxBuffer->frameType == tbt_dlData))
        {

            /* Post event to Channel Layer informing of DL completion */
            /* if it is a final frame */
            if ((tbv_p_headTxBuffer->finalFrame)&&(tbv_moreEventsFlag))
                tbm_postEvent(&tbm_Chan_FFTxDone);

            tbv_p_headTxBuffer->status = tbt_txAcked;

#ifdef DEBUG_STATE
            ++stateIndex;
            stateIndex       &= STATE_MASK;
            state[stateIndex] = tbt_uplinkCompleteWFpDFAcknowledged;
#endif
            /* data frame in progress has been acknowledged */
            /* increment the downlink sequence number */
            tbv_downlinkSequenceNumber = (tbv_downlinkSequenceNumber + 1) % 8;

            /* Data frame downlink is acknowledged (p bit) dequeue the frame */
            tbm_dequeueDownlink();

        }
        else /* check if there is a handshake in progress */
        if ((tbv_ackNakHandshakeQ.status == tbt_txInProgress)&&
            (tbv_ackNakHandshakeQ.frameType == tbt_dlHandshake))
        {
#ifdef DEBUG_STATE
            ++stateIndex;
            stateIndex       &= STATE_MASK;
            state[stateIndex] = tbt_handshakeAcknowledged;
#endif

            /* handshake was acknowledged, reset timer for next handshake */
            handshakeTickCounter20mS      = 0;
            timeToHandshake               = FALSE;

#ifdef DEBUG_VARS_ON
            debugVars.startedTransmitting = 5;
#endif

            /* handshake was acknowledged, so clean queue */
            tbv_ackNakHandshakeQ.frameType    = tbt_dlInvalid;
            tbv_ackNakHandshakeQ.status       = tbt_txNoStatus;
            tbv_ackNakHandshakeQ.attemptCount = 0;
        }
        else
        {
#ifdef DEBUG_STATE
            ++stateIndex;
            stateIndex       &= STATE_MASK;
            state[stateIndex] = tbt_uplinkCompleteWFpNothingAcked;
#endif
        }

        if (tbv_moreEventsFlag)
        {
            /* queue the frame to the Channel Layer */
            tbm_enqueueEntry((tbt_queuePointer *)  &tbv_ulFrameQ,
                             &receiveArray[rowOffset]);
            tbm_postEvent(&tbm_Chan_WaveformUL);

#ifdef DEBUG_STATE
            ++stateIndex;
            stateIndex       &= STATE_MASK;
            state[stateIndex] = tbt_ChannelWFQueued;
#endif
        }

        break;

    case tbt_ulDataf:

#ifdef DEBUG_VARS_ON
        ++debugVars.dataFrames;
        ++debugVars.goodFrames;
#endif
#ifdef DEBUG_STATE
        ++stateIndex;
        stateIndex                            &= STATE_MASK;
        state[stateIndex]                      = tbt_uplinkCompleteDFsgFinalBit;
#endif

        (&receiveArray[rowOffset])->finalFrame = TRUE;

        ++tbv_numberOfUnAckedFrames;

        tbv_expectedUplinkSequenceNumber = (tbv_expectedUplinkSequenceNumber + 1) % 8;

        if (tbv_moreEventsFlag)
        {
            /* Queue the downlink data */
            tbm_enqueueEntry((tbt_queuePointer *)  &tbv_ulFrameQ, &receiveArray[rowOffset]);
            tbm_postEvent(&tbm_Chan_DataFrameUL);
        }

        break;

    case tbt_ulData:
#ifdef DEBUG_VARS_ON
        ++debugVars.dataFrames;
        ++debugVars.goodFrames;
#endif
#ifdef DEBUG_STATE
        ++stateIndex;
        stateIndex                            &= STATE_MASK;
        state[stateIndex]                      = tbt_uplinkCompleteDFsgNofinal;
#endif
        (&receiveArray[rowOffset])->finalFrame = FALSE;

        ++tbv_numberOfUnAckedFrames;

        tbv_expectedUplinkSequenceNumber = (tbv_expectedUplinkSequenceNumber + 1) % 8;

        if (tbv_moreEventsFlag)
        {
            /* Queue the downlink data */
            tbm_enqueueEntry((tbt_queuePointer *)  &tbv_ulFrameQ, &receiveArray[rowOffset]);
            tbm_postEvent(&tbm_Chan_DataFrameUL);
        }

        break;

    case tbt_ulDatasb:
#ifdef DEBUG_VARS_ON
        ++debugVars.dataFramesBadSequence;
#endif
#ifdef DEBUG_STATE
        ++stateIndex;
        stateIndex       &= STATE_MASK;
        state[stateIndex] = tbt_uplinkCompleteDFsb;
#endif

        break;

    case tbt_ulWfmmID:
#ifdef DEBUG_VARS_ON
        ++debugVars.mismatchPgmrID;
#endif
#ifdef DEBUG_STATE
        ++stateIndex;
        stateIndex       &= STATE_MASK;
        state[stateIndex] = tbt_uplinkCompleteWFmmID;
#endif
        if (tbv_moreEventsFlag)
        {
            /* queue the frame to the Channel Layer */
            tbm_enqueueEntry((tbt_queuePointer *)  &tbv_ulFrameQ,
                             &receiveArray[rowOffset]);
            tbm_postEvent(&tbm_Chan_WaveformUL);

#ifdef DEBUG_STATE
            ++stateIndex;
            stateIndex       &= STATE_MASK;
            state[stateIndex] = tbt_ChannelWFQueued;
#endif
        }

        break;

    /* Marquis doesn't ACK explicitly, it ACKs through the WF p-bit set */
    /* This case would be for "Alpha" "DA+" derivative */
    case tbt_ulAck:
#ifdef DEBUG_STATE
        ++stateIndex;
        stateIndex       &= STATE_MASK;
        state[stateIndex] = tbt_uplinkCompleteACK;
#endif
        /* check if there is a frame data "in progress" */
        if ((tbv_p_headTxBuffer->status == tbt_txInProgress)&&
            (tbv_p_headTxBuffer->frameType == tbt_dlData))
        {

            /* Post event to Channel Layer informing of DL completion */
            /* if it is a final frame */
            if ((tbv_p_headTxBuffer->finalFrame)&&(tbv_moreEventsFlag))
                tbm_postEvent(&tbm_Chan_FFTxDone);

            tbv_p_headTxBuffer->status = tbt_txAcked;

#ifdef DEBUG_STATE
            ++stateIndex;
            stateIndex       &= STATE_MASK;
            state[stateIndex] = tbt_uplinkCompleteAckDFAcknowledged;
#endif
            /* data frame in progress has been acknowledged */
            /* increment the downlink sequence number */
            tbv_downlinkSequenceNumber = (tbv_downlinkSequenceNumber + 1) % 8;

            /* Data frame downlink is acknowledged (p bit) dequeue the frame */
            tbm_dequeueDownlink();

        }
        else /* check if there is a handshake in progress */
        if ((tbv_ackNakHandshakeQ.status == tbt_txInProgress)&&
            (tbv_ackNakHandshakeQ.frameType == tbt_dlHandshake))
        {
#ifdef DEBUG_STATE
            ++stateIndex;
            stateIndex       &= STATE_MASK;
            state[stateIndex] = tbt_handshakeAcknowledgedByAck;
#endif

            /* handshake was acknowledged, reset timer for next handshake */
            handshakeTickCounter20mS          = 0;
            timeToHandshake                   = FALSE;

            /* handshake was acknowledged, so clean queue */
            tbv_ackNakHandshakeQ.frameType    = tbt_dlInvalid;
            tbv_ackNakHandshakeQ.status       = tbt_txNoStatus;
            tbv_ackNakHandshakeQ.attemptCount = 0;
        }


        break;

    case tbt_ulAcksb:
#ifdef DEBUG_STATE
        ++stateIndex;
        stateIndex       &= STATE_MASK;
        state[stateIndex] = tbt_uplinkCompleteACKsb;
#endif

        break;

    case tbt_ulNak:
#ifdef DEBUG_STATE
        ++stateIndex;
        stateIndex       &= STATE_MASK;
        state[stateIndex] = tbt_uplinkCompleteNAK;
#endif
        /* Check if an implicit Acknowledgement through a NAK + 1 */
        if ((((rxFrameInfo.header & TBC_seqMask)-1)&TBC_seqMask)==(tbv_downlinkSequenceNumber))
        {
            if ((tbv_p_headTxBuffer->status == tbt_txInProgress)&&
                (tbv_p_headTxBuffer->frameType == tbt_dlData))
            {
                /* Post event to Channel Layer informing of DL completion */
                /* if it is a final frame */
                if ((tbv_p_headTxBuffer->finalFrame)&&(tbv_moreEventsFlag))
                    tbm_postEvent(&tbm_Chan_FFTxDone);

                tbv_p_headTxBuffer->status = tbt_txAcked;
                /* A downlink was acknowledged, NULL the pointer */
#ifdef DEBUG_STATE
                ++stateIndex;
                stateIndex       &= STATE_MASK;
                state[stateIndex] = tbt_uplinkCompleteNakDFAcknowledged;
#endif
                /* data frame in progress has been acknowledged */
                /* increment the downlink sequence number */
                tbv_downlinkSequenceNumber = (tbv_downlinkSequenceNumber + 1) % 8;

                /* Data frame downlink is acknowledged (p bit) dequeue the frame */
                tbm_dequeueDownlink();

            }
        }
        else
        if ((rxFrameInfo.header & TBC_seqMask) == (tbv_downlinkSequenceNumber))
        {

            /* check if there is a frame data "in progress" and max retries is hit */
            if ((tbv_p_headTxBuffer->status == tbt_txInProgress)&&
                (tbv_p_headTxBuffer->frameType == tbt_dlData)&&
                (tbv_p_headTxBuffer->attemptCount >= 6))
            {
#ifdef DEBUG_STATE
                ++stateIndex;
                stateIndex       &= STATE_MASK;
                state[stateIndex] = tbt_hitMaxRetriesDataByNak;
#endif
                /* hit max number of retries post a transmit timeout */
                if (tbv_moreEventsFlag)
                {
                    tbm_postEvent(&tbm_Chan_TxTimeout);
                }
            }

        }

        break;

    case tbt_ulNaksb:
#ifdef DEBUG_STATE
        ++stateIndex;
        stateIndex       &= STATE_MASK;
        state[stateIndex] = tbt_uplinkCompleteNAKsb;
#endif
        /* check if there is a frame data "in progress" and max retries is hit */
        if ((tbv_p_headTxBuffer->status == tbt_txInProgress)&&
            (tbv_p_headTxBuffer->frameType == tbt_dlData)&&
            (tbv_p_headTxBuffer->attemptCount >= 6))
        {
#ifdef DEBUG_STATE
            ++stateIndex;
            stateIndex       &= STATE_MASK;
            state[stateIndex] = tbt_hitMaxRetriesDataByNak;
#endif
            /* hit max number of retries post a transmit timeout */
            if (tbv_moreEventsFlag)
            {
                tbm_postEvent(&tbm_Chan_TxTimeout);
            }
        }

        break;


    default:
#ifdef DEBUG_STATE
        ++stateIndex;
        stateIndex       &= STATE_MASK;
        state[stateIndex] = tbt_uplinkCompleteInvalid;
#endif

        ++debugVars.invalidFrames;

        break;

    }

    /* Check if the instrument has had a valid Mode 1 uplink */
    /* The timer shall only expire if valid Mode 1 uplinks haven't been seen for 250mS */

    if ((rxFrameInfo.header & 0x60) == 0x20)
        tbm_reloadTimer(tbc_STOTimer);

    return;
} /* tbm_uplinkComplete()*/

/********************************************************************

FUNCTION: tbm_processUlWf()

DESCRIPTION:
    This function is called when an uplink waveform no - p completes.  It
    determines what the next downlink will be.

ARGS:
    <none>

RETURNS:
    <none>

NOTES:
    <none>

REQUIREMENTS:
    <none>

********************************************************************/
void tbm_processUlWf(void)
{
    tbt_dlFrameType    * currentDownlink = NULL;
    tbt_ulWaveFormType * rxPtr           = (tbt_ulWaveFormType *)tbv_headRxBuffer;

    /* Verify WF uplink has valid programmer id */
    if (  (rxPtr->pgmrId[0] == ((programmerID >> 8) & 0xff)) &&
          (rxPtr->pgmrId[1] == (programmerID & 0xff)) &&
          (tbv_linkMaintainSession))
    {

        /* if there are outstanding data frames we should have nothing in the queue */
        if (!tbv_numberOfUnAckedFrames)
            currentDownlink = (tbt_dlFrameType *)tbm_getQueueEntry(&tbv_dlFrameQ);

        /* Check for retried frames */
        if ((currentDownlink != NULL)&&(currentDownlink->status == tbt_txInProgress))
        {
            ++currentDownlink->attemptCount;

            /* check to see if we've maxed out retries */
            if (currentDownlink->attemptCount < 6)
                tbv_p_nextDownlink = currentDownlink;
            else
                tbv_p_nextDownlink = NULL;
        }
        else /* Check for retried handshakes */
        if ((tbv_ackNakHandshakeQ.status == tbt_txInProgress)&&
            (tbv_ackNakHandshakeQ.frameType == tbt_dlHandshake)&&
            (tbv_ackNakHandshakeQ.attemptCount < 6))
        {
#ifdef DEBUG_STATE
            ++stateIndex;
            stateIndex       &= STATE_MASK;
            state[stateIndex] = tbt_handshakeSentRetry;
#endif

            ++tbv_ackNakHandshakeQ.attemptCount;
            tbv_p_nextDownlink = &tbv_ackNakHandshakeQ;

#ifdef DEBUG_VARS_ON
            /* for logging some test information */
            if (tbv_ackNakHandshakeQ.attemptCount > debugVars.maxAttempts)
                debugVars.maxAttempts = tbv_ackNakHandshakeQ.attemptCount;
#endif

        }
        else /* Check for frame in the queue */
        if ((currentDownlink != NULL)&&(currentDownlink->status == tbt_txInQueue))
        {
            ++currentDownlink->attemptCount;
            if (currentDownlink->frameType == tbt_dlUFrameClose)
                currentDownlink->status = tbt_txInProgressNoRetry;
            else
                currentDownlink->status = tbt_txInProgress;

            /* It isn't a Close session, so it must be a data frame in the */
            /* synchronous queue so OR in the sequence number */
            if (currentDownlink->frameType != tbt_dlUFrameClose)
                currentDownlink->dlHeader |= tbv_downlinkSequenceNumber;

#ifdef DEBUG_STATE
            ++stateIndex;
            stateIndex       &= STATE_MASK;
            state[stateIndex] = tbt_dataFrameSentWaitingAck;
#endif
            if (currentDownlink->finalFrame)
                currentDownlink->dlHeader |= 0x08;

            tbv_p_nextDownlink = currentDownlink;

        }
        else /* Time to send ACK/NAK? */
        if (tbv_p_ackNakdl)
        {
            tbv_p_nextDownlink = tbv_p_ackNakdl;
        }
        else   /* Time for handshake? */
        if (timeToHandshake)
        {
            timeToHandshake                   = FALSE;
            tbv_ackNakHandshakeQ.length       = 3;
            tbv_ackNakHandshakeQ.attemptCount = 0;
            tbv_ackNakHandshakeQ.syncType     = tbc_sc_normal;
            tbv_ackNakHandshakeQ.uplinkRate   =  currentUplinkRate; /* leave as is */

            tbv_ackNakHandshakeQ.pgmrId[0]    = (programmerID >> 8) & 0xff;
            tbv_ackNakHandshakeQ.pgmrId[1]    = programmerID & 0xff;

            /* It is time to handshake, if no outstanding data frames send the handshake */
            /* otherwise an ack must be sent */
            if (!tbv_numberOfUnAckedFrames)
            {
#ifdef DEBUG_VARS_ON
                ++debugVars.handshakesStarted;
#endif
#ifdef DEBUG_STATE
                ++stateIndex;
                stateIndex                    &= STATE_MASK;
                state[stateIndex]              = tbt_handshakeSentWaitingAck;
#endif
                tbv_ackNakHandshakeQ.status    = tbt_txInProgress;
                tbv_ackNakHandshakeQ.dlHeader  = 0x59;
                tbv_ackNakHandshakeQ.frameType = tbt_dlHandshake;

            }
            else
            {
#ifdef DEBUG_STATE
                ++stateIndex;
                stateIndex                    &= STATE_MASK;
                state[stateIndex]              = tbt_downlinkACKNAKSent;
#endif
                tbv_ackNakHandshakeQ.status    = tbt_txInProgressNoRetry;
                tbv_ackNakHandshakeQ.dlHeader  = TBC_dlAck | (tbv_expectedUplinkSequenceNumber & 0x7);
                tbv_ackNakHandshakeQ.frameType = tbt_dlAck;

            }

            tbv_p_nextDownlink = &tbv_ackNakHandshakeQ;
        }
        else
        {
            /* it is time to wack */
            tbv_p_nextDownlink = (tbt_dlFrameType *)&tbv_wack;
#ifdef DEBUG_VARS_ON
            ++debugVars.wacksStarted;
#endif
        }

    }
    else
    {

        /* There is an invalid programmer ID for this waveform */
        /* uplinkComplete needs alternate processing */
        rxFrameInfo.headerType = tbt_ulWfmmID;
    }

    return;
} /* tbm_processUlWf() */

/********************************************************************

FUNCTION: tbm_processUlWfp()

DESCRIPTION:
    This function is called when an uplink waveform completes with
    a p-bit set.  It determines what the next downlink will be.

ARGS:
    <none>

RETURNS:
    <none>

NOTES:
    <none>

REQUIREMENTS:
    <none>

********************************************************************/
void tbm_processUlWfp(void)
{
    static tbt_ulWaveFormType *rxPtr;

    rxPtr = (tbt_ulWaveFormType *)tbv_headRxBuffer;

    /* Verify WF uplink has valid programmer id */
    if (  (rxPtr->pgmrId[0] == ((programmerID >> 8) & 0xff)) &&
          (rxPtr->pgmrId[1] == (programmerID & 0xff)) &&
          (tbv_linkMaintainSession))
    {

        if (timeToHandshake)
        {
#ifdef DEBUG_VARS_ON
            ++debugVars.handshakesStarted;
#endif
#ifdef DEBUG_STATE
            ++stateIndex;
            stateIndex                       &= STATE_MASK;
            state[stateIndex]                 = tbt_handshakeSentWaitingAck;
#endif

            timeToHandshake                   = FALSE;
            handshakeTickCounter20mS          = 0;

            tbv_ackNakHandshakeQ.length       = 3;
            tbv_ackNakHandshakeQ.attemptCount = 0;
            tbv_ackNakHandshakeQ.status       = tbt_txInProgress;
            tbv_ackNakHandshakeQ.syncType     = tbc_sc_normal;
            tbv_ackNakHandshakeQ.uplinkRate   =  currentUplinkRate; /* leave as is */
            tbv_ackNakHandshakeQ.dlHeader     = 0x59;
            tbv_ackNakHandshakeQ.frameType    = tbt_dlHandshake;

            tbv_ackNakHandshakeQ.pgmrId[0]    = (programmerID >> 8) & 0xff;
            tbv_ackNakHandshakeQ.pgmrId[1]    = programmerID & 0xff;

            tbv_p_nextDownlink                = &tbv_ackNakHandshakeQ;

        }
        else
        {
#ifdef DEBUG_VARS_ON
            ++debugVars.wacksStarted;
#endif
            /* it is time to wack */
            tbv_p_nextDownlink = (tbt_dlFrameType *)&tbv_wack;
        }

    }
    else
    {
        /* There is an invalid programmer ID for this waveform */
        /* uplinkComplete needs alternate processing */
        rxFrameInfo.headerType = tbt_ulWfmmID;
    }

    return;
} /* tbm_processUlWfp() */

/********************************************************************

FUNCTION: tbm_processUlUf()

DESCRIPTION:
    This function is called when an uplink UFrame completes.  It
    currently contains no processing since no downlink will be
    sent following a UFrame.

ARGS:
    <none>

RETURNS:
    <none>

NOTES:
    <none>

REQUIREMENTS:
    <none>

********************************************************************/
void tbm_processUlUf(void)
{

    return;
} /* tbm_processUlUf() */
/********************************************************************

FUNCTION: tbm_processUlDfsg()

DESCRIPTION:
    This function is called when an uplink dataframe completes.  It
    determines what the next downlink will be.  Usually an ACK following
    a data frame.

ARGS:
    <none>

RETURNS:
    <none>

NOTES:
    <none>

REQUIREMENTS:
    <none>

********************************************************************/
void tbm_processUlDfsg(void)
{

    if ((tbv_numberOfUnAckedFrames >= 7) || (timeToHandshake == TRUE))
    {
        tbv_ackNakHandshakeQ.length       = 3;
        tbv_ackNakHandshakeQ.attemptCount = 0;
        tbv_ackNakHandshakeQ.status       = tbt_txInProgressNoRetry;
        tbv_ackNakHandshakeQ.syncType     = tbc_sc_normal;
        tbv_ackNakHandshakeQ.uplinkRate   =  currentUplinkRate; /* leave as is */
        tbv_ackNakHandshakeQ.dlHeader     = TBC_dlAck | (tbv_expectedUplinkSequenceNumber & 0x7);
        tbv_ackNakHandshakeQ.frameType    = tbt_dlAck;

        tbv_ackNakHandshakeQ.pgmrId[0]    = (programmerID >> 8) & 0xff;
        tbv_ackNakHandshakeQ.pgmrId[1]    = programmerID & 0xff;

        /* Immediate ACK is config setup that will be true for DA+ this allows   */
        /* ACK downlink immediately following data frame uplink.  Marquis needs  */
        /* to wait until a Waveform uplink with no p-bit set to downlink the ACK */
        if (tbv_immediateACK == TRUE)
        {
            tbv_p_nextDownlink = &tbv_ackNakHandshakeQ;
        }
        else
        {
            tbv_p_ackNakdl = &tbv_ackNakHandshakeQ;
        }

    }

    return;
} /* tbm_processUlDfsg() */

/********************************************************************

FUNCTION: tbm_processUlDfsb()

DESCRIPTION:
    This function is called when an uplink dataframe completes with a
    bad sequence number.  It determines what the next downlink will be.
    A NAK is sent requesting the "proper" uplink data frame.

ARGS:
    <none>

RETURNS:
    <none>

NOTES:
    <none>

REQUIREMENTS:
    <none>

********************************************************************/
void tbm_processUlDfsb(void)
{
    tbv_ackNakHandshakeQ.length       = 3;
    tbv_ackNakHandshakeQ.attemptCount = 0;
    tbv_ackNakHandshakeQ.status       = tbt_txInProgressNoRetry;
    tbv_ackNakHandshakeQ.syncType     = tbc_sc_normal;
    tbv_ackNakHandshakeQ.uplinkRate   =  currentUplinkRate; /* leave as is */
    tbv_ackNakHandshakeQ.dlHeader     = TBC_dlNak | (tbv_expectedUplinkSequenceNumber & 0x7);
    tbv_ackNakHandshakeQ.frameType    = tbt_dlNak;

    tbv_ackNakHandshakeQ.pgmrId[0]    = (programmerID >> 8) & 0xff;
    tbv_ackNakHandshakeQ.pgmrId[1]    = programmerID & 0xff;

    /* Immediate ACK is config setup that will be true for DA+ this allows   */
    /* ACK downlink immediately following data frame uplink.  Marquis needs  */
    /* to wait until a Waveform uplink with no p-bit set to downlink the ACK */
    if (tbv_immediateACK == TRUE)
    {
        tbv_p_nextDownlink = &tbv_ackNakHandshakeQ;
    }
    else
    {
        tbv_p_ackNakdl = &tbv_ackNakHandshakeQ;
    }

    return;
} /* tbm_processUlDfsb() */

/********************************************************************

FUNCTION: tbm_processUlDfsgf()

DESCRIPTION:
    This function is called when an uplink dataframe with the final
    bit set completes.  An ACK is sent validating reception of frames.

ARGS:
    <none>

RETURNS:
    <none>

NOTES:
    <none>

REQUIREMENTS:
    <none>

********************************************************************/
void tbm_processUlDfsgf(void)
{

    tbv_ackNakHandshakeQ.length       = 3;
    tbv_ackNakHandshakeQ.attemptCount = 0;
    tbv_ackNakHandshakeQ.status       = tbt_txInProgress;
    tbv_ackNakHandshakeQ.syncType     = tbc_sc_normal;
    tbv_ackNakHandshakeQ.uplinkRate   =  currentUplinkRate; /* leave as is */
    tbv_ackNakHandshakeQ.dlHeader     = TBC_dlAck | (tbv_expectedUplinkSequenceNumber & 0x7);
    tbv_ackNakHandshakeQ.frameType    = tbt_dlAck;

    tbv_ackNakHandshakeQ.pgmrId[0]    = (programmerID >> 8) & 0xff;
    tbv_ackNakHandshakeQ.pgmrId[1]    = programmerID & 0xff;

    /* Immediate ACK is config setup that will be true for DA+ this allows   */
    /* ACK downlink immediately following data frame uplink.  Marquis needs  */
    /* to wait until a Waveform uplink with no p-bit set to downlink the ACK */
    if (tbv_immediateACK == TRUE)
    {
        tbv_p_nextDownlink = &tbv_ackNakHandshakeQ;
    }
    else
    {
        tbv_p_ackNakdl = &tbv_ackNakHandshakeQ;
    }

    return;
} /* tbm_processUlDfsgf() */

/********************************************************************

FUNCTION: tbm_processUlAcksg()

DESCRIPTION:
    This function is called when an uplink ACK completes.

ARGS:
    <none>

RETURNS:
    <none>

NOTES:
    <none>

REQUIREMENTS:
    <none>

********************************************************************/
void tbm_processUlAcksg(void)
{
    /* Uplink ACKs/NAKs are specific to Alphas and DA+s */

    /* This process function will do nothing */
    /* For greatest throughput (in the Alpha/DA+ case) it can immediately */
    /* send the next downlink in the downlink Queue, if a downlink exists */

    return;
} /* tbm_processUlAcksg() */

/********************************************************************

FUNCTION: tbm_processUlAcksb()

DESCRIPTION:
    This function is called when an uplink ACK with a bad sequence
    number completes.  There is no processing in this case.  The
    instrument will ignore this uplink.

ARGS:
    <none>

RETURNS:
    <none>

NOTES:
    <none>

REQUIREMENTS:
    <none>

********************************************************************/
void tbm_processUlAcksb(void)
{
    tbt_dlFrameType * currentDownlink = NULL;

    currentDownlink = (tbt_dlFrameType *)tbm_getQueueEntry(&tbv_dlFrameQ);

    /* Check for retried frames */
    if ((currentDownlink != NULL)&&(currentDownlink->status == tbt_txInProgress))
    {
        ++currentDownlink->attemptCount;

        /* check to see if we've maxed out retries */
        if (currentDownlink->attemptCount < 6)
            tbv_p_nextDownlink = currentDownlink;
        else
            tbv_p_nextDownlink = NULL;
    }

    return;
} /* tbm_processUlAcksb() */

/********************************************************************

FUNCTION: tbm_processUlNaksg()

DESCRIPTION:
    This function is called when an uplink NAK with a good sequence
    number completes.  It determines what the next downlink will be.
    Usually a retry of a dataframe downlink occurs.

ARGS:
    <none>

RETURNS:
    <none>

NOTES:
    <none>

REQUIREMENTS:
    <none>

********************************************************************/
void tbm_processUlNaksg(void)
{
    tbt_dlFrameType * currentDownlink = NULL;

    currentDownlink = (tbt_dlFrameType *)tbm_getQueueEntry(&tbv_dlFrameQ);


    if ((((rxFrameInfo.header & TBC_seqMask) - 1) & TBC_seqMask) == (tbv_downlinkSequenceNumber))
    {
        /* uplink NAK has sequence number of 1 greater than the last downlink sequence number. */
        /* The frame shall be marked as ACK'd (implicitly) in uplink complete.  The following */
        /* downlink shall be sent if it exists */

    }
    else
    if ((rxFrameInfo.header & TBC_seqMask) == (tbv_downlinkSequenceNumber))
    {
        /* A resend of the current downlink, make sure it's status is correct */

        if ((currentDownlink != NULL)&&(currentDownlink->status == tbt_txInProgress))
        {
            ++currentDownlink->attemptCount;

            /* check to see if we've maxed out retries */
            if (currentDownlink->attemptCount < 6)
                tbv_p_nextDownlink = currentDownlink;
            else
                tbv_p_nextDownlink = NULL;
        }

    }

    return;
} /* tbm_processUlNaksg() */

/********************************************************************

FUNCTION: tbm_processUlNaksb()

DESCRIPTION:
    This function is called when an uplink NAK with a bad sequence
    number completes.  No processing follows this uplink.

ARGS:
    <none>

RETURNS:
    <none>

NOTES:
    <none>

REQUIREMENTS:
    <none>

********************************************************************/
void tbm_processUlNaksb(void)
{
    /* No downlink or processing for NAK with bad sequence number */

    return;
} /* tbm_processUlNaksb() */

/********************************************************************

FUNCTION: tbm_shortTimeout()

DESCRIPTION:
    This function is called when the instrument hasn't seen valid
    Mode 1 uplinks for 250mS.  An event is posted to the channel layer
    to inform it of this.

ARGS:
    <none>

RETURNS:
    <none>

NOTES:
    <none>

REQUIREMENTS:
    <none>

********************************************************************/
void tbm_shortTimeout(void)
{
#ifdef DEBUG_STATE
    ++stateIndex;
    stateIndex       &= STATE_MASK;
    state[stateIndex] = tbt_shortTimeout;
#endif

#ifdef DEBUG_SHORT_TIMEOUT
        #warn "Telemetry B Short Timeout Testing Enabled."
    GLB_SET_XF;
#endif

    if (tbv_moreEventsFlag)
    {
        tbm_postEvent(&tbm_Chan_ShortTimeOut);
    }

    return;
} /* tbm_shortTimeoiut() */


/********************************************************************

FUNCTION: tbm_dequeueDownlink

DESCRIPTION:  Remove a downlink from the queue

ARGS:
    <none>

RETURNS:
    <none>

REQUIREMENTS:
    <none>

********************************************************************/
void tbm_dequeueDownlink(void)
{
    tbm_dequeueEntry(&tbv_dlFrameQ);

    return;
} /* tbm_dequeueDownlink() */

