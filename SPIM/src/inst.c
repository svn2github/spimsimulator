/* SPIM S20 MIPS simulator.
   Code to build assembly instructions and resolve symbolic labels.

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


/* $Header: /Software/SPIM/src/inst.c 10    12/24/00 1:37p Larus $
*/

#include <stdio.h>
#include <string.h>

#include "spim.h"
#include "spim-utils.h"
#include "inst.h"
#include "mem.h"
#include "reg.h"
#include "sym-tbl.h"
#include "parser.h"
#include "scanner.h"
#include "y.tab.h"
#include "data.h"


/* Local functions: */

#ifdef __STDC__
static int compare_pair_value (inst_info *p1, inst_info *p2);
static void i_type_inst_full_word (int opcode, int rt, int rs, imm_expr *expr,
				   int value_known, int32 value);
static void inst_cmp (instruction *inst1, instruction *inst2);
static instruction *make_r_type_inst (int opcode, int rd, int rs, int rt);
static instruction *mk_i_inst (uint32 value, int opcode, int rs,
			       int rt, int offset);
static instruction *mk_j_inst (uint32, int opcode, int target);
static instruction *mk_r_inst (uint32, int opcode, int rs,
			       int rt, int rd, int shamt);
static char* print_imm_expr (char *buf, unsigned int length, imm_expr *expr,
			     int base_reg);
static void produce_immediate (imm_expr *expr, int rt, int value_known, int32 value);
static void sort_name_table (void);
#else
static int compare_pair_value ();
static void i_type_inst_f ();
static void i_type_inst_full_word ();
static void inst_cmp ();
static instruction * make_r_type_inst ();
static instruction *mk_i_inst ();
static instruction *mk_j_inst ();
static instruction *mk_r_inst ();
static char* print_imm_expr ();
static void produce_immediate ();
static void sort_name_table ();
#endif


/* Local variables: */

/* Non-zero means store instructions in kernel, not user, text segment */

static int in_kernel = 0;

/* Instruction used as breakpoint by SPIM: */

static instruction *break_inst = NULL;


/* Locations for next instruction in user and kernel text segments */

static mem_addr next_text_pc;

static mem_addr next_k_text_pc;


#define INST_PC (in_kernel ? next_k_text_pc : next_text_pc)
#define BUMP_INST_PC(DELTA) {if (in_kernel) \
			       next_k_text_pc += DELTA; \
			       else next_text_pc += DELTA;}



/* Set ADDRESS at which the next instruction is stored. */

#ifdef __STDC__
void
text_begins_at_point (mem_addr addr)
#else
void
text_begins_at_point (addr)
     mem_addr addr;
#endif
{
  next_text_pc = addr;
}


#ifdef __STDC__
void
k_text_begins_at_point (mem_addr addr)
#else
void
k_text_begins_at_point (addr)
     mem_addr addr;
#endif
{
  next_k_text_pc = addr;
}


/* Set the location (in user or kernel text space) for the next instruction. */

#ifdef __STDC__
void
set_text_pc (mem_addr addr)
#else
void
set_text_pc (addr)
     mem_addr addr;
#endif
{
  if (in_kernel)
    next_k_text_pc = addr;
  else
    next_text_pc = addr;
}


/* Return address for next instruction, in appropriate text segment. */

#ifdef __STDC__
mem_addr
current_text_pc (void)
#else
mem_addr
current_text_pc ()
#endif
{
  return (INST_PC);
}


/* Increment the current text segement PC. */

#ifdef __STDC__
void
increment_text_pc (int delta)
#else
void
increment_text_pc (delta)
     int delta;
#endif
{
  BUMP_INST_PC (delta);
}


/* If FLAG is non-zero, next instruction goes to kernel text segment,
   otherwise it goes to user segment. */

#ifdef __STDC__
void
user_kernel_text_segment (int to_kernel)
#else
void
user_kernel_text_segment (to_kernel)
     int to_kernel;
#endif
{
  in_kernel = to_kernel;
}


/* Store an INSTRUCTION in memory at the next location. */

#ifdef __STDC__
void
store_instruction (instruction *inst)
#else
void
store_instruction (inst)
     instruction *inst;
#endif
{
  if (data_dir)
    {
      store_word (inst_encode (inst));
      free_inst (inst);
    }
  else if (text_dir)
    {
      exception_occurred = 0;
      SET_MEM_INST (INST_PC, inst);
      if (exception_occurred)
	error ("Invalid address (0x%08x) for instruction\n", INST_PC);
      else
	BUMP_INST_PC (BYTES_PER_WORD);
      if (inst != NULL)
	{
	  SET_SOURCE (inst, source_line ());
	  if (ENCODING (inst) == 0)
	    SET_ENCODING (inst, inst_encode (inst));
	}
    }
}



#ifdef __STDC__
void
i_type_inst_free (int opcode, int rt, int rs, imm_expr *expr)
#else
void
i_type_inst_free (opcode, rt, rs, expr)
     int opcode, rt, rs;
     imm_expr *expr;
#endif
{
  i_type_inst (opcode, rt, rs, expr);
  free (expr);
}


/* Produce an immediate instruction with the OPCODE, RT, RS, and IMM
   fields.  NB, because the immediate value may not fit in the field,
   this routine may produce more than one instruction.	On the bare
   machine, we resolve symbolic address, but they better produce values
   that fit into instruction's immediate field. */

#ifdef __STDC__
void
i_type_inst (int opcode, int rt, int rs, imm_expr *expr)
#else
void
i_type_inst (opcode, rt, rs, expr)
     int opcode, rt, rs;
     imm_expr *expr;
#endif
{
  instruction *inst = (instruction *) zmalloc (sizeof (instruction));

  SET_OPCODE (inst, opcode);
  SET_RS (inst, rs);
  SET_RT (inst, rt);
  SET_EXPR (inst, copy_imm_expr (expr));
  if (expr->symbol == NULL || SYMBOL_IS_DEFINED (expr->symbol))
    {
      /* Evaluate the instruction's expression. */
      int32 value = eval_imm_expr (expr);

      if (!bare_machine
	  && (((opcode == Y_ADDI_OP
		|| opcode == Y_ADDIU_OP
		|| opcode == Y_SLTI_OP
		|| opcode == Y_SLTIU_OP)
	       ? ((value & 0xffff8000) != 0
		  && (value & 0xffff8000) != 0xffff8000)
	       : (value & 0xffff0000) != 0)))
	{
	  free_inst (inst);
	  i_type_inst_full_word (opcode, rt, rs, expr, 1, value);
	  return;
	}
      else
	resolve_a_label (expr->symbol, inst);
    }
  else if (bare_machine || expr->bits != 0)
    /* Don't know expression's value, but only needed upper/lower 16-bits
       anyways. */
    record_inst_uses_symbol (inst, expr->symbol);
  else
    {
      /* Don't know the expressions's value and want all of its bits,
	 so assume that it will not produce a small result and generate
	 sequence for 32 bit value. */
      free_inst (inst);

      i_type_inst_full_word (opcode, rt, rs, expr, 0, 0);
      return;
    }

  store_instruction (inst);
}


