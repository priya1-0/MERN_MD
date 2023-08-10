/************************************************************************
*
* MODULE: dbg_TelemB.c
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
* DESCRIPTION: This file implements Telemetry B debug port functionality.
*
*************************************************************************/

// Project specific includes
#include "global.h"
#include "tbm_rcv.h"
#include "tbm_main.h"
#include "tbm_handler.h"
#include "bsm_led.h"
#include "bsm_SwitchInput.h"
#include "bsm_SerialPort.h"
#include "aim_tlmb.h"

#include <string.h>
#include <stdlib.h>

#define DEFINED_HERE
#include "dbg_TelemB.h"
#undef DEFINED_HERE

#include <csl.h>
#include <csl_gpio.h>

// Programmer ID value to be used in these Telemetry B Debug functions.
// This is NOT the define used for the application code.
#define DBG_PRGMR_ID (0x0001)


// Item Map defines
#define InitializeMapperInput() _GPIO_IODIR &= ~GPIO_PIN4
#define MapInputHigh()          (_GPIO_IODATA & GPIO_PIN4) ? TRUE : FALSE

// Item Map Data
UINT16              goodItemCnt;
UINT16              badItemCnt;
tbt_autoIDRespType  dbg_autoIDResp;
tbt_devIdEntry      dbg_TargetID;
USHORT              dbg_respLength;
BYTE                dbg_DownlinkMsg[0x0100];
tbt_uplinksReqEntry dbg_uplinksReqInfo;
tbt_appDataReqEntry dbg_appDataReqInfo;
BYTE                dbg_UplinksResp[0x2000];
BYTE                dbg_AppDataResp[0x1800];

// Item Map Functions.
static tbt_reqStatus dbg_EGM(void);
static void dbg_AppData(void);
static UINT16 dbg_CRC16(BYTE * bptr, UINT32 bsize);
static BOOL dbg_autoID (BOOL printIDs);

/********************************************************************
FUNCTION: dbg_rcvTestFrame

DESCRIPTION: This function prepares the 2490G to receive to "test"
frame over the Telemetry B interface. This function is called from
the debug port, and is provided for functional test purposes. If a valid
frame is received within 2 seconds, the test passes. If not, it fails.

If a good packet is received before dbg_rcvTestFrameStatus is called,
then the goodFrame count will increment.

The required "test frame" is an invalid header uplink (0xff).
There is little processing in tbm_uplinkComplete and
tbm_uplinkStarted to circumvent.

ARGS:
    None
RETURNS:
    None.
********************************************************************/
void dbg_rcvTestFrame(char uplinkRate)
{
    static UINT16 frameCount1;
    GLB_LTMR_OBJ  rcvTimeout;

    tbm_init();

    if (uplinkRate == '8') {
        bsm_SDPrint("Uplink Data Rate: 87500");
        desiredUplinkRate =  tbc_dr_87;
    }
    else if (uplinkRate == '2') {
        bsm_SDPrint("Uplink Data Rate: 21875");
        desiredUplinkRate =  tbc_dr_21;
    }
    else {
        bsm_SDPrint("Invalid Uplink Data Rate");
        tbm_telemBDeactivate();
        return;
    }

    frameCount1              = 0;
    debugVars.uplinksUnknown = 0;     // Current frame count.

    tbm_startPacketRcv();                       // Start the receiver.

    // Wait up to 2 seconds for a valid uplinked frame.
    GLB_GET_LTMR(rcvTimeout);
    while(!GLB_HAS_LTMR_EXPIRED(rcvTimeout, 2000)) {

        // The test is expected to uplink an "unknown" frame
        if (debugVars.uplinksUnknown > frameCount1) {
            bsm_SDPrint("Telemetry B Receive: Passed.");
            tbm_disableRcv(TRUE);
            tbm_telemBDeactivate();
            return;
        }
    }

    // No frame received. Disable the receiver and send the status
    // response on the debug port.
    tbm_disableRcv(TRUE);
    bsm_SDPrint("Telemetry B Receive: Failed.");
    tbm_telemBDeactivate();
}
/********************************************************************
FUNCTION: dbg_rcvTestFrame

DESCRIPTION: This function prepares the 2490G to receive to "test"
frame over the Telemetry B interface. This function is called from
the debug port, and is provided for functional test purposes. If a valid
frame is received within 2 seconds, the test passes. If not, it fails.

If a good packet is received before dbg_rcvTestFrameStatus is called,
then the goodFrame count will increment.

The required "test frame" is an invalid header uplink (0xff).
There is little processing in tbm_uplinkComplete and
tbm_uplinkStarted to circumvent.

ARGS:
    None
RETURNS:
    None.
********************************************************************/

