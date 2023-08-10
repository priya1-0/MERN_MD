/* Copyright (c) 2001 by Medtronic Inc.  All Rights Reserved */
/********************************************************************
DOCUMENT

$Revision$

$Date$

$RCSfile$

MODULE:       tbm_events.c   area = telemetry B

FUNCTIONS:
  tbm_clearMoreEventsFlag
  tbm_clearTimerExpiredFlag
  tbm_eventProcessor
  tbm_getEvent
  tbm_initializeEvents
  tbm_noEvents
  tbm_postEvent
  tbm_setMoreEventsFlag
  tbm_setTimerExpiredFlag

DESCRIPTION:
  Event handler for the Telemetry Channel.  Telemetry B functions
  are, in part, event driven. An event consists of an identifier
  to indicate the action which should be taken when the event is
  processed.

  CONSTRAINTS:  None of these functions can be used within the context
  of an interrupt.

ENDDOCUMENT
********************************************************************/
/*
 * Includes
 */
#include "types.h"
#include <string.h>

#define DEFINED_HERE
#include "tbm_events.h"
#undef DEFINED_HERE

#include "tbm_fsm.h"
#include "link.h"
#include "tbm_timer.h"
#include "tbm_channel.h"
#include "tbm_main.h"
#include "..\bsm\bsm_Event.h"

/********************************************************************
*****     GLOBAL DATA
********************************************************************/
/* Event manager array */
tbt_Event tbv_eventList[tbc_MaxEvents];

/* linked event list controls */
tbt_Event *tbv_p_eventHead;
tbt_Event *tbv_p_eventTail;
tbt_Event *tbv_p_freeEvents;

/* Statistics counters -
 * current number of events on the event list */
BYTE tbv_eventCounter;

/* tracks the events high water mark */
BYTE tbv_eventHighMark;

/*******************************************************************
*/

#ifdef DEBUG_EVENTS
/* Array of debug events */
USHORT tbv_debugEventsIndex;
UINT32 tbv_debugEvents[50];
#endif

/*******************************************************************
*/

void tbm_noEvent(struct tbm_Chan *);
void tbm_setMoreEventsFlag(void);

/********************************************************************

FUNCTION:  tbm_clearMoreEventsFlag

DESCRIPTION:
  This function provides access to a flag which is used to determine
  when an Application Request has been completed.  This function clears
  the flag which indicates that the Request has been completed.

INPUT:
  none

OUTPUT:
  none

********************************************************************/

void tbm_clearMoreEventsFlag(void)
{
    tbv_moreEventsFlag = FALSE;
}

/********************************************************************

FUNCTION: tbm_clearTimerExpiredFlag

DESCRIPTION:
  This function clears the expired timer flag.  It is called once all
  expired timer have been processed.

INPUT:
  none

OUTPUT:
  none

********************************************************************/

void tbm_clearTimerExpiredFlag(void)
{
    tbv_timerExpiredFlag = FALSE;
}

/********************************************************************

FUNCTION:  tbm_eventProcessor

DESCRIPTION:
  The is the core operating loop for the Telemetry Module.  It is designed
  as a mechanism for communicating between the Telemetry State Machine, the
  Application and the interrupt driven Telemetry Link layer.

  The Application will call one of the functions from tbm_handler which will
  start the Event Processor with an initial event.  All events are entries to the
  Telemetry State Machine which will post other events or call processing functions
  to handle the current event in conjunction with the current Telemetry State.

  The Telemetry Link layer is interrupt driven from the FPGA Transmit and Receive
  functions.  The Link communicates with the Channel layer via posting an event
  for the event processor.

  The Event Processer also coordinates the exectution of functions associated
  expired timers.

  The Event Processer may also be used to handle processes which have session
  wide impact such as adding a timer tick to a response buffer.

INPUT:
  none

OUTPUT:
  none

********************************************************************/
void tbm_eventProcessor(void)
{
    eventPtrType fsmPtr = &tbm_noEvent;

    tbm_setMoreEventsFlag();
    while (tbv_moreEventsFlag)
    {
        /*
         * Retrieve the next event off the event queue
         */
        fsmPtr = tbm_getEvent();
        /*
         * Process the current event
         */
        if (NULL != fsmPtr)
        {
            (*fsmPtr) (&tbv_Channel);
        }
        /*
           Check any timers that are ready to run.
         */
        if (tbv_timerExpiredFlag)
        {
            tbm_processExpiredTimers();
        }

    }                           /* end of while */
}

/********************************************************************

FUNCTION:  tbm_getEvent

DESCRIPTION:
  This function gets oldest event of the event list and returns its event ID.

  The event removed from the list and its former location is returned to the
  free list.

INPUT:
  none

OUTPUT:
  eventID = event identifier.

********************************************************************/
eventPtrType tbm_getEvent(void)
{
    eventPtrType fsmPtr = &tbm_noEvent;
    tbt_Event    *p_tmp;

    /*
       Disable Interrupts
     */
    tbm_disableInterrupts();

    if (tbv_p_eventHead != NULL)
    {

        fsmPtr                    = tbv_p_eventHead->eventPtr;
        tbv_p_eventHead->eventPtr = &tbm_noEvent;

        /*
         * unlink event from posted list
         */
        p_tmp                     = tbv_p_eventHead;
        tbv_p_eventHead           = p_tmp->p_next;
        if (tbv_p_eventTail == p_tmp)
            tbv_p_eventTail = NULL;

        /*
         * put it on the free list
         */
        p_tmp->p_next    = tbv_p_freeEvents;

        tbv_p_freeEvents = p_tmp;

        /*
         * decrement event counter
         */
        tbv_eventCounter--;

#ifdef DEBUG_EVENTS
        if ((fsmPtr != &tbm_Chan_WaveformUL)
            && (fsmPtr != &tbm_Chan_UnNumFrameUL))
        {
            tbv_debugEvents[tbv_debugEventsIndex]     =
                (0xA000 | tbv_debugEventsIndex);
            tbv_debugEvents[tbv_debugEventsIndex + 1] = (UINT32)(fsmPtr);
            tbv_debugEventsIndex                      = (tbv_debugEventsIndex + 2) % 50;
        }
#endif
    }
    /*
       Enable Interrupts
     */
    tbm_enableInterrupts();

    return (fsmPtr);
}                               /* end tbm_getEvent */

