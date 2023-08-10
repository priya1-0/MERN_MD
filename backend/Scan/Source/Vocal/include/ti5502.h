
/* ************************************************************************* */
/*
 *	ti5502.h
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

#ifndef _INCLUDE_TI5502_H
#define _INCLUDE_TI5502_H

#ifndef _INCLUDE_TI55X_H
#error Do not include ti5502.h directly!
#endif /* _INCLUDE_TI55X_H */

/* ************************************************************************* */
/*
 *	Define McBSP register offsets
 *
 */
struct _mcbsp {
	volatile unsigned int drr1;
	volatile unsigned int drr2;
	volatile unsigned int dxr1;
	volatile unsigned int dxr2;
	volatile unsigned int spcr1;
	volatile unsigned int spcr2;
	volatile unsigned int rcr1;
	volatile unsigned int rcr2;
	volatile unsigned int xcr1;
	volatile unsigned int xcr2;
	volatile unsigned int srgr1;
	volatile unsigned int srgr2;
	volatile unsigned int mcr1;
	volatile unsigned int mcr2;
	volatile unsigned int rcera;
	volatile unsigned int rcerb;
	volatile unsigned int xcera;
	volatile unsigned int xcerb;
	volatile unsigned int pcr;
	volatile unsigned int reserved;
	volatile unsigned int rcerc;
	volatile unsigned int rcerd;
	volatile unsigned int xcerc;
	volatile unsigned int xcerd;
	volatile unsigned int rcere;
	volatile unsigned int rcerf;
	volatile unsigned int xcere;
	volatile unsigned int xcerf;
	volatile unsigned int rcerg;
	volatile unsigned int rcerh;
	volatile unsigned int xcerg;
	volatile unsigned int xcerh;
};

/* ************************************************************************* */
/*
 *	Define Timer/Watchdog register offsets
 *
 */
struct _gpt {
	volatile unsigned int id1;
	volatile unsigned int id2;
	volatile unsigned int emu;
	volatile unsigned int clk;
	volatile unsigned int gpint;
	volatile unsigned int gpen;
	volatile unsigned int gpdat;
	volatile unsigned int gpdir;
	volatile unsigned int cnt1;
	volatile unsigned int cnt2;
	volatile unsigned int cnt3;
	volatile unsigned int cnt4;
	volatile unsigned int prd1;
	volatile unsigned int prd2;
	volatile unsigned int prd3;
	volatile unsigned int prd4;
	volatile unsigned int ctl1;
	volatile unsigned int ctl2;
	volatile unsigned int gctl1;
	volatile unsigned int gwtl1;		/* Watchdog only */
	volatile unsigned int gwtl2;		/* Watchdog only */
};

/* External Bus Selection Register */
#define XBSR		((ioport volatile unsigned int *) 0x6c00)

/* External Bus Control Register */
#define XBCR		((ioport volatile unsigned int *) 0x8800)

/* PLL Clock Mode Control Register */
#define CLKMD_REG	((ioport volatile unsigned int *) 0x8c00)

/* Timer Signal Selection Register */
#define TSSR		((ioport volatile unsigned int *) 0x8000)

/* Timer/Watchdog Registers - 5502*/
#define GPTPID1_0 ((ioport volatile struct _gpt *) 0x1000)
#define GPTPID1_1 ((ioport volatile struct _gpt *) 0x2400)
#define WDTPID1   ((ioport volatile struct _gpt *) 0x4000)

/* DMA Global Timeout Control Register */
#define DMA_GTCR ((ioport volatile unsigned int *) 0x0E01)

/* Parallel General-Purpose I/O Registers */
#define PGPIOEN0	((const ioport volatile unsigned int *) 0x4400)
#define PGPIODIR0	((const ioport volatile unsigned int *) 0x4401)
#define PGPIODAT0	((const ioport volatile unsigned int *) 0x4402)
#define PGPIOEN1	((const ioport volatile unsigned int *) 0x4403)
#define PGPIODIR1	((const ioport volatile unsigned int *) 0x4404)
#define PGPIODAT1	((const ioport volatile unsigned int *) 0x4405)
#define PGPIOEN2	((const ioport volatile unsigned int *) 0x4406)
#define PGPIODIR2	((const ioport volatile unsigned int *) 0x4407)
#define PGPIODAT2	((const ioport volatile unsigned int *) 0x4408)

/* Host Port Interface/General Purpose I/O Registers */
#define HGPIOEN		((ioport volatile unsigned int *) 0xa006)
#define HGPIODIR1	((const ioport volatile unsigned int *) 0xa008)
#define HGPIODAT1	((const ioport volatile unsigned int *) 0xa00a)
#define HGPIOINT1	((ioport volatile unsigned int *) 0xa004)
#define HGPIODIR2	((const ioport volatile unsigned int *) 0xa00c)
#define HGPIODAT2	((const ioport volatile unsigned int *) 0xa00e)
#define HGPIOINT2	((ioport volatile unsigned int *) 0xa005)
#define HGPIODIR3	((const ioport volatile unsigned int *) 0xa010)
#define HGPIODAT3	((const ioport volatile unsigned int *) 0xa012)

#define UART_BASE_CONSOLE			((ioport volatile uint16 *) 0x9c00)

#define UART_IRQ		0x0c

#define UROFF_THR		0		/* Transmitter holding register */
#define UROFF_RBR		0		/* Receiver buffer register */
#define UROFF_DLL		0		/* Divisor latch LSB */
#define UROFF_DLM		1		/* Divisor latch MSB */
#define UROFF_IER		1		/* Interrupt enable register */
#define UROFF_IIR		2		/* Interrupt ident register */
#define UROFF_FCR		2		/* FIFO control register (16550A only) */
#define UROFF_LCR		3		/* Line control register */
#define UROFF_MCR		4		/* Modem control register */
#define UROFF_LSR		5		/* Line status register */
#define UROFF_MSR		6		/* Modem status register */

#define UROFF_SCR		7		/* Not sure */
#define UROFF_PECR		12		/* TI 5501/02 only */

#define PECR_URST		0x8000
#define UART_URLSR_RFIER_ON		0x80

/* ************************************************************************* */
/*
 *	I2C Register Definitions
 *
 */
#define I2COAR
#define I2CSTR
#define I2CCLKL
#define I2CCLKH
#define I2CCNT
#define I2CDRR
#define I2CSAR
#define I2CDXR
#define I2CMDR

#endif /* _INCLUDE_TI5502_H */
