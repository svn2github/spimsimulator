/* SPIM S20 MIPS simulator.
   X interface to SPIM

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


/* $Header: /Software/SPIM/src/buttons.h 6     2/15/04 1:25p Larus $
 */


/* Exported functions: */

void create_buttons (Widget parent);
void confirm (Widget widget, XEvent *event, String *params,
	      Cardinal *num_params);
void continue_prompt (int interrupt_seen);
void record_file_name_for_prompt (char *name);
