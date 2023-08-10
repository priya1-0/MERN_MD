
/* ************************************************************************* */
/*
 *	local.h
 *
 *	(C) 1994 - 2006 VOCAL Technologies, Ltd.
 *
 *	ALL RIGHTS RESERVED.  PROPRIETARY AND CONFIDENTIAL.
 *
 *	VOCAL Technologies, Ltd.
 *	90A John Muir Drive.
 *	Buffalo, NY  14228
 *
 *	Product:	LANsEND
 *
 *	Module:		NET
 *
 *	This file contains the private declarations for the NET module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 20:31:57  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */
#ifndef _NET_LOCAL_H
#define _NET_LOCAL_H

#include "net/locald.h"
#include "net/net.h"

/* ************************************************************************* */
/*- MKHEADER Begin -*/

/* Local Routines: */

/* netuser.c */

#ifdef net_netuser_c
static int strto32dd (char *cp, char **ncp, uint32 *np, char sep);
static int strto8ha (char *cp, char **ncp, uint8 n[], int cnt, char sep);
#endif /* net_netuser_c */

/*- MKHEADER End -*/


/* ************************************************************************* */

#endif /* _NET_LOCAL_H */
