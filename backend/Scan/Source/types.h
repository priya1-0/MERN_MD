#ifndef __TYPES_H
#define __TYPES_H
#include <std.h>
#include <clk.h>


//standard data types
#define BOOL char

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef HIGH
#define HIGH 1
#endif

#ifndef LOW
#define LOW 0
#endif

#ifndef ON
#define ON 1
#endif

#ifndef OFF
#define OFF 0
#endif

#define bool  BOOL
#define true  TRUE
#define false FALSE
#define on    ON
#define off   OFF

typedef char BYTE;
typedef unsigned short USHORT;
typedef unsigned long ULONG;
typedef unsigned int UNSIGNED;
typedef void VOID;

typedef unsigned char UINT8;
typedef unsigned int UINT16;
typedef unsigned long UINT32;
typedef char INT8;
typedef int INT16;
typedef long INT32;

typedef unsigned long TICK_TIME;    //32bit


#define HTTP_DATETIME_LEN (29)


#endif

