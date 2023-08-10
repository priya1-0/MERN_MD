
/* ************************************************************************* */
/*
 *	debug.c
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
 *	Module:		MAIN
 *
 *	This file contains the debug command processing functions.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.2.6.2  2009/04/28 19:56:06  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#include "system/system.h"
#include "lansend/global.h"

#include <ctype.h>

#include "net/net.h"
#include "sys/sys.h"
#include "dev/dev.h"

#include "ip/ip.h"

#include "lansend/local.h"

#include "trace/trace.h"
#include "term/term.h"
#include "utils/utils.h"
#include "wan/wan.h"

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

LOCAL void
display_debug_out_masks(void)
{
	printf (" STD                 0x0001\n");
	printf (" ERROR               0x0002\n");
	printf (" WARNING             0x0004\n");
	printf (" INFO                0x0008\n");
	printf ("\n");
	printf (" DIAG                0x0010\n");
	printf (" DEBUG               0x0020\n");
	printf (" DEV                 0x0040\n");
	printf (" STATUS              0x0080\n");
	printf ("\n");
	printf (" PROTOCOL_ERROR      0x0100\n");
	printf (" PROTOCOL_WARNING    0x0200\n");
	printf (" PROTOCOL_INFO       0x0400\n");
	printf (" PROTOCOL_DETAIL     0x0800\n");
	printf ("\n");
	printf (" SYSLOG_SEND         0x1000\n");
	printf (" SYSLOG_LOCAL        0x2000\n");
	printf (" DEBUGLOG_SEND       0x4000\n");
	printf (" PERIODIC            0x8000\n");
	printf ("\n");
	printf ("\n");
}

LOCAL int
debug_out_process_mask (char *cp, uint16 *np)
{
#define MODE_REPLACE 0
#define MODE_OR 1
#define MODE_AND 2
	int mode = MODE_REPLACE;
	uint16 mask = 0;
	/* parse a string of form [+-] <hex16> */

	if (!cp) {
		return 0;
	}
	if (!np) {
		return 0;
	}

	if (*cp == '+' ) {
		mode = MODE_OR;
		cp++;
	} else if (*cp == '-') {
		mode = MODE_AND;
		cp++;
	}

	if (atoi16uh_err (cp, &mask)) {
		return 0;
	}

	switch (mode) {
	case MODE_REPLACE:
		*np = mask;
		return 1;

	case MODE_OR:
		*np |= mask;
		return 1;

	case MODE_AND:
		*np &= ~mask;
		return 1;
	}

	return 0;
}
ENTRY int
dodebugoutputall (int argc, char *argv[], void *p)
{
	if (argc > 1) {
		int tmp = 0;
		tmp |= debug_out_process_mask (argv[1], &parm__net_debug_level_ata);
		tmp |= debug_out_process_mask (argv[1], &parm__net_debug_level_sip);
		tmp |= debug_out_process_mask (argv[1], &parm__net_debug_level_mgcp);
		tmp |= debug_out_process_mask (argv[1], &parm__net_debug_level_net);
		tmp |= debug_out_process_mask (argv[1], &parm__net_debug_level_omc);
		tmp |= debug_out_process_mask (argv[1], &parm__net_debug_level_pmp);
		return tmp;
	} else {
		display_debug_out_masks();
		printf ("ATA  debug mask 0x%04x\n", parm__net_debug_level_ata);
		printf ("SIP  debug mask 0x%04x\n", parm__net_debug_level_sip);
		printf ("MGCP debug mask 0x%04x\n", parm__net_debug_level_mgcp);
		printf ("NET  debug mask 0x%04x\n", parm__net_debug_level_net);
		printf ("OMC  debug mask 0x%04x\n", parm__net_debug_level_omc);
		printf ("PMP  debug mask 0x%04x\n", parm__net_debug_level_pmp);
	}
	return 0;
}

ENTRY int
dodebugoutputata (int argc, char *argv[], void *p)
{
	if (argc > 1) {
		return debug_out_process_mask (argv[1], &parm__net_debug_level_ata);
	} else {
		display_debug_out_masks();
		printf ("Debug mask 0x%04x\n", parm__net_debug_level_ata);
	}
	return 0;
}

ENTRY int
dodebugoutputsip (int argc, char *argv[], void *p)
{
	if (argc > 1) {
		return debug_out_process_mask (argv[1], &parm__net_debug_level_sip);
	} else {
		display_debug_out_masks();
		printf ("Debug mask 0x%04x\n", parm__net_debug_level_sip);
	}
	return 0;
}

ENTRY int
dodebugoutputmgcp (int argc, char *argv[], void *p)
{
	if (argc > 1) {
		return debug_out_process_mask (argv[1], &parm__net_debug_level_mgcp);
	} else {
		display_debug_out_masks();
		printf ("Debug mask 0x%04x\n", parm__net_debug_level_mgcp);
	}
	return 0;
}

ENTRY int
dodebugoutputnet (int argc, char *argv[], void *p)
{
	if (argc > 1) {
		return debug_out_process_mask (argv[1], &parm__net_debug_level_net);
	} else {
		display_debug_out_masks();
		printf ("Debug mask 0x%04x\n", parm__net_debug_level_net);
	}
	return 0;
}

ENTRY int
dodebugoutputomc (int argc, char *argv[], void *p)
{
	if (argc > 1) {
		return debug_out_process_mask (argv[1], &parm__net_debug_level_omc);
	} else {
		display_debug_out_masks();
		printf ("Debug mask 0x%04x\n", parm__net_debug_level_omc);
	}
	return 0;
}

ENTRY int
dodebugoutputpmp (int argc, char *argv[], void *p)
{
	if (argc > 1) {
		return debug_out_process_mask (argv[1], &parm__net_debug_level_pmp);
	} else {
		display_debug_out_masks();
		printf ("Debug mask 0x%04x\n", parm__net_debug_level_pmp);
	}
	return 0;
}

/* ************************************************************************* */

/* "debug output" subcommands */
extern const struct cmds Debugoutputcmds[] = {
	{"all",			dodebugoutputall,		0,	0, 	""},
	{"ata",			dodebugoutputata,		0,	0, 	""},
	{"mgcp",		dodebugoutputmgcp,  	0,	0, 	""},
	{"net",			dodebugoutputnet,		0,	0, 	""},
	{"omc",			dodebugoutputomc,		0,	0, 	""},
	{"pmp",			dodebugoutputpmp,		0,	0, 	""},
	{"sip",			dodebugoutputsip,		0,	0, 	""},
	{NULLCHAR},
};

ENTRY int
dodebugoutput (int argc, char *argv[], void *p)
{
	return subcmd (Debugoutputcmds, argc, argv, p);
}

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

ENTRY int
dolevels (int argc, char *argv[], void *p)
{

	return 0;
}

/* ************************************************************************* */

/* ************************************************************************* */

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

/* ************************************************************************* */

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

extern const struct cmds Debugcmds[] = {
	{"all",			dodebugoutputall,		0,	0, 	"[mask]"},
	{"output",		dodebugoutput,			0,	0, 	"<all|ata|mgcp|net|omc|pmp|sip> [+-][mask]"},
	{"levels",		dolevels,				0,	0, 	"[channel]"},

	{NULLCHAR},
};

/* ************************************************************************* */

ENTRY int
dodebug (int argc, char *argv[], void *p)
{
	return subcmd (Debugcmds, argc, argv, p);
}
