/******************************************************************************\
*           Copyright (C) 2001 Texas Instruments Incorporated.
*                           All Rights Reserved
*------------------------------------------------------------------------------
* MODULE NAME... UART
* FILENAME...... csl_uart.h
* DATE CREATED.. Thur 01/17/2002 
* PROJECT....... Chip Support Library
* COMPONENT..... service layer
* PREREQUISITS.. cslhal.h
*------------------------------------------------------------------------------
* HISTORY:
*   CREATED:       01/17/2001  Created for 5502.  
*
*------------------------------------------------------------------------------
* DESCRIPTION:  (interface file for the UART module)
*
*
*
\******************************************************************************/
#ifndef _CSL_UART_H_
#define _CSL_UART_H_

#include <csl_std.h>
#include <csl.h>
#include <csl_chiphal.h>
#include <csl_csldat.h>
#include <csl_hpi.h>
#include <csl_hpihal.h>
#include <csl_irq.h>
#include <csl_uarthal.h>
#include <csl_uartdat.h>

#if (_UART_SUPPORT) 
/*----------------------------------------------------------------*\
*	 UART scope and inline control macros 			
\*----------------------------------------------------------------*/

#ifdef __cplusplus
#define CSLAPI extern "C"
#else
#define CSLAPI extern 
#endif

#undef  USEDEFS
#undef  IDECL
#undef  IDEF

#ifdef  _UART_MOD_
  #define IDECL CSLAPI
  #define IDEF
#else
  #ifdef  _INLINE
    #define IDECL static inline
    #define USEDEFS
    #define IDEF  static inline
  #else
    #define IDECL CSLAPI
 #endif
#endif


// fake define info - need to be deleted or modified when we intergrate 
//static Uint32 UART_isrDispatchTable[7];

/****************************************\
* Temp define info (should be included in other CSL module
\****************************************/
/******************************************************************************\
* Register Field Values
\******************************************************************************/

/* LCR Register field values */
#define UART_URLCR_WLS_5bits               (0x0000u)         /* word length is 5 bits */
#define UART_URLCR_WLS_6bits               (0x0001u)         /* word length is 6 bits */
#define UART_URLCR_WLS_7bits               (0x0002u)         /* word length is 7 bits */
#define UART_URLCR_WLS_8bits               (0x0003u)         /* word length is 8 bits */

#define UART_URLCR_STB_ZERO                (0x0000u)         /* STB bit setup to 0 */
#define UART_URLCR_STB_ONE                 (0x0004u)         /* STB bit setup to 1 */

#define UART_URLCR_PEN_ENABLE              (0x0008u)         /* parity enabled */
#define UART_URLCR_PEN_DISABLE             (0x0000u)         /* parity disabled */

#define UART_URLCR_EPS_ENABLE              (0x0010u)         /* even parity check enabled */
#define UART_URLCR_EPS_DISABLE             (0x0000u)         /* even parity check disabled */

#define UART_URLCR_STPAR_ENABLE            (0x0020u)         /* stick parity check enabled */
#define UART_URLCR_STPAR_DISABLE           (0x0000u)         /* stick parity check disabled */

#define UART_URLCR_BC_ENABLE               (0x0040u)         /* break control enabled */
#define UART_URLCR_BC_DISABLE              (0x0000u)         /* break control disabled */

#define UART_URLCR_DLAB_ONE                (0x0080u)         /* DLAB set to 1 */
#define UART_URLCR_DLAB_ZERO               (0x0000u)         /* DLAB set to 0 */

#define UART_URLCR_RMK(wls, stb, pen, eps, stpar, bc, dlab)((Uint16)(\
    (UART_FMK(URLCR,WLS, wls))|\
    (UART_FMK(URLCR,STB, stb))|\
    (UART_FMK(URLCR,PEN, pen))|\
    (UART_FMK(URLCR,EPS, eps))|\
    (UART_FMK(URLCR,STPAR, stpar))|\
    (UART_FMK(URLCR,BC, bc))|\
    (UART_FMK(URLCR,DLAB, dlab))\
 )\
)

