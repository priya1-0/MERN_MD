
/* ************************************************************************* */
/*
 *	devparam.c
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
 *	Module:		DEV
 *
 *  Parse and print device parameter tokens
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 19:38:37  zhangn1
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

#include "dev/local.h"

typedef struct param_s {
	int number;
	char *name;
} param_t;

static const param_t Parms[] =
{
	{PARAM_DTR, "DTR"},
	{PARAM_RTS, "RTS"},
	{PARAM_SPEED, "Speed"},
	{PARAM_IDLE, "Idle"},

	{PARAM_DCD, "DCD"},

	{PARAM_DOWN, "Down"},
	{PARAM_UP, "Up"},
	{PARAM_BLIND, "Blind"},
	{PARAM_READY, "Ready"},
	{PARAM_XOFF, "Xoff"},
	{ -1, NULLCHAR},
};

/* ************************************************************************* */
/*
 *  Function: devparam
 *
 *  Parse the device parameter name string to number identifier.
 *
 *  Parameters:
 *    "s" is the pointer to the string
 *
 *  Returns: + n as the parameter number
 *           -1 for error
 *
 */
ENTRY int
devparam (char *s)
{
	int len;
	const param_t *sp;

	len = strlen (s);
	if (isdigit (s[0]))
		return atoi (s);

	sp = &Parms[0];
	while (sp->number != -1) {
		if (strnicmp (s, sp->name, len) == 0)
			return sp->number;
		sp++;
	}
	return -1;
}

/* ************************************************************************* */
/*
 *  Function: parmname
 *
 *  Return string identifier for a parameter number.
 *
 *  Parameters:
 *    "n" is the parameter number
 *
 *  Returns: pointer to string
 *           NULLCHAR if error
 *
 */
ENTRY char *
parmname (int n)
{
	const param_t *sp;

	sp = &Parms[0];
	while (sp->number != -1) {
		if (sp->number == n)
			return sp->name;
		sp++;
	}
	return NULLCHAR;
}
