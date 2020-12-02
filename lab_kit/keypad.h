
#define IN_PORT GPIOC
#define IN_DDR RCC_APB2Periph_GPIOC
#define IN_MASK 0x000f

#define IN_1 GPIO_Pin_0
#define IN_2 GPIO_Pin_1
#define IN_3 GPIO_Pin_2
#define IN_4 GPIO_Pin_3

#define IN_LINE ( IN_1 | IN_2 | IN_3 | IN_4)

#define LINE_PORT GPIOC
#define LINE_DDR RCC_APB2Periph_GPIOC

#define LINE_1 GPIO_Pin_4
#define LINE_2 GPIO_Pin_5
#define LINE_3 GPIO_Pin_6
#define LINE_4 GPIO_Pin_7

#define LINE_MASK (LINE_1 | LINE_2 | LINE_3 | LINE_4)