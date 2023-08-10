
/* ************************************************************************* */
/*
 *	csp.h
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
 *	This file contains the public declarations for the CSP module.
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

#ifndef _CSP_CSP_H
#define _CSP_CSP_H

#include "csp/cspd.h"
#include "csp/parmd.h"
#include "csp/config.h"
#include "bind/bind.h"

/* ************************************************************************* */

#define CSP_CODE__DONE						0
#define CSP_CODE__CONTINUE					1
#define CSP_CODE__ERROR_INVALID				2
#define CSP_CODE__ERROR_UNRECOGNIZED		3
#define CSP_CODE__ERROR_RANGE				4
#define CSP_CODE__ACTION					5
#define CSP_CODE__RESPONSE					6
#define CSP_CODE__ACCESS					7

/* ************************************************************************* */

#define CSP_ACTION__ON_HOOK					0
#define CSP_ACTION__OFF_HOOK				1
#define CSP_ACTION__DIAL					2
#define CSP_ACTION__CONNECT					3
#define CSP_ACTION__ONLINE					4
#define CSP_ACTION__FAX_ACTION_1			5
#define CSP_ACTION__FAX_ACTION_2			6
#define CSP_ACTION__NVM_XXX					7
#define CSP_ACTION__TEST_RDLB				8
#define CSP_ACTION__RDLB					8
#define CSP_ACTION__TEST_TX					10
#define CSP_ACTION__TEST_TX2				11
#define CSP_ACTION__TEST_TD					12
#define CSP_ACTION__TEST_V13				13
#define CSP_ACTION__RESET_REQUEST			14
#define CSP_ACTION__VOICE_RX				15
#define CSP_ACTION__VOICE_TX				16
#define CSP_ACTION__VOICE_VTS				17
#define CSP_ACTION__VOICE_VXT				18
#define CSP_ACTION__VOICE_VLS				19
#define CSP_ACTION__FCLASS_CHANGE			20

/* ************************************************************************* */

#define FCLASS_0							0
#define FCLASS_1							1
#define FCLASS_1_0							2
#define FCLASS_2							3
#define FCLASS_2_0							4
#define FCLASS_2_1							5
#define FCLASS_8							6

/* ************************************************************************* */

#define CSP_OPCODE__NOP						0

#define CSP_OPCODE__FX1_FRM					1
#define CSP_OPCODE__FX1_FTM					2
#define CSP_OPCODE__FX1_FTH					3
#define CSP_OPCODE__FX1_FRH					4
#define CSP_OPCODE__FX1_FRS					5
#define CSP_OPCODE__FX1_FTS					6

#define CSP_OPCODE__FX1_ANSWER				7
#define CSP_OPCODE__FX1_ORIGINATE			8
#define CSP_OPCODE__FX2_ANSWER				9
#define CSP_OPCODE__FX2_ORIGINATE			10
#define CSP_OPCODE__FX2_VOICE_ANSWER		11
#define CSP_OPCODE__FX2_VOICE_ORIGINATE		12
#define CSP_OPCODE__FX2_FDT					13
#define CSP_OPCODE__FX2_FDR					14
#define CSP_OPCODE__FX2_FK					15
#define CSP_OPCODE__FX2_FET					16

#define CSP_OPCODE__FCLASS_8_ENTRY			20
#define CSP_OPCODE__FCLASS_8_EXIT			21

/* ************************************************************************* */

/*- MKHEADER Begin -*/

/* Global Routines: */

/* csp.c */
void csp_module_reset (void);
void csp__set_answer (void);
void csp__nvm_start (void);
void csp__set_default_values (void);
void csp__change_default_sreg_value (uint16 sreg_idx, uint32 new_val);
void csp__process_response_continue (void);
uint16 csp_read_value (uint16 this_entry, uint8 bit_mask, uint8 bit_shift);
uint16 csp_write_value (uint16 this_entry, uint8 hex_value, uint8 bit_mask, uint8 bit_shift);

/* m_std.c */
void parse__global_reset_command_sets (void);

/* process.c */
void csp__process_cmd (void);

/*- MKHEADER End -*/


/* ************************************************************************* */

#endif /* _CSP_CSP_H */
