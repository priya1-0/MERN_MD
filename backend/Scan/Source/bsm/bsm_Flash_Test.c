#include <log.h>
#include "..\2490Gcfg.h" //For LOG_printf(&trace ...
#include "bsm_Flash.h"
#include "bsm_Flash_Intel.h"
#include "bsm_Flash_SST.h"
#include "bsm_Led.h"
#include "bsm_Flash_test.h"
#include "bsm_NVStorage.h" //for extern of flashMirror
#include "bsm_SerialPort.h"
#include "stdio.h"
#include "csl_icache.h"
#include "MedtronicStubFunctions.h" //TBD - Stubs
#include "bsm_DAA.h"
#include "cx077.h"
#include "bsm_DebugOperations.h"


//extern BYTE *bsv_FLRAM;
//prototypes
int  doReadEntry(void);
void doResetFlashMirror(void);
BOOL doResetFlash(void);
BOOL NVTest(UINT16, UINT16, UINT16 Offset, BOOL Write);
BOOL wholeFlashTest(void);
BOOL eventLogSingle(void);
BOOL eventLogFull(void);
BOOL NVStorageSingle(void);
BOOL NVStorageFull(BOOL Mode);

void main(void){
    ICACHE_enable();

    bsm_initDAA();
    bsm_INInit();        //init of input switchss
    bsm_LedInit();       //init of the LEDs module
    bsm_ToneInit();      //init of the Tone module
    bsm_TNStop();        //ensure tone's are off
    bsm_PowerInit();     //init of the Power module
}


