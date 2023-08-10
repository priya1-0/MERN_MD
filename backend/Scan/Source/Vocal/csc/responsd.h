
/* ************************************************************************* */
/*
 *	responsd.h
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
 *	This file contains the public parameters definitions for
 *	the response related resources of the CSC module.
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

#ifndef _CSC_RESPONSD_H
#define _CSC_RESPONSD_H

#include "csc/config.h"

/* ************************************************************************* */

typedef struct {
	bool	_send_post_xoff;
	bool	_send_post_xon;
	uint16	_append_type;
	uint16	_state;
	uint16	_state_save;
	uint16	_value;
	uint16	_cmd_code;
	char	*_strp;
	bool	_append_arq;

	uint16	_csp_line_number;
	char	_csp_rsp_str [RESPONSE_BUFFER_SIZE];
	uint16	_csp_rsp_type;

	uint16	_csp_opcode;

	uint32	_connect_speed;
	char    _connect_modulation[6];
	bool    _connect_modulation_mask;
	char    _connect_protocol[10];
	uint16  _connect_protocol_mask;
	char    _connect_compression[9];
	char    _connect_line_speed[21];
	uint32  _connect_line_speed2;
	uint16  _connect_voice_data;
	char    _connect_message[80];
	bool    _connect;

	bool	_affected_by_quiet;
	bool	_affected_by_numeric;
	uint16	_numeric_code;
	uint16	_start_state;
} csc_response_t;

/* ************************************************************************* */

DEF_DATA(csc_response_t, csc_response)
#define CSC_RESPONSE_DATA csc_response_t csc_response
#define CSC_RESPONSE USE_DATA(csc_response)

/* ************************************************************************* */

#define rsp_send_post_xon					(CSC_RESPONSE._send_post_xon)
#define rsp_send_post_xoff					(CSC_RESPONSE._send_post_xoff)
#define rsp_append_type						(CSC_RESPONSE._append_type)
#define rsp_state							(CSC_RESPONSE._state)
#define rsp_state_save						(CSC_RESPONSE._state_save)
#define rsp_value							(CSC_RESPONSE._value)
#define rsp_cmd_code						(CSC_RESPONSE._cmd_code)
#define rsp_strp							(CSC_RESPONSE._strp)
#define rsp_append_arq						(CSC_RESPONSE._append_arq)

#define stat__csp_rsp_line_number			(CSC_RESPONSE._csp_line_number)
#define stat__csp_rsp_str					(CSC_RESPONSE._csp_rsp_str)
#define stat__csp_rsp_type					(CSC_RESPONSE._csp_rsp_type)
#define stat__csp_opcode					(CSC_RESPONSE._csp_opcode)

#define sl__connect_speed				(CSC_RESPONSE._connect_speed)
#define sl__connect_modulation			(CSC_RESPONSE._connect_modulation)
#define sl__connect_protocol  			(CSC_RESPONSE._connect_protocol)
#define sl__connect_modulation_mask		(CSC_RESPONSE._connect_modulation_mask)
#define	sl__connect_protocol_mask		(CSC_RESPONSE._connect_protocol_mask)
#define sl__connect_compression			(CSC_RESPONSE._connect_compression)
#define sl__connect_line_speed			(CSC_RESPONSE._connect_line_speed)
#define sl__connect_line_speed2			(CSC_RESPONSE._connect_line_speed2)
#define sl__connect_voice_data			(CSC_RESPONSE._connect_voice_data)
#define sl__connect						(CSC_RESPONSE._connect)
#define sl__connect_message				(CSC_RESPONSE._connect_message)

#define rsp_affected_by_quiet			(CSC_RESPONSE._affected_by_quiet)
#define rsp_affected_by_numeric			(CSC_RESPONSE._affected_by_numeric)
#define rsp_numeric_code				(CSC_RESPONSE._numeric_code)
#define rsp_start_state					(CSC_RESPONSE._start_state)

/* ************************************************************************* */

#endif /* _CSC_RESPONSD_H */
