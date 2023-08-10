
/* ************************************************************************* */
/*
 *	system.h
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
 *	Module:		SYSTEM
 *
 *	This file defines the standard modem 101 system definitions.
 *	All source files are to include this FIRST.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 20:47:21  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _SYSTEM_SYSTEM_H
#define _SYSTEM_SYSTEM_H

/* ************************************************************************* */

#include "include/options.h"

/* ************************************************************************* */

#include "system/standard.h"

#include "support/time.h"

#include <stdarg.h>
#include <string.h>

#include <errno.h>
#include "include/errno.h"

#include <stdlib.h>

#include "sys/sys.h"

#include "dspbios/d55cfg.h"

/* ************************************************************************* */

#include "system/module.h"
#include "system/print.h"

/* ************************************************************************* */

#include "include/ascii.h"
#include "include/events.h"
#include "include/idents.h"
#include "include/modem.h"
#include "include/owners.h"
#include "include/speech.h"
#include "include/status.h"
#include "include/sart.h"

#include "data/structs.h"

/* ************************************************************************* */

#include "system/allocate.h"
#include "system/access.h"
#include "system/globals.h"

/* ************************************************************************* */

#include "kernel/kernel.h"

#include "support/support.h"

#include "data/data.h"

#include "mdm/systemd.h"

#include "debug/logging.h"

/* ************************************************************************* */

#endif /* _SYSTEM_SYSTEM_H */
