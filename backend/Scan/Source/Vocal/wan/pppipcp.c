
/* ************************************************************************* */
/*
 *	pppipcp.c
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
 *	This file contains the PPP IPCP functions.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.2  2010/02/17 18:40:27  heiand1
 *	Revision History:	SCR 186511. IP Address of 0.0.0.0.
 *	Revision History:	
 *	Revision History:	Revision 1.1.24.1  2009/04/28 20:56:09  zhangn1
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

#include "wan/local.h"

#include "lansend/lansend.h"
#include "trace/trace.h"

/* These defaults are defined in the PPP RFCs, and must not be changed */
static struct ipcp_value_s far ipcp_default = {
	0L,			/* no source address */
	0L,			/* no destination address */

	0,			/* no compression protocol */
	0,			/* no slots */
	0,			/* no slot compression */

	0L,			/* no primary DNS address */
	0L,			/* no secondary DNS address */

};

/* for test purposes, accept anything we understand */
negotiate_t ipcp_accept = IPCP_N_2ADDRESSES | IPCP_N_1ADDRESS
		    | IPCP_N_PRIMARY_DNS | IPCP_N_SECONDARY_DNS
			| IPCP_N_COMPRESS;

/* these lengths are the minimum required for the option */
/*
 *	Translate numeric code provided by fsm_makeoptions in pppfsm to
 *	the actual PPP code used.  The number need not be sequential or
 *	limited to exactly two groups.  It is only required to have the
 *	mask bits defined in pppipcp.h matching the positions in this
 *	array.
 */
static uint8 far option_code[16] = {
	0,					/* 0 is unused */
	IPCP_2ADDRESSES,	/* 1 */
	IPCP_COMPRESS,		/* 2 */
	IPCP_1ADDRESS,		/* 3 */
	0,					/* 4 is unused */
	0,					/* 5 is unused */
	0,					/* 6 is unused */
	0,					/* 7 is unused */
	0,					/* 128 is unused */
	IPCP_PRIMARY_DNS,	/* 129 */
	IPCP_PRIMARY_NBNS,	/* 130 */
	IPCP_SECONDARY_DNS,	/* 131 */
	IPCP_SECONDARY_NBNS,/* 132 */
	0,					/* 133 is unused */
	0,					/* 134 is unused */
	0,					/* 135 is unused */
};

static uint8 far option_length[16] = {
	 0,		/* unused */		/* Standard option group */
	10,		/* addresses */
	 4,		/* compression */
	 6,		/* address */

	 0,		/* unused */
	 0,		/* unused */
	 0,		/* unused */
	 0,		/* unused */

	 0,		/* unused */		/* Extended option group */
	 6,		/* address */
	 6,		/* address */
	 6,		/* address */

	 6,		/* address */
	 0,		/* unused */
	 0,		/* unused */
	 0,		/* unused */
};

static struct fsm_constant_s far ipcp_constants = {
	"IPcp",
	PPP_IPCP_PROTOCOL,
	0x00FE,				/* codes 1-7 recognized */
	fsmCodes,

	IPcp,
	IPCP_REQ_TRY,
	IPCP_NAK_TRY,
	IPCP_TERM_TRY,
	IPCP_TIMEOUT * 1000L,

	IPCP_EXTENDED_LIMIT - IPCP_EXTENDED_OPTIONS + 8,	/* Codes 1 to 12 are possibly used */

	ipcp_free,
	fsm_down,

	ipcp_starting,
	ipcp_opening,
	ipcp_closing,
	ipcp_stopping,

	ipcp_option,
	ipcp_check,
	ipcp_reject
};

/************************************************************************/

/* "ppp <iface> ipcp" subcommands */
static const struct cmds far IPcpcmds[] = {
	{"Close",		doppp_close,		0,	0,	""},
	{"compress",	l_ipcp_compress,	0,	0,	"[tcp|vj|none [slots [flag]]]"},
	{"Local",		doipcp_local,		0,	0,	NULLCHAR},
	{"Open",		doppp_open,			0,	0,	""},
	{"Remote",		doipcp_remote,		0,	0,	NULLCHAR},
	{"Timeout",		doppp_timeout,		0,	0,	"[secs]"},
	{"Try",			doppp_try,			0,	0,	NULLCHAR},
	{NULLCHAR},
};

/* "ppp <iface> ipcp {local | remote}" subcommands */
static const struct cmds far IPcpside_cmds[] = {
	{"address",		doipcp_address,		0,	0,	"[on|off|allow [on|off]]"},
	{"compress",	doipcp_compress,	0,	0,	"[tcp|vj [slots [flag]]|none|allow [on|off]]"},
	{"default",		doipcp_default,		0,	0,	""},
	{"dns",			dodns_address,		0,	0,	"[on|off|allow [on|off]]"},
	{NULLCHAR},
};

