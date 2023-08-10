/************************************************************************
*
* MODULE: dbg_Modem.c
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the functions for debugging the modem.
*
*************************************************************************/

/////////////
// Includes
/////////////
#include "bsm_serialport.h"
#include "cx077.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "nwm_net.h"
#include "bsm_General.h"
#include "bsm_Event.h"

/******************************************************************

FUNCTION: SendAtCommand

DESCRIPTION: This function forwards the command to the modem.  The
             response from the modem is echoed to the host
             computer.

ARGS:
        char* Command: The command to forward to the modem.

RETURNS:
    <none>

******************************************************************/
void SendAtCommand(char* Command)
{
    char mdmResponse[50];
    int  Length;

    // need to append a "\r" to the end of the command
    Length = strlen(Command);
    if( Length < 64-1 )
    {
        Command[Length]   = '\r';
        Command[Length+1] = 0;
    }

    bsm_SDPrint("Sending Command:");
    bsm_SDPrint(Command);

    mdm_Send_Control_String (Command, mdmResponse, 50);

    bsm_SDPrint("Response from modem:");
    bsm_SDPrint(mdmResponse);
}

/******************************************************************

FUNCTION: TerminalDataExchange

DESCRIPTION: This function puts the modem into a terminal data
             exchange mode. This mode cannot be exited. Once this
             mode is activated, you must power off to exit this mode.
             This mode assumes that the modem has already been
             connected to another modem. This mode emulates the terminal
             connection. When characters are received via serial
             port, they are forwarded through the modem. When characters
             are received from the modem they are echoed out the serialport.

NOTE: There is NO flow control in this mode. The serial port can receive
      data faster than the modem can transmit. It is the responsibility
      of the device sending serial data to be sent through the modem to
      throttle the amount of data.

ARGS:
        <none>

RETURNS:
    <none>

******************************************************************/
char dbg_Modem_str[64];
void TerminalDataExchange(void)
{
    UINT16 status;
    UINT16 sent;

    bsm_SDPrint("***< You have entered Terminal Data Exchange mode >***");

    //this mode never returns
    while(1)
    {           // forward received characters from the modem to serial port
        status = mdm_Get_Char(sizeof(dbg_Modem_str), dbg_Modem_str);
        if(status > 0)
        {
            //null terminate the string
            dbg_Modem_str[status] = 0;

            //Forward out serial port
            bsm_SDWrite(dbg_Modem_str, status);
        }

        //forward character line from modem through modem
        status = bsm_SDReadBytes((BYTE*)dbg_Modem_str, sizeof(dbg_Modem_str));
        if(status > 0)
        {
            sent = mdm_Send_String(status, dbg_Modem_str);
            if(sent != status)
            {
                bsm_SDPrint("***< Failed to send full string to modem, Modem no longer connected? >***");
                strcpy(dbg_Modem_str, "toSend: ");
                ltoa( status, &dbg_Modem_str[strlen(dbg_Modem_str)]);                 // add the LineNum to the end of the sTemp
                strcat(dbg_Modem_str, ", sent: ");
                ltoa( sent, &dbg_Modem_str[strlen(dbg_Modem_str)]);
                bsm_SDPrint(dbg_Modem_str);
            }
        }
    }
}


/******************************************************************

FUNCTION: IgnoreCarrierLoss

DESCRIPTION: This function puts the modem into a state where it
             ignores carrier loss and retrain events. This is
             intended to be used for Part 68 testing for sinal
             strength testing

ARGS:
        <none>

RETURNS:
    <none>

******************************************************************/
void IgnoreCarrierLoss(void)
{
    //Set the number FG states to zero to prevent the modem from detecting
    //retrain events and carrier loss. This should only be used during testing
    //and should not be called in the course of nominal code running for released
    //product.
    set_num_fg_states(0);
}

#ifdef __DEV_VT__
/******************************************************************

FUNCTION: Read_sRegisters

DESCRIPTION: This function reads the S-registers in the SiLab
             chip and outputs them to the debug port.

ARGS:
        <none>

RETURNS:
    <none>

******************************************************************/

UINT16 codec_process_control_word (UINT16 control);
UINT16 siRegisters[] =
{
    1, 2, 3, 4, 5, 6, 7, 8, 9,10,
    11,12,13,14,15,16,17,18,19,20,
    21,22,23,24,25,26,27,28,29,30,
    31,38,39,40,41,43,44,59
};
void Read_sRegisters(void)
{

    UINT16 val;
    char   tbuf[80];
    UINT16 index;

    bsm_SDPrint("SiLabs Reg: ");
    for (index = 0; index < sizeof(siRegisters); index++)
    {
        val = codec_process_control_word ((siRegisters[index] << 8) | 0x8000);
        sprintf(tbuf,"reg %u = %04x", siRegisters[index],val);
        bsm_SDPrint (tbuf);
    }

}


/******************************************************************

FUNCTION: Write_sRegisters

DESCRIPTION: This function writes the S-registers in the SiLab
             chip and outputs them to the debug port.

ARGS: CommandlineParameters in format:
command <Reg Number> <Reg value in decimal>


RETURNS:
    <none>

******************************************************************/


void Write_sRegisters(char* CommandLineParameters)
{


    char   tbuf[80];
    UINT16 regVal;
    UINT16 regIndex;

    // parse out the location
    regIndex = (UINT16)atoi(CommandLineParameters);

    sprintf(tbuf,"SiLabs Reg No: %u ", regIndex);
    bsm_SDPrint (tbuf);

    // Check for a valid Silab register. To avoid compilation warning only check for upper limit.
    if (regIndex<=59)
    {
        // move the pointer to the length
        while( *CommandLineParameters != ' ' &&
               *CommandLineParameters != NULL )
        {
            CommandLineParameters++;
        }
        // skip past the ' ' after the location
        CommandLineParameters++;

        // parse out the length
        regVal = (UINT16)atoi(CommandLineParameters);

        sprintf(tbuf,"SiLabs Reg: Writing %u = %04x", regIndex,regVal);
        bsm_SDPrint (tbuf);
        codec_process_control_word ((regIndex << 8) | regVal);
    }
    else
    {
        bsm_SDPrint ("Invalid SiLabs Reg");
    }

}
#endif // __DEV_VT__