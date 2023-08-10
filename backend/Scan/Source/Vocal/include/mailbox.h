
/* ************************************************************************* */
/*
 *	mailbox.h
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
 *	Defines mailbox interface locations.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 19:50:33  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _INCLUDE_MAILBOX_H
#define _INCLUDE_MAILBOX_H

/* ************************************************************************* */
/*
 *	Boot ROM supported mailboxes (location 0 to 40)
 *
 */
/* ************************************************************************* */
/*
 *	Code execution mailbox
 *
 */
#define MBX__EXECUTE_FLAG			0	/* Execute mailbox flag */
#define MBX__EXECUTE_ADDRESS		1	/* Execute mailbox execute address */
#define MBX__EXECUTE_PAGE			2	/* Execute mailbox execute page */
#define MBX__EXECUTE_EXT_ADDRESS	2	/* Execute mailbox execute extended address */
/*
 *	Trace/breakpoint resume mailbox - not used
 *
 */
/*#define MBX__RESUME_FLAG			2 */ /* Resume mailbox */
/*#define MBX__RESUME_ADDRESS		3 */ /* Resume mailbox resume address */
/*
 *	Memory access mailbox
 *
 */
#define MBX__MEMORY_FLAG			4	/* Memory access mailbox flag */
#define MBX__MEMORY_COMMAND			5	/* Memory access mailbox command */
#define MBX__MEMORY_ADDRESS			6	/* Memory access mailbox address */
#define MBX__MEMORY_PAGE			7	/* Memory access mailbox page mask */
#define MBX__MEMORY_EXT_ADDRESS		7	/* Memory access mailbox extended address */
/* When mbx__memory_length > MBX__MEMORY_SIZEOF, the data is written with an implicit offset of (mbx__memory_length % MBX__MEMORY_SIZEOF) * MBX__MEMORY_SIZEOF */
#define MBX__MEMORY_LENGTH			8	/* Memory access mailbox length */
#define MBX__MEMORY_DATA			9	/* Memory access mailbox data */
#define MBX__MEMORY_SIZEOF			32	/* Size of memory access mailbox data */

/* ************************************************************************* */
/*
 *	Standard kernel supported mailboxes (locations 41 to 127)
 *
 */
/* ************************************************************************* */
/*
 *	Event generation mailbox
 *
 */
#define MBX__EVENT_FLAG				41	/* Event mailbox flag */
#define MBX__EVENT_CODE				42	/* Event mailbox event code */
#define MBX__EVENT_DATA				3	/* Event mailbox event data */
/*
 *	Status event notification mailbox
 *
 */
#define MBX__STATUS_FLAG			43	/* Status mailbox flag */
#define MBX__STATUS_CODE			44	/* Status mailbox status code */
#define MBX__STATUS_DATA			45	/* Status mailbox status data */
/*
 *	Location monitor notification mailbox
 *
 */
#define MBX__MONITOR_LOC_FLAG		46	/* Location monitor mailbox flag */
#define MBX__MONITOR_LOC_DATA		47	/* Location monitor mailbox data */
#define MBX__MONITOR_LOC_1_DATA		47	/* Location of location monitor 1 buffer */
#define MBX__MONITOR_LOC_2_DATA		48	/* Location of location monitor 2 buffer */
#define MBX__MONITOR_LOC_3_DATA		49	/* Location of location monitor 3 buffer */
#define MBX__MONITOR_LOC_4_DATA		50	/* Location of location monitor 4 buffer */
#define MBX__MONITOR_LOC_5_DATA		51	/* Location of location monitor 5 buffer */
#define MBX__MONITOR_LOC_6_DATA		52	/* Location of location monitor 6 buffer */
#define MBX__MONITOR_LOC_SIZEOF		6	/* Size of location monitor data */
/*
 *	XY (eye pattern) notification mailbox
 *
 */
#define MBX__MONITOR_XY_FLAG		53	/* Eye pattern mailbox flag */
#define MBX__MONITOR_XY_DATA		54	/* Eye pattern mailbox data */
#define MBX__MONITOR_X_DATA			54	/* Location of eye pattern X value */
#define MBX__MONITOR_Y_DATA			55	/* Location of eye pattern Y value */
#define MBX__MONITOR_XY_SIZEOF		8	/* Size of eye pattern data */
/*
 *	Memory dump notification mailbox
 *
 */
#define MBX__DUMP_FLAG				62	/* Memory dump mailbox flag */
#define MBX__DUMP_COMMAND			63	/* Memory dump mailbox command */
#define MBX__DUMP_ADDRESS			64	/* Memory dump mailbox address */
#define MBX__DUMP_PAGE				65	/* Memory dump mailbox page mask */
#define MBX__DUMP_EXT_ADDRESS		65	/* Memory dump mailbox extended address */
#define MBX__DUMP_LENGTH			66	/* Memory dump mailbox length */
/*
 *	H.223 related mailboxes
 *
 */
