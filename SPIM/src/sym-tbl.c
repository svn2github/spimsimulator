/* SPIM S20 MIPS simulator.
   Code to maintain symbol table to resolve symbolic labels.

   Copyright (C) 1990-1998 by James Larus (larus@cs.wisc.edu).
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


/* $Header: /u/l/a/larus/Software/SPIM/RCS/sym-tbl.c,v 3.20 1997/07/21 18:11:21 larus Exp $
*/



#include "spim.h"
#include "spim-utils.h"
#include "inst.h"
#include "mem.h"
#include "data.h"
#include "parser.h"
#include "sym-tbl.h"
#include "y.tab.h"


/* Local functions: */

#ifdef __STDC__
static void get_hash (char *name, int *slot_no, label **entry);
static void resolve_a_label_sub (label *sym, instruction *inst, mem_addr pc);
#else
static void get_hash ();
static void resolve_a_label_sub ();
#endif



/* Keep track of the memory location that a label represents.  If we
   see a reference to a label that is not yet defined, then record the
   reference so that we can patch up the instruction when the label is
   defined.

   At the end of a file, we flush the hash table of all non-global
   labels so they can't be seen in other files.	 */


static label *local_labels = NULL; /* Labels local to current file. */


#define HASHBITS 30

#define LABEL_HASH_TABLE_SIZE 8191


/* Map from name of a label to a label structure. */

static label *label_hash_table [LABEL_HASH_TABLE_SIZE];


/* Initialize the symbol table by removing and freeing old entries. */

#ifdef __STDC__
void
initialize_symbol_table (void)
#else
void
initialize_symbol_table ()
#endif
{
  int i;
  
  for (i = 0; i < LABEL_HASH_TABLE_SIZE; i ++)
  {
    label *x, *n;
    
    for (x = label_hash_table [i]; x != NULL; x = n)
    {
      free (x->name);
      n = x->next;
      free (x);
    }
    label_hash_table [i] = NULL;
  }
  
  local_labels = NULL;
}



/* Lookup for a label with the given NAME.  Set the SLOT_NO to be the hash
   table bucket that contains (or would contain) the label's record.  If the
   record is already in the table, set ENTRY to point to it.  Otherwise,
   set ENTRY to be NULL. */

#ifdef __STDC__
static void
get_hash (char *name, int *slot_no, label **entry)
#else
static void
get_hash (name, slot_no, entry)
     char *name;
     int *slot_no;
     label **entry;
#endif
{
  int hi;
  int i;
  label *lab;
  int len;

  /* Compute length of name in len.  */
  for (len = 0; name[len]; len++);

  /* Compute hash code */
  hi = len;
  for (i = 0; i < len; i++)
    hi = ((hi * 613) + (unsigned)(name[i]));

  hi &= (1 << HASHBITS) - 1;
  hi %= LABEL_HASH_TABLE_SIZE;

  *slot_no = hi;
  /* Search table for entry */
  for (lab = label_hash_table [hi]; lab; lab = lab->next)
    if (streq (lab->name, name))
      {
	*entry = lab;		/* <-- return if found */
	return;
      }
  *entry = NULL;
}


/* Lookup label with NAME.  Either return its symbol table entry or NULL
   if it is not in the table. */

#ifdef __STDC__
label *
label_is_defined (char *name)
#else
label *
label_is_defined (name)
     char *name;
#endif
{
  int hi;
  label *entry;

  get_hash (name, &hi, &entry);

  return (entry);
}


/* Return a label with a given NAME.  If an label with that name has
   previously been looked-up, the same node is returned this time.  */

#ifdef __STDC__
label *
lookup_label (char *name)
#else
label *
lookup_label (name)
     char *name;
#endif
{
  int hi;
  label *entry, *lab;

  get_hash (name, &hi, &entry);

  if (entry != NULL)
    return (entry);

  /* Not found, create one, add to chain */
  lab = (label *) xmalloc (sizeof (label));
  lab->name = str_copy (name);
  lab->addr = 0;
  lab->global_flag = 0;
  lab->const_flag = 0;
  lab->gp_flag = 0;
  lab->uses = NULL;

  lab->next = label_hash_table [hi];
  label_hash_table [hi] = lab;
  return lab;			/* <-- return if created */
}


/* Record that the label named NAME refers to ADDRESS.	If RESOLVE_USES is
   true, resolve all references to it.  Return the label structure. */

#ifdef __STDC__
label *
record_label (char *name, mem_addr address, int resolve_uses)
#else
label *
record_label (name, address, resolve_uses)
     char *name;
     mem_addr address;
     int resolve_uses;
