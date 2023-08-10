
/* ************************************************************************* */
/*
 *	pppfsm.c
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
 *	This file contains the PPP Finite State Machine (FSM) functions.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
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

#include "trace/trace.h"

struct iface *PPPiface = NULLIF;  /* iface for trace */

char far *fsmStates[] = {
	"Initial",
	"Starting",
	"Closed",
	"Stopped",
	"Closing",
	"Stopping",
	"Req Sent",
	"Ack Rcvd",
	"Ack Sent",
	"Opened"
};

char far *fsmCodes[] = {
	NULL,
	"Config Request",
	"Config Ack",
	"Config Nak",
	"Config Reject",
	"Termin Request",
	"Termin Ack",
	"Code Reject",
	"Protocol Reject",
	"Echo Request",
	"Echo Reply",
	"Discard Request"
};

ENTRY void
pppfsm_init(void)
{
	PPPiface = NULLIF;
}

/************************************************************************/
/* Convert header in host form to network form */
LOCAL struct mbuf *
htoncnf (struct config_hdr *cnf, struct mbuf *bp)
{
	register char *cp;

	pushdown(&bp, CONFIG_HDR_LEN);
	cp = bp->data;
	*cp++ = cnf->code;
	*cp++ = cnf->identifier;
	put16(cp, cnf->length);

	return bp;
}

/* Extract header from incoming packet */
ENTRY int
ntohcnf (struct config_hdr *cnf, struct mbuf **bpp)
{
	char cnfb[CONFIG_HDR_LEN];

	if (cnf == NULL)
		return -1;

	if (pullup(bpp, cnfb, CONFIG_HDR_LEN) < CONFIG_HDR_LEN)
		return -1;

	cnf->code = cnfb[0];
	cnf->identifier = cnfb[1];
	cnf->length = get16(&cnfb[2]);
	return 0;
}

/***************************************/
/* Convert configuration option header in host form to network form
 * and copy data
 */
ENTRY void
htonopt_copy (struct mbuf **bpp, struct option_hdr *opt, struct mbuf **copy_bpp)
{
	struct mbuf *bp = *bpp;
	register char *cp;
	register int used = opt->length - OPTION_HDR_LEN;

	if ((cp = bp->data + bp->cnt) + opt->length
	      > (char *)(bp + 1) + bp->size) {
		trace_log(PPPiface, "not enough room in buffer for option");
		return;
	}
	*cp++ = opt->type;
	*cp++ = opt->length;

	while (used-- > 0) {
		*cp++ = PULLCHAR(copy_bpp);
	}
	bp->cnt += opt->length;
}

/* Extract configuration option header */
ENTRY int
ntohopt (struct option_hdr *opt, struct mbuf **bpp)
{
	char optb[OPTION_HDR_LEN];

	if (opt == NULL)
		return -1;

	if (pullup(bpp, optb, OPTION_HDR_LEN) < OPTION_HDR_LEN)
		return -1;

	opt->type = optb[0];
	opt->length = optb[1];
	return 0;
}

/************************************************************************/
/* General log routine */
ENTRY void
fsm_log (struct fsm_s *fsm_p, char *comment)
{
	if (PPPiface->trace & PPP_DEBUG_FSA)
		trace_log(PPPiface,"%s %-8s; %s",
			fsm_p->pdc->name,
			fsmStates[fsm_p->state],
			comment);
}

/************************************************************************/
/* Set a timer in case an expected event does not occur */
ENTRY void
fsm_timer (struct fsm_s *fsm_p)
{
	PPP_DEBUG_ROUTINES("fsm_timer()");

	start_timer(&(fsm_p->timer));
}

/************************************************************************/
/* Send a packet to the remote host */
ENTRY int
fsm_send (struct fsm_s *fsm_p, uint8 code, uint8 identifier, struct mbuf *bp)
{
	struct ppp_s *ppp_p = fsm_p->ppp_p;
	struct iface *ifp = ppp_p->iface;
	struct config_hdr hdr;
	int ret;

	switch (hdr.code = code) {
	case CONFIG_REQ:
	case TERM_REQ:
	case ECHO_REQ:
		/* Save ID field for match against replies from remote host */
		fsm_p->lastid = ppp_p->id;
		/* fallthru */
	case PROT_REJ:
	case DISCARD_REQ:
		/* Use a unique ID field value */
		hdr.identifier = ppp_p->id++;
		break;

	case CONFIG_ACK:
	case CONFIG_NAK:
	case CONFIG_REJ:
	case TERM_ACK:
	case CODE_REJ:
	case ECHO_REPLY:
		/* Use ID sent by remote host */
		hdr.identifier = identifier;
		break;

	default:
		/* we're in trouble */
		trace_log(PPPiface,"%s %-8s;"
			" Send with bogus code: %d",
			fsm_p->pdc->name,
			fsmStates[fsm_p->state],
			code);
		return -1;
	};

	switch (code) {
	case ECHO_REQ:
	case ECHO_REPLY:
	case DISCARD_REQ:
	{
		register struct lcp_value_s *vp = (struct lcp_value_s *) fsm_p->local.work_pdv;
		pushdown(&bp, sizeof(vp->magic_number));
		put32(bp->data, vp->magic_number);
	}
	};

	hdr.length = len_p(bp) + CONFIG_HDR_LEN;

	/* Prepend header to packet data */
	bp = htoncnf(&hdr,bp);

	if (PPPiface->trace & PPP_DEBUG_PACKET) {
		trace_log(PPPiface,"%s %-8s;"
			" Sending %s, id: %d, len: %d",
			fsm_p->pdc->name,
			fsmStates[fsm_p->state],
			*(fsm_p->pdc->codes + code),
			hdr.identifier,hdr.length);
	}

	ppp_p->OutNCP[fsm_p->pdc->fsmi]++;

	bp->b_type = fsm_p->pdc->protocol;
	bp->priority = MQP_FAST;
	ret = (*ifp->iftype->outgoing)(ifp, bp, NULL);
	return ret;
}

