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
