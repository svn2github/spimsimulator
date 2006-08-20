/* SPIM S20 MIPS simulator.
   Misc. routines for SPIM.

   Copyright (C) 1990-2004 by James Larus (larus@cs.wisc.edu).
   ALL RIGHTS RESERVED.
   Changes for DOS and Windows versions by David A. Carley (dac@cs.wisc.edu)

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


/* $Header: /Software/SPIM/src/spim-utils.c 28    1/02/05 7:59p Larus $
*/


#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>

#include "spim.h"
#include "string-stream.h"
#include "spim-utils.h"
#include "inst.h"
#include "data.h"
#include "reg.h"
#include "mem.h"
#include "scanner.h"
#include "parser.h"
#include "y.tab.h"
#include "run.h"
#include "sym-tbl.h"


/* Internal functions: */

static mem_addr copy_int_to_stack (int n);
static mem_addr copy_str_to_stack (char *s);
static void delete_all_breakpoints ();


int exception_occurred;

mem_addr program_starting_address = 0;

int initial_text_size = TEXT_SIZE;

int initial_data_size = DATA_SIZE;

mem_addr initial_data_limit = DATA_LIMIT;

int initial_stack_size = STACK_SIZE;

mem_addr initial_stack_limit = STACK_LIMIT;

int initial_k_text_size = K_TEXT_SIZE;

int initial_k_data_size = K_DATA_SIZE;

mem_addr initial_k_data_limit = K_DATA_LIMIT;



/* Initialize or reinitialize the state of the machine. */

void
initialize_world (char* exception_file_names)
{
  /* Allocate the floating point registers */
  if (FGR == NULL)
    FPR = (double *) xmalloc (FPR_LENGTH * sizeof (double));
  /* Allocate the memory */
  make_memory (initial_text_size,
	       initial_data_size, initial_data_limit,
	       initial_stack_size, initial_stack_limit,
	       initial_k_text_size,
	       initial_k_data_size, initial_k_data_limit);
  initialize_registers ();
  program_starting_address = 0;
  initialize_inst_tables ();
  initialize_symbol_table ();
  k_text_begins_at_point (K_TEXT_BOT);
  k_data_begins_at_point (K_DATA_BOT);
  data_begins_at_point (DATA_BOT);
  text_begins_at_point (TEXT_BOT);

  if (exception_file_names != NULL)
    {
      int old_bare = bare_machine;
      int old_accept = accept_pseudo_insts;
      char *filename;
      char *files;

      /* Save machine state */
      bare_machine = 0;	       /* Exception handler uses extended machine */
      accept_pseudo_insts = 1;

      /* strtok modifies the string, so we must back up the string prior to use. */
      if ((files = strdup (exception_file_names)) == NULL)
         fatal_error ("Insufficient memory to complete.\n");

      for (filename = strtok (files, ";"); filename != NULL; filename = strtok (NULL, ";"))
         {
            if (read_assembly_file (filename))
               fatal_error ("Cannot read exception handler: %s\n", filename);

            write_output (message_out, "Loaded: %s\n", filename);
         }

      free (files);

      /* Restore machine state */
      bare_machine = old_bare;
      accept_pseudo_insts = old_accept;

      if (!bare_machine)
      {
	(void)make_label_global ("main"); /* In case .globl main forgotten */
	(void)record_label ("main", 0, 0);
      }
    }
  initialize_scanner (stdin);
  delete_all_breakpoints ();
}


void
write_startup_message ()
{
  write_output (message_out, "SPIM %s\n", SPIM_VERSION);
  write_output (message_out,
		"Copyright 1990-2004 by James R. Larus (larus@cs.wisc.edu).\n");
  write_output (message_out, "All Rights Reserved.\n");
#ifdef WIN32
  write_output (message_out, "DOS and Windows ports by David A. Carley (dac@cs.wisc.edu).\n");
  write_output (message_out, "Copyright 1997 by Morgan Kaufmann Publishers, Inc.\n");
#endif
  write_output (message_out, "See the file README for a full copyright notice.\n");
}



void
initialize_registers ()
{
  memclr (FPR, FPR_LENGTH * sizeof (double));
  FGR = (float *) FPR;
  FWR = (int *) FPR;

  memclr (R, R_LENGTH * sizeof (reg_word));
  R[REG_SP] = STACK_TOP - BYTES_PER_WORD - 4096; /* Initialize $sp */
  HI = LO = 0;
  PC = 0;

  CP0_BadVAddr = 0;
  CP0_Count = 0;
  CP0_Compare = 0;
  CP0_Status = (CP0_Status_CU & 0x30000000) | CP0_Status_IM | CP0_Status_UM;
  CP0_Cause = 0;
  CP0_EPC = 0;
#ifdef BIGENDIAN
  CP0_Config =  CP0_Config_BE;
#else
  CP0_Config = 0;
#endif

  FIR = FIR_W | FIR_D | FIR_S;	/* Word, double, & single implemented */
  FCSR = 0x0;
  FCCR = 0x0;
  FEXR = 0x0;
  FENR = 0x0;
}


