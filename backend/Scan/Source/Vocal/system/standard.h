
/* ************************************************************************* */
/*
 *	standard.h
 *
 *	(C) 1994 - 2006 VOCAL Technologies, Ltd.
 *
 *	ALL RIGHTS RESERVED.  PROPRIETARY AND CONFIDENTIAL.
 *
 *	VOCAL Technologies, Ltd.
 *	90A John Muir Drive.
 *	Buffalo, NY  14228
 *
 *	Product:	MODEM 101
 *
 *	Module:		SYSTEM
 *
 *	This file defines the standard system definitions.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 20:47:21  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _SYSTEM_STANDARD_H
#define _SYSTEM_STANDARD_H

/* ************************************************************************* */
/* set up defines for various local, module, and system scopes */
/* These also set up compiler specific defines for various compiler features. */
/* ************************************************************************* */

#define ENTRY
#define GLOBAL
#define MODULE
#define THREAD
#define LOCAL  static

/* inline scope */

#define INLINE static inline

#ifndef INLINE
#define INLINE Error_INLINE_is_either_not_enabled_or_not_yet_configured_for_this_compiler
#endif /* INLINE */

#define CONST  const

/* ************************************************************************* */
/* Use options.h to figure out which types are legal */
/* ************************************************************************* */

/* ************************************************************************* */
/* lowest level typedefs */
/* ************************************************************************* */

typedef unsigned char uint8;	/* range 0-255 */
typedef unsigned char umod8;	/* 8 bit math requirements */
typedef unsigned char octet;	/* octet data */
typedef signed char sint7;

#define uchar(x) (unsigned char) (((unsigned char) (x)) & 0xff)

typedef unsigned char pack8;	/* packed octet data */
typedef pack8 expand8; /* expand octet data to uint16 */

typedef unsigned short uint16;
typedef signed short sint15;
typedef signed short phase_t;

typedef unsigned long uint32;
typedef signed long sint31;

/* ************************************************************************* */
/* structures and more complex data types - fract40 included */
/* ************************************************************************* */

/* ************************************************************************* */
/* set up the base 64 bit data types */
/* ************************************************************************* */

/* everyone else in the world uses these as the default, except */
/* for the TI 54X compiler, which doesn't have any 64 bit types */
typedef unsigned long long uint64;
typedef long long sint63;

/* ************************************************************************* */
/* set up fract types based on fundamental types */
/* ************************************************************************* */

typedef sint15 fract;
typedef uint16 ufract;
typedef sint31 fract32;
typedef uint32 ufract32;

typedef sint63 fract40;
typedef uint64 ufract40;

/* the TI 55X compiler has some wierdness associated with it.  The 64 */
/* bit data types aren't really 64 bit - they are 'accumulator' size */
/* instead which is a mere 40 bits.  As such, we have to create */
/* fract48 as a structure instead. */
typedef struct {
	fract  hi;
	ufract me;
	ufract lo;
} fract48;

/* ************************************************************************* */
/* defines for doublefract, pretty much all processors are the same */
/* ************************************************************************* */

/* ************************************************************************* */
/* LSI specific stuff.  Don't ask why it's done this way, no one remembers */
/* ************************************************************************* */

/* ************************************************************************* */
/* micellaneous typedefs and structs */
/* ************************************************************************* */

typedef uint8 byte;
typedef uint16 word;

typedef uint16 bool;

typedef sint15 clk_t;

typedef struct {
	fract real;
	fract imag;
} complex_t;

typedef fract log_t;		/* used to represent 6.10 log numbers */
typedef sint15 index_t;		/* used for array indexes */
typedef sint15 count_t;		/* used for counters */

typedef uint16 event_t;
typedef uint16 offsettype;
typedef sint15 Flag;

typedef void (*FPP)(void);

/* ************************************************************************* */
/* forward declare typedefs */
/* ************************************************************************* */

/* ************************************************************************* */
/* miscellaneous platform independent */
/* ************************************************************************* */

#define MAX_UINT8	(255)
#define MAX_SINT7	(127)
#define MIN_SINT7	(-128)

#define MAX_UINT16	(65535)
#define MAX_SINT15	(32767)
#define MIN_SINT15	(-32768)

#define MIN_FRACT	FRACT (MIN_SINT15)

