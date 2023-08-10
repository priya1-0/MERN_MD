
/* ************************************************************************* */
/*
 *	silab.h
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
 *	Module:		CSC
 *
 *	This file defines various international telephony symbols.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.2.4.3  2009/05/27 20:28:00  zhangn1
 *	Revision History:	SCR #175480. Add new country support for Congo release
 *	Revision History:	
 *	Revision History:	Revision 1.2  2008/08/13 15:37:12  zhangn1
 *	Revision History:	SCR #152765. Vocal International telephone update
 *	Revision History:	
 *	Revision History:	Revision 1.1  2007/10/16 16:40:01  zhangn1
 *	Revision History:	SCR #149144. Integration Vocal M6+ to 2490C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _CSC_SILAB_H
#define _CSC_SILAB_H

#include "include/itel.h"
#include "csc/structs.h"

#ifdef WE_ARE_DEFINING_VARIABLES

/*
typedef struct {
	uint8	_daa_itel_country_code;
	uint8	_daa_reg16;
	uint8	_daa_reg31;
	uint8	_daa_reg26;
	uint8	_daa_reg30;
} daa_itel_entry_t;
*/

/*
 - see include/silabs.h -
Register 16  31   16 16 26   26  26   30   16  16
field    OHS OHS2 RZ RT ILIM DCV MINI ACIM ACT ACT2
*/

#define SILAB_DAA_REG_SET(CC, OHS, OHS2, RZ, RT, ILIM, DCV, MINI, ACIM, ACT, ACT2)   \
				  {                                                         \
				  CC,	                                                    \
				  (ACT2 << 7) | (OHS << 6) | (ACT << 5) | (RZ << 1) | (RT << 0), \
				  (OHS2 << 3),                                              \
				  (DCV  << 6) | (MINI << 4)| (ILIM << 1),                     \
				  (ACIM << 0)                                                \
				  },

