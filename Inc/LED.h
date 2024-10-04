#ifndef LED_H_
#define LED_H_

#define LED3	3
#define LED4	4
#define LED5	5
#define LED6	6

#include "stm32f4xx.h"

void LED_Init(void);
void LED_ON(uint8_t led);
void LED_OFF(uint8_t led);

#endif
