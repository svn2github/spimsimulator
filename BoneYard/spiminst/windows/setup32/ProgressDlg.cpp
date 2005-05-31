#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <stdio.h>
#include <tchar.h>
#include <regstr.h>

#include "resource.h"
#include "globals.h"
#include "ProgressDlg.h"
#include "..\common\defs.h"
#include "util.h"
#include "spimreg.h"
#include "regman.h"


CProgressDialog::CProgressDialog()
{
	GetCurrentDirectory(MAX_PATH, m_szCurDir);
}


CProgressDialog::~CProgressDialog()
{
}


HWND CProgressDialog::Create()
{
	return CDialog::Create(g_hInst, NULL, IDD_PROGRESS);
}


int CProgressDialog::DoModal()
{
	return CDialog::DoModal(g_hInst, NULL, IDD_PROGRESS);
}


BOOL CProgressDialog::DialogProc(HWND, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		HANDLE_DLG_MSG(m_hWnd, WM_INITDIALOG, OnInitDialog);
		HANDLE_DLG_MSG(m_hWnd, WM_COMMAND, OnCommand);
		HANDLE_DLG_MSG(m_hWnd, WM_TIMER, OnTimer);
	}

	return FALSE;
}


BOOL CProgressDialog::OnInitDialog(HWND, HWND hwndFocus, LPARAM lParam)
{
	CenterWindow(m_hWnd);

	int nFiles = InitializeCopying();

	// Set the progress bar range
	m_hwndProgress = GetDlgItem(m_hWnd, IDC_PROGRESS);
	int nSteps = nFiles + 1 // The number of files
				 + 1	// One step for setting up the registry
				 + 1	// One for creating the program group
				 + 1;	// One for saving uninstall info
	SendMessage(m_hwndProgress, PBM_SETRANGE, 0, MAKELPARAM(0, nSteps * 10));

	// Start the install tick
	SetTimer(m_hWnd, 42, 100, NULL);

	return TRUE;
}


void CProgressDialog::OnCommand(HWND, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id == IDCANCEL)
	{
		if (IDYES == MessageBox(m_hWnd, "Are you sure you want to exit setup?",
			SETUP_TITLE " -- Exiting Setup", MB_YESNO | MB_ICONQUESTION))
		{
			EndDialog(m_hWnd, id);
		}
	}
}

void CProgressDialog::OnTimer(HWND, UINT id)
{
	static int nState = 0;
	static BOOL fInTimer = FALSE;

	if (fInTimer)
		return;
	fInTimer = TRUE;

	switch (nState)
	{
	case 0:
		if (!m_fCopyingDone)
		{
			CopyNextFile();		// Copy another file.
			goto l_Leave;
		}
		break;

	case 1:
		SetupRegistry();
		break;

	case 2:
		CreateProgramGroupAndIcons();
		break;

	case 3:
		SaveUninstallInfo();
		KillTimer(m_hWnd, 42);
		EndDialog(m_hWnd, IDOK);
		break;
	}

	++nState;

l_Leave:
	SendMessage(m_hwndProgress, PBM_STEPIT, 0, 0);
	fInTimer = FALSE;
}

long CProgressDialog::InitializeCopying()
{
	m_fCopyingDone = FALSE;
	m_dwOSType = GetOSType();
	m_iCopyFile = 0;

	long cFiles = 0;
	while (g_rgfi[cFiles].szFrom != NULL)
		++cFiles;

	return cFiles;
}