#define UART_URLCR_RMKS(wls_sym, stb_sym, pen_sym, eps_sym, stpar_sym, bc_sym, dlab_sym)((Uint16)(\
    (UART_FMKS(URLCR,WLS, wls_sym))|\
    (UART_FMKS(URLCR,STB, stb_sym))|\
    (UART_FMKS(URLCR,PEN, pen_sym))|\
    (UART_FMKS(URLCR,EPS, eps_sym))|\
    (UART_FMKS(URLCR,STPAR, stpar_sym))|\
    (UART_FMKS(URLCR,BC, bc_sym))|\
    (UART_FMKS(URLCR,DLAB, dlab_sym))\
 )\
)

/* URIER Register field values */
#define UART_URIER_ERBI_DISABLE            (0x0000u)         /* disable receive data availabe interrupt */
#define UART_URIER_ERBI_ENABLE             (0x0001u)         /* enable receive data availabe interrupt */

#define UART_URIER_ETBEI_DISABLE           (0x0000u)         /* disable transmitter holding register empty interrupt */
#define UART_URIER_ETBEI_ENABLE            (0x0002u)         /* enable transmitter holding register empty interrupt */

#define UART_URIER_ELSI_DISABLE            (0x0000u)         /* disable receive line status interrupt */
#define UART_URIER_ELSI_ENABLE             (0x0004u)         /* enable receive line status interrupt */
#define UART_URIER_EDSSI_DISABLE           (0x0000u)         /* disable modem line status interrupt */
#define UART_URIER_EDSSI_ENABLE            (0x0008u)         /* enable modem status interrupt */

#define UART_URIER_RMK(erbi, etbei, elsi, edssi)((Uint16)(\
    (UART_FMK(URIER,ERBI, erbi))|\
    (UART_FMK(URIER,ETBEI, etbei))|\
    (UART_FMK(URIER,ELSI, elsi))|\
    (UART_FMK(URIER,EDSSI, edssi))\
 )\
)

#define UART_URIER_RMKS(erbi_sym, etbei_sym, elsi_sym, edssi_sym)((Uint16)(\
    (UART_FMKS(URIER,ERBI, erbi_sym))|\
    (UART_FMKS(URIER,ETBEI, etbei_sym))|\
    (UART_FMKS(URIER,ELSI, elsi_sym))|\
    (UART_FMKS(URIER,EDSSI, edssi_sym))\
 )\
)

/* URFCR Register field values */
#define UART_URFCR_FIEN_DISABLE            (0x0000u)         /* FIFO disable */
#define UART_URFCR_FIEN_ENABLE             (0x0001u)         /* FIFO enable */
#define UART_URFCR_RFIRS_NORESET           (0x0000u)         /*  */
#define UART_URFCR_RFIRS_RESET             (0x0002u)         /* receive FIFO reset */
#define UART_URFCR_TFIRS_NORESET           (0x0000u)         /*  */
#define UART_URFCR_TFIRS_RESET             (0x0004u)         /* transmit FIFO reset */
#define UART_URFCR_RFITR_TRIG01            (0x0000u)         /* receive FIFO trigger level */
#define UART_URFCR_RFITR_TRIG04            (0x0040u)         /* receive FIFO trigger level */
#define UART_URFCR_RFITR_TRIG08            (0x0080u)         /* receive FIFO trigger level */
#define UART_URFCR_RFITR_TRIG014           (0x00C0u)         /* receive FIFO trigger level */


#define UART_URFCR_RMK(fien, rfirs, tfirs, rfitr)((Uint16)(\
    (UART_FMK(URFCR,FIEN, fien))|\
    (UART_FMK(URFCR,RFIRS, rfirs))|\
    (UART_FMK(URFCR,TFIRS, tfirs))|\
    (UART_FMK(URFCR,RFITR, rfitr))\
 )\
)

#define UART_URFCR_RMKS(fien_sym, rfirs_sym, tfirs_sym, rfitr_sym)((Uint16)(\
    (UART_FMKS(URFCR,FIEN, fien_sym))|\
    (UART_FMKS(URFCR,RFIRS, rfirs_sym))|\
    (UART_FMKS(URFCR,TFIRS, tfirs_sym))|\
    (UART_FMKS(URFCR,RFITR, rfitr_sym))\
 )\
)

