// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows 95 Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxtempl.h>		// MFC template classes

extern "C"
{
#include "..\src\spim.h"
#include "..\src\spim-utils.h"
#include "..\src\inst.h"
#include "..\src\sym-tbl.h"
#include "..\src\reg.h"
#include "..\src\mem.h"
#include "..\src\scanner.h"
}


#ifdef STDAFX_CPP
#define GLOBAL
#else
#define GLOBAL extern
#endif

class CPCSpimView;

GLOBAL CPCSpimView *g_pView;
GLOBAL BOOL			g_fSaveWinPos;
GLOBAL BOOL			g_fLoadTrapHandler;
GLOBAL BOOL			g_fRunning;
GLOBAL BOOL			g_fGenRegHex;
GLOBAL BOOL			g_fFPRegHex;
GLOBAL BOOL			g_checkUndefinedSymbols;
GLOBAL CString			g_strCmdLine;

