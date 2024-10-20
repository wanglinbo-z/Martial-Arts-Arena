#include "FDT.h"

void FDT_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitTypeDef GPIO_FDT;
    GPIO_FDT.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_FDT.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_FDT.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_FDT);
}

uint8_t FDT_Read(uint8_t catch)
{
    if (catch == 1)
    {
        if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4) == 1)
        {
		    int Delay = 10000; while(Delay--);
            if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4) == 1)return 0;
        }
        else
        {
		    int Delay = 10000; while(Delay--);
            if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5) == 0)return 1;
        }
    }
    else if (catch == 2)
    {
        if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5) == 1)
        {
		    int Delay = 10000; while(Delay--);
            if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5) == 1)return 0;
        }
        else
        {
		    int Delay = 10000; while(Delay--);
            if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5) == 0)return 1;
        }
    }  
    return 0;
}


