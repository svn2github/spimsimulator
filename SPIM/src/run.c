/* SPIM S20 MIPS simulator.
   Execute SPIM instructions.

   Copyright (C) 1990-1997 by James Larus (larus@cs.wisc.edu).
   ALL RIGHTS RESERVED.
   Changes for DOS and Windows versions by David A. Carley (dac@cs.wisc.edu)

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


/* $Header: /u/l/a/larus/Software/SPIM/src/RCS/run.c,v 3.47 1998/01/14 20:57:44 larus Exp $
*/


#ifdef mips
#define _IEEE 1
#include <nan.h>
#else
#define NaN(X) ((X) != (X))
#endif

#include <math.h>
#include <stdio.h>

#include "spim.h"
#include "spim-utils.h"
#include "inst.h"
#include "mem.h"
#include "reg.h"
#include "sym-tbl.h"
#include "y.tab.h"
#include "mips-syscall.h"
#include "run.h"

int force_break = 0;	/* For the execution env. to force an execution break */

#ifndef _MSC_VER
extern int errno;
#endif

#ifdef __STDC__
long atol (const char *);
#else
long atol ();
#endif


/* Local functions: */

#ifdef __STDC__
static void long_multiply (reg_word v1, reg_word v2);
#else
static void long_multiply ();
#endif


#define SIGN_BIT(X) ((X) & 0x80000000)

#define ARITH_OVFL(RESULT, OP1, OP2) (SIGN_BIT (OP1) == SIGN_BIT (OP2) \
				      && SIGN_BIT (OP1) != SIGN_BIT (RESULT))


/* Executed delayed branch and jump instructions by running the
   instruction from the delay slot before transfering control.  Note,
   in branches that don't jump, the instruction in the delay slot is
   executed by falling through normally.

   We take advantage of the MIPS architecture, which leaves undefined
   the result of executing a delayed instruction in a delay slot.  Here
   we execute the second branch. */

#define BRANCH_INST(TEST, TARGET) {if (TEST)				\
				    {					\
				      mem_addr target = (TARGET);	\
				      if (bare_machine)			\
					/* +4 since jump in delay slot */\
					target += BYTES_PER_WORD;	\
				      JUMP_INST (target)		\
				    }					\
				  }


#define JUMP_INST(TARGET) {if (bare_machine)				\
			    run_spim (PC + BYTES_PER_WORD, 1, display);	\
			  /* -4 since PC is bumped after this inst */	\
			  PC = (TARGET) - BYTES_PER_WORD;		\
			  }


/* Result from load is available immediate, but no program should ever have
   assumed otherwise because of exceptions.*/

#define LOAD_INST(OP, ADDR, DEST_A, MASK)				\
				 {reg_word tmp;				\
				   OP (tmp, (ADDR));			\
				   *(DEST_A) = tmp & (MASK);		\
				 }


#define DELAYED_UPDATE(A, D) {if (delayed_addr1 != NULL)		\
				fatal_error("Two calls to DELAYED_UPDATE\n");\
				delayed_addr1 = A; delayed_value1 = D;	\
			      }


#define DO_DELAYED_UPDATE() if (bare_machine)				\
			       {					\
				 /* Check for delayed updates */	\
				 if (delayed_addr2 != NULL)		\
				   *delayed_addr2 = delayed_value2;	\
				 delayed_addr2 = delayed_addr1;		\
				 delayed_value2 = delayed_value1;	\
				 delayed_addr1 = NULL;			\
			       }



/* Run the program stored in memory, starting at address PC for
   STEPS_TO_RUN instruction executions.  If flag DISPLAY is non-zero, print
   each instruction before it executes. Return non-zero if program's
   execution can continue. */


#ifdef __STDC__
int
run_spim (mem_addr initial_PC, int steps_to_run, int display)
#else
int
run_spim (initial_PC, steps_to_run, display)
     mem_addr initial_PC;
     int steps_to_run;
     int display;
