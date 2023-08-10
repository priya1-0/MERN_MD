
/* ************************************************************************* */
/*
 *	frames.h
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
 *	Module:		MNP
 *
 *	This file contains the declarations for MNP transmit and receive frames.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 20:29:43  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _MNP_FRAMES_H
#define _MNP_FRAMES_H

/* ************************************************************************* */

typedef struct {
	uint8	line_status;
	uint8	packet_status;
	uint16	packet_length;
} mnp_frame_status_t;

#define MNP_FRAME_STATUS  mnp_frame_status.line_status
#define MNP_PACKET_STATUS mnp_frame_status.packet_status
#define MNP_PACKET_LENGTH mnp_frame_status.packet_length

/* ************************************************************************* */
/*
 * lr fields and data structures
 *
 */

/* - lr fixed header parameters --------------- */

typedef struct {
	pack8	parameter_type;			/* parm type 1, length 6 */
	pack8	parameter_length;
	pack8	values [6];					/* 1,0,0,0,0,255 */
} mnp_lr_serial_number_t;

typedef struct {
	pack8	parameter_type;			/* parm type 2, length 1 */
	pack8	parameter_length;
	pack8	values [1];
} mnp_lr_service_class_t;

typedef struct {
	pack8	parameter_type;			/* parm type 3, length 1 */
	pack8	parameter_length;
	pack8	values [1];
} mnp_lr_credit_amount_t;

typedef struct {
	pack8	parameter_type;			/* parm type 4, length 2 */
	pack8	parameter_length;
	pack8	values [2];					/* uint16 HL */
} mnp_lr_data_size_t;

/* - lr variable header parameters --------------- */

typedef struct {
	pack8	parameter_type;			/* parm type 8, length 1 */
	pack8	parameter_length;
	pack8	values [1];
} mnp_lr_optimization_t;

typedef struct {
	pack8	parameter_type;			/* parm type 9, length 1 */
	pack8	parameter_length;
	pack8	values [1];
} mnp_lr_data_compression_t;

typedef struct {
	mnp_lr_optimization_t optimization;
	mnp_lr_data_compression_t data_compression;
} mnp_lr_variable_header_t;

#define LR_OPTIMIZATION_SIZE sizeof(mnp_lr_optimization_t)
#define LR_DATA_COMPRESSION_SIZE  sizeof(mnp_lr_data_compression_t)

/* - lr total header declaration --------------- */

typedef struct {
	pack8	li;
	pack8	pdu;
	pack8	service_level;
	mnp_lr_serial_number_t serial_number;
	mnp_lr_service_class_t service_class;
	mnp_lr_credit_amount_t credit_amount;
	mnp_lr_data_size_t data_size;
	mnp_lr_variable_header_t variable_header;
} mnp_lr_header_t;

#define LR_SIZE (sizeof(mnp_lr_header_t)-sizeof(mnp_lr_variable_header_t))

/* - lr packet declaration --------------- */

typedef struct {
	mnp_lr_header_t header;
	/* no information */
} mnp_lr_packet_t;

/* - lr frame declaration --------------- */

#define MNP_TX_LR_SIZE_MAX 30

typedef struct {
	mnp_frame_status_t mnp_frame_status;
	uint8 frame [MNP_TX_LR_SIZE_MAX];
} mnp_lr_frame_t;

/* ************************************************************************* */
/*
 * ld fields and data structures
 *
 */

/* - ld fixed header parameters --------------- */

typedef struct {
	pack8	parameter_type;			/* parm type 1, length 1 */
	pack8	parameter_length;
	pack8	values [1];
} mnp_ld_disconnect_reason_t;

/* - ld variable header parameters --------------- */

typedef struct {
	pack8	parameter_type;			/* parm type 2, length 1 */
	pack8	parameter_length;
	pack8	values [1];
} mnp_ld_user_disconnect_reason_t;

typedef struct {
	mnp_ld_user_disconnect_reason_t user_disconnect_reason;
} mnp_ld_variable_header_t;

#define LD_USER_DISCONNECT_REASON_SIZE sizeof(mnp_ld_user_disconnect_reason_t)

/* - ld total header declaration --------------- */

