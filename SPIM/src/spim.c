/* SPIM S20 MIPS simulator.
   Terminal interface for SPIM simulator.

   Copyright (C) 1990-1997 by James Larus (larus@cs.wisc.edu).
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


/* $Header: /u/l/a/larus/Software/SPIM/src/RCS/spim.c,v 3.63 1998/01/14 20:45:06 larus Exp $
*/


#include <stdio.h>
#include <ctype.h>
#include <setjmp.h>
#include <signal.h>

#ifdef RS
/* This is problem on HP Snakes, which define RS in syscall.h */
#undef RS
#endif

#include <sys/types.h>

#ifdef _AIX
#ifndef NBBY
#define NBBY 8
#endif
#include <sys/select.h>
#endif

#ifdef DJGPP
#define USE_TERMIO
#define termio termios
#endif


#ifndef WIN32
#include <sys/time.h>

#ifdef USE_TERMIO
#ifndef DJGPP
#include <termio.h>
#endif
#include <termios.h>
#else
#include <sys/ioctl.h>
#include <sgtty.h>
#endif
#endif

#ifdef __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

#include "spim.h"
#include "spim-utils.h"
#include "inst.h"
#include "mem.h"
#include "reg.h"
#include "parser.h"
#include "sym-tbl.h"
#include "scanner.h"
#include "y.tab.h"


/* Internal functions: */

#ifdef __STDC__
static void console_to_program (void);
static void console_to_spim (void);
static void flush_to_newline (void);
static int get_opt_int (void);
static int parse_spim_command (FILE *file, int redo);
static int print_reg (int reg_no, int type_code);
static int read_assembly_command (void);
static int str_prefix (char *s1, char *s2, int min_match);
static void top_level (void);
static int read_token (void);
#else
static void console_to_program ();
static void console_to_spim ();
static void flush_to_newline ();
static int get_opt_int ();
static int parse_spim_command ();
static int print_reg ();
static int read_assembly_command ();
static int str_prefix ();
static void top_level ();
static int read_token ();
#endif


/* Exported Variables: */

/* Not local, but not export so all files don't need setjmp.h */
jmp_buf spim_top_level_env;	/* For ^C */

int bare_machine;		/* Non-Zero => simulate bare machine */
int accept_pseudo_insts;	/* Non-Zero => parse pseudo instructions  */
int quiet;			/* Non-Zero => no warning messages */
int source_file;		/* Non-Zero => program is source, not binary */
port message_out, console_out, console_in;
int mapped_io;			/* Non-zero => activate memory-mapped IO */
int pipe_out;
int cycle_level;		/* Non-zero => cycle level mode */


/* Local variables: */

static int load_trap_handler = 1; /* Non-zero => load standard trap handler */
char *trap_file = DEFAULT_TRAP_HANDLER;
static int console_state_saved;
#ifdef USE_TERMIO
static struct termio saved_console_state;
#else
static struct sgttyb saved_console_state;
#endif



#ifdef __STDC__
int
main (int argc, char **argv)
#else
int
main (argc, argv)
     int argc;
     char **argv;
