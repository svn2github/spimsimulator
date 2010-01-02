#ifndef PROGRESSDLG_H
#define PROGRESSDLG_H

#include "Dialog.h"

class CProgressDialog : public CDialog
{
// Public methods
public:
	CProgressDialog();
	~CProgressDialog();
	virtual HWND Create();
	virtual int DoModal();


// Private methods
private:
	HWND m_hwndProgress;
	TCHAR m_szCurDir[MAX_PATH];
	LPCTSTR GetHelpCmd();
	DWORD m_dwOSType;
	int m_iCopyFile;
	BOOL m_fCopyingDone;
	void SetStatusText(LPCTSTR strDesc, LPCTSTR sz1, LPCTSTR sz2, LPCTSTR sz3);
	void SaveUninstallInfo();
	void SetupRegistry();
	void CreateProgramGroupAndIcons();
	void CopyNextFile();
	long InitializeCopying();
	void OnTimer(HWND hwnd, UINT id);
	void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	BOOL OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);

// private member fields
private:

// Required by the interface
protected:
	virtual BOOL DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif // PROGRESSDLG_H
