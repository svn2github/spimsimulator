/* SPIM S20 MIPS simulator.
   Code to create, maintain and access memory.

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


/* $Header: /Software/SPIM/src/mem.c 18    3/06/04 4:32p Larus $
*/


#include "spim.h"
#include "spim-utils.h"
#include "inst.h"
#include "mem.h"
#include "reg.h"

/* Exported Variables: */

reg_word R[R_LENGTH];
reg_word HI, LO;
int HI_present, LO_present;
mem_addr PC, nPC;
double *FPR;			/* Dynamically allocate so overlay */
float *FGR;			/* is possible */
int *FWR;			/* is possible */
reg_word CCR[4][32], CPR[4][32];

instruction **text_seg;
int text_modified;		/* Non-zero means text segment was written */
mem_addr text_top;
mem_word *data_seg;
int data_modified;		/* Non-zero means a data segment was written */
short *data_seg_h;		/* Points to same vector as DATA_SEG */
BYTE_TYPE *data_seg_b;		/* Ditto */
mem_addr data_top;
mem_addr gp_midpoint;		/* Middle of $gp area */
mem_word *stack_seg;
short *stack_seg_h;		/* Points to same vector as STACK_SEG */
BYTE_TYPE *stack_seg_b;		/* Ditto */
mem_addr stack_bot;
instruction **k_text_seg;
mem_addr k_text_top;
mem_word *k_data_seg;
short *k_data_seg_h;
BYTE_TYPE *k_data_seg_b;
mem_addr k_data_top;


/* Local functions: */

static void free_instructions (register instruction **inst, int n);
static mem_word read_memory_mapped_IO (mem_addr addr);
static void write_memory_mapped_IO (mem_addr addr, mem_word value);


/* Local variables: */

static int32 data_size_limit, stack_size_limit, k_data_size_limit;



/* Memory is allocated in five chunks:
	text, data, stack, kernel text, and kernel data.

   The arrays are independent and have different semantics.

   text is allocated from 0x400000 up and only contains INSTRUCTIONs.
   It does not expand.

   data is allocated from 0x10000000 up.  It can be extended by the
   SBRK system call.  Programs can only read and write this segment.

   stack grows from 0x7fffefff down.  It is automatically extended.
   Programs can only read and write this segment.

   k_text is like text, except its is allocated from 0x80000000 up.

   k_data is like data, but is allocated from 0x90000000 up.

   Both kernel text and kernel data can only be accessed in kernel mode.
*/

/* The text segments contain pointers to instructions, not actual
   instructions, so they must be allocated large enough to hold as many
   pointers as there would be instructions (the two differ on machines in
   which pointers are not 32 bits long).  The following calculations round
   up in case size is not a multiple of BYTES_PER_WORD.  */

#define BYTES_TO_INST(N) (((N) + BYTES_PER_WORD - 1) / BYTES_PER_WORD * sizeof(instruction*))


