/* SPIM S20 MIPS simulator.
  Utilities for displaying machine contents.

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
  PURPOSE.

  $Header: /Software/SPIM/src/display-utils.c 13    2/28/04 11:23a Larus $
*/


#include "spim.h"
#include "spim-utils.h"
#include "inst.h"
#include "data.h"
#include "mem.h"
#include "reg.h"
#include "run.h"
#include "sym-tbl.h"


static char *check_buf_limit (char *buf, int *max_buf_len, int *string_len);
static mem_addr print_partial_line (mem_addr i, char *buf, int *max_buf_len, int *string_len);


/* Write the contents of the machine's registers, in a wide variety of
   formats, into string BUF, whose length is BUF_LEN.  Return length of
   string in buffer. */

char *
registers_as_string (char *buf, int* max_buf_len, int* string_len, int print_gpr_hex, int print_fpr_hex)
{
  int i;
  char *bufp;
  char *grstr, *fpstr;
  char *grfill, *fpfill;
  static char *reg_names[] =
  {"r0", "at", "v0", "v1", "a0", "a1", "a2", "a3",
   "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
   "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
   "t8", "t9", "k0", "k1", "gp", "sp", "s8", "ra"};
  
  if (buf == NULL)
    fatal_error ("NULL buf pointer");
  *buf = '\0';
  bufp = buf;
  
  sprintf (bufp, " PC     = %08x    ", PC); bufp += strlen (bufp);
  sprintf (bufp, " EPC    = %08x    ", EPC); bufp += strlen (bufp);
  sprintf (bufp, " Cause  = %08x    ", Cause); bufp += strlen (bufp);
  sprintf (bufp, " BadVAddr= %08x\n", BadVAddr); bufp += strlen (bufp);
  sprintf (bufp, " Status = %08x    ", Status_Reg); bufp += strlen (bufp);
  sprintf (bufp, " HI     = %08x    ", HI); bufp += strlen (bufp);
  sprintf (bufp, " LO     = %08x\n", LO); bufp += strlen (bufp);
  
  if (print_gpr_hex)
    grstr = "R%-2d (%2s) = %08x", grfill = "  ";
  else
    grstr = "R%-2d (%2s) = %-10d", grfill = " ";

  sprintf (bufp, "\t\t\t\t General Registers\n"); bufp += strlen (bufp);
  for (i = 0; i < 8; i++)
  {
    sprintf (bufp, grstr, i, reg_names[i], R[i]);
    bufp += strlen (bufp);
    sprintf (bufp, grfill); bufp += strlen (bufp);
    sprintf (bufp, grstr, i+8, reg_names[i+8], R[i+8]);
    bufp += strlen (bufp);
    sprintf (bufp, grfill); bufp += strlen (bufp);
    sprintf (bufp, grstr, i+16, reg_names[i+16], R[i+16]);
    bufp += strlen (bufp);
    sprintf (bufp, grfill); bufp += strlen (bufp);
    sprintf (bufp, grstr, i+24, reg_names[i+24], R[i+24]);
    bufp += strlen (bufp);
    sprintf (bufp, "\n");
    bufp += 1;
  }
  

  sprintf (bufp, "\t\t\t      Double Floating Point Registers\n");
  bufp += strlen (bufp);

  sprintf (bufp, "FIR    = %08x    ", FIR); bufp += strlen (bufp);
  sprintf (bufp, " FCSR   = %08x    ", FCSR); bufp += strlen (bufp);
  sprintf (bufp, " FCCR   = %08x    ", FCSR); bufp += strlen (bufp);
  sprintf (bufp, " FEXR   = %08x    ", FCSR); bufp += strlen (bufp);
  sprintf (bufp, " FENR   = %08x    ", FCSR); bufp += strlen (bufp);

  if (print_fpr_hex)
    fpstr = "FP%-2d=%08x,%08x", fpfill = " ";
  else
    fpstr = "FP%-2d = %#-13.6g", fpfill = " ";

  if (print_fpr_hex)
    for (i = 0; i < 4; i += 1)
    {
      int *r1, *r2;
      
      /* Use pointers to cast to ints without invoking float->int conversion
      so we can just print the bits. */
      r1 = (int *)&FPR[i]; r2 = r1 + 1;
      sprintf (bufp, fpstr, 2*i, *r1, *r2); bufp += strlen (bufp);
      sprintf (bufp, fpfill); bufp += strlen (bufp);
      
      r1 = (int *)&FPR[i+4]; r2 = r1 + 1;
      sprintf (bufp, fpstr, 2*i+8, *r1, *r2); bufp += strlen (bufp);
      sprintf (bufp, fpfill); bufp += strlen (bufp);
      
      r1 = (int *)&FPR[i+8]; r2 = r1 + 1;
      sprintf (bufp, fpstr, 2*i+16, *r1, *r2); bufp += strlen (bufp);
      sprintf (bufp, fpfill); bufp += strlen (bufp);
      
      r1 = (int *)&FPR[i+12]; r2 = r1 + 1;
      sprintf (bufp, fpstr, 2*i+24, *r1, *r2); bufp += strlen (bufp);
      sprintf (bufp, "\n"); bufp += 1;
    }
    else for (i = 0; i < 4; i += 1)
    {
      sprintf (bufp, fpstr, 2*i, FPR[i]);
      bufp += strlen (bufp);
      sprintf (bufp, fpfill); bufp += strlen (bufp);
      sprintf (bufp, fpstr, 2*i+8, FPR[i+4]);
      bufp += strlen (bufp);
      sprintf (bufp, fpfill); bufp += strlen (bufp);
      sprintf (bufp, fpstr, 2*i+16, FPR[i+8]);
      bufp += strlen (bufp);
      sprintf (bufp, fpfill); bufp += strlen (bufp);
      sprintf (bufp, fpstr, 2*i+24, FPR[i+12]);
      bufp += strlen (bufp);
      sprintf (bufp, "\n");
      bufp += 1;
    }
    
    if (print_fpr_hex)
      fpstr = "FP%-2d=%08x", fpfill = " ";
    else
      fpstr = "FP%-2d = %#-13.6g", fpfill = " ";
    sprintf (bufp, "\t\t\t      Single Floating Point Registers\n");
    bufp += strlen (bufp);
    if (print_fpr_hex)
      for (i = 0; i < 8; i += 1)
      {
      /* Use pointers to cast to ints without invoking float->int conversion
	so we can just print the bits. */
	sprintf (bufp, fpstr, i, *(int *)&FGR[i]); bufp += strlen (bufp);
	sprintf (bufp, fpfill); bufp += strlen (bufp);
	
	sprintf (bufp, fpstr, i+8, *(int *)&FGR[i+8]); bufp += strlen (bufp);
	sprintf (bufp, fpfill); bufp += strlen (bufp);
	
	sprintf (bufp, fpstr, i+16, *(int *)&FGR[i+16]); bufp += strlen (bufp);
	sprintf (bufp, fpfill); bufp += strlen (bufp);
	
	sprintf (bufp, fpstr, i+24, *(int *)&FGR[i+24]); bufp += strlen (bufp);
	sprintf (bufp, "\n"); bufp += 1;
      }
      else for (i = 0; i < 8; i += 1)
      {
	sprintf (bufp, fpstr, i, FGR[i]);
	bufp += strlen (bufp);
	sprintf (bufp, fpfill); bufp += strlen (bufp);
	sprintf (bufp, fpstr, i+8, FGR[i+8]);
	bufp += strlen (bufp);
	sprintf (bufp, fpfill); bufp += strlen (bufp);
	sprintf (bufp, fpstr, i+16, FGR[i+16]);
	bufp += strlen (bufp);
	sprintf (bufp, fpfill); bufp += strlen (bufp);
	sprintf (bufp, fpstr, i+24, FGR[i+24]);
	bufp += strlen (bufp);
	sprintf (bufp, "\n");
	bufp += 1;
      }

  *string_len = bufp - buf;
  if (*max_buf_len <= *string_len)
    fatal_error ("Exceeded buffer size");

  return (buf);
}



