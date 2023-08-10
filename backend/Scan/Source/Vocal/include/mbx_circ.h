
/* ************************************************************************* */
/*
 *	mbx_circ.h
 *
 *	(C) 1994 - 2006 VOCAL Technologies, Ltd.
 *
 *	ALL RIGHTS RESERVED.  PROPRIETARY AND CONFIDENTIAL.
 *
 *	VOCAL Technologies, Ltd.
 *	90A John Muir Drive.
 *	Buffalo, NY  14228
 *
 *	Product:	ADI PUMP
 *
 *	Module:		INCLUDE
 *
 *	Defines mailbox interface locations.
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

/* ************************************************************************* */

#ifdef DO_MBX_OVERSIZE_SAMPLE_RECORD
#define MBX_DTOH_SIZE		2048
#else /* DO_MBX_OVERSIZE_SAMPLE_RECORD */
#define MBX_DTOH_SIZE		576
#endif /* DO_MBX_OVERSIZE_SAMPLE_RECORD */
#define MBX_HTOD_SIZE		576

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/*
	Host -> DSP Sizes:

	Execute					2
	Event					4
	Tx Data					96
	Command					192
	Rx Sample				240

	DSP -> Host Sizes:

	Status					32
	Rx Data					96
	Response				16
	XY						16
	Diagnostic				144
	Tx Sample				240
*/

/* ************************************************************************* */
/* Host -> DSP */

/* Execute Mailbox */

#define MBX__EXECUTE__BUFFER		1
#define MBX__EXECUTE__SIZEOF		2
#define MBX__EXECUTE__WR_INDEX		3
#define MBX__EXECUTE__RD_INDEX		329

/* Event Mailbox */

#define MBX__EVENT__BUFFER			4
#define MBX__EVENT__SIZEOF			4
#define MBX__EVENT__WR_INDEX		8
#define MBX__EVENT__RD_INDEX		328

/* Primary Tx Data Mailbox */

#define MBX__TX_DATA__BUFFER		9
#define MBX__TX_DATA__SIZEOF		96
#define MBX__TX_DATA__WR_INDEX		105
#define MBX__TX_DATA__RD_INDEX		327

/* Command Mailbox */

#define MBX__COMMAND__BUFFER		106
#define MBX__COMMAND__SIZEOF		192
#define MBX__COMMAND__WR_INDEX		298
#define MBX__COMMAND__RD_INDEX		326

/* Rx Sample Mailbox */

#define MBX__RX_SAMPLE__BUFFER		330
#define MBX__RX_SAMPLE__SIZEOF		240
#define MBX__RX_SAMPLE__WR_INDEX	570
#ifdef DO_MBX_OVERSIZE_SAMPLE_RECORD
#define MBX__RX_SAMPLE__RD_INDEX	2047
#else /* DO_MBX_OVERSIZE_SAMPLE_RECORD */
#define MBX__RX_SAMPLE__RD_INDEX	575
#endif /* DO_MBX_OVERSIZE_SAMPLE_RECORD */

/* ************************************************************************* */
/* DSP -> Host */

/* Status Mailbox */

#define MBX__STATUS__WR_INDEX		1
#define MBX__STATUS__BUFFER			2
#define MBX__STATUS__SIZEOF			32
#define MBX__STATUS__RD_INDEX		329

/* Primary Rx Data Mailbox */

#define MBX__RX_DATA__WR_INDEX		34
#define MBX__RX_DATA__BUFFER		35
#define MBX__RX_DATA__SIZEOF		96
#define MBX__RX_DATA__RD_INDEX		328

/* Response Mailbox */

#define MBX__RESPONSE__WR_INDEX		131
#define MBX__RESPONSE__BUFFER		132
#define MBX__RESPONSE__SIZEOF		16
#define MBX__RESPONSE__RD_INDEX		327

/* Diagnostic Mailbox */

#define MBX__XY__WR_INDEX			148
#define MBX__XY__BUFFER				149
#define MBX__XY__SIZEOF				16
#define MBX__XY__RD_INDEX			326

/* Diagnostic Mailbox */

#define MBX__DIAG__WR_INDEX			165
#define MBX__DIAG__BUFFER			166
#define MBX__DIAG__SIZEOF			144
#define MBX__DIAG__RD_INDEX			325

/* Tx Sample Mailbox */

#define MBX__TX_SAMPLE__WR_INDEX	330
#define MBX__TX_SAMPLE__BUFFER		331
#ifdef DO_MBX_OVERSIZE_SAMPLE_RECORD
#define MBX__TX_SAMPLE__SIZEOF		1776
#else /* DO_MBX_OVERSIZE_SAMPLE_RECORD */
#define MBX__TX_SAMPLE__SIZEOF		240
#endif /* DO_MBX_OVERSIZE_SAMPLE_RECORD */
#define MBX__TX_SAMPLE__RD_INDEX	575

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/*	Format of Command:

	a) opcode
	b) address
	c) length of data field
	d) data - if write command

	Format of Response:

	a) opcode
	b) address
	c) length
	d) data
*/

#define MBX_CMD__NOP				0
#define MBX_CMD__PM_WR				1
#define MBX_CMD__PM_RD				2
#define MBX_CMD__DM_WR				3
#define MBX_CMD__DM_RD				4

#define MBX_RSP__NOP				0
#define MBX_RSP__PM_RD				2
#define MBX_RSP__DM_RD				4

/* ************************************************************************* */
