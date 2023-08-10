/* Copyright (c) 2005 by Medtronic Inc.  All Rights Reserved */
/********************************************************************

MODULE:  2490

OWNER: name

$Revision$

$Date$

DESCRIPTION:

    Functions to replicate the simplicity of printf for the 2490
    platforms.

    For callers, the advantage to this function is that one does
    not have to declare a buffer, concern oneself with buffer/stack
    overflow using sprintf, or make a call to bsm_SDPrint.


    So the following, which will blow up the stack:

        char output[10];

        sprintf(output, "A string larger than 10 chars already, %d", x);
        bsm_SDPrint(output);


    Becomes the simple and safe:


        printf2490("A string larger than 10 chars already, %d", x);


    These functions are only app-level output. Just as with
    sprintf/printf, it can't be called from interrupts or
    non-idle tasks as it is currently written.



ENDPURPOSE
********************************************************************/



/////////////
// Includes
/////////////

#include "printf2490.h"

#include <stdio.h>
#include <stdarg.h>

#include "bsm_SerialPort.h"
#include "bsm_Event.h"


#define FP_BFR_SIZE (512)

static char snprintfBfr[FP_BFR_SIZE];





#ifdef UNIT_TEST_CCM

#warn "Unit testing enabled"

#include "assert2490.h"
#include <string.h>

#undef bsm_EHLock
static int ehLock;

#define bsm_EHLock(s) ehLock++;



#endif



/*
***********************************************************************

 FUNCTION:      _vprintf2490

 DESCRIPTION:

    This function accepts the special va_list argument and
    calls vsnprintf to create the output string.

    NOTE: vsnprintf (not vsprintf) helps assure the buffer is not
    overrun.

 FUNCTION RETURN:

    None.

 FUNCTION PARAMETERS:

    The "printf"-style format string
    The arguments for the "printf" as va_list


***********************************************************************
*/
static void _vprintf2490(const char * _formatString, va_list outputargs )
{
    int totalSizeWas;

    totalSizeWas = vsnprintf(snprintfBfr, FP_BFR_SIZE, (const char *) _formatString, outputargs);

    bsm_SDPrint(snprintfBfr);

    if (totalSizeWas >= FP_BFR_SIZE)
        bsm_EHLock("Overflowing output was passed to printf2490.");
}




/*
***********************************************************************

 FUNCTION:      printf2490

 DESCRIPTION:

    This public function accepts the same arguments as printf - i.e.
    the format string and any related arguments

    This function largely just converts the variadic function
    argument into a va_list parameter.

 FUNCTION RETURN:

    None.

 FUNCTION PARAMETERS:

    The "printf"-style format string
    The arguments for the "printf"


***********************************************************************
*/

void printf2490(char * _formatString, ... )
{
    va_list _args;

    va_start (_args, _formatString);

    _vprintf2490((const char*)_formatString, _args);

    va_end (_args);
}


/*
***********************************************************************

 FUNCTION:      asciiHex

 DESCRIPTION:

    This public function translates the binary bytes of one array
    into ascii hex of another. The passed length parameter
    represents the number of binary bytes to translate. The output
    array needs to be large enough to represent the binary input
    array plus one extra byte for a NULL terminator. This means that
    the output array should be sized accordingly.

    char ptrOut[(2*sizeof(ptrIn)) + 1];

    Example:
        ptrIn[]  = "\x01Hello World! - 1\x0023456789"
        ptrOut[] = "0148656c6c6f20576f726c6421202d2031003233343536373839" + "00"

 FUNCTION RETURN:

    ptrOut is filled with ASCII hex

 FUNCTION PARAMETERS:

    ptrIn       - pointer to character array with binary data to translate
    ptrInLength - length of binary data to translate
    ptrOut      - pointer to character array to be filled

***********************************************************************
*/

void asciiHex(char* ptrIn, unsigned int ptrInLength, char* ptrOut)
{
    char            tmp[3];
    unsigned int    binaryCounter=0;
    unsigned int    asciiCounter=0;

    // convert each byte of ptrIn to ascii hex into ptrOut
    for(binaryCounter = 0; binaryCounter < ptrInLength; binaryCounter++)
    {
        sprintf(tmp, "%.2x", *(ptrIn + binaryCounter));
        ptrOut[asciiCounter++] = tmp[0];
        ptrOut[asciiCounter++] = tmp[1];
    }
    ptrOut[asciiCounter++] = 0;     // add the NULL
}


#ifdef UNIT_TEST_CCM

char output[FP_BFR_SIZE + 2]; // One extra char, one terminator

void UTestPrintf2490(void)
{



    bsm_SDPrint("----------------------------------------------------------------");

    ehLock = 0;

    printf2490("Just a string, no args.");

    printf2490("Two ints: 25 --> %d, -3 --> %d", 25, -3);

    printf2490("Two strings: String1 --> %s, String2 --> %s", "String1", "String2");

    printf2490("A long and an int: 2256525 --> %ld, -3 --> %d", 2256525, -3);

    printf2490("String1 --> %s, 33 --> %d, string --> %.6s",

    "String1", 33, "string2662");

    printf2490("4294967295--> %lu, 3ABCDE33 --> %08lx, 'f'->%c", 0xFFFFFFFFL, 0x3ABCDE33L, 'f' );

    assert2490(0 == ehLock); // No overflows up to this point

    // Now test overflow check.
    // ---------------------------

    memset(output, 'A', sizeof(output));
    output[sizeof(output) -1] = 0; // Set terminator at end.

    // Pass "output" as a whopper string.
    printf2490("Here's \"output\" -> %s", output);


    assert2490(1 == ehLock); // Caught the overflow


}


#endif
