/************************************************************************
*
* MODULE: tam_TransmitCommon.c
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the functions common to Telemetry A to
*              transmit data.
*
*************************************************************************/

#include "global.h"

#include <csl.h>
#include <csl_gpio.h>
#include <csl_mcbsp.h>
#include <clk.h>

#include <string.h>

#include "tam_TelemetryA.h"
#include "tam_TransmitCommon.h"

////////////
// Defines
////////////

#define NUM_OF_PHASE_REVERSED_CYCLES 2

#define BURST_CHAR 0xFF00

#define DEADBAND_CHAR 0x0000

#define TX_DMA_BUFFER_SIZE 256

#define TX_TIMEOUT 10

////////////
// Globals
////////////

// Pointer to the TxDmaBuffer of the current byte that is being transmitted
BYTE* TxBufferPtr;

// Number of bytes left to transmit out of the TxDmaBuffer
UINT16 TxBytesLeft;

// The bit that is being transmitted
UINT16 TxBufferBitMask = 0x01;

UINT16 TxDmaBuffer[TX_DMA_BUFFER_SIZE];

#pragma DATA_SECTION(ShortMessageBuffer, ".repeatbuffer");
UINT16 ShortMessageBuffer[32768];


/* Private Function Prototype*/
BOOL FillTxDmaBuffer(UINT16 BaseIndex);

static void WaitForDmaFlag(volatile BOOL* pFlag);
static volatile BOOL gotHalf;
static volatile BOOL gotBlock;
static volatile BOOL gotFinal;
static BOOL          singleBufferTx;


/******************************************************************

FUNCTION: InitializeMcbsp

DESCRIPTION:  This function initializes the McBSP to transmit.

ARGS:
    <none>

RETURNS:
    <none>

******************************************************************/
static void InitializeMcbsp()
{
    MCBSP_Config mcbspCfgTx = {
        0x0000, //Serial Port Control Register 1
        0x0000, //Serial Port Control Register 2
        0x0000, //Receive Control Register 1
                //  0x00 = 8 bit word
                //  0x3f = 63 = (63 + 1) == 64 word frame
        0x0004, //Receive Control Register 2
                //  ignore unexpected FS, 1 bit delay, single phase, LSB received first

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

        0x0000, //Multichannel Control Register 1
        0x0000, //Multichannel Control Register 2
        0x0f00, //Pin Control Register
        0x0000, //Receive Channel Enable Register Partition A
        0x0000, //Receive Channel Enable Register Partition B
        0x0000, //Receive Channel Enable Register Partition C
        0x0000, //Receive Channel Enable Register Partition D
        0x0000, //Receive Channel Enable Register Partition E
        0x0000, //Receive Channel Enable Register Partition F
        0x0000, //Receive Channel Enable Register Partition G
        0x0000, //Receive Channel Enable Register Partition H
        0x0000, //Transmit Channel Enable Register Partition A
        0x0000, //Transmit Channel Enable Register Partition B
        0x0000, //Transmit Channel Enable Register Partition C
        0x0000, //Transmit Channel Enable Register Partition D
        0x0000, //Transmit Channel Enable Register Partition E
        0x0000, //Transmit Channel Enable Register Partition F
        0x0000, //Transmit Channel Enable Register Partition G
        0x0000  //Transmit Channel Enable Register Partition H
    };

    // Configure the McBSP for receive operation.
    MCBSP_config(hMcbsp_TelemA, &mcbspCfgTx);
}

