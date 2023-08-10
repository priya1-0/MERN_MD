
/* ************************************************************************* */
/*
 *	domain.c
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
 *	Module:		IP
 *
 *	This file contains the functions.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 19:52:55  zhangn1
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

#include "lansend/lansend.h"

#include "ip/local.h"

#undef	DEBUG				/* for certain trace messages */
#undef	DEBUG_PAIN			/* for painful debugging */

static struct rr *Dcache = NULLRR;	/* Cache of resource records */
static int Dcache_size = 20;		/* size limit */
static time_t Dcache_time = 0L; 	/* timestamp */

static int Dfile_clean = FALSE; 	/* discard expired records (flag) */
static int Dfile_reading = 0;		/* read interlock (count) */
static int Dfile_writing = 0;		/* write interlock (count) */

struct proc *Dfile_updater = NULLPROC;
static sint31 Dfile_wait_absolute = 0L;	/* timeout Clock time */
static sint15 Dfile_wait_relative = 300;	/* timeout file activity (seconds) */

struct dserver *Dservers = NULLDOM;		/* List of potential servers */
static sint15 Dserver_retries = 2;		/* Attempts to reach servers */

static char *Dsuffix = NULLCHAR;	/* Default suffix for names without periods */
static int Dtrace = FALSE;
static char *Dtypes[] = {
	"",
	"A",
	"NS",
	"MD",
	"MF",
	"CNAME",
	"SOA",
	"MB",
	"MG",
	"MR",
	"NULL",
	"WKS",
	"PTR",
	"HINFO",
	"MINFO",
	"MX",
	"TXT"
};
static int Ndtypes = 17;
static char delim[] = " \t\r\n";

/**
 **	Domain Resolver Commands
 **/

static const struct cmds Dcmds[] = {
	{"add",			dodnsadd,		0, 2, "<server>"},
	{"cache",		docache,		0, 0, ""},
	{"drop",		dodnsdrop,		0, 2, "<server>"},
	{"query",		dodnsquery,		512, 2, "<server>"},
	{"retry",		dodnsretry,		0, 0, "[count]"},
	{"show",		dodnslist,		0, 0, ""},
	{"suffix",		dosuffix,		0, 0, "[string]"},
	{"trace",		dodnstrace,		0, 0, "[on|off]"},
	{NULLCHAR},
};

static const struct cmds Dcachecmds[] = {
	{"flush",		docacheclean,	0, 0, "[on|off]"},
	{"show",		docachelist, 512, 0, ""},
	{"size",		docachesize,	0, 0, "[count]"},
	{"wait",		docachewait,	0, 0, "[secs]"},
	{NULLCHAR},
};

ENTRY void
domain_init (void)
{
	Dcache = NULLRR;	/* Cache of resource records */
	Dcache_size = 20;		/* size limit */
	Dcache_time = 0L; 	/* timestamp */

	Dfile_clean = FALSE; 	/* discard expired records (flag) */
	Dfile_reading = 0;		/* read interlock (count) */
	Dfile_writing = 0;		/* write interlock (count) */

	Dfile_updater = NULLPROC;
	Dfile_wait_absolute = 0L;	/* timeout Clock time */
	Dfile_wait_relative = 300;	/* timeout file activity (seconds) */

	Dservers = NULLDOM; /* List of potential servers */
	Dserver_retries = 5;		/* Attempts to reach servers */

	Dsuffix = NULLCHAR;	/* Default suffix for names without periods */
	Dtrace = FALSE;
	Ndtypes = 17;
}

ENTRY int
dodomain (int argc, char *argv[], void *p)
{
	return subcmd (Dcmds, argc, argv, p);
}

LOCAL int
docache (int argc, char *argv[], void *p)
{
	return subcmd (Dcachecmds, argc, argv, p);
}

LOCAL int
dosuffix (int argc, char *argv[], void *p)
{
	if (argc < 2) {
		if (Dsuffix != NULLCHAR)
			printf("%s\n",Dsuffix);
		return 0;
	}
	free (Dsuffix);
	Dsuffix = strdup (argv[1]);
	return 0;
}

LOCAL int
docacheclean (int argc, char *argv[], void *p)
{
	return chg_bool (&Dfile_clean, "discard expired records", argc, argv);
}

LOCAL int
docachelist (int argc, char *argv[], void *p)
{
	struct rr *rrp;
	struct session *sp;
	int rows = MOREROWS;

	if ((sp = newsession ("domain", DCLIST, 1)) == NULLSESSION) {
		return -1;
	}

	(void)dcache_search(NULLRR); /* update ttl */

	for (rrp = Dcache;rrp != NULLRR;rrp = rrp->next)
	{
		put_rr (stdout, rrp);
		rows--;
		if (rows == 0) {
			if ((rows = morewait (NULLCHAR)) < 1) {
				break;
			}
		}
	}
	fflush (stdout);

	/* Put tty into raw mode so single-char responses will work */
	sp->ttystate.echo = sp->ttystate.edit = 0;
	keywait (NULLCHAR, 1);

	freesession (sp);
	return 0;
}

LOCAL int
docachesize (int argc, char *argv[], void *p)
{
	sint15 newsize;
	int oldsize;
	int result;

	newsize = oldsize = Dcache_size;
	result = chg_int16s (&newsize, "memory cache size", argc,argv);

	if (newsize > 0) {
		Dcache_size = newsize;
		if (newsize < oldsize) {
			(void)dcache_search(NULLRR); /* update size */
		}
	}
	return result;
}

LOCAL int
docachewait (int argc, char *argv[], void *p)
{
	return chg_int16s (&Dfile_wait_relative, "time before file update (seconds)", argc,argv);
}

LOCAL void
dlist_add (register struct dserver *dp)
{
	struct dserver *dptr;

	dp->prev = NULLDOM;
	dp->next = NULLDOM;

	if (Dservers != NULLDOM) {
		dptr = Dservers;
		while (dptr->next != NULLDOM) {
			dptr = dptr->next;
		}
		dptr->next = dp;
		dp->prev = dptr;
	} else {
		Dservers = dp;
	}
}

LOCAL void
dlist_drop (register struct dserver *dp)
{
	if (dp->prev != NULLDOM)
		dp->prev->next = dp->next;
	else
		Dservers = dp->next;
	if (dp->next != NULLDOM)
		dp->next->prev = dp->prev;
}

LOCAL int
dodnsadd (int argc, char *argv[], void *p)
{
	sint31 address;

	if ((address = resolve (argv[1])) == 0L) {
		printf("Resolver %s unknown\n",argv[1]);
		return 1;
	}
	return add_nameserver (address);
}

