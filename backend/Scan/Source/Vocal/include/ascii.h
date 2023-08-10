
/* ************************************************************************* */
/*
 *	ascii.h
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
 *	This file defines ASCII characters and related constructs.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 19:50:34  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _INCLUDE_ASCII_H
#define _INCLUDE_ASCII_H

/* ************************************************************************* */

extern const char *CRLF_STRING; /* "\r\n" */

#define ASCII__UPPER_TO_LOWER__OR_MASK		0x020
#define ASCII__LOWER_TO_UPPER__AND_MASK		0x0df

#define ASCII__NULL				0x000		/*   0 */
#define ASCII__ESC				0x01b		/*  27 */
#define ASCII__CTRL_C			0x003		/*   3 */
#define ASCII__CTRL_ABORT		0x01c		/*  28 */
#define ASCII__CR				0x00d		/*  13 */
#define ASCII__LF				0x00a		/*  10 */
#define ASCII__BS				0x008		/*   8 */
#define ASCII__EM				0x019		/*  25 */
#define ASCII__BELL				0x007		/*   7 */
#define ASCII__SHIFT_TAB		0x10f		/* 271 */
#define ASCII__TAB				0x009		/*   9 */
#define ASCII__SPACE			0x020		/*  32 */
#define	ASCII__FF				0x00c		/*  12 */
#define	ASCII__XON				0x011		/*  17 */	/* Control-Q */
#define	ASCII__XOFF				0x013		/*  19 */	/* Control-S */
#define	ASCII__DEL				0x07f		/* 127 */

#define ASCII__RIGHT			0x14d		/* 333 */
#define ASCII__LEFT				0x14b		/* 331 */
#define ASCII__UP				0x148		/* 328 */
#define ASCII__DOWN				0x150		/* 336 */
#define ASCII__DELETE			0x153		/* 339 */
#define ASCII__INS				0x152		/* 338 */
#define ASCII__PGUP				0x149		/* 329 */
#define ASCII__PGDOWN			0x151		/* 337 */
#define ASCII__ALT_UP			0x198		/* 408 */
#define ASCII__ALT_DOWN			0x1a0		/* 416 */
#define ASCII__ALT_PGUP			0x199		/* 409 */
#define ASCII__ALT_PGDOWN		0x1a1		/* 417 */
#define ASCII__CTRL_UP			0x18d		/* 397 */
#define ASCII__CTRL_DOWN		0x191		/* 401 */
#define ASCII__CTRL_PGUP		0x184		/* 388 */
#define ASCII__CTRL_PGDOWN		0x176		/* 374 */

#define ASCII__F1    			0x13b		/* 315 */
#define ASCII__F2    			0x13c		/* 316 */
#define ASCII__F3    			0x13d		/* 317 */
#define ASCII__F4    			0x13e		/* 318 */
#define ASCII__F5    			0x13f		/* 319 */
#define ASCII__F6    			0x140		/* 320 */
#define ASCII__F7    			0x141		/* 321 */
#define ASCII__F8    			0x142		/* 322 */
#define ASCII__F9    			0x143		/* 323 */
#define ASCII__F10   			0x144		/* 324 */
#define ASCII__F11   			0x145		/* 325 */
#define ASCII__F12   			0x146		/* 326 */