/* The immediate value for an instruction will (or may) not fit in 16 bits.
   Build the value from its piece with separate instructions. */

#ifdef __STDC__
static void
i_type_inst_full_word (int opcode, int rt, int rs, imm_expr *expr,
		       int value_known, int32 value)
#else
static void
i_type_inst_full_word (opcode, rt, rs, expr, value_known, value)
     int opcode, rt, rs;
     imm_expr *expr;
     int value_known;
     int32 value;
#endif
{
  if (opcode_is_load_store (opcode))
    {
      int offset;

      if (expr->symbol != NULL
	  && expr->symbol->gp_flag
	  && rs == 0
	  && IMM_MIN <= (offset = expr->symbol->addr + expr->offset)
	  && offset <= IMM_MAX)
	{
	  i_type_inst_free (opcode, rt, REG_GP, make_imm_expr (offset, NULL, 0));
	}
      else if (value_known)
	{
	  int low, high;

	  high = (value >> 16) & 0xffff;
	  low = value & 0xffff;

	  if (high != 0 &&
	      !(high == 0xffff && (low & 0x8000)))
	    {
	      /* Some of high 16 bits are non-zero */
	      if (low & 0x8000)
		{
		  /* Adjust high 16, since load sign-extends low 16*/
		  high += 1;
		}

	      i_type_inst_free (Y_LUI_OP, 1, 0, const_imm_expr (high));
	      if (rs != 0)	/* Base register */
		{
		r_type_inst (Y_ADDU_OP, 1, 1, rs);
		}
	      i_type_inst_free (opcode, rt, 1, const_imm_expr (low));
	    }
	  else
	    {
	      /* Special case, sign-extension of low 16 bits sets high to 0xffff */
	      i_type_inst_free (opcode, rt, rs, const_imm_expr (low));
	    }
	}
      else
	{
	  /* Use $at */
	  /* Need to adjust if lower bits are negative */
	  i_type_inst_free (Y_LUI_OP, 1, 0, upper_bits_of_expr (expr));
	  if (rs != 0)		/* Base register */
	    {
	    r_type_inst (Y_ADDU_OP, 1, 1, rs);
	    }
	  i_type_inst_free (opcode, rt, 1, lower_bits_of_expr (expr));
	}
    }
  else if (opcode_is_branch (opcode))
    {
      /* This only allows branches +/- 32K, which is not correct! */
      i_type_inst_free (opcode, rt, rs, lower_bits_of_expr (expr));
    }
  else
    /* Computation instruction */
    {
      int offset;

      if (expr->symbol != NULL
	  && expr->symbol->gp_flag && rs == 0
	  && IMM_MIN <= (offset = expr->symbol->addr + expr->offset)
	  && offset <= IMM_MAX)
	{
	i_type_inst_free ((opcode == Y_LUI_OP ? Y_ADDIU_OP : opcode),
			  rt, REG_GP, make_imm_expr (offset, NULL, 0));
	}
      else
	{
	  /* Use $at */
	  if ((opcode == Y_ORI_OP
	       || opcode == Y_ADDI_OP
	       || opcode == Y_ADDIU_OP
	       || opcode == Y_LUI_OP)
	      && rs == 0)
	    {
	      produce_immediate(expr, rt, value_known, value);
	    }
	  else
	    {
	      produce_immediate(expr, 1, value_known, value);
	      r_type_inst (imm_op_to_op (opcode), rt, rs, 1);
	    }
	}
    }
}


#ifdef __STDC__
static void
produce_immediate (imm_expr *expr, int rt, int value_known, int32 value)
#else
static void
produce_immediate (expr, rt, value_known, value)
     imm_expr *expr;
     int rt;
     int value_known;
     int32 value;
#endif
{
  if (value_known && (value & 0xffff) == 0)
    {
      i_type_inst_free (Y_LUI_OP, rt, 0, upper_bits_of_expr (expr));
    }
  else if (value_known && (value & 0xffff0000) == 0)
    {
      i_type_inst_free (Y_ORI_OP, rt, 0, lower_bits_of_expr (expr));
    }
  else
    {
      i_type_inst_free (Y_LUI_OP, 1, 0, upper_bits_of_expr (expr));
      i_type_inst_free (Y_ORI_OP, rt, 1, lower_bits_of_expr(expr));
    }
}


/* Return a jump-type instruction with the given OPCODE and TARGET
   fields. NB, even the immediate value may not fit in the field, this
   routine will not produce more than one instruction. */

#ifdef __STDC__
void
j_type_inst (int opcode, imm_expr *target)
#else
void
j_type_inst (opcode, target)
     int opcode;
     imm_expr *target;
#endif
{
  instruction *inst = (instruction *) zmalloc (sizeof (instruction));

  SET_OPCODE(inst, opcode);
  target->offset = 0;		/* Not PC relative */
  target->pc_relative = 0;
  SET_EXPR (inst, copy_imm_expr (target));
  if (target->symbol == NULL || SYMBOL_IS_DEFINED (target->symbol))
    resolve_a_label (target->symbol, inst);
  else
    record_inst_uses_symbol (inst, target->symbol);
  store_instruction (inst);
}


/* Return a register-type instruction with the given OPCODE, RD, RS, and RT
   fields. */

#ifdef __STDC__
static instruction *
make_r_type_inst (int opcode, int rd, int rs, int rt)
#else
static instruction *
make_r_type_inst (opcode, rd, rs, rt)
     int opcode, rd, rs, rt;
#endif
{
  instruction *inst = (instruction *) zmalloc (sizeof (instruction));

  SET_OPCODE(inst, opcode);
  SET_RS(inst, rs);
  SET_RT(inst, rt);
  SET_RD(inst, rd);
  SHAMT(inst) = 0;
  return (inst);
}


