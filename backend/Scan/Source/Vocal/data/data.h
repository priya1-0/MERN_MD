
/* ************************************************************************* */
/*
 *  data.h
 *
 *	(C) 1994 - 2006 VOCAL Technologies, Ltd.
 *
 *	ALL RIGHTS RESERVED.  PROPRIETARY AND CONFIDENTIAL.
 *
 *	VOCAL Technologies, Ltd.
 *	90A John Muir Drive.
 *	Buffalo, NY  14228
 *
 *  Product:    MODEM 101
 *
 *  Module:     DATA
 *
 *  This file includes the system's global, module and local data declarations.
 *
 *  Revision Number:    $Revision$
 *  Revision Status:    $State$
 *  Last Modified:      $Date$
 *  Identification:     $Id$
 *
 *  Revision History:   $Log$
 *  Revision History:   Revision 1.1.24.1  2009/04/28 19:33:27  zhangn1
 *  Revision History:   SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *  Revision History:
 *  Revision 1.0  1994/01/31  00:00:00  VD
 *  Initial release of software
 *
 */
/* ************************************************************************* */

#ifndef _DATA_DATA_H
#define _DATA_DATA_H

#define parm_d
#define stat_d
#define var_d
#define fast_d
#define persist_d
#define shared_d
#define temp_d
#define const_d
#define debug_d
#define local_d
#define coef_d

#ifndef BUILDING_OFFSETS
#ifndef WE_ARE_DEFINING_VARIABLES
#include "data/asm_refs.h"
#endif /* WE_ARE_DEFINING_VARIABLES */
#endif /* BUILDING_OFFSETS */

#ifdef BUILDING_DATA

#include "data/databld.h"

#else /* BUILDING_DATA */

#include "data/auto/sys.h"
#include "data/auto/cmn.h"

#include "data/auto/mod.h"
#include "data/auto/ph1.h"
#include "data/auto/lsd.h"
#include "data/auto/v32.h"

#include "data/auto/ph2.h"
#include "data/auto/v34.h"

#include "data/auto/user.h"

#include "data/auto/tel.h"

#endif /* BUILDING_DATA */

/* These special declarations are put last to override default names */
#include "data/special.h"

#endif /* _DATA_DATA_H */
