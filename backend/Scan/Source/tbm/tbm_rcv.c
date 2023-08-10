/************************************************************************
*
* MODULE: tbm_rcv.c
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
*
* --Private--
*
* DESCRIPTION: This file implements the Telemetry B Uplink Physical Layer.
*
*************************************************************************/

// Project specific includes
#include "global.h"

#define DEFINED_HERE
#include "tbm_rcv.h"
#undef DEFINED_HERE

#include "tbm_main.h"
#include "tbm_trx.h"
#include "tbm_events.h"

#include <string.h>

// DSP Lib includes
#include <math.h>
#include <tms320.h>
#include <dsplib.h>

// CSL includes
#include <csl.h>
#include <csl_dma.h>
#include <csl_irq.h>
#include <csl_pwr.h>
#include <csl_gpio.h>
#include <csl_mcbsp.h>
#include <csl_hpi.h>

// Filter size def is needed in the included filter coefficient files
#define FILTER_SIZE (129)

//************************************************************
// Filter kernels can be found at:
// J:\medtronic\6698\hw\dsp_system_analysis\FIR_filter_design
//************************************************************
#include "high_dr_filter_128.h"
#include "low_dr_filter_128.h"

//**********************************************************************
//* local definitions
//**********************************************************************

//* Notes:
//* 256 Point Sample Block for low data rate
//* At 2.77MHz, a 256 sample block is collected in 91.42us.
//* 192 Point Sample Block for high data rate
//* At 2.77MHz, a 192 sample block is collected in 69.31us.
//
#define MAX_BLK_SIZE        (256)                       // Maximum size sample block.
#define MAX_SAMPLES_PER_BIT (128)                       // Maximum number of samples per bit period
#define MAX_LPF_SIZE        (64)                        // Maximum number of samples in low pass filter.
#define MAX_CORR_IDEAL_SIZE (128)                       // Maximum size correlation ideal pattern size.
#define MAX_CORR_IN_SIZE    (192)                       // Maximum size correlation input sample block.

#define BLK_SIZE_87500 (192)
#define BLK_SIZE_21875 MAX_BLK_SIZE

// 32 words x 8 bits == 256 samples
#define MAX_RCV_BUF_SIZE    32
#define MCBSP_RCV_WORD_SIZE 8

// HD3 == Rcv/_Trx output
#define SET_RCV() HPI_FSET(HGPIODAT,HD3,1)

// HD2 == 150kHz/_200kHz output
#define SET_TRX_LOW() HPI_FSET(HGPIODAT,HD2,0)

// HD2 == 150kHz/_200kHz
#define SET_TRX_BIT(bit) HPI_FSET(HGPIODAT,HD2,(bit) ? 0 : 1)


#define PREV_BIT_INIT (-100)

#define MCBSP_RCV_START_DELAY (54)      // (2 x SRG_CLK_PER) / (4 x INST_PER)
// (2 x 357e-9) / (4 x 3.33e-9)

#define ROM_SINE_TABLE_ADDR (0x7FF680)

// The following two structures (and arrays) are used exclusively
// for debugging purposes. Correct functionality of the
// Telemetry B module does NOT depend on them in any way.
typedef enum {
    RCV_PASS,
    RCV_ABORT,
    RCV_CRC_ERR,
    RCV_OPEN_FLAG_ERR,
    RCV_NO_SYNC,
    RCV_LOST_SYNC,
    RCV_OVERRUN,
    RCV_END_FLAG_ERR
} status_t;

typedef struct {
    DATA syncScore;
    UINT16 syncBits;
    UINT16 sampleBlkNo;
    UINT16 sampleBlkNoAtSync;
    UINT16 sampleBlkNoAtStart;
    status_t status;
    UINT16 rcvBytes;
    UINT16 stuffedBits;
} rcvDebug_t;

#define RCV_DEBUG_SIZE   100
#define ERROR_INDEX_SIZE 50
rcvDebug_t receiveDebug[RCV_DEBUG_SIZE + 1];
UINT16     errorIndex[ERROR_INDEX_SIZE + 1];

// Define INLINE to be nothing to have functions called instead
// of inlined to make debug easier. Define to 'inline' for
// production release.
#define INLINE inline

//**********************************************************************
//* local function prototypes
//**********************************************************************
static INLINE void lpf(DATA *, DATA *);
static INLINE void demodulate(DATA *, DATA *);
static INLINE void processDBPSKData(DATA *);
static INLINE void extractBitVals(void);
static INLINE DATA maintainClockPhase(DATA *, DATA, INT16);
static INLINE void findSync(void);
static INLINE void unpackData (DATA *, DATA *);
static INLINE void memcpy32(void *, void *, INT16);
static INLINE void sync_mgmt (DATA *);
static INLINE void processFrame(DATA *);
static INLINE void disableRcv(void);
static INLINE void startDisableRcv(void);
static INLINE void finishRcv (void);
static INLINE void initRcvMcBSP();
static INLINE void initRcvDMA();
static INLINE void initRcvDMAIrq();

static interrupt void rcvDMAHwi();

/***********************************************************************
* local data
***********************************************************************/

// Note - the data type "DATA" is a TI DSP lib defined data type.

// Ideal correlation pattern for 87.5k
#pragma DATA_ALIGN(cor_87500, 2)
DATA cor_87500[64];

// Ideal correlation pattern for 21.875k
#pragma DATA_ALIGN(cor_21875, 2)
DATA cor_21875[96];

// Delay buffer amount is size of the filter kernel + 2.
// Does NOT need to be contiguous with any other array.
#pragma DATA_ALIGN(dBuffer, 2)
DATA dBuffer[FILTER_SIZE+2];                    // Delay buffer used in FIR filter.

#pragma DATA_ALIGN(fill, 2)
DATA fill[MAX_BLK_SIZE * 2];                    // Array filled with zeros to allow faster
// 32 bit copies to clear arrays.
#pragma DATA_ALIGN(corrOut, 2)
DATA corrOut[MAX_BLK_SIZE * 2];                 // Output array for sync correlation

#pragma DATA_ALIGN(syncBlock, 2)
DATA syncBlock[MAX_CORR_IN_SIZE * 2];   // Sync correlation input data array.


#pragma DATA_ALIGN(bitOverlap, 2)               // Processed data to overlap from one
DATA bitOverlap[MAX_SAMPLES_PER_BIT+1]; // sample block to the next.

//Overlap amount is the number of samples in a bit period.
//demodOverlap and in must be contiguous in memory.
#pragma DATA_ALIGN(demodOverlap, 2)
#pragma DATA_ALIGN(in, 2)
DATA demodOverlap[MAX_SAMPLES_PER_BIT]; // Overlap of data for demodulation.
DATA in[MAX_BLK_SIZE+1];                                // One of two arrays to process data in.