/* Return a register-type instruction with the given OPCODE, RD, RS, and RT
   fields. */

#ifdef __STDC__
void
r_type_inst (int opcode, int rd, int rs, int rt)
#else
void
r_type_inst (opcode, rd, rs, rt)
     int opcode, rd, rs, rt;
#endif
{
  store_instruction (make_r_type_inst (opcode, rd, rs, rt));
}


/* Return a register-shift instruction with the given OPCODE, RD, RT, and
   SHAMT fields.*/

#ifdef __STDC__
void
r_sh_type_inst (int opcode, int rd, int rt, int shamt)
#else
void
r_sh_type_inst (opcode, rd, rt, shamt)
     int opcode, rd, rt, shamt;
#endif
{
  instruction *inst = make_r_type_inst (opcode, rd, 0, rt);

  SET_SHAMT(inst, shamt & 0x1f);
  store_instruction (inst);
}


/* Return a floating-point compare instruction with the given OPCODE,
   FS, and FT fields.*/

#ifdef __STDC__
void
r_cond_type_inst (int opcode, int rs, int rt)
#else
void
r_cond_type_inst (opcode, rs, rt)
     int opcode, rs, rt;
#endif
{
  instruction *inst = make_r_type_inst (opcode, 0, rs, rt);

  switch (opcode)
    {
    case Y_C_EQ_D_OP:
    case Y_C_EQ_S_OP:
      {
	COND(inst) = COND_EQ;
	break;
      }

    case Y_C_LE_D_OP:
    case Y_C_LE_S_OP:
      {
	COND(inst) = COND_IN | COND_LT | COND_EQ;
	break;
      }

    case Y_C_LT_D_OP:
    case Y_C_LT_S_OP:
      {
	COND(inst) = COND_IN | COND_LT;
	break;
      }

    case Y_C_NGE_D_OP:
    case Y_C_NGE_S_OP:
      {
	COND(inst) = COND_IN | COND_LT | COND_UN;
	break;
      }

    case Y_C_NGLE_D_OP:
    case Y_C_NGLE_S_OP:
      {
	COND(inst) = COND_IN | COND_UN;
	break;
      }

    case Y_C_NGL_D_OP:
    case Y_C_NGL_S_OP:
      {
	COND(inst) = COND_IN | COND_EQ | COND_UN;
	break;
      }

    case Y_C_NGT_D_OP:
    case Y_C_NGT_S_OP:
      {
	COND(inst) = COND_IN | COND_LT | COND_EQ | COND_UN;
	break;
      }

    case Y_C_OLT_D_OP:
    case Y_C_OLT_S_OP:
      {
	COND(inst) = COND_LT;
	break;
      }

    case Y_C_OLE_D_OP:
    case Y_C_OLE_S_OP:
      {
	COND(inst) = COND_LT | COND_EQ;
	break;
      }

    case Y_C_SEQ_D_OP:
    case Y_C_SEQ_S_OP:
      {
	COND(inst) = COND_IN | COND_EQ;
	break;
      }

    case Y_C_SF_D_OP:
    case Y_C_SF_S_OP:
      {
	COND(inst) = COND_IN;
	break;
      }

    case Y_C_F_D_OP:
    case Y_C_F_S_OP:
      {
	COND(inst) = 0;
	break;
      }

    case Y_C_UEQ_D_OP:
    case Y_C_UEQ_S_OP:
      {
	COND(inst) = COND_EQ | COND_UN;
	break;
      }

    case Y_C_ULT_D_OP:
    case Y_C_ULT_S_OP:
      {
	COND(inst) = COND_LT | COND_UN;
	break;
      }

    case Y_C_ULE_D_OP:
    case Y_C_ULE_S_OP:
      {
	COND(inst) = COND_LT | COND_EQ | COND_UN;
	break;
      }

    case Y_C_UN_D_OP:
    case Y_C_UN_S_OP:
      {
	COND(inst) = COND_UN;
	break;
      }
    }
  store_instruction (inst);
}


/* Make and return a deep copy of INST. */

#ifdef __STDC__
instruction *
copy_inst (instruction *inst)
#else
instruction *
copy_inst (inst)
instruction *inst;
#endif
{
  instruction *new_inst = (instruction *) xmalloc (sizeof (instruction));

  *new_inst = *inst;
  /*memcpy ((void*)new_inst, (void*)inst , sizeof (instruction));*/
  SET_EXPR (new_inst, copy_imm_expr (EXPR (inst)));
  return (new_inst);
}


#ifdef __STDC__
void
free_inst (instruction *inst)
#else
void
free_inst (inst)
instruction *inst;
#endif
{
  if (inst != break_inst)
    /* Don't free the breakpoint insructions since we only have one. */
    {
      if (EXPR (inst))
	free (EXPR (inst));
      free (inst);
    }
}



/* Maintain a table mapping from opcode to instruction name and
   instruction type.

   Table must be sorted before first use since its entries are
   alphabetical on name, not ordered by opcode. */

static int sorted_name_table = 0;	/* Non-zero => table sorted */


/* Map from opcode -> name/type. */

static inst_info name_tbl [] = {
#undef OP
#define OP(NAME, OPCODE, TYPE, R_OPCODE) {NAME, OPCODE, TYPE},
#include "op.h"
};


/* Compare the VALUE1 field of two INST_INFO entries in the format
   required by qsort. */

#ifdef __STDC__
static int
compare_pair_value (inst_info *p1, inst_info *p2)
#else
static int
compare_pair_value (p1, p2)
     inst_info *p1, *p2;
#endif
{
  if (p1->value1 < p2->value1)
    return (-1);
  else if (p1->value1 > p2->value1)
    return (1);
  else
    return (0);
}


/* Sort the opcode table on their key (the opcode value). */

#ifdef __STDC__
static void
sort_name_table (void)
#else
static void
sort_name_table ()
#endif
{
  qsort (name_tbl,
	 sizeof (name_tbl) / sizeof (inst_info),
	 sizeof (inst_info),
	 (QSORT_FUNC) compare_pair_value);
  sorted_name_table = 1;
}


/* Print the instruction stored at the memory ADDRESS. */

#ifdef __STDC__
void
print_inst (mem_addr addr)
#else
void
print_inst (addr)
     mem_addr addr;
