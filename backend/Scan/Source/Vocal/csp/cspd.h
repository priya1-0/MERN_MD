
/* ************************************************************************* */
/*
 *	cspd.h
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
 *	Module:		CSP
 *
 *	This file contains the public parameter declarations/definitions for
 *	the CSP module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 18:24:09  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _CSP_CSPD_H
#define _CSP_CSPD_H

/* ************************************************************************* */

typedef struct {
	char	_dial_string [DIAL_STRING_SIZE];
	bool	_semicolon_found;
	uint16	_hash_cid;
	uint16	_astr_td;
	uint16	_astr_s91;
	uint16	_test_type;
	bool	_slsh_v;
	uint8	_tlde_vafx[9];
} csp_csp_t;

/* ************************************************************************* */

DEF_DATA(csp_csp_t, csp_csp)
#define CSP_CSP_DATA csp_csp_t csp_csp
#define CSP_CSP USE_DATA(csp_csp)

/* ************************************************************************* */

#define parm__csp_tlde_vafx					(CSP_CSP._tlde_vafx)
#define csp__slsh_v							(CSP_CSP._slsh_v)
#define csp__dial_string					(CSP_CSP._dial_string)
#define csp__semicolon_found				(CSP_CSP._semicolon_found)
#define csp__hash_cid						(CSP_CSP._hash_cid)
#define csp__astr_td						(CSP_CSP._astr_td)
#define csp__astr_s91						(CSP_CSP._astr_s91)
#define csp__test_type						(CSP_CSP._test_type)

#endif /* _CSP_CSPD_H */
