
/* ************************************************************************* */
/*
 *	alloc.c
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
 *	This file contains the memory allocation functions.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 20:46:45  zhangn1
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

#include <mem.h>

/* ************************************************************************* */

/* Adapted from alloc routine in K&R; memory statistics and interrupt
 * protection added for use with net package. Must be used in place of
 * standard Turbo - C library routines because the latter check for stack / heap
 * collisions. This causes erroneous failures because process stacks are
 * allocated off the heap.
 */

/* ************************************************************************* */

static uint32 Memfail = 0;	/* Count of allocation failures */
static uint32 Allocs = 0;	/* Total allocations */
static uint32 Frees = 0;	/* Total frees */
static uint32 Invalid = 0;	/* Total calls to free with bad arg */
static uint32 Intalloc = 0;	/* Calls to malloc with ints disabled */
static uint32 Intfree = 0;	/* Calls to free with ints disabled */

static int    Memwait = 0;	/* Number of tasks waiting for memory */
static uint32 Yellows = 0;	/* Yellow alert garbage collections */
static uint32 Reds = 0;		/* Red alert garbage collections */
       uint32 Availmem = 0;	/* Heap memory, ABLKSIZE units */
static uint32 Morecores = 0;

static uint32 Sizes[16] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0
};

/* ************************************************************************* */

const struct cmds Memcmds[] = {
	{"peek",		dopeek,				0,	2,	"<addr> [count]"},
	{"poke",		dopoke,				0,	3,	"<addr> <byte> [byte(s)]"},
	{"show",		dostat,				0,	0,	""},
	{"status",		dostat,				0,	0,	""},
	{"thresh",		dothresh,			0,	0,	"[bytes]"},
	{NULLCHAR},
};

/* ************************************************************************* */

union header {
	struct {
		union header HUGE *ptr;
		uint32 size;
	} s;
	sint31 l[2];
};

/* ************************************************************************* */

typedef union header HEADER;
#define	NULLHDR	(HEADER HUGE *)NULL
static HEADER HUGE * morecore (size_t nu);
void HUGE * sbrk (sint15 size);

#define	ABLKSIZE	(sizeof (HEADER))

static HEADER Base;
static HEADER HUGE *Allocp = NULLHDR;
static uint32 Heapsize;

/* ************************************************************************* */

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

ENTRY void
alloc_init (void)
{
	Memwait = 0;
	Yellows = 0;	/* Yellow alert garbage collections */
	Reds = 0;		/* Red alert garbage collections */
}

/* ************************************************************************* */

/* ************************************************************************* */

/* ************************************************************************* */

/* ************************************************************************* */

/* ************************************************************************* */

/* Version of malloc() that waits if necessary for memory to become available */
ENTRY void *
mallocw (size_t nb)
{
	register void *p;

	if (nb == 0) {
		return 0;
	}

	while ((p = malloc (nb)) == NULL) {
		Memwait++;

		if ((Memwait % 100) == 0) {
			sys_puts ("mallocw() - Waiting for ");
			sys_puts (Curproc->name);
			sys_puts ("\n");
		}
		pwait (NULL);
		Memwait--;
	}
	return p;
}

/* ************************************************************************* */

/* Version of calloc that waits if necessary for memory to become available */
ENTRY void *
callocw (size_t nelem, size_t size)
{
	register unsigned i;
	register char *cp;

	i = nelem * size;
	cp = (char *) mallocw (i);
	memset (cp, 0, i);
	return cp;
}

/* ************************************************************************* */

ENTRY int
availmem (void)
{
	return 0;
}

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

/* memory commands */
ENTRY int
domem (int argc, char *argv[], void *p)
{
	return subcmd (Memcmds, argc, argv, p);
}

/* ************************************************************************* */

/* ************************************************************************* */

LOCAL int
dopeek (int argc, char *argv[], void *p)
{
	uint32 pointer;
	uint16 count;
	uint32 repeat;
	volatile uint16 *word;
	int i, j;

	if (atoi32uh_err (argv[1], &pointer))
		return 1;

	if (argc > 2) {
		if (atoi16uh_err (argv[2], &count))
			return 1;
	}
	else
		count = 16;

	if (argc > 3) {
		if (atoi32uh_err (argv[3], &repeat))
			return 1;
	}
	else
		repeat = 1;

	while (repeat--) {
		word = (uint16 *) (pointer);

		for (j = count; j;) {
			printf ("%08lx: ", (uint32) word);
			for (i = 16; i;-- i) {
				printf ("%04x ", *word++);
				if (--j == 0)
					break;
			}
			printf ("\n");
		}
		fflush (stdout);
	}
	return 0;
}

