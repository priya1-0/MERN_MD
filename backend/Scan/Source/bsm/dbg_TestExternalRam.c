/************************************************************************
*
* MODULE: dbg_TestExternalRam.c
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the functions for testing the SDRAM.
*
*************************************************************************/

/////////////
// Includes
/////////////
#include <csl.h>
#include <csl_dma.h>
#include "global.h"
#include "bsm_serialport.h"
#include "bsm_general.h"

////////////
// Defines
////////////

// Memory boundaries in 16-bit words
#define SDRAM_BEGIN 0x0400000
#define SDRAM_SIZE  (0x0400000-0x4000)                     // subtract 16k words for the ROM

// number of bytes to test at a time.  WARNING - Do not make this number very
// large because 2 arrays of this size are put on the stack.
#define SDRAM_TEST_BLOCK_SIZE 16

// Defines for the SDRAM Test
#define RamTest_CopyToDaramSDP DMA_DMACSDP_RMK( \
        DMA_DMACSDP_DSTBEN_NOBURST, \
        DMA_DMACSDP_DSTPACK_OFF, \
        DMA_DMACSDP_DST_DARAMPORT1, \
        DMA_DMACSDP_SRCBEN_NOBURST, \
        DMA_DMACSDP_SRCPACK_OFF, \
        DMA_DMACSDP_SRC_EMIF, \
        DMA_DMACSDP_DATATYPE_32BIT \
        )
#define RamTest_CopyToDaramCCR DMA_DMACCR_RMK( \
        DMA_DMACCR_DSTAMODE_POSTINC, \
        DMA_DMACCR_SRCAMODE_POSTINC, \
        DMA_DMACCR_ENDPROG_ON, \
        DMA_DMACCR_REPEAT_OFF, \
        DMA_DMACCR_AUTOINIT_OFF, \
        DMA_DMACCR_EN_STOP, \
        DMA_DMACCR_PRIO_HI, \
        DMA_DMACCR_FS_DISABLE, \
        DMA_DMACCR_SYNC_NONE \
        )
#define RamTest_SetSdramSDP    DMA_DMACSDP_RMK( \
        DMA_DMACSDP_DSTBEN_NOBURST, \
        DMA_DMACSDP_DSTPACK_OFF, \
        DMA_DMACSDP_DST_EMIF, \
        DMA_DMACSDP_SRCBEN_NOBURST, \
        DMA_DMACSDP_SRCPACK_OFF, \
        DMA_DMACSDP_SRC_DARAMPORT1, \
        DMA_DMACSDP_DATATYPE_32BIT \
        )
#define RamTest_SetSdramCCR    DMA_DMACCR_RMK( \
        DMA_DMACCR_DSTAMODE_POSTINC, \
        DMA_DMACCR_SRCAMODE_CONST, \
        DMA_DMACCR_ENDPROG_ON, \
        DMA_DMACCR_REPEAT_OFF, \
        DMA_DMACCR_AUTOINIT_OFF, \
        DMA_DMACCR_EN_STOP, \
        DMA_DMACCR_PRIO_HI, \
        DMA_DMACCR_FS_DISABLE, \
        DMA_DMACCR_SYNC_NONE \
        )
#define RamTest_CopyToSdramSDP DMA_DMACSDP_RMK( \
        DMA_DMACSDP_DSTBEN_NOBURST, \
        DMA_DMACSDP_DSTPACK_OFF, \
        DMA_DMACSDP_DST_EMIF, \
        DMA_DMACSDP_SRCBEN_NOBURST, \
        DMA_DMACSDP_SRCPACK_OFF, \
        DMA_DMACSDP_SRC_DARAMPORT1, \
        DMA_DMACSDP_DATATYPE_32BIT \
        )
#define RamTest_CopyToSdramCCR DMA_DMACCR_RMK( \
        DMA_DMACCR_DSTAMODE_POSTINC, \
        DMA_DMACCR_SRCAMODE_POSTINC, \
        DMA_DMACCR_ENDPROG_ON, \
        DMA_DMACCR_REPEAT_OFF, \
        DMA_DMACCR_AUTOINIT_OFF, \
        DMA_DMACCR_EN_STOP, \
        DMA_DMACCR_PRIO_HI, \
        DMA_DMACCR_FS_DISABLE, \
        DMA_DMACCR_SYNC_NONE \
        )

/////////////////////
// Local Prototypes
/////////////////////
BOOL TestSdramWithDma(void);



