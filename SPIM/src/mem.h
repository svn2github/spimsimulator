/* SPIM S20 MIPS simulator.
   Macros for accessing memory.

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


/*   $Header: /Software/SPIM/src/mem.h 8     3/07/04 4:10p Larus $
*/


/* A note on directions:  "Bottom" of memory is the direction of
   decreasing addresses.  "Top" is the direction of increasing addresses.*/


/* Type of contents of a memory word. */

typedef int32 mem_word;


/* The text segment and boundaries. */

extern instruction **text_seg;

extern int text_modified;	/* Non-zero means text segment was written */

#define TEXT_BOT ((mem_addr) 0x400000)

extern mem_addr text_top;


/* Amount to grow text segment when we run out of space for instructions. */

#define TEXT_CHUNK_SIZE	4096


/* The data segment and boundaries. */

extern mem_word *data_seg;

extern int data_modified;	/* Non-zero means a data segment was written */

extern short *data_seg_h;	/* Points to same vector as DATA_SEG */

#define BYTE_TYPE signed char


extern BYTE_TYPE *data_seg_b;	/* Ditto */

#define DATA_BOT ((mem_addr) 0x10000000)

extern mem_addr data_top;

extern mem_addr gp_midpoint;	/* Middle of $gp area */


/* The stack segment and boundaries. */

extern mem_word *stack_seg;

extern short *stack_seg_h;	/* Points to same vector as STACK_SEG */

extern BYTE_TYPE *stack_seg_b;	/* Ditto */

extern mem_addr stack_bot;

/* Exclusive, but include 4K at top of stack. */

#define STACK_TOP ((mem_addr) 0x80000000)


/* The kernel text segment and boundaries. */

extern instruction **k_text_seg;

#define K_TEXT_BOT ((mem_addr) 0x80000000)

extern mem_addr k_text_top;


/* Kernel data segment and boundaries. */

extern mem_word *k_data_seg;

extern short *k_data_seg_h;

extern BYTE_TYPE *k_data_seg_b;

#define K_DATA_BOT ((mem_addr) 0x90000000)

extern mem_addr k_data_top;


/* Memory-mapped IO area: */
#define MM_IO_BOT		((mem_addr) 0xffff0000)
#define MM_IO_TOP		((mem_addr) 0xffffffff)


/* Read from console: */
#define RECV_CTRL_ADDR		((mem_addr) 0xffff0000)
#define RECV_BUFFER_ADDR	((mem_addr) 0xffff0004)

#define RECV_READY		0x1
#define RECV_INT_ENABLE		0x2

#define RECV_INT_MASK		CP0_Cause_IP3 /* HW Interrupt 1 */


/* Write to console: */
#define TRANS_CTRL_ADDR		((mem_addr) 0xffff0008)
#define TRANS_BUFFER_ADDR	((mem_addr) 0xffff000c)

#define TRANS_READY		0x1
#define TRANS_INT_ENABLE	0x2

#define TRANS_INT_MASK		CP0_Cause_IP2 /* HW Interrupt 0 */




/* Translate from SPIM memory address to physical address */

#define MEM_ADDRESS(ADDR)						   \
((((mem_addr) (ADDR) >= TEXT_BOT) && ((mem_addr) (ADDR) < text_top))	   \
 ? (mem_addr) (ADDR) - TEXT_BOT + (char*) text_seg			   \
 : ((((mem_addr) (ADDR) >= DATA_BOT) && ((mem_addr) (ADDR) < data_top))	   \
    ? (mem_addr) (ADDR) - DATA_BOT + (char*) data_seg		   \
    : ((((mem_addr) (ADDR) >= stack_bot) && ((mem_addr) (ADDR) < STACK_TOP)) \
       ? (mem_addr) (ADDR) - stack_bot + (char*) stack_seg		   \
       : ((((mem_addr) (ADDR) >= K_TEXT_BOT) && ((mem_addr) (ADDR) < k_text_top)) \
	  ? (mem_addr) (ADDR) - K_TEXT_BOT + (char*) k_text_seg		   \
	  : ((((mem_addr) (ADDR) >= K_DATA_BOT) && ((mem_addr) (ADDR) < k_data_top)) \
	     ? (mem_addr) (ADDR) - K_DATA_BOT + (char*) k_data_seg	   \
	     : (void*)run_error ("Memory address out of bounds\n"))))))

#define READ_MEM_INST(LOC, ADDR)					   \
{register mem_addr _addr_ = (mem_addr) (ADDR);				   \
   if (_addr_ >= TEXT_BOT && _addr_ < text_top && !(_addr_ & 0x3))	   \
     LOC = text_seg [(_addr_ - TEXT_BOT) >> 2];				   \
   else if (_addr_ >= K_TEXT_BOT && _addr_ < k_text_top && !(_addr_ & 0x3))\
     LOC = k_text_seg [(_addr_ - K_TEXT_BOT) >> 2];			   \
   else LOC = bad_text_read (_addr_);}


#define READ_MEM_BYTE(LOC, ADDR)					   \
{register mem_addr _addr_ = (mem_addr) (ADDR);				   \
   if (_addr_ >= DATA_BOT && _addr_ < data_top)				   \
    LOC = data_seg_b [_addr_ - DATA_BOT];				   \
   else if (_addr_ >= stack_bot && _addr_ < STACK_TOP)			   \
     LOC = stack_seg_b [_addr_ - stack_bot];				   \
   else if (_addr_ >= K_DATA_BOT && _addr_ < k_data_top)		   \
    LOC = k_data_seg_b [_addr_ - K_DATA_BOT];				   \
   else									   \
     LOC = bad_mem_read (_addr_, 0, (mem_word *)&LOC);}


