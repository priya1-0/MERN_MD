/************************************************************************
*
* MODULE: bsm_TelemetryA.h
*
* OWNER:
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This is the header file for all generic Telemetry A
*              functions.
*
*************************************************************************/
#ifndef BSM_TELEMETRY_H
#define BSM_TELEMETRY_H

#include "global.h"
#include "tam_global.h"
#include <csl_mcbsp.h>
#include <csl_dma.h>
#include <csl_hpi.h>

// Transmit at 175kHz
#define TX_FREQUENCY 175000

// Clock in data from the parallel to serial converter at 5MHz
#define RX_FREQUENCY 5000000

// Clocking in 8 data bits + 1 Frame bit
#define RX_MCBSP_BITS_PER_SAMPLE 9

// total number of frames to signal a total loss in communication
#define NUM_FRAMES_IN_SEGMENT_TIME_ERROR 3

// Macros for the Coil Drain Pin
#define CoilDrain_Port _GPIO_IODATA
#define CoilDrain_Dir  _GPIO_IODIR
#define CoilDrain_Pin  GPIO_PIN6
#define TurnOnCoilDrain_M()  //CoilDrain_Port = CoilDrain_Port & ~CoilDrain_Pin
#define TurnOffCoilDrain_M() //CoilDrain_Port = CoilDrain_Port | CoilDrain_Pin
// use for determining no uplink
// Macros for the Transmit Enable pin
#define Tx_En_N_Port _GPIO_IODATA
#define Tx_En_N_Dir  _GPIO_IODIR
#define Tx_En_N_Pin  GPIO_PIN6
#define InitializeTransmitEnable() HPI_FSET(HGPIOEN, EN7, 1); \
    HPI_FSET(HGPIODIR, HD3, 1)


#define SetAntennaToTransmit_M() HPI_FSET(HGPIODAT, HD3, 0)
#define SetAntennaToReceive_M()  HPI_FSET(HGPIODAT, HD3, 1)

// Defines for the AGC bits
#define _HPI_HGPIODAT2_ADDR (0xA00Eu)
#define _HPI_HGPIODAT2      PREG16(_HPI_HGPIODAT2_ADDR)
#define HGPIODAT2           _HPI_HGPIODAT2

#define _HPI_HGPIODIR2_ADDR (0xA00Cu)
#define _HPI_HGPIODIR2      PREG16(_HPI_HGPIODIR2_ADDR)
#define HGPIODIR2           _HPI_HGPIODIR2

#define AGC_DETECT_BIT  0x40
#define AGC_DETECT_PORT HGPIODAT2
#define GetAgcDetectBit() ((AGC_DETECT_PORT&AGC_DETECT_BIT) ? TRUE : FALSE)

#define AGC_EN_BIT  0x80
#define AGC_EN_PORT HGPIODAT2

#define AGC_ACTIVE_HIGH 0

#define HIGH_GAIN 5
#define MED_GAIN  4
#define LOW_GAIN  3

#if AGC_ACTIVE_HIGH
#define EnableHighGain() AGC_EN_PORT |= AGC_EN_BIT
#define EnableLowGain()  AGC_EN_PORT &= ~AGC_EN_BIT
#else
#define EnableHighGain() AGC_EN_PORT &= ~AGC_EN_BIT
#define EnableLowGain()  AGC_EN_PORT |= AGC_EN_BIT
#endif

#define InitializeAgc() EnableHighGain(); \
    HGPIOEN   |= 0x02; \
    HGPIODIR2 |= AGC_EN_BIT; \
    HGPIODIR2 &= ~AGC_DETECT_BIT


// The received pulses are based on 32768 Hz (~30.5 us).  Each bit represents
// 1/RX_FREQUENCY seconds.
#define DEVICE_FREQ 32768

// do not put '(' or ')' around this number because we use a flaoting point
// number to multiply against this number and the result is off it we do the
// integer divide first.
#define Tu  ((float)1000000/(float)DEVICE_FREQ)
#define nTu DEVICE_FREQ/1000000

#define PERIODS_IN_BYTE       1
#define MCBSP_BITS_PER_SAMPLE 16

#ifdef DEFINED_HERE
        #define SCOPE
        #pragma DATA_SECTION(AgcPulseSelect, ".tam_rx_data")
        #pragma DATA_SECTION(RxDmaBuffer, ".tam_rx_data")
        #pragma DATA_SECTION(RxData, ".tam_rx_data")
        #pragma DATA_SECTION(RxDataType, ".tam_rx_data")
        #pragma DATA_SECTION(RxDataValid, ".tam_rx_data")
        #pragma DATA_SECTION(FrameTime, ".tam_rx_data")
#else
        #define SCOPE extern
#endif

SCOPE MCBSP_Handle hMcbsp_TelemA;
SCOPE DMA_Handle hDma_Tx;
SCOPE DMA_Handle hDma_TxHandshake;
SCOPE DMA_Handle hDma_Rx;