daa_itel_entry_t daa_itel_table [DAA_ITEL_COUNTRY_ENTRY_MAX] = {
            SILAB_DAA_REG_SET (ICC__ARGENTINA,           0, 0, 0, 0, 0, 0x3, 0x0, 0x0, 0, 0)
            SILAB_DAA_REG_SET (ICC__AUSTRALIA,           1, 0, 0, 0, 0, 0x1, 0x1, 0x3, 0, 1)
            SILAB_DAA_REG_SET (ICC__AUSTRIA,             0, 1, 0, 0, 1, 0x3, 0x0, 0x2, 0, 1)
            SILAB_DAA_REG_SET (ICC__BAHRAIN,             0, 1, 0, 0, 1, 0x3, 0x0, 0x2, 0, 1)
            SILAB_DAA_REG_SET (ICC__BELGIUM,             0, 1, 0, 0, 1, 0x3, 0x0, 0x2, 0, 1)
            SILAB_DAA_REG_SET (ICC__BRAZIL,              0, 0, 0, 0, 0, 0x3, 0x0, 0x0, 0, 0)
            SILAB_DAA_REG_SET (ICC__BULGARIA,            0, 1, 0, 0, 1, 0x3, 0x0, 0x3, 0, 1)
            SILAB_DAA_REG_SET (ICC__CANADA,              0, 0, 0, 0, 0, 0x3, 0x0, 0x0, 0, 0)
            SILAB_DAA_REG_SET (ICC__CHILE,               0, 0, 0, 0, 0, 0x3, 0x0, 0x0, 0, 0)
            SILAB_DAA_REG_SET (ICC__CHINA,               0, 0, 0, 0, 0, 0x3, 0x0, 0x0, 0, 0)
            SILAB_DAA_REG_SET (ICC__COLOMBIA,            0, 0, 0, 0, 0, 0x3, 0x0, 0x0, 0, 0)
            SILAB_DAA_REG_SET (ICC__COSTA_RICA,          0, 0, 0, 0, 0, 0x3, 0x0, 0x0, 0, 0)
            SILAB_DAA_REG_SET (ICC__CROATIA,             0, 1, 0, 0, 1, 0x3, 0x0, 0x2, 0, 1)
            SILAB_DAA_REG_SET (ICC__CYPRUS,              0, 1, 0, 0, 1, 0x3, 0x0, 0x2, 0, 1)
            SILAB_DAA_REG_SET (ICC__CZECH_REPUBLIC,      0, 1, 0, 0, 1, 0x3, 0x0, 0x2, 0, 1)
            SILAB_DAA_REG_SET (ICC__DENMARK,             0, 1, 0, 0, 1, 0x3, 0x0, 0x2, 0, 1)
            SILAB_DAA_REG_SET (ICC__ECUADOR,             0, 0, 0, 0, 0, 0x3, 0x0, 0x0, 0, 0)
            SILAB_DAA_REG_SET (ICC__EGYPT,               0, 1, 0, 0, 1, 0x3, 0x0, 0x2, 0, 1)
            SILAB_DAA_REG_SET (ICC__EL_SALVADOR,         0, 0, 0, 0, 0, 0x3, 0x0, 0x0, 0, 0)
            SILAB_DAA_REG_SET (ICC__FINLAND,             0, 1, 0, 0, 1, 0x3, 0x0, 0x2, 0, 1)
            SILAB_DAA_REG_SET (ICC__FRANCE,              0, 1, 0, 0, 1, 0x3, 0x0, 0x2, 0, 1)
            SILAB_DAA_REG_SET (ICC__GERMANY,             0, 1, 0, 0, 1, 0x3, 0x0, 0x2, 0, 1)
            SILAB_DAA_REG_SET (ICC__GREECE,              0, 1, 0, 0, 1, 0x3, 0x0, 0x2, 0, 1)
            SILAB_DAA_REG_SET (ICC__GUAM,                0, 0, 0, 0, 0, 0x3, 0x0, 0x0, 0, 0)
            SILAB_DAA_REG_SET (ICC__HONG_KONG,           0, 0, 0, 0, 0, 0x3, 0x0, 0x0, 0, 0)
            SILAB_DAA_REG_SET (ICC__HUNGARY,             0, 1, 0, 0, 1, 0x3, 0x0, 0x2, 0, 1)
            SILAB_DAA_REG_SET (ICC__ICELAND,             0, 1, 0, 0, 1, 0x3, 0x0, 0x2, 0, 1)
            SILAB_DAA_REG_SET (ICC__INDIA,               0, 0, 0, 0, 0, 0x3, 0x0, 0x0, 0, 0)
            SILAB_DAA_REG_SET (ICC__INDONESIA,           0, 0, 0, 0, 0, 0x3, 0x0, 0x0, 0, 0)
            SILAB_DAA_REG_SET (ICC__IRAN,                0, 0, 0, 0, 0, 0x3, 0x0, 0x0, 0, 0)
            SILAB_DAA_REG_SET (ICC__IRELAND,             0, 1, 0, 0, 1, 0x3, 0x0, 0x2, 0, 1)
            SILAB_DAA_REG_SET (ICC__ISRAEL,              0, 1, 0, 0, 1, 0x3, 0x0, 0x2, 0, 1)
            SILAB_DAA_REG_SET (ICC__ITALY,               0, 1, 0, 0, 1, 0x3, 0x0, 0x2, 0, 1)
            SILAB_DAA_REG_SET (ICC__JAPAN,               0, 0, 0, 0, 0, 0x1, 0x1, 0x0, 0, 0)
            SILAB_DAA_REG_SET (ICC__JORDAN,              0, 0, 0, 0, 0, 0x1, 0x1, 0x0, 0, 0)
            SILAB_DAA_REG_SET (ICC__KAZAKHSTAN,          0, 0, 0, 0, 0, 0x3, 0x0, 0x0, 0, 0)
            SILAB_DAA_REG_SET (ICC__KOREA,               0, 0, 1, 0, 0, 0x3, 0x0, 0x0, 0, 0) // set to US values
            SILAB_DAA_REG_SET (ICC__KUWAIT,              0, 0, 0, 0, 0, 0x3, 0x0, 0x0, 0, 0)
            SILAB_DAA_REG_SET (ICC__LATVIA,              0, 1, 0, 0, 1, 0x3, 0x0, 0x2, 0, 1)
            SILAB_DAA_REG_SET (ICC__LEBANON,             0, 1, 0, 0, 1, 0x3, 0x0, 0x2, 0, 1)
            SILAB_DAA_REG_SET (ICC__LUXEMBOURG,          0, 1, 0, 0, 1, 0x3, 0x0, 0x2, 0, 1)
            SILAB_DAA_REG_SET (ICC__MACAO,               0, 0, 0, 0, 0, 0x3, 0x0, 0x0, 0, 0)
            SILAB_DAA_REG_SET (ICC__MALAYSIA,            0, 0, 0, 0, 0, 0x1, 0x1, 0x0, 0, 0)
            SILAB_DAA_REG_SET (ICC__MALTA,               0, 1, 0, 0, 1, 0x3, 0x0, 0x2, 0, 1)
            SILAB_DAA_REG_SET (ICC__MEXICO,              0, 0, 0, 0, 0, 0x3, 0x0, 0x0, 0, 0)
            SILAB_DAA_REG_SET (ICC__MOROCCO,             0, 1, 0, 0, 1, 0x3, 0x0, 0x2, 0, 1)
            SILAB_DAA_REG_SET (ICC__NETHERLANDS,         0, 1, 0, 0, 1, 0x3, 0x0, 0x2, 0, 1)
            SILAB_DAA_REG_SET (ICC__NEW_ZEALAND,         0, 0, 0, 0, 0, 0x3, 0x0, 0x4, 1, 1)
            SILAB_DAA_REG_SET (ICC__NIGERIA,             0, 1, 0, 0, 1, 0x3, 0x0, 0x2, 0, 1)
            SILAB_DAA_REG_SET (ICC__NORWAY,              0, 1, 0, 0, 1, 0x3, 0x0, 0x2, 0, 1)
            SILAB_DAA_REG_SET (ICC__OMAN,                0, 0, 0, 0, 0, 0x1, 0x1, 0x0, 0, 0)
            SILAB_DAA_REG_SET (ICC__QATAR,               0, 1, 0, 0, 1, 0x3, 0x0, 0x2, 0, 1) // set to BAHRAIN values
            SILAB_DAA_REG_SET (ICC__PAKISTAN,            0, 0, 0, 0, 0, 0x1, 0x1, 0x0, 0, 0)
            SILAB_DAA_REG_SET (ICC__PANAMA,              0, 0, 0, 0, 0, 0x3, 0x0, 0x0, 0, 0)
            SILAB_DAA_REG_SET (ICC__PERU,                0, 0, 0, 0, 0, 0x3, 0x0, 0x0, 0, 0)
            SILAB_DAA_REG_SET (ICC__PHILIPPINES,         0, 0, 0, 0, 0, 0x1, 0x1, 0x0, 0, 0)
            SILAB_DAA_REG_SET (ICC__POLAND,              0, 1, 0, 0, 1, 0x3, 0x0, 0x2, 0, 1)
            SILAB_DAA_REG_SET (ICC__PORTUGAL,            0, 1, 0, 0, 1, 0x3, 0x0, 0x2, 0, 1)
            SILAB_DAA_REG_SET (ICC__PUERTO_RICO,         0, 0, 0, 0, 0, 0x3, 0x0, 0x0, 0, 0)
            SILAB_DAA_REG_SET (ICC__ROMANIA,             0, 1, 0, 0, 1, 0x3, 0x0, 0x2, 0, 1)
            SILAB_DAA_REG_SET (ICC__RUSSIA,              0, 0, 0, 0, 0, 0x3, 0x0, 0x0, 0, 0)
            SILAB_DAA_REG_SET (ICC__SAUDI_ARABIA,        0, 0, 0, 0, 0, 0x3, 0x0, 0x0, 0, 0)
            SILAB_DAA_REG_SET (ICC__SERBIA,              0, 1, 0, 0, 1, 0x3, 0x0, 0x2, 0, 1) // set to SLOVENIA values
            SILAB_DAA_REG_SET (ICC__SINGAPORE,           0, 0, 0, 0, 0, 0x3, 0x0, 0x0, 0, 0)
            SILAB_DAA_REG_SET (ICC__SLOVAK_REPUBLIC,     0, 1, 0, 0, 1, 0x3, 0x0, 0x2, 0, 1)
            SILAB_DAA_REG_SET (ICC__SLOVENIA,            0, 1, 0, 0, 1, 0x3, 0x0, 0x2, 0, 1)
            SILAB_DAA_REG_SET (ICC__SOUTH_AFRICA,        0, 0, 1, 0, 0, 0x3, 0x0, 0x3, 1, 0)
            SILAB_DAA_REG_SET (ICC__SPAIN,               0, 1, 0, 0, 1, 0x3, 0x0, 0x2, 0, 1)
            SILAB_DAA_REG_SET (ICC__SWEDEN,              0, 1, 0, 0, 1, 0x3, 0x0, 0x2, 0, 1)
            SILAB_DAA_REG_SET (ICC__SWITZERLAND,         0, 1, 0, 0, 1, 0x3, 0x0, 0x2, 0, 1)
            SILAB_DAA_REG_SET (ICC__TAIWAN,              0, 0, 0, 0, 0, 0x3, 0x0, 0x0, 0, 0)
            SILAB_DAA_REG_SET (ICC__TBR21,               0, 0, 0, 0, 1, 0x3, 0x0, 0x2, 0, 1)
            SILAB_DAA_REG_SET (ICC__THAILAND,            0, 0, 0, 0, 0, 0x1, 0x1, 0x0, 0, 0)
            SILAB_DAA_REG_SET (ICC__TURKEY,              0, 1, 0, 0, 1, 0x3, 0x0, 0x2, 0, 1)
            SILAB_DAA_REG_SET (ICC__UAE,                 0, 0, 0, 0, 0, 0x3, 0x0, 0x0, 0, 0)
            SILAB_DAA_REG_SET (ICC__UKRAINE,             0, 0, 0, 0, 0, 0x3, 0x0, 0x0, 0, 0)
            SILAB_DAA_REG_SET (ICC__UNITED_KINGDOM,      0, 1, 0, 0, 1, 0x3, 0x0, 0x5, 0, 1)
            SILAB_DAA_REG_SET (ICC__UNITED_STATES,       0, 0, 0, 0, 0, 0x3, 0x0, 0x0, 0, 0)
            SILAB_DAA_REG_SET (ICC__VENEZUELA,           0, 0, 0, 0, 0, 0x3, 0x0, 0x0, 0, 0)
            SILAB_DAA_REG_SET (ICC__VIETNAM,             0, 0, 0, 0, 0, 0x3, 0x0, 0x0, 0, 0)
            SILAB_DAA_REG_SET (ICC__YEMEN,               0, 0, 0, 0, 0, 0x3, 0x0, 0x0, 0, 0)
		    {0xffff,0,0,0,0 }
};
#endif /* WE_ARE_DEFINING_VARIABLES */

#endif /* _CSC_SILAB_H */
