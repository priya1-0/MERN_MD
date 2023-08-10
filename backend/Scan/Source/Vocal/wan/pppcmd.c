
/* ************************************************************************* */
/*
 *	pppcmd.c
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
 *	This file contains the PPP user commands.
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

/* "ppp" subcommands */
static const struct cmds far Pppcmds[] = {
	{"ipcp",		doppp_ipcp,			0,	0,	NULLCHAR},
	{"lcp",			doppp_lcp,			0,	0,	NULLCHAR},
	{"pap",			doppp_pap,			0,	0,	NULLCHAR},
	{"chap",		doppp_chap,			0,	0,	NULLCHAR},
	{"Quick",		doppp_quick,		0,	0,	""},
	{"show",		doppp_show,			0,	0,	""},
	{NULLCHAR},
};

/* "ppp <iface> <ncp> try" subcommands */
static const struct cmds far PppTrycmds[] = {
	{"configure",	dotry_req,			0,	0,	"[count]"},
	{"failure",		dotry_nak,			0,	0,	"[count]"},
	{"terminate",	dotry_terminate,	0,	0,	"[count]"},
	{NULLCHAR},
};

static char far *PPPStatus[] = {
	"Physical Line Dead",
	"Establishment Phase",
	"Authentication Phase",
	"Network Protocol Phase",
	"Termination Phase"
};

static char far *NCPStatus[] = {
	"Initial",
	"Starting -- waiting for lower layer",
	"Closed",
	"Stopped -- waiting for peer to attempt open",
	"Closing -- terminate request sent to peer",
	"Stopping -- waiting for peer to terminate",
	"Sent configuration request",
	"Peer accepted our request; waiting for peer request",
	"We accepted peer request; waiting for reply to our request",
	"Opened"
};

/****************************************************************************/
/****************************************************************************/

ENTRY int
doppp_commands (int argc, char *argv[], void *p)
{
	return ifacecmd ((IFACECMD_EXIST | IFACECMD_SHOW | IFACECMD_ASYNC | IFACECMD_SYNC | IFACECMD_PPP | IFACECMD_DEVICE),
			Pppcmds, argc, argv, p);
}

LOCAL int
doppp_show (int argc, char *argv[], void *p)
{
	register struct iface *ifp;

	ifp = (struct iface *) p;
	if (ifp == NULLIF) {
		/* Display the active PPP interfaces */
		for (ifp = Ifaces; ifp != NULLIF; ifp = ifp->next) {
			if (ifp->iftype->ifType == IFT_PPP)
				ppp_show (ifp);
		}
		return 0;
	}
	/* Just the name, show the interface. */
	ppp_show(ifp);
	return 0;
}

/* Close connection on PPP interface */
ENTRY int
doppp_close (int argc, char *argv[], void *p)
{
	register struct fsm_s *fsm_p = p;

	fsm_close(fsm_p);
	return 0;
}

ENTRY int
doppp_open (int argc, char *argv[], void *p)
{
	register struct fsm_s *fsm_p = p;

	fsm_open(fsm_p);
	return 0;
}

ENTRY int
doppp_quick (int argc, char *argv[], void *p)
{
	register struct iface *ifp = p;
	register struct ppp_s *ppp_p = ifp->pppedv;
	struct fsm_side_s *lcp_local = &(ppp_p->fsm[Lcp].local);
	struct lcp_value_s *lcp_lwant = lcp_local->want_pdv;
	struct lcp_value_s *lcp_rwant = ppp_p->fsm[Lcp].remote.want_pdv;
	struct ipcp_value_s *ipcp_lwant = ppp_p->fsm[IPcp].local.want_pdv;

	if ((ifp->d_type == IFD_ASYNC) || (ifp->d_type == IFD_MDM)) {
		lcp_rwant->accm = 0L;
		lcp_lwant->accm = 0L;
		lcp_local->want |= LCP_N_ACCM | LCP_N_ACFC | LCP_N_PFC;
	}

	lcp_lwant->magic_number = (sint31)&lcp_lwant->magic_number
					+ time(NULL);
	lcp_local->want |= LCP_N_MAGIC;

	ipcp_lwant->compression = PPP_VJCH_PROTOCOL;
	ipcp_lwant->slots = 16;
	ipcp_lwant->slot_compress = 1;
	ppp_p->fsm[IPcp].local.want |= IPCP_N_COMPRESS;

	return 0;
}

