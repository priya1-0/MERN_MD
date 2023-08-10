
/* ************************************************************************* */
/*
 *	misc.c
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
 *	Module:		SYS
 *
 *	This file contains the miscellaneous machine independent utilities.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 20:46:45  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#include "system/system.h"
#include "lansend/global.h"

#include "net/net.h"
#include "sys/sys.h"
#include "dev/dev.h"

#include "ip/ip.h"

#include "sys/local.h"

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

/* Select from an array of strings, or return ascii number if out of range */
ENTRY char *
smsg (char *msgs[], uint16 nmsgs, uint16 n)
{
	static char buf[16];

	if (n < nmsgs && msgs[n] != NULLCHAR)
		return msgs[n];
	sprintf(buf,"%u",n);
	return buf;
}

/* ************************************************************************* */

/* replace terminating end of line marker(s) with null */
ENTRY void
rip (register char *s)
{
	register char *cp;

	if ((cp = strchr (s, '\n')) != NULLCHAR)
		*cp = '\0';
	if ((cp = strchr (s, '\r')) != NULLCHAR)
		*cp = '\0';
}

/* ************************************************************************* */

/* Count the occurrances of 'c' in a buffer */
ENTRY int
memcnt (char *buf, char c, int size)
{
	int cnt = 0;
	char *icp;

	while (size != 0) {
		if ((icp = (char *) memchr (buf, c, size)) == NULLCHAR)
			break;	/* No more found */
		/* Advance the start of the next search to right after
		 * this character
		 */
		/* Same thing, just more readable. */
		size -= (int) ((icp + 1) - buf);
		buf = icp + 1;
		cnt++;
	}
	return cnt;
}

/* ************************************************************************* */

/* Copy a string to a malloc'ed buffer. Turbo C has this one in its
 * library, but it doesn't call mallocw () and can therefore return NULL.
 * NOS uses of strdup () generally don't check for NULL, so they need this one.
 */
ENTRY char *
strdup (const char *s)
{
	register char *out;
	register int len;

	if (s == NULLCHAR)
		return NULLCHAR;
	len = strlen (s);
	out = (char *) mallocw (len + 1);
	/* This is probably a tad faster than strcpy, since we know the len */
	memcpy (out, s, len);
	out[len] = '\0';
	return out;
}

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* Routines not needed for Turbo 2.0, but available for older libraries */

/* ************************************************************************* */

/* Compute int(log2(x)) */
ENTRY int
log2 (uint16 x)
{
	register int n = 16;
	for (;n != 0;n--) {
		if (x & 0x8000)
			break;
		x <<= 1;
	}
	n--;
	return n;
}
