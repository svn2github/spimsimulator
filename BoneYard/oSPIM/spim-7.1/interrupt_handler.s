	.kdata
buffer: .space 80
bufptr: .word buffer
__hey: .asciiz "r"
__yo: .asciiz "w"
s0:	.word 0
s1:	.word 0
s2:	.word 0
s3:	.word 0
s4:	.word 0


	.ktext 0x80000180
  .set noat
  move $k1, $at
  .set at
  sw $k1, s0
  sw $v0, s1
  sw $a0, s2
  sw $t0, s3
  sw $t1, s4

  mfc0 $k0, $13  # Cause

  and $k1, $k0, 0x00000800
  bne $k1, 0, readinthandler

  and $k1, $k0, 0x00000400
  bne $k1, 0, writeinthandler

  # Huh?
  li $v0, 10
  syscall


readinthandler:
  #li $v0, 11
  #lbu $a0, __hey
  #syscall

  la $t0, 0xffff0004
  lw $t1, 0($t0)

  bne $t1, 13, skipcr
  li $t1, 10

skipcr:

  #li $v0, 1
  #move $a0, $t1
  #syscall

  lw $t0, bufptr
  sb $t1, 0($t0)
  add $t0, $t0, 1
  sw $t0, bufptr

  bne $t1, 10, done

  # Reset pointer.

  la $t0, buffer
  sw $t0, bufptr

  # switch to write mode.
  # Turn off read interrupts
  la $t0, 0xffff0000
  lw $t1, 0($t0)
  and $t1, $t1, 0xFFFFFFFD
  sw $t1, 0($t0)


  # Change detection of interrupts.
  #mfc0 $t0, $12
  #and $t0, $t0, 0xFFFFF7FF
  #or $t0, $t0, 0x00000400
  #mtc0 $t0, $12 

  # Turn on write interrupts.
  la $t0, 0xffff0008
  #sw $0, 4($t0)   # Flush.
  lw $t1, 0($t0)
  or $t1, $t1, 0x2
  sw $t1, 0($t0)
   
b done

writeinthandler:
  #li $v0, 4
  #la $a0, __yo
  #syscall

  lw $t0, bufptr
  lb $t1, 0($t0)
  add $t0, $t0, 1
  sw $t0, bufptr

  #li $v0, 1
  #move $a0, $t1
  #syscall

  la $t0, 0xFFFF0008
  #sw $0, 4($t0)
  sw $t1, 4($t0)

  bne $t1, 10, done

  la $t0, buffer
  sw $t0, bufptr

  #li $v0, 1
  #li $a0, 9999
  #syscall

  # switch to write mode.
  # Turn off write interrupts.
  la $t0, 0xffff0008
  lw $t1, 0($t0)
  and $t1, $t1, 0xFFFFFFFD
  sw $t1, 0($t0)

  #li $v0, 1
  #mfc0 $a0, $13
  #syscall
  #li $v0, 1
  #lw $a0, 0xffff0008
  #syscall

  # Change detection of interrupts.
  #mfc0 $t0, $12
  #and $t0, $t0, 0xFFFFFBFF
  #or $t0, $t0, 0x00000800
  #mtc0 $t0, $12 

  # Turn on read interrupts
  la $t0, 0xffff0000
  lw $t1, 0($t0)
  or $t1, $t1, 0x2
  sw $t1, 0($t0)

done:
  lw $t1, s4
  lw $t0, s3
  lw $a0, s2
  lw $v0, s1
  lw $k1, s0
  .set noat
  move $at, $k1
  .set at
mtc0 $0 $13		# Clear Cause register

	#mfc0 $k0 $14		# EPC (return to EPC)

	#rfe			# Return from exception handler
	#jr $k0
  #      nop
  eret


# Standard startup code.  Invoke the routine "main" with arguments:
#	main(argc, argv, envp)
#
	.text
	.globl __start
__start:
	lw $a0, 0($sp)		# argc
	addiu $a1, $sp, 4	# argv
	addiu $a2, $a1, 4	# envp
	sll $v0, $a0, 2
	addu $a2, $a2, $v0
	jal main
        nop

	li $v0 10
	syscall			# syscall 10 (exit)

	.globl __eoth
__eoth:
