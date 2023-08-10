#ifndef _GLOBAL_H
#define _GLOBAL_H

#include "types.h"
#include <clk.h>

/* Globals Defines */
#define MCBSP_BITS_16 0


#define bsc_VERMAJOR       1       // Version number used by Medtronic
#define bsc_VERMIDHIGH     0       // Version number used by Medtronic
#define NWC_SU_IN_PROGRESS 0x58
#define NWC_SU_NOTHING     0xff

//Note: When changing the cpu frequency, this effects the LTMR and HTMR settings.
// The Fash_Periph_Clk_Div should be set correspondingly to the value programmed
// for that clock frequency. In the CDB, the DSP frequency in the global settings
// properties box should be set to the speed of the fast peripheral clock. The
// TDDR setting in the clock manager should match the fast peripheral clock
// divider. After those have been set then set the PRD for the desired low
// resolution tick desired.

#define  CPU_FREQ            ((UINT32)(300000000))
#define  FAST_PERIPH_CLK_DIV (2)
#define  SLOW_PERIPH_CLK_DIV (2)

//The GPIO_XF pin is an output only pin accessable only by inline-assembly
#define GLB_SET_XF asm ("	bit(st1, #13) = #1");
#define GLB_CLR_XF asm ("	bit(st1, #13) = #0");

// Note - For these macros, bit numbers go from 0 to 7
// (not 1 to 8).
#define GLB_SET_BIT(addr, bit_num)    addr |= (1 << (bit_num));
#define GLB_CLEAR_BIT(addr, bit_num)  addr &= ~(1 << (bit_num));
#define GLB_TOGGLE_BIT(addr, bit_num) addr ^= (1 << (bit_num));

#define GLB_SET_W_MASK(addr, mask)   addr  |= (mask);
#define GLB_CLEAR_W_MASK(addr, mask) addr  &= ~(mask);

#define GLB_BIT_IS_SET(addr, bit_num)   ((addr & (1 << bit_num)) ? TRUE : FALSE)
#define GLB_BIT_IS_CLEAR(addr, bit_num) ((addr & (1 << bit_num)) ? FALSE : TRUE)


// Low Resolution Time Period Measurement
// Timeout values are in 1ms increments.
// 'base' should be allocated as type GLB_LTMR_OBJ
// The GLB_GET_LTMR macro should be used first to get the base time.
// The GLB_HAS_LTMR_EXPIRED macro should be used to check for expiration.
// The GLB_LTMR_WAIT macro should be used to wait for desired expiration.


// Low resolution clock rollover in milliseconds.
#define LTMR_TICKS_PER_SECOND ((int)1000) //For 1ms ticks
#define GLB_LOW_RES_ROLLOVER  1

typedef unsigned long GLB_LTMR_OBJ;

#define GLB_GET_LTMR(base) \
    base = CLK_getltime()

#define GLB_HAS_LTMR_EXPIRED(base, timeout) \
    ((CLK_getltime() - base < (timeout/GLB_LOW_RES_ROLLOVER)) ? FALSE : TRUE)

#define GLB_LTMR_WAIT(timeout)                               \
    {                                                        \
        GLB_LTMR_OBJ base;                                   \
        GLB_GET_LTMR(base);                                  \
        while(GLB_HAS_LTMR_EXPIRED(base, timeout) == FALSE) ; \
    }


// High Resolution Time Period Measurement
// Timeout values are expressed in nanoseconds.
// Example: for a 10us expiration,'timeout'should be 10000.
// 'base' should be allocated as type GLB_HTMR_OBJ
// The GLB_GET_HTMR macro should be used first to get the base time.
// The GLB_HTMR_EXPIRED macro should be used to check for expiration.

// High resolution clock tick time in nanoseconds
#define GLB_HIGH_RES_TICK ((float)1/((float)(CPU_FREQ/FAST_PERIPH_CLK_DIV))*1e9)

typedef unsigned long GLB_HTMR_OBJ;

#define GLB_GET_HTMR(base) \
    base = CLK_gethtime()

#define GLB_HAS_HTMR_EXPIRED(base, timeout) \
    ((CLK_gethtime() - base < (GLB_HTMR_OBJ)((float)timeout/GLB_HIGH_RES_TICK)) ? FALSE : TRUE)

#define GLB_HTMR_WAIT(timeout)                               \
    {                                                        \
        GLB_HTMR_OBJ base;                                   \
        GLB_GET_HTMR(base);                                  \
        while(GLB_HAS_HTMR_EXPIRED(base, timeout) == FALSE) ; \
    }

//These are functions provided to fullfill API requirements of Medtronic.
//The NU_Retrieve_Clock macro returns an unsigned 32-bit number
//The NU_Sleep macro wait for units of 10ms utilizing the GLB_LTMR_WAIT macro
#define NU_Retrieve_Clock() ((UINT32)CLK_getltime()/10)
#define NU_Sleep(x)         GLB_LTMR_WAIT((10UL*x))
#define NU_GCTR_SIZE     (0x04)      //Number of bytes for the global counter
#define TICKS_PER_SECOND ((int)100) //For 10ms ticks

// Dummy functions
#define bsm_EEReadTime() ((unsigned long)0xbeefcafe)
#define bsm_PMReadBat()  ((unsigned char)100)

#endif