void
make_memory (int text_size, int data_size, int data_limit,
	     int stack_size, int stack_limit, int k_text_size,
	     int k_data_size, int k_data_limit)
{
  if (data_size <= 65536)
    data_size = 65536;
  data_size = ROUND_UP(data_size, BYTES_PER_WORD); /* Keep word aligned */

  if (text_seg == NULL)
    text_seg = (instruction **) xmalloc (BYTES_TO_INST(text_size));
  else
    {
      free_instructions (text_seg, (text_top - TEXT_BOT) / BYTES_PER_WORD);
      text_seg = (instruction **) realloc (text_seg, BYTES_TO_INST(text_size));
    }
  memclr (text_seg, BYTES_TO_INST(text_size));
  text_top = TEXT_BOT + text_size;

  data_size = ROUND_UP(data_size, BYTES_PER_WORD); /* Keep word aligned */
  if (data_seg == NULL)
    data_seg = (mem_word *) xmalloc (data_size);
  else
    data_seg = (mem_word *) realloc (data_seg, data_size);
  memclr (data_seg, data_size);
  data_seg_b = (BYTE_TYPE *) data_seg;
  data_seg_h = (short *) data_seg;
  data_top = DATA_BOT + data_size;
  data_size_limit = data_limit;

  stack_size = ROUND_UP(stack_size, BYTES_PER_WORD); /* Keep word aligned */
  if (stack_seg == NULL)
    stack_seg = (mem_word *) xmalloc (stack_size);
  else
    stack_seg = (mem_word *) realloc (stack_seg, stack_size);
  memclr (stack_seg, stack_size);
  stack_seg_b = (BYTE_TYPE *) stack_seg;
  stack_seg_h = (short *) stack_seg;
  stack_bot = STACK_TOP - stack_size;
  stack_size_limit = stack_limit;

  if (k_text_seg == NULL)
    k_text_seg = (instruction **) xmalloc (BYTES_TO_INST(k_text_size));
  else
    {
      free_instructions (k_text_seg,
			 (k_text_top - K_TEXT_BOT) / BYTES_PER_WORD);
      k_text_seg = (instruction **) realloc(k_text_seg,
					    BYTES_TO_INST(k_text_size));
    }
  memclr (k_text_seg, BYTES_TO_INST(k_text_size));
  k_text_top = K_TEXT_BOT + k_text_size;

  k_data_size = ROUND_UP(k_data_size, BYTES_PER_WORD); /* Keep word aligned */
  if (k_data_seg == NULL)
    k_data_seg = (mem_word *) xmalloc (k_data_size);
  else
    k_data_seg = (mem_word *) realloc (k_data_seg, k_data_size);
  memclr (k_data_seg, k_data_size);
  k_data_seg_b = (BYTE_TYPE *) k_data_seg;
  k_data_seg_h = (short *) k_data_seg;
  k_data_top = K_DATA_BOT + k_data_size;
  k_data_size_limit = k_data_limit;

  text_modified = 1;
  data_modified = 1;
}


/* Free the storage used by the old instructions in memory. */

static void
free_instructions (register instruction **inst, int n)
{
  for ( ; n > 0; n --, inst ++)
    if (*inst)
      free_inst (*inst);
}


/* Expand the data segment by adding N bytes. */

void
expand_data (int addl_bytes)
{
  int delta = ROUND_UP(addl_bytes, BYTES_PER_WORD); /* Keep word aligned */
  int old_size = data_top - DATA_BOT;
  int new_size = old_size + delta;
  register BYTE_TYPE *p;

  if (addl_bytes < 0 || (source_file && new_size > data_size_limit))
    {
      error ("Can't expand data segment by %d bytes to %d bytes\n",
	     addl_bytes, new_size);
      run_error ("Use -ldata # with # > %d\n", new_size);
    }
  data_seg = (mem_word *) realloc (data_seg, new_size);
  if (data_seg == NULL)
    fatal_error ("realloc failed in expand_data\n");

  data_seg_b = (BYTE_TYPE *) data_seg;
  data_seg_h = (short *) data_seg;
  data_top += delta;

  /* Zero new memory */
  for (p = data_seg_b + old_size; p < data_seg_b + new_size; )
    *p ++ = 0;
}


/* Expand the stack segment by adding N bytes.  Can't use REALLOC
   since it copies from bottom of memory blocks and stack grows down from
   top of its block. */

void
expand_stack (int addl_bytes)
{
  int delta = ROUND_UP(addl_bytes, BYTES_PER_WORD); /* Keep word aligned */
  int old_size = STACK_TOP - stack_bot;
  int new_size = old_size + MAX (delta, old_size);
  mem_word *new_seg;
  register mem_word *po, *pn;

  if (addl_bytes < 0 || (source_file && new_size > stack_size_limit))
    {
      error ("Can't expand stack segment by %d bytes to %d bytes\n",
	     addl_bytes, new_size);
      run_error ("Use -lstack # with # > %d\n", new_size);
    }

  new_seg = (mem_word *) xmalloc (new_size);
  po = stack_seg + (old_size / BYTES_PER_WORD - 1);
  pn = new_seg + (new_size / BYTES_PER_WORD - 1);

  for ( ; po >= stack_seg ; ) *pn -- = *po --;
  for ( ; pn >= new_seg ; ) *pn -- = 0;

  free (stack_seg);
  stack_seg = new_seg;
  stack_seg_b = (BYTE_TYPE *) stack_seg;
  stack_seg_h = (short *) stack_seg;
  stack_bot -= (new_size - old_size);
}


