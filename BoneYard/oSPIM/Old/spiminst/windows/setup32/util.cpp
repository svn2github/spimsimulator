#include <windows.h>
#include <stdio.h>
#include <tchar.h>

#include "..\common\defs.h"
#include "util.h"

void CenterWindow(HWND hWnd)
{
	RECT r;
	GetWindowRect(hWnd, &r);
	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);

	SetWindowPos(hWnd, NULL,
		(cx - r.right + r.left) / 2, (cy - r.bottom + r.top) / 2,
		0, 0, SWP_NOSIZE | SWP_NOZORDER);
}


static OSVERSIONINFO * posvi = NULL;

DWORD GetOSType()
{
	if (posvi == NULL)
	{
		posvi = new OSVERSIONINFO;
		posvi->dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		GetVersionEx(posvi);
	}

    return posvi->dwPlatformId;
}


DWORD GetOSMajorVer()
{
	if (posvi == NULL)
	{
		posvi = new OSVERSIONINFO;
		posvi->dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		GetVersionEx(posvi);
	}

	return posvi->dwMajorVersion;
}


BOOL DoesFileExist(LPCTSTR szFile)
{
	SetLastError(0);
	DWORD dwAttr = GetFileAttributes(szFile);

	int nErr = GetLastError();
	if ((dwAttr == 0xFFFFFFFF) && 
		((nErr == ERROR_FILE_NOT_FOUND) || (nErr == ERROR_PATH_NOT_FOUND)))
		return FALSE;
	else
		return TRUE;
	
	return TRUE;
}


BOOL IsFileDir(LPCTSTR szFile)
{
	SetLastError(0);
	DWORD dwAttr = GetFileAttributes(szFile);

	if ((dwAttr & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY)
		return TRUE;
	else
		return FALSE;
}


BOOL VerifyOrCreateDirectory(LPCTSTR szDir)
{
	// Verify the directory exists.  If it doesn't,
	// ask if they would like to create it.
	if (!DoesFileExist(szDir))
	{
		static char szMsg[MAX_PATH * 2];
		_sntprintf(szMsg, MAX_PATH * 2, "\"%s\" does not exist.\n"
			"Would you like to create it?", szDir);
		int nRet = MessageBox(NULL, szMsg, SETUP_TITLE " -- Create Directory?",
			MB_YESNO | MB_ICONQUESTION);

		if (nRet == IDNO)	// We must have a valid directory.
			return FALSE;
		else
		{
			// Attempt to create the directory.
			if (FALSE == CreateDirTree(szDir))
			{
				MessageBox(NULL, "Could not create directory.", SETUP_TITLE " -- Error",
					MB_OK | MB_ICONEXCLAMATION);
				return FALSE;
			}
		}
	}
	else if (!IsFileDir(szDir))
	{
		MessageBox(NULL, "That is the name of an existing file.  "
			"Please choose another name.", SETUP_TITLE " -- Error", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	return TRUE;
}


BOOL CreateDirTree(LPCTSTR szDir)
{
	LPCTSTR szDelim = "\\/";
	LPTSTR szTemp = new TCHAR[lstrlen(szDir) + 1];
	LPTSTR szFullPath = new TCHAR[lstrlen(szDir) + 1];
	lstrcpy(szTemp, szDir);

	LPCTSTR szPart = strtok(szTemp, szDelim);
	lstrcpy(szFullPath, szPart);
	while (TRUE)
	{
		if (DoesFileExist(szFullPath))
		{
			if (!IsFileDir(szFullPath))
				break;
		}
		else
		{
			if (FALSE == CreateDirectory(szFullPath, NULL))
				break;
		}

		szPart = strtok(NULL, szDelim);
		if (szPart == NULL)
			break;

		lstrcat(szFullPath, "\\");
		lstrcat(szFullPath, szPart);
	}

	delete [] szTemp;
	delete [] szFullPath;

	return (szPart == NULL);	// We made it through all the dirs
}


BOOL SendCommandToProgMan(LPCTSTR szCmd)
{
	#define MAKEHSZ(id, sz) DdeCreateStringHandle(id, sz, CP_WINANSI)
	#define FREEHSZ(id, hsz) DdeFreeStringHandle(id, hsz)

	DWORD dwID = 0;

	// Initialize the DDEML layer
	DdeInitialize(&dwID, NULL, APPCLASS_STANDARD | APPCMD_CLIENTONLY, 0);

	// Connect to "Program Manager" or its standin
	HSZ hszService = MAKEHSZ(dwID, "PROGMAN");
	HSZ hszTopic = MAKEHSZ(dwID, "PROGMAN");
	HCONV hconv = DdeConnect(dwID, hszService, hszTopic, NULL);
	FREEHSZ(dwID, hszService);
	FREEHSZ(dwID, hszTopic);

	if (hconv == NULL)
		MessageBox(NULL, "Couldn't connect to Program Manager via DDE!",
			SETUP_TITLE " -- Error", MB_OK);
	else
	{
		// UNDONE:  If this fails, we should report something.
		DdeClientTransaction((PBYTE)szCmd, lstrlen(szCmd) + 1, hconv, NULL, 0, XTYP_EXECUTE, 10000, NULL);
		DdeDisconnect(hconv);
	}

	DdeUninitialize(dwID);

	return TRUE;
}