#endif
{
  label *l = lookup_label (name);

  if (!l->gp_flag)
    {
      if (l->addr != 0)
	{
	  yyerror ("Label is defined for the second time");
	  return (l);
	}
      l->addr = address;
    }

  if (resolve_uses)
    {
      resolve_label_uses (l);
    }

  if (!l->global_flag)
    {
      l->next_local = local_labels;
      local_labels = l;
    }
  return (l);
}


/* Make the label named NAME global.  Return its symbol. */

#ifdef __STDC__
label *
make_label_global (char *name)
#else
label *
make_label_global (name)
     char *name;
#endif
{
  label *l = lookup_label (name);

  l->global_flag = 1;
  return (l);
}


/* Record that an INSTRUCTION uses the as-yet undefined SYMBOL. */

#ifdef __STDC__
void
record_inst_uses_symbol (instruction *inst, label *sym)
#else
void
record_inst_uses_symbol (inst, sym)
     instruction *inst;
     label *sym;
#endif
{
  label_use *u = (label_use *) xmalloc (sizeof (label_use));

  if (data_dir)			/* Want to free up original instruction */
    {
      u->inst = copy_inst (inst);
      u->addr = current_data_pc ();
    }
  else
    {
      u->inst = inst;
      u->addr = current_text_pc ();
    }
  u->next = sym->uses;
  sym->uses = u;
}


/* Record that a memory LOCATION uses the as-yet undefined SYMBOL. */

#ifdef __STDC__
void
record_data_uses_symbol (mem_addr location, label *sym)
#else
void
record_data_uses_symbol (location, sym)
     mem_addr location;
     label *sym;
#endif
{
  label_use *u = (label_use *) xmalloc (sizeof (label_use));

  u->inst = NULL;
  u->addr = location;
  u->next = sym->uses;
  sym->uses = u;
}


/* Given a newly-defined LABEL, resolve the previously encountered
   instructions and data locations that refer to the label. */

#ifdef __STDC__
void
resolve_label_uses (label *sym)
#else
void
resolve_label_uses (sym)
     label *sym;
#endif
{
  label_use *use;
  label_use *next_use;

  for (use = sym->uses; use != NULL; use = next_use)
    {
      resolve_a_label_sub (sym, use->inst, use->addr);
      if (use->inst != NULL && use->addr >= DATA_BOT && use->addr < stack_bot)
	{
	  SET_MEM_WORD (use->addr, inst_encode (use->inst));
	  free_inst (use->inst);
	}
      next_use = use->next;
      free (use);
    }
  sym->uses = NULL;
}


/* Resolve the newly-defined label in INSTRUCTION. */

#ifdef __STDC__
void
resolve_a_label (label *sym, instruction *inst)
#else
void
resolve_a_label (sym, inst)
     label *sym;
     instruction *inst;
#endif
{
  resolve_a_label_sub (sym,
		       inst,
		       (data_dir ? current_data_pc () : current_text_pc ()));
}


#ifdef __STDC__
static void
resolve_a_label_sub (label *sym, instruction *inst, mem_addr pc)
#else
static void
resolve_a_label_sub (sym, inst, pc)
  label *sym;
   instruction *inst;
   mem_addr pc;
#endif
{
  if (inst == NULL)
    {
      /* Memory data: */
      SET_MEM_WORD (pc, sym->addr);
    }
  else
    {
      /* Instruction: */
      if (EXPR (inst)->pc_relative)
	EXPR (inst)->offset = 0 - pc; /* Instruction may have moved */

      if (EXPR (inst)->symbol == NULL
	  || SYMBOL_IS_DEFINED (EXPR (inst)->symbol))
	{
	  int32 value;
	  int32 mask;

	  if (opcode_is_branch (OPCODE (inst)))
	    {
	      int val;

	      /* Drop low two bits since instructions are on word
		 boundaries. */
	      val = eval_imm_expr (EXPR (inst));
	      val >>= 2;	/* Seperate to force sign-extension */

	      if (bare_machine)	/* Delayed branch */
		val -= 1;

	      value = val;
	      mask = 0xffff;
	    }
	  else if (opcode_is_jump (OPCODE (inst)))
	    {
	      /* Drop low two bits since instructions are on word
		 boundaries. */
	      value = eval_imm_expr (EXPR (inst)) >> 2;
	      mask = 0x03fffffff;
	    }
	  else if (opcode_is_load_store (OPCODE (inst)))
	    {
	      /* Label's location is an address */
	      value = eval_imm_expr (EXPR (inst));
	      mask = 0xffff;

	      /* LW/SW sign extends offset.  Add 1 to high 16 bits
	         to compensate. */
	      if (value & 0x8000)
	      {
		instruction* prev_inst;
		READ_MEM_INST (prev_inst, pc - BYTES_PER_WORD);
		if (OPCODE (prev_inst) == Y_LUI_OP
		    && EXPR (inst)->symbol == EXPR (prev_inst)->symbol)
		{
		  if (IMM (prev_inst) == 0)
		  {
		    /* Have not yet resolved label */
		    EXPR (prev_inst)->offset += 0x10000;
		  }
		  else
		  {
		    /* Already resolved label */
		    IMM (prev_inst) += 1;
		  }
		}
	      }
	    }
	  else
	    {
	      /* Label's location is a value */
	      value = eval_imm_expr (EXPR (inst));
	      mask = 0xffff;
	    }

	  if ((value & ~mask) != 0 && (value & ~mask) != 0xffff0000)
	    {
	      error ("Immediate value is too large for field: ");
	      print_inst (pc);
	    }
	  if (opcode_is_jump (OPCODE (inst)))
	    SET_TARGET (inst, value); /* Don't mask so it is sign-extended */
	  else
	    SET_IMM (inst, value);	/* Ditto */
	  ENCODING (inst) = inst_encode (inst);
	}
      else
	error ("Resolving undefined symbol: %s\n",
	       (EXPR (inst)->symbol == NULL) ? "" : EXPR (inst)->symbol->name);
    }
}


