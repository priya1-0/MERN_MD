/************************************************************************
*
* MODULE: bsm_serialport.c
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file contains the functions control the serial port
*
*************************************************************************/

/////////////
// includes
/////////////
#include <csl.h>
#include <csl_uart.h>

#include "global.h"
#include <string.h>
#include "bsm_event.h"
#include "bsm_SerialPort.h"

////////////
// Defines
////////////

// number of bytes that we can buffer.  Helps to have this as a power of 2.
#define RX_BUFFER_SIZE 64

// number of bytes that we can buffer.  Helps to have this as a power of 2.
#define TX_BUFFER_SIZE 256

// number of bytes in the FIFO
#define FIFO_SIZE 16

// The desired baud rate
#define BAUDRATE             115200
#define BAUDRATE_REG         ((UINT16)((CPU_FREQ/SLOW_PERIPH_CLK_DIV)/((UINT32)16*BAUDRATE)))
#define BITS_PER_SERIAL_BYTE 10

#define DEPTH_OF_HISTORY 16

///////////
// Global
///////////

// The buffer to put received bytes
BYTE RxBuffer[RX_BUFFER_SIZE];

// index to get the next byte from the RxBuffer
UINT16 RxBufferGet              = 0;

// index to put the next byte from the RxBuffer
UINT16 RxBufferPut              = 0;

// number of bytes in the RxBuffer
volatile UINT16 BytesInRxBuffer = 0;

// The buffer to put bytes to transmit
BYTE TxBuffer[TX_BUFFER_SIZE];

// index to get the next byte from the TxBuffer
UINT16 TxBufferGet             = 0;

// index to put the next byte from the TxBuffer
UINT16 TxBufferPut             = 0;

// number of bytes in the TxBuffer
volatile INT16 BytesInTxBuffer = 0;

// flag that is set if we receive a byte with an error
BOOL SerialPortError           = FALSE;

// flag that is set if we receive a byte with a full buffer
BOOL BufferFullError           = FALSE;

// Mutex flag
volatile BOOL TxBufferInUse    = TRUE;

char   PrevBuffer[DEPTH_OF_HISTORY][64];
UINT16 PrevBufferLength[DEPTH_OF_HISTORY];
BOOL   PrevBufferValid[DEPTH_OF_HISTORY];
UINT16 PrevBufferIndex;

///////////////
// Prototypes
///////////////
void bsm_UartInterrupt(void);
static void RxInterrupt(void);
static void TxInterrupt(void);


/******************************************************************

FUNCTION: bsm_SDInit

DESCRIPTION: This function intializes the serial port.

ARGS:
        unsigned char* p: A pointer to the bytes to send.

RETURNS:
    <none>

******************************************************************/
void bsm_SDInit(void)
{
    int i;

    for( i = 0; i < DEPTH_OF_HISTORY; i++ )
    {
        PrevBuffer[i][0]    = 0;
        PrevBufferLength[i] = 0;
        PrevBufferValid[i]  = 0;
    }

    // Reset the UART
    UART_FSET(URPECR, URST, 0);

    // Set the Baud Rate
    UART_RSET(URLCR, 0x80);
    UART_RSET(URDLL, BAUDRATE_REG & 0xFF);
    UART_RSET(URDLM, BAUDRATE_REG >> 8);

    // Set the rest of the UART registers
    UART_RSET(URLCR, 0x03);
    UART_RSET(URFCR, 0x87);
    UART_RSET(URIER, 0x00);
    UART_RSET(URLSR, 0x00);
    UART_RSET(URMCR, 0x00);

    // enable the interrupt
    IRQ_clear(IRQ_EVT_UART);
    IRQ_enable(IRQ_EVT_UART);

    // read the UART receive buffer to clear it
    while( UART_FGET(URLSR, DR) )
    {
        UART_RGET(URRBR);
    }

    // enable the tx and rx
    UART_FSET(URIER, ERBI, 1);
    UART_FSET(URIER, ETBEI, 1);

    // Enable the UART
    UART_FSET(URPECR, URST, 1);
}

/******************************************************************

FUNCTION: bsm_SDPrint

DESCRIPTION: This function sends data out the serial port with a
             newline at the end.

ARGS:
        unsigned char* p: A pointer to the bytes to send.

RETURNS:
    <none>

******************************************************************/
void bsm_SDPrint(char* p)
{
    UINT16 LengthP;
    // Calculate the length of the string once
    LengthP = strlen(p);

    // if there are bytes in the message ...
    if( LengthP > 0)
    {
        // write the bytes
        bsm_SDWrite(p, LengthP);
    }

    bsm_SDWrite("\n\r", 2);
}


