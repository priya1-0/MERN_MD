#include "global.h"
#include "tbm_rcv.h"
#include "tbm_trx.h"
#include "tbm_channel.h"
#include "tbm_handler.h"
#include "tbm_events.h"
#include "tbm_timer.h"

#include <csl.h>
#include <csl_gpio.h>
#include <string.h>

#define DEFINED_HERE
#include "tbm_main.h"
#undef DEFINED_HERE

extern int load_start_of_tbcode;
extern int run_start_of_tbcode;
extern int size_of_tbcode;
extern int load_start_of_tbconst;
extern int run_start_of_tbconst;
extern int size_of_tbconst;
extern int size_of_tbextdata;
extern int run_start_of_tbextdata;
extern int run_start_of_tbdata;
extern int size_of_tbdata;

//*************************************************************
//* tbm_codeCopy
//* This function copies TB module code from SDRAM to the
//* internal DARAM.
//************************************************************
#pragma CODE_SECTION(tbm_codeCopy, ".tbmExtCode")
void tbm_codeCopy(void)
{
    UINT16 *dst;
    UINT32 d,cnt;
    int    x;

    UINT16 *src;
    UINT32 s;

    // Copy the Telemetry B Code
    s   = ((UINT32)(&load_start_of_tbcode)) >> 1;
    src = (UINT16 *)(s);

    d   = ((UINT32)(&run_start_of_tbcode)) >> 1;
    dst = (UINT16 *)(d);

    cnt = ((UINT32)(&size_of_tbcode)) >> 1;

    for(x=0; x<cnt; ++x) *dst++ = *src++;

    // Copy the Telemetry B Constants
    s   = ((UINT32)(&load_start_of_tbconst)) >> 1;
    src = (UINT16 *)(s);

    d   = ((UINT32)(&run_start_of_tbconst)) >> 1;
    dst = (UINT16 *)(d);

    cnt = ((UINT32)(&size_of_tbconst)) >> 1;

    for(x=0; x<cnt; ++x) *dst++ = *src++;

    // Initialize the Telemetry B Data to 0.
    cnt = ((UINT32)(&size_of_tbdata)) >> 1;

    d   = ((UINT32)(&run_start_of_tbdata)) >> 1;
    dst = (UINT16 *)(d);
    for(x=0; x<cnt; ++x) *dst++ = 0;

    // Initialize the external Telemetry B Data to 0.
    cnt = ((UINT32)(&size_of_tbextdata)) >> 1;

    d   = ((UINT32)(&run_start_of_tbextdata)) >> 1;
    dst = (UINT16 *)(d);
    for(x=0; x<cnt; ++x) *dst++ = 0;

}

/********************************************************************
FUNCTION: tbm_init

DESCRIPTION: This function performs all tasks necessary to enable the
        Telemetry B module, including copying the TBM code from SDRAM to
        the internal DARAM as well as one time initialization of variables.
ARGS:
    None
RETURNS:
    None.
********************************************************************/
#pragma CODE_SECTION(tbm_init, ".tbmExtCode")
void tbm_init(void)
{
    tbm_codeCopy();
    tbm_trxInit();
    tbm_initRcv();
    tbm_hsDisable();

#ifdef DEBUG_STATE
    memset(state, 0, sizeof(state));
    stateIndex = 0;
#endif

#ifdef DEBUG_HEADERS_ON
    memset(debugHeaders, 0, sizeof(debugHeaders));
    debugHeadersIndex = 0;
#endif

#ifdef DEBUG_SHORT_TIMEOUT
        #warn "Telemetry B Short timeout Testing Enabled"
    GLB_CLR_XF;
#endif

#ifdef DEBUG_RCV_PROC_TIME
        #warn "Telemetry B Receive Processing Time Testing Enabled"
    // Configure GPIO4 as a debug output for this test and set low.
    _GPIO_IODIR  |= GPIO_PIN4;
    _GPIO_IODATA &= ~GPIO_PIN4;
#endif

    // tbm_main
    tbv_txInProgress                 = FALSE;
    tbv_rxInProgress                 = FALSE;
    tbv_tailRxBuffer                 = NULL;
    tbv_headRxBuffer                 = NULL;
    tbv_txByteCount                  = 0;
    tbv_txSize                       = 0;

    // tbm_rcv
    tbv_downlinkSequenceNumber       = 0;
    tbv_expectedUplinkSequenceNumber = 0;
    tbv_numberOfUnAckedFrames        = 0;
    handshakeTickCounter20mS         = 13; // > 12 is disabled
    timeToHandshake                  = FALSE;
    tbv_immediateACK                 = FALSE;
    programmerID                     = 0x0000;
    tbv_linkMaintainSession          = FALSE;
    tbv_startWFsequenceChecking      = FALSE;
    tbv_waveformsMissed              = 0;
    priorWFSequenceNumber            = 0;
    currentWFSequenceNumber          = 0;

    // tbm_trx
    tbv_p_headTxBuffer               = NULL;
    tbv_p_nextDownlink               = NULL;
    tbv_p_ackNakdl                   = NULL;

    // tbm_channel
    shortTimeoutTimerInitialized     = FALSE;
    tbv_respCurrentLength            = 0;
    tbv_unexpEventCounter            = 0;
    memset(&tbv_chanCoverage, 0, sizeof(tbv_chanCoverage));

    // tbm_events
    tbv_moreEventsFlag        = FALSE;
    tbv_timerExpiredFlag      = FALSE;

    // tbm_handler
    tbv_tag                   = 0;
    tbv_session.sessionStatus = tbc_successful;

    // This must be at the end of this function.
    tbv_active                = TRUE;
}

