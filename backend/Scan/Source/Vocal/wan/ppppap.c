
/* ************************************************************************* */
/*
 *	ppppap.c
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
 *	This file contains the PPP PAP functions.
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

#include "net/net.h"
#include "sys/sys.h"
#include "dev/dev.h"

#include "ip/ip.h"

#include "wan/local.h"

#include "lansend/lansend.h"
#include "trace/trace.h"

static char far *papCodes[] = {
	NULLCHAR,
	"Auth Req",
	"Auth Ack",
	"Auth Nak"
};

static struct fsm_constant_s far pap_constants = {
	"Pap",
	PPP_PAP_PROTOCOL,
	0x000E,				/* codes 1-3 recognized */
	papCodes,

	Pap,
	PAP_REQ_TRY,
	PAP_FAIL_MAX,
	0,
	PAP_TIMEOUT * 1000L,

	0,			/* no options */

	pap_free,
	pap_down
};

/****************************************************************************/
/* "ppp <iface> pap" subcommands */
static const struct cmds far Papcmds[] = {
	{"message",		dopap_message,		0,	0,	  ""},
	{"Timeout",		doppp_timeout,		0,	0,	  "[secs]"},
	{"Try",			doppp_try,			0,	0,	  NULLCHAR},
	{"user",		dopap_user,			0,	0,	  "[user [password]|none]"},
	{NULLCHAR},
};

ENTRY int
doppp_pap (int argc, char *argv[], void *p)
{
	register struct iface *ifp = (struct iface *) p;
	register struct ppp_s *ppp_p = (struct ppp_s *) ifp->pppedv;

	return subcmd(Papcmds, argc, argv, &(ppp_p->fsm[Pap]));
}

/* Display last message received */
ENTRY int
dopap_message (int argc, char *argv[], void *p)
{
	register struct fsm_s *fsm_p = (struct fsm_s *) p;
	register struct pap_s *pap_p = (struct pap_s *) fsm_p->pdv;

	printf("%s\n",
		(pap_p->message == NULLCHAR) ? "None" : pap_p->message);
	return 0;
}

/* Set user/password */
ENTRY int
dopap_user (int argc, char *argv[], void *p)
{
	register struct fsm_s *fsm_p = (struct fsm_s *) p;
	register struct pap_s *pap_p = (struct pap_s *) fsm_p->pdv;

	if (argc < 2) {
		printf("%s\n",
			(pap_p->username == NULLCHAR) ? "None" : pap_p->username);
		return 0;
	}
	free(pap_p->username);
	pap_p->username = NULLCHAR;
	free(pap_p->password);
	pap_p->password = NULLCHAR;

	if (stricmp(argv[1],"none") != 0) {
		pap_p->username = strdup(argv[1]);
		if (argc > 2) {
			pap_p->password = strdup(argv[2]);
		} else {
			pap_pwdlookup(pap_p);
		}
	}
	return 0;
}

/****************************************************************************/
/* Check the account file for this user; get password */
LOCAL void
pap_pwdlookup (struct pap_s *pap_p)
{
	struct account *ap;

	if (pap_p->username == NULLCHAR)
		return;

	if ((ap = account_find (pap_p->username, NULLCHAR)) == NULLACCOUNT)
		return;

	/* Check permitted protocol for this account */
	if (stricmp (ap->protocol, "pap") != 0)
		return;

	/* Save the password from this account record */
	if (strlen(ap->password) != 0)
		pap_p->password = strdup(ap->password);
}

/*******************************************/
/* Verify user and password sent by peer */
LOCAL int
pap_verify (char *username, char *password)
{
	struct account *ap;

	ap = account_find (username, password);

	/* Check privs for this user */
	if (ap == NULLACCOUNT) {
		trace_log(PPPiface,"PAP: username/password incorrect or not found: %s",
				username);
		return -1;
	}

	if (stricmp (ap->protocol, "pap") != 0) {
		trace_log(PPPiface,"PAP: no permission for PPP access: %s",
				username);
		return -1;
	}
	return 0;
}