/******************************************************************

FUNCTION: InitializeDma

DESCRIPTION:  This function initializes the DMA to transmit.

ARGS:
    <none>

RETURNS:
    <none>

******************************************************************/
static void InitializeDma()
{
    Uint32     addr;
    DMA_Config gDmaConfigTx = {

        //Source/Destination Register - DMACSDP
        DMA_DMACSDP_RMK(
            DMA_DMACSDP_DSTBEN_NOBURST,
            DMA_DMACSDP_DSTPACK_OFF,
            DMA_DMACSDP_DST_PERIPH,
            DMA_DMACSDP_SRCBEN_NOBURST,
            DMA_DMACSDP_SRCPACK_OFF,
            DMA_DMACSDP_SRC_EMIF,
            DMA_DMACSDP_DATATYPE_16BIT
            ),

        //Control Register - DMACCR
        DMA_DMACCR_RMK(
            DMA_DMACCR_DSTAMODE_CONST,
            DMA_DMACCR_SRCAMODE_POSTINC,
            DMA_DMACCR_ENDPROG_OFF,
            DMA_DMACCR_REPEAT_ON,
            DMA_DMACCR_AUTOINIT_ON,
            DMA_DMACCR_EN_STOP,
            DMA_DMACCR_PRIO_HI,
            DMA_DMACCR_FS_DISABLE,
            DMA_DMACCR_SYNC_XEVT0
            ),

        //Interrupt Control Register - DMACICR
        DMA_DMACICR_RMK(
            DMA_DMACICR_BLOCKIE_ON,
            DMA_DMACICR_LASTIE_OFF,
            DMA_DMACICR_FRAMEIE_OFF,
            DMA_DMACICR_FIRSTHALFIE_ON,
            DMA_DMACICR_DROPIE_OFF,
            DMA_DMACICR_TIMEOUTIE_OFF
            ),
        0, //Lower Source Address - DMACSSAL
        0, //Upper Source Address - DMACSSAU
        0, //Lower Destination Address - DMACDSAL
        0, //Upper Destination Address - DMACDSAU
        TX_DMA_BUFFER_SIZE, //Element Number - DMACEN
        1, //Frame Number - DMACFN
        0, //Frame Index - DMACFI
        0  //Element Index - DMACEI
    };

    // DMA source address for all transfers.
    addr                  = ((Uint32)&_MCBSP_DXR10) << 1;
    gDmaConfigTx.dmacdsal = (DMA_AdrPtr)(addr & 0xffff);
    gDmaConfigTx.dmacdsau = (Uint16)((addr >> 16) & 0xffff);

    // DMA destination address for the 1st transfer.
    addr                  = ((Uint32)&TxDmaBuffer[0]) << 1;
    gDmaConfigTx.dmacssal = (DMA_AdrPtr)(addr & 0xffff);
    gDmaConfigTx.dmacssau = (Uint16)((addr >> 16) & 0xffff);

    // Write values from DMA config structure to DMA channel control registers
    DMA_config(hDma_Tx, &gDmaConfigTx);

    // Clear out any pending interrupts.
    DMA_RGETH(hDma_Tx, DMACSR);

    // Start receive DMA
    DMA_start(hDma_Tx);
}

