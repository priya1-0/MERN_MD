
/* ************************************************************************* */
/*
 *	mbuf.c
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
 *	This file contains the mbuf (message buffer) primitives.
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
#include "dev/enet.h"

/* ************************************************************************* */

/* Interface/Interrupt buffer pool */
       uint16 Nibufs_iface = 0;
       uint16 Nibufs_current = 0;
static uint16 Intqlen = 0L;		/* Number of free mbufs on Intq */

#define IBUF_SIZE	(IBUFSIZE + IBUF_HEADER + sizeof(struct mbuf))
#define NUM_IBUF	((0xffff / IBUF_SIZE) - 1)

#pragma DATA_SECTION (IntqHeap, ".sect_mbuf")

static uint32 IntqHeap[NUM_IBUF][IBUF_SIZE/2]; /* declare as uint32 array to force proper allignment */

static struct mbuf *Intq = NULLBUF;	/* Mbuf pool for interface handlers */

static uint32 IbufAllocs = 0L;
static uint32 IbufFrees = 0L;
static uint32 IbufFail = 0L;

static uint32 MbufAllocs = 0L;
static uint32 MbufFrees = 0L;
static uint32 MbufFail = 0L;

static struct mbuf *Garbq = NULLBUF;	/* freed with interrupts off */
static uint32 GarbFrees = 0L;

static uint32 Pushdowns = 0L;		/* Total calls to pushdown() */
static uint32 Pushalloc = 0L;		/* Calls to pushdown that call malloc */

static int forced_free = 0;

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

ENTRY void
mbuf_init (void)
{
	int i;
	register struct mbuf *bp;

	Intq = NULLBUF;
	Ibufsize = IBUFSIZE;
	memset (IntqHeap, 0, sizeof (IntqHeap));
	for (i = 0; i < NUM_IBUF; i++) {
		bp = (struct mbuf*) &IntqHeap[i];
		/* Clear just the header portion */
		bp->size = (Ibufsize + IBUF_HEADER);
		bp->data = (char *) (bp + 1);
		bp->refcnt = 1;
		bp->flags |= MBUF_IBUF;
		bp->flags |= MBUF_DEALLOCATED;

		bp->next = Intq;
		bp->alloc_time = 0;
		Intq = bp;
	}
	Intqlen = i;
	Nibufs_current = i;

	IbufAllocs = 0L;
	IbufFrees = 0L;
	IbufFail = 0L;

	MbufAllocs = 0L;
	MbufFrees = 0L;
	MbufFail = 0L;

	Garbq = NULLBUF;	/* freed with interrupts off */
	GarbFrees = 0L;

	Pushdowns = 0L;		/* Total calls to pushdown() */
	Pushalloc = 0L;		/* Calls to pushdown that call malloc */
}

/* ************************************************************************* */

/* {WAS} refresh the interrupt/interface buffer queue.
 * Free up all the buffers that were returned during interrupt time,
 * to avoid interrupt problems in the memory handlers.
 * Fill the interrupt / interface memory pool so that buffers can be grabbed
 * and freed quickly in the interface handlers.
 */
static uint32 old_alloc = 0x7fffffffL;
ENTRY void
refiq (void)
{
	int i, j;
	register struct mbuf *bp;

	/* Empty the garbage */
	if (Garbq != NULLBUF) {
		network_nested_interrupt_disable ();
		bp = Garbq;
		Garbq = NULLBUF;
		network_nested_interrupt_restore ();
		free_p (bp);
	}

	/* Search for very old ibufs to be returned to the pool */
	old_alloc = 0x7fffffffL;
	for (i = 0; i < NUM_IBUF; i++) {
		bp = (struct mbuf*) &IntqHeap[i];

		if (bp->flags & MBUF_IBUF == 0) {
			bp->flags |= MBUF_IBUF;
			printf("\n\n ************* flags wrong in ibuf %d ************* \n\n",i);
		}

		if (!(bp->flags & MBUF_ETHERNET)) {	/* Must not deallocate special hardware held MBUFs */
			if (bp->alloc_time < old_alloc && bp->alloc_time != 0) {
				old_alloc = bp->alloc_time;
				if (secclock () - old_alloc > 100) {
					printf("\n\n ************* removing IBUF %d ************* \n",i);
					printf("allocation %lu\n",(long) bp->ibuf_alloc_num);
					printf("old_alloc %ld, current time %ld\n", (long) old_alloc, (long) secclock ());
					printf("flags\n", bp->flags);

					for (j = 0;j < 40; j++) {
						char *dpt = bp->data;
						printf("%04x  ",dpt[j]);
					}
					printf("\n");

					free_mbuf(bp);
					forced_free++;
				}
			}
		}
	}

	if (old_alloc == 0x7fffffffL) {
		old_alloc = 0;
	}

	return;
}

