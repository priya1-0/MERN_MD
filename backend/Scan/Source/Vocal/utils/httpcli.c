
/* ************************************************************************* */
/*
 *	httpcli.c
 *
 *	(C) 1994 - 2006 VOCAL Technologies, Ltd.
 *
 *	ALL RIGHTS RESERVED.  PROPRIETARY AND CONFIDENTIAL.
 *
 *	VOCAL Technologies, Ltd.
 *	90A John Muir Drive.
 *	Buffalo, NY  14228
 *
 *	Product:	LANsEND
 *
 *	Module:		UTIL
 *
 *	This file contains the HTTP application programming interface functions.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.3  2010/02/16 23:18:36  heiand1
 *	Revision History:	SCR 186213. TCP Socket Connection Timing.
 *	Revision History:	
 *	Revision History:	Revision 1.1.24.2  2009/04/28 20:53:03  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#include "system/system.h"

#include "net/net.h"

#include "utils/httpcli.h"
#include "utils/local.h"

#define closesocket(s) close_s(s)

char far local_returnbuf[16384];
#define GETFILE_BUFF_SIZE 1500

const char *BOUNDARY_DELIMITER = "--";

#define	INADDR_NONE 0
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

uint16 HTTP_Append_Digest_Authorization_Hdr(http_request_data *http_rec);

/* ************************************************************************* */
/*
 *  Function: encode64
 *
 *  Performs Base46 encoding.
 *
 *  Parameters:
 *	a is pointer to string to be encoded
 *	b is pointer to encoded string
 *  Returns: (none)
 *
 */
ENTRY void
encode64 (char *a, char *b)
{
	char *code = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+-";
	for (;;) {
		uint32 c1 = *a++, c2, c3, w;
		if (c1 == 0) break;
		if ((c2 = *a++) == 0) {
				*b++= code[(c1 >> 2) & 0x3f];
				*b++= code[(c1 << 4) & 0x3f];
				*b++= '=';
				*b++= '=';
				break;
		}
		if ((c3 = *a++) == 0) {
				w = (c1 << 16) | (c2 << 8);
				*b++= code[(w >> 18) & 0x3f];
				*b++= code[(w >> 12) & 0x3f];
				*b++= code[(w >> 6) & 0x3f];
				*b++= '=';
				break;
		}
		w = (c1 << 16) | (c2 << 8) | c3;
		*b++= code[(w >> 18) & 0x3f];
		*b++= code[(w >> 12) & 0x3f];
		*b++= code[(w >> 6) & 0x3f];
		*b++= code[w & 0x3f];
	}
	*b = 0;
}

/* ************************************************************************* */
/*
 *  Function: http_timeout
 *
 *  HTTP timeout protectionfunction
 *
 *  Parameters:
 *	Pointer to process waiting for http request
 *
 *  Returns: void
 *
 */
ENTRY void
http_timeout (void *process)
{
	struct proc *pp = (struct proc *) process;
	alert (pp, ETIMEOUT);
}

/* ************************************************************************* */
/*
 *  Function: http_process_request
 *
 *  HTTP request function that performs GET and POST.
 *
 *  Parameters:
 *	http_request_data structure contains all needed info
 *
 *  Returns: a status code
  *
 */