//Overlap amount is size of the low pass filter.
//lpfOverlap and out must be contiguous in memory.
#pragma DATA_ALIGN(out, 2)
#pragma DATA_ALIGN(lpfOverlap, 2)
DATA lpfOverlap[MAX_LPF_SIZE];                  // Low pass filter overlap data.
DATA out[MAX_BLK_SIZE+1];                               // One of two arrays to process data in.

#pragma DATA_ALIGN(rcvData, 2)
DATA rcvData[2][MAX_RCV_BUF_SIZE+1];    // The two buffers that McBSP data is copied
// into through DMA transfer.

BOOL         syncFound;                 // Has sync been found or not. Yes is correlation min score is exceeded.
INT32        lpfsum;                    // Sum of all samples currently in the low pass filters.
DATA         clockPhase;                // Sample number represented the current 'zero phase' location.
INT16        bitNum;                    // Bit number of the current byte being processed.
INT16        prevBit;                   // The previous bit's value.
INT16        curBit;                    // The current bit's value.
INT16        lookingForSync;    // Are we currently looking for sync, or not.
INT16        foundStartFlag;    // Are we currently looking for the start flag, or not.
INT16        noTransCnt;                // 'no transition count'; used while maintained clock synchronization
INT16        syncBlkNo;                 // Block number in the sync sequence.
DATA         tData;                             // Current byte of data currently being processed.
INT16        nrzi;                              // Current NRZI value.
INT16        rcvOnes;                   // Number of consecutive logics '1's received.
DATA         *cor;                              // Pointer to high or low data rate ideal correlation pattern.
DATA         *filter;                   // Pointer to high or low data rate filter coefficients.
MCBSP_Handle hMcbsp_TBRcv;      // Handle for the McBSP channel.
DATA         buf;                               // Which of the two rcvData buffers is currently being processed.
INT16        sampleBlkNo;               // Sample block since beginning the monitoring for current frame
INT16        syncScoreMax;              // Used to statistically score actual sync correlation values
INT16        syncScoreMin;              // Used to statistically score actual sync correlation values
INT16        prevSyncScore;     // Sync correlation value from the previous correlation.
INT16        samplesPerBit;     // Number of samples per bit period
INT16        lpfSize;                   // Number of samples in low pass filter.
UINT16       corrIdealSize;     // Number of samples in the correlation ideal pattern.
UINT16       corrInSize;                // Number of input samples for the sync correlation
INT16        corrDivisor;               // Number of input samples to skip in sync correlation.
INT16        syncThreshold;     // Correlation score minimum threshold
INT16        blkSize;                   // Number of samples in the input data.
INT16        idealSyncShift;    // Number of bits to shift ideal sync data to reduce magnitude.
DATA         dataMag;                   // 16 bit magnitude of a high sample during data unpacking.
DATA         dataMagNeg;                // 16 bit magnitude of a low sample during data unpacking.
INT16        syncMagShift;              // Number of bits to shift sync data to reduce magnitude.
INT16        syncIndex;                 // Location to store sync sample in syncBlock.
INT16        clockTol;                  // Clock phase maintenance tolerance about the ideal location.
INT16        clockTolInc;               // Sample increment amount to use with tolerance value.
GLB_LTMR_OBJ rcvTimeout;        // Low resolution timer object.
BOOL         frameFound;                // Indicates a frame has been found (start and end flags)
BOOL         shuttingDown;              // TRUE when the receiver is to be shut down (not reenabled).
UINT32       oldRcvIntStatus;   // Temporary storage of the previous receive interrupt enable state.
UINT16       frameCount;                // Count of frames
DATA         syncScore;                 // The current sync score.
UINT16       errorCount;                // error count for a debug structure
UINT16       syncBits;                  // Count of sync bits found in the current frame.
DATA         corrIndex;                 // Index of location of correlation peak.
DATA         prevCorrIndex;             // Index of location of correlation peak in previous correlation.
INT16        phaseOffset;               // Sample offset to apply in transition from sync to maintain.
UINT16       syncSampleBlocks;  // Number of sample blocks collected until sync was found.
UINT16       rcvDestuffBits;    // Number of destuffed bits in the current frame.
UINT16       rcvBits;                   // Number of bits in the current frame.
INT16        maintainFraction;  // Shift to apply to phase maintain delta.

/********************************************************************
FUNCTION: tbm_initRcv

DESCRIPTION: This function performs Telemetry B reception (uplink)
        initialization tasks that are required only once per session (not
        per frame). This function can be called when the Telemetry B module
        is activated.
ARGS:
    None
RETURNS:
    None.
********************************************************************/
void tbm_initRcv(void)
{
    DATA  *src,*dst;
    INT16 x;

    tbm_rcvState = RCV_IDLE;

    memset(rcvData, 0, sizeof(rcvData));
    memset(fill, 0, sizeof(fill));
    memset(&debugVars, 0, sizeof(debugVars));

    memset(receiveDebug, 0, sizeof(receiveDebug));
    memset(errorIndex, 0, sizeof(errorIndex));

    errorCount                             = 0;
    receiveRow                             = 0;
    frameCount                             = 0;

    // Marker values to show array bounds are not exceeded.
    receiveDebug[RCV_DEBUG_SIZE].syncScore = 0x5aa5;
    errorIndex[ERROR_INDEX_SIZE]           = 0x2992;
#ifdef DEBUG_STATE
    state[STATE_ARRAY_SIZE]                = (tbt_stateType)0x9731;
#endif
#ifdef DEBUG_HEADERS_ON
    debugHeaders[DEBUG_HEADERS_SIZE]       = 0x1639;
#endif

    // Open DMA channels
    tbv_hDma = DMA_open(DMA_CHA_ANY,DMA_OPEN_RESET);

    // This is the ideal sync pattern for the 21.875k data rate to correlate against.
    // It comes from the on chip ROM Sine table.
    src = (DATA *)(ROM_SINE_TABLE_ADDR);
    dst = &cor_21875[32];
    for(x = 0; x < 64; ++x, src+=4) {
        *dst++ = (*src)>>2;
    }
    memcpy(&cor_21875[0], &cor_21875[64], 32);

    // This is the ideal sync pattern for the 87.5k data rate to correlate against.
    // It comes from the on chip ROM Sine table.
    src = (DATA *)(ROM_SINE_TABLE_ADDR);
    dst =&cor_87500[0];
    for(x = 0; x < 32; ++x, src += 8) {
        *dst++ = (*src)>>1;
    }
    memcpy(&cor_87500[32], &cor_87500[0], 32);

    syncScoreMin=32767;
    syncScoreMax=0;
}

