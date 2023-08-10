
/* ************************************************************************* */
/*
 *	dteifd.h
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
 *	Module:		DTEIF
 *
 *	This file contains the public parameter declarations/definitions for
 *	the DTEIF module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 19:48:36  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _DTEIF_DTEIFD_H
#define _DTEIF_DTEIFD_H

/* ************************************************************************* */

typedef struct {
	uint16	_tx_state;
	uint16	_rx_state;
	uint32	_rx_mtr;
	uint32	_tx_mtr;
	uint32	_rx_raw_mtr;
	uint32	_tx_raw_mtr;

	uint16	_parm_dteif_v24_106;
	uint16	_parm_dteif_v24_107;
	uint16	_parm_dteif_v24_109;
	uint16	_parm_dteif_v24_110;
	uint16	_parm_dteif_v24_125;
	uint16	_parm_dteif_v24_132;
	uint16	_parm_dteif_v24_142;
	uint16	_parm_dteif_hook;

	uint16	_stat_dteif_v24_105;
	uint16	_stat_dteif_v24_108;
	uint16	_stat_dteif_v24_133;

} dteif_dteif_t;

/* ************************************************************************* */

DEF_DATA(dteif_dteif_t, dteif_dteif)
#define DTEIF_DTEIF_DATA dteif_dteif_t dteif_dteif
#define DTEIF_DTEIF USE_DATA(dteif_dteif)

/* ************************************************************************* */

#define	dteif_tx_state						(DTEIF_DTEIF._tx_state)
#define	dteif_rx_state						(DTEIF_DTEIF._rx_state)
#define	dteif_rx_mtr						(DTEIF_DTEIF._rx_mtr)
#define	dteif_tx_mtr						(DTEIF_DTEIF._tx_mtr)
#define	dteif_rx_raw_mtr					(DTEIF_DTEIF._rx_raw_mtr)
#define	dteif_tx_raw_mtr					(DTEIF_DTEIF._tx_raw_mtr)

#define	parm__dteif_v24_106					(DTEIF_DTEIF._parm_dteif_v24_106)
#define	parm__dteif_v24_107					(DTEIF_DTEIF._parm_dteif_v24_107)
#define	parm__dteif_v24_109					(DTEIF_DTEIF._parm_dteif_v24_109)
#define	parm__dteif_v24_110					(DTEIF_DTEIF._parm_dteif_v24_110)
#define	parm__dteif_v24_125					(DTEIF_DTEIF._parm_dteif_v24_125)
#define	parm__dteif_v24_132					(DTEIF_DTEIF._parm_dteif_v24_132)
#define	parm__dteif_v24_142					(DTEIF_DTEIF._parm_dteif_v24_142)
#define	parm__dteif_hook					(DTEIF_DTEIF._parm_dteif_hook)

#define	stat__dteif_v24_105					(DTEIF_DTEIF._stat_dteif_v24_105)
#define	stat__dteif_v24_108					(DTEIF_DTEIF._stat_dteif_v24_108)
#define	stat__dteif_v24_133					(DTEIF_DTEIF._stat_dteif_v24_133)

/* ************************************************************************* */

#endif /* _DTEIF_DTEIFD_H */