ENTRY int
add_nameserver (sint31 address)
{
	struct dserver *dp;

	dp = (struct dserver *) callocw (1, sizeof (struct dserver));
	dp->address = address;
	dp->srtt = 5000L; /* 5 sec */
	dp->mdev = 0;
	dp->timeout = 2 * dp->mdev + dp->srtt + 3;
	dlist_add (dp);
	return 0;
}

LOCAL int
dodnsdrop (int argc, char *argv[], void *p)
{
	sint31 addr;

	addr = resolve (argv[1]);
	if (drop_nameserver (addr)) {
		printf("Not found\n");
		return 1;
	}
	return 0;
}

ENTRY int
drop_nameserver (sint31 address)
{
	struct dserver *dp;

	for (dp = Dservers; dp != NULLDOM; dp = dp->next)
		if (address == dp->address)
			break;

	if (dp == NULLDOM) {
		return 1;
	}

	dlist_drop (dp);
	free ((char *) dp);
	return 0;
}

LOCAL int
dodnslist (int argc, char *argv[], void *p)
{
	register struct dserver *dp;

	printf("Server address          srtt    mdev   timeout   queries responses\n");
	for (dp = Dservers;dp != NULLDOM;dp = dp->next) {
		printf("%-20s%8lu%8lu%10lu%10lu%10lu\n",
		 inet_ntoa (dp->address),
		 dp->srtt, dp->mdev, dp->timeout,
		 dp->queries, dp->responses);
	}
	return 0;
}

ENTRY sint31
get_nameserver (int entry)
{
	struct dserver *dp;

	for (dp = Dservers;dp != NULLDOM;dp = dp->next)
		if (entry--== 0)
			break;

	if (dp == NULLDOM) {
		return 0L;
	}

	return dp->address;
}

LOCAL int
dodnsquery (int argc, char *argv[], void *p)
{
	struct rr *rrp;
	struct rr *result_rrlp;
	char *sname;
	struct session *sp;
	int rows = MOREROWS;

	if ((sp = newsession (argv[1], DQUERY, 1)) == NULLSESSION) {
		return -1;
	}

	if (isaddr (argv[1])) {
		result_rrlp = inverse_a (atonl (argv[1]));
	} else {
		sname = checksuffix (argv[1]);
		rrp = make_rr (RR_QUERY, sname, CLASS_IN, TYPE_ANY, 0, 0, NULL);
		free (sname);

		dns_query (rrp);
		result_rrlp = dcache_search (rrp);
		free_rr (rrp);
	}

	for (rrp = result_rrlp; rrp != NULLRR; rrp = rrp->next)
	{
		put_rr (stdout, rrp);
		rows--;
		if (rows == 0) {
			if ((rows = morewait (NULLCHAR)) < 1) {
				break;
			}
		}
	}
	fflush (stdout);
	free_rr (result_rrlp);

	/* Put tty into raw mode so single-char responses will work */
	sp->ttystate.echo = sp->ttystate.edit = 0;
	keywait (NULLCHAR, 1);

	freesession (sp);
	return 0;
}

LOCAL int
dodnsretry (int argc, char *argv[], void *p)
{
	return chg_int16s (&Dserver_retries, "server retries", argc,argv);
}

LOCAL int
dodnstrace (int argc, char *argv[], void *p)
{
	return chg_bool (&Dtrace, "server trace", argc, argv);
}

/**
 **	Domain Resource Record Utilities
 **/

LOCAL char *
dtype (int value)
{
	static char buf[10];

	if (value < Ndtypes)
		return Dtypes[value];

	sprintf(buf, "{%d}", value);
	return buf;
}

/* check list of resource records for any expired ones.
 * returns number of expired records.
 */
LOCAL int
check_ttl (register struct rr *rrlp)
{
	int count = 0;

	while (rrlp != NULLRR) {
		if (rrlp->ttl == 0L)
			count++;
		rrlp = rrlp->next;
	}
	return count;
}

/* Compare two resource records.
 * returns 0 if match, nonzero otherwise.
 */
LOCAL int
compare_rr (register struct rr *search_rrp, register struct rr *target_rrp)
{
	int i;

	if (search_rrp == NULLRR || target_rrp == NULLRR)
		return - 32765;

	if (search_rrp->af_class != target_rrp->af_class)
		return - 32763;

	if (search_rrp->type != TYPE_ANY
	&& search_rrp->type != target_rrp->type
	&& (search_rrp->source != RR_QUERY
	 || (target_rrp->type != TYPE_CNAME
	  && target_rrp->type != TYPE_PTR)))
		return - 32761;

	if (search_rrp->source != RR_INQUERY) {
		if ((i = strlen (search_rrp->name)) != strlen (target_rrp->name))
			return - 32759;
		if ((i = strnicmp (search_rrp->name, target_rrp->name, i)) != 0)
			return i;

		/* match negative records so that they are replaced */
		if (target_rrp->rdlength == 0)
			return 0;
	}

	/* if a query has gotten this far, match it */
	if (search_rrp->source == RR_QUERY)
		return 0;

	/* ensure negative records don't replace older records */
	if (search_rrp->rdlength == 0)
		return - 32757;

	/* match expired records so that they are replaced */
	if (search_rrp->source != RR_INQUERY) {
		if (target_rrp->ttl == 0L)
			return 0;
	}

	/* Note: rdlengths are not compared because they vary depending
	 * on the representation (ASCII or encoded) this record was
	 * generated from.
	 */

	switch (search_rrp->type) {
	case TYPE_A:
		i = search_rrp->rdata.addr != target_rrp->rdata.addr;
		break;
	case TYPE_CNAME:
	case TYPE_MB:
	case TYPE_MG:
	case TYPE_MR:
	case TYPE_NS:
	case TYPE_PTR:
	case TYPE_TXT:
		i = stricmp (search_rrp->rdata.data, target_rrp->rdata.data);
		break;
	case TYPE_HINFO:
		i = strcmp (search_rrp->rdata.hinfo.cpu, target_rrp->rdata.hinfo.cpu) ||
			strcmp (search_rrp->rdata.hinfo.os, target_rrp->rdata.hinfo.os);
		break;
	case TYPE_MX:
		i = stricmp (search_rrp->rdata.mx.exch, target_rrp->rdata.mx.exch);
		break;
	case TYPE_SOA:
		i = search_rrp->rdata.soa.serial != target_rrp->rdata.soa.serial;
		break;
	default:
		i = -32755;	/* unsupported */
	}
	return i;
}

LOCAL int
compare_rr_list (register struct rr *rrlp, register struct rr *target_rrp)
{
	while (rrlp != NULLRR) {
		if (compare_rr (rrlp, target_rrp) == 0)
			return 0;
#ifdef DO_LANSEND_DEBUG_PAIN
		if (Dtrace)
			printf("%15d %s\n",
				compare_rr (rrlp, target_rrp),
				target_rrp->name);
#endif /* DO_LANSEND_DEBUG_PAIN */
		rrlp = rrlp->next;
	}
	return - 32767;
}