#define ASCII__SF1   			0x154		/* 340 */
#define ASCII__SF2   			0x155		/* 341 */
#define ASCII__SF3   			0x156		/* 342 */
#define ASCII__SF4   			0x157		/* 343 */
#define ASCII__SF5   			0x158		/* 344 */
#define ASCII__SF6   			0x159		/* 345 */
#define ASCII__SF7   			0x15a		/* 346 */
#define ASCII__SF8   			0x15b		/* 347 */
#define ASCII__SF9   			0x15c		/* 348 */
#define ASCII__SF10  			0x15d		/* 349 */
#define ASCII__CF1   			0x15e		/* 350 */
#define ASCII__CF2   			0x15f		/* 351 */
#define ASCII__CF3   			0x160		/* 352 */
#define ASCII__CF4   			0x161		/* 353 */
#define ASCII__CF5   			0x162		/* 354 */
#define ASCII__CF6   			0x163		/* 355 */
#define ASCII__CF7   			0x164		/* 356 */
#define ASCII__CF8   			0x165		/* 357 */
#define ASCII__CF9   			0x166		/* 358 */
#define ASCII__CF10  			0x167		/* 359 */
#define ASCII__AF1   			0x168		/* 360 */
#define ASCII__AF2   			0x169		/* 361 */
#define ASCII__AF3   			0x16a		/* 362 */
#define ASCII__AF4   			0x16b		/* 363 */
#define ASCII__AF5   			0x16c		/* 364 */
#define ASCII__AF6   			0x16d		/* 365 */
#define ASCII__AF7   			0x16e		/* 366 */
#define ASCII__AF8   			0x16f		/* 367 */
#define ASCII__AF9   			0x170		/* 368 */
#define ASCII__AF10  			0x171		/* 369 */
#define	ASCII__ALTA  			0x11e		/* 286 */
#define	ASCII__ALTB  			0x130		/* 304 */
#define	ASCII__ALTC  			0x12e		/* 302 */
#define	ASCII__ALTD  			0x120		/* 288 */
#define	ASCII__ALTE  			0x112		/* 274 */
#define	ASCII__ALTF  			0x121		/* 289 */
#define	ASCII__ALTG  			0x122		/* 290 */
#define	ASCII__ALTH  			0x123		/* 291 */
#define	ASCII__ALTI  			0x117		/* 279 */
#define	ASCII__ALTJ  			0x124		/* 292 */
#define	ASCII__ALTK  			0x125		/* 293 */
#define	ASCII__ALTL  			0x126		/* 294 */
#define	ASCII__ALTM  			0x132		/* 306 */
#define	ASCII__ALTN  			0x131		/* 305 */
#define	ASCII__ALTO  			0x118		/* 280 */
#define	ASCII__ALTP  			0x119		/* 281 */
#define	ASCII__ALTQ  			0x110		/* 272 */
#define	ASCII__ALTR  			0x113		/* 275 */
#define	ASCII__ALTS  			0x11F		/* 287 */
#define	ASCII__ALTT  			0x114		/* 276 */
#define	ASCII__ALTU  			0x116		/* 278 */
#define	ASCII__ALTV  			0x12F		/* 303 */
#define	ASCII__ALTW  			0x111		/* 273 */
#define	ASCII__ALTX  			0x12D		/* 301 */
#define	ASCII__ALTY  			0x115		/* 277 */
#define	ASCII__ALTZ  			0x12C		/* 300 */

#define ASCII__CTRLA			0x001		/*   1 */
#define ASCII__CTRLB			0x002		/*   2 */
#define ASCII__CTRLC			0x003		/*   3 */
#define ASCII__CTRLD			0x004		/*   4 */
#define ASCII__CTRLE			0x005		/*   5 */
#define ASCII__CTRLP			0x010		/*  16 */
#define ASCII__CTRLR			0x012		/*  18 */
#define ASCII__CTRLS			0x013		/*  19 */
#define ASCII__CTRLT			0x014		/*  20 */
#define ASCII__CTRLX			0x018		/*  24 */

#define ASCII__CAN				0x018		/*	24 */
#define ASCII__DC2				0x012		/*	18 */
#define ASCII__DLE				0x010		/*	16 */
#define ASCII__STX				0x002		/*	 2 */
#define ASCII__ETX				0x003		/*	 3 */
#define ASCII__SUB				0x01a		/*	26 */
#define ASCII__GS				0x01d		/*  29 */

/* Fax specific characters */

#define ASCII__FX_FILL			0x000		/*	 0 */
#define ASCII__FX_DLE__REVERSED	0x008		/*	   */
#define ASCII__FX_BC			0x03f		/*     */
#define ASCII__FX_PRI			0x021		/*	   */
#define ASCII__FX_PPM__MPS		0x02c		/*	   */
#define ASCII__FX_PPM__EOM		0x03b		/*	   */
#define ASCII__FX_PPM__EOP		0x02e		/*	   */
#define ASCII__FX_FC__VR0		0x061		/*	   */
#define ASCII__FX_FC__VR1		0x062		/*	   */
#define ASCII__FX_FC__LN0		0x063		/*	   */
#define ASCII__FX_FC__LN1		0x064		/*	   */
#define ASCII__FX_FC__LN2		0x065		/*	   */
#define ASCII__FX_FC__WD0		0x066		/*	   */
#define ASCII__FX_FC__WD1		0x067		/*	   */
#define ASCII__FX_FC__WD2		0x068		/*	   */
#define ASCII__FX_FC__WD3		0x069		/*	   */
#define ASCII__FX_FC__WD4		0x06A		/*	   */
#define ASCII__FX_FC__DF0		0x06B		/*	   */
#define ASCII__FX_FC__DF1		0x06C		/*	   */
#define ASCII__FX_FC__DF2		0x06D		/*	   */
#define ASCII__FX_FC__DF3		0x06E		/*	   */

