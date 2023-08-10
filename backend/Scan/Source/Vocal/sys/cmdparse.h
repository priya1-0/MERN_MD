
/* ************************************************************************* */
/*
 *	cmdparse.h
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

#ifndef _SYS_CMDPARSE_H
#define _SYS_CMDPARSE_H

#define	NARG		20	/* Max number of args to commands */

struct cmds {
	char *name;		/* Name of command */
	int (*func) (int argc, char *argv[], void *p);
				/* Function to execute command */
	int stksize;		/* Size of stack if subprocess, 0 if synch */
	int  argcmin;		/* Minimum number of args */
	char *argc_errmsg;	/* Message to print if insufficient args */
};

#define IFACECMD_EXIST		0x1
#define IFACECMD_SHOW		0x2
#define IFACECMD_ATTACH		0x4
#define IFACECMD_ADD		0x8
#define IFACECMD_DEVICE		0x10
#define IFACECMD_CIRCUIT	0x20
#define IFACECMD_ASYNC		0x40
#define IFACECMD_SYNC		0x80
#define IFACECMD_PPP		0x100
#define IFACECMD_SLIP		0x200
#define IFACECMD_MODEM		0x400
#define IFACECMD_DECIDE		0x800
#define IFACECMD_MDM		0x1000

/* In commands.c */
extern const struct cmds far Cmds[];
extern const struct cmds far Restcmds[];

extern const struct cmds Debugoutputcmds[];

#endif /* _SYS_CMDPARSE_H */