/************************************************************************/
/* Build a list of options */
LOCAL void
fsm_makeoptions(struct fsm_s *fsm_p, void *vp, struct mbuf **bpp, negotiate_t negotiating)
{
	register int o_type;

	PPP_DEBUG_ROUTINES("fsm_makeoptions()");

	for (o_type = 1; o_type <= fsm_p->pdc->option_limit; o_type++) {
		if (negotiating & (1 << o_type)) {
			(*fsm_p->pdc->option)(fsm_p, vp, bpp, o_type);
		}
	}
}

/************************************************************************/
/* Build a request to send to remote host */
LOCAL struct mbuf *
fsm_makereq (struct fsm_s *fsm_p)
{
	struct mbuf *req_bp = NULLBUF;

	PPP_DEBUG_ROUTINES("fsm_makereq()");

	if ((req_bp = alloc_ibuf(MXU_DEFAULT,CONFIG_HDR_LEN)) != NULLBUF) {
		fsm_makeoptions(fsm_p, fsm_p->local.work_pdv,
				&req_bp, fsm_p->local.work);
	}
	return(req_bp);
}

/************************************************************************/
/* Send a Configure Request */
LOCAL int
fsm_configreq (struct fsm_s *fsm_p)
{
	struct mbuf *bp;
	int ret;

	PPP_DEBUG_ROUTINES("fsm_configreq()");
	if (fsm_p->retry_request <= 0) {
		return -1;
	}

	fsm_p->retry_request--;
	fsm_timer(fsm_p);

	bp = fsm_makereq(fsm_p);
	ret = fsm_send(fsm_p, CONFIG_REQ, 0, bp);
	return ret;
}

/************************************************************************/
/* Send a Terminate Request */
LOCAL int
fsm_termreq (struct fsm_s *fsm_p)
{
	int ret;

	PPP_DEBUG_ROUTINES("fsm_termreq()");

	if (fsm_p->retry_request <= 0) {
		return -1;
	}

	fsm_p->retry_request--;
	fsm_timer(fsm_p);
	ret = fsm_send(fsm_p, TERM_REQ, 0, NULLBUF);
	return ret;
}

/************************************************************************/
/* Send a Terminate Ack */
LOCAL int
fsm_termack (struct fsm_s *fsm_p, uint8 identifier)
{
	int ret;

	PPP_DEBUG_ROUTINES("fsm_termack()");

	ret = fsm_send(fsm_p, TERM_ACK, identifier, NULLBUF);
	return ret;
}

/************************************************************************/
/* Initialize Restart Counter */
LOCAL void
fsm_irc (struct fsm_s *fsm_p)
{

	PPP_DEBUG_ROUTINES("fsm_irc()");

	fsm_p->retry_request = fsm_p->try_configure;
	fsm_p->retry_nak = fsm_p->try_nak;
}

/************************************************************************/
/* Zero Restart Counter */
LOCAL void
fsm_zrc (struct fsm_s *fsm_p)
{

	PPP_DEBUG_ROUTINES("fsm_zrc()");

	fsm_p->retry_request = 0;
	fsm_timer(fsm_p);
}

/************************************************************************/
/* Configuration negotiation complete */
LOCAL void
fsm_opening (struct fsm_s *fsm_p)
{

	FSM_LOG(fsm_p, "Opened");

	stop_timer(&(fsm_p->timer));

	(*fsm_p->pdc->opening)(fsm_p);
}

