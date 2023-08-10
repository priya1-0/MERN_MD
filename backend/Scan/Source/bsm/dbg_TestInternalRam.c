/************************************************************************
*
* MODULE: dbg_TestInternalRam.c
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the functions for testing the internal
*              RAM.
*
*************************************************************************/

/////////////
// Includes
/////////////
#include <csl.h>
#include "global.h"
#include "bsm_serialport.h"

////////////
// Defines
////////////
#define INTERNAL_RAM_BEGIN 0x000060
#define INTERNAL_RAM_END   0x008000
#define INTERNAL_RAM_SIZE  (INTERNAL_RAM_END-INTERNAL_RAM_BEGIN)

/////////////////////
// Local Prototypes
/////////////////////
BOOL TestRam(UINT32 RamStart, UINT32 RamSize);

/******************************************************************

FUNCTION: TestInternalRam

DESCRIPTION: This function tests all of the internal RAM.

ARGS:
        <none>

RETURNS:
    TRUE if all RAM locations pass.
    FALSE if at least 1 location failed.

******************************************************************/
BOOL TestInternalRam(void)
{
    BOOL Result;

    bsm_SDPrint("Testing Internal RAM...");

    if(TestRam((UINT32)INTERNAL_RAM_BEGIN, INTERNAL_RAM_SIZE))
    {
        bsm_SDPrint("Internal RAM Passed");
        Result = TRUE;
    }
    else
    {
        bsm_SDPrint("Internal RAM Failed");
        Result = FALSE;
    }
    return Result;
}

/******************************************************************

FUNCTION: TestRam

DESCRIPTION: This function tests the RAM locations by writing all
             5's followed by writing all A's and checking the
             value of the RAM location.

ARGS:
        UINT32 RamStart: The WORD number to start the RAM test.
        UINT32 RamSize: The number of BYTES to test.

RETURNS:
    BOOL: TRUE all RAM locations passed.
          FALSE at least 1 RAM location failed.

******************************************************************/
BOOL TestRam(UINT32 RamStart, UINT32 RamSize)
{
    static volatile BOOL TestRamResult;

    // AR0 = RamPtr
    // AC0 = RamStart
    // AC1 = RamSize
    // AC2 = SavedData
    // AC3 = Temp

    TestRamResult = FALSE;

    asm ("TR1_Loop:");
    DISABLE_INTERRUPTS;
    asm ("	if( AC1 == #0) goto TR1_Finished");

    // set the pointer
    asm ("	XAR0 = AC0");

    // save the data
    asm ("	AC2 = *AR0");

    // test 0x5555
    asm ("	AC3 = #21845");
    asm ("	*AR0 = AC3");
    asm ("	AR2 = *AR0");
    asm ("	TC1 = ( AR2 == AC3 ) ");
    asm ("	if( !TC1 ) goto TR1_Failed");

    // test 0xAAAA
    asm ("	AC3 = #43690");
    asm ("	*AR0 = AC3");
    asm ("	AR2 = *AR0");
    asm ("	TC1 = ( AR2 == AC3 ) ");
    asm ("	if( !TC1 ) goto TR1_Failed");

    // restore the data
    asm ("	*AR0 = AC2");

    // goto the next location
    asm ("	AC0 = AC0 + 1");
    asm ("	AC1 = AC1 - 1");

    ENABLE_INTERRUPTS;
    asm ("	goto TR1_Loop");

    asm ("TR1_Finished:");
    ENABLE_INTERRUPTS;

    // All RAM locations passed
    TestRamResult = TRUE;
    asm ("	goto TR1_return");

    asm ("TR1_Failed:");
    ENABLE_INTERRUPTS;

    // A RAM location failed
    TestRamResult = FALSE;

    asm ("TR1_return:");

    return TestRamResult;
}
