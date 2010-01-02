/* SPIM S20 MIPS simulator.
   Interface to code to manipulate data segment directives.

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


/* $Header: /Software/SPIM/SPIM/Old/spim-6.4/data.h 1     1/02/05 8:03p Larus $
*/


/* Exported functions: */

#ifdef __STDC__
void align_data (int alignment);
mem_addr current_data_pc (void);
void data_begins_at_point (mem_addr addr);
void enable_data_alignment (void);
void end_of_assembly_file (void);
void extern_directive (char *name, int size);
void increment_data_pc (int value);
void k_data_begins_at_point (mem_addr addr);
void lcomm_directive (char *name, int size);
void set_data_alignment (int);
void set_data_pc (mem_addr addr);
void set_text_pc (mem_addr addr);
void store_byte (int value);
void store_double (double *value);
void store_float (double *value);
void store_half (int value);
void store_string (char *string, int length, int null_terminate);
void store_word (int value);
void user_kernel_data_segment (int to_kernel);
#else
void align_data ();
mem_addr current_data_pc ();
void data_begins_at_point ();
void enable_data_alignment ();
void end_of_assembly_file ();
void extern_directive ();
void increment_data_pc ();
void k_data_begins_at_point ();
void lcomm_directive ();
void set_data_alignment ();
void set_data_pc ();
void set_text_pc ();
void store_byte ();
void store_double ();
void store_float ();
void store_half ();
void store_string ();
void store_word ();
void user_kernel_data_segment ();
#endif