ENTRY int
http_process_request (http_request_data *http_data)
{
	struct sockaddr saServer;
	int http_socket;
	sint31 nRet, m, body_length;
	sint31 remaining_send_size, send_size, read_size, total_read_size, i, j, k;
	volatile int retcode = 0;
	int header_found = FALSE;
	uint32 tempbuf_p, returnbuf_p;
	sint31 chars_remaining = 0;

	struct timer timeout_protection;
	char temp_print_buffer[32];

	/* Initialize timeout protection function */
	timeout_protection.duration = http_data->timeout;
	timeout_protection.func = http_timeout;
	timeout_protection.arg = (void *) Curproc;
	timeout_protection.state = TIMER_STOP;
	set_timer (&timeout_protection, timeout_protection.duration);

	/* Init Some values */
	http_data->return_body_size = 0;
	http_data->return_header_size = 0;
	http_data->return_header = NULL;
	http_data->return_body = NULL;
	returnbuf_p = (uint32) http_data->returnbuf;
	*(char*) returnbuf_p = '\0';

	/* ****************************** */
/*	printf("\n------------------------------------------------");
	printf("\n------------------IN----------------------------");
	printf("\nmethod_type %d", http_data->method_type);
	printf("\nhttp_version %d", http_data->http_version);
	printf("\nservername %s", http_data->servername);
	printf("\nfilename %s", http_data->filename);
	printf("\nportnumber %d", http_data->portnumber);
	printf("\nnumforms %d", http_data->numforms);
	printf("\ndisposition_boundary_tag %s", http_data->disposition_boundary_tag);

	for (i = 0; i < http_data->numforms; i++) {
		printf("\n forms[%d] %ld", i, http_data->forms[i]);
	}

	printf("\nsend_header %s", http_data->send_header);
	printf("\nsend_header_size %ld", http_data->send_header_size);
	printf("\nuser_name %s", http_data->user_name);
	printf("\nuser_password %s", http_data->user_password);
	printf("\nreturnbuf %ld", http_data->returnbuf);
	printf("\nreturnbuf_max_size %ld", http_data->returnbuf_max_size);
	printf("\nreturn_type %d", http_data->return_type);
	printf("\nreturnbuf_size %ld", http_data->returnbuf_size);
	printf("\nreturn_header %ld", http_data->return_header);
	printf("\nreturn_body %ld", http_data->return_body);
	printf("\nreturn_header_size %ld",http_data->return_header_size);
	printf("\nreturn_body_size %ld", http_data->return_body_size);
	printf("\ntimeout %d", http_data->timeout);
	printf("\n------------------------------------------------");
*/	/* ****************************** */

	printf("Resolving %s...\n", http_data->servername);
	fflush (stdout);

	if (atos_err (http_data->servername, AF_INET, &saServer)) {
		print_error (("httpcli() - gethostbyname()\n"));
		return (HTTP_ERROR_NETWORK);
	}

	http_socket = socket (AF_INET, SOCK_STREAM, 0);
	if (http_socket == INVALID_SOCKET)
	{
		print_error (("httpcli() - socket()\n"));
		return (HTTP_ERROR_NETWORK);
	}

	/* Set the port number for the HTTP service */
	saServer.sin_port = http_data->portnumber;


	switch (http_data->method_type) {
	case HTTP_METHOD_GET:

		/* Format the HTTP request */

		large_buf_strcat(returnbuf_p, "GET /", http_data->returnbuf_max_size);
		large_buf_strcat (returnbuf_p, http_data->filename, http_data->returnbuf_max_size);
		large_buf_strcat(returnbuf_p, " ", http_data->returnbuf_max_size);

		/* Version Number */
		if (http_data->http_version == HTTP_V1_0) {
			large_buf_strcat(returnbuf_p, "HTTP/1.0", http_data->returnbuf_max_size);
			large_buf_strcat (returnbuf_p, CRLF_STRING, http_data->returnbuf_max_size);
		}
		if (http_data->http_version == HTTP_V1_1) {
			large_buf_strcat(returnbuf_p, "HTTP/1.1", http_data->returnbuf_max_size);
			large_buf_strcat (returnbuf_p, CRLF_STRING, http_data->returnbuf_max_size);
		}

		/* Rest of HTTP header */
		if (http_data->send_header != NULL) {
			large_buf_strcat (returnbuf_p, http_data->send_header, http_data->returnbuf_max_size);
		}

		/* Digest Authentication */
		if (http_data->digest->isReadyToAuthenticate) {
			http_data->digest_header_size += HTTP_Append_Digest_Authorization_Hdr (http_data);

			if(http_data->digest_header != NULL) {
				large_buf_strcat(returnbuf_p, http_data->digest_header, http_data->returnbuf_max_size);
				large_buf_strcat(returnbuf_p, CRLF_STRING, http_data->returnbuf_max_size);
			}
		}

		/* Denotes end of Header */
		large_buf_strcat (returnbuf_p, CRLF_STRING, http_data->returnbuf_max_size);

		/* Get Length of what to send */
		i = large_buf_strlen (returnbuf_p);

		break;

	case HTTP_METHOD_POST:

		/* Start of HTTP header */
		large_buf_strcat(returnbuf_p, "POST ", http_data->returnbuf_max_size);
		large_buf_strcat (returnbuf_p, http_data->filename, http_data->returnbuf_max_size);
		large_buf_strcat(returnbuf_p, " ", http_data->returnbuf_max_size);

		/* Version Number */
		if (http_data->http_version == HTTP_V1_0) {
			large_buf_strcat(returnbuf_p, "HTTP/1.0", http_data->returnbuf_max_size);
			large_buf_strcat (returnbuf_p, CRLF_STRING, http_data->returnbuf_max_size);
		}
 		if (http_data->http_version == HTTP_V1_1) {
			large_buf_strcat(returnbuf_p, "HTTP/1.1", http_data->returnbuf_max_size);
			large_buf_strcat (returnbuf_p, CRLF_STRING, http_data->returnbuf_max_size);
		}

		/* Rest of HTTP header */
		if (http_data->send_header != NULL) {
			large_buf_strcat (returnbuf_p, http_data->send_header, http_data->returnbuf_max_size);
		}

		if (http_data->disposition_boundary_tag != NULL) {
			large_buf_strcat(returnbuf_p, "Content-Type: multipart/form-data; boundary=", http_data->returnbuf_max_size);
			large_buf_strcat (returnbuf_p, http_data->disposition_boundary_tag, http_data->returnbuf_max_size);
			large_buf_strcat (returnbuf_p, CRLF_STRING, http_data->returnbuf_max_size);
			large_buf_strcat(returnbuf_p, "Content-Encoding: multipart/form-data", http_data->returnbuf_max_size);
			large_buf_strcat (returnbuf_p, CRLF_STRING, http_data->returnbuf_max_size);
		}

		/* Content Length */
		body_length = 0;
		if (http_data->numforms > 0) {
			for (j = 0; j < http_data->numforms; j++) {
				if (http_data->disposition_boundary_tag != NULL) {
					if (http_data->forms[j]->input_type == HTTP_INPUT_TYPE_TEXTBOX) {
						if (http_data->forms[j]->name != NULL) {
							body_length += http_data->forms[j]->name_length;
							body_length++; /* increment one for the delimiter '=' */

							/* add the length of the ending characters (CRLF) */
							body_length += strlen (CRLF_STRING);
						}
					}
					else if (http_data->forms[j]->input_type == HTTP_INPUT_TYPE_FILE) {
						body_length += strlen (BOUNDARY_DELIMITER);
						body_length += strlen (http_data->disposition_boundary_tag);
						body_length += strlen (CRLF_STRING);

						body_length += strlen ("Content-Disposition: form-data; name=\"");
						body_length += strlen (http_data->forms[j]->name);
						body_length += strlen ("\"");

							/* file_name is optional */
						if (http_data->forms[j]->file_name != NULL) {
							/* a string that starts with a semicolon will be replaced with a
							space due to a compiler bug, but the stringlen will be correct */
							body_length += strlen ("; filename=\"");
							body_length += strlen (http_data->forms[j]->file_name);
							body_length += strlen ("\"");
						}
						body_length += strlen (CRLF_STRING);
						body_length += strlen ("Content-Type: application/octet-stream");
						body_length += strlen (CRLF_STRING);
						body_length += strlen (CRLF_STRING);

						body_length += http_data->forms[j]->length;

						body_length += strlen (CRLF_STRING);
						body_length += strlen (BOUNDARY_DELIMITER);
						body_length += strlen (http_data->disposition_boundary_tag);
						body_length += strlen (BOUNDARY_DELIMITER);

						/* add the length of
						 * the ending
						 * characters (CRLF) */
						body_length += strlen (CRLF_STRING);
					}
					else if (http_data->forms[j]->input_type == HTTP_INPUT_TYPE_NONE) {
					}
				}
				else {
					if (http_data->forms[j]->input_type == HTTP_INPUT_TYPE_TEXTBOX) {
						if (http_data->forms[j]->name != NULL) {
							body_length += http_data->forms[j]->name_length;
							body_length++; /* increment one for the delimiter '=' */
							body_length += http_data->forms[j]->length;
							if (j > 0) {
								body_length++; /* increment one for the delimiter '&' between text forms*/
							}
						}

					}
				}
			}
			large_buf_strcat(returnbuf_p, "Content-Length: ", http_data->returnbuf_max_size);
			generic_sprintf(temp_print_buffer,"%ld%s",(long)body_length,CRLF_STRING);
			large_buf_strcat (returnbuf_p, temp_print_buffer, http_data->returnbuf_max_size);
		}

		/* Digest Authentication */
		if (http_data->digest->isReadyToAuthenticate) {
			http_data->digest_header_size += HTTP_Append_Digest_Authorization_Hdr(http_data);

			if (http_data->digest_header != NULL) {
				large_buf_strcat (returnbuf_p, http_data->digest_header, http_data->returnbuf_max_size);
				large_buf_strcat (returnbuf_p, CRLF_STRING, http_data->returnbuf_max_size);
			}
		}

		/* Denoted end of Header */
		large_buf_strcat (returnbuf_p, CRLF_STRING, http_data->returnbuf_max_size);

		i = large_buf_strlen (returnbuf_p);

		/* Form data inserted here */
		for (j = 0; j < http_data->numforms; j++) {

			if (http_data->disposition_boundary_tag != NULL)
			{
				/* check for valid input type */
				if (http_data->forms[j]->input_type == HTTP_INPUT_TYPE_TEXTBOX ||
				   http_data->forms[j]->input_type == HTTP_INPUT_TYPE_FILE)
				{
					/* common to both textbox and file types*/
					large_buf_strcat (returnbuf_p, BOUNDARY_DELIMITER, http_data->returnbuf_max_size);
					large_buf_strcat (returnbuf_p, http_data->disposition_boundary_tag, http_data->returnbuf_max_size);
					large_buf_strcat (returnbuf_p, CRLF_STRING, http_data->returnbuf_max_size);

					large_buf_strcat(returnbuf_p, "Content-Disposition: form-data; name=\"", http_data->returnbuf_max_size);
					large_buf_strcat (returnbuf_p, http_data->forms[j]->name, http_data->returnbuf_max_size);
					large_buf_strcat(returnbuf_p, "\"", http_data->returnbuf_max_size);

					/* specific to filetype */
					if (http_data->forms[j]->input_type == HTTP_INPUT_TYPE_FILE)
					{
						if (http_data->forms[j]->file_name != NULL) {
							{
								/* this is a workaround to fix a compiler bug,
									a string cannot start with a semicolon */
								sint31 semicolon_pointer = returnbuf_p;
								while (*((char *) semicolon_pointer) != 0) {
									semicolon_pointer++;
								}
								*((char *) semicolon_pointer) = ';';
								semicolon_pointer++;
								*((char *) semicolon_pointer) = 0;
							}
							large_buf_strcat(returnbuf_p, " filename=\"", http_data->returnbuf_max_size);
							large_buf_strcat (returnbuf_p, http_data->forms[j]->file_name, http_data->returnbuf_max_size);
							large_buf_strcat(returnbuf_p, "\"", http_data->returnbuf_max_size);
							large_buf_strcat (returnbuf_p, CRLF_STRING, http_data->returnbuf_max_size);
						}
						else {
							large_buf_strcat (returnbuf_p, CRLF_STRING, http_data->returnbuf_max_size);
						}
						large_buf_strcat(returnbuf_p, "Content-Type: application/octet-stream", http_data->returnbuf_max_size);
					}
					/* specific to textbox type */
					else if (http_data->forms[j]->input_type == HTTP_INPUT_TYPE_TEXTBOX) {
						/* None */
					}
					large_buf_strcat (returnbuf_p, CRLF_STRING, http_data->returnbuf_max_size);
					large_buf_strcat (returnbuf_p, CRLF_STRING, http_data->returnbuf_max_size);
					i = large_buf_strlen (returnbuf_p);
				}
			}
			else {
				if (http_data->forms[j]->input_type == HTTP_INPUT_TYPE_TEXTBOX) {
					if (http_data->forms[j]->name != NULL) {
						if (j > 0) {
							large_buf_strcat(returnbuf_p, "&", http_data->returnbuf_max_size);
						}
						large_buf_strcat (returnbuf_p, http_data->forms[j]->name, http_data->returnbuf_max_size);
						large_buf_strcat(returnbuf_p, "=", http_data->returnbuf_max_size);
						i = large_buf_strlen (returnbuf_p);
					}
				}
			}

			/* Check the packing type of the data*/
			if (http_data->forms[j]->value_type == HTTP_FORM_VALUE_TYPE_16) {
				for (k = 0; k < http_data->forms[j]->length; k++, i++) {
					tempbuf_p = (uint32) http_data->forms[j]->value;
					*((char*) (returnbuf_p + i)) = *((char*) (tempbuf_p + k));
				}
			}
			else if (http_data->forms[j]->value_type == HTTP_FORM_VALUE_TYPE_8_PACKED_LOW) {
				/* unpack packed data (2 8-bit values are packed into one 16-bit value) */
				for (k = 0; k < http_data->forms[j]->length; k++, i++) {
					if (k & 1) {
						tempbuf_p = (uint32) http_data->forms[j]->value;
						*((char*) (returnbuf_p + i)) = (*((char*) (tempbuf_p + k / 2)) >> 8) & 0xFF;
					}
					else {
						tempbuf_p = (uint32) http_data->forms[j]->value;
						*((char*) (returnbuf_p + i)) = (*((char*) (tempbuf_p + k / 2)) >> 0) & 0xFF;
					}
				}
			}
			else if (http_data->forms[j]->value_type == HTTP_FORM_VALUE_TYPE_8_PACKED_HIGH) {
				/* unpack packed data (2 8-bit values are packed into one 16-bit value) */
				for (k = 0; k < http_data->forms[j]->length; k++, i++) {
					if (k & 1) {
						tempbuf_p = (uint32) http_data->forms[j]->value;
						*((char*) (returnbuf_p + i)) = (*((char*) (tempbuf_p + k / 2)) >> 0) & 0xFF;
					}
					else {
						tempbuf_p = (uint32) http_data->forms[j]->value;
						*((char*) (returnbuf_p + i)) = (*((char*) (tempbuf_p + k / 2)) >> 8) & 0xFF;
					}
				}
			}

			if (http_data->disposition_boundary_tag != NULL) {
				large_buf_strcpy (returnbuf_p + i, CRLF_STRING, http_data->returnbuf_max_size);
				i += strlen (CRLF_STRING);

				large_buf_strcpy (returnbuf_p + i, BOUNDARY_DELIMITER, http_data->returnbuf_max_size);
				i += strlen (BOUNDARY_DELIMITER);

				large_buf_strcpy (returnbuf_p + i, http_data->disposition_boundary_tag, http_data->returnbuf_max_size);
				i += strlen (http_data->disposition_boundary_tag);

				large_buf_strcpy (returnbuf_p + i, BOUNDARY_DELIMITER, http_data->returnbuf_max_size);
				i += strlen (BOUNDARY_DELIMITER);

				large_buf_strcpy (returnbuf_p + i, CRLF_STRING, http_data->returnbuf_max_size);
				i += strlen (CRLF_STRING);

			}
			else {
				*((char*) (returnbuf_p + i)) = 0;
			}

		}
		break;

	default:
		break;
	}

	/* Connect the socket */
	start_timer (&timeout_protection);
	nRet = connect (http_socket, (char *) &saServer, sizeof (saServer));
	stop_timer (&timeout_protection);
	if (nRet == SOCKET_ERROR)
	{
		print_error (("httpcli() - connect()\n"));
		closesocket (http_socket);

		if (errno == ETIMEOUT) {
			return (HTTP_ERROR_NETWORK_TIMEOUT);
		}
		else {
			return (HTTP_ERROR_NETWORK);
		}
	}
	/* ensure connect packet has gone out before contining */ 
	pwait(NULL);


	/*Send Loop */
	remaining_send_size = i;
	tempbuf_p = returnbuf_p;
	while (1) {

		if (remaining_send_size > 16384) {
			send_size = 16384;
		}
		else {
			send_size = remaining_send_size;
		}

		if (((tempbuf_p + send_size) % 0x010000) < send_size) {
			send_size -= (tempbuf_p + send_size) % 0x010000;
		}

		pwait(NULL);

		start_timer (&timeout_protection);
		nRet = send (http_socket, (char*) tempbuf_p, send_size, 0);
		stop_timer (&timeout_protection);

		tempbuf_p += nRet;

		if (nRet == SOCKET_ERROR)
		{
			print_error (("httpcli() - send()\n"));
			closesocket (http_socket);

			if (errno == ETIMEOUT) {
				return (HTTP_ERROR_NETWORK_TIMEOUT);
			}
			else {
				return (HTTP_ERROR_NETWORK);
			}
		}

		remaining_send_size -= nRet;

		if (remaining_send_size == 0) {
			break;
		}

	}

	/* Receive response header and contents, print to stdout */
	http_data->returnbuf_size = 0;
	total_read_size = http_data->returnbuf_max_size;

	k = 0;

	while (1) {

		read_size = 16384;

		if (total_read_size <= 0) {
			print_error (("httpcli() - buffer_error, total_read_size = %ld\n", (long)total_read_size));
			return (HTTP_ERROR_BUFFER);
		}

		/* Wait to receive, nRet = Number Of Bytes Received */
		/* Wait to receive, nRet = Number Of Bytes Received */
		start_timer (&timeout_protection);
		nRet = recv (http_socket, (char*) local_returnbuf, read_size, 0);
		stop_timer (&timeout_protection);
		if (nRet == SOCKET_ERROR) {
			print_error (("httpcli() - recv()\n"));
			closesocket (http_socket);

			if (errno == ETIMEOUT) {
				return (HTTP_ERROR_NETWORK_TIMEOUT);
			}
			else {
				return (HTTP_ERROR_NETWORK);
			}
		}
		if (nRet == 0) {
			break;
		}

		start_timer (&timeout_protection);
		nRet += recv (http_socket, (char*) &local_returnbuf[nRet], read_size - nRet, 0);
		stop_timer (&timeout_protection);
		if (nRet == SOCKET_ERROR) {
			print_error (("httpcli() - recv()\n"));
			closesocket (http_socket);

			if (errno == ETIMEOUT) {
				return (HTTP_ERROR_NETWORK_TIMEOUT);
			}
			else {
				return (HTTP_ERROR_NETWORK);
			}
		}

		http_data->returnbuf_size += nRet;
		total_read_size -= nRet;

		if (!header_found) {
			/* Seperate response header from rest of body */
			if (!strncmp(&local_returnbuf[0], "HTTP/", 5)) {
				while (k < http_data->returnbuf_size) {
					int count_found = 0;

					if (!strncmp(&local_returnbuf[k], "\n\n", 2)) {
						count_found =  2;
					}
					if (!strncmp(&local_returnbuf[k], "\r\n\r\n", 4)) {
						count_found =  4;
					}
					if (count_found) {
						header_found = TRUE;
						http_data->return_header = (char*) returnbuf_p;

						/* Copy Header*/
						http_data->return_header_size = k;
						for (m = 0; m < http_data->return_header_size; m++) {
							*((char*) returnbuf_p) = local_returnbuf[m];
							returnbuf_p++;
						}
						/* null terminate */
						*((char*) returnbuf_p) = 0;
						returnbuf_p++;
						http_data->return_body = (char*) returnbuf_p;

						/* copy body */
						http_data->returnbuf_size -= count_found;
						chars_remaining = http_data->returnbuf_size - http_data->return_header_size;
						for (m = 0; m < chars_remaining; m++) {
							/* unpacked - only low 8 bits used */
							if (http_data->return_type == HTTP_FORM_VALUE_TYPE_16) {
								*((char*) returnbuf_p) = local_returnbuf[(http_data->return_header_size + count_found) + m];
								http_data->return_body_size++;
								returnbuf_p++;
							}
							/* packed high byte first */
							if (http_data->return_type == HTTP_FORM_VALUE_TYPE_8_PACKED_HIGH) {
								if ((http_data->return_body_size & 1) == 0) {
									*((char*) returnbuf_p) = (local_returnbuf[(http_data->return_header_size + count_found) + m] & 0x00ff) << 8;
									http_data->return_body_size++;

								} else {
									*((char*) returnbuf_p) = *((char*) returnbuf_p) | (local_returnbuf[(http_data->return_header_size + count_found) + m] & 0x00ff);
									http_data->return_body_size++;
									returnbuf_p++;
								}
							}
							/* packed low byte first */
							if (http_data->return_type == HTTP_FORM_VALUE_TYPE_8_PACKED_LOW) {
								if ((http_data->return_body_size & 1) == 0) {
									*((char*) returnbuf_p) = local_returnbuf[(http_data->return_header_size + count_found) + m] & 0x00ff;
									http_data->return_body_size++;

								} else {
									*((char*) returnbuf_p) = *((char*) returnbuf_p) | ((local_returnbuf[(http_data->return_header_size + count_found) + m] & 0x00ff) << 8);
									http_data->return_body_size++;
									returnbuf_p++;
								}
							}
						}
						break;
					}
					k++;
				}
			}
		}
		else {
			/* copy body */
			for (m = 0; m < nRet; m++) {
				/* unpacked - only low 8 bits used */
				if (http_data->return_type == HTTP_FORM_VALUE_TYPE_16) {
					*((char*) returnbuf_p) = local_returnbuf[m];
					http_data->return_body_size++;
					returnbuf_p++;
				}
				/* packed high byte first */
				if (http_data->return_type == HTTP_FORM_VALUE_TYPE_8_PACKED_HIGH) {
					if ((http_data->return_body_size & 1) == 0) {
						*((char*) returnbuf_p) = (local_returnbuf[m] & 0x00ff) << 8;
						http_data->return_body_size++;

					} else {
						*((char*) returnbuf_p) = *((char*) returnbuf_p) | (local_returnbuf[m] & 0x00ff);
						returnbuf_p++;
						http_data->return_body_size++;
					}
				}
				/* packed low byte first */
				if (http_data->return_type == HTTP_FORM_VALUE_TYPE_8_PACKED_LOW) {
					if ((http_data->return_body_size & 1) == 0) {
						*((char*) returnbuf_p) = (local_returnbuf[m] & 0x00ff);
						http_data->return_body_size++;
					} else {
						*((char*) returnbuf_p) = *((char*) returnbuf_p) | ((local_returnbuf[m] & 0x00ff) << 8);
						returnbuf_p++;
						http_data->return_body_size++;
					}
				}
			}
		}
		pwait(NULL);
	}

	if ((http_data->return_type == HTTP_FORM_VALUE_TYPE_8_PACKED_LOW  ||
		 http_data->return_type == HTTP_FORM_VALUE_TYPE_8_PACKED_HIGH) &&
		(http_data->return_body_size & 1) == 1)
	{
		returnbuf_p++;/* increment to the next word (part of current word is used by body) */
	}

	*((char*)returnbuf_p) = 0; /*add a null */
	closesocket (http_socket);
	/* Release WinSock */
	/* Release WinSock */

	/* ****************************** */
/*	printf("\n------------------------------------------------");
	printf("\n------------------OUT---------------------------");
	printf("\nmethod_type %d", http_data->method_type);
	printf("\nhttp_version %d", http_data->http_version);
	printf("\nservername %s", http_data->servername);
	printf("\nfilename %s", http_data->filename);
	printf("\nportnumber %d", http_data->portnumber);
	printf("\nnumforms %d", http_data->numforms);
	printf("\ndisposition_boundary_tag %s", http_data->disposition_boundary_tag);

	for (i = 0; i < http_data->numforms; i++) {
		printf("\n forms[%d] %ld", i, http_data->forms[i]);
	}

	printf("\nsend_header %s", http_data->send_header);
	printf("\nsend_header_size %ld", http_data->send_header_size);
	printf("\nuser_name %s", http_data->user_name);
	printf("\nuser_password %s", http_data->user_password);
	printf("\nreturnbuf %ld", http_data->returnbuf);
	printf("\nreturnbuf_max_size %ld", http_data->returnbuf_max_size);
	printf("\nreturn_type %d", http_data->return_type);
	printf("\nreturnbuf_size %ld", http_data->returnbuf_size);
	printf("\nreturn_header %ld", http_data->return_header);
	printf("\nreturn_body %ld", http_data->return_body);
	printf("\nreturn_header_size %ld",http_data->return_header_size);
	printf("\nreturn_body_size %ld", http_data->return_body_size);
	printf("\ntimeout %d", http_data->timeout);
	printf("\n------------------------------------------------");
*/	/* ****************************** */

	/* Parse response status */
	if (header_found) {
		int major, minor;
/*		if (sscanf(http_data->return_header, "HTTP/%d.%d %d", &major, &minor, &retcode) != 3 ||
			retcode < 0 || retcode > 999) {
			return (HTTP_ERROR_BAD_RETURN);
		}*/
		if (sscanf(http_data->return_header, "HTTP/%d.%d %d", &major, &minor, &retcode) != 3) {
			print_error(("\n!retcode_1 = %d!\n",retcode));
			return (HTTP_ERROR_BAD_RETURN);
		}
		if (retcode < 0 || retcode > 999) {
			print_error(("\n!retcode_2 = %d!\n",retcode));
			return (HTTP_ERROR_BAD_RETURN);
		}
		else {
			return (retcode);
		}
	}
	else {
		print_error(("\n!retcode_4 = %d!\n",retcode));
		return (HTTP_NO_HEADER);
	}

}

