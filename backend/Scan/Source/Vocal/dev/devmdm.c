
#undef use_mdm_trace_proc

/* ************************************************************************* */
/*
 *	devmdm.c
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
 *	Module:		DEV
 *
 *  Device driver for VOCAL master/mdm code.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.2  2010/02/17 17:45:09  heiand1
 *	Revision History:	SCR 186240. Interrupt Protection for Modem Variables.
 *	Revision History:	
 *	Revision History:	Revision 1.1.24.1  2009/04/28 19:38:37  zhangn1
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
#include "dev/devmdm.h"
#include "dev/mdmcmd.h"

#include "ip/ip.h"

#include "dev/local.h"

#include "term/term.h"

#include "v24/v24.h"
#include "dteif/dteif.h"
#include "csc/parmd.h"
#include "dteif/macro.h"

#include "csc/csc.h"
#include "csc/dte.h"

static const char far ifDescr_mdm[] = "LANsEND Async master/mdm Device";

struct mdm *Mdm[MDM_MAX] = {
	NULLMDM
};

/* ************************************************************************* */

ENTRY void
mdm_init (void)
{
	int i;

	for (i = 0; i < MDM_MAX; i++) {
		Mdm[i] = NULLMDM;
	}
}

/* ************************************************************************* */
/*
 *  Function: mdm_ioctl
 *
 *  Perform control operation on an mdm device.
 *
 *  Parameters:
 *    "ifp" is a pointer to the interface structure for the device
 *    "cmd" is the ioctl command number
 *    "set" is a boolean for performing set operation
 *    "val" is the value to be used for a set operation
 *
 *  Returns: value of current setting
 *
 */
LOCAL sint31
mdm_ioctl (struct iface *ifp, int cmd, int set, sint31 val)
{
	struct mdm *mdmp = ifp->ddv;

	switch (cmd) {
	case PARAM_RSPEED:
	case PARAM_TSPEED:
	case PARAM_SPEED:
		/* report the highest normal speed, since we don't have a 'real' RS232 link */
		return 115200L;

	case PARAM_DTR:
		if (set) {
			int have = stat__dteif_v24_108;

			if (val && ! have) {
				/* set DTR */
				macro__dteif_dtr_on ();
				mdmp->dtrState = rs232UP;
				mdmp->dtrChanges++;
			}
			else if (!val && have) {
				/* clear DTR */
				macro__dteif_dtr_off ();
				mdmp->dtrState = rs232DOWN;
				mdmp->dtrChanges++;
			}
		}
		return stat__dteif_v24_108;

	case PARAM_RTS:
		if (set) {
			int have = stat__dteif_v24_133;

			if (val && ! have) {
				macro__dteif_rts_on ();
				mdmp->rtsState = rs232UP;
				mdmp->rtsChanges++;
			}
			else if (!val && have) {
				macro__dteif_rts_off ();
				mdmp->rtsState = rs232DOWN;
				mdmp->rtsChanges++;
			}
		}
		return stat__dteif_v24_133;

	case PARAM_DOWN:			/* Set the connection DOWN. */
		mdm_ioctl (ifp, PARAM_RTS, TRUE, FALSE);
		mdm_ioctl (ifp, PARAM_DTR, TRUE, FALSE);
		return FALSE;

	case PARAM_UP:				/* Set the connection UP. */
		mdm_ioctl (ifp, PARAM_DTR, TRUE, TRUE);
		mdm_ioctl (ifp, PARAM_RTS, TRUE, TRUE);
		return TRUE;

	case PARAM_BLIND:
		if (set) {

			if (val) {
				/* Assert that we are blind, we don't care about clear to send or
				 * carrier detect. */
				mdmp->ctsState = rs232NONE;
				mdmp->dcdState = rs232NONE;
				/* Can't see what we are doing, so pretend we're up. */
				if (ifp->iftype != NULLIFT && ifp->iftype->iostatus != NULLVFP) {
					(*ifp->iftype->iostatus) (ifp, PARAM_UP, 0L);
				}
			}
			else {
				/* I CAN SEE!!!  I CAN SEE!!! */
				mdmp->ctsState = (parm__dteif_v24_106 ? rs232UP : rs232DOWN);
				mdmp->dcdState = (parm__dteif_v24_109 ? rs232UP : rs232DOWN);
			}
		}

		return (mdmp->ctsState == rs232NONE && mdmp->dcdState == rs232NONE);
		/* Additional commands added to isolate driver */

	case PARAM_BREAK:
		return 0;

	case PARAM_TRIG:
		return 0;

	case PARAM_DCD:
		return ((mdmp->dcdState & ~rs232CHANGED) == rs232ON);

	case PARAM_DATA:
		return cnt_mdm (ifp);

	case PARAM_RXSIZE:
		return 0;

	case PARAM_IDLE:
		return mdmp->txbp == NULLBUF;

	case PARAM_STATUS:
		return 0;
	case PARAM_SAVE:
		return 0L;
	case PARAM_RESTORE:
		return 0L;

	case PARAM_MODE:
		if (set && val == PARAM_MODE_MDM) {
			stat__dteif_v24_108 = TRUE;
			stat__dteif_v24_133 = TRUE;
		}
		return PARAM_MODE_MDM;

	case PARAM_XOFF:
		return 0;				/* Not supported */

	case PARAM_RCHARLEN:
	case PARAM_TCHARLEN:
		return 8L;

	case PARAM_RSTOPBITS:
	case PARAM_TSTOPBITS:
		return 1;

	case PARAM_RPARITY:
	case PARAM_TPARITY:
		return PARAM_N_PARITY;
	}							/* SWITCH cmd */
	return -1;
}

