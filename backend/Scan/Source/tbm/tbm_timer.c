/* Copyright (c) 2001 by Medtronic Inc.  All Rights Reserved */
/********************************************************************
DOCUMENT

$Revision$

$Date$

$RCSfile$

MODULE:
  tbm_timer.c  area = Telemetry B

FUNCTIONS:
  tbm_cancelTimer
  tbm_initTimers
  tbm_updateTimers
  tbm_processExpiredTimers
  tbm_addTimer
  tbm_reloadTimer
  tbm_reloadAllTimers
  tbm_nullTimer

DESCRIPTION:
  This module contains the functions used to set up and maintain timers
  for general Telemetry module use.  There are a maximum of eight timers
  available.

  All timers are based of the governing (Nucleus) timer tbv_TelemBTimer.  All
  expireTime and reloadTime values indicate the number of times tbv_TelemBTimer
  will expire before these associated Telemetry Timers will expire.

ENDDOCUMENT
********************************************************************/
#include <csl.h>
#include <csl_gpio.h>

#include "..\types.h"
#include <string.h>

#define DEFINED_HERE
#include "tbm_timer.h"
#undef DEFINED_HERE

#include "link.h"
#include "tbm_channel.h"
#include "tbm_events.h"
#include "tbm_main.h"
#include "..\bsm\bsm_Event.h"

void tbm_nullTimer(void);

/********************************************************************
*****     STATIC DATA
********************************************************************/
/* Timer manager arrays */
static tbt_timerType tbv_timerList[tbc_MaxTimers];

/*linked timer list controls*/
static tbt_timerType *tbv_p_timerHead;
static tbt_timerType *tbv_p_freeTimers;

/* current number of timers */
static UINT16 tbv_timerCounter;

/* tracks the timers high water mark */
static UINT16 tbv_timerHighMark;

/*******************************************************************
*/

/********************************************************************

FUNCTION:       tbm_cancelTimer

DESCRIPTION:    Remove the oldest timer Identified by timerID from the
                timer list.

INPUT:
  timerID : the ID of the timer to be cancelled

OUTPUT:
  none

********************************************************************/
void tbm_cancelTimer(tbt_timerID timerID)
{
    tbt_timerType *p_tmpPtr;
    tbt_timerType *p_tmpPrevPtr;
    tbt_timerType *p_tmpPrevFreePtr;
    tbt_timerType *p_tmpFreePtr = NULL;

    /*
       Disable Interrupts
     */
    tbm_PRDIntDisable();


    /*
       Start at the beginning
     */
    p_tmpPtr     = tbv_p_timerHead;
    p_tmpPrevPtr = tbv_p_timerHead;

    /*
       Go through the whole list
     */
    while (p_tmpPtr != NULL)
    {
        /*
           Looking for the desired timer
         */
        if (p_tmpPtr->timerID == timerID)
        {
            /*
               Keep pointer to timer to be freed
             */
            p_tmpFreePtr     = p_tmpPtr;
            p_tmpPrevFreePtr = p_tmpPrevPtr;

        }
        /*
           Get the next timer
         */
        p_tmpPrevPtr = p_tmpPtr;
        p_tmpPtr     = p_tmpPtr->p_next;

    }                           /* while (p_tmpPtr != NULL) */

    if (p_tmpFreePtr != NULL)
    {
        /*
           Check if at beginning of timer list
         */
        p_tmpPtr = p_tmpFreePtr;

        if (p_tmpPtr == tbv_p_timerHead)
        {
            /*
               make new head if this timer is current head
             */
            tbv_p_timerHead = tbv_p_timerHead->p_next;
        }

        /*
           clear out timer
         */
        p_tmpFreePtr->timerID         = tbc_nullTimer;
        p_tmpFreePtr->p_timerFunction = tbm_nullTimer;
        p_tmpFreePtr->reloadTime      = 0;
        p_tmpFreePtr->expireTime      = 0;

        p_tmpPrevFreePtr->p_next      = p_tmpFreePtr->p_next;

        /*
           Make the old head of the free list this guy's next
         */
        p_tmpFreePtr->p_next          = tbv_p_freeTimers;

        /*
           crown the new head of the list
         */
        tbv_p_freeTimers              = p_tmpFreePtr;

        tbv_timerCounter--;
    }

    /*
       Enable Interrupts
     */
    tbm_PRDIntEnable();

}                               /* end tbm_cancelTimer */

