
/* ************************************************************************* */
/*
 *	dte.h
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
 *	This file contains definitions for the DTE specific resources of
 *	the CSC module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 19:06:28  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _CSC_DTE_H
#define _CSC_DTE_H

#include "csc/dted.h"

/* ************************************************************************* */

/*- MKHEADER Begin -*/

/* Global Routines: */

/* dte.c */
void dte_tx_put_du__raw (uint16 du);
uint16 dte_rx_get_du (void);
void dte_tx_put_du (uint16 du);
void dte_tx_put_break (uint8 duration);
bool dte_tx_get_du (uint16 *dup);
bool dte_tx_examine_du (uint16 *dup);
bool dte_rx_put_du (uint16 du);
uint16 dte_tx_free (void);
void dte_tx_clear (void);
void dte_rx_clear (void);
uint16 dte_rx_free (void);
uint16 dte_rx_avail (void);
uint16 dte_tx_avail (void);
void dte_rx_put_break (uint8 duration, uint8 type);

/*- MKHEADER End -*/


/* ************************************************************************* */

#endif /* _CSC_DTE_H */
