#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "CS43xx.h"

#define F_SAMPLE	96000.0f
#define F_OUT		2000.0f
#define PI 		3.14159f

float mySinVal;
float sample_dt;
uint16_t dataI2S[100];
uint16_t sample_N;
uint16_t i_t;

int main(void)
{
	CS43_Init();
	CS43_SetVolume(100);
	CS43_SetSide(DUAL_ON);
	CS43_Start();

	sample_dt = F_OUT/F_SAMPLE;
	sample_N = F_SAMPLE/F_OUT;

	for(uint16_t i=0; i<sample_N; i++)
	{
		mySinVal = sinf(i*2*PI*sample_dt);
		dataI2S[i * 2] = (mySinVal ) * 8000;    //Right data (0 2 4 6 8 10 12)
		dataI2S[i * 2 + 1] =(mySinVal ) * 8000; //Left data  (1 3 5 7 9 11 13)
	}

	I2S3_SendData_Polling(dataI2S, 100);

	while(1)
	{

	}
}