/* Read file NAME, which should contain assembly code. Return zero if
   successful and non-zero otherwise. */

int
read_assembly_file (char *name)
{
  FILE *file = fopen (name, "rt");

  if (file == NULL)
    {
      error ("Cannot open file: `%s'\n", name);
      return (1);
    }
  else
    {
      initialize_scanner (file);
      initialize_parser (name);

      while (!yyparse ()) ;

      fclose (file);
      flush_local_labels (!parse_error_occurred);
      end_of_assembly_file ();
      return (0);
    }
}


mem_addr
starting_address ()
{
  if (PC == 0)
    {
      if (program_starting_address != 0)
	return (program_starting_address);
      else
	return (program_starting_address
		= find_symbol_address (DEFAULT_RUN_LOCATION));
    }
  else
    return (PC);
}


/* Initialize the SPIM stack with ARGC, ARGV, and ENVP data. */

#ifdef _MSC_VER
#define environ	_environ
#endif

void
initialize_run_stack (int argc, char **argv)
{
  char **p;
  extern char **environ;
  int i, j = 0, env_j;
  mem_addr addrs[10000];

  /* Put strings on stack: */

  /* env: */
  for (p = environ; *p != NULL; p++)
    addrs[j++] = copy_str_to_stack (*p);
  env_j = j;

  /* argv; */
  for (i = 0; i < argc; i++)
    addrs[j++] = copy_str_to_stack (argv[i]);

  R[REG_SP] = STACK_TOP - BYTES_PER_WORD - 4096; /* Initialize $sp */
  R[REG_SP] = R[REG_SP] & ~3;	/* Round down to nearest word */
  R[REG_SP] -= BYTES_PER_WORD;	/* First free word on stack */

  R[REG_SP] = R[REG_SP] & ~7;	/* Double-word align stack-pointer*/
  if ((j % 2) != 0)		/* Odd number of arguments */
    {
      R[REG_SP] -= BYTES_PER_WORD; /* Ensure stack ends up double-word aligned */
    }

  /* Build vectors on stack: */

  /* env: */
  (void)copy_int_to_stack (0);	/* Null-terminate vector */
  for (i = env_j - 1; i >= 0; i--)
    R[REG_A2] = copy_int_to_stack (addrs[i]);

  /* argv: */
  (void)copy_int_to_stack (0);	/* Null-terminate vector */
  for (i = j - 1; i >= env_j; i--)
    R[REG_A1] = copy_int_to_stack (addrs[i]);

  /* argc: */
  R[REG_A0] = argc;
  set_mem_word (R[REG_SP], argc); /* Leave argc on stack */
}


static mem_addr
copy_str_to_stack (char *s)
{
  int i = strlen (s);
  while (i >= 0)
    {
      set_mem_byte (R[REG_SP], s[i]);
      R[REG_SP] -= 1;
      i -= 1;
    }
  return ((mem_addr) R[REG_SP] + 1); /* Leaves stack pointer byte-aligned!! */
}


static mem_addr
copy_int_to_stack (int n)
{
  set_mem_word (R[REG_SP], n);
  R[REG_SP] -= BYTES_PER_WORD;
  return ((mem_addr) R[REG_SP] + BYTES_PER_WORD);
}


/* Run a program starting at PC for N steps and display each
   instruction before executing if FLAG is non-zero.  If CONTINUE is
   non-zero, then step through a breakpoint.  Return non-zero if
   breakpoint is encountered. */

int
run_program (mem_addr pc, int steps, int display, int cont_bkpt)
{
  if (cont_bkpt && inst_is_breakpoint (pc))
    {
      mem_addr addr = PC == 0 ? pc : PC;

      delete_breakpoint (addr);
      exception_occurred = 0;
      run_spim (addr, 1, display);
      add_breakpoint (addr);
      steps -= 1;
      pc = PC;
    }

  exception_occurred = 0;
  if (!run_spim (pc, steps, display))
      /* Can't restart program */
      PC = 0;
  if (exception_occurred && CP0_ExCode == ExcCode_Bp)
  {
      /* Turn off EXL bit, so subsequent interrupts set EPC since the break is
      handled by SPIM code, not MIPS code. */
      CP0_Status &= ~CP0_Status_EXL;
      return (1);
  }
  else
    return (0);
}


/* Record of where a breakpoint was placed and the instruction previously
   in memory. */

typedef struct bkptrec
{
  mem_addr addr;
  instruction *inst;
  struct bkptrec *next;
} bkpt;


static bkpt *bkpts = NULL;


/* Set a breakpoint at memory location ADDR. */

