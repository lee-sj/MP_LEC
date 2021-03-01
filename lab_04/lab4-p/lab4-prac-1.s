        NAME    main
        
        PUBLIC  __iar_program_start
        
        SECTION .intvec : CODE (2)
        // CODE32
        
__iar_program_start
        B       main

        
        SECTION .text : CODE (2)
        // CODE32

main    
        mov r0, #4
        mov r1, #6

        cmp r0, r1              // Compare r0, r1 
        
        NOP
        NOP
        
        ite gt                  // If r0 is great than r1
        movgt r0, r0           // Biger Num Assign r0 to r0
        movle r0, r1           // Smaller Num Assign r1 to r
 


        NOP

        END
        // 201302386@hufs.ac.kr lee-sj
