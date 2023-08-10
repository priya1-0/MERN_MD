/************************************************************************
*
* MODULE: dbg_TelemB.h
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the functions to executed
*  Telemetry B debug port functionality.
*
*************************************************************************/
#ifndef DBG_TELEMB_H
#define DBG_TELEMB_H

#ifdef DEFINED_HERE
        #define SCOPE
#else
        #define SCOPE extern
#endif

#include "tbt_handler.h"

SCOPE void dbg_rcvTestFrame(char uplinkRate);
SCOPE void dbg_rcvTestFrameLoop(char uplinkRate);
SCOPE tbt_reqStatus dbg_itemTest (BOOL init, char testType);
SCOPE void dbg_itemTestSingle (char testType);
SCOPE void dbg_itemTestApp(char testType);
SCOPE void dbg_itemTestCount(char testType, char *testCount);


#undef SCOPE
#endif


