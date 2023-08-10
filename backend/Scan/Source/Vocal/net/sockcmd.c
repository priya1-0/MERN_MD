
/* ************************************************************************* */
/*
 *	sockcmd.c
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
 *	This file contains the socket status functions.
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

#include "system/system.h"
#include "lansend/global.h"

#include "net/local.h"

#include "dev/dev.h"
#include "sys/sys.h"

#include "ip/ip.h"

#include "net/local.h"

/* Socket status display command */
ENTRY int
dosock (int argc, char *argv[], void *p)
{
	register struct usock *up;
	uint16 s;
	int i;
	struct sockaddr fsock;
	struct socklink *sp;
	char *cp;

	if (argc < 2) {
		printf("S#  Type    PCB      Remote socket         Owner\n");
		for (s = Nfiles;s < Nsock + Nfiles;s++) {
			up = itop (s);
			if (up == NULLUSOCK)
				continue;

			i = sizeof (fsock);
			if (getpeername (s, (char *) &fsock, &i) == 0 && i != 0)
				cp = snhptoa (&fsock);
			else
				cp = "";

			printf("%3d %-8s%-8lx %-22s%-8lx %-10s\n",
			 s, (long) Socktypes[(int)up->type], (long) ptol (up->cb.p), cp,
			 (long) ptol (up->owner), up->owner->name);
		}
		return 0;
	}
	if (atoi16u_err (argv[1], &s))
		return 1;
	if (s < Nfiles || s >= Nsock + Nfiles) {
		printf("Number out of range\n");
		return 1;
	}
	up = itop (s);
	if (up == NULLUSOCK) {
		printf("Socket not in use\n");
		return 0;
	}
	sp = up->sp;
	printf("%s %lx\n",Socktypes[(int)up->type],ptol(up->cb.p));
	if (up->cb.p == NULL)
		return 0;
	if (sp->status != NULLFP)
		(*sp->status) (up);
	return 0;
}
