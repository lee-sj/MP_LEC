        NAME    main
        
        PUBLIC  __iar_program_start
        
        SECTION .intvec : CODE (2)
        CODE32
        
__iar_program_start
        B       main

        
        SECTION .text : CODE (2)
        CODE32

main    
        // Assign values 1 to3 into r0 to r2 using MOV instruction
        mov r0, #1
        mov r1, #2
        mov r2, #3
        
        // Move value of r2 into r using MOV instruction
        mov r3, r2
        
        // Let r4 point to memory address of 0x20000000 using MOV instruction or LDR instruction
        ldr r4, =0x20000000
        
        // https://azeria-labs.com/load-and-store-multiple-part-5 
        
        // Store multile values of r0 to r4 into memory address pointed by r4 STM instruction
        stmia r4, {r0-r3}
        
        // Load multiple data saved at memory address pointed by r4 into r5 to r8 with increment of address by 4 using LDM instruction
        ldmia r4, {r5-r8}
        
        
        NOP

        END
