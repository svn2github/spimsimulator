/* SPIM S20 MIPS simulator.
   X interface to SPIM
   (Derived from an earlier work by Alan Siow.)

   Copyright (C) 1990-2000 by James Larus (larus@cs.wisc.edu).
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


/* $Header: /Software/SPIM/src/xspim.c 10    1/01/03 9:34p Larus $
 */

#include <stdio.h>
#include <setjmp.h>
#ifdef __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>
#include <X11/Shell.h>
#include <X11/Xlib.h>
#include <X11/Xaw/Cardinals.h>
#include <X11/Xaw/Paned.h>
#include <X11/Xaw/AsciiText.h>
#include <X11/Xaw/Text.h>
#include <X11/Xaw/Dialog.h>
#include <X11/keysym.h>

#include "spim.h"
#include "spim-utils.h"
#include "inst.h"
#include "mem.h"
#include "reg.h"
#include "y.tab.h"
#include "buttons.h"
#include "windows.h"
#include "xspim.h"
#include "sym-tbl.h"


typedef struct _AppResources
{
  String textFont;
  Boolean bare;
  Boolean delayed_branches;
  Boolean delayed_loads;
  Boolean pseudo;
  Boolean asmm;
  Boolean trap;
  char *trap_file;
  Boolean quiet;
  Boolean mapped_io;
  char *filename;
  char *ex_filename;
  char *display2;
  Boolean hex_gpr;
  Boolean hex_fpr;
  char *initial_data_limit;
  char *initial_data_size;
  char *initial_k_data_limit;
  char *initial_k_data_size;
  char *initial_k_text_size;
  char *initial_stack_limit;
  char *initial_stack_size;
  char *initial_text_size;
} AppResources;


/* Exported variables: */

/* Not local, but not export so all files don't need setjmp.h */
jmp_buf spim_top_level_env; /* For ^C */
reg_word R[32];
reg_word HI, LO;
int HI_present, LO_present;
mem_addr PC, nPC;
double *FPR;			/* Dynamically allocate so overlay */
float *FGR;			/* is possible */
int *FWR;			/* is possible */
int FP_reg_present;		/* Presence bits for FP registers */
int FP_reg_poison;		/* Poison bits for FP registers */
int FP_spec_load;		/* Is register waiting for a speculative ld */
reg_word CpCond[4], CCR[4][32], CPR[4][32];

int bare_machine;		/* Non-Zero => simulate bare machine */
int delayed_branches;		/* Non-Zero => simulate delayed branches */
int delayed_loads;		/* Non-Zero => simulate delayed loads */
int accept_pseudo_insts;	/* Non-Zero => parse pseudo instructions  */
int quiet;			/* Non-Zero => no warning messages */
int source_file;		/* Non-Zero => program is source, not binary */
port message_out, console_out, console_in;
int mapped_io;			/* Non-zero => activate memory-mapped IO */
int pipe_out;
int cycle_level;		/* Non-zero => cycle level mode */

XtAppContext app_con;
Widget message, console = NULL;
XtAppContext app_context;
XFontStruct *text_font;
Dimension button_width;
int load_trap_handler;
char *trap_file = DEFAULT_TRAP_HANDLER;
Pixmap mark;


/* Local functions: */

#ifdef __STDC__
static void center_text_at_PC (void);
static char *check_buf_limit (char *, int *, int *);
static void create_console_display (void);
static void display_data_seg (void);
static char *display_values (mem_addr from, mem_addr to, char *buf, int *limit,
			     int *n);
static char *display_insts (mem_addr from, mem_addr to, char *buf, int *limit,
			    int *n);
static void display_registers (void);
static void initialize (AppResources app_res);
static mem_addr print_partial_line (mem_addr, char *, int *, int *);
static void show_running (void);
static void syntax (char *program_name);
static void write_text_to_window (Widget w, char *s);

#else
static void center_text_at_PC ();
static char *check_buf_limit ();
static void create_console_display ();
static void display_data_seg ();
static char *display_values ();
static char *display_insts ();
static void display_registers ();
static void initialize ();
static mem_addr print_partial_line ();
static void show_running ();
static void syntax ();
static void write_text_to_window ();
#endif