/* ************************************************************************* */
/*
 *  Function: http_get_file
 *
 *  HTTP request function that performs GET to a file.
 *  This is a simpler version of the http_process_Request function that only does
 *  gets and does not concern itself with oversized buffers, assumes that the request
 *  can be put in a single small buffer, and that the results will be read back into
 *  a file.
 *
 *  Parameters:
 *	http_request_data structure contains all needed info
 *
 *  Returns: a status code
  *
 */

ENTRY int
http_get_file (http_request_data *http_data)
{

	struct sockaddr saServer;
	int http_socket;
	sint31 remaining_send_size, send_size, i;
	volatile int retcode = 0;
	int header_found = FALSE;
	char *returnbuf_p, *tempbuf_p, *tmp_p, *data_p;
	sint31 numwritten = 0;
	FILE *fp = NULLFILE;
	uint16 space_avail;
	uint32 chars_read  = 0;
	uint32 content_length;
	int nRet;
	char httpauth[64], httpauth64[64];
	struct timer timeout_protection;

	/* Initialize timeout protection function */
	timeout_protection.duration = http_data->timeout;
	timeout_protection.func = http_timeout;
	timeout_protection.arg = (void *) Curproc;
	timeout_protection.state = TIMER_STOP;
	set_timer (&timeout_protection, timeout_protection.duration);

	/* Init Some values */
	http_data->return_body_size = 0;
	http_data->return_header_size = 0;
	http_data->return_header = NULL;
	http_data->return_body = NULL;
	returnbuf_p = http_data->returnbuf;
	*returnbuf_p = '\0';

	/* Set the port number for the HTTP service */
	saServer.sin_port = http_data->portnumber;

	if (atos_err (http_data->servername, AF_INET, &saServer)) {
		print_error ((" http_get_file() - gethostbyname()\n"));
		return (HTTP_ERROR_NETWORK);
	}

	http_socket = socket (AF_INET, SOCK_STREAM, 0);
	if (http_socket == INVALID_SOCKET)
	{
		print_error ((" http_get_file() - socket()\n"));
		return (HTTP_ERROR_NETWORK);
	}

	/* Connect the socket */
	start_timer (&timeout_protection);
	nRet = connect (http_socket, (char *) &saServer, sizeof (saServer));
	stop_timer (&timeout_protection);
	if (nRet == SOCKET_ERROR)
	{
		print_error ((" http_get_file() - connect()\n"));
		closesocket (http_socket);

		if (errno == ETIMEOUT) {
			return (HTTP_ERROR_NETWORK_TIMEOUT);
		}
		else {
			return (HTTP_ERROR_NETWORK);
		}
	}

	switch (http_data->method_type) {
	case HTTP_METHOD_GET:
		/* Format the HTTP request */

		generic_strncat(returnbuf_p, "GET /", http_data->returnbuf_max_size);
		generic_strncat (returnbuf_p, http_data->filename, http_data->returnbuf_max_size);
		generic_strncat(returnbuf_p, " ", http_data->returnbuf_max_size);

		/* Version Number */
		if (http_data->http_version == HTTP_V1_0) {
			generic_strncat(returnbuf_p, "HTTP/1.0\r\n", http_data->returnbuf_max_size);
		}
		if (http_data->http_version == HTTP_V1_1) {
			generic_strncat(returnbuf_p, "HTTP/1.1\r\n", http_data->returnbuf_max_size);
		}

		/* Rest of HTTP header */
		if (http_data->send_header != NULL) {
			generic_strncat (returnbuf_p, http_data->send_header, http_data->returnbuf_max_size);
		}

		/* Basic Authentication */
		if (http_data->user_name != NULL && http_data->user_password != NULL) {
			generic_sprintf(httpauth, "%s:%s", http_data->user_name, http_data->user_password);
			encode64 (httpauth, httpauth64);
			generic_strncat(returnbuf_p,"Authorization: Basic ", http_data->returnbuf_max_size);
			generic_strncat (returnbuf_p, httpauth64, http_data->returnbuf_max_size);
			generic_strncat (returnbuf_p, CRLF_STRING, http_data->returnbuf_max_size);
		}

		/* Denotes end of Header */
		generic_strncat (returnbuf_p, CRLF_STRING, http_data->returnbuf_max_size);

		/* Get Length of what to send */
		i = strlen (returnbuf_p);

		break;

	case HTTP_METHOD_POST:
	default:
		print_error((" http_get_file() UNSUPORTED HTTP CASE\n"));
		fflush (stdout);
	}

	/*Send Loop */
	remaining_send_size = i;
	tempbuf_p = returnbuf_p;
	nRet = 0;

	while (1) {

		send_size = remaining_send_size;

		start_timer (&timeout_protection);
		nRet = send (http_socket, (char*) tempbuf_p, send_size, 0);
		stop_timer (&timeout_protection);

		tempbuf_p += nRet;

		if (nRet == SOCKET_ERROR)
		{
			print_error ((" http_get_file() - send()\n"));
			closesocket (http_socket);

			if (errno == ETIMEOUT) {
				return (HTTP_ERROR_NETWORK_TIMEOUT);
			}
			else {
				return (HTTP_ERROR_NETWORK);
			}
		}

		remaining_send_size -= nRet;

		if (remaining_send_size == 0) {
			break;
		}

	}

	/* Receive response header and contents, print to stdout */
	http_data->returnbuf_size = 0;

	returnbuf_p = http_data->returnbuf;
	space_avail = (uint16) http_data->returnbuf_max_size;
	chars_read  = 0;

	while (1) {

		/* Wait to receive, nRet = Number Of Bytes Received */
		start_timer (&timeout_protection);
		nRet = recv (http_socket, (char*) returnbuf_p, (space_avail - 1), 0);
		stop_timer (&timeout_protection);
		printf (".");

		if (nRet == SOCKET_ERROR) {
			closesocket (http_socket);

			if (errno == ETIMEOUT) {
				print_error ((" http_get_file() - HTTP_ERROR_NETWORK_TIMEOUT\n"));
				fclose (fp);
				return (HTTP_ERROR_NETWORK_TIMEOUT);
			}
			else {
				print_error ((" http_get_file() - HTTP_NO_HEADER 1\n"));
				pause(2000L);
				fclose (fp);
				return (HTTP_ERROR_NETWORK);
			}
		}

		if (nRet == 0) {
			break;
		};

		if (!header_found) {
			chars_read += nRet;
			returnbuf_p[nRet] = 0;
			returnbuf_p += nRet;
			space_avail -= nRet;

			/* this parsing is minimal - it could be made much more robust to deal with general servers */
			if (strstr(http_data->returnbuf,"\r\n") || strstr(http_data->returnbuf,"\n")) {
				if (!strstr(http_data->returnbuf,"HTTP/")) {
					fclose (fp);
					closesocket (http_socket);
					print_error((" http_get_file() - HTTP_NO_HEADER 2\n"));
					pause(2000L);
					return (HTTP_NO_HEADER);
				}

				/* If we don't get a 200 tough luck */
				if (!strstr(http_data->returnbuf,"200")) {
					fclose (fp);
					closesocket (http_socket);
					print_error((" http_get_file() - HTTP_ERROR_BAD_RETURN\n"));
					return (HTTP_ERROR_BAD_RETURN);
				}

				/* We may want to deal with \n\r\n\r for Macs as well */
				if (tmp_p = strstr(http_data->returnbuf,"\r\n\r\n")) {
					header_found = 1;
					data_p = tmp_p + 4;
				}
				else if (tmp_p = strstr(http_data->returnbuf,"\n\n")) {
					header_found = 1;
					data_p = tmp_p + 2;
				}

				if (header_found) {
					/* If we don't get a content-length, tough luck */
					/* This should be case -insensitive etc */
					tmp_p = generic_stristr(http_data->returnbuf,"content-length:");
					if (!tmp_p) {
						fclose (fp);
						closesocket (http_socket);
						print_error((" http_get_file() - HTTP_NO_HEADER 3\n"));
						pause(2000L);
						return (HTTP_NO_HEADER);
					}

					/* move past tag and look for length */
					tmp_p += 15;
					while (tmp_p < data_p) {
						if (*tmp_p >= 0x30 && *tmp_p <= 0x39) {
							/* found a number */
							break;
						}
						tmp_p++;
					}
				   content_length = generic_atol(tmp_p);
				   printf("opening %s \n",http_data->localname);
				   fp = fopen(http_data->localname,"w+b");
				   if (!fp) {
					   print_error((" http_get_file() - cannot open file\n"));
					   closesocket (http_socket);
				   }
				   numwritten = fwrite (data_p, sizeof (char), chars_read - (data_p - http_data->returnbuf), fp);

				   returnbuf_p = http_data->returnbuf;
				   space_avail = http_data->returnbuf_max_size;

				}
			}

		} else {
			chars_read += nRet;
			returnbuf_p[nRet] = 0;
			space_avail = http_data->returnbuf_max_size;

			numwritten += fwrite (returnbuf_p, sizeof (char), nRet, fp);

			if (numwritten >= content_length) {
				stop_timer (&timeout_protection);
				fclose (fp);
				break;
			}
		}
	}
	print_info (("\nhttp_get_file() - closing file\n"));
	stop_timer (&timeout_protection);
	pause (100L);
	fclose (fp);

	print_info (("\nhttp_get_file() - closing socket\n"));
	closesocket (http_socket);
	/* Release WinSock */

	return (HTTP_STATUS_OK);

}

