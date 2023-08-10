/*********************************************************************
 *          (C) COPYRIGHT TEXAS INSTRUMENTS, INC. 2000
 * flash.h -- Flash Memory handler info & prototypes.
 */

/* Change Log:
 */
/*
 *$Log$
 *Revision 1.2  2004/03/15 13:14:32  demlr1
 *SCR# 82009
 *Added Intel flash commands.
 *Changed parameters to match flash size.
 *
 *Revision 1.2  2004/03/05 19:57:52  robert.deml
 *no message
 *
 *Revision 1.1.1.1  2004/03/03 20:38:28  robert.deml
 *no message
 *
 *Revision 1.1.1.1  2004/02/04 18:04:53  robert.deml
 *no message
 *
 *Revision 1.3  2003/12/17 15:49:14  terry.sherman
 *Updated flash part size to a 2MB size.
 *
 *Revision 1.2  2003/12/02 18:02:39  robert.deml
 *Fixed 64kW boundary issue.
 *
 *Revision 1.1  2001/02/14 17:13:52  heeschen
 *v00.11 Beta
 *Capturing this new FBTC55 module. Successfully
 *reads/writes flash memory. Untested for bootability
 *of written program.
 *
 */

#ifndef _FLASH_H_
#define _FLASH_H_

#include "type.h"

#define OK          (0)
#define ERROR       (-1)

#define	FLASH_BASE_ADDR		(0x200000)	 //linear base word address
#define bsc_FLASHBASEADDR FLASH_BASE_ADDR
#define FLSIZEBYTES         (0x00200000UL) //2MB Flash Part
#define	FLEND		        (FLASH_BASE_ADDR + FLSIZEBYTES)

/* Reset the flash chip(s) to read state
 */
void flash_reset();


/* Erases entire flash memory.
 */
void chip_erase(void);

/*  Writes a block of data into flash memory. The flash is
 *	addressed with a linear address scheme that addresses the words of the
 *	flash memory as an offset from the start of the flash chip. In other
 *	words, a dest of 0 will result in a write to sector 0, page 0, address
 *	as viewed by the CPU, will be 0x8000.
 *
 *  source is an array of words to be written.
 *	dest is flash destination address
 *	length is in words.
 *
 *  Returns OK or ERROR
 */
int flash_write(u16 *source, u16 *dest, u32 length);

/*
 * sets memory bank appropriately based on passed word address Offset
 */
void bsm_IntelMemBlockSelect(u32 Offset);

#endif

