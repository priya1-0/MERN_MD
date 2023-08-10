
/* ************************************************************************* */
/*
 *  telcfg.h
 *
 *	(C) 1994 - 2006 VOCAL Technologies, Ltd.
 *
 *  ALL RIGHTS RESERVED.  PROPRIETARY AND CONFIDENTIAL.
 *
 *  VOCAL Technologies, Ltd.
 *	90A John Muir Drive.
 *	Buffalo, NY  14228
 *
 *  Product:    MODEM 101
 *
 *  Module:		LIBAUTO
 *
 *  This file defines array sizes for variables related to the TEL module.
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

#ifndef _DATA_TELCFG_H
#define _DATA_TELCFG_H

/* ************************************************************************* */

#define TONE_GENERATOR_COUNT		0x0004
#define TONE_PATTERN_COUNT			0x0008

#define RINGDET_OFF_TRIGGER_TIME	1350

/* Z_(REAL/10)_(IMAG/10) */
/* eg Z_22_82 is complex impedance of 220/820 */
/* these impedances are used in the internationalization tables */
#define Z_60_00		0
#define Z_27_75		1
#define Z_22_82		2
#define Z_20_68		3
#define Z_90_00		4
#define Z_37_62		5
#define Z_UNK		Z_27_75

/* ************************************************************************* */
/* ************************************************************************* */

/* these don't appear to be used, and plus the number format is wierd */
/* enough that we really don't want them to be common I suspect */

/* ************************************************************************* */

#endif /* _DATA_TELCFG_H */
