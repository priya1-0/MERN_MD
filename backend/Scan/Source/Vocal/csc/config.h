
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
 *	Module:		CSC
 *
 *	This file defines array sizes for variables related to the
 *	CSC module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.3  2009/05/27 20:29:31  zhangn1
 *	Revision History:	SCR #175480. Add new country support for Congo release
 *	Revision History:	
 *	Revision History:	Revision 1.5  2008/08/13 15:37:20  zhangn1
 *	Revision History:	SCR #152765. Vocal International telephone update
 *	Revision History:	
 *	Revision History:	Revision 1.4  2007/10/16 16:40:01  zhangn1
 *	Revision History:	SCR #149144. Integration Vocal M6+ to 2490C
 *	Revision History:	
 *
 */
/* ************************************************************************* */
#ifndef _CSC_CONFIG_H
#define _CSC_CONFIG_H

#include "include/config.h"

/* ************************************************************************* */

#define CSC_DIAL_STRING_SIZE		61
#define CSC_URESPONSE_BUFFER_SIZE	5


/* ************************************************************************* */

#define DTE_TX_BUFFER_SIZE			512
#define DTE_RX_BUFFER_SIZE			512
#define DTE_TX_CMD_SIZE				60
#define DTE_TX_MISC_SIZE			3
#define CSC_ECHO_BUFFER_SIZE		DTE_TX_CMD_SIZE	+ 4
#define RESPONSE_BUFFER_SIZE 		128

#define DTE_TX_XOFF_THRESHOLD		384		/* ~75% of DTE_TX_BUFFER_SIZE	*/
#define DTE_TX_XON_THRESHOLD		128		/* ~25% of DTE_TX_BUFFER_SIZE	*/
#define DTE_TX_XOFF_CRITICAL		432		/* ~85% of DTE_TX_BUFFER_SIZE	*/



/* ************************************************************************* */

#define ITEL_COUNTRY_ENTRY_MAX			62

#define DAA_ITEL_COUNTRY_ENTRY_MAX 82



/* ************************************************************************* */

#endif /* _CSC_CONFIG_H */