/********************************************************************
FUNCTION: tbm_startPacketRcv

DESCRIPTION: This function performs Telemetry B reception (uplink)
        initialization tasks that are required once per frame.
ARGS:
    None
RETURNS:
    None.
********************************************************************/
void tbm_startPacketRcv(void)
{
    UINT32 addr;

    // Note - the variable settings in the following block, one set
    // for 87.5k uplink, and one set for 21.875k uplink were derived
    // from extensive testing in the lab. Anyone attempting to modify
    // this code in the future should be cautious of the implications
    // of the change(s). Extensive retesting must be conducted!

    // Uplink data rate is 87.5k baud.
    if (desiredUplinkRate == tbc_dr_87) {
#ifdef DEBUG_STATE
        ++stateIndex;
        stateIndex            &= STATE_MASK;
        state[stateIndex]      = tbt_listenEntered87;
#endif
        currentUplinkRate      = tbc_dr_87;
#ifdef DEBUG_VARS_ON
        debugVars.listenMode87 = TRUE;
        debugVars.listenMode21 = FALSE;
#endif
        blkSize                = 192;
        samplesPerBit          = 32;

        corrDivisor            = 2;
        corrIdealSize          = 64;
        corrInSize             = 192;
        syncThreshold          =  15500;
        cor                    = (DATA *)cor_87500;
        clockTol               = 12;
        clockTolInc            = 2;
        syncSampleBlocks       = 2;

        dataMag                = 2048;
        dataMagNeg             = ~dataMag;
        syncMagShift           = 1;
        filter                 = highDRFilter;
        phaseOffset            = 0;
        maintainFraction       = 2;     // shift by 2 == div by 4
    }
    // Uplink data rate is 21.875k baud.
    else if (desiredUplinkRate == tbc_dr_21) {
#ifdef DEBUG_STATE
        ++stateIndex;
        stateIndex            &= STATE_MASK;
        state[stateIndex]      = tbt_listenEntered21;
#endif
        currentUplinkRate      = tbc_dr_21;
#ifdef DEBUG_VARS_ON
        debugVars.listenMode87 = FALSE;
        debugVars.listenMode21 = TRUE;
#endif
        blkSize                = 256;
        samplesPerBit          = 128;

        corrDivisor            = 4;
        corrIdealSize          = 96;
        corrInSize             = 224;
        syncSampleBlocks       = 5;
        syncThreshold          = 8100;
        cor                    = (DATA *)cor_21875;
        clockTol               = 28;
        clockTolInc            = 4;

        dataMag                = 1024;
        dataMagNeg             = ~dataMag;
        syncMagShift           = 2;
        filter                 = lowDRFilter;
        phaseOffset            = 0;
        maintainFraction       = 4;     // shift by 4 == div by 16
    }

    lpfSize = samplesPerBit/2;

    // This value must be 1 to correspond correctly with the way the
    // DMA destination register is configured.
    buf              = 1;

    sampleBlkNo      =0;
    syncIndex        =0;
    syncFound        = FALSE;
    bitNum           = 0;
    prevBit          = PREV_BIT_INIT;
    lookingForSync   = TRUE;
    noTransCnt       = 0;
    syncBlkNo        = 0;
    lpfsum           = 0;
    tbv_rxInProgress = TRUE;
    tbv_rxByteCount  = 0;
    tbm_rcvState     = RCV_FIND_SYNC;
    frameFound       = FALSE;
    syncBits         = 0;
    shuttingDown     = FALSE;

    if (frameCount >= RCV_DEBUG_SIZE) frameCount = 0;
    if (errorCount >= ERROR_INDEX_SIZE) errorCount = 0;

    // Set up pointers to new receive buffer
    tbv_headRxBuffer = (UINT8 *)&receiveArray[receiveRow];
    tbv_tailRxBuffer = (UINT8 *)&receiveArray[receiveRow].dlHeader;

    // Zero out buffers.
    memcpy32(dBuffer, fill, sizeof(dBuffer));
    memcpy32(lpfOverlap, fill, sizeof(lpfOverlap));
    memcpy32(demodOverlap, fill, sizeof(demodOverlap));
    memcpy32(syncBlock, fill, sizeof(syncBlock));

    // These are 'marker' bytes just beyond the legitimate usable range
    // of these arrays. Inspection of these locations should show the
    // values intact if the bounds of the arrays have not been exceeded.
    corrOut[sizeof(corrOut) - 1]       = 0x5A;
    syncBlock[sizeof(syncBlock) - 1]   = 0xA5;
    in[sizeof(in) - 1]                 = 0x87;
    out[sizeof(out) - 1]               = 0x78;
    bitOverlap[sizeof(bitOverlap) - 1] = 0x36;
    rcvData[0][MAX_RCV_BUF_SIZE]       = 0x91;
    rcvData[1][MAX_RCV_BUF_SIZE]       = 0x19;

    // Set the I/O for the antenna configuration, High == receiving.
    SET_RCV();
    SET_RCV();     // Multiple usage of this macro was necessary to get the
    SET_RCV();     // setting to "stick". Remove only if functionality is verified!
    GLB_HTMR_WAIT(100);

    // Set the 150kHz/_2000kHz pin low, so that it doesn't impact receive.
    SET_TRX_LOW();
    SET_TRX_LOW();     // Multiple usage of this macro was necessary to get the
    SET_TRX_LOW();     // setting to "stick". Remove only if functionality is verified!

    // Initialize the McBSP, DMA, and DMA interrupt.
    initRcvMcBSP();
    initRcvDMA();
    initRcvDMAIrq();

    // Start McBSP0 as the DBPSK input data channel
    MCBSP_start(
        hMcbsp_TBRcv,
        MCBSP_RCV_START | MCBSP_SRGR_START | MCBSP_SRGR_FRAMESYNC,
        MCBSP_RCV_START_DELAY);

    // Now that the DMA config regs have been transferred to the working
    // regs we need to reprogram the rcv dest config regs
    addr = ((Uint32)&rcvData[1][0]) << 1;
    DMA_RSETH(tbv_hDma, DMACDSAL, addr & 0xffff);
    DMA_RSETH(tbv_hDma, DMACDSAU, (addr >> 16) & 0xffff);
}