/************************************************************************/
/* Check configuration options requested by the remote host */
LOCAL int
fsm_request (struct fsm_s *fsm_p, struct config_hdr *config, struct mbuf *bp)
{
	sint31 signed_length = config->length;
	struct mbuf *reply_bp = NULLBUF;	/* reply packet */
	int reply_result = CONFIG_ACK;		/* reply to request */
	negotiate_t desired;			/* desired to negotiate */
	struct option_hdr option;		/* option header storage */
	struct mbuf *option_bp = NULLBUF;	/* option copy */
	int option_result;			/* option reply (signed) */
	int remaining;

	uint8 option_type;

	PPP_DEBUG_ROUTINES("fsm_request()");
	fsm_p->remote.work = FALSE;		/* clear all options */

	if ((reply_bp = alloc_ibuf(MXU_DEFAULT,CONFIG_HDR_LEN)) == NULLBUF) {
		free_p(bp);
		return -1;
	}

	/* Process options requested by remote host */
	while (signed_length > 0  &&  ntohopt(&option, &bp) != -1) {
		if ((signed_length -= option.length) < 0) {
			PPP_DEBUG_CHECKS("REQ: bad header length");
			free_p(bp);
			free_p(reply_bp);
			return -1;
		}

		/* save rest of option for later */
		if ((remaining = option.length - OPTION_HDR_LEN) > 0) {
			dup_p(&option_bp, bp, 0, remaining);
			if (option_bp == NULLBUF) {
				free_p(bp);
				free_p(reply_bp);
				return -1;
			}
		}

		if ((option_result = (*fsm_p->pdc->check)(fsm_p, &option,
				&bp, TRUE)) < 0) {
			PPP_DEBUG_CHECKS("REQ: ran out of data");
			free_p(bp);
			free_p(reply_bp);
                        free_p(option_bp);
			return -1;
		}

#ifdef DO_LANSEND_PPP_DEBUG_OPTIONS
if (PPPiface->trace & PPP_DEBUG_OPTIONS) {
	trace_log(PPPiface, "REQ: %s, option %d, length %d",
                fsmCodes[option_result],
                option.type,
		option.length);
}
#endif /* DO_LANSEND_PPP_DEBUG_OPTIONS */
		if (option_result < reply_result) {

	free_p(option_bp);
	option_bp = NULLBUF;
			continue;
		} else if (option_result > reply_result) {
			/* Discard current list of replies */
			reply_bp->cnt = 0;
			reply_result = option_result;
		}

		option_type = option.type;
		if (fsm_p->pdc->protocol == PPP_IPCP_PROTOCOL) {
			if ((option_type >= IPCP_EXTENDED_OPTIONS) && (option_type <= IPCP_EXTENDED_LIMIT)) {
				option_type = option_type - IPCP_EXTENDED_OPTIONS + 8;
			}
		}

		switch (option_result) {
		case CONFIG_ACK:
			fsm_p->remote.work |= (1 << option_type);
			htonopt_copy(&reply_bp, &option, &option_bp);
			break;
		case CONFIG_NAK:
			fsm_p->remote.work |= (1 << option_type);
			(*fsm_p->pdc->option)(fsm_p, fsm_p->remote.work_pdv,
						&reply_bp, option.type);
			break;
		case CONFIG_REJ:
			htonopt_copy(&reply_bp, &option, &option_bp);
			break;
		};
		free_p(option_bp);
		option_bp = NULLBUF;
	}

	/* Now check for any missing options which are desired */
	if (fsm_p->retry_nak > 0
	 &&  (desired = fsm_p->remote.want & ~fsm_p->remote.work) != 0) {
		switch (reply_result) {
		case CONFIG_ACK:
			reply_bp->cnt = 0;
			reply_result = CONFIG_NAK;
			/* fallthru */
		case CONFIG_NAK:
			fsm_makeoptions(fsm_p, fsm_p->remote.want_pdv,
					&reply_bp, desired);
			fsm_p->retry_nak--;
			break;
		case CONFIG_REJ:
			/* do nothing */
			break;
		};
	} else if (reply_result == CONFIG_NAK) {
		/* if too many NAKs, reject instead */
		if (fsm_p->retry_nak > 0) {
			fsm_p->retry_nak--;
		} else {
			reply_result = CONFIG_REJ;
		}
	}

	/* Send ACK/NAK/REJ to remote host */
	fsm_send(fsm_p, reply_result, config->identifier, reply_bp);
	free_p(bp);
	return (reply_result != CONFIG_ACK);
}

/************************************************************************/
/* Process configuration ACK sent by remote host */
LOCAL int
fsm_ack (struct fsm_s *fsm_p, struct config_hdr *config, struct mbuf *bp)
{
	struct mbuf *request_bp;
	int error = FALSE;

	PPP_DEBUG_ROUTINES("fsm_ack()");

	/* ID field must match last request we sent */
	if (config->identifier != fsm_p->lastid) {
		PPP_DEBUG_CHECKS("ACK: wrong ID");
		free_p(bp);
		return -1;
	}

	/* Get a copy of last request we sent */
	request_bp = fsm_makereq(fsm_p);

	/* Overall buffer length should match */
	if (config->length != len_p(request_bp)) {
		PPP_DEBUG_CHECKS("ACK: buffer length mismatch");
		error = TRUE;
	} else {
		register int req_char;
		register int ack_char;

		/* Each byte should match */
		while ((req_char = pullchar(&request_bp)) != -1) {
			if ((ack_char = pullchar(&bp)) == -1
			 || ack_char != req_char) {
				PPP_DEBUG_CHECKS("ACK: data mismatch");
				/*
				trace_log(PPPiface, "req=%02X, ack=%02X",
					req_char,
					ack_char);
				 */
				error = TRUE;
				break;
			}
		}
	}
	free_p(request_bp);
	free_p(bp);

	if (error) {
		return -1;
	}

	PPP_DEBUG_CHECKS("ACK: valid");
	return 0;
}

