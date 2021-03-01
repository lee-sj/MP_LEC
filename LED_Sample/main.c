/*******************************************************************************
  LED ���� ���α׷�
  
  ���� : ������ �����̸��� LED �Һ��� ������ �̵��Ѵ�.

  ��Ʈ ���� :
    ARM Cortex-M3 ����� ��ƮA (PA0 ~ PA7)�� 8�� ���̺� �̿��ؼ�
    LED����� LED0~7�� �����Ѵ�.

  ���̺귯�� ���� :
    1) GPIO_InitTypeDef ����ü
      Library\inc ������ stm32f10x_gpio.h �� ����� GPIO ����� ����ü �̴�.

    typedef struct
      {
        u16 GPIO_Pin; 
        => ����� ���� ��å�Ѵ�. GPIO_Pin_x (x = 0 ~ 15 ,All)
        GPIOSpeed_TypeDef GPIO_Speed;
        =>  �ش� ���� ����Ŭ���� �����Ѵ�. GPIO_Speed_xMHz (x = 10,2,50)
        GPIOMode_TypeDef GPIO_Mode;
        =>  �ش� ���� ����� ��带 �����Ѵ�.
            GPIO_Mode_AIN           
            GPIO_Mode_IN_FLOATING   
            GPIO_Mode_IPD           
            GPIO_Mode_IPU 
            GPIO_Mode_Out_OD
            GPIO_Mode_Out_PP
            GPIO_Mode_AF_OD 
            GPIO_Mode_AF_PP 
      }GPIO_InitTypeDef;
    
    2)  Init_STM32F103() �Լ�
        System_func.c�� ����� �ý��� �ʱ�ȭ �Լ�. ���� ���� Ŭ��(72MHz)��
        �ֺ� Device Ŭ�� ���� �� Vector Table base location�� �����Ѵ�.
        
    3)  RRCC_APB2PeriphClockCmd(u32 RCC_APB2Periph, FunctionalState NewState)
        �� �Լ��� APB2(Advanced Peripheral Bus 2)������ ����Ǿ� �ִ� �ֺ������
        ���� Ŭ���� �����Ѵ�.
        ù��° �Ű������� ����Ŭ���� ������ APB2�� ����� �ֺ���⸦ �����ϸ� �Ǵµ�,
        RCC_APB2Periph�� stm32f10x_rcc.h�� ����Ǿ� �ִ� �Ʒ���
        ��ũ�� ����� �Է��ϸ� �Ǹ�, �ι�° �Ű������� ENABLE �Ǵ� DISABLE �� �Է��Ѵ�.

        // APB2 peripheral 
        #define RCC_APB2Periph_AFIO              ((u32)0x00000001)
        #define RCC_APB2Periph_GPIOA             ((u32)0x00000004)
        #define RCC_APB2Periph_GPIOA             ((u32)0x00000008)
        #define RCC_APB2Periph_GPIOC             ((u32)0x00000010)
        #define RCC_APB2Periph_GPIOD             ((u32)0x00000020)
        #define RCC_APB2Periph_GPIOE             ((u32)0x00000040)
        #define RCC_APB2Periph_ADC1              ((u32)0x00000200)
        #define RCC_APB2Periph_ADC2              ((u32)0x00000400)
        #define RCC_APB2Periph_TIM1              ((u32)0x00000800)
        #define RCC_APB2Periph_SPI1              ((u32)0x00001000)
        #define RCC_APB2Periph_USART1            ((u32)0x00004000)
        #define RCC_APB2Periph_ALL               ((u32)0x00005E7D)

    4)  GPIO_ResetBits�Լ��� ù��° �Ű������� ������ ��Ʈ�� (GPIOx)
        �ι�° �Ű������� �����ϴ� ��(��)�� ����� 0���� ����Ѵ�.
        ����, ��ƮA(GPIOA)�� ���� High(1)������, GPIO_ResetBits(GPIOA,GPIO_Pin_1)
        �Լ��� ȣ���ϸ�, ��ƮA�� 0xFFFD �� �ȴ�.
        GPIO_SetBits()�Լ��� �ش����� high�� ����Ѵ�.
        GPIO_Write(GPIO_TypeDef* GPIOx, u16 PortVal)�Լ��� GPIOx�� ���� ��°�����
        ������� PortVal ���� ����Ѵ�.
      

  �ҽ� ���� : 
    1)  �ý��ۿ� �ʿ��� ��������� �����Ѵ�.
    2)  Delay�Լ�����
    3)  �ý��� �ʱ�ȭ
    4)  GPIOA�� ����Ŭ���� �ΰ��Ѵ�.
    5)  GPIOA�� ������� ����Ŭ���� 50MHz�� �ؼ� ��������� �����Ѵ�.
    6)  0������ �ǹ��ϴ� GPIOA,GPIO_Pin_0�� 0x0001 �� ���� ������
        GPIO_ResetBits�Լ��� ��ƮA�� LED_data������ �ǹ��ϴ� ���� Ŭ�����Ѵ�.
        �׸���  LED_data�� ��Ĭ�� ����Ʈ�ؼ� ��ġ�� �̵���Ų��. 
        0x80�϶�, ����Ʈ�� �ϸ� �����÷ο찡 �߻��ϹǷ�, �̶��� 1���� �ʱ�ȭ�Ѵ�.
        ���� LED_data�� �ɸ�ŭ GPIOA (��ƮA)�� High���� ����Ѵ�.
        
*******************************************************************************/

//  1)
#include "stm32f10x_lib.h"
#include "System_func.h"

//  2)
void Delay(vu32 nCount);


int main(void)
{
//  3)
  Init_STM32F103();
  
  GPIO_InitTypeDef GPIO_InitStructure;

  unsigned int LED_data = 0x0080; //LED ���� �����ϴ� ����    
  
//  4)
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  
//  5)
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1 | GPIO_Pin_2| GPIO_Pin_3| 
  GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

//  6)
  while (1)  {

    GPIO_ResetBits(GPIOA, LED_data);
  
    if(LED_data == 0x0080)
      LED_data = 0x0001;
     else
       LED_data<<=1;

    GPIO_SetBits(GPIOA, LED_data);
    // Delay(0xAFFFF);
  }
  
}//end main


void Delay(vu32 nCount)
{
  for(; nCount != 0; nCount--);
}


// 201302386@hufs.ac.kr lee-sj