/* Expand the kernel data segment by adding N bytes. */

void
expand_k_data (int addl_bytes)
{
  int delta = ROUND_UP(addl_bytes, BYTES_PER_WORD); /* Keep word aligned */
  int old_size = k_data_top - K_DATA_BOT;
  int new_size = old_size + delta;
  register BYTE_TYPE *p;

  if (addl_bytes < 0 || (source_file && new_size > k_data_size_limit))
    {
      error ("Can't expand kernel data segment by %d bytes to %d bytes\n",
	     addl_bytes, new_size);
      run_error ("Use -lkdata # with # > %d\n", new_size);
    }
  k_data_seg = (mem_word *) realloc (k_data_seg, new_size);
  if (k_data_seg == NULL)
    fatal_error ("realloc failed in expand_k_data\n");

  k_data_seg_b = (BYTE_TYPE *) k_data_seg;
  k_data_seg_h = (short *) k_data_seg;
  k_data_top += delta;

  /* Zero new memory */
  for (p = k_data_seg_b + old_size / BYTES_PER_WORD;
       p < k_data_seg_b + new_size / BYTES_PER_WORD; )
    *p ++ = 0;
}



/* Handle the infrequent and erroneous cases in the memory access macros. */

instruction *
bad_text_read (mem_addr addr)
{
  RAISE_EXCEPTION (IBUS_EXCPT, CP0_BadVAddr = addr);
  return (inst_decode (0));
}


void
bad_text_write (mem_addr addr, instruction *inst)
{
  RAISE_EXCEPTION (IBUS_EXCPT, CP0_BadVAddr = addr);
  SET_MEM_WORD (addr, ENCODING (inst));
}


mem_word
bad_mem_read (mem_addr addr, int mask, mem_word *dest)
{
  mem_word tmp;

  if (addr & mask)
    RAISE_EXCEPTION (ADDRL_EXCPT, CP0_BadVAddr = addr)
  else if (addr >= TEXT_BOT && addr < text_top)
    switch (mask)
      {
      case 0x0:
	tmp = ENCODING (text_seg [(addr - TEXT_BOT) >> 2]);
#ifdef BIGENDIAN
	tmp = (unsigned)tmp >> (8 * (3 - (addr & 0x3)));
#else
	tmp = (unsigned)tmp >> (8 * (addr & 0x3));
#endif
	return (0xff & tmp);

      case 0x1:
	tmp = ENCODING (text_seg [(addr - TEXT_BOT) >> 2]);
#ifdef BIGENDIAN
	tmp = (unsigned)tmp >> (8 * (2 - (addr & 0x2)));
#else
	tmp = (unsigned)tmp >> (8 * (addr & 0x2));
#endif
	return (0xffff & tmp);

      case 0x3:
	{
	instruction *inst = text_seg [(addr - TEXT_BOT) >> 2];
	if (inst == NULL)
	  return 0;
	else
	  return (ENCODING (inst));
	}

      default:
	run_error ("Bad mask (0x%x) in bad_mem_read\n", mask);
      }
  else if (addr > data_top
	   && addr < stack_bot
	   /* If more than 16 MB below stack, probably is bad data ref */
	   && addr > stack_bot - 16*K*K)
    {
      /* Grow stack segment */
      expand_stack (stack_bot - addr + 4);
      *dest = 0;		/* Newly allocated memory */
      return (0);
    }
  else if (MM_IO_BOT <= addr && addr <= MM_IO_TOP)
    return (read_memory_mapped_IO (addr));
  else
    /* Address out of range */
    RAISE_EXCEPTION (DBUS_EXCPT, CP0_BadVAddr = addr)
  return (0);
}


