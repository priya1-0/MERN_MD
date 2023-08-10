/* Copyright (c) 1997 by Medtronic Inc.  All Rights Reserved */
/********************************************************************
DOCUMENT

$Revision$

$Date$

$RCSfile$

MODULE:
  tbm_queue.c

FUNCTIONS:
  tbm_clearQueue
  tbm_dequeueAllEntries
  tbm_dequeueEntry
  tbm_enqueueEntry
  tbm_getQueueEntry
  tbm_initializeQueue

DESCRIPTION:
  This module contains functions that manage a queue.  For
  purposes of this module a queue is a first in, first out
  (FIFO) storage structure capable of holding fixed sized
  entries. The maximum number of entries is specified when
  the queue is initialized.

  Functions are provided to initialize a queue
  (tbm_initializeQueue), clear (reset, purge, empty) a
  queue (tbm_clearQueue), add an entry to a queue
  (tbm_enqueueEntry), access the first entry in a queue
  tbm_getQueueEntry), and remove the first entry from
  a queue tbm_DequeueEntry).

  A queue is represented by a structure consisting of a
  "header" field of type tbt_queueHeader, followed by an
  "entries" field which is an array of pointers which
  point to whatever type of entries the queue is to hold.

ENDDOCUMENT
********************************************************************/
/*
Includes
*/
#include <string.h>
#include "tbm_queue.h"
#include "link.h"
#include "tbm_channel.h"
#include "../bsm/bsm_Event.h"

/********************************************************************

FUNCTION:
  tbm_clearQueue

DESCRIPTION:
  Updates the queue's header to indicate that the queue
  is empty. This function should only be used by the
  writer of a queue, i.e. the caller of
  tbm_EnqueueEntry for the same queue.

INPUT:
  queuePointer - points to the queue.

OUTPUT:
  none

********************************************************************/
void tbm_clearQueue(tbt_queuePointer queuePointer)
{
    tbt_queueHeader *qp;

    qp              = (tbt_queueHeader *) queuePointer;

    qp->writeOffset = qp->readOffset;

    return;
}                               /* tbm_clearQueue */

/********************************************************************

FUNCTION:
  tbm_dequeueAllEntries

DESCRIPTION:
  Removes all entries from the queue.  This function
  should only be used by the reader of a queue, i.e.
  the caller of tbm_getQueueEntry and
  tbm_dequeueEntry for the same queue.

INPUT:
  queuePointer - points to the queue.

OUTPUT:
  none

********************************************************************/
void tbm_dequeueAllEntries(tbt_queuePointer queuePointer)
{
    tbt_queueHeader *qp;

    qp             = (tbt_queueHeader *) queuePointer;

    qp->readOffset = qp->writeOffset;

    return;
}                               /* tbm_DequeueAllEntries */

/********************************************************************

FUNCTION:
  tbm_dequeueEntry

DESCRIPTION:
  Removes the first entry from the queue.

  1. If the readOffset equals the writeOffset, the queue
     is empty so do nothing.
  2. Increment readOffset.  If the result equals the
     queueSize, set the readOffset to zero. Update the
     queue's readOffset.

INPUT:
  queuePointer - points to the queue.

OUTPUT:
  none

********************************************************************/
void tbm_dequeueEntry(tbt_queuePointer queuePointer)
{
    tbt_queueHeader *qp;
    USHORT          readOffset;

    qp         = (tbt_queueHeader *) queuePointer;

    readOffset = qp->readOffset;

    if (readOffset != qp->writeOffset)
    {
        readOffset++;
        if (readOffset >= qp->queueSize)
        {
            readOffset = 0;
        }
        qp->readOffset = readOffset;
    }

    return;
}                               /* tbm_dequeueEntry */

/********************************************************************

FUNCTION:
  tbm_enqueueEntry

DESCRIPTION:
  Adds an entry to the queue if the queue isn't full or if the queue
  was initialized with the tbt_enqueueClearIfFull option.

 1.  Compute nextWriteOffset by incrementing writeOffset.
     If the result equals the queue_size, set
     nextWriteOffset to zero.
 2.  If nextWriteOffset equals the readOffset, the queue
    is full.  Return FALSE.
 3.  Copy the specified entry to the queue at the
     writeOffset.
 4.  Set the writeOffset to nextWriteOffset.
 5.  Return TRUE.

INPUT:
  queuePointer  - points to the queue
  entryPointer  - points to the entry
                  to be added to the queue

OUTPUT:
  none

********************************************************************/
void tbm_enqueueEntry(tbt_queuePointer queuePointer, void *entryPointer)
{
    USHORT           nextWriteOffset;
    tbt_genericQueue *qp;
    USHORT           readOffset;
    USHORT           writeOffset;

    /*
     * Copy pointers into a local values
     */
    qp              = (tbt_genericQueue *) queuePointer;

    readOffset      = qp->header.readOffset;
    writeOffset     = qp->header.writeOffset;

    /*
       Handle the wrap around for the queue pointers.
     */
    nextWriteOffset = writeOffset + 1;
    if (nextWriteOffset >= qp->header.queueSize)
    {
        nextWriteOffset = 0;
    }

    if (nextWriteOffset == readOffset)
    {
        bsm_EHLock("tbm_enqueueEntry: queue full");
    }
    else
    {
        /*
         * Copy pointer to writeOffset in queue
         */
        qp->entries[writeOffset] = (void *)entryPointer;

        qp->header.writeOffset   = nextWriteOffset;
    }

    return;
}                               /* tbm_enqueueEntry */

/********************************************************************

FUNCTION:
  tbm_getQueueEntry

DESCRIPTION:
  Returns a pointer to the first entry in the queue (the
  entry to be read).  If the queue is empty, NULL is
  returned.

  NOTE that tbm_dequeueEntry must be called to remove
  the entry from the queue.

  1.  If the readOffset and writeOffset are equal, the
      queue is empty so return NULL.
  2.  Construct a pointer to the entry at the readOffset
      and return it.

INPUT DATA:
  queuePointer  - points to the queue

OUTPUT RESULTS:
  Pointer to the first entry in the queue or NULL if the queue is empty.

********************************************************************/
void *tbm_getQueueEntry(tbt_queuePointer queuePointer)
{
    tbt_genericQueue *qp;
    USHORT           readOffset;
    void             *returnVal;

    qp         = (tbt_genericQueue *) queuePointer;

    readOffset = qp->header.readOffset;

    if (readOffset == qp->header.writeOffset)
        returnVal = NULL;
    else
        returnVal = qp->entries[readOffset];

    return (returnVal);
}                               /* tbm_getQueueEntry */

/********************************************************************

FUNCTION:
  tbm_initializeQueue

DESCRIPTION:
  Initializes the header for a queue.

  The queue is initially empty (cleared).

  1. Set the queue's queueSize from the specified value.
  2. Set the readOffset and writeOffset to zero.

  NOTE:
  The actual size of a queue is 1 less than the queue
  size designated by the parameter queueSize.  This extra
  position is used to determine the status of the queue
  full or empty).

INPUT:
  queueSize     - the size of all entries in the queue
  queuePointer  - points to the queue

OUTPUT:
  None.

********************************************************************/
void tbm_initializeQueue(UINT16 queueSize, tbt_queuePointer queuePointer)
{
    tbt_queueHeader *qp;

    qp              = (tbt_queueHeader *) queuePointer;

    qp->queueSize   = queueSize;
    qp->readOffset  = 0;
    qp->writeOffset = 0;

    return;
}                               /* tbm_initializeQueue */
