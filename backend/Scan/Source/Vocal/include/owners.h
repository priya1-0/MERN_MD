
/* ************************************************************************* */
/*
 *	owners.h
 *
 *	(C) 1994 - 2006 VOCAL Technologies, Ltd.
 *
 *	ALL RIGHTS RESERVED.  PROPRIETARY AND CONFIDENTIAL.
 *
 *	VOCAL Technologies, Ltd.
 *	90A John Muir Drive.
 *	Buffalo, NY  14228
 *
 *	Product:	MODEM 101
 *
 *	Module:		INCLUDE
 *
 *	This file defines the owner resources required by various modules.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 19:50:33  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _INCLUDE_OWNERS_H
#define _INCLUDE_OWNERS_H

/* ************************************************************************* */

#define OWNER__BG_TIMER_ROUTINE						0x0100
#define OWNER__OMC									0x0101
#define OWNER__MONITOR								0x0102
#define OWNER__TASK_DP								0x0103
#define OWNER__ACCESS								0x0104
#define OWNER__DP									0x0105
#define OWNER__FX1									0x0106
#define OWNER__FX2									0x0107
#define OWNER__T30									0x0108
#define OWNER__T4									0x0109
#define OWNER__CSC									0x010A
#define OWNER__V24									0x010B
#define OWNER__T30_ECM								0x010C
#define OWNER__T30_ECM_MEM_SIM						0x010D
#define OWNER__CSC_CALLER_ID						0x010E
#define OWNER__OMC_CALLER_ID						0x010F
#define OWNER__SIGMA								0x0110
#define OWNER__RTMSC								0x0111
#define OWNER__T38									0x0112
#define OWNER__TASK_DTEIF_WRITE						0x0113
#define OWNER__TASK_DTEIF_READ						0x0114

#define OWNER__SIP									0x0115
#define OWNER__SIP_INTRPTR							0x0116
#define OWNER__SIP_MANAGER							0x0117
#define OWNER__SDP_MANAGER							0x0118
#define OWNER__SIP_RTP_RX							0x0119
#define OWNER__SIP_RTP_TX							0x011A

#define OWNER__MGCP									0x0120
#define OWNER__MGCP_INTRPTR							0x0121

#define OWNER__H323									0x0130
#define OWNER__T38_RTP_SEND							0x0131
#define OWNER__T38_RTP_RECEIVE						0x0132
#define OWNER__H323_ORG								0x2006
#define OWNER__H323_ANS								0x2007

#define	OWNER__H245									0x1000
#define OWNER__H245_ORG_RECV						0x2000
#define OWNER__H245_ORG_SEND						0x2001
#define OWNER__H245_ANS_RECV						0x2002
#define OWNER__H245_ANS_SEND						0x2003

#define OWNER__RTP_ORG_READ							0x2004
#define OWNER__H225_PHA_SEND						0x2008
#define OWNER__H225_PHA_RECV						0x2009

/*
#define OWNER__H225_ANS_READ						0x200A
#define OWNER__H225_ANS_WRITE						0x200B
*/
#define OWNER__H225									0x200C
#define OWNER__RTP									0x2011
#define	OWNER__H225RAS								0x200D
#define	OWNER__H225RAS_TALK							0x200F
#define	OWNER__H225RAS_LISTEN						0x2010
#define OWNER__RTP_RTCP_RECV						0x200E

#define OWNER__IPBX_SWITCH							0x0170
#define OWNER__ATA_MONITOR							0x0180

#define OWNER__APP_TEST								0x0200
#define OWNER__IP									0x0201
#define OWNER__APP_FXAPP							0x0202
#define OWNER__APP_DTAM								0x0203

#define OWNER__USER									0x020F

#define OWNER__FG_MAIN								0x0000	/* Main foreground state */
#define OWNER__FG_OVERLAY							0x0001
#define OWNER__FG_AUTOMODE							0x0002
#define OWNER__FG_MODULATION						0x0003
#define OWNER__FG_RDLB								0x0004
#define OWNER__FG_DATA								0x0005
#define OWNER__FG_BONDING							0x0006
#define OWNER__FG_ISDN								0x0007
#define OWNER__FG_FACSIMILE							0x0008
#define OWNER__FG_TEL								0x0009
#define OWNER__FG_V8_BIS							0x000a
#define OWNER__FG_V8_BIS_DETECT						0x000b
#define OWNER__FG_V13								0x000c
#define OWNER__FG_SPEECH							0x000d

#define OWNER__FG_USER								0x000f

/* ************************************************************************* */

#endif /* _INCLUDE_OWNERS_H */
