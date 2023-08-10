
/* ************************************************************************* */
/*
 *	dteif.h
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
 *	Module:		DTEIF
 *
 *	This file contains the public declarations for the DTEIF module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 19:48:36  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _DTEIF_DTEIF_H
#define _DTEIF_DTEIF_H

/* ************************************************************************* */

#include "dteif/dteifd.h"

/* ************************************************************************* */

#define DTEIF_RX_STATE__OFF				0
#define DTEIF_RX_STATE__DTE				1
#define DTEIF_RX_STATE__A				2
#define DTEIF_RX_STATE__T				3

#define DTEIF_TX_STATE__OFF				0
#define DTEIF_TX_STATE__DTE				1
#define DTEIF_TX_STATE__DTE_XOFF		2
#define DTEIF_TX_STATE__CMDSET			3
#define DTEIF_TX_STATE__LOCAL_ECHO		4

#define DTEIF_STATE__CONTROL				0
#define DTEIF_STATE__PRE_DATA				1
#define DTEIF_STATE__DATA					2
#define DTEIF_STATE__POST_DATA				3

/* ************************************************************************* */

extern uint16 MPI_Interrupt_state;

/* ************************************************************************* */

/*- MKHEADER Begin -*/

/* Global Routines: */

/* dte5501.c */
void dteif_hw_module_reset (void);
void dteif_tx_start (void);
void dteif_tx_start_disabled (void);
void UartInterrupt(void);
void dteif_dcd_on (void);
void dteif_dcd_off (void);
void dteif_dsr_on (void);
void dteif_dsr_off (void);
void dteif_cts_on (void);
void dteif_cts_off (void);
void dteif_ri_on (void);
void dteif_ri_off (void);
void dteif_hook_on (void);
void dteif_hook_off (void);
bool dteif_read_dtr (void);
bool dteif_read_rts (void);
void dteif_v24_status_report (void);

/* dteif.c */
void dteif_module_reset (void);

/* process.c */
uint16 dteif_rx_free(void);
void dteif_rx (uint16 du);
uint16 dteif_tx (void);
void dteif_echo_put_du (uint16 du);
void dteif_rx_state_set (uint16 state);
void dteif_tx_state_set (uint16 state);

/*- MKHEADER End -*/


/* ************************************************************************* */

#endif /* _DTEIF_DTEIF_H */
