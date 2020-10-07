        NAME    main
        
        PUBLIC  __iar_program_start
        
        SECTION .intvec : CODE (2)
        // CODE32
        
__iar_program_start
        B       main

        
        SECTION .text : CODE (2)
        // CODE32

main    
        mov r0, #5
        mov r1, #4
        mov r2, #6
        
        ldr r10, =0x20000000
        
        stmia r10, {r0-r2}

        mov r0, #0
        mov r1, #0
        mov r2, #0
        
        BL search+1

search
        mov r10, #0x20000000
        ldr r0, [r10], #4
        
loop
        
        ldr r1, [r10], #4
        cmp r0, r1
        ite gt
        movgt r3, r0
        movle r4, r1
        cmp r1, #0
        bne loop


        NOP
        
        END