#endif
{
  register instruction *inst;
  static reg_word *delayed_addr1 = NULL, delayed_value1;
  static reg_word *delayed_addr2 = NULL, delayed_value2;
  int step, step_size, next_step;

  PC = initial_PC;
  if (!bare_machine && mapped_io)
    next_step = IO_INTERVAL;
  else
    next_step = steps_to_run;	/* Run to completion */

  for (step_size = MIN (next_step, steps_to_run);
       steps_to_run > 0;
       steps_to_run -= step_size, step_size = MIN (next_step, steps_to_run))
    {
      if (!bare_machine && mapped_io)
	/* Every IO_INTERVAL steps, check if memory-mapped IO registers
	   have changed. */
	check_memory_mapped_IO ();
      /* else run inner loop for all steps */

      for (step = 0; step < step_size; step += 1)
	{
	  if (force_break)
	    {
	      force_break = 0;
	      return (1);
	    }

	  R[0] = 0;		/* Maintain invariant value */

	  READ_MEM_INST (inst, PC);

	  if (inst == NULL)
	    return 0;

	  if (exception_occurred)
	    {
	      exception_occurred = 0;
	      EPC = PC & 0xfffffffc; /* Round down */
	      handle_exception();
	      continue;
	    }
	  else if (inst == NULL)
	    run_error ("Attempt to execute non-instruction at 0x%08x\n", PC);
	  else if (EXPR (inst) != NULL
		   && EXPR (inst)->symbol != NULL
		   && EXPR (inst)->symbol->addr == 0)
	    {
	      error ("Instruction references undefined symbol at 0x%08x\n",
		     PC);
	      print_inst (PC);
	      run_error ("");
	    }

	  if (display)
	    print_inst (PC);

#ifdef TEST_ASM
	  test_assembly (inst);
#endif

	  DO_DELAYED_UPDATE ();

	  switch (OPCODE (inst))
	    {
	    case Y_ADD_OP:
	      {
		register reg_word vs = R[RS (inst)], vt = R[RT (inst)];
		register reg_word sum = vs + vt;

		if (ARITH_OVFL (sum, vs, vt))
		  RAISE_EXCEPTION (OVF_EXCPT, break);
		R[RD (inst)] = sum;
		break;
	      }

	    case Y_ADDI_OP:
	      {
		register reg_word vs = R[RS (inst)], imm = (short) IMM (inst);
		register reg_word sum = vs + imm;

		if (ARITH_OVFL (sum, vs, imm))
		  RAISE_EXCEPTION (OVF_EXCPT, break);
		R[RT (inst)] = sum;
		break;
	      }

	    case Y_ADDIU_OP:
	      R[RT (inst)] = R[RS (inst)] + (short) IMM (inst);
	      break;

	    case Y_ADDU_OP:
	      R[RD (inst)] = R[RS (inst)] + R[RT (inst)];
	      break;

	    case Y_AND_OP:
	      R[RD (inst)] = R[RS (inst)] & R[RT (inst)];
	      break;

	    case Y_ANDI_OP:
	      R[RT (inst)] = R[RS (inst)] & (0xffff & IMM (inst));
	      break;

	    case Y_BC0F_OP:
	    case Y_BC2F_OP:
	    case Y_BC3F_OP:
	      BRANCH_INST (CpCond[OPCODE (inst) - Y_BC0F_OP] == 0,
			   PC + (SIGN_EX (IOFFSET (inst)) << 2));
	      break;

	    case Y_BC0T_OP:
	    case Y_BC2T_OP:
	    case Y_BC3T_OP:
	      BRANCH_INST (CpCond[OPCODE (inst) - Y_BC0T_OP] != 0,
			   PC + (SIGN_EX (IOFFSET (inst)) << 2));
	      break;

	    case Y_BEQ_OP:
	      BRANCH_INST (R[RS (inst)] == R[RT (inst)],
			   PC + (SIGN_EX (IOFFSET (inst)) << 2));
	      break;

	    case Y_BGEZ_OP:
	      BRANCH_INST (SIGN_BIT (R[RS (inst)]) == 0,
			   PC + (SIGN_EX (IOFFSET (inst)) << 2));
	      break;

	    case Y_BGEZAL_OP:
	      if (bare_machine)
		R[31] = PC + 2 * BYTES_PER_WORD;
	      else
		R[31] = PC + BYTES_PER_WORD;
	      BRANCH_INST (SIGN_BIT (R[RS (inst)]) == 0,
			   PC + (SIGN_EX (IOFFSET (inst)) << 2));
	      break;

	    case Y_BGTZ_OP:
	      BRANCH_INST (R[RS (inst)] != 0 && SIGN_BIT (R[RS (inst)]) == 0,
			   PC + (SIGN_EX (IOFFSET (inst)) << 2));
	      break;

	    case Y_BLEZ_OP:
	      BRANCH_INST (R[RS (inst)] == 0 || SIGN_BIT (R[RS (inst)]) != 0,
			   PC + (SIGN_EX (IOFFSET (inst)) << 2));
	      break;

	    case Y_BLTZ_OP:
	      BRANCH_INST (SIGN_BIT (R[RS (inst)]) != 0,
			   PC + (SIGN_EX (IOFFSET (inst)) << 2));
	      break;

	    case Y_BLTZAL_OP:
	      if (bare_machine)
		R[31] = PC + 2 * BYTES_PER_WORD;
	      else
		R[31] = PC + BYTES_PER_WORD;
	      BRANCH_INST (SIGN_BIT (R[RS (inst)]) != 0,
			   PC + (SIGN_EX (IOFFSET (inst)) << 2));
	      break;

	    case Y_BNE_OP:
	      BRANCH_INST (R[RS (inst)] != R[RT (inst)],
			   PC + (SIGN_EX (IOFFSET (inst)) << 2));
	      break;

	    case Y_BREAK_OP:
	      if (RD (inst) == 1)
		/* Debugger breakpoint */
		RAISE_EXCEPTION (BKPT_EXCPT, return (1))
	      else
		RAISE_EXCEPTION (BKPT_EXCPT, break);

	    case Y_CFC0_OP:
	    case Y_CFC2_OP:
	    case Y_CFC3_OP:
	      R[RT (inst)] = CCR[OPCODE (inst) - Y_CFC0_OP][RD (inst)];
	      break;

	    case Y_COP0_OP:
	    case Y_COP1_OP:
	    case Y_COP2_OP:
	    case Y_COP3_OP:
	      CCR[OPCODE (inst) - Y_COP0_OP][RD (inst)] = R[RT (inst)];
	      break;

	    case Y_CTC0_OP:
	    case Y_CTC2_OP:
	    case Y_CTC3_OP:
	      CCR[OPCODE (inst) - Y_CTC0_OP][RD (inst)] = R[RT (inst)];
	      break;

	    case Y_DIV_OP:
	      if (R[RT (inst)] != 0)
		{
		  LO = (reg_word) R[RS (inst)] / (reg_word) R[RT (inst)];
		  HI = (reg_word) R[RS (inst)] % (reg_word) R[RT (inst)];
		}
	      break;

	    case Y_DIVU_OP:
	      if (R[RT (inst)] != 0)
		{
		  LO = ((u_reg_word) R[RS (inst)] / (u_reg_word) R[RT (inst)]);
		  HI = ((u_reg_word) R[RS (inst)] % (u_reg_word) R[RT (inst)]);
		}
	      break;

	    case Y_J_OP:
	      JUMP_INST (((PC & 0xf0000000) | TARGET (inst) << 2));
	      break;

	    case Y_JAL_OP:
	      if (bare_machine)
		R[31] = PC + 2 * BYTES_PER_WORD;
	      else
		R[31] = PC + BYTES_PER_WORD;
	      JUMP_INST (((PC & 0xf0000000) | (TARGET (inst) << 2)));
	      break;

	    case Y_JALR_OP:
	      {
		mem_addr tmp = R[RS (inst)];

		if (bare_machine)
		  R[RD (inst)] = PC + 2 * BYTES_PER_WORD;
		else
		  R[RD (inst)] = PC + BYTES_PER_WORD;
		JUMP_INST (tmp);
	      }
	      break;

	    case Y_JR_OP:
	      {
		mem_addr tmp = R[RS (inst)];

		JUMP_INST (tmp);
	      }
	      break;

	    case Y_LB_OP:
	      LOAD_INST (READ_MEM_BYTE, R[BASE (inst)] + IOFFSET (inst),
			 &R[RT (inst)], 0xffffffff);
	      break;

	    case Y_LBU_OP:
	      LOAD_INST (READ_MEM_BYTE, R[BASE (inst)] + IOFFSET (inst),
			 &R[RT (inst)], 0xff);
	      break;

	    case Y_LH_OP:
	      LOAD_INST (READ_MEM_HALF, R[BASE (inst)] + IOFFSET (inst),
			 &R[RT (inst)], 0xffffffff);
	      break;

	    case Y_LHU_OP:
	      LOAD_INST (READ_MEM_HALF, R[BASE (inst)] + IOFFSET (inst),
			 &R[RT (inst)], 0xffff);
	      break;

	    case Y_LUI_OP:
	      R[RT (inst)] = (IMM (inst) << 16) & 0xffff0000;
	      break;

	    case Y_LW_OP:
	      LOAD_INST (READ_MEM_WORD, R[BASE (inst)] + IOFFSET (inst),
			 &R[RT (inst)], 0xffffffff);
	      break;

	    case Y_LWC0_OP:
	    case Y_LWC2_OP:
	    case Y_LWC3_OP:
	      LOAD_INST (READ_MEM_WORD, R[BASE (inst)] + IOFFSET (inst),
			 &CPR[OPCODE (inst) - Y_LWC0_OP][RT (inst)],
			 0xffffffff);
	      break;

	    case Y_LWL_OP:
	      {
		register mem_addr addr = R[BASE (inst)] + IOFFSET (inst);
		reg_word word;	/* Can't be register */
		register int byte = addr & 0x3;
		reg_word reg_val = R[RT (inst)];

		LOAD_INST (READ_MEM_WORD, addr & 0xfffffffc, &word,
			   0xffffffff);
		DO_DELAYED_UPDATE ();

		if ((!exception_occurred) || ((Cause >> 2) > LAST_REAL_EXCEPT))
#ifdef BIGENDIAN
		  switch (byte)
		    {
		    case 0:
		      R[RT (inst)] = word;
		      break;

		    case 1:
		      R[RT (inst)] = (word & 0xffffff) << 8 | (reg_val & 0xff);
		      break;

		    case 2:
		      R[RT (inst)] = (word & 0xffff) << 16 | (reg_val & 0xffff);
		      break;

		    case 3:
		      R[RT (inst)] = (word & 0xff) << 24 | (reg_val & 0xffffff);
		      break;
		    }
#else
		switch (byte)
		  {
		  case 0:
		    R[RT (inst)] = (word & 0xff) << 24 | (reg_val & 0xffffff);
		    break;

		  case 1:
		    R[RT (inst)] = (word & 0xffff) << 16 | (reg_val & 0xffff);
		    break;

		  case 2:
		    R[RT (inst)] = (word & 0xffffff) << 8 | (reg_val & 0xff);
		    break;

		  case 3:
		    R[RT (inst)] = word;
		    break;
		  }
#endif
		break;
	      }

	    case Y_LWR_OP:
	      {
		register mem_addr addr = R[BASE (inst)] + IOFFSET (inst);
		reg_word word;	/* Can't be register */
		register int byte = addr & 0x3;
		reg_word reg_val = R[RT (inst)];

		LOAD_INST (READ_MEM_WORD, addr & 0xfffffffc, &word, 0xffffffff);
		DO_DELAYED_UPDATE ();

		if ((!exception_occurred) || ((Cause >> 2) > LAST_REAL_EXCEPT))
#ifdef BIGENDIAN
		  switch (byte)
		    {
		    case 0:
		      R[RT (inst)] = (reg_val & 0xffffff00)
			| ((unsigned)(word & 0xff000000) >> 24);
		      break;

		    case 1:
		      R[RT (inst)] = (reg_val & 0xffff0000)
			| ((unsigned)(word & 0xffff0000) >> 16);
		      break;

		    case 2:
		      R[RT (inst)] = (reg_val & 0xff000000)
			| ((unsigned)(word & 0xffffff00) >> 8);
		      break;

		    case 3:
		      R[RT (inst)] = word;
		      break;
		    }
#else
		switch (byte)
		  {
		    /* NB: The description of the little-endian case in Kane is
		       totally wrong. */
		  case 0:	/* 3 in book */
		    R[RT (inst)] = word;
		    break;

		  case 1:	/* 0 in book */
		    R[RT (inst)] = (reg_val & 0xff000000)
		      | ((word & 0xffffff00) >> 8);
		    break;

		  case 2:	/* 1 in book */
		    R[RT (inst)] = (reg_val & 0xffff0000)
		      | ((word & 0xffff0000) >> 16);
		    break;

		  case 3:	/* 2 in book */
		    R[RT (inst)] = (reg_val & 0xffffff00)
		      | ((word & 0xff000000) >> 24);
		    break;
		  }
#endif
		break;
	      }

	    case Y_MFC0_OP:
	    case Y_MFC2_OP:
	    case Y_MFC3_OP:
	      R[RT (inst)] = CPR[OPCODE (inst) - Y_MFC0_OP][RD (inst)];
	      break;

	    case Y_MFHI_OP:
	      R[RD (inst)] = HI;
	      break;

	    case Y_MFLO_OP:
	      R[RD (inst)] = LO;
	      break;

	    case Y_MTC0_OP:
	    case Y_MTC2_OP:
	    case Y_MTC3_OP:
	      CPR[OPCODE (inst) - Y_MTC0_OP][RD (inst)] = R[RT (inst)];
	      break;

	    case Y_MTHI_OP:
	      HI = R[RS (inst)];
	      break;

	    case Y_MTLO_OP:
	      LO = R[RS (inst)];
	      break;

	    case Y_MULT_OP:
	      {
		reg_word v1 = R[RS (inst)], v2 = R[RT (inst)];
		int neg_sign = 0;

		if (v1 < 0)
		  v1 = - v1, neg_sign = 1;
		if (v2 < 0)
		  v2 = - v2, neg_sign = ! neg_sign;

		long_multiply (v1, v2);
		if (neg_sign)
		  {
		    LO = ~ LO;
		    HI = ~ HI;
		    LO += 1;
		    if (LO == 0)
		      HI += 1;
		  }
	      }
	      break;

	    case Y_MULTU_OP:
	      long_multiply (R[RS (inst)], R[RT (inst)]);
	      break;

	    case Y_NOR_OP:
	      R[RD (inst)] = ~ (R[RS (inst)] | R[RT (inst)]);
	      break;

	    case Y_OR_OP:
	      R[RD (inst)] = R[RS (inst)] | R[RT (inst)];
	      break;

	    case Y_ORI_OP:
	      R[RT (inst)] = R[RS (inst)] | (0xffff & IMM (inst));
	      break;

	    case Y_RFE_OP:
	      Status_Reg = (Status_Reg & 0xfffffff0) | ((Status_Reg & 0x3c) >> 2);
	      break;

	    case Y_SB_OP:
	      SET_MEM_BYTE (R[BASE (inst)] + IOFFSET (inst), R[RT (inst)]);
	      break;

	    case Y_SH_OP:
	      SET_MEM_HALF (R[BASE (inst)] + IOFFSET (inst), R[RT (inst)]);
	      break;

	    case Y_SLL_OP:
	      {
		int shamt = SHAMT (inst);

		if (shamt >= 0 && shamt < 32)
		  R[RD (inst)] = R[RT (inst)] << shamt;
		else
		  R[RD (inst)] = R[RT (inst)];
		break;
	      }

	    case Y_SLLV_OP:
	      {
		int shamt = (R[RS (inst)] & 0x1f);

		if (shamt >= 0 && shamt < 32)
		  R[RD (inst)] = R[RT (inst)] << shamt;
		else
		  R[RD (inst)] = R[RT (inst)];
		break;
	      }

	    case Y_SLT_OP:
	      if (R[RS (inst)] < R[RT (inst)])
		R[RD (inst)] = 1;
	      else
		R[RD (inst)] = 0;
	      break;

	    case Y_SLTI_OP:
	      if (R[RS (inst)] < (short) IMM (inst))
		R[RT (inst)] = 1;
	      else
		R[RT (inst)] = 0;
	      break;

	    case Y_SLTIU_OP:
	      {
		int x = (short) IMM (inst);

		if ((u_reg_word) R[RS (inst)] < (u_reg_word) x)
		  R[RT (inst)] = 1;
		else
		  R[RT (inst)] = 0;
		break;
	      }

	    case Y_SLTU_OP:
	      if ((u_reg_word) R[RS (inst)] < (u_reg_word) R[RT (inst)])
		R[RD (inst)] = 1;
	      else
		R[RD (inst)] = 0;
	      break;

	    case Y_SRA_OP:
	      {
		int shamt = SHAMT (inst);
		reg_word val = R[RT (inst)];

		if (shamt >= 0 && shamt < 32)
		  R[RD (inst)] = val >> shamt;
		else
		  R[RD (inst)] = val;
		break;
	      }

	    case Y_SRAV_OP:
	      {
		int shamt = R[RS (inst)] & 0x1f;
		reg_word val = R[RT (inst)];

		if (shamt >= 0 && shamt < 32)
		  R[RD (inst)] = val >> shamt;
		else
		  R[RD (inst)] = val;
		break;
	      }

	    case Y_SRL_OP:
	      {
		int shamt = SHAMT (inst);
		u_reg_word val = R[RT (inst)];

		if (shamt >= 0 && shamt < 32)
		  R[RD (inst)] = val >> shamt;
		else
		  R[RD (inst)] = val;
		break;
	      }

	    case Y_SRLV_OP:
	      {
		int shamt = R[RS (inst)] & 0x1f;
		u_reg_word val = R[RT (inst)];

		if (shamt >= 0 && shamt < 32)
		  R[RD (inst)] = val >> shamt;
		else
		  R[RD (inst)] = val;
		break;
	      }

	    case Y_SUB_OP:
	      {
		register reg_word vs = R[RS (inst)], vt = R[RT (inst)];
		register reg_word diff = vs - vt;

		if (SIGN_BIT (vs) != SIGN_BIT (vt)
		    && SIGN_BIT (vs) != SIGN_BIT (diff))
		  RAISE_EXCEPTION (OVF_EXCPT, break);
		R[RD (inst)] = diff;
		break;
	      }

	    case Y_SUBU_OP:
	      R[RD (inst)] = (u_reg_word)R[RS (inst)]-(u_reg_word)R[RT (inst)];
	      break;

	    case Y_SW_OP:
	      SET_MEM_WORD (R[BASE (inst)] + IOFFSET (inst), R[RT (inst)]);
	      break;

	    case Y_SWC0_OP:
	    case Y_SWC2_OP:
	    case Y_SWC3_OP:
	      SET_MEM_WORD (R[BASE (inst)] + IOFFSET (inst),
			    CPR[OPCODE (inst) - Y_SWC0_OP][RT (inst)]);
	      break;

	    case Y_SWL_OP:
	      {
		register mem_addr addr = R[BASE (inst)] + IOFFSET (inst);
		mem_word data;
		reg_word reg = R[RT (inst)];
		register int byte = addr & 0x3;

		READ_MEM_WORD (data, (addr & 0xfffffffc));
#ifdef BIGENDIAN
		switch (byte)
		  {
		  case 0:
		    data = reg;
		    break;

		  case 1:
		    data = (data & 0xff000000) | (reg >> 8 & 0xffffff);
		    break;

		  case 2:
		    data = (data & 0xffff0000) | (reg >> 16 & 0xffff);
		    break;

		  case 3:
		    data = (data & 0xffffff00) | (reg >> 24 & 0xff);
		    break;
		  }
#else
		switch (byte)
		  {
		  case 0:
		    data = (data & 0xffffff00) | (reg >> 24 & 0xff);
		    break;

		  case 1:
		    data = (data & 0xffff0000) | (reg >> 16 & 0xffff);
		    break;

		  case 2:
		    data = (data & 0xff000000) | (reg >> 8 & 0xffffff);
		    break;

		  case 3:
		    data = reg;
		    break;
		  }
#endif
		SET_MEM_WORD (addr & 0xfffffffc, data);
		break;
	      }

	    case Y_SWR_OP:
	      {
		register mem_addr addr = R[BASE (inst)] + IOFFSET (inst);
		mem_word data;
		reg_word reg = R[RT (inst)];
		register int byte = addr & 0x3;

		READ_MEM_WORD (data, (addr & 0xfffffffc));
#ifdef BIGENDIAN
		switch (byte)
		  {
		  case 0:
		    data = ((reg << 24) & 0xff000000) | (data & 0xffffff);
		    break;

		  case 1:
		    data = ((reg << 16) & 0xffff0000) | (data & 0xffff);
		    break;

		  case 2:
		    data = ((reg << 8) & 0xffffff00) | (data & 0xff) ;
		    break;

		  case 3:
		    data = reg;
		    break;
		  }
#else
		switch (byte)
		  {
		  case 0:
		    data = reg;
		    break;

		  case 1:
		    data = ((reg << 8) & 0xffffff00) | (data & 0xff) ;
		    break;

		  case 2:
		    data = ((reg << 16) & 0xffff0000) | (data & 0xffff);
		    break;

		  case 3:
		    data = ((reg << 24) & 0xff000000) | (data & 0xffffff);
		    break;
		  }
#endif
		SET_MEM_WORD (addr & 0xfffffffc, data);
		break;
	      }

	    case Y_SYSCALL_OP:
	      if (!do_syscall ())
		return (0);
	      break;

	    case Y_TLBP_OP:
	    case Y_TLBR_OP:
	    case Y_TLBWI_OP:
	    case Y_TLBWR_OP:
	      fatal_error ("Unimplemented operation\n");
	      break;

	    case Y_XOR_OP:
	      R[RD (inst)] = R[RS (inst)] ^ R[RT (inst)];
	      break;

	    case Y_XORI_OP:
	      R[RT (inst)] = R[RS (inst)] ^ (0xffff & IMM (inst));
	      break;


	      /* FPA Operations */


	    case Y_ABS_S_OP:
	      SET_FPR_S (FD (inst), fabs (FPR_S (FS (inst))));
	      break;

	    case Y_ABS_D_OP:
	      SET_FPR_D (FD (inst), fabs (FPR_D (FS (inst))));
	      break;

	    case Y_ADD_S_OP:
	      SET_FPR_S (FD (inst), FPR_S (FS (inst)) + FPR_S (FT (inst)));
	      /* Should trap on inexact/overflow/underflow */
	      break;

	    case Y_ADD_D_OP:
	      SET_FPR_D (FD (inst), FPR_D (FS (inst)) + FPR_D (FT (inst)));
	      /* Should trap on inexact/overflow/underflow */
	      break;

	    case Y_BC1F_OP:
	      BRANCH_INST (FpCond == 0,
			   PC + (SIGN_EX (IOFFSET (inst)) << 2));
	      break;

	    case Y_BC1T_OP:
	      BRANCH_INST (FpCond == 1,
			   PC + (SIGN_EX (IOFFSET (inst)) << 2));
	      break;

	    case Y_C_F_S_OP:
	    case Y_C_UN_S_OP:
	    case Y_C_EQ_S_OP:
	    case Y_C_UEQ_S_OP:
	    case Y_C_OLT_S_OP:
	    case Y_C_OLE_S_OP:
	    case Y_C_ULT_S_OP:
	    case Y_C_ULE_S_OP:
	    case Y_C_SF_S_OP:
	    case Y_C_NGLE_S_OP:
	    case Y_C_SEQ_S_OP:
	    case Y_C_NGL_S_OP:
	    case Y_C_LT_S_OP:
	    case Y_C_NGE_S_OP:
	    case Y_C_LE_S_OP:
	    case Y_C_NGT_S_OP:
	      {
		float v1 = FPR_S (FS (inst)), v2 = FPR_S (FT (inst));
		double dv1 = v1, dv2 = v2;
		int less, equal, unordered;
		int cond = COND (inst);

		if (NaN (dv1) || NaN (dv2))
		  {
		    less = 0;
		    equal = 0;
		    unordered = 1;
		    if (cond & COND_IN)
		      RAISE_EXCEPTION (INVALID_EXCEPT, break);
		  }
		else
		  {
		    less = v1 < v2;
		    equal = v1 == v2;
		    unordered = 0;
		  }
		FpCond = 0;
		if (cond & COND_LT)
		  FpCond |= less;
		if (cond & COND_EQ)
		  FpCond |= equal;
		if (cond & COND_UN)
		  FpCond |= unordered;
	      }
	      break;

	    case Y_C_F_D_OP:
	    case Y_C_UN_D_OP:
	    case Y_C_EQ_D_OP:
	    case Y_C_UEQ_D_OP:
	    case Y_C_OLT_D_OP:
	    case Y_C_OLE_D_OP:
	    case Y_C_ULT_D_OP:
	    case Y_C_ULE_D_OP:
	    case Y_C_SF_D_OP:
	    case Y_C_NGLE_D_OP:
	    case Y_C_SEQ_D_OP:
	    case Y_C_NGL_D_OP:
	    case Y_C_LT_D_OP:
	    case Y_C_NGE_D_OP:
	    case Y_C_LE_D_OP:
	    case Y_C_NGT_D_OP:
	      {
		double v1 = FPR_D (FS (inst)), v2 = FPR_D (FT (inst));
		int less, equal, unordered;
		int cond = COND (inst);

		if (NaN (v1) || NaN (v2))
		  {
		    less = 0;
		    equal = 0;
		    unordered = 1;
		    if (cond & COND_IN)
		      RAISE_EXCEPTION (INVALID_EXCEPT, break);
		  }
		else
		  {
		    less = v1 < v2;
		    equal = v1 == v2;
		    unordered = 0;
		  }
		FpCond = 0;
		if (cond & COND_LT)
		  FpCond |= less;
		if (cond & COND_EQ)
		  FpCond |= equal;
		if (cond & COND_UN)
		  FpCond |= unordered;
	      }
	      break;

	    case Y_CFC1_OP:
	      R[RT (inst)] = FCR[RD (inst)]; /* RD not FS */
	      break;

	    case Y_CTC1_OP:
	      FCR[RD (inst)] = R[RT (inst)]; /* RD not FS */
	      break;

	    case Y_CVT_D_S_OP:
	      {
		double val = FPR_S (FS (inst));

		SET_FPR_D (FD (inst), val);
		break;
	      }

	    case Y_CVT_D_W_OP:
	      {
		double val = FPR_W (FS (inst));

		SET_FPR_D (FD (inst), val);
		break;
	      }

	    case Y_CVT_S_D_OP:
	      {
		float val = (float)FPR_D (FS (inst));

		SET_FPR_S (FD (inst), val);
		break;
	      }

	    case Y_CVT_S_W_OP:
	      {
		float val = (float)FPR_W (FS (inst));

		SET_FPR_S (FD (inst), val);
		break;
	      }

	    case Y_CVT_W_D_OP:
	      {
		int val = (int)FPR_D (FS (inst));

		SET_FPR_W (FD (inst), val);
		break;
	      }

	    case Y_CVT_W_S_OP:
	      {
		int val = (int)FPR_S (FS (inst));

		SET_FPR_W (FD (inst), val);
		break;
	      }

	    case Y_DIV_S_OP:
	      SET_FPR_S (FD (inst), FPR_S (FS (inst)) / FPR_S (FT (inst)));
	      break;

	    case Y_DIV_D_OP:
	      SET_FPR_D (FD (inst), FPR_D (FS (inst)) / FPR_D (FT (inst)));
	      break;

	    case Y_LWC1_OP:
	      {
		reg_word *wp = (reg_word *) &FGR[FT (inst)];

		LOAD_INST (READ_MEM_WORD, R[BASE (inst)] + IOFFSET (inst), wp,
			   0xffffffff);
		break;
	      }

	    case Y_MFC1_OP:
	      {
		float val = FGR[RD (inst)]; /* RD not FS */
		reg_word *vp = (reg_word *) &val;

		R[RT (inst)] = *vp; /* Fool coercion */
		break;
	      }

	    case Y_MOV_S_OP:
	      SET_FPR_S (FD (inst), FPR_S (FS (inst)));
	      break;

	    case Y_MOV_D_OP:
	      SET_FPR_D (FD (inst), FPR_D (FS (inst)));
	      break;

	    case Y_MTC1_OP:
	      {
		reg_word word = R[RT (inst)];
		float *wp = (float *) &word;

		FGR[RD (inst)] = *wp; /* RD not FS, fool coercion */
		break;
	      }

	    case Y_MUL_S_OP:
	      SET_FPR_S (FD (inst), FPR_S (FS (inst)) * FPR_S (FT (inst)));
	      break;

	    case Y_MUL_D_OP:
	      SET_FPR_D (FD (inst), FPR_D (FS (inst)) * FPR_D (FT (inst)));
	      break;

	    case Y_NEG_S_OP:
	      SET_FPR_S (FD (inst), -FPR_S (FS (inst)));
	      break;

	    case Y_NEG_D_OP:
	      SET_FPR_D (FD (inst), -FPR_D (FS (inst)));
	      break;

	    case Y_SUB_S_OP:
	      SET_FPR_S (FD (inst), FPR_S (FS (inst)) - FPR_S (FT (inst)));
	      break;

	    case Y_SUB_D_OP:
	      SET_FPR_D (FD (inst), FPR_D (FS (inst)) - FPR_D (FT (inst)));
	      break;

	    case Y_SWC1_OP:
	      {
		float val = FGR[RT (inst)];
		reg_word *vp = (reg_word *) &val;

		SET_MEM_WORD (R[BASE (inst)] + IOFFSET (inst), *vp);
		break;
	      }

	    default:
	      fatal_error ("Unknown instruction type: %d\n", OPCODE (inst));
	      break;
	    }

	  /* After instruction executes: */
	  PC += BYTES_PER_WORD;

	  if (exception_occurred)
	    {
	      if ((Cause >> 2) > LAST_REAL_EXCEPT)
		EPC = PC - BYTES_PER_WORD;

	      handle_exception ();
	    }
	}			/* End: for (step = 0; ... */
    }				/* End: for ( ; steps_to_run > 0 ... */

  /* Executed enought steps, return, but are able to continue. */
  return (1);
}


