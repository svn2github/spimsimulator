#-------------------------------------------------
#
# Project created by QtCreator 2010-07-11T10:46:07
#
#-------------------------------------------------

QT       += core gui

TARGET = QtSpim
TEMPLATE = app


YACCSOURCES = ../CPU/parser.y
LEXSOURCES = ../CPU/scanner.l


SOURCES += main.cpp\
        spimview.cpp\
        menu.cpp\
        regwin.cpp\
        textwin.cpp\
        datawin.cpp\
        state.cpp\
        console.cpp\
        ../CPU/data.c\
        ../CPU/display-utils.c\
        ../CPU/inst.c\
        ../CPU/mem.c\
        ../CPU/run.c\
        ../CPU/spim-utils.c\
        ../CPU/string-stream.c\
        ../CPU/sym-tbl.c\
        ../CPU/syscall.c\
        spim_support.c


HEADERS  += spimview.h\
	texttextedit.h\
	datatextedit.h\
        spim_settings.h\
        settablecheckbox.h\
        console.h


FORMS    += spimview.ui\
	savelogfile.ui\
	printwindows.ui\
        runparams.ui\
        settings.ui


INCLUDEPATH = ../CPU ../spim


win32:RESOURCES = windows_images.qrc


QMAKE_YACC		= bison
QMAKE_YACCFLAGS		= -d --defines=parser.tab.h --output=parser.tab.c
QMAKE_YACCFLAGS_MANGLE	= -p yy
QMAKE_YACC_HEADER	= parser.tab.h
QMAKE_YACC_SOURCE	= parser.tab.c

QMAKE_LEX		= flex
QMAKE_LEXFLAGS_MANGLE	= -o lex.scanner.c
QMAKE_LEXFLAGS		= -I -8



# Microsoft Visual C compiler flags
#
win32-msvc2008 {
  # Compile all files as C++
  #
  QMAKE_CFLAGS_DEBUG	+= -TP
  QMAKE_CFLAGS_RELEASE	+= -TP

  # Disable security warnings
  #
  DEFINES += _CRT_SECURE_NO_WARNINGS
}


# gcc flags
#
win32-g++ {
  # Compile all files as C++
  # Surpress gcc warning about deprecated conversion from string constant to char*
  #
  QMAKE_CFLAGS_DEBUG	+= -x c++ -Wno-write-strings
  QMAKE_CFLAGS_RELEASE	+= -x c++ -Wno-write-strings
  QMAKE_CXXFLAGS_DEBUG	+= -Wno-write-strings
  QMAKE_CXXFLAGS_RELEASE	+= -Wno-write-strings
}

linux-g++ {
  # Compile all files as C++
  # Surpress gcc warning about deprecated conversion from string constant to char*
  #
  QMAKE_CFLAGS_DEBUG	+= -x c++ -Wno-write-strings
  QMAKE_CFLAGS_RELEASE	+= -x c++ -Wno-write-strings
  QMAKE_CXXFLAGS_DEBUG	+= -Wno-write-strings
  QMAKE_CXXFLAGS_RELEASE	+= -Wno-write-strings
}

