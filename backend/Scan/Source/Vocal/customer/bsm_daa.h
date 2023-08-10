/************************************************************************
*
* MODULE: bsm_DAA.h
*
* OWNER:
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* FUNCTIONS:
* --Public--
* bsm_initDAA()
* bsm_set_DAA_FC_RGDTb()
* bsm_clear_DAA_FC_RGDTb()
* bsm_read_DAA_RGDT()
* bsm_set_DAA_OFHKb()
* bsm_clear_DAA_OFHKb()
* bsm_set_SPFC_DSR()
* bsm_clear_SPFC_DSR()
* bsm_set_SPFC_CTS()
* bsm_clear_SPFC_CTS()
* bsm_read_SPFC_RTS()
* bsm_read_SPFC_DTR()
*
* --Private--
*
* DESCRIPTION: Board support header file for the DAA and supplemental
*              HW flow control pins
*
*************************************************************************/
#ifndef __DAA_PINS_H
#define __DAA_PINS_H

#ifdef DEFINED_HERE
    #define SCOPE
#else
    #define SCOPE extern
#endif


#include <csl.h>
#include <csl_mcbsp.h>
#include <csl_hpi.h>
#include <csl_gpio.h>
//#include "../global.h"


// Remove these defines if they ever get added into the CSL
#define _HPI_HGPIODAT1_ADDR     (0xA00Au)
#define _HPI_HGPIODAT1          PREG16(_HPI_HGPIODAT1_ADDR)
#define HGPIODAT1               _HPI_HGPIODAT1

#define _HPI_HGPIODIR1_ADDR     (0xA008u)
#define _HPI_HGPIODIR1          PREG16(_HPI_HGPIODIR1_ADDR)
#define HGPIODIR1               _HPI_HGPIODIR1

#define _HPI_HGPIODAT2_ADDR     (0xA00Eu)
#define _HPI_HGPIODAT2          PREG16(_HPI_HGPIODAT2_ADDR)
#define HGPIODAT2               _HPI_HGPIODAT2

#define _HPI_HGPIODIR2_ADDR     (0xA00Cu)
#define _HPI_HGPIODIR2          PREG16(_HPI_HGPIODIR2_ADDR)
#define HGPIODIR2           _HPI_HGPIODIR2



/* DAA GPIO PINS **************************************************************/
//FC = HCS = P44 = Bit1 in HGPIODAT2
#define DAA_FC_RGDTb            0x02      // Bit mask for the I/O pin, pin1
#define DAA_FC_RGDTb_Addr       HGPIODAT2 // Data register
#define DAA_FC_RGDTb_Dir        HGPIODIR2 // Direction register
#define DAA_FC_RGDTb_EN         EN0       // the bit in the HGPIOEN register to enable this as GPIO.

//RGDT = HDS1 = P51 = Bit2 in HGPIODAT2
#define DAA_RGDT                0x04      // Bit mask for the I/O pin, pin2
#define DAA_RGDT_Addr           HGPIODAT2 // Data register
#define DAA_RGDT_Dir            HGPIODIR2 // Direction register
#define DAA_RGDT_EN             EN0       // the bit in the HGPIOEN register to enable this as GPIO.

//OFHK = HDS2 = P49 = Bit3 in HGPIODAT2
#define DAA_OFHK                0x08      // Bit mask for the I/O pin, pin3
#define DAA_OFHK_Addr           HGPIODAT2 // Data register
#define DAA_OFHK_Dir            HGPIODIR2 // Direction register
#define DAA_OFHK_EN             EN0       // the bit in the HGPIOEN register to enable this as GPIO.

//FC - DAA Pin 7,
#define set_DAA_FC_RGDTb()   (DAA_FC_RGDTb_Addr |=  (DAA_FC_RGDTb)) //sets to logical 1, Currently unused but provided
#define clear_DAA_FC_RGDTb() (DAA_FC_RGDTb_Addr &= ~(DAA_FC_RGDTb)) //sets to logical 0

//RGDT - DAA Pin 15 - Ring Detect
#define read_DAA_RGDT() ( (((DAA_RGDT_Addr) & DAA_RGDT) == DAA_RGDT) ? TRUE:FALSE)//output from DAA

//OFKHb - DAA Pin 16 - Off Hook
#define set_DAA_OFHKb()   (DAA_OFHK_Addr |=  (DAA_OFHK)) //sets to logical 1
#define clear_DAA_OFHKb() (DAA_OFHK_Addr &= ~(DAA_OFHK)) //sets to logical 0

/******************************************************************************/


/* SERIAL PORT - H/W FLOW CONTROL GPIO PINS ***********************************/
// = HD1 = P173 = Bit1 in HGPIODAT1
#define SPFC_CTS                0x02      // Bit mask for the I/O pin, pin1
#define SPFC_CTS_Addr           HGPIODAT1 // Data register
#define SPFC_CTS_Dir            HGPIODIR1 // Direction register
#define SPFC_CTS_EN             EN7       // the bit in the HGPIOEN register to enable this as GPIO.

// = HR/_W = P48 = Bit4 in HGPIODAT2
#define SPFC_RTS                0x10      // Bit mask for the I/O pin, pin4
#define SPFC_RTS_Addr           HGPIODAT2 // Data register
#define SPFC_RTS_Dir            HGPIODIR2 // Direction register
#define SPFC_RTS_EN             EN0       // the bit in the HGPIOEN register to enable this as GPIO.

// = HINT = P59 = Bit8 in HGPIODAT2
#define SPFC_DTR                0x0100      // Bit mask for the I/O pin, pin8
#define SPFC_DTR_Addr           HGPIODAT2 // Data register
#define SPFC_DTR_Dir            HGPIODIR2 // Direction register
#define SPFC_DTR_EN             EN6       // the bit in the HGPIOEN register to enable this as GPIO.

//SPFC_DSR
//#define set_SPFC_DSR();   GLB_SET_XF //note: This is a macro to an ainline assembly
//#define clear_SPFC_DSR(); GLB_CLR_XF //note: This is a macro to an ainline assembly
#define set_SPFC_DSR();   asm("	bset XF");
#define clear_SPFC_DSR(); asm("	bclr XF");

//SPFC_CTS
#define set_SPFC_CTS()   (SPFC_CTS_Addr |=  (SPFC_CTS)) //sets to logical 1
#define clear_SPFC_CTS() (SPFC_CTS_Addr &= ~(SPFC_CTS)) //sets to logical 0

//SPFC_RTS
#define read_SPFC_RTS() ( (((SPFC_RTS_Addr) & SPFC_RTS) == SPFC_RTS) ? TRUE:FALSE)

//SPFC_DTR
#define read_SPFC_DTR() ( (((SPFC_DTR_Addr) & SPFC_DTR) == SPFC_DTR) ? TRUE:FALSE)
/******************************************************************************/

/* PUBLIC FUNCTION DECLARATIONS*/
void bsm_initDAA();
 /*DAA*/
void bsm_set_DAA_FC_RGDTb();
void bsm_clear_DAA_FC_RGDTb();
int bsm_read_DAA_RGDT();
void bsm_set_DAA_OFHKb();
void bsm_clear_DAA_OFHKb();
 /*Serial Port Flow Control*/
void bsm_set_SPFC_DSR();
void bsm_clear_SPFC_DSR();
void bsm_set_SPFC_CTS();
void bsm_clear_SPFC_CTS();
int bsm_read_SPFC_RTS();
int bsm_read_SPFC_DTR();

/* GLOBAL VARIABLE*/
SCOPE MCBSP_Handle hDAA_mcbsp;

#endif
