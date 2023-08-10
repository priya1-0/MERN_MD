
/* ************************************************************************* */
/*
 *	netuser.c
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
 *	Module:		NET
 *
 *	This file contains the miscellaneous integer and address format conversion functions.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 20:31:57  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#include "system/system.h"
#include "lansend/global.h"

#include <ctype.h>

#include "net/local.h"

#include "dev/dev.h"
#include "sys/sys.h"

#include "ip/ip.h"

#include "net/local.h"

#define LINELEN 256

int Net_error = 0;

ENTRY void
netuser_init (void)
{
	Net_error = 0;
}

/* Convert Internet address in ascii dotted-decimal format (44.0.0.1) to
 * binary IP address.
 *
 *(This is an old style routine only used by bootpcmd and domain and is
 * not to be used in the future.)
 */
ENTRY sint31
atonl (register char *s)
{
	sint31 n;

	register int i;

	n = 0;
	if (s == NULLCHAR)
		return 0;
	for (i = 24;i >= 0;i -= 8) {
		/* Skip any leading stuff (e.g., spaces, '[') */
		while (*s != '\0' && ! isdigit (*s))
			s++;
		if (*s == '\0')
			break;
		n |= (sint31) atoi (s) << i;
		if ((s = strchr (s, '.')) == NULLCHAR)
			break;
		s++;
	}
	return n;
}

static char buf[SOCKSIZE*4];	/* The static buffer used for all address formatting */

/* Convert an internet address (in host byte order) to a dotted decimal ascii
 * string.
 *
 * 255.255.255.255\0
 */
ENTRY char *
inet_ntoa (sint31 a)
{
	sprintf (buf, "%u.%u.%u.%u", hibyte(hiword(a)), lobyte(hiword(a)),
	    hibyte (loword (a)), lobyte (loword (a)));
	return buf;
}

/* Convert the ethernet address to an ascii string.
 */
ENTRY char *
ethertoa (char *addr)
{
	sprintf (buf, "%02x:%02x:%02x:%02x:%02x:%02x",
		       uchar (addr[0]), uchar (addr[1]), uchar (addr[2]),
		       uchar (addr[3]), uchar (addr[4]), uchar (addr[5]));
	return buf;
}

/* Convert the network part of a socket address to an ascii string.
 *
 * IP - 255.255.255.255\0
 * IPX - 255.255.255.255\0
 */
ENTRY char *
sntoa (struct sockaddr *a)
{
	switch (a->sa_family) {
	case AF_INET:
		return inet_ntoa (a->sin_address);
	case AF_NOVELL:
		return inet_ntoa (a->sns_network);
	case AF_NONE:
		sprintf (buf, "None.");
		return buf;
	default:
		sprintf (buf, "Bad type: %d", a->sa_family);
		return buf;
	}

}

/* Convert the network and host part of a socket address to an ascii string.
 *
 * IP - 255.255.255.255\0
 * IPX - 255.255.255.255:AA:BB:CC:DD:EE:FF\0
 */
ENTRY char *
snhtoa (struct sockaddr *a)
{
	switch (a->sa_family) {
	case AF_INET:
		inet_ntoa (a->sin_address);
		break;
	case AF_NOVELL:
		inet_ntoa (a->sns_network);
		sprintf ((buf + strlen (buf)), ":%02x:%02x:%02x:%02x:%02x:%02x",
			       uchar (a->sns_host[0]), uchar (a->sns_host[1]),
			       uchar (a->sns_host[2]), uchar (a->sns_host[3]),
			       uchar (a->sns_host[4]), uchar (a->sns_host[5]));
		break;
	case AF_NONE:
		sprintf (buf, "None.");
		break;
	default:
		sprintf (buf, "Bad type: %d", a->sa_family);
	}
	return buf;
}

/* Convert the network, host and port of a socket address to an ascii string.
 *
 * IP - 255.255.255.255:1234\0
 * IPX - 255.255.255.255:AA:BB:CC:DD:EE:FF.ABCD\0
 */
