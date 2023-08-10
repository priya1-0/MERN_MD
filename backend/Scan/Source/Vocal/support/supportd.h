
/* ************************************************************************* */
/*
 *	supportd.h
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
 *	Module:		SUPPORT
 *
 *	This file contains the public parameter declarations/definitions for
 *	the SUPPORT module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 20:44:27  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _SUPPORT_SUPPORTD_H
#define _SUPPORT_SUPPORTD_H

#include "support/config.h"

/* ************************************************************************* */

typedef struct {
	bool	_print_disable;
} support_support_t;

/* ************************************************************************* */

DEF_DATA(support_support_t, support_support)
#define SUPPORT_SUPPORT_DATA support_support_t support_support
#define SUPPORT_SUPPORT USE_DATA(support_support)

/* ************************************************************************* */

#define print_disable						(SUPPORT_SUPPORT._print_disable)

/* ************************************************************************* */

#endif /* _SUPPORT_SUPPORTD_H */