/* ************************************************************************* */

LOCAL int
dopoke (int argc, char *argv[], void *p)
{
	uint32 pointer;
	uint16 value;
	uint16 *word;

	if (atoi32uh_err (argv[1], &pointer))
		return 1;

	word = (uint16 *) ((sint31) pointer);

	while (argc > 2) {
		if (atoi16uh_err (argv[2], &value))
			return 1;
		printf ("Setting 0x%08lx to 0x%04x\n", pointer, (unsigned int)value);
		*word++= value;
	-- argc;
	++ argv;
	}
	return 0;
}

/* ************************************************************************* */

/* ************************************************************************* */

/* Print heap stats */
LOCAL int
dostat (int argc, char *argv[], void *envp)
{

	extern unsigned network_heap;
	struct MEM_Stat mem;

	if (MEM_stat (network_heap, &mem)) {
		printf("network heap size %u used %u maxfreeblocksize %u\n",
			   mem.size,
			   mem.used,
			   mem.length);
	}
	else {
		printf("network heap information not available\n");
	}

	iqstat ();
	printf("garbage collections yellow %lu red %lu\n",
		(long) Yellows,
		(long) Reds);
	return 0;
}

/* ************************************************************************* */

/* Print heap free list */
LOCAL int
dofreelist (int argc, char *argv[], void *envp)
{
	HEADER list[96];
	HEADER HUGE *p;
	int i = 0;
	int l = 0;
	int n = 0;

	/* grab first 96 entries */
	for (p = Base.s.ptr; p != (HEADER HUGE *) &Base && n < 96;
				p = p->s.ptr, n++) {
		list[n].s.ptr = p->s.ptr;
		list[n].s.size = p->s.size;
	}

	for (l = 0; l < n; l++) {
		printf("%5lx %6lu",
			(uint32) ((void *)list[l].s.ptr),
			list[l].s.size * ABLKSIZE);
		if (++i == 4) {
			i = 0;
			if (printf("\n") == EOF)
				return 0;
		} else
			printf(" | ");
	}
	if (i != 0)
		printf("\n");
	return 0;
}

/* ************************************************************************* */

LOCAL int
dosizes (int argc, char *argv[], void *p)
{
	int i;

	for (i = 0;i < 16;i += 4) {
		printf("N>=%5u:%7ld| N>=%5u:%7ld| N>=%5u:%7ld| N>=%5u:%7ld\n",
		 1 <<i, Sizes[i],	2 <<i, Sizes[i + 1],
		 4 <<i, Sizes[i + 2], 8 <<i, Sizes[i + 3]);
	}
	return 0;
}

/* ************************************************************************* */

LOCAL int
donibufs (int argc, char *argv[], void *p)
{
	return chg_int16u (&Nibufs_host,"Interface pool buffers",argc,argv);
}

/* ************************************************************************* */

LOCAL int
doibufsize (int argc, char *argv[], void *p)
{
	return chg_int16u (&Ibufsize,"Interface buffer size",argc,argv);
}

/* ************************************************************************* */

LOCAL int
dothresh (int argc, char *argv[], void *p)
{
	return chg_int16u (&Memthresh,"Free memory threshold (bytes)",argc,argv);
}

/* ************************************************************************* */

/* Background memory compactor, used when memory runs low */
ENTRY void
gcollect (int i, void *v1, void *v2)
{
	void (**fp) (int);
	int red;

	for (;;) {
		pwait (&Memthresh);
		/* If memory is low, collect some garbage. If memory is VERY
		 * low, invoke the garbage collection routines in "red" mode.
		 */
		switch (availmem ()) {
		case 0:
			continue;	/* All is well */
		case 1:
			red = 0;
			Yellows++;
			break;
		case 2:
			red = 1;
			Reds++;
			break;
		}
		for (fp = Gcollect;*fp != NULL;fp++)
			(**fp) (red);
	}
}
