
/* ************************************************************************* */
/*
 *	tabled.h
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
 *	This file contains data declarations/definitions for fixed tables.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.3.2.5  2010/02/17 21:11:50  zhangn1
 *	Revision History:	SCR #186863. Implement blind dialing
 *	Revision History:	
 *	Revision History:	Revision 1.2.4.3  2009/06/01 19:57:39  zhangn1
 *	Revision History:	SCR #175670. Add telephony support for 10 countries to Congo release
 *	Revision History:	
 *	Revision History:	Revision 1.2  2008/08/13 15:36:53  zhangn1
 *	Revision History:	SCR #152765. Vocal International telephone update
 *	Revision History:	
 *	Revision History:	Revision 1.1  2007/10/16 16:40:01  zhangn1
 *	Revision History:	SCR #149144. Integration Vocal M6+ to 2490C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _CSC_TABLED_H
#define _CSC_TABLED_H

#ifdef WE_ARE_DEFINING_VARIABLES

#include "csc/config.h"
#include "include/callprog.h"
#include "include/itel.h"

#include "csc/silabd.h"
#include "csc/structs.h"

/* ************************************************************************* */

#define H		ITEL_DIAL_OPTION__BIT__RING_SHUNT
#define R		ITEL_DIAL_OPTION__BIT__PULSE_R_REDUCER
#define L		ITEL_DIAL_OPTION__BIT__LOOP_CURRENT
#define D		ITEL_DIAL_OPTION__BIT__DET_ANSW_TONE_RQD
#define A		ITEL_DIAL_OPTION__BIT__GEN_ANSW_TONE_RQD
#define C		ITEL_DIAL_OPTION__BIT__GEN_CALL_TONE_RQD
#define Y		ITEL_DIAL_OPTION__BIT__DET_BUSY_RQD
#define B		ITEL_DIAL_OPTION__BIT__BLIND_DIAL_ALLOWED
#define G		ITEL_DIAL_OPTION__BIT__GUARD_TONE

#define IDT		CP_STATUS__INITIAL_DIALTONE
#define SDT		CP_STATUS__SECOND_DIALTONE
#define ODT		CP_STATUS__OTHER_DIALTONE
#define BDT		CP_STATUS__BROKEN_DIALTONE

#define SBY		CP_STATUS__SHORT_BUSY
#define MBY		CP_STATUS__MEDIUM_BUSY
#define LBY		CP_STATUS__LONG_BUSY
#define BBY		CP_STATUS__BROAD_BUSY
#define OBY		CP_STATUS__OTHER_BUSY

#define USR		CP_STATUS__US_RRING
#define UKR		CP_STATUS__UK_RRING
#define SRR		CP_STATUS__SHORT_RRING
#define ORR		CP_STATUS__OTHER_RRING

#define RRS		CP_STATUS__RRING_SILENCE
#define XXS		CP_STATUS__602_SILENCE

