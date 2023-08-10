
/* ************************************************************************* */
/*
 *	cmdparse.c
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
 *	Module:		SYS
 *
 *	This file contains the command line parsing functions.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 20:46:45  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#include "system/system.h"
#include "lansend/global.h"

#include <ctype.h>

#include "net/net.h"
#include "sys/sys.h"
#include "dev/dev.h"

#include "ip/ip.h"

#include "sys/local.h"

#include "term/term.h"
#include "wan/wan.h"

/* ************************************************************************* */

static const char FAR Cmdcharacterhelp[] =
"\".\" moves up one level, \"/\" to restart from top, ESC to return to top\n";

struct boolcmd {
	char *str;	/* Token */
	int val;	/* Value */
};

/* ************************************************************************* */

static const struct boolcmd Boolcmds[] = {
	{"y",		1},	/* Synonyms for "true" */
	{"yes",		1},
	{"true",	1},
	{"on",		1},
	{"1",		1},
	{"set",		1},
	{"enable",	1},

	{"n",		0},	/* Synonyms for "false" */
	{"no",		0},
	{"false",	0},
	{"off",		0},
	{"0",		0},
	{"clear",	0},
	{"disable",	0},
	{NULLCHAR}
};

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

LOCAL char *
stringparse (char *line)
{
	register char *cp = line;
	uint32 num;

	while (*line != '\0' && *line != '\"') {
		if (*line == '\\') {
			line++;
			switch (*line++) {
			case 'n':
				*cp++= '\n';
				break;
			case 't':
				*cp++= '\t';
				break;
			case 'v':
				*cp++= '\v';
				break;
			case 'b':
				*cp++= '\b';
				break;
			case 'r':
				*cp++= '\r';
				break;
			case 'f':
				*cp++= '\f';
				break;
			case 'a':
				*cp++= '\a';
				break;
			case '\\':
				*cp++= '\\';
				break;
			case '\?':
				*cp++= '\?';
				break;
			case '\'':
				*cp++= '\'';
				break;
			case '\"':
				*cp++ = '\"';
				break;
			case 'x':
				line--;
				num = strtoul (line, &line, 16);
				*cp++= (char) num;
				break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
				line--;
				num = strtoul (line, &line, 8);
				*cp++= (char) num;
				break;
			case '\0':
				return NULLCHAR;
			default:
				*cp++= *(line -1);
				break;
			};
		} else {
			*cp++= *line++;
		}
	}

	if (*line == '\"')
		line++; 	/* skip final quote */
	*cp = '\0';		/* terminate string */
	return line;
}

/* ************************************************************************* */

ENTRY void
cmdnotfound (void)
{
	printf ("Unknown command, type \"?\" for help\n");
	return;
}

/* ************************************************************************* */

ENTRY void
cmdhelp (const struct cmds tab[], int level)
{
	register const struct cmds *cmdp;
	int i;
	char buf[66];

	printf("Available commands:\n");
	memset (buf, ' ', sizeof (buf));
	buf[64] = '\n';
	buf[65] = '\0';
	for (i = 0, cmdp = tab;cmdp->name != NULL;cmdp++, i = (i + 1) % 4) {
		/* Do not display hidden commands normally */
		while ((!level) && (tolower (cmdp->name[0]) != cmdp->name[0])) {
			cmdp++;
			if (cmdp->name == NULLCHAR)
				break;
		}
		if (cmdp->name == NULLCHAR)
			break;
		/* Copy the command name to the buffer for the display */
		strncpy (&buf[i*16], cmdp->name, strlen (cmdp->name));
		buf[i*16] = tolower (buf[i*16]);
		if (cmdp->argc_errmsg == NULLCHAR)
			buf[i*16 + strlen (cmdp->name) ] = '/';
		if (i == 3) {
			printf (buf);
			memset (buf, ' ', sizeof (buf));
			buf[64] = '\n';
			buf[65] = '\0';
		}
	}
	if (i != 0)
		printf (buf);
	printf (Cmdcharacterhelp);

	return;
}

/* ************************************************************************* */

ENTRY int
cmderror (const struct cmds *cmdp, int argc, char *argv[])
{
	int i, j;
	register char *cp;

	cp = cmdp->argc_errmsg;
	/* Check for insufficient arguments or help desired at this level */
	if ((argc < cmdp->argcmin) || ((argv[1][0] == '?') && (cp != NULLCHAR))) {
		if (cp == NULLCHAR) return -1;	/* Always fail if insufficient in some way */
		printf ("Usage: ");
		/* Check for character not to prefix command path */
		if (*cp != '^') {
			/* Find start of command arguments */
			for (i = 0; i > - NARG; i--) {
				if (argv[i] == NULLCHAR) {
					/* Print command arguments */
					j = i;
					for (i++; i <= 0; i++) {
						if ((j + 2) == i)
							printf ("%s ", argv[i]);
						else
							printf ("%c%s ", tolower (argv[i][0]), &argv[i][1]);
					}
				break;
				}
			}
		}
		else
			cp++;		/* Eat the '^' up */
		printf ("%s\n", cp);
		return -1;
	}
	return 0;
}

