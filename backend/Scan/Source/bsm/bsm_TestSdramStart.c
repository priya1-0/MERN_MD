/************************************************************************
*
* MODULE: bsm_TestSdramStart.c
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains a global variable that is needed to
*              copy the SDRAM Test function to DARAM.
*
*************************************************************************/

// Put the function in the section with the other receive functions
#pragma CODE_SECTION(bsm_SdramTestStart, ".shared_daram_start")

void bsm_SdramTestStart(void)
{
// this assembly directive puts the load address into a
// symbol called _bsm_SdramTestStart
    asm ("	.label _bsm_DaramLoadStart");
}

// make the variable visible to outside files
asm ("	.global _bsm_LoadSharedDaramStart");
// put it in the data section
asm ("	.data");
// Assign the variable the load address of the above function
asm ("_bsm_LoadSharedDaramStart: .long  _bsm_DaramLoadStart");