/* ************************************************************************* */
/*
 *  Function: mdm_msint
 *
 *  Process modem status interrupt for the mdm device.  If the
 *  signals are changed, they are used to condition the line, otherwise
 *  they are ignored.
 *
 *  Parameters:
 *    "mdmp" is a pointer to the mdm device data structure
 *
 *  Returns: (none)
 *
 */
LOCAL void
mdm_msint (struct mdm *mdmp)
{
	if (parm__dteif_v24_106) {
		switch (mdmp->ctsState) {
		case rs232OFF:
		case rs232DOWN:
			mdmp->ctsState = rs232UP;
			mdmp->ctsChanges++;
			break;
		}
	}
	else {
		switch (mdmp->ctsState) {
		case rs232ON:
		case rs232UP:
			mdmp->ctsState = rs232DOWN;
			mdmp->ctsChanges++;
			break;
		}
	}

	if (parm__dteif_v24_109) {
		switch (mdmp->dcdState) {
		case rs232OFF:
		case rs232DOWN:
			mdmp->dcdState = rs232UP;
			mdmp->dcdChanges++;

			/* RLSD just went up */
			psignal (&(mdmp->dcdState), 1);
			break;
		}
	}
	else {
		switch (mdmp->dcdState) {
		case rs232ON:
		case rs232UP:
			mdmp->dcdState = rs232DOWN;
			mdmp->dcdChanges++;

			/* RLSD just went down */
			psignal (&(mdmp->dcdState), 1);
			break;
		}
	}

	if (parm__dteif_v24_125) {
		mdm_ioctl (mdmp->iface, PARAM_UP, TRUE, 0L);
	}
}

/* ************************************************************************* */
/*
 *  Function: mdm_send
 *
 *  Send a packet as an mdm stream.  The packet data is simply
 *  sent as a stream of characters.
 *
 *  Parameters:
 *    "ifp" is a pointer to the interface structure for the device
 *    "bp" is a pointer to a packet structure
 *
 *  Returns: 0 (success)
 *           1 (non - fatal error)
 *           -1 (fatal error, or process alerted from wait)
 *
 */
