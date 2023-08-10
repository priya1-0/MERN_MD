
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
 *	Module:		SUPPORT
 *
 *	This file contains the private parameter declarations/definitions
 *	for the SUPPORT module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 20:44:27  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _SUPPORT_LOCALD_H
#define _SUPPORT_LOCALD_H

#include "support/config.h"

typedef struct {
	char	_support_str [PRINT_SIZE_MAX];

} support_local_t;

/* ************************************************************************* */

DEF_DATA(support_local_t, support_local)
#define SUPPORT_LOCAL_DATA support_local_t support_local
#define SUPPORT_LOCAL USE_DATA(support_local)

/* ************************************************************************* */

#define support_str							(SUPPORT_LOCAL._support_str)

#endif /* SUPPORT_LOCALD_H */
