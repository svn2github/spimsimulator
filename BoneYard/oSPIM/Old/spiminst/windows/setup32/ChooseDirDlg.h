#ifndef CHOOSEDIRDLG_H
#define CHOOSEDIRDLG_H

#include "Dialog.h"

class CChooseDirDlg : public CDialog
{
// Public methods
public:
	virtual HWND Create();
	virtual int DoModal();
	LPTSTR m_szDir;

protected:
	BOOL OnInitDialog(HWND, HWND hwndFocus, LPARAM lParam);
	LONG OnNotify(HWND hwnd, int idCtrl, LPNMHDR pnmh);
	void OnCommand(HWND, int id, HWND hwndCtl, UINT codeNotify);

private:
	void OnOK();
	LONG OnItemExpanding(NM_TREEVIEW *pnmtv);
	void OnDestroy(HWND hwnd);
	BOOL HasDirectories(LPCTSTR szPath);
	BOOL IsDotOrDotDot(LPCTSTR szPath);
	DWORD AddDirectories(HTREEITEM hParent, LPCTSTR szPath);
	LPCTSTR GetItemText(HTREEITEM hItem);
	void AddDrives();
	HTREEITEM AddDirectoryItem(HTREEITEM hParent, LPCTSTR szPath, DWORD cbPath, BOOL fHasChildren, HTREEITEM hAfter = TVI_LAST);
	LPTSTR GetPathToItem(HTREEITEM hItem);
	LPCTSTR GetCurrentPath();
	void OnTreeClick(NM_TREEVIEW *pnmtv);

	HWND m_hwndTreeCtrl;

protected:
	virtual BOOL DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif // CHOOSEDIRDLG_H
