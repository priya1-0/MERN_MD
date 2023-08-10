
/* ************************************************************************* */
/*
 *  general.h
 *
 *	(C) 1994 - 2006 VOCAL Technologies, Ltd.
 *
 *  ALL RIGHTS RESERVED.  PROPRIETARY AND CONFIDENTIAL.
 *
 *  VOCAL Technologies, Ltd.
 *  90A John Muir Drive.
 *  Buffalo, NY  14228
 *
 *  Product:    MODEM 101
 *
 *  Module:     GENERAL
 *
 *  This file contains the public declarations for the GENERAL module.
 *
 *  Revision Number:    $Revision$
 *  Revision Status:    $State$
 *  Last Modified:      $Date$
 *  Identification:     $Id$
 *
 *  Revision History:   $Log$
 *  Revision History:   Revision 1.1.24.1  2009/04/28 19:49:07  zhangn1
 *  Revision History:   SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *  Revision History:
 *
 */
/* ************************************************************************* */

#ifndef _GENERAL_GENERAL_H
#define _GENERAL_GENERAL_H

/* ************************************************************************* */

/* ************************************************************************* */

#define dsp_logx		dsp_log

#define CLEAR_BUFFER(length,buffer) \
		clear_buffer ((length)/(sizeof (fract)), buffer)

#define CLEAR_BUFFER32(length,buffer) \
		clear_buffer32 ((length)/(sizeof (fract32)), buffer)

#define CLEAR_BUFFER_SINT15(length,buffer) \
	    clear_buffer_sint15 ((length)/(sizeof (sint15)), buffer)

#define CLEAR_BUFFER_UINT16(length,buffer) \
		clear_buffer_uint16 ((length)/(sizeof (uint16)), buffer)

#define CLEAR_BUFFER40(length,buffer) \
		clear_buffer40 ((length)/(sizeof (fract40)), buffer)

/*
*/

#define INC_CIRC_POFFSET(__circ__poffset, __buff_size)				\
{																	\
	if (++__circ__poffset >= __buff_size)							\
		__circ__poffset = 0;										\
}

#define INC_CIRC_OFFSET_BY(__circ__offset, __buff__size, __inc)			\
{																		\
	__circ__offset += __inc;											\
	__circ__offset -= __circ__offset < __buff__size ? 0 : __buff__size;	\
}

#define DEC_CIRC_OFFSET_BY(__circ__offset, __buff__size, __dec)			\
{																		\
	__circ__offset -= __dec;											\
	__circ__offset += __circ__offset < 0 ? __buff__size : 0;			\
}

#define COPY_BUFFER_UINT16(dest, orig, size)		\
{													\
	int __cnt;										\
	uint16 *__orig_ptr = (orig);					\
	uint16 *__dest_ptr = (dest);					\
													\
	for (__cnt = size - 1; __cnt >= 0; __cnt--) {	\
		*__dest_ptr++ = *__orig_ptr++;				\
	}												\
}

#define COPY_BUFFER_FRACT(dest, orig, size)			\
{													\
	int __cnt;										\
	fract *__orig_ptr = (orig);						\
	fract *__dest_ptr = (dest);						\
													\
	for (__cnt = size - 1; __cnt >= 0; __cnt--) {	\
		*__dest_ptr++ = *__orig_ptr++;				\
	}												\
}

/* ************************************************************************* */

/*- MKHEADER Begin -*/

/* Global Routines: */

/* alog.c */
fract32 anti_log (fract logval);

/* arctan.c */
phase_t arctan (fract im, fract re);

/* biquad.c */
fract biquad (fract *data, const fract *coef, fract input, uint16 counter);

/* clearbuf.c */
void clear_buffer (int length, fract *buffer);
void clear_buffer32 (int length, fract32 *buffer32);
void clear_buffer40 (int length, fract40 *buffer40);
void clear_buffer_sint15 (int length, sint15 *ptr);
void clear_buffer_uint16 (int length, uint16 *ptr);
void CLEAR_BUFFER_ZONE (fract *buff, int buffer_size, int offset, int length);

/* db_conv.c */
fract convert_db_to_gain (int value_db);

/* divide.c */
fract DDLSSS (fract32 a, fract b);
ufract DDLSUU (ufract32 a, ufract b);
fract int_divide (fract32 a, fract b);

/* exponent.c */
sint15 EXPONENT (fract x);
sint15 EXPONENTL (fract32 x32);
sint15 EXPONENTE (fract40 x40);

/* inttwo.c */
fract two_point_interp (ufract res, uint16 ind, const fract *tab);

/* log.c */
fract dsp_log (fract40 input40);

/* longmult.c */
fract40 EMMSULS(fract32 x,ufract y);
fract40 EMMSSLL (fract32 x, fract32 y);
fract40 EMMUULS (ufract32 x, ufract y);
fract40 EMMSSLL_exact (fract32 x, fract32 y);

/* precsine.c */
void precision_sine (phase_t phase);

/* random.c */
void random_dsp (void);
void generic_rand16_update (void);
uint16 generic_rand16 (void);
uint32 generic_rand32 (void);
fract calibrated_18db_gaussian (void);
fract generic_gaussian (fract amplitude);
void generic_random_stir (uint16 entropy);
void generic_random_stir_string (const char *string);
void generic_random_init (void);
void generic_randomize (void);
uint16 generic_rand16_range (uint16 low, uint16 high);

/* sqroot.c */
fract square_root (fract32 input32);

/*- MKHEADER End -*/


/* ************************************************************************* */

#endif /* _GENERAL_GENERAL_H */
