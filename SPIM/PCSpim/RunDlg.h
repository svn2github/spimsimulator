// RunDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRunDlg dialog
class CRunDlg : public CDialog
{
// Construction
public:
	CRunDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRunDlg)
	enum { IDD = IDD_RUN };
	CString	m_strAddress;
	BOOL m_checkUndefinedSymbols;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRunDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRunDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckUndefined();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