/* Make a new copy of a resource record */
LOCAL struct rr *
copy_rr (register struct rr *rrp)
{
	register struct rr *newrr;

	if (rrp == NULLRR)
		return NULLRR;

	newrr = (struct rr *) callocw (1, sizeof (struct rr));
	newrr->source =	rrp->source;
	newrr->name = strdup (rrp->name);
	newrr->type = rrp->type;
	newrr->af_class = rrp->af_class;
	newrr->ttl = rrp->ttl;
	if ((newrr->rdlength = rrp->rdlength) == 0)
		return newrr;

	switch (rrp->type) {
	case TYPE_A:
		newrr->rdata.addr = rrp->rdata.addr;
		break;
	case TYPE_CNAME:
	case TYPE_MB:
	case TYPE_MG:
	case TYPE_MR:
	case TYPE_NS:
	case TYPE_PTR:
	case TYPE_TXT:
		newrr->rdata.name = strdup (rrp->rdata.name);
		break;
	case TYPE_HINFO:
		newrr->rdata.hinfo.cpu = strdup (rrp->rdata.hinfo.cpu);
		newrr->rdata.hinfo.os = strdup (rrp->rdata.hinfo.os);
		break;
	case TYPE_MX:
		newrr->rdata.mx.pref = rrp->rdata.mx.pref;
		newrr->rdata.mx.exch = strdup (rrp->rdata.mx.exch);
		break;
	case TYPE_SOA:
		newrr->rdata.soa.mname = 	strdup (rrp->rdata.soa.mname);
		newrr->rdata.soa.rname = 	strdup (rrp->rdata.soa.rname);
		newrr->rdata.soa.serial = 	rrp->rdata.soa.serial;
		newrr->rdata.soa.refresh = 	rrp->rdata.soa.refresh;
		newrr->rdata.soa.retry = 	rrp->rdata.soa.retry;
		newrr->rdata.soa.expire = 	rrp->rdata.soa.expire;
		newrr->rdata.soa.minimum = 	rrp->rdata.soa.minimum;
		break;
	}
	return newrr;
}

LOCAL struct rr *
copy_rr_list (register struct rr *rrlp)
{
	register struct rr **rrpp;
	struct rr *result_rrlp;

	rrpp = &result_rrlp;
	while (rrlp != NULLRR) {
		*rrpp = copy_rr (rrlp);
		rrpp = &(*rrpp)->next;
		rrlp = rrlp->next;
	}
	*rrpp = NULLRR;
	return result_rrlp;
}

/* Free (list of) resource records */
ENTRY void
free_rr (register struct rr *rrlp)
{
	register struct rr *rrp;

	while ((rrp = rrlp) != NULLRR) {
		rrlp = rrlp->next;

		free (rrp->comment);
		free (rrp->name);
		if (rrp->rdlength > 0) {
			switch (rrp->type) {
			case TYPE_A:
				break;	/* Nothing allocated in rdata section */
			case TYPE_CNAME:
			case TYPE_MB:
			case TYPE_MG:
			case TYPE_MR:
			case TYPE_NS:
			case TYPE_PTR:
			case TYPE_TXT:
				free (rrp->rdata.name);
				break;
			case TYPE_HINFO:
				free (rrp->rdata.hinfo.cpu);
				free (rrp->rdata.hinfo.os);
				break;
			case TYPE_MX:
				free (rrp->rdata.mx.exch);
				break;
			case TYPE_SOA:
				free (rrp->rdata.soa.mname);
				free (rrp->rdata.soa.rname);
				break;
			}
		}
		free ((char *) rrp);
	}
}

LOCAL struct rr *
make_rr (int source, char *dname, uint16 dclass, uint16 dtype, sint31 ttl, uint16 rdl, void *data)
{
	register struct rr *newrr;

	newrr = (struct rr *) callocw (1, sizeof (struct rr));
	newrr->source = source;
	newrr->name = strdup (dname);
	newrr->af_class = dclass;
	newrr->type = dtype;
	newrr->ttl = ttl;
	if ((newrr->rdlength = rdl) == 0)
		return newrr;

	switch (dtype) {
	case TYPE_A:
	  {
		register sint31 *ap = (sint31 *) data;
		newrr->rdata.addr = *ap;
		break;
	  }
	case TYPE_CNAME:
	case TYPE_MB:
	case TYPE_MG:
	case TYPE_MR:
	case TYPE_NS:
	case TYPE_PTR:
	case TYPE_TXT:
	  {
		newrr->rdata.name = strdup ((char *) data);
		break;
	  }
	case TYPE_HINFO:
	  {
		register struct hinfo *hinfop = (struct hinfo *) data;
		newrr->rdata.hinfo.cpu = strdup (hinfop->cpu);
		newrr->rdata.hinfo.os = strdup (hinfop->os);
		break;
	  }
	case TYPE_MX:
	  {
		register struct mx *mxp = (struct mx *) data;
		newrr->rdata.mx.pref = mxp->pref;
		newrr->rdata.mx.exch = strdup (mxp->exch);
		break;
	  }
	case TYPE_SOA:
	  {
		register struct soa *soap = (struct soa *) data;
		newrr->rdata.soa.mname = 	strdup (soap->mname);
		newrr->rdata.soa.rname = 	strdup (soap->rname);
		newrr->rdata.soa.serial = 	soap->serial;
		newrr->rdata.soa.refresh = 	soap->refresh;
		newrr->rdata.soa.retry = 	soap->retry;
		newrr->rdata.soa.expire = 	soap->expire;
		newrr->rdata.soa.minimum = 	soap->minimum;
		break;
	  }
	}
	return newrr;
}

/**
 **	Domain Cache Utilities
 **/

LOCAL void
dcache_add (register struct rr *rrlp)
{
	register struct rr *last_rrp;
	struct rr *save_rrp;

	if (rrlp == NULLRR)
		return;

	save_rrp = rrlp;
	last_rrp = NULLRR;
	while (rrlp != NULLRR) {
		rrlp->last = last_rrp;
		last_rrp = rrlp;
		rrlp = rrlp->next;
	}
	last_rrp->next = Dcache;
	if (Dcache != NULLRR)
		Dcache->last = last_rrp;
	Dcache = save_rrp;
}

LOCAL void
dcache_drop (register struct rr *rrp)
{
	if (rrp->last != NULLRR)
		rrp->last->next = rrp->next;
	else
		Dcache = rrp->next;
	if (rrp->next != NULLRR)
		rrp->next->last = rrp->last;
	rrp->last =
	rrp->next = NULLRR;
}

