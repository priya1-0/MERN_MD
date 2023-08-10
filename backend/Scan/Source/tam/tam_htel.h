/************************************************************************
*
* 2490 In-home Remote Monitor
* Copyright (c) Medtronic, Inc. 2001
*
* APPLICATION:   2490D
*
* MODULE:        tam_htel.h
*
* PURPOSE:  This file defines constants, types and enumerations.
*
********************************************************************/

#ifndef tam_htel_h
#define tam_htel_h

/* includes */
#include "global.h"
#include "tam_global.h"
//#include "tam_com.h"


/* defines */

#define tac_BYTES_PER_EGM_FRAME 2      // frame Id and data byte


#define tac_MAX_EGM_RECORD_TIME 10      // 30 seconds, limited due to
                                        // current buffer sizes for received
                                        // data
#define tac_MAX_IPG_EGM_RECORD_TIME 30      // 30 seconds, limited due to
// current buffer sizes for received
// data

#define tac_MAP_UPLINK_SIZE 132         // Header 2 bytes, Data bytes (128
                                        // bytes) and trailer 2 bytes (CRC)
#define tac_IPG_MAP_UPLINK_SIZE 35      // Header 2 bytes (Family Id and
                                        // Command Code), Data bytes (32 bytes
                                        // for 1 memory page) Parity byte
                                        // (1 bytes)
#define tac_MAP_TIMEOUT 100             // item map timeout

//Defines for the FPGA
#define tac_FPGAMiscCntrlReg2 *((int *)0x600032)
#define tac_A_DEMOD_SEL       ((int)0x0004)
#define tac_A_MANG_EN         ((int)0x0010)
#define tac_RX_LOW_GAIN_EN    ((int)0x0080)


/************************************************************************

                     Prototypes

************************************************************************/

/* public */
extern tat_status tam_Initialize_TelemetryA(tat_telemetryProtocolType);
extern tat_status tam_Send_Telemetry(BYTE *, USHORT, BYTE *, USHORT, BYTE);
extern tat_status tam_Continuous_Egm(BYTE *, BYTE, USHORT *,USHORT *, bool);
extern tat_status tam_Repeat_Downlink(BYTE *, USHORT, BYTE);
extern tat_status tam_Cancel_Repeat_Downlink(void);
extern tat_status tam_RTT_Test(BYTE *, USHORT,BYTE *, USHORT, USHORT);


// telemetry test code
#ifdef __TELEMA_TEST_CODE__
tat_status tam_Perform_Universal_Map(void);
tat_status tam_Perform_IPG_Universal_Map(void);
void tam_itemMap(void);
void telemATestCode(void);
#endif // __TELEMA_TEST_CODE__

#endif // tam_htel_h
