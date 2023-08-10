
/* ************************************************************************* */
/*
 *	support.c
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
 *	This contains the various debug variable display routines.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.2.6.2  2009/04/28 20:44:27  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#include "system/system.h"

#include "support/local.h"
#include "include/dtmf.h"

/* ************************************************************************* */
/*
 *	Entry Routine: support_module_reset
 *
 *	This routine is used to reset variables.
 *
 *	WARNING - This is assumed to be single instance only.  If multiple instance
 *	is required, the serial/printing initialization must be separated and remain
 *	early in the startup sequence soon after processor_initialization ().
 *
 *	Parameters:
 *		none
 *
 *	Returns:
 *		none
 *
 */
ENTRY void
support_module_reset (void)
{

	support_serial_module_reset();
}

/* ************************************************************************* */
/*
 *	Entry Routine: dtmf_vocal_to_ascii
 *	Entry Routine: dtmf_ascii_to_vocal
 *
 *	These routines convert between ascii (char) and VOCAL (uint16 with flags)
 *	dtmf digits.
 *
 *	Parameters:
 *
 *	Returns:
 *
 */

ENTRY char
dtmf_vocal_to_ascii(uint16 digit, int uppercase)
{
	digit = digit & 0x000f;

	if (digit == DTMF__DIGIT_STAR) {
		digit = '*';
	} else if (digit == DTMF__DIGIT_POUND) {
		digit = '#';
	} else if (digit <= DTMF__DIGIT_9) {
		digit += '0';
	} else {
		if (uppercase) digit += 'A';
		else digit += 'a';
		digit -= DTMF__DIGIT_A;
	}
	return (char)digit;
}

ENTRY uint16
dtmf_ascii_to_vocal (char key_code)
{
	uint16 rc;

	if ((key_code >= '0') && (key_code <= '9')) {
		rc = key_code - '0';
	}
	else if (key_code == '*') {
		rc = DTMF__DIGIT_STAR;
	}
	else if (key_code == '#') {
		rc = DTMF__DIGIT_POUND;
	}
	else {
		key_code = key_code | 32;
		if (key_code >= 'a' && key_code <= 'd') {
			rc = key_code - 'a' + DTMF__DIGIT_A;
		}
		else {
			rc = 0xffff;
		}
	}
	return rc;
}

/* ************************************************************************* */
/*
 *	Entry Routine: generic_uint16_to_02d
 *
 *	This routine is used to replace a format of the standard library sprintf.
 *
 *	Parameters:
 *		"str"	output string with format:  sprint_std ((str,"%02d",i)
 *		"i"	input number (assume i <= 99)
 *
 *	Returns:
 *		output string with format: sprint_std ((str,"%02d",i)
 *
 */
ENTRY char *
generic_uint16_to_02d (char *str, uint16 i)
{

	char c;
	char *str_begin;

	str_begin = str;
	c = '0';
	while (i >= 10) {
		i -= 10;
		c++;
	}
	*(str++) = c;

	c = '0';
	while (i >= 1) {
		i -= 1;
		c++;
	}
	*(str++) = c;
	*str = '\0';

	str = str_begin;
	return str_begin;
}

/* ************************************************************************* */
/*
 *	Entry Routine: generic_uint16_to_02x_uc
 *
 *	This routine is used to replace a format of the standard library sprintf.
 *
 *	Parameters:
 *		"str"	output string with format:  sprintf ((str,"%02d",i)
 *		"i"	input number (assume i <= 99)
 *
 *	Returns:
 *		output string with format: toupper (sprintf ((str, "%02d", i))
 *
 */
ENTRY char *
generic_uint16_to_02x_uc (char *str, uint16 i)
{

	char c;
	char *str_begin;

	str_begin = str;
	c = '0';
	while (i >= 16) {
		i -= 16;
		c++;
	}
	*(str++) = (c > '9') ? (c + ('A' - ':')) : c;

	c = '0';
	while (i >= 1) {
		i -= 1;
		c++;
	}
	*(str++) = (c > '9') ? (c + ('A' - ':')) : c;
	*str = '\0';

	str = str_begin;
	return str_begin;
}

