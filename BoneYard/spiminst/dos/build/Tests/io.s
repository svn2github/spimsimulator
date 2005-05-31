# SPIM S20 MIPS simulator.
# Test memory mapped IO
# Copyright (C) 1992-1994 James Larus, larus@cs.wisc.edu.
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

# $Header: /u/faculty/larus/Software/larus/SPIM/Tests/RCS/tt.io.s,v 1.3 1994/01/18 03:23:44 larus Exp $


	.data
prompt: .asciiz "SPIM IO Test.  Please type 6 input lines:\n"
nl:	.asciiz "\n"
	.text
	.globl main
main:
	li $v0, 4
	la $a0, prompt
	syscall
	li $s0, 3		# loop counter

l0:
	li $t0, 0xffff0000	# recv ctrl
	li $t1, 0xffff0004	# recv buf
	li $t2, 0xffff0008	# trans ctrl
	li $t3, 0xffff000c	# trans buf

l1:
	lw $t4, 0($t0)		# Wait for receiver ready
	and $t4, $t4, 1
	beq $t4, 0, l1

	lw $t5, 0($t1)		# Read character

l2:
	lw $t4, 0($t2)		# Wait for transmitter ready
	and $t4, $t4, 1
	beq $t4, 0, l1

	sw $t5, 0($t3)		# Write character

	beq $t5, 0xa, decr	# New line (nl)
	bne $t5, 0xd, l0	# Carriage return (cr)

decr:
	add $s0, $s0, -1
	bne $s0, 0, l0


	.globl main_async
main_async:
l20:
	li $t0, 0xffff0000	# recv ctrl
	li $t1, 0xffff0004	# recv buf
	li $t2, 0xffff0008	# trans ctrl
	li $t3, 0xffff000c	# trans buf

	li $s0, 3		# loop counter

	li $t4, 0xf		# Enable device interrupts
	sw $t4, 0($t0)
	sw $t4, 0($t2)
	li $t4, 0x301
	mtc0 $t4, $12		# Enable interrupt mask (Status register)
	li $t7, 0		# 1 => char in $t6

l21:	b l21

	.ktext 0x80000080
	mfc0 $t4, $13		# Get Cause register
	sll $t5, $t4, 2
	and $t5, $t5, 0xf	# ExcCode field
	bne $t5, 0, other
				# Interrupt:
	and $t5, $t4, 0x100
	beq $t5, 0, check_trans
				# Recevier interrupt

	lw $t5, 0($t0)		# Wait for receiver ready
	and $t5, $t5, 1
	beq $t5, 0, no_recv_ready

	lw $t6, 0($t1)		# Read character
	li $t7 1
	b check_tready

check_trans:
	and $t5, $t4, 0x200
	beq $t5, 0, bad_int
				# Transmitter interrupt

check_tready:
	lw $t5, 0($t2)		# Wait for transmitter ready
	and $t5, $t5, 1
	beq $t5, 0, no_trans_ready

	bne $t7, 1, done

	sw $t6, 0($t3)		# Write character
	li $t7, 0

	beq $t6, 0xa, decr2	# New line (nl)
	bne $t6, 0xd, done	# Carriage return (cr)

decr2:
	add $s0, $s0, -1
	bne $s0, 0, done

	li $v0 10	# Exit when done
	syscall		# syscall 10 (exit)


other:  li $v0, 4
	la $a0, other_str
	syscall
	b done

no_recv_ready:
	li $v0, 4
	la $a0, no_recv_str
	syscall
	b done

bad_int:
	li $v0, 4
	la $a0, bad_int_str
	syscall
	b done

no_trans_ready:
	li $v0, 4
	la $a0, no_trans_str
	syscall
	b done

done:
	mfc0 $k1 $14	# EPC
	rfe		# Return from exception handler
#	addiu $k1 $k1 4 # Return to next instruction
	jr $k1

	.data
other_str:
	.asciiz "Non-interrupt exception\n"
no_recv_str:
	.asciiz "Receiver not ready\n"
no_trans_str:
	.asciiz "Transmitter not ready\n"
bad_int_str:
	.asciiz "Unknown interrupt\n"

