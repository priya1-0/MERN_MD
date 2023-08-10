/************************************************************************
*
* MODULE: bsm_DAA.c
*
* OWNER:
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* FUNCTIONS:
* --Public--
* bsm_initDAA()
* bsm_DAA_Reset()
* bsm_set_DAA_FC_RGDTb()
* bsm_clear_DAA_FC_RGDTb()
* bsm_read_DAA_RGDT()
* bsm_set_DAA_OFHKb()
* bsm_clear_DAA_OFHKb()
* bsm_set_SPFC_DSR()
* bsm_clear_SPFC_DSR()
* bsm_set_SPFC_CTS()
* bsm_clear_SPFC_CTS()
* bsm_read_SPFC_RTS()
* bsm_read_SPFC_DTR()
*
* --Private--
* test_gpio()
*
* DESCRIPTION: Board support for the DAA and supplemental HW flow control
*              pins.
*
*************************************************************************/
#define DEFINED_HERE
#include "bsm_DAA.h"
#undef DEFINED_HERE

/*******************************************************************************************

FUNCTION: bsm_initDAA

DESCRIPTION: This function initializes the GPIO and McBSP associated with the DAA.
             It also setupsup and initializes GPIO associated with hardware flow
             control of the serial port. note: this requires board modification
             to use this configuration.

ARGS:
        <none>

RETURNS:
    <none>
*******************************************************************************************/
void bsm_initDAA(){
    /* McBSP Configuration*/
    MCBSP_Config daa_config = {
        0x0000,         /* spcr1 */
        0x0200,         /* spcr2 */
        0x0040,         /* rcr1 */
        0x0045,         /* rcr2 */
        0x0040,         /* xcr1 */
        0x0045,         /* xcr2 */
        0x0000,         /* srgr1 */
        0x2000,         /* srgr2 */
        0x0000,         /* mcr1 */
        0x0000,         /* mcr2 */
        0x0080,         /* pcr */
        0x0000,         /* rcera */
        0x0000,         /* rcerb */
        0x0000,         /* rcerc */
        0x0000,         /* rcerd */
        0x0000,         /* rcere */
        0x0000,         /* rcerf */
        0x0000,         /* rcerg */
        0x0000,         /* rcerh */
        0x0000,         /* xcera */
        0x0000,         /* xcerb */
        0x0000,         /* xcerc */
        0x0000,         /* xcerd */
        0x0000,         /* xcere */
        0x0000,         /* xcerf */
        0x0000,         /* xcerg */
        0x0000          /* xcerh */
    };

    /*Enable DAA pins as GPIO*/
    HPI_FSET(HGPIOEN, DAA_OFHK_EN,     0x01);    // Enable OFHK I/O
    HPI_FSET(HGPIOEN, DAA_RGDT_EN,     0x01);    // Enable RGDT I/O
    HPI_FSET(HGPIOEN, DAA_FC_RGDTb_EN, 0x01);    // Enable FC_RGDTb I/O

    /* Ensure DAA output is out of reset */
    not_reset_DAA();

    /* Setup direction registers for the DAA GPIO pins*/
    DAA_OFHK_Dir     |=  (DAA_OFHK);        // output
    DAA_RGDT_Dir     &= ~(DAA_RGDT);    // input
    DAA_FC_RGDTb_Dir |=  (DAA_FC_RGDTb); // output
    DAA_RESET_Dir    |=      (DAA_RESET);       // output

    /* Set OnHook by default*/
    bsm_set_DAA_OFHKb();

    /*Enable Serial Port Flow Control pins as GPIO*/
    HPI_FSET(HGPIOEN, SPFC_CTS_EN,      0x01);
    HPI_FSET(HGPIOEN, SPFC_RTS_EN,      0x01);
    HPI_FSET(HGPIOEN, SPFC_DTR_EN,      0x01);

    /* Setup direction registers for the Serial Port Flow Control GPIO pins*/
    SPFC_CTS_Dir |=  (SPFC_CTS);     //output
    SPFC_RTS_Dir &= ~(SPFC_RTS);     //input
    SPFC_DTR_Dir &= ~(SPFC_DTR);     //input

    /*Setup McBSP1*/
    //Open and configure the MCBSP port
    hDAA_mcbsp = MCBSP_open(MCBSP_PORT1, MCBSP_OPEN_RESET);
    MCBSP_config(hDAA_mcbsp, &daa_config);


    /* Start McBSP*/
    MCBSP_write16(hDAA_mcbsp,0);
    MCBSP_start(hDAA_mcbsp, MCBSP_XMIT_START|MCBSP_RCV_START, MCBSP_SRGR_DEFAULT_DELAY);

}

/*******************************************************************************************

FUNCTION: bsm_DAA_Reset

DESCRIPTION: This function Toggles the reset of the DAA.
Note: This must be called when HTMR functionality exists (after BIOS initializes).

ARGS:
        <none>

RETURNS:
    <none>
*******************************************************************************************/
void bsm_DAA_Reset()
{
    // Bring the DAA out of reset
    reset_DAA();
    GLB_HTMR_WAIT((UINT32)500);     // the DAA must be in reset for 250ns before it comes out.
    not_reset_DAA();
}


