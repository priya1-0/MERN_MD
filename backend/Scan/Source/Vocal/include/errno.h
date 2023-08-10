
/* ************************************************************************* */
/*
 *	errno.h
 *
 *	(C) 1994 - 2006 VOCAL Technologies, Ltd.
 *
 *	ALL RIGHTS RESERVED.  PROPRIETARY AND CONFIDENTIAL.
 *
 *	VOCAL Technologies, Ltd.
 *	90A John Muir Drive.
 *	Buffalo, NY  14228
 *
 *	Product:	MASTER
 *
 *	Module:		INCLUDE
 *
 *	This file defines additional errno values for various compilers
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 19:50:34  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _INCLUDE_ERRNO_H
#define _INCLUDE_ERRNO_H

/* ************************************************************************* */
/* compiler specific errno addons here */
/* ************************************************************************* */

#define EDOM	1
#define ERANGE	2
#define ENOENT	3
#define EFPOS	5
#define EILSEQ	6

#define EMFILE	6		/* IO failure */
#define EBADF	6		/* IO failure */
#define EFAULT	5		/* invalid parameter for device */
#define EINVAL	5		/* invalid parameter for device */

#define ENOMEM	10
#define ENOSPC	11
#define EACCES	12

/* ************************************************************************* */

#endif /* _INCLUDE_ERRNO_H */
