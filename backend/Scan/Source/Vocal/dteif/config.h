
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
 *	Module:		DTEIF
 *
 *	This file defines array sizes for variables related to the
 *	DTEIF module.
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

#ifndef _DTEIF_CONFIG_H
#define _DTEIF_CONFIG_H

/* ************************************************************************* */

/* This echo buffer does not need to be this large. */
/* In production use a value of 10. */
/* The reason for the large size, this is used as a chanel for debug info */

#define DTEIF_ECHO_BUFFER_SIZE 10

#define DTEIF_STORAGE_BUFFER_SIZE 80

#define DTEIF_NUM_READSTAT_HANDLES   2

#define DTEIF_AMOUNT_TO_READ   512
#define DTEIF_AMOUNT_TO_WRITE  512

#define DTEIF_MAX_WRITE_BUFFER     1024
#define DTEIF_MAX_READ_BUFFER      2048

#define DTEIF_STATUS_CHECK_TIMEOUT 0

#define DTEIF_EVENTFLAGS     (EV_BREAK | EV_CTS | EV_DSR | EV_ERR | EV_RING | EV_RLSD)
#define DTEIF_PURGE_FLAGS     (PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR)

/* ************************************************************************* */

#endif /* _DTEIF_CONFIG_H */