ENTRY char *
snhptoa (struct sockaddr *a)
{
	snhtoa (a);

	switch (a->sa_family) {
	case AF_INET:
		sprintf ((buf + strlen (buf)), ":%u", a->sin_port);
		break;
	case AF_NOVELL:
		sprintf ((buf + strlen (buf)), ".%04x", a->sns_port);
	default:;
	}
	return buf;
}

/* Convert the network, host, port, and connection id of a socket address
 * to an ascii string.
 *
 * IP - 255.255.255.255:1234\0
 * IPX - 255.255.255.255:AA:BB:CC:DD:EE:FF.ABCD.EFGH\0
 */
ENTRY char *
snhpctoa (struct sockaddr *a)
{

	snhptoa (a);

	switch (a->sa_family) {
	case AF_NOVELL:
		sprintf ((buf + strlen (buf)), ".%04x", a->sns_cid);
	case AF_INET:
	default:;
	}
	return buf;
}

/* Convert string to doted decimal long integer.
 */
LOCAL int
strto32dd (char *cp, char **ncp, uint32 *np, char sep)
{
	uint32 ddnum, num;
	register int i;

	ddnum = 0;
	if ((*ncp = cp) == NULLCHAR)
		return 1;
	for (i = 24; i >= 0; i -= 8) {
		num = strtoul (*ncp, ncp, 0);
		if (num > 255)
			return 1;
		ddnum |= num << i;
		if ((**ncp == '\0') || (**ncp == sep))
			break;
		if ((**ncp != '.') || (i == 0))
			return 1;
		(*ncp)++;
	}
	if (*ncp != cp)
		*np = ddnum;
	return 0;
}

/* Convert string to colon hex byte array.
 */
LOCAL int
strto8ha (char *cp, char **ncp, uint8 n[], int cnt, char sep)
{
	uint32 num;
	char *scp;
	register int i;

	if ((*ncp = cp) == NULLCHAR)
		return 1;
	for (i = 0; i < cnt; i++) {
		scp = *ncp;
		num = strtoul (scp, ncp, 16);
		if (num > 255)
			return 1;
		if ((**ncp == '\0') || (**ncp == sep)) {
			if (scp != *ncp)
				n[i] = num;
			return 0;
		}
		if (**ncp != ':')
			return 1;
		if (scp != *ncp)
			n[i] = num;
		(*ncp)++;
	}
	return 1;
}

/* Convert an address from ascii to the format defined by the
 * family field of dest, using global addresses to fill in default data.
 */
ENTRY int
atos_err (char *cp, uint16 family, struct sockaddr *dest)
{
	struct sockaddr sa;
	char *ncp, *scp;
	uint32 num;

	if (family >= AF_IFCMAX) {
		printf ("Bad type: %d\n", family);
		return 1;
	}

	/* Check for use of default address */
	if (stricmp (cp, "default") == 0) {
		*dest = Default_addr[family];
		return 0;
	}
	sa = Default_addr[family];

	/* Perform conversion of user input */
	switch (family) {
	case AF_INET:
		/* Address 1.2.3.4: */
		if (strto32dd (cp, &ncp, &sa.sin_address, ':')) {

			/* Process symbolic host names */
			if (cp == ncp) {
				if ((num = resolve (cp)) == 0L) {
					printf ("Unknown hostname: %s\n", cp);
					return 1;
				}
				sa.sin_address = num;
				ncp = strchr (cp, ':');
			}
			else
			{
				printf ("Error in address: %s\n", cp);
				return 1;
			}
		}
		/* Preserve the default port number */
		sa.sin_port = dest->sin_port;

		if (*ncp != ':')
			break;

		/* Port number is just a number */
		scp =++ ncp;
		num = strtoul (ncp, &ncp, 0);
		if ((*ncp != '\0') || (num > 65535)) {
			printf ("Error in port number: %s\n", scp);
			return 1;
		}
		if (scp != ncp)
			sa.sin_port = num;
		break;

	case AF_NOVELL:
		/* Network address 1.2.3.4: */
		if (strto32dd (cp, &ncp, &sa.sns_network, ':')) {
			printf ("Error in network address: %s\n", cp);
			return 1;
		}
		if (*ncp == '\0')
			break;

		/* Host address 1:2:3:4:5:6. */
		scp =++ ncp;
		if (strto8ha (ncp, &ncp, (uint8 *) sa.sns_host, 6, '.')) {
			printf ("Error in host address: %s\n", scp);
			return 1;
		}
		if (*ncp == '\0')
			break;

		/* Port number is a hex number */
		scp =++ ncp;
		num = strtoul (ncp, &ncp, 16);
		if (((*ncp != '\0') && (*ncp != '.')) || (num > 65535)) {
			printf ("Error in port number: %s\n", scp);
			return 1;
		}
		if (scp != ncp)
			sa.sns_port = num;
		if (*ncp == '\0')
			break;

		/* Connection ID is a hex number */
		scp =++ ncp;
		num = strtoul (ncp, &ncp, 16);
		if ((*ncp != '\0') || (num > 65535)) {
			printf ("Error in connection ID: %s\n", scp);
			return 1;
		}
		if (scp != ncp)
			sa.sns_cid = num;
	}
	/* Copy changed address to specified location */
	*dest = sa;
	return 0;
}

