
/* ************************************************************************* */
/*
 *	v34syn.h
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
 *	Module:		LIB34L
 *
 *	This file contains the V.34 forced resync detection defines.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 19:58:46  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _LIB34L_V34SYN_H
#define _LIB34L_V34SYN_H

/* ************************************************************************* */

/* ************************************************************************* */

#define V34_RESYNC_N				9							/* 9*/
#define V34_RESYNC_Nx2_plus_1		1+(1 * 2 * V34_RESYNC_N)	/*19*/
#define V34_RESYNC_Nx2_plus_1_x1	1+(1 * 2 * V34_RESYNC_N)	/*19*/
#define V34_RESYNC_Nx2_plus_1_x2	2+(2 * 2 * V34_RESYNC_N)	/*38*/
#define V34_RESYNC_Nx2_plus_1_x8	8+(8 * 2 * V34_RESYNC_N)	/*152*/

/* ************************************************************************* */

#endif /* _LIB34L_V34SYN_H */