void CProgressDialog::CopyNextFile()
{
	int i = m_iCopyFile;

	if (g_rgfi[i].szFrom == NULL)
	{
		m_fCopyingDone = TRUE;
		return;
	}

	// Check that we should install the file.
	if (((m_dwOSType == VER_PLATFORM_WIN32s) && g_rgfi[i].fWin32s) ||
		((m_dwOSType != VER_PLATFORM_WIN32s) && g_rgfi[i].f95andNT))
	{
		LPCTSTR szPrefix;
// This is a poor way of doing it, but it's a quick fix.
#if 0
		if (g_rgfi[i].fSystemFile)
		{
			static TCHAR szSysDir[MAX_PATH + 1];
			GetSystemDirectory(szSysDir, MAX_PATH);
			szPrefix = szSysDir;
		}
		else
#endif
			szPrefix = g_szDestDir;
		
		TCHAR szTo[MAX_PATH + 1];
		TCHAR szFrom[MAX_PATH + 1];
		_sntprintf(szTo, MAX_PATH, "%s\\%s", szPrefix, g_rgfi[i].szTo);
		_sntprintf(szFrom, MAX_PATH, "%s\\%s", m_szCurDir, g_rgfi[i].szFrom);

		SetStatusText("Copying", szFrom, "to", szTo);

		// We're taking a lazy approach, and _never_ overwriting
		// an already existing destination file.
		CopyFile(szFrom, szTo, TRUE);
	}

	++m_iCopyFile;
}


void CProgressDialog::CreateProgramGroupAndIcons()
{
	LPTSTR szCmd;

	SetStatusText("Creating program group and icons...", "", "", "");

	szCmd = new TCHAR[2048];
	_sntprintf(szCmd, 2048,
		"[CreateGroup(\"PCSpim for Windows\")]"
		"[AddItem(%s\\pcspim.exe, \"PCSpim for Windows\")]"
		"[AddItem(%s, \"PCSpim Help\")]"
		"[AddItem(%s\\setup.exe /uninstall, \"Uninstall PCSpim\", %s\\setup.exe, 1)]",
		g_szDestDir, GetHelpCmd(), g_szDestDir, g_szDestDir, g_szDestDir);
	SendCommandToProgMan(szCmd);
	delete [] szCmd;
}

void CProgressDialog::SetupRegistry()
{
	SetStatusText("Saving default configuration options...", "", "", "");

	if (GetOSType() == VER_PLATFORM_WIN32s)
	{
		LPTSTR szTrapPath = new TCHAR[MAX_PATH + 1];
		_sntprintf(szTrapPath, MAX_PATH, "%s\\trap.han", g_szDestDir);

		WritePrivateProfileString(INI_SETTINGS, SPIM_REG_TRAPFILE, szTrapPath, INI_FILENAME);
		WritePrivateProfileString(INI_SETTINGS, SPIM_REG_QUIET, "0", INI_FILENAME);
		WritePrivateProfileString(INI_SETTINGS, SPIM_REG_MAPPEDIO, "1", INI_FILENAME);
		WritePrivateProfileString(INI_SETTINGS, SPIM_REG_LOADTRAP, "1", INI_FILENAME);
		WritePrivateProfileString(INI_SETTINGS, SPIM_REG_PSEUDO, "1", INI_FILENAME);
		WritePrivateProfileString(INI_SETTINGS, SPIM_REG_BARE, "0", INI_FILENAME);
		WritePrivateProfileString(INI_SETTINGS, SPIM_REG_GENREG_HEX, "1", INI_FILENAME);
		WritePrivateProfileString(INI_SETTINGS, SPIM_REG_FPREG_HEX, "1", INI_FILENAME);
		WritePrivateProfileString(INI_SETTINGS, SPIM_REG_SAVEWINPOS, "1", INI_FILENAME);

		delete [] szTrapPath;
	}
	else
	{
		HKEY hKeyAppPaths, hKey;

		// Build the path to the trap handler
		LPTSTR szTrapPath = new TCHAR[MAX_PATH + 1];
		_sntprintf(szTrapPath, MAX_PATH, "%s\\trap.handler", g_szDestDir);

		// Save default registry settings.
		RegMan_CreateKey(HKEY_LOCAL_MACHINE, SPIM_REG_DEFAULTSETTINGS "\\Settings", &hKey);
		RegMan_SetSZValue(hKey, SPIM_REG_TRAPFILE, szTrapPath);
		RegMan_SetDWORDValue(hKey, SPIM_REG_QUIET, 0);
		RegMan_SetDWORDValue(hKey, SPIM_REG_MAPPEDIO, 1);
		RegMan_SetDWORDValue(hKey, SPIM_REG_LOADTRAP, 1);
		RegMan_SetDWORDValue(hKey, SPIM_REG_PSEUDO, 1);
		RegMan_SetDWORDValue(hKey, SPIM_REG_BARE, 0);
		RegMan_SetDWORDValue(hKey, SPIM_REG_GENREG_HEX, 1);
		RegMan_SetDWORDValue(hKey, SPIM_REG_FPREG_HEX, 1);
		RegMan_SetDWORDValue(hKey, SPIM_REG_SAVEWINPOS, 1);
		RegMan_CloseKey(hKey);

		delete [] szTrapPath;

		// Build the app path
		LPTSTR szAppPath = new TCHAR[MAX_PATH + 1];
		_sntprintf(szAppPath, MAX_PATH, "%s\\pcspim.exe", g_szDestDir);

		// Set app paths
		RegMan_OpenKey(HKEY_LOCAL_MACHINE, REGSTR_PATH_APPPATHS, &hKeyAppPaths);
		RegMan_CreateKey(hKeyAppPaths, "pcspim.exe", &hKey);
		RegMan_SetSZValue(hKey, NULL, szAppPath);
		RegMan_CloseKey(hKey);
		RegMan_CloseKey(hKeyAppPaths);

		delete [] szAppPath;
	}

}

