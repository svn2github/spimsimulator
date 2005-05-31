#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <direct.h>

#include "..\common\defs.h"

int IsWin32Available();
double FAR PASCAL GetWin32sVersion();
long CALLBACK __export MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HANDLE hInstance);
BOOL InitInstance(HANDLE hInstance, int nCmdShow);

HANDLE hInst;
UINT g_nRegMsgFinished;

int PASCAL WinMain(HANDLE hInstance, HANDLE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    MSG msg;
    
	if (IsWin32Available())
	{
	    if (!hPrevInstance)
	    if (!InitApplication(hInstance))
	        return (FALSE);
	
	    if (!InitInstance(hInstance, nCmdShow))
	        return (FALSE);

		// Cache the "Finished" message                                      
    	g_nRegMsgFinished = GET_FINISH_MSG();
    	
		// Try running setup32
    	char *szCmd = new char[2048];
    	lstrcpy(szCmd, "setup32.exe ");
    	lstrcat(szCmd, lpCmdLine);
    	int nRet = WinExec(szCmd, SW_NORMAL);
    	delete [] szCmd;
    	
    	if (nRet <= 32)
    	{
    		MessageBox(NULL, "Unable to launch SETUP32.EXE.", NULL, MB_OK);
    		return 0;
    	}

	    while (GetMessage(&msg, NULL, NULL, NULL))
	    {
	    	TranslateMessage(&msg);
	    	DispatchMessage(&msg);
	    }
	    return (msg.wParam);
    }
    else
    	return 0;
}


BOOL InitApplication(HANDLE hInstance)
{
    WNDCLASS  wc;
    wc.style = NULL;
    wc.lpfnWndProc = MainWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = SETUP_WND_CLASS;

    return (RegisterClass(&wc));
}


BOOL InitInstance(HANDLE hInstance, int nCmdShow)
{
    HWND hWnd;

    hInst = hInstance;

    hWnd = CreateWindow(
    	SETUP_WND_CLASS, SETUP_WND_CAPTION, WS_OVERLAPPEDWINDOW,
    	CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
    	NULL, NULL, hInstance, NULL);

    if (!hWnd)
        return (FALSE);
        
    // Don't show the window.  We want it hidden.

    return (TRUE);
}

long CALLBACK __export MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == g_nRegMsgFinished)
	{
		if (lParam == SETUP_UNINSTALL_SUCCESSFUL)
		{
			remove("setup32.exe");
			remove("setup.exe");
		
			char *szDir = new char[_MAX_PATH + 1];
			getcwd(szDir, _MAX_PATH);
			chdir("..");
			rmdir(szDir);
			delete [] szDir;
		}
		
       	DestroyWindow(hWnd);
       	return 0;
    }

    switch (message)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return (DefWindowProc(hWnd, message, wParam, lParam));
    }
    return (NULL);
}


int IsWin32Available()
{
        if ((GetWinFlags() & WF_NTWOW) == WF_NTWOW)
        	return TRUE;

        DWORD dwVersion = GetVersion();
        DWORD dwMajor = LOBYTE(LOWORD(dwVersion));
        DWORD dwMinor = HIBYTE(LOWORD(dwVersion));
        double dbVersion = dwMajor + (dwMinor / 100.0);
            
        // This is only here to pacify a compiler bug in VC152c.
        // Without this, it doesn't properly detect Win95  
        char szMsg[64];
        sprintf(szMsg, "", dbVersion);
        
        if (dbVersion >= 3.95)
        	return TRUE;
        else
        {
        	double dbWin32sVer = GetWin32sVersion();
        	if (dbWin32sVer >= 1.30)
        		return TRUE;
        	else if (dbWin32sVer > 0)
        	{
        		char * szMsg = new char[2048];
        		sprintf(szMsg, "This computer has Win32s version %lf installed.\n"
        					   "%s\n"
        					   "\n"
        					   "Would you like to attempt to install anyway?",
        					   dbWin32sVer, GET_WIN32S_MSG);
        		int nRet = MessageBox(NULL, szMsg, NULL, MB_YESNO | MB_ICONSTOP);
        		delete [] szMsg;
        		
        		if (nRet == IDNO)
        			return FALSE;
        		else
        			return TRUE;
        	}
        	else
        	{
	        	if (dbWin32sVer == 0)
	        	{
	        		char* szMsg = new char[2048];
	        		sprintf(szMsg, "This computer does not have Win32s installed.\n"
	        					   "%s", GET_WIN32S_MSG);
	        		MessageBox(NULL, szMsg, NULL, MB_OK | MB_ICONSTOP);
	        		delete [] szMsg;
	        	}
	        	// else, Win32s was installed, but non-functional.
	        	
        		return FALSE;
        	}
        }
}


typedef struct { 
    BYTE bMajor; 
    BYTE bMinor; 
    WORD wBuildNumber; 
    BOOL fDebug; 
} WIN32SINFO, far * LPWIN32SINFO; 

typedef WORD(*PFNGETWIN32SINFO)(LPWIN32SINFO lpInfo);
 
double FAR PASCAL GetWin32sVersion()
{ 
	double dbWin32sVersion = 0.0;
    PFNGETWIN32SINFO  pfnInfo; 
    HANDLE            hWin32sys; 
    WIN32SINFO        Info; 

    UINT sem = SetErrorMode(SEM_NOOPENFILEERRORBOX); 
    hWin32sys = LoadLibrary("W32SYS.DLL");
    SetErrorMode(sem);
    
    if (hWin32sys > HINSTANCE_ERROR)
    {
        pfnInfo = (PFNGETWIN32SINFO)GetProcAddress(hWin32sys, "GETWIN32SINFO");
        if (pfnInfo)
        {
        	char *szReason;
        	
            // Win32s version 1.1 (or later) is installed
            WORD wInfo = (*pfnInfo)(&Info);
            
            if (wInfo == 0)
                dbWin32sVersion = Info.bMajor + (Info.bMinor / 100.0);
			else
			{
				if (wInfo == 1)
					szReason = "because the Win32s VxD is not present on the system.\n"
							   "\n"
							   "Try reinstalling Win32s.";
		    	else if (wInfo == 2)
		    		szReason = "because virtual memory (swapping) is not turned on.\n"
		    				   "\n"
		    				   "See the Control Panel, under the Enhanced category, "
		    				   "to enable virtual memory.";
		    	else if (wInfo == 3)
		    		szReason = "because Windows is not running in 386 Enhanced mode.\n"
		    				   "\n"
		    				   "Try forcing Enhanced mode by using \"win /3\" from DOS.";
		    	else
		    		szReason = "for an unknown reason.";

				char *szMsg = new char[2048];
				sprintf(szMsg, "The Win32s extensions are required to run PCSpim for Windows.\n"
							   "\n"
							   "Win32s appears to have been installed on this computer.\n"
							   "\n"
							   "However, installation is unable to continue %s\n"
							   "\n"
			    			   "If you continue to have problems, please contact "
			    			   "dac@cs.wisc.edu with a bug report.",
			    			   szReason);
			    MessageBox(NULL, szMsg, NULL, MB_OK | MB_ICONEXCLAMATION);
			    delete [] szMsg;
			    dbWin32sVersion = -1.0;
        	}
        }
        else	// Win32s version 1.0 is installed.
            dbWin32sVersion = 1.0;
            
        FreeLibrary(hWin32sys); 
    }
    
    return dbWin32sVersion;
} 

