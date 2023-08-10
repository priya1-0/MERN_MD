
/* ************************************************************************* */
/*
 *	pppfsm.h
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
 *	This file contains the PPP Finite State Machine (FSM) declarations.
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

#ifndef _WAN_PPPFSM_H
#define _WAN_PPPFSM_H

/* currently these bits are scattered about the iface trace word */
#define PPP_DEBUG_CHECKS(x)	if (PPPiface->trace & 0x0004) \
				trace_log (PPPiface, x);
#define PPP_DEBUG_ROUTINES(x)	if (PPPiface->trace & 0x0040) \
				trace_log (PPPiface, x);
#define PPP_DEBUG_PACKET	0x0400
#define PPP_DEBUG_FSA		0x0800
#define PPP_DEBUG_LQR		0x4000
#define PPP_DEBUG_OPTIONS	0x8000
#define PPP_DEBUG_BOOLEAN(x)	if (PPPiface->trace & PPP_DEBUG_OPTIONS) \
				trace_log (PPPiface, x);
#define PPP_DEBUG_VALUE(x,y)	if (PPPiface->trace & PPP_DEBUG_OPTIONS) \
				trace_log (PPPiface, x, y);
#define FSM_LOG(x,y)		fsm_log(x,y)

/* config packet header */
struct config_hdr {
	uint8 code;
#define CONFIG_REQ	 1
#define CONFIG_ACK	 2
#define CONFIG_NAK	 3
#define CONFIG_REJ	 4
#define TERM_REQ	 5
#define TERM_ACK	 6
#define CODE_REJ	 7
#define PROT_REJ	 8
#define ECHO_REQ	 9
#define ECHO_REPLY	10
#define DISCARD_REQ	11

	uint8 identifier;
	uint16 length;
};
#define CONFIG_HDR_LEN	4	/* Length of config packet header */

/* config option header */
struct option_hdr {
	uint8 type;		/* protocol dependant types */
	uint8 length;
};
#define OPTION_HDR_LEN	2	/* Length of option header */

/* Supported Configuration Protocol index */
enum {
	Lcp,
	Pap,
	CHap,
	IPcp,
	IPXcp,
	fsmi_Size
};

struct fsm_s;		/* forward declaration */

/* Protocol Constants needed by State Machine */
struct fsm_constant_s {
	char *name;			/* Name of protocol */
	uint16 protocol;		/* Protocol number */
	uint16 recognize;		/* Codes to use (bits)*/
	char **codes;			/* names of codes */

	uint8 fsmi;			/* Finite State Machine index */
	uint8 try_configure;		/* # tries for configure */
	uint8 try_nak;	 		/* # tries for nak substitutes */
	uint8 try_terminate;		/* # tries for terminate */
	uint32 timeout;			/* Time for timeouts (milliseconds)*/

	uint8 option_limit;		/* maximum option number */

	/* To free structure */
	void (*free)		(struct fsm_s *fsm_p);

	/* Lower Layer Down event */
	void (*down)		(struct fsm_s *fsm_p);

	/* This Layer Start: entering Starting */
	void (*starting)	(struct fsm_s *fsm_p);
	/* This Layer Up: entering Opened */
	void (*opening)		(struct fsm_s *fsm_p);
	/* This Layer Down: leaving Opened */
	void (*closing)		(struct fsm_s *fsm_p);
	/* This Layer Finish: entering Closed or Stopped */
	void (*stopping)	(struct fsm_s *fsm_p);

	void (*option)		(struct fsm_s *fsm_p, void *vp, struct mbuf **bpp, uint8 o_type);
	int (*check)		(struct fsm_s *fsm_p, struct option_hdr *ohp, struct mbuf **bpp, int request);
	int (*reject)		(struct fsm_s *fsm_p, struct option_hdr *ohp);
};

/* FSM states */
enum {
	fsmINITIAL,
	fsmSTARTING,
	fsmCLOSED,
	fsmSTOPPED,
	fsmCLOSING,
	fsmSTOPPING,
	fsmREQ_Sent,
	fsmACK_Rcvd,
	fsmACK_Sent,
	fsmOPENED,
	fsmState_Size
};

/*
 *	local.will:	Options to accept in a NAK from remote,
 *			which may be different from the desired value.
 *	local.want:	Options to request.
 *			Contains desired value.
 *			Only non - default options need to be negotiated.
 *			Initially, all are default.
 *	local.work:	Options currently being negotiated.
 *			Value is valid only when negotiate bit is set.
 *
 *	remote.will:	Options to accept in a REQ from remote,
 *			which may be different from the desired value.
 *	remote.want:	Options to suggest by NAK if not present in REQ.
 *			Contains desired value.
 *	remote.work:	Options currently being negotiated.
 *			Value is valid only when negotiate bit is set.
 */

typedef uint16 negotiate_t;

struct fsm_side_s {
	negotiate_t will;
	negotiate_t want;
	void  *want_pdv;
	negotiate_t work;
	void  *work_pdv;
};

/* State Machine Control Block */
struct fsm_s {
	uint8 state;			/* FSM state */
	uint8 lastid;			/* ID of last REQ we sent */

	uint8 flags;

	uint8 retry_request;		/* counter for timeouts */
	uint8 try_configure;		/* # tries for configure */
	uint8 try_terminate;		/* # tries for terminate */

	uint8 retry_nak;		/* counter for naks of requests */
	uint8 try_nak;	 		/* # tries for nak substitutes */

	struct ppp_s *ppp_p;		/* the ppp we belong to */
	struct timer timer;
	struct fsm_constant_s *pdc;	/* protocol dependent constants */
	void *pdv;			/* protocol dependent variables */

	struct fsm_side_s local;
	struct fsm_side_s remote;
};

/* Link Phases */
enum {
	pppDEAD,		/* Waiting for physical layer */
	pppESTABLISH,		/* Link Establishment Phase */
	pppAUTHENTICATE,	/* Authentication Phase */
	pppNETWORK,		/* Network Protocol Phase */
	pppTERMINATE,		/* Termination Phase */
	pppPhase_Size
};

/* PPP control block */
struct ppp_s {
	struct iface *iface;		/* pointer to interface block */

	uint8 phase;			/* phase of link initialization */
	uint8 id;			/* id counter for connection */

	uint8 flags;
#define PPP_AP_LOCAL	0x10	/* local authentication */
#define PPP_AP_REMOTE	0x20	/* remote authentication */

	struct fsm_s fsm[fsmi_Size];	/* finite state machines */

	uint32 upsince;			/* Timestamp when Link Opened */
	char *peername;			/* Peername from remote (if any) */

	uint32 OutOpenFlag;		/* # of open flags sent */
	uint32 OutNCP[fsmi_Size];	/* # NCP packets sent by protocol */

	uint32 InGoodOctets;		/* # of good octets received */
	uint32 InOpenFlag;		/* # of open flags */
	uint32 InNCP[fsmi_Size];	/* # NCP packets by protocol */
	uint32 InUnknown;		/* # unknown packets received */
	uint32 InChecksum;		/* # packets with bad checksum */
	uint32 InFrame; 		/* # packets with frame error */
};
#define NULLPPP	(struct ppp_s *)0

extern struct iface *PPPiface;	/* iface for trace */

extern char far *fsmStates[];
extern char far *fsmCodes[];

#endif /* _WAN_PPPFSM_H */
