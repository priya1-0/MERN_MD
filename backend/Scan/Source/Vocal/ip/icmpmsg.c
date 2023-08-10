
/* ************************************************************************* */
/*
 *	icmpmsg.c
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

/* ICMP message types */
char *Icmptypes[] = {
	"Echo Reply",
	NULLCHAR,
	NULLCHAR,
	"Unreachable",
	"Source Quench",
	"Redirect",
	NULLCHAR,
	NULLCHAR,
	"Echo Request",
	NULLCHAR,
	NULLCHAR,
	"Time Exceeded",
	"Parameter Problem",
	"Timestamp",
	"Timestamp Reply",
	"Information Request",
	"Information Reply"
};

/* ICMP unreachable messages */
char *Unreach[] = {
	"Network",
	"Host",
	"Protocol",
	"Port",
	"Fragmentation",
        "Source route",
	"Dest net unknown",
	"Dest host unknown",
	"Source host isolated",
	"Net prohibited",
	"Host prohibited",
	"Net TOS",
	"Host TOS",
	"Administratively Prohibited"
};
/* ICMP Time exceeded messages */
char *Exceed[] = {
	"Time-to-live",
	"Fragment reassembly"
};

/* ICMP redirect messages */
char *Redirect[] = {
	"Network",
	"Host",
	"TOS & Network",
	"TOS & Host"
};