/****************************************************************************/

ENTRY void
ppp_show (struct iface *ifp)
{
	register struct ppp_s *ppp_p = ifp->pppedv;

	if (ppp_p == NULL)
		return;

	genstat(ppp_p);

	if (ppp_p->fsm[Lcp].pdc != NULL)
		lcpstat(&(ppp_p->fsm[Lcp]));

	if (ppp_p->fsm[Pap].pdc != NULL)
		papstat(&(ppp_p->fsm[Pap]));

	if (ppp_p->fsm[CHap].pdc != NULL)
		chapstat(&(ppp_p->fsm[CHap]));

	if (ppp_p->fsm[IPcp].pdc != NULL)
		ipcpstat(&(ppp_p->fsm[IPcp]));

}

ENTRY void
genstat (struct ppp_s *ppp_p)
{
	printf("%s", PPPStatus[ppp_p->phase]);

	if (ppp_p->phase == pppNETWORK) {
		printf("\t(open for %s)",
			tformat(secclock() - ppp_p->upsince));
	}
	printf("\n");

	printf("   In:  %10lu Flags,%10lu Lcp,    %10lu Pap,%10lu IPcp,\n"
	       "        %10lu IPXcp,%10lu Unknown, %10lu FE, %10lu CSE\n",
		(long) ppp_p->InOpenFlag,
		(long) ppp_p->InNCP[Lcp],
		(long) ppp_p->InNCP[Pap],
		(long) ppp_p->InNCP[IPcp],
		(long) 0,
		(long) ppp_p->InUnknown,
		(long) ppp_p->InFrame,
		(long) ppp_p->InChecksum);
	printf("   Out: %10lu Flags,%10lu Lcp,    %10lu Pap,%10lu IPcp,\n"
	       "        %10lu IPXcp\n",
		(long) ppp_p->OutOpenFlag,
		(long) ppp_p->OutNCP[Lcp],
		(long) ppp_p->OutNCP[Pap],
		(long) ppp_p->OutNCP[IPcp],
		(long) 0);
}

LOCAL int
spot (struct fsm_side_s *side_p, negotiate_t mask)
{
	negotiate_t work = side_p->work;
	negotiate_t want = side_p->want;
	negotiate_t will = side_p->will;
	char blot = ' ';
	int result = (work & mask);

	if (!(will & mask)) {
		blot = '*';
	} else if ((want ^ work) & mask) {
		blot = (result ? '+' : '-');
	}
	printf("%c", blot);
	return result;
}

LOCAL void
lcpstat (struct fsm_s *fsm_p)
{
	struct lcp_value_s *lworkp = fsm_p->local.work_pdv;
	struct lcp_value_s *rworkp = fsm_p->remote.work_pdv;

	printf("LCP %s\n",
		NCPStatus[fsm_p->state]);

	printf("\t\t MRU\t ACCM\t\t AP\t PFC  ACFC Magic\n");

	printf("\tLocal:\t");

	spot(&(fsm_p->local), LCP_N_MRU);
	printf("%4d\t", lworkp->mru);

	spot(&(fsm_p->local), LCP_N_ACCM);
	printf("0x%08lx\t", (long) lworkp->accm);

	if (spot(&(fsm_p->local), LCP_N_AP)) {
		switch (lworkp->authentication) {
		case PPP_PAP_PROTOCOL:
			printf("Pap\t");
			break;
		default:
			printf("0x%04x\t", lworkp->authentication);
			break;
		};
	} else {
		printf("None\t");
	}

	printf(spot(&(fsm_p->local), LCP_N_PFC)
		 ? "Yes " : "No  ");
	printf(spot(&(fsm_p->local), LCP_N_ACFC)
		 ? "Yes " : "No  ");

	spot(&(fsm_p->local), LCP_N_MAGIC);
	if (lworkp->magic_number != 0L) {
		printf("0x%08lx\n", (long) lworkp->magic_number);
	} else {
		printf("unused\n");
	}

	printf("\tRemote:\t");

	spot(&(fsm_p->remote), LCP_N_MRU);
	printf("%4d\t", rworkp->mru);

	spot(&(fsm_p->remote), LCP_N_ACCM);
	printf("0x%08lx\t", (long) rworkp->accm);

	if (spot(&(fsm_p->remote), LCP_N_AP)) {
		switch (rworkp->authentication) {
		case PPP_PAP_PROTOCOL:
			printf("Pap\t");
			break;
		default:
			printf("0x%04x\t", rworkp->authentication);
			break;
		};
	} else {
		printf("None\t");
	}

	printf(spot(&(fsm_p->remote), LCP_N_PFC)
		 ? "Yes " : "No  ");
	printf(spot(&(fsm_p->remote), LCP_N_ACFC)
		 ? "Yes " : "No  ");

	spot(&(fsm_p->remote), LCP_N_MAGIC);
	if (rworkp->magic_number != 0L) {
		printf("0x%08lx\n", (long) rworkp->magic_number);
	} else {
		printf("unused\n");
	}
}