/* ************************************************************************* */
/*
 *	Entry Routine: generic_uint16_to_03d
 *
 *	This routine is used to replace a format of the standard library sprintf.
 *
 *	Parameters:
 *		"str"	output string with format: sprint_std ((str,"%03d",i)
 *		"i"	input number
 *
 *	Returns:
 *		output string with format: sprint_std ((str,"%03d",i)
 *
 */
ENTRY char *
generic_uint16_to_03d (char *str, uint16 i)
{

	char c;
	char *str_begin;

	str_begin = str;
	c = '0';
	while (i >= 100) {
		i -= 100;
		c++;
	}
	*(str++) = c;

	c = '0';
	while (i >= 10) {
		i -= 10;
		c++;
	}
	*(str++) = c;

	c = '0';
	while (i >= 1) {
		i -= 1;
		c++;
	}
	*(str++) = c;
	*str = '\0';

	str = str_begin;
	return str_begin;
}

/* ************************************************************************* */
/*
 *	Entry Routine: generic_uint16_to_d
 *
 *	This routine is used to replace a format of the standard library sprintf.
 *
 *	Parameters:
 *		"str"	output string with format: sprint_std ((str,"%d",i)
 *		"i"	input number (assume i <= 65535)
 *
 *	Returns:
 *		output string with format: sprint_std ((str,"%d",i)
 *
 */
ENTRY char *
generic_uint16_to_d (char *str, uint16 i)
{
	char c;
	char *str_begin;
	bool found;

	found = FALSE;
	str_begin = str;
	c = '0';
	while (i >= 10000) {
		i -= 10000;
		c++;
		found = TRUE;
	}
	if (found) {
		*(str++) = c;
	}

	c = '0';
	while (i >= 1000) {
		i -= 1000;
		c++;
		found = TRUE;
	}
	if (found) {
		*(str++) = c;
	}

	c = '0';
	while (i >= 100) {
		i -= 100;
		c++;
		found = TRUE;
	}
	if (found) {
		*(str++) = c;
	}

	c = '0';
	while (i >= 10) {
		i -= 10;
		c++;
		found = TRUE;
	}
	if (found) {
		*(str++) = c;
	}

	c = '0';
	while (i >= 1) {
		i -= 1;
		c++;
	}
	*(str++) = c;
	*str = '\0';

	str = str_begin;
	return str_begin;
}

/* ************************************************************************* */
/*
 *	Entry Routine: generic_uint16_to_04x
 *
 *	This routine is used to replace a format of the standard library sprintf.
 *
 *	Parameters:
 *		"str"	output string with format: sprint_std ((str,"%04x",i)
 *		"i"	input number (assume i <= 65535)
 *
 *	Returns:
 *		output string with format: sprint_std ((str,"%04x",i)
 *
 */
ENTRY char *
generic_uint16_to_04x (char *str, uint16 i)
{
	char *str_begin;
	uint8 count;

	str_begin = str;
	count = 0;
	while (i >= 4096) {
		i -= 4096;
		count++;
	}
	if (count < 10) {
		*(str++) = '0' + count;
	}
	else {
		*(str++) = 'a' + (count - 10);
	}

	count = 0;
	while (i >= 256) {
		i -= 256;
		count++;
	}
	if (count < 10) {
		*(str++) = '0' + count;
	}
	else {
		*(str++) = 'a' + (count - 10);
	}

	count = 0;
	while (i >= 16) {
		i -= 16;
		count++;
	}
	if (count < 10) {
		*(str++) = '0' + count;
	}
	else {
		*(str++) = 'a' + (count - 10);
	}

	if (i < 10) {
		*(str++) = '0' + i;
	}
	else {
		*(str++) = 'a' + (i - 10);
	}

	*str = '\0';

	str = str_begin;
	return str_begin;
}

/* ************************************************************************* */
/*
 *	Entry Routine: generic_wordcmp
 *
 *	This routine is used for string parsing.  It compares whitespace
 *  delimited words.  Case sensitive.
 *
 *	Parameters:
 *		"string"	unknown string pointer
 *		"ref"		reference word/string to compare against
 *
 *	Returns:
 *		1 if match, 0 if not
 */

