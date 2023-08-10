/************************************************************************
*
* MODULE: tbm_com_main.c
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This is main application for tbm test purposes.
*
*************************************************************************/

/////////////
// Includes
/////////////

#include "global.h"
#include "bsm_global.h"
#include "nwm_net.h"
#include "uim_ui.h"
#include "tbm_handler.h"
#include "tbm_events.h"
#include "tbm_timer.h"
#include "tbm_queue.h"

#ifdef DSP_2490_SIMULATION
  #include "device_sim.h"
#endif

#ifdef ITEM_TEST
  #include "tam_ItemMap.h"
#endif


#include <string.h>
#include <stdlib.h>
#include <csl_icache.h>
////////////
// Defines
////////////

// Watchdog timer
#define ENABLE_WATCHDOG()
#define DISABLE_WATCHDOG()

////////////
// Globals
////////////


////////////
// Externs
////////////
// These two external functions are supplied by the specific
// application being built.
extern bool aim_CheckForDevice(void);
extern int aim_Interrogate(void);


extern void tbm_init(void);

extern void tbm_testEvents1(void);
extern void tbm_testEvents2(void);

extern void tbm_testQueue1(void);
extern void tbm_testQueue2(void);

extern void tbm_testTimers1(void);
extern void tbm_testTimers2(void);
extern void tbm_testTimers3(void);
extern void tbm_testTimers4(void);
extern void tbm_testTimers5(void);
extern void tbm_testTimers6(void);
extern void tbm_testTimers7(void);
extern void tbm_testTimers8(void);

////////////////////////////////////////////////////////////////////////////////
//
//  main
//
////////////////////////////////////////////////////////////////////////////////
void main()
{
    // The following 2 assembly lines correct a "bug" in DSP/BIOS.
    // The value of GBL_initdone is hard coded in a code section.  This
    // is burned into the Flash.  Once all the initialization is done,
    // this variable is set to 1.  But when we check the Flash against the
    // RAM, this becomes an error because it looks like a byte of execution code
    // changed.  We reset the variable back to a 0.
    asm ("	.ref GBL_initdone");
    asm ("	*(#GBL_initdone) = #0");

    ICACHE_enable();

    // Turn off the CLKOUT
    _CHIP_CLKOSR_SET(0);

    //Allow modem to make backup of initiailized section of DARAM
    mdm_Store_Data();

    bsm_initDAA();       //init of DAA
    bsm_LedInit();
    bsm_PowerInit();
    bsm_ToneInit();
    bsm_SDInit();
    bsm_INInit();
}

#ifdef TB_EMC_TEST
#warn "Build for Telemetry B EMC Testing."
////////////////////////////////////////////////////////////////////////////////
//
//  com_MainTask - for continuous Telemetry B looping for EMC testing.
//	Not for production code use!!
//
////////////////////////////////////////////////////////////////////////////////
void com_MainTask()
{
    char       stdoutBuffer[50];
    static int setNum=0;

    bst_POSTERR postError;

    // Enable the watchdog timer
    ENABLE_WATCHDOG();

    bsm_EEInit();

    // check all the hardware
    postError = bsm_CheckHardware();

    // if the battery voltage failed...
    if (postError == bsc_POST_VOLTS_FAILED)
    {
        bsm_PMEnableButton();
        uim_BatteryWarning();
        GLB_LTMR_WAIT(120000);
        bsm_PMShutDown();
    }

    // if there were any other errors, just fail and shutdown
    if (postError != bsc_POST_OK)
    {
        uim_ErrorTone();
        bsm_EHLock("POST Failed.");
    }

    uim_DisplayReady();

    // Enable the start button shutdown feature
    bsm_PMEnableButton();

    // Turn on the green LED above the start button.
    uim_DisplayReady();

    while(1) {
        // AutoId Device and send resume command immediately.
        aim_CheckForDevice();

        // Interrogate the device
        if (!aim_Interrogate())
        {
            bsm_EHLock("Device Interrogation failed");
        }

        tbm_telemBDeactivate();

        stdoutBuffer[0] = 0;
        strcat(stdoutBuffer, "Set Number: ");
        ltoa((long)++setNum, &stdoutBuffer[strlen(stdoutBuffer)]);
        bsm_SDPrint(stdoutBuffer);

    }
}
#endif

