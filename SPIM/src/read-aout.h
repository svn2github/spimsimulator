/* SPIM S20 MIPS simulator.
   Interface to code to read a MIPS a.out file.

   Copyright (C) 1990-1994 by James Larus (larus@cs.wisc.edu).
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
   PURPOSE. */


/* $Header: /u/l/a/larus/Software/SPIM/RCS/read-aout.h,v 1.6 1997/07/09 17:20:24 larus Exp $
*/


/* Exported functions: */

#ifdef __STDC__
int read_aout_file (char *file_name);
#else
int read_aout_file ();
#endif


/* Exported Variables: */

extern int program_break;	/* Last address in data segment (edata) */
