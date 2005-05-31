#ifndef UTIL_H
#define UTIL_H

void CenterWindow(HWND hWnd);
DWORD GetOSType();
BOOL DoesFileExist(LPCTSTR szFile);
BOOL VerifyOrCreateDirectory(LPCTSTR szDir);
BOOL CreateDirTree(LPCTSTR szDir);
DWORD GetOSMajorVer();
BOOL SendCommandToProgMan(LPCTSTR szCmd);

#endif // UTIL_H