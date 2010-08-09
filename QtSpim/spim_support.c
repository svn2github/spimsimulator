// SPIM S20 MIPS simulator.
// Definitions for the SPIM S20.
//
// Copyright (c) 1990-2010, James R. Larus.
// Changes for DOS and Windows versions by David A. Carley (dac@cs.wisc.edu)
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
// Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
//
// Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation and/or
// other materials provided with the distribution.
//
// Neither the name of the James R. Larus nor the names of its contributors may be
// used to endorse or promote products derived from this software without specific
// prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
// GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//


#include <stdarg.h>

#include "spimview.h"
#include "ui_spimview.h"


// SPIM globals
//
int bare_machine;              /* Non-zero => simulate bare machine */
int accept_pseudo_insts;       /* Non-Zero => parse pseudo instructions  */
int delayed_branches;          /* Non-zero => simulate delayed branches */
int delayed_loads;             /* Non-zero => simulate delayed loads */
int quiet;                     /* Non-zero => no warning messages */
int source_file;               /* Non-zero => program is source, not binary */
char* exception_file_name = 0; /* The path from which to load the exception handler, if desired */
port message_out, console_out;
int mapped_io;                  /* Non-zero => activate memory-mapped IO */
int spim_return_value;          /* Value returned when spim exits */




int console_input_available()
{
  return 0;
}


void control_c_seen(int arg)
{
}


void error(char *fmt, ...)
{
    va_list args;
    va_start (args, fmt);

    char buf[1000];
    qvsnprintf(buf, 1000, fmt, args);
    va_end(args);

    Window->Error(buf, 0);
}


void fatal_error(char *fmt, ...)
{
    va_list args;
    va_start (args, fmt);

    char buf[1000];
    qvsnprintf(buf, 1000, fmt, args);
    va_end(args);

    Window->Error(buf, 1);
}


char get_console_char()
{
  return 'x';
}


void put_console_char(char c)
{
}


void read_input(char *str, int str_size)
{
}


void run_error (char *fmt, ...)
{
}


void write_output (port fp, char *fmt, ...)
{
}