/* ************************************************************************* */

ENTRY int
cmdparse (const struct cmds cmds[], register char *line, void *p)
{
	const struct cmds *cmdp;
	char *argv[NARG], *cp;
	char **pargv;
	int argc, i, retval = -1;
	int found = 0;
	char c;

	/* Remove cr/lf */
	rip (line);

	/* Escape anywhere cancels command line and clear command prefix */
	for (cp = line; *cp != '\0'; cp++) {
		if (*cp == ASCII__ESC) {
			if (Curproc->prefix != NULLCHAR) {
				free (Curproc->prefix);
				Curproc->prefix = NULLCHAR;
			}
			return 0;
		}
	}

	/* Initialize argv array */
	for (argc = 0;argc < NARG;argc++)
		argv[argc] = NULLCHAR;

	/* Reserve argv[0] as indicator for start of argument list */
	for (argc = 1;argc < NARG;) {
		register int qflag = FALSE;

		/* Skip leading white space */
		while (*line == ' ' || *line == '\t')
			line++;
		if (*line == '\0')
			break;
		/* return if comment character first non-white */
		if (argc == 1  &&  *line == '#') {
			retval = 0;
			goto prefix;
		}
		/* Check for quoted token */
		if (*line == '"') {
			line++;	/* Suppress quote */
			qflag = TRUE;
		}
		if ((*(line + 1) == ' ') || (*(line + 1) == 0)) {
			/* Check for '/' to specify command from top level */
			if ((*line == '/') || (*line == '\\')) {
				line++;
				argc = 1;
				continue;
			}
			/* Check for '.' to specify command one level up */
			if (*line == '.') {
				line++;
				argc--;
				continue;
			}
		}
		argv[argc++] = line;	/* Beginning of token */

		if (qflag) {
			/* Find terminating delimiter */
			if ((line = stringparse (line)) == NULLCHAR) {
				retval = -1;
				goto prefix;
			}
		} else {
			/* Find space or tab. If not present,
			 * then we've already found the last
			 * token.
			 */
			if ((cp = strchr (line, ' ')) == NULLCHAR
			 && (cp = strchr (line, '\t')) == NULLCHAR) {
				break;
			}
			*cp++= '\0';
			line = cp;
		}
	}
	if (argc < 2) {		/* empty command line */
		if (Curproc->prefix != NULLCHAR) {
			free (Curproc->prefix);
			Curproc->prefix = NULLCHAR;
		}
		retval = 0;
		goto prefix;
	}
	/* Don't count null argument */
	argc--;
	/* Check for help */
	if (argv[1][0] == '?') {
		int level = 0;
		if (argv[1][1] == '?')
			level = 1;
		cmdhelp (cmds, level);
		retval = -1;
		goto prefix;
	}
	/* Look up command in table; prefix matches are OK */
	for (cmdp = cmds;cmdp->name != NULLCHAR;cmdp++) {
		/* Hidden commands begin with capital letter and must match exactly */
		if ((tolower (cmdp->name[0]) != cmdp->name[0]) &&
		    (strlen (argv[1]) < 5) && (strlen (cmdp->name) != strlen (argv[1])))
			continue;
		if (strnicmp (argv[1], cmdp->name, strlen (argv[1])) == 0) {
			argv[1] = cmdp->name;
			found = 1;
			break;
		}
	}
	if (!found) {
		cmdnotfound ();
		retval = -1;
		goto prefix;
	}
	/* Check for insufficient arguments and display help */
	if ((retval = cmderror (cmdp, argc, &argv[1])) == -1)
		goto prefix;

	if (cmdp->stksize == 0) {
		retval = (*cmdp->func) (argc, &argv[1], p);
	} else {
		/* Make private copy of argv and args,
		 * spawn off subprocess and return.
		 */
		pargv = (char **) callocw (argc, sizeof (char *));
		for (i = 0;i < argc;i++)
			pargv[i] = strdup (argv[i + 1]);
		newproc (cmdp->name, cmdp->stksize,
		(void (*) (int, void *, void *)) cmdp->func, argc, pargv, p, 1);
		retval = 0;
	}
prefix:
	if (Curproc->prefix != NULLCHAR) {
		printf ("%s", Curproc->prefix);
		ungetc (' ', stdin);
		for (i = strlen (Curproc->prefix) -1; i >= 0; i--) {
			c = Curproc->prefix[i];
			if (c == '-') c = ' ';
			ungetc (c, stdin);
		}
	}
	return retval;
}