/* URLSR Register field values */
#define UART_URLSR_DR_OFF                  (0x0000u)         /* data ready bit off */
#define UART_URLSR_DR_ON                   (0x0001u)         /* data ready bit on */
#define UART_URLSR_OE_OFF                  (0x0000u)         /* overrun error bit off */
#define UART_URLSR_OE_ON                   (0x0002u)         /* overrun bit on */
#define UART_URLSR_PE_OFF                  (0x0000u)         /* parity error bit off */
#define UART_URLSR_PE_ON                   (0x0004u)         /* parity error bit on */
#define UART_URLSR_FE_OFF                  (0x0000u)         /* frame error bit off */
#define UART_URLSR_FE_ON                   (0x0008u)         /* frame bit on */
#define UART_URLSR_BI_OFF                  (0x0000u)         /* break interrupt bit off */
#define UART_URLSR_BI_ON                   (0x0010u)         /* break interrupt bit on */
#define UART_URLSR_THRE_OFF                (0x0000u)         /* transmit holding register bit off */
#define UART_URLSR_THRE_ON                 (0x0020u)         /* transmit holding register bit bit on */
#define UART_URLSR_TEMT_OFF                (0x0000u)         /* transmitter empty bit off */
#define UART_URLSR_TEMT_ON                 (0x0040u)         /* transmitter empty bit on */
#define UART_URLSR_RFIER_OFF               (0x0000u)         /* error in RCVR FIFO bit off */
#define UART_URLSR_RFIER_ON                (0x0080u)         /* error in RCVR FIFO bit on */

#define UART_URLSR_RMK(dr, oe, pe, fe, bi, thre, temt, rfier)((Uint16)(\
    (UART_FMK(URLSR,DR, dr))|\
    (UART_FMK(URLSR,OE, oe))|\
    (UART_FMK(URLSR,PE, pe))|\
    (UART_FMK(URLSR,FE, fe))|\
    (UART_FMK(URLSR,BI, bi))|\
    (UART_FMK(URLSR,THRE, thre))|\
    (UART_FMK(URLSR,TEMT, temt))|\
    (UART_FMK(URLSR,RFIER, rfier))\
 )\
)

#define UART_URLSR_RMKS(dr_sym, oe_sym, pe_sym, fe_sym, bi_sym, thre_sym, temt_sym, rfier_sym)((Uint16)(\
    (UART_FMKS(URLSR,DR, dr_sym))|\
    (UART_FMKS(URLSR,OE, oe_sym))|\
    (UART_FMKS(URLSR,PE, pe_sym))|\
    (UART_FMKS(URLSR,FE, fe_sym))|\
    (UART_FMKS(URLSR,BI, bi_sym))|\
    (UART_FMKS(URLSR,THRE, thre_sym))|\
    (UART_FMKS(URLSR,TEMT, temt_sym))|\
    (UART_FMKS(URLSR,RFIER, rfier_sym))\
 )\
)

/* URIIR Register field values */
#define UART_URIIR_IP_ON                   (0x0001u)         /* interrupt pending bit on */
#define UART_URIIR_IP_OFF                  (0x0000u)         /* interrupt pending bit off */
#define UART_URIIR_IID_RCLINESTATUS        (0x0006u)         /* receive line status interrupt */
#define UART_URIIR_IID_RCDATA              (0x0004u)         /* receive line data interrupt */
#define UART_URIIR_IID_CHARTIMEOUT         (0x000Cu)         /* char time out interrupt */
#define UART_URIIR_IID_TXEMPTY             (0x0002u)         /* transmitter holding register empty interrupt */
#define UART_URIIR_FIENR_ON                (0x0080u)         /* FIFOs enabled bit on */
#define UART_URIIR_FIENR_OFF               (0x0000u)         /* FIFOs enabled bit off */


#define UART_URIIR_RMK(ip, iid, fienr)((Uint16)(\
    (UART_FMK(URIIR,IP, ip))|\
    (UART_FMK(URIIR,IID, iid))|\
    (UART_FMK(URIIR,FIENR, fienr))\
 )\
)