#define	MBX__SPEECH_RTP_HOST_ENC_RD	67	/* DSP -> HOST read RTP mailbox pointer */
#define MBX__SPEECH_RTP_HOST_DEC_WR	68	/* HOST -> DSP write RTP mailbox pointer */
#define MBX__SPEECH_RTP_PUMP_ENC_WR	69	/* HOST -> DSP write RTP mailbox pointer */
#define MBX__SPEECH_RTP_PUMP_DEC_RD	70	/* DSP -> HOST read RTP mailbox pointer */

#define	MBX__VIDEO_RTP_HOST_ENC_RD	71	/* DSP -> HOST read RTP mailbox pointer */
#define MBX__VIDEO_RTP_HOST_DEC_WR	72	/* HOST -> DSP write RTP mailbox pointer */
#define MBX__VIDEO_RTP_PUMP_ENC_WR	73	/* HOST -> DSP write RTP mailbox pointer */
#define MBX__VIDEO_RTP_PUMP_DEC_RD	74	/* DSP -> HOST read RTP mailbox pointer */

/*
 *	Unused locations 75 to 127
 *
 */

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */
/*
 *	Transmit data mailboxes (locations 128 to 255)
 *
 */
/* ************************************************************************* */
/*
 *	Primary transmit data mailbox
 *
 */
#define MBX__PRIMARY_TX_FLAG		128	/* Primary transmit mailbox flag */
#define MBX__PRIMARY_TX_LENGTH		129	/* Primary transmit mailbox length */
#define MBX__PRIMARY_TX_DATA		130	/* Primary transmit mailbox data */
#define MBX__PRIMARY_TX_SIZEOF		16	/* Size of primary transmit data */
#define MBX__LARGE_TX_SIZEOF		64	/* Size of large transmit data */
#define MBX__PACKED_TX_SIZEOF		128	/* Size of packed transmit data */
/*
 *	Secondary transmit data mailbox
 *
 */
#define MBX__SECONDARY_TX_FLAG		146	/* Secondary transmit mailbox flag */
#define MBX__SECONDARY_TX_LENGTH	147	/* Secondary transmit mailbox length */
#define MBX__SECONDARY_TX_DATA		148	/* Secondary transmit mailbox data */
#define MBX__SECONDARY_TX_SIZEOF	16	/* Size of secondary transmit data */
/*
 *	Control transmit data mailbox
 *
 */
#define MBX__CONTROL_TX_FLAG		164	/* Control transmit mailbox flag */
#define MBX__CONTROL_TX_LENGTH		165	/* Control transmit mailbox length */
#define MBX__CONTROL_TX_DATA		166	/* Control transmit mailbox data */
#define MBX__CONTROL_TX_SIZEOF		16	/* Size of control transmit data */
/*
 *	Auxiliary transmit data mailbox - must be beyond large transmit data
 *
 */
#define MBX__AUXILIARY_TX_FLAG		194	/* Auxiliary transmit mailbox flag */
#define MBX__AUXILIARY_TX_LENGTH	195	/* Auxiliary transmit mailbox length */
#define MBX__AUXILIARY_TX_DATA		196	/* Auxiliary transmit mailbox data */
#define MBX__AUXILIARY_TX_SIZEOF	16	/* Size of auxiliary transmit data */
/*
 *	Speech transmit data mailbox - overlays primary transmit data for now
 *
 */
#define MBX__SPEECH_TX_FLAG			128	/* Speech transmit mailbox flag */
#define MBX__SPEECH_TX_LENGTH		129	/* Speech transmit mailbox length */
#define MBX__SPEECH_TX_DATA			130	/* Speech transmit mailbox data */
#define MBX__SPEECH_TX_SIZEOF		16	/* Size of speech transmit data */

/* ************************************************************************* */
/*
 *	ISDN control mailbox
 *
 */
#define MBX__ISDN_CONTROL_FLAG		212	/* ISDN control mailbox flag */
#define MBX__ISDN_CONTROL_CODE		213	/* ISDN control mailbox status code */

/* ************************************************************************* */
/*
 *	RTP decode packet data mailbox - overlays primary transmit data and ISDN Control
 *
 */
#define MBX__RTP_DEC_FLAG			128	/* RTP decode packet flag */
#define MBX__RTP_DEC_LENGTH			129	/* RTP decode packet length */
#define MBX__RTP_DEC_DATA			130	/* RTP decode packet data */

/* Large enough for 240 samples of G.711 and 12 bytes RTP header (no extension headers) */
#define MBX__RTP_DEC_SIZEOF			126	/* Size of RTP decode data */
#define MBX__RTP_DEC_PACKED_SIZEOF	252	/* Size of RTP decode data (packed) */

/* ************************************************************************* */
/*
 *	Unused locations 214 to 255
 *
 */

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */
/*
 *	Receive data mailboxes (locations 256 to 383)
 *
 */
/* ************************************************************************* */
/*
 *	Primary receive data mailbox
 *
 */
#define MBX__PRIMARY_RX_FLAG		256	/* Primary receive mailbox flag */
#define MBX__PRIMARY_RX_LENGTH		257	/* Primary receive mailbox length */
#define MBX__PRIMARY_RX_DATA		258	/* Primary receive mailbox data */
#define MBX__PRIMARY_RX_SIZEOF		16	/* Size of primary receive data */
#define MBX__LARGE_RX_SIZEOF		64	/* Size of primary receive data */
#define MBX__PACKED_RX_SIZEOF		128	/* Size of packed receive data */
/*
 *	Secondary receive data mailbox
 *
 */
