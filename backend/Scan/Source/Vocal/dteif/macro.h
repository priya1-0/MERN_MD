
/* ************************************************************************* */
/*
 *	macro.h
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
 *	This file contains the macros for the DTEIF module.
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

#ifndef _DTEIF_MACRO_H
#define _DTEIF_MACRO_H

/* ************************************************************************* */

#define macro__dteif_rts_on() {												\
																			\
	stat__dteif_v24_133 = TRUE;												\
	set_event (EVENT__DTEIF_RTS_ON);										\
	if (parm__sg_dce_by_dte_fc_uses_cts_en) {								\
		if (dteif_tx_state == DTEIF_TX_STATE__DTE_XOFF) {					\
			dteif_tx_state = DTEIF_TX_STATE__DTE;							\
		}																	\
		dteif_tx_start ();													\
	}																		\
}

#define macro__dteif_rts_off() {											\
																			\
	stat__dteif_v24_133 = FALSE;											\
	set_event (EVENT__DTEIF_RTS_OFF);										\
	if (parm__sg_dce_by_dte_fc_uses_cts_en) {								\
		if (dteif_tx_state == DTEIF_TX_STATE__DTE) {						\
			dteif_tx_state = DTEIF_TX_STATE__DTE_XOFF;						\
		}																	\
	}																		\
}

#define macro__dteif_dtr_on() {												\
																			\
	stat__dteif_v24_108 = TRUE;												\
	set_event (EVENT__DTEIF_DTR_ON);										\
}

#define macro__dteif_dtr_off() {											\
																			\
	stat__dteif_v24_108 = FALSE;											\
	set_event (EVENT__DTEIF_DTR_OFF);										\
}

/* ************************************************************************* */

#endif /* _DTEIF_MACRO_H */
