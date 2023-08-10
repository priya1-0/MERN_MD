/*********************************************************************
 *          (C) COPYRIGHT TEXAS INSTRUMENTS, INC. 2000, 2001
 * flash.c -- Flash Memory handlers for dsk 5510
 */

/* Change Log:
 */
/*
 * $Log$
 * Revision 1.2  2004/03/15 13:14:06  demlr1
 * SCR# 82009
 * Added Intel flash commands.
 *
 * Revision 1.2  2004/03/05 19:57:56  robert.deml
 * no message
 *
 * Revision 1.1.1.1  2004/03/03 20:38:24  robert.deml
 * no message
 *
 * Revision 1.1.1.1  2004/02/04 18:04:52  robert.deml
 * no message
 *
 * Revision 1.3  2003/12/02 19:42:29  robert.deml
 * Added code for Intel.
 *
 * Revision 1.2  2003/12/02 18:02:54  robert.deml
 * Fixed 64kW boundary issue.
 *
 * Revision 1.3  2001/06/27 17:55:14  heeschen
 * v00.32 Beta Prep
 * Capturing all files to prepare for Beta Release
 *
 * Revision 1.2  2001/04/19 18:56:50  heeschen
 * v00.30 Alpha - Updated comments
 *
 *
 */
#include <std.h>
#include <csl.h>
#include <csl_gpio.h>
#include  "flash.h"
#include "global.h"


#define	FCP5			(FLASH_BASE_ADDR+(0x5555ul))		//flash command port 5
#define	FCPA			(FLASH_BASE_ADDR+(0x2aaaul))		//flash command port A
#define	FCW5			0x5555u
#define	FCWA			0xAAAAu
#define	FWORDWRITE		0x00A0u

#if defined SST_FLASH
	#define	FRESET			0xF0u
#elif defined INTEL_FLASH
	#define	FRESET			0xFFu
#endif

#define	FCHIPERASE0		0x8080u
#define	FCHIPERASE1		0x1010u
#define	FSECTORERASE0	0x80u
#define	FSECTORERASE1	0x30u
#define	FCHIPID			0x90u

#define INTEL_CMD_UNLOCK_1        (0x60)//The first command given in the two-cycle UNLOCK sequence
#define INTEL_CMD_UNLOCK_2        (0xD0)//The second command given in the two-cycle UNLOCK sequence.  

#define	DQ7				(1u<<7)
#define	DQ6				(1u<<6)
#define	DQ5				(1u<<5)
#define	DQ3				(1u<<3)
#define	DQ2				(1u<<2)


#define SR7 (0x80) // Write Machine STATUS 1 = Ready;                   0 = Busy 
#define SR6 (0x40) // ERASE SUSPEND STATUS 1 = ERASE suspended;         0 = ERASE in progress/completed 
#define SR5 (0x20) // ERASE STATUS         1 = BLOCK ERASE;             0 = Successful BLOCK ERASE
#define SR4 (0x10) // WRITE STATUS         1 = WORD/BYTE WRITE error;   0 = Successful WORD/BYTE WRITE 
#define SR3 (0x08) // VPP STATUS           1 = No VPP voltage detected; 0 = VPP present 
#define SR2 (0x04) // WRITE SUSPEND STATUS 1 = WRITE suspended;         0 = WRITE in progress/completed 
#define SR1 (0x02) // BLOCK LOCK STATUS    1 = Block is locked;         0 = Block not locked 	 


#define INTEL_CMD_READ_ARRAY      (0xFF)//Must be issued after any other command cycle before 
                                        //array can be read.
#define INTEL_CMD_READ_IDENTIFIER (0x90)//Puts the device into the read-identifier mode so that 
                                        //reading the device will output the manufacturer/device 
                                        //codes or block-lock status.
#define INTEL_CMD_READ_STATUS     (0x70)//Allows the status register to be read. 
#define INTEL_CMD_CLEAR_STATUS    (0x50)//Clears status register bits 3-5.
#define INTEL_CMD_WRITE           (0x40)//Write data and address are given in the following cycle 
                                        //to complete the WRITE.
