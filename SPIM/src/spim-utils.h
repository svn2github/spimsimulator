/* SPIM S20 MIPS simulator.
   Interface to misc. routines for SPIM.

   Copyright (C) 1990-1997 by James Larus (larus@cs.wisc.edu).
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


/* $Header: /u/l/a/larus/Software/SPIM/RCS/spim-utils.h,v 1.7 1997/07/09 18:05:05 larus Exp $
*/


/* Exported functions: */

#ifdef __STDC__
void add_breakpoint (mem_addr addr);
void delete_breakpoint (mem_addr addr);
void fatal_error (char *fmt, ...);
void initialize_registers (void);
void initialize_run_stack (int argc, char **argv);
void initialize_world (char* trap_file);
void list_breakpoints (void);
inst_info *map_int_to_inst_info (inst_info tbl[], int tbl_len, int num);
inst_info *map_string_to_inst_info (inst_info tbl[], int tbl_len, char *id);
int read_assembly_file (char *name);
int run_program (mem_addr pc, int steps, int display, int cont_bkpt);
mem_addr starting_address (void);
char *str_copy (char *str);
void write_startup_message (void);
void *xmalloc (int);
void *zmalloc (int);
#else
void add_breakpoint ();
void end_of_assembly_file ();
void delete_breakpoint ();
void fatal_error ();
void initialize_registers ();
void initialize_run_stack ();
void initialize_world ();
void list_breakpoints ();
inst_info *map_int_to_inst_info ();
inst_info *map_string_to_inst_info ();
int read_assembly_file ();
int run_program ();
mem_addr starting_address ();
char *str_copy ();
void write_startup_message ();
char *xmalloc ();
char *zmalloc ();
#endif