LOCAL int
mdm_send (struct iface *ifp, struct mbuf *bp)
{
	struct mdm *mdmp = ifp->ddv;

	int timeout_count;

	timeout_count = 0;

	mdmp->txbp = bp;	/* Indicates that a packet is currently being transmitted */

	/* Loop through all pending packet fragments */
	while (bp != NULLBUF) {

		/* Loop through all characters in packet */
		while (bp->cnt > 0) {
			/* If modem is asserting CTS, then send char */
			if (dte_tx_cnt < DTE_TX_BUFFER_SIZE) {
				sys_nested_interrupt_disable();
				dteif_rx (*bp->data++);
				sys_nested_interrupt_restore();
					
				bp->cnt--;
				mdmp->txchar++;
			}
			else {
				timeout_count++;
				if (timeout_count > 6000) {
					timeout_count = 0;
					dte_tx_cnt = 0;
					printf ("Kicking the MDM transmitter\n");
				} else {

				/* sleep a bit waiting for room in buffer */
					pause (20L);
				}
			}
		}
		mdmp->txbp = bp = free_mbuf(bp);	/* Free the fragment, get next fragment if any */
	}
	return 0;
}

/* ************************************************************************* */
/*
 *  Function: cnt_mdm
 *
 *  Report number of characters in receive buffer for an mdm device.
 *
 *  Parameters:
 *    "ifp" is a pointer to the interface structure for the device
 *
 *  Returns: number of characters in receive buffer
 *
 */
ENTRY uint16
cnt_mdm (struct iface *ifp)
{
	return dte_rx_avail ();
}

/* ************************************************************************* */
/*
 *  Function: get_mdm
 *
 *  Read character from an mdm device.
 *
 *  Parameters:
 *    "ifp" is a pointer to the interface structure for the device
 *
 *  Returns: 0 - 255 (character)
 *           -1 (alerted from wait)
 *
 */
LOCAL int
get_mdm (struct iface *ifp)
{
	struct mdm *mdmp = ifp->ddv;
	int c;

	while ((c = dteif_tx ()) == V24_DU__NO_DATA_AVAILABLE) {
		/* sleep a bit waiting for characters */
		pause (20L);
	}
	mdmp->rxchar++;
	c &= 0x00ff;
	return uchar (c);
}

/* ************************************************************************* */
/*
 *  Function: unget_mdm
 *
 *  Return character to buffer for an mdm device.
 *
 *  Parameters:
 *    "ifp" is a pointer to the interface structure for the device
 *    "c" is the character to be returned to the buffer
 *
 *  Returns: 0 (success)
 *           else (error)
 *
 */
LOCAL int
unget_mdm (struct iface *ifp, uint8 c)
{
	return -1;
}

/* ************************************************************************* */
/*
 *  Function: mdm_waitrlsd
 *
 *  Wait for a signal that RLSD (DCD) modem status has changed.  Upcalls
 *  the encapsulation iostatus routine when a state change has been detected.
 *
 *  Parameters:
 *    "ifp" is a pointer to the interface structure for the device
 *    "want" is the RS-232 condition to wait for
 *
 *  Returns: RLSD RS - 232 status
 *
 */
LOCAL int
mdm_waitrlsd (struct iface *ifp, int want)
{
	struct mdm *mdmp = ifp->ddv;
	int result;

	if (mdmp->dcdState == rs232NONE) {
		return rs232NONE;
	}

	switch (want) {
	case rs232NONE:
		/* Just return the current value */
		return (mdmp->dcdState);

	case rs232OFF:
	case rs232DOWN:
		switch (mdmp->dcdState) {
		case rs232OFF:
		case rs232DOWN:
			/* Already at requested value */
			return (want);
		}
		break;

	case rs232ON:
	case rs232UP:
		switch (mdmp->dcdState) {
		case rs232ON:
		case rs232UP:
			/* Already at requested value */
			return (want);
		}
		break;
	}

	/* Wait for UP/DOWN even if user asked for ON/OFF. */
	want |= rs232CHANGED;
	/* Wait for state change to requested value. */
	while (mdmp->dcdState != want
		&& mdmp->dcdState != rs232NONE) {
		mdm_msint (mdmp);
		pwait (NULL);
	}

	if (mdmp->dcdState == rs232UP)
		result = PARAM_UP;
	else						/* DOWN or NONE */
		result = PARAM_DOWN;

	/* Up call the status. */
	if (ifp->iftype != NULLIFT && ifp->iftype->iostatus != NULLVFP)
		(*ifp->iftype->iostatus) (ifp, result, 0L);

	return (mdmp->dcdState);
}