#endif
{
  int i;
  int assembly_file_read = 0;
  int argv_ptr = 0;

  console_out.f = stdout;
  message_out.f = stdout;

  bare_machine = 0;
  accept_pseudo_insts = 1;
  quiet = 0;
  source_file = 0;
  cycle_level = 0;

  /* Input comes directly (not through stdio): */
  console_in.i = 0;
  mapped_io = 0;

  write_startup_message ();

  for (i = 1; i < argc; i++)
    {
#ifdef DJGPP
      /* On DOS, support "/option" as well as "-option" */
      if (argv [i][0] == '/')
	argv [i][0] = '-';
#endif

      if (streq (argv [i], "-bare"))
	bare_machine = 1, quiet = 1;
      else if (streq (argv [i], "-asm"))
	bare_machine = 0;
      else if (streq (argv [i], "-pseudo"))
	accept_pseudo_insts = 1;
      else if (streq (argv [i], "-nopseudo"))
	accept_pseudo_insts = 0;
      else if (streq (argv [i], "-trap"))
	load_trap_handler = 1;
      else if (streq (argv [i], "-notrap"))
	load_trap_handler = 0;
      else if (streq (argv [i], "-trap_file"))
	{
	  trap_file = argv[++i];
	  load_trap_handler = 1;
	}
      else if (streq (argv [i], "-quiet"))
	quiet = 1;
      else if (streq (argv [i], "-noquiet"))
	quiet = 0;
      else if (streq (argv [i], "-file"))
	{
	  argv_ptr = i + 1;
	  if (!assembly_file_read)
	    {
	      initialize_world (load_trap_handler ? trap_file : NULL);
	    }
	  assembly_file_read |= !read_assembly_file (argv[++i]);
	  break;			/* Everything that follows is argv */
	}
      else if (streq (argv [i], "-mapped_io"))
	mapped_io = 1;
      else if (streq (argv [i], "-nomapped_io"))
	mapped_io = 0;
      else if (streq (argv [i], "-stext"))
	initial_text_size = atoi (argv[++i]);
      else if (streq (argv [i], "-sdata"))
	initial_data_size = atoi (argv[++i]);
      else if (streq (argv [i], "-ldata"))
	initial_data_limit = atoi (argv[++i]);
      else if (streq (argv [i], "-sstack"))
	initial_stack_size = atoi (argv[++i]);
      else if (streq (argv [i], "-lstack"))
	initial_stack_limit = atoi (argv[++i]);

      else if (streq (argv [i], "-sktext"))
	initial_k_text_size = atoi (argv[++i]);
      else if (streq (argv [i], "-skdata"))
	initial_k_data_size = atoi (argv[++i]);
      else if (streq (argv [i], "-lkdata"))
	initial_k_data_limit = atoi (argv[++i]);
      else
	error ("usage: spim -bare/-asm -trap/-notrap -trap_file <file> -quiet/-noquiet -mapped_io/-nomapped_io -file <file> <args>\n");
    }

  if (!assembly_file_read)
    {
      initialize_world (load_trap_handler ? trap_file : NULL);
      top_level ();
    }
  else if (assembly_file_read)
    {
      console_to_program ();
      initialize_run_stack (argc - argv_ptr, &argv[argv_ptr]);
      if (!setjmp (spim_top_level_env))
      {
	print_undefined_symbols();
	run_program (find_symbol_address (DEFAULT_RUN_LOCATION),
		     DEFAULT_RUN_STEPS, 0, 0);
      }
      console_to_spim ();
    }

  return (0);
}


/* Top-level read-eval-print loop for SPIM. */

#ifdef __STDC__
static void
top_level (void)
#else
static void
top_level ()
#endif
{
  int redo = 0;			/* Non-zero means reexecute last command */

  signal (SIGINT, control_c_seen);
  while (1)
    {
      if (!redo)
	write_output (message_out, "(spim) ");
      if (!setjmp (spim_top_level_env))
	redo = parse_spim_command (stdin, redo);
      else
	redo = 0;
      fflush (stdout);
      fflush (stderr);
    }
}


#ifdef __STDC__
void
control_c_seen (int arg)
#else
void
control_c_seen (arg)
int arg;
#endif
{
  console_to_spim ();
  write_output (message_out, "\nExecution interrupted\n");
  longjmp (spim_top_level_env, 1);
}


/* SPIM commands */

#define UNKNOWN_CMD		0
#define EXIT_CMD		1
#define READ_CMD		2
#define RUN_CMD			3
#define STEP_CMD		4
#define PRINT_CMD		5
#define PRINT_SYM_CMD		6
#define REINITIALIZE_CMD	7
#define ASM_CMD			8
#define REDO_CMD		9
#define NOP_CMD			10
#define HELP_CMD		11
#define CONTINUE_CMD		12
#define SET_BKPT_CMD		13
#define DELETE_BKPT_CMD		14
#define LIST_BKPT_CMD		15


