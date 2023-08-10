
/* ************************************************************************* */
/*
 *	pppchap.c
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
 *	This file contains the PPP CHAP functions.
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
#include "crypto/md5c.h"

#include "net/net.h"
#include "sys/sys.h"
#include "dev/dev.h"

#include "ip/ip.h"

#include "wan/local.h"

#include "lansend/lansend.h"
#include "trace/trace.h"

static char far *chapCodes[] = {
	NULLCHAR,
	"Challenge",
	"Response",
	"Success",
	"Failure"
};

static struct fsm_constant_s far chap_constants = {
	"CHap",
	PPP_CHAP_PROTOCOL,
	0x001E, 			/* codes 1-4 recognized */
	chapCodes,

	CHap,
	CHAP_RESP_TRY,
	CHAP_FAIL_MAX,
	0,
	CHAP_TIMEOUT * 1000L,

	0,			/* no options */

	chap_free,
	chap_down
};

/****************************************************************************/
/* "ppp <iface> chap" subcommands */
static const struct cmds far CHapcmds[] = {
	{"host",		dochap_host,		0,	0,	"[name|none]"},
	{"message",		dochap_message,		0,	0,	""},
	{"Timeout",		doppp_timeout,		0,	0,	"[secs]"},
	{"Try",			doppp_try,			0,	0,	NULLCHAR},
	{"user",		dochap_user,		0,	0,	"[user [password]|none]"},
	{NULLCHAR},
};

ENTRY int
doppp_chap(int argc, char *argv[], void *p)
{
	register struct iface *ifp = (struct iface *) p;
	register struct ppp_s *ppp_p = (struct ppp_s *) ifp->pppedv;

	return subcmd(CHapcmds, argc, argv, &(ppp_p->fsm[CHap]));
}

/* Set host */
ENTRY int
dochap_host (int argc, char *argv[], void *p)
{
	register struct fsm_s *fsm_p = (struct fsm_s *) p;
	register struct chap_s *chap_p = (struct chap_s *) fsm_p->pdv;

	if (argc < 2) {
		printf("%s\n",
			(chap_p->hostname == NULLCHAR) ? "None" : chap_p->hostname);
		return 0;
	}
	free(chap_p->hostname);
	chap_p->hostname = NULLCHAR;

	if (stricmp(argv[1],"none") != 0) {
		chap_p->hostname = strdup(argv[1]);
	}
	return 0;
}

/* Display last message received */
ENTRY int
dochap_message (int argc, char *argv[], void *p)
{
	register struct fsm_s *fsm_p = (struct fsm_s *) p;
	register struct chap_s *chap_p = (struct chap_s *) fsm_p->pdv;

	printf("%s\n",
		(chap_p->message == NULLCHAR) ? "None" : chap_p->message);
	return 0;
}

/* Set user/secret */
ENTRY int
dochap_user (int argc, char *argv[], void *p)
{
	register struct fsm_s *fsm_p = (struct fsm_s *) p;
	register struct chap_s *chap_p = (struct chap_s *) fsm_p->pdv;

	if (argc < 2) {
		printf("%s\n",
			(chap_p->username == NULLCHAR) ? "None" : chap_p->username);
		return 0;
	}
	free(chap_p->username);
	chap_p->username = NULLCHAR;
	free(chap_p->secret);
	chap_p->secret = NULLCHAR;

	if (stricmp(argv[1],"none") != 0) {
		chap_p->username = strdup(argv[1]);
		if (argc > 2) {
			chap_p->secret = strdup(argv[2]);
		} else {
			chap_lookup(chap_p->username, &(chap_p->secret));
		}
	}
	return 0;
}

/****************************************************************************/
/* Check the FTP userfile for this user; get secret if available */
LOCAL int
chap_lookup (char *username, char **result)
{
	struct account *ap;

	if (username == NULLCHAR)
		return -1;

	if ((ap = account_find (username, NULLCHAR)) == NULLACCOUNT)
		return -1;

	/* Check permitted protocol for this account */
	if (stricmp (ap->protocol, "chap") != 0)
		return -1;

	/* Save the password from this account record */
	if (strlen(ap->password) != 0)
		*result = strdup(ap->password);

	return PPP_ACCESS_PRIV;
}

