#ifndef CS43XX_H_
#define CS43XX_H_

#include "stdint.h"
#include "I2C.h"
#include "I2S.h"

#define CS43_CHIP_ADDRESS		(0x94>>1) // 7-bit Device Address : 1001010

// CS43L22 Register Address Definitions
#define POWER_CTL1				0x02
#define POWER_CTL2				0x04
#define CLOCKING_CTL 	  		0x05
#define INTERFACE_CTL1			0x06
#define INTERFACE_CTL2			0x07
#define PASSTHROUGH_A_SELECT	0x08
#define PASSTHROUGH_B_SELECT	0x09
#define PLAYBACK_CTL1			0x0D // Not sure if needed
#define MISC_CTL				0x0E
#define PLAYBACK_CTL2			0x0F // Surely Needed
#define PASSTHROUGH_VOL_A		0x14
#define PASSTHROUGH_VOL_B		0x15
#define PCM_A_VOL				0x1A
#define PCM_B_VOL				0x1B
#define MASTER_A_VOL    		0x20
#define MASTER_B_VOL    		0x21
#define CONFIG_00				0x00
#define CONFIG_32				0x32
#define CONFIG_47				0x47

// CS43L22 Output Side Definitions
#define DUAL_OFF				0x00
#define MONO_LEFT				0x01
#define MONO_RIGHT				0x02
#define	DUAL_ON					0x03

// Inline functions for Volume Conversion
#define VOLUME_CONVERT_A(Vol)	(((Vol) > 100) ? 255:((uint8_t)(((Vol)*255)/100)))
#define VOLUME_CONVERT_B(Vol)	(((Vol) > 100) ? 24:((uint8_t)((((Vol)*48)/100)-24)))

// Declaration of Public Functions
void CS43_Init(void);
void CS43_Start(void);
void CS43_Stop(void);
void CS43_SetSide(uint8_t side);
void CS43_SetVolume(uint8_t volume);

#endif
