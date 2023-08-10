
/* ************************************************************************* */
/*
 *	mdmd.h
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
 *	Module:		MDM
 *
 *	This file contains the public parameter declarations/definitions for
 *	the MDM module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 20:23:04  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _MDM_MDMD_H
#define _MDM_MDMD_H

#include "mdm/config.h"

/* ************************************************************************* */

typedef struct {
	char	_rev_string[MDM_REV_STR_MAX_SIZE];
	uint32	_tick_cnt;

	bool	_open;

	bool	_exit_without_dsp_shutdown;
	bool	_exit_with_dsp_reset;

} mdm_mdm_t;

/* ************************************************************************* */

DEF_DATA(mdm_mdm_t, mdm_mdm)
#define MDM_MDM_DATA mdm_mdm_t mdm_mdm
#define MDM_MDM USE_DATA(mdm_mdm)

/* ************************************************************************* */

#define	mdm_rev_string						(MDM_MDM._rev_string)
#define mdm_tick_cnt						(MDM_MDM._tick_cnt)

#define	mdm_open							(MDM_MDM._open)

#define mdm_exit_without_dsp_shutdown		(MDM_MDM._exit_without_dsp_shutdown)
#define mdm_exit_with_dsp_reset				(MDM_MDM._exit_with_dsp_reset)
#define mdm_critical_section				(MDM_MDM._critical_section)

/* ************************************************************************* */

#endif /* _MDM_MDMD_H */
