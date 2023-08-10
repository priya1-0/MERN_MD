
/* ************************************************************************* */
/*
 *	md5c.h
 *
 *	(C) 1994 - 2006 VOCAL Technologies, Ltd.
 *
 *	ALL RIGHTS RESERVED.  PROPRIETARY AND CONFIDENTIAL.
 *
 *	VOCAL Technologies, Ltd.
 *	90A John Muir Drive.
 *	Buffalo, NY  14228
 *
 *	Product:	LANsEND SSL
 *
 *	Module:		CRYPTO
 *
 *	This file contains the MD5 declarations.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.2.6.2  2009/04/28 18:26:54  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _CRYPTO_MD5C_H
#define _CRYPTO_MD5C_H

/* Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
	rights reserved.

	License to copy and use this software is granted provided that it
	is identified as the "RSA Data Security, Inc. MD5 Message-Digest
	Algorithm" in all material mentioning or referencing this software
	or this function.

	License is also granted to make and use derivative works provided
	that such works are identified as "derived from the RSA Data
	Security, Inc. MD5 Message-Digest Algorithm" in all material
	mentioning or referencing the derived work.

	RSA Data Security, Inc. makes no representations concerning either
	the merchantability of this software or the suitability of this
	software for any particular purpose. It is provided "as is"
	without express or implied warranty of any kind.

	These notices must be retained in any copies of any part of this
	documentation and / or software.
 */

/* POINTER defines a generic pointer type */
typedef uint8 *POINTER;

/* MD5 context. */
typedef struct {
  uint32 state[4];				     /* state (ABCD) */
  uint32 count[2];	  /* number of bits, modulo 2^64 (lsb first) */
  uint8 buffer[64];                         /* input buffer */
} MD5_CTX;

#define MD5_HASHLEN 16
#define MD5_HASHHEXLEN 32

/* ************************************************************************* */

#define MD5_DIGEST_LENGTH 16
#define MD5_CBLOCK	64

/* ************************************************************************* */

/*- MKHEADER Begin -*/

/* Global Routines: */

/* md5c.c */
void MD5Init (MD5_CTX *context);
void MD5Update (MD5_CTX *context, uint8 *input, unsigned int inputLen);
void MD5Final (uint8 digest[16], MD5_CTX *context);
void MD5CvtHex(uint8 Bin[16], char Hex[33]);

/*- MKHEADER End -*/


/* ************************************************************************* */

#endif /* _CRYPTO_MD5C_H */
