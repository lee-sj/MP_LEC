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
        mov r0, #1
        mov r1, #2
        mov r2, #3
        mov r3, r2
        mov r4, #0x20000000
        
        // ������ 32bit �� ����Ѵٸ�? ??? 
        // ldr r5, =0x22222222
        
        str r0, [r4, #0]
        
        NOP  // ?? �̰� ������ ���������� ������ ���ϴ°� ��?? 
        
        // memory �� LSB = 

        // NOP  // no operation , �Ѱ��� ������ �Ѱ��� ���� 
        // B main // branch main ���� ���� �ڵ� 
        
        
        
        // disassembly 
        // �޸� ����   ���� �ڵ�   �Ӻ��� �ڵ�  

        END