#define UART_URIIR_RMKS(ip_sym, iid_sym, fienr_sym)((Uint16)(\
    (UART_FMKS(URIIR,IP, ip_sym))|\
    (UART_FMKS(URIIR,IID, iid_sym))|\
    (UART_FMKS(URIIR,FIENR, fienr_sym))\
 )\
)

/* UAMSR Register field values */
#define UART_URMSR_DCTS_ONE            (0x0001u)         /* DCTS  bit is 1 */
#define UART_URMSR_DCTS_ZERO           (0x0000u)         /* DCTS  bit is 0 */
#define UART_URMSR_DDSR_ONE            (0x0002u)         /* DDSR  bit is 1 */
#define UART_URMSR_DDSR_ZERO           (0x0000u)         /* DDSR  bit is 0 */
#define UART_URMSR_TERI_ONE            (0x0004u)         /* TERI  bit is 1 */
#define UART_URMSR_TERI_ZERO           (0x0000u)         /* TERI  bit is 0 */
#define UART_URMSR_DCD_ONE             (0x0008u)         /* DCD  bit is 1 */
#define UART_URMSR_DCD_ZERO            (0x0000u)         /* DCD  bit is 0 */
#define UART_URMSR_CTS_ON              (0x0010u)         /* CTS  bit is 1 */
#define UART_URMSR_CTS_OFF             (0x0000u)         /* CTS  bit is 0 */
#define UART_URMSR_DSR_ON              (0x0020u)         /* DSR  bit is 1 */
#define UART_URMSR_DSR_OFF             (0x0000u)         /* DSR  bit is 0 */
#define UART_URMSR_RI_ON               (0x0040u)         /* RI  bit is 1 */
#define UART_URMSR_RI_OFF              (0x0000u)         /* RI  bit is 0 */
#define UART_URMSR_CD_ON               (0x0080u)         /* CD  bit is 1 */
#define UART_URMSR_CD_OFF              (0x0000u)         /* CD  bit is 0 */


#define UART_URMSR_RMK(dcts, ddsr, teri, dcd, cts, dsr, cd, ri)((Uint16)(\
    (UART_FMK(URMSR,DCTS, dcts))|\
    (UART_FMK(URMSR,DDSR, ddsr))|\
    (UART_FMK(URMSR,TERI, teri))|\
    (UART_FMK(URMSR,DCD, dcd))|\
    (UART_FMK(URMSR,CTS, cts))|\
    (UART_FMK(URMSR,DSR, dsr))|\
    (UART_FMK(URMSR,CD, cd))|\
    (UART_FMK(URMSR,RI, ri))\
 )\
)


#define UART_URMSR_RMKS(dcts_sym, ddsr_sym, teri_sym, dcd_sym, cts_sym, dsr_sym, cd_sym, ri_sym)((Uint16)(\
    (UART_FMKS(URMSR,DCTS, dcts_sym))|\
    (UART_FMKS(URMSR,DDSR, ddsr_sym))|\
    (UART_FMKS(URMSR,TERI, teri_sym))|\
    (UART_FMKS(URMSR,DCD, dcd_sym))|\
    (UART_FMKS(URMSR,CTS, cts_sym))|\
    (UART_FMKS(URMSR,DSR, dsr_sym))|\
    (UART_FMKS(URMSR,CD, cd_sym))|\
    (UART_FMKS(URMSR,RI, ri_sym))\
 )\
)

/* UAMCR Register field values */
#define UART_URMCR_DTR_ON              (0x0001u)         /* DTR  bit is 1 */
#define UART_URMCR_DTR_OFF             (0x0000u)         /* DTR  bit is 0 */
#define UART_URMCR_RTS_ON              (0x0002u)         /* RTS  bit is 1 */
#define UART_URMCR_RTS_OFF             (0x0000u)         /* RTS  bit is 0 */
#define UART_URMCR_OUT1_ON             (0x0004u)         /* OUT1  bit is 1 */
#define UART_URMCR_OUT1_OFF            (0x0000u)         /* OUT1  bit is 0 */
#define UART_URMCR_OUT2_ON             (0x0008u)         /* OUT2  bit is 1 */
#define UART_URMCR_OUT2_OFF            (0x0000u)         /* OUT2  bit is 0 */
#define UART_URMCR_LOOP_ON             (0x0010u)         /* LOOP  bit is 1 */
#define UART_URMCR_LOOP_OFF            (0x0000u)         /* LOOP  bit is 0 */
#define UART_URMCR_AFE_ON              (0x0020u)         /* autoflow control  bit is 1 */
#define UART_URMCR_AFE_OFF             (0x0000u)         /* autoflow control  bit is 0 */