#define READ_MEM_HALF(LOC, ADDR)					   \
{register mem_addr _addr_ = (mem_addr) (ADDR);				   \
   if (_addr_ >= DATA_BOT && _addr_ < data_top && !(_addr_ & 0x1))	   \
     LOC = data_seg_h [(_addr_ - DATA_BOT) >> 1];			   \
  else if (_addr_ >= stack_bot && _addr_ < STACK_TOP && !(_addr_ & 0x1))   \
    LOC = stack_seg_h [(_addr_ - stack_bot) >> 1];			   \
   else if (_addr_ >= K_DATA_BOT && _addr_ < k_data_top && !(_addr_ & 0x1))\
     LOC = k_data_seg_h [(_addr_ - K_DATA_BOT) >> 1];			   \
  else									   \
    LOC = bad_mem_read (_addr_, 0x1, (mem_word *)&LOC);}


#define READ_MEM_WORD(LOC, ADDR)					   \
{register mem_addr _addr_ = (mem_addr) (ADDR);				   \
   if (_addr_ >= DATA_BOT && _addr_ < data_top && !(_addr_ & 0x3))	   \
     LOC = data_seg [(_addr_ - DATA_BOT) >> 2];				   \
  else if (_addr_ >= stack_bot && _addr_ < STACK_TOP && !(_addr_ & 0x3))   \
    LOC = stack_seg [(_addr_ - stack_bot) >> 2];			   \
   else if (_addr_ >= K_DATA_BOT && _addr_ < k_data_top && !(_addr_ & 0x3))\
     LOC = k_data_seg [(_addr_ - K_DATA_BOT) >> 2];			   \
  else									   \
    LOC = bad_mem_read (_addr_, 0x3, (mem_word *)&LOC);}


#define SET_MEM_INST(ADDR, INST)					   \
{register mem_addr _addr_ = (mem_addr) (ADDR);				   \
   text_modified = 1;							   \
   if (_addr_ >= TEXT_BOT && _addr_ < text_top && !(_addr_ & 0x3))	   \
     text_seg [(_addr_ - TEXT_BOT) >> 2] = INST;			   \
   else if (_addr_ >= K_TEXT_BOT && _addr_ < k_text_top && !(_addr_ & 0x3))\
     k_text_seg [(_addr_ - K_TEXT_BOT) >> 2] = INST;			   \
   else bad_text_write (_addr_, INST);}


#define SET_MEM_BYTE(ADDR, VALUE)					   \
{register mem_addr _addr_ = (mem_addr) (ADDR);				   \
   data_modified = 1;							   \
   if (_addr_ >= DATA_BOT && _addr_ < data_top)				   \
     data_seg_b [_addr_ - DATA_BOT] = (unsigned char) (VALUE);		   \
   else if (_addr_ >= stack_bot && _addr_ < STACK_TOP)			   \
     stack_seg_b [_addr_ - stack_bot] = (unsigned char) (VALUE);	   \
   else if (_addr_ >= K_DATA_BOT && _addr_ < k_data_top)		   \
     k_data_seg_b [_addr_ - K_DATA_BOT] = (unsigned char) (VALUE);	   \
   else bad_mem_write (_addr_, VALUE, 0);}


#define SET_MEM_HALF(ADDR, VALUE)					   \
{register mem_addr _addr_ = (mem_addr) (ADDR);				   \
   data_modified = 1;							   \
   if (_addr_ >= DATA_BOT && _addr_ < data_top && !(_addr_ & 0x1))	   \
     data_seg_h [(_addr_ - DATA_BOT) >> 1] = (unsigned short) (VALUE);	   \
   else if (_addr_ >= stack_bot && _addr_ < STACK_TOP && !(_addr_ & 0x1))  \
     stack_seg_h [(_addr_ - stack_bot) >> 1] = (unsigned short) (VALUE);   \
   else if (_addr_ >= K_DATA_BOT && _addr_ < k_data_top && !(_addr_ & 0x1))\
     k_data_seg_h [(_addr_ - K_DATA_BOT) >> 1] = (unsigned short) (VALUE); \
   else bad_mem_write (_addr_, VALUE, 0x1);}


#define SET_MEM_WORD(ADDR, VALUE)					   \
{register mem_addr _addr_ = (mem_addr) (ADDR);				   \
   data_modified = 1;							   \
   if (_addr_ >= DATA_BOT && _addr_ < data_top && !(_addr_ & 0x3))	   \
     data_seg [(_addr_ - DATA_BOT) >> 2] = (mem_word) (VALUE);		   \
   else if (_addr_ >= stack_bot && _addr_ < STACK_TOP && !(_addr_ & 0x3))  \
     stack_seg [(_addr_ - stack_bot) >> 2] = (mem_word) (VALUE);	   \
   else if (_addr_ >= K_DATA_BOT && _addr_ < k_data_top && !(_addr_ & 0x3))\
     k_data_seg [(_addr_ - K_DATA_BOT) >> 2] = (mem_word) (VALUE);	   \
   else bad_mem_write (_addr_, VALUE, 0x3);}




/* Exported functions: */

mem_word bad_mem_read (mem_addr addr, int mask, mem_word *dest);
void bad_mem_write (mem_addr addr, mem_word value, int mask);
instruction *bad_text_read (mem_addr addr);
void bad_text_write (mem_addr addr, instruction *inst);
void check_memory_mapped_IO ();
void expand_data (int addl_bytes);
void expand_k_data (int addl_bytes);
void expand_stack (int addl_bytes);
void make_memory (int text_size, int data_size, int data_limit,
		  int stack_size, int stack_limit, int k_text_size,
		  int k_data_size, int k_data_limit);
void print_mem (mem_addr addr);