/* ************************************************************************* */

/* Print the queue statistics. */
ENTRY void
iqstat (void)
{
	printf("mbuf allocs %lu frees %lu (diff %ld) fails %lu\n",
		(long) MbufAllocs,
		(long) MbufFrees,
		(long) (MbufAllocs - MbufFrees),
		(long) MbufFail);
	printf("pushdowns %lu to malloc %lu\n",
		(long) Pushdowns,
		(long) Pushalloc);
	printf("ibuf allocs %lu frees %lu (diff %ld) fails %lu GarbFrees %lu\n",
		(long) IbufAllocs,
		(long) IbufFrees,
		(long) (IbufAllocs - IbufFrees),
		(long) IbufFail,
		(long) GarbFrees);
	printf("Intqlen %u Ibufsize %u\n",
		Intqlen,
		Ibufsize);

	/* -dcs- start of debug */
	printf("old_alloc %ld, current time %ld\n",
		   (long) old_alloc,
		  secclock ());

	printf("forced free %d\n",
			 forced_free);
	/* -dcs- end of debug */
}

/* ************************************************************************* */

/* Allocate mbuf from Intq.
 * Can be called with interrupts enabled or disabled.
 */

ENTRY struct mbuf *
alloc_ibuf (uint16 size, sint15 adjust)
{

	register struct mbuf *bp;

	network_nested_interrupt_disable ();
	if (size + IBUF_HEADER > Ibufsize || Intq == NULLBUF) {
		IbufFail++;
		network_nested_interrupt_restore ();
		return NULLBUF;
	}
	bp = Intq;
	Intq = bp->next;
	Intqlen--;
	IbufAllocs++;
	network_nested_interrupt_restore ();

	/* set up mbuf header */
	bp->next = NULLBUF;
	bp->qnext = NULLBUF;
	bp->data = (char *) (bp + 1) + adjust + IBUF_HEADER;
	bp->cnt = 0;
	bp->priority = 0;

	bp->flags &= ~MBUF_DEALLOCATED;

	bp->alloc_time = secclock ();

	bp->ibuf_alloc_num = IbufAllocs;
	/* -dcs- end of debug */

	return bp;
}

/* ************************************************************************* */

/* Allocate mbuf with associated buffer of 'size' bytes. If interrupts
 * are enabled, use the regular heap. All other calls should be using
 * alloc_ibuf instead.
 */
ENTRY struct mbuf *
alloc_mbuf (uint16 size)
{
	register struct mbuf *bp;

/* Allocate additional space and attempt to allign on a 32-bit address boundary */
#define MBUF_HEADER (IBUF_HEADER + ETHERLEN + IPHDRLEN + TCPLEN + 4)

	if (!network_nested_interrupt_read_depth ()) {
		/* Interrupts are enabled, use the heap normally */
		if (size) {
			size += MBUF_HEADER;
		}
		bp = (struct mbuf *) malloc ((unsigned) (size + sizeof (struct mbuf)));
		if (bp == NULLBUF) {
			MbufFail++;
			return NULLBUF;
		}
		/* Clear just the header portion */
		memset ((char *) bp, 0, sizeof (struct mbuf));
		if ((bp->size = size) != 0) {
			bp->data = ((char *) (bp + 1)) + MBUF_HEADER;
		}
		bp->refcnt = 1;
		bp->alloc_time = 0xffffffffL;
		bp->flags &= ~MBUF_DEALLOCATED;
		MbufAllocs++;
	} else {
		bp = NULLBUF;	/* should never happen again */
	}
	return bp;
}

/* ************************************************************************* */

/* Allocate mbuf, waiting if memory is unavailable */
ENTRY struct mbuf *
ambufw (uint16 size)
{
	register struct mbuf *bp;

	bp = (struct mbuf *) mallocw ((unsigned) (size + sizeof (struct mbuf)));

	/* Clear just the header portion */
	memset ((char *) bp, 0, sizeof (struct mbuf));
	if ((bp->size = size) != 0)
		bp->data = (char *) (bp + 1);
	bp->refcnt = 1;
	bp->alloc_time = 0xffffffffL;
	bp->flags &= ~MBUF_DEALLOCATED;
	MbufAllocs++;
	return bp;
}