/****************************************************
 Test Main: Initiate the actual tests
*****************************************************/
void com_MainTask(void){
    BOOL   status;
    UINT16 i;
    char   str[64];

    GLB_LTMR_OBJ base1;
    GLB_LTMR_OBJ base2;
    GLB_LTMR_OBJ whole;
    GLB_LTMR_OBJ EH_Single;
    GLB_LTMR_OBJ EH_Full;
    GLB_LTMR_OBJ NVStorage_Single;
    GLB_LTMR_OBJ NVStorage_True;
    GLB_LTMR_OBJ NVStorage_False;

    /* Init */
    bsm_SDInit();        //init of the serial comm port
    bsm_EEInit();        //init the NVStorage/Flash, must be done after BIOS initializes

    // test the internal and external RAM
    if( !TestSdram() )
    {
        bsm_SDPrint("* SDRAM TEST FAILED *");
    }

    if( !TestInternalRam() )
    {
        bsm_SDPrint("* INTERNAL RAM TEST FAILED *");
    }


//	status = mdm_Init();
    status = MDM_ERRORCODE__NO_ERROR;
//	mdm_Shut_Off();  //disable to modem, this is the standard power up condition
    bsm_EHClearLog();    //***For testing only

    /* Turn on Modem LEDs*/
    //bsm_ModemProgression();
    bsm_LDChange(bsc_LEDDATA1, bsc_LEDSTROBE);

    bsm_SDPrint("Starting Flash test");

    GLB_LTMR_WAIT(1000);     //1 sec
//	GLB_HTMR_WAIT(0x3B9ACA00);//1 sec

    /* Turn on LED for progress for new test*/
    bsm_LDChange(bsc_LEDPROGRESS1, bsc_LEDFASTFLASH);

    /* Start test*/
    status = TRUE;
    GLB_GET_LTMR(base1);
    status = wholeFlashTest();    //Test the whole flash (~21.4 sec)SST (~27.2 sec)Intel
    GLB_GET_LTMR(base2);
    whole  = base2 - base1;
    GLB_LTMR_WAIT(1);    //wait 1 ms for event logs to get sent out



    if(status == TRUE) {
        /* Set LED Indicator for successful test*/
        bsm_LDChange(bsc_LEDPROGRESS1, bsc_LEDON);

        /* Turn on LED for progress for new test*/
        bsm_LDChange(bsc_LEDPROGRESS2, bsc_LEDFASTFLASH);

        /* Do Next Test*/
        GLB_GET_LTMR(base1);
//	    status = eventLogSingle();//Single event log test (~0.5 sec)SST (~14.7sec)Intel
        GLB_GET_LTMR(base2);
        EH_Single = base2 - base1;
    }
    else
    {   /* Error in test occured, show error led for this test*/
        bsm_LDChange(bsc_LEDPROGRESS1, bsc_LEDSLOWFLASH);
    }



    if(status == TRUE) {
        /* Set LED Indicator for successful test*/
        bsm_LDChange(bsc_LEDPROGRESS2, bsc_LEDON);

        /* Turn on LED for progress for new test*/
        bsm_LDChange(bsc_LEDPROGRESS3, bsc_LEDFASTFLASH);

        GLB_GET_LTMR(base1);
//      status = eventLogFull();//Full event log test (~1.3 sec)SST (~15.5sec)Intel
        GLB_GET_LTMR(base2);
        EH_Full = base2 - base1;
    }
    else
    {   /* Error in test occured, show error led for this test*/
        bsm_LDChange(bsc_LEDPROGRESS2, bsc_LEDSLOWFLASH);
    }



    if(status == TRUE) {
        GLB_GET_LTMR(base1);
//      status = NVStorageSingle();
        GLB_GET_LTMR(base2);
        NVStorage_Single = base2 - base1;
    }



    if(status == TRUE) { //fills NVstorage and reads out, no flush (~0.5 sec)SST (~14.8sec)Intel
        /* Set LED Indicator for successful test*/
        bsm_LDChange(bsc_LEDPROGRESS4, bsc_LEDON);

        /* Turn on LED for progress for new test*/
        bsm_LDChange(bsc_LEDPROGRESS5, bsc_LEDFASTFLASH);

        GLB_GET_LTMR(base1);
//        status = NVStorageFull(FALSE);//flushs what was wrote in Test 3, reads back and validates
        GLB_GET_LTMR(base2);
        NVStorage_False = base2 - base1;
    }
    else
    {   /* Error in test occured, show error led for this test*/
        bsm_LDChange(bsc_LEDPROGRESS4, bsc_LEDSLOWFLASH);
    }



    if(status == TRUE) { //fills NVstorage and reads out, no flush (~0.5 sec)SST (~14.8sec)Intel
        /* Set LED Indicator for successful test*/
        bsm_LDChange(bsc_LEDPROGRESS4, bsc_LEDON);

        /* Turn on LED for progress for new test*/
        bsm_LDChange(bsc_LEDPROGRESS5, bsc_LEDFASTFLASH);

        GLB_GET_LTMR(base1);
//        status = NVStorageFull(FALSE);//flushs what was wrote in Test 3, reads back and validates
        GLB_GET_LTMR(base2);
        NVStorage_False = base2 - base1;
    }
    else
    {   /* Error in test occured, show error led for this test*/
        bsm_LDChange(bsc_LEDPROGRESS4, bsc_LEDSLOWFLASH);
    }



    if(status == TRUE) {
        /* Set LED Indicator for successful test*/
        bsm_LDChange(bsc_LEDPROGRESS5, bsc_LEDON);

        bsm_SDPrint("ALL TESTS PASSED");
    }
    else
    {   /* Error in test occured, show error led for this test*/
        bsm_LDChange(bsc_LEDPROGRESS5, bsc_LEDSLOWFLASH);
    }

    i=0;
    while(i < 1000 && status == bsc_SST)
    {
        status = bsm_SST_ID();
        i++;
    }

    bsm_SDPrint("End of Tests");
    bsm_SDPrint("<echo character mode now enabled>\n");

    while(1) {
        // Return received serial port characters
        str[0] = bsm_SDRead();                 //try to get first character
        if(str[0] != (INT16)(-1) &&                 //check for error
           str[0] != (INT16)(-2))
        {
            int i;
            i = 0;

            while( i < sizeof(str)-1 &&                    //check if temp string filled or SDP error
                   str[i] != (INT16)(-1) &&
                   str[i] != (INT16)(-2)   )
            {
                i++;
                str[i] = bsm_SDRead();                        //try to get next char
            }

            if(str[i] != (INT16)(-1) &&                    //check for error
               str[i] != (INT16)(-2)   )
            {
                i++;                        //increment only if there was no error
            }
            str[i]=0;                     //terminate string
            bsm_SDWrite(str, i);
        }
        GLB_LTMR_WAIT(1);                 //wait 1ms
    }

}


