// WinCRCDlg.cpp : implementation file
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include "WinCRC.h"
#include "WinCRCDlg.h"
#include "HelpDialog.h"
#include "readHex.h"
#include "crcCalc.h"
#include "CRCTemplate.h"
#include "InputTranslation.h"
#include "calcCRC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinCRCDlg dialog

CWinCRCDlg::CWinCRCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWinCRCDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWinCRCDlg)
	m_calcCRC = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWinCRCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWinCRCDlg)
	DDX_Control(pDX, IDC_WRITE_OUT, m_writeOut);
	DDX_Control(pDX, IDC_INPUT_DATA, m_InputData);
	DDX_Control(pDX, IDC_ALGO, m_algo);
	DDX_Control(pDX, IDC_COMP_CRC, m_compCRC);
	DDX_Control(pDX, IDC_REVERSE_BITS, m_reverseBits);
	DDX_Control(pDX, IDC_INPUT_FORMAT, m_inputFormat);
	DDX_Control(pDX, IDC_TEMPLATE_FILE, m_templateFile);
	DDX_Control(pDX, IDC_INPUT_FILE, m_inputFile);
	DDX_Control(pDX, IDC_OUTPUT_FILE, m_outputFile);
	DDX_Control(pDX, IDC_FILL_VALUE, m_fillValue);
	DDX_Control(pDX, IDC_END_ADDR, m_endAddr);
	DDX_Control(pDX, IDC_DONT_USE_TEMPLATE, m_dontUseTemplate);
	DDX_Control(pDX, IDC_CRC_SEED, m_seedCRC);
	DDX_Control(pDX, IDC_START_ADDR, m_startAddr);
	DDX_Text(pDX, IDC_CALC_CRC, m_calcCRC);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWinCRCDlg, CDialog)
	//{{AFX_MSG_MAP(CWinCRCDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDCALC, OnCalc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinCRCDlg message handlers

BOOL CWinCRCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	ReadInitFile();

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWinCRCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWinCRCDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWinCRCDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


// Input Hex File Selection
void CWinCRCDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	CFileDialog selectInputFile(TRUE, NULL, NULL, 0, 0, NULL);
	if (selectInputFile.DoModal() == IDOK)
	{
		m_inputFile.SetWindowText(selectInputFile.GetPathName());
		UpdateData(FALSE);
	}	
}

// Input Template File Selection
void CWinCRCDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	CFileDialog selectTemplateFile(TRUE, NULL, NULL, 0, 0, NULL);
	if (selectTemplateFile.DoModal() == IDOK)
	{
		m_templateFile.SetWindowText(selectTemplateFile.GetPathName());
		UpdateData(FALSE);
	}	
}

// Output File Selection
void CWinCRCDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	CFileDialog selectOutputFile(TRUE, NULL, NULL, 0, 0, NULL);
	if (selectOutputFile.DoModal() == IDOK)
	{
		m_outputFile.SetWindowText(selectOutputFile.GetPathName());
		UpdateData(FALSE);		
	}
}

