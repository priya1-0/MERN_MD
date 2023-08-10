
/* ************************************************************************* */
/*
 *	icmpcmd.c
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
 *	Module:		IP
 *
 *	This file contains the functions.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 19:52:55  zhangn1
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

#include "ip/local.h"

int Icmp_trace = FALSE;
int Icmp_echo = TRUE;

ENTRY void
icmpcmd_init (void)
{
	Icmp_trace = FALSE;
	Icmp_echo = TRUE;
}

LOCAL int
doicmpmib (int argc, char *argv[], void *p)
{
	print_mib (Icmp_mib, NUMICMPMIB);
	return 0;
}

LOCAL int
doicmptrace (int argc, char *argv[], void *p)
{
	return chg_bool (&Icmp_trace, "ICMP tracing", argc, argv);
}

LOCAL int
doicmpecho (int argc, char *argv[], void *p)
{
	return chg_bool (&Icmp_echo, "ICMP echo response accept", argc, argv);
}

static const struct cmds Icmpcmds[] = {
	{"echo",		doicmpecho,			0,	0,	""},
	{"mib",			doicmpmib,			0,	0,	""},
	{"trace",		doicmptrace,		0,	0,	"[on|off]"},
	{NULLCHAR}
};

ENTRY int
doicmp (int argc, char *argv[], void *p)
{
	return subcmd (Icmpcmds, argc, argv, p);
}
