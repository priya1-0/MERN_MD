
/* ************************************************************************* */
/*
 *	omc.h
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
 *	This file contains the public declarations for the OMC module.
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
 */
/* ************************************************************************* */

#ifndef _OMC_OMC_H
#define _OMC_OMC_H

/* ************************************************************************* */

#include "omc/omcd.h"
#include "omc/parmd.h"

/* ************************************************************************* */
/*- MKHEADER Begin -*/

/* Global States: */

/* omc.c */
extern state_action_t omc_idle [];

/* Global Routines: */

/* common.c */
void omc_module_reset (void);
void omc_state_print (uint16 state_num);
void omc_sm_startup (void);
void omc_disc_ack (void);
void omc_halt_ack (void);
void omc_tel_startup_ack_h (void);
void omc_tel_startup (void);
void omc_dm_process_stats (void);

/*- MKHEADER End -*/


/* ************************************************************************* */

#endif /* _OMC_OMC_H */
