
/* ************************************************************************* */
/*
 *	sys.h
 *
 *	(C) 1994 - 2007 VOCAL Technologies, Ltd.
 *
 *	ALL RIGHTS RESERVED.  PROPRIETARY AND CONFIDENTIAL.
 *
 *	VOCAL Technologies, Ltd.
 *	90A John Muir Drive.
 *	Buffalo, NY  14228
 *
 *	Product:	MODEM 101
 *
 *	Module:		DATA
 *
 *	This file contains automatically generated data for sys.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 19:12:25  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _DATA_SYS_H
#define _DATA_SYS_H
#include "data/sections.h"

/* ************************************************************************* */

typedef struct {
	shared_d   uint16                      _parm__net_debug_level_ata;
	shared_d   uint16                      _parm__net_debug_level_sip;
	shared_d   uint16                      _parm__net_debug_level_mgcp;
	shared_d   uint16                      _parm__net_debug_level_net;
	shared_d   uint16                      _parm__net_debug_level_omc;
	shared_d   uint16                      _parm__net_debug_level_pmp;
	shared_d   uint16                      _codec_tx_mask;
	shared_d   uint16                      _clock_rx;
	shared_d   sint15                      _sample_buffer [SAMPLE_BUFFER_SIZE];
	shared_d   uint16                      _sample_buffer_size;
	shared_d   uint16                      _sample_overflow_count;
	shared_d   int                         _sample_foreground_offset;
	shared_d   int                         _sample_interrupt_offset;
	shared_d   int                         _sample_interrupt_tx_offset;
	shared_d   int                         _interrupt_sample_count;
	shared_d   uint16                      _interrupt_running_fg;
	shared_d   volatile int                _tx_data_ti;
	shared_d   volatile int                _rx_data_ti;
	shared_d   volatile int                _codec_int_state;
	shared_d   volatile uint16             _codec_control_word;
} sys_shared_t;

/* ************************************************************************* */

DEF_DATA(sys_shared_t, sys_shared)
#define SYS_SHARED_DATA sys_shared_t sys_shared
#define SYS_SHARED USE_DATA(sys_shared)
#define sys_shared_used

/* ************************************************************************* */

#define parm__net_debug_level_ata        SYS_SHARED._parm__net_debug_level_ata
#define parm__net_debug_level_sip        SYS_SHARED._parm__net_debug_level_sip
#define parm__net_debug_level_mgcp       SYS_SHARED._parm__net_debug_level_mgcp
#define parm__net_debug_level_net        SYS_SHARED._parm__net_debug_level_net
#define parm__net_debug_level_omc        SYS_SHARED._parm__net_debug_level_omc
#define parm__net_debug_level_pmp        SYS_SHARED._parm__net_debug_level_pmp
#define codec_tx_mask                    SYS_SHARED._codec_tx_mask
#define clock_rx                         SYS_SHARED._clock_rx
#define sample_buffer                    SYS_SHARED._sample_buffer
#define sample_buffer_size               SYS_SHARED._sample_buffer_size
#define sample_overflow_count            SYS_SHARED._sample_overflow_count
#define sample_foreground_offset         SYS_SHARED._sample_foreground_offset
#define sample_interrupt_offset          SYS_SHARED._sample_interrupt_offset
#define sample_interrupt_tx_offset       SYS_SHARED._sample_interrupt_tx_offset
#define interrupt_sample_count           SYS_SHARED._interrupt_sample_count
#define interrupt_running_fg             SYS_SHARED._interrupt_running_fg
#define tx_data_ti                       SYS_SHARED._tx_data_ti
#define rx_data_ti                       SYS_SHARED._rx_data_ti
#define codec_int_state                  SYS_SHARED._codec_int_state
#define codec_control_word               SYS_SHARED._codec_control_word

/* ************************************************************************* */

#endif /* _DATA_SYS_H */
