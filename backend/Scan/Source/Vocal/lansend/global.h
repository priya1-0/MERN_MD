
/* ************************************************************************* */
/*
 *	global.h
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
 *	Module:		LANSEND
 *
 *	This file contains the functions.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 19:56:06  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

/* Global definitions used by every source file.
 * Some may be compiler dependent.
 */
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "lansend/config.h"

/* ************************************************************************* */

void net_log (int s, char *fmt, ...);

/* ************************************************************************* */

#define	READ_BINARY	"r"
#define	WRITE_BINARY	"w"
#define	APPEND_BINARY	"a+"
#define	READ_TEXT	"r"
#define	WRITE_TEXT	"w"
#define	APPEND_TEXT	"a+"

/* ************************************************************************* */

#define	ASSIGN(a,b)	((a) = (b))

#define	NULLFP	 (int (*)())0	/* Null pointer to function returning int */
#define	NULLVFP	 (void (*)())0	/* Null pointer to function returning void */

#define	NULLVIFP (INTERRUPT (*)())0

/* ************************************************************************* */

/* standard boolean constants */
#ifndef NO
#define NO 0
#endif /* NO */
#ifndef YES
#define YES 1
#endif /* YES */

/* ************************************************************************* */

#define CTLA 0x1
#define CTLB 0x2
#define CTLC 0x3
#define CTLD 0x4
#define CTLE 0x5
#define CTLF 0x6
#define CTLG 0x7
#define CTLH 0x8
#define CTLI 0x9
#define CTLJ 0xa
#define CTLK 0xb
#define CTLL 0xc
#define CTLM 0xd
#define CTLN 0xe
#define CTLO 0xf
#define CTLP 0x10
#define CTLQ 0x11
#define CTLR 0x12
#define CTLS 0x13
#define CTLT 0x14
#define CTLU 0x15
#define CTLV 0x16
#define CTLW 0x17
#define CTLX 0x18
#define CTLY 0x19
#define CTLZ 0x1a

/* ************************************************************************* */

/* string equality shorthand */
#define STREQ(x,y) (strcmp(x,y) == 0)

/* Extract a short from a long */
#define hiword(x)	((uint16)((x) >> 16))
#define loword(x)	((uint16)(x))

/* Extract a byte from a short */
#define hibyte(x)	(((uint8)((x) >> 8)) & 0xff)
#define lobyte(x)	(((uint8)(x)) & 0xff)

/* Extract nibbles from a byte */
#define	hinibble(x)	(((x) >> 4) & 0xf)
#define	lonibble(x)	((x) & 0xf)

/* ************************************************************************* */

#include <std.h>
#include <sys.h>

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

/* Externals used by getopt */
extern int optind;
extern char *optarg;

/* Threshold setting on available memory */
extern uint16 Memthresh;

/* System clock - count of ticks since startup */
extern sint31 Clock;

/* Various useful standard error messages */
extern const char Nospace[];
extern char *Hostname;

/* Your system's end-of-line convention */
extern char Eol[];

/* Your system's temp directory */
extern char *Tmpdir;

extern uint16 Nfiles; /* Maximum number of open files */
extern uint16 Nsock;  /* Maximum number of open sockets */

extern void (*Gcollect[]) (int);
