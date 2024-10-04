#include "I2C.h"

/* I2C Pin Mapping
	 * PB6 - I2C1_SCL
	 * PB9 - I2C1_SDA
*/

void I2C1_Init(void)
{
    // Enable the I2C1 and GPIOB clocks
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    // Configure PB6 (SCL) and PB9 (SDA) for I2C alternate function
    GPIOB->MODER &=~((3U<<12) | (3U<<18));
    GPIOB->MODER |= (2U<<12) | (2U<<18);
    GPIOB->AFR[0] |=  (4U<<0);
    GPIOB->AFR[1] |= (4U<<4);
    // Set PB6 & PB9 to Open-drain
    GPIOB->OTYPER |= (1U<<6) | (1U<<9);
    // Set PB6 & PB9 to High Speed
    GPIOB->OSPEEDR |= (3U<<12) | (3U<<18);
    // Pull Up PB6 & PB9
    GPIOB->PUPDR |= (1U<<12) | (1U<<18);

    // Reset I2C1 to clear any previous settings
    I2C1->CR1 |= I2C_CR1_SWRST;
    I2C1->CR1 &= ~I2C_CR1_SWRST;
    // Set the I2C clock frequency (APB1 is running at 42MHz)
    I2C1->CR2 = 42;  // 42 MHz APB1 clock
    // Configure clock control for 400kHz I2C operation
    I2C1->CCR = 0x50;  // CCR = 80, Fast mode, 400kHz (see reference manual for calculations)
    I2C1->TRISE = 43;  // Maximum rise time
    // Enable I2C1
    I2C1->CR1 |= I2C_CR1_PE;
}

void I2C1_Start(void)
{
	// Generate start condition
    I2C1->CR1 |= I2C_CR1_START;
    // Wait for start condition generated
    while (!(I2C1->SR1 & I2C_SR1_SB));
}

void I2C1_SendAddress(uint8_t address, bool mode)
{
	if(mode) // Execute in READ Mode
	{
		// Send the 7-bit address with the read bit
		I2C1->DR = ((address << 1) | 0x01);
	}
	else     // Execute in WRITE Mode
	{
		// Send the 7-bit address with the write bit
		I2C1->DR = (address << 1);
	}
	// Wait for address acknowledgment
    while (!(I2C1->SR1 & I2C_SR1_ADDR));
    // Clear the ADDR flag by reading SR2
    (void)I2C1->SR2;
}

void I2C1_SendData(uint8_t data)
{
    // Wait for data register empty
    while (!(I2C1->SR1 & I2C_SR1_TXE));
	// Load data into the data register
    I2C1->DR = data;
}

// Function to receive a byte of data on I2C1
uint8_t I2C1_ReadData(void)
{
	// Wait for data register to be filled
	while (!(I2C1->SR1 & I2C_SR1_RXNE));
	// Load data into the variable
    uint8_t data = I2C1->DR;
    // Return variable
    return data;
}

void I2C1_EnableACK(void)
{
	// Enable acknowledgment
	I2C1->CR1 |= I2C_CR1_ACK;
}

void I2C1_DisableACK(void)
{
	// Disable acknowledgment
	I2C1->CR1 &= ~I2C_CR1_ACK;
	// Clear SR2
	(void)I2C1->SR2;
}

void I2C1_Stop(void)
{
	// Generate stop condition
    I2C1->CR1 |= I2C_CR1_STOP;
}
