# Microsoft Visual C++ generated build script - Do not modify

PROJ = SETUP
DEBUG = 0
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\SPIM\SPIMINST\WINDOWS\SETUP\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC =             
FIRSTCPP = SETUP.CPP   
RC = rc
CFLAGS_D_WEXE = /nologo /W3 /FR /G2 /Zi /D_DEBUG /Od /AM /GA /Fd"SETUP.PDB"
CFLAGS_R_WEXE = /nologo /W3 /FR /O1 /DNDEBUG /AM /GA
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE /CO 
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE 
LIBS_D_WEXE = oldnames libw mlibcew 
LIBS_R_WEXE = oldnames libw mlibcew 
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
DEFFILE = SETUP.DEF
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WEXE)
LFLAGS = $(LFLAGS_D_WEXE)
LIBS = $(LIBS_D_WEXE)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_WEXE)
LFLAGS = $(LFLAGS_R_WEXE)
LIBS = $(LIBS_R_WEXE)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = SETUP.SBR


SETUP_DEP = c:\spim\spiminst\windows\common\defs.h


SETUP_RCDEP = c:\spim\spiminst\windows\setup\setup.ico


all:	$(PROJ).EXE $(PROJ).BSC

SETUP.OBJ:	SETUP.CPP $(SETUP_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c SETUP.CPP

SETUP.RES:	SETUP.RC $(SETUP_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r SETUP.RC


$(PROJ).EXE::	SETUP.RES

$(PROJ).EXE::	SETUP.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
SETUP.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
d:\vc152\msvc15\lib\+
d:\vc152\msvc15\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) SETUP.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	SETUP.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) SETUP.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
