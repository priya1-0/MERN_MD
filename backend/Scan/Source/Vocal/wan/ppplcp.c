
/* ************************************************************************* */
/*
 *	ppplcp.c
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
 *	Module:		WAN
 *
 *	This file contains the PPP LCP functions.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.2  2010/02/17 18:29:58  heiand1
 *	Revision History:	SCR 186241. Enhance Memory Handling in Heap.
 *	Revision History:	
 *	Revision History:	Revision 1.1.24.1  2009/04/28 20:56:09  zhangn1
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

#include "wan/local.h"

#include "term/term.h"
#include "trace/trace.h"

/* These defaults are defined in the PPP RFCs, and must not be changed */
static struct lcp_value_s far lcp_default = {
	LCP_MRU_DEFAULT,
	LCP_ACCM_DEFAULT,
	0,		/* no authentication */
	0,		/* no monitoring */
	0L,		/* no reporting period */
	0L		/* no magic number */
};

/* for test purposes, accept anything we understand */
negotiate_t lcp_accept = LCP_N_MRU | LCP_N_ACCM
			| LCP_N_AP /* | LCP_N_QMP */ | LCP_N_MAGIC
			| LCP_N_PFC | LCP_N_ACFC;

/* these lengths are the minimum required for the option */
static uint8 far option_length[] = {
	 0,		/* unused */
	 4,		/* MRU */
	 6,		/* ACCM */
	 4,		/* authentication */
	 4,		/* quality monitoring */
	 6,		/* magic number */
	 0,		/* reserved */
	 2,		/* Protocol compression */
	 2		/* Address/Control compression */
};

static struct fsm_constant_s far lcp_constants = {
	"Lcp",
	PPP_LCP_PROTOCOL,
	0x0FFE,				/* codes 1-11 recognized */
	fsmCodes,

	Lcp,
	LCP_REQ_TRY,
	LCP_NAK_TRY,
	LCP_TERM_TRY,
	LCP_TIMEOUT * 1000L,

	LCP_OPTION_LIMIT,

	lcp_free,
	fsm_down,

	lcp_starting,
	lcp_opening,
	lcp_closing,
	lcp_stopping,

	lcp_option,
	lcp_check,
	lcp_reject
};

/************************************************************************/

/* "ppp <iface> lcp" subcommands */
static const struct cmds far Lcpcmds[] = {
	{"authenticate", l_lcp_auth,		0,	0,	"[chap|pap]"},
	{"Close",		doppp_close,		0,	0,	""},
	{"Local",		dolcp_local,		0,	0,	NULLCHAR},
	{"mru",			l_lcp_mru,			0,	0,	"[bytes]"},
	{"Open",		doppp_open,			0,	0,	""},
	{"Remote",		dolcp_remote,		0,	0,	NULLCHAR},
	{"Timeout",		doppp_timeout,		0,	0,	"[secs]"},
	{"Try",			doppp_try,			0,	0,	NULLCHAR},
	{NULLCHAR},
};

/* "ppp <iface> lcp [local | remote]" subcommands */
static const struct cmds far Lcpside_cmds[] = {
	{"accm",		dolcp_accm,			0,	0,	"[bitmap|allow [on|off]]"},
	{"acfc",		dolcp_acfc,			0,	0,	"[on|off|allow [on|off]]"},
	{"authenticate", dolcp_auth,		0,	0,	"[chap [digest]|pap|none|allow [on|off]]"},
	{"magic",		dolcp_magic,		0,	0,	"[value|on|off|allow [on|off]]"},
	{"mru",			dolcp_mru,			0,	0,	"[bytes|allow [on|off]]"},
	{"pfc",			dolcp_pfc,			0,	0,	"[on|off|allow [on|off]]"},
	{"default",		dolcp_default,		0,	0,	""},
	{NULLCHAR},
};

ENTRY void
ppplcp_init(void)
{
	lcp_accept = LCP_N_MRU | LCP_N_ACCM
			| LCP_N_AP /* | LCP_N_QMP */ | LCP_N_MAGIC
			| LCP_N_PFC | LCP_N_ACFC;
}

ENTRY int
doppp_lcp (int argc, char *argv[], void *p)
{
	register struct iface *ifp = (struct iface *) p;
	register struct ppp_s *ppp_p = (struct ppp_s *) ifp->pppedv;

	return subcmd(Lcpcmds, argc, argv, &(ppp_p->fsm[Lcp]));
}

