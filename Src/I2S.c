#include "I2S.h"

/* I2S Pin Mapping
	 * I2S3_WS  - PA04
	 * I2S3_SD  - PC12
	 * I2S3_CK  - PC10
	 * I2S3_MCK - PC07
*/

static void I2S3_GPIO_Init(void)
{
	// Enable clock to GPIO Port A, C & D
	RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN);
	// Configuring PA04
	GPIOA->MODER |= (0x02<<8);
	GPIOA->AFR[0] |= (0x06<<16);

	// Configure PC07, PC10, PC12
	GPIOC->MODER |= ((0x02<<14) | (0x02<<20) | (0x02<<24));
	GPIOC->AFR[0] |= (0x06<<28);
	GPIOC->AFR[1] |= ((0x06<<8) | (0x06<<16));
}

void I2S3_Init(void)
{
	I2S3_GPIO_Init();
	// Enable clock to I2S3(SPI3) Peripheral
	RCC->APB1ENR |= RCC_APB1ENR_SPI3EN;
	// Enable Clock to DMA1 Peripheral
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;

	// Set I2SDIV to 12 in SPI_I2SPR register
	SPI3->I2SPR |= (03<<0);
	// Set ODD bit in SPI_I2SPR register to 1
	SPI3->I2SPR |= SPI_I2SPR_ODD;
	// Set MCKOE bit in the SPI_I2SPR register
	SPI3->I2SPR |= SPI_I2SPR_MCKOE;
	// Set Clock Polarity to LOW in SPI_I2SCFGR register
	SPI3->I2SCFGR &= ~SPI_I2SCFGR_CKPOL;
	// Select I2S Mode in the SPI_I2SCFGR register
	SPI3->I2SCFGR |= SPI_I2SCFGR_I2SMOD;
	// Set the standard to I2S Philips in the SPI_I2SCFGR register
	SPI3->I2SCFGR &= ~SPI_I2SCFGR_I2SSTD;
	// Set Data Length to 16-bit in the SPI_I2SCFGR register
	SPI3->I2SCFGR &= ~SPI_I2SCFGR_CHLEN;
	// Set Data Width to 16-bit in the SPI_I2SCFGR register
	SPI3->I2SCFGR &= ~SPI_I2SCFGR_DATLEN;
	// Set configuration to Master - Transmitter
	SPI3->I2SCFGR |= SPI_I2SCFGR_I2SCFG_1;

	// Enable Tx DMA on SPI3
	SPI3->CR2 |= SPI_CR2_TXDMAEN;
	// Enable SPI3 IRQ
	NVIC_EnableIRQ(SPI3_IRQn);
	// Configure DMA1 Stream 7 to Channel 0
	DMA1_Stream7->CR |= (0<<DMA_SxCR_CHSEL_Pos);
	// Set Memory Increment Mode
	DMA1_Stream7->CR |= DMA_SxCR_MINC;
	// Enable Circular Mode
	DMA1_Stream7->CR |= DMA_SxCR_CIRC;
	// Enabke Transfer Complete Interrupt
	DMA1_Stream7->CR |= DMA_SxCR_TCIE;
	// Set Direction from Memory to Peripheral
	DMA1_Stream7->CR |= DMA_SxCR_DIR_0;
	// Enable DMA1_Stream7 IRQ
	NVIC_EnableIRQ(DMA1_Stream7_IRQn);
	// Enable the I2S Peripheral
	SPI3->I2SCFGR |= SPI_I2SCFGR_I2SE;
}

void I2S3_SendData_Polling(uint16_t *data, uint16_t len)
{
	uint32_t i = 0;
	// Iterate from 0 to 'len-1'
	while(i < len)
	{
		// Check if DR is empty
		while(!(SPI3->SR & SPI_SR_TXE));
		// Write 16 bit data to DR
		SPI3->DR = data[i];
		// Increment data counter
		i++;
	}
	// Wait for last data to be transferred
	while(!(SPI3->SR & SPI_SR_TXE));
	// Wait until I2S is not busy
	while(SPI3->SR & SPI_SR_BSY);
	// Read DR & SR to clear OVR Flag
	(void)SPI3->DR;
	(void)SPI3->SR;
}

void I2S3_SendData_DMA(uint16_t *data, uint16_t len)
{
	// Set Peripheral Address
	DMA1_Stream7->PAR |= (uint32_t)&SPI3->DR;
	// Set Memory Address
	DMA1_Stream7->M0AR |= (uint32_t)data;
	// Set Number of Data Items to transfer
	DMA1_Stream7->NDTR = len;
	// Fire DMA
	DMA1_Stream7->CR |= DMA_SxCR_EN;
}

void SPI3_DMA_TX_Completed(void)
{

}

void SPI3_IRQHandler(void)
{
	if ((SPI3->SR & SPI_SR_TXE) && ((SPI3->SR & SPI_SR_BSY)==0))
	{
		/* Call SPI3_DMA_TX_Completed function */
		SPI3_DMA_TX_Completed();
		/* Disable SPI Tx Buffer Empty interrupt */
		SPI3->CR2 &= ~SPI_CR2_TXEIE;
	}
}

void DMA1_Stream7_IRQHandler(void)
{
	/* Check the Intrrupt source of DMA1_Stream7 */
	if((DMA1->HISR & DMA_HISR_TCIF7) == DMA_HISR_TCIF7)
	{
		/* Enable SPI Tx buffer empty interrupt */
		SPI3->CR2 |= SPI_CR2_TXEIE;
		/* Clear Pending flag */
		DMA1->HIFCR = DMA_HIFCR_CTCIF7;
	}
}