/********************************************************************
FUNCTION: tbm_disableRcv

DESCRIPTION: This function disables the Telemetry B receive (uplink)
        peripherals. This function is intended to be called from the
        application layer code. It will wait for the receiver to go into
        idle state or timeout after 250us.
ARGS:
    BOOL done - TRUE if the receiver is to be shut down without
                        re-enabling.
RETURNS:
    None.
********************************************************************/
void tbm_disableRcv(BOOL done)
{
    if (tbm_rcvState != RCV_RESET) {

        shuttingDown = done;
        tbm_rcvState = RCV_RESET;

        debugVars.noSync++;

        errorIndex[errorCount++]             = frameCount;
        receiveDebug[frameCount].status      = RCV_NO_SYNC;
        receiveDebug[frameCount].rcvBytes    = tbv_rxByteCount;
        receiveDebug[frameCount].sampleBlkNo = sampleBlkNo;
        receiveDebug[frameCount++].syncScore = syncScore;

        GLB_GET_HTMR(rcvTimeout);

        while( tbm_rcvState != RCV_IDLE) {              // Receiver is now disabled, or
            if (GLB_HAS_HTMR_EXPIRED(rcvTimeout, 250000)) {                     // 250us timeout.
                asm ("	nop");
                asm ("	nop");
                asm ("	nop");                  // Instructions to set a breakpoint on.
                break;
            }
        }
    }
}

/********************************************************************
FUNCTION: startDisableRcv

DESCRIPTION: This function initiates the disabling of the Telemetry B
        receive (uplink) peripherals. After this function is executed,
        one additional receive DMA interrupt must be received to finish
        the disabling of the receiver peripherals.
ARGS:
    None
RETURNS:
    None.
********************************************************************/
static INLINE void startDisableRcv(void) {
    // Take the DMA out of 'autoinit' and 'repeat' mode so that DMA transfers
    // will discontinue after the current block completes.
    DMA_FSETH (tbv_hDma, DMACCR, REPEAT, 0);
    DMA_FSETH (tbv_hDma, DMACCR, AUTOINIT, 1);
    tbm_rcvState = RCV_DONE;
}

/********************************************************************
FUNCTION: disableRcv

DESCRIPTION: This function finishes the disabling of the Telemetry B
        receive (uplink) peripherals. This function MUST be called from
        within the receive DMA ISR.
ARGS:
    None
RETURNS:
    None.
********************************************************************/
static INLINE void disableRcv(void)
{
    // Reset and close McBSP0
    IRQ_clear(MCBSP_getRcvEventId(hMcbsp_TBRcv));

    MCBSP_FSET(SPCR10, RRST, 0);
    MCBSP_FSET(SPCR20, FRST, 0);
    MCBSP_FSET(SPCR20, GRST, 0);
    MCBSP_FSET(SPCR20, XRST, 0);
    MCBSP_close(hMcbsp_TBRcv);

    // Get Event ID associated with the DMA channel interrupt
    // and disable DMA interrupt (IER)
    IRQ_disable(DMA_getEventId(tbv_hDma));

    // Clear out any pending interrupts.
    DMA_RGETH(tbv_hDma, DMACSR);
    IRQ_clear(DMA_getEventId(tbv_hDma));

    tbv_rxInProgress = FALSE;

    // Note that the DMA channel is not closed here. It is left
    // open through the Telemetry B session. Closing the DMA channel
    // adds significantly to turnaround time.
    DMA_stop(tbv_hDma);
}

/********************************************************************
FUNCTION: tbm_disableRcvInt

DESCRIPTION: This function disables the receiver DMA interrupt, if
        it is currently enabled.
ARGS:
    None
RETURNS:
    None.
********************************************************************/
void tbm_disableRcvInt (void)
{
    // Disabling the receive DMA interrupt proved to not be needed!

    // if (tbv_rxInProgress) IRQ_disable(DMA_getEventId(tbv_hDma));
}

/********************************************************************
FUNCTION: tbm_enableRcvInt

DESCRIPTION: This function enables the receiver DMA interrupt, if
        a receive is currently in progress, or should be in progress.
ARGS:
    None
RETURNS:
    None.
********************************************************************/
void tbm_enableRcvInt (void)
{
    // Since disabling was not needed, re-enabling is not either.

    // if (tbv_rxInProgress) IRQ_enable(DMA_getEventId(tbv_hDma));
}