/************************************************************************/
/* Process configuration NAK sent by remote host */
LOCAL int
fsm_nak (struct fsm_s *fsm_p, struct config_hdr *config, struct mbuf *bp)
{
	sint31 signed_length = config->length;
	struct option_hdr option;
	int last_option = 0;
	int result;

	uint8 option_type;

	PPP_DEBUG_ROUTINES("fsm_nak()");

	/* ID field must match last request we sent */
	if (config->identifier != fsm_p->lastid) {
		PPP_DEBUG_CHECKS("NAK: wrong ID");
		free_p(bp);
		return -1;
	}

	/* First, process in order.  Then, process extra "important" options */
	while (signed_length > 0  &&  ntohopt(&option, &bp) != -1) {
		if ((signed_length -= option.length) < 0) {
			PPP_DEBUG_CHECKS("NAK: bad header length");
			free_p(bp);
			return -1;
		}

		option_type = option.type;
		if (fsm_p->pdc->protocol == PPP_IPCP_PROTOCOL) {
			if ((option_type >= IPCP_EXTENDED_OPTIONS) && (option_type <= IPCP_EXTENDED_LIMIT)) {
				option_type = option_type - IPCP_EXTENDED_OPTIONS + 8;
			}
		}

		if (option_type > fsm_p->pdc->option_limit) {
			PPP_DEBUG_CHECKS("NAK: option out of range");
			/* option is allowed, but ignored */
			continue;
		} else if (!(fsm_p->local.work & (1 << option_type))) {
			fsm_p->local.work |= (1 << option_type);
			last_option = fsm_p->pdc->option_limit + 1;
		} else if (option_type < last_option) {
			PPP_DEBUG_CHECKS("NAK: option out of order");
			/* assumes options are always in numerical order */
			free_p(bp);
			return -1;
		} else {
			last_option = option_type;
		}
		if ((result =
		      (*fsm_p->pdc->check)(fsm_p, &option,
				&bp, FALSE)) < 0) {
			PPP_DEBUG_CHECKS("NAK: ran out of data");
			free_p(bp);
			return -1;
		}
		/* update the negotiation status */
		if (result == CONFIG_REJ) {
			fsm_p->local.work &= ~(1 << option_type);
		}
	}
	PPP_DEBUG_CHECKS("NAK: valid");
	free_p(bp);
	return 0;
}

/************************************************************************/
/* Process configuration Reject sent by remote host */
LOCAL int
fsm_reject (struct fsm_s *fsm_p, struct config_hdr *config, struct mbuf *bp)
{
	sint31 signed_length = config->length;
	struct option_hdr option;
	int last_option = 0;

	uint8 option_type;

	PPP_DEBUG_ROUTINES("fsm_reject()");

	/* ID field must match last request we sent */
	if (config->identifier != fsm_p->lastid) {
		PPP_DEBUG_CHECKS("REJ: wrong ID");
		free_p(bp);
		return -1;
	}

	/* Process in order, checking for errors */
	while (signed_length > 0  &&  ntohopt(&option, &bp) != -1) {
		register int k;

		if ((signed_length -= option.length) < 0) {
			PPP_DEBUG_CHECKS("REJ: bad header length");
			free_p(bp);
			return -1;
		}
#ifdef	DO_LANSEND_PPP_DEBUG_OPTIONS
if (PPPiface->trace & PPP_DEBUG_OPTIONS)
	trace_log(PPPiface, "    rejected option %d", option.type);
#endif /* DO_LANSEND_PPP_DEBUG_OPTIONS */

		option_type = option.type;
		if (fsm_p->pdc->protocol == PPP_IPCP_PROTOCOL) {
			if ((option_type >= IPCP_EXTENDED_OPTIONS) && (option_type <= IPCP_EXTENDED_LIMIT)) {
				option_type = option_type - IPCP_EXTENDED_OPTIONS + 8;
			}
		}

		if (option_type > fsm_p->pdc->option_limit) {
			PPP_DEBUG_CHECKS("REJ: option out of range");
			free_p(bp);
			return -1;
		} else if (!(fsm_p->local.work & (1 << option_type))) {
			PPP_DEBUG_CHECKS("REJ: option not negotiated");
			free_p(bp);
			return -1;
		} else if (option_type < last_option) {
			PPP_DEBUG_CHECKS("REJ: option out of order");
			/* assumes options are always in numerical order */
			free_p(bp);
			return -1;
		}

		/* currently, contents of options are not checked.
		 * just check that the data is all there.
		 */
		k = option.length - OPTION_HDR_LEN;
		if (pullup(&bp, NULLCHAR, k) != k) {
			PPP_DEBUG_CHECKS("REJ: ran out of data");
			free_p(bp);
			return -1;
		}
		if ((*fsm_p->pdc->reject)(fsm_p, &option) != 0) {
			free_p(bp);
			return -1;
		}

		fsm_p->local.work &= ~(1 << option_type);
	}

	PPP_DEBUG_CHECKS("REJ: valid");
	free_p(bp);
	return 0;
}

