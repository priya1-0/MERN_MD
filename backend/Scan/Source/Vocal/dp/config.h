
/* ************************************************************************* */
/*
 *	config.h
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
 *	Module:		DP
 *
 *	This file contains the public parameter declarations/definitions for
 *	the DP module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 18:25:54  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _DP_CONFIG_H
#define _DP_CONFIG_H

/* ************************************************************************* */

typedef struct {
	uint8	line_type;
	uint16	compression_used;
	uint8	error_count;
	uint16	current_block_size;
	uint16	protocol;
} system_dp_t;

typedef struct dpf_s {
	uint8	(*f_install) (void);
	uint8	(*f_remove) (void);
	uint8	(*f_start) (void);
	uint8	(*f_idle) (void);
	uint8	(*f_unidle) (void);
	uint8	(*f_suspend) (void);
	uint8	(*f_unsuspend) (void);
	uint8	(*f_stop) (expand8 user_disconnect_reason);
	uint8	(*f_halt) (void);
	uint8	(*f_reason) (void);
	uint8	(*f_reconfigure) (void);
	void	(*f_info) (void);
	uint8	(*f_sinfo) (void);
	void	(*f_timer) (void);
	void	(*f_tbrk) (uint8 break_length);
	uint16	(*f_test) (uint8 tst_len, uint8 *tst_str);
	uint16	(*f_test_status) (void);
	uint8	(*f_bg) (void);
} dpf_t;

typedef enum _dp_start_state_e{
	DP_START_STATE_ZERO = 0,
    DP_START_INITIAL_DELAY,
    DP_START_DATA_PROTOCOL,
    DP_START_COMPRESSION
} dp_start_state_e;

#endif /* _DP_CONFIG_H */
