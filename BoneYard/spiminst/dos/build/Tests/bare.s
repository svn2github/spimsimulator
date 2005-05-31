# SPIM S20 MIPS simulator.
# A simple torture test for the bare SPIM simulator.
# Copyright (C) 1990-1994 James Larus, larus@cs.wisc.edu.
# ALL RIGHTS RESERVED.
#
# SPIM is distributed under the following conditions:
#
# You may make copies of SPIM for your own use and modify those copies.
#
# All copies of SPIM must retain my name and copyright notice.
#
# You may not sell SPIM or distributed SPIM in conjunction with a commerical
# product or service without the expressed written consent of James Larus.
#
# THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE.
#

# $Header: /u/faculty/larus/Software/larus/SPIM/Tests/RCS/tt.bare.s,v 1.12 1994/01/18 03:23:44 larus Exp $

# Define the exception handling code.  This must go first!
# Duplicate of standard trap handler.

	.data
	.globl __m1_
__m1_:	.asciiz "  Exception "
	.globl __m2_
__m2_:	.asciiz " occurred\n"
	.ktext 0x80000080
	mfc0 $26 $13	# Cause
	mfc0 $27 $14	# EPC
	addiu $v0, $0, 4	# syscall 4 (print_str)
#	la $a0 __m1_
	lui $a0, 0x1000
	syscall
	addiu $v0, $0, 1	# syscall 1 (print_int)
	addu $a0 $0 $26
	syscall
	addiu $v0, $0, 4	# syscall 4 (print_str)
#	la $a0 __m2_
	lui $a0, 0x1000
	ori $a0, $a0, 0xd
	syscall
	mtc0 $0, $13		# Clear Cause register
	rfe			# Return from exception handler
	addiu $27 $27 4		# Return to next instruction
	jr $27
	add $0, $0, $0		# Nop

# Standard startup code.  Invoke the routine main with no arguments.

	.text
	.globl __start
__start: jal main
	addu $0, $0, $0		# Nop
	addiu $v0, $0, 10
	syscall			# syscall 10 (exit)


	.globl main
main:
	addu $20, $0, $31	# Save return PC

# Test delayed branches:

	addiu $2, $0, 0
	beq $0 $0 l1
	addiu $2, $0, 1		# Delayed instruction
l1:	addiu $3, $0, 1
	bne $2 $3 fail
	addu $0, $0, $0		# Nop

# Test delayed loads:

	.data
	.globl d
d:	.word 101
	.text
	addiu $3, $0, 0
	lui $4 0x1000
	lw $3 0x18($4)		# address of d
	addu $0, $0, $0		# Nop
	addiu $2, $3, 0		# Delayed instruction
	addiu $2, $0, 101
	bne $2 $3 fail
	addu $0, $0, $0		# Nop

# Done !!!
	.data
	.globl sm
sm:	.asciiz "\nPassed all tests\n"
	.text
	addiu $v0, $0, 4	# syscall 4 (print_str)
#	la $a0 sm
	lui $a0, 0x1000
	ori $a0, $a0, 0x01c
	syscall
	addu $31, $0 $20	# Return PC
	jr $31			# Return from main
	add $0, $0, $0		# Nop


	.data
	.globl fm
fm:	.asciiz "Failed test\n"
	.text
fail:	addiu $v0, $0, 4	# syscall 4 (print_str)
#	la $a0 fm
	lui $a0, 0x1000
	ori $a0, $a0, 0x2f
	syscall
	addiu $v0, $0, 10	# syscall 10 (exit)
	syscall