/* ************************************************************************* */

/* Decrement the reference pointer in an mbuf. If it goes to zero,
 * free all resources associated with mbuf.
 * Return pointer to next mbuf in packet chain
 */
ENTRY struct mbuf *
free_mbuf (register struct mbuf *bp)
{
	struct mbuf *bpnext;
	if (bp == NULLBUF)
		return NULLBUF;

	bpnext = bp->next;
	if (bp->dup != NULLBUF) {
		free_mbuf(bp->dup);	/* Follow indirection */
		bp->dup = NULLBUF;
	}
	/* Decrement reference count. If it has gone to zero, free it. */
	if (--bp->refcnt <= 0) {

		bp->flags &= ~MBUF_ETHERNET;
		if (bp->flags & MBUF_IBUF) {
			network_nested_interrupt_disable ();
			bp->refcnt = 1; /* Adjust */
			bp->next = Intq;
			bp->alloc_time = 0;
			bp->flags |= MBUF_DEALLOCATED;

			Intq = bp;
			Intqlen++;
			IbufFrees++;
			network_nested_interrupt_restore ();
		} else {
			free ((char *) bp);
			MbufFrees++;
		}
	}
	return bpnext;
}

/* ************************************************************************* */

/* Free packet (a chain of mbufs). Return pointer to next packet on queue,
 * if any
 * DLW Packets are linked via the qnext field.	The mbufs that make up a single
 * packet are linked by the next field.
 */
ENTRY struct mbuf *
free_p (register struct mbuf *bp)
{
	register struct mbuf *qbp;

	if (bp == NULLBUF)
		return NULLBUF;
	qbp = bp->qnext;
	while (bp != NULLBUF) {

		bp = free_mbuf (bp);
	}
	return qbp;
}

/* ************************************************************************* */

/* Free entire queue of packets (of mbufs) */
ENTRY void
free_q (struct mbuf **q)
{
	register struct mbuf *bp;

	while ((bp = dequeue (q)) != NULLBUF) {
		free_p (bp);
	}
}

/* ************************************************************************* */

/* Count up the total number of bytes in a packet */
ENTRY uint16
len_p (register struct mbuf *bp)
{
	register uint16 cnt = 0;

	while (bp != NULLBUF) {
		cnt += bp->cnt;

		bp = bp->next;
	}
	return cnt;
}

/* ************************************************************************* */

/* Count up the number of packets in a queue */
ENTRY uint16
len_q (register struct mbuf *bp)
{
	register uint16 cnt;

	for (cnt = 0;bp != NULLBUF;cnt++, bp = bp->qnext)
	;
	return cnt;
}

/* ************************************************************************* */

/* Trim mbuf to specified length by lopping off end */
/* DLW This really trims a packet, not an mbuf.  If need be, whole mbufs are
 * lopped off the packet, no partial mbufs are freed. */
ENTRY void
trim_mbuf (struct mbuf **bpp, uint16 length)
{
	register uint16 tot = 0;
	register struct mbuf *bp;

	if (bpp == NULLBUFP || *bpp == NULLBUF)
		return;	/* Nothing to trim */

	if (length == 0) {
		/* Toss the whole thing */
		free_p (*bpp);
		*bpp = NULLBUF;
		return;
	}
	/* Find the point at which to trim. If length is greater than
	 * the packet, we'll just fall through without doing anything
	 */
	for (bp = *bpp; bp != NULLBUF; bp = bp->next) {
		if (tot + bp->cnt < length) {
			tot += bp->cnt;
		} else {
			/* Cut here */
			bp->cnt = length - tot;
			free_p (bp->next);
			bp->next = NULLBUF;
			break;
		}
	}
}

/* ************************************************************************* */

/* Duplicate/enqueue/dequeue operations based on mbufs */

/* Duplicate first 'cnt' bytes of packet starting at 'offset'.
 * This is done without copying data; only the headers are duplicated,
 * but without data segments of their own. The pointers are set up to
 * share the data segments of the original copy. The return pointer is
 * passed back through the first argument, and the return value is the
 * number of bytes actually duplicated.
 */
