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

  $Header: /Software/SPIM/src/string-stream.h 1     3/21/04 2:05p Larus $
*/

typedef struct str_stm
{
  char* buf;			/* Buffer containing output */
  int max_length;		/* Length of buffer */
  int empty_pos;		/* Index  of empty char in stream*/
  int initialized;		/* Stream initialized? */
} str_stream;


void ss_clear (str_stream* ss);
void ss_erase (str_stream* ss, int n);
int ss_length (str_stream* ss);
char* ss_to_string (str_stream* ss);
void ss_printf (str_stream* ss, char* fmt, ...);