#endif
{
  instruction *inst;
  char buf [1024];

  exception_occurred = 0;
  READ_MEM_INST (inst, addr);

  if (exception_occurred)
    {
      error ("Can't print instruction not in text segment (0x%08x)\n", addr);
      return;
    }
  print_inst_internal (buf, sizeof(buf), inst, addr);
  write_output (message_out, buf);
}


#ifdef __STDC__
int
print_inst_internal (char *buf, int length, instruction *inst, mem_addr addr)
#else
int
print_inst_internal (buf, length, inst, addr)
     char *buf;
     int length;
     instruction *inst;
     mem_addr addr;
#endif
{
  char *bp = buf;
  inst_info *entry;

  if (!sorted_name_table)
    sort_name_table ();

  sprintf (buf, "[0x%08x]\t", addr);
  buf += strlen (buf);
  if (inst == NULL)
    {
      sprintf (buf, "<none>\n");
      buf += strlen (buf);
      return (buf - bp);
    }
  entry = map_int_to_inst_info (name_tbl,
				sizeof (name_tbl) / sizeof (inst_info),
				OPCODE (inst));
  if (entry == NULL)
    {
      sprintf (buf, "<unknown instruction %d>\n", OPCODE (inst));
      buf += strlen (buf);
      return (buf - bp);
    }
  sprintf (buf, "0x%08x  %s", ENCODING (inst), entry->name);
  buf += strlen (buf);
  switch (entry->value2)
    {
    case B0_TYPE_INST:
      sprintf (buf, " %d", IDISP (inst));
      buf += strlen (buf);
      break;

    case B1_TYPE_INST:
      sprintf (buf, " $%d %d", RS (inst), IDISP (inst));
      buf += strlen (buf);
      break;

    case I1t_TYPE_INST:
      sprintf (buf, " $%d, %d", RT (inst), IMM (inst));
      buf += strlen (buf);
      break;

    case I2_TYPE_INST:
      sprintf (buf, " $%d, $%d, %d", RT (inst), RS (inst), IMM (inst));
      buf += strlen (buf);
      break;

    case B2_TYPE_INST:
      sprintf (buf, " $%d, $%d, %d", RS (inst), RT (inst), IDISP (inst));
      buf += strlen (buf);
      break;

    case I2a_TYPE_INST:
      sprintf (buf, " $%d, %d($%d)", RT (inst), IMM (inst), BASE (inst));
      buf += strlen (buf);
      break;

    case R1s_TYPE_INST:
      sprintf (buf, " $%d", RS (inst));
      buf += strlen (buf);
      break;

    case R1d_TYPE_INST:
      sprintf (buf, " $%d", RD (inst));
      buf += strlen (buf);
      break;

    case R2td_TYPE_INST:
      sprintf (buf, " $%d, $%d", RT (inst), RD (inst));
      buf += strlen (buf);
      break;

    case R2st_TYPE_INST:
      sprintf (buf, " $%d, $%d", RS (inst), RT (inst));
      buf += strlen (buf);
      break;

    case R2ds_TYPE_INST:
      sprintf (buf, " $%d, $%d", RD (inst), RS (inst));
      buf += strlen (buf);
      break;

    case R2sh_TYPE_INST:
      if (ENCODING (inst) == 0)
	{
	  buf -= 3;		/* zap sll */
	  sprintf (buf, "nop");
	}
      else
	sprintf (buf, " $%d, $%d, %d", RD (inst), RT (inst), SHAMT (inst));
      buf += strlen (buf);
      break;

    case R3_TYPE_INST:
      sprintf (buf, " $%d, $%d, $%d", RD (inst), RS (inst), RT (inst));
      buf += strlen (buf);
      break;

    case R3sh_TYPE_INST:
      sprintf (buf, " $%d, $%d, $%d", RD (inst), RT (inst), RS (inst));
      buf += strlen (buf);
      break;

    case FP_I2a_TYPE_INST:
      sprintf (buf, " $f%d, %d($%d)", FT (inst), IMM (inst), BASE (inst));
      buf += strlen (buf);
      break;

    case FP_R2ds_TYPE_INST:
      sprintf (buf, " $f%d, $f%d", FD (inst), FS (inst));
      buf += strlen (buf);
      break;

    case FP_CMP_TYPE_INST:
      sprintf (buf, " $f%d, $f%d", FS (inst), FT (inst));
      buf += strlen (buf);
      break;

    case FP_R3_TYPE_INST:
      sprintf (buf, " $f%d, $f%d, $f%d", FD (inst), FS (inst), FT (inst));
      buf += strlen (buf);
      break;

    case FP_MOV_TYPE_INST:
      sprintf (buf, " $f%d, $f%d", FD (inst), FS (inst));
      buf += strlen (buf);
      break;

    case J_TYPE_INST:
      sprintf (buf, " 0x%08x", TARGET (inst) << 2);
      buf += strlen (buf);
      break;

    case CP_TYPE_INST:
      sprintf (buf, " $%d, $%d", RT (inst), RD (inst));
      buf += strlen (buf);
      break;

    case NOARG_TYPE_INST:
      break;

    case ASM_DIR:
    case PSEUDO_OP:
    default:
      fatal_error ("Unknown instruction type in print_inst\n");
    }

  if (EXPR (inst) != NULL && EXPR (inst)->symbol != NULL)
    {
      sprintf (buf, " [");
      buf += strlen (buf);
      if (opcode_is_load_store (OPCODE (inst)))
	buf = print_imm_expr (buf, length - (buf - bp) - 2,
			      EXPR (inst), BASE (inst));
      else
	buf = print_imm_expr (buf, length - (buf - bp) - 2, EXPR (inst), -1);
      sprintf (buf, "]");
      buf += strlen (buf);
    }

  if (SOURCE (inst) != NULL && 10 < length - (buf - bp))
    {
      /* Comment is source line text of current line. */
      int gap_length = 57 - (buf - bp);
      int n = strlen (SOURCE (inst));
      int remaining;

      for ( ; 0 < gap_length; gap_length -= 1)
	{
	  sprintf (buf, " ");
	  buf += 1;
	}

      strcpy (buf, "; ");
      buf += strlen (buf);

      remaining = length - (buf - bp);
      if (n < remaining - 2)
	{
	  strncpy (buf, SOURCE (inst), n + 1);
	  buf += n;
	}
      else
	{
	  strncpy (buf, SOURCE (inst), remaining - 3);
	  strncpy (buf + remaining - 3, "...", 3);
	  buf += remaining;
	}
    }

  sprintf (buf, "\n");
  buf += strlen (buf);
  return (buf - bp);
}