void
bad_mem_write (mem_addr addr, mem_word value, int mask)
{
  mem_word tmp;
  
  if (addr & mask)
    /* Unaligned address fault */
    RAISE_EXCEPTION (ADDRS_EXCPT, CP0_BadVAddr = addr)
    else if (addr >= TEXT_BOT && addr < text_top)
  {
    switch (mask)
    {
    case 0x0:
      tmp = ENCODING (text_seg [(addr - TEXT_BOT) >> 2]);
#ifdef BIGENDIAN
      tmp = ((tmp & ~(0xff << (8 * (3 - (addr & 0x3)))))
	       | (value & 0xff) << (8 * (3 - (addr & 0x3))));
#else
      tmp = ((tmp & ~(0xff << (8 * (addr & 0x3))))
	       | (value & 0xff) << (8 * (addr & 0x3)));
#endif
      text_seg [(addr - TEXT_BOT) >> 2] = inst_decode (tmp);
      break;
      
    case 0x1:
      tmp = ENCODING (text_seg [(addr - TEXT_BOT) >> 2]);
#ifdef BIGENDIAN
      tmp = ((tmp & ~(0xffff << (8 * (2 - (addr & 0x2)))))
	       | (value & 0xffff) << (8 * (2 - (addr & 0x2))));
#else
      tmp = ((tmp & ~(0xffff << (8 * (addr & 0x2))))
	       | (value & 0xffff) << (8 * (addr & 0x2)));
#endif
      text_seg [(addr - TEXT_BOT) >> 2] = inst_decode (tmp);
      break;
      
    case 0x3:
      text_seg [(addr - TEXT_BOT) >> 2] = inst_decode (value);
      break;
      
    default:
      run_error ("Bad mask (0x%x) in bad_mem_read\n", mask);
    }
    
    text_modified = 1;
  }
  else if (addr > data_top
	   && addr < stack_bot
	   /* If more than 16 MB below stack, probably is bad data ref */
	   && addr > stack_bot - 16*K*K)
  {
    /* Grow stack segment */
    expand_stack (stack_bot - addr + 4);
    if (addr >= stack_bot)
    {
      if (mask == 0)
	stack_seg_b [addr - stack_bot] = (char)value;
      else if (mask == 1)
	stack_seg_h [(addr - stack_bot) >> 1] = (short)value;
      else
	stack_seg [(addr - stack_bot) >> 2] = value;
    }
    else
      RAISE_EXCEPTION (DBUS_EXCPT, CP0_BadVAddr = addr)
      
    data_modified = 1;
  }
  else if (MM_IO_BOT <= addr && addr <= MM_IO_TOP)
    write_memory_mapped_IO (addr, value);
  else
    /* Address out of range */
    RAISE_EXCEPTION (DBUS_EXCPT, CP0_BadVAddr = addr)
}



/* Memory-mapped IO routines: */

static long recv_control, recv_buffer, recv_buffer_filled;
static long trans_control, trans_buffer, trans_buffer_filled;


/* Every IO_INTERVAL time steps, check if input is available and output
   is possible.  If so, update the control registers and buffers. */

void
check_memory_mapped_IO ()
{
  static long mm_io_initialized = 0;

  if (!mm_io_initialized)
    {
      recv_control = RECV_READY;
      trans_control = TRANS_READY;
      mm_io_initialized = 1;
    }

  if (console_input_available ())
    {
      recv_buffer_filled -= IO_INTERVAL;
      if (recv_buffer_filled <= 0)
	{
	  recv_buffer = get_console_char ();
	  recv_control |= RECV_READY;
	  recv_buffer_filled = RECV_LATENCY;
	  if ((recv_control & RECV_INT_ENABLE)
	      && CP0_INTERRUPTS_ON
	      && (CP0_Status & RECV_INT_MASK))
	    RAISE_EXCEPTION (INT_EXCPT, CP0_Cause |= RECV_INT_MASK);
	}
    }
  else if (recv_buffer_filled <= 0)
    recv_control &= ~RECV_READY;

  if (trans_buffer_filled > 0)
    {
      trans_buffer_filled -= IO_INTERVAL;
      if (trans_buffer_filled <= 0)
	{
	  put_console_char ((char)trans_buffer);
	  trans_control |= TRANS_READY;
	  trans_buffer_filled = 0;
	  if ((trans_control & TRANS_INT_ENABLE)
	      && CP0_INTERRUPTS_ON
	      && (CP0_Status & TRANS_INT_MASK))
	    RAISE_EXCEPTION (INT_EXCPT, CP0_Cause |= TRANS_INT_MASK)
	}
    }
}


