
#include "stm32f10x_lib.h" 
#include"system_func.h"

void putch(u8 c);
void puts(u8 *s);
u8 getch();

int main(void) {
  
  Init_STM32F103();
  
  USART_InitTypeDef USART_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);
  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No ;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_InitStructure.USART_Clock = USART_Clock_Disable;
  USART_InitStructure.USART_CPOL = USART_CPOL_Low;
  USART_InitStructure.USART_CPHA = USART_CPHA_2Edge;
  USART_InitStructure.USART_LastBit = USART_LastBit_Disable;
  
  USART_Init(USART1, &USART_InitStructure);
  
  USART_Cmd(USART1,ENABLE);

  puts("Hello");
  puts("\n\rEnter Name : ");
  while (1){
    u8 receiveChar = getch();
    putch(receiveChar);
  }
  
 }

u8 getch() {
  u8 receive;
  while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET){
  }
  receive = USART_ReceiveData(USART1);
  return receive;
}

void putch(u8 c) {
  USART_SendData(USART1, c);
  while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); 
}

void puts(u8 *s) {
  while (*s != '\0'){
    putch(*s);
    s ++; 
  }
}