/* Return non-zero if an INSTRUCTION is a conditional branch. */

#ifdef __STDC__
int
opcode_is_branch (int opcode)
#else
int
opcode_is_branch (opcode)
     int opcode;
#endif
{
  switch (opcode)
    {
    case Y_BEQ_OP:
    case Y_BEQZ_POP:
    case Y_BGE_POP:
    case Y_BGEU_POP:
    case Y_BGEZ_OP:
    case Y_BGEZAL_OP:
    case Y_BGT_POP:
    case Y_BGTU_POP:
    case Y_BGTZ_OP:
    case Y_BLE_POP:
    case Y_BLEU_POP:
    case Y_BLEZ_OP:
    case Y_BLT_POP:
    case Y_BLTU_POP:
    case Y_BLTZ_OP:
    case Y_BLTZAL_OP:
    case Y_BNE_OP:
    case Y_BNEZ_POP:
    case Y_BC1F_OP:
    case Y_BC1T_OP:
      return (1);

    default:
      return (0);
    }
}


/* Return non-zero if an INSTRUCTION is an conditional branch (jump). */

#ifdef __STDC__
int
opcode_is_jump (int opcode)
#else
int
opcode_is_jump (opcode)
     int opcode;
#endif
{
  switch (opcode)
    {
    case Y_J_OP:
    case Y_JAL_OP:
      return (1);

    default:
      return (0);
    }
}

/* Return non-zero if an INSTRUCTION is a load or store. */

#ifdef __STDC__
int
opcode_is_load_store (int opcode)
#else
int
opcode_is_load_store (opcode)
     int opcode;
#endif
{
  switch (opcode)
    {
    case Y_LB_OP: return (1);
    case Y_LBU_OP: return (1);
    case Y_LH_OP: return (1);
    case Y_LHU_OP: return (1);
    case Y_LW_OP: return (1);
    case Y_LWC0_OP: return (1);
    case Y_LWC1_OP: return (1);
    case Y_LWC2_OP: return (1);
    case Y_LWC3_OP: return (1);
    case Y_LWL_OP: return (1);
    case Y_LWR_OP: return (1);
    case Y_SB_OP: return (1);
    case Y_SH_OP: return (1);
    case Y_SW_OP: return (1);
    case Y_SWC0_OP: return (1);
    case Y_SWC1_OP: return (1);
    case Y_SWC2_OP: return (1);
    case Y_SWC3_OP: return (1);
    case Y_SWL_OP: return (1);
    case Y_SWR_OP: return (1);
    case Y_L_D_POP: return (1);
    case Y_L_S_POP: return (1);
    case Y_S_D_POP: return (1);
    case Y_S_S_POP: return (1);
    default: return (0);
    }
}


/* Return non-zero if a breakpoint is set at ADDR. */

#ifdef __STDC__
int
inst_is_breakpoint (mem_addr addr)
#else
int
inst_is_breakpoint (addr)
     mem_addr addr;
#endif
{
  instruction *old_inst;

  if (break_inst == NULL)
    break_inst = make_r_type_inst (Y_BREAK_OP, 1, 0, 0);

  READ_MEM_INST (old_inst, addr);
  return (old_inst == break_inst);
}


/* Set a breakpoint at ADDR and return the old instruction.  If the
   breakpoint cannot be set, return NULL. */

#ifdef __STDC__
instruction *
set_breakpoint (mem_addr addr)
#else
instruction *
set_breakpoint (addr)
     mem_addr addr;
#endif
{
  instruction *old_inst;

  if (break_inst == NULL)
    break_inst = make_r_type_inst (Y_BREAK_OP, 1, 0, 0);

  exception_occurred = 0;
  READ_MEM_INST (old_inst, addr);
  if (old_inst == break_inst)
    return (NULL);
  SET_MEM_INST (addr, break_inst);
  if (exception_occurred)
    return (NULL);
  else
    return (old_inst);
}



/* An immediate expression has the form: SYMBOL +/- IOFFSET, where either
   part may be omitted. */

/* Make and return a new immediate expression */

#ifdef __STDC__
imm_expr *
make_imm_expr (int offs, char *sym, int pc_rel)
#else
imm_expr *
make_imm_expr (offs, sym, pc_rel)
     int offs;
     char *sym;
     int pc_rel;
#endif
{
  imm_expr *expr = (imm_expr *) xmalloc (sizeof (imm_expr));

  expr->offset = offs;
  expr->bits = 0;
  expr->pc_relative = (short)pc_rel;
  if (sym != NULL)
    expr->symbol = lookup_label (sym);
  else
    expr->symbol = NULL;
  return (expr);
}


/* Return a shallow copy of the EXPRESSION. */

#ifdef __STDC__
imm_expr *
copy_imm_expr (imm_expr *old_expr)
#else
imm_expr *
copy_imm_expr (old_expr)
     imm_expr *old_expr;
#endif
{
  imm_expr *expr = (imm_expr *) xmalloc (sizeof (imm_expr));

  *expr = *old_expr;
  /*memcpy ((void*)expr, (void*)old_expr, sizeof (imm_expr));*/
  return (expr);
}


/* Return a shallow copy of an EXPRESSION that only uses the upper
   sixteen bits of the expression's value. */

#ifdef __STDC__
imm_expr *
upper_bits_of_expr (imm_expr *old_expr)
#else
imm_expr *
upper_bits_of_expr (old_expr)
     imm_expr *old_expr;
#endif
{
  imm_expr *expr = copy_imm_expr (old_expr);

  expr->bits = 1;
  return (expr);
}


/* Return a shallow copy of the EXPRESSION that only uses the lower
   sixteen bits of the expression's value. */

#ifdef __STDC__
imm_expr *
lower_bits_of_expr (imm_expr *old_expr)
#else
imm_expr *
lower_bits_of_expr (old_expr)
     imm_expr *old_expr;
#endif
{
  imm_expr *expr = copy_imm_expr (old_expr);

  expr->bits = -1;
  return (expr);
}


/* Return an instruction expression for a constant VALUE. */

#ifdef __STDC__
imm_expr *
const_imm_expr (int32 value)
#else
imm_expr *
const_imm_expr (value)
     int32 value;
