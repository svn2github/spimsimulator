// PCSpim.h : main header file for the PCSPIM application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPCSpimApp:
// See PCSpim.cpp for the implementation of this class
//

class CPCSpimApp : public CWinApp
{
public:
	void WriteSetting(LPCTSTR strName, LPRECT pr);
	BOOL GetSetting(LPCTSTR strName, LPRECT pr);
	void WriteSetting(LPCTSTR strName, LPCTSTR strValue);
	void WriteSetting(LPCTSTR strName, int nValue);
	LPCTSTR GetSetting(LPCTSTR strName, LPCTSTR strDefVal);
	int GetSetting(LPCTSTR strName, int nDefVal);
	void RunMessageLoop();
	CPCSpimApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPCSpimApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPCSpimApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
