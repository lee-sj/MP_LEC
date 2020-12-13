#include "stm32f10x_lib.h" 
#include "System_func.h"
#include "lcd.h"
#include "keypad.h"

u8 cnt=0;
u8 input_passwd[4]={0}; 
u8 PASSWD[]="1234";

void INT_Configuration(void);
void Timer3_Delay_init();
void Timer3_delay_ms(u16 time);

void passcheck(u8 data);
u8 pass_check(u8 pass[]);
void reset(void);
void back_pass(void);
void delay_ms(u16 time);

void rotate_motor(u8 direction);

void init_keypad(void){
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(IN_DDR | LINE_DDR, ENABLE);

  GPIO_InitStructure.GPIO_Pin = LINE_1 | LINE_2 | LINE_3 | LINE_4;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(LINE_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = IN_1 | IN_2 | IN_3| IN_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(IN_PORT, &GPIO_InitStructure);

  lcdInit();
  lcdGotoXY(0,0);
  lcdPrintData("PASSWORD?",sizeof("PASSWORD?")-1);
  lcdGotoXY(0,1);
  lcdDataWrite('>');

}

int main(void){

  Init_STM32F103();
  
  Timer3_Delay_init();

  rotate_motor(1);
  
  delay_ms(1000);
  init_keypad();
 

  while(1){

    GPIO_ResetBits(IN_PORT,IN_LINE);
    GPIO_SetBits(IN_PORT,IN_2|IN_3|IN_4);
    if(GPIO_ReadInputDataBit(LINE_PORT,LINE_1)==0){
      passcheck('1');
    }
    else if(GPIO_ReadInputDataBit(LINE_PORT,LINE_2)==0){
      passcheck('4');
    }
    else if(GPIO_ReadInputDataBit(LINE_PORT,LINE_3)==0){
      passcheck('7');
    }
    else if(GPIO_ReadInputDataBit(LINE_PORT,LINE_4)==0){
      reset();
    }
    delay_ms(100);
    GPIO_ResetBits(IN_PORT,IN_LINE);
    GPIO_SetBits(IN_PORT,IN_1|IN_3|IN_4);
   if(GPIO_ReadInputDataBit(LINE_PORT,LINE_1)==0){
      passcheck('2');
    }
    else if(GPIO_ReadInputDataBit(LINE_PORT,LINE_2)==0){
      passcheck('5');
    }
    else if(GPIO_ReadInputDataBit(LINE_PORT,LINE_3)==0){
      passcheck('8');
    }
    else if(GPIO_ReadInputDataBit(LINE_PORT,LINE_4)==0){
      passcheck('0');
    }
    delay_ms(100);
  
   GPIO_ResetBits(IN_PORT,IN_LINE);
   GPIO_SetBits(IN_PORT,IN_1|IN_2|IN_4);
      if(GPIO_ReadInputDataBit(LINE_PORT,LINE_1)==0){
      passcheck('3');
    }
    else if(GPIO_ReadInputDataBit(LINE_PORT,LINE_2)==0){
      passcheck('6');
    }
    else if(GPIO_ReadInputDataBit(LINE_PORT,LINE_3)==0){
      passcheck('9');
    }
    else if(GPIO_ReadInputDataBit(LINE_PORT,LINE_4)==0){
      back_pass();
    }
    delay_ms(100);
  }  
}

void back_pass(void){ 
  if(cnt!=0){
    lcdGotoXY(cnt,1);
    lcdDataWrite(' ');
    lcdGotoXY(cnt,1);
    cnt--;
  }
  while((~GPIO_ReadInputData(LINE_PORT))&LINE_MASK);
}

void reset(void){
  lcdClear();
  delay_ms(1000);

  lcdGotoXY(0,0);
  lcdPrintData("Reset!!",sizeof("Reset!!")-1);

  delay_ms(1000); 

  lcdGotoXY(0,0);
  lcdPrintData("PASSWORD?",sizeof("PASSWORD?")-1);
  lcdGotoXY(0,1);
  lcdDataWrite('>');

  while((~GPIO_ReadInputData(LINE_PORT))&LINE_MASK);

  cnt=0;
}

void passcheck(u8 data){
  if(cnt != 3){
    lcdDataWrite('*');
    input_passwd[cnt++] = data;
  } else if (cnt == 3){
    lcdDataWrite('*');
    input_passwd[cnt] = data;
   
   if(pass_check(input_passwd)!=0){
    lcdGotoXY(0,0);
    lcdPrintData("Wrong password",sizeof("Wrong password")-1);
    lcdGotoXY(0,1);
    lcdPrintData("Check your password",sizeof("Check your password")-1);
      
    cnt=0;
    delay_ms(1000);

    rotate_motor(0);

    lcdClear();
    delay_ms(1000);

    init_keypad();
    } else {
    lcdClear();
    lcdGotoXY(0,0);
    lcdPrintData("Correct password",sizeof("Correct password")-1);  
    cnt=0; 
    rotate_motor(1); 
    
    lcdClear();
    delay_ms(1000);

    init_keypad();
    }
  }
  while((~GPIO_ReadInputData(LINE_PORT))&LINE_MASK);
}

u8 pass_check(u8 pass[]){
  u8 _error=0;
  u8 i;
  for(i=0;i<4;i++){
    if(pass[i]!=PASSWD[i])
   _error++;
  }
  return _error;
}

void Timer3_Delay_init(void){
  TIM_TimeBaseInitTypeDef TIM3_TimeBaseInitStruct;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
  TIM3_TimeBaseInitStruct.TIM_Prescaler = 7200 -1;
  TIM3_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
  TIM3_TimeBaseInitStruct.TIM_Period = 10-1;
  TIM3_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInit(TIM3,&TIM3_TimeBaseInitStruct);
}

void delay_ms(u16 time){
 u16 i;
 TIM_Cmd(TIM3, ENABLE);
 for(i=0; i<time; i++){
   while(TIM_GetFlagStatus(TIM3,TIM_IT_Update)==RESET);
   TIM_ClearFlag(TIM3,TIM_FLAG_Update);
 }
  TIM_Cmd(TIM3,DISABLE);
}

void rotate_motor(u8 direction){
  
  u8 index=0;      
  unsigned short count = 0;
  
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  unsigned char mot_tbl[]={0x01, 0x03, 0x02, 0x06, 0x0c, 0x0C, 0x08, 0x09};

  TIM_TimeBaseInitTypeDef TIM3_TimeBaseInitStruct;
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
  TIM3_TimeBaseInitStruct.TIM_Prescaler = 7200-1;
  TIM3_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
  TIM3_TimeBaseInitStruct.TIM_Period = 4-1;
  TIM3_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInit(TIM3,&TIM3_TimeBaseInitStruct);

  for (count=0;count<10000;count++){
    GPIO_ResetBits(GPIOC, (mot_tbl[index]<<8));
  
    if(direction==1){
      index++;
      if(index>=8) 
        index=0;
    } else {
      if(index==0) 
        index=7;
      index--;
  }
  GPIO_SetBits(GPIOC,(mot_tbl[index]<<8));
  Timer3_delay_ms(1);
  }
  GPIO_ResetBits(GPIOC, (mot_tbl[index]<<8));
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void Timer3_delay_ms(u16 time){
  TIM_Cmd(TIM3,ENABLE);

  while(time--){
    while(TIM_GetFlagStatus(TIM3,TIM_IT_Update)==RESET);
  
    TIM_ClearFlag(TIM3,TIM_FLAG_Update);
  }
  TIM_Cmd(TIM3,DISABLE);

}