/****************************************************************************/
/* Build a request to send to authenticator */
LOCAL struct mbuf *
pap_makerequest (struct fsm_s *fsm_p)
{
	struct pap_s *pap_p = (struct pap_s *) fsm_p->pdv;
	struct mbuf *rbp = NULLBUF;
	register char *cp;
	int length;
	char *unp, *pwp;

	PPP_DEBUG_ROUTINES("pap_makerequest()");

	/* Get the user name and password */
	unp = pap_p->username;
	pwp = pap_p->password;

	if ((unp == NULLCHAR) || (pwp == NULLCHAR)) {
		FSM_LOG(fsm_p, "NULL username or password");
		return NULLBUF;
	}

#ifdef DO_LANSEND_PPP_DEBUG_OPTIONS
	if (PPPiface->trace & PPP_DEBUG_OPTIONS)
		trace_log(PPPiface, "    making user id %s", unp);
#endif /* DO_LANSEND_PPP_DEBUG_OPTIONS */

	/* Get buffer for authenticate request packet */
	length = 2 + strlen(unp) + strlen(pwp);
	if ((rbp = alloc_ibuf(length,0)) == NULLBUF)
		return NULLBUF;
	rbp->cnt += length;

	/* Load username and password */
	cp = rbp->data;

	length = strlen(unp);
	*cp++ = (char)length;
	if (length > 0) {
		memcpy(cp, unp, length);
		cp += length;
	}

	length = strlen(pwp);
	*cp++ = (char)length;
	if (length > 0) {
		memcpy(cp, pwp, length);
	}
	return(rbp);
}

/*******************************************/
/* Send a Authenticate Request */
LOCAL int
pap_sendrequest (struct fsm_s *fsm_p)
{
	struct mbuf *bp;
	int ret;

	PPP_DEBUG_ROUTINES("pap_sendrequest()");

	if (fsm_p->retry_request <= 0) {
		return -1;
	}

	fsm_p->retry_request--;
	fsm_timer(fsm_p);

	bp = pap_makerequest(fsm_p);
	ret = fsm_send(fsm_p, CONFIG_REQ, 0, bp);
	return ret;
}

/****************************************************************************/
/* abandon PAP attempt; shutdown LCP layer */
LOCAL void
pap_shutdown (struct fsm_s *fsm_p)
{
	struct ppp_s *ppp_p = fsm_p->ppp_p;

	PPP_DEBUG_ROUTINES("pap_shutdown()");

	FSM_LOG(fsm_p, "Failed; close connection");

	fsm_close(&(ppp_p->fsm[Lcp]));
	fsm_open(&(ppp_p->fsm[Lcp]));
}

/* Authentication complete */
LOCAL void
pap_opening (struct fsm_s *fsm_p, int flag)
{
	register struct ppp_s *ppp_p = fsm_p->ppp_p;

	FSM_LOG(fsm_p, "Open");

	stop_timer(&(fsm_p->timer));

	if (!((fsm_p->flags &= ~flag) & (PPP_AP_LOCAL | PPP_AP_REMOTE))) {
		fsm_p->state = fsmOPENED;
	}
	ppp_p->flags &= ~flag;
	ppp_ready(ppp_p);
}

/****************************************************************************/
/* Check request from peer */
LOCAL int
pap_request (struct fsm_s *fsm_p, struct config_hdr *hdr, struct mbuf *data)
{
	struct mbuf *reply_bp;
	int result;
	char *message;
	int mess_length;
	char *username = NULLCHAR;
	int userlen;
	char *password = NULLCHAR;
	int passwordlen;

	PPP_DEBUG_ROUTINES("pap_request()");

	/* Extract userID/password */
	if ((userlen = pullchar(&data)) != -1) {
		register int i;
		register char *cp;

		cp = username = (char *) mallocw (userlen+1);
		for (i = userlen; i-- > 0;) {
			*cp++ = PULLCHAR(&data);
		}
		*cp = '\0';
	}

#ifdef DO_LANSEND_PPP_DEBUG_OPTIONS
	if (PPPiface->trace & PPP_DEBUG_OPTIONS)
		trace_log(PPPiface,"    checking user: %s", username);
#endif /* DO_LANSEND_PPP_DEBUG_OPTIONS */

	if ((passwordlen = pullchar(&data)) != -1) {
		register int i;
		register char *cp;

		cp = password = (char *) mallocw (passwordlen+1);
		for (i = passwordlen; i-- > 0;) {
			*cp++ = PULLCHAR(&data);
		}
		*cp = '\0';
	}

#ifdef DO_LANSEND_PPP_DEBUG_OPTIONS
	if (PPPiface->trace & PPP_DEBUG_OPTIONS)
		trace_log(PPPiface,"    checking password: %s", password);
#endif /* DO_LANSEND_PPP_DEBUG_OPTIONS */

	if (pap_verify(username,password) == 0) {
		free(fsm_p->ppp_p->peername);
		fsm_p->ppp_p->peername = strdup(username);
		result = CONFIG_ACK;
		message = " Welcome";
	} else {
		result = CONFIG_NAK;
		message = " Invalid username or password";
	}

	/* the space at the beginning of the message is crucial */
	/* it is replaced with the length of the message */
	mess_length = strlen(message);
	reply_bp = qdata(message,mess_length);
	reply_bp->data[0] = (char)(mess_length - 1);

	fsm_send(fsm_p, result, hdr->identifier, reply_bp);

	if (result == CONFIG_NAK) {
		if (fsm_p->retry_nak > 0) {
			fsm_p->retry_nak--;
		} else {
			pap_shutdown(fsm_p);
		}
	}
	free_p(data);
	free(username);
	free(password);
	return (result != CONFIG_ACK);
}

