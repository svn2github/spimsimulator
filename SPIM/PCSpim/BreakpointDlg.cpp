// BreakpointDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PCSpim.h"
#include "BreakpointDlg.h"
#include "PCSpimView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBreakpointDlg dialog


CBreakpointDlg::CBreakpointDlg(CWnd* pParent /*=NULL*/)
  : CDialog(CBreakpointDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBreakpointDlg)
	//}}AFX_DATA_INIT
}


void CBreakpointDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBreakpointDlg)
	DDX_Control(pDX, IDC_BREAKPOINTS, m_lbBreakpoints);
	DDX_Control(pDX, IDC_ADDRESS, m_edAddress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBreakpointDlg, CDialog)
	//{{AFX_MSG_MAP(CBreakpointDlg)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	ON_BN_CLICKED(IDCLOSE, OnClose)
	ON_LBN_SELCHANGE(IDC_BREAKPOINTS, OnSelchangeBreakpoints)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBreakpointDlg message handlers

void CBreakpointDlg::OnAdd()
{
  CString strAddress;
  m_edAddress.GetWindowText(strAddress);

  if (strAddress.IsEmpty())
    {
      MessageBox("Please enter an address or symbol.");
      m_edAddress.SetFocus();
      return;
    }

  int nAddr;
  if (isdigit(strAddress[0]))
    {
      nAddr = strtoul(strAddress, NULL, 0);
    }
  else
    {
      char *szAddress = strAddress.GetBuffer(0);
      nAddr = find_symbol_address(szAddress);
      strAddress.ReleaseBuffer();
    }

  strAddress.Format("0x%08x", nAddr);
  if (m_lbBreakpoints.FindString(-1, strAddress) != LB_ERR)
    {
      MessageBox("There is already a breakpoint at that location!");
      return;
    }

  // Turn on message capture, and attempt to add the breakpoint.
  g_pView->SetMessageCapture(TRUE);
  add_breakpoint(nAddr);
  CString strResult = g_pView->GetMessageCaptureBuf();
  g_pView->SetMessageCapture(FALSE);

  if (strResult.IsEmpty())	// No Error
    {
      strAddress.Format("0x%08x", nAddr);
      m_lbBreakpoints.AddString(strAddress);

      m_edAddress.SetWindowText("");
    }
  else
    {
      MessageBox(strResult);
    }

  g_pView->UpdateStatusDisplay();
}


void CBreakpointDlg::OnRemove()
{
  int nCurSel = m_lbBreakpoints.GetCurSel();

  // Make sure an item is selected.
  if (nCurSel == LB_ERR)
    {
      MessageBox("Please select a breakpoint to delete.");
      return;
    }

  // Remove this item from the listbox.
  CString strAddress;
  m_lbBreakpoints.GetText(nCurSel, strAddress);
  m_lbBreakpoints.DeleteString(nCurSel);

  int nAddr;
  sscanf(strAddress, "%x", &nAddr);

  // Capture messages -- we set the breakpoint, it _should_ work... 8)
  g_pView->SetMessageCapture(TRUE);
  delete_breakpoint(nAddr);
  CString strResult = g_pView->GetMessageCaptureBuf();
  g_pView->SetMessageCapture(FALSE);

  // We shouldn't have any error messages.
  ASSERT(strResult.IsEmpty());

  // Disable the Remove button.
  GetDlgItem(IDC_REMOVE)->EnableWindow(FALSE);

  g_pView->UpdateStatusDisplay();
}


void CBreakpointDlg::OnClose()
{
  ShowWindow(SW_HIDE);
}


BOOL CBreakpointDlg::Create(CWnd *pParentWnd)
{
  return CDialog::Create(IDD, pParentWnd);
}


BOOL CBreakpointDlg::OnInitDialog()
{
  CDialog::OnInitDialog();

  LoadBreakpoints();

  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}


void CBreakpointDlg::OnSelchangeBreakpoints()
{
  GetDlgItem(IDC_REMOVE)->EnableWindow();
}


void CBreakpointDlg::LoadBreakpoints()
{
  m_lbBreakpoints.ResetContent();

  // Turn on message capture, have the simulator print
  // the list of breakpoints, turn off message capture
  g_pView->SetMessageCapture(TRUE);
  list_breakpoints();
  CString strBkpts = g_pView->GetMessageCaptureBuf();
  g_pView->SetMessageCapture(FALSE);

  // Now, process the dumped breakpoing list.
  char *szBkptTag = "Breakpoint at ";
  int nPos;
  while (1)
    {
      if (-1 == (nPos = strBkpts.Find(szBkptTag)))
	break;

      // Snip off the front.
      strBkpts = strBkpts.Mid(nPos + lstrlen(szBkptTag));

      // Extract the address
      m_lbBreakpoints.AddString(strBkpts.Left(10));
    }

  // Disable the Remove button
  GetDlgItem(IDC_REMOVE)->EnableWindow(FALSE);
}


void CBreakpointDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
  CDialog::OnShowWindow(bShow, nStatus);

  if (bShow)
    {
      LoadBreakpoints();
    }
}
