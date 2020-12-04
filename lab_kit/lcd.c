
#include "stm32f10x_lib.h"
#include "lcd.h"

GPIO_InitTypeDef GPIO_LCD;


void lcdInitHW(void){
  RCC_APB2PeriphClockCmd(LCD_CTRL_PORT_CLK, ENABLE);
  GPIO_LCD.GPIO_Pin = LCD_CTRL_RS | LCD_CTRL_RW | LCD_CTRL_E;
  GPIO_LCD.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_LCD.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(LCD_CTRL_PORT, &GPIO_LCD);
  
  GPIO_ResetBits(LCD_CTRL_PORT, LCD_CTRL_RS | LCD_CTRL_RW |LCD_CTRL_E );
  
  RCC_APB2PeriphClockCmd(LCD_DATA_CLK, ENABLE);
  GPIO_LCD.GPIO_Pin = 0x00FF;
  GPIO_LCD.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_LCD.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(LCD_DATA, &GPIO_LCD);
  
  GPIO_SetBits(LCD_DATA, 0x00FF ); 
  
}
void lcdBusyWait(void){
  
  GPIO_ResetBits(LCD_CTRL_PORT, LCD_CTRL_RS); // set RS to "control"
  GPIO_LCD.GPIO_Pin = 0x00FF;
  GPIO_LCD.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_LCD.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(LCD_DATA, &GPIO_LCD);
  
  GPIO_SetBits(LCD_DATA, 0x00FF ); //�ʱ� Ǯ��
  GPIO_SetBits(LCD_CTRL_PORT, LCD_CTRL_RW | LCD_CTRL_E); // set R/W to "read"
  LCD_DELAY; // wait
  
  while((GPIO_ReadInputDataBit(LCD_DATA, 1<<LCD_BUSY))) {
    GPIO_ResetBits(LCD_CTRL_PORT, LCD_CTRL_E); // clear "E" line
  
    LCD_DELAY; // wait
    LCD_DELAY; // wait
  
    GPIO_SetBits(LCD_CTRL_PORT, LCD_CTRL_E); // set "E" line
  
    LCD_DELAY; // wait
    LCD_DELAY; // wait
  }
  GPIO_ResetBits(LCD_CTRL_PORT, LCD_CTRL_E);// clear "E" line

}

void lcdControlWrite(u8 data){
  lcdBusyWait();
  
  GPIO_ResetBits(LCD_CTRL_PORT, LCD_CTRL_RS | LCD_CTRL_RW);
  GPIO_SetBits(LCD_CTRL_PORT, LCD_CTRL_E);  

  GPIO_LCD.GPIO_Pin = 0x00FF;
  GPIO_LCD.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_LCD.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(LCD_DATA, &GPIO_LCD);
  
  GPIO_ResetBits(LCD_DATA, 0x00FF);
  GPIO_SetBits(LCD_DATA, data); // output data, 8bits
  
  LCD_DELAY; // wait
  LCD_DELAY; // wait
  
  GPIO_ResetBits(LCD_CTRL_PORT, LCD_CTRL_E);// clear "E" line
  
  LCD_DELAY; // wait
  LCD_DELAY;
}

