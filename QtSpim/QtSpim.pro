#  SPIM S20 MIPS simulator.
#  Qt interface for SPIM simulator.
#
#  Copyright (c) 1990-2010, James R. Larus.
#  All rights reserved.
#
#  Redistribution and use in source and binary forms, with or without modification,
#  are permitted provided that the following conditions are met:
#
#  Redistributions of source code must retain the above copyright notice,
#  this list of conditions and the following disclaimer.
#
#  Redistributions in binary form must reproduce the above copyright notice,
#  this list of conditions and the following disclaimer in the documentation and/or
#  other materials provided with the distribution.
#
#  Neither the name of the James R. Larus nor the names of its contributors may be
#  used to endorse or promote products derived from this software without specific
#  prior written permission.
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
#  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
#  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
#  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
#  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
#  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
#  GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
#  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
#  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
#  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

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


RESOURCES = windows_images.qrc


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
  QMAKE_CXXFLAGS_DEBUG	+= -x c++ -Wno-write-strings
  QMAKE_CXXFLAGS_RELEASE += -x c++ -Wno-write-strings

  # Surpress error when deleting non-existent file.
  #
  QMAKE_DEL_FILE = rm -f
}

linux-g++ {
  # Compile all files as C++
  # Surpress gcc warning about deprecated conversion from string constant to char*
  #
  QMAKE_CFLAGS_DEBUG	+= -x c++ -Wno-write-strings
  QMAKE_CFLAGS_RELEASE	+= -x c++ -Wno-write-strings
  QMAKE_CXXFLAGS_DEBUG	+= -x c++ -Wno-write-strings
  QMAKE_CXXFLAGS_RELEASE += -x c++ -Wno-write-strings

  # Surpress error when deleting non-existent file.
  #
  QMAKE_DEL_FILE = rm -f
}

