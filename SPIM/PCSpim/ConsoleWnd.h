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

#ifndef _CONSOLEWND_H
#define _CONSOLEWND_H

// ConsoleWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConsoleWnd window

typedef CList<BYTE, BYTE>	CByteList;

class CConsoleWnd : public CWnd
{
// Construction
public:
	BOOL m_fActAsConsole;
	CRichEditCtrl & GetRichEdit();
	void Clear();
	char GetKeyPress();
	BOOL AreKeysAvailable();
	void WriteText(LPCTSTR strText);
	CConsoleWnd();

// Attributes
public:
	CByteList m_blKeys;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConsoleWnd)
	public:
	virtual BOOL Create(CWnd* pParentWnd, LPCTSTR szCaption,
		LPRECT pr = NULL, DWORD dwREStyle = 0, DWORD dwExStyle = 0,
		DWORD dwStyleChildOrPopup = WS_CHILD);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CConsoleWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CConsoleWnd)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	DWORD m_dwREStyle;
	CRichEditCtrl m_reText;
};

/////////////////////////////////////////////////////////////////////////////

#endif // _CONSOLEWND_H