u8 lcdControlRead(void){
  u8 data;
  
  lcdBusyWait(); // wait until LCD not busy
  
  GPIO_LCD.GPIO_Pin = 0x00FF;
  GPIO_LCD.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_LCD.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(LCD_DATA, &GPIO_LCD);
  
  GPIO_SetBits(LCD_DATA, 0x00FF ); //�ʱ� Ǯ��
  GPIO_ResetBits(LCD_CTRL_PORT, LCD_CTRL_RS); // set RS to "control"
  
  GPIO_SetBits(LCD_CTRL_PORT, LCD_CTRL_RW); // set R/W to "read"
  GPIO_SetBits(LCD_CTRL_PORT, LCD_CTRL_E); // set "E" line
  
  LCD_DELAY; // wait
  LCD_DELAY; // wait
  
  data = (GPIO_ReadInputData(LCD_DATA)); // input data, 8bits
  
  GPIO_ResetBits(LCD_CTRL_PORT, LCD_CTRL_E); // clear "E" line
  
  return data;
}
void lcdDataWrite(u8 data){
  lcdBusyWait(); // wait until LCD not busy
  GPIO_SetBits(LCD_CTRL_PORT, LCD_CTRL_RS); // set RS to "data"
  GPIO_ResetBits(LCD_CTRL_PORT, LCD_CTRL_RW); // set R/W to "write"
  
  GPIO_SetBits(LCD_CTRL_PORT, LCD_CTRL_E); // set "E" line
  GPIO_LCD.GPIO_Pin = 0x00FF;
  GPIO_LCD.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_LCD.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(LCD_DATA, &GPIO_LCD);

  GPIO_ResetBits(LCD_DATA,0x00FF);
  GPIO_SetBits(LCD_DATA, data);

  LCD_DELAY; // wait
  LCD_DELAY; // wait

  GPIO_ResetBits(LCD_CTRL_PORT, LCD_CTRL_E);
}
u8 lcdDataRead(void){
  u8 data;

  lcdBusyWait(); // wait until LCD not busy

  GPIO_LCD.GPIO_Pin = 0x00FF;
  GPIO_LCD.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_LCD.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(LCD_DATA, &GPIO_LCD);

  GPIO_SetBits(LCD_DATA, 0x00FF ); //�ʱ� Ǯ��
  GPIO_ResetBits(LCD_CTRL_PORT, LCD_CTRL_RS); // set RS to "control"

  GPIO_SetBits(LCD_CTRL_PORT, LCD_CTRL_RW); // set R/W to "read"
  GPIO_SetBits(LCD_CTRL_PORT, LCD_CTRL_E); // set "E" line

  LCD_DELAY; // wait
  LCD_DELAY; // wait

  data = (GPIO_ReadInputData(LCD_DATA)); // input data, 8bits

  GPIO_ResetBits(LCD_CTRL_PORT, LCD_CTRL_E); // clear "E" line

  return data; 
}


void lcdInit()
{
  lcdInitHW();

  lcdControlWrite(LCD_FUNCTION_DEFAULT);
  lcdControlWrite(1<<LCD_CLR);
  lcdControlWrite(1<<LCD_ENTRY_MODE | 1<<LCD_ENTRY_INC);
  lcdControlWrite(1<<LCD_ON_CTRL | 1<<LCD_ON_DISPLAY | 1<<LCD_ON_CURSOR | 1<<LCD_ON_BLINK);
  lcdControlWrite(1<<LCD_HOME);
  lcdControlWrite(1<<LCD_DDRAM | 0x00);

}

void lcdHome(void)
{
  lcdControlWrite(1<<LCD_HOME);
}

void lcdClear(void)
{
  lcdControlWrite(1<<LCD_CLR);
}

void lcdGotoXY(u8 x, u8 y)
{
  u8 DDRAMAddr = x;
  // remap lines into proper order
  switch(y){
    case 0: DDRAMAddr = LCD_LINE0_DDRAMADDR+x; break;
    case 1: DDRAMAddr = LCD_LINE1_DDRAMADDR+x; break;
    case 2: DDRAMAddr = LCD_LINE2_DDRAMADDR+x; break;
    case 3: DDRAMAddr = LCD_LINE3_DDRAMADDR+x; break;
    default: DDRAMAddr = LCD_LINE0_DDRAMADDR+x;
  }
  // set data address
  lcdControlWrite((1<<LCD_DDRAM) | DDRAMAddr);
}

void lcdPrintData(char *data, u8 nBytes){
  u8 i;
  if (!data)
    return;
  
  for(i=0;data[i] != '\0'; i++){
    lcdDataWrite(data[i]);
  
  }
}

void lcdPrint(char *data){
  u8 i;
  if (!data)
    return;
  
  for(i=0;data[i] != '\0'; i++){
    lcdDataWrite(data[i]);
  
  }
}