/********************************************************************
FUNCTION: initRcvMcBSP

DESCRIPTION: This function initializes the McBSP to capture Telemetry
        B uplink data words.
ARGS:
    None
RETURNS:
    None.
********************************************************************/
static INLINE void initRcvMcBSP()
{
    static const MCBSP_Config mcbspCfgTBRcv = {
        0x0000,    /*  Serial Port Control Register 1   */
        0x0100,    /*  Serial Port Control Register 2   */
        0x3f00,    /*  Receive Control Register 1   */
                   /*  0x00 = 8 bit word */
        /*  0x3f = 63 = (63 + 1) == 64 word frame */
        0x000d,    /*  Receive Control Register 2   */
        /*  ignore unexpected FS, 1 bit delay, single phase, LSB received first */
        0x0000,    /*  Transmit Control Register 1   */
        0x0000,    /*  Transmit Control Register 2   */
        0x0035,    /*  Sample Rate Generator Register 1   */
        /*  0x35 == 53 => CPU / ((53 + 1) * 2) == 2.7777MHz */
        0x21ff,    /*  Sample Rate Generator Register 2   */
        0x0000,    /*  Multichannel Control Register 1   */
        0x0000,    /*  Multichannel Control Register 2   */
        0x0500,    /*  Pin Control Register   */
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
    // Open the McBSP0 for Telemetry B Receive functionality.
    hMcbsp_TBRcv = MCBSP_open(MCBSP_PORT0,MCBSP_OPEN_RESET);

    // Configure the McBSP for receive operation.
    MCBSP_config(hMcbsp_TBRcv, (MCBSP_Config *)&mcbspCfgTBRcv);
}

/********************************************************************
FUNCTION: initRcvDMA

DESCRIPTION: This function initializes the DMA to capture Telemetry
        B uplink data blocks.
ARGS:
    None
RETURNS:
    None.
********************************************************************/
static INLINE void initRcvDMA()
{
    UINT32     addr;
    DMA_Config gDmaConfigRcv = {
        DMA_DMACSDP_RMK(
            DMA_DMACSDP_DSTBEN_NOBURST,
            DMA_DMACSDP_DSTPACK_OFF,
            DMA_DMACSDP_DST_DARAMPORT1,
            DMA_DMACSDP_SRCBEN_NOBURST,
            DMA_DMACSDP_SRCPACK_OFF,
            DMA_DMACSDP_SRC_PERIPH,
            DMA_DMACSDP_DATATYPE_16BIT
            ),  /* Source/Destination Register - DMACSDP  */
        DMA_DMACCR_RMK(
            DMA_DMACCR_DSTAMODE_POSTINC,
            DMA_DMACCR_SRCAMODE_CONST,
            DMA_DMACCR_ENDPROG_OFF,
            DMA_DMACCR_REPEAT_OFF,
            DMA_DMACCR_AUTOINIT_ON,
            DMA_DMACCR_EN_STOP,
            DMA_DMACCR_PRIO_HI,
            DMA_DMACCR_FS_DISABLE,
            DMA_DMACCR_SYNC_REVT0
            ),  /* Control Register - DMACCR   */
        DMA_DMACICR_RMK(
            DMA_DMACICR_BLOCKIE_OFF,
            DMA_DMACICR_LASTIE_OFF,
            DMA_DMACICR_FRAMEIE_ON,
            DMA_DMACICR_FIRSTHALFIE_OFF,
            DMA_DMACICR_DROPIE_OFF,
            DMA_DMACICR_TIMEOUTIE_OFF
            ),  /* Interrupt Control Register - DMACICR  */
        0,                              /* Lower Source Address - DMACSSAL */
        0,                              /* Upper Source Address - DMACSSAU */
        0,                              /* Lower Destination Address - DMACDSAL */
        0,                              /* Upper Destination Address - DMACDSAU */
        0,                              /* Element Number - DMACEN   */
        1,                              /* Frame Number - DMACFN   */
        1,                                      /* Source Frame Index - DMACSFI   */
        1,                                      /* Source Element Index - DMACSEI   */
        1,                                      /* Dest Frame Index - DMACDFI   */
        1                                       /* Dest Element Index - DMACDEI   */
    };

    // DMA source address for all transfers.
    addr                   = ((Uint32)&_MCBSP_DRR10) << 1;
    gDmaConfigRcv.dmacssal = (DMA_AdrPtr)(addr & 0xffff);
    gDmaConfigRcv.dmacssau = (Uint16)((addr >> 16) & 0xffff);

    // DMA destination address for the 1st transfer.
    addr                   = ((Uint32)&rcvData[0][0]) << 1;
    gDmaConfigRcv.dmacdsal = (DMA_AdrPtr)(addr & 0xffff);
    gDmaConfigRcv.dmacdsau = (Uint16)((addr >> 16) & 0xffff);

    gDmaConfigRcv.dmacen   = blkSize/8;

    // Write values from DMA config structure to DMA channel control registers
    DMA_config(tbv_hDma, &gDmaConfigRcv);

    // Clear out any pending interrupts.
    DMA_RGETH(tbv_hDma, DMACSR);

    // Start receive DMA
    DMA_start(tbv_hDma);
}

/********************************************************************
FUNCTION: initRcvDMAIrq

DESCRIPTION: This function enables the Telemetry B receive (uplink)
        DMA interrupt.
ARGS:
    None
RETURNS:
    None.
********************************************************************/
static INLINE void initRcvDMAIrq()
{
    UINT16 eventID;
    // Get Event ID associated with the DMA channel interrupt
    eventID = DMA_getEventId(tbv_hDma);

    // Clear any pending channel interrupt (IFR)
    IRQ_clear(eventID);

    // Enable DMA interrupt (IER)
    //tbm_enableRcvInt();
    IRQ_enable(DMA_getEventId(tbv_hDma));

    // Place the HWI hook at the proper spot in the interrupt vector table
    // and enable the dispatcher for this interrupt
    IRQ_plug(eventID, &rcvDMAHwi);
}

/********************************************************************
FUNCTION: initRcvDMAIrq

DESCRIPTION: This is the Telemetry B receive (uplink) DMA interrupt.
        It is called once per sample block.
        256 Point Sample Block for low data rate:
        At 2.77MHz, a 256 sample block is collected in 91.42us.
        192 Point Sample Block for high data rate:
        At 2.77MHz, a 192 sample block is collected in 69.31us.

        The DMA for the next sample block is re-initialized, and the
        processFrame function is called to process the collected data.

ARGS:
    None
RETURNS:
    None.
********************************************************************/
interrupt void rcvDMAHwi (void)
{
    UINT32 addr;
    INT16  intm;

#ifdef DEBUG_RCV_PROC_TIME
        #warn "Receive Processing Time Monitor Enabled."
    _GPIO_IODATA |= GPIO_PIN4;
#endif

    ++sampleBlkNo;

    // Clear any pending interrupts.
    DMA_RGETH(tbv_hDma, DMACSR);

    intm = IRQ_globalDisable();

    // Toggle which buffer is being filled.
    buf ^= 1;

    // Reprogram the Rcv DMA dest config regs
    DMA_FSETH (tbv_hDma, DMACCR, ENDPROG, 0);
    addr = ((Uint32)&rcvData[buf][0]) << 1;
    DMA_RSETH(tbv_hDma, DMACDSAL, addr & 0xffff);
    DMA_RSETH(tbv_hDma, DMACDSAU, (addr >> 16) & 0xffff);
    DMA_FSETH (tbv_hDma, DMACCR, ENDPROG, 1);

    // Process the block of data.
    processFrame(&rcvData[buf][0]);

    IRQ_globalRestore(intm);

#ifdef DEBUG_RCV_PROC_TIME
    _GPIO_IODATA &= ~(GPIO_PIN4);
#endif
}

/*********************************************************************
FUNCTION: sync_mgmt

DESCRIPTION: This function sequences the activities that occur during
the 'search for sync' phase of an uplink.

ARGS: None.
RETURNS: None.
**********************************************************************/
static INLINE void sync_mgmt (DATA *inBuf)
{
    int x;

    // First collect 'syncSampleBlocks' sample blocks of data...
    if (++syncBlkNo <= syncSampleBlocks) {

        processDBPSKData(inBuf);

        // Store the data, but reduce the size
        // of the output array by 'corrDivisor'.
        for(x=0; x<blkSize; x+=corrDivisor) {
            syncBlock[syncIndex++] = in[x] >> syncMagShift;
        }
    }

    // ...then process it to see if sync is present.
    else {
        syncBlkNo = 0;
        syncIndex = 0;
        findSync();
        if (syncFound) {
            tbm_rcvState = RCV_FIRST_SYNCED;
        }
    }
}

/********************************************************************
FUNCTION: processFrame

DESCRIPTION: This function sequences the processing of a frame of
        uplink data. The sequence includes finding sync and then extracting
        the data bit values.

ARGS:
    DATA *inBuf - buffer of data to process.
RETURNS:
    None.
********************************************************************/
static INLINE void processFrame(DATA *inBuf)
{
    switch(tbm_rcvState) {
    // Search for sync in this state.
    case RCV_FIND_SYNC:
        sync_mgmt(inBuf);
        break;

    // One set of data is collected after sync in this state to
    // fill the FIR filter delay buffer.
    case RCV_FIRST_SYNCED:
        processDBPSKData(inBuf);
        tbm_rcvState = RCV_SECOND_SYNCED;
        break;

    // Another set of data is collected after sync in this state to
    // fill the demodulation delay buffer.
    case RCV_SECOND_SYNCED:
        processDBPSKData(inBuf);
        // Save the last bit period's bits for potential processing in next block.
        memcpy32(bitOverlap, &in[blkSize-samplesPerBit], samplesPerBit);
        tbm_rcvState = RCV_SYNCED;
        break;

    // The data of the frame is processed in this state.
    case RCV_SYNCED:
        processDBPSKData(inBuf);
        extractBitVals();
        break;

    // This state is only entered if the receiver is disabled due to
    // an error during reception.
    case RCV_RESET:
        // Start the disabling of the receiver.
        startDisableRcv();
        break;

    // This state is entered when a frame has been received.
    case RCV_FINISH:
        // Start the disabling of the receiver.
        startDisableRcv();

        shuttingDown = FALSE;

        // Finish processing the frame that was just received and
        // determine the next action to take.
        finishRcv();
        break;

    // This the final state for reception of a frame.
    case RCV_DONE:
        // Complete the disabling of the receiver.
        disableRcv();

        tbm_rcvState = RCV_IDLE;

        if (!shuttingDown) {

            // Put in process function to check for next transmission
            if (rxFrameInfo.processFunction != NULL) {

                (rxFrameInfo.processFunction)();

                // Null it out so that it must be explicitly set for
                // a future frame.
                rxFrameInfo.processFunction = NULL;
            }

            // We're done processing the frame that was just received.
            // If there's a frame to transmit, do that; otherwise just
            // listen for asynchronous uplink frames.
            if (tbv_p_nextDownlink != NULL) {
                tbm_txFrame();
            }

            // This is only needed when we're in session when asynchronous
            // uplinks need to be handled.
            else if (tbv_linkMaintainSession) {
                tbm_startPacketRcv();
            }
        }
        else {
            shuttingDown = FALSE;
        }
        break;

    case RCV_IDLE:
        break;
    }
}

// ***************************************************************************
// * processDBPSKData
// *
// * Description:
// * Note: With a 512 point FFT, the number of stages is odd, so the result
// * ends up in 'in', not 'out'.
// ***************************************************************************
static INLINE void processDBPSKData(DATA *inBuf)
{
    // Unpack McBSP serial samples into separate words.
    unpackData(out, inBuf);

    fir2 (  out,                        // Input data
            filter,                             // Filter kernel data
            in,                                 // Output Data
            dBuffer,                            // Delay Buffer for overlapping blocks
            blkSize,                            // Size of the block of input data
            FILTER_SIZE);               // Size of the filter kernel.

    // Demodulate
    demodulate(in, out);

    // Low pass filter the demodulated data.
    lpf(out, in);

}

//***************************************************************************
//* unpackData -
//* This function unpacks McBSP serial word samples into a word for each bit.
//* For example, a 16 bit McBSP serial word would be unpacked into 16
//* contiguous memory locations. The magnitude is dataMag, or its negation.
//***************************************************************************
static INLINE void unpackData (DATA *dst, DATA *src)
{
    int  x,z;
    DATA temp, bufSize=blkSize/8;

    for (x=0; x<bufSize; ++x, src++) {
        temp = *src;
        for (z=0; z<MCBSP_RCV_WORD_SIZE; ++z, temp>>=1) {
            *dst++ = (temp & 1) ? dataMag : dataMagNeg;
        }
    }
}

//***************************************************************************
//* lpf
//* This function implements a "moving window average" low pass filter. Its
//* purpose is to smooth demodulated data. The size of the window should
//* ideally be chosen to be half the number of sample in a data bit.
//***************************************************************************
static INLINE void lpf(DATA *input, DATA *output)
{
    int x, y;
    if (desiredUplinkRate == tbc_dr_87) {
        for (x=0, y=-lpfSize; x<BLK_SIZE_87500; ++x, ++y ) {
            lpfsum   += (input[x] - input[y]);
            output[x] = (DATA)(lpfsum >> 4);             //divide by 16	(half of filter size)
        }
    }
    else {
        for (x=0, y=-lpfSize; x<BLK_SIZE_21875; ++x, ++y ) {
            lpfsum   += (input[x] - input[y]);
            output[x] = (DATA)(lpfsum >> 6);             //divide by 64	(half of filter size)
        }
    }
    memcpy32(&lpfOverlap[MAX_LPF_SIZE - lpfSize], &input[blkSize - lpfSize], lpfSize);
}

//***************************************************************************
//* demodulate -
//* DBPSK data is demodulated by shifting sample data by one bit period, and
//* then multiplying together. The demodulated output is scaled to allow the
//* result to fit in a 16 bit word.
//***************************************************************************
static INLINE void demodulate(DATA *input, DATA *output)
{
    int x,y;

    for (x=0,y=-samplesPerBit; x<blkSize; ++x, ++y) {
        output[x] = ((INT32)input[x] * (INT32)input[y]) >> 16;
    }

    memcpy32(
        &demodOverlap[MAX_SAMPLES_PER_BIT-samplesPerBit],
        &input[blkSize-samplesPerBit],
        samplesPerBit);
}

/********************************************************************
FUNCTION: extractBitVals

DESCRIPTION: This function examines the receive bitstream and decodes
        the data. Task include skipping through the sync bits, finding the
        start flag, NRZI decoding the data, bit de-stuffing the data,
        storing the data, and finding the end flag byte.

ARGS:
    None.
RETURNS:
    None.
********************************************************************/
#define BIT_VAL_H(loc) ((*(loc+8) + *(loc+13) + *(loc+18)) > 0) ? 1 : 0
#define BIT_VAL_L(loc) ((*(loc+32) + *(loc+64) + *(loc+96)) > 0) ? 1 : 0

static INLINE void extractBitVals(void)
{
    DATA *ptr=corrOut;

    ptr += samplesPerBit;

    // Restore the last bit period's bits for potential processing in this block.
    memcpy32(corrOut, bitOverlap, samplesPerBit);
    memcpy32(ptr, in, blkSize);

    clockPhase -= blkSize;

    // Loop through full data bits within the current block of samples.
    do {

        // Get the value of the current bit.
        curBit = (desiredUplinkRate == tbc_dr_87) ?
                 BIT_VAL_H(&ptr[clockPhase]) : BIT_VAL_L(&ptr[clockPhase]);

        // If this is the first time this check is performed, just assume
        // that the sync pattern is in progress.
        if (prevBit == PREV_BIT_INIT) {
            prevBit = curBit ^ 1;
        }

        clockPhase = maintainClockPhase(ptr, clockPhase, ((curBit) ? 1 : -1));

        // NRZI decode the bit.
        nrzi       = (curBit ^ prevBit) ? 0 : 1;
        prevBit    = curBit;

        // Check to see if its at the end of the sync sequence yet.
        // Note: while in the sync sequence, the nrzi value will always be 0.
        if (lookingForSync) {

            // Out of sync pattern now.
            if (nrzi == 1) {
                lookingForSync                    = FALSE;
                tData                             = 0x02;
                bitNum                            = 2;
                rcvOnes                           = 1;
                foundStartFlag                    = FALSE;
                rcvDestuffBits                    = 0;
                rcvBits                           = 2;
                receiveDebug[frameCount].syncBits = syncBits;
            }
            else {
                ++syncBits;
            }
        }

        // Store data bits if we're past the sync sequence.
        else if (!lookingForSync) {

            ++rcvBits;

            switch (rcvOnes) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
                // Maintain the count of consecutive '1' bits received for bit destuff.
                rcvOnes = (nrzi) ? rcvOnes+1 : 0;

                // Store the current bit in its correct position in the byte.
                tData  |= (nrzi << bitNum);

                // A full byte has been extracted. Checking framing, and store it away.
                if (bitNum >= 7) {
                    // Exceeded the maximum frame size yet?
                    if (tbv_rxByteCount >= (TBC_MAX_UPLINK_BYTE_SIZE+4)) {

                        debugVars.overruns++;
                        errorIndex[errorCount++]             = frameCount;
                        receiveDebug[frameCount].status      = RCV_OVERRUN;
                        receiveDebug[frameCount].rcvBytes    = tbv_rxByteCount;
                        receiveDebug[frameCount].sampleBlkNo = sampleBlkNo;
                        receiveDebug[frameCount++].syncScore = syncScore;
                        startDisableRcv();
                        return;
                    }
                    // We're in the middle of the frame. Store the data.
                    else {
                        *tbv_tailRxBuffer = tData;
                        ++tbv_tailRxBuffer;
                        ++tbv_rxByteCount;
                        tData             = 0;
                        bitNum            = 0;
                    }
                }
                else {
                    bitNum++;
                }
                break;

            // If we've had 5 ones in a row and the current bit is a zero, it is
            // a stuffed zero; ignore it.
            case 5:
                if (!nrzi) {
                    rcvOnes = 0;
                    ++rcvDestuffBits;
                }
                else {
                    // This condition should only occur for flag bytes or an abort.
                    ++rcvOnes;
                    tData |= (nrzi << bitNum);
                    bitNum++;
                }
                break;

            // Six ones in a row followed by a zero is a flag byte. Look for the
            // start flag first, then the end flag.
            case 6:
                if (!nrzi) {
                    rcvOnes = 0;

                    if (!foundStartFlag) {
                        if (tData != TBC_flag) {
                            debugVars.openingFlagErrors++;
                            errorIndex[errorCount++]             = frameCount;
                            receiveDebug[frameCount].status      = RCV_OPEN_FLAG_ERR;
                            receiveDebug[frameCount].rcvBytes    = tbv_rxByteCount;
                            receiveDebug[frameCount].sampleBlkNo = sampleBlkNo;
                            receiveDebug[frameCount++].syncScore = syncScore;
                            startDisableRcv();
                            return;
                        }
                        else {
                            debugVars.openingFlags++;
                            foundStartFlag                              = TRUE;
                            receiveDebug[frameCount].sampleBlkNoAtStart = sampleBlkNo;
                            tData                                       = 0;
                            bitNum                                      = 0;
                        }
                    }
                    else {
                        // The flag byte will denote the end of the frame.
                        if (tData == TBC_flag) {
                            frameFound   = TRUE;
                            debugVars.EOFsFound++;
                            tbm_rcvState = RCV_FINISH;

                            //Reduce the block size to reduce the last block
                            //sample time; minimizes turnaround time.
                            DMA_RSETH (tbv_hDma, DMACEN, 28);
                            return;
                        }
                        // Invalid end flag.
                        else {
                            debugVars.EOFErrors++;
                            errorIndex[errorCount++]             = frameCount;
                            receiveDebug[frameCount].status      = RCV_END_FLAG_ERR;
                            receiveDebug[frameCount].rcvBytes    = tbv_rxByteCount;
                            receiveDebug[frameCount].sampleBlkNo = sampleBlkNo;
                            receiveDebug[frameCount++].syncScore = syncScore;
                            startDisableRcv();
                            return;
                        }
                    }
                }
                else {
                    // Seven ones in a row is an abort condition.
                    debugVars.aborts++;
                    errorIndex[errorCount++]             = frameCount;
                    receiveDebug[frameCount].status      = RCV_ABORT;
                    receiveDebug[frameCount].rcvBytes    = tbv_rxByteCount;
                    receiveDebug[frameCount].sampleBlkNo = sampleBlkNo;
                    receiveDebug[frameCount++].syncScore = syncScore;
                    startDisableRcv();
                    return;
                }
                break;
            }
        }

        // Loop through FULL data bits within the current block of samples,
        // else wait til the next sample block to use the remaining samples
        // plus the new samples.
    } while ((clockPhase + samplesPerBit) < blkSize);

    // Save the last bit period's bits for potential processing in next block.
    memcpy32(bitOverlap, &in[blkSize-samplesPerBit], samplesPerBit);
}

