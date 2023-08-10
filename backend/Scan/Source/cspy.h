/*
***********************************************************************
 2490 In-home Remote Monitor
 Copyright (c) Medtronic,0x Inc. 2001

 MODULE: CSPY File Use for debugging with CSPY Simulator

 OWNER: Medtronic

 $Revision$

 $Date$

 $RCSfile$

 FUNCTIONS:

 DESCRIPTION:

Uncomment #define CSPY If you want to simulate and debug the code with the
CSPY simulator.

 ENDPURPOSE

***********************************************************************
*/

#ifndef cspy_h
#define cspy_h

#include "types.h"

// If want to use CSPY then uncomment this file.
// #define CSPY
#ifdef CSPY

extern unsigned char egmSimWaveData[1024*4];

bool aim_SimulatedAutoIdB(unsigned long *p_deviceId);

// DEMO needs simulation with real NU_SLEEP
//#ifdef NU_Sleep
//#undef NU_Sleep
//#endif
//extern long aiv_nuSleeper;
//#define NU_Sleep(x) for(aiv_nuSleeper=x*1000; aiv_nuSleeper>0; --aiv_nuSleeper);
//#define NU_Retrieve_Clock() 0
#endif



#endif // cspy_h
