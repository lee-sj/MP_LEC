        NAME    main
        
        PUBLIC  __iar_program_start
        
        SECTION .intvec : CODE (2)
      //  CODE32
        
__iar_program_start
        B       main

        
        SECTION .text : CODE (2)
     //   CODE32

main    NOP
        
        mov r0, #1
        mov r1, #3
        
        cmp r0, r1
        
        ite gt
        movgt r2, #2
        movle r3, #9
        
        NOP

        END