/********************************************************************
FUNCTION: maintainClockPhase

DESCRIPTION: This function maintains the clock phase from the receive
        bitstream. Zero phase synchronization is initially found in
        'findSync'. Using that starting point, this function looks forward
        at the nominal bit period +/- some tolerance for the position at
        which the zero cross occurs. A fraction of the difference between
        the nominal position and the found position is chosen as the new
        zero phase position.

ARGS:
    DATA *ptr - pointer to the receive data block
    DATA loc - zero phase position of the previous bit.
    INT16 previousBit - the value of the previous bit.
RETURNS:
    None.
********************************************************************/
static INLINE DATA maintainClockPhase(DATA *ptr, DATA loc, INT16 previousBit)
{
    int x;
    int nextLoc;

    nextLoc = loc + samplesPerBit;

    // Find the first transition location. Bit values are 1 or -1. A
    // transition has occurred if the previous bit and the current sample
    // multiplied together are negative.
    for (x=-clockTol; x<clockTol; x+=clockTolInc) {
        if (ptr[nextLoc + x] * previousBit < 0) {               // zero cross if < 0
            noTransCnt = 0;
            return(nextLoc + (x >> maintainFraction));
        }
    }

    // If no transition was found within the +/-CLOCK_TOL, then just
    // assume it to be at the nominal position. Note - there will be no
    // transition if the current and previous bit values are the same.
    // The maximum bits without a transition is 6 (in a flag byte).
    if (++noTransCnt > 6) {
        debugVars.lostSync++;

        errorIndex[errorCount++]             = frameCount;
        receiveDebug[frameCount].status      = RCV_LOST_SYNC;
        receiveDebug[frameCount].rcvBytes    = tbv_rxByteCount;
        receiveDebug[frameCount].sampleBlkNo = sampleBlkNo;
        receiveDebug[frameCount++].syncScore = syncScore;

        tbm_rcvState                         = RCV_DONE;
        noTransCnt                           = 0;
    }

    return (nextLoc);

}

