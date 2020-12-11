        NAME    main
        
        PUBLIC  __iar_program_start
        
        SECTION .intvec : CODE (2)
        CODE32
        
__iar_program_start
        B       main

        
        SECTION .text : CODE (2)
        CODE32

main           
        // Assign some 1 byte hex values to r0
        mov r0, #0xfe // 11111110 을 예시로 r0 레지스터에 assign한다. 
        mov r1, #1 // and 를 통해서 1의 숫자를 카운트하기위한 상수 1을 r1 에 assign한다
        mov r10, #0 // 
        mov r3, #0 // 비교하는 숫자의 갯수인 8만큼 반복해주기 위한 카운터를 r3 에 assign한다. 

HERE
        and r2, r1, r0 // Find number of 1's in r0 for binary expression
        cmp r2, #1 // 1이 아닐경우 jump 하여 r10을 증가하지 않는다. 
        bne JMP
        add r10, r10, #1 // Save number of 1's to r10
        
JMP
        add r3, r3, #1 // 반복횟수를 나타내는 상수를 증가시킨다. 
        lsr r0, r0, #1 // 오른쪽으로 비트를 밀어서 다음 숫자를 비교할수있게 해준다. 
        cmp r3, #8  // 반복 상수가 8인지 확인한다. 
        beq LOOPOUT // 8 일경우 반복문 밖으로 나간다. 8이 아닐경우 해당 코드를 무시하고 아래 코드로 진행
        b HERE // beq 에 걸리지 않은 8 이하의 경우에 HERE 로 보내서 반복문을 만든다. 
        
LOOPOUT

        NOP
        
        END