/**********************************************************************
 Do Read Entry: Reads a event log entry and returns only the code field
***********************************************************************/
int doReadEntry(void){
    char          log[250]; //char array
    int           code;
    unsigned long timeStamp;

    //clear the string
    for(code = 0; code < 250; code++) {
        log[code] = 0;
    }

    if(bsm_EHReadNextEntry(log, &code, &timeStamp) != TRUE) {
        bsm_SDPrint("_.-~-._.-~READ FAILED~-._.-~-._");
    }
    return code;
}


/*******************************************************************
 Do Reset Flash Mirror: Clears out the flashMirror contents to zero
*******************************************************************/
void doResetFlashMirror(void){
    UINT32 i; //loop var

    for(i = 0; i< bsc_NVStorage_SIZE*2; i++) {
        *(UINT16*)((UINT32)&bsv_FLRAM+i) = 0x0000;
    }
}

/*******************************************************************
 Do Reset Flash: Erases entire flash chip
*******************************************************************/
BOOL doResetFlash(void){
    BOOL status;

    //Determine flash type
    status = bsm_Flash_Init();
    if(status == FALSE) {
        bsm_SDPrint("Flash_Init FAILED");
    }

    //Clear flash and flash mirror before start
    if(status == TRUE) {

        //Erase all blocks, unlock beforehand if neccessary
        switch(bsm_Flash_Get_Type()) {
        case bsc_INTEL:
            //We must unlock the block if it is Intel type flash
            status = bsm_Intel_UnlockALLBlocks();
            if(status == FALSE) {
                bsm_SDPrint("did not unlock INTEL flash");
            }
            else{
                status = bsm_Intel_Erase_CHIP();     //erase all blocks
                if(status == FALSE) {
                    bsm_SDPrint("did not erase INTEL flash");
                }
            }
            break;
        case bsc_SST:
            status = bsm_SST_Erase_CHIP();     //erase all blocks
            if(status == FALSE) {
                bsm_SDPrint("did not erase SST flash");
            }
            break;
        case bsc_Unknown:
        //break intentionally left out
        default:
            bsm_SDPrint("did not identify flash");
            status = FALSE;
            break;
        }
    }
    return status;
}

/*******************************************************************
 NVTest: Helper function for testing the NVStorage flashMirror. It
         has a persistenmt array 'temp' that is generated when a call
         to this function is made with Write = TRUE.

         Write - FALSE: This only does a read of the flashMirror and
         tests what it reads againts the array 'temp' that had to be
         initialized via a previous call the this function with
         Write=TRUE

         Write - TRUE: This generates data in the temp array and then
         writes this data out to the flashMirror. it then does the
         read test from when Write=FALSE.
*******************************************************************/
BOOL NVTest(UINT16 size, UINT16 addr, UINT16 offset, BOOL Write){
    BOOL        status;
    static BYTE temp[(UINT16)coc_AppScratchPad_SIZE];
    UINT16      a;
    UINT16      b;

    int i; //loop variable
    status = TRUE;

    if(Write == TRUE) {
        for(i = 0; i < size; i++) {
            temp[i] = (i + offset) & 0x00FF;
        }

        bsm_EEWriteBuf(temp, size, addr);
    }

    bsm_EEReadBuf(temp, size, addr);
    for(i = 0; i < size; i++) {
        a = temp[i] & 0x00FF;
        b = (i + offset) & 0x00FF;

        if( a != b) {
            status = FALSE;
        }
    }
    return status;
}





//****************************************************************
//**TESTS*********************************************************
//****************************************************************
//****************************************************************