/* Parse a SPIM command from the FILE and execute it.  If REDO is non-zero,
   don't read a new command; just rexecute the previous one.
   Return non-zero if the command was to redo the previous command. */

#ifdef __STDC__
static int
parse_spim_command (FILE *file, int redo)
#else
static int
parse_spim_command (file, redo)
     FILE *file;
     int redo;
#endif
{
  static int prev_cmd = NOP_CMD; /* Default redo */
  static int prev_token;
  int cmd;

  initialize_scanner (file);
  initialize_parser ("<standard input>");
  switch (cmd = (redo ? prev_cmd : read_assembly_command ()))
    {
    case EXIT_CMD:
      console_to_spim ();
      exit (0);

    case READ_CMD:
      {
	int token = (redo ? prev_token : read_token ());

	if (!redo) flush_to_newline ();
	if (token == Y_STR)
	  {
	    read_assembly_file ((char *) yylval.p);
	    initialize_scanner (file); /* Reinitialize! */
	  }
	else
	  error ("Must supply a filename to read\n");
	prev_cmd = READ_CMD;
	return (0);
      }

    case RUN_CMD:
      {
	static mem_addr addr;

	addr = (redo ? addr : get_opt_int ());
	if (addr == 0)
	  addr = starting_address ();

	initialize_run_stack (0, 0);
	console_to_program ();
	if (addr)
	{
	  print_undefined_symbols();
	  if (run_program (addr, DEFAULT_RUN_STEPS, 0, 0))
	    write_output (message_out, "Breakpoint encountered at 0x%08x\n",
			  PC);
	}
	console_to_spim ();

	prev_cmd = RUN_CMD;
	return (0);
      }

    case CONTINUE_CMD:
      {
	if (PC != 0)
	  {
	    console_to_program ();
	    if (run_program (PC, DEFAULT_RUN_STEPS, 0, 1))
	      write_output (message_out, "Breakpoint encountered at 0x%08x\n",
			    PC);
	    console_to_spim ();
	  }
	prev_cmd = CONTINUE_CMD;
	return (0);
      }

    case STEP_CMD:
      {
	static int steps;
	mem_addr addr;

	steps = (redo ? steps : get_opt_int ());
	addr = starting_address ();

	if (steps == 0)
	  steps = 1;
	if (addr)
	  {
	    console_to_program ();
	    if (run_program (addr, steps, 1, 1))
	      write_output (message_out, "Breakpoint encountered at 0x%08x\n",
			    PC);
	    console_to_spim ();
	  }

	prev_cmd = STEP_CMD;
	return (0);
      }

    case PRINT_CMD:
      {
	int token = (redo ? prev_token : read_token ());
	static int loc;

	if (token == Y_REG)
	  {
	    if (redo) loc += 1;
	    else loc = yylval.i;
	    print_reg (loc, 0);
	  }
	else if (token == Y_FP_REG)
	  {
	    if (redo) loc += 2;
	    else loc = yylval.i;
	    print_reg (loc, 1);
	  }
	else if (token == Y_INT)
	  {
	    if (redo) loc += 4;
	    else loc = yylval.i;
	    print_mem (loc);
	  }
	else if (token == Y_ID)
	  {
	    if (!print_reg (yylval.i, 2))
	      {
		if (redo) loc += 4;
		else loc = find_symbol_address ((char *) yylval.p);

		if (loc != 0)
		  print_mem (loc);
		else
		  error ("Unknown label: %s\n", yylval.p);
	      }
	  }
	else
	  error ("Print what?\n");
	if (!redo) flush_to_newline ();
	prev_cmd = PRINT_CMD;
	prev_token = token;
	return (0);
      }

    case PRINT_SYM_CMD:
      print_symbols ();
      if (!redo) flush_to_newline ();
      prev_cmd = NOP_CMD;
      return (0);

    case REINITIALIZE_CMD:
      flush_to_newline ();
      initialize_world (load_trap_handler ? trap_file : NULL);
      write_startup_message ();
      prev_cmd = NOP_CMD;
      return (0);

    case ASM_CMD:
      yyparse ();
      prev_cmd = ASM_CMD;
      return (0);

    case REDO_CMD:
      return (1);

    case NOP_CMD:
      prev_cmd = NOP_CMD;
      return (0);

    case HELP_CMD:
      if (!redo) flush_to_newline ();
      write_output (message_out, "\nSPIM is a MIPS R2000 simulator.\n");
      write_output (message_out, "Its top-level commands are:\n");
      write_output (message_out, "exit  -- Exit the simulator\n");
      write_output (message_out, "quit  -- Exit the simulator\n");
      write_output (message_out,
		    "read \"FILE\" -- Read FILE of assembly code into memory\n");
      write_output (message_out,
		    "load \"FILE\" -- Same as read\n");
      write_output (message_out,
		    "run <ADDR> -- Start the program at optional ADDRESS\n");
      write_output (message_out,
		    "step <N> -- Step the program for N instructions\n");
      write_output (message_out,
		    "continue -- Continue program execution without stepping\n");
      write_output (message_out, "print $N -- Print register N\n");
      write_output (message_out,
		    "print $fN -- Print floating point register N\n");
      write_output (message_out,
		    "print ADDR -- Print contents of memory at ADDRESS\n");
      write_output (message_out,
		    "print_symbols -- Print a list of all symbols\n");
      write_output (message_out,
		    "reinitialize -- Clear the memory and registers\n");
      write_output (message_out,
		    "breakpoint <ADDR> -- Set a breakpoint at address\n");
      write_output (message_out,
		    "delete <ADDR> -- Delete all breakpoints at address\n");
      write_output (message_out, "list -- List all breakpoints\n");
      write_output (message_out,
		    ". -- Rest of line is assembly instruction to put in memory\n");
      write_output (message_out, "<cr> -- Newline reexecutes previous command\n");
      write_output (message_out, "? -- Print this message\n");

      write_output (message_out,
		    "\nMost commands can be abbreviated to their unique prefix\n");
      write_output (message_out, "e.g., ex(it), re(ad), l(oad), ru(n), s(tep), p(rint)\n\n");
      prev_cmd = HELP_CMD;
      return (0);

    case SET_BKPT_CMD:
    case DELETE_BKPT_CMD:
      {
	int token = (redo ? prev_token : read_token ());
	static mem_addr addr;

	if (!redo) flush_to_newline ();
	if (token == Y_INT)
	  addr = redo ? addr + 4 : (mem_addr)yylval.i;
	else if (token == Y_ID)
	  addr = redo ? addr + 4 : find_symbol_address ((char *) yylval.p);
	else
	  error ("Must supply an address for breakpoint\n");
	if (cmd == SET_BKPT_CMD)
	  add_breakpoint (addr);
	else
	  delete_breakpoint (addr);
	prev_cmd = cmd;

	return (0);
      }

    case LIST_BKPT_CMD:
      if (!redo) flush_to_newline ();
      list_breakpoints ();
      prev_cmd = LIST_BKPT_CMD;
      return (0);

    default:
      while (read_token () != Y_NL) ;
      error ("Unknown spim command\n");
      return (0);
    }
}


