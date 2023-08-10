
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
 *	Module:		CSC
 *
 *	This file contains the macros for the CSC module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 19:06:28  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _CSC_MACRO_H
#define _CSC_MACRO_H

/* ************************************************************************* */

#define e_cmd_result__h_ok		e_cmd_result__ok
#define e_cmd_result__j_error	e_cmd_result__i_error
#define e_cmd_result__j_ok		e_cmd_result__i_ok
#define e_cmd_result__k_error	e_cmd_result__error

#define e_disconnect_ack__d_ok	e_disconnect_ack__ok
#define e_disconnect_ack__e_nc	e_disconnect_ack__no_carrier
#define e_disconnect_ack__g_nc	e_disconnect_ack__f_nc
#define e_disconnect_ack__j_nc	e_disconnect_ack__i_nc
#define e_disconnect_ack__k_nc	e_disconnect_ack__no_carrier

#define e_halting__b			e_halting__a
#define e_halting__c			e_halting__a
#define e_halting__e_no_carrier	e_halting__no_carrier
#define e_halting__g_no_carrier	e_halting__f_no_carrier
#define e_halting__h_error		e_halting__error
#define e_halting__j_null		e_halting__i_null
#define e_halting__k_null		e_halting__null
#define e_halting__no_change	e_halting__common

#define e_on_hook_rsp__c		e_on_hook_rsp__a
#define e_on_hook_rsp__d_nc		e_on_hook_rsp__no_carrier
#define e_on_hook_rsp__e_nc		e_on_hook_rsp__no_carrier
#define e_on_hook_rsp__g_nc		e_on_hook_rsp__f_nc
#define e_on_hook_rsp__h_error	e_on_hook_rsp__error
#define e_on_hook_rsp__h_nc		e_on_hook_rsp__no_carrier
#define e_on_hook_rsp__j_error	e_on_hook_rsp__i_error
#define e_on_hook_rsp__k_error	e_on_hook_rsp__error

#define sr_cmd_process__d		sr_cmd_process__c

/* ************************************************************************* */

#endif /* _CSC_MACRO_H */