itel_entry_t itel_table [ITEL_COUNTRY_ENTRY_MAX] = {
/*
{Country
   Dialtone                 Remote Ring         Busy
  (IDT|SDT|ODT|BDT) |      (USR|UKR|SRR|ORR) | (SBY|MBY|LBY|BBY|OBY)

  Pulse                    Tone                MaxMin Disc   Option Mask
  Mak,Brk,Pause,           On,Pause,Hi,Low     Tx,Rx, Dur,   S|R|L|D|A|C|Y|B|G

  Dialing/PostDialDial     Ring to Answer      Restricted Dialing   Codec
  det WaitPostBlndBlndAnsw min max,min,max     max reset 1-2 sbs  Impedance
  dur,dur,dur,min,max,Wait dur,dur,cnt,cnt     num,dur, dur,dur  (see above)
  10  100 100 100 1        1   1                   1     1   1
  ms  ms  ms  ms  s        s   s                   s     s   s     (#defined)
*/

{ ICC__ARGENTINA,
  (IDT            ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT        ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY|BBY    ),
   33, 67,800,             80,135,  6,  8,     10, 48, 89,   R|    A|C    ,
   10,100, 10,  0,  0, 50,  1,100,  1,100,      4,  6, 61,3601,	Z_22_82  },

{ ICC__AUSTRALIA,
  (IDT            ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT        ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
   35, 65,800,             80, 80,  6,  8,     10, 48, 60,   R|    A|    B,
   10, 40,  0, 20, 50, 50,  3, 14,  1,100,     10,  3,  3,   0,	Z_22_82  },

{ ICC__AUSTRIA,
  (IDT    |ODT    ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT|ODT    ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY|BBY    ),
   40, 60,800,             80, 80,  6,  8,      6, 48, 39,   R|L|D|A|C|  B,
    8, 50, 10,  0,  0, 50,  0,  6,  1,100,      6,  6, 61,3601,	Z_27_75  },

{ ICC__BAHRAIN,			/* 09/05/05 */
  (IDT            ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT        ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY|BBY    ),
   33, 67,800,             80, 80,  9, 11,      9, 48, 59, H|R|          B,
   10,100, 10, 35, 80, 50,  1, 15,  1,100,      1,  1,  1,   1,	Z_27_75  },

{ ICC__BELGIUM,			/* 98/11/09 */
  (IDT    |ODT    ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT|ODT    ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY|BBY    ),
   33, 67,800,             80, 80,  8, 11,     10, 48, 59,           C|B|G,
   10,100, 10,  0,  0, 50,  1,100,  2,100,     10,  2, 61,   0,	Z_27_75  },

{ ICC__BRAZIL,
  (IDT        |BDT) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT|ODT|BDT) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
   33, 67,800,             80,135,  6,  8,     10, 48, 89,   R|    A|C    ,
   10,100, 10,  0,  0, 50,  1,100,  1,100,      4,  6, 61,3601,	Z_22_82  },

{ ICC__BULGARIA,		/* 98/11/09 */
  (IDT    |ODT|BDT) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),			//broken dialtone may not be needed
  (    SDT|ODT|BDT) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),			//broken dialtone may not be needed
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY|BBY        ),
   33, 67,800,             80, 80,  8, 11,     10, 48, 59,           C|B|G,
   10,100, 10, 50, 50, 50,  1,100,  2,100,     10,  2, 61,   0,	Z_UNK  },

{ ICC__CANADA,			/* 98/11/09 */
  (IDT            ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT        ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),			//may also need other dialtone
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
   40, 60,800,             80, 80,  6,  8,     10, 48, 59,           C|B|G,
   10,100, 10, 20,250, 50,  1,100,  2,100,     10,  2, 61,   0,	Z_60_00  },

{ ICC__CHILE,			/* 09/05/05 */
  (IDT            ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT        ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
   40, 60,800,             80, 80,  9, 11,     10, 48, 59,               B,
    0,100, 10, 20,250, 50,  1,100,  1,100,      1,  1,  1,   1,	Z_60_00  },

{ ICC__CHINA,			/* 98/11/09 */
  (IDT            ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT|ODT    ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY|BBY    ),
   40, 60,800,             80, 80,  6,  8,     10, 48, 59,           C|B|G,
   10,100, 10, 50, 50, 50,  1,100,  2,100,     10,  2, 61,   0,	Z_20_68  },

{ ICC__COLOMBIA,
  (IDT            ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT        ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY|BBY    ),
   33, 67,800,             80,135,  6,  8,     10, 48, 89,   R|    A|C    ,
   10,100, 10,  0,  0, 50,  1,100,  1,100,      4,  6, 61,3601,	Z_UNK  },

{ ICC__COSTA_RICA,			/* 98/11/09 */
  (IDT            ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT        ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY|BBY    ),
   33, 67,800,             80,135,  6,  8,     10, 48, 89,   R|    A|C    ,
   10,100, 10,  0,  0, 50,  1,100,  1,100,      4,  6, 61,3601,	Z_UNK  },

{ ICC__CZECH_REPUBLIC,	/* 98/11/09 */
  (IDT    |ODT|BDT) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),			//broken dialtone may not be needed
  (    SDT|ODT|BDT) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),			//broken dialtone may not be needed
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY|BBY    ),
   40, 60,800,             80, 80,  8, 11,     10, 48, 59,           C|B|G,
   10,100, 10, 50, 50, 50,  1,100,  2,100,     10,  2, 61,   0,	Z_UNK  },