ENTRY uint16
dup_p (struct mbuf **hp, struct mbuf *bp, uint16 offset, uint16 cnt)
{
	register struct mbuf *cp;
	uint16 tot;

	if (cnt == 0 || bp == NULLBUF || hp == NULLBUFP) {
		if (hp != NULLBUFP)
			*hp = NULLBUF;
		return 0;
	}
	/* Just allocate the header. */
	if ((*hp = cp = alloc_mbuf (0)) == NULLBUF) {
		return 0;
	}
	/* Skip over leading mbufs that are smaller than the offset */
	while (bp != NULLBUF && bp->cnt <= offset) {
		offset -= bp->cnt;
		bp = bp->next;
	}
	if (bp == NULLBUF) {
		free_mbuf (cp);
		*hp = NULLBUF;
		return 0;	/* Offset was too big */
	}
	tot = 0;
	/* This handles data that is fragmented accross mbufs.
	 * It makes a list of headers pointing to each fragment. */
	for (;;) {
		/* Make sure we get the original, "real" buffer (i.e. handle the
		 * case of duping a dupe)
		 * This also insures that dupes only go one deep.
		 */
		if (bp->dup != NULLBUF)
			cp->dup = bp->dup;
		else
			cp->dup = bp;

		/* Increment the duplicated buffer's reference count */
		cp->dup->refcnt++;

		cp->data = bp->data + offset;
		cp->cnt = min (cnt, bp->cnt - offset);
		offset = 0;
		cnt -= cp->cnt;
		tot += cp->cnt;
		bp = bp->next;
		if (cnt == 0 || bp == NULLBUF || (cp->next = alloc_mbuf (0)) == NULLBUF)
			break;
		cp = cp->next;
	}
	return tot;
}

/* ************************************************************************* */

/* Copy first 'cnt' bytes of packet into a new, single mbuf */
ENTRY struct mbuf *
copy_p (struct mbuf *bp, uint16 cnt)
{
	register struct mbuf *cp;
	register char *wp;
	register uint16 n;

	if (cnt == 0
	 ||  bp == NULLBUF
	 ||  (cp = alloc_ibuf (cnt, - IBUF_HEADER)) == NULLBUF)
		return NULLBUF;
	wp = cp->data;
	while (cnt != 0 && bp != NULLBUF) {
		n = min (cnt, bp->cnt);
		memcpy (wp, bp->data, n);
		wp += n;
		cp->cnt += n;
		cnt -= n;
		bp = bp->next;
	}
	return cp;
}

/* ************************************************************************* */

/* Copy and delete "cnt" bytes from beginning of packet. Return number of
 * bytes actually pulled off
 */
ENTRY uint16
pullup (struct mbuf **bph, char *buf, uint16 cnt)
{
	register struct mbuf *bp;
	uint16 n, tot;

	tot = 0;
	if (bph == NULLBUFP) {
		return 0;
	}
	while (cnt != 0 && (bp = *bph) != NULLBUF) {
		n = min (cnt, bp->cnt);
		if (buf != NULLCHAR) {
			if (n == 1)	/* Common case optimization */
				*buf = *bp->data;
			else if (n > 1)
				memcpy (buf, bp->data, n);
			buf += n;
		}
		tot += n;
		cnt -= n;
		bp->data += n;
		bp->cnt -= n;
		if (bp->cnt == 0) {
			/* If this is the last mbuf of a packet but there
			 * are others on the queue, return a pointer to
			 * the next on the queue. This allows pullups to
			 * to work on a packet queue
			 */
			if (bp->next == NULLBUF) {
				*bph = bp->qnext;
				free_mbuf (bp);
			} else {
				bp->next->qnext = bp->qnext;
				*bph = free_mbuf (bp);
			}
		}
	}
	return tot;
}

/* ************************************************************************* */

/* Copy and delete "cnt" bytes from beginning of packet and pack into return buffer.
 * Return number of bytes actually pulled off
 */
ENTRY uint16
pullup_packed (struct mbuf **bph, uint16 *buf, uint16 cnt)
{
	register struct mbuf *bp;
	uint16 n, tot;
	int odd_flag = 0;
	uint16 temp;

	tot = 0;
	if (bph == NULLBUFP) {
		return 0;
	}
	while (cnt != 0 && (bp = *bph) != NULLBUF) {
		n = min (cnt, bp->cnt);

		if (buf != (uint16*)0) {
			char * source = bp->data;
			sint15 byte_count = n;

			while (byte_count--) {
				if (odd_flag) {
					temp |= uchar (*source++);
					*buf++ = temp;
				} else {
					temp = uchar (*source++);
					temp <<= 8;
				}
				odd_flag ^= 1;
			}
		}
		tot += n;
		cnt -= n;
		bp->data += n;
		bp->cnt -= n;
		if (bp->cnt == 0) {
			/* If this is the last mbuf of a packet but there
			 * are others on the queue, return a pointer to
			 * the next on the queue. This allows pullups to
			 * to work on a packet queue
			 */
			if (bp->next == NULLBUF) {
				*bph = bp->qnext;
				free_mbuf (bp);
			} else {
				bp->next->qnext = bp->qnext;
				*bph = free_mbuf (bp);
			}
		}
	}
	if (odd_flag) {
		*buf = temp;
	}
	return tot;
}

