        // sorce file
        NAME    main
        
        PUBLIC  __iar_program_start
        
        SECTION .intvec : CODE (2)
        CODE32
        
__iar_program_start
        B       main // branch - �б�  -> main �̶�� ���� �̵� 

        
        SECTION .text : CODE (2)
        CODE32

main    
        // Assign values 1 to 3 into r0 to r2 using MOV instruction
        mov r0, #1
        mov r1, #2
        mov r2, #3
        
        // Move value of r2 into r3 using MOV instruction
        mov r3, r2
        
        // Let r4 point to memory address of 0x20000000 using MOV instruction or LDR instruction
        mov r4, #0x20000000
        // LDR r4, =0x20000000
        
        // Store values of r0 to r3 into memor address pointed by r4 with increment of address by 4 using STR instrucction
        str r0, [r4, #0]  // same with str r0, [r4], #4
        str r1, [r4, #4]  // same with str r1, [r4], #4
        str r2, [r4, #8]  // same with str r2, [r4], #4
        str r3, [r4, #12] // same with str r3, [r4], #4
        
        // Load data saved at memory address porinted by r4 into r5 to 48 with increment of address by 4 using LDR instruction
        
        ldr r5, [r4, #0]
        ldr r6, [r4, #4]
        ldr r7, [r4, #8]
        ldr r8, [r4, #12]
        
        NOP  // ?? �̰� ������ ���������� ������ ���ϴ°� ��?? 
        
        // memory �� LSB = 

        // NOP  // no operation , �Ѱ��� ������ �Ѱ��� ���� 
        // B main // branch main ���� ���� �ڵ� 
        
        
        // ������ 32bit �� ����Ѵٸ�? ??? 
        // ldr r5, =0x22222222        
        
        // disassembly 
        // �޸� ����   ���� �ڵ�   �Ӻ��� �ڵ�  

        END
