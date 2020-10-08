        NAME    main
        
        PUBLIC  __iar_program_start
        
        SECTION .intvec : CODE (2)
       // CODE32
        
__iar_program_start
        B       main

        
        SECTION .text : CODE (2)
       // CODE32

main   
        // Write assembly program that sum from 1 to 10 and save the result at r10

        // 1 + 2 + ... + 9 + n = n(n+1)/2 Math 

        mov r0, #10 // n
        mov r3, #2

        add r1, r0, #1  // n+1

        mul r2, r0, r1 // n(n+1)

        sdiv r10, r2, r3 // n(n+1)/2


        // Simple way (only use add, mov)
        mov r0, #1
        mov r1, #2
        mov r2, #3
        mov r3, #4
        mov r4, #5
        mov r5, #6
        mov r6, #7
        mov r7, #8
        mov r8, #9
        mov r9, #10
        add r10, r0, r1
        add r11, r2, r3
        add r10, r10, r11
        
        add r11, r4, r5
        add r12, r6, r7
        add r11, r11, r12
        add r10, r10, r11
        
        add r11, r8, r9
        add r10, r10, r11
        

        NOP

        END