#define MBX__SECONDARY_RX_FLAG		274	/* Secondary receive mailbox flag */
#define MBX__SECONDARY_RX_LENGTH	275	/* Secondary receive mailbox length */
#define MBX__SECONDARY_RX_DATA		276	/* Secondary receive mailbox data */
#define MBX__SECONDARY_RX_SIZEOF	16	/* Size of secondary receive data */
/*
 *	Control receive data mailbox
 *
 */
#define MBX__CONTROL_RX_FLAG		292	/* Control receive mailbox flag */
#define MBX__CONTROL_RX_LENGTH		293	/* Control receive mailbox length */
#define MBX__CONTROL_RX_DATA		294	/* Control receive mailbox data */
#define MBX__CONTROL_RX_SIZEOF		16	/* Size of control receive data */
/*
 *	Auxiliary receive data mailbox - overlays primary receive data for now
 *
 */
#define MBX__AUXILIARY_RX_FLAG		322	/* Auxiliary receive mailbox flag */
#define MBX__AUXILIARY_RX_LENGTH	323	/* Auxiliary receive mailbox length */
#define MBX__AUXILIARY_RX_DATA		324	/* Auxiliary receive mailbox data */
#define MBX__AUXILIARY_RX_SIZEOF	16	/* Size of auxiliary receive data */
/*
 *	Speech receive data mailbox - overlays primary receive data for now
 *
 */
#define MBX__SPEECH_RX_FLAG			256	/* Speech receive mailbox flag */
#define MBX__SPEECH_RX_LENGTH		257	/* Speech receive mailbox length */
#define MBX__SPEECH_RX_DATA			258	/* Speech receive mailbox data */
#define MBX__SPEECH_RX_SIZEOF		16	/* Size of speech receive data */

/* ************************************************************************* */
/*
 *	ISDN status mailbox
 *
 */
#define MBX__ISDN_STATUS_FLAG		340	/* ISDN status mailbox flag */
#define MBX__ISDN_STATUS_CODE		341	/* ISDN status mailbox status code */
#define MBX__ISDN_STATUS_PREVIOUS	342	/* ISDN status mailbox previous status code */

/* ************************************************************************* */
/*
 *	RTP encode packet data mailbox - overlays primary receive data and ISDN status
 *
 */
#define MBX__RTP_ENC_FLAG			256	/* RTP encode packet flag */
#define MBX__RTP_ENC_LENGTH			257	/* RTP encode packet length */
#define MBX__RTP_ENC_DATA			258	/* RTP encode packet data */

/* Large enough for 240 samples of G.711 and 12 bytes RTP header (no extension headers) */
#define MBX__RTP_ENC_SIZEOF			126	/* Size of RTP encode data */
#define MBX__RTP_ENC_PACKED_SIZEOF	252	/* Size of RTP encode data (packed) */

/* ************************************************************************* */
/*
 *	Unused locations 343 to 383
 *
 */

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */
/*
 *	Customer mailboxes (locations 384 to 511)
 *
 */
#define MBX__CUSTOMER_FLAG			384	/* Customer mailbox flag */
#define MBX__CUSTOMER_LENGTH		385	/* Customer mailbox length */
#define MBX__CUSTOMER_DATA			386	/* Customer mailbox data */
#define MBX__CUSTOMER_SIZEOF		18	/* Size of customer data */
/*
 *	Unused locations 404 to 511
 *
 */
#define MBX__REGION_SIZEOF			512	/* Size of mailbox memory */

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */
/*
 *	Define DSP monitor commands
 *
 */
#define MONITOR_CMD__NOOP			0x0000	/* Command to do nothing */
#define MONITOR_CMD__PMRD			0x0001	/* Command to read program memory */
#define MONITOR_CMD__PMWR			0x0002	/* Command to write program memory */
#define MONITOR_CMD__DMRD			0x0003	/* Command to read data memory */
#define MONITOR_CMD__DMWR			0x0004	/* Command to write data memory */

/* ************************************************************************* */
/*
 *	Define DSP memory dump commands
 *
 */
#define DUMP_CMD__NOOP				0x0000	/* Command to do nothing */
#define DUMP_CMD__PMRD				0x0001	/* Command to read program memory */
#define DUMP_CMD__DMRD				0x0002	/* Command to read data memory */

/* ************************************************************************* */

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */
/*
 *	Define mailbox types for remote mailbox support
 *
 */
#define MBX_TYPE__NUMOF				6		/* Number of polled mailboxes */

#define MBX_TYPE__PACKET			0		/* Reserved for sending HPNA packet */
#define MBX_TYPE__STATUS			1
#define MBX_TYPE__EVENT				2
#define MBX_TYPE__MEMORY			3
#define MBX_TYPE__TX_DATA			4
#define MBX_TYPE__RX_DATA			5

/* ************************************************************************* */

#endif /* _INCLUDE_MAILBOX_H */