/* ************************************************************************* */

/* Insert specified amount of contiguous new space at the BEGINNING of an
 * mbuf chain. If enough space is available in the first mbuf, no new space
 * is allocated. Otherwise a mbuf of the appropriate size is allocated and
 * tacked on the front of the chain.
 *
 * This operation is the logical inverse of pullup (), hence the name.
 */
ENTRY void
pushdown (struct mbuf **bph, uint16 size)
{
	register struct mbuf *bp = NULLBUF;
	register struct mbuf *nbp;

	if (bph == NULLBUFP){
		return;
	}

	Pushdowns++;
	/* Check that bp is real, that it hasn't been duplicated, and
	 * that it itself isn't a duplicate before checking to see if
	 * there's enough space at its front.
	 */
	if ((bp = *bph) != NULLBUF
	  && bp->refcnt == 1
	  && bp->dup == NULLBUF
	  && bp->data - (char *) (bp + 1) >= size) {
		/* No need to alloc new mbuf, just adjust this one */
		bp->data -= size;
		bp->cnt += size;
	} else {
		/* Make enough space so that the next pushdown won't
		 * require a new buffer to be allocated.
		 */
		nbp = ambufw (max (size, IBUF_HEADER));
		nbp->next = bp;
		nbp->data += nbp->size - size;
		nbp->cnt = size;
		nbp->b_type = bp->b_type;
		nbp->priority = bp->priority;
		*bph = nbp;
		Pushalloc++;
	}
}

/* ************************************************************************* */

/* Tack specified amount of contiguous new space at the END of an
 * mbuf chain. If enough space is available in the last mbuf, no new space
 * is allocated. Otherwise a mbuf of the appropriate size is allocated and
 * tacked on the end of the chain. */
ENTRY uint8 *
tackdown (struct mbuf **bph, uint16 size)
{
	register struct mbuf *bp;
	register struct mbuf *nbp;
	uint8 *retval;

	if (bph == NULLBUFP) {
		return (uint8 *) NULLCHAR;
	}

	if ((bp = *bph) != NULLBUF) {
		/* Find the last buffer in the chain. */
		while (bp->next != NULLBUF)
			bp = bp->next;
	}

	/* Check that bp is real, that it hasn't been duplicated, and
	 * that it itself isn't a duplicate before checking to see if
	 * there's enough space at its end.
	 */
	if ((bp = *bph) != NULLBUF
	  && bp->refcnt == 1
	  && bp->dup == NULLBUF
	  && ((char *) (bp + 1) + bp->size) - (bp->data + bp->cnt) >= size) {
		/* No need to alloc new mbuf, just adjust this one */
		retval = (uint8 *) (bp->data + bp->cnt);
		bp->cnt += size;
	}
	else {
		/* Make enough space so that the next tackdown won't
		 * require a new buffer to be allocated. */
		nbp = ambufw (max (size, IBUF_HEADER));
		nbp->cnt = size;

		if (bp == NULLBUF) {
			bp = nbp;
		}
		else {
			bp->next = nbp;
			nbp->b_type = bp->b_type;
			nbp->priority = bp->priority;
		}
		*bph = bp;
		retval = (uint8 *) nbp->data;
	}

	return retval;
}

/* ************************************************************************* */

/* Append mbuf to end of mbuf chain */
ENTRY void
append (struct mbuf **bph, struct mbuf *bp)
{
	register struct mbuf *p;

	if (bph == NULLBUFP || bp == NULLBUF)
		return;
	if (*bph == NULLBUF) {
		/* First one on chain */
		*bph = bp;
	} else {
		for (p = *bph; p->next != NULLBUF; p = p->next)
		;
		p->next = bp;
	}
}

/* ************************************************************************* */