static String fallback_resources[] =
{
  "*font:		*-courier-medium-r-normal--12-*-75-*",
  "*Label*font:		*-adobe-helvetica-bold-r-*-*-12-*-75-*",
  "*panel*font:		*-adobe-helvetica-medium-r-*-*-12-*-75-*",
  "*ShapeStyle:		Oval",
  "*dialog*value.translations: #override \\n <Key>Return: confirm()",
  "*.translations: #override \\n <Ctrl>C: control_c_seen()",
  "*Form*left:		ChainLeft",
  "*Form*right:		ChainLeft",
  "*Form*top:		ChainTop",
  "*Form*bottom:	ChainTop",
  "*console.label:	SPIM Console",
  "*Shell1*iconName:	SPIM Console",
  NULL,
};


static XtActionsRec actionTable[2] =
{
  {"confirm", (XtActionProc) confirm},
  {"control_c_seen", (XtActionProc) control_c_seen},
};


static XtResource resources[] =
{
  {XtNfont, XtCFont, XtRString, sizeof (char *),
   XtOffset (AppResources *, textFont), XtRString, NULL},
  {"bare", "Bare", XtRBoolean, sizeof (Boolean),
   XtOffset (AppResources *, bare), XtRImmediate, False},
  {"delayed_branches", "Delayed_Branches", XtRBoolean, sizeof (Boolean),
   XtOffset (AppResources *, delayed_branches), XtRImmediate, False},
  {"delayed_loads", "Delayed_Loads", XtRBoolean, sizeof (Boolean),
   XtOffset (AppResources *, delayed_loads), XtRImmediate, False},
  {"pseudo", "Pseudo", XtRBoolean, sizeof (Boolean),
   XtOffset (AppResources *, pseudo), XtRImmediate, (XtPointer)True},
  {"asm",  "Asm",  XtRBoolean, sizeof (Boolean),
   XtOffset (AppResources *, asmm), XtRImmediate, False},
  {"trap", "Trap", XtRBoolean, sizeof (Boolean),
   XtOffset (AppResources *, trap), XtRImmediate, (XtPointer) True},
  {"trap_file", "Trap_File", XtRString, sizeof (char *),
   XtOffset (AppResources *, trap_file), XtRString, NULL},
  {"quiet", "Quiet", XtRBoolean, sizeof (Boolean),
   XtOffset (AppResources *, quiet), XtRImmediate, False},
  {"mapped_io", "Mapped_IO", XtRBoolean, sizeof (Boolean),
   XtOffset (AppResources *, mapped_io), XtRImmediate, False},

  {"filename", "Filename", XtRString, sizeof (char *),
   XtOffset (AppResources *, filename), XtRString, NULL},
  {"ex_filename", "Ex_Filename", XtRString, sizeof (char *),
   XtOffset (AppResources *, ex_filename), XtRString, NULL},
  {"display2", "Display2", XtRString, sizeof (char *),
   XtOffset (AppResources *, display2), XtRString, NULL},
  {"hexGpr", "DisplayHex", XtRBoolean, sizeof (Boolean),
   XtOffset (AppResources *, hex_gpr), XtRImmediate, (XtPointer) True},
  {"hexFpr", "DisplayHex", XtRBoolean, sizeof (Boolean),
   XtOffset (AppResources *, hex_fpr), XtRImmediate, False},

  {"stext", "Stext", XtRString, sizeof (char *),
   XtOffset (AppResources *, initial_text_size), XtRString, NULL},
  {"sdata", "Sdata", XtRString, sizeof (char *),
   XtOffset (AppResources *, initial_data_size), XtRString, NULL},
  {"ldata", "Ldata", XtRString, sizeof (char *),
   XtOffset (AppResources *, initial_data_limit), XtRString, NULL},
  {"sstack", "Sstack", XtRString, sizeof (char *),
   XtOffset (AppResources *, initial_stack_size), XtRString, NULL},
  {"lstack", "Lstack", XtRString, sizeof (char *),
   XtOffset (AppResources *, initial_stack_limit), XtRString, NULL},
  {"sktext", "Sktext", XtRString, sizeof (char *),
   XtOffset (AppResources *, initial_k_text_size), XtRString, NULL},
  {"skdata", "Skdata", XtRString, sizeof (char *),
   XtOffset (AppResources *, initial_k_data_size), XtRString, NULL},
  {"lkdata", "Lkdata", XtRString, sizeof (char *),
   XtOffset (AppResources *, initial_k_data_limit), XtRString, NULL}
};


