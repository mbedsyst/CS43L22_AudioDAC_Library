#ifndef I2S_H_
#define I2S_H_

#include "stm32f4xx.h"

void I2S3_Init(void);
void I2S3_SendData_Polling(uint16_t *data, uint16_t len);

#endif
