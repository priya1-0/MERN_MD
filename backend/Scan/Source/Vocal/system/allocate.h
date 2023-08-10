
/* ************************************************************************* */
/*
 *	allocate.h
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
 *	Module:		SYSTEM
 *
 *	This file defines variable definition and usage macros.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 20:47:21  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _SYSTEM_ALLOCATE_H
#define _SYSTEM_ALLOCATE_H

/* ************************************************************************* */

#define SET_MVP(POINTER,CHAN)
#define CURRENT_CHANNEL 0
#define MCC_ENTRY()
#define MCC_EXIT()
#define SAVE_BG_MVP(A)
#define SAVE_BG_CURRENT_CHAN(A)
#define RSTR_BG_MVP(A)
#define RSTR_BG_CURRENT_CHAN(A)

#ifdef WE_ARE_DEFINING_VARIABLES
		#define EXTERN
		#define DEF_DATA(TYPE, MODULE) TYPE MODULE;
#define DEF_DATA_SYSTEM(TYPE, MODULE) TYPE MODULE;
		#define DEF_FAR_DATA(TYPE, MODULE)  TYPE far MODULE;
		#define DEF_HUGE_DATA(TYPE, MODULE)  TYPE huge MODULE;
#else /* WE_ARE_DEFINING_VARIABLES */
		#define EXTERN extern
#define DEF_DATA_SYSTEM(TYPE, MODULE) extern TYPE MODULE;
		#define DEF_DATA(TYPE, MODULE) extern TYPE MODULE;
		#define DEF_FAR_DATA(TYPE, MODULE)  extern TYPE far MODULE
		#define DEF_HUGE_DATA(TYPE, MODULE)  extern TYPE huge MODULE
#endif /* WE_ARE_DEFINING_VARIABLES */

#include "mdm/uniondec.h"
#include "mdm/include.h"

	#define USE_DATA(MODULE) MODULE
	#define USE_DATA_SYSTEM(MODULE) MODULE

/* ************************************************************************* */

#endif /* _SYSTEM_ALLOCATE_H */