/********************************************************************

FUNCTION:       tbm_initTimers

DESCRIPTION:
  The tbv_timerList array is initialized to its default settings.  The
  various pointers and counters are initialized.

INPUT:
  none

OUTPUT:
  none

********************************************************************/
void tbm_initTimers(void)
{
    UINT16 i;

    /*
     * Initialize all Timers
     */
    for (i = 0; i <= (tbc_MaxTimers - 1); i++)
    {
        tbv_timerList[i].expireTime      = 0;
        tbv_timerList[i].reloadTime      = 0;
        tbv_timerList[i].timerID         = tbc_nullTimer;
        tbv_timerList[i].p_timerFunction = &tbm_nullTimer;
        tbv_timerList[i].p_next          = &(tbv_timerList[i + 1]);
    }

    /*
       terminate last item in linked list
     */
    tbv_timerList[tbc_MaxTimers - 1].p_next = NULL;

    /*
     * put all scheduled timers on empty list
     */
    tbv_p_timerHead                         = NULL;
    tbv_p_freeTimers                        = tbv_timerList;

    /*
     * initialize stat counters
     */
    tbv_timerCounter                        = 0;
    tbv_timerHighMark                       = 0;

    return;
}                               /* end tbm_initTimers */

/********************************************************************

FUNCTION:       tbm_updateTimers

DESCRIPTION:
  This function is call from the periodic (Nucleus) timer tbv_TelemBTimer.
  It decrements the expireTime of each active timer and checks to see
  if the timer has expired.  If any timer has expired a Flag will be
  set to notify the Event Processor of that fact.

  Note: The functions associated with expired timer can not be called
  directly from this function because this function is reached from an
  interrupt.  Telemetry function calls must be called from the Event Processor
  in order to ensure sequential execution and to protect the integrety
  of global data.

INPUT:
  none

OUTPUT:
  none

********************************************************************/
void tbm_updateTimers(void)
{
    tbt_timerType *p_tmpPtr;

    if (tbv_moreEventsFlag)
    {
        /*
           Start at head of list
         */
        p_tmpPtr = tbv_p_timerHead;

        while (p_tmpPtr != NULL)
        {
            if (p_tmpPtr->expireTime > 0)
            {
                /*
                   Decrement the current timer's expireTime
                 */
                p_tmpPtr->expireTime--;

                /*
                   Check if timer has timed out
                 */
                if (p_tmpPtr->expireTime == 0)
                {
                    /*
                       Notify the Event Processor that at least one timer has expired.
                     */
                    tbm_setTimerExpiredFlag();
                }
            }
            /*
               Get the next timer
             */
//         p_tmpPrevPtr = p_tmpPtr;
            p_tmpPtr = p_tmpPtr->p_next;
        }
    }

    return;
}                               /* end tbm_updateTimers */