#define HTTP_RETURN_BUFFER_SIZE		16024
#define HTTP_RETURN_HEADER_SIZE		512

#ifdef TEST_HTTP
/* ************************************************************************* */
/*
 *  Function: http_main
 *
 *  Entry function.  Het an example of how to use http_process_request
 *
 *  Parameters:
 *	ServerName is the nae of the HTTP server
 *	FullPathName is the relative url
 *  Returns: (none)
 *
 */

ENTRY void
http_main (char *ServerName, char *FullPathName)
{
	int status;
	http_request_data data;
	FILE *fp;
	char *mypointer;

	/* Set method type and version */
#undef TEST_HTTP_POST
#ifdef TEST_HTTP_POST
	char header_buffer[512];
	form_struct form_zero;
	data.method_type = HTTP_METHOD_POST;
	data.http_version =  HTTP_V1_0;

	data.send_header = &header_buffer[0];
	strcpy(data.send_header, "Content-Type: application/x-www-form-urlencoded\r\n");
	strcat(data.send_header, "Content-Length: 10\r\n");
	strcat(data.send_header, "Accept: text/html\r\n");

	data.send_header_size = strlen (data.send_header);

	data.numforms = 1;

	form_zero.name = "test";
	form_zero.name_length = strlen (form_zero.name);
	form_zero.input_type = HTTP_INPUT_TYPE_TEXTBOX;
	form_zero.value_type = HTTP_FORM_VALUE_TYPE_16;

	form_zero.value = "data=Frank";
	form_zero.length = strlen (form_zero.value);

	data.forms[0] = &form_zero;

	data.user_name = "apache";
	data.user_password = "snowdev1";

#endif /* TEST_POST */

#define TEST_HTTP_GET
#ifdef TEST_HTTP_GET
	data.method_type = HTTP_METHOD_GET;
	data.http_version =  HTTP_V1_0;
	data.send_header = "Accept: */*\r\n";
	data.send_header_size = strlen (data.send_header);

	data.user_name = "apache";
	data.user_password = "snowdev1";

#endif /* TEST_GET */

	/* From command line */

	/* Set servername and relative path  */
	data.servername = "10.1.1.153";
	data.filename = "/test.html";
	data.portnumber = 80;

	/* Set Size of buffers */
	data.returnbuf_max_size = HTTP_RETURN_BUFFER_SIZE;

	/* alloc buffers */
	mypointer = (char*) mallocw (data.returnbuf_max_size);
	data.returnbuf = mypointer;
	data.returnbuf_size = 0;

	data.return_header_size = 0;

	/* Call http processing routine */
	status = http_process_request (&data);

	switch (data.method_type) {
	case HTTP_METHOD_GET:

		/* Output to file */
		if ((fp = fopen ("output", WRITE_TEXT)) != NULLFILE) {
			fwrite (data.return_header, data.return_header_size, 1, fp);
			fwrite (data.returnbuf, data.returnbuf_size, 1, fp);
			fclose (fp);
		}

		/* Print Get buffer */
		fwrite (data.return_header, data.return_header_size, 1, stdout);
		fwrite (data.returnbuf, data.returnbuf_size, 1, stdout);
		break;

	case HTTP_METHOD_POST:
		if ((fp = fopen ("post", "w")) != NULLFILE) {
			fwrite (data.return_header, data.return_header_size, 1, fp);
			fwrite (data.returnbuf, data.returnbuf_size, 1, fp);
			fclose (fp);
		}

		/* Print Get buffer */
		fwrite (data.return_header, data.return_header_size, 1, stdout);
		fwrite (data.returnbuf, data.returnbuf_size, 1, stdout);
		break;

	default:
		break;
	}

	/* Print Result status */
	http_status (status);

	free (mypointer);
	free (data.return_header);
}
#endif /* TEST_HTTP */

