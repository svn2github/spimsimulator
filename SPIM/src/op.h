/* SPIM S20 MIPS simulator.
   This file describes the MIPS instructions, the assembler pseudo
   instructions, the assembler pseudo-ops, and the spim commands.

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


/* $Header: /u/l/a/larus/Software/SPIM/RCS/op.h,v 3.16 1997/07/09 17:20:24 larus Exp $
*/


/* Type of each entry: */

#define ASM_DIR		0
#define PSEUDO_OP	2

#define B0_TYPE_INST	4
#define B1_TYPE_INST	5
#define I1t_TYPE_INST	6
#define I2_TYPE_INST	7
#define B2_TYPE_INST	25
#define I2a_TYPE_INST	8

#define R1s_TYPE_INST	9
#define R1d_TYPE_INST	10
#define R2td_TYPE_INST	11
#define R2st_TYPE_INST	12
#define R2ds_TYPE_INST	13
#define R2sh_TYPE_INST	14
#define R3_TYPE_INST	15
#define R3sh_TYPE_INST	16

#define FP_I2a_TYPE_INST	17
#define FP_R2ds_TYPE_INST	18
#define FP_CMP_TYPE_INST	19
#define FP_R3_TYPE_INST	20
#define FP_MOV_TYPE_INST 21

#define J_TYPE_INST	22
#define CP_TYPE_INST	23
#define NOARG_TYPE_INST 24


/* Information on each keyword token that can be read by spim.	Must be
   sorted in alphabetical order. */