void dbg_rcvTestFrameLoop(char uplinkRate)
{
    static UINT16       frameCount2;
    GLB_LTMR_OBJ        rcvTimeout;
    int                 x;
    char                stdoutBuffer[50];
    bst_ToneSwitchState switch1, switch2;
    int                 setNum=0;

    tbm_init();

    if (uplinkRate == '8') {
        bsm_SDPrint("Uplink Data Rate: 87500");
        desiredUplinkRate =  tbc_dr_87;
    }
    else if (uplinkRate == '2') {
        bsm_SDPrint("Uplink Data Rate: 21875");
        desiredUplinkRate =  tbc_dr_21;
    }
    else {
        bsm_SDPrint("Invalid Uplink Data Rate");
        tbm_telemBDeactivate();
        return;
    }

    // read the tone/pulse switch position.
    switch1 = bsm_INReadTonePulse();

    while (1) {
        stdoutBuffer[0] = 0;
        strcat(stdoutBuffer, "Set Number: ");
        ltoa((long)++setNum, &stdoutBuffer[strlen(stdoutBuffer)]);
        bsm_SDPrint(stdoutBuffer);

        tbm_startPacketRcv();           // Start the receiver.
        GLB_HTMR_WAIT(20000);

        // This is needed to  re-enable the receiver after
        // receiving a frame.
        tbv_linkMaintainSession  = TRUE;

        frameCount2              = 0;
        debugVars.uplinksUnknown = 0;         // Current frame count.

        for (x=0; x<5000; ++x) {
            // Set the output to trigger the waveform generator.
            GLB_SET_XF;

            // Wait up to 20ms for a valid uplinked frame.
            GLB_GET_LTMR(rcvTimeout);
            while(!GLB_HAS_LTMR_EXPIRED(rcvTimeout, 20)) {

                // The test is expected to uplink an "unknown" frame
                if (debugVars.uplinksUnknown > frameCount2) {
                    frameCount2 = debugVars.uplinksUnknown;
                    break;
                }
            }

            GLB_CLR_XF;
            GLB_LTMR_WAIT(2);
        }

        tbm_disableRcv(TRUE);
        GLB_LTMR_WAIT(20);
        stdoutBuffer[0] = 0;
        strcat(stdoutBuffer, "Good Frames (out of 5000): ");
        ltoa((long)frameCount2, &stdoutBuffer[strlen(stdoutBuffer)]);
        bsm_SDPrint(stdoutBuffer);

        while ((switch2 = bsm_INReadTonePulse()) == switch1) ;
        switch1 = switch2;
    }
}

//***********************************************************************
static tbt_reqStatus dbg_EGM(void)
{
    tbt_reqStatus EGMStatus = tbc_successful;

    dbg_uplinksReqInfo.targetIDPtr         = (tbt_devIdEntry *) &dbg_TargetID;
    dbg_uplinksReqInfo.progID              = DBG_PRGMR_ID;
    dbg_uplinksReqInfo.configBPtr          = (tbt_configBTableType *) &aiv_7274ConfigBTable;
    dbg_uplinksReqInfo.respBufferPtr       = (BYTE *) &dbg_UplinksResp[0];
    dbg_uplinksReqInfo.respBufferSize      = 0x2000;
    dbg_uplinksReqInfo.bufferUsedLengthPtr = &dbg_respLength;
    dbg_uplinksReqInfo.uplinkListenTime    = 10000; /* milli seconds */

    EGMStatus                              = tbm_telemBUplinks((tbt_uplinksReqEntry *) &dbg_uplinksReqInfo);

    return EGMStatus;
}

