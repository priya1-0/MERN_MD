
/* ************************************************************************* */
/*
 *  modcfg.h
 *
 *	(C) 1994 - 2006 VOCAL Technologies, Ltd.
 *
 *  ALL RIGHTS RESERVED.  PROPRIETARY AND CONFIDENTIAL.
 *
 *  VOCAL Technologies, Ltd.
 *  90A John Muir Drive.
 *  Buffalo, NY  14228
 *
 *  Product:    MODEM 101
 *
 *  Module:     LIB
 *
 *  This file defines array sizes for variables related to the LIB module.
 *
 *  Revision Number:    $Revision$
 *  Revision Status:    $State$
 *  Last Modified:      $Date$
 *  Identification:     $Id$
 *
 *  Revision History:   $Log$
 *  Revision History:   Revision 1.1.24.1  2009/04/28 19:33:26  zhangn1
 *  Revision History:   SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *  Revision History:
 *
 */
/* ************************************************************************* */

#ifndef _DATA_MODCFG_H
#define _DATA_MODCFG_H

/* ************************************************************************* */

#define V24__RLSD_OR	0x0100
#define V24__PUMP_OR	0x0200
#define V24__RDLB_OR	0x0400
#define V24__PUMP_AND	0x0001
#define V24__RDLB_AND	0x0002

#define V24__DEFAULT	0x01FE

/* ************************************************************************* */

#define V17_BULK_DELAY_BUFFER_SIZE		0x0020
#define V17_BULK_DELAY_BUFFER_LENGTH	0x0020
#define V17_EQUALIZER_DATA_SIZE			0x0040
#define V17_SEQUENCE_DETECT_SIZE		0x0040

#define V17_BULK_DELAY_BUFFER_OFFSET	0x0000
#define V17_EQUALIZER_DATA_OFFSET		V17_BULK_DELAY_BUFFER_OFFSET + V17_BULK_DELAY_BUFFER_SIZE
#define V17_SEQUENCE_DETECT_OFFSET		V17_EQUALIZER_DATA_OFFSET + V17_EQUALIZER_DATA_SIZE
#define V17_STORAGE_OFFSET				V17_SEQUENCE_DETECT_OFFSET + V17_SEQUENCE_DETECT_SIZE

#define V17_STORAGE_SIZE	BULK_DELAY_BUFFER_SIZEOF - (V17_STORAGE_OFFSET)

/* ************************************************************************* */

#define SILENCE_DATA_SIZE	0x0009
#define ENERGY_DATA_SIZE	0x0010

#define SILENCE_PASSBAND_BUFFER_SIZE	0x001D

#define ENERGY_COEFS_SIZE		0x0005
#define V21_DETECT_COEFS_SIZE	0x000A

/* ************************************************************************* */

/* ************************************************************************* */

#define V21_FLAG_CORRELATE_THRESHOLD	0x000A
#define V21_FLAG_HOLDOFF_DELAY			0x000C

/* ************************************************************************* */

#define TX_V21_MODE	(SELECT__TX_ENABLE + SELECT__V21)
#define RX_V21_MODE	(SELECT__RX_ENABLE + SELECT__V21)

/* ************************************************************************* */

#endif /* _DATA_MODCFG_H */