/******************************************************************

FUNCTION: InitializeDmaForHandshake

DESCRIPTION:  This function initializes the DMA to transmit the
              handshake pulse.

ARGS:
    <none>

RETURNS:
    <none>

******************************************************************/
static void InitializeDmaForHandshake()
{
    Uint32     addr;
    DMA_Config gDmaConfigTx = {

        //Source/Destination Register - DMACSDP
        DMA_DMACSDP_RMK(
            DMA_DMACSDP_DSTBEN_NOBURST,
            DMA_DMACSDP_DSTPACK_OFF,
            DMA_DMACSDP_DST_PERIPH,
            DMA_DMACSDP_SRCBEN_NOBURST,
            DMA_DMACSDP_SRCPACK_OFF,
            DMA_DMACSDP_SRC_EMIF,
            DMA_DMACSDP_DATATYPE_16BIT
            ),

        //Control Register - DMACCR
        DMA_DMACCR_RMK(
            DMA_DMACCR_DSTAMODE_CONST,
            DMA_DMACCR_SRCAMODE_POSTINC,
            DMA_DMACCR_ENDPROG_OFF,
            DMA_DMACCR_REPEAT_OFF,
            DMA_DMACCR_AUTOINIT_OFF,
            DMA_DMACCR_EN_STOP,
            DMA_DMACCR_PRIO_HI,
            DMA_DMACCR_FS_DISABLE,
            DMA_DMACCR_SYNC_XEVT0
            ),

        //Interrupt Control Register - DMACICR
        DMA_DMACICR_RMK(
            DMA_DMACICR_BLOCKIE_ON,
            DMA_DMACICR_LASTIE_OFF,
            DMA_DMACICR_FRAMEIE_OFF,
            DMA_DMACICR_FIRSTHALFIE_OFF,
            DMA_DMACICR_DROPIE_OFF,
            DMA_DMACICR_TIMEOUTIE_OFF
            ),
        0, //Lower Source Address - DMACSSAL
        0, //Upper Source Address - DMACSSAU
        0, //Lower Destination Address - DMACDSAL
        0, //Upper Destination Address - DMACDSAU
        1, //Element Number - DMACEN
        1, //Frame Number - DMACFN
        0, //Frame Index - DMACFI
        0  //Element Index - DMACEI
    };

    // DMA source address for all transfers.
    addr                  = ((Uint32)&_MCBSP_DXR10) << 1;
    gDmaConfigTx.dmacdsal = (DMA_AdrPtr)(addr & 0xffff);
    gDmaConfigTx.dmacdsau = (Uint16)((addr >> 16) & 0xffff);

    // DMA destination address for the 1st transfer.
    addr                  = ((Uint32)&TxDmaBuffer[0]) << 1;
    gDmaConfigTx.dmacssal = (DMA_AdrPtr)(addr & 0xffff);
    gDmaConfigTx.dmacssau = (Uint16)((addr >> 16) & 0xffff);

    // set the number of elements to transmit
    gDmaConfigTx.dmacen   = Trb+NUM_OF_PHASE_REVERSED_CYCLES+1;

    memset(&TxDmaBuffer[0], BURST_CHAR, Trb);
    memset(&TxDmaBuffer[Trb], ~BURST_CHAR, NUM_OF_PHASE_REVERSED_CYCLES);
    memset(&TxDmaBuffer[Trb+NUM_OF_PHASE_REVERSED_CYCLES], 0, 1); // put a '0' at the end

    // Write values from DMA config structure to DMA channel control registers
    DMA_config(hDma_TxHandshake, &gDmaConfigTx);

    // Clear out any pending interrupts.
    DMA_RGETH(hDma_TxHandshake, DMACSR);

    // Start receive DMA
    DMA_start(hDma_TxHandshake);
}

/******************************************************************

FUNCTION: InitializeTxDmaIrq

DESCRIPTION:  This function initializes the DMA interrupts.

ARGS:
    <none>

RETURNS:
    <none>

******************************************************************/
static void InitializeTxDmaIrq()
{
    Uint16 eventID;

    // Get Event ID associated with the DMA channel interrupt
    eventID = DMA_getEventId(hDma_Tx);

    // Clear any pending channel interrupt (IFR)
    IRQ_clear(eventID);

    // Enable DMA interrupt (IER)
    IRQ_enable(eventID);

    // Enable all interrupts (INTM)
    IRQ_globalEnable();
}

/******************************************************************

FUNCTION: InitializeTxHandshakeDmaIrq

DESCRIPTION:  This function initializes the DMA interrupts for
              handshaking.

ARGS:
    <none>

RETURNS:
    <none>

******************************************************************/
static void InitializeTxHandshakeDmaIrq()
{
    Uint16 eventID;

    // Get Event ID associated with the DMA channel interrupt
    eventID = DMA_getEventId(hDma_TxHandshake);

    // Clear any pending channel interrupt (IFR)
    IRQ_clear(eventID);

    // Enable DMA interrupt (IER)
    IRQ_enable(eventID);

    // Enable all interrupts (INTM)
    IRQ_globalEnable();
}

