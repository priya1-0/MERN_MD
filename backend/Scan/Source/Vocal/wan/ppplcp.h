
/* ************************************************************************* */
/*
 *	ppplcp.h
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
 *	This file contains the PPP LCP declarations.
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

#ifndef _WAN_PPPLCP_H
#define _WAN_PPPLCP_H

#define LCP_REQ_TRY	20		/* REQ attempts */
#define LCP_NAK_TRY	10		/* NAK attempts */
#define LCP_TERM_TRY	10		/* tries on TERM REQ */

#define LCP_TIMEOUT	10		/* Seconds to wait for response */

					/* LCP option types */
#define LCP_MRU			0x01
#define LCP_ACCM		0x02
#define LCP_AP			0x03
#define LCP_QMP 		0x04
#define LCP_MAGIC		0x05
#define LCP_PFC			0x07
#define LCP_ACFC		0x08
#define LCP_OPTION_LIMIT	0x08	/* highest # we can handle */

#define LCP_N_MRU		(1 << LCP_MRU)
#define LCP_N_ACCM		(1 << LCP_ACCM)
#define LCP_N_AP		(1 << LCP_AP)
#define LCP_N_QMP		(1 << LCP_QMP)
#define LCP_N_MAGIC		(1 << LCP_MAGIC)
#define LCP_N_PFC		(1 << LCP_PFC)
#define LCP_N_ACFC		(1 << LCP_ACFC)

/* Table for LCP configuration requests */
struct lcp_value_s {
	uint16 mru;			/* Maximum Receive Unit */
	uint32 accm;			/* Async Control Char Map */
	uint16 authentication;		/* Authentication protocol */
	uint8 chap_digest;
	uint16 monitoring;		/* Quality Monitoring protocol */
	uint32 reporting_period; 	/* Quality Reporting period */
	uint32 magic_number;		/* Magic number value */
};

/* Other configuration option values */
#define LCP_ACCM_DEFAULT	0xffffffffL
#define LCP_MRU_DEFAULT 	1492
#define LCP_MRU_HI		4096		/* High MRU limit */
#define LCP_MRU_LO		128		/* Lower MRU limit */

#endif /* _WAN_PPPLCP_H */
