#ifndef _INCLUDE_SILABS_H
#define _INCLUDE_SILABS_H
/* Define constants for use in programming the SiLabs 3056 DAA */
#define DAA_Control1     1
#define DAA_Control2     2
#define DAA_IntMask      3
#define DAA_IntSource    4
#define DAA_DAAControl1  5
#define DAA_DAAControl2  6
#define DAA_SampleRate   7
#define DAA_PLLdivN      8
#define DAA_PLLdivM      9
#define DAA_DAAControl3  10
#define DAA_SSrev        11
#define DAA_LSDevStatus  12
#define DAA_LSrev        13
#define DAA_InterfaceCtl 14
#define DAA_Gain1        15
#define DAA_INcontrol1   16
#define DAA_INcontrol2   17
#define DAA_INcontrol3   18
#define DAA_INcontrol4   19
#define DAA_CPRxAtten    20
#define DAA_CPTxAtten    21
#define DAA_RingVldCtl1  22
#define DAA_RingVldCtl2  23
#define DAA_RingVldCtl3  24
#define DAA_ResistorCal  25
#define DAA_DCtermCtl    26
#define DAA_LCstatus     28
#define DAA_LoopVoltage  29
#define DAA_ACterm       30
#define DAA_DAAControl4  31
#define DAA_TxGainCtl2   32
#define DAA_RxGainCtl2   33
#define DAA_TxGainCtl3   34
#define DAA_RxGainCtl3   35
#define DAA_LCvoltIntTH  36
#define DAA_LCvoltIntCtl 37
#define DAA_PHybridReg1  45
#define DAA_PHybridReg2  46
#define DAA_PHybridReg3  47
#define DAA_PHybridReg4  48
#define DAA_PHybridReg5  49
#define DAA_PHybridReg6  50
#define DAA_PHybridReg7  51
#define DAA_PHybridReg8  52

/*
Register 16. International Control 1
Bit		D7		D6		D5		D4		D3		D2		D1		D0
Name   ACT2    OHS      ACT    IIRE     -       -       RZ      RT
*/
#define DAA_ITEL_MASK_REG16   0xE3
/*
Register 31. DAA Control 4
Bit		D7		D6		D5		D4		D3		D2		D1		D0
Name   FULL      FOH[1:0]       -      OHS2     -      FILT    LVFD
*/
#define DAA_ITEL_MASK_REG31   0x08

/*
Register 26. DC Termination Control
Bit		D7		D6		D5		D4		D3		D2		D1		D0
Name	 DCV[1:0]        MINI[1:0]      -       -      ILIM     DCR
*/
#define DAA_ITEL_MASK_REG26   0xF2

/*
Register 30. AC Termination Control
Bit		D7		D6		D5		D4		D3		D2		D1		D0
Name	-   	-   	-   	-   			ACIM[3:0]
*/
#define DAA_ITEL_MASK_REG30   0x0F

#endif /* _INCLUDE_SILABS_H */