/* Search cache for resource records, removing them from the cache.
 * Also, timeout cache entries, and trim cache to size.
 *(Calling with NULLRR is legal-- will timeout & trim only.)
 * Note that an answer from the cache cannot be authoritative, because
 * we cannot guarantee that all the entries remain from a previous request.
 * Returns RR list, or NULLRR if no record found.
 */
LOCAL struct rr *
dcache_search (struct rr *rrlp)
{
	register struct rr *rrp, *test_rrp;
	struct rr **rrpp, *result_rrlp;
	sint31 elapsed;
	time_t now;
	int count = 0;

#ifdef DO_LANSEND_DEBUG
	if (Dtrace && rrlp != NULLRR) {
		printf("dcache_search: searching for %s\n",rrlp->name);
	}
#endif /* DO_LANSEND_DEBUG */

	elapsed = (sint31) (time (&now) - Dcache_time);
	Dcache_time = now;

	rrpp = &result_rrlp;
	for (rrp = Dcache; (test_rrp = rrp) != NULLRR;) {
		rrp = rrp->next;
					/* timeout entries */
		if (test_rrp->ttl > 0L
		&& (test_rrp->ttl -= elapsed) <= 0L)
			test_rrp->ttl = 0L;

		if (compare_rr_list (rrlp, test_rrp) == 0) {
			dcache_drop (*rrpp = test_rrp);
			rrpp = &(*rrpp)->next;
		} else if (test_rrp->source == RR_FILE &&++ count > Dcache_size) {
			dcache_drop (test_rrp);
			free_rr (test_rrp);
		}
	}
	*rrpp = NULLRR;
	return result_rrlp;
}

/* Move a list of resource records to the cache, removing duplicates. */
LOCAL void
dcache_update (register struct rr *rrlp)
{
	if (rrlp == NULLRR)
		return;

	free_rr(dcache_search(rrlp));	/* remove duplicates, first */
	dcache_add (rrlp);
}

/**
 **	File Utilities
 **/
LOCAL struct rr *
get_rr (FILE *fp, struct rr *lastrrp)
{
	char *line, *lp;
	char *strtok (char *, const char *);
	struct rr *rrp;
	char *name, *ttl, *get_class, *type, *data;
	int i;

	line = (char *) mallocw (256);
	if (fgets (line, 256, fp) == NULL) {
		free (line);
		return NULLRR;
	}

	rrp = (struct rr *) callocw (1, sizeof (struct rr));
	rrp->source = RR_FILE;

	if (line[0] == '\0' || line[0] == '#' || line[0] == ';') {
		rrp->comment = line;
		return rrp;
	}

	if (!isspace (line[0]) || lastrrp == NULLRR) {
		name = strtok (line, delim);
		lp = NULLCHAR;
	} else {	/* Name field is missing */
		name = lastrrp->name;
		lp = line;
	}
	if (name == NULLCHAR || (i = strlen (name)) == 0) {
		rrp->comment = strdup("\n");
		free (line);
		return rrp;
	}

	if (name[i -1] != '.') {
		/* Tack on a trailing period if it's not there */
		/* !!! need to implement $ORIGIN suffix here */
		rrp->name = (char *) mallocw (i + 2);
		strcpy (rrp->name, name);
		strcat(rrp->name,".");
	} else
		rrp->name = strdup (name);

	ttl = strtok (lp, delim);

	if (ttl == NULLCHAR || (!isdigit (ttl[0]) && ttl[0] != '-')) {
		/* Optional ttl field is missing */
		rrp->ttl = TTL_MISSING;
		get_class = ttl;
	} else {
		rrp->ttl = atol (ttl);
		get_class = strtok (NULLCHAR, delim);
	}

	if (get_class == NULLCHAR) {
		/* we're in trouble, but keep processing */
		rrp->af_class = CLASS_MISSING;
		type = get_class;
	} else if (get_class[0] == '<') {
		rrp->af_class = atoi (&get_class[1]);
		type = strtok (NULLCHAR, delim);
	} else if (stricmp (get_class,"IN") == 0) {
		rrp->af_class = CLASS_IN;
		type = strtok (NULLCHAR, delim);
	} else {
		/* Optional class field is missing; assume IN */
		rrp->af_class = CLASS_IN;
		type = get_class;
	}

	if (type == NULLCHAR) {
		/* we're in trouble, but keep processing */
		rrp->type = TYPE_MISSING;
		data = type;
	} else if (type[0] == '{') {
		rrp->type = atoi (&get_class[1]);
		data = strtok (NULLCHAR, delim);
	} else {
		rrp->type = TYPE_MISSING;
		for (i = 1;i < Ndtypes;i++) {
			if (stricmp (type, Dtypes[i]) == 0) {
				rrp->type = i;
				data = strtok (NULLCHAR, delim);
				break;
			}
		}
	}

	if (rrp->type == TYPE_MISSING) {
		data = NULLCHAR;
	}

	if (data == NULLCHAR) {
		/* Empty record, just return */
		free (line);
		return rrp;
	}
	switch (rrp->type) {
	case TYPE_A:
		rrp->rdlength = 4;
		rrp->rdata.addr = atonl (data);
		break;
	case TYPE_CNAME:
	case TYPE_MB:
	case TYPE_MG:
	case TYPE_MR:
	case TYPE_NS:
	case TYPE_PTR:
	case TYPE_TXT:
		rrp->rdlength = strlen (data);
		rrp->rdata.name = strdup (data);
		break;
	case TYPE_HINFO:
		rrp->rdlength = strlen (data);
		rrp->rdata.hinfo.cpu = strdup (data);
		if ((data = strtok (NULLCHAR, delim)) != NULLCHAR) {
			rrp->rdlength += strlen (data);
			rrp->rdata.hinfo.os = strdup (data);
		}
		break;
	case TYPE_MX:
		rrp->rdata.mx.pref = atoi (data);
		rrp->rdlength = 2;

		/* Get domain name of exchanger */
		if ((data = strtok (NULLCHAR, delim)) != NULLCHAR) {
			rrp->rdlength += strlen (data);
			rrp->rdata.mx.exch = strdup (data);
		}
		break;
	case TYPE_SOA:
		/* Get domain name of master name server */
		rrp->rdlength = strlen (data);
		rrp->rdata.soa.mname = strdup (data);

		/* Get domain name of irresponsible person */
		if ((data = strtok (NULLCHAR, delim)) != NULLCHAR) {
			rrp->rdata.soa.rname = strdup (data);
			rrp->rdlength += strlen (data);
		}
		data = strtok (NULLCHAR, delim);
		rrp->rdata.soa.serial = atol (data);
		data = strtok (NULLCHAR, delim);
		rrp->rdata.soa.refresh = atol (data);
		data = strtok (NULLCHAR, delim);
		rrp->rdata.soa.retry = atol (data);
		data = strtok (NULLCHAR, delim);
		rrp->rdata.soa.expire = atol (data);
		data = strtok (NULLCHAR, delim);
		rrp->rdata.soa.minimum = atol (data);
		rrp->rdlength += 20;
		break;
	}

	/* !!! need to handle trailing comments */
	free (line);
	return rrp;
}