LOCAL void
papstat (struct fsm_s *fsm_p)
{
	struct pap_s *pap_p = fsm_p->pdv;

	if (fsm_p->state != fsmINITIAL) {
		printf("PAP %s\n",
			NCPStatus[fsm_p->state]);

		printf("\tMessage: '%s'\n", (pap_p->message == NULL) ?
			"none" : pap_p->message);
	}
}

LOCAL void
chapstat (struct fsm_s *fsm_p)
{
	struct chap_s *chap_p = fsm_p->pdv;

	if (fsm_p->state != fsmINITIAL) {
		printf("CHAP %s\n",
			NCPStatus[fsm_p->state]);

		printf("\tMessage: '%s'\n", (chap_p->message == NULL) ?
			"none" : chap_p->message);
	}
}

LOCAL void
ipcpstat (struct fsm_s *fsm_p)
{
	struct ipcp_pdv_s *ipcp_p = fsm_p->pdv;
	negotiate_t localwork = fsm_p->local.work;
	negotiate_t remotework = fsm_p->remote.work;
	struct ipcp_value_s *lworkp = fsm_p->local.work_pdv;
	struct ipcp_value_s *rworkp = fsm_p->remote.work_pdv;

	printf("IPCP %s\n",
		NCPStatus[fsm_p->state]);
	printf("\tlocal IP address: %s",
		inet_ntoa(lworkp->address));
	printf("  remote IP address: %s\n",
		inet_ntoa(rworkp->address));

	if (localwork & IPCP_N_COMPRESS) {
		printf("    In\tTCP header compression enabled:"
			" slots = %d, flag = 0x%02x\n",
			lworkp->slots,
			lworkp->slot_compress);
		slhc_i_status(ipcp_p->slhcp);
	}

	if (remotework & IPCP_N_COMPRESS) {
		printf("    Out\tTCP header compression enabled:"
			" slots = %d, flag = 0x%02x\n",
			rworkp->slots,
			rworkp->slot_compress);
		slhc_o_status(ipcp_p->slhcp);
	}
}

/****************************************************************************/
/* Set timeout interval when waiting for response from remote peer */
ENTRY int
doppp_timeout (int argc, char *argv[], void *p)
{
	struct fsm_s *fsm_p = p;
	struct timer *t = &(fsm_p->timer);

	return chg_timer (t, "Timeout value (secs)", argc, argv);
}

ENTRY int
doppp_try (int argc, char *argv[], void *p)
{
	return subcmd(PppTrycmds, argc, argv, p);
}

LOCAL int
dotry_nak (int argc, char *argv[], void *p)
{
	struct fsm_s *fsm_p = p;

	return chg_int8u (&fsm_p->try_nak, "NAK retry count", argc, argv);
}

LOCAL int
dotry_req (int argc, char *argv[], void *p)
{
	struct fsm_s *fsm_p = p;

	return chg_int8u (&fsm_p->try_configure, "Configuration retry count", argc, argv);
}

LOCAL int
dotry_terminate (int argc, char *argv[], void *p)
{
	struct fsm_s *fsm_p = p;

	return chg_int8u (&fsm_p->try_terminate, "Termination retry count", argc, argv);
}