/********************************************************************
FUNCTION: tbm_disable

DESCRIPTION: This function disables the Telemetry B receive or transmit
        peripherals (depending on which is currently active).
ARGS:
    None
RETURNS:
    None.
********************************************************************/
void tbm_disablePhysLayer(BOOL done)
{
    if (tbv_txInProgress) {
        tbm_disableTrx();
    }
    else if (tbv_rxInProgress) {
        tbm_disableRcv(done);
    }
}

/********************************************************************
FUNCTION: tbm_disableInterrupts

DESCRIPTION: This function disables the Telemetry B receive or transmit
        interrupts and timer interrupt.

        Note - disabling of these interrupts must be MINIMIZED during
        Telemetry B activity or the physical layer processing may be
        corrupted.

ARGS:
    None
RETURNS:
    None.
********************************************************************/
void tbm_disableInterrupts (void)
{
    // Disable the periodic timer (PRD) interrupt.
    IRQ_disable(IRQ_EVT_TINT0);

    // Disable the telemetry B trx/rcv interrupt(s) if enabled.
    tbm_disableRcvInt();
    tbm_disableTrxInt();
}

/********************************************************************
FUNCTION: tbm_enableInterrupts

DESCRIPTION: This function enables the Telemetry B receive or transmit
        interrupts and timer interrupt that were enabled previous to the
        last call of tbm_disableInterrupts and timer interrupt.

        This function should only be used to re-enable interrupts that
        were disabled using tbm_disableInterrupts!!

        Note - Disabling of these interrupts must be MINIMIZED during
        Telemetry B activity or the physical layer processing may be
        corrupted.

ARGS:
    None
RETURNS:
    None.
********************************************************************/
void tbm_enableInterrupts (void)
{
    // Re-enable the periodic timer (PRD) interrupt.
    IRQ_enable(IRQ_EVT_TINT0);

    // Re-enable the telemetry B trx/rcv interrupt(s) if they
    // should be enabled
    tbm_enableRcvInt();
    tbm_enableTrxInt();
}

void tbm_PRDIntEnable(void )
{
    // Re-enable the periodic timer (PRD) interrupt.
    IRQ_enable(IRQ_EVT_TINT0);
}

void tbm_PRDIntDisable(void )
{
    // Disable the periodic timer (PRD) interrupt.
    IRQ_disable(IRQ_EVT_TINT0);
}

/********************************************************************
FUNCTION: tbm_PRD

DESCRIPTION: This function is called from a 20ms period DSP/BIOS PRD.
        It contains the Telemetry B timer functions that utilize a 20ms
        timebase.

ARGS:
    None
RETURNS:
    None.
********************************************************************/
#pragma CODE_SECTION(tbm_PRD, ".tbmExtCode")
void tbm_PRD (void) {
    if (tbv_active)
    {
        tbm_hsTimerExp();
        tbm_updateTimers();
    }
}






