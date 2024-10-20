#include "stm32f10x.h"

#include "LED.h"

void LED_Init(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    GPIO_InitTypeDef GPIO_LED;
    GPIO_LED.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_LED.GPIO_Pin = GPIO_Pin_7;
    GPIO_LED.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_LED);

    GPIO_WriteBit(LED_GPIO_PORT, LED_GPIO_PIN, Bit_SET);
}

