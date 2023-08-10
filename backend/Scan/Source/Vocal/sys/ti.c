
/* ************************************************************************* */
/*
 *	ti.c
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
 *	This file contains OS - and machine - dependent stuff for TI TMS DSPs.
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
#include <std.h>
#include <clk.h>

/* ************************************************************************* */

ENTRY void
ti_sys_init (void)
{
	srand ((unsigned int) (CLK_getltime ()));
}

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

/* integer to ascii */
ENTRY char *
itoa (sint7 balance, char tmp[11], int len)
{
	sprintf(tmp,"%d",balance);
	return tmp;
}

/* ************************************************************************* */

ENTRY int
random (int i)
{
	return rand () % i;
}

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

/*
 * setjmp / longjmp provided by TI (in lib\rts.src) doesn't save / restore
 * the upper 8 - bits of the stack pointers (it is common between sp and ssp)
 * We need to save restore this value because our normal system stack
 * is located in DARAM and the heap, which is where the process stacks
 * are allocated from, is in SDRAM.  This requires that the extended
 * stack pointer register be saved / restored
 */

ENTRY int
tisetjmp (sint31 *env)
{
/*
;*-------------------------------------------------------------------------- -
; *   setjmp
; *
; *     C syntax  :   int setjmp (env)
;*                      jmp_buf *env;
; *
; *     Function  : Save caller's current environment for a subsequent
; *                 call to longjmp.  Return 0.
;*-------------------------------------------------------------------------- -
; *
;*  NOTE : ANSI specifies that "setjmp.h" declare "setjmp" as a macro.
;*         In our implementation, the setjmp macro calls a function "_setjmp".
;*         However, since the user may not include "setjmp.h", we provide
; *         two entry - points to this function.
; *
;*-------------------------------------------------------------------------- -
 */
#Acode

	MOV RETA, dbl (*AR0 +); LCRPC

	MOV XAR5, dbl (*AR0 +)
	MOV XAR6, dbl (*AR0 +)
	MOV XAR7, dbl (*AR0 +)

	POPBOTH AC1
	PSHBOTH AC1
	MOV AC1, dbl (*AR0 +)

	MOV XSP, dbl (*AR0 +)
	MOV XSSP, dbl (*AR0 +)

	MOV DR2, *AR0 +
	MOV DR3, *AR0 +
#Ccode
	return 0;
}

/* ************************************************************************* */

ENTRY int
tilongjmp (sint31 *env, int returnvalue)
{
/*
;*-------------------------------------------------------------------------- -
; *   longjmp
; *
; *     C syntax  :   int longjmp (env, returnvalue)
;*                      jmp_buf *env;
; *                      int     returnvalue;
; *
; *     Function  : Restore the context contained in the jump buffer.
;*                 This causes an apparent "2nd return" from the
;*                 setjmp invocation which built the "env" buffer.
;*                 This return appears to return "returnvalue".
; *                 NOTE: This function may not return 0.
;*-------------------------------------------------------------------------- -
 */
#Acode
	.global _nested_interrupt_read_depth
	BSET ST2_DBGM
	BSET	INTM

	MOV dbl (*AR0 +), RETA; LCRPC

	MOV dbl (*AR0 +), XAR5
	MOV dbl (*AR0 +), XAR6
	MOV dbl (*AR0 +), XAR7

	MOV dbl (*AR0 +), AC1

	MOV dbl (*AR0 +), XSP
	MOV dbl (*AR0 +), XSSP

	NOP; silicon exception CPU_92
	NOP

	POPBOTH AC2
	PSHBOTH AC1

	MOV *AR0 +, DR2
	MOV *AR0 +, DR3

	CALL _nested_interrupt_read_depth
	BCC skip_int_disable, T0 != #0
	BCLR INTM

skip_int_disable:
	BCLR ST2_DBGM

#Ccode

	if (returnvalue == 0) {
		return 1;
	}
	else {
		return returnvalue;
	}
}

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */
/*
 *	Module Routine: large_buf_strcat
 *
 *	Does a strcat but takes into account size of destination, terminates
 *  properly, and cuts a warning on overflow.
 *
 *	Parameters:
 *		(sint31 dest) :      Destination location
 *		(const uint8 *src) : Source string
 *		(uint32) :              Destination length
 *
 *	Returns:
 *		(uint8) :  1 on success, 0 on failure (not that it matters)
 */
ENTRY uint8
large_buf_strcat (sint31 dest, const char *src, uint32 size)
{
	int i, j;

	if ((*src & 0xff) == 0) return 1;
	if (size <= 0) {
		print_debug_on(("Error in generic_safe_strcat(), size was %d.\n",size));
		return 0;
	}

	/* advance to end of dest */
	for (j = 0;j < size && (*((char*) (dest + j)) & 0xff) != '\0';j++);

	if (j >= size) {
		print_debug_on(("Error in generic_safe_strcat(), destination already full.\n"));
		print_debug_on(("Size %d, source was --------------\n%s\n---------------",size,src));
		return 0;
	}

	/* give us room for the terminating 0 */
	size--;

	for (i = 0; j < size && (src[i] & 0xff) != 0; i++, j++) {
		*((char*) (dest + j)) = src[i] & 0xff;
	}
	*((char*) (dest + j)) = 0;
	if ((src[i] & 0xff) == 0) return 1;

	size++;
	print_debug_on(("Error in generic_safe_strcat(), destination full.\n"));
	print_debug_on(("Size %d, source was --------------\n%s\n---------------",size,src));
	return 0;
}

/* ************************************************************************* */
/*
 *	Entry Routine: large_buf_strlen
 *
 *	This routine is used to return length of cs.
 *
 *	Parameters:
 *		"cs"	 string to parse
 *
 *	Returns:
 *		length of cs
 *
 */
ENTRY uint32
large_buf_strlen (sint31 cs)
{
	sint31 x = 0;
	while (*((char*) cs) != '\0') {
		x++;
		cs++;
	}
	return x;
}

/* ************************************************************************* */
/*
 *	Module Routine: large_buf_strcpy
 *
 *	Does a strcpy but takes into account size of destination, terminates
 *  properly, and cuts a warning on overflow.  Its like strncpy, but
 *  does extra stuff.
 *
 *	Parameters:
 *		(sint31 dest) :      Destination location
 *		(const char *src) : Source string
 *		(uint32) :              Destination length
 *
 *	Returns:
 *		(uint8) :  1 on success, 0 on failure (not that it matters)
 */

ENTRY uint8
large_buf_strcpy (sint31 dest, const char *src, uint32 size)
{
	int i;
	if (size <= 0) {
		print_debug_on(("Error in generic_safe_strcpy(), size was %d.\n",size));
		return 0;
	}

	/* give us room for the terminating 0 */
	size--;

	for (i = 0; i < size && src[i] != '\0'; i++) *((char*) ((sint31) dest + i)) = src[i];
	*((char*) ((sint31) dest + i)) = 0;
	if (src[i] == 0) return 1;

	size++;
	print_debug_on(("Error in generic_safe_strcpy(), overflow into buffer of size %d, source was '%s'.\n",size,src));
	return 0;
}
