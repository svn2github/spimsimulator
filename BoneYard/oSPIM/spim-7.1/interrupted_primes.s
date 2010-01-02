        .data

nl:     .asciiz "\n"

        .text
main:   
        # Enable interrupts.
        mfc0 $t0, $12
        # Bit 11 - receiver
        # Bit 10 - transmitter
        or $t0, $t0, 0x00000800
        mtc0 $t0, $12

        # Enable global interrupts.
        mfc0 $t0, $12
        or $t0, $t0, 0x1
        mtc0 $t0, $12

        # Enable interrupts on receiver.
        la $t0, 0xffff0000
        lw $t1, 0($t0)
        or $t1, $t1, 0x2
        sw $t1, 0($t0)

        # First prime is 2.
        li $t8, 2

        # Stop searching for primes after this number.
        li $s1, 200000

outerloop:
primeloop:
        # Got enough primes altogether?  Should we stop?
        beq $s1, 0, end
        sub $s1, $s1, 1

        # Compute the next prime.
        # Start by dividing by two.
        li $t1, 2
divideloop:
        div $t8, $t1
        # Stop when quotient is less than divisor.
        mflo $t2
        bltu $t2, $t1, gotprime
        # If remainder is zero, this number is composite.
        mfhi $t3
        beq $t3, 0, nextprime
        # Try next divisor.
        add $t1, $t1, 1
        j divideloop

gotprime:
        # Found a prime number in $t8.
        #li $v0, 1
        #move $a0, $t8
        #syscall
        #li $v0, 4
        #la $a0, nl
        #syscall

nextprime:
        add $t8, $t8, 1
        j primeloop

end:    # End program.
        li $v0, 10
        syscall