/************************************************************************/
/*			E V E N T   P R O C E S S I N G			*/
/************************************************************************/

/* Process incoming packet */
ENTRY void
fsm_proc (struct fsm_s *fsm_p, struct mbuf *bp)
{
	struct config_hdr hdr;
	uint16 rejected;

	PPPiface = fsm_p->ppp_p->iface;

	if (ntohcnf(&hdr, &bp) == -1) {
		FSM_LOG(fsm_p, "short configuration packet");
	}

	if (PPPiface->trace & PPP_DEBUG_PACKET) {
		trace_log(PPPiface,"%s %-8s;"
			" Processing %s, id: %d, len: %d",
			fsm_p->pdc->name,
			fsmStates[fsm_p->state],
			*(fsm_p->pdc->codes + hdr.code),
			hdr.identifier, hdr.length);
	}

	printf("%s %-8s; Processing %s, id: %d, len: %d\n",
		   fsm_p->pdc->name,
		   fsmStates[fsm_p->state],
		   *(fsm_p->pdc->codes + hdr.code),
		   hdr.identifier, hdr.length);

	hdr.length -= CONFIG_HDR_LEN;		/* Length includes envelope */
	trim_mbuf(&bp, hdr.length);		/* Trim off padding */

	switch (hdr.code) {
	case CONFIG_REQ:
		switch (fsm_p->state) {
		case fsmOPENED:
			(*fsm_p->pdc->closing)(fsm_p);
			(*fsm_p->pdc->starting)(fsm_p);
			fsm_configreq(fsm_p);
			fsm_p->state =
			(fsm_request(fsm_p, &hdr, bp) == 0)
				? fsmACK_Sent : fsmREQ_Sent;
			break;

		case fsmSTARTING:	/* can't happen? */
		case fsmSTOPPED:
			fsm_irc(fsm_p);
			(*fsm_p->pdc->starting)(fsm_p);
			fsm_configreq(fsm_p);
			/* fallthru */
		case fsmREQ_Sent:
		case fsmACK_Sent:
			fsm_p->state =
			(fsm_request(fsm_p, &hdr, bp) == 0)
				? fsmACK_Sent : fsmREQ_Sent;
			break;

		case fsmACK_Rcvd:
			if (fsm_request(fsm_p, &hdr, bp) == 0) {
				fsm_opening(fsm_p);
				fsm_p->state = fsmOPENED;
			}
			break;

		case fsmINITIAL:	/* can't happen? */
		case fsmCLOSED:
			/* Don't accept any connections */
			fsm_termack(fsm_p, hdr.identifier);
			/* fallthru */
		case fsmCLOSING:
		case fsmSTOPPING:
			/* We are attempting to close connection; */
			/* wait for timeout to resend a Terminate Request */
			free_p(bp);
			break;
		};
		break;

	case CONFIG_ACK:
		switch (fsm_p->state) {
		case fsmREQ_Sent:
			if (fsm_ack(fsm_p, &hdr, bp) == 0) {
				fsm_irc(fsm_p);
				fsm_p->state = fsmACK_Rcvd;
			}
			break;

		case fsmACK_Sent:
			if (fsm_ack(fsm_p, &hdr, bp) == 0) {
				fsm_irc(fsm_p);
				fsm_opening(fsm_p);
				fsm_p->state = fsmOPENED;
			}
			break;

		case fsmOPENED:		/* Unexpected event? */
                        (*fsm_p->pdc->closing)(fsm_p);
			(*fsm_p->pdc->starting)(fsm_p);
                        /* fallthru */
		case fsmACK_Rcvd:	/* Unexpected event? */
			free_p(bp);
			fsm_configreq(fsm_p);
			fsm_p->state = fsmREQ_Sent;
			break;

		case fsmINITIAL:	/* can't happen? */
		case fsmSTARTING:	/* can't happen? */
		case fsmCLOSED:
		case fsmSTOPPED:
			/* Out of Sync */
			fsm_termack(fsm_p, hdr.identifier);
			/* fallthru */
		case fsmCLOSING:
		case fsmSTOPPING:
			/* We are attempting to close connection; */
			/* wait for timeout to resend a Terminate Request */
			free_p(bp);
			break;
		};
		break;

	case CONFIG_NAK:
		switch (fsm_p->state) {
		case fsmREQ_Sent:
		case fsmACK_Sent:
			/* Update our request to reflect NAKed options */
			if (fsm_nak(fsm_p, &hdr, bp) == 0) {
				fsm_irc(fsm_p);
				/* Send updated config request */
				fsm_configreq(fsm_p);
				/* stay in same state */
			}
			break;

		case fsmOPENED: 	/* Unexpected event? */
			(*fsm_p->pdc->closing)(fsm_p);
			(*fsm_p->pdc->starting)(fsm_p);
			/* fallthru */
		case fsmACK_Rcvd:	/* Unexpected event? */
			free_p(bp);
			fsm_configreq(fsm_p);
			fsm_p->state = fsmREQ_Sent;
			break;

		case fsmINITIAL:	/* can't happen? */
		case fsmSTARTING:	/* can't happen? */
		case fsmCLOSED:
		case fsmSTOPPED:
			/* Out of Sync */
			fsm_termack(fsm_p, hdr.identifier);
			/* fallthru */
		case fsmCLOSING:
			/* We are attempting to close connection; */
			/* wait for timeout to resend a Terminate Request */
			free_p(bp);
			break;
		};
		break;

	case CONFIG_REJ:
		switch (fsm_p->state) {
		case fsmREQ_Sent:
		case fsmACK_Sent:
			/* Update our request to reflect REJECTed options */
			if (fsm_reject(fsm_p, &hdr, bp) == 0) {
				fsm_irc(fsm_p);
				/* Send updated config request */
				fsm_configreq(fsm_p);
				/* stay in same state */
			}
			break;

		case fsmOPENED:		/* Unexpected event? */
			(*fsm_p->pdc->closing)(fsm_p);
			(*fsm_p->pdc->starting)(fsm_p);
			/* fallthru */
		case fsmACK_Rcvd:	/* Unexpected event? */
			free_p(bp);
			fsm_configreq(fsm_p);
			fsm_p->state = fsmREQ_Sent;
			break;

		case fsmINITIAL:	/* can't happen? */
		case fsmSTARTING:	/* can't happen? */
		case fsmCLOSED:
		case fsmSTOPPED:
			/* Out of Sync */
			fsm_termack(fsm_p, hdr.identifier);
			/* fallthru */
		case fsmCLOSING:
			/* We are attempting to close connection; */
			/* wait for timeout to resend a Terminate Request */
			free_p(bp);
			break;
		};
		break;

	case TERM_REQ:
		FSM_LOG(fsm_p, "Peer requested Termination");

		switch (fsm_p->state) {
		case fsmOPENED:
			(*fsm_p->pdc->closing)(fsm_p);
			fsm_zrc(fsm_p);
			fsm_termack(fsm_p, hdr.identifier);
			fsm_p->state = fsmSTOPPING;
			break;

		case fsmACK_Rcvd:
		case fsmACK_Sent:
			fsm_p->state = fsmREQ_Sent;
			/* fallthru */
		case fsmREQ_Sent:
		case fsmCLOSING:
		case fsmSTOPPING:
			/* waiting for timeout */
			/* fallthru */
		case fsmINITIAL:	/* can't happen? */
		case fsmSTARTING:	/* can't happen? */
		case fsmCLOSED:
		case fsmSTOPPED:
			/* Unexpected, but make them happy */
			fsm_termack(fsm_p, hdr.identifier);
			break;
		};
		break;

	case TERM_ACK:
		switch (fsm_p->state) {
		case fsmCLOSING:
			stop_timer(&(fsm_p->timer));

			FSM_LOG(fsm_p, "Terminated");
			(*fsm_p->pdc->stopping)(fsm_p);
			fsm_p->state = fsmCLOSED;
			break;

		case fsmSTOPPING:
			stop_timer(&(fsm_p->timer));

			FSM_LOG(fsm_p, "Terminated");
			(*fsm_p->pdc->stopping)(fsm_p);
			fsm_p->state = fsmSTOPPED;
			break;

		case fsmOPENED:
			/* Remote host has abruptly closed connection */
			FSM_LOG(fsm_p, "Terminated unexpectly");
			(*fsm_p->pdc->closing)(fsm_p);
			(*fsm_p->pdc->starting)(fsm_p);
			fsm_configreq(fsm_p);
			fsm_p->state = fsmREQ_Sent;
			break;

		case fsmACK_Rcvd:
			fsm_p->state = fsmREQ_Sent;
			/* fallthru */
		case fsmREQ_Sent:
		case fsmACK_Sent:
			/* waiting for timeout */
			/* fallthru */
		case fsmINITIAL:	/* can't happen? */
		case fsmSTARTING:	/* can't happen? */
		case fsmCLOSED:
		case fsmSTOPPED:
			/* Unexpected, but no action needed */
			break;
		};
		break;

	case CODE_REJ:
		trace_log(PPPiface,"%s Code Reject;"
			" indicates faulty implementation",
			fsm_p->pdc->name);

		switch (fsm_p->state) {
/* !!! need more code */
		default:
			(*fsm_p->pdc->stopping)(fsm_p);
			break;

		case fsmINITIAL:	/* can't happen? */
		case fsmSTARTING:	/* can't happen? */
		case fsmCLOSED:
		case fsmSTOPPED:
		case fsmCLOSING:
		case fsmSTOPPING:
			break;
		};
		free_p(bp);
		break;

	case PROT_REJ:
		rejected = pull16(&bp);
		trace_log(PPPiface,"%s Protocol Reject;"
			" please do not use this protocol %04X",
			fsm_p->pdc->name,
			rejected);

		switch (rejected) {
		case PPP_IPCP_PROTOCOL:
			fsm_down(&(fsm_p->ppp_p->fsm[IPcp]));
			break;

		case PPP_IPXCP_PROTOCOL:
			fsm_down(&(fsm_p->ppp_p->fsm[IPXcp]));
			break;
		};
		free_p(bp);
		break;

	case ECHO_REQ:
		switch (fsm_p->state) {
		case fsmOPENED:
			fsm_send(fsm_p, ECHO_REPLY, hdr.identifier, bp);
			break;

		case fsmCLOSED:
		case fsmSTOPPED:
			/* Out of Sync */
			fsm_termack(fsm_p, hdr.identifier);
			/* fallthru */
		case fsmREQ_Sent:
		case fsmACK_Rcvd:
		case fsmACK_Sent:
		case fsmCLOSING:
			/* ignore */
			free_p(bp);
			break;
		};
		break;

	case ECHO_REPLY:
	case DISCARD_REQ:
		free_p(bp);
		break;

	default:
		trace_log(PPPiface,"%s Unknown packet type: %d;"
			" Sending Code Reject",
			fsm_p->pdc->name,
			hdr.code);

		hdr.length += CONFIG_HDR_LEN;	/* restore length */
		bp = htoncnf(&hdr, bp);	/* put header back on */
		fsm_send(fsm_p, CODE_REJ, hdr.identifier, bp);

		switch (fsm_p->state) {
		case fsmREQ_Sent:
		case fsmACK_Rcvd:
		case fsmACK_Sent:
		case fsmOPENED:
			fsm_p->state = fsmSTOPPED;
			break;

		case fsmCLOSED:
		case fsmSTOPPED:
		case fsmCLOSING:
			/* no change */
			break;
		};
		break;
	};
}