/******************************************************
*******************************************************/
static void dbg_AppData(void)
{
    USHORT crcValue = 0;

#if DEBUG_TB_DL_MULTI_FRAME
    // This message is a downlink that is larger than 1 frame.
    // The purpose is to test PROG_INST FRAGMENT DOWNLINK MESSAGE ALGORITHM,
    // F bit functionality, and N(S) functionality.
    {
        int x,y=0;
        dbg_DownlinkMsg[y++] = 0xf0;
        dbg_DownlinkMsg[y++] = 37;
        for(x=0; x<36; ++x) {
            dbg_DownlinkMsg[y++] = 0x00;
            dbg_DownlinkMsg[y++] = 0x00;
            dbg_DownlinkMsg[y++] = 0x02;
            dbg_DownlinkMsg[y++] = 0x75 + x;
            dbg_DownlinkMsg[y++] = 0x00;
            dbg_DownlinkMsg[y++] = 0x01;
        }

        crcValue                         = dbg_CRC16(&dbg_DownlinkMsg[1], y-1);
        dbg_DownlinkMsg[y++]             = ((crcValue & 0xff00) >> 8);
        dbg_DownlinkMsg[y++]             = crcValue & 0x00ff;

        dbg_appDataReqInfo.appDataReqLen = y;
    }

#elif DEBUG_TB_MAX_DL
    // This message is a downlink with an I-Field size of 25, which is the
    // max I-Field size of a downlink.
    dbg_DownlinkMsg[0] = 0xf0;
    dbg_DownlinkMsg[1] = 0x02;

    dbg_DownlinkMsg[2] = 0x80;                  //Memory Write Long

    dbg_DownlinkMsg[3] = 0x00;
    dbg_DownlinkMsg[4] = 0x00;
    dbg_DownlinkMsg[5] = 0x00;                  //Address == 0

    dbg_DownlinkMsg[6] = 0x00;
    dbg_DownlinkMsg[7] = 15;                    // 15 bytes

    memset(&dbg_DownlinkMsg[8], 0, 15); //Values to write

    crcValue                         = dbg_CRC16(&dbg_DownlinkMsg[1], 22);
    dbg_DownlinkMsg[23]              = ((crcValue & 0xff00) >> 8);
    dbg_DownlinkMsg[24]              = crcValue & 0x00ff;

    dbg_appDataReqInfo.appDataReqLen = 25;

#elif DEBUG_TB_MAX_UL
    // This message is a downlink that requests an uplink with an
    // I-Field size of 256, which is the max I-Field size for an uplink.
    dbg_DownlinkMsg[0]               = 0xf0;
    dbg_DownlinkMsg[1]               = 0x02;
    dbg_DownlinkMsg[2]               = 0x00;
    dbg_DownlinkMsg[3]               = 0x00;
    dbg_DownlinkMsg[4]               = 0x02;
    dbg_DownlinkMsg[5]               = 0x75;
    dbg_DownlinkMsg[6]               = 0x00;
    dbg_DownlinkMsg[7]               = 0xDB; // Read 0xDB == 219 bytes + 5 overhead = 224.

    crcValue                         = dbg_CRC16(&dbg_DownlinkMsg[1], 7);
    dbg_DownlinkMsg[8]               = ((crcValue & 0xff00) >> 8);
    dbg_DownlinkMsg[9]               = crcValue & 0x00ff;

    dbg_appDataReqInfo.appDataReqLen = 10;

#elif DEBUG_TB_UL_MULTI_FRAME
    // This message generates an uplink that is larger than 1 frame.
    // The purpose is to test PROG_INST ASSEMBLE UPLINK MESSAGE ALGORITHM,
    // DEVICE PROG_INST COMMAND CODE IN UPLINK FRAMES, F bit functionality,
    // and N(S) functionality.
    dbg_DownlinkMsg[0]               = 0xf0;
    dbg_DownlinkMsg[1]               = 0x02;
    dbg_DownlinkMsg[2]               = 0x00;
    dbg_DownlinkMsg[3]               = 0x00;
    dbg_DownlinkMsg[4]               = 0x02;
    dbg_DownlinkMsg[5]               = 0x75;
    dbg_DownlinkMsg[6]               = 0x08;
    dbg_DownlinkMsg[7]               = 0x34; // Read 0x834 == 2100 bytes; 9 frames required.

    crcValue                         = dbg_CRC16(&dbg_DownlinkMsg[1], 7);
    dbg_DownlinkMsg[8]               = ((crcValue & 0xff00) >> 8);
    dbg_DownlinkMsg[9]               = crcValue & 0x00ff;

    dbg_appDataReqInfo.appDataReqLen = 10;

#elif DEBUG_TB_SUSPEND_DETECTION
    // Message to send a 'suspend detection' message to the Marquis. The
    // Marquis will respond with a 'receive ready' message. The purpose is
    // to test DEVICE PROG_INST RECEIVE READY MESSAGE DEFINITION.
    dbg_DownlinkMsg[0]               = 0xf0;
    dbg_DownlinkMsg[1]               = 0x02;
    dbg_DownlinkMsg[2]               = 0xa2;
    dbg_DownlinkMsg[3]               = 0x09; // 0x08=suspend detection, 0x09=resume detection
    crcValue                         = dbg_CRC16(&dbg_DownlinkMsg[1], 3);

    dbg_DownlinkMsg[4]               = ((crcValue & 0xff00) >> 8);
    dbg_DownlinkMsg[5]               = crcValue & 0x00ff;

    dbg_appDataReqInfo.appDataReqLen = 6;

#else
    // app data device read  of 256 bytes
    dbg_DownlinkMsg[0]                     = 0xf0; // Command Code
    dbg_DownlinkMsg[1]                     = 0x02; // Number of records including this Start-Of-Message
    dbg_DownlinkMsg[2]                     = 0x00; // Record #2 - Command Code for Memory Read Long
    dbg_DownlinkMsg[3]                     = 0x08; // Address - High Byte
    dbg_DownlinkMsg[4]                     = 0x80; // Address - Medium Byte
    dbg_DownlinkMsg[5]                     = 0x00; // Address - Low Byte
    dbg_DownlinkMsg[6]                     = 0x01; // # bytes to read (high-byte)
    dbg_DownlinkMsg[7]                     = 0x00; // # bytes to read (low-byte)

    crcValue                               = dbg_CRC16(&dbg_DownlinkMsg[1], 7);
    dbg_DownlinkMsg[8]                     = ((crcValue & 0xff00) >> 8);
    dbg_DownlinkMsg[9]                     = crcValue & 0x00ff;

    dbg_appDataReqInfo.appDataReqLen       = 10;
#endif

    dbg_appDataReqInfo.targetIDPtr         = (tbt_devIdEntry *) &dbg_TargetID;
    dbg_appDataReqInfo.progID              = DBG_PRGMR_ID;
    dbg_appDataReqInfo.configBPtr          = (tbt_configBTableType *) &aiv_7274ConfigBTable;
    dbg_appDataReqInfo.respBufferPtr       = (BYTE *) &dbg_AppDataResp[0];
    dbg_appDataReqInfo.respBufferSize      = 0x1800;
    dbg_appDataReqInfo.bufferUsedLengthPtr = &dbg_respLength;
    dbg_appDataReqInfo.appDataReqPtr       = (BYTE *)&dbg_DownlinkMsg[0];

    dbg_appDataReqInfo.firstULRespTime     = 1000;

    // Write the device model and sub-model to the config table.
    aiv_7274ConfigBTable.modelID           = (dbg_TargetID.modelIDHigh << 8) | (dbg_TargetID.modelIDLow);
    aiv_7274ConfigBTable.subModelID        = dbg_TargetID.subModelID;

}