#endif
{
  return (make_imm_expr (value, NULL, 0));
}


/* Return a shallow copy of the EXPRESSION with the offset field
   incremented by the given amount. */

#ifdef __STDC__
imm_expr *
incr_expr_offset (imm_expr *expr, int32 value)
#else
imm_expr *
incr_expr_offset (expr, value)
     imm_expr *expr;
     int32 value;
#endif
{
  imm_expr *new_expr = copy_imm_expr (expr);

  new_expr->offset += value;
  return (new_expr);
}


/* Return the value of the EXPRESSION. */

#ifdef __STDC__
int32
eval_imm_expr (imm_expr *expr)
#else
int32
eval_imm_expr (expr)
     imm_expr *expr;
#endif
{
  int32 value;

  if (expr->symbol == NULL)
    value = expr->offset;
  else if (SYMBOL_IS_DEFINED (expr->symbol))
    {
      value = expr->offset + expr->symbol->addr;
      if (expr->symbol->gp_flag) /* Addr is offset from $gp */
	value += gp_midpoint;
    }
  else
    {
      error ("Evaluated undefined symbol: %s\n", expr->symbol->name);
      value = 0;
    }
  if (expr->bits > 0)
    return ((value >> 16) & 0xffff);  /* Use upper bits of result */
  else if (expr->bits < 0)
    return (value & 0xffff);	      /* Use lower bits */
  else
    return (value);
}


/* Print the EXPRESSION. */

#ifdef __STDC__
static char*
print_imm_expr (char *buf, unsigned int length, imm_expr *expr, int base_reg)
#else
static char*
print_imm_expr (buf, length, expr, base_reg)
     char *buf;
     int length;
     imm_expr *expr;
     int base_reg;
#endif
{
  char lbuf[100];
  char* lbp = lbuf;

  if (expr->symbol != NULL)
    {
      unsigned int n = strlen (expr->symbol->name);
      if (n < length)
	{
	  strncpy (buf, expr->symbol->name, length);
	  buf += n;
	  length -= n;
	}
      else
	{
	  strncpy (buf, expr->symbol->name, length - 3);
	  strncpy (buf + length - 3, "...", 3);
	  buf += length;
	  length = 0;
	}
    }

  *lbp = '\0';
  if (expr->pc_relative)
    sprintf (lbp, "-0x%08x", -expr->offset);
  else if (expr->offset < -10)
    sprintf (lbp, "-%d (-0x%08x)", -expr->offset, -expr->offset);
  else if (expr->offset > 10)
    sprintf (lbp, "+%d (0x%08x)", expr->offset, expr->offset);
  lbp += strlen(lbp);

  if (base_reg != -1 && expr->symbol != NULL &&
      (expr->offset > 10 || expr->offset < -10))
    {
      if (expr->offset == 0 && base_reg != 0)
	sprintf (lbp, "+0");
      if (expr->offset != 0 || base_reg != 0)
	sprintf (lbp, "($%d)", base_reg);
    }
  lbp += strlen (lbp);

  if (length <= 0)
    ;
  else if (strlen (lbuf) < length)
    {
      strncpy (buf, lbuf, length);
      buf += strlen (buf);
    }
  else
    {
      strncpy (buf, lbuf, length - 3);
      strncpy (buf + length - 3, "...", 3);
      buf += length;
    }

  return (buf);
}


/* Return non-zero if the EXPRESSION is a constant 0. */

#ifdef __STDC__
int
zero_imm (imm_expr *expr)
#else
int
zero_imm (expr)
     imm_expr *expr;
#endif
{
  return (expr->offset == 0 && expr->symbol == NULL);
}



/* Return an address expression of the form SYMBOL +/- IOFFSET (REGISTER).
   Any of the three parts may be omitted. */

#ifdef __STDC__
addr_expr *
make_addr_expr (int offs, char *sym, int reg_no)
#else
addr_expr *
make_addr_expr (offs, sym, reg_no)
     int offs;
     char *sym;
     int reg_no;
#endif
{
  addr_expr *expr = (addr_expr *) xmalloc (sizeof (addr_expr));
  label *lab;

  if (reg_no == 0 && sym != NULL && (lab = lookup_label (sym))->gp_flag)
    {
      expr->reg_no = REG_GP;
      expr->imm = make_imm_expr (offs + lab->addr - gp_midpoint, NULL, 0);
    }
  else
    {
      expr->reg_no = (unsigned char)reg_no;
      expr->imm = make_imm_expr (offs, (sym ? str_copy (sym) : sym), 0);
    }
  return (expr);
}


#ifdef __STDC__
imm_expr *
addr_expr_imm (addr_expr *expr)
#else
imm_expr *
addr_expr_imm (expr)
addr_expr *expr;
#endif
{
  return (expr->imm);
}


#ifdef __STDC__
int
addr_expr_reg (addr_expr *expr)
#else
int
addr_expr_reg (expr)
addr_expr *expr;
#endif
{
  return (expr->reg_no);
}



/* Map between a SPIM instruction and the binary representation of the
   instruction. */


/* Maintain a table mapping from internal opcode (i_opcode) to actual
   opcode (a_opcode).  Table must be sorted before first use since its
   entries are alphabetical on name, not ordered by opcode. */

static int sorted_i_opcode_table = 0; /* Non-zero => table sorted */


/* Map from internal opcode -> real opcode */

static inst_info i_opcode_tbl [] = {
#undef OP
#define OP(NAME, I_OPCODE, TYPE, A_OPCODE) {NAME, I_OPCODE, (int)A_OPCODE},
#include "op.h"
};


/* Sort the opcode table on their key (the interal opcode value). */

#ifdef __STDC__
static void
sort_i_opcode_table (void)
#else
static void
sort_i_opcode_table ()
#endif
{
  qsort (i_opcode_tbl,
	 sizeof (i_opcode_tbl) / sizeof (inst_info),
	 sizeof (inst_info),
	 (QSORT_FUNC) compare_pair_value);
  sorted_i_opcode_table = 1;
}


#define REGS(R,O) (((R) & 0x1f) << O)


#ifdef __STDC__
int32
inst_encode (instruction *inst)
#else
int32
inst_encode (inst)
     instruction *inst;
