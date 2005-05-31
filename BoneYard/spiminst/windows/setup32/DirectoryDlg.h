#ifndef DIRECTORYDLG_H
#define DIRECTORYDLG_H

#include "Dialog.h"

class CDirectoryDialog : public CDialog
{
// Public methods
public:
	virtual HWND Create();
	virtual int DoModal();


// Private methods
private:
	void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	BOOL OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);

// private member fields
private:

// Required by the interface
protected:
	virtual BOOL DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif // DIRECTORYDLG_H
