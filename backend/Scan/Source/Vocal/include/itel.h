
//* ************************************************************************* */
/*
 *	itel.h
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
 *	This file defines various international telephony symbols.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.4.4  2009/05/27 20:29:13  zhangn1
 *	Revision History:	SCR #175480. Add new country support for Congo release
 *	Revision History:	
 *	Revision History:	Revision 1.3  2008/08/13 15:37:48  zhangn1
 *	Revision History:	SCR #152765. Vocal International telephone update
 *	Revision History:	
 *	Revision History:	Revision 1.2  2007/10/16 18:05:57  zhangn1
 *	Revision History:	SCR #149144. Integration Vocal M6+ to 2490C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _INCLUDE_ITEL_H
#define _INCLUDE_ITEL_H

/* ************************************************************************* */

/* ************************************************************************* */

/* ICC is abbreviation for ITEL_COUNTRY_CODE */


/* This set of codes follows the industry standard set by Rockwell/Conexant */
#define ICC__ARGENTINA								31
#define ICC__AUSTRALIA								40
#define ICC__AUSTRIA								 1
#define ICC__BELGIUM								 2
#define ICC__BRAZIL									32
#define ICC__BULGARIA								27
#define ICC__CANADA									20
#define ICC__CHINA									41
#define ICC__COLOMBIA								33
#define ICC__COSTA_RICA								34
#define ICC__CZECH_REPUBLIC							19
#define ICC__DENMARK								 3
#define ICC__EGYPT									35
#define ICC__FINLAND								 4
#define ICC__FRANCE									 5
#define ICC__GERMANY								 6
#define ICC__GREECE									17
#define ICC__HONG_KONG								42
#define ICC__HUNGARY								23
#define ICC__INDIA									30
#define ICC__IRAN									36
#define ICC__IRELAND								 7
#define ICC__ISRAEL									18
#define ICC__ITALY									 8
#define ICC__JAPAN									43
#define ICC__KOREA									44
#define ICC__LUXEMBOURG								 9
#define ICC__MALAYSIA								37
#define ICC__MEXICO									21
#define ICC__NETHERLANDS							10
#define ICC__NEW_ZEALAND							48
#define ICC__NORWAY									11
#define ICC__PANAMA									38
#define ICC__PHILIPPINES							51
#define ICC__POLAND									24
#define ICC__PORTUGAL								12
#define ICC__PUERTO_RICO							39
#define ICC__RUSSIA									25
#define ICC__SAUDI_ARABIA							45
#define ICC__SINGAPORE								47
#define ICC__SLOVAK_REPUBLIC						26
#define ICC__SPAIN									13
#define ICC__SWEDEN									14
#define ICC__SWITZERLAND							15
#define ICC__TAIWAN									46
#define ICC__TURKEY									49
#define ICC__UKRAINE								28
#define ICC__UNITED_KINGDOM							16
#define ICC__UNITED_STATES							22
#define ICC__VENEZUELA								29
#define ICC__VIETNAM								50

/* 09/05/05 */
/* These additional codes are arbitrary */
#define ICC__BAHRAIN								71
#define ICC__CHILE									72
#define ICC__GUAM									73
#define ICC__KUWAIT									74
#define ICC__MALTA									75
#define ICC__QATAR									76
#define ICC__SERBIA									77
#define ICC__SLOVENIA								78
#define ICC__SOUTH_AFRICA							79		// Diamond uses 60 for South Africa
#define ICC__THAILAND								80
#define ICC__UAE									81

#define ICC__CROATIA								255
#define ICC__CYPRUS									255
#define ICC__ECUADOR								255
#define ICC__EL_SALVADOR							255
#define ICC__ICELAND								255
#define ICC__INDONESIA								255
#define ICC__JORDAN									255
#define ICC__KAZAKHSTAN								255
#define ICC__LATVIA									255
#define ICC__LEBANON								255
#define ICC__MACAO									255
#define ICC__MOROCCO								255
#define ICC__NIGERIA								255
#define ICC__OMAN									255
#define ICC__PAKISTAN								255
#define ICC__PERU									255
#define ICC__ROMANIA								255
#define ICC__SYRIA									255
#define ICC__TBR21									255
#define ICC__YEMEN									255

#define ITEL_DIAL_OPTION__BIT__RING_SHUNT			0x0001
#define ITEL_DIAL_OPTION__BIT__PULSE_R_REDUCER		0x0002
#define ITEL_DIAL_OPTION__BIT__LOOP_CURRENT			0x0004
#define ITEL_DIAL_OPTION__BIT__DET_ANSW_TONE_RQD	0x0010
#define ITEL_DIAL_OPTION__BIT__GEN_ANSW_TONE_RQD	0x0020
#define ITEL_DIAL_OPTION__BIT__GEN_CALL_TONE_RQD	0x0040
#define ITEL_DIAL_OPTION__BIT__DET_BUSY_RQD			0x0080
#define ITEL_DIAL_OPTION__BIT__BLIND_DIAL_ALLOWED	0x0100
#define ITEL_DIAL_OPTION__BIT__GUARD_TONE			0x0200


/* ************************************************************************* */

#endif /* _INCLUDE_ITEL_H */
