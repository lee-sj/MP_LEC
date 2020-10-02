        // sorce file
        NAME    main
        
        PUBLIC  __iar_program_start
        
        SECTION .intvec : CODE (2)
        CODE32
        
__iar_program_start
        B       main // branch - 분기  -> main 이라는 곳을 이동 

        
        SECTION .text : CODE (2)
        CODE32

main    
        mov r0, #1
        mov r1, #2
        mov r2, #3
        mov r3, r2
        mov r4, #0x20000000
        
        // 복잡한 32bit 를 사용한다면? ??? 
        // ldr r5, =0x22222222
        
        str r0, [r4, #0]
        
        NOP  // ?? 이게 없으면 정상적으로 실행을 안하는가 왜?? 
        
        // memory 는 LSB = 

        // NOP  // no operation , 한개의 문장이 한개의 실행 
        // B main // branch main 위와 같은 코드 
        
        
        
        // disassembly 
        // 메모리 영역   실제 코드   임베드 코드  

        END
