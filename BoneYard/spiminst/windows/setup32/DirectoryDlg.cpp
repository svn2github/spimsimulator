#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <regstr.h>

#include "resource.h"
#include "globals.h"
#include "DirectoryDlg.h"
#include "ChooseDirDlg.h"
#include "util.h"
#include "regman.h"


HWND CDirectoryDialog::Create()
{
	return CDialog::Create(g_hInst, NULL, IDD_DIRECTORY);
}


int CDirectoryDialog::DoModal()
{
	return CDialog::DoModal(g_hInst, NULL, IDD_DIRECTORY);
}


BOOL CDirectoryDialog::DialogProc(HWND, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		HANDLE_DLG_MSG(m_hWnd, WM_INITDIALOG, OnInitDialog);
		HANDLE_DLG_MSG(m_hWnd, WM_COMMAND, OnCommand);
	}

	return FALSE;
}


BOOL CDirectoryDialog::OnInitDialog(HWND, HWND hwndFocus, LPARAM lParam)
{
	DWORD dwcb = 2047;
	g_szDestDir = new char[dwcb + 1];
	g_szDestDir[0] = NULL;

	if (GetOSMajorVer() >= 4)
	{
		HKEY hKey;
		RegMan_OpenKey(HKEY_LOCAL_MACHINE, REGSTR_PATH_SETUP, &hKey);
		RegMan_GetSZValue(hKey, "ProgramFilesDir", g_szDestDir, &dwcb);
		RegMan_CloseKey(hKey);
	}
	
	if (lstrlen(g_szDestDir) == 0)
		lstrcpy(g_szDestDir, "C:");

	lstrcat(g_szDestDir, "\\PCSpim");

	SetWindowText(GetDlgItem(m_hWnd, IDC_DIRECTORY), g_szDestDir);
	CenterWindow(m_hWnd);

	return TRUE;
}


void CDirectoryDialog::OnCommand(HWND, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	case IDC_BROWSE:
		{
			CChooseDirDlg dlgChoose;

			// Disable ourselves, and display the dlg.
			EnableWindow(m_hWnd, FALSE);
			int nRet = dlgChoose.DoModal();
			EnableWindow(m_hWnd, TRUE);
			SetForegroundWindow(m_hWnd);

			if (nRet == IDOK)
				SetWindowText(GetDlgItem(m_hWnd, IDC_DIRECTORY), dlgChoose.m_szDir);
		}
		break;

	case IDOK:
		{
			HWND hwndCtl = GetDlgItem(m_hWnd, IDC_DIRECTORY);
			long cbText = GetWindowTextLength(hwndCtl) + 1;
			g_szDestDir = new char[cbText + 1];
			GetWindowText(hwndCtl, g_szDestDir, cbText);

			if (VerifyOrCreateDirectory(g_szDestDir))
			{
				TCHAR szBuf[MAX_PATH + 1];
				GetFullPathName(g_szDestDir, MAX_PATH, szBuf, NULL);
				GetShortPathName(szBuf, szBuf, MAX_PATH);
				lstrcpy(g_szDestDir, szBuf);

				EndDialog(m_hWnd, id);
			}
		}
		break;

	case IDCANCEL:
		EndDialog(m_hWnd, id);
		break;
	}
}