/* Invoked on a write in the memory-mapped IO area. */

static void
write_memory_mapped_IO (mem_addr addr, mem_word value)
{
  switch (addr)
    {
    case TRANS_CTRL_ADDR:
      trans_control = ((trans_control & ~TRANS_INT_ENABLE)
		       | (value & TRANS_INT_ENABLE));

      if ((trans_control & TRANS_READY)
	  && (trans_control & TRANS_INT_ENABLE)
	  && CP0_INTERRUPTS_ON
	  && (CP0_Status & TRANS_INT_MASK))
	/* Raise an interrupt immediately on enabling a ready xmitter */
	RAISE_EXCEPTION (INT_EXCPT, CP0_Cause |= TRANS_INT_MASK)
      break;

    case TRANS_BUFFER_ADDR:
      if (trans_control & TRANS_READY) /* Ignore if not ready */
	{
	  trans_buffer = value & 0xff;
	  trans_control &= ~TRANS_READY;
	  trans_buffer_filled = TRANS_LATENCY;
	}
      break;

    case RECV_CTRL_ADDR:
      recv_control = ((recv_control & ~RECV_INT_ENABLE)
		      | (value & RECV_INT_ENABLE));
      break;

    case RECV_BUFFER_ADDR:
      break;

    default:
      run_error ("Write to unused memory-mapped IO address (0x%x)\n",
		 addr);
    }
}


/* Invoked on a read in the memory-mapped IO area. */

static mem_word
read_memory_mapped_IO (mem_addr addr)
{
  switch (addr)
    {
    case TRANS_CTRL_ADDR:
      return (trans_control);

    case TRANS_BUFFER_ADDR:
      return (trans_buffer & 0xff);

    case RECV_CTRL_ADDR:
      return (recv_control);

    case RECV_BUFFER_ADDR:
      recv_control &= ~RECV_READY;
      recv_buffer_filled = 0;
      return (recv_buffer & 0xff);

    default:
      run_error ("Read from unused memory-mapped IO address (0x%x)\n",
		 addr);
      return (0);
    }
}



/* Misc. routines */

void
print_mem (mem_addr addr)
{
  mem_word value;

  if (addr & 0x3)
    addr &= ~0x3;		/* Address must be word-aligned */

  if (TEXT_BOT <= addr && addr < text_top)
    print_inst (addr);
  else if (DATA_BOT <= addr && addr < data_top)
    {
      READ_MEM_WORD (value, addr);
      write_output (message_out, "Data seg @ 0x%08x (%d) = 0x%08x (%d)\n",
		    addr, addr, value, value);
    }
  else if (stack_bot <= addr && addr < STACK_TOP)
    {
      READ_MEM_WORD (value, addr);
      write_output (message_out, "Stack seg @ 0x%08x (%d) = 0x%08x (%d)\n",
		    addr, addr, value, value);
    }
  else if (K_TEXT_BOT <= addr && addr < k_text_top)
    print_inst (addr);
  else if (K_DATA_BOT <= addr && addr < k_data_top)
    {
      READ_MEM_WORD (value, addr);
      write_output (message_out,
		    "Kernel Data seg @ 0x%08x (%d) = 0x%08x (%d)\n",
		    addr, addr, value, value);
    }
  else
    error ("Address 0x%08x (%d) to print_mem is out of bounds\n", addr, addr);
}
