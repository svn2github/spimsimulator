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

// PCSpimView.h : interface of the CPCSpimView class
//
/////////////////////////////////////////////////////////////////////////////

#include "BreakpointDlg.h"
#include "ConsoleWnd.h"

class CPCSpimDoc;

class CPCSpimView : public CView
{
protected: // create from serialization only
	CPCSpimView();
	DECLARE_DYNCREATE(CPCSpimView)

// Attributes
public:
	BOOL m_fConsoleMinimized;
	void BringConsoleToTop();
	void MakeConsoleVisible();
	CConsoleWnd * GetConsole();
	void UpdateStatusDisplay();
	BOOL AskContinue(BOOL fBreak);
	void HighlightCurrentInstruction();
	LPCTSTR GetMessageCaptureBuf();
	void SetMessageCapture(BOOL fOn);
	void WriteToMessage(LPCTSTR strText);
	void WriteToConsole(LPCTSTR strText);
	CPCSpimDoc* GetDocument();
	void CPCSpimView::TileWindows(long cx, long cy, long bottom);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPCSpimView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	protected:
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPCSpimView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	void DisplayRegisters();

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPCSpimView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSimulatorReinitialize();
	afx_msg void OnSimulatorClearRegisters();
	afx_msg void OnFileOpen();
	afx_msg void OnSimulatorRun();
	afx_msg void OnSimulatorBreakpoints();
	afx_msg void OnSimulatorSetvalue();
	afx_msg void OnSimulatorBreak();
	afx_msg void OnSimulatorSettings();
	afx_msg void OnUpdateSimulatorReload(CCmdUI* pCmdUI);
	afx_msg void OnSimulatorReload();
	afx_msg void OnUpdateSimulatorBreak(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSimulatorRun(CCmdUI* pCmdUI);
	afx_msg void OnSimulatorStep();
	afx_msg void OnUpdateSimulatorStep(CCmdUI* pCmdUI);
	afx_msg void OnSimulatorMultistep();
	afx_msg void OnUpdateSimulatorMultistep(CCmdUI* pCmdUI);
	afx_msg void OnSimulatorDisplaysymbols();
	afx_msg void OnWindowCascade();
	afx_msg void OnWindowNext();
	afx_msg void OnWindowPrevious();
	afx_msg void OnWindowTile();
	afx_msg void OnWindowClearConsole();
	afx_msg void OnUpdateSimulatorSetvalue(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSimulatorBreakpoints(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSimulatorDisplaysymbols(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSimulatorClearRegisters(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSimulatorReinitialize(CCmdUI* pCmdUI);
	afx_msg void OnWindowMessages();
	afx_msg void OnWindowRegisters();
	afx_msg void OnWindowTextseg();
	afx_msg void OnWindowDataseg();
	afx_msg void OnWindowConsole();
	afx_msg void OnDestroy();
	afx_msg void OnWindowArrangeicons();
	afx_msg void OnFileSaveLog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void OutputLog(CString &strBuf);
	void ProcessCommandLine();
	BOOL m_fSimulatorInitialized;
	long m_nSavedStatusReg;
	long m_nForceStop;
	CString m_strCurFilename;
	CString m_strMsgCaptureBuf;
	BOOL m_fCapture;
	CBreakpointDlg m_dlgBP;
	BOOL m_fStackInitialized;

	CConsoleWnd	m_wndConsole;
	CEdit		m_wndMessages;
	CEdit		m_wndDataSeg;
	CEdit		m_wndTextSeg;
	CEdit		m_wndRegisters;

	void ShowRunning();
	void InitStack(LPCTSTR args);
	void LoadFile(LPCTSTR strFilename);
	void DisplayTextSegment();
	char * DumpMemValues(mem_addr from, mem_addr to, char* buf, int *limit, int *n);
	void DisplayDataSegment();
	void ExecuteProgram(mem_addr pc, int steps, int display, int cont_bkpt);
	void InitializeSimulator();
	void Initialize();
};

#ifndef _DEBUG  // debug version in PCSpimView.cpp
inline CPCSpimDoc* CPCSpimView::GetDocument()
   { return (CPCSpimDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