LOCAL int
dolcp_local (int argc, char *argv[], void *p)
{
	struct fsm_s *fsm_p = (struct fsm_s *) p;
	return subcmd(Lcpside_cmds, argc, argv, &(fsm_p->local));
}

LOCAL int
dolcp_remote (int argc, char *argv[], void *p)
{
	struct fsm_s *fsm_p = (struct fsm_s *) p;
	return subcmd(Lcpside_cmds, argc, argv, &(fsm_p->remote));
}

/************************************************************************/

LOCAL int
dolcp_accm (int argc, char *argv[], void *p)
{
	struct fsm_side_s *side_p = (struct fsm_side_s *) p;
	struct lcp_value_s *want_p = (struct lcp_value_s *) side_p->want_pdv;

	if (argc < 2) {
		printf("0x%08lx\n",want_p->accm);
	} else if (stricmp(argv[1],"allow") == 0) {
		return chg_bit16 (&(side_p->will),LCP_N_ACCM,
			"Allow ACCM", --argc, &argv[1]);
	} else {
		if (atoi32u_err (argv[1], &want_p->accm))
			return 1;
		if (want_p->accm != LCP_ACCM_DEFAULT)
			side_p->want |= LCP_N_ACCM;
		else
			side_p->want &= ~LCP_N_ACCM;
	}
	return 0;
}

LOCAL int
dolcp_acfc (int argc, char *argv[], void *p)
{
	struct fsm_side_s *side_p = (struct fsm_side_s *) p;

	if (stricmp(argv[1],"allow") == 0) {
		return chg_bit16(&(side_p->will),LCP_N_ACFC,
			"Allow Address/Control Field Compression", --argc, &argv[1]);
	}
	return chg_bit16(&(side_p->want), LCP_N_ACFC,
		"Address/Control Field Compression", argc, argv);
}

LOCAL int
l_lcp_auth (int argc, char *argv[], void *p)
{
	struct fsm_s *fsm_p = (struct fsm_s *) p;
	return dolcp_auth(argc, argv, &(fsm_p->local));
}

LOCAL int
dolcp_auth (int argc, char *argv[], void *p)
{
	struct fsm_side_s *side_p = (struct fsm_side_s *) p;
	struct lcp_value_s *want_p = (struct lcp_value_s *) side_p->want_pdv;

	if (argc < 2) {
		if (side_p->want & LCP_N_AP) {
			switch (want_p->authentication) {
			case PPP_PAP_PROTOCOL:
				printf("Pap\n");
				break;
			case PPP_CHAP_PROTOCOL:
				printf("CHap\n");
				break;
			default:
				printf("0x%04x\n", want_p->authentication);
				break;
			};
		} else {
			printf("None\n");
		}
	} else if (stricmp(argv[1],"allow") == 0) {
		return chg_bit16(&(side_p->will),LCP_N_AP,
			"Allow Authentication", --argc, &argv[1]);
	} else if (stricmp(argv[1],"pap") == 0) {
		side_p->want |= LCP_N_AP;
		want_p->authentication = PPP_PAP_PROTOCOL;
	} else if (stricmp(argv[1],"chap") == 0) {
		side_p->want |= LCP_N_AP;
		want_p->authentication = PPP_CHAP_PROTOCOL;

		if (argc < 3)
			want_p->chap_digest = CHAP_MD5;
		else {
			uint16 x;
			if (atoi16u_err (argv[2], &x))
				return 1;
			want_p->chap_digest = x;
		}
	} else if (stricmp(argv[1],"none") == 0) {
		side_p->want &= ~LCP_N_AP;
	} else {
		printf("Choices: allow chap pap none\n");
		return 1;
	}
	return 0;
}