ENTRY void
pppipcp_init(void)
{
	memset((void*)&ipcp_default,sizeof(ipcp_default),0);
}

ENTRY int
doppp_ipcp (int argc, char *argv[], void *p)
{
	register struct iface *ifp = (struct iface *) p;
	register struct ppp_s *ppp_p = (struct ppp_s *) ifp->pppedv;

	return subcmd(IPcpcmds, argc, argv, &(ppp_p->fsm[IPcp]));
}

LOCAL int
doipcp_local (int argc, char *argv[], void *p)
{
	struct fsm_s *fsm_p = (struct fsm_s *) p;
	return subcmd(IPcpside_cmds, argc, argv, &(fsm_p->local));
}

LOCAL int
doipcp_remote (int argc, char *argv[], void *p)
{
	struct fsm_s *fsm_p = (struct fsm_s *) p;
	return subcmd(IPcpside_cmds, argc, argv, &(fsm_p->remote));
}

/************************************************************************/
/* Set addresses for PPP interface */
LOCAL int
doipcp_address (int argc, char *argv[], void *p)
{
	struct fsm_side_s *side_p = (struct fsm_side_s *) p;

	if (stricmp(argv[1],"allow") == 0) {
		return chg_bit16 (&(side_p->will), IPCP_N_1ADDRESS,
			"Allow Address", --argc, &argv[1]);
	}
	return chg_bit16 (&(side_p->want), IPCP_N_1ADDRESS,
		"Announce Address", argc, argv);
}

/* Set IP compression type for PPP interface */
LOCAL int
l_ipcp_compress (int argc, char *argv[], void *p)
{
	struct fsm_s *fsm_p = (struct fsm_s *) p;
	return doipcp_compress(argc, argv, &(fsm_p->local));
}

LOCAL int
doipcp_compress (int argc, char *argv[], void *p)
{
	struct fsm_side_s *side_p = (struct fsm_side_s *) p;
	struct ipcp_value_s *want_p = (struct ipcp_value_s *) side_p->want_pdv;

	if (argc < 2) {
		if (side_p->want & IPCP_N_COMPRESS) {
			switch (want_p->compression) {
			case PPP_VJCH_PROTOCOL:
				printf("TCP header compression enabled; "
					"Slots = %d, options = %x\n",
					want_p->slots,
					want_p->slot_compress);
				break;
			default:
				printf("0x%04x\n", want_p->compression);
				break;
			};
		} else {
			printf("None\n");
		}
	} else if (stricmp(argv[1],"allow") == 0) {
		return chg_bit16 (&(side_p->will), IPCP_N_COMPRESS,
			"Allow Compression", --argc, &argv[1]);
	} else if (stricmp(argv[1],"tcp") == 0
		||  stricmp(argv[1],"vj") == 0) {
		want_p->compression = PPP_VJCH_PROTOCOL;
		if (argc >= 3) {
			uint16 slots;
			if (atoi16u_err (argv[2], &slots))
				return 1;
			if (slots < IPCP_SLOT_LO
			 ||  slots > IPCP_SLOT_HI) {
				printf("Slots must be in range %d to %d\n",
					IPCP_SLOT_LO,
					IPCP_SLOT_HI);
				return 1;
			}
			want_p->slots = slots;
		} else {
			want_p->slots = IPCP_SLOT_DEFAULT;
		}
		if (argc >= 4) {
			uint16 x;

			if (atoi16u_err (argv[3], &x))
				return 1;
			want_p->slot_compress = x;
		} else {
			want_p->slot_compress = IPCP_SLOT_COMPRESS;
		}
		side_p->want |= IPCP_N_COMPRESS;
	} else if (stricmp(argv[1],"none") == 0) {
		side_p->want &= ~IPCP_N_COMPRESS;
	} else {
		if (stricmp (argv[-1], "local") == 0)
			cmderror (&IPcpside_cmds[1], -1, argv);
		else
			cmderror (&IPcpcmds[1], -1, argv);
		return 1;
	}
	return 0;
}

/* Set DNS addresses */
LOCAL int
dodns_address (int argc, char *argv[], void *p)
{
	struct fsm_side_s *side_p = (struct fsm_side_s *) p;

	if (stricmp(argv[1],"allow") == 0) {
		return chg_bit16 (&(side_p->will), IPCP_N_PRIMARY_DNS | IPCP_N_SECONDARY_DNS,
			"Allow DNS Address", --argc, &argv[1]);
	}
	return chg_bit16 (&(side_p->want), IPCP_N_PRIMARY_DNS | IPCP_N_SECONDARY_DNS,
		"Announce DNS Address", argc, argv);
}

