
/* ************************************************************************* */
/*
 *	config.h
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

#ifndef _LANSEND_CONFIG_H
#define _LANSEND_CONFIG_H

/* Software tuning parameters */
#define	MTHRESH		8192	/* Default memory threshold */
#define	NROWS		25	/* Number of rows on screen */
#define NHOST_IBUFS	10	/* Number of buffers the server itself needs. */

#define	IBUFSIZE	1700	/* Size of interrupt buffers */

#define QUICK_NAMES	10	/* Number of names for quick configuration */

#define NUSERS		5	/* How many users can be logged on at once. */

#endif /* _LANSEND_CONFIG_H */