ENTRY int
generic_wordcmp(const char *string, const char *ref)
{
	/* sanity */
	if (ref == NULL || *ref == 0) return 0;
	if (string == NULL || *string == 0) return 0;

	while(*string!=0 && *string!='\t' && *string!='\n' && *string!='\r' && *string!=' ') {
		/* *string is not whitespace, and it's also different from */
		/* *ref, so we clearly have a failure */
		if (*string != *ref) return 0;
		string++;
		ref++;
	}

	/* if we got here, *string is whitespace, eg end of word */
	/* if ref is also end of word, we're in good shape */
	if (*ref==0 || *ref=='\t' || *ref=='\n' || *ref=='\r' || *ref==' ') return 1;
	return 0;
}

/* ************************************************************************* */
/*
 *	Entry Routine: generic_next_arg
 *
 *	This routine is used for string parsing.  It advances to the next
 *  whitespace delimited word, and returns a pointer to it.  Returns
 *  NULL on end of line or end of string.
 *
 *	Parameters:
 *		"string"	unknown string pointer
 *
 *	Returns:
 *		pointer to next string argument, null if none
 */

ENTRY const char *
generic_next_arg(const char *string)
{
	/* sanity */
	if (string == NULL || *string == 0) return 0;

	/* first, skip over leading spaces */
	while(*string == ' ' || *string == '\t') string++;

	/* now, skip forward to next whitespace */
	while(*string!=0 && *string!='\t' && *string!='\n' && *string!='\r' && *string!=' ') string++;

	/* skip over trailing spaces, if any */
	while(*string == ' ' || *string == '\t') string++;

	/* end of line, return nothing */
	if (*string==0 || *string=='\n' || *string=='\r') return NULL;

	return string;
}

/* ************************************************************************* */
/*
 *	Module Routine: generic_cut_line
 *
 * This takes an incoming string, hacks off the first line, then
 * returns a pointer to the next line (DESTRUCTIVE)
 *
 *	Parameters:
 *		(char *string):      Destination location
 *
 *	Returns:
 *		(char *): pointer to next string or NULL if none
 */
ENTRY char *
generic_cut_line (char *string)
{
	while(*string != '\0') {
		/* look for end of line */
		if (*string == ASCII__CR || *string == ASCII__LF) {
			if ((string[0] == ASCII__CR && string[1] == ASCII__LF) ||
				(string[0] == ASCII__LF && string[1] == ASCII__CR)) {
				*string = '\0';
				return string+2;
			}
			string[0] = '\0';
			return string+1;
		}

		string++;
	}

	/* if we got out here, we hit the end of the string - no next line */
	return NULL;
}

/* ************************************************************************* */
/*
 *	Module Routine: safe_strcat
 *
 *	Does a strcat but takes into account size of destination, terminates
 *  properly, and cuts a warning on overflow.
 *
 *	Parameters:
 *		(char *dest):      Destination location
 *		(const char *src): Source string
 *		(int):              Destination length
 *
 *	Returns:
 *		(uint8):  1 on success, 0 on failure (not that it matters)
 */

ENTRY uint16
generic_safe_strcat (char *dest, const char *src, int size)
{
	int i,j;

	if (*src == 0) return 1;
	if (size <= 0) {
		print_debug_on(("Error in generic_safe_strcat(), size was %d.\n",size));
		return 0;
	}

	/* advance to end of dest */
	for(j=0;j < size && dest[j] != '\0';j++);
	if (j >= size) {
		print_debug_on(("Error in generic_safe_strcat(), destination already full.\n"));
		print_debug_on(("Size %d, source was --------------\n%s\n---------------",size,src));
		print_debug_on(("Destination was --------------\n%s\n---------------",dest));
		return 0;
	}

	/* give us room for the terminating 0 */
	size--;

	for(i=0; j<size && src[i]!=0; i++,j++) dest[j] = src[i];
	dest[j] = 0;
	if (src[i] == 0) return 1;

	size++;
	print_debug_on(("Error in generic_safe_strcat(), destination full.\n"));
	print_debug_on(("Size %d, source was --------------\n%s\n---------------",size,src));
	print_debug_on(("Destination is --------------\n%s\n---------------",dest));
	return 0;
}