#define UART_URMCR_RMK(dtr, rts, out1, out2, loop, afe)((Uint16)(\
    (UART_FMK(URMCR,DTR, dtr))|\
    (UART_FMK(URMCR,RTS, rts))|\
    (UART_FMK(URMCR,OUT1, out1))|\
    (UART_FMK(URMCR,OUT2, out2))|\
    (UART_FMK(URMCR,LOOP, loop))|\
    (UART_FMK(URMCR,AFE, afe))\
 )\
)

#define UART_URMCR_RMKS(dtr_sym, rts_sym, out1_sym, out2_sym, loop_sym, afe_sym)((Uint16)(\
    (UART_FMKS(URMCR,DTR, dtr_sym))|\
    (UART_FMKS(URMCR,RTS, rts_sym))|\
    (UART_FMKS(URMCR,OUT1, out1_sym))|\
    (UART_FMKS(URMCR,OUT2, out2_sym))|\
    (UART_FMKS(URMCR,LOOP, loop_sym))|\
    (UART_FMKS(URMCR,AFE, afe_sym))\
 )\
)

/****************************************\
* UART global typedef declarations
\****************************************/

/*****************************************************************************/
/* typedefs & enums                                                          */
/*****************************************************************************/

// TL16C550C UART interrupts
#define   UART_NOINT          0x00             // Disable all interrupts
#define   UART_RINT           0x01             // Enable rx data available interrupt
#define   UART_TINT           0x02             // Enable tx hold register empty interrupt
#define   UART_LSINT          0x04             // Enable rx line status interrupt
#define   UART_MSINT          0x08             // Enable modem status interrupt
#define   UART_ALLINT         0x0f             // Enable all interrupts

// TL16C550C UART autoBaud
#define   UART_AUTOBAUD            0x01           
#define   UART_NO_AUTOBAUD         0x00

// TL16C550C UART serial character word length
#define   UART_WORD5            0x00           // 5-bit 
#define   UART_WORD6            0x01           // 6-bit
#define   UART_WORD7            0x02           // 7-bit
#define   UART_WORD8            0x03            // 8-bit

// TL16C550C UART stop bits
#define   UART_STOP1                0x0             // 1 stop bit
#define   UART_STOP1_PLUS_HALF      0x4             // 1 1/2 stop bits
#define   UART_STOP2                0x4             // 2 stop bits

// TL16C550C UART flow control
#define   UART_NO_LOOPBACK    0x0
#define   UART_LOOPBACK       0x10

// TL16C550C UART parity select
/*  LCR		bit5 	bit4	bit3
 *  x		x		0		- No parity
 *  0		0		1		- odd parity
 *  0		1		1		- even parity
 *  1		0		1		- mark parity
 *  1		1		1		- space parity
 */
 
#define   UART_DISABLE_PARITY   0x0      //disable parity checking
#define   UART_ODD_PARITY       0x08   //enable odd parity
#define   UART_EVEN_PARITY      0x18   //enable even parity
#define   UART_MARK_PARITY      0x28   //enable mark parity
#define   UART_SPACE_PARITY     0x38   //enable space parity

#define   UART_PARITY_MASK      0x38   
// TL16C550C UART stick parity select
//#define   UART_DISABLE_STICKPARITY   0x0      //disable stick parity 
//#define   UART_ENABLE_STICKPARITY    0x2      //enable stick parity 