LOCAL int
doipcp_default (int argc, char *argv[], void *p)
{
	struct fsm_side_s *side_p = (struct fsm_side_s *) p;
	struct ipcp_value_s *want_p = (struct ipcp_value_s *) side_p->want_pdv;

	ASSIGN(*want_p, ipcp_default);
	side_p->want = FALSE;
	side_p->will = ipcp_accept;
	return 0;
}

/************************************************************************/
/*		      O P T I O N   P R O C E S S I N G 		*/
/************************************************************************/

LOCAL void
ipcp_option(struct fsm_s *fsm_p, void *vp, struct mbuf **bpp, uint8 o_type)
{
	struct ipcp_value_s *value_p = (struct ipcp_value_s *) vp;
	struct mbuf *bp = *bpp;
	register char *cp;

	int o_length;
	register int used;

	/*
	 *	Use the incoming code first to get the length and then the
	 *	actual code to be used in the PPP frame (when handling
	 *	additional PPP options which are not consecutively numbered).
	 */
	o_length = option_length[o_type];

	o_type = option_code[o_type];

	used = o_length - OPTION_HDR_LEN;

	/* this only tests for the minimum option length */
	if ((cp = bp->data + bp->cnt) + o_length > (char *) (bp + 1) + bp->size) {
		return;
	}
	*cp++ = o_type;
	*cp++ = o_length;

	switch (o_type) {
	case IPCP_1ADDRESS:
		cp = put32(cp, value_p->address);
		used -= 4;
		PPP_DEBUG_VALUE("    IP address %s",
			inet_ntoa(value_p->address));
		break;

	case IPCP_2ADDRESSES:
		cp = put32(cp, value_p->address);
		cp = put32(cp, value_p->other);
		used -= 8;
		PPP_DEBUG_VALUE("    IP source address %s",
			inet_ntoa(value_p->address));
		PPP_DEBUG_VALUE("    IP destination address %s",
			inet_ntoa(value_p->other));
		break;

	case IPCP_COMPRESS:
		cp = put16(cp, value_p->compression);
		used -= 2;
		PPP_DEBUG_VALUE("    IP compression 0x%04x",
			value_p->compression);

		if (value_p->compression == PPP_VJCH_PROTOCOL) {
			*cp++ = value_p->slots - 1;
			*cp++ = value_p->slot_compress;
			used -= 2;
			PPP_DEBUG_VALUE("    with slots %d",
				value_p->slots);
			PPP_DEBUG_VALUE("    and options %x",
				value_p->slot_compress);
		}
		break;

	case IPCP_PRIMARY_DNS:
		cp = put32(cp, value_p->primary_dns_address);
		used -= 4;
		PPP_DEBUG_VALUE("    Primary DNS address %s",
			inet_ntoa(value_p->primary_dns_address));
		break;

	case IPCP_SECONDARY_DNS:
		cp = put32(cp, value_p->secondary_dns_address);
		used -= 4;
		PPP_DEBUG_VALUE("    Secondary DNS address %s",
			inet_ntoa(value_p->secondary_dns_address));
		break;

	};

	o_length -= used;
	bp->data[bp->cnt + 1] = o_length;       /* length may be modified */
	bp->cnt += o_length;
}

/************************************************************************/
/* Check the options, updating the working values.
 * Returns -1 if ran out of data, ACK/NAK/REJ as appropriate.
 */
