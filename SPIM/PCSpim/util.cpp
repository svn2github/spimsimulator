#include "stdafx.h"
#include "util.h"
#include "regman.h"

LPTSTR MakeCRLFValid(LPCTSTR strBuf)
{
  if (lstrlen(strBuf) == 0)
    return NULL;

  // Allocate our new buffer twice as large as the old
  LPTSTR strNew = new TCHAR[lstrlen(strBuf) * 2 + 1];
  LPTSTR strRet = strNew;

  ASSERT(strBuf);

  while (*strBuf)
    {
      if (*strBuf == '\r')
	{
	  COPYCHAR(strNew, strBuf);

	  if (*strBuf == '\n')	// We had a CRLF.  Copy it.
	    COPYCHAR(strNew, strBuf);
	  else					// No LF.  Append one.
	    APPENDCHAR(strNew, '\n');
	}
      else if (*strBuf == '\n')
	{
	  APPENDCHAR(strNew, '\r');
	  COPYCHAR(strNew, strBuf);

	  // We had a LFCR.  Changed to CRLF.  Eat the CR.
	  if (*strBuf == '\r')
	    ++strBuf;
	}
      else
	COPYCHAR(strNew, strBuf);	// Normal
    }
  *strNew = NULL;

  return strRet;
}


int UTIL_GetOSType()
{
  OSVERSIONINFO osvi;
  osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO); // Win32 API says so
  GetVersionEx(&osvi);

  return osvi.dwPlatformId;
}