/*******************************************************************************************

FUNCTION: bsm_set_DAA_FC_RGDTb

DESCRIPTION: This function sets the FC_RGDTb line to the DAA.

ARGS:
        <none>

RETURNS:
    <none>
*******************************************************************************************/
void bsm_set_DAA_FC_RGDTb()
{
    set_DAA_FC_RGDTb();
}

/*******************************************************************************************

FUNCTION: bsm_clear_DAA_FC_RGDTb

DESCRIPTION: This function clears the FC_RGDTb line to the DAA.

ARGS:
        <none>

RETURNS:
    <none>
*******************************************************************************************/
void bsm_clear_DAA_FC_RGDTb()
{
    clear_DAA_FC_RGDTb();
}

/*******************************************************************************************

FUNCTION: bsm_read_DAA_RGDT

DESCRIPTION: This function read the RGDT line from the DAA.

ARGS:
        <none>

RETURNS:
    BOOL: TRUE if set high, FALSE otherwise
*******************************************************************************************/
BOOL bsm_read_DAA_RGDT()
{
    return read_DAA_RGDT();
}

/*******************************************************************************************

FUNCTION: bsm_set_DAA_OFHKb

DESCRIPTION: This function sets the OFHKb line to the DAA.

ARGS:
        <none>

RETURNS:
    <none>
*******************************************************************************************/
void bsm_set_DAA_OFHKb()
{
    set_DAA_OFHKb();
}

/*******************************************************************************************

FUNCTION: bsm_clear_DAA_OFHKb

DESCRIPTION: This function clears the OFHKb line to the DAA.

ARGS:
        <none>

RETURNS:
    <none>
*******************************************************************************************/
void bsm_clear_DAA_OFHKb()
{
    clear_DAA_OFHKb();
}

/*******************************************************************************************

FUNCTION: bsm_set_SPFC_DSR

DESCRIPTION: This function sets the SPFC_DSR line for the Serial Port Hardware Flow Control.

ARGS:
        <none>

RETURNS:
    <none>
*******************************************************************************************/
void bsm_set_SPFC_DSR()
{
    set_SPFC_DSR();
}

/*******************************************************************************************

FUNCTION: bsm_clear_SPFC_DSR

DESCRIPTION: This function clears the SPFC_DSR line for the Serial Port Hardware Flow Control.

ARGS:
        <none>

RETURNS:
    <none>
*******************************************************************************************/
void bsm_clear_SPFC_DSR()
{
    clear_SPFC_DSR();
}

/*******************************************************************************************

FUNCTION: bsm_set_SPFC_CTS

DESCRIPTION: This function sets the CTS line for the Serial Port Hardware Flow Control.

ARGS:
        <none>

RETURNS:
    <none>
*******************************************************************************************/
void bsm_set_SPFC_CTS()
{
    set_SPFC_CTS();
}

/*******************************************************************************************

FUNCTION: bsm_clear_SPFC_CTS

DESCRIPTION: This function clears the CTS line for the Serial Port Hardware Flow Control.

ARGS:
        <none>

RETURNS:
    <none>
*******************************************************************************************/
void bsm_clear_SPFC_CTS()
{
    clear_SPFC_CTS();
}

/*******************************************************************************************

FUNCTION: bsm_read_SPFC_RTS

DESCRIPTION: This function read the RGDT line from the Serial Port Hardware Flow Control.

ARGS:
        <none>

RETURNS:
    BOOL: TRUE if set high, FALSE otherwise
*******************************************************************************************/
BOOL bsm_read_SPFC_RTS()
{
    return read_SPFC_RTS();
}

/*******************************************************************************************

FUNCTION: bsm_read_SPFC_DTR

DESCRIPTION: This function read the DTR line from the Serial Port Hardware Flow Control.

ARGS:
        <none>

RETURNS:
    BOOL: TRUE if set high, FALSE otherwise
*******************************************************************************************/
BOOL bsm_read_SPFC_DTR()
{
    return read_SPFC_DTR();
}

/*******************************************************************************************

FUNCTION: daa_test_gpio

DESCRIPTION: This function is used for line level debug testing. It is not part of production
             code.

ARGS:
        <none>

RETURNS:
    <none>
*******************************************************************************************/
void daa_test_gpio(void){
    volatile BOOL valueRead;

    while(1) {
        bsm_set_DAA_FC_RGDTb();
        bsm_set_DAA_OFHKb();
        valueRead = bsm_read_DAA_RGDT();

        bsm_set_SPFC_DSR();
        bsm_set_SPFC_CTS();
        valueRead = bsm_read_SPFC_RTS();
        valueRead = bsm_read_SPFC_DTR();

        GLB_LTMR_WAIT((UINT32)100);        //wait 100ms

        bsm_clear_DAA_FC_RGDTb();
        bsm_clear_DAA_OFHKb();
        valueRead = bsm_read_DAA_RGDT();

        bsm_clear_SPFC_DSR();
        bsm_clear_SPFC_CTS();
        valueRead = bsm_read_SPFC_RTS();
        valueRead = bsm_read_SPFC_DTR();
        GLB_LTMR_WAIT((UINT32)100);        //wait 100ms
    }
}


