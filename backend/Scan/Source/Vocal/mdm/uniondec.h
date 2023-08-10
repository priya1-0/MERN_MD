
#define DO_FAX_DATA_OVERLAY_SINGLE

/* ************************************************************************* */
/*
 *	uniondec.h
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
 *	Module:		MDM
 *
 *	This module declares all shared memory modules.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 20:23:04  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _MDM_UNIONDEC_H
#define _MDM_UNIONDEC_H

#include "mdm/uniondef.h"

typedef struct {
	LAPM_LOCAL_DATA;
	LINE_LOCAL_LAPM_DATA;
} mem_overlay_lapm_t;

typedef struct {
	BTLZ_LOCAL_DATA;
} mem_overlay_btlz_t;

typedef struct {
	MNP_MNP_DATA;
	MNP_LOCAL_DATA;
	LINE_LOCAL_MNP_DATA;
} mem_overlay_mnp_t;

typedef struct {
	MNP5_LOCAL_DATA;
} mem_overlay_mnp5_t;

typedef union {
	mem_overlay_lapm_t			lapm;
	mem_overlay_mnp_t			mnp;
	uint16 unused;
} union_dp_t;

typedef union {
	mem_overlay_btlz_t			btlz;
	mem_overlay_mnp5_t			mnp5;
	uint16 unused;
} union_dc_t;

typedef struct {
	union_dp_t protocol;
	union_dc_t compression;
} mem_overlay_dp_dc_pair_t;

typedef struct {
	DIRECT_LOCAL_DATA;
} mem_overlay_direct_t;

typedef struct {
	DETECT_LOCAL_DATA;
	BUFFERED_LOCAL_DATA;
	LINE_LOCAL_BUFFERED_DATA;
} mem_overlay_buffered_t;

#ifdef DO_FAX_DATA_OVERLAY_SINGLE
#else /* DO_FAX_DATA_OVERLAY_SINGLE */

#endif /* DO_FAX_DATA_OVERLAY_SINGLE */

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/*																			 */
/* Allocate room for the data.												 */
/* Overlay the above structures in memory.									 */
/*																			 */
/* ************************************************************************* */
/* ************************************************************************* */

typedef union {
	mem_overlay_dp_dc_pair_t	mem_overlay_dp_dc_pair;
	mem_overlay_buffered_t		mem_overlay_buffered;
	mem_overlay_direct_t		mem_overlay_direct;
#ifdef DO_FAX_DATA_OVERLAY_SINGLE
#else /* DO_FAX_DATA_OVERLAY_SINGLE */
#endif /* DO_FAX_DATA_OVERLAY_SINGLE */
	uint16 unused;
} mov_t;

#define mem_overlay_lapm			mem_overlay_dp_dc_pair.protocol.lapm
#define mem_overlay_btlz			mem_overlay_dp_dc_pair.compression.btlz
#define mem_overlay_mnp				mem_overlay_dp_dc_pair.protocol.mnp
#define mem_overlay_mnp5			mem_overlay_dp_dc_pair.compression.mnp5

DEF_DATA(mov_t, mov)
#define UNION_DATA mov_t mov
#define UNION USE_DATA(mov)

#define USE_DATA_DIRECT(MODULE)		UNION.mem_overlay_direct.MODULE
#define USE_DATA_LAPM(MODULE)		UNION.mem_overlay_lapm.MODULE
#define USE_DATA_BTLZ(MODULE)		UNION.mem_overlay_btlz.MODULE
#define USE_DATA_BUFFERED(MODULE)	UNION.mem_overlay_buffered.MODULE
#define USE_DATA_MNP(MODULE)		UNION.mem_overlay_mnp.MODULE
#define USE_DATA_MNP5(MODULE)		UNION.mem_overlay_mnp5.MODULE
#ifdef DO_FAX_DATA_OVERLAY_SINGLE
#else /* DO_FAX_DATA_OVERLAY_SINGLE */
#endif /* DO_FAX_DATA_OVERLAY_SINGLE */

/* ************************************************************************* */

#endif /* _MDM_UNIONDEC_H */
