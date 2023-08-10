
/* ************************************************************************* */
/*
 *	parmd.h
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
 *	This file contains the public definitions for the CSP module.
 *	Specifically, the intermediate and unsupported command set variables
 *	are defined here.
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

#ifndef _CSP_PARMD_H
#define _CSP_PARMD_H

#include "csp/config.h"

#define CSPC__NO_CS_IDX 0xFFFF
#define MAX_CSP_STRING_PARM_SIZE 40
typedef struct {
	bool	_contents_bool [CSP_NUMBER_OF_BOOL_COMMANDS];
	uint8	_contents_uint8 [CSP_NUMBER_OF_UINT8_COMMANDS];
	uint32	_contents_uint32 [CSP_NUMBER_OF_UINT32_COMMANDS];

	char	_vts_string[MAX_CSP_STRING_PARM_SIZE];
} csp_parm_t;

/* ************************************************************************* */

DEF_DATA(csp_parm_t, csp_parm)
#define CSP_PARM_DATA csp_parm_t csp_parm
#define CSP_PARM USE_DATA(csp_parm)

/* ************************************************************************* */

#define csp__contents_bool					(CSP_PARM._contents_bool)
#define csp__contents_uint8					(CSP_PARM._contents_uint8)
#define csp__contents_uint32				(CSP_PARM._contents_uint32)

#define parm__cs_slsh_v						csp__contents_uint8[CSP_SLASH_V]
#define csp__ms_1							csp__contents_uint8[CSP_MS_MOD]
#define csp__ms_2							csp__contents_uint8[CSP_MS_AM]
#define csp__ms_3							csp__contents_uint32[CSP_MS_MIN]
#define csp__ms_4							csp__contents_uint32[CSP_MS_MAX]
#define parm__csp_func_z					csp__contents_bool[CSP_FUNC_Z]
#define stat__csc_ring_cntr					csp__contents_uint8[CSC_RING_CNTR]
#define stat__csc_disconnect_reason			csp__contents_uint8[CSC_DISCONNECT_REASON]
#define parm__csp_astr_vls					csp__contents_uint32[CSP_ASTR_VLS]
#define parm__csp_astr_s91					csp__contents_uint32[CSP_ASTR_S91]
#define parm__csp_default_profile			csp__contents_uint8[CSP_DEFAULT_PROFILE]
/* #define parm__csp_sreg_number				csp__contents_uint8[CSP_SREG_NUMBER] */
#define parm__cs_sreg_s00					csp__contents_uint8[CSP_SREG_S00]
#define parm__cs_sreg_s01					csp__contents_uint8[CSP_SREG_S01]
#define parm__cs_sreg_s02					csp__contents_uint8[CSP_SREG_S02]
#define parm__cs_sreg_s03					csp__contents_uint8[CSP_SREG_S03]
#define parm__cs_sreg_s04					csp__contents_uint8[CSP_SREG_S04]
#define parm__cs_sreg_s05					csp__contents_uint8[CSP_SREG_S05]
#define parm__cs_sreg_s06					csp__contents_uint8[CSP_SREG_S06]
#define parm__cs_sreg_s07					csp__contents_uint8[CSP_SREG_S07]
#define parm__cs_sreg_s08					csp__contents_uint8[CSP_SREG_S08]
#define parm__cs_sreg_s09					csp__contents_uint8[CSP_SREG_S09]
#define parm__cs_sreg_s10					csp__contents_uint8[CSP_SREG_S10]
#define parm__cs_sreg_s11					csp__contents_uint8[CSP_SREG_S11]
#define parm__cs_sreg_s12					csp__contents_uint8[CSP_SREG_S12]
#define parm__cs_sreg_s14					csp__contents_uint8[CSP_SREG_S14]
#define parm__cs_sreg_s16					csp__contents_uint8[CSP_SREG_S16]
#define parm__cs_sreg_s18					csp__contents_uint8[CSP_SREG_S18]
#define parm__cs_sreg_s19					csp__contents_uint8[CSP_SREG_S19]
#define parm__cs_sreg_s20					csp__contents_uint8[CSP_SREG_S20]
#define parm__cs_sreg_s21					csp__contents_uint8[CSP_SREG_S21]
#define parm__cs_sreg_s22					csp__contents_uint8[CSP_SREG_S22]
#define parm__cs_sreg_s23					csp__contents_uint8[CSP_SREG_S23]
#define parm__cs_sreg_s24					csp__contents_uint8[CSP_SREG_S24]
#define parm__cs_sreg_s25					csp__contents_uint8[CSP_SREG_S25]
#define parm__cs_sreg_s26					csp__contents_uint8[CSP_SREG_S26]
#define parm__cs_sreg_s27					csp__contents_uint8[CSP_SREG_S27]
#define parm__cs_sreg_s28					csp__contents_uint8[CSP_SREG_S28]
#define parm__cs_sreg_s29					csp__contents_uint8[CSP_SREG_S29]
#define parm__cs_sreg_s30					csp__contents_uint8[CSP_SREG_S30]
#define parm__cs_sreg_s31					csp__contents_uint8[CSP_SREG_S31]
#define parm__cs_sreg_s32					csp__contents_uint8[CSP_SREG_S32]
#define parm__cs_sreg_s33					csp__contents_uint8[CSP_SREG_S33]
#define parm__cs_sreg_s36					csp__contents_uint8[CSP_SREG_S36]
#define parm__cs_sreg_s37					csp__contents_uint8[CSP_SREG_S37]
#define parm__cs_sreg_s38					csp__contents_uint8[CSP_SREG_S38]
#define parm__cs_sreg_s39					csp__contents_uint8[CSP_SREG_S39]
#define parm__cs_sreg_s40					csp__contents_uint8[CSP_SREG_S40]
#define parm__cs_sreg_s41					csp__contents_uint8[CSP_SREG_S41]
#define parm__cs_sreg_s46					csp__contents_uint8[CSP_SREG_S46]
#define parm__cs_sreg_s48					csp__contents_uint8[CSP_SREG_S48]
#define parm__cs_sreg_s80					csp__contents_uint8[CSP_SREG_S80]
#define parm__cs_sreg_s82					csp__contents_uint8[CSP_SREG_S82]
#define parm__cs_sreg_s86					csp__contents_uint8[CSP_SREG_S86]
#define parm__cs_sreg_s91					csp__contents_uint8[CSP_SREG_S91]
#define parm__cs_sreg_s92					csp__contents_uint8[CSP_SREG_S92]
#define parm__cs_sreg_s95					csp__contents_uint8[CSP_SREG_S95]
#define parm__cs_sreg_s99					csp__contents_uint8[CSP_SREG_S99]
#define parm__cs_sreg_s201					csp__contents_uint8[CSP_SREG_S201]
#define parm__cs_sreg_s202					csp__contents_uint8[CSP_SREG_S202]

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