/************************************************************************/
/* Timeout while waiting for reply from remote host */
LOCAL void
fsm_timeout (void *vp)
{
	struct fsm_s *fsm_p = (struct fsm_s *)vp;

	PPPiface = fsm_p->ppp_p->iface;

	FSM_LOG(fsm_p, "Timeout");

	switch (fsm_p->state) {
	case fsmREQ_Sent:
	case fsmACK_Sent:
		if (fsm_p->retry_request > 0) {
			fsm_configreq(fsm_p);
		} else {
			FSM_LOG(fsm_p, "Request retry exceeded");
			(*fsm_p->pdc->stopping)(fsm_p);
			fsm_p->state = fsmSTOPPED;
		}
		break;

	case fsmACK_Rcvd:
		if (fsm_p->retry_request > 0) {
			fsm_configreq(fsm_p);
			fsm_p->state = fsmREQ_Sent;
		} else {
			FSM_LOG(fsm_p, "Request retry exceeded");
			(*fsm_p->pdc->stopping)(fsm_p);
			fsm_p->state = fsmSTOPPED;
		}
		break;

	case fsmCLOSING:
		if (fsm_p->retry_request > 0) {
			fsm_termreq(fsm_p);
		} else {
			FSM_LOG(fsm_p, "Terminate retry exceeded");
			(*fsm_p->pdc->stopping)(fsm_p);
			fsm_p->state = fsmCLOSED;
		}
		break;

	case fsmSTOPPING:
		if (fsm_p->retry_request > 0) {
			fsm_termreq(fsm_p);
		} else {
			FSM_LOG(fsm_p, "Terminate retry exceeded");
			(*fsm_p->pdc->stopping)(fsm_p);
			fsm_p->state = fsmSTOPPED;
		}
		break;

	default:
		/* can't happen */
		break;
	}
}

