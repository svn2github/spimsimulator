// SPIM S20 MIPS simulator.
// Definitions for the SPIM S20.
//
// Copyright (C) 1990-2000 by James Larus (larus@cs.wisc.edu).
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

/* $Version: $ */

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