/******************************************************************

FUNCTION: TransmitDownlinkBuffer

DESCRIPTION:  This function transmits a message.  The message is
              converted into McBSP data 1/2 a buffer length at a time.
              The DMA signals an interrupt when the 1/2 of the buffer was
              sent, and an interrupt fills the buffer with new data.

ARGS:
  BYTE* Buffer: An array of bytes to send to the device.
  UINT16 Length: The number of bytes to send.

RETURNS:
    <none>

******************************************************************/
void TransmitDownlinkBuffer(BYTE* Buffer, UINT16 Length)
{
    Uint16 eventID;

    TurnOffReceiver();
    
    // Set the transmit parameters
    TxBufferPtr     = Buffer;
    TxBytesLeft     = Length;
    TxBufferBitMask = 0x01;

    eventID         = DMA_getEventId(hDma_Tx);

    // turn on the transmit side of the antenna
    SetAntennaToTransmit_M();

    FillTxDmaBuffer(0);
    FillTxDmaBuffer(TX_DMA_BUFFER_SIZE/2);

    gotHalf        = FALSE;
    gotBlock       = FALSE;
    gotFinal       = FALSE;
    singleBufferTx = TRUE;

    InitializeMcbsp();
    InitializeDma();
    InitializeTxDmaIrq();

    // Start McBSP0
    MCBSP_start( hMcbsp_TelemA,
                 MCBSP_XMIT_START | MCBSP_SRGR_START | MCBSP_SRGR_FRAMESYNC,
                 MCBSP_SRGR_DEFAULT_DELAY);

    while(1)
    {
        //wait for the first HALF of the DMA transfer to finish
        WaitForDmaFlag(&gotHalf);

        if(!FillTxDmaBuffer(0))
            break; //no more data to Tx

        //wait for the rest of the BLOCK of the DMA transfer to finish
        WaitForDmaFlag(&gotBlock);

        if(!FillTxDmaBuffer(TX_DMA_BUFFER_SIZE/2))
            break; //no more data to Tx
    }

    DMA_FSETH (hDma_Tx, DMACCR, REPEAT, 0);

    //wait for last complete BLOCK
    //Note, a flag other than gotBlock MUST be used here
    WaitForDmaFlag(&gotFinal);

    // Disable the transmit DMA
    DMA_reset(hDma_Tx);
    IRQ_disable(eventID);
    IRQ_clear(eventID);
    singleBufferTx = FALSE;

    // Reset McBSP0
    MCBSP_reset(hMcbsp_TelemA);
    IRQ_clear(MCBSP_getRcvEventId(hMcbsp_TelemA));

    //See TMS320VC5502 Silicon Errata (SPRZ020K), Oct. 2004
    //Advisory DMA_2
    DMA_FSETH (hDma_Tx, DMACCR, SYNC, 0);
}

/******************************************************************

FUNCTION: WaitForDmaFlag

DESCRIPTION:  This function is used to wait for a particular flag
              to be set by the DMA interrupt.  If the flag is not
              set within a certain amount of time, the function
              will timeout.

ARGS:
  BOOL flag: The flag that the software will wait to be set

RETURNS:
    <none>

******************************************************************/
static void WaitForDmaFlag(volatile BOOL* pFlag)
{
    GLB_LTMR_OBJ StartTime;

    // set timeout timer
    GLB_GET_LTMR(StartTime);

    do
    {
        if( GLB_HAS_LTMR_EXPIRED(StartTime, TX_TIMEOUT) )
        {
            break;
        }
    } while( !(*pFlag) );

    *pFlag = FALSE;
}