typedef struct {
	pack8	li;
	pack8	pdu;
	mnp_ld_disconnect_reason_t disconnect_reason;
	mnp_ld_variable_header_t variable_header;
} mnp_ld_header_t;

#define LD_SIZE (sizeof(mnp_ld_header_t)-sizeof(mnp_ld_variable_header_t))

/* - ld packet declaration --------------- */

typedef struct {
	mnp_ld_header_t header;
	/* no information */
} mnp_ld_packet_t;

/* - ld frame declaration --------------- */

typedef struct {
	mnp_frame_status_t mnp_frame_status;
	union {
		mnp_ld_packet_t  ld;
	} packet;
} mnp_ld_frame_t;

/* ************************************************************************* */
/*
 * ln fields and data structures
 *
 */

/* - ln fixed header parameters --------------- */

typedef struct {
	pack8	parameter_type;			/* parm type 1, length 1 */
	pack8	parameter_length;
	pack8	values [1];
} mnp_ln_sequence_number_t;

typedef struct {
	pack8	parameter_type;			/* parm type 2, type length 1 */
	pack8	parameter_length;
	pack8	values [1];
} mnp_ln_attn_type_t;

/* - ln variable header parameters --------------- */

	/* none */

/* - ln total header declaration --------------- */

typedef struct {
	pack8	li;
	pack8	pdu;
	mnp_ln_sequence_number_t sequence_number;
	mnp_ln_attn_type_t attn_type;
} mnp_ln_header_t;

#define LN_SIZE (sizeof(mnp_ln_header_t))

/* - ln packet declaration --------------- */

typedef struct {
	mnp_ln_header_t header;
	/* no information */
} mnp_ln_packet_t;

/* - ln frame declaration --------------- */

typedef struct {
	mnp_frame_status_t mnp_frame_status;
	union {
		mnp_ln_packet_t  ln;
	} packet;
} mnp_ln_frame_t;

/* ************************************************************************* */
/*
 * lna fields and data structures
 *
 */

/* - lna fixed header parameters --------------- */

typedef struct {
	pack8	parameter_type;			/* parm type 1, length 1 */
	pack8	parameter_length;
	pack8	values [1];
} mnp_lna_sequence_number_t;

/* - lna variable header parameters --------------- */

	/* none */

/* - lna total header declaration --------------- */

typedef struct {
	pack8	li;
	pack8	pdu;
	mnp_lna_sequence_number_t sequence_number;
} mnp_lna_header_t;

#define LNA_SIZE (sizeof(mnp_lna_header_t))

/* - lna packet declaration --------------- */

typedef struct {
	mnp_lna_header_t header;
	/* no information */
} mnp_lna_packet_t;

/* - lna frame declaration --------------- */

typedef struct {
	mnp_frame_status_t mnp_frame_status;
	union {
		mnp_lna_packet_t lna;
	} packet;
} mnp_lna_frame_t;

/* ************************************************************************* */
/*
 * lt (lt and lt4) fields and data structures
 *
 */

/* - lt (lt and lt4) packet information size --------------- */

typedef struct {
	pack8	values [260];
} mnp_lt_information_t;

/* ---------------------------------------------------- */

/* - lt fixed header parameters --------------- */

typedef struct {
	pack8	parameter_type;			/* parm type 1, length 1 */
	pack8	parameter_length;
	pack8	values [1];
} mnp_lt_sequence_number_t;

/* - lt variable header parameters --------------- */

	/* none */

/* - lt total header declaration --------------- */

typedef struct {
	pack8	li;
	pack8	pdu;
	mnp_lt_sequence_number_t sequence_number;
} mnp_lt_header_t;

#define LT_SIZE (sizeof(mnp_lt_header_t))

/* - lt packet declaration --------------- */

typedef struct {
	mnp_lt_header_t header;
	mnp_lt_information_t information;
} mnp_lt_packet_t;

/* ---------------------------------------------------- */

/* - lt4 fixed header parameters --------------- */

	/* none */

/* - lt4 variable header parameters --------------- */

	/* none */

/* - lt4 total header declaration --------------- */

typedef struct {
	pack8	li;
	pack8	pdu;
	pack8	sequence_number;		/* value			*/
} mnp_lt4_header_t;

