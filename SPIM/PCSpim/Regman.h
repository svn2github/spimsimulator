// SPIM S20 MIPS simulator.
// Definitions for the SPIM S20.
//
// Copyright (C) 1990-2000 by James Larus (larus@cs.wisc.edu).
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

#ifndef _REGMAN_H_
#define _REGMAN_H_

#include <windows.h>
#include "winreg.h"

//
//	RegMan_CreateKey
//
//	Purpose:	Use to create a key in the registry.  This function works
//				on both Win32 and Win16.
//
//	Return Value:	ERROR_SUCCESS if successful
//					Error value otherwise(in winerror.h)
//
LONG RegMan_CreateKey(HKEY hKey, LPCTSTR lpstrKeyName, PHKEY phKeyDest);


//
//	RegMan_DeleteKey
//
//	Purpose:	Use to delete a key in the registry.  This function works
//				on both Win32 and Win16.
//
//	Return Value:	ERROR_SUCCESS if successful
//					Error value otherwise(in winerror.h)
//
LONG RegMan_DeleteKey(HKEY hKey, LPCTSTR lpstrKeyName);


//
//	RegMan_OpenKey
//
//	Purpose:	Use to open a key in the registry.  This function works
//				on both Win32 and Win16
//
//	Return Value:	ERROR_SUCCESS if successful
//					Error value otherwise(in winerror.h)
//
LONG RegMan_OpenKey(HKEY hKey, LPCTSTR lpstrKeyName, PHKEY phKeyDest);


//
//	RegMan_GetDWORDValue
//
//	Purpose:	Use to retrieve a DWORD from a registry "value".  This function
//				works on both Win32 and Win16
//
//	Return Value:	ERROR_SUCCESS if successful
//					Error value otherwise(in winerror.h)
//
LONG RegMan_GetDWORDValue(HKEY hKey, LPCTSTR lpstrValueName, LPDWORD pdwDest);


//
//	RegMan_SetSZValue
//
//	Purpose:	Use to set a string to a registry "value".  This function
//				works on both Win32 and Win16
//
//	Return Value:	ERROR_SUCCESS if successful
//					Error value otherwise(in winerror.h)
//
LONG RegMan_SetSZValue(HKEY hKey, LPCTSTR lpstrValueName, LPCTSTR lpstrSrc);


//
//	RegMan_GetSZValue
//
//	Purpose:	Use to retrieve a string from a registry "value".  This function
//				works on both Win32 and Win16
//
//	Return Value:	ERROR_SUCCESS if successful
//					Error value otherwise(in winerror.h)
//
LONG RegMan_GetSZValue(HKEY hKey, LPCTSTR lpstrValueName, LPTSTR lpstrDest, LPDWORD plcbDest);


//
//	RegMan_GetNumValues
//
//	Purpose:	Use to retrieve the number of "values" directly under a key
//				in the registry.  This function works on both Win32 and Win16
//
//	Return Value:	ERROR_SUCCESS if successful
//					Error value otherwise(in winerror.h)
//
LONG RegMan_GetNumValues(HKEY hKey, LPDWORD plcValues);


//
//	RegMan_EnumValueName
//
//	Purpose:	Use to enumerate the names of the "values" under a key
//				in the registry.  This function works in both Win32 and Win16.
//
//	Return Value:	ERROR_SUCCESS if successful
//					Error value otherwise(in winerror.h)
//
LONG RegMan_EnumValueName(HKEY hKey, DWORD dwIndex, LPTSTR lpstrValueName, LPDWORD pdwcbValueName);


//
//	RegMan_EnumSZValue
//
//	Purpose:	Use to enumerate the names _and_ string contents of the "values"
//				under a key in the registry.  This function works in both Win32 and Win16.
//
//	Return Value:	ERROR_SUCCESS if successful
//					Error value otherwise(in winerror.h)
//
LONG RegMan_EnumSZValue(HKEY hKey, DWORD dwIndex, LPTSTR lpstrValueName, LPDWORD pdwcbValueName, LPTSTR lpstrData, LPDWORD pdwcbData);

//
//	RegMan_EnumSZValue
//
//	Purpose:	Use to enumerate the names of the subkeys of a key in the registry.
//				This function works in both Win32 and Win16.
//
//	Return Value:	ERROR_SUCCESS if successful
//					Error value otherwise(in winerror.h)
//
LONG RegMan_EnumKey(HKEY hKey, DWORD dwIndex, LPTSTR lpstrName, LPDWORD pdwcbName);

//
//	RegMan_EnumSZValue
//
//	Purpose:	Use to delete a "value" under a key in the registry.
//				This function works in both Win32 and Win16.
//
//	Return Value:	ERROR_SUCCESS if successful
//					Error value otherwise(in winerror.h)
//
LONG RegMan_DeleteValue(HKEY hKey, LPCTSTR lpstrValueName);

//
//	RegMan_EnumSZValue
//
//	Purpose:	Use to retrieve a DWORD from a registry "value".
//				This function works in both Win32 and Win16.
//
//	Return Value:	ERROR_SUCCESS if successful
//					Error value otherwise(in winerror.h)
//
LONG RegMan_SetDWORDValue(HKEY hKey, LPCTSTR lpstrSubKey, DWORD dwData);

//
//	RegMan_EnumSZValue
//
//	Purpose:	Use to retrieve a DWORD from a registry "value".
//				This function works in both Win32 and Win16.
//
//	Return Value:	ERROR_SUCCESS if successful
//					Error value otherwise(in winerror.h)
//
LONG RegMan_CloseKey(HKEY hKey);

// Copies a registry tree.
LONG RegMan_CopyTree(HKEY hKeySrc, HKEY hKeyDest);

// Deletes the specified registry tree.
LONG RegMan_DeleteTree(HKEY hKey, LPCTSTR szTreeName);

#endif // _REGMAN_H