/******************************************************************

FUNCTION: FillTxDmaBuffer

DESCRIPTION:  This function fills 1/2 of the TxDmaBuffer with the
              next set of data for the waveform.

ARGS:
  UINT16 BaseIndex: The Starting index in the DMA Buffer.

RETURNS:
    TRUE if there is more data to send.
    FALSE if the waveform is finished.

******************************************************************/
BOOL FillTxDmaBuffer(UINT16 BaseIndex)
{
    typedef enum
    {
        SEND_WAKEUP_BURST,
        SEND_WAKE_INVERSE,
        SEND_DEADBAND,
        SEND_TB_BURST,
        SEND_PHASE_INVERSE,
        SEND_TE_DEADBAND,
        CLEAN_UP1,
        CLEAN_UP2
    } TxDmaIrqState;

    static TxDmaIrqState State        = SEND_WAKEUP_BURST;

    static UINT16 CurrentStateCounter = 0;

    UINT16 i                          = 0;
    UINT16 NumberOfWordsToCopy;

    // loop through 1/2 the buffer
    while( i < TX_DMA_BUFFER_SIZE/2 )
    {
        switch(State)
        {
        case SEND_WAKEUP_BURST:
        {
            // will the rest of this wave fit in the buffer?
            if( Tw - CurrentStateCounter < TX_DMA_BUFFER_SIZE/2 - i)
            {
                NumberOfWordsToCopy = Tw - CurrentStateCounter;
                State               = SEND_WAKE_INVERSE;
                CurrentStateCounter = 0;
            }
            // otherwise, just fill the buffer
            else
            {
                NumberOfWordsToCopy  = TX_DMA_BUFFER_SIZE/2 - i;
                CurrentStateCounter += NumberOfWordsToCopy;
            }

            memset(&TxDmaBuffer[BaseIndex + i], BURST_CHAR, NumberOfWordsToCopy);
            i = i + NumberOfWordsToCopy;
            break;
        }
        case SEND_WAKE_INVERSE:
        {
            // will the rest of this wave fit in the buffer?
            if( NUM_OF_PHASE_REVERSED_CYCLES - CurrentStateCounter < TX_DMA_BUFFER_SIZE/2 - i)
            {
                NumberOfWordsToCopy = NUM_OF_PHASE_REVERSED_CYCLES - CurrentStateCounter;
                State               = SEND_DEADBAND;
                CurrentStateCounter = 0;
            }
            // otherwise, just fill the buffer
            else
            {
                NumberOfWordsToCopy  = TX_DMA_BUFFER_SIZE/2 - i;
                CurrentStateCounter += NumberOfWordsToCopy;
            }

            memset(&TxDmaBuffer[BaseIndex + i], ~BURST_CHAR, NumberOfWordsToCopy);
            i = i + NumberOfWordsToCopy;
            break;
        }
        case SEND_DEADBAND:
        {
            UINT16 WidthOfDeadband;
            if( (*TxBufferPtr & TxBufferBitMask) == 0 )
            {
                // Set the number of elements
                WidthOfDeadband = T0-Tb-1;
            }
            else
            {
                // Set the number of elements
                WidthOfDeadband = T1-Tb-1;
            }

            // will the rest of this wave fit in the buffer?
            if( WidthOfDeadband - CurrentStateCounter < TX_DMA_BUFFER_SIZE/2 - i)
            {
                NumberOfWordsToCopy = WidthOfDeadband - CurrentStateCounter;
                State               = SEND_TB_BURST;
                CurrentStateCounter = 0;
            }
            // otherwise, just fill the buffer
            else
            {
                NumberOfWordsToCopy  = TX_DMA_BUFFER_SIZE/2 - i;
                CurrentStateCounter += NumberOfWordsToCopy;
            }

            memset(&TxDmaBuffer[BaseIndex + i], DEADBAND_CHAR, NumberOfWordsToCopy);
            i = i + NumberOfWordsToCopy;
            break;
        }
        case SEND_TB_BURST:
        {
            // will the rest of this wave fit in the buffer?
            if( Tb - CurrentStateCounter < TX_DMA_BUFFER_SIZE/2 - i)
            {
                NumberOfWordsToCopy = Tb - CurrentStateCounter;
                State               = SEND_PHASE_INVERSE;
                CurrentStateCounter = 0;
            }
            // otherwise, just fill the buffer
            else
            {
                NumberOfWordsToCopy  = TX_DMA_BUFFER_SIZE/2 - i;
                CurrentStateCounter += NumberOfWordsToCopy;
            }

            memset(&TxDmaBuffer[BaseIndex + i], BURST_CHAR, NumberOfWordsToCopy);
            i = i + NumberOfWordsToCopy;
            break;
        }
        case SEND_PHASE_INVERSE:
        {
            // will the rest of this wave fit in the buffer?
            if( NUM_OF_PHASE_REVERSED_CYCLES - CurrentStateCounter < TX_DMA_BUFFER_SIZE/2 - i)
            {
                // goto the next bit
                TxBufferBitMask = TxBufferBitMask << 1;

                // if the bit has moved outside of a byte
                if( TxBufferBitMask == 0x0100 )
                {
                    // Reset the mask
                    TxBufferBitMask = 0x01;
                    TxBufferPtr++;

                    TxBytesLeft--;

                    // if there are no more bytes to send...
                    if( TxBytesLeft == 0 )
                    {
                        // Send the End of Message signal
                        State = SEND_TE_DEADBAND;
                    }
                    // otherwise we need to send another byte
                    else
                    {
                        State = SEND_DEADBAND;
                    }
                }
                // otherwise we need to send another bit
                else
                {
                    State = SEND_DEADBAND;
                }

                NumberOfWordsToCopy = NUM_OF_PHASE_REVERSED_CYCLES - CurrentStateCounter;
                CurrentStateCounter = 0;
            }
            // otherwise, just fill the buffer
            else
            {
                NumberOfWordsToCopy  = TX_DMA_BUFFER_SIZE/2 - i;
                CurrentStateCounter += NumberOfWordsToCopy;
            }

            memset(&TxDmaBuffer[BaseIndex + i], ~BURST_CHAR, NumberOfWordsToCopy);
            i = i + NumberOfWordsToCopy;
            break;
        }
        case SEND_TE_DEADBAND:
        {
            // will the rest of this wave fit in the buffer?
            if( Te - CurrentStateCounter < TX_DMA_BUFFER_SIZE/2 - i)
            {
                NumberOfWordsToCopy = Te - CurrentStateCounter;
                State               = CLEAN_UP1;
                CurrentStateCounter = 0;
            }
            // otherwise, just fill the buffer
            else
            {
                NumberOfWordsToCopy  = TX_DMA_BUFFER_SIZE/2 - i;
                CurrentStateCounter += NumberOfWordsToCopy;
            }

            memset(&TxDmaBuffer[BaseIndex + i], DEADBAND_CHAR, NumberOfWordsToCopy);
            i = i + NumberOfWordsToCopy;
            break;
        }
        case CLEAN_UP1:
        {
            NumberOfWordsToCopy = TX_DMA_BUFFER_SIZE/2;
            memset(&TxDmaBuffer[BaseIndex + i], DEADBAND_CHAR, NumberOfWordsToCopy-i);
            State               = CLEAN_UP2;
            CurrentStateCounter = 0;
            break;
        }
        case CLEAN_UP2:
        {
            NumberOfWordsToCopy = TX_DMA_BUFFER_SIZE/2;
            memset(&TxDmaBuffer[BaseIndex + i], DEADBAND_CHAR, NumberOfWordsToCopy-i);
            State               = SEND_WAKEUP_BURST;
            // nothing else to do
            return FALSE;
        }
        }
    }
    return TRUE;
}