//***********************************************************************
static UINT16 dbg_CRC16(BYTE * buffer, UINT32 size)
{
    UINT16 CRCVal = 0xffff; /* Initialize CRC value */
    UINT16 j, tmp, newcrc;

    for (j=0; j<size; j++)
    {
        tmp    = CRCVal ^ ((UINT16) buffer[j] & 0xff);

        newcrc = ((((tmp << 12) & 0xf000) | ((tmp >> 4) & 0x000f)) ^
                  ((((tmp << 8) & 0xff00) | ((tmp >> 8) & 0x00ff)) ^
                   (((tmp << 7) & 0x0780) ^
                    (((tmp) & 0x000f) ^ ((tmp << 3) & 0x07f8)))));
        CRCVal = newcrc & 0x0ffff;  /* Mask so it is only 16 bytes */
    }
    return (CRCVal);
}


/********************************************************************
FUNCTION: dbg_itemTestApp

DESCRIPTION: This function performs the item mapping function. This
        function also contains the trigger input functionality. Once,
        entered, this function will never exit!!

        NOTE:
    The TonePulseSwitch=Pulse causes this code to free-run and
    not check or wait for input from Item Mapper.
    The TonePulseSwitch=Tone causes this code to wait on the
    Item Mapper for a trigger to run the test.

    If at any time the modem LEDs are turned on there is a
    telemetry problem.
    Modem LED #1 (bsc_LEDDATA1) -> tbc_telemetry_abuse
    Modem LED #2 (bas_LEDDATA2) -> tbc_fail
    See tbt_handler.h for a description of these errors.

ARGS:
    None
RETURNS:
    None.
********************************************************************/
void dbg_itemTestApp(char testType)
{
    BOOL          init    = TRUE;
    unsigned int  counter = 0;
    tbt_reqStatus telemStatus;

    InitializeMapperInput();

    goodItemCnt = 0;
    badItemCnt  = 0;

    // Stay in this loop infinitely.
    while(1) {
        // Strobe the lights to show this is running.
        // Turn on next led in progress meter
        if ((counter % 5) == 0)
            bsm_LDChange(bsc_LEDPROGRESS1, bsc_LEDON);
        else if ((counter % 5) == 1)
            bsm_LDChange(bsc_LEDPROGRESS2, bsc_LEDON);
        else if ((counter % 5) == 2)
            bsm_LDChange(bsc_LEDPROGRESS3, bsc_LEDON);
        else if ((counter % 5) == 3)
            bsm_LDChange(bsc_LEDPROGRESS4, bsc_LEDON);
        else if ((counter % 5) == 4)
            bsm_LDChange(bsc_LEDPROGRESS5, bsc_LEDON);

        // If the monitor is configured for TONE dialing
        // run the item map using the item mapper.
        if (bsm_INReadTonePulse() == bsc_TONE)
        {
            // wait, until input trigger goes low from item mapper
            while(MapInputHigh()) {
                NU_Sleep(10);              // sleep for 100 msec.
            }
            // check to see if input signal from mapper is still low
            if (!MapInputHigh()) {
                telemStatus = dbg_itemTest(init, testType);
                if (telemStatus == tbc_successful)
                    init = FALSE;

                // Let's see if we are getting any abuses.
                if (telemStatus == tbc_telemetry_abuse)
                {
                    bsm_LDChange(bsc_LEDDATA1, bsc_LEDON);
                }
                if (telemStatus == tbc_fail)
                {
                    bsm_LDChange(bsc_LEDDATA2, bsc_LEDON);
                }

                // Wait until input signal goes high before
                // continuing with next map.
                while(!MapInputHigh()) {
                    NU_Sleep(10);
                }
            }        /* end of if-do-map */
        }         /* end of if bsc_TONE */

        // The item mapper is configured for PULSE
        // free-run the item mapper and do not wait on input.
        else
        {
            // delay for the user to see the status/change.
            NU_Sleep(100);

            telemStatus = dbg_itemTest(init, testType);
            if (telemStatus == tbc_successful)
                init = FALSE;

            // Let's see if we are getting any abuses.
            if (telemStatus == tbc_telemetry_abuse)
            {
                bsm_LDChange(bsc_LEDDATA1, bsc_LEDON);
            }
            if (telemStatus == tbc_fail)
            {
                bsm_LDChange(bsc_LEDDATA2, bsc_LEDON);
            }

            // delay for the user to see the status/change.
            NU_Sleep(100);

        } /* end of if bsc_PULSE */

        // use LEDs to indicate test is running, turn off
        // current led in progress meter
        if ((counter % 5) == 0)
            bsm_LDChange(bsc_LEDPROGRESS1, bsc_LEDOFF);
        else if ((counter % 5) == 1)
            bsm_LDChange(bsc_LEDPROGRESS2, bsc_LEDOFF);
        else if ((counter % 5) == 2)
            bsm_LDChange(bsc_LEDPROGRESS3, bsc_LEDOFF);
        else if ((counter % 5) == 3)
            bsm_LDChange(bsc_LEDPROGRESS4, bsc_LEDOFF);
        else if ((counter % 5) == 4)
            bsm_LDChange(bsc_LEDPROGRESS5, bsc_LEDOFF);

        // increase counter used to control which led is on
        counter++;
        if (counter > 65000)
            counter = 0;

    }     /* end of while-statement */
}

