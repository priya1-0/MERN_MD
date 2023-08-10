
/* ************************************************************************* */
/*
 *	types.h
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
 *	This file contains the definitions for LAPM data types.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 19:57:11  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _LAPM_TYPES_H
#define _LAPM_TYPES_H

#include "lapm/frames.h"

/* ************************************************************************* */
/*
 * lapm event structure
 *
 */

typedef struct lapm_event_s {
	struct	lapm_event_s *next;			/* next event in list or NULL */
	uint16	type;						/* see events below! */
	lapm_rx_frame_t *rx_framep;	/* asssociated frame, if any */
} lapm_event_t;

/* ************************************************************************* */
/*
 * lapm list structure
 *
 */

typedef struct lapm_dummy_node_s {
	struct	lapm_dummy_node_s *next;
} lapm_dummy_node_t;

typedef struct {
	lapm_dummy_node_t *fill_begin;
	lapm_dummy_node_t *fill_end;
	lapm_dummy_node_t *empty_begin;
	lapm_dummy_node_t *empty_end;
} lapm_list_t;

#define pNODE		lapm_dummy_node_t *
#define pEVENT		lapm_event_t *
#define pTRANSMIT	lapm_tx_frame_t *
#define pRECEIVE	lapm_rx_frame_t *
#define pCONTROL	lapm_ctl_frame_t *

/* ************************************************************************* */
/*
 * lapm command structure
 *
 */

typedef const struct  {
	uint8	cmd_mask;			/* used to mask out the command					*/
	uint8	cmd_value;		/* associated command value						*/
	uint8	addr_type;		/* address type (C or R) of the frame			*/
	uint8	Spoll_mask;		/* used to mask out the S or I frame P/F bit	*/
	uint8	Spoll_value;		/* value of the S or I frame P/F bit			*/
	uint8	event_type;		/* event associated with the command			*/
} cmdtabentry_t;

/* ************************************************************************* */
/*
 * lapm lapm_state table structure
 *
 */

typedef const struct {
	uint8	new_state;			/* new state to process			*/
	void	(*fnc_ptr)(void);		/* action processing function	*/
} statetab_t;

/* ************************************************************************* */
/*
 * structure of the negotiation parameters and procedures
 *
 *	1.	transmiter's maximum number of outstanding I frames
 *	2.	receiver's maximum number of outstanding I frames
 *	3.	transmiter's maximum I frame info size
 *	4.	receiver's maximum I frame info size
 *	5.	value tells if selective reject is supported or not
 *	6.	value tells if loop-back TEST is supported or not
 *	7.	BTLZ p0, p1, p2
 *
 */

typedef struct {
	uint16	tk;
	uint16	rk;
	uint16	tn401;
	uint16	rn401;
	uint8	suptest;
	uint8	supsrej;
	uint8	p0;
	uint16	p1;
	uint8	p2;
} lapm_negotiation_parameters_t;

/* ************************************************************************* */
/*
 * debug structure
 *
 */

typedef struct {
	uint8	new_state;
	uint8	cur_state;
	uint8	last_state;
	uint8	cur_evt_type;
	uint8	last_evt_type;
} lapm_state_t;

/* ************************************************************************* */

#endif /* _LAPM_TYPES_H */
