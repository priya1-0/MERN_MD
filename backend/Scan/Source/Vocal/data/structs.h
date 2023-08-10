
/* ************************************************************************* */
/*
 *  structs.h
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
 *  Module:     DATA
 *
 *  This file includes the system's structure and symbol declarations.
 *
 *  Revision Number:    $Revision$
 *  Revision Status:    $State$
 *  Last Modified:      $Date$
 *  Identification:     $Id$
 *
 *  Revision History:   $Log$
 *  Revision History:   Revision 1.1.6.2  2009/04/28 19:33:26  zhangn1
 *  Revision History:   SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *  Revision History:
 *  Revision 1.0  1994/01/31  00:00:00  VD
 *  Initial release of software
 *
 */
/* ************************************************************************* */

#ifndef _DATA_STRUCTS_H
#define _DATA_STRUCTS_H

#include "include/config.h"
#include "include/const.h"

#include "include/mailbox.h"
#include "include/mbx_circ.h"

#include "include/callprog.h"
#include "data/telstr.h"

#include "include/tonedt.h"

#include "data/knlcfg.h"
#include "data/knlstr.h"

#include "data/modstr.h"
#include "data/modcfg.h"

#include "data/cmnstr.h"

#include "data/telstr.h"
#include "data/telcfg.h"

#include "net/sockaddr.h"

#include "lib34l/_v34syn.h"
#include "data/v34vastr.h"
#include "data/v34ph3st.h"
#include "libph2/constph2.h"

#include "include/clockpll.h"

extern const fract sine_table [];

#endif /* _DATA_STRUCTS_H */
