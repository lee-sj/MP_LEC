#ifndef LCD_H
#define LCD_H

#include "stm32f10x_lib.h"
#include "lcdconf.h"

#define LCD_CLR             0

#define LCD_HOME            1

#define LCD_ENTRY_MODE      2
#define LCD_ENTRY_INC       1
#define LCD_ENTRY_SHIFT     0

#define LCD_ON_CTRL         3
#define LCD_ON_DISPLAY      2
#define LCD_ON_CURSOR       1
#define LCD_ON_BLINK        0

#define LCD_MOVE            4
#define LCD_MOVE_DISP       3
#define LCD_MOVE_RIGHT      2

#define LCD_FUNCTION        5
#define LCD_FUNCTION_8BIT   4
#define LCD_FUNCTION_2LINES 3
#define LCD_FUNCTION_10DOTS 2

#define LCD_CDRAM           6
#define LCD_DDRAM           7

#define LCD_BUSY            7

#define LCD_FUNCTION_DEFAULT 0x38

void lcdInitHW(void);
void lcdBusyWait(void);
void lcdControlWrite(u8 data);
u8 lcdControlRead(void);
void lcdDataWrite(u8 data);
u8 lcdDataRead(void);

void lcdInit();
void lcdHome(void);
void lcdClear(void);
void lcdGotoXY(u8 x, u8 y);
void lcdPrintData(char *data, u8 nBytes);
void lcdPrint(char *data);

#endif