/* SPIM S20 MIPS simulator.
   Terminal interface for SPIM simulator.

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


/* $Header: /Software/SPIM/src/spim.c 25    3/11/04 9:25p Larus $
*/


#ifndef WIN32
#include <unistd.h>
#endif
#include <stdio.h>
#include <ctype.h>
#include <setjmp.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>


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


#ifndef WIN32
#include <sys/time.h>

#ifdef USE_TERMIO
#include <termio.h>
#include <termios.h>
#else
#include <sys/ioctl.h>
#include <sgtty.h>
#endif
#endif

#include <stdarg.h>

#include "spim.h"
#include "spim-utils.h"
#include "inst.h"
#include "reg.h"
#include "mem.h"
#include "parser.h"
#include "sym-tbl.h"
#include "scanner.h"
#include "y.tab.h"


/* Internal functions: */

static void console_to_program ();
static void console_to_spim ();
static void flush_to_newline ();
static int get_opt_int ();
static int parse_spim_command (FILE *file, int redo);
static int print_reg (int reg_no);
static int print_fp_reg (int reg_no);
static int print_reg_from_string (char *reg);
static void print_all_regs (int hex_flag);
static int read_assembly_command ();
static int str_prefix (char *s1, char *s2, int min_match);
static void top_level ();
static int read_token ();


/* Exported Variables: */

/* Not local, but not export so all files don't need setjmp.h */
jmp_buf spim_top_level_env;	/* For ^C */

int bare_machine;		/* Non-Zero => simulate bare machine */
int delayed_branches;		/* Non-Zero => simulate delayed branches */
int delayed_loads;		/* Non-Zero => simulate delayed loads */
int accept_pseudo_insts;	/* Non-Zero => parse pseudo instructions  */
int quiet;			/* Non-Zero => no warning messages */
port message_out, console_out, console_in;
int mapped_io;			/* Non-zero => activate memory-mapped IO */
int pipe_out;
int cycle_level;		/* Non-zero => cycle level mode */
int spim_return_value;		/* Value returned when spim exits */

/* Local variables: */

static int load_trap_handler = 1; /* Non-zero => load standard trap handler */
char *trap_file = DEFAULT_TRAP_HANDLER;
static int console_state_saved;
#ifdef USE_TERMIO
static struct termio saved_console_state;
#else
static struct sgttyb saved_console_state;
#endif



int
main (int argc, char **argv)
{
  int i;
  int assembly_file_read = 0;
  int argv_ptr = 0;

  console_out.f = stdout;
  message_out.f = stdout;

  bare_machine = 0;
  delayed_branches = 0;
  delayed_loads = 0;
  accept_pseudo_insts = 1;
  quiet = 0;
  cycle_level = 0;
  spim_return_value = 0;

  /* Input comes directly (not through stdio): */
  console_in.i = 0;
  mapped_io = 0;

  write_startup_message ();

  if (argc == 2)
    {
      /* Only one argument better be a file name. */
      initialize_world (load_trap_handler ? trap_file : NULL);
      assembly_file_read |= !read_assembly_file (argv[1]);
    }
  else
    for (i = 1; i < argc; i++)
      {
#ifdef WIN32
	/* On Windows, support "/option" as well as "-option" */
	if (argv [i][0] == '/')
	  argv [i][0] = '-';
#endif

	if (streq (argv [i], "-bare"))
	  {
	    bare_machine = 1;
	    delayed_branches = 1;
	    delayed_loads = 1;
	    quiet = 1;
	  }
	else if (streq (argv [i], "-asm"))
	  {
	    bare_machine = 0;
	    delayed_branches = 0;
	    delayed_loads = 0;
	  }
	else if (streq (argv [i], "-delayed_branches"))
	  {
	    delayed_branches = 1;
	  }
	else if (streq (argv [i], "-delayed_loads"))
	  {
	    delayed_loads = 1;
	  }
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
	else if (streq (argv [i], "-file") && (i + 1 < argc))
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
	  error ("usage: spim -bare/-asm {-delayed_branches} {-delayed_loads} -trap/-notrap -trap_file <file> -quiet/-noquiet -mapped_io/-nomapped_io -file <file> <args>\n");
      }

  if (!assembly_file_read)
    {
      initialize_world (load_trap_handler ? trap_file : NULL);
      top_level ();
    }
  else /* assembly_file_read */
    {
      console_to_program ();
      initialize_run_stack (argc - argv_ptr, &argv[argv_ptr]);
      if (!setjmp (spim_top_level_env))
	{
	  char *undefs = undefined_symbol_string ();
	  if (undefs != NULL)
	    {
	      write_output (message_out, "The following symbols are undefined:\n");
	      write_output (message_out, undefs);
	      write_output (message_out, "\n");
	      free (undefs);
	    }
	  run_program (find_symbol_address (DEFAULT_RUN_LOCATION),
		       DEFAULT_RUN_STEPS, 0, 0);
	}
      console_to_spim ();
    }

  spim_return_value = 0;
  return (spim_return_value);
}


