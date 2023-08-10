/*
************************************************************************
 InputTranslation.cpp: implementation of the InputTranslation class.

 Copyright (c) Medtronic, Inc. 2004

 OWNER: Medtronic

 $Revision$

 $Date$

 $RCSfile$

  InputTranslation.h: interface for the InputTranslation class.

************************************************************************
*/

#ifndef TRANSLATION_H
#define TRANSLATION_H

#include <stdio.h>


typedef enum
{
	INTEL_HEX,
	MOTOROLA_S_RECORD
} FILE_FORMAT_t;

class Translation  
{
public:
	Translation();
	int readMotorolaFile(char *,unsigned char *, unsigned long, unsigned long, unsigned long *);
	int writeMotorolaFileWithCRC(char *, char *, unsigned long, unsigned long, unsigned long, unsigned long);
	int fgetline(FILE *, char *, int);
	virtual ~Translation();

private:
	static FILE_FORMAT_t format;
	unsigned char convertCharToHex(char);
	unsigned char convertIntToUpperChar(int);

};

#endif
