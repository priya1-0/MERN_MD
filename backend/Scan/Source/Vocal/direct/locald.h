
/* ************************************************************************* */
/*
 *	locald.h
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
 *	Module:		DIRECT
 *
 *	This file contains the private parameter declarations/definitions
 *	for the DIRECT module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 19:43:48  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _DIRECT_LOCALD_H
#define _DIRECT_LOCALD_H

/* ************************************************************************* */

typedef struct {
	uint8	_status;
	uint8	_state;
	bool	_disconnect_request;
	uint8	_line_type;
	uint8	_compression_used;
	uint8	_stop_mode;
	bool	_tx_within_hdlc;
	uint16	_tx_lsd_duration;
} direct_local_t;

/* ************************************************************************* */

#define DIRECT_LOCAL_DATA direct_local_t direct_local
DEF_DATA(direct_local_t, direct_local)
#define DIRECT_LOCAL USE_DATA(direct_local)

/* ************************************************************************* */

#define dp_direct_status					(DIRECT_LOCAL._status)
#define direct_state						(DIRECT_LOCAL._state)
#define direct_disconnect_request			(DIRECT_LOCAL._disconnect_request)
#define direct_line_type				 	(DIRECT_LOCAL._line_type)
#define direct_compression_used		 		(DIRECT_LOCAL._compression_used)
#define direct_stop_mode					(DIRECT_LOCAL._stop_mode)
#define direct_tx_within_hdlc				(DIRECT_LOCAL._tx_within_hdlc)
#define direct_tx_lsd_duration				(DIRECT_LOCAL._tx_lsd_duration)

/* ************************************************************************* */

#endif /* DIRECT_LOCALD_H */
