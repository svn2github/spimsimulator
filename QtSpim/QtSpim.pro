#-------------------------------------------------
#
# Project created by QtCreator 2010-07-11T10:46:07
#
#-------------------------------------------------

QT       += core gui

TARGET = QtSpim
TEMPLATE = app


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

YACCSOURCES = ../CPU/parser.y
LEXSOURCES = ../CPU/scanner.l


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


# Default Qt/Qmake conventions for naming yacc and lex files are different from
# SPIM. These rules produce output that do not require source changes.
#
QMAKE_YACC		= bison
QMAKE_YACCFLAGS_MANGLE	= -d --file-prefix=y
QMAKE_YACC_HEADER	= y.tab.h
QMAKE_YACC_SOURCE	= y.tab.c

QMAKE_LEX		= flex
QMAKE_LEXFLAGS_MANGLE	= -o lex.scanner.c
QMAKE_LEXFLAGS		= -I -8



# Microsoft Visual C compiler flags

# Compile all files as C++
#
QMAKE_CFLAGS_DEBUG	+= -TP
QMAKE_CFLAGS_RELEASE	+= -TP

# Disable security warnings
#
DEFINES += _CRT_SECURE_NO_WARNINGS