/******************************************************************

FUNCTION: bsm_SDWrite_Unlimited

DESCRIPTION: This function sends data out the serial port. It
             can send a message larger than the transmit buffer
             but its blocking time is proportionate to the size
             of the message to print.

ARGS:
        unsigned char* p: A pointer to the bytes to send.
        UINT32   LengthP: Length of bytes associated with pointer
RETURNS:
    <none>

******************************************************************/
void bsm_SDWrite_Unlimited(char* p, UINT32 LengthP)
{
    UINT32 head;
    UINT32 tail;
    UINT32 i;
    UINT32 endCond;
    UINT32 lengthRemaining;

    // if there are bytes in the message ...
    if( LengthP > 0)
    {
        head            = 0;
        tail            = 0;
        lengthRemaining = LengthP;

        endCond         =  (LengthP / TX_BUFFER_SIZE);
        if( (LengthP % TX_BUFFER_SIZE) > 0 )
        {
            endCond++;
        }
        for(i=0; i<endCond; i++)
        {
            if(i == endCond - 1)
            {
                head += lengthRemaining;
            }
            else
            {
                head            += TX_BUFFER_SIZE;
                lengthRemaining -= TX_BUFFER_SIZE;
            }

            // write the bytes
            bsm_SDWrite(&p[tail], head - tail);
            GLB_LTMR_WAIT(1);
            tail = head;
        }
    }
}

/******************************************************************

FUNCTION: bsm_SDWrite

DESCRIPTION: This function sends data out the serial port.

ARGS:
        unsigned char* p: A pointer to the bytes to send.

RETURNS:
    <none>

******************************************************************/
void bsm_SDWrite(char* p, UINT16 LengthP)
{
    int i;
    // Set Mutex as inuse
    TxBufferInUse = TRUE;

    // check if the message would fit in the buffer
    if( LengthP > TX_BUFFER_SIZE )
    {
        return;
    }

    // check if there is enough room right now for the message
    if( TX_BUFFER_SIZE - BytesInTxBuffer < LengthP )
    {
        UINT32 Wait;

        // Wait = number of bytes in TX Buffer to fit the new message.
        Wait = TX_BUFFER_SIZE - LengthP;

        // Wait = Number of bytes that need to be sent
        Wait = BytesInTxBuffer - Wait;

        // Wait = Number of 16 byte packets that need to be sent rounded up and at least 2
        Wait = ((Wait + FIFO_SIZE-1)/FIFO_SIZE)+1;

        // Wait = Number of milliseconds to send the packets rounded up
        Wait = (Wait*16*BITS_PER_SERIAL_BYTE*1000);
        Wait = Wait +(BAUDRATE-1);
        Wait = Wait/BAUDRATE;

        GLB_LTMR_WAIT(Wait);

        if( TX_BUFFER_SIZE - BytesInTxBuffer < LengthP )
        {
            return;
        }
    }

    // add the entire message
    for( i = 0; i < LengthP; i++ )
    {
        IRQ_disable(IRQ_EVT_UART);

        // copy the character
        TxBuffer[TxBufferPut] = p[i];

        BytesInTxBuffer++;

        // move the PUT pointer
        TxBufferPut = (TxBufferPut+1)%TX_BUFFER_SIZE;

        IRQ_enable(IRQ_EVT_UART);
    }

    // if the transmit register is empty, then we need to place the first byte
    // into the register to start the interrupt
    IRQ_disable(IRQ_EVT_UART);
    if( UART_FGET(URLSR, THRE) == 1 )
    {
        BYTE Byte = TxBuffer[TxBufferGet];

        TxBufferGet = (TxBufferGet+1)%TX_BUFFER_SIZE;
        BytesInTxBuffer--;

        UART_RSET(URTHR, Byte);

        // Enable the transmit interrupt
        UART_FSET(URIER, ETBEI, 1);
    }
    IRQ_enable(IRQ_EVT_UART);

    // Set Mutex as available
    TxBufferInUse = FALSE;

}

