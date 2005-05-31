# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=setup32 - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to setup32 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "setup32 - Win32 Release" && "$(CFG)" !=\
 "setup32 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "setup32.mak" CFG="setup32 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "setup32 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "setup32 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "setup32 - Win32 Debug"
RSC=rc.exe
CPP=cl.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "setup32 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\setup32.exe"

CLEAN : 
	-@erase "$(INTDIR)\ChooseDirDlg.obj"
	-@erase "$(INTDIR)\Dialog.obj"
	-@erase "$(INTDIR)\DirectoryDlg.obj"
	-@erase "$(INTDIR)\globals.obj"
	-@erase "$(INTDIR)\ProgressDlg.obj"
	-@erase "$(INTDIR)\Regman.obj"
	-@erase "$(INTDIR)\setup32.obj"
	-@erase "$(INTDIR)\setup32.res"
	-@erase "$(INTDIR)\util.obj"
	-@erase "$(OUTDIR)\setup32.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/setup32.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/setup32.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/setup32.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 comctl32.lib user32.lib advapi32.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=comctl32.lib user32.lib advapi32.lib /nologo /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)/setup32.pdb" /machine:I386\
 /out:"$(OUTDIR)/setup32.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ChooseDirDlg.obj" \
	"$(INTDIR)\Dialog.obj" \
	"$(INTDIR)\DirectoryDlg.obj" \
	"$(INTDIR)\globals.obj" \
	"$(INTDIR)\ProgressDlg.obj" \
	"$(INTDIR)\Regman.obj" \
	"$(INTDIR)\setup32.obj" \
	"$(INTDIR)\setup32.res" \
	"$(INTDIR)\util.obj"

"$(OUTDIR)\setup32.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "setup32 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\setup32.exe" "$(OUTDIR)\setup32.bsc"

CLEAN : 
	-@erase "$(INTDIR)\ChooseDirDlg.obj"
	-@erase "$(INTDIR)\ChooseDirDlg.sbr"
	-@erase "$(INTDIR)\Dialog.obj"
	-@erase "$(INTDIR)\Dialog.sbr"
	-@erase "$(INTDIR)\DirectoryDlg.obj"
	-@erase "$(INTDIR)\DirectoryDlg.sbr"
	-@erase "$(INTDIR)\globals.obj"
	-@erase "$(INTDIR)\globals.sbr"
	-@erase "$(INTDIR)\ProgressDlg.obj"
	-@erase "$(INTDIR)\ProgressDlg.sbr"
	-@erase "$(INTDIR)\Regman.obj"
	-@erase "$(INTDIR)\Regman.sbr"
	-@erase "$(INTDIR)\setup32.obj"
	-@erase "$(INTDIR)\setup32.res"
	-@erase "$(INTDIR)\setup32.sbr"
	-@erase "$(INTDIR)\util.obj"
	-@erase "$(INTDIR)\util.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\setup32.bsc"
	-@erase "$(OUTDIR)\setup32.exe"
	-@erase "$(OUTDIR)\setup32.ilk"
	-@erase "$(OUTDIR)\setup32.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /FR"$(INTDIR)/" /Fp"$(INTDIR)/setup32.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/"\
 /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/setup32.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/setup32.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ChooseDirDlg.sbr" \
	"$(INTDIR)\Dialog.sbr" \
	"$(INTDIR)\DirectoryDlg.sbr" \
	"$(INTDIR)\globals.sbr" \
	"$(INTDIR)\ProgressDlg.sbr" \
	"$(INTDIR)\Regman.sbr" \
	"$(INTDIR)\setup32.sbr" \
	"$(INTDIR)\util.sbr"

"$(OUTDIR)\setup32.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 comctl32.lib user32.lib advapi32.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=comctl32.lib user32.lib advapi32.lib /nologo /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/setup32.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/setup32.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ChooseDirDlg.obj" \
	"$(INTDIR)\Dialog.obj" \
	"$(INTDIR)\DirectoryDlg.obj" \
	"$(INTDIR)\globals.obj" \
	"$(INTDIR)\ProgressDlg.obj" \
	"$(INTDIR)\Regman.obj" \
	"$(INTDIR)\setup32.obj" \
	"$(INTDIR)\setup32.res" \
	"$(INTDIR)\util.obj"

"$(OUTDIR)\setup32.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "setup32 - Win32 Release"
# Name "setup32 - Win32 Debug"

!IF  "$(CFG)" == "setup32 - Win32 Release"

!ELSEIF  "$(CFG)" == "setup32 - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\setup32.cpp
DEP_CPP_SETUP=\
	"..\common\defs.h"\
	".\Dialog.h"\
	".\DirectoryDlg.h"\
	".\globals.h"\
	".\ProgressDlg.h"\
	".\regman.H"\
	".\spimreg.h"\
	".\util.h"\
	

!IF  "$(CFG)" == "setup32 - Win32 Release"


"$(INTDIR)\setup32.obj" : $(SOURCE) $(DEP_CPP_SETUP) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "setup32 - Win32 Debug"