/* Read a SPIM command with the scanner and return its ennuemerated
   value. */

#ifdef __STDC__
static int
read_assembly_command (void)
#else
static int
read_assembly_command ()
#endif
{
  int token = read_token ();

  if (token == Y_NL)		/* Blank line means redo */
    return (REDO_CMD);
  else if (token != Y_ID)	/* Better be a string */
    return (UNKNOWN_CMD);
  else if (str_prefix ((char *) yylval.p, "exit", 2))
    return (EXIT_CMD);
  else if (str_prefix ((char *) yylval.p, "quit", 2))
    return (EXIT_CMD);
  else if (str_prefix ((char *) yylval.p, "print", 1))
    return (PRINT_CMD);
  else if (str_prefix ((char *) yylval.p, "print_symbols", 6))
    return (PRINT_SYM_CMD);
  else if (str_prefix ((char *) yylval.p, "run", 2))
    return (RUN_CMD);
  else if (str_prefix ((char *) yylval.p, "read", 2))
    return (READ_CMD);
  else if (str_prefix ((char *) yylval.p, "load", 2))
    return (READ_CMD);
  else if (str_prefix ((char *) yylval.p, "reinitialize", 6))
    return (REINITIALIZE_CMD);
  else if (str_prefix ((char *) yylval.p, "step", 1))
    return (STEP_CMD);
  else if (str_prefix ((char *) yylval.p, "help", 1))
    return (HELP_CMD);
  else if (str_prefix ((char *) yylval.p, "continue", 1))
    return (CONTINUE_CMD);
  else if (str_prefix ((char *) yylval.p, "breakpoint", 2))
    return (SET_BKPT_CMD);
  else if (str_prefix ((char *) yylval.p, "delete", 1))
    return (DELETE_BKPT_CMD);
  else if (str_prefix ((char *) yylval.p, "list", 2))
    return (LIST_BKPT_CMD);
  else if (*(char *) yylval.p == '?')
    return (HELP_CMD);
  else if (*(char *) yylval.p == '.')
    return (ASM_CMD);
  else
    return (UNKNOWN_CMD);
}