SCOPE tat_telemetryProtocolType TelemetryType;

// global that is initialized by Send Telemetry
SCOPE UINT16 AgcPulseSelect;

// globals shared by L88 and ICD

// Data from the latest Frame
SCOPE UINT16 RxData;

// The Frame Type of the latest Frame
SCOPE tat_frameType RxDataType;

// Flag to indicate there is new data
SCOPE volatile BOOL RxDataValid;

SCOPE void (*ProcessReceivedData)(UINT16 CurrPulse);

// Buffer to store data from the McBSP by the DMA
#define RX_DMA_BUFFER_SIZE 64
SCOPE UINT8 RxDmaBuffer[RX_DMA_BUFFER_SIZE];

#define CLKGDV_REG     (CPU_FREQ/SLOW_PERIPH_CLK_DIV/TX_FREQUENCY*PERIODS_IN_BYTE/MCBSP_BITS_PER_SAMPLE)
#define ACTUAL_TX_FREQ CPU_FREQ/SLOW_PERIPH_CLK_DIV/(CLKGDV_REG+1)/MCBSP_BITS_PER_SAMPLE

// The following variables are the times for the wakeup burst, Zero Bit,
// One Bit, Bit Pulse, and End Time.

#define TwL88        (UINT16)((.00200 * ACTUAL_TX_FREQ)/PERIODS_IN_BYTE)
#define T0L88        (UINT16)((.00068 * ACTUAL_TX_FREQ)/PERIODS_IN_BYTE)
#define T1L88        (UINT16)((.00115 * ACTUAL_TX_FREQ)/PERIODS_IN_BYTE)
#define TbL88        (UINT16)((.00016 * ACTUAL_TX_FREQ)/PERIODS_IN_BYTE)
#define TrbL88       (UINT16)((.00010 * ACTUAL_TX_FREQ)/PERIODS_IN_BYTE)
#define TeL88        (UINT16)((.00200 * ACTUAL_TX_FREQ)/PERIODS_IN_BYTE)
#define ThreplyL88   (UINT16)((.00040 * RX_FREQUENCY/RX_MCBSP_BITS_PER_SAMPLE)/(RX_DMA_BUFFER_SIZE/2))
#define FrameTimeL88 (84*RX_FREQUENCY/DEVICE_FREQ)

// number of ticks wide a message is
#define MESSAGE_LENGTH_L88 84

// Number of pulses in a message
#define NUM_PULSES_PER_FRAME_L88 6

#define TwICD        (UINT16)((.00200 * ACTUAL_TX_FREQ)/PERIODS_IN_BYTE)
#define T0ICD        (UINT16)((.00090 * ACTUAL_TX_FREQ)/PERIODS_IN_BYTE)
#define T1ICD        (UINT16)((.00220 * ACTUAL_TX_FREQ)/PERIODS_IN_BYTE)
#define TbICD        (UINT16)((.00035 * ACTUAL_TX_FREQ)/PERIODS_IN_BYTE)
#define TrbICD       (UINT16)((.00011 * ACTUAL_TX_FREQ)/PERIODS_IN_BYTE)
#define TeICD        (UINT16)((.00200 * ACTUAL_TX_FREQ)/PERIODS_IN_BYTE)
#define ThreplyICD   (UINT16)((.00052 * RX_FREQUENCY/RX_MCBSP_BITS_PER_SAMPLE)/(RX_DMA_BUFFER_SIZE/2))
#define FrameTimeICD (64*RX_FREQUENCY/DEVICE_FREQ)

// number of ticks wide a message is
#define MESSAGE_LENGTH_ICD 64

// Number of pulses in a message
#define NUM_PULSES_PER_FRAME_ICD 5

SCOPE UINT16 Tw;
SCOPE UINT16 T0;
SCOPE UINT16 T1;
SCOPE UINT16 Tb;
SCOPE UINT16 Trb;
SCOPE UINT16 Te;
SCOPE UINT16 Threply;
SCOPE UINT16 FrameTime;
SCOPE UINT16 SamplesPerFrame;
SCOPE UINT16 NumPulsesPerFrame;

/* Function Prototypes */
void ProcessReceivedDataL88(UINT16 CurrPulse);
void ProcessReceivedDataIcd(UINT16 CurrPulse);
tat_status ReceiveMemoryUplink( USHORT expectedUplinkBytes,
                                BYTE   timeoutLimit,
                                BYTE   *uplinkBuffer);
tat_status ReceiveMemoryUplinkL88( USHORT expectedUplinkBytes,
                                   BYTE   timeoutLimit,
                                   BYTE   *uplinkBuffer);
tat_status ReceiveMemoryUplinkIcd( USHORT expectedUplinkBytes,
                                   BYTE   timeoutLimit,
                                   BYTE   *uplinkBuffer);
void TurnOnReceiver(void);
void TurnOffReceiver(void);

#endif
