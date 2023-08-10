
/* ************************************************************************* */
/*
 *	locald.h
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
 *	This file contains the private parameter declarations/definitions
 *	for the MDM module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 20:23:04  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _MDM_LOCALD_H
#define _MDM_LOCALD_H

#include "mdm/config.h"

/* ************************************************************************* */

typedef struct {
	bool	_tick_occurred;

	uint16	_arg_debug_flag;

} mdm_local_t;

/* ************************************************************************* */

DEF_DATA(mdm_local_t, mdm_local)
#define MDM_LOCAL_DATA mdm_local_t mdm_local
#define MDM_LOCAL USE_DATA(mdm_local)

/* ************************************************************************* */

#define	mdm_tick_occurred					(MDM_LOCAL._tick_occurred)

#define	mdm_system_dot_display_flag			(MDM_LOCAL._dot_display_flag)
#define	mdm_system_dot_display_cnt			(MDM_LOCAL._dot_display_cnt)
#define	mdm_system_ratio_top				(MDM_LOCAL._ratio_top)
#define	mdm_system_ratio_bottom				(MDM_LOCAL._ratio_bottom)
#define	mdm_system_ratio_cnt				(MDM_LOCAL._ratio_cnt)

#define	mdm_arg_debug_flag					(MDM_LOCAL._arg_debug_flag)

/* ************************************************************************* */

#endif /* _MDM_LOCALD_H */