/********************************************************************
FUNCTION: dbg_itemTestSingle

DESCRIPTION: This function performs a single cycle of the item mapping
        function.

ARGS:
    char testType - 'E' egm capture, 'U' data uplinks
RETURNS:
    None.
********************************************************************/
void dbg_itemTestSingle (char testType)
{
    goodItemCnt = 0;
    badItemCnt  = 0;
    dbg_itemTest (TRUE, testType);
    tbm_telemBDeactivate();

}

/********************************************************************
FUNCTION: dbg_itemTestCount

DESCRIPTION: This function performs 100 cycles of the item mapping
        function.

ARGS:
    char testType - 'L' - low data rate , 'H' high data rate
RETURNS:
    None.
********************************************************************/
void dbg_itemTestCount (char testType, char *testCount)
{
    int  x, y, goodCount=0;
    char stdoutBuffer[50];
    long tcount;
    if( testCount[0] < '0' || testCount[0] > '9' )
    {
        bsm_SDPrint("2nd parameter is test count: 1 - 50000");
        return;
    }

    // convert the parameter to a number
    tcount = atol(testCount);

    if (tcount < 1 || tcount > 50000) {
        bsm_SDPrint("Test count min is 1, max is 50000");
        return;
    }

    (void)tbm_telemBInitialize();

    if (testType == 'L') {
        bsm_SDPrint("Low Data Rate Mapping...");
        for (x=0; x<tcount; ++x) {
            if (dbg_autoID(FALSE)) {
                ++goodCount;
            }
            stdoutBuffer[0] = 0;
            strcat(stdoutBuffer, "Frames Completed: ");
            ltoa((long)(x+1), &stdoutBuffer[strlen(stdoutBuffer)]);
            bsm_SDPrint(stdoutBuffer);
        }

        stdoutBuffer[0] = 0;
        strcat(stdoutBuffer, "Low Data Rate Mapping Pass Count: ");
        ltoa((long)goodCount, &stdoutBuffer[strlen(stdoutBuffer)]);
        bsm_SDPrint(stdoutBuffer);
        tbm_telemBDeactivate();
    }
    else if (testType == 'H') {
        bsm_SDPrint("High Data Rate Mapping...");
        dbg_autoID(TRUE);
        dbg_AppData();
        for (x=0; x<tcount; ++x) {
            if (tbm_telemBData((tbt_appDataReqEntry *)&dbg_appDataReqInfo)
                == tbc_successful) {
                ++goodCount;
            }
            if(x%10 == 9) {
                stdoutBuffer[0] = 0;
                strcat(stdoutBuffer, "Count: ");
                ltoa((long)(x+1), &stdoutBuffer[strlen(stdoutBuffer)]);
                bsm_SDPrint(stdoutBuffer);
            }
        }

        stdoutBuffer[0] = 0;
        strcat(stdoutBuffer, "High Data Rate Mapping Pass Count: ");
        ltoa((long)goodCount, &stdoutBuffer[strlen(stdoutBuffer)]);
        bsm_SDPrint(stdoutBuffer);

        GLB_LTMR_WAIT(100);
        tbm_telemBClose();

        tbm_telemBDeactivate();
    }
    else {
        bsm_SDPrint("Mapping: No Valid Type Specified.");
    }
}

