
/* ************************************************************************* */
/*
 *	print.h
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
 *	This file defines the printing control according to module grouping.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 20:47:21  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _SYSTEM_PRINT_H
#define _SYSTEM_PRINT_H

/* ************************************************************************* */

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */
/*
 *	Print control masks
 */

#define PRINT_CONTROL__STD					0x0001
#define PRINT_CONTROL__ERROR				0x0002
#define PRINT_CONTROL__WARNING				0x0004
#define PRINT_CONTROL__INFO					0x0008

#define PRINT_CONTROL__DIAG					0x0010
#define PRINT_CONTROL__DEBUG				0x0020
#define PRINT_CONTROL__DEV					0x0040
#define PRINT_CONTROL__STATUS				0x0080		/* Special for event and status reporting */

#define PRINT_CONTROL__PROTOCOL_ERROR		0x0100
#define PRINT_CONTROL__PROTOCOL_WARNING		0x0200
#define PRINT_CONTROL__PROTOCOL_INFO		0x0400
#define PRINT_CONTROL__PROTOCOL_DETAIL		0x0800

#define PRINT_CONTROL__SYSLOG_SEND			0x1000
#define PRINT_CONTROL__SYSLOG_LOCAL			0x2000
#define PRINT_CONTROL__DEBUGLOG_SEND		0x4000
#define PRINT_CONTROL__PERIODIC				0x8000

#define PRINT_CONTROL_ALL	0xffff

/* ************************************************************************* */
/*
 *	Assign module groups to share common control variables
 */
#define print_control_mask 0xffff

#ifdef ATA_MODULE_GROUP
#undef  print_control_mask
#define print_control_mask parm__net_debug_level_ata
#endif /* ATA_MODULE_GROUP */

#ifdef SYS_MODULE_GROUP
#undef  print_control_mask
#define print_control_mask parm__net_debug_level_ata
#endif /* SYS_MODULE_GROUP */

#ifdef SIP_MODULE_GROUP
#undef  print_control_mask
#define print_control_mask parm__net_debug_level_sip
#endif /* SIP_MODULE_GROUP */

#ifdef MGCP_MODULE_GROUP
#undef  print_control_mask
#define print_control_mask parm__net_debug_level_mgcp
#endif /* MGCP_MODULE_GROUP */

#ifdef VOIP_MODULE_GROUP
#undef  print_control_mask
#define print_control_mask parm__net_debug_level_net
#endif /* VOIP_MODULE_GROUP */

#ifdef NET_MODULE_GROUP
#undef  print_control_mask
#define print_control_mask parm__net_debug_level_net
#endif /* NET_MODULE_GROUP */

#ifdef MDM_MODULE_GROUP
#undef  print_control_mask
#define print_control_mask parm__net_debug_level_omc
#endif /* MDM_MODULE_GROUP */

#ifdef PMP_MODULE_GROUP
#undef  print_control_mask
#define print_control_mask parm__net_debug_level_pmp
#endif /* PMP_MODULE_GROUP */

#ifdef VIDEO_MODULE_GROUP
#undef  print_control_mask
#define print_control_mask parm__net_debug_level_video
#endif /* VIDEO_MODULE_GROUP */

#ifdef VPPN_MODULE_GROUP
#undef  print_control_mask
#define print_control_mask parm__net_debug_level_vppn
#endif /* VPPN_MODULE_GROUP */

/* ************************************************************************* */
/*
 *	Print macros
 */

#define fg_print_diag_off(A)
#define fg_print_debug_off(A)

#define print_diag_off(A)
#define print_debug_off(A)
#define print_dev_off(A)
#define print_routine_off(A)

/* ************************************************************************* */

/* ************************************************************************* */

/*
 *	Assign print routine according to features supported
 */
#define report_anomaly(A)		report_anomaly_routine (A)

#define fg_print_routine(A)		print_routine A
#define fg_vprint_routine(A)	vprint_routine A

#define bg_print_routine(A)		printf A
#define bg_vprint_routine(A)	vprintf A

/* ************************************************************************* */

/*
 * Foreground must use special print macros
 */
#define fg_print_primary(A)		fg_print_routine_primary A
#define fg_print_primary_nh(A)	fg_print_routine (A)
#define bg_print_primary(A)		bg_print_routine_primary A
#define bg_print_primary_nh(A)	bg_print_routine (A)

