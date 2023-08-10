/*************************************************************************
* $RCSFile: /db/sds/syseng/rtdx/target/examples/c55xx/target.h,v $
* $Revision$
* $Date$
* Copyright (c) 2000 Texas Instruments Incorporated
*
* C55xx specific inititlaization details
*************************************************************************/
#ifndef __TARGET_H
#define __TARGET_H

/*  RTDX Init functions are called by C55x runtimes during PINIT.
    RTDX_Init_RT_Monitor will enable the DLOG interrupt.
    However, the user must enable the global interrupt flag.
*/
#ifdef _ALGEBRAIC_ASM
#define TARGET_INITIALIZE() \
    asm(" BIT (ST1, #ST1_INTM) = #0");  /* Enable global ints */
#else
#define TARGET_INITIALIZE() \
    asm("	BCLR	ST1_INTM,ST1_55");	/* Enable global ints */
#endif

#endif /*__TARGET_H */
