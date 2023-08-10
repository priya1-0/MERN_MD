
/* ************************************************************************* */
/*
 *	locald.h
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
 *	This file contains the private parameter declarations/definitions
 *	for the CSP module.
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

#ifndef _CSP_LOCALD_H
#define _CSP_LOCALD_H

#include "csp/config.h"

/* ************************************************************************* */

struct csp_control_entry {

	char	*c;

	uint16	cs_idx;
	uint8	num_bits;
	uint32	range_l;
	uint32	range_h;
	uint16	sr_idx;

	uint32	flags;
	uint8	bit_mask;
	uint8	bit_shift;
	uint32	default_val;

	char	*test_response;

	uint16	(*mid_level_fn)(void);
};

/* ************************************************************************* */

struct csp_dispatch_entry {
	char	c;
	uint8	flags;
	uint8	(*check_valid_cmd)(void);
	union {
		const struct csp_control_entry *control_ptr;
		const struct csp_dispatch_entry *dispatch_ptr;
	} cmd_select;
};

/* ************************************************************************* */

extern const struct csp_control_entry *csp_control_list [];

extern const struct csp_dispatch_entry far csp_dispatch_table [];

extern const struct csp_dispatch_entry far csp_std_dispatch_table [];
extern const struct csp_control_entry far csp_std_table_default [];
extern const struct csp_control_entry far csp_std_table_ampr [];
extern const struct csp_control_entry far csp_std_table_prct [];
extern const struct csp_control_entry far csp_std_table_slsh [];
extern const struct csp_control_entry far csp_std_table_astr [];
extern const struct csp_control_entry far csp_std_table_dash [];
extern const struct csp_control_entry far csp_std_table_plus [];
extern const struct csp_control_entry far csp_std_table_tlde [];
extern const struct csp_control_entry far csp_std_table_hash [];
extern const struct csp_control_entry far csp_std_table_doll [];

extern struct csp_control_entry far csp_std_table_sreg [];

/* ************************************************************************* */

typedef struct {

	/* Flag variables */
	bool	_testing_parameter;		/* Flag used to resolve special ranges */
	bool	_reading_parameter;		/* Flag used when examining parameters */
	bool	_setting_parameter;		/* Used when loading an S-register */
	bool	_clearing_parameter;	/* flag used when clearing parameters */
	bool	_parse_parameters;		/* Input parameter must be extracted specially */
	bool	_setting_defaults;		/* Flag used when setting up the defaults */
	uint32	_input_parm;			/* Input parameter extracted from command line */
	char	_string_parm [40];		/* temporary string for special cases. */
	char	*_cmdp;				/* Local copy of the CSP command line pointer */
	bool	_quiet_sreg;			/* Used when viewing an S-register, &V vs. S? */
	uint8	_temp_ampr_v_vals [10];	/* temporary values used for ampr_v */
	bool	_executing_ampr_v;		/* Specifies that do_ampr_v should be called */
	bool	_reading_profile_zero;	/* Specifies profile zero being read from */
	bool	_read_both_profiles;	/* Specifies that both profiles have been read */
	uint8	_table_index;			/* Index used throughout ampr_v.c */
	uint8	_output_value;			/* Value to be sent to the DTE */
	uint16	_debug_length;
	bool	_executing_debug;		/* Specifies that do_ampr_v should be called */
	uint32	_address;
	uint8	_data_type;			/* Specifies that do_ampr_v should be called */
	bool	_memory_type;			/* Specifies that do_ampr_v should be called */
	bool    _executing_astr_b;
	bool    _executing_astr_d;
	uint16  _astr_get_index;
	uint16  _astr_output_index;
	const struct csp_control_entry *_current_sreg;

} csp_local_t;

/* ************************************************************************* */

DEF_DATA(csp_local_t, csp_local)
#define CSP_LOCAL_DATA csp_local_t csp_local
#define CSP_LOCAL USE_DATA(csp_local)

/* ************************************************************************* */

#define csp__testing_parameter				(CSP_LOCAL._testing_parameter)
#define csp__reading_parameter				(CSP_LOCAL._reading_parameter)
#define csp__setting_parameter				(CSP_LOCAL._setting_parameter)
#define csp__clearing_parameter				(CSP_LOCAL._clearing_parameter)
#define csp__parse_parameters				(CSP_LOCAL._parse_parameters)
#define csp__setting_defaults				(CSP_LOCAL._setting_defaults)

#define csp__input_parm						(CSP_LOCAL._input_parm)
#define csp__string_parm					(CSP_LOCAL._string_parm)

#define csp__cmdp							(CSP_LOCAL._cmdp)

#define csp__quiet_sreg						(CSP_LOCAL._quiet_sreg)
#define csp__temp_ampr_v_vals				(CSP_LOCAL._temp_ampr_v_vals)
#define csp__reading_profile_zero			(CSP_LOCAL._reading_profile_zero)
#define csp__executing_ampr_v				(CSP_LOCAL._executing_ampr_v)
#define csp__read_both_profiles				(CSP_LOCAL._read_both_profiles)
#define csp__table_index					(CSP_LOCAL._table_index)
#define csp__output_value					(CSP_LOCAL._output_value)

#define csp__executing_debug				(CSP_LOCAL._executing_debug)
#define csp__debug_length					(CSP_LOCAL._debug_length)
#define csp__address						(CSP_LOCAL._address)
#define csp__data_type						(CSP_LOCAL._data_type)
#define csp__memory_type					(CSP_LOCAL._memory_type)

#define csp__executing_astr_b				(CSP_LOCAL._executing_astr_b)
#define csp__executing_astr_d				(CSP_LOCAL._executing_astr_d)
#define csp__astr_get_index					(CSP_LOCAL._astr_get_index)
#define csp__astr_output_index				(CSP_LOCAL._astr_output_index)
#define csp_current_sreg					(CSP_LOCAL._current_sreg)

#endif /* _CSP_LOCALD_H */
