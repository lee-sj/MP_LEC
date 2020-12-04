#include "stm32f10x_lib.h" 
#include "System_func.h"
#include "lcd.h"

int main(void){

  Init_STM32F103();
  lcdInit();
  
  lcdDataWrite('H');
  lcdDataWrite('E');
  lcdDataWrite('L');
  lcdDataWrite('L');
  lcdDataWrite('O');
  
  lcdGotoXY(1,1);
  
  lcdPrintData("lee-sungjun",11);
  
  while(1){
  
  }  
}
