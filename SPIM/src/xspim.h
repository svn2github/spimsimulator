/* SPIM S20 MIPS simulator.
   X interface to SPIM

   Copyright (C) 1990-1994 by James Larus (larus@cs.wisc.edu)
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


/* $Header: /u/l/a/larus/Software/SPIM/RCS/xspim.h,v 3.12 1997/07/09 22:08:29 larus Exp $
 */


#define IO_BUFFSIZE 	10000

#define TEXTHEIGHT \
	(text_font->max_bounds.ascent + text_font->max_bounds.descent)

#define TEXTWIDTH \
	(text_font->max_bounds.width)



/* Exported functions: */

#ifdef __STDC__
void execute_program (mem_addr pc, int steps, int display, int cont_bkpt);
void popup_console (Widget w, XtPointer client_data, XtPointer call_data);
void read_file (char *name, int assembly_file);
void redisplay_data (void);
void redisplay_text (void);
void start_program (mem_addr addr);

#else
void control_c_seen ();
void execute_program ();
void popup_console ();
void read_file ();
void redisplay_data ();
void redisplay_text ();
void start_program ();
#endif


/* Exported variables: */

extern XtAppContext app_con;
extern Widget message, console;
extern XtAppContext app_context;
extern XFontStruct *text_font;
extern Dimension button_width;
extern int load_trap_handler;
extern char *load_file;
extern Pixmap mark;