OP (".alias",	Y_ALIAS_DIR,	ASM_DIR,		-1)
OP (".align",	Y_ALIGN_DIR,	ASM_DIR,		-1)
OP (".ascii",	Y_ASCII_DIR,	ASM_DIR,		-1)
OP (".asciiz",	Y_ASCIIZ_DIR,	ASM_DIR,		-1)
OP (".asm0",	Y_ASM0_DIR,	ASM_DIR,		-1)
OP (".bgnb",	Y_BGNB_DIR,	ASM_DIR,		-1)
OP (".byte",	Y_BYTE_DIR,	ASM_DIR,		-1)
OP (".comm",	Y_COMM_DIR,	ASM_DIR,		-1)
OP (".data",	Y_DATA_DIR,	ASM_DIR,		-1)
OP (".double",	Y_DOUBLE_DIR,	ASM_DIR,		-1)
OP (".end",	Y_END_DIR,	ASM_DIR,		-1)
OP (".endb",	Y_ENDB_DIR,	ASM_DIR,		-1)
OP (".endr",	Y_ENDR_DIR,	ASM_DIR,		-1)
OP (".ent",	Y_ENT_DIR,	ASM_DIR,		-1)
OP (".err",	Y_ERR_DIR,	ASM_DIR,		-1)
OP (".extern",	Y_EXTERN_DIR,	ASM_DIR,		-1)
OP (".file",	Y_FILE_DIR,	ASM_DIR,		-1)
OP (".float",	Y_FLOAT_DIR,	ASM_DIR,		-1)
OP (".fmask",	Y_FMASK_DIR,	ASM_DIR,		-1)
OP (".frame",	Y_FRAME_DIR,	ASM_DIR,		-1)
OP (".globl",	Y_GLOBAL_DIR,	ASM_DIR,		-1)
OP (".half",	Y_HALF_DIR,	ASM_DIR,		-1)
OP (".kdata",	Y_K_DATA_DIR,	ASM_DIR,		-1)
OP (".ktext",	Y_K_TEXT_DIR,	ASM_DIR,		-1)
OP (".lab",	Y_LABEL_DIR,	ASM_DIR,		-1)
OP (".lcomm",	Y_LCOMM_DIR,	ASM_DIR,		-1)
OP (".livereg",	Y_LIVEREG_DIR,	ASM_DIR,		-1)
OP (".loc",	Y_LOC_DIR,	ASM_DIR,		-1)
OP (".mask",	Y_MASK_DIR,	ASM_DIR,		-1)
OP (".noalias",	Y_NOALIAS_DIR,	ASM_DIR,		-1)
OP (".option",	Y_OPTIONS_DIR,	ASM_DIR,		-1)
OP (".rdata",	Y_RDATA_DIR,	ASM_DIR,		-1)
OP (".repeat",	Y_REPEAT_DIR,	ASM_DIR,		-1)
OP (".sdata",	Y_SDATA_DIR,	ASM_DIR,		-1)
OP (".set",	Y_SET_DIR,	ASM_DIR,		-1)
OP (".space",	Y_SPACE_DIR,	ASM_DIR,		-1)
OP (".struct",	Y_STRUCT_DIR,	ASM_DIR,		-1)
OP (".text",	Y_TEXT_DIR,	ASM_DIR,		-1)
OP (".verstamp",Y_VERSTAMP_DIR,	ASM_DIR,		-1)
OP (".vreg",	Y_VREG_DIR,	ASM_DIR,		-1)
OP (".word",	Y_WORD_DIR,	ASM_DIR,		-1)
OP ("abs",	Y_ABS_POP,	PSEUDO_OP,		-1)
OP ("abs.d",	Y_ABS_D_OP,	FP_R2ds_TYPE_INST,	0x46200005)
OP ("abs.s",	Y_ABS_S_OP,	FP_R2ds_TYPE_INST,	0x46000005)
OP ("add",	Y_ADD_OP,	R3_TYPE_INST,		0x00000020)
OP ("add.d",	Y_ADD_D_OP,	FP_R3_TYPE_INST,	0x46200000)
OP ("add.s",	Y_ADD_S_OP,	FP_R3_TYPE_INST,	0x46000000)
OP ("addi",	Y_ADDI_OP,	I2_TYPE_INST,		0x20000000)
OP ("addiu",	Y_ADDIU_OP,	I2_TYPE_INST,		0x24000000)
OP ("addu",	Y_ADDU_OP,	R3_TYPE_INST,		0x00000021)
OP ("and",	Y_AND_OP,	R3_TYPE_INST,		0x00000024)
OP ("andi",	Y_ANDI_OP,	I2_TYPE_INST,		0x30000000)
OP ("b",	Y_B_POP,	PSEUDO_OP,		-1)
OP ("bal",	Y_BAL_POP,	PSEUDO_OP,		-1)
OP ("bc0f",	Y_BC0F_OP,	B0_TYPE_INST,		0x41000000)
OP ("bc0t",	Y_BC0T_OP,	B0_TYPE_INST,		0x41010000)
OP ("bc1f",	Y_BC1F_OP,	B0_TYPE_INST,		0x45000000)
OP ("bc1t",	Y_BC1T_OP,	B0_TYPE_INST,		0x45010000)
OP ("bc2f",	Y_BC2F_OP,	B0_TYPE_INST,		0x49000000)
OP ("bc2t",	Y_BC2T_OP,	B0_TYPE_INST,		0x49010000)
OP ("bc3f",	Y_BC3F_OP,	B0_TYPE_INST,		0x4d000000)
OP ("bc3t",	Y_BC3T_OP,	B0_TYPE_INST,		0x4d010000)
OP ("beq",	Y_BEQ_OP,	B2_TYPE_INST,		0x10000000)
OP ("beqz",	Y_BEQZ_POP,	PSEUDO_OP,		-1)
OP ("bge",	Y_BGE_POP,	PSEUDO_OP,		-1)
OP ("bgeu",	Y_BGEU_POP,	PSEUDO_OP,		-1)
OP ("bgez",	Y_BGEZ_OP,	B1_TYPE_INST,		0x04010000)
OP ("bgezal",	Y_BGEZAL_OP,	B1_TYPE_INST,		0x04110000)
OP ("bgt",	Y_BGT_POP,	PSEUDO_OP,		-1)
OP ("bgtu",	Y_BGTU_POP,	PSEUDO_OP,		-1)
OP ("bgtz",	Y_BGTZ_OP,	B1_TYPE_INST,		0x1c000000)
OP ("ble",	Y_BLE_POP,	PSEUDO_OP,		-1)
OP ("bleu",	Y_BLEU_POP,	PSEUDO_OP,		-1)
OP ("blez",	Y_BLEZ_OP,	B1_TYPE_INST,		0x18000000)
OP ("blt",	Y_BLT_POP,	PSEUDO_OP,		-1)
OP ("bltu",	Y_BLTU_POP,	PSEUDO_OP,		-1)
OP ("bltz",	Y_BLTZ_OP,	B1_TYPE_INST,		0x04000000)
OP ("bltzal",	Y_BLTZAL_OP,	B1_TYPE_INST,		0x04100000)
OP ("bne",	Y_BNE_OP,	B2_TYPE_INST,		0x14000000)
OP ("bnez",	Y_BNEZ_POP,	PSEUDO_OP,		-1)
OP ("break",	Y_BREAK_OP,	R1d_TYPE_INST,		0x0000000d)
OP ("c.eq.d",	Y_C_EQ_D_OP,	FP_CMP_TYPE_INST,	0x46200032)
OP ("c.eq.s",	Y_C_EQ_S_OP,	FP_CMP_TYPE_INST,	0x46000032)
OP ("c.f.d",	Y_C_F_D_OP,	FP_CMP_TYPE_INST,	0x46200030)
OP ("c.f.s",	Y_C_F_S_OP,	FP_CMP_TYPE_INST,	0x46000030)
OP ("c.le.d",	Y_C_LE_D_OP,	FP_CMP_TYPE_INST,	0x4620003e)
OP ("c.le.s",	Y_C_LE_S_OP,	FP_CMP_TYPE_INST,	0x4600003e)
OP ("c.lt.d",	Y_C_LT_D_OP,	FP_CMP_TYPE_INST,	0x4620003c)
OP ("c.lt.s",	Y_C_LT_S_OP,	FP_CMP_TYPE_INST,	0x4600003c)
OP ("c.nge.d",	Y_C_NGE_D_OP,	FP_CMP_TYPE_INST,	0x4620003d)
OP ("c.nge.s",	Y_C_NGE_S_OP,	FP_CMP_TYPE_INST,	0x4600003d)
OP ("c.ngl.d",	Y_C_NGL_D_OP,	FP_CMP_TYPE_INST,	0x4620003b)
OP ("c.ngl.s",	Y_C_NGL_S_OP,	FP_CMP_TYPE_INST,	0x4600003b)
OP ("c.ngle.d",	Y_C_NGLE_D_OP,	FP_CMP_TYPE_INST,	0x46200039)
OP ("c.ngle.s",	Y_C_NGLE_S_OP,	FP_CMP_TYPE_INST,	0x46000039)
OP ("c.ngt.d",	Y_C_NGT_D_OP,	FP_CMP_TYPE_INST,	0x4620003f)
OP ("c.ngt.s",	Y_C_NGT_S_OP,	FP_CMP_TYPE_INST,	0x4600003f)
OP ("c.ole.d",	Y_C_OLE_D_OP,	FP_CMP_TYPE_INST,	0x46200036)
OP ("c.ole.s",	Y_C_OLE_S_OP,	FP_CMP_TYPE_INST,	0x46000036)
OP ("c.olt.d",	Y_C_OLT_D_OP,	FP_CMP_TYPE_INST,	0x46200034)
OP ("c.olt.s",	Y_C_OLT_S_OP,	FP_CMP_TYPE_INST,	0x46000034)
OP ("c.seq.d",	Y_C_SEQ_D_OP,	FP_CMP_TYPE_INST,	0x4620003a)
OP ("c.seq.s",	Y_C_SEQ_S_OP,	FP_CMP_TYPE_INST,	0x4600003a)
OP ("c.sf.d",	Y_C_SF_D_OP,	FP_CMP_TYPE_INST,	0x46200038)
OP ("c.sf.s",	Y_C_SF_S_OP,	FP_CMP_TYPE_INST,	0x46000038)
OP ("c.ueq.d",	Y_C_UEQ_D_OP,	FP_CMP_TYPE_INST,	0x46200033)
OP ("c.ueq.s",	Y_C_UEQ_S_OP,	FP_CMP_TYPE_INST,	0x46000033)
OP ("c.ule.d",	Y_C_ULE_D_OP,	FP_CMP_TYPE_INST,	0x46200037)
OP ("c.ule.s",	Y_C_ULE_S_OP,	FP_CMP_TYPE_INST,	0x46000037)
OP ("c.ult.d",	Y_C_ULT_D_OP,	FP_CMP_TYPE_INST,	0x46200035)
OP ("c.ult.s",	Y_C_ULT_S_OP,	FP_CMP_TYPE_INST,	0x46000035)
OP ("c.un.d",	Y_C_UN_D_OP,	FP_CMP_TYPE_INST,	0x46200031)
OP ("c.un.s",	Y_C_UN_S_OP,	FP_CMP_TYPE_INST,	0x46000031)
OP ("cfc0",	Y_CFC0_OP,	R2td_TYPE_INST,		0x40400000)
OP ("cfc1",	Y_CFC1_OP,	R2td_TYPE_INST,		0x44400000)
OP ("cfc2",	Y_CFC2_OP,	R2td_TYPE_INST,		0x48400000)
OP ("cfc3",	Y_CFC3_OP,	R2td_TYPE_INST,		0x4c400000)
OP ("cop0",	Y_COP0_OP,	J_TYPE_INST,		0x40200000)
OP ("cop1",	Y_COP1_OP,	J_TYPE_INST,		0x44200000)
OP ("cop2",	Y_COP2_OP,	J_TYPE_INST,		0x48200000)
OP ("cop3",	Y_COP3_OP,	J_TYPE_INST,		0x4c200000)
OP ("ctc0",	Y_CTC0_OP,	R2td_TYPE_INST,		0x40c00000)
OP ("ctc1",	Y_CTC1_OP,	R2td_TYPE_INST,		0x44c00000)
OP ("ctc2",	Y_CTC2_OP,	R2td_TYPE_INST,		0x48c00000)
OP ("ctc3",	Y_CTC3_OP,	R2td_TYPE_INST,		0x4cc00000)
OP ("cvt.d.s",	Y_CVT_D_S_OP,	FP_R2ds_TYPE_INST,	0x46000021)
OP ("cvt.d.w",	Y_CVT_D_W_OP,	FP_R2ds_TYPE_INST,	0x46800021)
OP ("cvt.s.d",	Y_CVT_S_D_OP,	FP_R2ds_TYPE_INST,	0x46200020)
OP ("cvt.s.w",	Y_CVT_S_W_OP,	FP_R2ds_TYPE_INST,	0x46800020)
OP ("cvt.w.d",	Y_CVT_W_D_OP,	FP_R2ds_TYPE_INST,	0x46200024)
OP ("cvt.w.s",	Y_CVT_W_S_OP,	FP_R2ds_TYPE_INST,	0x46000024)
OP ("div",	Y_DIV_OP,	R2st_TYPE_INST,		0x0000001a)
OP ("div.d",	Y_DIV_D_OP,	FP_R3_TYPE_INST,	0x46200003)
OP ("div.s",	Y_DIV_S_OP,	FP_R3_TYPE_INST,	0x46000003)
OP ("divu",	Y_DIVU_OP,	R2st_TYPE_INST,		0x0000001b)
OP ("j",	Y_J_OP,		J_TYPE_INST,		0x08000000)
OP ("jal",	Y_JAL_OP,	J_TYPE_INST,		0x0c000000)
OP ("jalr",	Y_JALR_OP,	R2ds_TYPE_INST,		0x00000009)
OP ("jr",	Y_JR_OP,	R1s_TYPE_INST,		0x00000008)
OP ("l.d",	Y_L_D_POP,	PSEUDO_OP,		-1)
OP ("l.s",	Y_L_S_POP,	PSEUDO_OP,		-1)
OP ("la",	Y_LA_POP,	PSEUDO_OP,		-1)
OP ("lb",	Y_LB_OP,	I2a_TYPE_INST,		0x80000000)
OP ("lbu",	Y_LBU_OP,	I2a_TYPE_INST,		0x90000000)
OP ("ld",	Y_LD_POP,	PSEUDO_OP,		-1)
OP ("lh",	Y_LH_OP,	I2a_TYPE_INST,		0x84000000)
OP ("lhu",	Y_LHU_OP,	I2a_TYPE_INST,		0x94000000)
OP ("li",	Y_LI_POP,	PSEUDO_OP,		-1)
OP ("li.d",	Y_LI_D_POP,	PSEUDO_OP,		-1)
OP ("li.s",	Y_LI_S_POP,	PSEUDO_OP,		-1)
OP ("lui",	Y_LUI_OP,	I1t_TYPE_INST,		0x3c000000)
OP ("lw",	Y_LW_OP,	I2a_TYPE_INST,		0x8c000000)
OP ("lwc0",	Y_LWC0_OP,	I2a_TYPE_INST,		0xc0000000)
OP ("lwc1",	Y_LWC1_OP,	FP_I2a_TYPE_INST,	0xc4000000)
OP ("lwc2",	Y_LWC2_OP,	I2a_TYPE_INST,		0xc8000000)
OP ("lwc3",	Y_LWC3_OP,	I2a_TYPE_INST,		0xcc000000)
OP ("lwl",	Y_LWL_OP,	I2a_TYPE_INST,		0x88000000)
OP ("lwr",	Y_LWR_OP,	I2a_TYPE_INST,		0x98000000)
OP ("mfc0",	Y_MFC0_OP,	CP_TYPE_INST,		0x40000000)
OP ("mfc1",	Y_MFC1_OP,	CP_TYPE_INST,		0x44000000)
OP ("mfc1.d",	Y_MFC1_D_POP,	PSEUDO_OP,		-1)
OP ("mfc1.s",	Y_MFC1_OP,	CP_TYPE_INST,		0x44000000)
OP ("mfc2",	Y_MFC2_OP,	CP_TYPE_INST,		0x48000000)
OP ("mfc3",	Y_MFC3_OP,	CP_TYPE_INST,		0x4c000000)
OP ("mfhi",	Y_MFHI_OP,	R1d_TYPE_INST,		0x00000010)
OP ("mflo",	Y_MFLO_OP,	R1d_TYPE_INST,		0x00000012)
OP ("mov.d",	Y_MOV_D_OP,	FP_MOV_TYPE_INST,	0x46200006)
OP ("mov.s",	Y_MOV_S_OP,	FP_MOV_TYPE_INST,	0x46000006)
OP ("move",	Y_MOVE_POP,	PSEUDO_OP,		-1)
OP ("mtc0",	Y_MTC0_OP,	CP_TYPE_INST,		0x40800000)
OP ("mtc1",	Y_MTC1_OP,	CP_TYPE_INST,		0x44800000)
OP ("mtc1.d",	Y_MTC1_D_POP,	PSEUDO_OP,		-1)
OP ("mtc2",	Y_MTC2_OP,	CP_TYPE_INST,		0x48800000)
OP ("mtc3",	Y_MTC3_OP,	CP_TYPE_INST,		0x4c800000)
OP ("mthi",	Y_MTHI_OP,	R1s_TYPE_INST,		0x00000011)
OP ("mtlo",	Y_MTLO_OP,	R1s_TYPE_INST,		0x00000013)
OP ("mul",	Y_MUL_POP,	PSEUDO_OP,		-1)
OP ("mul.d",	Y_MUL_D_OP,	FP_R3_TYPE_INST,	0x46200002)
OP ("mul.s",	Y_MUL_S_OP,	FP_R3_TYPE_INST,	0x46000002)
OP ("mulo",	Y_MULO_POP,	PSEUDO_OP,		-1)
OP ("mulou",	Y_MULOU_POP,	PSEUDO_OP,		-1)
OP ("mult",	Y_MULT_OP,	R2st_TYPE_INST,		0x00000018)
OP ("multu",	Y_MULTU_OP,	R2st_TYPE_INST,		0x00000019)
OP ("neg",	Y_NEG_POP,	PSEUDO_OP,		-1)
OP ("neg.d",	Y_NEG_D_OP,	FP_R2ds_TYPE_INST,	0x46200007)
OP ("neg.s",	Y_NEG_S_OP,	FP_R2ds_TYPE_INST,	0x46000007)
OP ("negu",	Y_NEGU_POP,	PSEUDO_OP,		-1)
OP ("nop",	Y_NOP_POP,	PSEUDO_OP,		-1)
OP ("nor",	Y_NOR_OP,	R3_TYPE_INST,		0x00000027)
OP ("not",	Y_NOT_POP,	PSEUDO_OP,		-1)
OP ("or",	Y_OR_OP,	R3_TYPE_INST,		0x00000025)
OP ("ori",	Y_ORI_OP,	I2_TYPE_INST,		0x34000000)
OP ("rem",	Y_REM_POP,	PSEUDO_OP,		-1)
OP ("remu",	Y_REMU_POP,	PSEUDO_OP,		-1)
OP ("rfe",	Y_RFE_OP,	NOARG_TYPE_INST,	0x42000010)
OP ("rol",	Y_ROL_POP,	PSEUDO_OP,		-1)
OP ("ror",	Y_ROR_POP,	PSEUDO_OP,		-1)
OP ("s.d",	Y_S_D_POP,	PSEUDO_OP,		-1)
OP ("s.s",	Y_S_S_POP,	PSEUDO_OP,		-1)
OP ("sb",	Y_SB_OP,	I2a_TYPE_INST,		0xa0000000)
OP ("sd",	Y_SD_POP,	PSEUDO_OP,		-1)
OP ("seq",	Y_SEQ_POP,	PSEUDO_OP,		-1)
OP ("sge",	Y_SGE_POP,	PSEUDO_OP,		-1)
OP ("sgeu",	Y_SGEU_POP,	PSEUDO_OP,		-1)
OP ("sgt",	Y_SGT_POP,	PSEUDO_OP,		-1)
OP ("sgtu",	Y_SGTU_POP,	PSEUDO_OP,		-1)
OP ("sh",	Y_SH_OP,	I2a_TYPE_INST,		0xa4000000)
OP ("sle",	Y_SLE_POP,	PSEUDO_OP,		-1)
OP ("sleu",	Y_SLEU_POP,	PSEUDO_OP,		-1)
OP ("sll",	Y_SLL_OP,	R2sh_TYPE_INST,		0x00000000)
OP ("sllv",	Y_SLLV_OP,	R3sh_TYPE_INST,		0x00000004)
OP ("slt",	Y_SLT_OP,	R3_TYPE_INST,		0x0000002a)
OP ("slti",	Y_SLTI_OP,	I2_TYPE_INST,		0x28000000)
OP ("sltiu",	Y_SLTIU_OP,	I2_TYPE_INST,		0x2c000000)
OP ("sltu",	Y_SLTU_OP,	R3_TYPE_INST,		0x0000002b)
OP ("sne",	Y_SNE_POP,	PSEUDO_OP,		-1)
OP ("sra",	Y_SRA_OP,	R2sh_TYPE_INST,		0x00000003)
OP ("srav",	Y_SRAV_OP,	R3sh_TYPE_INST,		0x00000007)
OP ("srl",	Y_SRL_OP,	R2sh_TYPE_INST,		0x00000002)
OP ("srlv",	Y_SRLV_OP,	R3sh_TYPE_INST,		0x00000006)
OP ("sub",	Y_SUB_OP,	R3_TYPE_INST,		0x00000022)
OP ("sub.d",	Y_SUB_D_OP,	FP_R3_TYPE_INST,	0x46200001)
OP ("sub.s",	Y_SUB_S_OP,	FP_R3_TYPE_INST,	0x46000001)
OP ("subu",	Y_SUBU_OP,	R3_TYPE_INST,		0x00000023)
OP ("sw",	Y_SW_OP,	I2a_TYPE_INST,		0xac000000)
OP ("swc0",	Y_SWC0_OP,	I2a_TYPE_INST,		0xe0000000)
OP ("swc1",	Y_SWC1_OP,	FP_I2a_TYPE_INST,	0xe4000000)
OP ("swc2",	Y_SWC2_OP,	I2a_TYPE_INST,		0xe8000000)
OP ("swc3",	Y_SWC3_OP,	I2a_TYPE_INST,		0xec000000)
OP ("swl",	Y_SWL_OP,	I2a_TYPE_INST,		0xa8000000)
OP ("swr",	Y_SWR_OP,	I2a_TYPE_INST,		0xb8000000)
OP ("syscall",	Y_SYSCALL_OP,	NOARG_TYPE_INST,	0x0000000c)
OP ("tlbp",	Y_TLBP_OP,	NOARG_TYPE_INST,	0x42000008)
OP ("tlbr",	Y_TLBR_OP,	NOARG_TYPE_INST,	0x42000001)
OP ("tlbwi",	Y_TLBWI_OP,	NOARG_TYPE_INST,	0x42000002)
OP ("tlbwr",	Y_TLBWR_OP,	NOARG_TYPE_INST,	0x42000006)
OP ("ulh",	Y_ULH_POP,	PSEUDO_OP,		-1)
OP ("ulhu",	Y_ULHU_POP,	PSEUDO_OP,		-1)
OP ("ulw",	Y_ULW_POP,	PSEUDO_OP,		-1)
OP ("ush",	Y_USH_POP,	PSEUDO_OP,		-1)
OP ("usw",	Y_USW_POP,	PSEUDO_OP,		-1)
OP ("xor",	Y_XOR_OP,	R3_TYPE_INST,		0x00000026)
OP ("xori",	Y_XORI_OP,	I2_TYPE_INST,		0x38000000)