/* Multiply two 32-bit numbers, V1 and V2, to produce a 64 bit result in
   the HI/LO registers.	 The algorithm is high-school math:

	 A B
       x C D
       ------
       AD || BD
 AC || CB || 0

 where A and B are the high and low short words of V1, C and D are the short
 words of V2, AD is the product of A and D, and X || Y is (X << 16) + Y.
 Since the algorithm is programmed in C, we need to be careful not to
 overflow. */

#ifdef __STDC__
static void
long_multiply (reg_word v1, reg_word v2)
#else
static void
long_multiply (v1, v2)
     reg_word v1, v2;
#endif
{
  register u_reg_word a, b, c, d;
  register u_reg_word bd, ad, cb, ac;
  register u_reg_word mid, mid2, carry_mid = 0;

  a = (v1 >> 16) & 0xffff;
  b = v1 & 0xffff;
  c = (v2 >> 16) & 0xffff;
  d = v2 & 0xffff;

  bd = b * d;
  ad = a * d;
  cb = c * b;
  ac = a * c;

  mid = ad + cb;
  if (mid < ad || mid < cb)
    /* Arithmetic overflow or carry-out */
    carry_mid = 1;

  mid2 = mid + ((bd >> 16) & 0xffff);
  if (mid2 < mid || mid2 < ((bd >> 16) & 0xffff))
    /* Arithmetic overflow or carry-out */
    carry_mid += 1;

  LO = (bd & 0xffff) | ((mid2 & 0xffff) << 16);
  HI = ac + (carry_mid << 16) + ((mid2 >> 16) & 0xffff);
}