/* ************************************************************************* */
/*
 *  Process: mdm_monitor
 *
 *  Process to monitor RLSD and report status changes.  An upcall to the
 *  encapsulation iostatus routine is performed when the RLSD status changes.
 *
 *  Parameters:
 *    "dev" is the mdm device number
 *    "p1" is a void pointer to the interface structure for the device
 *    "p2" is an unused pointer
 *
 *  Started by: sync_attach
 *
 *  Terminated by: sync_stop
 *
 */
LOCAL void
mdm_monitor (int dev, void *p1, void *p2)
{
	struct iface *ifp = (struct iface *) p1;
	int saved = Mdm[dev]->dcdState;

	while (saved != rs232NONE) {
		/* Monitor RLSD signal, and report status changes.  This just keeps
		 * calling mdm_waitrlsd with the 'other' state.  This forces a call
		 * to iostatus every time that status changes. */
		saved = mdm_waitrlsd (ifp, saved ^ 0x01);
		if (saved != rs232UP) {
			if ((ifp->decideedv != NULL) &&
				(strcmp (ifp->iftype->name, "Dialer") != 0) &&
				 (strcmp (ifp->iftype->name, "Modem") != 0)) {
				setencap (ifp, "Dialer");
			}
			mdm_ioctl (ifp, PARAM_UP, TRUE, 0L);
		}
	}
	Mdm[dev]->devmonitor = NULL;
}

/* ************************************************************************* */
/*
 *  Timer Process: mdm_timeout
 *
 *  Used to monitor mdm inactivity and shut the device
 *  down when found to be idle.
 *
 *  Parameter:
 *    "p" is a void pointer to the interface structure for the device
 *
 *  Started by: mdm_attach and itself
 *
 *  Canceled by: mdm_stop
 *
 */
LOCAL void
mdm_timeout (void *p)
{
	struct iface *ifp = (struct iface *) p;
	struct mdm *mdmp = ifp->ddv;
	struct timer *tp = &mdmp->idle;
	uint32 idle_time, nap_time;
	uint32 idle;

	stop_timer (tp);
	nap_time = idle_time = dur_timer (tp);

	/* Check if idle time is to be stopped */
	if (idle_time != 0L) {
		/* Determine how long ago was it last active */
		idle = (secclock () - ifp->lastactive) * 1000L;

		/* Did we time out? */
		if (idle >= idle_time) {
			/* Up call the timeout and go back to sleep */
			if (ifp->iftype != NULLIFT && ifp->iftype->timeout != NULLVFP)
				(*ifp->iftype->timeout) (ifp);
		}
		else {
			/* Just sleep till next timeout */
			nap_time = idle_time - idle;
		}
	}
	set_timer (tp, nap_time);
	tp->func = mdm_timeout;
	tp->arg = (void *) ifp;
	start_timer (tp);
	set_timer (tp, idle_time);
}

/* ************************************************************************* */
/*
 *  Function: mdm_stop
 *
 *  Command to detach an mdm device.
 *
 *  Parameters:
 *    "ifp" is a pointer to the interface structure for the device
 *
 *  Returns: 0 (success always)
 *
 */
LOCAL int
mdm_stop (struct iface *ifp)
{
	register struct mdm *mdmp = ifp->ddv;

	if (mdmp->devmonitor != NULLPROC) {
		mdmp->dcdState = rs232NONE;
		killproc (mdmp->devmonitor);
		mdmp->devmonitor = NULLPROC;
	}

#ifdef use_mdm_trace_proc
	if (mdmp->trace_proc != NULLPROC) {
		killproc (mdmp->trace_proc);
		mdmp->trace_proc = NULLPROC;
	}
#endif /* use_mdm_trace_proc */

	stop_timer (&mdmp->idle);	/* Stop the idle timer, if running */

	/* Purge the receive data buffer */
	while (dteif_tx () != V24_DU__NO_DATA_AVAILABLE);

	Mdm[ifp->dev] = NULLMDM;

	free_p (mdmp->txbp);
	free (mdmp);
	return 0;
}

