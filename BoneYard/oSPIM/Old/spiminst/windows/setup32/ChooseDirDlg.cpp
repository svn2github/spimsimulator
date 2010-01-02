#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <stdio.h>
#include <tchar.h>

#include "resource.h"
#include "globals.h"
#include "BusyCursor.h"
#include "ChooseDirDlg.h"
#include "util.h"

HWND CChooseDirDlg::Create()
{
	return CDialog::Create(g_hInst, NULL, IDD_CHOOSEDIR);
}


int CChooseDirDlg::DoModal()
{
	return CDialog::DoModal(g_hInst, NULL, IDD_CHOOSEDIR);
}


BOOL CChooseDirDlg::DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		HANDLE_DLG_MSG(m_hWnd, WM_INITDIALOG, OnInitDialog);
		HANDLE_DLG_MSG(m_hWnd, WM_COMMAND, OnCommand);
		HANDLE_DLG_MSG(m_hWnd, WM_NOTIFY, OnNotify);
		HANDLE_DLG_MSG(m_hWnd, WM_DESTROY, OnDestroy);
	}

	return FALSE;
}


BOOL CChooseDirDlg::OnInitDialog(HWND, HWND hwndFocus, LPARAM lParam)
{
	m_szDir = NULL;
	m_hwndTreeCtrl = GetDlgItem(m_hWnd, IDC_TREE);
	CenterWindow(m_hWnd);
	AddDrives();

	return TRUE;
}


LONG CChooseDirDlg::OnNotify(HWND hwnd, int idCtrl, LPNMHDR pnmh)
{
	switch (pnmh->idFrom)
	{
	case IDC_TREE:
		{
			if (pnmh->code == TVN_SELCHANGED)
			{
				OnTreeClick((NM_TREEVIEW*)pnmh);
			}
			else if (pnmh->code == TVN_ITEMEXPANDING)
			{
				OnItemExpanding((NM_TREEVIEW*)pnmh);
			}
		}
		break;
	}

	return 0;
}


void CChooseDirDlg::OnCommand(HWND, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	case IDOK: OnOK();
		break;

	case IDCANCEL:
		EndDialog(m_hWnd, id);
		break;
	}
}


BOOL CChooseDirDlg::HasDirectories(LPCTSTR szPath)
{
	WIN32_FIND_DATA fd;
	TCHAR szSpec[MAX_PATH];
	HANDLE hFind;

	_snprintf(szSpec, MAX_PATH, "%s\\*.*", szPath);

	hFind = FindFirstFile(szSpec, &fd);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
				(!IsDotOrDotDot(fd.cFileName)))
			{
				FindClose(hFind);
				return TRUE;
			}
		}
		while (FindNextFile(hFind, &fd));
		FindClose(hFind);
	}

	return FALSE;
}


BOOL CChooseDirDlg::IsDotOrDotDot(LPCTSTR szPath)
{
	return ((szPath[0] == '.') && ((szPath[1] == NULL) ||
								   ((szPath[1] == '.') && (szPath[2] == NULL))));
}


DWORD CChooseDirDlg::AddDirectories(HTREEITEM hParent, LPCTSTR szPath)
{
	WIN32_FIND_DATA fd;
	TCHAR szSpec[MAX_PATH];
	HANDLE hFind;
	HTREEITEM hItem;
	DWORD cDirs;
	TCHAR szFullPath[MAX_PATH];

	_snprintf(szSpec, MAX_PATH, "%s\\*.*", szPath);

	cDirs = 0;
	hFind = FindFirstFile(szSpec, &fd);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
				(!IsDotOrDotDot(fd.cFileName)))
			{
				_snprintf(szFullPath, MAX_PATH, "%s\\%s", szPath, fd.cFileName);
				hItem = AddDirectoryItem(hParent, fd.cFileName, lstrlen(fd.cFileName), HasDirectories(szFullPath));

				cDirs++;
			}
		}
		while (FindNextFile(hFind, &fd));
		FindClose(hFind);
	}

	return cDirs;
}


LPCTSTR CChooseDirDlg::GetItemText(HTREEITEM hItem)
{
	static TCHAR szBuf[2048];

    TV_ITEM item;
    item.hItem = hItem;
    item.mask = TVIF_TEXT;
    item.pszText = szBuf;
    item.cchTextMax = 2048;
	TreeView_GetItem(m_hwndTreeCtrl, &item);

    return szBuf;
}


