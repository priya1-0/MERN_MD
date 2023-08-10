
/* ************************************************************************* */
/*
 *	netuser.h
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
 *	This file contains the global declarations for the NET module.
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

#ifndef	_NET_NETUSER_H
#define	_NET_NETUSER_H

/* Global structures and constants needed by an Internet user process */

#define	NCONN	20		/* Maximum number of open network connections */

extern int Net_error;	/* Error return code */
extern char Inet_eol[];

#define	NONE		0	/* No error */
#define	CON_EXISTS	1	/* Connection already exists */
#define	NO_CONN		2	/* Connection does not exist */
#define	CON_CLOS	3	/* Connection closing */
#define	NO_MEM		4	/* No memory for TCB creation */
#define	WOULDBLK	5	/* Would block */
#define	NOPROTO		6	/* Protocol or mode not supported */
#define	INVALID		7	/* Invalid arguments */

#endif /* _NET_NETUSER_H */