LOCAL int
dolcp_magic (int argc, char *argv[], void *p)
{
	struct fsm_side_s *side_p = (struct fsm_side_s *) p;
	struct lcp_value_s *want_p = (struct lcp_value_s *) side_p->want_pdv;

	if (argc < 2) {
		printf("%d\n",(int)want_p->magic_number);
	} else if (stricmp(argv[1],"allow") == 0) {
		return chg_bit16(&(side_p->will),LCP_N_MAGIC,
			"Allow Magic Number", --argc, &argv[1]);
	} else {
		int test;

		/* Check for keyword */
		if (chg_bool (&test, "Magic Number", argc, argv) == 0) {
			if (test) {
				/* Make a non-zero random number */
				want_p->magic_number = (sint31)&want_p->magic_number
					+ time(NULL);
			}
			else {
				want_p->magic_number = 0;
			}
		}
		else {
			if (atoi32u_err (argv[1], &want_p->magic_number))
				return 1;
		}

		if (want_p->magic_number) {
			side_p->want |= LCP_N_MAGIC;
		} else {
			side_p->want &= ~LCP_N_MAGIC;
		}
	}
	return 0;
}

LOCAL int
l_lcp_mru (int argc, char *argv[], void *p)
{
	struct fsm_s *fsm_p = (struct fsm_s *) p;
	return dolcp_mru(argc, argv, &(fsm_p->local));
}

LOCAL int
dolcp_mru (int argc, char *argv[], void *p)
{
	struct fsm_side_s *side_p = (struct fsm_side_s *) p;
	struct lcp_value_s *want_p = (struct lcp_value_s *) side_p->want_pdv;

	if (argc < 2) {
		printf("%d\n",want_p->mru);
	} else if (stricmp(argv[1],"allow") == 0) {
		return chg_bit16(&(side_p->will),LCP_N_MRU,
			"Allow MRU", --argc, &argv[1]);
	} else {
		uint16 x;

		if (atoi16u_err (argv[1], &x))
			return 1;

		if (x < LCP_MRU_LO || x > LCP_MRU_HI) {
			printf("MRU must be between %d to %d\n",
				LCP_MRU_LO, LCP_MRU_HI);
			return -1;
		} else if (x != LCP_MRU_DEFAULT) {
			side_p->want |= LCP_N_MRU;
		} else {
			side_p->want &= ~LCP_N_MRU;
		}
		want_p->mru = x;
	}
	return 0;
}

LOCAL int
dolcp_pfc (int argc, char *argv[], void *p)
{
	struct fsm_side_s *side_p = (struct fsm_side_s *) p;

	if (stricmp(argv[1],"allow") == 0) {
		return chg_bit16(&(side_p->will),LCP_N_PFC,
			"Allow Protocol Field Compression", --argc, &argv[1]);
	}
	return chg_bit16(&(side_p->want), LCP_N_PFC,
		"Protocol Field Compression", argc, argv);
}

LOCAL int
dolcp_default (int argc, char *argv[], void *p)
{
	struct fsm_side_s *side_p = (struct fsm_side_s *) p;
	struct lcp_value_s *want_p = (struct lcp_value_s *) side_p->want_pdv;

	ASSIGN(*want_p, lcp_default);
	side_p->want = FALSE;
	side_p->will = lcp_accept;
	return 0;
}

/************************************************************************/
/*		      O P T I O N   P R O C E S S I N G 		*/
/************************************************************************/

LOCAL void
lcp_option (struct fsm_s *fsm_p, void *vp, struct mbuf **bpp, uint8 o_type)
{
	struct lcp_value_s *value_p = (struct lcp_value_s *) vp;
	struct mbuf *bp = *bpp;
	register char *cp;
	int o_length = option_length[o_type];
	register int used = o_length - OPTION_HDR_LEN;

	/* this only tests for the minimum option length */
	if ((cp = bp->data + bp->cnt) + o_length > (char *)(bp + 1) + bp->size) {
		return;
	}
	*cp++ = o_type;
	*cp++ = o_length;

	switch (o_type) {
	case LCP_MRU:
		put16(cp, value_p->mru);
		used -= 2;
		PPP_DEBUG_VALUE("    MRU: %d", value_p->mru);
		break;

	case LCP_ACCM:
		put32(cp, value_p->accm);
		used -= 4;
		PPP_DEBUG_VALUE("    ACCM: 0x%08lx", value_p->accm);
		break;

	case LCP_AP:
		cp = put16(cp, value_p->authentication);
		used -= 2;
		PPP_DEBUG_VALUE("    Auth Protocol: 0x%04x",
			value_p->authentication);

		if (value_p->authentication == PPP_CHAP_PROTOCOL) {
			*cp++ = value_p->chap_digest;
			used -= 1;
			PPP_DEBUG_VALUE("    with message digest %d",
				value_p->chap_digest);
		}
		break;

	case LCP_MAGIC:
		put32(cp, value_p->magic_number);
		used -= 4;
		PPP_DEBUG_VALUE("    Magic Number: 0x%08lx",
			value_p->magic_number);
		break;

	case LCP_PFC:
		PPP_DEBUG_BOOLEAN("    Protocol compression");
                break;

	case LCP_ACFC:
		PPP_DEBUG_BOOLEAN("    Addr/Ctl compression");
		break;
	};

	o_length -= used;
	bp->data[bp->cnt + 1] = o_length;	/* length may be modified */
	bp->cnt += o_length;
}

