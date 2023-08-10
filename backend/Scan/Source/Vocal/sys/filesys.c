
/* ************************************************************************* */
/*
 *	filesys.c
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
 *	This file contains the memory file system primitives.
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

#include "pump/pump.h"

#include "net/net.h"
#include "sys/sys.h"
#include "dev/dev.h"

#include "ip/ip.h"

#include "sys/local.h"

/* ************************************************************************* */

/* File descriptor structure array
 */
struct file_entry Fds[DEFNFILES];

/* Reference count table for open file descriptors */
uint16 Refcnt[DEFNFILES];

/* ************************************************************************* */

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

ENTRY void
filesys_init (void)
{
	int i;

	for (i = 0; i < DEFNFILES; i++) {
		memset (Fds[i].name, 0, MAX_FNAME);
		Fds[i].use = FALSE;
		Refcnt[i] = 0;
	}

	fbuf_init ();
}

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */
/*
 *	Move data from packed file memory to processor character format
 *
 */
ENTRY void
packed_data_read (void *dst, uint32 src, sint31 len)
{
	char *d = (char *) dst;
	uint16 *s;
	uint16 b, data;

	while (len--) {
		s = (uint16 *) (src >> 1);
		b = src & 1;

		data = *s;
		/* 0 for high byte, 1 for low byte */
		if (b) {
			*d++= (char) (data & 0xff);
		} else {
			*d++= (char) ((data >> 8) & 0xff);
		}
		src++;
	}
}

/* ************************************************************************* */
/*
 *	Move data to packed file memory from processor character format
 *
 */
ENTRY void
packed_data_write (uint32 dst, void *src, sint31 len)
{
	char *s = (char *) src;
	uint16 *d;
	uint16 b, data;

	while (len--) {
		d = (uint16 *) (dst >> 1);
		b = dst & 1;

		data = *d;
		/* 0 for high byte, 1 for low byte */
		if (b) {
			*d = (((uint16) (*s++)) & 0xff) | (data & 0xff00);
		} else {
			*d = ((((uint16) (*s++)) & 0xff) << 8) | (data & 0x00ff);
		}
		dst++;
	}
}

/* ************************************************************************* */
/*
 *	Move data from file memory to processor character format
 *
 */
ENTRY void
read_from_file_space (struct file_entry *fds, void *dst, sint31 len)
{
	char *d = (char *) dst;

	/* ********************************************************************* */

	/* ********************************************************************* */

	{
		sint31 current, offset, readcnt;
		uint32 src;
		struct fblk *blk;

		/* Find the starting block based on position */
		current = 0;
		if ((blk = (struct fblk *) fds->data) == NULL) {

			return;
		}
		do {
			if ((current + FBLK_SIZE) > fds->position) {
				break;
			}
			current += FBLK_SIZE;
			if (blk->next == NULL) {

				return;
			}
		} while (blk = blk->next);

		/* Transfer the first (partial) block of data */
		offset = fds->position - current;
		readcnt = min (len, (FBLK_SIZE - offset));

		src = (((uint32) &blk->data[0]) << 1) + offset;	/* Create byte pointer */

		packed_data_read (d, src, readcnt);
		d += readcnt;
		len -= readcnt;

		/* Transfer subsequent blocks of data */
		while (len) {
			if ((blk = blk->next) == NULL) {
				break;
			}
			readcnt = min (len, FBLK_SIZE);

			src = ((uint32) blk->data) << 1;	/* Create byte pointer */
			packed_data_read (d, src, readcnt);
			d += readcnt;
			len -= readcnt;
		}
	}
	return;
}

/* ************************************************************************* */
/*
 *	Move data to file memory from processor character format
 *
 */
ENTRY void
write_to_file_space (struct file_entry *fds, void *src, sint31 len)
{
	char *s = (char *) src;

	/* ********************************************************************* */

	{
		sint31 current, offset, writecnt;
		uint32 dst;
		struct fblk *blk;

		/* Find the starting block based on position */
		current = 0;
		if ((blk =  (struct fblk *) fds->data) == NULL) {
			if ((blk = alloc_fblk ()) == NULL) {
				return;
			}

			fds->data = (uint32) blk;
		}
		do {
			if ((current + FBLK_SIZE) > fds->position) {
				break;
			}
			if (blk->next == NULL) {
				break;
			}
			current += FBLK_SIZE;
		} while (blk = blk->next);

		if ((current + FBLK_SIZE) > fds->position) {
			/* Transfer the first (partial) block of data */
			offset = fds->position - current;
			writecnt = min (len, (FBLK_SIZE - offset));
			dst = (((uint32) blk->data) << 1) + offset;	/* Create byte pointer */

			packed_data_write (dst, s, writecnt);
			s += writecnt;
			len -= writecnt;
		}

		/* Transfer subsequent blocks of data */
		while (len) {
			if (blk->next == NULL) {
				if ((blk->next = alloc_fblk ()) == NULL) {
					break;
				}
			}
			blk = blk->next;
			writecnt = min (len, FBLK_SIZE);
			dst = ((uint32) blk->data) << 1;	/* Create byte pointer */
			packed_data_write (dst, s, writecnt);
			s += writecnt;
			len -= writecnt;
		}
	}
	return;
}

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* Free file memory if not in flash
 */
