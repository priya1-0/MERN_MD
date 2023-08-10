// CRCTemplate.h: interface for the CCRCTemplate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CRCTEMPLATE_H__3C5C1963_14C0_11D6_8835_000102D53C94__INCLUDED_)
#define AFX_CRCTEMPLATE_H__3C5C1963_14C0_11D6_8835_000102D53C94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCRCTemplate  
{
public:
	CCRCTemplate();
	int writeTemplate (unsigned short, char *, char *);
	int writeTemplate32 (unsigned long, char *, char *);
	virtual ~CCRCTemplate();

};

#endif // !defined(AFX_CRCTEMPLATE_H__3C5C1963_14C0_11D6_8835_000102D53C94__INCLUDED_)
