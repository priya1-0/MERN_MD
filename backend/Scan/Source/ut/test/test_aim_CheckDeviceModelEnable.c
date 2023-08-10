/*******************************************************************************
 *    INCLUDED FILES
 ******************************************************************************/
 
//-- unity: unit test framework
#include "unity.h"
 
//-- module being tested
//
#include "aim_CheckDeviceModelEnable.h"
#include "string.h"


#include "mock_bsm_EEReadBuf.h"

 
/*******************************************************************************
 *    DEFINITIONS
 ******************************************************************************/
#define FUNC_ENTER() printf("%s() Enter...\n", __func__) 
#define FUNC_EXIT()  printf("%s() Exit.\n", __func__) 
 
/*******************************************************************************
 *    PRIVATE TYPES
 ******************************************************************************/
 
/*******************************************************************************
 *    PRIVATE DATA
 ******************************************************************************/
char eepromPhone4[coc_ISPPhone4_SIZE];
 
 
/*******************************************************************************
 *    PRIVATE FUNCTIONS
 ******************************************************************************/
 
 
/*******************************************************************************
 *    SETUP, TEARDOWN
 ******************************************************************************/
 
void setUp(void)
{
    // Initialize the string to something other than NULL
    // although a strcpy will place a NULL
    memset(eepromPhone4, '5', sizeof(eepromPhone4));
}
 
void tearDown(void)
{
}
 
/*******************************************************************************
 *    TESTS
 ******************************************************************************/
 
void test_aim_CheckDeviceModelEnable_prefixBad(void)
{
    strcpy(eepromPhone4, "&0018;");

    bsm_EEReadBuf_Expect( 0,//(UINT8*)DeviceEnableList,
                          coc_ISPPhone4_SIZE,
                          coc_ISPPhone4_ADDR );
    bsm_EEReadBuf_IgnoreArg_buffer();       // ignore the "DeviceEnableList" parameter
    // tell unity what to return when bsm_EEReadBuf is called
    bsm_EEReadBuf_ReturnMemThruPtr_buffer(eepromPhone4, coc_ISPPhone4_SIZE);

    TEST_ASSERT_FALSE(aim_CheckDeviceModelEnable(0x18));
}

void test_aim_CheckDeviceModelEnable_prefixGood(void)
{
    strcpy(eepromPhone4, "#0019;");

    bsm_EEReadBuf_Expect( 0,//(UINT8*)DeviceEnableList,
                          coc_ISPPhone4_SIZE,
                          coc_ISPPhone4_ADDR );
    // ignore the "DeviceEnableList" parameter
    bsm_EEReadBuf_IgnoreArg_buffer();
    // tell unity what to return
    bsm_EEReadBuf_ReturnMemThruPtr_buffer(eepromPhone4, coc_ISPPhone4_SIZE);

    TEST_ASSERT_TRUE(aim_CheckDeviceModelEnable(0x19));
}

void test_aim_CheckDeviceModelEnable_suffixBad(void)
{
    strcpy(eepromPhone4, "#0001#");

    bsm_EEReadBuf_Expect( 0,//(UINT8*)DeviceEnableList,
                          coc_ISPPhone4_SIZE,
                          coc_ISPPhone4_ADDR );
    // ignore the "DeviceEnableList" parameter
    bsm_EEReadBuf_IgnoreArg_buffer();
    // tell unity what to return
    bsm_EEReadBuf_ReturnMemThruPtr_buffer(eepromPhone4, coc_ISPPhone4_SIZE);

    TEST_ASSERT_FALSE(aim_CheckDeviceModelEnable(0x01));
}

void test_aim_CheckDeviceModelEnable_suffixGood(void)
{
    strcpy(eepromPhone4, "#0001;");

    bsm_EEReadBuf_Expect( 0,//(UINT8*)DeviceEnableList,
                          coc_ISPPhone4_SIZE,
                          coc_ISPPhone4_ADDR );
    // ignore the "DeviceEnableList" parameter
    bsm_EEReadBuf_IgnoreArg_buffer();
    // tell unity what to return
    bsm_EEReadBuf_ReturnMemThruPtr_buffer(eepromPhone4, coc_ISPPhone4_SIZE);

    TEST_ASSERT_TRUE(aim_CheckDeviceModelEnable(0x01));
}

void test_aim_CheckDeviceModelEnable_modelIdShort(void)
{
    strcpy(eepromPhone4, "#002;");

    bsm_EEReadBuf_Expect( 0,//(UINT8*)DeviceEnableList,
                          coc_ISPPhone4_SIZE,
                          coc_ISPPhone4_ADDR );
    // ignore the "DeviceEnableList" parameter
    bsm_EEReadBuf_IgnoreArg_buffer();
    // tell unity what to return
    bsm_EEReadBuf_ReturnMemThruPtr_buffer(eepromPhone4, coc_ISPPhone4_SIZE);

    TEST_ASSERT_FALSE(aim_CheckDeviceModelEnable(0x02));
}

