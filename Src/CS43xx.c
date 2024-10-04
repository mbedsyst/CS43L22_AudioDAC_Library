#include "CS43xx.h"

static void CS43_WriteRegister(uint8_t reg, uint8_t val)
{
	I2C1_Start();
	I2C1_SendAddress(CS43_CHIP_ADDRESS, 0);
	I2C1_SendData(reg);
	I2C1_SendData(val);
	I2C1_Stop();
}

static uint8_t CS43_ReadRegister(uint8_t reg)
{
	I2C1_Start();
	I2C1_SendAddress(CS43_CHIP_ADDRESS, 0);
	I2C1_SendData(reg);
	I2C1_Start();
	I2C1_SendAddress(CS43_CHIP_ADDRESS, 1);
	I2C1_DisableACK();
	I2C1_Stop();
	uint8_t val = I2C1_ReadData();
	return val;
}

static void CS43_RST_Init(void)
{
	// Configure PD4
	RCC->AHB1ENR |= (RCC_AHB1ENR_GPIODEN);
	GPIOD->MODER |= (0x01<<8);
	GPIOD->PUPDR |= (0x02<<8);
	GPIOD->OSPEEDR |= (0x02<<8);
}

static void CS43_RST_HIGH(void)
{
	GPIOD->BSRR |= (1<<4);
}

void CS43_Init(void)
{
	// Temporary variable to Hold register values
	uint8_t regVal;
	// Initialize and Reset the CS43_RESET pin
	CS43_RST_Init();
	CS43_RST_HIGH();
	I2C1_Init();
	I2S3_Init();
	// Power down CS43
	regVal = 0x01;
	CS43_WriteRegister(POWER_CTL1, regVal);
	// Enable Right and Left Headphones
	regVal = 0xAF;
	CS43_WriteRegister(POWER_CTL2, regVal);
	// Enable Automatic Clock Detection
	regVal = 0x80;
	CS43_WriteRegister(CLOCKING_CTL, regVal);
	// Read & Configure Interface Control 1 register
	regVal = CS43_ReadRegister(INTERFACE_CTL1);
	regVal |= 0x27;
	CS43_WriteRegister(INTERFACE_CTL1, regVal);
	// Set Passthrough A Settings
	regVal = CS43_ReadRegister(PASSTHROUGH_A_SELECT);
	regVal |= 0x01;
	CS43_WriteRegister(PASSTHROUGH_A_SELECT, regVal);
	// Set Passthrough B Settings
	regVal = CS43_ReadRegister(PASSTHROUGH_B_SELECT);
	regVal |= 0x01;
	CS43_WriteRegister(PASSTHROUGH_B_SELECT, regVal);
	// Set Miscellaneous Register settings
	regVal = CS43_ReadRegister(MISC_CTL);
	regVal = 0x02;
	CS43_WriteRegister(MISC_CTL, regVal);
	// Configure Headphones & Speaker Output
	regVal = CS43_ReadRegister(PLAYBACK_CTL2);
	regVal = 0x00;
	CS43_WriteRegister(PLAYBACK_CTL2, regVal);
	//Set Volume settings to Default
	regVal = 0x00;
	CS43_WriteRegister(PASSTHROUGH_VOL_A, regVal);
	CS43_WriteRegister(PASSTHROUGH_VOL_B, regVal);
	CS43_WriteRegister(PCM_A_VOL, regVal);
	CS43_WriteRegister(PCM_B_VOL, regVal);
}

void CS43_Start(void)
{
	uint8_t regVal;

	regVal = 0x99;
	CS43_WriteRegister(CONFIG_00, regVal);

	regVal = 0x80;
	CS43_WriteRegister(CONFIG_47, regVal);

	regVal = CS43_ReadRegister(CONFIG_32);
	regVal |= 0x80;
	CS43_WriteRegister(CONFIG_32, regVal);

	regVal = CS43_ReadRegister(CONFIG_32);
	regVal &= ~0x80;
	CS43_WriteRegister(CONFIG_32, regVal);

	regVal = 0x00;
	CS43_WriteRegister(CONFIG_00, regVal);

	regVal = 0x9E;
	CS43_WriteRegister(POWER_CTL1, regVal);
}

void CS43_Stop(void)
{
	CS43_WriteRegister(POWER_CTL1, 0x01);
}

void CS43_SetSide(uint8_t side)
{
	uint8_t regVal;
	switch(side)
	{

		case 0: // HP-B always ON, HP-A always ON
			regVal = 0xF0;
			break;
		case 1: // HP-B always ON, HP-A always ON
			regVal = 0xB0;
			break;
		case 2: // HP-B always ON, HP-A always ON
			regVal = 0xE0;
			break;
		case 3: // HP-B always ON, HP-A always ON
			regVal = 0xA0;
			break;
		default:
			break;
	}
	// Speaker B always OFF, Speaker A always OFF
	regVal |= 0x0F;
	CS43_WriteRegister(POWER_CTL2, regVal);
}

void CS43_SetVolume(uint8_t volume)
{
	uint8_t regVal;
	int8_t tempVol = volume - 50;
	tempVol = tempVol*(127/50);
	uint8_t myVol = (uint8_t)tempVol;
	regVal = myVol;
	CS43_WriteRegister(PASSTHROUGH_VOL_A, regVal);
	CS43_WriteRegister(PASSTHROUGH_VOL_B, regVal);
	regVal = VOLUME_CONVERT_B(volume);
	CS43_WriteRegister(MASTER_A_VOL, regVal);
	CS43_WriteRegister(MASTER_B_VOL, regVal);
}
