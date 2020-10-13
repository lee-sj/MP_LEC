        NAME    main
        
        PUBLIC  __iar_program_start
        
        SECTION .intvec : CODE (2)
        // CODE32
        
__iar_program_start
        B       main

        
        SECTION .text : CODE (2)
        // CODE32
main    NOP
        
        // Store values into memory address given by the table below
        
        // Store values into register by the table named Array 1
        mov r0, #3
        mov r1, #3
        mov r2, #7
        mov r3, #7
        mov r4, #2
        mov r5, #3
        mov r6, #6
        mov r7, #6
        mov r8, #4
        mov r9, #5
        // load memory address to r10
        ldr r10, =0x20000000
        // store multiple vlaues into memory
        stmia r10, {r0-r9}
        
        // Store values into register by the table named Array 2
        mov r0, #3
        mov r1, #2
        mov r2, #8
        mov r3, #5
        mov r4, #2
        mov r5, #3
        mov r6, #4
        mov r7, #6
        mov r8, #3
        mov r9, #5
        // load memory address to r11
        ldr r11, =0x20002000
        // store multiple values into memory
        stmia r11, {r0-r9}

        // set r2, r3 to 0
        mov r2, #0
        mov r3, #0
        
        NOP
        
        // LOOP start
LOOP
        // load data at 0x2000 00## into r0 & load data at 0x2000 20## into r1
        ldr r0, [r10], #4
        ldr r1, [r11], #4

        // compare r0, r1 and if equal increment r2 by 1
        cmp r0, r1
        it eq
        addeq r2, r2, #1
        
        // set r3 to loop 10 times by increment while table data ( 10 array ) and r3 compare with 10 if not branch to LOOP ( it works - loop )
        add r3, r3, #1
        cmp r3, #10
        bne LOOP
        
        
        NOP
        NOP
        
        END
