/* SPIM S20 MIPS simulator.
   Dump the op.h file in a readable format to allow checking of encodings.

   Copyright (C) 2004 by James Larus (larus@cs.wisc.edu).
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


/* $Header: $
*/



#include <stdio.h>

typedef struct inst_t
{
  char *opcode;

  union
  {
    unsigned int x;
    struct
    {
      unsigned int funct:6;
      unsigned int pad:10;
      unsigned int rt:5;
      unsigned int rs:5;
      unsigned int op:6;
    } f;
  };
} inst;


#define OP(a, b, c, d) {a, d},

inst ops [] = {
#include "op.h"
};


int
compare_ops (inst *p1, inst *p2)
{
  if (p1->f.op < p2->f.op)
    return (-1);
  else if (p1->f.op > p2->f.op)
    return (1);
  else
    {
      if (p1->f.rs < p2->f.rs)
	return (-1);
      else if (p1->f.rs > p2->f.rs)
	return (1);
      else
	{
	  if (p1->f.rt < p2->f.rt)
	    return (-1);
	  else if (p1->f.rt > p2->f.rt)
	    return (1);
	  else
	    {
	      if (p1->f.funct < p2->f.funct)
		return (-1);
	      else if (p1->f.funct > p2->f.funct)
		return (1);
	      else
		return 0;
	    }
	}
    }
}


main (int argc, char** argv)
{
  /* Remove pseudo ops (opcode == -1) from table */
  int empty, next;
  for (empty = 0, next = 0; next < (sizeof(ops) / sizeof(ops[0])); next += 1)
    {
      if (-1 == ops[next].x)
	{
	}
      else
	{
	  ops[empty] = ops[next];
	  empty += 1;
	}
    }

  /* Radix sort instructions by field: op, rs, rt, funct */
  qsort (ops, empty, sizeof(ops[0]), compare_ops);

  /* Print related instructions in groups */
  int i;
  for (i = 0; i < empty; i += 1)
    {
      if (0 < i && ops[i - 1].f.op != ops[i].f.op)
	printf ("\n");

      printf ("%10s  op=%2d  rs=%2d  rt=%2d  funct=%02x      0x%08x\n",
	      ops[i].opcode,
	      ops[i].f.op,
	      ops[i].f.rs,
	      ops[i].f.rt,
	      ops[i].f.funct,
	      ops[i].x);
    }
}
