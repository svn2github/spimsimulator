#include <windows.h>
#include "Dialog.h"

CDialog::CDialog()
{
	m_hWnd = NULL;
	m_fInitialRectSet = FALSE;
}


CDialog::~CDialog()
{
	if (IsWindow(m_hWnd))
		DestroyWindow(m_hWnd);
}


HWND CDialog::Create(HINSTANCE hInst, HWND hwndParent, UINT idDlg)
{
	HWND hwnd = CreateDialogParam(hInst,
								  MAKEINTRESOURCE(idDlg),
								  hwndParent,
								  (DLGPROC)class_initial_DialogProc,
								  (LPARAM)this);
	return hwnd;
}


int CDialog::DoModal(HINSTANCE hInst, HWND hwndParent, UINT idDlg)
{
	return DialogBoxParam(hInst,
						  MAKEINTRESOURCE(idDlg),
						  hwndParent,
						  (DLGPROC)class_initial_DialogProc,
						  (LPARAM)this);
}


BOOL CALLBACK CDialog::class_initial_DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_INITDIALOG)
		SetWindowLong(hwndDlg, GWL_USERDATA, lParam);

	CDialog *pDlg = (CDialog*)GetWindowLong(hwndDlg, GWL_USERDATA);

	if (pDlg)
		return pDlg->class_DialogProc(hwndDlg, uMsg, wParam, lParam);
	else
		return FALSE;
}


BOOL CDialog::class_DialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_INITDIALOG)
	{
		m_hWnd = hWnd;
		if (m_fInitialRectSet)
			SetWindowPos(hWnd, NULL, m_rInitial.left, m_rInitial.top, 0, 0, SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOSIZE | SWP_NOZORDER);
	}

	return DialogProc(hWnd, uMsg, wParam, lParam);
}


BOOL CDialog::DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if ((uMsg == WM_COMMAND) &&
		((wParam == IDOK) || (wParam == IDCANCEL)))
	{
		return EndDialog(hwnd, wParam);
	}
	else
		return FALSE;
}


void CDialog::SetInitialPos(RECT &r)
{
	m_fInitialRectSet = TRUE;
	m_rInitial = r;
}