/******************************************************************

FUNCTION: TransmitHandshake

DESCRIPTION:  The HandshakeIrq is to send the handshake pulse after
              the instrument has received a handshake uplink.

ARGS:
  <none>

RETURNS:
  <none>

******************************************************************/
void TransmitHandshake(void)
{
    TurnOffReceiver();

    // turn on the transmit side of the antenna
    SetAntennaToTransmit_M();

    InitializeMcbsp();
    InitializeDmaForHandshake();
    InitializeTxHandshakeDmaIrq();

    // Start McBSP0
    MCBSP_start(
        hMcbsp_TelemA,
        MCBSP_XMIT_START | MCBSP_SRGR_START | MCBSP_SRGR_FRAMESYNC,
        100);
    // the 100 is the sample delay which is (2*SampleRatePeriod)/(4*InstructionCycle), or
    //                                      (2*3.57e-7)/(4*3.33e-9) = 53.
    //  I made this bigger just to be on the safe side.
}

/******************************************************************

FUNCTION: tam_EndOfHandshakePulseIrq

DESCRIPTION:  This interrupt happens after the DMA has transferred
              all the data to the McBSP for the handshake burst.
              The McBSP is configured for receiving and the DMA
              interrupt vector is pointed back to the TxDmaIsr.

ARGS:
  <none>

RETURNS:
  <none>

******************************************************************/
interrupt void tam_EndOfHandshakePulseIrq(void)
{
    MCBSP_reset(hMcbsp_TelemA);
    IRQ_clear(MCBSP_getRcvEventId(hMcbsp_TelemA));

    DMA_reset(hDma_TxHandshake);

    TurnOnReceiver();

    SetAntennaToReceive_M();
}