/********************************************************************
FUNCTION: dbg_autoID

DESCRIPTION: This function performs the auto-ID function for
        debug functions.

ARGS:
    BOOL printIDs - if TRUE prints IDs of found devices to debug port.
RETURNS:
    BOOL - TRUE if any devices were successfully ID'ed.
*******************************************************************/
static BOOL dbg_autoID (BOOL printIDs)
{
    int            x;
    char           stdoutBuffer[30];
    tbt_devIdEntry *deviceIDPtr;
    long           sn;

    // Auto ID the device
    // It's assumed only one Telemetry B device will be auto id'd.
    (void)tbm_telemBAutoID((tbt_autoIDRespType *) &dbg_autoIDResp, DBG_PRGMR_ID);
    if(dbg_autoIDResp.numberFound > 0)
    {
        for (x=0; x<dbg_autoIDResp.numberFound; ++x) {

            deviceIDPtr                   = (tbt_devIdEntry *) &dbg_autoIDResp.response[x];
            /* Copy device id into downlink request. */
            dbg_TargetID.modelIDHigh      = deviceIDPtr->modelIDHigh;
            dbg_TargetID.modelIDLow       = deviceIDPtr->modelIDLow;
            dbg_TargetID.subModelID       = deviceIDPtr->subModelID;
            dbg_TargetID.serialNumberHigh = deviceIDPtr->serialNumberHigh;
            dbg_TargetID.serialNumberMed  = deviceIDPtr->serialNumberMed;
            dbg_TargetID.serialNumberLow  = deviceIDPtr->serialNumberLow;

            sn                            = (long)dbg_TargetID.serialNumberLow;
            sn                           += (long)(dbg_TargetID.serialNumberMed << 8);
            sn                           += (((long)dbg_TargetID.serialNumberHigh & 0xf) << 16);

            if (printIDs) {
                stdoutBuffer[0] = 0;
                strcat(stdoutBuffer, "ID Successful: SN ");
                ltoa(sn, &stdoutBuffer[strlen(stdoutBuffer)]);
                bsm_SDPrint(stdoutBuffer);
            }
        }
        return TRUE;
    }
    else {
        return FALSE;
    }
}