/* Print a resource record */
LOCAL void
put_rr (FILE *fp, struct rr *rrp)
{
	char * stuff;

	if (fp == NULLFILE || rrp == NULLRR)
		return;

	if (rrp->name == NULLCHAR && rrp->comment != NULLCHAR) {
		fprintf(fp,"%s",rrp->comment);
		return;
	}

	fprintf(fp,"%s",rrp->name);
	if (rrp->ttl != TTL_MISSING)
		fprintf(fp, "\t%ld", (long) rrp->ttl);
	if (rrp->af_class == CLASS_IN)
		fprintf(fp, "\tIN");
	else
		fprintf(fp, "\t<%u>", rrp->af_class);

	stuff = dtype (rrp->type);
	fprintf(fp,"\t%s",stuff);
	if (rrp->rdlength == 0) {
		/* Null data portion, indicates nonexistent record */
		/* or unsupported type.  Hopefully, these will filter */
		/* as time goes by. */
		fprintf(fp,"\n");
		return;
	}
	switch (rrp->type) {
	case TYPE_A:
		fprintf(fp,"\t%s\n",inet_ntoa(rrp->rdata.addr));
		break;
	case TYPE_CNAME:
	case TYPE_MB:
	case TYPE_MG:
	case TYPE_MR:
	case TYPE_NS:
	case TYPE_PTR:
	case TYPE_TXT:
		/* These are all printable text strings */
		fprintf(fp,"\t%s\n",rrp->rdata.data);
		break;
	case TYPE_HINFO:
		fprintf(fp,"\t%s\t%s\n",
		 rrp->rdata.hinfo.cpu,
		 rrp->rdata.hinfo.os);
		break;
	case TYPE_MX:
		fprintf(fp,"\t%u\t%s\n",
		 rrp->rdata.mx.pref,
		 rrp->rdata.mx.exch);
		break;
	case TYPE_SOA:
		fprintf(fp,"\t%s\t%s\t%lu\t%lu\t%lu\t%lu\t%lu\n",
		 rrp->rdata.soa.mname, rrp->rdata.soa.rname,
		 (long) rrp->rdata.soa.serial, (long) rrp->rdata.soa.refresh,
		 (long) rrp->rdata.soa.retry, (long) rrp->rdata.soa.expire,
		 (long) rrp->rdata.soa.minimum);
		break;
	default:
		fprintf(fp,"\n");
		break;
	}
}

/* Search local database for resource records.
 * Returns RR list, or NULLRR if no record found.
 */
LOCAL struct rr *
dfile_search (struct rr *rrlp)
{
	register struct rr *frrp;
	struct rr **rrpp, *result_rrlp, *oldrrp;
	sint31 elapsed;
	FILE *dbase;
	struct stat dstat;

#ifdef DO_LANSEND_DEBUG
	if (Dtrace) {
		printf("dfile_search: searching for %s\n",rrlp->name);
	}
#endif /* DO_LANSEND_DEBUG */

	while (Dfile_writing > 0)
		pwait (&Dfile_reading);
	Dfile_reading++;

	if ((dbase = fopen (Dfile, READ_TEXT)) == NULLFILE) {
		Dfile_reading--;
		return NULLRR;
	}
	if (fstat (fileno (dbase), &dstat) != 0) {
		printf("dfile_search: can't get file status\n");
		fclose (dbase);
		Dfile_reading--;
		return NULLRR;
	}
	if ((elapsed = (sint31) (Dcache_time - (time_t) dstat.st_ctime)) < 0L)
		elapsed = -elapsed;	/* arbitrary time mismatch */

	result_rrlp = NULLRR;		/* for contiguous test below */
	oldrrp = NULLRR;
	rrpp = &result_rrlp;
	while ((frrp = get_rr (dbase, oldrrp)) != NULLRR) {
		free_rr (oldrrp);
		if (frrp->type != TYPE_MISSING
		&& frrp->rdlength > 0
		&& compare_rr_list (rrlp, frrp) == 0) {
			if (frrp->ttl > 0L
			&& (frrp->ttl -= elapsed) <= 0L)
				frrp->ttl = 0L;
			*rrpp = frrp;
			rrpp = &(*rrpp)->next;
			oldrrp = copy_rr (frrp);
		} else {
			oldrrp = frrp;
			/*
				All records of the same name and the same type
				are contiguous.  Therefore, for a single query,
				we can stop searching.  Multiple queries must
				read the whole file.
			*/
			if (rrlp->type != TYPE_ANY
			&& rrlp->next == NULLRR
			&& result_rrlp != NULLRR)
				break;
		}
		if (!main_exit)
			pwait(NULL);	/* run multiple sessions */
	}
	free_rr (oldrrp);
	*rrpp = NULLRR;

	fclose (dbase);

	if (--Dfile_reading <= 0) {
		Dfile_reading = 0;
		psignal (&Dfile_writing, 0);
	}

	return result_rrlp;
}

/* Process which will add new resource records from the cache
 * to the local file, eliminating duplicates while it goes.
 */