/********************************************************************
FUNCTION: findSync

DESCRIPTION: This function finds zero phase synchronization by
        correlating an ideal sine wave at the sync period with the
        sampled receive data.

ARGS:
        None.
RETURNS:
    None.
********************************************************************/
static INLINE void findSync(void)
{
    BOOL syncPresent = FALSE;
    DATA minPhase;
    DATA *dptr       = (desiredUplinkRate == tbc_dr_87) ?
                       syncBlock : &syncBlock[blkSize / corrDivisor];

    // Run a correlation of the output array against the
    // ideal sync pattern.
    corr_raw (cor,                              // Correlation Pattern
              dptr,                                     // Input Data
              corrOut,                                  // Correlation Output Array
              corrIdealSize,                    // Correlation Pattern Size
              corrInSize);                      // Input Data Size

    // Find the maximum value in the correlation output array.
    prevSyncScore = syncScore;
    prevCorrIndex = corrIndex;
    maxvec (corrOut, corrInSize+corrIdealSize-1, &syncScore, &corrIndex);

    // If the correlation max is above a certain threshold, then
    // sync has been found.
    if (syncScore > syncScoreMax) syncScoreMax = syncScore;

    // Threshold has been exceeded.
    if ((syncScore >= syncThreshold) && (corrIndex <= (corrInSize+15))) {
        // At the 87.5k uplink rate, multiple peaks will be present in the correlation.
        if (desiredUplinkRate == tbc_dr_87) {
            if ((corrOut[corrIndex+32] > syncThreshold) ||
                (corrOut[corrIndex-32] > syncThreshold)) {
                syncPresent = TRUE;
            }
        }
        else {
            // At the 21.875k uplink, rate at a minimum an additional peak, or
            // a negative peak will be present.
            if (( corrOut[corrIndex+64] > syncThreshold) ||
                ( corrOut[corrIndex-64] > syncThreshold) ||
                (-corrOut[corrIndex-32] > syncThreshold) ||
                (-corrOut[corrIndex+32] > syncThreshold)) {
                syncPresent = TRUE;
            }
        }
    }

    // Note - find max. vector in the whole corr out. If the max is
    // beyond CORR_IN_SIZE, then it is not valid; wait for the next cycle.
    if (syncPresent) {

        if (syncScore < syncScoreMin)
            syncScoreMin = syncScore;

        clockPhase                                 = corrIndex  * corrDivisor;

        minPhase                                   = blkSize - samplesPerBit - phaseOffset;
        while(clockPhase >= minPhase) clockPhase -= samplesPerBit;
        clockPhase                                += blkSize;
        clockPhase                                += phaseOffset;
        syncFound                                  = TRUE;
        receiveDebug[frameCount].sampleBlkNoAtSync = sampleBlkNo;
    }

    syncIndex=0;
    lpfsum   = 0;
    memcpy32(lpfOverlap, fill, sizeof(lpfOverlap));
    memcpy32(dBuffer, fill, sizeof(dBuffer));
    memcpy32(demodOverlap, fill, sizeof(demodOverlap));
}

