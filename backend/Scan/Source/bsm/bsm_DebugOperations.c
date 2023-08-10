/************************************************************************
*
* MODULE: bsm_DebugOperations.c
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the functions for all the debug
*              functionality.
*
*************************************************************************/

/////////////
// Includes
/////////////
#include <csl.h>
#include <csl_mcbsp.h>
#include <csl_dma.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "global.h"
#include "bsm_SerialPort.h"
#include "bsm_General.h"

#include "dbg_battery.h"
#include "dbg_General.h"
#include "dbg_led.h"
#include "dbg_switch.h"
#include "dbg_speaker.h"
#include "dbg_CountPulses.h"
#include "dbg_MeasureJitter.h"
#include "dbg_Flash.h"
#include "dbg_SoftwareUpdate.h"
#include "dbg_BurnIn.h"
#include "dbg_TestInternalRam.h"
#include "dbg_TestExternalRam.h"
#include "dbg_ContinuousRf.h"
#include "dbg_Modem.h"
#include "dbg_CalculateCrc.h"
#include "dbg_PrintLog.h"
#include "dbg_LoadProgram.h"
#include "bsm_Event.h"
#include "cx077.h"
#include "dbg_TelemB.h"
#include "dbg_menu.h"
#include "dbg_SendTelemAMessage.h"

////////////
// Defines
////////////

// command defines
//NOTE: The values are the HEX representation of rhe characters.
#define READ_BATTERY_THRESHOLD              0x4254  //'BT'
#define SET_LED                             0x4C45  //'LE'
#define READ_PULSE_TONE_SWITCH              0x5254  //'RT'
#define READ_PREFIX_SWITCH                  0x5250  //'RP'
#define SET_AUDIO_SPEAKER                   0x4153  //'AS'
#define CONTINUOUS_RF                       0x4352  //'CR'
#define RECEIVE_TELEMETRY_B                 0x5442  //'TB'
#define TELEM_B_ITEM_MAP_TRIGGERED          0x5454  //'TT'
#define TELEM_B_ITEM_MAP_SINGLE             0x5453  //'TS'
#define TELEM_B_HFIELD_TEST                 0x5448  //'TH'
#define TELEM_B_ITEM_MAP_COUNT              0x5443  //'TC'
#define START_COUNTING_TELEMETRY_A_PULSES   0x4243  //'BC'
#define STOP_COUNTING_TELEMETRY_A_PULSES    0x4543  //'EC'
#define START_TELEMETRY_A_JITTER            0x424A  //'BJ'
#define STOP_TELEMETRY_A_JITTER             0x454A  //'EJ'
#define SDRAM_MEMORY_TEST                   0x534D  //'SM'
#define INTERNAL_MEMORY_TEST                0x494D  //'IM'
#define CALCULATE_CRC                       0x4346  //'CF'
#define WRITE_FLASH                         0x5746  //'WF'
#define READ_FLASH                          0x5246  //'RF'
#define READ_LOG                            0x524C  //'RL'
#define CLEAR_LOG                           0x434C  //'CL'
#define COMMIT_CHANGES                      0x4343  //'CC'
#define BURN_IN_TEST                        0x4249  //'BI'
#define SOFTWARE_UPDATE                     0x5355  //'SU'
#define LOAD_PROGRAM                        0x4C50  //'LP'
#define OPEN_MODEM                          0x4F4D  //'OM'
#define MODEM_COMMAND                       0x4D44  //'MD'
#define MODEM_TERMINAL_DATA_EXCHANGE        0x4D54  //'MT'
#define MODEM_IGNORE_CARRIER_LOSS           0x4D49  //'MI'
#define MODEM_FORCE_DAILTONE_CADENCE_DETECT 0x4D43  //'MC'
#define MODEM_DTMF_CONFIG                   0x4D53  //'MS'
#define CLOSE_MODEM                         0x434D  //'CM'
#define EEPROM_ADDRESS                      0x4541  //'EA'
#define EXIT                                0x5858  //'XX'

#ifdef __DEV_VT__
#define HELP_SCREEN                         0x4850  //'HP'
#define SEND_TELEMA_MSG                     0x5354  //'ST'
#define TEST_WATCHDOG                       0x5457  //'TW'
#define SYSTEM_ID                           0x5349  //'SI'
#define READ_S_REGISTERS                    0x5352  //'SR' - Support Country Code Testing
#define WRITE_S_REGISTERS                   0x5357  //'SW' - Support Country Code Testing
#endif // __DEV_VT__