/* Remove all local (non-global) label from the table. */

#ifdef __STDC__
void
flush_local_labels (int issue_undef_warnings)
#else
void
flush_local_labels (issue_undef_warnings)
    int issue_undef_warnings;
#endif
{
  label *l;

  for (l = local_labels; l != NULL; l = l->next_local)
    {
      int hi;
      label *entry, *lab, *p;

      get_hash (l->name, &hi, &entry);

      for (lab = label_hash_table [hi], p = NULL;
	   lab;
	   p = lab, lab = lab->next)
	if (lab == entry)
	  {
	    if (p == NULL)
	      label_hash_table [hi] = lab->next;
	    else
	      p->next = lab->next;
	    if (issue_undef_warnings && entry->addr == 0 && !entry->const_flag)
	      error ("Warning: local symbol %s was not defined\n",
		     entry->name);
	    /* Can't free label since IMM_EXPR's still reference it */
	    break;
	  }
    }
  local_labels = NULL;
}


/* Return the address of SYMBOL or 0 if it is undefined. */

#ifdef __STDC__
mem_addr
find_symbol_address (char *symbol)
#else
mem_addr
find_symbol_address (symbol)
     char *symbol;
#endif
{
  label *l = lookup_label (symbol);

  if (l == NULL || l->addr == 0)
    return 0;
  else
    return (l->addr);
}


/* Print all symbols in the table. */

#ifdef __STDC__
void
print_symbols (void)
#else
void
print_symbols ()
#endif
{
  int i;
  label *l;

  for (i = 0; i < LABEL_HASH_TABLE_SIZE; i ++)
    for (l = label_hash_table [i]; l != NULL; l = l->next)
      write_output (message_out, "%s%s at 0x%08x\n",
		    l->global_flag ? "g\t" : "\t", l->name, l->addr);
}


/* Print all undefined symbols in the table. */

#ifdef __STDC__
void
print_undefined_symbols (void)
#else
void
print_undefined_symbols ()
#endif
{
  int i;
  label *l;

  for (i = 0; i < LABEL_HASH_TABLE_SIZE; i ++)
    for (l = label_hash_table [i]; l != NULL; l = l->next)
      if (l->addr == 0)
	write_output (message_out, "%s\n", l->name);
}


/* Return a string containing the names of all undefined symbols in the
   table, seperated by a newline character.  Return NULL if no symbols
   are undefined. */

#ifdef __STDC__
char *
undefined_symbol_string (void)
#else
char *
undefined_symbol_string ()
#endif
{
  int buffer_length = 128;
  int string_length = 0;
  char *buffer = malloc(buffer_length);

  int i;
  label *l;
  
  for (i = 0; i < LABEL_HASH_TABLE_SIZE; i ++)
    for (l = label_hash_table[i]; l != NULL; l = l->next)
      if (l->addr == 0)
      {
	int name_length = strlen(l->name);
	int after_length = string_length + name_length + 2;
	if (buffer_length < after_length)
	{
	  buffer_length = MAX (2 * buffer_length, 2 * after_length);
	  buffer = realloc (buffer, buffer_length);
	}
	memcpy (buffer + string_length, l->name, name_length);
	string_length += name_length;
	buffer[string_length] = '\n';
	string_length += 1;
	buffer[string_length + 1] = '\0'; /* After end of string */
      }

  if (string_length != 0)
    return (buffer);
  else
  {
    free (buffer);
    return (NULL);
  };
}
