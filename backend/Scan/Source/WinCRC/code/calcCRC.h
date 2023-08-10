// calcCRC.h: interface for the calcCRC class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALCCRC_H__A69A89C3_14FC_11D6_8835_000102D53C94__INCLUDED_)
#define AFX_CALCCRC_H__A69A89C3_14FC_11D6_8835_000102D53C94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class calcCRC  
{
public:
	calcCRC();
	unsigned short calculate (unsigned short, unsigned char);
    unsigned short calculate_X16_X15_X2_1(unsigned short, int);
    unsigned short calcCRC8(unsigned short, unsigned char);
	unsigned long  calc32(unsigned long, unsigned char);
	virtual ~calcCRC();

};

#endif // !defined(AFX_CALCCRC_H__A69A89C3_14FC_11D6_8835_000102D53C94__INCLUDED_)
