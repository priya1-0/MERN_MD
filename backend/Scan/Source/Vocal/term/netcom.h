
/* ************************************************************************* */
/*
 *	netcom.h
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
 *	Module:		TERM
 *
 *	This file contains the public declarations for the TERM module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 20:49:20  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _TERM_NETCOM_H
#define _TERM_NETCOM_H

/* The stuff in this file is the inter-application definitions. */
/* A note on the structures when they are packed into net packets:
 * All data is byte packed.  None of the values are padded.
 * All multi - byte values are big endian. */

/* Note: Must be less than 128 of these.
 * If the expedite flag is set then this command is expedited. */
enum netcom_function_type {
	NOP = 0,							/* No operation */
	PAUSE,								/* Stop everything for a while. */
	FLUSH,								/* Flush buffers. */
	CONFIG_PORT,						/* Set up the com port. */
	TX_DATA,							/* Transmit this data to the next layer. */
	STATUS_REQ,							/* Send back your status. */
	STATUS,								/* My status, sent to you. */
	SET_HW_MODE,						/* Set your hardware to this mode. */
	CONTROL,							/* Control command. */
    ECHO_REQUEST,						/* Request an echo. */
	ECHO_RESP,							/* Respond to an echo. */
	LAST_PARAM
};
#define NETCOM_EXPEDITE 0x80

#define NETCOM_MAX_PACKET 400	/* Maximum packet size. (Must be less than
								 * one ipx packet.)  This is a temp hack. */
struct netcom_packet_header {
	uint16 length;			/* How big the entire packet is, not including
							 * this header. */
	uint16 window;			/* How many more transmission bytes you can send
							 * me.  This is NOT an absolute size.  If one
							 * packet has 10, and the next packet has 15,
							 * then the receiver has room for 25 more bytes.
							 * If in between the sender sent 7 bytes, then
							 * the reciever has room for 18 bytes. */
#define NETCOM_PHEADER_LEN 4 /* Size of the packet header in PACKET bytes. */
};

/* Note: Each function only writes out the header, and the data for it's
 * function.  It doesn't put a NETCOM_FUNCTION structure in for each
 * function. */
struct netcom_function {
	uint8 function_code;	/* Which function is this. */
	uint16 param_length;	/* How many bytes are left in this function,
							 * Excluding this header. */
#define NETCOM_FHEADER_LEN 3 /* Size of the function header in PACKET bytes. */
	union {
		struct {
			uint16 msec;	/* Pause time in milliseconds. */
#define NETCOM_PAUSE_LEN 2
		} pause;
		struct {
			uint8 which;	/* Which buffer(s) to flush. */
#define NETCOM_FLUSH_TX 0x01	/* Flags for each buffer. */
#define NETCOM_FLUSH_RX 0x02

#define NETCOM_FLUSH_LEN 1
		} flush;
		struct {
			uint8 ctrl_mask;	/* On bit in this byte means change state. */
			uint8 ctrl_state;	/* Change to this state. */
#define NETCOM_BREAK		0x80	/* If 1, assert break. */
#define NETCOM_ABORT		0x80	/* If 1, assert abort. */
#define NETCOM_XOFF			0x40	/* If 1, transmit txoff character to other side.
									 * If 0, transmit txon character to other side. */
#define NETCOM_RTS			0x20	/* If 1, raise RTS. */
#define NETCOM_DTR			0x10	/* If 1, raise DTR. */

#define NETCOM_CONTROL_LEN 2
		} control;
		struct {
			/* Receive characteristics.  8250s use these for both receive
			 * and transmit. */
			uint8 rbaud;		/* Receive baud rate index. */
/* These indicies match the NASI spec when possable. */
#define NETCOM_50		0x00
#define NETCOM_75		0x01
#define NETCOM_110      0x02
#define NETCOM_134_5    0x03
#define NETCOM_150      0x04
#define NETCOM_300      0x05
#define NETCOM_600      0x06
#define NETCOM_1200     0x07
#define NETCOM_1800     0x08
#define NETCOM_2000     0x09
#define NETCOM_2400     0x0a
#define NETCOM_3600     0x0b
#define NETCOM_4800     0x0c
#define NETCOM_7200     0x0d
#define NETCOM_9600     0x0e
#define NETCOM_19200    0x0f
#define NETCOM_34800    0x10
#define NETCOM_57600    0x11
#define NETCOM_115200   0x12
#define NETCOM_BAUDMAX	0x13