/******************************************************************

FUNCTION: TestSdram

DESCRIPTION: This function tests all of the SDRAM.

ARGS:
        <none>

RETURNS:
    BOOL: TRUE is all RAM locations pass
          FALSE if 1 RAM location fails

******************************************************************/
BOOL TestSdram(void)
{
    // These variables are declared in the linker file
    extern UINT16 run_start_of_sdramtest;
    extern UINT16 load_start_of_sdramtest;
    extern UINT16 size_of_sdramtest;

    // create pointers to the source and destination
    UINT32 RunStart = (UINT32)(((UINT32)(&run_start_of_sdramtest))/2);
    UINT32 LoadStart= (UINT32)(((UINT32)(&load_start_of_sdramtest))/2);
    UINT16 Size     = (UINT16)(((UINT32)(&size_of_sdramtest+1))/2);

    BOOL Result;

    bsm_CopyCode(LoadStart, RunStart, Size);

    bsm_SDPrint("Testing SDRAM...");

    if( TestSdramWithDma() )
    {
        bsm_SDPrint("SDRAM Passed");
        Result = TRUE;
    }
    else
    {
        bsm_SDPrint("SDRAM Failed");
        Result = FALSE;
    }

    return Result;
}

/******************************************************************

FUNCTION: TestSdramWithDma

DESCRIPTION: This function tests all the external SDRAM locations.

ARGS:
        <none>

RETURNS:
    TRUE if all SDRAM locations pass.
    FALSE if a SDRAM location fails.

******************************************************************/
#pragma CODE_SECTION(TestSdramWithDma, ".sdram_test_code")
BOOL TestSdramWithDma(void)
{
    // a place to save the data
    UINT32 SavedData[SDRAM_TEST_BLOCK_SIZE];

    // a place to hold data to check
    UINT32 CheckData[SDRAM_TEST_BLOCK_SIZE];

    // the next address to start checking
    UINT32 NextAddress;

    // a variable set to 0xAAAAAAAA to write to SDRAM
    UINT32 hexAAAA = 0xAAAAAAAA;

    // a variable set to 0x55555555 to write to SDRAM
    UINT32 hex5555 = 0x55555555;

    // variable to run through the checked data
    UINT16 i;

    // the number of bytes to check this scan
    UINT16 SizeToCheck;

    NextAddress = SDRAM_BEGIN;

    while( NextAddress < SDRAM_BEGIN + SDRAM_SIZE )
    {
        // if we can't do a full copy/check...
        if( NextAddress + SDRAM_TEST_BLOCK_SIZE > SDRAM_BEGIN + SDRAM_SIZE )
        {
            SizeToCheck = SDRAM_BEGIN + SDRAM_SIZE - NextAddress;
        }
        // otherwise, do a full block copy/check
        else
        {
            SizeToCheck = SDRAM_TEST_BLOCK_SIZE;
        }

        // Disable interrupt so BIOS does not interfere.  Interrupts are turned off while 1 block of RAM is checked.
        DISABLE_INTERRUPTS;

        // configure the DMA to copy the data to SavedData
        DMA_RSET(DMACSDP5, RamTest_CopyToDaramSDP);
        DMA_RSET(DMACCR5, RamTest_CopyToDaramCCR);
        DMA_RSET(DMACICR5, 0x00);         // turn off all the interrupts
        DMA_RSET(DMACSSAL5, (Uint16)(((Uint32)(NextAddress)<<1)&0x00FFFF));
        DMA_RSET(DMACSSAU5, (Uint16)((((Uint32)(NextAddress)<<1)&0xFF0000) >> 16));
        DMA_RSET(DMACDSAL5, (Uint16)(((Uint32)(&SavedData)<<1)&0x00FFFF));
        DMA_RSET(DMACDSAU5, (Uint16)((((Uint32)(&SavedData)<<1)&0xFF0000) >> 16));
        DMA_RSET(DMACEN5, SizeToCheck);
        DMA_RSET(DMACFN5, 1);

        // Start the DMA
        DMA_RGET(DMACSR5);
        DMA_FSET(DMACCR5,EN,1);

        // wait for the DMA to transfer the block
        while( (DMA_RGET(DMACSR5) & 0x20) == 0x00 )
        {
        }

        // set the DMA to set the SDRAM to 0xAAAA
        DMA_RSET(DMACSDP5, RamTest_SetSdramSDP);
        DMA_RSET(DMACCR5, RamTest_SetSdramCCR);
        DMA_RSET(DMACSSAL5, (Uint16)(((Uint32)(&hexAAAA)<<1)&0x00FFFF));
        DMA_RSET(DMACSSAU5, (Uint16)((((Uint32)(&hexAAAA)<<1)&0xFF0000) >> 16));
        DMA_RSET(DMACDSAL5, (Uint16)(((Uint32)(NextAddress)<<1)&0x00FFFF));
        DMA_RSET(DMACDSAU5, (Uint16)((((Uint32)(NextAddress)<<1)&0xFF0000) >> 16));

        // Start the DMA
        DMA_RGET(DMACSR5);
        DMA_FSET(DMACCR5,EN,1);

        // wait for the DMA to transfer the block
        while( (DMA_RGET(DMACSR5) & 0x20) == 0x00 )
        {
        }

        // copy the data from SDRAM to SARAM for checking
        DMA_RSET(DMACSDP5, RamTest_CopyToDaramSDP);
        DMA_RSET(DMACCR5, RamTest_CopyToDaramCCR);
        DMA_RSET(DMACSSAL5, (Uint16)(((Uint32)(NextAddress)<<1)&0x00FFFF));
        DMA_RSET(DMACSSAU5, (Uint16)((((Uint32)(NextAddress)<<1)&0xFF0000) >> 16));
        DMA_RSET(DMACDSAL5, (Uint16)(((Uint32)(&CheckData)<<1)&0x00FFFF));
        DMA_RSET(DMACDSAU5, (Uint16)((((Uint32)(&CheckData)<<1)&0xFF0000) >> 16));

        // Start the DMA
        DMA_RGET(DMACSR5);
        DMA_FSET(DMACCR5,EN,1);

        // wait for the DMA to transfer the block
        while( (DMA_RGET(DMACSR5) & 0x20) == 0x00 )
        {
        }

        // set the DMA to set the SDRAM to 0x5555
        DMA_RSET(DMACSDP5, RamTest_SetSdramSDP);
        DMA_RSET(DMACCR5, RamTest_SetSdramCCR);
        DMA_RSET(DMACSSAL5, (Uint16)(((Uint32)(&hex5555)<<1)&0x00FFFF));
        DMA_RSET(DMACSSAU5, (Uint16)((((Uint32)(&hex5555)<<1)&0xFF0000) >> 16));
        DMA_RSET(DMACDSAL5, (Uint16)(((Uint32)(NextAddress)<<1)&0x00FFFF));
        DMA_RSET(DMACDSAU5, (Uint16)((((Uint32)(NextAddress)<<1)&0xFF0000) >> 16));

        // Start the DMA
        DMA_RGET(DMACSR5);
        DMA_FSET(DMACCR5,EN,1);

        // check the data
        for( i = 0; i < SizeToCheck; i++ )
        {
            if( CheckData[i] != 0xAAAAAAAA )
            {
                return FALSE;                   // ERROR!!
            }
        }

        // wait for the DMA to transfer the block
        while( (DMA_RGET(DMACSR5) & 0x20) == 0x00 )
        {
        }

        // copy the SDRAM to internal RAM for checking
        DMA_RSET(DMACSDP5, RamTest_CopyToDaramSDP);
        DMA_RSET(DMACCR5, RamTest_CopyToDaramCCR);
        DMA_RSET(DMACSSAL5, (Uint16)(((Uint32)(NextAddress)<<1)&0x00FFFF));
        DMA_RSET(DMACSSAU5, (Uint16)((((Uint32)(NextAddress)<<1)&0xFF0000) >> 16));
        DMA_RSET(DMACDSAL5, (Uint16)(((Uint32)(&CheckData)<<1)&0x00FFFF));
        DMA_RSET(DMACDSAU5, (Uint16)((((Uint32)(&CheckData)<<1)&0xFF0000) >> 16));

        // Start the DMA
        DMA_RGET(DMACSR5);
        DMA_FSET(DMACCR5,EN,1);

        // wait for the DMA to transfer the block
        while( (DMA_RGET(DMACSR5) & 0x20) == 0x00 )
        {
        }

        // copy the saved data back to sdram
        DMA_RSET(DMACSDP5, RamTest_CopyToSdramSDP);
        DMA_RSET(DMACCR5, RamTest_CopyToSdramCCR);
        DMA_RSET(DMACSSAL5, (Uint16)(((Uint32)(&SavedData)<<1)&0x00FFFF));
        DMA_RSET(DMACSSAU5, (Uint16)((((Uint32)(&SavedData)<<1)&0xFF0000) >> 16));
        DMA_RSET(DMACDSAL5, (Uint16)(((Uint32)(NextAddress)<<1)&0x00FFFF));
        DMA_RSET(DMACDSAU5, (Uint16)((((Uint32)(NextAddress)<<1)&0xFF0000) >> 16));

        // Start the DMA
        DMA_RGET(DMACSR5);
        DMA_FSET(DMACCR5,EN,1);

        // check the data
        for( i = 0; i < SizeToCheck; i++ )
        {
            if( CheckData[i] != 0x55555555 )
            {
                return FALSE;                   // ERROR!!
            }
        }

        // wait for the DMA to transfer the block
        while( (DMA_RGET(DMACSR5) & 0x20) == 0x00 )
        {
        }

        // re-enable interrupts for BIOS to do some stuff
        ENABLE_INTERRUPTS;

        // Move to the next block a addresses.  SizeToCheck is in 32-bit
        // words, NextAddress is in 16-bit words.
        NextAddress += SizeToCheck*2;
    }

    return TRUE;
}



