// CRCTemplate.cpp: implementation of the CCRCTemplate class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WinCRC.h"
#include "CRCTemplate.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCRCTemplate::CCRCTemplate()
{

}

CCRCTemplate::~CCRCTemplate()
{

}

int CCRCTemplate::writeTemplate (unsigned short  chksum, char *fileIn, char *fileOut)
{
FILE		*ftempIn = NULL, *fcrcOut = NULL;
char		linebuf[500];
char		crcbuf[6];
char		temp[30];
char		*strloc;

	sprintf (crcbuf, "%04X", chksum);
	
	ftempIn = fopen( fileIn, "r" );
	if( ftempIn == NULL ){		
		return(-1);
	}
	
	fcrcOut = fopen( fileOut, "w+" );
	if( fcrcOut == NULL ){
		return(-2);
	}

	while (fgets(linebuf, 120, ftempIn) != NULL)
	{
		if ((strloc = strstr (linebuf, "$CRC")) != NULL)
		{
			strcpy (temp, strloc+4);
			memcpy (strloc, crcbuf, 4);
			strloc += 4;
			strcpy (strloc, temp);
		}
		fputs (linebuf,  fcrcOut);
	}
	fclose (fcrcOut);
	fclose (ftempIn);

return 0;
}

int CCRCTemplate::writeTemplate32 (unsigned long crc32, char *fileIn, char *fileOut)
{
FILE		*ftempIn = NULL, *fcrcOut = NULL;
char		linebuf[500];
char		temp[30];
char		crcbuf[10];
char		*strloc;

	sprintf (crcbuf, "%08X", crc32);
	
	ftempIn = fopen( fileIn, "r" );
	if( ftempIn == NULL ){		
		return(-1);
	}
	
	fcrcOut = fopen( fileOut, "w+" );
	if( fcrcOut == NULL ){
		return(-2);
	}

	while (fgets(linebuf, 120, ftempIn) != NULL)
	{
		if ((strloc = strstr (linebuf, "$CRC")) != NULL)
		{
			strcpy (temp, strloc+4);
			memcpy (strloc, crcbuf, 8);
			strloc += 8;
			strcpy (strloc, temp);
		}
		fputs (linebuf,  fcrcOut);
		memset (linebuf, 0, sizeof(linebuf));
	}
	fclose (fcrcOut);
	fclose (ftempIn);

return 0;
}
