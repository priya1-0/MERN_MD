/************************************************************************
*
* MODULE: tbm_trx.c
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
* tbm_startPacketTrx
* tbm_trxInit
*
* --Private--
* initTrxMcBSP
* trxMcBSPHwi
* processTrxBuffer
* disableTBTrx
*
* DESCRIPTION: This file implements the Telemetry B Downlink Physical Layer.
*
*************************************************************************/

// Project specific includes
#include "global.h"

#define DEFINED_HERE
#include "tbm_trx.h"
#undef DEFINED_HERE

#include "tbm_rcv.h"
#include "tbm_main.h"


// CSL includes
#include <csl.h>
#include <csl_dma.h>
#include <csl_irq.h>
#include <csl_pwr.h>
#include <csl_gpio.h>
#include <csl_mcbsp.h>
#include <csl_hpi.h>
#include <csl_dat.h>

// BIOS includes
#include <std.h>
#include <hwi.h>
#include <swi.h>
#include <log.h>
#include <sts.h>
#include <clk.h>

//************************************************************************
//  Local Functions
//************************************************************************
static void initTrxMcBSP(void);
static interrupt void trxMcBSPHwi(void);
static void processTrxBuffer(void);

//************************************************************************
//  Local Macros
//************************************************************************
// HD2 == 150kHz/_200kHz output
#define SET_TRX_BIT(bit) HPI_FSET(HGPIODAT,HD2,(bit) ? 0 : 1)
// HD3 == Rcv/_Trx output
#define SET_TRX() HPI_FSET(HGPIODAT,HD3,0)
#define SET_RCV() HPI_FSET(HGPIODAT,HD3,1)

#define MCBSP_TRX_START_DELAY (125)     // (2 x SRG_CLK_PER) / (4 x INST_PER)
// (2 x 833e-9) / (4 x 3.33e-9)

//************************************************************************
//  Local Variables
//************************************************************************
UINT16       nextBitVal;
UINT16       bitVal;
UINT16       wordCount;
MCBSP_Handle hMcbsp_TBTrx;
INT16        syncBitCount;
UINT16       bitMask;
UINT16       ones;
UINT16       isrCnt;
UINT16       trxBitCount;
UINT16       stuffedBits;
BOOL         bitStuffHoldOff;
GLB_HTMR_OBJ trxTimeout;        // High resolution timer object.

// McBSP word patterns to generate 150kHz, 200kHz waveforms.
// 150kHz represent a logic '0', 200kHz represent a logic '1'
const UINT32 bit_TelB[2][3] = {
    { 0xf0f0f0f0, 0xf0f0f0f0, 0xf0f0f0f0 },              //150kHz
    { 0xe38e38e3, 0x8e38e38e, 0x38e38e38 }               //200kHz
};

/********************************************************************
FUNCTION: tbm_trxInit

DESCRIPTION: This function performs Telemetry B transmission (downlink)
        initialization tasks that are required only once per session (not
        per frame). This function can be called when the Telemetry B module
        is activated.
ARGS:
    None
RETURNS:
    None.
********************************************************************/
void tbm_trxInit(void)
{
    // HGPIO HD3 == Rcv/_Trx output
    // HGPIO HD2 == 150kHz/_200kHz output

    // EN7 GPIO enable bit for pins HD[7:0]
    HPI_FSET(HGPIOEN, EN7, 1);

    // HD15-HD0 Direction bits for pins HD[15:0].
    HPI_FSET(HGPIODIR, HD2, GPIO_OUTPUT);
    HPI_FSET(HGPIODIR, HD3, GPIO_OUTPUT);
}