/************************************************************************/
/* Check the options, updating the working values.
 * Returns -1 if ran out of data, ACK/NAK/REJ as appropriate.
 */
LOCAL int
lcp_check (struct fsm_s *fsm_p, struct option_hdr *ohp, struct mbuf **bpp, int request)
{

	struct lcp_value_s *lworkp = (struct lcp_value_s *) fsm_p->local.work_pdv;
	struct lcp_value_s *rworkp = (struct lcp_value_s *) fsm_p->remote.work_pdv;
	struct fsm_side_s *side_p = (request ? &(fsm_p->remote)
					     : &(fsm_p->local));
	struct lcp_value_s *swantp = (struct lcp_value_s *) side_p->want_pdv;
	struct lcp_value_s *sworkp = (struct lcp_value_s *) side_p->work_pdv;
	int used = ohp->length - OPTION_HDR_LEN;
	int option_result = CONFIG_ACK;		/* Assume good values */
	int test;

	/* see if we allow this option */
	if (ohp->type > LCP_OPTION_LIMIT
	 ||  ohp->length < option_length[ohp->type]
	 ||  !((side_p->will | side_p->want) & (1 << ohp->type))) {
		/* toss any bytes in option */
		while (used-- > 0) {
			if (pullchar(bpp) == -1) {
				return -1;
			}
		}
		return CONFIG_REJ;
	}

	switch (ohp->type) {
	case LCP_MRU:
		sworkp->mru = pull16(bpp);
		used -= 2;
		PPP_DEBUG_VALUE("    MRU: %d", sworkp->mru);

		/* Check if new value is appropriate */
		if (sworkp->mru < LCP_MRU_LO) {
			sworkp->mru = LCP_MRU_LO;
			option_result = CONFIG_NAK;
		} else if (sworkp->mru > LCP_MRU_HI) {
			sworkp->mru = LCP_MRU_HI;
			option_result = CONFIG_NAK;
		}
		if (request
		  && (side_p->want & LCP_N_MRU)
		  && sworkp->mru > swantp->mru) {
			/* send a smaller packet anyway */
			sworkp->mru = swantp->mru;
		}
		break;

	case LCP_ACCM:
		sworkp->accm = pull32(bpp);
		used -= 4;
		PPP_DEBUG_VALUE("    ACCM: 0x%08lx", sworkp->accm);

		/* Remote host may ask to escape more control
		 * characters than we require, but must escape
		 * at least the control chars that we require.
		 */
		if ((side_p->want & LCP_N_ACCM)
		 &&  sworkp->accm != (sworkp->accm | swantp->accm)) {
			sworkp->accm |= swantp->accm;
			option_result = CONFIG_NAK;
		}
		break;

	case LCP_AP:
		sworkp->authentication = pull16(bpp);
		used -= 2;
		PPP_DEBUG_VALUE("    Auth Protocol: 0x%04x",
			sworkp->authentication);

		/* Check if new value is appropriate */
		switch (sworkp->authentication) {
		case PPP_PAP_PROTOCOL:
			/* Yes */
			break;
		case PPP_CHAP_PROTOCOL:
			if ((test = pullchar(bpp)) == -1) {
				return -1;
			}
			PPP_DEBUG_VALUE("    with message digest %d",
				test);

			if ((sworkp->chap_digest = test) != CHAP_MD5) {
				sworkp->chap_digest = CHAP_MD5;
				option_result = CONFIG_NAK;
			}
			used -= 1;
			break;

		default:
			if (side_p->want & LCP_N_AP) {
				sworkp->authentication = swantp->authentication;
				sworkp->chap_digest = swantp->chap_digest;
			} else {
				sworkp->authentication = PPP_CHAP_PROTOCOL;
				sworkp->chap_digest = CHAP_MD5;
			}
			option_result = CONFIG_NAK;
			break;
		};
		break;

	case LCP_MAGIC:
		sworkp->magic_number = pull32(bpp);
		used -= 4;
		PPP_DEBUG_VALUE("    Magic Number: 0x%08lx",
			sworkp->magic_number);

		/* Ensure that magic numbers are different */
		if (sworkp->magic_number == 0L) {
			sworkp->magic_number = (uint32)sworkp;
			option_result = CONFIG_NAK;
		} else if (rworkp->magic_number == lworkp->magic_number) {
			sworkp->magic_number += msclock ();
			option_result = CONFIG_NAK;
		}
		break;

	case LCP_PFC:
		PPP_DEBUG_BOOLEAN("    Protocol compression");
		break;

	case LCP_ACFC:
		PPP_DEBUG_BOOLEAN("    Addr/Ctl compression");
		break;

	default:
		option_result = CONFIG_REJ;
		break;
	};

	if (used < 0) {
		return -1;
	}

	if (used > 0) {
		/* toss extra bytes in option */
		while (used-- > 0) {
			if (pullchar(bpp) == -1) {
				return -1;
			}
		}
	}

	return (option_result);
}

