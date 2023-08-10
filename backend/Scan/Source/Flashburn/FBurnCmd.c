/*
 * ----------------------------------------------------
 *          (C) COPYRIGHT TEXAS INSTRUMENTS, INC. 2000, 2001
 * FlashBurn Programming Functions
 *   for FBTC55
 * ----------------------------------------------------
 * $Log$
 * Revision 1.1  2004/01/19 21:58:33  perkig2
 * SCR 79555 - Initlal Flashburn code
 *
 * Revision 1.2  2003/12/02 18:03:13  robert.deml
 * Fixed 64kW boundary issue.
 *
 * Revision 1.5  2001/04/19 18:56:50  heeschen
 * v00.30 Alpha - Updated comments
 *
 *
 */
#include <stdio.h>
#include "fbtc55.h" 
#include "fbcmd.h"
#include "flash.h" 


static void AdjustOddAddress(unsigned long byteOffset, u16 *pdata, u16 nBytes);


	/* Non-zero if flash is erasing.
	 * Changes to zero when we determine
	 * that erasure is complete.
	 */
static int ErsStatus = 0;

    /* flashstart and flashnext are used to track
     * where we are in a "flat" Flash memory.
     * Paging, etc. are handled by helper funcs.
     * flashbaseoverride is 0 normally, but changes
     * if Host sends the Change FLASHSTART Address command.
     * Thus if it's not 0xffffffff, then it should be used
     * instead of the FLBASE value. 
     */  
static unsigned long flashstart = FLASH_BASE_ADDR;
static unsigned long flashnext =  FLASH_BASE_ADDR;

	/* These are "override" values, in case the
	 * Host has sent new flash base addr and size.
	 */
static unsigned long flashbaseov = 0xffffffffL;
static unsigned long flashsizeov = 0xffffffffL;

/* Set and get the flash base address
 */
void SetFlashBase(unsigned long val)
{
	flashbaseov = val;
}

unsigned long GetFlashBase(void)
{
	return flashbaseov != 0xffffffffL ? flashbaseov : FLASH_BASE_ADDR;
}

/* Set and get the flash size
 */
void SetFlashSize(unsigned long val)
{
	flashsizeov = val;
}

unsigned long GetFlashSize(void)
{
	return flashsizeov != 0xffffffffL ? flashsizeov : FLSIZEBYTES;
}


/* --------------------------------
 * Flash memory handlers
 * --------------------------------
 */
void InitFlash(void)
{
	flashstart = GetFlashBase();
	flashnext = flashstart;
}

void SetFlashAddr(unsigned long addr)
{
	flashstart = addr;
	flashnext = flashstart;
}


volatile u16 *GetNextFlashAddr(void)
{
	return (volatile u16 *)flashnext;
}

/* Flash is accessed via external memory.
 * For the AMD Flash (Am29LV400),
 * program 1 word at a time.
 */
void BurnFlash(unsigned long byteOffset, u16 *pdata, u32 nBytes)
{
	u32 nWords;

	if(nBytes == 0)
		return;
		
	if((byteOffset & 1ul) != 0)   // odd address?
	{
		/* Write the odd byte from the beginning
		 * of the data and shift all the others down
		 * so I can write whole words after this.
		 */
		AdjustOddAddress(byteOffset, pdata, nBytes);
		nBytes -= 1;
		byteOffset += 1;
	}
	
	SetFlashAddr(GetFlashBase() + byteOffset / 2);

	nWords = nBytes / 2;
		
	if(nWords > 0)
	{
		flash_write(pdata, (u16 *)flashnext, nWords);
		flashnext += nWords; /* For next time */
		pdata += nWords;
	}

	/* Write the odd byte at the end, if any.
	 */	
	if((nBytes & 1) != 0)
	{
		/* Write the spare byte: read/modify/write its
		 * containing word.
		 */
		u16 fval = *((u16 *)flashnext);
		fval &= 0x00ff;
		fval |= *pdata & 0xff00;

		flash_write(&fval, (u16 *)flashnext, 1);
	}
	
	return;
}

/* Called when byteOffset is odd.
 * Writes the 1st 8-bit byte at pdata
 * to flash using read/modify/write,
 * then shifts the rest of the data
 * down 1 byte so I write the rest on
 * word boundaries.
*/	
static void AdjustOddAddress(unsigned long byteOffset, u16 *pdata, u16 nBytes)
{
	int i;
	u16 myWord;
	
	SetFlashAddr(GetFlashBase() + byteOffset / 2);
	
	myWord = *((u16 *)flashnext);
	myWord &= 0xff00;
	myWord |= (*pdata) >> 8;
	flash_write(&myWord, (u16 *)flashnext, 1);
	flashnext += 1;
	
	nBytes -= 1;

	for(i=0; i<nBytes; i+=2)
	{
		myWord = *pdata << 8;
		myWord |= *(pdata+1) >> 8;
		*pdata++ = myWord;
	}
}


void CheckFlashErase(void)
{
	if(ErsStatus != 0)
	{
		if(*((u32 *)FLASH_BASE_ADDR) == 0xffffffff)
		{
			ErsStatus = 0;
		}
	}
}

void EraseFlash(void)
{
	chip_erase();

 	ErsStatus = 1;
 	
 	while(ErsStatus == 1)
 	{
 		CheckFlashErase();
 	}
	
	return;
}
 

static unsigned long cksum = 0;

void CKSSet(u16 val)
{
	cksum = val;
}
	
u16 CKSGet(void)
{
	return (u16)cksum;
}

	/* buf is start address in flash memory,
	 * len is length in BYTES!
	 */	
u16 CKSAccumBuf(unsigned long byteOffset, unsigned long nBytes)
{	
	u16 val, nWords;
//	u16 *pflash = (u16 *)(GetFlashBase() + byteOffset / 2);
	
	u32 flash = GetFlashBase() + byteOffset/2;
	
	if((byteOffset & 1) != 0)
	{
//		cksum += *pflash & 0x00ff;
		cksum += *(u16*)flash & 0x00ff;
		if(cksum >= 65536)
		{
			cksum += 1;
			cksum &= 0xffff;
		} 
		nBytes -= 1;
		byteOffset += 1;
//		pflash++;
		flash++;
	}
	
	nWords = nBytes / 2;  // data is word addressable
	
	while(nWords-- > 0)
	{
//		val = *pflash++;
		val = *(u16*)flash; flash++;
		cksum += val >> 8;
		if(cksum >= 65536)
		{
			cksum += 1;
			cksum &= 0xffff;
		} 
		cksum += val & 0x000000ff;
		if(cksum >= 65536)
		{
			cksum += 1;
			cksum &= 0xffff;
		} 
	}
	
	if((nBytes & 1) != 0)
	{
//		cksum += *pflash >> 8;
		cksum += *(u16*)flash >> 8;
		if(cksum >= 65536)
		{
			cksum += 1;
			cksum &= 0xffff;
		} 
	}

	return (u16)cksum;
}

u16 GetFlashVal(unsigned long addr)
{
	return *((u16 *)addr);
}

void SendFlashBufToHost(u16 cmd, unsigned long addr, u16 bytecount)
{
	u16 *pflash = (u16 *)addr;
	u16 *pmsgdata = GetData();
	u16 i, n;

	/* Prep header
	 */
	StoreCmd(cmd);     
	StoreArg(0, bytecount);

	n = (bytecount+1) / BYTESPERMAU;
	for(i=0; i<n; i+=1)
    {
		*pmsgdata++ = *pflash++;
	}
}

