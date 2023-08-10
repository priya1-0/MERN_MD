
/* ************************************************************************* */
/*
 *	v34ph3st.h
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
 *	This file contains struct definitions cmn files.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 19:33:25  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _DATA_V34PH3ST_H
#define _DATA_V34PH3ST_H

/* ************************************************************************* */

typedef struct {
	uint16  count;
	fract40	energy48;
} mse_struct;

typedef struct {
	const fract *v34_interpolator_coefs;
	sint15 v34_interpolator_coefs_length;
	const fract *rx_lpf_coef;
	sint15 rx_lpf_coef_length;
	const ufract *tx_gain_adjust_table;
	sint15 tx_gain_adjust_table_length;
	const ufract *rx_gain_adjust_table;
	sint15 rx_gain_adjust_table_length;
	const fract *trn2_data_maxrate_table;
	sint15 trn2_data_maxrate_table_length;
	const ufract *lo_preemph_adjust_table;
	sint15 lo_preemph_adjust_table_length;
	const ufract *hi_preemph_adjust_table;
	sint15 hi_preemph_adjust_table_length;
	const fract *preemph_coefs_1;
	sint15 preemph_coefs_1_length;
	const fract *preemph_coefs_6;
	sint15 preemph_coefs_6_length;
	const fract *lo_lo_preeq_coefs;
	sint15 lo_lo_preeq_coefs_length;
	const fract *lo_me_preeq_coefs;
	sint15 lo_me_preeq_coefs_length;
	const fract *lo_hi_preeq_coefs;
	sint15 lo_hi_preeq_coefs_length;
	const fract *hi_lo_preeq_coefs;
	sint15 hi_lo_preeq_coefs_length;
	const fract *hi_me_preeq_coefs;
	sint15 hi_me_preeq_coefs_length;
	const fract *hi_hi_preeq_coefs;
	sint15 hi_hi_preeq_coefs_length;
} v34_xx_data_t;

typedef struct {

	ufract txi_adjust;
	sint15 txi_count;
	sint15 txi_taps;
	phase_t txi_pll_count;

	ufract rxi_adjust;
	sint15 rxi_count;
	sint15 rxi_taps;
	phase_t rxi_pll_count;

	phase_t rxi_pll_count_x2;
	phase_t rxi_pll_half_adjust;

	sint15 tx_interpolator_size;
	sint15 rx_interpolator_size;

	sint15 MD_length_increment;
	ufract T_over_8K0_ratio;

	phase_t temp_lo_carrier;
	phase_t temp_hi_carrier;
} v34_xx_constant_t;

typedef struct {
	uint16 timer;
	fract  slew;
} eqc_slew_data_t;

/* ************************************************************************* */

#endif /* _DATA_V34PH3ST_H */
