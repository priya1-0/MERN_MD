
/* ************************************************************************* */
/*
 *	filesys.h
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
 *	This file contains the file system functions.
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

#ifndef _SYS_FILESYS_H
#define _SYS_FILESYS_H

#define	NSESSIONS	4	/* Number of interactive clients */
#define DEFNSOCK	20	/* Default number of sockets */

#define	DEFNFILES	12	/* Total number of available files */
#define FLASHFILES	12	/* Number of flash files */

#define FILE_SIZE	4000	/* Maximum file size in RAM file system */
#define FBLK_SIZE	1024	/* Allocated file block size in RAM file system */

#ifdef DO_LANSEND_FLASH_FILES
/* Define special segments for flash files */
#define FLASH_STORAGE		0x8000		/* Amount of flash storage provided */
#define EMBED_SEG_DATA 		0x00c0		/* Data segment used for temporary storage */

#ifdef DO_LANSEND_FLASH_BYTEWIDE
/* Location in byte wide flash */
#define EMBED_SEG_FLASH		0x5000          /* Flash segment */
#define EMBED_ADDR_FDS   	0x0000          /* Address of file descriptors in flash */
#else /* DO_LANSEND_FLASH_BYTEWIDE */
/* Location in word wide flash */
#define EMBED_SEG_FLASH		0x8000          /* Flash segment */
#define EMBED_ADDR_FDS   	0x0000          /* Address of file descriptors in flash */
#endif /* DO_LANSEND_FLASH_BYTEWIDE */
#endif /* DO_LANSEND_FLASH_FILES */

/* constants for file manipulations                                          */

#define  O_RDONLY    (0x0000) /* open for reading      */
#define  O_WRONLY    (0x0001) /* open for writing      */
#define  O_RDWR      (0x0002) /* open for read & write */
#define  O_APPEND    (0x0008) /* append on each write  */
#define  O_CREAT     (0x0200) /* open with file create */
#define  O_TRUNC     (0x0400) /* open with truncation  */
#define  O_BINARY    (0x8000) /* open in binary mode   */

#define MAX_FNAME 16

struct file_entry {
	char name[MAX_FNAME];
	sint15 use;
	sint15 mode;
	sint31 size;
	sint31 position;
	sint31 data;		/* TI 55x uses a "byte" pointer to packed data */
};

extern struct file_entry Fds[DEFNFILES];

struct fblk {
	struct fblk *next;
	uint16 data[FBLK_SIZE / 2];
};

#endif /* _SYS_FILESYS_H */