/*
// TL16C550C UART baud rates for clk = 24MHz
// divisor value = (24 x 1000000) / (16 x baud rate)
//        baud rate             divisor value      percent error                             
#define   UART_BAUD_150         10000              // -
#define   UART_BAUD_300         5000               // -
#define   UART_BAUD_600         2500               // -
#define   UART_BAUD_1200        1250               // -
#define   UART_BAUD_1800        833                // 0.04
#define   UART_BAUD_2000        750                // -
#define   UART_BAUD_2400        625                // -
#define   UART_BAUD_3600        417                // 0.08
#define   UART_BAUD_4800        313                // 0.16
#define   UART_BAUD_7200        208                // 0.158
#define   UART_BAUD_9600        156                // 0.16
#define   UART_BAUD_19200       78                 // 0.16
#define   UART_BAUD_38400       39                 // 0.16
#define   UART_BAUD_57600       26                 // 0.16
#define   UART_BAUD_115200      13                 // 0.16

// TL16C550C UART clkInput
#define   UART_CLK_INPUT_24        0x01        // Input clock = 24MHz    
#define   UART_CLK_INPUT_48        0x02        // Input clock = 48MHz    
#define   UART_CLK_INPUT_72        0x03        // Input clock = 72MHz    
#define   UART_CLK_INPUT_96        0x04        // Input clock = 96MHz    
#define   UART_CLK_INPUT_120       0x05        // Input clock = 120MHz    
#define   UART_CLK_INPUT_148       0x06        // Input clock = 148MHz    
#define   UART_CLK_INPUT_172       0x07        // Input clock = 172MHz    

*/

// TL16C550C UART baud rates for clk = 20MHz
// divisor value = (20 x 1000000) / (16 x baud rate)
//        baud rate             divisor value      percent error                             
#define   UART_BAUD_150         8333             // 0.004
#define   UART_BAUD_300         4167             // 0.008
#define   UART_BAUD_600         2083             // 0.016
#define   UART_BAUD_1200        1042             // 0.032
#define   UART_BAUD_1800        694              // 0.064
#define   UART_BAUD_2000        625              // 
#define   UART_BAUD_2400        521              // 0.032
#define   UART_BAUD_3600        347              // 0.064 
#define   UART_BAUD_4800        260              // 0.16
#define   UART_BAUD_7200        173              // 0.35
#define   UART_BAUD_9600        130              // 0.16
#define   UART_BAUD_19200       65               // 0.16
#define   UART_BAUD_38400       33               // 1.38
#define   UART_BAUD_57600       22               // 1.37
#define   UART_BAUD_115200      11               // 1.38

// TL16C550C UART clkInput
#define   UART_CLK_INPUT_20        0x01        // Input clock = 20MHz    
#define   UART_CLK_INPUT_40        0x02        // Input clock = 40MHz    
#define   UART_CLK_INPUT_60        0x03        // Input clock = 60MHz    
#define   UART_CLK_INPUT_80        0x04        // Input clock = 80MHz    
#define   UART_CLK_INPUT_100       0x05        // Input clock = 100MHz    
#define   UART_CLK_INPUT_120       0x06        // Input clock = 120MHz    
#define   UART_CLK_INPUT_140       0x07        // Input clock = 140MHz    
#define   UART_CLK_INPUT_160       0x08        // Input clock = 160MHz    
#define   UART_CLK_INPUT_180       0x09        // Input clock = 180MHz    
#define   UART_CLK_INPUT_200       0x0a        // Input clock = 200MHz    

// TL16C550C UART FIFO control
#define   UART_FIFO_DISABLE     0x00
#define   UART_FIFO_DMA0_TRIG01   0x07    //DMA mode0 and trigger level 01
#define   UART_FIFO_DMA0_TRIG04   0x47    //DMA mode0 and trigger level 01
#define   UART_FIFO_DMA0_TRIG08   0x87    //DMA mode0 and trigger level 01
#define   UART_FIFO_DMA0_TRIG14   0xC7    //DMA mode0 and trigger level 01

#define   UART_FIFO_DMA1_TRIG01   0x0F    //DMA mode0 and trigger level 01
#define   UART_FIFO_DMA1_TRIG04   0x4F    //DMA mode0 and trigger level 01
#define   UART_FIFO_DMA1_TRIG08   0x8F    //DMA mode0 and trigger level 01
#define   UART_FIFO_DMA1_TRIG14   0xCF    //DMA mode0 and trigger level 01

