/* SPIM S20 MIPS simulator.
   Data structures for symbolic addresses.

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


/* $Header: /Software/SPIM/src/sym-tbl.h 9     2/23/04 4:42a Larus $
*/


typedef struct lab_use
{
  instruction *inst;		/* NULL => Data, not code */
  mem_addr addr;
  struct lab_use *next;
} label_use;


/* Symbol table information on a label. */

typedef struct lab
{
  char *name;			/* Name of label */
  long addr;			/* Address of label or 0 if not yet defined */
  unsigned global_flag : 1;	/* Non-zero => declared global */
  unsigned gp_flag : 1;		/* Non-zero => referenced off gp */
  unsigned const_flag : 1;	/* Non-zero => constant value (in addr) */
  struct lab *next;		/* Hash table link */
  struct lab *next_local;	/* Link in list of local labels */
  label_use *uses;		/* List of instructions that reference */
} label;			/* label that has not yet been defined */


#define SYMBOL_IS_DEFINED(SYM) ((SYM)->addr != 0)



/* Exported functions: */

mem_addr find_symbol_address (char *symbol);
void flush_local_labels (int issue_undef_warnings);
void initialize_symbol_table ();
label *label_is_defined (char *name);
label *lookup_label (char *name);
label *make_label_global (char *name);
void print_symbols ();
void print_undefined_symbols ();
label *record_label (char *name, mem_addr address, int resolve_uses);
void record_data_uses_symbol (mem_addr location, label *sym);
void record_inst_uses_symbol (instruction *inst, label *sym);
char *undefined_symbol_string ();
void resolve_a_label (label *sym, instruction *inst);
void resolve_label_uses (label *sym);
