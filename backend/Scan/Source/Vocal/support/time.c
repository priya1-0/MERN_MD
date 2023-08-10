
/* ************************************************************************* */
/*
 *	time.c
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
 *	This file contains general purpose time conversion routines
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

#include "support/support.h"

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

/* ************************************************************************* */

/* Convert time count in seconds to printable days:hr:min:sec format */
ENTRY char *
tformat (sint31 t)
{
	static char buf[17], *cp;
	unsigned int days, hrs, mins, secs;
	int minus;

	if (t < 0) {
		t = - t;
		minus = 1;
	} else
		minus = 0;

	secs = t % 60;
	t /= 60;
	mins = t % 60;
	t /= 60;
	hrs = t % 24;
	t /= 24;

	days = t;
	if (minus) {
		cp = buf + 1;
		buf[0] = '-';
	} else
		cp = buf;
	sprintf(cp,"%u:%02u:%02u:%02u",days,hrs,mins,secs);

	return buf;
}

/* ************************************************************************* */

static const sint15 dayspermonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static const char *const day[7]  = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
static const char *const mon[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
									"Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

/* ************************************************************************* */

ENTRY char *
ctime (const time_t *timep)
{
	return asctime (gmtime (timep));
}

/* ************************************************************************* */

ENTRY char *
asctime (const struct tm *tp)
{
	static char buffer[26];

	sprintf (buffer, "%s %s%3d %02d:%02d:%02d %d\n",
			 day[tp->tm_wday], mon[tp->tm_mon], tp->tm_mday, tp->tm_hour,
			 tp->tm_min, tp->tm_sec, (tp->tm_year + 1900));
	return buffer;
}

/* ************************************************************************* */

#define IS_LEAPYEAR(y) (((y % 4) == 0) && (((y % 100) != 0) || ((y % 400) == 0)))

#define DAYS_IN_YEAR(y) (365 + IS_LEAPYEAR(y))
#define DAYS_IN_MONTH(m,y) (dayspermonth[m] + ((m == 1) && IS_LEAPYEAR(y)))

#define YEAR_START	1970	/* Start clock at January 1, 1970 */
#define JAN11970	4		/* January 1, 1970 is a Thursday */

ENTRY struct tm *
localtime (const time_t *timep)
{
	static struct tm local;
	time_t time = *timep;
	int year, days;

	local.tm_sec = 0;
	local.tm_min = 0;
	local.tm_hour = 0;
	local.tm_mday = 1;
	local.tm_mon = 0;
	local.tm_year = 0;
	local.tm_wday = 0;
	local.tm_yday = 0;
	local.tm_isdst = 0;

	if (time == 0) return &local;

	/* Compute hours, minutes and seconds */
	local.tm_sec = time % 60;
	local.tm_min = (time / 60) % 60;
	local.tm_hour = (time / (60 * 60)) % 24;

	/* Convert into days since 1970 and proceed */
	time /= (60L * 60L * 24L);
	local.tm_wday = (JAN11970 + time) % 7;

	/* Determine the year by subtracting number of days in each year */
	year = YEAR_START;
	while (time >= (days = DAYS_IN_YEAR (year))) {
		time -= days;
		++year;
	}

	local.tm_year = year - 1900;	/* Structure member stored relative to 1900 */
	local.tm_yday = days;

	while (time >= (days = DAYS_IN_MONTH (local.tm_mon, year))) {
		time -= days;
		local.tm_mon++;
	}
	local.tm_mday += time;			/* Structure member is day of month 1-31 */

	return &local;
}

/* ************************************************************************* */

ENTRY struct tm *
gmtime (const time_t *timep)
{
	time_t gm_time = *timep;

	return localtime (&gm_time);
}

/* ************************************************************************* */

ENTRY time_t
mktime (const struct tm *tp)
{
	time_t result;
	int i;
	int year;

	if ((tp->tm_sec < 0) || (tp->tm_sec > 59)) {
		print_debug_on (("mktime() - sec %d\n", tp->tm_sec));
		return (time_t)-1;
	}

	if ((tp->tm_min < 0) || (tp->tm_min > 59)) {
		print_debug_on (("mktime() - min %d\n", tp->tm_min));
		return (time_t)-1;
	}

	if ((tp->tm_hour < 0) || (tp->tm_hour > 23)) {
		print_debug_on (("mktime() - hour %d\n", tp->tm_hour));
		return (time_t)-1;
	}

	if ((tp->tm_mon < 0) || (tp->tm_mon > 11)) {
		print_debug_on (("mktime() - month %d\n", tp->tm_mon));
		return (time_t)-1;
	}

	if ((tp->tm_mday < 1) || (tp->tm_mday > dayspermonth[tp->tm_mon])) {
		print_debug_on (("mktime() - day %d\n", tp->tm_mday));
		return (time_t)-1;
	}

	year = tp->tm_year + 1900;
	if ((year < YEAR_START) || (year > (YEAR_START + 200))) {
		print_debug_on (("mktime() - year %d\n", tp->tm_year));
		return (time_t)-1;
	}

	year -= YEAR_START;
	print_debug_off (("mktime() - year offset is %d\n", year));

	/* Compute the number of days since 1970 */
	result = (((sint31) year) * 365) + ((sint31) ((year + 2) / 4)) + (sint31) (tp->tm_mday - 1);
	for (i = 0; i < tp->tm_mon; i++) {
		result += (sint31) dayspermonth[i];
	}
	print_debug_off (("mktime() - days is %ld\n", result));

	/* Add hours, minutes and seconds */
	result = (result * 24L * 60L * 60L);
	result += tp->tm_sec + (tp->tm_min * 60L) + (tp->tm_hour * 60L * 60L);
	print_debug_on (("mktime() - total seconds is %ld\n", result));

	return result;
}

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

ENTRY char *
rfc1123_time (const struct tm *tp)
{
	static char buffer[32];

	sprintf (buffer, "%s, %02d %s %d %02d:%02d:%02d GMT", day[tp->tm_wday], tp->tm_mday,
			 mon[tp->tm_mon], (tp->tm_year + 1900), tp->tm_hour, tp->tm_min, tp->tm_sec);

	return buffer;
}

/* ************************************************************************* */

/* Parse time in hrs:min:sec or hrs:min format */
ENTRY uint16
parse_time (struct tm *tmp, char *cp)
{
	tmp->tm_hour = atoi (cp);
	if ((cp = strchr (cp, ':')) != NULLCHAR) {
		tmp->tm_min = atoi (++cp);
		if ((cp = strchr (cp, ':')) != NULLCHAR) {
			tmp->tm_sec = atoi (++cp);
		} else {
			tmp->tm_sec = 0;
		}
		return 0;
	}

	return 1;
}

/* ************************************************************************* */

/* Parse date in year/mon/day format */
ENTRY uint16
parse_date (struct tm *tmp, char *cp)
{
	sint15 year;
	year = atoi (cp);
	if ((year >= 0) && (year < 70))
		year += 2000;
	if (year < 100)
		year += 1900;

	if ((cp = strchr (cp, '/')) != NULLCHAR) {
		tmp->tm_mon = (atoi (++cp)) - 1;
		if ((cp = strchr (cp, '/')) != NULLCHAR) {
			tmp->tm_mday = atoi (++cp);

			tmp->tm_year = year - 1900;
			return 0;
		}
	}

	return 1;
}