ENTRY uint16
generic_safe_hexcat (char *dest, const char *src, int size)
{
	int i,j;

	if (*src == 0) return 1;
	if (size <= 0) {
		print_debug_on(("Error in generic_safe_strcat(), size was %d.\n",size));
		return 0;
	}

	/* advance to end of dest */
	for(j=0;j < size && dest[j] != '\0';j++);
	if (j >= size) {
		print_debug_on(("Error in generic_safe_hexcat(), destination already full.\n"));
		print_debug_on(("Size %d, source was --------------\n%s\n---------------",size,src));
		print_debug_on(("Destination was --------------\n%s\n---------------",dest));
		return 0;
	}

	/* give us room for the terminating 0 */
	size -= 2;

	for(i=0; j<size && src[i]!=0; i++) {
		sprintf(&(dest[j]), "%02x", (unsigned int)((uint8)src[i]));
		j += 2;
	}
	if (src[i] == 0) return 1;

	size += 2;
	print_debug_on(("Error in generic_safe_hexcat(), destination full.\n"));
	print_debug_on(("Size %d, source was --------------\n%s\n---------------",size,src));
	print_debug_on(("Destination is --------------\n%s\n---------------",dest));
	return 0;
}

/* ************************************************************************* */
/*
 *	Module Routine: generic_safe_strcpy
 *
 *	Does a strcpy but takes into account size of destination, terminates
 *  properly, and cuts a warning on overflow.  Its like strncpy, but
 *  does extra stuff.
 *
 *	Parameters:
 *		(char *dest):      Destination location
 *		(const char *src): Source string
 *		(int):              Destination length
 *
 *	Returns:
 *		(uint8):  1 on success, 0 on failure (not that it matters)
 */

ENTRY uint8
generic_safe_strcpy (char *dest, const char *src, int size)
{
	int i;
	if (size <= 0) {
		print_debug_on(("Error in generic_safe_strcpy(), size was %d.\n",size));
		return 0;
	}

	/* give us room for the terminating 0 */
	size--;

	for(i=0; i<size && src[i]!='\0'; i++) dest[i] = src[i];
	dest[i] = 0;
	if (src[i] == 0) return 1;

	size++;
	print_debug_on(("Error in generic_safe_strcpy(), overflow into buffer of size %d, source was '%s'.\n",size,src));
	return 0;
}

/* ************************************************************************* */
/*
 *	Module Routine: generic_safe_str_unpack
 *
 *	Does a strcpy but takes into account size of destination, terminates
 *  properly, and cuts a warning on overflow.  Its like strncpy, but
 *  does extra stuff.  The packed data is according to PC conventions.
 *
 *	Parameters:
 *		(char *dest):      Destination location
 *		(const uint16 *src): Source string (packed two bytes per uint16)
 *		(int):              Destination length
 *
 *	Returns:
 *		(uint8):  1 on success, 0 on failure (not that it matters)
 */

ENTRY uint8
generic_safe_str_unpack (char *dest, const uint16 *src, int size)
{
	int i, j;
	uint16 w;
	char b;

	if (size <= 0) {
		print_debug_on(("Error in generic_safe_str_unpack(), size was %d.\n",size));
		return 0;
	}

	/* Unpack the data as it is copied */
	j = 0;
	for (i = 0; i < size; i++) {
		w = src[j++];
		b = (char) (w & 0xff);
		dest[i++] = b;
		if (b == 0) {
			break;
		}

		/* Move up to the size of the buffer including the terminating 0 */
		if (i >= size) {
			break;
		}

		b = (char) ((w >> 8) & 0xff);
		dest[i] = b;
		if (b == 0) {
			break;
		}
	}

	dest[size - 1] = 0;
	if (b == 0) return 1;

	print_debug_on(("Error in generic_safe_str_unpack(), overflow into buffer of size %d, source was '%s'.\n",size,src));
	return 0;
}

/* ************************************************************************* */
/*
 *	Entry Routine: generic_strcpy
 *
 *	This routine is used to replace the standard library routine generic_strcpy.
 *	Copies string ct to string s, including '\0'.
 *
 *	Parameters:
 *		"s"	output string pointer
 *		"ct"	input string pointer
 *
 *	Returns:
 *		ouput string pointer
 *
 */

ENTRY char *
generic_strcpy (char *s, const char *ct)
{
	char *s_begin;
	s_begin = s;

	while ((*s++ = *ct++) != '\0');

	s = s_begin;
	return s;
}