/*
// TL16C550C UART FIFO enable
#define   UART_FIFO_DISABLE     0x00
#define   UART_FIFO_ENABLE      0x01  

#define   UART_FIFO_DMA_MODE0   0x00    //DMA mode0
#define   UART_FIFO_DMA_MODE1   0x08    //DMA mode1

// TL16C550C UART receiver FIFO trigger level
#define   UART_FIFO_TRIG01      (0x00)  
#define   UART_FIFO_TRIG04      (0x40)
#define   UART_FIFO_TRIG08      (0x80)
#define   UART_FIFO_TRIG14      (0xC0)
*/

//TL16C550C UART interrupt information as indicated
//by b0-b3 of UART_IIR_REG
#define   UART_NO_INTERRUPTPENDING  -1   //no interrupt pending
#define   UART_LSR_INTR             0x6  //rx line status - overrun error, parity error,  
                                         //framing error, or break interrupt. Read line  
                                         //status register to determine exact interrupt 
                                         //source.
#define   UART_RXRDY_INTR           0x4  //rx data available
#define   UART_CHAR_TIMEOUT         0xc  //character timeout
#define   UART_TXRDY_INTR           0x2  //tx holding register empty
#define   UART_MSR_INTR             0x0  //modem status - clear to send, data set ready,
                                         //ring indicator, or data carrier detect.
                                         //Read modem status register to exact interrupt 
                                         //source.

typedef struct
{
   Uint16              clkInput;
   Uint16              baud;
   Uint16              wordLength;
   Uint16              stopBits;
   Uint16              parity;
   Uint16              fifoControl;
   Uint16              loopBackEnable;
} UART_Setup;

typedef struct
{
   Uint16              dll;
   Uint16              dlm;
   Uint16              lcr;
   Uint16              fcr;
   Uint16              mcr;                //only for loopback
} UART_Config;


typedef struct
{
   void (*lsiAddr)(void);          // Receiver line status
   void (*rbfiAddr)(void);         // received data available
   void (*tbeiAddr)(void);         // transmiter holding register empty
   void (*dssiAddr)(void);         // modem status
   void (*ctoiAddr)(void);         // character time-out indication
} UART_IsrAddr;

#define    UART_EVT_LSI    0x03     // Receiver line status
#define    UART_EVT_RBFI   0x02     // received data available
#define    UART_EVT_CTOI   0x06     // character time-out indication
#define    UART_EVT_TBEI   0x01     // transmiter holding register empty
#define    UART_EVT_DSSI   0x00     // modem status

/* timeout error define in the polling functions */
#define TIMEOUT_ERROR 256
/****************************************\
* UART global function declarations
\****************************************/
//CSLAPI void UART_reset();
CSLAPI void UART_setup(UART_Setup *Params);
//CSLAPI void UART_getParams(UART_Params *Params);
CSLAPI void UART_config(UART_Config *Config);
CSLAPI void UART_getConfig(UART_Config *Config);
CSLAPI void UART_configArgs(Uint16 dll, Uint16 dlm, Uint16 lcr, 
                            Uint16 fcr, Uint16 mcr);
CSLAPI void UART_eventEnable(Uint16 ierMask);
CSLAPI void UART_eventDisable(Uint16 ierMask);
CSLAPI void UART_setCallback(UART_IsrAddr *isrAddr);
CSLAPI Uint16 UART_getEventId();
CSLAPI void UART_setupBaudRate(Uint16 clkInput, Uint16 baudRate);
//CSLAPI void UART_read(char *pBuf, Uint16 length);
//CSLAPI void UART_write(char *pBuf, Uint16 length);
//CSLAPI int UART_fgetc(void);
//CSLAPI void UART_fputc(const int c);
//CSLAPI int UART_fgetc(Uint32 timeout);
//CSLAPI char* UART_fgets(char* pBuf, int bufSize);
CSLAPI CSLBool UART_read(char *pBuf, Uint16 length, Uint32 timeout);
CSLAPI CSLBool UART_write(char *pBuf, Uint16 length, Uint32 timeout);
CSLAPI CSLBool UART_fgetc(int *c, Uint32 timeout);
CSLAPI CSLBool UART_fputc(const int c, Uint32 timeout);
CSLAPI CSLBool UART_fgets(char* pBuf, Uint16 bufSize, Uint32 timeout);
CSLAPI CSLBool UART_fputs(const char* pBuf, Uint32 timeout);