/* ************************************************************************* */
/*
 *  Function: mdm_attach
 *
 *  Command to attach an mdm device.
 *
 *  Parameters:
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "name" is a void pointer to the device name to be used
 *
 *  Command line: device <name> attach mdm [ppp|slip|modem|dialer]
 *
 *  Returns: 0 (success)
 *           else (error)
 *
 */
ENTRY int
mdm_attach (int argc, char *argv[], void *name)
{
	register struct iface *ifp;
	int dev;
	register struct mdm *mdmp;
	char **amp;
	char *ifn;

	dev = 0;

	if (Mdm[dev] != NULLMDM) {
		printf ("Unit already in use: %s\n", argv[1]);
		return -1;
	}

	/* Create interface structure and fill in details */
	if ((ifp = if_attach (name, 0)) == NULLIF) {
		printf ("Device name already in use: %s\n", name);  /* Should never happen */
		return -1;
	}
	ifp->ddv = mdmp = Mdm[dev] = callocw (1, sizeof (struct mdm));

	ifp->dev = dev;
	ifp->ifDescr = ifDescr_mdm;
	ifp->d_type = IFD_MDM;
	ifp->ioget = get_mdm;
	ifp->iounget = unget_mdm;

	ifp->iosend = mdm_send;
	ifp->ioctl = mdm_ioctl;
	ifp->iostop = mdm_stop;

	ifp->mtu = MXU_DEFAULT;

	/* Initialize mdm port "dev" */
	mdmp->iface = ifp;

#ifdef use_mdm_trace_proc
	mdmp->trace_proc = NULLPROC;
#endif /* use_mdm_trace_proc */

	/* Purge the receive data buffer */
	while (dteif_tx () != V24_DU__NO_DATA_AVAILABLE);

	if (argc < 2) {
		printf ("Protocol missing\n");
	}
	else {
		/* Look for the protocol in the table */
		for (amp = (char **) Asymode; *amp != NULLCHAR; amp++) {
			if (stricmp (argv[1], *amp) == 0) {
				if (setencap (ifp, *amp) != 0) {
					printf ("Protocol initialization failed: %s\n", argv[1]);
					if_detach (ifp);
					return -1;
				}
				break;
			}
		}
		if (*amp == NULLCHAR) {
			printf ("Protocol unavailable: %s\n", argv[1]);
			if_detach (ifp);
			return -1;
		}
	}

	/* set up to monitor line signals */
	mdmp->devmonitor = newproc (ifn = if_name (ifp, " monitor"),
		2048, mdm_monitor, ifp->dev, ifp, NULL, 0);
	free (ifn);

	/* set up to process idle timeout */
	set_timer (&mdmp->idle, MDM_TIMEOUT * 1000L);
	mdmp->idle.func = mdm_timeout;
	mdmp->idle.arg = (void *) ifp;
	start_timer (&mdmp->idle);

	pwait (NULL);				/* let hooks get set up */

	/* Exercise the line signals to see what effect they have.
	 * By default, tell the line to come up.
	 */
	mdm_ioctl (ifp, PARAM_UP, TRUE, 0L);

	if (ifp->iftype != NULLIFT && ifp->iftype->iostatus != NULLVFP) {
		/* if dtr is up, the line could be up from a previous program.
		 * if dcd is also up, the other end is probably there.
		 *(dsr is a pretty unreliable indicator.)
		 */

		if ((mdmp->dtrState & ~rs232CHANGED) == rs232ON
			&& (mdmp->dcdState & ~rs232CHANGED) == rs232ON) {

			(*ifp->iftype->iostatus) (ifp, PARAM_UP, 0L);
		}
	}

	return 0;
}
