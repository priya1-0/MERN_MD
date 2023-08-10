// InputTranslation.h: interface for the InputTranslation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INPUTTRANSLATION_H__A69A89C2_14FC_11D6_8835_000102D53C94__INCLUDED_)
#define AFX_INPUTTRANSLATION_H__A69A89C2_14FC_11D6_8835_000102D53C94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef enum
{
	INTEL_HEX,
	MOTOROLA_S_RECORD
} FILE_FORMAT_t;

class InputTranslation  
{
public:
	InputTranslation();
	int readHexFile(char *, unsigned char *, unsigned long, unsigned long);
	int readMotorolaFile(char *,unsigned char *, unsigned long, unsigned long);
	int readHexFile(char *,unsigned char *, int);
    int readHexBox(char *, unsigned char *, int); 
	int fgetline(FILE *, char *, int);
	unsigned char reverseBits (unsigned char);
	virtual ~InputTranslation();

private:
	static FILE_FORMAT_t format;

};

#endif // !defined(AFX_INPUTTRANSLATION_H__A69A89C2_14FC_11D6_8835_000102D53C94__INCLUDED_)