/*******************************************/
/* Verify user and secret sent by peer */
LOCAL int
chap_verify (struct chap_s *chap_p, struct config_hdr *hdr, struct mbuf **bpp, char **username)
{
	int privs;
	int userlength;
	char *secret = NULLCHAR;
	int secretlength;
	char *response = NULLCHAR;
	int responselength;
	char *message;
	int length;
	char *cp;
	MD5_CTX context;
	char expected[CHAP_MD5_SIZE];
	int result;

	/* Extract response value */
	if ((responselength = pullchar(bpp)) != -1) {
		register int i;
		register char *cp;

		cp = response = (char *) mallocw (responselength+1);
		for (i = responselength; i-- > 0;) {
			*cp++ = PULLCHAR(bpp);
		}
	}

	if (responselength != CHAP_MD5_SIZE) {
		trace_log(PPPiface,"CHAP: wrong digest size: %d",
				responselength);
		free(response);
		return -1;
	}

	/* Extract username */
	if ((userlength = hdr->length - responselength - 1) > 0) {
		register int i;
		register char *cp;

		cp = *username = (char *) mallocw (userlength+1);
		for (i = userlength; i-- > 0;) {
			*cp++ = PULLCHAR(bpp);
		}
		*cp = '\0';
	}

#ifdef DO_LANSEND_PPP_DEBUG_OPTIONS
	if (PPPiface->trace & PPP_DEBUG_OPTIONS)
		trace_log(PPPiface,"    checking user: %s", *username);
#endif /* DO_LANSEND_PPP_DEBUG_OPTIONS */

	/* lookup username */
	privs = chap_lookup(*username, &secret);

	/* Check privs for this user */
	if (privs == -1) {
		trace_log(PPPiface,"CHAP: name/secret incorrect or not found: %s",
				*username);
		free(response);
		free(secret);
		return -1;
	}

	if ((privs & PPP_ACCESS_PRIV) == 0) {
		trace_log(PPPiface,"CHAP: no permission for PPP access: %s",
				*username);
		free(response);
		free(secret);
		return -1;
	}

	/* Build message for digest */
	length = chap_p->out_bp->data[0];
	secretlength = strlen(secret);
	cp = message = (char *) mallocw (1 + length + secretlength);

	*cp++ = hdr->identifier;

	if (secretlength > 0) {
		memcpy(cp, chap_p->secret, secretlength);
		cp += secretlength;
	}

	if (length > 0) {
		memcpy(cp, chap_p->out_bp->data + 1, length);
	}

	MD5Init(&context);
	MD5Update(&context, (uint8 *)message, 1 + length + secretlength);
	free(message);

	/* Compare response */
	MD5Final((uint8 *)expected, &context);

	result = memcmp(response, expected, CHAP_MD5_SIZE);

	if (result != 0)
		trace_log(PPPiface, "MD5 compare failed");
	free(response);
	free(secret);
	return result;
}

/****************************************************************************/
/* Build a request to send to authenticator */
LOCAL struct mbuf *
chap_makeresponse (struct fsm_s *fsm_p)
{
	struct chap_s *chap_p = (struct chap_s *) fsm_p->pdv;
	struct mbuf *rbp = NULLBUF;
	register char *cp;
	MD5_CTX context;
	char *message;
	int length, secretlength;
	char *unp, *pwp;

	PPP_DEBUG_ROUTINES("chap_makeresponse()");

	/* Get the user name and password */
	unp = chap_p->username;
	pwp = chap_p->secret;

	if ((unp == NULLCHAR) || (pwp == NULLCHAR)) {
		FSM_LOG(fsm_p, "NULL username or secret");
		return NULLBUF;
	}

#ifdef DO_LANSEND_PPP_DEBUG_OPTIONS
	if (PPPiface->trace & PPP_DEBUG_OPTIONS)
		trace_log(PPPiface, "    making user id %s", unp);
#endif /* DO_LANSEND_PPP_DEBUG_OPTIONS */

	/* Get buffer for response packet */
	length = 1 + CHAP_MD5_SIZE + strlen(unp);
	if ((rbp = alloc_ibuf(length,0)) == NULLBUF)
		return NULLBUF;
	rbp->cnt += length;

	/* Build message for digest */
	length = chap_p->in_bp->data[0];
	secretlength = strlen(pwp);
	cp = message = (char *) mallocw (1 + length + secretlength);

	*cp++ = chap_p->in_id;

	if (secretlength > 0) {
		memcpy(cp, pwp, secretlength);
		cp += secretlength;
	}

	if (length > 0) {
		memcpy(cp, chap_p->in_bp->data + 1, length);
	}

	MD5Init(&context);
	MD5Update(&context, (uint8 *)message, 1 + length + secretlength);
	free(message);

	/* Build response */
	cp = rbp->data;
	*cp++ = CHAP_MD5_SIZE;

	MD5Final((uint8 *)cp, &context);
	cp += CHAP_MD5_SIZE;

	if ((length = strlen(unp)) > 0) {
		memcpy(cp, unp, length);
	}
	return(rbp);
}

