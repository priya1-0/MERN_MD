/************************************************************************
*
* MODULE: dbg_ContinuousRf.c
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the functions send continuous RF.
*
*************************************************************************/

/////////////
// Includes
/////////////
#include <stdlib.h>
#include <csl_mcbsp.h>
#include <csl_gpio.h>
#include <csl_hpi.h>
#include "bsm_serialport.h"
#include "tam_TelemetryA.h"



////////////
// Globals
////////////

// character to send to produce the RF frequency
static UINT16 TransmitChar;

/******************************************************************

FUNCTION: SetRfFrequency

DESCRIPTION: This function configures the DMA and McBSP to transmit
             a frequency.

ARGS:
        char* CommandLineParameters: pointer to a character array that
            states the desired frequency.

RETURNS:
    <none>

******************************************************************/
void SetRfFrequency(char* CommandLineParameters)
{
    MCBSP_Config mcbspCfgTx = {
        0x0000,            /*  Serial Port Control Register 1   */
        0x0000,            /*  Serial Port Control Register 2   */
        0x0000,            /*  Receive Control Register 1   */
                           /*  0x00 = 8 bit word */
        /*  0x3f = 63 = (63 + 1) == 64 word frame */
        0x0004,            /*  Receive Control Register 2   */
        /*  ignore unexpected FS, 1 bit delay, single phase, LSB received first */
        // Configure the Transmit
        MCBSP_XCR1_RMK(
            MCBSP_XCR1_XFRLEN1_OF(0),
            MCBSP_XCR1_XWDLEN1_16BIT
            ),
        MCBSP_XCR2_RMK(
            MCBSP_XCR2_XPHASE_SINGLE,
            MCBSP_XCR2_XFRLEN2_OF(0),
            MCBSP_XCR2_XWDLEN2_8BIT,
            MCBSP_XCR2_XCOMPAND_MSB,
            MCBSP_XCR2_XFIG_NO,
            MCBSP_XCR2_XDATDLY_0BIT
            ),
        MCBSP_SRGR1_RMK(
            MCBSP_SRGR1_FWID_OF(0),
            MCBSP_SRGR1_CLKGDV_OF(CPU_FREQ/SLOW_PERIPH_CLK_DIV/TX_FREQUENCY*PERIODS_IN_BYTE/MCBSP_BITS_PER_SAMPLE)
            ),
        MCBSP_SRGR2_RMK(
            MCBSP_SRGR2_GSYNC_FREE,
            MCBSP_SRGR2_CLKSP_RISING,
            MCBSP_SRGR2_CLKSM_INTERNAL,
            MCBSP_SRGR2_FSGM_FSG,
            MCBSP_SRGR2_FPER_OF(15)
            ),
        0x0000,            /*  Multichannel Control Register 1   */
        0x0000,            /*  Multichannel Control Register 2   */
        0x0F00,                /*  Pin Control Register */
        0x0000,            /*  Receive Channel Enable Register Partition A   */
        0x0000,            /*  Receive Channel Enable Register Partition B   */
        0x0000,            /*  Receive Channel Enable Register Partition C   */
        0x0000,            /*  Receive Channel Enable Register Partition D   */
        0x0000,            /*  Receive Channel Enable Register Partition E   */
        0x0000,            /*  Receive Channel Enable Register Partition F   */
        0x0000,            /*  Receive Channel Enable Register Partition G   */
        0x0000,            /*  Receive Channel Enable Register Partition H   */
        0x0000,            /*  Transmit Channel Enable Register Partition A   */
        0x0000,            /*  Transmit Channel Enable Register Partition B   */
        0x0000,            /*  Transmit Channel Enable Register Partition C   */
        0x0000,            /*  Transmit Channel Enable Register Partition D   */
        0x0000,            /*  Transmit Channel Enable Register Partition E   */
        0x0000,            /*  Transmit Channel Enable Register Partition F   */
        0x0000,            /*  Transmit Channel Enable Register Partition G   */
        0x0000             /*  Transmit Channel Enable Register Partition H   */
    };

    DMA_Config gDmaConfigTx = {
        DMA_DMACSDP_RMK(
            DMA_DMACSDP_DSTBEN_NOBURST,
            DMA_DMACSDP_DSTPACK_OFF,
            DMA_DMACSDP_DST_PERIPH,
            DMA_DMACSDP_SRCBEN_NOBURST,
            DMA_DMACSDP_SRCPACK_OFF,
            DMA_DMACSDP_SRC_EMIF,
            DMA_DMACSDP_DATATYPE_16BIT
            ),          /* Source/Destination Register - DMACSDP  */
        DMA_DMACCR_RMK(
            DMA_DMACCR_DSTAMODE_CONST,
            DMA_DMACCR_SRCAMODE_CONST,
            DMA_DMACCR_ENDPROG_OFF,
            DMA_DMACCR_REPEAT_ON,
            DMA_DMACCR_AUTOINIT_ON,
            DMA_DMACCR_EN_STOP,
            DMA_DMACCR_PRIO_HI,
            DMA_DMACCR_FS_DISABLE,
            DMA_DMACCR_SYNC_XEVT0
            ),          /* Control Register - DMACCR   */
        DMA_DMACICR_RMK(
            DMA_DMACICR_BLOCKIE_OFF,
            DMA_DMACICR_LASTIE_OFF,
            DMA_DMACICR_FRAMEIE_OFF,
            DMA_DMACICR_FIRSTHALFIE_OFF,
            DMA_DMACICR_DROPIE_OFF,
            DMA_DMACICR_TIMEOUTIE_OFF
            ),          /* Interrupt Control Register - DMACICR  */
        0,                                      /* Lower Source Address - DMACSSAL */
        0,                                      /* Upper Source Address - DMACSSAU */
        0,                                      /* Lower Destination Address - DMACDSAL */
        0,                                      /* Upper Destination Address - DMACDSAU */
        1,                                      /* Element Number - DMACEN   */
        1,                                      /* Frame Number - DMACFN   */
        0,                                      /* Frame Index - DMACFI   */
        0                                       /* Element Index - DMACEI   */
    };

    Uint32 addr;
    long   Frequency;

    // configure the DMA for constantly put the same byte in the McBSP

    bsm_SDPrint("Setting Antenna Frequency");

    if( CommandLineParameters[0] < '0' || CommandLineParameters[0] > '9' )
    {
        bsm_SDPrint("Usage: CR {150000, 175000, 200000}");
        return;
    }

    // EN7 GPIO enable bit for pins HD[7:0]
    HPI_FSET(HGPIOEN, EN7, 1);
    // HGPIO HD2 == 150kHz/_200kHz output
    HPI_FSET(HGPIODIR, HD2, GPIO_OUTPUT);

    // convert the parameter to a number
    Frequency = atol(CommandLineParameters);

    // we the frequency is 0, then turn it off.
    if( Frequency == 0 )
    {
        // stop the DMA
        DMA_stop(hDma_Tx);

        MCBSP_write16(hMcbsp_TelemA, 0);

        SetAntennaToReceive_M();

        return;
    }

    if( Frequency != 150000 &&
        Frequency != 175000 &&
        Frequency != 200000 )
    {
        bsm_SDPrint("Valid Frequencies are 150kHz, 175kHz, and 200kHz.");
        return;
    }

    // HD2 == 150kHz/_200kHz output, don't care for 175000
    HPI_FSET(HGPIODAT,HD2,(Frequency == 200000) ? 0 : 1);

    TransmitChar = 0xFF00;

    // if the divide down factor is too big for the fields, print an error message
    if( CPU_FREQ/SLOW_PERIPH_CLK_DIV/Frequency/MCBSP_BITS_PER_SAMPLE > 255 )
    {
        bsm_SDPrint("The CPU clock is too high to reach this frequency");
    }

    // need to initialize the telemetry module.  The telemetry type is not important.
    tam_Initialize_TelemetryA(tac_L88TelemProtocol);

    SetAntennaToTransmit_M();

    MCBSP_reset(hMcbsp_TelemA);

    // Configure the McBSP for receive operation.
    mcbspCfgTx.srgr1 = CPU_FREQ/SLOW_PERIPH_CLK_DIV/Frequency*PERIODS_IN_BYTE/MCBSP_BITS_PER_SAMPLE;
    MCBSP_config(hMcbsp_TelemA, &mcbspCfgTx);


    // DMA source address for all transfers.
    addr                  = ((Uint32)&_MCBSP_DXR10) << 1;
    gDmaConfigTx.dmacdsal = (DMA_AdrPtr)(addr & 0xffff);
    gDmaConfigTx.dmacdsau = (Uint16)((addr >> 16) & 0xffff);

    // DMA destination address for the 1st transfer.
    addr                  = ((Uint32)&TransmitChar) << 1;
    gDmaConfigTx.dmacssal = (DMA_AdrPtr)(addr & 0xffff);
    gDmaConfigTx.dmacssau = (Uint16)((addr >> 16) & 0xffff);

    // Write values from DMA config structure to DMA channel control registers
    DMA_config(hDma_Tx, &gDmaConfigTx);

    // Clear out any pending interrupts.
    DMA_RGETH(hDma_Tx, DMACSR);

    // Start receive DMA
    DMA_start(hDma_Tx);

    // Start McBSP0
    MCBSP_start(
        hMcbsp_TelemA,
        MCBSP_XMIT_START | MCBSP_SRGR_START | MCBSP_SRGR_FRAMESYNC,
        MCBSP_SRGR_DEFAULT_DELAY);
}