/* Check acknowledgement from authenticator */
LOCAL int
pap_check (struct fsm_s *fsm_p, struct config_hdr *hdr, struct mbuf *data)
{
	struct pap_s *pap_p = (struct pap_s *) fsm_p->pdv;
	char *message;
	int mess_length;
	int full_length;
	int length;

	PPP_DEBUG_ROUTINES("pap_check()");

	/* ID field must match last request we sent */
	if (hdr->identifier != fsm_p->lastid) {
		PPP_DEBUG_CHECKS("PAP: wrong ID");
		printf ("id mismatch hdrid=%d, lastid=%d\n",
			hdr->identifier, fsm_p->lastid);
		free_p(data);
		return -1;
	}

	/* Log ASCII message from authenticator, if any */
	if ((mess_length = pullchar(&data)) != -1) {
		message = (char *) mallocw (mess_length+1);
		full_length = len_p(data);
		length = dqdata(data, message, mess_length);
		message[length] = '\0';

		free(pap_p->message);
		pap_p->message = message;

#ifdef	DO_LANSEND_PPP_DEBUG_PACKET
		if (PPPiface->trace & PPP_DEBUG_PACKET) {
			trace_log(PPPiface,"PAP %s %s: %s",
				(hdr->code == CONFIG_ACK) ? "Ack" : "Nak",
				(length < mess_length) ? "Short"
				   : (mess_length < full_length) ? "Long"
					: "Valid",
				message);
		}
#endif
		return (length < mess_length  ||  mess_length < full_length);
	}
	free_p(data);
	PPP_DEBUG_CHECKS("PAP: missing message count");
	return -1;
}

/************************************************************************/
/*			E V E N T   P R O C E S S I N G			*/
/************************************************************************/

/* Process incoming packet */
ENTRY void
pap_proc (struct fsm_s *fsm_p, struct mbuf *bp)
{

	struct config_hdr hdr;

	PPPiface = fsm_p->ppp_p->iface;

	if (ntohcnf(&hdr, &bp) == -1)
		FSM_LOG(fsm_p, "short authentication packet");

#ifdef	DO_LANSEND_PPP_DEBUG_PACKET
	if (PPPiface->trace & PPP_DEBUG_PACKET)
		trace_log(PPPiface, "%s Recv,"
			"  option: %s, id: %d, len: %d",
			fsm_p->pdc->name,
			papCodes[hdr.code],
			hdr.identifier, hdr.length);
#endif /* DO_LANSEND_PPP_DEBUG_PACKET */
	hdr.length -= CONFIG_HDR_LEN;		 /* Length includes envelope */
	trim_mbuf(&bp, hdr.length);		 /* Trim off padding */

	switch (hdr.code) {
	case CONFIG_REQ:
		if (pap_request(fsm_p, &hdr, bp) == 0) {
			pap_opening(fsm_p, PPP_AP_LOCAL);
		}
		break;

	case CONFIG_ACK:
		if (pap_check(fsm_p, &hdr, bp) == 0) {

			pap_opening(fsm_p, PPP_AP_REMOTE);
		}
		break;

	case CONFIG_NAK:
		if (pap_check(fsm_p, &hdr, bp) == 0) {

			stop_timer(&(fsm_p->timer));

			if (pap_sendrequest(fsm_p) != 0) {
				FSM_LOG(fsm_p, "Request retry exceeded");
				pap_shutdown(fsm_p);
			}

		}
		break;

	default:
		trace_log(PPPiface, "PAP Unknown packet type: %d;"
			" dropping packet",
			hdr.code);
		free_p(bp);
		break;
	}
}