#define INTEL_CMD_ERASE_1         (0x20)//The first command given in the two-cycle ERASE sequence. 
#define INTEL_CMD_ERASE_2         (0xD0)//The second command given in the two-cycle ERASE sequence. 

//Block Layout 1MB
#define INTEL_BLCK_NUMBLOCKS  (63)
#define INTEL_SECT_NUMBLOCKS  (8)

//General block information
#define INTEL_BLCK_NUMWORDS   (32768)/* words per block */ 
#define INTEL_SECT_NUMWORDS   (4096) /* words per block */
#define INTEL_TOTAL_NUMBLOCKS (INTEL_BLCK_NUMBLOCKS +INTEL_SECT_NUMBLOCKS)

#define UNLOCK_LOCATION       (0x0001)
#define UNLOCK_STATUS_MASK    (0x0001)
#define UNLOCK_STATUS_DESIRED (0x0000)


// bank select defines
#define BANKSELECT		GPIO_PIN4  // bit mask for I/O pin
#define BANKADDR        _GPIO_IODATA  //register of I/O pins
#define BANKDIR         _GPIO_IODIR   //register for the direction

// macros to clear and set the GPIO4 pin, used to select the upper two flash banks
#define SetUpperBank(x)    BANKADDR = (x) ? (BANKADDR | BANKSELECT): (BANKADDR & ~(BANKSELECT))


#if defined INTEL_FLASH
static unsigned long glbbaseaddr = FLASH_BASE_ADDR;
#endif

//local function protocols
#if defined INTEL_FLASH
static char bsm_Intel_Erase_BLCK(u32 Offset);
#endif

u32 bsm_Intel_Get_Block_Address(u32 Offset);
BOOL bsm_Intel_UnlockBlock(u32 Offset);
BOOL bsm_Intel_UnlockALLBlocks(void);
void bsm_IntelMemBlockSelect2(u32 Offset);

#if defined SST_FLASH
static int waitFor16bitCompletion(volatile u16 *s, u16 value);
#endif

/* Reset the Flash Memory. Places chip in read mode
 */ 
void flash_reset()
{
#if defined SST_FLASH
	/* 2 chips 16 bits wide: 32 bits.
	 */
	*(volatile u32 *)FLASH_BASE_ADDR = FRESET;
#elif defined INTEL_FLASH
    // the Flash should be in Read mode by default
	*(volatile u32 *)FLASH_BASE_ADDR = FRESET;
	
	
	//initialize the Flash Memory bank select lines
	BANKDIR |= BANKSELECT;
	bsm_IntelMemBlockSelect(0);
#endif
}


/* Writes length words from source to dest in flash.
 */
