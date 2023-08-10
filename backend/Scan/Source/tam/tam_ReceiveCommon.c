/************************************************************************
*
* MODULE: tam_ReceiveCommon.c
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the functions to receive Telemetry A
*              pulses.
*
*************************************************************************/

/////////////
// includes
/////////////

#include "global.h"

#include <sts.h>
#include <log.h>
#include <clk.h>
#include <csl_mcbsp.h>
//#include <csl_gpio.h>

#include "tam_global.h"
#include "tam_TelemetryA.h"
#include "tam_ReceiveCommon.h"
#include "tam_TransmitCommon.h"

#include "bsm_general.h"

////////////
// defines
////////////

// Debounce for 10 us
#define DEBOUNCE ((10*RX_FREQUENCY/RX_MCBSP_BITS_PER_SAMPLE)/1000000)

// Timeout for receiver shutdown (250 us)
#define RX_SHUTDOWN_TIMEOUT 250000

////////////
// globals
////////////

// States for the pulse processing
typedef enum
{
    NO_PULSE,
    START_PULSE,
    SYNC_PULSE,
    LOWER_NIBBLE,
    UPPER_NIBBLE,
    PARITY
} ProcessState;

// enumeration for the pulse positions
enum PulseNames
{
    SYNC            = 4,
    ID_9            = 9,
    ID_10           = 10,
    ID_11           = 11,
    ID_12           = 12,
    ID_13           = 13,
    ID_14           = 14,
    ID_15           = 15,
    ID_16           = 16,
    ID_17           = 17,
    ID_18           = 18,
    ID_19           = 19,
    LOWER_NIBBLE_0  = 24,
    LOWER_NIBBLE_1  = 25,
    LOWER_NIBBLE_2  = 26,
    LOWER_NIBBLE_3  = 27,
    LOWER_NIBBLE_4  = 28,
    LOWER_NIBBLE_5  = 29,
    LOWER_NIBBLE_6  = 30,
    LOWER_NIBBLE_7  = 31,
    LOWER_NIBBLE_8  = 32,
    LOWER_NIBBLE_9  = 33,
    LOWER_NIBBLE_A  = 34,
    LOWER_NIBBLE_B  = 35,
    LOWER_NIBBLE_C  = 36,
    LOWER_NIBBLE_D  = 37,
    LOWER_NIBBLE_E  = 38,
    LOWER_NIBBLE_F  = 39,
    UPPER_NIBBLE_0  = 44,
    UPPER_NIBBLE_1  = 45,
    UPPER_NIBBLE_2  = 46,
    UPPER_NIBBLE_3  = 47,
    UPPER_NIBBLE_4  = 48,
    UPPER_NIBBLE_5  = 49,
    UPPER_NIBBLE_6  = 50,
    UPPER_NIBBLE_7  = 51,
    UPPER_NIBBLE_8  = 52,
    UPPER_NIBBLE_9  = 53,
    UPPER_NIBBLE_A  = 54,
    UPPER_NIBBLE_B  = 55,
    UPPER_NIBBLE_C  = 56,
    UPPER_NIBBLE_D  = 57,
    UPPER_NIBBLE_E  = 58,
    UPPER_NIBBLE_F  = 59,
    PARITY_NIBBLE_0 = 64,
    PARITY_NIBBLE_1 = 65,
    PARITY_NIBBLE_2 = 66,
    PARITY_NIBBLE_3 = 67,
    PARITY_NIBBLE_4 = 68,
    PARITY_NIBBLE_5 = 69,
    PARITY_NIBBLE_6 = 70,
    PARITY_NIBBLE_7 = 71,
    PARITY_NIBBLE_8 = 72,
    PARITY_NIBBLE_9 = 73,
    PARITY_NIBBLE_A = 74,
    PARITY_NIBBLE_B = 75,
    PARITY_NIBBLE_C = 76,
    PARITY_NIBBLE_D = 77,
    PARITY_NIBBLE_E = 78,
    PARITY_NIBBLE_F = 79,
    IDLE            = 84
};

// State variable for the pulse processing
#pragma DATA_SECTION(State, ".tam_rx_data")
static ProcessState State;

// Data type of the frame.
#pragma DATA_SECTION(DataType, ".tam_rx_data")
static tat_frameType DataType;

// Time of the start pulse
#pragma DATA_SECTION(StartPulse, ".tam_rx_data")
static UINT16 StartPulse;

// Value of the lower nibble
#pragma DATA_SECTION(LowerNibble, ".tam_rx_data")
UINT16 LowerNibble;

// value of the upper nibble
#pragma DATA_SECTION(UpperNibble, ".tam_rx_data")
UINT16 UpperNibble;

// the number of received bytes to wait to send the handshake
#pragma DATA_SECTION(HandshakeHoldOff, ".tam_rx_data")
static UINT16 HandshakeHoldOff;

#pragma DATA_SECTION(HighBitCount, ".tam_rx_data")
static UINT16 HighBitCount;

#pragma DATA_SECTION(LowBitCount, ".tam_rx_data")
static UINT16 LowBitCount;

#pragma DATA_SECTION(Time, ".tam_rx_data")
static UINT16 Time;

// Flag used to indicate Rx has stopped
#pragma DATA_SECTION(RxStopped, ".tam_rx_data")
static volatile BOOL RxStopped;

#pragma DATA_SECTION(AgcPulseWidth, ".tam_rx_data")
UINT16 AgcPulseWidth[HIGH_GAIN + 1];

#pragma DATA_SECTION(DebouncedSignal, ".tam_rx_data")
UINT16 DebouncedSignal[HIGH_GAIN + 1];

#pragma DATA_SECTION(DebounceCount, ".tam_rx_data")
UINT16 DebounceCount[HIGH_GAIN + 1];

