
/* ************************************************************************* */
/*
 *	rev.h
 *
 *	(C) 1997 - 2006 VOCAL Technologies, Ltd.
 *
 *	ALL RIGHTS RESERVED.  PROPRIETARY AND CONFIDENTIAL.
 *
 *	VOCAL Technologies, Ltd.
 *	90A John Muir Drive.
 *	Buffalo, NY  14228
 *
 *	Product:	MODEM 101
 *
 *	Module:		MDM
 *
 *	This file contains various reviosion information.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 20:23:04  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _MDM_REV_H
#define _MDM_REV_H

/* ************************************************************************* */

#define VOCAL_REVISION	"4.56"

/*	As per contractural obligations, VOCAL's copyright notice string MUST
	always be a part of the binary.  Any modifications to the software must
	not cause it to be absent. */
#define COPYRIGHT_STRING	"(C) 1994-2005 VOCAL Technologies, Ltd."

/* ************************************************************************* */

#ifdef DO_CG_SRDEV
#define COMPILE_GROUP	"SRDEV"
#endif /* DO_CG_SRDEV */
#define COMPILE_GROUP	"TI55X"
#undef COMPILE_GROUP
#define COMPILE_GROUP	"CX077"

#ifndef COMPILE_GROUP
#define COMPILE_GROUP	"Unknown"
#endif /* COMPILE_GROUP */

/* ************************************************************************* */

#ifndef RECONFIG_GROUP
#define RECONFIG_GROUP	""
#endif /* RECONFIG_GROUP */

/* ************************************************************************* */

#define I0_STRING	"MDM "RECONFIG_GROUP" "COMPILE_GROUP" Ver "VOCAL_REVISION" "COPYRIGHT_STRING
#define I1_STRING	"This is a customizable response, I1"
#define I2_STRING	"This is a customizable response, I2"
#define I3_STRING	"This is a customizable response, I3"
#define I4_STRING	"This is a customizable response, I4"
#define I5_STRING	"This is a customizable response, I5"
#define I6_STRING	"This is a customizable response, I6"
#define I7_STRING	"This is a customizable response, I7"

/* ************************************************************************* */

#endif /* _MDM_REV_H */