LOCAL void
dfile_update (int s, void *unused, void *p)
{
	struct rr **rrpp, *rrlp, *oldrrp;
	char *newname;
	FILE *old_fp, *new_fp;
	struct stat old_stat, new_stat;

	net_log(-1,"update Domain.txt initiated");

	/* Produce output on command session rather than the one
	 * that invoked us
	 */
	fclose (stdin);
	stdin = fdup (Cmdpp->input);
	fclose (stdout);
	stdout = fdup (Cmdpp->output);

	newname = strdup (Dfile);
	strcpy(&newname[strlen(newname)-3],"tmp");

	while (Dfile_wait_absolute != 0L && ! main_exit) {
		register struct rr *frrp;
		sint31 elapsed;

		while (Dfile_wait_absolute != 0L) {
			elapsed = Dfile_wait_absolute - secclock ();
			Dfile_wait_absolute = 0L;
			if (elapsed > 0L && ! main_exit) {
				alarm (elapsed*1000L);
				pwait (&Dfile_wait_absolute);
				alarm (0L);
			}
		}

		net_log(-1,"update Domain.txt");

		/* create new file for copy */
		if ((new_fp = fopen (newname, WRITE_TEXT)) == NULLFILE) {
			printf("dfile_update: can't create %s!\n",newname);
			break;
		}
		if (fstat (fileno (new_fp), &new_stat) != 0) {
			printf("dfile_update: can't get new_file status!\n");
			fclose (new_fp);
			break;
		}

		pwait(NULL);	/* file operations can be slow */

		/* timeout the cache one last time before writing */
		(void) dcache_search (NULLRR);

		/* copy new RRs out to the new file */
		/* (can't wait here, the cache might change) */
		rrpp = &rrlp;
		for (frrp = Dcache; frrp != NULLRR; frrp = frrp->next) {
			switch (frrp->source) {
			case RR_QUESTION:
			case RR_ANSWER:
			case RR_AUTHORITY:
			case RR_ADDITIONAL:
				*rrpp = copy_rr (frrp);
				if (frrp->type != TYPE_MISSING
				&& frrp->rdlength > 0)
					put_rr (new_fp, frrp);
				rrpp = &(*rrpp)->next;
				frrp->source = RR_FILE;
				break;
			}
		}
		*rrpp = NULLRR;

		/* open up the old file, concurrently with everyone else */
		if ((old_fp = fopen (Dfile, READ_TEXT)) == NULLFILE) {
			/* great! no old file, so we're ready to go. */
			fclose (new_fp);
			rename (newname, Dfile);
			free_rr (rrlp);
			break;
		}
		if (fstat (fileno (old_fp), &old_stat) != 0) {
			printf("dfile_update: can't get old_file status!\n");
			fclose (new_fp);
			fclose (old_fp);
			free_rr (rrlp);
			break;
		}
		if ((elapsed = (sint31) (new_stat.st_ctime - old_stat.st_ctime)) < 0L)
			elapsed = -elapsed;	/* file times are inconsistant */

		/* Now append any non-duplicate records */
		oldrrp = NULLRR;
		while ((frrp = get_rr (old_fp, oldrrp)) != NULLRR) {
			free_rr (oldrrp);
			if (frrp->name == NULLCHAR
			&& frrp->comment != NULLCHAR)
				put_rr (new_fp, frrp);
			if (frrp->type != TYPE_MISSING
			&& frrp->rdlength > 0
			&& compare_rr_list (rrlp, frrp) != 0) {
				if (frrp->ttl > 0L
				&& (frrp->ttl -= elapsed) <= 0L)
					frrp->ttl = 0L;
				if (frrp->ttl != 0 || ! Dfile_clean)
					put_rr (new_fp, frrp);
			}
			oldrrp = frrp;
			if (!main_exit)
				pwait(NULL);	/* run in background */
		}
		free_rr (oldrrp);
		fclose (new_fp);
		fclose (old_fp);
		free_rr (rrlp);

		/* wait for everyone else to finish reading */
		Dfile_writing++;
		while (Dfile_reading > 0)
			pwait (&Dfile_writing);

		unlink (Dfile);
		rename (newname, Dfile);

		Dfile_writing = 0;
		psignal (&Dfile_reading, 0);
	}
	free (newname);

	net_log(-1,"update Domain.txt finished");
	Dfile_updater = NULLPROC;
}

/**
 **	Domain Server Utilities
 **/
LOCAL void
dumpdomain (struct dhdr *dhp, sint31 rtt)
{
	struct rr *rrp;
	char * stuff;
	printf("response id %u (rtt %lu sec) qr %u opcode %u aa %u tc %u rd %u ra %u rcode %u\n",
	 dhp->id, (long) rtt / 1000L,
	 dhp->qr, dhp->opcode, dhp->aa, dhp->tc, dhp->rd,
	 dhp->ra, dhp->rcode);

	printf("%u questions:\n",dhp->qdcount);
	for (rrp = dhp->questions; rrp != NULLRR; rrp = rrp->next) {
		stuff = dtype (rrp->type);
		printf("%s type %s class %u\n",rrp->name,
		 stuff, rrp->af_class);
	}
	printf("%u answers:\n",dhp->ancount);
	for (rrp = dhp->answers; rrp != NULLRR; rrp = rrp->next) {
		put_rr (stdout, rrp);
	}
	printf("%u authority:\n",dhp->nscount);
	for (rrp = dhp->authority; rrp != NULLRR; rrp = rrp->next) {
		put_rr (stdout, rrp);
	}
	printf("%u additional:\n",dhp->arcount);
	for (rrp = dhp->additional; rrp != NULLRR; rrp = rrp->next) {
		put_rr (stdout, rrp);
	}
	fflush (stdout);
}

/* operation */
/* Search RR */
/* Area for query */
/* Length of same */
LOCAL int
dns_makequery (uint16 op, struct rr *srrp, char *buffer, uint16 buflen)
{
	char *cp, *cp1;
	char *dname, *sname;
	uint16 parameter;
	uint16 dlen, len;

	cp = buffer;
	/* Use millisecond clock for timestamping */
	cp = put16 (cp, (uint16) msclock ());
	parameter = (op << 11)
			| 0x0100;	/* Recursion desired */
	cp = put16 (cp, parameter);
	cp = put16 (cp, 1);
	cp = put16 (cp, 0);
	cp = put16 (cp, 0);
	cp = put16 (cp, 0);

	sname = strdup (srrp->name);
	dname = sname;
	dlen = strlen (dname);
	for (;;) {
		/* Look for next dot */
		cp1 = strchr (dname, '.');
		if (cp1 != NULLCHAR)
			len = cp1-dname;	/* More to come */
		else
			len = dlen;	/* Last component */
		*cp++ = len;		/* Write length of component */
		if (len == 0)
			break;
		/* Copy component up to (but not including) dot */
		strncpy (cp, dname, len);
		cp += len;
		if (cp1 == NULLCHAR) {
			*cp++ = 0;	/* Last one; write null and finish */
			break;
		}
		dname += len + 1;
		dlen -= len + 1;
	}
	free (sname);
	cp = put16 (cp, srrp->type);
	cp = put16 (cp, srrp->af_class);
	return cp - buffer;
}

/* domain server resolution loop
 * returns: any answers in cache.
 *(future features)
 *	multiple queries.
 *	inverse queries.
 */
