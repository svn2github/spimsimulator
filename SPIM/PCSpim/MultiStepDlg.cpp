// MultiStepDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PCSpim.h"
#include "MultiStepDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMultiStepDlg dialog


CMultiStepDlg::CMultiStepDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMultiStepDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMultiStepDlg)
	m_cSteps = 0;
	//}}AFX_DATA_INIT
}


void CMultiStepDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMultiStepDlg)
	DDX_Text(pDX, IDC_STEPS, m_cSteps);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMultiStepDlg, CDialog)
	//{{AFX_MSG_MAP(CMultiStepDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultiStepDlg message handlers
