#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <tchar.h>
#include <commctrl.h>
#include <regstr.h>

#include "resource.h"
#include "globals.h"
#include "..\common\defs.h"
#include "util.h"
#include "SpimReg.h"
#include "regman.h"

#include "DirectoryDlg.h"
#include "ProgressDlg.h"

void CleanupOnCancel();
void SignalExiting();
int Uninstall(BOOL fCancelling = FALSE);
int Install();

int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,
				   int nCmdShow)
{
	g_hInst = hInstance;

	atexit(SignalExiting);

	InitCommonControls();

	// Convert the cmdline to lower case for comparison.
	CharLower(lpCmdLine);
	if (strstr(lpCmdLine, "/uninstall"))
		return Uninstall();
	else if (strstr(lpCmdLine, "/install"))
		return Install();
	else
	{
		MessageBox(NULL,
			"You must specify either /install or /uninstall on the command line.",
			SETUP_TITLE " -- Error",
			MB_OK | MB_ICONSTOP);
		return 0;
	}
}


int Install()
{
	g_lExitCode = SETUP_INSTALL_FAILED;

	CDirectoryDialog dlgDir;
	if (dlgDir.DoModal() != IDOK)
	{
		CleanupOnCancel();
		return 0;
	}

	// Do the setup.  Display progress dialog.
	CProgressDialog dlgProgress;
	if (dlgProgress.DoModal() != IDOK)
	{
		CleanupOnCancel();
		return 0;
	}

	if (!g_fViewedReadme)
	{
		MessageBox(NULL, "PCSpim for Windows is now installed.",
			SETUP_TITLE, MB_OK | MB_ICONINFORMATION);
	}

	g_lExitCode = SETUP_INSTALL_SUCCESSFUL;
	return 0;
}


int Uninstall(BOOL fCancelling)
{
	static TCHAR szFilename[MAX_PATH + 1];
	static TCHAR szInstDir[MAX_PATH + 1];

	if (!fCancelling)
	{
		g_lExitCode = SETUP_UNINSTALL_FAILED;	// Predict failure

		if (IDNO == MessageBox(NULL, "Are you sure you want to uninstall PCSpim for Windows?",
			SETUP_TITLE " -- Uninstall", MB_YESNO | MB_ICONQUESTION))
		{
			return 0;
		}
	}

	GetModuleFileName(NULL, szInstDir, MAX_PATH);
	GetShortPathName(szInstDir, szInstDir, MAX_PATH);
	
	*strrchr(szInstDir, '\\') = NULL;

	// Remove files
	int i = 0;
	while (g_rgfi[i].szFrom != NULL)
	{
		// Note:  This could attempt to delete a file multiple times.  That's OK though.
		if (!g_rgfi[i].fSystemFile)
		{
			_sntprintf(szFilename, MAX_PATH, "%s\\%s",
				szInstDir, g_rgfi[i].szTo);
			DeleteFile(szFilename);
		}

		++i;
	}

	// Remove program group
	SendCommandToProgMan("[DeleteGroup(\"PCSpim for Windows\")]");

	// Remove settings info
	if (GetOSType() == VER_PLATFORM_WIN32s)	// INI file on Win3x
	{
		static char szIniFile[MAX_PATH + 1];
		if (0 != SearchPath(NULL, INI_FILENAME, NULL, MAX_PATH, szIniFile, NULL))
		{
			DeleteFile(szIniFile);
		}
	}
	else	// Registry on 95 & NT
	{
		// Delete the default settings
		RegMan_DeleteTree(HKEY_LOCAL_MACHINE, SPIM_REG_SPIMROOT);

		// Delete the settings for all users.
		DWORD cbUserKey = 2047;
		LPTSTR szUserKey = new TCHAR[cbUserKey + 1];
		int i = 0;
		while (S_OK == RegMan_EnumKey(HKEY_USERS, i, szUserKey, &cbUserKey))
		{
			HKEY hKey;
			if (S_OK == RegMan_OpenKey(HKEY_USERS, szUserKey, &hKey))
			{
				RegMan_DeleteTree(hKey, SPIM_REG_SPIMROOT);
				RegMan_CloseKey(hKey);
			}
			++i;
			cbUserKey = 2047;
		}
		delete [] szUserKey;
		
		// Remove app path entry
		RegMan_DeleteKey(HKEY_LOCAL_MACHINE, REGSTR_PATH_APPPATHS "\\pcspim.exe");

		// Remove uninstall info.
		RegMan_DeleteKey(HKEY_LOCAL_MACHINE, REGSTR_PATH_UNINSTALL "\\PCSpim");
	}

	if (!fCancelling)
	{
		MessageBox(NULL, "Uninstallation successful.", SETUP_TITLE, MB_OK);
		g_lExitCode = SETUP_UNINSTALL_SUCCESSFUL;
	}

	return 0;
}


void SignalExiting()
{
	HWND hwnd = FindWindow(SETUP_WND_CLASS, SETUP_WND_CAPTION);
	if (hwnd != NULL)
		PostMessage(hwnd, GET_FINISH_MSG(), 0, g_lExitCode);
}

void CleanupOnCancel()
{
	MessageBox(NULL, "All temporary files will now be removed.",
		SETUP_TITLE " -- Exiting", MB_OK | MB_ICONINFORMATION);

	// Uninstall, silently.
	Uninstall(TRUE);
}