/******************************************************************

FUNCTION: TransmitShortMessage

DESCRIPTION:  This function transmits a short message by converting
              the entire message to McBSP data and then using the
              DMA to transmit all of it without CPU intervention.

ARGS:
  BYTE* Buffer: Pointer to the message to send.
  UINT16 Length: Number of bytes in the buffer.

RETURNS:
  <none>

******************************************************************/
void TransmitShortMessage(BYTE* Buffer, UINT16 Length)
{
    Uint32 addr;

    DMA_Config gDmaConfigTx = {

        //Source/Destination Register - DMACSDP
        DMA_DMACSDP_RMK(
            DMA_DMACSDP_DSTBEN_NOBURST,
            DMA_DMACSDP_DSTPACK_OFF,
            DMA_DMACSDP_DST_PERIPH,
            DMA_DMACSDP_SRCBEN_NOBURST,
            DMA_DMACSDP_SRCPACK_OFF,
            DMA_DMACSDP_SRC_EMIF,
            DMA_DMACSDP_DATATYPE_16BIT
            ),

        //Control Register - DMACCR
        DMA_DMACCR_RMK(
            DMA_DMACCR_DSTAMODE_CONST,
            DMA_DMACCR_SRCAMODE_POSTINC,
            DMA_DMACCR_ENDPROG_ON,
            DMA_DMACCR_REPEAT_OFF,
            DMA_DMACCR_AUTOINIT_OFF,
            DMA_DMACCR_EN_STOP,
            DMA_DMACCR_PRIO_HI,
            DMA_DMACCR_FS_DISABLE,
            DMA_DMACCR_SYNC_XEVT0
            ),

        //Interrupt Control Register - DMACICR
        DMA_DMACICR_RMK(
            DMA_DMACICR_BLOCKIE_ON,
            DMA_DMACICR_LASTIE_OFF,
            DMA_DMACICR_FRAMEIE_OFF,
            DMA_DMACICR_FIRSTHALFIE_OFF,
            DMA_DMACICR_DROPIE_OFF,
            DMA_DMACICR_TIMEOUTIE_OFF
            ),

        0, //Lower Source Address - DMACSSAL
        0, //Upper Source Address - DMACSSAU
        0, //Lower Destination Address - DMACDSAL
        0, //Upper Destination Address - DMACDSAU
        1, //Element Number - DMACEN
        1, //Frame Number - DMACFN
        0, //Frame Index - DMACFI
        0  //Element Index - DMACEI
    };

    UINT16 TxBufferBitMask = 0x01;
    UINT16 Index           = 0;

    // turn on the transmit side of the antenna
    SetAntennaToTransmit_M();

    memset(&ShortMessageBuffer[Index], BURST_CHAR, Tw);
    memset(&ShortMessageBuffer[Index + Tw], ~BURST_CHAR, NUM_OF_PHASE_REVERSED_CYCLES);

    Index += Tw + NUM_OF_PHASE_REVERSED_CYCLES;

    while( Length > 0 )
    {
        // Determine which bit pattern to send.
        if( (*Buffer & TxBufferBitMask) == 0 )
        {
            memset(&ShortMessageBuffer[Index], DEADBAND_CHAR, T0 - Tb);
            memset(&ShortMessageBuffer[Index + T0-Tb], BURST_CHAR, Tb);
            memset(&ShortMessageBuffer[Index + T0], ~BURST_CHAR, NUM_OF_PHASE_REVERSED_CYCLES);

            Index += T0 + NUM_OF_PHASE_REVERSED_CYCLES;
        }
        else
        {
            memset(&ShortMessageBuffer[Index], DEADBAND_CHAR, T1 - Tb);
            memset(&ShortMessageBuffer[Index + T1-Tb], BURST_CHAR, Tb);
            memset(&ShortMessageBuffer[Index + T1], ~BURST_CHAR, NUM_OF_PHASE_REVERSED_CYCLES);

            Index += T1 + NUM_OF_PHASE_REVERSED_CYCLES;
        }

        // goto the next bit
        TxBufferBitMask = TxBufferBitMask << 1;

        // if the bit has moved outside of a byte
        if( TxBufferBitMask == 0x0100 )
        {
            // Reset the mask
            TxBufferBitMask = 0x01;
            Buffer++;
            Length--;
        }
    }

    memset(&ShortMessageBuffer[Index], DEADBAND_CHAR, Te);

    Index += Te;

    InitializeMcbsp();

    // DMA source address for all transfers.
    addr                  = ((Uint32)&_MCBSP_DXR10) << 1;
    gDmaConfigTx.dmacdsal = (DMA_AdrPtr)(addr & 0xffff);
    gDmaConfigTx.dmacdsau = (Uint16)((addr >> 16) & 0xffff);

    // DMA destination address for the 1st transfer.
    addr                  = ((Uint32)&ShortMessageBuffer[0]) << 1;
    gDmaConfigTx.dmacssal = (DMA_AdrPtr)(addr & 0xffff);
    gDmaConfigTx.dmacssau = (Uint16)((addr >> 16) & 0xffff);

    gDmaConfigTx.dmacen   = Index;

    // Write values from DMA config structure to DMA channel control registers
    DMA_config(hDma_Tx, &gDmaConfigTx);

    // Clear out any pending interrupts.
    DMA_RGETH(hDma_Tx, DMACSR);

    // Start receive DMA
    DMA_start(hDma_Tx);

    InitializeTxDmaIrq();

    // Start McBSP0
    MCBSP_start(
        hMcbsp_TelemA,
        MCBSP_XMIT_START | MCBSP_SRGR_START | MCBSP_SRGR_FRAMESYNC,
        MCBSP_SRGR_DEFAULT_DELAY);

}

/******************************************************************

FUNCTION: tam_EndOfRepeatTransmitIrq

DESCRIPTION:  This ISR now serves two purposes.  A. It is executed
              after the repeat message is sent to place the antenna
              into receive mode. B. It is used during single-buffer
              transmision to indicate when a half and whole block
              has been sent.

ARGS:
    <none>

RETURNS:
    <none>

******************************************************************/
interrupt void tam_EndOfRepeatTransmitIrq(void)
{
    if(singleBufferTx)
    {
        UINT16 StatusRegister = DMA_RGETH(hDma_Tx, DMACSR);

        if( (DMA_FGETH(hDma_Tx, DMACCR, REPEAT) == 0) && GLB_BIT_IS_SET(StatusRegister, 5) )
            gotFinal = TRUE;

        if( GLB_BIT_IS_SET(StatusRegister, 5) )
            gotBlock = TRUE;

        if( GLB_BIT_IS_SET(StatusRegister, 2) )
            gotHalf = TRUE;
    }
    else
        SetAntennaToReceive_M();
}
