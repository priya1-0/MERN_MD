/********************************************************************
DOCUMENT

$Revision$

$Date$

$RCSfile$

NAME:  tbm_tctl.h

PURPOSE  This module provides an interface between the Channel and
         the Link layer.

USAGE:  none

ENDDOCUMENT
********************************************************************/
#ifndef tbm_tctl_h
#define tbm_tctl_h

#include "..\types.h"
#include "tbt_handler.h"

#ifdef DEFINED_HERE
        #define SCOPE
#else
        #define SCOPE extern
#endif

#include "tbt_channel.h"

// Global Functions
SCOPE BOOL tbm_linkAutoID(tbt_dlFrameType * dlFrame);
SCOPE BOOL tbm_OpenDLReq(tbt_dlFrameType * dlFrame);

#endif