/* Top-level read-eval-print loop for SPIM. */

static void
top_level ()
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


void
control_c_seen (int arg)
{
  console_to_spim ();
  write_output (message_out, "\nExecution interrupted\n");
  longjmp (spim_top_level_env, 1);
}


/* SPIM commands */

enum {
  UNKNOWN_CMD = 0,
  EXIT_CMD,
  READ_CMD,
  RUN_CMD,
  STEP_CMD,
  PRINT_CMD,
  PRINT_SYM_CMD,
  PRINT_ALL_REGS_CMD,
  REINITIALIZE_CMD,
  ASM_CMD,
  REDO_CMD,
  NOP_CMD,
  HELP_CMD,
  CONTINUE_CMD,
  SET_BKPT_CMD,
  DELETE_BKPT_CMD,
  LIST_BKPT_CMD,
  DUMPNATIVE_TEXT_CMD,
  DUMP_TEXT_CMD
};

/* Parse a SPIM command from the FILE and execute it.  If REDO is non-zero,
   don't read a new command; just rexecute the previous one.
   Return non-zero if the command was to redo the previous command. */

static int
parse_spim_command (FILE *file, int redo)
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
	  char *undefs = undefined_symbol_string ();
	  if (undefs != NULL)
	    {
	      write_output (message_out, "The following symbols are undefined:\n");
	      write_output (message_out, undefs);
	      write_output (message_out, "\n");
	      free (undefs);
	    }

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
	    print_reg (loc);
	  }
	else if (token == Y_FP_REG)
	  {
	    if (redo) loc += 2;
	    else loc = yylval.i;
	    print_fp_reg (loc);
	  }
	else if (token == Y_INT)
	  {
	    if (redo) loc += 4;
	    else loc = yylval.i;
	    print_mem (loc);
	  }
	else if (token == Y_ID)
	  {
	    if (!print_reg_from_string ((char *) yylval.p))
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

    case PRINT_ALL_REGS_CMD:
      {
	int hex_flag = 0;
	int token = (redo ? prev_token : read_token ());
	if (token == Y_ID && streq(yylval.p, "hex"))
	  hex_flag = 1;
	print_all_regs (hex_flag);
	if (!redo) flush_to_newline ();
	prev_cmd = NOP_CMD;
	return (0);
      }

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
		    "print_symbols -- Print all global symbols\n");
      write_output (message_out,
		    "print_all_regs -- Print all MIPS registers\n");
      write_output (message_out,
		    "print_all_regs hex -- Print all MIPS registers in hex\n");
      write_output (message_out,
		    "reinitialize -- Clear the memory and registers\n");
      write_output (message_out,
		    "breakpoint <ADDR> -- Set a breakpoint at address\n");
      write_output (message_out,
		    "delete <ADDR> -- Delete all breakpoints at address\n");
      write_output (message_out, "list -- List all breakpoints\n");
      write_output (message_out, "dump [ \"FILE\" ] -- Dump binary code to spim.dump or FILE in network byte order\n");
      write_output (message_out, "dumpnative [ \"FILE\" ] -- Dump binary code to spim.dump or FILE in host byte order\n");
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

    case DUMPNATIVE_TEXT_CMD:
    case DUMP_TEXT_CMD:
      {
        FILE *fp = NULL;
        char *filename = NULL;
	int token = (redo ? prev_token : read_token ());
        int i;
        int words = 0;
	int dump_start;
	int dump_limit;

        if (token == Y_STR)
	  filename = (char *) yylval.p;
        else if (token == Y_NL)
	  filename = "spim.dump";
        else
          {
            fprintf (stderr, "usage: %s [ \"filename\" ]\n",
                     (cmd == DUMP_TEXT_CMD ? "dump" : "dumpnative"));
            return (0);
          }

        fp = fopen (filename, "wb");
        if (fp == NULL)
          {
            perror (filename);
            return (0);
          }

	dump_start = find_symbol_address (END_OF_TRAP_HANDLER_SYMBOL);
	if (dump_start != 0)
	  dump_start -= TEXT_BOT;
	dump_start = dump_start >> 2;

	user_kernel_text_segment (0);
	dump_limit = (current_text_pc() - TEXT_BOT) >> 2;

        for (i = dump_start; i < dump_limit; i++)
          {
            int32 code = inst_encode (text_seg[i]);
            if (cmd == DUMP_TEXT_CMD)
	      code = htonl (code);    /* dump in network byte order */
            fwrite (&code, 1, sizeof(code), fp);
            words++;
          }

        fclose (fp);
        fprintf (stderr, "Dumped %d words starting at 0x%08x to file %s\n",
                 words, (dump_start << 2) + TEXT_BOT, filename);
      }
      prev_cmd = cmd;
      return (0);

    default:
      while (read_token () != Y_NL) ;
      error ("Unknown spim command\n");
      return (0);
    }
}


