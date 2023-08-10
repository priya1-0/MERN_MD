
/* ************************************************************************* */
/*
 *	include.h
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
 *	This module contains references to all include files that contain
 *	data definitions.
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

#ifndef _MDM_INCLUDE_H
#define _MDM_INCLUDE_H

/* ************************************************************************* */
/* ************************************************************************* */

#include "mdm/locald.h"
#include "mdm/mdmd.h"

#include "support/supportd.h"
#include "support/locald.h"

/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */
/* ************************************************************************* */

/* command set controller related parameter definitions */
#include "csc/cscd.h"
#include "csc/dted.h"
#include "csc/locald.h"
#include "csc/parmd.h"
#include "csc/responsd.h"
#include "csc/stated.h"
#include "csc/monitord.h"
#include "csc/tabled.h"

#include "bind/bindd.h"
#include "bind/locald.h"

#include "v24/locald.h"
#include "v24/v24d.h"
#include "dteif/dteifd.h"
#include "dteif/locald.h"

/* command set parameter definitions */
#include "csp/parmd.h"
#include "csp/cspd.h"
#include "csp/locald.h"

/* ************************************************************************* */
/* ************************************************************************* */

#include "omc/locald.h"
#include "omc/omcd.h"
#include "omc/parmd.h"

#include "line/locald.h"

/*************************************************************************/
/* data protocol (DM_DP) headers */
/*************************************************************************/

#include "dp/locald.h"

#include "detect/detect.h"
#include "detect/locald.h"

#include "mnp/locald.h"
#include "mnp/mnpd.h"
#include "mnp5/locald.h"
#include "mnp5/mnp5d.h"
#include "line/mnpld.h"

#include "lapm/lapmd.h"
#include "lapm/locald.h"
#include "line/lapmld.h"

#include "buffered/locald.h"
#include "line/bufferld.h"

#include "direct/directd.h"
#include "direct/locald.h"

#include "btlz/btlzd.h"
#include "btlz/locald.h"

/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

#endif /* _MDM_INCLUDE_H */
