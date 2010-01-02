#ifndef DEFS_H
#define DEFS_H

#define GET_FINISH_MSG()		RegisterWindowMessage("Setup32 is finished")
#define SETUP_WND_CLASS			"SetupHiddenWindowClass"
#define SETUP_WND_CAPTION		"Setup Hidden Window"

#define WF_NTWOW	0x4000
#define GET_WIN32S_MSG	"You need at least version 1.3 to use PCSpim for Windows.\n"	\
						"\n"															\
						"You can obtain Win32s version 1.3 at:\n"						\
						"ftp://ftp.microsoft.com/Softlib/MSLFILES/PW1118.EXE"
						

#define SETUP_TITLE	"PCSpim for Windows Setup"
#define SETUP_INSTALL_SUCCESSFUL	0
#define SETUP_INSTALL_FAILED        1
#define SETUP_UNINSTALL_SUCCESSFUL  2
#define SETUP_UNINSTALL_FAILED      3

#define INI_FILENAME			"pcspim.ini"
#define INI_SETTINGS			"Settings"

typedef struct
{
	LPSTR szFrom;
	LPSTR szTo;
	BOOL f95andNT;
	BOOL fWin32s;
	BOOL fSystemFile;
} FILEINFO;


#endif // DEFS_H