static XrmOptionDescRec options[] =
{
  {"-bare",   "bare", XrmoptionNoArg, "True"},
  {"-asm",    "asmm",  XrmoptionNoArg, "True"},
  {"-pseudo",   "pseudo", XrmoptionNoArg, "True"},
  {"-delayed_branches", "delayed_branches", XrmoptionNoArg, "True"},
  {"-delayed_loads", "delayed_loads", XrmoptionNoArg, "True"},
  {"-nopseudo", "pseudo", XrmoptionNoArg, "False"},
  {"-trap",   "trap", XrmoptionNoArg, "True"},
  {"-notrap", "trap", XrmoptionNoArg, "False"},
  {"-trap_file", "trap_file", XrmoptionSepArg, NULL},
  {"-quiet",  "quiet", XrmoptionNoArg, "True"},
  {"-noquiet","quiet", XrmoptionNoArg, "False"},
  {"-mapped_io",  "mapped_io", XrmoptionNoArg, "True"},
  {"-nomapped_io","mapped_io", XrmoptionNoArg, "False"},

  {"-file",   "filename", XrmoptionSepArg, NULL},
  {"-execute","ex_filename", XrmoptionSepArg, NULL},
  {"-d2",     "display2", XrmoptionSepArg, NULL},
  {"-hexgpr", "hexGpr", XrmoptionNoArg, "True"},
  {"-nohexgpr", "hexGpr", XrmoptionNoArg, "False"},
  {"-hexfpr", "hexFpr", XrmoptionNoArg, "True"},
  {"-nohexfpr", "hexFpr", XrmoptionNoArg, "False"},
  {"-stext", "stext", XrmoptionSepArg, NULL},
  {"-sdata", "sdata", XrmoptionSepArg, NULL},
  {"-ldata", "ldata", XrmoptionSepArg, NULL},
  {"-sstack", "sstack", XrmoptionSepArg, NULL},
  {"-lstack", "lstack", XrmoptionSepArg, NULL},
  {"-sktext", "sktext", XrmoptionSepArg, NULL},
  {"-skdata", "skdata", XrmoptionSepArg, NULL},
  {"-lkdata", "lkdata", XrmoptionSepArg, NULL}
};


#define TICK_WIDTH 10

#define TICK_HEIGHT 10

static unsigned char tick_bits[] = {
  0x00, 0x00, 0x00, 0x02, 0x00, 0x03, 0x80, 0x01, 0xc1, 0x00, 0x63, 0x00,
  0x36, 0x00, 0x1c, 0x00, 0x08, 0x00, 0x00, 0x00};


/* Flags to control the way that registers are displayed. */

static int print_gpr_hex;		/* Print GPRs in hex/decimal */
static int print_fpr_hex;		/* Print FPRs in hex/floating point */


/* Local variables: */

static Dimension app_width;
static Dimension button_height;
static Dimension command_height;
static Dimension command_hspace;
static Dimension command_vspace;
static int console_is_visible;
static Dimension display_height;
static char *ex_file_name = NULL;
static char *file_name = NULL;
static Dimension reg_min_height;
static Dimension reg_max_height;
static Dimension segment_height;
static Widget shell1;
static int spim_is_running = 0;
static Widget toplevel;
static Widget pane1;



#ifdef __STDC__
static void
initialize (AppResources app_res)
#else
static void
initialize (app_res)
     AppResources app_res;