/********************************************************************
FUNCTION: finishRcv

DESCRIPTION: This function completes the processing of the received
        frame of data. This includes checking the CRC of the frame, and
        determining the next course of action to take. (tbm_uplinkStarted,
        tbm_uplinkComplete).

ARGS:
        None.
RETURNS:
    None.
********************************************************************/
static INLINE void finishRcv (void)
{
    static UINT16 crc;

    // Don't bother checking the CRC if a frame wasn't found.
    if (!frameFound) return;

    // Calculate the CRC of the frame and store it at the CRC position of the frame.
    crc  = tbm_frameCRC(&receiveArray[receiveRow].dlHeader, tbv_rxByteCount);
    crc ^= 0xffff;

    // 0xF0B8 is the 'magic number' for the CCITT CRC with
    // character reversing and CRC complimenting.
    if (crc != 0xF0B8) {
        debugVars.crcErrors++;

        errorIndex[errorCount++]             = frameCount;
        receiveDebug[frameCount].status      = RCV_CRC_ERR;
        receiveDebug[frameCount].rcvBytes    = tbv_rxByteCount;
        receiveDebug[frameCount].sampleBlkNo = sampleBlkNo;
        receiveDebug[frameCount++].syncScore = syncScore;

    }
    else {
        receiveDebug[frameCount].status      = RCV_PASS;
        receiveDebug[frameCount].rcvBytes    = tbv_rxByteCount;
        receiveDebug[frameCount].sampleBlkNo = sampleBlkNo;
        receiveDebug[frameCount++].syncScore = syncScore;

        tbm_uplinkStarted(receiveArray[receiveRow].dlHeader);

#ifdef DEBUG_HEADERS_ON
        debugHeaders[debugHeadersIndex++] = (receiveArray[receiveRow].dlHeader | RCV_HEADER);
        debugHeadersIndex                &= DEBUG_HEADERS_MASK;
#endif

        tbm_uplinkComplete(receiveRow);

        // fill in header info for uplink - length and final frame
        // Subtract 2 from the length to account for the 2 CRC bytes.
        receiveArray[receiveRow].length = tbv_rxByteCount - 2;

        // Point to new buffer
        ++receiveRow;

        // There is a circular buffer of 8
        receiveRow     &= 0x7;

        // Reset to zero for the next receive frame
        tbv_rxByteCount = 0;

    }
}

//***************************************************************************
//* memcpy32
//* Use this function to copy 32 bit wide data twice as fast as a normal
//* 'memcpy'.
//* void *dst - destination address. Must be 32 bit aligned.
//* void *src - source address. Must be 32 bit aligned.
//* int cnt - number of 16 bit 'words' to copy. Must be an even number.
//***************************************************************************
static INLINE void memcpy32(void *dst, void *src, INT16 cnt)
{
    int    x;
    UINT32 *d = (UINT32 *)dst, *s = (UINT32 *)src;
    for (x=0; x<(cnt/2); ++x) {
        *d++ = *s++;
    }
}