/********************************************************************
FUNCTION: tbm_startPacketTrx

DESCRIPTION:  This function performs all tasks necessary to initiate
        the transmission of a Telemetry B frame.
ARGS:
    None
RETURNS:
    None.
********************************************************************/
void tbm_startPacketTrx(void)
{
    // Set the antenna for transmission.
    SET_TRX();
    SET_TRX();     // Multiple usage of this macro was necessary to get the
    SET_TRX();     // setting to "stick". Remove only if functionality is verified!

    nextBitVal      = 1;
    bitVal          = nextBitVal;
    wordCount       = 3;
    tbm_xmtState    = TX_INIT;
    syncBitCount    = 0;
    bitMask         = 0x1;
    ones            = 0;
    isrCnt          = 0;
    trxBitCount     = 0;
    stuffedBits     = 0;
    bitStuffHoldOff = FALSE;

    SET_TRX_BIT(bitVal); // Rcv/_Trx output
    SET_TRX_BIT(bitVal); // Multiple usage of this macro was necessary to get the
    SET_TRX_BIT(bitVal); // setting to "stick". Remove only if functionality is verified!

    // Initialize the McBSP0 to transmit TB FSK data.
    initTrxMcBSP();

    // Write the high 16 bits before the low 16 bits (required).
    // The TRX data is written before enabling the transmitter. If not
    // done in this order, the McBSP transmitter can lock up.
    // McBSP_write32 cannot be used here either. It hangs up indefinitely
    // is used before the transmitter is enabled.
    _DXR20 = (bit_TelB[bitVal][0] > 16) & 0xffff;
    _DXR10 = bit_TelB[bitVal][0] & 0xffff;

    // Start McBSP0 as the FSK output data channel
    MCBSP_start(
        hMcbsp_TBTrx,
        MCBSP_XMIT_START | MCBSP_SRGR_START | MCBSP_SRGR_FRAMESYNC,
        MCBSP_TRX_START_DELAY);

#ifdef TURNAROUND_TIME_TEST
        #warn "Telemetry B Turnaround Time Testing Enabled"
    // Set the output
    _GPIO_IODATA |= GPIO_PIN4;
#endif
}

