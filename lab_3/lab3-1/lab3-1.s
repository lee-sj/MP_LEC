        NAME    main
        
        PUBLIC  __iar_program_start
        
        SECTION .intvec : CODE (2)
        CODE32
        
__iar_program_start
        B       main

        
        SECTION .text : CODE (2)
        CODE32

main    NOP
        B main

        // Assign r0 with value 0xFFFF FFF7 (16진수)
        mov r0, #0xFFFFFFF7

        // Assign r1 with value 0x7FFF FFFF 
        mov r1, #0x7fffffff

        // Assign r2 with value #0000111b (2진수)
        mov r2, #0000111b

        // Try out ASR instruction on r0,r1 by 4 and save the result in r3,r4
        ASR r3, r0, #4
        ASR R4, r1, #4
        
        // Try out LSL instructions on r2 by 4 and save the result r5

        // Try out ROR on r2 by 4 and save the result in r7

        // Explain the results on r3 - r7


        END