LOCAL void
filefree (uint32 ptr)
{

	free_fblk ((struct fblk  *) ptr);
}

/* ************************************************************************* */

ENTRY int
_creat (const char *file, int mode)
{
	int fd;

	if (*file == '/') file++;

	/* Truncate file being re-created if it already exists */
	for (fd = 0; fd < Nfiles; fd++) {

		if (Fds[fd].use && (strcmp (Fds[fd].name, file) == 0)) {
			if (Refcnt[fd] != 0) {
				/* File is open, so it can't be created. */
				errno = EACCES;		/* Was EINVAL */
				return -1;

			}

			if (Fds[fd].size != 0L) {
				filefree (Fds[fd].data);
				Fds[fd].size = 0L;
			}
			Fds[fd].mode = O_CREAT | O_RDWR;
			Fds[fd].position = 0L;
			Fds[fd].data = 0L;
			Refcnt[fd] = 1;
			return fd;	/* Return handle */
		}
	}

	/* Create a new file */
	for (fd = 0; fd < Nfiles; fd++) {
		if (!Fds[fd].use) {

			Fds[fd].use = TRUE;
			Fds[fd].size = 0L;
			memset (Fds[fd].name, 0, MAX_FNAME);
			strncpy (Fds[fd].name, file, MAX_FNAME);
			if (strlen (file) >= MAX_FNAME)
				Fds[fd].name[MAX_FNAME -1] = '\0';
			Fds[fd].mode = O_CREAT | O_RDWR;
			Fds[fd].position = 0L;
			Fds[fd].data = 0L;

			Refcnt[fd] = 1;
			return fd;	/* Return handle */
		}
	}
	errno = ENOSPC;
	return -1;
}

ENTRY int
_open (const char *file, int mode)
{
	int fd;

	if (mode & O_TRUNC) {
		remove (file);
		mode |= O_CREAT;
	}
	switch (mode &(O_RDONLY | O_WRONLY | O_RDWR)) {
	case O_RDONLY:
		break;
	case O_WRONLY:
		break;
	case O_RDWR:
		break;
	default:
		errno = EINVAL;
		return -1;
	}
	if (*file == '/') file++;
	/* Does the file already exist? */
	for (fd = 0; fd < Nfiles; fd++) {
		if (Fds[fd].use && (strcmp (Fds[fd].name, file) == 0)) {
			if (Refcnt[fd] != 0) {
				/* File exists and is open.  We run into
				 * some shortcommings of our simple file
				 * system here. In our case OPEN acts a lot
				 * like a dup.  Ie: The file pointer isn't
				 * reset, and modes must match or the open
				 * fails. */
				/* File is already open. */
				if (Fds[fd].mode != mode) {
					errno = EACCES;		/* Was EINVAL */
					return -1;
				}
				Refcnt[fd]++;
			} else {
				/* First open, we set the rules. */
				Fds[fd].mode = mode;
				Fds[fd].position = 0L;
				Refcnt[fd] = 1;
			}
			return fd;	/* Return handle */
		}
	}
	/* File doesn't exist, and we want to create it. */
	if (mode & O_CREAT)
		return _creat (file, 0);

	errno = ENOENT;
	return -1;
}

/* Dup a file descriptor. Rather than allocating a new descriptor,
 * as in UNIX or MS - DOS, we maintain a reference count table so we
 * can return the same descriptor that is passed. This saves precious
 * file descriptor space.
 */
ENTRY int
dup (int fd)
{
	if (fd < 0 || fd >= Nfiles || Refcnt[fd] == 0) {
		errno = EINVAL;
		return -1;
	}
	/* Exclusive access check omitted in original code */
	/* if (Fds[fd].mode & O_EXCL) {
		errno = EACCESS;
		return -1;
	} */
	Refcnt[fd]++;
	return fd;
}

ENTRY int
_close (int fd)
{
	/* If out of range, or not open. */
	if (fd < 0 || fd >= Nfiles || Refcnt[fd] == 0) {
		errno = EINVAL;
		return -1;
	}

	if (--Refcnt[fd] != 0)
		return 0;	/* Somebody else is still using it */
	Fds[fd].mode = 0;
	if (!Fds[fd].use) {
		/* The file was already unlinked, and now the last reference
		 * to it is closed, so the memory can be freed. */
		if (Fds[fd].size != 0L) {
			filefree (Fds[fd].data);
			Fds[fd].size = 0L;
		}
	}
	return 0;
}