/* ************************************************************************* */
/*
 *	Entry Routine: generic_strncpy
 *
 *	This routine is used to replace the standard library routine generic_strncpy.
 *	Copies at most n characters of string ct to string s, including '\0'.
 *	Pad with '\0' if ct has fewer than n charcters.
 *
 *	Parameters:
 *		"s"	output string pointer
 *		"ct"	input string pointer
 *		"n"	input number
 *
 *	Returns:
 *		ouput string pointer
 *
 */

ENTRY char *
generic_strncpy (char *s, const char *ct, uint16 n)
{
	uint16 count;
	char *s_begin;

	count = 0;
	s_begin = s;

	while ((count++ < n) && ((*s++ = *ct++) != '\0')) ;
	while (count++ < n)	*s++ = '\0';

	s = s_begin;
	return s;
}

/* ************************************************************************* */
/*
 *	Entry Routine: generic_block_clear
 *
 *	This routine is used to place 0 into first 'n' characters of string 's'.
 *
 *	Parameters:
 *		"s"	input string pointer
 *		"n"	number of characters to set to zero
 *
 *	Returns:
 *		output string pointer
 *
 */
ENTRY void *
generic_block_clear (void *s, uint16 n)
{

	return (void *) memset (s, 0, n);
}

/* ************************************************************************* */
/*
 *	Entry Routine: generic_toupper
 *
 *	This routine is used to convert c to upper case.
 *
 *	Parameters:
 *		"n"	character to convert
 *
 *	Returns:
 *		output upper case character
 *
 */
ENTRY uint8
generic_toupper (uint8 n)
{
	if (n >= 'a' && n <= 'z') n = (uint8)(n - 32);
	return n;
}

/* ************************************************************************* */
/*
 *	Entry Routine: generic_isdigit
 *
 *	This routine is used to testing character for a decimal digit.
 *
 *	Parameters:
 *		"n"	 (assume n <=255)
 *
 *	Returns:
 *		non-zero if true
 *
 */
ENTRY int
generic_isdigit (uint8 n)
{
	return ((n >= '0') && (n <= '9'));
}

/* ************************************************************************* */
/*
 *	Entry Routine: generic_strncmp
 *
 *	This routine is used to compare string cs to string ct.
 *
 *	Parameters:
 *		"n"	 (assume n <=255)
 *
 *	Returns:
 *		<0 if cs<ct, 0 if cs==ct, or >0 if cs>ct
 *
 */

ENTRY int
generic_strncmp (const char *cs, const char *ct, uint16 n)
{
	int x;
	for (x = 0; x < n; x++) {
		if (*cs < *ct) return -1;
		if (*cs++ > *ct++) return 1;
	}
	return 0;
}

/* ************************************************************************* */
/*
 *	Entry Routine: generic_strcmp
 *
 *	This routine is used to compare at most n characters of string cs to
 *	string ct.
 *
 *	Parameters:
 *		"n"	 (assume n <=255)
 *
 *	Returns:
 *		<0 if cs<ct, 0 if cs==ct, or >0 if cs>ct
 *
 */
ENTRY int
generic_strcmp (const char *str1, const char *str2)
{
	char ch1, ch2;
	while (1) {
		ch1 = *str1++;
		ch2 = *str2++;

		if (ch1 < ch2) return -1;
		if (ch1 > ch2) return 1;
		if (ch1 == 0) break;
	}
	return 0;
}

/* ************************************************************************* */
/*
 *	Entry Routine: bincmp
 *
 *	This routine is used to compare up to n characters of one string to another, case sensitive.
 *
 *	Parameters:
 *		"n"	 (assume n <=255)
 *
 *	Returns:
 *		<0 if cs== ct, 1 if cs!=ct
 *
 */

ENTRY int
bincmp(char *str1, char *str2, int len)
{
	int i = 0;

	if (len == 0)
		return 1;

	while (i < len) {
		if (*str1 == *str2) {
			str1++;
			str2++;
			i++;
		}
		else {
			return 1;
		}
	}
	return 0;
}

