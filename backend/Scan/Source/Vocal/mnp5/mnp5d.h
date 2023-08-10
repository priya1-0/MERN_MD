
/* ************************************************************************* */
/*
 *	mnp5d.h
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
 *	Module:		MNP5
 *
 *	This file contains the public parameter declarations/definitions for
 *	the MNP5 module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 20:31:23  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _MNP5_MNP5D_H
#define _MNP5_MNP5D_H

/* ************************************************************************* */
/*
 * common (passed) variables
 *
 */

typedef struct {
	bool	_tx_flush;
	expand8 *_tx_datap;
	expand8 _tx_index;

	expand8 _rx_index;
	expand8 _rx_error;						/* MNP5_ERR__xxx */
} mnp5_mnp5_t;

/* ************************************************************************* */

DEF_DATA (mnp5_mnp5_t, mnp5_mnp5)
#define MNP5_MNP5_DATA mnp5_mnp5_t mnp5_mnp5
#define MNP5_MNP5 USE_DATA(mnp5_mnp5)

/* ************************************************************************* */

#define shared_mnp5_tx_flush				(MNP5_MNP5._tx_flush)
#define shared_mnp5_tx_datap				(MNP5_MNP5._tx_datap)
#define shared_mnp5_tx_index				(MNP5_MNP5._tx_index)
#define shared_mnp5_rx_index				(MNP5_MNP5._rx_index)
#define shared_mnp5_rx_error				(MNP5_MNP5._rx_error)

/* ************************************************************************* */

#endif /* _MNP5_MNP5D_H */