/* Convert string to network address and check if any destination route exists.
 */
ENTRY int
atosr_err (char *cp, uint16 family, struct sockaddr *dest, struct route **rpp)
{
	struct route *rp;

	if (atos_err (cp, family, dest))
		return 1;

	if ((rp = rt_lookup (dest)) == NULLROUTE) {
		printf ("Destination unreachable: %s\n", snhtoa (dest));
		return 1;
	}
	*rpp = rp;
	return 0;
}

ENTRY int
atosb_err (char *cp, uint16 family, struct sockaddr *dest)
{
	int retval;
        int i;

	if (((retval = atos_err (cp, family, dest)) == 0) && (family == AF_NOVELL)) {
		/* Check if broadcast adderess is to be used */
		if (memcmp (&dest->sns_host, &Default_addr[AF_NOVELL].sns_host, 6) == 0) {
			for (i = 0; i < 6; i++)
				dest->sns_host[i] = 0xFF;
		}
	}
	return retval;
}

ENTRY int
atosbr_err (char *cp, uint16 family, struct sockaddr *dest, struct route **rpp)
{
	int retval;
        int i;

	if (((retval = atosr_err (cp, family, dest, rpp)) == 0) && (family == AF_NOVELL)) {
		/* Check if broadcast adderess is to be used */
		if (memcmp (&dest->sns_host, &Default_addr[AF_NOVELL].sns_host, 6) == 0) {
			for (i = 0; i < 6; i++)
				dest->sns_host[i] = 0xFF;
		}
	}
	return retval;
}

/* Convert a string of characters into a network mask.
 */
ENTRY int
atom_err (char *cp, uint32 *netmask)
{
	uint32 num;
	char *ncp;

	/* Check for shorthand representation for mask class */
	if (*(cp + 1) == '\0') {
		if (tolower (*cp) == 'a') {
			*netmask = 0xff000000L;
			return 0;
		}
		else if (tolower (*cp) == 'b') {
			*netmask = 0xffff0000L;
			return 0;
		}
		else if (tolower (*cp) == 'c') {
			*netmask = 0xffffff00L;
			return 0;
		}
	}

	/* Process dotted decimal representation */
	if (strchr (cp, '.') != NULLCHAR) {
		if (strto32dd (cp, &ncp, netmask, '\0') == 0) {
			return 0;
		}
	}
	/* Process hex mask or number of bits representations */
	else {
		num = strtoul (cp, &ncp, 0);
		if (*ncp == '\0') {
			if (*cp == '0')
				*netmask = num;
			else
				*netmask = 0xffffffffL << (32 - num);
			return 0;
		}
	}
	printf ("Error in network mask: %s\n", cp);
	return 0;
}

/* Convert string to an ethernet address.
 */