{ ICC__DENMARK,
  (IDT            ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT        ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY|BBY    ),
   35, 65,800,             80, 80,  9, 11,     10, 48, 14,   R|    A|    B,
   10, 90, 50,  0,  0, 50,  1,100,  1,100,     10,  2, 61,   0,	Z_27_75  },

{ ICC__EGYPT,
  (IDT            ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT        ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY|BBY    ),
   40, 60,800,             80, 80,  9, 11,     10, 48, 59,               B,
    0,100, 10, 20,250, 50,  1,100,  1,100,      1,  1,  1,   1,	Z_UNK  },

{ ICC__FINLAND,
  (IDT    |ODT    ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT|ODT    ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY|BBY    ),
   40, 60,800,             80, 80,  6,  8,     10, 48, 89,   R|          B,
   10,100, 10, 20, 50, 50,  2,100,  1,100,      4,  6, 61,3601,	Z_27_75  },

{ ICC__FRANCE,
  (IDT        |BDT) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT    |BDT) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
   33, 67,900,             80, 80,  6,  8,     10, 48,179, H|R|L|D|A|C|  B,
   10,100, 10,  0,  0, 50,  6, 14,  1,100,      6, 61, 61,   0,	Z_27_75  },

{ ICC__GERMANY,
  (IDT    |ODT    ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT|ODT    ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY|BBY    ),
   40, 60,800,             80, 80,  9, 11,      9, 48, 59,   R|    A|    B,
   10,100, 10, 25,100, 50,  0, 59,  1,100,     12,  6,  6,7201,	Z_27_75  },

{ ICC__GREECE,			/* 98/11/09 */
  (IDT    |ODT    ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT|ODT    ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY|BBY        ),
   40, 60,800,             80, 80,  8, 11,     10, 48, 59,           C|B|G,
   10,100, 10, 50, 50, 50,  1,100,  2,100,     10,  2, 61,   0,	Z_27_75 },

