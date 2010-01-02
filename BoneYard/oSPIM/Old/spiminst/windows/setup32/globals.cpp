#include <windows.h>
#include "..\common\defs.h"

HINSTANCE g_hInst = NULL;
char *g_szDestDir = NULL;
LONG g_lExitCode = SETUP_INSTALL_SUCCESSFUL;
BOOL g_fViewedReadme = FALSE;
FILEINFO g_rgfi[] =
{
	{"pcspim.exe", "pcspim.exe", TRUE, TRUE, FALSE},
	{"mfc40.dll", "mfc40.dll", TRUE, TRUE, TRUE},
	{"msvc4095.dll", "msvcrt40.dll", TRUE, FALSE, TRUE},
	{"msvc4032.dll", "msvcrt40.dll", FALSE, TRUE, TRUE},
	{"trap.han", "trap.handler", TRUE, TRUE, FALSE},
	{"readme.txt", "readme.txt", TRUE, TRUE, FALSE},
	{"pcspim.hlp", "pcspim.hlp", TRUE, TRUE, FALSE},
	{"pcspim.cnt", "pcspim.cnt", TRUE, TRUE, FALSE},
	{"setup.exe", "setup.exe", TRUE, TRUE, FALSE},
	{"setup32.exe", "setup32.exe", TRUE, TRUE, FALSE},
	{NULL, NULL, FALSE, FALSE, FALSE}
};