/****************************************************
 Whole Flash: Test writing a pattern to entire Flash
*****************************************************/
BOOL wholeFlashTest(void){
    BOOL   status;
    UINT32 numWords; //used to know the number of words to write and read from flash
    UINT32 i;       //loop variable
    UINT16 temp;    //temp for writing and reading

    GLB_LTMR_OBJ base1;
    GLB_LTMR_OBJ base2;
    GLB_LTMR_OBJ deltaErase;
    GLB_LTMR_OBJ deltaWrite;
    GLB_LTMR_OBJ deltaRead;

    GLB_GET_LTMR(base1);
    status     = doResetFlash();
    GLB_GET_LTMR(base2);
    deltaErase = base2 - base1;

    //Write pattern out to Flash
    if(status == TRUE) {
        //Flash identified, unlocked if necessary, and erased
        switch(bsm_Flash_Get_Type()) {
        case bsc_INTEL:
            //Total number of words is determined
            numWords = (INTEL_BLCK_NUMBLOCKS * INTEL_BLCK_NUMWORDS) + ((UINT32)INTEL_SECT_NUMBLOCKS * (UINT32)INTEL_SECT_NUMWORDS);
            break;
        case bsc_SST:
            //Total number of words is determined
            numWords = (SST_BLCK_NUMBLOCKS * SST_BLCK_NUMWORDS) + ((UINT32)SST_SECT_NUMBLOCKS * (UINT32)SST_SECT_NUMWORDS);
            break;
        case bsc_Unknown:
        //break intentionally left out
        default:
            bsm_SDPrint("Whole Flash Test FAILED -- did not identify flash");
            status = FALSE;
            break;
        }

        if(status == TRUE) {
            //issue writes
            GLB_GET_LTMR(base1);
            for(i=0; i<numWords; i++) {
                temp   = (i & 0x0000FFFF);
                //do write, offset = i, value = temp, length = 1 word.
                status = bsm_Flash_Write_With_Packed(i, &temp, (UINT32)(1));
                if(status == FALSE) {
                    bsm_SDPrint("Whole Flash Test FAILED -- writing FAILED at 0x%d");
                    break; //break out of writes if a write fails
                }
            }
            GLB_GET_LTMR(base2);
            deltaWrite = base2 - base1;
        }
    }


    //Read and verify pattern from Flash
    if(status == TRUE) {
        //A pattern has been written to the flash
        //note: numWords is the same as the Write sequence
        //issue reads
        GLB_GET_LTMR(base1);
        for(i=0; i<numWords; i++) {
            //do read, offset = i, value = temp, length = 1 word.
            status = bsm_Flash_Read_With_Packed(i, &temp, (UINT32)(1));
            if(status == FALSE) {
                bsm_SDPrint("Whole Flash Test FAILED -- read FAILED");
                break; //break out of writes if a write fails
            }
            if(temp != (UINT16)(i & 0x0000FFFF)) {
                bsm_SDPrint("Whole Flash Test FAILED -- data verification FAILED");
                break; //break out of writes if a write fails
            }
        }
        GLB_GET_LTMR(base2);
        deltaRead = base2 - base1;
    }

    if(status == TRUE) {
        bsm_SDPrint("Whole Flash Test PASSED");
    }

    return status;
}



/****************************************************************
 Event Log Single: Test writing a single entry to the event log,
                   tests both the flash Mirror and the flash with
                   a flush to flash
*****************************************************************/
BOOL eventLogSingle(void){
    BOOL status;
    int  code;


    status = doResetFlash();

    //Now that flash is clear, do an init to setup NVStorage, event handler pointers etc.
    if(status == TRUE) {
        status = bsm_EEInit();
        if(status == FALSE) {
            bsm_SDPrint("eventLogSingle FAILED - EEInit FAILED");
        }
        else{
            bsm_EHClearLog();    //clear log for a fresh log
        }
    }

    // CREATE AND READ A LOG ENTRY W/O FLUSHING
    if(status == TRUE) {
        code = 0;

        //Create a Log Entry
        bsm_EHLog("Test Log Message", code);


        //Read Entry
        if(doReadEntry() != code) {
            bsm_SDPrint("eventLogSingle FAILED - cannot read what we wrote to FlashMirror");
            status = false;
        }
    }

    //Flush Mirror out to FLASH
    if(status == TRUE) {
        status = bsm_EEFlush();
        if(status == FALSE) {
            bsm_SDPrint("eventLogSingle FAILED - EEFlush FAILED");
        }
    }

    //CLEAR FLASHMIRROR
    if(status == TRUE) {
        doResetFlashMirror();

        //Read from FLASH to fill mirror
        status = bsm_EEInit();
        if(status == FALSE) {
            bsm_SDPrint("eventLogSingle FAILED - EEInit FAILED");
        }
    }

    bsm_EHResetLogReadPointer();

    //Read Entry
    if(status == TRUE) {
        if(doReadEntry()!= code) {
            bsm_SDPrint("eventLogSingle FAILED - cannot read what we wrote after flush/init");
        }
    }

    if(status == TRUE) {
        bsm_SDPrint("eventLogSingle PASSED");
    }

    return status;
}