void CWinCRCDlg::OnCalc() 
{
// TODO: Add your control notification handler code here
CString temp;
unsigned long   hex_size;
unsigned char   *ptr;
unsigned long   y;
unsigned short  chksum;
unsigned long	crc32;
unsigned short  seed = 0;
unsigned short  fill_char = 0xffff;
unsigned long   min_addr = 0;
unsigned long   max_addr = 0xffffff;
unsigned char   *hex_data;
CString			 cInputFile, cTemplateFile, cOutputFile, cInputData;
char            *input_file;
char            *templateFileIn;
char            *crcFileOut;
CCRCTemplate	 crcTemplate;
InputTranslation inputTrans;
calcCRC			 crc;
int				 readStatus;
char            *inputData;
FILE            *fbin=NULL;

	m_startAddr.GetWindowText(temp);
	sscanf (temp, "%06X", &min_addr );	

	m_endAddr.GetWindowText(temp);
	sscanf (temp, "%06X", &max_addr );	

	m_seedCRC.GetWindowText(temp);
	sscanf (temp, "%05X", &seed );

	m_fillValue.GetWindowText(temp);
	sscanf (temp, "%05X", &fill_char );

	m_inputFile.GetWindowText(cInputFile);
	input_file = cInputFile.GetBuffer(3);

	m_templateFile.GetWindowText(cTemplateFile);
	templateFileIn = cTemplateFile.GetBuffer(3);

	m_outputFile.GetWindowText(cOutputFile);
	crcFileOut = cOutputFile.GetBuffer(3);

    m_InputData.GetWindowText(cInputData);
    inputData = cInputData.GetBuffer(2);

	hex_size = max_addr - min_addr + 1;

	if ((hex_data = (unsigned char *)malloc (hex_size)) == NULL) 
	{
		MessageBox("Out of Memory for Hex Data", NULL, MB_OK);
		exit(1);
	}
	
	memset (hex_data, (char) (0xff & fill_char), hex_size);

	//
	// Which input format is to be used?
	//
	readStatus = m_inputFormat.GetCurSel();
	switch (m_inputFormat.GetCurSel())
	{
		case 0:
			readStatus = inputTrans.readHexFile (input_file, hex_data, min_addr, max_addr);
			break;

		case 1:
			readStatus = inputTrans.readMotorolaFile (input_file, hex_data, min_addr, max_addr);
			break;

		case 2:
			readStatus = inputTrans.readHexFile (input_file, hex_data, m_reverseBits.GetCheck());
			hex_size = readStatus;
			break;

      case 3:
			readStatus = inputTrans.readHexBox (inputData, hex_data, m_reverseBits.GetCheck());
			hex_size = readStatus;
         break;

		default:
			MessageBox("Illegal Input File Type", NULL, MB_OK);
			exit(1);
			break;
	}

	if (readStatus < 0)
	{
		MessageBox("Input File Open Error", NULL, MB_OK);
		exit(1);
	}
		
	chksum = seed;

	crc32 = seed;
	crc32 <<= 16;
	crc32 += seed;
		
	for  (ptr=hex_data, y=0; y < hex_size; ++y, ++ptr) 
	{
      switch(m_algo.GetCurSel())
      {
         case 0:
            chksum = crc.calculate (chksum, *ptr);
            break;
		 case 1:
            chksum = crc.calculate_X16_X15_X2_1(chksum, (int)(*ptr));
            break;
         case 2:
		    chksum += *ptr;
            break;
         case 3:
            chksum = crc.calcCRC8(chksum, *ptr);
            break;
		 case 4:
			crc32 = crc.calc32(crc32, *ptr);
      }
	}

	if (m_reverseBits.GetCheck())
	{
		chksum = reverseBits(chksum);
		crc32 = reverseBits32(crc32);

	}

	if (m_compCRC.GetCheck())
	{
		chksum ^= 0xffff;
		crc32 ^= 0xffffffff;
	}

	if (m_writeOut.GetCheck())
	{
		fbin = fopen("out.bin", "wb+" );
		if( fbin == NULL )
		{
			MessageBox("Output Binary File Open Error", NULL, MB_OK);
			exit(1);
		}
		else {
			ptr=hex_data;	
			fwrite(ptr, 0x4000, hex_size/0x4000, fbin);
			if (hex_size%0x4000) {
				ptr += ((hex_size/0x4000) * 0x4000);
				fwrite(ptr, hex_size%0x4000, 1, fbin);
			}

			fputc((crc32>>24)& 0xff, fbin);
			fputc((crc32>>16)& 0xff, fbin);
			fputc((crc32>>8) & 0xff, fbin);
			fputc((crc32)    & 0xff, fbin);
			fclose (fbin);
		}
	} 
	
	free (hex_data);

	if (templateFileIn[0] != 0 && !m_dontUseTemplate.GetCheck())
	{
		if (m_algo.GetCurSel() ==  4) {
			switch (crcTemplate.writeTemplate32 (crc32, templateFileIn, crcFileOut))
			{
				case -1:
					MessageBox("Template Input File Open Error", NULL, MB_OK);
					break;

				case -2:
					MessageBox("Template Output File Open Error", NULL, MB_OK);
					break;

				default:
					break;
			}
		}
		else {
			switch (crcTemplate.writeTemplate (chksum, templateFileIn, crcFileOut))
			{
				case -1:
					MessageBox("Template Input File Open Error", NULL, MB_OK);
					break;

				case -2:
					MessageBox("Template Output File Open Error", NULL, MB_OK);
					break;

				default:
					break;
			}
		}
	}

	if (m_algo.GetCurSel() ==  4) {
		m_calcCRC.Format("0x%08x", crc32);
	}
	else {
		m_calcCRC.Format("0x%04x", chksum);
	}
	UpdateData(FALSE);

	WriteInitFile();
}


