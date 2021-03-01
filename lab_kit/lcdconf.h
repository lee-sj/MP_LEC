#ifndef LCDCONF_H
#define LCDCONF_H

#define LCD_CTRL_PORT_CLK       RCC_APB2Periph_GPIOB
#define LCD_CTRL_PORT           GPIOB
#define LCD_CTRL_RS             GPIO_Pin_0
#define LCD_CTRL_RW             GPIO_Pin_1
#define LCD_CTRL_E              GPIO_Pin_2

#define LCD_DATA_CLK            RCC_APB2Periph_GPIOA
#define LCD_DATA                GPIOA

#define LCD_LINES               2 // visible lines
#define LCD_LINE_LENGTH         16 // line length (in characters)
// cursor position to DDRAM mapping

#define LCD_LINE0_DDRAMADDR     0x00
#define LCD_LINE1_DDRAMADDR     0x40
#define LCD_LINE2_DDRAMADDR 0x14
#define LCD_LINE3_DDRAMADDR 0x54
// LCD delay
#define LCD_DELAY asm ("nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n");

#endif
// 201302386@hufs.ac.kr lee-sj