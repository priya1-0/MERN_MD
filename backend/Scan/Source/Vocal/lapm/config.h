
/* ************************************************************************* */
/*
 *	config.h
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
 *	Module:		LAPM
 *
 *	This file defines array sizes for variables related to the
 *	LAPM module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 19:57:12  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _LAPM_CONFIG_H
#define _LAPM_CONFIG_H

/* ************************************************************************* */

/* ************************************************************************* */
/*
 *	1.	number of frames allocated for the working code
 *	2.	size of ancillary data structures
 *	3.	size of lapm info frames
 *
 */

#define LAPM_NUMBER_TX_BUFFERS		6		/* Numb of send buffers */
#define LAPM_NUMBER_RX_BUFFERS		7		/* Numb of receive buffers */
#define LAPM_NUMBER_CTL_BUFFERS		6		/* Numb of control buffers */

#define CMD_I_INFO_MAX				128		/* Max size of the info field */
#define CMD_U_TEST_MAX				128		/* Max size of the info field */
#define CMD_U_XID_MAX				51		/* Max size of the our xid field */

/*
 *
 *	[0]			XIDFID
 *
 *	[1]			XIDGID
 *	[2], [3]	group length
 *	[4] 		XIDOPT
 *	[5]			3
 *	[6]			XIDSUPT3
 *	[7]			XIDSUPT2
 *	[8]			0
 *
 *	[9]			XIDTN401
 *	[10]		length
 *	[11], [12], [13], [14]
 *
 *	[15]		XIDRN401
 *	[16]		length
 *	[17], [18], [19], [20]
 *
 *	[21]		XIDTK
 *	[22]		length
 *	[23], [24], [25], [26]
 *
 *	[27]		XIDRK
 *	[28]		length
 *	[29], [30], [31], [32]
 *
 *	[33] 		COMPGID
 *	[34], [35]	group length
 *	[36] 		COMPSID
 *	[37]		COMPSLEN
 *	[38]		'V'
 *	[39]		'4'
 *	[40]		'2'
 *
 *	[41]		COMPP0ID
 *	[42]		1
 *	[43]		p0
 *
 *	[44]		COMPP1ID
 *	[45]		2
 *	[46], [47]	p1
 *
 *	[48]		COMPP2ID
 *	[49]		1
 *	[50]		p2
 *
 */

/* ************************************************************************* */

/* From locald.h: */

#define UI_CMD_SIZEOF			(sizeof(lapm_UI_packet_t))
#define UI_RSP_SIZEOF			(sizeof(lapm_UI_rsp_packet_t))
#define XID_BASE_SIZEOF			4		/* XIDFID, XIDGID, group length size */

#define CMD_TABLE_SIZE			34		/* fixed in the code */
#define LAPM_NUMBER_OF_EVENTS	20		/* Number of lapm_eventp buffers */
#define LAPM_NUMBER_OF_TIMERS	4		/* Number of timers */

/* ************************************************************************* */

#endif /* _LAPM_CONFIG_H */