#pragma DATA_SECTION(AgcSampleCounter, ".tam_rx_data")
UINT16 AgcSampleCounter;

#pragma DATA_SECTION(NewAgcPulseSelect, ".tam_rx_data")
UINT16 NewAgcPulseSelect;

#pragma DATA_SECTION(NeedToChangeAgcPulseSelect, ".tam_rx_data")
BOOL NeedToChangeAgcPulseSelect;

/******************************************************************

FUNCTION: tam_ProcessRxDmaBuffer

DESCRIPTION:  This function is called when the DMA has filled 1/2
              or all of the buffer.  The function processes the data
              looking for a rising edge.  When a rising edge is found,
              the specific edge processing function is called.

ARGS:
  <none>

RETURNS:
    <none>

******************************************************************/
#pragma CODE_SECTION(tam_ProcessRxDmaBuffer, ".tam_rx_text")
interrupt void tam_ProcessRxDmaBuffer(void)
{
    // BaseIndex is either 0 or RX_DMA_BUFFER_SIZE/2 based on if this interrupt was
    // caused by the half or block interrupt;
    UINT16 BaseIndex;

    // index for going through the DMA Buffer and gain selection
    INT16 i, j;

    // Need to save the DMA Status Register because it clears after the first read
    UINT16 StatusRegister;

    // Clear the interrupt flag
    StatusRegister = DMA_RGET(DMACSR1);

    StatusRegister = (StatusRegister & (_DMA_DMACSR_HALF_MASK|_DMA_DMACSR_BLOCK_MASK));

    if( StatusRegister == _DMA_DMACSR_HALF_MASK )
    {
        BaseIndex = 0;
    }
    else if( StatusRegister == _DMA_DMACSR_BLOCK_MASK )
    {
        if( DMA_FGETH(hDma_Rx, DMACCR, REPEAT) == 0 )
        {
            RxStopped = TRUE;
            return;
        }

        BaseIndex = RX_DMA_BUFFER_SIZE/2;
    }
    else
    {
        // bad interrupt
        return;
    }

    for( i = 0; i < RX_DMA_BUFFER_SIZE/2; i++ )
    {
        // Debounce the signal
        for( j = LOW_GAIN; j <= HIGH_GAIN; j++ )
        {
            // if the sampled signal is different than the debounced signal...
            if( DebouncedSignal[j] != (RxDmaBuffer[BaseIndex+i] & (1<<(j))) )
            {
                DebounceCount[j]--;

                // if we saw enough of the different signal...
                if( DebounceCount[j] <= 0 )
                {
                    // Count the signal as debounced
                    DebouncedSignal[j] = RxDmaBuffer[BaseIndex+i] & (1<<(j));

                    // Reset the debounce counter
                    DebounceCount[j]   = DEBOUNCE;
                }
            }
            // the debounced signal is the same as the sampled signal
            else
            {
                // Reset the debounce counter
                DebounceCount[j] = DEBOUNCE;
            }
        }

        // Calculate the pulse widths
        for( j = LOW_GAIN; j <= HIGH_GAIN; j++ )
        {
            // if the debounced signal is high, then increment the AGC Pulse Width counter
            if( DebouncedSignal[j] != 0 )
            {
                AgcPulseWidth[j]++;
            }
            // if the signal is low, then we ended a pulse and it's time to check for the best AGC Signal
            else
            {
                // calculate the AGC if there was a pulse
                if( AgcPulseWidth[j] != 0 )
                {
                    // if the debounced pulse width is within a good range
                    if( AgcPulseWidth[j] < ((100*RX_FREQUENCY/RX_MCBSP_BITS_PER_SAMPLE)/1000000) &&
                        AgcPulseWidth[j] > ((15*RX_FREQUENCY/RX_MCBSP_BITS_PER_SAMPLE)/1000000) )
                    {
                        // Set the AGC Pulse Select to this gain setting
                        AgcPulseSelect = j;
                    }

                    if( j == LOW_GAIN && AgcPulseWidth[LOW_GAIN] > 100*RX_FREQUENCY/RX_MCBSP_BITS_PER_SAMPLE/1000000 )
                    {
                        AgcPulseSelect = LOW_GAIN;
                    }

                    AgcPulseWidth[j] = 0;
                }
            }
        }

        // Process the signal if the bit is a 0
        if( DebouncedSignal[AgcPulseSelect] == 0 )
        {
            // count the bit
            HighBitCount = 0;
            LowBitCount++;

            // if we went too long without a pulse
            if( LowBitCount >= NUM_FRAMES_IN_SEGMENT_TIME_ERROR*FrameTime )
            {
                // reset the count so we catch another long time without pulses
                LowBitCount = 0;
                StoreDataByte(0xFF, (tat_frameType)tac_telemetrySegmentTimeError);
            }
        }
        // if the bit is a 1
        else
        {
            LowBitCount = 0;
            HighBitCount++;

            // only process the edge when we get DEBOUNCE bits high
            // (it is set to '==' so that it is only called on the edge and not on the level)
            if( HighBitCount == 1 )
            {
                //_GPIO_IODATA ^= 0x10;
                (*ProcessReceivedData)(Time);
            }
        }

        // go to the next time
        Time++;
    }

    // Send the handshake if it is the correct time
    if( HandshakeHoldOff != 0 )
    {
        HandshakeHoldOff--;
        if( HandshakeHoldOff == 0 )
        {
            TransmitHandshake();
        }
    }
}


/******************************************************************

FUNCTION: StoreDataByte

DESCRIPTION:  This function stores a data byte in the buffer pointed
              to by DataPtr.

ARGS:
  UINT8 Data: The data byte to store in the buffer.
  tat_frameType DataType: The type of the data.

RETURNS:
    <none>

******************************************************************/
#pragma CODE_SECTION(StoreDataByte, ".tam_rx_text")
void StoreDataByte(UINT8 Data, tat_frameType DataType)
{
    RxData      = Data;
    RxDataType  = DataType;
    RxDataValid = TRUE;
}