/********************************************************************
FUNCTION: initTrxMcBSP

DESCRIPTION:  This function initializes the McBSP at the start of the
        transmission of a frame.
ARGS:
    None
RETURNS:
    None.
********************************************************************/
static void initTrxMcBSP()
{
    Uint16                    eventID;
    static const MCBSP_Config mcbspCfgTBTrx = {
        0x0000,    /*  Serial Port Control Register 1   */
        0x0100,    /*  Serial Port Control Register 2   */
        0x0000,    /*  Receive Control Register 1   */
        0x0000,    /*  Receive Control Register 2   */
        0x00a0,    /*  Transmit Control Register 1, 32 data bits */
        0x0000,    /*  Transmit Control Register 2   */
        0x107C,    /*  Sample Rate Generator Register 1   */
        /*  0x7C == 124 => CPU / ((124 + 1) * 2) == 1.2MHz */
        0x301f,    /*  Sample Rate Generator Register 2  */
        /*  Frame sync with frame sync generator */
        0x0000,    /*  Multichannel Control Register 1   */
        0x0000,    /*  Multichannel Control Register 2   */
        0x1a02,    /*  Pin Control Register   */
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
    // Open the McBSP0 for Telemetry B Transmit functionality.
    hMcbsp_TBTrx = MCBSP_open(MCBSP_PORT0, MCBSP_OPEN_RESET);

    // Configure the McBSP for transmit operation.
    MCBSP_config(hMcbsp_TBTrx, (MCBSP_Config *)&mcbspCfgTBTrx);

    // Get Event ID associated with McBSP Transmit
    eventID = MCBSP_getXmtEventId(hMcbsp_TBTrx);

    // Clear any pending channel interrupt (IFR)
    IRQ_clear(eventID);

    // Place the HWI hook at the proper spot in the interrupt vector table
    // and enable the dispatcher for this interrupt
    IRQ_plug(eventID, &trxMcBSPHwi);

    // Enable McBSP interrupt (IER)
    //tbm_enableTrxInt();
    IRQ_enable(MCBSP_getXmtEventId(hMcbsp_TBTrx));
}

/********************************************************************
FUNCTION: tbm_enableTrxInt

DESCRIPTION: This function enables the transmitter McBSP interrupt,
        if a transmission is, or should be, in progress.
ARGS:
    None
RETURNS:
    None.
********************************************************************/
void tbm_enableTrxInt(void)
{

// This functionality is intentionally commented out since it was not
// needed. It was left in here (commented out), so that it's implementation
// would be easily known, if it later proved to be needed.

//	if (tbv_txInProgress) {
//		IRQ_enable(MCBSP_getXmtEventId(hMcbsp_TBTrx));
//	}
}

/********************************************************************
FUNCTION: tbm_disableRcvInt

DESCRIPTION: This function disables the transmitter McBSP interrupt,
        if it is currently enabled.
ARGS:
    None
RETURNS:
    None.
********************************************************************/
void tbm_disableTrxInt(void)
{

// This functionality is intentionally commented out since it was not
// needed. It was left in here (commented out), so that it's implementation
// would be easily known, if it later proved to be needed.

//	if (tbv_txInProgress) {
//		IRQ_disable(MCBSP_getXmtEventId(hMcbsp_TBTrx));
//	}
}

/********************************************************************
FUNCTION: disableTBTrx

DESCRIPTION:  This function disables the transmitter at the end of
        the transmission of a frame.
ARGS:
    None
RETURNS:
    None.
********************************************************************/
void tbm_disableTrx(void) {

    // Get Event ID associated with the McBSP interrupt
    // and disable the interrupt (IER)
    //tbm_disableTrxInt();
    IRQ_disable(MCBSP_getXmtEventId(hMcbsp_TBTrx));
    IRQ_clear(MCBSP_getXmtEventId(hMcbsp_TBTrx));

    GLB_GET_HTMR(trxTimeout);

    // Wait for the last McBSP word to be transmitted.
    while (MCBSP_xempty(hMcbsp_TBTrx) == 1) {
        if (GLB_HAS_HTMR_EXPIRED(trxTimeout, 40000)) {          // 40us timeout.
            asm ("	nop");
            asm ("	nop");
            asm ("	nop");                  // Instructions to set a breakpoint on.
            break;
        }
    };

#ifdef TURNAROUND_TIME_TEST
        #warn "Telemetry B Turnaround Time Testing Enabled"
    // Clear the output
    _GPIO_IODATA &= ~(GPIO_PIN4);
#endif

    MCBSP_FSET(SPCR20, XRST, 0);

    // Reset and close McBSP0.
    MCBSP_FSET(SPCR20, FRST, 0);
    MCBSP_FSET(SPCR20, GRST, 0);
    MCBSP_FSET(SPCR10, RRST, 0);

    MCBSP_close(hMcbsp_TBTrx);

    tbm_xmtState     = TX_IDLE;
    tbv_txInProgress = FALSE;
}

/********************************************************************
FUNCTION: trxMcBSPHwi

DESCRIPTION:  This function is the transmit ISR. It is called 3 times
        per bit period. It handles setting up the McBSP to generate the
        correct FSK waveform given the current bit to transmit. It calls
        the processTrxBuffer function once per bit period to determine
        the next bit of the frame to transmit. When transmission is complete,
        it handles the disabled of the transmitter, and enabling of the
        receiver, if appropriate.

ARGS:
    None
RETURNS:
    None.
********************************************************************/
static interrupt void trxMcBSPHwi (void)
{
    if (tbv_txInProgress == FALSE) return;

    if (tbm_xmtState == TX_DONE && wordCount == 1)
    {
        tbm_disableTrx();

        if (tbv_p_currentTxBuffer == &tbv_wack) {
#ifdef DEBUG_VARS_ON
            debugVars.startedTransmitting     = 4;
            ++debugVars.wacksCompleted;
            debugVars.startedTransmitting     = FALSE;
#endif
#ifdef DEBUG_HEADERS_ON
            debugHeaders[debugHeadersIndex++] = TRX_WACK;
            debugHeadersIndex                &= DEBUG_HEADERS_MASK;
#endif
            asm ("	nop");                 // make sures there's always something in this branch.
        }
        else {
            tbm_processTransmitComplete(tbv_p_headTxBuffer);
        }

        tbm_startPacketRcv();
        return;
    }

    switch(wordCount)
    {
    case 1:
        MCBSP_write32(hMcbsp_TBTrx, bit_TelB[bitVal][wordCount++]);
        SET_TRX_BIT(bitVal);                 // 150kHz/_200kHz output
        SET_TRX_BIT(bitVal);                 // 150kHz/_200kHz output
        SET_TRX_BIT(bitVal);                 // 150kHz/_200kHz output
        break;

    case 2:
        MCBSP_write32(hMcbsp_TBTrx, bit_TelB[bitVal][wordCount++]);

        // Determine the next bit of the frame to send.
        processTrxBuffer();
        break;

    case 3:
        bitVal    = nextBitVal;
        wordCount = 0;
        MCBSP_write32(hMcbsp_TBTrx, bit_TelB[bitVal][wordCount++]);
        break;
    }
}

/********************************************************************
FUNCTION: processTrxBuffer

DESCRIPTION:  This function is called from the transmit ISR once per
        bit period. It determines the next bit to transmit in the current
        frame. It handles the insertion of sync bits, bit stuffing, and
        NRZI encoding.

ARGS:
    None
RETURNS:
    None.
********************************************************************/
static void processTrxBuffer(void)
{
    switch (tbm_xmtState)
    {
    case TX_INIT:
        syncBitCount =0;
        tbm_xmtState = TX_SYNC;

    // Fall through to TX_SYNC otherwise.

    case TX_SYNC:
        //still need to keep transmitting sync character,
        //which, when NRZI encoded, is a series of alternating
        //ones and zeros
        nextBitVal ^= 1;

        // Copy next bit's data pattern.
        if(++syncBitCount >= tbv_syncBits)
        {
            //The correct number of sync character have been transmitted
            tbm_xmtState = TX_DATA;
        }
        break;

    case TX_DATA:
        // check to make sure there are still bits to send
        if (tbv_txByteCount < tbv_txSize &&
            tbv_txWackBitCount < tbv_txWackBitSize)
        {
            // Debug var to count total bits sent.
            trxBitCount++;

            // Only use WACK bit count if transmitting a WACK.
            if (tbv_txWackBitSize != TBC_no_wack) {
                tbv_txWackBitCount++;
            }

            // check to see if a bit-stuff zero needs to be sent
            if (ones >= 5)
            {
                // The flag bytes are assumed to always be the first and
                // last bytes in the packet buffer. Don't stuff them!
                if (tbv_txByteCount != 0 &&                                      // Start Flag
                    tbv_txByteCount != tbv_txSize - 1)               // End Flag
                {
                    // Debug var to count stuffed bits sent.
                    ++stuffedBits;

                    // Send a bit-stuff zero, so frequency change
                    nextBitVal ^= 1;
                    ones        = 0;

                    // If we're at the end of the byte, increment now.
                    // (it was held off after the 8th bit was sent to
                    // wait for the stuffed bit to be sent).
                    if (bitStuffHoldOff)
                    {
                        bitStuffHoldOff = FALSE;
                        bitMask         = 0x01;
                        tbv_txByteCount++;
                    }

                    // Nothing else to do.
                    return;
                }
            }

            // Send out the data in NRZI-encoded form
            if (tbv_p_currentTxBuffer[tbv_txByteCount] & bitMask)
            {
                // This bit was a '1'; nextBitVal doesn't change.
                ones++;
            }
            else
            {
                // this bit was a '0', so frequency change
                nextBitVal ^= 1;
                ones        = 0;
            }

            //go to the next bit in the stream
            if (bitMask == 0x80)
            {
                // Hold off moving to the next byte if a stuffed
                // bit needs to be sent.
                if (ones < 5) {
                    bitMask = 0x01;
                    tbv_txByteCount++;
                }
                else {
                    bitStuffHoldOff = TRUE;
                }
            }
            else
            {
                bitMask <<= 1;
            }
        }
        else
        {
            //the bits have all been transmitted
            tbm_xmtState = TX_DONE;
            debugVars.trxFrames++;
        }
        break;

    case TX_DONE:
    default:
        break;
    }
}