/* ************************************************************************* */

ENTRY int
_read (int fd, void *buf, unsigned cnt)
{
	sint31 readcnt;

	if (fd < 0 || fd >= Nfiles) {
		errno = EINVAL;
		return -1;
	}
	switch (Fds[fd].mode &(O_RDONLY | O_WRONLY | O_RDWR)) {
	case O_RDONLY:
		break;
	case O_RDWR:
		break;
	case O_WRONLY:
	default:
		errno = EINVAL;
		return -1;
	}

	readcnt = (sint31) ((uint32) cnt);
	if ((Fds[fd].size - Fds[fd].position) < readcnt) {
		readcnt = (Fds[fd].size - Fds[fd].position);
	}

	if (readcnt == 0) {
		return 0;
	}

	read_from_file_space (&Fds[fd], buf, readcnt);
	Fds[fd].position += readcnt;
	return (int) readcnt;			/* Return count */
}

/* ************************************************************************* */

ENTRY int
_write (int fd, const void *buf, unsigned cnt)
{
	sint31 writecnt, writeend;

	if (fd < 0 || fd >= Nfiles) {
		errno = EINVAL;
		return -1;
	}
	switch (Fds[fd].mode &(O_RDONLY | O_WRONLY | O_RDWR)) {
	case O_WRONLY:
		break;
	case O_RDWR:
		break;
	case O_RDONLY:
	default:
		errno = EINVAL;
		return -1;
	}

	writecnt = (sint31) ((uint32) cnt);
	writeend = Fds[fd].position + writecnt;

	/* ********************************************************************* */

	/* Copy file from FLASH to RAM if being overwritten */

	/* ********************************************************************* */

	/* Process writing more than allocated */
	if (writeend > Fds[fd].size) {
			/* Writing past the end of the file. */
			if (writeend > FILE_SIZE) {
				/* This write makes the file too big. */
				if (Fds[fd].size >= FILE_SIZE) {
					/* Files too big, can't write more. */
					errno = ENOMEM;
					return -1;
				}
				/* Just write what you can. */
				writeend = FILE_SIZE;
				writecnt = FILE_SIZE - Fds[fd].position;
			}

		Fds[fd].size = writeend;
	}

	/* ********************************************************************* */

	write_to_file_space (&Fds[fd], (void *) buf, writecnt);
	Fds[fd].position += writecnt;
	return (int) writecnt;			/* Return count */
}

/* ************************************************************************* */

ENTRY sint31
_lseek (int fd, sint31 offset, int whence)
{
	if (fd < 0 || fd >= Nfiles) {
		errno = EINVAL;
		return -1;
	}
	switch (whence) {
	case 0:
		Fds[fd].position = offset;
		break;
	case 1:
		Fds[fd].position += offset;
		break;
	case 2:
		Fds[fd].position = Fds[fd].size + offset;
		break;
	default:;
	}
	if (Fds[fd].position > Fds[fd].size)
		Fds[fd].position = Fds[fd].size;
	if (Fds[fd].position < 0L)
		Fds[fd].position = 0L;
	return Fds[fd].position;
}

/* ************************************************************************* */

ENTRY char *
fversion (int fd)
{
	/* Return pointer to the version number */
	return &Fds[fd].name[strlen (Fds[fd].name) + 1];
}

/* ************************************************************************* */

ENTRY int
sversion (int fd, const char *version)
{
	int length;
	char *version_p;

	/* Version number is a special string after the null terminated file name */
	length = strlen (Fds[fd].name) + 1;
	version_p = &Fds[fd].name[length];

	length = MAX_FNAME - length;
	generic_safe_strcpy (version_p, version, length);

	return 0;
}

/* ************************************************************************* */

ENTRY int
remove (const char *file)
{
	return unlink (file);
}

/* ************************************************************************* */

ENTRY int
unlink (const char *file)
{
	int fd;

	if (*file == '/') file++;
	for (fd = 0; fd < Nfiles; fd++) {
		if (Fds[fd].use && (strcmp (Fds[fd].name, file) == 0)) {
			Fds[fd].use = FALSE;
			if (Refcnt[fd] == 0 && Fds[fd].size != 0L) {
				filefree (Fds[fd].data);
				Fds[fd].size = 0L;
			}
			return 0;	/* Return success */
		}
	}
	errno = ENOENT;
	return -1;
}

/* ************************************************************************* */