/* Read a SPIM command with the scanner and return its ennuemerated
   value. */

static int
read_assembly_command ()
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
  else if (str_prefix ((char *) yylval.p, "print_symbols", 7))
    return (PRINT_SYM_CMD);
  else if (str_prefix ((char *) yylval.p, "print_all_regs", 7))
    return (PRINT_ALL_REGS_CMD);
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
  else if (str_prefix ((char *) yylval.p, "dumpnative", 5))
    return (DUMPNATIVE_TEXT_CMD);
  else if (str_prefix ((char *) yylval.p, "dump", 4))
    return (DUMP_TEXT_CMD);
  else if (*(char *) yylval.p == '?')
    return (HELP_CMD);
  else if (*(char *) yylval.p == '.')
    return (ASM_CMD);
  else
    return (UNKNOWN_CMD);
}


/* Return non-nil if STRING1 is a (proper) prefix of STRING2. */

static int
str_prefix (char *s1, char *s2, int min_match)
{
  for ( ; *s1 == *s2 && *s1 != '\0'; s1 ++, s2 ++) min_match --;
  return (*s1 == '\0' && min_match <= 0);
}


/* Read and return an integer from the current line of input.  If the
   line doesn't contain an integer, return 0.  In either case, flush the
   rest of the line, including the newline. */

static int
get_opt_int ()
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

static void
flush_to_newline ()
{
  while (read_token () != Y_NL) ;
}


/* Print register number N.
   Return non-zero if register N was valid register string. */

static int
print_reg (int reg_no)
{
  write_output (message_out, "Reg %d = 0x%08x (%d)\n", reg_no, R[reg_no], R[reg_no]);
  return (1);
}


static int
print_fp_reg (int reg_no)
{
  if ((reg_no & 1) == 0)
    write_output (message_out, "FP reg %d = %g (double)\n", reg_no, FPR_D (reg_no));
  write_output (message_out, "FP reg %d = %g (single)\n", reg_no, FPR_S (reg_no));
  return (1);
}


