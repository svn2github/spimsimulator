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

/* $Version: $ */

#ifndef BREAKPOINTDLG_H
#define BREAKPOINTDLG_H

// BreakpointDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBreakpointDlg dialog

class CBreakpointDlg : public CDialog
{
// Construction
public:
	BOOL Create(CWnd *pParentWnd);
	CBreakpointDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBreakpointDlg)
	enum { IDD = IDD_BREAKPOINTS };
	CListBox	m_lbBreakpoints;
	CEdit	m_edAddress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBreakpointDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBreakpointDlg)
	afx_msg void OnAdd();
	afx_msg void OnRemove();
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeBreakpoints();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void LoadBreakpoints();
};


#endif //  BREAKPOINTDLG_H
