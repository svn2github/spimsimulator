REM SPIM S20 MIPS simulator.
REM Definitions for the SPIM S20.
REM
REM Copyright (C) 1990-2004 by James Larus (larus@cs.wisc.edu).
REM ALL RIGHTS RESERVED.
REM Changes for DOS and Windows versions by David A. Carley (dac@cs.wisc.edu)
REM
REM SPIM is distributed under the following conditions:
REM
REM   You may make copies of SPIM for your own use and modify those copies.
REM
REM   All copies of SPIM must retain my name and copyright notice.
REM
REM   You may not sell SPIM or distributed SPIM in conjunction with a
REM   commerical product or service without the expressed written consent of
REM   James Larus.
REM
REM THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
REM IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
REM WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
REM PURPOSE.

REM $Header: $

REM Batch file to produce PCSPIM help files.
REM
REM Usage: MakeHelp <target directory>
REM    e.g. MakeHelp ..\Release
REM

@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by PCSPIM.HPJ. >"hlp\PCSpim.hm"
echo. >>"hlp\PCSpim.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\PCSpim.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\PCSpim.hm"
echo. >>"hlp\PCSpim.hm"
echo // Prompts (IDP_*) >>"hlp\PCSpim.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\PCSpim.hm"
echo. >>"hlp\PCSpim.hm"
echo // Resources (IDR_*) >>"hlp\PCSpim.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\PCSpim.hm"
echo. >>"hlp\PCSpim.hm"
echo // Dialogs (IDD_*) >>"hlp\PCSpim.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\PCSpim.hm"
echo. >>"hlp\PCSpim.hm"
echo // Frame Controls (IDW_*) >>"hlp\PCSpim.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\PCSpim.hm"
REM -- Make help for Project PCSPIM

echo Building Win32 Help files
start /wait hcrtf -x "hlp\PCSpim.hpj"
echo.

copy "hlp\PCSpim.hlp" %1
copy "hlp\PCSpim.cnt" %1

echo.


