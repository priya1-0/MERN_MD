
/* ************************************************************************* */
/*
 *	network.c
 *
 *	(C) 2005 - 2006 VOCAL Technologies, Ltd.
 *
 *	ALL RIGHTS RESERVED.  PROPRIETARY AND CONFIDENTIAL.
 *
 *	VOCAL Technologies, Ltd.
 *	90A John Muir Drive.
 *	Buffalo, NY  14228
 *
 *	Product:	MASTER
 *
 *	Module:		SUPPORT
 *
 *	This file contains miscellaneous network support utilities.
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

#include "system/system.h"
#include "support/local.h"

/* ************************************************************************* */

/* Host-network conversion routines.  Could be replaced on the x86 with
 * assembler code in pcgen.s
 */
/* Put a long in host order into a char array in network order */
ENTRY char *
put32 (register char *cp, uint32 x)
{
	*cp++= uchar (x >> 24);
	*cp++= uchar (x >> 16);
	*cp++= uchar (x >> 8);
	*cp++= uchar (x);
	return cp;
}

/* ************************************************************************* */

/* Put a short in host order into a char array in network order */
ENTRY char *
put16 (char *cp, uint16 x)
{
	*cp++= uchar (x >> 8);
	*cp++= uchar (x);
	return cp;
}

/* ************************************************************************* */

ENTRY uint16
get16 (register char *cp)
{
	register uint16 x;

	x = uchar (*cp++);
	x <<= 8;
	x |= uchar (*cp);
	return x;
}

/* ************************************************************************* */

/* Machine-independent, alignment insensitive network-to-host long conversion */
ENTRY uint32
get32 (register char *cp)
{
	sint31 rval;

	rval = uchar (*cp++);
	rval <<= 8;
	rval |= uchar (*cp++);
	rval <<= 8;
	rval |= uchar (*cp++);
	rval <<= 8;
	rval |= uchar (*cp);

	return rval;
}