#define MAX_UINT32	(4294967296)
#define MAX_SINT31	(2147483647)
#define MIN_SINT31	(-2147483648)

#define MIN_DOUBLE	(1.7e-308)
#define MAX_DOUBLE	(1.7e308)

#define PI						3.141592654
#define LOG2					0.30102999571

#define	S0			FRACT  (0)
#define	U0			UFRACT (0)
#define	L0			LFRACT (0)
#define	E0			EFRACT (0)

#define	M1			FRACT  (0x8000)
#define	S1			FRACT  (0x7fff)
#define	U1			UFRACT (0x8000)
#define	L1			LFRACTL(0x7fffffff)
#define	E1			EFORMATL(LFRACTL(0x7fffffff))
#define NEAR1		FRACT  (0x7FFF)

#define NULLCHAR (char *)0	/* Null character pointer */
#define	NULLFILE (FILE *)0	/* Null file pointer */

#define OFF			0
#define ON			1

#define BIT0	0x0001
#define BIT1	0x0002
#define BIT2	0x0004
#define BIT3	0x0008
#define BIT4	0x0010
#define BIT5	0x0020
#define BIT6	0x0040
#define BIT7	0x0080
#define BIT8	0x0100
#define BIT9	0x0200
#define BIT10	0x0400
#define BIT11	0x0800
#define BIT12	0x1000
#define BIT13	0x2000
#define BIT14	0x4000
#define BIT15	0x8000

#define bit(loc, msk)	(((loc)&(msk)) == (msk))
#define set(loc, msk)	((loc) |=  (msk))
#define clr(loc, msk)	((loc) &= ~(msk))

#define forever			for (;;)

#define macro__min(A,B)	(((A) < (B)) ? (A) : (B));
#define macro__max(A,B)	(((A) > (B)) ? (A) : (B));

#define min(a,b)		(((a) < (b)) ? (a) : (b))
#define max(a,b)		(((a) > (b)) ? (a) : (b))

/* ************************************************************************* */

#define XXX
#define OOO

/* ************************************************************************* */
/* profile macro definitions */
/* ************************************************************************* */

#define UPPERWORD(x)	(((x) >> 16) & 0x0000FFFF)
#define LOWERWORD(x)	((x) & 0x0000FFFF)

/* PORTING NOTE - phase vars should be a signed integer, with the phase */
/* angle in the upper bits (including the sign bit).  These macros should */
/* be configured to convert between 16 bit integers and whatever the */
/* phase_t type happens to be. */
#define PHASE(x)		((phase_t)(x))
#define PHASE2INT(x)	((sint15)(x))

#include "system/profile.h"

/* ************************************************************************* */
/* miscellaneous include files and platform dependent */
/* ************************************************************************* */

/* ************************************************************************* */
/* miscellaneous */
/* ************************************************************************* */

#define ph2p_return()	return
#define ph2p_exit()		exit(-1)

#ifndef NULL
#if defined (__TINY__) || defined (__SMALL__) || defined (__MEDIUM__)
#define NULL	0
#else
#define NULL	0L
#endif
#endif

#define far

#define INTERRUPT interrupt

#define FALSE	0
#define TRUE	(!FALSE)

#define NET_DOMAIN_SIZEOF			64		/* Fully qualified domain name with optional port numer */

/* ************************************************************************* */

#define ident(x)
#define CIRCULAR

#define CLOCK(x)	((clk_t)(x))
#define COUNT(x)	((count_t)(x))

#define INS_CIRCULAR(offset,LENGTH,buffer)	buffer[offset]=buffer[offset+LENGTH]

#define INC_CIRCULAR(offset,LENGTH)	if (++offset >= LENGTH) offset = 0
#define DEC_CIRCULAR(offset,LENGTH)	if (--offset < 0) offset += LENGTH
#define FWD_CIRCULAR(offset,LENGTH)	if (offset >= LENGTH) offset -= LENGTH
#define BWD_CIRCULAR(offset,LENGTH)	if (offset <       0) offset += LENGTH

#define conv_clip_adj(x,y) ADDFSAT(x,y)

/* ************************************************************************* */

/* some of the const filter coefs in various files use these */
#define YBSS
#define XBSS

/* ************************************************************************* */
/* interrupt macros */
/* ************************************************************************* */

void nested_interrupt_disable (void);
void nested_interrupt_restore (void);
void nested_interrupt_forced_enable (void);
uint16 nested_interrupt_read_depth (void);

