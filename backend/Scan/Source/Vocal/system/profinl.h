
/* ************************************************************************* */
/*
 *	profinl.h
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
 *	This file defines various profile.h macros as inline functions.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 20:47:21  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _SYSTEM_PROFINL_H
#define _SYSTEM_PROFINL_H

/* ************************************************************************* */

INLINE fract40
EMMSSLS(const fract32 x, fract y)
{
	fract40 temp40;
	temp40  = EMMUS (x, y);
	temp40  = ESHIFTE (temp40, -16);
	temp40 += EMMSS (FORMATL(x), y);
	return temp40;

}

/* ************************************************************************* */

/* ************************************************************************* */

#define FORMATERNDSAT(A)FORMATL((_rnd(_lsat(A))))

#define SATURATEE(A)	FORMATL((_lsat(A)))

/* ************************************************************************* */
#define LSATURATEE(A)(_lsat(A))

#define ESATURATEE(A)(_lsat(A))

/* ************************************************************************* */

#define MMSUSAT(x,y)		FORMATESAT(EMMSU(x,y))

/* ************************************************************************* */
#endif /* _SYSTEM_PROFINL_H */