/************************************************************************/
/*			I N I T I A L I Z A T I O N			*/
/************************************************************************/

/* Lower Layer Up Event */
ENTRY void
fsm_up (struct fsm_s *fsm_p)
{

	if (fsm_p->pdc == NULL) {
		return;
	}

	PPPiface = fsm_p->ppp_p->iface;

	FSM_LOG(fsm_p, "Up event");
	switch (fsm_p->state) {
	case fsmINITIAL:
		(*fsm_p->pdc->starting)(fsm_p);
		fsm_p->state = fsmCLOSED;
		break;

	case fsmSTARTING:
		fsm_irc(fsm_p);
		(*fsm_p->pdc->starting)(fsm_p);
		fsm_configreq(fsm_p);
		fsm_p->state = fsmREQ_Sent;
		break;

	default:
		/* already up */
		break;
	};
}

/************************************************************************/
/* Lower Layer Down Event */
ENTRY void
fsm_down (struct fsm_s *fsm_p)
{

	if (fsm_p->pdc == NULL) {
		return;
	}

	PPPiface = fsm_p->ppp_p->iface;

	FSM_LOG(fsm_p, "Down event");

	switch (fsm_p->state) {
	case fsmCLOSED:
		fsm_p->state = fsmINITIAL;
		break;
	case fsmSTOPPED:
		/*TLS*/
		fsm_p->state = fsmSTARTING;
		break;

	case fsmCLOSING:
		stop_timer(&(fsm_p->timer));
		fsm_p->state = fsmINITIAL;
		break;
	case fsmSTOPPING:
	case fsmREQ_Sent:
	case fsmACK_Rcvd:
	case fsmACK_Sent:
		stop_timer(&(fsm_p->timer));
		fsm_p->state = fsmSTARTING;
		break;

	case fsmOPENED:
		(*fsm_p->pdc->closing)(fsm_p);
		fsm_p->state = fsmSTARTING;
		break;

	default:
		/* already down */
		break;
	};
}

