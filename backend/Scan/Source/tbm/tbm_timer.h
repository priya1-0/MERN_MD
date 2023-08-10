/* Copyright (c) 1997 by Medtronic Inc.  All Rights Reserved */
/********************************************************************
DOCUMENT

$Revision$
$Date$
$RCSfile$

ENDDOCUMENT
********************************************************************/

/********************************************************************
DOCUMENT

NAME:    tbm_timer.h

PURPOSE: This include file contains an number of defines and function
         prototypes used by the timer manager.

ENDDOCUMENT
********************************************************************/

#ifndef _tbm_timer_h
#define _tbm_timer_h

#ifdef DEFINED_HERE
        #define SCOPE
#else
        #define SCOPE extern
#endif

/*
 * timer function pointer
 * Design constraints for *timerPtrType functions.
 *  1.  They shall not call any timer operation.
 *  2.  They must be as short and as quick as a
 *      typical ISR routine.
 */
typedef void (*timerPtrType) (void);

typedef enum tbt_timerID
{
    tbc_nullTimer = 0x0000,
    reserved1     = 0x4000,
    tbc_RxTimer   = 0x4001,
    tbc_TxTimer   = 0x4002,
    tbc_HSTimer   = 0x4003,
    tbc_STOTimer  = 0x4004,
    tbc_ledTimer  = 0x4005,
    tbc_EGMTimer  = 0x4006,
    reserved7     = 0x4007,
    maxTimerID    = 0x4007
}
tbt_timerID;

/*
 * Pending timers linked list structures
 */
typedef struct tbt_timerType
{
    UINT16 expireTime;
    UINT16 reloadTime;
    timerPtrType p_timerFunction;
    tbt_timerID timerID;
    struct tbt_timerType *p_next;
}
tbt_timerType;

/* Defines for timers   */

/*
 * Maximum number of timers
 */
#define tbc_MaxTimers 8


// Global Data
SCOPE BOOL  timeToHandshake;
SCOPE UINT8 handshakeTickCounter20mS;

/*
 * external timer functions prototypes
 */
SCOPE void tbm_cancelTimer(tbt_timerID timerID);
SCOPE void tbm_initTimers(void);
SCOPE void tbm_addTimer(timerPtrType p_timerFunction,
                        tbt_timerID timerID,
                        UINT16 expireTime, UINT16 reloadTime);
SCOPE void tbm_reloadTimer(tbt_timerID timerID);
SCOPE void tbm_updateTimers(void);
SCOPE void tbm_processExpiredTimers(void);
SCOPE void tbm_reloadAllTimers(void);
SCOPE void tbm_hsTimerExp (void);
SCOPE void tbm_hsDisable (void);

#undef SCOPE

#endif /* _timers_h */
