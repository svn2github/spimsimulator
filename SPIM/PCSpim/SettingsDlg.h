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

// SettingsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSettingsDlg dialog

class CSettingsDlg : public CDialog
{
// Construction
public:
	CSettingsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSettingsDlg)
	enum { IDD = IDD_SETTINGS };
	BOOL	m_fBare;
	BOOL	m_fDelayedBranches;
	BOOL	m_fDelayedLoads;
	BOOL	m_fLoadTrap;
	BOOL	m_fMappedIO;
	BOOL	m_fAllowPseudo;
	BOOL	m_fQuiet;
	CString	m_strTrapFile;
	BOOL	m_fFPRegHex;
	BOOL	m_fGenRegHex;
	BOOL	m_fSaveWinPos;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSettingsDlg)
	afx_msg void OnBrowse();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnLoadtrap();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL CheckValid();
};