/******************************************************************

FUNCTION: ReadLine

DESCRIPTION: This function read from the serial port until it finds
             a carriage return or line feed.

ARGS:
        <none>

RETURNS:
        <none>

******************************************************************/
void bsm_SDReadLine(char* Buffer, int Size)
{
    UINT16 CurrDepth = PrevBufferIndex;

    UINT16 Index     = 0;
    int    RxByte;
    int    i;

    do
    {
        // get a valid byte
        do
        {
            RxByte = bsm_SDRead();
            NU_Sleep(1);
        } while( RxByte == -1 );

        // if the first character is a carriage return or line feed
        if( (RxByte == '\r' || RxByte == '\n') && Index == 0)
        {
            RxByte = 0;
        }

        // if we got a backspace
        if( RxByte == '\b' )
        {
            // If this isn't the first byte...
            if( Index > 0 )
            {
                Index--;                              // back up one character and
                Buffer[Index] = 0;                    // Clear the byte.
            }
        }
        // if this is a valid byte and it is not then end of the password
        else if( RxByte && RxByte!='\r' && RxByte!='\n' && Index < Size )
        {
            Buffer[Index++] = RxByte;              // Add to the buffer
        }

        // If we got an up arrow...
        if( Index > 2 &&
            Buffer[Index-1] == 'A' &&
            Buffer[Index-2] == '[' &&
            Buffer[Index-3] == 0x1B )
        {
            // find the next previous history
            for( i = 0; i < DEPTH_OF_HISTORY; i++ )
            {
                CurrDepth = (CurrDepth-1)%DEPTH_OF_HISTORY;
                if( PrevBufferValid[CurrDepth] == TRUE )
                {
                    break;
                }
            }

            // copy the previous buffer to the current buffer
            strncpy(Buffer, PrevBuffer[CurrDepth], PrevBufferLength[CurrDepth]);

            // set the next index
            Index = PrevBufferLength[CurrDepth];

            bsm_SDPrint("");
            bsm_SDWrite(Buffer, Index);
        }
        // Loop as long as we don't get an end of line or fill the buffer
    } while( RxByte != '\r' && RxByte != '\n' && Index < Size);

    // copy the previous buffer to the current buffer
    strncpy(PrevBuffer[PrevBufferIndex], Buffer, Index);
    PrevBufferLength[PrevBufferIndex] = Index;
    PrevBufferValid[PrevBufferIndex]  = TRUE;

    // go to the next available slot
    PrevBufferIndex                   = (PrevBufferIndex+1) % DEPTH_OF_HISTORY;

    // if there is room, add a NULL at the end of the string
    if( Index < Size )
    {
        Buffer[Index] = 0;
    }
}

/******************************************************************

FUNCTION: bsm_SDRead

DESCRIPTION: This function returns a received character.

ARGS:
        <none>

RETURNS:
    int: -1 if no data available
         -2 if there was a serial port error
         0-255 for the data

******************************************************************/
int bsm_SDRead(void)
{
    BYTE Byte;

    if( SerialPortError )
    {
        IRQ_disable(IRQ_EVT_UART);

        // clear the error flag
        SerialPortError = FALSE;

        // reset all the pointers
        RxBufferGet     = 0;
        RxBufferPut     = 0;
        BytesInRxBuffer = 0;

        //re-initialize the serial port to reset the errors.
        bsm_SDInit();

        IRQ_enable(IRQ_EVT_UART);

        return -2;
    }

    // we had a buffer overrun
    if( BufferFullError )
    {
        IRQ_disable(IRQ_EVT_UART);

        // reset all the pointers
        RxBufferGet     = 0;
        RxBufferPut     = 0;
        BytesInRxBuffer = 0;

        // clear the error flag
        BufferFullError = FALSE;

        IRQ_enable(IRQ_EVT_UART);

        return -2;         // RJD: can we make this a different value from the serial port error?
    }

    // if there are bytes in the buffer
    if( BytesInRxBuffer > 0 )
    {
        IRQ_disable(IRQ_EVT_UART);

        // get the byte and move the index
        Byte        = RxBuffer[RxBufferGet];
        RxBufferGet = (RxBufferGet+1)%RX_BUFFER_SIZE;
        BytesInRxBuffer--;

        IRQ_enable(IRQ_EVT_UART);

        return Byte;
    }
    else
    {
        return -1;
    }
}