#define csstd__slsh_v						parm__cs_slsh_v
#define csstd__func_z						parm__csp_func_z
#define csstd__astr_vls						parm__csp_astr_vls
#define csstd__astr_s91						parm__csp_astr_s91
#define csstd__default_profile				parm__csp_default_profile
/* #define csstd__sreg_number					parm__csp_sreg_number */
#define csstd__sreg_s00						parm__cs_sreg_s00
#define csstd__sreg_s01						parm__cs_sreg_s01
#define csstd__sreg_s02						parm__cs_sreg_s02
#define csstd__sreg_s03						parm__cs_sreg_s03
#define csstd__sreg_s04						parm__cs_sreg_s04
#define csstd__sreg_s05						parm__cs_sreg_s05
#define csstd__sreg_s06						parm__cs_sreg_s06
#define csstd__sreg_s07						parm__cs_sreg_s07
#define csstd__sreg_s08						parm__cs_sreg_s08
#define csstd__sreg_s09						parm__cs_sreg_s09
#define csstd__sreg_s10						parm__cs_sreg_s10
#define csstd__sreg_s11						parm__cs_sreg_s11
#define csstd__sreg_s12						parm__cs_sreg_s12
#define csstd__sreg_s14						parm__cs_sreg_s14
#define csstd__sreg_s16						parm__cs_sreg_s16
#define csstd__sreg_s18						parm__cs_sreg_s18
#define csstd__sreg_s19						parm__cs_sreg_s19
#define csstd__sreg_s20						parm__cs_sreg_s20
#define csstd__sreg_s21						parm__cs_sreg_s21
#define csstd__sreg_s22						parm__cs_sreg_s22
#define csstd__sreg_s23						parm__cs_sreg_s23
#define csstd__sreg_s24						parm__cs_sreg_s24
#define csstd__sreg_s25						parm__cs_sreg_s25
#define csstd__sreg_s26						parm__cs_sreg_s26
#define csstd__sreg_s27						parm__cs_sreg_s27
#define csstd__sreg_s28						parm__cs_sreg_s28
#define csstd__sreg_s29						parm__cs_sreg_s29
#define csstd__sreg_s30						parm__cs_sreg_s30
#define csstd__sreg_s31						parm__cs_sreg_s31
#define csstd__sreg_s32						parm__cs_sreg_s32
#define csstd__sreg_s33						parm__cs_sreg_s33
#define csstd__sreg_s36						parm__cs_sreg_s36
#define csstd__sreg_s37						parm__cs_sreg_s37
#define csstd__sreg_s38						parm__cs_sreg_s38
#define csstd__sreg_s39						parm__cs_sreg_s39
#define csstd__sreg_s40						parm__cs_sreg_s40
#define csstd__sreg_s41						parm__cs_sreg_s41
#define csstd__sreg_s46						parm__cs_sreg_s46
#define csstd__sreg_s48						parm__cs_sreg_s48
#define csstd__sreg_s80						parm__cs_sreg_s80
#define csstd__sreg_s82						parm__cs_sreg_s82
#define csstd__sreg_s86						parm__cs_sreg_s86
#define csstd__sreg_s91						parm__cs_sreg_s91
#define csstd__sreg_s92						parm__cs_sreg_s92
#define csstd__sreg_s95						parm__cs_sreg_s95
#define csstd__sreg_s99						parm__cs_sreg_s99
#define csstd__sreg_s201					parm__cs_sreg_s201
#define csstd__sreg_s202					parm__cs_sreg_s202

#define csstd__dial_string					csp__dial_string
#define csstd__semicolon_found				csp__semicolon_found
#define csstd__ms_1							csp__ms_1
#define csstd__ms_2							csp__ms_2
#define csstd__ms_3							csp__ms_3
#define csstd__ms_4							csp__ms_4
/* #define csstd__hash_cid					csp__hash_cid
#define csstd__astr_td						csp__astr_td
#define csstd__astr_s91						csp__astr_s91 */
#define csstd__test_type					csp__test_type

#endif /* _CSP_PARMD_H */