/****************************************************************
 Event Log Full: Test writing event entries to nearly fill the
                 entire event log space
*****************************************************************/
#define NUMLOGS 631
BOOL eventLogFull(void){
    BOOL   status;
    char   log[250]; //char array
    int    code;
    UINT32 timeStamp;
    UINT32 i; //loop var

    status = doResetFlash();

    //INITIALIZE THE NVStorage, FLASH, AND EVENT HANDLER
    if(status == TRUE) {
        status = bsm_EEInit();
        if(status == FALSE) {
            bsm_SDPrint("eventLogFull FAILED - EEInit FAILED");
        }
        else{
            bsm_EHClearLog();    //clear log for a fresh log
        }
    }

    //Create Log Entries to fill mirror	and flush mirror out to flash (for pointers)
    if(status == TRUE) {
        for(i = 0; i<NUMLOGS; i++) {
            bsm_EHLogFull("Test Log Message", ((UINT16)i), __LINE__, __FILE__);
            GLB_LTMR_WAIT(18);    //wait for message to be transmitted out(Serial debug port)
            //255 char max, 11500 baud, 8 bit/char => 18ms to xmit out serialport
        }

        //Flush Mirror out to FLASH
        status = bsm_EEFlush();
        if(status == FALSE) {
            bsm_SDPrint("eventLogFull FAILED - EEFlush FAILED");
        }
    }

    //Clear flashMirror and read in flash copy back into flashMirror
    if(status == TRUE) {
        //Clear Flash Mirror
        doResetFlashMirror();

        //Read from FLASH to fill mirror
        bsm_EEInit();
    }

    //reset read pointer and read entries
    if(status == TRUE) {
        bsm_EHResetLogReadPointer();

        //Read Log Entries
        for(i = 0; i<NUMLOGS; i++) {
            if(bsm_EHReadNextEntry(log, &code, &timeStamp) == TRUE) {
                if(i != (UINT32)(code)) {
                    bsm_SDPrint("eventLogFull FAILED - Expected code != received code");
                    status = FALSE;
                }
            }
            else{
                bsm_SDPrint("eventLogFull FAILED - ran out of logs to read, last read code:");
                status = FALSE;
            }
        }
    }

    if(status == TRUE) {
        bsm_SDPrint("eventLogFull PASSED");
    }

    return status;
}


/****************************************************************
 NVStorageSingle: Test writes one entry in NVStorage area, does a flush to flash,
                  re-inits the NVStiorage RAM copy and checks if writeen value can
                  be read back out.

*****************************************************************/
BOOL NVStorageSingle(void){
    BOOL   status;
    BYTE   value[coc_NetworkConnectionAttempts_SIZE];
    UINT16 i;     //loop var

    //Clear out the RAM copy of flash
    doResetFlashMirror();

    //Init of the flash module has occured in startup


    //Read existing data in Flash
    if(status == TRUE)
    {
        status = bsm_EEReadBuf(value, coc_NetworkConnectionAttempts_SIZE, coc_NetworkConnectionAttempts_ADDR);
        if(status == FALSE)
        {
            bsm_SDPrint("NVStorageFull FAILED - EEReadBuf FAILED");
        }
    }

    //Write data to flash
    if(status == TRUE)
    {
        //create and set desired data
        for(i=0; i<sizeof(value); i++)
        {
            value[i] = i + 42;             //for non-trival values
        }

        //Write desired data to flash
        status = bsm_EEWriteBuf(value, coc_NetworkConnectionAttempts_SIZE, coc_NetworkConnectionAttempts_ADDR);
        if(status == FALSE)
        {
            bsm_SDPrint("NVStorageFull FAILED - EEWriteBuf FAILED");
        }
    }

    //Simulate power down flush to flash
    if(status == TRUE)
    {
        status = bsm_EEFlush();
        if(status == FALSE)
        {
            bsm_SDPrint("NVStorageFull FAILED - EEFlush FAILED");
        }
        //Read existing data in Flash
        status = bsm_EEReadBuf(value, coc_NetworkConnectionAttempts_SIZE, coc_NetworkConnectionAttempts_ADDR);
    }

    return status;

}