/* Write a printable representation of the instructions in memory
   address FROM...TO to buffer BUF, which is of size LIMIT and whose next
   free location is N.  Return the, possible realloc'ed, buffer. */

char *
insts_as_string (mem_addr from, mem_addr to, char *buf, int *max_buf_len, int *string_len)
{
  instruction *inst;
  mem_addr i;
  
  for (i = from; i < to; i += 4)
  {
    READ_MEM_INST (inst, i);
    if (inst != NULL)
    {
      *string_len += print_inst_internal (&buf[*string_len], 1*K, inst, i);
      if ((*max_buf_len - *string_len) < 1*K)
      {
	/* Low memory: double buffer size and continue. */
	*max_buf_len = 2 * *max_buf_len;
	if ((buf = (char *) realloc (buf, *max_buf_len)) == 0)
	  fatal_error ("realloc failed\n");
      }
    }
  }
  return (buf);
}



/* Return a newly allocated string contain the contents of the data and
   stack segments. */

char *
data_seg_as_string (char *buf, int *max_buf_len, int *string_len)
{
  sprintf (&buf[*string_len], "\n\tDATA\n");
  *string_len += strlen (&buf[*string_len]);
  buf = mem_as_string (DATA_BOT, data_top, buf, max_buf_len, string_len);

  sprintf (&buf[*string_len], "\n\tSTACK\n");
  *string_len += strlen (&buf[*string_len]);
  buf = mem_as_string (ROUND_DOWN (R[29], BYTES_PER_WORD),
		       STACK_TOP - 4096,
		       buf,
		       max_buf_len,
		       string_len);

  sprintf (&buf[*string_len], "\n\tKERNEL DATA\n");
  *string_len += strlen (&buf[*string_len]);
  buf = mem_as_string (K_DATA_BOT, k_data_top, buf, max_buf_len, string_len);

  return (buf);
}