#define fg_print_std(A)			if (print_control_mask & PRINT_CONTROL__STD) fg_print_routine_std A
#define fg_print_std_nh(A)		if (print_control_mask & PRINT_CONTROL__STD) fg_print_routine (A)
#define fg_print_error(A)		if (print_control_mask & PRINT_CONTROL__ERROR) fg_print_routine_error A
#define fg_print_error_nh(A)	if (print_control_mask & PRINT_CONTROL__ERROR) fg_print_routine (A)
#define fg_print_warning(A)		if (print_control_mask & PRINT_CONTROL__WARNING) fg_print_routine_warning A
#define fg_print_warning_nh(A)	if (print_control_mask & PRINT_CONTROL__WARNING) fg_print_routine (A)
#define fg_print_info(A)		if (print_control_mask & PRINT_CONTROL__INFO) fg_print_routine_info A
#define fg_print_info_nh(A)		if (print_control_mask & PRINT_CONTROL__INFO) fg_print_routine (A)

#define fg_print_std_periodic(A)		if ((print_control_mask & (PRINT_CONTROL__STD | PRINT_CONTROL__PERIODIC)) == (PRINT_CONTROL__STD | PRINT_CONTROL__PERIODIC)) fg_print_routine_std A
#define fg_print_std_periodic_nh(A)		if ((print_control_mask & (PRINT_CONTROL__STD | PRINT_CONTROL__PERIODIC)) == (PRINT_CONTROL__STD | PRINT_CONTROL__PERIODIC)) fg_print_routine (A)
#define fg_print_warning_periodic(A)	if ((print_control_mask & (PRINT_CONTROL__WARNING | PRINT_CONTROL__PERIODIC)) == (PRINT_CONTROL__WARNING | PRINT_CONTROL__PERIODIC)) fg_print_routine_warning A
#define fg_print_warning_periodic_nh(A)	if ((print_control_mask & (PRINT_CONTROL__WARNING | PRINT_CONTROL__PERIODIC)) == (PRINT_CONTROL__WARNING | PRINT_CONTROL__PERIODIC)) fg_print_routine (A)
#define fg_print_info_periodic(A)		if ((print_control_mask & (PRINT_CONTROL__INFO | PRINT_CONTROL__PERIODIC)) == (PRINT_CONTROL__INFO | PRINT_CONTROL__PERIODIC)) fg_print_routine_info A
#define fg_print_info_periodic_nh(A)	if ((print_control_mask & (PRINT_CONTROL__INFO | PRINT_CONTROL__PERIODIC)) == (PRINT_CONTROL__INFO | PRINT_CONTROL__PERIODIC)) fg_print_routine (A)

#define fg_print_diag_on(A)		if (print_control_mask & PRINT_CONTROL__DIAG) fg_print_routine_diag A
#define fg_print_diag_on_nh(A)	if (print_control_mask & PRINT_CONTROL__DIAG) fg_print_routine (A)
#define fg_print_debug_on(A) 	if (print_control_mask & PRINT_CONTROL__DEBUG) fg_print_routine_dev A
#define fg_print_debug_on_nh(A) if (print_control_mask & PRINT_CONTROL__DEBUG) fg_print_routine (A)
#define fg_print_dev_on(A)		if (print_control_mask & PRINT_CONTROL__DEV) fg_print_routine_dev A
#define fg_print_dev_on_nh(A)	if (print_control_mask & PRINT_CONTROL__DEV) fg_print_routine (A)

#define fg_print_diag_on_periodic(A)		if ((print_control_mask & (PRINT_CONTROL__DIAG | PRINT_CONTROL__PERIODIC)) == (PRINT_CONTROL__DIAG | PRINT_CONTROL__PERIODIC)) fg_print_routine_diag A
#define fg_print_diag_on_periodic_nh(A)		if ((print_control_mask & (PRINT_CONTROL__DIAG | PRINT_CONTROL__PERIODIC)) == (PRINT_CONTROL__DIAG | PRINT_CONTROL__PERIODIC)) fg_print_routine (A)
#define fg_print_debug_on_periodic(A)		if ((print_control_mask & (PRINT_CONTROL__DEBUG | PRINT_CONTROL__PERIODIC)) == (PRINT_CONTROL__DEBUG | PRINT_CONTROL__PERIODIC)) fg_print_routine_debug A
#define fg_print_debug_on_periodic_nh(A)	if ((print_control_mask & (PRINT_CONTROL__DEBUG | PRINT_CONTROL__PERIODIC)) == (PRINT_CONTROL__DEBUG | PRINT_CONTROL__PERIODIC)) fg_print_routine (A)
#define fg_print_dev_on_periodic(A)			if ((print_control_mask & (PRINT_CONTROL__DEV | PRINT_CONTROL__PERIODIC)) == (PRINT_CONTROL__DEV | PRINT_CONTROL__PERIODIC)) fg_print_routine_dev A
#define fg_print_dev_on_periodic_nh(A)		if ((print_control_mask & (PRINT_CONTROL__DEV | PRINT_CONTROL__PERIODIC)) == (PRINT_CONTROL__DEV | PRINT_CONTROL__PERIODIC)) fg_print_routine (A)