int flash_write(u16 *source, u16 *dest, u32 length)
{
	u16 *pdst;// = dest;
	u16 *psrc;// = source;
	u32	i,len = length;
#if defined SST_FLASH
    u16 j;
#endif
    u32 src;
    u32 dst;
#if defined INTEL_FLASH
    u16 Status;
#endif
    
    src = (u32)source;
    dst = (u32)dest;
         
		 asm ("	NOP");
		 asm ("	NOP");
		 asm ("	NOP");
		 asm ("	NOP");
		 asm ("	NOP");
	for(i = 0; i < len; i++) 
	{
		pdst = (u16*)dst;
		psrc = (u16*)src;

#if defined SST_FLASH

		*(volatile u16 *)FCP5 = FCWA;
		
		*(volatile u16 *)FCPA = FCW5;
		
		*(volatile u16 *)FCP5 = FWORDWRITE;
		
		*pdst = *psrc;

        for (j = 0; j < 10; j++);
        
		while(1)
		    if (*pdst == *psrc)
		        break;
		
		if (waitFor16bitCompletion((volatile u16 *)pdst, *psrc) == ERROR) 
			return ERROR;

#elif defined INTEL_FLASH
		
		//glbbaseaddr =  GetFlashBase();
		
         bsm_IntelMemBlockSelect2(dst- glbbaseaddr);  //fix for hardware problem
		*pdst = INTEL_CMD_WRITE; //Issue first write command
		 asm ("	NOP");
		 asm ("	NOP");
		 asm ("	NOP");
		 asm ("	NOP");
		 asm ("	NOP");
		 asm ("	NOP");
		 asm ("	NOP");
		 asm ("	NOP");
		 asm ("	NOP");
		 asm ("	NOP");
		 
		 
		 
	    *pdst = *psrc; //Issue actual write
	    asm ("	NOP");
		 asm ("	NOP");
		 asm ("	NOP");
		 asm ("	NOP");
		 asm ("	NOP");
		 asm ("	NOP");
		 asm ("	NOP");
		 asm ("	NOP");
		 asm ("	NOP");
		 asm ("	NOP");

        *(u16*)((u32)FLASH_BASE_ADDR) = INTEL_CMD_READ_STATUS;//Initiate read status register
	    do{
	        Status = *(u16*)((u32)FLASH_BASE_ADDR);
	    }while( (Status & SR7) != SR7);

	    if( (Status & SR3) != 0){
	        // Vpp Error
	        *(u16*) ((u32)FLASH_BASE_ADDR) = INTEL_CMD_CLEAR_STATUS; //Clear status because Flash can't clear this bit itself
	    }

        if( (Status & SR4) != 0){
            // Program(Write) Error
            *(u16*)((u32)FLASH_BASE_ADDR) = INTEL_CMD_CLEAR_STATUS; //Clear status because Flash can't clear this bit itself
        }

	    if( (Status & SR1) != 0){
	        //Block Locked Error
	        *(u16*)((u32)FLASH_BASE_ADDR) = INTEL_CMD_CLEAR_STATUS; //Clear status because Flash can't clear this bit itself
	    }

	    // the Flash should be in Read mode by default
	    *(u16*)((u32)FLASH_BASE_ADDR) = INTEL_CMD_READ_ARRAY; //Issue the read array command for subsequent reads.
	   
	    if (*pdst != *psrc)
	    {
	        asm ("	NOP");
	    }
	    
#endif
		
			
		dst++;
		src++;
	}
	return OK;
}
/******************************************************************

FUNCTION: bsm_IntelMemBlockSelect

DESCRIPTION:  Selects the appropriate memory bank based on the
              passed value.  A bank selects a 2Mbyte addressable
              portion of the flash.  
              Currently four banks are supported.  
              Any address above the 4*2Mbyte boundary of Bank 3 
              is assumed to lie within Bank 3 anyway.

ARGS:
	UINT32  Offset: Offset into the Flash for which the bank is
                    to be selected.

RETURNS:
    <none>
    
******************************************************************/
void bsm_IntelMemBlockSelect(u32 Offset)
{
    u16 bank = (Offset >> 20) & 7;
	if ( bank >= 4 ) bank = 3;
	switch( bank )
	{
		case 0: GLB_CLR_XF; BANKADDR = BANKADDR & ~(BANKSELECT); break;
		case 1: GLB_SET_XF; BANKADDR = BANKADDR & ~(BANKSELECT); break;
		case 2: GLB_CLR_XF; BANKADDR = BANKADDR | (BANKSELECT); break;
		case 3: 
		default: GLB_SET_XF; BANKADDR = BANKADDR | (BANKSELECT); break;
	}
}

void bsm_IntelMemBlockSelect2(u32 Offset)
{
    u16 bank = (Offset >> 20) & 7;
	if ( bank >= 4 ) bank = 3;
	switch( bank )
	{
		case 0: GLB_SET_XF; BANKADDR = BANKADDR & ~(BANKSELECT); break;
		case 1: GLB_CLR_XF; BANKADDR = BANKADDR & ~(BANKSELECT); break;
		case 2: GLB_CLR_XF; BANKADDR = BANKADDR | (BANKSELECT); break;
		case 3: 
		default: GLB_SET_XF; BANKADDR = BANKADDR | (BANKSELECT); break;
	}
}


/****************************************************************************
FUNCTION: bsm_Intel_Get_Block_Address(Offset)

DESCRIPTION: This procedure determines the starting block address of the block
             containing the passed offset

ARGS:
    UINT32 Offset: Offset into the Flash to erase, Defines Block

RETURNS:   
	UINT32: Starting address of block
 ***************************************************************************/