#ifdef TBM_UNIT_TEST
#warn "Build for Telemetry B Unit Testing."
////////////////////////////////////////////////////////////////////////////////
//
//  com_MainTask - to execute various unit test functions. Not for production
//  code use!!
////////////////////////////////////////////////////////////////////////////////
void com_MainTask()
{
    // needed to allow event logging to not fail.
    bsm_EEInit();

    // TBM unit test functions!!
    tbm_init();

    // Event tests.
    //tbm_testEvents1();
    tbm_testEvents2();

    // Queue tests.
    //tbm_testQueue1();
    tbm_testQueue2();

    // Timer tests1. Only include one at a time.
    //tbm_testTimers1();
    //tbm_testTimers2();
    //tbm_testTimers3();
    //tbm_testTimers4();
    //tbm_testTimers5();
    //tbm_testTimers6();
    //tbm_testTimers7();
    tbm_testTimers8();

    // loop indefinitely
    while(1) {; }
}

/********************************************************************

FUNCTION:
  tbm_testEvents

DESCRIPTION:
  This function is used to test the Event functionality. It serves
  no purpose for real application usage. The results of this test
  must be inspected using the emulator.

INPUT DATA:
  none

OUTPUT RESULTS:
  none

********************************************************************/
void tbm_testEvents1()
{
    tbm_initializeEvents();

    tbm_postEvent((eventPtrType)(0x1000));
    tbm_postEvent((eventPtrType)(0x2000));
    tbm_postEvent((eventPtrType)(0x3000));
    tbm_postEvent((eventPtrType)(0x4000));
    tbm_postEvent((eventPtrType)(0x5000));
    tbm_postEvent((eventPtrType)(0x6000));
    tbm_postEvent((eventPtrType)(0x7000));
    tbm_postEvent((eventPtrType)(0x8000));
    tbm_postEvent((eventPtrType)(0x9000));
    tbm_postEvent((eventPtrType)(0xa000));
    tbm_postEvent((eventPtrType)(0xb000));
}
void tbm_testEvents2()
{
    int          x;
    eventPtrType temp[14];

    tbm_initializeEvents();

    temp[0] = tbm_getEvent();

    tbm_postEvent((eventPtrType)(0x1000));
    tbm_postEvent((eventPtrType)(0x2000));
    tbm_postEvent((eventPtrType)(0x3000));
    tbm_postEvent((eventPtrType)(0x4000));
    tbm_postEvent((eventPtrType)(0x5000));
    tbm_postEvent((eventPtrType)(0x6000));
    tbm_postEvent((eventPtrType)(0x7000));
    tbm_postEvent((eventPtrType)(0x8000));
    tbm_postEvent((eventPtrType)(0x9000));
    tbm_postEvent((eventPtrType)(0xa000));

    for (x=1; x<12; ++x) {
        temp[x] = tbm_getEvent();
    }

    tbm_postEvent((eventPtrType)(0xf000));
    tbm_postEvent((eventPtrType)(0xc000));

    temp[12] = tbm_getEvent();
    temp[13] = tbm_getEvent();
}

/********************************************************************
FUNCTION: tbm_testQueue()

DESCRIPTION:
    This function test the Telemetry B queues functionality.
    It serves no purpose for real application usage. The results
    of these tests must be inspected using the emulator.

ARGS:
    <none>

RETURNS:
    <none>
********************************************************************/
#include "tbt_channel.h"
#include "tbm_trx.h"
int temp[17] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
};
void tbm_testQueue1 (void)
{
    int x;

    tbm_initializeQueue((TBC_DL_FRAME_Q_SIZE), &tbv_dlFrameQ);

    for (x=0; x<15; ++x) {
        tbm_enqueueEntry(&tbv_dlFrameQ, (void *)&temp[x]);
    }
    tbm_enqueueEntry(&tbv_dlFrameQ, (void *)&temp[15]);
}