/* ************************************************************************* */
/*
 *  Function: http_status
 *
 *  Local function.
 *
 *  Parameters:
 *	status
 *
 *  Returns: (none)
 *
 */
LOCAL int
http_status (int status)
{
	/* Print Result status */
	printf("\nstatus returned by http_process_request %d", status);
	switch (status) {
	case HTTP_STATUS_OK:
		printf("\nHTTP_STATUS_OK");
		break;
	case HTTP_STATUS_CREATED:
		printf("\nHTTP_STATUS_CREATED");
		break;
	case HTTP_STATUS_ACCEPTED:
		printf("\nHTTP_STATUS_ACCEPTED");
		break;
	case HTTP_STATUS_NO_CONTENT:
		printf("\nHTTP_STATUS_NO_CONTENT");
		break;
	case HTTP_STATUS_MOVED_PERM:
		printf("\nHTTP_STATUS_MOVED_PERM");
		break;
	case HTTP_STATUS_MOVED_TEMP:
		printf("\nHTTP_STATUS_MOVED_TEMP");
		break;
	case HTTP_STATUS_NOT_MOD:
		printf("\nHTTP_STATUS_NOT_MOD");
		break;
	case HTTP_STATUS_BAD_REQUEST:
		printf("\nHTTP_STATUS_BAD_REQUEST");
		break;
	case HTTP_STATUS_UNAUTH:
		printf("\nHTTP_STATUS_UNAUTH");
		break;
	case HTTP_STATUS_FORBIDDEN:
		printf("\nHTTP_STATUS_FORBIDDEN");
		break;
	case HTTP_STATUS_NOT_FOUND:
		printf("\nHTTP_STATUS_NOT_FOUND");
		break;
	case HTTP_STATUS_SERVER_ERROR:
		printf("\nHTTP_STATUS_SERVER_ERROR");
		break;
	case HTTP_STATUS_NOT_IMPL:
		printf("\nHTTP_STATUS_NOT_IMPL");
		break;
	case HTTP_STATUS_BAD_GATEWAY:
		printf("\nHTTP_STATUS_BAD_GATEWAY");
		break;
	case HTTP_STATUS_SERVICE_UNAVAIL:
		printf("\nHTTP_STATUS_SERVICE_UNAVAIL");
		break;
	case HTTP_ERROR_PARAM:
		printf("\nHTTP_ERROR_PARAM");
		break;
	case HTTP_ERROR_NETWORK:
		printf("\nHTTP_ERROR_NETWORK");
		break;
	case HTTP_ERROR_BUFFER:
		printf("\nHTTP_ERROR_BUFFER");
		break;
	case HTTP_ERROR_DNS_FAILED:
		printf("\nHTTP_ERROR_DNS_FAILED");
		break;
	case HTTP_ERROR_BAD_RETURN:
		printf("\nHTTP_ERROR_BAD_RETURN");
		break;
	case HTTP_NO_HEADER:
		printf("\nHTTP_NO_HEADER");
		break;
	default:
		printf("\ndefault status ");
	}
	return status;
}

