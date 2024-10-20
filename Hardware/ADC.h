#ifndef __ADC_H
#define __ADC_H
#include "stm32f10x.h"

#define Sensor0   AD_Value[0]
#define Sensor1   AD_Value[1]
#define Sensor2   AD_Value[2]
#define Sensor3   AD_Value[3]
#define Sensor4   AD_Value[4]
#define Sensor5   AD_Value[5]
#define Sensor6   AD_Value[6]
#define Sensor7   AD_Value[7]
#define Sensor8   AD_Value[8]
#define Sensor9   AD_Value[9]
#define Sensor10  AD_Value[10]
#define Sensor11  AD_Value[11]
#define Sensor12  AD_Value[12]
#define Sensor13  AD_Value[13]
#define Sensor14  AD_Value[14]
#define Sensor15  AD_Value[15]

#define L1 F_Distance(12)
#define L2 F_Distance(10)
#define L3 F_Distance(1)
#define L4 F_Distance(3)
#define L5 F_Distance(5)
#define L6 F_Distance(7)
#define L7 F_Distance(15)

#define R1 F_Distance(13)
#define R2 F_Distance(11)
#define R3 F_Distance(0)
#define R4 F_Distance(2)
#define R5 F_Distance(4)
#define R6 F_Distance(6)
#define R7 F_Distance(14)


void AD_Init(void);

#endif // __ADC_H