#define LT4_SIZE (sizeof(mnp_lt4_header_t))

/* - lt4 packet declaration --------------- */

typedef struct {
	mnp_lt4_header_t header;
	mnp_lt_information_t information;
} mnp_lt4_packet_t;

/* ---------------------------------------------------- */

/* - lt (lt and lt4) frame declaration --------------- */

typedef struct {
	mnp_frame_status_t mnp_frame_status;
	union {
		mnp_lt_packet_t  lt;
		mnp_lt4_packet_t lt4;
	} packet;
} mnp_lt_frame_t;

/* ************************************************************************* */
/*
 * la (la and la4) fields and data structures
 *
 */

/* - la fixed header parameters --------------- */

typedef struct {
	pack8	parameter_type;			/* parm type 1, length 1 */
	pack8	parameter_length;
	pack8	values [1];
} mnp_la_sequence_number_t;

typedef struct {
	pack8	parameter_type;			/* parm type 2, length 1 */
	pack8	parameter_length;
	pack8	values [1];
} mnp_la_credit_amount_t;

/* - la variable header parameters --------------- */

	/* none */

/* - la total header declaration --------------- */

typedef struct {
	pack8	li;
	pack8	pdu;
	mnp_la_sequence_number_t sequence_number;
	mnp_la_credit_amount_t credit_amount;
} mnp_la_header_t;

#define LA_SIZE (sizeof(mnp_la_header_t))

/* - la packet declaration --------------- */

typedef struct {
	mnp_la_header_t header;
	/* no information */
} mnp_la_packet_t;

/* ---------------------------------------------------- */

/* - la4 fixed header parameters --------------- */

	/* none */

/* - la4 variable header parameters --------------- */

	/* none */

/* - la4 total header declaration --------------- */

typedef struct {
	pack8	li;
	pack8	pdu;
	pack8	sequence_number;		/* value			*/
	pack8	credit_amount;			/* value			*/
} mnp_la4_header_t;

#define LA4_SIZE (sizeof(mnp_la4_header_t))

/* - la4 packet declaration --------------- */

typedef struct {
	mnp_la4_header_t header;
	/* no information */
} mnp_la4_packet_t;

/* ---------------------------------------------------- */

/* - la (la and la4) frame declaration --------------- */

typedef struct {
	mnp_frame_status_t mnp_frame_status;
	union {
		mnp_la_packet_t  la;
		mnp_la4_packet_t la4;
	} packet;
} mnp_la_frame_t;

/* ************************************************************************* */

/* - any mnp fixed header parameters --------------- */

	/* none */

/* - any mnp variable header parameters --------------- */

	/* none */

/* - any mnp total header declaration --------------- */

typedef struct {
	pack8	li;
	pack8	pdu;
	pack8	header_data [1];	/* actually 0 elements but compiler won't let us */
} mnp_any_header_t;

/* - any_mnp packet declaration --------------- */

typedef struct {
	mnp_any_header_t header;
} mnp_any_packet_t;

/* - any frame declarations --------------- */

typedef struct {
	mnp_frame_status_t mnp_frame_status;
	union {
		mnp_any_packet_t any;
		mnp_lr_packet_t  lr;
		mnp_ld_packet_t  ld;
		mnp_ln_packet_t  ln;
		mnp_lna_packet_t lna;
		mnp_lt_packet_t  lt;
		mnp_lt4_packet_t lt4;
		mnp_la_packet_t  la;
		mnp_la4_packet_t la4;
	} packet;
} mnp_transmit_frame_t;

typedef struct {
	mnp_frame_status_t mnp_frame_status;
	union {
		mnp_any_packet_t any;
		mnp_lr_packet_t  lr;
		mnp_ld_packet_t  ld;
		mnp_ln_packet_t  ln;
		mnp_lna_packet_t lna;
		mnp_lt_packet_t  lt;
		mnp_lt4_packet_t lt4;
		mnp_la_packet_t  la;
		mnp_la4_packet_t la4;
	} packet;
	uint8 crc [2];
} mnp_receive_frame_t;

/* ************************************************************************* */

#endif /* _MNP_FRAMES_H */