void test_aim_CheckDeviceModelEnable_modelIdLong(void)
{
    strcpy(eepromPhone4, "#00002;");

    bsm_EEReadBuf_Expect( 0,//(UINT8*)DeviceEnableList,
                          coc_ISPPhone4_SIZE,
                          coc_ISPPhone4_ADDR );
    // ignore the "DeviceEnableList" parameter
    bsm_EEReadBuf_IgnoreArg_buffer();
    // tell unity what to return
    bsm_EEReadBuf_ReturnMemThruPtr_buffer(eepromPhone4, coc_ISPPhone4_SIZE);

    TEST_ASSERT_FALSE(aim_CheckDeviceModelEnable(0x02));
}

void test_aim_CheckDeviceModelEnable_2entriesFirstOneShort(void)
{
    strcpy(eepromPhone4, "#002,0003;");

    bsm_EEReadBuf_Expect( 0,//(UINT8*)DeviceEnableList,
                          coc_ISPPhone4_SIZE,
                          coc_ISPPhone4_ADDR );
    // ignore the "DeviceEnableList" parameter
    bsm_EEReadBuf_IgnoreArg_buffer();
    // tell unity what to return
    bsm_EEReadBuf_ReturnMemThruPtr_buffer(eepromPhone4, coc_ISPPhone4_SIZE);

    TEST_ASSERT_TRUE(aim_CheckDeviceModelEnable(0x03));
}

void test_aim_CheckDeviceModelEnable_ABCD(void)
{
    strcpy(eepromPhone4, "#,,,,ABCD;");

    bsm_EEReadBuf_Expect( 0,//(UINT8*)DeviceEnableList,
                          coc_ISPPhone4_SIZE,
                          coc_ISPPhone4_ADDR );
    // ignore the "DeviceEnableList" parameter
    bsm_EEReadBuf_IgnoreArg_buffer();
    // tell unity what to return
    bsm_EEReadBuf_ReturnMemThruPtr_buffer(eepromPhone4, coc_ISPPhone4_SIZE);

    TEST_ASSERT_TRUE(aim_CheckDeviceModelEnable(0xDCBAabcd));
}

void test_aim_CheckDeviceModelEnable_ABCd_showFunctionIsCaseSensitive(void)
{
    strcpy(eepromPhone4, "#0018,ABCd;");

    bsm_EEReadBuf_Expect( 0,//(UINT8*)DeviceEnableList,
                          coc_ISPPhone4_SIZE,
                          coc_ISPPhone4_ADDR );
    // ignore the "DeviceEnableList" parameter
    bsm_EEReadBuf_IgnoreArg_buffer();
    // tell unity what to return
    bsm_EEReadBuf_ReturnMemThruPtr_buffer(eepromPhone4, coc_ISPPhone4_SIZE);

    TEST_ASSERT_FALSE(aim_CheckDeviceModelEnable(0x0000abcd));
}

void test_aim_CheckDeviceModelEnable_maxEntries(void)
{
    int     i;
    
    //                    012345678901234567890123456789012
    strcpy(eepromPhone4, "#0001,0002,0003,0004,0005,0006;");

    for (i=1; i<=6; ++i){
        bsm_EEReadBuf_Expect( 0,//(UINT8*)DeviceEnableList,
                            coc_ISPPhone4_SIZE,
                            coc_ISPPhone4_ADDR );
        // ignore the "DeviceEnableList" parameter
        bsm_EEReadBuf_IgnoreArg_buffer();
        // tell unity what to return
        bsm_EEReadBuf_ReturnMemThruPtr_buffer(eepromPhone4, coc_ISPPhone4_SIZE);

        TEST_ASSERT_TRUE(aim_CheckDeviceModelEnable(i));
    }
}

// This test shows that a max string and no NULL termination passes.
// It also shows that, besides the first entry, the only requirement 
// for a valid entry is that the the entry have a ',' followed by a 
// 4 character value
void test_aim_CheckDeviceModelEnable_maxPhone4StringNotNullTerminated(void)
{
    int     i;
    
    //                    012345678901234567890123456789012
    strcpy(eepromPhone4, "#000A,000B,000C,000D,000EX,000F");
    // put a semicolon in the last location of the string, right after the 'X'
    eepromPhone4[coc_ISPPhone4_SIZE-1]=';';

//     // These loops show the indexed content of the string.
//     // It is commented out because the output distracts from the test output.
//     for (i=0; i<coc_ISPPhone4_SIZE; ++i) {
//         printf("%d", i%10);
//     }
//     printf("\n");
//     for (i=0; i<coc_ISPPhone4_SIZE; ++i) {
//         printf("%c", eepromPhone4[i]);
//     }

    for (i=0xa; i<=0xf; ++i){
        bsm_EEReadBuf_Expect( 0,//(UINT8*)DeviceEnableList,
                            coc_ISPPhone4_SIZE,
                            coc_ISPPhone4_ADDR );
        // ignore the "DeviceEnableList" parameter
        bsm_EEReadBuf_IgnoreArg_buffer();
        // tell unity what to return
        bsm_EEReadBuf_ReturnMemThruPtr_buffer(eepromPhone4, coc_ISPPhone4_SIZE);

        TEST_ASSERT_TRUE(aim_CheckDeviceModelEnable(i));
    }
}