/*
CSLAPI void UART_flowCtrlInit();
CSLAPI void UART_CTSOff();
CSLAPI void UART_CTSOn();
CSLAPI CSLBool UART_isRTS();
CSLAPI void UART_DCDOff();
CSLAPI void UART_DCDOn();
CSLAPI void UART_RIOff();
CSLAPI void UART_RIOn();
CSLAPI void UART_DSROff();
CSLAPI void UART_DSROn();
CSLAPI CSLBool UART_isDTR();
*/

/* private function */
interrupt void UART_intrDispatch(void);
//void _delay(Uint16 loopNum);

/****************************************\
* UART global macro declarations
\****************************************/ 
#define UART_ctsOff            UART_FSET(URMSR,CTS,0)
#define UART_ctsOn             UART_FSET(URMSR,CTS,1)
#define UART_isCts             ((UART_FGET(URMSR,CTS)) ? 1 : 0)
 
#define UART_rtsOff            UART_FSET(URMCR,RTS,0)
#define UART_rtsOn             UART_FSET(URMCR,RTS,1)
#define UART_isRts             ((UART_FGET(URMCR,RTS)) ? 1 : 0)
 
#define UART_cdOff             UART_FSET(URMSR,CD,0)
#define UART_cdOn              UART_FSET(URMSR,CD,1)
#define UART_isCd              ((UART_FGET(URMSR,CD)) ? 1 : 0)
 
#define UART_riOff             UART_FSET(URMSR,RI,0)
#define UART_riOn              UART_FSET(URMSR,RI,1)
#define UART_isRi              ((UART_FGET(URMSR,RI)) ? 1 : 0)
 
#define UART_dsrOff            UART_FSET(URMSR,DSR,1)
#define UART_dsrOn             UART_FSET(URMSR,DSR,0)
#define UART_isDsr             ((UART_FGET(URMSR,DSR)) ? 1 : 0)
 
#define UART_dtrOff            UART_FSET(URMCR,DTR,0)
#define UART_dtrOn             UART_FSET(URMCR,DTR,1)
#define UART_isDtr             ((UART_FGET(URMCR,DTR)) ? 1 : 0)
 
 
/* configure HPIGPIO pins to UART control signals and configure the direction    */
/* of of those control signals as following:                                     */
/* HD0 - DTR - Input                                                             */
/* HD1 - RTS - Input                                                             */
/* HD2 - CTS - Output                                                            */
/* HD3 - DSR - Output                                                            */
/* HD4 - DCD - Output                                                            */
/* HD5 - RI - Output                                                             */
#define UART_flowCtrlInit0      {CHIP_FSET(XBSR,SP1,0); CHIP_FSET(XBSR,UART,1);\
  HPI_FSET(HGPIOEN,EN7,1);  HPI_RAOI(HGPIODIR,0xFFFC,0x0003,0x0000);}

/* configure HPIGPIO pins to UART control signals and configure the direction    */
/* of of those control signals as following:                                     */
/* HD0 - DTR - Output                                                            */
/* HD1 - RTS - Output                                                            */
/* HD2 - CTS - Input                                                             */
/* HD3 - DSR - Input                                                             */
/* HD4 - DCD - Input                                                             */
/* HD5 - RI - Input                                                              */
#define UART_flowCtrlInit1      {CHIP_FSET(XBSR,SP1,0); CHIP_FSET(XBSR,UART,1);\
 HPI_FSET(HGPIOEN,EN7,1); HPI_RAOI(HGPIODIR,0xFF03,0x00FC,0x0000);}
#define UART_reset()             UART_FSET(URPECR,URST,0)
#define UART_resetOff()          UART_FSET(URPECR,URST,1)


/****************************************\
* UART global variable declarations
\****************************************/ 

#elif (!(_UART_MOD))
	#error UART Hal Module Not Supported on Specified Target
#endif  /* _UART_SUPPORT  */

#endif /* _CSL_UART_H_ */                
/******************************************************************************\
* End of CSL_uart.h
\******************************************************************************/

