
/* ************************************************************************* */
/*
 *	string.c
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
 *	This file contains the functions.
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

ENTRY int
stricmp (const char *string1, const char *string2)
{
	char *s1, *s2;
	int i, ret;

	s1 = strdup (string1);
	s2 = strdup (string2);

	for (i = 0; i < strlen (s1);++ i)
		s1[i] = tolower (s1[i]);
	for (i = 0; i < strlen (s2);++ i)
		s2[i] = tolower (s2[i]);

	ret = strcmp (s1, s2);
	free (s1);
	free (s2);

	return ret;
}

/* ************************************************************************* */

ENTRY int
strnicmp (const char *string1, const char *string2, size_t n)
{
	char *s1, *s2;
	int i, ret;

	s1 = strdup (string1);
	s2 = strdup (string2);

	for (i = 0; i < strlen (s1);++ i)
		s1[i] = tolower (s1[i]);
	for (i = 0; i < strlen (s2);++ i)
		s2[i] = tolower (s2[i]);

	ret = strncmp (s1, s2, n);
	free (s1);
	free (s2);

	return ret;
}
