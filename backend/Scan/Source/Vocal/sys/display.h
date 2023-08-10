
/* ************************************************************************* */
/*
 *	display.h
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

#ifndef _SYS_DISPLAY_H
#define _SYS_DISPLAY_H

/* ************************************************************************* */

#define	MAXARGS	5

#define	NROWS	25
#define	NCOLS	80

/* ************************************************************************* */

struct display {
	unsigned cookie;	/* Magic cookie to detect bogus pointers */
#define	D_COOKIE	0xbeef
	int cols;	/* Screen width */
	int col;	/* cursor column, 0 to cols-1 */
	int savcol;	/* Saved cursor column */

	int rows;	/* Screen height */
	int row;	/* cursor row, 0 to rows-1 */
	int savrow;	/* Saved cursor row */
	int firstrow;	/* First row to be displayed when scrolled */

	int argi;	/* index to current entry in arg[] */
	int arg[MAXARGS];	/* numerical args to ANSI sequence */

	char attrib;	/* Current screen attribute */
	char state;	/* State of ANSI escape sequence FSM */
#define	NORMAL	0	/* No ANSI sequence in progress */
#define	ESCAPE	1	/* ESC char seen */
#define	ARG	2	/* ESC[ seen */

	int flags;	/* Status flags */
#define	DIRTY_SCREEN	1	/* Rewrite whole screen on next dupdate() */
#define	DIRTY_ROW	2	/* Rewrite current row */
#define	DIRTY_CURSOR	4	/* Cursor has moved */
#define	NOWRAP		8	/* Set if end-of-line wrapping is disabled */
#define	NOSCROL		16	/* Set if wrap-around scrolling is in use */
#define	INSERT_MODE	32	/* Insert mode active */

	char *buf;	/* Internal screen image */
};

#define	NULLDISP	(struct display *)0

/* ************************************************************************* */

/* ************************************************************************* */

#endif /* _SYS_DISPLAY_H */