void CProgressDialog::SaveUninstallInfo()
{
	SetStatusText("Saving uninstall information...", "", "", "");

	if (GetOSMajorVer() >= 4)
	{
		LPCTSTR szDisplayName = "PCSpim for Windows (Remove only)";
		LPTSTR szCmdLine = new TCHAR[MAX_PATH + 1];
		_sntprintf(szCmdLine, MAX_PATH, "%s\\setup /uninstall", g_szDestDir);

		HKEY hKeyUninstall, hKey;
		RegOpenKeyEx(HKEY_LOCAL_MACHINE, REGSTR_PATH_UNINSTALL, NULL, KEY_ALL_ACCESS, &hKeyUninstall);
		RegCreateKeyEx(hKeyUninstall, "PCSpim", NULL, NULL, NULL, KEY_ALL_ACCESS, NULL, &hKey, NULL);
		RegSetValueEx(hKey, REGSTR_VAL_UNINSTALLER_DISPLAYNAME, NULL, REG_SZ, (LPBYTE)szDisplayName, lstrlen(szDisplayName) + 1);
		RegSetValueEx(hKey, REGSTR_VAL_UNINSTALLER_COMMANDLINE, NULL, REG_SZ, (LPBYTE)szCmdLine, lstrlen(szCmdLine) + 1);
		RegCloseKey(hKey);
		RegCloseKey(hKeyUninstall);

		delete [] szCmdLine;
	}

}


void CProgressDialog::SetStatusText(LPCTSTR strDesc, LPCTSTR sz1, LPCTSTR sz2, LPCTSTR sz3)
{
	SetWindowText(GetDlgItem(m_hWnd, IDC_DESCRIPTION), strDesc);
	SetWindowText(GetDlgItem(m_hWnd, IDC_FIELD1), sz1);
	SetWindowText(GetDlgItem(m_hWnd, IDC_FIELD2), sz2);
	SetWindowText(GetDlgItem(m_hWnd, IDC_FIELD3), sz3);
}


LPCTSTR CProgressDialog::GetHelpCmd()
{
	static char szCmd[MAX_PATH * 2] = {0};

	if (szCmd[0] == NULL)
	{
		if (GetOSType() == VER_PLATFORM_WIN32s)
			sprintf(szCmd, "winhlp32 %s\\pcspim.hlp", g_szDestDir);
		else
			sprintf(szCmd, "%s\\pcspim.hlp", g_szDestDir);
	}

	return szCmd;
}
