/* SPIM S20 MIPS simulator.
   Declarations of registers and code for accessing them.

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


/* $Header: /Software/SPIM/src/reg.h 4     12/24/00 1:37p Larus $
*/


typedef int32 reg_word;
typedef uint32 u_reg_word;


/* General purpose registers: */

extern reg_word R[32];

extern reg_word HI, LO;

extern mem_addr PC, nPC;


/* Argument passing registers */

#define REG_V0 2
#define REG_A0 4
#define REG_A1 5
#define REG_A2 6
#define REG_A3 7
#define REG_FA0 12
#define REG_SP 29


/* Result registers */

#define REG_RES 2
#define REG_FRES 0


/* $gp registers */

#define REG_GP 28



/* Floating Point Coprocessor (1) registers :*/

extern double *FPR;		/* Dynamically allocate so overlay */
extern float *FGR;		/* is possible */
extern int *FWR;		/* is possible */


extern int FP_reg_present;	/* Presence bits for FP registers */
extern int FP_reg_poison;	/* Poison bits for FP registers */
extern int FP_spec_load;	/* Is register waiting for a speculative load */


#define FPR_S(REGNO) (FGR[REGNO])

#define FPR_D(REGNO) (double) (((REGNO) & 0x1) \
			       ? (run_error ("Bit 0 in FP double reg\n") ? 0.0 : 0.0)\
			       : FPR[(REGNO) >> 1])

#define FPR_W(REGNO) (FWR[REGNO])


#define SET_FPR_S(REGNO, VALUE) {FGR[REGNO] = (float) (VALUE);}

#define SET_FPR_D(REGNO, VALUE) {if ((REGNO) & 0x1) \
				 run_error ("Bit 0 in FP double reg\n");\
				 else FPR[(REGNO) >> 1] = (double) (VALUE);}

#define SET_FPR_W(REGNO, VALUE) {FWR[REGNO] = (int) (VALUE);}


/* Floating point control and condition registers: */

#define FCR		CPR[1]
#define FPId		(CPR[1][0])
#define FpCond		(CPR[1][31])



/* Other Coprocessor Registers.  The floating point registers
   (coprocessor 1) are above.  */

extern reg_word CpCond[4], CCR[4][32], CPR[4][32];


/* Exeception Handling Registers (actually registers in Coprocoessor
   0's register file) */

extern int exception_occurred;

#define EntryHI         (CPR[0][0])
#define EntryLO         (CPR[0][1])
#define Index           (CPR[0][2])
#define Random          (CPR[0][3])
#define Context		(CPR[0][4])
#define BadVAddr	(CPR[0][8])
#define Status_Reg	(CPR[0][12])
#define Cause		(CPR[0][13])
#define EPC		(CPR[0][14])
#define PRId		(CPR[0][15])


#define USER_MODE (Status_Reg & 0x2)
#define INTERRUPTS_ON (Status_Reg & 0x1)
