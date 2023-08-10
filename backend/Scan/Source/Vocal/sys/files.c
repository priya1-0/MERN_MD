
/* ************************************************************************* */
/*
 *	files.c
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
 *	System - dependent definitions of various files, spool directories, etc.
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

char * sys_errlist[1];

/* ************************************************************************* */

static char *rootdir = "";

char *Startup = "startup";		/* Initialization file */
char *Startup_bak = "startup.bak";	/* Backup initialization file */
char *Account = "account";		/* Account file */
char *Account_bak = "account.bak";	/* Backup account file */
char *Userfile = "users";		/* Authorized users and passwords */
char *Alias = "alias";			/* the alias file */
char *Dfile = "domain";			/* Domain cache */
char *Tmpfile = "";	 		/* Temporary file */
char Eol[] = "\r\n";
#define	SEPARATOR	"/"

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */
