
/* ************************************************************************* */
/*
 *	profile.h
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
 *	This file binds the computational macros to specific operation sequences.
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

#ifndef _SYSTEM_PROFILE_H
#define _SYSTEM_PROFILE_H

/* ************************************************************************* */

double floor (double);

#define RANGE	(32768.*65536.)

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

#define MMSSRND(x,y)		FORMATLRND(LMMSS(x,y))
#define MMSURND(x,y)		FORMATLRND(LMMSU(x,y))
#define MMUSRND(x,y)		FORMATLRND(LMMUS(x,y))
#define MMUURND(x,y)		FORMATLRND(LMMUU(x,y))

#define LMMSSLS(x,y)		LFORMATE(EMMSSLS(x,y))
#define LMMSULS(x,y)		LFORMATE(EMMSULS(x,y))
#define LMMUULS(x,y)		LFORMATE(EMMUULS(x,y))

#define SHIFTE(x,y)			FORMATE(ESHIFTE(x,y))
#define SHIFTL(x,y)			FORMATL(LSHIFTL(x,y))
#define LSHIFT(x,y)			LSHIFTL(LFORMAT(x),y)
#define LSHIFTE(x,y)		LFORMATE(ESHIFTE(x,y))

#define NORMALIZE(x,y)		SHIFT(x,-(y))
#define NORMALIZEL(x,y)		SHIFTL(x,-(y))
#define NORMALIZEE(x,y)		SHIFTE(x,-(y))

#define MMSSRNDSAT(x,y)		FORMATERNDSAT(EMMSS(x,y))
#define EFORMATERNDSAT(x)	EFORMATESAT(EFORMATERND(x))

#define ABS(x)				(((x)<0)?-(x):+(x))

/* ************************************************************************* */

/* ************************************************************************* */
#define FRACT(x)			( ( fract  ) ((sint15)(x)) )
#define UFRACT(x)			( (ufract  ) ((uint16)(x)) )
#define LFRACT(x)			((( fract32)  (sint15)(x))<<16)
#define LUFRACT(x)			(((ufract32)  (uint16)(x))<<16)
#define LFRACTL(x)			( ( fract32) ((sint31)(x)) )
#define LUFRACTL(x)			( (ufract32) ((uint32)(x)) )

/* The TI 55X compiler is currently the only compiler that supports direct */
/* use of fractional math in hardware.  The following macros are designed */
/* in such a way as to optimize well with that compiler. */
/* */
/* Note that the longest data type for TI 55X is only 40 bits.  The type 'long long int' */
/* really just aliases the 40 bit accumulator, so in order to do 48 bit math */
/* we need to use function calls and structures. */
#define LMMSS(x,y)			LFORMATE(EMMSS(x,y))
#define LMMSU(x,y)			LFORMATE(EMMSU(x,y))
#define LMMUS(x,y)			LFORMATE(EMMUS(x,y))
#define LMMUU(x,y)			LFORMATE(EMMUU(x,y))

#define MMSS(x,y)			FORMATE(EMMSS(x,y))
#define MMSU(x,y)			FORMATE(EMMSU(x,y))
#define MMUS(x,y)			FORMATE(EMMUS(x,y))
#define MMUU(x,y)			FORMATE(EMMUU(x,y))

#define EMMSS(x,y)			((fract40)(( ( fract40)(( fract  )(x)) * ( fract40)(( fract)(y)) ) << 1))
#define EMMSU(x,y)			((fract40)(( ( fract40)(( fract  )(x)) * (ufract40)((ufract)(y)) ) << 1))
#define EMMUS(x,y)			((fract40)(( (ufract40)((ufract  )(x)) * ( fract40)(( fract)(y)) ) << 1))
#define EMMUU(x,y)			((fract40)(( (ufract40)((ufract  )(x)) * (ufract40)((ufract)(y)) ) << 1))

#define LIMMSS(x,y)			(( fract32)((( fract32)( fract)(x)) * (( fract32)( fract)(y))))
#define LIMMSU(x,y)			(( fract32)((( fract32)( fract)(x)) * ((ufract32)(ufract)(y))))
#define LIMMUS(x,y)			(( fract32)(((ufract32)(ufract)(x)) * (( fract32)( fract)(y))))
#define LIMMUU(x,y)			((ufract32)(((ufract32)(ufract)(x)) * ((ufract32)(ufract)(y))))

#define EIMMSS(x,y)			((fract40)((( fract32)( fract)(x)) * (( fract32)( fract)(y))))
#define EIMMSU(x,y)			((fract40)((( fract32)( fract)(x)) * ((ufract32)(ufract)(y))))
#define EIMMUS(x,y)			((fract40)(((ufract32)(ufract)(x)) * (( fract32)( fract)(y))))
#define EIMMUU(x,y)			((fract40)(((ufract32)(ufract)(x)) * ((ufract32)(ufract)(y))))

#define EMASS(x,y,z)		(EMMSS(x,y) + (fract40) z)

/* integer multiply, not fract */
#define IMMSS(x,y)			((sint15) (((sint15) (x)) * ((sint15) (y))))
#define IMMSU(x,y)			((sint15) (((sint15) (x)) * ((uint16) (y))))
#define IMMUS(x,y)			((sint15) (((uint16) (x)) * ((sint15) (y))))
#define IMMUU(x,y)			((uint16) (((uint16) (x)) * ((uint16) (y))))

/* ************************************************************************* */
/* long multiply support */
/* ************************************************************************* */

/* ************************************************************************* */
/* saturation */
/* ************************************************************************* */

#define FORMATESAT(x)		SATURATEE((fract40)(x))
#define LFORMATESAT(x)		LSATURATEE((fract40)(x))
#define EFORMATESAT(x)		ESATURATEE((fract40)(x))
#define ABSSAT(x)			((fract) ((fract) (x) == (fract) (0x8000) ? (fract) (0x7fff) : ABS (x)))
#define ADDSAT(x,y)			SATURATEE(EFORMAT(x) + EFORMAT(y))
#define ADDFSAT(x,y)		((fract) (((ufract)(x) >> 15) + (fract)(y)))
#define MMUURNDSAT(x,y)		FORMATERNDSAT(EMMUU(x,y))
#define LFORMATERNDSAT(x)	LFORMATESAT(EFORMATERND(x))
#define LMMSUSAT(x,y)		LFORMATESAT(EMMSU(x,y))

/* ************************************************************************* */
/* miscellaneous */
/* ************************************************************************* */

#define SHIFT(x,y)			( ( fract  ) ( ((y)<0) ? (( fract  )(x)>>(-(y))) : (( fract  )(x)<<(y)) ) )
#define USHIFT(x,y)			( (ufract  ) ( ((y)<0) ? ((ufract  )(x)>>(-(y))) : ((ufract  )(x)<<(y)) ) )
#define LSHIFTL(x,y)		( ( fract32) ( ((y)<0) ? (( fract32)(x)>>(-(y))) : (( fract32)(x)<<(y)) ) )
#define LUSHIFTL(x,y)		( (ufract32) ( ((y)<0) ? ((ufract32)(x)>>(-(y))) : ((ufract32)(x)<<(y)) ) )
#define ESHIFTE(x,y)		( ( fract40) ( ((y)<0) ? (( fract40)(x)>>(-(y))) : (( fract40)(x)<<(y)) ) )

#define LOGEXP(x)			FRACT(((sint15) (x)) << 10)

#define MAX(x,y)			((x) > (y) ? (x) : (y))
#define MIN(x,y)			((x) > (y) ? (y) : (x))
#define SIGN(x)				( (ufract) (x >= 0) ? 0 : 1)

#define LNORMALIZEL(x,y)	LSHIFTL(x,-(y))
#define ENORMALIZEE(x,y)	ESHIFTE(x,-(y))

#define NEG(x)				( fract  )   (( fract)   (-(x)))
#define LNEGL(x)			( fract32)   (( fract32) (-(x)))

/* ************************************************************************* */
/* formatting, rounding, and type conversion */
/* ************************************************************************* */

#define EFORMAT(x)			( ( fract40)((( fract32) ( fract  )(x)) << 16) )
#define EUFORMAT(x)			( (ufract40)(((ufract32) (ufract  )(x)) << 16) )
#define EFORMATL(x)			( (( fract40) ( fract32)(x))       )
#define EUFORMATL(x)		( ((ufract40) (ufract32)(x))       )

