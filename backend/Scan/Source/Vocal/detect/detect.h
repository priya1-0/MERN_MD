
/* ************************************************************************* */
/*
 *	detect.h
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
 *	Module:		DETECT
 *
 *	This file contains the public declarations for the DETECT module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 18:29:10  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _DETECT_DETECT_H
#define _DETECT_DETECT_H

/* ************************************************************************* */

#include "dp/dp.h"
#include "detect/detectd.h"

/* ************************************************************************* */
/*
 * services provided to v42 (autoreliable and detect)
 *
 */

/*- MKHEADER Begin -*/

/* Global Routines: */

/* interrup.c */
void detect_async_rx_int (uint16 du);
uint16 detect_async_tx_int (void);
void detect_line_dispatch_convert (void);

/* routines.c */
dpf_t* detect_entry (void);
uint8 detect_install (void);
uint8 detect_remove (void);
uint8 detect_start (void);
uint8 detect_halt (void);
uint8 detect_reason (void);
void detect_timer (void);

/* rx_state.c */
uint16 pre_lapm_state_machine (void);
uint16 pre_mnp_state_machine (void);
uint16 ar_char_state_machine (void);
uint16 ar_200_ch_state_machine (void);
uint16 det_adp_state_machine (void);
uint16 det_odp_state_machine (void);

/*- MKHEADER End -*/


/* ************************************************************************* */

#endif /* _DETECT_DETECT_H */
