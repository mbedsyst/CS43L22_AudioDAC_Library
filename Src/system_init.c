#include <stdint.h>
#include "system_stm32f4xx.h"
#include "stm32f4xx.h"

void PLLI2SClock_Config(void)
{
	// Set PLLM to 16
	RCC->PLLI2SCFGR |= (16<<RCC_PLLI2SCFGR_PLLI2SM_Pos);
	// Set PLLN to 344
	RCC->PLLI2SCFGR |= (344<<RCC_PLLI2SCFGR_PLLI2SN_Pos);
	// Set PLLR to 2
	RCC->PLLI2SCFGR |= (2<<RCC_PLLI2SCFGR_PLLI2SR_Pos);
	// Enable PLLI2S
	RCC->CR |= RCC_CR_PLLI2SON;
	// Wait for PLLI2S to be locked
	while(!(RCC->CR & RCC_CR_PLLI2SRDY));
}

void SystemInit(void)
{
	PLLI2SClock_Config();
}