/*******************************************/
/* Send a Response */
LOCAL int
chap_sendresponse (struct fsm_s *fsm_p)
{
	struct chap_s *chap_p = (struct chap_s *) fsm_p->pdv;
	struct mbuf *bp;
	int ret;

	PPP_DEBUG_ROUTINES("chap_sendresponse()");

	if (fsm_p->retry_request <= 0) {
		return -1;
	}

	fsm_p->retry_request--;
	fsm_timer(fsm_p);

	bp = chap_makeresponse(fsm_p);
	ret = fsm_send(fsm_p, CHAP_RESPONSE, chap_p->in_id, bp);
	return ret;
}

/****************************************************************************/
/* abandon CHAP attempt; shutdown LCP layer */
LOCAL void
chap_shutdown (struct fsm_s *fsm_p)
{
	struct ppp_s *ppp_p = fsm_p->ppp_p;

	PPP_DEBUG_ROUTINES("chap_shutdown()");

	FSM_LOG(fsm_p, "Failed; close connection");

	fsm_close(&(ppp_p->fsm[Lcp]));
	fsm_open(&(ppp_p->fsm[Lcp]));
}

/* Authentication complete */
LOCAL void
chap_opening (struct fsm_s *fsm_p, int flag)
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
chap_response (struct fsm_s *fsm_p, struct config_hdr *hdr, struct mbuf *bp)
{
	struct chap_s *chap_p = (struct chap_s *) fsm_p->pdv;
	struct mbuf *reply_bp;
	char *message;
	int messagelength;
	char *username = NULLCHAR;
	int result;

	PPP_DEBUG_ROUTINES("chap_response()");

	/* ID field must match last challenge we sent */
	if (hdr->identifier != fsm_p->lastid) {
		PPP_DEBUG_CHECKS("CHAP: wrong ID");

		free_p(bp);
		return -1;
	}

	/* Ensure we've sent a challenge */
	if (chap_p->out_bp == NULLBUF) {
		PPP_DEBUG_CHECKS("CHAP: missing challenge");
		free_p(bp);
		return -1;
	}

	if (chap_verify(chap_p, hdr, &bp, &username) == 0) {
		free(fsm_p->ppp_p->peername);
		fsm_p->ppp_p->peername = strdup(username);
		result = CHAP_SUCCESS;
		message = "Welcome";
	} else {
		result = CHAP_FAILURE;
		message = "Invalid response";
	}

	/* no space at the beginning of the message */
	messagelength = strlen(message);
	reply_bp = qdata(message,messagelength);

	fsm_send(fsm_p, result, hdr->identifier, reply_bp);

	if (result == CHAP_FAILURE) {
		chap_shutdown(fsm_p);
	}
	free_p(bp);
	free(username);
	return (result != CHAP_SUCCESS);
}

/* Check acknowledgement from authenticator */
LOCAL int
chap_check (struct fsm_s *fsm_p, struct config_hdr *hdr, struct mbuf *bp)
{
	struct chap_s *chap_p = (struct chap_s *) fsm_p->pdv;
	char *message;
	int messagelength;
	int full_length;
	int length;

	PPP_DEBUG_ROUTINES("chap_check()");

	/* ID field must match last response we sent */
	if (hdr->identifier != chap_p->in_id) {
		PPP_DEBUG_CHECKS("CHAP: wrong ID");

		free_p(bp);
		return -1;
	}

	/* Log ASCII message from authenticator, if any */
	if ((messagelength = hdr->length) > 0) {
		message = (char *) mallocw (messagelength+1);
		full_length = len_p(bp);
		length = dqdata(bp, message, messagelength);
		message[length] = '\0';

		if (chap_p->message == NULLCHAR
		  || strcmp(message,chap_p->message) != 0)
			fsm_p->flags |= CHAP_SHOW_MESSAGE;

		free(chap_p->message);
		chap_p->message = message;

#ifdef	DO_LANSEND_PPP_DEBUG_PACKET
		if (PPPiface->trace & PPP_DEBUG_PACKET) {
			trace_log(PPPiface,"CHAP %s %s: %s",
				(hdr->code == CHAP_SUCCESS) ? "Success" : "Failure",
				(length < messagelength) ? "Short"
				   : (messagelength < full_length) ? "Long"
					: "Valid",
				message);
		}
#endif /* DO_LANSEND_PPP_DEBUG_PACKET */
		return (length < messagelength	||  messagelength < full_length);
	}

#ifdef	DO_LANSEND_PPP_DEBUG_PACKET
	if (PPPiface->trace & PPP_DEBUG_PACKET) {
		trace_log(PPPiface,"CHAP %s valid: no message",
			(hdr->code == CHAP_SUCCESS) ? "Success" : "Failure");
	}
#endif /* DO_LANSEND_PPP_DEBUG_PACKET */
	free_p(bp);
	return 0;
}

