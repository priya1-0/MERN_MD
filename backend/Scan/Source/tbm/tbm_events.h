/* Copyright (c) 2001 by Medtronic Inc.  All Rights Reserved */
/********************************************************************
DOCUMENT

$Revision$

$Date$

$RCSfile$

NAME:    tbm_events.h

PURPOSE: Event handler for the Telemetry Channel.

ENDDOCUMENT
*************************************************************************/

#ifndef tbm_events_h
#define tbm_events_h

#ifdef DEFINED_HERE
        #define SCOPE
#else
        #define SCOPE extern
#endif

#include "../types.h"
#include "tbm_fsm.h"

/*
 * Maximum number of events supported
 */
#define tbc_MaxEvents 10

// Global Data
SCOPE BOOL tbv_moreEventsFlag;
SCOPE BOOL tbv_timerExpiredFlag;

typedef void (*eventPtrType) (struct tbm_Chan *);

typedef struct tbt_Event
{
    eventPtrType eventPtr;
    struct tbt_Event *p_next;
}
tbt_Event;

/*
 * external event functions prototypes
 */
SCOPE void tbm_eventProcessor(void);
SCOPE eventPtrType tbm_getEvent(void);
SCOPE void tbm_initializeEvents(void);
SCOPE void tbm_postEvent(eventPtrType fsmPtr);
SCOPE void tbm_clearMoreEventsFlag(void);
SCOPE void tbm_setTimerExpiredFlag(void);
SCOPE void tbm_clearTimerExpiredFlag(void);

#undef SCOPE

#endif /* tbm_events_h */