/* Return non-nil if STRING1 is a (proper) prefix of STRING2. */

#ifdef __STDC__
static int
str_prefix (char *s1, char *s2, int min_match)
#else
static int
str_prefix (s1, s2, min_match)
     char *s1, *s2;
     int min_match;
#endif
{
  for ( ; *s1 == *s2 && *s1 != '\0'; s1 ++, s2 ++) min_match --;
  return (*s1 == '\0' && min_match <= 0);
}


/* Read and return an integer from the current line of input.  If the
   line doesn't contain an integer, return 0.  In either case, flush the
   rest of the line, including the newline. */

#ifdef __STDC__
static int
get_opt_int (void)
#else
static int
get_opt_int ()
#endif
{
  int token;

  if ((token = read_token ()) == Y_INT)
    {
      flush_to_newline ();
      return (yylval.i);
    }
  else if (token == Y_NL)
    return (0);
  else
    {
      flush_to_newline ();
      return (0);
    }
}


/* Flush the rest of the input line up to and including the next newline. */

#ifdef __STDC__
static void
flush_to_newline (void)
#else
static void
flush_to_newline ()
#endif
{
  while (read_token () != Y_NL) ;
}


/* Print register number N.  TYPE code indicate which register set to use.
   Return non-zero if register N was valid register string. */

#ifdef __STDC__
static int
print_reg (int reg_no, int type_code)
#else
static int
print_reg (reg_no, type_code)
     int reg_no;
     int type_code;
#endif
{
  switch (type_code)
    {
    case 0:
      write_output (message_out, "Reg %d = 0x%08x (%d)\n",
		 reg_no, R[reg_no], R[reg_no]);
      break;

    case 1:
      if ((reg_no & 1) == 0)
	write_output (message_out, "FP reg %d = %g (double)\n",
		      reg_no, FPR_D (reg_no));

      write_output (message_out, "FP reg %d = %g (single)\n",
		 reg_no, FPR_S (reg_no));
      break;

    case 2:
      {
	char *rn = (char *) reg_no;
	char s[100];
	char *s1 = s;

	/* Conver to lower case */
	while (*rn != '\0' && s1 - s < 100)
	  *s1++ = tolower (*rn++);
	*s1 = '\0';
	/* Drop leading $ */
	if (s[0] == '$')
	  s1 = s + 1;
	else
	  s1 = s;

	if (streq (s1, "pc"))
	  write_output (message_out, "PC = 0x%08x (%d)\n", PC, PC);
	else if (streq (s1, "hi"))
	  write_output (message_out, "HI = 0x%08x (%d)\n", HI, HI);
	else if (streq (s1, "lo"))
	  write_output (message_out, "LO = 0x%08x (%d)\n", LO, LO);
	else if (streq (s1, "fpcond"))
	  write_output (message_out, "FpCond = 0x%08x (%d)\n", FpCond, FpCond);
	else if (streq (s1, "cause"))
	  write_output (message_out, "Cause = 0x%08x (%d)\n", Cause, Cause);
	else if (streq (s1, "epc"))
	  write_output (message_out, "EPC = 0x%08x (%d)\n", EPC, EPC);
	else if (streq (s1, "status"))
	  write_output (message_out, "Status = 0x%08x (%d)\n",
		     Status_Reg, Status_Reg);
	else if (streq (s1, "badvaddr"))
	  write_output (message_out, "BadVAddr = 0x%08x (%d)\n",
		     BadVAddr, BadVAddr);
	else if (streq (s1, "context"))
	  write_output (message_out, "Context = 0x%08x (%d)\n",
			Context, Context);
	else if (streq (s1, "prid"))
	  write_output (message_out, "PRId = 0x%08x (%d)\n", PRId, PRId);
	else
	  return (0);
	break;
      }
    }

  return (1);
}



