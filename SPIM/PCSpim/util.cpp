// SPIM S20 MIPS simulator.
// Definitions for the SPIM S20.
//
// Copyright (C) 1990-2004 by James Larus (larus@cs.wisc.edu).
// ALL RIGHTS RESERVED.
// Changes for DOS and Windows versions by David A. Carley (dac@cs.wisc.edu)
//
// SPIM is distributed under the following conditions:
//
//   You may make copies of SPIM for your own use and modify those copies.
//
//   All copies of SPIM must retain my name and copyright notice.
//
//   You may not sell SPIM or distributed SPIM in conjunction with a
//   commerical product or service without the expressed written consent of
//   James Larus.
//
// THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE.

/* $Version: $ */

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

