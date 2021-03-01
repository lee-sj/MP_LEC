#include "stm32f10x_lib.h" 
#include "System_func.h"
#include "lcd.h"
#include "keypad.h"

u8 cnt=0;
u8 input_passwd[4]={0};

u8 PASSWD[]="1234";
void passcheck(u8 data);
u8 pass_check(u8 pass[]);
void reset(void);
void back_pass(void);

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

  
}

void init_lcdinfo(void) {
  lcdInit();
  lcdGotoXY(0,0);
  lcdPrintData("PASSWORD?",sizeof("PASSWORD?")-1);
  lcdGotoXY(0,1);
  lcdDataWrite('>');

}
void Timer3_Delay_init(){
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

int main(void){

  Init_STM32F103();
  
  init_keypad();
  init_lcdinfo();
  Timer3_Delay_init();
 

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

void passcheck(u8 data){
  if(cnt != 3){
    lcdDataWrite(data);
    input_passwd[cnt++] = data;
  } else if (cnt == 3){
    lcdDataWrite(data);
    input_passwd[cnt] = data;
   
   if(pass_check(input_passwd)!=0){
     lcdClear();
     lcdGotoXY(0,0);
     lcdPrintData("Wrong password",sizeof("Wrong password")-1);
     lcdGotoXY(0,1);
     lcdPrintData("Check your password",sizeof("Check your password")-1);
      
      cnt=0;
      delay_ms(1000);
      init_lcdinfo();
    } else {
      lcdClear();
      lcdGotoXY(0,0);
      lcdPrintData("Correct password",sizeof("Correct password")-1);     
      delay_ms(1000);
      init_lcdinfo();
   }
   
  }
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

void back_pass(void){ 
  lcdGotoXY(cnt,1);
  lcdDataWrite(' ');
  lcdGotoXY(cnt,1);
  cnt--;
  while(~GPIO_ReadInputData(LINE_PORT)&LINE_MASK);
}

void reset(void){
 lcdClear();
 delay_ms(1000);
 lcdGotoXY(0,0);
 lcdPrintData("Reset!!",sizeof("Reset!!")-1);
 delay_ms(1000); 
 init_lcdinfo();
}
// 201302386@hufs.ac.kr lee-sj