/************************************************************************/
/* Administratively Open the link */
ENTRY void
fsm_open (struct fsm_s *fsm_p)
{

	if (fsm_p->pdc == NULL) {
		return;
	}

	PPPiface = fsm_p->ppp_p->iface;

	FSM_LOG(fsm_p, "Open event");

	switch (fsm_p->state) {
	case fsmINITIAL:
		/*TLS*/
		fsm_p->state = fsmSTARTING;
		break;

	case fsmCLOSED:
		fsm_irc(fsm_p);
		(*fsm_p->pdc->starting)(fsm_p);
		fsm_configreq(fsm_p);
		fsm_p->state = fsmREQ_Sent;
		break;

	case fsmCLOSING:
		fsm_p->state = fsmSTOPPING;
		break;

	default:
		/* already open */
		break;
	};
}

/************************************************************************/
/* Administratively Close the link */
ENTRY void
fsm_close (struct fsm_s *fsm_p)
{
	if (fsm_p->pdc == NULL) {
		return;
	}

	PPPiface = fsm_p->ppp_p->iface;

	FSM_LOG(fsm_p, "Close event");

	switch (fsm_p->state) {
	case fsmSTARTING:
		fsm_p->state = fsmINITIAL;
		break;

	case fsmSTOPPED:
		fsm_p->state = fsmCLOSED;
		break;

	case fsmSTOPPING:
		fsm_p->state = fsmCLOSING;
		break;

	case fsmOPENED:
		(*fsm_p->pdc->closing)(fsm_p);
		/* fallthru */
	case fsmREQ_Sent:
	case fsmACK_Rcvd:
	case fsmACK_Sent:
		fsm_p->retry_request = fsm_p->try_terminate;
		fsm_termreq(fsm_p);
		fsm_p->state = fsmCLOSING;
		break;

	default:
		/* already closed */
		break;
	};
}

/************************************************************************/
/* Attach the fsm for this protocol
 * Called from protocol _attach
 */
ENTRY void
fsm_attach (struct fsm_s *fsm_p)
{
	struct timer *t = &(fsm_p->timer);

	PPP_DEBUG_ROUTINES("fsm_attach()");

	fsm_p->try_configure = fsm_p->pdc->try_configure;
	fsm_p->try_nak = fsm_p->pdc->try_nak;
	fsm_p->try_terminate = fsm_p->pdc->try_terminate;

        /* Initialize timer */
        t->func = (void (*)(void *))fsm_timeout;
        t->arg = (void *)fsm_p;
        set_timer(t, fsm_p->pdc->timeout);
}

/* Initialize the fsm for this protocol
 * Called from protocol _init
 */
ENTRY void
fsm_init (struct fsm_s *fsm_p)
{
	struct timer *t = &(fsm_p->timer);

	PPP_DEBUG_ROUTINES("fsm_init()");

	fsm_timer(fsm_p);
	stop_timer(t);
}

ENTRY void
fsm_free (struct fsm_s *fsm_p)
{
	if (fsm_p->pdc != NULL) {
		if (fsm_p->pdc->free != NULL)
			(*fsm_p->pdc->free)(fsm_p);

		free(fsm_p->pdv);
		free(fsm_p->local.want_pdv);
		free(fsm_p->local.work_pdv);
		free(fsm_p->remote.want_pdv);
		free(fsm_p->remote.work_pdv);
		fsm_p->pdc = NULL;
	}
}
