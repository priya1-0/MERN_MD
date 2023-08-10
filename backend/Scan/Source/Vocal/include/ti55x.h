
/* ************************************************************************* */
/*
 *	ti55x.h
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
 *	Module:		INCLUDE
 *
 *	Define TI 55x specific symbols and structures.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 19:50:33  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _INCLUDE_TI55X_H
#define _INCLUDE_TI55X_H

#include "include/ti5502.h"

#define _CSL_TIME
#define _CSL_RTC_DATA_H_
#include "c55x.h"

/* ************************************************************************* */
/*
 *	Define hardware target platform
 *
 */
#define BIT(n)						((1)<<(n))
#define HPIC_REG__HINT					BIT(3)

/* ************************************************************************* */
/*
 *	Define DMA register offsets
 *
 */
struct _dma {
	volatile unsigned int CSDP;		/* 0x00: source destination parameters */
	volatile unsigned int CCR;		/* 0x01: control */
	volatile unsigned int CICR;		/* 0x02: interrupt control */
	volatile unsigned int CSR;		/* 0x03: status */
	volatile unsigned int CSSA_L;	/* 0x04: source start address lower bits */
	volatile unsigned int CSSA_U;	/* 0x05: source start address upper bits */
	volatile unsigned int CDSA_L;	/* 0x06: source destination start address lower bits */
	volatile unsigned int CDSA_U;	/* 0x07: source destination start address upper bits */
	volatile unsigned int CEN;		/* 0x08: element number */
	volatile unsigned int CFN;		/* 0x09: frame number */
	volatile unsigned int CSFI;		/* 0x0A: source frame index */
	volatile unsigned int CSEI;		/* 0x0B: source element index */
	volatile unsigned int CSAC;		/* 0x0C: source address counter */
	volatile unsigned int CDAC;		/* 0x0D: destination address counter */
	volatile unsigned int CDEI;		/* 0x0E: destination element index */
	volatile unsigned int CDFI;		/* 0x0F: destination frame index */
	volatile unsigned int fill[16];	/* 0x10-0x1F: structure filler */
};

/* PLL Control / Status Register 5501 */
#define PLLCSR		((ioport volatile unsigned int *) 0x1c80)

/* PLL Multiplier Control Register 5501 */
#define PLLM_REG	((ioport volatile unsigned int *) 0x1c88)

/* General-Purpose I/O Registers 5501 */
#define IODIR		((const ioport volatile unsigned int *) 0x3400)
#define IODATA		((const ioport volatile unsigned int *) 0x3401)

/* I-Cache registers */
#define ICGC		((ioport volatile unsigned int *) 0x1400)
#define ICFLARL		((ioport volatile unsigned int *) 0x1401)
#define ICFLARH		((ioport volatile unsigned int *) 0x1402)
#define ICWMC		((ioport volatile unsigned int *) 0x1403)
#define ICWC	ICWMC

/* DMA Global Control Register */
#define DMA_GCR  ((ioport volatile unsigned int *) 0x0E00)

#define pMcbsp1_mpi   ((ioport struct _mcbsp *)0x2c00)

extern ioport struct _mcbsp *pMcbsp;

/* ************************************************************************* */
/*
 *	Define Processor Interrupt Registers
 *
 */
#define IFR0_REG  ((volatile unsigned int *) 0x0001)
#define IFR1_REG  ((volatile unsigned int *) 0x0046)
#define IER0_REG  ((volatile unsigned int *) 0x0000)
#define IER1_REG  ((volatile unsigned int *) 0x0045)
#define IVPD_REG  ((volatile unsigned int *) 0x0049)
#define IVPH_REG  ((volatile unsigned int *) 0x004A)

/* ************************************************************************* */
/*
 *	Define Processor Status Registers
 *
 */
#define ST1_55_REG  ((volatile unsigned int *) 0x0003)
#define ST3_55_REG  ((volatile unsigned int *) 0x0004)

/* ************************************************************************* */
/*
 *	Routine:	system_peripheral_write
 *
 *	Note:
 *		This function reads from the register first.  Do not use
 *		if register reads are destructive!
 *
 *	Parameters:
 *		reg - system peripheral register to modify
 *		mask - bit mask
 *		pattern - bit pattern
 *
 *	Returns:
 *		none
 */
INLINE uint16
system_peripheral_write (ioport volatile unsigned int *reg, uint16 mask, uint16 pattern)
{
	uint16 shadow = *reg;
	shadow = (shadow & ~mask) | (pattern & mask);
	*reg = shadow;
	return shadow;
}

/* ************************************************************************* */
/*
 *	Routine:	system_peripheral_read
 *
 *
 *
 *
 *	Parameters:
 *		reg - system peripheral register to read.
 *		mask - system peripheral bits to read
 *
 *	Returns:
 *		none
 */
INLINE uint16
system_peripheral_read (ioport volatile unsigned int *reg)
{
	uint16 val = *reg;
	return val;
}

/* ************************************************************************* */
/*
 *	Routine:	enable_interrupt
 *
 *
 *
 *	Parameters:
 *		evt - event to enable in the interrupt enable register
 *
 *	Returns:
 *		none
 */
INLINE void
enable_interrupt(uint16 evt)
{
	uint16 value;
	int old_intm = ((*(volatile uint16*) 0x03) & (0x800));
	asm("\
		NOP;\
		BSET INTM;\
	");
	if (((evt & 0x10) >> 4)) {
		value = (*(volatile uint16*) 0x45) | (1 << (evt & 0xf));
		(*(volatile uint16*) 0x45) = value;
	} else {
		value = (*(volatile uint16*) 0x00) | (1 << (evt & 0xf));
		(*(volatile uint16*) 0x00) = value;
	}
	if (old_intm) {
		asm("\
			NOP;\
			BSET INTM;\
		");
	} else {
		asm("\
			NOP;\
			BCLR INTM;\
		");
	}
}

/* ************************************************************************* */
/*
 *	Routine:	clear_interrupt_flag
 *
 *
 *
 *	Parameters:
 *		evt - event to clear flag
 *
 *	Returns:
 *		none
 */
INLINE void
clear_interrupt_flag(uint16 evt)
{
	uint16 mask;
	int old_intm = ((*(volatile uint16*) 0x03) & (0x800));
	asm("\
		NOP;\
		BSET INTM;\
	");
	mask = (1 << (evt & 0xf));
	if (((evt & 0x10) >> 4)) {
		(*(volatile uint16*) 0x46) = mask;
	} else {
		(*(volatile uint16*) 0x01) = mask;
	}
	if (old_intm) {
		asm("\
			NOP;\
			BSET INTM;\
		");
	} else {
		asm("\
			NOP;\
			BCLR INTM;\
		");
	}
}
#endif /* _INCLUDE_TI55X_H */
