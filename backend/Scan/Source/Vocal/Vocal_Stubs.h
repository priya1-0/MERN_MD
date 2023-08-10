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
#ifndef _VOCAL_STUBS_H
#define _VOCAL_STUBS_H
#include "global.h"

/* Http return status */                                                 
#define HTTP_STATUS_OK			200	/* http 200 OK */
#define HTTP_STATUS_CREATED		201	/* http 201 Created */
#define HTTP_STATUS_ACCEPTED 	202	/* http 202 Accepted */
#define HTTP_STATUS_NO_CONTENT 	204	/* http 204 No Content */

#define HTTP_STATUS_MOVED_PERM	301	/* http 301 Moved Permanently */
#define HTTP_STATUS_MOVED_TEMP	302	/* http 302 Moved Temporarily */
#define HTTP_STATUS_NOT_MOD		304	/* http 304 Not Modified*/

#define HTTP_STATUS_BAD_REQUEST 400	/* http 400 Bad Request */
#define HTTP_STATUS_UNAUTH		401	/* http 401 Unauthorized or failed */
#define HTTP_STATUS_FORBIDDEN	403	/* http 403 Forbidden */
#define HTTP_STATUS_NOT_FOUND	404	/* http 404 Not Found */

#define HTTP_STATUS_SERVER_ERROR	500	/*http 500 Internal Server Error */
#define HTTP_STATUS_NOT_IMPL	501	/* http 501 Not Implemented */
#define HTTP_STATUS_BAD_GATEWAY	502	/* http 502 Bad Gateway */
#define HTTP_STATUS_SERVICE_UNAVAIL	503	/* http 503 Service Unavailable */

//* Additional return status */
#define HTTP_ERROR_PARAM		900	/* parameter error */
#define HTTP_ERROR_BUFFER		901	/* Return buffer too small */

#define HTTP_ERROR_NETWORK		902	/* network unreachable */
#define HTTP_ERROR_DNS_FAILED	903	/* DNS lookup failed */

/* return values for network_ppp_auth_type */
#define NET_PPP_AUTH_NONE		0
#define NET_PPP_AUTH_PAP		1
#define NET_PPP_AUTH_CHAP		2

/* Input type */
#define HTTP_INPUT_TYPE_FILE	0
#define HTTP_INPUT_TYPE_TEXTBOX	1

/* HTTP method types */
#define HTTP_METHOD_HEAD		0
#define HTTP_METHOD_GET			1
#define HTTP_METHOD_POST		2

/* HTTP version */
#define HTTP_V1_0				0
#define HTTP_V1_1				1

#define MAX_FORM_NAME_LEN		100
#define MAX_NUM_FORMS			10

typedef struct {
	char name[MAX_FORM_NAME_LEN];	/* Name of form */
	int	input_type;					/* Defined above (file or textbox) */
	long int length;				/* Length of value */ 
	int value_type;					/* Describes if data is 16bit or 8bit unpacked. */
	unsigned int *value;			/* Pointer to form data */ 
} form_struct;

typedef struct {
   /*Filled by Plexus as parameters*/
	unsigned int method_type;		/* defined above (get, post, head)*/
	unsigned int http_version;		/* defined above (1.0 or 1.1) */
	char* servername;				/* server name (www.123.com) null terminated */
	char* fileName;					/* Relative path and file name (\dir1\dir2\file.ext) */
	unsigned int portNumber;		/* Port number */
	form_struct* forms[MAX_NUM_FORMS]; /* form_struct defined above. Array of pointers to form structures. */
	unsigned int numForms;			/* Number of forms in forms array. */
	char* send_header;				/* Pointer to request header to be sent.  The request header consists of one or more null terminated strings. */
	unsigned int send_header_size;	/* Length of send_header. */
	char* userName;					/* null terminated user name for http basic auth, a null indicates that basic authentication will not be used */
	char* userPassword;				/* null terminated password for http basic auth*/	
	char* returnBuf;				/* Pointer to data that is returned as a result of a response. Pointer set by Plexus and passed as a parameter to VOCAL, data is placed into returnBuf by VOCAL */
	signed long returnBuf_max_size;	/* Maximum Length that the response can fill in returnBuf. */

   /*Filled by Vocal as return values*/
	signed long returnBuf_size;		/* Length of data placed in returnBuf by Vocal. Must be <= returnBuf_max_size or VOCAL returns HTTP_ERROR_BUFFER. */
	char* return_header;			/* Pointer to return header. */
	signed long return_header_size;	/* Length of return_header.  */
} http_request_data;

/* mdm_Init() return codes */
#define MDM_ERRORCODE__NO_ERROR							0
#define MDM_ERRORCODE__GENERAL							1
#define MDM_ERRORCODE__SYSTEM_INITIALIZATION			2
#define MDM_ERRORCODE__HARDWARE_RESET_FAILURE			3
#define MDM_ERRORCODE__HARDWARE_TIMEOUT					4
#define MDM_ERRORCODE__DSP_TIMER_FAILURE				5
#define MDM_ERRORCODE__DSPDRV_SETUP						6
#define MDM_ERRORCODE__DSPDRV_STARTUP					7
#define MDM_ERRORCODE__DTEIF_SETUP						8
#define MDM_ERRORCODE__DTEIF_STARTUP					9
#define MDM_ERRORCODE__DIAGNOSTIC_STARTUP				10
#define MDM_ERRORCODE__SYSTEM_CONFIGURATION				33
#define MDM_ERRORCODE__CTRL_BREAK_SEEN					34


/* Prototypes*/
/* Modem*/
char* mdm_Send_Control_String (unsigned int TimeoutTicks, char* command);
int mdm_Init(void);
void mdm_Shut_Off(void);
long mdm_Get_Connect_Speed(void);
int mdm_Check_Dialtone(void);

/* Terminal Mode API */
void mdm_Init_Term_Mode(void);
int mdm_Get_Char(int max, char* buffer);
void mdm_Purge_Input_Buffer (void);
int mdm_Send_String (int length, char* buffer);

/* Network API */
int network_Init (int do_auth, char* username, char* password);
int network_Get_PPP_Auth_Type (void);
int http_Process_Request (http_request_data req_data);

/* UART API */
/* ************************************************************************* */
/* ************************************************************************* */
#define UART_RECEIVED(x)		dteif_rx(x)
#define UART_GET_BYTE_TO_TX()	dteif_tx()
/* UART_GET_BYTE_TO_TX() will return UART_NO_DATA_AVAILABLE when no more data
 * is ready to be transmitted */
#define UART_NO_DATA_AVAILABLE	0x8000


#endif

