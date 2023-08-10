
/* ************************************************************************* */
/*
 *	modcap.h
 *
 *	(C) 1994 - 2006 VOCAL Technologies, Ltd.
 *
 *	ALL RIGHTS RESERVED.  PROPRIETARY AND CONFIDENTIAL.
 *
 *	VOCAL Technologies, Ltd.
 *	90A John Muir Drive.
 *	Buffalo, NY  14228
 *
 *	Product:	LANsEND
 *
 *	Module:		TERM
 *
 *	Defines and structures needed to define a modem capability.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 20:49:20  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _TERM_MODCAP_H
#define _TERM_MODCAP_H

/* A modem capability structure.
 *
 * This structure defines the strings needed to activate the capabilites
 * of the modem. */
struct modcap {
	struct modcap *next;
	char *name;							/* Name of the modem. */
	char *init;							/* Sent at setencap. */
	char *dial;							/* The dial prefix, number comes after this. */
	char *post_con;						/* Sent after the phone connects. */
};
#define NULLMODCAP ((struct modcap *) 0)

#endif /* _TERM_MODCAP_H */