/******************************************************************

FUNCTION: bsm_SDReadBytes

DESCRIPTION: This function reads up to a number of bytes from the
                         serial port.  These are the bytes that are available
                         at the time of the call.

ARGS:
        BYTE* Buffer: A pointer to a buffer.
        UINT16 Length: The number of bytes available in the buffer

RETURNS:
        Negative numbers for an error.
        0 for no bytes available.
        Positive numbers for the number of bytes copied into the buffer.

******************************************************************/
int bsm_SDReadBytes(BYTE* Buffer, UINT16 Length)
{
    // Number of bytes we have captured this call
    int NumOfBytes = 0;

    // one byte that we have captured.
    int Byte;

    do
    {
        // read a btye
        Byte = bsm_SDRead();

        // if this is a valid byte...
        if( Byte > 0 )
        {
            // add the byte to the buffer
            Buffer[NumOfBytes] = Byte;
            // go to the next index
            NumOfBytes++;
        }
    }
    // while we are getting valid bytes and we have room for them...
    while( Byte > 0 && NumOfBytes < Length);

    // return the number of bytes put into the buffer
    return NumOfBytes;
}

/******************************************************************

FUNCTION: UartInterrupt

DESCRIPTION:  This function is called when the UART has an
              interrupt.  The interrupt source is determined and
              the handler for that interrupt is called.

ARGS:
        <none>

RETURNS:
    <none>

******************************************************************/
interrupt void bsm_UartInterrupt(void)
{
    UINT16 IIR;

    // loop while there are interrupts to handle
    while( ((IIR = UART_RGET(URIIR))&0x01) != 0x01)
    {
        // shift and mask to make the IDs low numbers
        IIR = (IIR >> 1) & 0x07;

        switch(IIR)
        {
        case 0x01:                      // Transmit interrupt
            TxInterrupt();
            break;

        case 0x02:                      // Data Received
        case 0x06:                      // Receiver Timeout
            RxInterrupt();
            break;

        default:
            break;
        }
    }
}

/******************************************************************

FUNCTION: TxInterrupt

DESCRIPTION:  This function is called when the transmitter is
              empty.  If there are more bytes in the buffer, the
              next byte is transmitted

ARGS:
        <none>

RETURNS:
    <none>

******************************************************************/
void TxInterrupt(void)
{
    UINT16 i;

    // if there are no bytes left...
    if( BytesInTxBuffer <= 0 )
    {
        // Disable the transmit interrupt
        UART_FSET(URIER, ETBEI, 0);
        return;
    }

    for( i = 0; i < FIFO_SIZE; i++)
    {
        // if there are no more bytes...
        if( BytesInTxBuffer <= 0 )
        {
            return;
        }

        // put the byte in the transmit holding register
        UART_RSET(URTHR, TxBuffer[TxBufferGet]);

        // move the Get pointer
        TxBufferGet = (TxBufferGet+1)%TX_BUFFER_SIZE;

        // there is 1 less byte in the Tx buffer
        BytesInTxBuffer--;
    }
}

/******************************************************************

FUNCTION: RxInterrupt

DESCRIPTION: This ISR is called when the serial port receives a
             byte.

ARGS:
        <none>

RETURNS:
    <none>

******************************************************************/
void RxInterrupt(void)
{
    UINT8 Byte;

    // while there is still data in the UART...
    while( UART_FGET(URLSR, DR) )
    {
        Byte = UART_RGET(URRBR);

        // if there was an error in the serial port
        if( (UART_RGET(URLSR) & (UART_URLSR_RFIER_ON |
                                 UART_URLSR_BI_ON |
                                 UART_URLSR_FE_ON |
                                 UART_URLSR_PE_ON |
                                 UART_URLSR_OE_ON ) ) != 0 )
        {
            // Reset the UART to clear the error
            UART_FSET(URPECR, URST, 0);
            UART_FSET(URPECR, URST, 1);

            // set the error flag and return
            SerialPortError = TRUE;
            return;
        }

        // check to see if there is room
        else if( BytesInRxBuffer >= RX_BUFFER_SIZE )
        {
            // set the flag and return
            BufferFullError = TRUE;
        }

        else
        {
            // put the byte in the buffer and move the index pointer
            RxBuffer[RxBufferPut] = Byte;
            RxBufferPut           = (RxBufferPut+1)%RX_BUFFER_SIZE;
            BytesInRxBuffer++;
        }
    }
}


/******************************************************************

FUNCTION: bsm_SDTxCheckMutex

DESCRIPTION: This function returns the mutex value of the transmit
             buffer

ARGS:
        <none>

RETURNS:
        BOOL: The mutex value

******************************************************************/
BOOL bsm_SDTxCheckMutex(void)
{
    return TxBufferInUse;
}


