// SPIM S20 MIPS simulator.
// Definitions for the SPIM S20.
//
// Copyright (C) 1990-2004 by James Larus (larus@cs.wisc.edu).
// ALL RIGHTS RESERVED.
// Changes for DOS and Windows versions by David A. Carley (dac@cs.wisc.edu)
//
// SPIM is distributed under the following conditions:
//
//   You may make copies of SPIM for your own use and modify those copies.
//
//   All copies of SPIM must retain my name and copyright notice.
//
//   You may not sell SPIM or distributed SPIM in conjunction with a
//   commerical product or service without the expressed written consent of
//   James Larus.
//
// THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE.

/* $Header: /Software/SPIM/SPIM/PCSpim/PCSpim.cpp 1     1/02/05 8:03p Larus $ */

// PCSpim.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "PCSpim.h"

#include "MainFrm.h"
#include "PCSpimDoc.h"
#include "PCSpimView.h"
#include "util.h"
#include "SpimReg.h"

#include "regman.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPCSpimApp

BEGIN_MESSAGE_MAP(CPCSpimApp, CWinApp)
	//{{AFX_MSG_MAP(CPCSpimApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPCSpimApp construction

CPCSpimApp::CPCSpimApp()
{
  // TODO: add construction code here,
  // Place all significant initialization in InitInstance
}


/////////////////////////////////////////////////////////////////////////////
// The one and only CPCSpimApp object

CPCSpimApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CPCSpimApp initialization

BOOL CPCSpimApp::InitInstance()
{
	// SPIM is bad about cleaning up after itself...
	AfxEnableMemoryTracking(FALSE);

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();		// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Turn on registry (vs. INI) support, and set the "company" tag.
	SetRegistryKey("LarusStone");

	if (VER_PLATFORM_WIN32s != UTIL_GetOSType())
	{
		// If registry settings for this user do not exist, copy them from
		// the "Default Settings" tree in HKLM.
		HKEY hKeySrc, hKeySettings;
		HKEY hKeyDest = GetAppRegistryKey();
		if (S_OK != RegMan_OpenKey(hKeyDest, "Settings", &hKeySettings))
		{
			if (S_OK == RegMan_OpenKey(HKEY_LOCAL_MACHINE,
				SPIM_REG_DEFAULTSETTINGS,
				&hKeySrc))
			{
				RegMan_CopyTree(hKeySrc, hKeyDest);
				RegMan_CloseKey(hKeySrc);
			}
		}
		else
		{
			RegMan_CloseKey(hKeySettings);
		}
		RegMan_CloseKey(hKeyDest);
	}

	LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	// serve as the connection between documents, frame windows and views.
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CPCSpimDoc),
		// main SDI frame window
		RUNTIME_CLASS(CMainFrame),
		RUNTIME_CLASS(CPCSpimView));
	AddDocTemplate(pDocTemplate);


	// We do our own cmdline processing later.  Even though we aren't using
	// MFC's standard cmdline processing (we aren't calling ParseCommandLine),
	// we _must_ call ProcessShellCommand...
	CCommandLineInfo cmdInfo;
	if (!ProcessShellCommand(cmdInfo))
	{
		return FALSE;
	}
	return TRUE;
}


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
	virtual BOOL OnInitDialog();
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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// App command to run the dialog
void CPCSpimApp::OnAppAbout()
{
  CAboutDlg aboutDlg;
  aboutDlg.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CPCSpimApp commands

void CPCSpimApp::RunMessageLoop()
{
  MSG msg;
  while (::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
    {
      if (!PumpMessage())
        {
	  force_break = 1;
	  ::PostQuitMessage(0);
	  break;
        }
    }

  // let MFC do its idle processing
  LONG lIdle = 0;
  while (OnIdle(lIdle++));
}


int CPCSpimApp::GetSetting(LPCTSTR strName, int nDefVal)
{
  return GetProfileInt("Settings", strName, nDefVal);
}


LPCTSTR CPCSpimApp::GetSetting(LPCTSTR strName, LPCTSTR strDefVal)
{
  static CString strRet;

  strRet = GetProfileString("Settings", strName, strDefVal);

  return strRet;
}


void CPCSpimApp::WriteSetting(LPCTSTR strName, int nValue)
{
  WriteProfileInt("Settings", strName, nValue);
}


void CPCSpimApp::WriteSetting(LPCTSTR strName, LPCTSTR strValue)
{
  WriteProfileString("Settings", strName, strValue);
}


BOOL CAboutDlg::OnInitDialog()
{
  CDialog::OnInitDialog();

  g_pView->SetMessageCapture(TRUE);
  write_startup_message();
  GetDlgItem(IDC_COPYRIGHT)->SetWindowText(g_pView->GetMessageCaptureBuf());
  g_pView->SetMessageCapture(FALSE);

  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}


#define UTIL_RECTPRINTFFORMAT	"%d, %d, %d, %d"


BOOL CPCSpimApp::GetSetting(LPCTSTR strName, LPRECT pr)
{
  CString strRect = GetProfileString("Settings", strName);

  return (4 == _stscanf(strRect,
			UTIL_RECTPRINTFFORMAT,
			&pr->left, &pr->top, &pr->right, &pr->bottom));
}


void CPCSpimApp::WriteSetting(LPCTSTR strName, LPRECT pr)
{
  CString strRect;
  strRect.Format(UTIL_RECTPRINTFFORMAT, pr->left, pr->top, pr->right, pr->bottom);
  WriteProfileString("Settings", strName, strRect);
}