void CChooseDirDlg::AddDrives()
{
	DWORD dwDriveMask;
	TCHAR szDrive[MAX_PATH];
	UINT iDriveType;
	DWORD cbBuf;
	HTREEITEM hItem;

	// Returns a bitmask indicating presence/absence of drives
	dwDriveMask = GetLogicalDrives();

	for (int i = 'A'; i <= 'Z'; i++)
	{
		// If the current drive is present.
		if (dwDriveMask & (1 << (i - 'A')))
		{
			// Create a string for the root of the drive.
			wsprintf(szDrive, "%c:\\", i);
			// Basically, check for the presence of media in the drive
			iDriveType = GetDriveType(szDrive);

			if (iDriveType != 1)
			{
				cbBuf = lstrlen(szDrive);
				szDrive[cbBuf - 1] = NULL;	// Trim the "\" off

				hItem = AddDirectoryItem(TVI_ROOT, szDrive, cbBuf - 1, TRUE);
			}
		}
	}
}


HTREEITEM CChooseDirDlg::AddDirectoryItem(HTREEITEM hParent, LPCTSTR szPath, DWORD cbPath, BOOL fHasChildren, HTREEITEM hAfter)
{
	TV_INSERTSTRUCT tvi;
	HTREEITEM hItem;

	memset(&tvi, 0, sizeof(tvi));
	tvi.hParent = hParent;
	tvi.hInsertAfter = hAfter;
	tvi.item.mask = TVIF_TEXT;
	tvi.item.pszText = (LPTSTR)szPath;
	tvi.item.cchTextMax = cbPath;

	if (fHasChildren)
	{
		tvi.item.mask |= TVIF_CHILDREN;
		tvi.item.cChildren = 1;
	}
	
	hItem = TreeView_InsertItem(m_hwndTreeCtrl, &tvi);

	return hItem;
}


LPTSTR CChooseDirDlg::GetPathToItem(HTREEITEM hItem)
{
	static TCHAR szFullPath[MAX_PATH];
	HTREEITEM hParent;

	if (NULL != (hParent = TreeView_GetParent(m_hwndTreeCtrl, hItem)))
	{
		GetPathToItem(hParent);
		lstrcat(szFullPath, "\\");
		lstrcat(szFullPath, GetItemText(hItem));
	}
	else	// We're the drive letter, clear the buffer.
	{
		ZeroMemory(szFullPath, MAX_PATH);
		lstrcpy(szFullPath, GetItemText(hItem));
	}

	return szFullPath;
}


LPCTSTR CChooseDirDlg::GetCurrentPath()
{
	HTREEITEM hItem;

	if (NULL == (hItem = TreeView_GetSelection(m_hwndTreeCtrl)))
		return NULL;

	LPCTSTR pszPath = GetPathToItem(hItem);
	
	return pszPath;
}


void CChooseDirDlg::OnTreeClick(NM_TREEVIEW *pnmtv)
{
	SetWindowText(GetDlgItem(m_hWnd, IDC_DIR), GetCurrentPath());
}

void CChooseDirDlg::OnDestroy(HWND hwnd)
{
	TreeView_DeleteAllItems(m_hwndTreeCtrl);
}


LONG CChooseDirDlg::OnItemExpanding(NM_TREEVIEW *pnmtv)
{
	CBusyCursor bc;
	HTREEITEM hItem = pnmtv->itemNew.hItem;

	if (pnmtv->action != TVE_EXPAND)
		return 0;

	// If the item has been opened once already, delete the item, and re-add.
	if ((pnmtv->itemNew.state & TVIS_EXPANDEDONCE) == TVIS_EXPANDEDONCE)
	{
		HTREEITEM hParent = TreeView_GetParent(m_hwndTreeCtrl, hItem);
		if (hParent == NULL)
			hParent = TVI_ROOT;

		HTREEITEM hAfter = TreeView_GetPrevSibling(m_hwndTreeCtrl, hItem);

		// Get the old text
		LPCTSTR szTemp = GetItemText(hItem);
		LONG cbText = lstrlen(szTemp);
		TCHAR *szText = new TCHAR[cbText + 1];
		lstrcpy(szText, szTemp);

		// Delete the item, and re-add.
		TreeView_DeleteItem(m_hwndTreeCtrl, (LPARAM)hItem);
		hItem = AddDirectoryItem(hParent, szText, cbText, TRUE, hAfter);
		delete [] szText;
	}

	TreeView_Select(m_hwndTreeCtrl, hItem, TVGN_CARET);

	LPCTSTR pszPath = GetPathToItem(hItem);
	AddDirectories(hItem, pszPath);

	return 0;
}

void CChooseDirDlg::OnOK()
{
	HWND hwndCtl = GetDlgItem(m_hWnd, IDC_DIR);
	long cb = GetWindowTextLength(hwndCtl);
	m_szDir = new TCHAR[cb + 1];
	GetWindowText(hwndCtl, m_szDir, cb + 1);

	if (VerifyOrCreateDirectory(m_szDir))
		EndDialog(m_hWnd, IDOK);
}