#endif
{
  bare_machine = 0;
  delayed_branches = 0;
  delayed_loads = 0;
  accept_pseudo_insts = 1;
  quiet = 0;
  source_file = 0;
  cycle_level = 0;

  if (app_res.bare)
    {
      bare_machine = 1;
      delayed_branches = 1;
      delayed_loads = 1;
    }

  if (app_res.asmm)
    {
      bare_machine = 0;
      delayed_branches = 0;
      delayed_loads = 0;
    }

  if (app_res.delayed_branches)
    delayed_branches = 1;

  if (app_res.delayed_loads)
    delayed_loads = 1;

  if (app_res.pseudo)
    accept_pseudo_insts = 1;
  else
    accept_pseudo_insts = 0;

  if (app_res.trap)
    load_trap_handler = 1;
  else
    load_trap_handler = 0;

  if (app_res.trap_file)
    {
      trap_file = app_res.trap_file;
      load_trap_handler = 1;
    }

  if (app_res.quiet)
    quiet = 1;
  else
    quiet = 0;

  if (app_res.mapped_io)
    mapped_io = 1;
  else
    mapped_io = 0;

  if (app_res.filename)
    file_name = app_res.filename;
  if (app_res.ex_filename)
    {
      ex_file_name = app_res.ex_filename;
      load_trap_handler = 0;
    }

  if (app_res.textFont == NULL)
    app_res.textFont = XtNewString ("8x13");
  if (!(text_font = XLoadQueryFont (XtDisplay (toplevel), app_res.textFont)))
    fatal_error ("Cannot open font %s\n", app_res.textFont);

  mark = XCreateBitmapFromData (XtDisplay (toplevel),
				RootWindowOfScreen (XtScreen (toplevel)),
				(char*)tick_bits, TICK_WIDTH, TICK_HEIGHT);

  button_height = TEXTHEIGHT * 1.6;
  button_width = TEXTWIDTH * 12;
  app_width = 6 * (button_width + 16);
  if ((unsigned)app_width < TEXTWIDTH * 4 * 22) /* Register display width */
    app_width = TEXTWIDTH * 4 * 22;
  command_hspace = 8;
  command_vspace = 8;
  command_height = (button_height * 3) + (command_vspace * 4) + 2;
  reg_min_height = 17 * TEXTHEIGHT + 4;
  reg_max_height = reg_min_height + 10 * TEXTHEIGHT + 4;
  segment_height = 10 * TEXTHEIGHT + 4;
  display_height = 8 * TEXTHEIGHT + 4;
  print_gpr_hex = app_res.hex_gpr;
  print_fpr_hex = app_res.hex_fpr;
}


#ifdef __STDC__
static void
create_console_display (void)
#else
static void
create_console_display ()
#endif
{
  Arg args[10];
  Cardinal n;

  n = 0;
  XtSetArg (args[n], XtNeditType, XawtextAppend); n++;
  XtSetArg (args[n], XtNscrollVertical, XawtextScrollWhenNeeded); n++;
  XtSetArg (args[n], XtNpreferredPaneSize, TEXTHEIGHT * 24); n++;
  XtSetArg (args[n], XtNwidth, TEXTWIDTH * 80); n++;
  console = XtCreateManagedWidget ("console", asciiTextWidgetClass, pane1,
				   args, n);
  XawTextEnableRedisplay (console);
  console_out.f = (FILE*) console;
}

#ifdef __STDC__
void
clear_console_display (void)
#else
void
clear_console_display ()
#endif
{
  Arg args[10];
  Cardinal n;

  XtSetArg (args[0], XtNstring, "");
  XtSetValues(console, args, 1);
}


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
  Widget toplevel2;
  AppResources app_res;
  Display *display;

  toplevel = XtAppInitialize (&app_context, "Xspim", options,
			      XtNumber (options), &argc, argv,
			      fallback_resources, NULL, ZERO);

  if (argc != 1)
    syntax (argv[0]);

  XtGetApplicationResources (toplevel, (XtPointer) &app_res, resources,
			     XtNumber (resources), NULL, ZERO);

  if (app_res.display2 == NULL)
    display = XtDisplay (toplevel);
  else
    display = XtOpenDisplay (app_context, app_res.display2, "xspim",
			     "Xspim", NULL, ZERO, &argc, argv);

  toplevel2 = XtAppCreateShell ("xspim","Xspim",applicationShellWidgetClass,
				display, NULL, ZERO);

  XtAppAddActions (app_context, actionTable, XtNumber (actionTable));

  initialize (app_res);

  /* Console window */

  shell1 = XtCreatePopupShell ("Shell1", topLevelShellWidgetClass,
			       toplevel, NULL, ZERO);
  pane1 = XtCreateManagedWidget ("pane1", panedWidgetClass, shell1,
				 NULL, ZERO);
  create_console_display ();

  create_sub_windows (toplevel, app_width, reg_min_height, reg_max_height,
		      command_height, command_hspace, command_vspace,
		      button_height, segment_height, display_height);

  XtRealizeWidget (toplevel);

  if (app_res.initial_text_size != NULL)
    initial_text_size = atoi (app_res.initial_text_size);
  if (app_res.initial_data_size != NULL)
    initial_data_size = atoi (app_res.initial_data_size);
  if (app_res.initial_data_limit != NULL)
    initial_data_limit = atoi (app_res.initial_data_limit);
  if (app_res.initial_stack_size != NULL)
    initial_stack_size = atoi (app_res.initial_stack_size);
  if (app_res.initial_stack_limit != NULL)
    initial_stack_limit = atoi (app_res.initial_stack_limit);
  if (app_res.initial_k_text_size != NULL)
    initial_k_text_size = atoi (app_res.initial_k_text_size);
  if (app_res.initial_k_data_size != NULL)
    initial_k_data_size = atoi (app_res.initial_k_data_size);
  if (app_res.initial_k_data_limit != NULL)
    initial_k_data_limit = atoi (app_res.initial_k_data_limit);
  write_startup_message ();
  initialize_world (load_trap_handler ? trap_file : NULL);

  if (file_name)
    {
      read_file (file_name, 1);
      record_file_name_for_prompt (file_name);
    }
  else if (ex_file_name)
    {
      initialize_world (0);	/* Don't have a trap handler loaded. */
      read_file (ex_file_name, 0);
      record_file_name_for_prompt (ex_file_name);
    }
  else
    {
      PC = starting_address ();
      redisplay_text ();
      center_text_at_PC ();
      redisplay_data ();
    }

  XtAppMainLoop (app_context);
  return (0);
}


