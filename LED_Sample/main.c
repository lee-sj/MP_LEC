/*******************************************************************************
  LED 제어 프로그램
  
  동작 : 일정한 딜레이마다 LED 불빛이 옆으로 이동한다.

  포트 연결 :
    ARM Cortex-M3 모듈의 포트A (PA0 ~ PA7)를 8핀 케이블 이용해서
    LED모듈의 LED0~7에 연결한다.

  라이브러리 설명 :
    1) GPIO_InitTypeDef 구조체
      Library\inc 폴더의 stm32f10x_gpio.h 에 선언된 GPIO 제어용 구조체 이다.

    typedef struct
      {
        u16 GPIO_Pin; 
        => 사용할 핀을 선책한다. GPIO_Pin_x (x = 0 ~ 15 ,All)
        GPIOSpeed_TypeDef GPIO_Speed;
        =>  해당 핀의 동작클럭을 결정한다. GPIO_Speed_xMHz (x = 10,2,50)
        GPIOMode_TypeDef GPIO_Mode;
        =>  해당 핀의 입출력 모드를 선택한다.
            GPIO_Mode_AIN           
            GPIO_Mode_IN_FLOATING   
            GPIO_Mode_IPD           
            GPIO_Mode_IPU 
            GPIO_Mode_Out_OD
            GPIO_Mode_Out_PP
            GPIO_Mode_AF_OD 
            GPIO_Mode_AF_PP 
      }GPIO_InitTypeDef;
    
    2)  Init_STM32F103() 함수
        System_func.c에 선언된 시스템 초기화 함수. 내부 동작 클럭(72MHz)및
        주변 Device 클럭 설정 및 Vector Table base location을 설정한다.
        
    3)  RRCC_APB2PeriphClockCmd(u32 RCC_APB2Periph, FunctionalState NewState)
        이 함수는 APB2(Advanced Peripheral Bus 2)버스에 연결되어 있는 주변기기의
        동작 클럭을 제어한다.
        첫번째 매개변수는 동작클럭을 제어할 APB2에 연결된 주변기기를 선택하면 되는데,
        RCC_APB2Periph는 stm32f10x_rcc.h에 선언되어 있는 아래의
        매크로 상수를 입력하면 되며, 두번째 매개변수는 ENABLE 또는 DISABLE 를 입력한다.

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

    4)  GPIO_ResetBits함수는 첫번째 매개변수가 선언한 포트로 (GPIOx)
        두번째 매개변수가 선언하는 핀(들)의 출력을 0으로 출력한다.
        만약, 포트A(GPIOA)가 전부 High(1)였을때, GPIO_ResetBits(GPIOA,GPIO_Pin_1)
        함수를 호출하면, 포트A는 0xFFFD 가 된다.
        GPIO_SetBits()함수는 해당핀을 high로 출력한다.
        GPIO_Write(GPIO_TypeDef* GPIOx, u16 PortVal)함수는 GPIOx의 현재 출력값과는
        상관없이 PortVal 값을 출력한다.
      

  소스 설명 : 
    1)  시스템에 필요한 헤더파일을 선언한다.
    2)  Delay함수선언
    3)  시스템 초기화
    4)  GPIOA에 동작클럭을 인가한다.
    5)  GPIOA의 모든핀을 동작클럭을 50MHz로 해서 출력핀으로 설정한다.
    6)  0번핀을 의미하는 GPIOA,GPIO_Pin_0는 0x0001 과 같기 때문에
        GPIO_ResetBits함수는 포트A로 LED_data변수가 의미하는 핀을 클리어한다.
        그리고  LED_data를 한칵씩 시프트해서 위치를 이동시킨다. 
        0x80일때, 시프트를 하면 오버플로우가 발생하므로, 이때는 1으로 초기화한다.
        계산된 LED_data의 핀만큼 GPIOA (포트A)로 High값을 출력한다.
        
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

  unsigned int LED_data = 0x0080; //LED 값을 저장하는 변수    
  
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