/********************************************************************
FUNCTION: dbg_itemTest

DESCRIPTION: This function performs the item mapping function. This
        function does not, however, contain the trigger input functionality.
        That is contained in a higher level function. This allows this
        function to be "triggered" through alternate means, such as
        through the debug port.

ARGS:
    None
RETURNS:
    None.
********************************************************************/
tbt_reqStatus dbg_itemTest (BOOL init, char testType)
{
    char          stdoutBuffer[60]; // send information to debug port
    tbt_reqStatus retStatus;
    static BOOL   AutoIDOK;

#ifdef TURNAROUND_TIME_TEST
        #warn "Telemetry B Turnaround Time Testing Enabled"
    // Configure GPIO4 as a debug output for this test.
    _GPIO_IODIR  |= GPIO_PIN4;
    // Set the output
    _GPIO_IODATA |= GPIO_PIN4;
#endif

    // pull output signal low in preparation for next mapping request
    // This line was removed since it is confusing to the person running
    // the test and the original developer said it was not needed.
    // bsm_LDChange(bsc_LEDBADANTENNA, bsc_LEDON);

    // Auto ID if necessary.
    if (init)
    {
        (void)tbm_telemBInitialize();

        if (dbg_autoID(TRUE)) {
            AutoIDOK = TRUE;
            // From the original ITEM Mapper code setup the request.
            dbg_AppData();
        }
        else {
            AutoIDOK = FALSE;
        }
    }     /* end of auto-id logic */

    // If a successful Auto ID was completed then perform a
    // standard Telemetry B downlink/uplink.
    if (AutoIDOK)
    {
        if (testType == 'E') {
            bsm_SDPrint("Mapping: EGM Capture");
            retStatus = dbg_EGM();
        }
        else if (testType == 'U') {
            bsm_SDPrint("Mapping: Data Uplinks");
            retStatus = tbm_telemBData((tbt_appDataReqEntry *)&dbg_appDataReqInfo);
        }
        else {
            bsm_SDPrint("Mapping: No Valid Type Specified.");
            return;
        }

        // If a successful downlink/uplink was done then
        // signal to ITEM Mapper.
        if (retStatus == tbc_successful)
        {
            // pull output signal high to indicate successful to
            // ITEM Mapping System
            bsm_LDChange(bsc_LEDBADANTENNA, bsc_LEDOFF);
            ++goodItemCnt;
            stdoutBuffer[0] = 0;
            strcat(stdoutBuffer, "Mapping: Successful: ");
            ltoa((long)goodItemCnt, &stdoutBuffer[strlen(stdoutBuffer)]);
            strcat(stdoutBuffer, ", Failed: ");
            ltoa((long)badItemCnt, &stdoutBuffer[strlen(stdoutBuffer)]);
            bsm_SDPrint(stdoutBuffer);
        }
        // If an unsuccessful downlink/uplink was done then
        // signal to ITEM Mapper.
        else
        {
            // pull output signal low to indicate failure to
            // ITEM Mapping System
            bsm_LDChange(bsc_LEDBADANTENNA, bsc_LEDON);
            ++badItemCnt;
            stdoutBuffer[0] = 0;
            strcat(stdoutBuffer, "Mapping: Failure: ");
            ltoa((long)badItemCnt, &stdoutBuffer[strlen(stdoutBuffer)]);
            bsm_SDPrint(stdoutBuffer);
        }

        GLB_LTMR_WAIT(100);
        tbm_telemBClose();
    }
    else
    {
        // pull output signal low to indicate failure to
        // ITEM Mapping System
        bsm_LDChange(bsc_LEDBADANTENNA, bsc_LEDON);
        ++badItemCnt;
        bsm_SDPrint("Mapping: Failure: AutoID");
        retStatus = tbc_not_successful;
    }

    return (retStatus);
}