#define LFORMAT(x)			( (( fract32) ( fract  )(x)) << 16 )
#define LFORMATE(x)			( (( fract32) ( fract40)(x))       )

#define FORMATE(x)			( ( fract ) (( fract40)(x) >> 16))
#define FORMATL(x)			( ( fract ) (( fract32)(x) >> 16))
#define UFORMATL(x)			( (ufract ) ((ufract32)(x) >> 16))

#define FORMATLIRND(x)		(( fract )  ((  ( fract32)(x)           + 0x00004000L ) >> 15))

#define UFORMATLRND(x)		((ufract )  ((  (ufract32)(x)           + 0x00008000L ) >> 16))
#define FORMATLRND(x)		(( fract )  ((  ( fract32)(x)           + 0x00008000L ) >> 16))
#define FORMATERND(x)		(( fract )  (( (( fract32)(fract40)(x)) + 0x00008000L ) >> 16))

#define LFORMATLRND(x)		((fract32) (((  (fract32)(x) +          (0x00008000L)) >> 16) << 16))
#define EFORMATERND(x)		((fract40) (((  (fract40)(x) + (fract40)(0x00008000L)) >> 16) << 16))

#define LFORMATERND(x)		LFORMATE(EFORMATERND(x))

#define FORML(x32,msw,lsw)	(x32 = (fract32) ((((fract32) (msw)) << 16) + (ufract32) (lsw)))
#define PARTL(x32,msw,lsw) {lsw = (ufract) LOWERWORD (x32); msw = (fract) UPPERWORD (x32);}

#define US16(x)				((ufract  ) (( fract  ) (x)))
#define US32(x)				((ufract32) (( fract32) (x)))
#define SU16(x)				(( fract  ) ((ufract  ) (x)))
#define SU32(x)				(( fract32) ((ufract32) (x)))

#define EFRACT(x)			EFORMAT(FRACT(x))

#define LUFORMAT(x) 		(((ufract32)  (ufract  )(x))<<16)

#define MODULO(x)			( (fract  ) (x) )
#define LMODULOL(x)			( (fract32) (x) )

#define INTRND(x)			( (sint15) (( fract  )(x)) )
#define UINTRND(x)			( (uint16) ((ufract  )(x)) )
#define LINTRND(x)			(((sint31)  ( fract  )(x))<<16)
#define LUINTRND(x)			(((uint32)  (ufract  )(x))<<16)

#define INTLRND(x)			( (sint15) (( fract32)(x) >>16))
#define UINTLRND(x)			( (uint16) ((ufract32)(x) >>16))
#define LINTLRND(x)			( (sint31) (( fract32)(x)) )
#define LUINTLRND(x)		( (uint32) ((ufract32)(x)) )

#define INTTRUNC(x)			( (sint15) (( fract  )(x)      ) )
#define UINTTRUNC(x)		( (uint16) ((ufract  )(x)      ) )
#define INTLTRUNC(x)		( (sint15) (( fract32)(x) >> 16) )
#define UINTLTRUNC(x)		( (uint16) ((ufract32)(x) >> 16) )
#define ETRUNCE(x)			ESHIFTE(ESHIFTE(x, -16), 16)

#define FRACTDOUBLE(x)		( ( fract  ) floor(   (double)(( double )(x)*32768.)) )
#define LFRACTDOUBLE(x)		( ( fract32) floor(   (double)(( double )(x)*RANGE )) )
#define EFRACTDOUBLE(x)		( ( fract40)      (   (double)(( double )(x)*RANGE )) )
#define DOUBLEFRACT(x)		( ( double ) (( fract  )(x)/32768.) )
#define DOUBLEFRACTL(x)		( ( double ) (( fract32)(x)/RANGE ) )
#define DOUBLEFRACTE(x)		( ( double ) (( fract40)(x)/RANGE ) )

/* ************************************************************************* */

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */
/* inlined profile functions */
/* ************************************************************************* */

#include "system/profinl.h"

#endif /* _SYSTEM_PROFILE_H */