ENTRY int
atoether_err (char *cp, char address[])
{
	char *ncp;
	char local[6];
	int i;

	if (strto8ha (cp, &ncp, (uint8 *) local, 6, '\0')) {
		printf ("Error in ethernet address: %s\n", cp);
		return 1;
	}
	for (i = 0; i < 6; i++)
		address[i] = local[i];
	return 0;
}

/* Convert string to interface pointer.
 */
ENTRY int
atoiface_err (char *cp, struct iface **ifpp)
{
	struct iface *ifp;

	if ((ifp = if_lookup (cp)) == NULLIF) {
		printf ("Unknown device: %s\n",cp);
		return 1;
	}

	*ifpp = ifp;
	return 0;
}

/* Convert string to an signed short integer.
 */
ENTRY int
atoi16s_err (char *cp, sint15 *np)
{
	sint31 num;
	char *ncp;

	if (cp == NULLCHAR)
		return 1;

	num = strtol (cp, &ncp, 0);
	if (*ncp != '\0') {
		printf ("Not a valid number: %s\n", cp);
		return 1;
	}

	if ((num > 32767L) || (num < - 32768L)) {
		printf ("Number out of range: %s\n", cp);
		return 1;
	}

	*np = num;
	return 0;
}

/* Convert string to an unsigned short integer.
 */
ENTRY int
atoi16u_err (char *cp, uint16 *np)
{
	sint31 num;
	char *ncp;

	if (cp == NULLCHAR)
		return 1;

	num = strtoul (cp, &ncp, 0);
	if (*ncp != '\0') {
		printf ("Not a valid number: %s\n", cp);
		return 1;
	}

	if (num > 65535L) {
		printf ("Number out of range: %s\n", cp);
		return 1;
	}

	*np = num;
	return 0;
}

/* Convert string to an hex short integer.
 */
ENTRY int
atoi16uh_err (char *cp, uint16 *np)
{
	sint31 num;
	char *ncp;

	if (cp == NULLCHAR)
		return 1;

	num = strtoul (cp, &ncp, 16);
	if (*ncp != '\0') {
		printf ("Not a valid number: %s\n", cp);
		return 1;
	}

	if (num > 65535L) {
		printf ("Number out of range: %s\n", cp);
		return 1;
	}

	*np = num;
	return 0;
}

/* Convert string to a signed long integer.
 */
ENTRY int
atoi32s_err (char *cp, sint31 *np)
{
	sint31 num;
	char *ncp;

	if (cp == NULLCHAR)
		return 1;

	num = strtol (cp, &ncp, 0);
	if (*ncp != '\0') {
		printf ("Not a valid number: %s\n", cp);
		return 1;
	}

	*np = num;
	return 0;
}

/* Convert string to an unsigned long integer.
 */
ENTRY int
atoi32u_err (char *cp, uint32 *np)
{
	uint32 num;
	char *ncp;

	if (cp == NULLCHAR)
		return 1;

	num = strtoul (cp, &ncp, 0);
	if (*ncp != '\0') {
		printf ("Not a valid number: %s\n", cp);
		return 1;
	}

	*np = num;
	return 0;
}

/* Convert string to an hex long integer.
 */
ENTRY int
atoi32uh_err (char *cp, uint32 *np)
{
	uint32 num;
	char *ncp;

	if (cp == NULLCHAR)
		return 1;

	num = strtoul (cp, &ncp, 16);
	if (*ncp != '\0') {
		printf ("Not a valid number: %s\n", cp);
		return 1;
	}

	*np = num;
	return 0;
}

/* Display MIB table.
 */
ENTRY void
print_mib (struct mib_entry mib[], int entries)
{
	int i, j;

	for (j = i = 1; i <= entries; i++) {
		if ((mib[i].name == NULLCHAR) || (mib[i].name == ""))
			continue;
		printf ("(%2u) %-23s%10lu", i, mib[i].name,
			(long) mib[i].value.integer);
		if (j++ % 2)
			printf ("  ");
		else
			printf ("\n");
	}
	if ((j % 2) == 0)
		printf ("\n");
}
