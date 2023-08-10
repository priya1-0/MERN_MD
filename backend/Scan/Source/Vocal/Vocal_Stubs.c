/************************************************************************
*
* MODULE: Vocal_Stubs.c
*
* OWNER: 
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: 
*
*************************************************************************/
#include "Vocal_Stubs.h"
#include "global.h"

/* Modem*/
char* mdm_Send_Control_String (unsigned int TimeoutTicks, char* command)
{
	char string[10];
    return string;
}

int mdm_Init(void)
{            
    return 1;
}

void mdm_Shut_Off(void)
{            
}

long mdm_Get_Connect_Speed(void)
{            
    return 1;
}

int mdm_Check_Dialtone(void)
{            
    return 1;
}


/* Terminal Mode*/
void mdm_Init_Term_Mode(void)
{
}

int mdm_Get_Char(int max, char* buffer)
{
    return 1;
}

void mdm_Purge_Input_Buffer(void)
{
}

int mdm_Send_String(int length, char* buffer)
{
    return 1;
}


/* Network - General */
int network_Init(int do_auth, char* username, char* password)
{
    return 1;
}

int network_ppp_auth_type(void)
{
    return 1;
}

/* HTTP*/
int http_Process_Request(http_request_data http_request)
{
	return 1;
}