			uint8 rchar_len;	/* Receive character length index. */
#define NETCOM_LEN_5	0x00
#define NETCOM_LEN_6    0x01
#define NETCOM_LEN_7    0x02
#define NETCOM_LEN_8    0x03
#define NETCOM_LENMAX	0x04
			uint8 rstop_bit;	/* Receive stop bit index */
#define NETCOM_STOP_1	0x00
#define NETCOM_STOP_1_5	0x01
#define NETCOM_STOP_2	0x02
#define NETCOM_STOPMAX	0x03
			uint8 rparity;	/* Receive parity index. */
#define NETCOM_N_PARITY	0x00
#define NETCOM_O_PARITY	0x01
#define NETCOM_E_PARITY	0x02
#define NETCOM_M_PARITY	0x03
#define NETCOM_S_PARITY	0x04
#define NETCOM_PARITYMAX 0x05

			uint8 tbaud;		/* Transmit baud rate index. */
			uint8 tchar_len;	/* Transmit character length index. */
			uint8 tstop_bit;	/* Transmit stop bit index */
			uint8 tparity;		/* Transmit parity index. */

			uint8 flow_control;
#define NETCOM_FLOW_NONE 0x00
#define NETCOM_FLOW_SOFT 0x01
#define NETCOM_FLOW_HARD 0x02
#define NETCOM_FLOW_BOTH (NETCOM_FLOW_HARD|NETCOM_FLOW_SOFT)

			uint8 txon;			/* Transmit XON charater (default 0x11) */
			uint8 txoff;		/* Transmit XOFF charater (default 0x13) */
			uint8 rxon; 		/* Receive XON charater (default 0x11) */
			uint8 rxoff;		/* Receive XON charater (default 0x13) */
#define NETCOM_DTXON    CTLQ
#define NETCOM_DTXOFF   CTLS
#define NETCOM_DRXON    CTLQ
#define NETCOM_DRXOFF   CTLS

#define NETCOM_IGNORE ~0
/* Note: If a value is NETCOM_IGNORE, then the current value is retained.
 *       This has the side effect of making 0xFF unusable for software flow
 *       control.  This isn't known to be a problem, but if it turns out to
 *       be one, we'll have to change our definition. */

#define NETCOM_CONFIGP_LEN 13
		} config_port;
		struct {
			uint8 *data;
/* TX_DATA is of variable length. */
		} tx_data;
		struct {
			uint8 mode;
#define NETCOM_ASYNC_DATA   0
#define NETCOM_HDLC_DATA    1
#define NETCOM_SYNC_DATA    2
#define NETCOM_FAX_II	    3
#define NETCOM_FAX_II_SPOOF 4
			uint8 *options;				/* Variable length optional paramaters. */
/* HW_MODE is of variable length. */
		} hw_mode;

		/* The status_req function has no paramaters. */
#define NETCOM_STATUSREQ_LEN 0
		struct {
			uint8 hw_mode;				/* The hardware mode. */

			uint8 line_status;			/* Line status bits in 8250 order. */
/* These are bit fields */
#define NETCOM_LSTOUT	0x80
#define NETCOM_LSTXSRE	0x40
#define NETCOM_LSTXBE	0x20
#define NETCOM_LSBRKD	0x10
#define NETCOM_LSFRERR	0x08
#define NETCOM_LSPERR	0x04
#define NETCOM_LSOERR	0x02
#define NETCOM_LSRDR	0x01

			uint8 modem_status;			/* Modem status bits in 8250 order. */
#define NETCOM_MSRLSD	0x80
#define NETCOM_MSDCD	0x80
#define NETCOM_MSRING	0x40
#define NETCOM_MSDSR	0x20
#define NETCOM_MSCTS	0x10
#define NETCOM_MSDRLSD	0x08
#define NETCOM_MSTERI	0x04
#define NETCOM_MSDDSR	0x02
#define NETCOM_MSDCTS	0x01

			uint8 other_status;			/* Other statuses that don't fit well
										 * into line or modem. */
#define NETCOM_XON_SET 0x01				/* Is XON asserted from other side etc. */

#define NETCOM_STATUS_LEN 4
		} status;
		struct {
			uint16 data;
		} echo;
#define NETCOM_ECHO_LEN 2
	} param;
};

#endif /* _TERM_NETCOM_H */
