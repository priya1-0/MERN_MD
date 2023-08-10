
/* ************************************************************************* */
/*
 *	mbuf.h
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

#ifndef _SYS_MBUF_H
#define _SYS_MBUF_H

#define IBUF_HEADER	100	/* extra space for later headers (pushdown)*/

/* Basic message buffer structure */
struct mbuf {
	struct mbuf *next;	/* Links mbufs belonging to single packets */
	struct mbuf *qnext;	/* Links packets on queues */
	struct mbuf *dup;	/* Pointer to duplicated mbuf */
	sint15 refcnt;		/* Reference count (by dup)*/

	uint16 size;		/* # bytes in buffer area */
	uint16 cnt;		/* # bytes used from data to end */

	uint16 b_type;		/* type of buffer */
	uint16 priority;	/* pseudo type of service for queuing */
#define MQP_NORMAL	0
#define MQP_FAST	0x4000
#define MQP_HIGHEST	0x7fff

	uint16 flags;		/* Misc bits */
#define MBUF_IBUF		0x0001	/* mbuf is an interface buffer */
#define MBUF_LOCAL		0x0002	/* mbuf is from local host */
#define MBUF_ETHERNET	0x0004	/* mbuf is in special ethernet memory */

#define MBUF_VOICE		0x0010	/* mbuf contains real-time voice */
#define MBUF_AUDIO		0x0020	/* mbuf contains real-time audio */
#define MBUF_VIDEO		0x0030	/* mbuf contains real-time video */

#define MBUF_DEALLOCATED	0x0100	/* mbuf is not currently allocated */

	char *data;		/* Active working pointers */

	uint32 alloc_time;	/* Clock time of allocation */

	char *file;			/* debug */
	int line;			/* debug */

	char *freefile;			/* debug */
	int freeline;			/* debug */

	uint32 ibuf_alloc_num;			/* debug */
};

#define	NULLBUF	(struct mbuf *)0
#define	NULLBUFP (struct mbuf **)0

#define	PULLCHAR(bpp)\
 ((bpp) != NULL && (*bpp) != NULLBUF && (*bpp)->cnt > 1 ? \
 ((*bpp)->cnt--, uchar (*(*bpp)->data++)) : pullchar (bpp))

/* How many bytes are available to push down in this physical mbuf. */
#define MBUF_PRE(bp)	((bp)->data - (char *)((bp) + 1))
/* How much room is on the end of this physical mbuf. */
#define MBUF_POST(bp)	((char *)((bp) + 1) + (bp)->size - (bp)->data - (bp)->cnt)

extern uint16 Ibufsize; 	/* Size of interrupt buffers to allocate */
extern uint16 Nibufs_host;	/* # buffers for host use */

extern uint16 Nibufs_iface;	/* # buffers for iface use */
extern uint16 Nibufs_current;	/* # buffers actually allocated */

#define AUDIT(bp)       audit(bp,__FILE__,__LINE__)

#endif /* _SYS_MBUF_H */
