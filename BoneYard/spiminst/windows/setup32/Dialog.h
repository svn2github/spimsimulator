#ifndef DIALOG_H
#define DIALOG_H

#define HANDLE_DLG_MSG(hwnd, message, fn)    \
    case (message): return (BOOL)HANDLE_##message((hwnd), (wParam), (lParam), (fn))

class CDialog
{
public:
	WNDPROC m_pfnSubclassedWndProc;
	void SetInitialPos(RECT &r);
	CDialog();
	~CDialog();
	virtual HWND Create(HINSTANCE hInst, HWND hwndParent, UINT idDlg);
	virtual int DoModal(HINSTANCE hInst, HWND hwndParent, UINT idDlg);

public:
	HWND m_hWnd;

private:
	BOOL m_fInitialRectSet;
	RECT m_rInitial;
	static BOOL CALLBACK class_initial_DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
	BOOL class_DialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
	virtual BOOL DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif // DIALOG_H