/******************************************************************

FUNCTION: ExecuteCommand

DESCRIPTION: This function processes the message and calls the
             function to perform the action.

ARGS:
        char* CommandLine: A null terminated string with the command.

RETURNS:
    <none>

******************************************************************/
BOOL ExecuteCommand(char* CommandLine)
{
    UINT16 Command;

    // form a 16-bit word from the first 2 bytes
    Command = (CommandLine[0]<<8) | CommandLine[1];

    // execute a command based on the first 2 bytes of the command line
    switch( Command )
    {
    case READ_BATTERY_THRESHOLD:
        ReadBatteryThreshold();
        break;

    case SET_LED:
        SetLed(&CommandLine[3]);
        break;

    case READ_PULSE_TONE_SWITCH:
        ReadPulseToneSwitch();
        break;

    case READ_PREFIX_SWITCH:
        ReadPrefixSwitch();
        break;

    case SET_AUDIO_SPEAKER:
        SetAudioSpeaker(&CommandLine[3]);
        break;

    case CONTINUOUS_RF:
        SetRfFrequency(&CommandLine[3]);
        break;
#ifdef __2490TELEMB__
    case RECEIVE_TELEMETRY_B:
        dbg_rcvTestFrame(CommandLine[3]);
        break;

    case TELEM_B_HFIELD_TEST:
        dbg_rcvTestFrameLoop(CommandLine[3]);
        break;

    case TELEM_B_ITEM_MAP_TRIGGERED:
        dbg_itemTestApp(CommandLine[3]);
        break;

    case TELEM_B_ITEM_MAP_SINGLE:
        dbg_itemTestSingle(CommandLine[3]);
        break;

    case TELEM_B_ITEM_MAP_COUNT:
        dbg_itemTestCount(CommandLine[3], &CommandLine[5]);
        break;
#endif
    case START_COUNTING_TELEMETRY_A_PULSES:
        StartCountingPulses();
        break;

    case STOP_COUNTING_TELEMETRY_A_PULSES:
        StopCountingPulses();
        break;

    case START_TELEMETRY_A_JITTER:
        StartMeasuringJitter();
        break;

    case STOP_TELEMETRY_A_JITTER:
        StopMeasuringJitter();
        break;

    case SDRAM_MEMORY_TEST:
        TestSdram();
        break;

    case INTERNAL_MEMORY_TEST:
        TestInternalRam();
        break;

    case CALCULATE_CRC:
        CalculateApplicationCrc();
        break;

    case BURN_IN_TEST:
        BurnInTest();
        break;

    case WRITE_FLASH:
        WriteFlash(&CommandLine[3]);
        break;

    case READ_FLASH:
        ReadFlash(&CommandLine[3]);
        break;

    case READ_LOG:
        PrintLog();
        break;

    case CLEAR_LOG:
        bsm_EHClearLog();
        break;

    case COMMIT_CHANGES:
        CommitChanges();
        break;

    case SOFTWARE_UPDATE:
        SoftwareUpdate(&CommandLine[3]);
        break;

    case LOAD_PROGRAM:
        LoadProgram(&CommandLine[3]);
        break;

    case EXIT:
        // we are done executing commands
        bsm_SDPrint("Exiting Debug Mode");
        return FALSE;

    case OPEN_MODEM:
        bsm_setModemState(ON);
        break;

    case MODEM_COMMAND:
        SendAtCommand(&CommandLine[3]);
        break;

    case MODEM_TERMINAL_DATA_EXCHANGE:
        TerminalDataExchange();
        break;

    case MODEM_IGNORE_CARRIER_LOSS:
        IgnoreCarrierLoss();
        break;

    case MODEM_FORCE_DAILTONE_CADENCE_DETECT:
        mdm_setModemCadenceDialDetect();
        break;

    case MODEM_DTMF_CONFIG:
        mdm_setModemDTMFStrength();
        break;

    case CLOSE_MODEM:
        bsm_setModemState(OFF);
        break;

#ifdef __DEV_VT__
    case HELP_SCREEN:
        PrintMenu();
        break;

    case SEND_TELEMA_MSG:
        SendTelemetryAMessage(&CommandLine[3]);
        break;

    case TEST_WATCHDOG:
        DISABLE_INTERRUPTS;
        while(1) ;

    case SYSTEM_ID:
        ReadSystemID();
        break;

    // Support country code testing
    case READ_S_REGISTERS:
        Read_sRegisters();
        break;

    // Support country code testing
    case WRITE_S_REGISTERS:
        Write_sRegisters(&CommandLine[3]);
        break;
#endif // __DEV_VT__

    case EEPROM_ADDRESS:
        PrintEepromAddr();
        break;

    default:
        bsm_SDPrint("Unknown Command");
        break;
    }
    // we executed a command.
    return TRUE;
}
