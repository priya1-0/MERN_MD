
/* ************************************************************************* */
/*
 *	support.h
 *
 *	(C) 1994 - 2006 VOCAL Technologies, Ltd.
 *
 *	ALL RIGHTS RESERVED.  PROPRIETARY AND CONFIDENTIAL.
 *
 *	VOCAL Technologies, Ltd.
 *	90A John Muir Drive.
 *	Buffalo, NY  14228
 *
 *	Product:	MODEM 101
 *
 *	Module:		SUPPORT
 *
 *	This file contains the public declarations for the SUPPORT module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 20:44:27  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _SUPPORT_SUPPORT_H
#define _SUPPORT_SUPPORT_H

/* ************************************************************************* */

#include "support/supportd.h"

/* ************************************************************************* */
/*- MKHEADER Begin -*/

/* Global Routines: */

/* network.c */
char * put32 (register char *cp, uint32 x);
char * put16 (char *cp, uint16 x);
uint16 get16 (register char *cp);
uint32 get32 (register char *cp);

/* print.c */
void fg_print_routine_primary (const char *fmt, ...);
void fg_print_routine_std (const char *fmt, ...);
void fg_print_routine_error (const char *fmt, ...);
void fg_print_routine_warning (const char *fmt, ...);
void fg_print_routine_info (const char *fmt, ...);
void fg_print_routine_diag (const char *fmt, ...);
void fg_print_routine_debug (const char *fmt, ...);
void fg_print_routine_dev (const char *fmt, ...);
void fg_print_routine_dump (const char *fmt, ...);
void bg_print_routine_primary (const char *fmt, ...);
void bg_print_routine_std (const char *fmt, ...);
void bg_print_routine_error (const char *fmt, ...);
void bg_print_routine_warning (const char *fmt, ...);
void bg_print_routine_info (const char *fmt, ...);
void bg_print_routine_diag (const char *fmt, ...);
void bg_print_routine_debug (const char *fmt, ...);
void bg_print_routine_dev (const char *fmt, ...);
void bg_print_routine_dump (const char *fmt, ...);
void bg_print_routine_protocol_error (const char *fmt, ...);
void bg_print_routine_protocol_warning (const char *fmt, ...);
void bg_print_routine_protocol_info (const char *fmt, ...);
void bg_print_routine_protocol_detail (const char *fmt, ...);
void print_routine (const char *fmt, ...);
void report_anomaly_routine (uint16 val);

/* serial.c */
void support_serial_module_reset (void);
uint16 sys_putc (char c);
int sys_puts (const char *buf);
int sys_putb (const char *buf, int len);
int kbread (void);
void serial_console_rx (uint16 du);
uint16 serial_console_tx (void);
uint16 console_tx_pending (void);

/* support.c */
void support_module_reset (void);
char dtmf_vocal_to_ascii(uint16 digit, int uppercase);
uint16 dtmf_ascii_to_vocal (char key_code);
char * generic_uint16_to_02d (char *str, uint16 i);
char * generic_uint16_to_02x_uc (char *str, uint16 i);
char * generic_uint16_to_03d (char *str, uint16 i);
char * generic_uint16_to_d (char *str, uint16 i);
char * generic_uint16_to_04x (char *str, uint16 i);
int generic_wordcmp(const char *string, const char *ref);
const char * generic_next_arg(const char *string);
char * generic_cut_line (char *string);
uint16 generic_safe_strcat (char *dest, const char *src, int size);
uint16 generic_safe_hexcat (char *dest, const char *src, int size);
uint8 generic_safe_strcpy (char *dest, const char *src, int size);
uint8 generic_safe_str_unpack (char *dest, const uint16 *src, int size);
char * generic_strcpy (char *s, const char *ct);
char * generic_strncpy (char *s, const char *ct, uint16 n);
void * generic_block_clear (void *s, uint16 n);
uint8 generic_toupper (uint8 n);
int generic_isdigit (uint8 n);
int generic_strncmp (const char *cs, const char *ct, uint16 n);
int generic_strcmp (const char *str1, const char *str2);
int bincmp(char *str1, char *str2, int len);
int generic_stricmp (const char *str1, const char *str2);
int generic_strincmp (const char *str1, const char *str2, int len);
char * generic_stristr (const char *str1, const char *str2);
int generic_strlen (const char *cs);
char * generic_strlwr (char *cs);
char * generic_strupr (char *cs);
char * generic_strchr (char *cs, char c);
char * generic_strncat (char *cs, const char *ct, uint16 n);
char * generic_strcat (char *cs, const char *ct);
uint16 generic_min (uint16 a, uint16 b);
uint16 generic_max (uint16 a, uint16 b);
sint31 generic_atol (const char *ch);
uint32 generic_atoi (const char *ch);
uint8 generic_atoh (char file_char);
int generic_vsprintf (char *buf, const char *format_string, va_list list);
int generic_vsnprintf (char *buf, int size, const char *format_string, va_list list);
int generic_sprintf (char *buf, const char *format_string, ... );
int generic_snprintf (char *buf, int size, const char *format_string, ... );
void * generic_memcpy (void *to, const void *from, unsigned int n);

/* time.c */
char * tformat (sint31 t);
char * ctime (const time_t *timep);
char * asctime (const struct tm *tp);
struct tm * localtime (const time_t *timep);
struct tm * gmtime (const time_t *timep);
time_t mktime (const struct tm *tp);
char * rfc1123_time (const struct tm *tp);
uint16 parse_time (struct tm *tmp, char *cp);
uint16 parse_date (struct tm *tmp, char *cp);

/*- MKHEADER End -*/


/* ************************************************************************* */

#endif /* _SUPPORT_SUPPORT_H */