LOCAL void
dns_query (struct rr *rrlp)
{
	struct mbuf *bp;
	struct dhdr *dhp;
	struct dserver *dp;	/* server list */
	sint31 rtt, abserr;
	int tried = 0;		/* server list has been retried (count) */

	struct sockaddr server_in;
	int s;

	if ((dp = Dservers) == NULLDOM) {
		return;
	}

	s = socket (AF_INET, SOCK_DGRAM, 0);

	for (;;) {
		char *buf;
		int len;
		int rval;

		dp->queries++;

		server_in.sa_family = AF_INET;
		server_in.sin_port = IPPORT_DOMAIN;
		server_in.sin_address = dp->address;

		if (Dtrace) {
			printf("dns_query: querying server %s for %s\n",
			 inet_ntoa (dp->address), rrlp->name);
		}

		buf = (char *) mallocw (512);
		len = dns_makequery (0, rrlp, buf, 512);
		if (sendto (s, buf, len, 0, (char *) &server_in, sizeof (server_in)) == -1)
			perror("domain sendto");
		free (buf);
		alarm (max (1000, 100));
		/* Wait for something to happen */
		rval = recv_mbuf (s, &bp, 0, 0, NULLCHAR, 0);
		alarm (0L);

		if (Dtrace) {
			if (errno == 0)
				printf("dns_query: received message length %d\n",rval);
			else
				perror("dns_query");
		}

		if (rval > 0)
			break;

		if (errno == EABORT) {
			close_s (s);
			return;		/* Killed by "reset" command */
		}

		/* Timeout; back off this one and try another server */
		dp->timeout <<= 1;
		if ((dp = dp->next) == NULLDOM) {
			dp = Dservers;
			if (Dserver_retries > 0 &&++ tried > Dserver_retries) {
				close_s (s);
				return;
			}
		}
	}

	/* got a response */
	close_s (s);
	dp->responses++;
	dhp = (struct dhdr *) mallocw (sizeof (struct dhdr));
	ntohdomain(dhp,&bp);	/* Convert to local format */

	/* Compute and update the round trip time */
	rtt = (sint31) ((uint16) msclock () - dhp->id);
	abserr = rtt > dp->srtt ? rtt - dp->srtt : dp->srtt - rtt;
	dp->srtt = ((AGAIN -1) * dp->srtt + rtt + (AGAIN / 2)) >> LAGAIN;
	dp->mdev = ((DGAIN -1) * dp->mdev + abserr + (DGAIN / 2)) >> LDGAIN;
	dp->timeout = 4 * dp->mdev + dp->srtt;

	/* move to top of list for next time */
	if (dp->prev != NULLDOM) {
		dlist_drop (dp);
		dlist_add (dp);
	}

	if (Dtrace)
		dumpdomain (dhp, rtt);

	/* Add negative reply to answers.  This assumes that there was
	 * only one question, which is true for all questions we send.
	 */
	if (dhp->aa && (dhp->rcode == NAME_ERROR || dhp->ancount == 0)) {
		register struct rr *rrp;
		sint31 ttl = 600L; /* Default TTL for negative records */

		/* look for SOA ttl */
		for (rrp = dhp->authority; rrp != NULLRR; rrp = rrp->next) {
			if (rrp->type == TYPE_SOA)
				ttl = rrp->ttl;
		}

		/* make the questions the negative answers */
		for (rrp = dhp->questions; rrp != NULLRR; rrp = rrp->next)
			rrp->ttl = ttl;
	} else {
		free_rr (dhp->questions);
		dhp->questions = NULLRR;
	}

	/* post in reverse order to maintain original order */
	dcache_update (dhp->additional);
	dcache_update (dhp->authority);
	dcache_update (dhp->answers);
	dcache_update (dhp->questions);

	Dfile_wait_absolute = secclock () + Dfile_wait_relative;
	if (Dfile_updater == NULLPROC) {
		Dfile_updater = newproc("domain update",
			512, dfile_update, 0, NULL, NULL, 0);
	}

#ifdef DO_LANSEND_DEBUG
	if (Dtrace)
		keywait(NULLCHAR,1);	/* so we can look around */
#endif /* DO_LANSEND_DEBUG */
	free ((char *) dhp);
	return;
}

/**
 **	Resolver Utilities
 **/

/* Return TRUE if string appears to be an IP address in dotted decimal;
 * return FALSE otherwise (i.e., if string is a domain name)
 */
LOCAL int
isaddr (register char *s)
{
	char c;

	if (s == NULLCHAR)
		return TRUE;	/* Can't happen */

	while ((c = *s++) != '\0') {
		if (c != '[' && c != ']' && ! isdigit (c) && c != '.')
			return FALSE;
	}
	return TRUE;
}

/* Return "normalized" domain name, with default suffix and trailing '.'
 */
LOCAL char *
checksuffix (char *dname)
{
	char *sname, *tname;
	char *cp;

	sname = strdup (dname);

	/* Eliminate port number from name if specified */
	if (cp = strchr (sname, ':')) {
		*cp = 0;	/* In the copied string, set end to the colon, malloc'ed buffer will retire in its entirety  */
	}

	if (strchr (sname, '.') == NULLCHAR && Dsuffix != NULLCHAR) {
		/* Append default suffix */
		tname = (char *) mallocw (strlen (sname) + strlen (Dsuffix) + 2);
		sprintf(tname,"%s.%s",sname,Dsuffix);
		free (sname);
		sname = tname;
	}
	if (sname[strlen (sname) -1] != '.') {
		/* Append trailing dot */
		tname = (char *) mallocw (strlen (sname) + 2);
		sprintf(tname,"%s.",sname);
		free (sname);
		sname = tname;
	}
	return sname;
}

/* Search for resource records.
 * Returns RR list, or NULLRR if no record found.
 */
LOCAL struct rr *
resolver (register struct rr *rrlp)
{
	register struct rr *result_rrlp;

	if ((result_rrlp = dcache_search (rrlp)) == NULLRR) {
		result_rrlp = dfile_search (rrlp);
	}
	if (result_rrlp == NULLRR || check_ttl (result_rrlp) != 0) {
		dcache_add(result_rrlp); 	/* save any expired RRs */
		dns_query (rrlp);
		result_rrlp = dcache_search (rrlp);
	}
	dcache_add (copy_rr_list (result_rrlp));
	return result_rrlp;
}

/* general entry point for address -> domain name resolution.
 * Returns RR list, or NULLRR if no record found.
 */
ENTRY struct rr *
inverse_a (sint31 ip_address)
{
	struct rr *prrp;
	struct rr *result_rrlp;
	char pname[30];

	if (ip_address == 0L)
		return NULLRR;

	sprintf(pname, "%u.%u.%u.%u.IN-ADDR.ARPA.",
			lobyte (loword (ip_address)),
			hibyte (loword (ip_address)),
			lobyte (hiword (ip_address)),
			hibyte (hiword (ip_address)));

	prrp = make_rr (RR_QUERY, pname, CLASS_IN, TYPE_PTR, 0, 0, NULL);

	prrp->next = 		/* make list to speed search */
		make_rr (RR_INQUERY, NULLCHAR, CLASS_IN, TYPE_A, 0, 4, &ip_address);

	result_rrlp = resolver (prrp);

	free_rr (prrp);
	return result_rrlp;
}

