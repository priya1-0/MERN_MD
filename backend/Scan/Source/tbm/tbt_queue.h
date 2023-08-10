/* Copyright (c) 1998 by Medtronic Inc.  All Rights Reserved */
/********************************************************************
DOCUMENT

$Revision$
$Date$
$RCSfile$

NAME:
  tbt_queue.h

PURPOSE:
  This include file contains an number of type definitions used
  by the queue manager.

ENDDOCUMENT
********************************************************************/

#ifndef tbt_queue_h
#define tbt_queue_h

/****************************************************************
* DATATYPE: tbt_queueHeader
*
* DESCRIPTION/USE:
*    Defines the layout of a "standard" queue header.
*
* VALUES:
*    queueSize     - the size of all entries in the queue
*                    (maximum number of queue entries)
*    readOffset    - the offset of the next entry that can be
*                    read from the queue
*    writeOffset   - the offset of the next entry that can be
*                    written to the queue
*
* NOTES:
*    1.  The queue is empty when the readOffset and the
*        writeOffset are equal.
*    2.  The queue is full when the writeOffset is one entry
*        behind the readOffset.
*    3.  Although space is reserved for queueSize entries
*        the queue can hold at most one less than that number.
*
* STRUCTURE:
*/
typedef struct
{
    USHORT queueSize;
    USHORT readOffset;
    USHORT writeOffset;
}
tbt_queueHeader;

/*
ENDPURPOSE
****************************************************************/

/****************************************************************
* DATATYPE: tbt_genericQueue
*
* DESCRIPTION/USE:
*    Defines the layout of any queue.
*
* VALUES:
*    A queue data structure consists of a queue header
*    followed by space for the queue entries.
*
* STRUCTURE:
*/
typedef struct
{
    tbt_queueHeader header;
    void *entries[1];
}
tbt_genericQueue;

/*
ENDPURPOSE
****************************************************************/

/****************************************************************
* DATATYPE: tbt_queuePointer
*
* DESCRIPTION/USE:
*    Used to designate a pointer to any queue.
*
* VALUES:
*    Since this type is defined a void pointer no type casting
*    is required when passing a queue to a queue management
*    function.
*
* STRUCTURE:
*/
typedef void *tbt_queuePointer;

/*
ENDPURPOSE
****************************************************************/

#endif /* tbt_queue_h */