/* ************************************************************************* */

/* Prepare new command line prefix of commands and device/interface names */
ENTRY int
cmdprefix (char *argv[])
{
	int i;
	char *cp;

	if (Curproc->prefix == NULLCHAR) {
		if ((Curproc->prefix = (char *) mallocw (256)) == NULLCHAR)
			return 0;
	}
	/* Find start of command arguments */
	for (i = 0; i > - NARG; i--) {
		if (argv[i] == NULLCHAR) {
			if (i == 0) break;
			cp = Curproc->prefix;
			/* Copy arguments to command prefix buffer */
			for (i++; i <= 0; i++) {
				strcpy (cp, argv[i]);
				cp += strlen (argv[i]);
				*cp++= '-';
			}
			cp--;
			*cp = '\0';
			return 0;
		}
	}
	free (Curproc->prefix);
	Curproc->prefix = NULLCHAR;
	return 0;
}

/* ************************************************************************* */

/* Call a subcommand based on the first token in an already-parsed line */
ENTRY int
subcmd (const struct cmds tab[], int argc, char *argv[], void *p)
{
	register const struct cmds *cmdp;
	char **pargv;
	int found = 0;
	int i;
	int retval;

	/* Strip off first token and pass rest of line to subcommand */
	if (argc < 2) {
		if (argc < 1) {
			printf("SUBCMD - Don't know what to do?\n");
			return -1;
		} else {
			cmdprefix (argv);
			return 0;
		}
	}
	/* Check for help */
	if (argv[1][0] == '?') {
		int level = 0;
		if (argv[1][1] == '?')
			level = 1;
		cmdhelp (tab, level);
		return -1;
	}
	argc--;
	argv++;
	for (cmdp = tab;cmdp->name != NULLCHAR;cmdp++) {
		/* Hidden commands begin with capital letter and must match exactly */
		if ((tolower (cmdp->name[0]) != cmdp->name[0]) &&
		    (strlen (argv[0]) < 5) && (strlen (cmdp->name) != strlen (argv[0])))
			continue;
		if (strnicmp (argv[0], cmdp->name, strlen (argv[0])) == 0) {
			argv[0] = cmdp->name;
			found = 1;
			break;
		}
	}
	if (!found) {
		cmdnotfound ();
		return -1;
	}
	/* Check for insufficient arguments and display help */
	if ((retval = cmderror (cmdp, argc, &argv[0])) == -1)
		return retval;

	if (cmdp->stksize == 0) {
		return (*cmdp->func) (argc, argv, p);
	} else {
		/* Make private copy of argv and args */
		pargv = (char **) callocw (argc, sizeof (char *));
		for (i = 0;i < argc;i++)
			pargv[i] = strdup (argv[i]);
		newproc (cmdp->name, cmdp->stksize,
		 (void (*) (int, void *, void *)) cmdp->func, argc, pargv, p, 1);
		return (0);
	}
}

/* ************************************************************************* */

/* Process subcommands after device/interface name with command prefixes
 */
ENTRY int
ifacecmd (int check, const struct cmds tab[], int argc, char *argv[], void *p)
{
	struct iface *ifp;

	/* Set new command prefix if only one parameter */
	if (argc == 1)
		return cmdprefix (argv);

	/* Lookup the interface name if it exists */
	ifp = if_lookup (argv[1]);

	/* Permit use of show command without device name */
	if ((ifp == NULLIF) && (check & IFACECMD_SHOW) &&
	  (strnicmp (argv[1], "show", strlen (argv[1])) == 0)) {
		argv[1] = "show";
		argv[2] = argv[1];
		argc = 3;
	} else {
		/* Check for help request */
		if ((argc == 2) && (argv[1][0] == '?')) {
			printf ("%s <%s> [args...]\n", argv[0], "device");
			return -1;
		}

		/* Check for other conditions to pop or save command prefixes */
		if (argc == 2) {
				return cmdprefix (&argv[1]);
		}

		/* Check for help request */
		if ((argc > 2) && (argv[2][0] == '?')) {
			int level = 0;
			if (argv[2][1] == '?')
				level = 1;
			cmdhelp (tab, level);
			return -1;
		}

		/* Perform check for valid device/interface name if required
		 */
		if (check & IFACECMD_EXIST) {
			if (ifp == NULLIF) {
				if (!(((check & (IFACECMD_ATTACH | IFACECMD_ADD)) && (argc < 3)) ||
				  ((check & IFACECMD_ATTACH) && (strnicmp (argv[2], "attach", strlen (argv[2])) == 0)) ||
				  ((check & IFACECMD_ADD) && (strnicmp (argv[2], "add", strlen (argv[2])) == 0)))) {
					printf ("%s \"%s\" unknown\n","Device", argv[1]);
					return 1;
				}
			}
			else {

					if ((check & IFACECMD_MDM) && (ifp->d_type != IFD_MDM)) {
						printf("\"%s\" does not support mdm communications\n", argv[1]);
						return 1;
					}

				if ((check & IFACECMD_PPP) && (ifp->pppedv == NULL))
					ppp_attach (ifp);

			}
		}
	}

	/* Process subcommands on the interface
	 */
	argc--;
	return subcmd (tab, argc, &argv[1], ifp);
}

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