#ifdef __STDC__
static void
syntax (char *program_name)
#else
static void
syntax (program_name)
     char *program_name;
#endif
{
  XtDestroyApplicationContext (app_context);
  fprintf (stderr, "Usage:\n %s", program_name);
  fprintf (stderr, "\t[ -bare/-asm ] [ -trap/-notrap ] [ -quiet/noquiet ]\n");
  fprintf (stderr, "\t[ -delayed_branches][ -delayed_loads]\n");
  fprintf (stderr, "\t[ -pseudo/-nopseudo][ -mapped_io/-nomapped_io ]\n");
  fprintf (stderr, "\t[ -d2 <display> ] [ -file/-execute <filename> ]\n");
  fprintf (stderr, "\t[ -s<seg> <size>] [ -l<seg> <size>]\n");
  exit (1);
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
  write_output (message_out, "\nExecution interrupted\n");
  redisplay_data ();
  continue_prompt (1);
  if (spim_is_running)
    longjmp (spim_top_level_env, 1);
}


#ifdef __STDC__
void
popup_console (Widget w, XtPointer client_data, XtPointer call_data)
#else
void
popup_console (w, client_data, call_data)
     Widget w;
     XtPointer client_data, call_data;
#endif
{
  if (console_is_visible)
    {
      console_is_visible = 0;
      XtPopdown (shell1);
    }
  else
    {
      console_is_visible = 1;
      XtPopup (shell1, XtGrabNone);
    }
}


#ifdef __STDC__
void
read_file (char *name, int assembly_file)
#else
void
read_file (name, assembly_file)
     char *name;
     int assembly_file;
#endif
{
  int error_flag;

  if (*name == '\0')
    error_flag = 1;
  else if (assembly_file)
    error_flag = read_assembly_file (name);
  if (!error_flag)
    {
      PC = find_symbol_address (DEFAULT_RUN_LOCATION);
      redisplay_text ();
      center_text_at_PC ();
      redisplay_data ();
    }
}


#ifdef __STDC__
void
start_program (mem_addr addr)
#else
void
start_program (addr)
     mem_addr addr;
#endif
{
  if (addr == 0)
    addr = starting_address ();

  if (addr != 0)
    execute_program (addr, DEFAULT_RUN_STEPS, 0, 0);
}


#ifdef __STDC__
void
execute_program (mem_addr pc, int steps, int display, int cont_bkpt)
#else
void
execute_program (pc, steps, display, cont_bkpt)
     mem_addr pc;
     int steps, display, cont_bkpt;
#endif
{
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

      spim_is_running = 1;
      show_running ();

      if (run_program (pc, steps, display, cont_bkpt))
	continue_prompt (0);
    }
  redisplay_text ();
  spim_is_running = 0;
  center_text_at_PC ();
  redisplay_data ();
}


#ifdef __STDC__
static void
show_running (void)
#else
static void
show_running ()
#endif
{
  Arg args[1];

  XtSetArg (args[0], XtNstring, "Running.....");
  XtSetValues (register_window, args, ONE);
}