/****************************************************************
 NVStorageFull: Test writing all entries in NVStorage area.
 Mode: TRUE  -> Writes to flashMirror ONLY, does NOT flush to flash
               (i.e. does not simulate actual power down flush to flash)
           FALSE -> Flushs current contents of flashMirror to flash and
                    then reads it
                   //Note: the function must be run with mode=TRUE
                     first for the FALSE test to be valid!
*****************************************************************/
BOOL NVStorageFull(BOOL Mode){
    BOOL status;
    int  offset; //offset for number test vector generation
    char str[64];

    status = TRUE;
    offset = 0;
    if(Mode == FALSE) {
        //since mode is false, we are doing a write test, we must
        //first flush NVStorage to flash

        //CLEAR FLASH BEFORE START
        status = doResetFlash();

        //FLUSH TO FLASH
        if( status == TRUE) {
            status = bsm_EEFlush();
            if(status == FALSE) {
                bsm_SDPrint("NVStorageFull FAILED - EElush FAILED");
            }
        }
    }

    //CLEAR FLASHMIRROR BEFORE START, (place in RAM where flash copy is stored)
    if(status == TRUE) {
        doResetFlashMirror();

        if(Mode == FALSE) {
            //since mode is false, we are doing a write/flush test, we must
            //init NVStorage (read from flash to create FlashMirror)
            status = bsm_EEInit();
            if(status == FALSE) {
                bsm_SDPrint("NVStorageFull FAILED - EEInit FAILED");
            }
        }
    }

    //AppScratchPad Check
    if(status == TRUE) {
        if(NVTest(coc_AppScratchPad_SIZE, coc_AppScratchPad_ADDR, offset, Mode)  != TRUE) {
            sprintf(str, "NVStorageFull FAILED -- AppScratchPad, mode %d", Mode);
            bsm_SDPrint(str);
            status = FALSE;
        }
        offset++;
    }

    //Asset Management Data
    //SWVer Check
    if(status == TRUE) {
        if(NVTest(coc_SWVer_SIZE, coc_SWVer_ADDR, offset, Mode)  != TRUE) {
            sprintf(str, "NVStorageFull FAILED -- SWVer, mode %d", Mode);
            bsm_SDPrint(str);
            status = FALSE;
        }
        offset++;
    }

    //SN Check
    if(status == TRUE) {
        if(NVTest(coc_EEPROM_SN_SIZE, coc_EEPROM_SN_ADDR, offset, Mode)  != TRUE) {
            sprintf(str, "NVStorageFull FAILED -- SN, mode %d", Mode);
            bsm_SDPrint(str);
            status = FALSE;
        }
        offset++;
    }

    //DialPrefix Check
    if(status == TRUE) {
        if(NVTest(coc_DIALPREFIX_SIZE, coc_DIALPREFIX_ADDR, offset, Mode)  != TRUE) {
            sprintf(str, "NVStorageFull FAILED -- DialPrefix, mode %d", Mode);
            bsm_SDPrint(str);
            status = FALSE;
        }
        offset++;
    }

    //LastInterrogateDuration Check
    if(status == TRUE) {
        if(NVTest(coc_LastInterrogateDuration_SIZE, coc_LastInterrogateDuration_ADDR, offset, Mode)  != TRUE) {
            sprintf(str, "NVStorageFull FAILED -- LastInterrogateDuration, mode %d", Mode);
            bsm_SDPrint(str);
            status = FALSE;
        }
        offset++;
    }

    //NetworkConnectionAttempts Check
    if(status == TRUE) {
        if(NVTest(coc_NetworkConnectionAttempts_SIZE, coc_NetworkConnectionAttempts_ADDR, offset, Mode)  != TRUE) {
            sprintf(str, "NVStorageFull FAILED -- NetworkConnectionAttempts, mode %d", Mode);
            bsm_SDPrint(str);
            status = FALSE;
        }
        offset++;
    }

    //HWMetric Check
    if(status == TRUE) {
        if(NVTest(coc_HWMetric_SIZE, coc_HWMetric_ADDR, offset, Mode)  != TRUE) {
            sprintf(str, "NVStorageFull FAILED -- HWMetric, mode %d", Mode);
            bsm_SDPrint(str);
            status = FALSE;
        }
        offset++;
    }

    //ISPAuthMethod Check
    if(status == TRUE) {
        if(NVTest(coc_ISPAuthMethod_SIZE, coc_ISPAuthMethod_ADDR, offset, Mode)  != TRUE) {
            sprintf(str, "NVStorageFull FAILED -- ISPAuthMethod, mode %d", Mode);
            bsm_SDPrint(str);
            status = FALSE;
        }
        offset++;
    }


    //Configuration Data
    //ISPLoginID Check
    if(status == TRUE) {
        if(NVTest(coc_IPLoginID_SIZE, coc_IPLoginID_ADDR, offset, Mode)  != TRUE) {
            sprintf(str, "NVStorageFull FAILED -- ISPLoginID, mode %d", Mode);
            bsm_SDPrint(str);
            status = FALSE;
        }
        offset++;
    }

    //ISPPassword Check
    if(status == TRUE) {
        if(NVTest(coc_IPPassword_SIZE, coc_IPPassword_ADDR, offset, Mode)  != TRUE) {
            sprintf(str, "NVStorageFull FAILED -- ISPPassword, mode %d", Mode);
            bsm_SDPrint(str);
            status = FALSE;
        }
        offset++;
    }

    //EncryptionKey Check
    if(status == TRUE) {
        if(NVTest(coc_EncryptionKey_SIZE, coc_EncryptionKey_ADDR, offset, Mode)  != TRUE) {
            sprintf(str, "NVStorageFull FAILED -- EncryptionKey, mode %d", Mode);
            bsm_SDPrint(str);
            status = FALSE;
        }
        offset++;
    }

    //HTTPLoginID Check
    if(status == TRUE) {
        if(NVTest(coc_HTTPLoginID_SIZE, coc_HTTPLoginID_ADDR, offset, Mode)  != TRUE) {
            sprintf(str, "NVStorageFull FAILED -- HTTPLoginID, mode %d", Mode);
            bsm_SDPrint(str);
            status = FALSE;
        }
        offset++;
    }

    //HTTPPassword Check
    if(status == TRUE) {
        if(NVTest(coc_HTTPPassword_SIZE, coc_HTTPPassword_ADDR, offset, Mode)  != TRUE) {
            sprintf(str, "NVStorageFull FAILED -- HTTPPassword, mode %d", Mode);
            bsm_SDPrint(str);
            status = FALSE;
        }
        offset++;
    }

    //ISPPhone1 Check
    if(status == TRUE) {
        if(NVTest(coc_ISPPhone1_SIZE, coc_ISPPhone1_ADDR, offset, Mode)  != TRUE) {
            sprintf(str, "NVStorageFull FAILED -- ISPPhone1, mode %d", Mode);
            bsm_SDPrint(str);
            status = FALSE;
        }
        offset++;
    }

    //ISPPhone2 Check
    if(status == TRUE) {
        if(NVTest(coc_ISPPhone2_SIZE, coc_ISPPhone2_ADDR, offset, Mode)  != TRUE) {
            sprintf(str, "NVStorageFull FAILED -- ISPPhone2, mode %d", Mode);
            bsm_SDPrint(str);
            status = FALSE;
        }
        offset++;
    }

    //ISPHostName Check
    if(status == TRUE) {
        if(NVTest(coc_ISPHostName_SIZE, coc_ISPHostName_ADDR, offset, Mode)  != TRUE) {
            sprintf(str, "NVStorageFull FAILED -- ISPHostName, mode %d", Mode);
            bsm_SDPrint(str);
            status = FALSE;
        }
        offset++;
    }

    //HTTPServerName Check
    if(status == TRUE) {
        if(NVTest(coc_HTTPServerName_SIZE, coc_HTTPServerName_ADDR, offset, Mode)  != TRUE) {
            sprintf(str, "NVStorageFull FAILED -- HTTPServerName, mode %d", Mode);
            bsm_SDPrint(str);
            status = FALSE;
        }
        offset++;
    }

    //HTTPHomePage Check
    if(status == TRUE) {
        if(NVTest(coc_HTTPHomePage_SIZE, coc_HTTPHomePage_ADDR, offset, Mode)  != TRUE) {
            sprintf(str, "NVStorageFull FAILED -- HTTPHomePage, mode %d", Mode);
            bsm_SDPrint(str);
            status = FALSE;
        }
        offset++;
    }


    //BSM Management Data

    //CurrLogRead Check
    if(status == TRUE) {
        if(Mode == TRUE) {
            //Only do log pointers and CRC if we're writing mode(mode == true), during a
            //EEFlush these values are updated so a check will fail, so don't do a check
            // on mode==false where a flush occurs. The values change because this test
            //puts known garbage data in those fields the read reading it back. The log
            //pointers are updates on a flush and the crc is recalculated.
            if(NVTest(coc_CurrLogRead_SIZE, coc_CurrLogRead_ADDR, offset, Mode)  != TRUE) {
                sprintf(str, "NVStorageFull FAILED -- CurrLogRead, mode %d", Mode);
                bsm_SDPrint(str);
                status = FALSE;
            }
            offset++;

            //CurrLogWrite Check
            if(status == TRUE) {
                if(NVTest(coc_CurrLogWrite_SIZE, coc_CurrLogWrite_ADDR, offset, Mode)  != TRUE) {
                    sprintf(str, "NVStorageFull FAILED -- CurrLogWrite, mode %d", Mode);
                    bsm_SDPrint(str);
                    status = FALSE;
                }
                offset++;
            }

            if(status == TRUE) {
                if(NVTest(coc_CRC_SIZE, coc_CRC_ADDR, coc_CRC_ADDR, Mode) != TRUE) {
                    sprintf(str, "NVStorageFull FAILED -- CRC, mode %d", Mode);
                    bsm_SDPrint(str);
                    status = FALSE;
                }
            }
        }
    }

    if(status == TRUE) {
        bsm_SDPrint("NVStorageFull PASSED");
    }

    return status;
}






BOOL doNetworkDebugPRD = FALSE;

/******************************************************************************
* prd_getVocalNetworkDebug
* PURPOSE: This grabs serialized data from the Vocal network layer and echos
*          it out the serial port
******************************************************************************/
void prd_getVocalNetworkDebug(void)
{
    INT16        data;
    GLB_HTMR_OBJ startTime;

    //Only run if debug is enabled
    if(doNetworkDebugPRD == TRUE)
    {
        GLB_GET_HTMR(startTime);

        // continue printing from buffer while valid data is present and
        // before a 5ms timeout occurs
        while( ((data = network_serial_tx()) & 0x8000) != 0x8000 &&
               GLB_HAS_HTMR_EXPIRED(startTime, (UINT32)1000000) != TRUE)
        {
            data &= 0x007F;
            bsm_SDWrite((char *)&data, 1);
        }
    }
//	else{
//		data = 0x34;
//		bsm_SDWrite((char *)&data, 1);
//		data = 0x32;
//		bsm_SDWrite((char *)&data, 1);
//		data = 0x21;
//		bsm_SDWrite((char *)&data, 1);
//	}
}