/********************************************************************

FUNCTION:  tbm_initializeEvents

DESCRIPTION:
  This function initializes the event management subsystem.

INPUT:
  none

OUTPUT:
  none

********************************************************************/
void tbm_initializeEvents(void)
{
    USHORT i;

    tbm_clearMoreEventsFlag();
    /*
     * initialize event list
     */
    for (i = 0; i <= (tbc_MaxEvents - 1); i++)
    {
        tbv_eventList[i].eventPtr = &tbm_noEvent;
        tbv_eventList[i].p_next   = &(tbv_eventList[i + 1]);
    }

    /*
       terminate last item in linked list
     */

    tbv_eventList[tbc_MaxEvents - 1].p_next = NULL;

    /*
     * put all events on the empty list
     */
    tbv_p_eventHead                         = NULL;
    tbv_p_eventTail                         = NULL;
    tbv_p_freeEvents                        = tbv_eventList;

    /*
     * initialize stat counters
     */
    tbv_eventCounter                        = 0;
    tbv_eventHighMark                       = 0;

#ifdef DEBUG_EVENTS
    for (i = 0; i < 50; i++)
        tbv_debugEvents[i] = 0xffff;
    tbv_debugEventsIndex = 0;
#endif

    return;
}                               /* end tbm_initializeEvents */

/********************************************************************

FUNCTION: tbm_noEvent

DESCRIPTION:
  A null function for execution when there are no other
  events pending.  Available for use by the event manager.

INPUT:
  noChannel : A dummy state machine.

OUTPUT:
  none

********************************************************************/
void tbm_noEvent(struct tbm_Chan *Dummy)
{
    return;
}

/********************************************************************

FUNCTION:  tbm_postEvent

DESCRIPTION:  Adds an event to the event list.

INPUT:
  fsmPtr : A pointer to a state machine function aka event ID. Or a
           default function if no events are posted.

OUTPUT:
  none

********************************************************************/
void tbm_postEvent(eventPtrType fsmPtr)
{
    /*
       Disable Interrupt
     */
    tbm_disableInterrupts();

    if (tbv_p_eventTail != NULL)
    {
        /*
         * at least one event is already on the posted list
         * so put the new event at the end
         */
        if (tbv_p_freeEvents != NULL)
        {
            tbv_p_eventTail->p_next = tbv_p_freeEvents;
            tbv_p_eventTail         = tbv_p_freeEvents;
            tbv_p_freeEvents        = tbv_p_eventTail->p_next;
        }
        else
        {
            /*
               No events available.
             */
            bsm_EHLock("tbm_postEvent: no events available.");
        }
    }
    else
    {
        /*
         * empty event list
         */
        tbv_p_eventTail  = tbv_p_freeEvents;
        tbv_p_eventHead  = tbv_p_freeEvents;
        tbv_p_freeEvents = tbv_p_eventTail->p_next;
    }

    /*
     * add event to the end of the list
     */
    tbv_p_eventTail->eventPtr = fsmPtr;
    tbv_p_eventTail->p_next   = NULL;

    /*
     * update status counters
     */
    tbv_eventCounter++;
    if (tbv_eventCounter > tbv_eventHighMark)
        tbv_eventHighMark = tbv_eventCounter;

#ifdef DEBUG_EVENTS
    if ((fsmPtr != &tbm_Chan_WaveformUL) && (fsmPtr != &tbm_Chan_UnNumFrameUL))
    {
        tbv_debugEvents[tbv_debugEventsIndex]     = (0xB000 | tbv_debugEventsIndex);
        tbv_debugEvents[tbv_debugEventsIndex + 1] = (UINT32)fsmPtr;
        tbv_debugEventsIndex                      = (tbv_debugEventsIndex + 2) % 50;
    }
#endif
    /*
       Enable interrupt
     */
    tbm_enableInterrupts();

    return;
}                               /* end tbm_postEvent */

/********************************************************************

FUNCTION:
  tbm_setMoreEventsFlag

DESCRIPTION:
  This function provides access to a flag which is used to determine
  when a Application Request has been completed.  This function sets
  the flag which indicates that there is more to do to complete the
  Request.

INPUT:
  none

OUTPUT:
  none

********************************************************************/

void tbm_setMoreEventsFlag(void)
{
    tbv_moreEventsFlag = TRUE;
}

/********************************************************************

FUNCTION:
  tbm_setTimerExpiredFlag

DESCRIPTION:
  This function sets the expired timer flag.  It is called when a timer
  has expired.

INPUT DATA:
  none

OUTPUT RESULTS:

********************************************************************/

void tbm_setTimerExpiredFlag(void)
{
    tbv_timerExpiredFlag = TRUE;
}

