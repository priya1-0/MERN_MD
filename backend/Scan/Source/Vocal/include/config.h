
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
 *	Module:		INCLUDE
 *
 *	This file defines array sizes for various interproject arrays.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 19:50:34  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _INCLUDE_CONFIG_H
#define _INCLUDE_CONFIG_H

/* ************************************************************************* */

#include "general/general.h"

/* ************************************************************************* */

#define STRSIZE_16						16			/* port number */
#define STRSIZE_32						32			/* tag field */
#define STRSIZE_64						64			/* most fields can reasonably fit in here */
#define STRSIZE_96						96			/* via data field */
#define STRSIZE_128						128			/* uri stuff */
#define STRSIZE_256						256			/* rtp message body size */
#define STRSIZE_512						512			/* mgcp digit map field */
#define STRSIZE_1024					1024		/* sdp message body size */

#define MAX_HOST_BUFFER_CHARS			64

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */
/* Sample buffer size declarations */
/* ************************************************************************* */

/* ************************************* */
/* first, set up defaults */

/* Number of timeslots in the sample buffer.  1 for most arches, 2 for  */
/* two channels interleaved into one sample buffer.  When using dma to  */
/* store multiple channels in the sample buffer, you should change this */
/* define in the appropriate configuration section below (DO NOT CHANGE */
/* IT HERE, THIS IS A GLOBAL DEFAULT) */
#define SPORT_NUM_TIMESLOTS							1

/* if you're using dma, you'll want to override this dma frame size for */
/* your specific platform (again, DO NOT CHANGE IT HERE, ADD IT BELOW.) */
/* Note that this number should always be a multiple of num_timeslots.  */
/* IF YOU'RE NOT USING DMA, LEAVE THIS 1.  THE DEFINE IS ALWAYS USED.   */
#define SPORT_DMA_SINGLE_CHANNEL_SIZE				1

#define SAMPLE_BUFFER_WORDS_PER_SAMPLE				1

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */
/* ************************************************************************* */

#define MULTI_DEVICES_NUM	 NUMBER_OF_CHANNELS_PER_DSP

/* ************************************************************************* */

#define NUMBER_OF_LOCAL_LINES_PER_DSP	(NUMBER_OF_LINES_PER_DSP)		/* Local channels corresponding to actual hardware ports (FXS and full FXO) */
#define NUMBER_OF_REMOTE_LINES_PER_DSP				0					/* Remote channels corresponding to packetized hardware ports (VPPN FXS devices) */

/* ************************************************************************* */

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* Display buffer length for long strings (may be any length, not limited by hardware) */
#define LCD_CHAR_DISPLAY_MAX	1

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

#define SAMPLE_BUFFER_SINGLE_CHANNEL_SIZE			17

/* speech requires a lot of horsepower and has large amounts of block */
/* processing, so increase default size of the sample buffer */

/* ************************************* */
/* per architecture settings */

/* ************************************************************************* */
/* ************************************************************************* */

#undef  SPORT_DMA_SINGLE_CHANNEL_SIZE
#define SPORT_DMA_SINGLE_CHANNEL_SIZE				8

#undef  SAMPLE_BUFFER_SINGLE_CHANNEL_SIZE
#define SAMPLE_BUFFER_SINGLE_CHANNEL_SIZE			80

/* ***************************************************** */
/* TEST ONLY - overrides */

/* ************************************************************************* */

#define SAMPLE_BUFFER_SIZE				((SAMPLE_BUFFER_SINGLE_CHANNEL_SIZE * SAMPLE_BUFFER_WORDS_PER_SAMPLE) * SPORT_NUM_TIMESLOTS)
#define SPORT_DMA_FRAME_SIZE			((SPORT_DMA_SINGLE_CHANNEL_SIZE  * SAMPLE_BUFFER_WORDS_PER_SAMPLE)  * SPORT_NUM_TIMESLOTS)
#define SPORT_DMA_FRAME_COUNT			(SAMPLE_BUFFER_SIZE / SPORT_DMA_FRAME_SIZE)

/* ************************************************************************* */
/* linux kernel mode stuff? */
/* ************************************************************************* */

/* ************************************************************************* */

#define CID_DATA_BUFFER_SIZEOF	64
#define CID_RX_BUFFER_LENGTH	256

#define DIAL_STRING_SIZE		61
#define STORED_DIAL_STRING_SIZE	45

/* ************************************************************************* */

#define T30_NSF_SIZEOF			90
#define T30_ID_SIZEOF			20

/* ************************************************************************* */
/* Size of vector of analysis parameters for various codecs. */
/* ************************************************************************* */

/* ************************************************************************* */
/* Size of decoded speech frames for various codecs. */
/* ************************************************************************* */

/* ************************************************************************* */
/* ************************************************************************* */

#define		ASM_ENCODE_SLOT_CNT_MAX			8
#define		ASM_DECODE_SLOT_CNT_MAX			8

/* ************************************************************************* */

/*	The values for the below symbols should possibly have been calculated
	from other symbols, but this is not done because certain
	compiler/assemblers have difficulty with this preprocessor operation.

	Where these values should be calculated from other symbols, a comment
	on the preceding line is required. */

/* Below number is maximum from above. */
#define RTMSC_FRAME_SIZE_MAX						30

/* ************************************************************************* */

#endif /* _INCLUDE_CONFIG_H */
