/********************************************************************
DOCUMENT

$Revision$

$Date$

$RCSfile$

NAME:  tbm_tctl.c

PURPOSE  This module provides an interface between the Channel and
         the Link layer.

USAGE:  none

ENDDOCUMENT
********************************************************************/
#include "link.h"
#include "tbm_main.h"
#include "tbm_channel.h"
#include "tbm_trx.h"

#define DEFINED_HERE
#include "tbm_tctl.h"
#undef DEFINED_HERE

/********************************************************************

FUNCTION: tbm_linkAutoID()

DESCRIPTION:
    This function provides the interface for the channel layer to
    perfom auto ID

ARGS:
    tbt_dlFrameType * dlFrame

RETURNS:
    TRUE - if frame was successfully transmitted.
    FALSE - if frame wasn't transmitted.

NOTES:
    <none>

REQUIREMENTS:
    <none>

********************************************************************/
BOOL tbm_linkAutoID(tbt_dlFrameType * dlFrame)
{
    BYTE header   = TBC_dlHeaderUFrameMode0;
    BOOL txQueued = TRUE;

    if (!tbv_txInProgress)
    {
        tbv_txInProgress                 = TRUE;

        tbv_p_nextDownlink               = dlFrame;
        tbv_p_nextDownlink->frameType    = tbt_dlUFrame;
        tbv_p_nextDownlink->status       = tbt_txInProgressNoRetry;
        tbv_p_nextDownlink->attemptCount = 0;

        tbv_p_nextDownlink->dlHeader     = header;

        // start Auto-ID frame transmission
        // this will transmit tbv_p_nextDownlink
        tbm_txFrame();
    }
    else
    {
        txQueued = FALSE;
    }

    return (txQueued);
}

/********************************************************************

FUNCTION: tbm_OpenDLReq()

DESCRIPTION:
    This function provides the interface for the channel layer to
    interface to the link layer for an Open Session.

ARGS:
    <none>

RETURNS:
    TRUE - if frame was successfully transmitted.
    FALSE - if frame wasn't transmitted.

NOTES:
    <none>

REQUIREMENTS:
    <none>

********************************************************************/
BOOL tbm_OpenDLReq(tbt_dlFrameType * dlFrame)
{
    BYTE header   = TBC_dlHeaderUFrameMode0;
    BOOL txQueued = TRUE;

    if (!tbv_txInProgress)
    {
        tbv_txInProgress                 = TRUE;

        tbv_p_nextDownlink               = dlFrame;
        tbv_p_nextDownlink->dlHeader     = header;
        tbv_p_nextDownlink->frameType    = tbt_dlUFrameOpen;
        tbv_p_nextDownlink->status       = tbt_txInProgressNoRetry;
        tbv_p_nextDownlink->attemptCount = 0;

        // start Open Session frame transmission
        // this will transmit tbv_p_nextDownlink
        tbm_txFrame();
    }
    else
    {
        txQueued = FALSE;
    }

    return (txQueued);
}