/******************************************************************

FUNCTION: ProcessReceivedDataL88

DESCRIPTION:  This method is called when a valid pulse is detected.
              The pulse is process according to L88 or ICD, which
              ever is defined.

ARGS:
  UINT16 CurrPulse: The next pulse that has come in.

RETURNS:
  <none>

******************************************************************/
#pragma CODE_SECTION(ProcessReceivedDataL88, ".tam_rx_text")
void ProcessReceivedDataL88(UINT16 CurrPulse)
{
    // value of the parity
    UINT32 ParityNibble;  // RJD: can we change this to a UINT16?

    // Calculate the offset
    UINT16 PulseOffsetUs;

    PulseOffsetUs = ((CurrPulse - StartPulse)*RX_MCBSP_BITS_PER_SAMPLE); // /(RX_FREQUENCY/1000000);

    switch( State )
    {
    case NO_PULSE:
        // save the time of the start of frame pulse
        StartPulse = CurrPulse;
        State      = START_PULSE;
        break;

    case START_PULSE:
    {
        if( PulseOffsetUs >= (UINT16)(SYNC*(Tu) - .5*(Tu))*(RX_FREQUENCY/1000000) &&
            PulseOffsetUs <= (UINT16)(SYNC*(Tu) + .5*(Tu))*(RX_FREQUENCY/1000000) )
        {
            // We got a sync pulse, now look for the Frame ID pulse
            State = SYNC_PULSE;
        }
        else
        {
            // not a sync pulse, so mark this as the frame pulse
            StartPulse = CurrPulse;
        }
        break;
    }
    case SYNC_PULSE:
        if( PulseOffsetUs >= (UINT16)(ID_9*(Tu) - .5*(Tu))*(RX_FREQUENCY/1000000) &&
            PulseOffsetUs <= (UINT16)(ID_9*(Tu) + .5*(Tu))*(RX_FREQUENCY/1000000) )
        {
            // set the time to send a handshake burst
            HandshakeHoldOff = Threply;

            // send the handshake to the application
            StoreDataByte( 0, tac_handshakeRequestFrame );
            State = NO_PULSE;
        }
        else if( PulseOffsetUs >= (UINT16)(ID_11*(Tu) - .5*(Tu))*(RX_FREQUENCY/1000000) &&
                 PulseOffsetUs <= (UINT16)(ID_11*(Tu) + .5*(Tu))*(RX_FREQUENCY/1000000) )
        {
            State    = LOWER_NIBBLE;
            DataType = tac_primaryEgmFrame;
        }
        else if( PulseOffsetUs >= (UINT16)(ID_12*(Tu) - .5*(Tu))*(RX_FREQUENCY/1000000) &&
                 PulseOffsetUs <= (UINT16)(ID_12*(Tu) + .5*(Tu))*(RX_FREQUENCY/1000000) )
        {
            State    = LOWER_NIBBLE;
            DataType = tac_secondaryEgmFrame;
        }
        else if( PulseOffsetUs >= (UINT16)(ID_13*(Tu) - .5*(Tu))*(RX_FREQUENCY/1000000) &&
                 PulseOffsetUs <= (UINT16)(ID_13*(Tu) + .5*(Tu))*(RX_FREQUENCY/1000000) )
        {
            State    = LOWER_NIBBLE;
            DataType = tac_aux1EgmFrame;
        }
        else if( PulseOffsetUs >= (UINT16)(ID_14*(Tu) - .5*(Tu))*(RX_FREQUENCY/1000000) &&
                 PulseOffsetUs <= (UINT16)(ID_14*(Tu) + .5*(Tu))*(RX_FREQUENCY/1000000) )
        {
            State    = LOWER_NIBBLE;
            DataType = tac_aux2EgmFrame;
        }
        else if( PulseOffsetUs >= (UINT16)(ID_15*(Tu) - .5*(Tu))*(RX_FREQUENCY/1000000) &&
                 PulseOffsetUs <= (UINT16)(ID_15*(Tu) + .5*(Tu))*(RX_FREQUENCY/1000000) )
        {
            State    = LOWER_NIBBLE;
            DataType = tac_markerFrame;
        }
        else if( PulseOffsetUs >= (UINT16)(ID_17*(Tu) - .5*(Tu))*(RX_FREQUENCY/1000000) &&
                 PulseOffsetUs <= (UINT16)(ID_17*(Tu) + .5*(Tu))*(RX_FREQUENCY/1000000) )
        {
            State    = LOWER_NIBBLE;
            DataType = tac_memoryFrame;

        }
        else if( PulseOffsetUs >= (UINT16)(ID_19*(Tu) - .5*(Tu))*(RX_FREQUENCY/1000000) &&
                 PulseOffsetUs <= (UINT16)(ID_19*(Tu) + .5*(Tu))*(RX_FREQUENCY/1000000) )
        {
            State    = LOWER_NIBBLE;
            DataType = tac_handshakeConfirmFrame;
        }
        else if( PulseOffsetUs >= (UINT16)(IDLE*(Tu) - .5*(Tu))*(RX_FREQUENCY/1000000) &&
                 PulseOffsetUs <= (UINT16)(IDLE*(Tu) + .5*(Tu))*(RX_FREQUENCY/1000000) )
        {
            StoreDataByte( 0, tac_idleFrame );
            StartPulse = CurrPulse;
            State      = START_PULSE;
        }
        else
        {
            StartPulse = CurrPulse;
            State      = START_PULSE;
            StoreDataByte( 0, tac_invalidIdentifierFrame );
        }
        break;

    case LOWER_NIBBLE:
        if( PulseOffsetUs >= (UINT16)((LOWER_NIBBLE_0*Tu - .5*Tu)*(RX_FREQUENCY/1000000)) &&
            PulseOffsetUs <= (UINT16)((LOWER_NIBBLE_F*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
        {
            if( PulseOffsetUs <= (UINT16)((LOWER_NIBBLE_0*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                LowerNibble = LOWER_NIBBLE_0 - LOWER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((LOWER_NIBBLE_1*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                LowerNibble = LOWER_NIBBLE_1 - LOWER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((LOWER_NIBBLE_2*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                LowerNibble = LOWER_NIBBLE_2 - LOWER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((LOWER_NIBBLE_3*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                LowerNibble = LOWER_NIBBLE_3 - LOWER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((LOWER_NIBBLE_4*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                LowerNibble = LOWER_NIBBLE_4 - LOWER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((LOWER_NIBBLE_5*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                LowerNibble = LOWER_NIBBLE_5 - LOWER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((LOWER_NIBBLE_6*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                LowerNibble = LOWER_NIBBLE_6 - LOWER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((LOWER_NIBBLE_7*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                LowerNibble = LOWER_NIBBLE_7 - LOWER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((LOWER_NIBBLE_8*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                LowerNibble = LOWER_NIBBLE_8 - LOWER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((LOWER_NIBBLE_9*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                LowerNibble = LOWER_NIBBLE_9 - LOWER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((LOWER_NIBBLE_A*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                LowerNibble = LOWER_NIBBLE_A - LOWER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((LOWER_NIBBLE_B*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                LowerNibble = LOWER_NIBBLE_B - LOWER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((LOWER_NIBBLE_C*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                LowerNibble = LOWER_NIBBLE_C - LOWER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((LOWER_NIBBLE_D*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                LowerNibble = LOWER_NIBBLE_D - LOWER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((LOWER_NIBBLE_E*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                LowerNibble = LOWER_NIBBLE_E - LOWER_NIBBLE_0;
            }
            else
            {
                LowerNibble = LOWER_NIBBLE_F - LOWER_NIBBLE_0;
            }

            State = UPPER_NIBBLE;
        }
        else
        {
            StartPulse = CurrPulse;
            State      = START_PULSE;
            StoreDataByte( 0, tac_invalidIdentifierFrame );
        }
        break;

    case UPPER_NIBBLE:
        if( PulseOffsetUs >= (UINT16)(UPPER_NIBBLE_0*Tu - .5*Tu)*(RX_FREQUENCY/1000000) &&
            PulseOffsetUs <= (UINT16)(UPPER_NIBBLE_F*Tu + .5*Tu)*(RX_FREQUENCY/1000000) )
        {
            if( PulseOffsetUs <= (UINT16)((UPPER_NIBBLE_0*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                UpperNibble = UPPER_NIBBLE_0 - UPPER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((UPPER_NIBBLE_1*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                UpperNibble = UPPER_NIBBLE_1 - UPPER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((UPPER_NIBBLE_2*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                UpperNibble = UPPER_NIBBLE_2 - UPPER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((UPPER_NIBBLE_3*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                UpperNibble = UPPER_NIBBLE_3 - UPPER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((UPPER_NIBBLE_4*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                UpperNibble = UPPER_NIBBLE_4 - UPPER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((UPPER_NIBBLE_5*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                UpperNibble = UPPER_NIBBLE_5 - UPPER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((UPPER_NIBBLE_6*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                UpperNibble = UPPER_NIBBLE_6 - UPPER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((UPPER_NIBBLE_7*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                UpperNibble = UPPER_NIBBLE_7 - UPPER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((UPPER_NIBBLE_8*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                UpperNibble = UPPER_NIBBLE_8 - UPPER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((UPPER_NIBBLE_9*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                UpperNibble = UPPER_NIBBLE_9 - UPPER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((UPPER_NIBBLE_A*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                UpperNibble = UPPER_NIBBLE_A - UPPER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((UPPER_NIBBLE_B*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                UpperNibble = UPPER_NIBBLE_B - UPPER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((UPPER_NIBBLE_C*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                UpperNibble = UPPER_NIBBLE_C - UPPER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((UPPER_NIBBLE_D*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                UpperNibble = UPPER_NIBBLE_D - UPPER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((UPPER_NIBBLE_E*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                UpperNibble = UPPER_NIBBLE_E - UPPER_NIBBLE_0;
            }
            else
            {
                UpperNibble = UPPER_NIBBLE_F - UPPER_NIBBLE_0;
            }

            State = PARITY;
        }
        else
        {
            StartPulse = CurrPulse;
            State      = START_PULSE;
            StoreDataByte( 0, tac_invalidIdentifierFrame );
        }
        break;

    case PARITY:
        if( PulseOffsetUs >= (UINT16)(PARITY_NIBBLE_0*(Tu) - .5*(Tu))*(RX_FREQUENCY/1000000) &&
            PulseOffsetUs <= (UINT16)(PARITY_NIBBLE_F*(Tu) + .5*(Tu))*(RX_FREQUENCY/1000000) )
        {
            if( PulseOffsetUs <= (UINT16)((PARITY_NIBBLE_0*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                ParityNibble = PARITY_NIBBLE_0 - PARITY_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((PARITY_NIBBLE_1*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                ParityNibble = PARITY_NIBBLE_1 - PARITY_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((PARITY_NIBBLE_2*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                ParityNibble = PARITY_NIBBLE_2 - PARITY_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((PARITY_NIBBLE_3*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                ParityNibble = PARITY_NIBBLE_3 - PARITY_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((PARITY_NIBBLE_4*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                ParityNibble = PARITY_NIBBLE_4 - PARITY_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((PARITY_NIBBLE_5*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                ParityNibble = PARITY_NIBBLE_5 - PARITY_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((PARITY_NIBBLE_6*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                ParityNibble = PARITY_NIBBLE_6 - PARITY_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((PARITY_NIBBLE_7*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                ParityNibble = PARITY_NIBBLE_7 - PARITY_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((PARITY_NIBBLE_8*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                ParityNibble = PARITY_NIBBLE_8 - PARITY_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((PARITY_NIBBLE_9*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                ParityNibble = PARITY_NIBBLE_9 - PARITY_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((PARITY_NIBBLE_A*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                ParityNibble = PARITY_NIBBLE_A - PARITY_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((PARITY_NIBBLE_B*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                ParityNibble = PARITY_NIBBLE_B - PARITY_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((PARITY_NIBBLE_C*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                ParityNibble = PARITY_NIBBLE_C - PARITY_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((PARITY_NIBBLE_D*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                ParityNibble = PARITY_NIBBLE_D - PARITY_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((PARITY_NIBBLE_E*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                ParityNibble = PARITY_NIBBLE_E - PARITY_NIBBLE_0;
            }
            else
            {
                ParityNibble = PARITY_NIBBLE_F - PARITY_NIBBLE_0;
            }

            // check the parity
            if( LowerNibble ^ UpperNibble == ParityNibble )
            {
                // if the parity is good, store the byte
                StoreDataByte( (UpperNibble<<4)|LowerNibble, DataType );
            }

            State = NO_PULSE;
        }
        else
        {
            StartPulse = CurrPulse;
            State      = START_PULSE;
            StoreDataByte( 0, tac_invalidIdentifierFrame );
        }
        break;
    default:
        break;
    }
}

/******************************************************************

FUNCTION: ProcessReceivedDataIcd

DESCRIPTION:  This method is called when a valid pulse is detected.
              The pulse is process according to L88 or ICD, which
              ever is defined.

ARGS:
  UINT16 CurrPulse: The next pulse that has come in.

RETURNS:
  <none>

******************************************************************/
#pragma CODE_SECTION(ProcessReceivedDataIcd, ".tam_rx_text")
void ProcessReceivedDataIcd(UINT16 CurrPulse)
{
    // Calculate the offset
    UINT16 PulseOffsetUs;

    PulseOffsetUs = ((CurrPulse - StartPulse)*RX_MCBSP_BITS_PER_SAMPLE); // /(RX_FREQUENCY/1000000);

    switch( State )
    {
    case NO_PULSE:
        // save the time of the start of frame pulse
        StartPulse = CurrPulse;
        State      = START_PULSE;
        break;

    case START_PULSE:
    {
        if( PulseOffsetUs >= (UINT16)(SYNC*(Tu) - .5*(Tu))*(RX_FREQUENCY/1000000) &&
            PulseOffsetUs <= (UINT16)(SYNC*(Tu) + .5*(Tu))*(RX_FREQUENCY/1000000) )
        {
            // We got a sync pulse, now look for the Frame ID pulse
            State = SYNC_PULSE;
        }
        else
        {
            // not a sync pulse, so mark this as the frame pulse
            StartPulse = CurrPulse;
        }
        break;
    }
    case SYNC_PULSE:
        if( PulseOffsetUs >= (UINT16)(ID_9*(Tu) - .5*(Tu))*(RX_FREQUENCY/1000000) &&
            PulseOffsetUs <= (UINT16)(ID_9*(Tu) + .5*(Tu))*(RX_FREQUENCY/1000000) )
        {
            State    = LOWER_NIBBLE;
            DataType = tac_memoryFrame;
        }
        else if( PulseOffsetUs >= (UINT16)(ID_10*(Tu) - .5*(Tu))*(RX_FREQUENCY/1000000) &&
                 PulseOffsetUs <= (UINT16)(ID_10*(Tu) + .5*(Tu))*(RX_FREQUENCY/1000000) )
        {
            // send the handshake to the application
            StoreDataByte( 0, tac_handshakeRequestFrame );
            State = NO_PULSE;
        }
        else if( PulseOffsetUs >= (UINT16)(ID_11*(Tu) - .5*(Tu))*(RX_FREQUENCY/1000000) &&
                 PulseOffsetUs <= (UINT16)(ID_11*(Tu) + .5*(Tu))*(RX_FREQUENCY/1000000) )
        {
            State    = LOWER_NIBBLE;
            DataType = tac_markerFrame;
        }
        else if( PulseOffsetUs >= (UINT16)(ID_12*(Tu) - .5*(Tu))*(RX_FREQUENCY/1000000) &&
                 PulseOffsetUs <= (UINT16)(ID_12*(Tu) + .5*(Tu))*(RX_FREQUENCY/1000000) )
        {
            State    = LOWER_NIBBLE;
            DataType = tac_markerSupplementFrame;
        }
        else if( PulseOffsetUs >= (UINT16)(ID_14*(Tu) - .5*(Tu))*(RX_FREQUENCY/1000000) &&
                 PulseOffsetUs <= (UINT16)(ID_14*(Tu) + .5*(Tu))*(RX_FREQUENCY/1000000) )
        {
            State = NO_PULSE;
            StoreDataByte( 0, tac_idleFrame );
        }
        else if( PulseOffsetUs >= (UINT16)(ID_16*(Tu) - .5*(Tu))*(RX_FREQUENCY/1000000) &&
                 PulseOffsetUs <= (UINT16)(ID_16*(Tu) + .5*(Tu))*(RX_FREQUENCY/1000000) )
        {
            State    = LOWER_NIBBLE;
            DataType = tac_primaryEgmFrame;
        }
        else if( PulseOffsetUs >= (UINT16)(ID_17*(Tu) - .5*(Tu))*(RX_FREQUENCY/1000000) &&
                 PulseOffsetUs <= (UINT16)(ID_17*(Tu) + .5*(Tu))*(RX_FREQUENCY/1000000) )
        {
            State    = LOWER_NIBBLE;
            DataType = tac_secondaryEgmFrame;
        }
        else if( PulseOffsetUs >= (UINT16)(ID_19*(Tu) - .5*(Tu))*(RX_FREQUENCY/1000000) &&
                 PulseOffsetUs <= (UINT16)(ID_19*(Tu) + .5*(Tu))*(RX_FREQUENCY/1000000) )
        {
            State    = LOWER_NIBBLE;
            DataType = tac_handshakeConfirmFrame;
        }
        else
        {
            StartPulse = CurrPulse;
            State      = START_PULSE;
            StoreDataByte( 0, tac_invalidIdentifierFrame );
        }
        break;

    case LOWER_NIBBLE:
        if( PulseOffsetUs >= (UINT16)((LOWER_NIBBLE_0*Tu - .5*Tu)*(RX_FREQUENCY/1000000)) &&
            PulseOffsetUs <= (UINT16)((LOWER_NIBBLE_F*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
        {
            if( PulseOffsetUs <= (UINT16)((LOWER_NIBBLE_0*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                LowerNibble = LOWER_NIBBLE_0 - LOWER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((LOWER_NIBBLE_1*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                LowerNibble = LOWER_NIBBLE_1 - LOWER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((LOWER_NIBBLE_2*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                LowerNibble = LOWER_NIBBLE_2 - LOWER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((LOWER_NIBBLE_3*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                LowerNibble = LOWER_NIBBLE_3 - LOWER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((LOWER_NIBBLE_4*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                LowerNibble = LOWER_NIBBLE_4 - LOWER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((LOWER_NIBBLE_5*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                LowerNibble = LOWER_NIBBLE_5 - LOWER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((LOWER_NIBBLE_6*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                LowerNibble = LOWER_NIBBLE_6 - LOWER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((LOWER_NIBBLE_7*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                LowerNibble = LOWER_NIBBLE_7 - LOWER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((LOWER_NIBBLE_8*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                LowerNibble = LOWER_NIBBLE_8 - LOWER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((LOWER_NIBBLE_9*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                LowerNibble = LOWER_NIBBLE_9 - LOWER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((LOWER_NIBBLE_A*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                LowerNibble = LOWER_NIBBLE_A - LOWER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((LOWER_NIBBLE_B*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                LowerNibble = LOWER_NIBBLE_B - LOWER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((LOWER_NIBBLE_C*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                LowerNibble = LOWER_NIBBLE_C - LOWER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((LOWER_NIBBLE_D*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                LowerNibble = LOWER_NIBBLE_D - LOWER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((LOWER_NIBBLE_E*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                LowerNibble = LOWER_NIBBLE_E - LOWER_NIBBLE_0;
            }
            else
            {
                LowerNibble = LOWER_NIBBLE_F - LOWER_NIBBLE_0;
            }

            State = UPPER_NIBBLE;
        }
        else
        {
            StartPulse = CurrPulse;
            State      = START_PULSE;
            StoreDataByte( 0, tac_invalidIdentifierFrame );
        }
        break;

    case UPPER_NIBBLE:
        if( PulseOffsetUs >= (UINT16)(UPPER_NIBBLE_0*Tu - .5*Tu)*(RX_FREQUENCY/1000000) &&
            PulseOffsetUs <= (UINT16)(UPPER_NIBBLE_F*Tu + .5*Tu)*(RX_FREQUENCY/1000000) )
        {
            if( PulseOffsetUs <= (UINT16)((UPPER_NIBBLE_0*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                UpperNibble = UPPER_NIBBLE_0 - UPPER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((UPPER_NIBBLE_1*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                UpperNibble = UPPER_NIBBLE_1 - UPPER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((UPPER_NIBBLE_2*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                UpperNibble = UPPER_NIBBLE_2 - UPPER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((UPPER_NIBBLE_3*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                UpperNibble = UPPER_NIBBLE_3 - UPPER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((UPPER_NIBBLE_4*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                UpperNibble = UPPER_NIBBLE_4 - UPPER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((UPPER_NIBBLE_5*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                UpperNibble = UPPER_NIBBLE_5 - UPPER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((UPPER_NIBBLE_6*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                UpperNibble = UPPER_NIBBLE_6 - UPPER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((UPPER_NIBBLE_7*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                UpperNibble = UPPER_NIBBLE_7 - UPPER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((UPPER_NIBBLE_8*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                UpperNibble = UPPER_NIBBLE_8 - UPPER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((UPPER_NIBBLE_9*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                UpperNibble = UPPER_NIBBLE_9 - UPPER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((UPPER_NIBBLE_A*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                UpperNibble = UPPER_NIBBLE_A - UPPER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((UPPER_NIBBLE_B*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                UpperNibble = UPPER_NIBBLE_B - UPPER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((UPPER_NIBBLE_C*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                UpperNibble = UPPER_NIBBLE_C - UPPER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((UPPER_NIBBLE_D*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                UpperNibble = UPPER_NIBBLE_D - UPPER_NIBBLE_0;
            }
            else if( PulseOffsetUs <= (UINT16)((UPPER_NIBBLE_E*Tu + .5*Tu)*(RX_FREQUENCY/1000000)) )
            {
                UpperNibble = UPPER_NIBBLE_E - UPPER_NIBBLE_0;
            }
            else
            {
                UpperNibble = UPPER_NIBBLE_F - UPPER_NIBBLE_0;
            }

            StoreDataByte( (UpperNibble<<4)|LowerNibble, DataType );
            State = NO_PULSE;
        }
        else
        {
            StartPulse = CurrPulse;
            State      = START_PULSE;
            StoreDataByte( 0, tac_invalidIdentifierFrame );
        }
        break;

    default:
        break;
    }
}

/******************************************************************

FUNCTION: InitializeMcbsp

DESCRIPTION:  This function initialized the McBSP to receive data
              from the shift register.

ARGS:
  <none>

RETURNS:
    <none>

******************************************************************/
static void InitializeMcbsp()
{
    static MCBSP_Config mcbspCfgRx = {
        0x0000,    /*  Serial Port Control Register 1   */
        0x0000,    /*  Serial Port Control Register 2   */
        MCBSP_RCR1_RMK(
            MCBSP_RCR1_RFRLEN1_OF(0),
            MCBSP_RCR1_RWDLEN1_8BIT
            ),
        MCBSP_RCR2_RMK(
            MCBSP_RCR2_RPHASE_SINGLE,
            MCBSP_RCR2_RFRLEN2_OF(0),
            MCBSP_RCR2_RWDLEN2_8BIT,
            MCBSP_RCR2_RCOMPAND_MSB,
            MCBSP_RCR2_RFIG_NO,
            MCBSP_RCR2_RDATDLY_0BIT
            ),
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
            MCBSP_SRGR1_CLKGDV_OF(((CPU_FREQ/SLOW_PERIPH_CLK_DIV)/RX_FREQUENCY) - 1)
            ),
        MCBSP_SRGR2_RMK(
            MCBSP_SRGR2_GSYNC_FREE,
            MCBSP_SRGR2_CLKSP_RISING,
            MCBSP_SRGR2_CLKSM_INTERNAL,
            MCBSP_SRGR2_FSGM_FSG,
            MCBSP_SRGR2_FPER_OF(8)
            ),
        0x0000,    /*  Multichannel Control Register 1   */
        0x0000,    /*  Multichannel Control Register 2   */
        0x0F05,  /*  Pin Control Register */
        0x0000,    /*  Receive Channel Enable Register Partition A   */
        0x0000,    /*  Receive Channel Enable Register Partition B   */
        0x0000,    /*  Receive Channel Enable Register Partition C   */
        0x0000,    /*  Receive Channel Enable Register Partition D   */
        0x0000,    /*  Receive Channel Enable Register Partition E   */
        0x0000,    /*  Receive Channel Enable Register Partition F   */
        0x0000,    /*  Receive Channel Enable Register Partition G   */
        0x0000,    /*  Receive Channel Enable Register Partition H   */
        0x0000,    /*  Transmit Channel Enable Register Partition A   */
        0x0000,    /*  Transmit Channel Enable Register Partition B   */
        0x0000,    /*  Transmit Channel Enable Register Partition C   */
        0x0000,    /*  Transmit Channel Enable Register Partition D   */
        0x0000,    /*  Transmit Channel Enable Register Partition E   */
        0x0000,    /*  Transmit Channel Enable Register Partition F   */
        0x0000,    /*  Transmit Channel Enable Register Partition G   */
        0x0000     /*  Transmit Channel Enable Register Partition H   */
    };
    // Configure the McBSP for receive operation.
    MCBSP_config(hMcbsp_TelemA, &mcbspCfgRx);
}

/******************************************************************

FUNCTION: InitializeDma

DESCRIPTION:  This function initialized the DMA to receive data
              from the shift register.

ARGS:
  <none>

RETURNS:
    <none>

******************************************************************/
static void InitializeDma()
{
    Uint32            addr;
    static DMA_Config gDmaConfigRx = {
        DMA_DMACSDP_RMK(
            DMA_DMACSDP_DSTBEN_NOBURST,
            DMA_DMACSDP_DSTPACK_OFF,
            DMA_DMACSDP_DST_DARAMPORT1,
            DMA_DMACSDP_SRCBEN_NOBURST,
            DMA_DMACSDP_SRCPACK_OFF,
            DMA_DMACSDP_SRC_PERIPH,
            DMA_DMACSDP_DATATYPE_16BIT
            ), /* Source/Destination Register - DMACSDP  */
        DMA_DMACCR_RMK(
            DMA_DMACCR_DSTAMODE_POSTINC,
            DMA_DMACCR_SRCAMODE_CONST,
            DMA_DMACCR_ENDPROG_OFF,
            DMA_DMACCR_REPEAT_ON,
            DMA_DMACCR_AUTOINIT_ON,
            DMA_DMACCR_EN_STOP,
            DMA_DMACCR_PRIO_HI,
            DMA_DMACCR_FS_DISABLE,
            DMA_DMACCR_SYNC_REVT0
            ), /* Control Register - DMACCR   */
        DMA_DMACICR_RMK(
            DMA_DMACICR_BLOCKIE_ON,
            DMA_DMACICR_LASTIE_OFF,
            DMA_DMACICR_FRAMEIE_OFF,
            DMA_DMACICR_FIRSTHALFIE_ON,
            DMA_DMACICR_DROPIE_OFF,
            DMA_DMACICR_TIMEOUTIE_OFF
            ), /* Interrupt Control Register - DMACICR  */
        0,      /* Lower Source Address - DMACSSAL */
        0,      /* Upper Source Address - DMACSSAU */
        0,      /* Lower Destination Address - DMACDSAL */
        0,      /* Upper Destination Address - DMACDSAU */
        RX_DMA_BUFFER_SIZE, /* Element Number - DMACEN   */
        1,      /* Frame Number - DMACFN   */
        0,      /* Frame Index - DMACFI   */
        0     /* Element Index - DMACEI   */
    };

    // DMA source address for all transfers.
    addr                  = ((Uint32)&_MCBSP_DRR10) << 1;
    gDmaConfigRx.dmacssal = (DMA_AdrPtr)(addr & 0xffff);
    gDmaConfigRx.dmacssau = (Uint16)((addr >> 16) & 0xffff);

    // DMA destination address for the 1st transfer.
    addr                  = ((Uint32)&RxDmaBuffer[0]) << 1;
    gDmaConfigRx.dmacdsal = (DMA_AdrPtr)(addr & 0xffff);
    gDmaConfigRx.dmacdsau = (Uint16)((addr >> 16) & 0xffff);

    // Write values from DMA config structure to DMA channel control registers
    DMA_config(hDma_Rx, &gDmaConfigRx);

    // Clear out any pending interrupts.
    DMA_RGETH(hDma_Rx, DMACSR);

    // Start receive DMA
    DMA_start(hDma_Rx);
}

/******************************************************************

FUNCTION: InitializeRxDmaIrq

DESCRIPTION:  This function initialized the Interrupts for the DMA
              to cause an interrupt on buffer 1/2 and full.

ARGS:
  <none>

RETURNS:
    <none>

******************************************************************/

static void InitializeRxDmaIrq()
{
    Uint16 eventID;

    // Get Event ID associated with the DMA channel interrupt
    eventID = DMA_getEventId(hDma_Rx);

    // Clear any pending channel interrupt (IFR)
    IRQ_clear(eventID);

    // Enable DMA interrupt (IER)
    IRQ_enable(eventID);

    // Enable all interrupts (INTM)
    IRQ_globalEnable();
}

/******************************************************************

FUNCTION: TurnOnReceiver

DESCRIPTION:  This function turns on the DMA and McBSP for the
              receiver

ARGS:
  <none>

RETURNS:
  <none>

******************************************************************/
void TurnOnReceiver(void)
{
    UINT16 j;

    // These variables are declared in the linker file
    extern UINT16 run_start_of_tacode;
    extern UINT16 load_start_of_tacode;
    extern UINT16 size_of_tacode;

    // create pointers to the source and destination
    UINT32 RunStart = (UINT32)(((UINT32)(&run_start_of_tacode))/2);
    UINT32 LoadStart= (UINT32)(((UINT32)(&load_start_of_tacode))/2);
    UINT16 Size     = (UINT16)(((UINT32)(&size_of_tacode+1))/2);

    bsm_CopyCode(LoadStart, RunStart, Size);

    // Reset the statemachine
    State                      = NO_PULSE;

    // invalidate any data in the holding bin
    RxDataValid                = FALSE;
    RxData                     = 0;
    RxDataType                 = tac_invalidIdentifierFrame;

    // initialize the AGC countdown
    AgcSampleCounter           = SamplesPerFrame;

    NeedToChangeAgcPulseSelect = FALSE;

    DataType                   = tac_invalidIdentifierFrame;
    StartPulse                 = 0;
    LowerNibble                = 0;
    UpperNibble                = 0;
    HandshakeHoldOff           = 0;
    HighBitCount               = 0;
    LowBitCount                = 0;
    Time                       = 0;
    NewAgcPulseSelect          = HIGH_GAIN;
    AgcPulseSelect             = HIGH_GAIN;

    if(TelemetryType == tac_L88TelemProtocol)
    {
        FrameTime = FrameTimeL88;
    }
    else
    {
        FrameTime = FrameTimeICD;
    }

    // initialize the receive characteristics
    for( j = LOW_GAIN; j <= HIGH_GAIN; j++ )
    {
        DebounceCount[j]   = DEBOUNCE;
        AgcPulseWidth[j]   = 0;
        DebouncedSignal[j] = 0;
    }

    InitializeMcbsp();
    InitializeDma();
    InitializeRxDmaIrq();

    // Start McBSP0
    MCBSP_start(
        hMcbsp_TelemA,
        MCBSP_RCV_START | MCBSP_SRGR_START | MCBSP_SRGR_FRAMESYNC,
        100);
    // the 100 is the sample delay which is (2*SampleRatePeriod)/(4*InstructionCycle), or
    //                                      (2*3.57e-7)/(4*3.33e-9) = 53.
    //  I made this bigger just to be on the safe side.
}


/******************************************************************

FUNCTION: TurnOffReceiver

DESCRIPTION:  This function turns off the DMA and McBSP for the
              receiver

ARGS:
  <none>

RETURNS:
  <none>

******************************************************************/
void TurnOffReceiver(void)
{
    GLB_LTMR_OBJ rcvShutdownTimeout;

    //See TMS320VC5502 Silicon Errata (SPRZ020K), Oct. 2004
    //Advisory DMA_1 and Advisory DMA_2

    UINT16 eventID = DMA_getEventId(hDma_Rx);

    // Wait for the DMA to finish transfering one last complete block
    // before disabling it.

    // The RxStopped flag will be set by the ISR once the last
    // block transfer is done
    RxStopped = FALSE;

    // (Step 1 of Advisory DMA_1 Workaround)
    DMA_FSETH (hDma_Rx, DMACCR, REPEAT, 0);

    GLB_GET_HTMR(rcvShutdownTimeout);

    // (Step 2 of Advisory DMA_1 Workaround)
    while(!RxStopped)
    {
        if (GLB_HAS_HTMR_EXPIRED(rcvShutdownTimeout, RX_SHUTDOWN_TIMEOUT))
        {
            break;
        }
    }

    // Disable further DMA interrupts, and clear any pending ones
    IRQ_disable(eventID);
    IRQ_clear(eventID);

    // (Step 3 of Advisory DMA_1 Workaround)
    // Disable the transmit DMA
    DMA_reset(hDma_Rx);

    // Reset and close McBSP0.  This stops the flow of receive
    // syncronization events.
    MCBSP_reset(hMcbsp_TelemA);
    IRQ_clear(MCBSP_getRcvEventId(hMcbsp_TelemA));

    // (Only Step of Advisory DMA_2 Workaround)
    // Write 0 to SYNC field in DMACCR before programming the channel for
    // more data transfers.
    DMA_FSETH (hDma_Rx, DMACCR, SYNC, 0);
}
