#ifndef __MYI2C_H
#define __MYI2C_H

#define MyI2Cx I2C1
#define I2Cx_CLK RCC_APB1Periph_I2C1

#include "stm32f10x.h"

void MyI2C_Init(void);
void MyI2C_WriteCommend(uint8_t SlaveAddr, uint8_t RegAddr, uint8_t Data);
void MyI2C_WriteData(uint8_t SlaveAddr, uint8_t RegAddr, uint8_t* Data,uint8_t count);
uint8_t MyI2C_Read(uint8_t SlaveAddr, uint8_t RegAddr);
void MyI2C_WaitEvent(uint32_t I2C_EVENT);
#endif