#define BYTES_PER_LINE (4*BYTES_PER_WORD)


/* Write a printable representation of the data in memory address
   FROM...TO to buffer BUF, which is of size LIMIT and whose next free
   location is N.  Return the, possible realloc'ed, buffer. */

char *
mem_as_string (mem_addr from, mem_addr to, char *buf, int *max_buf_len, int *string_len)
{
  mem_word val;
  mem_addr i = ROUND_UP (from, BYTES_PER_WORD);
  int j;
  
  i = print_partial_line (i, buf, max_buf_len, string_len);
  
  for ( ; i < to; )
  {
    /* Look for a block of 4 or more zero memory words */
    for (j = 0; i + j < to; j += BYTES_PER_WORD)
    {
      READ_MEM_WORD (val, i + j);
      if (val != 0)
	break;
    }
    if (i + j < to)
      j -= BYTES_PER_WORD;
    
    if (j >= 4 * BYTES_PER_WORD)
    {
      sprintf (&buf[*string_len], "[0x%08x]...[0x%08x]	0x00000000\n",
	i, i + j);
      buf = check_buf_limit (buf, max_buf_len, string_len);
      i = i + j;
      
      i = print_partial_line (i, buf, max_buf_len, string_len);
    }
    else
    {
      /* Otherwise, print the next four words on a single line */
      sprintf (&buf[*string_len], "[0x%08x]		      ", i);
      *string_len += strlen (&buf[*string_len]);
      do
      {
	READ_MEM_WORD (val, i);
	sprintf (&buf[*string_len], "  0x%08x", val);
	*string_len += strlen (&buf[*string_len]);
	i += BYTES_PER_WORD;
      }
      while (i % BYTES_PER_LINE != 0);
      sprintf (&buf[*string_len], "\n");
      buf = check_buf_limit (buf, max_buf_len, string_len);
    }
  }
  return (buf);
}



/* Check to see if the buffer is getting too full and, if so,
   reallocate it. */

static char *
check_buf_limit (char *buf, int *max_buf_len, int *string_len)
{
  *string_len += strlen (&buf[*string_len]);
  if ((*max_buf_len - *string_len) < 1*K)
  {
    *max_buf_len = 2 * *max_buf_len;
    if ((buf = (char *) realloc (buf, *max_buf_len)) == 0)
      fatal_error ("realloc failed\n");
  }
  return (buf);
}



/* Print out a line containing a fraction of a quadword.  */

static mem_addr
print_partial_line (mem_addr i, char *buf, int *max_buf_len, int *string_len)
{
  mem_word val;
  
  if ((i % BYTES_PER_LINE) != 0)
  {
    sprintf (&buf[*string_len], "[0x%08x]		      ", i);
    buf = check_buf_limit (buf, max_buf_len, string_len);
    
    for (; (i % BYTES_PER_LINE) != 0; i += BYTES_PER_WORD)
    {
      READ_MEM_WORD (val, i);
      sprintf (&buf[*string_len], "  0x%08x", val);
      buf = check_buf_limit (buf, max_buf_len, string_len);
    }
    
    sprintf (&buf[*string_len], "\n");
    buf = check_buf_limit (buf, max_buf_len, string_len);
  }
  
  return (i);
}

