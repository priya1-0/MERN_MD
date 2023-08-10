
/* ************************************************************************* */
/*
 *	utils.h
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
 *	Module:		UTILS
 *
 *	This file contains the private declarations for the UTILS module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 20:53:02  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _UTILS_UTILS_H
#define _UTILS_UTILS_H

#include "utils/utilsd.h"

#include "net/sockaddr.h"
#include "sys/timer.h"
#include "ip/arp.h"

#include "ip/ip.h"

#include "utils/httpcli.h"

/* ************************************************************************* */

/*- MKHEADER Begin -*/

/* Global Routines: */

/* httpcli.c */
void encode64 (char *a, char *b);
void http_timeout (void *process);
int http_process_request (http_request_data *http_data);
int http_get_file (http_request_data *http_data);
int dohttp (int argc, char *argv[], void *p);

/* ping.c */
int doping (int argc, char *argv[], void *p);
void echo_proc (sint31 source, sint31 dest, icmp_t *icmp, struct mbuf *bp);
int pingem (int s, uint32 target, uint16 seq, uint16 id, uint16 len);

/* utils.c */
void utils_module_reset (void);
void utils_startup (void);

/*- MKHEADER End -*/


/* ************************************************************************* */

#endif /* _UTILS_UTILS_H */
