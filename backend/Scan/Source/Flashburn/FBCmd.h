/*********************************************************************
 *          (C) COPYRIGHT TEXAS INSTRUMENTS, INC. 2000, 2001
 * FBCmd.h -- Process FlashBurn Target Component commands
 *            for 55x DSK
 */

/* Change Log:
 * $Log$
 * Revision 1.1  2004/01/19 21:58:33  perkig2
 * SCR 79555 - Initlal Flashburn code
 *
 * Revision 1.2  2003/12/02 18:04:06  robert.deml
 * Fixed 64kW boundary issue.
 *
 * Revision 1.5  2001/04/19 18:56:50  heeschen
 * v00.30 Alpha - Updated comments
 *
 *
 */

/* Implements FlashBurn communications protocol
 */
 
#include "type.h"



#define ShortsToLong(vHighHalf, vLowHalf)  \
		((long)(((unsigned long)((u16)(vHighHalf)) << 16) | ((unsigned long)((u16)(vLowHalf)))))

#define ShortsToULong(vHighHalf, vLowHalf)  \
		((unsigned long)(((unsigned long)((u16)(vHighHalf)) << 16) | ((unsigned long)((u16)(vLowHalf)))))


/* Given the command message,
 * Carry out the command and prepare response,
 * if any.
 */
u16 doCommand(u16 *msg);


/* --------------------------
 * Prototypes from FBURNCMD.C
*/
	/* Set/Get Flash Memory base address.
	 * The Host may want me to change where
	 * I think the flash memory is, rather
	 * than have me use my hard-coded flash
	 * base address (FLASHBASE in this header
	 * file). It is set in response to a
	 * Set FLASHBASE Address command from Host.
	 */
void SetFlashBase(unsigned long val);
unsigned long GetFlashBase(void);

	/* Set/Get Flash Memory size.
	 * The Host may want me to change how big
	 * I think the flash memory is, rather
	 * than have me use my hard-coded flash
	 * size (FLASHSIZE in this header
	 * file)
	 */
void SetFlashSize(unsigned long val);
unsigned long GetFlashSize(void);

	/* Initialize flash memory pointers
	 * to a known flash memory address
	 */
void InitFlash(void);

	/* Initialize flash memory pointers
	 * to a given address
	 */
void SetFlashAddr(unsigned long addr);

	/* Burn data into flash memory starting
	 * at current flash memory pointer.
	 * Note that bytecount is #of 8-bit bytes.
	 * Thus on 5510 (2 bytes per address unit)
	 * data space indexing is by 16-bit units.
	 */
void BurnFlash(unsigned long byteOffset, u16 *data, u32 nBytes);

	/* Get pointer to next available flash memory
	 * location.
	 */
volatile u16 *GetNextFlashAddr(void);

	/* Erase all of flash memory.
	 */
void EraseFlash();

	/* Called periodically to maintain
	 * the Status Busy Bit when flash
	 * is erasing.
	 */
void CheckFlashErase(void);

	/* Checksum Processing.
	 * A simple modulo-16 additive cksum
	 * which adds the carry bit back into
	 * the accumulator.
	 */
	 /* Initialize to a value */
void CKSSet(u16 val);
	 /* Returns the current value */
u16 CKSGet(void);
	 /* Accumulate a buffer */
u16 CKSAccumBuf(unsigned long byteOffset, unsigned long len);
 	/* Return flash contents */
u16 GetFlashVal(unsigned long addr);
	/* Sends a block of flash bytes to host
	 */
void SendFlashBufToHost(u16 cmd, unsigned long addr, u16 count);
