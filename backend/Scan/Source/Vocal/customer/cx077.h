
/* ************************************************************************* */
/*
 *	cx077.h
 *
 *	(C) 2003 - 2006 VOCAL Technologies, Ltd.
 *
 *	ALL RIGHTS RESERVED.  PROPRIETARY AND CONFIDENTIAL.
 *
 *	VOCAL Technologies, Ltd.
 *	90A John Muir Drive.
 *	Buffalo, NY	 14228
 *
 *	Product:	MASTER CODE
 *
 *	Module:		CUSTOMER
 *
 *	Define customer symbols.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.2  2010/02/17 23:16:48  heiand1
 *	Revision History:	SCR 186226. Add nwm_Get_Modem_Response() for network debugging.
 *	Revision History:	
 *	Revision History:	Revision 1.1.24.1  2009/04/28 19:09:22  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _CX077_H
#define _CX077_H
/* ************************************************************************* */
/* ************************************************************************* */


typedef unsigned short uint16;
typedef signed short sint15;
typedef unsigned long uint32;
typedef signed long sint31;

#include "include/modem.h"
#include "utils/httpcli.h"

/* ************************************************************************* */

/* These symbols defined in other Vocal headers that are not included in the
   MDT build. When the Vocal code is compiled these prototypes should not
   be defined (multiply declared); however, when the MDT code is compiled
   these should be defined because the MDT code calls these functions.
 */

/* ************************************************************************* */
/*
 *	Entry Routine: network_Send_Cmd
 *
 *	This routine passes command line commands to the network command processor
 *
 *  NOTE: This function *modifies* the passed string by changing spaces to
 *        NULLs!
 *
 *	Parameters:
 *		none
 *
 *	Returns:
 *		none
 *
 */
int  network_Send_Cmd(char*);


/******************************************************************************/
/******************************************************************************/
/* Modem API */
/******************************************************************************/
/******************************************************************************/

/* mdm_cancel_command */
/* Set to TRUE to cancel currently running command */
extern int mdm_cancel_command;

/* ************************************************************************* */
/*
 *	Module Routine: mdm_Send_Control_String
 *
 *	This routine sends a control string to the modem and returns the response.
 *
 *	Parameters:
 *		char * command - pointer to AT command as a null terminated string
 *		char * respbuf - pointer to buffer to receive response
 *		buflen - length of buffer pointed to by respbuf
 *
 *	Returns:
 *		int - number of characters returned in respbuf, not including the null terminator
 *
 *  Notes:
 *		function blocks until a complete reponse string is available
 *		Must be called by an IDL function
 *		function can be terminated by setting mdm_cancel_command to true
 *			in this case the function will return a null terminated string
 *			containing the character received so far
 *		A maximum of buflen - 1 characters will be returned (must leave room for
 *		string terminator).  If buflen-1 characters is reached, then the response
 *		is returned and excess character are ignored.
 *		The first AT command following "+++" to enter command mode, may not return
 *		an "OK".  So, when entering command mode send two commands in the same
 *		string, e.g. "+++ATH\rAT\r".
 */

int mdm_Send_Control_String (char* command, char* respbuf, int buflen);


/* ************************************************************************* */
/*
 *	Module Routine: mdm_Init
 *
 *	This routine initializes the modem.
 *
 *	Parameters:
 *		none
 *
 *	Returns:
 *		One of MDM_ERRORCODE__xxx.
 *
 *	Note:
 *		Function blocks until init is complete or error is detected.
 *		Must be called by an IDL function.
 *		MDM_ERRORCODE__HARDWARE_TIMEOUT indicates that the DAA did not
 *			initialize properly.
 */

int mdm_Init(void);


/* ************************************************************************* */
/*
 *	Module Routine: mdm_Shut_Off
 *
 *	This routine shuts off the DAA and deinitializes the modem.
 *
 *	Parameters:
 *		none
 *
 *	Returns:
 *		none
 *
 *	Note:
 *		This function may be called from any context, wait 2 seconds following
 *		a call to this function before using shared memory locations.
 */

void mdm_Shut_Off(void);


/* ************************************************************************* */
/*
 *	Module Routine: mdm_Get_Connect_Speed
 *
 *	This routine returns the connect speed if modem is connected.
 *
 *	Parameters:
 *		none
 *
 *	Returns:
 *		long integer connect speed, 0 (zero) if not connected
 *
 */

long mdm_Get_Connect_Speed(void);


/* ************************************************************************* */
/*
 *	Module Routine: mdm_Check_Dialtone
 *
 *	This routine check if there is a dial tone.
 *
 *	Parameters:
 *		none
 *
 *	Returns:
 *		0 - no dial tone found.
 *		1 - dial tone found
 *
 *	Notes:
 *      This function blocks, so it must be called from the IDL function
 *		It will block for 3 seconds while detecting dialtone.
 *      It may be called immediately following an ATH1 or ATD##; command
 */

int mdm_Check_Dialtone(void);


/******************************************************************

FUNCTION: mdm_setModemDTMFStrength

DESCRIPTION: This function sets the DTMF signal strength. By default
             the values the modem code uses are low. This function
             overides the modem's configuration to increase the DTMF 
             signal strength.
CONSTRAINT:  This function should be called AFTER all country code
             commands have taken place (AT*NCn where n is the 
             country code). A subsequent country code assignment 
             will nullify this setting.

ARGS:
	<none>

RETURNS:
    <none>    
******************************************************************/
void mdm_setModemDTMFStrength(void);


