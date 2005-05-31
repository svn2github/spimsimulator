/* SPIM S20 MIPS simulator.
   Execute SPIM syscalls, both in simulator and bare mode.

   Copyright (C) 1990-2000 by James Larus (larus@cs.wisc.edu).
   ALL RIGHTS RESERVED.
   Improved by Emin Gun Sirer.

   SPIM is distributed under the following conditions:

     You may make copies of SPIM for your own use and modify those copies.

     All copies of SPIM must retain my name and copyright notice.
     ALL RIGHTS RESERVED.

     You may not sell SPIM or distributed SPIM in conjunction with a
     commerical product or service without the expressed written consent of
     James Larus.

   THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
   IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
   PURPOSE. */


/* $Header: /Software/SPIM/SPIM/Old/spim-6.5/mips-syscall.h 1     1/02/05 8:03p Larus $
*/


/* Exported functions. */

#ifdef __STDC__
int do_syscall (void);
void handle_exception (void);
void initialize_prog_fds (void);
void kill_prog_fds (void);
void print_syscall_usage (void);
#else
int do_syscall ();
void handle_exception ();
void initialize_prog_fds ();
void kill_prog_fds ();
void print_syscall_usage ();
#endif