/* general entry point for domain name -> resource resolution.
 * Returns RR list, or NULLRR if no record found.
 */
ENTRY struct rr *
resolve_rr (char *dname, uint16 dtype)
{
	struct rr *qrrp;
	struct rr *result_rrlp;
	char *sname;
	int looping = MAXCNAME;

	if (dname == NULLCHAR)
		return NULLRR;

	sname = checksuffix (dname);
	qrrp = make_rr (RR_QUERY, sname, CLASS_IN, dtype, 0, 0, NULL);
	free (sname);

	while (looping > 0) {
		if ((result_rrlp = resolver (qrrp)) == NULLRR
		|| result_rrlp->type == dtype)
			break;
#ifdef DO_LANSEND_DEBUG
		if (Dtrace)
			put_rr (stdout, result_rrlp);
#endif /* DO_LANSEND_DEBUG */
		/* Should be CNAME or PTR record */
		/* Replace name and try again */
		free (qrrp->name);
		qrrp->name = strdup (result_rrlp->rdata.name);
		free_rr (result_rrlp);
		result_rrlp = NULLRR;
		looping--;
	}
	free_rr (qrrp);
	return result_rrlp;
}

/* main entry point for address -> domain name resolution.
 * Returns string, or NULLCHAR if no name found.
 */
ENTRY char *
resolve_a (sint31 ip_address, int shorten)
{
	char *result = NULLCHAR;

	struct rr *save_rrlp, *rrlp;

	for (rrlp = save_rrlp = inverse_a (ip_address);
	     rrlp != NULLRR && result == NULLCHAR;
	     rrlp = rrlp->next) {
		if (rrlp->rdlength > 0) {
			switch (rrlp->type) {
			case TYPE_PTR:
				result = strdup (rrlp->rdata.name);
				break;
			case TYPE_A:
				result = strdup (rrlp->name);
				break;
			}
		}
	}
	free_rr (save_rrlp);

	if (result != NULLCHAR && shorten) {
		int dot;
		char *shortened;

		if ((dot = strcspn(result, ".")) == 0) {
			shortened = (char *) mallocw (dot + 1);
			strncpy (shortened, result, dot);
			shortened[dot] = '\0';
			free (result);
			result = shortened;
		}
	}
	return result;
}

/* Main entry point for domain name -> address resolution.
 * Returns 0 if name is currently unresolvable.
 */
ENTRY sint31
resolve (char *name)
{
	register struct rr *rrlp;
	sint31 ip_address = 0;

	if (name == NULLCHAR)
		return 0;

	if (stricmp(name, "default") == 0)
		return Default_addr[AF_INET].sin_address;

	if (isaddr (name))
		return atonl (name);

	if ((rrlp = resolve_rr (name, TYPE_A)) != NULLRR
	 && rrlp->rdlength > 0)
		ip_address = rrlp->rdata.addr;

	/* multi-homed hosts are handled here */
	if (rrlp != NULLRR && rrlp->next != NULLRR) {
		register struct rr *rrp;
		register struct route *rp;
		uint16 cost = MAX_UINT16;
		struct sockaddr tmpsock;
		rrp = rrlp;
		/* choose the best of a set of routes */
		while (rrp != NULLRR) {
			tmpsock.sin_address = rrp->rdata.addr;
			tmpsock.sa_family = AF_INET;
			if (rrp->rdlength > 0
			 && (rp = rt_lookup (&tmpsock)) != NULLROUTE
			 && rp->metric <= cost) {
				ip_address = rrp->rdata.addr;
				cost = rp->metric;
			}
			rrp = rrp->next;
		}
	}

	free_rr (rrlp);

	return ip_address;
}

/* Main entry point for MX record lookup.
 * Returns 0 if name is currently unresolvable.
 */
ENTRY sint31
resolve_mx (char *name)
{
	register struct rr *rrp, *arrp;
	char *sname, *tmp, *cp;
	sint31 addr, ip_address = 0;
	uint16 pref = MAX_UINT16;

	if (name == NULLCHAR)
		return 0;

	if (isaddr (name)) {
		if ((sname = resolve_a (atonl (name), FALSE)) == NULLCHAR)
			return 0;
	}
	else
		sname = strdup (name);

	cp = sname;
	while (1) {
		rrp = arrp = resolve_rr (sname, TYPE_MX);
		/* Search this list of rr's for an MX record */
		while (rrp != NULLRR) {
			if (rrp->rdlength > 0 && rrp->rdata.mx.pref <= pref &&
			   (addr = resolve (rrp->rdata.mx.exch)) != 0L) {
				pref = rrp->rdata.mx.pref;
				ip_address = addr;
			}
			rrp = rrp->next;
		}
		free_rr (arrp);
		if (ip_address != 0)
			break;
		/* Compose wild card one level up */
		if ((cp = strchr (cp, '.')) == NULLCHAR)
			break;
		tmp = (char *) mallocw (strlen (cp) + 2);
		sprintf(tmp,"*%s",cp);		/* wildcard expansion */
		free (sname);
		sname = tmp;
		cp = sname + 2;
	}
	free (sname);
	return ip_address;
}

/* Search for local records of the MB, MG and MR type. Returns list of
 * matching records.
 */
ENTRY struct rr *
resolve_mailb (char *name)
{
	register struct rr *result_rrlp;
	struct rr *rrlp;
	char *sname;

	/* Append trailing dot */
	sname = (char *) mallocw (strlen (name) + 2);
	sprintf(sname,"%s.",name);
	rrlp = make_rr (RR_QUERY, sname, CLASS_IN, TYPE_MB, 0, 0, NULL);
	rrlp->next = make_rr (RR_QUERY, sname, CLASS_IN, TYPE_MG, 0, 0, NULL);
	rrlp->next->next = make_rr (RR_QUERY, sname, CLASS_IN, TYPE_MR, 0, 0, NULL);
	free (sname);
	if ((result_rrlp = dcache_search (rrlp)) == NULLRR) {
		result_rrlp = dfile_search (rrlp);
	}
	free_rr (rrlp);
	if (Dsuffix != NULLCHAR) {
		rrlp = result_rrlp;
		while (rrlp != NULLRR) {	/* add domain suffix to data */
			if (rrlp->rdlength > 0 &&
			   rrlp->rdata.name[rrlp->rdlength -1] != '.') {
				sname = (char *) mallocw (rrlp->rdlength +
					strlen (Dsuffix) + 2);
				sprintf(sname,"%s.%s",rrlp->rdata.name,Dsuffix);
				free (rrlp->rdata.name);
				rrlp->rdata.name = sname;
				rrlp->rdlength = strlen (sname);
			}
			rrlp = rrlp->next;
		}
	}
	dcache_add (copy_rr_list (result_rrlp));
	return result_rrlp;
}