/********************************************************************

FUNCTION:       tbm_processExpiredTimers

DESCRIPTION:
  This function is called from the Event Processor when it
  receives a Flag (set by tbm_updateTimers).  It evaluates
  all of the active timers on the list and if they have expired, it will
  call the associated function.  If the expired timer has a reloadTime
  associated with it, the expire time will be reset to the reloadTime.
  If, however, there an expired timer has a zero valued reloadTime, then
  the timer will be removed from the timerList.

INPUT:
  none

OUTPUT:
  none

********************************************************************/
void tbm_processExpiredTimers(void)
{
    tbt_timerType *p_tmpPtr;
    tbt_timerType *p_tmpPrevPtr;
    tbt_timerType *p_tmpFreePtr;

    /*
       Disable Interrupt
     */
    tbm_PRDIntDisable();

    /*
       Start at head of list
     */
    p_tmpPtr     = tbv_p_timerHead;
    p_tmpPrevPtr = tbv_p_timerHead;

    while (p_tmpPtr != NULL)
    {
        /*
           Check if timer has timed out
         */
        if (p_tmpPtr->expireTime == 0)
        {
            /*
               Executed timer function
             */
            (*(p_tmpPtr->p_timerFunction))();

            /*
               Check if timer is a periodic timer
             */
            if (p_tmpPtr->reloadTime != 0)
            {
                /*
                   Restart timer
                 */
                p_tmpPtr->expireTime = p_tmpPtr->reloadTime;

                /*
                   Get the next timer
                 */
                p_tmpPrevPtr         = p_tmpPtr;
                p_tmpPtr             = p_tmpPtr->p_next;
            }
            else
            {
                /*
                   Remove timer from list
                 */

                /*
                   Keep pointer to timer to be freed
                 */
                p_tmpFreePtr = p_tmpPtr;

                /*
                   Check if at beginning of scheduled timer list
                 */

                if (p_tmpPtr == tbv_p_timerHead)
                {
                    /*
                       make new head if this timer is current head
                     */
                    tbv_p_timerHead = tbv_p_timerHead->p_next;
                    /*
                       Update current and previous pointers
                     */
                    p_tmpPtr        = tbv_p_timerHead;
                    p_tmpPrevPtr    = tbv_p_timerHead;
                }
                else
                {
                    /*
                       Keep previous the same and
                     */
                    /*
                       update current to current's next
                     */
                    p_tmpPtr             = p_tmpPtr->p_next;
                    p_tmpPrevPtr->p_next = p_tmpPtr;
                }

                /*
                   add free timer to free list
                 */

                /*
                   clear out timer
                 */
                p_tmpFreePtr->timerID         = tbc_nullTimer;
                p_tmpFreePtr->p_timerFunction = &tbm_nullTimer;

                // Fixed bug. JAB 1/16/04
                if (p_tmpPtr != NULL) {
                    p_tmpPtr->expireTime = 0;
                    p_tmpPtr->reloadTime = 0;
                }

                /*
                   Make the old head of the free list this guy's next
                 */
                p_tmpFreePtr->p_next = tbv_p_freeTimers;

                /*
                   crown the new head of the list
                 */
                tbv_p_freeTimers     = p_tmpFreePtr;

                tbv_timerCounter--;
            }
        }
        else
        {
            /*
               Get the next timer
             */
            p_tmpPrevPtr = p_tmpPtr;
            p_tmpPtr     = p_tmpPtr->p_next;
        }
    }
    tbm_clearTimerExpiredFlag();

    /*
       Enable Interrupt
     */
    tbm_PRDIntEnable();

    return;
}                               /* end tbm_processExpiredTimers */

/********************************************************************

FUNCTION:       tbm_addTimer

DESCRIPTION:
  This function adds a new timer to the timerList.  All added timers are
  based off the Nucleus timer tbv_TelemBTimer which provides a 20 ms tick.

INPUT:
  p_timerFunction : A pointer to the function to be called when the
                    timer expires
  timerID : the identifier of the timer
  expiretime : The timer before the first expiration of this timer.
               Time is in units of 20ms increments, for example if a
               timer should expire in 100 ms, then the expireTime should
               be 100ms/20ms = 5.
  reloadTime : Zero if the timer should expire once and then be automaticaly
               removed.
               Non-Zero if the timer is periodic. In this case each time
               the timer expires, it's expireTime will be reset to the
               value in the reloadTime.  To remove the timer tbm_cancelTimer
               must be used.

OUTPUT:
  none

********************************************************************/
void tbm_addTimer(timerPtrType p_timerFunction,
                  tbt_timerID timerID, UINT16 expireTime, UINT16 reloadTime)
{
    tbt_timerType *p_tmpPtr;

    /*
       Disable Interrupts
     */
    tbm_PRDIntDisable();

    /*
     * obtain an available timer
     */
    if (tbv_p_freeTimers != NULL)
    {
        /*
           Grab new timer
         */
        p_tmpPtr                  = tbv_p_freeTimers;

        /*
           Create new head of free list
         */
        tbv_p_freeTimers          = p_tmpPtr->p_next;

        /*
         * Initialize New Entry
         */
        p_tmpPtr->expireTime      = expireTime;
        p_tmpPtr->reloadTime      = reloadTime;
        p_tmpPtr->timerID         = timerID;
        p_tmpPtr->p_timerFunction = p_timerFunction;

        /*
         * Put new guy on active list
         */

        /*
           Make new guy point ahead to current head
         */
        p_tmpPtr->p_next = tbv_p_timerHead;

        /*
           Make new guy the head of the active list
         */
        tbv_p_timerHead  = p_tmpPtr;

        /*
         * update timer counter statistics
         */
        tbv_timerCounter++;
        if (tbv_timerCounter > tbv_timerHighMark)
            tbv_timerHighMark = tbv_timerCounter;

    }
    else
    {
        /*
           No free timers
         */
        /*
           SYSTEM ERROR
         */
        bsm_EHLock("tbm_addTimer: no free timers.");
    }

    /*
       Enable Interrupts
     */
    tbm_PRDIntEnable();

}                               /* end tbm_addTimer */

