
/* ************************************************************************* */
/*
 *	print.c
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
 *  This file contains standard formated print routines.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 20:44:27  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#include "system/system.h"

#include "support/local.h"

/* ************************************************************************* */

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */
/*
 *	Entry Routine:
 *		fg_print_routine_primary
 *		fg_print_routine_std
 *
 *		fg_print_routine_diag
 *		fg_print_routine_debug
 *		fg_print_routine_dev
 *		fg_print_routine_dump
 *
 *		bg_print_routine_primary
 *		bg_print_routine_std
 *		bg_print_routine_error
 *		bg_print_routine_warning
 *		bg_print_routine_info
 *
 *		bg_print_routine_diag
 *		bg_print_routine_debug
 *		bg_print_routine_dev
 *		bg_print_routine_dump
 *
 *		bg_print_routine_protocol_error
 *		bg_print_routine_protocol_warning
 *		bg_print_routine_protocol_info
 *		bg_print_routine_protocol_detail
 *
 *	These routines are used to prefix print statements with their associated
 *	warning or debug level.
 *
 *	Parameters:
 *
 *	Returns:
 *		none
 */

#ifdef SHOW_NEW_LINE
#define NL	"\n"
#else /* SHOW_NEW_LINE */
#define NL
#endif /* SHOW_NEW_LINE */

ENTRY void
fg_print_routine_primary (const char *fmt, ...)
{
	va_list temp_args;
	va_start (temp_args, fmt);
	fg_print_routine ((NL "PRI: "));
	fg_vprint_routine ((fmt, temp_args));
	va_end (temp_args);
}

ENTRY void
fg_print_routine_std (const char *fmt, ...)
{
	va_list temp_args;
	va_start (temp_args, fmt);
	fg_print_routine ((NL "STD: "));
	fg_vprint_routine ((fmt, temp_args));
	va_end (temp_args);
}

/* ************************************************************************* */

ENTRY void
fg_print_routine_error (const char *fmt, ...)
{
	va_list temp_args;
	va_start (temp_args, fmt);
	fg_print_routine ((NL "FERR: "));
	fg_vprint_routine ((fmt, temp_args));
	va_end (temp_args);
}

ENTRY void
fg_print_routine_warning (const char *fmt, ...)
{
	va_list temp_args;
	va_start (temp_args, fmt);
	fg_print_routine ((NL "FWAR: "));
	fg_vprint_routine ((fmt, temp_args));
	va_end (temp_args);
}

ENTRY void
fg_print_routine_info (const char *fmt, ...)
{
	va_list temp_args;
	va_start (temp_args, fmt);
	fg_print_routine ((NL "FINF: "));
	fg_vprint_routine ((fmt, temp_args));
	va_end (temp_args);
}

ENTRY void
fg_print_routine_diag (const char *fmt, ...)
{
	va_list temp_args;
	va_start (temp_args, fmt);
	fg_print_routine ((NL "FDIA: "));
	fg_vprint_routine ((fmt, temp_args));
	va_end (temp_args);
}

ENTRY void
fg_print_routine_debug (const char *fmt, ...)
{
	va_list temp_args;
	va_start (temp_args, fmt);
	fg_print_routine ((NL "FDBG: "));
	fg_vprint_routine ((fmt, temp_args));
	va_end (temp_args);
}

ENTRY void
fg_print_routine_dev (const char *fmt, ...)
{
	va_list temp_args;
	va_start (temp_args, fmt);
	fg_print_routine ((NL "FDEV: "));
	fg_vprint_routine ((fmt, temp_args));
	va_end (temp_args);
}

ENTRY void
fg_print_routine_dump (const char *fmt, ...)
{
	va_list temp_args;
	va_start (temp_args, fmt);
	fg_print_routine ((NL "FDMP: "));
	fg_vprint_routine ((fmt, temp_args));
	va_end (temp_args);
}

/* ************************************************************************* */

ENTRY void
bg_print_routine_primary (const char *fmt, ...)
{
	va_list temp_args;
	va_start (temp_args, fmt);
	bg_print_routine ((NL "PRI: "));
	bg_vprint_routine ((fmt, temp_args));
	va_end (temp_args);
}

ENTRY void
bg_print_routine_std (const char *fmt, ...)
{
	va_list temp_args;
	va_start (temp_args, fmt);
	bg_print_routine ((NL "STD: "));
	bg_vprint_routine ((fmt, temp_args));
	va_end (temp_args);
}

ENTRY void
bg_print_routine_error (const char *fmt, ...)
{
	va_list temp_args;
	va_start (temp_args, fmt);
	bg_print_routine ((NL "ERR: "));
	bg_vprint_routine ((fmt, temp_args));
	va_end (temp_args);
}