ENTRY int
rename (const char *oldfile, const char *newfile)
{
	int fd;
	char *version;

	if (*oldfile == '/') oldfile++;
	if (*newfile == '/') newfile++;
	/* Check that newfile does not exist */
	for (fd = 0; fd < Nfiles; fd++) {
		if (Fds[fd].use && (strcmp (Fds[fd].name, newfile) == 0)) {
			errno = EACCES;
			return -1;	/* Return error */
		}
	}
	/* Now perform file rename if oldfile exists */
	for (fd = 0; fd < Nfiles; fd++) {
		if (Fds[fd].use && (strcmp (Fds[fd].name, oldfile) == 0)) {
			/* Get the version number first */
			version = fversion (fd);
			version = strdup (version);

			/* Rename the file */
			memset (Fds[fd].name, 0, MAX_FNAME);
			strncpy (Fds[fd].name, newfile, MAX_FNAME);
			if (strlen (newfile) >= MAX_FNAME) {
				Fds[fd].name[MAX_FNAME -1] = '\0';
			}

			/* Save the version number */
			sversion (fd, version);
			free (version);
			return 0;	/* Return success */
		}
	}
	errno = ENOENT;
	return -1;
}

/* ************************************************************************* */

ENTRY int
fstat (int fd, struct stat *statbuf)
{
	if ((fd < 0) || (fd >= Nfiles)) {
		errno = ENOENT;
		return -1;
	}
	if (Fds[fd].use) {
		statbuf->st_size = Fds[fd].size;
		return 0;
	}
	errno = ENOENT;
	return -1;
}

/* ************************************************************************* */

ENTRY int
stat (const char *file, struct stat *statbuf)
{
	int fd;

	if (*file == '/') file++;
	for (fd = 0; fd < Nfiles; fd++) {
		if (Fds[fd].use && (strcmp (Fds[fd].name, file) == 0)) {
			fstat (fd, statbuf);
			return 0;	/* Return success */
		}
	}
	errno = ENOENT;
	return -1;
}

/* ************************************************************************* */

ENTRY sint15
showdirentry (int fd, int full, FILE *fp)
{
	if ((fd < 0) || (fd >= Nfiles)) {
		errno = ENOENT;
		return -1;
	}
	if (Fds[fd].use) {
		if (full)
			fprintf(fp, "%-15s   %5ld\n", Fds[fd].name, (long) Fds[fd].size);
		else
			fprintf(fp, "%s\n", Fds[fd].name);
		errno = 0;
		return (sint15) Fds[fd].size;
	}
	errno = ENOENT;
	return 0;
}

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* File block pool */

#define NUM_FBLK	((0x1ffff / FBLK_SIZE) - 1)		/* 128 Kbytes */

#pragma DATA_SECTION (FileBlks, ".sect_fblk")

static struct fblk FileBlks[NUM_FBLK];
static struct fblk *Fblkq = NULL;
static uint32 FblkAllocs = 0L;
static uint32 FblkFrees = 0L;
static uint32 FblkFail = 0L;
static uint16 Fblkqlen = 0;

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

ENTRY uint16
get_flbkqlen(void)
{
	return Fblkqlen;
}

ENTRY void
fbuf_init (void)
{
	int i;
	register struct fblk *blk;

	Fblkq = NULL;
	memset (FileBlks, 0, sizeof (FileBlks));

	for (i = 0; i < NUM_FBLK; i++) {
		blk = &FileBlks[i];
		blk->next = Fblkq;
		Fblkq = blk;
	}
	Fblkqlen = i;
	FblkAllocs = 0L;
	FblkFrees = 0L;
	FblkFail = 0L;
}

/* ************************************************************************* */

/* Print the queue statistics. */
ENTRY void
fqstat (void)
{
	printf("fblk allocs %lu frees %lu (diff %ld) fails %lu\n",
		(long) FblkAllocs,
		(long) FblkFrees,
		(long) (FblkAllocs - FblkFrees),
		(long) FblkFail);
	printf("Nblkqlen %u Fblksize %u\n",
		Fblkqlen,
		FBLK_SIZE);
}

/* ************************************************************************* */

/* Allocate fblk from Fblkq
 */
ENTRY struct fblk *
alloc_fblk (void)
{
	register struct fblk *blk;

	if ((blk = Fblkq) == NULL) {
		FblkFail++;
	} else {
		Fblkq = blk->next;
		blk->next = NULL;
		Fblkqlen--;
		FblkAllocs++;
	}
	return blk;
}

/* ************************************************************************* */

/* Deallocate fblk (one ore more in a chain) to Fblkq
 */
ENTRY void
free_fblk (struct fblk *blk)
{
	struct fblk *temp;

	if (blk == NULL) {
		return;
	}
	temp = Fblkq;
	Fblkq = blk;
	Fblkqlen++;
	FblkFrees++;

	while (blk->next != NULL) {
		blk = blk->next;
		Fblkqlen++;
		FblkFrees++;
	}

	blk->next = temp;
}
