
/* ************************************************************************* */
/*
 *	pathname.c
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
 *	This file contains the functions to convert relative to absolute pathnames.
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

/* Given a working directory and an arbitrary pathname, resolve them into
 * an absolute pathname. Memory is allocated for the result, which
 * the caller must free
 */
ENTRY char *
pathname (char *cd, char *path)
{
	register char *buf;

	if (cd == NULLCHAR || path == NULLCHAR)
		return NULLCHAR;

	/* Strip any leading white space on args */
	while (*cd == ' ' || *cd == '\t')
		cd++;
	while (*path == ' ' || *path == '\t')
		path++;

	/* Allocate and initialize output buffer; user must free */
	buf = (char *) mallocw ((unsigned) strlen(cd) + strlen(path) + 10);	/* fudge factor */
	buf[0] = '\0';

	/* Interpret path relative to cd only if it doesn't begin with "/" */
	if (path[0] != '/')
		crunch (buf, cd);

	crunch (buf, path);

	/* Special case: null final path means the root directory */
	if (buf[0] == '\0') {
		buf[0] = '/';
		buf[1] = '\0';
	}

	return buf;
}

/* ************************************************************************* */

/* Process a path name string, starting with and adding to
 * the existing buffer
 */
LOCAL void
crunch (char *buf, register char *path)
{
	register char *cp;

	cp = buf + strlen(buf);	/* Start write at end of current buffer */

	/* Now start crunching the pathname argument */
	for (;;) {
		/* Strip leading /'s; one will be written later */
		while (*path == '/')
			path++;
		if (*path == '\0')
			break;		/* no more, all done */
		/* Look for parent directory references, either at the end
		 * of the path or imbedded in it
		 */
		if (strcmp(path,"..") == 0 || strncmp(path,"../",3) == 0) {
			/* Hop up a level */
			if ((cp = strrchr (buf, '/')) == NULLCHAR)
				cp = buf;	/* Don't back up beyond root */
			*cp = '\0';		/* In case there's another .. */
			path += 2;		/* Skip ".." */
			while (*path == '/')	/* Skip one or more slashes */
				path++;
		/* Look for current directory references, either at the end
		 * of the path or imbedded in it
		 */
		} else if (strcmp(path,".") == 0 || strncmp(path,"./",2) == 0) {
			/* "no op" */
			path++;			/* Skip "." */
			while (*path == '/')	/* Skip one or more slashes */
				path++;
		} else {
			/* Ordinary name, copy up to next '/' or end of path */
			*cp++= '/';
			while (*path != '/' && *path != '\0')
				*cp++= *path++;
		}
	}
	*cp++= '\0';
}
