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
        mov r1, #6
        mov r2, #7
        mov r3, #4
        mov r4, #3
        mov r5, #2
        mov r6, #1
        mov r7, #8
        mov r8, #9
        mov r9, #0
        
        mov r10, #0x20000000
        
        stmia r10, {r0-r9}
        
        BL search+1
        
        
        //str r0 {r2}, #4
        //mov r0, #1
       // mov r1, #1
       // mov r2, #1
       // cmp r0, r1
        
       // it eq // if then ÀÌÄ÷
       // moveq r2, #2




        NOP

search
        mov r0, #0
        mov r10, #0x20000000
        mov r3, #0
        
loop
        ldr r0, {r10}
        cmp r2, r0
        it gt
        movgt r0, r2
        add r3 r3, #1
        
        mov pc, lr

        END
