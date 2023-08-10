
/* ************************************************************************* */
/*
 *	mnpd.h
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
 *	Module:		MNP
 *
 *	This file contains the public parameter declarations/definitions for
 *	the MNP module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 20:29:43  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _MNP_MNPD_H
#define _MNP_MNPD_H

#include "mnp/config.h"

/* ************************************************************************* */
/*
 * passed parameter variables
 *
 */

typedef struct {

	bool	_parm_version_2_en;
	bool	_parm_version_3_en;
	bool	_parm_version_3_start;
	bool	_parm_plus_en;
	uint8   _parm_mnp_version_type;

} mnp_mnp_t;

/* ************************************************************************* */

#define MNP_MNP_DATA mnp_mnp_t mnp_mnp
DEF_DATA(mnp_mnp_t, mnp_mnp)
#define MNP_MNP USE_DATA(mnp_mnp)

/* ************************************************************************* */

#define parm__mnp_version_2_en				(MNP_MNP._parm_version_2_en)
#define parm__mnp_version_3_en				(MNP_MNP._parm_version_3_en)
#define parm__mnp_version_3_start			(MNP_MNP._parm_version_3_start)
#define parm__mnp_plus_en					(MNP_MNP._parm_plus_en)
#define parm__mnp_version_type				(MNP_MNP._parm_mnp_version_type)

/* ************************************************************************* */

#endif /* MNP_MNPD_H */