/* Redisplay the contents of the registers and, if modified, the data
   and stack segments. */

#ifdef __STDC__
void
redisplay_data (void)
#else
void
redisplay_data ()
#endif
{
  display_registers ();
  display_data_seg ();
}


/* Redisplay the contents of the registers in a wide variety of
   formats. */

#ifdef __STDC__
static void
display_registers (void)
#else
static void
display_registers ()
#endif
{
  static char buf[8 * K];
  int max_buf_len = 8 * K;
  int string_len = 0;
  Arg args [2];

  registers_as_string (buf, &max_buf_len, &string_len, print_gpr_hex, print_fpr_hex);

  XtSetArg (args[0], XtNstring, (String)buf);
  XtSetArg (args[1], XtNlength, string_len);
  XtSetValues (register_window, args, TWO);
}


/* Redisplay the text segment and ktext segments if they have changed. */

#ifdef __STDC__
void
redisplay_text (void)
#else
void
redisplay_text ()
#endif
{
  static String buf = NULL;
  static int max_buf_len = 16 * K;
  int string_len = 0;
  Arg args [2];

  if (!text_modified)
    return;

  if (buf == NULL)
    buf = (String) malloc (max_buf_len);
  *buf = '\0';

  buf = insts_as_string (TEXT_BOT, text_top, buf, &max_buf_len, &string_len);
  sprintf (&buf[string_len], "\n\tKERNEL\n");
  string_len += strlen (&buf[string_len]);
  buf = insts_as_string (K_TEXT_BOT, k_text_top, buf, &max_buf_len, &string_len);

  XtSetArg (args[0], XtNstring, buf);
  XtSetArg (args[1], XtNlength, string_len);
  XtSetValues (text_window, args, TWO);

  text_modified = 0;
}


/* Center the text window at the instruction at the current PC and
   highlight the instruction. */

#ifdef __STDC__
static void
center_text_at_PC (void)
#else
static void
center_text_at_PC ()
#endif
{
  char buf[100];
  XawTextBlock text;
  XawTextPosition start, finish;
  static mem_addr prev_PC = 0;

  XawTextUnsetSelection(text_window);

  if (PC < TEXT_BOT || (PC > text_top && (PC < K_TEXT_BOT || PC > k_text_top)))
    return;

  sprintf (buf, "\n[0x%08x]", PC);
  text.firstPos = 0;
  text.length = strlen (buf);
  text.ptr = buf;
  text.format = FMT8BIT;

  /* Find start of line at PC: */
  start = XawTextSearch (text_window, prev_PC <= PC ? XawsdRight : XawsdLeft,
			 &text);

  if (start == XawTextSearchError)
    {
      start = XawTextSearch (text_window,
			     prev_PC > PC ? XawsdRight : XawsdLeft,
			     &text);
    }

  if (start == XawTextSearchError)
    {
      if (PC != 0x00400000) return;
      XawTextSetInsertionPoint (text_window, 0);
    }
  else
    XawTextSetInsertionPoint (text_window, start + 1);

  /* Find end of the line: */
  text.length = 1;
  finish = XawTextSearch (text_window, XawsdRight, &text);
  if (finish == XawTextSearchError)
    return;

  /* Highlight the line: */
  XawTextSetSelection(text_window, start + 1, finish);

  prev_PC = PC;
}


/* Display the contents of the data and stack segments, if they have
   been modified. */

#ifdef __STDC__
static void
display_data_seg (void)
#else
static void
display_data_seg ()
#endif
{
  static String buf = NULL;
  static int max_buf_len = 16 * K;
  int string_len = 0;
  Arg args [2];

  if (!data_modified)
    return;

  if (buf == NULL)
    buf = (char *) malloc (max_buf_len);

  buf = data_seg_as_string(buf, &max_buf_len, &string_len);

  XtSetArg (args[0], XtNstring, buf);
  XtSetArg (args[1], XtNlength, string_len);
  XtSetValues (data_window, args, TWO);

  data_modified = 0;
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
  Widget w;
#ifndef __STDC__
  char *fmt;
  port fp;
#endif
  char io_buffer [IO_BUFFSIZE];

#ifdef __STDC__
  va_start (args, fmt);
#else
  va_start (args);
  fp = va_arg (args, port);
  fmt = va_arg (args, char *);
#endif
  w = (Widget) fp.f;

  if (w == console && !console_is_visible)
    {
      XtPopup (shell1, XtGrabNone);
      console_is_visible = 1;
    }

  vsprintf (io_buffer, fmt, args);
  va_end (args);

  write_text_to_window (w, io_buffer);

  /* Look for keyboard input (such as ^C) */
  while (XtAppPending (app_context))
    {
      XEvent event;

      XtAppNextEvent (app_context, &event);
      XtDispatchEvent (&event);
    }
}