/************************************************************************/
/* Process configuration reject sent by remote host */
LOCAL int
lcp_reject (struct fsm_s *fsm_p, struct option_hdr *ohp)
{
	PPP_DEBUG_ROUTINES("lcp_reject()");
	return 0;
}

/************************************************************************/
/*			I N I T I A L I Z A T I O N			*/
/************************************************************************/

/* Check for PPP Network-Layer Protocol Phase */
ENTRY void
ppp_ready (struct ppp_s *ppp_p)
{
	if (!(ppp_p->flags & (PPP_AP_LOCAL | PPP_AP_REMOTE))) {
		/* no pending authentication */
		ppp_p->phase = pppNETWORK;
		ppp_p->upsince = secclock();
		fsm_up(&(ppp_p->fsm[IPcp]));
		fsm_up(&(ppp_p->fsm[IPXcp]));
	}
}

/************************************************************************/
/* Prepare to begin configuration exchange */
ENTRY void
lcp_starting (struct fsm_s *fsm_p)
{
	struct lcp_value_s *lwantp =	(struct lcp_value_s *) fsm_p->local.want_pdv;
	struct lcp_value_s *lworkp =	(struct lcp_value_s *) fsm_p->local.work_pdv;

	PPP_DEBUG_ROUTINES("lcp_starting()");
	fsm_p->ppp_p->phase = pppESTABLISH;

	if (fsm_p->local.want & LCP_N_MAGIC) {
		lwantp->magic_number += msclock ();
	}

	ASSIGN(*lworkp, *lwantp);
	fsm_p->local.work = fsm_p->local.want;

	fsm_p->remote.work = FALSE;

	/* Set Default Max Transmission Unit for outgoing packets */
	fsm_p->ppp_p->iface->mtu = LCP_MRU_DEFAULT;
}

/************************************************************************/
/* configuration negotiation complete */
LOCAL void
lcp_opening (struct fsm_s *fsm_p)
{
	struct iface *ifp =		fsm_p->ppp_p->iface;
	struct lcp_value_s *lworkp =	(struct lcp_value_s *) fsm_p->local.work_pdv;
	struct lcp_value_s *rworkp =	(struct lcp_value_s *)fsm_p->remote.work_pdv;
	struct mbuf *tempbp;

	if (!(fsm_p->remote.work & LCP_N_MRU)) {
		rworkp->mru = LCP_MRU_DEFAULT;
	}

	if (ifp->mtu != rworkp->mru) {
		/* Set new Max Transmission Unit for outgoing packets */
		ifp->mtu = rworkp->mru;

		if (PPPiface->trace & PPP_DEBUG_FSA)
			trace_log(PPPiface,"    Set new MTU for outgoing packets: %d",
				ifp->mtu);
	}

	/* delay transition to next phase to allow remote ACCM to settle */
	tempbp = alloc_mbuf (500);
	if (tempbp == NULLBUF) {
		printf("lcp_opening mbuf failed \n");
		return;
	}

	ppp_discard(ifp,tempbp);

	/* check for authentication */
	fsm_p->ppp_p->phase = pppAUTHENTICATE;
	fsm_p->ppp_p->flags &= ~(PPP_AP_LOCAL | PPP_AP_REMOTE);
	free(fsm_p->ppp_p->peername);
	fsm_p->ppp_p->peername = NULLCHAR;

	if (fsm_p->local.work & LCP_N_AP) {
		switch (lworkp->authentication) {
		case PPP_PAP_PROTOCOL:
			pap_local(fsm_p->ppp_p);
			break;
		case PPP_CHAP_PROTOCOL:
			chap_local(fsm_p->ppp_p);
			break;
		};
	}
	if (fsm_p->remote.work & LCP_N_AP) {
		switch (rworkp->authentication) {
		case PPP_PAP_PROTOCOL:
			pap_remote(fsm_p->ppp_p);
			break;
		case PPP_CHAP_PROTOCOL:
			chap_remote(fsm_p->ppp_p);
			break;
		};
	}

	/* check for authentication complete */
	ppp_ready(fsm_p->ppp_p);
}