#endif
{
  int32 a_opcode = 0;
  inst_info *entry;

  if (inst == NULL)
    return (0);
  if (!sorted_i_opcode_table)
    sort_i_opcode_table ();
  if (!sorted_name_table)
    sort_name_table ();

  entry = map_int_to_inst_info (i_opcode_tbl,
				sizeof (i_opcode_tbl) / sizeof (inst_info),
				OPCODE (inst));
  if (entry == NULL)
    return 0;

  a_opcode = entry->value2;
  entry = map_int_to_inst_info (name_tbl,
				sizeof (name_tbl) / sizeof (inst_info),
				OPCODE (inst));

  switch (entry->value2)
    {
    case B0_TYPE_INST:
      return (a_opcode
	      | (IOFFSET (inst) & 0xffff));

    case B1_TYPE_INST:
      return (a_opcode
	      | REGS (RS (inst), 21)
	      | (IOFFSET (inst) & 0xffff));

    case I1t_TYPE_INST:
      return (a_opcode
	      | REGS (RS (inst), 21)
	      | REGS (RT (inst), 16)
	      | (IMM (inst) & 0xffff));

    case I2_TYPE_INST:
    case B2_TYPE_INST:
      return (a_opcode
	      | REGS (RS (inst), 21)
	      | REGS (RT (inst), 16)
	      | (IMM (inst) & 0xffff));

    case I2a_TYPE_INST:
      return (a_opcode
	      | REGS (BASE (inst), 21)
	      | REGS (RT (inst), 16)
	      | (IOFFSET (inst) & 0xffff));

    case R1s_TYPE_INST:
      return (a_opcode
	      | REGS (RS (inst), 21));

    case R1d_TYPE_INST:
      return (a_opcode
	      | REGS (RD (inst), 11));

    case R2td_TYPE_INST:
      return (a_opcode
	      | REGS (RT (inst), 16)
	      | REGS (RD (inst), 11));

    case R2st_TYPE_INST:
      return (a_opcode
	      | REGS (RS (inst), 21)
	      | REGS (RT (inst), 16));

    case R2ds_TYPE_INST:
      return (a_opcode
	      | REGS (RS (inst), 21)
	      | REGS (RD (inst), 11));

    case R2sh_TYPE_INST:
      return (a_opcode
	      | REGS (RT (inst), 16)
	      | REGS (RD (inst), 11)
	      | REGS (SHAMT (inst), 6));

    case R3_TYPE_INST:
      return (a_opcode
	      | REGS (RS (inst), 21)
	      | REGS (RT (inst), 16)
	      | REGS (RD (inst), 11));

    case R3sh_TYPE_INST:
      return (a_opcode
	      | REGS (RS (inst), 21)
	      | REGS (RT (inst), 16)
	      | REGS (RD (inst), 11));

    case FP_I2a_TYPE_INST:
      return (a_opcode
	      | REGS (BASE (inst), 21)
	      | REGS (RT (inst), 16)
	      | (IOFFSET (inst) & 0xffff));

    case FP_R2ds_TYPE_INST:
      return (a_opcode
	      | REGS (FS (inst), 11)
	      | REGS (FD (inst), 6));

    case FP_CMP_TYPE_INST:
      return (a_opcode
	      | REGS (FT (inst), 16)
	      | REGS (FS (inst), 11)
	      | (COND (inst) & 0xf));

    case FP_R3_TYPE_INST:
      return (a_opcode
	      | REGS (FT (inst), 16)
	      | REGS (FS (inst), 11)
	      | REGS (FD (inst), 6));

    case FP_MOV_TYPE_INST:
      return (a_opcode
	      | REGS (FS (inst), 11)
	      | REGS (FD (inst), 6));

    case J_TYPE_INST:
      return (a_opcode
	      | TARGET (inst));

    case CP_TYPE_INST:
      return (a_opcode
	      | REGS (RT (inst), 16)
	      | REGS (RD (inst), 11));

    case NOARG_TYPE_INST:
      return (a_opcode);

    case ASM_DIR:
    case PSEUDO_OP:
    default:
      fatal_error ("Unknown instruction type in inst_encoding\n");
      return (0);		/* Not reached */
    }
}


/* Maintain a table mapping from actual opcode to interal opcode.
   Table must be sorted before first use since its entries are
   alphabetical on name, not ordered by opcode. */

static int sorted_a_opcode_table = 0; /* Non-zero => table sorted */


/* Map from internal opcode -> real opcode */

static inst_info a_opcode_tbl [] = {
#undef OP
#define OP(NAME, I_OPCODE, TYPE, A_OPCODE) {NAME, (int)A_OPCODE, (int)I_OPCODE},
#include "op.h"
};


/* Sort the opcode table on their key (the interal opcode value). */

#ifdef __STDC__
static void
sort_a_opcode_table (void)
#else
static void
sort_a_opcode_table ()
#endif
{
  qsort (a_opcode_tbl,
	 sizeof (a_opcode_tbl) / sizeof (inst_info),
	 sizeof (inst_info),
	 (QSORT_FUNC) compare_pair_value);
  sorted_a_opcode_table = 1;
}


#define REG(V,O) ((V) >> O) & 0x1f


#ifdef __STDC__
instruction *
  inst_decode (uint32 value)
#else
instruction *
  inst_decode (value)