/* ************************************************************************* */
/*
 *	Entry Routine: generic_stricmp
 *
 *	This routine is used to compare one string to another, case insensitive.
 *
 *	Parameters:
 *		"n"	 (assume n <=255)
 *
 *	Returns:
 *		<0 if cs<ct, 0 if cs==ct, or >0 if cs>ct
 *
 */

ENTRY int
generic_stricmp (const char *str1, const char *str2)
{
	/* a lot of arches don't seem to have this, so for now just use the vocal version */
	char ch1, ch2;
	while (1) {
		ch1 = *str1++;
		ch2 = *str2++;

		if (ch1 >= 'A' && ch1 <= 'Z') ch1 += 32;
		if (ch2 >= 'A' && ch2 <= 'Z') ch2 += 32;

		if (ch1 < ch2) return -1;
		if (ch1 > ch2) return 1;
		if (ch1 == 0) break;
	}
	return 0;
}

/* ************************************************************************* */
/*
 *	Entry Routine: generic_strincmp
 *
 *	This routine is used to compare at most n characters of string cs to
 *	string ct, case insensitive.
 *
 *	Parameters:
 *		"n"	 (assume n <=255)
 *
 *	Returns:
 *		<0 if cs<ct, 0 if cs==ct, or >0 if cs>ct
 *
 */

ENTRY int
generic_strincmp (const char *str1, const char *str2, int len)
{
	char ch1, ch2;
	while (len > 0) {
		ch1 = *str1++;
		ch2 = *str2++;

		if (ch1 >= 'A' && ch1 <= 'Z') ch1 += 32;
		if (ch2 >= 'A' && ch2 <= 'Z') ch2 += 32;

		if (ch1 < ch2) return -1;
		if (ch1 > ch2) return 1;
		if (ch1 == 0) return 0;
		len--;
	}
	return 0;
}

/* ************************************************************************* */
/*
 *	Entry Routine: generic_stristr
 *
 *	This routine is used to search for one string inside another, case insensitive.
 *
 *	Parameters:
 *		(char *str1): string to search in
 *		(char *str2): string to look for
 *
 *	Returns:
 *		(char *): pointer to first occurrence(beginning of string) of str2 in str1, NULL if not found
 *
 */
ENTRY char *
generic_stristr (const char *str1, const char *str2)
{
	const char *temp1 = str1;
	int len;
	if (!str1 || !temp1) {
		return NULL;
	}

	len = strlen(str2);

	while (*temp1) {
		if (!generic_strincmp (temp1, str2, len)) {
			return (char *) temp1;
		} else {
			temp1++;
		}
	}
	return NULL;
}

/* ************************************************************************* */
/*
 *	Entry Routine: generic_strlen
 *
 *	This routine is used to return length of cs.
 *
 *	Parameters:
 *		"n"	 (assume n <=255)
 *
 *	Returns:
 *		length of cs
 *
 */
ENTRY int
generic_strlen (const char *cs)
{
	int x = 0;
	while ((*cs++ & 0xff) != '\0')
		x++;
	return x;
}

size_t strlen (const char *string)
{
	size_t n = (size_t)-1;
	const char *s = string - 1;
	size_t l = 2000;

	do {
		n++;
	} while (*++s && --l);

	if (l) {
		return n;
	}

	return 0;
}

/* ************************************************************************* */
/*
 *	Entry Routine: generic_strlwr
 *
 *	This routine is used to convert uppercase letters in a string to lowercase.
 *
 *	Parameters:
 *		"n"	 (assume n <=255)
 *
 *	Returns:
 *		non-zero if true
 *
 */
ENTRY char *
generic_strlwr (char *cs)
{
	char *temp;

	temp = cs;
	while (*cs != '\0') {
		if ((*cs >= 0x41) && (*cs <= 0x5a)) {
			*cs |= 0x20;
		}
		cs++;
	}
	return temp;
}

/* ************************************************************************* */
/*
 *	Entry Routine: generic_strupr
 *
 *	This routine is used to convert lowercase letters in a string to uppercase.
 *
 *	Parameters:
 *		"n"	 (assume n <=255)
 *
 *	Returns:
 *		non-zero if true
 *
 */
ENTRY char *
generic_strupr (char *cs)
{
	char *temp;

	temp = cs;
	while (*cs != '\0') {
		if ((*cs >= 0x61) && (*cs <= 0x7a)) {
			*cs &= 0xdf;
		}
		cs++;
	}
	return temp;
}

