
/* ************************************************************************* */
/*
 *	omcd.h
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
 *	Module:		OMC
 *
 *	This file contains the public parameter declarations/definitions for
 *	the OMC module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 20:41:08  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _OMC_OMCD_H
#define _OMC_OMCD_H

/* ************************************************************************* */

typedef struct {
	uint16	_class;
	uint16  _pump_carrier_code;
	bool	_omc_halt_active;
	bool	_omc_originate_procedure;
} omc_omc_t;

/* ************************************************************************* */

DEF_DATA(omc_omc_t, omc_omc)
#define OMC_OMC_DATA omc_omc_t omc_omc
#define OMC_OMC USE_DATA(omc_omc)

/* ************************************************************************* */

#define omc_class						(OMC_OMC._class)
#define omc_pump_carrier_code			(OMC_OMC._pump_carrier_code)
#define omc_halt_active					(OMC_OMC._omc_halt_active)
#define omc_originate_procedure			(OMC_OMC._omc_originate_procedure)

/* ************************************************************************* */

#endif /* OMC_OMCD_H */
