
#include "stm32f10x_lib.h"
#include "System_func.h"

void Delay(vu32 nCount);

int main(void)
{
  Init_STM32F103();
  
  GPIO_InitTypeDef GPIO_InitStructure;

  // unsigned int LED_data = 0x0080;    
  
  unsigned int switch_value = 0x0;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1 | GPIO_Pin_2| GPIO_Pin_3| 
  GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1 | GPIO_Pin_2| GPIO_Pin_3| 
  GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  while (1)  {

    switch_value = GPIO_ReadInputData(GPIOC);
   // GPIO_SetBits(GPIOA, switch_value);
    GPIO_Write(GPIOA, switch_value);
  
   // if(LED_data == 0x0080)
   //   LED_data = 0x0001;
   //  else
   //    LED_data<<=1;

    //GPIO_ResetBits(GPIOA, switch_value);
    Delay(0xEFFFF);
  }
  
}


void Delay(vu32 nCount)
{
  for(; nCount != 0; nCount--);
}