void CWinCRCDlg::ReadInitFile()
{
char dataArray[300];
FILE *f = NULL;
int temp;

	f = fopen("winCRC.ini", "r" );
	getcwd(iniFilePath, sizeof(iniFilePath));
	
	if( f == NULL )
	{
		MessageBox("Initialization File Open Error", NULL, MB_OK);
		return;
	}
	if( (fgetline(f, dataArray, sizeof(dataArray))) != EOF)			// 1
	{
		m_startAddr.SetWindowText(dataArray);
	}

	if( (fgetline(f, dataArray, sizeof(dataArray))) != EOF)			// 2
	{
		m_seedCRC.SetWindowText(dataArray);
	}
		
	if( (fgetline(f, dataArray, sizeof(dataArray))) != EOF)			// 3
	{
		m_endAddr.SetWindowText(dataArray);
	}	

	if( (fgetline(f, dataArray, sizeof(dataArray))) != EOF)			// 4
	{
		m_fillValue.SetWindowText(dataArray);
	}

	if( (fgetline(f, dataArray, sizeof(dataArray))) != EOF)			// 5
	{
		sscanf(dataArray, "%d", &temp);
		m_inputFormat.SetCurSel(temp);
	}

	if( (fgetline(f, dataArray, sizeof(dataArray))) != EOF)			// 6
	{
		sscanf(dataArray, "%d", &temp);
		m_dontUseTemplate.SetCheck(temp);
	}

	if( (fgetline(f, dataArray, sizeof(dataArray))) != EOF)			// 7
	{
		m_inputFile.SetWindowText(dataArray);
	}

	if( (fgetline(f, dataArray, sizeof(dataArray))) != EOF)			// 8
	{
		m_templateFile.SetWindowText(dataArray);
	}
	
	if( (fgetline(f, dataArray, sizeof(dataArray))) != EOF)			// 9
	{
		m_outputFile.SetWindowText(dataArray);
	}

	if( (fgetline(f, dataArray, sizeof(dataArray))) != EOF)			// 10
	{
		sscanf(dataArray, "%d", &temp);
		m_reverseBits.SetCheck(temp);
	}

   if( (fgetline(f, dataArray, sizeof(dataArray))) != EOF)			// 11
	{
		sscanf(dataArray, "%d", &temp);
		m_compCRC.SetCheck(temp);
	}

	if( (fgetline(f, dataArray, sizeof(dataArray))) != EOF)			// 12
	{
		sscanf(dataArray, "%d", &temp);
		m_algo.SetCurSel(temp);
	}

	if( (fgetline(f, dataArray, sizeof(dataArray))) != EOF)			// 13
	{
		sscanf(dataArray, "%d", &temp);
		m_writeOut.SetCheck(temp);
	}
	
	fclose(f);
	UpdateData(FALSE);
}

