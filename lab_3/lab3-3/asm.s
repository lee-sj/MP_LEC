        NAME    main
        
        PUBLIC  __iar_program_start
        
        SECTION .intvec : CODE (2)
        CODE32
        
__iar_program_start
        B       main

        
        SECTION .text : CODE (2)
        CODE32

main           
        // Assign some 1 byte hex values to r0
        mov r0, #0xfe
        mov r1, #1
        mov r10, #0
        mov r3, #0

HERE
        and r2, r1, r0
        cmp r2, #1
        bne JMP
        add r10, r10, #1
        
JMP
        add r3, r3, #1
        lsr r0, r0, #1
        cmp r3, #8
        beq LOOPOUT
        b HERE
        
LOOPOUT
        // Find number of 1's in r0 for binary expression

        // Save number of 1's to r10


        NOP
        
        END