LOCAL int
ipcp_check (struct fsm_s *fsm_p, struct option_hdr *ohp, struct mbuf **bpp, int request)
{
	struct ipcp_value_s *lwantp = (struct ipcp_value_s *) fsm_p->local.want_pdv;
	struct ipcp_value_s *rwantp = (struct ipcp_value_s *) fsm_p->remote.want_pdv;
	struct ipcp_value_s *rworkp = (struct ipcp_value_s *) fsm_p->remote.work_pdv;
	struct fsm_side_s *side_p = (request ? &(fsm_p->remote)
					     : &(fsm_p->local));
	struct ipcp_value_s *swantp = (struct ipcp_value_s *) side_p->want_pdv;
	struct ipcp_value_s *sworkp = (struct ipcp_value_s *) side_p->work_pdv;
	int used = ohp->length - OPTION_HDR_LEN;
	int option_result = CONFIG_ACK;		/* Assume good values */
	int test;

	/* see if we allow this option */
	/*
	 *	These option codes need no translation as they come
	 *	from the ppp frame itself.
	 */
	if (ohp->type >= IPCP_EXTENDED_OPTIONS) {
		if (ohp->type > IPCP_EXTENDED_LIMIT
		 ||  ohp->length < option_length[ohp->type - IPCP_EXTENDED_OPTIONS + 8]
		 ||  !((side_p->will | side_p->want) & (1 << (ohp->type - IPCP_EXTENDED_OPTIONS + 8)))) {
			/* toss any bytes in option */
			while (used-- > 0) {
				if (pullchar(bpp) == -1) {
					return -1;
				}
			}
			return CONFIG_REJ;
		}
	} else
	{
		if (ohp->type > IPCP_OPTION_LIMIT
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
	}

	switch (ohp->type) {
	case IPCP_1ADDRESS:
		sworkp->address = pull32(bpp);
		used -= 4;
		PPP_DEBUG_VALUE("    IP address %s",
			inet_ntoa(sworkp->address));

		if (!request) {
			/* Accept whatever the peer wants,
			 * unless specifically configured to refuse.
			 */
			if (!(side_p->will & IPCP_N_1ADDRESS)) {
				/* no changes allowed */
				sworkp->address = swantp->address;
			} else if (sworkp->address == 0L) {
				/* set current address */
				if ((sworkp->address = swantp->address) == 0L) {
					sworkp->address = Default_addr[AF_INET].sin_address;
				}
			}
			break;
		}

		/* Request */
		if (sworkp->address == swantp->address) {
			if (sworkp->address == 0L) {
				if ((sworkp->address
				    = ip_pool(PPPiface)) != 0L) {
					option_result = CONFIG_NAK;
				}
			}
		} else if (swantp->address != 0L) {
			/* Require that the peer use configured address */
			sworkp->address = swantp->address;
			option_result = CONFIG_NAK;
		}
		break;

	case IPCP_2ADDRESSES:
		sworkp->address = pull32(bpp);
		sworkp->other = pull32(bpp);
		used -= 8;
		PPP_DEBUG_VALUE("    IP source address %s",
			inet_ntoa(sworkp->address));
		PPP_DEBUG_VALUE("    IP destination address %s",
			inet_ntoa(sworkp->other));

		if (!request) {
			if (!(side_p->will & IPCP_N_1ADDRESS)) {
				/* no changes allowed */
				sworkp->address = swantp->address;
			} else if (sworkp->address == 0L) {
				/* set current address */
				if ((sworkp->address = swantp->address) == 0L) {
					sworkp->address = Default_addr[AF_INET].sin_address;
				}
			}
			if (rwantp->address != 0L) {
				/* no changes allowed */
				sworkp->other = rwantp->address;
			}
			break;
		}

		/* Request */
		if (sworkp->address == swantp->address) {
			if (sworkp->address == 0L) {
				if ((sworkp->address
				    = ip_pool(PPPiface)) != 0L) {
					option_result = CONFIG_NAK;
				}
			}
		} else if (swantp->address != 0L) {
			/* Require that the peer use configured address */
			sworkp->address = swantp->address;
			option_result = CONFIG_NAK;
		}

		if (sworkp->other == 0L) {
			if (lwantp->address != 0L) {
				rworkp->other = lwantp->address;
				option_result = CONFIG_NAK;
			}
		}
		break;

	case IPCP_COMPRESS:
		sworkp->compression = pull16(bpp);
		used -= 2;
		PPP_DEBUG_VALUE("    IP compression 0x%04x",
			sworkp->compression);

		/* Check if requested type is acceptable */
		switch (sworkp->compression) {
		case PPP_VJCH_PROTOCOL:
			if ((test = pullchar(bpp)) == -1) {
				return -1;
			}
			PPP_DEBUG_VALUE("    with slots %d",
				(test + 1));

			if ((sworkp->slots = test + 1) < IPCP_SLOT_LO) {
				sworkp->slots = IPCP_SLOT_LO;
				option_result = CONFIG_NAK;
			} else if (sworkp->slots > IPCP_SLOT_HI) {
				sworkp->slots = IPCP_SLOT_HI;
				option_result = CONFIG_NAK;
			}

			if ((test = pullchar(bpp)) == -1) {
				return -1;
			}
			PPP_DEBUG_VALUE("    and options %x",
				test);

			if ((sworkp->slot_compress = test) > 1) {
				sworkp->slot_compress = 1;
				option_result = CONFIG_NAK;
			}
			used -= 2;
			break;

		default:
			if (side_p->want & IPCP_N_COMPRESS) {
				sworkp->compression = swantp->compression;
				sworkp->slots = swantp->slots;
				sworkp->slot_compress = swantp->slot_compress;
			} else {
				sworkp->compression = PPP_VJCH_PROTOCOL;
				sworkp->slots = IPCP_SLOT_DEFAULT;
				sworkp->slot_compress = IPCP_SLOT_COMPRESS;
			}
			option_result = CONFIG_NAK;
			break;
		};
		break;

	case IPCP_PRIMARY_DNS:
		sworkp->primary_dns_address = pull32(bpp);
		used -= 4;
		PPP_DEBUG_VALUE("    Primary DNS address %s",
			inet_ntoa(sworkp->primary_dns_address));

		if (!request) {
			/* Accept whatever the peer wants,
			 * unless specifically configured to refuse.
			 */
			if (!(side_p->will & IPCP_N_PRIMARY_DNS)) {
				/* no changes allowed */
				sworkp->primary_dns_address = swantp->primary_dns_address;
			} else if (sworkp->primary_dns_address == 0L) {
				/* set current address */
				if ((sworkp->primary_dns_address = swantp->primary_dns_address) == 0L) {
					/* There is no domain name server provided - live with it */
				}
			}
			break;
		}

		/* Request */
		if (sworkp->primary_dns_address == swantp->primary_dns_address) {
			if (sworkp->primary_dns_address == 0L) {
				if ((sworkp->primary_dns_address = get_nameserver(0)) != 0L) {	/* We should already have this in swant->primary_dns_address */
					option_result = CONFIG_NAK;
				}
			}
		} else if (swantp->primary_dns_address != 0L) {
			/* Require that the peer use configured domain name server address */
			sworkp->primary_dns_address = swantp->primary_dns_address;
			option_result = CONFIG_NAK;
		}
		break;

	case IPCP_SECONDARY_DNS:
		sworkp->secondary_dns_address = pull32(bpp);
		used -= 4;
		PPP_DEBUG_VALUE("    Secondary DNS address %s",
			inet_ntoa(sworkp->secondary_dns_address));

		if (!request) {
			/* Accept whatever the peer wants,
			 * unless specifically configured to refuse.
			 */
			if (!(side_p->will & IPCP_N_SECONDARY_DNS)) {
				/* no changes allowed */
				sworkp->secondary_dns_address = swantp->secondary_dns_address;
			} else if (sworkp->secondary_dns_address == 0L) {
				/* set current address */
				if ((sworkp->secondary_dns_address = swantp->secondary_dns_address) == 0L) {
					/* There is no domain name server provided - live with it */
				}
			}
			break;
		}

		/* Request */
		if (sworkp->secondary_dns_address == swantp->secondary_dns_address) {
			if (sworkp->secondary_dns_address == 0L) {
				if ((sworkp->secondary_dns_address = get_nameserver(1)) != 0L) {	/* We should already have this in swant->secondary_dns_address */
					option_result = CONFIG_NAK;
				}
			}
		} else if (swantp->secondary_dns_address != 0L) {
			/* Require that the peer use configured domain name server address */
			sworkp->secondary_dns_address = swantp->secondary_dns_address;
			option_result = CONFIG_NAK;
		}
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
ipcp_reject (struct fsm_s *fsm_p, struct option_hdr *ohp)
{
	struct ipcp_value_s *lworkp =	(struct ipcp_value_s *) fsm_p->local.work_pdv;
	struct ipcp_value_s *rwantp =	(struct ipcp_value_s *) fsm_p->remote.want_pdv;

	PPP_DEBUG_ROUTINES("ipcp_reject()");

	if (ohp->type == IPCP_1ADDRESS
	  && !(fsm_p->remote.work & IPCP_N_2ADDRESSES)) {
		fsm_p->local.work |= IPCP_N_2ADDRESSES;
		lworkp->other = rwantp->address;
	}
	return 0;
}

/************************************************************************/
/*			I N I T I A L I Z A T I O N			*/
/************************************************************************/

/* Check if we have a specific IP address to assign to remote peer host */
/* !!! TO DO: subnet mask, and routing */
LOCAL uint32
ipcp_lookuppeer (char *peerid)
{
	struct account *ap;

	sint31 peer_addr = 0L;

	if (peerid == NULLCHAR) {
		return 0L;
	}

	if ((ap = account_find (peerid, NULLCHAR)) == NULLACCOUNT) {
		return 0L;
	}

	if (ap->address)
		peer_addr = resolve (ap->address);

	return(peer_addr);
}

/************************************************************************/
/* Prepare to begin configuration exchange */
LOCAL void
ipcp_starting (struct fsm_s *fsm_p)
{
	struct iface *ifp =		fsm_p->ppp_p->iface;
	struct ipcp_pdv_s *ipcp_p =	(struct ipcp_pdv_s *) fsm_p->pdv;
	struct ipcp_value_s *lwantp =	(struct ipcp_value_s *) fsm_p->local.want_pdv;
	struct ipcp_value_s *lworkp =	(struct ipcp_value_s *) fsm_p->local.work_pdv;
	struct ipcp_value_s *rwantp =	(struct ipcp_value_s *) fsm_p->remote.want_pdv;
	struct ipcp_value_s *rworkp =	(struct ipcp_value_s *) fsm_p->remote.work_pdv;

	PPP_DEBUG_ROUTINES("ipcp_starting()");

	/* There are several ways that the local address can be assigned:
	 * 1. peer assigned (most recent)
	 * 2. ifconfig address command (passive, saved)
	 * 3. default global address command (passive)
	 */
	if (ifp->address[AF_INET].sa_family == AF_INET) {
		/* save the address, in case it is replaced */
		ipcp_p->save_local_address = ifp->address[AF_INET].sin_address;
	}

	if (fsm_p->local.work & (IPCP_N_1ADDRESS | IPCP_N_2ADDRESSES)
	 ||  fsm_p->remote.work & IPCP_N_2ADDRESSES) {
		/* retry previous assignment for continuity */
		lwantp->address = lworkp->address;
	} else {
		/* use default interface address */
		lwantp->address = ifp->address[AF_INET].sin_address;
	}

	/* There are several ways that the remote address can be assigned:
	 * 1. authenticated name lookup
	 * 2. peer assigned
	 * 3. pool assignment
	 * 4. ifconfig peer address command (passive, saved)
	 */
	if (ifp->flags & IFF_PEER) {
		/* save the address, in case it is replaced */
		ipcp_p->save_remote_address = ifp->peeraddr[AF_INET].sin_address;
	}

	if ((rwantp->address =
	      ipcp_lookuppeer(fsm_p->ppp_p->peername)) == 0L) {
		if (fsm_p->local.work & IPCP_N_2ADDRESSES
		 || fsm_p->remote.work & (IPCP_N_1ADDRESS | IPCP_N_2ADDRESSES)) {
			/* retry previous assignment for continuity */
			rwantp->address = rworkp->address;
		} else {
			/* use default interface address */
			rwantp->address = ifp->peeraddr[AF_INET].sin_address;
		}
	}

		/* Use this code to reduce need for ACK/NAK/ACK sequence */
		/* This may be used on the client end to reduce connection time */
	if (fsm_p->local.work & (IPCP_N_PRIMARY_DNS | IPCP_N_SECONDARY_DNS)) {
		/* retry previous assignment for continuity */
		lwantp->primary_dns_address = lworkp->primary_dns_address;
		lwantp->secondary_dns_address = lworkp->secondary_dns_address;
	} else
	{
		/* use default domain name server addresses */
		lwantp->primary_dns_address = 0L;
		lwantp->secondary_dns_address = 0L;
	}

	ASSIGN(*lworkp, *lwantp);
	fsm_p->local.work = fsm_p->local.want;

	/* Always ask for address.*/
	fsm_p->local.work |= IPCP_N_1ADDRESS;

	fsm_p->remote.work = FALSE;
}

/************************************************************************/
/* configuration negotiation complete */
LOCAL void
ipcp_opening (struct fsm_s *fsm_p)
{
	struct iface *ifp =		fsm_p->ppp_p->iface;
	struct ipcp_pdv_s *ipcp_p =	(struct ipcp_pdv_s *) fsm_p->pdv;
	struct ipcp_value_s *lwantp =	(struct ipcp_value_s *) fsm_p->local.want_pdv;
	struct ipcp_value_s *lworkp =	(struct ipcp_value_s *) fsm_p->local.work_pdv;
	struct ipcp_value_s *rworkp =	(struct ipcp_value_s *) fsm_p->remote.work_pdv;
	uint32 address = 0L;
	int rslots = 0;
	int tslots = 0;

	/* Set our IP address to reflect negotiated option */
	if (fsm_p->local.work & (IPCP_N_1ADDRESS | IPCP_N_2ADDRESSES)) {
		address = lworkp->address;
	} else if (fsm_p->remote.work & IPCP_N_2ADDRESSES) {
		lworkp->address = address = rworkp->other;
	}

	if (address != 0L || (ifp->flags & IFF_DYNAMIC)) {
		struct sockaddr addr;

		addr.sa_family = AF_INET;
		addr.sin_address = address;

		if (!inet_hostsame (&(ifp->address[AF_INET]), &addr) && (ifp->flags & IFF_DYNAMIC)) {
			/* address not the same as last time */
			register struct tcb *tcb;

			for (tcb = Tcbs; tcb != NULLTCB; tcb = tcb->next) {
				if ((tcb->state == TCP_LISTEN) && (tcb->flags.clone == TRUE)) {
					/* Leave servers alone */
					continue;
				}
				if (inet_hostsame (&tcb->conn.local, &ifp->address[AF_INET])) {
					/* Reset active connections */
					reset_tcp(tcb);
				}
			}
		}

		if (address == 0L) {
			ifp->flags &= ~IFF_DYNAMIC;
			addr = Default_addr[AF_INET];
		} else if (address == lwantp->address) {
			ifp->flags &= ~IFF_DYNAMIC;
		} else {
			ifp->flags |= IFF_DYNAMIC;
		}

		/* Save the prior global address for a possible later restore */
		ipcp_p->save_global_address = Default_addr[AF_INET].sin_address;

		if_setaddr (ifp, &addr, ifp->netmask[AF_INET], TRUE);

#ifdef	DO_LANSEND_PPP_DEBUG_FSA
		if (PPPiface->trace & PPP_DEBUG_FSA)
			trace_log(PPPiface,"IPCP Setting iface address: %s", snhtoa(&addr));
#endif /* DO_LANSEND_PPP_DEBUG_FSA */
	}

	if (fsm_p->remote.work & (IPCP_N_1ADDRESS | IPCP_N_2ADDRESSES)) {
		address = rworkp->address;
	} else if (fsm_p->local.work & IPCP_N_2ADDRESSES) {
		rworkp->address = address = lworkp->other;
	} else {
		address = 0L;
	}
	/* Save the peer address */
	ifp->peeraddr[AF_INET].sin_address = address;

	if (address != 0L) {
		struct sockaddr addr;

		addr.sa_family = AF_INET;
		addr.sin_address = address;

		rt_add(&addr, 0xffffffffL, 0L, ifp, (uint16)1, 0, 0, (sint31)0, (char)1);

#ifdef	DO_LANSEND_PPP_DEBUG_FSA
		if (PPPiface->trace & PPP_DEBUG_FSA)
			trace_log(PPPiface,"IPCP Add route to peer (%s)",
				snhtoa(&addr));
#endif /* DO_LANSEND_PPP_DEBUG_FSA */
	}

	/* free old slhc configuration, if any */
	slhc_free(ipcp_p->slhcp);
	ipcp_p->slhcp = NULL;

	if (fsm_p->local.work & IPCP_N_COMPRESS) {
		rslots = lworkp->slots;
	}
	if (fsm_p->remote.work & IPCP_N_COMPRESS) {
		tslots = rworkp->slots;
	}

	if (rslots != 0 || tslots != 0) {
		ipcp_p->slhcp = slhc_init(rslots, tslots);

#ifdef	DO_LANSEND_PPP_DEBUG_FSA
		if (PPPiface->trace & PPP_DEBUG_FSA)
			trace_log(PPPiface,"IPCP Compression enabled;"
				" Recv slots = %d, options = %x;"
				" Xmit slots = %d, options = %x",
				rslots,
				lworkp->slot_compress,
				tslots,
				rworkp->slot_compress);
#endif /* DO_LANSEND_PPP_DEBUG_FSA */
	}

	/* Configure the negotiated Domain Name Servers */
	if (fsm_p->local.work & (IPCP_N_PRIMARY_DNS | IPCP_N_SECONDARY_DNS)) {
		if (lworkp->primary_dns_address != 0L)
			add_nameserver (lworkp->primary_dns_address);
		if (lworkp->secondary_dns_address != 0L)
			add_nameserver (lworkp->secondary_dns_address);
	}

}

/************************************************************************/
/* Close IPCP */
LOCAL void
ipcp_closing (struct fsm_s *fsm_p)
{
	struct iface *ifp = 		fsm_p->ppp_p->iface;
	struct ipcp_pdv_s *ipcp_p =	(struct ipcp_pdv_s *) fsm_p->pdv;
	struct ipcp_value_s *lworkp =	(struct ipcp_value_s *) fsm_p->local.work_pdv;
	struct ipcp_value_s *rworkp =	(struct ipcp_value_s *) fsm_p->remote.work_pdv;
	uint32 address = 0L;

	/* free old slhc configuration, if any */
	slhc_free(ipcp_p->slhcp);
	ipcp_p->slhcp = NULL;

	if (fsm_p->remote.work & (IPCP_N_1ADDRESS | IPCP_N_2ADDRESSES)) {
		address = rworkp->address;
	} else if (fsm_p->local.work & IPCP_N_2ADDRESSES) {
		address = lworkp->other;
	}

	if (address != 0L) {
		struct sockaddr addr;

		addr.sa_family = AF_INET;
		addr.sin_address = address;

#ifdef	DO_LANSEND_PPP_DEBUG_FSA
		if (PPPiface->trace & PPP_DEBUG_FSA)
			trace_log(PPPiface,"IPCP Drop route to peer (%s)",
				snhtoa(&addr));
#endif /* DO_LANSEND_PPP_DEBUG_FSA */
		rt_drop(&addr, 0xffffffffL, ifp);
	}

	/* clear pool address */
	if (ifp->flags & IFF_POOL) {
		ifp->flags &= ~IFF_POOL;
		ifp->peeraddr[AF_INET].sin_address = 0L;
	}

	/* Restore prior global IP address if configured from device */
	if (ifp->flags & IFF_GLOBAL) {
		Default_addr[AF_INET].sin_address = ipcp_p->save_global_address;
	}

	/* Remove the negotiated Domain Name Servers */
	if (fsm_p->local.work & (IPCP_N_PRIMARY_DNS | IPCP_N_SECONDARY_DNS)) {
		if (lworkp->primary_dns_address != 0L)
			drop_nameserver (lworkp->primary_dns_address);
		if (lworkp->secondary_dns_address != 0L)
			drop_nameserver (lworkp->secondary_dns_address);
	}

}

/************************************************************************/
/* After termination */
LOCAL void
ipcp_stopping (struct fsm_s *fsm_p)
{
	struct iface *ifp =		fsm_p->ppp_p->iface;
	struct ipcp_pdv_s *ipcp_p =	(struct ipcp_pdv_s *) fsm_p->pdv;
	struct sockaddr addr;

	PPP_DEBUG_ROUTINES("ipcp_stopping()");

	if (ifp->address[AF_INET].sa_family == AF_INET) {
		ifp->flags &= ~IFF_DYNAMIC;
		addr.sa_family = AF_INET;
		addr.sin_address = ipcp_p->save_local_address;

		if_setaddr (ifp, &addr, ifp->netmask[AF_INET], TRUE);
	}
	if (ifp->flags & IFF_PEER) {
		ifp->flags &= ~IFF_POOL;
		ifp->peeraddr[AF_INET].sin_address = ipcp_p->save_remote_address;
	}
	/* Restore the global IP address here */
	if (ifp->flags & IFF_GLOBAL) {
		Default_addr[AF_INET].sin_address = ipcp_p->save_global_address;
	}

}

/************************************************************************/
/* Attach configuration structures */
ENTRY void
ipcp_attach (struct ppp_s *ppp_p)
{
	struct fsm_s *fsm_p = &(ppp_p->fsm[IPcp]);
	struct ipcp_value_s *value_p;

	PPPiface = ppp_p->iface;

	PPP_DEBUG_ROUTINES("ipcp_attach()");

	fsm_p->ppp_p = ppp_p;
	fsm_p->pdc = &ipcp_constants;
	fsm_p->pdv = callocw(1,sizeof(struct ipcp_pdv_s));

	/* Set local option parameters to first request defaults */
	fsm_p->local.will = ipcp_accept;

	fsm_p->local.want_pdv =
	value_p = (struct ipcp_value_s *) callocw (1, sizeof(struct ipcp_value_s));
	ASSIGN(*value_p, ipcp_default);
	fsm_p->local.want = FALSE;

	fsm_p->local.work_pdv =
	value_p = (struct ipcp_value_s *) callocw (1, sizeof(struct ipcp_value_s));
	ASSIGN(*value_p, ipcp_default);
	fsm_p->local.work = FALSE;

	/* Set remote option parameters to first request defaults */
	fsm_p->remote.will = ipcp_accept;

	fsm_p->remote.want_pdv =
	value_p = (struct ipcp_value_s *) callocw (1, sizeof(struct ipcp_value_s));
	ASSIGN(*value_p, ipcp_default);
	fsm_p->remote.want = FALSE;

	fsm_p->remote.work_pdv =
	value_p = (struct ipcp_value_s *) callocw (1, sizeof(struct ipcp_value_s));
	ASSIGN(*value_p, ipcp_default);
	fsm_p->remote.work = FALSE;

	fsm_attach(fsm_p);
}

/* Initialize protocol operation */
ENTRY void
ipcp_init (struct ppp_s *ppp_p)
{
	struct fsm_s *fsm_p = &(ppp_p->fsm[IPcp]);

	PPPiface = ppp_p->iface;

	PPP_DEBUG_ROUTINES("ipcp_init()");

	fsm_init(fsm_p);
}

LOCAL void
ipcp_free (struct fsm_s *fsm_p)
{
	struct ipcp_pdv_s *ipcp_p =	fsm_p->pdv;

	slhc_free(ipcp_p->slhcp);
	ipcp_p->slhcp = NULL;
}
