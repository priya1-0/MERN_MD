
/* ************************************************************************* */
/*
 *	account.c
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
 *	Module:		MAIN
 *
 *	This file contains the account maintanence functions.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 19:56:06  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#include "system/system.h"
#include "lansend/global.h"

#include "net/net.h"
#include "sys/sys.h"
#include "dev/dev.h"

#include "ip/ip.h"

#include "lansend/local.h"

/* ************************************************************************* */

struct account *Accounts = NULLACCOUNT;

/* ************************************************************************* */

ENTRY void
account_init (void)
{
	Accounts = NULLACCOUNT;
}

/****************************************************************************+F
 *
 *  Function: account_find
 *
 *  Description: Looks up the specified account and matches the password
 *               if supplied.
 *
 *  Parameters:
 *
 *    "name" is the account name
 *    "password" is the optional password to be matched
 *
 *  Return value: account structure pointer
 *
 **************************************************************************** - F
 */
ENTRY struct account *
account_find (char *name, char *password)
{
	struct account *ap;

#define pw password

	for (ap = Accounts; ap != NULLACCOUNT; ap = ap->next) {
		if (strcmp (ap->name, name) == 0) {
			if (password == NULLCHAR)
				return ap;
			if (strcmp (ap->password, pw) == 0)
				return ap;
			else
				return NULLACCOUNT;
		}
	}
	return NULLACCOUNT;
}

/****************************************************************************+F
 *
 *  Function: doaccadd
 *
 *  Description: Command to add / modify an account.
 *
 *  Parameters:
 *
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is an unused pointer
 *
 *  Command line: account add <name> <password> [protocol [address [message]]]
 *
 *  Return value: 0 (success)
 *
 **************************************************************************** - F
 */
LOCAL int
doaccadd (int argc, char *argv[], void *p)
{
	struct account *ap, *aptmp;
	int isave;

	aptmp = NULLACCOUNT;
	for (ap = Accounts; ap != NULLACCOUNT; ap = ap->next) {
		if ((isave = strcmp (ap->name, argv[1])) == 0) {
			free (ap->password);
			if (argc > 3)
				free (ap->protocol);
			if (argc > 4)
				free (ap->address);
			if (argc > 5)
				free (ap->message);
			break;
		}
		/* Save insertion point */
		else if (isave < 0)
			aptmp = ap;
	}
	if (ap == NULLACCOUNT) {
		ap = (struct account *) callocw (1, sizeof (struct account));
		/* Link in the account */
		if (aptmp == NULLACCOUNT) {
			ap->next = Accounts;
			Accounts = ap;
		} else {
			ap->next = aptmp->next;
			aptmp->next = ap;
		}
		ap->name = strdup (argv[1]);
	}

	ap->password = strdup (argv[2]);

	if ((argc > 3) && (argv[3][0] != 0))
		ap->protocol = strdup (argv[3]);
	if ((argc > 4) && (argv[4][0] != 0))
		ap->address = strdup (argv[4]);
	if ((argc > 5) && (argv[5][0] != 0))
		ap->message = strdup (argv[5]);
	return 0;
}

/****************************************************************************+F
 *
 *  Function: doaccdrop
 *
 *  Description: Command to drop an account.
 *
 *  Parameters:
 *
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is an unused pointer
 *
 *  Command line: account drop <name>
 *
 *  Return value: 0 (success)
 *                1 (account does not exist)
 *
 **************************************************************************** - F
 */
LOCAL int
doaccdrop (int argc, char *argv[], void *p)
{
	struct account *ap, *aptmp;

	for (ap = Accounts; ap != NULLACCOUNT; ap = ap->next) {
		if (strcmp (argv[1], ap->name) == 0) {
			free (ap->password);
			free (ap->protocol);
			free (ap->address);
			free (ap->message);
			/* Remove from account list */
			if (ap == Accounts) {
				Accounts = ap->next;
			} else {
				/* Search for entry just before this one
				 *(necessary because list is only singly - linked.)
				 */
				for (aptmp = Accounts; aptmp != NULLACCOUNT; aptmp = aptmp->next)
					if (aptmp->next == ap)
					break;
				if ((aptmp != NULLACCOUNT) && (aptmp->next == ap))
					aptmp->next = ap->next;
			}
			free (ap);
			return 0;
		}
	}
	return 1;
}

/****************************************************************************+F
 *
 *  Function: doaccshow
 *
 *  Description: Command to show all accounts.
 *
 *  Parameters:
 *
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is an unused pointer
 *
 *  Command line: account show
 *
 *  Return value: 0 (success)
 *
 **************************************************************************** - F
 */