/************************************************************************/
/*			E V E N T   P R O C E S S I N G			*/
/************************************************************************/

/* Process incoming packet */
ENTRY void
chap_proc (struct fsm_s *fsm_p, struct mbuf *bp)
{
	struct chap_s *chap_p = (struct chap_s *) fsm_p->pdv;
	struct config_hdr hdr;

	PPPiface = fsm_p->ppp_p->iface;

	if (ntohcnf(&hdr, &bp) == -1)
		FSM_LOG(fsm_p, "short authentication packet");

#ifdef	DO_LANSEND_PPP_DEBUG_PACKET
	if (PPPiface->trace & PPP_DEBUG_PACKET)
		trace_log(PPPiface, "%s Recv,"
			"  option: %s, id: %d, len: %d",
			fsm_p->pdc->name,
			chapCodes[hdr.code],
			hdr.identifier, hdr.length);
#endif

	hdr.length -= CONFIG_HDR_LEN;		/* Length includes envelope */
	trim_mbuf(&bp, hdr.length);		/* Trim off padding */

	switch (hdr.code) {
	case CHAP_CHALLENGE:
		free_p(chap_p->in_bp);
		chap_p->in_bp = bp;
		chap_p->in_id = hdr.identifier;
		fsm_p->retry_request = fsm_p->try_configure;

		chap_sendresponse(fsm_p);

		break;

	case CHAP_RESPONSE:
		if (chap_response(fsm_p, &hdr, bp) == 0) {
			chap_opening(fsm_p, PPP_AP_LOCAL);
		}
		break;

	case CHAP_SUCCESS:
		if (chap_check(fsm_p, &hdr, bp) == 0) {
			chap_opening(fsm_p, PPP_AP_REMOTE);
			free_p(chap_p->in_bp);
			chap_p->in_bp = NULLBUF;
		}
		break;

	case CHAP_FAILURE:
		if (chap_check(fsm_p, &hdr, bp) == 0) {

			stop_timer(&(fsm_p->timer));
			free_p(chap_p->in_bp);
			chap_p->in_bp = NULLBUF;
		}
		break;

	default:
		trace_log(PPPiface, "CHAP Unknown packet type: %d;"
			" dropping packet",
			hdr.code);
		free_p(bp);
		break;
	}
}

/* Timeout while waiting for reply from authenticator */
static void
chap_timeout(void *vp)
{
	struct fsm_s *fsm_p = (struct fsm_s *)vp;
	struct chap_s *chap_p = (struct chap_s *) fsm_p->pdv;

	PPPiface = fsm_p->ppp_p->iface;

	FSM_LOG(fsm_p, "Timeout");

	if (fsm_p->retry_request > 0) {
		free (chap_p->message);
		chap_p->message = strdup("Response timeout");

		if (chap_p->in_bp != NULLBUF) {
			chap_sendresponse(fsm_p);
		}

	} else {
		free (chap_p->message);
		chap_p->message = strdup("Response retry exceeded");

		FSM_LOG(fsm_p, "Response retry exceeded");
		chap_shutdown(fsm_p);
	}
}

/****************************************************************************/
/* Send a challenge at irregular intervals
 */
LOCAL void
chap_challenger (int unused, void *v1, void *v2)
{
	struct fsm_s *fsm_p = (struct fsm_s *) v2;
	struct chap_s *chap_p = (struct chap_s *) fsm_p->pdv;
	char *hnp;

	while (!main_exit) {
		int host_len;
		int length;
		struct mbuf *bp;

		hnp = chap_p->hostname;
		if (hnp == NULLCHAR)
			hnp = Hostname;
		if (hnp == NULLCHAR)
			hnp = "<none>";

		host_len = strlen(hnp);
		length = host_len + sizeof(uint32) + sizeof(time_t) + 1;

		/* make challenge */
		if ((bp = alloc_mbuf(length)) != NULLBUF) {
			struct mbuf *new_bp = NULLBUF;
			char *cp = bp->data;

			*cp++ = (char)(sizeof(uint32) + sizeof(time_t));
			cp = put32(cp, time(NULL));
			cp = put32(cp, (uint32)chap_p);
			if (host_len > 0)
				memcpy(cp, hnp, host_len);
			bp->cnt = length;

			free_p(chap_p->out_bp);
			chap_p->out_bp = bp;
			dup_p(&new_bp, bp, 0, length);

			fsm_send(fsm_p, CHAP_CHALLENGE, 0, new_bp);
		}
		if (fsm_p->state == fsmOPENED) {
			pause(60000L + (msclock() & 0xffff));
		} else {
			pause(10000L);	/* !!! should have command to set */
		}
	}
}