#if !defined (PMP_MODULE_GROUP) && !defined (VIDEO_MG_MODULE)
/*
 * Background print macros
 */
#define print_primary(A)		bg_print_routine_primary A
#define print_primary_nh(A)		bg_print_routine (A)

#define print_std(A)			if (print_control_mask & PRINT_CONTROL__STD) bg_print_routine_std A
#define print_std_nh(A)			if (print_control_mask & PRINT_CONTROL__STD) bg_print_routine (A)
#define print_error(A)			if (print_control_mask & PRINT_CONTROL__ERROR) bg_print_routine_error A
#define print_error_nh(A)		if (print_control_mask & PRINT_CONTROL__ERROR) bg_print_routine (A)
#define print_warning(A)		if (print_control_mask & PRINT_CONTROL__WARNING) bg_print_routine_warning A
#define print_warning_nh(A)		if (print_control_mask & PRINT_CONTROL__WARNING) bg_print_routine (A)
#define print_info(A)			if (print_control_mask & PRINT_CONTROL__INFO) bg_print_routine_info A
#define print_info_nh(A)		if (print_control_mask & PRINT_CONTROL__INFO) bg_print_routine (A)

#define print_std_periodic(A)			if ((print_control_mask & (PRINT_CONTROL__STD | PRINT_CONTROL__PERIODIC)) == (PRINT_CONTROL__STD | PRINT_CONTROL__PERIODIC))			bg_print_routine_std A
#define print_std_periodic_nh(A)		if ((print_control_mask & (PRINT_CONTROL__STD | PRINT_CONTROL__PERIODIC)) == (PRINT_CONTROL__STD | PRINT_CONTROL__PERIODIC))			bg_print_routine (A)
#define print_warning_periodic(A)		if ((print_control_mask & (PRINT_CONTROL__WARNING | PRINT_CONTROL__PERIODIC)) == (PRINT_CONTROL__WARNING | PRINT_CONTROL__PERIODIC))	bg_print_routine_warning A
#define print_warning_periodic_nh(A)	if ((print_control_mask & (PRINT_CONTROL__WARNING | PRINT_CONTROL__PERIODIC)) == (PRINT_CONTROL__WARNING | PRINT_CONTROL__PERIODIC))	bg_print_routine (A)
#define print_info_periodic(A)			if ((print_control_mask & (PRINT_CONTROL__INFO | PRINT_CONTROL__PERIODIC)) == (PRINT_CONTROL__INFO | PRINT_CONTROL__PERIODIC))			bg_print_routine_info A
#define print_info_periodic_nh(A)		if ((print_control_mask & (PRINT_CONTROL__INFO | PRINT_CONTROL__PERIODIC)) == (PRINT_CONTROL__INFO | PRINT_CONTROL__PERIODIC))			bg_print_routine (A)

#define print_diag_on(A)		if (print_control_mask & PRINT_CONTROL__DIAG) bg_print_routine_diag A
#define print_diag_on_nh(A)		if (print_control_mask & PRINT_CONTROL__DIAG) bg_print_routine (A)
#define print_debug_on(A)		if (print_control_mask & PRINT_CONTROL__DEBUG) bg_print_routine_debug A
#define print_debug_on_nh(A)	if (print_control_mask & PRINT_CONTROL__DEBUG) bg_print_routine (A)
#define print_dev_on(A)			if (print_control_mask & PRINT_CONTROL__DEV) bg_print_routine_dev A
#define print_dev_on_nh(A)		if (print_control_mask & PRINT_CONTROL__DEV) bg_print_routine (A)

