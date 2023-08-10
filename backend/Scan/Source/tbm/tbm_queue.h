/* Copyright (c) 1997 by Medtronic Inc.  All Rights Reserved */
/********************************************************************
DOCUMENT

$Revision$
$Date$
$RCSfile$

NAME:
  tbm_queue.h

PURPOSE:
  This include file contains the external declarations of queue
  management functions.

ENDDOCUMENT
********************************************************************/

#ifndef tbm_queue_h
#define tbm_queue_h

#include "..\types.h"
#include "tbt_queue.h"

/***************************************************
  Updates the queue's header to indicate that the queue
  is empty. This function should only be used by the
  writer of a queue, i.e. the caller of
  tbm_EnqueueEntry for the same queue.
****************************************************
*/
void tbm_clearQueue(tbt_queuePointer queuePointer);

/***************************************************
  Removes all entries from the queue.  This function
  should only be used by the reader of a queue, i.e.
  the caller of tbm_getQueueEntry and
  tbm_dequeueEntry for the same queue.
****************************************************
*/
void tbm_dequeueAllEntries(tbt_queuePointer queuePointer);

/***************************************************
  Removes the first entry from the queue.
****************************************************
*/
void tbm_dequeueEntry(tbt_queuePointer queuePointer);

/***************************************************
  Adds an entry to the queue if the queue isn't full.
****************************************************
*/
void tbm_enqueueEntry(tbt_queuePointer queuePointer, void *entryPointer);

/***************************************************
  Returns a pointer to the first entry in the queue (the
  entry to be read).  If the queue is empty, NULL is
  returned.
****************************************************
*/
void *tbm_getQueueEntry(tbt_queuePointer queuePointer);

/***************************************************
  Initializes the header for a queue.
****************************************************
*/
void tbm_initializeQueue(UINT16           queueSize,
                         tbt_queuePointer queuePointer);

#endif /* tbm_queue_h */