/************************************************************************/
/*			I N I T I A L I Z A T I O N			*/
/************************************************************************/

ENTRY void
chap_down (struct fsm_s *fsm_p)
{
	struct chap_s *chap_p = (struct chap_s *) fsm_p->pdv;

	if (chap_p == NULL) {
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
		free_p(chap_p->out_bp);
		chap_p->out_bp = NULLBUF;
		killproc(chap_p->cpp);
		chap_p->cpp = NULLPROC;

		fsm_p->state = fsmCLOSED;
		break;

	case fsmCLOSED:
		/* Already closed; nothing to do */
		break;
	};
}

LOCAL void
chap_free (struct fsm_s *fsm_p)
{
	struct chap_s *chap_p = (struct chap_s *) fsm_p->pdv;

	free(chap_p->hostname);
	free(chap_p->username);
	free(chap_p->secret);
	free(chap_p->message);
	free_p(chap_p->out_bp);
	chap_p->out_bp = NULLBUF;
	free_p(chap_p->in_bp);
	chap_p->in_bp = NULLBUF;
	killproc(chap_p->cpp);
	chap_p->cpp = NULLPROC;

}

/* Attach configuration structures */
ENTRY void
chap_attach (struct ppp_s *ppp_p)
{
	struct fsm_s *fsm_p = &(ppp_p->fsm[CHap]);

	PPPiface = ppp_p->iface;

	PPP_DEBUG_ROUTINES("chap_attach()");

	fsm_p->ppp_p = ppp_p;
	fsm_p->pdc = &chap_constants;
	fsm_p->pdv = callocw(1,sizeof(struct chap_s));

	fsm_attach(fsm_p);
	fsm_p->timer.func = chap_timeout;
}

/* Initialize configuration structure */
ENTRY void
chap_init (struct ppp_s *ppp_p)
{
	struct fsm_s *fsm_p = &(ppp_p->fsm[CHap]);

	PPPiface = ppp_p->iface;

	PPP_DEBUG_ROUTINES("chap_init()");

	fsm_p->state = fsmINITIAL;
	fsm_p->retry_request = fsm_p->try_configure;
	fsm_p->retry_nak = fsm_p->try_nak;

	fsm_init(fsm_p);

}

/* Send authentication challenge to peer */
ENTRY int
chap_local (struct ppp_s *ppp_p)
{
	struct fsm_s *fsm_p = &(ppp_p->fsm[CHap]);
	struct chap_s *chap_p = (struct chap_s *) fsm_p->pdv;
	char *ifn;

	PPPiface = ppp_p->iface;

	PPP_DEBUG_ROUTINES("chap_local()");

	fsm_p->state = fsmREQ_Sent;
	fsm_p->flags |= PPP_AP_LOCAL;
	ppp_p->flags |= PPP_AP_LOCAL;
	fsm_p->retry_request = fsm_p->try_configure;

	/* build a process/session to send challenges */
	ifn = if_name(ppp_p->iface, " challenge");
	chap_p->cpp = newproc(ifn,
		512, chap_challenger, 0, ppp_p->iface, fsm_p, 0);
	free(ifn);
	return 0;
}

/* Expect authentication challenge from peer */
ENTRY int
chap_remote (struct ppp_s *ppp_p)
{
	struct fsm_s *fsm_p = &(ppp_p->fsm[CHap]);
	struct chap_s *chap_p = (struct chap_s *) fsm_p->pdv;

	PPPiface = ppp_p->iface;

	PPP_DEBUG_ROUTINES("chap_remote()");

	fsm_p->state = fsmSTOPPED;
	fsm_p->flags |= PPP_AP_REMOTE;
	ppp_p->flags |= PPP_AP_REMOTE;
	fsm_p->retry_request = fsm_p->try_configure;

	if (chap_p->in_bp != NULLBUF) {
		chap_sendresponse(fsm_p);
	}

	return 0;
}
