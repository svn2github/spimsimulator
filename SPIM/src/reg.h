/* SPIM S20 MIPS simulator.
   Declarations of registers and code for accessing them.

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


/* $Header: /Software/SPIM/src/reg.h 8     2/28/04 11:23a Larus $
*/


typedef int32 reg_word;
typedef uint32 u_reg_word;


/* General purpose registers: */

#define R_LENGTH	32

extern reg_word R[R_LENGTH];

extern reg_word HI, LO;

extern mem_addr PC, nPC;


/* Argument passing registers */

#define REG_V0		2
#define REG_A0		4
#define REG_A1		5
#define REG_A2		6
#define REG_A3		7
#define REG_FA0		12
#define REG_SP		29


/* Result registers */

#define REG_RES		2
#define REG_FRES	0


/* $gp registers */

#define REG_GP		28



/* Floating Point Coprocessor (1) registers.

   This is the MIPS32, Revision 1 FPU register set. It contains 32, 32-bit
   registers (either 32 single or 16 double precision), as in the R2010.
   The MIPS32, Revision 2 or MIPS64 register set has 32 of each type of
   register. */

#define FGR_LENGTH	32
#define FPR_LENGTH	16

extern double *FPR;		/* Dynamically allocate so overlay */
extern float *FGR;		/* is possible */
extern int *FWR;		/* is possible */


#ifdef LITTLEENDIAN
#define FPR_S(REGNO)	(FGR[REGNO])
#else
/* Flip low-order bit of register number, so that even and odd 32-bit float
   registers reverse and correctly overlap the double registers:

   0              63              0              63
   -----------------              -----------------
   |   1   |   0   |	  =>      |   0   |   1   |
   -----------------              -----------------

   Fortunately, this is not necessary on little endian machines. */
#define FPR_S(REGNO)	(FGR[(REGNO) ^ 0x1])
#endif

#define FPR_D(REGNO)	(((REGNO) & 0x1) \
			 ? (run_error ("Odd FP double register number\n") \
			    ? 0.0 : 0.0) \
			 : FPR[(REGNO) / 2])

#define FPR_W(REGNO)	(FWR[REGNO])


#ifdef LITTLEENDIAN
#define SET_FPR_S(REGNO, VALUE)	{FGR[REGNO] = (float) (VALUE);}
#else
#define SET_FPR_S(REGNO, VALUE)	{FGR[(REGNO) ^ 0x1] = (float) (VALUE);}
#endif

#define SET_FPR_D(REGNO, VALUE) {if ((REGNO) & 0x1) \
				 run_error ("Odd FP double register number\n"); \
				 else FPR[(REGNO) / 2] = (double) (VALUE);}

#define SET_FPR_W(REGNO, VALUE) {FWR[REGNO] = (int32) (VALUE);}


/* Floating point control registers: */

#define FCR		(CPR[1])

#define FIR_REG		0
#define FIR		(CPR[1][FIR_REG])

#define FCCR_REG	25
#define FCCR		(CPR[1][FCCR_REG])

#define FEXR_REG	26
#define FEXR		(CPR[1][FEXR_REG])

#define FENR_REG	28
#define FENR		(CPR[1][FENR_REG])

#define FCSR_REG	31
#define FCSR		(CPR[1][FCSR_REG])




/* The Coprocessor registers: */

extern reg_word CCR[4][32], CPR[4][32];


/* Exeception handling registers (Coprocoessor 0): */

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


#define USER_MODE	(Status_Reg & 0x2)
#define INTERRUPTS_ON	(Status_Reg & 0x1)