LOCAL int
doaccshow (int argc, char *argv[], void *p)
{
	struct account *ap;

	if (Accounts != NULLACCOUNT) {
		printf ("Account    Password         Protocol   Address    Message\n");
		for (ap = Accounts; ap != NULLACCOUNT; ap = ap->next) {
			printf ("%-10s %-16s %-10s %-10s %-25s\n", ap->name, ap->password, ((ap->protocol) ? ap->protocol : "None"), ((ap->address) ? ap->address : "None"), ((ap->message) ? ap->message : ""));
		}
	}
	return 0;
}

/****************************************************************************+F
 *
 *  Function: doacctest
 *
 *  Description: Command to locate an account from a user name and display
 *               the entry.
 *
 *  Parameters:
 *
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is an unused pointer
 *
 *  Command line: account test <name> <password>
 *
 *  Return value: 0 (success always)
 *
 **************************************************************************** - F
 */
LOCAL int
doacctest (int argc, char *argv[], void *p)
{
	struct account *ap;

	if ((ap = account_find (argv[1], argv[2])) != NULLACCOUNT) {
		printf ("%-10s %-16s %-10s %-10s %-25s\n", ap->name, ap->password, ((ap->protocol) ? ap->protocol : "None"), ((ap->address) ? ap->address : "None"), ((ap->message) ? ap->message : ""));
	}
	return 0;
}

/****************************************************************************+F
 *
 *  Function: doaccread
 *
 *  Description: Command to read an account file to add accounts.
 *
 *  Parameters:
 *
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is an unused pointer
 *
 *  Command line: account read [file]
 *
 *  Return value: 0 (success always)
 *
 **************************************************************************** - F
 */
LOCAL int
doaccread (int argc, char *argv[], void *p)
{
	char *cp;
	FILE *fp;
	char inbuf[240];
	char acc_cmdbuf[256];

	if (argc < 2) {
		cp = Account;
	}
	else
		cp = argv[1];

	if ((fp = fopen (cp, READ_TEXT)) != NULLFILE) {
		cp = Curproc->prefix;
		Curproc->prefix = NULLCHAR;
		/* Start reading the account file */
		while (fgets (inbuf, sizeof (inbuf), fp) != NULLCHAR) {
			if (inbuf[0] == '#')
				continue;
			strcpy (acc_cmdbuf, "account add ");
			strcat (acc_cmdbuf, inbuf);

			if (cmdparse (Cmds, acc_cmdbuf, NULL) != 0) {
				printf ("input line: %s", inbuf);
			}
		}
		fclose (fp);
		Curproc->prefix = cp;
	}
	return 0;
}

/****************************************************************************+F
 *
 *  Function: doaccsave
 *
 *  Description: Command to save current account to a file.
 *
 *  Parameters:
 *
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is an unused pointer
 *
 *  Command line: account save [file]
 *
 *  Return value: 0 (success always)
 *
 **************************************************************************** - F
 */
ENTRY int
doaccsave (int argc, char *argv[], void *p)
{
	char *cp;
	FILE *fp;
	struct account *ap;

	if (argc < 2) {
		unlink (Account_bak);
		rename (Account, Account_bak);
		cp = Account;
	}
	else
		cp = argv[1];

	if ((fp = fopen (cp, WRITE_TEXT)) != NULLFILE) {
		/* Start writing to the account file */
		fprintf (fp, "# Account Password Protocol Address Message\n");
		for (ap = Accounts; ap != NULLACCOUNT; ap = ap->next) {
			fprintf (fp, "%s %s %s \"%s\" \"%s\"\n", ap->name, ap->password, ((ap->protocol) ? ap->protocol : "\"\""), ((ap->address) ? ap->address : ""), ((ap->message) ? ap->message : ""));
		}
		fclose (fp);
	}
	return 0;
}

/****************************************************************************+C
 *
 *  Command processing table for "account" subcommands
 *
 ******************************************************************************
 */
static const struct cmds Accountcmds[] = {
	{"add",			doaccadd,			0,	3,	"<name> <password> [protocol [address [message]]]"},
	{"drop",		doaccdrop,			0,	2,	"<name>"},
	{"read",		doaccread,			0,	0,	"[file]"},
	{"show",		doaccshow,			0,	0,	""},
	{"save",		doaccsave,			0,	0,	"[file]"},
	{"test",		doacctest,			0,	3,	"<name> <password>"},
	{NULLCHAR}
};
/****************************************************************************-C
 */

/****************************************************************************+F
 *
 *  Function: doaccount
 *
 *  Description: Dispatch to process account subcommands.
 *
 *  Parameters:
 *
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is an unused pointer
 *
 *  Return value: 0 (success)
 *                else (error)
 *
 **************************************************************************** - F
 */
ENTRY int
doaccount (int argc, char *argv[], void *p)
{
	return subcmd (Accountcmds, argc, argv, p);
}
