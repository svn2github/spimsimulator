// SetValueDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetValueDlg dialog

class CSetValueDlg : public CDialog
{
// Construction
public:
	CSetValueDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetValueDlg)
	enum { IDD = IDD_SETVALUE };
	CString	m_strAddress;
	CString	m_strValue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetValueDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetValueDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
