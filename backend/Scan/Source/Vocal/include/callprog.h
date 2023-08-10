
/* ************************************************************************* */
/*
 *	callprog.h
 *
 *	(C) 1993 - 2006 VOCAL Technologies, Ltd.
 *
 *	ALL RIGHTS RESERVED.  PROPRIETARY AND CONFIDENTIAL.
 *
 *	VOCAL Technologies, Ltd.
 *	90A John Muir Drive.
 *	Buffalo, NY  14228
 *
 *	Product:	MODEM 101
 *
 *	Module:		CALL PROGRESS
 *
 *	This file contains the definitions of the call progress symbols.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 19:50:34  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _INCLUDE_CALLPROG_H
#define _INCLUDE_CALLPROG_H

/* ************************************************************************* */

/*
 *	call progress tone detector bits and flags
 */
#define CP_TONES__V8BIS_1375						0x0001
#define CP_TONES__V8BIS_2002						0x0002
#define CP_TONES__V22_2250							0x0004	/* Not specially required */
#define CP_TONES__CNG_1100							0x0008
#define CP_TONES__ANS_2100							0x0010
#define CP_TONES__V32_600							0x0020	/* Not specially required */
#define CP_TONES__V32_3000							0x0040

#define CP_TONES__SILENCE							0x4000
#define CP_TONES__CALL_PROGRESS						0x8000

#define CP_TONES__SILENCE__BIT						14
#define CP_TONES__CALL_PROGRESS__BIT				15

/* ************************************************************************* */
/*
 *	Definition of detector types defined within this file.
 *
 *	These types are also those used to indicate to the upper
 *	level software the presence of a particular detection.
 */
#define CP_ENTRY_SIZE 2
#define CP_TABLE_ENTRY_SIZE 4

#define CP_TABLE_ENTRY_NUM 16

#define CP_STATUS__INITIAL_DIALTONE					0x0001
#define CP_STATUS__SECOND_DIALTONE					0x0002
#define CP_STATUS__OTHER_DIALTONE					0x0004
#define CP_STATUS__BROKEN_DIALTONE					0x0008
#define CP_STATUS_GROUP__DIALTONE					0x000f

#define CP_STATUS__SHORT_BUSY						0x0010
#define CP_STATUS__MEDIUM_BUSY						0x0020
#define CP_STATUS__LONG_BUSY						0x0040
#define CP_STATUS__BROAD_BUSY						0x0080
#define CP_STATUS__OTHER_BUSY						0x0100
#define CP_STATUS_GROUP__BUSY						0x01f0

#define CP_STATUS__US_RRING							0x0200
#define CP_STATUS__UK_RRING							0x0400
#define CP_STATUS__SHORT_RRING						0x0800
#define CP_STATUS__OTHER_RRING						0x1000
#define CP_STATUS_GROUP__RRING						0x1e00

#define CP_STATUS__RRING_SILENCE					0x2000
#define CP_STATUS__602_SILENCE						0x4000
#define CP_STATUS_GROUP__SILENCE					0x6000

#define CP_STATUS__CNG								0x8000

/* ************************************************************************* */
/*
 *	Definition of disconnect detector types defined within this file.
 *
 *	These types are also those used to indicate to the upper
 *	level software the presence of a particular detection.
 */

#define DT_TABLE_ENTRY_NUM 3

#define DT_STATUS__DISCONNECT_TONE_1				0x0001
#define DT_STATUS__DISCONNECT_TONE_2				0x0002
#define DT_STATUS__DISCONNECT_TONE_3				0x0004
#define DT_STATUS_GROUP__DISCONNECT_TONE			0x0007

/* ************************************************************************* */

#endif /* _INCLUDE_CALLPROG_H */