/************************************************************************/
/* Close higher levels in preparation for link shutdown */
LOCAL void
lcp_closing (struct fsm_s *fsm_p)
{
	struct ppp_s *ppp_p =		fsm_p->ppp_p;
	int i;

	ppp_p->phase = pppTERMINATE;

	for (i = Lcp + 1; i < fsmi_Size;) {
		struct fsm_s *fsm_p = &(ppp_p->fsm[i++]);

		if (fsm_p->pdc != NULL
		  && fsm_p->pdc->down != NULL) {
			(*fsm_p->pdc->down)(fsm_p);
		}
	}
}

/************************************************************************/
/* After termination */
LOCAL void
lcp_stopping (struct fsm_s *fsm_p)
{
	struct iface *ifp =		fsm_p->ppp_p->iface;

	PPP_DEBUG_ROUTINES("lcp_stopping()");

	/* Now, tell the device to go down.
	 * In turn, the device should tell our IO status
	 * when it has gone down.
	 */
	if (ifp->ioctl != NULL) {
		ifp->ioctl(ifp,PARAM_DOWN,TRUE,0L);
	} else {
		ppp_iostatus (ifp, PARAM_DOWN, 0L);
	}
	hangup (ifp);
}

/************************************************************************/
/* Attach configuration structures */
ENTRY void
lcp_attach (struct ppp_s *ppp_p)
{
	struct fsm_s *fsm_p = &(ppp_p->fsm[Lcp]);
	struct lcp_value_s *value_p;

	PPPiface = ppp_p->iface;

	PPP_DEBUG_ROUTINES("lcp_attach()");

	fsm_p->ppp_p = ppp_p;
	fsm_p->pdc = &lcp_constants;
	fsm_p->pdv = NULL;

	/* Set local option parameters to first request defaults */
	fsm_p->local.will = lcp_accept;

	fsm_p->local.want_pdv =
	value_p = (struct lcp_value_s *) callocw (1, sizeof(struct lcp_value_s));
	ASSIGN(*value_p, lcp_default);
	fsm_p->local.want = FALSE;

	fsm_p->local.work_pdv =
	value_p = (struct lcp_value_s *) callocw (1, sizeof(struct lcp_value_s));
	ASSIGN(*value_p, lcp_default);
	fsm_p->local.work = FALSE;

	/* Set remote option parameters to first request defaults */
	fsm_p->remote.will = lcp_accept;

	fsm_p->remote.want_pdv =
	value_p = (struct lcp_value_s *) callocw (1, sizeof(struct lcp_value_s));
	ASSIGN(*value_p, lcp_default);
	fsm_p->remote.want = FALSE;

	fsm_p->remote.work_pdv =
	value_p = (struct lcp_value_s *) callocw (1, sizeof(struct lcp_value_s));
	ASSIGN(*value_p, lcp_default);
	fsm_p->remote.work = FALSE;

	fsm_attach(fsm_p);

}

/* Initialize protocol operation */
ENTRY void
lcp_init (struct ppp_s *ppp_p)
{
	struct fsm_s *fsm_p = &(ppp_p->fsm[Lcp]);

	PPPiface = ppp_p->iface;

	PPP_DEBUG_ROUTINES("lcp_init()");

	fsm_init(fsm_p);
}

LOCAL void
lcp_free (struct fsm_s *fsm_p)
{
	/* nothing to do */
}
