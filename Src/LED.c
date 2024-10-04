#include "LED.h"

/*	LED Mapping
 * 		LD3	- PD13
 * 		LD4	- PD12
 * 		LD5 - PD14
 * 		LD6 - PD15
 */

void LED_Init(void)
{
	GPIOD->MODER |= (0x01<<24) | (0x01<<28) | (0x01<<18) | (0x01<<30);
}

void LED_ON(uint8_t led)
{
	switch(led)
	{
		case 3: GPIOD->BSRR |= (1<<13); break;
		case 4: GPIOD->BSRR |= (1<<12); break;
		case 5: GPIOD->BSRR |= (1<<14); break;
		case 6: GPIOD->BSRR |= (1<<15); break;
		default:  break;
	}
}

void LED_OFF(uint8_t led)
{
	switch(led)
	{
		case 3: GPIOD->BSRR |= (1<<29); break;
		case 4: GPIOD->BSRR |= (1<<28); break;
		case 5: GPIOD->BSRR |= (1<<30); break;
		case 6: GPIOD->BSRR |= (1<<31); break;
		default: break;
	}
}