u32 bsm_Intel_Get_Block_Address(u32 Offset){
	u32 temp;
	
	// get the block number if the block is fullsize block
	temp = Offset / INTEL_BLCK_NUMWORDS;
	if(temp >= INTEL_BLCK_NUMBLOCKS )
	{
		//. Address not within full-size block addresses
		temp = Offset - (INTEL_BLCK_NUMWORDS * INTEL_BLCK_NUMBLOCKS);		
		temp = temp / INTEL_SECT_NUMWORDS;
		if(temp >= INTEL_SECT_NUMBLOCKS )
		{
			//Address out of range, return what waqs passed in
			temp = Offset;
		}
		else
		{
			// Address is within small-size block addresses
			//Determine starting address
			temp = temp * INTEL_SECT_NUMWORDS;
			
			//add back in offset to the small-blocks
			temp += INTEL_BLCK_NUMWORDS * INTEL_BLCK_NUMBLOCKS;

		}
	}
	else
	{
		// Address is within full-size block addresses
		// Determine starting address
		temp = temp * INTEL_BLCK_NUMWORDS;	
	}

	return temp;
}


/******************************************************************

FUNCTION: bsm_Intel_UnlockBlock

DESCRIPTION: This function unlocks the specified block on the flash
             device 

ARGS:
	u32 Offset: Offset into the Flash to erase, Defines Block
RETURNS:   
        BOOL: TRUE if success, 
              FALSE otherwise
Assumptions:
    The block indicated was previously locked.
    
******************************************************************/
BOOL bsm_Intel_UnlockBlock(u32 Offset)
{
//	GLB_HTMR_OBJ base;
	BOOL   status;
	u32 blockStart;
	u16 temp;

    bsm_IntelMemBlockSelect(Offset);
    
	blockStart = bsm_Intel_Get_Block_Address(Offset);
//	GLB_GET_HTMR(base); //get base time	

	status = FALSE;
	do{
    	*(u16*)((u32)bsc_FLASHBASEADDR + Offset) = INTEL_CMD_UNLOCK_1; //1st unlock command
    	*(u16*)((u32)bsc_FLASHBASEADDR + Offset) = INTEL_CMD_UNLOCK_2; //2nd unlock command
    
    			
    	/*check the protection status of the block */
    	temp = *(u16*)(blockStart + (u32)UNLOCK_LOCATION);
    	temp = temp & UNLOCK_STATUS_MASK;
    	if(temp == UNLOCK_STATUS_DESIRED)
    		status = TRUE;
    	else
    		status = FALSE;
    }
    while(status != TRUE);	
//	while((GLB_HAS_LTMR_EXPIRED(base, (u32)INTEL_WRITE_TIME) != TRUE) && status != TRUE);

    // the Flash should be in Read mode by default
    *(u16*)((u32)bsc_FLASHBASEADDR) = INTEL_CMD_READ_ARRAY; //Issue the read array command for subsequent reads.
    
    return status;
}





/*****************************************************
 *  int chip_erase()
 *  
 *  This function commands an entire flash erasure
 *  returns immediately. Use checkFor32bitCompletion()
 *  to see when erasing is complete.
 *
 *  Parameters:
 *      none
 * 
 *  Return:
 *  - OK success
 *  - ERROR failure
 * 
 *  Notes:
 * 
 */
void chip_erase(void)
{
#if defined SST_FLASH
	*(volatile u16 *)FCP5 = FCWA;
	*(volatile u16 *)FCPA = FCW5;
	*(volatile u16 *)FCP5 = FCHIPERASE0;

	*(volatile u16 *)FCP5 = FCWA;
	*(volatile u16 *)FCPA = FCW5;
	*(volatile u16 *)FCP5 = FCHIPERASE1;
#elif defined INTEL_FLASH
    u32 offset = 0;
    u16 block;  

     bsm_Intel_UnlockALLBlocks();
     
    //Erase BLCK size blocks first
    for (block=0; block < INTEL_BLCK_NUMBLOCKS; block++ )
    {
        //if(bsm_Intel_UnlockBlock(offset) == FALSE){
          //  return;
        //}
        if(bsm_Intel_Erase_BLCK(offset) == FALSE){
            return;
        }
        offset += INTEL_BLCK_NUMWORDS;
    }

    //Now Erase SECT size blocks first
    for (block=0; block < INTEL_SECT_NUMBLOCKS; block++ )
    {
        //if(bsm_Intel_UnlockBlock(offset) == FALSE){
          //  return;
        //}
        if(bsm_Intel_Erase_BLCK(offset) == FALSE){
            return;
        }
        offset += INTEL_SECT_NUMWORDS;
    }

#endif			
	return;
}

