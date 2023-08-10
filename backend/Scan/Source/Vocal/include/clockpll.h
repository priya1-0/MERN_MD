
/* ************************************************************************* */
/*
 *	clockpll.h
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
 *	Module:		INCLUDE
 *
 *	This file contains modem clocking PLL constants.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 19:50:34  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _INCLUDE_CLOCKPLL_H
#define _INCLUDE_CLOCKPLL_H

/* ************************************************************************* */

#define CLOCK_CYCLES_PER_BAUD__7200				2800
#define CLOCK_CYCLES_PER_BAUD__8000				2520
#define CLOCK_CYCLES_PER_BAUD__9600				2100

#define PLL_COUNT_FULL_BAUD_INT					20160			/* For use in assembly language ONLY */
#define PLL_COUNT_FULL_BAUD						PHASE(20160)	/* Least common multiple */
#define PLL_COUNT_HALF_BAUD						PHASE(10080)	/* Least common multiple */
#define PLL_COUNT_2_3RDS_BAUD					PHASE(13440)

/* ************************************************************************* */
/* BAUD counts for various sample rates */
/* ************************************************************************* */

#define PLL_COUNT_2400_BAUD_7200_SAMPLE			PHASE(6720)		/* V.32 and V.29 */
#define PLL_COUNT_1600_BAUD_7200_SAMPLE			PHASE(4480)		/* V.27ter 4800 baud */
#define PLL_COUNT_1200_BAUD_7200_SAMPLE			PHASE(3360)		/* V.23 originate and V.27ter 2400 baud */
#define PLL_COUNT_600_BAUD_7200_SAMPLE			PHASE(1680)		/* V.22 */
#define PLL_COUNT_300_BAUD_7200_SAMPLE			PHASE(840)		/* V.21 */
#define PLL_COUNT_75_BAUD_7200_SAMPLE			PHASE(210)		/* V.23 answer */

#define PLL_COUNT_3429_BAUD_8000_SAMPLE			PHASE(8640)
#define PLL_COUNT_3200_BAUD_8000_SAMPLE			PHASE(8064)
#define PLL_COUNT_3000_BAUD_8000_SAMPLE			PHASE(7560)
#define PLL_COUNT_2800_BAUD_8000_SAMPLE			PHASE(7056)
#define PLL_COUNT_2743_BAUD_8000_SAMPLE			PHASE(6912)
#define PLL_COUNT_2400_BAUD_8000_SAMPLE			PHASE(6048)
#define PLL_COUNT_1600_BAUD_8000_SAMPLE			PHASE(4032)
#define PLL_COUNT_1200_BAUD_8000_SAMPLE			PHASE(3024)
#define PLL_COUNT_600_BAUD_8000_SAMPLE			PHASE(1512)
#define PLL_COUNT_300_BAUD_8000_SAMPLE			PHASE(756)
#define PLL_COUNT_75_BAUD_8000_SAMPLE			PHASE(189)

#define PLL_COUNT_600_BAUD_9600_SAMPLE			PHASE(1260)	/* V.34 phase 2 */

/* ************************************************************************* */
/* rate conversion defines */
/* ************************************************************************* */

#define PLL_COUNT_1200_BAUD		PLL_COUNT_1200_BAUD_7200_SAMPLE
#define PLL_COUNT_300_BAUD		PLL_COUNT_300_BAUD_7200_SAMPLE
#define PLL_COUNT_75_BAUD		PLL_COUNT_75_BAUD_7200_SAMPLE

/* ************************************************************************* */

/* New constant for adjusting the interpolator to work with */
/* the reference point of 20160 instead of 3072             */
#define VXX_TXI_ADJUST							FRACT (0x4E05)

/* ************************************************************************* */
#endif /* _INCLUDE_CLOCKPLL_H */
