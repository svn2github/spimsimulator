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
