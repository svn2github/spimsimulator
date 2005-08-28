# SPIM S20 MIPS simulator.
# Test of memory mapped IO.
#
# Copyright (C) 1992-2004 James Larus, larus@cs.wisc.edu.
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
prompt: .asciiz "SPIM IO Test.\nOnly runs with -mapped_io flag.\nPlease type 6 input lines:\n"
nl:	.asciiz "\n"

	.text
	.globl main
main:
	li $v0 4
	la $a0 prompt
	syscall


# Register usage:
#		s0		loop counter
#		t0		address of recv_ctrl
#		t1		address of recv_buffer
#		t2		address of trans_ctrl
#		t3		address of trans_buffer
#		t4, t5		temporaries
#		t6		char read from input
#		t7		1 => char in t6

	li $s0 3		# loop counter


	li $t0 0xffff0000	# recv ctrl
	li $t1 0xffff0004	# recv buf
	li $t2 0xffff0008	# trans ctrl
	li $t3 0xffff000c	# trans buf

# First, read and echo 3 lines of input by polling the IO registers, not through
# interrupts:

	mtc0 $0 $12		# Clear IE bit in Status reg to disable interrupts

l1:
	lw $t4 0($t0)		# Wait for receiver ready
	and $t4 $t4 1
	beq $t4 0 l1

	lw $t6 0($t1)		# Read character

l2:
	lw $t4 0($t2)		# Wait for transmitter ready
	and $t4 $t4 1
	beq $t4 0 l2

	sw $t6 0($t3)		# Write character

	beq $t6 0xa decr	# New line (nl)
	bne $t6 0xd l1		# Carriage return (cr)

decr:
	add $s0 $s0 -1		# Decrement line counter
	bne $s0 0 l1		# If not zero, get another line


# Second, read and echo 3 lines of input by through interrupts:

	mfc0 $t4 $13
	and $t4 0xffff00ff	# Clear IP bits in Cause register
	mtc0 $t4 $13

	li $s0 3		# loop counter

	li $t4 0x2		# Enable device interrupts
	sw $t4 0($t0)
	sw $t4 0($t2)

	mfc0 $t4 $12		# Enable interrupts and mask in Status reg
	ori $t4 $t4 0xff01
	mtc0 $t4 $12


l3:	b l3			# Loop waiting for interrupts


# Trap handler. Replaces the standard SPIM handler.

	.ktext 0x80000180
	mfc0 $t4 $13		# Get ExcCode field from Cause reg
	srl $t5 $t4 2
	and $t5 $t5 0x1f	# ExcCode field
	bne $t5 0 exception

# An interrupt:
	and $t5 $t4 0x800	# Check for IP3 (HW 1)
	beq $t5 0 check_trans

# Receiver interrupt:
	lw $t5 0($t0)		# Check receiver ready
	and $t5 $t5 1
	beq $t5 0 no_recv_ready	# Error if receiver is not ready

	lw $t6 0($t1)		# Read character
	li $t7 1

	beq $t6 0xa decr2	# New line (nl)
	bne $t6 0xd next	# Carriage return (cr)

decr2:
	add $s0 $s0 -1		# Decrement line counter

next:
	mfc0 $t4 $13		# Get Cause register
	and $t4 0xfffff7ff	# Clear IP3 bit
	mtc0 $t4 $13

check_trans:
	beq $t7 0 ret_handler	# No char to write yet

	and $t5 $t4 0x400	# Check for IP2 (HW 0)
	beq $t5 0 check_loop

# Transmitter interrupt:
	lw $t5 0($t2)		# Check transmitter ready
	and $t5 $t5 1
	beq $t5 0 no_trans_ready

	sw $t6 0($t3)		# Write character
	li $t7 0

	mfc0 $t4 $13		# Get Cause register
	and $t4 0xfffffbff	# Clear IP2 bit
	mtc0 $t4 $13

check_loop:
	bne $s0 0 ret_handler	# If line counter not zero, get another line

# Done echoing, so terminate program.
	li $v0 10
	syscall			# syscall 10 (exit)

# Return from handler.
ret_handler:
	mfc0 $t4 $12		# Enable interrupts and mask in Status reg
	ori $t4 $t4 0xff01
	mtc0 $t4 $12

	eret			# return to interrupted instruction


exception:
	li $v0 4		# Non-interrupt exception
	la $a0 other_str	# Print message and ignore
	syscall
	b ret_handler

no_recv_ready:
	li $v0 4		# Receiver was not ready after interrupt
	la $a0 no_recv_str	# Print message and ignore
	syscall
	b ret_handler

bad_int:
	li $v0 4		# Interrupt was not from recv or trans
	la $a0 bad_int_str	# Print message and ignore
	syscall
	b ret_handler

no_trans_ready:
	li $v0 4		# Transmitter was not ready after interrupt
	la $a0 no_trans_str	# Print message and ignore
	syscall
	b ret_handler

	.data
other_str:
	.asciiz "Non-interrupt exception\n"
no_recv_str:
	.asciiz "Receiver not ready\n"
no_trans_str:
	.asciiz "Transmitter not ready\n"
bad_int_str:
	.asciiz "Unknown interrupt\n"