void
add_breakpoint (mem_addr addr)
{
  bkpt *rec = (bkpt *) xmalloc (sizeof (bkpt));

  rec->next = bkpts;
  rec->addr = addr;

  if ((rec->inst = set_breakpoint (addr)) != NULL)
    bkpts = rec;
  else
    {
      if (exception_occurred)
	error ("Cannot put a breakpoint at address 0x%08x\n", addr);
      else
	error ("No instruction to breakpoint at address 0x%08x\n", addr);
      free (rec);
    }
}


/* Delete all breakpoints at memory location ADDR. */

void
delete_breakpoint (mem_addr addr)
{
  bkpt *p, *b;
  int deleted_one = 0;

  for (p = NULL, b = bkpts; b != NULL; )
    if (b->addr == addr)
      {
	bkpt *n;

	set_mem_inst (addr, b->inst);
	if (p == NULL)
	  bkpts = b->next;
	else
	  p->next = b->next;
	n = b->next;
	free (b);
	b = n;
	deleted_one = 1;
      }
    else
      p = b, b = b->next;
  if (!deleted_one)
    error ("No breakpoint to delete at 0x%08x\n", addr);
}


static void
delete_all_breakpoints ()
{
  bkpt *b, *n;

  for (b = bkpts, n = NULL; b != NULL; b = n)
    {
      n = b->next;
      free (b);
    }
  bkpts = NULL;
}


/* List all breakpoints. */

void
list_breakpoints ()
{
  bkpt *b;

  if (bkpts)
    for (b = bkpts;  b != NULL; b = b->next)
      write_output (message_out, "Breakpoint at 0x%08x\n", b->addr);
  else
    write_output (message_out, "No breakpoints set\n");
}



/* Utility routines */


/* Return the entry in the linear TABLE of length LENGTH with key STRING.
   TABLE must be sorted on the key field.
   Return NULL if no such entry exists. */

name_val_val *
map_string_to_name_val_val (name_val_val tbl[], int tbl_len, char *id)
{
  int low = 0;
  int hi = tbl_len - 1;

  while (low <= hi)
    {
      int mid = (low + hi) / 2;
      char *idp = id, *np = tbl[mid].name;

      while (*idp == *np && *idp != '\0') {idp ++; np ++;}

      if (*np == '\0' && *idp == '\0') /* End of both strings */
	return (& tbl[mid]);
      else if (*idp > *np)
	low = mid + 1;
      else
	hi = mid - 1;
    }

  return NULL;
}


/* Return the entry in the linear TABLE of length LENGTH with VALUE1 field NUM.
   TABLE must be sorted on the VALUE1 field.
   Return NULL if no such entry exists. */

name_val_val *
map_int_to_name_val_val (name_val_val tbl[], int tbl_len, int num)
{
  int low = 0;
  int hi = tbl_len - 1;

  while (low <= hi)
    {
      int mid = (low + hi) / 2;

      if (tbl[mid].value1 == num)
	return (&tbl[mid]);
      else if (num > tbl[mid].value1)
	low = mid + 1;
      else
	hi = mid - 1;
    }

  return NULL;
}


#ifdef NEED_VSPRINTF
char *
vsprintf (str, fmt, args)
     char *str,*fmt;
     va_list *args;
{
  FILE _strbuf;

  _strbuf._flag = _IOWRT+_IOSTRG;
  _strbuf._ptr = str;
  _strbuf._cnt = 32767;
  _doprnt(fmt, args, &_strbuf);
  putc('\0', &_strbuf);
  return(str);
}
#endif


#ifdef NEED_STRTOL
unsigned long
strtol (const char* str, const char** eptr, int base)
{
  long result;

  if (base != 0 && base != 16)
    fatal_error ("SPIM's strtol only works for base 16 (not base %d)\n", base);
  if (*str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X'))
    {
      str += 2;
      sscanf (str, "%lx", &result);
    }
  else if (base == 16)
    {
      sscanf (str, "%lx", &result);
    }
  else
    {
      sscanf (str, "%ld", &result);
    }
  return (result);
}
#endif

#ifdef NEED_STRTOUL
unsigned long
strtoul (const char* str, char** eptr, int base)
{
  unsigned long result;

  if (base != 0 && base != 16)
    fatal_error ("SPIM's strtoul only works for base 16 (not base %d)\n", base);
  if (*str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X'))
    {
      str += 2;
      sscanf (str, "%lx", &result);
    }
  else if (base == 16)
    {
      sscanf (str, "%lx", &result);
    }
  else
    {
      sscanf (str, "%ld", &result);
    }
  return (result);
}
#endif


char *
str_copy (char *str)
{
  return (strcpy (xmalloc (strlen (str) + 1), str));
}


void *
xmalloc (int size)
{
  void *x = (void *) malloc (size);

  if (x == 0)
    fatal_error ("Out of memory at request for %d bytes.\n");
  return (x);
}


/* Allocate a zero'ed block of storage. */

void *
zmalloc (int size)
{
  void *z = (void *) malloc (size);

  if (z == 0)
    fatal_error ("Out of memory at request for %d bytes.\n");

  memclr (z, size);
  return (z);
}