/* Print an error message. */

#ifdef __STDC__
void
error (char *fmt, ...)
#else
/*VARARGS0*/
void
error (va_alist)
va_dcl
#endif
{
  va_list args;
#ifndef __STDC__
  char *fmt;
#endif

#ifdef __STDC__
  va_start (args, fmt);
#else
  va_start (args);
  fmt = va_arg (args, char *);
#endif

#ifdef NO_VFPRINTF
  _doprnt (fmt, args, stderr);
#else
  vfprintf (stderr, fmt, args);
#endif
  va_end (args);
}


/* Print an error message and return to top level. */

#ifdef __STDC__
int*
run_error (char *fmt, ...)
#else
/*VARARGS0*/
int*
run_error (va_alist)
va_dcl
#endif
{
  va_list args;
#ifndef __STDC__
  char *fmt;
#endif

#ifdef __STDC__
  va_start (args, fmt);
#else
  va_start (args);
  fmt = va_arg (args, char *);
#endif

  console_to_spim ();

#ifdef VFPRINTF
  _doprnt (fmt, args, stderr);
#else
  vfprintf (stderr, fmt, args);
#endif
  va_end (args);
  longjmp (spim_top_level_env, 1);
  return (0);			/* So it can be used in expressions */
}



/* IO facilities: */

#ifdef __STDC__
void
write_output (port fp, char *fmt, ...)
#else
/*VARARGS0*/
void
write_output (va_alist)
va_dcl
#endif
{
  va_list args;
  FILE *f;
#ifndef __STDC__
  char *fmt;
  port fp;
#endif
  int restore_console_to_program = 0;

#ifdef __STDC__
  va_start (args, fmt);
  f = (FILE *) fp.f;
#else
  va_start (args);
  fp = va_arg (args, port);
  f = (FILE *) fp.f;
  fmt = va_arg (args, char *);
#endif

  if (console_state_saved)
    {
      restore_console_to_program = 1;
      console_to_spim ();
    }

  if (f != 0)
    {
#ifdef NO_VFPRINTF
      _doprnt (fmt, args, f);
#else
      vfprintf (f, fmt, args);
#endif
      fflush (f);
    }
  else
    {
#ifdef NO_VFPRINTF
      _doprnt (fmt, args, stdout);
#else
      vfprintf (stdout, fmt, args);
#endif
      fflush (stdout);
    }
  va_end (args);

  if (restore_console_to_program)
    console_to_program ();
}


/* Simulate the semantics of fgets (not gets) on Unix file. */

#ifdef __STDC__
void
read_input (char *str, int str_size)
#else
void
read_input (str, str_size)
     char *str;
     int str_size;
#endif
{
  char *ptr;
  int restore_console_to_program = 0;

  if (console_state_saved)
    {
      restore_console_to_program = 1;
      console_to_spim ();
    }

  ptr = str;

  while (1 < str_size)		/* Reserve space for null */
    {
      char buf[1];
      read ((int) console_in.i, buf, 1); /* Not in raw mode! */

      *ptr ++ = buf[0];
      str_size -= 1;

      if (buf[0] == '\n')
	break;
    }

  if (0 < str_size)
    *ptr = '\0';		/* Null terminate input */

  if (restore_console_to_program)
    console_to_program ();
}


