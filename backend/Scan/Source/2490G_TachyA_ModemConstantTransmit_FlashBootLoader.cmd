/* Copyright (c) 2004 by Medtronic Inc.  All Rights Reserved */
/********************************************************************
MODULE:  Flash Boot Loader Configuration File

OWNER: Medtronic

$Revision$

$Date$

$RCSfile$

This file contains the setup instructions for the timers, registers,
I/O, etc. for Flash Boot Loading.

********************************************************************/
ModemConstantTransmit\2490G_TachyA.out      	   	/* Input COFF file */
-m2                        		/* Select Motorola-S1 */
-map ModemConstantTransmit\2490G_TachyA_hex.map   	/* Name hex utility output map file */
-parallel16                		/* Set Flash system memory width */
-v5510:2                   		/* Set processor type 5510:2 = 5502. See TI document SPRA911A */
-o ModemConstantTransmit\2490G_TachyA.hex    		/* Name hex output file */

/* PLL Register for C5502 */
-reg_config 0x1C8C, 0x8001 /* PLLDIV1 */
-reg_config 0x1C8E, 0x8001 /* PLLDIV2 */
-reg_config 0x1C90, 0x8003 /* PLLDIV3 */

-reg_config 0x1C80, 0x0000 /* PLLCSR  */
-reg_config 0x1C80, 0x0008 /* PLLCSR  */
-reg_config 0x1C88, 0x000F /* PLLM    */ 
-reg_config 0x1C8A, 0x8000 /* PLLDIV0 */
-reg_config 0x8400, 0x0005 /* PLL_CLKOUTSR, Disable Clock Out */ 

/* wait 1 us @ 20MHz => */
-delay 0x1000

-reg_config 0x1C80, 0x0000 /* PLLCSR */

/* Wait for the PLL to relock (delay @ 20MHz) */
-delay 0xFFFF

-reg_config 0x1C80, 0x0001 /* PLLCSR */


/* EMIF Registers for the C5502 */
-reg_config 0x0800, 0x00E0 /* EMIF_GCR1    */
-reg_config 0x0801, 0x0002 /* EMIF_GCR2    */
-reg_config 0x0802, 0x8411 /* EMIF_CE1_1   */ 
-reg_config 0x0803, 0x2152 /* EMIF_CE1_2   */
-reg_config 0x0804, 0x8411 /* EMIF_CE0_1   */
-reg_config 0x0805, 0x2152 /* EMIF_CE0_2   */
-reg_config 0x0808, 0xFF33 /* EMIF_CE2_1   */
-reg_config 0x0809, 0xFFFF /* EMIF_CE2_2   */
-reg_config 0x080E, 0x0927 /* EMIF_SDRFR1  */
-reg_config 0x080F, 0x0000 /* EMIF_SDRFR2  */
-reg_config 0x0810, 0x45B7 /* EMIF_SDEXT1  */
-reg_config 0x0811, 0x0005 /* EMIF_SDEXT2  */
-reg_config 0x0824, 0x0000 /* EMIF_CE0_SC1 */
-reg_config 0x0825, 0x0000 /* EMIF_CE0_SC2 */
-reg_config 0x0828, 0x0000 /* EMIF_CE2_SC1 */
-reg_config 0x0829, 0x0000 /* EMIF_CE2_SC2 */
-reg_config 0x080C, 0x5000 /* EMIF_SDCTL1  */
-reg_config 0x080D, 0x4751 /* EMIF_SDCTL2  */
-reg_config 0x0840, 0x0001 /* EMIF_CECTL1  */

/* wait ?? us */
-delay 0xFFFF

ROMS
{
	PAGE 0 : ROM : o=0x000000, l=0x200000
}

SECTIONS
{
   .sysstack 		 = boot, 
   .bios 			 = boot,
   .stack			 = boot,
   .sysinit 		 = boot,
   .trcdata 		 = boot,
   .gblinit 		 = boot,
   .args 			 = boot,
   .trace$buf 		 = boot,
   .LOG_system$buf 	 = boot,
   .hwi_vec 		 = boot,
   /* Telem A */
   .tam_rx_text  	 = boot,
   
   .sdram_test_text  = boot,
   /* Telem B */
   .coeffs           = boot,
   .tbmExtData       = boot,
   .tbmExtCode       = boot,
   .tbmCode          = boot,
   .tbmConst         = boot,
   
   
   /* Vocal */
   .isr_code 	     = boot,
   .vocal_uninit_int = boot,
   .vocal_const_int  = boot,
   .trellis_code     = boot,
   .ph2_vars         = boot,
   .ph2_local        = boot,
   .tel_vars         = boot,
   .v34_vars         = boot,
   .vocal_data_store = boot,
   /* End Vocal */
   
   .const 			 = boot,
   .sect_state 		 = boot,
   .switch 			 = boot,
   .cinit 			 = boot,
   .text 			 = boot,
   .crc 	paddr = 0x1EFFFC 
}
   
   