LOCAL void
get_proc (int iarg, void *p1, void *p2)
{
	http_request_data *data = (http_request_data *) p1;
	int status;

	printf("Starting http get\n");

	/* Call http processing routine */
	status = http_process_request (data);

	printf("Done with http call\n");

	printf("Returned %u bytes\n",data->returnbuf_size);

	/* Output to file */

	/* Print Get buffer */
	/* this may not be a string !!! */
	if (data->returnbuf_size) {
		printf (data->return_header);
		printf("\n-----------------\n");
		printf (data->return_body);
	}
	http_status (status);

	free (data->returnbuf);
	free (data);
}

LOCAL int
getfile_proc (int iarg, void *p1, void *p2)
{
	http_request_data *data = (http_request_data *)p1;
	int status;

	/* Call http processing routine */
	status = http_get_file (data);

	free (data->returnbuf);
	free (data);

	return status;
}

LOCAL int
doget (int argc, char *argv[], void *p)
{
	http_request_data * data;

	if (argc < 3) {
		printf("Missing server and/or filename\n");
		return 1;
	}

	data = (http_request_data *) mallocw (sizeof (http_request_data));

	data->method_type = HTTP_METHOD_GET;
	data->http_version =  HTTP_V1_0;
	data->send_header = "Accept: */*\r\n";
	data->send_header_size = strlen (data->send_header);

	/* username/password */
	if (argc >= 5) {
		data->user_name = argv[3];
		data->user_password = argv[4];
	}
	else {
		data->user_name = NULL;
		data->user_password = NULL;
	}

	/* From code */
	data->servername = argv[1];
	data->filename = argv[2];
	data->portnumber = 80;

	/* Set Size of buffers */
	data->returnbuf_max_size = HTTP_RETURN_BUFFER_SIZE;

	/* alloc buffers */
	data->returnbuf = (char*) mallocw (data->returnbuf_max_size);
	data->returnbuf_size = 0;

	data->timeout = 20000;

	data->return_type = HTTP_FORM_VALUE_TYPE_16;

	if (newproc("http get", 1024, get_proc, 0, (void*)data, NULL, FALSE) == NULLPROC) {
		printf("Failed to create http get process\n");
		fflush (stdout);
	}

	return 0;
}

