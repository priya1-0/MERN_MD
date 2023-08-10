
/* ************************************************************************* */
/*
 *	sart.h
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
 *	Define synchronous/asynchronous receiver transmitter parameters and data.
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

#ifndef _INCLUDE_SART_H
#define _INCLUDE_SART_H

/* ************************************************************************* */

/*
 *	Mode selection
 *
 */
#define SART_PARM__MODE__MASK				0xf000
#define SART_PARM__MODE__OFF				0x0000
#define SART_PARM__MODE__BAUD				0x1000
#define SART_PARM__MODE__ASYNC				0x2000
#define SART_PARM__MODE__HDLC				0x3000
#define SART_PARM__MODE__BINARY				0x4000
#define SART_PARM__MODE__FSK				0x5000
#define SART_PARM__MODE__NO_CARRIER			0x6000

/* ************************************************************************* */
/*
 *	Parameters used for async (V.14 and FSK)
 *
 */
#define SART_PARM__DATASIZE__MASK			0x0003
#define SART_PARM__DATASIZE__8_CODE			0x0003
#define SART_PARM__DATASIZE__7_CODE			0x0002
#define SART_PARM__DATASIZE__6_CODE			0x0001
#define SART_PARM__DATASIZE__5_CODE			0x0000

#define SART_PARM__STOPBIT_GEN_TWO			0x0004
#define SART_PARM__PARITY_ENABLE			0x0008
#define SART_PARM__PARITY_EVEN_SPACE		0x0010
#define SART_PARM__PARITY_STICK				0x0020
#define SART_PARM__STOPBIT_DELETE_FOURTH	0x0040
#define SART_PARM__NRZI						0x0800
/*
 *	Parameters used for HDLC
 *
 */
#define SART_PARM__CRC_FLAG_BY_UNDERRUN		0x0001
#define SART_PARM__DISABLE_CRC				0x0002
#define SART_PARM__CRC32					0x0004
#define SART_PARM__FILL_1					0x0008
#define SART_PARM__INVERTED					0x0010
#define SART_PARM__MARK_IDLE				0x0020
#define SART_PARM__NRZI						0x0800

#define SART_PARM__LEAD_FLAG_CNT__MASK		0x0700

#define SART_PARM__MODE__HDLC__FAX			SART_PARM__MODE__HDLC + SART_PARM__CRC_FLAG_BY_UNDERRUN
/*
 *	Parameters used for binary
 *
 */
#define SART_PARM__FILL_CODE				0x00ff
#define	SART_PARM__TRANSPARENT				0x0100
#define SART_PARM__USE_FILLWORD				0x0200
#define SART_PARM__NRZI						0x0800

/* ************************************************************************* */
/*
 *	Outgoing async (V.14 & FSK)
 *
 */
#define DU__NO_DATA_AVAILABLE				0x8000
#define DU__TIMED_BREAK						0x4000
#define DU__END_BREAK						0x2000
#define DU__START_BREAK						0x1000
#define DU__DELETE_STOP_BIT					0x0800	/* V.14 only */
#define DU__DETECT_MODE						0x0400
#define DU__NO_MORE_DATA					0x0100
/*
 *	Outgoing PPP escaping
 *
 */
#define DU__NO_DATA_AVAILABLE				0x8000
#define DU__FRAME_END						0x4000
#define DU__FRAME_START						0x2000
#define DU__GENERATE_ABORT					0x1000
#define DU__CORRUPT_FRAME					0x0800
#define DU__CONTROL_PACKET					0x0400
#define DU__SKIP_CRC						0x0200
#define DU__NO_MORE_DATA					0x0100
/*
 *	Outgoing HDLC
 *
 */
#define DU__NO_DATA_AVAILABLE				0x8000
#define DU__FRAME_END						0x4000
#define DU__FRAME_START						0x2000
#define DU__GENERATE_ABORT					0x1000
#define DU__CORRUPT_FRAME					0x0800
#define DU__NO_MORE_DATA					0x0100
/*
 *	Outgoing binary
 *
 */
#define DU__NO_MORE_DATA					0x0100

/* ************************************************************************* */
/*
 *	Incoming async (V.14 & FSK)
 *
 *	Up to 9 bits of data+parity are returned (Bit 8 is not avail for status)
 *
 */
#define DU__NO_DATA_AVAILABLE				0x8000
#define DU__BREAK_END_DETECT				0x2000
#define DU__BREAK_START_DETECT				0x1000
#define DU__FOUND_DELETED_STOP_BIT			0x0800	/* V.14 only */
#define DU__FRAMING_ERROR					0x0800	/* fsk only */
#define DU__PARITY_ERROR					0x0400
#define DU__OVERFLOW						0x0200

/* ************************************************************************* */
/*
 *	Generic async
 *
 */
#define DU__ASYNC__BREAK_START				0x1000
#define DU__ASYNC__BREAK_END				0x2000
#define DU__ASYNC__STOP_BIT_ERROR			0x0800
#define DU__ASYNC__PARITY_ERROR				0x0400

/* ************************************************************************* */
/*
 *	Generic sync (hdlc)
 *
 */
#define DU__SYNC__ABORT						0x1000
#define DU__SYNC__FCS_ERROR					0x0400
#define DU__SYNC__HDLC_IDLE					0x0100

/*
 *	Incoming PPP escaping
 *
 */
#define DU__NO_DATA_AVAILABLE				0x8000
#define DU__FRAME_END						0x4000
#define DU__FRAME_START						0x2000
#define DU__ABORT_DETECTED					0x1000
#define DU__CRC_ERROR						0x0400
#define DU__OVERFLOW						0x0200
/*
 *	Incoming HDLC
 *
 */
#define DU__NO_DATA_AVAILABLE				0x8000
#define DU__FRAME_END						0x4000
#define DU__FRAME_START						0x2000
#define DU__ABORT_DETECTED					0x1000
#define DU__RESIDUE_ERROR					0x0800
#define DU__CRC_ERROR						0x0400
#define DU__OVERFLOW						0x0200
/* May indicate in-stream carrier loss */
#define DU__NO_MORE_DATA					0x0100
/*
 *	Incoming binary
 *
 */
/* May indicate in-stream carrier loss */
#define DU__NO_MORE_DATA					0x0100

/* ************************************************************************* */
/*
 *	Misc.
 *
 */
#define CRC_EXPECTED						0xf0b8
#define NUM_DETECT_MODE_STOP_BITS			12	/* Should be between 8 & 16 */

/* ************************************************************************* */
/*
 *	Octet Interface Data Units flags
 *
 */

#define DU__CHANNEL_MODE_CHANGE				0x4000
#define DU__CHANNEL_MODE__BF__MASK			0x0003
#define DU__CHANNEL_MODE__BF__CONTROL		0x0000
#define DU__CHANNEL_MODE__BF__PRE_DATA		0x0001
#define DU__CHANNEL_MODE__BF__DATA			0x0002
#define DU__CHANNEL_MODE__BF__POST_DATA		0x0003

/* ************************************************************************* */

#endif /* _INCLUDE_SART_H */