/* ************************************************************************* */
/*
 *	Entry Routine: generic_strchr
 *
 *	This routine is used to point to the first occurrence of c in cs or NULL
 *	if not present.
 *
 *	Parameters:
 *		"n"	 (assume n <=255)
 *
 *	Returns:
 *		non-zero if true
 *
 */
ENTRY char *
generic_strchr (char *cs, char c)
{
	while (*cs != '\0') {
		if (*cs == c) return cs;
		cs++;
	}
	return NULL;
}

/* ************************************************************************* */
/*
 *	Entry Routine: generic_strncat
 *
 *	This routine is used to compare string cs to string ct.
 *
 *	Parameters:
 *		"n"	 (assume n <=255)
 *
 *	Returns:
 *		<0 if cs<ct, 0 if cs==ct, or >0 if cs>ct
 *
 */
ENTRY char *
generic_strncat (char *cs, const char *ct, uint16 n)
{
	char c;
	char *s = cs;

	/* Find the end of cs.  */
	do
		c = *cs++;
	while (c != '\0');

	/* Make cs point before next character, so we can increment
 	it while memory is read (wins on pipelined cpus).  */
	cs -= 2;

	if (n >= 4) {
		size_t n4 = n >> 2;
		do {
			c = *ct++;
			*++cs = c;
			if (c == '\0')
				return s;
			c = *ct++;
			*++cs = c;
			if (c == '\0')
				return s;
			c = *ct++;
			*++cs = c;
			if (c == '\0')
				return s;
			c = *ct++;
			*++cs = c;
			if (c == '\0')
				return s;
		} while (--n4 > 0);
		n &= 3;
	}
	while (n > 0) {
		c = *ct++;
		*++cs = c;
		if (c == '\0')
			return s;
		n--;
	}

	if (c != '\0')
		*++cs = '\0';
	return s;
}

/* ************************************************************************* */
/*
 *	Entry Routine: generic_strcat
 *
 *	This routine is used to compare at most n characters of string cs to
 *	string ct.
 *
 *	Parameters:
 *		"n"	 (assume n <=255)
 *
 *	Returns:
 *		<0 if cs<ct, 0 if cs==ct, or >0 if cs>ct
 *
 */
ENTRY char *
generic_strcat (char *cs, const char *ct)
{
	char *s1 = cs;
	const char *s2 = ct;
	char c;

	/* Find the end of the string.  */
	do
		c = *s1++;
	while (c != '\0');

	/* Make S1 point before the next character, so we can increment
	it while memory is read (wins on pipelined cpus).  */
	s1 -= 2;

	do {
		c = *s2++;
		*++s1 = c;
	}
	while (c != '\0');
	return cs;
}

/* ************************************************************************* */
/*
 *	Entry Routine: generic_min
 *
 *	This routine is used to compare two values and return the smaller of the two.
 *
 *	Parameters:
 *		"a" input value to compare
 *		"b" input value to compare
 *
 *	Returns:
 *		the smaller of two values
 *
 */
ENTRY uint16
generic_min (uint16 a, uint16 b)
{
	return (((a) < (b)) ? (a) : (b));
}

/* ************************************************************************* */
/*
 *	Entry Routine: generic_max
 *
 *	This routine is used to compare two values and return the larger of the two.
 *
 *	Parameters:
 *		"a" input value to compare
 *		"b" input value to compare
 *
 *	Returns:
 *		the larger of two values
 *
 */
ENTRY uint16
generic_max (uint16 a, uint16 b)
{
	return (((a) > (b)) ? (a) : (b));
}

/* ************************************************************************* */
/*
 *	Entry Routine: generic_atol
 *
 *	This routine is used to convert a string to a long.
 *
 *	Parameters:
 *		"ch" the input string
 *
 *	Returns:
 *		the converted value of the input string
 *
 */