/******************************************************************

FUNCTION: mdm_setModemCadenceDialDetect

DESCRIPTION: This function overides the modem country code to support
             the detection of cadenced dialtones.
CONSTRAINT:  This function should be called AFTER all country code
             commands (AT*NCn where n is the country code). A
             subsequent country code assignment will nullify this
             setting.
NOTE:        Enabling this for some countries can cause problems, as
             an example the unit may detect a busy done as a 
             dialtone because if the simularity between the busy tone
             and a cadenced dialtone.
ARGS:
	<none>

RETURNS:
    <none>    
******************************************************************/
void mdm_setModemCadenceDialDetect(void);


/******************************************************************************/
/******************************************************************************/
/* Terminal Mode API */
/******************************************************************************/
/******************************************************************************/

/* ************************************************************************* */
/*
 *	Module Routine: mdm_Init_Term_Mode
 *
 *	This routine switches modem to terminal mode for scripted login.
 *
 *	Parameters:
 *		none
 *
 *	Returns:
 *		none
 */

void mdm_Init_Term_Mode(void);


/* ************************************************************************* */
/*
 *	Module Routine: mdm_Get_Char
 *
 *	This routine gets a character from the modem buffer.
 *
 *	Parameters:
 *		int max - size of buffer passed
 *		char * buffer - pointer to buffer to receive characters
 *
 *	Returns:
 *		int - number of characters placed in buffer
 *
 */

int mdm_Get_Char(int max, char* buffer);


/* ************************************************************************* */
/*
 *	Module Routine: mdm_Purge_Input_Buffer
 *
 *	This routine clears the input buffer.
 *
 *	Parameters:
 *		none
 *
 *	Returns:
 *		none
 *
 */

void mdm_Purge_Input_Buffer (void);


/* ************************************************************************* */
/*
 *	Module Routine: mdm_Send_String
 *
 *	This routine sends a string via terminal mode.
 *
 *	Parameters:
 *		int length - length of string to send
 *		char * buffer - pointer to buffer containing string to send
 *
 *	Returns:
 *		int - number of characters sent
 *
 *	Notes:
 *		String to send should be terminated with a carriage return.
 */

int mdm_Send_String (int length, char* buffer);


/* ************************************************************************* */
/* ************************************************************************* */
/* Network API */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */
/*
 *	Module Routine: network_Init
 *
 *	This routine stops terminal mode and makes a network connection via PPP.
 *
 *	Parameters:
 *		int do_auth - if 1 username/password are used to authenticate
 *			via PAP/CHAP
 *		char * username - null terminated string containing username
 *		char * password - null terminated string containing password
 *
 *	Returns:
 *		int -
 *
 *	Notes:
 *		Blocking, must be called from an IDL function
 */

int network_Init (int do_auth, char* username, char* password);


/* ************************************************************************* */
/*
 *	Module Routine: mdm_Get_PPP_Auth_Type
 *
 *	This routine returns the type of authentication that succeeded durring
 *		PPP negotiation.
 *
 *	Parameters:
 *		none
 *
 *	Returns:
 *		int - NET_PPP_AUTH_*
 *
 */

int network_Get_PPP_Auth_Type (void);


/* ************************************************************************* */
/*
 *	Module Routine: http_Process_Request
 *
 *	This routine processes an HTTP request, found in http_request_data, and
 *		fills in the response field of http_request_data.
 *
 *	Parameters:
 *		http_request_data req_data - http request data structure
 *
 *	Returns:
 *		int - HTTP_STATUS_*
 *
 *	Notes:
 *		Blocking, must be called from an IDL function
 */

int http_Process_Request (http_request_data * req_data);

/* ************************************************************************* */
/*
 *	Module Routine: speaker_monitor_on
 *
 *	This routine turns on the speaker.
 *
 *	Parameters:
 *		none
 *
 *	Returns:
 *		none
 *
 */

void speaker_monitor_on (void);

/* ************************************************************************* */
/*
 *	Module Routine: speaker_monitor_off
 *
 *	This routine turns off the speaker.
 *
 *	Parameters:
 *		none
 *
 *	Returns:
 *		none
 *
 */

void speaker_monitor_off (void);

/* ************************************************************************* */
/*
 *	Entry Routine: mdm_Store_Data
 *
 *	This routine stores all data that is initialized in DARAM into a data store
 *		for later retrieval by mdm_Init
 *
 *	Parameters:
 *		none
 *
 *	Returns:
 *		none
 *
 */
void mdm_Store_Data (void);

/******************************************************************

FUNCTION: mdm_setNetworkDebugEnable

DESCRIPTION: This function enables/disables network debug functionality.
             
			 If the parameter is enabled prior to network startup, network
             debug printing will start automatically. Please note that it
			 is disabled by default.

			 This function may be called dynamically.
			 
Paramters:
	int mode - 1 enables network debug, 0 disables network debug

RETURNS:
    <none>    
******************************************************************/
void mdm_setNetworkDebugEnable (int mode);

/* ************************************************************************* 
	Module Routine: get_disconnect_reason()

	Returns the modem disconnect reason

	Parameters:
		<none>

	Returns:
		(unit16):  Modem disconnect reason
**************************************************************************** */
uint16 get_disconnect_reason(void);

/* ************************************************************************* */
/* ************************************************************************* */

void serial_console_rx(char);
uint16 serial_console_tx(void);

/* Functions to clear modem state machines (ingnore carrier loss and retraining) */
void fg_clear_all_states(void);
int read_num_fg_states (void);
void set_num_fg_states (int desired);

/* ************************************************************************* */
/* ************************************************************************* */
#endif /* _CX077_H */
