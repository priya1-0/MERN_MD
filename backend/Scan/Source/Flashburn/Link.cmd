/*************************************************************************
* $RCSfile$
* $Revision$
* $Date$
* Copyright (c) 2001 Texas Instruments Incorporated
*
* Description:
*       This file is used to link 55x FBTC for FlashBurn.
*       Use it as a guideline; you  may want to change the
*       allocation scheme according to the size of your program
*       and the memory layout of your target system.
*
*************************************************************************/
-c
-stack 0x0256

/* SPECIFY THE SYSTEM MEMORY MAP                                    	*/
/* - Loader/Linker only uses Byte-addresses.							*/
MEMORY
{
	DARAM (RWIX)    : o=00000C0h, l=000FF40h
/*	SARAM (RWIX)	: o=0010000h, l=0040000h*/
	CE0 (RWIX)		: o=0050000h, l=03B0000h
	CE1 (RWIX)		: o=0400000h, l=0400000h
	CE2 (RWIX)		: o=0800000h, l=0400000h
	CE3 (RWIX)		: o=0C00000h, l=03F8000h
	DROM(RX)		: o=0FF8000h, l=0008000h
}

/* SPECIFY THE SECTIONS ALLOCATION INTO MEMORY                      	*/
SECTIONS
{
	/* The power-up vector location is NOT writable.					*/
	/* - So vectors must be loaded at a different address.				*/
	.text       > DARAM			/* CODE             					*/
    .switch     > DARAM			/* SWITCH TABLE INFO 					*/
    .const      > DARAM			/* CONSTANT DATA    					*/
    .cinit      > DARAM			/* INITIALIZATION TABLES 				*/
    .pinit      > DARAM			/* INITIALIZATION TABLES 				*/

    .data       > DARAM fill=0xBEEF	/* INITIALIZED DATA 				*/
    .bss        > DARAM	fill=0xBEEF /* GLOBAL & STATIC VARS  			*/
    .sysmem     > DARAM	fill=0xBEEF /* DYNAMIC MALLOC AREA 				*/
    .stack      > DARAM fill=0xBEEF	/* PRIMARY SYSTEM STACK  			*/
    .cio        > DARAM fill=0xBEEF
}