LOCAL int
dogetfile (int argc, char *argv[], void *p)
{
	http_request_data * data;

	if (argc < 3) {
		printf("Missing server and/or filename\n");
		return 1;
	}

	data = (http_request_data *) mallocw (sizeof (http_request_data));

	data->method_type = HTTP_METHOD_GET;
	data->http_version =  HTTP_V1_0;
	data->send_header = "Accept: */*\r\n";
	data->send_header_size = strlen (data->send_header);

	/* username/password */

	/* From code */

	/* <server> <remotefile> */
	data->servername = argv[1];

	data->filename = argv[2];
	data->localname = argv[2];

	if (argc == 4) {
		/* <server> <remotefile> <localfile>*/
		data->localname = argv[3];
		data->user_name = NULL;
		data->user_password = NULL;
	}
	else if (argc == 5) {
		/* <server> <remotefile> <username> <password> */
		data->localname = argv[2];
		data->user_name = argv[4];
		data->user_password = argv[5];
	}
	else if (argc == 6) {
		/* <server> <remotefile> <localfile> <username> <password> */
		data->localname = argv[3];
		data->user_name = argv[4];
		data->user_password = argv[5];
	}

	data->portnumber = 80;

	printf ("Server %s\n", data->servername);
	printf ("Remote %s\n", data->filename);
	printf ("Local %s\n", data->localname);

	printf ("User %s\n", data->user_name);
	printf ("Password %s\n", data->user_password);

	/* Set Size of buffers */
	data->returnbuf_max_size = GETFILE_BUFF_SIZE;

	/* alloc buffers */
	data->returnbuf = (char*) mallocw (data->returnbuf_max_size);
	data->returnbuf_size = 0;

	data->timeout = 20000;

	data->return_type = HTTP_FORM_VALUE_TYPE_16;

	if (getfile_proc(0,(void*)data, NULL) == HTTP_STATUS_OK) {
		return 0;
	} else {
		return 1;
	}
}

const struct cmds Httpcmds[] = {
	{"get",			doget,				0,	2,	"<server> <file> [<username> <password>]"},
	{"getfile",		dogetfile,			0,	2,	"<server> <remotefile> [<localfile>] [<username> <password>]"},
	{NULLCHAR},
};

ENTRY int
dohttp (int argc, char *argv[], void *p)
{
	return subcmd (Httpcmds, argc, argv, p);
}
