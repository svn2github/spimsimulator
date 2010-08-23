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
        ../CPU/data.c\
        ../CPU/display-utils.c\
        ../CPU/inst.c\
        ../CPU/mem.c\
        ../CPU/run.c\
        ../CPU/spim-utils.c\
        ../CPU/string-stream.c\
        ../CPU/sym-tbl.c\
        ../CPU/syscall.c\
        y_tab.c\
        lex_yy.c\
        spim_support.c

HEADERS  += spimview.h\
	texttextedit.h

FORMS    += spimview.ui\
	savelogfile.ui\
	printwindows.ui\
        runparams.ui

INCLUDEPATH = ../CPU ../spim

QMAKE_CFLAGS_DEBUG	 += -TP