ENTRY void
bg_print_routine_warning (const char *fmt, ...)
{
	va_list temp_args;
	va_start (temp_args, fmt);
	bg_print_routine ((NL "WAR: "));
	bg_vprint_routine ((fmt, temp_args));
	va_end (temp_args);
}

ENTRY void
bg_print_routine_info (const char *fmt, ...)
{
	va_list temp_args;
	va_start (temp_args, fmt);
	bg_print_routine ((NL "INF: "));
	bg_vprint_routine ((fmt, temp_args));
	va_end (temp_args);
}

/* ************************************************************************* */

ENTRY void
bg_print_routine_diag (const char *fmt, ...)
{
	va_list temp_args;
	va_start (temp_args, fmt);
	bg_print_routine ((NL "DIA: "));
	bg_vprint_routine ((fmt, temp_args));
	va_end (temp_args);
}

ENTRY void
bg_print_routine_debug (const char *fmt, ...)
{
	va_list temp_args;
	va_start (temp_args, fmt);
	bg_print_routine ((NL "DBG: "));
	bg_vprint_routine ((fmt, temp_args));
	va_end (temp_args);
}

ENTRY void
bg_print_routine_dev (const char *fmt, ...)
{
	va_list temp_args;
	va_start (temp_args, fmt);
	bg_print_routine ((NL "DEV: "));
	bg_vprint_routine ((fmt, temp_args));
	va_end (temp_args);
}

ENTRY void
bg_print_routine_dump (const char *fmt, ...)
{
	va_list temp_args;
	va_start (temp_args, fmt);
	bg_print_routine ((NL "DMP: "));
	bg_vprint_routine ((fmt, temp_args));
	va_end (temp_args);
}

/* ************************************************************************* */

ENTRY void
bg_print_routine_protocol_error (const char *fmt, ...)
{
	va_list temp_args;
	va_start (temp_args, fmt);
	bg_print_routine ((NL "PER: "));
	bg_vprint_routine ((fmt, temp_args));
	va_end (temp_args);
}

ENTRY void
bg_print_routine_protocol_warning (const char *fmt, ...)
{
	va_list temp_args;
	va_start (temp_args, fmt);
	bg_print_routine ((NL "PWA: "));
	bg_vprint_routine ((fmt, temp_args));
	va_end (temp_args);
}

ENTRY void
bg_print_routine_protocol_info (const char *fmt, ...)
{
	va_list temp_args;
	va_start (temp_args, fmt);
	bg_print_routine ((NL "PIN: "));
	bg_vprint_routine ((fmt, temp_args));
	va_end (temp_args);
}

ENTRY void
bg_print_routine_protocol_detail (const char *fmt, ...)
{
	va_list temp_args;
	va_start (temp_args, fmt);
	bg_print_routine ((NL "PDT: "));
	bg_vprint_routine ((fmt, temp_args));
	va_end (temp_args);
}

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */
/*
 *	Entry Routine:
 *		print_primary_routine
 *		print_std_routine
 *		print_info_routine
 *		print_debug_routine
 *
 *	These routines are used as the formatted output mechanism.  The four
 *	different flavors of routines are used to categorize the output type.
 *	These routines are called by similarly named system-wide macros (the
 *	macro names are without the _routine suffix).  The reason for using macros
 *	is so that the calls can be cleanly compiled out for production code,
 *	with no code overhead whatsoever.  However, since these are variable
 *	argument functions, the macros must be implemented with double parenthesis.
 *
 *	An example invocation:
 *
 *		print_std ((("State: %d", state_num)));
 *
 *	Suggested category usage is:
 *
 *	print_primary:	Copyright notices, help menu, anomalies, background
 *					"I'm alive" indication, etc.
 *	print_std:		Events, state numbers, etc.
 *	print_info:		State names, packet types rx'd or tx'd, etc.
 *	print_debug:	Prints added for debuging a particular problem
 *					where the added debug code is expected to be
 *					removed shortly.
 *
 *	The user must guarantee that the length of the string generated can be
 *	no more than PRINT_SIZE_MAX - 1 in size.
 *
 *	This code is expected to be modified to send the output to various
 *	customer-dependant platform destinations.  Because of this, the standard
 *	code base must assume that these prints cannot be called from within
 *	interrupts!
 *
 *	Parameters:
 *
 *	Returns:
 *		none
 */

ENTRY void
print_routine (const char *fmt, ...)
{
	va_list temp_args;
	va_start (temp_args, fmt);
	vprint_routine (fmt, temp_args);
	va_end (temp_args);
}

/* ************************************************************************* */
/*
 *	Minimal print routine which avoids usage of sprintf
 *
 *	(sprintf may not be re-entrant/thread safe or not available.)
 *
 */