ENTRY sint31
generic_atol (const char *ch)
{
	/* this truncates the result, it does NOT round */
	sint31 result;
	sint15 sign;
	sint15 x;

	if (ch == NULL) return 0;

	/* first, pull sign char */
	sign = 1;
	if (*ch == '-') {
		sign = -1;
		ch++;
	}
	else if (*ch == '+') ch++;

	/* sanity, make sure we have a digit following sign */
	if (*ch < '0' || *ch > '9') return 0;

	/* add up all the digits */
	result = 0;
	while(*ch >= '0' && *ch <= '9') {
		x = *ch++ - '0';
		result = result * 10 + x;
	}
	if (sign < 0) result = -result;

	return result;
}

/* ************************************************************************* */
/*
 *	Entry Routine: generic_atoi
 *
 *	This routine is used to convert a string to an int.
 *
 *	Parameters:
 *		"ch" the input string
 *
 *	Returns:
 *		the converted value of the input string
 *
 */
ENTRY uint32
generic_atoi (const char *ch)
{
	return (uint32)generic_atol(ch);
}

/* ************************************************************************* */
/*
 *	Entry Routine: generic_atoh
 *
 *	This routine is used to translate a character into a hex value.
 *
 *	Parameters:
 *		"file_char" which is the character to be translated.
 *
 *	Returns:
 *		The result of the translation.
 */
ENTRY uint8
generic_atoh (char file_char)
{
	uint8 return_val;

	switch (file_char) {
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
		return_val = file_char - '0';
		break;
	case 'a': case 'A':
		return_val = 0x0a;
		break;
	case 'b': case 'B':
		return_val = 0x0b;
		break;
	case 'c': case 'C':
		return_val = 0x0c;
		break;
	case 'd': case 'D':
		return_val = 0x0d;
		break;
	case 'e': case 'E':
		return_val = 0x0e;
		break;
	case 'f': case 'F':
		return_val = 0x0f;
		break;
	default:
		return_val = 0xff;
		break;
	}
	return (return_val);
}

/* ************************************************************************* */
/*
 *	Entry Routine: generic_vsprintf
 *
 *	This routine is used to replace the standard library routine generic_vsprintf.
 *	Formats string in buffer.
 *
 *	Parameters:
 *		"s"	output string pointer
 *		"ct"	input string pointer
 *
 *	Returns:
 *		length of string NOT including trailing null.
 *
 */
ENTRY int
generic_vsprintf (char *buf, const char *format_string, va_list list)
{

	SYS_vsprintf (buf, (char * )format_string, list);
	return generic_strlen (buf) - 1;
}

/* ************************************************************************* */
/*
 *	Entry Routine: generic_vsnprintf
 *
 *	This routine is used to replace the standard library routine generic_vsnprintf.
 *	Formats string in buffer.
 *
 *	Parameters:
 *		"s"	output string pointer
 *		"ct"	input string pointer
 *
 *	Returns:
 *		length of string NOT including trailing null.
 *
 */
ENTRY int
generic_vsnprintf (char *buf, int size, const char *format_string, va_list list)
{
	extern vsnprintf (char *buf, int size, const char *format_string, va_list list);

	vsnprintf (buf, size, format_string, list);
	return generic_strlen (buf) - 1;
}

/* ************************************************************************* */
/*
 *	Entry Routine: generic_sprintf
 *
 *	This routine is used to replace the standard library routine sprintf.
 *
 *	Parameters:
 *		"s"	output string pointer
 *		"ct"	input string pointer
 *
 *	Returns:
 *		length of string NOT including trailing null.
 *
 */
ENTRY int
generic_sprintf (char *buf, const char *format_string, ... )
{
	va_list temp_argptr;
	int len;
	va_start (temp_argptr, format_string);
	len = generic_vsprintf (buf, format_string, temp_argptr);
	va_end (temp_argptr);
	return len;
}

ENTRY int
generic_snprintf (char *buf, int size, const char *format_string, ... )
{
	va_list temp_argptr;
	int len;
	va_start (temp_argptr, format_string);
	len = generic_vsnprintf (buf, size, format_string, temp_argptr);
	va_end (temp_argptr);
	return len;
}

/* ************************************************************************* */

ENTRY void *
generic_memcpy (void *to, const void *from, unsigned int n)
{
	register char *rto   = (char *) to;
	register char *rfrom = (char *) from;
	register size_t rn;

	for (rn = 0; rn < n; rn++) *rto++ = *rfrom++;
	return (to);
}