void tbm_testQueue2 (void)
{
    int *temp2[20], x;
    tbm_initializeQueue((TBC_DL_FRAME_Q_SIZE), &tbv_dlFrameQ);

    for (x=0; x<15; ++x) {
        tbm_enqueueEntry(&tbv_dlFrameQ, (void *)&temp[x]);
    }

    tbm_clearQueue(&tbv_dlFrameQ);
    temp2[0] = tbm_getQueueEntry(&tbv_dlFrameQ);

    for (x=0; x<15; ++x) {
        tbm_enqueueEntry(&tbv_dlFrameQ, (void *)&temp[x]);
    }

    tbm_dequeueAllEntries(&tbv_dlFrameQ);
    temp2[1] = tbm_getQueueEntry(&tbv_dlFrameQ);

    for (x=0; x<15; ++x) {
        tbm_enqueueEntry(&tbv_dlFrameQ, (void *)&temp[x]);
    }

    temp2[2] = tbm_getQueueEntry(&tbv_dlFrameQ);
    temp2[3] = tbm_getQueueEntry(&tbv_dlFrameQ);
    tbm_dequeueEntry(&tbv_dlFrameQ);

    for (x=0; x<16; ++x) {
        temp2[x+4] = tbm_getQueueEntry(&tbv_dlFrameQ);
        tbm_dequeueEntry(&tbv_dlFrameQ);
    }
}

/********************************************************************
FUNCTION: testFunc(), tbm_testTimers1 - 7()

DESCRIPTION:
    These functions test the Telemetry B timers functionality.
    They serve no purpose for real application usage. The results
    of these tests must be inspected using the emulator and
    oscilloscope.

ARGS:
    <none>

RETURNS:
    <none>
********************************************************************/
static int tbm_tmr_status;
void testFunc(void) {
    tbm_tmr_status ^= 1;
    if (tbm_tmr_status) {
        _GPIO_IODATA |= GPIO_PIN4;
    }
    else {
        _GPIO_IODATA &= ~GPIO_PIN4;
    }
}

void testFuncInit(void) {
    // Configure GPIO4 as a debug output for this test.
    _GPIO_IODIR  |= GPIO_PIN4;
    // Output pattern to observe.
    _GPIO_IODATA |= GPIO_PIN4;
    GLB_LTMR_WAIT(2);
    _GPIO_IODATA &= ~GPIO_PIN4;
    GLB_LTMR_WAIT(2);
    _GPIO_IODATA |= GPIO_PIN4;

    tbm_initializeEvents();
    tbm_initTimers();
    tbm_tmr_status = 1;
}

void tbm_testTimers1()
{
    testFuncInit();

    // call 'test func' on 2 sec. expiration; one-shot.
    tbm_addTimer(testFunc, reserved1, 100, 0);

    tbm_eventProcessor();
}

void tbm_testTimers2()
{
    testFuncInit();

    // call 'test func' on 2 sec. expiration; one-shot.
    tbm_addTimer(testFunc, reserved1, 100, 0);

    // cancel a timer that has not been created to make
    // sure that this is handled OK.
    tbm_cancelTimer(tbc_HSTimer);

    // cancel after 1.5 seconds.
    GLB_LTMR_WAIT(1500);

    tbm_cancelTimer(reserved1);

    tbm_eventProcessor();
}

//call 'test func' on 100ms period; auto-reload.
void tbm_testTimers3()
{
    testFuncInit();

    tbm_addTimer(testFunc, reserved1, 5, 5);

    tbm_eventProcessor();
}

// One-shot timers. First toggle occurs in 100ms, next in 120ms, etc.
// up to 240ms for the last one.
void tbm_testTimers4()
{
    testFuncInit();

    tbm_addTimer(testFunc, reserved1,           5,  0); // 1
    tbm_addTimer(testFunc, tbc_RxTimer,         6,  0); // 2
    tbm_addTimer(testFunc, tbc_TxTimer,         7,  0); // 3
    tbm_addTimer(testFunc, tbc_HSTimer,         8,  0); // 4
    tbm_addTimer(testFunc, tbc_STOTimer,        9,  0); // 5
    tbm_addTimer(testFunc, tbc_ledTimer,        10, 0); // 6
    tbm_addTimer(testFunc, tbc_EGMTimer,        11, 0); // 7
    tbm_addTimer(testFunc, reserved7,           12,     0);     // 8

    tbm_eventProcessor();
}