/* Append packet to end of packet queue */
ENTRY void
enqueue (struct mbuf **q, struct mbuf *bp)
{
	register struct mbuf *p;

	if (q == NULLBUFP || bp == NULLBUF)
		return;
	network_nested_interrupt_disable ();
	if (*q == NULLBUF) {
		/* List is empty, stick at front */
		*q = bp;
	} else {
		for (p = *q; p->qnext != NULLBUF; p = p->qnext)
		;
		p->qnext = bp;
	}
	network_nested_interrupt_restore ();
	/* Tell one process that the queue has grown. */

	psignal (q, 1);
}

/* ************************************************************************* */

/* Unlink a packet from the head of the queue */
ENTRY struct mbuf *
dequeue (register struct mbuf **q)
{
	register struct mbuf *bp;

	if (q == NULLBUFP)
		return NULLBUF;
	network_nested_interrupt_disable ();
	if ((bp = *q) != NULLBUF) {
		*q = bp->qnext;
		bp->qnext = NULLBUF;
	}
	network_nested_interrupt_restore ();
	return bp;
}

/* ************************************************************************* */

/* Copy user data into an mbuf */
ENTRY struct mbuf *
qdata (char *data, uint16 cnt)
{
	register struct mbuf *bp;

	bp = ambufw (cnt + IBUF_HEADER + IPHDRLEN + TCPLEN);
	bp->data += (IBUF_HEADER + IPHDRLEN + TCPLEN);
	memcpy (bp->data, data, cnt);
	bp->cnt = cnt;
	return bp;
}

/* ************************************************************************* */

/* Copy mbuf data into user buffer */
ENTRY uint16
dqdata (struct mbuf *bp, char *buf, uint16 cnt)
{
	uint16 n, tot;
	struct mbuf *bp1;

	if (buf == NULLCHAR)
		return 0;

	tot = 0;
	for (bp1 = bp;bp1 != NULLBUF; bp1 = bp1->next) {
		n = min (bp1->cnt, cnt);
		memcpy (buf, bp1->data, n);
		cnt -= n;
		buf += n;
		tot += n;
	}
	free_p (bp);
	return tot;
}

/* ************************************************************************* */

/* Pull a 32-bit integer in host order from buffer in network byte order.
 * On error, return 0. Note that this is indistinguishable from a normal
 * return.
 */
ENTRY uint32
pull32 (struct mbuf **bpp)
{
	char buf[4];

	if (pullup (bpp, buf, 4) != 4) {
		/* Return zero if insufficient buffer */
		return 0;
	}
	return get32 (buf);
}

/* ************************************************************************* */

/* Pull a 16-bit integer in host order from buffer in network byte order.
 * Return -1 on error
 */
ENTRY sint31
pull16 (struct mbuf **bpp)
{
	char buf[2];

	if (pullup (bpp, buf, 2) != 2) {
		return -1;		/* Nothing left */
	}
	return get16 (buf);
}

/* ************************************************************************* */

/* Pull single character from mbuf */
ENTRY sint15
pullchar (struct mbuf **bpp)
{
	char c;
	unsigned char uc;

	if (pullup (bpp, &c, 1) != 1) {
		return -1;		/* Nothing left */
	}
	uc = uchar(c);
	return (int) uc;
}

/* ************************************************************************* */

/* DLW Write out a packet. */
ENTRY int
write_p (FILE *fp, struct mbuf *bp)
{
	while (bp != NULLBUF) {
		if (fwrite (bp->data, 1, bp->cnt, fp) != bp->cnt)
			return -1;
		bp = bp->next;
	}
	return 0;
}

/* ************************************************************************* */

/* Reclaim unused space in a mbuf chain. If the argument is a chain of mbufs
 * and / or it appears to have wasted space, copy it to a single new mbuf and
 * free the old mbuf (s) . But refuse to move mbufs that merely
 * reference other mbufs, or that have other headers referencing them.
 *
 * Be extremely careful that there aren't any other pointers to
 *(or into) this mbuf, since we have no way of detecting them here.
 * This function is meant to be called only when free memory is in
 * short supply.
 */
ENTRY void
mbuf_crunch (struct mbuf **bpp)
{
	register struct mbuf *bp = *bpp;
	struct mbuf *nbp;

	if (bp->refcnt > 1 || bp->dup != NULLBUF) {
		/* Can't crunch, there are other refs */
		return;
	}
	if (bp->next == NULLBUF && bp->cnt == bp->size) {
		/* Nothing to be gained by crunching */
		return;
	}
	if ((nbp = copy_p (bp, len_p (bp))) == NULLBUF) {
		/* Copy failed due to lack of (contiguous) space */
		return;
	}
	nbp->qnext = bp->qnext;
	free_p (bp);
	*bpp = nbp;
}