/* Simulate the semantics of fgets, not gets, on an x-window. */

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
  char buffer[11];
  KeySym key;
  XComposeStatus compose;
  XEvent event;
  char *ptr;

  if (!console_is_visible)
    {
      XtPopup (shell1, XtGrabNone);
      console_is_visible = 1;
    }

  ptr = str;

  while (1 < str_size)		/* Reserve space for null */
    {
      XtAppNextEvent (app_context, &event);
      if (event.type == KeyPress)
	{
	  int chars = XLookupString (&event.xkey, buffer, 10, &key, &compose);
	  if ((key == XK_Return) || (key == XK_KP_Enter))
	    {
	      *ptr++ = '\n';

	      write_text_to_window (console, "\n");
	      break;
	    }
	  else if (*buffer == 3) /* ^C */
	    XtDispatchEvent (&event);
	  else
	    {
	      int n = (chars < str_size - 1 ? chars : str_size - 1);

	      strncpy (ptr, buffer, n);
	      ptr += n;
	      str_size -= n;

	      buffer[chars] = '\0';
	      write_text_to_window (console, buffer);
	    }
	}
      else
	XtDispatchEvent (&event);
    }

  if (0 < str_size)
    *ptr = '\0';
}


#ifdef __STDC__
int
console_input_available (void)
#else
int
console_input_available ()
#endif
{
  if (mapped_io)
    return (XtAppPending (app_context));
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
  XEvent event;

  if (!console_is_visible)
    {
      XtPopup (shell1, XtGrabNone);
      console_is_visible = 1;
    }

  while (1)
    {
      XtAppNextEvent (app_context, &event);
      if (event.type == KeyPress)
	{
	  char buffer[11];
	  KeySym key;
	  XComposeStatus compose;
	  XLookupString (&event.xkey, buffer, 10, &key, &compose);

	  if (*buffer == 3)		       /* ^C */
	    XtDispatchEvent (&event);
	  else if (*buffer != 0)
	    return (buffer[0]);
	}
      else
	XtDispatchEvent (&event);
    }
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
  char buf[4];

  buf[0] = c;
  buf[1] = '\0';
  if (!console_is_visible)
    {
      XtPopup (shell1, XtGrabNone);
      console_is_visible = 1;
    }
  write_text_to_window (console, buf);
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
  char io_buffer [IO_BUFFSIZE];

#ifdef __STDC__
  va_start (args, fmt);
#else
  va_start (args);
  fmt = va_arg (args, char *);
#endif
  vsprintf (io_buffer, fmt, args);
  va_end (args);
  if (message != 0)
    write_text_to_window (message, io_buffer);
  else
    fprintf (stderr, "%s", io_buffer);
}


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
  char io_buffer [IO_BUFFSIZE];

#ifdef __STDC__
  va_start (args, fmt);
#else
  va_start (args);
  fmt = va_arg (args, char *);
#endif
  vsprintf (io_buffer, fmt, args);
  va_end (args);
  if (message != 0)
    write_text_to_window (message, io_buffer);
  else
    fprintf (stderr, "%s", io_buffer);
  if (spim_is_running)
    longjmp (spim_top_level_env, 1);
  return (0);			/* So it can be used in expressions */
}


#ifdef __STDC__
static void
write_text_to_window (Widget w, char *s)
#else
static void
write_text_to_window (w, s)
     Widget w;
     char *s;
#endif
{
  XawTextBlock textblock;
  XawTextPosition ip = XawTextGetInsertionPoint (w);

  if (!s || strlen (s) == 0) return;

  textblock.firstPos = 0;
  textblock.length = strlen (s);
  textblock.ptr = s;
  textblock.format = FMT8BIT;

  XawTextReplace (w, ip, ip, &textblock);
  XawTextSetInsertionPoint (w,
			    XawTextGetInsertionPoint (w) + textblock.length);
}