/* Timeout while waiting for reply from authenticator */
LOCAL void
pap_timeout (void *vp)
{
	struct fsm_s *fsm_p = (struct fsm_s *) vp;
	struct pap_s *pap_p = (struct pap_s *) fsm_p->pdv;

	PPPiface = fsm_p->ppp_p->iface;

	FSM_LOG(fsm_p, "Timeout");

	if (fsm_p->retry_request > 0) {
		free (pap_p->message);
		pap_p->message = strdup("Request timeout");

		pap_sendrequest(fsm_p);

	} else {
		free(pap_p->message);
		pap_p->message = strdup("Request retry exceeded");

		FSM_LOG(fsm_p, "Request retry exceeded");
		pap_shutdown(fsm_p);
	}
}

/************************************************************************/
/*			I N I T I A L I Z A T I O N			*/
/************************************************************************/

ENTRY void
pap_down (struct fsm_s *fsm_p)
{
	struct pap_s *pap_p = (struct pap_s *) fsm_p->pdv;

	if (pap_p == NULL) {
		return;
	}

	PPPiface = fsm_p->ppp_p->iface;

	FSM_LOG(fsm_p, "Down");

	fsm_p->flags = FALSE;
	fsm_p->retry_request = fsm_p->try_configure;
	fsm_p->retry_nak = fsm_p->try_nak;

	switch (fsm_p->state) {
	case fsmREQ_Sent:
		stop_timer(&(fsm_p->timer));

		/* fallthru */
	case fsmOPENED:
	case fsmSTOPPED:
		fsm_p->state = fsmCLOSED;
		break;

	case fsmCLOSED:
		/* Already closed; nothing to do */
		break;
	};
}

LOCAL void
pap_free (struct fsm_s *fsm_p)
{
	struct pap_s *pap_p = (struct pap_s *) fsm_p->pdv;

	free(pap_p->username);
	free(pap_p->password);
	free(pap_p->message);

}

/* Attach configuration structures */
ENTRY void
pap_attach (struct ppp_s *ppp_p)
{
	struct fsm_s *fsm_p = &(ppp_p->fsm[Pap]);

	PPPiface = ppp_p->iface;

	PPP_DEBUG_ROUTINES("pap_attach()");

	fsm_p->ppp_p = ppp_p;
	fsm_p->pdc = &pap_constants;
	fsm_p->pdv = callocw(1,sizeof(struct pap_s));

	fsm_attach(fsm_p);
	fsm_p->timer.func = pap_timeout;
}

/* Initialize configuration structure */
ENTRY void
pap_init (struct ppp_s *ppp_p)
{
	struct fsm_s *fsm_p = &(ppp_p->fsm[Pap]);

	PPPiface = ppp_p->iface;

	PPP_DEBUG_ROUTINES("pap_init()");

	fsm_p->state = fsmINITIAL;
	fsm_p->retry_request = fsm_p->try_configure;
	fsm_p->retry_nak = fsm_p->try_nak;

	fsm_init(fsm_p);
}

/* Expect authentication request from peer */
ENTRY int
pap_local (struct ppp_s *ppp_p)
{
	struct fsm_s *fsm_p = &(ppp_p->fsm[Pap]);

	PPPiface = ppp_p->iface;

	PPP_DEBUG_ROUTINES("pap_local()");

	fsm_p->state = fsmSTOPPED;
	fsm_p->flags |= PPP_AP_LOCAL;
	ppp_p->flags |= PPP_AP_LOCAL;
	fsm_p->retry_request = fsm_p->try_configure;
	return 0;
}

/* Send authentication request to peer */
ENTRY int
pap_remote (struct ppp_s *ppp_p)
{
	struct fsm_s *fsm_p = &(ppp_p->fsm[Pap]);

	PPPiface = ppp_p->iface;

	PPP_DEBUG_ROUTINES("pap_remote()");

	fsm_p->state = fsmREQ_Sent;
	fsm_p->flags |= PPP_AP_REMOTE;
	ppp_p->flags |= PPP_AP_REMOTE;

	pap_sendrequest(fsm_p);
	return 0;
}
