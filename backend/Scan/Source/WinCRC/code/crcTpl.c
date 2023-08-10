#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>
#include "crcTpl.h"


void CRCTemplate::writeTemplate (unsigned short  chksum, char *fileIn, char *fileOut)
{
FILE		*ftempIn = NULL, *fcrcOut = NULL;
char		linebuf[500];
char		crcbuf[6];
char		*strloc;

	sprintf (crcbuf, "%04X", chksum);
	
	ftempIn = fopen( fileIn, "r" );
	if( ftempIn == NULL ){
		printf( "Template Input File Open Error: %s \n", fileIn);
		perror( "Template Input File Open Error\n" );
		exit(-1);
	}
	
	fcrcOut = fopen( fileOut, "w+" );
	if( fcrcOut == NULL ){
		printf( "CRC Output File Open Error: %s", fileOut);
		perror( "CRC Output File Open Error" );
		exit(-1);
	}

	while (fgets(linebuf, 120, ftempIn) != NULL)
	{
		if ((strloc = strstr (linebuf, "$CRC")) != NULL)
		{
			memcpy (strloc, crcbuf, 4);
		}
		fputs (linebuf,  fcrcOut);
	}
	fclose (fcrcOut);
	fclose (ftempIn);
}