uint32 value;
#endif
{
  int32 a_opcode = value & 0xfc000000;
  inst_info *entry;
  int32 i_opcode;

  if (a_opcode == 0)		/* SPECIAL */
    a_opcode |= (value & 0x3f);
  else if (a_opcode == 0x04000000) /* BCOND */
    a_opcode |= (value & 0x001f0000);
  else if (a_opcode == 0x40000000) /* COP0 */
    a_opcode |= (value & 0x03e00000) | (value & 0x1f);
  else if (a_opcode == 0x44000000) /* COP1 */
    {
      a_opcode |= (value & 0x03e00000);
      if ((value & 0xff000000) == 0x45000000)
	a_opcode |= (value & 0x00010000); /* BC1f/t */
      else
	a_opcode |= (value & 0x3f);
    }
  else if (a_opcode == 0x48000000 /* COPz */
	   || a_opcode == 0x4c000000)
    a_opcode |= (value & 0x03e00000);


  if (!sorted_a_opcode_table)
    sort_a_opcode_table ();
  if (!sorted_name_table)
    sort_name_table ();

  entry = map_int_to_inst_info (a_opcode_tbl,
				sizeof (a_opcode_tbl) / sizeof (inst_info),
				a_opcode);
  if (entry == NULL)
    return (mk_r_inst (value, 0, 0, 0, 0, 0)); /* Invalid inst */

  i_opcode = entry->value2;

  switch (map_int_to_inst_info (name_tbl,
				sizeof (name_tbl) / sizeof (inst_info),
				i_opcode)->value2)
    {
    case B0_TYPE_INST:
      return (mk_i_inst (value, i_opcode, 0, 0, value & 0xffff));

    case B1_TYPE_INST:
      return (mk_i_inst (value, i_opcode, REG (value, 21), 0, value & 0xffff));

    case I1t_TYPE_INST:
      return (mk_i_inst (value, i_opcode, REG (value, 21), REG (value, 16),
			 value & 0xffff));

    case I2_TYPE_INST:
    case B2_TYPE_INST:
      return (mk_i_inst (value, i_opcode, REG (value, 21), REG (value, 16),
			 value & 0xffff));

    case I2a_TYPE_INST:
      return (mk_i_inst (value, i_opcode, REG (value, 21), REG (value, 16),
			 value & 0xffff));

    case R1s_TYPE_INST:
      return (mk_r_inst (value, i_opcode, REG (value, 21), 0, 0, 0));

    case R1d_TYPE_INST:
      return (mk_r_inst (value, i_opcode, 0, 0, REG (value, 11), 0));

    case R2td_TYPE_INST:
      return (mk_r_inst (value, i_opcode, 0, REG (value, 16), REG (value, 11),
			 0));

    case R2st_TYPE_INST:
      return (mk_r_inst (value, i_opcode, REG (value, 21), REG (value, 16),
			 0, 0));

    case R2ds_TYPE_INST:
      return (mk_r_inst (value, i_opcode, REG (value, 21), 0, REG (value, 11),
			 0));

    case R2sh_TYPE_INST:
      return (mk_r_inst (value, i_opcode, 0, REG (value, 16), REG (value, 11),
			 REG (value, 6)));

    case R3_TYPE_INST:
      return (mk_r_inst (value, i_opcode, REG (value, 21), REG (value, 16),
			 REG (value, 11), 0));

    case R3sh_TYPE_INST:
      return (mk_r_inst (value, i_opcode, REG (value, 21), REG (value, 16),
			 REG (value, 11), 0));

    case FP_I2a_TYPE_INST:
      return (mk_i_inst (value, i_opcode, REG (value, 21), REG (value, 16),
			 value & 0xffff));

    case FP_R2ds_TYPE_INST:
      return (mk_r_inst (value, i_opcode, REG (value, 11), 0, REG (value, 6),
			 0));

    case FP_CMP_TYPE_INST:
      {
	instruction *inst = mk_r_inst (value, i_opcode, REG (value, 11),
				       REG (value, 16), 0, 0);
	SET_COND (inst, value & 0xf);
	return (inst);
      }

    case FP_R3_TYPE_INST:
      return (mk_r_inst (value, i_opcode, REG (value, 11), REG (value, 16),
			 REG (value, 6), 0));

    case FP_MOV_TYPE_INST:
      return (mk_r_inst (value, i_opcode, REG (value, 11), 0, REG (value, 6),
			 0));

    case J_TYPE_INST:
      return (mk_j_inst (value, i_opcode, value & 0x2ffffff));

    case CP_TYPE_INST:
      return (mk_r_inst (value, i_opcode, 0, REG (value, 16), REG (value, 11),
			 0));

    case NOARG_TYPE_INST:
      return (mk_r_inst (value, i_opcode, 0, 0, 0, 0));

    case ASM_DIR:
    case PSEUDO_OP:
    default:
      return (mk_r_inst (value, 0, 0, 0, 0, 0)); /* Invalid inst */
    }
}


#ifdef __STDC__
static instruction *
mk_r_inst (uint32 value, int opcode, int rs, int rt, int rd, int shamt)
#else
static instruction *
mk_r_inst (value, opcode, rs, rt, rd, shamt)
     uint32 value;
     int opcode, rs, rt, rd, shamt;
#endif
{
  instruction *inst = (instruction *) zmalloc (sizeof (instruction));

  SET_OPCODE (inst, opcode);
  SET_RS (inst, rs);
  SET_RT (inst, rt);
  SET_RD (inst, rd);
  SET_SHAMT (inst, shamt);
  SET_ENCODING (inst, value);
  SET_EXPR (inst, NULL);
  return (inst);
}


#ifdef __STDC__
static instruction *
mk_i_inst (uint32 value, int opcode, int rs, int rt, int offset)
#else
static instruction *
mk_i_inst (value, opcode, rs, rt, offset)
     uint32 value;
     int opcode, rs, rt, offset;
#endif
{
  instruction *inst = (instruction *) zmalloc (sizeof (instruction));

  SET_OPCODE (inst, opcode);
  SET_RS (inst, rs);
  SET_RT (inst, rt);
  SET_IOFFSET (inst, offset);
  SET_ENCODING (inst, value);
  SET_EXPR (inst, NULL);
  return (inst);
}

#ifdef __STDC__
static instruction *
mk_j_inst (uint32 value, int opcode, int target)
#else
static instruction *
mk_j_inst (value, opcode, target)
     uint32 value;
     int opcode, target;
#endif
{
  instruction *inst = (instruction *) zmalloc (sizeof (instruction));

  SET_OPCODE (inst, opcode);
  SET_TARGET (inst, target);
  SET_ENCODING (inst, value);
  SET_EXPR (inst, NULL);
  return (inst);
}


/* Code to test encode/decode of instructions. */

#ifdef __STDC__
void
test_assembly (instruction *inst)
#else
void
test_assembly (inst)
     instruction *inst;
#endif
{
  instruction *new_inst = inst_decode (inst_encode (inst));

  inst_cmp (inst, new_inst);
  free_inst (new_inst);
}


#ifdef __STDC__
static void
inst_cmp (instruction *inst1, instruction *inst2)
#else
static void
inst_cmp (inst1, inst2)
     instruction *inst1, *inst2;
#endif
{
  char buf[1024];

  if (memcmp (inst1, inst2, sizeof (instruction) - 4) != 0)
    {
      printf ("=================== Not Equal ===================\n");
      print_inst_internal (buf, sizeof(buf), inst1, 0);
      printf ("%s\n", buf);
      print_inst_internal (buf, sizeof(buf), inst2, 0);
      printf ("%s\n", buf);
      printf ("=================== Not Equal ===================\n");
    }
}
