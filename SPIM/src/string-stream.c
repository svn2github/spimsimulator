/* SPIM S20 MIPS simulator.
  Append-only output stream convertable to a string.

  Copyright (C) 2004 by James Larus (larus@cs.wisc.edu).
  ALL RIGHTS RESERVED.

  SPIM is distributed under the following conditions:

  You may make copies of SPIM for your own use and modify those copies.

  All copies of SPIM must retain my name and copyright notice.

  You may not sell SPIM or distributed SPIM in conjunction with a
  commerical product or service without the expressed written consent of
  James Larus.

  THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
  IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
  PURPOSE.

  $Header: /Software/SPIM/src/string-stream.c 1     3/21/04 2:04p Larus $
*/

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#include "spim.h"
#include "string-stream.h"


#ifndef SS_BUF_LENGTH
/* Initialize length of buffer */
#define SS_BUF_LENGTH 256
#endif


static void
ss_init (str_stream* ss)
{
  ss->buf = (char *) malloc (SS_BUF_LENGTH);
  ss->max_length = SS_BUF_LENGTH;
  ss->empty_pos = 0;
  ss->initialized = 1;
}


void
ss_clear (str_stream* ss)
{
  if (0 == ss->initialized) ss_init(ss);

  ss->empty_pos = 0;
}


void
ss_erase (str_stream* ss, int n)
{
  if (0 == ss->initialized) ss_init(ss);

  ss->empty_pos -= n;
  if (ss->empty_pos <0) ss->empty_pos = 0;
}


int
ss_length (str_stream* ss)
{
  if (0 == ss->initialized) ss_init(ss);

  return ss->empty_pos;
}


char*
ss_to_string (str_stream* ss)
{
  if (0 == ss->initialized) ss_init(ss);

  ss->buf[ss->empty_pos] = '\0'; /* Null terminate string */
  return ss->buf;
}


#ifdef WIN32
/* Named differently on Windows */
#define vsnprintf _vsnprintf
#endif

void
ss_printf (str_stream* ss, char* fmt, ...)
{
  int free_space;
  int n;
  va_list args;

  va_start (args, fmt);

  if (0 == ss->initialized) ss_init(ss);

  free_space = ss->max_length - ss->empty_pos;
  while ((n = vsnprintf (ss->buf + ss->empty_pos, free_space, fmt, args)) < 0)
    {
      /* Not enough room to store output: double buffer size and try again */
      ss->max_length = 2 * ss->max_length;
      ss->buf = (char *) realloc (ss->buf, (size_t)ss->max_length);
      free_space = ss->max_length - ss->empty_pos;
      if (NULL == ss->buf)
	fatal_error ("realloc failed\n");
    }
  ss->empty_pos += n;

  ss->buf[ss->empty_pos] = '\0'; /* Null terminate string (for debugging)*/
  va_end (args);
}