"$(INTDIR)\setup32.obj" : $(SOURCE) $(DEP_CPP_SETUP) "$(INTDIR)"

"$(INTDIR)\setup32.sbr" : $(SOURCE) $(DEP_CPP_SETUP) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\setup32.rc
DEP_RSC_SETUP3=\
	".\remove32.ico"\
	".\setup32.ico"\
	

"$(INTDIR)\setup32.res" : $(SOURCE) $(DEP_RSC_SETUP3) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ProgressDlg.cpp
DEP_CPP_PROGR=\
	"..\common\defs.h"\
	".\Dialog.h"\
	".\globals.h"\
	".\ProgressDlg.h"\
	".\regman.H"\
	".\spimreg.h"\
	".\util.h"\
	

!IF  "$(CFG)" == "setup32 - Win32 Release"


"$(INTDIR)\ProgressDlg.obj" : $(SOURCE) $(DEP_CPP_PROGR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "setup32 - Win32 Debug"


"$(INTDIR)\ProgressDlg.obj" : $(SOURCE) $(DEP_CPP_PROGR) "$(INTDIR)"

"$(INTDIR)\ProgressDlg.sbr" : $(SOURCE) $(DEP_CPP_PROGR) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\util.cpp
DEP_CPP_UTIL_=\
	"..\common\defs.h"\
	".\util.h"\
	

!IF  "$(CFG)" == "setup32 - Win32 Release"


"$(INTDIR)\util.obj" : $(SOURCE) $(DEP_CPP_UTIL_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "setup32 - Win32 Debug"


"$(INTDIR)\util.obj" : $(SOURCE) $(DEP_CPP_UTIL_) "$(INTDIR)"

"$(INTDIR)\util.sbr" : $(SOURCE) $(DEP_CPP_UTIL_) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dialog.cpp
DEP_CPP_DIALO=\
	".\Dialog.h"\
	

!IF  "$(CFG)" == "setup32 - Win32 Release"


"$(INTDIR)\Dialog.obj" : $(SOURCE) $(DEP_CPP_DIALO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "setup32 - Win32 Debug"


"$(INTDIR)\Dialog.obj" : $(SOURCE) $(DEP_CPP_DIALO) "$(INTDIR)"

"$(INTDIR)\Dialog.sbr" : $(SOURCE) $(DEP_CPP_DIALO) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\globals.cpp
DEP_CPP_GLOBA=\
	"..\common\defs.h"\
	

!IF  "$(CFG)" == "setup32 - Win32 Release"


"$(INTDIR)\globals.obj" : $(SOURCE) $(DEP_CPP_GLOBA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "setup32 - Win32 Debug"


"$(INTDIR)\globals.obj" : $(SOURCE) $(DEP_CPP_GLOBA) "$(INTDIR)"

"$(INTDIR)\globals.sbr" : $(SOURCE) $(DEP_CPP_GLOBA) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DirectoryDlg.cpp
DEP_CPP_DIREC=\
	"..\common\defs.h"\
	".\ChooseDirDlg.h"\
	".\Dialog.h"\
	".\DirectoryDlg.h"\
	".\globals.h"\
	".\regman.H"\
	".\util.h"\
	

!IF  "$(CFG)" == "setup32 - Win32 Release"


"$(INTDIR)\DirectoryDlg.obj" : $(SOURCE) $(DEP_CPP_DIREC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "setup32 - Win32 Debug"


"$(INTDIR)\DirectoryDlg.obj" : $(SOURCE) $(DEP_CPP_DIREC) "$(INTDIR)"

"$(INTDIR)\DirectoryDlg.sbr" : $(SOURCE) $(DEP_CPP_DIREC) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ChooseDirDlg.cpp
DEP_CPP_CHOOS=\
	"..\common\defs.h"\
	".\BusyCursor.h"\
	".\ChooseDirDlg.h"\
	".\Dialog.h"\
	".\globals.h"\
	".\util.h"\
	

!IF  "$(CFG)" == "setup32 - Win32 Release"


"$(INTDIR)\ChooseDirDlg.obj" : $(SOURCE) $(DEP_CPP_CHOOS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "setup32 - Win32 Debug"


"$(INTDIR)\ChooseDirDlg.obj" : $(SOURCE) $(DEP_CPP_CHOOS) "$(INTDIR)"

"$(INTDIR)\ChooseDirDlg.sbr" : $(SOURCE) $(DEP_CPP_CHOOS) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Regman.cpp
DEP_CPP_REGMA=\
	".\regman.H"\
	

!IF  "$(CFG)" == "setup32 - Win32 Release"


"$(INTDIR)\Regman.obj" : $(SOURCE) $(DEP_CPP_REGMA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "setup32 - Win32 Debug"


"$(INTDIR)\Regman.obj" : $(SOURCE) $(DEP_CPP_REGMA) "$(INTDIR)"

"$(INTDIR)\Regman.sbr" : $(SOURCE) $(DEP_CPP_REGMA) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
