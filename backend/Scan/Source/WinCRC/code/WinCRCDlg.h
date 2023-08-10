// WinCRCDlg.h : header file
//

#if !defined(AFX_WINCRCDLG_H__E9593608_13F9_11D6_8835_000102D53C94__INCLUDED_)
#define AFX_WINCRCDLG_H__E9593608_13F9_11D6_8835_000102D53C94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CWinCRCDlg dialog

class CWinCRCDlg : public CDialog
{
// Construction
public:
	CWinCRCDlg(CWnd* pParent = NULL);	// standard constructor

	void ReadInitFile();
	void WriteInitFile();
	unsigned short reverseBits(unsigned short);
	unsigned long  reverseBits32(unsigned long);
	int  fgetline(FILE *, char *, int);

	char  iniFilePath[100];

// Dialog Data
	//{{AFX_DATA(CWinCRCDlg)
	enum { IDD = IDD_WINCRC_DIALOG };
	CButton	m_writeOut;
	CEdit	m_InputData;
	CComboBox	m_algo;
	CButton	m_compCRC;
	CButton	m_reverseBits;
	CComboBox	m_inputFormat;
	CEdit	m_templateFile;
	CEdit	m_inputFile;
	CEdit	m_outputFile;
	CEdit	m_fillValue;
	CEdit	m_endAddr;
	CButton	m_dontUseTemplate;
	CEdit	m_seedCRC;
	CEdit	m_addrCRC;
	CEdit	m_startAddr;
	CString	m_calcCRC;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinCRCDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWinCRCDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnCalc();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINCRCDLG_H__E9593608_13F9_11D6_8835_000102D53C94__INCLUDED_)
