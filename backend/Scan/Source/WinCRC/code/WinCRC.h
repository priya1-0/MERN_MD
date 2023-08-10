// WinCRC.h : main header file for the WINCRC application
//

#if !defined(AFX_WINCRC_H__E9593606_13F9_11D6_8835_000102D53C94__INCLUDED_)
#define AFX_WINCRC_H__E9593606_13F9_11D6_8835_000102D53C94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWinCRCApp:
// See WinCRC.cpp for the implementation of this class
//

class CWinCRCApp : public CWinApp
{
public:
	CWinCRCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinCRCApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWinCRCApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINCRC_H__E9593606_13F9_11D6_8835_000102D53C94__INCLUDED_)