void CWinCRCDlg::WriteInitFile()
{
CString temp;
FILE *f = NULL;
int val;

	chdir(iniFilePath);

	f = fopen("winCRC.ini", "w+" );
	if( f == NULL ){
		MessageBox("Initialization File Open Error", NULL, MB_OK);
		exit(-1);
	}
	m_startAddr.GetWindowText(temp);
	fprintf (f, "%s  ; Code Starting Address\n", temp);			// 1

	m_seedCRC.GetWindowText(temp);
	fprintf (f, "%s  ; CRC Seed Value\n", temp);				// 2

	m_endAddr.GetWindowText(temp);
	fprintf (f, "%s  ; Code Ending Address\n", temp);			// 3

	m_fillValue.GetWindowText(temp);
	fprintf (f, "%s  ; Unused Memory Fill Value\n", temp);		// 4

	val = m_inputFormat.GetCurSel();
	fprintf (f, "%d  ; Input File Format (0:Intel Hex, 1:Motorola S-Rec, 2:ASCII Hex, 3:ASCII Text Box)\n", val); // 5

	val = m_dontUseTemplate.GetCheck();
	fprintf (f, "%d  ; Don't Use Template Files (0:Unchecked, 1:Checked)\n", val);	// 6	

	m_inputFile.GetWindowText(temp);
	fprintf (f, "%s  ; Input File\n", temp);					// 7

	m_templateFile.GetWindowText(temp);
	fprintf (f, "%s  ; Input Template File\n", temp);			// 8

	m_outputFile.GetWindowText(temp);							// 9
	fprintf (f, "%s  ; Output File\n", temp);

    val = m_reverseBits.GetCheck();								// 10
	fprintf (f, "%d  ; Reverse Bits (0:Unchecked, 1:Checked)\n", val);

    val = m_compCRC.GetCheck();									// 11
	fprintf (f, "%d  ; Compliment CRC (0:Unchecked, 1:Checked)\n", val);

	val = m_algo.GetCurSel();									// 12
	fprintf (f, "%d  ; Algorithm (0:CCITT CRC, 1:X^16+X^15+X^2+1), 2:Checksum, 3:8 bit CRC, 4: 32 bit CRC, \n", val);

    val = m_writeOut.GetCheck();								// 13
	fprintf (f, "%d  ; Write out.bin binary file\n", val);

	fprintf (f, ";\n; All initialization tokens MUST be terminated with a semi-colon (;)\n");

	fclose(f);

}

int CWinCRCDlg::fgetline(FILE *fptr, char *string, int size )
{
int  c;
int  i=0;
int endOfToken=FALSE;

	/*
	** get characters from the file until the maximum number of
	** characters, "size",  for the string "string" has been reached
	** or until EOF has been reached or until the end of line has
	** been reached.
	*/
	while( ( --size > 0 ) && 
		(((c = fgetc(fptr)) != EOF ) && c != '\n' )) 
	{
		if (c == ';')
		{
			endOfToken=TRUE;
		}
		else
		{
			if (!endOfToken)
				string[i++] = c;
		}
	}

	/*
	** verify that the string is NULL terminated.
	*/
	string[i] = '\0';

	/*
	** we will only return EOF if EOF is the only character read.
	*/
	if( c == EOF && i == 0 ){
		return( EOF );
	}
	else {

		/*
		** if EOF was found at the end of a line of characters,
		** put the EOF back and return just the number of
		** characters read.  The EOF will be picked up on the
		** next call to fgetline.
		*/
		if( c == EOF ){
			fputc( c, fptr );
			i--;
		}
		
		// Strip trailing spaces or tabs from end of string
		while(string[i-1] == ' ' || string[i-1] == '\t') --i;
		string[i] = '\0';

	
		/*
		** otherwise, return the number of characters read.     
		*/
		return( i );
	}

}


void CWinCRCDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	WriteInitFile();

	CDialog::OnCancel();
}

unsigned short CWinCRCDlg::reverseBits(unsigned short data) 
{
unsigned short a, b, temp;

	for (	a = 0x8000, b = 0x0001, temp = 0;
			b != 0; 
			b <<= 1, a >>= 1)
	{
		temp |= (data & b) ? a:0; 
	}

return temp;
}

unsigned long CWinCRCDlg::reverseBits32(unsigned long data) 
{
unsigned long a, b, temp;

	for (	a = 0x80000000, b = 0x00000001, temp = 0;
			b != 0; 
			b <<= 1, a >>= 1)
	{
		temp |= (data & b) ? a:0; 
	}

return temp;
}