#define base__nested_interrupt_disable()			nested_interrupt_disable()
#define base__nested_interrupt_restore()			nested_interrupt_restore()
#define base__nested_interrupt_forced_enable()		nested_interrupt_forced_enable()
#define base__nested_interrupt_read_depth()			nested_interrupt_read_depth()
#define base__nested_interrupt_force_depth(A)		nested_interrupt_force_depth(A)

/* ************************************************************************* */
/* interrupt enable/disable using above macros */
/* ************************************************************************* */

#define sys_nested_interrupt_disable()				base__nested_interrupt_disable()
#define sys_nested_interrupt_restore()				base__nested_interrupt_restore()
#define inc_nested_interrupt_disable()
#define inc_nested_interrupt_restore()

#define line_nested_interrupt_disable()				base__nested_interrupt_disable()
#define line_nested_interrupt_restore()				base__nested_interrupt_restore()
#define line_inc_nested_interrupt_disable()
#define line_inc_nested_interrupt_restore()

#define dteif_nested_interrupt_disable()			base__nested_interrupt_disable()
#define dteif_nested_interrupt_restore()			base__nested_interrupt_restore()
#define dteif_inc_nested_interrupt_disable()
#define dteif_inc_nested_interrupt_restore()

#define sigma_nested_interrupt_disable()
#define sigma_nested_interrupt_restore()
#define sigma_inc_nested_interrupt_disable()
#define sigma_inc_nested_interrupt_restore()

#define timer_nested_interrupt_disable()			base__nested_interrupt_disable()
#define timer_nested_interrupt_restore()			base__nested_interrupt_restore()
#define timer_inc_nested_interrupt_disable()
#define timer_inc_nested_interrupt_restore()

#define network_nested_interrupt_disable()			base__nested_interrupt_disable()
#define network_nested_interrupt_restore()			base__nested_interrupt_restore()
#define network_nested_interrupt_forced_enable()	base__nested_interrupt_forced_enable()
#define network_nested_interrupt_read_depth()		base__nested_interrupt_read_depth()
#define network_nested_interrupt_force_depth(A)		base__nested_interrupt_force_depth(A)

#define serial_nested_interrupt_disable()			base__nested_interrupt_disable()
#define serial_nested_interrupt_restore()			base__nested_interrupt_restore()

#define packet_nested_interrupt_disable()			base__nested_interrupt_disable()
#define packet_nested_interrupt_restore()			base__nested_interrupt_restore()

/* ************************************************************************* */
/* miscellaneous initialization */
/* ************************************************************************* */

#define initialize_data(data)								\
															initialize_routine (l_ ## data, data, b_ ## data)

#define initialize_data_uint16(data)						\
															initialize_routine_uint16 (l_ ## data, data, b_ ## data)

#define initialize_data_sint15(data)						\
															initialize_routine_sint15 (l_ ## data, data, b_ ## data)

#define initialize_buffer(size,data)						\
															static int l_ ## data = size;								\
															static uint16 b_ ## data [size]

void initialize_routine (int size, fract data [], uint16 b_data []);

void initialize_routine_uint16 (int size, uint16 data [], uint16 b_data []);

void initialize_routine_sint15 (int size, sint15 data [], uint16 b_data []);

#ifdef WE_ARE_DEFINING_VARIABLES
void
   initialize_routine (int size, fract data [], uint16 b_data [])
{
	int i;
	for (i = 0; i < size; i++) {
		data [i] = FRACT (b_data [i]);
	}
}

void
   initialize_routine_uint16 (int size, uint16 data [], uint16 b_data [])
{
	int i;
	for (i = 0; i < size; i++) {
		data [i] = b_data [i];
	}
}

void
   initialize_routine_sint15 (int size, sint15 data [], uint16 b_data [])
{
	int i;
	for (i = 0; i < size; i++) {
		data [i] = (sint15) b_data [i];
	}
}
#endif /* WE_ARE_DEFINING_VARIABLES */

/* ************************************************************************* */
/* debug */
/* ************************************************************************* */

#define foobuf_put(A)

/* ************************************************************************* */

#define DEBUGC(name)
#define DEBUGCX(name)
#define DEBUGCE(name)
#define note(A)
#define DEBUGCNL()

#endif /* SYSTEM_STANDARD_H */
