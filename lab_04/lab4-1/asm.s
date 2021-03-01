        NAME    main
        
        PUBLIC  __iar_program_start
        
        SECTION .intvec : CODE (2)
        // CODE32
        
__iar_program_start
        B       main

        
        SECTION .text : CODE (2)
        // CODE32

main    
        // 1. Store 10 integer values at memory[0x20000000]~[0x20000024]

        // Assign 10 integer values into r0 to r9 using MOV instruction
        mov r0, #6
        mov r1, #5
        mov r2, #7
        mov r3, #4
        mov r4, #8
        mov r5, #3
        mov r6, #9
        mov r7, #2
        mov r8, #10
        mov r9, #1

        // Let r10 point to memory address of 0x20000000 using MOV instruction 
        mov r10, #0x20000000
        // Store multile values of r0 to r9 into memory address pointed by r10 STM instruction
        stmia r10, {r0-r9}
        
        // 2. Branch with link to Search subroutine
        BL search+1


        // 4. Returning from the Search subroutine Save the maximum value to memory[0x20000028]
        ldr r12, =0x20000028    // Let r12 point to memory address of 0x20000028 using LDR instruction
        str r0, [r12]       // Store maximum value(r0) to memory(r12)

        nop
        nop


        // 3. In Search subroutine
search
        // Load (first and second)two data saved at memory address pointed by r10 into r0 with increment of address by 4 using LDR instruction
        ldr r0, [r10], #4
        ldr r1, [r10], #4
        
        // Move into Loop 
loop    
        // 3-1. Find maximum value from 10 integer values in that memory
        cmp r0, r1              // Compare r0, r1 
        ite gt                  // If r0 is great than r1
        movgt r0, r0           // Biger Num Assign r0 to r0
        movle r0, r1           // Smaller Num Assign r1 to r
        ldr r1, [r10], #4       // Load (next) data saved at memory address potinted by r10 into r1 with increment of address by 4 using LDR instruction
        // 3-2 Save the maximum value( Assigned by loop into r11 ) to r0
        cmp r1, #0              // Compare r1, 0 ( means - next data is exist)
        bne loop                // if not branch to loop (this line make loop)

        // 3-3 return 
        mov pc, lr
        
        NOP
        
        END
        // 201302386@hufs.ac.kr lee-sj