/* Subroutine for setting and displaying boolean flags */
ENTRY int
chg_bool (int *var, char *label, int argc, char *argv[])
{
	const struct boolcmd *bc;

	if (argc < 2) {
		printf("%s: %s\n",label,*var ? "on":"off");
		return 0;
	}
	for (bc = Boolcmds;bc->str != NULLCHAR;bc++) {
		if (stricmp (argv[1], bc->str) == 0) {
			*var = bc->val;
			return 0;
		}
	}
	printf("Valid options:");
	for (bc = Boolcmds;bc->str != NULLCHAR;bc++)
		if (printf(" %s",bc->str) == EOF)
			return 1;
	printf("\n");
	return 1;
}

/* ************************************************************************* */

/* Subroutine for setting and displaying bit values */
ENTRY int
chg_bit16 (uint16 *bits, uint16 mask, char *label, int argc, char *argv[])
{
	int doing = (*bits & mask);
	int result = chg_bool (&doing, label, argc, argv);

	if (!result) {
		if (doing)
			*bits |= mask;
		else
			*bits &= ~mask;
	}
	return result;
}

/* ************************************************************************* */

/* Subroutine for setting and displaying long variables */
ENTRY int
chg_int32s (sint31 *var, char *label, int argc, char *argv[])
{
	if (argc < 2)
		printf("%s: %ld\n",label,*var);
	else
		return (atoi32s_err (argv[1], var));

	return 0;
}

/* ************************************************************************* */

/* Subroutine for setting and displaying short variables */
ENTRY int
chg_int16u (uint16 *var, char *label, int argc, char *argv[])
{
	if (argc < 2)
		printf("%s: %u\n",label,*var);
	else
		return (atoi16u_err (argv[1], var));

	return 0;
}

/* ************************************************************************* */

/* Subroutine for setting and displaying integer variables */
ENTRY int
chg_int16s (sint15 *var, char *label, int argc, char *argv[])
{
	if (argc < 2)
		printf("%s: %i\n",label,*var);
	else
		return (atoi16s_err (argv[1], var));

	return 0;
}

/* ************************************************************************* */

/* Subroutine for setting and displaying integer variables with maximum limit
*/
ENTRY int
chg_int16u_max (uint16 *var, char *label, int argc, char *argv[], uint16 max)
{
	uint16 local;

	if (argc < 2)
		printf("%s: %u\n",label,*var);
	else {
		if (atoi16u_err (argv[1], &local))
			return 1;
		if (local > max) {
			printf ("Number exceeds limit of %u: %u\n", max, local);
			return 1;
		}
		*var = local;
	}
	return 0;
}

/* ************************************************************************* */

/* Subroutine for setting and displaying byte variables
*/
ENTRY int
chg_int8u (uint8 *var, char *label, int argc, char *argv[])
{
	uint16 local;

	if (argc < 2)
		printf("%s: %u\n",label,*var);
	else {
		if (atoi16u_err (argv[1], &local))
			return 1;
		if (local > 255) {
			printf ("Number out of range: %u\n", local);
			return 1;
		}
		*var = (uint8) local;
	}
	return 0;
}

/* ************************************************************************* */

/* Subroutine for setting and displaying addresses
 */
ENTRY int
chg_addr (struct sockaddr *addr, uint16 family, char *label, int argc, char *argv[])
{
	if (argc < 2)
		printf ("%s: %s\n", label, snhtoa(addr));
	else
		return (atos_err (argv[1], family, addr));

	return 0;
}

/* ************************************************************************* */

/* Subroutine for setting and displaying masks
 */
ENTRY int
chg_mask (uint32 *mask, char *label, int argc, char *argv[])
{
	if (argc < 2)
		printf ("%s: 0x%08lx\n", label, *mask);
	else
		return (atom_err (argv[1], mask));

	return 0;
}

/* ************************************************************************* */

/* Subroutine for setting and displaying timers
 */
ENTRY int
chg_timer (struct timer *t, char *label, int argc, char *argv[])
{

	if (argc < 2) {
		printf ("%s: %d\n", label, (int)(dur_timer(t)/1000L));
	} else {
		uint16 x;

		if (atoi16u_err (argv[1], &x))
			return 1;

		set_timer (t, ((uint32) x) * 1000L);
	}
	return 0;
}