// Should result in tbc_ledTimer as the only one remaining.
// A 200ms toggle of the debug output should occur.
void tbm_testTimers5()
{
    testFuncInit();

    tbm_addTimer(testFunc, reserved1,           5,  0); // 1
    tbm_addTimer(testFunc, tbc_RxTimer,         6,  0); // 2
    tbm_addTimer(testFunc, tbc_TxTimer,         7,  0); // 3
    tbm_addTimer(testFunc, tbc_HSTimer,         8,  0); // 4
    tbm_addTimer(testFunc, tbc_STOTimer,        9,  0); // 5
    tbm_addTimer(testFunc, tbc_ledTimer,        10, 10); // 6
    tbm_addTimer(testFunc, tbc_EGMTimer,        11, 0); // 7
    tbm_addTimer(testFunc, reserved7,           12,     0);     // 8

    tbm_cancelTimer(reserved1);         // 1
    tbm_cancelTimer(tbc_RxTimer);       // 2
    tbm_cancelTimer(tbc_TxTimer);       // 3
    tbm_cancelTimer(tbc_HSTimer);       // 4
    tbm_cancelTimer(tbc_STOTimer);      // 5
    tbm_cancelTimer(tbc_EGMTimer);      // 7
    tbm_cancelTimer(reserved7);         // 8

    tbm_eventProcessor();
}

// Relative to 2ms toggles up front:
// (1) a reload of reserved1 60ms later.
// (2) a toggle from tbc_TxTimer at t+140ms.
// (3) a toggle from reserved1 at t+260ms.
// (4) repetition of 200ms toggle thereafter.
void tbm_testTimers6()
{
    testFuncInit();

    tbm_addTimer(tbm_reloadAllTimers, reserved7,        3,  0); // 60ms one-shot
    tbm_addTimer(testFunc,                      tbc_TxTimer,    7,  0); // 140ms one-shot
    tbm_addTimer(testFunc,                      reserved1,              10, 10); // 200ms reload

    tbm_eventProcessor();
}

// Relative to 2ms toggles up front:
// (1) a reload of reserved1 60ms later.
// (2) a toggle from tbc_TxTimer at t+140ms.
// (3) a toggle from reserved1 at t+260ms.
// (4) repetition of 200ms toggle thereafter.
void testFunc2(void) {
    tbm_reloadTimer(reserved1);                 // Should reload.
    tbm_reloadTimer(tbc_TxTimer);       // Shouldn't reload; it's a one-shot.
}
void testFunc3(void) {
    tbm_reloadTimer(tbc_RxTimer);       // Shouldn't reload; it's a one-shot.
}
void tbm_testTimers7()
{
    testFuncInit();

    tbm_addTimer(testFunc3, reserved7,          3,  0); // 60ms one-shot
    tbm_addTimer(testFunc2,     tbc_RxTimer,    5,  0); // 100ms one-shot
    tbm_addTimer(testFunc,      tbc_TxTimer,    7,  0); // 140ms one-shot
    tbm_addTimer(testFunc,      reserved1,              10, 10); // 200ms reload

    tbm_eventProcessor();
}

// 9th timer added should not work.
void tbm_testTimers8()
{
    testFuncInit();

    tbm_addTimer(testFunc, reserved1,           5,  0); // 1
    tbm_addTimer(testFunc, tbc_RxTimer,         6,  0); // 2
    tbm_addTimer(testFunc, tbc_TxTimer,         7,  0); // 3
    tbm_addTimer(testFunc, tbc_HSTimer,         8,  0); // 4
    tbm_addTimer(testFunc, tbc_STOTimer,        9,  0); // 5
    tbm_addTimer(testFunc, tbc_ledTimer,        10, 0); // 6
    tbm_addTimer(testFunc, tbc_EGMTimer,        11, 0); // 7
    tbm_addTimer(testFunc, reserved7,           12,     0);     // 8

    tbm_addTimer(testFunc, tbc_nullTimer,       13, 0); // 9 - shouldn't work
}
#endif

