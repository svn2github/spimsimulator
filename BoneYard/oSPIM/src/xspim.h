/* SPIM S20 MIPS simulator.
   X interface to SPIM

   Copyright (C) 1990-2004 by James Larus (larus@cs.wisc.edu)
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


/* $Header: /Software/SPIM/src/xspim.h 12    3/21/04 2:05p Larus $
 */


#define IO_BUFFSIZE 	10000

#define TEXTHEIGHT \
	(text_font->max_bounds.ascent + text_font->max_bounds.descent)

#define TEXTWIDTH \
	(text_font->max_bounds.width)



/* Exported functions (also see spim.h): */

void clear_console_display ();
void execute_program (mem_addr pc, int steps, int display, int cont_bkpt);
void popup_console (Widget w, XtPointer client_data, XtPointer call_data);
void read_file (char *name);
void redisplay_data ();
void redisplay_text ();
void start_program (mem_addr addr);


/* Exported variables: */

extern XtAppContext app_con;
extern Widget message, console;
extern XtAppContext app_context;
extern XFontStruct *text_font;
extern Dimension button_width;
extern int load_exception_handler;
extern char *load_file;
extern Pixmap mark;