/****************************************************************************
FUNCTION: bsm_Intel_UnlockALLBlocks

DESCRIPTION: This procedure is called to unlock all data blocks on the flash 
              device. 

ARGS:
    <none>

RETURNS:   
        BOOL: TRUE if success, 
              FALSE otherwise
 ***************************************************************************/
BOOL bsm_Intel_UnlockALLBlocks( void ){
    u32 offset;
    u16 block;  

	offset = 0;
    /* Erase BLCK size blocks first*/
    for ( block=0; block < INTEL_BLCK_NUMBLOCKS; block++ ){
        if(bsm_Intel_UnlockBlock(offset) == FALSE){
            return FALSE;
        }
        offset += INTEL_BLCK_NUMWORDS;
    }

    /* Now Erase SECT size blocks first*/
    for ( block=0; block < INTEL_SECT_NUMBLOCKS; block++ ){
        if(bsm_Intel_UnlockBlock(offset) == FALSE){
            return FALSE;
        }
        offset += INTEL_SECT_NUMWORDS;
    }

    return TRUE;
}
/*************
 * Local Funcs
 *************
 */
#if defined INTEL_FLASH
char bsm_Intel_Erase_BLCK(u32 Offset)
{
	u16 Status;
	
    bsm_IntelMemBlockSelect(Offset);
    *(u16*)((u32)FLASH_BASE_ADDR + Offset) = INTEL_CMD_ERASE_1; //Do first erase command
    *(u16*)((u32)FLASH_BASE_ADDR + Offset) = INTEL_CMD_ERASE_2; //Do Second erase command, offset is within block to erase

    //Poll the status register
    *(u16*)((u32)FLASH_BASE_ADDR) = INTEL_CMD_READ_STATUS;//Initiate read status register
    do{
        Status = *(u16*)((u32)FLASH_BASE_ADDR);
    }while( (Status & SR7) != SR7 );
    
    if( (Status & SR3) != 0){
        // Vpp Error
        *(u16*)((u32)FLASH_BASE_ADDR) = INTEL_CMD_CLEAR_STATUS; //Clear status because Flash can't clear this bit itself
        return FALSE;
    }
    if( (Status & SR4) != 0 && (Status & SR5) != 0){
        //SR[4,5]=(1,1)
        //Command Sequence Error
        *(u16*)((u32)FLASH_BASE_ADDR) = INTEL_CMD_CLEAR_STATUS; //Clear status because Flash can't clear this bit itself
        return FALSE;
    }
    if( (Status & SR5) != 0){
        //Block Erase Error
        *(u16*)((u32)FLASH_BASE_ADDR) = INTEL_CMD_CLEAR_STATUS; //Clear status because Flash can't clear this bit itself
        return FALSE;
    }
    

    if( (Status & SR1) != 0){
        //Block Locked Error
        *(u16*)((u32)FLASH_BASE_ADDR) = INTEL_CMD_CLEAR_STATUS; //Clear status because Flash can't clear this bit itself
        return FALSE;
    }
    
    // the Flash should be in Read mode by default
    *(u16*)((u32)FLASH_BASE_ADDR) = INTEL_CMD_READ_ARRAY; //Issue the read array command for subsequent reads.

    return TRUE;//No Error detected
}
#endif

/*  Waits for the flash operation to complete.
 *
 * s - pointer to location to compare to value
 * value - value to compare to data stored in location pointedt to by s
 * 
 *  Returns OK if success, else ERROR
 */ 

#if defined SST_FLASH
int waitFor16bitCompletion(volatile u16 *s, u16 value)
{
	while(1)
	{
		if ((*s & DQ7) == (value & DQ7))
			return OK;
		
		if (*s & DQ5)
		{
			return ((*s & DQ7) == (value & DQ7)) ? OK : ERROR;
		}
	}
}

#endif			
