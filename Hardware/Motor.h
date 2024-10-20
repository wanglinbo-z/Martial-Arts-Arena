#ifndef __MOTOR_H
#define __MOTOR_H

#include "stm32f10x.h"

#define StoreData_RSpeedErr_Value 2
#define StoreData_LSpeedErr_Value 3

void Motor_Init(void);
void Motor_Stop(void);
void Motor_RSpeed(int16_t Speed);
void Motor_LSpeed(int16_t Speed);
uint16_t LSpeedErr(int16_t Err);
uint16_t RSpeedErr(int16_t Err);

#endif /* __MOTOR_H */
