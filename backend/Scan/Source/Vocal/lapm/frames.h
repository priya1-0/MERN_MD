
/* ************************************************************************* */
/*
 *	frames.h
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
 *	Module:		LAPM
 *
 *	This file contains the declarations for LAPM transmit and receive frames.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 19:57:12  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _LAPM_FRAMES_H
#define _LAPM_FRAMES_H

#include "lapm/config.h"

/* ************************************************************************* */

typedef struct {
	uint8	line_status;
	uint8	packet_status;
	uint16	packet_length;
} lapm_frame_status_t;

#define LAPM_FRAME_STATUS  lapm_frame_status.line_status
#define LAPM_PACKET_STATUS lapm_frame_status.packet_status
#define LAPM_PACKET_LENGTH lapm_frame_status.packet_length

/* ************************************************************************* */
/*
 * lapm packet structures
 *
 */

typedef struct {
	expand8	cmd;
	expand8 cmd_nr;
	expand8 vs;
	expand8 vr;
	expand8 status;
} frmr_t;

/* ************************************************************************* */

typedef struct {
	expand8 addr;
	expand8 cmd_ns;
	expand8 cmd_nr;
	expand8 info [CMD_I_INFO_MAX];
} lapm_I_packet_t;

typedef struct {
	expand8 addr;
	expand8 cmd;
	expand8 cmd_nr;
} lapm_S_packet_t;

typedef struct {
	expand8 addr;
	expand8 cmd;
	expand8 info [1];
} lapm_U_packet_t;

typedef struct {
	expand8 addr;
	expand8 cmd;
	expand8 UI_cmd;
	expand8 UI_type;
	expand8 UI_length;
} lapm_UI_packet_t;

typedef struct {			/* this is created for the sizeof the response */
	expand8 addr;
	expand8 cmd;
	expand8 UI_cmd;
} lapm_UI_rsp_packet_t;

typedef struct {
	expand8 addr;
	expand8 cmd;
	expand8 info [CMD_U_XID_MAX];
} lapm_XID_packet_t;

typedef struct {
	expand8 addr;
	expand8 cmd;
	expand8 info [CMD_U_TEST_MAX];
} lapm_TEST_packet_t;

typedef struct {
	expand8 addr;
	expand8 cmd;
	frmr_t frmr;
} lapm_FRMR_packet_t;

typedef struct {
	expand8 addr;
	expand8 cmd;
	expand8 cmd2;
} lapm_every_packet_t;

/* ************************************************************************* */
/*
 * lapm frame structures (for allocation reasons)
 *
 */

typedef struct lapm_break_frame_s {
	struct lapm_break_frame_s *next;
	lapm_frame_status_t lapm_frame_status;
	union {
		lapm_UI_packet_t UI_packet;
	} packet;
} lapm_break_frame_t;

typedef struct lapm_xid_frame_s {
	struct lapm_xid_frame_s *next;
	lapm_frame_status_t lapm_frame_status;
	union {
		lapm_XID_packet_t XID_packet;
	} packet;
} lapm_xid_frame_t;

typedef struct lapm_test_frame_s {
	struct lapm_test_frame_s *next;
	lapm_frame_status_t lapm_frame_status;
	union {
		lapm_TEST_packet_t TEST_packet;
	} packet;
} lapm_test_frame_t;

/* ************************************************************************* */

typedef struct lapm_tx_frame_s {
	struct lapm_tx_frame_s *next;
	lapm_frame_status_t lapm_frame_status;
	union {
		lapm_every_packet_t  every_packet;
		lapm_I_packet_t      I_packet;
		lapm_S_packet_t      S_packet;
		lapm_U_packet_t      U_packet;
		lapm_UI_packet_t     UI_packet;
		lapm_XID_packet_t    XID_packet;
		lapm_FRMR_packet_t   FRMR_packet;
		lapm_TEST_packet_t   TEST_packet;
	} packet;
} lapm_tx_frame_t;

typedef struct lapm_rx_frame_s {
	struct lapm_rx_frame_s *next;
	lapm_frame_status_t lapm_frame_status;
	union {
		lapm_every_packet_t  every_packet;
		lapm_I_packet_t      I_packet;
		lapm_S_packet_t      S_packet;
		lapm_U_packet_t      U_packet;
		lapm_UI_packet_t     UI_packet;
		lapm_XID_packet_t    XID_packet;
		lapm_FRMR_packet_t   FRMR_packet;
		lapm_TEST_packet_t   TEST_packet;
	} packet;
	expand8 crc [2];
} lapm_rx_frame_t;

/*
 * these are the frames that are allocated from the control queue
 *
 * other frames (XID/FRMR/UI/TEST) are placed on the lapm_control_list
 *
 */

typedef struct lapm_ctl_frame_s {
	struct lapm_ctl_frame_s *next;
	lapm_frame_status_t lapm_frame_status;
	union {
		lapm_every_packet_t  every_packet;
		lapm_S_packet_t      S_packet;
		lapm_U_packet_t      U_packet;
		lapm_UI_packet_t     UI_packet;
		lapm_FRMR_packet_t   FRMR_packet;
	} packet;
} lapm_ctl_frame_t;

/* ************************************************************************* */

#endif /* LAPM_FRAMES_H */
