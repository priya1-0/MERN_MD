
/* ************************************************************************* */
/*
 *	sections.h
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
 *	Module:		DATA
 *
 *  This file is used to move structures from the data dir to their own sections
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 19:33:26  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

/* ************************************************************************* */

#ifdef WE_ARE_DEFINING_VARIABLES
#ifndef BUILDING_OFFSETS


/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

#ifndef SECTIONS_DECLARED
#define SECTIONS_DECLARED
#pragma DATA_SECTION(cmn_parms,".cmn_parms");
#pragma DATA_SECTION(omc_parm,".omc_parms");
#pragma DATA_SECTION(cmn_vars,".cmn_vars");
#pragma DATA_SECTION(mod_vars,".mod_vars");
#pragma DATA_SECTION(v34_vars,".v34_vars");
#pragma DATA_SECTION(ph2_vars,".ph2_vars");
#pragma DATA_SECTION(ph2_local,".ph2_local");
#pragma DATA_SECTION(sys_shared,".sys_shared");
#pragma DATA_SECTION(dteif_local,".dteif_local");
#pragma DATA_SECTION(dteif_dteif,".dteif_dteif");
#pragma DATA_SECTION(tel_vars,".tel_vars");
#pragma DATA_SECTION(tel_debug,".tel_debug");
#pragma DATA_SECTION(mod_fast,".mod_fast");
#pragma DATA_SECTION(cmn_fast,".cmn_fast");
#pragma DATA_SECTION(v34_fast,".v34_fast");
#pragma DATA_SECTION(tel_fast,".tel_fast");
#pragma DATA_SECTION(cmn_const,".cmn_const");
#pragma DATA_SECTION(cmn_debug,".cmn_debug");
#pragma DATA_SECTION(v34_stats,".v34_stats");
#pragma DATA_SECTION(v34_debug,".v34_debug");
#pragma DATA_SECTION(v34_local,".v34_local");

#endif /* SECTIONS_DECLARED */




#endif /* BUILDING_OFFSETS */
#endif /* WE_ARE_DEFINING_VARIABLES */

/* ************************************************************************* */
