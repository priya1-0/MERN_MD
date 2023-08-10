
/* ************************************************************************* */
/*
 *	response.h
 *
 *	(C) 1994 - 2006 VOCAL Technologies, Ltd.
 *
 *	ALL RIGHTS RESERVED.  PROPRIETARY AND CONFIDENTIAL.
 *
 *	VOCAL Technologies, Ltd.
 *	90A John Muir Drive.
 *	Buffalo, NY  14228
 *
 *	Product:	MODEM 101
 *
 *	Module:		CSC
 *
 *	This file contains definitions for the response.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 19:06:28  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _CSC_RESPONSE_H
#define _CSC_RESPONSE_H

#include "csc/responsd.h"

/* ************************************************************************* */

#define RSP_CODE__OK							0
#define RSP_CODE__CONNECT						1
#define RSP_CODE__RING							2
#define RSP_CODE__NO_CARRIER					3
#define RSP_CODE__ERROR							4
#define RSP_CODE__FAX							33
#define RSP_CODE__DATA							35

#define RSP_CODE__FCERROR						0x1000
#define RSP_CODE__INITIAL_DATA_CONNECT			0x1001
#define RSP_CODE__ONLINE_DATA_CONNECT			0x1002
#define RSP_CODE__TIES_FAIL_CONNECT				0x1003
#define RSP_CODE__INTERMEDIATE__CARRIER			0x1004
#define RSP_CODE__INTERMEDIATE__PROTOCOL		0x1005
#define RSP_CODE__INTERMEDIATE__COMPRESSION		0x1006
#define RSP_CODE__INTERMEDIATE__NETWORK			0x1007
#define RSP_CODE__DIAL_FAIL						0x1008

#define RSP_CODE__STRING						0x2000
#define RSP_CODE__STRING_END					0x2001
#define RSP_CODE__STRING_MIDDLE					0x2002
#define RSP_CODE__STRING_START					0x2003
#define RSP_CODE__BYTE_DECIMAL					0x2004
#define RSP_CODE__NOT_AVAILABLE					0xffff

#define RSP_STATE__APPEND_CR					0
#define RSP_STATE__APPEND_CR_LF					1
#define RSP_STATE__APPEND_LF					2
#define RSP_STATE__DONE							3
#define RSP_STATE__PRE_CR_LF					4
#define RSP_STATE__PRE_LF						5
#define RSP_STATE__STRING						6
#define RSP_STATE__XON							7
#define RSP_STATE__NULL							8

#define RSP_APPEND_TYPE__CR						0
#define RSP_APPEND_TYPE__CR_LF					1
#define RSP_APPEND_TYPE__NONE					2

/* ************************************************************************* */

/*- MKHEADER Begin -*/

/* Global Routines: */

/* response.c */
bool response_start (uint16 rsp_code);
uint16 response_get_du (void);

/*- MKHEADER End -*/


/* ************************************************************************* */

#endif /* _CSC_RESPONSE_H */