static int
print_reg_from_string (char* reg_num)
{
  char s[100];
  char *s1 = s;

  /* Conver to lower case */
  while (*reg_num != '\0' && s1 - s < 100)
    *s1++ = tolower (*reg_num++);
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
    write_output (message_out, "FCSR = 0x%08x (%d)\n", FCSR, FCSR);
  else if (streq (s1, "cause"))
    write_output (message_out, "Cause = 0x%08x (%d)\n", CP0_Cause, CP0_Cause);
  else if (streq (s1, "epc"))
    write_output (message_out, "EPC = 0x%08x (%d)\n", CP0_EPC, CP0_EPC);
  else if (streq (s1, "status"))
    write_output (message_out, "Status = 0x%08x (%d)\n", CP0_Status, CP0_Status);
  else if (streq (s1, "badvaddr"))
    write_output (message_out, "BadVAddr = 0x%08x (%d)\n", CP0_BadVAddr, CP0_BadVAddr);
  else
    return (0);

  return (1);
}


#define MAX_BUF_LEN 32000

static void
print_all_regs (int hex_flag)
{
  int max_buf_len = MAX_BUF_LEN;
  char buf[MAX_BUF_LEN];
  int count;
  registers_as_string (buf, &max_buf_len, &count, hex_flag, hex_flag);
  write_output (message_out, "%s\n", buf);
}



/* Print an error message. */

void
error (char *fmt, ...)
{
  va_list args;

  va_start (args, fmt);

#ifdef NO_VFPRINTF
  _doprnt (fmt, args, stderr);
#else
  vfprintf (stderr, fmt, args);
#endif
  va_end (args);
}


/* Print an error message and return to top level. */

int*
run_error (char *fmt, ...)
{
  va_list args;

  va_start (args, fmt);

  console_to_spim ();

#ifdef NO_VFPRINTF
  _doprnt (fmt, args, stderr);
#else
  vfprintf (stderr, fmt, args);
#endif
  va_end (args);
  longjmp (spim_top_level_env, 1);
  return (0);			/* So it can be used in expressions */
}



/* IO facilities: */

void
write_output (port fp, char *fmt, ...)
{
  va_list args;
  FILE *f;
  int restore_console_to_program = 0;

  va_start (args, fmt);
  f = (FILE *) fp.f;

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

void
read_input (char *str, int str_size)
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

static void
console_to_program ()
{
  if (mapped_io && !console_state_saved)
    {
#ifdef USE_TERMIO
      struct termio params;

      ioctl (console_in.i, TCGETA, (char *) &saved_console_state);
      params = saved_console_state;
      params.c_iflag &= ~(ISTRIP|IUCLC|INLCR|ICRNL|IGNCR|IXON|IXOFF|IXANY|INPCK|BRKINT|PARMRK);

      params.c_iflag |= IGNBRK|IGNPAR;
      /*params.c_oflag &= ~OPOST;*/
      params.c_cflag &= ~PARENB;
      params.c_cflag |= CREAD|CS8;
      params.c_lflag = 0;
      params.c_cc[VMIN] = 1;
      params.c_cc[VTIME] = 1;
      ioctl ((int)console_in.i, TCSETA, (char *) &params);
#else
      int flags;
      ioctl ((int) console_in.i, TIOCGETP, (char *) &saved_console_state);
      flags = saved_console_state.sg_flags;
      saved_console_state.sg_flags = (flags | RAW) & ~(CRMOD|ECHO);
      ioctl ((int) console_in.i, TIOCSETP, (char *) &saved_console_state);
      saved_console_state.sg_flags = flags;
#endif
      console_state_saved = 1;
    }
}


/* Return the console to SPIM. */

static void
console_to_spim ()
{
  if (mapped_io && console_state_saved)
#ifdef USE_TERMIO
    ioctl ((int) console_in.i, TCSETA, (char *) &saved_console_state);
#else
    ioctl ((int) console_in.i, TIOCSETP, (char *) &saved_console_state);
#endif
  console_state_saved = 0;
}


int
console_input_available ()
{
#ifndef __CYGWIN32__
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
#endif
    return (0);
}


char
get_console_char ()
{
  char buf;

  read ((int) console_in.i, &buf, 1);

  if (buf == 3)			/* ^C */
    control_c_seen (0);
  return (buf);
}


void
put_console_char (char c)
{
  putc (c, (FILE *) console_out.f);
  fflush ((FILE *) console_out.f);
}

static int
read_token ()
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
