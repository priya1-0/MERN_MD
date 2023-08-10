/* type.h
 *
 * Copyright (c) 2000 Texas Instruments Incorporated
 *
 *  Originally created by DNA Software,
 *  Modified by Russ Heeschen for the FlashBurn
 *  project.
 */

/*
 * $Log$
 * Revision 1.2  2004/03/15 13:15:05  demlr1
 * SCR# 82009
 * Removed some lines.
 *
 * Revision 1.2  2004/03/05 19:57:42  robert.deml
 * no message
 *
 * Revision 1.1.1.1  2004/03/03 20:38:34  robert.deml
 * no message
 *
 * Revision 1.1.1.1  2004/02/04 18:04:55  robert.deml
 * no message
 *
 * Revision 1.1.1.1  2003/11/20 18:05:37  robert.deml
 * no message
 *
 * Revision 1.2  2001/04/19 16:29:03  heeschen
 * v00.30 Snapshot
 * Saving this stuff after massive redesign to remove RTDX dependency.
 * Next step is to clean up, fix comments, and do unit testing.
 *
 * Revision 1.1  2001/02/14 17:13:52  heeschen
 * v00.11 Beta
 * Capturing this new FBTC55 module. Successfully
 * reads/writes flash memory. Untested for bootability
 * of written program.
 *
 * Revision 1.2  2000/12/07 19:57:25  heeschen
 * v0.00002 of the FBTC54 program.
 * Changes made as a result of code review 12/05/00.
 * Doc. CR_12_05_00.doc is the minutes of the review.
 * Biggest change was to the RTDX comm. method, and
 * changing several macros into functions.
 *
 */

#if !defined( TYPE__H )
#define       TYPE__H

#if 0
typedef enum 
{
   FALSE = 0,
   TRUE  = !FALSE
} BOOL;
#endif

typedef float f32;

typedef long s32;
typedef unsigned long u32;

typedef short s16;
typedef unsigned short u16;

typedef signed char s8;
typedef unsigned char u8;

#endif