/* Give the console to the program for IO. */

#ifdef __STDC__
static void
console_to_program (void)
#else
static void
console_to_program ()
#endif
{
  if (mapped_io && !console_state_saved)
    {
#ifdef USE_TERMIO
      struct termio params;

#ifdef DJGPP
      tcgetattr((int)console_in.i, &saved_console_state);
      params = saved_console_state;

      /* Note:  You must include the ICRNL option on DOS
		IUCLC and IXANY simply are not supported under DJGPP */
      params.c_iflag &= ~(ISTRIP|INLCR|IGNCR|IXON|IXOFF|INPCK|BRKINT|PARMRK);
      params.c_iflag |= ICRNL;
#else
      ioctl (console_in.i, TCGETA, (char *) &saved_console_state);
      params = saved_console_state;
      params.c_iflag &= ~(ISTRIP|IUCLC|INLCR|ICRNL|IGNCR|IXON|IXOFF|IXANY|INPCK|BRKINT|PARMRK);
#endif

      params.c_iflag |= IGNBRK|IGNPAR;
      params.c_oflag &= ~OPOST;
      params.c_cflag &= ~PARENB;
      params.c_cflag |= CREAD|CS8;
      params.c_lflag = 0;
      params.c_cc[VMIN] = 1;
      params.c_cc[VTIME] = 1;
#ifdef DJGPP
      tcsetattr((int)console_in.i, TCSANOW, &params);
#else
      ioctl ((int)console_in.i, TCSETA, (char *) &params);
#endif
#else
      int flags;
      ioctl ((int) console_in.i, TIOCGETP, (char *) &saved_console_state);
      flags = saved_console_state.sg_flags;
      saved_console_state.sg_flags = (flags | RAW) & ~(CRMOD|ECHO);
      ioctl ((int) console_in.i, TIOCSETP, (char *) &saved_console_state);
      saved_console_state.sg_flags = flags;
      console_state_saved = 1;
#endif
    }
}


/* Return the console to SPIM. */

#ifdef __STDC__
static void
console_to_spim (void)
#else
static void
console_to_spim ()
#endif
{
  if (mapped_io && console_state_saved)
#ifdef USE_TERMIO
#ifdef DJGPP
    tcgetattr((int)console_in.i, &saved_console_state);
#else
    ioctl ((int) console_in.i, TCGETA, (char *) &saved_console_state);
#endif
#else
    ioctl ((int) console_in.i, TIOCSETP, (char *) &saved_console_state);
#endif
  console_state_saved = 0;
}


#ifdef __STDC__
int
console_input_available (void)
#else
int
console_input_available ()
#endif
{
  fd_set fdset;
  struct timeval timeout;

  if (mapped_io)
    {
      timeout.tv_sec = 0;
      timeout.tv_usec = 0;
      FD_ZERO (&fdset);
      FD_SET ((int) console_in.i, &fdset);
      return (select (sizeof (fdset) * 8, &fdset, NULL, NULL, &timeout));
    }
  else
    return (0);
}


#ifdef __STDC__
char
get_console_char (void)
#else
char
get_console_char ()
#endif
{
  char buf;

  read ((int) console_in.i, &buf, 1);

  if (buf == 3)			/* ^C */
    control_c_seen (0);
  return (buf);
}


#ifdef __STDC__
void
put_console_char (char c)
#else
void
put_console_char (c)
     char c;
#endif
{
  putc (c, (FILE *) console_out.f);
  fflush ((FILE *) console_out.f);
}

#ifdef __STDC__
static int
read_token ()
#else
static int
read_token ()
#endif
{
  int token = yylex ();

  if (token == 0)		/* End of file */
    {
      console_to_spim ();
      exit (0);
    }
  else
    {
      return (token);
    }
}