#define ASCII__FX_RB__00_10		0x030		/*	   */
#define ASCII__FX_RB__10_20		0x031		/*	   */
#define ASCII__FX_RB__20_30		0x032		/*	   */
#define ASCII__FX_RB__30_40		0x033		/*	   */
#define ASCII__FX_RB__40_50		0x034		/*	   */
#define ASCII__FX_RB__50_60		0x035		/*	   */
#define ASCII__FX_RB__60_70		0x036		/*	   */
#define ASCII__FX_RB__70_80		0x037		/*	   */
#define ASCII__FX_RB__80_90		0x038		/*	   */
#define ASCII__FX_RB__90_100	0x039		/*	   */

#define ASCII__FX_DC2			0x012		/*	   */
#define ASCII__FX_OVR			0x04f		/*	   */
#define ASCII__FX_SOH			0x041		/*	   */
#define ASCII__FX_ETB			0x057		/*	   */

/* ************************************************************************* */

#define ASCII__LT		0x003c
#define ASCII__GT		0x003e
#define ASCII__US		0x005f

#define ASCII__0		0x0030
#define ASCII__1		0x0031
#define ASCII__2		0x0032
#define ASCII__3		0x0033
#define ASCII__4		0x0034
#define ASCII__5		0x0035
#define ASCII__6		0x0036
#define ASCII__7		0x0037
#define ASCII__8		0x0038
#define ASCII__9		0x0039

#define ASCII__A		0x0041
#define ASCII__B		0x0042
#define ASCII__C		0x0043
#define ASCII__D		0x0044
#define ASCII__E		0x0045
#define ASCII__F		0x0046
#define ASCII__G		0x0047
#define ASCII__H		0x0048
#define ASCII__I		0x0049
#define ASCII__J		0x004a
#define ASCII__K		0x004b
#define ASCII__L		0x004c
#define ASCII__M		0x004d
#define ASCII__N		0x004e
#define ASCII__O		0x004f
#define ASCII__P		0x0050
#define ASCII__Q		0x0051
#define ASCII__R		0x0052
#define ASCII__S		0x0053
#define ASCII__T		0x0054
#define ASCII__U		0x0055
#define ASCII__V		0x0056
#define ASCII__W		0x0057
#define ASCII__X		0x0058
#define ASCII__Y		0x0059
#define ASCII__Z		0x005a

#define ASCII__LC_A		0x0061
#define ASCII__LC_B		0x0062
#define ASCII__LC_C		0x0063
#define ASCII__LC_D		0x0064
#define ASCII__LC_E		0x0065
#define ASCII__LC_F		0x0066
#define ASCII__LC_G		0x0067
#define ASCII__LC_H		0x0068
#define ASCII__LC_I		0x0069
#define ASCII__LC_J		0x006a
#define ASCII__LC_K		0x006b
#define ASCII__LC_L		0x006c
#define ASCII__LC_M		0x006d
#define ASCII__LC_N		0x006e
#define ASCII__LC_O		0x006f
#define ASCII__LC_P		0x0070
#define ASCII__LC_Q		0x0071
#define ASCII__LC_R		0x0072
#define ASCII__LC_S		0x0073
#define ASCII__LC_T		0x0074
#define ASCII__LC_U		0x0075
#define ASCII__LC_V		0x0076
#define ASCII__LC_W		0x0077
#define ASCII__LC_X		0x0078
#define ASCII__LC_Y		0x0079
#define ASCII__LC_Z		0x007a

/* ************************************************************************* */

#endif /* _INCLUDE_ASCII_H */