LOCAL void
vprint_routine (const char *fmt, va_list argp)
{
	static char *lookup = "0123456789abcdef";
	bool desync_ocd = FALSE;
	int i;
	char c;
	char *cp;
	sint31 l;
	const char *parsep;
	const char *restore_parsep;
	char type;

	parsep = fmt;

	while (*parsep != '\0') {
		if ((*parsep != '%') || desync_ocd) {
label__copy_char:
			print_output_char (*parsep);
		}
		else {
			restore_parsep = parsep;
			type = print_parse_type (&parsep);
			switch (type) {
			case 'c':
				c = va_arg (argp, int);
				print_output_char (c);
				break;

			case 's':
				cp = va_arg (argp, char *);
				while (*cp != '\0') {
					print_output_char (*cp++);
				}
				break;

			case 'x':
			case 'd':
			case 'u':
				/*	Since va_arg is really a macro, lets minimize the
					amount of code generated by combining cases. */
				i = va_arg (argp, int);
				switch (type) {
				case 'x':
				case 'd': /* Fix Later: Output as decimal */
				case 'u': /* Fix Later: Output as unsigned */
					print_output_char (lookup [ ((i >> 12) & 0x000F)]);
					print_output_char (lookup [ ((i >>  8) & 0x000F)]);
					print_output_char (lookup [ ((i >>  4) & 0x000F)]);
					print_output_char (lookup [ ((i >>  0) & 0x000F)]);
					break;
				}
				break;

			case 'l': /* ld */
			case 'z': /* lx */
				/*	Since va_arg is really a macro, lets minimize the
					amount of code generated by combining cases. */
				l = va_arg (argp, sint31);
				switch (type) {
				case 'l': /* ld */
				case 'z': /* lx */
					print_output_char (lookup [ ((l >> 28) & 0x0000000F)]);
					print_output_char (lookup [ ((l >> 24) & 0x0000000F)]);
					print_output_char (lookup [ ((l >> 20) & 0x0000000F)]);
					print_output_char (lookup [ ((l >> 16) & 0x0000000F)]);
					print_output_char (lookup [ ((l >> 12) & 0x0000000F)]);
					print_output_char (lookup [ ((l >>  8) & 0x0000000F)]);
					print_output_char (lookup [ ((l >>  4) & 0x0000000F)]);
					print_output_char (lookup [ ((l >>  0) & 0x0000000F)]);
					break;
				}
				break;

			default:
				parsep = restore_parsep;
				desync_ocd = TRUE;
				goto label__copy_char;
			}
		}
		parsep++;
	}

}

/* ************************************************************************* */

LOCAL char
print_parse_type (const char **cpp)
{
	bool long_flag = FALSE;

	(*cpp)++;
	while (**cpp != '\0') {
		switch (**cpp) {
		case 'd':
		case 'D':
			if (long_flag) {
				return 'l';
			}
			return 'd';

		case 'u':
		case 'U':
			if (long_flag) {
				return 'l';
			}
			return 'u';

		case 'x':
		case 'X':
			if (long_flag) {
				return 'z';
			}
			return 'x';

		case 'c':
		case 'C':
			return 'c';

		case 's':
		case 'S':
			return 's';

		case 'L':
		case 'l':
			long_flag = TRUE;
			break;

		case 'o':
		case 'O':
		case 'f':
		case 'F':
		case 'g':
		case 'G':
		case 'e':
		case 'E':
		case 'n':
		case 'p':
				/* Unsupported */
			return '1';

		default:
				/* Ignore all other characters */
			break;
		}
		(*cpp)++;
	}
	return 0;	/* End of string encountered */
}

/* ************************************************************************* */
/*
 *	Local Routine: print_output_char
 *
 *	This routine buffer a character in the diagnostic print buffer.
 *
 *	Parameters:
 *		the character to print
 *
 *	Returns:
 *		none
 *
 */

LOCAL void
print_output_char (char c)
{
	/* Expand \n to \r\n */
	if (c == '\n') {
		sys_putc ('\r');
	}

	sys_putc (0x007f & c);
}

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */
/*
 *	Entry Routine: report_anomaly_routine
 *
 *	This routine is used to report anomalies.  It is called by similarly
 *	named system-wide macros (without the _routine suffix).
 *
 *	Parameters:
 *		"val" is the anomaly number.
 *
 *	Returns:
 *		none
 */
ENTRY void
report_anomaly_routine (uint16 val)
{
	report_status (STATUS__CSC_ANOMALY_REPORT, val);
	if (print_disable) {
		return;
	}
	print_primary (("\nAnomaly #%04x - Please report this and the condition under which it occurred.\n", (int) val));
}

/* ************************************************************************* */