{ ICC__GUAM,			/* 09/05/05 */
  (IDT            ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT        ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
   40, 60,800,             80, 80,  9, 11,     10, 48, 59,               B,
    0,100, 10, 20,250, 50,  1,100,  1,100,      1,  1,  1,   1,	Z_60_00  },

{ ICC__HONG_KONG,		/* 98/11/09 */
  (IDT            ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT        ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
    0, 0,   0,             80, 80,  6,  8,     10, 48, 59,           C|B|G,
   10,100, 10, 50, 50, 50,  1,100,  2,100,     10,  2, 61,   0,	Z_60_00  },

{ ICC__HUNGARY,			/* 98/11/09 */
  (IDT            ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT        ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY|BBY        ),
   33, 67,800,             80, 80,  8, 11,     10, 48, 59,           C|B|G,
   10,100, 10, 50, 50, 50,  1,100,  2,100,     10,  2, 61,   0,	Z_UNK  },

{ ICC__INDIA,			/* 98/11/09 */
  (IDT            ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT|ODT    ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY|BBY    ),
   33, 67,800,             80, 80,  9, 11,     10, 48, 59,           C|B|G,
   10,100, 10, 50, 50, 50,  1,100,  2,100,     10,  2, 61,   0,	Z_UNK  },

{ ICC__IRAN,			/* 98/11/09 */
  (IDT            ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT        ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
   33, 67,800,             80,135,  6,  8,     10, 48, 89,   R|    A|C    ,
   10,100, 10,  0,  0, 50,  1,100,  1,100,      4,  6, 61,3601,	Z_UNK  },

{ ICC__IRELAND,			/* 98/11/09 */
  (IDT            ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT        ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY|BBY    ),
   33, 67,800,             80, 80,  8, 11,     10, 48, 59,           C|B|G,
   10,100, 10,  0,  0, 50,  1,100,  2,100,     10,  2, 61,   0,	Z_27_75  },

{ ICC__ISRAEL,			/* 98/11/09 */
  (IDT            ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),			//may also need other dialtone for special dialtone
  (    SDT        ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
   40, 60,800,             80, 80,  8, 11,     10, 48, 59,           C|B|G,
   10,100, 10, 50, 50, 50,  1,100,  2,100,     10,  2, 61,   0,	Z_UNK  },

{ ICC__ITALY,
  (IDT    |ODT|BDT) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),			//the addition of broken dialtone appears unnecessary
  (    SDT|ODT|BDT) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),			//the addition of broken dialtone appears unnecessary
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
   40, 60,850,             80, 80,  6,  8,     10, 48, 39,   R|    A|    B,
    4,100, 10, 10,100, 50,  7, 21,  1,100,      4,  6, 61,3601,	Z_27_75  },


{ ICC__JAPAN,
  (IDT    |ODT    ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT|ODT    ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
   36, 66,800,             80, 80,  6,  8,     15, 48, 59,   R|    A|	B,
   10,100, 10, 30, 30, 50,  1,100,  1,100,     10,  6, 61,3601,	Z_60_00  },

{ ICC__KOREA,			/* 98/11/09 */
  (IDT            ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT        ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),			//may also need different dialtone (almost like ringback)
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
    0,  0,  0,             80, 80,  6,  8,     10, 48, 59,           C|B|G,
   10,100, 10, 50, 50, 50,  1,100,  2,100,      3,  2, 61,   0,	Z_60_00  },

{ ICC__KUWAIT,			/* 09/05/05 */
  (IDT            ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT        ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
   40, 60,800,             80, 80,  9, 11,     10, 48, 59,               B,
    0,100, 10, 20,250, 50,  1,100,  1,100,      1,  1,  1,   1,	Z_60_00  },

{ ICC__LUXEMBOURG,		/* 98/11/09 */
  (IDT            ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT        ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY|BBY    ),
   40, 60,800,             80, 80,  8, 11,     10, 48, 59,           C|B|G,
   10,100, 10, 50, 50, 50,  1,100,  2,100,     10,  2, 61,   0,	Z_27_75  },

{ ICC__MALAYSIA,
  (IDT            ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT        ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY|BBY    ),
    0,  0,  0,             80, 80,  6,  8,     10, 48, 59,           C|B|G,
   10,100, 10, 50, 50, 50,  1,100,  2,100,     10,  2, 61,   0,	Z_UNK  },

{ ICC__MALTA,			/* 09/05/05 */
  (IDT    |ODT    ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT        ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY|BBY    ),
   33, 67,800,             80, 80,  9, 11,      9, 48, 59, H|R|          B,
   10,100, 10, 35, 80, 50,  1, 15,  1,100,      1,  1,  1,   1,	Z_27_75  },

{ ICC__MEXICO,			/* 98/11/09 */
  (IDT            ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT        ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
   33, 67,800,             80, 80,  6,  8,     10, 48, 59,           C|B|G,
   10,100, 10, 50, 50, 50,  1,100,  2,100,     10,  2, 61,   0,	Z_90_00  },

{ ICC__NETHERLANDS,
  (IDT            ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT        ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),			//may also need broken dialtone
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
   39, 61,800,             80, 80,  9, 11,      6, 48, 59,   R|    A|  Y|B,
    9,100, 10,  0,  0, 50,  2, 14,  1,100,     15,  6, 61,   0,	Z_60_00  },

{ ICC__NEW_ZEALAND,		/* 98/11/09 */
  (IDT            ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT        ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
    0,   0,  0,             80, 80,  6,  8,     10, 48, 59,           C|B|G,
   10,100, 10, 50, 50, 50,   1,100,  2,100,     10,  2, 61,   0, Z_37_62  },

{ ICC__NORWAY,
  (IDT            ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT        ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY|BBY    ),
    0,  0,  0,             80, 80,  9, 11,     10, 48, 29,   R|    A|C|  B,
   10,100, 10,  0,  0, 50,  0, 15,  1,100,     10,  6, 75, 100,	Z_27_75  },

{ ICC__PANAMA,		/* 98/11/09 */
  (IDT            ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT        ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
   33, 67,800,             80,135,  6,  8,     10, 48, 89,   R|    A|C    ,
   10,100, 10,  0,  0, 50,  1,100,  1,100,      4,  6, 61,3601,	Z_UNK  },

{ ICC__PHILIPPINES,		/* 98/11/09 */
  (IDT    |ODT    ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT|ODT    ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY|BBY    ),
   40, 60,800,             80, 80,  6,  8,     10, 48, 59,           C|B|G,
   10,100, 10, 50, 50, 50,  1,100,  2,100,     10,  2, 61,   0,	Z_UNK  },

{ ICC__POLAND,			/* 98/11/09 */
  (IDT            ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT        ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
   33, 67,800,             80, 80,  8, 11,     10, 48, 59,           C|B|G,
   10,100, 10, 50, 50, 50,  1,100,  2,100,     10,  2,121,   0,	Z_27_75  },

{ ICC__PORTUGAL,		/* 98/11/09 */
  (IDT            ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),			//may also need other dialtone
  (    SDT        ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
   33, 67,800,             80, 80,  8, 11,     10, 48, 59,           C|B|G,
   10,100, 10, 25, 50, 50,  1,100,  2,100,     10,  2, 61,   0,	Z_27_75  },

{ ICC__PUERTO_RICO,
  (IDT            ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT        ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
   40, 60,800,             80, 80,  9, 11,     10, 48, 59,               B,
    0,100, 10, 20, 250, 50,  1,100,  1,100,      1,  1,  1,   1,	Z_UNK  },

{ ICC__QATAR,			/* 09/05/05 */
  (IDT            ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT        ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY|BBY    ),
   33, 67,800,             80, 80,  9, 11,      9, 48, 59, H|R|          B,
   10,100, 10, 35, 80, 50,  1, 15,  1,100,      1,  1,  1,   1,	Z_27_75  },

{ ICC__RUSSIA,			/* 98/11/09 */
  (IDT            ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT        ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
   40, 60,800,             80, 80,  6,  8,     10, 48, 59,           C|B|G,
   10,100, 10, 50, 50, 50,  1,100,  2,100,     10,  2, 61,   0,	Z_UNK  },

{ ICC__SAUDI_ARABIA,
  (IDT            ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT        ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
   33, 67,800,             80,135,  6,  8,     10, 48, 89,   R|    A|C    ,
   10,100, 10,  0,  0, 50,  1,100,  1,100,      4,  6, 61,3601,	Z_UNK  },

{ ICC__SERBIA,			/* 09/05/05 */
  (IDT    |ODT    ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT|ODT    ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY|BBY    ),
   40, 60,800,             80, 80,  9, 11,      9, 48, 59,   R|    A|    B,
   10,100, 10, 25,100, 50,  0, 59,  1,100,     12,  6,  6,   1,	Z_27_75  },

{ ICC__SINGAPORE,		/* 98/11/09 */
  (IDT            ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT        ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY|BBY    ),
    0,  0,  0,             80, 80,  6,  8,     10, 48, 59,           C|G,
   10,100, 10, 50, 50, 50,  1,100,  2,100,     10,  2, 61,   0,	Z_60_00  },

{ ICC__SLOVAK_REPUBLIC,	/* 98/11/09 */	/* SLOVAKIA */
  (IDT    |ODT    ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT|ODT    ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY|BBY    ),
   40, 60,800,             80, 80,  6,  8,     10, 48, 59,           C|B|G,
   10,100, 10, 50, 50, 50,  1,100,  2,100,     10,  2, 61,   0,	Z_UNK  },

{ ICC__SLOVENIA,		/* 09/05/05 */
  (IDT    |ODT    ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT|ODT    ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY|BBY    ),
   40, 60,800,             80, 80,  9, 11,      9, 48, 59,   R|    A|    B,
   10,100, 10, 25,100, 50,  0, 59,  1,100,     12,  6,  6,   1,	Z_27_75  },

{ ICC__SOUTH_AFRICA,	/* 09/05/05 */
  (IDT            ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT        ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY|BBY    ),
   35, 65,800,             80, 80,  9, 11,     10, 48, 59,   R|    A|    B,
   10, 90, 50,  0,  0, 50,  1,100,  1,100,     10,  2, 61,   0,	Z_27_75  },

{ ICC__SPAIN,
  (IDT    |ODT|BDT) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT|ODT|BDT) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
   33, 67,800,             80,135,  6,  8,     10, 48, 89,   R|    A|C|  B,
   10,100, 10,  0,  0, 50,  1,100,  1,100,      4,  6, 61,3601,	Z_27_75  },

{ ICC__SWEDEN,
  (IDT        |BDT) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT    |BDT) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY|BBY    ),
   40, 60,700,             80, 80,  9, 11,     13, 48, 59,   R|          B,
    7,100, 10,  0,  0, 50,  1,100,  1,100,     10,  4, 61,   0,	Z_27_75  },

{ ICC__SWITZERLAND,
  (IDT            ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT        ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY|BBY    ),
   40, 60,800,             80, 80,  6,  8,      9, 48, 59,   R|L|  A|  Y|B,
   10,100, 10,  0,  0, 90,  0,100,  2, 10,      2, 61,  1, 21001,Z_27_75  },

{ ICC__TAIWAN,			/* 98/11/09 */
  (IDT            ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT        ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
   33, 67,800,             80, 80,  8, 11,     10, 48, 59,           C|B|G,
   10,100, 10, 50, 50, 50,  1,100,  2,100,     10,  2, 61,   0,	Z_60_00  },

{ ICC__THAILAND,			/* 09/05/05 */
  (IDT            ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT        ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY|BBY    ),
   33, 67,800,             80, 80,  9, 11,     10, 48, 59,           C|B|G,
   10,100, 10, 50, 50, 50,  1,100,  2,100,     10,  2, 61,   0,	Z_60_00  },

{ ICC__TURKEY,
  (IDT    |ODT    ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT|ODT    ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
   40, 60,800,           80, 80,  6,  8,	   10, 48, 59,           C|B|G,
   10,100, 10, 50, 50, 50,  1,100,  2,100,	   10,  2, 61,   0,	Z_UNK  },

{ ICC__UKRAINE,			/* 98/11/09 */
  (IDT            ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT        ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
   40, 60,800,             80, 80,  6,  8,     10, 48, 59,           C|B|G,
   10,100, 10, 50, 50, 50,  1,100,  2,100,     10,  2, 61,   0,	Z_UNK  },

{ ICC__UAE,				/* 09/05/05 */
  (IDT            ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT        ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY|BBY    ),
   40, 60,800,             80, 80,  9, 11,     10, 48, 59,               B,
    0,100, 10, 20,250, 50,  1,100,  1,100,      1,  1,  1,   1,	Z_60_00  },

{ ICC__UNITED_KINGDOM,
  (IDT            ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT        ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
   33, 67,800,             80, 80,  9, 11,      9, 48, 59, H|R|          B,
   10,100, 10, 35, 80, 50,  1, 15,  1,100,      1,  1,  1, 601,	Z_27_75  },


{ ICC__UNITED_STATES,
  (IDT            ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT        ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
   40, 60,800,             80, 80,  9, 11,     10, 48, 59,               B,
    0,100, 10, 20,250, 50,  1,100,  1,100,      1,  1,  1,   1,	Z_60_00  },

{ ICC__VENEZUELA,
  (IDT            ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT        ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
   33, 67,800,             80,135,  6,  8,     10, 48, 89,   R|    A|C    ,
   10,100, 10,  0,  0, 50,  1,100,  1,100,      4,  6, 61,3601,	Z_UNK  },

{ ICC__VIETNAM,
  (IDT    |ODT    ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
  (    SDT|ODT    ) |    (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
                         (USR|UKR|SRR    ) | (SBY|MBY|LBY        ),
   40, 60,800,           80, 80,  6,  8,	   10, 48, 59,           C|B|G,
   10,100, 10, 50, 50, 50,  1,100,  2,100,	   10,  2, 61,   0,	Z_UNK  },
};

#undef IDT
#undef SDT
#undef ODT
#undef BDT
#undef SBY
#undef MBY
#undef LBY
#undef BBY
#undef OBY
#undef USR
#undef UKR
#undef SRR
#undef ORR
#undef RRS
#undef XXS

#undef H
#undef R
#undef L
#undef D
#undef A
#undef C
#undef Y
#undef B


/* ************************************************************************* */
#endif /* WE_ARE_DEFINING_VARIABLES */

#endif /* _CSC_TABLED_H */