#define print_diag_on_periodic(A)		if ((print_control_mask & (PRINT_CONTROL__DIAG | PRINT_CONTROL__PERIODIC)) == (PRINT_CONTROL__DIAG | PRINT_CONTROL__PERIODIC))		bg_print_routine_diag A
#define print_diag_on_periodic_nh(A)	if ((print_control_mask & (PRINT_CONTROL__DIAG | PRINT_CONTROL__PERIODIC)) == (PRINT_CONTROL__DIAG | PRINT_CONTROL__PERIODIC))		bg_print_routine (A)
#define print_debug_on_periodic(A)		if ((print_control_mask & (PRINT_CONTROL__DEBUG | PRINT_CONTROL__PERIODIC)) == (PRINT_CONTROL__DEBUG | PRINT_CONTROL__PERIODIC))	bg_print_routine_debug A
#define print_debug_on_periodic_nh(A)	if ((print_control_mask & (PRINT_CONTROL__DEBUG | PRINT_CONTROL__PERIODIC)) == (PRINT_CONTROL__DEBUG | PRINT_CONTROL__PERIODIC))	bg_print_routine (A)
#define print_dev_on_periodic(A)		if ((print_control_mask & (PRINT_CONTROL__DEV | PRINT_CONTROL__PERIODIC)) == (PRINT_CONTROL__DEV | PRINT_CONTROL__PERIODIC))		bg_print_routine_dev A
#define print_dev_on_periodic_nh(A)		if ((print_control_mask & (PRINT_CONTROL__DEV | PRINT_CONTROL__PERIODIC)) == (PRINT_CONTROL__DEV | PRINT_CONTROL__PERIODIC))		bg_print_routine (A)

#define protocol_error(A)		if (print_control_mask & PRINT_CONTROL__PROTOCOL_ERROR) bg_print_routine_protocol_error A
#define protocol_error_nh(A)	if (print_control_mask & PRINT_CONTROL__PROTOCOL_ERROR) bg_print_routine (A)
#define protocol_warning(A)		if (print_control_mask & PRINT_CONTROL__PROTOCOL_WARNING) bg_print_routine_protocol_warning A
#define protocol_warning_nh(A)	if (print_control_mask & PRINT_CONTROL__PROTOCOL_WARNING) bg_print_routine (A)
#define protocol_info(A)		if (print_control_mask & PRINT_CONTROL__PROTOCOL_INFO) bg_print_routine_protocol_info A
#define protocol_info_nh(A)		if (print_control_mask & PRINT_CONTROL__PROTOCOL_INFO) bg_print_routine (A)
#define protocol_detail(A)		if (print_control_mask & PRINT_CONTROL__PROTOCOL_DETAIL) bg_print_routine_protocol_detail A
#define protocol_detail_nh(A)	if (print_control_mask & PRINT_CONTROL__PROTOCOL_DETAIL) bg_print_routine (A)

#define protocol_warning_periodic(A)	if ((print_control_mask & (PRINT_CONTROL__PROTOCOL_WARNING | PRINT_CONTROL__PERIODIC)) == (PRINT_CONTROL__PROTOCOL_WARNING | PRINT_CONTROL__PERIODIC))	bg_print_routine_protocol_warning A
#define protocol_warning_periodic_nh(A)	if ((print_control_mask & (PRINT_CONTROL__PROTOCOL_WARNING | PRINT_CONTROL__PERIODIC)) == (PRINT_CONTROL__PROTOCOL_WARNING | PRINT_CONTROL__PERIODIC))	bg_print_routine (A)
#define protocol_info_periodic(A)		if ((print_control_mask & (PRINT_CONTROL__PROTOCOL_INFO | PRINT_CONTROL__PERIODIC)) == (PRINT_CONTROL__PROTOCOL_INFO | PRINT_CONTROL__PERIODIC))		bg_print_routine_protocol_info
#define protocol_info_periodic_nh(A)	if ((print_control_mask & (PRINT_CONTROL__PROTOCOL_INFO | PRINT_CONTROL__PERIODIC)) == (PRINT_CONTROL__PROTOCOL_INFO | PRINT_CONTROL__PERIODIC))		bg_print_routine (A)
#define protocol_detail_periodic(A)		if ((print_control_mask & (PRINT_CONTROL__PROTOCOL_DETAIL | PRINT_CONTROL__PERIODIC)) == (PRINT_CONTROL__PROTOCOL_DETAIL | PRINT_CONTROL__PERIODIC))	bg_print_routine_protocol_detail
#define protocol_detail_periodic_nh(A)	if ((print_control_mask & (PRINT_CONTROL__PROTOCOL_DETAIL | PRINT_CONTROL__PERIODIC)) == (PRINT_CONTROL__PROTOCOL_DETAIL | PRINT_CONTROL__PERIODIC))	bg_print_routine (A)

#endif /* !PMP_MODULE_GROUP && !VIDEO_MG_MODULE */

/* ************************************************************************* */

#ifndef print_debug_on
#define print_debug_on Error_print_debug_on_not_defined_for_foreground error error error
#endif /* print_debug_on */

/* ************************************************************************* */

#endif /* _SYSTEM_PRINT_H */
