/* SPIM S20 MIPS simulator.
   Interface to misc. routines for SPIM.

   Copyright (C) 1990-2004 by James Larus (larus@cs.wisc.edu).
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


/* $Header: /Software/SPIM/src/spim-utils.h 10    3/21/04 2:05p Larus $
*/


/* Triple containing a string and two integers.	 Used in tables
   mapping from a name to values. */

typedef struct
{
  char *name;
  int value1;
  int value2;
} name_val_val;



/* Exported functions: */

void add_breakpoint (mem_addr addr);
void delete_breakpoint (mem_addr addr);
void format_data_segs (str_stream *ss);
void format_insts (str_stream *ss, mem_addr from, mem_addr to);
void format_mem (str_stream *ss, mem_addr from, mem_addr to);
void format_registers (str_stream *ss, int print_gpr_hex, int print_fpr_hex);
void initialize_registers ();
void initialize_run_stack (int argc, char **argv);
void initialize_world (char *exception_file_names);
void list_breakpoints ();
name_val_val *map_int_to_name_val_val (name_val_val tbl[], int tbl_len, int num);
name_val_val *map_string_to_name_val_val (name_val_val tbl[], int tbl_len, char *id);
int read_assembly_file (char *name);
int run_program (mem_addr pc, int steps, int display, int cont_bkpt);
mem_addr starting_address ();
char *str_copy (char *str);
void write_startup_message ();
void *xmalloc (int);
void *zmalloc (int);
