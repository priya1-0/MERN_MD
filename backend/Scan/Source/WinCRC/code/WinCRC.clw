; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CWinCRCDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "WinCRC.h"

ClassCount=4
Class1=CWinCRCApp
Class2=CWinCRCDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CHelpDialog
Resource3=IDD_WINCRC_DIALOG

[CLS:CWinCRCApp]
Type=0
HeaderFile=WinCRC.h
ImplementationFile=WinCRC.cpp
Filter=N
LastObject=CWinCRCApp

[CLS:CWinCRCDlg]
Type=0
HeaderFile=WinCRCDlg.h
ImplementationFile=WinCRCDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CWinCRCDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=WinCRCDlg.h
ImplementationFile=WinCRCDlg.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_WINCRC_DIALOG]
Type=1
Class=CWinCRCDlg
ControlCount=33
Control1=IDC_START_ADDR,edit,1350631552
Control2=IDC_CRC_SEED,edit,1350631552
Control3=IDC_END_ADDR,edit,1350631552
Control4=IDC_FILL_VALUE,edit,1350631552
Control5=IDC_REVERSE_BITS,button,1342242819
Control6=IDC_INPUT_FORMAT,combobox,1344340995
Control7=IDC_INPUT_FILE,edit,1350631552
Control8=IDC_DONT_USE_TEMPLATE,button,1342242819
Control9=IDC_TEMPLATE_FILE,edit,1350631552
Control10=IDC_OUTPUT_FILE,edit,1350631552
Control11=IDC_CALC_CRC,edit,1350631552
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDCALC,button,1342242817
Control15=IDCANCEL,button,1342242816
Control16=IDC_STATIC,static,1342308352
Control17=IDC_INPUT_FILE_BROWSE,button,1342242816
Control18=IDC_STATIC,static,1342308352
Control19=IDC_TEMPLATE_FILE_BROWSE,button,1342242816
Control20=IDC_STATIC,static,1342308352
Control21=IDC_OUTPUT_FILE_BROWSE,button,1342242816
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=ID_HELP,button,1342242816
Control25=IDC_STATIC,button,1342177287
Control26=IDC_STATIC,button,1342177287
Control27=IDC_STATIC,button,1342177287
Control28=IDC_COMP_CRC,button,1342242819
Control29=IDC_ALGO,combobox,1344339970
Control30=IDC_STATIC,button,1342177287
Control31=IDC_INPUT_DATA,edit,1350631552
Control32=IDC_STATIC,static,1342308352
Control33=IDC_WRITE_OUT,button,1342242851

[CLS:CHelpDialog]
Type=0
HeaderFile=HelpDialog.h
ImplementationFile=HelpDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CHelpDialog