/********************************************************************

FUNCTION:       tbm_reloadTimer

DESCRIPTION:
  If a timer was set up to expire periodically, then it can also be
  reloaded.  The process of reloading a timer resets it's expire time with
  the value in its reload time.  This is used if one wants a timer which
  will expire if a particular thing doesn't happen, but if that particular
  thing does happen then the timer can be restarted.

  This function searches for the first occurance of the desired timer and restarts it
  by setting the expire time equal to the reload time.  By design there is only one
  timer of a type active at any point.

INPUT DATA:
  timerID:  the ID of the timer to be reloaded.

OUTPUT RESULTS:
  none

********************************************************************/
void tbm_reloadTimer(tbt_timerID timerID)
{

    tbt_timerType *p_tmpPtr;

    /*
       Disable Interrupts
     */
    tbm_PRDIntDisable();

    /*
       Start at the beginning
     */
    p_tmpPtr = tbv_p_timerHead;

    /*
       Go through the list until the first matching timer is found.
     */
    while (p_tmpPtr != NULL)
    {
        /*
           Looking for the desired timer
         */
        if (p_tmpPtr->timerID == timerID)
        {
            /*
               Retriggering only if it is a periodic timer
             */
            if (p_tmpPtr->reloadTime != 0)
                p_tmpPtr->expireTime = p_tmpPtr->reloadTime;

            /*
               And then getting out.
             */
            break;
        }

        /*
           Or getting the next timer
         */
        p_tmpPtr = p_tmpPtr->p_next;
    }

    /*
       Enable Interrupts
     */
    tbm_PRDIntEnable();
}                               /* end tbm_reloadTimer */

/********************************************************************

FUNCTION:       tbm_reloadAllTimers

DESCRIPTION:
  This is a service routine for re-initialization of the timerList.
  It resets the expireTime to the reloadTime for each timer with a
  non-zero reloadTime value.

INPUT:
  none

OUTPUT:
  none

********************************************************************/
void tbm_reloadAllTimers(void)
{
    tbt_timerType *p_tmpPtr;

    /*
       Disable Interrupts
     */
    tbm_PRDIntDisable();

    /*
       Start at the beginning
     */
    p_tmpPtr = tbv_p_timerHead;

    /*
       Go through the list and reload all timers
     */
    while (p_tmpPtr != NULL)
    {
        /*
           Reload only if it is a periodic timer
         */
        if (p_tmpPtr->reloadTime != 0)
            p_tmpPtr->expireTime = p_tmpPtr->reloadTime;

        /*
           Get the next timer
         */
        p_tmpPtr = p_tmpPtr->p_next;
    }

    /*
       Enable Interrupts
     */
    tbm_PRDIntEnable();
}                               /* end tbm_reloadAllTimers */

/********************************************************************

FUNCTION:
  tbm_nullTimer

DESCRIPTION:
  Does nothing.  Provides the a default destination address for unused
  timers.

INPUT:
  none

OUTPUT:
  none

********************************************************************/
void tbm_nullTimer(void)
{
    return;
}

/********************************************************************

FUNCTION: tbm_hsTimerExp()

DESCRIPTION:
    This function is called when the handshake timer expires.  A
    global flag gets set which informs the instrument that a downlink
    is due to be sent.  Normally a handshake ... or an ACK if there is
    some unacknowledged uplink data frames.

ARGS:
    <none>

RETURNS:
    <none>

NOTES:
    <none>

REQUIREMENTS:
    <none>

********************************************************************/
void tbm_hsTimerExp(void)
{
    /* Count the number of 20 mS ticks */
    /* Handshake need to be sent at least every 250mS */
    /* 12 * 20mS = 240mS */
    if (handshakeTickCounter20mS < 12) {
        handshakeTickCounter20mS++;
    }
    else if (handshakeTickCounter20mS == 12)
    {
#ifdef DEBUG_STATE
        ++stateIndex;
        stateIndex       &= STATE_MASK;
        state[stateIndex] = tbt_HStimerExpire;
#endif
        ++handshakeTickCounter20mS;
        timeToHandshake   = TRUE;
    }
    else {
        //do nothing; timer disabled.
        asm ("	nop");
    }

    return;
} /* tbm_hsTimerExp() */

/********************************************************************
FUNCTION: tbm_hsTimerExp()

DESCRIPTION:
    This function is called to disable the handshake timer.

ARGS:
    <none>

RETURNS:
    <none>
********************************************************************/
void tbm_hsDisable (void) {
    handshakeTickCounter20mS = 13;
    timeToHandshake          = FALSE;
}
